<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */

#समावेश <drm/radeon_drm.h>
#समावेश "radeon.h"
#समावेश "radeon_trace.h"

/*
 * GPUVM
 * GPUVM is similar to the legacy gart on older asics, however
 * rather than there being a single global gart table
 * क्रम the entire GPU, there are multiple VM page tables active
 * at any given समय.  The VM page tables can contain a mix
 * vram pages and प्रणाली memory pages and प्रणाली memory pages
 * can be mapped as snooped (cached प्रणाली pages) or unsnooped
 * (uncached प्रणाली pages).
 * Each VM has an ID associated with it and there is a page table
 * associated with each VMID.  When execting a command buffer,
 * the kernel tells the the ring what VMID to use क्रम that command
 * buffer.  VMIDs are allocated dynamically as commands are submitted.
 * The userspace drivers मुख्यtain their own address space and the kernel
 * sets up their pages tables accordingly when they submit their
 * command buffers and a VMID is asचिन्हित.
 * Cayman/Trinity support up to 8 active VMs at any given समय;
 * SI supports 16.
 */

/**
 * radeon_vm_num_pde - वापस the number of page directory entries
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Calculate the number of page directory entries (cayman+).
 */
अटल अचिन्हित radeon_vm_num_pdes(काष्ठा radeon_device *rdev)
अणु
	वापस rdev->vm_manager.max_pfn >> radeon_vm_block_size;
पूर्ण

/**
 * radeon_vm_directory_size - वापसs the size of the page directory in bytes
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Calculate the size of the page directory in bytes (cayman+).
 */
अटल अचिन्हित radeon_vm_directory_size(काष्ठा radeon_device *rdev)
अणु
	वापस RADEON_GPU_PAGE_ALIGN(radeon_vm_num_pdes(rdev) * 8);
पूर्ण

/**
 * radeon_vm_manager_init - init the vm manager
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Init the vm manager (cayman+).
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक radeon_vm_manager_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->vm_manager.enabled) अणु
		r = radeon_asic_vm_init(rdev);
		अगर (r)
			वापस r;

		rdev->vm_manager.enabled = true;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * radeon_vm_manager_fini - tear करोwn the vm manager
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Tear करोwn the VM manager (cayman+).
 */
व्योम radeon_vm_manager_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	अगर (!rdev->vm_manager.enabled)
		वापस;

	क्रम (i = 0; i < RADEON_NUM_VM; ++i)
		radeon_fence_unref(&rdev->vm_manager.active[i]);
	radeon_asic_vm_fini(rdev);
	rdev->vm_manager.enabled = false;
पूर्ण

/**
 * radeon_vm_get_bos - add the vm BOs to a validation list
 *
 * @rdev: radeon_device poपूर्णांकer
 * @vm: vm providing the BOs
 * @head: head of validation list
 *
 * Add the page directory to the list of BOs to
 * validate क्रम command submission (cayman+).
 */
काष्ठा radeon_bo_list *radeon_vm_get_bos(काष्ठा radeon_device *rdev,
					  काष्ठा radeon_vm *vm,
					  काष्ठा list_head *head)
अणु
	काष्ठा radeon_bo_list *list;
	अचिन्हित i, idx;

	list = kvदो_स्मृति_array(vm->max_pde_used + 2,
			     माप(काष्ठा radeon_bo_list), GFP_KERNEL);
	अगर (!list)
		वापस शून्य;

	/* add the vm page table to the list */
	list[0].robj = vm->page_directory;
	list[0].preferred_करोमुख्यs = RADEON_GEM_DOMAIN_VRAM;
	list[0].allowed_करोमुख्यs = RADEON_GEM_DOMAIN_VRAM;
	list[0].tv.bo = &vm->page_directory->tbo;
	list[0].tv.num_shared = 1;
	list[0].tiling_flags = 0;
	list_add(&list[0].tv.head, head);

	क्रम (i = 0, idx = 1; i <= vm->max_pde_used; i++) अणु
		अगर (!vm->page_tables[i].bo)
			जारी;

		list[idx].robj = vm->page_tables[i].bo;
		list[idx].preferred_करोमुख्यs = RADEON_GEM_DOMAIN_VRAM;
		list[idx].allowed_करोमुख्यs = RADEON_GEM_DOMAIN_VRAM;
		list[idx].tv.bo = &list[idx].robj->tbo;
		list[idx].tv.num_shared = 1;
		list[idx].tiling_flags = 0;
		list_add(&list[idx++].tv.head, head);
	पूर्ण

	वापस list;
पूर्ण

/**
 * radeon_vm_grab_id - allocate the next मुक्त VMID
 *
 * @rdev: radeon_device poपूर्णांकer
 * @vm: vm to allocate id क्रम
 * @ring: ring we want to submit job to
 *
 * Allocate an id क्रम the vm (cayman+).
 * Returns the fence we need to sync to (अगर any).
 *
 * Global and local mutex must be locked!
 */
काष्ठा radeon_fence *radeon_vm_grab_id(काष्ठा radeon_device *rdev,
				       काष्ठा radeon_vm *vm, पूर्णांक ring)
