<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Ram backed block device driver.
 *
 * Copyright (C) 2007 Nick Piggin
 * Copyright (C) 2007 Novell Inc.
 *
 * Parts derived from drivers/block/rd.c, and drivers/block/loop.c, copyright
 * of their respective owners.
 */

#समावेश <linux/init.h>
#समावेश <linux/initrd.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/major.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mutex.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/debugfs.h>

#समावेश <linux/uaccess.h>

#घोषणा PAGE_SECTORS_SHIFT	(PAGE_SHIFT - SECTOR_SHIFT)
#घोषणा PAGE_SECTORS		(1 << PAGE_SECTORS_SHIFT)

/*
 * Each block ramdisk device has a radix_tree brd_pages of pages that stores
 * the pages containing the block device's contents. A brd page's ->index is
 * its offset in PAGE_SIZE units. This is similar to, but in no way connected
 * with, the kernel's pagecache or buffer cache (which sit above our block
 * device).
 */
काष्ठा brd_device अणु
	पूर्णांक		brd_number;

	काष्ठा request_queue	*brd_queue;
	काष्ठा gendisk		*brd_disk;
	काष्ठा list_head	brd_list;

	/*
	 * Backing store of pages and lock to protect it. This is the contents
	 * of the block device.
	 */
	spinlock_t		brd_lock;
	काष्ठा radix_tree_root	brd_pages;
	u64			brd_nr_pages;
पूर्ण;

/*
 * Look up and वापस a brd's page क्रम a given sector.
 */
अटल काष्ठा page *brd_lookup_page(काष्ठा brd_device *brd, sector_t sector)
अणु
	pgoff_t idx;
	काष्ठा page *page;

	/*
	 * The page lअगरeसमय is रक्षित by the fact that we have खोलोed the
	 * device node -- brd pages will never be deleted under us, so we
	 * करोn't need any further locking or refcounting.
	 *
	 * This is strictly true क्रम the radix-tree nodes as well (ie. we
	 * करोn't actually need the rcu_पढ़ो_lock()), however that is not a
	 * करोcumented feature of the radix-tree API so it is better to be
	 * safe here (we करोn't have total exclusion from radix tree updates
	 * here, only deletes).
	 */
	rcu_पढ़ो_lock();
	idx = sector >> PAGE_SECTORS_SHIFT; /* sector to page index */
	page = radix_tree_lookup(&brd->brd_pages, idx);
	rcu_पढ़ो_unlock();

	BUG_ON(page && page->index != idx);

	वापस page;
पूर्ण

/*
 * Look up and वापस a brd's page क्रम a given sector.
 * If one करोes not exist, allocate an empty page, and insert that. Then
 * वापस it.
 */
अटल काष्ठा page *brd_insert_page(काष्ठा brd_device *brd, sector_t sector)
अणु
	pgoff_t idx;
	काष्ठा page *page;
	gfp_t gfp_flags;

	page = brd_lookup_page(brd, sector);
	अगर (page)
		वापस page;

	/*
	 * Must use NOIO because we करोn't want to recurse back पूर्णांकo the
	 * block or fileप्रणाली layers from page reclaim.
	 */
	gfp_flags = GFP_NOIO | __GFP_ZERO | __GFP_HIGHMEM;
	page = alloc_page(gfp_flags);
	अगर (!page)
		वापस शून्य;

	अगर (radix_tree_preload(GFP_NOIO)) अणु
		__मुक्त_page(page);
		वापस शून्य;
	पूर्ण

	spin_lock(&brd->brd_lock);
	idx = sector >> PAGE_SECTORS_SHIFT;
	page->index = idx;
	अगर (radix_tree_insert(&brd->brd_pages, idx, page)) अणु
		__मुक्त_page(page);
		page = radix_tree_lookup(&brd->brd_pages, idx);
		BUG_ON(!page);
		BUG_ON(page->index != idx);
	पूर्ण अन्यथा अणु
		brd->brd_nr_pages++;
	पूर्ण
	spin_unlock(&brd->brd_lock);

	radix_tree_preload_end();

	वापस page;
