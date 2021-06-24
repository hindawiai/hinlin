<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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

#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "hwmgr.h"
#समावेश "amd_powerplay.h"
#समावेश "vega12_smumgr.h"
#समावेश "hardwaremanager.h"
#समावेश "ppatomfwctrl.h"
#समावेश "atomfirmware.h"
#समावेश "cgs_common.h"
#समावेश "vega12_inc.h"
#समावेश "pppcielanes.h"
#समावेश "vega12_hwmgr.h"
#समावेश "vega12_processpptables.h"
#समावेश "vega12_pptable.h"
#समावेश "vega12_thermal.h"
#समावेश "vega12_ppsmc.h"
#समावेश "pp_debug.h"
#समावेश "amd_pcie_helpers.h"
#समावेश "ppinterrupt.h"
#समावेश "pp_overdriver.h"
#समावेश "pp_thermal.h"
#समावेश "vega12_baco.h"

#घोषणा smnPCIE_LC_SPEED_CNTL			0x11140290
#घोषणा smnPCIE_LC_LINK_WIDTH_CNTL		0x11140288

#घोषणा LINK_WIDTH_MAX				6
#घोषणा LINK_SPEED_MAX				3
अटल स्थिर पूर्णांक link_width[] = अणु0, 1, 2, 4, 8, 12, 16पूर्ण;
अटल स्थिर पूर्णांक link_speed[] = अणु25, 50, 80, 160पूर्ण;

अटल पूर्णांक vega12_क्रमce_घड़ी_level(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, uपूर्णांक32_t mask);
अटल पूर्णांक vega12_get_घड़ी_ranges(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t *घड़ी,
		PPCLK_e घड़ी_select,
		bool max);

अटल व्योम vega12_set_शेष_registry_data(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);

	data->gfxclk_average_alpha = PPVEGA12_VEGA12GFXCLKAVERAGEALPHA_DFLT;
	data->socclk_average_alpha = PPVEGA12_VEGA12SOCCLKAVERAGEALPHA_DFLT;
	data->uclk_average_alpha = PPVEGA12_VEGA12UCLKCLKAVERAGEALPHA_DFLT;
	data->gfx_activity_average_alpha = PPVEGA12_VEGA12GFXACTIVITYAVERAGEALPHA_DFLT;
	data->lowest_uclk_reserved_क्रम_ulv = PPVEGA12_VEGA12LOWESTUCLKRESERVEDFORULV_DFLT;

	data->display_voltage_mode = PPVEGA12_VEGA12DISPLAYVOLTAGEMODE_DFLT;
	data->dcef_clk_quad_eqn_a = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->dcef_clk_quad_eqn_b = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->dcef_clk_quad_eqn_c = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_a = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_b = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_c = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_a = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_b = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_c = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_a = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_b = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_c = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;

	data->registry_data.disallowed_features = 0x0;
	data->registry_data.od_state_in_dc_support = 0;
	data->registry_data.thermal_support = 1;
	data->registry_data.skip_baco_hardware = 0;

	data->registry_data.log_avfs_param = 0;
	data->registry_data.sclk_throttle_low_notअगरication = 1;
	data->registry_data.क्रमce_dpm_high = 0;
	data->registry_data.stable_pstate_sclk_dpm_percentage = 75;

	data->registry_data.didt_support = 0;
	अगर (data->registry_data.didt_support) अणु
		data->registry_data.didt_mode = 6;
		data->registry_data.sq_ramping_support = 1;
		data->registry_data.db_ramping_support = 0;
		data->registry_data.td_ramping_support = 0;
		data->registry_data.tcp_ramping_support = 0;
		data->registry_data.dbr_ramping_support = 0;
		data->registry_data.edc_didt_support = 1;
		data->registry_data.gc_didt_support = 0;
		data->registry_data.psm_didt_support = 0;
	पूर्ण

	data->registry_data.pcie_lane_override = 0xff;
	data->registry_data.pcie_speed_override = 0xff;
	data->registry_data.pcie_घड़ी_override = 0xffffffff;
	data->registry_data.regulator_hot_gpio_support = 1;
	data->registry_data.ac_dc_चयन_gpio_support = 0;
	data->registry_data.quick_transition_support = 0;
	data->registry_data.zrpm_start_temp = 0xffff;
	data->registry_data.zrpm_stop_temp = 0xffff;
	data->registry_data.odn_feature_enable = 1;
	data->registry_data.disable_water_mark = 0;
	data->registry_data.disable_pp_tuning = 0;
	data->registry_data.disable_xlpp_tuning = 0;
	data->registry_data.disable_workload_policy = 0;
	data->registry_data.perf_ui_tuning_profile_turbo = 0x19190F0F;
	data->registry_data.perf_ui_tuning_profile_घातerSave = 0x19191919;
	data->registry_data.perf_ui_tuning_profile_xl = 0x00000F0A;
	data->registry_data.क्रमce_workload_policy_mask = 0;
	data->registry_data.disable_3d_fs_detection = 0;
	data->registry_data.fps_support = 1;
	data->registry_data.disable_स्वतः_watपंचांगan = 1;
	data->registry_data.स्वतः_watपंचांगan_debug = 0;
	data->registry_data.स्वतः_watपंचांगan_sample_period = 100;
	data->registry_data.स्वतः_watपंचांगan_threshold = 50;
	data->registry_data.pcie_dpm_key_disabled = !(hwmgr->feature_mask & PP_PCIE_DPM_MASK);
पूर्ण

अटल पूर्णांक vega12_set_features_platक्रमm_caps(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	अगर (data->vddci_control == VEGA12_VOLTAGE_CONTROL_NONE)
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_ControlVDDCI);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_TablelessHardwareInterface);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_EnableSMU7ThermalManagement);

	अगर (adev->pg_flags & AMD_PG_SUPPORT_UVD) अणु
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_UVDPowerGating);
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_UVDDynamicPowerGating);
	पूर्ण

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCE)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_VCEPowerGating);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_UnTabledHardwareInterface);

	अगर (data->registry_data.odn_feature_enable)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_ODNinACSupport);
	अन्यथा अणु
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_OD6inACSupport);
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_OD6PlusinACSupport);
	पूर्ण

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ActivityReporting);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_FanSpeedInTableIsRPM);

	अगर (data->registry_data.od_state_in_dc_support) अणु
		अगर (data->registry_data.odn_feature_enable)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_ODNinDCSupport);
		अन्यथा अणु
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_OD6inDCSupport);
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_OD6PlusinDCSupport);
		पूर्ण
	पूर्ण

	अगर (data->registry_data.thermal_support
			&& data->registry_data.fuzzy_fan_control_support
			&& hwmgr->thermal_controller.advanceFanControlParameters.usTMax)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_ODFuzzyFanControlSupport);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_DynamicPowerManagement);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SMC);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ThermalPolicyDelay);

	अगर (data->registry_data.क्रमce_dpm_high)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_ExclusiveModeAlwaysHigh);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_DynamicUVDState);

	अगर (data->registry_data.sclk_throttle_low_notअगरication)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_SclkThrottleLowNotअगरication);

	/* घातer tune caps */
	/* assume disabled */
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_PowerContainment);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_DiDtSupport);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SQRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_DBRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_TDRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_TCPRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_DBRRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_DiDtEDCEnable);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_GCEDC);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_PSM);

	अगर (data->registry_data.didt_support) अणु
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_DiDtSupport);
		अगर (data->registry_data.sq_ramping_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_SQRamping);
		अगर (data->registry_data.db_ramping_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_DBRamping);
		अगर (data->registry_data.td_ramping_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_TDRamping);
		अगर (data->registry_data.tcp_ramping_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_TCPRamping);
		अगर (data->registry_data.dbr_ramping_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_DBRRamping);
		अगर (data->registry_data.edc_didt_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_DiDtEDCEnable);
		अगर (data->registry_data.gc_didt_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_GCEDC);
		अगर (data->registry_data.psm_didt_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_PSM);
	पूर्ण

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_RegulatorHot);

	अगर (data->registry_data.ac_dc_चयन_gpio_support) अणु
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_AutomaticDCTransition);
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_SMCtoPPLIBAcdcGpioScheme);
	पूर्ण

	अगर (data->registry_data.quick_transition_support) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_AutomaticDCTransition);
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_SMCtoPPLIBAcdcGpioScheme);
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_Falcon_QuickTransition);
	पूर्ण

	अगर (data->lowest_uclk_reserved_क्रम_ulv != PPVEGA12_VEGA12LOWESTUCLKRESERVEDFORULV_DFLT) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_LowestUclkReservedForUlv);
		अगर (data->lowest_uclk_reserved_क्रम_ulv == 1)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_LowestUclkReservedForUlv);
	पूर्ण

	अगर (data->registry_data.custom_fan_support)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_CustomFanControlSupport);

	वापस 0;
पूर्ण

अटल व्योम vega12_init_dpm_शेषs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t top32, bottom32;
	पूर्णांक i;

	data->smu_features[GNLD_DPM_PREFETCHER].smu_feature_id =
			FEATURE_DPM_PREFETCHER_BIT;
	data->smu_features[GNLD_DPM_GFXCLK].smu_feature_id =
			FEATURE_DPM_GFXCLK_BIT;
	data->smu_features[GNLD_DPM_UCLK].smu_feature_id =
			FEATURE_DPM_UCLK_BIT;
	data->smu_features[GNLD_DPM_SOCCLK].smu_feature_id =
			FEATURE_DPM_SOCCLK_BIT;
	data->smu_features[GNLD_DPM_UVD].smu_feature_id =
			FEATURE_DPM_UVD_BIT;
	data->smu_features[GNLD_DPM_VCE].smu_feature_id =
			FEATURE_DPM_VCE_BIT;
	data->smu_features[GNLD_ULV].smu_feature_id =
			FEATURE_ULV_BIT;
	data->smu_features[GNLD_DPM_MP0CLK].smu_feature_id =
			FEATURE_DPM_MP0CLK_BIT;
	data->smu_features[GNLD_DPM_LINK].smu_feature_id =
			FEATURE_DPM_LINK_BIT;
	data->smu_features[GNLD_DPM_DCEFCLK].smu_feature_id =
			FEATURE_DPM_DCEFCLK_BIT;
	data->smu_features[GNLD_DS_GFXCLK].smu_feature_id =
			FEATURE_DS_GFXCLK_BIT;
	data->smu_features[GNLD_DS_SOCCLK].smu_feature_id =
			FEATURE_DS_SOCCLK_BIT;
	data->smu_features[GNLD_DS_LCLK].smu_feature_id =
			FEATURE_DS_LCLK_BIT;
	data->smu_features[GNLD_PPT].smu_feature_id =
			FEATURE_PPT_BIT;
	data->smu_features[GNLD_TDC].smu_feature_id =
			FEATURE_TDC_BIT;
	data->smu_features[GNLD_THERMAL].smu_feature_id =
			FEATURE_THERMAL_BIT;
	data->smu_features[GNLD_GFX_PER_CU_CG].smu_feature_id =
			FEATURE_GFX_PER_CU_CG_BIT;
	data->smu_features[GNLD_RM].smu_feature_id =
			FEATURE_RM_BIT;
	data->smu_features[GNLD_DS_DCEFCLK].smu_feature_id =
			FEATURE_DS_DCEFCLK_BIT;
	data->smu_features[GNLD_ACDC].smu_feature_id =
			FEATURE_ACDC_BIT;
	data->smu_features[GNLD_VR0HOT].smu_feature_id =
			FEATURE_VR0HOT_BIT;
	data->smu_features[GNLD_VR1HOT].smu_feature_id =
			FEATURE_VR1HOT_BIT;
	data->smu_features[GNLD_FW_CTF].smu_feature_id =
			FEATURE_FW_CTF_BIT;
	data->smu_features[GNLD_LED_DISPLAY].smu_feature_id =
			FEATURE_LED_DISPLAY_BIT;
	data->smu_features[GNLD_FAN_CONTROL].smu_feature_id =
			FEATURE_FAN_CONTROL_BIT;
	data->smu_features[GNLD_DIDT].smu_feature_id = FEATURE_GFX_EDC_BIT;
	data->smu_features[GNLD_GFXOFF].smu_feature_id = FEATURE_GFXOFF_BIT;
	data->smu_features[GNLD_CG].smu_feature_id = FEATURE_CG_BIT;
	data->smu_features[GNLD_ACG].smu_feature_id = FEATURE_ACG_BIT;

	क्रम (i = 0; i < GNLD_FEATURES_MAX; i++) अणु
		data->smu_features[i].smu_feature_biपंचांगap =
			(uपूर्णांक64_t)(1ULL << data->smu_features[i].smu_feature_id);
		data->smu_features[i].allowed =
			((data->registry_data.disallowed_features >> i) & 1) ?
			false : true;
	पूर्ण

	/* Get the SN to turn पूर्णांकo a Unique ID */
	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ReadSerialNumTop32, &top32);
	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ReadSerialNumBottom32, &bottom32);

	adev->unique_id = ((uपूर्णांक64_t)bottom32 << 32) | top32;
