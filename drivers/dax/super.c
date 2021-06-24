<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2017 Intel Corporation. All rights reserved.
 */
#समावेश <linux/pagemap.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/magic.h>
#समावेश <linux/genhd.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/cdev.h>
#समावेश <linux/hash.h>
#समावेश <linux/slab.h>
#समावेश <linux/uपन.स>
#समावेश <linux/dax.h>
#समावेश <linux/fs.h>
#समावेश "dax-private.h"

अटल dev_t dax_devt;
DEFINE_STATIC_SRCU(dax_srcu);
अटल काष्ठा vfsmount *dax_mnt;
अटल DEFINE_IDA(dax_minor_ida);
अटल काष्ठा kmem_cache *dax_cache __पढ़ो_mostly;
अटल काष्ठा super_block *dax_superblock __पढ़ो_mostly;

#घोषणा DAX_HASH_SIZE (PAGE_SIZE / माप(काष्ठा hlist_head))
अटल काष्ठा hlist_head dax_host_list[DAX_HASH_SIZE];
अटल DEFINE_SPINLOCK(dax_host_lock);

पूर्णांक dax_पढ़ो_lock(व्योम)
अणु
	वापस srcu_पढ़ो_lock(&dax_srcu);
पूर्ण
EXPORT_SYMBOL_GPL(dax_पढ़ो_lock);

व्योम dax_पढ़ो_unlock(पूर्णांक id)
अणु
	srcu_पढ़ो_unlock(&dax_srcu, id);
पूर्ण
EXPORT_SYMBOL_GPL(dax_पढ़ो_unlock);

#अगर_घोषित CONFIG_BLOCK
#समावेश <linux/blkdev.h>

पूर्णांक bdev_dax_pgoff(काष्ठा block_device *bdev, sector_t sector, माप_प्रकार size,
		pgoff_t *pgoff)
अणु
	sector_t start_sect = bdev ? get_start_sect(bdev) : 0;
	phys_addr_t phys_off = (start_sect + sector) * 512;

	अगर (pgoff)
		*pgoff = PHYS_PFN(phys_off);
	अगर (phys_off % PAGE_SIZE || size % PAGE_SIZE)
		वापस -EINVAL;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(bdev_dax_pgoff);

#अगर IS_ENABLED(CONFIG_FS_DAX)
काष्ठा dax_device *fs_dax_get_by_bdev(काष्ठा block_device *bdev)
अणु
	अगर (!blk_queue_dax(bdev->bd_disk->queue))
		वापस शून्य;
	वापस dax_get_by_host(bdev->bd_disk->disk_name);
पूर्ण
EXPORT_SYMBOL_GPL(fs_dax_get_by_bdev);
#पूर्ण_अगर

bool __generic_fsdax_supported(काष्ठा dax_device *dax_dev,
		काष्ठा block_device *bdev, पूर्णांक blocksize, sector_t start,
		sector_t sectors)
