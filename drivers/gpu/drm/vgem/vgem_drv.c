<शैली गुरु>
/*
 * Copyright 2011 Red Hat, Inc.
 * Copyright तऊ 2014 The Chromium OS Authors
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software")
 * to deal in the software without restriction, including without limitation
 * on the rights to use, copy, modअगरy, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * them Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTIBILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *	Adam Jackson <ajax@redhat.com>
 *	Ben Widawsky <ben@bwidawsk.net>
 */

/**
 * This is vgem, a (non-hardware-backed) GEM service.  This is used by Mesa's
 * software renderer and the X server क्रम efficient buffer sharing.
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_prime.h>

#समावेश "vgem_drv.h"

#घोषणा DRIVER_NAME	"vgem"
#घोषणा DRIVER_DESC	"Virtual GEM provider"
#घोषणा DRIVER_DATE	"20120112"
#घोषणा DRIVER_MAJOR	1
#घोषणा DRIVER_MINOR	0

अटल स्थिर काष्ठा drm_gem_object_funcs vgem_gem_object_funcs;

अटल काष्ठा vgem_device अणु
	काष्ठा drm_device drm;
	काष्ठा platक्रमm_device *platक्रमm;
पूर्ण *vgem_device;

अटल व्योम vgem_gem_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_vgem_gem_object *vgem_obj = to_vgem_bo(obj);

	kvमुक्त(vgem_obj->pages);
	mutex_destroy(&vgem_obj->pages_lock);

	अगर (obj->import_attach)
		drm_prime_gem_destroy(obj, vgem_obj->table);

	drm_gem_object_release(obj);
	kमुक्त(vgem_obj);
पूर्ण

अटल vm_fault_t vgem_gem_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा drm_vgem_gem_object *obj = vma->vm_निजी_data;
	/* We करोn't use vmf->pgoff since that has the fake offset */
	अचिन्हित दीर्घ vaddr = vmf->address;
	vm_fault_t ret = VM_FAULT_SIGBUS;
	loff_t num_pages;
	pgoff_t page_offset;
	page_offset = (vaddr - vma->vm_start) >> PAGE_SHIFT;

	num_pages = DIV_ROUND_UP(obj->base.size, PAGE_SIZE);

	अगर (page_offset >= num_pages)
		वापस VM_FAULT_SIGBUS;

	mutex_lock(&obj->pages_lock);
	अगर (obj->pages) अणु
		get_page(obj->pages[page_offset]);
		vmf->page = obj->pages[page_offset];
		ret = 0;
	पूर्ण
	mutex_unlock(&obj->pages_lock);
	अगर (ret) अणु
		काष्ठा page *page;

		page = shmem_पढ़ो_mapping_page(
					file_inode(obj->base.filp)->i_mapping,
					page_offset);
		अगर (!IS_ERR(page)) अणु
			vmf->page = page;
			ret = 0;
		पूर्ण अन्यथा चयन (PTR_ERR(page)) अणु
			हाल -ENOSPC:
			हाल -ENOMEM:
				ret = VM_FAULT_OOM;
				अवरोध;
			हाल -EBUSY:
				ret = VM_FAULT_RETRY;
				अवरोध;
			हाल -EFAULT:
			हाल -EINVAL:
				ret = VM_FAULT_SIGBUS;
				अवरोध;
			शेष:
				WARN_ON(PTR_ERR(page));
				ret = VM_FAULT_SIGBUS;
				अवरोध;
		पूर्ण

	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा vgem_gem_vm_ops = अणु
	.fault = vgem_gem_fault,
	.खोलो = drm_gem_vm_खोलो,
	.बंद = drm_gem_vm_बंद,
पूर्ण;

अटल पूर्णांक vgem_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा vgem_file *vfile;
	पूर्णांक ret;

	vfile = kzalloc(माप(*vfile), GFP_KERNEL);
	अगर (!vfile)
		वापस -ENOMEM;

	file->driver_priv = vfile;

	ret = vgem_fence_खोलो(vfile);
	अगर (ret) अणु
		kमुक्त(vfile);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vgem_postबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा vgem_file *vfile = file->driver_priv;

	vgem_fence_बंद(vfile);
	kमुक्त(vfile);
पूर्ण

अटल काष्ठा drm_vgem_gem_object *__vgem_gem_create(काष्ठा drm_device *dev,
						अचिन्हित दीर्घ size)
अणु
	काष्ठा drm_vgem_gem_object *obj;
	पूर्णांक ret;

	obj = kzalloc(माप(*obj), GFP_KERNEL);
	अगर (!obj)
		वापस ERR_PTR(-ENOMEM);

	obj->base.funcs = &vgem_gem_object_funcs;

	ret = drm_gem_object_init(dev, &obj->base, roundup(size, PAGE_SIZE));
	अगर (ret) अणु
		kमुक्त(obj);
		वापस ERR_PTR(ret);
	पूर्ण

	mutex_init(&obj->pages_lock);

	वापस obj;
पूर्ण

