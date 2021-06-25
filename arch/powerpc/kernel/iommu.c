<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001 Mike Corrigan & Dave Engebretsen, IBM Corporation
 * 
 * Reग_लिखो, cleanup, new allocation schemes, भव merging: 
 * Copyright (C) 2004 Olof Johansson, IBM Corporation
 *               and  Ben. Herrenschmidt, IBM Corporation
 *
 * Dynamic DMA mapping support, bus-independent parts.
 */


#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/iommu-helper.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/hash.h>
#समावेश <linux/fault-inject.h>
#समावेश <linux/pci.h>
#समावेश <linux/iommu.h>
#समावेश <linux/sched.h>
#समावेश <linux/debugfs.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/kdump.h>
#समावेश <यंत्र/fadump.h>
#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/tce.h>
#समावेश <यंत्र/mmu_context.h>

#घोषणा DBG(...)

#अगर_घोषित CONFIG_IOMMU_DEBUGFS
अटल पूर्णांक iommu_debugfs_weight_get(व्योम *data, u64 *val)
अणु
	काष्ठा iommu_table *tbl = data;
	*val = biपंचांगap_weight(tbl->it_map, tbl->it_size);
	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(iommu_debugfs_fops_weight, iommu_debugfs_weight_get, शून्य, "%llu\n");

अटल व्योम iommu_debugfs_add(काष्ठा iommu_table *tbl)
अणु
	अक्षर name[10];
	काष्ठा dentry *liobn_entry;

	प्र_लिखो(name, "%08lx", tbl->it_index);
	liobn_entry = debugfs_create_dir(name, iommu_debugfs_dir);

	debugfs_create_file_unsafe("weight", 0400, liobn_entry, tbl, &iommu_debugfs_fops_weight);
	debugfs_create_uदीर्घ("it_size", 0400, liobn_entry, &tbl->it_size);
	debugfs_create_uदीर्घ("it_page_shift", 0400, liobn_entry, &tbl->it_page_shअगरt);
	debugfs_create_uदीर्घ("it_reserved_start", 0400, liobn_entry, &tbl->it_reserved_start);
	debugfs_create_uदीर्घ("it_reserved_end", 0400, liobn_entry, &tbl->it_reserved_end);
	debugfs_create_uदीर्घ("it_indirect_levels", 0400, liobn_entry, &tbl->it_indirect_levels);
	debugfs_create_uदीर्घ("it_level_size", 0400, liobn_entry, &tbl->it_level_size);
पूर्ण

अटल व्योम iommu_debugfs_del(काष्ठा iommu_table *tbl)
अणु
	अक्षर name[10];
	काष्ठा dentry *liobn_entry;

	प्र_लिखो(name, "%08lx", tbl->it_index);
	liobn_entry = debugfs_lookup(name, iommu_debugfs_dir);
	debugfs_हटाओ(liobn_entry);
पूर्ण
#अन्यथा
अटल व्योम iommu_debugfs_add(काष्ठा iommu_table *tbl)अणुपूर्ण
अटल व्योम iommu_debugfs_del(काष्ठा iommu_table *tbl)अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक novmerge;

अटल व्योम __iommu_मुक्त(काष्ठा iommu_table *, dma_addr_t, अचिन्हित पूर्णांक);

अटल पूर्णांक __init setup_iommu(अक्षर *str)
अणु
	अगर (!म_भेद(str, "novmerge"))
		novmerge = 1;
	अन्यथा अगर (!म_भेद(str, "vmerge"))
		novmerge = 0;
	वापस 1;
पूर्ण

__setup("iommu=", setup_iommu);

अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, iommu_pool_hash);

/*
 * We precalculate the hash to aव्योम करोing it on every allocation.
 *
 * The hash is important to spपढ़ो CPUs across all the pools. For example,
 * on a POWER7 with 4 way SMT we want पूर्णांकerrupts on the primary thपढ़ोs and
 * with 4 pools all primary thपढ़ोs would map to the same pool.
 */