पूर्ण

अटल पूर्णांक vega12_set_निजी_data_based_on_pptable(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vega12_hwmgr_backend_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	kमुक्त(hwmgr->backend);
	hwmgr->backend = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_hwmgr_backend_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	काष्ठा vega12_hwmgr *data;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	data = kzalloc(माप(काष्ठा vega12_hwmgr), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	hwmgr->backend = data;

	vega12_set_शेष_registry_data(hwmgr);

	data->disable_dpm_mask = 0xff;
	data->workload_mask = 0xff;

	/* need to set voltage control types beक्रमe EVV patching */
	data->vddc_control = VEGA12_VOLTAGE_CONTROL_NONE;
	data->mvdd_control = VEGA12_VOLTAGE_CONTROL_NONE;
	data->vddci_control = VEGA12_VOLTAGE_CONTROL_NONE;

	data->water_marks_biपंचांगap = 0;
	data->avfs_exist = false;

	vega12_set_features_platक्रमm_caps(hwmgr);

	vega12_init_dpm_शेषs(hwmgr);

	/* Parse pptable data पढ़ो from VBIOS */
	vega12_set_निजी_data_based_on_pptable(hwmgr);

	data->is_tlu_enabled = false;

	hwmgr->platक्रमm_descriptor.hardwareActivityPerक्रमmanceLevels =
			VEGA12_MAX_HARDWARE_POWERLEVELS;
	hwmgr->platक्रमm_descriptor.hardwarePerक्रमmanceLevels = 2;
	hwmgr->platक्रमm_descriptor.minimumClocksReductionPercentage = 50;

	hwmgr->platक्रमm_descriptor.vbiosInterruptId = 0x20000400; /* IRQ_SOURCE1_SW_INT */
	/* The true घड़ी step depends on the frequency, typically 4.5 or 9 MHz. Here we use 5. */
	hwmgr->platक्रमm_descriptor.घड़ीStep.engineClock = 500;
	hwmgr->platक्रमm_descriptor.घड़ीStep.memoryClock = 500;

	data->total_active_cus = adev->gfx.cu_info.number;
	/* Setup शेष Overdrive Fan control settings */
	data->odn_fan_table.target_fan_speed =
			hwmgr->thermal_controller.advanceFanControlParameters.usMaxFanRPM;
	data->odn_fan_table.target_temperature =
			hwmgr->thermal_controller.advanceFanControlParameters.ucTargetTemperature;
	data->odn_fan_table.min_perक्रमmance_घड़ी =
			hwmgr->thermal_controller.advanceFanControlParameters.ulMinFanSCLKAcousticLimit;
	data->odn_fan_table.min_fan_limit =
			hwmgr->thermal_controller.advanceFanControlParameters.usFanPWMMinLimit *
			hwmgr->thermal_controller.fanInfo.ulMaxRPM / 100;

	अगर (hwmgr->feature_mask & PP_GFXOFF_MASK)
		data->gfxoff_controlled_by_driver = true;
	अन्यथा
		data->gfxoff_controlled_by_driver = false;

	वापस result;
पूर्ण

अटल पूर्णांक vega12_init_sclk_threshold(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);

	data->low_sclk_पूर्णांकerrupt_threshold = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_setup_asic_task(काष्ठा pp_hwmgr *hwmgr)
अणु
	PP_ASSERT_WITH_CODE(!vega12_init_sclk_threshold(hwmgr),
			"Failed to init sclk threshold!",
			वापस -EINVAL);

	वापस 0;
पूर्ण

/*
 * @fn vega12_init_dpm_state
 * @brief Function to initialize all Soft Min/Max and Hard Min/Max to 0xff.
 *
 * @param    dpm_state - the address of the DPM Table to initiailize.
 * @वापस   None.
 */
अटल व्योम vega12_init_dpm_state(काष्ठा vega12_dpm_state *dpm_state)
अणु
	dpm_state->soft_min_level = 0x0;
	dpm_state->soft_max_level = 0xffff;
	dpm_state->hard_min_level = 0x0;
	dpm_state->hard_max_level = 0xffff;
पूर्ण

अटल पूर्णांक vega12_override_pcie_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t pcie_gen = 0, pcie_width = 0, smu_pcie_arg, pcie_gen_arg, pcie_width_arg;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	पूर्णांक i;
	पूर्णांक ret;

	अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN4)
		pcie_gen = 3;
	अन्यथा अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3)
		pcie_gen = 2;
	अन्यथा अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2)
		pcie_gen = 1;
	अन्यथा अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN1)
		pcie_gen = 0;

	अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X16)
		pcie_width = 6;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X12)
		pcie_width = 5;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X8)
		pcie_width = 4;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X4)
		pcie_width = 3;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X2)
		pcie_width = 2;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X1)
		pcie_width = 1;

	/* Bit 31:16: LCLK DPM level. 0 is DPM0, and 1 is DPM1
	 * Bit 15:8:  PCIE GEN, 0 to 3 corresponds to GEN1 to GEN4
	 * Bit 7:0:   PCIE lane width, 1 to 7 corresponds is x1 to x32
	 */
	क्रम (i = 0; i < NUM_LINK_LEVELS; i++) अणु
		pcie_gen_arg = (pp_table->PcieGenSpeed[i] > pcie_gen) ? pcie_gen :
			pp_table->PcieGenSpeed[i];
		pcie_width_arg = (pp_table->PcieLaneCount[i] > pcie_width) ? pcie_width :
			pp_table->PcieLaneCount[i];

		अगर (pcie_gen_arg != pp_table->PcieGenSpeed[i] || pcie_width_arg !=
		    pp_table->PcieLaneCount[i]) अणु
			smu_pcie_arg = (i << 16) | (pcie_gen_arg << 8) | pcie_width_arg;
			ret = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_OverridePcieParameters, smu_pcie_arg,
				शून्य);
			PP_ASSERT_WITH_CODE(!ret,
				"[OverridePcieParameters] Attempt to override pcie params failed!",
				वापस ret);
		पूर्ण

		/* update the pptable */
		pp_table->PcieGenSpeed[i] = pcie_gen_arg;
		pp_table->PcieLaneCount[i] = pcie_width_arg;
	पूर्ण

	/* override to the highest अगर it's disabled from ppfeaturmask */
	अगर (data->registry_data.pcie_dpm_key_disabled) अणु
		क्रम (i = 0; i < NUM_LINK_LEVELS; i++) अणु
			smu_pcie_arg = (i << 16) | (pcie_gen << 8) | pcie_width;
			ret = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_OverridePcieParameters, smu_pcie_arg,
				शून्य);
			PP_ASSERT_WITH_CODE(!ret,
				"[OverridePcieParameters] Attempt to override pcie params failed!",
				वापस ret);

			pp_table->PcieGenSpeed[i] = pcie_gen;
			pp_table->PcieLaneCount[i] = pcie_width;
		पूर्ण
		ret = vega12_enable_smc_features(hwmgr,
				false,
				data->smu_features[GNLD_DPM_LINK].smu_feature_biपंचांगap);
		PP_ASSERT_WITH_CODE(!ret,
				"Attempt to Disable DPM LINK Failed!",
				वापस ret);
		data->smu_features[GNLD_DPM_LINK].enabled = false;
		data->smu_features[GNLD_DPM_LINK].supported = false;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_number_of_dpm_level(काष्ठा pp_hwmgr *hwmgr,
		PPCLK_e clk_id, uपूर्णांक32_t *num_of_levels)
अणु
	पूर्णांक ret = 0;

	ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_GetDpmFreqByIndex,
			(clk_id << 16 | 0xFF),
			num_of_levels);
	PP_ASSERT_WITH_CODE(!ret,
			"[GetNumOfDpmLevel] failed to get dpm levels!",
			वापस ret);

	वापस ret;
पूर्ण

अटल पूर्णांक vega12_get_dpm_frequency_by_index(काष्ठा pp_hwmgr *hwmgr,
		PPCLK_e clkID, uपूर्णांक32_t index, uपूर्णांक32_t *घड़ी)
अणु
	/*
	 *SMU expects the Clock ID to be in the top 16 bits.
	 *Lower 16 bits specअगरy the level
	 */
	PP_ASSERT_WITH_CODE(smum_send_msg_to_smc_with_parameter(hwmgr,
		PPSMC_MSG_GetDpmFreqByIndex, (clkID << 16 | index),
		घड़ी) == 0,
		"[GetDpmFrequencyByIndex] Failed to get dpm frequency from SMU!",
		वापस -EINVAL);

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_setup_single_dpm_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा vega12_single_dpm_table *dpm_table, PPCLK_e clk_id)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t i, num_of_levels, clk;

	ret = vega12_get_number_of_dpm_level(hwmgr, clk_id, &num_of_levels);
	PP_ASSERT_WITH_CODE(!ret,
			"[SetupSingleDpmTable] failed to get clk levels!",
			वापस ret);

	dpm_table->count = num_of_levels;

	क्रम (i = 0; i < num_of_levels; i++) अणु
		ret = vega12_get_dpm_frequency_by_index(hwmgr, clk_id, i, &clk);
		PP_ASSERT_WITH_CODE(!ret,
			"[SetupSingleDpmTable] failed to get clk of specific level!",
			वापस ret);
		dpm_table->dpm_levels[i].value = clk;
		dpm_table->dpm_levels[i].enabled = true;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function is to initialize all DPM state tables
 * क्रम SMU based on the dependency table.
 * Dynamic state patching function will then trim these
 * state tables to the allowed range based
 * on the घातer policy or बाह्यal client requests,
 * such as UVD request, etc.
 */
