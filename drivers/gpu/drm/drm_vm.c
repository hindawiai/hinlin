<शैली गुरु>
/*
 * \पile drm_vm.c
 * Memory mapping क्रम DRM
 *
 * \चuthor Rickard E. (Rik) Faith <faith@valinux.com>
 * \चuthor Gareth Hughes <gareth@valinux.com>
 */

/*
 * Created: Mon Jan  4 08:58:31 1999 by faith@valinux.com
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pgtable.h>

#अगर defined(__ia64__)
#समावेश <linux/efi.h>
#समावेश <linux/slab.h>
#पूर्ण_अगर
#समावेश <linux/mem_encrypt.h>


#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_internal.h"
#समावेश "drm_legacy.h"

काष्ठा drm_vma_entry अणु
	काष्ठा list_head head;
	काष्ठा vm_area_काष्ठा *vma;
	pid_t pid;
पूर्ण;

अटल व्योम drm_vm_खोलो(काष्ठा vm_area_काष्ठा *vma);
अटल व्योम drm_vm_बंद(काष्ठा vm_area_काष्ठा *vma);

अटल pgprot_t drm_io_prot(काष्ठा drm_local_map *map,
			    काष्ठा vm_area_काष्ठा *vma)
अणु
	pgprot_t पंचांगp = vm_get_page_prot(vma->vm_flags);

#अगर defined(__i386__) || defined(__x86_64__) || defined(__घातerpc__) || \
    defined(__mips__)
	अगर (map->type == _DRM_REGISTERS && !(map->flags & _DRM_WRITE_COMBINING))
		पंचांगp = pgprot_noncached(पंचांगp);
	अन्यथा
		पंचांगp = pgprot_ग_लिखोcombine(पंचांगp);
#या_अगर defined(__ia64__)
	अगर (efi_range_is_wc(vma->vm_start, vma->vm_end -
				    vma->vm_start))
		पंचांगp = pgprot_ग_लिखोcombine(पंचांगp);
	अन्यथा
		पंचांगp = pgprot_noncached(पंचांगp);
#या_अगर defined(__sparc__) || defined(__arm__)
	पंचांगp = pgprot_noncached(पंचांगp);
#पूर्ण_अगर
	वापस पंचांगp;
पूर्ण

अटल pgprot_t drm_dma_prot(uपूर्णांक32_t map_type, काष्ठा vm_area_काष्ठा *vma)
अणु
	pgprot_t पंचांगp = vm_get_page_prot(vma->vm_flags);

#अगर defined(__घातerpc__) && defined(CONFIG_NOT_COHERENT_CACHE)
	पंचांगp = pgprot_noncached_wc(पंचांगp);
#पूर्ण_अगर
	वापस पंचांगp;
पूर्ण

/*
 * \c fault method क्रम AGP भव memory.
 *
 * \param vma भव memory area.
 * \param address access address.
 * \लeturn poपूर्णांकer to the page काष्ठाure.
 *
 * Find the right map and अगर it's AGP memory find the real physical page to
 * map, get the page, increment the use count and वापस it.
 */
#अगर IS_ENABLED(CONFIG_AGP)
अटल vm_fault_t drm_vm_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा drm_file *priv = vma->vm_file->निजी_data;
	काष्ठा drm_device *dev = priv->minor->dev;
	काष्ठा drm_local_map *map = शून्य;
	काष्ठा drm_map_list *r_list;
	काष्ठा drm_hash_item *hash;

	/*
	 * Find the right map
	 */
	अगर (!dev->agp)
		जाओ vm_fault_error;

	अगर (!dev->agp || !dev->agp->cant_use_aperture)
		जाओ vm_fault_error;

	अगर (drm_ht_find_item(&dev->map_hash, vma->vm_pgoff, &hash))
		जाओ vm_fault_error;

	r_list = drm_hash_entry(hash, काष्ठा drm_map_list, hash);
	map = r_list->map;

	अगर (map && map->type == _DRM_AGP) अणु
		/*
		 * Using vm_pgoff as a selector क्रमces us to use this unusual
		 * addressing scheme.
		 */
		resource_माप_प्रकार offset = vmf->address - vma->vm_start;
		resource_माप_प्रकार baddr = map->offset + offset;
		काष्ठा drm_agp_mem *agpmem;
		काष्ठा page *page;

#अगर_घोषित __alpha__
		/*
		 * Adjust to a bus-relative address
		 */
		baddr -= dev->hose->mem_space->start;
