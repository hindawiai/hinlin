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

#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "hwmgr.h"
#समावेश "amd_powerplay.h"
#समावेश "vega20_smumgr.h"
#समावेश "hardwaremanager.h"
#समावेश "ppatomfwctrl.h"
#समावेश "atomfirmware.h"
#समावेश "cgs_common.h"
#समावेश "vega20_powertune.h"
#समावेश "vega20_inc.h"
#समावेश "pppcielanes.h"
#समावेश "vega20_hwmgr.h"
#समावेश "vega20_processpptables.h"
#समावेश "vega20_pptable.h"
#समावेश "vega20_thermal.h"
#समावेश "vega20_ppsmc.h"
#समावेश "pp_debug.h"
#समावेश "amd_pcie_helpers.h"
#समावेश "ppinterrupt.h"
#समावेश "pp_overdriver.h"
#समावेश "pp_thermal.h"
#समावेश "soc15_common.h"
#समावेश "vega20_baco.h"
#समावेश "smuio/smuio_9_0_offset.h"
#समावेश "smuio/smuio_9_0_sh_mask.h"
#समावेश "nbio/nbio_7_4_sh_mask.h"

#घोषणा smnPCIE_LC_SPEED_CNTL			0x11140290
#घोषणा smnPCIE_LC_LINK_WIDTH_CNTL		0x11140288

#घोषणा LINK_WIDTH_MAX				6
#घोषणा LINK_SPEED_MAX				3
अटल स्थिर पूर्णांक link_width[] = अणु0, 1, 2, 4, 8, 12, 16पूर्ण;
अटल स्थिर पूर्णांक link_speed[] = अणु25, 50, 80, 160पूर्ण;

अटल व्योम vega20_set_शेष_registry_data(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);

	data->gfxclk_average_alpha = PPVEGA20_VEGA20GFXCLKAVERAGEALPHA_DFLT;
	data->socclk_average_alpha = PPVEGA20_VEGA20SOCCLKAVERAGEALPHA_DFLT;
	data->uclk_average_alpha = PPVEGA20_VEGA20UCLKCLKAVERAGEALPHA_DFLT;
	data->gfx_activity_average_alpha = PPVEGA20_VEGA20GFXACTIVITYAVERAGEALPHA_DFLT;
	data->lowest_uclk_reserved_क्रम_ulv = PPVEGA20_VEGA20LOWESTUCLKRESERVEDFORULV_DFLT;

	data->display_voltage_mode = PPVEGA20_VEGA20DISPLAYVOLTAGEMODE_DFLT;
	data->dcef_clk_quad_eqn_a = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->dcef_clk_quad_eqn_b = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->dcef_clk_quad_eqn_c = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_a = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_b = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_c = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_a = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_b = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_c = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_a = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_b = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_c = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;

	/*
	 * Disable the following features क्रम now:
	 *   GFXCLK DS
	 *   SOCLK DS
	 *   LCLK DS
	 *   DCEFCLK DS
	 *   FCLK DS
	 *   MP1CLK DS
	 *   MP0CLK DS
	 */
	data->registry_data.disallowed_features = 0xE0041C00;
	/* ECC feature should be disabled on old SMUs */
	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetSmuVersion, &hwmgr->smu_version);
	अगर (hwmgr->smu_version < 0x282100)
		data->registry_data.disallowed_features |= FEATURE_ECC_MASK;

	अगर (!(hwmgr->feature_mask & PP_PCIE_DPM_MASK))
		data->registry_data.disallowed_features |= FEATURE_DPM_LINK_MASK;

	अगर (!(hwmgr->feature_mask & PP_SCLK_DPM_MASK))
		data->registry_data.disallowed_features |= FEATURE_DPM_GFXCLK_MASK;

	अगर (!(hwmgr->feature_mask & PP_SOCCLK_DPM_MASK))
		data->registry_data.disallowed_features |= FEATURE_DPM_SOCCLK_MASK;

	अगर (!(hwmgr->feature_mask & PP_MCLK_DPM_MASK))
		data->registry_data.disallowed_features |= FEATURE_DPM_UCLK_MASK;

	अगर (!(hwmgr->feature_mask & PP_DCEFCLK_DPM_MASK))
		data->registry_data.disallowed_features |= FEATURE_DPM_DCEFCLK_MASK;

	अगर (!(hwmgr->feature_mask & PP_ULV_MASK))
		data->registry_data.disallowed_features |= FEATURE_ULV_MASK;

	अगर (!(hwmgr->feature_mask & PP_SCLK_DEEP_SLEEP_MASK))
		data->registry_data.disallowed_features |= FEATURE_DS_GFXCLK_MASK;

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
	data->registry_data.od8_feature_enable = 1;
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
	data->registry_data.fclk_gfxclk_ratio = 0;
	data->registry_data.स्वतः_watपंचांगan_threshold = 50;
	data->registry_data.gfxoff_controlled_by_driver = 1;
	data->gfxoff_allowed = false;
	data->counter_gfxoff = 0;
	data->registry_data.pcie_dpm_key_disabled = !(hwmgr->feature_mask & PP_PCIE_DPM_MASK);
पूर्ण

अटल पूर्णांक vega20_set_features_platक्रमm_caps(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	अगर (data->vddci_control == VEGA20_VOLTAGE_CONTROL_NONE)
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_ControlVDDCI);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_TablelessHardwareInterface);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_BACO);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_EnableSMU7ThermalManagement);

	अगर (adev->pg_flags & AMD_PG_SUPPORT_UVD)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_UVDPowerGating);

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCE)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_VCEPowerGating);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_UnTabledHardwareInterface);

	अगर (data->registry_data.od8_feature_enable)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_OD8inACSupport);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ActivityReporting);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_FanSpeedInTableIsRPM);

	अगर (data->registry_data.od_state_in_dc_support) अणु
		अगर (data->registry_data.od8_feature_enable)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_OD8inDCSupport);
	पूर्ण

	अगर (data->registry_data.thermal_support &&
	    data->registry_data.fuzzy_fan_control_support &&
	    hwmgr->thermal_controller.advanceFanControlParameters.usTMax)
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
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_DiDtSupport);
		अगर (data->registry_data.sq_ramping_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_SQRamping);
		अगर (data->registry_data.db_ramping_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_DBRamping);
		अगर (data->registry_data.td_ramping_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_TDRamping);
		अगर (data->registry_data.tcp_ramping_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_TCPRamping);
		अगर (data->registry_data.dbr_ramping_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_DBRRamping);
		अगर (data->registry_data.edc_didt_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_DiDtEDCEnable);
		अगर (data->registry_data.gc_didt_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_GCEDC);
		अगर (data->registry_data.psm_didt_support)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_PSM);
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

	अगर (data->lowest_uclk_reserved_क्रम_ulv != PPVEGA20_VEGA20LOWESTUCLKRESERVEDFORULV_DFLT) अणु
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

अटल व्योम vega20_init_dpm_शेषs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
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
	data->smu_features[GNLD_DPM_FCLK].smu_feature_id = FEATURE_DPM_FCLK_BIT;
	data->smu_features[GNLD_DS_FCLK].smu_feature_id = FEATURE_DS_FCLK_BIT;
	data->smu_features[GNLD_DS_MP1CLK].smu_feature_id = FEATURE_DS_MP1CLK_BIT;
	data->smu_features[GNLD_DS_MP0CLK].smu_feature_id = FEATURE_DS_MP0CLK_BIT;
	data->smu_features[GNLD_XGMI].smu_feature_id = FEATURE_XGMI_BIT;
	data->smu_features[GNLD_ECC].smu_feature_id = FEATURE_ECC_BIT;

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

