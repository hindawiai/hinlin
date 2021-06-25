<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* exynos_drm_gem.c
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Author: Inki Dae <inki.dae@samsung.com>
 */


#समावेश <linux/dma-buf.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/shmem_fs.h>

#समावेश <drm/drm_prime.h>
#समावेश <drm/drm_vma_manager.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_gem.h"

अटल पूर्णांक exynos_drm_alloc_buf(काष्ठा exynos_drm_gem *exynos_gem, bool kvmap)
अणु
	काष्ठा drm_device *dev = exynos_gem->base.dev;
	अचिन्हित दीर्घ attr = 0;

	अगर (exynos_gem->dma_addr) अणु
		DRM_DEV_DEBUG_KMS(to_dma_dev(dev), "already allocated.\n");
		वापस 0;
	पूर्ण

	/*
	 * अगर EXYNOS_BO_CONTIG, fully physically contiguous memory
	 * region will be allocated अन्यथा physically contiguous
	 * as possible.
	 */
	अगर (!(exynos_gem->flags & EXYNOS_BO_NONCONTIG))
		attr |= DMA_ATTR_FORCE_CONTIGUOUS;

	/*
	 * अगर EXYNOS_BO_WC or EXYNOS_BO_NONCACHABLE, ग_लिखोcombine mapping
	 * अन्यथा cachable mapping.
	 */
	अगर (exynos_gem->flags & EXYNOS_BO_WC ||
			!(exynos_gem->flags & EXYNOS_BO_CACHABLE))
		attr |= DMA_ATTR_WRITE_COMBINE;

	/* FBDev emulation requires kernel mapping */
	अगर (!kvmap)
		attr |= DMA_ATTR_NO_KERNEL_MAPPING;

	exynos_gem->dma_attrs = attr;
	exynos_gem->cookie = dma_alloc_attrs(to_dma_dev(dev), exynos_gem->size,
					     &exynos_gem->dma_addr, GFP_KERNEL,
					     exynos_gem->dma_attrs);
	अगर (!exynos_gem->cookie) अणु
		DRM_DEV_ERROR(to_dma_dev(dev), "failed to allocate buffer.\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (kvmap)
		exynos_gem->kvaddr = exynos_gem->cookie;

	DRM_DEV_DEBUG_KMS(to_dma_dev(dev), "dma_addr(0x%lx), size(0x%lx)\n",
			(अचिन्हित दीर्घ)exynos_gem->dma_addr, exynos_gem->size);
	वापस 0;
पूर्ण

अटल व्योम exynos_drm_मुक्त_buf(काष्ठा exynos_drm_gem *exynos_gem)
अणु
	काष्ठा drm_device *dev = exynos_gem->base.dev;

	अगर (!exynos_gem->dma_addr) अणु
		DRM_DEV_DEBUG_KMS(dev->dev, "dma_addr is invalid.\n");
		वापस;
	पूर्ण

	DRM_DEV_DEBUG_KMS(dev->dev, "dma_addr(0x%lx), size(0x%lx)\n",
			(अचिन्हित दीर्घ)exynos_gem->dma_addr, exynos_gem->size);

	dma_मुक्त_attrs(to_dma_dev(dev), exynos_gem->size, exynos_gem->cookie,
			(dma_addr_t)exynos_gem->dma_addr,
			exynos_gem->dma_attrs);
पूर्ण

अटल पूर्णांक exynos_drm_gem_handle_create(काष्ठा drm_gem_object *obj,
					काष्ठा drm_file *file_priv,
					अचिन्हित पूर्णांक *handle)
अणु
	पूर्णांक ret;

	/*
	 * allocate a id of idr table where the obj is रेजिस्टरed
	 * and handle has the id what user can see.
	 */
	ret = drm_gem_handle_create(file_priv, obj, handle);
	अगर (ret)
		वापस ret;

	DRM_DEV_DEBUG_KMS(to_dma_dev(obj->dev), "gem handle = 0x%x\n", *handle);

	/* drop reference from allocate - handle holds it now. */
	drm_gem_object_put(obj);

	वापस 0;
पूर्ण

व्योम exynos_drm_gem_destroy(काष्ठा exynos_drm_gem *exynos_gem)
अणु
	काष्ठा drm_gem_object *obj = &exynos_gem->base;

	DRM_DEV_DEBUG_KMS(to_dma_dev(obj->dev), "handle count = %d\n",
			  obj->handle_count);

	/*
	 * करो not release memory region from exporter.
	 *
	 * the region will be released by exporter
	 * once dmabuf's refcount becomes 0.
	 */
	अगर (obj->import_attach)
		drm_prime_gem_destroy(obj, exynos_gem->sgt);
	अन्यथा
		exynos_drm_मुक्त_buf(exynos_gem);

	/* release file poपूर्णांकer to gem object. */
	drm_gem_object_release(obj);

	kमुक्त(exynos_gem);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा exynos_drm_gem_vm_ops = अणु
	.खोलो = drm_gem_vm_खोलो,
	.बंद = drm_gem_vm_बंद,
पूर्ण;

अटल स्थिर काष्ठा drm_gem_object_funcs exynos_drm_gem_object_funcs = अणु
	.मुक्त = exynos_drm_gem_मुक्त_object,
	.get_sg_table = exynos_drm_gem_prime_get_sg_table,
	.vm_ops = &exynos_drm_gem_vm_ops,
पूर्ण;

अटल काष्ठा exynos_drm_gem *exynos_drm_gem_init(काष्ठा drm_device *dev,
						  अचिन्हित दीर्घ size)
अणु
	काष्ठा exynos_drm_gem *exynos_gem;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	exynos_gem = kzalloc(माप(*exynos_gem), GFP_KERNEL);
	अगर (!exynos_gem)
		वापस ERR_PTR(-ENOMEM);

	exynos_gem->size = size;
	obj = &exynos_gem->base;

	obj->funcs = &exynos_drm_gem_object_funcs;

	ret = drm_gem_object_init(dev, obj, size);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev->dev, "failed to initialize gem object\n");
		kमुक्त(exynos_gem);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = drm_gem_create_mmap_offset(obj);
	अगर (ret < 0) अणु
		drm_gem_object_release(obj);
		kमुक्त(exynos_gem);
		वापस ERR_PTR(ret);
	पूर्ण

	DRM_DEV_DEBUG_KMS(dev->dev, "created file object = %pK\n", obj->filp);

	वापस exynos_gem;