अटल पूर्णांक vega12_setup_शेष_dpm_tables(काष्ठा pp_hwmgr *hwmgr)
अणु

	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	काष्ठा vega12_single_dpm_table *dpm_table;
	पूर्णांक ret = 0;

	स_रखो(&data->dpm_table, 0, माप(data->dpm_table));

	/* socclk */
	dpm_table = &(data->dpm_table.soc_table);
	अगर (data->smu_features[GNLD_DPM_SOCCLK].enabled) अणु
		ret = vega12_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_SOCCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get socclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.soc_घड़ी / 100;
	पूर्ण
	vega12_init_dpm_state(&(dpm_table->dpm_state));

	/* gfxclk */
	dpm_table = &(data->dpm_table.gfx_table);
	अगर (data->smu_features[GNLD_DPM_GFXCLK].enabled) अणु
		ret = vega12_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_GFXCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get gfxclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.gfx_घड़ी / 100;
	पूर्ण
	vega12_init_dpm_state(&(dpm_table->dpm_state));

	/* memclk */
	dpm_table = &(data->dpm_table.mem_table);
	अगर (data->smu_features[GNLD_DPM_UCLK].enabled) अणु
		ret = vega12_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_UCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get memclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.mem_घड़ी / 100;
	पूर्ण
	vega12_init_dpm_state(&(dpm_table->dpm_state));

	/* eclk */
	dpm_table = &(data->dpm_table.eclk_table);
	अगर (data->smu_features[GNLD_DPM_VCE].enabled) अणु
		ret = vega12_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_ECLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get eclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.eघड़ी / 100;
	पूर्ण
	vega12_init_dpm_state(&(dpm_table->dpm_state));

	/* vclk */
	dpm_table = &(data->dpm_table.vclk_table);
	अगर (data->smu_features[GNLD_DPM_UVD].enabled) अणु
		ret = vega12_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_VCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get vclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.vघड़ी / 100;
	पूर्ण
	vega12_init_dpm_state(&(dpm_table->dpm_state));

	/* dclk */
	dpm_table = &(data->dpm_table.dclk_table);
	अगर (data->smu_features[GNLD_DPM_UVD].enabled) अणु
		ret = vega12_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_DCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get dclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.dघड़ी / 100;
	पूर्ण
	vega12_init_dpm_state(&(dpm_table->dpm_state));

	/* dcefclk */
	dpm_table = &(data->dpm_table.dcef_table);
	अगर (data->smu_features[GNLD_DPM_DCEFCLK].enabled) अणु
		ret = vega12_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_DCEFCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get dcefclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.dcef_घड़ी / 100;
	पूर्ण
	vega12_init_dpm_state(&(dpm_table->dpm_state));

	/* pixclk */
	dpm_table = &(data->dpm_table.pixel_table);
	अगर (data->smu_features[GNLD_DPM_DCEFCLK].enabled) अणु
		ret = vega12_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_PIXCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get pixclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा
		dpm_table->count = 0;
	vega12_init_dpm_state(&(dpm_table->dpm_state));

	/* dispclk */
	dpm_table = &(data->dpm_table.display_table);
	अगर (data->smu_features[GNLD_DPM_DCEFCLK].enabled) अणु
		ret = vega12_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_DISPCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get dispclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा
		dpm_table->count = 0;
	vega12_init_dpm_state(&(dpm_table->dpm_state));

	/* phyclk */
	dpm_table = &(data->dpm_table.phy_table);
	अगर (data->smu_features[GNLD_DPM_DCEFCLK].enabled) अणु
		ret = vega12_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_PHYCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get phyclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा
		dpm_table->count = 0;
	vega12_init_dpm_state(&(dpm_table->dpm_state));

	/* save a copy of the शेष DPM table */
	स_नकल(&(data->golden_dpm_table), &(data->dpm_table),
			माप(काष्ठा vega12_dpm_table));

	वापस 0;
पूर्ण

#अगर 0
अटल पूर्णांक vega12_save_शेष_घातer_profile(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	काष्ठा vega12_single_dpm_table *dpm_table = &(data->dpm_table.gfx_table);
	uपूर्णांक32_t min_level;

	hwmgr->शेष_gfx_घातer_profile.type = AMD_PP_GFX_PROखाता;
	hwmgr->शेष_compute_घातer_profile.type = AMD_PP_COMPUTE_PROखाता;

	/* Optimize compute घातer profile: Use only highest
	 * 2 घातer levels (अगर more than 2 are available)
	 */
	अगर (dpm_table->count > 2)
		min_level = dpm_table->count - 2;
	अन्यथा अगर (dpm_table->count == 2)
		min_level = 1;
	अन्यथा
		min_level = 0;

	hwmgr->शेष_compute_घातer_profile.min_sclk =
			dpm_table->dpm_levels[min_level].value;

	hwmgr->gfx_घातer_profile = hwmgr->शेष_gfx_घातer_profile;
	hwmgr->compute_घातer_profile = hwmgr->शेष_compute_घातer_profile;

	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 * Initializes the SMC table and uploads it
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * वापस:  always 0
 */
अटल पूर्णांक vega12_init_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा pp_atomfwctrl_bios_boot_up_values boot_up_values;
	काष्ठा phm_ppt_v3_inक्रमmation *pptable_inक्रमmation =
		(काष्ठा phm_ppt_v3_inक्रमmation *)hwmgr->pptable;

	result = pp_atomfwctrl_get_vbios_bootup_values(hwmgr, &boot_up_values);
	अगर (!result) अणु
		data->vbios_boot_state.vddc     = boot_up_values.usVddc;
		data->vbios_boot_state.vddci    = boot_up_values.usVddci;
		data->vbios_boot_state.mvddc    = boot_up_values.usMvddc;
		data->vbios_boot_state.gfx_घड़ी = boot_up_values.ulGfxClk;
		data->vbios_boot_state.mem_घड़ी = boot_up_values.ulUClk;
		data->vbios_boot_state.soc_घड़ी = boot_up_values.ulSocClk;
		data->vbios_boot_state.dcef_घड़ी = boot_up_values.ulDCEFClk;
		data->vbios_boot_state.uc_cooling_id = boot_up_values.ucCoolingID;
		data->vbios_boot_state.eघड़ी = boot_up_values.ulEClk;
		data->vbios_boot_state.dघड़ी = boot_up_values.ulDClk;
		data->vbios_boot_state.vघड़ी = boot_up_values.ulVClk;
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetMinDeepSleepDcefclk,
			(uपूर्णांक32_t)(data->vbios_boot_state.dcef_घड़ी / 100),
				शून्य);
	पूर्ण

	स_नकल(pp_table, pptable_inक्रमmation->smc_pptable, माप(PPTable_t));

	result = smum_smc_table_manager(hwmgr,
					(uपूर्णांक8_t *)pp_table, TABLE_PPTABLE, false);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to upload PPtable!", वापस result);

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_run_acg_btc(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t result;

	PP_ASSERT_WITH_CODE(
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_RunAcgBtc, &result) == 0,
		"[Run_ACG_BTC] Attempt to run ACG BTC failed!",
		वापस -EINVAL);

	PP_ASSERT_WITH_CODE(result == 1,
			"Failed to run ACG BTC!", वापस -EINVAL);

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_set_allowed_featuresmask(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	पूर्णांक i;
	uपूर्णांक32_t allowed_features_low = 0, allowed_features_high = 0;

	क्रम (i = 0; i < GNLD_FEATURES_MAX; i++)
		अगर (data->smu_features[i].allowed)
			data->smu_features[i].smu_feature_id > 31 ?
				(allowed_features_high |= ((data->smu_features[i].smu_feature_biपंचांगap >> SMU_FEATURES_HIGH_SHIFT) & 0xFFFFFFFF)) :
				(allowed_features_low |= ((data->smu_features[i].smu_feature_biपंचांगap >> SMU_FEATURES_LOW_SHIFT) & 0xFFFFFFFF));

	PP_ASSERT_WITH_CODE(
		smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_SetAllowedFeaturesMaskHigh, allowed_features_high,
			शून्य) == 0,
		"[SetAllowedFeaturesMask] Attempt to set allowed features mask (high) failed!",
		वापस -1);

	PP_ASSERT_WITH_CODE(
		smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_SetAllowedFeaturesMaskLow, allowed_features_low,
			शून्य) == 0,
		"[SetAllowedFeaturesMask] Attempt to set allowed features mask (low) failed!",
		वापस -1);

	वापस 0;
पूर्ण

अटल व्योम vega12_init_घातergate_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);

	data->uvd_घातer_gated = true;
	data->vce_घातer_gated = true;

	अगर (data->smu_features[GNLD_DPM_UVD].enabled)
		data->uvd_घातer_gated = false;

	अगर (data->smu_features[GNLD_DPM_VCE].enabled)
		data->vce_घातer_gated = false;
पूर्ण

अटल पूर्णांक vega12_enable_all_smu_features(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	uपूर्णांक64_t features_enabled;
	पूर्णांक i;
	bool enabled;

	PP_ASSERT_WITH_CODE(
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_EnableAllSmuFeatures, शून्य) == 0,
		"[EnableAllSMUFeatures] Failed to enable all smu features!",
		वापस -1);

	अगर (vega12_get_enabled_smc_features(hwmgr, &features_enabled) == 0) अणु
		क्रम (i = 0; i < GNLD_FEATURES_MAX; i++) अणु
			enabled = (features_enabled & data->smu_features[i].smu_feature_biपंचांगap) ? true : false;
			data->smu_features[i].enabled = enabled;
			data->smu_features[i].supported = enabled;
		पूर्ण
	पूर्ण

	vega12_init_घातergate_state(hwmgr);

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_disable_all_smu_features(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	uपूर्णांक64_t features_enabled;
	पूर्णांक i;
	bool enabled;

	PP_ASSERT_WITH_CODE(
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_DisableAllSmuFeatures, शून्य) == 0,
		"[DisableAllSMUFeatures] Failed to disable all smu features!",
		वापस -1);

	अगर (vega12_get_enabled_smc_features(hwmgr, &features_enabled) == 0) अणु
		क्रम (i = 0; i < GNLD_FEATURES_MAX; i++) अणु
			enabled = (features_enabled & data->smu_features[i].smu_feature_biपंचांगap) ? true : false;
			data->smu_features[i].enabled = enabled;
			data->smu_features[i].supported = enabled;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_odn_initialize_शेष_settings(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vega12_set_overdrive_target_percentage(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t adjust_percent)
अणु
	वापस smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_OverDriveSetPercentage, adjust_percent,
			शून्य);
पूर्ण

अटल पूर्णांक vega12_घातer_control_set_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक adjust_percent, result = 0;

	अगर (PP_CAP(PHM_Platक्रमmCaps_PowerContainment)) अणु
		adjust_percent =
				hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगentPolarity ?
				hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगent :
				(-1 * hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगent);
		result = vega12_set_overdrive_target_percentage(hwmgr,
				(uपूर्णांक32_t)adjust_percent);
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक vega12_get_all_घड़ी_ranges_helper(काष्ठा pp_hwmgr *hwmgr,
		PPCLK_e clkid, काष्ठा vega12_घड़ी_range *घड़ी)