अटल पूर्णांक vega20_set_निजी_data_based_on_pptable(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vega20_hwmgr_backend_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	kमुक्त(hwmgr->backend);
	hwmgr->backend = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_hwmgr_backend_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	data = kzalloc(माप(काष्ठा vega20_hwmgr), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	hwmgr->backend = data;

	hwmgr->workload_mask = 1 << hwmgr->workload_prority[PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT];
	hwmgr->घातer_profile_mode = PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT;
	hwmgr->शेष_घातer_profile_mode = PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT;

	vega20_set_शेष_registry_data(hwmgr);

	data->disable_dpm_mask = 0xff;

	/* need to set voltage control types beक्रमe EVV patching */
	data->vddc_control = VEGA20_VOLTAGE_CONTROL_NONE;
	data->mvdd_control = VEGA20_VOLTAGE_CONTROL_NONE;
	data->vddci_control = VEGA20_VOLTAGE_CONTROL_NONE;

	data->water_marks_biपंचांगap = 0;
	data->avfs_exist = false;

	vega20_set_features_platक्रमm_caps(hwmgr);

	vega20_init_dpm_शेषs(hwmgr);

	/* Parse pptable data पढ़ो from VBIOS */
	vega20_set_निजी_data_based_on_pptable(hwmgr);

	data->is_tlu_enabled = false;

	hwmgr->platक्रमm_descriptor.hardwareActivityPerक्रमmanceLevels =
			VEGA20_MAX_HARDWARE_POWERLEVELS;
	hwmgr->platक्रमm_descriptor.hardwarePerक्रमmanceLevels = 2;
	hwmgr->platक्रमm_descriptor.minimumClocksReductionPercentage = 50;

	hwmgr->platक्रमm_descriptor.vbiosInterruptId = 0x20000400; /* IRQ_SOURCE1_SW_INT */
	/* The true घड़ी step depends on the frequency, typically 4.5 or 9 MHz. Here we use 5. */
	hwmgr->platक्रमm_descriptor.घड़ीStep.engineClock = 500;
	hwmgr->platक्रमm_descriptor.घड़ीStep.memoryClock = 500;

	data->total_active_cus = adev->gfx.cu_info.number;
	data->is_custom_profile_set = false;

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_init_sclk_threshold(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);

	data->low_sclk_पूर्णांकerrupt_threshold = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_setup_asic_task(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	पूर्णांक ret = 0;
	bool use_baco = (amdgpu_in_reset(adev) &&
			 (amdgpu_asic_reset_method(adev) == AMD_RESET_METHOD_BACO)) ||
		(adev->in_runpm && amdgpu_asic_supports_baco(adev));

	ret = vega20_init_sclk_threshold(hwmgr);
	PP_ASSERT_WITH_CODE(!ret,
			"Failed to init sclk threshold!",
			वापस ret);

	अगर (use_baco) अणु
		ret = vega20_baco_apply_vdci_flush_workaround(hwmgr);
		अगर (ret)
			pr_err("Failed to apply vega20 baco workaround!\n");
	पूर्ण

	वापस ret;
पूर्ण

/*
 * @fn vega20_init_dpm_state
 * @brief Function to initialize all Soft Min/Max and Hard Min/Max to 0xff.
 *
 * @param    dpm_state - the address of the DPM Table to initiailize.
 * @वापस   None.
 */
अटल व्योम vega20_init_dpm_state(काष्ठा vega20_dpm_state *dpm_state)
अणु
	dpm_state->soft_min_level = 0x0;
	dpm_state->soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_state->hard_min_level = 0x0;
	dpm_state->hard_max_level = VG20_CLOCK_MAX_DEFAULT;
पूर्ण

अटल पूर्णांक vega20_get_number_of_dpm_level(काष्ठा pp_hwmgr *hwmgr,
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

अटल पूर्णांक vega20_get_dpm_frequency_by_index(काष्ठा pp_hwmgr *hwmgr,
		PPCLK_e clk_id, uपूर्णांक32_t index, uपूर्णांक32_t *clk)
अणु
	पूर्णांक ret = 0;

	ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_GetDpmFreqByIndex,
			(clk_id << 16 | index),
			clk);
	PP_ASSERT_WITH_CODE(!ret,
			"[GetDpmFreqByIndex] failed to get dpm freq by index!",
			वापस ret);

	वापस ret;
पूर्ण

अटल पूर्णांक vega20_setup_single_dpm_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा vega20_single_dpm_table *dpm_table, PPCLK_e clk_id)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t i, num_of_levels, clk;

	ret = vega20_get_number_of_dpm_level(hwmgr, clk_id, &num_of_levels);
	PP_ASSERT_WITH_CODE(!ret,
			"[SetupSingleDpmTable] failed to get clk levels!",
			वापस ret);

	dpm_table->count = num_of_levels;

	क्रम (i = 0; i < num_of_levels; i++) अणु
		ret = vega20_get_dpm_frequency_by_index(hwmgr, clk_id, i, &clk);
		PP_ASSERT_WITH_CODE(!ret,
			"[SetupSingleDpmTable] failed to get clk of specific level!",
			वापस ret);
		dpm_table->dpm_levels[i].value = clk;
		dpm_table->dpm_levels[i].enabled = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vega20_setup_gfxclk_dpm_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_single_dpm_table *dpm_table;
	पूर्णांक ret = 0;

	dpm_table = &(data->dpm_table.gfx_table);
	अगर (data->smu_features[GNLD_DPM_GFXCLK].enabled) अणु
		ret = vega20_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_GFXCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get gfxclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.gfx_घड़ी / 100;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vega20_setup_memclk_dpm_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_single_dpm_table *dpm_table;
	पूर्णांक ret = 0;

	dpm_table = &(data->dpm_table.mem_table);
	अगर (data->smu_features[GNLD_DPM_UCLK].enabled) अणु
		ret = vega20_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_UCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get memclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.mem_घड़ी / 100;
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
अटल पूर्णांक vega20_setup_शेष_dpm_tables(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_single_dpm_table *dpm_table;
	पूर्णांक ret = 0;

	स_रखो(&data->dpm_table, 0, माप(data->dpm_table));

	/* socclk */
	dpm_table = &(data->dpm_table.soc_table);
	अगर (data->smu_features[GNLD_DPM_SOCCLK].enabled) अणु
		ret = vega20_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_SOCCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get socclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.soc_घड़ी / 100;
	पूर्ण
	vega20_init_dpm_state(&(dpm_table->dpm_state));

	/* gfxclk */
	dpm_table = &(data->dpm_table.gfx_table);
	ret = vega20_setup_gfxclk_dpm_table(hwmgr);
	अगर (ret)
		वापस ret;
	vega20_init_dpm_state(&(dpm_table->dpm_state));

	/* memclk */
	dpm_table = &(data->dpm_table.mem_table);
	ret = vega20_setup_memclk_dpm_table(hwmgr);
	अगर (ret)
		वापस ret;
	vega20_init_dpm_state(&(dpm_table->dpm_state));

	/* eclk */
	dpm_table = &(data->dpm_table.eclk_table);
	अगर (data->smu_features[GNLD_DPM_VCE].enabled) अणु
		ret = vega20_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_ECLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get eclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.eघड़ी / 100;
	पूर्ण
	vega20_init_dpm_state(&(dpm_table->dpm_state));

	/* vclk */
	dpm_table = &(data->dpm_table.vclk_table);
	अगर (data->smu_features[GNLD_DPM_UVD].enabled) अणु
		ret = vega20_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_VCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get vclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.vघड़ी / 100;
	पूर्ण
	vega20_init_dpm_state(&(dpm_table->dpm_state));

	/* dclk */
	dpm_table = &(data->dpm_table.dclk_table);
	अगर (data->smu_features[GNLD_DPM_UVD].enabled) अणु
		ret = vega20_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_DCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get dclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.dघड़ी / 100;
	पूर्ण
	vega20_init_dpm_state(&(dpm_table->dpm_state));

	/* dcefclk */
	dpm_table = &(data->dpm_table.dcef_table);
	अगर (data->smu_features[GNLD_DPM_DCEFCLK].enabled) अणु
		ret = vega20_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_DCEFCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get dcefclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.dcef_घड़ी / 100;
	पूर्ण
	vega20_init_dpm_state(&(dpm_table->dpm_state));

	/* pixclk */
	dpm_table = &(data->dpm_table.pixel_table);
	अगर (data->smu_features[GNLD_DPM_DCEFCLK].enabled) अणु
		ret = vega20_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_PIXCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get pixclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा
		dpm_table->count = 0;
	vega20_init_dpm_state(&(dpm_table->dpm_state));

	/* dispclk */
	dpm_table = &(data->dpm_table.display_table);
	अगर (data->smu_features[GNLD_DPM_DCEFCLK].enabled) अणु
		ret = vega20_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_DISPCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get dispclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा
		dpm_table->count = 0;
	vega20_init_dpm_state(&(dpm_table->dpm_state));

	/* phyclk */
	dpm_table = &(data->dpm_table.phy_table);
	अगर (data->smu_features[GNLD_DPM_DCEFCLK].enabled) अणु
		ret = vega20_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_PHYCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get phyclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा
		dpm_table->count = 0;
	vega20_init_dpm_state(&(dpm_table->dpm_state));

	/* fclk */
	dpm_table = &(data->dpm_table.fclk_table);
	अगर (data->smu_features[GNLD_DPM_FCLK].enabled) अणु
		ret = vega20_setup_single_dpm_table(hwmgr, dpm_table, PPCLK_FCLK);
		PP_ASSERT_WITH_CODE(!ret,
				"[SetupDefaultDpmTable] failed to get fclk dpm levels!",
				वापस ret);
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = data->vbios_boot_state.fघड़ी / 100;
	पूर्ण
	vega20_init_dpm_state(&(dpm_table->dpm_state));

	/* save a copy of the शेष DPM table */
	स_नकल(&(data->golden_dpm_table), &(data->dpm_table),
			माप(काष्ठा vega20_dpm_table));

	वापस 0;
पूर्ण

/**
 * Initializes the SMC table and uploads it
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * वापस:  always 0
 */
अटल पूर्णांक vega20_init_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा pp_atomfwctrl_bios_boot_up_values boot_up_values;
	काष्ठा phm_ppt_v3_inक्रमmation *pptable_inक्रमmation =
		(काष्ठा phm_ppt_v3_inक्रमmation *)hwmgr->pptable;

	result = pp_atomfwctrl_get_vbios_bootup_values(hwmgr, &boot_up_values);
	PP_ASSERT_WITH_CODE(!result,
			"[InitSMCTable] Failed to get vbios bootup values!",
			वापस result);

	data->vbios_boot_state.vddc     = boot_up_values.usVddc;
	data->vbios_boot_state.vddci    = boot_up_values.usVddci;
	data->vbios_boot_state.mvddc    = boot_up_values.usMvddc;
	data->vbios_boot_state.gfx_घड़ी = boot_up_values.ulGfxClk;
	data->vbios_boot_state.mem_घड़ी = boot_up_values.ulUClk;
	data->vbios_boot_state.soc_घड़ी = boot_up_values.ulSocClk;
	data->vbios_boot_state.dcef_घड़ी = boot_up_values.ulDCEFClk;
	data->vbios_boot_state.eघड़ी = boot_up_values.ulEClk;
	data->vbios_boot_state.vघड़ी = boot_up_values.ulVClk;
	data->vbios_boot_state.dघड़ी = boot_up_values.ulDClk;
	data->vbios_boot_state.fघड़ी = boot_up_values.ulFClk;
	data->vbios_boot_state.uc_cooling_id = boot_up_values.ucCoolingID;

	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetMinDeepSleepDcefclk,
		(uपूर्णांक32_t)(data->vbios_boot_state.dcef_घड़ी / 100),
			शून्य);

	स_नकल(pp_table, pptable_inक्रमmation->smc_pptable, माप(PPTable_t));

	result = smum_smc_table_manager(hwmgr,
					(uपूर्णांक8_t *)pp_table, TABLE_PPTABLE, false);
	PP_ASSERT_WITH_CODE(!result,
			"[InitSMCTable] Failed to upload PPtable!",
			वापस result);

	वापस 0;
पूर्ण

/*
 * Override PCIe link speed and link width क्रम DPM Level 1. PPTable entries
 * reflect the ASIC capabilities and not the प्रणाली capabilities. For e.g.
 * Vega20 board in a PCI Gen3 प्रणाली. In this हाल, when SMU's tries to चयन
 * to DPM1, it fails as प्रणाली करोesn't support Gen4.
 */
अटल पूर्णांक vega20_override_pcie_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
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
		ret = vega20_enable_smc_features(hwmgr,
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

अटल पूर्णांक vega20_set_allowed_featuresmask(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t allowed_features_low = 0, allowed_features_high = 0;
	पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < GNLD_FEATURES_MAX; i++)
		अगर (data->smu_features[i].allowed)
			data->smu_features[i].smu_feature_id > 31 ?
				(allowed_features_high |=
				 ((data->smu_features[i].smu_feature_biपंचांगap >> SMU_FEATURES_HIGH_SHIFT)
				  & 0xFFFFFFFF)) :
				(allowed_features_low |=
				 ((data->smu_features[i].smu_feature_biपंचांगap >> SMU_FEATURES_LOW_SHIFT)
				  & 0xFFFFFFFF));

	ret = smum_send_msg_to_smc_with_parameter(hwmgr,
		PPSMC_MSG_SetAllowedFeaturesMaskHigh, allowed_features_high, शून्य);
	PP_ASSERT_WITH_CODE(!ret,
		"[SetAllowedFeaturesMask] Attempt to set allowed features mask(high) failed!",
		वापस ret);

	ret = smum_send_msg_to_smc_with_parameter(hwmgr,
		PPSMC_MSG_SetAllowedFeaturesMaskLow, allowed_features_low, शून्य);
	PP_ASSERT_WITH_CODE(!ret,
		"[SetAllowedFeaturesMask] Attempt to set allowed features mask (low) failed!",
		वापस ret);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_run_btc(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस smum_send_msg_to_smc(hwmgr, PPSMC_MSG_RunBtc, शून्य);
पूर्ण

अटल पूर्णांक vega20_run_btc_afll(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस smum_send_msg_to_smc(hwmgr, PPSMC_MSG_RunAfllBtc, शून्य);
पूर्ण

अटल पूर्णांक vega20_enable_all_smu_features(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	uपूर्णांक64_t features_enabled;
	पूर्णांक i;
	bool enabled;
	पूर्णांक ret = 0;

	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc(hwmgr,
			PPSMC_MSG_EnableAllSmuFeatures,
			शून्य)) == 0,
			"[EnableAllSMUFeatures] Failed to enable all smu features!",
			वापस ret);

	ret = vega20_get_enabled_smc_features(hwmgr, &features_enabled);
	PP_ASSERT_WITH_CODE(!ret,
			"[EnableAllSmuFeatures] Failed to get enabled smc features!",
			वापस ret);

	क्रम (i = 0; i < GNLD_FEATURES_MAX; i++) अणु
		enabled = (features_enabled & data->smu_features[i].smu_feature_biपंचांगap) ?
			true : false;
		data->smu_features[i].enabled = enabled;
		data->smu_features[i].supported = enabled;

#अगर 0
		अगर (data->smu_features[i].allowed && !enabled)
			pr_info("[EnableAllSMUFeatures] feature %d is expected enabled!", i);
		अन्यथा अगर (!data->smu_features[i].allowed && enabled)
			pr_info("[EnableAllSMUFeatures] feature %d is expected disabled!", i);
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_notअगरy_smc_display_change(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);

	अगर (data->smu_features[GNLD_DPM_UCLK].enabled)
		वापस smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetUclkFastSwitch,
			1,
			शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_send_घड़ी_ratio(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);

	वापस smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetFclkGfxClkRatio,
			data->registry_data.fclk_gfxclk_ratio,
			शून्य);
पूर्ण

अटल पूर्णांक vega20_disable_all_smu_features(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	पूर्णांक i, ret = 0;

	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc(hwmgr,
			PPSMC_MSG_DisableAllSmuFeatures,
			शून्य)) == 0,
			"[DisableAllSMUFeatures] Failed to disable all smu features!",
			वापस ret);

	क्रम (i = 0; i < GNLD_FEATURES_MAX; i++)
		data->smu_features[i].enabled = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_od8_set_feature_capabilities(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा phm_ppt_v3_inक्रमmation *pptable_inक्रमmation =
		(काष्ठा phm_ppt_v3_inक्रमmation *)hwmgr->pptable;
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा vega20_od8_settings *od_settings = &(data->od8_settings);

	od_settings->overdrive8_capabilities = 0;

	अगर (data->smu_features[GNLD_DPM_GFXCLK].enabled) अणु
		अगर (pptable_inक्रमmation->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_GFXCLK_LIMITS] &&
		    pptable_inक्रमmation->od_settings_max[OD8_SETTING_GFXCLK_FMAX] > 0 &&
		    pptable_inक्रमmation->od_settings_min[OD8_SETTING_GFXCLK_FMIN] > 0 &&
		    (pptable_inक्रमmation->od_settings_max[OD8_SETTING_GFXCLK_FMAX] >=
		    pptable_inक्रमmation->od_settings_min[OD8_SETTING_GFXCLK_FMIN]))
			od_settings->overdrive8_capabilities |= OD8_GFXCLK_LIMITS;

		अगर (pptable_inक्रमmation->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_GFXCLK_CURVE] &&
		    (pptable_inक्रमmation->od_settings_min[OD8_SETTING_GFXCLK_VOLTAGE1] >=
		     pp_table->MinVoltageGfx / VOLTAGE_SCALE) &&
		    (pptable_inक्रमmation->od_settings_max[OD8_SETTING_GFXCLK_VOLTAGE3] <=
		     pp_table->MaxVoltageGfx / VOLTAGE_SCALE) &&
		    (pptable_inक्रमmation->od_settings_max[OD8_SETTING_GFXCLK_VOLTAGE3] >=
		     pptable_inक्रमmation->od_settings_min[OD8_SETTING_GFXCLK_VOLTAGE1]))
			od_settings->overdrive8_capabilities |= OD8_GFXCLK_CURVE;
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_UCLK].enabled) अणु
		pptable_inक्रमmation->od_settings_min[OD8_SETTING_UCLK_FMAX] =
			data->dpm_table.mem_table.dpm_levels[data->dpm_table.mem_table.count - 2].value;
		अगर (pptable_inक्रमmation->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_UCLK_MAX] &&
		    pptable_inक्रमmation->od_settings_min[OD8_SETTING_UCLK_FMAX] > 0 &&
		    pptable_inक्रमmation->od_settings_max[OD8_SETTING_UCLK_FMAX] > 0 &&
		    (pptable_inक्रमmation->od_settings_max[OD8_SETTING_UCLK_FMAX] >=
		    pptable_inक्रमmation->od_settings_min[OD8_SETTING_UCLK_FMAX]))
			od_settings->overdrive8_capabilities |= OD8_UCLK_MAX;
	पूर्ण

	अगर (pptable_inक्रमmation->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_POWER_LIMIT] &&
	    pptable_inक्रमmation->od_settings_max[OD8_SETTING_POWER_PERCENTAGE] > 0 &&
	    pptable_inक्रमmation->od_settings_max[OD8_SETTING_POWER_PERCENTAGE] <= 100 &&
	    pptable_inक्रमmation->od_settings_min[OD8_SETTING_POWER_PERCENTAGE] > 0 &&
	    pptable_inक्रमmation->od_settings_min[OD8_SETTING_POWER_PERCENTAGE] <= 100)
		od_settings->overdrive8_capabilities |= OD8_POWER_LIMIT;

	अगर (data->smu_features[GNLD_FAN_CONTROL].enabled) अणु
		अगर (pptable_inक्रमmation->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_FAN_ACOUSTIC_LIMIT] &&
		    pptable_inक्रमmation->od_settings_min[OD8_SETTING_FAN_ACOUSTIC_LIMIT] > 0 &&
		    pptable_inक्रमmation->od_settings_max[OD8_SETTING_FAN_ACOUSTIC_LIMIT] > 0 &&
		    (pptable_inक्रमmation->od_settings_max[OD8_SETTING_FAN_ACOUSTIC_LIMIT] >=
		     pptable_inक्रमmation->od_settings_min[OD8_SETTING_FAN_ACOUSTIC_LIMIT]))
			od_settings->overdrive8_capabilities |= OD8_ACOUSTIC_LIMIT_SCLK;

		अगर (pptable_inक्रमmation->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_FAN_SPEED_MIN] &&
		    (pptable_inक्रमmation->od_settings_min[OD8_SETTING_FAN_MIN_SPEED] >=
		    (pp_table->FanPwmMin * pp_table->FanMaximumRpm / 100)) &&
		    pptable_inक्रमmation->od_settings_max[OD8_SETTING_FAN_MIN_SPEED] > 0 &&
		    (pptable_inक्रमmation->od_settings_max[OD8_SETTING_FAN_MIN_SPEED] >=
		     pptable_inक्रमmation->od_settings_min[OD8_SETTING_FAN_MIN_SPEED]))
			od_settings->overdrive8_capabilities |= OD8_FAN_SPEED_MIN;
	पूर्ण

	अगर (data->smu_features[GNLD_THERMAL].enabled) अणु
		अगर (pptable_inक्रमmation->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_TEMPERATURE_FAN] &&
		    pptable_inक्रमmation->od_settings_max[OD8_SETTING_FAN_TARGET_TEMP] > 0 &&
		    pptable_inक्रमmation->od_settings_min[OD8_SETTING_FAN_TARGET_TEMP] > 0 &&
		    (pptable_inक्रमmation->od_settings_max[OD8_SETTING_FAN_TARGET_TEMP] >=
		     pptable_inक्रमmation->od_settings_min[OD8_SETTING_FAN_TARGET_TEMP]))
			od_settings->overdrive8_capabilities |= OD8_TEMPERATURE_FAN;

		अगर (pptable_inक्रमmation->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_TEMPERATURE_SYSTEM] &&
		    pptable_inक्रमmation->od_settings_max[OD8_SETTING_OPERATING_TEMP_MAX] > 0 &&
		    pptable_inक्रमmation->od_settings_min[OD8_SETTING_OPERATING_TEMP_MAX] > 0 &&
		    (pptable_inक्रमmation->od_settings_max[OD8_SETTING_OPERATING_TEMP_MAX] >=
		     pptable_inक्रमmation->od_settings_min[OD8_SETTING_OPERATING_TEMP_MAX]))
			od_settings->overdrive8_capabilities |= OD8_TEMPERATURE_SYSTEM;
	पूर्ण

	अगर (pptable_inक्रमmation->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_MEMORY_TIMING_TUNE])
		od_settings->overdrive8_capabilities |= OD8_MEMORY_TIMING_TUNE;

	अगर (pptable_inक्रमmation->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_FAN_ZERO_RPM_CONTROL] &&
	    pp_table->FanZeroRpmEnable)
		od_settings->overdrive8_capabilities |= OD8_FAN_ZERO_RPM_CONTROL;

	अगर (!od_settings->overdrive8_capabilities)
		hwmgr->od_enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_od8_set_feature_id(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_od8_settings *od_settings = &(data->od8_settings);

	अगर (od_settings->overdrive8_capabilities & OD8_GFXCLK_LIMITS) अणु
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMIN].feature_id =
			OD8_GFXCLK_LIMITS;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].feature_id =
			OD8_GFXCLK_LIMITS;
	पूर्ण अन्यथा अणु
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMIN].feature_id =
			0;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].feature_id =
			0;
	पूर्ण

	अगर (od_settings->overdrive8_capabilities & OD8_GFXCLK_CURVE) अणु
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ1].feature_id =
			OD8_GFXCLK_CURVE;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE1].feature_id =
			OD8_GFXCLK_CURVE;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ2].feature_id =
			OD8_GFXCLK_CURVE;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE2].feature_id =
			OD8_GFXCLK_CURVE;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ3].feature_id =
			OD8_GFXCLK_CURVE;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE3].feature_id =
			OD8_GFXCLK_CURVE;
	पूर्ण अन्यथा अणु
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ1].feature_id =
			0;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE1].feature_id =
			0;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ2].feature_id =
			0;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE2].feature_id =
			0;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ3].feature_id =
			0;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE3].feature_id =
			0;
	पूर्ण

	अगर (od_settings->overdrive8_capabilities & OD8_UCLK_MAX)
		od_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].feature_id = OD8_UCLK_MAX;
	अन्यथा
		od_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].feature_id = 0;

	अगर (od_settings->overdrive8_capabilities & OD8_POWER_LIMIT)
		od_settings->od8_settings_array[OD8_SETTING_POWER_PERCENTAGE].feature_id = OD8_POWER_LIMIT;
	अन्यथा
		od_settings->od8_settings_array[OD8_SETTING_POWER_PERCENTAGE].feature_id = 0;

	अगर (od_settings->overdrive8_capabilities & OD8_ACOUSTIC_LIMIT_SCLK)
		od_settings->od8_settings_array[OD8_SETTING_FAN_ACOUSTIC_LIMIT].feature_id =
			OD8_ACOUSTIC_LIMIT_SCLK;
	अन्यथा
		od_settings->od8_settings_array[OD8_SETTING_FAN_ACOUSTIC_LIMIT].feature_id =
			0;

	अगर (od_settings->overdrive8_capabilities & OD8_FAN_SPEED_MIN)
		od_settings->od8_settings_array[OD8_SETTING_FAN_MIN_SPEED].feature_id =
			OD8_FAN_SPEED_MIN;
	अन्यथा
		od_settings->od8_settings_array[OD8_SETTING_FAN_MIN_SPEED].feature_id =
			0;

	अगर (od_settings->overdrive8_capabilities & OD8_TEMPERATURE_FAN)
		od_settings->od8_settings_array[OD8_SETTING_FAN_TARGET_TEMP].feature_id =
			OD8_TEMPERATURE_FAN;
	अन्यथा
		od_settings->od8_settings_array[OD8_SETTING_FAN_TARGET_TEMP].feature_id =
			0;

	अगर (od_settings->overdrive8_capabilities & OD8_TEMPERATURE_SYSTEM)
		od_settings->od8_settings_array[OD8_SETTING_OPERATING_TEMP_MAX].feature_id =
			OD8_TEMPERATURE_SYSTEM;
	अन्यथा
		od_settings->od8_settings_array[OD8_SETTING_OPERATING_TEMP_MAX].feature_id =
			0;

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_od8_get_gfx_घड़ी_base_voltage(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t *voltage,
		uपूर्णांक32_t freq)
