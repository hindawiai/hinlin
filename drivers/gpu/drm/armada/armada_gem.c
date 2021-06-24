<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Russell King
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mman.h>
#समावेश <linux/shmem_fs.h>

#समावेश <drm/armada_drm.h>
#समावेश <drm/drm_prime.h>

#समावेश "armada_drm.h"
#समावेश "armada_gem.h"
#समावेश "armada_ioctlP.h"

अटल vm_fault_t armada_gem_vm_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा drm_gem_object *gobj = vmf->vma->vm_निजी_data;
	काष्ठा armada_gem_object *obj = drm_to_armada_gem(gobj);
	अचिन्हित दीर्घ pfn = obj->phys_addr >> PAGE_SHIFT;

	pfn += (vmf->address - vmf->vma->vm_start) >> PAGE_SHIFT;
	वापस vmf_insert_pfn(vmf->vma, vmf->address, pfn);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा armada_gem_vm_ops = अणु
	.fault	= armada_gem_vm_fault,
	.खोलो	= drm_gem_vm_खोलो,
	.बंद	= drm_gem_vm_बंद,
पूर्ण;

अटल माप_प्रकार roundup_gem_size(माप_प्रकार size)
अणु
	वापस roundup(size, PAGE_SIZE);
पूर्ण

व्योम armada_gem_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा armada_gem_object *करोbj = drm_to_armada_gem(obj);
	काष्ठा armada_निजी *priv = drm_to_armada_dev(obj->dev);

	DRM_DEBUG_DRIVER("release obj %p\n", करोbj);

	drm_gem_मुक्त_mmap_offset(&करोbj->obj);

	might_lock(&priv->linear_lock);

	अगर (करोbj->page) अणु
		/* page backed memory */
		अचिन्हित पूर्णांक order = get_order(करोbj->obj.size);
		__मुक्त_pages(करोbj->page, order);
	पूर्ण अन्यथा अगर (करोbj->linear) अणु
		/* linear backed memory */
		mutex_lock(&priv->linear_lock);
		drm_mm_हटाओ_node(करोbj->linear);
		mutex_unlock(&priv->linear_lock);
		kमुक्त(करोbj->linear);
		अगर (करोbj->addr)
			iounmap(करोbj->addr);
	पूर्ण

	अगर (करोbj->obj.import_attach) अणु
		/* We only ever display imported data */
		अगर (करोbj->sgt)
			dma_buf_unmap_attachment(करोbj->obj.import_attach,
						 करोbj->sgt, DMA_TO_DEVICE);
		drm_prime_gem_destroy(&करोbj->obj, शून्य);
	पूर्ण

	drm_gem_object_release(&करोbj->obj);

	kमुक्त(करोbj);
पूर्ण

