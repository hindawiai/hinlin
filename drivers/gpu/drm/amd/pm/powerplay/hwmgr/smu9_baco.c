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
#समावेश "amdgpu.h"
#समावेश "soc15.h"
#समावेश "soc15_hw_ip.h"
#समावेश "vega10_ip_offset.h"
#समावेश "soc15_common.h"
#समावेश "vega10_inc.h"
#समावेश "smu9_baco.h"

पूर्णांक smu9_baco_get_capability(काष्ठा pp_hwmgr *hwmgr, bool *cap)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	uपूर्णांक32_t reg, data;

	*cap = false;
	अगर (!phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_BACO))
		वापस 0;

	WREG32(0x12074, 0xFFF0003B);
	data = RREG32(0x12075);

	अगर (data == 0x1) अणु
		reg = RREG32_SOC15(NBIF, 0, mmRCC_BIF_STRAP0);

		अगर (reg & RCC_BIF_STRAP0__STRAP_PX_CAPABLE_MASK)
			*cap = true;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक smu9_baco_get_state(काष्ठा pp_hwmgr *hwmgr, क्रमागत BACO_STATE *state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	uपूर्णांक32_t reg;

	reg = RREG32_SOC15(NBIF, 0, mmBACO_CNTL);

	अगर (reg & BACO_CNTL__BACO_MODE_MASK)
		/* gfx has alपढ़ोy entered BACO state */
		*state = BACO_STATE_IN;
	अन्यथा
		*state = BACO_STATE_OUT;
	वापस 0;
पूर्ण
