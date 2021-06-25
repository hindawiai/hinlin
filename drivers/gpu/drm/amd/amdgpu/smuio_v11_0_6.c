<शैली गुरु>
/*
 * Copyright 2021 Advanced Micro Devices, Inc.
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
#समावेश "smuio_v11_0_6.h"
#समावेश "smuio/smuio_11_0_6_offset.h"
#समावेश "smuio/smuio_11_0_6_sh_mask.h"

अटल u32 smuio_v11_0_6_get_rom_index_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(SMUIO, 0, mmROM_INDEX);
पूर्ण

अटल u32 smuio_v11_0_6_get_rom_data_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(SMUIO, 0, mmROM_DATA);
पूर्ण

अटल व्योम smuio_v11_0_6_update_rom_घड़ी_gating(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 def, data;

	/* enable/disable ROM CG is not supported on APU */
	अगर (adev->flags & AMD_IS_APU)
		वापस;

	def = data = RREG32_SOC15(SMUIO, 0, mmCGTT_ROM_CLK_CTRL0);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_ROM_MGCG))
		data &= ~(CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE0_MASK |
			CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE1_MASK);
	अन्यथा
		data |= CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE0_MASK |
			CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE1_MASK;

	अगर (def != data)
		WREG32_SOC15(SMUIO, 0, mmCGTT_ROM_CLK_CTRL0, data);
पूर्ण

अटल व्योम smuio_v11_0_6_get_घड़ी_gating_state(काष्ठा amdgpu_device *adev, u32 *flags)
अणु
	u32 data;

	/* CGTT_ROM_CLK_CTRL0 is not available क्रम APU */
	अगर (adev->flags & AMD_IS_APU)
		वापस;

	data = RREG32_SOC15(SMUIO, 0, mmCGTT_ROM_CLK_CTRL0);
	अगर (!(data & CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE0_MASK))
		*flags |= AMD_CG_SUPPORT_ROM_MGCG;
पूर्ण

स्थिर काष्ठा amdgpu_smuio_funcs smuio_v11_0_6_funcs = अणु
	.get_rom_index_offset = smuio_v11_0_6_get_rom_index_offset,
	.get_rom_data_offset = smuio_v11_0_6_get_rom_data_offset,
	.update_rom_घड़ी_gating = smuio_v11_0_6_update_rom_घड़ी_gating,
	.get_घड़ी_gating_state = smuio_v11_0_6_get_घड़ी_gating_state,
पूर्ण;
