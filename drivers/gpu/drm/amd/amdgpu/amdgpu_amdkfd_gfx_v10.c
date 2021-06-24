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
#समावेश "amdgpu.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "gc/gc_10_1_0_offset.h"
#समावेश "gc/gc_10_1_0_sh_mask.h"
#समावेश "athub/athub_2_0_0_offset.h"
#समावेश "athub/athub_2_0_0_sh_mask.h"
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

अटल व्योम kgd_program_sh_mem_settings(काष्ठा kgd_dev *kgd, uपूर्णांक32_t vmid,
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

अटल पूर्णांक kgd_set_pasid_vmid_mapping(काष्ठा kgd_dev *kgd, u32 pasid,
					अचिन्हित पूर्णांक vmid)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	/*
	 * We have to assume that there is no outstanding mapping.
	 * The ATC_VMID_PASID_MAPPING_UPDATE_STATUS bit could be 0 because
	 * a mapping is in progress or because a mapping finished
	 * and the SW cleared it.
	 * So the protocol is to always रुको & clear.
	 */
	uपूर्णांक32_t pasid_mapping = (pasid == 0) ? 0 : (uपूर्णांक32_t)pasid |
			ATC_VMID0_PASID_MAPPING__VALID_MASK;

	pr_debug("pasid 0x%x vmid %d, reg value %x\n", pasid, vmid, pasid_mapping);

	pr_debug("ATHUB, reg %x\n", SOC15_REG_OFFSET(ATHUB, 0, mmATC_VMID0_PASID_MAPPING) + vmid);
	WREG32(SOC15_REG_OFFSET(ATHUB, 0, mmATC_VMID0_PASID_MAPPING) + vmid,
	       pasid_mapping);

#अगर 0
	/* TODO: uncomment this code when the hardware support is पढ़ोy. */
	जबतक (!(RREG32(SOC15_REG_OFFSET(
				ATHUB, 0,
				mmATC_VMID_PASID_MAPPING_UPDATE_STATUS)) &
		 (1U << vmid)))
		cpu_relax();

	pr_debug("ATHUB mapping update finished\n");
	WREG32(SOC15_REG_OFFSET(ATHUB, 0,
				mmATC_VMID_PASID_MAPPING_UPDATE_STATUS),
	       1U << vmid);
#पूर्ण_अगर

	/* Mapping vmid to pasid also क्रम IH block */
	pr_debug("update mapping for IH block and mmhub");
	WREG32(SOC15_REG_OFFSET(OSSSYS, 0, mmIH_VMID_0_LUT) + vmid,
	       pasid_mapping);

	वापस 0;
पूर्ण

/* TODO - RING0 क्रमm of field is obsolete, seems to date back to SI
 * but still works
 */

अटल पूर्णांक kgd_init_पूर्णांकerrupts(काष्ठा kgd_dev *kgd, uपूर्णांक32_t pipe_id)
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
	uपूर्णांक32_t sdma_engine_reg_base[2] = अणु
		SOC15_REG_OFFSET(SDMA0, 0,
				 mmSDMA0_RLC0_RB_CNTL) - mmSDMA0_RLC0_RB_CNTL,
		/* On gfx10, mmSDMA1_xxx रेजिस्टरs are defined NOT based
		 * on SDMA1 base address (dw 0x1860) but based on SDMA0
		 * base address (dw 0x1260). Thereक्रमe use mmSDMA0_RLC0_RB_CNTL
		 * instead of mmSDMA1_RLC0_RB_CNTL क्रम the base address calc
		 * below
		 */
		SOC15_REG_OFFSET(SDMA1, 0,
				 mmSDMA1_RLC0_RB_CNTL) - mmSDMA0_RLC0_RB_CNTL
	पूर्ण;

	uपूर्णांक32_t retval = sdma_engine_reg_base[engine_id]
		+ queue_id * (mmSDMA0_RLC1_RB_CNTL - mmSDMA0_RLC0_RB_CNTL);

	pr_debug("RLC register offset for SDMA%d RLC%d: 0x%x\n", engine_id,
			queue_id, retval);

	वापस retval;
पूर्ण

#अगर 0
अटल uपूर्णांक32_t get_watch_base_addr(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t retval = SOC15_REG_OFFSET(GC, 0, mmTCP_WATCH0_ADDR_H) -
			mmTCP_WATCH0_ADDR_H;

	pr_debug("kfd: reg watch base address: 0x%x\n", retval);

	वापस retval;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा v10_compute_mqd *get_mqd(व्योम *mqd)
अणु
	वापस (काष्ठा v10_compute_mqd *)mqd;
पूर्ण

अटल अंतरभूत काष्ठा v10_sdma_mqd *get_sdma_mqd(व्योम *mqd)
अणु
	वापस (काष्ठा v10_sdma_mqd *)mqd;
पूर्ण

अटल पूर्णांक kgd_hqd_load(काष्ठा kgd_dev *kgd, व्योम *mqd, uपूर्णांक32_t pipe_id,
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

अटल पूर्णांक kgd_hiq_mqd_load(काष्ठा kgd_dev *kgd, व्योम *mqd,
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

अटल पूर्णांक kgd_hqd_dump(काष्ठा kgd_dev *kgd,
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

अटल पूर्णांक kgd_hqd_sdma_load(काष्ठा kgd_dev *kgd, व्योम *mqd,
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

अटल पूर्णांक kgd_hqd_sdma_dump(काष्ठा kgd_dev *kgd,
			     uपूर्णांक32_t engine_id, uपूर्णांक32_t queue_id,
			     uपूर्णांक32_t (**dump)[2], uपूर्णांक32_t *n_regs)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t sdma_rlc_reg_offset = get_sdma_rlc_reg_offset(adev,
			engine_id, queue_id);
	uपूर्णांक32_t i = 0, reg;
#अघोषित HQD_N_REGS
#घोषणा HQD_N_REGS (19+6+7+10)

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

अटल bool kgd_hqd_is_occupied(काष्ठा kgd_dev *kgd, uपूर्णांक64_t queue_address,
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

अटल bool kgd_hqd_sdma_is_occupied(काष्ठा kgd_dev *kgd, व्योम *mqd)
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

अटल पूर्णांक kgd_hqd_destroy(काष्ठा kgd_dev *kgd, व्योम *mqd,
				क्रमागत kfd_preempt_type reset_type,
				अचिन्हित पूर्णांक uसमयout, uपूर्णांक32_t pipe_id,
				uपूर्णांक32_t queue_id)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	क्रमागत hqd_dequeue_request_type type;
	अचिन्हित दीर्घ end_jअगरfies;
	uपूर्णांक32_t temp;
	काष्ठा v10_compute_mqd *m = get_mqd(mqd);

	अगर (amdgpu_in_reset(adev))
		वापस -EIO;

#अगर 0
	अचिन्हित दीर्घ flags;
	पूर्णांक retry;
#पूर्ण_अगर

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

#अगर 0 /* Is this still needed? */
	/* Workaround: If IQ समयr is active and the रुको समय is बंद to or
	 * equal to 0, dequeueing is not safe. Wait until either the रुको समय
	 * is larger or समयr is cleared. Also, ensure that IQ_REQ_PEND is
	 * cleared beक्रमe continuing. Also, ensure रुको बार are set to at
	 * least 0x3.
	 */
	local_irq_save(flags);
	preempt_disable();
	retry = 5000; /* रुको क्रम 500 usecs at maximum */
	जबतक (true) अणु
		temp = RREG32(mmCP_HQD_IQ_TIMER);
		अगर (REG_GET_FIELD(temp, CP_HQD_IQ_TIMER, PROCESSING_IQ)) अणु
			pr_debug("HW is processing IQ\n");
			जाओ loop;
		पूर्ण
		अगर (REG_GET_FIELD(temp, CP_HQD_IQ_TIMER, ACTIVE)) अणु
			अगर (REG_GET_FIELD(temp, CP_HQD_IQ_TIMER, RETRY_TYPE)
					== 3) /* SEM-rearm is safe */
				अवरोध;
			/* Wait समय 3 is safe क्रम CP, but our MMIO पढ़ो/ग_लिखो
			 * समय is बंद to 1 microsecond, so check क्रम 10 to
			 * leave more buffer room
			 */
			अगर (REG_GET_FIELD(temp, CP_HQD_IQ_TIMER, WAIT_TIME)
					>= 10)
				अवरोध;
			pr_debug("IQ timer is active\n");
		पूर्ण अन्यथा
			अवरोध;
loop:
		अगर (!retry) अणु
			pr_err("CP HQD IQ timer status time out\n");
			अवरोध;
		पूर्ण
		ndelay(100);
		--retry;
	पूर्ण
	retry = 1000;
	जबतक (true) अणु
		temp = RREG32(mmCP_HQD_DEQUEUE_REQUEST);
		अगर (!(temp & CP_HQD_DEQUEUE_REQUEST__IQ_REQ_PEND_MASK))
			अवरोध;
		pr_debug("Dequeue request is pending\n");

		अगर (!retry) अणु
			pr_err("CP HQD dequeue request time out\n");
			अवरोध;
		पूर्ण
		ndelay(100);
		--retry;
	पूर्ण
	local_irq_restore(flags);
	preempt_enable();
#पूर्ण_अगर

	WREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_DEQUEUE_REQUEST), type);

	end_jअगरfies = (uसमयout * HZ / 1000) + jअगरfies;
	जबतक (true) अणु
		temp = RREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_ACTIVE));
		अगर (!(temp & CP_HQD_ACTIVE__ACTIVE_MASK))
			अवरोध;
		अगर (समय_after(jअगरfies, end_jअगरfies)) अणु
			pr_err("cp queue preemption time out.\n");
			release_queue(kgd);
			वापस -ETIME;
		पूर्ण
		usleep_range(500, 1000);
	पूर्ण

	release_queue(kgd);
	वापस 0;
पूर्ण

अटल पूर्णांक kgd_hqd_sdma_destroy(काष्ठा kgd_dev *kgd, व्योम *mqd,
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

अटल bool get_atc_vmid_pasid_mapping_info(काष्ठा kgd_dev *kgd,
					uपूर्णांक8_t vmid, uपूर्णांक16_t *p_pasid)
अणु
	uपूर्णांक32_t value;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *) kgd;

	value = RREG32(SOC15_REG_OFFSET(ATHUB, 0, mmATC_VMID0_PASID_MAPPING)
		     + vmid);
	*p_pasid = value & ATC_VMID0_PASID_MAPPING__PASID_MASK;

	वापस !!(value & ATC_VMID0_PASID_MAPPING__VALID_MASK);
पूर्ण

अटल पूर्णांक kgd_address_watch_disable(काष्ठा kgd_dev *kgd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक kgd_address_watch_execute(काष्ठा kgd_dev *kgd,
					अचिन्हित पूर्णांक watch_poपूर्णांक_id,
					uपूर्णांक32_t cntl_val,
					uपूर्णांक32_t addr_hi,
					uपूर्णांक32_t addr_lo)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक kgd_wave_control_execute(काष्ठा kgd_dev *kgd,
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

अटल uपूर्णांक32_t kgd_address_watch_get_offset(काष्ठा kgd_dev *kgd,
					अचिन्हित पूर्णांक watch_poपूर्णांक_id,
					अचिन्हित पूर्णांक reg_offset)
अणु
	वापस 0;
पूर्ण

अटल व्योम set_vm_context_page_table_base(काष्ठा kgd_dev *kgd, uपूर्णांक32_t vmid,
		uपूर्णांक64_t page_table_base)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	अगर (!amdgpu_amdkfd_is_kfd_vmid(adev, vmid)) अणु
		pr_err("trying to set page table base for wrong VMID %u\n",
		       vmid);
		वापस;
	पूर्ण

	/* SDMA is on gfxhub as well क्रम Navi1* series */
	adev->gfxhub.funcs->setup_vm_pt_regs(adev, vmid, page_table_base);
पूर्ण

स्थिर काष्ठा kfd2kgd_calls gfx_v10_kfd2kgd = अणु
	.program_sh_mem_settings = kgd_program_sh_mem_settings,
	.set_pasid_vmid_mapping = kgd_set_pasid_vmid_mapping,
	.init_पूर्णांकerrupts = kgd_init_पूर्णांकerrupts,
	.hqd_load = kgd_hqd_load,
	.hiq_mqd_load = kgd_hiq_mqd_load,
	.hqd_sdma_load = kgd_hqd_sdma_load,
	.hqd_dump = kgd_hqd_dump,
	.hqd_sdma_dump = kgd_hqd_sdma_dump,
	.hqd_is_occupied = kgd_hqd_is_occupied,
	.hqd_sdma_is_occupied = kgd_hqd_sdma_is_occupied,
	.hqd_destroy = kgd_hqd_destroy,
	.hqd_sdma_destroy = kgd_hqd_sdma_destroy,
	.address_watch_disable = kgd_address_watch_disable,
	.address_watch_execute = kgd_address_watch_execute,
	.wave_control_execute = kgd_wave_control_execute,
	.address_watch_get_offset = kgd_address_watch_get_offset,
	.get_atc_vmid_pasid_mapping_info =
			get_atc_vmid_pasid_mapping_info,
	.set_vm_context_page_table_base = set_vm_context_page_table_base,
पूर्ण;
