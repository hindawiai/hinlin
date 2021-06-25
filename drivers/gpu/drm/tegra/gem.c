<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NVIDIA Tegra DRM GEM helper functions
 *
 * Copyright (C) 2012 Sascha Hauer, Pengutronix
 * Copyright (C) 2013-2015 NVIDIA CORPORATION, All rights reserved.
 *
 * Based on the GEM/CMA helpers
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/iommu.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_prime.h>
#समावेश <drm/tegra_drm.h>

#समावेश "drm.h"
#समावेश "gem.h"

अटल व्योम tegra_bo_put(काष्ठा host1x_bo *bo)
अणु
	काष्ठा tegra_bo *obj = host1x_to_tegra_bo(bo);

	drm_gem_object_put(&obj->gem);
पूर्ण

/* XXX move this पूर्णांकo lib/scatterlist.c? */
अटल पूर्णांक sg_alloc_table_from_sg(काष्ठा sg_table *sgt, काष्ठा scatterlist *sg,
				  अचिन्हित पूर्णांक nents, gfp_t gfp_mask)
अणु
	काष्ठा scatterlist *dst;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = sg_alloc_table(sgt, nents, gfp_mask);
	अगर (err < 0)
		वापस err;

	dst = sgt->sgl;

	क्रम (i = 0; i < nents; i++) अणु
		sg_set_page(dst, sg_page(sg), sg->length, 0);
		dst = sg_next(dst);
		sg = sg_next(sg);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sg_table *tegra_bo_pin(काष्ठा device *dev, काष्ठा host1x_bo *bo,
				     dma_addr_t *phys)
अणु
	काष्ठा tegra_bo *obj = host1x_to_tegra_bo(bo);
	काष्ठा sg_table *sgt;
	पूर्णांक err;

	/*
	 * If we've manually mapped the buffer object through the IOMMU, make
	 * sure to वापस the IOVA address of our mapping.
	 *
	 * Similarly, क्रम buffers that have been allocated by the DMA API the
	 * physical address can be used क्रम devices that are not attached to
	 * an IOMMU. For these devices, callers must pass a valid poपूर्णांकer via
	 * the @phys argument.
	 *
	 * Imported buffers were also alपढ़ोy mapped at import समय, so the
	 * existing mapping can be reused.
	 */
	अगर (phys) अणु
		*phys = obj->iova;
		वापस शून्य;
	पूर्ण

	/*
	 * If we करोn't have a mapping क्रम this buffer yet, वापस an SG table
	 * so that host1x can करो the mapping क्रम us via the DMA API.
	 */
	sgt = kzalloc(माप(*sgt), GFP_KERNEL);
	अगर (!sgt)
		वापस ERR_PTR(-ENOMEM);

	अगर (obj->pages) अणु
		/*
		 * If the buffer object was allocated from the explicit IOMMU
		 * API code paths, स्थिरruct an SG table from the pages.
		 */
		err = sg_alloc_table_from_pages(sgt, obj->pages, obj->num_pages,
						0, obj->gem.size, GFP_KERNEL);
		अगर (err < 0)
			जाओ मुक्त;
	पूर्ण अन्यथा अगर (obj->sgt) अणु
		/*
		 * If the buffer object alपढ़ोy has an SG table but no pages
		 * were allocated क्रम it, it means the buffer was imported and
		 * the SG table needs to be copied to aव्योम overwriting any
		 * other potential users of the original SG table.
		 */
		err = sg_alloc_table_from_sg(sgt, obj->sgt->sgl,
					     obj->sgt->orig_nents, GFP_KERNEL);
		अगर (err < 0)
			जाओ मुक्त;
	पूर्ण अन्यथा अणु
		/*
		 * If the buffer object had no pages allocated and अगर it was
		 * not imported, it had to be allocated with the DMA API, so
		 * the DMA API helper can be used.
		 */
		err = dma_get_sgtable(dev, sgt, obj->vaddr, obj->iova,
				      obj->gem.size);
		अगर (err < 0)
			जाओ मुक्त;
	पूर्ण

	वापस sgt;

