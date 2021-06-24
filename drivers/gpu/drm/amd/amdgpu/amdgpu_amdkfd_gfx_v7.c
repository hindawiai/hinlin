<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
#समावेश "cikd.h"
#समावेश "cik_sdma.h"
#समावेश "gfx_v7_0.h"
#समावेश "gca/gfx_7_2_d.h"
#समावेश "gca/gfx_7_2_enum.h"
#समावेश "gca/gfx_7_2_sh_mask.h"
#समावेश "oss/oss_2_0_d.h"
#समावेश "oss/oss_2_0_sh_mask.h"
#समावेश "gmc/gmc_7_1_d.h"
#समावेश "gmc/gmc_7_1_sh_mask.h"
#समावेश "cik_structs.h"

क्रमागत hqd_dequeue_request_type अणु
	NO_ACTION = 0,
	DRAIN_PIPE,
	RESET_WAVES
पूर्ण;

क्रमागत अणु
	MAX_TRAPID = 8,		/* 3 bits in the bitfield. */
	MAX_WATCH_ADDRESSES = 4
पूर्ण;

क्रमागत अणु
	ADDRESS_WATCH_REG_ADDR_HI = 0,
	ADDRESS_WATCH_REG_ADDR_LO,
	ADDRESS_WATCH_REG_CNTL,
	ADDRESS_WATCH_REG_MAX
पूर्ण;

/*  not defined in the CI/KV reg file  */
क्रमागत अणु
	ADDRESS_WATCH_REG_CNTL_ATC_BIT = 0x10000000UL,
	ADDRESS_WATCH_REG_CNTL_DEFAULT_MASK = 0x00FFFFFF,
	ADDRESS_WATCH_REG_ADDLOW_MASK_EXTENSION = 0x03000000,
	/* extend the mask to 26 bits to match the low address field */
	ADDRESS_WATCH_REG_ADDLOW_SHIFT = 6,
	ADDRESS_WATCH_REG_ADDHIGH_MASK = 0xFFFF
पूर्ण;

अटल स्थिर uपूर्णांक32_t watchRegs[MAX_WATCH_ADDRESSES * ADDRESS_WATCH_REG_MAX] = अणु
	mmTCP_WATCH0_ADDR_H, mmTCP_WATCH0_ADDR_L, mmTCP_WATCH0_CNTL,
	mmTCP_WATCH1_ADDR_H, mmTCP_WATCH1_ADDR_L, mmTCP_WATCH1_CNTL,
	mmTCP_WATCH2_ADDR_H, mmTCP_WATCH2_ADDR_L, mmTCP_WATCH2_CNTL,
	mmTCP_WATCH3_ADDR_H, mmTCP_WATCH3_ADDR_L, mmTCP_WATCH3_CNTL
पूर्ण;

जोड़ TCP_WATCH_CNTL_BITS अणु
	काष्ठा अणु
		uपूर्णांक32_t mask:24;
		uपूर्णांक32_t vmid:4;
		uपूर्णांक32_t atc:1;
		uपूर्णांक32_t mode:2;
		uपूर्णांक32_t valid:1;
	पूर्ण bitfields, bits;
	uपूर्णांक32_t u32All;
	चिन्हित पूर्णांक i32All;
	भग्न f32All;
पूर्ण;

अटल अंतरभूत काष्ठा amdgpu_device *get_amdgpu_device(काष्ठा kgd_dev *kgd)
अणु
	वापस (काष्ठा amdgpu_device *)kgd;
पूर्ण

अटल व्योम lock_srbm(काष्ठा kgd_dev *kgd, uपूर्णांक32_t mec, uपूर्णांक32_t pipe,
			uपूर्णांक32_t queue, uपूर्णांक32_t vmid)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t value = PIPEID(pipe) | MEID(mec) | VMID(vmid) | QUEUEID(queue);

	mutex_lock(&adev->srbm_mutex);
	WREG32(mmSRBM_GFX_CNTL, value);
पूर्ण