पूर्णांक
armada_gem_linear_back(काष्ठा drm_device *dev, काष्ठा armada_gem_object *obj)
अणु
	काष्ठा armada_निजी *priv = drm_to_armada_dev(dev);
	माप_प्रकार size = obj->obj.size;

	अगर (obj->page || obj->linear)
		वापस 0;

	/*
	 * If it is a small allocation (typically cursor, which will
	 * be 32x64 or 64x32 ARGB pixels) try to get it from the प्रणाली.
	 * Framebuffers will never be this small (our minimum size क्रम
	 * framebuffers is larger than this anyway.)  Such objects are
	 * only accessed by the CPU so we करोn't need any special handing
	 * here.
	 */
	अगर (size <= 8192) अणु
		अचिन्हित पूर्णांक order = get_order(size);
		काष्ठा page *p = alloc_pages(GFP_KERNEL, order);

		अगर (p) अणु
			obj->addr = page_address(p);
			obj->phys_addr = page_to_phys(p);
			obj->page = p;

			स_रखो(obj->addr, 0, PAGE_ALIGN(size));
		पूर्ण
	पूर्ण

	/*
	 * We could grab something from CMA अगर it's enabled, but that
	 * involves building in a problem:
	 *
	 * CMA's पूर्णांकerface uses dma_alloc_coherent(), which provides us
	 * with an CPU भव address and a device address.
	 *
	 * The CPU भव address may be either an address in the kernel
	 * direct mapped region (क्रम example, as it would be on x86) or
	 * it may be remapped पूर्णांकo another part of kernel memory space
	 * (eg, as it would be on ARM.)  This means virt_to_phys() on the
	 * वापसed भव address is invalid depending on the architecture
	 * implementation.
	 *
	 * The device address may also not be a physical address; it may
	 * be that there is some kind of remapping between the device and
	 * प्रणाली RAM, which makes the use of the device address also
	 * unsafe to re-use as a physical address.
	 *
	 * This makes DRM usage of dma_alloc_coherent() in a generic way
	 * at best very questionable and unsafe.
	 */

	/* Otherwise, grab it from our linear allocation */
	अगर (!obj->page) अणु
		काष्ठा drm_mm_node *node;
		अचिन्हित align = min_t(अचिन्हित, size, SZ_2M);
		व्योम __iomem *ptr;
		पूर्णांक ret;

		node = kzalloc(माप(*node), GFP_KERNEL);
		अगर (!node)
			वापस -ENOSPC;

		mutex_lock(&priv->linear_lock);
		ret = drm_mm_insert_node_generic(&priv->linear, node,
						 size, align, 0, 0);
		mutex_unlock(&priv->linear_lock);
		अगर (ret) अणु
			kमुक्त(node);
			वापस ret;
		पूर्ण

		obj->linear = node;

		/* Ensure that the memory we're वापसing is cleared. */
		ptr = ioremap_wc(obj->linear->start, size);
		अगर (!ptr) अणु
			mutex_lock(&priv->linear_lock);
			drm_mm_हटाओ_node(obj->linear);
			mutex_unlock(&priv->linear_lock);
			kमुक्त(obj->linear);
			obj->linear = शून्य;
			वापस -ENOMEM;
		पूर्ण

		स_रखो_io(ptr, 0, size);
		iounmap(ptr);

		obj->phys_addr = obj->linear->start;
		obj->dev_addr = obj->linear->start;
		obj->mapped = true;
	पूर्ण

	DRM_DEBUG_DRIVER("obj %p phys %#llx dev %#llx\n", obj,
			 (अचिन्हित दीर्घ दीर्घ)obj->phys_addr,
			 (अचिन्हित दीर्घ दीर्घ)obj->dev_addr);

	वापस 0;
पूर्ण

व्योम *
armada_gem_map_object(काष्ठा drm_device *dev, काष्ठा armada_gem_object *करोbj)
अणु
	/* only linear objects need to be ioremap'd */
	अगर (!करोbj->addr && करोbj->linear)
		करोbj->addr = ioremap_wc(करोbj->phys_addr, करोbj->obj.size);
	वापस करोbj->addr;
पूर्ण

अटल स्थिर काष्ठा drm_gem_object_funcs armada_gem_object_funcs = अणु
	.मुक्त = armada_gem_मुक्त_object,
	.export = armada_gem_prime_export,
	.vm_ops = &armada_gem_vm_ops,
पूर्ण;

काष्ठा armada_gem_object *
armada_gem_alloc_निजी_object(काष्ठा drm_device *dev, माप_प्रकार size)
अणु
	काष्ठा armada_gem_object *obj;

	size = roundup_gem_size(size);

	obj = kzalloc(माप(*obj), GFP_KERNEL);
	अगर (!obj)
		वापस शून्य;

	obj->obj.funcs = &armada_gem_object_funcs;

	drm_gem_निजी_object_init(dev, &obj->obj, size);

	DRM_DEBUG_DRIVER("alloc private obj %p size %zu\n", obj, size);

	वापस obj;
पूर्ण

अटल काष्ठा armada_gem_object *armada_gem_alloc_object(काष्ठा drm_device *dev,
	माप_प्रकार size)