अटल पूर्णांक __init setup_iommu_pool_hash(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_possible_cpu(i)
		per_cpu(iommu_pool_hash, i) = hash_32(i, IOMMU_POOL_HASHBITS);

	वापस 0;
पूर्ण
subsys_initcall(setup_iommu_pool_hash);

#अगर_घोषित CONFIG_FAIL_IOMMU

अटल DECLARE_FAULT_ATTR(fail_iommu);

अटल पूर्णांक __init setup_fail_iommu(अक्षर *str)
अणु
	वापस setup_fault_attr(&fail_iommu, str);
पूर्ण
__setup("fail_iommu=", setup_fail_iommu);

अटल bool should_fail_iommu(काष्ठा device *dev)
अणु
	वापस dev->archdata.fail_iommu && should_fail(&fail_iommu, 1);
पूर्ण

अटल पूर्णांक __init fail_iommu_debugfs(व्योम)
अणु
	काष्ठा dentry *dir = fault_create_debugfs_attr("fail_iommu",
						       शून्य, &fail_iommu);

	वापस PTR_ERR_OR_ZERO(dir);
पूर्ण
late_initcall(fail_iommu_debugfs);

अटल sमाप_प्रकार fail_iommu_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", dev->archdata.fail_iommu);
पूर्ण

अटल sमाप_प्रकार fail_iommu_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	पूर्णांक i;

	अगर (count > 0 && माला_पूछो(buf, "%d", &i) > 0)
		dev->archdata.fail_iommu = (i == 0) ? 0 : 1;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(fail_iommu);

अटल पूर्णांक fail_iommu_bus_notअगरy(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा device *dev = data;

	अगर (action == BUS_NOTIFY_ADD_DEVICE) अणु
		अगर (device_create_file(dev, &dev_attr_fail_iommu))
			pr_warn("Unable to create IOMMU fault injection sysfs "
				"entries\n");
	पूर्ण अन्यथा अगर (action == BUS_NOTIFY_DEL_DEVICE) अणु
		device_हटाओ_file(dev, &dev_attr_fail_iommu);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block fail_iommu_bus_notअगरier = अणु
	.notअगरier_call = fail_iommu_bus_notअगरy
पूर्ण;

अटल पूर्णांक __init fail_iommu_setup(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	bus_रेजिस्टर_notअगरier(&pci_bus_type, &fail_iommu_bus_notअगरier);
#पूर्ण_अगर
#अगर_घोषित CONFIG_IBMVIO
	bus_रेजिस्टर_notअगरier(&vio_bus_type, &fail_iommu_bus_notअगरier);
#पूर्ण_अगर

	वापस 0;
पूर्ण
/*
 * Must execute after PCI and VIO subप्रणाली have initialised but beक्रमe
 * devices are probed.
 */
arch_initcall(fail_iommu_setup);
#अन्यथा
अटल अंतरभूत bool should_fail_iommu(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित दीर्घ iommu_range_alloc(काष्ठा device *dev,
				       काष्ठा iommu_table *tbl,
                                       अचिन्हित दीर्घ npages,
                                       अचिन्हित दीर्घ *handle,
                                       अचिन्हित दीर्घ mask,
                                       अचिन्हित पूर्णांक align_order)
अणु 
	अचिन्हित दीर्घ n, end, start;
	अचिन्हित दीर्घ limit;
	पूर्णांक largealloc = npages > 15;
	पूर्णांक pass = 0;
	अचिन्हित दीर्घ align_mask;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक pool_nr;
	काष्ठा iommu_pool *pool;

	align_mask = (1ull << align_order) - 1;

	/* This allocator was derived from x86_64's bit string search */

	/* Sanity check */
	अगर (unlikely(npages == 0)) अणु
		अगर (prपूर्णांकk_ratelimit())
			WARN_ON(1);
		वापस DMA_MAPPING_ERROR;
	पूर्ण

	अगर (should_fail_iommu(dev))
		वापस DMA_MAPPING_ERROR;

	/*
	 * We करोn't need to disable preemption here because any CPU can
	 * safely use any IOMMU pool.
	 */
	pool_nr = raw_cpu_पढ़ो(iommu_pool_hash) & (tbl->nr_pools - 1);

	अगर (largealloc)
		pool = &(tbl->large_pool);
	अन्यथा
		pool = &(tbl->pools[pool_nr]);

	spin_lock_irqsave(&(pool->lock), flags);

again:
	अगर ((pass == 0) && handle && *handle &&
	    (*handle >= pool->start) && (*handle < pool->end))
		start = *handle;
	अन्यथा
		start = pool->hपूर्णांक;

	limit = pool->end;

	/* The हाल below can happen अगर we have a small segment appended
	 * to a large, or when the previous alloc was at the very end of
	 * the available space. If so, go back to the initial start.
	 */
	अगर (start >= limit)
		start = pool->start;

	अगर (limit + tbl->it_offset > mask) अणु
		limit = mask - tbl->it_offset + 1;
		/* If we're स्थिरrained on address range, first try
		 * at the masked hपूर्णांक to aव्योम O(n) search complनिकासy,
		 * but on second pass, start at 0 in pool 0.
		 */
		अगर ((start & mask) >= limit || pass > 0) अणु
			spin_unlock(&(pool->lock));
			pool = &(tbl->pools[0]);
			spin_lock(&(pool->lock));
			start = pool->start;
		पूर्ण अन्यथा अणु
			start &= mask;
		पूर्ण
	पूर्ण

	n = iommu_area_alloc(tbl->it_map, limit, start, npages, tbl->it_offset,
			dma_get_seg_boundary_nr_pages(dev, tbl->it_page_shअगरt),
			align_mask);
	अगर (n == -1) अणु
		अगर (likely(pass == 0)) अणु
			/* First try the pool from the start */
			pool->hपूर्णांक = pool->start;
			pass++;
			जाओ again;

		पूर्ण अन्यथा अगर (pass <= tbl->nr_pools) अणु
			/* Now try scanning all the other pools */
			spin_unlock(&(pool->lock));
			pool_nr = (pool_nr + 1) & (tbl->nr_pools - 1);
			pool = &tbl->pools[pool_nr];
			spin_lock(&(pool->lock));
			pool->hपूर्णांक = pool->start;
			pass++;
			जाओ again;

		पूर्ण अन्यथा अगर (pass == tbl->nr_pools + 1) अणु
			/* Last resort: try largepool */
			spin_unlock(&pool->lock);
			pool = &tbl->large_pool;
			spin_lock(&pool->lock);
			pool->hपूर्णांक = pool->start;
			pass++;
			जाओ again;

		पूर्ण अन्यथा अणु
			/* Give up */
			spin_unlock_irqrestore(&(pool->lock), flags);
			वापस DMA_MAPPING_ERROR;
		पूर्ण
	पूर्ण

	end = n + npages;

	/* Bump the hपूर्णांक to a new block क्रम small allocs. */
	अगर (largealloc) अणु
		/* Don't bump to new block to aव्योम fragmentation */
		pool->hपूर्णांक = end;
	पूर्ण अन्यथा अणु
		/* Overflow will be taken care of at the next allocation */
		pool->hपूर्णांक = (end + tbl->it_blocksize - 1) &
		                ~(tbl->it_blocksize - 1);
	पूर्ण

	/* Update handle क्रम SG allocations */
	अगर (handle)
		*handle = end;

	spin_unlock_irqrestore(&(pool->lock), flags);

	वापस n;
पूर्ण

अटल dma_addr_t iommu_alloc(काष्ठा device *dev, काष्ठा iommu_table *tbl,
			      व्योम *page, अचिन्हित पूर्णांक npages,
			      क्रमागत dma_data_direction direction,
			      अचिन्हित दीर्घ mask, अचिन्हित पूर्णांक align_order,
			      अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित दीर्घ entry;
	dma_addr_t ret = DMA_MAPPING_ERROR;
	पूर्णांक build_fail;

	entry = iommu_range_alloc(dev, tbl, npages, शून्य, mask, align_order);

	अगर (unlikely(entry == DMA_MAPPING_ERROR))
		वापस DMA_MAPPING_ERROR;

	entry += tbl->it_offset;	/* Offset पूर्णांकo real TCE table */
	ret = entry << tbl->it_page_shअगरt;	/* Set the वापस dma address */

	/* Put the TCEs in the HW table */
	build_fail = tbl->it_ops->set(tbl, entry, npages,
				      (अचिन्हित दीर्घ)page &
				      IOMMU_PAGE_MASK(tbl), direction, attrs);

	/* tbl->it_ops->set() only वापसs non-zero क्रम transient errors.
	 * Clean up the table biपंचांगap in this हाल and वापस
	 * DMA_MAPPING_ERROR. For all other errors the functionality is
	 * not altered.
	 */
	अगर (unlikely(build_fail)) अणु
		__iommu_मुक्त(tbl, ret, npages);
		वापस DMA_MAPPING_ERROR;
	पूर्ण

	/* Flush/invalidate TLB caches अगर necessary */
	अगर (tbl->it_ops->flush)
		tbl->it_ops->flush(tbl);

	/* Make sure updates are seen by hardware */
	mb();

	वापस ret;
पूर्ण

अटल bool iommu_मुक्त_check(काष्ठा iommu_table *tbl, dma_addr_t dma_addr,
			     अचिन्हित पूर्णांक npages)
अणु
	अचिन्हित दीर्घ entry, मुक्त_entry;

	entry = dma_addr >> tbl->it_page_shअगरt;
	मुक्त_entry = entry - tbl->it_offset;

	अगर (((मुक्त_entry + npages) > tbl->it_size) ||
	    (entry < tbl->it_offset)) अणु
		अगर (prपूर्णांकk_ratelimit()) अणु
			prपूर्णांकk(KERN_INFO "iommu_free: invalid entry\n");
			prपूर्णांकk(KERN_INFO "\tentry     = 0x%lx\n", entry); 
			prपूर्णांकk(KERN_INFO "\tdma_addr  = 0x%llx\n", (u64)dma_addr);
			prपूर्णांकk(KERN_INFO "\tTable     = 0x%llx\n", (u64)tbl);
			prपूर्णांकk(KERN_INFO "\tbus#      = 0x%llx\n", (u64)tbl->it_busno);
			prपूर्णांकk(KERN_INFO "\tsize      = 0x%llx\n", (u64)tbl->it_size);
			prपूर्णांकk(KERN_INFO "\tstartOff  = 0x%llx\n", (u64)tbl->it_offset);
			prपूर्णांकk(KERN_INFO "\tindex     = 0x%llx\n", (u64)tbl->it_index);
			WARN_ON(1);
		पूर्ण

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा iommu_pool *get_pool(काष्ठा iommu_table *tbl,
				   अचिन्हित दीर्घ entry)
अणु
	काष्ठा iommu_pool *p;
	अचिन्हित दीर्घ largepool_start = tbl->large_pool.start;

	/* The large pool is the last pool at the top of the table */
	अगर (entry >= largepool_start) अणु
		p = &tbl->large_pool;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक pool_nr = entry / tbl->poolsize;

		BUG_ON(pool_nr > tbl->nr_pools);
		p = &tbl->pools[pool_nr];
	पूर्ण

	वापस p;
पूर्ण

अटल व्योम __iommu_मुक्त(काष्ठा iommu_table *tbl, dma_addr_t dma_addr,
			 अचिन्हित पूर्णांक npages)
अणु
	अचिन्हित दीर्घ entry, मुक्त_entry;
	अचिन्हित दीर्घ flags;
	काष्ठा iommu_pool *pool;

	entry = dma_addr >> tbl->it_page_shअगरt;
	मुक्त_entry = entry - tbl->it_offset;

	pool = get_pool(tbl, मुक्त_entry);

	अगर (!iommu_मुक्त_check(tbl, dma_addr, npages))
		वापस;

	tbl->it_ops->clear(tbl, entry, npages);

	spin_lock_irqsave(&(pool->lock), flags);
	biपंचांगap_clear(tbl->it_map, मुक्त_entry, npages);
	spin_unlock_irqrestore(&(pool->lock), flags);
पूर्ण

अटल व्योम iommu_मुक्त(काष्ठा iommu_table *tbl, dma_addr_t dma_addr,
		अचिन्हित पूर्णांक npages)
अणु
	__iommu_मुक्त(tbl, dma_addr, npages);

	/* Make sure TLB cache is flushed अगर the HW needs it. We करो
	 * not करो an mb() here on purpose, it is not needed on any of
	 * the current platक्रमms.
	 */
	अगर (tbl->it_ops->flush)
		tbl->it_ops->flush(tbl);
पूर्ण

पूर्णांक ppc_iommu_map_sg(काष्ठा device *dev, काष्ठा iommu_table *tbl,
		     काष्ठा scatterlist *sglist, पूर्णांक nelems,
		     अचिन्हित दीर्घ mask, क्रमागत dma_data_direction direction,
		     अचिन्हित दीर्घ attrs)
अणु
	dma_addr_t dma_next = 0, dma_addr;
	काष्ठा scatterlist *s, *outs, *segstart;
	पूर्णांक outcount, incount, i, build_fail = 0;
	अचिन्हित पूर्णांक align;
	अचिन्हित दीर्घ handle;
	अचिन्हित पूर्णांक max_seg_size;

	BUG_ON(direction == DMA_NONE);

	अगर ((nelems == 0) || !tbl)
		वापस 0;

	outs = s = segstart = &sglist[0];
	outcount = 1;
	incount = nelems;
	handle = 0;

	/* Init first segment length क्रम backout at failure */
	outs->dma_length = 0;

	DBG("sg mapping %d elements:\n", nelems);

	max_seg_size = dma_get_max_seg_size(dev);
	क्रम_each_sg(sglist, s, nelems, i) अणु
		अचिन्हित दीर्घ vaddr, npages, entry, slen;

		slen = s->length;
		/* Sanity check */
		अगर (slen == 0) अणु
			dma_next = 0;
			जारी;
		पूर्ण
		/* Allocate iommu entries क्रम that segment */
		vaddr = (अचिन्हित दीर्घ) sg_virt(s);
		npages = iommu_num_pages(vaddr, slen, IOMMU_PAGE_SIZE(tbl));
		align = 0;
		अगर (tbl->it_page_shअगरt < PAGE_SHIFT && slen >= PAGE_SIZE &&
		    (vaddr & ~PAGE_MASK) == 0)
			align = PAGE_SHIFT - tbl->it_page_shअगरt;
		entry = iommu_range_alloc(dev, tbl, npages, &handle,
					  mask >> tbl->it_page_shअगरt, align);

		DBG("  - vaddr: %lx, size: %lx\n", vaddr, slen);

		/* Handle failure */
		अगर (unlikely(entry == DMA_MAPPING_ERROR)) अणु
			अगर (!(attrs & DMA_ATTR_NO_WARN) &&
			    prपूर्णांकk_ratelimit())
				dev_info(dev, "iommu_alloc failed, tbl %p "
					 "vaddr %lx npages %lu\n", tbl, vaddr,
					 npages);
			जाओ failure;
		पूर्ण

		/* Convert entry to a dma_addr_t */
		entry += tbl->it_offset;
		dma_addr = entry << tbl->it_page_shअगरt;
		dma_addr |= (s->offset & ~IOMMU_PAGE_MASK(tbl));

		DBG("  - %lu pages, entry: %lx, dma_addr: %lx\n",
			    npages, entry, dma_addr);

		/* Insert पूर्णांकo HW table */
		build_fail = tbl->it_ops->set(tbl, entry, npages,
					      vaddr & IOMMU_PAGE_MASK(tbl),
					      direction, attrs);
		अगर(unlikely(build_fail))
			जाओ failure;

		/* If we are in an खोलो segment, try merging */
		अगर (segstart != s) अणु
			DBG("  - trying merge...\n");
			/* We cannot merge अगर:
			 * - allocated dma_addr isn't contiguous to previous allocation
			 */
			अगर (novmerge || (dma_addr != dma_next) ||
			    (outs->dma_length + s->length > max_seg_size)) अणु
				/* Can't merge: create a new segment */
				segstart = s;
				outcount++;
				outs = sg_next(outs);
				DBG("    can't merge, new segment.\n");
			पूर्ण अन्यथा अणु
				outs->dma_length += s->length;
				DBG("    merged, new len: %ux\n", outs->dma_length);
			पूर्ण
		पूर्ण

		अगर (segstart == s) अणु
			/* This is a new segment, fill entries */
			DBG("  - filling new segment.\n");
			outs->dma_address = dma_addr;
			outs->dma_length = slen;
		पूर्ण

		/* Calculate next page poपूर्णांकer क्रम contiguous check */
		dma_next = dma_addr + slen;

		DBG("  - dma next is: %lx\n", dma_next);
	पूर्ण

	/* Flush/invalidate TLB caches अगर necessary */
	अगर (tbl->it_ops->flush)
		tbl->it_ops->flush(tbl);

	DBG("mapped %d elements:\n", outcount);

	/* For the sake of ppc_iommu_unmap_sg, we clear out the length in the
	 * next entry of the sglist अगर we didn't fill the list completely
	 */
	अगर (outcount < incount) अणु
		outs = sg_next(outs);
		outs->dma_address = DMA_MAPPING_ERROR;
		outs->dma_length = 0;
	पूर्ण

	/* Make sure updates are seen by hardware */
	mb();

	वापस outcount;

 failure:
	क्रम_each_sg(sglist, s, nelems, i) अणु
		अगर (s->dma_length != 0) अणु
			अचिन्हित दीर्घ vaddr, npages;

			vaddr = s->dma_address & IOMMU_PAGE_MASK(tbl);
			npages = iommu_num_pages(s->dma_address, s->dma_length,
						 IOMMU_PAGE_SIZE(tbl));
			__iommu_मुक्त(tbl, vaddr, npages);
			s->dma_address = DMA_MAPPING_ERROR;
			s->dma_length = 0;
		पूर्ण
		अगर (s == outs)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण


व्योम ppc_iommu_unmap_sg(काष्ठा iommu_table *tbl, काष्ठा scatterlist *sglist,
			पूर्णांक nelems, क्रमागत dma_data_direction direction,
			अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *sg;

	BUG_ON(direction == DMA_NONE);

	अगर (!tbl)
		वापस;

	sg = sglist;
	जबतक (nelems--) अणु
		अचिन्हित पूर्णांक npages;
		dma_addr_t dma_handle = sg->dma_address;

		अगर (sg->dma_length == 0)
			अवरोध;
		npages = iommu_num_pages(dma_handle, sg->dma_length,
					 IOMMU_PAGE_SIZE(tbl));
		__iommu_मुक्त(tbl, dma_handle, npages);
		sg = sg_next(sg);
	पूर्ण

	/* Flush/invalidate TLBs अगर necessary. As क्रम iommu_मुक्त(), we
	 * करो not करो an mb() here, the affected platक्रमms करो not need it
	 * when मुक्तing.
	 */
	अगर (tbl->it_ops->flush)
		tbl->it_ops->flush(tbl);
पूर्ण

अटल व्योम iommu_table_clear(काष्ठा iommu_table *tbl)
अणु
	/*
	 * In हाल of firmware assisted dump प्रणाली goes through clean
	 * reboot process at the समय of प्रणाली crash. Hence it's safe to
	 * clear the TCE entries अगर firmware assisted dump is active.
	 */
	अगर (!is_kdump_kernel() || is_fadump_active()) अणु
		/* Clear the table in हाल firmware left allocations in it */
		tbl->it_ops->clear(tbl, tbl->it_offset, tbl->it_size);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_CRASH_DUMP
	अगर (tbl->it_ops->get) अणु
		अचिन्हित दीर्घ index, tceval, tcecount = 0;

		/* Reserve the existing mappings left by the first kernel. */
		क्रम (index = 0; index < tbl->it_size; index++) अणु
			tceval = tbl->it_ops->get(tbl, index + tbl->it_offset);
			/*
			 * Freed TCE entry contains 0x7fffffffffffffff on JS20
			 */
			अगर (tceval && (tceval != 0x7fffffffffffffffUL)) अणु
				__set_bit(index, tbl->it_map);
				tcecount++;
			पूर्ण
		पूर्ण

		अगर ((tbl->it_size - tcecount) < KDUMP_MIN_TCE_ENTRIES) अणु
			prपूर्णांकk(KERN_WARNING "TCE table is full; freeing ");
			prपूर्णांकk(KERN_WARNING "%d entries for the kdump boot\n",
				KDUMP_MIN_TCE_ENTRIES);
			क्रम (index = tbl->it_size - KDUMP_MIN_TCE_ENTRIES;
				index < tbl->it_size; index++)
				__clear_bit(index, tbl->it_map);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम iommu_table_reserve_pages(काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ res_start, अचिन्हित दीर्घ res_end)
अणु
	पूर्णांक i;

	WARN_ON_ONCE(res_end < res_start);
	/*
	 * Reserve page 0 so it will not be used क्रम any mappings.
	 * This aव्योमs buggy drivers that consider page 0 to be invalid
	 * to crash the machine or even lose data.
	 */
	अगर (tbl->it_offset == 0)
		set_bit(0, tbl->it_map);

	tbl->it_reserved_start = res_start;
	tbl->it_reserved_end = res_end;

	/* Check अगर res_start..res_end isn't empty and overlaps the table */
	अगर (res_start && res_end &&
			(tbl->it_offset + tbl->it_size < res_start ||
			 res_end < tbl->it_offset))
		वापस;

	क्रम (i = tbl->it_reserved_start; i < tbl->it_reserved_end; ++i)
		set_bit(i - tbl->it_offset, tbl->it_map);
पूर्ण

अटल व्योम iommu_table_release_pages(काष्ठा iommu_table *tbl)
अणु
	पूर्णांक i;

	/*
	 * In हाल we have reserved the first bit, we should not emit
	 * the warning below.
	 */
	अगर (tbl->it_offset == 0)
		clear_bit(0, tbl->it_map);

	क्रम (i = tbl->it_reserved_start; i < tbl->it_reserved_end; ++i)
		clear_bit(i - tbl->it_offset, tbl->it_map);
पूर्ण

/*
 * Build a iommu_table काष्ठाure.  This contains a bit map which
 * is used to manage allocation of the tce space.
 */
काष्ठा iommu_table *iommu_init_table(काष्ठा iommu_table *tbl, पूर्णांक nid,
		अचिन्हित दीर्घ res_start, अचिन्हित दीर्घ res_end)
अणु
	अचिन्हित दीर्घ sz;
	अटल पूर्णांक welcomed = 0;
	अचिन्हित पूर्णांक i;
	काष्ठा iommu_pool *p;

	BUG_ON(!tbl->it_ops);

	/* number of bytes needed क्रम the biपंचांगap */
	sz = BITS_TO_LONGS(tbl->it_size) * माप(अचिन्हित दीर्घ);

	tbl->it_map = vzalloc_node(sz, nid);
	अगर (!tbl->it_map) अणु
		pr_err("%s: Can't allocate %ld bytes\n", __func__, sz);
		वापस शून्य;
	पूर्ण

	iommu_table_reserve_pages(tbl, res_start, res_end);

	/* We only split the IOMMU table अगर we have 1GB or more of space */
	अगर ((tbl->it_size << tbl->it_page_shअगरt) >= (1UL * 1024 * 1024 * 1024))
		tbl->nr_pools = IOMMU_NR_POOLS;
	अन्यथा
		tbl->nr_pools = 1;

	/* We reserve the top 1/4 of the table क्रम large allocations */
	tbl->poolsize = (tbl->it_size * 3 / 4) / tbl->nr_pools;

	क्रम (i = 0; i < tbl->nr_pools; i++) अणु
		p = &tbl->pools[i];
		spin_lock_init(&(p->lock));
		p->start = tbl->poolsize * i;
		p->hपूर्णांक = p->start;
		p->end = p->start + tbl->poolsize;
	पूर्ण

	p = &tbl->large_pool;
	spin_lock_init(&(p->lock));
	p->start = tbl->poolsize * i;
	p->hपूर्णांक = p->start;
	p->end = tbl->it_size;

	iommu_table_clear(tbl);

	अगर (!welcomed) अणु
		prपूर्णांकk(KERN_INFO "IOMMU table initialized, virtual merging %s\n",
		       novmerge ? "disabled" : "enabled");
		welcomed = 1;
	पूर्ण

	iommu_debugfs_add(tbl);

	वापस tbl;
पूर्ण

अटल व्योम iommu_table_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा iommu_table *tbl;

	tbl = container_of(kref, काष्ठा iommu_table, it_kref);

	अगर (tbl->it_ops->मुक्त)
		tbl->it_ops->मुक्त(tbl);

	अगर (!tbl->it_map) अणु
		kमुक्त(tbl);
		वापस;
	पूर्ण

	iommu_debugfs_del(tbl);

	iommu_table_release_pages(tbl);

	/* verअगरy that table contains no entries */
	अगर (!biपंचांगap_empty(tbl->it_map, tbl->it_size))
		pr_warn("%s: Unexpected TCEs\n", __func__);

	/* मुक्त biपंचांगap */
	vमुक्त(tbl->it_map);

	/* मुक्त table */
	kमुक्त(tbl);
पूर्ण

काष्ठा iommu_table *iommu_tce_table_get(काष्ठा iommu_table *tbl)
अणु
	अगर (kref_get_unless_zero(&tbl->it_kref))
		वापस tbl;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_tce_table_get);

पूर्णांक iommu_tce_table_put(काष्ठा iommu_table *tbl)
अणु
	अगर (WARN_ON(!tbl))
		वापस 0;

	वापस kref_put(&tbl->it_kref, iommu_table_मुक्त);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_tce_table_put);

/* Creates TCEs क्रम a user provided buffer.  The user buffer must be
 * contiguous real kernel storage (not vदो_स्मृति).  The address passed here
 * comprises a page address and offset पूर्णांकo that page. The dma_addr_t
 * वापसed will poपूर्णांक to the same byte within the page as was passed in.
 */
dma_addr_t iommu_map_page(काष्ठा device *dev, काष्ठा iommu_table *tbl,
			  काष्ठा page *page, अचिन्हित दीर्घ offset, माप_प्रकार size,
			  अचिन्हित दीर्घ mask, क्रमागत dma_data_direction direction,
			  अचिन्हित दीर्घ attrs)
अणु
	dma_addr_t dma_handle = DMA_MAPPING_ERROR;
	व्योम *vaddr;
	अचिन्हित दीर्घ uaddr;
	अचिन्हित पूर्णांक npages, align;

	BUG_ON(direction == DMA_NONE);

	vaddr = page_address(page) + offset;
	uaddr = (अचिन्हित दीर्घ)vaddr;

	अगर (tbl) अणु
		npages = iommu_num_pages(uaddr, size, IOMMU_PAGE_SIZE(tbl));
		align = 0;
		अगर (tbl->it_page_shअगरt < PAGE_SHIFT && size >= PAGE_SIZE &&
		    ((अचिन्हित दीर्घ)vaddr & ~PAGE_MASK) == 0)
			align = PAGE_SHIFT - tbl->it_page_shअगरt;

		dma_handle = iommu_alloc(dev, tbl, vaddr, npages, direction,
					 mask >> tbl->it_page_shअगरt, align,
					 attrs);
		अगर (dma_handle == DMA_MAPPING_ERROR) अणु
			अगर (!(attrs & DMA_ATTR_NO_WARN) &&
			    prपूर्णांकk_ratelimit())  अणु
				dev_info(dev, "iommu_alloc failed, tbl %p "
					 "vaddr %p npages %d\n", tbl, vaddr,
					 npages);
			पूर्ण
		पूर्ण अन्यथा
			dma_handle |= (uaddr & ~IOMMU_PAGE_MASK(tbl));
	पूर्ण

	वापस dma_handle;
पूर्ण

व्योम iommu_unmap_page(काष्ठा iommu_table *tbl, dma_addr_t dma_handle,
		      माप_प्रकार size, क्रमागत dma_data_direction direction,
		      अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित पूर्णांक npages;

	BUG_ON(direction == DMA_NONE);

	अगर (tbl) अणु
		npages = iommu_num_pages(dma_handle, size,
					 IOMMU_PAGE_SIZE(tbl));
		iommu_मुक्त(tbl, dma_handle, npages);
	पूर्ण
पूर्ण

/* Allocates a contiguous real buffer and creates mappings over it.
 * Returns the भव address of the buffer and sets dma_handle
 * to the dma address (mapping) of the first page.
 */
व्योम *iommu_alloc_coherent(काष्ठा device *dev, काष्ठा iommu_table *tbl,
			   माप_प्रकार size,	dma_addr_t *dma_handle,
			   अचिन्हित दीर्घ mask, gfp_t flag, पूर्णांक node)
अणु
	व्योम *ret = शून्य;
	dma_addr_t mapping;
	अचिन्हित पूर्णांक order;
	अचिन्हित पूर्णांक nio_pages, io_order;
	काष्ठा page *page;

	size = PAGE_ALIGN(size);
	order = get_order(size);

 	/*
	 * Client asked क्रम way too much space.  This is checked later
	 * anyway.  It is easier to debug here क्रम the drivers than in
	 * the tce tables.
	 */
	अगर (order >= IOMAP_MAX_ORDER) अणु
		dev_info(dev, "iommu_alloc_consistent size too large: 0x%lx\n",
			 size);
		वापस शून्य;
	पूर्ण

	अगर (!tbl)
		वापस शून्य;

	/* Alloc enough pages (and possibly more) */
	page = alloc_pages_node(node, flag, order);
	अगर (!page)
		वापस शून्य;
	ret = page_address(page);
	स_रखो(ret, 0, size);

	/* Set up tces to cover the allocated range */
	nio_pages = size >> tbl->it_page_shअगरt;
	io_order = get_iommu_order(size, tbl);
	mapping = iommu_alloc(dev, tbl, ret, nio_pages, DMA_BIसूचीECTIONAL,
			      mask >> tbl->it_page_shअगरt, io_order, 0);
	अगर (mapping == DMA_MAPPING_ERROR) अणु
		मुक्त_pages((अचिन्हित दीर्घ)ret, order);
		वापस शून्य;
	पूर्ण
	*dma_handle = mapping;
	वापस ret;
पूर्ण

व्योम iommu_मुक्त_coherent(काष्ठा iommu_table *tbl, माप_प्रकार size,
			 व्योम *vaddr, dma_addr_t dma_handle)
अणु
	अगर (tbl) अणु
		अचिन्हित पूर्णांक nio_pages;

		size = PAGE_ALIGN(size);
		nio_pages = size >> tbl->it_page_shअगरt;
		iommu_मुक्त(tbl, dma_handle, nio_pages);
		size = PAGE_ALIGN(size);
		मुक्त_pages((अचिन्हित दीर्घ)vaddr, get_order(size));
	पूर्ण
पूर्ण

अचिन्हित दीर्घ iommu_direction_to_tce_perm(क्रमागत dma_data_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_BIसूचीECTIONAL:
		वापस TCE_PCI_READ | TCE_PCI_WRITE;
	हाल DMA_FROM_DEVICE:
		वापस TCE_PCI_WRITE;
	हाल DMA_TO_DEVICE:
		वापस TCE_PCI_READ;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(iommu_direction_to_tce_perm);

#अगर_घोषित CONFIG_IOMMU_API
/*
 * SPAPR TCE API
 */
अटल व्योम group_release(व्योम *iommu_data)
अणु
	काष्ठा iommu_table_group *table_group = iommu_data;

	table_group->group = शून्य;
पूर्ण

व्योम iommu_रेजिस्टर_group(काष्ठा iommu_table_group *table_group,
		पूर्णांक pci_करोमुख्य_number, अचिन्हित दीर्घ pe_num)
अणु
	काष्ठा iommu_group *grp;
	अक्षर *name;

	grp = iommu_group_alloc();
	अगर (IS_ERR(grp)) अणु
		pr_warn("powerpc iommu api: cannot create new group, err=%ld\n",
				PTR_ERR(grp));
		वापस;
	पूर्ण
	table_group->group = grp;
	iommu_group_set_iommudata(grp, table_group, group_release);
	name = kaप्र_लिखो(GFP_KERNEL, "domain%d-pe%lx",
			pci_करोमुख्य_number, pe_num);
	अगर (!name)
		वापस;
	iommu_group_set_name(grp, name);
	kमुक्त(name);
पूर्ण

क्रमागत dma_data_direction iommu_tce_direction(अचिन्हित दीर्घ tce)
अणु
	अगर ((tce & TCE_PCI_READ) && (tce & TCE_PCI_WRITE))
		वापस DMA_BIसूचीECTIONAL;
	अन्यथा अगर (tce & TCE_PCI_READ)
		वापस DMA_TO_DEVICE;
	अन्यथा अगर (tce & TCE_PCI_WRITE)
		वापस DMA_FROM_DEVICE;
	अन्यथा
		वापस DMA_NONE;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_tce_direction);

व्योम iommu_flush_tce(काष्ठा iommu_table *tbl)
अणु
	/* Flush/invalidate TLB caches अगर necessary */
	अगर (tbl->it_ops->flush)
		tbl->it_ops->flush(tbl);

	/* Make sure updates are seen by hardware */
	mb();
पूर्ण
EXPORT_SYMBOL_GPL(iommu_flush_tce);

पूर्णांक iommu_tce_check_ioba(अचिन्हित दीर्घ page_shअगरt,
		अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ ioba, अचिन्हित दीर्घ npages)
अणु
	अचिन्हित दीर्घ mask = (1UL << page_shअगरt) - 1;

	अगर (ioba & mask)
		वापस -EINVAL;

	ioba >>= page_shअगरt;
	अगर (ioba < offset)
		वापस -EINVAL;

	अगर ((ioba + 1) > (offset + size))
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_tce_check_ioba);

पूर्णांक iommu_tce_check_gpa(अचिन्हित दीर्घ page_shअगरt, अचिन्हित दीर्घ gpa)
अणु
	अचिन्हित दीर्घ mask = (1UL << page_shअगरt) - 1;

	अगर (gpa & mask)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_tce_check_gpa);

बाह्य दीर्घ iommu_tce_xchg_no_समाप्त(काष्ठा mm_काष्ठा *mm,
		काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ *hpa,
		क्रमागत dma_data_direction *direction)
अणु
	दीर्घ ret;
	अचिन्हित दीर्घ size = 0;

	ret = tbl->it_ops->xchg_no_समाप्त(tbl, entry, hpa, direction, false);
	अगर (!ret && ((*direction == DMA_FROM_DEVICE) ||
			(*direction == DMA_BIसूचीECTIONAL)) &&
			!mm_iommu_is_devmem(mm, *hpa, tbl->it_page_shअगरt,
					&size))
		SetPageDirty(pfn_to_page(*hpa >> PAGE_SHIFT));

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_tce_xchg_no_समाप्त);

व्योम iommu_tce_समाप्त(काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ pages)
अणु
	अगर (tbl->it_ops->tce_समाप्त)
		tbl->it_ops->tce_समाप्त(tbl, entry, pages, false);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_tce_समाप्त);

पूर्णांक iommu_take_ownership(काष्ठा iommu_table *tbl)
अणु
	अचिन्हित दीर्घ flags, i, sz = (tbl->it_size + 7) >> 3;
	पूर्णांक ret = 0;

	/*
	 * VFIO करोes not control TCE entries allocation and the guest
	 * can ग_लिखो new TCEs on top of existing ones so iommu_tce_build()
	 * must be able to release old pages. This functionality
	 * requires exchange() callback defined so अगर it is not
	 * implemented, we disallow taking ownership over the table.
	 */
	अगर (!tbl->it_ops->xchg_no_समाप्त)
		वापस -EINVAL;

	spin_lock_irqsave(&tbl->large_pool.lock, flags);
	क्रम (i = 0; i < tbl->nr_pools; i++)
		spin_lock_nest_lock(&tbl->pools[i].lock, &tbl->large_pool.lock);

	iommu_table_release_pages(tbl);

	अगर (!biपंचांगap_empty(tbl->it_map, tbl->it_size)) अणु
		pr_err("iommu_tce: it_map is not empty");
		ret = -EBUSY;
		/* Unकरो iommu_table_release_pages, i.e. restore bit#0, etc */
		iommu_table_reserve_pages(tbl, tbl->it_reserved_start,
				tbl->it_reserved_end);
	पूर्ण अन्यथा अणु
		स_रखो(tbl->it_map, 0xff, sz);
	पूर्ण

	क्रम (i = 0; i < tbl->nr_pools; i++)
		spin_unlock(&tbl->pools[i].lock);
	spin_unlock_irqrestore(&tbl->large_pool.lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_take_ownership);

व्योम iommu_release_ownership(काष्ठा iommu_table *tbl)
अणु
	अचिन्हित दीर्घ flags, i, sz = (tbl->it_size + 7) >> 3;

	spin_lock_irqsave(&tbl->large_pool.lock, flags);
	क्रम (i = 0; i < tbl->nr_pools; i++)
		spin_lock_nest_lock(&tbl->pools[i].lock, &tbl->large_pool.lock);

	स_रखो(tbl->it_map, 0, sz);

	iommu_table_reserve_pages(tbl, tbl->it_reserved_start,
			tbl->it_reserved_end);

	क्रम (i = 0; i < tbl->nr_pools; i++)
		spin_unlock(&tbl->pools[i].lock);
	spin_unlock_irqrestore(&tbl->large_pool.lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_release_ownership);

पूर्णांक iommu_add_device(काष्ठा iommu_table_group *table_group, काष्ठा device *dev)
अणु
	/*
	 * The sysfs entries should be populated beक्रमe
	 * binding IOMMU group. If sysfs entries isn't
	 * पढ़ोy, we simply bail.
	 */
	अगर (!device_is_रेजिस्टरed(dev))
		वापस -ENOENT;

	अगर (device_iommu_mapped(dev)) अणु
		pr_debug("%s: Skipping device %s with iommu group %d\n",
			 __func__, dev_name(dev),
			 iommu_group_id(dev->iommu_group));
		वापस -EBUSY;
	पूर्ण

	pr_debug("%s: Adding %s to iommu group %d\n",
		 __func__, dev_name(dev),  iommu_group_id(table_group->group));

	वापस iommu_group_add_device(table_group->group, dev);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_add_device);

व्योम iommu_del_device(काष्ठा device *dev)
अणु
	/*
	 * Some devices might not have IOMMU table and group
	 * and we needn't detach them from the associated
	 * IOMMU groups
	 */
	अगर (!device_iommu_mapped(dev)) अणु
		pr_debug("iommu_tce: skipping device %s with no tbl\n",
			 dev_name(dev));
		वापस;
	पूर्ण

	iommu_group_हटाओ_device(dev);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_del_device);
#पूर्ण_अगर /* CONFIG_IOMMU_API */
