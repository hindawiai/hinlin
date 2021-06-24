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
#समावेश <linux/module.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/firmware.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "sdma0/sdma0_4_2_2_offset.h"
#समावेश "sdma0/sdma0_4_2_2_sh_mask.h"
#समावेश "sdma1/sdma1_4_2_2_offset.h"
#समावेश "sdma1/sdma1_4_2_2_sh_mask.h"
#समावेश "sdma2/sdma2_4_2_2_offset.h"
#समावेश "sdma2/sdma2_4_2_2_sh_mask.h"
#समावेश "sdma3/sdma3_4_2_2_offset.h"
#समावेश "sdma3/sdma3_4_2_2_sh_mask.h"
#समावेश "sdma4/sdma4_4_2_2_offset.h"
#समावेश "sdma4/sdma4_4_2_2_sh_mask.h"
#समावेश "sdma5/sdma5_4_2_2_offset.h"
#समावेश "sdma5/sdma5_4_2_2_sh_mask.h"
#समावेश "sdma6/sdma6_4_2_2_offset.h"
#समावेश "sdma6/sdma6_4_2_2_sh_mask.h"
#समावेश "sdma7/sdma7_4_2_2_offset.h"
#समावेश "sdma7/sdma7_4_2_2_sh_mask.h"
#समावेश "v9_structs.h"
#समावेश "soc15.h"
#समावेश "soc15d.h"
#समावेश "amdgpu_amdkfd_gfx_v9.h"
#समावेश "gfxhub_v1_0.h"
#समावेश "mmhub_v9_4.h"

#घोषणा HQD_N_REGS 56
#घोषणा DUMP_REG(addr) करो अणु				\
		अगर (WARN_ON_ONCE(i >= HQD_N_REGS))	\
			अवरोध;				\
		(*dump)[i][0] = (addr) << 2;		\
		(*dump)[i++][1] = RREG32(addr);		\
	पूर्ण जबतक (0)

अटल अंतरभूत काष्ठा amdgpu_device *get_amdgpu_device(काष्ठा kgd_dev *kgd)
अणु
	वापस (काष्ठा amdgpu_device *)kgd;
पूर्ण

अटल अंतरभूत काष्ठा v9_sdma_mqd *get_sdma_mqd(व्योम *mqd)
अणु
	वापस (काष्ठा v9_sdma_mqd *)mqd;
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
		sdma_engine_reg_base = SOC15_REG_OFFSET(SDMA1, 0,
				mmSDMA1_RLC0_RB_CNTL) - mmSDMA1_RLC0_RB_CNTL;
		अवरोध;
	हाल 2:
		sdma_engine_reg_base = SOC15_REG_OFFSET(SDMA2, 0,
				mmSDMA2_RLC0_RB_CNTL) - mmSDMA2_RLC0_RB_CNTL;
		अवरोध;
	हाल 3:
		sdma_engine_reg_base = SOC15_REG_OFFSET(SDMA3, 0,
				mmSDMA3_RLC0_RB_CNTL) - mmSDMA3_RLC0_RB_CNTL;
		अवरोध;
	हाल 4:
		sdma_engine_reg_base = SOC15_REG_OFFSET(SDMA4, 0,
				mmSDMA4_RLC0_RB_CNTL) - mmSDMA4_RLC0_RB_CNTL;
		अवरोध;
	हाल 5:
		sdma_engine_reg_base = SOC15_REG_OFFSET(SDMA5, 0,
				mmSDMA5_RLC0_RB_CNTL) - mmSDMA5_RLC0_RB_CNTL;
		अवरोध;
	हाल 6:
		sdma_engine_reg_base = SOC15_REG_OFFSET(SDMA6, 0,
				mmSDMA6_RLC0_RB_CNTL) - mmSDMA6_RLC0_RB_CNTL;
		अवरोध;
	हाल 7:
		sdma_engine_reg_base = SOC15_REG_OFFSET(SDMA7, 0,
				mmSDMA7_RLC0_RB_CNTL) - mmSDMA7_RLC0_RB_CNTL;
		अवरोध;
	पूर्ण

	sdma_rlc_reg_offset = sdma_engine_reg_base
		+ queue_id * (mmSDMA0_RLC1_RB_CNTL - mmSDMA0_RLC0_RB_CNTL);

	pr_debug("RLC register offset for SDMA%d RLC%d: 0x%x\n", engine_id,
			queue_id, sdma_rlc_reg_offset);

	वापस sdma_rlc_reg_offset;