अणु
	काष्ठा armada_gem_object *obj;
	काष्ठा address_space *mapping;

	size = roundup_gem_size(size);

	obj = kzalloc(माप(*obj), GFP_KERNEL);
	अगर (!obj)
		वापस शून्य;

	obj->obj.funcs = &armada_gem_object_funcs;

	अगर (drm_gem_object_init(dev, &obj->obj, size)) अणु
		kमुक्त(obj);
		वापस शून्य;
	पूर्ण

	mapping = obj->obj.filp->f_mapping;
	mapping_set_gfp_mask(mapping, GFP_HIGHUSER | __GFP_RECLAIMABLE);

	DRM_DEBUG_DRIVER("alloc obj %p size %zu\n", obj, size);

	वापस obj;
पूर्ण

/* Dumb alloc support */
पूर्णांक armada_gem_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
	काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा armada_gem_object *करोbj;
	u32 handle;
	माप_प्रकार size;
	पूर्णांक ret;

	args->pitch = armada_pitch(args->width, args->bpp);
	args->size = size = args->pitch * args->height;

	करोbj = armada_gem_alloc_निजी_object(dev, size);
	अगर (करोbj == शून्य)
		वापस -ENOMEM;

	ret = armada_gem_linear_back(dev, करोbj);
	अगर (ret)
		जाओ err;

	ret = drm_gem_handle_create(file, &करोbj->obj, &handle);
	अगर (ret)
		जाओ err;

	args->handle = handle;

	/* drop reference from allocate - handle holds it now */
	DRM_DEBUG_DRIVER("obj %p size %zu handle %#x\n", करोbj, size, handle);
 err:
	drm_gem_object_put(&करोbj->obj);
	वापस ret;
पूर्ण

/* Private driver gem ioctls */
पूर्णांक armada_gem_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
	काष्ठा drm_file *file)
अणु
	काष्ठा drm_armada_gem_create *args = data;
	काष्ठा armada_gem_object *करोbj;
	माप_प्रकार size;
	u32 handle;
	पूर्णांक ret;

	अगर (args->size == 0)
		वापस -ENOMEM;

	size = args->size;

	करोbj = armada_gem_alloc_object(dev, size);
	अगर (करोbj == शून्य)
		वापस -ENOMEM;

	ret = drm_gem_handle_create(file, &करोbj->obj, &handle);
	अगर (ret)
		जाओ err;

	args->handle = handle;

	/* drop reference from allocate - handle holds it now */
	DRM_DEBUG_DRIVER("obj %p size %zu handle %#x\n", करोbj, size, handle);
 err:
	drm_gem_object_put(&करोbj->obj);
	वापस ret;
पूर्ण

/* Map a shmem-backed object पूर्णांकo process memory space */
पूर्णांक armada_gem_mmap_ioctl(काष्ठा drm_device *dev, व्योम *data,
	काष्ठा drm_file *file)
अणु
	काष्ठा drm_armada_gem_mmap *args = data;
	काष्ठा armada_gem_object *करोbj;
	अचिन्हित दीर्घ addr;

	करोbj = armada_gem_object_lookup(file, args->handle);
	अगर (करोbj == शून्य)
		वापस -ENOENT;

	अगर (!करोbj->obj.filp) अणु
		drm_gem_object_put(&करोbj->obj);
		वापस -EINVAL;
	पूर्ण

	addr = vm_mmap(करोbj->obj.filp, 0, args->size, PROT_READ | PROT_WRITE,
		       MAP_SHARED, args->offset);
	drm_gem_object_put(&करोbj->obj);
	अगर (IS_ERR_VALUE(addr))
		वापस addr;

	args->addr = addr;

	वापस 0;
पूर्ण

पूर्णांक armada_gem_pग_लिखो_ioctl(काष्ठा drm_device *dev, व्योम *data,
	काष्ठा drm_file *file)
