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
#समावेश "soc15_common.h"
#समावेश "vega20_inc.h"
#समावेश "vega20_ppsmc.h"
#समावेश "vega20_baco.h"
#समावेश "vega20_smumgr.h"

#समावेश "amdgpu_ras.h"

अटल स्थिर काष्ठा soc15_baco_cmd_entry clean_baco_tbl[] =
अणु
	अणुCMD_WRITE, SOC15_REG_ENTRY(NBIF, 0, mmBIOS_SCRATCH_6), 0, 0, 0, 0पूर्ण,
	अणुCMD_WRITE, SOC15_REG_ENTRY(NBIF, 0, mmBIOS_SCRATCH_7), 0, 0, 0, 0पूर्ण,
पूर्ण;

पूर्णांक vega20_baco_get_capability(काष्ठा pp_hwmgr *hwmgr, bool *cap)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	uपूर्णांक32_t reg;

	*cap = false;
	अगर (!phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_BACO))
		वापस 0;

	अगर (((RREG32(0x17569) & 0x20000000) >> 29) == 0x1) अणु
		reg = RREG32_SOC15(NBIF, 0, mmRCC_BIF_STRAP0);

		अगर (reg & RCC_BIF_STRAP0__STRAP_PX_CAPABLE_MASK)
			*cap = true;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vega20_baco_get_state(काष्ठा pp_hwmgr *hwmgr, क्रमागत BACO_STATE *state)
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

पूर्णांक vega20_baco_set_state(काष्ठा pp_hwmgr *hwmgr, क्रमागत BACO_STATE state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	काष्ठा amdgpu_ras *ras = amdgpu_ras_get_context(adev);
	क्रमागत BACO_STATE cur_state;
	uपूर्णांक32_t data;

	vega20_baco_get_state(hwmgr, &cur_state);

	अगर (cur_state == state)
		/* aisc alपढ़ोy in the target state */
		वापस 0;

	अगर (state == BACO_STATE_IN) अणु
		अगर (!ras || !ras->supported) अणु
			data = RREG32_SOC15(THM, 0, mmTHM_BACO_CNTL);
			data |= 0x80000000;
			WREG32_SOC15(THM, 0, mmTHM_BACO_CNTL, data);

			अगर(smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_EnterBaco, 0, शून्य))
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर(smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_EnterBaco, 1, शून्य))
				वापस -EINVAL;
		पूर्ण

	पूर्ण अन्यथा अगर (state == BACO_STATE_OUT) अणु
		अगर (smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ExitBaco, शून्य))
			वापस -EINVAL;
		अगर (!soc15_baco_program_रेजिस्टरs(hwmgr, clean_baco_tbl,
						     ARRAY_SIZE(clean_baco_tbl)))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vega20_baco_apply_vdci_flush_workaround(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret = 0;

	ret = vega20_set_pptable_driver_address(hwmgr);
	अगर (ret)
		वापस ret;

	वापस smum_send_msg_to_smc(hwmgr, PPSMC_MSG_BacoWorkAroundFlushVDCI, शून्य);
पूर्ण
