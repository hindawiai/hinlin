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
#समावेश "smu/smu_8_0_d.h"
#समावेश "smu8_fusion.h"
#समावेश "smu/smu_8_0_sh_mask.h"
#समावेश "smumgr.h"
#समावेश "hwmgr.h"
#समावेश "hardwaremanager.h"
#समावेश "cz_ppsmc.h"
#समावेश "smu8_hwmgr.h"
#समावेश "power_state.h"
#समावेश "pp_thermal.h"

#घोषणा ixSMUSVI_NB_CURRENTVID 0xD8230044
#घोषणा CURRENT_NB_VID_MASK 0xff000000
#घोषणा CURRENT_NB_VID__SHIFT 24
#घोषणा ixSMUSVI_GFX_CURRENTVID  0xD8230048
#घोषणा CURRENT_GFX_VID_MASK 0xff000000
#घोषणा CURRENT_GFX_VID__SHIFT 24

अटल स्थिर अचिन्हित दीर्घ smu8_magic = (अचिन्हित दीर्घ) PHM_Cz_Magic;

अटल काष्ठा smu8_घातer_state *cast_smu8_घातer_state(काष्ठा pp_hw_घातer_state *hw_ps)
अणु
	अगर (smu8_magic != hw_ps->magic)
		वापस शून्य;

	वापस (काष्ठा smu8_घातer_state *)hw_ps;
पूर्ण

अटल स्थिर काष्ठा smu8_घातer_state *cast_स्थिर_smu8_घातer_state(
				स्थिर काष्ठा pp_hw_घातer_state *hw_ps)
अणु
	अगर (smu8_magic != hw_ps->magic)
		वापस शून्य;

	वापस (काष्ठा smu8_घातer_state *)hw_ps;
पूर्ण

अटल uपूर्णांक32_t smu8_get_eclk_level(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक32_t घड़ी, uपूर्णांक32_t msg)
अणु
	पूर्णांक i = 0;
	काष्ठा phm_vce_घड़ी_voltage_dependency_table *ptable =
		hwmgr->dyn_state.vce_घड़ी_voltage_dependency_table;

	चयन (msg) अणु
	हाल PPSMC_MSG_SetEclkSoftMin:
	हाल PPSMC_MSG_SetEclkHardMin:
		क्रम (i = 0; i < (पूर्णांक)ptable->count; i++) अणु
			अगर (घड़ी <= ptable->entries[i].ecclk)
				अवरोध;
		पूर्ण
		अवरोध;

	हाल PPSMC_MSG_SetEclkSoftMax:
	हाल PPSMC_MSG_SetEclkHardMax:
		क्रम (i = ptable->count - 1; i >= 0; i--) अणु
			अगर (घड़ी >= ptable->entries[i].ecclk)
				अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल uपूर्णांक32_t smu8_get_sclk_level(काष्ठा pp_hwmgr *hwmgr,
				uपूर्णांक32_t घड़ी, uपूर्णांक32_t msg)
अणु
	पूर्णांक i = 0;
	काष्ठा phm_घड़ी_voltage_dependency_table *table =
				hwmgr->dyn_state.vddc_dependency_on_sclk;

	चयन (msg) अणु
	हाल PPSMC_MSG_SetSclkSoftMin:
	हाल PPSMC_MSG_SetSclkHardMin:
		क्रम (i = 0; i < (पूर्णांक)table->count; i++) अणु
			अगर (घड़ी <= table->entries[i].clk)
				अवरोध;
		पूर्ण
		अवरोध;

	हाल PPSMC_MSG_SetSclkSoftMax:
	हाल PPSMC_MSG_SetSclkHardMax:
		क्रम (i = table->count - 1; i >= 0; i--) अणु
			अगर (घड़ी >= table->entries[i].clk)
				अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस i;
पूर्ण

अटल uपूर्णांक32_t smu8_get_uvd_level(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक32_t घड़ी, uपूर्णांक32_t msg)
अणु
	पूर्णांक i = 0;
	काष्ठा phm_uvd_घड़ी_voltage_dependency_table *ptable =
		hwmgr->dyn_state.uvd_घड़ी_voltage_dependency_table;

	चयन (msg) अणु
	हाल PPSMC_MSG_SetUvdSoftMin:
	हाल PPSMC_MSG_SetUvdHardMin:
		क्रम (i = 0; i < (पूर्णांक)ptable->count; i++) अणु
			अगर (घड़ी <= ptable->entries[i].vclk)
				अवरोध;
		पूर्ण
		अवरोध;

	हाल PPSMC_MSG_SetUvdSoftMax:
	हाल PPSMC_MSG_SetUvdHardMax:
		क्रम (i = ptable->count - 1; i >= 0; i--) अणु
			अगर (घड़ी >= ptable->entries[i].vclk)
				अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल uपूर्णांक32_t smu8_get_max_sclk_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	अगर (data->max_sclk_level == 0) अणु
		smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_GetMaxSclkLevel,
				&data->max_sclk_level);
		data->max_sclk_level += 1;
	पूर्ण

	वापस data->max_sclk_level;
पूर्ण

अटल पूर्णांक smu8_initialize_dpm_शेषs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	data->gfx_ramp_step = 256*25/100;
	data->gfx_ramp_delay = 1; /* by शेष, we delay 1us */

	data->mgcg_cgtt_local0 = 0x00000000;
	data->mgcg_cgtt_local1 = 0x00000000;
	data->घड़ी_slow_करोwn_freq = 25000;
	data->skip_घड़ी_slow_करोwn = 1;
	data->enable_nb_ps_policy = 1; /* disable until UNB is पढ़ोy, Enabled */
	data->voltage_drop_in_dce_घातer_gating = 0; /* disable until fully verअगरied */
	data->voting_rights_clients = 0x00C00033;
	data->अटल_screen_threshold = 8;
	data->ddi_घातer_gating_disabled = 0;
	data->bapm_enabled = 1;
	data->voltage_drop_threshold = 0;
	data->gfx_घातer_gating_threshold = 500;
	data->vce_slow_sclk_threshold = 20000;
	data->dce_slow_sclk_threshold = 30000;
	data->disable_driver_thermal_policy = 1;
	data->disable_nb_ps3_in_battery = 0;

	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
							PHM_Platक्रमmCaps_ABM);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				    PHM_Platक्रमmCaps_NonABMSupportInPPLib);

	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_DynamicM3Arbiter);

	data->override_dynamic_mgpg = 1;

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				  PHM_Platक्रमmCaps_DynamicPatchPowerState);

	data->thermal_स्वतः_throttling_treshold = 0;
	data->tdr_घड़ी = 0;
	data->disable_gfx_घातer_gating_in_uvd = 0;

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_DynamicUVDState);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_UVDDPM);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_VCEDPM);

	data->cc6_settings.cpu_cc6_disable = false;
	data->cc6_settings.cpu_pstate_disable = false;
	data->cc6_settings.nb_pstate_चयन_disable = false;
	data->cc6_settings.cpu_pstate_separation_समय = 0;

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				   PHM_Platक्रमmCaps_DisableVoltageIsland);

	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
		      PHM_Platक्रमmCaps_UVDPowerGating);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
		      PHM_Platक्रमmCaps_VCEPowerGating);

	अगर (adev->pg_flags & AMD_PG_SUPPORT_UVD)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			      PHM_Platक्रमmCaps_UVDPowerGating);
	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCE)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			      PHM_Platक्रमmCaps_VCEPowerGating);


	वापस 0;
पूर्ण

/* convert क्रमm 8bit vid to real voltage in mV*4 */
अटल uपूर्णांक32_t smu8_convert_8Bit_index_to_voltage(
			काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t voltage)
अणु
	वापस 6200 - (voltage * 25);
पूर्ण

अटल पूर्णांक smu8_स्थिरruct_max_घातer_limits_table(काष्ठा pp_hwmgr *hwmgr,
			काष्ठा phm_घड़ी_and_voltage_limits *table)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	काष्ठा smu8_sys_info *sys_info = &data->sys_info;
	काष्ठा phm_घड़ी_voltage_dependency_table *dep_table =
				hwmgr->dyn_state.vddc_dependency_on_sclk;

	अगर (dep_table->count > 0) अणु
		table->sclk = dep_table->entries[dep_table->count-1].clk;
		table->vddc = smu8_convert_8Bit_index_to_voltage(hwmgr,
		   (uपूर्णांक16_t)dep_table->entries[dep_table->count-1].v);
	पूर्ण
	table->mclk = sys_info->nbp_memory_घड़ी[0];
	वापस 0;
पूर्ण

अटल पूर्णांक smu8_init_dynamic_state_adjusपंचांगent_rule_settings(
			काष्ठा pp_hwmgr *hwmgr,
			ATOM_CLK_VOLT_CAPABILITY *disp_voltage_table)
अणु
	काष्ठा phm_घड़ी_voltage_dependency_table *table_clk_vlt;

	table_clk_vlt = kzalloc(काष्ठा_size(table_clk_vlt, entries, 8),
				GFP_KERNEL);

	अगर (शून्य == table_clk_vlt) अणु
		pr_err("Can not allocate memory!\n");
		वापस -ENOMEM;
	पूर्ण

	table_clk_vlt->count = 8;
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

