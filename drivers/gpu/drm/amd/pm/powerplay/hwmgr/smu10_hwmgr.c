<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
#समावेश "pp_debug.h"
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश "atom-types.h"
#समावेश "atombios.h"
#समावेश "processpptables.h"
#समावेश "cgs_common.h"
#समावेश "smumgr.h"
#समावेश "hwmgr.h"
#समावेश "hardwaremanager.h"
#समावेश "rv_ppsmc.h"
#समावेश "smu10_hwmgr.h"
#समावेश "power_state.h"
#समावेश "soc15_common.h"
#समावेश "smu10.h"
#समावेश "asic_reg/pwr/pwr_10_0_offset.h"
#समावेश "asic_reg/pwr/pwr_10_0_sh_mask.h"

#घोषणा SMU10_MAX_DEEPSLEEP_DIVIDER_ID     5
#घोषणा SMU10_MINIMUM_ENGINE_CLOCK         800   /* 8Mhz, the low boundary of engine घड़ी allowed on this chip */
#घोषणा SCLK_MIN_DIV_INTV_SHIFT         12
#घोषणा SMU10_DISPCLK_BYPASS_THRESHOLD     10000 /* 100Mhz */
#घोषणा SMC_RAM_END                     0x40000

अटल स्थिर अचिन्हित दीर्घ SMU10_Magic = (अचिन्हित दीर्घ) PHM_Rv_Magic;


अटल पूर्णांक smu10_display_घड़ी_voltage_request(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_display_घड़ी_request *घड़ी_req)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);
	क्रमागत amd_pp_घड़ी_प्रकारype clk_type = घड़ी_req->घड़ी_प्रकारype;
	uपूर्णांक32_t clk_freq = घड़ी_req->घड़ी_freq_in_khz / 1000;
	PPSMC_Msg        msg;

	चयन (clk_type) अणु
	हाल amd_pp_dcf_घड़ी:
		अगर (clk_freq == smu10_data->dcf_actual_hard_min_freq)
			वापस 0;
		msg =  PPSMC_MSG_SetHardMinDcefclkByFreq;
		smu10_data->dcf_actual_hard_min_freq = clk_freq;
		अवरोध;
	हाल amd_pp_soc_घड़ी:
		 msg = PPSMC_MSG_SetHardMinSocclkByFreq;
		अवरोध;
	हाल amd_pp_f_घड़ी:
		अगर (clk_freq == smu10_data->f_actual_hard_min_freq)
			वापस 0;
		smu10_data->f_actual_hard_min_freq = clk_freq;
		msg = PPSMC_MSG_SetHardMinFclkByFreq;
		अवरोध;
	शेष:
		pr_info("[DisplayClockVoltageRequest]Invalid Clock Type!");
		वापस -EINVAL;
	पूर्ण
	smum_send_msg_to_smc_with_parameter(hwmgr, msg, clk_freq, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा smu10_घातer_state *cast_smu10_ps(काष्ठा pp_hw_घातer_state *hw_ps)
अणु
	अगर (SMU10_Magic != hw_ps->magic)
		वापस शून्य;

	वापस (काष्ठा smu10_घातer_state *)hw_ps;
पूर्ण

अटल स्थिर काष्ठा smu10_घातer_state *cast_स्थिर_smu10_ps(
				स्थिर काष्ठा pp_hw_घातer_state *hw_ps)
अणु
	अगर (SMU10_Magic != hw_ps->magic)
		वापस शून्य;

	वापस (काष्ठा smu10_घातer_state *)hw_ps;
पूर्ण

अटल पूर्णांक smu10_initialize_dpm_शेषs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);

	smu10_data->dce_slow_sclk_threshold = 30000;
	smu10_data->thermal_स्वतः_throttling_treshold = 0;
	smu10_data->is_nb_dpm_enabled = 1;
	smu10_data->dpm_flags = 1;
	smu10_data->need_min_deep_sleep_dcefclk = true;
	smu10_data->num_active_display = 0;
	smu10_data->deep_sleep_dcefclk = 0;

	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_SclkDeepSleep);

	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_SclkThrottleLowNotअगरication);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_PowerPlaySupport);
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_स्थिरruct_max_घातer_limits_table(काष्ठा pp_hwmgr *hwmgr,
			काष्ठा phm_घड़ी_and_voltage_limits *table)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_init_dynamic_state_adjusपंचांगent_rule_settings(
							काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक count = 8;
	काष्ठा phm_घड़ी_voltage_dependency_table *table_clk_vlt;

	table_clk_vlt = kzalloc(काष्ठा_size(table_clk_vlt, entries, count),
				GFP_KERNEL);

	अगर (शून्य == table_clk_vlt) अणु
		pr_err("Can not allocate memory!\n");
		वापस -ENOMEM;
	पूर्ण

	table_clk_vlt->count = count;
	table_clk_vlt->entries[0].clk = PP_DAL_POWERLEVEL_0;
	table_clk_vlt->entries[0].v = 0;
	table_clk_vlt->entries[1].clk = PP_DAL_POWERLEVEL_1;
	table_clk_vlt->entries[1].v = 1;
	table_clk_vlt->entries[2].clk = PP_DAL_POWERLEVEL_2;
	table_clk_vlt->entries[2].v = 2;
	table_clk_vlt->entries[3].clk = PP_DAL_POWERLEVEL_3;
	table_clk_vlt->entries[3].v = 3;
	table_clk_vlt->entries[4].clk = PP_DAL_POWERLEVEL_4;
	table_clk_vlt->entries[4].v = 4;
	table_clk_vlt->entries[5].clk = PP_DAL_POWERLEVEL_5;
	table_clk_vlt->entries[5].v = 5;
	table_clk_vlt->entries[6].clk = PP_DAL_POWERLEVEL_6;
	table_clk_vlt->entries[6].v = 6;
	table_clk_vlt->entries[7].clk = PP_DAL_POWERLEVEL_7;
	table_clk_vlt->entries[7].v = 7;
	hwmgr->dyn_state.vddc_dep_on_dal_pwrl = table_clk_vlt;

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_get_प्रणाली_info_data(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)hwmgr->backend;

	smu10_data->sys_info.htc_hyst_lmt = 5;
	smu10_data->sys_info.htc_पंचांगp_lmt = 203;

	अगर (smu10_data->thermal_स्वतः_throttling_treshold == 0)
		 smu10_data->thermal_स्वतः_throttling_treshold = 203;

	smu10_स्थिरruct_max_घातer_limits_table (hwmgr,
				    &hwmgr->dyn_state.max_घड़ी_voltage_on_ac);

	smu10_init_dynamic_state_adjusपंचांगent_rule_settings(hwmgr);

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_स्थिरruct_boot_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_set_घड़ी_limit(काष्ठा pp_hwmgr *hwmgr, स्थिर व्योम *input)
अणु
	काष्ठा PP_Clocks घड़ीs = अणु0पूर्ण;
	काष्ठा pp_display_घड़ी_request घड़ी_req;

	घड़ीs.dcefClock = hwmgr->display_config->min_dcef_set_clk;
	घड़ी_req.घड़ी_प्रकारype = amd_pp_dcf_घड़ी;
	घड़ी_req.घड़ी_freq_in_khz = घड़ीs.dcefClock * 10;

	PP_ASSERT_WITH_CODE(!smu10_display_घड़ी_voltage_request(hwmgr, &घड़ी_req),
				"Attempt to set DCF Clock Failed!", वापस -EINVAL);

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_set_min_deep_sleep_dcefclk(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);

	अगर (घड़ी && smu10_data->deep_sleep_dcefclk != घड़ी) अणु
		smu10_data->deep_sleep_dcefclk = घड़ी;
		smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetMinDeepSleepDcefclk,
					smu10_data->deep_sleep_dcefclk,
					शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_set_hard_min_dcefclk_by_freq(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);

	अगर (घड़ी && smu10_data->dcf_actual_hard_min_freq != घड़ी) अणु
		smu10_data->dcf_actual_hard_min_freq = घड़ी;
		smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetHardMinDcefclkByFreq,
					smu10_data->dcf_actual_hard_min_freq,
					शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_set_hard_min_fclk_by_freq(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);

	अगर (घड़ी && smu10_data->f_actual_hard_min_freq != घड़ी) अणु
		smu10_data->f_actual_hard_min_freq = घड़ी;
		smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetHardMinFclkByFreq,
					smu10_data->f_actual_hard_min_freq,
					शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_set_hard_min_gfxclk_by_freq(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);

	अगर (घड़ी && smu10_data->gfx_actual_soft_min_freq != घड़ी) अणु
		smu10_data->gfx_actual_soft_min_freq = घड़ी;
		smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetHardMinGfxClk,
					घड़ी,
					शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_set_soft_max_gfxclk_by_freq(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);

	अगर (घड़ी && smu10_data->gfx_max_freq_limit != (घड़ी * 100))  अणु
		smu10_data->gfx_max_freq_limit = घड़ी * 100;
		smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetSoftMaxGfxClk,
					घड़ी,
					शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_set_active_display_count(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t count)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);

	अगर (smu10_data->num_active_display != count) अणु
		smu10_data->num_active_display = count;
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetDisplayCount,
				smu10_data->num_active_display,
				शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_set_घातer_state_tasks(काष्ठा pp_hwmgr *hwmgr, स्थिर व्योम *input)