अणु
	/* AC Max */
	PP_ASSERT_WITH_CODE(
		smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_GetMaxDpmFreq, (clkid << 16),
			&(घड़ी->ACMax)) == 0,
		"[GetClockRanges] Failed to get max ac clock from SMC!",
		वापस -EINVAL);

	/* AC Min */
	PP_ASSERT_WITH_CODE(
		smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_GetMinDpmFreq, (clkid << 16),
			&(घड़ी->ACMin)) == 0,
		"[GetClockRanges] Failed to get min ac clock from SMC!",
		वापस -EINVAL);

	/* DC Max */
	PP_ASSERT_WITH_CODE(
		smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_GetDcModeMaxDpmFreq, (clkid << 16),
			&(घड़ी->DCMax)) == 0,
		"[GetClockRanges] Failed to get max dc clock from SMC!",
		वापस -EINVAL);

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_all_घड़ी_ranges(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t i;

	क्रम (i = 0; i < PPCLK_COUNT; i++)
		PP_ASSERT_WITH_CODE(!vega12_get_all_घड़ी_ranges_helper(hwmgr,
					i, &(data->clk_range[i])),
				"Failed to get clk range from SMC!",
				वापस -EINVAL);

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_enable_dpm_tasks(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक पंचांगp_result, result = 0;

	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_NumOfDisplays, 0, शून्य);

	result = vega12_set_allowed_featuresmask(hwmgr);
	PP_ASSERT_WITH_CODE(result == 0,
			"[EnableDPMTasks] Failed to set allowed featuresmask!\n",
			वापस result);

	पंचांगp_result = vega12_init_smc_table(hwmgr);
	PP_ASSERT_WITH_CODE(!पंचांगp_result,
			"Failed to initialize SMC table!",
			result = पंचांगp_result);

	पंचांगp_result = vega12_run_acg_btc(hwmgr);
	PP_ASSERT_WITH_CODE(!पंचांगp_result,
			"Failed to run ACG BTC!",
			result = पंचांगp_result);

	result = vega12_enable_all_smu_features(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to enable all smu features!",
			वापस result);

	result = vega12_override_pcie_parameters(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to override pcie parameters!",
			वापस result);

	पंचांगp_result = vega12_घातer_control_set_level(hwmgr);
	PP_ASSERT_WITH_CODE(!पंचांगp_result,
			"Failed to power control set level!",
			result = पंचांगp_result);

	result = vega12_get_all_घड़ी_ranges(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to get all clock ranges!",
			वापस result);

	result = vega12_odn_initialize_शेष_settings(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to power control set level!",
			वापस result);

	result = vega12_setup_शेष_dpm_tables(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to setup default DPM tables!",
			वापस result);
	वापस result;
पूर्ण

अटल पूर्णांक vega12_patch_boot_state(काष्ठा pp_hwmgr *hwmgr,
	     काष्ठा pp_hw_घातer_state *hw_ps)
अणु
	वापस 0;
पूर्ण

अटल uपूर्णांक32_t vega12_find_lowest_dpm_level(
		काष्ठा vega12_single_dpm_table *table)
अणु
	uपूर्णांक32_t i;

	क्रम (i = 0; i < table->count; i++) अणु
		अगर (table->dpm_levels[i].enabled)
			अवरोध;
	पूर्ण

	अगर (i >= table->count) अणु
		i = 0;
		table->dpm_levels[i].enabled = true;
	पूर्ण

	वापस i;
पूर्ण

अटल uपूर्णांक32_t vega12_find_highest_dpm_level(
		काष्ठा vega12_single_dpm_table *table)
अणु
	पूर्णांक32_t i = 0;
	PP_ASSERT_WITH_CODE(table->count <= MAX_REGULAR_DPM_NUMBER,
			"[FindHighestDPMLevel] DPM Table has too many entries!",
			वापस MAX_REGULAR_DPM_NUMBER - 1);

	क्रम (i = table->count - 1; i >= 0; i--) अणु
		अगर (table->dpm_levels[i].enabled)
			अवरोध;
	पूर्ण

	अगर (i < 0) अणु
		i = 0;
		table->dpm_levels[i].enabled = true;
	पूर्ण

	वापस (uपूर्णांक32_t)i;
पूर्ण

अटल पूर्णांक vega12_upload_dpm_min_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t min_freq;
	पूर्णांक ret = 0;

	अगर (data->smu_features[GNLD_DPM_GFXCLK].enabled) अणु
		min_freq = data->dpm_table.gfx_table.dpm_state.soft_min_level;
		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMinByFreq,
					(PPCLK_GFXCLK << 16) | (min_freq & 0xffff),
					शून्य)),
					"Failed to set soft min gfxclk !",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_UCLK].enabled) अणु
		min_freq = data->dpm_table.mem_table.dpm_state.soft_min_level;
		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMinByFreq,
					(PPCLK_UCLK << 16) | (min_freq & 0xffff),
					शून्य)),
					"Failed to set soft min memclk !",
					वापस ret);

		min_freq = data->dpm_table.mem_table.dpm_state.hard_min_level;
		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetHardMinByFreq,
					(PPCLK_UCLK << 16) | (min_freq & 0xffff),
					शून्य)),
					"Failed to set hard min memclk !",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_UVD].enabled) अणु
		min_freq = data->dpm_table.vclk_table.dpm_state.soft_min_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMinByFreq,
					(PPCLK_VCLK << 16) | (min_freq & 0xffff),
					शून्य)),
					"Failed to set soft min vclk!",
					वापस ret);

		min_freq = data->dpm_table.dclk_table.dpm_state.soft_min_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMinByFreq,
					(PPCLK_DCLK << 16) | (min_freq & 0xffff),
					शून्य)),
					"Failed to set soft min dclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_VCE].enabled) अणु
		min_freq = data->dpm_table.eclk_table.dpm_state.soft_min_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMinByFreq,
					(PPCLK_ECLK << 16) | (min_freq & 0xffff),
					शून्य)),
					"Failed to set soft min eclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_SOCCLK].enabled) अणु
		min_freq = data->dpm_table.soc_table.dpm_state.soft_min_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMinByFreq,
					(PPCLK_SOCCLK << 16) | (min_freq & 0xffff),
					शून्य)),
					"Failed to set soft min socclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_DCEFCLK].enabled) अणु
		min_freq = data->dpm_table.dcef_table.dpm_state.hard_min_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetHardMinByFreq,
					(PPCLK_DCEFCLK << 16) | (min_freq & 0xffff),
					शून्य)),
					"Failed to set hard min dcefclk!",
					वापस ret);
	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक vega12_upload_dpm_max_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t max_freq;
	पूर्णांक ret = 0;

	अगर (data->smu_features[GNLD_DPM_GFXCLK].enabled) अणु
		max_freq = data->dpm_table.gfx_table.dpm_state.soft_max_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMaxByFreq,
					(PPCLK_GFXCLK << 16) | (max_freq & 0xffff),
					शून्य)),
					"Failed to set soft max gfxclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_UCLK].enabled) अणु
		max_freq = data->dpm_table.mem_table.dpm_state.soft_max_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMaxByFreq,
					(PPCLK_UCLK << 16) | (max_freq & 0xffff),
					शून्य)),
					"Failed to set soft max memclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_UVD].enabled) अणु
		max_freq = data->dpm_table.vclk_table.dpm_state.soft_max_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMaxByFreq,
					(PPCLK_VCLK << 16) | (max_freq & 0xffff),
					शून्य)),
					"Failed to set soft max vclk!",
					वापस ret);

		max_freq = data->dpm_table.dclk_table.dpm_state.soft_max_level;
		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMaxByFreq,
					(PPCLK_DCLK << 16) | (max_freq & 0xffff),
					शून्य)),
					"Failed to set soft max dclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_VCE].enabled) अणु
		max_freq = data->dpm_table.eclk_table.dpm_state.soft_max_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMaxByFreq,
					(PPCLK_ECLK << 16) | (max_freq & 0xffff),
					शून्य)),
					"Failed to set soft max eclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_SOCCLK].enabled) अणु
		max_freq = data->dpm_table.soc_table.dpm_state.soft_max_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMaxByFreq,
					(PPCLK_SOCCLK << 16) | (max_freq & 0xffff),
					शून्य)),
					"Failed to set soft max socclk!",
					वापस ret);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक vega12_enable_disable_vce_dpm(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);

	अगर (data->smu_features[GNLD_DPM_VCE].supported) अणु
		PP_ASSERT_WITH_CODE(!vega12_enable_smc_features(hwmgr,
				enable,
				data->smu_features[GNLD_DPM_VCE].smu_feature_biपंचांगap),
				"Attempt to Enable/Disable DPM VCE Failed!",
				वापस -1);
		data->smu_features[GNLD_DPM_VCE].enabled = enable;
	पूर्ण

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t vega12_dpm_get_sclk(काष्ठा pp_hwmgr *hwmgr, bool low)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t gfx_clk;

	अगर (!data->smu_features[GNLD_DPM_GFXCLK].enabled)
		वापस -1;

	अगर (low)
		PP_ASSERT_WITH_CODE(
			vega12_get_घड़ी_ranges(hwmgr, &gfx_clk, PPCLK_GFXCLK, false) == 0,
			"[GetSclks]: fail to get min PPCLK_GFXCLK\n",
			वापस -1);
	अन्यथा
		PP_ASSERT_WITH_CODE(
			vega12_get_घड़ी_ranges(hwmgr, &gfx_clk, PPCLK_GFXCLK, true) == 0,
			"[GetSclks]: fail to get max PPCLK_GFXCLK\n",
			वापस -1);

	वापस (gfx_clk * 100);
पूर्ण

अटल uपूर्णांक32_t vega12_dpm_get_mclk(काष्ठा pp_hwmgr *hwmgr, bool low)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t mem_clk;

	अगर (!data->smu_features[GNLD_DPM_UCLK].enabled)
		वापस -1;

	अगर (low)
		PP_ASSERT_WITH_CODE(
			vega12_get_घड़ी_ranges(hwmgr, &mem_clk, PPCLK_UCLK, false) == 0,
			"[GetMclks]: fail to get min PPCLK_UCLK\n",
			वापस -1);
	अन्यथा
		PP_ASSERT_WITH_CODE(
			vega12_get_घड़ी_ranges(hwmgr, &mem_clk, PPCLK_UCLK, true) == 0,
			"[GetMclks]: fail to get max PPCLK_UCLK\n",
			वापस -1);

	वापस (mem_clk * 100);
पूर्ण

अटल पूर्णांक vega12_get_metrics_table(काष्ठा pp_hwmgr *hwmgr,
				    SmuMetrics_t *metrics_table,
				    bool bypass_cache)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	पूर्णांक ret = 0;

	अगर (bypass_cache ||
	    !data->metrics_समय ||
	    समय_after(jअगरfies, data->metrics_समय + msecs_to_jअगरfies(1))) अणु
		ret = smum_smc_table_manager(hwmgr,
					     (uपूर्णांक8_t *)(&data->metrics_table),
					     TABLE_SMU_METRICS,
					     true);
		अगर (ret) अणु
			pr_info("Failed to export SMU metrics table!\n");
			वापस ret;
		पूर्ण
		data->metrics_समय = jअगरfies;
	पूर्ण

	अगर (metrics_table)
		स_नकल(metrics_table, &data->metrics_table, माप(SmuMetrics_t));

	वापस ret;
पूर्ण

अटल पूर्णांक vega12_get_gpu_घातer(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *query)
अणु
	SmuMetrics_t metrics_table;
	पूर्णांक ret = 0;

	ret = vega12_get_metrics_table(hwmgr, &metrics_table, false);
	अगर (ret)
		वापस ret;

	*query = metrics_table.CurrSocketPower << 8;

	वापस ret;
पूर्ण

अटल पूर्णांक vega12_get_current_gfx_clk_freq(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *gfx_freq)
अणु
	uपूर्णांक32_t gfx_clk = 0;

	*gfx_freq = 0;

	PP_ASSERT_WITH_CODE(smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_GetDpmClockFreq, (PPCLK_GFXCLK << 16),
			&gfx_clk) == 0,
			"[GetCurrentGfxClkFreq] Attempt to get Current GFXCLK Frequency Failed!",
			वापस -EINVAL);

	*gfx_freq = gfx_clk * 100;

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_current_mclk_freq(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *mclk_freq)
अणु
	uपूर्णांक32_t mem_clk = 0;

	*mclk_freq = 0;

	PP_ASSERT_WITH_CODE(
			smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_GetDpmClockFreq, (PPCLK_UCLK << 16),
				&mem_clk) == 0,
			"[GetCurrentMClkFreq] Attempt to get Current MCLK Frequency Failed!",
			वापस -EINVAL);

	*mclk_freq = mem_clk * 100;

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_current_activity_percent(
		काष्ठा pp_hwmgr *hwmgr,
		पूर्णांक idx,
		uपूर्णांक32_t *activity_percent)
अणु
	SmuMetrics_t metrics_table;
	पूर्णांक ret = 0;

	ret = vega12_get_metrics_table(hwmgr, &metrics_table, false);
	अगर (ret)
		वापस ret;

	चयन (idx) अणु
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
		*activity_percent = metrics_table.AverageGfxActivity;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_MEM_LOAD:
		*activity_percent = metrics_table.AverageUclkActivity;
		अवरोध;
	शेष:
		pr_err("Invalid index for retrieving clock activity\n");
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vega12_पढ़ो_sensor(काष्ठा pp_hwmgr *hwmgr, पूर्णांक idx,
			      व्योम *value, पूर्णांक *size)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	SmuMetrics_t metrics_table;
	पूर्णांक ret = 0;

	चयन (idx) अणु
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		ret = vega12_get_current_gfx_clk_freq(hwmgr, (uपूर्णांक32_t *)value);
		अगर (!ret)
			*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_MCLK:
		ret = vega12_get_current_mclk_freq(hwmgr, (uपूर्णांक32_t *)value);
		अगर (!ret)
			*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
	हाल AMDGPU_PP_SENSOR_MEM_LOAD:
		ret = vega12_get_current_activity_percent(hwmgr, idx, (uपूर्णांक32_t *)value);
		अगर (!ret)
			*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_TEMP:
		*((uपूर्णांक32_t *)value) = vega12_thermal_get_temperature(hwmgr);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_HOTSPOT_TEMP:
		ret = vega12_get_metrics_table(hwmgr, &metrics_table, false);
		अगर (ret)
			वापस ret;

		*((uपूर्णांक32_t *)value) = metrics_table.TemperatureHotspot *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_MEM_TEMP:
		ret = vega12_get_metrics_table(hwmgr, &metrics_table, false);
		अगर (ret)
			वापस ret;

		*((uपूर्णांक32_t *)value) = metrics_table.TemperatureHBM *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_UVD_POWER:
		*((uपूर्णांक32_t *)value) = data->uvd_घातer_gated ? 0 : 1;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_VCE_POWER:
		*((uपूर्णांक32_t *)value) = data->vce_घातer_gated ? 0 : 1;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_POWER:
		ret = vega12_get_gpu_घातer(hwmgr, (uपूर्णांक32_t *)value);
		अगर (!ret)
			*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_ENABLED_SMC_FEATURES_MASK:
		ret = vega12_get_enabled_smc_features(hwmgr, (uपूर्णांक64_t *)value);
		अगर (!ret)
			*size = 8;
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक vega12_notअगरy_smc_display_change(काष्ठा pp_hwmgr *hwmgr,
		bool has_disp)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);

	अगर (data->smu_features[GNLD_DPM_UCLK].enabled)
		वापस smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetUclkFastSwitch,
			has_disp ? 1 : 0,
			शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_display_घड़ी_voltage_request(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_display_घड़ी_request *घड़ी_req)
