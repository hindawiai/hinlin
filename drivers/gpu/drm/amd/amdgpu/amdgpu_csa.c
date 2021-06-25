<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

 * * Author: Monk.liu@amd.com
 */

#समावेश "amdgpu.h"

uपूर्णांक64_t amdgpu_csa_vaddr(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t addr = adev->vm_manager.max_pfn << AMDGPU_GPU_PAGE_SHIFT;

	addr -= AMDGPU_VA_RESERVED_SIZE;
	addr = amdgpu_gmc_sign_extend(addr);

	वापस addr;
पूर्ण

पूर्णांक amdgpu_allocate_अटल_csa(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_bo **bo,
				u32 करोमुख्य, uपूर्णांक32_t size)
अणु
	व्योम *ptr;

	amdgpu_bo_create_kernel(adev, size, PAGE_SIZE,
				करोमुख्य, bo,
				शून्य, &ptr);
	अगर (!*bo)
		वापस -ENOMEM;

	स_रखो(ptr, 0, size);
	adev->virt.csa_cpu_addr = ptr;
	वापस 0;
पूर्ण

व्योम amdgpu_मुक्त_अटल_csa(काष्ठा amdgpu_bo **bo)
अणु
	amdgpu_bo_मुक्त_kernel(bo, शून्य, शून्य);
पूर्ण

/*
 * amdgpu_map_अटल_csa should be called during amdgpu_vm_init
 * it maps भव address amdgpu_csa_vaddr() to this VM, and each command
 * submission of GFX should use this भव address within META_DATA init
 * package to support SRIOV gfx preemption.
 */
पूर्णांक amdgpu_map_अटल_csa(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm,
			  काष्ठा amdgpu_bo *bo, काष्ठा amdgpu_bo_va **bo_va,
			  uपूर्णांक64_t csa_addr, uपूर्णांक32_t size)
अणु
	काष्ठा ww_acquire_ctx ticket;
	काष्ठा list_head list;
	काष्ठा amdgpu_bo_list_entry pd;
	काष्ठा tपंचांग_validate_buffer csa_tv;
	पूर्णांक r;

	INIT_LIST_HEAD(&list);
	INIT_LIST_HEAD(&csa_tv.head);
	csa_tv.bo = &bo->tbo;
	csa_tv.num_shared = 1;

	list_add(&csa_tv.head, &list);
	amdgpu_vm_get_pd_bo(vm, &list, &pd);

	r = tपंचांग_eu_reserve_buffers(&ticket, &list, true, शून्य);
	अगर (r) अणु
		DRM_ERROR("failed to reserve CSA,PD BOs: err=%d\n", r);
		वापस r;
	पूर्ण

	*bo_va = amdgpu_vm_bo_add(adev, vm, bo);
	अगर (!*bo_va) अणु
		tपंचांग_eu_backoff_reservation(&ticket, &list);
		DRM_ERROR("failed to create bo_va for static CSA\n");
		वापस -ENOMEM;
	पूर्ण

	r = amdgpu_vm_bo_map(adev, *bo_va, csa_addr, 0, size,
			     AMDGPU_PTE_READABLE | AMDGPU_PTE_WRITEABLE |
			     AMDGPU_PTE_EXECUTABLE);

	अगर (r) अणु
		DRM_ERROR("failed to do bo_map on static CSA, err=%d\n", r);
		amdgpu_vm_bo_rmv(adev, *bo_va);
		tपंचांग_eu_backoff_reservation(&ticket, &list);
		वापस r;
	पूर्ण

	tपंचांग_eu_backoff_reservation(&ticket, &list);
	वापस 0;
पूर्ण