अणु
	काष्ठा drm_armada_gem_pग_लिखो *args = data;
	काष्ठा armada_gem_object *करोbj;
	अक्षर __user *ptr;
	पूर्णांक ret;

	DRM_DEBUG_DRIVER("handle %u off %u size %u ptr 0x%llx\n",
		args->handle, args->offset, args->size, args->ptr);

	अगर (args->size == 0)
		वापस 0;

	ptr = (अक्षर __user *)(uपूर्णांकptr_t)args->ptr;

	अगर (!access_ok(ptr, args->size))
		वापस -EFAULT;

	ret = fault_in_pages_पढ़ोable(ptr, args->size);
	अगर (ret)
		वापस ret;

	करोbj = armada_gem_object_lookup(file, args->handle);
	अगर (करोbj == शून्य)
		वापस -ENOENT;

	/* Must be a kernel-mapped object */
	अगर (!करोbj->addr)
		वापस -EINVAL;

	अगर (args->offset > करोbj->obj.size ||
	    args->size > करोbj->obj.size - args->offset) अणु
		DRM_ERROR("invalid size: object size %u\n", करोbj->obj.size);
		ret = -EINVAL;
		जाओ unref;
	पूर्ण

	अगर (copy_from_user(करोbj->addr + args->offset, ptr, args->size)) अणु
		ret = -EFAULT;
	पूर्ण अन्यथा अगर (करोbj->update) अणु
		करोbj->update(करोbj->update_data);
		ret = 0;
	पूर्ण

 unref:
	drm_gem_object_put(&करोbj->obj);
	वापस ret;
पूर्ण

/* Prime support */
अटल काष्ठा sg_table *
armada_gem_prime_map_dma_buf(काष्ठा dma_buf_attachment *attach,
	क्रमागत dma_data_direction dir)
अणु
	काष्ठा drm_gem_object *obj = attach->dmabuf->priv;
	काष्ठा armada_gem_object *करोbj = drm_to_armada_gem(obj);
	काष्ठा scatterlist *sg;
	काष्ठा sg_table *sgt;
	पूर्णांक i;

	sgt = kदो_स्मृति(माप(*sgt), GFP_KERNEL);
	अगर (!sgt)
		वापस शून्य;

	अगर (करोbj->obj.filp) अणु
		काष्ठा address_space *mapping;
		पूर्णांक count;

		count = करोbj->obj.size / PAGE_SIZE;
		अगर (sg_alloc_table(sgt, count, GFP_KERNEL))
			जाओ मुक्त_sgt;

		mapping = करोbj->obj.filp->f_mapping;

		क्रम_each_sgtable_sg(sgt, sg, i) अणु
			काष्ठा page *page;

			page = shmem_पढ़ो_mapping_page(mapping, i);
			अगर (IS_ERR(page))
				जाओ release;

			sg_set_page(sg, page, PAGE_SIZE, 0);
		पूर्ण

		अगर (dma_map_sgtable(attach->dev, sgt, dir, 0))
			जाओ release;
	पूर्ण अन्यथा अगर (करोbj->page) अणु
		/* Single contiguous page */
		अगर (sg_alloc_table(sgt, 1, GFP_KERNEL))
			जाओ मुक्त_sgt;

		sg_set_page(sgt->sgl, करोbj->page, करोbj->obj.size, 0);

		अगर (dma_map_sgtable(attach->dev, sgt, dir, 0))
			जाओ मुक्त_table;
	पूर्ण अन्यथा अगर (करोbj->linear) अणु
		/* Single contiguous physical region - no काष्ठा page */
		अगर (sg_alloc_table(sgt, 1, GFP_KERNEL))
			जाओ मुक्त_sgt;
		sg_dma_address(sgt->sgl) = करोbj->dev_addr;
		sg_dma_len(sgt->sgl) = करोbj->obj.size;
	पूर्ण अन्यथा अणु
		जाओ मुक्त_sgt;
	पूर्ण
	वापस sgt;

 release:
	क्रम_each_sgtable_sg(sgt, sg, i)
		अगर (sg_page(sg))
			put_page(sg_page(sg));
 मुक्त_table:
	sg_मुक्त_table(sgt);
 मुक्त_sgt:
	kमुक्त(sgt);
	वापस शून्य;
पूर्ण

