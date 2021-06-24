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
 */

#अगर_अघोषित __SOC15_COMMON_H__
#घोषणा __SOC15_COMMON_H__

/* Register Access Macros */
#घोषणा SOC15_REG_OFFSET(ip, inst, reg)	(adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg)

#घोषणा WREG32_FIELD15(ip, idx, reg, field, val)	\
	WREG32(adev->reg_offset[ip##_HWIP][idx][mm##reg##_BASE_IDX] + mm##reg,	\
	(RREG32(adev->reg_offset[ip##_HWIP][idx][mm##reg##_BASE_IDX] + mm##reg)	\
	& ~REG_FIELD_MASK(reg, field)) | (val) << REG_FIELD_SHIFT(reg, field))

#घोषणा RREG32_SOC15(ip, inst, reg) \
	RREG32(adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg)

#घोषणा RREG32_SOC15_NO_KIQ(ip, inst, reg) \
	RREG32_NO_KIQ(adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg)

#घोषणा RREG32_SOC15_OFFSET(ip, inst, reg, offset) \
	RREG32((adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg) + offset)

#घोषणा WREG32_SOC15(ip, inst, reg, value) \
	WREG32((adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg), value)

#घोषणा WREG32_SOC15_NO_KIQ(ip, inst, reg, value) \
	WREG32_NO_KIQ((adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg), value)

#घोषणा WREG32_SOC15_OFFSET(ip, inst, reg, offset, value) \
	WREG32((adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg) + offset, value)

#घोषणा SOC15_WAIT_ON_RREG(ip, inst, reg, expected_value, mask) \
(अणु	पूर्णांक ret = 0;						\
	करो अणु							\
		uपूर्णांक32_t old_ = 0;				\
		uपूर्णांक32_t पंचांगp_ = RREG32(adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg); \
		uपूर्णांक32_t loop = adev->usec_समयout;		\
		ret = 0;					\
		जबतक ((पंचांगp_ & (mask)) != (expected_value)) अणु	\
			अगर (old_ != पंचांगp_) अणु			\
				loop = adev->usec_समयout;	\
				old_ = पंचांगp_;			\
			पूर्ण अन्यथा					\
				udelay(1);			\
			पंचांगp_ = RREG32(adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg); \
			loop--;					\
			अगर (!loop) अणु				\
				DRM_WARN("Register(%d) [%s] failed to reach value 0x%08x != 0x%08x\n", \
					  inst, #reg, (अचिन्हित)expected_value, (अचिन्हित)(पंचांगp_ & (mask))); \
				ret = -ETIMEDOUT;		\
				अवरोध;				\
			पूर्ण					\
		पूर्ण						\
	पूर्ण जबतक (0);						\
	ret;							\
पूर्ण)

#घोषणा WREG32_RLC(reg, value) \
	करो अणु \
		अगर (adev->gfx.rlc.funcs->rlcg_wreg) \
			adev->gfx.rlc.funcs->rlcg_wreg(adev, reg, value, 0); \
		अन्यथा \
			WREG32(reg, value);	\
	पूर्ण जबतक (0)

#घोषणा WREG32_RLC_EX(prefix, reg, value) \
	करो अणु							\
		अगर (amdgpu_sriov_fullaccess(adev)) अणु    \
			uपूर्णांक32_t i = 0;	\
			uपूर्णांक32_t retries = 50000;	\
			uपूर्णांक32_t r0 = adev->reg_offset[GC_HWIP][0][prefix##SCRATCH_REG0_BASE_IDX] + prefix##SCRATCH_REG0;	\
			uपूर्णांक32_t r1 = adev->reg_offset[GC_HWIP][0][prefix##SCRATCH_REG1_BASE_IDX] + prefix##SCRATCH_REG1;	\
			uपूर्णांक32_t spare_पूर्णांक = adev->reg_offset[GC_HWIP][0][prefix##RLC_SPARE_INT_BASE_IDX] + prefix##RLC_SPARE_INT;	\
			WREG32(r0, value);	\
			WREG32(r1, (reg | 0x80000000));	\
			WREG32(spare_पूर्णांक, 0x1);	\
			क्रम (i = 0; i < retries; i++) अणु	\
				u32 पंचांगp = RREG32(r1);	\
				अगर (!(पंचांगp & 0x80000000))	\
					अवरोध;	\
				udelay(10);	\
			पूर्ण	\
			अगर (i >= retries)	\
				pr_err("timeout: rlcg program reg:0x%05x failed !\n", reg);	\
		पूर्ण अन्यथा अणु	\
			WREG32(reg, value); \
		पूर्ण	\
	पूर्ण जबतक (0)

#घोषणा WREG32_SOC15_RLC_SHADOW(ip, inst, reg, value) \
	WREG32_RLC((adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg), value)

#घोषणा RREG32_RLC(reg) \
	(adev->gfx.rlc.funcs->rlcg_rreg ? \
		adev->gfx.rlc.funcs->rlcg_rreg(adev, reg, 0) : RREG32(reg))

#घोषणा WREG32_RLC_NO_KIQ(reg, value) \
	करो अणु \
		अगर (adev->gfx.rlc.funcs->rlcg_wreg) \
			adev->gfx.rlc.funcs->rlcg_wreg(adev, reg, value, AMDGPU_REGS_NO_KIQ); \
		अन्यथा \
			WREG32_NO_KIQ(reg, value);	\
	पूर्ण जबतक (0)

#घोषणा RREG32_RLC_NO_KIQ(reg) \
	(adev->gfx.rlc.funcs->rlcg_rreg ? \
		adev->gfx.rlc.funcs->rlcg_rreg(adev, reg, AMDGPU_REGS_NO_KIQ) : RREG32_NO_KIQ(reg))

#घोषणा WREG32_SOC15_RLC_SHADOW_EX(prefix, ip, inst, reg, value) \
	करो अणु							\
		uपूर्णांक32_t target_reg = adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg;\
		अगर (amdgpu_sriov_fullaccess(adev)) अणु    \
			uपूर्णांक32_t r2 = adev->reg_offset[GC_HWIP][0][prefix##SCRATCH_REG1_BASE_IDX] + prefix##SCRATCH_REG2;	\
			uपूर्णांक32_t r3 = adev->reg_offset[GC_HWIP][0][prefix##SCRATCH_REG1_BASE_IDX] + prefix##SCRATCH_REG3;	\
			uपूर्णांक32_t grbm_cntl = adev->reg_offset[GC_HWIP][0][prefix##GRBM_GFX_CNTL_BASE_IDX] + prefix##GRBM_GFX_CNTL;   \
			uपूर्णांक32_t grbm_idx = adev->reg_offset[GC_HWIP][0][prefix##GRBM_GFX_INDEX_BASE_IDX] + prefix##GRBM_GFX_INDEX;   \
			अगर (target_reg == grbm_cntl) \
				WREG32(r2, value);	\
			अन्यथा अगर (target_reg == grbm_idx) \
				WREG32(r3, value);	\
			WREG32(target_reg, value);	\
		पूर्ण अन्यथा अणु	\
			WREG32(target_reg, value); \
		पूर्ण	\
	पूर्ण जबतक (0)

#घोषणा RREG32_SOC15_RLC(ip, inst, reg) \
	RREG32_RLC(adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg)

#घोषणा WREG32_SOC15_RLC(ip, inst, reg, value) \
	करो अणु							\
		uपूर्णांक32_t target_reg = adev->reg_offset[ip##_HWIP][0][reg##_BASE_IDX] + reg;\
		WREG32_RLC(target_reg, value); \
	पूर्ण जबतक (0)

#घोषणा WREG32_SOC15_RLC_EX(prefix, ip, inst, reg, value) \
	करो अणु							\
			uपूर्णांक32_t target_reg = adev->reg_offset[GC_HWIP][0][reg##_BASE_IDX] + reg;\
			WREG32_RLC_EX(prefix, target_reg, value); \
	पूर्ण जबतक (0)

#घोषणा WREG32_FIELD15_RLC(ip, idx, reg, field, val)   \
	WREG32_RLC((adev->reg_offset[ip##_HWIP][idx][mm##reg##_BASE_IDX] + mm##reg), \
	(RREG32_RLC(adev->reg_offset[ip##_HWIP][idx][mm##reg##_BASE_IDX] + mm##reg) \
	& ~REG_FIELD_MASK(reg, field)) | (val) << REG_FIELD_SHIFT(reg, field))

#घोषणा WREG32_SOC15_OFFSET_RLC(ip, inst, reg, offset, value) \
	WREG32_RLC(((adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg) + offset), value)

#घोषणा RREG32_SOC15_OFFSET_RLC(ip, inst, reg, offset) \
	RREG32_RLC(((adev->reg_offset[ip##_HWIP][inst][reg##_BASE_IDX] + reg) + offset))

#पूर्ण_अगर
