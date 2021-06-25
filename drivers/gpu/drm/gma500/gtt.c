<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007, Intel Corporation.
 * All Rights Reserved.
 *
 * Authors: Thomas Hellstrom <thomas-at-tungstengraphics.com>
 *	    Alan Cox <alan@linux.पूर्णांकel.com>
 */

#समावेश <linux/shmem_fs.h>

#समावेश <यंत्र/set_memory.h>

#समावेश "psb_drv.h"


/*
 *	GTT resource allocator - manage page mappings in GTT space
 */

/**
 *	psb_gtt_mask_pte	-	generate GTT pte entry
 *	@pfn: page number to encode
 *	@type: type of memory in the GTT
 *
 *	Set the GTT entry क्रम the appropriate memory type.
 */
अटल अंतरभूत uपूर्णांक32_t psb_gtt_mask_pte(uपूर्णांक32_t pfn, पूर्णांक type)
अणु
	uपूर्णांक32_t mask = PSB_PTE_VALID;

	/* Ensure we explode rather than put an invalid low mapping of
	   a high mapping page पूर्णांकo the gtt */
	BUG_ON(pfn & ~(0xFFFFFFFF >> PAGE_SHIFT));

	अगर (type & PSB_MMU_CACHED_MEMORY)
		mask |= PSB_PTE_CACHED;
	अगर (type & PSB_MMU_RO_MEMORY)
		mask |= PSB_PTE_RO;
	अगर (type & PSB_MMU_WO_MEMORY)
		mask |= PSB_PTE_WO;

	वापस (pfn << PAGE_SHIFT) | mask;
पूर्ण

/**
 *	psb_gtt_entry		-	find the GTT entries क्रम a gtt_range
 *	@dev: our DRM device
 *	@r: our GTT range
 *
 *	Given a gtt_range object वापस the GTT offset of the page table
 *	entries क्रम this gtt_range
 */
अटल u32 __iomem *psb_gtt_entry(काष्ठा drm_device *dev, काष्ठा gtt_range *r)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	अचिन्हित दीर्घ offset;

	offset = r->resource.start - dev_priv->gtt_mem->start;

	वापस dev_priv->gtt_map + (offset >> PAGE_SHIFT);
पूर्ण

/**
 *	psb_gtt_insert	-	put an object पूर्णांकo the GTT
 *	@dev: our DRM device
 *	@r: our GTT range
 *	@resume: on resume
 *
 *	Take our pपुनः_स्मृतिated GTT range and insert the GEM object पूर्णांकo
 *	the GTT. This is रक्षित via the gtt mutex which the caller
 *	must hold.
 */
अटल पूर्णांक psb_gtt_insert(काष्ठा drm_device *dev, काष्ठा gtt_range *r,
			  पूर्णांक resume)
अणु
	u32 __iomem *gtt_slot;
	u32 pte;
	काष्ठा page **pages;
	पूर्णांक i;

	अगर (r->pages == शून्य) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	WARN_ON(r->stolen);	/* refcount these maybe ? */

	gtt_slot = psb_gtt_entry(dev, r);
	pages = r->pages;

	अगर (!resume) अणु
		/* Make sure changes are visible to the GPU */
		set_pages_array_wc(pages, r->npage);
	पूर्ण

	/* Write our page entries पूर्णांकo the GTT itself */
	क्रम (i = 0; i < r->npage; i++) अणु
		pte = psb_gtt_mask_pte(page_to_pfn(r->pages[i]),
				       PSB_MMU_CACHED_MEMORY);
		ioग_लिखो32(pte, gtt_slot++);
	पूर्ण

	/* Make sure all the entries are set beक्रमe we वापस */
	ioपढ़ो32(gtt_slot - 1);

	वापस 0;
पूर्ण

/**
 *	psb_gtt_हटाओ	-	हटाओ an object from the GTT
 *	@dev: our DRM device
 *	@r: our GTT range
 *
 *	Remove a pपुनः_स्मृतिated GTT range from the GTT. Overग_लिखो all the
 *	page table entries with the dummy page. This is रक्षित via the gtt
 *	mutex which the caller must hold.
 */
