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
#समावेश <linux/mmu_context.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "gc/gc_10_3_0_offset.h"
#समावेश "gc/gc_10_3_0_sh_mask.h"
#समावेश "oss/osssys_5_0_0_offset.h"
#समावेश "oss/osssys_5_0_0_sh_mask.h"
#समावेश "soc15_common.h"
#समावेश "v10_structs.h"
#समावेश "nv.h"
#समावेश "nvd.h"

क्रमागत hqd_dequeue_request_type अणु
	NO_ACTION = 0,
	DRAIN_PIPE,
	RESET_WAVES,
	SAVE_WAVES
पूर्ण;

अटल अंतरभूत काष्ठा amdgpu_device *get_amdgpu_device(काष्ठा kgd_dev *kgd)
अणु
	वापस (काष्ठा amdgpu_device *)kgd;
पूर्ण

अटल व्योम lock_srbm(काष्ठा kgd_dev *kgd, uपूर्णांक32_t mec, uपूर्णांक32_t pipe,
			uपूर्णांक32_t queue, uपूर्णांक32_t vmid)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	mutex_lock(&adev->srbm_mutex);
	nv_grbm_select(adev, mec, pipe, queue, vmid);
पूर्ण

अटल व्योम unlock_srbm(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	nv_grbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);
पूर्ण

अटल व्योम acquire_queue(काष्ठा kgd_dev *kgd, uपूर्णांक32_t pipe_id,
				uपूर्णांक32_t queue_id)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	uपूर्णांक32_t mec = (pipe_id / adev->gfx.mec.num_pipe_per_mec) + 1;
	uपूर्णांक32_t pipe = (pipe_id % adev->gfx.mec.num_pipe_per_mec);

	lock_srbm(kgd, mec, pipe, queue_id, 0);
पूर्ण

अटल uपूर्णांक64_t get_queue_mask(काष्ठा amdgpu_device *adev,
			       uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id)
अणु
	अचिन्हित पूर्णांक bit = pipe_id * adev->gfx.mec.num_queue_per_pipe +
			queue_id;

	वापस 1ull << bit;
पूर्ण

अटल व्योम release_queue(काष्ठा kgd_dev *kgd)
अणु
	unlock_srbm(kgd);
पूर्ण

अटल व्योम program_sh_mem_settings_v10_3(काष्ठा kgd_dev *kgd, uपूर्णांक32_t vmid,
					uपूर्णांक32_t sh_mem_config,
					uपूर्णांक32_t sh_mem_ape1_base,
					uपूर्णांक32_t sh_mem_ape1_limit,
					uपूर्णांक32_t sh_mem_bases)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	lock_srbm(kgd, 0, 0, 0, vmid);

	WREG32(SOC15_REG_OFFSET(GC, 0, mmSH_MEM_CONFIG), sh_mem_config);
	WREG32(SOC15_REG_OFFSET(GC, 0, mmSH_MEM_BASES), sh_mem_bases);
	/* APE1 no दीर्घer exists on GFX9 */

	unlock_srbm(kgd);
पूर्ण

/* ATC is defeatured on Sienna_Cichlid */
अटल पूर्णांक set_pasid_vmid_mapping_v10_3(काष्ठा kgd_dev *kgd, अचिन्हित पूर्णांक pasid,
					अचिन्हित पूर्णांक vmid)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	uपूर्णांक32_t value = pasid << IH_VMID_0_LUT__PASID__SHIFT;

	/* Mapping vmid to pasid also क्रम IH block */
	pr_debug("mapping vmid %d -> pasid %d in IH block for GFX client\n",
			vmid, pasid);
	WREG32(SOC15_REG_OFFSET(OSSSYS, 0, mmIH_VMID_0_LUT) + vmid, value);

	वापस 0;
पूर्ण

अटल पूर्णांक init_पूर्णांकerrupts_v10_3(काष्ठा kgd_dev *kgd, uपूर्णांक32_t pipe_id)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t mec;
	uपूर्णांक32_t pipe;

	mec = (pipe_id / adev->gfx.mec.num_pipe_per_mec) + 1;
	pipe = (pipe_id % adev->gfx.mec.num_pipe_per_mec);

	lock_srbm(kgd, mec, pipe, 0, 0);

	WREG32(SOC15_REG_OFFSET(GC, 0, mmCPC_INT_CNTL),
		CP_INT_CNTL_RING0__TIME_STAMP_INT_ENABLE_MASK |
		CP_INT_CNTL_RING0__OPCODE_ERROR_INT_ENABLE_MASK);

	unlock_srbm(kgd);

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t get_sdma_rlc_reg_offset(काष्ठा amdgpu_device *adev,
				अचिन्हित पूर्णांक engine_id,
				अचिन्हित पूर्णांक queue_id)