अटल पूर्णांक smu8_get_प्रणाली_info_data(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	ATOM_INTEGRATED_SYSTEM_INFO_V1_9 *info = शून्य;
	uपूर्णांक32_t i;
	पूर्णांक result = 0;
	uपूर्णांक8_t frev, crev;
	uपूर्णांक16_t size;

	info = (ATOM_INTEGRATED_SYSTEM_INFO_V1_9 *)smu_atom_get_data_table(hwmgr->adev,
			GetIndexIntoMasterTable(DATA, IntegratedSystemInfo),
			&size, &frev, &crev);

	अगर (info == शून्य) अणु
		pr_err("Could not retrieve the Integrated System Info Table!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (crev != 9) अणु
		pr_err("Unsupported IGP table: %d %d\n", frev, crev);
		वापस -EINVAL;
	पूर्ण

	data->sys_info.bootup_uma_घड़ी =
				   le32_to_cpu(info->ulBootUpUMAClock);

	data->sys_info.bootup_engine_घड़ी =
				le32_to_cpu(info->ulBootUpEngineClock);

	data->sys_info.dentist_vco_freq =
				   le32_to_cpu(info->ulDentistVCOFreq);

	data->sys_info.प्रणाली_config =
				     le32_to_cpu(info->ulSystemConfig);

	data->sys_info.bootup_nb_voltage_index =
				  le16_to_cpu(info->usBootUpNBVoltage);

	data->sys_info.htc_hyst_lmt =
			(info->ucHtcHystLmt == 0) ? 5 : info->ucHtcHystLmt;

	data->sys_info.htc_पंचांगp_lmt =
			(info->ucHtcTmpLmt == 0) ? 203 : info->ucHtcTmpLmt;

	अगर (data->sys_info.htc_पंचांगp_lmt <=
			data->sys_info.htc_hyst_lmt) अणु
		pr_err("The htcTmpLmt should be larger than htcHystLmt.\n");
		वापस -EINVAL;
	पूर्ण

	data->sys_info.nb_dpm_enable =
				data->enable_nb_ps_policy &&
				(le32_to_cpu(info->ulSystemConfig) >> 3 & 0x1);

	क्रम (i = 0; i < SMU8_NUM_NBPSTATES; i++) अणु
		अगर (i < SMU8_NUM_NBPMEMORYCLOCK) अणु
			data->sys_info.nbp_memory_घड़ी[i] =
			  le32_to_cpu(info->ulNbpStateMemclkFreq[i]);
		पूर्ण
		data->sys_info.nbp_n_घड़ी[i] =
			    le32_to_cpu(info->ulNbpStateNClkFreq[i]);
	पूर्ण

	क्रम (i = 0; i < MAX_DISPLAY_CLOCK_LEVEL; i++) अणु
		data->sys_info.display_घड़ी[i] =
					le32_to_cpu(info->sDispClkVoltageMapping[i].ulMaximumSupportedCLK);
	पूर्ण

	/* Here use 4 levels, make sure not exceed */
	क्रम (i = 0; i < SMU8_NUM_NBPSTATES; i++) अणु
		data->sys_info.nbp_voltage_index[i] =
			     le16_to_cpu(info->usNBPStateVoltage[i]);
	पूर्ण

	अगर (!data->sys_info.nb_dpm_enable) अणु
		क्रम (i = 1; i < SMU8_NUM_NBPSTATES; i++) अणु
			अगर (i < SMU8_NUM_NBPMEMORYCLOCK) अणु
				data->sys_info.nbp_memory_घड़ी[i] =
				    data->sys_info.nbp_memory_घड़ी[0];
			पूर्ण
			data->sys_info.nbp_n_घड़ी[i] =
				    data->sys_info.nbp_n_घड़ी[0];
			data->sys_info.nbp_voltage_index[i] =
				    data->sys_info.nbp_voltage_index[0];
		पूर्ण
	पूर्ण

	अगर (le32_to_cpu(info->ulGPUCapInfo) &
		SYS_INFO_GPUCAPS__ENABEL_DFS_BYPASS) अणु
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				    PHM_Platक्रमmCaps_EnableDFSBypass);
	पूर्ण

	data->sys_info.uma_channel_number = info->ucUMAChannelNumber;

	smu8_स्थिरruct_max_घातer_limits_table (hwmgr,
				    &hwmgr->dyn_state.max_घड़ी_voltage_on_ac);

	smu8_init_dynamic_state_adjusपंचांगent_rule_settings(hwmgr,
				    &info->sDISPCLK_Voltage[0]);

	वापस result;
पूर्ण

अटल पूर्णांक smu8_स्थिरruct_boot_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	data->boot_घातer_level.engineClock =
				data->sys_info.bootup_engine_घड़ी;

	data->boot_घातer_level.vddcIndex =
			(uपूर्णांक8_t)data->sys_info.bootup_nb_voltage_index;

	data->boot_घातer_level.dsDividerIndex = 0;
	data->boot_घातer_level.ssDividerIndex = 0;
	data->boot_घातer_level.allowGnbSlow = 1;
	data->boot_घातer_level.क्रमceNBPstate = 0;
	data->boot_घातer_level.hysteresis_up = 0;
	data->boot_घातer_level.numSIMDToPowerDown = 0;
	data->boot_घातer_level.display_wm = 0;
	data->boot_घातer_level.vce_wm = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_upload_pptable_to_smu(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा SMU8_Fusion_ClkTable *घड़ी_प्रकारable;
	पूर्णांक ret;
	uपूर्णांक32_t i;
	व्योम *table = शून्य;
	pp_atomctrl_घड़ी_भागiders_kong भागiders;

	काष्ठा phm_घड़ी_voltage_dependency_table *vddc_table =
		hwmgr->dyn_state.vddc_dependency_on_sclk;
	काष्ठा phm_घड़ी_voltage_dependency_table *vdd_gfx_table =
		hwmgr->dyn_state.vdd_gfx_dependency_on_sclk;
	काष्ठा phm_acp_घड़ी_voltage_dependency_table *acp_table =
		hwmgr->dyn_state.acp_घड़ी_voltage_dependency_table;
	काष्ठा phm_uvd_घड़ी_voltage_dependency_table *uvd_table =
		hwmgr->dyn_state.uvd_घड़ी_voltage_dependency_table;
	काष्ठा phm_vce_घड़ी_voltage_dependency_table *vce_table =
		hwmgr->dyn_state.vce_घड़ी_voltage_dependency_table;

	अगर (!hwmgr->need_pp_table_upload)
		वापस 0;

	ret = smum_करोwnload_घातerplay_table(hwmgr, &table);

	PP_ASSERT_WITH_CODE((0 == ret && शून्य != table),
			    "Fail to get clock table from SMU!", वापस -EINVAL;);

	घड़ी_प्रकारable = (काष्ठा SMU8_Fusion_ClkTable *)table;

	/* patch घड़ी table */
	PP_ASSERT_WITH_CODE((vddc_table->count <= SMU8_MAX_HARDWARE_POWERLEVELS),
			    "Dependency table entry exceeds max limit!", वापस -EINVAL;);
	PP_ASSERT_WITH_CODE((vdd_gfx_table->count <= SMU8_MAX_HARDWARE_POWERLEVELS),
			    "Dependency table entry exceeds max limit!", वापस -EINVAL;);
	PP_ASSERT_WITH_CODE((acp_table->count <= SMU8_MAX_HARDWARE_POWERLEVELS),
			    "Dependency table entry exceeds max limit!", वापस -EINVAL;);
	PP_ASSERT_WITH_CODE((uvd_table->count <= SMU8_MAX_HARDWARE_POWERLEVELS),
			    "Dependency table entry exceeds max limit!", वापस -EINVAL;);
	PP_ASSERT_WITH_CODE((vce_table->count <= SMU8_MAX_HARDWARE_POWERLEVELS),
			    "Dependency table entry exceeds max limit!", वापस -EINVAL;);

	क्रम (i = 0; i < SMU8_MAX_HARDWARE_POWERLEVELS; i++) अणु

		/* vddc_sclk */
		घड़ी_प्रकारable->SclkBreakकरोwnTable.ClkLevel[i].GnbVid =
			(i < vddc_table->count) ? (uपूर्णांक8_t)vddc_table->entries[i].v : 0;
		घड़ी_प्रकारable->SclkBreakकरोwnTable.ClkLevel[i].Frequency =
			(i < vddc_table->count) ? vddc_table->entries[i].clk : 0;

		atomctrl_get_engine_pll_भागiders_kong(hwmgr,
						      घड़ी_प्रकारable->SclkBreakकरोwnTable.ClkLevel[i].Frequency,
						      &भागiders);

		घड़ी_प्रकारable->SclkBreakकरोwnTable.ClkLevel[i].DfsDid =
			(uपूर्णांक8_t)भागiders.pll_post_भागider;

		/* vddgfx_sclk */
		घड़ी_प्रकारable->SclkBreakकरोwnTable.ClkLevel[i].GfxVid =
			(i < vdd_gfx_table->count) ? (uपूर्णांक8_t)vdd_gfx_table->entries[i].v : 0;

		/* acp अवरोधकरोwn */
		घड़ी_प्रकारable->AclkBreakकरोwnTable.ClkLevel[i].GfxVid =
			(i < acp_table->count) ? (uपूर्णांक8_t)acp_table->entries[i].v : 0;
		घड़ी_प्रकारable->AclkBreakकरोwnTable.ClkLevel[i].Frequency =
			(i < acp_table->count) ? acp_table->entries[i].acpclk : 0;

		atomctrl_get_engine_pll_भागiders_kong(hwmgr,
						      घड़ी_प्रकारable->AclkBreakकरोwnTable.ClkLevel[i].Frequency,
						      &भागiders);

		घड़ी_प्रकारable->AclkBreakकरोwnTable.ClkLevel[i].DfsDid =
			(uपूर्णांक8_t)भागiders.pll_post_भागider;


		/* uvd अवरोधकरोwn */
		घड़ी_प्रकारable->VclkBreakकरोwnTable.ClkLevel[i].GfxVid =
			(i < uvd_table->count) ? (uपूर्णांक8_t)uvd_table->entries[i].v : 0;
		घड़ी_प्रकारable->VclkBreakकरोwnTable.ClkLevel[i].Frequency =
			(i < uvd_table->count) ? uvd_table->entries[i].vclk : 0;

		atomctrl_get_engine_pll_भागiders_kong(hwmgr,
						      घड़ी_प्रकारable->VclkBreakकरोwnTable.ClkLevel[i].Frequency,
						      &भागiders);

		घड़ी_प्रकारable->VclkBreakकरोwnTable.ClkLevel[i].DfsDid =
			(uपूर्णांक8_t)भागiders.pll_post_भागider;

		घड़ी_प्रकारable->DclkBreakकरोwnTable.ClkLevel[i].GfxVid =
			(i < uvd_table->count) ? (uपूर्णांक8_t)uvd_table->entries[i].v : 0;
		घड़ी_प्रकारable->DclkBreakकरोwnTable.ClkLevel[i].Frequency =
			(i < uvd_table->count) ? uvd_table->entries[i].dclk : 0;

		atomctrl_get_engine_pll_भागiders_kong(hwmgr,
						      घड़ी_प्रकारable->DclkBreakकरोwnTable.ClkLevel[i].Frequency,
						      &भागiders);

		घड़ी_प्रकारable->DclkBreakकरोwnTable.ClkLevel[i].DfsDid =
			(uपूर्णांक8_t)भागiders.pll_post_भागider;

		/* vce अवरोधकरोwn */
		घड़ी_प्रकारable->EclkBreakकरोwnTable.ClkLevel[i].GfxVid =
			(i < vce_table->count) ? (uपूर्णांक8_t)vce_table->entries[i].v : 0;
		घड़ी_प्रकारable->EclkBreakकरोwnTable.ClkLevel[i].Frequency =
			(i < vce_table->count) ? vce_table->entries[i].ecclk : 0;


		atomctrl_get_engine_pll_भागiders_kong(hwmgr,
						      घड़ी_प्रकारable->EclkBreakकरोwnTable.ClkLevel[i].Frequency,
						      &भागiders);

		घड़ी_प्रकारable->EclkBreakकरोwnTable.ClkLevel[i].DfsDid =
			(uपूर्णांक8_t)भागiders.pll_post_भागider;

	पूर्ण
	ret = smum_upload_घातerplay_table(hwmgr);

	वापस ret;
पूर्ण

अटल पूर्णांक smu8_init_sclk_limit(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	काष्ठा phm_घड़ी_voltage_dependency_table *table =
					hwmgr->dyn_state.vddc_dependency_on_sclk;
	अचिन्हित दीर्घ घड़ी = 0, level;

	अगर (शून्य == table || table->count <= 0)
		वापस -EINVAL;

	data->sclk_dpm.soft_min_clk = table->entries[0].clk;
	data->sclk_dpm.hard_min_clk = table->entries[0].clk;

	level = smu8_get_max_sclk_level(hwmgr) - 1;

	अगर (level < table->count)
		घड़ी = table->entries[level].clk;
	अन्यथा
		घड़ी = table->entries[table->count - 1].clk;

	data->sclk_dpm.soft_max_clk = घड़ी;
	data->sclk_dpm.hard_max_clk = घड़ी;

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_init_uvd_limit(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	काष्ठा phm_uvd_घड़ी_voltage_dependency_table *table =
				hwmgr->dyn_state.uvd_घड़ी_voltage_dependency_table;
	अचिन्हित दीर्घ घड़ी = 0;
	uपूर्णांक32_t level;

	अगर (शून्य == table || table->count <= 0)
		वापस -EINVAL;

	data->uvd_dpm.soft_min_clk = 0;
	data->uvd_dpm.hard_min_clk = 0;

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxUvdLevel, &level);

	अगर (level < table->count)
		घड़ी = table->entries[level].vclk;
	अन्यथा
		घड़ी = table->entries[table->count - 1].vclk;

	data->uvd_dpm.soft_max_clk = घड़ी;
	data->uvd_dpm.hard_max_clk = घड़ी;

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_init_vce_limit(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	काष्ठा phm_vce_घड़ी_voltage_dependency_table *table =
				hwmgr->dyn_state.vce_घड़ी_voltage_dependency_table;
	अचिन्हित दीर्घ घड़ी = 0;
	uपूर्णांक32_t level;

	अगर (शून्य == table || table->count <= 0)
		वापस -EINVAL;

	data->vce_dpm.soft_min_clk = 0;
	data->vce_dpm.hard_min_clk = 0;

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxEclkLevel, &level);

	अगर (level < table->count)
		घड़ी = table->entries[level].ecclk;
	अन्यथा
		घड़ी = table->entries[table->count - 1].ecclk;

	data->vce_dpm.soft_max_clk = घड़ी;
	data->vce_dpm.hard_max_clk = घड़ी;

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_init_acp_limit(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	काष्ठा phm_acp_घड़ी_voltage_dependency_table *table =
				hwmgr->dyn_state.acp_घड़ी_voltage_dependency_table;
	अचिन्हित दीर्घ घड़ी = 0;
	uपूर्णांक32_t level;

	अगर (शून्य == table || table->count <= 0)
		वापस -EINVAL;

	data->acp_dpm.soft_min_clk = 0;
	data->acp_dpm.hard_min_clk = 0;

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxAclkLevel, &level);

	अगर (level < table->count)
		घड़ी = table->entries[level].acpclk;
	अन्यथा
		घड़ी = table->entries[table->count - 1].acpclk;

	data->acp_dpm.soft_max_clk = घड़ी;
	data->acp_dpm.hard_max_clk = घड़ी;
	वापस 0;
पूर्ण

अटल व्योम smu8_init_घातer_gate_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	data->uvd_घातer_gated = false;
	data->vce_घातer_gated = false;
	data->samu_घातer_gated = false;
#अगर_घोषित CONFIG_DRM_AMD_ACP
	data->acp_घातer_gated = false;
#अन्यथा
	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ACPPowerOFF, शून्य);
	data->acp_घातer_gated = true;
#पूर्ण_अगर

पूर्ण

अटल व्योम smu8_init_sclk_threshold(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	data->low_sclk_पूर्णांकerrupt_threshold = 0;
पूर्ण

अटल पूर्णांक smu8_update_sclk_limit(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	काष्ठा phm_घड़ी_voltage_dependency_table *table =
					hwmgr->dyn_state.vddc_dependency_on_sclk;

	अचिन्हित दीर्घ घड़ी = 0;
	अचिन्हित दीर्घ level;
	अचिन्हित दीर्घ stable_pstate_sclk;
	अचिन्हित दीर्घ percentage;

	data->sclk_dpm.soft_min_clk = table->entries[0].clk;
	level = smu8_get_max_sclk_level(hwmgr) - 1;

	अगर (level < table->count)
		data->sclk_dpm.soft_max_clk  = table->entries[level].clk;
	अन्यथा
		data->sclk_dpm.soft_max_clk  = table->entries[table->count - 1].clk;

	घड़ी = hwmgr->display_config->min_core_set_घड़ी;
	अगर (घड़ी == 0)
		pr_debug("min_core_set_clock not set\n");

	अगर (data->sclk_dpm.hard_min_clk != घड़ी) अणु
		data->sclk_dpm.hard_min_clk = घड़ी;

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSclkHardMin,
						 smu8_get_sclk_level(hwmgr,
					data->sclk_dpm.hard_min_clk,
					     PPSMC_MSG_SetSclkHardMin),
						 शून्य);
	पूर्ण

	घड़ी = data->sclk_dpm.soft_min_clk;

	/* update minimum घड़ीs क्रम Stable P-State feature */
	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				     PHM_Platक्रमmCaps_StablePState)) अणु
		percentage = 75;
		/*Sclk - calculate sclk value based on percentage and find FLOOR sclk from VddcDependencyOnSCLK table  */
		stable_pstate_sclk = (hwmgr->dyn_state.max_घड़ी_voltage_on_ac.mclk *
					percentage) / 100;

		अगर (घड़ी < stable_pstate_sclk)
			घड़ी = stable_pstate_sclk;
	पूर्ण

	अगर (data->sclk_dpm.soft_min_clk != घड़ी) अणु
		data->sclk_dpm.soft_min_clk = घड़ी;
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSclkSoftMin,
						smu8_get_sclk_level(hwmgr,
					data->sclk_dpm.soft_min_clk,
					     PPSMC_MSG_SetSclkSoftMin),
						शून्य);
	पूर्ण

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				    PHM_Platक्रमmCaps_StablePState) &&
			 data->sclk_dpm.soft_max_clk != घड़ी) अणु
		data->sclk_dpm.soft_max_clk = घड़ी;
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSclkSoftMax,
						smu8_get_sclk_level(hwmgr,
					data->sclk_dpm.soft_max_clk,
					PPSMC_MSG_SetSclkSoftMax),
						शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_set_deep_sleep_sclk_threshold(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_SclkDeepSleep)) अणु
		uपूर्णांक32_t clks = hwmgr->display_config->min_core_set_घड़ी_in_sr;
		अगर (clks == 0)
			clks = SMU8_MIN_DEEP_SLEEP_SCLK;

		PP_DBG_LOG("Setting Deep Sleep Clock: %d\n", clks);

		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetMinDeepSleepSclk,
				clks,
				शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_set_watermark_threshold(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data =
				  hwmgr->backend;

	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetWatermarkFrequency,
					data->sclk_dpm.soft_max_clk,
					शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_nbdpm_pstate_enable_disable(काष्ठा pp_hwmgr *hwmgr, bool enable, bool lock)
अणु
	काष्ठा smu8_hwmgr *hw_data = hwmgr->backend;

	अगर (hw_data->is_nb_dpm_enabled) अणु
		अगर (enable) अणु
			PP_DBG_LOG("enable Low Memory PState.\n");

			वापस smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_EnableLowMemoryPstate,
						(lock ? 1 : 0),
						शून्य);
		पूर्ण अन्यथा अणु
			PP_DBG_LOG("disable Low Memory PState.\n");

			वापस smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_DisableLowMemoryPstate,
						(lock ? 1 : 0),
						शून्य);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_disable_nb_dpm(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret = 0;

	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	अचिन्हित दीर्घ dpm_features = 0;

	अगर (data->is_nb_dpm_enabled) अणु
		smu8_nbdpm_pstate_enable_disable(hwmgr, true, true);
		dpm_features |= NB_DPM_MASK;
		ret = smum_send_msg_to_smc_with_parameter(
							  hwmgr,
							  PPSMC_MSG_DisableAllSmuFeatures,
							  dpm_features,
							  शून्य);
		अगर (ret == 0)
			data->is_nb_dpm_enabled = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smu8_enable_nb_dpm(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret = 0;

	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	अचिन्हित दीर्घ dpm_features = 0;

	अगर (!data->is_nb_dpm_enabled) अणु
		PP_DBG_LOG("enabling ALL SMU features.\n");
		dpm_features |= NB_DPM_MASK;
		ret = smum_send_msg_to_smc_with_parameter(
							  hwmgr,
							  PPSMC_MSG_EnableAllSmuFeatures,
							  dpm_features,
							  शून्य);
		अगर (ret == 0)
			data->is_nb_dpm_enabled = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smu8_update_low_mem_pstate(काष्ठा pp_hwmgr *hwmgr, स्थिर व्योम *input)
अणु
	bool disable_चयन;
	bool enable_low_mem_state;
	काष्ठा smu8_hwmgr *hw_data = hwmgr->backend;
	स्थिर काष्ठा phm_set_घातer_state_input *states = (काष्ठा phm_set_घातer_state_input *)input;
	स्थिर काष्ठा smu8_घातer_state *pnew_state = cast_स्थिर_smu8_घातer_state(states->pnew_state);

	अगर (hw_data->sys_info.nb_dpm_enable) अणु
		disable_चयन = hw_data->cc6_settings.nb_pstate_चयन_disable ? true : false;
		enable_low_mem_state = hw_data->cc6_settings.nb_pstate_चयन_disable ? false : true;

		अगर (pnew_state->action == FORCE_HIGH)
			smu8_nbdpm_pstate_enable_disable(hwmgr, false, disable_चयन);
		अन्यथा अगर (pnew_state->action == CANCEL_FORCE_HIGH)
			smu8_nbdpm_pstate_enable_disable(hwmgr, true, disable_चयन);
		अन्यथा
			smu8_nbdpm_pstate_enable_disable(hwmgr, enable_low_mem_state, disable_चयन);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu8_set_घातer_state_tasks(काष्ठा pp_hwmgr *hwmgr, स्थिर व्योम *input)
अणु
	पूर्णांक ret = 0;

	smu8_update_sclk_limit(hwmgr);
	smu8_set_deep_sleep_sclk_threshold(hwmgr);
	smu8_set_watermark_threshold(hwmgr);
	ret = smu8_enable_nb_dpm(hwmgr);
	अगर (ret)
		वापस ret;
	smu8_update_low_mem_pstate(hwmgr, input);

	वापस 0;
पूर्ण


अटल पूर्णांक smu8_setup_asic_task(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret;

	ret = smu8_upload_pptable_to_smu(hwmgr);
	अगर (ret)
		वापस ret;
	ret = smu8_init_sclk_limit(hwmgr);
	अगर (ret)
		वापस ret;
	ret = smu8_init_uvd_limit(hwmgr);
	अगर (ret)
		वापस ret;
	ret = smu8_init_vce_limit(hwmgr);
	अगर (ret)
		वापस ret;
	ret = smu8_init_acp_limit(hwmgr);
	अगर (ret)
		वापस ret;

	smu8_init_घातer_gate_state(hwmgr);
	smu8_init_sclk_threshold(hwmgr);

	वापस 0;
पूर्ण

अटल व्योम smu8_घातer_up_display_घड़ी_sys_pll(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *hw_data = hwmgr->backend;

	hw_data->disp_clk_bypass_pending = false;
	hw_data->disp_clk_bypass = false;
पूर्ण

अटल व्योम smu8_clear_nb_dpm_flag(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *hw_data = hwmgr->backend;

	hw_data->is_nb_dpm_enabled = false;
पूर्ण

अटल व्योम smu8_reset_cc6_data(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *hw_data = hwmgr->backend;

	hw_data->cc6_settings.cc6_setting_changed = false;
	hw_data->cc6_settings.cpu_pstate_separation_समय = 0;
	hw_data->cc6_settings.cpu_cc6_disable = false;
	hw_data->cc6_settings.cpu_pstate_disable = false;
पूर्ण

अटल व्योम smu8_program_voting_clients(काष्ठा pp_hwmgr *hwmgr)
अणु
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
				ixCG_FREQ_TRAN_VOTING_0,
				SMU8_VOTINGRIGHTSCLIENTS_DFLT0);
पूर्ण

अटल व्योम smu8_clear_voting_clients(काष्ठा pp_hwmgr *hwmgr)
अणु
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
				ixCG_FREQ_TRAN_VOTING_0, 0);
पूर्ण

अटल पूर्णांक smu8_start_dpm(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	data->dpm_flags |= DPMFlags_SCLK_Enabled;

	वापस smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_EnableAllSmuFeatures,
				SCLK_DPM_MASK,
				शून्य);
पूर्ण

अटल पूर्णांक smu8_stop_dpm(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret = 0;
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	अचिन्हित दीर्घ dpm_features = 0;

	अगर (data->dpm_flags & DPMFlags_SCLK_Enabled) अणु
		dpm_features |= SCLK_DPM_MASK;
		data->dpm_flags &= ~DPMFlags_SCLK_Enabled;
		ret = smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DisableAllSmuFeatures,
					dpm_features,
					शून्य);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक smu8_program_bootup_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	data->sclk_dpm.soft_min_clk = data->sys_info.bootup_engine_घड़ी;
	data->sclk_dpm.soft_max_clk = data->sys_info.bootup_engine_घड़ी;

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSclkSoftMin,
				smu8_get_sclk_level(hwmgr,
				data->sclk_dpm.soft_min_clk,
				PPSMC_MSG_SetSclkSoftMin),
				शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSclkSoftMax,
				smu8_get_sclk_level(hwmgr,
				data->sclk_dpm.soft_max_clk,
				PPSMC_MSG_SetSclkSoftMax),
				शून्य);

	वापस 0;
पूर्ण

अटल व्योम smu8_reset_acp_boot_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	data->acp_boot_level = 0xff;
पूर्ण

अटल पूर्णांक smu8_enable_dpm_tasks(काष्ठा pp_hwmgr *hwmgr)
अणु
	smu8_program_voting_clients(hwmgr);
	अगर (smu8_start_dpm(hwmgr))
		वापस -EINVAL;
	smu8_program_bootup_state(hwmgr);
	smu8_reset_acp_boot_level(hwmgr);

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_disable_dpm_tasks(काष्ठा pp_hwmgr *hwmgr)
अणु
	smu8_disable_nb_dpm(hwmgr);

	smu8_clear_voting_clients(hwmgr);
	अगर (smu8_stop_dpm(hwmgr))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_घातer_off_asic(काष्ठा pp_hwmgr *hwmgr)
अणु
	smu8_disable_dpm_tasks(hwmgr);
	smu8_घातer_up_display_घड़ी_sys_pll(hwmgr);
	smu8_clear_nb_dpm_flag(hwmgr);
	smu8_reset_cc6_data(hwmgr);
	वापस 0;
पूर्ण

अटल पूर्णांक smu8_apply_state_adjust_rules(काष्ठा pp_hwmgr *hwmgr,
				काष्ठा pp_घातer_state  *prequest_ps,
			स्थिर काष्ठा pp_घातer_state *pcurrent_ps)
अणु
	काष्ठा smu8_घातer_state *smu8_ps =
				cast_smu8_घातer_state(&prequest_ps->hardware);

	स्थिर काष्ठा smu8_घातer_state *smu8_current_ps =
				cast_स्थिर_smu8_घातer_state(&pcurrent_ps->hardware);

	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	काष्ठा PP_Clocks घड़ीs = अणु0, 0, 0, 0पूर्ण;
	bool क्रमce_high;

	smu8_ps->need_dfs_bypass = true;

	data->battery_state = (PP_StateUILabel_Battery == prequest_ps->classअगरication.ui_label);

	घड़ीs.memoryClock = hwmgr->display_config->min_mem_set_घड़ी != 0 ?
				hwmgr->display_config->min_mem_set_घड़ी :
				data->sys_info.nbp_memory_घड़ी[1];


	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_StablePState))
		घड़ीs.memoryClock = hwmgr->dyn_state.max_घड़ी_voltage_on_ac.mclk;

	क्रमce_high = (घड़ीs.memoryClock > data->sys_info.nbp_memory_घड़ी[SMU8_NUM_NBPMEMORYCLOCK - 1])
			|| (hwmgr->display_config->num_display >= 3);

	smu8_ps->action = smu8_current_ps->action;

	अगर (hwmgr->request_dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK)
		smu8_nbdpm_pstate_enable_disable(hwmgr, false, false);
	अन्यथा अगर (hwmgr->request_dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD)
		smu8_nbdpm_pstate_enable_disable(hwmgr, false, true);
	अन्यथा अगर (!क्रमce_high && (smu8_ps->action == FORCE_HIGH))
		smu8_ps->action = CANCEL_FORCE_HIGH;
	अन्यथा अगर (क्रमce_high && (smu8_ps->action != FORCE_HIGH))
		smu8_ps->action = FORCE_HIGH;
	अन्यथा
		smu8_ps->action = DO_NOTHING;

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_hwmgr_backend_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	काष्ठा smu8_hwmgr *data;

	data = kzalloc(माप(काष्ठा smu8_hwmgr), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	hwmgr->backend = data;

	result = smu8_initialize_dpm_शेषs(hwmgr);
	अगर (result != 0) अणु
		pr_err("smu8_initialize_dpm_defaults failed\n");
		वापस result;
	पूर्ण

	result = smu8_get_प्रणाली_info_data(hwmgr);
	अगर (result != 0) अणु
		pr_err("smu8_get_system_info_data failed\n");
		वापस result;
	पूर्ण

	smu8_स्थिरruct_boot_state(hwmgr);

	hwmgr->platक्रमm_descriptor.hardwareActivityPerक्रमmanceLevels =  SMU8_MAX_HARDWARE_POWERLEVELS;

	वापस result;
पूर्ण

अटल पूर्णांक smu8_hwmgr_backend_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (hwmgr != शून्य) अणु
		kमुक्त(hwmgr->dyn_state.vddc_dep_on_dal_pwrl);
		hwmgr->dyn_state.vddc_dep_on_dal_pwrl = शून्य;

		kमुक्त(hwmgr->backend);
		hwmgr->backend = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu8_phm_क्रमce_dpm_highest(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetSclkSoftMin,
					smu8_get_sclk_level(hwmgr,
					data->sclk_dpm.soft_max_clk,
					PPSMC_MSG_SetSclkSoftMin),
					शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSclkSoftMax,
				smu8_get_sclk_level(hwmgr,
				data->sclk_dpm.soft_max_clk,
				PPSMC_MSG_SetSclkSoftMax),
				शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_phm_unक्रमce_dpm_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	काष्ठा phm_घड़ी_voltage_dependency_table *table =
				hwmgr->dyn_state.vddc_dependency_on_sclk;
	अचिन्हित दीर्घ घड़ी = 0, level;

	अगर (शून्य == table || table->count <= 0)
		वापस -EINVAL;

	data->sclk_dpm.soft_min_clk = table->entries[0].clk;
	data->sclk_dpm.hard_min_clk = table->entries[0].clk;
	hwmgr->pstate_sclk = table->entries[0].clk;
	hwmgr->pstate_mclk = 0;

	level = smu8_get_max_sclk_level(hwmgr) - 1;

	अगर (level < table->count)
		घड़ी = table->entries[level].clk;
	अन्यथा
		घड़ी = table->entries[table->count - 1].clk;

	data->sclk_dpm.soft_max_clk = घड़ी;
	data->sclk_dpm.hard_max_clk = घड़ी;

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSclkSoftMin,
				smu8_get_sclk_level(hwmgr,
				data->sclk_dpm.soft_min_clk,
				PPSMC_MSG_SetSclkSoftMin),
				शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSclkSoftMax,
				smu8_get_sclk_level(hwmgr,
				data->sclk_dpm.soft_max_clk,
				PPSMC_MSG_SetSclkSoftMax),
				शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_phm_क्रमce_dpm_lowest(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetSclkSoftMax,
			smu8_get_sclk_level(hwmgr,
			data->sclk_dpm.soft_min_clk,
			PPSMC_MSG_SetSclkSoftMax),
			शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSclkSoftMin,
				smu8_get_sclk_level(hwmgr,
				data->sclk_dpm.soft_min_clk,
				PPSMC_MSG_SetSclkSoftMin),
				शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_dpm_क्रमce_dpm_level(काष्ठा pp_hwmgr *hwmgr,
				क्रमागत amd_dpm_क्रमced_level level)
अणु
	पूर्णांक ret = 0;

	चयन (level) अणु
	हाल AMD_DPM_FORCED_LEVEL_HIGH:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_PEAK:
		ret = smu8_phm_क्रमce_dpm_highest(hwmgr);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_LOW:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD:
		ret = smu8_phm_क्रमce_dpm_lowest(hwmgr);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_AUTO:
		ret = smu8_phm_unक्रमce_dpm_levels(hwmgr);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_MANUAL:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_EXIT:
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smu8_dpm_घातerकरोwn_uvd(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (PP_CAP(PHM_Platक्रमmCaps_UVDPowerGating))
		वापस smum_send_msg_to_smc(hwmgr, PPSMC_MSG_UVDPowerOFF, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक smu8_dpm_घातerup_uvd(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (PP_CAP(PHM_Platक्रमmCaps_UVDPowerGating)) अणु
		वापस smum_send_msg_to_smc_with_parameter(
			hwmgr,
			PPSMC_MSG_UVDPowerON,
			PP_CAP(PHM_Platक्रमmCaps_UVDDynamicPowerGating) ? 1 : 0,
			शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक  smu8_dpm_update_vce_dpm(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	काष्ठा phm_vce_घड़ी_voltage_dependency_table *ptable =
		hwmgr->dyn_state.vce_घड़ी_voltage_dependency_table;

	/* Stable Pstate is enabled and we need to set the VCE DPM to highest level */
	अगर (PP_CAP(PHM_Platक्रमmCaps_StablePState) ||
	    hwmgr->en_umd_pstate) अणु
		data->vce_dpm.hard_min_clk =
				  ptable->entries[ptable->count - 1].ecclk;

		smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetEclkHardMin,
			smu8_get_eclk_level(hwmgr,
				data->vce_dpm.hard_min_clk,
				PPSMC_MSG_SetEclkHardMin),
			शून्य);
	पूर्ण अन्यथा अणु

		smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetEclkHardMin,
					0,
					शून्य);
		/* disable ECLK DPM 0. Otherwise VCE could hang अगर
		 * चयनing SCLK from DPM 0 to 6/7 */
		smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetEclkSoftMin,
					1,
					शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu8_dpm_घातerकरोwn_vce(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (PP_CAP(PHM_Platक्रमmCaps_VCEPowerGating))
		वापस smum_send_msg_to_smc(hwmgr,
					    PPSMC_MSG_VCEPowerOFF,
					    शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक smu8_dpm_घातerup_vce(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (PP_CAP(PHM_Platक्रमmCaps_VCEPowerGating))
		वापस smum_send_msg_to_smc(hwmgr,
					    PPSMC_MSG_VCEPowerON,
					    शून्य);
	वापस 0;
पूर्ण

अटल uपूर्णांक32_t smu8_dpm_get_mclk(काष्ठा pp_hwmgr *hwmgr, bool low)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	वापस data->sys_info.bootup_uma_घड़ी;
पूर्ण

अटल uपूर्णांक32_t smu8_dpm_get_sclk(काष्ठा pp_hwmgr *hwmgr, bool low)
अणु
	काष्ठा pp_घातer_state  *ps;
	काष्ठा smu8_घातer_state  *smu8_ps;

	अगर (hwmgr == शून्य)
		वापस -EINVAL;

	ps = hwmgr->request_ps;

	अगर (ps == शून्य)
		वापस -EINVAL;

	smu8_ps = cast_smu8_घातer_state(&ps->hardware);

	अगर (low)
		वापस smu8_ps->levels[0].engineClock;
	अन्यथा
		वापस smu8_ps->levels[smu8_ps->level-1].engineClock;
पूर्ण

अटल पूर्णांक smu8_dpm_patch_boot_state(काष्ठा pp_hwmgr *hwmgr,
					काष्ठा pp_hw_घातer_state *hw_ps)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	काष्ठा smu8_घातer_state *smu8_ps = cast_smu8_घातer_state(hw_ps);

	smu8_ps->level = 1;
	smu8_ps->nbps_flags = 0;
	smu8_ps->bapm_flags = 0;
	smu8_ps->levels[0] = data->boot_घातer_level;

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_dpm_get_pp_table_entry_callback(
						     काष्ठा pp_hwmgr *hwmgr,
					   काष्ठा pp_hw_घातer_state *hw_ps,
							  अचिन्हित पूर्णांक index,
						     स्थिर व्योम *घड़ी_info)
अणु
	काष्ठा smu8_घातer_state *smu8_ps = cast_smu8_घातer_state(hw_ps);

	स्थिर ATOM_PPLIB_CZ_CLOCK_INFO *smu8_घड़ी_info = घड़ी_info;

	काष्ठा phm_घड़ी_voltage_dependency_table *table =
				    hwmgr->dyn_state.vddc_dependency_on_sclk;
	uपूर्णांक8_t घड़ी_info_index = smu8_घड़ी_info->index;

	अगर (घड़ी_info_index > (uपूर्णांक8_t)(hwmgr->platक्रमm_descriptor.hardwareActivityPerक्रमmanceLevels - 1))
		घड़ी_info_index = (uपूर्णांक8_t)(hwmgr->platक्रमm_descriptor.hardwareActivityPerक्रमmanceLevels - 1);

	smu8_ps->levels[index].engineClock = table->entries[घड़ी_info_index].clk;
	smu8_ps->levels[index].vddcIndex = (uपूर्णांक8_t)table->entries[घड़ी_info_index].v;

	smu8_ps->level = index + 1;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_SclkDeepSleep)) अणु
		smu8_ps->levels[index].dsDividerIndex = 5;
		smu8_ps->levels[index].ssDividerIndex = 5;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_dpm_get_num_of_pp_table_entries(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ ret = 0;

	result = pp_tables_get_num_of_entries(hwmgr, &ret);

	वापस result ? 0 : ret;
पूर्ण

अटल पूर्णांक smu8_dpm_get_pp_table_entry(काष्ठा pp_hwmgr *hwmgr,
		    अचिन्हित दीर्घ entry, काष्ठा pp_घातer_state *ps)
अणु
	पूर्णांक result;
	काष्ठा smu8_घातer_state *smu8_ps;

	ps->hardware.magic = smu8_magic;

	smu8_ps = cast_smu8_घातer_state(&(ps->hardware));

	result = pp_tables_get_entry(hwmgr, entry, ps,
			smu8_dpm_get_pp_table_entry_callback);

	smu8_ps->uvd_घड़ीs.vclk = ps->uvd_घड़ीs.VCLK;
	smu8_ps->uvd_घड़ीs.dclk = ps->uvd_घड़ीs.DCLK;

	वापस result;
पूर्ण

अटल पूर्णांक smu8_get_घातer_state_size(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस माप(काष्ठा smu8_घातer_state);
पूर्ण

अटल व्योम smu8_hw_prपूर्णांक_display_cfg(
	स्थिर काष्ठा cc6_settings *cc6_settings)
अणु
	PP_DBG_LOG("New Display Configuration:\n");

	PP_DBG_LOG("   cpu_cc6_disable: %d\n",
			cc6_settings->cpu_cc6_disable);
	PP_DBG_LOG("   cpu_pstate_disable: %d\n",
			cc6_settings->cpu_pstate_disable);
	PP_DBG_LOG("   nb_pstate_switch_disable: %d\n",
			cc6_settings->nb_pstate_चयन_disable);
	PP_DBG_LOG("   cpu_pstate_separation_time: %d\n\n",
			cc6_settings->cpu_pstate_separation_समय);
पूर्ण

 अटल पूर्णांक smu8_set_cpu_घातer_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_hwmgr *hw_data = hwmgr->backend;
	uपूर्णांक32_t data = 0;

	अगर (hw_data->cc6_settings.cc6_setting_changed) अणु

		hw_data->cc6_settings.cc6_setting_changed = false;

		smu8_hw_prपूर्णांक_display_cfg(&hw_data->cc6_settings);

		data |= (hw_data->cc6_settings.cpu_pstate_separation_समय
			& PWRMGT_SEPARATION_TIME_MASK)
			<< PWRMGT_SEPARATION_TIME_SHIFT;

		data |= (hw_data->cc6_settings.cpu_cc6_disable ? 0x1 : 0x0)
			<< PWRMGT_DISABLE_CPU_CSTATES_SHIFT;

		data |= (hw_data->cc6_settings.cpu_pstate_disable ? 0x1 : 0x0)
			<< PWRMGT_DISABLE_CPU_PSTATES_SHIFT;

		PP_DBG_LOG("SetDisplaySizePowerParams data: 0x%X\n",
			data);

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetDisplaySizePowerParams,
						data,
						शून्य);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक smu8_store_cc6_data(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t separation_समय,
			bool cc6_disable, bool pstate_disable, bool pstate_चयन_disable)
अणु
	काष्ठा smu8_hwmgr *hw_data = hwmgr->backend;

	अगर (separation_समय !=
	    hw_data->cc6_settings.cpu_pstate_separation_समय ||
	    cc6_disable != hw_data->cc6_settings.cpu_cc6_disable ||
	    pstate_disable != hw_data->cc6_settings.cpu_pstate_disable ||
	    pstate_चयन_disable != hw_data->cc6_settings.nb_pstate_चयन_disable) अणु

		hw_data->cc6_settings.cc6_setting_changed = true;

		hw_data->cc6_settings.cpu_pstate_separation_समय =
			separation_समय;
		hw_data->cc6_settings.cpu_cc6_disable =
			cc6_disable;
		hw_data->cc6_settings.cpu_pstate_disable =
			pstate_disable;
		hw_data->cc6_settings.nb_pstate_चयन_disable =
			pstate_चयन_disable;

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_get_dal_घातer_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा amd_pp_simple_घड़ी_info *info)
अणु
	uपूर्णांक32_t i;
	स्थिर काष्ठा phm_घड़ी_voltage_dependency_table *table =
			hwmgr->dyn_state.vddc_dep_on_dal_pwrl;
	स्थिर काष्ठा phm_घड़ी_and_voltage_limits *limits =
			&hwmgr->dyn_state.max_घड़ी_voltage_on_ac;

	info->engine_max_घड़ी = limits->sclk;
	info->memory_max_घड़ी = limits->mclk;

	क्रम (i = table->count - 1; i > 0; i--) अणु
		अगर (limits->vddc >= table->entries[i].v) अणु
			info->level = table->entries[i].clk;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक smu8_क्रमce_घड़ी_level(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, uपूर्णांक32_t mask)
अणु
	चयन (type) अणु
	हाल PP_SCLK:
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSclkSoftMin,
				mask,
				शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSclkSoftMax,
				mask,
				शून्य);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_prपूर्णांक_घड़ी_levels(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, अक्षर *buf)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	काष्ठा phm_घड़ी_voltage_dependency_table *sclk_table =
			hwmgr->dyn_state.vddc_dependency_on_sclk;
	पूर्णांक i, now, size = 0;

	चयन (type) अणु
	हाल PP_SCLK:
		now = PHM_GET_FIELD(cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device,
				CGS_IND_REG__SMC,
				ixTARGET_AND_CURRENT_PROखाता_INDEX),
				TARGET_AND_CURRENT_PROखाता_INDEX,
				CURR_SCLK_INDEX);

		क्रम (i = 0; i < sclk_table->count; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
					i, sclk_table->entries[i].clk / 100,
					(i == now) ? "*" : "");
		अवरोध;
	हाल PP_MCLK:
		now = PHM_GET_FIELD(cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device,
				CGS_IND_REG__SMC,
				ixTARGET_AND_CURRENT_PROखाता_INDEX),
				TARGET_AND_CURRENT_PROखाता_INDEX,
				CURR_MCLK_INDEX);

		क्रम (i = SMU8_NUM_NBPMEMORYCLOCK; i > 0; i--)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
					SMU8_NUM_NBPMEMORYCLOCK-i, data->sys_info.nbp_memory_घड़ी[i-1] / 100,
					(SMU8_NUM_NBPMEMORYCLOCK-i == now) ? "*" : "");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस size;
पूर्ण

अटल पूर्णांक smu8_get_perक्रमmance_level(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा pp_hw_घातer_state *state,
				PHM_Perक्रमmanceLevelDesignation designation, uपूर्णांक32_t index,
				PHM_Perक्रमmanceLevel *level)
अणु
	स्थिर काष्ठा smu8_घातer_state *ps;
	काष्ठा smu8_hwmgr *data;
	uपूर्णांक32_t level_index;
	uपूर्णांक32_t i;

	अगर (level == शून्य || hwmgr == शून्य || state == शून्य)
		वापस -EINVAL;

	data = hwmgr->backend;
	ps = cast_स्थिर_smu8_घातer_state(state);

	level_index = index > ps->level - 1 ? ps->level - 1 : index;
	level->coreClock = ps->levels[level_index].engineClock;

	अगर (designation == PHM_Perक्रमmanceLevelDesignation_PowerContainment) अणु
		क्रम (i = 1; i < ps->level; i++) अणु
			अगर (ps->levels[i].engineClock > data->dce_slow_sclk_threshold) अणु
				level->coreClock = ps->levels[i].engineClock;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (level_index == 0)
		level->memory_घड़ी = data->sys_info.nbp_memory_घड़ी[SMU8_NUM_NBPMEMORYCLOCK - 1];
	अन्यथा
		level->memory_घड़ी = data->sys_info.nbp_memory_घड़ी[0];

	level->vddc = (smu8_convert_8Bit_index_to_voltage(hwmgr, ps->levels[level_index].vddcIndex) + 2) / 4;
	level->nonLocalMemoryFreq = 0;
	level->nonLocalMemoryWidth = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_get_current_shallow_sleep_घड़ीs(काष्ठा pp_hwmgr *hwmgr,
	स्थिर काष्ठा pp_hw_घातer_state *state, काष्ठा pp_घड़ी_info *घड़ी_info)
अणु
	स्थिर काष्ठा smu8_घातer_state *ps = cast_स्थिर_smu8_घातer_state(state);

	घड़ी_info->min_eng_clk = ps->levels[0].engineClock / (1 << (ps->levels[0].ssDividerIndex));
	घड़ी_info->max_eng_clk = ps->levels[ps->level - 1].engineClock / (1 << (ps->levels[ps->level - 1].ssDividerIndex));

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_get_घड़ी_by_type(काष्ठा pp_hwmgr *hwmgr, क्रमागत amd_pp_घड़ी_प्रकारype type,
						काष्ठा amd_pp_घड़ीs *घड़ीs)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	पूर्णांक i;
	काष्ठा phm_घड़ी_voltage_dependency_table *table;

	घड़ीs->count = smu8_get_max_sclk_level(hwmgr);
	चयन (type) अणु
	हाल amd_pp_disp_घड़ी:
		क्रम (i = 0; i < घड़ीs->count; i++)
			घड़ीs->घड़ी[i] = data->sys_info.display_घड़ी[i] * 10;
		अवरोध;
	हाल amd_pp_sys_घड़ी:
		table = hwmgr->dyn_state.vddc_dependency_on_sclk;
		क्रम (i = 0; i < घड़ीs->count; i++)
			घड़ीs->घड़ी[i] = table->entries[i].clk * 10;
		अवरोध;
	हाल amd_pp_mem_घड़ी:
		घड़ीs->count = SMU8_NUM_NBPMEMORYCLOCK;
		क्रम (i = 0; i < घड़ीs->count; i++)
			घड़ीs->घड़ी[i] = data->sys_info.nbp_memory_घड़ी[घड़ीs->count - 1 - i] * 10;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_get_max_high_घड़ीs(काष्ठा pp_hwmgr *hwmgr, काष्ठा amd_pp_simple_घड़ी_info *घड़ीs)
अणु
	काष्ठा phm_घड़ी_voltage_dependency_table *table =
					hwmgr->dyn_state.vddc_dependency_on_sclk;
	अचिन्हित दीर्घ level;
	स्थिर काष्ठा phm_घड़ी_and_voltage_limits *limits =
			&hwmgr->dyn_state.max_घड़ी_voltage_on_ac;

	अगर ((शून्य == table) || (table->count <= 0) || (घड़ीs == शून्य))
		वापस -EINVAL;

	level = smu8_get_max_sclk_level(hwmgr) - 1;

	अगर (level < table->count)
		घड़ीs->engine_max_घड़ी = table->entries[level].clk;
	अन्यथा
		घड़ीs->engine_max_घड़ी = table->entries[table->count - 1].clk;

	घड़ीs->memory_max_घड़ी = limits->mclk;

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_thermal_get_temperature(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक actual_temp = 0;
	uपूर्णांक32_t val = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device,
					     CGS_IND_REG__SMC, ixTHM_TCON_CUR_TMP);
	uपूर्णांक32_t temp = PHM_GET_FIELD(val, THM_TCON_CUR_TMP, CUR_TEMP);

	अगर (PHM_GET_FIELD(val, THM_TCON_CUR_TMP, CUR_TEMP_RANGE_SEL))
		actual_temp = ((temp / 8) - 49) * PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	अन्यथा
		actual_temp = (temp / 8) * PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	वापस actual_temp;
पूर्ण

अटल पूर्णांक smu8_पढ़ो_sensor(काष्ठा pp_hwmgr *hwmgr, पूर्णांक idx,
			  व्योम *value, पूर्णांक *size)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	काष्ठा phm_घड़ी_voltage_dependency_table *table =
				hwmgr->dyn_state.vddc_dependency_on_sclk;

	काष्ठा phm_vce_घड़ी_voltage_dependency_table *vce_table =
		hwmgr->dyn_state.vce_घड़ी_voltage_dependency_table;

	काष्ठा phm_uvd_घड़ी_voltage_dependency_table *uvd_table =
		hwmgr->dyn_state.uvd_घड़ी_voltage_dependency_table;

	uपूर्णांक32_t sclk_index = PHM_GET_FIELD(cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixTARGET_AND_CURRENT_PROखाता_INDEX),
					TARGET_AND_CURRENT_PROखाता_INDEX, CURR_SCLK_INDEX);
	uपूर्णांक32_t uvd_index = PHM_GET_FIELD(cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixTARGET_AND_CURRENT_PROखाता_INDEX_2),
					TARGET_AND_CURRENT_PROखाता_INDEX_2, CURR_UVD_INDEX);
	uपूर्णांक32_t vce_index = PHM_GET_FIELD(cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixTARGET_AND_CURRENT_PROखाता_INDEX_2),
					TARGET_AND_CURRENT_PROखाता_INDEX_2, CURR_VCE_INDEX);

	uपूर्णांक32_t sclk, vclk, dclk, ecclk, पंचांगp, activity_percent;
	uपूर्णांक16_t vddnb, vddgfx;
	पूर्णांक result;

	/* size must be at least 4 bytes क्रम all sensors */
	अगर (*size < 4)
		वापस -EINVAL;
	*size = 4;

	चयन (idx) अणु
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		अगर (sclk_index < NUM_SCLK_LEVELS) अणु
			sclk = table->entries[sclk_index].clk;
			*((uपूर्णांक32_t *)value) = sclk;
			वापस 0;
		पूर्ण
		वापस -EINVAL;
	हाल AMDGPU_PP_SENSOR_VDDNB:
		पंचांगp = (cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixSMUSVI_NB_CURRENTVID) &
			CURRENT_NB_VID_MASK) >> CURRENT_NB_VID__SHIFT;
		vddnb = smu8_convert_8Bit_index_to_voltage(hwmgr, पंचांगp) / 4;
		*((uपूर्णांक32_t *)value) = vddnb;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_VDDGFX:
		पंचांगp = (cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixSMUSVI_GFX_CURRENTVID) &
			CURRENT_GFX_VID_MASK) >> CURRENT_GFX_VID__SHIFT;
		vddgfx = smu8_convert_8Bit_index_to_voltage(hwmgr, (u16)पंचांगp) / 4;
		*((uपूर्णांक32_t *)value) = vddgfx;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_UVD_VCLK:
		अगर (!data->uvd_घातer_gated) अणु
			अगर (uvd_index >= SMU8_MAX_HARDWARE_POWERLEVELS) अणु
				वापस -EINVAL;
			पूर्ण अन्यथा अणु
				vclk = uvd_table->entries[uvd_index].vclk;
				*((uपूर्णांक32_t *)value) = vclk;
				वापस 0;
			पूर्ण
		पूर्ण
		*((uपूर्णांक32_t *)value) = 0;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_UVD_DCLK:
		अगर (!data->uvd_घातer_gated) अणु
			अगर (uvd_index >= SMU8_MAX_HARDWARE_POWERLEVELS) अणु
				वापस -EINVAL;
			पूर्ण अन्यथा अणु
				dclk = uvd_table->entries[uvd_index].dclk;
				*((uपूर्णांक32_t *)value) = dclk;
				वापस 0;
			पूर्ण
		पूर्ण
		*((uपूर्णांक32_t *)value) = 0;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_VCE_ECCLK:
		अगर (!data->vce_घातer_gated) अणु
			अगर (vce_index >= SMU8_MAX_HARDWARE_POWERLEVELS) अणु
				वापस -EINVAL;
			पूर्ण अन्यथा अणु
				ecclk = vce_table->entries[vce_index].ecclk;
				*((uपूर्णांक32_t *)value) = ecclk;
				वापस 0;
			पूर्ण
		पूर्ण
		*((uपूर्णांक32_t *)value) = 0;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
		result = smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_GetAverageGraphicsActivity,
				&activity_percent);
		अगर (0 == result)
			activity_percent = activity_percent > 100 ? 100 : activity_percent;
		अन्यथा
			वापस -EIO;
		*((uपूर्णांक32_t *)value) = activity_percent;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_UVD_POWER:
		*((uपूर्णांक32_t *)value) = data->uvd_घातer_gated ? 0 : 1;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_VCE_POWER:
		*((uपूर्णांक32_t *)value) = data->vce_घातer_gated ? 0 : 1;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_GPU_TEMP:
		*((uपूर्णांक32_t *)value) = smu8_thermal_get_temperature(hwmgr);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक smu8_notअगरy_cac_buffer_info(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक32_t भव_addr_low,
					uपूर्णांक32_t भव_addr_hi,
					uपूर्णांक32_t mc_addr_low,
					uपूर्णांक32_t mc_addr_hi,
					uपूर्णांक32_t size)