पूर्ण

/*
 * Free all backing store pages and radix tree. This must only be called when
 * there are no other users of the device.
 */
#घोषणा FREE_BATCH 16
अटल व्योम brd_मुक्त_pages(काष्ठा brd_device *brd)
अणु
	अचिन्हित दीर्घ pos = 0;
	काष्ठा page *pages[FREE_BATCH];
	पूर्णांक nr_pages;

	करो अणु
		पूर्णांक i;

		nr_pages = radix_tree_gang_lookup(&brd->brd_pages,
				(व्योम **)pages, pos, FREE_BATCH);

		क्रम (i = 0; i < nr_pages; i++) अणु
			व्योम *ret;

			BUG_ON(pages[i]->index < pos);
			pos = pages[i]->index;
			ret = radix_tree_delete(&brd->brd_pages, pos);
			BUG_ON(!ret || ret != pages[i]);
			__मुक्त_page(pages[i]);
		पूर्ण

		pos++;

		/*
		 * It takes 3.4 seconds to हटाओ 80GiB ramdisk.
		 * So, we need cond_resched to aव्योम stalling the CPU.
		 */
		cond_resched();

		/*
		 * This assumes radix_tree_gang_lookup always वापसs as
		 * many pages as possible. If the radix-tree code changes,
		 * so will this have to.
		 */
	पूर्ण जबतक (nr_pages == FREE_BATCH);
पूर्ण

/*
 * copy_to_brd_setup must be called beक्रमe copy_to_brd. It may sleep.
 */
अटल पूर्णांक copy_to_brd_setup(काष्ठा brd_device *brd, sector_t sector, माप_प्रकार n)
अणु
	अचिन्हित पूर्णांक offset = (sector & (PAGE_SECTORS-1)) << SECTOR_SHIFT;
	माप_प्रकार copy;

	copy = min_t(माप_प्रकार, n, PAGE_SIZE - offset);
	अगर (!brd_insert_page(brd, sector))
		वापस -ENOSPC;
	अगर (copy < n) अणु
		sector += copy >> SECTOR_SHIFT;
		अगर (!brd_insert_page(brd, sector))
			वापस -ENOSPC;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Copy n bytes from src to the brd starting at sector. Does not sleep.
 */
अटल व्योम copy_to_brd(काष्ठा brd_device *brd, स्थिर व्योम *src,
			sector_t sector, माप_प्रकार n)
अणु
	काष्ठा page *page;
	व्योम *dst;
	अचिन्हित पूर्णांक offset = (sector & (PAGE_SECTORS-1)) << SECTOR_SHIFT;
	माप_प्रकार copy;

	copy = min_t(माप_प्रकार, n, PAGE_SIZE - offset);
	page = brd_lookup_page(brd, sector);
	BUG_ON(!page);

	dst = kmap_atomic(page);
	स_नकल(dst + offset, src, copy);
	kunmap_atomic(dst);

	अगर (copy < n) अणु
		src += copy;
		sector += copy >> SECTOR_SHIFT;
		copy = n - copy;
		page = brd_lookup_page(brd, sector);
		BUG_ON(!page);

		dst = kmap_atomic(page);
		स_नकल(dst, src, copy);
		kunmap_atomic(dst);
	पूर्ण
पूर्ण

/*
 * Copy n bytes to dst from the brd starting at sector. Does not sleep.
 */
अटल व्योम copy_from_brd(व्योम *dst, काष्ठा brd_device *brd,
			sector_t sector, माप_प्रकार n)