अणु
	पूर्णांक result = 0;
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	क्रमागत amd_pp_घड़ी_प्रकारype clk_type = घड़ी_req->घड़ी_प्रकारype;
	uपूर्णांक32_t clk_freq = घड़ी_req->घड़ी_freq_in_khz / 1000;
	PPCLK_e clk_select = 0;
	uपूर्णांक32_t clk_request = 0;

	अगर (data->smu_features[GNLD_DPM_DCEFCLK].enabled) अणु
		चयन (clk_type) अणु
		हाल amd_pp_dcef_घड़ी:
			clk_select = PPCLK_DCEFCLK;
			अवरोध;
		हाल amd_pp_disp_घड़ी:
			clk_select = PPCLK_DISPCLK;
			अवरोध;
		हाल amd_pp_pixel_घड़ी:
			clk_select = PPCLK_PIXCLK;
			अवरोध;
		हाल amd_pp_phy_घड़ी:
			clk_select = PPCLK_PHYCLK;
			अवरोध;
		शेष:
			pr_info("[DisplayClockVoltageRequest]Invalid Clock Type!");
			result = -1;
			अवरोध;
		पूर्ण

		अगर (!result) अणु
			clk_request = (clk_select << 16) | clk_freq;
			result = smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetHardMinByFreq,
					clk_request,
					शून्य);
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक vega12_notअगरy_smc_display_config_after_ps_adjusपंचांगent(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	काष्ठा PP_Clocks min_घड़ीs = अणु0पूर्ण;
	काष्ठा pp_display_घड़ी_request घड़ी_req;

	अगर ((hwmgr->display_config->num_display > 1) &&
	     !hwmgr->display_config->multi_monitor_in_sync &&
	     !hwmgr->display_config->nb_pstate_चयन_disable)
		vega12_notअगरy_smc_display_change(hwmgr, false);
	अन्यथा
		vega12_notअगरy_smc_display_change(hwmgr, true);

	min_घड़ीs.dcefClock = hwmgr->display_config->min_dcef_set_clk;
	min_घड़ीs.dcefClockInSR = hwmgr->display_config->min_dcef_deep_sleep_set_clk;
	min_घड़ीs.memoryClock = hwmgr->display_config->min_mem_set_घड़ी;

	अगर (data->smu_features[GNLD_DPM_DCEFCLK].supported) अणु
		घड़ी_req.घड़ी_प्रकारype = amd_pp_dcef_घड़ी;
		घड़ी_req.घड़ी_freq_in_khz = min_घड़ीs.dcefClock/10;
		अगर (!vega12_display_घड़ी_voltage_request(hwmgr, &घड़ी_req)) अणु
			अगर (data->smu_features[GNLD_DS_DCEFCLK].supported)
				PP_ASSERT_WITH_CODE(
					!smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetMinDeepSleepDcefclk,
					min_घड़ीs.dcefClockInSR /100,
					शून्य),
					"Attempt to set divider for DCEFCLK Failed!",
					वापस -1);
		पूर्ण अन्यथा अणु
			pr_info("Attempt to set Hard Min for DCEFCLK Failed!");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_क्रमce_dpm_highest(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);

	uपूर्णांक32_t soft_level;

	soft_level = vega12_find_highest_dpm_level(&(data->dpm_table.gfx_table));

	data->dpm_table.gfx_table.dpm_state.soft_min_level =
		data->dpm_table.gfx_table.dpm_state.soft_max_level =
		data->dpm_table.gfx_table.dpm_levels[soft_level].value;

	soft_level = vega12_find_highest_dpm_level(&(data->dpm_table.mem_table));

	data->dpm_table.mem_table.dpm_state.soft_min_level =
		data->dpm_table.mem_table.dpm_state.soft_max_level =
		data->dpm_table.mem_table.dpm_levels[soft_level].value;

	PP_ASSERT_WITH_CODE(!vega12_upload_dpm_min_level(hwmgr),
			"Failed to upload boot level to highest!",
			वापस -1);

	PP_ASSERT_WITH_CODE(!vega12_upload_dpm_max_level(hwmgr),
			"Failed to upload dpm max level to highest!",
			वापस -1);

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_क्रमce_dpm_lowest(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t soft_level;

	soft_level = vega12_find_lowest_dpm_level(&(data->dpm_table.gfx_table));

	data->dpm_table.gfx_table.dpm_state.soft_min_level =
		data->dpm_table.gfx_table.dpm_state.soft_max_level =
		data->dpm_table.gfx_table.dpm_levels[soft_level].value;

	soft_level = vega12_find_lowest_dpm_level(&(data->dpm_table.mem_table));

	data->dpm_table.mem_table.dpm_state.soft_min_level =
		data->dpm_table.mem_table.dpm_state.soft_max_level =
		data->dpm_table.mem_table.dpm_levels[soft_level].value;

	PP_ASSERT_WITH_CODE(!vega12_upload_dpm_min_level(hwmgr),
			"Failed to upload boot level to highest!",
			वापस -1);

	PP_ASSERT_WITH_CODE(!vega12_upload_dpm_max_level(hwmgr),
			"Failed to upload dpm max level to highest!",
			वापस -1);

	वापस 0;

पूर्ण

अटल पूर्णांक vega12_unक्रमce_dpm_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	PP_ASSERT_WITH_CODE(!vega12_upload_dpm_min_level(hwmgr),
			"Failed to upload DPM Bootup Levels!",
			वापस -1);

	PP_ASSERT_WITH_CODE(!vega12_upload_dpm_max_level(hwmgr),
			"Failed to upload DPM Max Levels!",
			वापस -1);

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_profiling_clk_mask(काष्ठा pp_hwmgr *hwmgr, क्रमागत amd_dpm_क्रमced_level level,
				uपूर्णांक32_t *sclk_mask, uपूर्णांक32_t *mclk_mask, uपूर्णांक32_t *soc_mask)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	काष्ठा vega12_single_dpm_table *gfx_dpm_table = &(data->dpm_table.gfx_table);
	काष्ठा vega12_single_dpm_table *mem_dpm_table = &(data->dpm_table.mem_table);
	काष्ठा vega12_single_dpm_table *soc_dpm_table = &(data->dpm_table.soc_table);

	*sclk_mask = 0;
	*mclk_mask = 0;
	*soc_mask  = 0;

	अगर (gfx_dpm_table->count > VEGA12_UMD_PSTATE_GFXCLK_LEVEL &&
	    mem_dpm_table->count > VEGA12_UMD_PSTATE_MCLK_LEVEL &&
	    soc_dpm_table->count > VEGA12_UMD_PSTATE_SOCCLK_LEVEL) अणु
		*sclk_mask = VEGA12_UMD_PSTATE_GFXCLK_LEVEL;
		*mclk_mask = VEGA12_UMD_PSTATE_MCLK_LEVEL;
		*soc_mask  = VEGA12_UMD_PSTATE_SOCCLK_LEVEL;
	पूर्ण

	अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK) अणु
		*sclk_mask = 0;
	पूर्ण अन्यथा अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK) अणु
		*mclk_mask = 0;
	पूर्ण अन्यथा अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
		*sclk_mask = gfx_dpm_table->count - 1;
		*mclk_mask = mem_dpm_table->count - 1;
		*soc_mask  = soc_dpm_table->count - 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vega12_set_fan_control_mode(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t mode)