मुक्त:
	kमुक्त(sgt);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tegra_bo_unpin(काष्ठा device *dev, काष्ठा sg_table *sgt)
अणु
	अगर (sgt) अणु
		sg_मुक्त_table(sgt);
		kमुक्त(sgt);
	पूर्ण
पूर्ण

अटल व्योम *tegra_bo_mmap(काष्ठा host1x_bo *bo)
अणु
	काष्ठा tegra_bo *obj = host1x_to_tegra_bo(bo);
	काष्ठा dma_buf_map map;
	पूर्णांक ret;

	अगर (obj->vaddr) अणु
		वापस obj->vaddr;
	पूर्ण अन्यथा अगर (obj->gem.import_attach) अणु
		ret = dma_buf_vmap(obj->gem.import_attach->dmabuf, &map);
		वापस ret ? शून्य : map.vaddr;
	पूर्ण अन्यथा अणु
		वापस vmap(obj->pages, obj->num_pages, VM_MAP,
			    pgprot_ग_लिखोcombine(PAGE_KERNEL));
	पूर्ण
पूर्ण

अटल व्योम tegra_bo_munmap(काष्ठा host1x_bo *bo, व्योम *addr)
अणु
	काष्ठा tegra_bo *obj = host1x_to_tegra_bo(bo);
	काष्ठा dma_buf_map map = DMA_BUF_MAP_INIT_VADDR(addr);

	अगर (obj->vaddr)
		वापस;
	अन्यथा अगर (obj->gem.import_attach)
		dma_buf_vunmap(obj->gem.import_attach->dmabuf, &map);
	अन्यथा
		vunmap(addr);
पूर्ण

अटल काष्ठा host1x_bo *tegra_bo_get(काष्ठा host1x_bo *bo)
अणु
	काष्ठा tegra_bo *obj = host1x_to_tegra_bo(bo);

	drm_gem_object_get(&obj->gem);

	वापस bo;
पूर्ण

अटल स्थिर काष्ठा host1x_bo_ops tegra_bo_ops = अणु
	.get = tegra_bo_get,
	.put = tegra_bo_put,
	.pin = tegra_bo_pin,
	.unpin = tegra_bo_unpin,
	.mmap = tegra_bo_mmap,
	.munmap = tegra_bo_munmap,
पूर्ण;

अटल पूर्णांक tegra_bo_iommu_map(काष्ठा tegra_drm *tegra, काष्ठा tegra_bo *bo)
अणु
	पूर्णांक prot = IOMMU_READ | IOMMU_WRITE;
	पूर्णांक err;

	अगर (bo->mm)
		वापस -EBUSY;

	bo->mm = kzalloc(माप(*bo->mm), GFP_KERNEL);
	अगर (!bo->mm)
		वापस -ENOMEM;

	mutex_lock(&tegra->mm_lock);

	err = drm_mm_insert_node_generic(&tegra->mm,
					 bo->mm, bo->gem.size, PAGE_SIZE, 0, 0);
	अगर (err < 0) अणु
		dev_err(tegra->drm->dev, "out of I/O virtual memory: %d\n",
			err);
		जाओ unlock;
	पूर्ण

	bo->iova = bo->mm->start;

	bo->size = iommu_map_sgtable(tegra->करोमुख्य, bo->iova, bo->sgt, prot);
	अगर (!bo->size) अणु
		dev_err(tegra->drm->dev, "failed to map buffer\n");
		err = -ENOMEM;
		जाओ हटाओ;
	पूर्ण

	mutex_unlock(&tegra->mm_lock);

	वापस 0;

हटाओ:
	drm_mm_हटाओ_node(bo->mm);
unlock:
	mutex_unlock(&tegra->mm_lock);
	kमुक्त(bo->mm);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_bo_iommu_unmap(काष्ठा tegra_drm *tegra, काष्ठा tegra_bo *bo)
