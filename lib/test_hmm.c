<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This is a module to test the HMM (Heterogeneous Memory Management)
 * mirror and zone device निजी memory migration APIs of the kernel.
 * Userspace programs can रेजिस्टर with the driver to mirror their own address
 * space and can use the device to पढ़ो/ग_लिखो any valid भव address.
 */
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/delay.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/hmm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "test_hmm_uapi.h"

#घोषणा DMIRROR_NDEVICES		2
#घोषणा DMIRROR_RANGE_FAULT_TIMEOUT	1000
#घोषणा DEVMEM_CHUNK_SIZE		(256 * 1024 * 1024U)
#घोषणा DEVMEM_CHUNKS_RESERVE		16

अटल स्थिर काष्ठा dev_pagemap_ops dmirror_devmem_ops;
अटल स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops dmirror_min_ops;
अटल dev_t dmirror_dev;

काष्ठा dmirror_device;

काष्ठा dmirror_bounce अणु
	व्योम			*ptr;
	अचिन्हित दीर्घ		size;
	अचिन्हित दीर्घ		addr;
	अचिन्हित दीर्घ		cpages;
पूर्ण;

#घोषणा DPT_XA_TAG_WRITE 3UL

/*
 * Data काष्ठाure to track address ranges and रेजिस्टर क्रम mmu पूर्णांकerval
 * notअगरier updates.
 */
काष्ठा dmirror_पूर्णांकerval अणु
	काष्ठा mmu_पूर्णांकerval_notअगरier	notअगरier;
	काष्ठा dmirror			*dmirror;
पूर्ण;

/*
 * Data attached to the खोलो device file.
 * Note that it might be shared after a विभाजन().
 */
काष्ठा dmirror अणु
	काष्ठा dmirror_device		*mdevice;
	काष्ठा xarray			pt;
	काष्ठा mmu_पूर्णांकerval_notअगरier	notअगरier;
	काष्ठा mutex			mutex;
पूर्ण;

/*
 * ZONE_DEVICE pages क्रम migration and simulating device memory.
 */
काष्ठा dmirror_chunk अणु
	काष्ठा dev_pagemap	pagemap;
	काष्ठा dmirror_device	*mdevice;
पूर्ण;

/*
 * Per device data.
 */
काष्ठा dmirror_device अणु
	काष्ठा cdev		cdevice;
	काष्ठा hmm_devmem	*devmem;

	अचिन्हित पूर्णांक		devmem_capacity;
	अचिन्हित पूर्णांक		devmem_count;
	काष्ठा dmirror_chunk	**devmem_chunks;
	काष्ठा mutex		devmem_lock;	/* protects the above */

	अचिन्हित दीर्घ		सुस्मृति;
	अचिन्हित दीर्घ		cमुक्त;
	काष्ठा page		*मुक्त_pages;
	spinlock_t		lock;		/* protects the above */
पूर्ण;

अटल काष्ठा dmirror_device dmirror_devices[DMIRROR_NDEVICES];

अटल पूर्णांक dmirror_bounce_init(काष्ठा dmirror_bounce *bounce,
			       अचिन्हित दीर्घ addr,
			       अचिन्हित दीर्घ size)
अणु
	bounce->addr = addr;
	bounce->size = size;
	bounce->cpages = 0;
	bounce->ptr = vदो_स्मृति(size);
	अगर (!bounce->ptr)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम dmirror_bounce_fini(काष्ठा dmirror_bounce *bounce)
अणु
	vमुक्त(bounce->ptr);
पूर्ण

अटल पूर्णांक dmirror_fops_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cdev *cdev = inode->i_cdev;
	काष्ठा dmirror *dmirror;
	पूर्णांक ret;

	/* Mirror this process address space */
	dmirror = kzalloc(माप(*dmirror), GFP_KERNEL);
	अगर (dmirror == शून्य)
		वापस -ENOMEM;

	dmirror->mdevice = container_of(cdev, काष्ठा dmirror_device, cdevice);
	mutex_init(&dmirror->mutex);
	xa_init(&dmirror->pt);

	ret = mmu_पूर्णांकerval_notअगरier_insert(&dmirror->notअगरier, current->mm,
				0, अच_दीर्घ_उच्च & PAGE_MASK, &dmirror_min_ops);
	अगर (ret) अणु
		kमुक्त(dmirror);
		वापस ret;
	पूर्ण

	filp->निजी_data = dmirror;
	वापस 0;
पूर्ण

अटल पूर्णांक dmirror_fops_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा dmirror *dmirror = filp->निजी_data;

	mmu_पूर्णांकerval_notअगरier_हटाओ(&dmirror->notअगरier);
	xa_destroy(&dmirror->pt);
	kमुक्त(dmirror);
	वापस 0;
पूर्ण

अटल काष्ठा dmirror_device *dmirror_page_to_device(काष्ठा page *page)

अणु
	वापस container_of(page->pgmap, काष्ठा dmirror_chunk,
			    pagemap)->mdevice;
पूर्ण

