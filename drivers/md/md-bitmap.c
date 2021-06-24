<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * biपंचांगap.c two-level biपंचांगap (C) Peter T. Breuer (ptb@ot.uc3m.es) 2003
 *
 * biपंचांगap_create  - sets up the biपंचांगap काष्ठाure
 * biपंचांगap_destroy - destroys the biपंचांगap काष्ठाure
 *
 * additions, Copyright (C) 2003-2004, Paul Clements, SteelEye Technology, Inc.:
 * - added disk storage क्रम biपंचांगap
 * - changes to allow various biपंचांगap chunk sizes
 */

/*
 * Still to करो:
 *
 * flush after percent set rather than just समय based. (maybe both).
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sched.h>
#समावेश <linux/list.h>
#समावेश <linux/file.h>
#समावेश <linux/mount.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/seq_file.h>
#समावेश <trace/events/block.h>
#समावेश "md.h"
#समावेश "md-bitmap.h"

अटल अंतरभूत अक्षर *bmname(काष्ठा biपंचांगap *biपंचांगap)
अणु
	वापस biपंचांगap->mddev ? mdname(biपंचांगap->mddev) : "mdX";
पूर्ण

/*
 * check a page and, अगर necessary, allocate it (or hijack it अगर the alloc fails)
 *
 * 1) check to see अगर this page is allocated, अगर it's not then try to alloc
 * 2) अगर the alloc fails, set the page's hijacked flag so we'll use the
 *    page poपूर्णांकer directly as a counter
 *
 * अगर we find our page, we increment the page's refcount so that it stays
 * allocated जबतक we're using it
 */
अटल पूर्णांक md_biपंचांगap_checkpage(काष्ठा biपंचांगap_counts *biपंचांगap,
			       अचिन्हित दीर्घ page, पूर्णांक create, पूर्णांक no_hijack)
__releases(biपंचांगap->lock)
__acquires(biपंचांगap->lock)
अणु
	अचिन्हित अक्षर *mappage;

	अगर (page >= biपंचांगap->pages) अणु
		/* This can happen अगर biपंचांगap_start_sync goes beyond
		 * End-of-device जबतक looking क्रम a whole page.
		 * It is harmless.
		 */
		वापस -EINVAL;
	पूर्ण

	अगर (biपंचांगap->bp[page].hijacked) /* it's hijacked, don't try to alloc */
		वापस 0;

	अगर (biपंचांगap->bp[page].map) /* page is alपढ़ोy allocated, just वापस */
		वापस 0;

	अगर (!create)
		वापस -ENOENT;

	/* this page has not been allocated yet */

	spin_unlock_irq(&biपंचांगap->lock);
	/* It is possible that this is being called inside a
	 * prepare_to_रुको/finish_रुको loop from raid5c:make_request().
	 * In general it is not permitted to sleep in that context as it
	 * can cause the loop to spin मुक्तly.
	 * That करोesn't apply here as we can only reach this poपूर्णांक
	 * once with any loop.
	 * When this function completes, either bp[page].map or
	 * bp[page].hijacked.  In either हाल, this function will
	 * पात beक्रमe getting to this poपूर्णांक again.  So there is
	 * no risk of a मुक्त-spin, and so it is safe to निश्चित
	 * that sleeping here is allowed.
	 */
	sched_annotate_sleep();
	mappage = kzalloc(PAGE_SIZE, GFP_NOIO);
	spin_lock_irq(&biपंचांगap->lock);

	अगर (mappage == शून्य) अणु
		pr_debug("md/bitmap: map page allocation failed, hijacking\n");
		/* We करोn't support hijack क्रम cluster raid */
		अगर (no_hijack)
			वापस -ENOMEM;
		/* failed - set the hijacked flag so that we can use the
		 * poपूर्णांकer as a counter */
		अगर (!biपंचांगap->bp[page].map)
			biपंचांगap->bp[page].hijacked = 1;
	पूर्ण अन्यथा अगर (biपंचांगap->bp[page].map ||
		   biपंचांगap->bp[page].hijacked) अणु
		/* somebody beat us to getting the page */
		kमुक्त(mappage);
	पूर्ण अन्यथा अणु

		/* no page was in place and we have one, so install it */

		biपंचांगap->bp[page].map = mappage;
		biपंचांगap->missing_pages--;
	पूर्ण
	वापस 0;
पूर्ण

/* अगर page is completely empty, put it back on the मुक्त list, or dealloc it */
/* अगर page was hijacked, unmark the flag so it might get alloced next समय */
/* Note: lock should be held when calling this */
अटल व्योम md_biपंचांगap_checkमुक्त(काष्ठा biपंचांगap_counts *biपंचांगap, अचिन्हित दीर्घ page)
अणु
	अक्षर *ptr;

	अगर (biपंचांगap->bp[page].count) /* page is still busy */
		वापस;

	/* page is no दीर्घer in use, it can be released */

	अगर (biपंचांगap->bp[page].hijacked) अणु /* page was hijacked, unकरो this now */
		biपंचांगap->bp[page].hijacked = 0;
		biपंचांगap->bp[page].map = शून्य;
	पूर्ण अन्यथा अणु
		/* normal हाल, मुक्त the page */
		ptr = biपंचांगap->bp[page].map;
		biपंचांगap->bp[page].map = शून्य;
		biपंचांगap->missing_pages++;
		kमुक्त(ptr);
	पूर्ण
पूर्ण

/*
 * biपंचांगap file handling - पढ़ो and ग_लिखो the biपंचांगap file and its superblock
 */

/*
 * basic page I/O operations
 */

/* IO operations when biपंचांगap is stored near all superblocks */
अटल पूर्णांक पढ़ो_sb_page(काष्ठा mddev *mddev, loff_t offset,
			काष्ठा page *page,
			अचिन्हित दीर्घ index, पूर्णांक size)
अणु
	/* choose a good rdev and पढ़ो the page from there */

	काष्ठा md_rdev *rdev;
	sector_t target;

	rdev_क्रम_each(rdev, mddev) अणु
		अगर (! test_bit(In_sync, &rdev->flags)
		    || test_bit(Faulty, &rdev->flags)
		    || test_bit(Biपंचांगap_sync, &rdev->flags))
			जारी;

		target = offset + index * (PAGE_SIZE/512);

		अगर (sync_page_io(rdev, target,
				 roundup(size, bdev_logical_block_size(rdev->bdev)),
				 page, REQ_OP_READ, 0, true)) अणु
			page->index = index;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EIO;
पूर्ण

अटल काष्ठा md_rdev *next_active_rdev(काष्ठा md_rdev *rdev, काष्ठा mddev *mddev)
अणु
	/* Iterate the disks of an mddev, using rcu to protect access to the
	 * linked list, and raising the refcount of devices we वापस to ensure
	 * they करोn't disappear जबतक in use.
	 * As devices are only added or हटाओd when raid_disk is < 0 and
	 * nr_pending is 0 and In_sync is clear, the entries we वापस will
	 * still be in the same position on the list when we re-enter
	 * list_क्रम_each_entry_जारी_rcu.
	 *
	 * Note that अगर entered with 'rdev == NULL' to start at the
	 * beginning, we temporarily assign 'rdev' to an address which
	 * isn't really an rdev, but which can be used by
	 * list_क्रम_each_entry_जारी_rcu() to find the first entry.
	 */
	rcu_पढ़ो_lock();
	अगर (rdev == शून्य)
		/* start at the beginning */
		rdev = list_entry(&mddev->disks, काष्ठा md_rdev, same_set);
	अन्यथा अणु
		/* release the previous rdev and start from there. */
		rdev_dec_pending(rdev, mddev);
	पूर्ण
	list_क्रम_each_entry_जारी_rcu(rdev, &mddev->disks, same_set) अणु
		अगर (rdev->raid_disk >= 0 &&
		    !test_bit(Faulty, &rdev->flags)) अणु
			/* this is a usable devices */
			atomic_inc(&rdev->nr_pending);
			rcu_पढ़ो_unlock();
			वापस rdev;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

अटल पूर्णांक ग_लिखो_sb_page(काष्ठा biपंचांगap *biपंचांगap, काष्ठा page *page, पूर्णांक रुको)
अणु
	काष्ठा md_rdev *rdev;
	काष्ठा block_device *bdev;
	काष्ठा mddev *mddev = biपंचांगap->mddev;
	काष्ठा biपंचांगap_storage *store = &biपंचांगap->storage;

restart:
	rdev = शून्य;
	जबतक ((rdev = next_active_rdev(rdev, mddev)) != शून्य) अणु
		पूर्णांक size = PAGE_SIZE;
		loff_t offset = mddev->biपंचांगap_info.offset;

		bdev = (rdev->meta_bdev) ? rdev->meta_bdev : rdev->bdev;

		अगर (page->index == store->file_pages-1) अणु
			पूर्णांक last_page_size = store->bytes & (PAGE_SIZE-1);
			अगर (last_page_size == 0)
				last_page_size = PAGE_SIZE;
			size = roundup(last_page_size,
				       bdev_logical_block_size(bdev));
		पूर्ण
		/* Just make sure we aren't corrupting data or
		 * metadata
		 */
		अगर (mddev->बाह्यal) अणु
			/* Biपंचांगap could be anywhere. */
			अगर (rdev->sb_start + offset + (page->index
						       * (PAGE_SIZE/512))
			    > rdev->data_offset
			    &&
			    rdev->sb_start + offset
			    < (rdev->data_offset + mddev->dev_sectors
			     + (PAGE_SIZE/512)))
				जाओ bad_alignment;
		पूर्ण अन्यथा अगर (offset < 0) अणु
			/* DATA  BITMAP METADATA  */
			अगर (offset
			    + (दीर्घ)(page->index * (PAGE_SIZE/512))
			    + size/512 > 0)
				/* biपंचांगap runs in to metadata */
				जाओ bad_alignment;
			अगर (rdev->data_offset + mddev->dev_sectors
			    > rdev->sb_start + offset)
				/* data runs in to biपंचांगap */
				जाओ bad_alignment;
		पूर्ण अन्यथा अगर (rdev->sb_start < rdev->data_offset) अणु
			/* METADATA BITMAP DATA */
			अगर (rdev->sb_start
			    + offset
			    + page->index*(PAGE_SIZE/512) + size/512
			    > rdev->data_offset)
				/* biपंचांगap runs in to data */
				जाओ bad_alignment;
		पूर्ण अन्यथा अणु
			/* DATA METADATA BITMAP - no problems */
		पूर्ण
		md_super_ग_लिखो(mddev, rdev,
			       rdev->sb_start + offset
			       + page->index * (PAGE_SIZE/512),
			       size,
			       page);
	पूर्ण

	अगर (रुको && md_super_रुको(mddev) < 0)
		जाओ restart;
	वापस 0;

 bad_alignment:
	वापस -EINVAL;
पूर्ण

अटल व्योम md_biपंचांगap_file_kick(काष्ठा biपंचांगap *biपंचांगap);
/*
 * ग_लिखो out a page to a file
 */
अटल व्योम ग_लिखो_page(काष्ठा biपंचांगap *biपंचांगap, काष्ठा page *page, पूर्णांक रुको)
अणु
	काष्ठा buffer_head *bh;

	अगर (biपंचांगap->storage.file == शून्य) अणु
		चयन (ग_लिखो_sb_page(biपंचांगap, page, रुको)) अणु
		हाल -EINVAL:
			set_bit(BITMAP_WRITE_ERROR, &biपंचांगap->flags);
		पूर्ण
	पूर्ण अन्यथा अणु

		bh = page_buffers(page);

		जबतक (bh && bh->b_blocknr) अणु
			atomic_inc(&biपंचांगap->pending_ग_लिखोs);
			set_buffer_locked(bh);
			set_buffer_mapped(bh);
			submit_bh(REQ_OP_WRITE, REQ_SYNC, bh);
			bh = bh->b_this_page;
		पूर्ण

		अगर (रुको)
			रुको_event(biपंचांगap->ग_लिखो_रुको,
				   atomic_पढ़ो(&biपंचांगap->pending_ग_लिखोs)==0);
	पूर्ण
	अगर (test_bit(BITMAP_WRITE_ERROR, &biपंचांगap->flags))
		md_biपंचांगap_file_kick(biपंचांगap);
पूर्ण