अणु
	पूर्णांक ret = 0;

	ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_GetAVFSVoltageByDpm,
			((AVFS_CURVE << 24) | (OD8_HOTCURVE_TEMPERATURE << 16) | freq),
			voltage);
	PP_ASSERT_WITH_CODE(!ret,
			"[GetBaseVoltage] failed to get GFXCLK AVFS voltage from SMU!",
			वापस ret);

	*voltage = *voltage / VOLTAGE_SCALE;

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_od8_initialize_शेष_settings(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा phm_ppt_v3_inक्रमmation *pptable_inक्रमmation =
		(काष्ठा phm_ppt_v3_inक्रमmation *)hwmgr->pptable;
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_od8_settings *od8_settings = &(data->od8_settings);
	OverDriveTable_t *od_table = &(data->smc_state_table.overdrive_table);
	पूर्णांक i, ret = 0;

	/* Set Feature Capabilities */
	vega20_od8_set_feature_capabilities(hwmgr);

	/* Map FeatureID to inभागidual settings */
	vega20_od8_set_feature_id(hwmgr);

	/* Set शेष values */
	ret = smum_smc_table_manager(hwmgr, (uपूर्णांक8_t *)od_table, TABLE_OVERDRIVE, true);
	PP_ASSERT_WITH_CODE(!ret,
			"Failed to export over drive table!",
			वापस ret);

	अगर (od8_settings->overdrive8_capabilities & OD8_GFXCLK_LIMITS) अणु
		od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMIN].शेष_value =
			od_table->GfxclkFmin;
		od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].शेष_value =
			od_table->GfxclkFmax;
	पूर्ण अन्यथा अणु
		od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMIN].शेष_value =
			0;
		od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].शेष_value =
			0;
	पूर्ण

	अगर (od8_settings->overdrive8_capabilities & OD8_GFXCLK_CURVE) अणु
		od_table->GfxclkFreq1 = od_table->GfxclkFmin;
		od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ1].शेष_value =
			od_table->GfxclkFreq1;

		od_table->GfxclkFreq3 = od_table->GfxclkFmax;
		od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ3].शेष_value =
			od_table->GfxclkFreq3;

		od_table->GfxclkFreq2 = (od_table->GfxclkFreq1 + od_table->GfxclkFreq3) / 2;
		od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ2].शेष_value =
			od_table->GfxclkFreq2;

		PP_ASSERT_WITH_CODE(!vega20_od8_get_gfx_घड़ी_base_voltage(hwmgr,
				   &(od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE1].शेष_value),
				     od_table->GfxclkFreq1),
				"[PhwVega20_OD8_InitializeDefaultSettings] Failed to get Base clock voltage from SMU!",
				od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE1].शेष_value = 0);
		od_table->GfxclkVolt1 = od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE1].शेष_value
			* VOLTAGE_SCALE;

		PP_ASSERT_WITH_CODE(!vega20_od8_get_gfx_घड़ी_base_voltage(hwmgr,
				   &(od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE2].शेष_value),
				     od_table->GfxclkFreq2),
				"[PhwVega20_OD8_InitializeDefaultSettings] Failed to get Base clock voltage from SMU!",
				od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE2].शेष_value = 0);
		od_table->GfxclkVolt2 = od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE2].शेष_value
			* VOLTAGE_SCALE;

		PP_ASSERT_WITH_CODE(!vega20_od8_get_gfx_घड़ी_base_voltage(hwmgr,
				   &(od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE3].शेष_value),
				     od_table->GfxclkFreq3),
				"[PhwVega20_OD8_InitializeDefaultSettings] Failed to get Base clock voltage from SMU!",
				od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE3].शेष_value = 0);
		od_table->GfxclkVolt3 = od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE3].शेष_value
			* VOLTAGE_SCALE;
	पूर्ण अन्यथा अणु
		od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ1].शेष_value =
			0;
		od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE1].शेष_value =
			0;
		od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ2].शेष_value =
			0;
		od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE2].शेष_value =
			0;
		od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ3].शेष_value =
			0;
		od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE3].शेष_value =
			0;
	पूर्ण

	अगर (od8_settings->overdrive8_capabilities & OD8_UCLK_MAX)
		od8_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].शेष_value =
			od_table->UclkFmax;
	अन्यथा
		od8_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].शेष_value =
			0;

	अगर (od8_settings->overdrive8_capabilities & OD8_POWER_LIMIT)
		od8_settings->od8_settings_array[OD8_SETTING_POWER_PERCENTAGE].शेष_value =
			od_table->OverDrivePct;
	अन्यथा
		od8_settings->od8_settings_array[OD8_SETTING_POWER_PERCENTAGE].शेष_value =
			0;

	अगर (od8_settings->overdrive8_capabilities & OD8_ACOUSTIC_LIMIT_SCLK)
		od8_settings->od8_settings_array[OD8_SETTING_FAN_ACOUSTIC_LIMIT].शेष_value =
			od_table->FanMaximumRpm;
	अन्यथा
		od8_settings->od8_settings_array[OD8_SETTING_FAN_ACOUSTIC_LIMIT].शेष_value =
			0;

	अगर (od8_settings->overdrive8_capabilities & OD8_FAN_SPEED_MIN)
		od8_settings->od8_settings_array[OD8_SETTING_FAN_MIN_SPEED].शेष_value =
			od_table->FanMinimumPwm * data->smc_state_table.pp_table.FanMaximumRpm / 100;
	अन्यथा
		od8_settings->od8_settings_array[OD8_SETTING_FAN_MIN_SPEED].शेष_value =
			0;

	अगर (od8_settings->overdrive8_capabilities & OD8_TEMPERATURE_FAN)
		od8_settings->od8_settings_array[OD8_SETTING_FAN_TARGET_TEMP].शेष_value =
			od_table->FanTargetTemperature;
	अन्यथा
		od8_settings->od8_settings_array[OD8_SETTING_FAN_TARGET_TEMP].शेष_value =
			0;

	अगर (od8_settings->overdrive8_capabilities & OD8_TEMPERATURE_SYSTEM)
		od8_settings->od8_settings_array[OD8_SETTING_OPERATING_TEMP_MAX].शेष_value =
			od_table->MaxOpTemp;
	अन्यथा
		od8_settings->od8_settings_array[OD8_SETTING_OPERATING_TEMP_MAX].शेष_value =
			0;

	क्रम (i = 0; i < OD8_SETTING_COUNT; i++) अणु
		अगर (od8_settings->od8_settings_array[i].feature_id) अणु
			od8_settings->od8_settings_array[i].min_value =
				pptable_inक्रमmation->od_settings_min[i];
			od8_settings->od8_settings_array[i].max_value =
				pptable_inक्रमmation->od_settings_max[i];
			od8_settings->od8_settings_array[i].current_value =
				od8_settings->od8_settings_array[i].शेष_value;
		पूर्ण अन्यथा अणु
			od8_settings->od8_settings_array[i].min_value =
				0;
			od8_settings->od8_settings_array[i].max_value =
				0;
			od8_settings->od8_settings_array[i].current_value =
				0;
		पूर्ण
	पूर्ण

	ret = smum_smc_table_manager(hwmgr, (uपूर्णांक8_t *)od_table, TABLE_OVERDRIVE, false);
	PP_ASSERT_WITH_CODE(!ret,
			"Failed to import over drive table!",
			वापस ret);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_od8_set_settings(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t index,
		uपूर्णांक32_t value)
अणु
	OverDriveTable_t od_table;
	पूर्णांक ret = 0;
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_od8_single_setting *od8_settings =
			data->od8_settings.od8_settings_array;

	ret = smum_smc_table_manager(hwmgr, (uपूर्णांक8_t *)(&od_table), TABLE_OVERDRIVE, true);
	PP_ASSERT_WITH_CODE(!ret,
			"Failed to export over drive table!",
			वापस ret);

	चयन(index) अणु
	हाल OD8_SETTING_GFXCLK_FMIN:
		od_table.GfxclkFmin = (uपूर्णांक16_t)value;
		अवरोध;
	हाल OD8_SETTING_GFXCLK_FMAX:
		अगर (value < od8_settings[OD8_SETTING_GFXCLK_FMAX].min_value ||
		    value > od8_settings[OD8_SETTING_GFXCLK_FMAX].max_value)
			वापस -EINVAL;

		od_table.GfxclkFmax = (uपूर्णांक16_t)value;
		अवरोध;
	हाल OD8_SETTING_GFXCLK_FREQ1:
		od_table.GfxclkFreq1 = (uपूर्णांक16_t)value;
		अवरोध;
	हाल OD8_SETTING_GFXCLK_VOLTAGE1:
		od_table.GfxclkVolt1 = (uपूर्णांक16_t)value;
		अवरोध;
	हाल OD8_SETTING_GFXCLK_FREQ2:
		od_table.GfxclkFreq2 = (uपूर्णांक16_t)value;
		अवरोध;
	हाल OD8_SETTING_GFXCLK_VOLTAGE2:
		od_table.GfxclkVolt2 = (uपूर्णांक16_t)value;
		अवरोध;
	हाल OD8_SETTING_GFXCLK_FREQ3:
		od_table.GfxclkFreq3 = (uपूर्णांक16_t)value;
		अवरोध;
	हाल OD8_SETTING_GFXCLK_VOLTAGE3:
		od_table.GfxclkVolt3 = (uपूर्णांक16_t)value;
		अवरोध;
	हाल OD8_SETTING_UCLK_FMAX:
		अगर (value < od8_settings[OD8_SETTING_UCLK_FMAX].min_value ||
		    value > od8_settings[OD8_SETTING_UCLK_FMAX].max_value)
			वापस -EINVAL;
		od_table.UclkFmax = (uपूर्णांक16_t)value;
		अवरोध;
	हाल OD8_SETTING_POWER_PERCENTAGE:
		od_table.OverDrivePct = (पूर्णांक16_t)value;
		अवरोध;
	हाल OD8_SETTING_FAN_ACOUSTIC_LIMIT:
		od_table.FanMaximumRpm = (uपूर्णांक16_t)value;
		अवरोध;
	हाल OD8_SETTING_FAN_MIN_SPEED:
		od_table.FanMinimumPwm = (uपूर्णांक16_t)value;
		अवरोध;
	हाल OD8_SETTING_FAN_TARGET_TEMP:
		od_table.FanTargetTemperature = (uपूर्णांक16_t)value;
		अवरोध;
	हाल OD8_SETTING_OPERATING_TEMP_MAX:
		od_table.MaxOpTemp = (uपूर्णांक16_t)value;
		अवरोध;
	पूर्ण

	ret = smum_smc_table_manager(hwmgr, (uपूर्णांक8_t *)(&od_table), TABLE_OVERDRIVE, false);
	PP_ASSERT_WITH_CODE(!ret,
			"Failed to import over drive table!",
			वापस ret);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_get_sclk_od(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = hwmgr->backend;
	काष्ठा vega20_single_dpm_table *sclk_table =
			&(data->dpm_table.gfx_table);
	काष्ठा vega20_single_dpm_table *golden_sclk_table =
			&(data->golden_dpm_table.gfx_table);
	पूर्णांक value = sclk_table->dpm_levels[sclk_table->count - 1].value;
	पूर्णांक golden_value = golden_sclk_table->dpm_levels
			[golden_sclk_table->count - 1].value;

	/* od percentage */
	value -= golden_value;
	value = DIV_ROUND_UP(value * 100, golden_value);

	वापस value;
पूर्ण

अटल पूर्णांक vega20_set_sclk_od(
		काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t value)
अणु
	काष्ठा vega20_hwmgr *data = hwmgr->backend;
	काष्ठा vega20_single_dpm_table *golden_sclk_table =
			&(data->golden_dpm_table.gfx_table);
	uपूर्णांक32_t od_sclk;
	पूर्णांक ret = 0;

	od_sclk = golden_sclk_table->dpm_levels[golden_sclk_table->count - 1].value * value;
	od_sclk /= 100;
	od_sclk += golden_sclk_table->dpm_levels[golden_sclk_table->count - 1].value;

	ret = vega20_od8_set_settings(hwmgr, OD8_SETTING_GFXCLK_FMAX, od_sclk);
	PP_ASSERT_WITH_CODE(!ret,
			"[SetSclkOD] failed to set od gfxclk!",
			वापस ret);

	/* retrieve updated gfxclk table */
	ret = vega20_setup_gfxclk_dpm_table(hwmgr);
	PP_ASSERT_WITH_CODE(!ret,
			"[SetSclkOD] failed to refresh gfxclk table!",
			वापस ret);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_get_mclk_od(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = hwmgr->backend;
	काष्ठा vega20_single_dpm_table *mclk_table =
			&(data->dpm_table.mem_table);
	काष्ठा vega20_single_dpm_table *golden_mclk_table =
			&(data->golden_dpm_table.mem_table);
	पूर्णांक value = mclk_table->dpm_levels[mclk_table->count - 1].value;
	पूर्णांक golden_value = golden_mclk_table->dpm_levels
			[golden_mclk_table->count - 1].value;

	/* od percentage */
	value -= golden_value;
	value = DIV_ROUND_UP(value * 100, golden_value);

	वापस value;
पूर्ण

अटल पूर्णांक vega20_set_mclk_od(
		काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t value)
अणु
	काष्ठा vega20_hwmgr *data = hwmgr->backend;
	काष्ठा vega20_single_dpm_table *golden_mclk_table =
			&(data->golden_dpm_table.mem_table);
	uपूर्णांक32_t od_mclk;
	पूर्णांक ret = 0;

	od_mclk = golden_mclk_table->dpm_levels[golden_mclk_table->count - 1].value * value;
	od_mclk /= 100;
	od_mclk += golden_mclk_table->dpm_levels[golden_mclk_table->count - 1].value;

	ret = vega20_od8_set_settings(hwmgr, OD8_SETTING_UCLK_FMAX, od_mclk);
	PP_ASSERT_WITH_CODE(!ret,
			"[SetMclkOD] failed to set od memclk!",
			वापस ret);

	/* retrieve updated memclk table */
	ret = vega20_setup_memclk_dpm_table(hwmgr);
	PP_ASSERT_WITH_CODE(!ret,
			"[SetMclkOD] failed to refresh memclk table!",
			वापस ret);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_populate_umdpstate_घड़ीs(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_single_dpm_table *gfx_table = &(data->dpm_table.gfx_table);
	काष्ठा vega20_single_dpm_table *mem_table = &(data->dpm_table.mem_table);

	hwmgr->pstate_sclk = gfx_table->dpm_levels[0].value;
	hwmgr->pstate_mclk = mem_table->dpm_levels[0].value;

	अगर (gfx_table->count > VEGA20_UMD_PSTATE_GFXCLK_LEVEL &&
	    mem_table->count > VEGA20_UMD_PSTATE_MCLK_LEVEL) अणु
		hwmgr->pstate_sclk = gfx_table->dpm_levels[VEGA20_UMD_PSTATE_GFXCLK_LEVEL].value;
		hwmgr->pstate_mclk = mem_table->dpm_levels[VEGA20_UMD_PSTATE_MCLK_LEVEL].value;
	पूर्ण

	hwmgr->pstate_sclk = hwmgr->pstate_sclk * 100;
	hwmgr->pstate_mclk = hwmgr->pstate_mclk * 100;

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_get_max_sustainable_घड़ी(काष्ठा pp_hwmgr *hwmgr,
		PP_Clock *घड़ी, PPCLK_e घड़ी_select)
अणु
	पूर्णांक ret = 0;

	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_GetDcModeMaxDpmFreq,
			(घड़ी_select << 16),
			घड़ी)) == 0,
			"[GetMaxSustainableClock] Failed to get max DC clock from SMC!",
			वापस ret);

	/* अगर DC limit is zero, वापस AC limit */
	अगर (*घड़ी == 0) अणु
		PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_GetMaxDpmFreq,
			(घड़ी_select << 16),
			घड़ी)) == 0,
			"[GetMaxSustainableClock] failed to get max AC clock from SMC!",
			वापस ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_init_max_sustainable_घड़ीs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
		(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_max_sustainable_घड़ीs *max_sustainable_घड़ीs =
		&(data->max_sustainable_घड़ीs);
	पूर्णांक ret = 0;

	max_sustainable_घड़ीs->uघड़ी = data->vbios_boot_state.mem_घड़ी / 100;
	max_sustainable_घड़ीs->soc_घड़ी = data->vbios_boot_state.soc_घड़ी / 100;
	max_sustainable_घड़ीs->dcef_घड़ी = data->vbios_boot_state.dcef_घड़ी / 100;
	max_sustainable_घड़ीs->display_घड़ी = 0xFFFFFFFF;
	max_sustainable_घड़ीs->phy_घड़ी = 0xFFFFFFFF;
	max_sustainable_घड़ीs->pixel_घड़ी = 0xFFFFFFFF;

	अगर (data->smu_features[GNLD_DPM_UCLK].enabled)
		PP_ASSERT_WITH_CODE((ret = vega20_get_max_sustainable_घड़ी(hwmgr,
				&(max_sustainable_घड़ीs->uघड़ी),
				PPCLK_UCLK)) == 0,
				"[InitMaxSustainableClocks] failed to get max UCLK from SMC!",
				वापस ret);

	अगर (data->smu_features[GNLD_DPM_SOCCLK].enabled)
		PP_ASSERT_WITH_CODE((ret = vega20_get_max_sustainable_घड़ी(hwmgr,
				&(max_sustainable_घड़ीs->soc_घड़ी),
				PPCLK_SOCCLK)) == 0,
				"[InitMaxSustainableClocks] failed to get max SOCCLK from SMC!",
				वापस ret);

	अगर (data->smu_features[GNLD_DPM_DCEFCLK].enabled) अणु
		PP_ASSERT_WITH_CODE((ret = vega20_get_max_sustainable_घड़ी(hwmgr,
				&(max_sustainable_घड़ीs->dcef_घड़ी),
				PPCLK_DCEFCLK)) == 0,
				"[InitMaxSustainableClocks] failed to get max DCEFCLK from SMC!",
				वापस ret);
		PP_ASSERT_WITH_CODE((ret = vega20_get_max_sustainable_घड़ी(hwmgr,
				&(max_sustainable_घड़ीs->display_घड़ी),
				PPCLK_DISPCLK)) == 0,
				"[InitMaxSustainableClocks] failed to get max DISPCLK from SMC!",
				वापस ret);
		PP_ASSERT_WITH_CODE((ret = vega20_get_max_sustainable_घड़ी(hwmgr,
				&(max_sustainable_घड़ीs->phy_घड़ी),
				PPCLK_PHYCLK)) == 0,
				"[InitMaxSustainableClocks] failed to get max PHYCLK from SMC!",
				वापस ret);
		PP_ASSERT_WITH_CODE((ret = vega20_get_max_sustainable_घड़ी(hwmgr,
				&(max_sustainable_घड़ीs->pixel_घड़ी),
				PPCLK_PIXCLK)) == 0,
				"[InitMaxSustainableClocks] failed to get max PIXCLK from SMC!",
				वापस ret);
	पूर्ण

	अगर (max_sustainable_घड़ीs->soc_घड़ी < max_sustainable_घड़ीs->uघड़ी)
		max_sustainable_घड़ीs->uघड़ी = max_sustainable_घड़ीs->soc_घड़ी;

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_enable_mgpu_fan_boost(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;

	result = smum_send_msg_to_smc(hwmgr,
		PPSMC_MSG_SetMGpuFanBoostLimitRpm,
		शून्य);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableMgpuFan] Failed to enable mgpu fan boost!",
			वापस result);

	वापस 0;
