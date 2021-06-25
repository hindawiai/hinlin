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
#समावेश <linux/dma-fence-array.h>
#समावेश <linux/पूर्णांकerval_tree_generic.h>
#समावेश <linux/idr.h>
#समावेश <linux/dma-buf.h>

#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_trace.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "amdgpu_gmc.h"
#समावेश "amdgpu_xgmi.h"
#समावेश "amdgpu_dma_buf.h"

/**
 * DOC: GPUVM
 *
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

#घोषणा START(node) ((node)->start)
#घोषणा LAST(node) ((node)->last)

INTERVAL_TREE_DEFINE(काष्ठा amdgpu_bo_va_mapping, rb, uपूर्णांक64_t, __subtree_last,
		     START, LAST, अटल, amdgpu_vm_it)

#अघोषित START
#अघोषित LAST

/**
 * काष्ठा amdgpu_prt_cb - Helper to disable partial resident texture feature from a fence callback
 */
काष्ठा amdgpu_prt_cb अणु

	/**
	 * @adev: amdgpu device
	 */
	काष्ठा amdgpu_device *adev;

	/**
	 * @cb: callback
	 */
	काष्ठा dma_fence_cb cb;
पूर्ण;

/*
 * vm eviction_lock can be taken in MMU notअगरiers. Make sure no reclaim-FS
 * happens जबतक holding this lock anywhere to prevent deadlocks when
 * an MMU notअगरier runs in reclaim-FS context.
 */
अटल अंतरभूत व्योम amdgpu_vm_eviction_lock(काष्ठा amdgpu_vm *vm)
अणु
	mutex_lock(&vm->eviction_lock);
	vm->saved_flags = meदो_स्मृति_noreclaim_save();
पूर्ण

अटल अंतरभूत पूर्णांक amdgpu_vm_eviction_trylock(काष्ठा amdgpu_vm *vm)
अणु
	अगर (mutex_trylock(&vm->eviction_lock)) अणु
		vm->saved_flags = meदो_स्मृति_noreclaim_save();
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम amdgpu_vm_eviction_unlock(काष्ठा amdgpu_vm *vm)
अणु
	meदो_स्मृति_noreclaim_restore(vm->saved_flags);
	mutex_unlock(&vm->eviction_lock);
पूर्ण

/**
 * amdgpu_vm_level_shअगरt - वापस the addr shअगरt क्रम each level
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @level: VMPT level
 *
 * Returns:
 * The number of bits the pfn needs to be right shअगरted क्रम a level.
 */
अटल अचिन्हित amdgpu_vm_level_shअगरt(काष्ठा amdgpu_device *adev,
				      अचिन्हित level)
अणु
	चयन (level) अणु
	हाल AMDGPU_VM_PDB2:
	हाल AMDGPU_VM_PDB1:
	हाल AMDGPU_VM_PDB0:
		वापस 9 * (AMDGPU_VM_PDB0 - level) +
			adev->vm_manager.block_size;
	हाल AMDGPU_VM_PTB:
		वापस 0;
	शेष:
		वापस ~0;
	पूर्ण
पूर्ण

/**
 * amdgpu_vm_num_entries - वापस the number of entries in a PD/PT
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @level: VMPT level
 *
 * Returns:
 * The number of entries in a page directory or page table.
 */
अटल अचिन्हित amdgpu_vm_num_entries(काष्ठा amdgpu_device *adev,
				      अचिन्हित level)
अणु
	अचिन्हित shअगरt = amdgpu_vm_level_shअगरt(adev,
					       adev->vm_manager.root_level);

	अगर (level == adev->vm_manager.root_level)
		/* For the root directory */
		वापस round_up(adev->vm_manager.max_pfn, 1ULL << shअगरt)
			>> shअगरt;
	अन्यथा अगर (level != AMDGPU_VM_PTB)
		/* Everything in between */
		वापस 512;
	अन्यथा
		/* For the page tables on the leaves */
		वापस AMDGPU_VM_PTE_COUNT(adev);
पूर्ण

/**
 * amdgpu_vm_num_ats_entries - वापस the number of ATS entries in the root PD
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Returns:
 * The number of entries in the root page directory which needs the ATS setting.
 */
अटल अचिन्हित amdgpu_vm_num_ats_entries(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित shअगरt;

	shअगरt = amdgpu_vm_level_shअगरt(adev, adev->vm_manager.root_level);
	वापस AMDGPU_GMC_HOLE_START >> (shअगरt + AMDGPU_GPU_PAGE_SHIFT);
पूर्ण

/**
 * amdgpu_vm_entries_mask - the mask to get the entry number of a PD/PT
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @level: VMPT level
 *
 * Returns:
 * The mask to extract the entry number of a PD/PT from an address.
 */
अटल uपूर्णांक32_t amdgpu_vm_entries_mask(काष्ठा amdgpu_device *adev,
				       अचिन्हित पूर्णांक level)
अणु
	अगर (level <= adev->vm_manager.root_level)
		वापस 0xffffffff;
	अन्यथा अगर (level != AMDGPU_VM_PTB)
		वापस 0x1ff;
	अन्यथा
		वापस AMDGPU_VM_PTE_COUNT(adev) - 1;
पूर्ण

/**
 * amdgpu_vm_bo_size - वापसs the size of the BOs in bytes
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @level: VMPT level
 *
 * Returns:
 * The size of the BO क्रम a page directory or page table in bytes.
 */
अटल अचिन्हित amdgpu_vm_bo_size(काष्ठा amdgpu_device *adev, अचिन्हित level)
अणु
	वापस AMDGPU_GPU_PAGE_ALIGN(amdgpu_vm_num_entries(adev, level) * 8);
पूर्ण

/**
 * amdgpu_vm_bo_evicted - vm_bo is evicted
 *
 * @vm_bo: vm_bo which is evicted
 *
 * State क्रम PDs/PTs and per VM BOs which are not at the location they should
 * be.
 */
अटल व्योम amdgpu_vm_bo_evicted(काष्ठा amdgpu_vm_bo_base *vm_bo)
अणु
	काष्ठा amdgpu_vm *vm = vm_bo->vm;
	काष्ठा amdgpu_bo *bo = vm_bo->bo;

	vm_bo->moved = true;
	अगर (bo->tbo.type == tपंचांग_bo_type_kernel)
		list_move(&vm_bo->vm_status, &vm->evicted);
	अन्यथा
		list_move_tail(&vm_bo->vm_status, &vm->evicted);
पूर्ण
/**
 * amdgpu_vm_bo_moved - vm_bo is moved
 *
 * @vm_bo: vm_bo which is moved
 *
 * State क्रम per VM BOs which are moved, but that change is not yet reflected
 * in the page tables.
 */
अटल व्योम amdgpu_vm_bo_moved(काष्ठा amdgpu_vm_bo_base *vm_bo)
अणु
	list_move(&vm_bo->vm_status, &vm_bo->vm->moved);
पूर्ण

/**
 * amdgpu_vm_bo_idle - vm_bo is idle
 *
 * @vm_bo: vm_bo which is now idle
 *
 * State क्रम PDs/PTs and per VM BOs which have gone through the state machine
 * and are now idle.
 */
अटल व्योम amdgpu_vm_bo_idle(काष्ठा amdgpu_vm_bo_base *vm_bo)
अणु
	list_move(&vm_bo->vm_status, &vm_bo->vm->idle);
	vm_bo->moved = false;
पूर्ण

/**
 * amdgpu_vm_bo_invalidated - vm_bo is invalidated
 *
 * @vm_bo: vm_bo which is now invalidated
 *
 * State क्रम normal BOs which are invalidated and that change not yet reflected
 * in the PTs.
 */
अटल व्योम amdgpu_vm_bo_invalidated(काष्ठा amdgpu_vm_bo_base *vm_bo)
अणु
	spin_lock(&vm_bo->vm->invalidated_lock);
	list_move(&vm_bo->vm_status, &vm_bo->vm->invalidated);
	spin_unlock(&vm_bo->vm->invalidated_lock);
पूर्ण

/**
 * amdgpu_vm_bo_relocated - vm_bo is reloacted
 *
 * @vm_bo: vm_bo which is relocated
 *
 * State क्रम PDs/PTs which needs to update their parent PD.
 * For the root PD, just move to idle state.
 */
अटल व्योम amdgpu_vm_bo_relocated(काष्ठा amdgpu_vm_bo_base *vm_bo)
अणु
	अगर (vm_bo->bo->parent)
		list_move(&vm_bo->vm_status, &vm_bo->vm->relocated);
	अन्यथा
		amdgpu_vm_bo_idle(vm_bo);
पूर्ण

/**
 * amdgpu_vm_bo_करोne - vm_bo is करोne
 *
 * @vm_bo: vm_bo which is now करोne
 *
 * State क्रम normal BOs which are invalidated and that change has been updated
 * in the PTs.
 */
अटल व्योम amdgpu_vm_bo_करोne(काष्ठा amdgpu_vm_bo_base *vm_bo)
अणु
	spin_lock(&vm_bo->vm->invalidated_lock);
	list_move(&vm_bo->vm_status, &vm_bo->vm->करोne);
	spin_unlock(&vm_bo->vm->invalidated_lock);
पूर्ण

/**
 * amdgpu_vm_bo_base_init - Adds bo to the list of bos associated with the vm
 *
 * @base: base काष्ठाure क्रम tracking BO usage in a VM
 * @vm: vm to which bo is to be added
 * @bo: amdgpu buffer object
 *
 * Initialize a bo_va_base काष्ठाure and add it to the appropriate lists
 *
 */
अटल व्योम amdgpu_vm_bo_base_init(काष्ठा amdgpu_vm_bo_base *base,
				   काष्ठा amdgpu_vm *vm,
				   काष्ठा amdgpu_bo *bo)
अणु
	base->vm = vm;
	base->bo = bo;
	base->next = शून्य;
	INIT_LIST_HEAD(&base->vm_status);

	अगर (!bo)
		वापस;
	base->next = bo->vm_bo;
	bo->vm_bo = base;

	अगर (bo->tbo.base.resv != vm->root.base.bo->tbo.base.resv)
		वापस;

	vm->bulk_moveable = false;
	अगर (bo->tbo.type == tपंचांग_bo_type_kernel && bo->parent)
		amdgpu_vm_bo_relocated(base);
	अन्यथा
		amdgpu_vm_bo_idle(base);

	अगर (bo->preferred_करोमुख्यs &
	    amdgpu_mem_type_to_करोमुख्य(bo->tbo.mem.mem_type))
		वापस;

	/*
	 * we checked all the prerequisites, but it looks like this per vm bo
	 * is currently evicted. add the bo to the evicted list to make sure it
	 * is validated on next vm use to aव्योम fault.
	 * */
	amdgpu_vm_bo_evicted(base);
पूर्ण

/**
 * amdgpu_vm_pt_parent - get the parent page directory
 *
 * @pt: child page table
 *
 * Helper to get the parent entry क्रम the child page table. शून्य अगर we are at
 * the root page directory.
 */
अटल काष्ठा amdgpu_vm_pt *amdgpu_vm_pt_parent(काष्ठा amdgpu_vm_pt *pt)
अणु
	काष्ठा amdgpu_bo *parent = pt->base.bo->parent;

	अगर (!parent)
		वापस शून्य;

	वापस container_of(parent->vm_bo, काष्ठा amdgpu_vm_pt, base);
पूर्ण

/*
 * amdgpu_vm_pt_cursor - state क्रम क्रम_each_amdgpu_vm_pt
 */
काष्ठा amdgpu_vm_pt_cursor अणु
	uपूर्णांक64_t pfn;
	काष्ठा amdgpu_vm_pt *parent;
	काष्ठा amdgpu_vm_pt *entry;
	अचिन्हित level;
पूर्ण;

/**
 * amdgpu_vm_pt_start - start PD/PT walk
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: amdgpu_vm काष्ठाure
 * @start: start address of the walk
 * @cursor: state to initialize
 *
 * Initialize a amdgpu_vm_pt_cursor to start a walk.
 */
अटल व्योम amdgpu_vm_pt_start(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_vm *vm, uपूर्णांक64_t start,
			       काष्ठा amdgpu_vm_pt_cursor *cursor)
अणु
	cursor->pfn = start;
	cursor->parent = शून्य;
	cursor->entry = &vm->root;
	cursor->level = adev->vm_manager.root_level;
पूर्ण

/**
 * amdgpu_vm_pt_descendant - go to child node
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @cursor: current state
 *
 * Walk to the child node of the current node.
 * Returns:
 * True अगर the walk was possible, false otherwise.
 */
अटल bool amdgpu_vm_pt_descendant(काष्ठा amdgpu_device *adev,
				    काष्ठा amdgpu_vm_pt_cursor *cursor)
अणु
	अचिन्हित mask, shअगरt, idx;

	अगर (!cursor->entry->entries)
		वापस false;

	BUG_ON(!cursor->entry->base.bo);
	mask = amdgpu_vm_entries_mask(adev, cursor->level);
	shअगरt = amdgpu_vm_level_shअगरt(adev, cursor->level);

	++cursor->level;
	idx = (cursor->pfn >> shअगरt) & mask;
	cursor->parent = cursor->entry;
	cursor->entry = &cursor->entry->entries[idx];
	वापस true;
पूर्ण

/**
 * amdgpu_vm_pt_sibling - go to sibling node
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @cursor: current state
 *
 * Walk to the sibling node of the current node.
 * Returns:
 * True अगर the walk was possible, false otherwise.
 */
अटल bool amdgpu_vm_pt_sibling(काष्ठा amdgpu_device *adev,
				 काष्ठा amdgpu_vm_pt_cursor *cursor)
अणु
	अचिन्हित shअगरt, num_entries;

	/* Root करोesn't have a sibling */
	अगर (!cursor->parent)
		वापस false;

	/* Go to our parents and see अगर we got a sibling */
	shअगरt = amdgpu_vm_level_shअगरt(adev, cursor->level - 1);
	num_entries = amdgpu_vm_num_entries(adev, cursor->level - 1);

	अगर (cursor->entry == &cursor->parent->entries[num_entries - 1])
		वापस false;

	cursor->pfn += 1ULL << shअगरt;
	cursor->pfn &= ~((1ULL << shअगरt) - 1);
	++cursor->entry;
	वापस true;
पूर्ण

/**
 * amdgpu_vm_pt_ancestor - go to parent node
 *
 * @cursor: current state
 *
 * Walk to the parent node of the current node.
 * Returns:
 * True अगर the walk was possible, false otherwise.
 */
अटल bool amdgpu_vm_pt_ancestor(काष्ठा amdgpu_vm_pt_cursor *cursor)
अणु
	अगर (!cursor->parent)
		वापस false;

	--cursor->level;
	cursor->entry = cursor->parent;
	cursor->parent = amdgpu_vm_pt_parent(cursor->parent);
	वापस true;
पूर्ण

/**
 * amdgpu_vm_pt_next - get next PD/PT in hieratchy
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @cursor: current state
 *
 * Walk the PD/PT tree to the next node.
 */
अटल व्योम amdgpu_vm_pt_next(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_vm_pt_cursor *cursor)
अणु
	/* First try a newborn child */
	अगर (amdgpu_vm_pt_descendant(adev, cursor))
		वापस;

	/* If that didn't worked try to find a sibling */
	जबतक (!amdgpu_vm_pt_sibling(adev, cursor)) अणु
		/* No sibling, go to our parents and gअक्रमparents */
		अगर (!amdgpu_vm_pt_ancestor(cursor)) अणु
			cursor->pfn = ~0ll;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * amdgpu_vm_pt_first_dfs - start a deep first search
 *
 * @adev: amdgpu_device काष्ठाure
 * @vm: amdgpu_vm काष्ठाure
 * @start: optional cursor to start with
 * @cursor: state to initialize
 *
 * Starts a deep first traversal of the PD/PT tree.
 */
अटल व्योम amdgpu_vm_pt_first_dfs(काष्ठा amdgpu_device *adev,
				   काष्ठा amdgpu_vm *vm,
				   काष्ठा amdgpu_vm_pt_cursor *start,
				   काष्ठा amdgpu_vm_pt_cursor *cursor)
अणु
	अगर (start)
		*cursor = *start;
	अन्यथा
		amdgpu_vm_pt_start(adev, vm, 0, cursor);
	जबतक (amdgpu_vm_pt_descendant(adev, cursor));
पूर्ण

/**
 * amdgpu_vm_pt_जारी_dfs - check अगर the deep first search should जारी
 *
 * @start: starting poपूर्णांक क्रम the search
 * @entry: current entry
 *
 * Returns:
 * True when the search should जारी, false otherwise.
 */
अटल bool amdgpu_vm_pt_जारी_dfs(काष्ठा amdgpu_vm_pt_cursor *start,
				      काष्ठा amdgpu_vm_pt *entry)
अणु
	वापस entry && (!start || entry != start->entry);
पूर्ण

/**
 * amdgpu_vm_pt_next_dfs - get the next node क्रम a deep first search
 *
 * @adev: amdgpu_device काष्ठाure
 * @cursor: current state
 *
 * Move the cursor to the next node in a deep first search.
 */
अटल व्योम amdgpu_vm_pt_next_dfs(काष्ठा amdgpu_device *adev,
				  काष्ठा amdgpu_vm_pt_cursor *cursor)
अणु
	अगर (!cursor->entry)
		वापस;

	अगर (!cursor->parent)
		cursor->entry = शून्य;
	अन्यथा अगर (amdgpu_vm_pt_sibling(adev, cursor))
		जबतक (amdgpu_vm_pt_descendant(adev, cursor));
	अन्यथा
		amdgpu_vm_pt_ancestor(cursor);
पूर्ण

/*
 * क्रम_each_amdgpu_vm_pt_dfs_safe - safe deep first search of all PDs/PTs
 */
#घोषणा क्रम_each_amdgpu_vm_pt_dfs_safe(adev, vm, start, cursor, entry)		\
	क्रम (amdgpu_vm_pt_first_dfs((adev), (vm), (start), &(cursor)),		\
	     (entry) = (cursor).entry, amdgpu_vm_pt_next_dfs((adev), &(cursor));\
	     amdgpu_vm_pt_जारी_dfs((start), (entry));			\
	     (entry) = (cursor).entry, amdgpu_vm_pt_next_dfs((adev), &(cursor)))

/**
 * amdgpu_vm_get_pd_bo - add the VM PD to a validation list
 *
 * @vm: vm providing the BOs
 * @validated: head of validation list
 * @entry: entry to add
 *
 * Add the page directory to the list of BOs to
 * validate क्रम command submission.
 */
व्योम amdgpu_vm_get_pd_bo(काष्ठा amdgpu_vm *vm,
			 काष्ठा list_head *validated,
			 काष्ठा amdgpu_bo_list_entry *entry)
अणु
	entry->priority = 0;
	entry->tv.bo = &vm->root.base.bo->tbo;
	/* Two क्रम VM updates, one क्रम TTM and one क्रम the CS job */
	entry->tv.num_shared = 4;
	entry->user_pages = शून्य;
	list_add(&entry->tv.head, validated);
पूर्ण

/**
 * amdgpu_vm_del_from_lru_notअगरy - update bulk_moveable flag
 *
 * @bo: BO which was हटाओd from the LRU
 *
 * Make sure the bulk_moveable flag is updated when a BO is हटाओd from the
 * LRU.
 */
व्योम amdgpu_vm_del_from_lru_notअगरy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा amdgpu_bo *abo;
	काष्ठा amdgpu_vm_bo_base *bo_base;

	अगर (!amdgpu_bo_is_amdgpu_bo(bo))
		वापस;

	अगर (bo->pin_count)
		वापस;

	abo = tपंचांग_to_amdgpu_bo(bo);
	अगर (!abo->parent)
		वापस;
	क्रम (bo_base = abo->vm_bo; bo_base; bo_base = bo_base->next) अणु
		काष्ठा amdgpu_vm *vm = bo_base->vm;

		अगर (abo->tbo.base.resv == vm->root.base.bo->tbo.base.resv)
			vm->bulk_moveable = false;
	पूर्ण

पूर्ण
/**
 * amdgpu_vm_move_to_lru_tail - move all BOs to the end of LRU
 *
 * @adev: amdgpu device poपूर्णांकer
 * @vm: vm providing the BOs
 *
 * Move all BOs to the end of LRU and remember their positions to put them
 * together.
 */
व्योम amdgpu_vm_move_to_lru_tail(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_vm *vm)
अणु
	काष्ठा amdgpu_vm_bo_base *bo_base;

	अगर (vm->bulk_moveable) अणु
		spin_lock(&adev->mman.bdev.lru_lock);
		tपंचांग_bo_bulk_move_lru_tail(&vm->lru_bulk_move);
		spin_unlock(&adev->mman.bdev.lru_lock);
		वापस;
	पूर्ण

	स_रखो(&vm->lru_bulk_move, 0, माप(vm->lru_bulk_move));

	spin_lock(&adev->mman.bdev.lru_lock);
	list_क्रम_each_entry(bo_base, &vm->idle, vm_status) अणु
		काष्ठा amdgpu_bo *bo = bo_base->bo;

		अगर (!bo->parent)
			जारी;

		tपंचांग_bo_move_to_lru_tail(&bo->tbo, &bo->tbo.mem,
					&vm->lru_bulk_move);
		अगर (bo->shaकरोw)
			tपंचांग_bo_move_to_lru_tail(&bo->shaकरोw->tbo,
						&bo->shaकरोw->tbo.mem,
						&vm->lru_bulk_move);
	पूर्ण
	spin_unlock(&adev->mman.bdev.lru_lock);

	vm->bulk_moveable = true;
पूर्ण

/**
 * amdgpu_vm_validate_pt_bos - validate the page table BOs
 *
 * @adev: amdgpu device poपूर्णांकer
 * @vm: vm providing the BOs
 * @validate: callback to करो the validation
 * @param: parameter क्रम the validation callback
 *
 * Validate the page table BOs on command submission अगर neccessary.
 *
 * Returns:
 * Validation result.
 */
पूर्णांक amdgpu_vm_validate_pt_bos(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm,
			      पूर्णांक (*validate)(व्योम *p, काष्ठा amdgpu_bo *bo),
			      व्योम *param)
अणु
	काष्ठा amdgpu_vm_bo_base *bo_base, *पंचांगp;
	पूर्णांक r;

	vm->bulk_moveable &= list_empty(&vm->evicted);

	list_क्रम_each_entry_safe(bo_base, पंचांगp, &vm->evicted, vm_status) अणु
		काष्ठा amdgpu_bo *bo = bo_base->bo;

		r = validate(param, bo);
		अगर (r)
			वापस r;

		अगर (bo->tbo.type != tपंचांग_bo_type_kernel) अणु
			amdgpu_vm_bo_moved(bo_base);
		पूर्ण अन्यथा अणु
			vm->update_funcs->map_table(bo);
			amdgpu_vm_bo_relocated(bo_base);
		पूर्ण
	पूर्ण

	amdgpu_vm_eviction_lock(vm);
	vm->evicting = false;
	amdgpu_vm_eviction_unlock(vm);

	वापस 0;
पूर्ण

/**
 * amdgpu_vm_पढ़ोy - check VM is पढ़ोy क्रम updates
 *
 * @vm: VM to check
 *
 * Check अगर all VM PDs/PTs are पढ़ोy क्रम updates
 *
 * Returns:
 * True अगर eviction list is empty.
 */
bool amdgpu_vm_पढ़ोy(काष्ठा amdgpu_vm *vm)
अणु
	वापस list_empty(&vm->evicted);
पूर्ण

/**
 * amdgpu_vm_clear_bo - initially clear the PDs/PTs
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: VM to clear BO from
 * @bo: BO to clear
 * @immediate: use an immediate update
 *
 * Root PD needs to be reserved when calling this.
 *
 * Returns:
 * 0 on success, त्रुटि_सं otherwise.
 */
अटल पूर्णांक amdgpu_vm_clear_bo(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_vm *vm,
			      काष्ठा amdgpu_bo *bo,
			      bool immediate)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु true, false पूर्ण;
	अचिन्हित level = adev->vm_manager.root_level;
	काष्ठा amdgpu_vm_update_params params;
	काष्ठा amdgpu_bo *ancestor = bo;
	अचिन्हित entries, ats_entries;
	uपूर्णांक64_t addr;
	पूर्णांक r;

	/* Figure out our place in the hierarchy */
	अगर (ancestor->parent) अणु
		++level;
		जबतक (ancestor->parent->parent) अणु
			++level;
			ancestor = ancestor->parent;
		पूर्ण
	पूर्ण

	entries = amdgpu_bo_size(bo) / 8;
	अगर (!vm->pte_support_ats) अणु
		ats_entries = 0;

	पूर्ण अन्यथा अगर (!bo->parent) अणु
		ats_entries = amdgpu_vm_num_ats_entries(adev);
		ats_entries = min(ats_entries, entries);
		entries -= ats_entries;

	पूर्ण अन्यथा अणु
		काष्ठा amdgpu_vm_pt *pt;

		pt = container_of(ancestor->vm_bo, काष्ठा amdgpu_vm_pt, base);
		ats_entries = amdgpu_vm_num_ats_entries(adev);
		अगर ((pt - vm->root.entries) >= ats_entries) अणु
			ats_entries = 0;
		पूर्ण अन्यथा अणु
			ats_entries = entries;
			entries = 0;
		पूर्ण
	पूर्ण

	r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
	अगर (r)
		वापस r;

	अगर (bo->shaकरोw) अणु
		r = tपंचांग_bo_validate(&bo->shaकरोw->tbo, &bo->shaकरोw->placement,
				    &ctx);
		अगर (r)
			वापस r;
	पूर्ण

	r = vm->update_funcs->map_table(bo);
	अगर (r)
		वापस r;

	स_रखो(&params, 0, माप(params));
	params.adev = adev;
	params.vm = vm;
	params.immediate = immediate;

	r = vm->update_funcs->prepare(&params, शून्य, AMDGPU_SYNC_EXPLICIT);
	अगर (r)
		वापस r;

	addr = 0;
	अगर (ats_entries) अणु
		uपूर्णांक64_t value = 0, flags;

		flags = AMDGPU_PTE_DEFAULT_ATC;
		अगर (level != AMDGPU_VM_PTB) अणु
			/* Handle leaf PDEs as PTEs */
			flags |= AMDGPU_PDE_PTE;
			amdgpu_gmc_get_vm_pde(adev, level, &value, &flags);
		पूर्ण

		r = vm->update_funcs->update(&params, bo, addr, 0, ats_entries,
					     value, flags);
		अगर (r)
			वापस r;

		addr += ats_entries * 8;
	पूर्ण

	अगर (entries) अणु
		uपूर्णांक64_t value = 0, flags = 0;

		अगर (adev->asic_type >= CHIP_VEGA10) अणु
			अगर (level != AMDGPU_VM_PTB) अणु
				/* Handle leaf PDEs as PTEs */
				flags |= AMDGPU_PDE_PTE;
				amdgpu_gmc_get_vm_pde(adev, level,
						      &value, &flags);
			पूर्ण अन्यथा अणु
				/* Workaround क्रम fault priority problem on GMC9 */
				flags = AMDGPU_PTE_EXECUTABLE;
			पूर्ण
		पूर्ण

		r = vm->update_funcs->update(&params, bo, addr, 0, entries,
					     value, flags);
		अगर (r)
			वापस r;
	पूर्ण

	वापस vm->update_funcs->commit(&params, शून्य);
पूर्ण

/**
 * amdgpu_vm_bo_param - fill in parameters क्रम PD/PT allocation
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: requesting vm
 * @level: the page table level
 * @immediate: use a immediate update
 * @bp: resulting BO allocation parameters
 */
अटल व्योम amdgpu_vm_bo_param(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm,
			       पूर्णांक level, bool immediate,
			       काष्ठा amdgpu_bo_param *bp)
अणु
	स_रखो(bp, 0, माप(*bp));

	bp->size = amdgpu_vm_bo_size(adev, level);
	bp->byte_align = AMDGPU_GPU_PAGE_SIZE;
	bp->करोमुख्य = AMDGPU_GEM_DOMAIN_VRAM;
	bp->करोमुख्य = amdgpu_bo_get_preferred_pin_करोमुख्य(adev, bp->करोमुख्य);
	bp->flags = AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS |
		AMDGPU_GEM_CREATE_CPU_GTT_USWC;
	bp->bo_ptr_size = माप(काष्ठा amdgpu_bo);
	अगर (vm->use_cpu_क्रम_update)
		bp->flags |= AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;
	अन्यथा अगर (!vm->root.base.bo || vm->root.base.bo->shaकरोw)
		bp->flags |= AMDGPU_GEM_CREATE_SHADOW;
	bp->type = tपंचांग_bo_type_kernel;
	bp->no_रुको_gpu = immediate;
	अगर (vm->root.base.bo)
		bp->resv = vm->root.base.bo->tbo.base.resv;
पूर्ण

/**
 * amdgpu_vm_alloc_pts - Allocate a specअगरic page table
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: VM to allocate page tables क्रम
 * @cursor: Which page table to allocate
 * @immediate: use an immediate update
 *
 * Make sure a specअगरic page table or directory is allocated.
 *
 * Returns:
 * 1 अगर page table needed to be allocated, 0 अगर page table was alपढ़ोy
 * allocated, negative त्रुटि_सं अगर an error occurred.
 */
अटल पूर्णांक amdgpu_vm_alloc_pts(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_vm *vm,
			       काष्ठा amdgpu_vm_pt_cursor *cursor,
			       bool immediate)
अणु
	काष्ठा amdgpu_vm_pt *entry = cursor->entry;
	काष्ठा amdgpu_bo_param bp;
	काष्ठा amdgpu_bo *pt;
	पूर्णांक r;

	अगर (cursor->level < AMDGPU_VM_PTB && !entry->entries) अणु
		अचिन्हित num_entries;

		num_entries = amdgpu_vm_num_entries(adev, cursor->level);
		entry->entries = kvदो_स्मृति_array(num_entries,
						माप(*entry->entries),
						GFP_KERNEL | __GFP_ZERO);
		अगर (!entry->entries)
			वापस -ENOMEM;
	पूर्ण

	अगर (entry->base.bo)
		वापस 0;

	amdgpu_vm_bo_param(adev, vm, cursor->level, immediate, &bp);

	r = amdgpu_bo_create(adev, &bp, &pt);
	अगर (r)
		वापस r;

	/* Keep a reference to the root directory to aव्योम
	 * मुक्तing them up in the wrong order.
	 */
	pt->parent = amdgpu_bo_ref(cursor->parent->base.bo);
	amdgpu_vm_bo_base_init(&entry->base, vm, pt);

	r = amdgpu_vm_clear_bo(adev, vm, pt, immediate);
	अगर (r)
		जाओ error_मुक्त_pt;

	वापस 0;

error_मुक्त_pt:
	amdgpu_bo_unref(&pt->shaकरोw);
	amdgpu_bo_unref(&pt);
	वापस r;
पूर्ण

/**
 * amdgpu_vm_मुक्त_table - fre one PD/PT
 *
 * @entry: PDE to मुक्त
 */
अटल व्योम amdgpu_vm_मुक्त_table(काष्ठा amdgpu_vm_pt *entry)
अणु
	अगर (entry->base.bo) अणु
		entry->base.bo->vm_bo = शून्य;
		list_del(&entry->base.vm_status);
		amdgpu_bo_unref(&entry->base.bo->shaकरोw);
		amdgpu_bo_unref(&entry->base.bo);
	पूर्ण
	kvमुक्त(entry->entries);
	entry->entries = शून्य;
पूर्ण

/**
 * amdgpu_vm_मुक्त_pts - मुक्त PD/PT levels
 *
 * @adev: amdgpu device काष्ठाure
 * @vm: amdgpu vm काष्ठाure
 * @start: optional cursor where to start मुक्तing PDs/PTs
 *
 * Free the page directory or page table level and all sub levels.
 */
अटल व्योम amdgpu_vm_मुक्त_pts(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_vm *vm,
			       काष्ठा amdgpu_vm_pt_cursor *start)
अणु
	काष्ठा amdgpu_vm_pt_cursor cursor;
	काष्ठा amdgpu_vm_pt *entry;

	vm->bulk_moveable = false;

	क्रम_each_amdgpu_vm_pt_dfs_safe(adev, vm, start, cursor, entry)
		amdgpu_vm_मुक्त_table(entry);

	अगर (start)
		amdgpu_vm_मुक्त_table(start->entry);
पूर्ण

/**
 * amdgpu_vm_check_compute_bug - check whether asic has compute vm bug
 *
 * @adev: amdgpu_device poपूर्णांकer
 */
व्योम amdgpu_vm_check_compute_bug(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा amdgpu_ip_block *ip_block;
	bool has_compute_vm_bug;
	काष्ठा amdgpu_ring *ring;
	पूर्णांक i;

	has_compute_vm_bug = false;

	ip_block = amdgpu_device_ip_get_ip_block(adev, AMD_IP_BLOCK_TYPE_GFX);
	अगर (ip_block) अणु
		/* Compute has a VM bug क्रम GFX version < 7.
		   Compute has a VM bug क्रम GFX 8 MEC firmware version < 673.*/
		अगर (ip_block->version->major <= 7)
			has_compute_vm_bug = true;
		अन्यथा अगर (ip_block->version->major == 8)
			अगर (adev->gfx.mec_fw_version < 673)
				has_compute_vm_bug = true;
	पूर्ण

	क्रम (i = 0; i < adev->num_rings; i++) अणु
		ring = adev->rings[i];
		अगर (ring->funcs->type == AMDGPU_RING_TYPE_COMPUTE)
			/* only compute rings */
			ring->has_compute_vm_bug = has_compute_vm_bug;
		अन्यथा
			ring->has_compute_vm_bug = false;
	पूर्ण
पूर्ण

/**
 * amdgpu_vm_need_pipeline_sync - Check अगर pipe sync is needed क्रम job.
 *
 * @ring: ring on which the job will be submitted
 * @job: job to submit
 *
 * Returns:
 * True अगर sync is needed.
 */
bool amdgpu_vm_need_pipeline_sync(काष्ठा amdgpu_ring *ring,
				  काष्ठा amdgpu_job *job)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	अचिन्हित vmhub = ring->funcs->vmhub;
	काष्ठा amdgpu_vmid_mgr *id_mgr = &adev->vm_manager.id_mgr[vmhub];
	काष्ठा amdgpu_vmid *id;
	bool gds_चयन_needed;
	bool vm_flush_needed = job->vm_needs_flush || ring->has_compute_vm_bug;

	अगर (job->vmid == 0)
		वापस false;
	id = &id_mgr->ids[job->vmid];
	gds_चयन_needed = ring->funcs->emit_gds_चयन && (
		id->gds_base != job->gds_base ||
		id->gds_size != job->gds_size ||
		id->gws_base != job->gws_base ||
		id->gws_size != job->gws_size ||
		id->oa_base != job->oa_base ||
		id->oa_size != job->oa_size);

	अगर (amdgpu_vmid_had_gpu_reset(adev, id))
		वापस true;

	वापस vm_flush_needed || gds_चयन_needed;
पूर्ण

/**
 * amdgpu_vm_flush - hardware flush the vm
 *
 * @ring: ring to use क्रम flush
 * @job:  related job
 * @need_pipe_sync: is pipe sync needed
 *
 * Emit a VM flush when it is necessary.
 *
 * Returns:
 * 0 on success, त्रुटि_सं otherwise.
 */
पूर्णांक amdgpu_vm_flush(काष्ठा amdgpu_ring *ring, काष्ठा amdgpu_job *job,
		    bool need_pipe_sync)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	अचिन्हित vmhub = ring->funcs->vmhub;
	काष्ठा amdgpu_vmid_mgr *id_mgr = &adev->vm_manager.id_mgr[vmhub];
	काष्ठा amdgpu_vmid *id = &id_mgr->ids[job->vmid];
	bool gds_चयन_needed = ring->funcs->emit_gds_चयन && (
		id->gds_base != job->gds_base ||
		id->gds_size != job->gds_size ||
		id->gws_base != job->gws_base ||
		id->gws_size != job->gws_size ||
		id->oa_base != job->oa_base ||
		id->oa_size != job->oa_size);
	bool vm_flush_needed = job->vm_needs_flush;
	काष्ठा dma_fence *fence = शून्य;
	bool pasid_mapping_needed = false;
	अचिन्हित patch_offset = 0;
	bool update_spm_vmid_needed = (job->vm && (job->vm->reserved_vmid[vmhub] != शून्य));
	पूर्णांक r;

	अगर (update_spm_vmid_needed && adev->gfx.rlc.funcs->update_spm_vmid)
		adev->gfx.rlc.funcs->update_spm_vmid(adev, job->vmid);

	अगर (amdgpu_vmid_had_gpu_reset(adev, id)) अणु
		gds_चयन_needed = true;
		vm_flush_needed = true;
		pasid_mapping_needed = true;
	पूर्ण

	mutex_lock(&id_mgr->lock);
	अगर (id->pasid != job->pasid || !id->pasid_mapping ||
	    !dma_fence_is_संकेतed(id->pasid_mapping))
		pasid_mapping_needed = true;
	mutex_unlock(&id_mgr->lock);

	gds_चयन_needed &= !!ring->funcs->emit_gds_चयन;
	vm_flush_needed &= !!ring->funcs->emit_vm_flush  &&
			job->vm_pd_addr != AMDGPU_BO_INVALID_OFFSET;
	pasid_mapping_needed &= adev->gmc.gmc_funcs->emit_pasid_mapping &&
		ring->funcs->emit_wreg;

	अगर (!vm_flush_needed && !gds_चयन_needed && !need_pipe_sync)
		वापस 0;

	अगर (ring->funcs->init_cond_exec)
		patch_offset = amdgpu_ring_init_cond_exec(ring);

	अगर (need_pipe_sync)
		amdgpu_ring_emit_pipeline_sync(ring);

	अगर (vm_flush_needed) अणु
		trace_amdgpu_vm_flush(ring, job->vmid, job->vm_pd_addr);
		amdgpu_ring_emit_vm_flush(ring, job->vmid, job->vm_pd_addr);
	पूर्ण

	अगर (pasid_mapping_needed)
		amdgpu_gmc_emit_pasid_mapping(ring, job->vmid, job->pasid);

	अगर (vm_flush_needed || pasid_mapping_needed) अणु
		r = amdgpu_fence_emit(ring, &fence, 0);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (vm_flush_needed) अणु
		mutex_lock(&id_mgr->lock);
		dma_fence_put(id->last_flush);
		id->last_flush = dma_fence_get(fence);
		id->current_gpu_reset_count =
			atomic_पढ़ो(&adev->gpu_reset_counter);
		mutex_unlock(&id_mgr->lock);
	पूर्ण

	अगर (pasid_mapping_needed) अणु
		mutex_lock(&id_mgr->lock);
		id->pasid = job->pasid;
		dma_fence_put(id->pasid_mapping);
		id->pasid_mapping = dma_fence_get(fence);
		mutex_unlock(&id_mgr->lock);
	पूर्ण
	dma_fence_put(fence);

	अगर (ring->funcs->emit_gds_चयन && gds_चयन_needed) अणु
		id->gds_base = job->gds_base;
		id->gds_size = job->gds_size;
		id->gws_base = job->gws_base;
		id->gws_size = job->gws_size;
		id->oa_base = job->oa_base;
		id->oa_size = job->oa_size;
		amdgpu_ring_emit_gds_चयन(ring, job->vmid, job->gds_base,
					    job->gds_size, job->gws_base,
					    job->gws_size, job->oa_base,
					    job->oa_size);
	पूर्ण

	अगर (ring->funcs->patch_cond_exec)
		amdgpu_ring_patch_cond_exec(ring, patch_offset);

	/* the द्विगुन SWITCH_BUFFER here *cannot* be skipped by COND_EXEC */
	अगर (ring->funcs->emit_चयन_buffer) अणु
		amdgpu_ring_emit_चयन_buffer(ring);
		amdgpu_ring_emit_चयन_buffer(ring);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_vm_bo_find - find the bo_va क्रम a specअगरic vm & bo
 *
 * @vm: requested vm
 * @bo: requested buffer object
 *
 * Find @bo inside the requested vm.
 * Search inside the @bos vm list क्रम the requested vm
 * Returns the found bo_va or शून्य अगर none is found
 *
 * Object has to be reserved!
 *
 * Returns:
 * Found bo_va or शून्य.
 */
काष्ठा amdgpu_bo_va *amdgpu_vm_bo_find(काष्ठा amdgpu_vm *vm,
				       काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_vm_bo_base *base;

	क्रम (base = bo->vm_bo; base; base = base->next) अणु
		अगर (base->vm != vm)
			जारी;

		वापस container_of(base, काष्ठा amdgpu_bo_va, base);
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * amdgpu_vm_map_gart - Resolve gart mapping of addr
 *
 * @pages_addr: optional DMA address to use क्रम lookup
 * @addr: the unmapped addr
 *
 * Look up the physical address of the page that the pte resolves
 * to.
 *
 * Returns:
 * The poपूर्णांकer क्रम the page table entry.
 */
uपूर्णांक64_t amdgpu_vm_map_gart(स्थिर dma_addr_t *pages_addr, uपूर्णांक64_t addr)
अणु
	uपूर्णांक64_t result;

	/* page table offset */
	result = pages_addr[addr >> PAGE_SHIFT];

	/* in हाल cpu page size != gpu page size*/
	result |= addr & (~PAGE_MASK);

	result &= 0xFFFFFFFFFFFFF000ULL;

	वापस result;
पूर्ण

/**
 * amdgpu_vm_update_pde - update a single level in the hierarchy
 *
 * @params: parameters क्रम the update
 * @vm: requested vm
 * @entry: entry to update
 *
 * Makes sure the requested entry in parent is up to date.
 */
अटल पूर्णांक amdgpu_vm_update_pde(काष्ठा amdgpu_vm_update_params *params,
				काष्ठा amdgpu_vm *vm,
				काष्ठा amdgpu_vm_pt *entry)
अणु
	काष्ठा amdgpu_vm_pt *parent = amdgpu_vm_pt_parent(entry);
	काष्ठा amdgpu_bo *bo = parent->base.bo, *pbo;
	uपूर्णांक64_t pde, pt, flags;
	अचिन्हित level;

	क्रम (level = 0, pbo = bo->parent; pbo; ++level)
		pbo = pbo->parent;

	level += params->adev->vm_manager.root_level;
	amdgpu_gmc_get_pde_क्रम_bo(entry->base.bo, level, &pt, &flags);
	pde = (entry - parent->entries) * 8;
	वापस vm->update_funcs->update(params, bo, pde, pt, 1, 0, flags);
पूर्ण

/**
 * amdgpu_vm_invalidate_pds - mark all PDs as invalid
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: related vm
 *
 * Mark all PD level as invalid after an error.
 */
अटल व्योम amdgpu_vm_invalidate_pds(काष्ठा amdgpu_device *adev,
				     काष्ठा amdgpu_vm *vm)
अणु
	काष्ठा amdgpu_vm_pt_cursor cursor;
	काष्ठा amdgpu_vm_pt *entry;

	क्रम_each_amdgpu_vm_pt_dfs_safe(adev, vm, शून्य, cursor, entry)
		अगर (entry->base.bo && !entry->base.moved)
			amdgpu_vm_bo_relocated(&entry->base);
पूर्ण

/**
 * amdgpu_vm_update_pdes - make sure that all directories are valid
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: requested vm
 * @immediate: submit immediately to the paging queue
 *
 * Makes sure all directories are up to date.
 *
 * Returns:
 * 0 क्रम success, error क्रम failure.
 */
पूर्णांक amdgpu_vm_update_pdes(काष्ठा amdgpu_device *adev,
			  काष्ठा amdgpu_vm *vm, bool immediate)
अणु
	काष्ठा amdgpu_vm_update_params params;
	पूर्णांक r;

	अगर (list_empty(&vm->relocated))
		वापस 0;

	स_रखो(&params, 0, माप(params));
	params.adev = adev;
	params.vm = vm;
	params.immediate = immediate;

	r = vm->update_funcs->prepare(&params, शून्य, AMDGPU_SYNC_EXPLICIT);
	अगर (r)
		वापस r;

	जबतक (!list_empty(&vm->relocated)) अणु
		काष्ठा amdgpu_vm_pt *entry;

		entry = list_first_entry(&vm->relocated, काष्ठा amdgpu_vm_pt,
					 base.vm_status);
		amdgpu_vm_bo_idle(&entry->base);

		r = amdgpu_vm_update_pde(&params, vm, entry);
		अगर (r)
			जाओ error;
	पूर्ण

	r = vm->update_funcs->commit(&params, &vm->last_update);
	अगर (r)
		जाओ error;
	वापस 0;

error:
	amdgpu_vm_invalidate_pds(adev, vm);
	वापस r;
पूर्ण

/*
 * amdgpu_vm_update_flags - figure out flags क्रम PTE updates
 *
 * Make sure to set the right flags क्रम the PTEs at the desired level.
 */
अटल व्योम amdgpu_vm_update_flags(काष्ठा amdgpu_vm_update_params *params,
				   काष्ठा amdgpu_bo *bo, अचिन्हित level,
				   uपूर्णांक64_t pe, uपूर्णांक64_t addr,
				   अचिन्हित count, uपूर्णांक32_t incr,
				   uपूर्णांक64_t flags)

अणु
	अगर (level != AMDGPU_VM_PTB) अणु
		flags |= AMDGPU_PDE_PTE;
		amdgpu_gmc_get_vm_pde(params->adev, level, &addr, &flags);

	पूर्ण अन्यथा अगर (params->adev->asic_type >= CHIP_VEGA10 &&
		   !(flags & AMDGPU_PTE_VALID) &&
		   !(flags & AMDGPU_PTE_PRT)) अणु

		/* Workaround क्रम fault priority problem on GMC9 */
		flags |= AMDGPU_PTE_EXECUTABLE;
	पूर्ण

	params->vm->update_funcs->update(params, bo, pe, addr, count, incr,
					 flags);
पूर्ण

/**
 * amdgpu_vm_fragment - get fragment क्रम PTEs
 *
 * @params: see amdgpu_vm_update_params definition
 * @start: first PTE to handle
 * @end: last PTE to handle
 * @flags: hw mapping flags
 * @frag: resulting fragment size
 * @frag_end: end of this fragment
 *
 * Returns the first possible fragment क्रम the start and end address.
 */
अटल व्योम amdgpu_vm_fragment(काष्ठा amdgpu_vm_update_params *params,
			       uपूर्णांक64_t start, uपूर्णांक64_t end, uपूर्णांक64_t flags,
			       अचिन्हित पूर्णांक *frag, uपूर्णांक64_t *frag_end)
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
	 *
	 * Starting with Vega10 the fragment size only controls the L1. The L2
	 * is now directly feed with small/huge/giant pages from the walker.
	 */
	अचिन्हित max_frag;

	अगर (params->adev->asic_type < CHIP_VEGA10)
		max_frag = params->adev->vm_manager.fragment_size;
	अन्यथा
		max_frag = 31;

	/* प्रणाली pages are non continuously */
	अगर (params->pages_addr) अणु
		*frag = 0;
		*frag_end = end;
		वापस;
	पूर्ण

	/* This पूर्णांकentionally wraps around अगर no bit is set */
	*frag = min((अचिन्हित)ffs(start) - 1, (अचिन्हित)fls64(end - start) - 1);
	अगर (*frag >= max_frag) अणु
		*frag = max_frag;
		*frag_end = end & ~((1ULL << max_frag) - 1);
	पूर्ण अन्यथा अणु
		*frag_end = start + (1 << *frag);
	पूर्ण
पूर्ण

/**
 * amdgpu_vm_update_ptes - make sure that page tables are valid
 *
 * @params: see amdgpu_vm_update_params definition
 * @start: start of GPU address range
 * @end: end of GPU address range
 * @dst: destination address to map to, the next dst inside the function
 * @flags: mapping flags
 *
 * Update the page tables in the range @start - @end.
 *
 * Returns:
 * 0 क्रम success, -EINVAL क्रम failure.
 */
अटल पूर्णांक amdgpu_vm_update_ptes(काष्ठा amdgpu_vm_update_params *params,
				 uपूर्णांक64_t start, uपूर्णांक64_t end,
				 uपूर्णांक64_t dst, uपूर्णांक64_t flags)
अणु
	काष्ठा amdgpu_device *adev = params->adev;
	काष्ठा amdgpu_vm_pt_cursor cursor;
	uपूर्णांक64_t frag_start = start, frag_end;
	अचिन्हित पूर्णांक frag;
	पूर्णांक r;

	/* figure out the initial fragment */
	amdgpu_vm_fragment(params, frag_start, end, flags, &frag, &frag_end);

	/* walk over the address space and update the PTs */
	amdgpu_vm_pt_start(adev, params->vm, start, &cursor);
	जबतक (cursor.pfn < end) अणु
		अचिन्हित shअगरt, parent_shअगरt, mask;
		uपूर्णांक64_t incr, entry_end, pe_start;
		काष्ठा amdgpu_bo *pt;

		अगर (!params->unlocked) अणु
			/* make sure that the page tables covering the
			 * address range are actually allocated
			 */
			r = amdgpu_vm_alloc_pts(params->adev, params->vm,
						&cursor, params->immediate);
			अगर (r)
				वापस r;
		पूर्ण

		shअगरt = amdgpu_vm_level_shअगरt(adev, cursor.level);
		parent_shअगरt = amdgpu_vm_level_shअगरt(adev, cursor.level - 1);
		अगर (params->unlocked) अणु
			/* Unlocked updates are only allowed on the leaves */
			अगर (amdgpu_vm_pt_descendant(adev, &cursor))
				जारी;
		पूर्ण अन्यथा अगर (adev->asic_type < CHIP_VEGA10 &&
			   (flags & AMDGPU_PTE_VALID)) अणु
			/* No huge page support beक्रमe GMC v9 */
			अगर (cursor.level != AMDGPU_VM_PTB) अणु
				अगर (!amdgpu_vm_pt_descendant(adev, &cursor))
					वापस -ENOENT;
				जारी;
			पूर्ण
		पूर्ण अन्यथा अगर (frag < shअगरt) अणु
			/* We can't use this level when the fragment size is
			 * smaller than the address shअगरt. Go to the next
			 * child entry and try again.
			 */
			अगर (amdgpu_vm_pt_descendant(adev, &cursor))
				जारी;
		पूर्ण अन्यथा अगर (frag >= parent_shअगरt) अणु
			/* If the fragment size is even larger than the parent
			 * shअगरt we should go up one level and check it again.
			 */
			अगर (!amdgpu_vm_pt_ancestor(&cursor))
				वापस -EINVAL;
			जारी;
		पूर्ण

		pt = cursor.entry->base.bo;
		अगर (!pt) अणु
			/* We need all PDs and PTs क्रम mapping something, */
			अगर (flags & AMDGPU_PTE_VALID)
				वापस -ENOENT;

			/* but unmapping something can happen at a higher
			 * level.
			 */
			अगर (!amdgpu_vm_pt_ancestor(&cursor))
				वापस -EINVAL;

			pt = cursor.entry->base.bo;
			shअगरt = parent_shअगरt;
			frag_end = max(frag_end, ALIGN(frag_start + 1,
				   1ULL << shअगरt));
		पूर्ण

		/* Looks good so far, calculate parameters क्रम the update */
		incr = (uपूर्णांक64_t)AMDGPU_GPU_PAGE_SIZE << shअगरt;
		mask = amdgpu_vm_entries_mask(adev, cursor.level);
		pe_start = ((cursor.pfn >> shअगरt) & mask) * 8;
		entry_end = ((uपूर्णांक64_t)mask + 1) << shअगरt;
		entry_end += cursor.pfn & ~(entry_end - 1);
		entry_end = min(entry_end, end);

		करो अणु
			काष्ठा amdgpu_vm *vm = params->vm;
			uपूर्णांक64_t upd_end = min(entry_end, frag_end);
			अचिन्हित nptes = (upd_end - frag_start) >> shअगरt;
			uपूर्णांक64_t upd_flags = flags | AMDGPU_PTE_FRAG(frag);

			/* This can happen when we set higher level PDs to
			 * silent to stop fault floods.
			 */
			nptes = max(nptes, 1u);

			trace_amdgpu_vm_update_ptes(params, frag_start, upd_end,
						    nptes, dst, incr, upd_flags,
						    vm->task_info.pid,
						    vm->immediate.fence_context);
			amdgpu_vm_update_flags(params, pt, cursor.level,
					       pe_start, dst, nptes, incr,
					       upd_flags);

			pe_start += nptes * 8;
			dst += nptes * incr;

			frag_start = upd_end;
			अगर (frag_start >= frag_end) अणु
				/* figure out the next fragment */
				amdgpu_vm_fragment(params, frag_start, end,
						   flags, &frag, &frag_end);
				अगर (frag < shअगरt)
					अवरोध;
			पूर्ण
		पूर्ण जबतक (frag_start < entry_end);

		अगर (amdgpu_vm_pt_descendant(adev, &cursor)) अणु
			/* Free all child entries.
			 * Update the tables with the flags and addresses and मुक्त up subsequent
			 * tables in the हाल of huge pages or मुक्तd up areas.
			 * This is the maximum you can मुक्त, because all other page tables are not
			 * completely covered by the range and so potentially still in use.
			 */
			जबतक (cursor.pfn < frag_start) अणु
				amdgpu_vm_मुक्त_pts(adev, params->vm, &cursor);
				amdgpu_vm_pt_next(adev, &cursor);
			पूर्ण

		पूर्ण अन्यथा अगर (frag >= shअगरt) अणु
			/* or just move on to the next on the same level. */
			amdgpu_vm_pt_next(adev, &cursor);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_vm_bo_update_mapping - update a mapping in the vm page table
 *
 * @adev: amdgpu_device poपूर्णांकer of the VM
 * @bo_adev: amdgpu_device poपूर्णांकer of the mapped BO
 * @vm: requested vm
 * @immediate: immediate submission in a page fault
 * @unlocked: unlocked invalidation during MM callback
 * @resv: fences we need to sync to
 * @start: start of mapped range
 * @last: last mapped entry
 * @flags: flags क्रम the entries
 * @offset: offset पूर्णांकo nodes and pages_addr
 * @nodes: array of drm_mm_nodes with the MC addresses
 * @pages_addr: DMA addresses to use क्रम mapping
 * @fence: optional resulting fence
 *
 * Fill in the page table entries between @start and @last.
 *
 * Returns:
 * 0 क्रम success, -EINVAL क्रम failure.
 */
अटल पूर्णांक amdgpu_vm_bo_update_mapping(काष्ठा amdgpu_device *adev,
				       काष्ठा amdgpu_device *bo_adev,
				       काष्ठा amdgpu_vm *vm, bool immediate,
				       bool unlocked, काष्ठा dma_resv *resv,
				       uपूर्णांक64_t start, uपूर्णांक64_t last,
				       uपूर्णांक64_t flags, uपूर्णांक64_t offset,
				       काष्ठा drm_mm_node *nodes,
				       dma_addr_t *pages_addr,
				       काष्ठा dma_fence **fence)
अणु
	काष्ठा amdgpu_vm_update_params params;
	क्रमागत amdgpu_sync_mode sync_mode;
	uपूर्णांक64_t pfn;
	पूर्णांक r;

	स_रखो(&params, 0, माप(params));
	params.adev = adev;
	params.vm = vm;
	params.immediate = immediate;
	params.pages_addr = pages_addr;
	params.unlocked = unlocked;

	/* Implicitly sync to command submissions in the same VM beक्रमe
	 * unmapping. Sync to moving fences beक्रमe mapping.
	 */
	अगर (!(flags & AMDGPU_PTE_VALID))
		sync_mode = AMDGPU_SYNC_EQ_OWNER;
	अन्यथा
		sync_mode = AMDGPU_SYNC_EXPLICIT;

	pfn = offset >> PAGE_SHIFT;
	अगर (nodes) अणु
		जबतक (pfn >= nodes->size) अणु
			pfn -= nodes->size;
			++nodes;
		पूर्ण
	पूर्ण

	amdgpu_vm_eviction_lock(vm);
	अगर (vm->evicting) अणु
		r = -EBUSY;
		जाओ error_unlock;
	पूर्ण

	अगर (!unlocked && !dma_fence_is_संकेतed(vm->last_unlocked)) अणु
		काष्ठा dma_fence *पंचांगp = dma_fence_get_stub();

		amdgpu_bo_fence(vm->root.base.bo, vm->last_unlocked, true);
		swap(vm->last_unlocked, पंचांगp);
		dma_fence_put(पंचांगp);
	पूर्ण

	r = vm->update_funcs->prepare(&params, resv, sync_mode);
	अगर (r)
		जाओ error_unlock;

	करो अणु
		uपूर्णांक64_t पंचांगp, num_entries, addr;


		num_entries = last - start + 1;
		अगर (nodes) अणु
			addr = nodes->start << PAGE_SHIFT;
			num_entries = min((nodes->size - pfn) *
				AMDGPU_GPU_PAGES_IN_CPU_PAGE, num_entries);
		पूर्ण अन्यथा अणु
			addr = 0;
		पूर्ण

		अगर (pages_addr) अणु
			bool contiguous = true;

			अगर (num_entries > AMDGPU_GPU_PAGES_IN_CPU_PAGE) अणु
				uपूर्णांक64_t count;

				contiguous = pages_addr[pfn + 1] ==
					pages_addr[pfn] + PAGE_SIZE;

				पंचांगp = num_entries /
					AMDGPU_GPU_PAGES_IN_CPU_PAGE;
				क्रम (count = 2; count < पंचांगp; ++count) अणु
					uपूर्णांक64_t idx = pfn + count;

					अगर (contiguous != (pages_addr[idx] ==
					    pages_addr[idx - 1] + PAGE_SIZE))
						अवरोध;
				पूर्ण
				num_entries = count *
					AMDGPU_GPU_PAGES_IN_CPU_PAGE;
			पूर्ण

			अगर (!contiguous) अणु
				addr = pfn << PAGE_SHIFT;
				params.pages_addr = pages_addr;
			पूर्ण अन्यथा अणु
				addr = pages_addr[pfn];
				params.pages_addr = शून्य;
			पूर्ण

		पूर्ण अन्यथा अगर (flags & (AMDGPU_PTE_VALID | AMDGPU_PTE_PRT)) अणु
			addr += bo_adev->vm_manager.vram_base_offset;
			addr += pfn << PAGE_SHIFT;
		पूर्ण

		पंचांगp = start + num_entries;
		r = amdgpu_vm_update_ptes(&params, start, पंचांगp, addr, flags);
		अगर (r)
			जाओ error_unlock;

		pfn += num_entries / AMDGPU_GPU_PAGES_IN_CPU_PAGE;
		अगर (nodes && nodes->size == pfn) अणु
			pfn = 0;
			++nodes;
		पूर्ण
		start = पंचांगp;

	पूर्ण जबतक (unlikely(start != last + 1));

	r = vm->update_funcs->commit(&params, fence);

error_unlock:
	amdgpu_vm_eviction_unlock(vm);
	वापस r;
पूर्ण

/**
 * amdgpu_vm_bo_update - update all BO mappings in the vm page table
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @bo_va: requested BO and VM object
 * @clear: अगर true clear the entries
 *
 * Fill in the page table entries क्रम @bo_va.
 *
 * Returns:
 * 0 क्रम success, -EINVAL क्रम failure.
 */
पूर्णांक amdgpu_vm_bo_update(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_bo_va *bo_va,
			bool clear)
अणु
	काष्ठा amdgpu_bo *bo = bo_va->base.bo;
	काष्ठा amdgpu_vm *vm = bo_va->base.vm;
	काष्ठा amdgpu_bo_va_mapping *mapping;
	dma_addr_t *pages_addr = शून्य;
	काष्ठा tपंचांग_resource *mem;
	काष्ठा drm_mm_node *nodes;
	काष्ठा dma_fence **last_update;
	काष्ठा dma_resv *resv;
	uपूर्णांक64_t flags;
	काष्ठा amdgpu_device *bo_adev = adev;
	पूर्णांक r;

	अगर (clear || !bo) अणु
		mem = शून्य;
		nodes = शून्य;
		resv = vm->root.base.bo->tbo.base.resv;
	पूर्ण अन्यथा अणु
		काष्ठा drm_gem_object *obj = &bo->tbo.base;

		resv = bo->tbo.base.resv;
		अगर (obj->import_attach && bo_va->is_xgmi) अणु
			काष्ठा dma_buf *dma_buf = obj->import_attach->dmabuf;
			काष्ठा drm_gem_object *gobj = dma_buf->priv;
			काष्ठा amdgpu_bo *abo = gem_to_amdgpu_bo(gobj);

			अगर (abo->tbo.mem.mem_type == TTM_PL_VRAM)
				bo = gem_to_amdgpu_bo(gobj);
		पूर्ण
		mem = &bo->tbo.mem;
		nodes = mem->mm_node;
		अगर (mem->mem_type == TTM_PL_TT)
			pages_addr = bo->tbo.tपंचांग->dma_address;
	पूर्ण

	अगर (bo) अणु
		flags = amdgpu_tपंचांग_tt_pte_flags(adev, bo->tbo.tपंचांग, mem);

		अगर (amdgpu_bo_encrypted(bo))
			flags |= AMDGPU_PTE_TMZ;

		bo_adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	पूर्ण अन्यथा अणु
		flags = 0x0;
	पूर्ण

	अगर (clear || (bo && bo->tbo.base.resv ==
		      vm->root.base.bo->tbo.base.resv))
		last_update = &vm->last_update;
	अन्यथा
		last_update = &bo_va->last_pt_update;

	अगर (!clear && bo_va->base.moved) अणु
		bo_va->base.moved = false;
		list_splice_init(&bo_va->valids, &bo_va->invalids);

	पूर्ण अन्यथा अगर (bo_va->cleared != clear) अणु
		list_splice_init(&bo_va->valids, &bo_va->invalids);
	पूर्ण

	list_क्रम_each_entry(mapping, &bo_va->invalids, list) अणु
		uपूर्णांक64_t update_flags = flags;

		/* normally,bo_va->flags only contians READABLE and WIRTEABLE bit go here
		 * but in हाल of something, we filter the flags in first place
		 */
		अगर (!(mapping->flags & AMDGPU_PTE_READABLE))
			update_flags &= ~AMDGPU_PTE_READABLE;
		अगर (!(mapping->flags & AMDGPU_PTE_WRITEABLE))
			update_flags &= ~AMDGPU_PTE_WRITEABLE;

		/* Apply ASIC specअगरic mapping flags */
		amdgpu_gmc_get_vm_pte(adev, mapping, &update_flags);

		trace_amdgpu_vm_bo_update(mapping);

		r = amdgpu_vm_bo_update_mapping(adev, bo_adev, vm, false, false,
						resv, mapping->start,
						mapping->last, update_flags,
						mapping->offset, nodes,
						pages_addr, last_update);
		अगर (r)
			वापस r;
	पूर्ण

	/* If the BO is not in its preferred location add it back to
	 * the evicted list so that it माला_लो validated again on the
	 * next command submission.
	 */
	अगर (bo && bo->tbo.base.resv == vm->root.base.bo->tbo.base.resv) अणु
		uपूर्णांक32_t mem_type = bo->tbo.mem.mem_type;

		अगर (!(bo->preferred_करोमुख्यs &
		      amdgpu_mem_type_to_करोमुख्य(mem_type)))
			amdgpu_vm_bo_evicted(&bo_va->base);
		अन्यथा
			amdgpu_vm_bo_idle(&bo_va->base);
	पूर्ण अन्यथा अणु
		amdgpu_vm_bo_करोne(&bo_va->base);
	पूर्ण

	list_splice_init(&bo_va->invalids, &bo_va->valids);
	bo_va->cleared = clear;

	अगर (trace_amdgpu_vm_bo_mapping_enabled()) अणु
		list_क्रम_each_entry(mapping, &bo_va->valids, list)
			trace_amdgpu_vm_bo_mapping(mapping);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_vm_update_prt_state - update the global PRT state
 *
 * @adev: amdgpu_device poपूर्णांकer
 */
अटल व्योम amdgpu_vm_update_prt_state(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित दीर्घ flags;
	bool enable;

	spin_lock_irqsave(&adev->vm_manager.prt_lock, flags);
	enable = !!atomic_पढ़ो(&adev->vm_manager.num_prt_users);
	adev->gmc.gmc_funcs->set_prt(adev, enable);
	spin_unlock_irqrestore(&adev->vm_manager.prt_lock, flags);
पूर्ण

/**
 * amdgpu_vm_prt_get - add a PRT user
 *
 * @adev: amdgpu_device poपूर्णांकer
 */
अटल व्योम amdgpu_vm_prt_get(काष्ठा amdgpu_device *adev)
अणु
	अगर (!adev->gmc.gmc_funcs->set_prt)
		वापस;

	अगर (atomic_inc_वापस(&adev->vm_manager.num_prt_users) == 1)
		amdgpu_vm_update_prt_state(adev);
पूर्ण

/**
 * amdgpu_vm_prt_put - drop a PRT user
 *
 * @adev: amdgpu_device poपूर्णांकer
 */
अटल व्योम amdgpu_vm_prt_put(काष्ठा amdgpu_device *adev)
अणु
	अगर (atomic_dec_वापस(&adev->vm_manager.num_prt_users) == 0)
		amdgpu_vm_update_prt_state(adev);
पूर्ण

/**
 * amdgpu_vm_prt_cb - callback क्रम updating the PRT status
 *
 * @fence: fence क्रम the callback
 * @_cb: the callback function
 */
अटल व्योम amdgpu_vm_prt_cb(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *_cb)
अणु
	काष्ठा amdgpu_prt_cb *cb = container_of(_cb, काष्ठा amdgpu_prt_cb, cb);

	amdgpu_vm_prt_put(cb->adev);
	kमुक्त(cb);
पूर्ण

/**
 * amdgpu_vm_add_prt_cb - add callback क्रम updating the PRT status
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @fence: fence क्रम the callback
 */
अटल व्योम amdgpu_vm_add_prt_cb(काष्ठा amdgpu_device *adev,
				 काष्ठा dma_fence *fence)
अणु
	काष्ठा amdgpu_prt_cb *cb;

	अगर (!adev->gmc.gmc_funcs->set_prt)
		वापस;

	cb = kदो_स्मृति(माप(काष्ठा amdgpu_prt_cb), GFP_KERNEL);
	अगर (!cb) अणु
		/* Last resort when we are OOM */
		अगर (fence)
			dma_fence_रुको(fence, false);

		amdgpu_vm_prt_put(adev);
	पूर्ण अन्यथा अणु
		cb->adev = adev;
		अगर (!fence || dma_fence_add_callback(fence, &cb->cb,
						     amdgpu_vm_prt_cb))
			amdgpu_vm_prt_cb(fence, &cb->cb);
	पूर्ण
पूर्ण

/**
 * amdgpu_vm_मुक्त_mapping - मुक्त a mapping
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: requested vm
 * @mapping: mapping to be मुक्तd
 * @fence: fence of the unmap operation
 *
 * Free a mapping and make sure we decrease the PRT usage count अगर applicable.
 */
अटल व्योम amdgpu_vm_मुक्त_mapping(काष्ठा amdgpu_device *adev,
				   काष्ठा amdgpu_vm *vm,
				   काष्ठा amdgpu_bo_va_mapping *mapping,
				   काष्ठा dma_fence *fence)
अणु
	अगर (mapping->flags & AMDGPU_PTE_PRT)
		amdgpu_vm_add_prt_cb(adev, fence);
	kमुक्त(mapping);
पूर्ण

/**
 * amdgpu_vm_prt_fini - finish all prt mappings
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: requested vm
 *
 * Register a cleanup callback to disable PRT support after VM dies.
 */
अटल व्योम amdgpu_vm_prt_fini(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm)
अणु
	काष्ठा dma_resv *resv = vm->root.base.bo->tbo.base.resv;
	काष्ठा dma_fence *excl, **shared;
	अचिन्हित i, shared_count;
	पूर्णांक r;

	r = dma_resv_get_fences_rcu(resv, &excl,
					      &shared_count, &shared);
	अगर (r) अणु
		/* Not enough memory to grab the fence list, as last resort
		 * block क्रम all the fences to complete.
		 */
		dma_resv_रुको_समयout_rcu(resv, true, false,
						    MAX_SCHEDULE_TIMEOUT);
		वापस;
	पूर्ण

	/* Add a callback क्रम each fence in the reservation object */
	amdgpu_vm_prt_get(adev);
	amdgpu_vm_add_prt_cb(adev, excl);

	क्रम (i = 0; i < shared_count; ++i) अणु
		amdgpu_vm_prt_get(adev);
		amdgpu_vm_add_prt_cb(adev, shared[i]);
	पूर्ण

	kमुक्त(shared);
पूर्ण

/**
 * amdgpu_vm_clear_मुक्तd - clear मुक्तd BOs in the PT
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: requested vm
 * @fence: optional resulting fence (unchanged अगर no work needed to be करोne
 * or अगर an error occurred)
 *
 * Make sure all मुक्तd BOs are cleared in the PT.
 * PTs have to be reserved and mutex must be locked!
 *
 * Returns:
 * 0 क्रम success.
 *
 */
पूर्णांक amdgpu_vm_clear_मुक्तd(काष्ठा amdgpu_device *adev,
			  काष्ठा amdgpu_vm *vm,
			  काष्ठा dma_fence **fence)
अणु
	काष्ठा dma_resv *resv = vm->root.base.bo->tbo.base.resv;
	काष्ठा amdgpu_bo_va_mapping *mapping;
	uपूर्णांक64_t init_pte_value = 0;
	काष्ठा dma_fence *f = शून्य;
	पूर्णांक r;

	जबतक (!list_empty(&vm->मुक्तd)) अणु
		mapping = list_first_entry(&vm->मुक्तd,
			काष्ठा amdgpu_bo_va_mapping, list);
		list_del(&mapping->list);

		अगर (vm->pte_support_ats &&
		    mapping->start < AMDGPU_GMC_HOLE_START)
			init_pte_value = AMDGPU_PTE_DEFAULT_ATC;

		r = amdgpu_vm_bo_update_mapping(adev, adev, vm, false, false,
						resv, mapping->start,
						mapping->last, init_pte_value,
						0, शून्य, शून्य, &f);
		amdgpu_vm_मुक्त_mapping(adev, vm, mapping, f);
		अगर (r) अणु
			dma_fence_put(f);
			वापस r;
		पूर्ण
	पूर्ण

	अगर (fence && f) अणु
		dma_fence_put(*fence);
		*fence = f;
	पूर्ण अन्यथा अणु
		dma_fence_put(f);
	पूर्ण

	वापस 0;

पूर्ण

/**
 * amdgpu_vm_handle_moved - handle moved BOs in the PT
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: requested vm
 *
 * Make sure all BOs which are moved are updated in the PTs.
 *
 * Returns:
 * 0 क्रम success.
 *
 * PTs have to be reserved!
 */
पूर्णांक amdgpu_vm_handle_moved(काष्ठा amdgpu_device *adev,
			   काष्ठा amdgpu_vm *vm)
अणु
	काष्ठा amdgpu_bo_va *bo_va, *पंचांगp;
	काष्ठा dma_resv *resv;
	bool clear;
	पूर्णांक r;

	list_क्रम_each_entry_safe(bo_va, पंचांगp, &vm->moved, base.vm_status) अणु
		/* Per VM BOs never need to bo cleared in the page tables */
		r = amdgpu_vm_bo_update(adev, bo_va, false);
		अगर (r)
			वापस r;
	पूर्ण

	spin_lock(&vm->invalidated_lock);
	जबतक (!list_empty(&vm->invalidated)) अणु
		bo_va = list_first_entry(&vm->invalidated, काष्ठा amdgpu_bo_va,
					 base.vm_status);
		resv = bo_va->base.bo->tbo.base.resv;
		spin_unlock(&vm->invalidated_lock);

		/* Try to reserve the BO to aव्योम clearing its ptes */
		अगर (!amdgpu_vm_debug && dma_resv_trylock(resv))
			clear = false;
		/* Somebody अन्यथा is using the BO right now */
		अन्यथा
			clear = true;

		r = amdgpu_vm_bo_update(adev, bo_va, clear);
		अगर (r)
			वापस r;

		अगर (!clear)
			dma_resv_unlock(resv);
		spin_lock(&vm->invalidated_lock);
	पूर्ण
	spin_unlock(&vm->invalidated_lock);

	वापस 0;
पूर्ण

/**
 * amdgpu_vm_bo_add - add a bo to a specअगरic vm
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: requested vm
 * @bo: amdgpu buffer object
 *
 * Add @bo पूर्णांकo the requested vm.
 * Add @bo to the list of bos associated with the vm
 *
 * Returns:
 * Newly added bo_va or शून्य क्रम failure
 *
 * Object has to be reserved!
 */
काष्ठा amdgpu_bo_va *amdgpu_vm_bo_add(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_vm *vm,
				      काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_bo_va *bo_va;

	bo_va = kzalloc(माप(काष्ठा amdgpu_bo_va), GFP_KERNEL);
	अगर (bo_va == शून्य) अणु
		वापस शून्य;
	पूर्ण
	amdgpu_vm_bo_base_init(&bo_va->base, vm, bo);

	bo_va->ref_count = 1;
	INIT_LIST_HEAD(&bo_va->valids);
	INIT_LIST_HEAD(&bo_va->invalids);

	अगर (!bo)
		वापस bo_va;

	अगर (amdgpu_dmabuf_is_xgmi_accessible(adev, bo)) अणु
		bo_va->is_xgmi = true;
		/* Power up XGMI अगर it can be potentially used */
		amdgpu_xgmi_set_pstate(adev, AMDGPU_XGMI_PSTATE_MAX_VEGA20);
	पूर्ण

	वापस bo_va;
पूर्ण


/**
 * amdgpu_vm_bo_insert_map - insert a new mapping
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @bo_va: bo_va to store the address
 * @mapping: the mapping to insert
 *
 * Insert a new mapping पूर्णांकo all काष्ठाures.
 */
अटल व्योम amdgpu_vm_bo_insert_map(काष्ठा amdgpu_device *adev,
				    काष्ठा amdgpu_bo_va *bo_va,
				    काष्ठा amdgpu_bo_va_mapping *mapping)
अणु
	काष्ठा amdgpu_vm *vm = bo_va->base.vm;
	काष्ठा amdgpu_bo *bo = bo_va->base.bo;

	mapping->bo_va = bo_va;
	list_add(&mapping->list, &bo_va->invalids);
	amdgpu_vm_it_insert(mapping, &vm->va);

	अगर (mapping->flags & AMDGPU_PTE_PRT)
		amdgpu_vm_prt_get(adev);

	अगर (bo && bo->tbo.base.resv == vm->root.base.bo->tbo.base.resv &&
	    !bo_va->base.moved) अणु
		list_move(&bo_va->base.vm_status, &vm->moved);
	पूर्ण
	trace_amdgpu_vm_bo_map(bo_va, mapping);
पूर्ण

/**
 * amdgpu_vm_bo_map - map bo inside a vm
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @bo_va: bo_va to store the address
 * @saddr: where to map the BO
 * @offset: requested offset in the BO
 * @size: BO size in bytes
 * @flags: attributes of pages (पढ़ो/ग_लिखो/valid/etc.)
 *
 * Add a mapping of the BO at the specefied addr पूर्णांकo the VM.
 *
 * Returns:
 * 0 क्रम success, error क्रम failure.
 *
 * Object has to be reserved and unreserved outside!
 */
पूर्णांक amdgpu_vm_bo_map(काष्ठा amdgpu_device *adev,
		     काष्ठा amdgpu_bo_va *bo_va,
		     uपूर्णांक64_t saddr, uपूर्णांक64_t offset,
		     uपूर्णांक64_t size, uपूर्णांक64_t flags)
अणु
	काष्ठा amdgpu_bo_va_mapping *mapping, *पंचांगp;
	काष्ठा amdgpu_bo *bo = bo_va->base.bo;
	काष्ठा amdgpu_vm *vm = bo_va->base.vm;
	uपूर्णांक64_t eaddr;

	/* validate the parameters */
	अगर (saddr & ~PAGE_MASK || offset & ~PAGE_MASK ||
	    size == 0 || size & ~PAGE_MASK)
		वापस -EINVAL;

	/* make sure object fit at this offset */
	eaddr = saddr + size - 1;
	अगर (saddr >= eaddr ||
	    (bo && offset + size > amdgpu_bo_size(bo)) ||
	    (eaddr >= adev->vm_manager.max_pfn << AMDGPU_GPU_PAGE_SHIFT))
		वापस -EINVAL;

	saddr /= AMDGPU_GPU_PAGE_SIZE;
	eaddr /= AMDGPU_GPU_PAGE_SIZE;

	पंचांगp = amdgpu_vm_it_iter_first(&vm->va, saddr, eaddr);
	अगर (पंचांगp) अणु
		/* bo and पंचांगp overlap, invalid addr */
		dev_err(adev->dev, "bo %p va 0x%010Lx-0x%010Lx conflict with "
			"0x%010Lx-0x%010Lx\n", bo, saddr, eaddr,
			पंचांगp->start, पंचांगp->last + 1);
		वापस -EINVAL;
	पूर्ण

	mapping = kदो_स्मृति(माप(*mapping), GFP_KERNEL);
	अगर (!mapping)
		वापस -ENOMEM;

	mapping->start = saddr;
	mapping->last = eaddr;
	mapping->offset = offset;
	mapping->flags = flags;

	amdgpu_vm_bo_insert_map(adev, bo_va, mapping);

	वापस 0;
पूर्ण

/**
 * amdgpu_vm_bo_replace_map - map bo inside a vm, replacing existing mappings
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @bo_va: bo_va to store the address
 * @saddr: where to map the BO
 * @offset: requested offset in the BO
 * @size: BO size in bytes
 * @flags: attributes of pages (पढ़ो/ग_लिखो/valid/etc.)
 *
 * Add a mapping of the BO at the specefied addr पूर्णांकo the VM. Replace existing
 * mappings as we करो so.
 *
 * Returns:
 * 0 क्रम success, error क्रम failure.
 *
 * Object has to be reserved and unreserved outside!
 */
पूर्णांक amdgpu_vm_bo_replace_map(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_bo_va *bo_va,
			     uपूर्णांक64_t saddr, uपूर्णांक64_t offset,
			     uपूर्णांक64_t size, uपूर्णांक64_t flags)
अणु
	काष्ठा amdgpu_bo_va_mapping *mapping;
	काष्ठा amdgpu_bo *bo = bo_va->base.bo;
	uपूर्णांक64_t eaddr;
	पूर्णांक r;

	/* validate the parameters */
	अगर (saddr & ~PAGE_MASK || offset & ~PAGE_MASK ||
	    size == 0 || size & ~PAGE_MASK)
		वापस -EINVAL;

	/* make sure object fit at this offset */
	eaddr = saddr + size - 1;
	अगर (saddr >= eaddr ||
	    (bo && offset + size > amdgpu_bo_size(bo)) ||
	    (eaddr >= adev->vm_manager.max_pfn << AMDGPU_GPU_PAGE_SHIFT))
		वापस -EINVAL;

	/* Allocate all the needed memory */
	mapping = kदो_स्मृति(माप(*mapping), GFP_KERNEL);
	अगर (!mapping)
		वापस -ENOMEM;

	r = amdgpu_vm_bo_clear_mappings(adev, bo_va->base.vm, saddr, size);
	अगर (r) अणु
		kमुक्त(mapping);
		वापस r;
	पूर्ण

	saddr /= AMDGPU_GPU_PAGE_SIZE;
	eaddr /= AMDGPU_GPU_PAGE_SIZE;

	mapping->start = saddr;
	mapping->last = eaddr;
	mapping->offset = offset;
	mapping->flags = flags;

	amdgpu_vm_bo_insert_map(adev, bo_va, mapping);

	वापस 0;
पूर्ण

/**
 * amdgpu_vm_bo_unmap - हटाओ bo mapping from vm
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @bo_va: bo_va to हटाओ the address from
 * @saddr: where to the BO is mapped
 *
 * Remove a mapping of the BO at the specefied addr from the VM.
 *
 * Returns:
 * 0 क्रम success, error क्रम failure.
 *
 * Object has to be reserved and unreserved outside!
 */
पूर्णांक amdgpu_vm_bo_unmap(काष्ठा amdgpu_device *adev,
		       काष्ठा amdgpu_bo_va *bo_va,
		       uपूर्णांक64_t saddr)
अणु
	काष्ठा amdgpu_bo_va_mapping *mapping;
	काष्ठा amdgpu_vm *vm = bo_va->base.vm;
	bool valid = true;

	saddr /= AMDGPU_GPU_PAGE_SIZE;

	list_क्रम_each_entry(mapping, &bo_va->valids, list) अणु
		अगर (mapping->start == saddr)
			अवरोध;
	पूर्ण

	अगर (&mapping->list == &bo_va->valids) अणु
		valid = false;

		list_क्रम_each_entry(mapping, &bo_va->invalids, list) अणु
			अगर (mapping->start == saddr)
				अवरोध;
		पूर्ण

		अगर (&mapping->list == &bo_va->invalids)
			वापस -ENOENT;
	पूर्ण

	list_del(&mapping->list);
	amdgpu_vm_it_हटाओ(mapping, &vm->va);
	mapping->bo_va = शून्य;
	trace_amdgpu_vm_bo_unmap(bo_va, mapping);

	अगर (valid)
		list_add(&mapping->list, &vm->मुक्तd);
	अन्यथा
		amdgpu_vm_मुक्त_mapping(adev, vm, mapping,
				       bo_va->last_pt_update);

	वापस 0;
पूर्ण

/**
 * amdgpu_vm_bo_clear_mappings - हटाओ all mappings in a specअगरic range
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: VM काष्ठाure to use
 * @saddr: start of the range
 * @size: size of the range
 *
 * Remove all mappings in a range, split them as appropriate.
 *
 * Returns:
 * 0 क्रम success, error क्रम failure.
 */
पूर्णांक amdgpu_vm_bo_clear_mappings(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_vm *vm,
				uपूर्णांक64_t saddr, uपूर्णांक64_t size)
अणु
	काष्ठा amdgpu_bo_va_mapping *beक्रमe, *after, *पंचांगp, *next;
	LIST_HEAD(हटाओd);
	uपूर्णांक64_t eaddr;

	eaddr = saddr + size - 1;
	saddr /= AMDGPU_GPU_PAGE_SIZE;
	eaddr /= AMDGPU_GPU_PAGE_SIZE;

	/* Allocate all the needed memory */
	beक्रमe = kzalloc(माप(*beक्रमe), GFP_KERNEL);
	अगर (!beक्रमe)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&beक्रमe->list);

	after = kzalloc(माप(*after), GFP_KERNEL);
	अगर (!after) अणु
		kमुक्त(beक्रमe);
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&after->list);

	/* Now gather all हटाओd mappings */
	पंचांगp = amdgpu_vm_it_iter_first(&vm->va, saddr, eaddr);
	जबतक (पंचांगp) अणु
		/* Remember mapping split at the start */
		अगर (पंचांगp->start < saddr) अणु
			beक्रमe->start = पंचांगp->start;
			beक्रमe->last = saddr - 1;
			beक्रमe->offset = पंचांगp->offset;
			beक्रमe->flags = पंचांगp->flags;
			beक्रमe->bo_va = पंचांगp->bo_va;
			list_add(&beक्रमe->list, &पंचांगp->bo_va->invalids);
		पूर्ण

		/* Remember mapping split at the end */
		अगर (पंचांगp->last > eaddr) अणु
			after->start = eaddr + 1;
			after->last = पंचांगp->last;
			after->offset = पंचांगp->offset;
			after->offset += (after->start - पंचांगp->start) << PAGE_SHIFT;
			after->flags = पंचांगp->flags;
			after->bo_va = पंचांगp->bo_va;
			list_add(&after->list, &पंचांगp->bo_va->invalids);
		पूर्ण

		list_del(&पंचांगp->list);
		list_add(&पंचांगp->list, &हटाओd);

		पंचांगp = amdgpu_vm_it_iter_next(पंचांगp, saddr, eaddr);
	पूर्ण

	/* And मुक्त them up */
	list_क्रम_each_entry_safe(पंचांगp, next, &हटाओd, list) अणु
		amdgpu_vm_it_हटाओ(पंचांगp, &vm->va);
		list_del(&पंचांगp->list);

		अगर (पंचांगp->start < saddr)
		    पंचांगp->start = saddr;
		अगर (पंचांगp->last > eaddr)
		    पंचांगp->last = eaddr;

		पंचांगp->bo_va = शून्य;
		list_add(&पंचांगp->list, &vm->मुक्तd);
		trace_amdgpu_vm_bo_unmap(शून्य, पंचांगp);
	पूर्ण

	/* Insert partial mapping beक्रमe the range */
	अगर (!list_empty(&beक्रमe->list)) अणु
		amdgpu_vm_it_insert(beक्रमe, &vm->va);
		अगर (beक्रमe->flags & AMDGPU_PTE_PRT)
			amdgpu_vm_prt_get(adev);
	पूर्ण अन्यथा अणु
		kमुक्त(beक्रमe);
	पूर्ण

	/* Insert partial mapping after the range */
	अगर (!list_empty(&after->list)) अणु
		amdgpu_vm_it_insert(after, &vm->va);
		अगर (after->flags & AMDGPU_PTE_PRT)
			amdgpu_vm_prt_get(adev);
	पूर्ण अन्यथा अणु
		kमुक्त(after);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_vm_bo_lookup_mapping - find mapping by address
 *
 * @vm: the requested VM
 * @addr: the address
 *
 * Find a mapping by it's address.
 *
 * Returns:
 * The amdgpu_bo_va_mapping matching क्रम addr or शून्य
 *
 */
काष्ठा amdgpu_bo_va_mapping *amdgpu_vm_bo_lookup_mapping(काष्ठा amdgpu_vm *vm,
							 uपूर्णांक64_t addr)
अणु
	वापस amdgpu_vm_it_iter_first(&vm->va, addr, addr);
पूर्ण

/**
 * amdgpu_vm_bo_trace_cs - trace all reserved mappings
 *
 * @vm: the requested vm
 * @ticket: CS ticket
 *
 * Trace all mappings of BOs reserved during a command submission.
 */
व्योम amdgpu_vm_bo_trace_cs(काष्ठा amdgpu_vm *vm, काष्ठा ww_acquire_ctx *ticket)
अणु
	काष्ठा amdgpu_bo_va_mapping *mapping;

	अगर (!trace_amdgpu_vm_bo_cs_enabled())
		वापस;

	क्रम (mapping = amdgpu_vm_it_iter_first(&vm->va, 0, U64_MAX); mapping;
	     mapping = amdgpu_vm_it_iter_next(mapping, 0, U64_MAX)) अणु
		अगर (mapping->bo_va && mapping->bo_va->base.bo) अणु
			काष्ठा amdgpu_bo *bo;

			bo = mapping->bo_va->base.bo;
			अगर (dma_resv_locking_ctx(bo->tbo.base.resv) !=
			    ticket)
				जारी;
		पूर्ण

		trace_amdgpu_vm_bo_cs(mapping);
	पूर्ण
पूर्ण

/**
 * amdgpu_vm_bo_rmv - हटाओ a bo to a specअगरic vm
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @bo_va: requested bo_va
 *
 * Remove @bo_va->bo from the requested vm.
 *
 * Object have to be reserved!
 */
व्योम amdgpu_vm_bo_rmv(काष्ठा amdgpu_device *adev,
		      काष्ठा amdgpu_bo_va *bo_va)
अणु
	काष्ठा amdgpu_bo_va_mapping *mapping, *next;
	काष्ठा amdgpu_bo *bo = bo_va->base.bo;
	काष्ठा amdgpu_vm *vm = bo_va->base.vm;
	काष्ठा amdgpu_vm_bo_base **base;

	अगर (bo) अणु
		अगर (bo->tbo.base.resv == vm->root.base.bo->tbo.base.resv)
			vm->bulk_moveable = false;

		क्रम (base = &bo_va->base.bo->vm_bo; *base;
		     base = &(*base)->next) अणु
			अगर (*base != &bo_va->base)
				जारी;

			*base = bo_va->base.next;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_lock(&vm->invalidated_lock);
	list_del(&bo_va->base.vm_status);
	spin_unlock(&vm->invalidated_lock);

	list_क्रम_each_entry_safe(mapping, next, &bo_va->valids, list) अणु
		list_del(&mapping->list);
		amdgpu_vm_it_हटाओ(mapping, &vm->va);
		mapping->bo_va = शून्य;
		trace_amdgpu_vm_bo_unmap(bo_va, mapping);
		list_add(&mapping->list, &vm->मुक्तd);
	पूर्ण
	list_क्रम_each_entry_safe(mapping, next, &bo_va->invalids, list) अणु
		list_del(&mapping->list);
		amdgpu_vm_it_हटाओ(mapping, &vm->va);
		amdgpu_vm_मुक्त_mapping(adev, vm, mapping,
				       bo_va->last_pt_update);
	पूर्ण

	dma_fence_put(bo_va->last_pt_update);

	अगर (bo && bo_va->is_xgmi)
		amdgpu_xgmi_set_pstate(adev, AMDGPU_XGMI_PSTATE_MIN);

	kमुक्त(bo_va);
पूर्ण

/**
 * amdgpu_vm_evictable - check अगर we can evict a VM
 *
 * @bo: A page table of the VM.
 *
 * Check अगर it is possible to evict a VM.
 */
bool amdgpu_vm_evictable(काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_vm_bo_base *bo_base = bo->vm_bo;

	/* Page tables of a destroyed VM can go away immediately */
	अगर (!bo_base || !bo_base->vm)
		वापस true;

	/* Don't evict VM page tables जबतक they are busy */
	अगर (!dma_resv_test_संकेतed_rcu(bo->tbo.base.resv, true))
		वापस false;

	/* Try to block ongoing updates */
	अगर (!amdgpu_vm_eviction_trylock(bo_base->vm))
		वापस false;

	/* Don't evict VM page tables जबतक they are updated */
	अगर (!dma_fence_is_संकेतed(bo_base->vm->last_unlocked)) अणु
		amdgpu_vm_eviction_unlock(bo_base->vm);
		वापस false;
	पूर्ण

	bo_base->vm->evicting = true;
	amdgpu_vm_eviction_unlock(bo_base->vm);
	वापस true;
पूर्ण

/**
 * amdgpu_vm_bo_invalidate - mark the bo as invalid
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @bo: amdgpu buffer object
 * @evicted: is the BO evicted
 *
 * Mark @bo as invalid.
 */
व्योम amdgpu_vm_bo_invalidate(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_bo *bo, bool evicted)
अणु
	काष्ठा amdgpu_vm_bo_base *bo_base;

	/* shaकरोw bo करोesn't have bo base, its validation needs its parent */
	अगर (bo->parent && bo->parent->shaकरोw == bo)
		bo = bo->parent;

	क्रम (bo_base = bo->vm_bo; bo_base; bo_base = bo_base->next) अणु
		काष्ठा amdgpu_vm *vm = bo_base->vm;

		अगर (evicted && bo->tbo.base.resv == vm->root.base.bo->tbo.base.resv) अणु
			amdgpu_vm_bo_evicted(bo_base);
			जारी;
		पूर्ण

		अगर (bo_base->moved)
			जारी;
		bo_base->moved = true;

		अगर (bo->tbo.type == tपंचांग_bo_type_kernel)
			amdgpu_vm_bo_relocated(bo_base);
		अन्यथा अगर (bo->tbo.base.resv == vm->root.base.bo->tbo.base.resv)
			amdgpu_vm_bo_moved(bo_base);
		अन्यथा
			amdgpu_vm_bo_invalidated(bo_base);
	पूर्ण
पूर्ण

/**
 * amdgpu_vm_get_block_size - calculate VM page table size as घातer of two
 *
 * @vm_size: VM size
 *
 * Returns:
 * VM page table as घातer of two
 */
अटल uपूर्णांक32_t amdgpu_vm_get_block_size(uपूर्णांक64_t vm_size)
अणु
	/* Total bits covered by PD + PTs */
	अचिन्हित bits = ilog2(vm_size) + 18;

	/* Make sure the PD is 4K in size up to 8GB address space.
	   Above that split equal between PD and PTs */
	अगर (vm_size <= 8)
		वापस (bits - 9);
	अन्यथा
		वापस ((bits + 3) / 2);
पूर्ण

/**
 * amdgpu_vm_adjust_size - adjust vm size, block size and fragment size
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @min_vm_size: the minimum vm size in GB अगर it's set स्वतः
 * @fragment_size_शेष: Default PTE fragment size
 * @max_level: max VMPT level
 * @max_bits: max address space size in bits
 *
 */
व्योम amdgpu_vm_adjust_size(काष्ठा amdgpu_device *adev, uपूर्णांक32_t min_vm_size,
			   uपूर्णांक32_t fragment_size_शेष, अचिन्हित max_level,
			   अचिन्हित max_bits)
अणु
	अचिन्हित पूर्णांक max_size = 1 << (max_bits - 30);
	अचिन्हित पूर्णांक vm_size;
	uपूर्णांक64_t पंचांगp;

	/* adjust vm size first */
	अगर (amdgpu_vm_size != -1) अणु
		vm_size = amdgpu_vm_size;
		अगर (vm_size > max_size) अणु
			dev_warn(adev->dev, "VM size (%d) too large, max is %u GB\n",
				 amdgpu_vm_size, max_size);
			vm_size = max_size;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा sysinfo si;
		अचिन्हित पूर्णांक phys_ram_gb;

		/* Optimal VM size depends on the amount of physical
		 * RAM available. Underlying requirements and
		 * assumptions:
		 *
		 *  - Need to map प्रणाली memory and VRAM from all GPUs
		 *     - VRAM from other GPUs not known here
		 *     - Assume VRAM <= प्रणाली memory
		 *  - On GFX8 and older, VM space can be segmented क्रम
		 *    dअगरferent MTYPEs
		 *  - Need to allow room क्रम fragmentation, guard pages etc.
		 *
		 * This adds up to a rough guess of प्रणाली memory x3.
		 * Round up to घातer of two to maximize the available
		 * VM size with the given page table size.
		 */
		si_meminfo(&si);
		phys_ram_gb = ((uपूर्णांक64_t)si.totalram * si.mem_unit +
			       (1 << 30) - 1) >> 30;
		vm_size = roundup_घात_of_two(
			min(max(phys_ram_gb * 3, min_vm_size), max_size));
	पूर्ण

	adev->vm_manager.max_pfn = (uपूर्णांक64_t)vm_size << 18;

	पंचांगp = roundup_घात_of_two(adev->vm_manager.max_pfn);
	अगर (amdgpu_vm_block_size != -1)
		पंचांगp >>= amdgpu_vm_block_size - 9;
	पंचांगp = DIV_ROUND_UP(fls64(पंचांगp) - 1, 9) - 1;
	adev->vm_manager.num_level = min(max_level, (अचिन्हित)पंचांगp);
	चयन (adev->vm_manager.num_level) अणु
	हाल 3:
		adev->vm_manager.root_level = AMDGPU_VM_PDB2;
		अवरोध;
	हाल 2:
		adev->vm_manager.root_level = AMDGPU_VM_PDB1;
		अवरोध;
	हाल 1:
		adev->vm_manager.root_level = AMDGPU_VM_PDB0;
		अवरोध;
	शेष:
		dev_err(adev->dev, "VMPT only supports 2~4+1 levels\n");
	पूर्ण
	/* block size depends on vm size and hw setup*/
	अगर (amdgpu_vm_block_size != -1)
		adev->vm_manager.block_size =
			min((अचिन्हित)amdgpu_vm_block_size, max_bits
			    - AMDGPU_GPU_PAGE_SHIFT
			    - 9 * adev->vm_manager.num_level);
	अन्यथा अगर (adev->vm_manager.num_level > 1)
		adev->vm_manager.block_size = 9;
	अन्यथा
		adev->vm_manager.block_size = amdgpu_vm_get_block_size(पंचांगp);

	अगर (amdgpu_vm_fragment_size == -1)
		adev->vm_manager.fragment_size = fragment_size_शेष;
	अन्यथा
		adev->vm_manager.fragment_size = amdgpu_vm_fragment_size;

	DRM_INFO("vm size is %u GB, %u levels, block size is %u-bit, fragment size is %u-bit\n",
		 vm_size, adev->vm_manager.num_level + 1,
		 adev->vm_manager.block_size,
		 adev->vm_manager.fragment_size);
पूर्ण

/**
 * amdgpu_vm_रुको_idle - रुको क्रम the VM to become idle
 *
 * @vm: VM object to रुको क्रम
 * @समयout: समयout to रुको क्रम VM to become idle
 */
दीर्घ amdgpu_vm_रुको_idle(काष्ठा amdgpu_vm *vm, दीर्घ समयout)
अणु
	समयout = dma_resv_रुको_समयout_rcu(vm->root.base.bo->tbo.base.resv,
					    true, true, समयout);
	अगर (समयout <= 0)
		वापस समयout;

	वापस dma_fence_रुको_समयout(vm->last_unlocked, true, समयout);
पूर्ण

/**
 * amdgpu_vm_init - initialize a vm instance
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: requested vm
 * @vm_context: Indicates अगर it GFX or Compute context
 * @pasid: Process address space identअगरier
 *
 * Init @vm fields.
 *
 * Returns:
 * 0 क्रम success, error क्रम failure.
 */
पूर्णांक amdgpu_vm_init(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm,
		   पूर्णांक vm_context, u32 pasid)
अणु
	काष्ठा amdgpu_bo_param bp;
	काष्ठा amdgpu_bo *root;
	पूर्णांक r, i;

	vm->va = RB_ROOT_CACHED;
	क्रम (i = 0; i < AMDGPU_MAX_VMHUBS; i++)
		vm->reserved_vmid[i] = शून्य;
	INIT_LIST_HEAD(&vm->evicted);
	INIT_LIST_HEAD(&vm->relocated);
	INIT_LIST_HEAD(&vm->moved);
	INIT_LIST_HEAD(&vm->idle);
	INIT_LIST_HEAD(&vm->invalidated);
	spin_lock_init(&vm->invalidated_lock);
	INIT_LIST_HEAD(&vm->मुक्तd);
	INIT_LIST_HEAD(&vm->करोne);

	/* create scheduler entities क्रम page table updates */
	r = drm_sched_entity_init(&vm->immediate, DRM_SCHED_PRIORITY_NORMAL,
				  adev->vm_manager.vm_pte_scheds,
				  adev->vm_manager.vm_pte_num_scheds, शून्य);
	अगर (r)
		वापस r;

	r = drm_sched_entity_init(&vm->delayed, DRM_SCHED_PRIORITY_NORMAL,
				  adev->vm_manager.vm_pte_scheds,
				  adev->vm_manager.vm_pte_num_scheds, शून्य);
	अगर (r)
		जाओ error_मुक्त_immediate;

	vm->pte_support_ats = false;
	vm->is_compute_context = false;

	अगर (vm_context == AMDGPU_VM_CONTEXT_COMPUTE) अणु
		vm->use_cpu_क्रम_update = !!(adev->vm_manager.vm_update_mode &
						AMDGPU_VM_USE_CPU_FOR_COMPUTE);

		अगर (adev->asic_type == CHIP_RAVEN)
			vm->pte_support_ats = true;
	पूर्ण अन्यथा अणु
		vm->use_cpu_क्रम_update = !!(adev->vm_manager.vm_update_mode &
						AMDGPU_VM_USE_CPU_FOR_GFX);
	पूर्ण
	DRM_DEBUG_DRIVER("VM update mode is %s\n",
			 vm->use_cpu_क्रम_update ? "CPU" : "SDMA");
	WARN_ONCE((vm->use_cpu_क्रम_update &&
		   !amdgpu_gmc_vram_full_visible(&adev->gmc)),
		  "CPU update of VM recommended only for large BAR system\n");

	अगर (vm->use_cpu_क्रम_update)
		vm->update_funcs = &amdgpu_vm_cpu_funcs;
	अन्यथा
		vm->update_funcs = &amdgpu_vm_sdma_funcs;
	vm->last_update = शून्य;
	vm->last_unlocked = dma_fence_get_stub();

	mutex_init(&vm->eviction_lock);
	vm->evicting = false;

	amdgpu_vm_bo_param(adev, vm, adev->vm_manager.root_level, false, &bp);
	अगर (vm_context == AMDGPU_VM_CONTEXT_COMPUTE)
		bp.flags &= ~AMDGPU_GEM_CREATE_SHADOW;
	r = amdgpu_bo_create(adev, &bp, &root);
	अगर (r)
		जाओ error_मुक्त_delayed;

	r = amdgpu_bo_reserve(root, true);
	अगर (r)
		जाओ error_मुक्त_root;

	r = dma_resv_reserve_shared(root->tbo.base.resv, 1);
	अगर (r)
		जाओ error_unreserve;

	amdgpu_vm_bo_base_init(&vm->root.base, vm, root);

	r = amdgpu_vm_clear_bo(adev, vm, root, false);
	अगर (r)
		जाओ error_unreserve;

	amdgpu_bo_unreserve(vm->root.base.bo);

	अगर (pasid) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&adev->vm_manager.pasid_lock, flags);
		r = idr_alloc(&adev->vm_manager.pasid_idr, vm, pasid, pasid + 1,
			      GFP_ATOMIC);
		spin_unlock_irqrestore(&adev->vm_manager.pasid_lock, flags);
		अगर (r < 0)
			जाओ error_मुक्त_root;

		vm->pasid = pasid;
	पूर्ण

	INIT_KFIFO(vm->faults);

	वापस 0;

error_unreserve:
	amdgpu_bo_unreserve(vm->root.base.bo);

error_मुक्त_root:
	amdgpu_bo_unref(&vm->root.base.bo->shaकरोw);
	amdgpu_bo_unref(&vm->root.base.bo);
	vm->root.base.bo = शून्य;

error_मुक्त_delayed:
	dma_fence_put(vm->last_unlocked);
	drm_sched_entity_destroy(&vm->delayed);

error_मुक्त_immediate:
	drm_sched_entity_destroy(&vm->immediate);

	वापस r;
पूर्ण

/**
 * amdgpu_vm_check_clean_reserved - check अगर a VM is clean
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: the VM to check
 *
 * check all entries of the root PD, अगर any subsequent PDs are allocated,
 * it means there are page table creating and filling, and is no a clean
 * VM
 *
 * Returns:
 *	0 अगर this VM is clean
 */
अटल पूर्णांक amdgpu_vm_check_clean_reserved(काष्ठा amdgpu_device *adev,
	काष्ठा amdgpu_vm *vm)
अणु
	क्रमागत amdgpu_vm_level root = adev->vm_manager.root_level;
	अचिन्हित पूर्णांक entries = amdgpu_vm_num_entries(adev, root);
	अचिन्हित पूर्णांक i = 0;

	अगर (!(vm->root.entries))
		वापस 0;

	क्रम (i = 0; i < entries; i++) अणु
		अगर (vm->root.entries[i].base.bo)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_vm_make_compute - Turn a GFX VM पूर्णांकo a compute VM
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: requested vm
 * @pasid: pasid to use
 *
 * This only works on GFX VMs that करोn't have any BOs added and no
 * page tables allocated yet.
 *
 * Changes the following VM parameters:
 * - use_cpu_क्रम_update
 * - pte_supports_ats
 * - pasid (old PASID is released, because compute manages its own PASIDs)
 *
 * Reinitializes the page directory to reflect the changed ATS
 * setting.
 *
 * Returns:
 * 0 क्रम success, -त्रुटि_सं क्रम errors.
 */
पूर्णांक amdgpu_vm_make_compute(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm,
			   u32 pasid)
अणु
	bool pte_support_ats = (adev->asic_type == CHIP_RAVEN);
	पूर्णांक r;

	r = amdgpu_bo_reserve(vm->root.base.bo, true);
	अगर (r)
		वापस r;

	/* Sanity checks */
	r = amdgpu_vm_check_clean_reserved(adev, vm);
	अगर (r)
		जाओ unreserve_bo;

	अगर (pasid) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&adev->vm_manager.pasid_lock, flags);
		r = idr_alloc(&adev->vm_manager.pasid_idr, vm, pasid, pasid + 1,
			      GFP_ATOMIC);
		spin_unlock_irqrestore(&adev->vm_manager.pasid_lock, flags);

		अगर (r == -ENOSPC)
			जाओ unreserve_bo;
		r = 0;
	पूर्ण

	/* Check अगर PD needs to be reinitialized and करो it beक्रमe
	 * changing any other state, in हाल it fails.
	 */
	अगर (pte_support_ats != vm->pte_support_ats) अणु
		vm->pte_support_ats = pte_support_ats;
		r = amdgpu_vm_clear_bo(adev, vm, vm->root.base.bo, false);
		अगर (r)
			जाओ मुक्त_idr;
	पूर्ण

	/* Update VM state */
	vm->use_cpu_क्रम_update = !!(adev->vm_manager.vm_update_mode &
				    AMDGPU_VM_USE_CPU_FOR_COMPUTE);
	DRM_DEBUG_DRIVER("VM update mode is %s\n",
			 vm->use_cpu_क्रम_update ? "CPU" : "SDMA");
	WARN_ONCE((vm->use_cpu_क्रम_update &&
		   !amdgpu_gmc_vram_full_visible(&adev->gmc)),
		  "CPU update of VM recommended only for large BAR system\n");

	अगर (vm->use_cpu_क्रम_update) अणु
		/* Sync with last SDMA update/clear beक्रमe चयनing to CPU */
		r = amdgpu_bo_sync_रुको(vm->root.base.bo,
					AMDGPU_FENCE_OWNER_UNDEFINED, true);
		अगर (r)
			जाओ मुक्त_idr;

		vm->update_funcs = &amdgpu_vm_cpu_funcs;
	पूर्ण अन्यथा अणु
		vm->update_funcs = &amdgpu_vm_sdma_funcs;
	पूर्ण
	dma_fence_put(vm->last_update);
	vm->last_update = शून्य;
	vm->is_compute_context = true;

	अगर (vm->pasid) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&adev->vm_manager.pasid_lock, flags);
		idr_हटाओ(&adev->vm_manager.pasid_idr, vm->pasid);
		spin_unlock_irqrestore(&adev->vm_manager.pasid_lock, flags);

		/* Free the original amdgpu allocated pasid
		 * Will be replaced with kfd allocated pasid
		 */
		amdgpu_pasid_मुक्त(vm->pasid);
		vm->pasid = 0;
	पूर्ण

	/* Free the shaकरोw bo क्रम compute VM */
	amdgpu_bo_unref(&vm->root.base.bo->shaकरोw);

	अगर (pasid)
		vm->pasid = pasid;

	जाओ unreserve_bo;

मुक्त_idr:
	अगर (pasid) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&adev->vm_manager.pasid_lock, flags);
		idr_हटाओ(&adev->vm_manager.pasid_idr, pasid);
		spin_unlock_irqrestore(&adev->vm_manager.pasid_lock, flags);
	पूर्ण
unreserve_bo:
	amdgpu_bo_unreserve(vm->root.base.bo);
	वापस r;
पूर्ण

/**
 * amdgpu_vm_release_compute - release a compute vm
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: a vm turned पूर्णांकo compute vm by calling amdgpu_vm_make_compute
 *
 * This is a correspondant of amdgpu_vm_make_compute. It decouples compute
 * pasid from vm. Compute should stop use of vm after this call.
 */
व्योम amdgpu_vm_release_compute(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm)
अणु
	अगर (vm->pasid) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&adev->vm_manager.pasid_lock, flags);
		idr_हटाओ(&adev->vm_manager.pasid_idr, vm->pasid);
		spin_unlock_irqrestore(&adev->vm_manager.pasid_lock, flags);
	पूर्ण
	vm->pasid = 0;
	vm->is_compute_context = false;
पूर्ण

/**
 * amdgpu_vm_fini - tear करोwn a vm instance
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: requested vm
 *
 * Tear करोwn @vm.
 * Unbind the VM and हटाओ all bos from the vm bo list
 */
व्योम amdgpu_vm_fini(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm)
अणु
	काष्ठा amdgpu_bo_va_mapping *mapping, *पंचांगp;
	bool prt_fini_needed = !!adev->gmc.gmc_funcs->set_prt;
	काष्ठा amdgpu_bo *root;
	पूर्णांक i;

	amdgpu_amdkfd_gpuvm_destroy_cb(adev, vm);

	root = amdgpu_bo_ref(vm->root.base.bo);
	amdgpu_bo_reserve(root, true);
	अगर (vm->pasid) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&adev->vm_manager.pasid_lock, flags);
		idr_हटाओ(&adev->vm_manager.pasid_idr, vm->pasid);
		spin_unlock_irqrestore(&adev->vm_manager.pasid_lock, flags);
		vm->pasid = 0;
	पूर्ण

	dma_fence_रुको(vm->last_unlocked, false);
	dma_fence_put(vm->last_unlocked);

	list_क्रम_each_entry_safe(mapping, पंचांगp, &vm->मुक्तd, list) अणु
		अगर (mapping->flags & AMDGPU_PTE_PRT && prt_fini_needed) अणु
			amdgpu_vm_prt_fini(adev, vm);
			prt_fini_needed = false;
		पूर्ण

		list_del(&mapping->list);
		amdgpu_vm_मुक्त_mapping(adev, vm, mapping, शून्य);
	पूर्ण

	amdgpu_vm_मुक्त_pts(adev, vm, शून्य);
	amdgpu_bo_unreserve(root);
	amdgpu_bo_unref(&root);
	WARN_ON(vm->root.base.bo);

	drm_sched_entity_destroy(&vm->immediate);
	drm_sched_entity_destroy(&vm->delayed);

	अगर (!RB_EMPTY_ROOT(&vm->va.rb_root)) अणु
		dev_err(adev->dev, "still active bo inside vm\n");
	पूर्ण
	rbtree_postorder_क्रम_each_entry_safe(mapping, पंचांगp,
					     &vm->va.rb_root, rb) अणु
		/* Don't remove the mapping here, we don't want to trigger a
		 * rebalance and the tree is about to be destroyed anyway.
		 */
		list_del(&mapping->list);
		kमुक्त(mapping);
	पूर्ण

	dma_fence_put(vm->last_update);
	क्रम (i = 0; i < AMDGPU_MAX_VMHUBS; i++)
		amdgpu_vmid_मुक्त_reserved(adev, vm, i);