पूर्ण

काष्ठा exynos_drm_gem *exynos_drm_gem_create(काष्ठा drm_device *dev,
					     अचिन्हित पूर्णांक flags,
					     अचिन्हित दीर्घ size,
					     bool kvmap)
अणु
	काष्ठा exynos_drm_gem *exynos_gem;
	पूर्णांक ret;

	अगर (flags & ~(EXYNOS_BO_MASK)) अणु
		DRM_DEV_ERROR(dev->dev,
			      "invalid GEM buffer flags: %u\n", flags);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!size) अणु
		DRM_DEV_ERROR(dev->dev, "invalid GEM buffer size: %lu\n", size);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	size = roundup(size, PAGE_SIZE);

	exynos_gem = exynos_drm_gem_init(dev, size);
	अगर (IS_ERR(exynos_gem))
		वापस exynos_gem;

	अगर (!is_drm_iommu_supported(dev) && (flags & EXYNOS_BO_NONCONTIG)) अणु
		/*
		 * when no IOMMU is available, all allocated buffers are
		 * contiguous anyway, so drop EXYNOS_BO_NONCONTIG flag
		 */
		flags &= ~EXYNOS_BO_NONCONTIG;
		DRM_WARN("Non-contiguous allocation is not supported without IOMMU, falling back to contiguous buffer\n");
	पूर्ण

	/* set memory type and cache attribute from user side. */
	exynos_gem->flags = flags;

	ret = exynos_drm_alloc_buf(exynos_gem, kvmap);
	अगर (ret < 0) अणु
		drm_gem_object_release(&exynos_gem->base);
		kमुक्त(exynos_gem);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस exynos_gem;
पूर्ण