अणु
	bool dax_enabled = false;
	pgoff_t pgoff, pgoff_end;
	अक्षर buf[BDEVNAME_SIZE];
	व्योम *kaddr, *end_kaddr;
	pfn_t pfn, end_pfn;
	sector_t last_page;
	दीर्घ len, len2;
	पूर्णांक err, id;

	अगर (blocksize != PAGE_SIZE) अणु
		pr_info("%s: error: unsupported blocksize for dax\n",
				bdevname(bdev, buf));
		वापस false;
	पूर्ण

	अगर (!dax_dev) अणु
		pr_debug("%s: error: dax unsupported by block device\n",
				bdevname(bdev, buf));
		वापस false;
	पूर्ण

	err = bdev_dax_pgoff(bdev, start, PAGE_SIZE, &pgoff);
	अगर (err) अणु
		pr_info("%s: error: unaligned partition for dax\n",
				bdevname(bdev, buf));
		वापस false;
	पूर्ण

	last_page = PFN_DOWN((start + sectors - 1) * 512) * PAGE_SIZE / 512;
	err = bdev_dax_pgoff(bdev, last_page, PAGE_SIZE, &pgoff_end);
	अगर (err) अणु
		pr_info("%s: error: unaligned partition for dax\n",
				bdevname(bdev, buf));
		वापस false;
	पूर्ण

	id = dax_पढ़ो_lock();
	len = dax_direct_access(dax_dev, pgoff, 1, &kaddr, &pfn);
	len2 = dax_direct_access(dax_dev, pgoff_end, 1, &end_kaddr, &end_pfn);

	अगर (len < 1 || len2 < 1) अणु
		pr_info("%s: error: dax access failed (%ld)\n",
				bdevname(bdev, buf), len < 1 ? len : len2);
		dax_पढ़ो_unlock(id);
		वापस false;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_FS_DAX_LIMITED) && pfn_t_special(pfn)) अणु
		/*
		 * An arch that has enabled the pmem api should also
		 * have its drivers support pfn_t_devmap()
		 *
		 * This is a developer warning and should not trigger in
		 * production. dax_flush() will crash since it depends
		 * on being able to करो (page_address(pfn_to_page())).
		 */
		WARN_ON(IS_ENABLED(CONFIG_ARCH_HAS_PMEM_API));
		dax_enabled = true;
	पूर्ण अन्यथा अगर (pfn_t_devmap(pfn) && pfn_t_devmap(end_pfn)) अणु
		काष्ठा dev_pagemap *pgmap, *end_pgmap;

		pgmap = get_dev_pagemap(pfn_t_to_pfn(pfn), शून्य);
		end_pgmap = get_dev_pagemap(pfn_t_to_pfn(end_pfn), शून्य);
		अगर (pgmap && pgmap == end_pgmap && pgmap->type == MEMORY_DEVICE_FS_DAX
				&& pfn_t_to_page(pfn)->pgmap == pgmap
				&& pfn_t_to_page(end_pfn)->pgmap == pgmap
				&& pfn_t_to_pfn(pfn) == PHYS_PFN(__pa(kaddr))
				&& pfn_t_to_pfn(end_pfn) == PHYS_PFN(__pa(end_kaddr)))
			dax_enabled = true;
		put_dev_pagemap(pgmap);
		put_dev_pagemap(end_pgmap);

	पूर्ण
	dax_पढ़ो_unlock(id);

	अगर (!dax_enabled) अणु
		pr_info("%s: error: dax support not enabled\n",
				bdevname(bdev, buf));
		वापस false;
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(__generic_fsdax_supported);

/**
 * __bdev_dax_supported() - Check अगर the device supports dax क्रम fileप्रणाली
 * @bdev: block device to check
 * @blocksize: The block size of the device
 *
 * This is a library function क्रम fileप्रणालीs to check अगर the block device
 * can be mounted with dax option.
 *
 * Return: true अगर supported, false अगर unsupported
 */
bool __bdev_dax_supported(काष्ठा block_device *bdev, पूर्णांक blocksize)
अणु
	काष्ठा dax_device *dax_dev;
	काष्ठा request_queue *q;
	अक्षर buf[BDEVNAME_SIZE];
	bool ret;
	पूर्णांक id;

	q = bdev_get_queue(bdev);
	अगर (!q || !blk_queue_dax(q)) अणु
		pr_debug("%s: error: request queue doesn't support dax\n",
				bdevname(bdev, buf));
		वापस false;
	पूर्ण

	dax_dev = dax_get_by_host(bdev->bd_disk->disk_name);
	अगर (!dax_dev) अणु
		pr_debug("%s: error: device does not support dax\n",
				bdevname(bdev, buf));
		वापस false;
	पूर्ण

	id = dax_पढ़ो_lock();
	ret = dax_supported(dax_dev, bdev, blocksize, 0,
			i_size_पढ़ो(bdev->bd_inode) / 512);
	dax_पढ़ो_unlock(id);

	put_dax(dax_dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__bdev_dax_supported);
#पूर्ण_अगर