अणु
	uपूर्णांक32_t sdma_engine_reg_base = 0;
	uपूर्णांक32_t sdma_rlc_reg_offset;

	चयन (engine_id) अणु
	शेष:
		dev_warn(adev->dev,
			 "Invalid sdma engine id (%d), using engine id 0\n",
			 engine_id);
		fallthrough;
	हाल 0:
		sdma_engine_reg_base = SOC15_REG_OFFSET(SDMA0, 0,
				mmSDMA0_RLC0_RB_CNTL) - mmSDMA0_RLC0_RB_CNTL;
		अवरोध;
	हाल 1:
		sdma_engine_reg_base = SOC15_REG_OFFSET(SDMA0, 0,
				mmSDMA1_RLC0_RB_CNTL) - mmSDMA0_RLC0_RB_CNTL;
		अवरोध;
	हाल 2:
		sdma_engine_reg_base = SOC15_REG_OFFSET(SDMA0, 0,
				mmSDMA2_RLC0_RB_CNTL) - mmSDMA0_RLC0_RB_CNTL;
		अवरोध;
	हाल 3:
		sdma_engine_reg_base = SOC15_REG_OFFSET(SDMA0, 0,
				mmSDMA3_RLC0_RB_CNTL) - mmSDMA0_RLC0_RB_CNTL;
		अवरोध;
	पूर्ण

	sdma_rlc_reg_offset = sdma_engine_reg_base
		+ queue_id * (mmSDMA0_RLC1_RB_CNTL - mmSDMA0_RLC0_RB_CNTL);

	pr_debug("RLC register offset for SDMA%d RLC%d: 0x%x\n", engine_id,
			queue_id, sdma_rlc_reg_offset);

	वापस sdma_rlc_reg_offset;
पूर्ण

अटल अंतरभूत काष्ठा v10_compute_mqd *get_mqd(व्योम *mqd)
अणु
	वापस (काष्ठा v10_compute_mqd *)mqd;
पूर्ण

अटल अंतरभूत काष्ठा v10_sdma_mqd *get_sdma_mqd(व्योम *mqd)
अणु
	वापस (काष्ठा v10_sdma_mqd *)mqd;
पूर्ण