अटल व्योम end_biपंचांगap_ग_लिखो(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	काष्ठा biपंचांगap *biपंचांगap = bh->b_निजी;

	अगर (!uptodate)
		set_bit(BITMAP_WRITE_ERROR, &biपंचांगap->flags);
	अगर (atomic_dec_and_test(&biपंचांगap->pending_ग_लिखोs))
		wake_up(&biपंचांगap->ग_लिखो_रुको);
पूर्ण

अटल व्योम मुक्त_buffers(काष्ठा page *page)
अणु
	काष्ठा buffer_head *bh;

	अगर (!PagePrivate(page))
		वापस;

	bh = page_buffers(page);
	जबतक (bh) अणु
		काष्ठा buffer_head *next = bh->b_this_page;
		मुक्त_buffer_head(bh);
		bh = next;
	पूर्ण
	detach_page_निजी(page);
	put_page(page);
पूर्ण

/* पढ़ो a page from a file.
 * We both पढ़ो the page, and attach buffers to the page to record the
 * address of each block (using bmap).  These addresses will be used
 * to ग_लिखो the block later, completely bypassing the fileप्रणाली.
 * This usage is similar to how swap files are handled, and allows us
 * to ग_लिखो to a file with no concerns of memory allocation failing.
 */
अटल पूर्णांक पढ़ो_page(काष्ठा file *file, अचिन्हित दीर्घ index,
		     काष्ठा biपंचांगap *biपंचांगap,
		     अचिन्हित दीर्घ count,
		     काष्ठा page *page)
अणु
	पूर्णांक ret = 0;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा buffer_head *bh;
	sector_t block, blk_cur;
	अचिन्हित दीर्घ blocksize = i_blocksize(inode);

	pr_debug("read bitmap file (%dB @ %llu)\n", (पूर्णांक)PAGE_SIZE,
		 (अचिन्हित दीर्घ दीर्घ)index << PAGE_SHIFT);

	bh = alloc_page_buffers(page, blocksize, false);
	अगर (!bh) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	attach_page_निजी(page, bh);
	blk_cur = index << (PAGE_SHIFT - inode->i_blkbits);
	जबतक (bh) अणु
		block = blk_cur;

		अगर (count == 0)
			bh->b_blocknr = 0;
		अन्यथा अणु
			ret = bmap(inode, &block);
			अगर (ret || !block) अणु
				ret = -EINVAL;
				bh->b_blocknr = 0;
				जाओ out;
			पूर्ण

			bh->b_blocknr = block;
			bh->b_bdev = inode->i_sb->s_bdev;
			अगर (count < blocksize)
				count = 0;
			अन्यथा
				count -= blocksize;

			bh->b_end_io = end_biपंचांगap_ग_लिखो;
			bh->b_निजी = biपंचांगap;
			atomic_inc(&biपंचांगap->pending_ग_लिखोs);
			set_buffer_locked(bh);
			set_buffer_mapped(bh);
			submit_bh(REQ_OP_READ, 0, bh);
		पूर्ण
		blk_cur++;
		bh = bh->b_this_page;
	पूर्ण
	page->index = index;

	रुको_event(biपंचांगap->ग_लिखो_रुको,
		   atomic_पढ़ो(&biपंचांगap->pending_ग_लिखोs)==0);
	अगर (test_bit(BITMAP_WRITE_ERROR, &biपंचांगap->flags))
		ret = -EIO;
out:
	अगर (ret)
		pr_err("md: bitmap read error: (%dB @ %llu): %d\n",
		       (पूर्णांक)PAGE_SIZE,
		       (अचिन्हित दीर्घ दीर्घ)index << PAGE_SHIFT,
		       ret);
	वापस ret;
पूर्ण

/*
 * biपंचांगap file superblock operations
 */

/*
 * md_biपंचांगap_रुको_ग_लिखोs() should be called beक्रमe writing any biपंचांगap
 * blocks, to ensure previous ग_लिखोs, particularly from
 * md_biपंचांगap_daemon_work(), have completed.
 */
अटल व्योम md_biपंचांगap_रुको_ग_लिखोs(काष्ठा biपंचांगap *biपंचांगap)
अणु
	अगर (biपंचांगap->storage.file)
		रुको_event(biपंचांगap->ग_लिखो_रुको,
			   atomic_पढ़ो(&biपंचांगap->pending_ग_लिखोs)==0);
	अन्यथा
		/* Note that we ignore the वापस value.  The ग_लिखोs
		 * might have failed, but that would just mean that
		 * some bits which should be cleared haven't been,
		 * which is safe.  The relevant biपंचांगap blocks will
		 * probably get written again, but there is no great
		 * loss अगर they aren't.
		 */
		md_super_रुको(biपंचांगap->mddev);
पूर्ण


/* update the event counter and sync the superblock to disk */
व्योम md_biपंचांगap_update_sb(काष्ठा biपंचांगap *biपंचांगap)
अणु
	biपंचांगap_super_t *sb;

	अगर (!biपंचांगap || !biपंचांगap->mddev) /* no biपंचांगap क्रम this array */
		वापस;
	अगर (biपंचांगap->mddev->biपंचांगap_info.बाह्यal)
		वापस;
	अगर (!biपंचांगap->storage.sb_page) /* no superblock */
		वापस;
	sb = kmap_atomic(biपंचांगap->storage.sb_page);
	sb->events = cpu_to_le64(biपंचांगap->mddev->events);
	अगर (biपंचांगap->mddev->events < biपंचांगap->events_cleared)
		/* rocking back to पढ़ो-only */
		biपंचांगap->events_cleared = biपंचांगap->mddev->events;
	sb->events_cleared = cpu_to_le64(biपंचांगap->events_cleared);
	/*
	 * clear BITMAP_WRITE_ERROR bit to protect against the हाल that
	 * a biपंचांगap ग_लिखो error occurred but the later ग_लिखोs succeeded.
	 */
	sb->state = cpu_to_le32(biपंचांगap->flags & ~BIT(BITMAP_WRITE_ERROR));
	/* Just in हाल these have been changed via sysfs: */
	sb->daemon_sleep = cpu_to_le32(biपंचांगap->mddev->biपंचांगap_info.daemon_sleep/HZ);
	sb->ग_लिखो_behind = cpu_to_le32(biपंचांगap->mddev->biपंचांगap_info.max_ग_लिखो_behind);
	/* This might have been changed by a reshape */
	sb->sync_size = cpu_to_le64(biपंचांगap->mddev->resync_max_sectors);
	sb->chunksize = cpu_to_le32(biपंचांगap->mddev->biपंचांगap_info.chunksize);
	sb->nodes = cpu_to_le32(biपंचांगap->mddev->biपंचांगap_info.nodes);
	sb->sectors_reserved = cpu_to_le32(biपंचांगap->mddev->
					   biपंचांगap_info.space);
	kunmap_atomic(sb);
	ग_लिखो_page(biपंचांगap, biपंचांगap->storage.sb_page, 1);
पूर्ण
EXPORT_SYMBOL(md_biपंचांगap_update_sb);

/* prपूर्णांक out the biपंचांगap file superblock */
व्योम md_biपंचांगap_prपूर्णांक_sb(काष्ठा biपंचांगap *biपंचांगap)
अणु
	biपंचांगap_super_t *sb;

	अगर (!biपंचांगap || !biपंचांगap->storage.sb_page)
		वापस;
	sb = kmap_atomic(biपंचांगap->storage.sb_page);
	pr_debug("%s: bitmap file superblock:\n", bmname(biपंचांगap));
	pr_debug("         magic: %08x\n", le32_to_cpu(sb->magic));
	pr_debug("       version: %d\n", le32_to_cpu(sb->version));
	pr_debug("          uuid: %08x.%08x.%08x.%08x\n",
		 le32_to_cpu(*(__le32 *)(sb->uuid+0)),
		 le32_to_cpu(*(__le32 *)(sb->uuid+4)),
		 le32_to_cpu(*(__le32 *)(sb->uuid+8)),
		 le32_to_cpu(*(__le32 *)(sb->uuid+12)));
	pr_debug("        events: %llu\n",
		 (अचिन्हित दीर्घ दीर्घ) le64_to_cpu(sb->events));
	pr_debug("events cleared: %llu\n",
		 (अचिन्हित दीर्घ दीर्घ) le64_to_cpu(sb->events_cleared));
	pr_debug("         state: %08x\n", le32_to_cpu(sb->state));
	pr_debug("     chunksize: %d B\n", le32_to_cpu(sb->chunksize));
	pr_debug("  daemon sleep: %ds\n", le32_to_cpu(sb->daemon_sleep));
	pr_debug("     sync size: %llu KB\n",
		 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(sb->sync_size)/2);
	pr_debug("max write behind: %d\n", le32_to_cpu(sb->ग_लिखो_behind));
	kunmap_atomic(sb);
पूर्ण

/*
 * biपंचांगap_new_disk_sb
 * @biपंचांगap
 *
 * This function is somewhat the reverse of biपंचांगap_पढ़ो_sb.  biपंचांगap_पढ़ो_sb
 * पढ़ोs and verअगरies the on-disk biपंचांगap superblock and populates biपंचांगap_info.
 * This function verअगरies 'bitmap_info' and populates the on-disk biपंचांगap
 * काष्ठाure, which is to be written to disk.
 *
 * Returns: 0 on success, -Exxx on error
 */
अटल पूर्णांक md_biपंचांगap_new_disk_sb(काष्ठा biपंचांगap *biपंचांगap)
अणु
	biपंचांगap_super_t *sb;
	अचिन्हित दीर्घ chunksize, daemon_sleep, ग_लिखो_behind;

	biपंचांगap->storage.sb_page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	अगर (biपंचांगap->storage.sb_page == शून्य)
		वापस -ENOMEM;
	biपंचांगap->storage.sb_page->index = 0;

	sb = kmap_atomic(biपंचांगap->storage.sb_page);

	sb->magic = cpu_to_le32(BITMAP_MAGIC);
	sb->version = cpu_to_le32(BITMAP_MAJOR_HI);

	chunksize = biपंचांगap->mddev->biपंचांगap_info.chunksize;
	BUG_ON(!chunksize);
	अगर (!is_घातer_of_2(chunksize)) अणु
		kunmap_atomic(sb);
		pr_warn("bitmap chunksize not a power of 2\n");
		वापस -EINVAL;
	पूर्ण
	sb->chunksize = cpu_to_le32(chunksize);

	daemon_sleep = biपंचांगap->mddev->biपंचांगap_info.daemon_sleep;
	अगर (!daemon_sleep || (daemon_sleep > MAX_SCHEDULE_TIMEOUT)) अणु
		pr_debug("Choosing daemon_sleep default (5 sec)\n");
		daemon_sleep = 5 * HZ;
	पूर्ण
	sb->daemon_sleep = cpu_to_le32(daemon_sleep);
	biपंचांगap->mddev->biपंचांगap_info.daemon_sleep = daemon_sleep;

	/*
	 * FIXME: ग_लिखो_behind क्रम RAID1.  If not specअगरied, what
	 * is a good choice?  We choose COUNTER_MAX / 2 arbitrarily.
	 */
	ग_लिखो_behind = biपंचांगap->mddev->biपंचांगap_info.max_ग_लिखो_behind;
	अगर (ग_लिखो_behind > COUNTER_MAX)
		ग_लिखो_behind = COUNTER_MAX / 2;
	sb->ग_लिखो_behind = cpu_to_le32(ग_लिखो_behind);
	biपंचांगap->mddev->biपंचांगap_info.max_ग_लिखो_behind = ग_लिखो_behind;

	/* keep the array size field of the biपंचांगap superblock up to date */
	sb->sync_size = cpu_to_le64(biपंचांगap->mddev->resync_max_sectors);

	स_नकल(sb->uuid, biपंचांगap->mddev->uuid, 16);

	set_bit(BITMAP_STALE, &biपंचांगap->flags);
	sb->state = cpu_to_le32(biपंचांगap->flags);
	biपंचांगap->events_cleared = biपंचांगap->mddev->events;
	sb->events_cleared = cpu_to_le64(biपंचांगap->mddev->events);
	biपंचांगap->mddev->biपंचांगap_info.nodes = 0;

	kunmap_atomic(sb);

	वापस 0;
पूर्ण

/* पढ़ो the superblock from the biपंचांगap file and initialize some biपंचांगap fields */
अटल पूर्णांक md_biपंचांगap_पढ़ो_sb(काष्ठा biपंचांगap *biपंचांगap)
अणु
	अक्षर *reason = शून्य;
	biपंचांगap_super_t *sb;
	अचिन्हित दीर्घ chunksize, daemon_sleep, ग_लिखो_behind;
	अचिन्हित दीर्घ दीर्घ events;
	पूर्णांक nodes = 0;
	अचिन्हित दीर्घ sectors_reserved = 0;
	पूर्णांक err = -EINVAL;
	काष्ठा page *sb_page;
	loff_t offset = biपंचांगap->mddev->biपंचांगap_info.offset;

	अगर (!biपंचांगap->storage.file && !biपंचांगap->mddev->biपंचांगap_info.offset) अणु
		chunksize = 128 * 1024 * 1024;
		daemon_sleep = 5 * HZ;
		ग_लिखो_behind = 0;
		set_bit(BITMAP_STALE, &biपंचांगap->flags);
		err = 0;
		जाओ out_no_sb;
	पूर्ण
	/* page 0 is the superblock, पढ़ो it... */
	sb_page = alloc_page(GFP_KERNEL);
	अगर (!sb_page)
		वापस -ENOMEM;
	biपंचांगap->storage.sb_page = sb_page;

re_पढ़ो:
	/* If cluster_slot is set, the cluster is setup */
	अगर (biपंचांगap->cluster_slot >= 0) अणु
		sector_t bm_blocks = biपंचांगap->mddev->resync_max_sectors;

		bm_blocks = DIV_ROUND_UP_SECTOR_T(bm_blocks,
			   (biपंचांगap->mddev->biपंचांगap_info.chunksize >> 9));
		/* bits to bytes */
		bm_blocks = ((bm_blocks+7) >> 3) + माप(biपंचांगap_super_t);
		/* to 4k blocks */
		bm_blocks = DIV_ROUND_UP_SECTOR_T(bm_blocks, 4096);
		offset = biपंचांगap->mddev->biपंचांगap_info.offset + (biपंचांगap->cluster_slot * (bm_blocks << 3));
		pr_debug("%s:%d bm slot: %d offset: %llu\n", __func__, __LINE__,
			biपंचांगap->cluster_slot, offset);
	पूर्ण

	अगर (biपंचांगap->storage.file) अणु
		loff_t isize = i_size_पढ़ो(biपंचांगap->storage.file->f_mapping->host);
		पूर्णांक bytes = isize > PAGE_SIZE ? PAGE_SIZE : isize;

		err = पढ़ो_page(biपंचांगap->storage.file, 0,
				biपंचांगap, bytes, sb_page);
	पूर्ण अन्यथा अणु
		err = पढ़ो_sb_page(biपंचांगap->mddev,
				   offset,
				   sb_page,
				   0, माप(biपंचांगap_super_t));
	पूर्ण
	अगर (err)
		वापस err;

	err = -EINVAL;
	sb = kmap_atomic(sb_page);

	chunksize = le32_to_cpu(sb->chunksize);
	daemon_sleep = le32_to_cpu(sb->daemon_sleep) * HZ;
	ग_लिखो_behind = le32_to_cpu(sb->ग_लिखो_behind);
	sectors_reserved = le32_to_cpu(sb->sectors_reserved);
	/* Setup nodes/clustername only अगर biपंचांगap version is
	 * cluster-compatible
	 */
	अगर (sb->version == cpu_to_le32(BITMAP_MAJOR_CLUSTERED)) अणु
		nodes = le32_to_cpu(sb->nodes);
		strlcpy(biपंचांगap->mddev->biपंचांगap_info.cluster_name,
				sb->cluster_name, 64);
	पूर्ण

	/* verअगरy that the biपंचांगap-specअगरic fields are valid */
	अगर (sb->magic != cpu_to_le32(BITMAP_MAGIC))
		reason = "bad magic";
	अन्यथा अगर (le32_to_cpu(sb->version) < BITMAP_MAJOR_LO ||
		 le32_to_cpu(sb->version) > BITMAP_MAJOR_CLUSTERED)
		reason = "unrecognized superblock version";
	अन्यथा अगर (chunksize < 512)
		reason = "bitmap chunksize too small";
	अन्यथा अगर (!is_घातer_of_2(chunksize))
		reason = "bitmap chunksize not a power of 2";
	अन्यथा अगर (daemon_sleep < 1 || daemon_sleep > MAX_SCHEDULE_TIMEOUT)
		reason = "daemon sleep period out of range";
	अन्यथा अगर (ग_लिखो_behind > COUNTER_MAX)
		reason = "write-behind limit out of range (0 - 16383)";
	अगर (reason) अणु
		pr_warn("%s: invalid bitmap file superblock: %s\n",
			bmname(biपंचांगap), reason);
		जाओ out;
	पूर्ण

	/* keep the array size field of the biपंचांगap superblock up to date */
	sb->sync_size = cpu_to_le64(biपंचांगap->mddev->resync_max_sectors);

	अगर (biपंचांगap->mddev->persistent) अणु
		/*
		 * We have a persistent array superblock, so compare the
		 * biपंचांगap's UUID and event counter to the mddev's
		 */
		अगर (स_भेद(sb->uuid, biपंचांगap->mddev->uuid, 16)) अणु
			pr_warn("%s: bitmap superblock UUID mismatch\n",
				bmname(biपंचांगap));
			जाओ out;
		पूर्ण
		events = le64_to_cpu(sb->events);
		अगर (!nodes && (events < biपंचांगap->mddev->events)) अणु
			pr_warn("%s: bitmap file is out of date (%llu < %llu) -- forcing full recovery\n",
				bmname(biपंचांगap), events,
				(अचिन्हित दीर्घ दीर्घ) biपंचांगap->mddev->events);
			set_bit(BITMAP_STALE, &biपंचांगap->flags);
		पूर्ण
	पूर्ण

	/* assign fields using values from superblock */
	biपंचांगap->flags |= le32_to_cpu(sb->state);
	अगर (le32_to_cpu(sb->version) == BITMAP_MAJOR_HOSTENDIAN)
		set_bit(BITMAP_HOSTENDIAN, &biपंचांगap->flags);
	biपंचांगap->events_cleared = le64_to_cpu(sb->events_cleared);
	strlcpy(biपंचांगap->mddev->biपंचांगap_info.cluster_name, sb->cluster_name, 64);
	err = 0;

out:
	kunmap_atomic(sb);
	/* Assigning chunksize is required क्रम "re_read" */
	biपंचांगap->mddev->biपंचांगap_info.chunksize = chunksize;
	अगर (err == 0 && nodes && (biपंचांगap->cluster_slot < 0)) अणु
		err = md_setup_cluster(biपंचांगap->mddev, nodes);
		अगर (err) अणु
			pr_warn("%s: Could not setup cluster service (%d)\n",
				bmname(biपंचांगap), err);
			जाओ out_no_sb;
		पूर्ण
		biपंचांगap->cluster_slot = md_cluster_ops->slot_number(biपंचांगap->mddev);
		जाओ re_पढ़ो;
	पूर्ण


out_no_sb:
	अगर (test_bit(BITMAP_STALE, &biपंचांगap->flags))
		biपंचांगap->events_cleared = biपंचांगap->mddev->events;
	biपंचांगap->mddev->biपंचांगap_info.chunksize = chunksize;
	biपंचांगap->mddev->biपंचांगap_info.daemon_sleep = daemon_sleep;
	biपंचांगap->mddev->biपंचांगap_info.max_ग_लिखो_behind = ग_लिखो_behind;
	biपंचांगap->mddev->biपंचांगap_info.nodes = nodes;
	अगर (biपंचांगap->mddev->biपंचांगap_info.space == 0 ||
	    biपंचांगap->mddev->biपंचांगap_info.space > sectors_reserved)
		biपंचांगap->mddev->biपंचांगap_info.space = sectors_reserved;
	अगर (err) अणु
		md_biपंचांगap_prपूर्णांक_sb(biपंचांगap);
		अगर (biपंचांगap->cluster_slot < 0)
			md_cluster_stop(biपंचांगap->mddev);
	पूर्ण
	वापस err;
पूर्ण

/*
 * general biपंचांगap file operations
 */

/*
 * on-disk biपंचांगap:
 *
 * Use one bit per "chunk" (block set). We करो the disk I/O on the biपंचांगap
 * file a page at a समय. There's a superblock at the start of the file.
 */
/* calculate the index of the page that contains this bit */
अटल अंतरभूत अचिन्हित दीर्घ file_page_index(काष्ठा biपंचांगap_storage *store,
					    अचिन्हित दीर्घ chunk)
अणु
	अगर (store->sb_page)
		chunk += माप(biपंचांगap_super_t) << 3;
	वापस chunk >> PAGE_BIT_SHIFT;
पूर्ण

/* calculate the (bit) offset of this bit within a page */
अटल अंतरभूत अचिन्हित दीर्घ file_page_offset(काष्ठा biपंचांगap_storage *store,
					     अचिन्हित दीर्घ chunk)
अणु
	अगर (store->sb_page)
		chunk += माप(biपंचांगap_super_t) << 3;
	वापस chunk & (PAGE_BITS - 1);
पूर्ण

/*
 * वापस a poपूर्णांकer to the page in the filemap that contains the given bit
 *
 */
अटल अंतरभूत काष्ठा page *filemap_get_page(काष्ठा biपंचांगap_storage *store,
					    अचिन्हित दीर्घ chunk)
अणु
	अगर (file_page_index(store, chunk) >= store->file_pages)
		वापस शून्य;
	वापस store->filemap[file_page_index(store, chunk)];
पूर्ण

अटल पूर्णांक md_biपंचांगap_storage_alloc(काष्ठा biपंचांगap_storage *store,
				   अचिन्हित दीर्घ chunks, पूर्णांक with_super,
				   पूर्णांक slot_number)
अणु
	पूर्णांक pnum, offset = 0;
	अचिन्हित दीर्घ num_pages;
	अचिन्हित दीर्घ bytes;

	bytes = DIV_ROUND_UP(chunks, 8);
	अगर (with_super)
		bytes += माप(biपंचांगap_super_t);

	num_pages = DIV_ROUND_UP(bytes, PAGE_SIZE);
	offset = slot_number * num_pages;

	store->filemap = kदो_स्मृति_array(num_pages, माप(काष्ठा page *),
				       GFP_KERNEL);
	अगर (!store->filemap)
		वापस -ENOMEM;

	अगर (with_super && !store->sb_page) अणु
		store->sb_page = alloc_page(GFP_KERNEL|__GFP_ZERO);
		अगर (store->sb_page == शून्य)
			वापस -ENOMEM;
	पूर्ण

	pnum = 0;
	अगर (store->sb_page) अणु
		store->filemap[0] = store->sb_page;
		pnum = 1;
		store->sb_page->index = offset;
	पूर्ण

	क्रम ( ; pnum < num_pages; pnum++) अणु
		store->filemap[pnum] = alloc_page(GFP_KERNEL|__GFP_ZERO);
		अगर (!store->filemap[pnum]) अणु
			store->file_pages = pnum;
			वापस -ENOMEM;
		पूर्ण
		store->filemap[pnum]->index = pnum + offset;
	पूर्ण
	store->file_pages = pnum;

	/* We need 4 bits per page, rounded up to a multiple
	 * of माप(अचिन्हित दीर्घ) */
	store->filemap_attr = kzalloc(
		roundup(DIV_ROUND_UP(num_pages*4, 8), माप(अचिन्हित दीर्घ)),
		GFP_KERNEL);
	अगर (!store->filemap_attr)
		वापस -ENOMEM;

	store->bytes = bytes;

	वापस 0;
पूर्ण

अटल व्योम md_biपंचांगap_file_unmap(काष्ठा biपंचांगap_storage *store)
अणु
	काष्ठा page **map, *sb_page;
	पूर्णांक pages;
	काष्ठा file *file;

	file = store->file;
	map = store->filemap;
	pages = store->file_pages;
	sb_page = store->sb_page;

	जबतक (pages--)
		अगर (map[pages] != sb_page) /* 0 is sb_page, release it below */
			मुक्त_buffers(map[pages]);
	kमुक्त(map);
	kमुक्त(store->filemap_attr);

	अगर (sb_page)
		मुक्त_buffers(sb_page);

	अगर (file) अणु
		काष्ठा inode *inode = file_inode(file);
		invalidate_mapping_pages(inode->i_mapping, 0, -1);
		fput(file);
	पूर्ण
पूर्ण

/*
 * biपंचांगap_file_kick - अगर an error occurs जबतक manipulating the biपंचांगap file
 * then it is no दीर्घer reliable, so we stop using it and we mark the file
 * as failed in the superblock
 */
अटल व्योम md_biपंचांगap_file_kick(काष्ठा biपंचांगap *biपंचांगap)
अणु
	अक्षर *path, *ptr = शून्य;

	अगर (!test_and_set_bit(BITMAP_STALE, &biपंचांगap->flags)) अणु
		md_biपंचांगap_update_sb(biपंचांगap);

		अगर (biपंचांगap->storage.file) अणु
			path = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
			अगर (path)
				ptr = file_path(biपंचांगap->storage.file,
					     path, PAGE_SIZE);

			pr_warn("%s: kicking failed bitmap file %s from array!\n",
				bmname(biपंचांगap), IS_ERR(ptr) ? "" : ptr);

			kमुक्त(path);
		पूर्ण अन्यथा
			pr_warn("%s: disabling internal bitmap due to errors\n",
				bmname(biपंचांगap));
	पूर्ण
पूर्ण

क्रमागत biपंचांगap_page_attr अणु
	BITMAP_PAGE_सूचीTY = 0,     /* there are set bits that need to be synced */
	BITMAP_PAGE_PENDING = 1,   /* there are bits that are being cleaned.
				    * i.e. counter is 1 or 2. */
	BITMAP_PAGE_NEEDWRITE = 2, /* there are cleared bits that need to be synced */
पूर्ण;

अटल अंतरभूत व्योम set_page_attr(काष्ठा biपंचांगap *biपंचांगap, पूर्णांक pnum,
				 क्रमागत biपंचांगap_page_attr attr)
अणु
	set_bit((pnum<<2) + attr, biपंचांगap->storage.filemap_attr);
पूर्ण

अटल अंतरभूत व्योम clear_page_attr(काष्ठा biपंचांगap *biपंचांगap, पूर्णांक pnum,
				   क्रमागत biपंचांगap_page_attr attr)
अणु
	clear_bit((pnum<<2) + attr, biपंचांगap->storage.filemap_attr);
पूर्ण

अटल अंतरभूत पूर्णांक test_page_attr(काष्ठा biपंचांगap *biपंचांगap, पूर्णांक pnum,
				 क्रमागत biपंचांगap_page_attr attr)
अणु
	वापस test_bit((pnum<<2) + attr, biपंचांगap->storage.filemap_attr);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_clear_page_attr(काष्ठा biपंचांगap *biपंचांगap, पूर्णांक pnum,
					   क्रमागत biपंचांगap_page_attr attr)
अणु
	वापस test_and_clear_bit((pnum<<2) + attr,
				  biपंचांगap->storage.filemap_attr);
पूर्ण
/*
 * biपंचांगap_file_set_bit -- called beक्रमe perक्रमming a ग_लिखो to the md device
 * to set (and eventually sync) a particular bit in the biपंचांगap file
 *
 * we set the bit immediately, then we record the page number so that
 * when an unplug occurs, we can flush the dirty pages out to disk
 */
अटल व्योम md_biपंचांगap_file_set_bit(काष्ठा biपंचांगap *biपंचांगap, sector_t block)
अणु
	अचिन्हित दीर्घ bit;
	काष्ठा page *page;
	व्योम *kaddr;
	अचिन्हित दीर्घ chunk = block >> biपंचांगap->counts.chunkshअगरt;
	काष्ठा biपंचांगap_storage *store = &biपंचांगap->storage;
	अचिन्हित दीर्घ node_offset = 0;

	अगर (mddev_is_clustered(biपंचांगap->mddev))
		node_offset = biपंचांगap->cluster_slot * store->file_pages;

	page = filemap_get_page(&biपंचांगap->storage, chunk);
	अगर (!page)
		वापस;
	bit = file_page_offset(&biपंचांगap->storage, chunk);

	/* set the bit */
	kaddr = kmap_atomic(page);
	अगर (test_bit(BITMAP_HOSTENDIAN, &biपंचांगap->flags))
		set_bit(bit, kaddr);
	अन्यथा
		set_bit_le(bit, kaddr);
	kunmap_atomic(kaddr);
	pr_debug("set file bit %lu page %lu\n", bit, page->index);
	/* record page number so it माला_लो flushed to disk when unplug occurs */
	set_page_attr(biपंचांगap, page->index - node_offset, BITMAP_PAGE_सूचीTY);
पूर्ण

अटल व्योम md_biपंचांगap_file_clear_bit(काष्ठा biपंचांगap *biपंचांगap, sector_t block)
अणु
	अचिन्हित दीर्घ bit;
	काष्ठा page *page;
	व्योम *paddr;
	अचिन्हित दीर्घ chunk = block >> biपंचांगap->counts.chunkshअगरt;
	काष्ठा biपंचांगap_storage *store = &biपंचांगap->storage;
	अचिन्हित दीर्घ node_offset = 0;

	अगर (mddev_is_clustered(biपंचांगap->mddev))
		node_offset = biपंचांगap->cluster_slot * store->file_pages;

	page = filemap_get_page(&biपंचांगap->storage, chunk);
	अगर (!page)
		वापस;
	bit = file_page_offset(&biपंचांगap->storage, chunk);
	paddr = kmap_atomic(page);
	अगर (test_bit(BITMAP_HOSTENDIAN, &biपंचांगap->flags))
		clear_bit(bit, paddr);
	अन्यथा
		clear_bit_le(bit, paddr);
	kunmap_atomic(paddr);
	अगर (!test_page_attr(biपंचांगap, page->index - node_offset, BITMAP_PAGE_NEEDWRITE)) अणु
		set_page_attr(biपंचांगap, page->index - node_offset, BITMAP_PAGE_PENDING);
		biपंचांगap->allclean = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक md_biपंचांगap_file_test_bit(काष्ठा biपंचांगap *biपंचांगap, sector_t block)
अणु
	अचिन्हित दीर्घ bit;
	काष्ठा page *page;
	व्योम *paddr;
	अचिन्हित दीर्घ chunk = block >> biपंचांगap->counts.chunkshअगरt;
	पूर्णांक set = 0;

	page = filemap_get_page(&biपंचांगap->storage, chunk);
	अगर (!page)
		वापस -EINVAL;
	bit = file_page_offset(&biपंचांगap->storage, chunk);
	paddr = kmap_atomic(page);
	अगर (test_bit(BITMAP_HOSTENDIAN, &biपंचांगap->flags))
		set = test_bit(bit, paddr);
	अन्यथा
		set = test_bit_le(bit, paddr);
	kunmap_atomic(paddr);
	वापस set;
पूर्ण


/* this माला_लो called when the md device is पढ़ोy to unplug its underlying
 * (slave) device queues -- beक्रमe we let any ग_लिखोs go करोwn, we need to
 * sync the dirty pages of the biपंचांगap file to disk */
व्योम md_biपंचांगap_unplug(काष्ठा biपंचांगap *biपंचांगap)
अणु
	अचिन्हित दीर्घ i;
	पूर्णांक dirty, need_ग_लिखो;
	पूर्णांक writing = 0;

	अगर (!biपंचांगap || !biपंचांगap->storage.filemap ||
	    test_bit(BITMAP_STALE, &biपंचांगap->flags))
		वापस;

	/* look at each page to see अगर there are any set bits that need to be
	 * flushed out to disk */
	क्रम (i = 0; i < biपंचांगap->storage.file_pages; i++) अणु
		dirty = test_and_clear_page_attr(biपंचांगap, i, BITMAP_PAGE_सूचीTY);
		need_ग_लिखो = test_and_clear_page_attr(biपंचांगap, i,
						      BITMAP_PAGE_NEEDWRITE);
		अगर (dirty || need_ग_लिखो) अणु
			अगर (!writing) अणु
				md_biपंचांगap_रुको_ग_लिखोs(biपंचांगap);
				अगर (biपंचांगap->mddev->queue)
					blk_add_trace_msg(biपंचांगap->mddev->queue,
							  "md bitmap_unplug");
			पूर्ण
			clear_page_attr(biपंचांगap, i, BITMAP_PAGE_PENDING);
			ग_लिखो_page(biपंचांगap, biपंचांगap->storage.filemap[i], 0);
			writing = 1;
		पूर्ण
	पूर्ण
	अगर (writing)
		md_biपंचांगap_रुको_ग_लिखोs(biपंचांगap);

	अगर (test_bit(BITMAP_WRITE_ERROR, &biपंचांगap->flags))
		md_biपंचांगap_file_kick(biपंचांगap);
पूर्ण
EXPORT_SYMBOL(md_biपंचांगap_unplug);

अटल व्योम md_biपंचांगap_set_memory_bits(काष्ठा biपंचांगap *biपंचांगap, sector_t offset, पूर्णांक needed);
/* * biपंचांगap_init_from_disk -- called at biपंचांगap_create समय to initialize
 * the in-memory biपंचांगap from the on-disk biपंचांगap -- also, sets up the
 * memory mapping of the biपंचांगap file
 * Special हालs:
 *   अगर there's no biपंचांगap file, or अगर the biपंचांगap file had been
 *   previously kicked from the array, we mark all the bits as
 *   1's in order to cause a full resync.
 *
 * We ignore all bits क्रम sectors that end earlier than 'start'.
 * This is used when पढ़ोing an out-of-date biपंचांगap...
 */
अटल पूर्णांक md_biपंचांगap_init_from_disk(काष्ठा biपंचांगap *biपंचांगap, sector_t start)
अणु
	अचिन्हित दीर्घ i, chunks, index, oldindex, bit, node_offset = 0;
	काष्ठा page *page = शून्य;
	अचिन्हित दीर्घ bit_cnt = 0;
	काष्ठा file *file;
	अचिन्हित दीर्घ offset;
	पूर्णांक outofdate;
	पूर्णांक ret = -ENOSPC;
	व्योम *paddr;
	काष्ठा biपंचांगap_storage *store = &biपंचांगap->storage;

	chunks = biपंचांगap->counts.chunks;
	file = store->file;

	अगर (!file && !biपंचांगap->mddev->biपंचांगap_info.offset) अणु
		/* No permanent biपंचांगap - fill with '1s'. */
		store->filemap = शून्य;
		store->file_pages = 0;
		क्रम (i = 0; i < chunks ; i++) अणु
			/* अगर the disk bit is set, set the memory bit */
			पूर्णांक needed = ((sector_t)(i+1) << (biपंचांगap->counts.chunkshअगरt)
				      >= start);
			md_biपंचांगap_set_memory_bits(biपंचांगap,
						  (sector_t)i << biपंचांगap->counts.chunkshअगरt,
						  needed);
		पूर्ण
		वापस 0;
	पूर्ण

	outofdate = test_bit(BITMAP_STALE, &biपंचांगap->flags);
	अगर (outofdate)
		pr_warn("%s: bitmap file is out of date, doing full recovery\n", bmname(biपंचांगap));

	अगर (file && i_size_पढ़ो(file->f_mapping->host) < store->bytes) अणु
		pr_warn("%s: bitmap file too short %lu < %lu\n",
			bmname(biपंचांगap),
			(अचिन्हित दीर्घ) i_size_पढ़ो(file->f_mapping->host),
			store->bytes);
		जाओ err;
	पूर्ण

	oldindex = ~0L;
	offset = 0;
	अगर (!biपंचांगap->mddev->biपंचांगap_info.बाह्यal)
		offset = माप(biपंचांगap_super_t);

	अगर (mddev_is_clustered(biपंचांगap->mddev))
		node_offset = biपंचांगap->cluster_slot * (DIV_ROUND_UP(store->bytes, PAGE_SIZE));

	क्रम (i = 0; i < chunks; i++) अणु
		पूर्णांक b;
		index = file_page_index(&biपंचांगap->storage, i);
		bit = file_page_offset(&biपंचांगap->storage, i);
		अगर (index != oldindex) अणु /* this is a new page, पढ़ो it in */
			पूर्णांक count;
			/* unmap the old page, we're करोne with it */
			अगर (index == store->file_pages-1)
				count = store->bytes - index * PAGE_SIZE;
			अन्यथा
				count = PAGE_SIZE;
			page = store->filemap[index];
			अगर (file)
				ret = पढ़ो_page(file, index, biपंचांगap,
						count, page);
			अन्यथा
				ret = पढ़ो_sb_page(
					biपंचांगap->mddev,
					biपंचांगap->mddev->biपंचांगap_info.offset,
					page,
					index + node_offset, count);

			अगर (ret)
				जाओ err;

			oldindex = index;

			अगर (outofdate) अणु
				/*
				 * अगर biपंचांगap is out of date, dirty the
				 * whole page and ग_लिखो it out
				 */
				paddr = kmap_atomic(page);
				स_रखो(paddr + offset, 0xff,
				       PAGE_SIZE - offset);
				kunmap_atomic(paddr);
				ग_लिखो_page(biपंचांगap, page, 1);

				ret = -EIO;
				अगर (test_bit(BITMAP_WRITE_ERROR,
					     &biपंचांगap->flags))
					जाओ err;
			पूर्ण
		पूर्ण
		paddr = kmap_atomic(page);
		अगर (test_bit(BITMAP_HOSTENDIAN, &biपंचांगap->flags))
			b = test_bit(bit, paddr);
		अन्यथा
			b = test_bit_le(bit, paddr);
		kunmap_atomic(paddr);
		अगर (b) अणु
			/* अगर the disk bit is set, set the memory bit */
			पूर्णांक needed = ((sector_t)(i+1) << biपंचांगap->counts.chunkshअगरt
				      >= start);
			md_biपंचांगap_set_memory_bits(biपंचांगap,
						  (sector_t)i << biपंचांगap->counts.chunkshअगरt,
						  needed);
			bit_cnt++;
		पूर्ण
		offset = 0;
	पूर्ण

	pr_debug("%s: bitmap initialized from disk: read %lu pages, set %lu of %lu bits\n",
		 bmname(biपंचांगap), store->file_pages,
		 bit_cnt, chunks);

	वापस 0;

 err:
	pr_warn("%s: bitmap initialisation failed: %d\n",
		bmname(biपंचांगap), ret);
	वापस ret;
पूर्ण

व्योम md_biपंचांगap_ग_लिखो_all(काष्ठा biपंचांगap *biपंचांगap)
अणु
	/* We करोn't actually ग_लिखो all biपंचांगap blocks here,
	 * just flag them as needing to be written
	 */
	पूर्णांक i;

	अगर (!biपंचांगap || !biपंचांगap->storage.filemap)
		वापस;
	अगर (biपंचांगap->storage.file)
		/* Only one copy, so nothing needed */
		वापस;

	क्रम (i = 0; i < biपंचांगap->storage.file_pages; i++)
		set_page_attr(biपंचांगap, i,
			      BITMAP_PAGE_NEEDWRITE);
	biपंचांगap->allclean = 0;
पूर्ण

अटल व्योम md_biपंचांगap_count_page(काष्ठा biपंचांगap_counts *biपंचांगap,
				 sector_t offset, पूर्णांक inc)
अणु
	sector_t chunk = offset >> biपंचांगap->chunkshअगरt;
	अचिन्हित दीर्घ page = chunk >> PAGE_COUNTER_SHIFT;
	biपंचांगap->bp[page].count += inc;
	md_biपंचांगap_checkमुक्त(biपंचांगap, page);
पूर्ण

अटल व्योम md_biपंचांगap_set_pending(काष्ठा biपंचांगap_counts *biपंचांगap, sector_t offset)
अणु
	sector_t chunk = offset >> biपंचांगap->chunkshअगरt;
	अचिन्हित दीर्घ page = chunk >> PAGE_COUNTER_SHIFT;
	काष्ठा biपंचांगap_page *bp = &biपंचांगap->bp[page];

	अगर (!bp->pending)
		bp->pending = 1;
पूर्ण

अटल biपंचांगap_counter_t *md_biपंचांगap_get_counter(काष्ठा biपंचांगap_counts *biपंचांगap,
					       sector_t offset, sector_t *blocks,
					       पूर्णांक create);

/*
 * biपंचांगap daemon -- periodically wakes up to clean bits and flush pages
 *			out to disk
 */

व्योम md_biपंचांगap_daemon_work(काष्ठा mddev *mddev)
अणु
	काष्ठा biपंचांगap *biपंचांगap;
	अचिन्हित दीर्घ j;
	अचिन्हित दीर्घ nextpage;
	sector_t blocks;
	काष्ठा biपंचांगap_counts *counts;

	/* Use a mutex to guard daemon_work against
	 * biपंचांगap_destroy.
	 */
	mutex_lock(&mddev->biपंचांगap_info.mutex);
	biपंचांगap = mddev->biपंचांगap;
	अगर (biपंचांगap == शून्य) अणु
		mutex_unlock(&mddev->biपंचांगap_info.mutex);
		वापस;
	पूर्ण
	अगर (समय_beक्रमe(jअगरfies, biपंचांगap->daemon_lastrun
			+ mddev->biपंचांगap_info.daemon_sleep))
		जाओ करोne;

	biपंचांगap->daemon_lastrun = jअगरfies;
	अगर (biपंचांगap->allclean) अणु
		mddev->thपढ़ो->समयout = MAX_SCHEDULE_TIMEOUT;
		जाओ करोne;
	पूर्ण
	biपंचांगap->allclean = 1;

	अगर (biपंचांगap->mddev->queue)
		blk_add_trace_msg(biपंचांगap->mddev->queue,
				  "md bitmap_daemon_work");

	/* Any file-page which is PENDING now needs to be written.
	 * So set NEEDWRITE now, then after we make any last-minute changes
	 * we will ग_लिखो it.
	 */
	क्रम (j = 0; j < biपंचांगap->storage.file_pages; j++)
		अगर (test_and_clear_page_attr(biपंचांगap, j,
					     BITMAP_PAGE_PENDING))
			set_page_attr(biपंचांगap, j,
				      BITMAP_PAGE_NEEDWRITE);

	अगर (biपंचांगap->need_sync &&
	    mddev->biपंचांगap_info.बाह्यal == 0) अणु
		/* Arrange क्रम superblock update as well as
		 * other changes */
		biपंचांगap_super_t *sb;
		biपंचांगap->need_sync = 0;
		अगर (biपंचांगap->storage.filemap) अणु
			sb = kmap_atomic(biपंचांगap->storage.sb_page);
			sb->events_cleared =
				cpu_to_le64(biपंचांगap->events_cleared);
			kunmap_atomic(sb);
			set_page_attr(biपंचांगap, 0,
				      BITMAP_PAGE_NEEDWRITE);
		पूर्ण
	पूर्ण
	/* Now look at the biपंचांगap counters and अगर any are '2' or '1',
	 * decrement and handle accordingly.
	 */
	counts = &biपंचांगap->counts;
	spin_lock_irq(&counts->lock);
	nextpage = 0;
	क्रम (j = 0; j < counts->chunks; j++) अणु
		biपंचांगap_counter_t *bmc;
		sector_t  block = (sector_t)j << counts->chunkshअगरt;

		अगर (j == nextpage) अणु
			nextpage += PAGE_COUNTER_RATIO;
			अगर (!counts->bp[j >> PAGE_COUNTER_SHIFT].pending) अणु
				j |= PAGE_COUNTER_MASK;
				जारी;
			पूर्ण
			counts->bp[j >> PAGE_COUNTER_SHIFT].pending = 0;
		पूर्ण

		bmc = md_biपंचांगap_get_counter(counts, block, &blocks, 0);
		अगर (!bmc) अणु
			j |= PAGE_COUNTER_MASK;
			जारी;
		पूर्ण
		अगर (*bmc == 1 && !biपंचांगap->need_sync) अणु
			/* We can clear the bit */
			*bmc = 0;
			md_biपंचांगap_count_page(counts, block, -1);
			md_biपंचांगap_file_clear_bit(biपंचांगap, block);
		पूर्ण अन्यथा अगर (*bmc && *bmc <= 2) अणु
			*bmc = 1;
			md_biपंचांगap_set_pending(counts, block);
			biपंचांगap->allclean = 0;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&counts->lock);

	md_biपंचांगap_रुको_ग_लिखोs(biपंचांगap);
	/* Now start ग_लिखोout on any page in NEEDWRITE that isn't सूचीTY.
	 * सूचीTY pages need to be written by biपंचांगap_unplug so it can रुको
	 * क्रम them.
	 * If we find any सूचीTY page we stop there and let biपंचांगap_unplug
	 * handle all the rest.  This is important in the हाल where
	 * the first blocking holds the superblock and it has been updated.
	 * We mustn't ग_लिखो any other blocks beक्रमe the superblock.
	 */
	क्रम (j = 0;
	     j < biपंचांगap->storage.file_pages
		     && !test_bit(BITMAP_STALE, &biपंचांगap->flags);
	     j++) अणु
		अगर (test_page_attr(biपंचांगap, j,
				   BITMAP_PAGE_सूचीTY))
			/* biपंचांगap_unplug will handle the rest */
			अवरोध;
		अगर (biपंचांगap->storage.filemap &&
		    test_and_clear_page_attr(biपंचांगap, j,
					     BITMAP_PAGE_NEEDWRITE)) अणु
			ग_लिखो_page(biपंचांगap, biपंचांगap->storage.filemap[j], 0);
		पूर्ण
	पूर्ण

 करोne:
	अगर (biपंचांगap->allclean == 0)
		mddev->thपढ़ो->समयout =
			mddev->biपंचांगap_info.daemon_sleep;
	mutex_unlock(&mddev->biपंचांगap_info.mutex);