अणु
	वापस smu10_set_घड़ी_limit(hwmgr, input);
पूर्ण

अटल पूर्णांक smu10_init_घातer_gate_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	smu10_data->vcn_घातer_gated = true;
	smu10_data->isp_tileA_घातer_gated = true;
	smu10_data->isp_tileB_घातer_gated = true;

	अगर (adev->pg_flags & AMD_PG_SUPPORT_GFX_PG)
		वापस smum_send_msg_to_smc_with_parameter(hwmgr,
							   PPSMC_MSG_SetGfxCGPG,
							   true,
							   शून्य);
	अन्यथा
		वापस 0;
पूर्ण


अटल पूर्णांक smu10_setup_asic_task(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस smu10_init_घातer_gate_state(hwmgr);
पूर्ण

अटल पूर्णांक smu10_reset_cc6_data(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);

	smu10_data->separation_समय = 0;
	smu10_data->cc6_disable = false;
	smu10_data->pstate_disable = false;
	smu10_data->cc6_setting_changed = false;

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_घातer_off_asic(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस smu10_reset_cc6_data(hwmgr);
पूर्ण

अटल bool smu10_is_gfx_on(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t reg;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	reg = RREG32_SOC15(PWR, 0, mmPWR_MISC_CNTL_STATUS);
	अगर ((reg & PWR_MISC_CNTL_STATUS__PWR_GFXOFF_STATUS_MASK) ==
	    (0x2 << PWR_MISC_CNTL_STATUS__PWR_GFXOFF_STATUS__SHIFT))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक smu10_disable_gfx_off(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	अगर (adev->pm.pp_feature & PP_GFXOFF_MASK) अणु
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_DisableGfxOff, शून्य);

		/* confirm gfx is back to "on" state */
		जबतक (!smu10_is_gfx_on(hwmgr))
			msleep(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_disable_dpm_tasks(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_enable_gfx_off(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	अगर (adev->pm.pp_feature & PP_GFXOFF_MASK)
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_EnableGfxOff, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_enable_dpm_tasks(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_gfx_off_control(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	अगर (enable)
		वापस smu10_enable_gfx_off(hwmgr);
	अन्यथा
		वापस smu10_disable_gfx_off(hwmgr);
पूर्ण

अटल पूर्णांक smu10_apply_state_adjust_rules(काष्ठा pp_hwmgr *hwmgr,
				काष्ठा pp_घातer_state  *prequest_ps,
			स्थिर काष्ठा pp_घातer_state *pcurrent_ps)
अणु
	वापस 0;
पूर्ण

/* temporary hardcoded घड़ी voltage अवरोधकरोwn tables */
अटल स्थिर DpmClock_t VddDcfClk[]= अणु
	अणु 300, 2600पूर्ण,
	अणु 600, 3200पूर्ण,
	अणु 600, 3600पूर्ण,
पूर्ण;

अटल स्थिर DpmClock_t VddSocClk[]= अणु
	अणु 478, 2600पूर्ण,
	अणु 722, 3200पूर्ण,
	अणु 722, 3600पूर्ण,
पूर्ण;

अटल स्थिर DpmClock_t VddFClk[]= अणु
	अणु 400, 2600पूर्ण,
	अणु1200, 3200पूर्ण,
	अणु1200, 3600पूर्ण,
पूर्ण;

अटल स्थिर DpmClock_t VddDispClk[]= अणु
	अणु 435, 2600पूर्ण,
	अणु 661, 3200पूर्ण,
	अणु1086, 3600पूर्ण,
पूर्ण;

अटल स्थिर DpmClock_t VddDppClk[]= अणु
	अणु 435, 2600पूर्ण,
	अणु 661, 3200पूर्ण,
	अणु 661, 3600पूर्ण,
पूर्ण;

अटल स्थिर DpmClock_t VddPhyClk[]= अणु
	अणु 540, 2600पूर्ण,
	अणु 810, 3200पूर्ण,
	अणु 810, 3600पूर्ण,
पूर्ण;

अटल पूर्णांक smu10_get_घड़ी_voltage_dependency_table(काष्ठा pp_hwmgr *hwmgr,
			काष्ठा smu10_voltage_dependency_table **pptable,
			uपूर्णांक32_t num_entry, स्थिर DpmClock_t *pclk_dependency_table)
अणु
	uपूर्णांक32_t i;
	काष्ठा smu10_voltage_dependency_table *ptable;

	ptable = kzalloc(काष्ठा_size(ptable, entries, num_entry), GFP_KERNEL);
	अगर (शून्य == ptable)
		वापस -ENOMEM;

	ptable->count = num_entry;

	क्रम (i = 0; i < ptable->count; i++) अणु
		ptable->entries[i].clk         = pclk_dependency_table->Freq * 100;
		ptable->entries[i].vol         = pclk_dependency_table->Vol;
		pclk_dependency_table++;
	पूर्ण

	*pptable = ptable;

	वापस 0;
पूर्ण


अटल पूर्णांक smu10_populate_घड़ी_प्रकारable(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t result;

	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);
	DpmClocks_t  *table = &(smu10_data->घड़ी_प्रकारable);
	काष्ठा smu10_घड़ी_voltage_inक्रमmation *pinfo = &(smu10_data->घड़ी_vol_info);

	result = smum_smc_table_manager(hwmgr, (uपूर्णांक8_t *)table, SMU10_CLOCKTABLE, true);

	PP_ASSERT_WITH_CODE((0 == result),
			"Attempt to copy clock table from smc failed",
			वापस result);

	अगर (0 == result && table->DcefClocks[0].Freq != 0) अणु
		smu10_get_घड़ी_voltage_dependency_table(hwmgr, &pinfo->vdd_dep_on_dcefclk,
						NUM_DCEFCLK_DPM_LEVELS,
						&smu10_data->घड़ी_प्रकारable.DcefClocks[0]);
		smu10_get_घड़ी_voltage_dependency_table(hwmgr, &pinfo->vdd_dep_on_socclk,
						NUM_SOCCLK_DPM_LEVELS,
						&smu10_data->घड़ी_प्रकारable.SocClocks[0]);
		smu10_get_घड़ी_voltage_dependency_table(hwmgr, &pinfo->vdd_dep_on_fclk,
						NUM_FCLK_DPM_LEVELS,
						&smu10_data->घड़ी_प्रकारable.FClocks[0]);
		smu10_get_घड़ी_voltage_dependency_table(hwmgr, &pinfo->vdd_dep_on_mclk,
						NUM_MEMCLK_DPM_LEVELS,
						&smu10_data->घड़ी_प्रकारable.MemClocks[0]);
	पूर्ण अन्यथा अणु
		smu10_get_घड़ी_voltage_dependency_table(hwmgr, &pinfo->vdd_dep_on_dcefclk,
						ARRAY_SIZE(VddDcfClk),
						&VddDcfClk[0]);
		smu10_get_घड़ी_voltage_dependency_table(hwmgr, &pinfo->vdd_dep_on_socclk,
						ARRAY_SIZE(VddSocClk),
						&VddSocClk[0]);
		smu10_get_घड़ी_voltage_dependency_table(hwmgr, &pinfo->vdd_dep_on_fclk,
						ARRAY_SIZE(VddFClk),
						&VddFClk[0]);
	पूर्ण
	smu10_get_घड़ी_voltage_dependency_table(hwmgr, &pinfo->vdd_dep_on_dispclk,
					ARRAY_SIZE(VddDispClk),
					&VddDispClk[0]);
	smu10_get_घड़ी_voltage_dependency_table(hwmgr, &pinfo->vdd_dep_on_dppclk,
					ARRAY_SIZE(VddDppClk), &VddDppClk[0]);
	smu10_get_घड़ी_voltage_dependency_table(hwmgr, &pinfo->vdd_dep_on_phyclk,
					ARRAY_SIZE(VddPhyClk), &VddPhyClk[0]);

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMinGfxclkFrequency, &result);
	smu10_data->gfx_min_freq_limit = result / 10 * 1000;

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxGfxclkFrequency, &result);
	smu10_data->gfx_max_freq_limit = result / 10 * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_hwmgr_backend_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	काष्ठा smu10_hwmgr *data;

	data = kzalloc(माप(काष्ठा smu10_hwmgr), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	hwmgr->backend = data;

	result = smu10_initialize_dpm_शेषs(hwmgr);
	अगर (result != 0) अणु
		pr_err("smu10_initialize_dpm_defaults failed\n");
		वापस result;
	पूर्ण

	smu10_populate_घड़ी_प्रकारable(hwmgr);

	result = smu10_get_प्रणाली_info_data(hwmgr);
	अगर (result != 0) अणु
		pr_err("smu10_get_system_info_data failed\n");
		वापस result;
	पूर्ण

	smu10_स्थिरruct_boot_state(hwmgr);

	hwmgr->platक्रमm_descriptor.hardwareActivityPerक्रमmanceLevels =
						SMU10_MAX_HARDWARE_POWERLEVELS;

	hwmgr->platक्रमm_descriptor.hardwarePerक्रमmanceLevels =
						SMU10_MAX_HARDWARE_POWERLEVELS;

	hwmgr->platक्रमm_descriptor.vbiosInterruptId = 0;

	hwmgr->platक्रमm_descriptor.घड़ीStep.engineClock = 500;

	hwmgr->platक्रमm_descriptor.घड़ीStep.memoryClock = 500;

	hwmgr->platक्रमm_descriptor.minimumClocksReductionPercentage = 50;

	hwmgr->pstate_sclk = SMU10_UMD_PSTATE_GFXCLK * 100;
	hwmgr->pstate_mclk = SMU10_UMD_PSTATE_FCLK * 100;

	/* enable the pp_od_clk_voltage sysfs file */
	hwmgr->od_enabled = 1;
	/* disabled fine grain tuning function by शेष */
	data->fine_grain_enabled = 0;
	वापस result;
पूर्ण

अटल पूर्णांक smu10_hwmgr_backend_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);
	काष्ठा smu10_घड़ी_voltage_inक्रमmation *pinfo = &(smu10_data->घड़ी_vol_info);

	kमुक्त(pinfo->vdd_dep_on_dcefclk);
	pinfo->vdd_dep_on_dcefclk = शून्य;
	kमुक्त(pinfo->vdd_dep_on_socclk);
	pinfo->vdd_dep_on_socclk = शून्य;
	kमुक्त(pinfo->vdd_dep_on_fclk);
	pinfo->vdd_dep_on_fclk = शून्य;
	kमुक्त(pinfo->vdd_dep_on_dispclk);
	pinfo->vdd_dep_on_dispclk = शून्य;
	kमुक्त(pinfo->vdd_dep_on_dppclk);
	pinfo->vdd_dep_on_dppclk = शून्य;
	kमुक्त(pinfo->vdd_dep_on_phyclk);
	pinfo->vdd_dep_on_phyclk = शून्य;

	kमुक्त(hwmgr->dyn_state.vddc_dep_on_dal_pwrl);
	hwmgr->dyn_state.vddc_dep_on_dal_pwrl = शून्य;

	kमुक्त(hwmgr->backend);
	hwmgr->backend = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_dpm_क्रमce_dpm_level(काष्ठा pp_hwmgr *hwmgr,
				क्रमागत amd_dpm_क्रमced_level level)
अणु
	काष्ठा smu10_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t min_sclk = hwmgr->display_config->min_core_set_घड़ी;
	uपूर्णांक32_t min_mclk = hwmgr->display_config->min_mem_set_घड़ी/100;
	uपूर्णांक32_t index_fclk = data->घड़ी_vol_info.vdd_dep_on_fclk->count - 1;
	uपूर्णांक32_t index_socclk = data->घड़ी_vol_info.vdd_dep_on_socclk->count - 1;
	uपूर्णांक32_t fine_grain_min_freq = 0, fine_grain_max_freq = 0;

	अगर (hwmgr->smu_version < 0x1E3700) अणु
		pr_info("smu firmware version too old, can not set dpm level\n");
		वापस 0;
	पूर्ण

	अगर (min_sclk < data->gfx_min_freq_limit)
		min_sclk = data->gfx_min_freq_limit;

	min_sclk /= 100; /* transfer 10KHz to MHz */
	अगर (min_mclk < data->घड़ी_प्रकारable.FClocks[0].Freq)
		min_mclk = data->घड़ी_प्रकारable.FClocks[0].Freq;

	चयन (level) अणु
	हाल AMD_DPM_FORCED_LEVEL_HIGH:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_PEAK:
		data->fine_grain_enabled = 0;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMinGfxclkFrequency, &fine_grain_min_freq);
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxGfxclkFrequency, &fine_grain_max_freq);

		data->gfx_actual_soft_min_freq = fine_grain_min_freq;
		data->gfx_actual_soft_max_freq = fine_grain_max_freq;

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinGfxClk,
						data->gfx_max_freq_limit/100,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinFclkByFreq,
						SMU10_UMD_PSTATE_PEAK_FCLK,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinSocclkByFreq,
						SMU10_UMD_PSTATE_PEAK_SOCCLK,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinVcn,
						SMU10_UMD_PSTATE_VCE,
						शून्य);

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxGfxClk,
						data->gfx_max_freq_limit/100,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxFclkByFreq,
						SMU10_UMD_PSTATE_PEAK_FCLK,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxSocclkByFreq,
						SMU10_UMD_PSTATE_PEAK_SOCCLK,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxVcn,
						SMU10_UMD_PSTATE_VCE,
						शून्य);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK:
		data->fine_grain_enabled = 0;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMinGfxclkFrequency, &fine_grain_min_freq);
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxGfxclkFrequency, &fine_grain_max_freq);

		data->gfx_actual_soft_min_freq = fine_grain_min_freq;
		data->gfx_actual_soft_max_freq = fine_grain_max_freq;

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinGfxClk,
						min_sclk,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxGfxClk,
						min_sclk,
						शून्य);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK:
		data->fine_grain_enabled = 0;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMinGfxclkFrequency, &fine_grain_min_freq);
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxGfxclkFrequency, &fine_grain_max_freq);

		data->gfx_actual_soft_min_freq = fine_grain_min_freq;
		data->gfx_actual_soft_max_freq = fine_grain_max_freq;

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinFclkByFreq,
						min_mclk,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxFclkByFreq,
						min_mclk,
						शून्य);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD:
		data->fine_grain_enabled = 0;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMinGfxclkFrequency, &fine_grain_min_freq);
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxGfxclkFrequency, &fine_grain_max_freq);

		data->gfx_actual_soft_min_freq = fine_grain_min_freq;
		data->gfx_actual_soft_max_freq = fine_grain_max_freq;

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinGfxClk,
						SMU10_UMD_PSTATE_GFXCLK,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinFclkByFreq,
						SMU10_UMD_PSTATE_FCLK,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinSocclkByFreq,
						SMU10_UMD_PSTATE_SOCCLK,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinVcn,
						SMU10_UMD_PSTATE_PROखाता_VCE,
						शून्य);

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxGfxClk,
						SMU10_UMD_PSTATE_GFXCLK,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxFclkByFreq,
						SMU10_UMD_PSTATE_FCLK,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxSocclkByFreq,
						SMU10_UMD_PSTATE_SOCCLK,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxVcn,
						SMU10_UMD_PSTATE_PROखाता_VCE,
						शून्य);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_AUTO:
		data->fine_grain_enabled = 0;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMinGfxclkFrequency, &fine_grain_min_freq);
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxGfxclkFrequency, &fine_grain_max_freq);

		data->gfx_actual_soft_min_freq = fine_grain_min_freq;
		data->gfx_actual_soft_max_freq = fine_grain_max_freq;

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinGfxClk,
						min_sclk,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinFclkByFreq,
						hwmgr->display_config->num_display > 3 ?
						data->घड़ी_vol_info.vdd_dep_on_fclk->entries[0].clk :
						min_mclk,
						शून्य);

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinSocclkByFreq,
						data->घड़ी_vol_info.vdd_dep_on_socclk->entries[0].clk,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinVcn,
						SMU10_UMD_PSTATE_MIN_VCE,
						शून्य);

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxGfxClk,
						data->gfx_max_freq_limit/100,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxFclkByFreq,
						data->घड़ी_vol_info.vdd_dep_on_fclk->entries[index_fclk].clk,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxSocclkByFreq,
						data->घड़ी_vol_info.vdd_dep_on_socclk->entries[index_socclk].clk,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxVcn,
						SMU10_UMD_PSTATE_VCE,
						शून्य);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_LOW:
		data->fine_grain_enabled = 0;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMinGfxclkFrequency, &fine_grain_min_freq);
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxGfxclkFrequency, &fine_grain_max_freq);

		data->gfx_actual_soft_min_freq = fine_grain_min_freq;
		data->gfx_actual_soft_max_freq = fine_grain_max_freq;

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinGfxClk,
						data->gfx_min_freq_limit/100,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxGfxClk,
						data->gfx_min_freq_limit/100,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinFclkByFreq,
						min_mclk,
						शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxFclkByFreq,
						min_mclk,
						शून्य);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_MANUAL:
		data->fine_grain_enabled = 1;
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_EXIT:
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल uपूर्णांक32_t smu10_dpm_get_mclk(काष्ठा pp_hwmgr *hwmgr, bool low)
अणु
	काष्ठा smu10_hwmgr *data;

	अगर (hwmgr == शून्य)
		वापस -EINVAL;

	data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);

	अगर (low)
		वापस data->घड़ी_vol_info.vdd_dep_on_fclk->entries[0].clk;
	अन्यथा
		वापस data->घड़ी_vol_info.vdd_dep_on_fclk->entries[
			data->घड़ी_vol_info.vdd_dep_on_fclk->count - 1].clk;
