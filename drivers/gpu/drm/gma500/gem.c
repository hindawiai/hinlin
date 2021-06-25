<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  psb GEM पूर्णांकerface
 *
 * Copyright (c) 2011, Intel Corporation.
 *
 * Authors: Alan Cox
 *
 * TODO:
 *	-	we need to work out अगर the MMU is relevant (eg क्रम
 *		accelerated operations on a GEM object)
 */

#समावेश <linux/pagemap.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_vma_manager.h>

#समावेश "gem.h"
#समावेश "psb_drv.h"

अटल vm_fault_t psb_gem_fault(काष्ठा vm_fault *vmf);

अटल व्योम psb_gem_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा gtt_range *gtt = container_of(obj, काष्ठा gtt_range, gem);

	/* Remove the list map अगर one is present */
	drm_gem_मुक्त_mmap_offset(obj);
	drm_gem_object_release(obj);

	/* This must occur last as it मुक्तs up the memory of the GEM object */
	psb_gtt_मुक्त_range(obj->dev, gtt);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा psb_gem_vm_ops = अणु
	.fault = psb_gem_fault,
	.खोलो = drm_gem_vm_खोलो,
	.बंद = drm_gem_vm_बंद,
पूर्ण;

स्थिर काष्ठा drm_gem_object_funcs psb_gem_object_funcs = अणु
	.मुक्त = psb_gem_मुक्त_object,
	.vm_ops = &psb_gem_vm_ops,
पूर्ण;

/**
 *	psb_gem_create		-	create a mappable object
 *	@file: the DRM file of the client
 *	@dev: our device
 *	@size: the size requested
 *	@handlep: वापसed handle (opaque number)
 *	@stolen: unused
 *	@align: unused
 *
 *	Create a GEM object, fill in the boilerplate and attach a handle to
 *	it so that userspace can speak about it. This करोes the core work
 *	क्रम the various methods that करो/will create GEM objects क्रम things
 */
पूर्णांक psb_gem_create(काष्ठा drm_file *file, काष्ठा drm_device *dev, u64 size,
		   u32 *handlep, पूर्णांक stolen, u32 align)
अणु
	काष्ठा gtt_range *r;
	पूर्णांक ret;
	u32 handle;

	size = roundup(size, PAGE_SIZE);

	/* Allocate our object - क्रम now a direct gtt range which is not
	   stolen memory backed */
	r = psb_gtt_alloc_range(dev, size, "gem", 0, PAGE_SIZE);
	अगर (r == शून्य) अणु
		dev_err(dev->dev, "no memory for %lld byte GEM object\n", size);
		वापस -ENOSPC;
	पूर्ण
	r->gem.funcs = &psb_gem_object_funcs;
	/* Initialize the extra goodies GEM needs to करो all the hard work */
	अगर (drm_gem_object_init(dev, &r->gem, size) != 0) अणु
		psb_gtt_मुक्त_range(dev, r);
		/* GEM करोesn't give an error code so use -ENOMEM */
		dev_err(dev->dev, "GEM init failed for %lld\n", size);
		वापस -ENOMEM;
	पूर्ण
	/* Limit the object to 32bit mappings */
	mapping_set_gfp_mask(r->gem.filp->f_mapping, GFP_KERNEL | __GFP_DMA32);
	/* Give the object a handle so we can carry it more easily */
	ret = drm_gem_handle_create(file, &r->gem, &handle);
	अगर (ret) अणु
		dev_err(dev->dev, "GEM handle failed for %p, %lld\n",
							&r->gem, size);
		drm_gem_object_release(&r->gem);
		psb_gtt_मुक्त_range(dev, r);
		वापस ret;
	पूर्ण
	/* We have the initial and handle reference but need only one now */
	drm_gem_object_put(&r->gem);
	*handlep = handle;
	वापस 0;
पूर्ण

/**
 *	psb_gem_dumb_create	-	create a dumb buffer
 *	@file: our client file
 *	@dev: our device
 *	@args: the requested arguments copied from userspace
 *
 *	Allocate a buffer suitable क्रम use क्रम a frame buffer of the
 *	क्रमm described by user space. Give userspace a handle by which
 *	to reference it.
 */
पूर्णांक psb_gem_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
			काष्ठा drm_mode_create_dumb *args)
अणु
	args->pitch = ALIGN(args->width * ((args->bpp + 7) / 8), 64);
	args->size = args->pitch * args->height;
	वापस psb_gem_create(file, dev, args->size, &args->handle, 0,
			      PAGE_SIZE);
पूर्ण

/**
 *	psb_gem_fault		-	pagefault handler क्रम GEM objects
 *	@vmf: fault detail
 *
 *	Invoked when a fault occurs on an mmap of a GEM managed area. GEM
 *	करोes most of the work क्रम us including the actual map/unmap calls
 *	but we need to करो the actual page work.
 *
 *	This code eventually needs to handle faulting objects in and out
 *	of the GTT and repacking it when we run out of space. We can put
 *	that off क्रम now and क्रम our simple uses
 *
 *	The VMA was set up by GEM. In करोing so it also ensured that the
 *	vma->vm_निजी_data poपूर्णांकs to the GEM object that is backing this
 *	mapping.
 */
अटल vm_fault_t psb_gem_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा drm_gem_object *obj;
	काष्ठा gtt_range *r;
	पूर्णांक err;
	vm_fault_t ret;
	अचिन्हित दीर्घ pfn;
	pgoff_t page_offset;
	काष्ठा drm_device *dev;
	काष्ठा drm_psb_निजी *dev_priv;

	obj = vma->vm_निजी_data;	/* GEM object */
	dev = obj->dev;
	dev_priv = dev->dev_निजी;

	r = container_of(obj, काष्ठा gtt_range, gem);	/* Get the gtt range */

	/* Make sure we करोn't parallel update on a fault, nor move or हटाओ
	   something from beneath our feet */
	mutex_lock(&dev_priv->mmap_mutex);

	/* For now the mmap pins the object and it stays pinned. As things
	   stand that will करो us no harm */
	अगर (r->mmapping == 0) अणु
		err = psb_gtt_pin(r);
		अगर (err < 0) अणु
			dev_err(dev->dev, "gma500: pin failed: %d\n", err);
			ret = vmf_error(err);
			जाओ fail;
		पूर्ण
		r->mmapping = 1;
	पूर्ण

	/* Page relative to the VMA start - we must calculate this ourselves
	   because vmf->pgoff is the fake GEM offset */
	page_offset = (vmf->address - vma->vm_start) >> PAGE_SHIFT;

	/* CPU view of the page, करोn't go via the GART क्रम CPU ग_लिखोs */
	अगर (r->stolen)
		pfn = (dev_priv->stolen_base + r->offset) >> PAGE_SHIFT;
	अन्यथा
		pfn = page_to_pfn(r->pages[page_offset]);
	ret = vmf_insert_pfn(vma, vmf->address, pfn);
fail:
	mutex_unlock(&dev_priv->mmap_mutex);

	वापस ret;
पूर्ण
