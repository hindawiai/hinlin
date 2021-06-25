<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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

#समावेश "amdgpu_vm.h"
#समावेश "amdgpu_object.h"
#समावेश "amdgpu_trace.h"

/**
 * amdgpu_vm_cpu_map_table - make sure new PDs/PTs are kmapped
 *
 * @table: newly allocated or validated PD/PT
 */
अटल पूर्णांक amdgpu_vm_cpu_map_table(काष्ठा amdgpu_bo *table)
अणु
	वापस amdgpu_bo_kmap(table, शून्य);
पूर्ण

/**
 * amdgpu_vm_cpu_prepare - prepare page table update with the CPU
 *
 * @p: see amdgpu_vm_update_params definition
 * @resv: reservation object with embedded fence
 * @sync_mode: synchronization mode
 *
 * Returns:
 * Negativ त्रुटि_सं, 0 क्रम success.
 */
अटल पूर्णांक amdgpu_vm_cpu_prepare(काष्ठा amdgpu_vm_update_params *p,
				 काष्ठा dma_resv *resv,
				 क्रमागत amdgpu_sync_mode sync_mode)
अणु
	अगर (!resv)
		वापस 0;

	वापस amdgpu_bo_sync_रुको_resv(p->adev, resv, sync_mode, p->vm, true);
पूर्ण

/**
 * amdgpu_vm_cpu_update - helper to update page tables via CPU
 *
 * @p: see amdgpu_vm_update_params definition
 * @bo: PD/PT to update
 * @pe: byte offset of the PDE/PTE, relative to start of PDB/PTB
 * @addr: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 * @flags: hw access flags
 *
 * Write count number of PT/PD entries directly.
 */
अटल पूर्णांक amdgpu_vm_cpu_update(काष्ठा amdgpu_vm_update_params *p,
				काष्ठा amdgpu_bo *bo, uपूर्णांक64_t pe,
				uपूर्णांक64_t addr, अचिन्हित count, uपूर्णांक32_t incr,
				uपूर्णांक64_t flags)
अणु
	अचिन्हित पूर्णांक i;
	uपूर्णांक64_t value;
	पूर्णांक r;

	अगर (bo->tbo.moving) अणु
		r = dma_fence_रुको(bo->tbo.moving, true);
		अगर (r)
			वापस r;
	पूर्ण

	pe += (अचिन्हित दीर्घ)amdgpu_bo_kptr(bo);

	trace_amdgpu_vm_set_ptes(pe, addr, count, incr, flags, p->immediate);

	क्रम (i = 0; i < count; i++) अणु
		value = p->pages_addr ?
			amdgpu_vm_map_gart(p->pages_addr, addr) :
			addr;
		amdgpu_gmc_set_pte_pde(p->adev, (व्योम *)(uपूर्णांकptr_t)pe,
				       i, value, flags);
		addr += incr;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_vm_cpu_commit - commit page table update to the HW
 *
 * @p: see amdgpu_vm_update_params definition
 * @fence: unused
 *
 * Make sure that the hardware sees the page table updates.
 */
अटल पूर्णांक amdgpu_vm_cpu_commit(काष्ठा amdgpu_vm_update_params *p,
				काष्ठा dma_fence **fence)
अणु
	/* Flush HDP */
	mb();
	amdgpu_asic_flush_hdp(p->adev, शून्य);
	वापस 0;
पूर्ण

स्थिर काष्ठा amdgpu_vm_update_funcs amdgpu_vm_cpu_funcs = अणु
	.map_table = amdgpu_vm_cpu_map_table,
	.prepare = amdgpu_vm_cpu_prepare,
	.update = amdgpu_vm_cpu_update,
	.commit = amdgpu_vm_cpu_commit
पूर्ण;