पूर्ण

अटल biपंचांगap_counter_t *md_biपंचांगap_get_counter(काष्ठा biपंचांगap_counts *biपंचांगap,
					       sector_t offset, sector_t *blocks,
					       पूर्णांक create)
__releases(biपंचांगap->lock)
__acquires(biपंचांगap->lock)
अणु
	/* If 'create', we might release the lock and reclaim it.
	 * The lock must have been taken with पूर्णांकerrupts enabled.
	 * If !create, we करोn't release the lock.
	 */
	sector_t chunk = offset >> biपंचांगap->chunkshअगरt;
	अचिन्हित दीर्घ page = chunk >> PAGE_COUNTER_SHIFT;
	अचिन्हित दीर्घ pageoff = (chunk & PAGE_COUNTER_MASK) << COUNTER_BYTE_SHIFT;
	sector_t csize;
	पूर्णांक err;

	err = md_biपंचांगap_checkpage(biपंचांगap, page, create, 0);

	अगर (biपंचांगap->bp[page].hijacked ||
	    biपंचांगap->bp[page].map == शून्य)
		csize = ((sector_t)1) << (biपंचांगap->chunkshअगरt +
					  PAGE_COUNTER_SHIFT);
	अन्यथा
		csize = ((sector_t)1) << biपंचांगap->chunkshअगरt;
	*blocks = csize - (offset & (csize - 1));

	अगर (err < 0)
		वापस शून्य;

	/* now locked ... */

	अगर (biपंचांगap->bp[page].hijacked) अणु /* hijacked poपूर्णांकer */
		/* should we use the first or second counter field
		 * of the hijacked poपूर्णांकer? */
		पूर्णांक hi = (pageoff > PAGE_COUNTER_MASK);
		वापस  &((biपंचांगap_counter_t *)
			  &biपंचांगap->bp[page].map)[hi];
	पूर्ण अन्यथा /* page is allocated */
		वापस (biपंचांगap_counter_t *)
			&(biपंचांगap->bp[page].map[pageoff]);