अणु
	अगर (!bo->mm)
		वापस 0;

	mutex_lock(&tegra->mm_lock);
	iommu_unmap(tegra->करोमुख्य, bo->iova, bo->size);
	drm_mm_हटाओ_node(bo->mm);
	mutex_unlock(&tegra->mm_lock);

	kमुक्त(bo->mm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_gem_object_funcs tegra_gem_object_funcs = अणु
	.मुक्त = tegra_bo_मुक्त_object,
	.export = tegra_gem_prime_export,
	.vm_ops = &tegra_bo_vm_ops,
पूर्ण;

अटल काष्ठा tegra_bo *tegra_bo_alloc_object(काष्ठा drm_device *drm,
					      माप_प्रकार size)
अणु
	काष्ठा tegra_bo *bo;
	पूर्णांक err;

	bo = kzalloc(माप(*bo), GFP_KERNEL);
	अगर (!bo)
		वापस ERR_PTR(-ENOMEM);

	bo->gem.funcs = &tegra_gem_object_funcs;

	host1x_bo_init(&bo->base, &tegra_bo_ops);
	size = round_up(size, PAGE_SIZE);

	err = drm_gem_object_init(drm, &bo->gem, size);
	अगर (err < 0)
		जाओ मुक्त;

	err = drm_gem_create_mmap_offset(&bo->gem);
	अगर (err < 0)
		जाओ release;

	वापस bo;

release:
	drm_gem_object_release(&bo->gem);
मुक्त:
	kमुक्त(bo);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tegra_bo_मुक्त(काष्ठा drm_device *drm, काष्ठा tegra_bo *bo)
अणु
	अगर (bo->pages) अणु
		dma_unmap_sgtable(drm->dev, bo->sgt, DMA_FROM_DEVICE, 0);
		drm_gem_put_pages(&bo->gem, bo->pages, true, true);
		sg_मुक्त_table(bo->sgt);
		kमुक्त(bo->sgt);
	पूर्ण अन्यथा अगर (bo->vaddr) अणु
		dma_मुक्त_wc(drm->dev, bo->gem.size, bo->vaddr, bo->iova);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_bo_get_pages(काष्ठा drm_device *drm, काष्ठा tegra_bo *bo)
अणु
	पूर्णांक err;

	bo->pages = drm_gem_get_pages(&bo->gem);
	अगर (IS_ERR(bo->pages))
		वापस PTR_ERR(bo->pages);

	bo->num_pages = bo->gem.size >> PAGE_SHIFT;

	bo->sgt = drm_prime_pages_to_sg(bo->gem.dev, bo->pages, bo->num_pages);
	अगर (IS_ERR(bo->sgt)) अणु
		err = PTR_ERR(bo->sgt);
		जाओ put_pages;
	पूर्ण

	err = dma_map_sgtable(drm->dev, bo->sgt, DMA_FROM_DEVICE, 0);
	अगर (err)
		जाओ मुक्त_sgt;

	वापस 0;

मुक्त_sgt:
	sg_मुक्त_table(bo->sgt);
	kमुक्त(bo->sgt);
put_pages:
	drm_gem_put_pages(&bo->gem, bo->pages, false, false);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_bo_alloc(काष्ठा drm_device *drm, काष्ठा tegra_bo *bo)
अणु
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	पूर्णांक err;

	अगर (tegra->करोमुख्य) अणु
		err = tegra_bo_get_pages(drm, bo);
		अगर (err < 0)
			वापस err;

		err = tegra_bo_iommu_map(tegra, bo);
		अगर (err < 0) अणु
			tegra_bo_मुक्त(drm, bo);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		माप_प्रकार size = bo->gem.size;

		bo->vaddr = dma_alloc_wc(drm->dev, size, &bo->iova,
					 GFP_KERNEL | __GFP_NOWARN);
		अगर (!bo->vaddr) अणु
			dev_err(drm->dev,
				"failed to allocate buffer of size %zu\n",
				size);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा tegra_bo *tegra_bo_create(काष्ठा drm_device *drm, माप_प्रकार size,
				 अचिन्हित दीर्घ flags)
अणु
	काष्ठा tegra_bo *bo;
	पूर्णांक err;

	bo = tegra_bo_alloc_object(drm, size);
	अगर (IS_ERR(bo))
		वापस bo;

	err = tegra_bo_alloc(drm, bo);
	अगर (err < 0)
		जाओ release;

	अगर (flags & DRM_TEGRA_GEM_CREATE_TILED)
		bo->tiling.mode = TEGRA_BO_TILING_MODE_TILED;

	अगर (flags & DRM_TEGRA_GEM_CREATE_BOTTOM_UP)
		bo->flags |= TEGRA_BO_BOTTOM_UP;

	वापस bo;

release:
	drm_gem_object_release(&bo->gem);
	kमुक्त(bo);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा tegra_bo *tegra_bo_create_with_handle(काष्ठा drm_file *file,
					     काष्ठा drm_device *drm,
					     माप_प्रकार size,
					     अचिन्हित दीर्घ flags,
					     u32 *handle)
अणु
	काष्ठा tegra_bo *bo;
	पूर्णांक err;

	bo = tegra_bo_create(drm, size, flags);
	अगर (IS_ERR(bo))
		वापस bo;

	err = drm_gem_handle_create(file, &bo->gem, handle);
	अगर (err) अणु
		tegra_bo_मुक्त_object(&bo->gem);
		वापस ERR_PTR(err);
	पूर्ण

	drm_gem_object_put(&bo->gem);

	वापस bo;
पूर्ण

अटल काष्ठा tegra_bo *tegra_bo_import(काष्ठा drm_device *drm,
					काष्ठा dma_buf *buf)
अणु
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	काष्ठा dma_buf_attachment *attach;
	काष्ठा tegra_bo *bo;
	पूर्णांक err;

	bo = tegra_bo_alloc_object(drm, buf->size);
	अगर (IS_ERR(bo))
		वापस bo;

	attach = dma_buf_attach(buf, drm->dev);
	अगर (IS_ERR(attach)) अणु
		err = PTR_ERR(attach);
		जाओ मुक्त;
	पूर्ण

	get_dma_buf(buf);

	bo->sgt = dma_buf_map_attachment(attach, DMA_TO_DEVICE);
	अगर (IS_ERR(bo->sgt)) अणु
		err = PTR_ERR(bo->sgt);
		जाओ detach;
	पूर्ण

	अगर (tegra->करोमुख्य) अणु
		err = tegra_bo_iommu_map(tegra, bo);
		अगर (err < 0)
			जाओ detach;
	पूर्ण

	bo->gem.import_attach = attach;

	वापस bo;

detach:
	अगर (!IS_ERR_OR_शून्य(bo->sgt))
		dma_buf_unmap_attachment(attach, bo->sgt, DMA_TO_DEVICE);

	dma_buf_detach(buf, attach);
	dma_buf_put(buf);
मुक्त:
	drm_gem_object_release(&bo->gem);
	kमुक्त(bo);
	वापस ERR_PTR(err);
पूर्ण

व्योम tegra_bo_मुक्त_object(काष्ठा drm_gem_object *gem)
अणु
	काष्ठा tegra_drm *tegra = gem->dev->dev_निजी;
	काष्ठा tegra_bo *bo = to_tegra_bo(gem);

	अगर (tegra->करोमुख्य)
		tegra_bo_iommu_unmap(tegra, bo);

	अगर (gem->import_attach) अणु
		dma_buf_unmap_attachment(gem->import_attach, bo->sgt,
					 DMA_TO_DEVICE);
		drm_prime_gem_destroy(gem, शून्य);
	पूर्ण अन्यथा अणु
		tegra_bo_मुक्त(gem->dev, bo);
	पूर्ण

	drm_gem_object_release(gem);
	kमुक्त(bo);
पूर्ण

पूर्णांक tegra_bo_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *drm,
			 काष्ठा drm_mode_create_dumb *args)