अणु
	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DramAddrHiVirtual,
					mc_addr_hi,
					शून्य);
	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DramAddrLoVirtual,
					mc_addr_low,
					शून्य);
	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DramAddrHiPhysical,
					भव_addr_hi,
					शून्य);
	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DramAddrLoPhysical,
					भव_addr_low,
					शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DramBufferSize,
					size,
					शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक smu8_get_thermal_temperature_range(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा PP_TemperatureRange *thermal_data)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	स_नकल(thermal_data, &SMU7ThermalPolicy[0], माप(काष्ठा PP_TemperatureRange));

	thermal_data->max = (data->thermal_स्वतः_throttling_treshold +
			data->sys_info.htc_hyst_lmt) *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_enable_disable_uvd_dpm(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t dpm_features = 0;

	अगर (enable &&
		phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				  PHM_Platक्रमmCaps_UVDDPM)) अणु
		data->dpm_flags |= DPMFlags_UVD_Enabled;
		dpm_features |= UVD_DPM_MASK;
		smum_send_msg_to_smc_with_parameter(hwmgr,
			    PPSMC_MSG_EnableAllSmuFeatures,
			    dpm_features,
			    शून्य);
	पूर्ण अन्यथा अणु
		dpm_features |= UVD_DPM_MASK;
		data->dpm_flags &= ~DPMFlags_UVD_Enabled;
		smum_send_msg_to_smc_with_parameter(hwmgr,
			   PPSMC_MSG_DisableAllSmuFeatures,
			   dpm_features,
			   शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu8_dpm_update_uvd_dpm(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	काष्ठा phm_uvd_घड़ी_voltage_dependency_table *ptable =
		hwmgr->dyn_state.uvd_घड़ी_voltage_dependency_table;

	अगर (!bgate) अणु
		/* Stable Pstate is enabled and we need to set the UVD DPM to highest level */
		अगर (PP_CAP(PHM_Platक्रमmCaps_StablePState) ||
		    hwmgr->en_umd_pstate) अणु
			data->uvd_dpm.hard_min_clk =
				   ptable->entries[ptable->count - 1].vclk;

			smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetUvdHardMin,
				smu8_get_uvd_level(hwmgr,
					data->uvd_dpm.hard_min_clk,
					PPSMC_MSG_SetUvdHardMin),
				शून्य);

			smu8_enable_disable_uvd_dpm(hwmgr, true);
		पूर्ण अन्यथा अणु
			smu8_enable_disable_uvd_dpm(hwmgr, true);
		पूर्ण
	पूर्ण अन्यथा अणु
		smu8_enable_disable_uvd_dpm(hwmgr, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_enable_disable_vce_dpm(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t dpm_features = 0;

	अगर (enable && phm_cap_enabled(
				hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_VCEDPM)) अणु
		data->dpm_flags |= DPMFlags_VCE_Enabled;
		dpm_features |= VCE_DPM_MASK;
		smum_send_msg_to_smc_with_parameter(hwmgr,
			    PPSMC_MSG_EnableAllSmuFeatures,
			    dpm_features,
			    शून्य);
	पूर्ण अन्यथा अणु
		dpm_features |= VCE_DPM_MASK;
		data->dpm_flags &= ~DPMFlags_VCE_Enabled;
		smum_send_msg_to_smc_with_parameter(hwmgr,
			   PPSMC_MSG_DisableAllSmuFeatures,
			   dpm_features,
			   शून्य);
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम smu8_dpm_घातergate_acp(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	अगर (data->acp_घातer_gated == bgate)
		वापस;

	अगर (bgate)
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ACPPowerOFF, शून्य);
	अन्यथा
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ACPPowerON, शून्य);
पूर्ण

अटल व्योम smu8_dpm_घातergate_uvd(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	data->uvd_घातer_gated = bgate;

	अगर (bgate) अणु
		amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_UVD,
						AMD_PG_STATE_GATE);
		amdgpu_device_ip_set_घड़ीgating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_UVD,
						AMD_CG_STATE_GATE);
		smu8_dpm_update_uvd_dpm(hwmgr, true);
		smu8_dpm_घातerकरोwn_uvd(hwmgr);
	पूर्ण अन्यथा अणु
		smu8_dpm_घातerup_uvd(hwmgr);
		amdgpu_device_ip_set_घड़ीgating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_UVD,
						AMD_CG_STATE_UNGATE);
		amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_UVD,
						AMD_PG_STATE_UNGATE);
		smu8_dpm_update_uvd_dpm(hwmgr, false);
	पूर्ण