अटल व्योम unlock_srbm(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	WREG32(mmSRBM_GFX_CNTL, 0);
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

	WREG32(mmSH_MEM_CONFIG, sh_mem_config);
	WREG32(mmSH_MEM_APE1_BASE, sh_mem_ape1_base);
	WREG32(mmSH_MEM_APE1_LIMIT, sh_mem_ape1_limit);
	WREG32(mmSH_MEM_BASES, sh_mem_bases);

	unlock_srbm(kgd);
पूर्ण

अटल पूर्णांक kgd_set_pasid_vmid_mapping(काष्ठा kgd_dev *kgd, u32 pasid,
					अचिन्हित पूर्णांक vmid)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	/*
	 * We have to assume that there is no outstanding mapping.
	 * The ATC_VMID_PASID_MAPPING_UPDATE_STATUS bit could be 0 because
	 * a mapping is in progress or because a mapping finished and the
	 * SW cleared it. So the protocol is to always रुको & clear.
	 */
	uपूर्णांक32_t pasid_mapping = (pasid == 0) ? 0 : (uपूर्णांक32_t)pasid |
			ATC_VMID0_PASID_MAPPING__VALID_MASK;

	WREG32(mmATC_VMID0_PASID_MAPPING + vmid, pasid_mapping);

	जबतक (!(RREG32(mmATC_VMID_PASID_MAPPING_UPDATE_STATUS) & (1U << vmid)))
		cpu_relax();
	WREG32(mmATC_VMID_PASID_MAPPING_UPDATE_STATUS, 1U << vmid);

	/* Mapping vmid to pasid also क्रम IH block */
	WREG32(mmIH_VMID_0_LUT + vmid, pasid_mapping);

	वापस 0;
पूर्ण

अटल पूर्णांक kgd_init_पूर्णांकerrupts(काष्ठा kgd_dev *kgd, uपूर्णांक32_t pipe_id)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t mec;
	uपूर्णांक32_t pipe;

	mec = (pipe_id / adev->gfx.mec.num_pipe_per_mec) + 1;
	pipe = (pipe_id % adev->gfx.mec.num_pipe_per_mec);

	lock_srbm(kgd, mec, pipe, 0, 0);

	WREG32(mmCPC_INT_CNTL, CP_INT_CNTL_RING0__TIME_STAMP_INT_ENABLE_MASK |
			CP_INT_CNTL_RING0__OPCODE_ERROR_INT_ENABLE_MASK);

	unlock_srbm(kgd);

	वापस 0;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t get_sdma_rlc_reg_offset(काष्ठा cik_sdma_rlc_रेजिस्टरs *m)
अणु
	uपूर्णांक32_t retval;

	retval = m->sdma_engine_id * SDMA1_REGISTER_OFFSET +
			m->sdma_queue_id * KFD_CIK_SDMA_QUEUE_OFFSET;

	pr_debug("RLC register offset for SDMA%d RLC%d: 0x%x\n",
			m->sdma_engine_id, m->sdma_queue_id, retval);

	वापस retval;
पूर्ण

अटल अंतरभूत काष्ठा cik_mqd *get_mqd(व्योम *mqd)
अणु
	वापस (काष्ठा cik_mqd *)mqd;
पूर्ण

अटल अंतरभूत काष्ठा cik_sdma_rlc_रेजिस्टरs *get_sdma_mqd(व्योम *mqd)
अणु
	वापस (काष्ठा cik_sdma_rlc_रेजिस्टरs *)mqd;
पूर्ण

अटल पूर्णांक kgd_hqd_load(काष्ठा kgd_dev *kgd, व्योम *mqd, uपूर्णांक32_t pipe_id,
			uपूर्णांक32_t queue_id, uपूर्णांक32_t __user *wptr,
			uपूर्णांक32_t wptr_shअगरt, uपूर्णांक32_t wptr_mask,
			काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा cik_mqd *m;
	uपूर्णांक32_t *mqd_hqd;
	uपूर्णांक32_t reg, wptr_val, data;
	bool valid_wptr = false;

	m = get_mqd(mqd);

	acquire_queue(kgd, pipe_id, queue_id);

	/* HQD रेजिस्टरs extend from CP_MQD_BASE_ADDR to CP_MQD_CONTROL. */
	mqd_hqd = &m->cp_mqd_base_addr_lo;

	क्रम (reg = mmCP_MQD_BASE_ADDR; reg <= mmCP_MQD_CONTROL; reg++)
		WREG32(reg, mqd_hqd[reg - mmCP_MQD_BASE_ADDR]);

	/* Copy userspace ग_लिखो poपूर्णांकer value to रेजिस्टर.
	 * Activate करोorbell logic to monitor subsequent changes.
	 */
	data = REG_SET_FIELD(m->cp_hqd_pq_करोorbell_control,
			     CP_HQD_PQ_DOORBELL_CONTROL, DOORBELL_EN, 1);
	WREG32(mmCP_HQD_PQ_DOORBELL_CONTROL, data);

	/* पढ़ो_user_ptr may take the mm->mmap_lock.
	 * release srbm_mutex to aव्योम circular dependency between
	 * srbm_mutex->mm_sem->reservation_ww_class_mutex->srbm_mutex.
	 */
	release_queue(kgd);
	valid_wptr = पढ़ो_user_wptr(mm, wptr, wptr_val);
	acquire_queue(kgd, pipe_id, queue_id);
	अगर (valid_wptr)
		WREG32(mmCP_HQD_PQ_WPTR, (wptr_val << wptr_shअगरt) & wptr_mask);

	data = REG_SET_FIELD(m->cp_hqd_active, CP_HQD_ACTIVE, ACTIVE, 1);
	WREG32(mmCP_HQD_ACTIVE, data);

	release_queue(kgd);

	वापस 0;
पूर्ण

अटल पूर्णांक kgd_hqd_dump(काष्ठा kgd_dev *kgd,
			uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id,
			uपूर्णांक32_t (**dump)[2], uपूर्णांक32_t *n_regs)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t i = 0, reg;
#घोषणा HQD_N_REGS (35+4)
#घोषणा DUMP_REG(addr) करो अणु				\
		अगर (WARN_ON_ONCE(i >= HQD_N_REGS))	\
			अवरोध;				\
		(*dump)[i][0] = (addr) << 2;		\
		(*dump)[i++][1] = RREG32(addr);		\
	पूर्ण जबतक (0)

	*dump = kदो_स्मृति_array(HQD_N_REGS * 2, माप(uपूर्णांक32_t), GFP_KERNEL);
	अगर (*dump == शून्य)
		वापस -ENOMEM;

	acquire_queue(kgd, pipe_id, queue_id);

	DUMP_REG(mmCOMPUTE_STATIC_THREAD_MGMT_SE0);
	DUMP_REG(mmCOMPUTE_STATIC_THREAD_MGMT_SE1);
	DUMP_REG(mmCOMPUTE_STATIC_THREAD_MGMT_SE2);
	DUMP_REG(mmCOMPUTE_STATIC_THREAD_MGMT_SE3);

	क्रम (reg = mmCP_MQD_BASE_ADDR; reg <= mmCP_MQD_CONTROL; reg++)
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
	काष्ठा cik_sdma_rlc_रेजिस्टरs *m;
	अचिन्हित दीर्घ end_jअगरfies;
	uपूर्णांक32_t sdma_rlc_reg_offset;
	uपूर्णांक32_t data;

	m = get_sdma_mqd(mqd);
	sdma_rlc_reg_offset = get_sdma_rlc_reg_offset(m);

	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_CNTL,
		m->sdma_rlc_rb_cntl & (~SDMA0_RLC0_RB_CNTL__RB_ENABLE_MASK));

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

	data = REG_SET_FIELD(m->sdma_rlc_करोorbell, SDMA0_RLC0_DOORBELL,
			     ENABLE, 1);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_DOORBELL, data);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_RPTR,
				m->sdma_rlc_rb_rptr);

	अगर (पढ़ो_user_wptr(mm, wptr, data))
		WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_WPTR, data);
	अन्यथा
		WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_WPTR,
		       m->sdma_rlc_rb_rptr);

	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_VIRTUAL_ADDR,
				m->sdma_rlc_भव_addr);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_BASE, m->sdma_rlc_rb_base);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_BASE_HI,
			m->sdma_rlc_rb_base_hi);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_RPTR_ADDR_LO,
			m->sdma_rlc_rb_rptr_addr_lo);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_RPTR_ADDR_HI,
			m->sdma_rlc_rb_rptr_addr_hi);

	data = REG_SET_FIELD(m->sdma_rlc_rb_cntl, SDMA0_RLC0_RB_CNTL,
			     RB_ENABLE, 1);
	WREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_CNTL, data);

	वापस 0;