पूर्ण

अटल व्योम vega20_init_घातergate_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
		(काष्ठा vega20_hwmgr *)(hwmgr->backend);

	data->uvd_घातer_gated = true;
	data->vce_घातer_gated = true;
पूर्ण

अटल पूर्णांक vega20_enable_dpm_tasks(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;

	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_NumOfDisplays, 0, शून्य);

	result = vega20_set_allowed_featuresmask(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to set allowed featuresmask!\n",
			वापस result);

	result = vega20_init_smc_table(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to initialize SMC table!",
			वापस result);

	result = vega20_run_btc(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to run btc!",
			वापस result);

	result = vega20_run_btc_afll(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to run btc afll!",
			वापस result);

	result = vega20_enable_all_smu_features(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to enable all smu features!",
			वापस result);

	result = vega20_override_pcie_parameters(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to override pcie parameters!",
			वापस result);

	result = vega20_notअगरy_smc_display_change(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to notify smc display change!",
			वापस result);

	result = vega20_send_घड़ी_ratio(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to send clock ratio!",
			वापस result);

	/* Initialize UVD/VCE घातergating state */
	vega20_init_घातergate_state(hwmgr);

	result = vega20_setup_शेष_dpm_tables(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to setup default DPM tables!",
			वापस result);

	result = vega20_init_max_sustainable_घड़ीs(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to get maximum sustainable clocks!",
			वापस result);

	result = vega20_घातer_control_set_level(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to power control set level!",
			वापस result);

	result = vega20_od8_initialize_शेष_settings(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to initialize odn settings!",
			वापस result);

	result = vega20_populate_umdpstate_घड़ीs(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"[EnableDPMTasks] Failed to populate umdpstate clocks!",
			वापस result);

	result = smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_GetPptLimit,
			POWER_SOURCE_AC << 16, &hwmgr->शेष_घातer_limit);
	PP_ASSERT_WITH_CODE(!result,
			"[GetPptLimit] get default PPT limit failed!",
			वापस result);
	hwmgr->घातer_limit =
		hwmgr->शेष_घातer_limit;

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t vega20_find_lowest_dpm_level(
		काष्ठा vega20_single_dpm_table *table)
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

अटल uपूर्णांक32_t vega20_find_highest_dpm_level(
		काष्ठा vega20_single_dpm_table *table)
अणु
	पूर्णांक i = 0;

	PP_ASSERT_WITH_CODE(table != शून्य,
			"[FindHighestDPMLevel] DPM Table does not exist!",
			वापस 0);
	PP_ASSERT_WITH_CODE(table->count > 0,
			"[FindHighestDPMLevel] DPM Table has no entry!",
			वापस 0);
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

	वापस i;
पूर्ण

अटल पूर्णांक vega20_upload_dpm_min_level(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t feature_mask)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t min_freq;
	पूर्णांक ret = 0;

	अगर (data->smu_features[GNLD_DPM_GFXCLK].enabled &&
	   (feature_mask & FEATURE_DPM_GFXCLK_MASK)) अणु
		min_freq = data->dpm_table.gfx_table.dpm_state.soft_min_level;
		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMinByFreq,
					(PPCLK_GFXCLK << 16) | (min_freq & 0xffff),
					शून्य)),
					"Failed to set soft min gfxclk !",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_UCLK].enabled &&
	   (feature_mask & FEATURE_DPM_UCLK_MASK)) अणु
		min_freq = data->dpm_table.mem_table.dpm_state.soft_min_level;
		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMinByFreq,
					(PPCLK_UCLK << 16) | (min_freq & 0xffff),
					शून्य)),
					"Failed to set soft min memclk !",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_UVD].enabled &&
	   (feature_mask & FEATURE_DPM_UVD_MASK)) अणु
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

	अगर (data->smu_features[GNLD_DPM_VCE].enabled &&
	   (feature_mask & FEATURE_DPM_VCE_MASK)) अणु
		min_freq = data->dpm_table.eclk_table.dpm_state.soft_min_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMinByFreq,
					(PPCLK_ECLK << 16) | (min_freq & 0xffff),
					शून्य)),
					"Failed to set soft min eclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_SOCCLK].enabled &&
	   (feature_mask & FEATURE_DPM_SOCCLK_MASK)) अणु
		min_freq = data->dpm_table.soc_table.dpm_state.soft_min_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMinByFreq,
					(PPCLK_SOCCLK << 16) | (min_freq & 0xffff),
					शून्य)),
					"Failed to set soft min socclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_FCLK].enabled &&
	   (feature_mask & FEATURE_DPM_FCLK_MASK)) अणु
		min_freq = data->dpm_table.fclk_table.dpm_state.soft_min_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMinByFreq,
					(PPCLK_FCLK << 16) | (min_freq & 0xffff),
					शून्य)),
					"Failed to set soft min fclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_DCEFCLK].enabled &&
	   (feature_mask & FEATURE_DPM_DCEFCLK_MASK)) अणु
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

अटल पूर्णांक vega20_upload_dpm_max_level(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t feature_mask)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t max_freq;
	पूर्णांक ret = 0;

	अगर (data->smu_features[GNLD_DPM_GFXCLK].enabled &&
	   (feature_mask & FEATURE_DPM_GFXCLK_MASK)) अणु
		max_freq = data->dpm_table.gfx_table.dpm_state.soft_max_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMaxByFreq,
					(PPCLK_GFXCLK << 16) | (max_freq & 0xffff),
					शून्य)),
					"Failed to set soft max gfxclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_UCLK].enabled &&
	   (feature_mask & FEATURE_DPM_UCLK_MASK)) अणु
		max_freq = data->dpm_table.mem_table.dpm_state.soft_max_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMaxByFreq,
					(PPCLK_UCLK << 16) | (max_freq & 0xffff),
					शून्य)),
					"Failed to set soft max memclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_UVD].enabled &&
	   (feature_mask & FEATURE_DPM_UVD_MASK)) अणु
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

	अगर (data->smu_features[GNLD_DPM_VCE].enabled &&
	   (feature_mask & FEATURE_DPM_VCE_MASK)) अणु
		max_freq = data->dpm_table.eclk_table.dpm_state.soft_max_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMaxByFreq,
					(PPCLK_ECLK << 16) | (max_freq & 0xffff),
					शून्य)),
					"Failed to set soft max eclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_SOCCLK].enabled &&
	   (feature_mask & FEATURE_DPM_SOCCLK_MASK)) अणु
		max_freq = data->dpm_table.soc_table.dpm_state.soft_max_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMaxByFreq,
					(PPCLK_SOCCLK << 16) | (max_freq & 0xffff),
					शून्य)),
					"Failed to set soft max socclk!",
					वापस ret);
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_FCLK].enabled &&
	   (feature_mask & FEATURE_DPM_FCLK_MASK)) अणु
		max_freq = data->dpm_table.fclk_table.dpm_state.soft_max_level;

		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetSoftMaxByFreq,
					(PPCLK_FCLK << 16) | (max_freq & 0xffff),
					शून्य)),
					"Failed to set soft max fclk!",
					वापस ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vega20_enable_disable_vce_dpm(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	पूर्णांक ret = 0;

	अगर (data->smu_features[GNLD_DPM_VCE].supported) अणु
		अगर (data->smu_features[GNLD_DPM_VCE].enabled == enable) अणु
			अगर (enable)
				PP_DBG_LOG("[EnableDisableVCEDPM] feature VCE DPM already enabled!\n");
			अन्यथा
				PP_DBG_LOG("[EnableDisableVCEDPM] feature VCE DPM already disabled!\n");
		पूर्ण

		ret = vega20_enable_smc_features(hwmgr,
				enable,
				data->smu_features[GNLD_DPM_VCE].smu_feature_biपंचांगap);
		PP_ASSERT_WITH_CODE(!ret,
				"Attempt to Enable/Disable DPM VCE Failed!",
				वापस ret);
		data->smu_features[GNLD_DPM_VCE].enabled = enable;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_get_घड़ी_ranges(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t *घड़ी,
		PPCLK_e घड़ी_select,
		bool max)
अणु
	पूर्णांक ret;
	*घड़ी = 0;

	अगर (max) अणु
		PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_GetMaxDpmFreq, (घड़ी_select << 16),
				घड़ी)) == 0,
				"[GetClockRanges] Failed to get max clock from SMC!",
				वापस ret);
	पूर्ण अन्यथा अणु
		PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_GetMinDpmFreq,
				(घड़ी_select << 16),
				घड़ी)) == 0,
				"[GetClockRanges] Failed to get min clock from SMC!",
				वापस ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t vega20_dpm_get_sclk(काष्ठा pp_hwmgr *hwmgr, bool low)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t gfx_clk;
	पूर्णांक ret = 0;

	PP_ASSERT_WITH_CODE(data->smu_features[GNLD_DPM_GFXCLK].enabled,
			"[GetSclks]: gfxclk dpm not enabled!\n",
			वापस -EPERM);

	अगर (low) अणु
		ret = vega20_get_घड़ी_ranges(hwmgr, &gfx_clk, PPCLK_GFXCLK, false);
		PP_ASSERT_WITH_CODE(!ret,
			"[GetSclks]: fail to get min PPCLK_GFXCLK\n",
			वापस ret);
	पूर्ण अन्यथा अणु
		ret = vega20_get_घड़ी_ranges(hwmgr, &gfx_clk, PPCLK_GFXCLK, true);
		PP_ASSERT_WITH_CODE(!ret,
			"[GetSclks]: fail to get max PPCLK_GFXCLK\n",
			वापस ret);
	पूर्ण

	वापस (gfx_clk * 100);
पूर्ण

अटल uपूर्णांक32_t vega20_dpm_get_mclk(काष्ठा pp_hwmgr *hwmgr, bool low)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t mem_clk;
	पूर्णांक ret = 0;

	PP_ASSERT_WITH_CODE(data->smu_features[GNLD_DPM_UCLK].enabled,
			"[MemMclks]: memclk dpm not enabled!\n",
			वापस -EPERM);

	अगर (low) अणु
		ret = vega20_get_घड़ी_ranges(hwmgr, &mem_clk, PPCLK_UCLK, false);
		PP_ASSERT_WITH_CODE(!ret,
			"[GetMclks]: fail to get min PPCLK_UCLK\n",
			वापस ret);
	पूर्ण अन्यथा अणु
		ret = vega20_get_घड़ी_ranges(hwmgr, &mem_clk, PPCLK_UCLK, true);
		PP_ASSERT_WITH_CODE(!ret,
			"[GetMclks]: fail to get max PPCLK_UCLK\n",
			वापस ret);
	पूर्ण

	वापस (mem_clk * 100);
पूर्ण

अटल पूर्णांक vega20_get_metrics_table(काष्ठा pp_hwmgr *hwmgr,
				    SmuMetrics_t *metrics_table,
				    bool bypass_cache)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
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

अटल पूर्णांक vega20_get_gpu_घातer(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t *query)
अणु
	पूर्णांक ret = 0;
	SmuMetrics_t metrics_table;

	ret = vega20_get_metrics_table(hwmgr, &metrics_table, false);
	अगर (ret)
		वापस ret;

	/* For the 40.46 release, they changed the value name */
	अगर (hwmgr->smu_version == 0x282e00)
		*query = metrics_table.AverageSocketPower << 8;
	अन्यथा
		*query = metrics_table.CurrSocketPower << 8;

	वापस ret;
पूर्ण

अटल पूर्णांक vega20_get_current_clk_freq(काष्ठा pp_hwmgr *hwmgr,
		PPCLK_e clk_id, uपूर्णांक32_t *clk_freq)
अणु
	पूर्णांक ret = 0;

	*clk_freq = 0;

	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_GetDpmClockFreq, (clk_id << 16),
			clk_freq)) == 0,
			"[GetCurrentClkFreq] Attempt to get Current Frequency Failed!",
			वापस ret);

	*clk_freq = *clk_freq * 100;

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_get_current_activity_percent(काष्ठा pp_hwmgr *hwmgr,
		पूर्णांक idx,
		uपूर्णांक32_t *activity_percent)
अणु
	पूर्णांक ret = 0;
	SmuMetrics_t metrics_table;

	ret = vega20_get_metrics_table(hwmgr, &metrics_table, false);
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

अटल पूर्णांक vega20_पढ़ो_sensor(काष्ठा pp_hwmgr *hwmgr, पूर्णांक idx,
			      व्योम *value, पूर्णांक *size)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	SmuMetrics_t metrics_table;
	uपूर्णांक32_t val_vid;
	पूर्णांक ret = 0;

	चयन (idx) अणु
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		ret = vega20_get_metrics_table(hwmgr, &metrics_table, false);
		अगर (ret)
			वापस ret;

		*((uपूर्णांक32_t *)value) = metrics_table.AverageGfxclkFrequency * 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_MCLK:
		ret = vega20_get_current_clk_freq(hwmgr,
				PPCLK_UCLK,
				(uपूर्णांक32_t *)value);
		अगर (!ret)
			*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
	हाल AMDGPU_PP_SENSOR_MEM_LOAD:
		ret = vega20_get_current_activity_percent(hwmgr, idx, (uपूर्णांक32_t *)value);
		अगर (!ret)
			*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_HOTSPOT_TEMP:
		*((uपूर्णांक32_t *)value) = vega20_thermal_get_temperature(hwmgr);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_EDGE_TEMP:
		ret = vega20_get_metrics_table(hwmgr, &metrics_table, false);
		अगर (ret)
			वापस ret;

		*((uपूर्णांक32_t *)value) = metrics_table.TemperatureEdge *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_MEM_TEMP:
		ret = vega20_get_metrics_table(hwmgr, &metrics_table, false);
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
		*size = 16;
		ret = vega20_get_gpu_घातer(hwmgr, (uपूर्णांक32_t *)value);
		अवरोध;
	हाल AMDGPU_PP_SENSOR_VDDGFX:
		val_vid = (RREG32_SOC15(SMUIO, 0, mmSMUSVI0_TEL_PLANE0) &
			SMUSVI0_TEL_PLANE0__SVI0_PLANE0_VDDCOR_MASK) >>
			SMUSVI0_TEL_PLANE0__SVI0_PLANE0_VDDCOR__SHIFT;
		*((uपूर्णांक32_t *)value) =
			(uपूर्णांक32_t)convert_to_vddc((uपूर्णांक8_t)val_vid);
		अवरोध;
	हाल AMDGPU_PP_SENSOR_ENABLED_SMC_FEATURES_MASK:
		ret = vega20_get_enabled_smc_features(hwmgr, (uपूर्णांक64_t *)value);
		अगर (!ret)
			*size = 8;
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक vega20_display_घड़ी_voltage_request(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_display_घड़ी_request *घड़ी_req)
अणु
	पूर्णांक result = 0;
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
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
			result = -EINVAL;
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