पूर्ण

पूर्णांक md_biपंचांगap_startग_लिखो(काष्ठा biपंचांगap *biपंचांगap, sector_t offset, अचिन्हित दीर्घ sectors, पूर्णांक behind)
अणु
	अगर (!biपंचांगap)
		वापस 0;

	अगर (behind) अणु
		पूर्णांक bw;
		atomic_inc(&biपंचांगap->behind_ग_लिखोs);
		bw = atomic_पढ़ो(&biपंचांगap->behind_ग_लिखोs);
		अगर (bw > biपंचांगap->behind_ग_लिखोs_used)
			biपंचांगap->behind_ग_लिखोs_used = bw;

		pr_debug("inc write-behind count %d/%lu\n",
			 bw, biपंचांगap->mddev->biपंचांगap_info.max_ग_लिखो_behind);
	पूर्ण

	जबतक (sectors) अणु
		sector_t blocks;
		biपंचांगap_counter_t *bmc;

		spin_lock_irq(&biपंचांगap->counts.lock);
		bmc = md_biपंचांगap_get_counter(&biपंचांगap->counts, offset, &blocks, 1);
		अगर (!bmc) अणु
			spin_unlock_irq(&biपंचांगap->counts.lock);
			वापस 0;
		पूर्ण

		अगर (unlikely(COUNTER(*bmc) == COUNTER_MAX)) अणु
			DEFINE_WAIT(__रुको);
			/* note that it is safe to करो the prepare_to_रुको
			 * after the test as दीर्घ as we करो it beक्रमe dropping
			 * the spinlock.
			 */
			prepare_to_रुको(&biपंचांगap->overflow_रुको, &__रुको,
					TASK_UNINTERRUPTIBLE);
			spin_unlock_irq(&biपंचांगap->counts.lock);
			schedule();
			finish_रुको(&biपंचांगap->overflow_रुको, &__रुको);
			जारी;
		पूर्ण

		चयन (*bmc) अणु
		हाल 0:
			md_biपंचांगap_file_set_bit(biपंचांगap, offset);
			md_biपंचांगap_count_page(&biपंचांगap->counts, offset, 1);
			fallthrough;
		हाल 1:
			*bmc = 2;
		पूर्ण

		(*bmc)++;

		spin_unlock_irq(&biपंचांगap->counts.lock);

		offset += blocks;
		अगर (sectors > blocks)
			sectors -= blocks;
		अन्यथा
			sectors = 0;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(md_biपंचांगap_startग_लिखो);