पूर्ण

अटल uपूर्णांक32_t smu10_dpm_get_sclk(काष्ठा pp_hwmgr *hwmgr, bool low)
अणु
	काष्ठा smu10_hwmgr *data;

	अगर (hwmgr == शून्य)
		वापस -EINVAL;

	data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);

	अगर (low)
		वापस data->gfx_min_freq_limit;
	अन्यथा
		वापस data->gfx_max_freq_limit;
पूर्ण

अटल पूर्णांक smu10_dpm_patch_boot_state(काष्ठा pp_hwmgr *hwmgr,
					काष्ठा pp_hw_घातer_state *hw_ps)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_dpm_get_pp_table_entry_callback(
						     काष्ठा pp_hwmgr *hwmgr,
					   काष्ठा pp_hw_घातer_state *hw_ps,
							  अचिन्हित पूर्णांक index,
						     स्थिर व्योम *घड़ी_info)
अणु
	काष्ठा smu10_घातer_state *smu10_ps = cast_smu10_ps(hw_ps);

	smu10_ps->levels[index].engine_घड़ी = 0;

	smu10_ps->levels[index].vddc_index = 0;
	smu10_ps->level = index + 1;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_SclkDeepSleep)) अणु
		smu10_ps->levels[index].ds_भागider_index = 5;
		smu10_ps->levels[index].ss_भागider_index = 5;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_dpm_get_num_of_pp_table_entries(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ ret = 0;

	result = pp_tables_get_num_of_entries(hwmgr, &ret);

	वापस result ? 0 : ret;
पूर्ण

अटल पूर्णांक smu10_dpm_get_pp_table_entry(काष्ठा pp_hwmgr *hwmgr,
		    अचिन्हित दीर्घ entry, काष्ठा pp_घातer_state *ps)
अणु
	पूर्णांक result;
	काष्ठा smu10_घातer_state *smu10_ps;

	ps->hardware.magic = SMU10_Magic;

	smu10_ps = cast_smu10_ps(&(ps->hardware));

	result = pp_tables_get_entry(hwmgr, entry, ps,
			smu10_dpm_get_pp_table_entry_callback);

	smu10_ps->uvd_घड़ीs.vclk = ps->uvd_घड़ीs.VCLK;
	smu10_ps->uvd_घड़ीs.dclk = ps->uvd_घड़ीs.DCLK;

	वापस result;
पूर्ण

अटल पूर्णांक smu10_get_घातer_state_size(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस माप(काष्ठा smu10_घातer_state);
पूर्ण

अटल पूर्णांक smu10_set_cpu_घातer_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस 0;
पूर्ण


अटल पूर्णांक smu10_store_cc6_data(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t separation_समय,
			bool cc6_disable, bool pstate_disable, bool pstate_चयन_disable)
अणु
	काष्ठा smu10_hwmgr *data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);

	अगर (separation_समय != data->separation_समय ||
			cc6_disable != data->cc6_disable ||
			pstate_disable != data->pstate_disable) अणु
		data->separation_समय = separation_समय;
		data->cc6_disable = cc6_disable;
		data->pstate_disable = pstate_disable;
		data->cc6_setting_changed = true;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_get_dal_घातer_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा amd_pp_simple_घड़ी_info *info)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक smu10_क्रमce_घड़ी_level(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, uपूर्णांक32_t mask)
