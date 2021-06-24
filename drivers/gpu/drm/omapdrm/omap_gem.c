<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob.clark@linaro.org>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pfn_t.h>

#समावेश <drm/drm_prime.h>
#समावेश <drm/drm_vma_manager.h>

#समावेश "omap_drv.h"
#समावेश "omap_dmm_tiler.h"

/*
 * GEM buffer object implementation.
 */

/* note: we use upper 8 bits of flags क्रम driver-पूर्णांकernal flags: */
#घोषणा OMAP_BO_MEM_DMA_API	0x01000000	/* memory allocated with the dma_alloc_* API */
#घोषणा OMAP_BO_MEM_SHMEM	0x02000000	/* memory allocated through shmem backing */
#घोषणा OMAP_BO_MEM_DMABUF	0x08000000	/* memory imported from a dmabuf */

काष्ठा omap_gem_object अणु
	काष्ठा drm_gem_object base;

	काष्ठा list_head mm_list;

	u32 flags;

	/** width/height क्रम tiled क्रमmats (rounded up to slot boundaries) */
	u16 width, height;

	/** roll applied when mapping to DMM */
	u32 roll;

	/** protects dma_addr_cnt, block, pages, dma_addrs and vaddr */
	काष्ठा mutex lock;

	/**
	 * dma_addr contains the buffer DMA address. It is valid क्रम
	 *
	 * - buffers allocated through the DMA mapping API (with the
	 *   OMAP_BO_MEM_DMA_API flag set)
	 *
	 * - buffers imported from dmabuf (with the OMAP_BO_MEM_DMABUF flag set)
	 *   अगर they are physically contiguous (when sgt->orig_nents == 1)
	 *
	 * - buffers mapped through the TILER when dma_addr_cnt is not zero, in
	 *   which हाल the DMA address poपूर्णांकs to the TILER aperture
	 *
	 * Physically contiguous buffers have their DMA address equal to the
	 * physical address as we करोn't remap those buffers through the TILER.
	 *
	 * Buffers mapped to the TILER have their DMA address poपूर्णांकing to the
	 * TILER aperture. As TILER mappings are refcounted (through
	 * dma_addr_cnt) the DMA address must be accessed through omap_gem_pin()
	 * to ensure that the mapping won't disappear unexpectedly. References
	 * must be released with omap_gem_unpin().
	 */
	dma_addr_t dma_addr;

	/**
	 * # of users of dma_addr
	 */
	refcount_t dma_addr_cnt;

	/**
	 * If the buffer has been imported from a dmabuf the OMAP_DB_DMABUF flag
	 * is set and the sgt field is valid.
	 */
	काष्ठा sg_table *sgt;

	/**
	 * tiler block used when buffer is remapped in DMM/TILER.
	 */
	काष्ठा tiler_block *block;

	/**
	 * Array of backing pages, अगर allocated.  Note that pages are never
	 * allocated क्रम buffers originally allocated from contiguous memory
	 */
	काष्ठा page **pages;

	/** addresses corresponding to pages in above array */
	dma_addr_t *dma_addrs;

	/**
	 * Virtual address, अगर mapped.
	 */
	व्योम *vaddr;
पूर्ण;

#घोषणा to_omap_bo(x) container_of(x, काष्ठा omap_gem_object, base)

/* To deal with userspace mmap'ings of 2d tiled buffers, which (a) are
 * not necessarily pinned in TILER all the समय, and (b) when they are
 * they are not necessarily page aligned, we reserve one or more small
 * regions in each of the 2d containers to use as a user-GART where we
 * can create a second page-aligned mapping of parts of the buffer
 * being accessed from userspace.
 *
 * Note that we could optimize slightly when we know that multiple
 * tiler containers are backed by the same PAT.. but I'll leave that
 * क्रम later..
 */
#घोषणा NUM_USERGART_ENTRIES 2
काष्ठा omap_drm_usergart_entry अणु
	काष्ठा tiler_block *block;	/* the reserved tiler block */
	dma_addr_t dma_addr;
	काष्ठा drm_gem_object *obj;	/* the current pinned obj */
	pgoff_t obj_pgoff;		/* page offset of obj currently
					   mapped in */
पूर्ण;

काष्ठा omap_drm_usergart अणु
	काष्ठा omap_drm_usergart_entry entry[NUM_USERGART_ENTRIES];
	पूर्णांक height;				/* height in rows */
	पूर्णांक height_shअगरt;		/* ilog2(height in rows) */
	पूर्णांक slot_shअगरt;			/* ilog2(width per slot) */
	पूर्णांक stride_pfn;			/* stride in pages */
	पूर्णांक last;				/* index of last used entry */
पूर्ण;

/* -----------------------------------------------------------------------------
 * Helpers
 */