अणु
	काष्ठा page *page;
	व्योम *src;
	अचिन्हित पूर्णांक offset = (sector & (PAGE_SECTORS-1)) << SECTOR_SHIFT;
	माप_प्रकार copy;

	copy = min_t(माप_प्रकार, n, PAGE_SIZE - offset);
	page = brd_lookup_page(brd, sector);
	अगर (page) अणु
		src = kmap_atomic(page);
		स_नकल(dst, src + offset, copy);
		kunmap_atomic(src);
	पूर्ण अन्यथा
		स_रखो(dst, 0, copy);

	अगर (copy < n) अणु
		dst += copy;
		sector += copy >> SECTOR_SHIFT;
		copy = n - copy;
		page = brd_lookup_page(brd, sector);
		अगर (page) अणु
			src = kmap_atomic(page);
			स_नकल(dst, src, copy);
			kunmap_atomic(src);
		पूर्ण अन्यथा
			स_रखो(dst, 0, copy);
	पूर्ण
पूर्ण

/*
 * Process a single bvec of a bio.
 */
अटल पूर्णांक brd_करो_bvec(काष्ठा brd_device *brd, काष्ठा page *page,
			अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off, अचिन्हित पूर्णांक op,
			sector_t sector)
अणु
	व्योम *mem;
	पूर्णांक err = 0;

	अगर (op_is_ग_लिखो(op)) अणु
		err = copy_to_brd_setup(brd, sector, len);
		अगर (err)
			जाओ out;
	पूर्ण

	mem = kmap_atomic(page);
	अगर (!op_is_ग_लिखो(op)) अणु
		copy_from_brd(mem + off, brd, sector, len);
		flush_dcache_page(page);
	पूर्ण अन्यथा अणु
		flush_dcache_page(page);
		copy_to_brd(brd, mem + off, sector, len);
	पूर्ण
	kunmap_atomic(mem);

out:
	वापस err;
पूर्ण

अटल blk_qc_t brd_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा brd_device *brd = bio->bi_bdev->bd_disk->निजी_data;
	sector_t sector = bio->bi_iter.bi_sector;
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;

	bio_क्रम_each_segment(bvec, bio, iter) अणु
		अचिन्हित पूर्णांक len = bvec.bv_len;
		पूर्णांक err;

		/* Don't support un-aligned buffer */
		WARN_ON_ONCE((bvec.bv_offset & (SECTOR_SIZE - 1)) ||
				(len & (SECTOR_SIZE - 1)));

		err = brd_करो_bvec(brd, bvec.bv_page, len, bvec.bv_offset,
				  bio_op(bio), sector);
		अगर (err)
			जाओ io_error;
		sector += len >> SECTOR_SHIFT;
	पूर्ण

	bio_endio(bio);
	वापस BLK_QC_T_NONE;
io_error:
	bio_io_error(bio);
	वापस BLK_QC_T_NONE;
पूर्ण

अटल पूर्णांक brd_rw_page(काष्ठा block_device *bdev, sector_t sector,
		       काष्ठा page *page, अचिन्हित पूर्णांक op)
अणु
	काष्ठा brd_device *brd = bdev->bd_disk->निजी_data;
	पूर्णांक err;

	अगर (PageTransHuge(page))
		वापस -ENOTSUPP;
	err = brd_करो_bvec(brd, page, PAGE_SIZE, 0, op, sector);
	page_endio(page, op_is_ग_लिखो(op), err);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा block_device_operations brd_fops = अणु
	.owner =		THIS_MODULE,
	.submit_bio =		brd_submit_bio,
	.rw_page =		brd_rw_page,
पूर्ण;

/*
 * And now the modules code and kernel पूर्णांकerface.
 */
अटल पूर्णांक rd_nr = CONFIG_BLK_DEV_RAM_COUNT;
module_param(rd_nr, पूर्णांक, 0444);
MODULE_PARM_DESC(rd_nr, "Maximum number of brd devices");

अचिन्हित दीर्घ rd_size = CONFIG_BLK_DEV_RAM_SIZE;
module_param(rd_size, uदीर्घ, 0444);
MODULE_PARM_DESC(rd_size, "Size of each RAM disk in kbytes.");

अटल पूर्णांक max_part = 1;
module_param(max_part, पूर्णांक, 0444);
MODULE_PARM_DESC(max_part, "Num Minors to reserve between devices");