अणु
	काष्ठा smu10_hwmgr *data = hwmgr->backend;
	काष्ठा smu10_voltage_dependency_table *mclk_table =
					data->घड़ी_vol_info.vdd_dep_on_fclk;
	uपूर्णांक32_t low, high;

	low = mask ? (ffs(mask) - 1) : 0;
	high = mask ? (fls(mask) - 1) : 0;

	चयन (type) अणु
	हाल PP_SCLK:
		अगर (low > 2 || high > 2) अणु
			pr_info("Currently sclk only support 3 levels on RV\n");
			वापस -EINVAL;
		पूर्ण

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinGfxClk,
						low == 2 ? data->gfx_max_freq_limit/100 :
						low == 1 ? SMU10_UMD_PSTATE_GFXCLK :
						data->gfx_min_freq_limit/100,
						शून्य);

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxGfxClk,
						high == 0 ? data->gfx_min_freq_limit/100 :
						high == 1 ? SMU10_UMD_PSTATE_GFXCLK :
						data->gfx_max_freq_limit/100,
						शून्य);
		अवरोध;

	हाल PP_MCLK:
		अगर (low > mclk_table->count - 1 || high > mclk_table->count - 1)
			वापस -EINVAL;

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinFclkByFreq,
						mclk_table->entries[low].clk/100,
						शून्य);

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxFclkByFreq,
						mclk_table->entries[high].clk/100,
						शून्य);
		अवरोध;

	हाल PP_PCIE:
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_prपूर्णांक_घड़ी_levels(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, अक्षर *buf)
अणु
	काष्ठा smu10_hwmgr *data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);
	काष्ठा smu10_voltage_dependency_table *mclk_table =
			data->घड़ी_vol_info.vdd_dep_on_fclk;
	uपूर्णांक32_t i, now, size = 0;
	uपूर्णांक32_t min_freq, max_freq = 0;
	uपूर्णांक32_t ret = 0;

	चयन (type) अणु
	हाल PP_SCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetGfxclkFrequency, &now);

	/* driver only know min/max gfx_clk, Add level 1 क्रम all other gfx clks */
		अगर (now == data->gfx_max_freq_limit/100)
			i = 2;
		अन्यथा अगर (now == data->gfx_min_freq_limit/100)
			i = 0;
		अन्यथा
			i = 1;

		size += प्र_लिखो(buf + size, "0: %uMhz %s\n",
					data->gfx_min_freq_limit/100,
					i == 0 ? "*" : "");
		size += प्र_लिखो(buf + size, "1: %uMhz %s\n",
					i == 1 ? now : SMU10_UMD_PSTATE_GFXCLK,
					i == 1 ? "*" : "");
		size += प्र_लिखो(buf + size, "2: %uMhz %s\n",
					data->gfx_max_freq_limit/100,
					i == 2 ? "*" : "");
		अवरोध;
	हाल PP_MCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetFclkFrequency, &now);

		क्रम (i = 0; i < mclk_table->count; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
					i,
					mclk_table->entries[i].clk / 100,
					((mclk_table->entries[i].clk / 100)
					 == now) ? "*" : "");
		अवरोध;
	हाल OD_SCLK:
		अगर (hwmgr->od_enabled) अणु
			ret = smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMinGfxclkFrequency, &min_freq);
			अगर (ret)
				वापस ret;
			ret = smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxGfxclkFrequency, &max_freq);
			अगर (ret)
				वापस ret;

			size = प्र_लिखो(buf, "%s:\n", "OD_SCLK");
			size += प्र_लिखो(buf + size, "0: %10uMhz\n",
			(data->gfx_actual_soft_min_freq > 0) ? data->gfx_actual_soft_min_freq : min_freq);
			size += प्र_लिखो(buf + size, "1: %10uMhz\n",
			(data->gfx_actual_soft_max_freq > 0) ? data->gfx_actual_soft_max_freq : max_freq);
		पूर्ण
		अवरोध;
	हाल OD_RANGE:
		अगर (hwmgr->od_enabled) अणु
			ret = smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMinGfxclkFrequency, &min_freq);
			अगर (ret)
				वापस ret;
			ret = smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxGfxclkFrequency, &max_freq);
			अगर (ret)
				वापस ret;

			size = प्र_लिखो(buf, "%s:\n", "OD_RANGE");
			size += प्र_लिखो(buf + size, "SCLK: %7uMHz %10uMHz\n",
				min_freq, max_freq);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक smu10_get_perक्रमmance_level(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा pp_hw_घातer_state *state,
				PHM_Perक्रमmanceLevelDesignation designation, uपूर्णांक32_t index,
				PHM_Perक्रमmanceLevel *level)