अणु
	काष्ठा radeon_fence *best[RADEON_NUM_RINGS] = अणुपूर्ण;
	काष्ठा radeon_vm_id *vm_id = &vm->ids[ring];

	अचिन्हित choices[2] = अणुपूर्ण;
	अचिन्हित i;

	/* check अगर the id is still valid */
	अगर (vm_id->id && vm_id->last_id_use &&
	    vm_id->last_id_use == rdev->vm_manager.active[vm_id->id])
		वापस शून्य;

	/* we definitely need to flush */
	vm_id->pd_gpu_addr = ~0ll;

	/* skip over VMID 0, since it is the प्रणाली VM */
	क्रम (i = 1; i < rdev->vm_manager.nvm; ++i) अणु
		काष्ठा radeon_fence *fence = rdev->vm_manager.active[i];

		अगर (fence == शून्य) अणु
			/* found a मुक्त one */
			vm_id->id = i;
			trace_radeon_vm_grab_id(i, ring);
			वापस शून्य;
		पूर्ण

		अगर (radeon_fence_is_earlier(fence, best[fence->ring])) अणु
			best[fence->ring] = fence;
			choices[fence->ring == ring ? 0 : 1] = i;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 2; ++i) अणु
		अगर (choices[i]) अणु
			vm_id->id = choices[i];
			trace_radeon_vm_grab_id(choices[i], ring);
			वापस rdev->vm_manager.active[choices[i]];
		पूर्ण
	पूर्ण

	/* should never happen */
	BUG();
	वापस शून्य;
पूर्ण

/**
 * radeon_vm_flush - hardware flush the vm
 *
 * @rdev: radeon_device poपूर्णांकer
 * @vm: vm we want to flush
 * @ring: ring to use क्रम flush
 * @updates: last vm update that is रुकोed क्रम
 *
 * Flush the vm (cayman+).
 *
 * Global and local mutex must be locked!
 */
व्योम radeon_vm_flush(काष्ठा radeon_device *rdev,
		     काष्ठा radeon_vm *vm,
		     पूर्णांक ring, काष्ठा radeon_fence *updates)
अणु
	uपूर्णांक64_t pd_addr = radeon_bo_gpu_offset(vm->page_directory);
	काष्ठा radeon_vm_id *vm_id = &vm->ids[ring];

	अगर (pd_addr != vm_id->pd_gpu_addr || !vm_id->flushed_updates ||
	    radeon_fence_is_earlier(vm_id->flushed_updates, updates)) अणु

		trace_radeon_vm_flush(pd_addr, ring, vm->ids[ring].id);
		radeon_fence_unref(&vm_id->flushed_updates);
		vm_id->flushed_updates = radeon_fence_ref(updates);
		vm_id->pd_gpu_addr = pd_addr;
		radeon_ring_vm_flush(rdev, &rdev->ring[ring],
				     vm_id->id, vm_id->pd_gpu_addr);

	पूर्ण
पूर्ण

/**
 * radeon_vm_fence - remember fence क्रम vm
 *
 * @rdev: radeon_device poपूर्णांकer
 * @vm: vm we want to fence
 * @fence: fence to remember
 *
 * Fence the vm (cayman+).
 * Set the fence used to protect page table and id.
 *
 * Global and local mutex must be locked!
 */
व्योम radeon_vm_fence(काष्ठा radeon_device *rdev,
		     काष्ठा radeon_vm *vm,
		     काष्ठा radeon_fence *fence)
अणु
	अचिन्हित vm_id = vm->ids[fence->ring].id;

	radeon_fence_unref(&rdev->vm_manager.active[vm_id]);
	rdev->vm_manager.active[vm_id] = radeon_fence_ref(fence);

	radeon_fence_unref(&vm->ids[fence->ring].last_id_use);
	vm->ids[fence->ring].last_id_use = radeon_fence_ref(fence);
पूर्ण

/**
 * radeon_vm_bo_find - find the bo_va क्रम a specअगरic vm & bo
 *
 * @vm: requested vm
 * @bo: requested buffer object
 *
 * Find @bo inside the requested vm (cayman+).
 * Search inside the @bos vm list क्रम the requested vm
 * Returns the found bo_va or शून्य अगर none is found
 *
 * Object has to be reserved!
 */
काष्ठा radeon_bo_va *radeon_vm_bo_find(काष्ठा radeon_vm *vm,
				       काष्ठा radeon_bo *bo)
अणु
	काष्ठा radeon_bo_va *bo_va;

	list_क्रम_each_entry(bo_va, &bo->va, bo_list) अणु
		अगर (bo_va->vm == vm)
			वापस bo_va;

	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * radeon_vm_bo_add - add a bo to a specअगरic vm
 *
 * @rdev: radeon_device poपूर्णांकer
 * @vm: requested vm
 * @bo: radeon buffer object
 *
 * Add @bo पूर्णांकo the requested vm (cayman+).
 * Add @bo to the list of bos associated with the vm
 * Returns newly added bo_va or शून्य क्रम failure
 *
 * Object has to be reserved!
 */
काष्ठा radeon_bo_va *radeon_vm_bo_add(काष्ठा radeon_device *rdev,
				      काष्ठा radeon_vm *vm,
				      काष्ठा radeon_bo *bo)
अणु
	काष्ठा radeon_bo_va *bo_va;

	bo_va = kzalloc(माप(काष्ठा radeon_bo_va), GFP_KERNEL);
	अगर (bo_va == शून्य)
		वापस शून्य;

	bo_va->vm = vm;
	bo_va->bo = bo;
	bo_va->it.start = 0;
	bo_va->it.last = 0;
	bo_va->flags = 0;
	bo_va->ref_count = 1;
	INIT_LIST_HEAD(&bo_va->bo_list);
	INIT_LIST_HEAD(&bo_va->vm_status);

	mutex_lock(&vm->mutex);
	list_add_tail(&bo_va->bo_list, &bo->va);
	mutex_unlock(&vm->mutex);

	वापस bo_va;
पूर्ण

/**
 * radeon_vm_set_pages - helper to call the right asic function
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @addr: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 * @flags: hw access flags
 *
 * Traces the parameters and calls the right asic functions
 * to setup the page table using the DMA.
 */
अटल व्योम radeon_vm_set_pages(काष्ठा radeon_device *rdev,
				काष्ठा radeon_ib *ib,
				uपूर्णांक64_t pe,
				uपूर्णांक64_t addr, अचिन्हित count,
				uपूर्णांक32_t incr, uपूर्णांक32_t flags)
