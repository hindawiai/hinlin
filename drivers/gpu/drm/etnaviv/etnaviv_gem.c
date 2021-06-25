<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2018 Etnaviv Project
 */

#समावेश <drm/drm_prime.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "etnaviv_drv.h"
#समावेश "etnaviv_gem.h"
#समावेश "etnaviv_gpu.h"
#समावेश "etnaviv_mmu.h"

अटल काष्ठा lock_class_key etnaviv_shm_lock_class;
अटल काष्ठा lock_class_key etnaviv_userptr_lock_class;

अटल व्योम etnaviv_gem_scatter_map(काष्ठा etnaviv_gem_object *etnaviv_obj)
अणु
	काष्ठा drm_device *dev = etnaviv_obj->base.dev;
	काष्ठा sg_table *sgt = etnaviv_obj->sgt;

	/*
	 * For non-cached buffers, ensure the new pages are clean
	 * because display controller, GPU, etc. are not coherent.
	 */
	अगर (etnaviv_obj->flags & ETNA_BO_CACHE_MASK)
		dma_map_sgtable(dev->dev, sgt, DMA_BIसूचीECTIONAL, 0);
पूर्ण

अटल व्योम etnaviv_gem_scatterlist_unmap(काष्ठा etnaviv_gem_object *etnaviv_obj)
अणु
	काष्ठा drm_device *dev = etnaviv_obj->base.dev;
	काष्ठा sg_table *sgt = etnaviv_obj->sgt;

	/*
	 * For non-cached buffers, ensure the new pages are clean
	 * because display controller, GPU, etc. are not coherent:
	 *
	 * WARNING: The DMA API करोes not support concurrent CPU
	 * and device access to the memory area.  With BIसूचीECTIONAL,
	 * we will clean the cache lines which overlap the region,
	 * and invalidate all cache lines (partially) contained in
	 * the region.
	 *
	 * If you have dirty data in the overlapping cache lines,
	 * that will corrupt the GPU-written data.  If you have
	 * written पूर्णांकo the reमुख्यder of the region, this can
	 * discard those ग_लिखोs.
	 */
	अगर (etnaviv_obj->flags & ETNA_BO_CACHE_MASK)
		dma_unmap_sgtable(dev->dev, sgt, DMA_BIसूचीECTIONAL, 0);
पूर्ण

/* called with etnaviv_obj->lock held */
अटल पूर्णांक etnaviv_gem_shmem_get_pages(काष्ठा etnaviv_gem_object *etnaviv_obj)
अणु
	काष्ठा drm_device *dev = etnaviv_obj->base.dev;
	काष्ठा page **p = drm_gem_get_pages(&etnaviv_obj->base);

	अगर (IS_ERR(p)) अणु
		dev_dbg(dev->dev, "could not get pages: %ld\n", PTR_ERR(p));
		वापस PTR_ERR(p);
	पूर्ण

	etnaviv_obj->pages = p;

	वापस 0;
पूर्ण

अटल व्योम put_pages(काष्ठा etnaviv_gem_object *etnaviv_obj)
अणु
	अगर (etnaviv_obj->sgt) अणु
		etnaviv_gem_scatterlist_unmap(etnaviv_obj);
		sg_मुक्त_table(etnaviv_obj->sgt);
		kमुक्त(etnaviv_obj->sgt);
		etnaviv_obj->sgt = शून्य;
	पूर्ण
	अगर (etnaviv_obj->pages) अणु
		drm_gem_put_pages(&etnaviv_obj->base, etnaviv_obj->pages,
				  true, false);

		etnaviv_obj->pages = शून्य;
	पूर्ण
पूर्ण