अणु
	काष्ठा smu10_hwmgr *data;

	अगर (level == शून्य || hwmgr == शून्य || state == शून्य)
		वापस -EINVAL;

	data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);

	अगर (index == 0) अणु
		level->memory_घड़ी = data->घड़ी_vol_info.vdd_dep_on_fclk->entries[0].clk;
		level->coreClock = data->gfx_min_freq_limit;
	पूर्ण अन्यथा अणु
		level->memory_घड़ी = data->घड़ी_vol_info.vdd_dep_on_fclk->entries[
			data->घड़ी_vol_info.vdd_dep_on_fclk->count - 1].clk;
		level->coreClock = data->gfx_max_freq_limit;
	पूर्ण

	level->nonLocalMemoryFreq = 0;
	level->nonLocalMemoryWidth = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_get_current_shallow_sleep_घड़ीs(काष्ठा pp_hwmgr *hwmgr,
	स्थिर काष्ठा pp_hw_घातer_state *state, काष्ठा pp_घड़ी_info *घड़ी_info)
अणु
	स्थिर काष्ठा smu10_घातer_state *ps = cast_स्थिर_smu10_ps(state);

	घड़ी_info->min_eng_clk = ps->levels[0].engine_घड़ी / (1 << (ps->levels[0].ss_भागider_index));
	घड़ी_info->max_eng_clk = ps->levels[ps->level - 1].engine_घड़ी / (1 << (ps->levels[ps->level - 1].ss_भागider_index));

	वापस 0;
पूर्ण

#घोषणा MEM_FREQ_LOW_LATENCY        25000
#घोषणा MEM_FREQ_HIGH_LATENCY       80000
#घोषणा MEM_LATENCY_HIGH            245
#घोषणा MEM_LATENCY_LOW             35
#घोषणा MEM_LATENCY_ERR             0xFFFF