अणु
	trace_radeon_vm_set_page(pe, addr, count, incr, flags);

	अगर ((flags & R600_PTE_GART_MASK) == R600_PTE_GART_MASK) अणु
		uपूर्णांक64_t src = rdev->gart.table_addr + (addr >> 12) * 8;
		radeon_asic_vm_copy_pages(rdev, ib, pe, src, count);

	पूर्ण अन्यथा अगर ((flags & R600_PTE_SYSTEM) || (count < 3)) अणु
		radeon_asic_vm_ग_लिखो_pages(rdev, ib, pe, addr,
					   count, incr, flags);

	पूर्ण अन्यथा अणु
		radeon_asic_vm_set_pages(rdev, ib, pe, addr,
					 count, incr, flags);
	पूर्ण
पूर्ण

/**
 * radeon_vm_clear_bo - initially clear the page dir/table
 *
 * @rdev: radeon_device poपूर्णांकer
 * @bo: bo to clear
 */
अटल पूर्णांक radeon_vm_clear_bo(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_bo *bo)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु true, false पूर्ण;
	काष्ठा radeon_ib ib;
	अचिन्हित entries;
	uपूर्णांक64_t addr;
	पूर्णांक r;

	r = radeon_bo_reserve(bo, false);
	अगर (r)
		वापस r;

	r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
	अगर (r)
		जाओ error_unreserve;

	addr = radeon_bo_gpu_offset(bo);
	entries = radeon_bo_size(bo) / 8;

	r = radeon_ib_get(rdev, R600_RING_TYPE_DMA_INDEX, &ib, शून्य, 256);
	अगर (r)
		जाओ error_unreserve;

	ib.length_dw = 0;

	radeon_vm_set_pages(rdev, &ib, addr, 0, entries, 0, 0);
	radeon_asic_vm_pad_ib(rdev, &ib);
	WARN_ON(ib.length_dw > 64);

	r = radeon_ib_schedule(rdev, &ib, शून्य, false);
	अगर (r)
		जाओ error_मुक्त;

	ib.fence->is_vm_update = true;
	radeon_bo_fence(bo, ib.fence, false);

error_मुक्त:
	radeon_ib_मुक्त(rdev, &ib);

error_unreserve:
	radeon_bo_unreserve(bo);
	वापस r;
पूर्ण

/**
 * radeon_vm_bo_set_addr - set bos भव address inside a vm
 *
 * @rdev: radeon_device poपूर्णांकer
 * @bo_va: bo_va to store the address
 * @soffset: requested offset of the buffer in the VM address space
 * @flags: attributes of pages (पढ़ो/ग_लिखो/valid/etc.)
 *
 * Set offset of @bo_va (cayman+).
 * Validate and set the offset requested within the vm address space.
 * Returns 0 क्रम success, error क्रम failure.
 *
 * Object has to be reserved and माला_लो unreserved by this function!
 */
पूर्णांक radeon_vm_bo_set_addr(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_bo_va *bo_va,
			  uपूर्णांक64_t soffset,
			  uपूर्णांक32_t flags)
अणु
	uपूर्णांक64_t size = radeon_bo_size(bo_va->bo);
	काष्ठा radeon_vm *vm = bo_va->vm;
	अचिन्हित last_pfn, pt_idx;
	uपूर्णांक64_t eoffset;
	पूर्णांक r;

	अगर (soffset) अणु
		/* make sure object fit at this offset */
		eoffset = soffset + size - 1;
		अगर (soffset >= eoffset) अणु
			r = -EINVAL;
			जाओ error_unreserve;
		पूर्ण

		last_pfn = eoffset / RADEON_GPU_PAGE_SIZE;
		अगर (last_pfn >= rdev->vm_manager.max_pfn) अणु
			dev_err(rdev->dev, "va above limit (0x%08X >= 0x%08X)\n",
				last_pfn, rdev->vm_manager.max_pfn);
			r = -EINVAL;
			जाओ error_unreserve;
		पूर्ण

	पूर्ण अन्यथा अणु
		eoffset = last_pfn = 0;
	पूर्ण

	mutex_lock(&vm->mutex);
	soffset /= RADEON_GPU_PAGE_SIZE;
	eoffset /= RADEON_GPU_PAGE_SIZE;
	अगर (soffset || eoffset) अणु
		काष्ठा पूर्णांकerval_tree_node *it;
		it = पूर्णांकerval_tree_iter_first(&vm->va, soffset, eoffset);
		अगर (it && it != &bo_va->it) अणु
			काष्ठा radeon_bo_va *पंचांगp;
			पंचांगp = container_of(it, काष्ठा radeon_bo_va, it);
			/* bo and पंचांगp overlap, invalid offset */
			dev_err(rdev->dev, "bo %p va 0x%010Lx conflict with "
				"(bo %p 0x%010lx 0x%010lx)\n", bo_va->bo,
				soffset, पंचांगp->bo, पंचांगp->it.start, पंचांगp->it.last);
			mutex_unlock(&vm->mutex);
			r = -EINVAL;
			जाओ error_unreserve;
		पूर्ण
	पूर्ण

	अगर (bo_va->it.start || bo_va->it.last) अणु
		/* add a clone of the bo_va to clear the old address */
		काष्ठा radeon_bo_va *पंचांगp;
		पंचांगp = kzalloc(माप(काष्ठा radeon_bo_va), GFP_KERNEL);
		अगर (!पंचांगp) अणु
			mutex_unlock(&vm->mutex);
			r = -ENOMEM;
			जाओ error_unreserve;
		पूर्ण
		पंचांगp->it.start = bo_va->it.start;
		पंचांगp->it.last = bo_va->it.last;
		पंचांगp->vm = vm;
		पंचांगp->bo = radeon_bo_ref(bo_va->bo);

		पूर्णांकerval_tree_हटाओ(&bo_va->it, &vm->va);
		spin_lock(&vm->status_lock);
		bo_va->it.start = 0;
		bo_va->it.last = 0;
		list_del_init(&bo_va->vm_status);
		list_add(&पंचांगp->vm_status, &vm->मुक्तd);
		spin_unlock(&vm->status_lock);
	पूर्ण

	अगर (soffset || eoffset) अणु
		spin_lock(&vm->status_lock);
		bo_va->it.start = soffset;
		bo_va->it.last = eoffset;
		list_add(&bo_va->vm_status, &vm->cleared);
		spin_unlock(&vm->status_lock);
		पूर्णांकerval_tree_insert(&bo_va->it, &vm->va);
	पूर्ण

	bo_va->flags = flags;

	soffset >>= radeon_vm_block_size;
	eoffset >>= radeon_vm_block_size;

	BUG_ON(eoffset >= radeon_vm_num_pdes(rdev));

	अगर (eoffset > vm->max_pde_used)
		vm->max_pde_used = eoffset;

	radeon_bo_unreserve(bo_va->bo);

	/* walk over the address space and allocate the page tables */
	क्रम (pt_idx = soffset; pt_idx <= eoffset; ++pt_idx) अणु
		काष्ठा radeon_bo *pt;

		अगर (vm->page_tables[pt_idx].bo)
			जारी;

		/* drop mutex to allocate and clear page table */
		mutex_unlock(&vm->mutex);

		r = radeon_bo_create(rdev, RADEON_VM_PTE_COUNT * 8,
				     RADEON_GPU_PAGE_SIZE, true,
				     RADEON_GEM_DOMAIN_VRAM, 0,
				     शून्य, शून्य, &pt);
		अगर (r)
			वापस r;

		r = radeon_vm_clear_bo(rdev, pt);
		अगर (r) अणु
			radeon_bo_unref(&pt);
			वापस r;
		पूर्ण

		/* aquire mutex again */
		mutex_lock(&vm->mutex);
		अगर (vm->page_tables[pt_idx].bo) अणु
			/* someone अन्यथा allocated the pt in the meanसमय */
			mutex_unlock(&vm->mutex);
			radeon_bo_unref(&pt);
			mutex_lock(&vm->mutex);
			जारी;
		पूर्ण

		vm->page_tables[pt_idx].addr = 0;
		vm->page_tables[pt_idx].bo = pt;
	पूर्ण

	mutex_unlock(&vm->mutex);
	वापस 0;