अटल पूर्णांक vega20_get_perक्रमmance_level(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा pp_hw_घातer_state *state,
				PHM_Perक्रमmanceLevelDesignation designation, uपूर्णांक32_t index,
				PHM_Perक्रमmanceLevel *level)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vega20_notअगरy_smc_display_config_after_ps_adjusपंचांगent(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_single_dpm_table *dpm_table =
			&data->dpm_table.mem_table;
	काष्ठा PP_Clocks min_घड़ीs = अणु0पूर्ण;
	काष्ठा pp_display_घड़ी_request घड़ी_req;
	पूर्णांक ret = 0;

	min_घड़ीs.dcefClock = hwmgr->display_config->min_dcef_set_clk;
	min_घड़ीs.dcefClockInSR = hwmgr->display_config->min_dcef_deep_sleep_set_clk;
	min_घड़ीs.memoryClock = hwmgr->display_config->min_mem_set_घड़ी;

	अगर (data->smu_features[GNLD_DPM_DCEFCLK].supported) अणु
		घड़ी_req.घड़ी_प्रकारype = amd_pp_dcef_घड़ी;
		घड़ी_req.घड़ी_freq_in_khz = min_घड़ीs.dcefClock * 10;
		अगर (!vega20_display_घड़ी_voltage_request(hwmgr, &घड़ी_req)) अणु
			अगर (data->smu_features[GNLD_DS_DCEFCLK].supported)
				PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetMinDeepSleepDcefclk,
					min_घड़ीs.dcefClockInSR / 100,
					शून्य)) == 0,
					"Attempt to set divider for DCEFCLK Failed!",
					वापस ret);
		पूर्ण अन्यथा अणु
			pr_info("Attempt to set Hard Min for DCEFCLK Failed!");
		पूर्ण
	पूर्ण

	अगर (data->smu_features[GNLD_DPM_UCLK].enabled) अणु
		dpm_table->dpm_state.hard_min_level = min_घड़ीs.memoryClock / 100;
		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetHardMinByFreq,
				(PPCLK_UCLK << 16 ) | dpm_table->dpm_state.hard_min_level,
				शून्य)),
				"[SetHardMinFreq] Set hard min uclk failed!",
				वापस ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_क्रमce_dpm_highest(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t soft_level;
	पूर्णांक ret = 0;

	soft_level = vega20_find_highest_dpm_level(&(data->dpm_table.gfx_table));

	data->dpm_table.gfx_table.dpm_state.soft_min_level =
		data->dpm_table.gfx_table.dpm_state.soft_max_level =
		data->dpm_table.gfx_table.dpm_levels[soft_level].value;

	soft_level = vega20_find_highest_dpm_level(&(data->dpm_table.mem_table));

	data->dpm_table.mem_table.dpm_state.soft_min_level =
		data->dpm_table.mem_table.dpm_state.soft_max_level =
		data->dpm_table.mem_table.dpm_levels[soft_level].value;

	soft_level = vega20_find_highest_dpm_level(&(data->dpm_table.soc_table));

	data->dpm_table.soc_table.dpm_state.soft_min_level =
		data->dpm_table.soc_table.dpm_state.soft_max_level =
		data->dpm_table.soc_table.dpm_levels[soft_level].value;

	ret = vega20_upload_dpm_min_level(hwmgr, FEATURE_DPM_GFXCLK_MASK |
						 FEATURE_DPM_UCLK_MASK |
						 FEATURE_DPM_SOCCLK_MASK);
	PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload boot level to highest!",
			वापस ret);

	ret = vega20_upload_dpm_max_level(hwmgr, FEATURE_DPM_GFXCLK_MASK |
						 FEATURE_DPM_UCLK_MASK |
						 FEATURE_DPM_SOCCLK_MASK);
	PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload dpm max level to highest!",
			वापस ret);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_क्रमce_dpm_lowest(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t soft_level;
	पूर्णांक ret = 0;

	soft_level = vega20_find_lowest_dpm_level(&(data->dpm_table.gfx_table));

	data->dpm_table.gfx_table.dpm_state.soft_min_level =
		data->dpm_table.gfx_table.dpm_state.soft_max_level =
		data->dpm_table.gfx_table.dpm_levels[soft_level].value;

	soft_level = vega20_find_lowest_dpm_level(&(data->dpm_table.mem_table));

	data->dpm_table.mem_table.dpm_state.soft_min_level =
		data->dpm_table.mem_table.dpm_state.soft_max_level =
		data->dpm_table.mem_table.dpm_levels[soft_level].value;

	soft_level = vega20_find_lowest_dpm_level(&(data->dpm_table.soc_table));

	data->dpm_table.soc_table.dpm_state.soft_min_level =
		data->dpm_table.soc_table.dpm_state.soft_max_level =
		data->dpm_table.soc_table.dpm_levels[soft_level].value;

	ret = vega20_upload_dpm_min_level(hwmgr, FEATURE_DPM_GFXCLK_MASK |
						 FEATURE_DPM_UCLK_MASK |
						 FEATURE_DPM_SOCCLK_MASK);
	PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload boot level to highest!",
			वापस ret);

	ret = vega20_upload_dpm_max_level(hwmgr, FEATURE_DPM_GFXCLK_MASK |
						 FEATURE_DPM_UCLK_MASK |
						 FEATURE_DPM_SOCCLK_MASK);
	PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload dpm max level to highest!",
			वापस ret);

	वापस 0;

पूर्ण

अटल पूर्णांक vega20_unक्रमce_dpm_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t soft_min_level, soft_max_level;
	पूर्णांक ret = 0;

	/* gfxclk soft min/max settings */
	soft_min_level =
		vega20_find_lowest_dpm_level(&(data->dpm_table.gfx_table));
	soft_max_level =
		vega20_find_highest_dpm_level(&(data->dpm_table.gfx_table));

	data->dpm_table.gfx_table.dpm_state.soft_min_level =
		data->dpm_table.gfx_table.dpm_levels[soft_min_level].value;
	data->dpm_table.gfx_table.dpm_state.soft_max_level =
		data->dpm_table.gfx_table.dpm_levels[soft_max_level].value;

	/* uclk soft min/max settings */
	soft_min_level =
		vega20_find_lowest_dpm_level(&(data->dpm_table.mem_table));
	soft_max_level =
		vega20_find_highest_dpm_level(&(data->dpm_table.mem_table));

	data->dpm_table.mem_table.dpm_state.soft_min_level =
		data->dpm_table.mem_table.dpm_levels[soft_min_level].value;
	data->dpm_table.mem_table.dpm_state.soft_max_level =
		data->dpm_table.mem_table.dpm_levels[soft_max_level].value;

	/* socclk soft min/max settings */
	soft_min_level =
		vega20_find_lowest_dpm_level(&(data->dpm_table.soc_table));
	soft_max_level =
		vega20_find_highest_dpm_level(&(data->dpm_table.soc_table));

	data->dpm_table.soc_table.dpm_state.soft_min_level =
		data->dpm_table.soc_table.dpm_levels[soft_min_level].value;
	data->dpm_table.soc_table.dpm_state.soft_max_level =
		data->dpm_table.soc_table.dpm_levels[soft_max_level].value;

	ret = vega20_upload_dpm_min_level(hwmgr, FEATURE_DPM_GFXCLK_MASK |
						 FEATURE_DPM_UCLK_MASK |
						 FEATURE_DPM_SOCCLK_MASK);
	PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload DPM Bootup Levels!",
			वापस ret);

	ret = vega20_upload_dpm_max_level(hwmgr, FEATURE_DPM_GFXCLK_MASK |
						 FEATURE_DPM_UCLK_MASK |
						 FEATURE_DPM_SOCCLK_MASK);
	PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload DPM Max Levels!",
			वापस ret);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_get_profiling_clk_mask(काष्ठा pp_hwmgr *hwmgr, क्रमागत amd_dpm_क्रमced_level level,
				uपूर्णांक32_t *sclk_mask, uपूर्णांक32_t *mclk_mask, uपूर्णांक32_t *soc_mask)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_single_dpm_table *gfx_dpm_table = &(data->dpm_table.gfx_table);
	काष्ठा vega20_single_dpm_table *mem_dpm_table = &(data->dpm_table.mem_table);
	काष्ठा vega20_single_dpm_table *soc_dpm_table = &(data->dpm_table.soc_table);

	*sclk_mask = 0;
	*mclk_mask = 0;
	*soc_mask  = 0;

	अगर (gfx_dpm_table->count > VEGA20_UMD_PSTATE_GFXCLK_LEVEL &&
	    mem_dpm_table->count > VEGA20_UMD_PSTATE_MCLK_LEVEL &&
	    soc_dpm_table->count > VEGA20_UMD_PSTATE_SOCCLK_LEVEL) अणु
		*sclk_mask = VEGA20_UMD_PSTATE_GFXCLK_LEVEL;
		*mclk_mask = VEGA20_UMD_PSTATE_MCLK_LEVEL;
		*soc_mask  = VEGA20_UMD_PSTATE_SOCCLK_LEVEL;
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

अटल पूर्णांक vega20_क्रमce_घड़ी_level(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, uपूर्णांक32_t mask)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t soft_min_level, soft_max_level, hard_min_level;
	पूर्णांक ret = 0;

	चयन (type) अणु
	हाल PP_SCLK:
		soft_min_level = mask ? (ffs(mask) - 1) : 0;
		soft_max_level = mask ? (fls(mask) - 1) : 0;

		अगर (soft_max_level >= data->dpm_table.gfx_table.count) अणु
			pr_err("Clock level specified %d is over max allowed %d\n",
					soft_max_level,
					data->dpm_table.gfx_table.count - 1);
			वापस -EINVAL;
		पूर्ण

		data->dpm_table.gfx_table.dpm_state.soft_min_level =
			data->dpm_table.gfx_table.dpm_levels[soft_min_level].value;
		data->dpm_table.gfx_table.dpm_state.soft_max_level =
			data->dpm_table.gfx_table.dpm_levels[soft_max_level].value;

		ret = vega20_upload_dpm_min_level(hwmgr, FEATURE_DPM_GFXCLK_MASK);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload boot level to lowest!",
			वापस ret);

		ret = vega20_upload_dpm_max_level(hwmgr, FEATURE_DPM_GFXCLK_MASK);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload dpm max level to highest!",
			वापस ret);
		अवरोध;

	हाल PP_MCLK:
		soft_min_level = mask ? (ffs(mask) - 1) : 0;
		soft_max_level = mask ? (fls(mask) - 1) : 0;

		अगर (soft_max_level >= data->dpm_table.mem_table.count) अणु
			pr_err("Clock level specified %d is over max allowed %d\n",
					soft_max_level,
					data->dpm_table.mem_table.count - 1);
			वापस -EINVAL;
		पूर्ण

		data->dpm_table.mem_table.dpm_state.soft_min_level =
			data->dpm_table.mem_table.dpm_levels[soft_min_level].value;
		data->dpm_table.mem_table.dpm_state.soft_max_level =
			data->dpm_table.mem_table.dpm_levels[soft_max_level].value;

		ret = vega20_upload_dpm_min_level(hwmgr, FEATURE_DPM_UCLK_MASK);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload boot level to lowest!",
			वापस ret);

		ret = vega20_upload_dpm_max_level(hwmgr, FEATURE_DPM_UCLK_MASK);
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

		ret = vega20_upload_dpm_min_level(hwmgr, FEATURE_DPM_SOCCLK_MASK);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload boot level to lowest!",
			वापस ret);

		ret = vega20_upload_dpm_max_level(hwmgr, FEATURE_DPM_SOCCLK_MASK);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload dpm max level to highest!",
			वापस ret);

		अवरोध;

	हाल PP_FCLK:
		soft_min_level = mask ? (ffs(mask) - 1) : 0;
		soft_max_level = mask ? (fls(mask) - 1) : 0;

		अगर (soft_max_level >= data->dpm_table.fclk_table.count) अणु
			pr_err("Clock level specified %d is over max allowed %d\n",
					soft_max_level,
					data->dpm_table.fclk_table.count - 1);
			वापस -EINVAL;
		पूर्ण

		data->dpm_table.fclk_table.dpm_state.soft_min_level =
			data->dpm_table.fclk_table.dpm_levels[soft_min_level].value;
		data->dpm_table.fclk_table.dpm_state.soft_max_level =
			data->dpm_table.fclk_table.dpm_levels[soft_max_level].value;

		ret = vega20_upload_dpm_min_level(hwmgr, FEATURE_DPM_FCLK_MASK);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload boot level to lowest!",
			वापस ret);

		ret = vega20_upload_dpm_max_level(hwmgr, FEATURE_DPM_FCLK_MASK);
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

		ret = vega20_upload_dpm_min_level(hwmgr, FEATURE_DPM_DCEFCLK_MASK);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to upload boot level to lowest!",
			वापस ret);

		//TODO: Setting DCEFCLK max dpm level is not supported

		अवरोध;

	हाल PP_PCIE:
		soft_min_level = mask ? (ffs(mask) - 1) : 0;
		soft_max_level = mask ? (fls(mask) - 1) : 0;
		अगर (soft_min_level >= NUM_LINK_LEVELS ||
		    soft_max_level >= NUM_LINK_LEVELS)
			वापस -EINVAL;

		ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetMinLinkDpmByIndex, soft_min_level,
			शून्य);
		PP_ASSERT_WITH_CODE(!ret,
			"Failed to set min link dpm level!",
			वापस ret);

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_dpm_क्रमce_dpm_level(काष्ठा pp_hwmgr *hwmgr,
				क्रमागत amd_dpm_क्रमced_level level)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t sclk_mask, mclk_mask, soc_mask;

	चयन (level) अणु
	हाल AMD_DPM_FORCED_LEVEL_HIGH:
		ret = vega20_क्रमce_dpm_highest(hwmgr);
		अवरोध;

	हाल AMD_DPM_FORCED_LEVEL_LOW:
		ret = vega20_क्रमce_dpm_lowest(hwmgr);
		अवरोध;

	हाल AMD_DPM_FORCED_LEVEL_AUTO:
		ret = vega20_unक्रमce_dpm_levels(hwmgr);
		अवरोध;

	हाल AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_PEAK:
		ret = vega20_get_profiling_clk_mask(hwmgr, level, &sclk_mask, &mclk_mask, &soc_mask);
		अगर (ret)
			वापस ret;
		vega20_क्रमce_घड़ी_level(hwmgr, PP_SCLK, 1 << sclk_mask);
		vega20_क्रमce_घड़ी_level(hwmgr, PP_MCLK, 1 << mclk_mask);
		vega20_क्रमce_घड़ी_level(hwmgr, PP_SOCCLK, 1 << soc_mask);
		अवरोध;

	हाल AMD_DPM_FORCED_LEVEL_MANUAL:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_EXIT:
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल uपूर्णांक32_t vega20_get_fan_control_mode(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);

	अगर (data->smu_features[GNLD_FAN_CONTROL].enabled == false)
		वापस AMD_FAN_CTRL_MANUAL;
	अन्यथा
		वापस AMD_FAN_CTRL_AUTO;
पूर्ण