अटल व्योम psb_gtt_हटाओ(काष्ठा drm_device *dev, काष्ठा gtt_range *r)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 __iomem *gtt_slot;
	u32 pte;
	पूर्णांक i;

	WARN_ON(r->stolen);

	gtt_slot = psb_gtt_entry(dev, r);
	pte = psb_gtt_mask_pte(page_to_pfn(dev_priv->scratch_page),
			       PSB_MMU_CACHED_MEMORY);

	क्रम (i = 0; i < r->npage; i++)
		ioग_लिखो32(pte, gtt_slot++);
	ioपढ़ो32(gtt_slot - 1);
	set_pages_array_wb(r->pages, r->npage);
पूर्ण

/**
 *	psb_gtt_attach_pages	-	attach and pin GEM pages
 *	@gt: the gtt range
 *
 *	Pin and build an in kernel list of the pages that back our GEM object.
 *	While we hold this the pages cannot be swapped out. This is रक्षित
 *	via the gtt mutex which the caller must hold.
 */
अटल पूर्णांक psb_gtt_attach_pages(काष्ठा gtt_range *gt)
अणु
	काष्ठा page **pages;

	WARN_ON(gt->pages);

	pages = drm_gem_get_pages(&gt->gem);
	अगर (IS_ERR(pages))
		वापस PTR_ERR(pages);

	gt->npage = gt->gem.size / PAGE_SIZE;
	gt->pages = pages;

	वापस 0;
पूर्ण

/**
 *	psb_gtt_detach_pages	-	attach and pin GEM pages
 *	@gt: the gtt range
 *
 *	Unकरो the effect of psb_gtt_attach_pages. At this poपूर्णांक the pages
 *	must have been हटाओd from the GTT as they could now be paged out
 *	and move bus address. This is रक्षित via the gtt mutex which the
 *	caller must hold.
 */
अटल व्योम psb_gtt_detach_pages(काष्ठा gtt_range *gt)
अणु
	drm_gem_put_pages(&gt->gem, gt->pages, true, false);
	gt->pages = शून्य;
पूर्ण

/**
 *	psb_gtt_pin		-	pin pages पूर्णांकo the GTT
 *	@gt: range to pin
 *
 *	Pin a set of pages पूर्णांकo the GTT. The pins are refcounted so that
 *	multiple pins need multiple unpins to unकरो.
 *
 *	Non GEM backed objects treat this as a no-op as they are always GTT
 *	backed objects.
 */
पूर्णांक psb_gtt_pin(काष्ठा gtt_range *gt)
अणु
	पूर्णांक ret = 0;
	काष्ठा drm_device *dev = gt->gem.dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 gpu_base = dev_priv->gtt.gatt_start;

	mutex_lock(&dev_priv->gtt_mutex);

	अगर (gt->in_gart == 0 && gt->stolen == 0) अणु
		ret = psb_gtt_attach_pages(gt);
		अगर (ret < 0)
			जाओ out;
		ret = psb_gtt_insert(dev, gt, 0);
		अगर (ret < 0) अणु
			psb_gtt_detach_pages(gt);
			जाओ out;
		पूर्ण
		psb_mmu_insert_pages(psb_mmu_get_शेष_pd(dev_priv->mmu),
				     gt->pages, (gpu_base + gt->offset),
				     gt->npage, 0, 0, PSB_MMU_CACHED_MEMORY);
	पूर्ण
	gt->in_gart++;
out:
	mutex_unlock(&dev_priv->gtt_mutex);
	वापस ret;
पूर्ण

/**
 *	psb_gtt_unpin		-	Drop a GTT pin requirement
 *	@gt: range to pin
 *
 *	Unकरोes the effect of psb_gtt_pin. On the last drop the GEM object
 *	will be हटाओd from the GTT which will also drop the page references
 *	and allow the VM to clean up or page stuff.
 *
 *	Non GEM backed objects treat this as a no-op as they are always GTT
 *	backed objects.
 */