क्रमागत dax_device_flags अणु
	/* !alive + rcu grace period == no new operations / mappings */
	DAXDEV_ALIVE,
	/* gate whether dax_flush() calls the low level flush routine */
	DAXDEV_WRITE_CACHE,
	/* flag to check अगर device supports synchronous flush */
	DAXDEV_SYNC,
पूर्ण;

/**
 * काष्ठा dax_device - anchor object क्रम dax services
 * @inode: core vfs
 * @cdev: optional अक्षरacter पूर्णांकerface क्रम "device dax"
 * @host: optional name क्रम lookups where the device path is not available
 * @निजी: dax driver निजी data
 * @flags: state and boolean properties
 */
काष्ठा dax_device अणु
	काष्ठा hlist_node list;
	काष्ठा inode inode;
	काष्ठा cdev cdev;
	स्थिर अक्षर *host;
	व्योम *निजी;
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा dax_operations *ops;
पूर्ण;

अटल sमाप_प्रकार ग_लिखो_cache_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dax_device *dax_dev = dax_get_by_host(dev_name(dev));
	sमाप_प्रकार rc;

	WARN_ON_ONCE(!dax_dev);
	अगर (!dax_dev)
		वापस -ENXIO;

	rc = प्र_लिखो(buf, "%d\n", !!dax_ग_लिखो_cache_enabled(dax_dev));
	put_dax(dax_dev);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_cache_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	bool ग_लिखो_cache;
	पूर्णांक rc = strtobool(buf, &ग_लिखो_cache);
	काष्ठा dax_device *dax_dev = dax_get_by_host(dev_name(dev));

	WARN_ON_ONCE(!dax_dev);
	अगर (!dax_dev)
		वापस -ENXIO;

	अगर (rc)
		len = rc;
	अन्यथा
		dax_ग_लिखो_cache(dax_dev, ग_लिखो_cache);

	put_dax(dax_dev);
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(ग_लिखो_cache);

अटल umode_t dax_visible(काष्ठा kobject *kobj, काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, typeof(*dev), kobj);
	काष्ठा dax_device *dax_dev = dax_get_by_host(dev_name(dev));

	WARN_ON_ONCE(!dax_dev);
	अगर (!dax_dev)
		वापस 0;

#अगर_अघोषित CONFIG_ARCH_HAS_PMEM_API
	अगर (a == &dev_attr_ग_लिखो_cache.attr)
		वापस 0;
#पूर्ण_अगर
	वापस a->mode;
पूर्ण

अटल काष्ठा attribute *dax_attributes[] = अणु
	&dev_attr_ग_लिखो_cache.attr,
	शून्य,
पूर्ण;

काष्ठा attribute_group dax_attribute_group = अणु
	.name = "dax",
	.attrs = dax_attributes,
	.is_visible = dax_visible,
पूर्ण;
EXPORT_SYMBOL_GPL(dax_attribute_group);

/**
 * dax_direct_access() - translate a device pgoff to an असलolute pfn
 * @dax_dev: a dax_device instance representing the logical memory range
 * @pgoff: offset in pages from the start of the device to translate
 * @nr_pages: number of consecutive pages caller can handle relative to @pfn
 * @kaddr: output parameter that वापसs a भव address mapping of pfn
 * @pfn: output parameter that वापसs an असलolute pfn translation of @pgoff
 *
 * Return: negative त्रुटि_सं अगर an error occurs, otherwise the number of
 * pages accessible at the device relative @pgoff.
 */
दीर्घ dax_direct_access(काष्ठा dax_device *dax_dev, pgoff_t pgoff, दीर्घ nr_pages,
		व्योम **kaddr, pfn_t *pfn)
अणु
	दीर्घ avail;

	अगर (!dax_dev)
		वापस -EOPNOTSUPP;

	अगर (!dax_alive(dax_dev))
		वापस -ENXIO;

	अगर (nr_pages < 0)
		वापस nr_pages;

	avail = dax_dev->ops->direct_access(dax_dev, pgoff, nr_pages,
			kaddr, pfn);
	अगर (!avail)
		वापस -दुस्फल;
	वापस min(avail, nr_pages);