MODULE_LICENSE("GPL");
MODULE_ALIAS_BLOCKDEV_MAJOR(RAMDISK_MAJOR);
MODULE_ALIAS("rd");

#अगर_अघोषित MODULE
/* Legacy boot options - nonmodular */
अटल पूर्णांक __init ramdisk_size(अक्षर *str)
अणु
	rd_size = simple_म_से_दीर्घ(str, शून्य, 0);
	वापस 1;
पूर्ण
__setup("ramdisk_size=", ramdisk_size);
#पूर्ण_अगर

/*
 * The device scheme is derived from loop.c. Keep them in synch where possible
 * (should share code eventually).
 */
अटल LIST_HEAD(brd_devices);
अटल DEFINE_MUTEX(brd_devices_mutex);
अटल काष्ठा dentry *brd_debugfs_dir;

अटल काष्ठा brd_device *brd_alloc(पूर्णांक i)
अणु
	काष्ठा brd_device *brd;
	काष्ठा gendisk *disk;
	अक्षर buf[DISK_NAME_LEN];

	brd = kzalloc(माप(*brd), GFP_KERNEL);
	अगर (!brd)
		जाओ out;
	brd->brd_number		= i;
	spin_lock_init(&brd->brd_lock);
	INIT_RADIX_TREE(&brd->brd_pages, GFP_ATOMIC);

	brd->brd_queue = blk_alloc_queue(NUMA_NO_NODE);
	अगर (!brd->brd_queue)
		जाओ out_मुक्त_dev;

	snम_लिखो(buf, DISK_NAME_LEN, "ram%d", i);
	अगर (!IS_ERR_OR_शून्य(brd_debugfs_dir))
		debugfs_create_u64(buf, 0444, brd_debugfs_dir,
				&brd->brd_nr_pages);

	/* This is so fdisk will align partitions on 4k, because of
	 * direct_access API needing 4k alignment, वापसing a PFN
	 * (This is only a problem on very small devices <= 4M,
	 *  otherwise fdisk will align on 1M. Regardless this call
	 *  is harmless)
	 */
	blk_queue_physical_block_size(brd->brd_queue, PAGE_SIZE);
	disk = brd->brd_disk = alloc_disk(max_part);
	अगर (!disk)
		जाओ out_मुक्त_queue;
	disk->major		= RAMDISK_MAJOR;
	disk->first_minor	= i * max_part;
	disk->fops		= &brd_fops;
	disk->निजी_data	= brd;
	disk->flags		= GENHD_FL_EXT_DEVT;
	strlcpy(disk->disk_name, buf, DISK_NAME_LEN);
	set_capacity(disk, rd_size * 2);

	/* Tell the block layer that this is not a rotational device */
	blk_queue_flag_set(QUEUE_FLAG_NONROT, brd->brd_queue);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, brd->brd_queue);

	वापस brd;

out_मुक्त_queue:
	blk_cleanup_queue(brd->brd_queue);
out_मुक्त_dev:
	kमुक्त(brd);
out:
	वापस शून्य;
पूर्ण

अटल व्योम brd_मुक्त(काष्ठा brd_device *brd)
अणु
	put_disk(brd->brd_disk);
	blk_cleanup_queue(brd->brd_queue);
	brd_मुक्त_pages(brd);
	kमुक्त(brd);
पूर्ण

अटल व्योम brd_probe(dev_t dev)
अणु
	काष्ठा brd_device *brd;
	पूर्णांक i = MINOR(dev) / max_part;

	mutex_lock(&brd_devices_mutex);
	list_क्रम_each_entry(brd, &brd_devices, brd_list) अणु
		अगर (brd->brd_number == i)
			जाओ out_unlock;
	पूर्ण

	brd = brd_alloc(i);
	अगर (brd) अणु
		brd->brd_disk->queue = brd->brd_queue;
		add_disk(brd->brd_disk);
		list_add_tail(&brd->brd_list, &brd_devices);
	पूर्ण

