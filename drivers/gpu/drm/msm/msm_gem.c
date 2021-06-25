<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/dma-map-ops.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/pfn_t.h>

#समावेश <drm/drm_prime.h>

#समावेश "msm_drv.h"
#समावेश "msm_fence.h"
#समावेश "msm_gem.h"
#समावेश "msm_gpu.h"
#समावेश "msm_mmu.h"

अटल व्योम update_inactive(काष्ठा msm_gem_object *msm_obj);

अटल dma_addr_t physaddr(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा msm_drm_निजी *priv = obj->dev->dev_निजी;
	वापस (((dma_addr_t)msm_obj->vram_node->start) << PAGE_SHIFT) +
			priv->vram.paddr;
पूर्ण

अटल bool use_pages(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	वापस !msm_obj->vram_node;
पूर्ण

/*
 * Cache sync.. this is a bit over-complicated, to fit dma-mapping
 * API.  Really GPU cache is out of scope here (handled on cmdstream)
 * and all we need to करो is invalidate newly allocated pages beक्रमe
 * mapping to CPU as uncached/ग_लिखोcombine.
 *
 * On top of this, we have the added headache, that depending on
 * display generation, the display's iommu may be wired up to either
 * the toplevel drm device (mdss), or to the mdp sub-node, meaning
 * that here we either have dma-direct or iommu ops.
 *
 * Let this be a cautionary tail of असलtraction gone wrong.
 */

अटल व्योम sync_क्रम_device(काष्ठा msm_gem_object *msm_obj)
अणु
	काष्ठा device *dev = msm_obj->base.dev->dev;

	dma_map_sgtable(dev, msm_obj->sgt, DMA_BIसूचीECTIONAL, 0);
पूर्ण

अटल व्योम sync_क्रम_cpu(काष्ठा msm_gem_object *msm_obj)
अणु
	काष्ठा device *dev = msm_obj->base.dev->dev;

	dma_unmap_sgtable(dev, msm_obj->sgt, DMA_BIसूचीECTIONAL, 0);
पूर्ण

/* allocate pages from VRAM carveout, used when no IOMMU: */
अटल काष्ठा page **get_pages_vram(काष्ठा drm_gem_object *obj, पूर्णांक npages)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा msm_drm_निजी *priv = obj->dev->dev_निजी;
	dma_addr_t paddr;
	काष्ठा page **p;
	पूर्णांक ret, i;

	p = kvदो_स्मृति_array(npages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!p)
		वापस ERR_PTR(-ENOMEM);

	spin_lock(&priv->vram.lock);
	ret = drm_mm_insert_node(&priv->vram.mm, msm_obj->vram_node, npages);
	spin_unlock(&priv->vram.lock);
	अगर (ret) अणु
		kvमुक्त(p);
		वापस ERR_PTR(ret);
	पूर्ण

	paddr = physaddr(obj);
	क्रम (i = 0; i < npages; i++) अणु
		p[i] = phys_to_page(paddr);
		paddr += PAGE_SIZE;
	पूर्ण

	वापस p;
पूर्ण

अटल काष्ठा page **get_pages(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);

	GEM_WARN_ON(!msm_gem_is_locked(obj));

	अगर (!msm_obj->pages) अणु
		काष्ठा drm_device *dev = obj->dev;
		काष्ठा page **p;
		पूर्णांक npages = obj->size >> PAGE_SHIFT;

		अगर (use_pages(obj))
			p = drm_gem_get_pages(obj);
		अन्यथा
			p = get_pages_vram(obj, npages);

		अगर (IS_ERR(p)) अणु
			DRM_DEV_ERROR(dev->dev, "could not get pages: %ld\n",
					PTR_ERR(p));
			वापस p;
		पूर्ण

		msm_obj->pages = p;

		msm_obj->sgt = drm_prime_pages_to_sg(obj->dev, p, npages);
		अगर (IS_ERR(msm_obj->sgt)) अणु
			व्योम *ptr = ERR_CAST(msm_obj->sgt);

			DRM_DEV_ERROR(dev->dev, "failed to allocate sgt\n");
			msm_obj->sgt = शून्य;
			वापस ptr;
		पूर्ण

		/* For non-cached buffers, ensure the new pages are clean
		 * because display controller, GPU, etc. are not coherent:
		 */
		अगर (msm_obj->flags & (MSM_BO_WC|MSM_BO_UNCACHED))
			sync_क्रम_device(msm_obj);

		GEM_WARN_ON(msm_obj->active_count);
		update_inactive(msm_obj);
	पूर्ण

	वापस msm_obj->pages;
पूर्ण

अटल व्योम put_pages_vram(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा msm_drm_निजी *priv = obj->dev->dev_निजी;

	spin_lock(&priv->vram.lock);
	drm_mm_हटाओ_node(msm_obj->vram_node);
	spin_unlock(&priv->vram.lock);

	kvमुक्त(msm_obj->pages);
पूर्ण

अटल व्योम put_pages(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);

	अगर (msm_obj->pages) अणु
		अगर (msm_obj->sgt) अणु
			/* For non-cached buffers, ensure the new
			 * pages are clean because display controller,
			 * GPU, etc. are not coherent:
			 */
			अगर (msm_obj->flags & (MSM_BO_WC|MSM_BO_UNCACHED))
				sync_क्रम_cpu(msm_obj);

			sg_मुक्त_table(msm_obj->sgt);
			kमुक्त(msm_obj->sgt);
			msm_obj->sgt = शून्य;
		पूर्ण

		अगर (use_pages(obj))
			drm_gem_put_pages(obj, msm_obj->pages, true, false);
		अन्यथा
			put_pages_vram(obj);

		msm_obj->pages = शून्य;
	पूर्ण
पूर्ण

काष्ठा page **msm_gem_get_pages(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा page **p;

	msm_gem_lock(obj);

	अगर (GEM_WARN_ON(msm_obj->madv != MSM_MADV_WILLNEED)) अणु
		msm_gem_unlock(obj);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	p = get_pages(obj);

	अगर (!IS_ERR(p)) अणु
		msm_obj->pin_count++;
		update_inactive(msm_obj);
	पूर्ण

	msm_gem_unlock(obj);
	वापस p;
पूर्ण

व्योम msm_gem_put_pages(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);

	msm_gem_lock(obj);
	msm_obj->pin_count--;
	GEM_WARN_ON(msm_obj->pin_count < 0);
	update_inactive(msm_obj);
	msm_gem_unlock(obj);
पूर्ण

पूर्णांक msm_gem_mmap_obj(काष्ठा drm_gem_object *obj,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);

	vma->vm_flags &= ~VM_PFNMAP;
	vma->vm_flags |= VM_MIXEDMAP;

	अगर (msm_obj->flags & MSM_BO_WC) अणु
		vma->vm_page_prot = pgprot_ग_लिखोcombine(vm_get_page_prot(vma->vm_flags));
	पूर्ण अन्यथा अगर (msm_obj->flags & MSM_BO_UNCACHED) अणु
		vma->vm_page_prot = pgprot_noncached(vm_get_page_prot(vma->vm_flags));
	पूर्ण अन्यथा अणु
		/*
		 * Shunt off cached objs to shmem file so they have their own
		 * address_space (so unmap_mapping_range करोes what we want,
		 * in particular in the हाल of mmap'd dmabufs)
		 */
		vma->vm_pgoff = 0;
		vma_set_file(vma, obj->filp);

		vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक msm_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;

	ret = drm_gem_mmap(filp, vma);
	अगर (ret) अणु
		DBG("mmap failed: %d", ret);
		वापस ret;
	पूर्ण

	वापस msm_gem_mmap_obj(vma->vm_निजी_data, vma);
पूर्ण

अटल vm_fault_t msm_gem_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा drm_gem_object *obj = vma->vm_निजी_data;
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा page **pages;
	अचिन्हित दीर्घ pfn;
	pgoff_t pgoff;
	पूर्णांक err;
	vm_fault_t ret;

	/*
	 * vm_ops.खोलो/drm_gem_mmap_obj and बंद get and put
	 * a reference on obj. So, we करोnt need to hold one here.
	 */
	err = msm_gem_lock_पूर्णांकerruptible(obj);
	अगर (err) अणु
		ret = VM_FAULT_NOPAGE;
		जाओ out;
	पूर्ण

	अगर (GEM_WARN_ON(msm_obj->madv != MSM_MADV_WILLNEED)) अणु
		msm_gem_unlock(obj);
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	/* make sure we have pages attached now */
	pages = get_pages(obj);
	अगर (IS_ERR(pages)) अणु
		ret = vmf_error(PTR_ERR(pages));
		जाओ out_unlock;
	पूर्ण

	/* We करोn't use vmf->pgoff since that has the fake offset: */
	pgoff = (vmf->address - vma->vm_start) >> PAGE_SHIFT;

	pfn = page_to_pfn(pages[pgoff]);

	VERB("Inserting %p pfn %lx, pa %lx", (व्योम *)vmf->address,
			pfn, pfn << PAGE_SHIFT);

	ret = vmf_insert_mixed(vma, vmf->address, __pfn_to_pfn_t(pfn, PFN_DEV));
out_unlock:
	msm_gem_unlock(obj);
out:
	वापस ret;
पूर्ण

/** get mmap offset */
अटल uपूर्णांक64_t mmap_offset(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_device *dev = obj->dev;
	पूर्णांक ret;

	GEM_WARN_ON(!msm_gem_is_locked(obj));

	/* Make it mmapable */
	ret = drm_gem_create_mmap_offset(obj);

	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "could not allocate mmap offset\n");
		वापस 0;
	पूर्ण

	वापस drm_vma_node_offset_addr(&obj->vma_node);
पूर्ण

uपूर्णांक64_t msm_gem_mmap_offset(काष्ठा drm_gem_object *obj)
अणु
	uपूर्णांक64_t offset;

	msm_gem_lock(obj);
	offset = mmap_offset(obj);
	msm_gem_unlock(obj);
	वापस offset;
पूर्ण

अटल काष्ठा msm_gem_vma *add_vma(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा msm_gem_vma *vma;

	GEM_WARN_ON(!msm_gem_is_locked(obj));

	vma = kzalloc(माप(*vma), GFP_KERNEL);
	अगर (!vma)
		वापस ERR_PTR(-ENOMEM);

	vma->aspace = aspace;

	list_add_tail(&vma->list, &msm_obj->vmas);

	वापस vma;
पूर्ण

अटल काष्ठा msm_gem_vma *lookup_vma(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा msm_gem_vma *vma;

	GEM_WARN_ON(!msm_gem_is_locked(obj));

	list_क्रम_each_entry(vma, &msm_obj->vmas, list) अणु
		अगर (vma->aspace == aspace)
			वापस vma;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम del_vma(काष्ठा msm_gem_vma *vma)
अणु
	अगर (!vma)
		वापस;

	list_del(&vma->list);
	kमुक्त(vma);
पूर्ण

/**
 * If बंद is true, this also बंदs the VMA (releasing the allocated
 * iova range) in addition to removing the iommu mapping.  In the eviction
 * हाल (!बंद), we keep the iova allocated, but only हटाओ the iommu
 * mapping.
 */
अटल व्योम
put_iova_spaces(काष्ठा drm_gem_object *obj, bool बंद)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा msm_gem_vma *vma;

	GEM_WARN_ON(!msm_gem_is_locked(obj));

	list_क्रम_each_entry(vma, &msm_obj->vmas, list) अणु
		अगर (vma->aspace) अणु
			msm_gem_purge_vma(vma->aspace, vma);
			अगर (बंद)
				msm_gem_बंद_vma(vma->aspace, vma);
		पूर्ण
	पूर्ण
पूर्ण

/* Called with msm_obj locked */
अटल व्योम
put_iova_vmas(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा msm_gem_vma *vma, *पंचांगp;

	GEM_WARN_ON(!msm_gem_is_locked(obj));

	list_क्रम_each_entry_safe(vma, पंचांगp, &msm_obj->vmas, list) अणु
		del_vma(vma);
	पूर्ण
पूर्ण

अटल पूर्णांक get_iova_locked(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace, uपूर्णांक64_t *iova,
		u64 range_start, u64 range_end)
अणु
	काष्ठा msm_gem_vma *vma;
	पूर्णांक ret = 0;

	GEM_WARN_ON(!msm_gem_is_locked(obj));

	vma = lookup_vma(obj, aspace);

	अगर (!vma) अणु
		vma = add_vma(obj, aspace);
		अगर (IS_ERR(vma))
			वापस PTR_ERR(vma);

		ret = msm_gem_init_vma(aspace, vma, obj->size >> PAGE_SHIFT,
			range_start, range_end);
		अगर (ret) अणु
			del_vma(vma);
			वापस ret;
		पूर्ण
	पूर्ण

	*iova = vma->iova;
	वापस 0;
पूर्ण

अटल पूर्णांक msm_gem_pin_iova(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा msm_gem_vma *vma;
	काष्ठा page **pages;
	पूर्णांक ret, prot = IOMMU_READ;

	अगर (!(msm_obj->flags & MSM_BO_GPU_READONLY))
		prot |= IOMMU_WRITE;

	अगर (msm_obj->flags & MSM_BO_MAP_PRIV)
		prot |= IOMMU_PRIV;

	GEM_WARN_ON(!msm_gem_is_locked(obj));

	अगर (GEM_WARN_ON(msm_obj->madv != MSM_MADV_WILLNEED))
		वापस -EBUSY;

	vma = lookup_vma(obj, aspace);
	अगर (GEM_WARN_ON(!vma))
		वापस -EINVAL;

	pages = get_pages(obj);
	अगर (IS_ERR(pages))
		वापस PTR_ERR(pages);

	ret = msm_gem_map_vma(aspace, vma, prot,
			msm_obj->sgt, obj->size >> PAGE_SHIFT);

	अगर (!ret)
		msm_obj->pin_count++;

	वापस ret;
पूर्ण

अटल पूर्णांक get_and_pin_iova_range_locked(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace, uपूर्णांक64_t *iova,
		u64 range_start, u64 range_end)
अणु
	u64 local;
	पूर्णांक ret;

	GEM_WARN_ON(!msm_gem_is_locked(obj));

	ret = get_iova_locked(obj, aspace, &local,
		range_start, range_end);

	अगर (!ret)
		ret = msm_gem_pin_iova(obj, aspace);

	अगर (!ret)
		*iova = local;

	वापस ret;
पूर्ण

/*
 * get iova and pin it. Should have a matching put
 * limits iova to specअगरied range (in pages)
 */
पूर्णांक msm_gem_get_and_pin_iova_range(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace, uपूर्णांक64_t *iova,
		u64 range_start, u64 range_end)
अणु
	पूर्णांक ret;

	msm_gem_lock(obj);
	ret = get_and_pin_iova_range_locked(obj, aspace, iova, range_start, range_end);
	msm_gem_unlock(obj);

	वापस ret;
पूर्ण

पूर्णांक msm_gem_get_and_pin_iova_locked(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace, uपूर्णांक64_t *iova)
अणु
	वापस get_and_pin_iova_range_locked(obj, aspace, iova, 0, U64_MAX);
पूर्ण

/* get iova and pin it. Should have a matching put */
पूर्णांक msm_gem_get_and_pin_iova(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace, uपूर्णांक64_t *iova)
अणु
	वापस msm_gem_get_and_pin_iova_range(obj, aspace, iova, 0, U64_MAX);
पूर्ण

/*
 * Get an iova but करोn't pin it. Doesn't need a put because iovas are currently
 * valid क्रम the lअगरe of the object
 */
पूर्णांक msm_gem_get_iova(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace, uपूर्णांक64_t *iova)
अणु
	पूर्णांक ret;

	msm_gem_lock(obj);
	ret = get_iova_locked(obj, aspace, iova, 0, U64_MAX);
	msm_gem_unlock(obj);

	वापस ret;
पूर्ण

/* get iova without taking a reference, used in places where you have
 * alपढ़ोy करोne a 'msm_gem_get_and_pin_iova' or 'msm_gem_get_iova'
 */
uपूर्णांक64_t msm_gem_iova(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace)
अणु
	काष्ठा msm_gem_vma *vma;

	msm_gem_lock(obj);
	vma = lookup_vma(obj, aspace);
	msm_gem_unlock(obj);
	GEM_WARN_ON(!vma);

	वापस vma ? vma->iova : 0;
पूर्ण

/*
 * Locked variant of msm_gem_unpin_iova()
 */
व्योम msm_gem_unpin_iova_locked(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा msm_gem_vma *vma;

	GEM_WARN_ON(!msm_gem_is_locked(obj));

	vma = lookup_vma(obj, aspace);

	अगर (!GEM_WARN_ON(!vma)) अणु
		msm_gem_unmap_vma(aspace, vma);

		msm_obj->pin_count--;
		GEM_WARN_ON(msm_obj->pin_count < 0);

		update_inactive(msm_obj);
	पूर्ण
पूर्ण

/*
 * Unpin a iova by updating the reference counts. The memory isn't actually
 * purged until something अन्यथा (shrinker, mm_notअगरier, destroy, etc) decides
 * to get rid of it
 */
व्योम msm_gem_unpin_iova(काष्ठा drm_gem_object *obj,
		काष्ठा msm_gem_address_space *aspace)
अणु
	msm_gem_lock(obj);
	msm_gem_unpin_iova_locked(obj, aspace);
	msm_gem_unlock(obj);
पूर्ण

पूर्णांक msm_gem_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
		काष्ठा drm_mode_create_dumb *args)
अणु
	args->pitch = align_pitch(args->width, args->bpp);
	args->size  = PAGE_ALIGN(args->pitch * args->height);
	वापस msm_gem_new_handle(dev, file, args->size,
			MSM_BO_SCANOUT | MSM_BO_WC, &args->handle, "dumb");
पूर्ण

पूर्णांक msm_gem_dumb_map_offset(काष्ठा drm_file *file, काष्ठा drm_device *dev,
		uपूर्णांक32_t handle, uपूर्णांक64_t *offset)
अणु
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret = 0;

	/* GEM करोes all our handle to object mapping */
	obj = drm_gem_object_lookup(file, handle);
	अगर (obj == शून्य) अणु
		ret = -ENOENT;
		जाओ fail;
	पूर्ण

	*offset = msm_gem_mmap_offset(obj);

	drm_gem_object_put(obj);

fail:
	वापस ret;
पूर्ण

अटल व्योम *get_vaddr(काष्ठा drm_gem_object *obj, अचिन्हित madv)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	पूर्णांक ret = 0;

	GEM_WARN_ON(!msm_gem_is_locked(obj));

	अगर (obj->import_attach)
		वापस ERR_PTR(-ENODEV);

	अगर (GEM_WARN_ON(msm_obj->madv > madv)) अणु
		DRM_DEV_ERROR(obj->dev->dev, "Invalid madv state: %u vs %u\n",
			msm_obj->madv, madv);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	/* increment vmap_count *beक्रमe* vmap() call, so shrinker can
	 * check vmap_count (is_vunmapable()) outside of msm_obj lock.
	 * This guarantees that we won't try to msm_gem_vunmap() this
	 * same object from within the vmap() call (जबतक we alपढ़ोy
	 * hold msm_obj lock)
	 */
	msm_obj->vmap_count++;

	अगर (!msm_obj->vaddr) अणु
		काष्ठा page **pages = get_pages(obj);
		अगर (IS_ERR(pages)) अणु
			ret = PTR_ERR(pages);
			जाओ fail;
		पूर्ण
		msm_obj->vaddr = vmap(pages, obj->size >> PAGE_SHIFT,
				VM_MAP, pgprot_ग_लिखोcombine(PAGE_KERNEL));
		अगर (msm_obj->vaddr == शून्य) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		update_inactive(msm_obj);
	पूर्ण

	वापस msm_obj->vaddr;

fail:
	msm_obj->vmap_count--;
	वापस ERR_PTR(ret);
पूर्ण

व्योम *msm_gem_get_vaddr_locked(काष्ठा drm_gem_object *obj)
अणु
	वापस get_vaddr(obj, MSM_MADV_WILLNEED);
पूर्ण

व्योम *msm_gem_get_vaddr(काष्ठा drm_gem_object *obj)
अणु
	व्योम *ret;

	msm_gem_lock(obj);
	ret = msm_gem_get_vaddr_locked(obj);
	msm_gem_unlock(obj);

	वापस ret;
पूर्ण

/*
 * Don't use this!  It is क्रम the very special हाल of dumping
 * submits from GPU hangs or faults, were the bo may alपढ़ोy
 * be MSM_MADV_DONTNEED, but we know the buffer is still on the
 * active list.
 */
व्योम *msm_gem_get_vaddr_active(काष्ठा drm_gem_object *obj)
अणु
	वापस get_vaddr(obj, __MSM_MADV_PURGED);
पूर्ण

व्योम msm_gem_put_vaddr_locked(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);

	GEM_WARN_ON(!msm_gem_is_locked(obj));
	GEM_WARN_ON(msm_obj->vmap_count < 1);

	msm_obj->vmap_count--;
पूर्ण

व्योम msm_gem_put_vaddr(काष्ठा drm_gem_object *obj)
अणु
	msm_gem_lock(obj);
	msm_gem_put_vaddr_locked(obj);
	msm_gem_unlock(obj);
पूर्ण

/* Update madvise status, वापसs true अगर not purged, अन्यथा
 * false or -त्रुटि_सं.
 */
पूर्णांक msm_gem_madvise(काष्ठा drm_gem_object *obj, अचिन्हित madv)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);

	msm_gem_lock(obj);

	अगर (msm_obj->madv != __MSM_MADV_PURGED)
		msm_obj->madv = madv;

	madv = msm_obj->madv;

	/* If the obj is inactive, we might need to move it
	 * between inactive lists
	 */
	अगर (msm_obj->active_count == 0)
		update_inactive(msm_obj);

	msm_gem_unlock(obj);

	वापस (madv != __MSM_MADV_PURGED);
पूर्ण

व्योम msm_gem_purge(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_device *dev = obj->dev;
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);

	GEM_WARN_ON(!msm_gem_is_locked(obj));
	GEM_WARN_ON(!is_purgeable(msm_obj));

	/* Get rid of any iommu mapping(s): */
	put_iova_spaces(obj, true);

	msm_gem_vunmap(obj);

	drm_vma_node_unmap(&obj->vma_node, dev->anon_inode->i_mapping);

	put_pages(obj);

	put_iova_vmas(obj);

	msm_obj->madv = __MSM_MADV_PURGED;
	update_inactive(msm_obj);

	drm_gem_मुक्त_mmap_offset(obj);

	/* Our goal here is to वापस as much of the memory as
	 * is possible back to the प्रणाली as we are called from OOM.
	 * To करो this we must inकाष्ठा the shmfs to drop all of its
	 * backing pages, *now*.
	 */
	shmem_truncate_range(file_inode(obj->filp), 0, (loff_t)-1);

	invalidate_mapping_pages(file_inode(obj->filp)->i_mapping,
			0, (loff_t)-1);
पूर्ण

/**
 * Unpin the backing pages and make them available to be swapped out.
 */
व्योम msm_gem_evict(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_device *dev = obj->dev;
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);

	GEM_WARN_ON(!msm_gem_is_locked(obj));
	GEM_WARN_ON(is_unevictable(msm_obj));
	GEM_WARN_ON(!msm_obj->evictable);
	GEM_WARN_ON(msm_obj->active_count);

	/* Get rid of any iommu mapping(s): */
	put_iova_spaces(obj, false);

	drm_vma_node_unmap(&obj->vma_node, dev->anon_inode->i_mapping);

	put_pages(obj);

	update_inactive(msm_obj);
पूर्ण

व्योम msm_gem_vunmap(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);

	GEM_WARN_ON(!msm_gem_is_locked(obj));

	अगर (!msm_obj->vaddr || GEM_WARN_ON(!is_vunmapable(msm_obj)))
		वापस;

	vunmap(msm_obj->vaddr);
	msm_obj->vaddr = शून्य;
पूर्ण

/* must be called beक्रमe _move_to_active().. */
पूर्णांक msm_gem_sync_object(काष्ठा drm_gem_object *obj,
		काष्ठा msm_fence_context *fctx, bool exclusive)
अणु
	काष्ठा dma_resv_list *fobj;
	काष्ठा dma_fence *fence;
	पूर्णांक i, ret;

	fobj = dma_resv_get_list(obj->resv);
	अगर (!fobj || (fobj->shared_count == 0)) अणु
		fence = dma_resv_get_excl(obj->resv);
		/* करोn't need to रुको on our own fences, since ring is fअगरo */
		अगर (fence && (fence->context != fctx->context)) अणु
			ret = dma_fence_रुको(fence, true);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (!exclusive || !fobj)
		वापस 0;

	क्रम (i = 0; i < fobj->shared_count; i++) अणु
		fence = rcu_dereference_रक्षित(fobj->shared[i],
						dma_resv_held(obj->resv));
		अगर (fence->context != fctx->context) अणु
			ret = dma_fence_रुको(fence, true);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम msm_gem_active_get(काष्ठा drm_gem_object *obj, काष्ठा msm_gpu *gpu)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा msm_drm_निजी *priv = obj->dev->dev_निजी;

	might_sleep();
	GEM_WARN_ON(!msm_gem_is_locked(obj));
	GEM_WARN_ON(msm_obj->madv != MSM_MADV_WILLNEED);
	GEM_WARN_ON(msm_obj->करोntneed);
	GEM_WARN_ON(!msm_obj->sgt);

	अगर (msm_obj->active_count++ == 0) अणु
		mutex_lock(&priv->mm_lock);
		अगर (msm_obj->evictable)
			mark_unevictable(msm_obj);
		list_del(&msm_obj->mm_list);
		list_add_tail(&msm_obj->mm_list, &gpu->active_list);
		mutex_unlock(&priv->mm_lock);
	पूर्ण
पूर्ण

व्योम msm_gem_active_put(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);

	might_sleep();
	GEM_WARN_ON(!msm_gem_is_locked(obj));

	अगर (--msm_obj->active_count == 0) अणु
		update_inactive(msm_obj);
	पूर्ण
पूर्ण

अटल व्योम update_inactive(काष्ठा msm_gem_object *msm_obj)
अणु
	काष्ठा msm_drm_निजी *priv = msm_obj->base.dev->dev_निजी;

	GEM_WARN_ON(!msm_gem_is_locked(&msm_obj->base));

	अगर (msm_obj->active_count != 0)
		वापस;

	mutex_lock(&priv->mm_lock);

	अगर (msm_obj->करोntneed)
		mark_unpurgeable(msm_obj);
	अगर (msm_obj->evictable)
		mark_unevictable(msm_obj);

	list_del(&msm_obj->mm_list);
	अगर ((msm_obj->madv == MSM_MADV_WILLNEED) && msm_obj->sgt) अणु
		list_add_tail(&msm_obj->mm_list, &priv->inactive_willneed);
		mark_evictable(msm_obj);
	पूर्ण अन्यथा अगर (msm_obj->madv == MSM_MADV_DONTNEED) अणु
		list_add_tail(&msm_obj->mm_list, &priv->inactive_करोntneed);
		mark_purgeable(msm_obj);
	पूर्ण अन्यथा अणु
		GEM_WARN_ON((msm_obj->madv != __MSM_MADV_PURGED) && msm_obj->sgt);
		list_add_tail(&msm_obj->mm_list, &priv->inactive_unpinned);
	पूर्ण

	mutex_unlock(&priv->mm_lock);
पूर्ण

पूर्णांक msm_gem_cpu_prep(काष्ठा drm_gem_object *obj, uपूर्णांक32_t op, kसमय_प्रकार *समयout)
अणु
	bool ग_लिखो = !!(op & MSM_PREP_WRITE);
	अचिन्हित दीर्घ reमुख्य =
		op & MSM_PREP_NOSYNC ? 0 : समयout_to_jअगरfies(समयout);
	दीर्घ ret;

	ret = dma_resv_रुको_समयout_rcu(obj->resv, ग_लिखो,
						  true,  reमुख्य);
	अगर (ret == 0)
		वापस reमुख्य == 0 ? -EBUSY : -ETIMEDOUT;
	अन्यथा अगर (ret < 0)
		वापस ret;

	/* TODO cache मुख्यtenance */

	वापस 0;
पूर्ण

पूर्णांक msm_gem_cpu_fini(काष्ठा drm_gem_object *obj)
अणु
	/* TODO cache मुख्यtenance */
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम describe_fence(काष्ठा dma_fence *fence, स्थिर अक्षर *type,
		काष्ठा seq_file *m)
अणु
	अगर (!dma_fence_is_संकेतed(fence))
		seq_म_लिखो(m, "\t%9s: %s %s seq %llu\n", type,
				fence->ops->get_driver_name(fence),
				fence->ops->get_समयline_name(fence),
				fence->seqno);
पूर्ण

व्योम msm_gem_describe(काष्ठा drm_gem_object *obj, काष्ठा seq_file *m,
		काष्ठा msm_gem_stats *stats)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा dma_resv *robj = obj->resv;
	काष्ठा dma_resv_list *fobj;
	काष्ठा dma_fence *fence;
	काष्ठा msm_gem_vma *vma;
	uपूर्णांक64_t off = drm_vma_node_start(&obj->vma_node);
	स्थिर अक्षर *madv;

	msm_gem_lock(obj);

	stats->all.count++;
	stats->all.size += obj->size;

	अगर (is_active(msm_obj)) अणु
		stats->active.count++;
		stats->active.size += obj->size;
	पूर्ण

	अगर (msm_obj->pages) अणु
		stats->resident.count++;
		stats->resident.size += obj->size;
	पूर्ण

	चयन (msm_obj->madv) अणु
	हाल __MSM_MADV_PURGED:
		stats->purged.count++;
		stats->purged.size += obj->size;
		madv = " purged";
		अवरोध;
	हाल MSM_MADV_DONTNEED:
		stats->purgeable.count++;
		stats->purgeable.size += obj->size;
		madv = " purgeable";
		अवरोध;
	हाल MSM_MADV_WILLNEED:
	शेष:
		madv = "";
		अवरोध;
	पूर्ण

	seq_म_लिखो(m, "%08x: %c %2d (%2d) %08llx %p",
			msm_obj->flags, is_active(msm_obj) ? 'A' : 'I',
			obj->name, kref_पढ़ो(&obj->refcount),
			off, msm_obj->vaddr);

	seq_म_लिखो(m, " %08zu %9s %-32s\n", obj->size, madv, msm_obj->name);

	अगर (!list_empty(&msm_obj->vmas)) अणु

		seq_माला_दो(m, "      vmas:");

		list_क्रम_each_entry(vma, &msm_obj->vmas, list) अणु
			स्थिर अक्षर *name, *comm;
			अगर (vma->aspace) अणु
				काष्ठा msm_gem_address_space *aspace = vma->aspace;
				काष्ठा task_काष्ठा *task =
					get_pid_task(aspace->pid, PIDTYPE_PID);
				अगर (task) अणु
					comm = kstrdup(task->comm, GFP_KERNEL);
				पूर्ण अन्यथा अणु
					comm = शून्य;
				पूर्ण
				name = aspace->name;
			पूर्ण अन्यथा अणु
				name = comm = शून्य;
			पूर्ण
			seq_म_लिखो(m, " [%s%s%s: aspace=%p, %08llx,%s,inuse=%d]",
				name, comm ? ":" : "", comm ? comm : "",
				vma->aspace, vma->iova,
				vma->mapped ? "mapped" : "unmapped",
				vma->inuse);
			kमुक्त(comm);
		पूर्ण

		seq_माला_दो(m, "\n");
	पूर्ण

	rcu_पढ़ो_lock();
	fobj = rcu_dereference(robj->fence);
	अगर (fobj) अणु
		अचिन्हित पूर्णांक i, shared_count = fobj->shared_count;

		क्रम (i = 0; i < shared_count; i++) अणु
			fence = rcu_dereference(fobj->shared[i]);
			describe_fence(fence, "Shared", m);
		पूर्ण
	पूर्ण

	fence = rcu_dereference(robj->fence_excl);
	अगर (fence)
		describe_fence(fence, "Exclusive", m);
	rcu_पढ़ो_unlock();

	msm_gem_unlock(obj);
पूर्ण

व्योम msm_gem_describe_objects(काष्ठा list_head *list, काष्ठा seq_file *m)
अणु
	काष्ठा msm_gem_stats stats = अणुपूर्ण;
	काष्ठा msm_gem_object *msm_obj;

	seq_माला_दो(m, "   flags       id ref  offset   kaddr            size     madv      name\n");
	list_क्रम_each_entry(msm_obj, list, node) अणु
		काष्ठा drm_gem_object *obj = &msm_obj->base;
		seq_माला_दो(m, "   ");
		msm_gem_describe(obj, m, &stats);
	पूर्ण

	seq_म_लिखो(m, "Total:     %4d objects, %9zu bytes\n",
			stats.all.count, stats.all.size);
	seq_म_लिखो(m, "Active:    %4d objects, %9zu bytes\n",
			stats.active.count, stats.active.size);
	seq_म_लिखो(m, "Resident:  %4d objects, %9zu bytes\n",
			stats.resident.count, stats.resident.size);
	seq_म_लिखो(m, "Purgeable: %4d objects, %9zu bytes\n",
			stats.purgeable.count, stats.purgeable.size);
	seq_म_लिखो(m, "Purged:    %4d objects, %9zu bytes\n",
			stats.purged.count, stats.purged.size);
पूर्ण
#पूर्ण_अगर

/* करोn't call directly!  Use drm_gem_object_put_locked() and मित्रs */
व्योम msm_gem_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	काष्ठा drm_device *dev = obj->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;

	mutex_lock(&priv->obj_lock);
	list_del(&msm_obj->node);
	mutex_unlock(&priv->obj_lock);

	mutex_lock(&priv->mm_lock);
	अगर (msm_obj->करोntneed)
		mark_unpurgeable(msm_obj);
	list_del(&msm_obj->mm_list);
	mutex_unlock(&priv->mm_lock);

	msm_gem_lock(obj);

	/* object should not be on active list: */
	GEM_WARN_ON(is_active(msm_obj));

	put_iova_spaces(obj, true);

	अगर (obj->import_attach) अणु
		GEM_WARN_ON(msm_obj->vaddr);

		/* Don't drop the pages क्रम imported dmabuf, as they are not
		 * ours, just मुक्त the array we allocated:
		 */
		kvमुक्त(msm_obj->pages);

		put_iova_vmas(obj);

		/* dma_buf_detach() grअसल resv lock, so we need to unlock
		 * prior to drm_prime_gem_destroy
		 */
		msm_gem_unlock(obj);

		drm_prime_gem_destroy(obj, msm_obj->sgt);
	पूर्ण अन्यथा अणु
		msm_gem_vunmap(obj);
		put_pages(obj);
		put_iova_vmas(obj);
		msm_gem_unlock(obj);
	पूर्ण

	drm_gem_object_release(obj);

	kमुक्त(msm_obj);
पूर्ण

/* convenience method to स्थिरruct a GEM buffer object, and userspace handle */
पूर्णांक msm_gem_new_handle(काष्ठा drm_device *dev, काष्ठा drm_file *file,
		uपूर्णांक32_t size, uपूर्णांक32_t flags, uपूर्णांक32_t *handle,
		अक्षर *name)
अणु
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	obj = msm_gem_new(dev, size, flags);

	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	अगर (name)
		msm_gem_object_set_name(obj, "%s", name);

	ret = drm_gem_handle_create(file, obj, handle);

	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put(obj);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा vm_ops = अणु
	.fault = msm_gem_fault,
	.खोलो = drm_gem_vm_खोलो,
	.बंद = drm_gem_vm_बंद,
पूर्ण;

अटल स्थिर काष्ठा drm_gem_object_funcs msm_gem_object_funcs = अणु
	.मुक्त = msm_gem_मुक्त_object,
	.pin = msm_gem_prime_pin,
	.unpin = msm_gem_prime_unpin,
	.get_sg_table = msm_gem_prime_get_sg_table,
	.vmap = msm_gem_prime_vmap,
	.vunmap = msm_gem_prime_vunmap,
	.vm_ops = &vm_ops,
पूर्ण;

अटल पूर्णांक msm_gem_new_impl(काष्ठा drm_device *dev,
		uपूर्णांक32_t size, uपूर्णांक32_t flags,
		काष्ठा drm_gem_object **obj)
अणु
	काष्ठा msm_gem_object *msm_obj;

	चयन (flags & MSM_BO_CACHE_MASK) अणु
	हाल MSM_BO_UNCACHED:
	हाल MSM_BO_CACHED:
	हाल MSM_BO_WC:
		अवरोध;
	शेष:
		DRM_DEV_ERROR(dev->dev, "invalid cache flag: %x\n",
				(flags & MSM_BO_CACHE_MASK));
		वापस -EINVAL;
	पूर्ण

	msm_obj = kzalloc(माप(*msm_obj), GFP_KERNEL);
	अगर (!msm_obj)
		वापस -ENOMEM;

	msm_obj->flags = flags;
	msm_obj->madv = MSM_MADV_WILLNEED;

	INIT_LIST_HEAD(&msm_obj->submit_entry);
	INIT_LIST_HEAD(&msm_obj->vmas);

	*obj = &msm_obj->base;
	(*obj)->funcs = &msm_gem_object_funcs;

	वापस 0;
पूर्ण

अटल काष्ठा drm_gem_object *_msm_gem_new(काष्ठा drm_device *dev,
		uपूर्णांक32_t size, uपूर्णांक32_t flags, bool काष्ठा_mutex_locked)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_gem_object *msm_obj;
	काष्ठा drm_gem_object *obj = शून्य;
	bool use_vram = false;
	पूर्णांक ret;

	size = PAGE_ALIGN(size);

	अगर (!msm_use_mmu(dev))
		use_vram = true;
	अन्यथा अगर ((flags & (MSM_BO_STOLEN | MSM_BO_SCANOUT)) && priv->vram.size)
		use_vram = true;

	अगर (GEM_WARN_ON(use_vram && !priv->vram.size))
		वापस ERR_PTR(-EINVAL);

	/* Disallow zero sized objects as they make the underlying
	 * infraकाष्ठाure grumpy
	 */
	अगर (size == 0)
		वापस ERR_PTR(-EINVAL);

	ret = msm_gem_new_impl(dev, size, flags, &obj);
	अगर (ret)
		जाओ fail;

	msm_obj = to_msm_bo(obj);

	अगर (use_vram) अणु
		काष्ठा msm_gem_vma *vma;
		काष्ठा page **pages;

		drm_gem_निजी_object_init(dev, obj, size);

		msm_gem_lock(obj);

		vma = add_vma(obj, शून्य);
		msm_gem_unlock(obj);
		अगर (IS_ERR(vma)) अणु
			ret = PTR_ERR(vma);
			जाओ fail;
		पूर्ण

		to_msm_bo(obj)->vram_node = &vma->node;

		/* Call chain get_pages() -> update_inactive() tries to
		 * access msm_obj->mm_list, but it is not initialized yet.
		 * To aव्योम शून्य poपूर्णांकer dereference error, initialize
		 * mm_list to be empty.
		 */
		INIT_LIST_HEAD(&msm_obj->mm_list);

		msm_gem_lock(obj);
		pages = get_pages(obj);
		msm_gem_unlock(obj);
		अगर (IS_ERR(pages)) अणु
			ret = PTR_ERR(pages);
			जाओ fail;
		पूर्ण

		vma->iova = physaddr(obj);
	पूर्ण अन्यथा अणु
		ret = drm_gem_object_init(dev, obj, size);
		अगर (ret)
			जाओ fail;
		/*
		 * Our buffers are kept pinned, so allocating them from the
		 * MOVABLE zone is a really bad idea, and conflicts with CMA.
		 * See comments above new_inode() why this is required _and_
		 * expected अगर you're going to pin these pages.
		 */
		mapping_set_gfp_mask(obj->filp->f_mapping, GFP_HIGHUSER);
	पूर्ण

	mutex_lock(&priv->mm_lock);
	list_add_tail(&msm_obj->mm_list, &priv->inactive_unpinned);
	mutex_unlock(&priv->mm_lock);

	mutex_lock(&priv->obj_lock);
	list_add_tail(&msm_obj->node, &priv->objects);
	mutex_unlock(&priv->obj_lock);

	वापस obj;

fail:
	अगर (काष्ठा_mutex_locked) अणु
		drm_gem_object_put_locked(obj);
	पूर्ण अन्यथा अणु
		drm_gem_object_put(obj);
	पूर्ण
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा drm_gem_object *msm_gem_new_locked(काष्ठा drm_device *dev,
		uपूर्णांक32_t size, uपूर्णांक32_t flags)
अणु
	वापस _msm_gem_new(dev, size, flags, true);
पूर्ण

काष्ठा drm_gem_object *msm_gem_new(काष्ठा drm_device *dev,
		uपूर्णांक32_t size, uपूर्णांक32_t flags)
अणु
	वापस _msm_gem_new(dev, size, flags, false);
पूर्ण

काष्ठा drm_gem_object *msm_gem_import(काष्ठा drm_device *dev,
		काष्ठा dma_buf *dmabuf, काष्ठा sg_table *sgt)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_gem_object *msm_obj;
	काष्ठा drm_gem_object *obj;
	uपूर्णांक32_t size;
	पूर्णांक ret, npages;

	/* अगर we करोn't have IOMMU, don't bother pretending we can import: */
	अगर (!msm_use_mmu(dev)) अणु
		DRM_DEV_ERROR(dev->dev, "cannot import without IOMMU\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	size = PAGE_ALIGN(dmabuf->size);

	ret = msm_gem_new_impl(dev, size, MSM_BO_WC, &obj);
	अगर (ret)
		जाओ fail;

	drm_gem_निजी_object_init(dev, obj, size);

	npages = size / PAGE_SIZE;

	msm_obj = to_msm_bo(obj);
	msm_gem_lock(obj);
	msm_obj->sgt = sgt;
	msm_obj->pages = kvदो_स्मृति_array(npages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!msm_obj->pages) अणु
		msm_gem_unlock(obj);
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	ret = drm_prime_sg_to_page_array(sgt, msm_obj->pages, npages);
	अगर (ret) अणु
		msm_gem_unlock(obj);
		जाओ fail;
	पूर्ण

	msm_gem_unlock(obj);

	mutex_lock(&priv->mm_lock);
	list_add_tail(&msm_obj->mm_list, &priv->inactive_unpinned);
	mutex_unlock(&priv->mm_lock);

	mutex_lock(&priv->obj_lock);
	list_add_tail(&msm_obj->node, &priv->objects);
	mutex_unlock(&priv->obj_lock);

	वापस obj;

fail:
	drm_gem_object_put(obj);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम *_msm_gem_kernel_new(काष्ठा drm_device *dev, uपूर्णांक32_t size,
		uपूर्णांक32_t flags, काष्ठा msm_gem_address_space *aspace,
		काष्ठा drm_gem_object **bo, uपूर्णांक64_t *iova, bool locked)
अणु
	व्योम *vaddr;
	काष्ठा drm_gem_object *obj = _msm_gem_new(dev, size, flags, locked);
	पूर्णांक ret;

	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	अगर (iova) अणु
		ret = msm_gem_get_and_pin_iova(obj, aspace, iova);
		अगर (ret)
			जाओ err;
	पूर्ण

	vaddr = msm_gem_get_vaddr(obj);
	अगर (IS_ERR(vaddr)) अणु
		msm_gem_unpin_iova(obj, aspace);
		ret = PTR_ERR(vaddr);
		जाओ err;
	पूर्ण

	अगर (bo)
		*bo = obj;

	वापस vaddr;
err:
	अगर (locked)
		drm_gem_object_put_locked(obj);
	अन्यथा
		drm_gem_object_put(obj);

	वापस ERR_PTR(ret);

पूर्ण

व्योम *msm_gem_kernel_new(काष्ठा drm_device *dev, uपूर्णांक32_t size,
		uपूर्णांक32_t flags, काष्ठा msm_gem_address_space *aspace,
		काष्ठा drm_gem_object **bo, uपूर्णांक64_t *iova)
अणु
	वापस _msm_gem_kernel_new(dev, size, flags, aspace, bo, iova, false);
पूर्ण

व्योम *msm_gem_kernel_new_locked(काष्ठा drm_device *dev, uपूर्णांक32_t size,
		uपूर्णांक32_t flags, काष्ठा msm_gem_address_space *aspace,
		काष्ठा drm_gem_object **bo, uपूर्णांक64_t *iova)
अणु
	वापस _msm_gem_kernel_new(dev, size, flags, aspace, bo, iova, true);
पूर्ण

व्योम msm_gem_kernel_put(काष्ठा drm_gem_object *bo,
		काष्ठा msm_gem_address_space *aspace, bool locked)
अणु
	अगर (IS_ERR_OR_शून्य(bo))
		वापस;

	msm_gem_put_vaddr(bo);
	msm_gem_unpin_iova(bo, aspace);

	अगर (locked)
		drm_gem_object_put_locked(bo);
	अन्यथा
		drm_gem_object_put(bo);
पूर्ण

व्योम msm_gem_object_set_name(काष्ठा drm_gem_object *bo, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(bo);
	बहु_सूची ap;

	अगर (!fmt)
		वापस;

	बहु_शुरू(ap, fmt);
	vsnम_लिखो(msm_obj->name, माप(msm_obj->name), fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण
