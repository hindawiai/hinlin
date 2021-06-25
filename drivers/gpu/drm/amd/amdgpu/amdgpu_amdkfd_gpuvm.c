<शैली गुरु>
/*
 * Copyright 2014-2018 Advanced Micro Devices, Inc.
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
 */
#समावेश <linux/dma-buf.h>
#समावेश <linux/list.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task.h>

#समावेश "amdgpu_object.h"
#समावेश "amdgpu_gem.h"
#समावेश "amdgpu_vm.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "amdgpu_dma_buf.h"
#समावेश <uapi/linux/kfd_ioctl.h>
#समावेश "amdgpu_xgmi.h"

/* BO flag to indicate a KFD userptr BO */
#घोषणा AMDGPU_AMDKFD_USERPTR_BO (1ULL << 63)

/* Userptr restore delay, just दीर्घ enough to allow consecutive VM
 * changes to accumulate
 */
#घोषणा AMDGPU_USERPTR_RESTORE_DELAY_MS 1

/* Impose limit on how much memory KFD can use */
अटल काष्ठा अणु
	uपूर्णांक64_t max_प्रणाली_mem_limit;
	uपूर्णांक64_t max_tपंचांग_mem_limit;
	पूर्णांक64_t प्रणाली_mem_used;
	पूर्णांक64_t tपंचांग_mem_used;
	spinlock_t mem_limit_lock;
पूर्ण kfd_mem_limit;

/* Struct used क्रम amdgpu_amdkfd_bo_validate */
काष्ठा amdgpu_vm_parser अणु
	uपूर्णांक32_t        करोमुख्य;
	bool            रुको;
पूर्ण;

अटल स्थिर अक्षर * स्थिर करोमुख्य_bit_to_string[] = अणु
		"CPU",
		"GTT",
		"VRAM",
		"GDS",
		"GWS",
		"OA"
पूर्ण;

#घोषणा करोमुख्य_string(करोमुख्य) करोमुख्य_bit_to_string[ffs(करोमुख्य)-1]

अटल व्योम amdgpu_amdkfd_restore_userptr_worker(काष्ठा work_काष्ठा *work);


अटल अंतरभूत काष्ठा amdgpu_device *get_amdgpu_device(काष्ठा kgd_dev *kgd)
अणु
	वापस (काष्ठा amdgpu_device *)kgd;
पूर्ण

अटल bool check_अगर_add_bo_to_vm(काष्ठा amdgpu_vm *avm,
		काष्ठा kgd_mem *mem)
अणु
	काष्ठा kfd_bo_बहु_सूची *entry;

	list_क्रम_each_entry(entry, &mem->bo_बहु_सूची, bo_list)
		अगर (entry->bo_va->base.vm == avm)
			वापस false;

	वापस true;
पूर्ण

/* Set memory usage limits. Current, limits are
 *  System (TTM + userptr) memory - 15/16th System RAM
 *  TTM memory - 3/8th System RAM
 */
व्योम amdgpu_amdkfd_gpuvm_init_mem_limits(व्योम)
अणु
	काष्ठा sysinfo si;
	uपूर्णांक64_t mem;

	si_meminfo(&si);
	mem = si.मुक्तram - si.मुक्तhigh;
	mem *= si.mem_unit;

	spin_lock_init(&kfd_mem_limit.mem_limit_lock);
	kfd_mem_limit.max_प्रणाली_mem_limit = mem - (mem >> 4);
	kfd_mem_limit.max_tपंचांग_mem_limit = (mem >> 1) - (mem >> 3);
	pr_debug("Kernel memory limit %lluM, TTM limit %lluM\n",
		(kfd_mem_limit.max_प्रणाली_mem_limit >> 20),
		(kfd_mem_limit.max_tपंचांग_mem_limit >> 20));
पूर्ण

/* Estimate page table size needed to represent a given memory size
 *
 * With 4KB pages, we need one 8 byte PTE क्रम each 4KB of memory
 * (factor 512, >> 9). With 2MB pages, we need one 8 byte PTE क्रम 2MB
 * of memory (factor 256K, >> 18). ROCm user mode tries to optimize
 * क्रम 2MB pages क्रम TLB efficiency. However, small allocations and
 * fragmented प्रणाली memory still need some 4KB pages. We choose a
 * compromise that should work in most हालs without reserving too
 * much memory क्रम page tables unnecessarily (factor 16K, >> 14).
 */
#घोषणा ESTIMATE_PT_SIZE(mem_size) ((mem_size) >> 14)

अटल माप_प्रकार amdgpu_amdkfd_acc_size(uपूर्णांक64_t size)
अणु
	size >>= PAGE_SHIFT;
	size *= माप(dma_addr_t) + माप(व्योम *);

	वापस __roundup_घात_of_two(माप(काष्ठा amdgpu_bo)) +
		__roundup_घात_of_two(माप(काष्ठा tपंचांग_tt)) +
		PAGE_ALIGN(size);
पूर्ण

अटल पूर्णांक amdgpu_amdkfd_reserve_mem_limit(काष्ठा amdgpu_device *adev,
		uपूर्णांक64_t size, u32 करोमुख्य, bool sg)
अणु
	uपूर्णांक64_t reserved_क्रम_pt =
		ESTIMATE_PT_SIZE(amdgpu_amdkfd_total_mem_size);
	माप_प्रकार acc_size, प्रणाली_mem_needed, tपंचांग_mem_needed, vram_needed;
	पूर्णांक ret = 0;

	acc_size = amdgpu_amdkfd_acc_size(size);

	vram_needed = 0;
	अगर (करोमुख्य == AMDGPU_GEM_DOMAIN_GTT) अणु
		/* TTM GTT memory */
		प्रणाली_mem_needed = acc_size + size;
		tपंचांग_mem_needed = acc_size + size;
	पूर्ण अन्यथा अगर (करोमुख्य == AMDGPU_GEM_DOMAIN_CPU && !sg) अणु
		/* Userptr */
		प्रणाली_mem_needed = acc_size + size;
		tपंचांग_mem_needed = acc_size;
	पूर्ण अन्यथा अणु
		/* VRAM and SG */
		प्रणाली_mem_needed = acc_size;
		tपंचांग_mem_needed = acc_size;
		अगर (करोमुख्य == AMDGPU_GEM_DOMAIN_VRAM)
			vram_needed = size;
	पूर्ण

	spin_lock(&kfd_mem_limit.mem_limit_lock);

	अगर (kfd_mem_limit.प्रणाली_mem_used + प्रणाली_mem_needed >
	    kfd_mem_limit.max_प्रणाली_mem_limit)
		pr_debug("Set no_system_mem_limit=1 if using shared memory\n");

	अगर ((kfd_mem_limit.प्रणाली_mem_used + प्रणाली_mem_needed >
	     kfd_mem_limit.max_प्रणाली_mem_limit && !no_प्रणाली_mem_limit) ||
	    (kfd_mem_limit.tपंचांग_mem_used + tपंचांग_mem_needed >
	     kfd_mem_limit.max_tपंचांग_mem_limit) ||
	    (adev->kfd.vram_used + vram_needed >
	     adev->gmc.real_vram_size - reserved_क्रम_pt)) अणु
		ret = -ENOMEM;
	पूर्ण अन्यथा अणु
		kfd_mem_limit.प्रणाली_mem_used += प्रणाली_mem_needed;
		kfd_mem_limit.tपंचांग_mem_used += tपंचांग_mem_needed;
		adev->kfd.vram_used += vram_needed;
	पूर्ण

	spin_unlock(&kfd_mem_limit.mem_limit_lock);
	वापस ret;
पूर्ण

अटल व्योम unreserve_mem_limit(काष्ठा amdgpu_device *adev,
		uपूर्णांक64_t size, u32 करोमुख्य, bool sg)
अणु
	माप_प्रकार acc_size;

	acc_size = amdgpu_amdkfd_acc_size(size);

	spin_lock(&kfd_mem_limit.mem_limit_lock);
	अगर (करोमुख्य == AMDGPU_GEM_DOMAIN_GTT) अणु
		kfd_mem_limit.प्रणाली_mem_used -= (acc_size + size);
		kfd_mem_limit.tपंचांग_mem_used -= (acc_size + size);
	पूर्ण अन्यथा अगर (करोमुख्य == AMDGPU_GEM_DOMAIN_CPU && !sg) अणु
		kfd_mem_limit.प्रणाली_mem_used -= (acc_size + size);
		kfd_mem_limit.tपंचांग_mem_used -= acc_size;
	पूर्ण अन्यथा अणु
		kfd_mem_limit.प्रणाली_mem_used -= acc_size;
		kfd_mem_limit.tपंचांग_mem_used -= acc_size;
		अगर (करोमुख्य == AMDGPU_GEM_DOMAIN_VRAM) अणु
			adev->kfd.vram_used -= size;
			WARN_ONCE(adev->kfd.vram_used < 0,
				  "kfd VRAM memory accounting unbalanced");
		पूर्ण
	पूर्ण
	WARN_ONCE(kfd_mem_limit.प्रणाली_mem_used < 0,
		  "kfd system memory accounting unbalanced");
	WARN_ONCE(kfd_mem_limit.tपंचांग_mem_used < 0,
		  "kfd TTM memory accounting unbalanced");

	spin_unlock(&kfd_mem_limit.mem_limit_lock);
पूर्ण

व्योम amdgpu_amdkfd_unreserve_memory_limit(काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	u32 करोमुख्य = bo->preferred_करोमुख्यs;
	bool sg = (bo->preferred_करोमुख्यs == AMDGPU_GEM_DOMAIN_CPU);

	अगर (bo->flags & AMDGPU_AMDKFD_USERPTR_BO) अणु
		करोमुख्य = AMDGPU_GEM_DOMAIN_CPU;
		sg = false;
	पूर्ण

	unreserve_mem_limit(adev, amdgpu_bo_size(bo), करोमुख्य, sg);
पूर्ण


/* amdgpu_amdkfd_हटाओ_eviction_fence - Removes eviction fence from BO's
 *  reservation object.
 *
 * @bo: [IN] Remove eviction fence(s) from this BO
 * @ef: [IN] This eviction fence is हटाओd अगर it
 *  is present in the shared list.
 *
 * NOTE: Must be called with BO reserved i.e. bo->tbo.resv->lock held.
 */
अटल पूर्णांक amdgpu_amdkfd_हटाओ_eviction_fence(काष्ठा amdgpu_bo *bo,
					काष्ठा amdgpu_amdkfd_fence *ef)
अणु
	काष्ठा dma_resv *resv = bo->tbo.base.resv;
	काष्ठा dma_resv_list *old, *new;
	अचिन्हित पूर्णांक i, j, k;

	अगर (!ef)
		वापस -EINVAL;

	old = dma_resv_get_list(resv);
	अगर (!old)
		वापस 0;

	new = kदो_स्मृति(काष्ठा_size(new, shared, old->shared_max), GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;

	/* Go through all the shared fences in the resevation object and sort
	 * the पूर्णांकeresting ones to the end of the list.
	 */
	क्रम (i = 0, j = old->shared_count, k = 0; i < old->shared_count; ++i) अणु
		काष्ठा dma_fence *f;

		f = rcu_dereference_रक्षित(old->shared[i],
					      dma_resv_held(resv));

		अगर (f->context == ef->base.context)
			RCU_INIT_POINTER(new->shared[--j], f);
		अन्यथा
			RCU_INIT_POINTER(new->shared[k++], f);
	पूर्ण
	new->shared_max = old->shared_max;
	new->shared_count = k;

	/* Install the new fence list, seqcount provides the barriers */
	ग_लिखो_seqcount_begin(&resv->seq);
	RCU_INIT_POINTER(resv->fence, new);
	ग_लिखो_seqcount_end(&resv->seq);

	/* Drop the references to the हटाओd fences or move them to ef_list */
	क्रम (i = j, k = 0; i < old->shared_count; ++i) अणु
		काष्ठा dma_fence *f;

		f = rcu_dereference_रक्षित(new->shared[i],
					      dma_resv_held(resv));
		dma_fence_put(f);
	पूर्ण
	kमुक्त_rcu(old, rcu);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_amdkfd_हटाओ_fence_on_pt_pd_bos(काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_bo *root = bo;
	काष्ठा amdgpu_vm_bo_base *vm_bo;
	काष्ठा amdgpu_vm *vm;
	काष्ठा amdkfd_process_info *info;
	काष्ठा amdgpu_amdkfd_fence *ef;
	पूर्णांक ret;

	/* we can always get vm_bo from root PD bo.*/
	जबतक (root->parent)
		root = root->parent;

	vm_bo = root->vm_bo;
	अगर (!vm_bo)
		वापस 0;

	vm = vm_bo->vm;
	अगर (!vm)
		वापस 0;

	info = vm->process_info;
	अगर (!info || !info->eviction_fence)
		वापस 0;

	ef = container_of(dma_fence_get(&info->eviction_fence->base),
			काष्ठा amdgpu_amdkfd_fence, base);

	BUG_ON(!dma_resv_trylock(bo->tbo.base.resv));
	ret = amdgpu_amdkfd_हटाओ_eviction_fence(bo, ef);
	dma_resv_unlock(bo->tbo.base.resv);

	dma_fence_put(&ef->base);
	वापस ret;
पूर्ण

अटल पूर्णांक amdgpu_amdkfd_bo_validate(काष्ठा amdgpu_bo *bo, uपूर्णांक32_t करोमुख्य,
				     bool रुको)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	पूर्णांक ret;

	अगर (WARN(amdgpu_tपंचांग_tt_get_usermm(bo->tbo.tपंचांग),
		 "Called with userptr BO"))
		वापस -EINVAL;

	amdgpu_bo_placement_from_करोमुख्य(bo, करोमुख्य);

	ret = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
	अगर (ret)
		जाओ validate_fail;
	अगर (रुको)
		amdgpu_bo_sync_रुको(bo, AMDGPU_FENCE_OWNER_KFD, false);

validate_fail:
	वापस ret;
पूर्ण

अटल पूर्णांक amdgpu_amdkfd_validate(व्योम *param, काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_vm_parser *p = param;

	वापस amdgpu_amdkfd_bo_validate(bo, p->करोमुख्य, p->रुको);
पूर्ण

/* vm_validate_pt_pd_bos - Validate page table and directory BOs
 *
 * Page directories are not updated here because huge page handling
 * during page table updates can invalidate page directory entries
 * again. Page directories are only updated after updating page
 * tables.
 */
अटल पूर्णांक vm_validate_pt_pd_bos(काष्ठा amdgpu_vm *vm)
अणु
	काष्ठा amdgpu_bo *pd = vm->root.base.bo;
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(pd->tbo.bdev);
	काष्ठा amdgpu_vm_parser param;
	पूर्णांक ret;

	param.करोमुख्य = AMDGPU_GEM_DOMAIN_VRAM;
	param.रुको = false;

	ret = amdgpu_vm_validate_pt_bos(adev, vm, amdgpu_amdkfd_validate,
					&param);
	अगर (ret) अणु
		pr_err("failed to validate PT BOs\n");
		वापस ret;
	पूर्ण

	ret = amdgpu_amdkfd_validate(&param, pd);
	अगर (ret) अणु
		pr_err("failed to validate PD\n");
		वापस ret;
	पूर्ण

	vm->pd_phys_addr = amdgpu_gmc_pd_addr(vm->root.base.bo);

	अगर (vm->use_cpu_क्रम_update) अणु
		ret = amdgpu_bo_kmap(pd, शून्य);
		अगर (ret) अणु
			pr_err("failed to kmap PD, ret=%d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vm_update_pds(काष्ठा amdgpu_vm *vm, काष्ठा amdgpu_sync *sync)
अणु
	काष्ठा amdgpu_bo *pd = vm->root.base.bo;
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(pd->tbo.bdev);
	पूर्णांक ret;

	ret = amdgpu_vm_update_pdes(adev, vm, false);
	अगर (ret)
		वापस ret;

	वापस amdgpu_sync_fence(sync, vm->last_update);
पूर्ण

अटल uपूर्णांक64_t get_pte_flags(काष्ठा amdgpu_device *adev, काष्ठा kgd_mem *mem)
अणु
	काष्ठा amdgpu_device *bo_adev = amdgpu_tपंचांग_adev(mem->bo->tbo.bdev);
	bool coherent = mem->alloc_flags & KFD_IOC_ALLOC_MEM_FLAGS_COHERENT;
	bool uncached = mem->alloc_flags & KFD_IOC_ALLOC_MEM_FLAGS_UNCACHED;
	uपूर्णांक32_t mapping_flags;
	uपूर्णांक64_t pte_flags;
	bool snoop = false;

	mapping_flags = AMDGPU_VM_PAGE_READABLE;
	अगर (mem->alloc_flags & KFD_IOC_ALLOC_MEM_FLAGS_WRITABLE)
		mapping_flags |= AMDGPU_VM_PAGE_WRITEABLE;
	अगर (mem->alloc_flags & KFD_IOC_ALLOC_MEM_FLAGS_EXECUTABLE)
		mapping_flags |= AMDGPU_VM_PAGE_EXECUTABLE;

	चयन (adev->asic_type) अणु
	हाल CHIP_ARCTURUS:
		अगर (mem->alloc_flags & KFD_IOC_ALLOC_MEM_FLAGS_VRAM) अणु
			अगर (bo_adev == adev)
				mapping_flags |= coherent ?
					AMDGPU_VM_MTYPE_CC : AMDGPU_VM_MTYPE_RW;
			अन्यथा
				mapping_flags |= AMDGPU_VM_MTYPE_UC;
		पूर्ण अन्यथा अणु
			mapping_flags |= coherent ?
				AMDGPU_VM_MTYPE_UC : AMDGPU_VM_MTYPE_NC;
		पूर्ण
		अवरोध;
	हाल CHIP_ALDEBARAN:
		अगर (coherent && uncached) अणु
			अगर (adev->gmc.xgmi.connected_to_cpu ||
				!(mem->alloc_flags & KFD_IOC_ALLOC_MEM_FLAGS_VRAM))
				snoop = true;
			mapping_flags |= AMDGPU_VM_MTYPE_UC;
		पूर्ण अन्यथा अगर (mem->alloc_flags & KFD_IOC_ALLOC_MEM_FLAGS_VRAM) अणु
			अगर (bo_adev == adev) अणु
				mapping_flags |= coherent ?
					AMDGPU_VM_MTYPE_CC : AMDGPU_VM_MTYPE_RW;
				अगर (adev->gmc.xgmi.connected_to_cpu)
					snoop = true;
			पूर्ण अन्यथा अणु
				mapping_flags |= AMDGPU_VM_MTYPE_UC;
				अगर (amdgpu_xgmi_same_hive(adev, bo_adev))
					snoop = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			snoop = true;
			mapping_flags |= coherent ?
				AMDGPU_VM_MTYPE_UC : AMDGPU_VM_MTYPE_NC;
		पूर्ण
		अवरोध;
	शेष:
		mapping_flags |= coherent ?
			AMDGPU_VM_MTYPE_UC : AMDGPU_VM_MTYPE_NC;
	पूर्ण

	pte_flags = amdgpu_gem_va_map_flags(adev, mapping_flags);
	pte_flags |= snoop ? AMDGPU_PTE_SNOOPED : 0;

	वापस pte_flags;
पूर्ण

/* add_bo_to_vm - Add a BO to a VM
 *
 * Everything that needs to bo करोne only once when a BO is first added
 * to a VM. It can later be mapped and unmapped many बार without
 * repeating these steps.
 *
 * 1. Allocate and initialize BO VA entry data काष्ठाure
 * 2. Add BO to the VM
 * 3. Determine ASIC-specअगरic PTE flags
 * 4. Alloc page tables and directories अगर needed
 * 4a.  Validate new page tables and directories
 */
अटल पूर्णांक add_bo_to_vm(काष्ठा amdgpu_device *adev, काष्ठा kgd_mem *mem,
		काष्ठा amdgpu_vm *vm, bool is_aql,
		काष्ठा kfd_bo_बहु_सूची **p_bo_va_entry)
अणु
	पूर्णांक ret;
	काष्ठा kfd_bo_बहु_सूची *bo_va_entry;
	काष्ठा amdgpu_bo *bo = mem->bo;
	uपूर्णांक64_t va = mem->va;
	काष्ठा list_head *list_bo_va = &mem->bo_बहु_सूची;
	अचिन्हित दीर्घ bo_size = bo->tbo.base.size;

	अगर (!va) अणु
		pr_err("Invalid VA when adding BO to VM\n");
		वापस -EINVAL;
	पूर्ण

	अगर (is_aql)
		va += bo_size;

	bo_va_entry = kzalloc(माप(*bo_va_entry), GFP_KERNEL);
	अगर (!bo_va_entry)
		वापस -ENOMEM;

	pr_debug("\t add VA 0x%llx - 0x%llx to vm %p\n", va,
			va + bo_size, vm);

	/* Add BO to VM पूर्णांकernal data काष्ठाures*/
	bo_va_entry->bo_va = amdgpu_vm_bo_add(adev, vm, bo);
	अगर (!bo_va_entry->bo_va) अणु
		ret = -EINVAL;
		pr_err("Failed to add BO object to VM. ret == %d\n",
				ret);
		जाओ err_vmadd;
	पूर्ण

	bo_va_entry->va = va;
	bo_va_entry->pte_flags = get_pte_flags(adev, mem);
	bo_va_entry->kgd_dev = (व्योम *)adev;
	list_add(&bo_va_entry->bo_list, list_bo_va);

	अगर (p_bo_va_entry)
		*p_bo_va_entry = bo_va_entry;

	/* Allocate validate page tables अगर needed */
	ret = vm_validate_pt_pd_bos(vm);
	अगर (ret) अणु
		pr_err("validate_pt_pd_bos() failed\n");
		जाओ err_alloc_pts;
	पूर्ण

	वापस 0;

err_alloc_pts:
	amdgpu_vm_bo_rmv(adev, bo_va_entry->bo_va);
	list_del(&bo_va_entry->bo_list);
err_vmadd:
	kमुक्त(bo_va_entry);
	वापस ret;
पूर्ण

अटल व्योम हटाओ_bo_from_vm(काष्ठा amdgpu_device *adev,
		काष्ठा kfd_bo_बहु_सूची *entry, अचिन्हित दीर्घ size)
अणु
	pr_debug("\t remove VA 0x%llx - 0x%llx in entry %p\n",
			entry->va,
			entry->va + size, entry);
	amdgpu_vm_bo_rmv(adev, entry->bo_va);
	list_del(&entry->bo_list);
	kमुक्त(entry);
पूर्ण

अटल व्योम add_kgd_mem_to_kfd_bo_list(काष्ठा kgd_mem *mem,
				काष्ठा amdkfd_process_info *process_info,
				bool userptr)
अणु
	काष्ठा tपंचांग_validate_buffer *entry = &mem->validate_list;
	काष्ठा amdgpu_bo *bo = mem->bo;

	INIT_LIST_HEAD(&entry->head);
	entry->num_shared = 1;
	entry->bo = &bo->tbo;
	mutex_lock(&process_info->lock);
	अगर (userptr)
		list_add_tail(&entry->head, &process_info->userptr_valid_list);
	अन्यथा
		list_add_tail(&entry->head, &process_info->kfd_bo_list);
	mutex_unlock(&process_info->lock);
पूर्ण

अटल व्योम हटाओ_kgd_mem_from_kfd_bo_list(काष्ठा kgd_mem *mem,
		काष्ठा amdkfd_process_info *process_info)
अणु
	काष्ठा tपंचांग_validate_buffer *bo_list_entry;

	bo_list_entry = &mem->validate_list;
	mutex_lock(&process_info->lock);
	list_del(&bo_list_entry->head);
	mutex_unlock(&process_info->lock);
पूर्ण

/* Initializes user pages. It रेजिस्टरs the MMU notअगरier and validates
 * the userptr BO in the GTT करोमुख्य.
 *
 * The BO must alपढ़ोy be on the userptr_valid_list. Otherwise an
 * eviction and restore may happen that leaves the new BO unmapped
 * with the user mode queues running.
 *
 * Takes the process_info->lock to protect against concurrent restore
 * workers.
 *
 * Returns 0 क्रम success, negative त्रुटि_सं क्रम errors.
 */
अटल पूर्णांक init_user_pages(काष्ठा kgd_mem *mem, uपूर्णांक64_t user_addr)
अणु
	काष्ठा amdkfd_process_info *process_info = mem->process_info;
	काष्ठा amdgpu_bo *bo = mem->bo;
	काष्ठा tपंचांग_operation_ctx ctx = अणु true, false पूर्ण;
	पूर्णांक ret = 0;

	mutex_lock(&process_info->lock);

	ret = amdgpu_tपंचांग_tt_set_userptr(&bo->tbo, user_addr, 0);
	अगर (ret) अणु
		pr_err("%s: Failed to set userptr: %d\n", __func__, ret);
		जाओ out;
	पूर्ण

	ret = amdgpu_mn_रेजिस्टर(bo, user_addr);
	अगर (ret) अणु
		pr_err("%s: Failed to register MMU notifier: %d\n",
		       __func__, ret);
		जाओ out;
	पूर्ण

	ret = amdgpu_tपंचांग_tt_get_user_pages(bo, bo->tbo.tपंचांग->pages);
	अगर (ret) अणु
		pr_err("%s: Failed to get user pages: %d\n", __func__, ret);
		जाओ unरेजिस्टर_out;
	पूर्ण

	ret = amdgpu_bo_reserve(bo, true);
	अगर (ret) अणु
		pr_err("%s: Failed to reserve BO\n", __func__);
		जाओ release_out;
	पूर्ण
	amdgpu_bo_placement_from_करोमुख्य(bo, mem->करोमुख्य);
	ret = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
	अगर (ret)
		pr_err("%s: failed to validate BO\n", __func__);
	amdgpu_bo_unreserve(bo);

release_out:
	amdgpu_tपंचांग_tt_get_user_pages_करोne(bo->tbo.tपंचांग);
unरेजिस्टर_out:
	अगर (ret)
		amdgpu_mn_unरेजिस्टर(bo);
out:
	mutex_unlock(&process_info->lock);
	वापस ret;
पूर्ण

/* Reserving a BO and its page table BOs must happen atomically to
 * aव्योम deadlocks. Some operations update multiple VMs at once. Track
 * all the reservation info in a context काष्ठाure. Optionally a sync
 * object can track VM updates.
 */
काष्ठा bo_vm_reservation_context अणु
	काष्ठा amdgpu_bo_list_entry kfd_bo; /* BO list entry क्रम the KFD BO */
	अचिन्हित पूर्णांक n_vms;		    /* Number of VMs reserved	    */
	काष्ठा amdgpu_bo_list_entry *vm_pd; /* Array of VM BO list entries  */
	काष्ठा ww_acquire_ctx ticket;	    /* Reservation ticket	    */
	काष्ठा list_head list, duplicates;  /* BO lists			    */
	काष्ठा amdgpu_sync *sync;	    /* Poपूर्णांकer to sync object	    */
	bool reserved;			    /* Whether BOs are reserved	    */
पूर्ण;

क्रमागत bo_vm_match अणु
	BO_VM_NOT_MAPPED = 0,	/* Match VMs where a BO is not mapped */
	BO_VM_MAPPED,		/* Match VMs where a BO is mapped     */
	BO_VM_ALL,		/* Match all VMs a BO was added to    */
पूर्ण;

/**
 * reserve_bo_and_vm - reserve a BO and a VM unconditionally.
 * @mem: KFD BO काष्ठाure.
 * @vm: the VM to reserve.
 * @ctx: the काष्ठा that will be used in unreserve_bo_and_vms().
 */
अटल पूर्णांक reserve_bo_and_vm(काष्ठा kgd_mem *mem,
			      काष्ठा amdgpu_vm *vm,
			      काष्ठा bo_vm_reservation_context *ctx)
अणु
	काष्ठा amdgpu_bo *bo = mem->bo;
	पूर्णांक ret;

	WARN_ON(!vm);

	ctx->reserved = false;
	ctx->n_vms = 1;
	ctx->sync = &mem->sync;

	INIT_LIST_HEAD(&ctx->list);
	INIT_LIST_HEAD(&ctx->duplicates);

	ctx->vm_pd = kसुस्मृति(ctx->n_vms, माप(*ctx->vm_pd), GFP_KERNEL);
	अगर (!ctx->vm_pd)
		वापस -ENOMEM;

	ctx->kfd_bo.priority = 0;
	ctx->kfd_bo.tv.bo = &bo->tbo;
	ctx->kfd_bo.tv.num_shared = 1;
	list_add(&ctx->kfd_bo.tv.head, &ctx->list);

	amdgpu_vm_get_pd_bo(vm, &ctx->list, &ctx->vm_pd[0]);

	ret = tपंचांग_eu_reserve_buffers(&ctx->ticket, &ctx->list,
				     false, &ctx->duplicates);
	अगर (ret) अणु
		pr_err("Failed to reserve buffers in ttm.\n");
		kमुक्त(ctx->vm_pd);
		ctx->vm_pd = शून्य;
		वापस ret;
	पूर्ण

	ctx->reserved = true;
	वापस 0;
पूर्ण

/**
 * reserve_bo_and_cond_vms - reserve a BO and some VMs conditionally
 * @mem: KFD BO काष्ठाure.
 * @vm: the VM to reserve. If शून्य, then all VMs associated with the BO
 * is used. Otherwise, a single VM associated with the BO.
 * @map_type: the mapping status that will be used to filter the VMs.
 * @ctx: the काष्ठा that will be used in unreserve_bo_and_vms().
 *
 * Returns 0 क्रम success, negative क्रम failure.
 */
अटल पूर्णांक reserve_bo_and_cond_vms(काष्ठा kgd_mem *mem,
				काष्ठा amdgpu_vm *vm, क्रमागत bo_vm_match map_type,
				काष्ठा bo_vm_reservation_context *ctx)
अणु
	काष्ठा amdgpu_bo *bo = mem->bo;
	काष्ठा kfd_bo_बहु_सूची *entry;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ctx->reserved = false;
	ctx->n_vms = 0;
	ctx->vm_pd = शून्य;
	ctx->sync = &mem->sync;

	INIT_LIST_HEAD(&ctx->list);
	INIT_LIST_HEAD(&ctx->duplicates);

	list_क्रम_each_entry(entry, &mem->bo_बहु_सूची, bo_list) अणु
		अगर ((vm && vm != entry->bo_va->base.vm) ||
			(entry->is_mapped != map_type
			&& map_type != BO_VM_ALL))
			जारी;

		ctx->n_vms++;
	पूर्ण

	अगर (ctx->n_vms != 0) अणु
		ctx->vm_pd = kसुस्मृति(ctx->n_vms, माप(*ctx->vm_pd),
				     GFP_KERNEL);
		अगर (!ctx->vm_pd)
			वापस -ENOMEM;
	पूर्ण

	ctx->kfd_bo.priority = 0;
	ctx->kfd_bo.tv.bo = &bo->tbo;
	ctx->kfd_bo.tv.num_shared = 1;
	list_add(&ctx->kfd_bo.tv.head, &ctx->list);

	i = 0;
	list_क्रम_each_entry(entry, &mem->bo_बहु_सूची, bo_list) अणु
		अगर ((vm && vm != entry->bo_va->base.vm) ||
			(entry->is_mapped != map_type
			&& map_type != BO_VM_ALL))
			जारी;

		amdgpu_vm_get_pd_bo(entry->bo_va->base.vm, &ctx->list,
				&ctx->vm_pd[i]);
		i++;
	पूर्ण

	ret = tपंचांग_eu_reserve_buffers(&ctx->ticket, &ctx->list,
				     false, &ctx->duplicates);
	अगर (ret) अणु
		pr_err("Failed to reserve buffers in ttm.\n");
		kमुक्त(ctx->vm_pd);
		ctx->vm_pd = शून्य;
		वापस ret;
	पूर्ण

	ctx->reserved = true;
	वापस 0;
पूर्ण

/**
 * unreserve_bo_and_vms - Unreserve BO and VMs from a reservation context
 * @ctx: Reservation context to unreserve
 * @रुको: Optionally रुको क्रम a sync object representing pending VM updates
 * @पूर्णांकr: Whether the रुको is पूर्णांकerruptible
 *
 * Also मुक्तs any resources allocated in
 * reserve_bo_and_(cond_)vm(s). Returns the status from
 * amdgpu_sync_रुको.
 */
अटल पूर्णांक unreserve_bo_and_vms(काष्ठा bo_vm_reservation_context *ctx,
				 bool रुको, bool पूर्णांकr)
अणु
	पूर्णांक ret = 0;

	अगर (रुको)
		ret = amdgpu_sync_रुको(ctx->sync, पूर्णांकr);

	अगर (ctx->reserved)
		tपंचांग_eu_backoff_reservation(&ctx->ticket, &ctx->list);
	kमुक्त(ctx->vm_pd);

	ctx->sync = शून्य;

	ctx->reserved = false;
	ctx->vm_pd = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक unmap_bo_from_gpuvm(काष्ठा amdgpu_device *adev,
				काष्ठा kfd_bo_बहु_सूची *entry,
				काष्ठा amdgpu_sync *sync)
अणु
	काष्ठा amdgpu_bo_va *bo_va = entry->bo_va;
	काष्ठा amdgpu_vm *vm = bo_va->base.vm;

	amdgpu_vm_bo_unmap(adev, bo_va, entry->va);

	amdgpu_vm_clear_मुक्तd(adev, vm, &bo_va->last_pt_update);

	amdgpu_sync_fence(sync, bo_va->last_pt_update);

	वापस 0;
पूर्ण

अटल पूर्णांक update_gpuvm_pte(काष्ठा amdgpu_device *adev,
		काष्ठा kfd_bo_बहु_सूची *entry,
		काष्ठा amdgpu_sync *sync)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_bo_va *bo_va = entry->bo_va;

	/* Update the page tables  */
	ret = amdgpu_vm_bo_update(adev, bo_va, false);
	अगर (ret) अणु
		pr_err("amdgpu_vm_bo_update failed\n");
		वापस ret;
	पूर्ण

	वापस amdgpu_sync_fence(sync, bo_va->last_pt_update);
पूर्ण

अटल पूर्णांक map_bo_to_gpuvm(काष्ठा amdgpu_device *adev,
		काष्ठा kfd_bo_बहु_सूची *entry, काष्ठा amdgpu_sync *sync,
		bool no_update_pte)
अणु
	पूर्णांक ret;

	/* Set भव address क्रम the allocation */
	ret = amdgpu_vm_bo_map(adev, entry->bo_va, entry->va, 0,
			       amdgpu_bo_size(entry->bo_va->base.bo),
			       entry->pte_flags);
	अगर (ret) अणु
		pr_err("Failed to map VA 0x%llx in vm. ret %d\n",
				entry->va, ret);
		वापस ret;
	पूर्ण

	अगर (no_update_pte)
		वापस 0;

	ret = update_gpuvm_pte(adev, entry, sync);
	अगर (ret) अणु
		pr_err("update_gpuvm_pte() failed\n");
		जाओ update_gpuvm_pte_failed;
	पूर्ण

	वापस 0;

update_gpuvm_pte_failed:
	unmap_bo_from_gpuvm(adev, entry, sync);
	वापस ret;
पूर्ण

अटल काष्ठा sg_table *create_करोorbell_sg(uपूर्णांक64_t addr, uपूर्णांक32_t size)
अणु
	काष्ठा sg_table *sg = kदो_स्मृति(माप(*sg), GFP_KERNEL);

	अगर (!sg)
		वापस शून्य;
	अगर (sg_alloc_table(sg, 1, GFP_KERNEL)) अणु
		kमुक्त(sg);
		वापस शून्य;
	पूर्ण
	sg->sgl->dma_address = addr;
	sg->sgl->length = size;
#अगर_घोषित CONFIG_NEED_SG_DMA_LENGTH
	sg->sgl->dma_length = size;
#पूर्ण_अगर
	वापस sg;
पूर्ण

अटल पूर्णांक process_validate_vms(काष्ठा amdkfd_process_info *process_info)
अणु
	काष्ठा amdgpu_vm *peer_vm;
	पूर्णांक ret;

	list_क्रम_each_entry(peer_vm, &process_info->vm_list_head,
			    vm_list_node) अणु
		ret = vm_validate_pt_pd_bos(peer_vm);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_sync_pds_resv(काष्ठा amdkfd_process_info *process_info,
				 काष्ठा amdgpu_sync *sync)
अणु
	काष्ठा amdgpu_vm *peer_vm;
	पूर्णांक ret;

	list_क्रम_each_entry(peer_vm, &process_info->vm_list_head,
			    vm_list_node) अणु
		काष्ठा amdgpu_bo *pd = peer_vm->root.base.bo;

		ret = amdgpu_sync_resv(शून्य, sync, pd->tbo.base.resv,
				       AMDGPU_SYNC_NE_OWNER,
				       AMDGPU_FENCE_OWNER_KFD);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_update_pds(काष्ठा amdkfd_process_info *process_info,
			      काष्ठा amdgpu_sync *sync)
अणु
	काष्ठा amdgpu_vm *peer_vm;
	पूर्णांक ret;

	list_क्रम_each_entry(peer_vm, &process_info->vm_list_head,
			    vm_list_node) अणु
		ret = vm_update_pds(peer_vm, sync);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_kfd_vm(काष्ठा amdgpu_vm *vm, व्योम **process_info,
		       काष्ठा dma_fence **ef)
अणु
	काष्ठा amdkfd_process_info *info = शून्य;
	पूर्णांक ret;

	अगर (!*process_info) अणु
		info = kzalloc(माप(*info), GFP_KERNEL);
		अगर (!info)
			वापस -ENOMEM;

		mutex_init(&info->lock);
		INIT_LIST_HEAD(&info->vm_list_head);
		INIT_LIST_HEAD(&info->kfd_bo_list);
		INIT_LIST_HEAD(&info->userptr_valid_list);
		INIT_LIST_HEAD(&info->userptr_inval_list);

		info->eviction_fence =
			amdgpu_amdkfd_fence_create(dma_fence_context_alloc(1),
						   current->mm);
		अगर (!info->eviction_fence) अणु
			pr_err("Failed to create eviction fence\n");
			ret = -ENOMEM;
			जाओ create_evict_fence_fail;
		पूर्ण

		info->pid = get_task_pid(current->group_leader, PIDTYPE_PID);
		atomic_set(&info->evicted_bos, 0);
		INIT_DELAYED_WORK(&info->restore_userptr_work,
				  amdgpu_amdkfd_restore_userptr_worker);

		*process_info = info;
		*ef = dma_fence_get(&info->eviction_fence->base);
	पूर्ण

	vm->process_info = *process_info;

	/* Validate page directory and attach eviction fence */
	ret = amdgpu_bo_reserve(vm->root.base.bo, true);
	अगर (ret)
		जाओ reserve_pd_fail;
	ret = vm_validate_pt_pd_bos(vm);
	अगर (ret) अणु
		pr_err("validate_pt_pd_bos() failed\n");
		जाओ validate_pd_fail;
	पूर्ण
	ret = amdgpu_bo_sync_रुको(vm->root.base.bo,
				  AMDGPU_FENCE_OWNER_KFD, false);
	अगर (ret)
		जाओ रुको_pd_fail;
	ret = dma_resv_reserve_shared(vm->root.base.bo->tbo.base.resv, 1);
	अगर (ret)
		जाओ reserve_shared_fail;
	amdgpu_bo_fence(vm->root.base.bo,
			&vm->process_info->eviction_fence->base, true);
	amdgpu_bo_unreserve(vm->root.base.bo);

	/* Update process info */
	mutex_lock(&vm->process_info->lock);
	list_add_tail(&vm->vm_list_node,
			&(vm->process_info->vm_list_head));
	vm->process_info->n_vms++;
	mutex_unlock(&vm->process_info->lock);

	वापस 0;

reserve_shared_fail:
रुको_pd_fail:
validate_pd_fail:
	amdgpu_bo_unreserve(vm->root.base.bo);
reserve_pd_fail:
	vm->process_info = शून्य;
	अगर (info) अणु
		/* Two fence references: one in info and one in *ef */
		dma_fence_put(&info->eviction_fence->base);
		dma_fence_put(*ef);
		*ef = शून्य;
		*process_info = शून्य;
		put_pid(info->pid);
create_evict_fence_fail:
		mutex_destroy(&info->lock);
		kमुक्त(info);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक amdgpu_amdkfd_gpuvm_acquire_process_vm(काष्ठा kgd_dev *kgd,
					   काष्ठा file *filp, u32 pasid,
					   व्योम **vm, व्योम **process_info,
					   काष्ठा dma_fence **ef)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा drm_file *drm_priv = filp->निजी_data;
	काष्ठा amdgpu_fpriv *drv_priv = drm_priv->driver_priv;
	काष्ठा amdgpu_vm *avm = &drv_priv->vm;
	पूर्णांक ret;

	/* Alपढ़ोy a compute VM? */
	अगर (avm->process_info)
		वापस -EINVAL;

	/* Convert VM पूर्णांकo a compute VM */
	ret = amdgpu_vm_make_compute(adev, avm, pasid);
	अगर (ret)
		वापस ret;

	/* Initialize KFD part of the VM and process info */
	ret = init_kfd_vm(avm, process_info, ef);
	अगर (ret)
		वापस ret;

	*vm = (व्योम *)avm;

	वापस 0;
पूर्ण

व्योम amdgpu_amdkfd_gpuvm_destroy_cb(काष्ठा amdgpu_device *adev,
				    काष्ठा amdgpu_vm *vm)
अणु
	काष्ठा amdkfd_process_info *process_info = vm->process_info;
	काष्ठा amdgpu_bo *pd = vm->root.base.bo;

	अगर (!process_info)
		वापस;

	/* Release eviction fence from PD */
	amdgpu_bo_reserve(pd, false);
	amdgpu_bo_fence(pd, शून्य, false);
	amdgpu_bo_unreserve(pd);

	/* Update process info */
	mutex_lock(&process_info->lock);
	process_info->n_vms--;
	list_del(&vm->vm_list_node);
	mutex_unlock(&process_info->lock);

	vm->process_info = शून्य;

	/* Release per-process resources when last compute VM is destroyed */
	अगर (!process_info->n_vms) अणु
		WARN_ON(!list_empty(&process_info->kfd_bo_list));
		WARN_ON(!list_empty(&process_info->userptr_valid_list));
		WARN_ON(!list_empty(&process_info->userptr_inval_list));

		dma_fence_put(&process_info->eviction_fence->base);
		cancel_delayed_work_sync(&process_info->restore_userptr_work);
		put_pid(process_info->pid);
		mutex_destroy(&process_info->lock);
		kमुक्त(process_info);
	पूर्ण
पूर्ण

व्योम amdgpu_amdkfd_gpuvm_release_process_vm(काष्ठा kgd_dev *kgd, व्योम *vm)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा amdgpu_vm *avm = (काष्ठा amdgpu_vm *)vm;

	अगर (WARN_ON(!kgd || !vm))
		वापस;

	pr_debug("Releasing process vm %p\n", vm);

	/* The original pasid of amdgpu vm has alपढ़ोy been
	 * released during making a amdgpu vm to a compute vm
	 * The current pasid is managed by kfd and will be
	 * released on kfd process destroy. Set amdgpu pasid
	 * to 0 to aव्योम duplicate release.
	 */
	amdgpu_vm_release_compute(adev, avm);
पूर्ण

uपूर्णांक64_t amdgpu_amdkfd_gpuvm_get_process_page_dir(व्योम *vm)
अणु
	काष्ठा amdgpu_vm *avm = (काष्ठा amdgpu_vm *)vm;
	काष्ठा amdgpu_bo *pd = avm->root.base.bo;
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(pd->tbo.bdev);

	अगर (adev->asic_type < CHIP_VEGA10)
		वापस avm->pd_phys_addr >> AMDGPU_GPU_PAGE_SHIFT;
	वापस avm->pd_phys_addr;
पूर्ण

पूर्णांक amdgpu_amdkfd_gpuvm_alloc_memory_of_gpu(
		काष्ठा kgd_dev *kgd, uपूर्णांक64_t va, uपूर्णांक64_t size,
		व्योम *vm, काष्ठा kgd_mem **mem,
		uपूर्णांक64_t *offset, uपूर्णांक32_t flags)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा amdgpu_vm *avm = (काष्ठा amdgpu_vm *)vm;
	क्रमागत tपंचांग_bo_type bo_type = tपंचांग_bo_type_device;
	काष्ठा sg_table *sg = शून्य;
	uपूर्णांक64_t user_addr = 0;
	काष्ठा amdgpu_bo *bo;
	काष्ठा drm_gem_object *gobj;
	u32 करोमुख्य, alloc_करोमुख्य;
	u64 alloc_flags;
	पूर्णांक ret;

	/*
	 * Check on which करोमुख्य to allocate BO
	 */
	अगर (flags & KFD_IOC_ALLOC_MEM_FLAGS_VRAM) अणु
		करोमुख्य = alloc_करोमुख्य = AMDGPU_GEM_DOMAIN_VRAM;
		alloc_flags = AMDGPU_GEM_CREATE_VRAM_WIPE_ON_RELEASE;
		alloc_flags |= (flags & KFD_IOC_ALLOC_MEM_FLAGS_PUBLIC) ?
			AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED :
			AMDGPU_GEM_CREATE_NO_CPU_ACCESS;
	पूर्ण अन्यथा अगर (flags & KFD_IOC_ALLOC_MEM_FLAGS_GTT) अणु
		करोमुख्य = alloc_करोमुख्य = AMDGPU_GEM_DOMAIN_GTT;
		alloc_flags = 0;
	पूर्ण अन्यथा अगर (flags & KFD_IOC_ALLOC_MEM_FLAGS_USERPTR) अणु
		करोमुख्य = AMDGPU_GEM_DOMAIN_GTT;
		alloc_करोमुख्य = AMDGPU_GEM_DOMAIN_CPU;
		alloc_flags = 0;
		अगर (!offset || !*offset)
			वापस -EINVAL;
		user_addr = untagged_addr(*offset);
	पूर्ण अन्यथा अगर (flags & (KFD_IOC_ALLOC_MEM_FLAGS_DOORBELL |
			KFD_IOC_ALLOC_MEM_FLAGS_MMIO_REMAP)) अणु
		करोमुख्य = AMDGPU_GEM_DOMAIN_GTT;
		alloc_करोमुख्य = AMDGPU_GEM_DOMAIN_CPU;
		bo_type = tपंचांग_bo_type_sg;
		alloc_flags = 0;
		अगर (size > अच_पूर्णांक_उच्च)
			वापस -EINVAL;
		sg = create_करोorbell_sg(*offset, size);
		अगर (!sg)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	*mem = kzalloc(माप(काष्ठा kgd_mem), GFP_KERNEL);
	अगर (!*mem) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	INIT_LIST_HEAD(&(*mem)->bo_बहु_सूची);
	mutex_init(&(*mem)->lock);
	(*mem)->aql_queue = !!(flags & KFD_IOC_ALLOC_MEM_FLAGS_AQL_QUEUE_MEM);

	/* Workaround क्रम AQL queue wraparound bug. Map the same
	 * memory twice. That means we only actually allocate half
	 * the memory.
	 */
	अगर ((*mem)->aql_queue)
		size = size >> 1;

	(*mem)->alloc_flags = flags;

	amdgpu_sync_create(&(*mem)->sync);

	ret = amdgpu_amdkfd_reserve_mem_limit(adev, size, alloc_करोमुख्य, !!sg);
	अगर (ret) अणु
		pr_debug("Insufficient memory\n");
		जाओ err_reserve_limit;
	पूर्ण

	pr_debug("\tcreate BO VA 0x%llx size 0x%llx domain %s\n",
			va, size, करोमुख्य_string(alloc_करोमुख्य));

	ret = amdgpu_gem_object_create(adev, size, 1, alloc_करोमुख्य, alloc_flags,
				       bo_type, शून्य, &gobj);
	अगर (ret) अणु
		pr_debug("Failed to create BO on domain %s. ret %d\n",
			 करोमुख्य_string(alloc_करोमुख्य), ret);
		जाओ err_bo_create;
	पूर्ण
	bo = gem_to_amdgpu_bo(gobj);
	अगर (bo_type == tपंचांग_bo_type_sg) अणु
		bo->tbo.sg = sg;
		bo->tbo.tपंचांग->sg = sg;
	पूर्ण
	bo->kfd_bo = *mem;
	(*mem)->bo = bo;
	अगर (user_addr)
		bo->flags |= AMDGPU_AMDKFD_USERPTR_BO;

	(*mem)->va = va;
	(*mem)->करोमुख्य = करोमुख्य;
	(*mem)->mapped_to_gpu_memory = 0;
	(*mem)->process_info = avm->process_info;
	add_kgd_mem_to_kfd_bo_list(*mem, avm->process_info, user_addr);

	अगर (user_addr) अणु
		ret = init_user_pages(*mem, user_addr);
		अगर (ret)
			जाओ allocate_init_user_pages_failed;
	पूर्ण

	अगर (offset)
		*offset = amdgpu_bo_mmap_offset(bo);

	वापस 0;

allocate_init_user_pages_failed:
	हटाओ_kgd_mem_from_kfd_bo_list(*mem, avm->process_info);
	amdgpu_bo_unref(&bo);
	/* Don't unreserve प्रणाली mem limit twice */
	जाओ err_reserve_limit;
err_bo_create:
	unreserve_mem_limit(adev, size, alloc_करोमुख्य, !!sg);
err_reserve_limit:
	mutex_destroy(&(*mem)->lock);
	kमुक्त(*mem);
err:
	अगर (sg) अणु
		sg_मुक्त_table(sg);
		kमुक्त(sg);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक amdgpu_amdkfd_gpuvm_मुक्त_memory_of_gpu(
		काष्ठा kgd_dev *kgd, काष्ठा kgd_mem *mem, uपूर्णांक64_t *size)
अणु
	काष्ठा amdkfd_process_info *process_info = mem->process_info;
	अचिन्हित दीर्घ bo_size = mem->bo->tbo.base.size;
	काष्ठा kfd_bo_बहु_सूची *entry, *पंचांगp;
	काष्ठा bo_vm_reservation_context ctx;
	काष्ठा tपंचांग_validate_buffer *bo_list_entry;
	अचिन्हित पूर्णांक mapped_to_gpu_memory;
	पूर्णांक ret;
	bool is_imported = false;

	mutex_lock(&mem->lock);
	mapped_to_gpu_memory = mem->mapped_to_gpu_memory;
	is_imported = mem->is_imported;
	mutex_unlock(&mem->lock);
	/* lock is not needed after this, since mem is unused and will
	 * be मुक्तd anyway
	 */

	अगर (mapped_to_gpu_memory > 0) अणु
		pr_debug("BO VA 0x%llx size 0x%lx is still mapped.\n",
				mem->va, bo_size);
		वापस -EBUSY;
	पूर्ण

	/* Make sure restore workers करोn't access the BO any more */
	bo_list_entry = &mem->validate_list;
	mutex_lock(&process_info->lock);
	list_del(&bo_list_entry->head);
	mutex_unlock(&process_info->lock);

	/* No more MMU notअगरiers */
	amdgpu_mn_unरेजिस्टर(mem->bo);

	ret = reserve_bo_and_cond_vms(mem, शून्य, BO_VM_ALL, &ctx);
	अगर (unlikely(ret))
		वापस ret;

	/* The eviction fence should be हटाओd by the last unmap.
	 * TODO: Log an error condition अगर the bo still has the eviction fence
	 * attached
	 */
	amdgpu_amdkfd_हटाओ_eviction_fence(mem->bo,
					process_info->eviction_fence);
	pr_debug("Release VA 0x%llx - 0x%llx\n", mem->va,
		mem->va + bo_size * (1 + mem->aql_queue));

	/* Remove from VM पूर्णांकernal data काष्ठाures */
	list_क्रम_each_entry_safe(entry, पंचांगp, &mem->bo_बहु_सूची, bo_list)
		हटाओ_bo_from_vm((काष्ठा amdgpu_device *)entry->kgd_dev,
				entry, bo_size);

	ret = unreserve_bo_and_vms(&ctx, false, false);

	/* Free the sync object */
	amdgpu_sync_मुक्त(&mem->sync);

	/* If the SG is not शून्य, it's one we created क्रम a करोorbell or mmio
	 * remap BO. We need to मुक्त it.
	 */
	अगर (mem->bo->tbo.sg) अणु
		sg_मुक्त_table(mem->bo->tbo.sg);
		kमुक्त(mem->bo->tbo.sg);
	पूर्ण

	/* Update the size of the BO being मुक्तd अगर it was allocated from
	 * VRAM and is not imported.
	 */
	अगर (size) अणु
		अगर ((mem->bo->preferred_करोमुख्यs == AMDGPU_GEM_DOMAIN_VRAM) &&
		    (!is_imported))
			*size = bo_size;
		अन्यथा
			*size = 0;
	पूर्ण

	/* Free the BO*/
	drm_gem_object_put(&mem->bo->tbo.base);
	mutex_destroy(&mem->lock);
	kमुक्त(mem);

	वापस ret;
पूर्ण

पूर्णांक amdgpu_amdkfd_gpuvm_map_memory_to_gpu(
		काष्ठा kgd_dev *kgd, काष्ठा kgd_mem *mem, व्योम *vm)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा amdgpu_vm *avm = (काष्ठा amdgpu_vm *)vm;
	पूर्णांक ret;
	काष्ठा amdgpu_bo *bo;
	uपूर्णांक32_t करोमुख्य;
	काष्ठा kfd_bo_बहु_सूची *entry;
	काष्ठा bo_vm_reservation_context ctx;
	काष्ठा kfd_bo_बहु_सूची *bo_va_entry = शून्य;
	काष्ठा kfd_bo_बहु_सूची *bo_va_entry_aql = शून्य;
	अचिन्हित दीर्घ bo_size;
	bool is_invalid_userptr = false;

	bo = mem->bo;
	अगर (!bo) अणु
		pr_err("Invalid BO when mapping memory to GPU\n");
		वापस -EINVAL;
	पूर्ण

	/* Make sure restore is not running concurrently. Since we
	 * करोn't map invalid userptr BOs, we rely on the next restore
	 * worker to करो the mapping
	 */
	mutex_lock(&mem->process_info->lock);

	/* Lock mmap-sem. If we find an invalid userptr BO, we can be
	 * sure that the MMU notअगरier is no दीर्घer running
	 * concurrently and the queues are actually stopped
	 */
	अगर (amdgpu_tपंचांग_tt_get_usermm(bo->tbo.tपंचांग)) अणु
		mmap_ग_लिखो_lock(current->mm);
		is_invalid_userptr = atomic_पढ़ो(&mem->invalid);
		mmap_ग_लिखो_unlock(current->mm);
	पूर्ण

	mutex_lock(&mem->lock);

	करोमुख्य = mem->करोमुख्य;
	bo_size = bo->tbo.base.size;

	pr_debug("Map VA 0x%llx - 0x%llx to vm %p domain %s\n",
			mem->va,
			mem->va + bo_size * (1 + mem->aql_queue),
			vm, करोमुख्य_string(करोमुख्य));

	ret = reserve_bo_and_vm(mem, vm, &ctx);
	अगर (unlikely(ret))
		जाओ out;

	/* Userptr can be marked as "not invalid", but not actually be
	 * validated yet (still in the प्रणाली करोमुख्य). In that हाल
	 * the queues are still stopped and we can leave mapping क्रम
	 * the next restore worker
	 */
	अगर (amdgpu_tपंचांग_tt_get_usermm(bo->tbo.tपंचांग) &&
	    bo->tbo.mem.mem_type == TTM_PL_SYSTEM)
		is_invalid_userptr = true;

	अगर (check_अगर_add_bo_to_vm(avm, mem)) अणु
		ret = add_bo_to_vm(adev, mem, avm, false,
				&bo_va_entry);
		अगर (ret)
			जाओ add_bo_to_vm_failed;
		अगर (mem->aql_queue) अणु
			ret = add_bo_to_vm(adev, mem, avm,
					true, &bo_va_entry_aql);
			अगर (ret)
				जाओ add_bo_to_vm_failed_aql;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = vm_validate_pt_pd_bos(avm);
		अगर (unlikely(ret))
			जाओ add_bo_to_vm_failed;
	पूर्ण

	अगर (mem->mapped_to_gpu_memory == 0 &&
	    !amdgpu_tपंचांग_tt_get_usermm(bo->tbo.tपंचांग)) अणु
		/* Validate BO only once. The eviction fence माला_लो added to BO
		 * the first समय it is mapped. Validate will रुको क्रम all
		 * background evictions to complete.
		 */
		ret = amdgpu_amdkfd_bo_validate(bo, करोमुख्य, true);
		अगर (ret) अणु
			pr_debug("Validate failed\n");
			जाओ map_bo_to_gpuvm_failed;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(entry, &mem->bo_बहु_सूची, bo_list) अणु
		अगर (entry->bo_va->base.vm == vm && !entry->is_mapped) अणु
			pr_debug("\t map VA 0x%llx - 0x%llx in entry %p\n",
					entry->va, entry->va + bo_size,
					entry);

			ret = map_bo_to_gpuvm(adev, entry, ctx.sync,
					      is_invalid_userptr);
			अगर (ret) अणु
				pr_err("Failed to map bo to gpuvm\n");
				जाओ map_bo_to_gpuvm_failed;
			पूर्ण

			ret = vm_update_pds(vm, ctx.sync);
			अगर (ret) अणु
				pr_err("Failed to update page directories\n");
				जाओ map_bo_to_gpuvm_failed;
			पूर्ण

			entry->is_mapped = true;
			mem->mapped_to_gpu_memory++;
			pr_debug("\t INC mapping count %d\n",
					mem->mapped_to_gpu_memory);
		पूर्ण
	पूर्ण

	अगर (!amdgpu_tपंचांग_tt_get_usermm(bo->tbo.tपंचांग) && !bo->tbo.pin_count)
		amdgpu_bo_fence(bo,
				&avm->process_info->eviction_fence->base,
				true);
	ret = unreserve_bo_and_vms(&ctx, false, false);

	जाओ out;

map_bo_to_gpuvm_failed:
	अगर (bo_va_entry_aql)
		हटाओ_bo_from_vm(adev, bo_va_entry_aql, bo_size);
add_bo_to_vm_failed_aql:
	अगर (bo_va_entry)
		हटाओ_bo_from_vm(adev, bo_va_entry, bo_size);
add_bo_to_vm_failed:
	unreserve_bo_and_vms(&ctx, false, false);
out:
	mutex_unlock(&mem->process_info->lock);
	mutex_unlock(&mem->lock);
	वापस ret;
पूर्ण

पूर्णांक amdgpu_amdkfd_gpuvm_unmap_memory_from_gpu(
		काष्ठा kgd_dev *kgd, काष्ठा kgd_mem *mem, व्योम *vm)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा amdkfd_process_info *process_info =
		((काष्ठा amdgpu_vm *)vm)->process_info;
	अचिन्हित दीर्घ bo_size = mem->bo->tbo.base.size;
	काष्ठा kfd_bo_बहु_सूची *entry;
	काष्ठा bo_vm_reservation_context ctx;
	पूर्णांक ret;

	mutex_lock(&mem->lock);

	ret = reserve_bo_and_cond_vms(mem, vm, BO_VM_MAPPED, &ctx);
	अगर (unlikely(ret))
		जाओ out;
	/* If no VMs were reserved, it means the BO wasn't actually mapped */
	अगर (ctx.n_vms == 0) अणु
		ret = -EINVAL;
		जाओ unreserve_out;
	पूर्ण

	ret = vm_validate_pt_pd_bos((काष्ठा amdgpu_vm *)vm);
	अगर (unlikely(ret))
		जाओ unreserve_out;

	pr_debug("Unmap VA 0x%llx - 0x%llx from vm %p\n",
		mem->va,
		mem->va + bo_size * (1 + mem->aql_queue),
		vm);

	list_क्रम_each_entry(entry, &mem->bo_बहु_सूची, bo_list) अणु
		अगर (entry->bo_va->base.vm == vm && entry->is_mapped) अणु
			pr_debug("\t unmap VA 0x%llx - 0x%llx from entry %p\n",
					entry->va,
					entry->va + bo_size,
					entry);

			ret = unmap_bo_from_gpuvm(adev, entry, ctx.sync);
			अगर (ret == 0) अणु
				entry->is_mapped = false;
			पूर्ण अन्यथा अणु
				pr_err("failed to unmap VA 0x%llx\n",
						mem->va);
				जाओ unreserve_out;
			पूर्ण

			mem->mapped_to_gpu_memory--;
			pr_debug("\t DEC mapping count %d\n",
					mem->mapped_to_gpu_memory);
		पूर्ण
	पूर्ण

	/* If BO is unmapped from all VMs, unfence it. It can be evicted अगर
	 * required.
	 */
	अगर (mem->mapped_to_gpu_memory == 0 &&
	    !amdgpu_tपंचांग_tt_get_usermm(mem->bo->tbo.tपंचांग) &&
	    !mem->bo->tbo.pin_count)
		amdgpu_amdkfd_हटाओ_eviction_fence(mem->bo,
						process_info->eviction_fence);

unreserve_out:
	unreserve_bo_and_vms(&ctx, false, false);
out:
	mutex_unlock(&mem->lock);
	वापस ret;
पूर्ण

पूर्णांक amdgpu_amdkfd_gpuvm_sync_memory(
		काष्ठा kgd_dev *kgd, काष्ठा kgd_mem *mem, bool पूर्णांकr)
अणु
	काष्ठा amdgpu_sync sync;
	पूर्णांक ret;

	amdgpu_sync_create(&sync);

	mutex_lock(&mem->lock);
	amdgpu_sync_clone(&mem->sync, &sync);
	mutex_unlock(&mem->lock);

	ret = amdgpu_sync_रुको(&sync, पूर्णांकr);
	amdgpu_sync_मुक्त(&sync);
	वापस ret;
पूर्ण

पूर्णांक amdgpu_amdkfd_gpuvm_map_gtt_bo_to_kernel(काष्ठा kgd_dev *kgd,
		काष्ठा kgd_mem *mem, व्योम **kptr, uपूर्णांक64_t *size)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_bo *bo = mem->bo;

	अगर (amdgpu_tपंचांग_tt_get_usermm(bo->tbo.tपंचांग)) अणु
		pr_err("userptr can't be mapped to kernel\n");
		वापस -EINVAL;
	पूर्ण

	/* delete kgd_mem from kfd_bo_list to aव्योम re-validating
	 * this BO in BO's restoring after eviction.
	 */
	mutex_lock(&mem->process_info->lock);

	ret = amdgpu_bo_reserve(bo, true);
	अगर (ret) अणु
		pr_err("Failed to reserve bo. ret %d\n", ret);
		जाओ bo_reserve_failed;
	पूर्ण

	ret = amdgpu_bo_pin(bo, AMDGPU_GEM_DOMAIN_GTT);
	अगर (ret) अणु
		pr_err("Failed to pin bo. ret %d\n", ret);
		जाओ pin_failed;
	पूर्ण

	ret = amdgpu_bo_kmap(bo, kptr);
	अगर (ret) अणु
		pr_err("Failed to map bo to kernel. ret %d\n", ret);
		जाओ kmap_failed;
	पूर्ण

	amdgpu_amdkfd_हटाओ_eviction_fence(
		bo, mem->process_info->eviction_fence);
	list_del_init(&mem->validate_list.head);

	अगर (size)
		*size = amdgpu_bo_size(bo);

	amdgpu_bo_unreserve(bo);

	mutex_unlock(&mem->process_info->lock);
	वापस 0;

kmap_failed:
	amdgpu_bo_unpin(bo);
pin_failed:
	amdgpu_bo_unreserve(bo);
bo_reserve_failed:
	mutex_unlock(&mem->process_info->lock);

	वापस ret;
पूर्ण

पूर्णांक amdgpu_amdkfd_gpuvm_get_vm_fault_info(काष्ठा kgd_dev *kgd,
					      काष्ठा kfd_vm_fault_info *mem)
अणु
	काष्ठा amdgpu_device *adev;

	adev = (काष्ठा amdgpu_device *)kgd;
	अगर (atomic_पढ़ो(&adev->gmc.vm_fault_info_updated) == 1) अणु
		*mem = *adev->gmc.vm_fault_info;
		mb();
		atomic_set(&adev->gmc.vm_fault_info_updated, 0);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक amdgpu_amdkfd_gpuvm_import_dmabuf(काष्ठा kgd_dev *kgd,
				      काष्ठा dma_buf *dma_buf,
				      uपूर्णांक64_t va, व्योम *vm,
				      काष्ठा kgd_mem **mem, uपूर्णांक64_t *size,
				      uपूर्णांक64_t *mmap_offset)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;
	काष्ठा drm_gem_object *obj;
	काष्ठा amdgpu_bo *bo;
	काष्ठा amdgpu_vm *avm = (काष्ठा amdgpu_vm *)vm;

	अगर (dma_buf->ops != &amdgpu_dmabuf_ops)
		/* Can't handle non-graphics buffers */
		वापस -EINVAL;

	obj = dma_buf->priv;
	अगर (drm_to_adev(obj->dev) != adev)
		/* Can't handle buffers from other devices */
		वापस -EINVAL;

	bo = gem_to_amdgpu_bo(obj);
	अगर (!(bo->preferred_करोमुख्यs & (AMDGPU_GEM_DOMAIN_VRAM |
				    AMDGPU_GEM_DOMAIN_GTT)))
		/* Only VRAM and GTT BOs are supported */
		वापस -EINVAL;

	*mem = kzalloc(माप(काष्ठा kgd_mem), GFP_KERNEL);
	अगर (!*mem)
		वापस -ENOMEM;

	अगर (size)
		*size = amdgpu_bo_size(bo);

	अगर (mmap_offset)
		*mmap_offset = amdgpu_bo_mmap_offset(bo);

	INIT_LIST_HEAD(&(*mem)->bo_बहु_सूची);
	mutex_init(&(*mem)->lock);

	(*mem)->alloc_flags =
		((bo->preferred_करोमुख्यs & AMDGPU_GEM_DOMAIN_VRAM) ?
		KFD_IOC_ALLOC_MEM_FLAGS_VRAM : KFD_IOC_ALLOC_MEM_FLAGS_GTT)
		| KFD_IOC_ALLOC_MEM_FLAGS_WRITABLE
		| KFD_IOC_ALLOC_MEM_FLAGS_EXECUTABLE;

	drm_gem_object_get(&bo->tbo.base);
	(*mem)->bo = bo;
	(*mem)->va = va;
	(*mem)->करोमुख्य = (bo->preferred_करोमुख्यs & AMDGPU_GEM_DOMAIN_VRAM) ?
		AMDGPU_GEM_DOMAIN_VRAM : AMDGPU_GEM_DOMAIN_GTT;
	(*mem)->mapped_to_gpu_memory = 0;
	(*mem)->process_info = avm->process_info;
	add_kgd_mem_to_kfd_bo_list(*mem, avm->process_info, false);
	amdgpu_sync_create(&(*mem)->sync);
	(*mem)->is_imported = true;

	वापस 0;
पूर्ण

/* Evict a userptr BO by stopping the queues अगर necessary
 *
 * Runs in MMU notअगरier, may be in RECLAIM_FS context. This means it
 * cannot करो any memory allocations, and cannot take any locks that
 * are held अन्यथाwhere जबतक allocating memory. Thereक्रमe this is as
 * simple as possible, using atomic counters.
 *
 * It करोesn't करो anything to the BO itself. The real work happens in
 * restore, where we get updated page addresses. This function only
 * ensures that GPU access to the BO is stopped.
 */
पूर्णांक amdgpu_amdkfd_evict_userptr(काष्ठा kgd_mem *mem,
				काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा amdkfd_process_info *process_info = mem->process_info;
	पूर्णांक evicted_bos;
	पूर्णांक r = 0;

	atomic_inc(&mem->invalid);
	evicted_bos = atomic_inc_वापस(&process_info->evicted_bos);
	अगर (evicted_bos == 1) अणु
		/* First eviction, stop the queues */
		r = kgd2kfd_quiesce_mm(mm);
		अगर (r)
			pr_err("Failed to quiesce KFD\n");
		schedule_delayed_work(&process_info->restore_userptr_work,
			msecs_to_jअगरfies(AMDGPU_USERPTR_RESTORE_DELAY_MS));
	पूर्ण

	वापस r;
पूर्ण

/* Update invalid userptr BOs
 *
 * Moves invalidated (evicted) userptr BOs from userptr_valid_list to
 * userptr_inval_list and updates user pages क्रम all BOs that have
 * been invalidated since their last update.
 */
अटल पूर्णांक update_invalid_user_pages(काष्ठा amdkfd_process_info *process_info,
				     काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा kgd_mem *mem, *पंचांगp_mem;
	काष्ठा amdgpu_bo *bo;
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	पूर्णांक invalid, ret;

	/* Move all invalidated BOs to the userptr_inval_list and
	 * release their user pages by migration to the CPU करोमुख्य
	 */
	list_क्रम_each_entry_safe(mem, पंचांगp_mem,
				 &process_info->userptr_valid_list,
				 validate_list.head) अणु
		अगर (!atomic_पढ़ो(&mem->invalid))
			जारी; /* BO is still valid */

		bo = mem->bo;

		अगर (amdgpu_bo_reserve(bo, true))
			वापस -EAGAIN;
		amdgpu_bo_placement_from_करोमुख्य(bo, AMDGPU_GEM_DOMAIN_CPU);
		ret = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
		amdgpu_bo_unreserve(bo);
		अगर (ret) अणु
			pr_err("%s: Failed to invalidate userptr BO\n",
			       __func__);
			वापस -EAGAIN;
		पूर्ण

		list_move_tail(&mem->validate_list.head,
			       &process_info->userptr_inval_list);
	पूर्ण

	अगर (list_empty(&process_info->userptr_inval_list))
		वापस 0; /* All evicted userptr BOs were मुक्तd */

	/* Go through userptr_inval_list and update any invalid user_pages */
	list_क्रम_each_entry(mem, &process_info->userptr_inval_list,
			    validate_list.head) अणु
		invalid = atomic_पढ़ो(&mem->invalid);
		अगर (!invalid)
			/* BO hasn't been invalidated since the last
			 * revalidation attempt. Keep its BO list.
			 */
			जारी;

		bo = mem->bo;

		/* Get updated user pages */
		ret = amdgpu_tपंचांग_tt_get_user_pages(bo, bo->tbo.tपंचांग->pages);
		अगर (ret) अणु
			pr_debug("%s: Failed to get user pages: %d\n",
				__func__, ret);

			/* Return error -EBUSY or -ENOMEM, retry restore */
			वापस ret;
		पूर्ण

		/*
		 * FIXME: Cannot ignore the वापस code, must hold
		 * notअगरier_lock
		 */
		amdgpu_tपंचांग_tt_get_user_pages_करोne(bo->tbo.tपंचांग);

		/* Mark the BO as valid unless it was invalidated
		 * again concurrently.
		 */
		अगर (atomic_cmpxchg(&mem->invalid, invalid, 0) != invalid)
			वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

/* Validate invalid userptr BOs
 *
 * Validates BOs on the userptr_inval_list, and moves them back to the
 * userptr_valid_list. Also updates GPUVM page tables with new page
 * addresses and रुकोs क्रम the page table updates to complete.
 */
अटल पूर्णांक validate_invalid_user_pages(काष्ठा amdkfd_process_info *process_info)
अणु
	काष्ठा amdgpu_bo_list_entry *pd_bo_list_entries;
	काष्ठा list_head resv_list, duplicates;
	काष्ठा ww_acquire_ctx ticket;
	काष्ठा amdgpu_sync sync;

	काष्ठा amdgpu_vm *peer_vm;
	काष्ठा kgd_mem *mem, *पंचांगp_mem;
	काष्ठा amdgpu_bo *bo;
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	पूर्णांक i, ret;

	pd_bo_list_entries = kसुस्मृति(process_info->n_vms,
				     माप(काष्ठा amdgpu_bo_list_entry),
				     GFP_KERNEL);
	अगर (!pd_bo_list_entries) अणु
		pr_err("%s: Failed to allocate PD BO list entries\n", __func__);
		ret = -ENOMEM;
		जाओ out_no_mem;
	पूर्ण

	INIT_LIST_HEAD(&resv_list);
	INIT_LIST_HEAD(&duplicates);

	/* Get all the page directory BOs that need to be reserved */
	i = 0;
	list_क्रम_each_entry(peer_vm, &process_info->vm_list_head,
			    vm_list_node)
		amdgpu_vm_get_pd_bo(peer_vm, &resv_list,
				    &pd_bo_list_entries[i++]);
	/* Add the userptr_inval_list entries to resv_list */
	list_क्रम_each_entry(mem, &process_info->userptr_inval_list,
			    validate_list.head) अणु
		list_add_tail(&mem->resv_list.head, &resv_list);
		mem->resv_list.bo = mem->validate_list.bo;
		mem->resv_list.num_shared = mem->validate_list.num_shared;
	पूर्ण

	/* Reserve all BOs and page tables क्रम validation */
	ret = tपंचांग_eu_reserve_buffers(&ticket, &resv_list, false, &duplicates);
	WARN(!list_empty(&duplicates), "Duplicates should be empty");
	अगर (ret)
		जाओ out_मुक्त;

	amdgpu_sync_create(&sync);

	ret = process_validate_vms(process_info);
	अगर (ret)
		जाओ unreserve_out;

	/* Validate BOs and update GPUVM page tables */
	list_क्रम_each_entry_safe(mem, पंचांगp_mem,
				 &process_info->userptr_inval_list,
				 validate_list.head) अणु
		काष्ठा kfd_bo_बहु_सूची *bo_va_entry;

		bo = mem->bo;

		/* Validate the BO अगर we got user pages */
		अगर (bo->tbo.tपंचांग->pages[0]) अणु
			amdgpu_bo_placement_from_करोमुख्य(bo, mem->करोमुख्य);
			ret = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
			अगर (ret) अणु
				pr_err("%s: failed to validate BO\n", __func__);
				जाओ unreserve_out;
			पूर्ण
		पूर्ण

		list_move_tail(&mem->validate_list.head,
			       &process_info->userptr_valid_list);

		/* Update mapping. If the BO was not validated
		 * (because we couldn't get user pages), this will
		 * clear the page table entries, which will result in
		 * VM faults अगर the GPU tries to access the invalid
		 * memory.
		 */
		list_क्रम_each_entry(bo_va_entry, &mem->bo_बहु_सूची, bo_list) अणु
			अगर (!bo_va_entry->is_mapped)
				जारी;

			ret = update_gpuvm_pte((काष्ठा amdgpu_device *)
					       bo_va_entry->kgd_dev,
					       bo_va_entry, &sync);
			अगर (ret) अणु
				pr_err("%s: update PTE failed\n", __func__);
				/* make sure this माला_लो validated again */
				atomic_inc(&mem->invalid);
				जाओ unreserve_out;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Update page directories */
	ret = process_update_pds(process_info, &sync);

unreserve_out:
	tपंचांग_eu_backoff_reservation(&ticket, &resv_list);
	amdgpu_sync_रुको(&sync, false);
	amdgpu_sync_मुक्त(&sync);
out_मुक्त:
	kमुक्त(pd_bo_list_entries);
out_no_mem:

	वापस ret;
पूर्ण

/* Worker callback to restore evicted userptr BOs
 *
 * Tries to update and validate all userptr BOs. If successful and no
 * concurrent evictions happened, the queues are restarted. Otherwise,
 * reschedule क्रम another attempt later.
 */
अटल व्योम amdgpu_amdkfd_restore_userptr_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा amdkfd_process_info *process_info =
		container_of(dwork, काष्ठा amdkfd_process_info,
			     restore_userptr_work);
	काष्ठा task_काष्ठा *usertask;
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक evicted_bos;

	evicted_bos = atomic_पढ़ो(&process_info->evicted_bos);
	अगर (!evicted_bos)
		वापस;

	/* Reference task and mm in हाल of concurrent process termination */
	usertask = get_pid_task(process_info->pid, PIDTYPE_PID);
	अगर (!usertask)
		वापस;
	mm = get_task_mm(usertask);
	अगर (!mm) अणु
		put_task_काष्ठा(usertask);
		वापस;
	पूर्ण

	mutex_lock(&process_info->lock);

	अगर (update_invalid_user_pages(process_info, mm))
		जाओ unlock_out;
	/* userptr_inval_list can be empty अगर all evicted userptr BOs
	 * have been मुक्तd. In that हाल there is nothing to validate
	 * and we can just restart the queues.
	 */
	अगर (!list_empty(&process_info->userptr_inval_list)) अणु
		अगर (atomic_पढ़ो(&process_info->evicted_bos) != evicted_bos)
			जाओ unlock_out; /* Concurrent eviction, try again */

		अगर (validate_invalid_user_pages(process_info))
			जाओ unlock_out;
	पूर्ण
	/* Final check क्रम concurrent evicton and atomic update. If
	 * another eviction happens after successful update, it will
	 * be a first eviction that calls quiesce_mm. The eviction
	 * reference counting inside KFD will handle this हाल.
	 */
	अगर (atomic_cmpxchg(&process_info->evicted_bos, evicted_bos, 0) !=
	    evicted_bos)
		जाओ unlock_out;
	evicted_bos = 0;
	अगर (kgd2kfd_resume_mm(mm)) अणु
		pr_err("%s: Failed to resume KFD\n", __func__);
		/* No recovery from this failure. Probably the CP is
		 * hanging. No poपूर्णांक trying again.
		 */
	पूर्ण

unlock_out:
	mutex_unlock(&process_info->lock);
	mmput(mm);
	put_task_काष्ठा(usertask);

	/* If validation failed, reschedule another attempt */
	अगर (evicted_bos)
		schedule_delayed_work(&process_info->restore_userptr_work,
			msecs_to_jअगरfies(AMDGPU_USERPTR_RESTORE_DELAY_MS));
पूर्ण

/** amdgpu_amdkfd_gpuvm_restore_process_bos - Restore all BOs क्रम the given
 *   KFD process identअगरied by process_info
 *
 * @process_info: amdkfd_process_info of the KFD process
 *
 * After memory eviction, restore thपढ़ो calls this function. The function
 * should be called when the Process is still valid. BO restore involves -
 *
 * 1.  Release old eviction fence and create new one
 * 2.  Get two copies of PD BO list from all the VMs. Keep one copy as pd_list.
 * 3   Use the second PD list and kfd_bo_list to create a list (ctx.list) of
 *     BOs that need to be reserved.
 * 4.  Reserve all the BOs
 * 5.  Validate of PD and PT BOs.
 * 6.  Validate all KFD BOs using kfd_bo_list and Map them and add new fence
 * 7.  Add fence to all PD and PT BOs.
 * 8.  Unreserve all BOs
 */
पूर्णांक amdgpu_amdkfd_gpuvm_restore_process_bos(व्योम *info, काष्ठा dma_fence **ef)
अणु
	काष्ठा amdgpu_bo_list_entry *pd_bo_list;
	काष्ठा amdkfd_process_info *process_info = info;
	काष्ठा amdgpu_vm *peer_vm;
	काष्ठा kgd_mem *mem;
	काष्ठा bo_vm_reservation_context ctx;
	काष्ठा amdgpu_amdkfd_fence *new_fence;
	पूर्णांक ret = 0, i;
	काष्ठा list_head duplicate_save;
	काष्ठा amdgpu_sync sync_obj;
	अचिन्हित दीर्घ failed_size = 0;
	अचिन्हित दीर्घ total_size = 0;

	INIT_LIST_HEAD(&duplicate_save);
	INIT_LIST_HEAD(&ctx.list);
	INIT_LIST_HEAD(&ctx.duplicates);

	pd_bo_list = kसुस्मृति(process_info->n_vms,
			     माप(काष्ठा amdgpu_bo_list_entry),
			     GFP_KERNEL);
	अगर (!pd_bo_list)
		वापस -ENOMEM;

	i = 0;
	mutex_lock(&process_info->lock);
	list_क्रम_each_entry(peer_vm, &process_info->vm_list_head,
			vm_list_node)
		amdgpu_vm_get_pd_bo(peer_vm, &ctx.list, &pd_bo_list[i++]);

	/* Reserve all BOs and page tables/directory. Add all BOs from
	 * kfd_bo_list to ctx.list
	 */
	list_क्रम_each_entry(mem, &process_info->kfd_bo_list,
			    validate_list.head) अणु

		list_add_tail(&mem->resv_list.head, &ctx.list);
		mem->resv_list.bo = mem->validate_list.bo;
		mem->resv_list.num_shared = mem->validate_list.num_shared;
	पूर्ण

	ret = tपंचांग_eu_reserve_buffers(&ctx.ticket, &ctx.list,
				     false, &duplicate_save);
	अगर (ret) अणु
		pr_debug("Memory eviction: TTM Reserve Failed. Try again\n");
		जाओ tपंचांग_reserve_fail;
	पूर्ण

	amdgpu_sync_create(&sync_obj);

	/* Validate PDs and PTs */
	ret = process_validate_vms(process_info);
	अगर (ret)
		जाओ validate_map_fail;

	ret = process_sync_pds_resv(process_info, &sync_obj);
	अगर (ret) अणु
		pr_debug("Memory eviction: Failed to sync to PD BO moving fence. Try again\n");
		जाओ validate_map_fail;
	पूर्ण

	/* Validate BOs and map them to GPUVM (update VM page tables). */
	list_क्रम_each_entry(mem, &process_info->kfd_bo_list,
			    validate_list.head) अणु

		काष्ठा amdgpu_bo *bo = mem->bo;
		uपूर्णांक32_t करोमुख्य = mem->करोमुख्य;
		काष्ठा kfd_bo_बहु_सूची *bo_va_entry;

		total_size += amdgpu_bo_size(bo);

		ret = amdgpu_amdkfd_bo_validate(bo, करोमुख्य, false);
		अगर (ret) अणु
			pr_debug("Memory eviction: Validate BOs failed\n");
			failed_size += amdgpu_bo_size(bo);
			ret = amdgpu_amdkfd_bo_validate(bo,
						AMDGPU_GEM_DOMAIN_GTT, false);
			अगर (ret) अणु
				pr_debug("Memory eviction: Try again\n");
				जाओ validate_map_fail;
			पूर्ण
		पूर्ण
		ret = amdgpu_sync_fence(&sync_obj, bo->tbo.moving);
		अगर (ret) अणु
			pr_debug("Memory eviction: Sync BO fence failed. Try again\n");
			जाओ validate_map_fail;
		पूर्ण
		list_क्रम_each_entry(bo_va_entry, &mem->bo_बहु_सूची,
				    bo_list) अणु
			ret = update_gpuvm_pte((काष्ठा amdgpu_device *)
					      bo_va_entry->kgd_dev,
					      bo_va_entry,
					      &sync_obj);
			अगर (ret) अणु
				pr_debug("Memory eviction: update PTE failed. Try again\n");
				जाओ validate_map_fail;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (failed_size)
		pr_debug("0x%lx/0x%lx in system\n", failed_size, total_size);

	/* Update page directories */
	ret = process_update_pds(process_info, &sync_obj);
	अगर (ret) अणु
		pr_debug("Memory eviction: update PDs failed. Try again\n");
		जाओ validate_map_fail;
	पूर्ण

	/* Wait क्रम validate and PT updates to finish */
	amdgpu_sync_रुको(&sync_obj, false);

	/* Release old eviction fence and create new one, because fence only
	 * goes from unसंकेतed to संकेतed, fence cannot be reused.
	 * Use context and mm from the old fence.
	 */
	new_fence = amdgpu_amdkfd_fence_create(
				process_info->eviction_fence->base.context,
				process_info->eviction_fence->mm);
	अगर (!new_fence) अणु
		pr_err("Failed to create eviction fence\n");
		ret = -ENOMEM;
		जाओ validate_map_fail;
	पूर्ण
	dma_fence_put(&process_info->eviction_fence->base);
	process_info->eviction_fence = new_fence;
	*ef = dma_fence_get(&new_fence->base);

	/* Attach new eviction fence to all BOs */
	list_क्रम_each_entry(mem, &process_info->kfd_bo_list,
		validate_list.head)
		amdgpu_bo_fence(mem->bo,
			&process_info->eviction_fence->base, true);

	/* Attach eviction fence to PD / PT BOs */
	list_क्रम_each_entry(peer_vm, &process_info->vm_list_head,
			    vm_list_node) अणु
		काष्ठा amdgpu_bo *bo = peer_vm->root.base.bo;

		amdgpu_bo_fence(bo, &process_info->eviction_fence->base, true);
	पूर्ण

validate_map_fail:
	tपंचांग_eu_backoff_reservation(&ctx.ticket, &ctx.list);
	amdgpu_sync_मुक्त(&sync_obj);
tपंचांग_reserve_fail:
	mutex_unlock(&process_info->lock);
	kमुक्त(pd_bo_list);
	वापस ret;
पूर्ण

पूर्णांक amdgpu_amdkfd_add_gws_to_process(व्योम *info, व्योम *gws, काष्ठा kgd_mem **mem)
अणु
	काष्ठा amdkfd_process_info *process_info = (काष्ठा amdkfd_process_info *)info;
	काष्ठा amdgpu_bo *gws_bo = (काष्ठा amdgpu_bo *)gws;
	पूर्णांक ret;

	अगर (!info || !gws)
		वापस -EINVAL;

	*mem = kzalloc(माप(काष्ठा kgd_mem), GFP_KERNEL);
	अगर (!*mem)
		वापस -ENOMEM;

	mutex_init(&(*mem)->lock);
	INIT_LIST_HEAD(&(*mem)->bo_बहु_सूची);
	(*mem)->bo = amdgpu_bo_ref(gws_bo);
	(*mem)->करोमुख्य = AMDGPU_GEM_DOMAIN_GWS;
	(*mem)->process_info = process_info;
	add_kgd_mem_to_kfd_bo_list(*mem, process_info, false);
	amdgpu_sync_create(&(*mem)->sync);


	/* Validate gws bo the first समय it is added to process */
	mutex_lock(&(*mem)->process_info->lock);
	ret = amdgpu_bo_reserve(gws_bo, false);
	अगर (unlikely(ret)) अणु
		pr_err("Reserve gws bo failed %d\n", ret);
		जाओ bo_reservation_failure;
	पूर्ण

	ret = amdgpu_amdkfd_bo_validate(gws_bo, AMDGPU_GEM_DOMAIN_GWS, true);
	अगर (ret) अणु
		pr_err("GWS BO validate failed %d\n", ret);
		जाओ bo_validation_failure;
	पूर्ण
	/* GWS resource is shared b/t amdgpu and amdkfd
	 * Add process eviction fence to bo so they can
	 * evict each other.
	 */
	ret = dma_resv_reserve_shared(gws_bo->tbo.base.resv, 1);
	अगर (ret)
		जाओ reserve_shared_fail;
	amdgpu_bo_fence(gws_bo, &process_info->eviction_fence->base, true);
	amdgpu_bo_unreserve(gws_bo);
	mutex_unlock(&(*mem)->process_info->lock);

	वापस ret;

reserve_shared_fail:
bo_validation_failure:
	amdgpu_bo_unreserve(gws_bo);
bo_reservation_failure:
	mutex_unlock(&(*mem)->process_info->lock);
	amdgpu_sync_मुक्त(&(*mem)->sync);
	हटाओ_kgd_mem_from_kfd_bo_list(*mem, process_info);
	amdgpu_bo_unref(&gws_bo);
	mutex_destroy(&(*mem)->lock);
	kमुक्त(*mem);
	*mem = शून्य;
	वापस ret;
पूर्ण

पूर्णांक amdgpu_amdkfd_हटाओ_gws_from_process(व्योम *info, व्योम *mem)
अणु
	पूर्णांक ret;
	काष्ठा amdkfd_process_info *process_info = (काष्ठा amdkfd_process_info *)info;
	काष्ठा kgd_mem *kgd_mem = (काष्ठा kgd_mem *)mem;
	काष्ठा amdgpu_bo *gws_bo = kgd_mem->bo;

	/* Remove BO from process's validate list so restore worker won't touch
	 * it anymore
	 */
	हटाओ_kgd_mem_from_kfd_bo_list(kgd_mem, process_info);

	ret = amdgpu_bo_reserve(gws_bo, false);
	अगर (unlikely(ret)) अणु
		pr_err("Reserve gws bo failed %d\n", ret);
		//TODO add BO back to validate_list?
		वापस ret;
	पूर्ण
	amdgpu_amdkfd_हटाओ_eviction_fence(gws_bo,
			process_info->eviction_fence);
	amdgpu_bo_unreserve(gws_bo);
	amdgpu_sync_मुक्त(&kgd_mem->sync);
	amdgpu_bo_unref(&gws_bo);
	mutex_destroy(&kgd_mem->lock);
	kमुक्त(mem);
	वापस 0;
पूर्ण

/* Returns GPU-specअगरic tiling mode inक्रमmation */
पूर्णांक amdgpu_amdkfd_get_tile_config(काष्ठा kgd_dev *kgd,
				काष्ठा tile_config *config)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	config->gb_addr_config = adev->gfx.config.gb_addr_config;
	config->tile_config_ptr = adev->gfx.config.tile_mode_array;
	config->num_tile_configs =
			ARRAY_SIZE(adev->gfx.config.tile_mode_array);
	config->macro_tile_config_ptr =
			adev->gfx.config.macrotile_mode_array;
	config->num_macro_tile_configs =
			ARRAY_SIZE(adev->gfx.config.macrotile_mode_array);

	/* Those values are not set from GFX9 onwards */
	config->num_banks = adev->gfx.config.num_banks;
	config->num_ranks = adev->gfx.config.num_ranks;

	वापस 0;
पूर्ण