अटल पूर्णांक hqd_load_v10_3(काष्ठा kgd_dev *kgd, व्योम *mqd, uपूर्णांक32_t pipe_id,
			uपूर्णांक32_t queue_id, uपूर्णांक32_t __user *wptr,
			uपूर्णांक32_t wptr_shअगरt, uपूर्णांक32_t wptr_mask,
			काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा v10_compute_mqd *m;
	uपूर्णांक32_t *mqd_hqd;
	uपूर्णांक32_t reg, hqd_base, data;

	m = get_mqd(mqd);

	pr_debug("Load hqd of pipe %d queue %d\n", pipe_id, queue_id);
	acquire_queue(kgd, pipe_id, queue_id);

	/* HIQ is set during driver init period with vmid set to 0*/
	अगर (m->cp_hqd_vmid == 0) अणु
		uपूर्णांक32_t value, mec, pipe;

		mec = (pipe_id / adev->gfx.mec.num_pipe_per_mec) + 1;
		pipe = (pipe_id % adev->gfx.mec.num_pipe_per_mec);

		pr_debug("kfd: set HIQ, mec:%d, pipe:%d, queue:%d.\n",
			mec, pipe, queue_id);
		value = RREG32(SOC15_REG_OFFSET(GC, 0, mmRLC_CP_SCHEDULERS));
		value = REG_SET_FIELD(value, RLC_CP_SCHEDULERS, scheduler1,
			((mec << 5) | (pipe << 3) | queue_id | 0x80));
		WREG32(SOC15_REG_OFFSET(GC, 0, mmRLC_CP_SCHEDULERS), value);
	पूर्ण

	/* HQD रेजिस्टरs extend from CP_MQD_BASE_ADDR to CP_HQD_EOP_WPTR_MEM. */
	mqd_hqd = &m->cp_mqd_base_addr_lo;
	hqd_base = SOC15_REG_OFFSET(GC, 0, mmCP_MQD_BASE_ADDR);

	क्रम (reg = hqd_base;
	     reg <= SOC15_REG_OFFSET(GC, 0, mmCP_HQD_PQ_WPTR_HI); reg++)
		WREG32(reg, mqd_hqd[reg - hqd_base]);


	/* Activate करोorbell logic beक्रमe triggering WPTR poll. */
	data = REG_SET_FIELD(m->cp_hqd_pq_करोorbell_control,
			     CP_HQD_PQ_DOORBELL_CONTROL, DOORBELL_EN, 1);
	WREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_PQ_DOORBELL_CONTROL), data);

	अगर (wptr) अणु
		/* Don't पढ़ो wptr with get_user because the user
		 * context may not be accessible (अगर this function
		 * runs in a work queue). Instead trigger a one-shot
		 * polling पढ़ो from memory in the CP. This assumes
		 * that wptr is GPU-accessible in the queue's VMID via
		 * ATC or SVM. WPTR==RPTR beक्रमe starting the poll so
		 * the CP starts fetching new commands from the right
		 * place.
		 *
		 * Guessing a 64-bit WPTR from a 32-bit RPTR is a bit
		 * tricky. Assume that the queue didn't overflow. The
		 * number of valid bits in the 32-bit RPTR depends on
		 * the queue size. The reमुख्यing bits are taken from
		 * the saved 64-bit WPTR. If the WPTR wrapped, add the
		 * queue size.
		 */
		uपूर्णांक32_t queue_size =
			2 << REG_GET_FIELD(m->cp_hqd_pq_control,
					   CP_HQD_PQ_CONTROL, QUEUE_SIZE);
		uपूर्णांक64_t guessed_wptr = m->cp_hqd_pq_rptr & (queue_size - 1);

		अगर ((m->cp_hqd_pq_wptr_lo & (queue_size - 1)) < guessed_wptr)
			guessed_wptr += queue_size;
		guessed_wptr += m->cp_hqd_pq_wptr_lo & ~(queue_size - 1);
		guessed_wptr += (uपूर्णांक64_t)m->cp_hqd_pq_wptr_hi << 32;

		WREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_PQ_WPTR_LO),
		       lower_32_bits(guessed_wptr));
		WREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_PQ_WPTR_HI),
		       upper_32_bits(guessed_wptr));
		WREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_PQ_WPTR_POLL_ADDR),
		       lower_32_bits((uपूर्णांक64_t)wptr));
		WREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_PQ_WPTR_POLL_ADDR_HI),
		       upper_32_bits((uपूर्णांक64_t)wptr));
		pr_debug("%s setting CP_PQ_WPTR_POLL_CNTL1 to %x\n", __func__,
			 (uपूर्णांक32_t)get_queue_mask(adev, pipe_id, queue_id));
		WREG32(SOC15_REG_OFFSET(GC, 0, mmCP_PQ_WPTR_POLL_CNTL1),
		       (uपूर्णांक32_t)get_queue_mask(adev, pipe_id, queue_id));
	पूर्ण

	/* Start the EOP fetcher */
	WREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_EOP_RPTR),
	       REG_SET_FIELD(m->cp_hqd_eop_rptr,
			     CP_HQD_EOP_RPTR, INIT_FETCHER, 1));

	data = REG_SET_FIELD(m->cp_hqd_active, CP_HQD_ACTIVE, ACTIVE, 1);
	WREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_ACTIVE), data);

	release_queue(kgd);

	वापस 0;
पूर्ण