पूर्ण

पूर्णांक kgd_arcturus_hqd_sdma_load(काष्ठा kgd_dev *kgd, व्योम *mqd,
			     uपूर्णांक32_t __user *wptr, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा v9_sdma_mqd *m;
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

पूर्णांक kgd_arcturus_hqd_sdma_dump(काष्ठा kgd_dev *kgd,
			     uपूर्णांक32_t engine_id, uपूर्णांक32_t queue_id,
			     uपूर्णांक32_t (**dump)[2], uपूर्णांक32_t *n_regs)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	uपूर्णांक32_t sdma_rlc_reg_offset = get_sdma_rlc_reg_offset(adev,
			engine_id, queue_id);
	uपूर्णांक32_t i = 0, reg;
#अघोषित HQD_N_REGS
#घोषणा HQD_N_REGS (19+6+7+10)

	*dump = kदो_स्मृति_array(HQD_N_REGS * 2, माप(uपूर्णांक32_t), GFP_KERNEL);
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

bool kgd_arcturus_hqd_sdma_is_occupied(काष्ठा kgd_dev *kgd, व्योम *mqd)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा v9_sdma_mqd *m;
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

पूर्णांक kgd_arcturus_hqd_sdma_destroy(काष्ठा kgd_dev *kgd, व्योम *mqd,
				अचिन्हित पूर्णांक uसमयout)
अणु
	काष्ठा amdgpu_device *adev = get_amdgpu_device(kgd);
	काष्ठा v9_sdma_mqd *m;
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

स्थिर काष्ठा kfd2kgd_calls arcturus_kfd2kgd = अणु
	.program_sh_mem_settings = kgd_gfx_v9_program_sh_mem_settings,
	.set_pasid_vmid_mapping = kgd_gfx_v9_set_pasid_vmid_mapping,
	.init_पूर्णांकerrupts = kgd_gfx_v9_init_पूर्णांकerrupts,
	.hqd_load = kgd_gfx_v9_hqd_load,
	.hiq_mqd_load = kgd_gfx_v9_hiq_mqd_load,
	.hqd_sdma_load = kgd_arcturus_hqd_sdma_load,
	.hqd_dump = kgd_gfx_v9_hqd_dump,
	.hqd_sdma_dump = kgd_arcturus_hqd_sdma_dump,
	.hqd_is_occupied = kgd_gfx_v9_hqd_is_occupied,
	.hqd_sdma_is_occupied = kgd_arcturus_hqd_sdma_is_occupied,
	.hqd_destroy = kgd_gfx_v9_hqd_destroy,
	.hqd_sdma_destroy = kgd_arcturus_hqd_sdma_destroy,
	.address_watch_disable = kgd_gfx_v9_address_watch_disable,
	.address_watch_execute = kgd_gfx_v9_address_watch_execute,
	.wave_control_execute = kgd_gfx_v9_wave_control_execute,
	.address_watch_get_offset = kgd_gfx_v9_address_watch_get_offset,
	.get_atc_vmid_pasid_mapping_info =
				kgd_gfx_v9_get_atc_vmid_pasid_mapping_info,
	.set_vm_context_page_table_base =
				kgd_gfx_v9_set_vm_context_page_table_base,
	.get_cu_occupancy = kgd_gfx_v9_get_cu_occupancy
पूर्ण;