पूर्ण
EXPORT_SYMBOL_GPL(dax_direct_access);

bool dax_supported(काष्ठा dax_device *dax_dev, काष्ठा block_device *bdev,
		पूर्णांक blocksize, sector_t start, sector_t len)
अणु
	अगर (!dax_dev)
		वापस false;

	अगर (!dax_alive(dax_dev))
		वापस false;

	वापस dax_dev->ops->dax_supported(dax_dev, bdev, blocksize, start, len);
पूर्ण
EXPORT_SYMBOL_GPL(dax_supported);

माप_प्रकार dax_copy_from_iter(काष्ठा dax_device *dax_dev, pgoff_t pgoff, व्योम *addr,
		माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अगर (!dax_alive(dax_dev))
		वापस 0;

	वापस dax_dev->ops->copy_from_iter(dax_dev, pgoff, addr, bytes, i);
पूर्ण
EXPORT_SYMBOL_GPL(dax_copy_from_iter);

माप_प्रकार dax_copy_to_iter(काष्ठा dax_device *dax_dev, pgoff_t pgoff, व्योम *addr,
		माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अगर (!dax_alive(dax_dev))
		वापस 0;

	वापस dax_dev->ops->copy_to_iter(dax_dev, pgoff, addr, bytes, i);
पूर्ण
EXPORT_SYMBOL_GPL(dax_copy_to_iter);

पूर्णांक dax_zero_page_range(काष्ठा dax_device *dax_dev, pgoff_t pgoff,
			माप_प्रकार nr_pages)
अणु
	अगर (!dax_alive(dax_dev))
		वापस -ENXIO;
	/*
	 * There are no callers that want to zero more than one page as of now.
	 * Once users are there, this check can be हटाओd after the
	 * device mapper code has been updated to split ranges across tarमाला_लो.
	 */
	अगर (nr_pages != 1)
		वापस -EIO;

	वापस dax_dev->ops->zero_page_range(dax_dev, pgoff, nr_pages);
पूर्ण
EXPORT_SYMBOL_GPL(dax_zero_page_range);

#अगर_घोषित CONFIG_ARCH_HAS_PMEM_API
व्योम arch_wb_cache_pmem(व्योम *addr, माप_प्रकार size);
व्योम dax_flush(काष्ठा dax_device *dax_dev, व्योम *addr, माप_प्रकार size)
अणु
	अगर (unlikely(!dax_ग_लिखो_cache_enabled(dax_dev)))
		वापस;

	arch_wb_cache_pmem(addr, size);
पूर्ण
#अन्यथा
व्योम dax_flush(काष्ठा dax_device *dax_dev, व्योम *addr, माप_प्रकार size)
अणु
पूर्ण
#पूर्ण_अगर
EXPORT_SYMBOL_GPL(dax_flush);

व्योम dax_ग_लिखो_cache(काष्ठा dax_device *dax_dev, bool wc)
अणु
	अगर (wc)
		set_bit(DAXDEV_WRITE_CACHE, &dax_dev->flags);
	अन्यथा
		clear_bit(DAXDEV_WRITE_CACHE, &dax_dev->flags);
पूर्ण
EXPORT_SYMBOL_GPL(dax_ग_लिखो_cache);

bool dax_ग_लिखो_cache_enabled(काष्ठा dax_device *dax_dev)
अणु
	वापस test_bit(DAXDEV_WRITE_CACHE, &dax_dev->flags);
पूर्ण
EXPORT_SYMBOL_GPL(dax_ग_लिखो_cache_enabled);

bool __dax_synchronous(काष्ठा dax_device *dax_dev)
अणु
	वापस test_bit(DAXDEV_SYNC, &dax_dev->flags);
पूर्ण
EXPORT_SYMBOL_GPL(__dax_synchronous);

व्योम __set_dax_synchronous(काष्ठा dax_device *dax_dev)
अणु
	set_bit(DAXDEV_SYNC, &dax_dev->flags);
पूर्ण
EXPORT_SYMBOL_GPL(__set_dax_synchronous);

bool dax_alive(काष्ठा dax_device *dax_dev)
अणु
	lockdep_निश्चित_held(&dax_srcu);
	वापस test_bit(DAXDEV_ALIVE, &dax_dev->flags);
पूर्ण
EXPORT_SYMBOL_GPL(dax_alive);

अटल पूर्णांक dax_host_hash(स्थिर अक्षर *host)
अणु
	वापस hashlen_hash(hashlen_string("DAX", host)) % DAX_HASH_SIZE;
पूर्ण

/*
 * Note, rcu is not protecting the liveness of dax_dev, rcu is ensuring
 * that any fault handlers or operations that might have seen
 * dax_alive(), have completed.  Any operations that start after
 * synchronize_srcu() has run will पात upon seeing !dax_alive().
 */
व्योम समाप्त_dax(काष्ठा dax_device *dax_dev)
अणु
	अगर (!dax_dev)
		वापस;

	clear_bit(DAXDEV_ALIVE, &dax_dev->flags);

	synchronize_srcu(&dax_srcu);

	spin_lock(&dax_host_lock);
	hlist_del_init(&dax_dev->list);
	spin_unlock(&dax_host_lock);
पूर्ण
EXPORT_SYMBOL_GPL(समाप्त_dax);

व्योम run_dax(काष्ठा dax_device *dax_dev)
अणु
	set_bit(DAXDEV_ALIVE, &dax_dev->flags);
पूर्ण
EXPORT_SYMBOL_GPL(run_dax);

अटल काष्ठा inode *dax_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा dax_device *dax_dev;
	काष्ठा inode *inode;

	dax_dev = kmem_cache_alloc(dax_cache, GFP_KERNEL);
	अगर (!dax_dev)
		वापस शून्य;

	inode = &dax_dev->inode;
	inode->i_rdev = 0;
	वापस inode;
पूर्ण

अटल काष्ठा dax_device *to_dax_dev(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा dax_device, inode);
पूर्ण

अटल व्योम dax_मुक्त_inode(काष्ठा inode *inode)
अणु
	काष्ठा dax_device *dax_dev = to_dax_dev(inode);
	kमुक्त(dax_dev->host);
	dax_dev->host = शून्य;
	अगर (inode->i_rdev)
		ida_simple_हटाओ(&dax_minor_ida, iminor(inode));
	kmem_cache_मुक्त(dax_cache, dax_dev);
पूर्ण

अटल व्योम dax_destroy_inode(काष्ठा inode *inode)
अणु
	काष्ठा dax_device *dax_dev = to_dax_dev(inode);
	WARN_ONCE(test_bit(DAXDEV_ALIVE, &dax_dev->flags),
			"kill_dax() must be called before final iput()\n");
पूर्ण

अटल स्थिर काष्ठा super_operations dax_sops = अणु
	.statfs = simple_statfs,
	.alloc_inode = dax_alloc_inode,
	.destroy_inode = dax_destroy_inode,
	.मुक्त_inode = dax_मुक्त_inode,
	.drop_inode = generic_delete_inode,
पूर्ण;

अटल पूर्णांक dax_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा pseuकरो_fs_context *ctx = init_pseuकरो(fc, DAXFS_MAGIC);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->ops = &dax_sops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type dax_fs_type = अणु
	.name		= "dax",
	.init_fs_context = dax_init_fs_context,
	.समाप्त_sb	= समाप्त_anon_super,
पूर्ण;

अटल पूर्णांक dax_test(काष्ठा inode *inode, व्योम *data)
अणु
	dev_t devt = *(dev_t *) data;

	वापस inode->i_rdev == devt;
पूर्ण

अटल पूर्णांक dax_set(काष्ठा inode *inode, व्योम *data)
अणु
	dev_t devt = *(dev_t *) data;

	inode->i_rdev = devt;
	वापस 0;
पूर्ण

अटल काष्ठा dax_device *dax_dev_get(dev_t devt)
अणु
	काष्ठा dax_device *dax_dev;
	काष्ठा inode *inode;

	inode = iget5_locked(dax_superblock, hash_32(devt + DAXFS_MAGIC, 31),
			dax_test, dax_set, &devt);

	अगर (!inode)
		वापस शून्य;

	dax_dev = to_dax_dev(inode);
	अगर (inode->i_state & I_NEW) अणु
		set_bit(DAXDEV_ALIVE, &dax_dev->flags);
		inode->i_cdev = &dax_dev->cdev;
		inode->i_mode = S_IFCHR;
		inode->i_flags = S_DAX;
		mapping_set_gfp_mask(&inode->i_data, GFP_USER);
		unlock_new_inode(inode);
	पूर्ण

	वापस dax_dev;
पूर्ण

अटल व्योम dax_add_host(काष्ठा dax_device *dax_dev, स्थिर अक्षर *host)
अणु
	पूर्णांक hash;

	/*
	 * Unconditionally init dax_dev since it's coming from a
	 * non-zeroed slab cache
	 */
	INIT_HLIST_NODE(&dax_dev->list);
	dax_dev->host = host;
	अगर (!host)
		वापस;

	hash = dax_host_hash(host);
	spin_lock(&dax_host_lock);
	hlist_add_head(&dax_dev->list, &dax_host_list[hash]);
	spin_unlock(&dax_host_lock);
पूर्ण

काष्ठा dax_device *alloc_dax(व्योम *निजी, स्थिर अक्षर *__host,
		स्थिर काष्ठा dax_operations *ops, अचिन्हित दीर्घ flags)
अणु
	काष्ठा dax_device *dax_dev;
	स्थिर अक्षर *host;
	dev_t devt;
	पूर्णांक minor;

	अगर (ops && !ops->zero_page_range) अणु
		pr_debug("%s: error: device does not provide dax"
			 " operation zero_page_range()\n",
			 __host ? __host : "Unknown");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	host = kstrdup(__host, GFP_KERNEL);
	अगर (__host && !host)
		वापस ERR_PTR(-ENOMEM);

	minor = ida_simple_get(&dax_minor_ida, 0, MINORMASK+1, GFP_KERNEL);
	अगर (minor < 0)
		जाओ err_minor;

	devt = MKDEV(MAJOR(dax_devt), minor);
	dax_dev = dax_dev_get(devt);
	अगर (!dax_dev)
		जाओ err_dev;

	dax_add_host(dax_dev, host);
	dax_dev->ops = ops;
	dax_dev->निजी = निजी;
	अगर (flags & DAXDEV_F_SYNC)
		set_dax_synchronous(dax_dev);

	वापस dax_dev;

 err_dev:
	ida_simple_हटाओ(&dax_minor_ida, minor);
 err_minor:
	kमुक्त(host);
	वापस ERR_PTR(-ENOMEM);
पूर्ण
EXPORT_SYMBOL_GPL(alloc_dax);

व्योम put_dax(काष्ठा dax_device *dax_dev)
अणु
	अगर (!dax_dev)
		वापस;
	iput(&dax_dev->inode);
पूर्ण
EXPORT_SYMBOL_GPL(put_dax);

/**
 * dax_get_by_host() - temporary lookup mechanism क्रम fileप्रणाली-dax
 * @host: alternate name क्रम the device रेजिस्टरed by a dax driver
 */
काष्ठा dax_device *dax_get_by_host(स्थिर अक्षर *host)
अणु
	काष्ठा dax_device *dax_dev, *found = शून्य;
	पूर्णांक hash, id;

	अगर (!host)
		वापस शून्य;

	hash = dax_host_hash(host);

	id = dax_पढ़ो_lock();
	spin_lock(&dax_host_lock);
	hlist_क्रम_each_entry(dax_dev, &dax_host_list[hash], list) अणु
		अगर (!dax_alive(dax_dev)
				|| म_भेद(host, dax_dev->host) != 0)
			जारी;

		अगर (igrab(&dax_dev->inode))
			found = dax_dev;
		अवरोध;
	पूर्ण
	spin_unlock(&dax_host_lock);
	dax_पढ़ो_unlock(id);

	वापस found;
पूर्ण
EXPORT_SYMBOL_GPL(dax_get_by_host);

/**
 * inode_dax: convert a खुला inode पूर्णांकo its dax_dev
 * @inode: An inode with i_cdev poपूर्णांकing to a dax_dev
 *
 * Note this is not equivalent to to_dax_dev() which is क्रम निजी
 * पूर्णांकernal use where we know the inode fileप्रणाली type == dax_fs_type.
 */
काष्ठा dax_device *inode_dax(काष्ठा inode *inode)
अणु
	काष्ठा cdev *cdev = inode->i_cdev;

	वापस container_of(cdev, काष्ठा dax_device, cdev);
पूर्ण
EXPORT_SYMBOL_GPL(inode_dax);

काष्ठा inode *dax_inode(काष्ठा dax_device *dax_dev)
अणु
	वापस &dax_dev->inode;
पूर्ण
EXPORT_SYMBOL_GPL(dax_inode);

व्योम *dax_get_निजी(काष्ठा dax_device *dax_dev)
अणु
	अगर (!test_bit(DAXDEV_ALIVE, &dax_dev->flags))
		वापस शून्य;
	वापस dax_dev->निजी;
पूर्ण
EXPORT_SYMBOL_GPL(dax_get_निजी);

अटल व्योम init_once(व्योम *_dax_dev)
अणु
	काष्ठा dax_device *dax_dev = _dax_dev;
	काष्ठा inode *inode = &dax_dev->inode;

	स_रखो(dax_dev, 0, माप(*dax_dev));
	inode_init_once(inode);
पूर्ण

अटल पूर्णांक dax_fs_init(व्योम)
अणु
	पूर्णांक rc;

	dax_cache = kmem_cache_create("dax_cache", माप(काष्ठा dax_device), 0,
			(SLAB_HWCACHE_ALIGN|SLAB_RECLAIM_ACCOUNT|
			 SLAB_MEM_SPREAD|SLAB_ACCOUNT),
			init_once);
	अगर (!dax_cache)
		वापस -ENOMEM;

	dax_mnt = kern_mount(&dax_fs_type);
	अगर (IS_ERR(dax_mnt)) अणु
		rc = PTR_ERR(dax_mnt);
		जाओ err_mount;
	पूर्ण
	dax_superblock = dax_mnt->mnt_sb;

	वापस 0;

 err_mount:
	kmem_cache_destroy(dax_cache);

	वापस rc;
पूर्ण

अटल व्योम dax_fs_निकास(व्योम)
अणु
	kern_unmount(dax_mnt);
	kmem_cache_destroy(dax_cache);
पूर्ण

अटल पूर्णांक __init dax_core_init(व्योम)
अणु
	पूर्णांक rc;

	rc = dax_fs_init();
	अगर (rc)
		वापस rc;

	rc = alloc_chrdev_region(&dax_devt, 0, MINORMASK+1, "dax");
	अगर (rc)
		जाओ err_chrdev;

	rc = dax_bus_init();
	अगर (rc)
		जाओ err_bus;
	वापस 0;

err_bus:
	unरेजिस्टर_chrdev_region(dax_devt, MINORMASK+1);
err_chrdev:
	dax_fs_निकास();
	वापस 0;
पूर्ण

अटल व्योम __निकास dax_core_निकास(व्योम)
अणु
	dax_bus_निकास();
	unरेजिस्टर_chrdev_region(dax_devt, MINORMASK+1);
	ida_destroy(&dax_minor_ida);
	dax_fs_निकास();
पूर्ण

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
subsys_initcall(dax_core_init);
module_निकास(dax_core_निकास);