अटल पूर्णांक hiq_mqd_load_v10_3(काष्ठा kgd_dev *kgd, व्योम *mqd,
			    uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id,
			    uपूर्णांक32_t करोorbell_off)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा amdgpu_ring *kiq_ring = &adev->gfx.kiq.ring;
	काष्ठा v10_compute_mqd *m;
	uपूर्णांक32_t mec, pipe;
	पूर्णांक r;

	m = get_mqd(mqd);

	acquire_queue(kgd, pipe_id, queue_id);

	mec = (pipe_id / adev->gfx.mec.num_pipe_per_mec) + 1;
	pipe = (pipe_id % adev->gfx.mec.num_pipe_per_mec);

	pr_debug("kfd: set HIQ, mec:%d, pipe:%d, queue:%d.\n",
		 mec, pipe, queue_id);

	spin_lock(&adev->gfx.kiq.ring_lock);
	r = amdgpu_ring_alloc(kiq_ring, 7);
	अगर (r) अणु
		pr_err("Failed to alloc KIQ (%d).\n", r);
		जाओ out_unlock;
	पूर्ण

	amdgpu_ring_ग_लिखो(kiq_ring, PACKET3(PACKET3_MAP_QUEUES, 5));
	amdgpu_ring_ग_लिखो(kiq_ring,
			  PACKET3_MAP_QUEUES_QUEUE_SEL(0) | /* Queue_Sel */
			  PACKET3_MAP_QUEUES_VMID(m->cp_hqd_vmid) | /* VMID */
			  PACKET3_MAP_QUEUES_QUEUE(queue_id) |
			  PACKET3_MAP_QUEUES_PIPE(pipe) |
			  PACKET3_MAP_QUEUES_ME((mec - 1)) |
			  PACKET3_MAP_QUEUES_QUEUE_TYPE(0) | /*queue_type: normal compute queue */
			  PACKET3_MAP_QUEUES_ALLOC_FORMAT(0) | /* alloc क्रमmat: all_on_one_pipe */
			  PACKET3_MAP_QUEUES_ENGINE_SEL(1) | /* engine_sel: hiq */
			  PACKET3_MAP_QUEUES_NUM_QUEUES(1)); /* num_queues: must be 1 */
	amdgpu_ring_ग_लिखो(kiq_ring,
			  PACKET3_MAP_QUEUES_DOORBELL_OFFSET(करोorbell_off));
	amdgpu_ring_ग_लिखो(kiq_ring, m->cp_mqd_base_addr_lo);
	amdgpu_ring_ग_लिखो(kiq_ring, m->cp_mqd_base_addr_hi);
	amdgpu_ring_ग_लिखो(kiq_ring, m->cp_hqd_pq_wptr_poll_addr_lo);
	amdgpu_ring_ग_लिखो(kiq_ring, m->cp_hqd_pq_wptr_poll_addr_hi);
	amdgpu_ring_commit(kiq_ring);

out_unlock:
	spin_unlock(&adev->gfx.kiq.ring_lock);
	release_queue(kgd);

	वापस r;
पूर्ण

अटल पूर्णांक hqd_dump_v10_3(काष्ठा kgd_dev *kgd,
			uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id,
			uपूर्णांक32_t (**dump)[2], uपूर्णांक32_t *n_regs)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t i = 0, reg;
#घोषणा HQD_N_REGS 56
#घोषणा DUMP_REG(addr) करो अणु				\
		अगर (WARN_ON_ONCE(i >= HQD_N_REGS))	\
			अवरोध;				\
		(*dump)[i][0] = (addr) << 2;		\
		(*dump)[i++][1] = RREG32(addr);		\
	पूर्ण जबतक (0)

	*dump = kदो_स्मृति(HQD_N_REGS*2*माप(uपूर्णांक32_t), GFP_KERNEL);
	अगर (*dump == शून्य)
		वापस -ENOMEM;

	acquire_queue(kgd, pipe_id, queue_id);

	क्रम (reg = SOC15_REG_OFFSET(GC, 0, mmCP_MQD_BASE_ADDR);
	     reg <= SOC15_REG_OFFSET(GC, 0, mmCP_HQD_PQ_WPTR_HI); reg++)
		DUMP_REG(reg);

	release_queue(kgd);

	WARN_ON_ONCE(i != HQD_N_REGS);
	*n_regs = i;

	वापस 0;
पूर्ण

अटल पूर्णांक hqd_sdma_load_v10_3(काष्ठा kgd_dev *kgd, व्योम *mqd,
			     uपूर्णांक32_t __user *wptr, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा v10_sdma_mqd *m;
	uपूर्णांक32_t sdma_rlc_reg_offset;
	अचिन्हित दीर्घ end_jअगरfies;
	uपूर्णांक32_t data;
	uपूर्णांक64_t data64;
	uपूर्णांक64_t __user *wptr64 = (uपूर्णांक64_t __user *)wptr;

	m = get_sdma_mqd(mqd);
	sdma_rlc_reg_offset = get_sdma_rlc_reg_offset(adev, m->sdma_engine_id,
					    m->sdma_queue_id);

	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_CNTL,
		m->sdmax_rlcx_rb_cntl & (~SDMA0_RLC0_RB_CNTL__RB_ENABLE_MASK));

	end_jअगरfies = msecs_to_jअगरfies(2000) + jअगरfies;
	जबतक (true) अणु
		data = RREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_CONTEXT_STATUS);
		अगर (data & SDMA0_RLC0_CONTEXT_STATUS__IDLE_MASK)
			अवरोध;
		अगर (समय_after(jअगरfies, end_jअगरfies)) अणु
			pr_err("SDMA RLC not idle in %s\n", __func__);
			वापस -ETIME;
		पूर्ण
		usleep_range(500, 1000);
	पूर्ण

	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_DOORBELL_OFFSET,
	       m->sdmax_rlcx_करोorbell_offset);

	data = REG_SET_FIELD(m->sdmax_rlcx_करोorbell, SDMA0_RLC0_DOORBELL,
			     ENABLE, 1);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_DOORBELL, data);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_RPTR,
				m->sdmax_rlcx_rb_rptr);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_RPTR_HI,
				m->sdmax_rlcx_rb_rptr_hi);

	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_MINOR_PTR_UPDATE, 1);
	अगर (पढ़ो_user_wptr(mm, wptr64, data64)) अणु
		WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_WPTR,
		       lower_32_bits(data64));
		WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_WPTR_HI,
		       upper_32_bits(data64));
	पूर्ण अन्यथा अणु
		WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_WPTR,
		       m->sdmax_rlcx_rb_rptr);
		WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_WPTR_HI,
		       m->sdmax_rlcx_rb_rptr_hi);
	पूर्ण
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_MINOR_PTR_UPDATE, 0);

	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_BASE, m->sdmax_rlcx_rb_base);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_BASE_HI,
			m->sdmax_rlcx_rb_base_hi);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_RPTR_ADDR_LO,
			m->sdmax_rlcx_rb_rptr_addr_lo);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_RPTR_ADDR_HI,
			m->sdmax_rlcx_rb_rptr_addr_hi);

	data = REG_SET_FIELD(m->sdmax_rlcx_rb_cntl, SDMA0_RLC0_RB_CNTL,
			     RB_ENABLE, 1);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_CNTL, data);

	वापस 0;