error_unreserve:
	radeon_bo_unreserve(bo_va->bo);
	वापस r;
पूर्ण

/**
 * radeon_vm_map_gart - get the physical address of a gart page
 *
 * @rdev: radeon_device poपूर्णांकer
 * @addr: the unmapped addr
 *
 * Look up the physical address of the page that the pte resolves
 * to (cayman+).
 * Returns the physical address of the page.
 */
uपूर्णांक64_t radeon_vm_map_gart(काष्ठा radeon_device *rdev, uपूर्णांक64_t addr)
अणु
	uपूर्णांक64_t result;

	/* page table offset */
	result = rdev->gart.pages_entry[addr >> RADEON_GPU_PAGE_SHIFT];
	result &= ~RADEON_GPU_PAGE_MASK;

	वापस result;
पूर्ण

/**
 * radeon_vm_page_flags - translate page flags to what the hw uses
 *
 * @flags: flags comming from userspace
 *
 * Translate the flags the userspace ABI uses to hw flags.
 */
अटल uपूर्णांक32_t radeon_vm_page_flags(uपूर्णांक32_t flags)
अणु
	uपूर्णांक32_t hw_flags = 0;

	hw_flags |= (flags & RADEON_VM_PAGE_VALID) ? R600_PTE_VALID : 0;
	hw_flags |= (flags & RADEON_VM_PAGE_READABLE) ? R600_PTE_READABLE : 0;
	hw_flags |= (flags & RADEON_VM_PAGE_WRITEABLE) ? R600_PTE_WRITEABLE : 0;
	अगर (flags & RADEON_VM_PAGE_SYSTEM) अणु
		hw_flags |= R600_PTE_SYSTEM;
		hw_flags |= (flags & RADEON_VM_PAGE_SNOOPED) ? R600_PTE_SNOOPED : 0;
	पूर्ण
	वापस hw_flags;
पूर्ण

/**
 * radeon_vm_update_pdes - make sure that page directory is valid
 *
 * @rdev: radeon_device poपूर्णांकer
 * @vm: requested vm
 *
 * Allocates new page tables अगर necessary
 * and updates the page directory (cayman+).
 * Returns 0 क्रम success, error क्रम failure.
 *
 * Global and local mutex must be locked!
 */
पूर्णांक radeon_vm_update_page_directory(काष्ठा radeon_device *rdev,
				    काष्ठा radeon_vm *vm)