अटल व्योम vega20_set_fan_control_mode(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t mode)
अणु
	चयन (mode) अणु
	हाल AMD_FAN_CTRL_NONE:
		vega20_fan_ctrl_set_fan_speed_percent(hwmgr, 100);
		अवरोध;
	हाल AMD_FAN_CTRL_MANUAL:
		अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl))
			vega20_fan_ctrl_stop_smc_fan_control(hwmgr);
		अवरोध;
	हाल AMD_FAN_CTRL_AUTO:
		अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl))
			vega20_fan_ctrl_start_smc_fan_control(hwmgr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक vega20_get_dal_घातer_level(काष्ठा pp_hwmgr *hwmgr,
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


अटल पूर्णांक vega20_get_sclks(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_single_dpm_table *dpm_table = &(data->dpm_table.gfx_table);
	पूर्णांक i, count;

	अगर (!data->smu_features[GNLD_DPM_GFXCLK].enabled)
		वापस -1;

	count = (dpm_table->count > MAX_NUM_CLOCKS) ? MAX_NUM_CLOCKS : dpm_table->count;
	घड़ीs->num_levels = count;

	क्रम (i = 0; i < count; i++) अणु
		घड़ीs->data[i].घड़ीs_in_khz =
			dpm_table->dpm_levels[i].value * 1000;
		घड़ीs->data[i].latency_in_us = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t vega20_get_mem_latency(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी)
अणु
	वापस 25;
पूर्ण

अटल पूर्णांक vega20_get_memघड़ीs(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_single_dpm_table *dpm_table = &(data->dpm_table.mem_table);
	पूर्णांक i, count;

	अगर (!data->smu_features[GNLD_DPM_UCLK].enabled)
		वापस -1;

	count = (dpm_table->count > MAX_NUM_CLOCKS) ? MAX_NUM_CLOCKS : dpm_table->count;
	घड़ीs->num_levels = data->mclk_latency_table.count = count;

	क्रम (i = 0; i < count; i++) अणु
		घड़ीs->data[i].घड़ीs_in_khz =
			data->mclk_latency_table.entries[i].frequency =
			dpm_table->dpm_levels[i].value * 1000;
		घड़ीs->data[i].latency_in_us =
			data->mclk_latency_table.entries[i].latency =
			vega20_get_mem_latency(hwmgr, dpm_table->dpm_levels[i].value);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_get_dcefघड़ीs(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_single_dpm_table *dpm_table = &(data->dpm_table.dcef_table);
	पूर्णांक i, count;

	अगर (!data->smu_features[GNLD_DPM_DCEFCLK].enabled)
		वापस -1;

	count = (dpm_table->count > MAX_NUM_CLOCKS) ? MAX_NUM_CLOCKS : dpm_table->count;
	घड़ीs->num_levels = count;

	क्रम (i = 0; i < count; i++) अणु
		घड़ीs->data[i].घड़ीs_in_khz =
			dpm_table->dpm_levels[i].value * 1000;
		घड़ीs->data[i].latency_in_us = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_get_socघड़ीs(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_single_dpm_table *dpm_table = &(data->dpm_table.soc_table);
	पूर्णांक i, count;

	अगर (!data->smu_features[GNLD_DPM_SOCCLK].enabled)
		वापस -1;

	count = (dpm_table->count > MAX_NUM_CLOCKS) ? MAX_NUM_CLOCKS : dpm_table->count;
	घड़ीs->num_levels = count;

	क्रम (i = 0; i < count; i++) अणु
		घड़ीs->data[i].घड़ीs_in_khz =
			dpm_table->dpm_levels[i].value * 1000;
		घड़ीs->data[i].latency_in_us = 0;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक vega20_get_घड़ी_by_type_with_latency(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	पूर्णांक ret;

	चयन (type) अणु
	हाल amd_pp_sys_घड़ी:
		ret = vega20_get_sclks(hwmgr, घड़ीs);
		अवरोध;
	हाल amd_pp_mem_घड़ी:
		ret = vega20_get_memघड़ीs(hwmgr, घड़ीs);
		अवरोध;
	हाल amd_pp_dcef_घड़ी:
		ret = vega20_get_dcefघड़ीs(hwmgr, घड़ीs);
		अवरोध;
	हाल amd_pp_soc_घड़ी:
		ret = vega20_get_socघड़ीs(hwmgr, घड़ीs);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vega20_get_घड़ी_by_type_with_voltage(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_voltage *घड़ीs)
अणु
	घड़ीs->num_levels = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_set_watermarks_क्रम_घड़ीs_ranges(काष्ठा pp_hwmgr *hwmgr,
						   व्योम *घड़ी_ranges)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
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

अटल पूर्णांक vega20_odn_edit_dpm_table(काष्ठा pp_hwmgr *hwmgr,
					क्रमागत PP_OD_DPM_TABLE_COMMAND type,
					दीर्घ *input, uपूर्णांक32_t size)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_od8_single_setting *od8_settings =
			data->od8_settings.od8_settings_array;
	OverDriveTable_t *od_table =
			&(data->smc_state_table.overdrive_table);
	पूर्णांक32_t input_index, input_clk, input_vol, i;
	पूर्णांक od8_id;
	पूर्णांक ret;

	PP_ASSERT_WITH_CODE(input, "NULL user input for clock and voltage",
				वापस -EINVAL);

	चयन (type) अणु
	हाल PP_OD_EDIT_SCLK_VDDC_TABLE:
		अगर (!(od8_settings[OD8_SETTING_GFXCLK_FMIN].feature_id &&
		      od8_settings[OD8_SETTING_GFXCLK_FMAX].feature_id)) अणु
			pr_info("Sclk min/max frequency overdrive not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		क्रम (i = 0; i < size; i += 2) अणु
			अगर (i + 2 > size) अणु
				pr_info("invalid number of input parameters %d\n",
					size);
				वापस -EINVAL;
			पूर्ण

			input_index = input[i];
			input_clk = input[i + 1];

			अगर (input_index != 0 && input_index != 1) अणु
				pr_info("Invalid index %d\n", input_index);
				pr_info("Support min/max sclk frequency setting only which index by 0/1\n");
				वापस -EINVAL;
			पूर्ण

			अगर (input_clk < od8_settings[OD8_SETTING_GFXCLK_FMIN].min_value ||
			    input_clk > od8_settings[OD8_SETTING_GFXCLK_FMAX].max_value) अणु
				pr_info("clock freq %d is not within allowed range [%d - %d]\n",
					input_clk,
					od8_settings[OD8_SETTING_GFXCLK_FMIN].min_value,
					od8_settings[OD8_SETTING_GFXCLK_FMAX].max_value);
				वापस -EINVAL;
			पूर्ण

			अगर ((input_index == 0 && od_table->GfxclkFmin != input_clk) ||
			    (input_index == 1 && od_table->GfxclkFmax != input_clk))
				data->gfxclk_overdrive = true;

			अगर (input_index == 0)
				od_table->GfxclkFmin = input_clk;
			अन्यथा
				od_table->GfxclkFmax = input_clk;
		पूर्ण

		अवरोध;

	हाल PP_OD_EDIT_MCLK_VDDC_TABLE:
		अगर (!od8_settings[OD8_SETTING_UCLK_FMAX].feature_id) अणु
			pr_info("Mclk max frequency overdrive not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		क्रम (i = 0; i < size; i += 2) अणु
			अगर (i + 2 > size) अणु
				pr_info("invalid number of input parameters %d\n",
					size);
				वापस -EINVAL;
			पूर्ण

			input_index = input[i];
			input_clk = input[i + 1];

			अगर (input_index != 1) अणु
				pr_info("Invalid index %d\n", input_index);
				pr_info("Support max Mclk frequency setting only which index by 1\n");
				वापस -EINVAL;
			पूर्ण

			अगर (input_clk < od8_settings[OD8_SETTING_UCLK_FMAX].min_value ||
			    input_clk > od8_settings[OD8_SETTING_UCLK_FMAX].max_value) अणु
				pr_info("clock freq %d is not within allowed range [%d - %d]\n",
					input_clk,
					od8_settings[OD8_SETTING_UCLK_FMAX].min_value,
					od8_settings[OD8_SETTING_UCLK_FMAX].max_value);
				वापस -EINVAL;
			पूर्ण

			अगर (input_index == 1 && od_table->UclkFmax != input_clk)
				data->memclk_overdrive = true;

			od_table->UclkFmax = input_clk;
		पूर्ण

		अवरोध;

	हाल PP_OD_EDIT_VDDC_CURVE:
		अगर (!(od8_settings[OD8_SETTING_GFXCLK_FREQ1].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_FREQ2].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_FREQ3].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_VOLTAGE1].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_VOLTAGE2].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_VOLTAGE3].feature_id)) अणु
			pr_info("Voltage curve calibrate not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		क्रम (i = 0; i < size; i += 3) अणु
			अगर (i + 3 > size) अणु
				pr_info("invalid number of input parameters %d\n",
					size);
				वापस -EINVAL;
			पूर्ण

			input_index = input[i];
			input_clk = input[i + 1];
			input_vol = input[i + 2];

			अगर (input_index > 2) अणु
				pr_info("Setting for point %d is not supported\n",
						input_index + 1);
				pr_info("Three supported points index by 0, 1, 2\n");
				वापस -EINVAL;
			पूर्ण

			od8_id = OD8_SETTING_GFXCLK_FREQ1 + 2 * input_index;
			अगर (input_clk < od8_settings[od8_id].min_value ||
			    input_clk > od8_settings[od8_id].max_value) अणु
				pr_info("clock freq %d is not within allowed range [%d - %d]\n",
					input_clk,
					od8_settings[od8_id].min_value,
					od8_settings[od8_id].max_value);
				वापस -EINVAL;
			पूर्ण

			od8_id = OD8_SETTING_GFXCLK_VOLTAGE1 + 2 * input_index;
			अगर (input_vol < od8_settings[od8_id].min_value ||
			    input_vol > od8_settings[od8_id].max_value) अणु
				pr_info("clock voltage %d is not within allowed range [%d - %d]\n",
					input_vol,
					od8_settings[od8_id].min_value,
					od8_settings[od8_id].max_value);
				वापस -EINVAL;
			पूर्ण

			चयन (input_index) अणु
			हाल 0:
				od_table->GfxclkFreq1 = input_clk;
				od_table->GfxclkVolt1 = input_vol * VOLTAGE_SCALE;
				अवरोध;
			हाल 1:
				od_table->GfxclkFreq2 = input_clk;
				od_table->GfxclkVolt2 = input_vol * VOLTAGE_SCALE;
				अवरोध;
			हाल 2:
				od_table->GfxclkFreq3 = input_clk;
				od_table->GfxclkVolt3 = input_vol * VOLTAGE_SCALE;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल PP_OD_RESTORE_DEFAULT_TABLE:
		data->gfxclk_overdrive = false;
		data->memclk_overdrive = false;

		ret = smum_smc_table_manager(hwmgr,
					     (uपूर्णांक8_t *)od_table,
					     TABLE_OVERDRIVE, true);
		PP_ASSERT_WITH_CODE(!ret,
				"Failed to export overdrive table!",
				वापस ret);
		अवरोध;

	हाल PP_OD_COMMIT_DPM_TABLE:
		ret = smum_smc_table_manager(hwmgr,
					     (uपूर्णांक8_t *)od_table,
					     TABLE_OVERDRIVE, false);
		PP_ASSERT_WITH_CODE(!ret,
				"Failed to import overdrive table!",
				वापस ret);

		/* retrieve updated gfxclk table */
		अगर (data->gfxclk_overdrive) अणु
			data->gfxclk_overdrive = false;

			ret = vega20_setup_gfxclk_dpm_table(hwmgr);
			अगर (ret)
				वापस ret;
		पूर्ण

		/* retrieve updated memclk table */
		अगर (data->memclk_overdrive) अणु
			data->memclk_overdrive = false;

			ret = vega20_setup_memclk_dpm_table(hwmgr);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_set_mp1_state(काष्ठा pp_hwmgr *hwmgr,
				क्रमागत pp_mp1_state mp1_state)
अणु
	uपूर्णांक16_t msg;
	पूर्णांक ret;

	चयन (mp1_state) अणु
	हाल PP_MP1_STATE_SHUTDOWN:
		msg = PPSMC_MSG_PrepareMp1ForShutकरोwn;
		अवरोध;
	हाल PP_MP1_STATE_UNLOAD:
		msg = PPSMC_MSG_PrepareMp1ForUnload;
		अवरोध;
	हाल PP_MP1_STATE_RESET:
		msg = PPSMC_MSG_PrepareMp1ForReset;
		अवरोध;
	हाल PP_MP1_STATE_NONE:
	शेष:
		वापस 0;
	पूर्ण

	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc(hwmgr, msg, शून्य)) == 0,
			    "[PrepareMp1] Failed!",
			    वापस ret);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_get_ppfeature_status(काष्ठा pp_hwmgr *hwmgr, अक्षर *buf)
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
				"GFX_EDC",
				"GFXOFF",
				"CG",
				"FCLK_DPM",
				"FCLK_DS",
				"MP1CLK_DS",
				"MP0CLK_DS",
				"XGMI",
				"ECC"पूर्ण;
	अटल स्थिर अक्षर *output_title[] = अणु
				"FEATURES",
				"BITMASK",
				"ENABLEMENT"पूर्ण;
	uपूर्णांक64_t features_enabled;
	पूर्णांक i;
	पूर्णांक ret = 0;
	पूर्णांक size = 0;

	ret = vega20_get_enabled_smc_features(hwmgr, &features_enabled);
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

अटल पूर्णांक vega20_set_ppfeature_status(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक64_t new_ppfeature_masks)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	uपूर्णांक64_t features_enabled, features_to_enable, features_to_disable;
	पूर्णांक i, ret = 0;
	bool enabled;

	अगर (new_ppfeature_masks >= (1ULL << GNLD_FEATURES_MAX))
		वापस -EINVAL;

	ret = vega20_get_enabled_smc_features(hwmgr, &features_enabled);
	अगर (ret)
		वापस ret;

	features_to_disable =
		features_enabled & ~new_ppfeature_masks;
	features_to_enable =
		~features_enabled & new_ppfeature_masks;

	pr_debug("features_to_disable 0x%llx\n", features_to_disable);
	pr_debug("features_to_enable 0x%llx\n", features_to_enable);

	अगर (features_to_disable) अणु
		ret = vega20_enable_smc_features(hwmgr, false, features_to_disable);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (features_to_enable) अणु
		ret = vega20_enable_smc_features(hwmgr, true, features_to_enable);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Update the cached feature enablement state */
	ret = vega20_get_enabled_smc_features(hwmgr, &features_enabled);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < GNLD_FEATURES_MAX; i++) अणु
		enabled = (features_enabled & data->smu_features[i].smu_feature_biपंचांगap) ?
			true : false;
		data->smu_features[i].enabled = enabled;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_get_current_pcie_link_width_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	वापस (RREG32_PCIE(smnPCIE_LC_LINK_WIDTH_CNTL) &
		PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD_MASK)
		>> PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD__SHIFT;
पूर्ण

अटल पूर्णांक vega20_get_current_pcie_link_width(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t width_level;

	width_level = vega20_get_current_pcie_link_width_level(hwmgr);
	अगर (width_level > LINK_WIDTH_MAX)
		width_level = 0;

	वापस link_width[width_level];
पूर्ण

अटल पूर्णांक vega20_get_current_pcie_link_speed_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	वापस (RREG32_PCIE(smnPCIE_LC_SPEED_CNTL) &
		PSWUSP0_PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE_MASK)
		>> PSWUSP0_PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE__SHIFT;
पूर्ण

अटल पूर्णांक vega20_get_current_pcie_link_speed(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t speed_level;

	speed_level = vega20_get_current_pcie_link_speed_level(hwmgr);
	अगर (speed_level > LINK_SPEED_MAX)
		speed_level = 0;

	वापस link_speed[speed_level];
पूर्ण

अटल पूर्णांक vega20_prपूर्णांक_घड़ी_levels(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, अक्षर *buf)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_od8_single_setting *od8_settings =
			data->od8_settings.od8_settings_array;
	OverDriveTable_t *od_table =
			&(data->smc_state_table.overdrive_table);
	PPTable_t *pptable = &(data->smc_state_table.pp_table);
	काष्ठा pp_घड़ी_levels_with_latency घड़ीs;
	काष्ठा vega20_single_dpm_table *fclk_dpm_table =
			&(data->dpm_table.fclk_table);
	पूर्णांक i, now, size = 0;
	पूर्णांक ret = 0;
	uपूर्णांक32_t gen_speed, lane_width, current_gen_speed, current_lane_width;

	चयन (type) अणु
	हाल PP_SCLK:
		ret = vega20_get_current_clk_freq(hwmgr, PPCLK_GFXCLK, &now);
		PP_ASSERT_WITH_CODE(!ret,
				"Attempt to get current gfx clk Failed!",
				वापस ret);

		अगर (vega20_get_sclks(hwmgr, &घड़ीs)) अणु
			size += प्र_लिखो(buf + size, "0: %uMhz * (DPM disabled)\n",
				now / 100);
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < घड़ीs.num_levels; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
				i, घड़ीs.data[i].घड़ीs_in_khz / 1000,
				(घड़ीs.data[i].घड़ीs_in_khz == now * 10) ? "*" : "");
		अवरोध;

	हाल PP_MCLK:
		ret = vega20_get_current_clk_freq(hwmgr, PPCLK_UCLK, &now);
		PP_ASSERT_WITH_CODE(!ret,
				"Attempt to get current mclk freq Failed!",
				वापस ret);

		अगर (vega20_get_memघड़ीs(hwmgr, &घड़ीs)) अणु
			size += प्र_लिखो(buf + size, "0: %uMhz * (DPM disabled)\n",
				now / 100);
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < घड़ीs.num_levels; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
				i, घड़ीs.data[i].घड़ीs_in_khz / 1000,
				(घड़ीs.data[i].घड़ीs_in_khz == now * 10) ? "*" : "");
		अवरोध;

	हाल PP_SOCCLK:
		ret = vega20_get_current_clk_freq(hwmgr, PPCLK_SOCCLK, &now);
		PP_ASSERT_WITH_CODE(!ret,
				"Attempt to get current socclk freq Failed!",
				वापस ret);

		अगर (vega20_get_socघड़ीs(hwmgr, &घड़ीs)) अणु
			size += प्र_लिखो(buf + size, "0: %uMhz * (DPM disabled)\n",
				now / 100);
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < घड़ीs.num_levels; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
				i, घड़ीs.data[i].घड़ीs_in_khz / 1000,
				(घड़ीs.data[i].घड़ीs_in_khz == now * 10) ? "*" : "");
		अवरोध;

	हाल PP_FCLK:
		ret = vega20_get_current_clk_freq(hwmgr, PPCLK_FCLK, &now);
		PP_ASSERT_WITH_CODE(!ret,
				"Attempt to get current fclk freq Failed!",
				वापस ret);

		क्रम (i = 0; i < fclk_dpm_table->count; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
				i, fclk_dpm_table->dpm_levels[i].value,
				fclk_dpm_table->dpm_levels[i].value == (now / 100) ? "*" : "");
		अवरोध;

	हाल PP_DCEFCLK:
		ret = vega20_get_current_clk_freq(hwmgr, PPCLK_DCEFCLK, &now);
		PP_ASSERT_WITH_CODE(!ret,
				"Attempt to get current dcefclk freq Failed!",
				वापस ret);

		अगर (vega20_get_dcefघड़ीs(hwmgr, &घड़ीs)) अणु
			size += प्र_लिखो(buf + size, "0: %uMhz * (DPM disabled)\n",
				now / 100);
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < घड़ीs.num_levels; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
				i, घड़ीs.data[i].घड़ीs_in_khz / 1000,
				(घड़ीs.data[i].घड़ीs_in_khz == now * 10) ? "*" : "");
		अवरोध;

	हाल PP_PCIE:
		current_gen_speed =
			vega20_get_current_pcie_link_speed_level(hwmgr);
		current_lane_width =
			vega20_get_current_pcie_link_width_level(hwmgr);
		क्रम (i = 0; i < NUM_LINK_LEVELS; i++) अणु
			gen_speed = pptable->PcieGenSpeed[i];
			lane_width = pptable->PcieLaneCount[i];

			size += प्र_लिखो(buf + size, "%d: %s %s %dMhz %s\n", i,
					(gen_speed == 0) ? "2.5GT/s," :
					(gen_speed == 1) ? "5.0GT/s," :
					(gen_speed == 2) ? "8.0GT/s," :
					(gen_speed == 3) ? "16.0GT/s," : "",
					(lane_width == 1) ? "x1" :
					(lane_width == 2) ? "x2" :
					(lane_width == 3) ? "x4" :
					(lane_width == 4) ? "x8" :
					(lane_width == 5) ? "x12" :
					(lane_width == 6) ? "x16" : "",
					pptable->LclkFreq[i],
					(current_gen_speed == gen_speed) &&
					(current_lane_width == lane_width) ?
					"*" : "");
		पूर्ण
		अवरोध;

	हाल OD_SCLK:
		अगर (od8_settings[OD8_SETTING_GFXCLK_FMIN].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_FMAX].feature_id) अणु
			size = प्र_लिखो(buf, "%s:\n", "OD_SCLK");
			size += प्र_लिखो(buf + size, "0: %10uMhz\n",
				od_table->GfxclkFmin);
			size += प्र_लिखो(buf + size, "1: %10uMhz\n",
				od_table->GfxclkFmax);
		पूर्ण
		अवरोध;

	हाल OD_MCLK:
		अगर (od8_settings[OD8_SETTING_UCLK_FMAX].feature_id) अणु
			size = प्र_लिखो(buf, "%s:\n", "OD_MCLK");
			size += प्र_लिखो(buf + size, "1: %10uMhz\n",
				od_table->UclkFmax);
		पूर्ण

		अवरोध;

	हाल OD_VDDC_CURVE:
		अगर (od8_settings[OD8_SETTING_GFXCLK_FREQ1].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_FREQ2].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_FREQ3].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_VOLTAGE1].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_VOLTAGE2].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_VOLTAGE3].feature_id) अणु
			size = प्र_लिखो(buf, "%s:\n", "OD_VDDC_CURVE");
			size += प्र_लिखो(buf + size, "0: %10uMhz %10dmV\n",
				od_table->GfxclkFreq1,
				od_table->GfxclkVolt1 / VOLTAGE_SCALE);
			size += प्र_लिखो(buf + size, "1: %10uMhz %10dmV\n",
				od_table->GfxclkFreq2,
				od_table->GfxclkVolt2 / VOLTAGE_SCALE);
			size += प्र_लिखो(buf + size, "2: %10uMhz %10dmV\n",
				od_table->GfxclkFreq3,
				od_table->GfxclkVolt3 / VOLTAGE_SCALE);
		पूर्ण

		अवरोध;

	हाल OD_RANGE:
		size = प्र_लिखो(buf, "%s:\n", "OD_RANGE");

		अगर (od8_settings[OD8_SETTING_GFXCLK_FMIN].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_FMAX].feature_id) अणु
			size += प्र_लिखो(buf + size, "SCLK: %7uMhz %10uMhz\n",
				od8_settings[OD8_SETTING_GFXCLK_FMIN].min_value,
				od8_settings[OD8_SETTING_GFXCLK_FMAX].max_value);
		पूर्ण

		अगर (od8_settings[OD8_SETTING_UCLK_FMAX].feature_id) अणु
			size += प्र_लिखो(buf + size, "MCLK: %7uMhz %10uMhz\n",
				od8_settings[OD8_SETTING_UCLK_FMAX].min_value,
				od8_settings[OD8_SETTING_UCLK_FMAX].max_value);
		पूर्ण

		अगर (od8_settings[OD8_SETTING_GFXCLK_FREQ1].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_FREQ2].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_FREQ3].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_VOLTAGE1].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_VOLTAGE2].feature_id &&
		    od8_settings[OD8_SETTING_GFXCLK_VOLTAGE3].feature_id) अणु
			size += प्र_लिखो(buf + size, "VDDC_CURVE_SCLK[0]: %7uMhz %10uMhz\n",
				od8_settings[OD8_SETTING_GFXCLK_FREQ1].min_value,
				od8_settings[OD8_SETTING_GFXCLK_FREQ1].max_value);
			size += प्र_लिखो(buf + size, "VDDC_CURVE_VOLT[0]: %7dmV %11dmV\n",
				od8_settings[OD8_SETTING_GFXCLK_VOLTAGE1].min_value,
				od8_settings[OD8_SETTING_GFXCLK_VOLTAGE1].max_value);
			size += प्र_लिखो(buf + size, "VDDC_CURVE_SCLK[1]: %7uMhz %10uMhz\n",
				od8_settings[OD8_SETTING_GFXCLK_FREQ2].min_value,
				od8_settings[OD8_SETTING_GFXCLK_FREQ2].max_value);
			size += प्र_लिखो(buf + size, "VDDC_CURVE_VOLT[1]: %7dmV %11dmV\n",
				od8_settings[OD8_SETTING_GFXCLK_VOLTAGE2].min_value,
				od8_settings[OD8_SETTING_GFXCLK_VOLTAGE2].max_value);
			size += प्र_लिखो(buf + size, "VDDC_CURVE_SCLK[2]: %7uMhz %10uMhz\n",
				od8_settings[OD8_SETTING_GFXCLK_FREQ3].min_value,
				od8_settings[OD8_SETTING_GFXCLK_FREQ3].max_value);
			size += प्र_लिखो(buf + size, "VDDC_CURVE_VOLT[2]: %7dmV %11dmV\n",
				od8_settings[OD8_SETTING_GFXCLK_VOLTAGE3].min_value,
				od8_settings[OD8_SETTING_GFXCLK_VOLTAGE3].max_value);
		पूर्ण

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस size;
पूर्ण

