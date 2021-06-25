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

#समावेश "hwmgr.h"
#समावेश "vega20_hwmgr.h"
#समावेश "vega20_powertune.h"
#समावेश "vega20_smumgr.h"
#समावेश "vega20_ppsmc.h"
#समावेश "vega20_inc.h"
#समावेश "pp_debug.h"

पूर्णांक vega20_set_घातer_limit(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t n)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);

	अगर (data->smu_features[GNLD_PPT].enabled)
		वापस smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetPptLimit, n,
				शून्य);

	वापस 0;
पूर्ण

पूर्णांक vega20_validate_घातer_level_request(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t tdp_percentage_adjusपंचांगent, uपूर्णांक32_t tdp_असलolute_value_adjusपंचांगent)
अणु
	वापस (tdp_percentage_adjusपंचांगent > hwmgr->platक्रमm_descriptor.TDPLimit) ? -1 : 0;
पूर्ण

अटल पूर्णांक vega20_set_overdrive_target_percentage(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t adjust_percent)
अणु
	वापस smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_OverDriveSetPercentage, adjust_percent,
			शून्य);
पूर्ण

पूर्णांक vega20_घातer_control_set_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक adjust_percent, result = 0;

	अगर (PP_CAP(PHM_Platक्रमmCaps_PowerContainment)) अणु
		adjust_percent =
				hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगentPolarity ?
				hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगent :
				(-1 * hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगent);
		result = vega20_set_overdrive_target_percentage(hwmgr,
				(uपूर्णांक32_t)adjust_percent);
	पूर्ण
	वापस result;
पूर्ण