अणु
	काष्ठा radeon_bo *pd = vm->page_directory;
	uपूर्णांक64_t pd_addr = radeon_bo_gpu_offset(pd);
	uपूर्णांक32_t incr = RADEON_VM_PTE_COUNT * 8;
	uपूर्णांक64_t last_pde = ~0, last_pt = ~0;
	अचिन्हित count = 0, pt_idx, ndw;
	काष्ठा radeon_ib ib;
	पूर्णांक r;

	/* padding, etc. */
	ndw = 64;

	/* assume the worst हाल */
	ndw += vm->max_pde_used * 6;

	/* update too big क्रम an IB */
	अगर (ndw > 0xfffff)
		वापस -ENOMEM;

	r = radeon_ib_get(rdev, R600_RING_TYPE_DMA_INDEX, &ib, शून्य, ndw * 4);
	अगर (r)
		वापस r;
	ib.length_dw = 0;

	/* walk over the address space and update the page directory */
	क्रम (pt_idx = 0; pt_idx <= vm->max_pde_used; ++pt_idx) अणु
		काष्ठा radeon_bo *bo = vm->page_tables[pt_idx].bo;
		uपूर्णांक64_t pde, pt;

		अगर (bo == शून्य)
			जारी;

		pt = radeon_bo_gpu_offset(bo);
		अगर (vm->page_tables[pt_idx].addr == pt)
			जारी;
		vm->page_tables[pt_idx].addr = pt;

		pde = pd_addr + pt_idx * 8;
		अगर (((last_pde + 8 * count) != pde) ||
		    ((last_pt + incr * count) != pt)) अणु

			अगर (count) अणु
				radeon_vm_set_pages(rdev, &ib, last_pde,
						    last_pt, count, incr,
						    R600_PTE_VALID);
			पूर्ण

			count = 1;
			last_pde = pde;
			last_pt = pt;
		पूर्ण अन्यथा अणु
			++count;
		पूर्ण
	पूर्ण

	अगर (count)
		radeon_vm_set_pages(rdev, &ib, last_pde, last_pt, count,
				    incr, R600_PTE_VALID);

	अगर (ib.length_dw != 0) अणु
		radeon_asic_vm_pad_ib(rdev, &ib);

		radeon_sync_resv(rdev, &ib.sync, pd->tbo.base.resv, true);
		WARN_ON(ib.length_dw > ndw);
		r = radeon_ib_schedule(rdev, &ib, शून्य, false);
		अगर (r) अणु
			radeon_ib_मुक्त(rdev, &ib);
			वापस r;
		पूर्ण
		ib.fence->is_vm_update = true;
		radeon_bo_fence(pd, ib.fence, false);
	पूर्ण
	radeon_ib_मुक्त(rdev, &ib);

	वापस 0;
पूर्ण

/**
 * radeon_vm_frag_ptes - add fragment inक्रमmation to PTEs
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: IB क्रम the update
 * @pe_start: first PTE to handle
 * @pe_end: last PTE to handle
 * @addr: addr those PTEs should poपूर्णांक to
 * @flags: hw mapping flags
 *
 * Global and local mutex must be locked!
 */
अटल व्योम radeon_vm_frag_ptes(काष्ठा radeon_device *rdev,
				काष्ठा radeon_ib *ib,
				uपूर्णांक64_t pe_start, uपूर्णांक64_t pe_end,
				uपूर्णांक64_t addr, uपूर्णांक32_t flags)
अणु
	/**
	 * The MC L1 TLB supports variable sized pages, based on a fragment
	 * field in the PTE. When this field is set to a non-zero value, page
	 * granularity is increased from 4KB to (1 << (12 + frag)). The PTE
	 * flags are considered valid क्रम all PTEs within the fragment range
	 * and corresponding mappings are assumed to be physically contiguous.
	 *
	 * The L1 TLB can store a single PTE क्रम the whole fragment,
	 * signअगरicantly increasing the space available क्रम translation
	 * caching. This leads to large improvements in throughput when the
	 * TLB is under pressure.
	 *
	 * The L2 TLB distributes small and large fragments पूर्णांकo two
	 * asymmetric partitions. The large fragment cache is signअगरicantly
	 * larger. Thus, we try to use large fragments wherever possible.
	 * Userspace can support this by aligning भव base address and
	 * allocation size to the fragment size.
	 */

	/* NI is optimized क्रम 256KB fragments, SI and newer क्रम 64KB */
	uपूर्णांक64_t frag_flags = ((rdev->family == CHIP_CAYMAN) ||
			       (rdev->family == CHIP_ARUBA)) ?
			R600_PTE_FRAG_256KB : R600_PTE_FRAG_64KB;
	uपूर्णांक64_t frag_align = ((rdev->family == CHIP_CAYMAN) ||
			       (rdev->family == CHIP_ARUBA)) ? 0x200 : 0x80;

	uपूर्णांक64_t frag_start = ALIGN(pe_start, frag_align);
	uपूर्णांक64_t frag_end = pe_end & ~(frag_align - 1);

	अचिन्हित count;

	/* प्रणाली pages are non continuously */
	अगर ((flags & R600_PTE_SYSTEM) || !(flags & R600_PTE_VALID) ||
	    (frag_start >= frag_end)) अणु

		count = (pe_end - pe_start) / 8;
		radeon_vm_set_pages(rdev, ib, pe_start, addr, count,
				    RADEON_GPU_PAGE_SIZE, flags);
		वापस;
	पूर्ण

	/* handle the 4K area at the beginning */
	अगर (pe_start != frag_start) अणु
		count = (frag_start - pe_start) / 8;
		radeon_vm_set_pages(rdev, ib, pe_start, addr, count,
				    RADEON_GPU_PAGE_SIZE, flags);
		addr += RADEON_GPU_PAGE_SIZE * count;
	पूर्ण

	/* handle the area in the middle */
	count = (frag_end - frag_start) / 8;
	radeon_vm_set_pages(rdev, ib, frag_start, addr, count,
			    RADEON_GPU_PAGE_SIZE, flags | frag_flags);

	/* handle the 4K area at the end */
	अगर (frag_end != pe_end) अणु
		addr += RADEON_GPU_PAGE_SIZE * count;
		count = (pe_end - frag_end) / 8;
		radeon_vm_set_pages(rdev, ib, frag_end, addr, count,
				    RADEON_GPU_PAGE_SIZE, flags);
	पूर्ण
पूर्ण