पूर्ण

अटल पूर्णांक kgd_hqd_sdma_dump(काष्ठा kgd_dev *kgd,
			     uपूर्णांक32_t engine_id, uपूर्णांक32_t queue_id,
			     uपूर्णांक32_t (**dump)[2], uपूर्णांक32_t *n_regs)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t sdma_offset = engine_id * SDMA1_REGISTER_OFFSET +
		queue_id * KFD_CIK_SDMA_QUEUE_OFFSET;
	uपूर्णांक32_t i = 0, reg;
#अघोषित HQD_N_REGS
#घोषणा HQD_N_REGS (19+4)

	*dump = kदो_स्मृति_array(HQD_N_REGS * 2, माप(uपूर्णांक32_t), GFP_KERNEL);
	अगर (*dump == शून्य)
		वापस -ENOMEM;

	क्रम (reg = mmSDMA0_RLC0_RB_CNTL; reg <= mmSDMA0_RLC0_DOORBELL; reg++)
		DUMP_REG(sdma_offset + reg);
	क्रम (reg = mmSDMA0_RLC0_VIRTUAL_ADDR; reg <= mmSDMA0_RLC0_WATERMARK;
	     reg++)
		DUMP_REG(sdma_offset + reg);

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
	act = RREG32(mmCP_HQD_ACTIVE);
	अगर (act) अणु
		low = lower_32_bits(queue_address >> 8);
		high = upper_32_bits(queue_address >> 8);

		अगर (low == RREG32(mmCP_HQD_PQ_BASE) &&
				high == RREG32(mmCP_HQD_PQ_BASE_HI))
			retval = true;
	पूर्ण
	release_queue(kgd);
	वापस retval;