पूर्ण

/**
 * amdgpu_vm_manager_init - init the VM manager
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Initialize the VM manager काष्ठाures
 */
व्योम amdgpu_vm_manager_init(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i;

	/* Concurrent flushes are only possible starting with Vega10 and
	 * are broken on Navi10 and Navi14.
	 */
	adev->vm_manager.concurrent_flush = !(adev->asic_type < CHIP_VEGA10 ||
					      adev->asic_type == CHIP_NAVI10 ||
					      adev->asic_type == CHIP_NAVI14);
	amdgpu_vmid_mgr_init(adev);

	adev->vm_manager.fence_context =
		dma_fence_context_alloc(AMDGPU_MAX_RINGS);
	क्रम (i = 0; i < AMDGPU_MAX_RINGS; ++i)
		adev->vm_manager.seqno[i] = 0;

	spin_lock_init(&adev->vm_manager.prt_lock);
	atomic_set(&adev->vm_manager.num_prt_users, 0);

	/* If not overridden by the user, by शेष, only in large BAR प्रणालीs
	 * Compute VM tables will be updated by CPU
	 */
#अगर_घोषित CONFIG_X86_64
	अगर (amdgpu_vm_update_mode == -1) अणु
		अगर (amdgpu_gmc_vram_full_visible(&adev->gmc))
			adev->vm_manager.vm_update_mode =
				AMDGPU_VM_USE_CPU_FOR_COMPUTE;
		अन्यथा
			adev->vm_manager.vm_update_mode = 0;
	पूर्ण अन्यथा
		adev->vm_manager.vm_update_mode = amdgpu_vm_update_mode;
#अन्यथा
	adev->vm_manager.vm_update_mode = 0;
#पूर्ण_अगर

	idr_init(&adev->vm_manager.pasid_idr);
	spin_lock_init(&adev->vm_manager.pasid_lock);
पूर्ण

/**
 * amdgpu_vm_manager_fini - cleanup VM manager
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Cleanup the VM manager and मुक्त resources.
 */
व्योम amdgpu_vm_manager_fini(काष्ठा amdgpu_device *adev)
अणु
	WARN_ON(!idr_is_empty(&adev->vm_manager.pasid_idr));
	idr_destroy(&adev->vm_manager.pasid_idr);

	amdgpu_vmid_mgr_fini(adev);
पूर्ण

/**
 * amdgpu_vm_ioctl - Manages VMID reservation क्रम vm hubs.
 *
 * @dev: drm device poपूर्णांकer
 * @data: drm_amdgpu_vm
 * @filp: drm file poपूर्णांकer
 *
 * Returns:
 * 0 क्रम success, -त्रुटि_सं क्रम errors.
 */
पूर्णांक amdgpu_vm_ioctl(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *filp)
अणु
	जोड़ drm_amdgpu_vm *args = data;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_fpriv *fpriv = filp->driver_priv;
	दीर्घ समयout = msecs_to_jअगरfies(2000);
	पूर्णांक r;

	चयन (args->in.op) अणु
	हाल AMDGPU_VM_OP_RESERVE_VMID:
		/* We only have requirement to reserve vmid from gfxhub */
		r = amdgpu_vmid_alloc_reserved(adev, &fpriv->vm,
					       AMDGPU_GFXHUB_0);
		अगर (r)
			वापस r;
		अवरोध;
	हाल AMDGPU_VM_OP_UNRESERVE_VMID:
		अगर (amdgpu_sriov_runसमय(adev))
			समयout = 8 * समयout;

		/* Wait vm idle to make sure the vmid set in SPM_VMID is
		 * not referenced anymore.
		 */
		r = amdgpu_bo_reserve(fpriv->vm.root.base.bo, true);
		अगर (r)
			वापस r;

		r = amdgpu_vm_रुको_idle(&fpriv->vm, समयout);
		अगर (r < 0)
			वापस r;

		amdgpu_bo_unreserve(fpriv->vm.root.base.bo);
		amdgpu_vmid_मुक्त_reserved(adev, &fpriv->vm, AMDGPU_GFXHUB_0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_vm_get_task_info - Extracts task info क्रम a PASID.
 *
 * @adev: drm device poपूर्णांकer
 * @pasid: PASID identअगरier क्रम VM
 * @task_info: task_info to fill.
 */
व्योम amdgpu_vm_get_task_info(काष्ठा amdgpu_device *adev, u32 pasid,
			 काष्ठा amdgpu_task_info *task_info)
अणु
	काष्ठा amdgpu_vm *vm;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->vm_manager.pasid_lock, flags);

	vm = idr_find(&adev->vm_manager.pasid_idr, pasid);
	अगर (vm)
		*task_info = vm->task_info;

	spin_unlock_irqrestore(&adev->vm_manager.pasid_lock, flags);
पूर्ण

/**
 * amdgpu_vm_set_task_info - Sets VMs task info.
 *
 * @vm: vm क्रम which to set the info
 */
व्योम amdgpu_vm_set_task_info(काष्ठा amdgpu_vm *vm)
अणु
	अगर (vm->task_info.pid)
		वापस;

	vm->task_info.pid = current->pid;
	get_task_comm(vm->task_info.task_name, current);

	अगर (current->group_leader->mm != current->mm)
		वापस;

	vm->task_info.tgid = current->group_leader->pid;
	get_task_comm(vm->task_info.process_name, current->group_leader);
पूर्ण

/**
 * amdgpu_vm_handle_fault - graceful handling of VM faults.
 * @adev: amdgpu device poपूर्णांकer
 * @pasid: PASID of the VM
 * @addr: Address of the fault
 *
 * Try to gracefully handle a VM fault. Return true अगर the fault was handled and
 * shouldn't be reported any more.
 */
bool amdgpu_vm_handle_fault(काष्ठा amdgpu_device *adev, u32 pasid,
			    uपूर्णांक64_t addr)
अणु
	काष्ठा amdgpu_bo *root;
	uपूर्णांक64_t value, flags;
	काष्ठा amdgpu_vm *vm;
	पूर्णांक r;

	spin_lock(&adev->vm_manager.pasid_lock);
	vm = idr_find(&adev->vm_manager.pasid_idr, pasid);
	अगर (vm)
		root = amdgpu_bo_ref(vm->root.base.bo);
	अन्यथा
		root = शून्य;
	spin_unlock(&adev->vm_manager.pasid_lock);

	अगर (!root)
		वापस false;

	r = amdgpu_bo_reserve(root, true);
	अगर (r)
		जाओ error_unref;

	/* Double check that the VM still exists */
	spin_lock(&adev->vm_manager.pasid_lock);
	vm = idr_find(&adev->vm_manager.pasid_idr, pasid);
	अगर (vm && vm->root.base.bo != root)
		vm = शून्य;
	spin_unlock(&adev->vm_manager.pasid_lock);
	अगर (!vm)
		जाओ error_unlock;

	addr /= AMDGPU_GPU_PAGE_SIZE;
	flags = AMDGPU_PTE_VALID | AMDGPU_PTE_SNOOPED |
		AMDGPU_PTE_SYSTEM;

	अगर (vm->is_compute_context) अणु
		/* Intentionally setting invalid PTE flag
		 * combination to क्रमce a no-retry-fault
		 */
		flags = AMDGPU_PTE_EXECUTABLE | AMDGPU_PDE_PTE |
			AMDGPU_PTE_TF;
		value = 0;

	पूर्ण अन्यथा अगर (amdgpu_vm_fault_stop == AMDGPU_VM_FAULT_STOP_NEVER) अणु
		/* Redirect the access to the dummy page */
		value = adev->dummy_page_addr;
		flags |= AMDGPU_PTE_EXECUTABLE | AMDGPU_PTE_READABLE |
			AMDGPU_PTE_WRITEABLE;

	पूर्ण अन्यथा अणु
		/* Let the hw retry silently on the PTE */
		value = 0;
	पूर्ण

	r = dma_resv_reserve_shared(root->tbo.base.resv, 1);
	अगर (r) अणु
		pr_debug("failed %d to reserve fence slot\n", r);
		जाओ error_unlock;
	पूर्ण

	r = amdgpu_vm_bo_update_mapping(adev, adev, vm, true, false, शून्य, addr,
					addr, flags, value, शून्य, शून्य,
					शून्य);
	अगर (r)
		जाओ error_unlock;

	r = amdgpu_vm_update_pdes(adev, vm, true);

error_unlock:
	amdgpu_bo_unreserve(root);
	अगर (r < 0)
		DRM_ERROR("Can't handle page fault (%d)\n", r);

error_unref:
	amdgpu_bo_unref(&root);

	वापस false;
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)
/**
 * amdgpu_debugfs_vm_bo_info  - prपूर्णांक BO info क्रम the VM
 *
 * @vm: Requested VM क्रम prपूर्णांकing BO info
 * @m: debugfs file
 *
 * Prपूर्णांक BO inक्रमmation in debugfs file क्रम the VM
 */