#पूर्ण_अगर

		/*
		 * It's AGP memory - find the real physical page to map
		 */
		list_क्रम_each_entry(agpmem, &dev->agp->memory, head) अणु
			अगर (agpmem->bound <= baddr &&
			    agpmem->bound + agpmem->pages * PAGE_SIZE > baddr)
				अवरोध;
		पूर्ण

		अगर (&agpmem->head == &dev->agp->memory)
			जाओ vm_fault_error;

		/*
		 * Get the page, inc the use count, and वापस it
		 */
		offset = (baddr - agpmem->bound) >> PAGE_SHIFT;
		page = agpmem->memory->pages[offset];
		get_page(page);
		vmf->page = page;

		DRM_DEBUG
		    ("baddr = 0x%llx page = 0x%p, offset = 0x%llx, count=%d\n",
		     (अचिन्हित दीर्घ दीर्घ)baddr,
		     agpmem->memory->pages[offset],
		     (अचिन्हित दीर्घ दीर्घ)offset,
		     page_count(page));
		वापस 0;
	पूर्ण
vm_fault_error:
	वापस VM_FAULT_SIGBUS;	/* Disallow mremap */
पूर्ण
#अन्यथा
अटल vm_fault_t drm_vm_fault(काष्ठा vm_fault *vmf)
अणु
	वापस VM_FAULT_SIGBUS;
पूर्ण
#पूर्ण_अगर

/*
 * \c nopage method क्रम shared भव memory.
 *
 * \param vma भव memory area.
 * \param address access address.
 * \लeturn poपूर्णांकer to the page काष्ठाure.
 *
 * Get the mapping, find the real physical page to map, get the page, and
 * वापस it.
 */
अटल vm_fault_t drm_vm_shm_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा drm_local_map *map = vma->vm_निजी_data;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ i;
	काष्ठा page *page;

	अगर (!map)
		वापस VM_FAULT_SIGBUS;	/* Nothing allocated */

	offset = vmf->address - vma->vm_start;
	i = (अचिन्हित दीर्घ)map->handle + offset;
	page = vदो_स्मृति_to_page((व्योम *)i);
	अगर (!page)
		वापस VM_FAULT_SIGBUS;
	get_page(page);
	vmf->page = page;

	DRM_DEBUG("shm_fault 0x%lx\n", offset);
	वापस 0;
पूर्ण

/*
 * \c बंद method क्रम shared भव memory.
 *
 * \param vma भव memory area.
 *
 * Deletes map inक्रमmation अगर we are the last
 * person to बंद a mapping and it's not in the global maplist.
 */
अटल व्योम drm_vm_shm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_file *priv = vma->vm_file->निजी_data;
	काष्ठा drm_device *dev = priv->minor->dev;
	काष्ठा drm_vma_entry *pt, *temp;
	काष्ठा drm_local_map *map;
	काष्ठा drm_map_list *r_list;
	पूर्णांक found_maps = 0;

	DRM_DEBUG("0x%08lx,0x%08lx\n",
		  vma->vm_start, vma->vm_end - vma->vm_start);

	map = vma->vm_निजी_data;

	mutex_lock(&dev->काष्ठा_mutex);
	list_क्रम_each_entry_safe(pt, temp, &dev->vmalist, head) अणु
		अगर (pt->vma->vm_निजी_data == map)
			found_maps++;
		अगर (pt->vma == vma) अणु
			list_del(&pt->head);
			kमुक्त(pt);
		पूर्ण
	पूर्ण

	/* We were the only map that was found */
	अगर (found_maps == 1 && map->flags & _DRM_REMOVABLE) अणु
		/* Check to see अगर we are in the maplist, अगर we are not, then
		 * we delete this mappings inक्रमmation.
		 */
		found_maps = 0;
		list_क्रम_each_entry(r_list, &dev->maplist, head) अणु
			अगर (r_list->map == map)
				found_maps++;
		पूर्ण

		अगर (!found_maps) अणु
			चयन (map->type) अणु
			हाल _DRM_REGISTERS:
			हाल _DRM_FRAME_BUFFER:
				arch_phys_wc_del(map->mtrr);
				iounmap(map->handle);
				अवरोध;
			हाल _DRM_SHM:
				vमुक्त(map->handle);
				अवरोध;
			हाल _DRM_AGP:
			हाल _DRM_SCATTER_GATHER:
				अवरोध;
			हाल _DRM_CONSISTENT:
				dma_मुक्त_coherent(dev->dev,
						  map->size,
						  map->handle,
						  map->offset);
				अवरोध;
			पूर्ण
			kमुक्त(map);
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->काष्ठा_mutex);
पूर्ण