out_unlock:
	mutex_unlock(&brd_devices_mutex);
पूर्ण

अटल व्योम brd_del_one(काष्ठा brd_device *brd)
अणु
	list_del(&brd->brd_list);
	del_gendisk(brd->brd_disk);
	brd_मुक्त(brd);
पूर्ण

अटल अंतरभूत व्योम brd_check_and_reset_par(व्योम)
अणु
	अगर (unlikely(!max_part))
		max_part = 1;

	/*
	 * make sure 'max_part' can be भागided exactly by (1U << MINORBITS),
	 * otherwise, it is possiable to get same dev_t when adding partitions.
	 */
	अगर ((1U << MINORBITS) % max_part != 0)
		max_part = 1UL << fls(max_part);

	अगर (max_part > DISK_MAX_PARTS) अणु
		pr_info("brd: max_part can't be larger than %d, reset max_part = %d.\n",
			DISK_MAX_PARTS, DISK_MAX_PARTS);
		max_part = DISK_MAX_PARTS;
	पूर्ण
पूर्ण

अटल पूर्णांक __init brd_init(व्योम)
अणु
	काष्ठा brd_device *brd, *next;
	पूर्णांक i;

	/*
	 * brd module now has a feature to instantiate underlying device
	 * काष्ठाure on-demand, provided that there is an access dev node.
	 *
	 * (1) अगर rd_nr is specअगरied, create that many upfront. अन्यथा
	 *     it शेषs to CONFIG_BLK_DEV_RAM_COUNT
	 * (2) User can further extend brd devices by create dev node themselves
	 *     and have kernel स्वतःmatically instantiate actual device
	 *     on-demand. Example:
	 *		mknod /path/devnod_name b 1 X	# 1 is the rd major
	 *		fdisk -l /path/devnod_name
	 *	If (X / max_part) was not alपढ़ोy created it will be created
	 *	dynamically.
	 */

	अगर (__रेजिस्टर_blkdev(RAMDISK_MAJOR, "ramdisk", brd_probe))
		वापस -EIO;

	brd_check_and_reset_par();

	brd_debugfs_dir = debugfs_create_dir("ramdisk_pages", शून्य);

	mutex_lock(&brd_devices_mutex);
	क्रम (i = 0; i < rd_nr; i++) अणु
		brd = brd_alloc(i);
		अगर (!brd)
			जाओ out_मुक्त;
		list_add_tail(&brd->brd_list, &brd_devices);
	पूर्ण

	/* poपूर्णांक of no वापस */

	list_क्रम_each_entry(brd, &brd_devices, brd_list) अणु
		/*
		 * associate with queue just beक्रमe adding disk क्रम
		 * aव्योमing to mess up failure path
		 */
		brd->brd_disk->queue = brd->brd_queue;
		add_disk(brd->brd_disk);
	पूर्ण
	mutex_unlock(&brd_devices_mutex);

	pr_info("brd: module loaded\n");
	वापस 0;

out_मुक्त:
	debugfs_हटाओ_recursive(brd_debugfs_dir);

	list_क्रम_each_entry_safe(brd, next, &brd_devices, brd_list) अणु
		list_del(&brd->brd_list);
		brd_मुक्त(brd);
	पूर्ण
	mutex_unlock(&brd_devices_mutex);
	unरेजिस्टर_blkdev(RAMDISK_MAJOR, "ramdisk");

	pr_info("brd: module NOT loaded !!!\n");
	वापस -ENOMEM;
पूर्ण

अटल व्योम __निकास brd_निकास(व्योम)
अणु
	काष्ठा brd_device *brd, *next;

	debugfs_हटाओ_recursive(brd_debugfs_dir);

	list_क्रम_each_entry_safe(brd, next, &brd_devices, brd_list)
		brd_del_one(brd);

	unरेजिस्टर_blkdev(RAMDISK_MAJOR, "ramdisk");

	pr_info("brd: module unloaded\n");
पूर्ण

module_init(brd_init);
module_निकास(brd_निकास);

