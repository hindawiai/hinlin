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
 *
 * Authors: Christian Kथघnig
 */
#अगर_अघोषित __AMDGPU_RING_H__
#घोषणा __AMDGPU_RING_H__

#समावेश <drm/amdgpu_drm.h>
#समावेश <drm/gpu_scheduler.h>
#समावेश <drm/drm_prपूर्णांक.h>

/* max number of rings */
#घोषणा AMDGPU_MAX_RINGS		28
#घोषणा AMDGPU_MAX_HWIP_RINGS		8
#घोषणा AMDGPU_MAX_GFX_RINGS		2
#घोषणा AMDGPU_MAX_COMPUTE_RINGS	8
#घोषणा AMDGPU_MAX_VCE_RINGS		3
#घोषणा AMDGPU_MAX_UVD_ENC_RINGS	2

#घोषणा AMDGPU_RING_PRIO_DEFAULT	1
#घोषणा AMDGPU_RING_PRIO_MAX		AMDGPU_GFX_PIPE_PRIO_MAX

/* some special values क्रम the owner field */
#घोषणा AMDGPU_FENCE_OWNER_UNDEFINED	((व्योम *)0ul)
#घोषणा AMDGPU_FENCE_OWNER_VM		((व्योम *)1ul)
#घोषणा AMDGPU_FENCE_OWNER_KFD		((व्योम *)2ul)

#घोषणा AMDGPU_FENCE_FLAG_64BIT         (1 << 0)
#घोषणा AMDGPU_FENCE_FLAG_INT           (1 << 1)
#घोषणा AMDGPU_FENCE_FLAG_TC_WB_ONLY    (1 << 2)

#घोषणा to_amdgpu_ring(s) container_of((s), काष्ठा amdgpu_ring, sched)

#घोषणा AMDGPU_IB_POOL_SIZE	(1024 * 1024)

क्रमागत amdgpu_ring_type अणु
	AMDGPU_RING_TYPE_GFX		= AMDGPU_HW_IP_GFX,
	AMDGPU_RING_TYPE_COMPUTE	= AMDGPU_HW_IP_COMPUTE,
	AMDGPU_RING_TYPE_SDMA		= AMDGPU_HW_IP_DMA,
	AMDGPU_RING_TYPE_UVD		= AMDGPU_HW_IP_UVD,
	AMDGPU_RING_TYPE_VCE		= AMDGPU_HW_IP_VCE,
	AMDGPU_RING_TYPE_UVD_ENC	= AMDGPU_HW_IP_UVD_ENC,
	AMDGPU_RING_TYPE_VCN_DEC	= AMDGPU_HW_IP_VCN_DEC,
	AMDGPU_RING_TYPE_VCN_ENC	= AMDGPU_HW_IP_VCN_ENC,
	AMDGPU_RING_TYPE_VCN_JPEG	= AMDGPU_HW_IP_VCN_JPEG,
	AMDGPU_RING_TYPE_KIQ,
	AMDGPU_RING_TYPE_MES
पूर्ण;

क्रमागत amdgpu_ib_pool_type अणु
	/* Normal submissions to the top of the pipeline. */
	AMDGPU_IB_POOL_DELAYED,
	/* Immediate submissions to the bottom of the pipeline. */
	AMDGPU_IB_POOL_IMMEDIATE,
	/* Direct submission to the ring buffer during init and reset. */
	AMDGPU_IB_POOL_सूचीECT,

	AMDGPU_IB_POOL_MAX
पूर्ण;

काष्ठा amdgpu_device;
काष्ठा amdgpu_ring;
काष्ठा amdgpu_ib;
काष्ठा amdgpu_cs_parser;
काष्ठा amdgpu_job;

काष्ठा amdgpu_sched अणु
	u32				num_scheds;
	काष्ठा drm_gpu_scheduler	*sched[AMDGPU_MAX_HWIP_RINGS];
पूर्ण;

/*
 * Fences.
 */