पूर्ण

अटल पूर्णांक hqd_sdma_dump_v10_3(काष्ठा kgd_dev *kgd,
			     uपूर्णांक32_t engine_id, uपूर्णांक32_t queue_id,
			     uपूर्णांक32_t (**dump)[2], uपूर्णांक32_t *n_regs)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t sdma_rlc_reg_offset = get_sdma_rlc_reg_offset(adev,
			engine_id, queue_id);
	uपूर्णांक32_t i = 0, reg;
#अघोषित HQD_N_REGS
#घोषणा HQD_N_REGS (19+6+7+12)

	*dump = kदो_स्मृति(HQD_N_REGS*2*माप(uपूर्णांक32_t), GFP_KERNEL);
	अगर (*dump == शून्य)
		वापस -ENOMEM;

	क्रम (reg = mmSDMA0_RLC0_RB_CNTL; reg <= mmSDMA0_RLC0_DOORBELL; reg++)
		DUMP_REG(sdma_rlc_reg_offset + reg);
	क्रम (reg = mmSDMA0_RLC0_STATUS; reg <= mmSDMA0_RLC0_CSA_ADDR_HI; reg++)
		DUMP_REG(sdma_rlc_reg_offset + reg);
	क्रम (reg = mmSDMA0_RLC0_IB_SUB_REMAIN;
	     reg <= mmSDMA0_RLC0_MINOR_PTR_UPDATE; reg++)
		DUMP_REG(sdma_rlc_reg_offset + reg);
	क्रम (reg = mmSDMA0_RLC0_MIDCMD_DATA0;
	     reg <= mmSDMA0_RLC0_MIDCMD_CNTL; reg++)
		DUMP_REG(sdma_rlc_reg_offset + reg);

	WARN_ON_ONCE(i != HQD_N_REGS);
	*n_regs = i;

	वापस 0;
पूर्ण

अटल bool hqd_is_occupied_v10_3(काष्ठा kgd_dev *kgd, uपूर्णांक64_t queue_address,
				uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t act;
	bool retval = false;
	uपूर्णांक32_t low, high;

	acquire_queue(kgd, pipe_id, queue_id);
	act = RREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_ACTIVE));
	अगर (act) अणु
		low = lower_32_bits(queue_address >> 8);
		high = upper_32_bits(queue_address >> 8);

		अगर (low == RREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_PQ_BASE)) &&
		   high == RREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_PQ_BASE_HI)))
			retval = true;
	पूर्ण
	release_queue(kgd);
	वापस retval;
पूर्ण