अटल पूर्णांक vega20_set_uclk_to_highest_dpm_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा vega20_single_dpm_table *dpm_table)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
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

अटल पूर्णांक vega20_set_fclk_to_highest_dpm_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_single_dpm_table *dpm_table = &(data->dpm_table.fclk_table);
	पूर्णांक ret = 0;

	अगर (data->smu_features[GNLD_DPM_FCLK].enabled) अणु
		PP_ASSERT_WITH_CODE(dpm_table->count > 0,
				"[SetFclkToHightestDpmLevel] Dpm table has no entry!",
				वापस -EINVAL);
		PP_ASSERT_WITH_CODE(dpm_table->count <= NUM_FCLK_DPM_LEVELS,
				"[SetFclkToHightestDpmLevel] Dpm table has too many entries!",
				वापस -EINVAL);

		dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		PP_ASSERT_WITH_CODE(!(ret = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSoftMinByFreq,
				(PPCLK_FCLK << 16 ) | dpm_table->dpm_state.soft_min_level,
				शून्य)),
				"[SetFclkToHightestDpmLevel] Set soft min fclk failed!",
				वापस ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vega20_pre_display_configuration_changed_task(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	पूर्णांक ret = 0;

	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_NumOfDisplays, 0, शून्य);

	ret = vega20_set_uclk_to_highest_dpm_level(hwmgr,
			&data->dpm_table.mem_table);
	अगर (ret)
		वापस ret;

	वापस vega20_set_fclk_to_highest_dpm_level(hwmgr);
पूर्ण

अटल पूर्णांक vega20_display_configuration_changed_task(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	पूर्णांक result = 0;
	Watermarks_t *wm_table = &(data->smc_state_table.water_marks_table);

	अगर ((data->water_marks_biपंचांगap & WaterMarksExist) &&
	    !(data->water_marks_biपंचांगap & WaterMarksLoaded)) अणु
		result = smum_smc_table_manager(hwmgr,
						(uपूर्णांक8_t *)wm_table, TABLE_WATERMARKS, false);
		PP_ASSERT_WITH_CODE(!result,
				"Failed to update WMTABLE!",
				वापस result);
		data->water_marks_biपंचांगap |= WaterMarksLoaded;
	पूर्ण

	अगर ((data->water_marks_biपंचांगap & WaterMarksExist) &&
	    data->smu_features[GNLD_DPM_DCEFCLK].supported &&
	    data->smu_features[GNLD_DPM_SOCCLK].supported) अणु
		result = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_NumOfDisplays,
			hwmgr->display_config->num_display,
			शून्य);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक vega20_enable_disable_uvd_dpm(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	पूर्णांक ret = 0;

	अगर (data->smu_features[GNLD_DPM_UVD].supported) अणु
		अगर (data->smu_features[GNLD_DPM_UVD].enabled == enable) अणु
			अगर (enable)
				PP_DBG_LOG("[EnableDisableUVDDPM] feature DPM UVD already enabled!\n");
			अन्यथा
				PP_DBG_LOG("[EnableDisableUVDDPM] feature DPM UVD already disabled!\n");
		पूर्ण

		ret = vega20_enable_smc_features(hwmgr,
				enable,
				data->smu_features[GNLD_DPM_UVD].smu_feature_biपंचांगap);
		PP_ASSERT_WITH_CODE(!ret,
				"[EnableDisableUVDDPM] Attempt to Enable/Disable DPM UVD Failed!",
				वापस ret);
		data->smu_features[GNLD_DPM_UVD].enabled = enable;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vega20_घातer_gate_vce(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);

	अगर (data->vce_घातer_gated == bgate)
		वापस ;

	data->vce_घातer_gated = bgate;
	अगर (bgate) अणु
		vega20_enable_disable_vce_dpm(hwmgr, !bgate);
		amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_VCE,
						AMD_PG_STATE_GATE);
	पूर्ण अन्यथा अणु
		amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_VCE,
						AMD_PG_STATE_UNGATE);
		vega20_enable_disable_vce_dpm(hwmgr, !bgate);
	पूर्ण

पूर्ण

अटल व्योम vega20_घातer_gate_uvd(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);

	अगर (data->uvd_घातer_gated == bgate)
		वापस ;

	data->uvd_घातer_gated = bgate;
	vega20_enable_disable_uvd_dpm(hwmgr, !bgate);
पूर्ण