पूर्ण

अटल व्योम smu8_dpm_घातergate_vce(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	काष्ठा smu8_hwmgr *data = hwmgr->backend;

	अगर (bgate) अणु
		amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
					AMD_IP_BLOCK_TYPE_VCE,
					AMD_PG_STATE_GATE);
		amdgpu_device_ip_set_घड़ीgating_state(hwmgr->adev,
					AMD_IP_BLOCK_TYPE_VCE,
					AMD_CG_STATE_GATE);
		smu8_enable_disable_vce_dpm(hwmgr, false);
		smu8_dpm_घातerकरोwn_vce(hwmgr);
		data->vce_घातer_gated = true;
	पूर्ण अन्यथा अणु
		smu8_dpm_घातerup_vce(hwmgr);
		data->vce_घातer_gated = false;
		amdgpu_device_ip_set_घड़ीgating_state(hwmgr->adev,
					AMD_IP_BLOCK_TYPE_VCE,
					AMD_CG_STATE_UNGATE);
		amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
					AMD_IP_BLOCK_TYPE_VCE,
					AMD_PG_STATE_UNGATE);
		smu8_dpm_update_vce_dpm(hwmgr);
		smu8_enable_disable_vce_dpm(hwmgr, true);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pp_hwmgr_func smu8_hwmgr_funcs = अणु
	.backend_init = smu8_hwmgr_backend_init,
	.backend_fini = smu8_hwmgr_backend_fini,
	.apply_state_adjust_rules = smu8_apply_state_adjust_rules,
	.क्रमce_dpm_level = smu8_dpm_क्रमce_dpm_level,
	.get_घातer_state_size = smu8_get_घातer_state_size,
	.घातerकरोwn_uvd = smu8_dpm_घातerकरोwn_uvd,
	.घातergate_uvd = smu8_dpm_घातergate_uvd,
	.घातergate_vce = smu8_dpm_घातergate_vce,
	.घातergate_acp = smu8_dpm_घातergate_acp,
	.get_mclk = smu8_dpm_get_mclk,
	.get_sclk = smu8_dpm_get_sclk,
	.patch_boot_state = smu8_dpm_patch_boot_state,
	.get_pp_table_entry = smu8_dpm_get_pp_table_entry,
	.get_num_of_pp_table_entries = smu8_dpm_get_num_of_pp_table_entries,
	.set_cpu_घातer_state = smu8_set_cpu_घातer_state,
	.store_cc6_data = smu8_store_cc6_data,
	.क्रमce_घड़ी_level = smu8_क्रमce_घड़ी_level,
	.prपूर्णांक_घड़ी_levels = smu8_prपूर्णांक_घड़ी_levels,
	.get_dal_घातer_level = smu8_get_dal_घातer_level,
	.get_perक्रमmance_level = smu8_get_perक्रमmance_level,
	.get_current_shallow_sleep_घड़ीs = smu8_get_current_shallow_sleep_घड़ीs,
	.get_घड़ी_by_type = smu8_get_घड़ी_by_type,
	.get_max_high_घड़ीs = smu8_get_max_high_घड़ीs,
	.पढ़ो_sensor = smu8_पढ़ो_sensor,
	.घातer_off_asic = smu8_घातer_off_asic,
	.asic_setup = smu8_setup_asic_task,
	.dynamic_state_management_enable = smu8_enable_dpm_tasks,
	.घातer_state_set = smu8_set_घातer_state_tasks,
	.dynamic_state_management_disable = smu8_disable_dpm_tasks,
	.notअगरy_cac_buffer_info = smu8_notअगरy_cac_buffer_info,
	.update_nbdpm_pstate = smu8_nbdpm_pstate_enable_disable,
	.get_thermal_temperature_range = smu8_get_thermal_temperature_range,
पूर्ण;

पूर्णांक smu8_init_function_poपूर्णांकers(काष्ठा pp_hwmgr *hwmgr)
अणु
	hwmgr->hwmgr_func = &smu8_hwmgr_funcs;
	hwmgr->pptable_func = &pptable_funcs;
	वापस 0;
पूर्ण