/*
 * \c fault method क्रम DMA भव memory.
 *
 * \param address access address.
 * \लeturn poपूर्णांकer to the page काष्ठाure.
 *
 * Determine the page number from the page offset and get it from drm_device_dma::pagelist.
 */
अटल vm_fault_t drm_vm_dma_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा drm_file *priv = vma->vm_file->निजी_data;
	काष्ठा drm_device *dev = priv->minor->dev;
	काष्ठा drm_device_dma *dma = dev->dma;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ page_nr;
	काष्ठा page *page;

	अगर (!dma)
		वापस VM_FAULT_SIGBUS;	/* Error */
	अगर (!dma->pagelist)
		वापस VM_FAULT_SIGBUS;	/* Nothing allocated */

	offset = vmf->address - vma->vm_start;
					/* vm_[pg]off[set] should be 0 */
	page_nr = offset >> PAGE_SHIFT; /* page_nr could just be vmf->pgoff */
	page = virt_to_page((व्योम *)dma->pagelist[page_nr]);

	get_page(page);
	vmf->page = page;

	DRM_DEBUG("dma_fault 0x%lx (page %lu)\n", offset, page_nr);
	वापस 0;
पूर्ण

/*
 * \c fault method क्रम scatter-gather भव memory.
 *
 * \param address access address.
 * \लeturn poपूर्णांकer to the page काष्ठाure.
 *
 * Determine the map offset from the page offset and get it from drm_sg_mem::pagelist.
 */
अटल vm_fault_t drm_vm_sg_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा drm_local_map *map = vma->vm_निजी_data;
	काष्ठा drm_file *priv = vma->vm_file->निजी_data;
	काष्ठा drm_device *dev = priv->minor->dev;
	काष्ठा drm_sg_mem *entry = dev->sg;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ map_offset;
	अचिन्हित दीर्घ page_offset;
	काष्ठा page *page;

	अगर (!entry)
		वापस VM_FAULT_SIGBUS;	/* Error */
	अगर (!entry->pagelist)
		वापस VM_FAULT_SIGBUS;	/* Nothing allocated */

	offset = vmf->address - vma->vm_start;
	map_offset = map->offset - (अचिन्हित दीर्घ)dev->sg->भव;
	page_offset = (offset >> PAGE_SHIFT) + (map_offset >> PAGE_SHIFT);
	page = entry->pagelist[page_offset];
	get_page(page);
	vmf->page = page;

	वापस 0;
पूर्ण

/** AGP भव memory operations */
अटल स्थिर काष्ठा vm_operations_काष्ठा drm_vm_ops = अणु
	.fault = drm_vm_fault,
	.खोलो = drm_vm_खोलो,
	.बंद = drm_vm_बंद,
पूर्ण;

/** Shared भव memory operations */
अटल स्थिर काष्ठा vm_operations_काष्ठा drm_vm_shm_ops = अणु
	.fault = drm_vm_shm_fault,
	.खोलो = drm_vm_खोलो,
	.बंद = drm_vm_shm_बंद,
पूर्ण;

/** DMA भव memory operations */
अटल स्थिर काष्ठा vm_operations_काष्ठा drm_vm_dma_ops = अणु
	.fault = drm_vm_dma_fault,
	.खोलो = drm_vm_खोलो,
	.बंद = drm_vm_बंद,
पूर्ण;

/** Scatter-gather भव memory operations */
अटल स्थिर काष्ठा vm_operations_काष्ठा drm_vm_sg_ops = अणु
	.fault = drm_vm_sg_fault,
	.खोलो = drm_vm_खोलो,
	.बंद = drm_vm_बंद,
पूर्ण;