अटल bool hqd_sdma_is_occupied_v10_3(काष्ठा kgd_dev *kgd, व्योम *mqd)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा v10_sdma_mqd *m;
	uपूर्णांक32_t sdma_rlc_reg_offset;
	uपूर्णांक32_t sdma_rlc_rb_cntl;

	m = get_sdma_mqd(mqd);
	sdma_rlc_reg_offset = get_sdma_rlc_reg_offset(adev, m->sdma_engine_id,
					    m->sdma_queue_id);

	sdma_rlc_rb_cntl = RREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_CNTL);

	अगर (sdma_rlc_rb_cntl & SDMA0_RLC0_RB_CNTL__RB_ENABLE_MASK)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक hqd_destroy_v10_3(काष्ठा kgd_dev *kgd, व्योम *mqd,
				क्रमागत kfd_preempt_type reset_type,
				अचिन्हित पूर्णांक uसमयout, uपूर्णांक32_t pipe_id,
				uपूर्णांक32_t queue_id)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	क्रमागत hqd_dequeue_request_type type;
	अचिन्हित दीर्घ end_jअगरfies;
	uपूर्णांक32_t temp;
	काष्ठा v10_compute_mqd *m = get_mqd(mqd);

	acquire_queue(kgd, pipe_id, queue_id);

	अगर (m->cp_hqd_vmid == 0)
		WREG32_FIELD15(GC, 0, RLC_CP_SCHEDULERS, scheduler1, 0);

	चयन (reset_type) अणु
	हाल KFD_PREEMPT_TYPE_WAVEFRONT_DRAIN:
		type = DRAIN_PIPE;
		अवरोध;
	हाल KFD_PREEMPT_TYPE_WAVEFRONT_RESET:
		type = RESET_WAVES;
		अवरोध;
	शेष:
		type = DRAIN_PIPE;
		अवरोध;
	पूर्ण

	WREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_DEQUEUE_REQUEST), type);

	end_jअगरfies = (uसमयout * HZ / 1000) + jअगरfies;
	जबतक (true) अणु
		temp = RREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_ACTIVE));
		अगर (!(temp & CP_HQD_ACTIVE__ACTIVE_MASK))
			अवरोध;
		अगर (समय_after(jअगरfies, end_jअगरfies)) अणु
			pr_err("cp queue pipe %d queue %d preemption failed\n",
					pipe_id, queue_id);
			release_queue(kgd);
			वापस -ETIME;
		पूर्ण
		usleep_range(500, 1000);
	पूर्ण

	release_queue(kgd);
	वापस 0;
पूर्ण

अटल पूर्णांक hqd_sdma_destroy_v10_3(काष्ठा kgd_dev *kgd, व्योम *mqd,
				अचिन्हित पूर्णांक uसमयout)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा v10_sdma_mqd *m;
	uपूर्णांक32_t sdma_rlc_reg_offset;
	uपूर्णांक32_t temp;
	अचिन्हित दीर्घ end_jअगरfies = (uसमयout * HZ / 1000) + jअगरfies;

	m = get_sdma_mqd(mqd);
	sdma_rlc_reg_offset = get_sdma_rlc_reg_offset(adev, m->sdma_engine_id,
					    m->sdma_queue_id);

	temp = RREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_CNTL);
	temp = temp & ~SDMA0_RLC0_RB_CNTL__RB_ENABLE_MASK;
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_CNTL, temp);

	जबतक (true) अणु
		temp = RREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_CONTEXT_STATUS);
		अगर (temp & SDMA0_RLC0_CONTEXT_STATUS__IDLE_MASK)
			अवरोध;
		अगर (समय_after(jअगरfies, end_jअगरfies)) अणु
			pr_err("SDMA RLC not idle in %s\n", __func__);
			वापस -ETIME;
		पूर्ण
		usleep_range(500, 1000);
	पूर्ण

	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_DOORBELL, 0);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_CNTL,
		RREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_CNTL) |
		SDMA0_RLC0_RB_CNTL__RB_ENABLE_MASK);

	m->sdmax_rlcx_rb_rptr = RREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_RPTR);
	m->sdmax_rlcx_rb_rptr_hi =
		RREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_RPTR_HI);

	वापस 0;
पूर्ण