अणु
	चयन (mode) अणु
	हाल AMD_FAN_CTRL_NONE:
		अवरोध;
	हाल AMD_FAN_CTRL_MANUAL:
		अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl))
			vega12_fan_ctrl_stop_smc_fan_control(hwmgr);
		अवरोध;
	हाल AMD_FAN_CTRL_AUTO:
		अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl))
			vega12_fan_ctrl_start_smc_fan_control(hwmgr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक vega12_dpm_क्रमce_dpm_level(काष्ठा pp_hwmgr *hwmgr,
				क्रमागत amd_dpm_क्रमced_level level)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t sclk_mask = 0;
	uपूर्णांक32_t mclk_mask = 0;
	uपूर्णांक32_t soc_mask = 0;

	चयन (level) अणु
	हाल AMD_DPM_FORCED_LEVEL_HIGH:
		ret = vega12_क्रमce_dpm_highest(hwmgr);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_LOW:
		ret = vega12_क्रमce_dpm_lowest(hwmgr);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_AUTO:
		ret = vega12_unक्रमce_dpm_levels(hwmgr);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_PEAK:
		ret = vega12_get_profiling_clk_mask(hwmgr, level, &sclk_mask, &mclk_mask, &soc_mask);
		अगर (ret)
			वापस ret;
		vega12_क्रमce_घड़ी_level(hwmgr, PP_SCLK, 1 << sclk_mask);
		vega12_क्रमce_घड़ी_level(hwmgr, PP_MCLK, 1 << mclk_mask);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_MANUAL:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_EXIT:
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल uपूर्णांक32_t vega12_get_fan_control_mode(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);

	अगर (data->smu_features[GNLD_FAN_CONTROL].enabled == false)
		वापस AMD_FAN_CTRL_MANUAL;
	अन्यथा
		वापस AMD_FAN_CTRL_AUTO;
पूर्ण

अटल पूर्णांक vega12_get_dal_घातer_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा amd_pp_simple_घड़ी_info *info)
अणु
#अगर 0
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_घड़ी_and_voltage_limits *max_limits =
			&table_info->max_घड़ी_voltage_on_ac;

	info->engine_max_घड़ी = max_limits->sclk;
	info->memory_max_घड़ी = max_limits->mclk;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_घड़ी_ranges(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t *घड़ी,
		PPCLK_e घड़ी_select,
		bool max)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);

	अगर (max)
		*घड़ी = data->clk_range[घड़ी_select].ACMax;
	अन्यथा
		*घड़ी = data->clk_range[घड़ी_select].ACMin;

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_sclks(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t ucount;
	पूर्णांक i;
	काष्ठा vega12_single_dpm_table *dpm_table;

	अगर (!data->smu_features[GNLD_DPM_GFXCLK].enabled)
		वापस -1;

	dpm_table = &(data->dpm_table.gfx_table);
	ucount = (dpm_table->count > MAX_NUM_CLOCKS) ?
		MAX_NUM_CLOCKS : dpm_table->count;

	क्रम (i = 0; i < ucount; i++) अणु
		घड़ीs->data[i].घड़ीs_in_khz =
			dpm_table->dpm_levels[i].value * 1000;

		घड़ीs->data[i].latency_in_us = 0;
	पूर्ण

	घड़ीs->num_levels = ucount;

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t vega12_get_mem_latency(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी)
अणु
	वापस 25;
पूर्ण

अटल पूर्णांक vega12_get_memघड़ीs(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t ucount;
	पूर्णांक i;
	काष्ठा vega12_single_dpm_table *dpm_table;
	अगर (!data->smu_features[GNLD_DPM_UCLK].enabled)
		वापस -1;

	dpm_table = &(data->dpm_table.mem_table);
	ucount = (dpm_table->count > MAX_NUM_CLOCKS) ?
		MAX_NUM_CLOCKS : dpm_table->count;

	क्रम (i = 0; i < ucount; i++) अणु
		घड़ीs->data[i].घड़ीs_in_khz = dpm_table->dpm_levels[i].value * 1000;
		data->mclk_latency_table.entries[i].frequency = dpm_table->dpm_levels[i].value * 100;
		घड़ीs->data[i].latency_in_us =
			data->mclk_latency_table.entries[i].latency =
			vega12_get_mem_latency(hwmgr, dpm_table->dpm_levels[i].value);
	पूर्ण

	घड़ीs->num_levels = data->mclk_latency_table.count = ucount;

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_dcefघड़ीs(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t ucount;
	पूर्णांक i;
	काष्ठा vega12_single_dpm_table *dpm_table;

	अगर (!data->smu_features[GNLD_DPM_DCEFCLK].enabled)
		वापस -1;


	dpm_table = &(data->dpm_table.dcef_table);
	ucount = (dpm_table->count > MAX_NUM_CLOCKS) ?
		MAX_NUM_CLOCKS : dpm_table->count;

	क्रम (i = 0; i < ucount; i++) अणु
		घड़ीs->data[i].घड़ीs_in_khz =
			dpm_table->dpm_levels[i].value * 1000;

		घड़ीs->data[i].latency_in_us = 0;
	पूर्ण

	घड़ीs->num_levels = ucount;

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_socघड़ीs(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t ucount;
	पूर्णांक i;
	काष्ठा vega12_single_dpm_table *dpm_table;

	अगर (!data->smu_features[GNLD_DPM_SOCCLK].enabled)
		वापस -1;


	dpm_table = &(data->dpm_table.soc_table);
	ucount = (dpm_table->count > MAX_NUM_CLOCKS) ?
		MAX_NUM_CLOCKS : dpm_table->count;

	क्रम (i = 0; i < ucount; i++) अणु
		घड़ीs->data[i].घड़ीs_in_khz =
			dpm_table->dpm_levels[i].value * 1000;

		घड़ीs->data[i].latency_in_us = 0;
	पूर्ण

	घड़ीs->num_levels = ucount;

	वापस 0;

पूर्ण

अटल पूर्णांक vega12_get_घड़ी_by_type_with_latency(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	पूर्णांक ret;

	चयन (type) अणु
	हाल amd_pp_sys_घड़ी:
		ret = vega12_get_sclks(hwmgr, घड़ीs);
		अवरोध;
	हाल amd_pp_mem_घड़ी:
		ret = vega12_get_memघड़ीs(hwmgr, घड़ीs);
		अवरोध;
	हाल amd_pp_dcef_घड़ी:
		ret = vega12_get_dcefघड़ीs(hwmgr, घड़ीs);
		अवरोध;
	हाल amd_pp_soc_घड़ी:
		ret = vega12_get_socघड़ीs(hwmgr, घड़ीs);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vega12_get_घड़ी_by_type_with_voltage(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_voltage *घड़ीs)
अणु
	घड़ीs->num_levels = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_set_watermarks_क्रम_घड़ीs_ranges(काष्ठा pp_hwmgr *hwmgr,
							व्योम *घड़ी_ranges)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	Watermarks_t *table = &(data->smc_state_table.water_marks_table);
	काष्ठा dm_pp_wm_sets_with_घड़ी_ranges_soc15 *wm_with_घड़ी_ranges = घड़ी_ranges;

	अगर (!data->registry_data.disable_water_mark &&
			data->smu_features[GNLD_DPM_DCEFCLK].supported &&
			data->smu_features[GNLD_DPM_SOCCLK].supported) अणु
		smu_set_watermarks_क्रम_घड़ीs_ranges(table, wm_with_घड़ी_ranges);
		data->water_marks_biपंचांगap |= WaterMarksExist;
		data->water_marks_biपंचांगap &= ~WaterMarksLoaded;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_क्रमce_घड़ी_level(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, uपूर्णांक32_t mask)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t soft_min_level, soft_max_level, hard_min_level;
	पूर्णांक ret = 0;

	चयन (type) अणु
	हाल PP_SCLK:
		soft_min_level = mask ? (ffs(mask) - 1) : 0;
		soft_max_level = mask ? (fls(mask) - 1) : 0;

		data->dpm_table.gfx_table.dpm_state.soft_min_level =
			data->dpm_table.gfx_table.dpm_levels[soft_min_level].value;
		data->dpm_table.gfx_table.dpm_state.soft_max_level =
			data->dpm_table.gfx_table.dpm_levels[soft_max_level].value;

		ret = vega12_upload_dpm_min_level(hwmgr);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload boot level to lowest!",
			वापस ret);

		ret = vega12_upload_dpm_max_level(hwmgr);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload dpm max level to highest!",
			वापस ret);
		अवरोध;

	हाल PP_MCLK:
		soft_min_level = mask ? (ffs(mask) - 1) : 0;
		soft_max_level = mask ? (fls(mask) - 1) : 0;

		data->dpm_table.mem_table.dpm_state.soft_min_level =
			data->dpm_table.mem_table.dpm_levels[soft_min_level].value;
		data->dpm_table.mem_table.dpm_state.soft_max_level =
			data->dpm_table.mem_table.dpm_levels[soft_max_level].value;

		ret = vega12_upload_dpm_min_level(hwmgr);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload boot level to lowest!",
			वापस ret);

		ret = vega12_upload_dpm_max_level(hwmgr);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload dpm max level to highest!",
			वापस ret);

		अवरोध;

	हाल PP_SOCCLK:
		soft_min_level = mask ? (ffs(mask) - 1) : 0;
		soft_max_level = mask ? (fls(mask) - 1) : 0;

		अगर (soft_max_level >= data->dpm_table.soc_table.count) अणु
			pr_err("Clock level specified %d is over max allowed %d\n",
					soft_max_level,
					data->dpm_table.soc_table.count - 1);
			वापस -EINVAL;
		पूर्ण

		data->dpm_table.soc_table.dpm_state.soft_min_level =
			data->dpm_table.soc_table.dpm_levels[soft_min_level].value;
		data->dpm_table.soc_table.dpm_state.soft_max_level =
			data->dpm_table.soc_table.dpm_levels[soft_max_level].value;

		ret = vega12_upload_dpm_min_level(hwmgr);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload boot level to lowest!",
			वापस ret);

		ret = vega12_upload_dpm_max_level(hwmgr);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload dpm max level to highest!",
			वापस ret);

		अवरोध;

	हाल PP_DCEFCLK:
		hard_min_level = mask ? (ffs(mask) - 1) : 0;

		अगर (hard_min_level >= data->dpm_table.dcef_table.count) अणु
			pr_err("Clock level specified %d is over max allowed %d\n",
					hard_min_level,
					data->dpm_table.dcef_table.count - 1);
			वापस -EINVAL;
		पूर्ण

		data->dpm_table.dcef_table.dpm_state.hard_min_level =
			data->dpm_table.dcef_table.dpm_levels[hard_min_level].value;

		ret = vega12_upload_dpm_min_level(hwmgr);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload boot level to lowest!",
			वापस ret);

		//TODO: Setting DCEFCLK max dpm level is not supported

		अवरोध;

	हाल PP_PCIE:
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_ppfeature_status(काष्ठा pp_hwmgr *hwmgr, अक्षर *buf)
अणु
	अटल स्थिर अक्षर *ppfeature_name[] = अणु
			"DPM_PREFETCHER",
			"GFXCLK_DPM",
			"UCLK_DPM",
			"SOCCLK_DPM",
			"UVD_DPM",
			"VCE_DPM",
			"ULV",
			"MP0CLK_DPM",
			"LINK_DPM",
			"DCEFCLK_DPM",
			"GFXCLK_DS",
			"SOCCLK_DS",
			"LCLK_DS",
			"PPT",
			"TDC",
			"THERMAL",
			"GFX_PER_CU_CG",
			"RM",
			"DCEFCLK_DS",
			"ACDC",
			"VR0HOT",
			"VR1HOT",
			"FW_CTF",
			"LED_DISPLAY",
			"FAN_CONTROL",
			"DIDT",
			"GFXOFF",
			"CG",
			"ACG"पूर्ण;
	अटल स्थिर अक्षर *output_title[] = अणु
			"FEATURES",
			"BITMASK",
			"ENABLEMENT"पूर्ण;
	uपूर्णांक64_t features_enabled;
	पूर्णांक i;
	पूर्णांक ret = 0;
	पूर्णांक size = 0;

	ret = vega12_get_enabled_smc_features(hwmgr, &features_enabled);
	PP_ASSERT_WITH_CODE(!ret,
		"[EnableAllSmuFeatures] Failed to get enabled smc features!",
		वापस ret);

	size += प्र_लिखो(buf + size, "Current ppfeatures: 0x%016llx\n", features_enabled);
	size += प्र_लिखो(buf + size, "%-19s %-22s %s\n",
				output_title[0],
				output_title[1],
				output_title[2]);
	क्रम (i = 0; i < GNLD_FEATURES_MAX; i++) अणु
		size += प्र_लिखो(buf + size, "%-19s 0x%016llx %6s\n",
				ppfeature_name[i],
				1ULL << i,
				(features_enabled & (1ULL << i)) ? "Y" : "N");
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक vega12_set_ppfeature_status(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक64_t new_ppfeature_masks)
अणु
	uपूर्णांक64_t features_enabled;
	uपूर्णांक64_t features_to_enable;
	uपूर्णांक64_t features_to_disable;
	पूर्णांक ret = 0;

	अगर (new_ppfeature_masks >= (1ULL << GNLD_FEATURES_MAX))
		वापस -EINVAL;

	ret = vega12_get_enabled_smc_features(hwmgr, &features_enabled);
	अगर (ret)
		वापस ret;

	features_to_disable =
		features_enabled & ~new_ppfeature_masks;
	features_to_enable =
		~features_enabled & new_ppfeature_masks;

	pr_debug("features_to_disable 0x%llx\n", features_to_disable);
	pr_debug("features_to_enable 0x%llx\n", features_to_enable);

	अगर (features_to_disable) अणु
		ret = vega12_enable_smc_features(hwmgr, false, features_to_disable);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (features_to_enable) अणु
		ret = vega12_enable_smc_features(hwmgr, true, features_to_enable);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_current_pcie_link_width_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	वापस (RREG32_PCIE(smnPCIE_LC_LINK_WIDTH_CNTL) &
		PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD_MASK)
		>> PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD__SHIFT;
पूर्ण