व्योम md_biपंचांगap_endग_लिखो(काष्ठा biपंचांगap *biपंचांगap, sector_t offset,
			अचिन्हित दीर्घ sectors, पूर्णांक success, पूर्णांक behind)
अणु
	अगर (!biपंचांगap)
		वापस;
	अगर (behind) अणु
		अगर (atomic_dec_and_test(&biपंचांगap->behind_ग_लिखोs))
			wake_up(&biपंचांगap->behind_रुको);
		pr_debug("dec write-behind count %d/%lu\n",
			 atomic_पढ़ो(&biपंचांगap->behind_ग_लिखोs),
			 biपंचांगap->mddev->biपंचांगap_info.max_ग_लिखो_behind);
	पूर्ण

	जबतक (sectors) अणु
		sector_t blocks;
		अचिन्हित दीर्घ flags;
		biपंचांगap_counter_t *bmc;

		spin_lock_irqsave(&biपंचांगap->counts.lock, flags);
		bmc = md_biपंचांगap_get_counter(&biपंचांगap->counts, offset, &blocks, 0);
		अगर (!bmc) अणु
			spin_unlock_irqrestore(&biपंचांगap->counts.lock, flags);
			वापस;
		पूर्ण

		अगर (success && !biपंचांगap->mddev->degraded &&
		    biपंचांगap->events_cleared < biपंचांगap->mddev->events) अणु
			biपंचांगap->events_cleared = biपंचांगap->mddev->events;
			biपंचांगap->need_sync = 1;
			sysfs_notअगरy_dirent_safe(biपंचांगap->sysfs_can_clear);
		पूर्ण

		अगर (!success && !NEEDED(*bmc))
			*bmc |= NEEDED_MASK;

		अगर (COUNTER(*bmc) == COUNTER_MAX)
			wake_up(&biपंचांगap->overflow_रुको);

		(*bmc)--;
		अगर (*bmc <= 2) अणु
			md_biपंचांगap_set_pending(&biपंचांगap->counts, offset);
			biपंचांगap->allclean = 0;
		पूर्ण
		spin_unlock_irqrestore(&biपंचांगap->counts.lock, flags);
		offset += blocks;
		अगर (sectors > blocks)
			sectors -= blocks;
		अन्यथा
			sectors = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(md_biपंचांगap_endग_लिखो);

अटल पूर्णांक __biपंचांगap_start_sync(काष्ठा biपंचांगap *biपंचांगap, sector_t offset, sector_t *blocks,
			       पूर्णांक degraded)
अणु
	biपंचांगap_counter_t *bmc;
	पूर्णांक rv;
	अगर (biपंचांगap == शून्य) अणु/* FIXME or biपंचांगap set as 'failed' */
		*blocks = 1024;
		वापस 1; /* always resync अगर no biपंचांगap */
	पूर्ण
	spin_lock_irq(&biपंचांगap->counts.lock);
	bmc = md_biपंचांगap_get_counter(&biपंचांगap->counts, offset, blocks, 0);
	rv = 0;
	अगर (bmc) अणु
		/* locked */
		अगर (RESYNC(*bmc))
			rv = 1;
		अन्यथा अगर (NEEDED(*bmc)) अणु
			rv = 1;
			अगर (!degraded) अणु /* करोn't set/clear bits अगर degraded */
				*bmc |= RESYNC_MASK;
				*bmc &= ~NEEDED_MASK;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irq(&biपंचांगap->counts.lock);
	वापस rv;
पूर्ण

पूर्णांक md_biपंचांगap_start_sync(काष्ठा biपंचांगap *biपंचांगap, sector_t offset, sector_t *blocks,
			 पूर्णांक degraded)
अणु
	/* biपंचांगap_start_sync must always report on multiples of whole
	 * pages, otherwise resync (which is very PAGE_SIZE based) will
	 * get confused.
	 * So call __biपंचांगap_start_sync repeatedly (अगर needed) until
	 * At least PAGE_SIZE>>9 blocks are covered.
	 * Return the 'or' of the result.
	 */
	पूर्णांक rv = 0;
	sector_t blocks1;

	*blocks = 0;
	जबतक (*blocks < (PAGE_SIZE>>9)) अणु
		rv |= __biपंचांगap_start_sync(biपंचांगap, offset,
					  &blocks1, degraded);
		offset += blocks1;
		*blocks += blocks1;
	पूर्ण
	वापस rv;
पूर्ण
EXPORT_SYMBOL(md_biपंचांगap_start_sync);

व्योम md_biपंचांगap_end_sync(काष्ठा biपंचांगap *biपंचांगap, sector_t offset, sector_t *blocks, पूर्णांक पातed)
अणु
	biपंचांगap_counter_t *bmc;
	अचिन्हित दीर्घ flags;

	अगर (biपंचांगap == शून्य) अणु
		*blocks = 1024;
		वापस;
	पूर्ण
	spin_lock_irqsave(&biपंचांगap->counts.lock, flags);
	bmc = md_biपंचांगap_get_counter(&biपंचांगap->counts, offset, blocks, 0);
	अगर (bmc == शून्य)
		जाओ unlock;
	/* locked */
	अगर (RESYNC(*bmc)) अणु
		*bmc &= ~RESYNC_MASK;

		अगर (!NEEDED(*bmc) && पातed)
			*bmc |= NEEDED_MASK;
		अन्यथा अणु
			अगर (*bmc <= 2) अणु
				md_biपंचांगap_set_pending(&biपंचांगap->counts, offset);
				biपंचांगap->allclean = 0;
			पूर्ण
		पूर्ण
	पूर्ण
 unlock:
	spin_unlock_irqrestore(&biपंचांगap->counts.lock, flags);
पूर्ण
EXPORT_SYMBOL(md_biपंचांगap_end_sync);