व्योम psb_gtt_unpin(काष्ठा gtt_range *gt)
अणु
	काष्ठा drm_device *dev = gt->gem.dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 gpu_base = dev_priv->gtt.gatt_start;

	mutex_lock(&dev_priv->gtt_mutex);

	WARN_ON(!gt->in_gart);

	gt->in_gart--;
	अगर (gt->in_gart == 0 && gt->stolen == 0) अणु
		psb_mmu_हटाओ_pages(psb_mmu_get_शेष_pd(dev_priv->mmu),
				     (gpu_base + gt->offset), gt->npage, 0, 0);
		psb_gtt_हटाओ(dev, gt);
		psb_gtt_detach_pages(gt);
	पूर्ण

	mutex_unlock(&dev_priv->gtt_mutex);
पूर्ण

/*
 *	GTT resource allocator - allocate and manage GTT address space
 */

/**
 *	psb_gtt_alloc_range	-	allocate GTT address space
 *	@dev: Our DRM device
 *	@len: length (bytes) of address space required
 *	@name: resource name
 *	@backed: resource should be backed by stolen pages
 *	@align: requested alignment
 *
 *	Ask the kernel core to find us a suitable range of addresses
 *	to use क्रम a GTT mapping.
 *
 *	Returns a gtt_range काष्ठाure describing the object, or शून्य on
 *	error. On successful वापस the resource is both allocated and marked
 *	as in use.
 */
काष्ठा gtt_range *psb_gtt_alloc_range(काष्ठा drm_device *dev, पूर्णांक len,
				      स्थिर अक्षर *name, पूर्णांक backed, u32 align)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gtt_range *gt;
	काष्ठा resource *r = dev_priv->gtt_mem;
	पूर्णांक ret;
	अचिन्हित दीर्घ start, end;

	अगर (backed) अणु
		/* The start of the GTT is the stolen pages */
		start = r->start;
		end = r->start + dev_priv->gtt.stolen_size - 1;
	पूर्ण अन्यथा अणु
		/* The rest we will use क्रम GEM backed objects */
		start = r->start + dev_priv->gtt.stolen_size;
		end = r->end;
	पूर्ण

	gt = kzalloc(माप(काष्ठा gtt_range), GFP_KERNEL);
	अगर (gt == शून्य)
		वापस शून्य;
	gt->resource.name = name;
	gt->stolen = backed;
	gt->in_gart = backed;
	/* Ensure this is set क्रम non GEM objects */
	gt->gem.dev = dev;
	ret = allocate_resource(dev_priv->gtt_mem, &gt->resource,
				len, start, end, align, शून्य, शून्य);
	अगर (ret == 0) अणु
		gt->offset = gt->resource.start - r->start;
		वापस gt;
	पूर्ण
	kमुक्त(gt);
	वापस शून्य;
पूर्ण

/**
 *	psb_gtt_मुक्त_range	-	release GTT address space
 *	@dev: our DRM device
 *	@gt: a mapping created with psb_gtt_alloc_range
 *
 *	Release a resource that was allocated with psb_gtt_alloc_range. If the
 *	object has been pinned by mmap users we clean this up here currently.
 */
व्योम psb_gtt_मुक्त_range(काष्ठा drm_device *dev, काष्ठा gtt_range *gt)
अणु
	/* Unकरो the mmap pin अगर we are destroying the object */
	अगर (gt->mmapping) अणु
		psb_gtt_unpin(gt);
		gt->mmapping = 0;
	पूर्ण
	WARN_ON(gt->in_gart && !gt->stolen);
	release_resource(&gt->resource);
	kमुक्त(gt);
पूर्ण