पूर्ण

अटल bool kgd_hqd_sdma_is_occupied(काष्ठा kgd_dev *kgd, व्योम *mqd)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा cik_sdma_rlc_रेजिस्टरs *m;
	uपूर्णांक32_t sdma_rlc_reg_offset;
	uपूर्णांक32_t sdma_rlc_rb_cntl;

	m = get_sdma_mqd(mqd);
	sdma_rlc_reg_offset = get_sdma_rlc_reg_offset(m);

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
	uपूर्णांक32_t temp;
	क्रमागत hqd_dequeue_request_type type;
	अचिन्हित दीर्घ flags, end_jअगरfies;
	पूर्णांक retry;

	अगर (amdgpu_in_reset(adev))
		वापस -EIO;

	acquire_queue(kgd, pipe_id, queue_id);
	WREG32(mmCP_HQD_PQ_DOORBELL_CONTROL, 0);

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

	WREG32(mmCP_HQD_DEQUEUE_REQUEST, type);

	end_jअगरfies = (uसमयout * HZ / 1000) + jअगरfies;
	जबतक (true) अणु
		temp = RREG32(mmCP_HQD_ACTIVE);
		अगर (!(temp & CP_HQD_ACTIVE__ACTIVE_MASK))
			अवरोध;
		अगर (समय_after(jअगरfies, end_jअगरfies)) अणु
			pr_err("cp queue preemption time out\n");
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
	काष्ठा cik_sdma_rlc_रेजिस्टरs *m;
	uपूर्णांक32_t sdma_rlc_reg_offset;
	uपूर्णांक32_t temp;
	अचिन्हित दीर्घ end_jअगरfies = (uसमयout * HZ / 1000) + jअगरfies;

	m = get_sdma_mqd(mqd);
	sdma_rlc_reg_offset = get_sdma_rlc_reg_offset(m);

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

	m->sdma_rlc_rb_rptr = RREG32(sdma_rlc_reg_offset + mmSDMA0_RLC0_RB_RPTR);

	वापस 0;
पूर्ण