काष्ठा page **etnaviv_gem_get_pages(काष्ठा etnaviv_gem_object *etnaviv_obj)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&etnaviv_obj->lock);

	अगर (!etnaviv_obj->pages) अणु
		ret = etnaviv_obj->ops->get_pages(etnaviv_obj);
		अगर (ret < 0)
			वापस ERR_PTR(ret);
	पूर्ण

	अगर (!etnaviv_obj->sgt) अणु
		काष्ठा drm_device *dev = etnaviv_obj->base.dev;
		पूर्णांक npages = etnaviv_obj->base.size >> PAGE_SHIFT;
		काष्ठा sg_table *sgt;

		sgt = drm_prime_pages_to_sg(etnaviv_obj->base.dev,
					    etnaviv_obj->pages, npages);
		अगर (IS_ERR(sgt)) अणु
			dev_err(dev->dev, "failed to allocate sgt: %ld\n",
				PTR_ERR(sgt));
			वापस ERR_CAST(sgt);
		पूर्ण

		etnaviv_obj->sgt = sgt;

		etnaviv_gem_scatter_map(etnaviv_obj);
	पूर्ण

	वापस etnaviv_obj->pages;
पूर्ण

व्योम etnaviv_gem_put_pages(काष्ठा etnaviv_gem_object *etnaviv_obj)
अणु
	lockdep_निश्चित_held(&etnaviv_obj->lock);
	/* when we start tracking the pin count, then करो something here */
पूर्ण

