<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
 */
#अगर_अघोषित __AMDGPU_JOB_H__
#घोषणा __AMDGPU_JOB_H__

/* bit set means command submit involves a preamble IB */
#घोषणा AMDGPU_PREAMBLE_IB_PRESENT          (1 << 0)
/* bit set means preamble IB is first presented in beदीर्घing context */
#घोषणा AMDGPU_PREAMBLE_IB_PRESENT_FIRST    (1 << 1)
/* bit set means context चयन occured */
#घोषणा AMDGPU_HAVE_CTX_SWITCH              (1 << 2)
/* bit set means IB is preempted */
#घोषणा AMDGPU_IB_PREEMPTED                 (1 << 3)

#घोषणा to_amdgpu_job(sched_job)		\
		container_of((sched_job), काष्ठा amdgpu_job, base)

#घोषणा AMDGPU_JOB_GET_VMID(job) ((job) ? (job)->vmid : 0)

काष्ठा amdgpu_fence;
क्रमागत amdgpu_ib_pool_type;

काष्ठा amdgpu_job अणु
	काष्ठा drm_sched_job    base;
	काष्ठा amdgpu_vm	*vm;
	काष्ठा amdgpu_sync	sync;
	काष्ठा amdgpu_sync	sched_sync;
	काष्ठा amdgpu_ib	*ibs;
	काष्ठा dma_fence	*fence; /* the hw fence */
	uपूर्णांक32_t		preamble_status;
	uपूर्णांक32_t                preemption_status;
	uपूर्णांक32_t		num_ibs;
	bool                    vm_needs_flush;
	uपूर्णांक64_t		vm_pd_addr;
	अचिन्हित		vmid;
	अचिन्हित		pasid;
	uपूर्णांक32_t		gds_base, gds_size;
	uपूर्णांक32_t		gws_base, gws_size;
	uपूर्णांक32_t		oa_base, oa_size;
	uपूर्णांक32_t		vram_lost_counter;

	/* user fence handling */
	uपूर्णांक64_t		uf_addr;
	uपूर्णांक64_t		uf_sequence;
पूर्ण;

पूर्णांक amdgpu_job_alloc(काष्ठा amdgpu_device *adev, अचिन्हित num_ibs,
		     काष्ठा amdgpu_job **job, काष्ठा amdgpu_vm *vm);
पूर्णांक amdgpu_job_alloc_with_ib(काष्ठा amdgpu_device *adev, अचिन्हित size,
		क्रमागत amdgpu_ib_pool_type pool, काष्ठा amdgpu_job **job);
व्योम amdgpu_job_मुक्त_resources(काष्ठा amdgpu_job *job);
व्योम amdgpu_job_मुक्त(काष्ठा amdgpu_job *job);
पूर्णांक amdgpu_job_submit(काष्ठा amdgpu_job *job, काष्ठा drm_sched_entity *entity,
		      व्योम *owner, काष्ठा dma_fence **f);
पूर्णांक amdgpu_job_submit_direct(काष्ठा amdgpu_job *job, काष्ठा amdgpu_ring *ring,
			     काष्ठा dma_fence **fence);

व्योम amdgpu_job_stop_all_jobs_on_sched(काष्ठा drm_gpu_scheduler *sched);

#पूर्ण_अगर