पूर्णांक exynos_drm_gem_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_exynos_gem_create *args = data;
	काष्ठा exynos_drm_gem *exynos_gem;
	पूर्णांक ret;

	exynos_gem = exynos_drm_gem_create(dev, args->flags, args->size, false);
	अगर (IS_ERR(exynos_gem))
		वापस PTR_ERR(exynos_gem);

	ret = exynos_drm_gem_handle_create(&exynos_gem->base, file_priv,
					   &args->handle);
	अगर (ret) अणु
		exynos_drm_gem_destroy(exynos_gem);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक exynos_drm_gem_map_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_exynos_gem_map *args = data;

	वापस drm_gem_dumb_map_offset(file_priv, dev, args->handle,
				       &args->offset);
पूर्ण

काष्ठा exynos_drm_gem *exynos_drm_gem_get(काष्ठा drm_file *filp,
					  अचिन्हित पूर्णांक gem_handle)
अणु
	काष्ठा drm_gem_object *obj;

	obj = drm_gem_object_lookup(filp, gem_handle);
	अगर (!obj)
		वापस शून्य;
	वापस to_exynos_gem(obj);
पूर्ण

अटल पूर्णांक exynos_drm_gem_mmap_buffer(काष्ठा exynos_drm_gem *exynos_gem,
				      काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_device *drm_dev = exynos_gem->base.dev;
	अचिन्हित दीर्घ vm_size;
	पूर्णांक ret;

	vma->vm_flags &= ~VM_PFNMAP;
	vma->vm_pgoff = 0;

	vm_size = vma->vm_end - vma->vm_start;

	/* check अगर user-requested size is valid. */
	अगर (vm_size > exynos_gem->size)
		वापस -EINVAL;

	ret = dma_mmap_attrs(to_dma_dev(drm_dev), vma, exynos_gem->cookie,
			     exynos_gem->dma_addr, exynos_gem->size,
			     exynos_gem->dma_attrs);
	अगर (ret < 0) अणु
		DRM_ERROR("failed to mmap.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक exynos_drm_gem_get_ioctl(काष्ठा drm_device *dev, व्योम *data,
				      काष्ठा drm_file *file_priv)
अणु
	काष्ठा exynos_drm_gem *exynos_gem;
	काष्ठा drm_exynos_gem_info *args = data;
	काष्ठा drm_gem_object *obj;

	obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!obj) अणु
		DRM_DEV_ERROR(dev->dev, "failed to lookup gem object.\n");
		वापस -EINVAL;
	पूर्ण

	exynos_gem = to_exynos_gem(obj);

	args->flags = exynos_gem->flags;
	args->size = exynos_gem->size;

	drm_gem_object_put(obj);

	वापस 0;
पूर्ण

व्योम exynos_drm_gem_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	exynos_drm_gem_destroy(to_exynos_gem(obj));
पूर्ण