अटल uपूर्णांक32_t smu10_get_mem_latency(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी)
अणु
	अगर (घड़ी >= MEM_FREQ_LOW_LATENCY &&
			घड़ी < MEM_FREQ_HIGH_LATENCY)
		वापस MEM_LATENCY_HIGH;
	अन्यथा अगर (घड़ी >= MEM_FREQ_HIGH_LATENCY)
		वापस MEM_LATENCY_LOW;
	अन्यथा
		वापस MEM_LATENCY_ERR;
पूर्ण

अटल पूर्णांक smu10_get_घड़ी_by_type_with_latency(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	uपूर्णांक32_t i;
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);
	काष्ठा smu10_घड़ी_voltage_inक्रमmation *pinfo = &(smu10_data->घड़ी_vol_info);
	काष्ठा smu10_voltage_dependency_table *pclk_vol_table;
	bool latency_required = false;

	अगर (pinfo == शून्य)
		वापस -EINVAL;

	चयन (type) अणु
	हाल amd_pp_mem_घड़ी:
		pclk_vol_table = pinfo->vdd_dep_on_mclk;
		latency_required = true;
		अवरोध;
	हाल amd_pp_f_घड़ी:
		pclk_vol_table = pinfo->vdd_dep_on_fclk;
		latency_required = true;
		अवरोध;
	हाल amd_pp_dcf_घड़ी:
		pclk_vol_table = pinfo->vdd_dep_on_dcefclk;
		अवरोध;
	हाल amd_pp_disp_घड़ी:
		pclk_vol_table = pinfo->vdd_dep_on_dispclk;
		अवरोध;
	हाल amd_pp_phy_घड़ी:
		pclk_vol_table = pinfo->vdd_dep_on_phyclk;
		अवरोध;
	हाल amd_pp_dpp_घड़ी:
		pclk_vol_table = pinfo->vdd_dep_on_dppclk;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (pclk_vol_table == शून्य || pclk_vol_table->count == 0)
		वापस -EINVAL;

	घड़ीs->num_levels = 0;
	क्रम (i = 0; i < pclk_vol_table->count; i++) अणु
		अगर (pclk_vol_table->entries[i].clk) अणु
			घड़ीs->data[घड़ीs->num_levels].घड़ीs_in_khz =
				pclk_vol_table->entries[i].clk * 10;
			घड़ीs->data[घड़ीs->num_levels].latency_in_us = latency_required ?
				smu10_get_mem_latency(hwmgr,
						      pclk_vol_table->entries[i].clk) :
				0;
			घड़ीs->num_levels++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_get_घड़ी_by_type_with_voltage(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_voltage *घड़ीs)
अणु
	uपूर्णांक32_t i;
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);
	काष्ठा smu10_घड़ी_voltage_inक्रमmation *pinfo = &(smu10_data->घड़ी_vol_info);
	काष्ठा smu10_voltage_dependency_table *pclk_vol_table = शून्य;

	अगर (pinfo == शून्य)
		वापस -EINVAL;

	चयन (type) अणु
	हाल amd_pp_mem_घड़ी:
		pclk_vol_table = pinfo->vdd_dep_on_mclk;
		अवरोध;
	हाल amd_pp_f_घड़ी:
		pclk_vol_table = pinfo->vdd_dep_on_fclk;
		अवरोध;
	हाल amd_pp_dcf_घड़ी:
		pclk_vol_table = pinfo->vdd_dep_on_dcefclk;
		अवरोध;
	हाल amd_pp_soc_घड़ी:
		pclk_vol_table = pinfo->vdd_dep_on_socclk;
		अवरोध;
	हाल amd_pp_disp_घड़ी:
		pclk_vol_table = pinfo->vdd_dep_on_dispclk;
		अवरोध;
	हाल amd_pp_phy_घड़ी:
		pclk_vol_table = pinfo->vdd_dep_on_phyclk;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (pclk_vol_table == शून्य || pclk_vol_table->count == 0)
		वापस -EINVAL;

	घड़ीs->num_levels = 0;
	क्रम (i = 0; i < pclk_vol_table->count; i++) अणु
		अगर (pclk_vol_table->entries[i].clk) अणु
			घड़ीs->data[घड़ीs->num_levels].घड़ीs_in_khz = pclk_vol_table->entries[i].clk  * 10;
			घड़ीs->data[घड़ीs->num_levels].voltage_in_mv = pclk_vol_table->entries[i].vol;
			घड़ीs->num_levels++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण



अटल पूर्णांक smu10_get_max_high_घड़ीs(काष्ठा pp_hwmgr *hwmgr, काष्ठा amd_pp_simple_घड़ी_info *घड़ीs)
अणु
	घड़ीs->engine_max_घड़ी = 80000; /* driver can't get engine घड़ी, temp hard code to 800MHz */
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_thermal_get_temperature(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t reg_value = RREG32_SOC15(THM, 0, mmTHM_TCON_CUR_TMP);
	पूर्णांक cur_temp =
		(reg_value & THM_TCON_CUR_TMP__CUR_TEMP_MASK) >> THM_TCON_CUR_TMP__CUR_TEMP__SHIFT;

	अगर (cur_temp & THM_TCON_CUR_TMP__CUR_TEMP_RANGE_SEL_MASK)
		cur_temp = ((cur_temp / 8) - 49) * PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	अन्यथा
		cur_temp = (cur_temp / 8) * PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	वापस cur_temp;
पूर्ण

अटल पूर्णांक smu10_पढ़ो_sensor(काष्ठा pp_hwmgr *hwmgr, पूर्णांक idx,
			  व्योम *value, पूर्णांक *size)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t sclk, mclk, activity_percent;
	bool has_gfx_busy;
	पूर्णांक ret = 0;

	/* GetGfxBusy support was added on RV SMU FW 30.85.00 and PCO 4.30.59 */
	अगर ((adev->apu_flags & AMD_APU_IS_PICASSO) &&
	    (hwmgr->smu_version >= 0x41e3b))
		has_gfx_busy = true;
	अन्यथा अगर ((adev->apu_flags & AMD_APU_IS_RAVEN) &&
		 (hwmgr->smu_version >= 0x1e5500))
		has_gfx_busy = true;
	अन्यथा
		has_gfx_busy = false;

	चयन (idx) अणु
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetGfxclkFrequency, &sclk);
			/* in units of 10KHZ */
		*((uपूर्णांक32_t *)value) = sclk * 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_MCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetFclkFrequency, &mclk);
			/* in units of 10KHZ */
		*((uपूर्णांक32_t *)value) = mclk * 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_TEMP:
		*((uपूर्णांक32_t *)value) = smu10_thermal_get_temperature(hwmgr);
		अवरोध;
	हाल AMDGPU_PP_SENSOR_VCN_POWER_STATE:
		*(uपूर्णांक32_t *)value =  smu10_data->vcn_घातer_gated ? 0 : 1;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
		अगर (!has_gfx_busy)
			ret = -EOPNOTSUPP;
		अन्यथा अणु
			ret = smum_send_msg_to_smc(hwmgr,
						   PPSMC_MSG_GetGfxBusy,
						   &activity_percent);
			अगर (!ret)
				*((uपूर्णांक32_t *)value) = min(activity_percent, (u32)100);
			अन्यथा
				ret = -EIO;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smu10_set_watermarks_क्रम_घड़ीs_ranges(काष्ठा pp_hwmgr *hwmgr,
		व्योम *घड़ी_ranges)