व्योम md_biपंचांगap_बंद_sync(काष्ठा biपंचांगap *biपंचांगap)
अणु
	/* Sync has finished, and any biपंचांगap chunks that weren't synced
	 * properly have been पातed.  It reमुख्यs to us to clear the
	 * RESYNC bit wherever it is still on
	 */
	sector_t sector = 0;
	sector_t blocks;
	अगर (!biपंचांगap)
		वापस;
	जबतक (sector < biपंचांगap->mddev->resync_max_sectors) अणु
		md_biपंचांगap_end_sync(biपंचांगap, sector, &blocks, 0);
		sector += blocks;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(md_biपंचांगap_बंद_sync);

व्योम md_biपंचांगap_cond_end_sync(काष्ठा biपंचांगap *biपंचांगap, sector_t sector, bool क्रमce)
अणु
	sector_t s = 0;
	sector_t blocks;

	अगर (!biपंचांगap)
		वापस;
	अगर (sector == 0) अणु
		biपंचांगap->last_end_sync = jअगरfies;
		वापस;
	पूर्ण
	अगर (!क्रमce && समय_beक्रमe(jअगरfies, (biपंचांगap->last_end_sync
				  + biपंचांगap->mddev->biपंचांगap_info.daemon_sleep)))
		वापस;
	रुको_event(biपंचांगap->mddev->recovery_रुको,
		   atomic_पढ़ो(&biपंचांगap->mddev->recovery_active) == 0);

	biपंचांगap->mddev->curr_resync_completed = sector;
	set_bit(MD_SB_CHANGE_CLEAN, &biपंचांगap->mddev->sb_flags);
	sector &= ~((1ULL << biपंचांगap->counts.chunkshअगरt) - 1);
	s = 0;
	जबतक (s < sector && s < biपंचांगap->mddev->resync_max_sectors) अणु
		md_biपंचांगap_end_sync(biपंचांगap, s, &blocks, 0);
		s += blocks;
	पूर्ण
	biपंचांगap->last_end_sync = jअगरfies;
	sysfs_notअगरy_dirent_safe(biपंचांगap->mddev->sysfs_completed);
पूर्ण
EXPORT_SYMBOL(md_biपंचांगap_cond_end_sync);

व्योम md_biपंचांगap_sync_with_cluster(काष्ठा mddev *mddev,
			      sector_t old_lo, sector_t old_hi,
			      sector_t new_lo, sector_t new_hi)
अणु
	काष्ठा biपंचांगap *biपंचांगap = mddev->biपंचांगap;
	sector_t sector, blocks = 0;

	क्रम (sector = old_lo; sector < new_lo; ) अणु
		md_biपंचांगap_end_sync(biपंचांगap, sector, &blocks, 0);
		sector += blocks;
	पूर्ण
	WARN((blocks > new_lo) && old_lo, "alignment is not correct for lo\n");

	क्रम (sector = old_hi; sector < new_hi; ) अणु
		md_biपंचांगap_start_sync(biपंचांगap, sector, &blocks, 0);
		sector += blocks;
	पूर्ण
	WARN((blocks > new_hi) && old_hi, "alignment is not correct for hi\n");
पूर्ण
EXPORT_SYMBOL(md_biपंचांगap_sync_with_cluster);

अटल व्योम md_biपंचांगap_set_memory_bits(काष्ठा biपंचांगap *biपंचांगap, sector_t offset, पूर्णांक needed)
अणु
	/* For each chunk covered by any of these sectors, set the
	 * counter to 2 and possibly set resync_needed.  They should all
	 * be 0 at this poपूर्णांक
	 */

	sector_t secs;
	biपंचांगap_counter_t *bmc;
	spin_lock_irq(&biपंचांगap->counts.lock);
	bmc = md_biपंचांगap_get_counter(&biपंचांगap->counts, offset, &secs, 1);
	अगर (!bmc) अणु
		spin_unlock_irq(&biपंचांगap->counts.lock);
		वापस;
	पूर्ण
	अगर (!*bmc) अणु
		*bmc = 2;
		md_biपंचांगap_count_page(&biपंचांगap->counts, offset, 1);
		md_biपंचांगap_set_pending(&biपंचांगap->counts, offset);
		biपंचांगap->allclean = 0;
	पूर्ण
	अगर (needed)
		*bmc |= NEEDED_MASK;
	spin_unlock_irq(&biपंचांगap->counts.lock);
पूर्ण

/* dirty the memory and file bits क्रम biपंचांगap chunks "s" to "e" */
व्योम md_biपंचांगap_dirty_bits(काष्ठा biपंचांगap *biपंचांगap, अचिन्हित दीर्घ s, अचिन्हित दीर्घ e)
अणु
	अचिन्हित दीर्घ chunk;

	क्रम (chunk = s; chunk <= e; chunk++) अणु
		sector_t sec = (sector_t)chunk << biपंचांगap->counts.chunkshअगरt;
		md_biपंचांगap_set_memory_bits(biपंचांगap, sec, 1);
		md_biपंचांगap_file_set_bit(biपंचांगap, sec);
		अगर (sec < biपंचांगap->mddev->recovery_cp)
			/* We are निश्चितing that the array is dirty,
			 * so move the recovery_cp address back so
			 * that it is obvious that it is dirty
			 */
			biपंचांगap->mddev->recovery_cp = sec;
	पूर्ण
पूर्ण

/*
 * flush out any pending updates
 */
व्योम md_biपंचांगap_flush(काष्ठा mddev *mddev)
अणु
	काष्ठा biपंचांगap *biपंचांगap = mddev->biपंचांगap;
	दीर्घ sleep;

	अगर (!biपंचांगap) /* there was no biपंचांगap */
		वापस;

	/* run the daemon_work three समय to ensure everything is flushed
	 * that can be
	 */
	sleep = mddev->biपंचांगap_info.daemon_sleep * 2;
	biपंचांगap->daemon_lastrun -= sleep;
	md_biपंचांगap_daemon_work(mddev);
	biपंचांगap->daemon_lastrun -= sleep;
	md_biपंचांगap_daemon_work(mddev);
	biपंचांगap->daemon_lastrun -= sleep;
	md_biपंचांगap_daemon_work(mddev);
	अगर (mddev->biपंचांगap_info.बाह्यal)
		md_super_रुको(mddev);
	md_biपंचांगap_update_sb(biपंचांगap);
पूर्ण

/*
 * मुक्त memory that was allocated
 */
व्योम md_biपंचांगap_मुक्त(काष्ठा biपंचांगap *biपंचांगap)
अणु
	अचिन्हित दीर्घ k, pages;
	काष्ठा biपंचांगap_page *bp;

	अगर (!biपंचांगap) /* there was no biपंचांगap */
		वापस;

	अगर (biपंचांगap->sysfs_can_clear)
		sysfs_put(biपंचांगap->sysfs_can_clear);

	अगर (mddev_is_clustered(biपंचांगap->mddev) && biपंचांगap->mddev->cluster_info &&
		biपंचांगap->cluster_slot == md_cluster_ops->slot_number(biपंचांगap->mddev))
		md_cluster_stop(biपंचांगap->mddev);

	/* Shouldn't be needed - but just in हाल.... */
	रुको_event(biपंचांगap->ग_लिखो_रुको,
		   atomic_पढ़ो(&biपंचांगap->pending_ग_लिखोs) == 0);

	/* release the biपंचांगap file  */
	md_biपंचांगap_file_unmap(&biपंचांगap->storage);

	bp = biपंचांगap->counts.bp;
	pages = biपंचांगap->counts.pages;

	/* मुक्त all allocated memory */

	अगर (bp) /* deallocate the page memory */
		क्रम (k = 0; k < pages; k++)
			अगर (bp[k].map && !bp[k].hijacked)
				kमुक्त(bp[k].map);
	kमुक्त(bp);
	kमुक्त(biपंचांगap);
पूर्ण
EXPORT_SYMBOL(md_biपंचांगap_मुक्त);

व्योम md_biपंचांगap_रुको_behind_ग_लिखोs(काष्ठा mddev *mddev)
अणु
	काष्ठा biपंचांगap *biपंचांगap = mddev->biपंचांगap;

	/* रुको क्रम behind ग_लिखोs to complete */
	अगर (biपंचांगap && atomic_पढ़ो(&biपंचांगap->behind_ग_लिखोs) > 0) अणु
		pr_debug("md:%s: behind writes in progress - waiting to stop.\n",
			 mdname(mddev));
		/* need to kick something here to make sure I/O goes? */
		रुको_event(biपंचांगap->behind_रुको,
			   atomic_पढ़ो(&biपंचांगap->behind_ग_लिखोs) == 0);
	पूर्ण
पूर्ण

व्योम md_biपंचांगap_destroy(काष्ठा mddev *mddev)
अणु
	काष्ठा biपंचांगap *biपंचांगap = mddev->biपंचांगap;

	अगर (!biपंचांगap) /* there was no biपंचांगap */
		वापस;

	md_biपंचांगap_रुको_behind_ग_लिखोs(mddev);
	अगर (!mddev->serialize_policy)
		mddev_destroy_serial_pool(mddev, शून्य, true);

	mutex_lock(&mddev->biपंचांगap_info.mutex);
	spin_lock(&mddev->lock);
	mddev->biपंचांगap = शून्य; /* disconnect from the md device */
	spin_unlock(&mddev->lock);
	mutex_unlock(&mddev->biपंचांगap_info.mutex);
	अगर (mddev->thपढ़ो)
		mddev->thपढ़ो->समयout = MAX_SCHEDULE_TIMEOUT;

	md_biपंचांगap_मुक्त(biपंचांगap);
पूर्ण

/*
 * initialize the biपंचांगap काष्ठाure
 * अगर this वापसs an error, biपंचांगap_destroy must be called to करो clean up
 * once mddev->biपंचांगap is set
 */
काष्ठा biपंचांगap *md_biपंचांगap_create(काष्ठा mddev *mddev, पूर्णांक slot)
अणु
	काष्ठा biपंचांगap *biपंचांगap;
	sector_t blocks = mddev->resync_max_sectors;
	काष्ठा file *file = mddev->biपंचांगap_info.file;
	पूर्णांक err;
	काष्ठा kernfs_node *bm = शून्य;

	BUILD_BUG_ON(माप(biपंचांगap_super_t) != 256);

	BUG_ON(file && mddev->biपंचांगap_info.offset);

	अगर (test_bit(MD_HAS_JOURNAL, &mddev->flags)) अणु
		pr_notice("md/raid:%s: array with journal cannot have bitmap\n",
			  mdname(mddev));
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	biपंचांगap = kzalloc(माप(*biपंचांगap), GFP_KERNEL);
	अगर (!biपंचांगap)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&biपंचांगap->counts.lock);
	atomic_set(&biपंचांगap->pending_ग_लिखोs, 0);
	init_रुकोqueue_head(&biपंचांगap->ग_लिखो_रुको);
	init_रुकोqueue_head(&biपंचांगap->overflow_रुको);
	init_रुकोqueue_head(&biपंचांगap->behind_रुको);

	biपंचांगap->mddev = mddev;
	biपंचांगap->cluster_slot = slot;

	अगर (mddev->kobj.sd)
		bm = sysfs_get_dirent(mddev->kobj.sd, "bitmap");
	अगर (bm) अणु
		biपंचांगap->sysfs_can_clear = sysfs_get_dirent(bm, "can_clear");
		sysfs_put(bm);
	पूर्ण अन्यथा
		biपंचांगap->sysfs_can_clear = शून्य;

	biपंचांगap->storage.file = file;
	अगर (file) अणु
		get_file(file);
		/* As future accesses to this file will use bmap,
		 * and bypass the page cache, we must sync the file
		 * first.
		 */
		vfs_fsync(file, 1);
	पूर्ण
	/* पढ़ो superblock from biपंचांगap file (this sets mddev->biपंचांगap_info.chunksize) */
	अगर (!mddev->biपंचांगap_info.बाह्यal) अणु
		/*
		 * If 'MD_ARRAY_FIRST_USE' is set, then device-mapper is
		 * inकाष्ठाing us to create a new on-disk biपंचांगap instance.
		 */
		अगर (test_and_clear_bit(MD_ARRAY_FIRST_USE, &mddev->flags))
			err = md_biपंचांगap_new_disk_sb(biपंचांगap);
		अन्यथा
			err = md_biपंचांगap_पढ़ो_sb(biपंचांगap);
	पूर्ण अन्यथा अणु
		err = 0;
		अगर (mddev->biपंचांगap_info.chunksize == 0 ||
		    mddev->biपंचांगap_info.daemon_sleep == 0)
			/* chunksize and समय_base need to be
			 * set first. */
			err = -EINVAL;
	पूर्ण
	अगर (err)
		जाओ error;

	biपंचांगap->daemon_lastrun = jअगरfies;
	err = md_biपंचांगap_resize(biपंचांगap, blocks, mddev->biपंचांगap_info.chunksize, 1);
	अगर (err)
		जाओ error;

	pr_debug("created bitmap (%lu pages) for device %s\n",
		 biपंचांगap->counts.pages, bmname(biपंचांगap));

	err = test_bit(BITMAP_WRITE_ERROR, &biपंचांगap->flags) ? -EIO : 0;
	अगर (err)
		जाओ error;

	वापस biपंचांगap;
 error:
	md_biपंचांगap_मुक्त(biपंचांगap);
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक md_biपंचांगap_load(काष्ठा mddev *mddev)
अणु
	पूर्णांक err = 0;
	sector_t start = 0;
	sector_t sector = 0;
	काष्ठा biपंचांगap *biपंचांगap = mddev->biपंचांगap;
	काष्ठा md_rdev *rdev;

	अगर (!biपंचांगap)
		जाओ out;

	rdev_क्रम_each(rdev, mddev)
		mddev_create_serial_pool(mddev, rdev, true);

	अगर (mddev_is_clustered(mddev))
		md_cluster_ops->load_biपंचांगaps(mddev, mddev->biपंचांगap_info.nodes);

	/* Clear out old biपंचांगap info first:  Either there is none, or we
	 * are resuming after someone अन्यथा has possibly changed things,
	 * so we should क्रमget old cached info.
	 * All chunks should be clean, but some might need_sync.
	 */
	जबतक (sector < mddev->resync_max_sectors) अणु
		sector_t blocks;
		md_biपंचांगap_start_sync(biपंचांगap, sector, &blocks, 0);
		sector += blocks;
	पूर्ण
	md_biपंचांगap_बंद_sync(biपंचांगap);

	अगर (mddev->degraded == 0
	    || biपंचांगap->events_cleared == mddev->events)
		/* no need to keep dirty bits to optimise a
		 * re-add of a missing device */
		start = mddev->recovery_cp;

	mutex_lock(&mddev->biपंचांगap_info.mutex);
	err = md_biपंचांगap_init_from_disk(biपंचांगap, start);
	mutex_unlock(&mddev->biपंचांगap_info.mutex);

	अगर (err)
		जाओ out;
	clear_bit(BITMAP_STALE, &biपंचांगap->flags);

	/* Kick recovery in हाल any bits were set */
	set_bit(MD_RECOVERY_NEEDED, &biपंचांगap->mddev->recovery);

	mddev->thपढ़ो->समयout = mddev->biपंचांगap_info.daemon_sleep;
	md_wakeup_thपढ़ो(mddev->thपढ़ो);

	md_biपंचांगap_update_sb(biपंचांगap);

	अगर (test_bit(BITMAP_WRITE_ERROR, &biपंचांगap->flags))
		err = -EIO;
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(md_biपंचांगap_load);