/** get mmap offset */
u64 omap_gem_mmap_offset(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_device *dev = obj->dev;
	पूर्णांक ret;
	माप_प्रकार size;

	/* Make it mmapable */
	size = omap_gem_mmap_size(obj);
	ret = drm_gem_create_mmap_offset_size(obj, size);
	अगर (ret) अणु
		dev_err(dev->dev, "could not allocate mmap offset\n");
		वापस 0;
	पूर्ण

	वापस drm_vma_node_offset_addr(&obj->vma_node);
पूर्ण

अटल bool omap_gem_is_contiguous(काष्ठा omap_gem_object *omap_obj)
अणु
	अगर (omap_obj->flags & OMAP_BO_MEM_DMA_API)
		वापस true;

	अगर ((omap_obj->flags & OMAP_BO_MEM_DMABUF) && omap_obj->sgt->nents == 1)
		वापस true;

	वापस false;
पूर्ण

/* -----------------------------------------------------------------------------
 * Eviction
 */

अटल व्योम omap_gem_evict_entry(काष्ठा drm_gem_object *obj,
		क्रमागत tiler_fmt fmt, काष्ठा omap_drm_usergart_entry *entry)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	काष्ठा omap_drm_निजी *priv = obj->dev->dev_निजी;
	पूर्णांक n = priv->usergart[fmt].height;
	माप_प्रकार size = PAGE_SIZE * n;
	loff_t off = omap_gem_mmap_offset(obj) +
			(entry->obj_pgoff << PAGE_SHIFT);
	स्थिर पूर्णांक m = DIV_ROUND_UP(omap_obj->width << fmt, PAGE_SIZE);

	अगर (m > 1) अणु
		पूर्णांक i;
		/* अगर stride > than PAGE_SIZE then sparse mapping: */
		क्रम (i = n; i > 0; i--) अणु
			unmap_mapping_range(obj->dev->anon_inode->i_mapping,
					    off, PAGE_SIZE, 1);
			off += PAGE_SIZE * m;
		पूर्ण
	पूर्ण अन्यथा अणु
		unmap_mapping_range(obj->dev->anon_inode->i_mapping,
				    off, size, 1);
	पूर्ण

	entry->obj = शून्य;
पूर्ण

/* Evict a buffer from usergart, अगर it is mapped there */
अटल व्योम omap_gem_evict(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	काष्ठा omap_drm_निजी *priv = obj->dev->dev_निजी;

	अगर (omap_obj->flags & OMAP_BO_TILED_MASK) अणु
		क्रमागत tiler_fmt fmt = gem2fmt(omap_obj->flags);
		पूर्णांक i;

		क्रम (i = 0; i < NUM_USERGART_ENTRIES; i++) अणु
			काष्ठा omap_drm_usergart_entry *entry =
				&priv->usergart[fmt].entry[i];

			अगर (entry->obj == obj)
				omap_gem_evict_entry(obj, fmt, entry);
		पूर्ण
	पूर्ण
पूर्ण

/* -----------------------------------------------------------------------------
 * Page Management
 */

/*
 * Ensure backing pages are allocated. Must be called with the omap_obj.lock
 * held.
 */
अटल पूर्णांक omap_gem_attach_pages(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_device *dev = obj->dev;
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	काष्ठा page **pages;
	पूर्णांक npages = obj->size >> PAGE_SHIFT;
	पूर्णांक i, ret;
	dma_addr_t *addrs;

	lockdep_निश्चित_held(&omap_obj->lock);

	/*
	 * If not using shmem (in which हाल backing pages करोn't need to be
	 * allocated) or अगर pages are alपढ़ोy allocated we're करोne.
	 */
	अगर (!(omap_obj->flags & OMAP_BO_MEM_SHMEM) || omap_obj->pages)
		वापस 0;

	pages = drm_gem_get_pages(obj);
	अगर (IS_ERR(pages)) अणु
		dev_err(obj->dev->dev, "could not get pages: %ld\n", PTR_ERR(pages));
		वापस PTR_ERR(pages);
	पूर्ण

	/* क्रम non-cached buffers, ensure the new pages are clean because
	 * DSS, GPU, etc. are not cache coherent:
	 */
	अगर (omap_obj->flags & (OMAP_BO_WC|OMAP_BO_UNCACHED)) अणु
		addrs = kदो_स्मृति_array(npages, माप(*addrs), GFP_KERNEL);
		अगर (!addrs) अणु
			ret = -ENOMEM;
			जाओ मुक्त_pages;
		पूर्ण

		क्रम (i = 0; i < npages; i++) अणु
			addrs[i] = dma_map_page(dev->dev, pages[i],
					0, PAGE_SIZE, DMA_TO_DEVICE);

			अगर (dma_mapping_error(dev->dev, addrs[i])) अणु
				dev_warn(dev->dev,
					"%s: failed to map page\n", __func__);

				क्रम (i = i - 1; i >= 0; --i) अणु
					dma_unmap_page(dev->dev, addrs[i],
						PAGE_SIZE, DMA_TO_DEVICE);
				पूर्ण

				ret = -ENOMEM;
				जाओ मुक्त_addrs;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		addrs = kसुस्मृति(npages, माप(*addrs), GFP_KERNEL);
		अगर (!addrs) अणु
			ret = -ENOMEM;
			जाओ मुक्त_pages;
		पूर्ण
	पूर्ण

	omap_obj->dma_addrs = addrs;
	omap_obj->pages = pages;

	वापस 0;

मुक्त_addrs:
	kमुक्त(addrs);
मुक्त_pages:
	drm_gem_put_pages(obj, pages, true, false);

	वापस ret;
पूर्ण

/* Release backing pages. Must be called with the omap_obj.lock held. */
अटल व्योम omap_gem_detach_pages(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	अचिन्हित पूर्णांक npages = obj->size >> PAGE_SHIFT;
	अचिन्हित पूर्णांक i;

	lockdep_निश्चित_held(&omap_obj->lock);

	क्रम (i = 0; i < npages; i++) अणु
		अगर (omap_obj->dma_addrs[i])
			dma_unmap_page(obj->dev->dev, omap_obj->dma_addrs[i],
				       PAGE_SIZE, DMA_TO_DEVICE);
	पूर्ण

	kमुक्त(omap_obj->dma_addrs);
	omap_obj->dma_addrs = शून्य;

	drm_gem_put_pages(obj, omap_obj->pages, true, false);
	omap_obj->pages = शून्य;
पूर्ण

/* get buffer flags */
u32 omap_gem_flags(काष्ठा drm_gem_object *obj)
अणु
	वापस to_omap_bo(obj)->flags;
पूर्ण

/** get mmap size */
माप_प्रकार omap_gem_mmap_size(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	माप_प्रकार size = obj->size;

	अगर (omap_obj->flags & OMAP_BO_TILED_MASK) अणु
		/* क्रम tiled buffers, the भव size has stride rounded up
		 * to 4kb.. (to hide the fact that row n+1 might start 16kb or
		 * 32kb later!).  But we करोn't back the entire buffer with
		 * pages, only the valid picture part.. so need to adjust क्रम
		 * this in the size used to mmap and generate mmap offset
		 */
		size = tiler_vsize(gem2fmt(omap_obj->flags),
				omap_obj->width, omap_obj->height);
	पूर्ण

	वापस size;
पूर्ण

/* -----------------------------------------------------------------------------
 * Fault Handling
 */

/* Normal handling क्रम the हाल of faulting in non-tiled buffers */
अटल vm_fault_t omap_gem_fault_1d(काष्ठा drm_gem_object *obj,
		काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_fault *vmf)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	अचिन्हित दीर्घ pfn;
	pgoff_t pgoff;

	/* We करोn't use vmf->pgoff since that has the fake offset: */
	pgoff = (vmf->address - vma->vm_start) >> PAGE_SHIFT;

	अगर (omap_obj->pages) अणु
		omap_gem_cpu_sync_page(obj, pgoff);
		pfn = page_to_pfn(omap_obj->pages[pgoff]);
	पूर्ण अन्यथा अणु
		BUG_ON(!omap_gem_is_contiguous(omap_obj));
		pfn = (omap_obj->dma_addr >> PAGE_SHIFT) + pgoff;
	पूर्ण

	VERB("Inserting %p pfn %lx, pa %lx", (व्योम *)vmf->address,
			pfn, pfn << PAGE_SHIFT);

	वापस vmf_insert_mixed(vma, vmf->address,
			__pfn_to_pfn_t(pfn, PFN_DEV));
पूर्ण

/* Special handling क्रम the हाल of faulting in 2d tiled buffers */
अटल vm_fault_t omap_gem_fault_2d(काष्ठा drm_gem_object *obj,
		काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_fault *vmf)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	काष्ठा omap_drm_निजी *priv = obj->dev->dev_निजी;
	काष्ठा omap_drm_usergart_entry *entry;
	क्रमागत tiler_fmt fmt = gem2fmt(omap_obj->flags);
	काष्ठा page *pages[64];  /* XXX is this too much to have on stack? */
	अचिन्हित दीर्घ pfn;
	pgoff_t pgoff, base_pgoff;
	अचिन्हित दीर्घ vaddr;
	पूर्णांक i, err, slots;
	vm_fault_t ret = VM_FAULT_NOPAGE;

	/*
	 * Note the height of the slot is also equal to the number of pages
	 * that need to be mapped in to fill 4kb wide CPU page.  If the slot
	 * height is 64, then 64 pages fill a 4kb wide by 64 row region.
	 */
	स्थिर पूर्णांक n = priv->usergart[fmt].height;
	स्थिर पूर्णांक n_shअगरt = priv->usergart[fmt].height_shअगरt;

	/*
	 * If buffer width in bytes > PAGE_SIZE then the भव stride is
	 * rounded up to next multiple of PAGE_SIZE.. this need to be taken
	 * पूर्णांकo account in some of the math, so figure out भव stride
	 * in pages
	 */
	स्थिर पूर्णांक m = DIV_ROUND_UP(omap_obj->width << fmt, PAGE_SIZE);

	/* We करोn't use vmf->pgoff since that has the fake offset: */
	pgoff = (vmf->address - vma->vm_start) >> PAGE_SHIFT;

	/*
	 * Actual address we start mapping at is rounded करोwn to previous slot
	 * boundary in the y direction:
	 */
	base_pgoff = round_करोwn(pgoff, m << n_shअगरt);

	/* figure out buffer width in slots */
	slots = omap_obj->width >> priv->usergart[fmt].slot_shअगरt;

	vaddr = vmf->address - ((pgoff - base_pgoff) << PAGE_SHIFT);

	entry = &priv->usergart[fmt].entry[priv->usergart[fmt].last];

	/* evict previous buffer using this usergart entry, अगर any: */
	अगर (entry->obj)
		omap_gem_evict_entry(entry->obj, fmt, entry);

	entry->obj = obj;
	entry->obj_pgoff = base_pgoff;

	/* now convert base_pgoff to phys offset from virt offset: */
	base_pgoff = (base_pgoff >> n_shअगरt) * slots;

	/* क्रम wider-than 4k.. figure out which part of the slot-row we want: */
	अगर (m > 1) अणु
		पूर्णांक off = pgoff % m;
		entry->obj_pgoff += off;
		base_pgoff /= m;
		slots = min(slots - (off << n_shअगरt), n);
		base_pgoff += off << n_shअगरt;
		vaddr += off << PAGE_SHIFT;
	पूर्ण

	/*
	 * Map in pages. Beyond the valid pixel part of the buffer, we set
	 * pages[i] to शून्य to get a dummy page mapped in.. अगर someone
	 * पढ़ोs/ग_लिखोs it they will get अक्रमom/undefined content, but at
	 * least it won't be corrupting whatever other अक्रमom page used to
	 * be mapped in, or other undefined behavior.
	 */
	स_नकल(pages, &omap_obj->pages[base_pgoff],
			माप(काष्ठा page *) * slots);
	स_रखो(pages + slots, 0,
			माप(काष्ठा page *) * (n - slots));

	err = tiler_pin(entry->block, pages, ARRAY_SIZE(pages), 0, true);
	अगर (err) अणु
		ret = vmf_error(err);
		dev_err(obj->dev->dev, "failed to pin: %d\n", err);
		वापस ret;
	पूर्ण

	pfn = entry->dma_addr >> PAGE_SHIFT;

	VERB("Inserting %p pfn %lx, pa %lx", (व्योम *)vmf->address,
			pfn, pfn << PAGE_SHIFT);

	क्रम (i = n; i > 0; i--) अणु
		ret = vmf_insert_mixed(vma,
			vaddr, __pfn_to_pfn_t(pfn, PFN_DEV));
		अगर (ret & VM_FAULT_ERROR)
			अवरोध;
		pfn += priv->usergart[fmt].stride_pfn;
		vaddr += PAGE_SIZE * m;
	पूर्ण

	/* simple round-robin: */
	priv->usergart[fmt].last = (priv->usergart[fmt].last + 1)
				 % NUM_USERGART_ENTRIES;

	वापस ret;
पूर्ण

/**
 * omap_gem_fault		-	pagefault handler क्रम GEM objects
 * @vmf: fault detail
 *
 * Invoked when a fault occurs on an mmap of a GEM managed area. GEM
 * करोes most of the work क्रम us including the actual map/unmap calls
 * but we need to करो the actual page work.
 *
 * The VMA was set up by GEM. In करोing so it also ensured that the
 * vma->vm_निजी_data poपूर्णांकs to the GEM object that is backing this
 * mapping.
 */
अटल vm_fault_t omap_gem_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा drm_gem_object *obj = vma->vm_निजी_data;
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	पूर्णांक err;
	vm_fault_t ret;

	/* Make sure we करोn't parallel update on a fault, nor move or हटाओ
	 * something from beneath our feet
	 */
	mutex_lock(&omap_obj->lock);

	/* अगर a shmem backed object, make sure we have pages attached now */
	err = omap_gem_attach_pages(obj);
	अगर (err) अणु
		ret = vmf_error(err);
		जाओ fail;
	पूर्ण

	/* where should we करो corresponding put_pages().. we are mapping
	 * the original page, rather than thru a GART, so we can't rely
	 * on eviction to trigger this.  But munmap() or all mappings should
	 * probably trigger put_pages()?
	 */

	अगर (omap_obj->flags & OMAP_BO_TILED_MASK)
		ret = omap_gem_fault_2d(obj, vma, vmf);
	अन्यथा
		ret = omap_gem_fault_1d(obj, vma, vmf);


fail:
	mutex_unlock(&omap_obj->lock);
	वापस ret;
पूर्ण

/** We override मुख्यly to fix up some of the vm mapping flags.. */
पूर्णांक omap_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;

	ret = drm_gem_mmap(filp, vma);
	अगर (ret) अणु
		DBG("mmap failed: %d", ret);
		वापस ret;
	पूर्ण

	वापस omap_gem_mmap_obj(vma->vm_निजी_data, vma);
पूर्ण

पूर्णांक omap_gem_mmap_obj(काष्ठा drm_gem_object *obj,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);

	vma->vm_flags &= ~VM_PFNMAP;
	vma->vm_flags |= VM_MIXEDMAP;

	अगर (omap_obj->flags & OMAP_BO_WC) अणु
		vma->vm_page_prot = pgprot_ग_लिखोcombine(vm_get_page_prot(vma->vm_flags));
	पूर्ण अन्यथा अगर (omap_obj->flags & OMAP_BO_UNCACHED) अणु
		vma->vm_page_prot = pgprot_noncached(vm_get_page_prot(vma->vm_flags));
	पूर्ण अन्यथा अणु
		/*
		 * We करो have some निजी objects, at least क्रम scanout buffers
		 * on hardware without DMM/TILER.  But these are allocated ग_लिखो-
		 * combine
		 */
		अगर (WARN_ON(!obj->filp))
			वापस -EINVAL;

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

/* -----------------------------------------------------------------------------
 * Dumb Buffers
 */

/**
 * omap_gem_dumb_create	-	create a dumb buffer
 * @file: our client file
 * @dev: our device
 * @args: the requested arguments copied from userspace
 *
 * Allocate a buffer suitable क्रम use क्रम a frame buffer of the
 * क्रमm described by user space. Give userspace a handle by which
 * to reference it.
 */
पूर्णांक omap_gem_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
		काष्ठा drm_mode_create_dumb *args)
अणु
	जोड़ omap_gem_size gsize;

	args->pitch = DIV_ROUND_UP(args->width * args->bpp, 8);

	args->size = PAGE_ALIGN(args->pitch * args->height);

	gsize = (जोड़ omap_gem_size)अणु
		.bytes = args->size,
	पूर्ण;

	वापस omap_gem_new_handle(dev, file, gsize,
			OMAP_BO_SCANOUT | OMAP_BO_WC, &args->handle);
पूर्ण

/**
 * omap_gem_dumb_map	-	buffer mapping क्रम dumb पूर्णांकerface
 * @file: our drm client file
 * @dev: drm device
 * @handle: GEM handle to the object (from dumb_create)
 * @offset: memory map offset placeholder
 *
 * Do the necessary setup to allow the mapping of the frame buffer
 * पूर्णांकo user memory. We करोn't have to करो much here at the moment.
 */
पूर्णांक omap_gem_dumb_map_offset(काष्ठा drm_file *file, काष्ठा drm_device *dev,
		u32 handle, u64 *offset)
अणु
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret = 0;

	/* GEM करोes all our handle to object mapping */
	obj = drm_gem_object_lookup(file, handle);
	अगर (obj == शून्य) अणु
		ret = -ENOENT;
		जाओ fail;
	पूर्ण

	*offset = omap_gem_mmap_offset(obj);

	drm_gem_object_put(obj);

fail:
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
/* Set scrolling position.  This allows us to implement fast scrolling
 * क्रम console.
 *
 * Call only from non-atomic contexts.
 */
पूर्णांक omap_gem_roll(काष्ठा drm_gem_object *obj, u32 roll)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	u32 npages = obj->size >> PAGE_SHIFT;
	पूर्णांक ret = 0;

	अगर (roll > npages) अणु
		dev_err(obj->dev->dev, "invalid roll: %d\n", roll);
		वापस -EINVAL;
	पूर्ण

	omap_obj->roll = roll;

	mutex_lock(&omap_obj->lock);

	/* अगर we aren't mapped yet, we don't need to करो anything */
	अगर (omap_obj->block) अणु
		ret = omap_gem_attach_pages(obj);
		अगर (ret)
			जाओ fail;

		ret = tiler_pin(omap_obj->block, omap_obj->pages, npages,
				roll, true);
		अगर (ret)
			dev_err(obj->dev->dev, "could not repin: %d\n", ret);
	पूर्ण

fail:
	mutex_unlock(&omap_obj->lock);

	वापस ret;
पूर्ण
#पूर्ण_अगर

/* -----------------------------------------------------------------------------
 * Memory Management & DMA Sync
 */

/*
 * shmem buffers that are mapped cached are not coherent.
 *
 * We keep track of dirty pages using page faulting to perक्रमm cache management.
 * When a page is mapped to the CPU in पढ़ो/ग_लिखो mode the device can't access
 * it and omap_obj->dma_addrs[i] is शून्य. When a page is mapped to the device
 * the omap_obj->dma_addrs[i] is set to the DMA address, and the page is
 * unmapped from the CPU.
 */
अटल अंतरभूत bool omap_gem_is_cached_coherent(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);

	वापस !((omap_obj->flags & OMAP_BO_MEM_SHMEM) &&
		((omap_obj->flags & OMAP_BO_CACHE_MASK) == OMAP_BO_CACHED));
पूर्ण

/* Sync the buffer क्रम CPU access.. note pages should alपढ़ोy be
 * attached, ie. omap_gem_get_pages()
 */
व्योम omap_gem_cpu_sync_page(काष्ठा drm_gem_object *obj, पूर्णांक pgoff)
अणु
	काष्ठा drm_device *dev = obj->dev;
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);

	अगर (omap_gem_is_cached_coherent(obj))
		वापस;

	अगर (omap_obj->dma_addrs[pgoff]) अणु
		dma_unmap_page(dev->dev, omap_obj->dma_addrs[pgoff],
				PAGE_SIZE, DMA_TO_DEVICE);
		omap_obj->dma_addrs[pgoff] = 0;
	पूर्ण
पूर्ण

/* sync the buffer क्रम DMA access */
व्योम omap_gem_dma_sync_buffer(काष्ठा drm_gem_object *obj,
		क्रमागत dma_data_direction dir)
अणु
	काष्ठा drm_device *dev = obj->dev;
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	पूर्णांक i, npages = obj->size >> PAGE_SHIFT;
	काष्ठा page **pages = omap_obj->pages;
	bool dirty = false;

	अगर (omap_gem_is_cached_coherent(obj))
		वापस;

	क्रम (i = 0; i < npages; i++) अणु
		अगर (!omap_obj->dma_addrs[i]) अणु
			dma_addr_t addr;

			addr = dma_map_page(dev->dev, pages[i], 0,
					    PAGE_SIZE, dir);
			अगर (dma_mapping_error(dev->dev, addr)) अणु
				dev_warn(dev->dev, "%s: failed to map page\n",
					__func__);
				अवरोध;
			पूर्ण

			dirty = true;
			omap_obj->dma_addrs[i] = addr;
		पूर्ण
	पूर्ण

	अगर (dirty) अणु
		unmap_mapping_range(obj->filp->f_mapping, 0,
				    omap_gem_mmap_size(obj), 1);
	पूर्ण
पूर्ण

/**
 * omap_gem_pin() - Pin a GEM object in memory
 * @obj: the GEM object
 * @dma_addr: the DMA address
 *
 * Pin the given GEM object in memory and fill the dma_addr poपूर्णांकer with the
 * object's DMA address. If the buffer is not physically contiguous it will be
 * remapped through the TILER to provide a contiguous view.
 *
 * Pins are reference-counted, calling this function multiple बार is allowed
 * as दीर्घ the corresponding omap_gem_unpin() calls are balanced.
 *
 * Return 0 on success or a negative error code otherwise.
 */
पूर्णांक omap_gem_pin(काष्ठा drm_gem_object *obj, dma_addr_t *dma_addr)
अणु
	काष्ठा omap_drm_निजी *priv = obj->dev->dev_निजी;
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	पूर्णांक ret = 0;

	mutex_lock(&omap_obj->lock);

	अगर (!omap_gem_is_contiguous(omap_obj) && priv->has_dmm) अणु
		अगर (refcount_पढ़ो(&omap_obj->dma_addr_cnt) == 0) अणु
			u32 npages = obj->size >> PAGE_SHIFT;
			क्रमागत tiler_fmt fmt = gem2fmt(omap_obj->flags);
			काष्ठा tiler_block *block;

			BUG_ON(omap_obj->block);

			refcount_set(&omap_obj->dma_addr_cnt, 1);

			ret = omap_gem_attach_pages(obj);
			अगर (ret)
				जाओ fail;

			अगर (omap_obj->flags & OMAP_BO_TILED_MASK) अणु
				block = tiler_reserve_2d(fmt,
						omap_obj->width,
						omap_obj->height, 0);
			पूर्ण अन्यथा अणु
				block = tiler_reserve_1d(obj->size);
			पूर्ण

			अगर (IS_ERR(block)) अणु
				ret = PTR_ERR(block);
				dev_err(obj->dev->dev,
					"could not remap: %d (%d)\n", ret, fmt);
				जाओ fail;
			पूर्ण

			/* TODO: enable async refill.. */
			ret = tiler_pin(block, omap_obj->pages, npages,
					omap_obj->roll, true);
			अगर (ret) अणु
				tiler_release(block);
				dev_err(obj->dev->dev,
						"could not pin: %d\n", ret);
				जाओ fail;
			पूर्ण

			omap_obj->dma_addr = tiler_ssptr(block);
			omap_obj->block = block;

			DBG("got dma address: %pad", &omap_obj->dma_addr);
		पूर्ण अन्यथा अणु
			refcount_inc(&omap_obj->dma_addr_cnt);
		पूर्ण

		अगर (dma_addr)
			*dma_addr = omap_obj->dma_addr;
	पूर्ण अन्यथा अगर (omap_gem_is_contiguous(omap_obj)) अणु
		अगर (dma_addr)
			*dma_addr = omap_obj->dma_addr;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

fail:
	mutex_unlock(&omap_obj->lock);

	वापस ret;
पूर्ण

/**
 * omap_gem_unpin_locked() - Unpin a GEM object from memory
 * @obj: the GEM object
 *
 * omap_gem_unpin() without locking.
 */
अटल व्योम omap_gem_unpin_locked(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा omap_drm_निजी *priv = obj->dev->dev_निजी;
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	पूर्णांक ret;

	अगर (omap_gem_is_contiguous(omap_obj) || !priv->has_dmm)
		वापस;

	अगर (refcount_dec_and_test(&omap_obj->dma_addr_cnt)) अणु
		ret = tiler_unpin(omap_obj->block);
		अगर (ret) अणु
			dev_err(obj->dev->dev,
				"could not unpin pages: %d\n", ret);
		पूर्ण
		ret = tiler_release(omap_obj->block);
		अगर (ret) अणु
			dev_err(obj->dev->dev,
				"could not release unmap: %d\n", ret);
		पूर्ण
		omap_obj->dma_addr = 0;
		omap_obj->block = शून्य;
	पूर्ण
पूर्ण

/**
 * omap_gem_unpin() - Unpin a GEM object from memory
 * @obj: the GEM object
 *
 * Unpin the given GEM object previously pinned with omap_gem_pin(). Pins are
 * reference-counted, the actual unpin will only be perक्रमmed when the number
 * of calls to this function matches the number of calls to omap_gem_pin().
 */
व्योम omap_gem_unpin(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);

	mutex_lock(&omap_obj->lock);
	omap_gem_unpin_locked(obj);
	mutex_unlock(&omap_obj->lock);
पूर्ण

/* Get rotated scanout address (only valid अगर alपढ़ोy pinned), at the
 * specअगरied orientation and x,y offset from top-left corner of buffer
 * (only valid क्रम tiled 2d buffers)
 */
पूर्णांक omap_gem_rotated_dma_addr(काष्ठा drm_gem_object *obj, u32 orient,
		पूर्णांक x, पूर्णांक y, dma_addr_t *dma_addr)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	पूर्णांक ret = -EINVAL;

	mutex_lock(&omap_obj->lock);

	अगर ((refcount_पढ़ो(&omap_obj->dma_addr_cnt) > 0) && omap_obj->block &&
			(omap_obj->flags & OMAP_BO_TILED_MASK)) अणु
		*dma_addr = tiler_tsptr(omap_obj->block, orient, x, y);
		ret = 0;
	पूर्ण

	mutex_unlock(&omap_obj->lock);

	वापस ret;
पूर्ण

/* Get tiler stride क्रम the buffer (only valid क्रम 2d tiled buffers) */
पूर्णांक omap_gem_tiled_stride(काष्ठा drm_gem_object *obj, u32 orient)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	पूर्णांक ret = -EINVAL;
	अगर (omap_obj->flags & OMAP_BO_TILED_MASK)
		ret = tiler_stride(gem2fmt(omap_obj->flags), orient);
	वापस ret;
पूर्ण

/* अगर !remap, and we करोn't have pages backing, then fail, rather than
 * increasing the pin count (which we करोn't really करो yet anyways,
 * because we करोn't support swapping pages back out).  And 'remap'
 * might not be quite the right name, but I wanted to keep it working
 * similarly to omap_gem_pin().  Note though that mutex is not
 * aquired अगर !remap (because this can be called in atomic ctxt),
 * but probably omap_gem_unpin() should be changed to work in the
 * same way.  If !remap, a matching omap_gem_put_pages() call is not
 * required (and should not be made).
 */
पूर्णांक omap_gem_get_pages(काष्ठा drm_gem_object *obj, काष्ठा page ***pages,
		bool remap)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	पूर्णांक ret = 0;

	mutex_lock(&omap_obj->lock);

	अगर (remap) अणु
		ret = omap_gem_attach_pages(obj);
		अगर (ret)
			जाओ unlock;
	पूर्ण

	अगर (!omap_obj->pages) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	*pages = omap_obj->pages;

unlock:
	mutex_unlock(&omap_obj->lock);

	वापस ret;
पूर्ण

/* release pages when DMA no दीर्घer being perक्रमmed */
पूर्णांक omap_gem_put_pages(काष्ठा drm_gem_object *obj)
अणु
	/* करो something here अगर we dynamically attach/detach pages.. at
	 * least they would no दीर्घer need to be pinned अगर everyone has
	 * released the pages..
	 */
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
/*
 * Get kernel भव address क्रम CPU access.. this more or less only
 * exists क्रम omap_fbdev.
 */
व्योम *omap_gem_vaddr(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	व्योम *vaddr;
	पूर्णांक ret;

	mutex_lock(&omap_obj->lock);

	अगर (!omap_obj->vaddr) अणु
		ret = omap_gem_attach_pages(obj);
		अगर (ret) अणु
			vaddr = ERR_PTR(ret);
			जाओ unlock;
		पूर्ण

		omap_obj->vaddr = vmap(omap_obj->pages, obj->size >> PAGE_SHIFT,
				VM_MAP, pgprot_ग_लिखोcombine(PAGE_KERNEL));
	पूर्ण

	vaddr = omap_obj->vaddr;

unlock:
	mutex_unlock(&omap_obj->lock);
	वापस vaddr;
पूर्ण
#पूर्ण_अगर

/* -----------------------------------------------------------------------------
 * Power Management
 */

#अगर_घोषित CONFIG_PM
/* re-pin objects in DMM in resume path: */
पूर्णांक omap_gem_resume(काष्ठा drm_device *dev)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा omap_gem_object *omap_obj;
	पूर्णांक ret = 0;

	mutex_lock(&priv->list_lock);
	list_क्रम_each_entry(omap_obj, &priv->obj_list, mm_list) अणु
		अगर (omap_obj->block) अणु
			काष्ठा drm_gem_object *obj = &omap_obj->base;
			u32 npages = obj->size >> PAGE_SHIFT;

			WARN_ON(!omap_obj->pages);  /* this can't happen */
			ret = tiler_pin(omap_obj->block,
					omap_obj->pages, npages,
					omap_obj->roll, true);
			अगर (ret) अणु
				dev_err(dev->dev, "could not repin: %d\n", ret);
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण

करोne:
	mutex_unlock(&priv->list_lock);
	वापस ret;
पूर्ण
#पूर्ण_अगर

/* -----------------------------------------------------------------------------
 * DebugFS
 */

#अगर_घोषित CONFIG_DEBUG_FS
व्योम omap_gem_describe(काष्ठा drm_gem_object *obj, काष्ठा seq_file *m)
अणु
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);
	u64 off;

	off = drm_vma_node_start(&obj->vma_node);

	mutex_lock(&omap_obj->lock);

	seq_म_लिखो(m, "%08x: %2d (%2d) %08llx %pad (%2d) %p %4d",
			omap_obj->flags, obj->name, kref_पढ़ो(&obj->refcount),
			off, &omap_obj->dma_addr,
			refcount_पढ़ो(&omap_obj->dma_addr_cnt),
			omap_obj->vaddr, omap_obj->roll);

	अगर (omap_obj->flags & OMAP_BO_TILED_MASK) अणु
		seq_म_लिखो(m, " %dx%d", omap_obj->width, omap_obj->height);
		अगर (omap_obj->block) अणु
			काष्ठा tcm_area *area = &omap_obj->block->area;
			seq_म_लिखो(m, " (%dx%d, %dx%d)",
					area->p0.x, area->p0.y,
					area->p1.x, area->p1.y);
		पूर्ण
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, " %zu", obj->size);
	पूर्ण

	mutex_unlock(&omap_obj->lock);

	seq_म_लिखो(m, "\n");
पूर्ण

व्योम omap_gem_describe_objects(काष्ठा list_head *list, काष्ठा seq_file *m)
अणु
	काष्ठा omap_gem_object *omap_obj;
	पूर्णांक count = 0;
	माप_प्रकार size = 0;

	list_क्रम_each_entry(omap_obj, list, mm_list) अणु
		काष्ठा drm_gem_object *obj = &omap_obj->base;
		seq_म_लिखो(m, "   ");
		omap_gem_describe(obj, m);
		count++;
		size += obj->size;
	पूर्ण

	seq_म_लिखो(m, "Total %d objects, %zu bytes\n", count, size);
पूर्ण
#पूर्ण_अगर

/* -----------------------------------------------------------------------------
 * Conकाष्ठाor & Deकाष्ठाor
 */

अटल व्योम omap_gem_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_device *dev = obj->dev;
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा omap_gem_object *omap_obj = to_omap_bo(obj);

	omap_gem_evict(obj);

	mutex_lock(&priv->list_lock);
	list_del(&omap_obj->mm_list);
	mutex_unlock(&priv->list_lock);

	/*
	 * We own the sole reference to the object at this poपूर्णांक, but to keep
	 * lockdep happy, we must still take the omap_obj_lock to call
	 * omap_gem_detach_pages(). This should hardly make any dअगरference as
	 * there can't be any lock contention.
	 */
	mutex_lock(&omap_obj->lock);

	/* The object should not be pinned. */
	WARN_ON(refcount_पढ़ो(&omap_obj->dma_addr_cnt) > 0);

	अगर (omap_obj->pages) अणु
		अगर (omap_obj->flags & OMAP_BO_MEM_DMABUF)
			kमुक्त(omap_obj->pages);
		अन्यथा
			omap_gem_detach_pages(obj);
	पूर्ण

	अगर (omap_obj->flags & OMAP_BO_MEM_DMA_API) अणु
		dma_मुक्त_wc(dev->dev, obj->size, omap_obj->vaddr,
			    omap_obj->dma_addr);
	पूर्ण अन्यथा अगर (omap_obj->vaddr) अणु
		vunmap(omap_obj->vaddr);
	पूर्ण अन्यथा अगर (obj->import_attach) अणु
		drm_prime_gem_destroy(obj, omap_obj->sgt);
	पूर्ण

	mutex_unlock(&omap_obj->lock);

	drm_gem_object_release(obj);

	mutex_destroy(&omap_obj->lock);

	kमुक्त(omap_obj);
पूर्ण

अटल bool omap_gem_validate_flags(काष्ठा drm_device *dev, u32 flags)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;

	चयन (flags & OMAP_BO_CACHE_MASK) अणु
	हाल OMAP_BO_CACHED:
	हाल OMAP_BO_WC:
	हाल OMAP_BO_CACHE_MASK:
		अवरोध;

	शेष:
		वापस false;
	पूर्ण

	अगर (flags & OMAP_BO_TILED_MASK) अणु
		अगर (!priv->usergart)
			वापस false;

		चयन (flags & OMAP_BO_TILED_MASK) अणु
		हाल OMAP_BO_TILED_8:
		हाल OMAP_BO_TILED_16:
		हाल OMAP_BO_TILED_32:
			अवरोध;

		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा omap_gem_vm_ops = अणु
	.fault = omap_gem_fault,
	.खोलो = drm_gem_vm_खोलो,
	.बंद = drm_gem_vm_बंद,
पूर्ण;

अटल स्थिर काष्ठा drm_gem_object_funcs omap_gem_object_funcs = अणु
	.मुक्त = omap_gem_मुक्त_object,
	.export = omap_gem_prime_export,
	.vm_ops = &omap_gem_vm_ops,
पूर्ण;

/* GEM buffer object स्थिरructor */
काष्ठा drm_gem_object *omap_gem_new(काष्ठा drm_device *dev,
		जोड़ omap_gem_size gsize, u32 flags)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा omap_gem_object *omap_obj;
	काष्ठा drm_gem_object *obj;
	काष्ठा address_space *mapping;
	माप_प्रकार size;
	पूर्णांक ret;

	अगर (!omap_gem_validate_flags(dev, flags))
		वापस शून्य;

	/* Validate the flags and compute the memory and cache flags. */
	अगर (flags & OMAP_BO_TILED_MASK) अणु
		/*
		 * Tiled buffers are always shmem paged backed. When they are
		 * scanned out, they are remapped पूर्णांकo DMM/TILER.
		 */
		flags |= OMAP_BO_MEM_SHMEM;

		/*
		 * Currently करोn't allow cached buffers. There is some caching
		 * stuff that needs to be handled better.
		 */
		flags &= ~(OMAP_BO_CACHED|OMAP_BO_WC|OMAP_BO_UNCACHED);
		flags |= tiler_get_cpu_cache_flags();
	पूर्ण अन्यथा अगर ((flags & OMAP_BO_SCANOUT) && !priv->has_dmm) अणु
		/*
		 * If we करोn't have DMM, we must allocate scanout buffers
		 * from contiguous DMA memory.
		 */
		flags |= OMAP_BO_MEM_DMA_API;
	पूर्ण अन्यथा अगर (!(flags & OMAP_BO_MEM_DMABUF)) अणु
		/*
		 * All other buffers not backed by dma_buf are shmem-backed.
		 */
		flags |= OMAP_BO_MEM_SHMEM;
	पूर्ण

	/* Allocate the initialize the OMAP GEM object. */
	omap_obj = kzalloc(माप(*omap_obj), GFP_KERNEL);
	अगर (!omap_obj)
		वापस शून्य;

	obj = &omap_obj->base;
	omap_obj->flags = flags;
	mutex_init(&omap_obj->lock);

	अगर (flags & OMAP_BO_TILED_MASK) अणु
		/*
		 * For tiled buffers align dimensions to slot boundaries and
		 * calculate size based on aligned dimensions.
		 */
		tiler_align(gem2fmt(flags), &gsize.tiled.width,
			    &gsize.tiled.height);

		size = tiler_size(gem2fmt(flags), gsize.tiled.width,
				  gsize.tiled.height);

		omap_obj->width = gsize.tiled.width;
		omap_obj->height = gsize.tiled.height;
	पूर्ण अन्यथा अणु
		size = PAGE_ALIGN(gsize.bytes);
	पूर्ण

	obj->funcs = &omap_gem_object_funcs;

	/* Initialize the GEM object. */
	अगर (!(flags & OMAP_BO_MEM_SHMEM)) अणु
		drm_gem_निजी_object_init(dev, obj, size);
	पूर्ण अन्यथा अणु
		ret = drm_gem_object_init(dev, obj, size);
		अगर (ret)
			जाओ err_मुक्त;

		mapping = obj->filp->f_mapping;
		mapping_set_gfp_mask(mapping, GFP_USER | __GFP_DMA32);
	पूर्ण

	/* Allocate memory अगर needed. */
	अगर (flags & OMAP_BO_MEM_DMA_API) अणु
		omap_obj->vaddr = dma_alloc_wc(dev->dev, size,
					       &omap_obj->dma_addr,
					       GFP_KERNEL);
		अगर (!omap_obj->vaddr)
			जाओ err_release;
	पूर्ण

	mutex_lock(&priv->list_lock);
	list_add(&omap_obj->mm_list, &priv->obj_list);
	mutex_unlock(&priv->list_lock);

	वापस obj;

err_release:
	drm_gem_object_release(obj);
err_मुक्त:
	kमुक्त(omap_obj);
	वापस शून्य;
पूर्ण

काष्ठा drm_gem_object *omap_gem_new_dmabuf(काष्ठा drm_device *dev, माप_प्रकार size,
					   काष्ठा sg_table *sgt)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा omap_gem_object *omap_obj;
	काष्ठा drm_gem_object *obj;
	जोड़ omap_gem_size gsize;

	/* Without a DMM only physically contiguous buffers can be supported. */
	अगर (sgt->orig_nents != 1 && !priv->has_dmm)
		वापस ERR_PTR(-EINVAL);

	gsize.bytes = PAGE_ALIGN(size);
	obj = omap_gem_new(dev, gsize, OMAP_BO_MEM_DMABUF | OMAP_BO_WC);
	अगर (!obj)
		वापस ERR_PTR(-ENOMEM);

	omap_obj = to_omap_bo(obj);

	mutex_lock(&omap_obj->lock);

	omap_obj->sgt = sgt;

	अगर (sgt->orig_nents == 1) अणु
		omap_obj->dma_addr = sg_dma_address(sgt->sgl);
	पूर्ण अन्यथा अणु
		/* Create pages list from sgt */
		काष्ठा page **pages;
		अचिन्हित पूर्णांक npages;
		अचिन्हित पूर्णांक ret;

		npages = DIV_ROUND_UP(size, PAGE_SIZE);
		pages = kसुस्मृति(npages, माप(*pages), GFP_KERNEL);
		अगर (!pages) अणु
			omap_gem_मुक्त_object(obj);
			obj = ERR_PTR(-ENOMEM);
			जाओ करोne;
		पूर्ण

		omap_obj->pages = pages;
		ret = drm_prime_sg_to_page_array(sgt, pages, npages);
		अगर (ret) अणु
			omap_gem_मुक्त_object(obj);
			obj = ERR_PTR(-ENOMEM);
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	mutex_unlock(&omap_obj->lock);
	वापस obj;
पूर्ण

/* convenience method to स्थिरruct a GEM buffer object, and userspace handle */
पूर्णांक omap_gem_new_handle(काष्ठा drm_device *dev, काष्ठा drm_file *file,
		जोड़ omap_gem_size gsize, u32 flags, u32 *handle)
अणु
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	obj = omap_gem_new(dev, gsize, flags);
	अगर (!obj)
		वापस -ENOMEM;

	ret = drm_gem_handle_create(file, obj, handle);
	अगर (ret) अणु
		omap_gem_मुक्त_object(obj);
		वापस ret;
	पूर्ण

	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put(obj);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Init & Cleanup
 */

/* If DMM is used, we need to set some stuff up.. */
व्योम omap_gem_init(काष्ठा drm_device *dev)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा omap_drm_usergart *usergart;
	स्थिर क्रमागत tiler_fmt fmts[] = अणु
			TILFMT_8BIT, TILFMT_16BIT, TILFMT_32BIT
	पूर्ण;
	पूर्णांक i, j;

	अगर (!dmm_is_available()) अणु
		/* DMM only supported on OMAP4 and later, so this isn't fatal */
		dev_warn(dev->dev, "DMM not available, disable DMM support\n");
		वापस;
	पूर्ण

	usergart = kसुस्मृति(3, माप(*usergart), GFP_KERNEL);
	अगर (!usergart)
		वापस;

	/* reserve 4k aligned/wide regions क्रम userspace mappings: */
	क्रम (i = 0; i < ARRAY_SIZE(fmts); i++) अणु
		u16 h = 1, w = PAGE_SIZE >> i;

		tiler_align(fmts[i], &w, &h);
		/* note: since each region is 1 4kb page wide, and minimum
		 * number of rows, the height ends up being the same as the
		 * # of pages in the region
		 */
		usergart[i].height = h;
		usergart[i].height_shअगरt = ilog2(h);
		usergart[i].stride_pfn = tiler_stride(fmts[i], 0) >> PAGE_SHIFT;
		usergart[i].slot_shअगरt = ilog2((PAGE_SIZE / h) >> i);
		क्रम (j = 0; j < NUM_USERGART_ENTRIES; j++) अणु
			काष्ठा omap_drm_usergart_entry *entry;
			काष्ठा tiler_block *block;

			entry = &usergart[i].entry[j];
			block = tiler_reserve_2d(fmts[i], w, h, PAGE_SIZE);
			अगर (IS_ERR(block)) अणु
				dev_err(dev->dev,
						"reserve failed: %d, %d, %ld\n",
						i, j, PTR_ERR(block));
				वापस;
			पूर्ण
			entry->dma_addr = tiler_ssptr(block);
			entry->block = block;

			DBG("%d:%d: %dx%d: dma_addr=%pad stride=%d", i, j, w, h,
					&entry->dma_addr,
					usergart[i].stride_pfn << PAGE_SHIFT);
		पूर्ण
	पूर्ण

	priv->usergart = usergart;
	priv->has_dmm = true;
पूर्ण

व्योम omap_gem_deinit(काष्ठा drm_device *dev)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;

	/* I believe we can rely on there being no more outstanding GEM
	 * objects which could depend on usergart/dmm at this poपूर्णांक.
	 */
	kमुक्त(priv->usergart);
पूर्ण