अणु
	काष्ठा smu10_hwmgr *data = hwmgr->backend;
	काष्ठा dm_pp_wm_sets_with_घड़ी_ranges_soc15 *wm_with_घड़ी_ranges = घड़ी_ranges;
	Watermarks_t *table = &(data->water_marks_table);
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक i;

	smu_set_watermarks_क्रम_घड़ीs_ranges(table,wm_with_घड़ी_ranges);

	अगर (adev->apu_flags & AMD_APU_IS_RAVEN2) अणु
		क्रम (i = 0; i < NUM_WM_RANGES; i++)
			table->WatermarkRow[WM_DCFCLK][i].WmType = (uपूर्णांक8_t)0;

		क्रम (i = 0; i < NUM_WM_RANGES; i++)
			table->WatermarkRow[WM_SOCCLK][i].WmType = (uपूर्णांक8_t)0;
	पूर्ण

	smum_smc_table_manager(hwmgr, (uपूर्णांक8_t *)table, (uपूर्णांक16_t)SMU10_WMTABLE, false);
	data->water_marks_exist = true;
	वापस 0;
पूर्ण

अटल पूर्णांक smu10_smus_notअगरy_pwe(काष्ठा pp_hwmgr *hwmgr)
अणु

	वापस smum_send_msg_to_smc(hwmgr, PPSMC_MSG_SetRccPfcPmeRestoreRegister, शून्य);
पूर्ण

अटल पूर्णांक smu10_घातergate_mmhub(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस smum_send_msg_to_smc(hwmgr, PPSMC_MSG_PowerGateMmHub, शून्य);
पूर्ण

अटल पूर्णांक smu10_घातergate_sdma(काष्ठा pp_hwmgr *hwmgr, bool gate)
अणु
	अगर (gate)
		वापस smum_send_msg_to_smc(hwmgr, PPSMC_MSG_PowerDownSdma, शून्य);
	अन्यथा
		वापस smum_send_msg_to_smc(hwmgr, PPSMC_MSG_PowerUpSdma, शून्य);
पूर्ण

अटल व्योम smu10_घातergate_vcn(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);

	अगर (bgate) अणु
		amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_VCN,
						AMD_PG_STATE_GATE);
		smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_PowerDownVcn, 0, शून्य);
		smu10_data->vcn_घातer_gated = true;
	पूर्ण अन्यथा अणु
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_PowerUpVcn, 0, शून्य);
		amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_VCN,
						AMD_PG_STATE_UNGATE);
		smu10_data->vcn_घातer_gated = false;
	पूर्ण
पूर्ण

अटल पूर्णांक conv_घातer_profile_to_pplib_workload(पूर्णांक घातer_profile)
अणु
	पूर्णांक pplib_workload = 0;

	चयन (घातer_profile) अणु
	हाल PP_SMC_POWER_PROखाता_FULLSCREEN3D:
		pplib_workload = WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT;
		अवरोध;
	हाल PP_SMC_POWER_PROखाता_VIDEO:
		pplib_workload = WORKLOAD_PPLIB_VIDEO_BIT;
		अवरोध;
	हाल PP_SMC_POWER_PROखाता_VR:
		pplib_workload = WORKLOAD_PPLIB_VR_BIT;
		अवरोध;
	हाल PP_SMC_POWER_PROखाता_COMPUTE:
		pplib_workload = WORKLOAD_PPLIB_COMPUTE_BIT;
		अवरोध;
	हाल PP_SMC_POWER_PROखाता_CUSTOM:
		pplib_workload = WORKLOAD_PPLIB_CUSTOM_BIT;
		अवरोध;
	पूर्ण

	वापस pplib_workload;
पूर्ण

अटल पूर्णांक smu10_get_घातer_profile_mode(काष्ठा pp_hwmgr *hwmgr, अक्षर *buf)
अणु
	uपूर्णांक32_t i, size = 0;
	अटल स्थिर uपूर्णांक8_t
		profile_mode_setting[6][4] = अणुअणु70, 60, 0, 0,पूर्ण,
						अणु70, 60, 1, 3,पूर्ण,
						अणु90, 60, 0, 0,पूर्ण,
						अणु70, 60, 0, 0,पूर्ण,
						अणु70, 90, 0, 0,पूर्ण,
						अणु30, 60, 0, 6,पूर्ण,
						पूर्ण;
	अटल स्थिर अक्षर *profile_name[6] = अणु
					"BOOTUP_DEFAULT",
					"3D_FULL_SCREEN",
					"POWER_SAVING",
					"VIDEO",
					"VR",
					"COMPUTE"पूर्ण;
	अटल स्थिर अक्षर *title[6] = अणु"NUM",
			"MODE_NAME",
			"BUSY_SET_POINT",
			"FPS",
			"USE_RLC_BUSY",
			"MIN_ACTIVE_LEVEL"पूर्ण;

	अगर (!buf)
		वापस -EINVAL;

	size += प्र_लिखो(buf + size, "%s %16s %s %s %s %s\n",title[0],
			title[1], title[2], title[3], title[4], title[5]);

	क्रम (i = 0; i <= PP_SMC_POWER_PROखाता_COMPUTE; i++)
		size += प्र_लिखो(buf + size, "%3d %14s%s: %14d %3d %10d %14d\n",
			i, profile_name[i], (i == hwmgr->घातer_profile_mode) ? "*" : " ",
			profile_mode_setting[i][0], profile_mode_setting[i][1],
			profile_mode_setting[i][2], profile_mode_setting[i][3]);

	वापस size;
पूर्ण

अटल bool smu10_is_raven1_refresh(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	अगर ((adev->apu_flags & AMD_APU_IS_RAVEN) &&
	    (hwmgr->smu_version >= 0x41e2b))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक smu10_set_घातer_profile_mode(काष्ठा pp_hwmgr *hwmgr, दीर्घ *input, uपूर्णांक32_t size)
अणु
	पूर्णांक workload_type = 0;
	पूर्णांक result = 0;

	अगर (input[size] > PP_SMC_POWER_PROखाता_COMPUTE) अणु
		pr_err("Invalid power profile mode %ld\n", input[size]);
		वापस -EINVAL;
	पूर्ण
	अगर (hwmgr->घातer_profile_mode == input[size])
		वापस 0;

	/* conv PP_SMC_POWER_PROखाता* to WORKLOAD_PPLIB_*_BIT */
	workload_type =
		conv_घातer_profile_to_pplib_workload(input[size]);
	अगर (workload_type &&
	    smu10_is_raven1_refresh(hwmgr) &&
	    !hwmgr->gfxoff_state_changed_by_workload) अणु
		smu10_gfx_off_control(hwmgr, false);
		hwmgr->gfxoff_state_changed_by_workload = true;
	पूर्ण
	result = smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_ActiveProcessNotअगरy,
						1 << workload_type,
						शून्य);
	अगर (!result)
		hwmgr->घातer_profile_mode = input[size];
	अगर (workload_type && hwmgr->gfxoff_state_changed_by_workload) अणु
		smu10_gfx_off_control(hwmgr, true);
		hwmgr->gfxoff_state_changed_by_workload = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_asic_reset(काष्ठा pp_hwmgr *hwmgr, क्रमागत SMU_ASIC_RESET_MODE mode)