अटल व्योम __vgem_gem_destroy(काष्ठा drm_vgem_gem_object *obj)
अणु
	drm_gem_object_release(&obj->base);
	kमुक्त(obj);
पूर्ण

अटल काष्ठा drm_gem_object *vgem_gem_create(काष्ठा drm_device *dev,
					      काष्ठा drm_file *file,
					      अचिन्हित पूर्णांक *handle,
					      अचिन्हित दीर्घ size)
अणु
	काष्ठा drm_vgem_gem_object *obj;
	पूर्णांक ret;

	obj = __vgem_gem_create(dev, size);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	ret = drm_gem_handle_create(file, &obj->base, handle);
	अगर (ret) अणु
		drm_gem_object_put(&obj->base);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &obj->base;
पूर्ण

अटल पूर्णांक vgem_gem_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
				काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा drm_gem_object *gem_object;
	u64 pitch, size;

	pitch = args->width * DIV_ROUND_UP(args->bpp, 8);
	size = args->height * pitch;
	अगर (size == 0)
		वापस -EINVAL;

	gem_object = vgem_gem_create(dev, file, &args->handle, size);
	अगर (IS_ERR(gem_object))
		वापस PTR_ERR(gem_object);

	args->size = gem_object->size;
	args->pitch = pitch;

	drm_gem_object_put(gem_object);

	DRM_DEBUG("Created object of size %llu\n", args->size);

	वापस 0;
पूर्ण

अटल काष्ठा drm_ioctl_desc vgem_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(VGEM_FENCE_ATTACH, vgem_fence_attach_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VGEM_FENCE_SIGNAL, vgem_fence_संकेत_ioctl, DRM_RENDER_ALLOW),
पूर्ण;

अटल पूर्णांक vgem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ flags = vma->vm_flags;
	पूर्णांक ret;

	ret = drm_gem_mmap(filp, vma);
	अगर (ret)
		वापस ret;

	/* Keep the WC mmaping set by drm_gem_mmap() but our pages
	 * are ordinary and not special.
	 */
	vma->vm_flags = flags | VM_DONTEXPAND | VM_DONTDUMP;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations vgem_driver_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= drm_खोलो,
	.mmap		= vgem_mmap,
	.poll		= drm_poll,
	.पढ़ो		= drm_पढ़ो,
	.unlocked_ioctl = drm_ioctl,
	.compat_ioctl	= drm_compat_ioctl,
	.release	= drm_release,
पूर्ण;

अटल काष्ठा page **vgem_pin_pages(काष्ठा drm_vgem_gem_object *bo)
अणु
	mutex_lock(&bo->pages_lock);
	अगर (bo->pages_pin_count++ == 0) अणु
		काष्ठा page **pages;

		pages = drm_gem_get_pages(&bo->base);
		अगर (IS_ERR(pages)) अणु
			bo->pages_pin_count--;
			mutex_unlock(&bo->pages_lock);
			वापस pages;
		पूर्ण

		bo->pages = pages;
	पूर्ण
	mutex_unlock(&bo->pages_lock);

	वापस bo->pages;
पूर्ण

अटल व्योम vgem_unpin_pages(काष्ठा drm_vgem_gem_object *bo)
अणु
	mutex_lock(&bo->pages_lock);
	अगर (--bo->pages_pin_count == 0) अणु
		drm_gem_put_pages(&bo->base, bo->pages, true, true);
		bo->pages = शून्य;
	पूर्ण
	mutex_unlock(&bo->pages_lock);
पूर्ण

