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
#समावेश "amdgpu_job.h"
#समावेश "amdgpu_object.h"
#समावेश "amdgpu_trace.h"

#घोषणा AMDGPU_VM_SDMA_MIN_NUM_DW	256u
#घोषणा AMDGPU_VM_SDMA_MAX_NUM_DW	(16u * 1024u)

/**
 * amdgpu_vm_sdma_map_table - make sure new PDs/PTs are GTT mapped
 *
 * @table: newly allocated or validated PD/PT
 */
अटल पूर्णांक amdgpu_vm_sdma_map_table(काष्ठा amdgpu_bo *table)
अणु
	पूर्णांक r;

	r = amdgpu_tपंचांग_alloc_gart(&table->tbo);
	अगर (r)
		वापस r;

	अगर (table->shaकरोw)
		r = amdgpu_tपंचांग_alloc_gart(&table->shaकरोw->tbo);

	वापस r;
पूर्ण

/**
 * amdgpu_vm_sdma_prepare - prepare SDMA command submission
 *
 * @p: see amdgpu_vm_update_params definition
 * @resv: reservation object with embedded fence
 * @sync_mode: synchronization mode
 *
 * Returns:
 * Negativ त्रुटि_सं, 0 क्रम success.
 */
अटल पूर्णांक amdgpu_vm_sdma_prepare(काष्ठा amdgpu_vm_update_params *p,
				  काष्ठा dma_resv *resv,
				  क्रमागत amdgpu_sync_mode sync_mode)
अणु
	क्रमागत amdgpu_ib_pool_type pool = p->immediate ? AMDGPU_IB_POOL_IMMEDIATE
		: AMDGPU_IB_POOL_DELAYED;
	अचिन्हित पूर्णांक ndw = AMDGPU_VM_SDMA_MIN_NUM_DW;
	पूर्णांक r;

	r = amdgpu_job_alloc_with_ib(p->adev, ndw * 4, pool, &p->job);
	अगर (r)
		वापस r;

	p->num_dw_left = ndw;

	अगर (!resv)
		वापस 0;

	वापस amdgpu_sync_resv(p->adev, &p->job->sync, resv, sync_mode, p->vm);
पूर्ण

/**
 * amdgpu_vm_sdma_commit - commit SDMA command submission
 *
 * @p: see amdgpu_vm_update_params definition
 * @fence: resulting fence
 *
 * Returns:
 * Negativ त्रुटि_सं, 0 क्रम success.
 */
अटल पूर्णांक amdgpu_vm_sdma_commit(काष्ठा amdgpu_vm_update_params *p,
				 काष्ठा dma_fence **fence)
अणु
	काष्ठा amdgpu_ib *ib = p->job->ibs;
	काष्ठा drm_sched_entity *entity;
	काष्ठा amdgpu_ring *ring;
	काष्ठा dma_fence *f;
	पूर्णांक r;

	entity = p->immediate ? &p->vm->immediate : &p->vm->delayed;
	ring = container_of(entity->rq->sched, काष्ठा amdgpu_ring, sched);

	WARN_ON(ib->length_dw == 0);
	amdgpu_ring_pad_ib(ring, ib);
	WARN_ON(ib->length_dw > p->num_dw_left);
	r = amdgpu_job_submit(p->job, entity, AMDGPU_FENCE_OWNER_VM, &f);
	अगर (r)
		जाओ error;

	अगर (p->unlocked) अणु
		काष्ठा dma_fence *पंचांगp = dma_fence_get(f);

		swap(p->vm->last_unlocked, f);
		dma_fence_put(पंचांगp);
	पूर्ण अन्यथा अणु
		amdgpu_bo_fence(p->vm->root.base.bo, f, true);
	पूर्ण

	अगर (fence && !p->immediate)
		swap(*fence, f);
	dma_fence_put(f);
	वापस 0;

error:
	amdgpu_job_मुक्त(p->job);
	वापस r;
पूर्ण

/**
 * amdgpu_vm_sdma_copy_ptes - copy the PTEs from mapping
 *
 * @p: see amdgpu_vm_update_params definition
 * @bo: PD/PT to update
 * @pe: addr of the page entry
 * @count: number of page entries to copy
 *
 * Traces the parameters and calls the DMA function to copy the PTEs.
 */
अटल व्योम amdgpu_vm_sdma_copy_ptes(काष्ठा amdgpu_vm_update_params *p,
				     काष्ठा amdgpu_bo *bo, uपूर्णांक64_t pe,
				     अचिन्हित count)
अणु
	काष्ठा amdgpu_ib *ib = p->job->ibs;
	uपूर्णांक64_t src = ib->gpu_addr;

	src += p->num_dw_left * 4;

	pe += amdgpu_gmc_sign_extend(amdgpu_bo_gpu_offset_no_check(bo));
	trace_amdgpu_vm_copy_ptes(pe, src, count, p->immediate);

	amdgpu_vm_copy_pte(p->adev, ib, pe, src, count);
पूर्ण

