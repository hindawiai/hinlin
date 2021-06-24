<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
#समावेश "amdgpu.h"
#समावेश "smuio_v13_0.h"
#समावेश "smuio/smuio_13_0_2_offset.h"
#समावेश "smuio/smuio_13_0_2_sh_mask.h"

#घोषणा SMUIO_MCM_CONFIG__HOST_GPU_XGMI_MASK	0x00000001L

अटल u32 smuio_v13_0_get_rom_index_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(SMUIO, 0, regROM_INDEX);
पूर्ण

अटल u32 smuio_v13_0_get_rom_data_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(SMUIO, 0, regROM_DATA);
पूर्ण

अटल व्योम smuio_v13_0_update_rom_घड़ी_gating(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 def, data;

	/* enable/disable ROM CG is not supported on APU */
	अगर (adev->flags & AMD_IS_APU)
		वापस;

	def = data = RREG32_SOC15(SMUIO, 0, regCGTT_ROM_CLK_CTRL0);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_ROM_MGCG))
		data &= ~(CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE0_MASK |
			CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE1_MASK);
	अन्यथा
		data |= CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE0_MASK |
			CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE1_MASK;

	अगर (def != data)
		WREG32_SOC15(SMUIO, 0, regCGTT_ROM_CLK_CTRL0, data);
पूर्ण

अटल व्योम smuio_v13_0_get_घड़ी_gating_state(काष्ठा amdgpu_device *adev, u32 *flags)
अणु
	u32 data;

	/* CGTT_ROM_CLK_CTRL0 is not available क्रम APU */
	अगर (adev->flags & AMD_IS_APU)
		वापस;

	data = RREG32_SOC15(SMUIO, 0, regCGTT_ROM_CLK_CTRL0);
	अगर (!(data & CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE0_MASK))
		*flags |= AMD_CG_SUPPORT_ROM_MGCG;
पूर्ण

/**
 * smuio_v13_0_get_die_id - query die id from FCH.
 *
 * @adev: amdgpu device poपूर्णांकer
 *
 * Returns die id
 */
अटल u32 smuio_v13_0_get_die_id(काष्ठा amdgpu_device *adev)
अणु
	u32 data, die_id;

	data = RREG32_SOC15(SMUIO, 0, regSMUIO_MCM_CONFIG);
	die_id = REG_GET_FIELD(data, SMUIO_MCM_CONFIG, DIE_ID);

	वापस die_id;
पूर्ण

/**
 * smuio_v13_0_supports_host_gpu_xgmi - detect xgmi पूर्णांकerface between cpu and gpu/s.
 *
 * @adev: amdgpu device poपूर्णांकer
 *
 * Returns true on success or false otherwise.
 */
अटल bool smuio_v13_0_is_host_gpu_xgmi_supported(काष्ठा amdgpu_device *adev)
अणु
	u32 data;

	data = RREG32_SOC15(SMUIO, 0, regSMUIO_MCM_CONFIG);
	data = REG_GET_FIELD(data, SMUIO_MCM_CONFIG, TOPOLOGY_ID);
	/* data[4:0]
	 * bit 0 == 0 host-gpu पूर्णांकerface is PCIE
	 * bit 0 == 1 host-gpu पूर्णांकerface is Alternate Protocal
	 * क्रम AMD, this is XGMI
	 */
	data &= SMUIO_MCM_CONFIG__HOST_GPU_XGMI_MASK;

	वापस data ? true : false;
पूर्ण

स्थिर काष्ठा amdgpu_smuio_funcs smuio_v13_0_funcs = अणु
	.get_rom_index_offset = smuio_v13_0_get_rom_index_offset,
	.get_rom_data_offset = smuio_v13_0_get_rom_data_offset,
	.get_die_id = smuio_v13_0_get_die_id,
	.is_host_gpu_xgmi_supported = smuio_v13_0_is_host_gpu_xgmi_supported,
	.update_rom_घड़ी_gating = smuio_v13_0_update_rom_घड़ी_gating,
	.get_घड़ी_gating_state = smuio_v13_0_get_घड़ी_gating_state,
पूर्ण;