अणु
	वापस smum_send_msg_to_smc_with_parameter(hwmgr,
						   PPSMC_MSG_DeviceDriverReset,
						   mode,
						   शून्य);
पूर्ण

अटल पूर्णांक smu10_set_fine_grain_clk_vol(काष्ठा pp_hwmgr *hwmgr,
					क्रमागत PP_OD_DPM_TABLE_COMMAND type,
					दीर्घ *input, uपूर्णांक32_t size)
अणु
	uपूर्णांक32_t min_freq, max_freq = 0;
	काष्ठा smu10_hwmgr *smu10_data = (काष्ठा smu10_hwmgr *)(hwmgr->backend);
	पूर्णांक ret = 0;

	अगर (!hwmgr->od_enabled) अणु
		pr_err("Fine grain not support\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!smu10_data->fine_grain_enabled) अणु
		pr_err("pp_od_clk_voltage is not accessible if power_dpm_force_performance_level is not in manual mode!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (type == PP_OD_EDIT_SCLK_VDDC_TABLE) अणु
		अगर (size != 2) अणु
			pr_err("Input parameter number not correct\n");
			वापस -EINVAL;
		पूर्ण

		अगर (input[0] == 0) अणु
			smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMinGfxclkFrequency, &min_freq);
			अगर (input[1] < min_freq) अणु
				pr_err("Fine grain setting minimum sclk (%ld) MHz is less than the minimum allowed (%d) MHz\n",
					input[1], min_freq);
				वापस -EINVAL;
			पूर्ण
			smu10_data->gfx_actual_soft_min_freq = input[1];
		पूर्ण अन्यथा अगर (input[0] == 1) अणु
			smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxGfxclkFrequency, &max_freq);
			अगर (input[1] > max_freq) अणु
				pr_err("Fine grain setting maximum sclk (%ld) MHz is greater than the maximum allowed (%d) MHz\n",
					input[1], max_freq);
				वापस -EINVAL;
			पूर्ण
			smu10_data->gfx_actual_soft_max_freq = input[1];
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (type == PP_OD_RESTORE_DEFAULT_TABLE) अणु
		अगर (size != 0) अणु
			pr_err("Input parameter number not correct\n");
			वापस -EINVAL;
		पूर्ण
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMinGfxclkFrequency, &min_freq);
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxGfxclkFrequency, &max_freq);

		smu10_data->gfx_actual_soft_min_freq = min_freq;
		smu10_data->gfx_actual_soft_max_freq = max_freq;
	पूर्ण अन्यथा अगर (type == PP_OD_COMMIT_DPM_TABLE) अणु
		अगर (size != 0) अणु
			pr_err("Input parameter number not correct\n");
			वापस -EINVAL;
		पूर्ण

		अगर (smu10_data->gfx_actual_soft_min_freq > smu10_data->gfx_actual_soft_max_freq) अणु
			pr_err("The setting minimun sclk (%d) MHz is greater than the setting maximum sclk (%d) MHz\n",
					smu10_data->gfx_actual_soft_min_freq, smu10_data->gfx_actual_soft_max_freq);
			वापस -EINVAL;
		पूर्ण

		ret = smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetHardMinGfxClk,
					smu10_data->gfx_actual_soft_min_freq,
					शून्य);
		अगर (ret)
			वापस ret;

		ret = smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetSoftMaxGfxClk,
					smu10_data->gfx_actual_soft_max_freq,
					शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_gfx_state_change(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t state)
अणु
	smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_GpuChangeState, state, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pp_hwmgr_func smu10_hwmgr_funcs = अणु
	.backend_init = smu10_hwmgr_backend_init,
	.backend_fini = smu10_hwmgr_backend_fini,
	.apply_state_adjust_rules = smu10_apply_state_adjust_rules,
	.क्रमce_dpm_level = smu10_dpm_क्रमce_dpm_level,
	.get_घातer_state_size = smu10_get_घातer_state_size,
	.घातerकरोwn_uvd = शून्य,
	.घातergate_uvd = smu10_घातergate_vcn,
	.घातergate_vce = शून्य,
	.get_mclk = smu10_dpm_get_mclk,
	.get_sclk = smu10_dpm_get_sclk,
	.patch_boot_state = smu10_dpm_patch_boot_state,
	.get_pp_table_entry = smu10_dpm_get_pp_table_entry,
	.get_num_of_pp_table_entries = smu10_dpm_get_num_of_pp_table_entries,
	.set_cpu_घातer_state = smu10_set_cpu_घातer_state,
	.store_cc6_data = smu10_store_cc6_data,
	.क्रमce_घड़ी_level = smu10_क्रमce_घड़ी_level,
	.prपूर्णांक_घड़ी_levels = smu10_prपूर्णांक_घड़ी_levels,
	.get_dal_घातer_level = smu10_get_dal_घातer_level,
	.get_perक्रमmance_level = smu10_get_perक्रमmance_level,
	.get_current_shallow_sleep_घड़ीs = smu10_get_current_shallow_sleep_घड़ीs,
	.get_घड़ी_by_type_with_latency = smu10_get_घड़ी_by_type_with_latency,
	.get_घड़ी_by_type_with_voltage = smu10_get_घड़ी_by_type_with_voltage,
	.set_watermarks_क्रम_घड़ीs_ranges = smu10_set_watermarks_क्रम_घड़ीs_ranges,
	.get_max_high_घड़ीs = smu10_get_max_high_घड़ीs,
	.पढ़ो_sensor = smu10_पढ़ो_sensor,
	.set_active_display_count = smu10_set_active_display_count,
	.set_min_deep_sleep_dcefclk = smu10_set_min_deep_sleep_dcefclk,
	.dynamic_state_management_enable = smu10_enable_dpm_tasks,
	.घातer_off_asic = smu10_घातer_off_asic,
	.asic_setup = smu10_setup_asic_task,
	.घातer_state_set = smu10_set_घातer_state_tasks,
	.dynamic_state_management_disable = smu10_disable_dpm_tasks,
	.घातergate_mmhub = smu10_घातergate_mmhub,
	.smus_notअगरy_pwe = smu10_smus_notअगरy_pwe,
	.display_घड़ी_voltage_request = smu10_display_घड़ी_voltage_request,
	.घातergate_gfx = smu10_gfx_off_control,
	.घातergate_sdma = smu10_घातergate_sdma,
	.set_hard_min_dcefclk_by_freq = smu10_set_hard_min_dcefclk_by_freq,
	.set_hard_min_fclk_by_freq = smu10_set_hard_min_fclk_by_freq,
	.set_hard_min_gfxclk_by_freq = smu10_set_hard_min_gfxclk_by_freq,
	.set_soft_max_gfxclk_by_freq = smu10_set_soft_max_gfxclk_by_freq,
	.get_घातer_profile_mode = smu10_get_घातer_profile_mode,
	.set_घातer_profile_mode = smu10_set_घातer_profile_mode,
	.asic_reset = smu10_asic_reset,
	.set_fine_grain_clk_vol = smu10_set_fine_grain_clk_vol,
	.gfx_state_change = smu10_gfx_state_change,
पूर्ण;

पूर्णांक smu10_init_function_poपूर्णांकers(काष्ठा pp_hwmgr *hwmgr)
अणु
	hwmgr->hwmgr_func = &smu10_hwmgr_funcs;
	hwmgr->pptable_func = &pptable_funcs;
	वापस 0;
पूर्ण