व्योम amdgpu_debugfs_vm_bo_info(काष्ठा amdgpu_vm *vm, काष्ठा seq_file *m)
अणु
	काष्ठा amdgpu_bo_va *bo_va, *पंचांगp;
	u64 total_idle = 0;
	u64 total_evicted = 0;
	u64 total_relocated = 0;
	u64 total_moved = 0;
	u64 total_invalidated = 0;
	u64 total_करोne = 0;
	अचिन्हित पूर्णांक total_idle_objs = 0;
	अचिन्हित पूर्णांक total_evicted_objs = 0;
	अचिन्हित पूर्णांक total_relocated_objs = 0;
	अचिन्हित पूर्णांक total_moved_objs = 0;
	अचिन्हित पूर्णांक total_invalidated_objs = 0;
	अचिन्हित पूर्णांक total_करोne_objs = 0;
	अचिन्हित पूर्णांक id = 0;

	seq_माला_दो(m, "\tIdle BOs:\n");
	list_क्रम_each_entry_safe(bo_va, पंचांगp, &vm->idle, base.vm_status) अणु
		अगर (!bo_va->base.bo)
			जारी;
		total_idle += amdgpu_bo_prपूर्णांक_info(id++, bo_va->base.bo, m);
	पूर्ण
	total_idle_objs = id;
	id = 0;

	seq_माला_दो(m, "\tEvicted BOs:\n");
	list_क्रम_each_entry_safe(bo_va, पंचांगp, &vm->evicted, base.vm_status) अणु
		अगर (!bo_va->base.bo)
			जारी;
		total_evicted += amdgpu_bo_prपूर्णांक_info(id++, bo_va->base.bo, m);
	पूर्ण
	total_evicted_objs = id;
	id = 0;

	seq_माला_दो(m, "\tRelocated BOs:\n");
	list_क्रम_each_entry_safe(bo_va, पंचांगp, &vm->relocated, base.vm_status) अणु
		अगर (!bo_va->base.bo)
			जारी;
		total_relocated += amdgpu_bo_prपूर्णांक_info(id++, bo_va->base.bo, m);
	पूर्ण
	total_relocated_objs = id;
	id = 0;

	seq_माला_दो(m, "\tMoved BOs:\n");
	list_क्रम_each_entry_safe(bo_va, पंचांगp, &vm->moved, base.vm_status) अणु
		अगर (!bo_va->base.bo)
			जारी;
		total_moved += amdgpu_bo_prपूर्णांक_info(id++, bo_va->base.bo, m);
	पूर्ण
	total_moved_objs = id;
	id = 0;

	seq_माला_दो(m, "\tInvalidated BOs:\n");
	spin_lock(&vm->invalidated_lock);
	list_क्रम_each_entry_safe(bo_va, पंचांगp, &vm->invalidated, base.vm_status) अणु
		अगर (!bo_va->base.bo)
			जारी;
		total_invalidated += amdgpu_bo_prपूर्णांक_info(id++,	bo_va->base.bo, m);
	पूर्ण
	total_invalidated_objs = id;
	id = 0;

	seq_माला_दो(m, "\tDone BOs:\n");
	list_क्रम_each_entry_safe(bo_va, पंचांगp, &vm->करोne, base.vm_status) अणु
		अगर (!bo_va->base.bo)
			जारी;
		total_करोne += amdgpu_bo_prपूर्णांक_info(id++, bo_va->base.bo, m);
	पूर्ण
	spin_unlock(&vm->invalidated_lock);
	total_करोne_objs = id;

	seq_म_लिखो(m, "\tTotal idle size:        %12lld\tobjs:\t%d\n", total_idle,
		   total_idle_objs);
	seq_म_लिखो(m, "\tTotal evicted size:     %12lld\tobjs:\t%d\n", total_evicted,
		   total_evicted_objs);
	seq_म_लिखो(m, "\tTotal relocated size:   %12lld\tobjs:\t%d\n", total_relocated,
		   total_relocated_objs);
	seq_म_लिखो(m, "\tTotal moved size:       %12lld\tobjs:\t%d\n", total_moved,
		   total_moved_objs);
	seq_म_लिखो(m, "\tTotal invalidated size: %12lld\tobjs:\t%d\n", total_invalidated,
		   total_invalidated_objs);
	seq_म_लिखो(m, "\tTotal done size:        %12lld\tobjs:\t%d\n", total_करोne,
		   total_करोne_objs);
पूर्ण
#पूर्ण_अगर