काष्ठा amdgpu_fence_driver अणु
	uपूर्णांक64_t			gpu_addr;
	अस्थिर uपूर्णांक32_t		*cpu_addr;
	/* sync_seq is रक्षित by ring emission lock */
	uपूर्णांक32_t			sync_seq;
	atomic_t			last_seq;
	bool				initialized;
	काष्ठा amdgpu_irq_src		*irq_src;
	अचिन्हित			irq_type;
	काष्ठा समयr_list		fallback_समयr;
	अचिन्हित			num_fences_mask;
	spinlock_t			lock;
	काष्ठा dma_fence		**fences;
पूर्ण;

पूर्णांक amdgpu_fence_driver_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_fence_driver_fini(काष्ठा amdgpu_device *adev);
व्योम amdgpu_fence_driver_क्रमce_completion(काष्ठा amdgpu_ring *ring);

पूर्णांक amdgpu_fence_driver_init_ring(काष्ठा amdgpu_ring *ring,
				  अचिन्हित num_hw_submission,
				  atomic_t *sched_score);
पूर्णांक amdgpu_fence_driver_start_ring(काष्ठा amdgpu_ring *ring,
				   काष्ठा amdgpu_irq_src *irq_src,
				   अचिन्हित irq_type);
व्योम amdgpu_fence_driver_suspend(काष्ठा amdgpu_device *adev);
व्योम amdgpu_fence_driver_resume(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_fence_emit(काष्ठा amdgpu_ring *ring, काष्ठा dma_fence **fence,
		      अचिन्हित flags);
पूर्णांक amdgpu_fence_emit_polling(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t *s,
			      uपूर्णांक32_t समयout);
bool amdgpu_fence_process(काष्ठा amdgpu_ring *ring);
पूर्णांक amdgpu_fence_रुको_empty(काष्ठा amdgpu_ring *ring);
चिन्हित दीर्घ amdgpu_fence_रुको_polling(काष्ठा amdgpu_ring *ring,
				      uपूर्णांक32_t रुको_seq,
				      चिन्हित दीर्घ समयout);
अचिन्हित amdgpu_fence_count_emitted(काष्ठा amdgpu_ring *ring);

/*
 * Rings.
 */

/* provided by hw blocks that expose a ring buffer क्रम commands */
काष्ठा amdgpu_ring_funcs अणु
	क्रमागत amdgpu_ring_type	type;
	uपूर्णांक32_t		align_mask;
	u32			nop;
	bool			support_64bit_ptrs;
	bool			no_user_fence;
	अचिन्हित		vmhub;
	अचिन्हित		extra_dw;

	/* ring पढ़ो/ग_लिखो ptr handling */
	u64 (*get_rptr)(काष्ठा amdgpu_ring *ring);
	u64 (*get_wptr)(काष्ठा amdgpu_ring *ring);
	व्योम (*set_wptr)(काष्ठा amdgpu_ring *ring);
	/* validating and patching of IBs */
	पूर्णांक (*parse_cs)(काष्ठा amdgpu_cs_parser *p, uपूर्णांक32_t ib_idx);
	पूर्णांक (*patch_cs_in_place)(काष्ठा amdgpu_cs_parser *p, uपूर्णांक32_t ib_idx);
	/* स्थिरants to calculate how many DW are needed क्रम an emit */
	अचिन्हित emit_frame_size;
	अचिन्हित emit_ib_size;
	/* command emit functions */
	व्योम (*emit_ib)(काष्ठा amdgpu_ring *ring,
			काष्ठा amdgpu_job *job,
			काष्ठा amdgpu_ib *ib,
			uपूर्णांक32_t flags);
	व्योम (*emit_fence)(काष्ठा amdgpu_ring *ring, uपूर्णांक64_t addr,
			   uपूर्णांक64_t seq, अचिन्हित flags);
	व्योम (*emit_pipeline_sync)(काष्ठा amdgpu_ring *ring);
	व्योम (*emit_vm_flush)(काष्ठा amdgpu_ring *ring, अचिन्हित vmid,
			      uपूर्णांक64_t pd_addr);
	व्योम (*emit_hdp_flush)(काष्ठा amdgpu_ring *ring);
	व्योम (*emit_gds_चयन)(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t vmid,
				uपूर्णांक32_t gds_base, uपूर्णांक32_t gds_size,
				uपूर्णांक32_t gws_base, uपूर्णांक32_t gws_size,
				uपूर्णांक32_t oa_base, uपूर्णांक32_t oa_size);
	/* testing functions */
	पूर्णांक (*test_ring)(काष्ठा amdgpu_ring *ring);
	पूर्णांक (*test_ib)(काष्ठा amdgpu_ring *ring, दीर्घ समयout);
	/* insert NOP packets */
	व्योम (*insert_nop)(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t count);
	व्योम (*insert_start)(काष्ठा amdgpu_ring *ring);
	व्योम (*insert_end)(काष्ठा amdgpu_ring *ring);
	/* pad the indirect buffer to the necessary number of dw */
	व्योम (*pad_ib)(काष्ठा amdgpu_ring *ring, काष्ठा amdgpu_ib *ib);
	अचिन्हित (*init_cond_exec)(काष्ठा amdgpu_ring *ring);
	व्योम (*patch_cond_exec)(काष्ठा amdgpu_ring *ring, अचिन्हित offset);
	/* note usage क्रम घड़ी and घातer gating */
	व्योम (*begin_use)(काष्ठा amdgpu_ring *ring);
	व्योम (*end_use)(काष्ठा amdgpu_ring *ring);
	व्योम (*emit_चयन_buffer) (काष्ठा amdgpu_ring *ring);
	व्योम (*emit_cntxcntl) (काष्ठा amdgpu_ring *ring, uपूर्णांक32_t flags);
	व्योम (*emit_rreg)(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg,
			  uपूर्णांक32_t reg_val_offs);
	व्योम (*emit_wreg)(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg, uपूर्णांक32_t val);
	व्योम (*emit_reg_रुको)(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg,
			      uपूर्णांक32_t val, uपूर्णांक32_t mask);
	व्योम (*emit_reg_ग_लिखो_reg_रुको)(काष्ठा amdgpu_ring *ring,
					uपूर्णांक32_t reg0, uपूर्णांक32_t reg1,
					uपूर्णांक32_t ref, uपूर्णांक32_t mask);
	व्योम (*emit_frame_cntl)(काष्ठा amdgpu_ring *ring, bool start,
				bool secure);
	/* Try to soft recover the ring to make the fence संकेत */
	व्योम (*soft_recovery)(काष्ठा amdgpu_ring *ring, अचिन्हित vmid);
	पूर्णांक (*preempt_ib)(काष्ठा amdgpu_ring *ring);
	व्योम (*emit_mem_sync)(काष्ठा amdgpu_ring *ring);
	व्योम (*emit_wave_limit)(काष्ठा amdgpu_ring *ring, bool enable);
पूर्ण;

काष्ठा amdgpu_ring अणु
	काष्ठा amdgpu_device		*adev;
	स्थिर काष्ठा amdgpu_ring_funcs	*funcs;
	काष्ठा amdgpu_fence_driver	fence_drv;
	काष्ठा drm_gpu_scheduler	sched;

	काष्ठा amdgpu_bo	*ring_obj;
	अस्थिर uपूर्णांक32_t	*ring;
	अचिन्हित		rptr_offs;
	u64			wptr;
	u64			wptr_old;
	अचिन्हित		ring_size;
	अचिन्हित		max_dw;
	पूर्णांक			count_dw;
	uपूर्णांक64_t		gpu_addr;
	uपूर्णांक64_t		ptr_mask;
	uपूर्णांक32_t		buf_mask;
	u32			idx;
	u32			me;
	u32			pipe;
	u32			queue;
	काष्ठा amdgpu_bo	*mqd_obj;
	uपूर्णांक64_t                mqd_gpu_addr;
	व्योम                    *mqd_ptr;
	uपूर्णांक64_t                eop_gpu_addr;
	u32			करोorbell_index;
	bool			use_करोorbell;
	bool			use_pollmem;
	अचिन्हित		wptr_offs;
	अचिन्हित		fence_offs;
	uपूर्णांक64_t		current_ctx;
	अक्षर			name[16];
	u32                     trail_seq;
	अचिन्हित		trail_fence_offs;
	u64			trail_fence_gpu_addr;
	अस्थिर u32		*trail_fence_cpu_addr;
	अचिन्हित		cond_exe_offs;
	u64			cond_exe_gpu_addr;
	अस्थिर u32		*cond_exe_cpu_addr;
	अचिन्हित		vm_inv_eng;
	काष्ठा dma_fence	*vmid_रुको;
	bool			has_compute_vm_bug;
	bool			no_scheduler;
	पूर्णांक			hw_prio;

#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *ent;
#पूर्ण_अगर
पूर्ण;

#घोषणा amdgpu_ring_parse_cs(r, p, ib) ((r)->funcs->parse_cs((p), (ib)))
#घोषणा amdgpu_ring_patch_cs_in_place(r, p, ib) ((r)->funcs->patch_cs_in_place((p), (ib)))
#घोषणा amdgpu_ring_test_ring(r) (r)->funcs->test_ring((r))
#घोषणा amdgpu_ring_test_ib(r, t) (r)->funcs->test_ib((r), (t))
#घोषणा amdgpu_ring_get_rptr(r) (r)->funcs->get_rptr((r))
#घोषणा amdgpu_ring_get_wptr(r) (r)->funcs->get_wptr((r))
#घोषणा amdgpu_ring_set_wptr(r) (r)->funcs->set_wptr((r))
#घोषणा amdgpu_ring_emit_ib(r, job, ib, flags) ((r)->funcs->emit_ib((r), (job), (ib), (flags)))
#घोषणा amdgpu_ring_emit_pipeline_sync(r) (r)->funcs->emit_pipeline_sync((r))
#घोषणा amdgpu_ring_emit_vm_flush(r, vmid, addr) (r)->funcs->emit_vm_flush((r), (vmid), (addr))
#घोषणा amdgpu_ring_emit_fence(r, addr, seq, flags) (r)->funcs->emit_fence((r), (addr), (seq), (flags))
#घोषणा amdgpu_ring_emit_gds_चयन(r, v, db, ds, wb, ws, ab, as) (r)->funcs->emit_gds_चयन((r), (v), (db), (ds), (wb), (ws), (ab), (as))
#घोषणा amdgpu_ring_emit_hdp_flush(r) (r)->funcs->emit_hdp_flush((r))
#घोषणा amdgpu_ring_emit_चयन_buffer(r) (r)->funcs->emit_चयन_buffer((r))
#घोषणा amdgpu_ring_emit_cntxcntl(r, d) (r)->funcs->emit_cntxcntl((r), (d))
#घोषणा amdgpu_ring_emit_rreg(r, d, o) (r)->funcs->emit_rreg((r), (d), (o))
#घोषणा amdgpu_ring_emit_wreg(r, d, v) (r)->funcs->emit_wreg((r), (d), (v))
#घोषणा amdgpu_ring_emit_reg_रुको(r, d, v, m) (r)->funcs->emit_reg_रुको((r), (d), (v), (m))
#घोषणा amdgpu_ring_emit_reg_ग_लिखो_reg_रुको(r, d0, d1, v, m) (r)->funcs->emit_reg_ग_लिखो_reg_रुको((r), (d0), (d1), (v), (m))
#घोषणा amdgpu_ring_emit_frame_cntl(r, b, s) (r)->funcs->emit_frame_cntl((r), (b), (s))
#घोषणा amdgpu_ring_pad_ib(r, ib) ((r)->funcs->pad_ib((r), (ib)))
#घोषणा amdgpu_ring_init_cond_exec(r) (r)->funcs->init_cond_exec((r))
#घोषणा amdgpu_ring_patch_cond_exec(r,o) (r)->funcs->patch_cond_exec((r),(o))
#घोषणा amdgpu_ring_preempt_ib(r) (r)->funcs->preempt_ib(r)

पूर्णांक amdgpu_ring_alloc(काष्ठा amdgpu_ring *ring, अचिन्हित ndw);
व्योम amdgpu_ring_insert_nop(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t count);
व्योम amdgpu_ring_generic_pad_ib(काष्ठा amdgpu_ring *ring, काष्ठा amdgpu_ib *ib);
व्योम amdgpu_ring_commit(काष्ठा amdgpu_ring *ring);
व्योम amdgpu_ring_unकरो(काष्ठा amdgpu_ring *ring);
पूर्णांक amdgpu_ring_init(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ring *ring,
		     अचिन्हित पूर्णांक ring_size, काष्ठा amdgpu_irq_src *irq_src,
		     अचिन्हित पूर्णांक irq_type, अचिन्हित पूर्णांक prio,
		     atomic_t *sched_score);
व्योम amdgpu_ring_fini(काष्ठा amdgpu_ring *ring);
व्योम amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper(काष्ठा amdgpu_ring *ring,
						uपूर्णांक32_t reg0, uपूर्णांक32_t val0,
						uपूर्णांक32_t reg1, uपूर्णांक32_t val1);
bool amdgpu_ring_soft_recovery(काष्ठा amdgpu_ring *ring, अचिन्हित पूर्णांक vmid,
			       काष्ठा dma_fence *fence);

अटल अंतरभूत व्योम amdgpu_ring_set_preempt_cond_exec(काष्ठा amdgpu_ring *ring,
							bool cond_exec)
अणु
	*ring->cond_exe_cpu_addr = cond_exec;
पूर्ण

अटल अंतरभूत व्योम amdgpu_ring_clear_ring(काष्ठा amdgpu_ring *ring)
अणु
	पूर्णांक i = 0;
	जबतक (i <= ring->buf_mask)
		ring->ring[i++] = ring->funcs->nop;

पूर्ण

अटल अंतरभूत व्योम amdgpu_ring_ग_लिखो(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t v)
अणु
	अगर (ring->count_dw <= 0)
		DRM_ERROR("amdgpu: writing more dwords to the ring than expected!\n");
	ring->ring[ring->wptr++ & ring->buf_mask] = v;
	ring->wptr &= ring->ptr_mask;
	ring->count_dw--;
पूर्ण

अटल अंतरभूत व्योम amdgpu_ring_ग_लिखो_multiple(काष्ठा amdgpu_ring *ring,
					      व्योम *src, पूर्णांक count_dw)
अणु
	अचिन्हित occupied, chunk1, chunk2;
	व्योम *dst;

	अगर (unlikely(ring->count_dw < count_dw))
		DRM_ERROR("amdgpu: writing more dwords to the ring than expected!\n");

	occupied = ring->wptr & ring->buf_mask;
	dst = (व्योम *)&ring->ring[occupied];
	chunk1 = ring->buf_mask + 1 - occupied;
	chunk1 = (chunk1 >= count_dw) ? count_dw: chunk1;
	chunk2 = count_dw - chunk1;
	chunk1 <<= 2;
	chunk2 <<= 2;

	अगर (chunk1)
		स_नकल(dst, src, chunk1);

	अगर (chunk2) अणु
		src += chunk1;
		dst = (व्योम *)ring->ring;
		स_नकल(dst, src, chunk2);
	पूर्ण

	ring->wptr += count_dw;
	ring->wptr &= ring->ptr_mask;
	ring->count_dw -= count_dw;
पूर्ण

पूर्णांक amdgpu_ring_test_helper(काष्ठा amdgpu_ring *ring);

पूर्णांक amdgpu_debugfs_ring_init(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_ring *ring);
व्योम amdgpu_debugfs_ring_fini(काष्ठा amdgpu_ring *ring);

#पूर्ण_अगर