अटल पूर्णांक dmirror_करो_fault(काष्ठा dmirror *dmirror, काष्ठा hmm_range *range)
अणु
	अचिन्हित दीर्घ *pfns = range->hmm_pfns;
	अचिन्हित दीर्घ pfn;

	क्रम (pfn = (range->start >> PAGE_SHIFT);
	     pfn < (range->end >> PAGE_SHIFT);
	     pfn++, pfns++) अणु
		काष्ठा page *page;
		व्योम *entry;

		/*
		 * Since we asked क्रम hmm_range_fault() to populate pages,
		 * it shouldn't वापस an error entry on success.
		 */
		WARN_ON(*pfns & HMM_PFN_ERROR);
		WARN_ON(!(*pfns & HMM_PFN_VALID));

		page = hmm_pfn_to_page(*pfns);
		WARN_ON(!page);

		entry = page;
		अगर (*pfns & HMM_PFN_WRITE)
			entry = xa_tag_poपूर्णांकer(entry, DPT_XA_TAG_WRITE);
		अन्यथा अगर (WARN_ON(range->शेष_flags & HMM_PFN_WRITE))
			वापस -EFAULT;
		entry = xa_store(&dmirror->pt, pfn, entry, GFP_ATOMIC);
		अगर (xa_is_err(entry))
			वापस xa_err(entry);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dmirror_करो_update(काष्ठा dmirror *dmirror, अचिन्हित दीर्घ start,
			      अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ pfn;
	व्योम *entry;

	/*
	 * The XArray करोesn't hold references to pages since it relies on
	 * the mmu notअगरier to clear page poपूर्णांकers when they become stale.
	 * Thereक्रमe, it is OK to just clear the entry.
	 */
	xa_क्रम_each_range(&dmirror->pt, pfn, entry, start >> PAGE_SHIFT,
			  end >> PAGE_SHIFT)
		xa_erase(&dmirror->pt, pfn);
पूर्ण

अटल bool dmirror_पूर्णांकerval_invalidate(काष्ठा mmu_पूर्णांकerval_notअगरier *mni,
				स्थिर काष्ठा mmu_notअगरier_range *range,
				अचिन्हित दीर्घ cur_seq)
अणु
	काष्ठा dmirror *dmirror = container_of(mni, काष्ठा dmirror, notअगरier);

	/*
	 * Ignore invalidation callbacks क्रम device निजी pages since
	 * the invalidation is handled as part of the migration process.
	 */
	अगर (range->event == MMU_NOTIFY_MIGRATE &&
	    range->migrate_pgmap_owner == dmirror->mdevice)
		वापस true;

	अगर (mmu_notअगरier_range_blockable(range))
		mutex_lock(&dmirror->mutex);
	अन्यथा अगर (!mutex_trylock(&dmirror->mutex))
		वापस false;

	mmu_पूर्णांकerval_set_seq(mni, cur_seq);
	dmirror_करो_update(dmirror, range->start, range->end);

	mutex_unlock(&dmirror->mutex);
	वापस true;
पूर्ण

अटल स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops dmirror_min_ops = अणु
	.invalidate = dmirror_पूर्णांकerval_invalidate,
पूर्ण;

अटल पूर्णांक dmirror_range_fault(काष्ठा dmirror *dmirror,
				काष्ठा hmm_range *range)
अणु
	काष्ठा mm_काष्ठा *mm = dmirror->notअगरier.mm;
	अचिन्हित दीर्घ समयout =
		jअगरfies + msecs_to_jअगरfies(HMM_RANGE_DEFAULT_TIMEOUT);
	पूर्णांक ret;

	जबतक (true) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण

		range->notअगरier_seq = mmu_पूर्णांकerval_पढ़ो_begin(range->notअगरier);
		mmap_पढ़ो_lock(mm);
		ret = hmm_range_fault(range);
		mmap_पढ़ो_unlock(mm);
		अगर (ret) अणु
			अगर (ret == -EBUSY)
				जारी;
			जाओ out;
		पूर्ण

		mutex_lock(&dmirror->mutex);
		अगर (mmu_पूर्णांकerval_पढ़ो_retry(range->notअगरier,
					    range->notअगरier_seq)) अणु
			mutex_unlock(&dmirror->mutex);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	ret = dmirror_करो_fault(dmirror, range);

	mutex_unlock(&dmirror->mutex);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक dmirror_fault(काष्ठा dmirror *dmirror, अचिन्हित दीर्घ start,
			 अचिन्हित दीर्घ end, bool ग_लिखो)
अणु
	काष्ठा mm_काष्ठा *mm = dmirror->notअगरier.mm;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ pfns[64];
	काष्ठा hmm_range range = अणु
		.notअगरier = &dmirror->notअगरier,
		.hmm_pfns = pfns,
		.pfn_flags_mask = 0,
		.शेष_flags =
			HMM_PFN_REQ_FAULT | (ग_लिखो ? HMM_PFN_REQ_WRITE : 0),
		.dev_निजी_owner = dmirror->mdevice,
	पूर्ण;
	पूर्णांक ret = 0;

	/* Since the mm is क्रम the mirrored process, get a reference first. */
	अगर (!mmget_not_zero(mm))
		वापस 0;

	क्रम (addr = start; addr < end; addr = range.end) अणु
		range.start = addr;
		range.end = min(addr + (ARRAY_SIZE(pfns) << PAGE_SHIFT), end);

		ret = dmirror_range_fault(dmirror, &range);
		अगर (ret)
			अवरोध;
	पूर्ण

	mmput(mm);
	वापस ret;
पूर्ण

अटल पूर्णांक dmirror_करो_पढ़ो(काष्ठा dmirror *dmirror, अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ end, काष्ठा dmirror_bounce *bounce)
अणु
	अचिन्हित दीर्घ pfn;
	व्योम *ptr;

	ptr = bounce->ptr + ((start - bounce->addr) & PAGE_MASK);

	क्रम (pfn = start >> PAGE_SHIFT; pfn < (end >> PAGE_SHIFT); pfn++) अणु
		व्योम *entry;
		काष्ठा page *page;
		व्योम *पंचांगp;

		entry = xa_load(&dmirror->pt, pfn);
		page = xa_untag_poपूर्णांकer(entry);
		अगर (!page)
			वापस -ENOENT;

		पंचांगp = kmap(page);
		स_नकल(ptr, पंचांगp, PAGE_SIZE);
		kunmap(page);

		ptr += PAGE_SIZE;
		bounce->cpages++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dmirror_पढ़ो(काष्ठा dmirror *dmirror, काष्ठा hmm_dmirror_cmd *cmd)
अणु
	काष्ठा dmirror_bounce bounce;
	अचिन्हित दीर्घ start, end;
	अचिन्हित दीर्घ size = cmd->npages << PAGE_SHIFT;
	पूर्णांक ret;

	start = cmd->addr;
	end = start + size;
	अगर (end < start)
		वापस -EINVAL;

	ret = dmirror_bounce_init(&bounce, start, size);
	अगर (ret)
		वापस ret;

	जबतक (1) अणु
		mutex_lock(&dmirror->mutex);
		ret = dmirror_करो_पढ़ो(dmirror, start, end, &bounce);
		mutex_unlock(&dmirror->mutex);
		अगर (ret != -ENOENT)
			अवरोध;

		start = cmd->addr + (bounce.cpages << PAGE_SHIFT);
		ret = dmirror_fault(dmirror, start, end, false);
		अगर (ret)
			अवरोध;
		cmd->faults++;
	पूर्ण

	अगर (ret == 0) अणु
		अगर (copy_to_user(u64_to_user_ptr(cmd->ptr), bounce.ptr,
				 bounce.size))
			ret = -EFAULT;
	पूर्ण
	cmd->cpages = bounce.cpages;
	dmirror_bounce_fini(&bounce);
	वापस ret;
पूर्ण

अटल पूर्णांक dmirror_करो_ग_लिखो(काष्ठा dmirror *dmirror, अचिन्हित दीर्घ start,
			    अचिन्हित दीर्घ end, काष्ठा dmirror_bounce *bounce)
अणु
	अचिन्हित दीर्घ pfn;
	व्योम *ptr;

	ptr = bounce->ptr + ((start - bounce->addr) & PAGE_MASK);

	क्रम (pfn = start >> PAGE_SHIFT; pfn < (end >> PAGE_SHIFT); pfn++) अणु
		व्योम *entry;
		काष्ठा page *page;
		व्योम *पंचांगp;

		entry = xa_load(&dmirror->pt, pfn);
		page = xa_untag_poपूर्णांकer(entry);
		अगर (!page || xa_poपूर्णांकer_tag(entry) != DPT_XA_TAG_WRITE)
			वापस -ENOENT;

		पंचांगp = kmap(page);
		स_नकल(पंचांगp, ptr, PAGE_SIZE);
		kunmap(page);

		ptr += PAGE_SIZE;
		bounce->cpages++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dmirror_ग_लिखो(काष्ठा dmirror *dmirror, काष्ठा hmm_dmirror_cmd *cmd)
अणु
	काष्ठा dmirror_bounce bounce;
	अचिन्हित दीर्घ start, end;
	अचिन्हित दीर्घ size = cmd->npages << PAGE_SHIFT;
	पूर्णांक ret;

	start = cmd->addr;
	end = start + size;
	अगर (end < start)
		वापस -EINVAL;

	ret = dmirror_bounce_init(&bounce, start, size);
	अगर (ret)
		वापस ret;
	अगर (copy_from_user(bounce.ptr, u64_to_user_ptr(cmd->ptr),
			   bounce.size)) अणु
		ret = -EFAULT;
		जाओ fini;
	पूर्ण

	जबतक (1) अणु
		mutex_lock(&dmirror->mutex);
		ret = dmirror_करो_ग_लिखो(dmirror, start, end, &bounce);
		mutex_unlock(&dmirror->mutex);
		अगर (ret != -ENOENT)
			अवरोध;

		start = cmd->addr + (bounce.cpages << PAGE_SHIFT);
		ret = dmirror_fault(dmirror, start, end, true);
		अगर (ret)
			अवरोध;
		cmd->faults++;
	पूर्ण

fini:
	cmd->cpages = bounce.cpages;
	dmirror_bounce_fini(&bounce);
	वापस ret;
पूर्ण

अटल bool dmirror_allocate_chunk(काष्ठा dmirror_device *mdevice,
				   काष्ठा page **ppage)
अणु
	काष्ठा dmirror_chunk *devmem;
	काष्ठा resource *res;
	अचिन्हित दीर्घ pfn;
	अचिन्हित दीर्घ pfn_first;
	अचिन्हित दीर्घ pfn_last;
	व्योम *ptr;

	devmem = kzalloc(माप(*devmem), GFP_KERNEL);
	अगर (!devmem)
		वापस false;

	res = request_मुक्त_mem_region(&iomem_resource, DEVMEM_CHUNK_SIZE,
				      "hmm_dmirror");
	अगर (IS_ERR(res))
		जाओ err_devmem;

	devmem->pagemap.type = MEMORY_DEVICE_PRIVATE;
	devmem->pagemap.range.start = res->start;
	devmem->pagemap.range.end = res->end;
	devmem->pagemap.nr_range = 1;
	devmem->pagemap.ops = &dmirror_devmem_ops;
	devmem->pagemap.owner = mdevice;

	mutex_lock(&mdevice->devmem_lock);

	अगर (mdevice->devmem_count == mdevice->devmem_capacity) अणु
		काष्ठा dmirror_chunk **new_chunks;
		अचिन्हित पूर्णांक new_capacity;

		new_capacity = mdevice->devmem_capacity +
				DEVMEM_CHUNKS_RESERVE;
		new_chunks = kपुनः_स्मृति(mdevice->devmem_chunks,
				माप(new_chunks[0]) * new_capacity,
				GFP_KERNEL);
		अगर (!new_chunks)
			जाओ err_release;
		mdevice->devmem_capacity = new_capacity;
		mdevice->devmem_chunks = new_chunks;
	पूर्ण

	ptr = memremap_pages(&devmem->pagemap, numa_node_id());
	अगर (IS_ERR(ptr))
		जाओ err_release;

	devmem->mdevice = mdevice;
	pfn_first = devmem->pagemap.range.start >> PAGE_SHIFT;
	pfn_last = pfn_first + (range_len(&devmem->pagemap.range) >> PAGE_SHIFT);
	mdevice->devmem_chunks[mdevice->devmem_count++] = devmem;

	mutex_unlock(&mdevice->devmem_lock);

	pr_info("added new %u MB chunk (total %u chunks, %u MB) PFNs [0x%lx 0x%lx)\n",
		DEVMEM_CHUNK_SIZE / (1024 * 1024),
		mdevice->devmem_count,
		mdevice->devmem_count * (DEVMEM_CHUNK_SIZE / (1024 * 1024)),
		pfn_first, pfn_last);

	spin_lock(&mdevice->lock);
	क्रम (pfn = pfn_first; pfn < pfn_last; pfn++) अणु
		काष्ठा page *page = pfn_to_page(pfn);

		page->zone_device_data = mdevice->मुक्त_pages;
		mdevice->मुक्त_pages = page;
	पूर्ण
	अगर (ppage) अणु
		*ppage = mdevice->मुक्त_pages;
		mdevice->मुक्त_pages = (*ppage)->zone_device_data;
		mdevice->सुस्मृति++;
	पूर्ण
	spin_unlock(&mdevice->lock);

	वापस true;

err_release:
	mutex_unlock(&mdevice->devmem_lock);
	release_mem_region(devmem->pagemap.range.start, range_len(&devmem->pagemap.range));
err_devmem:
	kमुक्त(devmem);

	वापस false;
पूर्ण

अटल काष्ठा page *dmirror_devmem_alloc_page(काष्ठा dmirror_device *mdevice)
अणु
	काष्ठा page *dpage = शून्य;
	काष्ठा page *rpage;

	/*
	 * This is a fake device so we alloc real प्रणाली memory to store
	 * our device memory.
	 */
	rpage = alloc_page(GFP_HIGHUSER);
	अगर (!rpage)
		वापस शून्य;

	spin_lock(&mdevice->lock);

	अगर (mdevice->मुक्त_pages) अणु
		dpage = mdevice->मुक्त_pages;
		mdevice->मुक्त_pages = dpage->zone_device_data;
		mdevice->सुस्मृति++;
		spin_unlock(&mdevice->lock);
	पूर्ण अन्यथा अणु
		spin_unlock(&mdevice->lock);
		अगर (!dmirror_allocate_chunk(mdevice, &dpage))
			जाओ error;
	पूर्ण

	dpage->zone_device_data = rpage;
	get_page(dpage);
	lock_page(dpage);
	वापस dpage;

error:
	__मुक्त_page(rpage);
	वापस शून्य;
पूर्ण

अटल व्योम dmirror_migrate_alloc_and_copy(काष्ठा migrate_vma *args,
					   काष्ठा dmirror *dmirror)
अणु
	काष्ठा dmirror_device *mdevice = dmirror->mdevice;
	स्थिर अचिन्हित दीर्घ *src = args->src;
	अचिन्हित दीर्घ *dst = args->dst;
	अचिन्हित दीर्घ addr;

	क्रम (addr = args->start; addr < args->end; addr += PAGE_SIZE,
						   src++, dst++) अणु
		काष्ठा page *spage;
		काष्ठा page *dpage;
		काष्ठा page *rpage;

		अगर (!(*src & MIGRATE_PFN_MIGRATE))
			जारी;

		/*
		 * Note that spage might be शून्य which is OK since it is an
		 * unallocated pte_none() or पढ़ो-only zero page.
		 */
		spage = migrate_pfn_to_page(*src);

		dpage = dmirror_devmem_alloc_page(mdevice);
		अगर (!dpage)
			जारी;

		rpage = dpage->zone_device_data;
		अगर (spage)
			copy_highpage(rpage, spage);
		अन्यथा
			clear_highpage(rpage);

		/*
		 * Normally, a device would use the page->zone_device_data to
		 * poपूर्णांक to the mirror but here we use it to hold the page क्रम
		 * the simulated device memory and that page holds the poपूर्णांकer
		 * to the mirror.
		 */
		rpage->zone_device_data = dmirror;

		*dst = migrate_pfn(page_to_pfn(dpage)) |
			    MIGRATE_PFN_LOCKED;
		अगर ((*src & MIGRATE_PFN_WRITE) ||
		    (!spage && args->vma->vm_flags & VM_WRITE))
			*dst |= MIGRATE_PFN_WRITE;
	पूर्ण
पूर्ण

अटल पूर्णांक dmirror_migrate_finalize_and_map(काष्ठा migrate_vma *args,
					    काष्ठा dmirror *dmirror)
अणु
	अचिन्हित दीर्घ start = args->start;
	अचिन्हित दीर्घ end = args->end;
	स्थिर अचिन्हित दीर्घ *src = args->src;
	स्थिर अचिन्हित दीर्घ *dst = args->dst;
	अचिन्हित दीर्घ pfn;

	/* Map the migrated pages पूर्णांकo the device's page tables. */
	mutex_lock(&dmirror->mutex);

	क्रम (pfn = start >> PAGE_SHIFT; pfn < (end >> PAGE_SHIFT); pfn++,
								src++, dst++) अणु
		काष्ठा page *dpage;
		व्योम *entry;

		अगर (!(*src & MIGRATE_PFN_MIGRATE))
			जारी;

		dpage = migrate_pfn_to_page(*dst);
		अगर (!dpage)
			जारी;

		/*
		 * Store the page that holds the data so the page table
		 * करोesn't have to deal with ZONE_DEVICE निजी pages.
		 */
		entry = dpage->zone_device_data;
		अगर (*dst & MIGRATE_PFN_WRITE)
			entry = xa_tag_poपूर्णांकer(entry, DPT_XA_TAG_WRITE);
		entry = xa_store(&dmirror->pt, pfn, entry, GFP_ATOMIC);
		अगर (xa_is_err(entry)) अणु
			mutex_unlock(&dmirror->mutex);
			वापस xa_err(entry);
		पूर्ण
	पूर्ण

	mutex_unlock(&dmirror->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक dmirror_migrate(काष्ठा dmirror *dmirror,
			   काष्ठा hmm_dmirror_cmd *cmd)
अणु
	अचिन्हित दीर्घ start, end, addr;
	अचिन्हित दीर्घ size = cmd->npages << PAGE_SHIFT;
	काष्ठा mm_काष्ठा *mm = dmirror->notअगरier.mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ src_pfns[64];
	अचिन्हित दीर्घ dst_pfns[64];
	काष्ठा dmirror_bounce bounce;
	काष्ठा migrate_vma args;
	अचिन्हित दीर्घ next;
	पूर्णांक ret;

	start = cmd->addr;
	end = start + size;
	अगर (end < start)
		वापस -EINVAL;

	/* Since the mm is क्रम the mirrored process, get a reference first. */
	अगर (!mmget_not_zero(mm))
		वापस -EINVAL;

	mmap_पढ़ो_lock(mm);
	क्रम (addr = start; addr < end; addr = next) अणु
		vma = find_vma(mm, addr);
		अगर (!vma || addr < vma->vm_start ||
		    !(vma->vm_flags & VM_READ)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		next = min(end, addr + (ARRAY_SIZE(src_pfns) << PAGE_SHIFT));
		अगर (next > vma->vm_end)
			next = vma->vm_end;

		args.vma = vma;
		args.src = src_pfns;
		args.dst = dst_pfns;
		args.start = addr;
		args.end = next;
		args.pgmap_owner = dmirror->mdevice;
		args.flags = MIGRATE_VMA_SELECT_SYSTEM;
		ret = migrate_vma_setup(&args);
		अगर (ret)
			जाओ out;

		dmirror_migrate_alloc_and_copy(&args, dmirror);
		migrate_vma_pages(&args);
		dmirror_migrate_finalize_and_map(&args, dmirror);
		migrate_vma_finalize(&args);
	पूर्ण
	mmap_पढ़ो_unlock(mm);
	mmput(mm);

	/* Return the migrated data क्रम verअगरication. */
	ret = dmirror_bounce_init(&bounce, start, size);
	अगर (ret)
		वापस ret;
	mutex_lock(&dmirror->mutex);
	ret = dmirror_करो_पढ़ो(dmirror, start, end, &bounce);
	mutex_unlock(&dmirror->mutex);
	अगर (ret == 0) अणु
		अगर (copy_to_user(u64_to_user_ptr(cmd->ptr), bounce.ptr,
				 bounce.size))
			ret = -EFAULT;
	पूर्ण
	cmd->cpages = bounce.cpages;
	dmirror_bounce_fini(&bounce);
	वापस ret;

out:
	mmap_पढ़ो_unlock(mm);
	mmput(mm);
	वापस ret;
पूर्ण

अटल व्योम dmirror_mkentry(काष्ठा dmirror *dmirror, काष्ठा hmm_range *range,
			    अचिन्हित अक्षर *perm, अचिन्हित दीर्घ entry)
अणु
	काष्ठा page *page;

	अगर (entry & HMM_PFN_ERROR) अणु
		*perm = HMM_DMIRROR_PROT_ERROR;
		वापस;
	पूर्ण
	अगर (!(entry & HMM_PFN_VALID)) अणु
		*perm = HMM_DMIRROR_PROT_NONE;
		वापस;
	पूर्ण

	page = hmm_pfn_to_page(entry);
	अगर (is_device_निजी_page(page)) अणु
		/* Is the page migrated to this device or some other? */
		अगर (dmirror->mdevice == dmirror_page_to_device(page))
			*perm = HMM_DMIRROR_PROT_DEV_PRIVATE_LOCAL;
		अन्यथा
			*perm = HMM_DMIRROR_PROT_DEV_PRIVATE_REMOTE;
	पूर्ण अन्यथा अगर (is_zero_pfn(page_to_pfn(page)))
		*perm = HMM_DMIRROR_PROT_ZERO;
	अन्यथा
		*perm = HMM_DMIRROR_PROT_NONE;
	अगर (entry & HMM_PFN_WRITE)
		*perm |= HMM_DMIRROR_PROT_WRITE;
	अन्यथा
		*perm |= HMM_DMIRROR_PROT_READ;
	अगर (hmm_pfn_to_map_order(entry) + PAGE_SHIFT == PMD_SHIFT)
		*perm |= HMM_DMIRROR_PROT_PMD;
	अन्यथा अगर (hmm_pfn_to_map_order(entry) + PAGE_SHIFT == PUD_SHIFT)
		*perm |= HMM_DMIRROR_PROT_PUD;
पूर्ण

अटल bool dmirror_snapshot_invalidate(काष्ठा mmu_पूर्णांकerval_notअगरier *mni,
				स्थिर काष्ठा mmu_notअगरier_range *range,
				अचिन्हित दीर्घ cur_seq)
अणु
	काष्ठा dmirror_पूर्णांकerval *dmi =
		container_of(mni, काष्ठा dmirror_पूर्णांकerval, notअगरier);
	काष्ठा dmirror *dmirror = dmi->dmirror;

	अगर (mmu_notअगरier_range_blockable(range))
		mutex_lock(&dmirror->mutex);
	अन्यथा अगर (!mutex_trylock(&dmirror->mutex))
		वापस false;

	/*
	 * Snapshots only need to set the sequence number since any
	 * invalidation in the पूर्णांकerval invalidates the whole snapshot.
	 */
	mmu_पूर्णांकerval_set_seq(mni, cur_seq);

	mutex_unlock(&dmirror->mutex);
	वापस true;
पूर्ण

अटल स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops dmirror_mrn_ops = अणु
	.invalidate = dmirror_snapshot_invalidate,
पूर्ण;

अटल पूर्णांक dmirror_range_snapshot(काष्ठा dmirror *dmirror,
				  काष्ठा hmm_range *range,
				  अचिन्हित अक्षर *perm)
अणु
	काष्ठा mm_काष्ठा *mm = dmirror->notअगरier.mm;
	काष्ठा dmirror_पूर्णांकerval notअगरier;
	अचिन्हित दीर्घ समयout =
		jअगरfies + msecs_to_jअगरfies(HMM_RANGE_DEFAULT_TIMEOUT);
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ n;
	पूर्णांक ret = 0;

	notअगरier.dmirror = dmirror;
	range->notअगरier = &notअगरier.notअगरier;

	ret = mmu_पूर्णांकerval_notअगरier_insert(range->notअगरier, mm,
			range->start, range->end - range->start,
			&dmirror_mrn_ops);
	अगर (ret)
		वापस ret;

	जबतक (true) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण

		range->notअगरier_seq = mmu_पूर्णांकerval_पढ़ो_begin(range->notअगरier);

		mmap_पढ़ो_lock(mm);
		ret = hmm_range_fault(range);
		mmap_पढ़ो_unlock(mm);
		अगर (ret) अणु
			अगर (ret == -EBUSY)
				जारी;
			जाओ out;
		पूर्ण

		mutex_lock(&dmirror->mutex);
		अगर (mmu_पूर्णांकerval_पढ़ो_retry(range->notअगरier,
					    range->notअगरier_seq)) अणु
			mutex_unlock(&dmirror->mutex);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	n = (range->end - range->start) >> PAGE_SHIFT;
	क्रम (i = 0; i < n; i++)
		dmirror_mkentry(dmirror, range, perm + i, range->hmm_pfns[i]);

	mutex_unlock(&dmirror->mutex);
out:
	mmu_पूर्णांकerval_notअगरier_हटाओ(range->notअगरier);
	वापस ret;
पूर्ण

अटल पूर्णांक dmirror_snapshot(काष्ठा dmirror *dmirror,
			    काष्ठा hmm_dmirror_cmd *cmd)
अणु
	काष्ठा mm_काष्ठा *mm = dmirror->notअगरier.mm;
	अचिन्हित दीर्घ start, end;
	अचिन्हित दीर्घ size = cmd->npages << PAGE_SHIFT;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ pfns[64];
	अचिन्हित अक्षर perm[64];
	अक्षर __user *uptr;
	काष्ठा hmm_range range = अणु
		.hmm_pfns = pfns,
		.dev_निजी_owner = dmirror->mdevice,
	पूर्ण;
	पूर्णांक ret = 0;

	start = cmd->addr;
	end = start + size;
	अगर (end < start)
		वापस -EINVAL;

	/* Since the mm is क्रम the mirrored process, get a reference first. */
	अगर (!mmget_not_zero(mm))
		वापस -EINVAL;

	/*
	 * Register a temporary notअगरier to detect invalidations even अगर it
	 * overlaps with other mmu_पूर्णांकerval_notअगरiers.
	 */
	uptr = u64_to_user_ptr(cmd->ptr);
	क्रम (addr = start; addr < end; addr = next) अणु
		अचिन्हित दीर्घ n;

		next = min(addr + (ARRAY_SIZE(pfns) << PAGE_SHIFT), end);
		range.start = addr;
		range.end = next;

		ret = dmirror_range_snapshot(dmirror, &range, perm);
		अगर (ret)
			अवरोध;

		n = (range.end - range.start) >> PAGE_SHIFT;
		अगर (copy_to_user(uptr, perm, n)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		cmd->cpages += n;
		uptr += n;
	पूर्ण
	mmput(mm);

	वापस ret;
पूर्ण

अटल दीर्घ dmirror_fops_unlocked_ioctl(काष्ठा file *filp,
					अचिन्हित पूर्णांक command,
					अचिन्हित दीर्घ arg)
अणु
	व्योम __user *uarg = (व्योम __user *)arg;
	काष्ठा hmm_dmirror_cmd cmd;
	काष्ठा dmirror *dmirror;
	पूर्णांक ret;

	dmirror = filp->निजी_data;
	अगर (!dmirror)
		वापस -EINVAL;

	अगर (copy_from_user(&cmd, uarg, माप(cmd)))
		वापस -EFAULT;

	अगर (cmd.addr & ~PAGE_MASK)
		वापस -EINVAL;
	अगर (cmd.addr >= (cmd.addr + (cmd.npages << PAGE_SHIFT)))
		वापस -EINVAL;

	cmd.cpages = 0;
	cmd.faults = 0;

	चयन (command) अणु
	हाल HMM_DMIRROR_READ:
		ret = dmirror_पढ़ो(dmirror, &cmd);
		अवरोध;

	हाल HMM_DMIRROR_WRITE:
		ret = dmirror_ग_लिखो(dmirror, &cmd);
		अवरोध;

	हाल HMM_DMIRROR_MIGRATE:
		ret = dmirror_migrate(dmirror, &cmd);
		अवरोध;

	हाल HMM_DMIRROR_SNAPSHOT:
		ret = dmirror_snapshot(dmirror, &cmd);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(uarg, &cmd, माप(cmd)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations dmirror_fops = अणु
	.खोलो		= dmirror_fops_खोलो,
	.release	= dmirror_fops_release,
	.unlocked_ioctl = dmirror_fops_unlocked_ioctl,
	.llseek		= शेष_llseek,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम dmirror_devmem_मुक्त(काष्ठा page *page)
अणु
	काष्ठा page *rpage = page->zone_device_data;
	काष्ठा dmirror_device *mdevice;

	अगर (rpage)
		__मुक्त_page(rpage);

	mdevice = dmirror_page_to_device(page);

	spin_lock(&mdevice->lock);
	mdevice->cमुक्त++;
	page->zone_device_data = mdevice->मुक्त_pages;
	mdevice->मुक्त_pages = page;
	spin_unlock(&mdevice->lock);
पूर्ण

अटल vm_fault_t dmirror_devmem_fault_alloc_and_copy(काष्ठा migrate_vma *args,
						      काष्ठा dmirror *dmirror)
अणु
	स्थिर अचिन्हित दीर्घ *src = args->src;
	अचिन्हित दीर्घ *dst = args->dst;
	अचिन्हित दीर्घ start = args->start;
	अचिन्हित दीर्घ end = args->end;
	अचिन्हित दीर्घ addr;

	क्रम (addr = start; addr < end; addr += PAGE_SIZE,
				       src++, dst++) अणु
		काष्ठा page *dpage, *spage;

		spage = migrate_pfn_to_page(*src);
		अगर (!spage || !(*src & MIGRATE_PFN_MIGRATE))
			जारी;
		spage = spage->zone_device_data;

		dpage = alloc_page_vma(GFP_HIGHUSER_MOVABLE, args->vma, addr);
		अगर (!dpage)
			जारी;

		lock_page(dpage);
		xa_erase(&dmirror->pt, addr >> PAGE_SHIFT);
		copy_highpage(dpage, spage);
		*dst = migrate_pfn(page_to_pfn(dpage)) | MIGRATE_PFN_LOCKED;
		अगर (*src & MIGRATE_PFN_WRITE)
			*dst |= MIGRATE_PFN_WRITE;
	पूर्ण
	वापस 0;
पूर्ण

अटल vm_fault_t dmirror_devmem_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा migrate_vma args;
	अचिन्हित दीर्घ src_pfns;
	अचिन्हित दीर्घ dst_pfns;
	काष्ठा page *rpage;
	काष्ठा dmirror *dmirror;
	vm_fault_t ret;

	/*
	 * Normally, a device would use the page->zone_device_data to poपूर्णांक to
	 * the mirror but here we use it to hold the page क्रम the simulated
	 * device memory and that page holds the poपूर्णांकer to the mirror.
	 */
	rpage = vmf->page->zone_device_data;
	dmirror = rpage->zone_device_data;

	/* FIXME demonstrate how we can adjust migrate range */
	args.vma = vmf->vma;
	args.start = vmf->address;
	args.end = args.start + PAGE_SIZE;
	args.src = &src_pfns;
	args.dst = &dst_pfns;
	args.pgmap_owner = dmirror->mdevice;
	args.flags = MIGRATE_VMA_SELECT_DEVICE_PRIVATE;

	अगर (migrate_vma_setup(&args))
		वापस VM_FAULT_SIGBUS;

	ret = dmirror_devmem_fault_alloc_and_copy(&args, dmirror);
	अगर (ret)
		वापस ret;
	migrate_vma_pages(&args);
	/*
	 * No device finalize step is needed since
	 * dmirror_devmem_fault_alloc_and_copy() will have alपढ़ोy
	 * invalidated the device page table.
	 */
	migrate_vma_finalize(&args);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pagemap_ops dmirror_devmem_ops = अणु
	.page_मुक्त	= dmirror_devmem_मुक्त,
	.migrate_to_ram	= dmirror_devmem_fault,
पूर्ण;

अटल पूर्णांक dmirror_device_init(काष्ठा dmirror_device *mdevice, पूर्णांक id)
अणु
	dev_t dev;
	पूर्णांक ret;

	dev = MKDEV(MAJOR(dmirror_dev), id);
	mutex_init(&mdevice->devmem_lock);
	spin_lock_init(&mdevice->lock);

	cdev_init(&mdevice->cdevice, &dmirror_fops);
	mdevice->cdevice.owner = THIS_MODULE;
	ret = cdev_add(&mdevice->cdevice, dev, 1);
	अगर (ret)
		वापस ret;

	/* Build a list of मुक्त ZONE_DEVICE निजी काष्ठा pages */
	dmirror_allocate_chunk(mdevice, शून्य);

	वापस 0;
पूर्ण

अटल व्योम dmirror_device_हटाओ(काष्ठा dmirror_device *mdevice)
अणु
	अचिन्हित पूर्णांक i;

	अगर (mdevice->devmem_chunks) अणु
		क्रम (i = 0; i < mdevice->devmem_count; i++) अणु
			काष्ठा dmirror_chunk *devmem =
				mdevice->devmem_chunks[i];

			memunmap_pages(&devmem->pagemap);
			release_mem_region(devmem->pagemap.range.start,
					   range_len(&devmem->pagemap.range));
			kमुक्त(devmem);
		पूर्ण
		kमुक्त(mdevice->devmem_chunks);
	पूर्ण

	cdev_del(&mdevice->cdevice);
पूर्ण

अटल पूर्णांक __init hmm_dmirror_init(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक id;

	ret = alloc_chrdev_region(&dmirror_dev, 0, DMIRROR_NDEVICES,
				  "HMM_DMIRROR");
	अगर (ret)
		जाओ err_unreg;

	क्रम (id = 0; id < DMIRROR_NDEVICES; id++) अणु
		ret = dmirror_device_init(dmirror_devices + id, id);
		अगर (ret)
			जाओ err_chrdev;
	पूर्ण

	pr_info("HMM test module loaded. This is only for testing HMM.\n");
	वापस 0;

err_chrdev:
	जबतक (--id >= 0)
		dmirror_device_हटाओ(dmirror_devices + id);
	unरेजिस्टर_chrdev_region(dmirror_dev, DMIRROR_NDEVICES);
err_unreg:
	वापस ret;
पूर्ण

अटल व्योम __निकास hmm_dmirror_निकास(व्योम)
अणु
	पूर्णांक id;

	क्रम (id = 0; id < DMIRROR_NDEVICES; id++)
		dmirror_device_हटाओ(dmirror_devices + id);
	unरेजिस्टर_chrdev_region(dmirror_dev, DMIRROR_NDEVICES);
पूर्ण

module_init(hmm_dmirror_init);
module_निकास(hmm_dmirror_निकास);
MODULE_LICENSE("GPL");