/* caller need to मुक्त वापसed biपंचांगap with md_biपंचांगap_मुक्त() */
काष्ठा biपंचांगap *get_biपंचांगap_from_slot(काष्ठा mddev *mddev, पूर्णांक slot)
अणु
	पूर्णांक rv = 0;
	काष्ठा biपंचांगap *biपंचांगap;

	biपंचांगap = md_biपंचांगap_create(mddev, slot);
	अगर (IS_ERR(biपंचांगap)) अणु
		rv = PTR_ERR(biपंचांगap);
		वापस ERR_PTR(rv);
	पूर्ण

	rv = md_biपंचांगap_init_from_disk(biपंचांगap, 0);
	अगर (rv) अणु
		md_biपंचांगap_मुक्त(biपंचांगap);
		वापस ERR_PTR(rv);
	पूर्ण

	वापस biपंचांगap;
पूर्ण
EXPORT_SYMBOL(get_biपंचांगap_from_slot);

/* Loads the biपंचांगap associated with slot and copies the resync inक्रमmation
 * to our biपंचांगap
 */
पूर्णांक md_biपंचांगap_copy_from_slot(काष्ठा mddev *mddev, पूर्णांक slot,
		sector_t *low, sector_t *high, bool clear_bits)
अणु
	पूर्णांक rv = 0, i, j;
	sector_t block, lo = 0, hi = 0;
	काष्ठा biपंचांगap_counts *counts;
	काष्ठा biपंचांगap *biपंचांगap;

	biपंचांगap = get_biपंचांगap_from_slot(mddev, slot);
	अगर (IS_ERR(biपंचांगap)) अणु
		pr_err("%s can't get bitmap from slot %d\n", __func__, slot);
		वापस -1;
	पूर्ण

	counts = &biपंचांगap->counts;
	क्रम (j = 0; j < counts->chunks; j++) अणु
		block = (sector_t)j << counts->chunkshअगरt;
		अगर (md_biपंचांगap_file_test_bit(biपंचांगap, block)) अणु
			अगर (!lo)
				lo = block;
			hi = block;
			md_biपंचांगap_file_clear_bit(biपंचांगap, block);
			md_biपंचांगap_set_memory_bits(mddev->biपंचांगap, block, 1);
			md_biपंचांगap_file_set_bit(mddev->biपंचांगap, block);
		पूर्ण
	पूर्ण

	अगर (clear_bits) अणु
		md_biपंचांगap_update_sb(biपंचांगap);
		/* BITMAP_PAGE_PENDING is set, but biपंचांगap_unplug needs
		 * BITMAP_PAGE_सूचीTY or _NEEDWRITE to ग_लिखो ... */
		क्रम (i = 0; i < biपंचांगap->storage.file_pages; i++)
			अगर (test_page_attr(biपंचांगap, i, BITMAP_PAGE_PENDING))
				set_page_attr(biपंचांगap, i, BITMAP_PAGE_NEEDWRITE);
		md_biपंचांगap_unplug(biपंचांगap);
	पूर्ण
	md_biपंचांगap_unplug(mddev->biपंचांगap);
	*low = lo;
	*high = hi;
	md_biपंचांगap_मुक्त(biपंचांगap);

	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(md_biपंचांगap_copy_from_slot);


व्योम md_biपंचांगap_status(काष्ठा seq_file *seq, काष्ठा biपंचांगap *biपंचांगap)
अणु
	अचिन्हित दीर्घ chunk_kb;
	काष्ठा biपंचांगap_counts *counts;

	अगर (!biपंचांगap)
		वापस;

	counts = &biपंचांगap->counts;

	chunk_kb = biपंचांगap->mddev->biपंचांगap_info.chunksize >> 10;
	seq_म_लिखो(seq, "bitmap: %lu/%lu pages [%luKB], "
		   "%lu%s chunk",
		   counts->pages - counts->missing_pages,
		   counts->pages,
		   (counts->pages - counts->missing_pages)
		   << (PAGE_SHIFT - 10),
		   chunk_kb ? chunk_kb : biपंचांगap->mddev->biपंचांगap_info.chunksize,
		   chunk_kb ? "KB" : "B");
	अगर (biपंचांगap->storage.file) अणु
		seq_म_लिखो(seq, ", file: ");
		seq_file_path(seq, biपंचांगap->storage.file, " \t\n");
	पूर्ण

	seq_म_लिखो(seq, "\n");
पूर्ण

पूर्णांक md_biपंचांगap_resize(काष्ठा biपंचांगap *biपंचांगap, sector_t blocks,
		  पूर्णांक chunksize, पूर्णांक init)
अणु
	/* If chunk_size is 0, choose an appropriate chunk size.
	 * Then possibly allocate new storage space.
	 * Then quiesce, copy bits, replace biपंचांगap, and re-start
	 *
	 * This function is called both to set up the initial biपंचांगap
	 * and to resize the biपंचांगap जबतक the array is active.
	 * If this happens as a result of the array being resized,
	 * chunksize will be zero, and we need to choose a suitable
	 * chunksize, otherwise we use what we are given.
	 */
	काष्ठा biपंचांगap_storage store;
	काष्ठा biपंचांगap_counts old_counts;
	अचिन्हित दीर्घ chunks;
	sector_t block;
	sector_t old_blocks, new_blocks;
	पूर्णांक chunkshअगरt;
	पूर्णांक ret = 0;
	दीर्घ pages;
	काष्ठा biपंचांगap_page *new_bp;

	अगर (biपंचांगap->storage.file && !init) अणु
		pr_info("md: cannot resize file-based bitmap\n");
		वापस -EINVAL;
	पूर्ण

	अगर (chunksize == 0) अणु
		/* If there is enough space, leave the chunk size unchanged,
		 * अन्यथा increase by factor of two until there is enough space.
		 */
		दीर्घ bytes;
		दीर्घ space = biपंचांगap->mddev->biपंचांगap_info.space;

		अगर (space == 0) अणु
			/* We करोn't know how much space there is, so limit
			 * to current size - in sectors.
			 */
			bytes = DIV_ROUND_UP(biपंचांगap->counts.chunks, 8);
			अगर (!biपंचांगap->mddev->biपंचांगap_info.बाह्यal)
				bytes += माप(biपंचांगap_super_t);
			space = DIV_ROUND_UP(bytes, 512);
			biपंचांगap->mddev->biपंचांगap_info.space = space;
		पूर्ण
		chunkshअगरt = biपंचांगap->counts.chunkshअगरt;
		chunkshअगरt--;
		करो अणु
			/* 'chunkshift' is shअगरt from block size to chunk size */
			chunkshअगरt++;
			chunks = DIV_ROUND_UP_SECTOR_T(blocks, 1 << chunkshअगरt);
			bytes = DIV_ROUND_UP(chunks, 8);
			अगर (!biपंचांगap->mddev->biपंचांगap_info.बाह्यal)
				bytes += माप(biपंचांगap_super_t);
		पूर्ण जबतक (bytes > (space << 9));
	पूर्ण अन्यथा
		chunkshअगरt = ffz(~chunksize) - BITMAP_BLOCK_SHIFT;

	chunks = DIV_ROUND_UP_SECTOR_T(blocks, 1 << chunkshअगरt);
	स_रखो(&store, 0, माप(store));
	अगर (biपंचांगap->mddev->biपंचांगap_info.offset || biपंचांगap->mddev->biपंचांगap_info.file)
		ret = md_biपंचांगap_storage_alloc(&store, chunks,
					      !biपंचांगap->mddev->biपंचांगap_info.बाह्यal,
					      mddev_is_clustered(biपंचांगap->mddev)
					      ? biपंचांगap->cluster_slot : 0);
	अगर (ret) अणु
		md_biपंचांगap_file_unmap(&store);
		जाओ err;
	पूर्ण

	pages = DIV_ROUND_UP(chunks, PAGE_COUNTER_RATIO);

	new_bp = kसुस्मृति(pages, माप(*new_bp), GFP_KERNEL);
	ret = -ENOMEM;
	अगर (!new_bp) अणु
		md_biपंचांगap_file_unmap(&store);
		जाओ err;
	पूर्ण

	अगर (!init)
		biपंचांगap->mddev->pers->quiesce(biपंचांगap->mddev, 1);

	store.file = biपंचांगap->storage.file;
	biपंचांगap->storage.file = शून्य;

	अगर (store.sb_page && biपंचांगap->storage.sb_page)
		स_नकल(page_address(store.sb_page),
		       page_address(biपंचांगap->storage.sb_page),
		       माप(biपंचांगap_super_t));
	spin_lock_irq(&biपंचांगap->counts.lock);
	md_biपंचांगap_file_unmap(&biपंचांगap->storage);
	biपंचांगap->storage = store;

	old_counts = biपंचांगap->counts;
	biपंचांगap->counts.bp = new_bp;
	biपंचांगap->counts.pages = pages;
	biपंचांगap->counts.missing_pages = pages;
	biपंचांगap->counts.chunkshअगरt = chunkshअगरt;
	biपंचांगap->counts.chunks = chunks;
	biपंचांगap->mddev->biपंचांगap_info.chunksize = 1 << (chunkshअगरt +
						     BITMAP_BLOCK_SHIFT);

	blocks = min(old_counts.chunks << old_counts.chunkshअगरt,
		     chunks << chunkshअगरt);

	/* For cluster raid, need to pre-allocate biपंचांगap */
	अगर (mddev_is_clustered(biपंचांगap->mddev)) अणु
		अचिन्हित दीर्घ page;
		क्रम (page = 0; page < pages; page++) अणु
			ret = md_biपंचांगap_checkpage(&biपंचांगap->counts, page, 1, 1);
			अगर (ret) अणु
				अचिन्हित दीर्घ k;

				/* deallocate the page memory */
				क्रम (k = 0; k < page; k++) अणु
					kमुक्त(new_bp[k].map);
				पूर्ण
				kमुक्त(new_bp);

				/* restore some fields from old_counts */
				biपंचांगap->counts.bp = old_counts.bp;
				biपंचांगap->counts.pages = old_counts.pages;
				biपंचांगap->counts.missing_pages = old_counts.pages;
				biपंचांगap->counts.chunkshअगरt = old_counts.chunkshअगरt;
				biपंचांगap->counts.chunks = old_counts.chunks;
				biपंचांगap->mddev->biपंचांगap_info.chunksize = 1 << (old_counts.chunkshअगरt +
									     BITMAP_BLOCK_SHIFT);
				blocks = old_counts.chunks << old_counts.chunkshअगरt;
				pr_warn("Could not pre-allocate in-memory bitmap for cluster raid\n");
				अवरोध;
			पूर्ण अन्यथा
				biपंचांगap->counts.bp[page].count += 1;
		पूर्ण
	पूर्ण

	क्रम (block = 0; block < blocks; ) अणु
		biपंचांगap_counter_t *bmc_old, *bmc_new;
		पूर्णांक set;

		bmc_old = md_biपंचांगap_get_counter(&old_counts, block, &old_blocks, 0);
		set = bmc_old && NEEDED(*bmc_old);

		अगर (set) अणु
			bmc_new = md_biपंचांगap_get_counter(&biपंचांगap->counts, block, &new_blocks, 1);
			अगर (*bmc_new == 0) अणु
				/* need to set on-disk bits too. */
				sector_t end = block + new_blocks;
				sector_t start = block >> chunkshअगरt;
				start <<= chunkshअगरt;
				जबतक (start < end) अणु
					md_biपंचांगap_file_set_bit(biपंचांगap, block);
					start += 1 << chunkshअगरt;
				पूर्ण
				*bmc_new = 2;
				md_biपंचांगap_count_page(&biपंचांगap->counts, block, 1);
				md_biपंचांगap_set_pending(&biपंचांगap->counts, block);
			पूर्ण
			*bmc_new |= NEEDED_MASK;
			अगर (new_blocks < old_blocks)
				old_blocks = new_blocks;
		पूर्ण
		block += old_blocks;
	पूर्ण

	अगर (biपंचांगap->counts.bp != old_counts.bp) अणु
		अचिन्हित दीर्घ k;
		क्रम (k = 0; k < old_counts.pages; k++)
			अगर (!old_counts.bp[k].hijacked)
				kमुक्त(old_counts.bp[k].map);
		kमुक्त(old_counts.bp);
	पूर्ण

	अगर (!init) अणु
		पूर्णांक i;
		जबतक (block < (chunks << chunkshअगरt)) अणु
			biपंचांगap_counter_t *bmc;
			bmc = md_biपंचांगap_get_counter(&biपंचांगap->counts, block, &new_blocks, 1);
			अगर (bmc) अणु
				/* new space.  It needs to be resynced, so
				 * we set NEEDED_MASK.
				 */
				अगर (*bmc == 0) अणु
					*bmc = NEEDED_MASK | 2;
					md_biपंचांगap_count_page(&biपंचांगap->counts, block, 1);
					md_biपंचांगap_set_pending(&biपंचांगap->counts, block);
				पूर्ण
			पूर्ण
			block += new_blocks;
		पूर्ण
		क्रम (i = 0; i < biपंचांगap->storage.file_pages; i++)
			set_page_attr(biपंचांगap, i, BITMAP_PAGE_सूचीTY);
	पूर्ण
	spin_unlock_irq(&biपंचांगap->counts.lock);

	अगर (!init) अणु
		md_biपंचांगap_unplug(biपंचांगap);
		biपंचांगap->mddev->pers->quiesce(biपंचांगap->mddev, 0);
	पूर्ण
	ret = 0;
err:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(md_biपंचांगap_resize);

अटल sमाप_प्रकार
location_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	sमाप_प्रकार len;
	अगर (mddev->biपंचांगap_info.file)
		len = प्र_लिखो(page, "file");
	अन्यथा अगर (mddev->biपंचांगap_info.offset)
		len = प्र_लिखो(page, "%+lld", (दीर्घ दीर्घ)mddev->biपंचांगap_info.offset);
	अन्यथा
		len = प्र_लिखो(page, "none");
	len += प्र_लिखो(page+len, "\n");
	वापस len;
पूर्ण

अटल sमाप_प्रकार
location_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक rv;

	rv = mddev_lock(mddev);
	अगर (rv)
		वापस rv;
	अगर (mddev->pers) अणु
		अगर (!mddev->pers->quiesce) अणु
			rv = -EBUSY;
			जाओ out;
		पूर्ण
		अगर (mddev->recovery || mddev->sync_thपढ़ो) अणु
			rv = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (mddev->biपंचांगap || mddev->biपंचांगap_info.file ||
	    mddev->biपंचांगap_info.offset) अणु
		/* biपंचांगap alपढ़ोy configured.  Only option is to clear it */
		अगर (म_भेदन(buf, "none", 4) != 0) अणु
			rv = -EBUSY;
			जाओ out;
		पूर्ण
		अगर (mddev->pers) अणु
			mddev_suspend(mddev);
			md_biपंचांगap_destroy(mddev);
			mddev_resume(mddev);
		पूर्ण
		mddev->biपंचांगap_info.offset = 0;
		अगर (mddev->biपंचांगap_info.file) अणु
			काष्ठा file *f = mddev->biपंचांगap_info.file;
			mddev->biपंचांगap_info.file = शून्य;
			fput(f);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* No biपंचांगap, OK to set a location */
		दीर्घ दीर्घ offset;
		अगर (म_भेदन(buf, "none", 4) == 0)
			/* nothing to be करोne */;
		अन्यथा अगर (म_भेदन(buf, "file:", 5) == 0) अणु
			/* Not supported yet */
			rv = -EINVAL;
			जाओ out;
		पूर्ण अन्यथा अणु
			अगर (buf[0] == '+')
				rv = kम_से_दीर्घl(buf+1, 10, &offset);
			अन्यथा
				rv = kम_से_दीर्घl(buf, 10, &offset);
			अगर (rv)
				जाओ out;
			अगर (offset == 0) अणु
				rv = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (mddev->biपंचांगap_info.बाह्यal == 0 &&
			    mddev->major_version == 0 &&
			    offset != mddev->biपंचांगap_info.शेष_offset) अणु
				rv = -EINVAL;
				जाओ out;
			पूर्ण
			mddev->biपंचांगap_info.offset = offset;
			अगर (mddev->pers) अणु
				काष्ठा biपंचांगap *biपंचांगap;
				biपंचांगap = md_biपंचांगap_create(mddev, -1);
				mddev_suspend(mddev);
				अगर (IS_ERR(biपंचांगap))
					rv = PTR_ERR(biपंचांगap);
				अन्यथा अणु
					mddev->biपंचांगap = biपंचांगap;
					rv = md_biपंचांगap_load(mddev);
					अगर (rv)
						mddev->biपंचांगap_info.offset = 0;
				पूर्ण
				अगर (rv) अणु
					md_biपंचांगap_destroy(mddev);
					mddev_resume(mddev);
					जाओ out;
				पूर्ण
				mddev_resume(mddev);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!mddev->बाह्यal) अणु
		/* Ensure new biपंचांगap info is stored in
		 * metadata promptly.
		 */
		set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
	पूर्ण
	rv = 0;
out:
	mddev_unlock(mddev);
	अगर (rv)
		वापस rv;
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry biपंचांगap_location =
__ATTR(location, S_IRUGO|S_IWUSR, location_show, location_store);

/* 'bitmap/space' is the space available at 'location' क्रम the
 * biपंचांगap.  This allows the kernel to know when it is safe to
 * resize the biपंचांगap to match a resized array.
 */
अटल sमाप_प्रकार
space_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%lu\n", mddev->biपंचांगap_info.space);
पूर्ण

अटल sमाप_प्रकार
space_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ sectors;
	पूर्णांक rv;

	rv = kम_से_अदीर्घ(buf, 10, &sectors);
	अगर (rv)
		वापस rv;

	अगर (sectors == 0)
		वापस -EINVAL;

	अगर (mddev->biपंचांगap &&
	    sectors < (mddev->biपंचांगap->storage.bytes + 511) >> 9)
		वापस -EFBIG; /* Biपंचांगap is too big क्रम this small space */

	/* could make sure it isn't too big, but that isn't really
	 * needed - user-space should be careful.
	 */
	mddev->biपंचांगap_info.space = sectors;
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry biपंचांगap_space =
__ATTR(space, S_IRUGO|S_IWUSR, space_show, space_store);

अटल sमाप_प्रकार
समयout_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	sमाप_प्रकार len;
	अचिन्हित दीर्घ secs = mddev->biपंचांगap_info.daemon_sleep / HZ;
	अचिन्हित दीर्घ jअगरs = mddev->biपंचांगap_info.daemon_sleep % HZ;

	len = प्र_लिखो(page, "%lu", secs);
	अगर (jअगरs)
		len += प्र_लिखो(page+len, ".%03u", jअगरfies_to_msecs(jअगरs));
	len += प्र_लिखो(page+len, "\n");
	वापस len;
पूर्ण

अटल sमाप_प्रकार
समयout_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	/* समयout can be set at any समय */
	अचिन्हित दीर्घ समयout;
	पूर्णांक rv = strict_म_से_अदीर्घ_scaled(buf, &समयout, 4);
	अगर (rv)
		वापस rv;

	/* just to make sure we करोn't overflow... */
	अगर (समयout >= दीर्घ_उच्च / HZ)
		वापस -EINVAL;

	समयout = समयout * HZ / 10000;

	अगर (समयout >= MAX_SCHEDULE_TIMEOUT)
		समयout = MAX_SCHEDULE_TIMEOUT-1;
	अगर (समयout < 1)
		समयout = 1;
	mddev->biपंचांगap_info.daemon_sleep = समयout;
	अगर (mddev->thपढ़ो) अणु
		/* अगर thपढ़ो->समयout is MAX_SCHEDULE_TIMEOUT, then
		 * the biपंचांगap is all clean and we करोn't need to
		 * adjust the समयout right now
		 */
		अगर (mddev->thपढ़ो->समयout < MAX_SCHEDULE_TIMEOUT) अणु
			mddev->thपढ़ो->समयout = समयout;
			md_wakeup_thपढ़ो(mddev->thपढ़ो);
		पूर्ण
	पूर्ण
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry biपंचांगap_समयout =
__ATTR(समय_base, S_IRUGO|S_IWUSR, समयout_show, समयout_store);

अटल sमाप_प्रकार
backlog_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%lu\n", mddev->biपंचांगap_info.max_ग_लिखो_behind);
पूर्ण

अटल sमाप_प्रकार
backlog_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ backlog;
	अचिन्हित दीर्घ old_mwb = mddev->biपंचांगap_info.max_ग_लिखो_behind;
	पूर्णांक rv = kम_से_अदीर्घ(buf, 10, &backlog);
	अगर (rv)
		वापस rv;
	अगर (backlog > COUNTER_MAX)
		वापस -EINVAL;
	mddev->biपंचांगap_info.max_ग_लिखो_behind = backlog;
	अगर (!backlog && mddev->serial_info_pool) अणु
		/* serial_info_pool is not needed अगर backlog is zero */
		अगर (!mddev->serialize_policy)
			mddev_destroy_serial_pool(mddev, शून्य, false);
	पूर्ण अन्यथा अगर (backlog && !mddev->serial_info_pool) अणु
		/* serial_info_pool is needed since backlog is not zero */
		काष्ठा md_rdev *rdev;

		rdev_क्रम_each(rdev, mddev)
			mddev_create_serial_pool(mddev, rdev, false);
	पूर्ण
	अगर (old_mwb != backlog)
		md_biपंचांगap_update_sb(mddev->biपंचांगap);
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry biपंचांगap_backlog =
__ATTR(backlog, S_IRUGO|S_IWUSR, backlog_show, backlog_store);

अटल sमाप_प्रकार
chunksize_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%lu\n", mddev->biपंचांगap_info.chunksize);
पूर्ण

अटल sमाप_प्रकार
chunksize_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	/* Can only be changed when no biपंचांगap is active */
	पूर्णांक rv;
	अचिन्हित दीर्घ csize;
	अगर (mddev->biपंचांगap)
		वापस -EBUSY;
	rv = kम_से_अदीर्घ(buf, 10, &csize);
	अगर (rv)
		वापस rv;
	अगर (csize < 512 ||
	    !is_घातer_of_2(csize))
		वापस -EINVAL;
	mddev->biपंचांगap_info.chunksize = csize;
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry biपंचांगap_chunksize =
__ATTR(chunksize, S_IRUGO|S_IWUSR, chunksize_show, chunksize_store);

अटल sमाप_प्रकार metadata_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	अगर (mddev_is_clustered(mddev))
		वापस प्र_लिखो(page, "clustered\n");
	वापस प्र_लिखो(page, "%s\n", (mddev->biपंचांगap_info.बाह्यal
				      ? "external" : "internal"));
पूर्ण

अटल sमाप_प्रकार metadata_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अगर (mddev->biपंचांगap ||
	    mddev->biपंचांगap_info.file ||
	    mddev->biपंचांगap_info.offset)
		वापस -EBUSY;
	अगर (म_भेदन(buf, "external", 8) == 0)
		mddev->biपंचांगap_info.बाह्यal = 1;
	अन्यथा अगर ((म_भेदन(buf, "internal", 8) == 0) ||
			(म_भेदन(buf, "clustered", 9) == 0))
		mddev->biपंचांगap_info.बाह्यal = 0;
	अन्यथा
		वापस -EINVAL;
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry biपंचांगap_metadata =
__ATTR(metadata, S_IRUGO|S_IWUSR, metadata_show, metadata_store);

अटल sमाप_प्रकार can_clear_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	पूर्णांक len;
	spin_lock(&mddev->lock);
	अगर (mddev->biपंचांगap)
		len = प्र_लिखो(page, "%s\n", (mddev->biपंचांगap->need_sync ?
					     "false" : "true"));
	अन्यथा
		len = प्र_लिखो(page, "\n");
	spin_unlock(&mddev->lock);
	वापस len;
पूर्ण

अटल sमाप_प्रकार can_clear_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अगर (mddev->biपंचांगap == शून्य)
		वापस -ENOENT;
	अगर (म_भेदन(buf, "false", 5) == 0)
		mddev->biपंचांगap->need_sync = 1;
	अन्यथा अगर (म_भेदन(buf, "true", 4) == 0) अणु
		अगर (mddev->degraded)
			वापस -EBUSY;
		mddev->biपंचांगap->need_sync = 0;
	पूर्ण अन्यथा
		वापस -EINVAL;
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry biपंचांगap_can_clear =
__ATTR(can_clear, S_IRUGO|S_IWUSR, can_clear_show, can_clear_store);

अटल sमाप_प्रकार
behind_ग_लिखोs_used_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	sमाप_प्रकार ret;
	spin_lock(&mddev->lock);
	अगर (mddev->biपंचांगap == शून्य)
		ret = प्र_लिखो(page, "0\n");
	अन्यथा
		ret = प्र_लिखो(page, "%lu\n",
			      mddev->biपंचांगap->behind_ग_लिखोs_used);
	spin_unlock(&mddev->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
behind_ग_लिखोs_used_reset(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अगर (mddev->biपंचांगap)
		mddev->biपंचांगap->behind_ग_लिखोs_used = 0;
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry max_backlog_used =
__ATTR(max_backlog_used, S_IRUGO | S_IWUSR,
       behind_ग_लिखोs_used_show, behind_ग_लिखोs_used_reset);

अटल काष्ठा attribute *md_biपंचांगap_attrs[] = अणु
	&biपंचांगap_location.attr,
	&biपंचांगap_space.attr,
	&biपंचांगap_समयout.attr,
	&biपंचांगap_backlog.attr,
	&biपंचांगap_chunksize.attr,
	&biपंचांगap_metadata.attr,
	&biपंचांगap_can_clear.attr,
	&max_backlog_used.attr,
	शून्य
पूर्ण;
काष्ठा attribute_group md_biपंचांगap_group = अणु
	.name = "bitmap",
	.attrs = md_biपंचांगap_attrs,
पूर्ण;
