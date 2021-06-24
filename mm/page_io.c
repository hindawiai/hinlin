<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/mm/page_io.c
 *
 *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *
 *  Swap reorganised 29.12.95, 
 *  Asynchronous swapping added 30.12.95. Stephen Tweedie
 *  Removed race in async swapping. 14.4.1996. Bruno Haible
 *  Add swap of shared pages through the page cache. 20.2.1998. Stephen Tweedie
 *  Always use brw_page, lअगरe becomes simpler. 12 May 1998 Eric Biederman
 */

#समावेश <linux/mm.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/gfp.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/bपन.स>
#समावेश <linux/swapops.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/frontswap.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/psi.h>
#समावेश <linux/uपन.स>
#समावेश <linux/sched/task.h>

व्योम end_swap_bio_ग_लिखो(काष्ठा bio *bio)
अणु
	काष्ठा page *page = bio_first_page_all(bio);

	अगर (bio->bi_status) अणु
		SetPageError(page);
		/*
		 * We failed to ग_लिखो the page out to swap-space.
		 * Re-dirty the page in order to aव्योम it being reclaimed.
		 * Also prपूर्णांक a dire warning that things will go BAD (पंचांग)
		 * very quickly.
		 *
		 * Also clear PG_reclaim to aव्योम rotate_reclaimable_page()
		 */
		set_page_dirty(page);
		pr_alert_ratelimited("Write-error on swap-device (%u:%u:%llu)\n",
				     MAJOR(bio_dev(bio)), MINOR(bio_dev(bio)),
				     (अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector);
		ClearPageReclaim(page);
	पूर्ण
	end_page_ग_लिखोback(page);
	bio_put(bio);
पूर्ण

अटल व्योम swap_slot_मुक्त_notअगरy(काष्ठा page *page)
अणु
	काष्ठा swap_info_काष्ठा *sis;
	काष्ठा gendisk *disk;
	swp_entry_t entry;

	/*
	 * There is no guarantee that the page is in swap cache - the software
	 * suspend code (at least) uses end_swap_bio_पढ़ो() against a non-
	 * swapcache page.  So we must check PG_swapcache beक्रमe proceeding with
	 * this optimization.
	 */
	अगर (unlikely(!PageSwapCache(page)))
		वापस;

	sis = page_swap_info(page);
	अगर (data_race(!(sis->flags & SWP_BLKDEV)))
		वापस;

	/*
	 * The swap subप्रणाली perक्रमms lazy swap slot मुक्तing,
	 * expecting that the page will be swapped out again.
	 * So we can aव्योम an unnecessary ग_लिखो अगर the page
	 * isn't redirtied.
	 * This is good क्रम real swap storage because we can
	 * reduce unnecessary I/O and enhance wear-leveling
	 * अगर an SSD is used as the as swap device.
	 * But अगर in-memory swap device (eg zram) is used,
	 * this causes a duplicated copy between uncompressed
	 * data in VM-owned memory and compressed data in
	 * zram-owned memory.  So let's मुक्त zram-owned memory
	 * and make the VM-owned decompressed page *dirty*,
	 * so the page should be swapped out somewhere again अगर
	 * we again wish to reclaim it.
	 */
	disk = sis->bdev->bd_disk;
	entry.val = page_निजी(page);
	अगर (disk->fops->swap_slot_मुक्त_notअगरy && __swap_count(entry) == 1) अणु
		अचिन्हित दीर्घ offset;

		offset = swp_offset(entry);

		SetPageDirty(page);
		disk->fops->swap_slot_मुक्त_notअगरy(sis->bdev,
				offset);
	पूर्ण
पूर्ण

अटल व्योम end_swap_bio_पढ़ो(काष्ठा bio *bio)
अणु
	काष्ठा page *page = bio_first_page_all(bio);
	काष्ठा task_काष्ठा *रुकोer = bio->bi_निजी;

	अगर (bio->bi_status) अणु
		SetPageError(page);
		ClearPageUptodate(page);
		pr_alert_ratelimited("Read-error on swap-device (%u:%u:%llu)\n",
				     MAJOR(bio_dev(bio)), MINOR(bio_dev(bio)),
				     (अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector);
		जाओ out;
	पूर्ण

	SetPageUptodate(page);
	swap_slot_मुक्त_notअगरy(page);
out:
	unlock_page(page);
	WRITE_ONCE(bio->bi_निजी, शून्य);
	bio_put(bio);
	अगर (रुकोer) अणु
		blk_wake_io_task(रुकोer);
		put_task_काष्ठा(रुकोer);
	पूर्ण
पूर्ण

पूर्णांक generic_swapfile_activate(काष्ठा swap_info_काष्ठा *sis,
				काष्ठा file *swap_file,
				sector_t *span)
अणु
	काष्ठा address_space *mapping = swap_file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	अचिन्हित blocks_per_page;
	अचिन्हित दीर्घ page_no;
	अचिन्हित blkbits;
	sector_t probe_block;
	sector_t last_block;
	sector_t lowest_block = -1;
	sector_t highest_block = 0;
	पूर्णांक nr_extents = 0;
	पूर्णांक ret;

	blkbits = inode->i_blkbits;
	blocks_per_page = PAGE_SIZE >> blkbits;

	/*
	 * Map all the blocks पूर्णांकo the extent tree.  This code करोesn't try
	 * to be very smart.
	 */
	probe_block = 0;
	page_no = 0;
	last_block = i_size_पढ़ो(inode) >> blkbits;
	जबतक ((probe_block + blocks_per_page) <= last_block &&
			page_no < sis->max) अणु
		अचिन्हित block_in_page;
		sector_t first_block;

		cond_resched();

		first_block = probe_block;
		ret = bmap(inode, &first_block);
		अगर (ret || !first_block)
			जाओ bad_bmap;

		/*
		 * It must be PAGE_SIZE aligned on-disk
		 */
		अगर (first_block & (blocks_per_page - 1)) अणु
			probe_block++;
			जाओ reprobe;
		पूर्ण

		क्रम (block_in_page = 1; block_in_page < blocks_per_page;
					block_in_page++) अणु
			sector_t block;

			block = probe_block + block_in_page;
			ret = bmap(inode, &block);
			अगर (ret || !block)
				जाओ bad_bmap;

			अगर (block != first_block + block_in_page) अणु
				/* Discontiguity */
				probe_block++;
				जाओ reprobe;
			पूर्ण
		पूर्ण

		first_block >>= (PAGE_SHIFT - blkbits);
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
	pr_err("swapon: swapfile has holes\n");
	ret = -EINVAL;
	जाओ out;
पूर्ण

/*
 * We may have stale swap cache pages in memory: notice
 * them here and get rid of the unnecessary final ग_लिखो.
 */
पूर्णांक swap_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret = 0;

	अगर (try_to_मुक्त_swap(page)) अणु
		unlock_page(page);
		जाओ out;
	पूर्ण
	/*
	 * Arch code may have to preserve more data than just the page
	 * contents, e.g. memory tags.
	 */
	ret = arch_prepare_to_swap(page);
	अगर (ret) अणु
		set_page_dirty(page);
		unlock_page(page);
		जाओ out;
	पूर्ण
	अगर (frontswap_store(page) == 0) अणु
		set_page_ग_लिखोback(page);
		unlock_page(page);
		end_page_ग_लिखोback(page);
		जाओ out;
	पूर्ण
	ret = __swap_ग_लिखोpage(page, wbc, end_swap_bio_ग_लिखो);
out:
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम count_swpout_vm_event(काष्ठा page *page)
अणु
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	अगर (unlikely(PageTransHuge(page)))
		count_vm_event(THP_SWPOUT);
#पूर्ण_अगर
	count_vm_events(PSWPOUT, thp_nr_pages(page));
पूर्ण

#अगर defined(CONFIG_MEMCG) && defined(CONFIG_BLK_CGROUP)
अटल व्योम bio_associate_blkg_from_page(काष्ठा bio *bio, काष्ठा page *page)
अणु
	काष्ठा cgroup_subsys_state *css;
	काष्ठा mem_cgroup *memcg;

	memcg = page_memcg(page);
	अगर (!memcg)
		वापस;

	rcu_पढ़ो_lock();
	css = cgroup_e_css(memcg->css.cgroup, &io_cgrp_subsys);
	bio_associate_blkg_from_css(bio, css);
	rcu_पढ़ो_unlock();
पूर्ण
#अन्यथा
#घोषणा bio_associate_blkg_from_page(bio, page)		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_MEMCG && CONFIG_BLK_CGROUP */

पूर्णांक __swap_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc,
		bio_end_io_t end_ग_लिखो_func)
अणु
	काष्ठा bio *bio;
	पूर्णांक ret;
	काष्ठा swap_info_काष्ठा *sis = page_swap_info(page);

	VM_BUG_ON_PAGE(!PageSwapCache(page), page);
	अगर (data_race(sis->flags & SWP_FS_OPS)) अणु
		काष्ठा kiocb kiocb;
		काष्ठा file *swap_file = sis->swap_file;
		काष्ठा address_space *mapping = swap_file->f_mapping;
		काष्ठा bio_vec bv = अणु
			.bv_page = page,
			.bv_len  = PAGE_SIZE,
			.bv_offset = 0
		पूर्ण;
		काष्ठा iov_iter from;

		iov_iter_bvec(&from, WRITE, &bv, 1, PAGE_SIZE);
		init_sync_kiocb(&kiocb, swap_file);
		kiocb.ki_pos = page_file_offset(page);

		set_page_ग_लिखोback(page);
		unlock_page(page);
		ret = mapping->a_ops->direct_IO(&kiocb, &from);
		अगर (ret == PAGE_SIZE) अणु
			count_vm_event(PSWPOUT);
			ret = 0;
		पूर्ण अन्यथा अणु
			/*
			 * In the हाल of swap-over-nfs, this can be a
			 * temporary failure अगर the प्रणाली has limited
			 * memory क्रम allocating transmit buffers.
			 * Mark the page dirty and aव्योम
			 * rotate_reclaimable_page but rate-limit the
			 * messages but करो not flag PageError like
			 * the normal direct-to-bio हाल as it could
			 * be temporary.
			 */
			set_page_dirty(page);
			ClearPageReclaim(page);
			pr_err_ratelimited("Write error on dio swapfile (%llu)\n",
					   page_file_offset(page));
		पूर्ण
		end_page_ग_लिखोback(page);
		वापस ret;
	पूर्ण

	ret = bdev_ग_लिखो_page(sis->bdev, swap_page_sector(page), page, wbc);
	अगर (!ret) अणु
		count_swpout_vm_event(page);
		वापस 0;
	पूर्ण

	bio = bio_alloc(GFP_NOIO, 1);
	bio_set_dev(bio, sis->bdev);
	bio->bi_iter.bi_sector = swap_page_sector(page);
	bio->bi_opf = REQ_OP_WRITE | REQ_SWAP | wbc_to_ग_लिखो_flags(wbc);
	bio->bi_end_io = end_ग_लिखो_func;
	bio_add_page(bio, page, thp_size(page), 0);

	bio_associate_blkg_from_page(bio, page);
	count_swpout_vm_event(page);
	set_page_ग_लिखोback(page);
	unlock_page(page);
	submit_bio(bio);

	वापस 0;
पूर्ण

पूर्णांक swap_पढ़ोpage(काष्ठा page *page, bool synchronous)
अणु
	काष्ठा bio *bio;
	पूर्णांक ret = 0;
	काष्ठा swap_info_काष्ठा *sis = page_swap_info(page);
	blk_qc_t qc;
	काष्ठा gendisk *disk;
	अचिन्हित दीर्घ pflags;

	VM_BUG_ON_PAGE(!PageSwapCache(page) && !synchronous, page);
	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(PageUptodate(page), page);

	/*
	 * Count submission समय as memory stall. When the device is congested,
	 * or the submitting cgroup IO-throttled, submission can be a
	 * signअगरicant part of overall IO समय.
	 */
	psi_memstall_enter(&pflags);

	अगर (frontswap_load(page) == 0) अणु
		SetPageUptodate(page);
		unlock_page(page);
		जाओ out;
	पूर्ण

	अगर (data_race(sis->flags & SWP_FS_OPS)) अणु
		काष्ठा file *swap_file = sis->swap_file;
		काष्ठा address_space *mapping = swap_file->f_mapping;

		ret = mapping->a_ops->पढ़ोpage(swap_file, page);
		अगर (!ret)
			count_vm_event(PSWPIN);
		जाओ out;
	पूर्ण

	अगर (sis->flags & SWP_SYNCHRONOUS_IO) अणु
		ret = bdev_पढ़ो_page(sis->bdev, swap_page_sector(page), page);
		अगर (!ret) अणु
			अगर (trylock_page(page)) अणु
				swap_slot_मुक्त_notअगरy(page);
				unlock_page(page);
			पूर्ण

			count_vm_event(PSWPIN);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = 0;
	bio = bio_alloc(GFP_KERNEL, 1);
	bio_set_dev(bio, sis->bdev);
	bio->bi_opf = REQ_OP_READ;
	bio->bi_iter.bi_sector = swap_page_sector(page);
	bio->bi_end_io = end_swap_bio_पढ़ो;
	bio_add_page(bio, page, thp_size(page), 0);

	disk = bio->bi_bdev->bd_disk;
	/*
	 * Keep this task valid during swap पढ़ोpage because the oom समाप्तer may
	 * attempt to access it in the page fault retry समय check.
	 */
	अगर (synchronous) अणु
		bio->bi_opf |= REQ_HIPRI;
		get_task_काष्ठा(current);
		bio->bi_निजी = current;
	पूर्ण
	count_vm_event(PSWPIN);
	bio_get(bio);
	qc = submit_bio(bio);
	जबतक (synchronous) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		अगर (!READ_ONCE(bio->bi_निजी))
			अवरोध;

		अगर (!blk_poll(disk->queue, qc, true))
			blk_io_schedule();
	पूर्ण
	__set_current_state(TASK_RUNNING);
	bio_put(bio);

out:
	psi_memstall_leave(&pflags);
	वापस ret;
पूर्ण

पूर्णांक swap_set_page_dirty(काष्ठा page *page)
अणु
	काष्ठा swap_info_काष्ठा *sis = page_swap_info(page);

	अगर (data_race(sis->flags & SWP_FS_OPS)) अणु
		काष्ठा address_space *mapping = sis->swap_file->f_mapping;

		VM_BUG_ON_PAGE(!PageSwapCache(page), page);
		वापस mapping->a_ops->set_page_dirty(page);
	पूर्ण अन्यथा अणु
		वापस __set_page_dirty_no_ग_लिखोback(page);
	पूर्ण
पूर्ण