अटल व्योम drm_vm_खोलो_locked(काष्ठा drm_device *dev,
			       काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_vma_entry *vma_entry;

	DRM_DEBUG("0x%08lx,0x%08lx\n",
		  vma->vm_start, vma->vm_end - vma->vm_start);

	vma_entry = kदो_स्मृति(माप(*vma_entry), GFP_KERNEL);
	अगर (vma_entry) अणु
		vma_entry->vma = vma;
		vma_entry->pid = current->pid;
		list_add(&vma_entry->head, &dev->vmalist);
	पूर्ण
पूर्ण

अटल व्योम drm_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_file *priv = vma->vm_file->निजी_data;
	काष्ठा drm_device *dev = priv->minor->dev;

	mutex_lock(&dev->काष्ठा_mutex);
	drm_vm_खोलो_locked(dev, vma);
	mutex_unlock(&dev->काष्ठा_mutex);
पूर्ण

अटल व्योम drm_vm_बंद_locked(काष्ठा drm_device *dev,
				काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_vma_entry *pt, *temp;

	DRM_DEBUG("0x%08lx,0x%08lx\n",
		  vma->vm_start, vma->vm_end - vma->vm_start);

	list_क्रम_each_entry_safe(pt, temp, &dev->vmalist, head) अणु
		अगर (pt->vma == vma) अणु
			list_del(&pt->head);
			kमुक्त(pt);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * \c बंद method क्रम all भव memory types.
 *
 * \param vma भव memory area.
 *
 * Search the \p vma निजी data entry in drm_device::vmalist, unlink it, and
 * मुक्त it.
 */
अटल व्योम drm_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_file *priv = vma->vm_file->निजी_data;
	काष्ठा drm_device *dev = priv->minor->dev;

	mutex_lock(&dev->काष्ठा_mutex);
	drm_vm_बंद_locked(dev, vma);
	mutex_unlock(&dev->काष्ठा_mutex);
पूर्ण

/*
 * mmap DMA memory.
 *
 * \param file_priv DRM file निजी.
 * \param vma भव memory area.
 * \लeturn zero on success or a negative number on failure.
 *
 * Sets the भव memory area operations काष्ठाure to vm_dma_ops, the file
 * poपूर्णांकer, and calls vm_खोलो().
 */
अटल पूर्णांक drm_mmap_dma(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_file *priv = filp->निजी_data;
	काष्ठा drm_device *dev;
	काष्ठा drm_device_dma *dma;
	अचिन्हित दीर्घ length = vma->vm_end - vma->vm_start;

	dev = priv->minor->dev;
	dma = dev->dma;
	DRM_DEBUG("start = 0x%lx, end = 0x%lx, page offset = 0x%lx\n",
		  vma->vm_start, vma->vm_end, vma->vm_pgoff);

	/* Length must match exact page count */
	अगर (!dma || (length >> PAGE_SHIFT) != dma->page_count) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (!capable(CAP_SYS_ADMIN) &&
	    (dma->flags & _DRM_DMA_USE_PCI_RO)) अणु
		vma->vm_flags &= ~(VM_WRITE | VM_MAYWRITE);
#अगर defined(__i386__) || defined(__x86_64__)
		pgprot_val(vma->vm_page_prot) &= ~_PAGE_RW;
#अन्यथा
		/* Ye gads this is ugly.  With more thought
		   we could move this up higher and use
		   `protection_map' instead.  */
		vma->vm_page_prot =
		    __pgprot(pte_val
			     (pte_wrprotect
			      (__pte(pgprot_val(vma->vm_page_prot)))));
#पूर्ण_अगर
	पूर्ण

	vma->vm_ops = &drm_vm_dma_ops;

	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;

	drm_vm_खोलो_locked(dev, vma);
	वापस 0;
पूर्ण

अटल resource_माप_प्रकार drm_core_get_reg_ofs(काष्ठा drm_device *dev)
अणु
#अगर_घोषित __alpha__
	वापस dev->hose->dense_mem_base;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*
 * mmap DMA memory.
 *
 * \param file_priv DRM file निजी.
 * \param vma भव memory area.
 * \लeturn zero on success or a negative number on failure.
 *
 * If the भव memory area has no offset associated with it then it's a DMA
 * area, so calls mmap_dma(). Otherwise searches the map in drm_device::maplist,
 * checks that the restricted flag is not set, sets the भव memory operations
 * according to the mapping type and remaps the pages. Finally sets the file
 * poपूर्णांकer and calls vm_खोलो().
 */
अटल पूर्णांक drm_mmap_locked(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_file *priv = filp->निजी_data;
	काष्ठा drm_device *dev = priv->minor->dev;
	काष्ठा drm_local_map *map = शून्य;
	resource_माप_प्रकार offset = 0;
	काष्ठा drm_hash_item *hash;

	DRM_DEBUG("start = 0x%lx, end = 0x%lx, page offset = 0x%lx\n",
		  vma->vm_start, vma->vm_end, vma->vm_pgoff);

	अगर (!priv->authenticated)
		वापस -EACCES;

	/* We check क्रम "dma". On Apple's UniNorth, it's valid to have
	 * the AGP mapped at physical address 0
	 * --BenH.
	 */
	अगर (!vma->vm_pgoff
#अगर IS_ENABLED(CONFIG_AGP)
	    && (!dev->agp
		|| dev->agp->agp_info.device->venकरोr != PCI_VENDOR_ID_APPLE)
#पूर्ण_अगर
	    )
		वापस drm_mmap_dma(filp, vma);

	अगर (drm_ht_find_item(&dev->map_hash, vma->vm_pgoff, &hash)) अणु
		DRM_ERROR("Could not find map\n");
		वापस -EINVAL;
	पूर्ण

	map = drm_hash_entry(hash, काष्ठा drm_map_list, hash)->map;
	अगर (!map || ((map->flags & _DRM_RESTRICTED) && !capable(CAP_SYS_ADMIN)))
		वापस -EPERM;

	/* Check क्रम valid size. */
	अगर (map->size < vma->vm_end - vma->vm_start)
		वापस -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN) && (map->flags & _DRM_READ_ONLY)) अणु
		vma->vm_flags &= ~(VM_WRITE | VM_MAYWRITE);
#अगर defined(__i386__) || defined(__x86_64__)
		pgprot_val(vma->vm_page_prot) &= ~_PAGE_RW;
#अन्यथा
		/* Ye gads this is ugly.  With more thought
		   we could move this up higher and use
		   `protection_map' instead.  */
		vma->vm_page_prot =
		    __pgprot(pte_val
			     (pte_wrprotect
			      (__pte(pgprot_val(vma->vm_page_prot)))));
#पूर्ण_अगर
	पूर्ण

	चयन (map->type) अणु
#अगर !defined(__arm__)
	हाल _DRM_AGP:
		अगर (dev->agp && dev->agp->cant_use_aperture) अणु
			/*
			 * On some platक्रमms we can't talk to bus dma address from the CPU, so क्रम
			 * memory of type DRM_AGP, we'll deal with sorting out the real physical
			 * pages and mappings in fault()
			 */
#अगर defined(__घातerpc__)
			vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
#पूर्ण_अगर
			vma->vm_ops = &drm_vm_ops;
			अवरोध;
		पूर्ण
		fallthrough;	/* to _DRM_FRAME_BUFFER... */
#पूर्ण_अगर
	हाल _DRM_FRAME_BUFFER:
	हाल _DRM_REGISTERS:
		offset = drm_core_get_reg_ofs(dev);
		vma->vm_page_prot = drm_io_prot(map, vma);
		अगर (io_remap_pfn_range(vma, vma->vm_start,
				       (map->offset + offset) >> PAGE_SHIFT,
				       vma->vm_end - vma->vm_start,
				       vma->vm_page_prot))
			वापस -EAGAIN;
		DRM_DEBUG("   Type = %d; start = 0x%lx, end = 0x%lx,"
			  " offset = 0x%llx\n",
			  map->type,
			  vma->vm_start, vma->vm_end, (अचिन्हित दीर्घ दीर्घ)(map->offset + offset));

		vma->vm_ops = &drm_vm_ops;
		अवरोध;
	हाल _DRM_CONSISTENT:
		/* Consistent memory is really like shared memory. But
		 * it's allocated in a dअगरferent way, so aव्योम fault */
		अगर (remap_pfn_range(vma, vma->vm_start,
		    page_to_pfn(virt_to_page(map->handle)),
		    vma->vm_end - vma->vm_start, vma->vm_page_prot))
			वापस -EAGAIN;
		vma->vm_page_prot = drm_dma_prot(map->type, vma);
		fallthrough;	/* to _DRM_SHM */
	हाल _DRM_SHM:
		vma->vm_ops = &drm_vm_shm_ops;
		vma->vm_निजी_data = (व्योम *)map;
		अवरोध;
	हाल _DRM_SCATTER_GATHER:
		vma->vm_ops = &drm_vm_sg_ops;
		vma->vm_निजी_data = (व्योम *)map;
		vma->vm_page_prot = drm_dma_prot(map->type, vma);
		अवरोध;
	शेष:
		वापस -EINVAL;	/* This should never happen. */
	पूर्ण
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;

	drm_vm_खोलो_locked(dev, vma);
	वापस 0;
पूर्ण

पूर्णांक drm_legacy_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_file *priv = filp->निजी_data;
	काष्ठा drm_device *dev = priv->minor->dev;
	पूर्णांक ret;

	अगर (drm_dev_is_unplugged(dev))
		वापस -ENODEV;

	mutex_lock(&dev->काष्ठा_mutex);
	ret = drm_mmap_locked(filp, vma);
	mutex_unlock(&dev->काष्ठा_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_legacy_mmap);

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
व्योम drm_legacy_vma_flush(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_vma_entry *vma, *vma_temp;

	/* Clear vma list (only needed क्रम legacy drivers) */
	list_क्रम_each_entry_safe(vma, vma_temp, &dev->vmalist, head) अणु
		list_del(&vma->head);
		kमुक्त(vma);
	पूर्ण
पूर्ण
#पूर्ण_अगर