अटल पूर्णांक vgem_prime_pin(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_vgem_gem_object *bo = to_vgem_bo(obj);
	दीर्घ n_pages = obj->size >> PAGE_SHIFT;
	काष्ठा page **pages;

	pages = vgem_pin_pages(bo);
	अगर (IS_ERR(pages))
		वापस PTR_ERR(pages);

	/* Flush the object from the CPU cache so that importers can rely
	 * on coherent indirect access via the exported dma-address.
	 */
	drm_clflush_pages(pages, n_pages);

	वापस 0;
पूर्ण

अटल व्योम vgem_prime_unpin(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_vgem_gem_object *bo = to_vgem_bo(obj);

	vgem_unpin_pages(bo);
पूर्ण

अटल काष्ठा sg_table *vgem_prime_get_sg_table(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_vgem_gem_object *bo = to_vgem_bo(obj);

	वापस drm_prime_pages_to_sg(obj->dev, bo->pages, bo->base.size >> PAGE_SHIFT);
पूर्ण

अटल काष्ठा drm_gem_object* vgem_prime_import(काष्ठा drm_device *dev,
						काष्ठा dma_buf *dma_buf)
अणु
	काष्ठा vgem_device *vgem = container_of(dev, typeof(*vgem), drm);

	वापस drm_gem_prime_import_dev(dev, dma_buf, &vgem->platक्रमm->dev);
पूर्ण

अटल काष्ठा drm_gem_object *vgem_prime_import_sg_table(काष्ठा drm_device *dev,
			काष्ठा dma_buf_attachment *attach, काष्ठा sg_table *sg)
अणु
	काष्ठा drm_vgem_gem_object *obj;
	पूर्णांक npages;

	obj = __vgem_gem_create(dev, attach->dmabuf->size);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	npages = PAGE_ALIGN(attach->dmabuf->size) / PAGE_SIZE;

	obj->table = sg;
	obj->pages = kvदो_स्मृति_array(npages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!obj->pages) अणु
		__vgem_gem_destroy(obj);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	obj->pages_pin_count++; /* perma-pinned */
	drm_prime_sg_to_page_array(obj->table, obj->pages, npages);
	वापस &obj->base;
पूर्ण

अटल पूर्णांक vgem_prime_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_vgem_gem_object *bo = to_vgem_bo(obj);
	दीर्घ n_pages = obj->size >> PAGE_SHIFT;
	काष्ठा page **pages;
	व्योम *vaddr;

	pages = vgem_pin_pages(bo);
	अगर (IS_ERR(pages))
		वापस PTR_ERR(pages);

	vaddr = vmap(pages, n_pages, 0, pgprot_ग_लिखोcombine(PAGE_KERNEL));
	अगर (!vaddr)
		वापस -ENOMEM;
	dma_buf_map_set_vaddr(map, vaddr);

	वापस 0;
पूर्ण

अटल व्योम vgem_prime_vunmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_vgem_gem_object *bo = to_vgem_bo(obj);

	vunmap(map->vaddr);
	vgem_unpin_pages(bo);
पूर्ण

अटल पूर्णांक vgem_prime_mmap(काष्ठा drm_gem_object *obj,
			   काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;

	अगर (obj->size < vma->vm_end - vma->vm_start)
		वापस -EINVAL;

	अगर (!obj->filp)
		वापस -ENODEV;

	ret = call_mmap(obj->filp, vma);
	अगर (ret)
		वापस ret;

	vma_set_file(vma, obj->filp);
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_page_prot = pgprot_ग_लिखोcombine(vm_get_page_prot(vma->vm_flags));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_gem_object_funcs vgem_gem_object_funcs = अणु
	.मुक्त = vgem_gem_मुक्त_object,
	.pin = vgem_prime_pin,
	.unpin = vgem_prime_unpin,
	.get_sg_table = vgem_prime_get_sg_table,
	.vmap = vgem_prime_vmap,
	.vunmap = vgem_prime_vunmap,
	.vm_ops = &vgem_gem_vm_ops,
पूर्ण;

अटल स्थिर काष्ठा drm_driver vgem_driver = अणु
	.driver_features		= DRIVER_GEM | DRIVER_RENDER,
	.खोलो				= vgem_खोलो,
	.postबंद			= vgem_postबंद,
	.ioctls				= vgem_ioctls,
	.num_ioctls 			= ARRAY_SIZE(vgem_ioctls),
	.fops				= &vgem_driver_fops,

	.dumb_create			= vgem_gem_dumb_create,

	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import = vgem_prime_import,
	.gem_prime_import_sg_table = vgem_prime_import_sg_table,
	.gem_prime_mmap = vgem_prime_mmap,

	.name	= DRIVER_NAME,
	.desc	= DRIVER_DESC,
	.date	= DRIVER_DATE,
	.major	= DRIVER_MAJOR,
	.minor	= DRIVER_MINOR,
पूर्ण;

अटल पूर्णांक __init vgem_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_रेजिस्टर_simple("vgem", -1, शून्य, 0);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	अगर (!devres_खोलो_group(&pdev->dev, शून्य, GFP_KERNEL)) अणु
		ret = -ENOMEM;
		जाओ out_unरेजिस्टर;
	पूर्ण

	dma_coerce_mask_and_coherent(&pdev->dev,
				     DMA_BIT_MASK(64));

	vgem_device = devm_drm_dev_alloc(&pdev->dev, &vgem_driver,
					 काष्ठा vgem_device, drm);
	अगर (IS_ERR(vgem_device)) अणु
		ret = PTR_ERR(vgem_device);
		जाओ out_devres;
	पूर्ण
	vgem_device->platक्रमm = pdev;

	/* Final step: expose the device/driver to userspace */
	ret = drm_dev_रेजिस्टर(&vgem_device->drm, 0);
	अगर (ret)
		जाओ out_devres;

	वापस 0;

out_devres:
	devres_release_group(&pdev->dev, शून्य);
out_unरेजिस्टर:
	platक्रमm_device_unरेजिस्टर(pdev);
	वापस ret;
पूर्ण

अटल व्योम __निकास vgem_निकास(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev = vgem_device->platक्रमm;

	drm_dev_unरेजिस्टर(&vgem_device->drm);
	devres_release_group(&pdev->dev, शून्य);
	platक्रमm_device_unरेजिस्टर(pdev);
पूर्ण

module_init(vgem_init);
module_निकास(vgem_निकास);

MODULE_AUTHOR("Red Hat, Inc.");
MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