/**
 * amdgpu_vm_sdma_set_ptes - helper to call the right asic function
 *
 * @p: see amdgpu_vm_update_params definition
 * @bo: PD/PT to update
 * @pe: byte offset of the PDE/PTE, relative to start of PDB/PTB
 * @addr: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 * @flags: hw access flags
 *
 * Traces the parameters and calls the right asic functions
 * to setup the page table using the DMA.
 */
अटल व्योम amdgpu_vm_sdma_set_ptes(काष्ठा amdgpu_vm_update_params *p,
				    काष्ठा amdgpu_bo *bo, uपूर्णांक64_t pe,
				    uपूर्णांक64_t addr, अचिन्हित count,
				    uपूर्णांक32_t incr, uपूर्णांक64_t flags)
अणु
	काष्ठा amdgpu_ib *ib = p->job->ibs;

	pe += amdgpu_gmc_sign_extend(amdgpu_bo_gpu_offset_no_check(bo));
	trace_amdgpu_vm_set_ptes(pe, addr, count, incr, flags, p->immediate);
	अगर (count < 3) अणु
		amdgpu_vm_ग_लिखो_pte(p->adev, ib, pe, addr | flags,
				    count, incr);
	पूर्ण अन्यथा अणु
		amdgpu_vm_set_pte_pde(p->adev, ib, pe, addr,
				      count, incr, flags);
	पूर्ण
पूर्ण

/**
 * amdgpu_vm_sdma_update - execute VM update
 *
 * @p: see amdgpu_vm_update_params definition
 * @bo: PD/PT to update
 * @pe: byte offset of the PDE/PTE, relative to start of PDB/PTB
 * @addr: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 * @flags: hw access flags
 *
 * Reserve space in the IB, setup mapping buffer on demand and ग_लिखो commands to
 * the IB.
 */
अटल पूर्णांक amdgpu_vm_sdma_update(काष्ठा amdgpu_vm_update_params *p,
				 काष्ठा amdgpu_bo *bo, uपूर्णांक64_t pe,
				 uपूर्णांक64_t addr, अचिन्हित count, uपूर्णांक32_t incr,
				 uपूर्णांक64_t flags)
अणु
	क्रमागत amdgpu_ib_pool_type pool = p->immediate ? AMDGPU_IB_POOL_IMMEDIATE
		: AMDGPU_IB_POOL_DELAYED;
	अचिन्हित पूर्णांक i, ndw, nptes;
	uपूर्णांक64_t *pte;
	पूर्णांक r;

	/* Wait क्रम PD/PT moves to be completed */
	r = amdgpu_sync_fence(&p->job->sync, bo->tbo.moving);
	अगर (r)
		वापस r;

	करो अणु
		ndw = p->num_dw_left;
		ndw -= p->job->ibs->length_dw;

		अगर (ndw < 32) अणु
			r = amdgpu_vm_sdma_commit(p, शून्य);
			अगर (r)
				वापस r;

			/* estimate how many dw we need */
			ndw = 32;
			अगर (p->pages_addr)
				ndw += count * 2;
			ndw = max(ndw, AMDGPU_VM_SDMA_MIN_NUM_DW);
			ndw = min(ndw, AMDGPU_VM_SDMA_MAX_NUM_DW);

			r = amdgpu_job_alloc_with_ib(p->adev, ndw * 4, pool,
						     &p->job);
			अगर (r)
				वापस r;

			p->num_dw_left = ndw;
		पूर्ण

		अगर (!p->pages_addr) अणु
			/* set page commands needed */
			अगर (bo->shaकरोw)
				amdgpu_vm_sdma_set_ptes(p, bo->shaकरोw, pe, addr,
							count, incr, flags);
			amdgpu_vm_sdma_set_ptes(p, bo, pe, addr, count,
						incr, flags);
			वापस 0;
		पूर्ण

		/* copy commands needed */
		ndw -= p->adev->vm_manager.vm_pte_funcs->copy_pte_num_dw *
			(bo->shaकरोw ? 2 : 1);

		/* क्रम padding */
		ndw -= 7;

		nptes = min(count, ndw / 2);

		/* Put the PTEs at the end of the IB. */
		p->num_dw_left -= nptes * 2;
		pte = (uपूर्णांक64_t *)&(p->job->ibs->ptr[p->num_dw_left]);
		क्रम (i = 0; i < nptes; ++i, addr += incr) अणु
			pte[i] = amdgpu_vm_map_gart(p->pages_addr, addr);
			pte[i] |= flags;
		पूर्ण

		अगर (bo->shaकरोw)
			amdgpu_vm_sdma_copy_ptes(p, bo->shaकरोw, pe, nptes);
		amdgpu_vm_sdma_copy_ptes(p, bo, pe, nptes);

		pe += nptes * 8;
		count -= nptes;
	पूर्ण जबतक (count);

	वापस 0;
पूर्ण

स्थिर काष्ठा amdgpu_vm_update_funcs amdgpu_vm_sdma_funcs = अणु
	.map_table = amdgpu_vm_sdma_map_table,
	.prepare = amdgpu_vm_sdma_prepare,
	.update = amdgpu_vm_sdma_update,
	.commit = amdgpu_vm_sdma_commit
पूर्ण;