/**
 * radeon_vm_update_ptes - make sure that page tables are valid
 *
 * @rdev: radeon_device poपूर्णांकer
 * @vm: requested vm
 * @ib: indirect buffer to use क्रम the update
 * @start: start of GPU address range
 * @end: end of GPU address range
 * @dst: destination address to map to
 * @flags: mapping flags
 *
 * Update the page tables in the range @start - @end (cayman+).
 *
 * Global and local mutex must be locked!
 */
अटल पूर्णांक radeon_vm_update_ptes(काष्ठा radeon_device *rdev,
				 काष्ठा radeon_vm *vm,
				 काष्ठा radeon_ib *ib,
				 uपूर्णांक64_t start, uपूर्णांक64_t end,
				 uपूर्णांक64_t dst, uपूर्णांक32_t flags)
अणु
	uपूर्णांक64_t mask = RADEON_VM_PTE_COUNT - 1;
	uपूर्णांक64_t last_pte = ~0, last_dst = ~0;
	अचिन्हित count = 0;
	uपूर्णांक64_t addr;

	/* walk over the address space and update the page tables */
	क्रम (addr = start; addr < end; ) अणु
		uपूर्णांक64_t pt_idx = addr >> radeon_vm_block_size;
		काष्ठा radeon_bo *pt = vm->page_tables[pt_idx].bo;
		अचिन्हित nptes;
		uपूर्णांक64_t pte;
		पूर्णांक r;

		radeon_sync_resv(rdev, &ib->sync, pt->tbo.base.resv, true);
		r = dma_resv_reserve_shared(pt->tbo.base.resv, 1);
		अगर (r)
			वापस r;

		अगर ((addr & ~mask) == (end & ~mask))
			nptes = end - addr;
		अन्यथा
			nptes = RADEON_VM_PTE_COUNT - (addr & mask);

		pte = radeon_bo_gpu_offset(pt);
		pte += (addr & mask) * 8;

		अगर ((last_pte + 8 * count) != pte) अणु

			अगर (count) अणु
				radeon_vm_frag_ptes(rdev, ib, last_pte,
						    last_pte + 8 * count,
						    last_dst, flags);
			पूर्ण

			count = nptes;
			last_pte = pte;
			last_dst = dst;
		पूर्ण अन्यथा अणु
			count += nptes;
		पूर्ण

		addr += nptes;
		dst += nptes * RADEON_GPU_PAGE_SIZE;
	पूर्ण

	अगर (count) अणु
		radeon_vm_frag_ptes(rdev, ib, last_pte,
				    last_pte + 8 * count,
				    last_dst, flags);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * radeon_vm_fence_pts - fence page tables after an update
 *
 * @vm: requested vm
 * @start: start of GPU address range
 * @end: end of GPU address range
 * @fence: fence to use
 *
 * Fence the page tables in the range @start - @end (cayman+).
 *
 * Global and local mutex must be locked!
 */
अटल व्योम radeon_vm_fence_pts(काष्ठा radeon_vm *vm,
				uपूर्णांक64_t start, uपूर्णांक64_t end,
				काष्ठा radeon_fence *fence)
अणु
	अचिन्हित i;

	start >>= radeon_vm_block_size;
	end = (end - 1) >> radeon_vm_block_size;

	क्रम (i = start; i <= end; ++i)
		radeon_bo_fence(vm->page_tables[i].bo, fence, true);
पूर्ण

/**
 * radeon_vm_bo_update - map a bo पूर्णांकo the vm page table
 *
 * @rdev: radeon_device poपूर्णांकer
 * @bo_va: radeon buffer भव address object
 * @mem: tपंचांग mem
 *
 * Fill in the page table entries क्रम @bo (cayman+).
 * Returns 0 क्रम success, -EINVAL क्रम failure.
 *
 * Object have to be reserved and mutex must be locked!
 */