अटल पूर्णांक vega20_apply_घड़ीs_adjust_rules(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा vega20_single_dpm_table *dpm_table;
	bool vblank_too_लघु = false;
	bool disable_mclk_चयनing;
	bool disable_fclk_चयनing;
	uपूर्णांक32_t i, latency;

	disable_mclk_चयनing = ((1 < hwmgr->display_config->num_display) &&
                           !hwmgr->display_config->multi_monitor_in_sync) ||
                            vblank_too_लघु;
	latency = hwmgr->display_config->dce_tolerable_mclk_in_active_latency;

	/* gfxclk */
	dpm_table = &(data->dpm_table.gfx_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;

	अगर (PP_CAP(PHM_Platक्रमmCaps_UMDPState)) अणु
		अगर (VEGA20_UMD_PSTATE_GFXCLK_LEVEL < dpm_table->count) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_GFXCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_GFXCLK_LEVEL].value;
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
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;

	अगर (PP_CAP(PHM_Platक्रमmCaps_UMDPState)) अणु
		अगर (VEGA20_UMD_PSTATE_MCLK_LEVEL < dpm_table->count) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_MCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_MCLK_LEVEL].value;
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

	अगर ((disable_mclk_चयनing &&
	    (dpm_table->dpm_state.hard_min_level == dpm_table->dpm_levels[dpm_table->count - 1].value)) ||
	     hwmgr->display_config->min_mem_set_घड़ी / 100 >= dpm_table->dpm_levels[dpm_table->count - 1].value)
		disable_fclk_चयनing = true;
	अन्यथा
		disable_fclk_चयनing = false;

	/* fclk */
	dpm_table = &(data->dpm_table.fclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;
	अगर (hwmgr->display_config->nb_pstate_चयन_disable || disable_fclk_चयनing)
		dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

	/* vclk */
	dpm_table = &(data->dpm_table.vclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;

	अगर (PP_CAP(PHM_Platक्रमmCaps_UMDPState)) अणु
		अगर (VEGA20_UMD_PSTATE_UVDCLK_LEVEL < dpm_table->count) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_UVDCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_UVDCLK_LEVEL].value;
		पूर्ण

		अगर (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		पूर्ण
	पूर्ण

	/* dclk */
	dpm_table = &(data->dpm_table.dclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;

	अगर (PP_CAP(PHM_Platक्रमmCaps_UMDPState)) अणु
		अगर (VEGA20_UMD_PSTATE_UVDCLK_LEVEL < dpm_table->count) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_UVDCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_UVDCLK_LEVEL].value;
		पूर्ण

		अगर (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		पूर्ण
	पूर्ण

	/* socclk */
	dpm_table = &(data->dpm_table.soc_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;

	अगर (PP_CAP(PHM_Platक्रमmCaps_UMDPState)) अणु
		अगर (VEGA20_UMD_PSTATE_SOCCLK_LEVEL < dpm_table->count) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_SOCCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_SOCCLK_LEVEL].value;
		पूर्ण

		अगर (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		पूर्ण
	पूर्ण

	/* eclk */
	dpm_table = &(data->dpm_table.eclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;

	अगर (PP_CAP(PHM_Platक्रमmCaps_UMDPState)) अणु
		अगर (VEGA20_UMD_PSTATE_VCEMCLK_LEVEL < dpm_table->count) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_VCEMCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_VCEMCLK_LEVEL].value;
		पूर्ण

		अगर (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
vega20_check_smc_update_required_क्रम_display_configuration(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	bool is_update_required = false;

	अगर (data->display_timing.num_existing_displays !=
			hwmgr->display_config->num_display)
		is_update_required = true;

	अगर (data->registry_data.gfx_clk_deep_sleep_support &&
	   (data->display_timing.min_घड़ी_in_sr !=
	    hwmgr->display_config->min_core_set_घड़ी_in_sr))
		is_update_required = true;

	वापस is_update_required;
पूर्ण

अटल पूर्णांक vega20_disable_dpm_tasks(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret = 0;

	ret = vega20_disable_all_smu_features(hwmgr);
	PP_ASSERT_WITH_CODE(!ret,
			"[DisableDpmTasks] Failed to disable all smu features!",
			वापस ret);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_घातer_off_asic(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	पूर्णांक result;

	result = vega20_disable_dpm_tasks(hwmgr);
	PP_ASSERT_WITH_CODE((0 == result),
			"[PowerOffAsic] Failed to disable DPM!",
			);
	data->water_marks_biपंचांगap &= ~(WaterMarksLoaded);

	वापस result;
पूर्ण

अटल पूर्णांक conv_घातer_profile_to_pplib_workload(पूर्णांक घातer_profile)
अणु
	पूर्णांक pplib_workload = 0;

	चयन (घातer_profile) अणु
	हाल PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT:
		pplib_workload = WORKLOAD_DEFAULT_BIT;
		अवरोध;
	हाल PP_SMC_POWER_PROखाता_FULLSCREEN3D:
		pplib_workload = WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT;
		अवरोध;
	हाल PP_SMC_POWER_PROखाता_POWERSAVING:
		pplib_workload = WORKLOAD_PPLIB_POWER_SAVING_BIT;
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

अटल पूर्णांक vega20_get_घातer_profile_mode(काष्ठा pp_hwmgr *hwmgr, अक्षर *buf)
अणु
	DpmActivityMonitorCoeffInt_t activity_monitor;
	uपूर्णांक32_t i, size = 0;
	uपूर्णांक16_t workload_type = 0;
	अटल स्थिर अक्षर *profile_name[] = अणु
					"BOOTUP_DEFAULT",
					"3D_FULL_SCREEN",
					"POWER_SAVING",
					"VIDEO",
					"VR",
					"COMPUTE",
					"CUSTOM"पूर्ण;
	अटल स्थिर अक्षर *title[] = अणु
			"PROFILE_INDEX(NAME)",
			"CLOCK_TYPE(NAME)",
			"FPS",
			"UseRlcBusy",
			"MinActiveFreqType",
			"MinActiveFreq",
			"BoosterFreqType",
			"BoosterFreq",
			"PD_Data_limit_c",
			"PD_Data_error_coeff",
			"PD_Data_error_rate_coeff"पूर्ण;
	पूर्णांक result = 0;

	अगर (!buf)
		वापस -EINVAL;

	size += प्र_लिखो(buf + size, "%16s %s %s %s %s %s %s %s %s %s %s\n",
			title[0], title[1], title[2], title[3], title[4], title[5],
			title[6], title[7], title[8], title[9], title[10]);

	क्रम (i = 0; i <= PP_SMC_POWER_PROखाता_CUSTOM; i++) अणु
		/* conv PP_SMC_POWER_PROखाता* to WORKLOAD_PPLIB_*_BIT */
		workload_type = conv_घातer_profile_to_pplib_workload(i);
		result = vega20_get_activity_monitor_coeff(hwmgr,
				(uपूर्णांक8_t *)(&activity_monitor), workload_type);
		PP_ASSERT_WITH_CODE(!result,
				"[GetPowerProfile] Failed to get activity monitor!",
				वापस result);

		size += प्र_लिखो(buf + size, "%2d %14s%s:\n",
			i, profile_name[i], (i == hwmgr->घातer_profile_mode) ? "*" : " ");

		size += प्र_लिखो(buf + size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			0,
			"GFXCLK",
			activity_monitor.Gfx_FPS,
			activity_monitor.Gfx_UseRlcBusy,
			activity_monitor.Gfx_MinActiveFreqType,
			activity_monitor.Gfx_MinActiveFreq,
			activity_monitor.Gfx_BoosterFreqType,
			activity_monitor.Gfx_BoosterFreq,
			activity_monitor.Gfx_PD_Data_limit_c,
			activity_monitor.Gfx_PD_Data_error_coeff,
			activity_monitor.Gfx_PD_Data_error_rate_coeff);

		size += प्र_लिखो(buf + size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			1,
			"SOCCLK",
			activity_monitor.Soc_FPS,
			activity_monitor.Soc_UseRlcBusy,
			activity_monitor.Soc_MinActiveFreqType,
			activity_monitor.Soc_MinActiveFreq,
			activity_monitor.Soc_BoosterFreqType,
			activity_monitor.Soc_BoosterFreq,
			activity_monitor.Soc_PD_Data_limit_c,
			activity_monitor.Soc_PD_Data_error_coeff,
			activity_monitor.Soc_PD_Data_error_rate_coeff);

		size += प्र_लिखो(buf + size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			2,
			"UCLK",
			activity_monitor.Mem_FPS,
			activity_monitor.Mem_UseRlcBusy,
			activity_monitor.Mem_MinActiveFreqType,
			activity_monitor.Mem_MinActiveFreq,
			activity_monitor.Mem_BoosterFreqType,
			activity_monitor.Mem_BoosterFreq,
			activity_monitor.Mem_PD_Data_limit_c,
			activity_monitor.Mem_PD_Data_error_coeff,
			activity_monitor.Mem_PD_Data_error_rate_coeff);

		size += प्र_लिखो(buf + size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			3,
			"FCLK",
			activity_monitor.Fclk_FPS,
			activity_monitor.Fclk_UseRlcBusy,
			activity_monitor.Fclk_MinActiveFreqType,
			activity_monitor.Fclk_MinActiveFreq,
			activity_monitor.Fclk_BoosterFreqType,
			activity_monitor.Fclk_BoosterFreq,
			activity_monitor.Fclk_PD_Data_limit_c,
			activity_monitor.Fclk_PD_Data_error_coeff,
			activity_monitor.Fclk_PD_Data_error_rate_coeff);
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक vega20_set_घातer_profile_mode(काष्ठा pp_hwmgr *hwmgr, दीर्घ *input, uपूर्णांक32_t size)
अणु
	DpmActivityMonitorCoeffInt_t activity_monitor;
	पूर्णांक workload_type, result = 0;
	uपूर्णांक32_t घातer_profile_mode = input[size];

	अगर (घातer_profile_mode > PP_SMC_POWER_PROखाता_CUSTOM) अणु
		pr_err("Invalid power profile mode %d\n", घातer_profile_mode);
		वापस -EINVAL;
	पूर्ण

	अगर (घातer_profile_mode == PP_SMC_POWER_PROखाता_CUSTOM) अणु
		काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
		अगर (size == 0 && !data->is_custom_profile_set)
			वापस -EINVAL;
		अगर (size < 10 && size != 0)
			वापस -EINVAL;

		result = vega20_get_activity_monitor_coeff(hwmgr,
				(uपूर्णांक8_t *)(&activity_monitor),
				WORKLOAD_PPLIB_CUSTOM_BIT);
		PP_ASSERT_WITH_CODE(!result,
				"[SetPowerProfile] Failed to get activity monitor!",
				वापस result);

		/* If size==0, then we want to apply the alपढ़ोy-configured
		 * CUSTOM profile again. Just apply it, since we checked its
		 * validity above
		 */
		अगर (size == 0)
			जाओ out;

		चयन (input[0]) अणु
		हाल 0: /* Gfxclk */
			activity_monitor.Gfx_FPS = input[1];
			activity_monitor.Gfx_UseRlcBusy = input[2];
			activity_monitor.Gfx_MinActiveFreqType = input[3];
			activity_monitor.Gfx_MinActiveFreq = input[4];
			activity_monitor.Gfx_BoosterFreqType = input[5];
			activity_monitor.Gfx_BoosterFreq = input[6];
			activity_monitor.Gfx_PD_Data_limit_c = input[7];
			activity_monitor.Gfx_PD_Data_error_coeff = input[8];
			activity_monitor.Gfx_PD_Data_error_rate_coeff = input[9];
			अवरोध;
		हाल 1: /* Socclk */
			activity_monitor.Soc_FPS = input[1];
			activity_monitor.Soc_UseRlcBusy = input[2];
			activity_monitor.Soc_MinActiveFreqType = input[3];
			activity_monitor.Soc_MinActiveFreq = input[4];
			activity_monitor.Soc_BoosterFreqType = input[5];
			activity_monitor.Soc_BoosterFreq = input[6];
			activity_monitor.Soc_PD_Data_limit_c = input[7];
			activity_monitor.Soc_PD_Data_error_coeff = input[8];
			activity_monitor.Soc_PD_Data_error_rate_coeff = input[9];
			अवरोध;
		हाल 2: /* Uclk */
			activity_monitor.Mem_FPS = input[1];
			activity_monitor.Mem_UseRlcBusy = input[2];
			activity_monitor.Mem_MinActiveFreqType = input[3];
			activity_monitor.Mem_MinActiveFreq = input[4];
			activity_monitor.Mem_BoosterFreqType = input[5];
			activity_monitor.Mem_BoosterFreq = input[6];
			activity_monitor.Mem_PD_Data_limit_c = input[7];
			activity_monitor.Mem_PD_Data_error_coeff = input[8];
			activity_monitor.Mem_PD_Data_error_rate_coeff = input[9];
			अवरोध;
		हाल 3: /* Fclk */
			activity_monitor.Fclk_FPS = input[1];
			activity_monitor.Fclk_UseRlcBusy = input[2];
			activity_monitor.Fclk_MinActiveFreqType = input[3];
			activity_monitor.Fclk_MinActiveFreq = input[4];
			activity_monitor.Fclk_BoosterFreqType = input[5];
			activity_monitor.Fclk_BoosterFreq = input[6];
			activity_monitor.Fclk_PD_Data_limit_c = input[7];
			activity_monitor.Fclk_PD_Data_error_coeff = input[8];
			activity_monitor.Fclk_PD_Data_error_rate_coeff = input[9];
			अवरोध;
		पूर्ण

		result = vega20_set_activity_monitor_coeff(hwmgr,
				(uपूर्णांक8_t *)(&activity_monitor),
				WORKLOAD_PPLIB_CUSTOM_BIT);
		data->is_custom_profile_set = true;
		PP_ASSERT_WITH_CODE(!result,
				"[SetPowerProfile] Failed to set activity monitor!",
				वापस result);
	पूर्ण

out:
	/* conv PP_SMC_POWER_PROखाता* to WORKLOAD_PPLIB_*_BIT */
	workload_type =
		conv_घातer_profile_to_pplib_workload(घातer_profile_mode);
	smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_SetWorkloadMask,
						1 << workload_type,
						शून्य);

	hwmgr->घातer_profile_mode = घातer_profile_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_notअगरy_cac_buffer_info(काष्ठा pp_hwmgr *hwmgr,
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

अटल पूर्णांक vega20_get_thermal_temperature_range(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा PP_TemperatureRange *thermal_data)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
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

अटल पूर्णांक vega20_smu_i2c_bus_access(काष्ठा pp_hwmgr *hwmgr, bool acquire)
अणु
	पूर्णांक res;

	/* I2C bus access can happen very early, when SMU not loaded yet */
	अगर (!vega20_is_smc_ram_running(hwmgr))
		वापस 0;

	res = smum_send_msg_to_smc_with_parameter(hwmgr,
						  (acquire ?
						  PPSMC_MSG_RequestI2CBus :
						  PPSMC_MSG_ReleaseI2CBus),
						  0,
						  शून्य);

	PP_ASSERT_WITH_CODE(!res, "[SmuI2CAccessBus] Failed to access bus!", वापस res);
	वापस res;
पूर्ण

अटल पूर्णांक vega20_set_df_cstate(काष्ठा pp_hwmgr *hwmgr,
				क्रमागत pp_df_cstate state)
अणु
	पूर्णांक ret;

	/* PPSMC_MSG_DFCstateControl is supported with 40.50 and later fws */
	अगर (hwmgr->smu_version < 0x283200) अणु
		pr_err("Df cstate control is supported with 40.50 and later SMC fw!\n");
		वापस -EINVAL;
	पूर्ण

	ret = smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_DFCstateControl, state,
				शून्य);
	अगर (ret)
		pr_err("SetDfCstate failed!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक vega20_set_xgmi_pstate(काष्ठा pp_hwmgr *hwmgr,
				  uपूर्णांक32_t pstate)
अणु
	पूर्णांक ret;

	ret = smum_send_msg_to_smc_with_parameter(hwmgr,
						  PPSMC_MSG_SetXgmiMode,
						  pstate ? XGMI_MODE_PSTATE_D0 : XGMI_MODE_PSTATE_D3,
						  शून्य);
	अगर (ret)
		pr_err("SetXgmiPstate failed!\n");

	वापस ret;
पूर्ण

अटल व्योम vega20_init_gpu_metrics_v1_0(काष्ठा gpu_metrics_v1_0 *gpu_metrics)
अणु
	स_रखो(gpu_metrics, 0xFF, माप(काष्ठा gpu_metrics_v1_0));

	gpu_metrics->common_header.काष्ठाure_size =
				माप(काष्ठा gpu_metrics_v1_0);
	gpu_metrics->common_header.क्रमmat_revision = 1;
	gpu_metrics->common_header.content_revision = 0;

	gpu_metrics->प्रणाली_घड़ी_counter = kसमय_get_bootसमय_ns();
पूर्ण

अटल sमाप_प्रकार vega20_get_gpu_metrics(काष्ठा pp_hwmgr *hwmgr,
				      व्योम **table)
अणु
	काष्ठा vega20_hwmgr *data =
			(काष्ठा vega20_hwmgr *)(hwmgr->backend);
	काष्ठा gpu_metrics_v1_0 *gpu_metrics =
			&data->gpu_metrics_table;
	SmuMetrics_t metrics;
	uपूर्णांक32_t fan_speed_rpm;
	पूर्णांक ret;

	ret = vega20_get_metrics_table(hwmgr, &metrics, true);
	अगर (ret)
		वापस ret;

	vega20_init_gpu_metrics_v1_0(gpu_metrics);

	gpu_metrics->temperature_edge = metrics.TemperatureEdge;
	gpu_metrics->temperature_hotspot = metrics.TemperatureHotspot;
	gpu_metrics->temperature_mem = metrics.TemperatureHBM;
	gpu_metrics->temperature_vrgfx = metrics.TemperatureVrGfx;
	gpu_metrics->temperature_vrsoc = metrics.TemperatureVrSoc;
	gpu_metrics->temperature_vrmem = metrics.TemperatureVrMem0;

	gpu_metrics->average_gfx_activity = metrics.AverageGfxActivity;
	gpu_metrics->average_umc_activity = metrics.AverageUclkActivity;

	gpu_metrics->average_socket_घातer = metrics.AverageSocketPower;

	gpu_metrics->average_gfxclk_frequency = metrics.AverageGfxclkFrequency;
	gpu_metrics->average_socclk_frequency = metrics.AverageSocclkFrequency;
	gpu_metrics->average_uclk_frequency = metrics.AverageUclkFrequency;

	gpu_metrics->current_gfxclk = metrics.CurrClock[PPCLK_GFXCLK];
	gpu_metrics->current_socclk = metrics.CurrClock[PPCLK_SOCCLK];
	gpu_metrics->current_uclk = metrics.CurrClock[PPCLK_UCLK];
	gpu_metrics->current_vclk0 = metrics.CurrClock[PPCLK_VCLK];
	gpu_metrics->current_dclk0 = metrics.CurrClock[PPCLK_DCLK];

	gpu_metrics->throttle_status = metrics.ThrottlerStatus;

	vega20_fan_ctrl_get_fan_speed_rpm(hwmgr, &fan_speed_rpm);
	gpu_metrics->current_fan_speed = (uपूर्णांक16_t)fan_speed_rpm;

	gpu_metrics->pcie_link_width =
			vega20_get_current_pcie_link_width(hwmgr);
	gpu_metrics->pcie_link_speed =
			vega20_get_current_pcie_link_speed(hwmgr);

	*table = (व्योम *)gpu_metrics;

	वापस माप(काष्ठा gpu_metrics_v1_0);
पूर्ण

अटल स्थिर काष्ठा pp_hwmgr_func vega20_hwmgr_funcs = अणु
	/* init/fini related */
	.backend_init = vega20_hwmgr_backend_init,
	.backend_fini = vega20_hwmgr_backend_fini,
	.asic_setup = vega20_setup_asic_task,
	.घातer_off_asic = vega20_घातer_off_asic,
	.dynamic_state_management_enable = vega20_enable_dpm_tasks,
	.dynamic_state_management_disable = vega20_disable_dpm_tasks,
	/* घातer state related */
	.apply_घड़ीs_adjust_rules = vega20_apply_घड़ीs_adjust_rules,
	.pre_display_config_changed = vega20_pre_display_configuration_changed_task,
	.display_config_changed = vega20_display_configuration_changed_task,
	.check_smc_update_required_क्रम_display_configuration =
		vega20_check_smc_update_required_क्रम_display_configuration,
	.notअगरy_smc_display_config_after_ps_adjusपंचांगent =
		vega20_notअगरy_smc_display_config_after_ps_adjusपंचांगent,
	/* export to DAL */
	.get_sclk = vega20_dpm_get_sclk,
	.get_mclk = vega20_dpm_get_mclk,
	.get_dal_घातer_level = vega20_get_dal_घातer_level,
	.get_घड़ी_by_type_with_latency = vega20_get_घड़ी_by_type_with_latency,
	.get_घड़ी_by_type_with_voltage = vega20_get_घड़ी_by_type_with_voltage,
	.set_watermarks_क्रम_घड़ीs_ranges = vega20_set_watermarks_क्रम_घड़ीs_ranges,
	.display_घड़ी_voltage_request = vega20_display_घड़ी_voltage_request,
	.get_perक्रमmance_level = vega20_get_perक्रमmance_level,
	/* UMD pstate, profile related */
	.क्रमce_dpm_level = vega20_dpm_क्रमce_dpm_level,
	.get_घातer_profile_mode = vega20_get_घातer_profile_mode,
	.set_घातer_profile_mode = vega20_set_घातer_profile_mode,
	/* od related */
	.set_घातer_limit = vega20_set_घातer_limit,
	.get_sclk_od = vega20_get_sclk_od,
	.set_sclk_od = vega20_set_sclk_od,
	.get_mclk_od = vega20_get_mclk_od,
	.set_mclk_od = vega20_set_mclk_od,
	.odn_edit_dpm_table = vega20_odn_edit_dpm_table,
	/* क्रम sysfs to retrive/set gfxclk/memclk */
	.क्रमce_घड़ी_level = vega20_क्रमce_घड़ी_level,
	.prपूर्णांक_घड़ी_levels = vega20_prपूर्णांक_घड़ी_levels,
	.पढ़ो_sensor = vega20_पढ़ो_sensor,
	.get_ppfeature_status = vega20_get_ppfeature_status,
	.set_ppfeature_status = vega20_set_ppfeature_status,
	/* घातergate related */
	.घातergate_uvd = vega20_घातer_gate_uvd,
	.घातergate_vce = vega20_घातer_gate_vce,
	/* thermal related */
	.start_thermal_controller = vega20_start_thermal_controller,
	.stop_thermal_controller = vega20_thermal_stop_thermal_controller,
	.get_thermal_temperature_range = vega20_get_thermal_temperature_range,
	.रेजिस्टर_irq_handlers = smu9_रेजिस्टर_irq_handlers,
	.disable_smc_firmware_ctf = vega20_thermal_disable_alert,
	/* fan control related */
	.get_fan_speed_percent = vega20_fan_ctrl_get_fan_speed_percent,
	.set_fan_speed_percent = vega20_fan_ctrl_set_fan_speed_percent,
	.get_fan_speed_info = vega20_fan_ctrl_get_fan_speed_info,
	.get_fan_speed_rpm = vega20_fan_ctrl_get_fan_speed_rpm,
	.set_fan_speed_rpm = vega20_fan_ctrl_set_fan_speed_rpm,
	.get_fan_control_mode = vega20_get_fan_control_mode,
	.set_fan_control_mode = vega20_set_fan_control_mode,
	/* smu memory related */
	.notअगरy_cac_buffer_info = vega20_notअगरy_cac_buffer_info,
	.enable_mgpu_fan_boost = vega20_enable_mgpu_fan_boost,
	/* BACO related */
	.get_asic_baco_capability = vega20_baco_get_capability,
	.get_asic_baco_state = vega20_baco_get_state,
	.set_asic_baco_state = vega20_baco_set_state,
	.set_mp1_state = vega20_set_mp1_state,
	.smu_i2c_bus_access = vega20_smu_i2c_bus_access,
	.set_df_cstate = vega20_set_df_cstate,
	.set_xgmi_pstate = vega20_set_xgmi_pstate,
	.get_gpu_metrics = vega20_get_gpu_metrics,
पूर्ण;

पूर्णांक vega20_hwmgr_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	hwmgr->hwmgr_func = &vega20_hwmgr_funcs;
	hwmgr->pptable_func = &vega20_pptable_funcs;

	वापस 0;
पूर्ण