अटल पूर्णांक address_watch_disable_v10_3(काष्ठा kgd_dev *kgd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक address_watch_execute_v10_3(काष्ठा kgd_dev *kgd,
					अचिन्हित पूर्णांक watch_poपूर्णांक_id,
					uपूर्णांक32_t cntl_val,
					uपूर्णांक32_t addr_hi,
					uपूर्णांक32_t addr_lo)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक wave_control_execute_v10_3(काष्ठा kgd_dev *kgd,
					uपूर्णांक32_t gfx_index_val,
					uपूर्णांक32_t sq_cmd)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t data = 0;

	mutex_lock(&adev->grbm_idx_mutex);

	WREG32(SOC15_REG_OFFSET(GC, 0, mmGRBM_GFX_INDEX), gfx_index_val);
	WREG32(SOC15_REG_OFFSET(GC, 0, mmSQ_CMD), sq_cmd);

	data = REG_SET_FIELD(data, GRBM_GFX_INDEX,
		INSTANCE_BROADCAST_WRITES, 1);
	data = REG_SET_FIELD(data, GRBM_GFX_INDEX,
		SA_BROADCAST_WRITES, 1);
	data = REG_SET_FIELD(data, GRBM_GFX_INDEX,
		SE_BROADCAST_WRITES, 1);

	WREG32(SOC15_REG_OFFSET(GC, 0, mmGRBM_GFX_INDEX), data);
	mutex_unlock(&adev->grbm_idx_mutex);

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t address_watch_get_offset_v10_3(काष्ठा kgd_dev *kgd,
					अचिन्हित पूर्णांक watch_poपूर्णांक_id,
					अचिन्हित पूर्णांक reg_offset)
अणु
	वापस 0;
पूर्ण

अटल व्योम set_vm_context_page_table_base_v10_3(काष्ठा kgd_dev *kgd, uपूर्णांक32_t vmid,
		uपूर्णांक64_t page_table_base)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	/* SDMA is on gfxhub as well क्रम Navi1* series */
	adev->gfxhub.funcs->setup_vm_pt_regs(adev, vmid, page_table_base);
पूर्ण

#अगर 0
uपूर्णांक32_t enable_debug_trap_v10_3(काष्ठा kgd_dev *kgd,
				uपूर्णांक32_t trap_debug_wave_launch_mode,
				uपूर्णांक32_t vmid)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t data = 0;
	uपूर्णांक32_t orig_wave_cntl_value;
	uपूर्णांक32_t orig_stall_vmid;

	mutex_lock(&adev->grbm_idx_mutex);

	orig_wave_cntl_value = RREG32(SOC15_REG_OFFSET(GC,
				0,
				mmSPI_GDBG_WAVE_CNTL));
	orig_stall_vmid = REG_GET_FIELD(orig_wave_cntl_value,
			SPI_GDBG_WAVE_CNTL,
			STALL_VMID);

	data = REG_SET_FIELD(data, SPI_GDBG_WAVE_CNTL, STALL_RA, 1);
	WREG32(SOC15_REG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTL), data);

	data = 0;
	WREG32(SOC15_REG_OFFSET(GC, 0, mmSPI_GDBG_TRAP_MASK), data);

	WREG32(SOC15_REG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTL), orig_stall_vmid);

	mutex_unlock(&adev->grbm_idx_mutex);

	वापस 0;
पूर्ण

uपूर्णांक32_t disable_debug_trap_v10_3(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	mutex_lock(&adev->grbm_idx_mutex);

	WREG32(SOC15_REG_OFFSET(GC, 0, mmSPI_GDBG_TRAP_MASK), 0);

	mutex_unlock(&adev->grbm_idx_mutex);

	वापस 0;
पूर्ण

uपूर्णांक32_t set_wave_launch_trap_override_v10_3(काष्ठा kgd_dev *kgd,
						uपूर्णांक32_t trap_override,
						uपूर्णांक32_t trap_mask)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t data = 0;

	mutex_lock(&adev->grbm_idx_mutex);

	data = RREG32(SOC15_REG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTL));
	data = REG_SET_FIELD(data, SPI_GDBG_WAVE_CNTL, STALL_RA, 1);
	WREG32(SOC15_REG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTL), data);

	data = 0;
	data = REG_SET_FIELD(data, SPI_GDBG_TRAP_MASK,
			EXCP_EN, trap_mask);
	data = REG_SET_FIELD(data, SPI_GDBG_TRAP_MASK,
			REPLACE, trap_override);
	WREG32(SOC15_REG_OFFSET(GC, 0, mmSPI_GDBG_TRAP_MASK), data);

	data = RREG32(SOC15_REG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTL));
	data = REG_SET_FIELD(data, SPI_GDBG_WAVE_CNTL, STALL_RA, 0);
	WREG32(SOC15_REG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTL), data);

	mutex_unlock(&adev->grbm_idx_mutex);

	वापस 0;
पूर्ण