पूर्णांक radeon_vm_bo_update(काष्ठा radeon_device *rdev,
			काष्ठा radeon_bo_va *bo_va,
			काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा radeon_vm *vm = bo_va->vm;
	काष्ठा radeon_ib ib;
	अचिन्हित nptes, ncmds, ndw;
	uपूर्णांक64_t addr;
	uपूर्णांक32_t flags;
	पूर्णांक r;

	अगर (!bo_va->it.start) अणु
		dev_err(rdev->dev, "bo %p don't has a mapping in vm %p\n",
			bo_va->bo, vm);
		वापस -EINVAL;
	पूर्ण

	spin_lock(&vm->status_lock);
	अगर (mem) अणु
		अगर (list_empty(&bo_va->vm_status)) अणु
			spin_unlock(&vm->status_lock);
			वापस 0;
		पूर्ण
		list_del_init(&bo_va->vm_status);
	पूर्ण अन्यथा अणु
		list_del(&bo_va->vm_status);
		list_add(&bo_va->vm_status, &vm->cleared);
	पूर्ण
	spin_unlock(&vm->status_lock);

	bo_va->flags &= ~RADEON_VM_PAGE_VALID;
	bo_va->flags &= ~RADEON_VM_PAGE_SYSTEM;
	bo_va->flags &= ~RADEON_VM_PAGE_SNOOPED;
	अगर (bo_va->bo && radeon_tपंचांग_tt_is_पढ़ोonly(rdev, bo_va->bo->tbo.tपंचांग))
		bo_va->flags &= ~RADEON_VM_PAGE_WRITEABLE;

	अगर (mem) अणु
		addr = (u64)mem->start << PAGE_SHIFT;
		अगर (mem->mem_type != TTM_PL_SYSTEM)
			bo_va->flags |= RADEON_VM_PAGE_VALID;

		अगर (mem->mem_type == TTM_PL_TT) अणु
			bo_va->flags |= RADEON_VM_PAGE_SYSTEM;
			अगर (!(bo_va->bo->flags & (RADEON_GEM_GTT_WC | RADEON_GEM_GTT_UC)))
				bo_va->flags |= RADEON_VM_PAGE_SNOOPED;

		पूर्ण अन्यथा अणु
			addr += rdev->vm_manager.vram_base_offset;
		पूर्ण
	पूर्ण अन्यथा अणु
		addr = 0;
	पूर्ण

	trace_radeon_vm_bo_update(bo_va);

	nptes = bo_va->it.last - bo_va->it.start + 1;

	/* reserve space क्रम one command every (1 << BLOCK_SIZE) entries
	   or 2k dwords (whatever is smaller) */
	ncmds = (nptes >> min(radeon_vm_block_size, 11)) + 1;

	/* padding, etc. */
	ndw = 64;

	flags = radeon_vm_page_flags(bo_va->flags);
	अगर ((flags & R600_PTE_GART_MASK) == R600_PTE_GART_MASK) अणु
		/* only copy commands needed */
		ndw += ncmds * 7;

	पूर्ण अन्यथा अगर (flags & R600_PTE_SYSTEM) अणु
		/* header क्रम ग_लिखो data commands */
		ndw += ncmds * 4;

		/* body of ग_लिखो data command */
		ndw += nptes * 2;

	पूर्ण अन्यथा अणु
		/* set page commands needed */
		ndw += ncmds * 10;

		/* two extra commands क्रम begin/end of fragment */
		ndw += 2 * 10;
	पूर्ण

	/* update too big क्रम an IB */
	अगर (ndw > 0xfffff)
		वापस -ENOMEM;

	r = radeon_ib_get(rdev, R600_RING_TYPE_DMA_INDEX, &ib, शून्य, ndw * 4);
	अगर (r)
		वापस r;
	ib.length_dw = 0;

	अगर (!(bo_va->flags & RADEON_VM_PAGE_VALID)) अणु
		अचिन्हित i;

		क्रम (i = 0; i < RADEON_NUM_RINGS; ++i)
			radeon_sync_fence(&ib.sync, vm->ids[i].last_id_use);
	पूर्ण

	r = radeon_vm_update_ptes(rdev, vm, &ib, bo_va->it.start,
				  bo_va->it.last + 1, addr,
				  radeon_vm_page_flags(bo_va->flags));
	अगर (r) अणु
		radeon_ib_मुक्त(rdev, &ib);
		वापस r;
	पूर्ण

	radeon_asic_vm_pad_ib(rdev, &ib);
	WARN_ON(ib.length_dw > ndw);

	r = radeon_ib_schedule(rdev, &ib, शून्य, false);
	अगर (r) अणु
		radeon_ib_मुक्त(rdev, &ib);
		वापस r;
	पूर्ण
	ib.fence->is_vm_update = true;
	radeon_vm_fence_pts(vm, bo_va->it.start, bo_va->it.last + 1, ib.fence);
	radeon_fence_unref(&bo_va->last_pt_update);
	bo_va->last_pt_update = radeon_fence_ref(ib.fence);
	radeon_ib_मुक्त(rdev, &ib);

	वापस 0;
पूर्ण

/**
 * radeon_vm_clear_मुक्तd - clear मुक्तd BOs in the PT
 *
 * @rdev: radeon_device poपूर्णांकer
 * @vm: requested vm
 *
 * Make sure all मुक्तd BOs are cleared in the PT.
 * Returns 0 क्रम success.
 *
 * PTs have to be reserved and mutex must be locked!
 */
पूर्णांक radeon_vm_clear_मुक्तd(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_vm *vm)
अणु
	काष्ठा radeon_bo_va *bo_va;
	पूर्णांक r = 0;

	spin_lock(&vm->status_lock);
	जबतक (!list_empty(&vm->मुक्तd)) अणु
		bo_va = list_first_entry(&vm->मुक्तd,
			काष्ठा radeon_bo_va, vm_status);
		spin_unlock(&vm->status_lock);

		r = radeon_vm_bo_update(rdev, bo_va, शून्य);
		radeon_bo_unref(&bo_va->bo);
		radeon_fence_unref(&bo_va->last_pt_update);
		spin_lock(&vm->status_lock);
		list_del(&bo_va->vm_status);
		kमुक्त(bo_va);
		अगर (r)
			अवरोध;

	पूर्ण
	spin_unlock(&vm->status_lock);
	वापस r;

पूर्ण

/**
 * radeon_vm_clear_invalids - clear invalidated BOs in the PT
 *
 * @rdev: radeon_device poपूर्णांकer
 * @vm: requested vm
 *
 * Make sure all invalidated BOs are cleared in the PT.
 * Returns 0 क्रम success.
 *
 * PTs have to be reserved and mutex must be locked!
 */
पूर्णांक radeon_vm_clear_invalids(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_vm *vm)
अणु
	काष्ठा radeon_bo_va *bo_va;
	पूर्णांक r;

	spin_lock(&vm->status_lock);
	जबतक (!list_empty(&vm->invalidated)) अणु
		bo_va = list_first_entry(&vm->invalidated,
			काष्ठा radeon_bo_va, vm_status);
		spin_unlock(&vm->status_lock);

		r = radeon_vm_bo_update(rdev, bo_va, शून्य);
		अगर (r)
			वापस r;

		spin_lock(&vm->status_lock);
	पूर्ण
	spin_unlock(&vm->status_lock);

	वापस 0;
पूर्ण

/**
 * radeon_vm_bo_rmv - हटाओ a bo to a specअगरic vm
 *
 * @rdev: radeon_device poपूर्णांकer
 * @bo_va: requested bo_va
 *
 * Remove @bo_va->bo from the requested vm (cayman+).
 *
 * Object have to be reserved!
 */
व्योम radeon_vm_bo_rmv(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_bo_va *bo_va)
अणु
	काष्ठा radeon_vm *vm = bo_va->vm;

	list_del(&bo_va->bo_list);

	mutex_lock(&vm->mutex);
	अगर (bo_va->it.start || bo_va->it.last)
		पूर्णांकerval_tree_हटाओ(&bo_va->it, &vm->va);

	spin_lock(&vm->status_lock);
	list_del(&bo_va->vm_status);
	अगर (bo_va->it.start || bo_va->it.last) अणु
		bo_va->bo = radeon_bo_ref(bo_va->bo);
		list_add(&bo_va->vm_status, &vm->मुक्तd);
	पूर्ण अन्यथा अणु
		radeon_fence_unref(&bo_va->last_pt_update);
		kमुक्त(bo_va);
	पूर्ण
	spin_unlock(&vm->status_lock);

	mutex_unlock(&vm->mutex);
पूर्ण

/**
 * radeon_vm_bo_invalidate - mark the bo as invalid
 *
 * @rdev: radeon_device poपूर्णांकer
 * @bo: radeon buffer object
 *
 * Mark @bo as invalid (cayman+).
 */
व्योम radeon_vm_bo_invalidate(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_bo *bo)
अणु
	काष्ठा radeon_bo_va *bo_va;

	list_क्रम_each_entry(bo_va, &bo->va, bo_list) अणु
		spin_lock(&bo_va->vm->status_lock);
		अगर (list_empty(&bo_va->vm_status) &&
		    (bo_va->it.start || bo_va->it.last))
			list_add(&bo_va->vm_status, &bo_va->vm->invalidated);
		spin_unlock(&bo_va->vm->status_lock);
	पूर्ण
पूर्ण

/**
 * radeon_vm_init - initialize a vm instance
 *
 * @rdev: radeon_device poपूर्णांकer
 * @vm: requested vm
 *
 * Init @vm fields (cayman+).
 */
पूर्णांक radeon_vm_init(काष्ठा radeon_device *rdev, काष्ठा radeon_vm *vm)
अणु
	स्थिर अचिन्हित align = min(RADEON_VM_PTB_ALIGN_SIZE,
		RADEON_VM_PTE_COUNT * 8);
	अचिन्हित pd_size, pd_entries, pts_size;
	पूर्णांक i, r;

	vm->ib_bo_va = शून्य;
	क्रम (i = 0; i < RADEON_NUM_RINGS; ++i) अणु
		vm->ids[i].id = 0;
		vm->ids[i].flushed_updates = शून्य;
		vm->ids[i].last_id_use = शून्य;
	पूर्ण
	mutex_init(&vm->mutex);
	vm->va = RB_ROOT_CACHED;
	spin_lock_init(&vm->status_lock);
	INIT_LIST_HEAD(&vm->invalidated);
	INIT_LIST_HEAD(&vm->मुक्तd);
	INIT_LIST_HEAD(&vm->cleared);

	pd_size = radeon_vm_directory_size(rdev);
	pd_entries = radeon_vm_num_pdes(rdev);

	/* allocate page table array */
	pts_size = pd_entries * माप(काष्ठा radeon_vm_pt);
	vm->page_tables = kzalloc(pts_size, GFP_KERNEL);
	अगर (vm->page_tables == शून्य) अणु
		DRM_ERROR("Cannot allocate memory for page table array\n");
		वापस -ENOMEM;
	पूर्ण

	r = radeon_bo_create(rdev, pd_size, align, true,
			     RADEON_GEM_DOMAIN_VRAM, 0, शून्य,
			     शून्य, &vm->page_directory);
	अगर (r)
		वापस r;

	r = radeon_vm_clear_bo(rdev, vm->page_directory);
	अगर (r) अणु
		radeon_bo_unref(&vm->page_directory);
		vm->page_directory = शून्य;
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * radeon_vm_fini - tear करोwn a vm instance
 *
 * @rdev: radeon_device poपूर्णांकer
 * @vm: requested vm
 *
 * Tear करोwn @vm (cayman+).
 * Unbind the VM and हटाओ all bos from the vm bo list
 */
व्योम radeon_vm_fini(काष्ठा radeon_device *rdev, काष्ठा radeon_vm *vm)
अणु
	काष्ठा radeon_bo_va *bo_va, *पंचांगp;
	पूर्णांक i, r;

	अगर (!RB_EMPTY_ROOT(&vm->va.rb_root))
		dev_err(rdev->dev, "still active bo inside vm\n");

	rbtree_postorder_क्रम_each_entry_safe(bo_va, पंचांगp,
					     &vm->va.rb_root, it.rb) अणु
		पूर्णांकerval_tree_हटाओ(&bo_va->it, &vm->va);
		r = radeon_bo_reserve(bo_va->bo, false);
		अगर (!r) अणु
			list_del_init(&bo_va->bo_list);
			radeon_bo_unreserve(bo_va->bo);
			radeon_fence_unref(&bo_va->last_pt_update);
			kमुक्त(bo_va);
		पूर्ण
	पूर्ण
	list_क्रम_each_entry_safe(bo_va, पंचांगp, &vm->मुक्तd, vm_status) अणु
		radeon_bo_unref(&bo_va->bo);
		radeon_fence_unref(&bo_va->last_pt_update);
		kमुक्त(bo_va);
	पूर्ण

	क्रम (i = 0; i < radeon_vm_num_pdes(rdev); i++)
		radeon_bo_unref(&vm->page_tables[i].bo);
	kमुक्त(vm->page_tables);

	radeon_bo_unref(&vm->page_directory);

	क्रम (i = 0; i < RADEON_NUM_RINGS; ++i) अणु
		radeon_fence_unref(&vm->ids[i].flushed_updates);
		radeon_fence_unref(&vm->ids[i].last_id_use);
	पूर्ण

	mutex_destroy(&vm->mutex);
पूर्ण