अणु
	अचिन्हित पूर्णांक min_pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	काष्ठा tegra_bo *bo;

	args->pitch = round_up(min_pitch, tegra->pitch_align);
	args->size = args->pitch * args->height;

	bo = tegra_bo_create_with_handle(file, drm, args->size, 0,
					 &args->handle);
	अगर (IS_ERR(bo))
		वापस PTR_ERR(bo);

	वापस 0;
पूर्ण

अटल vm_fault_t tegra_bo_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा drm_gem_object *gem = vma->vm_निजी_data;
	काष्ठा tegra_bo *bo = to_tegra_bo(gem);
	काष्ठा page *page;
	pgoff_t offset;

	अगर (!bo->pages)
		वापस VM_FAULT_SIGBUS;

	offset = (vmf->address - vma->vm_start) >> PAGE_SHIFT;
	page = bo->pages[offset];

	वापस vmf_insert_page(vma, vmf->address, page);
पूर्ण

स्थिर काष्ठा vm_operations_काष्ठा tegra_bo_vm_ops = अणु
	.fault = tegra_bo_fault,
	.खोलो = drm_gem_vm_खोलो,
	.बंद = drm_gem_vm_बंद,
पूर्ण;

पूर्णांक __tegra_gem_mmap(काष्ठा drm_gem_object *gem, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा tegra_bo *bo = to_tegra_bo(gem);

	अगर (!bo->pages) अणु
		अचिन्हित दीर्घ vm_pgoff = vma->vm_pgoff;
		पूर्णांक err;

		/*
		 * Clear the VM_PFNMAP flag that was set by drm_gem_mmap(),
		 * and set the vm_pgoff (used as a fake buffer offset by DRM)
		 * to 0 as we want to map the whole buffer.
		 */
		vma->vm_flags &= ~VM_PFNMAP;
		vma->vm_pgoff = 0;

		err = dma_mmap_wc(gem->dev->dev, vma, bo->vaddr, bo->iova,
				  gem->size);
		अगर (err < 0) अणु
			drm_gem_vm_बंद(vma);
			वापस err;
		पूर्ण

		vma->vm_pgoff = vm_pgoff;
	पूर्ण अन्यथा अणु
		pgprot_t prot = vm_get_page_prot(vma->vm_flags);

		vma->vm_flags |= VM_MIXEDMAP;
		vma->vm_flags &= ~VM_PFNMAP;

		vma->vm_page_prot = pgprot_ग_लिखोcombine(prot);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tegra_drm_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_gem_object *gem;
	पूर्णांक err;

	err = drm_gem_mmap(file, vma);
	अगर (err < 0)
		वापस err;

	gem = vma->vm_निजी_data;

	वापस __tegra_gem_mmap(gem, vma);
पूर्ण

अटल काष्ठा sg_table *
tegra_gem_prime_map_dma_buf(काष्ठा dma_buf_attachment *attach,
			    क्रमागत dma_data_direction dir)
अणु
	काष्ठा drm_gem_object *gem = attach->dmabuf->priv;
	काष्ठा tegra_bo *bo = to_tegra_bo(gem);
	काष्ठा sg_table *sgt;

	sgt = kदो_स्मृति(माप(*sgt), GFP_KERNEL);
	अगर (!sgt)
		वापस शून्य;

	अगर (bo->pages) अणु
		अगर (sg_alloc_table_from_pages(sgt, bo->pages, bo->num_pages,
					      0, gem->size, GFP_KERNEL) < 0)
			जाओ मुक्त;
	पूर्ण अन्यथा अणु
		अगर (dma_get_sgtable(attach->dev, sgt, bo->vaddr, bo->iova,
				    gem->size) < 0)
			जाओ मुक्त;
	पूर्ण

	अगर (dma_map_sgtable(attach->dev, sgt, dir, 0))
		जाओ मुक्त;

	वापस sgt;

मुक्त:
	sg_मुक्त_table(sgt);
	kमुक्त(sgt);
	वापस शून्य;
पूर्ण

अटल व्योम tegra_gem_prime_unmap_dma_buf(काष्ठा dma_buf_attachment *attach,
					  काष्ठा sg_table *sgt,
					  क्रमागत dma_data_direction dir)
अणु
	काष्ठा drm_gem_object *gem = attach->dmabuf->priv;
	काष्ठा tegra_bo *bo = to_tegra_bo(gem);

	अगर (bo->pages)
		dma_unmap_sgtable(attach->dev, sgt, dir, 0);

	sg_मुक्त_table(sgt);
	kमुक्त(sgt);
पूर्ण

अटल व्योम tegra_gem_prime_release(काष्ठा dma_buf *buf)
अणु
	drm_gem_dmabuf_release(buf);
पूर्ण

अटल पूर्णांक tegra_gem_prime_begin_cpu_access(काष्ठा dma_buf *buf,
					    क्रमागत dma_data_direction direction)
अणु
	काष्ठा drm_gem_object *gem = buf->priv;
	काष्ठा tegra_bo *bo = to_tegra_bo(gem);
	काष्ठा drm_device *drm = gem->dev;

	अगर (bo->pages)
		dma_sync_sgtable_क्रम_cpu(drm->dev, bo->sgt, DMA_FROM_DEVICE);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_gem_prime_end_cpu_access(काष्ठा dma_buf *buf,
					  क्रमागत dma_data_direction direction)
अणु
	काष्ठा drm_gem_object *gem = buf->priv;
	काष्ठा tegra_bo *bo = to_tegra_bo(gem);
	काष्ठा drm_device *drm = gem->dev;

	अगर (bo->pages)
		dma_sync_sgtable_क्रम_device(drm->dev, bo->sgt, DMA_TO_DEVICE);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_gem_prime_mmap(काष्ठा dma_buf *buf, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_gem_object *gem = buf->priv;
	पूर्णांक err;

	err = drm_gem_mmap_obj(gem, gem->size, vma);
	अगर (err < 0)
		वापस err;

	वापस __tegra_gem_mmap(gem, vma);
पूर्ण

अटल पूर्णांक tegra_gem_prime_vmap(काष्ठा dma_buf *buf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_gem_object *gem = buf->priv;
	काष्ठा tegra_bo *bo = to_tegra_bo(gem);

	dma_buf_map_set_vaddr(map, bo->vaddr);

	वापस 0;
पूर्ण

अटल व्योम tegra_gem_prime_vunmap(काष्ठा dma_buf *buf, काष्ठा dma_buf_map *map)
अणु
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops tegra_gem_prime_dmabuf_ops = अणु
	.map_dma_buf = tegra_gem_prime_map_dma_buf,
	.unmap_dma_buf = tegra_gem_prime_unmap_dma_buf,
	.release = tegra_gem_prime_release,
	.begin_cpu_access = tegra_gem_prime_begin_cpu_access,
	.end_cpu_access = tegra_gem_prime_end_cpu_access,
	.mmap = tegra_gem_prime_mmap,
	.vmap = tegra_gem_prime_vmap,
	.vunmap = tegra_gem_prime_vunmap,
पूर्ण;

काष्ठा dma_buf *tegra_gem_prime_export(काष्ठा drm_gem_object *gem,
				       पूर्णांक flags)
अणु
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	exp_info.exp_name = KBUILD_MODNAME;
	exp_info.owner = gem->dev->driver->fops->owner;
	exp_info.ops = &tegra_gem_prime_dmabuf_ops;
	exp_info.size = gem->size;
	exp_info.flags = flags;
	exp_info.priv = gem;

	वापस drm_gem_dmabuf_export(gem->dev, &exp_info);
पूर्ण

काष्ठा drm_gem_object *tegra_gem_prime_import(काष्ठा drm_device *drm,
					      काष्ठा dma_buf *buf)
अणु
	काष्ठा tegra_bo *bo;

	अगर (buf->ops == &tegra_gem_prime_dmabuf_ops) अणु
		काष्ठा drm_gem_object *gem = buf->priv;

		अगर (gem->dev == drm) अणु
			drm_gem_object_get(gem);
			वापस gem;
		पूर्ण
	पूर्ण

	bo = tegra_bo_import(drm, buf);
	अगर (IS_ERR(bo))
		वापस ERR_CAST(bo);

	वापस &bo->gem;
पूर्ण
