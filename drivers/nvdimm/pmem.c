<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Persistent Memory Driver
 *
 * Copyright (c) 2014-2015, Intel Corporation.
 * Copyright (c) 2015, Christoph Hellwig <hch@lst.de>.
 * Copyright (c) 2015, Boaz Harrosh <boaz@plexistor.com>.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/set_memory.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/badblocks.h>
#समावेश <linux/memremap.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/slab.h>
#समावेश <linux/uपन.स>
#समावेश <linux/dax.h>
#समावेश <linux/nd.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश "pmem.h"
#समावेश "btt.h"
#समावेश "pfn.h"
#समावेश "nd.h"

अटल काष्ठा device *to_dev(काष्ठा pmem_device *pmem)
अणु
	/*
	 * nvdimm bus services need a 'dev' parameter, and we record the device
	 * at init in bb.dev.
	 */
	वापस pmem->bb.dev;
पूर्ण

अटल काष्ठा nd_region *to_region(काष्ठा pmem_device *pmem)
अणु
	वापस to_nd_region(to_dev(pmem)->parent);
पूर्ण

अटल व्योम hwpoison_clear(काष्ठा pmem_device *pmem,
		phys_addr_t phys, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ pfn_start, pfn_end, pfn;

	/* only pmem in the linear map supports HWPoison */
	अगर (is_vदो_स्मृति_addr(pmem->virt_addr))
		वापस;

	pfn_start = PHYS_PFN(phys);
	pfn_end = pfn_start + PHYS_PFN(len);
	क्रम (pfn = pfn_start; pfn < pfn_end; pfn++) अणु
		काष्ठा page *page = pfn_to_page(pfn);

		/*
		 * Note, no need to hold a get_dev_pagemap() reference
		 * here since we're in the driver I/O path and
		 * outstanding I/O requests pin the dev_pagemap.
		 */
		अगर (test_and_clear_pmem_poison(page))
			clear_mce_nospec(pfn);
	पूर्ण
पूर्ण

अटल blk_status_t pmem_clear_poison(काष्ठा pmem_device *pmem,
		phys_addr_t offset, अचिन्हित पूर्णांक len)
अणु
	काष्ठा device *dev = to_dev(pmem);
	sector_t sector;
	दीर्घ cleared;
	blk_status_t rc = BLK_STS_OK;

	sector = (offset - pmem->data_offset) / 512;

	cleared = nvdimm_clear_poison(dev, pmem->phys_addr + offset, len);
	अगर (cleared < len)
		rc = BLK_STS_IOERR;
	अगर (cleared > 0 && cleared / 512) अणु
		hwpoison_clear(pmem, pmem->phys_addr + offset, cleared);
		cleared /= 512;
		dev_dbg(dev, "%#llx clear %ld sector%s\n",
				(अचिन्हित दीर्घ दीर्घ) sector, cleared,
				cleared > 1 ? "s" : "");
		badblocks_clear(&pmem->bb, sector, cleared);
		अगर (pmem->bb_state)
			sysfs_notअगरy_dirent(pmem->bb_state);
	पूर्ण

	arch_invalidate_pmem(pmem->virt_addr + offset, len);

	वापस rc;
पूर्ण

अटल व्योम ग_लिखो_pmem(व्योम *pmem_addr, काष्ठा page *page,
		अचिन्हित पूर्णांक off, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक chunk;
	व्योम *mem;

	जबतक (len) अणु
		mem = kmap_atomic(page);
		chunk = min_t(अचिन्हित पूर्णांक, len, PAGE_SIZE - off);
		स_नकल_flushcache(pmem_addr, mem + off, chunk);
		kunmap_atomic(mem);
		len -= chunk;
		off = 0;
		page++;
		pmem_addr += chunk;
	पूर्ण
पूर्ण

अटल blk_status_t पढ़ो_pmem(काष्ठा page *page, अचिन्हित पूर्णांक off,
		व्योम *pmem_addr, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक chunk;
	अचिन्हित दीर्घ rem;
	व्योम *mem;

	जबतक (len) अणु
		mem = kmap_atomic(page);
		chunk = min_t(अचिन्हित पूर्णांक, len, PAGE_SIZE - off);
		rem = copy_mc_to_kernel(mem + off, pmem_addr, chunk);
		kunmap_atomic(mem);
		अगर (rem)
			वापस BLK_STS_IOERR;
		len -= chunk;
		off = 0;
		page++;
		pmem_addr += chunk;
	पूर्ण
	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t pmem_करो_पढ़ो(काष्ठा pmem_device *pmem,
			काष्ठा page *page, अचिन्हित पूर्णांक page_off,
			sector_t sector, अचिन्हित पूर्णांक len)
अणु
	blk_status_t rc;
	phys_addr_t pmem_off = sector * 512 + pmem->data_offset;
	व्योम *pmem_addr = pmem->virt_addr + pmem_off;

	अगर (unlikely(is_bad_pmem(&pmem->bb, sector, len)))
		वापस BLK_STS_IOERR;

	rc = पढ़ो_pmem(page, page_off, pmem_addr, len);
	flush_dcache_page(page);
	वापस rc;
पूर्ण

अटल blk_status_t pmem_करो_ग_लिखो(काष्ठा pmem_device *pmem,
			काष्ठा page *page, अचिन्हित पूर्णांक page_off,
			sector_t sector, अचिन्हित पूर्णांक len)
अणु
	blk_status_t rc = BLK_STS_OK;
	bool bad_pmem = false;
	phys_addr_t pmem_off = sector * 512 + pmem->data_offset;
	व्योम *pmem_addr = pmem->virt_addr + pmem_off;

	अगर (unlikely(is_bad_pmem(&pmem->bb, sector, len)))
		bad_pmem = true;

	/*
	 * Note that we ग_लिखो the data both beक्रमe and after
	 * clearing poison.  The ग_लिखो beक्रमe clear poison
	 * handles situations where the latest written data is
	 * preserved and the clear poison operation simply marks
	 * the address range as valid without changing the data.
	 * In this हाल application software can assume that an
	 * पूर्णांकerrupted ग_लिखो will either वापस the new good
	 * data or an error.
	 *
	 * However, अगर pmem_clear_poison() leaves the data in an
	 * indeterminate state we need to perक्रमm the ग_लिखो
	 * after clear poison.
	 */
	flush_dcache_page(page);
	ग_लिखो_pmem(pmem_addr, page, page_off, len);
	अगर (unlikely(bad_pmem)) अणु
		rc = pmem_clear_poison(pmem, pmem_off, len);
		ग_लिखो_pmem(pmem_addr, page, page_off, len);
	पूर्ण

	वापस rc;
पूर्ण

अटल blk_qc_t pmem_submit_bio(काष्ठा bio *bio)
अणु
	पूर्णांक ret = 0;
	blk_status_t rc = 0;
	bool करो_acct;
	अचिन्हित दीर्घ start;
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;
	काष्ठा pmem_device *pmem = bio->bi_bdev->bd_disk->निजी_data;
	काष्ठा nd_region *nd_region = to_region(pmem);

	अगर (bio->bi_opf & REQ_PREFLUSH)
		ret = nvdimm_flush(nd_region, bio);

	करो_acct = blk_queue_io_stat(bio->bi_bdev->bd_disk->queue);
	अगर (करो_acct)
		start = bio_start_io_acct(bio);
	bio_क्रम_each_segment(bvec, bio, iter) अणु
		अगर (op_is_ग_लिखो(bio_op(bio)))
			rc = pmem_करो_ग_लिखो(pmem, bvec.bv_page, bvec.bv_offset,
				iter.bi_sector, bvec.bv_len);
		अन्यथा
			rc = pmem_करो_पढ़ो(pmem, bvec.bv_page, bvec.bv_offset,
				iter.bi_sector, bvec.bv_len);
		अगर (rc) अणु
			bio->bi_status = rc;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (करो_acct)
		bio_end_io_acct(bio, start);

	अगर (bio->bi_opf & REQ_FUA)
		ret = nvdimm_flush(nd_region, bio);

	अगर (ret)
		bio->bi_status = त्रुटि_सं_to_blk_status(ret);

	bio_endio(bio);
	वापस BLK_QC_T_NONE;
पूर्ण

अटल पूर्णांक pmem_rw_page(काष्ठा block_device *bdev, sector_t sector,
		       काष्ठा page *page, अचिन्हित पूर्णांक op)
अणु
	काष्ठा pmem_device *pmem = bdev->bd_disk->निजी_data;
	blk_status_t rc;

	अगर (op_is_ग_लिखो(op))
		rc = pmem_करो_ग_लिखो(pmem, page, 0, sector, thp_size(page));
	अन्यथा
		rc = pmem_करो_पढ़ो(pmem, page, 0, sector, thp_size(page));
	/*
	 * The ->rw_page पूर्णांकerface is subtle and tricky.  The core
	 * retries on any error, so we can only invoke page_endio() in
	 * the successful completion हाल.  Otherwise, we'll see crashes
	 * caused by द्विगुन completion.
	 */
	अगर (rc == 0)
		page_endio(page, op_is_ग_लिखो(op), 0);

	वापस blk_status_to_त्रुटि_सं(rc);
पूर्ण

/* see "strong" declaration in tools/testing/nvdimm/pmem-dax.c */
__weak दीर्घ __pmem_direct_access(काष्ठा pmem_device *pmem, pgoff_t pgoff,
		दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn)
अणु
	resource_माप_प्रकार offset = PFN_PHYS(pgoff) + pmem->data_offset;

	अगर (unlikely(is_bad_pmem(&pmem->bb, PFN_PHYS(pgoff) / 512,
					PFN_PHYS(nr_pages))))
		वापस -EIO;

	अगर (kaddr)
		*kaddr = pmem->virt_addr + offset;
	अगर (pfn)
		*pfn = phys_to_pfn_t(pmem->phys_addr + offset, pmem->pfn_flags);

	/*
	 * If badblocks are present, limit known good range to the
	 * requested range.
	 */
	अगर (unlikely(pmem->bb.count))
		वापस nr_pages;
	वापस PHYS_PFN(pmem->size - pmem->pfn_pad - offset);
पूर्ण

अटल स्थिर काष्ठा block_device_operations pmem_fops = अणु
	.owner =		THIS_MODULE,
	.submit_bio =		pmem_submit_bio,
	.rw_page =		pmem_rw_page,
पूर्ण;

अटल पूर्णांक pmem_dax_zero_page_range(काष्ठा dax_device *dax_dev, pgoff_t pgoff,
				    माप_प्रकार nr_pages)
अणु
	काष्ठा pmem_device *pmem = dax_get_निजी(dax_dev);

	वापस blk_status_to_त्रुटि_सं(pmem_करो_ग_लिखो(pmem, ZERO_PAGE(0), 0,
				   PFN_PHYS(pgoff) >> SECTOR_SHIFT,
				   PAGE_SIZE));
पूर्ण

अटल दीर्घ pmem_dax_direct_access(काष्ठा dax_device *dax_dev,
		pgoff_t pgoff, दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn)
अणु
	काष्ठा pmem_device *pmem = dax_get_निजी(dax_dev);

	वापस __pmem_direct_access(pmem, pgoff, nr_pages, kaddr, pfn);
पूर्ण

/*
 * Use the 'no check' versions of copy_from_iter_flushcache() and
 * copy_mc_to_iter() to bypass HARDENED_USERCOPY overhead. Bounds
 * checking, both file offset and device offset, is handled by
 * dax_iomap_actor()
 */
अटल माप_प्रकार pmem_copy_from_iter(काष्ठा dax_device *dax_dev, pgoff_t pgoff,
		व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	वापस _copy_from_iter_flushcache(addr, bytes, i);
पूर्ण

अटल माप_प्रकार pmem_copy_to_iter(काष्ठा dax_device *dax_dev, pgoff_t pgoff,
		व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	वापस _copy_mc_to_iter(addr, bytes, i);
पूर्ण

अटल स्थिर काष्ठा dax_operations pmem_dax_ops = अणु
	.direct_access = pmem_dax_direct_access,
	.dax_supported = generic_fsdax_supported,
	.copy_from_iter = pmem_copy_from_iter,
	.copy_to_iter = pmem_copy_to_iter,
	.zero_page_range = pmem_dax_zero_page_range,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *pmem_attribute_groups[] = अणु
	&dax_attribute_group,
	शून्य,
पूर्ण;

अटल व्योम pmem_pagemap_cleanup(काष्ठा dev_pagemap *pgmap)
अणु
	काष्ठा request_queue *q =
		container_of(pgmap->ref, काष्ठा request_queue, q_usage_counter);

	blk_cleanup_queue(q);
पूर्ण

अटल व्योम pmem_release_queue(व्योम *pgmap)
अणु
	pmem_pagemap_cleanup(pgmap);
पूर्ण

अटल व्योम pmem_pagemap_समाप्त(काष्ठा dev_pagemap *pgmap)
अणु
	काष्ठा request_queue *q =
		container_of(pgmap->ref, काष्ठा request_queue, q_usage_counter);

	blk_मुक्तze_queue_start(q);
पूर्ण

अटल व्योम pmem_release_disk(व्योम *__pmem)
अणु
	काष्ठा pmem_device *pmem = __pmem;

	समाप्त_dax(pmem->dax_dev);
	put_dax(pmem->dax_dev);
	del_gendisk(pmem->disk);
	put_disk(pmem->disk);
पूर्ण

अटल स्थिर काष्ठा dev_pagemap_ops fsdax_pagemap_ops = अणु
	.समाप्त			= pmem_pagemap_समाप्त,
	.cleanup		= pmem_pagemap_cleanup,
पूर्ण;

अटल पूर्णांक pmem_attach_disk(काष्ठा device *dev,
		काष्ठा nd_namespace_common *ndns)
अणु
	काष्ठा nd_namespace_io *nsio = to_nd_namespace_io(&ndns->dev);
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	पूर्णांक nid = dev_to_node(dev), fua;
	काष्ठा resource *res = &nsio->res;
	काष्ठा range bb_range;
	काष्ठा nd_pfn *nd_pfn = शून्य;
	काष्ठा dax_device *dax_dev;
	काष्ठा nd_pfn_sb *pfn_sb;
	काष्ठा pmem_device *pmem;
	काष्ठा request_queue *q;
	काष्ठा device *gendev;
	काष्ठा gendisk *disk;
	व्योम *addr;
	पूर्णांक rc;
	अचिन्हित दीर्घ flags = 0UL;

	pmem = devm_kzalloc(dev, माप(*pmem), GFP_KERNEL);
	अगर (!pmem)
		वापस -ENOMEM;

	rc = devm_namespace_enable(dev, ndns, nd_info_block_reserve());
	अगर (rc)
		वापस rc;

	/* जबतक nsio_rw_bytes is active, parse a pfn info block अगर present */
	अगर (is_nd_pfn(dev)) अणु
		nd_pfn = to_nd_pfn(dev);
		rc = nvdimm_setup_pfn(nd_pfn, &pmem->pgmap);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* we're attaching a block device, disable raw namespace access */
	devm_namespace_disable(dev, ndns);

	dev_set_drvdata(dev, pmem);
	pmem->phys_addr = res->start;
	pmem->size = resource_size(res);
	fua = nvdimm_has_flush(nd_region);
	अगर (!IS_ENABLED(CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE) || fua < 0) अणु
		dev_warn(dev, "unable to guarantee persistence of writes\n");
		fua = 0;
	पूर्ण

	अगर (!devm_request_mem_region(dev, res->start, resource_size(res),
				dev_name(&ndns->dev))) अणु
		dev_warn(dev, "could not reserve region %pR\n", res);
		वापस -EBUSY;
	पूर्ण

	q = blk_alloc_queue(dev_to_node(dev));
	अगर (!q)
		वापस -ENOMEM;

	pmem->pfn_flags = PFN_DEV;
	pmem->pgmap.ref = &q->q_usage_counter;
	अगर (is_nd_pfn(dev)) अणु
		pmem->pgmap.type = MEMORY_DEVICE_FS_DAX;
		pmem->pgmap.ops = &fsdax_pagemap_ops;
		addr = devm_memremap_pages(dev, &pmem->pgmap);
		pfn_sb = nd_pfn->pfn_sb;
		pmem->data_offset = le64_to_cpu(pfn_sb->dataoff);
		pmem->pfn_pad = resource_size(res) -
			range_len(&pmem->pgmap.range);
		pmem->pfn_flags |= PFN_MAP;
		bb_range = pmem->pgmap.range;
		bb_range.start += pmem->data_offset;
	पूर्ण अन्यथा अगर (pmem_should_map_pages(dev)) अणु
		pmem->pgmap.range.start = res->start;
		pmem->pgmap.range.end = res->end;
		pmem->pgmap.nr_range = 1;
		pmem->pgmap.type = MEMORY_DEVICE_FS_DAX;
		pmem->pgmap.ops = &fsdax_pagemap_ops;
		addr = devm_memremap_pages(dev, &pmem->pgmap);
		pmem->pfn_flags |= PFN_MAP;
		bb_range = pmem->pgmap.range;
	पूर्ण अन्यथा अणु
		अगर (devm_add_action_or_reset(dev, pmem_release_queue,
					&pmem->pgmap))
			वापस -ENOMEM;
		addr = devm_memremap(dev, pmem->phys_addr,
				pmem->size, ARCH_MEMREMAP_PMEM);
		bb_range.start =  res->start;
		bb_range.end = res->end;
	पूर्ण

	अगर (IS_ERR(addr))
		वापस PTR_ERR(addr);
	pmem->virt_addr = addr;

	blk_queue_ग_लिखो_cache(q, true, fua);
	blk_queue_physical_block_size(q, PAGE_SIZE);
	blk_queue_logical_block_size(q, pmem_sector_size(ndns));
	blk_queue_max_hw_sectors(q, अच_पूर्णांक_उच्च);
	blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
	अगर (pmem->pfn_flags & PFN_MAP)
		blk_queue_flag_set(QUEUE_FLAG_DAX, q);

	disk = alloc_disk_node(0, nid);
	अगर (!disk)
		वापस -ENOMEM;
	pmem->disk = disk;

	disk->fops		= &pmem_fops;
	disk->queue		= q;
	disk->flags		= GENHD_FL_EXT_DEVT;
	disk->निजी_data	= pmem;
	nvdimm_namespace_disk_name(ndns, disk->disk_name);
	set_capacity(disk, (pmem->size - pmem->pfn_pad - pmem->data_offset)
			/ 512);
	अगर (devm_init_badblocks(dev, &pmem->bb))
		वापस -ENOMEM;
	nvdimm_badblocks_populate(nd_region, &pmem->bb, &bb_range);
	disk->bb = &pmem->bb;

	अगर (is_nvdimm_sync(nd_region))
		flags = DAXDEV_F_SYNC;
	dax_dev = alloc_dax(pmem, disk->disk_name, &pmem_dax_ops, flags);
	अगर (IS_ERR(dax_dev)) अणु
		put_disk(disk);
		वापस PTR_ERR(dax_dev);
	पूर्ण
	dax_ग_लिखो_cache(dax_dev, nvdimm_has_cache(nd_region));
	pmem->dax_dev = dax_dev;
	gendev = disk_to_dev(disk);
	gendev->groups = pmem_attribute_groups;

	device_add_disk(dev, disk, शून्य);
	अगर (devm_add_action_or_reset(dev, pmem_release_disk, pmem))
		वापस -ENOMEM;

	nvdimm_check_and_set_ro(disk);

	pmem->bb_state = sysfs_get_dirent(disk_to_dev(disk)->kobj.sd,
					  "badblocks");
	अगर (!pmem->bb_state)
		dev_warn(dev, "'badblocks' notification disabled\n");

	वापस 0;
पूर्ण

अटल पूर्णांक nd_pmem_probe(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा nd_namespace_common *ndns;

	ndns = nvdimm_namespace_common_probe(dev);
	अगर (IS_ERR(ndns))
		वापस PTR_ERR(ndns);

	अगर (is_nd_btt(dev))
		वापस nvdimm_namespace_attach_btt(ndns);

	अगर (is_nd_pfn(dev))
		वापस pmem_attach_disk(dev, ndns);

	ret = devm_namespace_enable(dev, ndns, nd_info_block_reserve());
	अगर (ret)
		वापस ret;

	ret = nd_btt_probe(dev, ndns);
	अगर (ret == 0)
		वापस -ENXIO;

	/*
	 * We have two failure conditions here, there is no
	 * info reserver block or we found a valid info reserve block
	 * but failed to initialize the pfn superblock.
	 *
	 * For the first हाल consider namespace as a raw pmem namespace
	 * and attach a disk.
	 *
	 * For the latter, consider this a success and advance the namespace
	 * seed.
	 */
	ret = nd_pfn_probe(dev, ndns);
	अगर (ret == 0)
		वापस -ENXIO;
	अन्यथा अगर (ret == -EOPNOTSUPP)
		वापस ret;

	ret = nd_dax_probe(dev, ndns);
	अगर (ret == 0)
		वापस -ENXIO;
	अन्यथा अगर (ret == -EOPNOTSUPP)
		वापस ret;

	/* probe complete, attach handles namespace enabling */
	devm_namespace_disable(dev, ndns);

	वापस pmem_attach_disk(dev, ndns);
पूर्ण

अटल व्योम nd_pmem_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा pmem_device *pmem = dev_get_drvdata(dev);

	अगर (is_nd_btt(dev))
		nvdimm_namespace_detach_btt(to_nd_btt(dev));
	अन्यथा अणु
		/*
		 * Note, this assumes nd_device_lock() context to not
		 * race nd_pmem_notअगरy()
		 */
		sysfs_put(pmem->bb_state);
		pmem->bb_state = शून्य;
	पूर्ण
	nvdimm_flush(to_nd_region(dev->parent), शून्य);
पूर्ण

अटल व्योम nd_pmem_shutकरोwn(काष्ठा device *dev)
अणु
	nvdimm_flush(to_nd_region(dev->parent), शून्य);
पूर्ण

अटल व्योम pmem_revalidate_poison(काष्ठा device *dev)
अणु
	काष्ठा nd_region *nd_region;
	resource_माप_प्रकार offset = 0, end_trunc = 0;
	काष्ठा nd_namespace_common *ndns;
	काष्ठा nd_namespace_io *nsio;
	काष्ठा badblocks *bb;
	काष्ठा range range;
	काष्ठा kernfs_node *bb_state;

	अगर (is_nd_btt(dev)) अणु
		काष्ठा nd_btt *nd_btt = to_nd_btt(dev);

		ndns = nd_btt->ndns;
		nd_region = to_nd_region(ndns->dev.parent);
		nsio = to_nd_namespace_io(&ndns->dev);
		bb = &nsio->bb;
		bb_state = शून्य;
	पूर्ण अन्यथा अणु
		काष्ठा pmem_device *pmem = dev_get_drvdata(dev);

		nd_region = to_region(pmem);
		bb = &pmem->bb;
		bb_state = pmem->bb_state;

		अगर (is_nd_pfn(dev)) अणु
			काष्ठा nd_pfn *nd_pfn = to_nd_pfn(dev);
			काष्ठा nd_pfn_sb *pfn_sb = nd_pfn->pfn_sb;

			ndns = nd_pfn->ndns;
			offset = pmem->data_offset +
					__le32_to_cpu(pfn_sb->start_pad);
			end_trunc = __le32_to_cpu(pfn_sb->end_trunc);
		पूर्ण अन्यथा अणु
			ndns = to_ndns(dev);
		पूर्ण

		nsio = to_nd_namespace_io(&ndns->dev);
	पूर्ण

	range.start = nsio->res.start + offset;
	range.end = nsio->res.end - end_trunc;
	nvdimm_badblocks_populate(nd_region, bb, &range);
	अगर (bb_state)
		sysfs_notअगरy_dirent(bb_state);
पूर्ण

अटल व्योम pmem_revalidate_region(काष्ठा device *dev)
अणु
	काष्ठा pmem_device *pmem;

	अगर (is_nd_btt(dev)) अणु
		काष्ठा nd_btt *nd_btt = to_nd_btt(dev);
		काष्ठा btt *btt = nd_btt->btt;

		nvdimm_check_and_set_ro(btt->btt_disk);
		वापस;
	पूर्ण

	pmem = dev_get_drvdata(dev);
	nvdimm_check_and_set_ro(pmem->disk);
पूर्ण

अटल व्योम nd_pmem_notअगरy(काष्ठा device *dev, क्रमागत nvdimm_event event)
अणु
	चयन (event) अणु
	हाल NVDIMM_REVALIDATE_POISON:
		pmem_revalidate_poison(dev);
		अवरोध;
	हाल NVDIMM_REVALIDATE_REGION:
		pmem_revalidate_region(dev);
		अवरोध;
	शेष:
		dev_WARN_ONCE(dev, 1, "notify: unknown event: %d\n", event);
		अवरोध;
	पूर्ण
पूर्ण

MODULE_ALIAS("pmem");
MODULE_ALIAS_ND_DEVICE(ND_DEVICE_NAMESPACE_IO);
MODULE_ALIAS_ND_DEVICE(ND_DEVICE_NAMESPACE_PMEM);
अटल काष्ठा nd_device_driver nd_pmem_driver = अणु
	.probe = nd_pmem_probe,
	.हटाओ = nd_pmem_हटाओ,
	.notअगरy = nd_pmem_notअगरy,
	.shutकरोwn = nd_pmem_shutकरोwn,
	.drv = अणु
		.name = "nd_pmem",
	पूर्ण,
	.type = ND_DRIVER_NAMESPACE_IO | ND_DRIVER_NAMESPACE_PMEM,
पूर्ण;

module_nd_driver(nd_pmem_driver);

MODULE_AUTHOR("Ross Zwisler <ross.zwisler@linux.intel.com>");
MODULE_LICENSE("GPL v2");