uपूर्णांक32_t set_wave_launch_mode_v10_3(काष्ठा kgd_dev *kgd,
					uपूर्णांक8_t wave_launch_mode,
					uपूर्णांक32_t vmid)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t data = 0;
	bool is_stall_mode;
	bool is_mode_set;

	is_stall_mode = (wave_launch_mode == 4);
	is_mode_set = (wave_launch_mode != 0 && wave_launch_mode != 4);

	mutex_lock(&adev->grbm_idx_mutex);

	data = REG_SET_FIELD(data, SPI_GDBG_WAVE_CNTL2,
			VMID_MASK, is_mode_set ? 1 << vmid : 0);
	data = REG_SET_FIELD(data, SPI_GDBG_WAVE_CNTL2,
			MODE, is_mode_set ? wave_launch_mode : 0);
	WREG32(SOC15_REG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTL2), data);

	data = RREG32(SOC15_REG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTL));
	data = REG_SET_FIELD(data, SPI_GDBG_WAVE_CNTL,
			STALL_VMID, is_stall_mode ? 1 << vmid : 0);
	data = REG_SET_FIELD(data, SPI_GDBG_WAVE_CNTL,
			STALL_RA, is_stall_mode ? 1 : 0);
	WREG32(SOC15_REG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTL), data);

	mutex_unlock(&adev->grbm_idx_mutex);

	वापस 0;
पूर्ण

/* kgd_get_iq_रुको_बार: Returns the mmCP_IQ_WAIT_TIME1/2 values
 * The values पढ़ो are:
 *	ib_offload_रुको_समय     -- Wait Count क्रम Indirect Buffer Offloads.
 *	atomic_offload_रुको_समय -- Wait Count क्रम L2 and GDS Atomics Offloads.
 *	wrm_offload_रुको_समय    -- Wait Count क्रम WAIT_REG_MEM Offloads.
 *	gws_रुको_समय            -- Wait Count क्रम Global Wave Syncs.
 *	que_sleep_रुको_समय      -- Wait Count क्रम Dequeue Retry.
 *	sch_wave_रुको_समय       -- Wait Count क्रम Scheduling Wave Message.
 *	sem_rearm_रुको_समय      -- Wait Count क्रम Semaphore re-arm.
 *	deq_retry_रुको_समय      -- Wait Count क्रम Global Wave Syncs.
 */
व्योम get_iq_रुको_बार_v10_3(काष्ठा kgd_dev *kgd,
					uपूर्णांक32_t *रुको_बार)

अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	*रुको_बार = RREG32(SOC15_REG_OFFSET(GC, 0, mmCP_IQ_WAIT_TIME2));
पूर्ण

व्योम build_grace_period_packet_info_v10_3(काष्ठा kgd_dev *kgd,
						uपूर्णांक32_t रुको_बार,
						uपूर्णांक32_t grace_period,
						uपूर्णांक32_t *reg_offset,
						uपूर्णांक32_t *reg_data)
अणु
	*reg_data = रुको_बार;

	*reg_data = REG_SET_FIELD(*reg_data,
			CP_IQ_WAIT_TIME2,
			SCH_WAVE,
			grace_period);

	*reg_offset = mmCP_IQ_WAIT_TIME2;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा kfd2kgd_calls gfx_v10_3_kfd2kgd = अणु
	.program_sh_mem_settings = program_sh_mem_settings_v10_3,
	.set_pasid_vmid_mapping = set_pasid_vmid_mapping_v10_3,
	.init_पूर्णांकerrupts = init_पूर्णांकerrupts_v10_3,
	.hqd_load = hqd_load_v10_3,
	.hiq_mqd_load = hiq_mqd_load_v10_3,
	.hqd_sdma_load = hqd_sdma_load_v10_3,
	.hqd_dump = hqd_dump_v10_3,
	.hqd_sdma_dump = hqd_sdma_dump_v10_3,
	.hqd_is_occupied = hqd_is_occupied_v10_3,
	.hqd_sdma_is_occupied = hqd_sdma_is_occupied_v10_3,
	.hqd_destroy = hqd_destroy_v10_3,
	.hqd_sdma_destroy = hqd_sdma_destroy_v10_3,
	.address_watch_disable = address_watch_disable_v10_3,
	.address_watch_execute = address_watch_execute_v10_3,
	.wave_control_execute = wave_control_execute_v10_3,
	.address_watch_get_offset = address_watch_get_offset_v10_3,
	.get_atc_vmid_pasid_mapping_info = शून्य,
	.set_vm_context_page_table_base = set_vm_context_page_table_base_v10_3,
#अगर 0
	.enable_debug_trap = enable_debug_trap_v10_3,
	.disable_debug_trap = disable_debug_trap_v10_3,
	.set_wave_launch_trap_override = set_wave_launch_trap_override_v10_3,
	.set_wave_launch_mode = set_wave_launch_mode_v10_3,
	.get_iq_रुको_बार = get_iq_रुको_बार_v10_3,
	.build_grace_period_packet_info = build_grace_period_packet_info_v10_3,
#पूर्ण_अगर
पूर्ण;