अटल व्योम psb_gtt_alloc(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	init_rwsem(&dev_priv->gtt.sem);
पूर्ण

व्योम psb_gtt_takeकरोwn(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	अगर (dev_priv->gtt_map) अणु
		iounmap(dev_priv->gtt_map);
		dev_priv->gtt_map = शून्य;
	पूर्ण
	अगर (dev_priv->gtt_initialized) अणु
		pci_ग_लिखो_config_word(pdev, PSB_GMCH_CTRL,
				      dev_priv->gmch_ctrl);
		PSB_WVDC32(dev_priv->pge_ctl, PSB_PGETBL_CTL);
		(व्योम) PSB_RVDC32(PSB_PGETBL_CTL);
	पूर्ण
	अगर (dev_priv->vram_addr)
		iounmap(dev_priv->gtt_map);
पूर्ण

पूर्णांक psb_gtt_init(काष्ठा drm_device *dev, पूर्णांक resume)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	अचिन्हित gtt_pages;
	अचिन्हित दीर्घ stolen_size, vram_stolen_size;
	अचिन्हित i, num_pages;
	अचिन्हित pfn_base;
	काष्ठा psb_gtt *pg;

	पूर्णांक ret = 0;
	uपूर्णांक32_t pte;

	अगर (!resume) अणु
		mutex_init(&dev_priv->gtt_mutex);
		mutex_init(&dev_priv->mmap_mutex);
		psb_gtt_alloc(dev);
	पूर्ण

	pg = &dev_priv->gtt;

	/* Enable the GTT */
	pci_पढ़ो_config_word(pdev, PSB_GMCH_CTRL, &dev_priv->gmch_ctrl);
	pci_ग_लिखो_config_word(pdev, PSB_GMCH_CTRL,
			      dev_priv->gmch_ctrl | _PSB_GMCH_ENABLED);

	dev_priv->pge_ctl = PSB_RVDC32(PSB_PGETBL_CTL);
	PSB_WVDC32(dev_priv->pge_ctl | _PSB_PGETBL_ENABLED, PSB_PGETBL_CTL);
	(व्योम) PSB_RVDC32(PSB_PGETBL_CTL);

	/* The root resource we allocate address space from */
	dev_priv->gtt_initialized = 1;

	pg->gtt_phys_start = dev_priv->pge_ctl & PAGE_MASK;

	/*
	 *	The video mmu has a hw bug when accessing 0x0D0000000.
	 *	Make gatt start at 0x0e000,0000. This करोesn't actually
	 *	matter क्रम us but may करो अगर the video acceleration ever
	 *	माला_लो खोलोed up.
	 */
	pg->mmu_gatt_start = 0xE0000000;

	pg->gtt_start = pci_resource_start(pdev, PSB_GTT_RESOURCE);
	gtt_pages = pci_resource_len(pdev, PSB_GTT_RESOURCE)
								>> PAGE_SHIFT;
	/* CDV करोesn't report this. In which हाल the प्रणाली has 64 gtt pages */
	अगर (pg->gtt_start == 0 || gtt_pages == 0) अणु
		dev_dbg(dev->dev, "GTT PCI BAR not initialized.\n");
		gtt_pages = 64;
		pg->gtt_start = dev_priv->pge_ctl;
	पूर्ण

	pg->gatt_start = pci_resource_start(pdev, PSB_GATT_RESOURCE);
	pg->gatt_pages = pci_resource_len(pdev, PSB_GATT_RESOURCE)
								>> PAGE_SHIFT;
	dev_priv->gtt_mem = &pdev->resource[PSB_GATT_RESOURCE];

	अगर (pg->gatt_pages == 0 || pg->gatt_start == 0) अणु
		अटल काष्ठा resource fudge;	/* Preferably peppermपूर्णांक */
		/* This can occur on CDV प्रणालीs. Fudge it in this हाल.
		   We really करोn't care what imaginary space is being allocated
		   at this poपूर्णांक */
		dev_dbg(dev->dev, "GATT PCI BAR not initialized.\n");
		pg->gatt_start = 0x40000000;
		pg->gatt_pages = (128 * 1024 * 1024) >> PAGE_SHIFT;
		/* This is a little confusing but in fact the GTT is providing
		   a view from the GPU पूर्णांकo memory and not vice versa. As such
		   this is really allocating space that is not the same as the
		   CPU address space on CDV */
		fudge.start = 0x40000000;
		fudge.end = 0x40000000 + 128 * 1024 * 1024 - 1;
		fudge.name = "fudge";
		fudge.flags = IORESOURCE_MEM;
		dev_priv->gtt_mem = &fudge;
	पूर्ण

	pci_पढ़ो_config_dword(pdev, PSB_BSM, &dev_priv->stolen_base);
	vram_stolen_size = pg->gtt_phys_start - dev_priv->stolen_base
								- PAGE_SIZE;

	stolen_size = vram_stolen_size;

	dev_dbg(dev->dev, "Stolen memory base 0x%x, size %luK\n",
			dev_priv->stolen_base, vram_stolen_size / 1024);

	अगर (resume && (gtt_pages != pg->gtt_pages) &&
	    (stolen_size != pg->stolen_size)) अणु
		dev_err(dev->dev, "GTT resume error.\n");
		ret = -EINVAL;
		जाओ out_err;
	पूर्ण

	pg->gtt_pages = gtt_pages;
	pg->stolen_size = stolen_size;
	dev_priv->vram_stolen_size = vram_stolen_size;

	/*
	 *	Map the GTT and the stolen memory area
	 */
	अगर (!resume)
		dev_priv->gtt_map = ioremap(pg->gtt_phys_start,
						gtt_pages << PAGE_SHIFT);
	अगर (!dev_priv->gtt_map) अणु
		dev_err(dev->dev, "Failure to map gtt.\n");
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	अगर (!resume)
		dev_priv->vram_addr = ioremap_wc(dev_priv->stolen_base,
						 stolen_size);

	अगर (!dev_priv->vram_addr) अणु
		dev_err(dev->dev, "Failure to map stolen base.\n");
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	/*
	 * Insert vram stolen pages पूर्णांकo the GTT
	 */

	pfn_base = dev_priv->stolen_base >> PAGE_SHIFT;
	num_pages = vram_stolen_size >> PAGE_SHIFT;
	dev_dbg(dev->dev, "Set up %d stolen pages starting at 0x%08x, GTT offset %dK\n",
		num_pages, pfn_base << PAGE_SHIFT, 0);
	क्रम (i = 0; i < num_pages; ++i) अणु
		pte = psb_gtt_mask_pte(pfn_base + i, PSB_MMU_CACHED_MEMORY);
		ioग_लिखो32(pte, dev_priv->gtt_map + i);
	पूर्ण

	/*
	 * Init rest of GTT to the scratch page to aव्योम accidents or scribbles
	 */

	pfn_base = page_to_pfn(dev_priv->scratch_page);
	pte = psb_gtt_mask_pte(pfn_base, PSB_MMU_CACHED_MEMORY);
	क्रम (; i < gtt_pages; ++i)
		ioग_लिखो32(pte, dev_priv->gtt_map + i);

	(व्योम) ioपढ़ो32(dev_priv->gtt_map + i - 1);
	वापस 0;

out_err:
	psb_gtt_takeकरोwn(dev);
	वापस ret;
पूर्ण

पूर्णांक psb_gtt_restore(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा resource *r = dev_priv->gtt_mem->child;
	काष्ठा gtt_range *range;
	अचिन्हित पूर्णांक restored = 0, total = 0, size = 0;

	/* On resume, the gtt_mutex is alपढ़ोy initialized */
	mutex_lock(&dev_priv->gtt_mutex);
	psb_gtt_init(dev, 1);

	जबतक (r != शून्य) अणु
		range = container_of(r, काष्ठा gtt_range, resource);
		अगर (range->pages) अणु
			psb_gtt_insert(dev, range, 1);
			size += range->resource.end - range->resource.start;
			restored++;
		पूर्ण
		r = r->sibling;
		total++;
	पूर्ण
	mutex_unlock(&dev_priv->gtt_mutex);
	DRM_DEBUG_DRIVER("Restored %u of %u gtt ranges (%u KB)", restored,
			 total, (size / 1024));

	वापस 0;
पूर्ण