अटल पूर्णांक kgd_address_watch_disable(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	जोड़ TCP_WATCH_CNTL_BITS cntl;
	अचिन्हित पूर्णांक i;

	cntl.u32All = 0;

	cntl.bitfields.valid = 0;
	cntl.bitfields.mask = ADDRESS_WATCH_REG_CNTL_DEFAULT_MASK;
	cntl.bitfields.atc = 1;

	/* Turning off this address until we set all the रेजिस्टरs */
	क्रम (i = 0; i < MAX_WATCH_ADDRESSES; i++)
		WREG32(watchRegs[i * ADDRESS_WATCH_REG_MAX +
			ADDRESS_WATCH_REG_CNTL], cntl.u32All);

	वापस 0;
पूर्ण

अटल पूर्णांक kgd_address_watch_execute(काष्ठा kgd_dev *kgd,
					अचिन्हित पूर्णांक watch_poपूर्णांक_id,
					uपूर्णांक32_t cntl_val,
					uपूर्णांक32_t addr_hi,
					uपूर्णांक32_t addr_lo)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	जोड़ TCP_WATCH_CNTL_BITS cntl;

	cntl.u32All = cntl_val;

	/* Turning off this watch poपूर्णांक until we set all the रेजिस्टरs */
	cntl.bitfields.valid = 0;
	WREG32(watchRegs[watch_poपूर्णांक_id * ADDRESS_WATCH_REG_MAX +
		ADDRESS_WATCH_REG_CNTL], cntl.u32All);

	WREG32(watchRegs[watch_poपूर्णांक_id * ADDRESS_WATCH_REG_MAX +
		ADDRESS_WATCH_REG_ADDR_HI], addr_hi);

	WREG32(watchRegs[watch_poपूर्णांक_id * ADDRESS_WATCH_REG_MAX +
		ADDRESS_WATCH_REG_ADDR_LO], addr_lo);

	/* Enable the watch poपूर्णांक */
	cntl.bitfields.valid = 1;

	WREG32(watchRegs[watch_poपूर्णांक_id * ADDRESS_WATCH_REG_MAX +
		ADDRESS_WATCH_REG_CNTL], cntl.u32All);

	वापस 0;
पूर्ण

अटल पूर्णांक kgd_wave_control_execute(काष्ठा kgd_dev *kgd,
					uपूर्णांक32_t gfx_index_val,
					uपूर्णांक32_t sq_cmd)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t data;

	mutex_lock(&adev->grbm_idx_mutex);

	WREG32(mmGRBM_GFX_INDEX, gfx_index_val);
	WREG32(mmSQ_CMD, sq_cmd);

	/*  Restore the GRBM_GFX_INDEX रेजिस्टर  */

	data = GRBM_GFX_INDEX__INSTANCE_BROADCAST_WRITES_MASK |
		GRBM_GFX_INDEX__SH_BROADCAST_WRITES_MASK |
		GRBM_GFX_INDEX__SE_BROADCAST_WRITES_MASK;

	WREG32(mmGRBM_GFX_INDEX, data);

	mutex_unlock(&adev->grbm_idx_mutex);

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t kgd_address_watch_get_offset(काष्ठा kgd_dev *kgd,
					अचिन्हित पूर्णांक watch_poपूर्णांक_id,
					अचिन्हित पूर्णांक reg_offset)
अणु
	वापस watchRegs[watch_poपूर्णांक_id * ADDRESS_WATCH_REG_MAX + reg_offset];
पूर्ण

अटल bool get_atc_vmid_pasid_mapping_info(काष्ठा kgd_dev *kgd,
					uपूर्णांक8_t vmid, uपूर्णांक16_t *p_pasid)
अणु
	uपूर्णांक32_t value;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *) kgd;

	value = RREG32(mmATC_VMID0_PASID_MAPPING + vmid);
	*p_pasid = value & ATC_VMID0_PASID_MAPPING__PASID_MASK;

	वापस !!(value & ATC_VMID0_PASID_MAPPING__VALID_MASK);
पूर्ण

अटल व्योम set_scratch_backing_va(काष्ठा kgd_dev *kgd,
					uपूर्णांक64_t va, uपूर्णांक32_t vmid)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *) kgd;

	lock_srbm(kgd, 0, 0, 0, vmid);
	WREG32(mmSH_HIDDEN_PRIVATE_BASE_VMID, va);
	unlock_srbm(kgd);
पूर्ण

अटल व्योम set_vm_context_page_table_base(काष्ठा kgd_dev *kgd, uपूर्णांक32_t vmid,
			uपूर्णांक64_t page_table_base)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	अगर (!amdgpu_amdkfd_is_kfd_vmid(adev, vmid)) अणु
		pr_err("trying to set page table base for wrong VMID\n");
		वापस;
	पूर्ण
	WREG32(mmVM_CONTEXT8_PAGE_TABLE_BASE_ADDR + vmid - 8,
		lower_32_bits(page_table_base));
पूर्ण

 /**
  * पढ़ो_vmid_from_vmfault_reg - पढ़ो vmid from रेजिस्टर
  *
  * adev: amdgpu_device poपूर्णांकer
  * @vmid: vmid poपूर्णांकer
  * पढ़ो vmid from रेजिस्टर (CIK).
  */
अटल uपूर्णांक32_t पढ़ो_vmid_from_vmfault_reg(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);

	uपूर्णांक32_t status = RREG32(mmVM_CONTEXT1_PROTECTION_FAULT_STATUS);

	वापस REG_GET_FIELD(status, VM_CONTEXT1_PROTECTION_FAULT_STATUS, VMID);
पूर्ण

स्थिर काष्ठा kfd2kgd_calls gfx_v7_kfd2kgd = अणु
	.program_sh_mem_settings = kgd_program_sh_mem_settings,
	.set_pasid_vmid_mapping = kgd_set_pasid_vmid_mapping,
	.init_पूर्णांकerrupts = kgd_init_पूर्णांकerrupts,
	.hqd_load = kgd_hqd_load,
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
	.get_atc_vmid_pasid_mapping_info = get_atc_vmid_pasid_mapping_info,
	.set_scratch_backing_va = set_scratch_backing_va,
	.set_vm_context_page_table_base = set_vm_context_page_table_base,
	.पढ़ो_vmid_from_vmfault_reg = पढ़ो_vmid_from_vmfault_reg,
पूर्ण;