पूर्णांक exynos_drm_gem_dumb_create(काष्ठा drm_file *file_priv,
			       काष्ठा drm_device *dev,
			       काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा exynos_drm_gem *exynos_gem;
	अचिन्हित पूर्णांक flags;
	पूर्णांक ret;

	/*
	 * allocate memory to be used क्रम framebuffer.
	 * - this callback would be called by user application
	 *	with DRM_IOCTL_MODE_CREATE_DUMB command.
	 */

	args->pitch = args->width * ((args->bpp + 7) / 8);
	args->size = args->pitch * args->height;

	अगर (is_drm_iommu_supported(dev))
		flags = EXYNOS_BO_NONCONTIG | EXYNOS_BO_WC;
	अन्यथा
		flags = EXYNOS_BO_CONTIG | EXYNOS_BO_WC;

	exynos_gem = exynos_drm_gem_create(dev, flags, args->size, false);
	अगर (IS_ERR(exynos_gem)) अणु
		dev_warn(dev->dev, "FB allocation failed.\n");
		वापस PTR_ERR(exynos_gem);
	पूर्ण

	ret = exynos_drm_gem_handle_create(&exynos_gem->base, file_priv,
					   &args->handle);
	अगर (ret) अणु
		exynos_drm_gem_destroy(exynos_gem);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_drm_gem_mmap_obj(काष्ठा drm_gem_object *obj,
				   काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा exynos_drm_gem *exynos_gem = to_exynos_gem(obj);
	पूर्णांक ret;

	DRM_DEV_DEBUG_KMS(to_dma_dev(obj->dev), "flags = 0x%x\n",
			  exynos_gem->flags);

	/* non-cachable as शेष. */
	अगर (exynos_gem->flags & EXYNOS_BO_CACHABLE)
		vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);
	अन्यथा अगर (exynos_gem->flags & EXYNOS_BO_WC)
		vma->vm_page_prot =
			pgprot_ग_लिखोcombine(vm_get_page_prot(vma->vm_flags));
	अन्यथा
		vma->vm_page_prot =
			pgprot_noncached(vm_get_page_prot(vma->vm_flags));

	ret = exynos_drm_gem_mmap_buffer(exynos_gem, vma);
	अगर (ret)
		जाओ err_बंद_vm;

	वापस ret;

err_बंद_vm:
	drm_gem_vm_बंद(vma);

	वापस ret;
पूर्ण

पूर्णांक exynos_drm_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	/* set vm_area_काष्ठा. */
	ret = drm_gem_mmap(filp, vma);
	अगर (ret < 0) अणु
		DRM_ERROR("failed to mmap.\n");
		वापस ret;
	पूर्ण

	obj = vma->vm_निजी_data;

	अगर (obj->import_attach)
		वापस dma_buf_mmap(obj->dma_buf, vma, 0);

	वापस exynos_drm_gem_mmap_obj(obj, vma);
पूर्ण

/* low-level पूर्णांकerface prime helpers */
काष्ठा drm_gem_object *exynos_drm_gem_prime_import(काष्ठा drm_device *dev,
					    काष्ठा dma_buf *dma_buf)
अणु
	वापस drm_gem_prime_import_dev(dev, dma_buf, to_dma_dev(dev));
पूर्ण

काष्ठा sg_table *exynos_drm_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा exynos_drm_gem *exynos_gem = to_exynos_gem(obj);
	काष्ठा drm_device *drm_dev = obj->dev;
	काष्ठा sg_table *sgt;
	पूर्णांक ret;

	sgt = kzalloc(माप(*sgt), GFP_KERNEL);
	अगर (!sgt)
		वापस ERR_PTR(-ENOMEM);

	ret = dma_get_sgtable_attrs(to_dma_dev(drm_dev), sgt, exynos_gem->cookie,
				    exynos_gem->dma_addr, exynos_gem->size,
				    exynos_gem->dma_attrs);
	अगर (ret) अणु
		DRM_ERROR("failed to get sgtable, %d\n", ret);
		kमुक्त(sgt);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस sgt;
पूर्ण

काष्ठा drm_gem_object *
exynos_drm_gem_prime_import_sg_table(काष्ठा drm_device *dev,
				     काष्ठा dma_buf_attachment *attach,
				     काष्ठा sg_table *sgt)
अणु
	काष्ठा exynos_drm_gem *exynos_gem;

	/* check अगर the entries in the sg_table are contiguous */
	अगर (drm_prime_get_contiguous_size(sgt) < attach->dmabuf->size) अणु
		DRM_ERROR("buffer chunks must be mapped contiguously");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	exynos_gem = exynos_drm_gem_init(dev, attach->dmabuf->size);
	अगर (IS_ERR(exynos_gem))
		वापस ERR_CAST(exynos_gem);

	/*
	 * Buffer has been mapped as contiguous पूर्णांकo DMA address space,
	 * but अगर there is IOMMU, it can be either CONTIG or NONCONTIG.
	 * We assume a simplअगरied logic below:
	 */
	अगर (is_drm_iommu_supported(dev))
		exynos_gem->flags |= EXYNOS_BO_NONCONTIG;
	अन्यथा
		exynos_gem->flags |= EXYNOS_BO_CONTIG;

	exynos_gem->dma_addr = sg_dma_address(sgt->sgl);
	exynos_gem->sgt = sgt;
	वापस &exynos_gem->base;
पूर्ण

पूर्णांक exynos_drm_gem_prime_mmap(काष्ठा drm_gem_object *obj,
			      काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;

	ret = drm_gem_mmap_obj(obj, obj->size, vma);
	अगर (ret < 0)
		वापस ret;

	वापस exynos_drm_gem_mmap_obj(obj, vma);
पूर्ण
