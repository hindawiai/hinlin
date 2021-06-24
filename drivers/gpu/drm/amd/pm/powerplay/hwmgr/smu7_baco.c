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
 *
 */
#समावेश "amdgpu.h"
#समावेश "smu7_baco.h"
#समावेश "tonga_baco.h"
#समावेश "fiji_baco.h"
#समावेश "polaris_baco.h"
#समावेश "ci_baco.h"

#समावेश "bif/bif_5_0_d.h"
#समावेश "bif/bif_5_0_sh_mask.h"

#समावेश "smu/smu_7_1_2_d.h"
#समावेश "smu/smu_7_1_2_sh_mask.h"

पूर्णांक smu7_baco_get_capability(काष्ठा pp_hwmgr *hwmgr, bool *cap)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	uपूर्णांक32_t reg;

	*cap = false;
	अगर (!phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_BACO))
		वापस 0;

	reg = RREG32(mmCC_BIF_BX_FUSESTRAP0);

	अगर (reg & CC_BIF_BX_FUSESTRAP0__STRAP_BIF_PX_CAPABLE_MASK)
		*cap = true;

	वापस 0;
पूर्ण

पूर्णांक smu7_baco_get_state(काष्ठा pp_hwmgr *hwmgr, क्रमागत BACO_STATE *state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	uपूर्णांक32_t reg;

	reg = RREG32(mmBACO_CNTL);

	अगर (reg & BACO_CNTL__BACO_MODE_MASK)
		/* gfx has alपढ़ोy entered BACO state */
		*state = BACO_STATE_IN;
	अन्यथा
		*state = BACO_STATE_OUT;
	वापस 0;
पूर्ण

पूर्णांक smu7_baco_set_state(काष्ठा pp_hwmgr *hwmgr, क्रमागत BACO_STATE state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);

	चयन (adev->asic_type) अणु
	हाल CHIP_TOPAZ:
	हाल CHIP_TONGA:
		वापस tonga_baco_set_state(hwmgr, state);
	हाल CHIP_FIJI:
		वापस fiji_baco_set_state(hwmgr, state);
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
		वापस polaris_baco_set_state(hwmgr, state);
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
	हाल CHIP_BONAIRE:
	हाल CHIP_HAWAII:
		वापस ci_baco_set_state(hwmgr, state);
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