अटल पूर्णांक etnaviv_gem_mmap_obj(काष्ठा etnaviv_gem_object *etnaviv_obj,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	pgprot_t vm_page_prot;

	vma->vm_flags &= ~VM_PFNMAP;
	vma->vm_flags |= VM_MIXEDMAP;

	vm_page_prot = vm_get_page_prot(vma->vm_flags);

	अगर (etnaviv_obj->flags & ETNA_BO_WC) अणु
		vma->vm_page_prot = pgprot_ग_लिखोcombine(vm_page_prot);
	पूर्ण अन्यथा अगर (etnaviv_obj->flags & ETNA_BO_UNCACHED) अणु
		vma->vm_page_prot = pgprot_noncached(vm_page_prot);
	पूर्ण अन्यथा अणु
		/*
		 * Shunt off cached objs to shmem file so they have their own
		 * address_space (so unmap_mapping_range करोes what we want,
		 * in particular in the हाल of mmap'd dmabufs)
		 */
		vma->vm_pgoff = 0;
		vma_set_file(vma, etnaviv_obj->base.filp);

		vma->vm_page_prot = vm_page_prot;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक etnaviv_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा etnaviv_gem_object *obj;
	पूर्णांक ret;

	ret = drm_gem_mmap(filp, vma);
	अगर (ret) अणु
		DBG("mmap failed: %d", ret);
		वापस ret;
	पूर्ण

	obj = to_etnaviv_bo(vma->vm_निजी_data);
	वापस obj->ops->mmap(obj, vma);
पूर्ण

अटल vm_fault_t etnaviv_gem_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा drm_gem_object *obj = vma->vm_निजी_data;
	काष्ठा etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	काष्ठा page **pages, *page;
	pgoff_t pgoff;
	पूर्णांक err;

	/*
	 * Make sure we करोn't parallel update on a fault, nor move or हटाओ
	 * something from beneath our feet.  Note that vmf_insert_page() is
	 * specअगरically coded to take care of this, so we करोn't have to.
	 */
	err = mutex_lock_पूर्णांकerruptible(&etnaviv_obj->lock);
	अगर (err)
		वापस VM_FAULT_NOPAGE;
	/* make sure we have pages attached now */
	pages = etnaviv_gem_get_pages(etnaviv_obj);
	mutex_unlock(&etnaviv_obj->lock);

	अगर (IS_ERR(pages)) अणु
		err = PTR_ERR(pages);
		वापस vmf_error(err);
	पूर्ण

	/* We करोn't use vmf->pgoff since that has the fake offset: */
	pgoff = (vmf->address - vma->vm_start) >> PAGE_SHIFT;

	page = pages[pgoff];

	VERB("Inserting %p pfn %lx, pa %lx", (व्योम *)vmf->address,
	     page_to_pfn(page), page_to_pfn(page) << PAGE_SHIFT);

	वापस vmf_insert_page(vma, vmf->address, page);
पूर्ण

पूर्णांक etnaviv_gem_mmap_offset(काष्ठा drm_gem_object *obj, u64 *offset)
अणु
	पूर्णांक ret;

	/* Make it mmapable */
	ret = drm_gem_create_mmap_offset(obj);
	अगर (ret)
		dev_err(obj->dev->dev, "could not allocate mmap offset\n");
	अन्यथा
		*offset = drm_vma_node_offset_addr(&obj->vma_node);

	वापस ret;
पूर्ण

अटल काष्ठा etnaviv_vram_mapping *
etnaviv_gem_get_vram_mapping(काष्ठा etnaviv_gem_object *obj,
			     काष्ठा etnaviv_iommu_context *context)
अणु
	काष्ठा etnaviv_vram_mapping *mapping;

	list_क्रम_each_entry(mapping, &obj->vram_list, obj_node) अणु
		अगर (mapping->context == context)
			वापस mapping;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम etnaviv_gem_mapping_unreference(काष्ठा etnaviv_vram_mapping *mapping)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj = mapping->object;

	mutex_lock(&etnaviv_obj->lock);
	WARN_ON(mapping->use == 0);
	mapping->use -= 1;
	mutex_unlock(&etnaviv_obj->lock);

	drm_gem_object_put(&etnaviv_obj->base);
पूर्ण

काष्ठा etnaviv_vram_mapping *etnaviv_gem_mapping_get(
	काष्ठा drm_gem_object *obj, काष्ठा etnaviv_iommu_context *mmu_context,
	u64 va)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	काष्ठा etnaviv_vram_mapping *mapping;
	काष्ठा page **pages;
	पूर्णांक ret = 0;

	mutex_lock(&etnaviv_obj->lock);
	mapping = etnaviv_gem_get_vram_mapping(etnaviv_obj, mmu_context);
	अगर (mapping) अणु
		/*
		 * Holding the object lock prevents the use count changing
		 * beneath us.  If the use count is zero, the MMU might be
		 * reaping this object, so take the lock and re-check that
		 * the MMU owns this mapping to बंद this race.
		 */
		अगर (mapping->use == 0) अणु
			mutex_lock(&mmu_context->lock);
			अगर (mapping->context == mmu_context)
				mapping->use += 1;
			अन्यथा
				mapping = शून्य;
			mutex_unlock(&mmu_context->lock);
			अगर (mapping)
				जाओ out;
		पूर्ण अन्यथा अणु
			mapping->use += 1;
			जाओ out;
		पूर्ण
	पूर्ण

	pages = etnaviv_gem_get_pages(etnaviv_obj);
	अगर (IS_ERR(pages)) अणु
		ret = PTR_ERR(pages);
		जाओ out;
	पूर्ण

	/*
	 * See अगर we have a reaped vram mapping we can re-use beक्रमe
	 * allocating a fresh mapping.
	 */
	mapping = etnaviv_gem_get_vram_mapping(etnaviv_obj, शून्य);
	अगर (!mapping) अणु
		mapping = kzalloc(माप(*mapping), GFP_KERNEL);
		अगर (!mapping) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		INIT_LIST_HEAD(&mapping->scan_node);
		mapping->object = etnaviv_obj;
	पूर्ण अन्यथा अणु
		list_del(&mapping->obj_node);
	पूर्ण

	etnaviv_iommu_context_get(mmu_context);
	mapping->context = mmu_context;
	mapping->use = 1;

	ret = etnaviv_iommu_map_gem(mmu_context, etnaviv_obj,
				    mmu_context->global->memory_base,
				    mapping, va);
	अगर (ret < 0) अणु
		etnaviv_iommu_context_put(mmu_context);
		kमुक्त(mapping);
	पूर्ण अन्यथा अणु
		list_add_tail(&mapping->obj_node, &etnaviv_obj->vram_list);
	पूर्ण

out:
	mutex_unlock(&etnaviv_obj->lock);

	अगर (ret)
		वापस ERR_PTR(ret);

	/* Take a reference on the object */
	drm_gem_object_get(obj);
	वापस mapping;
पूर्ण

व्योम *etnaviv_gem_vmap(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

	अगर (etnaviv_obj->vaddr)
		वापस etnaviv_obj->vaddr;

	mutex_lock(&etnaviv_obj->lock);
	/*
	 * Need to check again, as we might have raced with another thपढ़ो
	 * जबतक रुकोing क्रम the mutex.
	 */
	अगर (!etnaviv_obj->vaddr)
		etnaviv_obj->vaddr = etnaviv_obj->ops->vmap(etnaviv_obj);
	mutex_unlock(&etnaviv_obj->lock);

	वापस etnaviv_obj->vaddr;
पूर्ण

अटल व्योम *etnaviv_gem_vmap_impl(काष्ठा etnaviv_gem_object *obj)
अणु
	काष्ठा page **pages;

	lockdep_निश्चित_held(&obj->lock);

	pages = etnaviv_gem_get_pages(obj);
	अगर (IS_ERR(pages))
		वापस शून्य;

	वापस vmap(pages, obj->base.size >> PAGE_SHIFT,
			VM_MAP, pgprot_ग_लिखोcombine(PAGE_KERNEL));
पूर्ण

अटल अंतरभूत क्रमागत dma_data_direction etnaviv_op_to_dma_dir(u32 op)
अणु
	अगर (op & ETNA_PREP_READ)
		वापस DMA_FROM_DEVICE;
	अन्यथा अगर (op & ETNA_PREP_WRITE)
		वापस DMA_TO_DEVICE;
	अन्यथा
		वापस DMA_BIसूचीECTIONAL;
पूर्ण

पूर्णांक etnaviv_gem_cpu_prep(काष्ठा drm_gem_object *obj, u32 op,
		काष्ठा drm_etnaviv_बारpec *समयout)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	काष्ठा drm_device *dev = obj->dev;
	bool ग_लिखो = !!(op & ETNA_PREP_WRITE);
	पूर्णांक ret;

	अगर (!etnaviv_obj->sgt) अणु
		व्योम *ret;

		mutex_lock(&etnaviv_obj->lock);
		ret = etnaviv_gem_get_pages(etnaviv_obj);
		mutex_unlock(&etnaviv_obj->lock);
		अगर (IS_ERR(ret))
			वापस PTR_ERR(ret);
	पूर्ण

	अगर (op & ETNA_PREP_NOSYNC) अणु
		अगर (!dma_resv_test_संकेतed_rcu(obj->resv,
							  ग_लिखो))
			वापस -EBUSY;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ reमुख्य = etnaviv_समयout_to_jअगरfies(समयout);

		ret = dma_resv_रुको_समयout_rcu(obj->resv,
							  ग_लिखो, true, reमुख्य);
		अगर (ret <= 0)
			वापस ret == 0 ? -ETIMEDOUT : ret;
	पूर्ण

	अगर (etnaviv_obj->flags & ETNA_BO_CACHED) अणु
		dma_sync_sgtable_क्रम_cpu(dev->dev, etnaviv_obj->sgt,
					 etnaviv_op_to_dma_dir(op));
		etnaviv_obj->last_cpu_prep_op = op;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक etnaviv_gem_cpu_fini(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_device *dev = obj->dev;
	काष्ठा etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

	अगर (etnaviv_obj->flags & ETNA_BO_CACHED) अणु
		/* fini without a prep is almost certainly a userspace error */
		WARN_ON(etnaviv_obj->last_cpu_prep_op == 0);
		dma_sync_sgtable_क्रम_device(dev->dev, etnaviv_obj->sgt,
			etnaviv_op_to_dma_dir(etnaviv_obj->last_cpu_prep_op));
		etnaviv_obj->last_cpu_prep_op = 0;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक etnaviv_gem_रुको_bo(काष्ठा etnaviv_gpu *gpu, काष्ठा drm_gem_object *obj,
	काष्ठा drm_etnaviv_बारpec *समयout)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

	वापस etnaviv_gpu_रुको_obj_inactive(gpu, etnaviv_obj, समयout);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम etnaviv_gem_describe_fence(काष्ठा dma_fence *fence,
	स्थिर अक्षर *type, काष्ठा seq_file *m)
अणु
	अगर (!test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags))
		seq_म_लिखो(m, "\t%9s: %s %s seq %llu\n",
			   type,
			   fence->ops->get_driver_name(fence),
			   fence->ops->get_समयline_name(fence),
			   fence->seqno);
पूर्ण

अटल व्योम etnaviv_gem_describe(काष्ठा drm_gem_object *obj, काष्ठा seq_file *m)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	काष्ठा dma_resv *robj = obj->resv;
	काष्ठा dma_resv_list *fobj;
	काष्ठा dma_fence *fence;
	अचिन्हित दीर्घ off = drm_vma_node_start(&obj->vma_node);

	seq_म_लिखो(m, "%08x: %c %2d (%2d) %08lx %p %zd\n",
			etnaviv_obj->flags, is_active(etnaviv_obj) ? 'A' : 'I',
			obj->name, kref_पढ़ो(&obj->refcount),
			off, etnaviv_obj->vaddr, obj->size);

	rcu_पढ़ो_lock();
	fobj = rcu_dereference(robj->fence);
	अगर (fobj) अणु
		अचिन्हित पूर्णांक i, shared_count = fobj->shared_count;

		क्रम (i = 0; i < shared_count; i++) अणु
			fence = rcu_dereference(fobj->shared[i]);
			etnaviv_gem_describe_fence(fence, "Shared", m);
		पूर्ण
	पूर्ण

	fence = rcu_dereference(robj->fence_excl);
	अगर (fence)
		etnaviv_gem_describe_fence(fence, "Exclusive", m);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम etnaviv_gem_describe_objects(काष्ठा etnaviv_drm_निजी *priv,
	काष्ठा seq_file *m)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj;
	पूर्णांक count = 0;
	माप_प्रकार size = 0;

	mutex_lock(&priv->gem_lock);
	list_क्रम_each_entry(etnaviv_obj, &priv->gem_list, gem_node) अणु
		काष्ठा drm_gem_object *obj = &etnaviv_obj->base;

		seq_माला_दो(m, "   ");
		etnaviv_gem_describe(obj, m);
		count++;
		size += obj->size;
	पूर्ण
	mutex_unlock(&priv->gem_lock);

	seq_म_लिखो(m, "Total %d objects, %zu bytes\n", count, size);
पूर्ण
#पूर्ण_अगर

अटल व्योम etnaviv_gem_shmem_release(काष्ठा etnaviv_gem_object *etnaviv_obj)
अणु
	vunmap(etnaviv_obj->vaddr);
	put_pages(etnaviv_obj);
पूर्ण

अटल स्थिर काष्ठा etnaviv_gem_ops etnaviv_gem_shmem_ops = अणु
	.get_pages = etnaviv_gem_shmem_get_pages,
	.release = etnaviv_gem_shmem_release,
	.vmap = etnaviv_gem_vmap_impl,
	.mmap = etnaviv_gem_mmap_obj,
पूर्ण;

व्योम etnaviv_gem_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	काष्ठा etnaviv_drm_निजी *priv = obj->dev->dev_निजी;
	काष्ठा etnaviv_vram_mapping *mapping, *पंचांगp;

	/* object should not be active */
	WARN_ON(is_active(etnaviv_obj));

	mutex_lock(&priv->gem_lock);
	list_del(&etnaviv_obj->gem_node);
	mutex_unlock(&priv->gem_lock);

	list_क्रम_each_entry_safe(mapping, पंचांगp, &etnaviv_obj->vram_list,
				 obj_node) अणु
		काष्ठा etnaviv_iommu_context *context = mapping->context;

		WARN_ON(mapping->use);

		अगर (context) अणु
			etnaviv_iommu_unmap_gem(context, mapping);
			etnaviv_iommu_context_put(context);
		पूर्ण

		list_del(&mapping->obj_node);
		kमुक्त(mapping);
	पूर्ण

	drm_gem_मुक्त_mmap_offset(obj);
	etnaviv_obj->ops->release(etnaviv_obj);
	drm_gem_object_release(obj);

	kमुक्त(etnaviv_obj);
पूर्ण

व्योम etnaviv_gem_obj_add(काष्ठा drm_device *dev, काष्ठा drm_gem_object *obj)
अणु
	काष्ठा etnaviv_drm_निजी *priv = dev->dev_निजी;
	काष्ठा etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

	mutex_lock(&priv->gem_lock);
	list_add_tail(&etnaviv_obj->gem_node, &priv->gem_list);
	mutex_unlock(&priv->gem_lock);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा vm_ops = अणु
	.fault = etnaviv_gem_fault,
	.खोलो = drm_gem_vm_खोलो,
	.बंद = drm_gem_vm_बंद,
पूर्ण;

अटल स्थिर काष्ठा drm_gem_object_funcs etnaviv_gem_object_funcs = अणु
	.मुक्त = etnaviv_gem_मुक्त_object,
	.pin = etnaviv_gem_prime_pin,
	.unpin = etnaviv_gem_prime_unpin,
	.get_sg_table = etnaviv_gem_prime_get_sg_table,
	.vmap = etnaviv_gem_prime_vmap,
	.vm_ops = &vm_ops,
पूर्ण;

अटल पूर्णांक etnaviv_gem_new_impl(काष्ठा drm_device *dev, u32 size, u32 flags,
	स्थिर काष्ठा etnaviv_gem_ops *ops, काष्ठा drm_gem_object **obj)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj;
	अचिन्हित sz = माप(*etnaviv_obj);
	bool valid = true;

	/* validate flags */
	चयन (flags & ETNA_BO_CACHE_MASK) अणु
	हाल ETNA_BO_UNCACHED:
	हाल ETNA_BO_CACHED:
	हाल ETNA_BO_WC:
		अवरोध;
	शेष:
		valid = false;
	पूर्ण

	अगर (!valid) अणु
		dev_err(dev->dev, "invalid cache flag: %x\n",
			(flags & ETNA_BO_CACHE_MASK));
		वापस -EINVAL;
	पूर्ण

	etnaviv_obj = kzalloc(sz, GFP_KERNEL);
	अगर (!etnaviv_obj)
		वापस -ENOMEM;

	etnaviv_obj->flags = flags;
	etnaviv_obj->ops = ops;

	mutex_init(&etnaviv_obj->lock);
	INIT_LIST_HEAD(&etnaviv_obj->vram_list);

	*obj = &etnaviv_obj->base;
	(*obj)->funcs = &etnaviv_gem_object_funcs;

	वापस 0;
पूर्ण

/* convenience method to स्थिरruct a GEM buffer object, and userspace handle */
पूर्णांक etnaviv_gem_new_handle(काष्ठा drm_device *dev, काष्ठा drm_file *file,
	u32 size, u32 flags, u32 *handle)
अणु
	काष्ठा etnaviv_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_gem_object *obj = शून्य;
	पूर्णांक ret;

	size = PAGE_ALIGN(size);

	ret = etnaviv_gem_new_impl(dev, size, flags,
				   &etnaviv_gem_shmem_ops, &obj);
	अगर (ret)
		जाओ fail;

	lockdep_set_class(&to_etnaviv_bo(obj)->lock, &etnaviv_shm_lock_class);

	ret = drm_gem_object_init(dev, obj, size);
	अगर (ret)
		जाओ fail;

	/*
	 * Our buffers are kept pinned, so allocating them from the MOVABLE
	 * zone is a really bad idea, and conflicts with CMA. See comments
	 * above new_inode() why this is required _and_ expected अगर you're
	 * going to pin these pages.
	 */
	mapping_set_gfp_mask(obj->filp->f_mapping, priv->shm_gfp_mask);

	etnaviv_gem_obj_add(dev, obj);

	ret = drm_gem_handle_create(file, obj, handle);

	/* drop reference from allocate - handle holds it now */
fail:
	drm_gem_object_put(obj);

	वापस ret;
पूर्ण

पूर्णांक etnaviv_gem_new_निजी(काष्ठा drm_device *dev, माप_प्रकार size, u32 flags,
	स्थिर काष्ठा etnaviv_gem_ops *ops, काष्ठा etnaviv_gem_object **res)
अणु
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	ret = etnaviv_gem_new_impl(dev, size, flags, ops, &obj);
	अगर (ret)
		वापस ret;

	drm_gem_निजी_object_init(dev, obj, size);

	*res = to_etnaviv_bo(obj);

	वापस 0;
पूर्ण

अटल पूर्णांक etnaviv_gem_userptr_get_pages(काष्ठा etnaviv_gem_object *etnaviv_obj)
अणु
	काष्ठा page **pvec = शून्य;
	काष्ठा etnaviv_gem_userptr *userptr = &etnaviv_obj->userptr;
	पूर्णांक ret, pinned = 0, npages = etnaviv_obj->base.size >> PAGE_SHIFT;

	might_lock_पढ़ो(&current->mm->mmap_lock);

	अगर (userptr->mm != current->mm)
		वापस -EPERM;

	pvec = kvदो_स्मृति_array(npages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pvec)
		वापस -ENOMEM;

	करो अणु
		अचिन्हित num_pages = npages - pinned;
		uपूर्णांक64_t ptr = userptr->ptr + pinned * PAGE_SIZE;
		काष्ठा page **pages = pvec + pinned;

		ret = pin_user_pages_fast(ptr, num_pages,
					  FOLL_WRITE | FOLL_FORCE | FOLL_LONGTERM,
					  pages);
		अगर (ret < 0) अणु
			unpin_user_pages(pvec, pinned);
			kvमुक्त(pvec);
			वापस ret;
		पूर्ण

		pinned += ret;

	पूर्ण जबतक (pinned < npages);

	etnaviv_obj->pages = pvec;

	वापस 0;
पूर्ण

अटल व्योम etnaviv_gem_userptr_release(काष्ठा etnaviv_gem_object *etnaviv_obj)
अणु
	अगर (etnaviv_obj->sgt) अणु
		etnaviv_gem_scatterlist_unmap(etnaviv_obj);
		sg_मुक्त_table(etnaviv_obj->sgt);
		kमुक्त(etnaviv_obj->sgt);
	पूर्ण
	अगर (etnaviv_obj->pages) अणु
		पूर्णांक npages = etnaviv_obj->base.size >> PAGE_SHIFT;

		unpin_user_pages(etnaviv_obj->pages, npages);
		kvमुक्त(etnaviv_obj->pages);
	पूर्ण
पूर्ण

अटल पूर्णांक etnaviv_gem_userptr_mmap_obj(काष्ठा etnaviv_gem_object *etnaviv_obj,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा etnaviv_gem_ops etnaviv_gem_userptr_ops = अणु
	.get_pages = etnaviv_gem_userptr_get_pages,
	.release = etnaviv_gem_userptr_release,
	.vmap = etnaviv_gem_vmap_impl,
	.mmap = etnaviv_gem_userptr_mmap_obj,
पूर्ण;

पूर्णांक etnaviv_gem_new_userptr(काष्ठा drm_device *dev, काष्ठा drm_file *file,
	uपूर्णांकptr_t ptr, u32 size, u32 flags, u32 *handle)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj;
	पूर्णांक ret;

	ret = etnaviv_gem_new_निजी(dev, size, ETNA_BO_CACHED,
				      &etnaviv_gem_userptr_ops, &etnaviv_obj);
	अगर (ret)
		वापस ret;

	lockdep_set_class(&etnaviv_obj->lock, &etnaviv_userptr_lock_class);

	etnaviv_obj->userptr.ptr = ptr;
	etnaviv_obj->userptr.mm = current->mm;
	etnaviv_obj->userptr.ro = !(flags & ETNA_USERPTR_WRITE);

	etnaviv_gem_obj_add(dev, &etnaviv_obj->base);

	ret = drm_gem_handle_create(file, &etnaviv_obj->base, handle);

	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put(&etnaviv_obj->base);
	वापस ret;
पूर्ण