अटल व्योम armada_gem_prime_unmap_dma_buf(काष्ठा dma_buf_attachment *attach,
	काष्ठा sg_table *sgt, क्रमागत dma_data_direction dir)
अणु
	काष्ठा drm_gem_object *obj = attach->dmabuf->priv;
	काष्ठा armada_gem_object *करोbj = drm_to_armada_gem(obj);
	पूर्णांक i;

	अगर (!करोbj->linear)
		dma_unmap_sgtable(attach->dev, sgt, dir, 0);

	अगर (करोbj->obj.filp) अणु
		काष्ठा scatterlist *sg;

		क्रम_each_sgtable_sg(sgt, sg, i)
			put_page(sg_page(sg));
	पूर्ण

	sg_मुक्त_table(sgt);
	kमुक्त(sgt);
पूर्ण

अटल पूर्णांक
armada_gem_dmabuf_mmap(काष्ठा dma_buf *buf, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops armada_gem_prime_dmabuf_ops = अणु
	.map_dma_buf	= armada_gem_prime_map_dma_buf,
	.unmap_dma_buf	= armada_gem_prime_unmap_dma_buf,
	.release	= drm_gem_dmabuf_release,
	.mmap		= armada_gem_dmabuf_mmap,
पूर्ण;

काष्ठा dma_buf *
armada_gem_prime_export(काष्ठा drm_gem_object *obj, पूर्णांक flags)
अणु
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	exp_info.ops = &armada_gem_prime_dmabuf_ops;
	exp_info.size = obj->size;
	exp_info.flags = O_RDWR;
	exp_info.priv = obj;

	वापस drm_gem_dmabuf_export(obj->dev, &exp_info);
पूर्ण

काष्ठा drm_gem_object *
armada_gem_prime_import(काष्ठा drm_device *dev, काष्ठा dma_buf *buf)
अणु
	काष्ठा dma_buf_attachment *attach;
	काष्ठा armada_gem_object *करोbj;

	अगर (buf->ops == &armada_gem_prime_dmabuf_ops) अणु
		काष्ठा drm_gem_object *obj = buf->priv;
		अगर (obj->dev == dev) अणु
			/*
			 * Importing our own dmabuf(s) increases the
			 * refcount on the gem object itself.
			 */
			drm_gem_object_get(obj);
			वापस obj;
		पूर्ण
	पूर्ण

	attach = dma_buf_attach(buf, dev->dev);
	अगर (IS_ERR(attach))
		वापस ERR_CAST(attach);

	करोbj = armada_gem_alloc_निजी_object(dev, buf->size);
	अगर (!करोbj) अणु
		dma_buf_detach(buf, attach);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	करोbj->obj.import_attach = attach;
	get_dma_buf(buf);

	/*
	 * Don't call dma_buf_map_attachment() here - it maps the
	 * scatterlist immediately क्रम DMA, and this is not always
	 * an appropriate thing to करो.
	 */
	वापस &करोbj->obj;
पूर्ण

पूर्णांक armada_gem_map_import(काष्ठा armada_gem_object *करोbj)
अणु
	पूर्णांक ret;

	करोbj->sgt = dma_buf_map_attachment(करोbj->obj.import_attach,
					   DMA_TO_DEVICE);
	अगर (IS_ERR(करोbj->sgt)) अणु
		ret = PTR_ERR(करोbj->sgt);
		करोbj->sgt = शून्य;
		DRM_ERROR("dma_buf_map_attachment() error: %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (करोbj->sgt->nents > 1) अणु
		DRM_ERROR("dma_buf_map_attachment() returned an (unsupported) scattered list\n");
		वापस -EINVAL;
	पूर्ण
	अगर (sg_dma_len(करोbj->sgt->sgl) < करोbj->obj.size) अणु
		DRM_ERROR("dma_buf_map_attachment() returned a small buffer\n");
		वापस -EINVAL;
	पूर्ण
	करोbj->dev_addr = sg_dma_address(करोbj->sgt->sgl);
	करोbj->mapped = true;
	वापस 0;
पूर्ण