अटल पूर्णांक vega12_get_current_pcie_link_width(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t width_level;

	width_level = vega12_get_current_pcie_link_width_level(hwmgr);
	अगर (width_level > LINK_WIDTH_MAX)
		width_level = 0;

	वापस link_width[width_level];
पूर्ण

अटल पूर्णांक vega12_get_current_pcie_link_speed_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	वापस (RREG32_PCIE(smnPCIE_LC_SPEED_CNTL) &
		PSWUSP0_PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE_MASK)
		>> PSWUSP0_PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE__SHIFT;
पूर्ण

अटल पूर्णांक vega12_get_current_pcie_link_speed(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t speed_level;

	speed_level = vega12_get_current_pcie_link_speed_level(hwmgr);
	अगर (speed_level > LINK_SPEED_MAX)
		speed_level = 0;

	वापस link_speed[speed_level];
पूर्ण

अटल पूर्णांक vega12_prपूर्णांक_घड़ी_levels(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, अक्षर *buf)
अणु
	पूर्णांक i, now, size = 0;
	काष्ठा pp_घड़ी_levels_with_latency घड़ीs;

	चयन (type) अणु
	हाल PP_SCLK:
		PP_ASSERT_WITH_CODE(
				vega12_get_current_gfx_clk_freq(hwmgr, &now) == 0,
				"Attempt to get current gfx clk Failed!",
				वापस -1);

		PP_ASSERT_WITH_CODE(
				vega12_get_sclks(hwmgr, &घड़ीs) == 0,
				"Attempt to get gfx clk levels Failed!",
				वापस -1);
		क्रम (i = 0; i < घड़ीs.num_levels; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
				i, घड़ीs.data[i].घड़ीs_in_khz / 1000,
				(घड़ीs.data[i].घड़ीs_in_khz / 1000 == now / 100) ? "*" : "");
		अवरोध;

	हाल PP_MCLK:
		PP_ASSERT_WITH_CODE(
				vega12_get_current_mclk_freq(hwmgr, &now) == 0,
				"Attempt to get current mclk freq Failed!",
				वापस -1);

		PP_ASSERT_WITH_CODE(
				vega12_get_memघड़ीs(hwmgr, &घड़ीs) == 0,
				"Attempt to get memory clk levels Failed!",
				वापस -1);
		क्रम (i = 0; i < घड़ीs.num_levels; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
				i, घड़ीs.data[i].घड़ीs_in_khz / 1000,
				(घड़ीs.data[i].घड़ीs_in_khz / 1000 == now / 100) ? "*" : "");
		अवरोध;

	हाल PP_SOCCLK:
		PP_ASSERT_WITH_CODE(
				smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_GetDpmClockFreq, (PPCLK_SOCCLK << 16),
					&now) == 0,
				"Attempt to get Current SOCCLK Frequency Failed!",
				वापस -EINVAL);

		PP_ASSERT_WITH_CODE(
				vega12_get_socघड़ीs(hwmgr, &घड़ीs) == 0,
				"Attempt to get soc clk levels Failed!",
				वापस -1);
		क्रम (i = 0; i < घड़ीs.num_levels; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
				i, घड़ीs.data[i].घड़ीs_in_khz / 1000,
				(घड़ीs.data[i].घड़ीs_in_khz / 1000 == now) ? "*" : "");
		अवरोध;

	हाल PP_DCEFCLK:
		PP_ASSERT_WITH_CODE(
				smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_GetDpmClockFreq, (PPCLK_DCEFCLK << 16),
					&now) == 0,
				"Attempt to get Current DCEFCLK Frequency Failed!",
				वापस -EINVAL);

		PP_ASSERT_WITH_CODE(
				vega12_get_dcefघड़ीs(hwmgr, &घड़ीs) == 0,
				"Attempt to get dcef clk levels Failed!",
				वापस -1);
		क्रम (i = 0; i < घड़ीs.num_levels; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
				i, घड़ीs.data[i].घड़ीs_in_khz / 1000,
				(घड़ीs.data[i].घड़ीs_in_khz / 1000 == now) ? "*" : "");
		अवरोध;

	हाल PP_PCIE:
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस size;
पूर्ण

अटल पूर्णांक vega12_apply_घड़ीs_adjust_rules(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	काष्ठा vega12_single_dpm_table *dpm_table;
	bool vblank_too_लघु = false;
	bool disable_mclk_चयनing;
	uपूर्णांक32_t i, latency;

	disable_mclk_चयनing = ((1 < hwmgr->display_config->num_display) &&
			          !hwmgr->display_config->multi_monitor_in_sync) ||
			          vblank_too_लघु;
	latency = hwmgr->display_config->dce_tolerable_mclk_in_active_latency;

	/* gfxclk */
	dpm_table = &(data->dpm_table.gfx_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

	अगर (PP_CAP(PHM_Platक्रमmCaps_UMDPState)) अणु
		अगर (VEGA12_UMD_PSTATE_GFXCLK_LEVEL < dpm_table->count) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA12_UMD_PSTATE_GFXCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA12_UMD_PSTATE_GFXCLK_LEVEL].value;
		पूर्ण

		अगर (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[0].value;
		पूर्ण

		अगर (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		पूर्ण
	पूर्ण

	/* memclk */
	dpm_table = &(data->dpm_table.mem_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

	अगर (PP_CAP(PHM_Platक्रमmCaps_UMDPState)) अणु
		अगर (VEGA12_UMD_PSTATE_MCLK_LEVEL < dpm_table->count) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA12_UMD_PSTATE_MCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA12_UMD_PSTATE_MCLK_LEVEL].value;
		पूर्ण

		अगर (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[0].value;
		पूर्ण

		अगर (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		पूर्ण
	पूर्ण

	/* honour DAL's UCLK Hardmin */
	अगर (dpm_table->dpm_state.hard_min_level < (hwmgr->display_config->min_mem_set_घड़ी / 100))
		dpm_table->dpm_state.hard_min_level = hwmgr->display_config->min_mem_set_घड़ी / 100;

	/* Hardmin is dependent on displayconfig */
	अगर (disable_mclk_चयनing) अणु
		dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		क्रम (i = 0; i < data->mclk_latency_table.count - 1; i++) अणु
			अगर (data->mclk_latency_table.entries[i].latency <= latency) अणु
				अगर (dpm_table->dpm_levels[i].value >= (hwmgr->display_config->min_mem_set_घड़ी / 100)) अणु
					dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[i].value;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (hwmgr->display_config->nb_pstate_चयन_disable)
		dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

	/* vclk */
	dpm_table = &(data->dpm_table.vclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

	अगर (PP_CAP(PHM_Platक्रमmCaps_UMDPState)) अणु
		अगर (VEGA12_UMD_PSTATE_UVDCLK_LEVEL < dpm_table->count) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA12_UMD_PSTATE_UVDCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA12_UMD_PSTATE_UVDCLK_LEVEL].value;
		पूर्ण

		अगर (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		पूर्ण
	पूर्ण

	/* dclk */
	dpm_table = &(data->dpm_table.dclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

	अगर (PP_CAP(PHM_Platक्रमmCaps_UMDPState)) अणु
		अगर (VEGA12_UMD_PSTATE_UVDCLK_LEVEL < dpm_table->count) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA12_UMD_PSTATE_UVDCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA12_UMD_PSTATE_UVDCLK_LEVEL].value;
		पूर्ण

		अगर (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		पूर्ण
	पूर्ण

	/* socclk */
	dpm_table = &(data->dpm_table.soc_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

	अगर (PP_CAP(PHM_Platक्रमmCaps_UMDPState)) अणु
		अगर (VEGA12_UMD_PSTATE_SOCCLK_LEVEL < dpm_table->count) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA12_UMD_PSTATE_SOCCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA12_UMD_PSTATE_SOCCLK_LEVEL].value;
		पूर्ण

		अगर (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		पूर्ण
	पूर्ण

	/* eclk */
	dpm_table = &(data->dpm_table.eclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

	अगर (PP_CAP(PHM_Platक्रमmCaps_UMDPState)) अणु
		अगर (VEGA12_UMD_PSTATE_VCEMCLK_LEVEL < dpm_table->count) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA12_UMD_PSTATE_VCEMCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA12_UMD_PSTATE_VCEMCLK_LEVEL].value;
		पूर्ण

		अगर (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_set_uclk_to_highest_dpm_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा vega12_single_dpm_table *dpm_table)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	पूर्णांक ret = 0;

	अगर (data->smu_features[GNLD_DPM_UCLK].enabled) अणु
		PP_ASSERT_WITH_CODE(dpm_table->count > 0,
				"[SetUclkToHightestDpmLevel] Dpm table has no entry!",
				वापस -EINVAL);
		PP_ASSERT_WITH_CODE(dpm_table->count <= NUM_UCLK_DPM_LEVELS,
				"[SetUclkToHightestDpmLevel] Dpm table has too many entries!",
				वापस -EINVAL);

		dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetHardMinByFreq,
				(PPCLK_UCLK << 16 ) | dpm_table->dpm_state.hard_min_level,
				शून्य)),
				"[SetUclkToHightestDpmLevel] Set hard min uclk failed!",
				वापस ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vega12_pre_display_configuration_changed_task(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	पूर्णांक ret = 0;

	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_NumOfDisplays, 0,
			शून्य);

	ret = vega12_set_uclk_to_highest_dpm_level(hwmgr,
			&data->dpm_table.mem_table);

	वापस ret;
पूर्ण

अटल पूर्णांक vega12_display_configuration_changed_task(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	पूर्णांक result = 0;
	Watermarks_t *wm_table = &(data->smc_state_table.water_marks_table);

	अगर ((data->water_marks_biपंचांगap & WaterMarksExist) &&
			!(data->water_marks_biपंचांगap & WaterMarksLoaded)) अणु
		result = smum_smc_table_manager(hwmgr,
						(uपूर्णांक8_t *)wm_table, TABLE_WATERMARKS, false);
		PP_ASSERT_WITH_CODE(result, "Failed to update WMTABLE!", वापस -EINVAL);
		data->water_marks_biपंचांगap |= WaterMarksLoaded;
	पूर्ण

	अगर ((data->water_marks_biपंचांगap & WaterMarksExist) &&
		data->smu_features[GNLD_DPM_DCEFCLK].supported &&
		data->smu_features[GNLD_DPM_SOCCLK].supported)
		smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_NumOfDisplays, hwmgr->display_config->num_display,
			शून्य);

	वापस result;
पूर्ण

अटल पूर्णांक vega12_enable_disable_uvd_dpm(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);

	अगर (data->smu_features[GNLD_DPM_UVD].supported) अणु
		PP_ASSERT_WITH_CODE(!vega12_enable_smc_features(hwmgr,
				enable,
				data->smu_features[GNLD_DPM_UVD].smu_feature_biपंचांगap),
				"Attempt to Enable/Disable DPM UVD Failed!",
				वापस -1);
		data->smu_features[GNLD_DPM_UVD].enabled = enable;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vega12_घातer_gate_vce(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);

	अगर (data->vce_घातer_gated == bgate)
		वापस;

	data->vce_घातer_gated = bgate;
	vega12_enable_disable_vce_dpm(hwmgr, !bgate);
पूर्ण

अटल व्योम vega12_घातer_gate_uvd(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);

	अगर (data->uvd_घातer_gated == bgate)
		वापस;

	data->uvd_घातer_gated = bgate;
	vega12_enable_disable_uvd_dpm(hwmgr, !bgate);
पूर्ण

अटल bool
vega12_check_smc_update_required_क्रम_display_configuration(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	bool is_update_required = false;

	अगर (data->display_timing.num_existing_displays != hwmgr->display_config->num_display)
		is_update_required = true;

	अगर (data->registry_data.gfx_clk_deep_sleep_support) अणु
		अगर (data->display_timing.min_घड़ी_in_sr != hwmgr->display_config->min_core_set_घड़ी_in_sr)
			is_update_required = true;
	पूर्ण

	वापस is_update_required;
पूर्ण

अटल पूर्णांक vega12_disable_dpm_tasks(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक पंचांगp_result, result = 0;

	पंचांगp_result = vega12_disable_all_smu_features(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable all smu features!", result = पंचांगp_result);

	वापस result;
पूर्ण

अटल पूर्णांक vega12_घातer_off_asic(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	पूर्णांक result;

	result = vega12_disable_dpm_tasks(hwmgr);
	PP_ASSERT_WITH_CODE((0 == result),
			"[disable_dpm_tasks] Failed to disable DPM!",
			);
	data->water_marks_biपंचांगap &= ~(WaterMarksLoaded);

	वापस result;
पूर्ण

#अगर 0
अटल व्योम vega12_find_min_घड़ी_index(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t *sclk_idx, uपूर्णांक32_t *mclk_idx,
		uपूर्णांक32_t min_sclk, uपूर्णांक32_t min_mclk)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	काष्ठा vega12_dpm_table *dpm_table = &(data->dpm_table);
	uपूर्णांक32_t i;

	क्रम (i = 0; i < dpm_table->gfx_table.count; i++) अणु
		अगर (dpm_table->gfx_table.dpm_levels[i].enabled &&
			dpm_table->gfx_table.dpm_levels[i].value >= min_sclk) अणु
			*sclk_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dpm_table->mem_table.count; i++) अणु
		अगर (dpm_table->mem_table.dpm_levels[i].enabled &&
			dpm_table->mem_table.dpm_levels[i].value >= min_mclk) अणु
			*mclk_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर 0
अटल पूर्णांक vega12_set_घातer_profile_state(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा amd_pp_profile *request)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_sclk_od(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	काष्ठा vega12_single_dpm_table *sclk_table = &(data->dpm_table.gfx_table);
	काष्ठा vega12_single_dpm_table *golden_sclk_table =
			&(data->golden_dpm_table.gfx_table);
	पूर्णांक value = sclk_table->dpm_levels[sclk_table->count - 1].value;
	पूर्णांक golden_value = golden_sclk_table->dpm_levels
			[golden_sclk_table->count - 1].value;

	value -= golden_value;
	value = DIV_ROUND_UP(value * 100, golden_value);

	वापस value;
पूर्ण

अटल पूर्णांक vega12_set_sclk_od(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t value)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_mclk_od(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data = (काष्ठा vega12_hwmgr *)(hwmgr->backend);
	काष्ठा vega12_single_dpm_table *mclk_table = &(data->dpm_table.mem_table);
	काष्ठा vega12_single_dpm_table *golden_mclk_table =
			&(data->golden_dpm_table.mem_table);
	पूर्णांक value = mclk_table->dpm_levels[mclk_table->count - 1].value;
	पूर्णांक golden_value = golden_mclk_table->dpm_levels
			[golden_mclk_table->count - 1].value;

	value -= golden_value;
	value = DIV_ROUND_UP(value * 100, golden_value);

	वापस value;
पूर्ण

अटल पूर्णांक vega12_set_mclk_od(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t value)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक vega12_notअगरy_cac_buffer_info(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक32_t भव_addr_low,
					uपूर्णांक32_t भव_addr_hi,
					uपूर्णांक32_t mc_addr_low,
					uपूर्णांक32_t mc_addr_hi,
					uपूर्णांक32_t size)
अणु
	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetSystemVirtualDramAddrHigh,
					भव_addr_hi,
					शून्य);
	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetSystemVirtualDramAddrLow,
					भव_addr_low,
					शून्य);
	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DramLogSetDramAddrHigh,
					mc_addr_hi,
					शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DramLogSetDramAddrLow,
					mc_addr_low,
					शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DramLogSetDramSize,
					size,
					शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक vega12_get_thermal_temperature_range(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा PP_TemperatureRange *thermal_data)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);

	स_नकल(thermal_data, &SMU7ThermalWithDelayPolicy[0], माप(काष्ठा PP_TemperatureRange));

	thermal_data->max = pp_table->TedgeLimit *
		PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	thermal_data->edge_emergency_max = (pp_table->TedgeLimit + CTF_OFFSET_EDGE) *
		PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	thermal_data->hotspot_crit_max = pp_table->ThotspotLimit *
		PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	thermal_data->hotspot_emergency_max = (pp_table->ThotspotLimit + CTF_OFFSET_HOTSPOT) *
		PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	thermal_data->mem_crit_max = pp_table->ThbmLimit *
		PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	thermal_data->mem_emergency_max = (pp_table->ThbmLimit + CTF_OFFSET_HBM)*
		PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_enable_gfx_off(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	पूर्णांक ret = 0;

	अगर (data->gfxoff_controlled_by_driver)
		ret = smum_send_msg_to_smc(hwmgr, PPSMC_MSG_AllowGfxOff, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक vega12_disable_gfx_off(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	पूर्णांक ret = 0;

	अगर (data->gfxoff_controlled_by_driver)
		ret = smum_send_msg_to_smc(hwmgr, PPSMC_MSG_DisallowGfxOff, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक vega12_gfx_off_control(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	अगर (enable)
		वापस vega12_enable_gfx_off(hwmgr);
	अन्यथा
		वापस vega12_disable_gfx_off(hwmgr);
पूर्ण

अटल पूर्णांक vega12_get_perक्रमmance_level(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा pp_hw_घातer_state *state,
				PHM_Perक्रमmanceLevelDesignation designation, uपूर्णांक32_t index,
				PHM_Perक्रमmanceLevel *level)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vega12_set_mp1_state(काष्ठा pp_hwmgr *hwmgr,
				क्रमागत pp_mp1_state mp1_state)
अणु
	uपूर्णांक16_t msg;
	पूर्णांक ret;

	चयन (mp1_state) अणु
	हाल PP_MP1_STATE_UNLOAD:
		msg = PPSMC_MSG_PrepareMp1ForUnload;
		अवरोध;
	हाल PP_MP1_STATE_SHUTDOWN:
	हाल PP_MP1_STATE_RESET:
	हाल PP_MP1_STATE_NONE:
	शेष:
		वापस 0;
	पूर्ण

	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc(hwmgr, msg, शून्य)) == 0,
			    "[PrepareMp1] Failed!",
			    वापस ret);

	वापस 0;
पूर्ण

अटल व्योम vega12_init_gpu_metrics_v1_0(काष्ठा gpu_metrics_v1_0 *gpu_metrics)
अणु
	स_रखो(gpu_metrics, 0xFF, माप(काष्ठा gpu_metrics_v1_0));

	gpu_metrics->common_header.काष्ठाure_size =
				माप(काष्ठा gpu_metrics_v1_0);
	gpu_metrics->common_header.क्रमmat_revision = 1;
	gpu_metrics->common_header.content_revision = 0;

	gpu_metrics->प्रणाली_घड़ी_counter = kसमय_get_bootसमय_ns();
पूर्ण

अटल sमाप_प्रकार vega12_get_gpu_metrics(काष्ठा pp_hwmgr *hwmgr,
				      व्योम **table)
अणु
	काष्ठा vega12_hwmgr *data =
			(काष्ठा vega12_hwmgr *)(hwmgr->backend);
	काष्ठा gpu_metrics_v1_0 *gpu_metrics =
			&data->gpu_metrics_table;
	SmuMetrics_t metrics;
	uपूर्णांक32_t fan_speed_rpm;
	पूर्णांक ret;

	ret = vega12_get_metrics_table(hwmgr, &metrics, true);
	अगर (ret)
		वापस ret;

	vega12_init_gpu_metrics_v1_0(gpu_metrics);

	gpu_metrics->temperature_edge = metrics.TemperatureEdge;
	gpu_metrics->temperature_hotspot = metrics.TemperatureHotspot;
	gpu_metrics->temperature_mem = metrics.TemperatureHBM;
	gpu_metrics->temperature_vrgfx = metrics.TemperatureVrGfx;
	gpu_metrics->temperature_vrmem = metrics.TemperatureVrMem;

	gpu_metrics->average_gfx_activity = metrics.AverageGfxActivity;
	gpu_metrics->average_umc_activity = metrics.AverageUclkActivity;

	gpu_metrics->average_gfxclk_frequency = metrics.AverageGfxclkFrequency;
	gpu_metrics->average_socclk_frequency = metrics.AverageSocclkFrequency;
	gpu_metrics->average_uclk_frequency = metrics.AverageUclkFrequency;

	gpu_metrics->current_gfxclk = metrics.CurrClock[PPCLK_GFXCLK];
	gpu_metrics->current_socclk = metrics.CurrClock[PPCLK_SOCCLK];
	gpu_metrics->current_uclk = metrics.CurrClock[PPCLK_UCLK];
	gpu_metrics->current_vclk0 = metrics.CurrClock[PPCLK_VCLK];
	gpu_metrics->current_dclk0 = metrics.CurrClock[PPCLK_DCLK];

	gpu_metrics->throttle_status = metrics.ThrottlerStatus;

	vega12_fan_ctrl_get_fan_speed_rpm(hwmgr, &fan_speed_rpm);
	gpu_metrics->current_fan_speed = (uपूर्णांक16_t)fan_speed_rpm;

	gpu_metrics->pcie_link_width =
			vega12_get_current_pcie_link_width(hwmgr);
	gpu_metrics->pcie_link_speed =
			vega12_get_current_pcie_link_speed(hwmgr);

	*table = (व्योम *)gpu_metrics;

	वापस माप(काष्ठा gpu_metrics_v1_0);
पूर्ण

अटल स्थिर काष्ठा pp_hwmgr_func vega12_hwmgr_funcs = अणु
	.backend_init = vega12_hwmgr_backend_init,
	.backend_fini = vega12_hwmgr_backend_fini,
	.asic_setup = vega12_setup_asic_task,
	.dynamic_state_management_enable = vega12_enable_dpm_tasks,
	.dynamic_state_management_disable = vega12_disable_dpm_tasks,
	.patch_boot_state = vega12_patch_boot_state,
	.get_sclk = vega12_dpm_get_sclk,
	.get_mclk = vega12_dpm_get_mclk,
	.notअगरy_smc_display_config_after_ps_adjusपंचांगent =
			vega12_notअगरy_smc_display_config_after_ps_adjusपंचांगent,
	.क्रमce_dpm_level = vega12_dpm_क्रमce_dpm_level,
	.stop_thermal_controller = vega12_thermal_stop_thermal_controller,
	.get_fan_speed_info = vega12_fan_ctrl_get_fan_speed_info,
	.reset_fan_speed_to_शेष =
			vega12_fan_ctrl_reset_fan_speed_to_शेष,
	.get_fan_speed_rpm = vega12_fan_ctrl_get_fan_speed_rpm,
	.set_fan_control_mode = vega12_set_fan_control_mode,
	.get_fan_control_mode = vega12_get_fan_control_mode,
	.पढ़ो_sensor = vega12_पढ़ो_sensor,
	.get_dal_घातer_level = vega12_get_dal_घातer_level,
	.get_घड़ी_by_type_with_latency = vega12_get_घड़ी_by_type_with_latency,
	.get_घड़ी_by_type_with_voltage = vega12_get_घड़ी_by_type_with_voltage,
	.set_watermarks_क्रम_घड़ीs_ranges = vega12_set_watermarks_क्रम_घड़ीs_ranges,
	.display_घड़ी_voltage_request = vega12_display_घड़ी_voltage_request,
	.क्रमce_घड़ी_level = vega12_क्रमce_घड़ी_level,
	.prपूर्णांक_घड़ी_levels = vega12_prपूर्णांक_घड़ी_levels,
	.apply_घड़ीs_adjust_rules =
		vega12_apply_घड़ीs_adjust_rules,
	.pre_display_config_changed =
		vega12_pre_display_configuration_changed_task,
	.display_config_changed = vega12_display_configuration_changed_task,
	.घातergate_uvd = vega12_घातer_gate_uvd,
	.घातergate_vce = vega12_घातer_gate_vce,
	.check_smc_update_required_क्रम_display_configuration =
			vega12_check_smc_update_required_क्रम_display_configuration,
	.घातer_off_asic = vega12_घातer_off_asic,
	.disable_smc_firmware_ctf = vega12_thermal_disable_alert,
#अगर 0
	.set_घातer_profile_state = vega12_set_घातer_profile_state,
	.get_sclk_od = vega12_get_sclk_od,
	.set_sclk_od = vega12_set_sclk_od,
	.get_mclk_od = vega12_get_mclk_od,
	.set_mclk_od = vega12_set_mclk_od,
#पूर्ण_अगर
	.notअगरy_cac_buffer_info = vega12_notअगरy_cac_buffer_info,
	.get_thermal_temperature_range = vega12_get_thermal_temperature_range,
	.रेजिस्टर_irq_handlers = smu9_रेजिस्टर_irq_handlers,
	.start_thermal_controller = vega12_start_thermal_controller,
	.घातergate_gfx = vega12_gfx_off_control,
	.get_perक्रमmance_level = vega12_get_perक्रमmance_level,
	.get_asic_baco_capability = smu9_baco_get_capability,
	.get_asic_baco_state = smu9_baco_get_state,
	.set_asic_baco_state = vega12_baco_set_state,
	.get_ppfeature_status = vega12_get_ppfeature_status,
	.set_ppfeature_status = vega12_set_ppfeature_status,
	.set_mp1_state = vega12_set_mp1_state,
	.get_gpu_metrics = vega12_get_gpu_metrics,
पूर्ण;

पूर्णांक vega12_hwmgr_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	hwmgr->hwmgr_func = &vega12_hwmgr_funcs;
	hwmgr->pptable_func = &vega12_pptable_funcs;

	वापस 0;
पूर्ण
