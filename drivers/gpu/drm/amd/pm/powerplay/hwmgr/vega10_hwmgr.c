<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश "hwmgr.h"
#समावेश "amd_powerplay.h"
#समावेश "hardwaremanager.h"
#समावेश "ppatomfwctrl.h"
#समावेश "atomfirmware.h"
#समावेश "cgs_common.h"
#समावेश "vega10_powertune.h"
#समावेश "smu9.h"
#समावेश "smu9_driver_if.h"
#समावेश "vega10_inc.h"
#समावेश "soc15_common.h"
#समावेश "pppcielanes.h"
#समावेश "vega10_hwmgr.h"
#समावेश "vega10_smumgr.h"
#समावेश "vega10_processpptables.h"
#समावेश "vega10_pptable.h"
#समावेश "vega10_thermal.h"
#समावेश "pp_debug.h"
#समावेश "amd_pcie_helpers.h"
#समावेश "ppinterrupt.h"
#समावेश "pp_overdriver.h"
#समावेश "pp_thermal.h"
#समावेश "vega10_baco.h"

#समावेश "smuio/smuio_9_0_offset.h"
#समावेश "smuio/smuio_9_0_sh_mask.h"

#घोषणा smnPCIE_LC_SPEED_CNTL			0x11140290
#घोषणा smnPCIE_LC_LINK_WIDTH_CNTL		0x11140288

#घोषणा HBM_MEMORY_CHANNEL_WIDTH    128

अटल स्थिर uपूर्णांक32_t channel_number[] = अणु1, 2, 0, 4, 0, 8, 0, 16, 2पूर्ण;

#घोषणा mmDF_CS_AON0_DramBaseAddress0                                                                  0x0044
#घोषणा mmDF_CS_AON0_DramBaseAddress0_BASE_IDX                                                         0

//DF_CS_AON0_DramBaseAddress0
#घोषणा DF_CS_AON0_DramBaseAddress0__AddrRngVal__SHIFT                                                        0x0
#घोषणा DF_CS_AON0_DramBaseAddress0__LgcyMmioHoleEn__SHIFT                                                    0x1
#घोषणा DF_CS_AON0_DramBaseAddress0__IntLvNumChan__SHIFT                                                      0x4
#घोषणा DF_CS_AON0_DramBaseAddress0__IntLvAddrSel__SHIFT                                                      0x8
#घोषणा DF_CS_AON0_DramBaseAddress0__DramBaseAddr__SHIFT                                                      0xc
#घोषणा DF_CS_AON0_DramBaseAddress0__AddrRngVal_MASK                                                          0x00000001L
#घोषणा DF_CS_AON0_DramBaseAddress0__LgcyMmioHoleEn_MASK                                                      0x00000002L
#घोषणा DF_CS_AON0_DramBaseAddress0__IntLvNumChan_MASK                                                        0x000000F0L
#घोषणा DF_CS_AON0_DramBaseAddress0__IntLvAddrSel_MASK                                                        0x00000700L
#घोषणा DF_CS_AON0_DramBaseAddress0__DramBaseAddr_MASK                                                        0xFFFFF000L

प्रकार क्रमागत अणु
	CLK_SMNCLK = 0,
	CLK_SOCCLK,
	CLK_MP0CLK,
	CLK_MP1CLK,
	CLK_LCLK,
	CLK_DCEFCLK,
	CLK_VCLK,
	CLK_DCLK,
	CLK_ECLK,
	CLK_UCLK,
	CLK_GFXCLK,
	CLK_COUNT,
पूर्ण CLOCK_ID_e;

अटल स्थिर ULONG PhwVega10_Magic = (ULONG)(PHM_VIslands_Magic);

अटल काष्ठा vega10_घातer_state *cast_phw_vega10_घातer_state(
				  काष्ठा pp_hw_घातer_state *hw_ps)
अणु
	PP_ASSERT_WITH_CODE((PhwVega10_Magic == hw_ps->magic),
				"Invalid Powerstate Type!",
				 वापस शून्य;);

	वापस (काष्ठा vega10_घातer_state *)hw_ps;
पूर्ण

अटल स्थिर काष्ठा vega10_घातer_state *cast_स्थिर_phw_vega10_घातer_state(
				 स्थिर काष्ठा pp_hw_घातer_state *hw_ps)
अणु
	PP_ASSERT_WITH_CODE((PhwVega10_Magic == hw_ps->magic),
				"Invalid Powerstate Type!",
				 वापस शून्य;);

	वापस (स्थिर काष्ठा vega10_घातer_state *)hw_ps;
पूर्ण

अटल व्योम vega10_set_शेष_registry_data(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	data->registry_data.sclk_dpm_key_disabled =
			hwmgr->feature_mask & PP_SCLK_DPM_MASK ? false : true;
	data->registry_data.socclk_dpm_key_disabled =
			hwmgr->feature_mask & PP_SOCCLK_DPM_MASK ? false : true;
	data->registry_data.mclk_dpm_key_disabled =
			hwmgr->feature_mask & PP_MCLK_DPM_MASK ? false : true;
	data->registry_data.pcie_dpm_key_disabled =
			hwmgr->feature_mask & PP_PCIE_DPM_MASK ? false : true;

	data->registry_data.dcefclk_dpm_key_disabled =
			hwmgr->feature_mask & PP_DCEFCLK_DPM_MASK ? false : true;

	अगर (hwmgr->feature_mask & PP_POWER_CONTAINMENT_MASK) अणु
		data->registry_data.घातer_containment_support = 1;
		data->registry_data.enable_pkg_pwr_tracking_feature = 1;
		data->registry_data.enable_tdc_limit_feature = 1;
	पूर्ण

	data->registry_data.घड़ी_stretcher_support =
			hwmgr->feature_mask & PP_CLOCK_STRETCH_MASK ? true : false;

	data->registry_data.ulv_support =
			hwmgr->feature_mask & PP_ULV_MASK ? true : false;

	data->registry_data.sclk_deep_sleep_support =
			hwmgr->feature_mask & PP_SCLK_DEEP_SLEEP_MASK ? true : false;

	data->registry_data.disable_water_mark = 0;

	data->registry_data.fan_control_support = 1;
	data->registry_data.thermal_support = 1;
	data->registry_data.fw_ctf_enabled = 1;

	data->registry_data.avfs_support =
		hwmgr->feature_mask & PP_AVFS_MASK ? true : false;
	data->registry_data.led_dpm_enabled = 1;

	data->registry_data.vr0hot_enabled = 1;
	data->registry_data.vr1hot_enabled = 1;
	data->registry_data.regulator_hot_gpio_support = 1;

	data->registry_data.didt_support = 1;
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

	data->display_voltage_mode = PPVEGA10_VEGA10DISPLAYVOLTAGEMODE_DFLT;
	data->dcef_clk_quad_eqn_a = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->dcef_clk_quad_eqn_b = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->dcef_clk_quad_eqn_c = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_a = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_b = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_c = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_a = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_b = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_c = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_a = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_b = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_c = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;

	data->gfxclk_average_alpha = PPVEGA10_VEGA10GFXCLKAVERAGEALPHA_DFLT;
	data->socclk_average_alpha = PPVEGA10_VEGA10SOCCLKAVERAGEALPHA_DFLT;
	data->uclk_average_alpha = PPVEGA10_VEGA10UCLKCLKAVERAGEALPHA_DFLT;
	data->gfx_activity_average_alpha = PPVEGA10_VEGA10GFXACTIVITYAVERAGEALPHA_DFLT;
पूर्ण

अटल पूर्णांक vega10_set_features_platक्रमm_caps(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)hwmgr->pptable;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SclkDeepSleep);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_DynamicPatchPowerState);

	अगर (data->vddci_control == VEGA10_VOLTAGE_CONTROL_NONE)
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_ControlVDDCI);

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

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_FanSpeedInTableIsRPM);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ODFuzzyFanControlSupport);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_DynamicPowerManagement);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SMC);

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

	अगर (data->registry_data.घातer_containment_support)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_PowerContainment);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_CAC);

	अगर (table_info->tdp_table->usClockStretchAmount &&
			data->registry_data.घड़ी_stretcher_support)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_ClockStretcher);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_RegulatorHot);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_AutomaticDCTransition);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_UVDDPM);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_VCEDPM);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_odn_initial_शेष_setting(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा vega10_odn_dpm_table *odn_table = &(data->odn_dpm_table);
	काष्ठा vega10_odn_vddc_lookup_table *od_lookup_table;
	काष्ठा phm_ppt_v1_voltage_lookup_table *vddc_lookup_table;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table[3];
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *od_table[3];
	काष्ठा pp_atomfwctrl_avfs_parameters avfs_params = अणु0पूर्ण;
	uपूर्णांक32_t i;
	पूर्णांक result;

	result = pp_atomfwctrl_get_avfs_inक्रमmation(hwmgr, &avfs_params);
	अगर (!result) अणु
		data->odn_dpm_table.max_vddc = avfs_params.ulMaxVddc;
		data->odn_dpm_table.min_vddc = avfs_params.ulMinVddc;
	पूर्ण

	od_lookup_table = &odn_table->vddc_lookup_table;
	vddc_lookup_table = table_info->vddc_lookup_table;

	क्रम (i = 0; i < vddc_lookup_table->count; i++)
		od_lookup_table->entries[i].us_vdd = vddc_lookup_table->entries[i].us_vdd;

	od_lookup_table->count = vddc_lookup_table->count;

	dep_table[0] = table_info->vdd_dep_on_sclk;
	dep_table[1] = table_info->vdd_dep_on_mclk;
	dep_table[2] = table_info->vdd_dep_on_socclk;
	od_table[0] = (काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *)&odn_table->vdd_dep_on_sclk;
	od_table[1] = (काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *)&odn_table->vdd_dep_on_mclk;
	od_table[2] = (काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *)&odn_table->vdd_dep_on_socclk;

	क्रम (i = 0; i < 3; i++)
		smu_get_voltage_dependency_table_ppt_v1(dep_table[i], od_table[i]);

	अगर (odn_table->max_vddc == 0 || odn_table->max_vddc > 2000)
		odn_table->max_vddc = dep_table[0]->entries[dep_table[0]->count - 1].vddc;
	अगर (odn_table->min_vddc == 0 || odn_table->min_vddc > 2000)
		odn_table->min_vddc = dep_table[0]->entries[0].vddc;

	i = od_table[2]->count - 1;
	od_table[2]->entries[i].clk = hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock > od_table[2]->entries[i].clk ?
					hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock :
					od_table[2]->entries[i].clk;
	od_table[2]->entries[i].vddc = odn_table->max_vddc > od_table[2]->entries[i].vddc ?
					odn_table->max_vddc :
					od_table[2]->entries[i].vddc;

	वापस 0;
पूर्ण

अटल व्योम vega10_init_dpm_शेषs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	पूर्णांक i;
	uपूर्णांक32_t sub_venकरोr_id, hw_revision;
	uपूर्णांक32_t top32, bottom32;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	vega10_initialize_घातer_tune_शेषs(hwmgr);

	क्रम (i = 0; i < GNLD_FEATURES_MAX; i++) अणु
		data->smu_features[i].smu_feature_id = 0xffff;
		data->smu_features[i].smu_feature_biपंचांगap = 1 << i;
		data->smu_features[i].enabled = false;
		data->smu_features[i].supported = false;
	पूर्ण

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
	data->smu_features[GNLD_DPM_MP0CLK].smu_feature_id =
			FEATURE_DPM_MP0CLK_BIT;
	data->smu_features[GNLD_DPM_LINK].smu_feature_id =
			FEATURE_DPM_LINK_BIT;
	data->smu_features[GNLD_DPM_DCEFCLK].smu_feature_id =
			FEATURE_DPM_DCEFCLK_BIT;
	data->smu_features[GNLD_ULV].smu_feature_id =
			FEATURE_ULV_BIT;
	data->smu_features[GNLD_AVFS].smu_feature_id =
			FEATURE_AVFS_BIT;
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
	data->smu_features[GNLD_ACG].smu_feature_id = FEATURE_ACG_BIT;
	data->smu_features[GNLD_DIDT].smu_feature_id = FEATURE_GFX_EDC_BIT;
	data->smu_features[GNLD_PCC_LIMIT].smu_feature_id = FEATURE_PCC_LIMIT_CONTROL_BIT;

	अगर (!data->registry_data.prefetcher_dpm_key_disabled)
		data->smu_features[GNLD_DPM_PREFETCHER].supported = true;

	अगर (!data->registry_data.sclk_dpm_key_disabled)
		data->smu_features[GNLD_DPM_GFXCLK].supported = true;

	अगर (!data->registry_data.mclk_dpm_key_disabled)
		data->smu_features[GNLD_DPM_UCLK].supported = true;

	अगर (!data->registry_data.socclk_dpm_key_disabled)
		data->smu_features[GNLD_DPM_SOCCLK].supported = true;

	अगर (PP_CAP(PHM_Platक्रमmCaps_UVDDPM))
		data->smu_features[GNLD_DPM_UVD].supported = true;

	अगर (PP_CAP(PHM_Platक्रमmCaps_VCEDPM))
		data->smu_features[GNLD_DPM_VCE].supported = true;

	data->smu_features[GNLD_DPM_LINK].supported = true;

	अगर (!data->registry_data.dcefclk_dpm_key_disabled)
		data->smu_features[GNLD_DPM_DCEFCLK].supported = true;

	अगर (PP_CAP(PHM_Platक्रमmCaps_SclkDeepSleep) &&
	    data->registry_data.sclk_deep_sleep_support) अणु
		data->smu_features[GNLD_DS_GFXCLK].supported = true;
		data->smu_features[GNLD_DS_SOCCLK].supported = true;
		data->smu_features[GNLD_DS_LCLK].supported = true;
		data->smu_features[GNLD_DS_DCEFCLK].supported = true;
	पूर्ण

	अगर (data->registry_data.enable_pkg_pwr_tracking_feature)
		data->smu_features[GNLD_PPT].supported = true;

	अगर (data->registry_data.enable_tdc_limit_feature)
		data->smu_features[GNLD_TDC].supported = true;

	अगर (data->registry_data.thermal_support)
		data->smu_features[GNLD_THERMAL].supported = true;

	अगर (data->registry_data.fan_control_support)
		data->smu_features[GNLD_FAN_CONTROL].supported = true;

	अगर (data->registry_data.fw_ctf_enabled)
		data->smu_features[GNLD_FW_CTF].supported = true;

	अगर (data->registry_data.avfs_support)
		data->smu_features[GNLD_AVFS].supported = true;

	अगर (data->registry_data.led_dpm_enabled)
		data->smu_features[GNLD_LED_DISPLAY].supported = true;

	अगर (data->registry_data.vr1hot_enabled)
		data->smu_features[GNLD_VR1HOT].supported = true;

	अगर (data->registry_data.vr0hot_enabled)
		data->smu_features[GNLD_VR0HOT].supported = true;

	smum_send_msg_to_smc(hwmgr,
			PPSMC_MSG_GetSmuVersion,
			&hwmgr->smu_version);
		/* ACG firmware has major version 5 */
	अगर ((hwmgr->smu_version & 0xff000000) == 0x5000000)
		data->smu_features[GNLD_ACG].supported = true;
	अगर (data->registry_data.didt_support)
		data->smu_features[GNLD_DIDT].supported = true;

	hw_revision = adev->pdev->revision;
	sub_venकरोr_id = adev->pdev->subप्रणाली_venकरोr;

	अगर ((hwmgr->chip_id == 0x6862 ||
		hwmgr->chip_id == 0x6861 ||
		hwmgr->chip_id == 0x6868) &&
		(hw_revision == 0) &&
		(sub_venकरोr_id != 0x1002))
		data->smu_features[GNLD_PCC_LIMIT].supported = true;

	/* Get the SN to turn पूर्णांकo a Unique ID */
	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ReadSerialNumTop32, &top32);
	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ReadSerialNumBottom32, &bottom32);

	adev->unique_id = ((uपूर्णांक64_t)bottom32 << 32) | top32;
पूर्ण

#अगर_घोषित PPLIB_VEGA10_EVV_SUPPORT
अटल पूर्णांक vega10_get_socclk_क्रम_voltage_evv(काष्ठा pp_hwmgr *hwmgr,
	phm_ppt_v1_voltage_lookup_table *lookup_table,
	uपूर्णांक16_t भव_voltage_id, पूर्णांक32_t *socclk)
अणु
	uपूर्णांक8_t entry_id;
	uपूर्णांक8_t voltage_id;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);

	PP_ASSERT_WITH_CODE(lookup_table->count != 0,
			"Lookup table is empty",
			वापस -EINVAL);

	/* search क्रम leakage voltage ID 0xff01 ~ 0xff08 and sclk */
	क्रम (entry_id = 0; entry_id < table_info->vdd_dep_on_sclk->count; entry_id++) अणु
		voltage_id = table_info->vdd_dep_on_socclk->entries[entry_id].vddInd;
		अगर (lookup_table->entries[voltage_id].us_vdd == भव_voltage_id)
			अवरोध;
	पूर्ण

	PP_ASSERT_WITH_CODE(entry_id < table_info->vdd_dep_on_socclk->count,
			"Can't find requested voltage id in vdd_dep_on_socclk table!",
			वापस -EINVAL);

	*socclk = table_info->vdd_dep_on_socclk->entries[entry_id].clk;

	वापस 0;
पूर्ण

#घोषणा ATOM_VIRTUAL_VOLTAGE_ID0             0xff01
/**
 * Get Leakage VDDC based on leakage ID.
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * वापस:  always 0.
 */
अटल पूर्णांक vega10_get_evv_voltages(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	uपूर्णांक16_t vv_id;
	uपूर्णांक32_t vddc = 0;
	uपूर्णांक16_t i, j;
	uपूर्णांक32_t sclk = 0;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *socclk_table =
			table_info->vdd_dep_on_socclk;
	पूर्णांक result;

	क्रम (i = 0; i < VEGA10_MAX_LEAKAGE_COUNT; i++) अणु
		vv_id = ATOM_VIRTUAL_VOLTAGE_ID0 + i;

		अगर (!vega10_get_socclk_क्रम_voltage_evv(hwmgr,
				table_info->vddc_lookup_table, vv_id, &sclk)) अणु
			अगर (PP_CAP(PHM_Platक्रमmCaps_ClockStretcher)) अणु
				क्रम (j = 1; j < socclk_table->count; j++) अणु
					अगर (socclk_table->entries[j].clk == sclk &&
							socclk_table->entries[j].cks_enable == 0) अणु
						sclk += 5000;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			PP_ASSERT_WITH_CODE(!atomctrl_get_voltage_evv_on_sclk_ai(hwmgr,
					VOLTAGE_TYPE_VDDC, sclk, vv_id, &vddc),
					"Error retrieving EVV voltage value!",
					जारी);


			/* need to make sure vddc is less than 2v or अन्यथा, it could burn the ASIC. */
			PP_ASSERT_WITH_CODE((vddc < 2000 && vddc != 0),
					"Invalid VDDC value", result = -EINVAL;);

			/* the voltage should not be zero nor equal to leakage ID */
			अगर (vddc != 0 && vddc != vv_id) अणु
				data->vddc_leakage.actual_voltage[data->vddc_leakage.count] = (uपूर्णांक16_t)(vddc/100);
				data->vddc_leakage.leakage_id[data->vddc_leakage.count] = vv_id;
				data->vddc_leakage.count++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * Change भव leakage voltage to actual value.
 *
 * @hwmgr:         the address of the घातerplay hardware manager.
 * @voltage:       poपूर्णांकer to changing voltage
 * @leakage_table: poपूर्णांकer to leakage table
 */
अटल व्योम vega10_patch_with_vdd_leakage(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक16_t *voltage, काष्ठा vega10_leakage_voltage *leakage_table)
अणु
	uपूर्णांक32_t index;

	/* search क्रम leakage voltage ID 0xff01 ~ 0xff08 */
	क्रम (index = 0; index < leakage_table->count; index++) अणु
		/* अगर this voltage matches a leakage voltage ID */
		/* patch with actual leakage voltage */
		अगर (leakage_table->leakage_id[index] == *voltage) अणु
			*voltage = leakage_table->actual_voltage[index];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (*voltage > ATOM_VIRTUAL_VOLTAGE_ID0)
		pr_info("Voltage value looks like a Leakage ID but it's not patched\n");
पूर्ण

/**
 * Patch voltage lookup table by EVV leakages.
 *
 * @hwmgr:         the address of the घातerplay hardware manager.
 * @lookup_table:  poपूर्णांकer to voltage lookup table
 * @leakage_table: poपूर्णांकer to leakage table
 * वापस:         always 0
 */
अटल पूर्णांक vega10_patch_lookup_table_with_leakage(काष्ठा pp_hwmgr *hwmgr,
		phm_ppt_v1_voltage_lookup_table *lookup_table,
		काष्ठा vega10_leakage_voltage *leakage_table)
अणु
	uपूर्णांक32_t i;

	क्रम (i = 0; i < lookup_table->count; i++)
		vega10_patch_with_vdd_leakage(hwmgr,
				&lookup_table->entries[i].us_vdd, leakage_table);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_patch_घड़ी_voltage_limits_with_vddc_leakage(
		काष्ठा pp_hwmgr *hwmgr, काष्ठा vega10_leakage_voltage *leakage_table,
		uपूर्णांक16_t *vddc)
अणु
	vega10_patch_with_vdd_leakage(hwmgr, (uपूर्णांक16_t *)vddc, leakage_table);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक vega10_patch_voltage_dependency_tables_with_lookup_table(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक8_t entry_id, voltage_id;
	अचिन्हित i;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_table =
			table_info->mm_dep_table;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *mclk_table =
			table_info->vdd_dep_on_mclk;

	क्रम (i = 0; i < 6; i++) अणु
		काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vdt;
		चयन (i) अणु
			हाल 0: vdt = table_info->vdd_dep_on_socclk; अवरोध;
			हाल 1: vdt = table_info->vdd_dep_on_sclk; अवरोध;
			हाल 2: vdt = table_info->vdd_dep_on_dcefclk; अवरोध;
			हाल 3: vdt = table_info->vdd_dep_on_pixclk; अवरोध;
			हाल 4: vdt = table_info->vdd_dep_on_dispclk; अवरोध;
			हाल 5: vdt = table_info->vdd_dep_on_phyclk; अवरोध;
		पूर्ण

		क्रम (entry_id = 0; entry_id < vdt->count; entry_id++) अणु
			voltage_id = vdt->entries[entry_id].vddInd;
			vdt->entries[entry_id].vddc =
					table_info->vddc_lookup_table->entries[voltage_id].us_vdd;
		पूर्ण
	पूर्ण

	क्रम (entry_id = 0; entry_id < mm_table->count; ++entry_id) अणु
		voltage_id = mm_table->entries[entry_id].vddcInd;
		mm_table->entries[entry_id].vddc =
			table_info->vddc_lookup_table->entries[voltage_id].us_vdd;
	पूर्ण

	क्रम (entry_id = 0; entry_id < mclk_table->count; ++entry_id) अणु
		voltage_id = mclk_table->entries[entry_id].vddInd;
		mclk_table->entries[entry_id].vddc =
				table_info->vddc_lookup_table->entries[voltage_id].us_vdd;
		voltage_id = mclk_table->entries[entry_id].vddciInd;
		mclk_table->entries[entry_id].vddci =
				table_info->vddci_lookup_table->entries[voltage_id].us_vdd;
		voltage_id = mclk_table->entries[entry_id].mvddInd;
		mclk_table->entries[entry_id].mvdd =
				table_info->vddmem_lookup_table->entries[voltage_id].us_vdd;
	पूर्ण


	वापस 0;

पूर्ण

अटल पूर्णांक vega10_sort_lookup_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_ppt_v1_voltage_lookup_table *lookup_table)
अणु
	uपूर्णांक32_t table_size, i, j;

	PP_ASSERT_WITH_CODE(lookup_table && lookup_table->count,
		"Lookup table is empty", वापस -EINVAL);

	table_size = lookup_table->count;

	/* Sorting voltages */
	क्रम (i = 0; i < table_size - 1; i++) अणु
		क्रम (j = i + 1; j > 0; j--) अणु
			अगर (lookup_table->entries[j].us_vdd <
					lookup_table->entries[j - 1].us_vdd) अणु
				swap(lookup_table->entries[j - 1],
				     lookup_table->entries[j]);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_complete_dependency_tables(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	पूर्णांक पंचांगp_result;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
#अगर_घोषित PPLIB_VEGA10_EVV_SUPPORT
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	पंचांगp_result = vega10_patch_lookup_table_with_leakage(hwmgr,
			table_info->vddc_lookup_table, &(data->vddc_leakage));
	अगर (पंचांगp_result)
		result = पंचांगp_result;

	पंचांगp_result = vega10_patch_घड़ी_voltage_limits_with_vddc_leakage(hwmgr,
			&(data->vddc_leakage), &table_info->max_घड़ी_voltage_on_dc.vddc);
	अगर (पंचांगp_result)
		result = पंचांगp_result;
#पूर्ण_अगर

	पंचांगp_result = vega10_patch_voltage_dependency_tables_with_lookup_table(hwmgr);
	अगर (पंचांगp_result)
		result = पंचांगp_result;

	पंचांगp_result = vega10_sort_lookup_table(hwmgr, table_info->vddc_lookup_table);
	अगर (पंचांगp_result)
		result = पंचांगp_result;

	वापस result;
पूर्ण

अटल पूर्णांक vega10_set_निजी_data_based_on_pptable(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *allowed_sclk_vdd_table =
			table_info->vdd_dep_on_socclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *allowed_mclk_vdd_table =
			table_info->vdd_dep_on_mclk;

	PP_ASSERT_WITH_CODE(allowed_sclk_vdd_table,
		"VDD dependency on SCLK table is missing. This table is mandatory", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(allowed_sclk_vdd_table->count >= 1,
		"VDD dependency on SCLK table is empty. This table is mandatory", वापस -EINVAL);

	PP_ASSERT_WITH_CODE(allowed_mclk_vdd_table,
		"VDD dependency on MCLK table is missing.  This table is mandatory", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(allowed_mclk_vdd_table->count >= 1,
		"VDD dependency on MCLK table is empty.  This table is mandatory", वापस -EINVAL);

	table_info->max_घड़ी_voltage_on_ac.sclk =
		allowed_sclk_vdd_table->entries[allowed_sclk_vdd_table->count - 1].clk;
	table_info->max_घड़ी_voltage_on_ac.mclk =
		allowed_mclk_vdd_table->entries[allowed_mclk_vdd_table->count - 1].clk;
	table_info->max_घड़ी_voltage_on_ac.vddc =
		allowed_sclk_vdd_table->entries[allowed_sclk_vdd_table->count - 1].vddc;
	table_info->max_घड़ी_voltage_on_ac.vddci =
		allowed_mclk_vdd_table->entries[allowed_mclk_vdd_table->count - 1].vddci;

	hwmgr->dyn_state.max_घड़ी_voltage_on_ac.sclk =
		table_info->max_घड़ी_voltage_on_ac.sclk;
	hwmgr->dyn_state.max_घड़ी_voltage_on_ac.mclk =
		table_info->max_घड़ी_voltage_on_ac.mclk;
	hwmgr->dyn_state.max_घड़ी_voltage_on_ac.vddc =
		table_info->max_घड़ी_voltage_on_ac.vddc;
	hwmgr->dyn_state.max_घड़ी_voltage_on_ac.vddci =
		table_info->max_घड़ी_voltage_on_ac.vddci;

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_hwmgr_backend_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	kमुक्त(hwmgr->dyn_state.vddc_dep_on_dal_pwrl);
	hwmgr->dyn_state.vddc_dep_on_dal_pwrl = शून्य;

	kमुक्त(hwmgr->backend);
	hwmgr->backend = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_hwmgr_backend_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	काष्ठा vega10_hwmgr *data;
	uपूर्णांक32_t config_telemetry = 0;
	काष्ठा pp_atomfwctrl_voltage_table vol_table;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	data = kzalloc(माप(काष्ठा vega10_hwmgr), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	hwmgr->backend = data;

	hwmgr->workload_mask = 1 << hwmgr->workload_prority[PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT];
	hwmgr->घातer_profile_mode = PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT;
	hwmgr->शेष_घातer_profile_mode = PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT;

	vega10_set_शेष_registry_data(hwmgr);
	data->disable_dpm_mask = 0xff;

	/* need to set voltage control types beक्रमe EVV patching */
	data->vddc_control = VEGA10_VOLTAGE_CONTROL_NONE;
	data->mvdd_control = VEGA10_VOLTAGE_CONTROL_NONE;
	data->vddci_control = VEGA10_VOLTAGE_CONTROL_NONE;

	/* VDDCR_SOC */
	अगर (pp_atomfwctrl_is_voltage_controlled_by_gpio_v4(hwmgr,
			VOLTAGE_TYPE_VDDC, VOLTAGE_OBJ_SVID2)) अणु
		अगर (!pp_atomfwctrl_get_voltage_table_v4(hwmgr,
				VOLTAGE_TYPE_VDDC, VOLTAGE_OBJ_SVID2,
				&vol_table)) अणु
			config_telemetry = ((vol_table.telemetry_slope << 8) & 0xff00) |
					(vol_table.telemetry_offset & 0xff);
			data->vddc_control = VEGA10_VOLTAGE_CONTROL_BY_SVID2;
		पूर्ण
	पूर्ण अन्यथा अणु
		kमुक्त(hwmgr->backend);
		hwmgr->backend = शून्य;
		PP_ASSERT_WITH_CODE(false,
				"VDDCR_SOC is not SVID2!",
				वापस -1);
	पूर्ण

	/* MVDDC */
	अगर (pp_atomfwctrl_is_voltage_controlled_by_gpio_v4(hwmgr,
			VOLTAGE_TYPE_MVDDC, VOLTAGE_OBJ_SVID2)) अणु
		अगर (!pp_atomfwctrl_get_voltage_table_v4(hwmgr,
				VOLTAGE_TYPE_MVDDC, VOLTAGE_OBJ_SVID2,
				&vol_table)) अणु
			config_telemetry |=
					((vol_table.telemetry_slope << 24) & 0xff000000) |
					((vol_table.telemetry_offset << 16) & 0xff0000);
			data->mvdd_control = VEGA10_VOLTAGE_CONTROL_BY_SVID2;
		पूर्ण
	पूर्ण

	 /* VDDCI_MEM */
	अगर (PP_CAP(PHM_Platक्रमmCaps_ControlVDDCI)) अणु
		अगर (pp_atomfwctrl_is_voltage_controlled_by_gpio_v4(hwmgr,
				VOLTAGE_TYPE_VDDCI, VOLTAGE_OBJ_GPIO_LUT))
			data->vddci_control = VEGA10_VOLTAGE_CONTROL_BY_GPIO;
	पूर्ण

	data->config_telemetry = config_telemetry;

	vega10_set_features_platक्रमm_caps(hwmgr);

	vega10_init_dpm_शेषs(hwmgr);

#अगर_घोषित PPLIB_VEGA10_EVV_SUPPORT
	/* Get leakage voltage based on leakage ID. */
	PP_ASSERT_WITH_CODE(!vega10_get_evv_voltages(hwmgr),
			"Get EVV Voltage Failed.  Abort Driver loading!",
			वापस -1);
#पूर्ण_अगर

	/* Patch our voltage dependency table with actual leakage voltage
	 * We need to perक्रमm leakage translation beक्रमe it's used by other functions
	 */
	vega10_complete_dependency_tables(hwmgr);

	/* Parse pptable data पढ़ो from VBIOS */
	vega10_set_निजी_data_based_on_pptable(hwmgr);

	data->is_tlu_enabled = false;

	hwmgr->platक्रमm_descriptor.hardwareActivityPerक्रमmanceLevels =
			VEGA10_MAX_HARDWARE_POWERLEVELS;
	hwmgr->platक्रमm_descriptor.hardwarePerक्रमmanceLevels = 2;
	hwmgr->platक्रमm_descriptor.minimumClocksReductionPercentage = 50;

	hwmgr->platक्रमm_descriptor.vbiosInterruptId = 0x20000400; /* IRQ_SOURCE1_SW_INT */
	/* The true घड़ी step depends on the frequency, typically 4.5 or 9 MHz. Here we use 5. */
	hwmgr->platक्रमm_descriptor.घड़ीStep.engineClock = 500;
	hwmgr->platक्रमm_descriptor.घड़ीStep.memoryClock = 500;

	data->total_active_cus = adev->gfx.cu_info.number;
	अगर (!hwmgr->not_vf)
		वापस result;

	/* Setup शेष Overdrive Fan control settings */
	data->odn_fan_table.target_fan_speed =
			hwmgr->thermal_controller.advanceFanControlParameters.usMaxFanRPM;
	data->odn_fan_table.target_temperature =
			hwmgr->thermal_controller.
			advanceFanControlParameters.ucTargetTemperature;
	data->odn_fan_table.min_perक्रमmance_घड़ी =
			hwmgr->thermal_controller.advanceFanControlParameters.
			ulMinFanSCLKAcousticLimit;
	data->odn_fan_table.min_fan_limit =
			hwmgr->thermal_controller.
			advanceFanControlParameters.usFanPWMMinLimit *
			hwmgr->thermal_controller.fanInfo.ulMaxRPM / 100;

	data->mem_channels = (RREG32_SOC15(DF, 0, mmDF_CS_AON0_DramBaseAddress0) &
			DF_CS_AON0_DramBaseAddress0__IntLvNumChan_MASK) >>
			DF_CS_AON0_DramBaseAddress0__IntLvNumChan__SHIFT;
	PP_ASSERT_WITH_CODE(data->mem_channels < ARRAY_SIZE(channel_number),
			"Mem Channel Index Exceeded maximum!",
			वापस -EINVAL);

	वापस result;
पूर्ण

अटल पूर्णांक vega10_init_sclk_threshold(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	data->low_sclk_पूर्णांकerrupt_threshold = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_setup_dpm_led_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);

	काष्ठा pp_atomfwctrl_voltage_table table;
	uपूर्णांक8_t i, j;
	uपूर्णांक32_t mask = 0;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक32_t ret = 0;

	ret = pp_atomfwctrl_get_voltage_table_v4(hwmgr, VOLTAGE_TYPE_LEDDPM,
						VOLTAGE_OBJ_GPIO_LUT, &table);

	अगर (!ret) अणु
		पंचांगp = table.mask_low;
		क्रम (i = 0, j = 0; i < 32; i++) अणु
			अगर (पंचांगp & 1) अणु
				mask |= (uपूर्णांक32_t)(i << (8 * j));
				अगर (++j >= 3)
					अवरोध;
			पूर्ण
			पंचांगp >>= 1;
		पूर्ण
	पूर्ण

	pp_table->LedPin0 = (uपूर्णांक8_t)(mask & 0xff);
	pp_table->LedPin1 = (uपूर्णांक8_t)((mask >> 8) & 0xff);
	pp_table->LedPin2 = (uपूर्णांक8_t)((mask >> 16) & 0xff);
	वापस 0;
पूर्ण

अटल पूर्णांक vega10_setup_asic_task(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (!hwmgr->not_vf)
		वापस 0;

	PP_ASSERT_WITH_CODE(!vega10_init_sclk_threshold(hwmgr),
			"Failed to init sclk threshold!",
			वापस -EINVAL);

	PP_ASSERT_WITH_CODE(!vega10_setup_dpm_led_config(hwmgr),
			"Failed to set up led dpm config!",
			वापस -EINVAL);

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_NumOfDisplays,
				0,
				शून्य);

	वापस 0;
पूर्ण

/**
 * Remove repeated voltage values and create table with unique values.
 *
 * @hwmgr:      the address of the घातerplay hardware manager.
 * @vol_table:  the poपूर्णांकer to changing voltage table
 * वापस:      0 in success
 */
अटल पूर्णांक vega10_trim_voltage_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_atomfwctrl_voltage_table *vol_table)
अणु
	uपूर्णांक32_t i, j;
	uपूर्णांक16_t vvalue;
	bool found = false;
	काष्ठा pp_atomfwctrl_voltage_table *table;

	PP_ASSERT_WITH_CODE(vol_table,
			"Voltage Table empty.", वापस -EINVAL);
	table = kzalloc(माप(काष्ठा pp_atomfwctrl_voltage_table),
			GFP_KERNEL);

	अगर (!table)
		वापस -ENOMEM;

	table->mask_low = vol_table->mask_low;
	table->phase_delay = vol_table->phase_delay;

	क्रम (i = 0; i < vol_table->count; i++) अणु
		vvalue = vol_table->entries[i].value;
		found = false;

		क्रम (j = 0; j < table->count; j++) अणु
			अगर (vvalue == table->entries[j].value) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			table->entries[table->count].value = vvalue;
			table->entries[table->count].smio_low =
					vol_table->entries[i].smio_low;
			table->count++;
		पूर्ण
	पूर्ण

	स_नकल(vol_table, table, माप(काष्ठा pp_atomfwctrl_voltage_table));
	kमुक्त(table);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_get_mvdd_voltage_table(काष्ठा pp_hwmgr *hwmgr,
		phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table,
		काष्ठा pp_atomfwctrl_voltage_table *vol_table)
अणु
	पूर्णांक i;

	PP_ASSERT_WITH_CODE(dep_table->count,
			"Voltage Dependency Table empty.",
			वापस -EINVAL);

	vol_table->mask_low = 0;
	vol_table->phase_delay = 0;
	vol_table->count = dep_table->count;

	क्रम (i = 0; i < vol_table->count; i++) अणु
		vol_table->entries[i].value = dep_table->entries[i].mvdd;
		vol_table->entries[i].smio_low = 0;
	पूर्ण

	PP_ASSERT_WITH_CODE(!vega10_trim_voltage_table(hwmgr,
			vol_table),
			"Failed to trim MVDD Table!",
			वापस -1);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_get_vddci_voltage_table(काष्ठा pp_hwmgr *hwmgr,
		phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table,
		काष्ठा pp_atomfwctrl_voltage_table *vol_table)
अणु
	uपूर्णांक32_t i;

	PP_ASSERT_WITH_CODE(dep_table->count,
			"Voltage Dependency Table empty.",
			वापस -EINVAL);

	vol_table->mask_low = 0;
	vol_table->phase_delay = 0;
	vol_table->count = dep_table->count;

	क्रम (i = 0; i < dep_table->count; i++) अणु
		vol_table->entries[i].value = dep_table->entries[i].vddci;
		vol_table->entries[i].smio_low = 0;
	पूर्ण

	PP_ASSERT_WITH_CODE(!vega10_trim_voltage_table(hwmgr, vol_table),
			"Failed to trim VDDCI table.",
			वापस -1);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_get_vdd_voltage_table(काष्ठा pp_hwmgr *hwmgr,
		phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table,
		काष्ठा pp_atomfwctrl_voltage_table *vol_table)
अणु
	पूर्णांक i;

	PP_ASSERT_WITH_CODE(dep_table->count,
			"Voltage Dependency Table empty.",
			वापस -EINVAL);

	vol_table->mask_low = 0;
	vol_table->phase_delay = 0;
	vol_table->count = dep_table->count;

	क्रम (i = 0; i < vol_table->count; i++) अणु
		vol_table->entries[i].value = dep_table->entries[i].vddc;
		vol_table->entries[i].smio_low = 0;
	पूर्ण

	वापस 0;
पूर्ण

/* ---- Voltage Tables ----
 * If the voltage table would be bigger than
 * what will fit पूर्णांकo the state table on
 * the SMC keep only the higher entries.
 */
अटल व्योम vega10_trim_voltage_table_to_fit_state_table(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t max_vol_steps,
		काष्ठा pp_atomfwctrl_voltage_table *vol_table)
अणु
	अचिन्हित पूर्णांक i, dअगरf;

	अगर (vol_table->count <= max_vol_steps)
		वापस;

	dअगरf = vol_table->count - max_vol_steps;

	क्रम (i = 0; i < max_vol_steps; i++)
		vol_table->entries[i] = vol_table->entries[i + dअगरf];

	vol_table->count = max_vol_steps;
पूर्ण

/**
 * Create Voltage Tables.
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * वापस:  always 0
 */
अटल पूर्णांक vega10_स्थिरruct_voltage_tables(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)hwmgr->pptable;
	पूर्णांक result;

	अगर (data->mvdd_control == VEGA10_VOLTAGE_CONTROL_BY_SVID2 ||
			data->mvdd_control == VEGA10_VOLTAGE_CONTROL_NONE) अणु
		result = vega10_get_mvdd_voltage_table(hwmgr,
				table_info->vdd_dep_on_mclk,
				&(data->mvdd_voltage_table));
		PP_ASSERT_WITH_CODE(!result,
				"Failed to retrieve MVDDC table!",
				वापस result);
	पूर्ण

	अगर (data->vddci_control == VEGA10_VOLTAGE_CONTROL_NONE) अणु
		result = vega10_get_vddci_voltage_table(hwmgr,
				table_info->vdd_dep_on_mclk,
				&(data->vddci_voltage_table));
		PP_ASSERT_WITH_CODE(!result,
				"Failed to retrieve VDDCI_MEM table!",
				वापस result);
	पूर्ण

	अगर (data->vddc_control == VEGA10_VOLTAGE_CONTROL_BY_SVID2 ||
			data->vddc_control == VEGA10_VOLTAGE_CONTROL_NONE) अणु
		result = vega10_get_vdd_voltage_table(hwmgr,
				table_info->vdd_dep_on_sclk,
				&(data->vddc_voltage_table));
		PP_ASSERT_WITH_CODE(!result,
				"Failed to retrieve VDDCR_SOC table!",
				वापस result);
	पूर्ण

	PP_ASSERT_WITH_CODE(data->vddc_voltage_table.count <= 16,
			"Too many voltage values for VDDC. Trimming to fit state table.",
			vega10_trim_voltage_table_to_fit_state_table(hwmgr,
					16, &(data->vddc_voltage_table)));

	PP_ASSERT_WITH_CODE(data->vddci_voltage_table.count <= 16,
			"Too many voltage values for VDDCI. Trimming to fit state table.",
			vega10_trim_voltage_table_to_fit_state_table(hwmgr,
					16, &(data->vddci_voltage_table)));

	PP_ASSERT_WITH_CODE(data->mvdd_voltage_table.count <= 16,
			"Too many voltage values for MVDD. Trimming to fit state table.",
			vega10_trim_voltage_table_to_fit_state_table(hwmgr,
					16, &(data->mvdd_voltage_table)));


	वापस 0;
पूर्ण

/*
 * vega10_init_dpm_state
 * Function to initialize all Soft Min/Max and Hard Min/Max to 0xff.
 *
 * @dpm_state: - the address of the DPM Table to initiailize.
 * वापस:   None.
 */
अटल व्योम vega10_init_dpm_state(काष्ठा vega10_dpm_state *dpm_state)
अणु
	dpm_state->soft_min_level = 0xff;
	dpm_state->soft_max_level = 0xff;
	dpm_state->hard_min_level = 0xff;
	dpm_state->hard_max_level = 0xff;
पूर्ण

अटल व्योम vega10_setup_शेष_single_dpm_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा vega10_single_dpm_table *dpm_table,
		काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table)
अणु
	पूर्णांक i;

	dpm_table->count = 0;

	क्रम (i = 0; i < dep_table->count; i++) अणु
		अगर (i == 0 || dpm_table->dpm_levels[dpm_table->count - 1].value <=
				dep_table->entries[i].clk) अणु
			dpm_table->dpm_levels[dpm_table->count].value =
					dep_table->entries[i].clk;
			dpm_table->dpm_levels[dpm_table->count].enabled = true;
			dpm_table->count++;
		पूर्ण
	पूर्ण
पूर्ण
अटल पूर्णांक vega10_setup_शेष_pcie_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा vega10_pcie_table *pcie_table = &(data->dpm_table.pcie_table);
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_pcie_table *bios_pcie_table =
			table_info->pcie_table;
	uपूर्णांक32_t i;

	PP_ASSERT_WITH_CODE(bios_pcie_table->count,
			"Incorrect number of PCIE States from VBIOS!",
			वापस -1);

	क्रम (i = 0; i < NUM_LINK_LEVELS; i++) अणु
		अगर (data->registry_data.pcieSpeedOverride)
			pcie_table->pcie_gen[i] =
					data->registry_data.pcieSpeedOverride;
		अन्यथा
			pcie_table->pcie_gen[i] =
					bios_pcie_table->entries[i].gen_speed;

		अगर (data->registry_data.pcieLaneOverride)
			pcie_table->pcie_lane[i] = (uपूर्णांक8_t)encode_pcie_lane_width(
					data->registry_data.pcieLaneOverride);
		अन्यथा
			pcie_table->pcie_lane[i] = (uपूर्णांक8_t)encode_pcie_lane_width(
							bios_pcie_table->entries[i].lane_width);
		अगर (data->registry_data.pcieClockOverride)
			pcie_table->lclk[i] =
					data->registry_data.pcieClockOverride;
		अन्यथा
			pcie_table->lclk[i] =
					bios_pcie_table->entries[i].pcie_sclk;
	पूर्ण

	pcie_table->count = NUM_LINK_LEVELS;

	वापस 0;
पूर्ण

/*
 * This function is to initialize all DPM state tables
 * क्रम SMU based on the dependency table.
 * Dynamic state patching function will then trim these
 * state tables to the allowed range based
 * on the घातer policy or बाह्यal client requests,
 * such as UVD request, etc.
 */
अटल पूर्णांक vega10_setup_शेष_dpm_tables(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा vega10_single_dpm_table *dpm_table;
	uपूर्णांक32_t i;

	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_soc_table =
			table_info->vdd_dep_on_socclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_gfx_table =
			table_info->vdd_dep_on_sclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_mclk_table =
			table_info->vdd_dep_on_mclk;
	काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table *dep_mm_table =
			table_info->mm_dep_table;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_dcef_table =
			table_info->vdd_dep_on_dcefclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_pix_table =
			table_info->vdd_dep_on_pixclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_disp_table =
			table_info->vdd_dep_on_dispclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_phy_table =
			table_info->vdd_dep_on_phyclk;

	PP_ASSERT_WITH_CODE(dep_soc_table,
			"SOCCLK dependency table is missing. This table is mandatory",
			वापस -EINVAL);
	PP_ASSERT_WITH_CODE(dep_soc_table->count >= 1,
			"SOCCLK dependency table is empty. This table is mandatory",
			वापस -EINVAL);

	PP_ASSERT_WITH_CODE(dep_gfx_table,
			"GFXCLK dependency table is missing. This table is mandatory",
			वापस -EINVAL);
	PP_ASSERT_WITH_CODE(dep_gfx_table->count >= 1,
			"GFXCLK dependency table is empty. This table is mandatory",
			वापस -EINVAL);

	PP_ASSERT_WITH_CODE(dep_mclk_table,
			"MCLK dependency table is missing. This table is mandatory",
			वापस -EINVAL);
	PP_ASSERT_WITH_CODE(dep_mclk_table->count >= 1,
			"MCLK dependency table has to have is missing. This table is mandatory",
			वापस -EINVAL);

	/* Initialize Sclk DPM table based on allow Sclk values */
	dpm_table = &(data->dpm_table.soc_table);
	vega10_setup_शेष_single_dpm_table(hwmgr,
			dpm_table,
			dep_soc_table);

	vega10_init_dpm_state(&(dpm_table->dpm_state));

	dpm_table = &(data->dpm_table.gfx_table);
	vega10_setup_शेष_single_dpm_table(hwmgr,
			dpm_table,
			dep_gfx_table);
	अगर (hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock == 0)
		hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock =
					dpm_table->dpm_levels[dpm_table->count-1].value;
	vega10_init_dpm_state(&(dpm_table->dpm_state));

	/* Initialize Mclk DPM table based on allow Mclk values */
	data->dpm_table.mem_table.count = 0;
	dpm_table = &(data->dpm_table.mem_table);
	vega10_setup_शेष_single_dpm_table(hwmgr,
			dpm_table,
			dep_mclk_table);
	अगर (hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock == 0)
		hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock =
					dpm_table->dpm_levels[dpm_table->count-1].value;
	vega10_init_dpm_state(&(dpm_table->dpm_state));

	data->dpm_table.eclk_table.count = 0;
	dpm_table = &(data->dpm_table.eclk_table);
	क्रम (i = 0; i < dep_mm_table->count; i++) अणु
		अगर (i == 0 || dpm_table->dpm_levels
				[dpm_table->count - 1].value <=
						dep_mm_table->entries[i].eclk) अणु
			dpm_table->dpm_levels[dpm_table->count].value =
					dep_mm_table->entries[i].eclk;
			dpm_table->dpm_levels[dpm_table->count].enabled =
					(i == 0) ? true : false;
			dpm_table->count++;
		पूर्ण
	पूर्ण
	vega10_init_dpm_state(&(dpm_table->dpm_state));

	data->dpm_table.vclk_table.count = 0;
	data->dpm_table.dclk_table.count = 0;
	dpm_table = &(data->dpm_table.vclk_table);
	क्रम (i = 0; i < dep_mm_table->count; i++) अणु
		अगर (i == 0 || dpm_table->dpm_levels
				[dpm_table->count - 1].value <=
						dep_mm_table->entries[i].vclk) अणु
			dpm_table->dpm_levels[dpm_table->count].value =
					dep_mm_table->entries[i].vclk;
			dpm_table->dpm_levels[dpm_table->count].enabled =
					(i == 0) ? true : false;
			dpm_table->count++;
		पूर्ण
	पूर्ण
	vega10_init_dpm_state(&(dpm_table->dpm_state));

	dpm_table = &(data->dpm_table.dclk_table);
	क्रम (i = 0; i < dep_mm_table->count; i++) अणु
		अगर (i == 0 || dpm_table->dpm_levels
				[dpm_table->count - 1].value <=
						dep_mm_table->entries[i].dclk) अणु
			dpm_table->dpm_levels[dpm_table->count].value =
					dep_mm_table->entries[i].dclk;
			dpm_table->dpm_levels[dpm_table->count].enabled =
					(i == 0) ? true : false;
			dpm_table->count++;
		पूर्ण
	पूर्ण
	vega10_init_dpm_state(&(dpm_table->dpm_state));

	/* Assume there is no headless Vega10 क्रम now */
	dpm_table = &(data->dpm_table.dcef_table);
	vega10_setup_शेष_single_dpm_table(hwmgr,
			dpm_table,
			dep_dcef_table);

	vega10_init_dpm_state(&(dpm_table->dpm_state));

	dpm_table = &(data->dpm_table.pixel_table);
	vega10_setup_शेष_single_dpm_table(hwmgr,
			dpm_table,
			dep_pix_table);

	vega10_init_dpm_state(&(dpm_table->dpm_state));

	dpm_table = &(data->dpm_table.display_table);
	vega10_setup_शेष_single_dpm_table(hwmgr,
			dpm_table,
			dep_disp_table);

	vega10_init_dpm_state(&(dpm_table->dpm_state));

	dpm_table = &(data->dpm_table.phy_table);
	vega10_setup_शेष_single_dpm_table(hwmgr,
			dpm_table,
			dep_phy_table);

	vega10_init_dpm_state(&(dpm_table->dpm_state));

	vega10_setup_शेष_pcie_table(hwmgr);

	/* Zero out the saved copy of the CUSTOM profile
	 * This will be checked when trying to set the profile
	 * and will require that new values be passed in
	 */
	data->custom_profile_mode[0] = 0;
	data->custom_profile_mode[1] = 0;
	data->custom_profile_mode[2] = 0;
	data->custom_profile_mode[3] = 0;

	/* save a copy of the शेष DPM table */
	स_नकल(&(data->golden_dpm_table), &(data->dpm_table),
			माप(काष्ठा vega10_dpm_table));

	वापस 0;
पूर्ण

/*
 * vega10_populate_ulv_state
 * Function to provide parameters क्रम Utral Low Voltage state to SMC.
 *
 * @hwmgr: - the address of the hardware manager.
 * वापस:   Always 0.
 */
अटल पूर्णांक vega10_populate_ulv_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);

	data->smc_state_table.pp_table.UlvOffsetVid =
			(uपूर्णांक8_t)table_info->us_ulv_voltage_offset;

	data->smc_state_table.pp_table.UlvSmnclkDid =
			(uपूर्णांक8_t)(table_info->us_ulv_smnclk_did);
	data->smc_state_table.pp_table.UlvMp1clkDid =
			(uपूर्णांक8_t)(table_info->us_ulv_mp1clk_did);
	data->smc_state_table.pp_table.UlvGfxclkBypass =
			(uपूर्णांक8_t)(table_info->us_ulv_gfxclk_bypass);
	data->smc_state_table.pp_table.UlvPhaseSheddingPsi0 =
			(uपूर्णांक8_t)(data->vddc_voltage_table.psi0_enable);
	data->smc_state_table.pp_table.UlvPhaseSheddingPsi1 =
			(uपूर्णांक8_t)(data->vddc_voltage_table.psi1_enable);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_populate_single_lclk_level(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t lघड़ी, uपूर्णांक8_t *curr_lclk_did)
अणु
	काष्ठा pp_atomfwctrl_घड़ी_भागiders_soc15 भागiders;

	PP_ASSERT_WITH_CODE(!pp_atomfwctrl_get_gpu_pll_भागiders_vega10(
			hwmgr,
			COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
			lघड़ी, &भागiders),
			"Failed to get LCLK clock settings from VBIOS!",
			वापस -1);

	*curr_lclk_did = भागiders.ulDid;

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_override_pcie_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	काष्ठा vega10_hwmgr *data =
			(काष्ठा vega10_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t pcie_gen = 0, pcie_width = 0;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	पूर्णांक i;

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

	क्रम (i = 0; i < NUM_LINK_LEVELS; i++) अणु
		अगर (pp_table->PcieGenSpeed[i] > pcie_gen)
			pp_table->PcieGenSpeed[i] = pcie_gen;

		अगर (pp_table->PcieLaneCount[i] > pcie_width)
			pp_table->PcieLaneCount[i] = pcie_width;
	पूर्ण

	अगर (data->registry_data.pcie_dpm_key_disabled) अणु
		क्रम (i = 0; i < NUM_LINK_LEVELS; i++) अणु
			pp_table->PcieGenSpeed[i] = pcie_gen;
			pp_table->PcieLaneCount[i] = pcie_width;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_populate_smc_link_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = -1;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा vega10_pcie_table *pcie_table =
			&(data->dpm_table.pcie_table);
	uपूर्णांक32_t i, j;

	क्रम (i = 0; i < pcie_table->count; i++) अणु
		pp_table->PcieGenSpeed[i] = pcie_table->pcie_gen[i];
		pp_table->PcieLaneCount[i] = pcie_table->pcie_lane[i];

		result = vega10_populate_single_lclk_level(hwmgr,
				pcie_table->lclk[i], &(pp_table->LclkDid[i]));
		अगर (result) अणु
			pr_info("Populate LClock Level %d Failed!\n", i);
			वापस result;
		पूर्ण
	पूर्ण

	j = i - 1;
	जबतक (i < NUM_LINK_LEVELS) अणु
		pp_table->PcieGenSpeed[i] = pcie_table->pcie_gen[j];
		pp_table->PcieLaneCount[i] = pcie_table->pcie_lane[j];

		result = vega10_populate_single_lclk_level(hwmgr,
				pcie_table->lclk[j], &(pp_table->LclkDid[i]));
		अगर (result) अणु
			pr_info("Populate LClock Level %d Failed!\n", i);
			वापस result;
		पूर्ण
		i++;
	पूर्ण

	वापस result;
पूर्ण

/**
 * Populates single SMC GFXSCLK काष्ठाure using the provided engine घड़ी
 *
 * @hwmgr:      the address of the hardware manager
 * @gfx_घड़ी:  the GFX घड़ी to use to populate the काष्ठाure.
 * @current_gfxclk_level:  location in PPTable क्रम the SMC GFXCLK काष्ठाure.
 * @acg_freq:   ACG frequenty to वापस (MHz)
 */
अटल पूर्णांक vega10_populate_single_gfx_level(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t gfx_घड़ी, PllSetting_t *current_gfxclk_level,
		uपूर्णांक32_t *acg_freq)
अणु
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_on_sclk;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा pp_atomfwctrl_घड़ी_भागiders_soc15 भागiders;
	uपूर्णांक32_t gfx_max_घड़ी =
			hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock;
	uपूर्णांक32_t i = 0;

	अगर (hwmgr->od_enabled)
		dep_on_sclk = (काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *)
						&(data->odn_dpm_table.vdd_dep_on_sclk);
	अन्यथा
		dep_on_sclk = table_info->vdd_dep_on_sclk;

	PP_ASSERT_WITH_CODE(dep_on_sclk,
			"Invalid SOC_VDD-GFX_CLK Dependency Table!",
			वापस -EINVAL);

	अगर (data->need_update_dpm_table & DPMTABLE_OD_UPDATE_SCLK)
		gfx_घड़ी = gfx_घड़ी > gfx_max_घड़ी ? gfx_max_घड़ी : gfx_घड़ी;
	अन्यथा अणु
		क्रम (i = 0; i < dep_on_sclk->count; i++) अणु
			अगर (dep_on_sclk->entries[i].clk == gfx_घड़ी)
				अवरोध;
		पूर्ण
		PP_ASSERT_WITH_CODE(dep_on_sclk->count > i,
				"Cannot find gfx_clk in SOC_VDD-GFX_CLK!",
				वापस -EINVAL);
	पूर्ण

	PP_ASSERT_WITH_CODE(!pp_atomfwctrl_get_gpu_pll_भागiders_vega10(hwmgr,
			COMPUTE_GPUCLK_INPUT_FLAG_GFXCLK,
			gfx_घड़ी, &भागiders),
			"Failed to get GFX Clock settings from VBIOS!",
			वापस -EINVAL);

	/* Feedback Multiplier: bit 0:8 पूर्णांक, bit 15:12 post_भाग, bit 31:16 frac */
	current_gfxclk_level->FbMult =
			cpu_to_le32(भागiders.ulPll_fb_mult);
	/* Spपढ़ो FB Multiplier bit: bit 0:8 पूर्णांक, bit 31:16 frac */
	current_gfxclk_level->SsOn = भागiders.ucPll_ss_enable;
	current_gfxclk_level->SsFbMult =
			cpu_to_le32(भागiders.ulPll_ss_fbsmult);
	current_gfxclk_level->SsSlewFrac =
			cpu_to_le16(भागiders.usPll_ss_slew_frac);
	current_gfxclk_level->Did = (uपूर्णांक8_t)(भागiders.ulDid);

	*acg_freq = gfx_घड़ी / 100; /* 100 Khz to Mhz conversion */

	वापस 0;
पूर्ण

/**
 * Populates single SMC SOCCLK काष्ठाure using the provided घड़ी.
 *
 * @hwmgr:     the address of the hardware manager.
 * @soc_घड़ी: the SOC घड़ी to use to populate the काष्ठाure.
 * @current_soc_did:   DFS भागider to pass back to caller
 * @current_vol_index: index of current VDD to pass back to caller
 * वापस:      0 on success
 */
अटल पूर्णांक vega10_populate_single_soc_level(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t soc_घड़ी, uपूर्णांक8_t *current_soc_did,
		uपूर्णांक8_t *current_vol_index)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_on_soc;
	काष्ठा pp_atomfwctrl_घड़ी_भागiders_soc15 भागiders;
	uपूर्णांक32_t i;

	अगर (hwmgr->od_enabled) अणु
		dep_on_soc = (काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *)
						&data->odn_dpm_table.vdd_dep_on_socclk;
		क्रम (i = 0; i < dep_on_soc->count; i++) अणु
			अगर (dep_on_soc->entries[i].clk >= soc_घड़ी)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		dep_on_soc = table_info->vdd_dep_on_socclk;
		क्रम (i = 0; i < dep_on_soc->count; i++) अणु
			अगर (dep_on_soc->entries[i].clk == soc_घड़ी)
				अवरोध;
		पूर्ण
	पूर्ण

	PP_ASSERT_WITH_CODE(dep_on_soc->count > i,
			"Cannot find SOC_CLK in SOC_VDD-SOC_CLK Dependency Table",
			वापस -EINVAL);

	PP_ASSERT_WITH_CODE(!pp_atomfwctrl_get_gpu_pll_भागiders_vega10(hwmgr,
			COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
			soc_घड़ी, &भागiders),
			"Failed to get SOC Clock settings from VBIOS!",
			वापस -EINVAL);

	*current_soc_did = (uपूर्णांक8_t)भागiders.ulDid;
	*current_vol_index = (uपूर्णांक8_t)(dep_on_soc->entries[i].vddInd);
	वापस 0;
पूर्ण

/**
 * Populates all SMC SCLK levels' काष्ठाure based on the trimmed allowed dpm engine घड़ी states
 *
 * @hwmgr:      the address of the hardware manager
 */
अटल पूर्णांक vega10_populate_all_graphic_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा vega10_single_dpm_table *dpm_table = &(data->dpm_table.gfx_table);
	पूर्णांक result = 0;
	uपूर्णांक32_t i, j;

	क्रम (i = 0; i < dpm_table->count; i++) अणु
		result = vega10_populate_single_gfx_level(hwmgr,
				dpm_table->dpm_levels[i].value,
				&(pp_table->GfxclkLevel[i]),
				&(pp_table->AcgFreqTable[i]));
		अगर (result)
			वापस result;
	पूर्ण

	j = i - 1;
	जबतक (i < NUM_GFXCLK_DPM_LEVELS) अणु
		result = vega10_populate_single_gfx_level(hwmgr,
				dpm_table->dpm_levels[j].value,
				&(pp_table->GfxclkLevel[i]),
				&(pp_table->AcgFreqTable[i]));
		अगर (result)
			वापस result;
		i++;
	पूर्ण

	pp_table->GfxclkSlewRate =
			cpu_to_le16(table_info->us_gfxclk_slew_rate);

	dpm_table = &(data->dpm_table.soc_table);
	क्रम (i = 0; i < dpm_table->count; i++) अणु
		result = vega10_populate_single_soc_level(hwmgr,
				dpm_table->dpm_levels[i].value,
				&(pp_table->SocclkDid[i]),
				&(pp_table->SocDpmVoltageIndex[i]));
		अगर (result)
			वापस result;
	पूर्ण

	j = i - 1;
	जबतक (i < NUM_SOCCLK_DPM_LEVELS) अणु
		result = vega10_populate_single_soc_level(hwmgr,
				dpm_table->dpm_levels[j].value,
				&(pp_table->SocclkDid[i]),
				&(pp_table->SocDpmVoltageIndex[i]));
		अगर (result)
			वापस result;
		i++;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम vega10_populate_vddc_soc_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा phm_ppt_v2_inक्रमmation *table_info = hwmgr->pptable;
	काष्ठा phm_ppt_v1_voltage_lookup_table *vddc_lookup_table;

	uपूर्णांक8_t soc_vid = 0;
	uपूर्णांक32_t i, max_vddc_level;

	अगर (hwmgr->od_enabled)
		vddc_lookup_table = (काष्ठा phm_ppt_v1_voltage_lookup_table *)&data->odn_dpm_table.vddc_lookup_table;
	अन्यथा
		vddc_lookup_table = table_info->vddc_lookup_table;

	max_vddc_level = vddc_lookup_table->count;
	क्रम (i = 0; i < max_vddc_level; i++) अणु
		soc_vid = (uपूर्णांक8_t)convert_to_vid(vddc_lookup_table->entries[i].us_vdd);
		pp_table->SocVid[i] = soc_vid;
	पूर्ण
	जबतक (i < MAX_REGULAR_DPM_NUMBER) अणु
		pp_table->SocVid[i] = soc_vid;
		i++;
	पूर्ण
पूर्ण

/*
 * Populates single SMC GFXCLK काष्ठाure using the provided घड़ी.
 *
 * @hwmgr:     the address of the hardware manager.
 * @mem_घड़ी: the memory घड़ी to use to populate the काष्ठाure.
 * वापस:     0 on success..
 */
अटल पूर्णांक vega10_populate_single_memory_level(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t mem_घड़ी, uपूर्णांक8_t *current_mem_vid,
		PllSetting_t *current_memclk_level, uपूर्णांक8_t *current_mem_soc_vind)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_on_mclk;
	काष्ठा pp_atomfwctrl_घड़ी_भागiders_soc15 भागiders;
	uपूर्णांक32_t mem_max_घड़ी =
			hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock;
	uपूर्णांक32_t i = 0;

	अगर (hwmgr->od_enabled)
		dep_on_mclk = (काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *)
					&data->odn_dpm_table.vdd_dep_on_mclk;
	अन्यथा
		dep_on_mclk = table_info->vdd_dep_on_mclk;

	PP_ASSERT_WITH_CODE(dep_on_mclk,
			"Invalid SOC_VDD-UCLK Dependency Table!",
			वापस -EINVAL);

	अगर (data->need_update_dpm_table & DPMTABLE_OD_UPDATE_MCLK) अणु
		mem_घड़ी = mem_घड़ी > mem_max_घड़ी ? mem_max_घड़ी : mem_घड़ी;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < dep_on_mclk->count; i++) अणु
			अगर (dep_on_mclk->entries[i].clk == mem_घड़ी)
				अवरोध;
		पूर्ण
		PP_ASSERT_WITH_CODE(dep_on_mclk->count > i,
				"Cannot find UCLK in SOC_VDD-UCLK Dependency Table!",
				वापस -EINVAL);
	पूर्ण

	PP_ASSERT_WITH_CODE(!pp_atomfwctrl_get_gpu_pll_भागiders_vega10(
			hwmgr, COMPUTE_GPUCLK_INPUT_FLAG_UCLK, mem_घड़ी, &भागiders),
			"Failed to get UCLK settings from VBIOS!",
			वापस -1);

	*current_mem_vid =
			(uपूर्णांक8_t)(convert_to_vid(dep_on_mclk->entries[i].mvdd));
	*current_mem_soc_vind =
			(uपूर्णांक8_t)(dep_on_mclk->entries[i].vddInd);
	current_memclk_level->FbMult = cpu_to_le32(भागiders.ulPll_fb_mult);
	current_memclk_level->Did = (uपूर्णांक8_t)(भागiders.ulDid);

	PP_ASSERT_WITH_CODE(current_memclk_level->Did >= 1,
			"Invalid Divider ID!",
			वापस -EINVAL);

	वापस 0;
पूर्ण

/**
 * Populates all SMC MCLK levels' काष्ठाure based on the trimmed allowed dpm memory घड़ी states.
 *
 * @hwmgr:  the address of the hardware manager.
 * वापस:   PP_Result_OK on success.
 */
अटल पूर्णांक vega10_populate_all_memory_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा vega10_single_dpm_table *dpm_table =
			&(data->dpm_table.mem_table);
	पूर्णांक result = 0;
	uपूर्णांक32_t i, j;

	क्रम (i = 0; i < dpm_table->count; i++) अणु
		result = vega10_populate_single_memory_level(hwmgr,
				dpm_table->dpm_levels[i].value,
				&(pp_table->MemVid[i]),
				&(pp_table->UclkLevel[i]),
				&(pp_table->MemSocVoltageIndex[i]));
		अगर (result)
			वापस result;
	पूर्ण

	j = i - 1;
	जबतक (i < NUM_UCLK_DPM_LEVELS) अणु
		result = vega10_populate_single_memory_level(hwmgr,
				dpm_table->dpm_levels[j].value,
				&(pp_table->MemVid[i]),
				&(pp_table->UclkLevel[i]),
				&(pp_table->MemSocVoltageIndex[i]));
		अगर (result)
			वापस result;
		i++;
	पूर्ण

	pp_table->NumMemoryChannels = (uपूर्णांक16_t)(data->mem_channels);
	pp_table->MemoryChannelWidth =
			(uपूर्णांक16_t)(HBM_MEMORY_CHANNEL_WIDTH *
					channel_number[data->mem_channels]);

	pp_table->LowestUclkReservedForUlv =
			(uपूर्णांक8_t)(data->lowest_uclk_reserved_क्रम_ulv);

	वापस result;
पूर्ण

अटल पूर्णांक vega10_populate_single_display_type(काष्ठा pp_hwmgr *hwmgr,
		DSPCLK_e disp_घड़ी)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)
			(hwmgr->pptable);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table;
	uपूर्णांक32_t i;
	uपूर्णांक16_t clk = 0, vddc = 0;
	uपूर्णांक8_t vid = 0;

	चयन (disp_घड़ी) अणु
	हाल DSPCLK_DCEFCLK:
		dep_table = table_info->vdd_dep_on_dcefclk;
		अवरोध;
	हाल DSPCLK_DISPCLK:
		dep_table = table_info->vdd_dep_on_dispclk;
		अवरोध;
	हाल DSPCLK_PIXCLK:
		dep_table = table_info->vdd_dep_on_pixclk;
		अवरोध;
	हाल DSPCLK_PHYCLK:
		dep_table = table_info->vdd_dep_on_phyclk;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	PP_ASSERT_WITH_CODE(dep_table->count <= NUM_DSPCLK_LEVELS,
			"Number Of Entries Exceeded maximum!",
			वापस -1);

	क्रम (i = 0; i < dep_table->count; i++) अणु
		clk = (uपूर्णांक16_t)(dep_table->entries[i].clk / 100);
		vddc = table_info->vddc_lookup_table->
				entries[dep_table->entries[i].vddInd].us_vdd;
		vid = (uपूर्णांक8_t)convert_to_vid(vddc);
		pp_table->DisplayClockTable[disp_घड़ी][i].Freq =
				cpu_to_le16(clk);
		pp_table->DisplayClockTable[disp_घड़ी][i].Vid =
				cpu_to_le16(vid);
	पूर्ण

	जबतक (i < NUM_DSPCLK_LEVELS) अणु
		pp_table->DisplayClockTable[disp_घड़ी][i].Freq =
				cpu_to_le16(clk);
		pp_table->DisplayClockTable[disp_घड़ी][i].Vid =
				cpu_to_le16(vid);
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_populate_all_display_घड़ी_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t i;

	क्रम (i = 0; i < DSPCLK_COUNT; i++) अणु
		PP_ASSERT_WITH_CODE(!vega10_populate_single_display_type(hwmgr, i),
				"Failed to populate Clock in DisplayClockTable!",
				वापस -1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_populate_single_eघड़ी_level(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t eघड़ी, uपूर्णांक8_t *current_eclk_did,
		uपूर्णांक8_t *current_soc_vol)
अणु
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table *dep_table =
			table_info->mm_dep_table;
	काष्ठा pp_atomfwctrl_घड़ी_भागiders_soc15 भागiders;
	uपूर्णांक32_t i;

	PP_ASSERT_WITH_CODE(!pp_atomfwctrl_get_gpu_pll_भागiders_vega10(hwmgr,
			COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
			eघड़ी, &भागiders),
			"Failed to get ECLK clock settings from VBIOS!",
			वापस -1);

	*current_eclk_did = (uपूर्णांक8_t)भागiders.ulDid;

	क्रम (i = 0; i < dep_table->count; i++) अणु
		अगर (dep_table->entries[i].eclk == eघड़ी)
			*current_soc_vol = dep_table->entries[i].vddcInd;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_populate_smc_vce_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा vega10_single_dpm_table *dpm_table = &(data->dpm_table.eclk_table);
	पूर्णांक result = -EINVAL;
	uपूर्णांक32_t i, j;

	क्रम (i = 0; i < dpm_table->count; i++) अणु
		result = vega10_populate_single_eघड़ी_level(hwmgr,
				dpm_table->dpm_levels[i].value,
				&(pp_table->EclkDid[i]),
				&(pp_table->VceDpmVoltageIndex[i]));
		अगर (result)
			वापस result;
	पूर्ण

	j = i - 1;
	जबतक (i < NUM_VCE_DPM_LEVELS) अणु
		result = vega10_populate_single_eघड़ी_level(hwmgr,
				dpm_table->dpm_levels[j].value,
				&(pp_table->EclkDid[i]),
				&(pp_table->VceDpmVoltageIndex[i]));
		अगर (result)
			वापस result;
		i++;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक vega10_populate_single_vघड़ी_level(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t vघड़ी, uपूर्णांक8_t *current_vclk_did)
अणु
	काष्ठा pp_atomfwctrl_घड़ी_भागiders_soc15 भागiders;

	PP_ASSERT_WITH_CODE(!pp_atomfwctrl_get_gpu_pll_भागiders_vega10(hwmgr,
			COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
			vघड़ी, &भागiders),
			"Failed to get VCLK clock settings from VBIOS!",
			वापस -EINVAL);

	*current_vclk_did = (uपूर्णांक8_t)भागiders.ulDid;

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_populate_single_dघड़ी_level(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t dघड़ी, uपूर्णांक8_t *current_dclk_did)
अणु
	काष्ठा pp_atomfwctrl_घड़ी_भागiders_soc15 भागiders;

	PP_ASSERT_WITH_CODE(!pp_atomfwctrl_get_gpu_pll_भागiders_vega10(hwmgr,
			COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
			dघड़ी, &भागiders),
			"Failed to get DCLK clock settings from VBIOS!",
			वापस -EINVAL);

	*current_dclk_did = (uपूर्णांक8_t)भागiders.ulDid;

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_populate_smc_uvd_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा vega10_single_dpm_table *vclk_dpm_table =
			&(data->dpm_table.vclk_table);
	काष्ठा vega10_single_dpm_table *dclk_dpm_table =
			&(data->dpm_table.dclk_table);
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table *dep_table =
			table_info->mm_dep_table;
	पूर्णांक result = -EINVAL;
	uपूर्णांक32_t i, j;

	क्रम (i = 0; i < vclk_dpm_table->count; i++) अणु
		result = vega10_populate_single_vघड़ी_level(hwmgr,
				vclk_dpm_table->dpm_levels[i].value,
				&(pp_table->VclkDid[i]));
		अगर (result)
			वापस result;
	पूर्ण

	j = i - 1;
	जबतक (i < NUM_UVD_DPM_LEVELS) अणु
		result = vega10_populate_single_vघड़ी_level(hwmgr,
				vclk_dpm_table->dpm_levels[j].value,
				&(pp_table->VclkDid[i]));
		अगर (result)
			वापस result;
		i++;
	पूर्ण

	क्रम (i = 0; i < dclk_dpm_table->count; i++) अणु
		result = vega10_populate_single_dघड़ी_level(hwmgr,
				dclk_dpm_table->dpm_levels[i].value,
				&(pp_table->DclkDid[i]));
		अगर (result)
			वापस result;
	पूर्ण

	j = i - 1;
	जबतक (i < NUM_UVD_DPM_LEVELS) अणु
		result = vega10_populate_single_dघड़ी_level(hwmgr,
				dclk_dpm_table->dpm_levels[j].value,
				&(pp_table->DclkDid[i]));
		अगर (result)
			वापस result;
		i++;
	पूर्ण

	क्रम (i = 0; i < dep_table->count; i++) अणु
		अगर (dep_table->entries[i].vclk ==
				vclk_dpm_table->dpm_levels[i].value &&
			dep_table->entries[i].dclk ==
				dclk_dpm_table->dpm_levels[i].value)
			pp_table->UvdDpmVoltageIndex[i] =
					dep_table->entries[i].vddcInd;
		अन्यथा
			वापस -1;
	पूर्ण

	j = i - 1;
	जबतक (i < NUM_UVD_DPM_LEVELS) अणु
		pp_table->UvdDpmVoltageIndex[i] = dep_table->entries[j].vddcInd;
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_populate_घड़ी_stretcher_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table =
			table_info->vdd_dep_on_sclk;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < dep_table->count; i++) अणु
		pp_table->CksEnable[i] = dep_table->entries[i].cks_enable;
		pp_table->CksVidOffset[i] = (uपूर्णांक8_t)(dep_table->entries[i].cks_voffset
				* VOLTAGE_VID_OFFSET_SCALE2 / VOLTAGE_VID_OFFSET_SCALE1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_populate_avfs_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table =
			table_info->vdd_dep_on_sclk;
	काष्ठा pp_atomfwctrl_avfs_parameters avfs_params = अणु0पूर्ण;
	पूर्णांक result = 0;
	uपूर्णांक32_t i;

	pp_table->MinVoltageVid = (uपूर्णांक8_t)0xff;
	pp_table->MaxVoltageVid = (uपूर्णांक8_t)0;

	अगर (data->smu_features[GNLD_AVFS].supported) अणु
		result = pp_atomfwctrl_get_avfs_inक्रमmation(hwmgr, &avfs_params);
		अगर (!result) अणु
			pp_table->MinVoltageVid = (uपूर्णांक8_t)
					convert_to_vid((uपूर्णांक16_t)(avfs_params.ulMinVddc));
			pp_table->MaxVoltageVid = (uपूर्णांक8_t)
					convert_to_vid((uपूर्णांक16_t)(avfs_params.ulMaxVddc));

			pp_table->AConstant[0] = cpu_to_le32(avfs_params.ulMeanNsigmaAcontant0);
			pp_table->AConstant[1] = cpu_to_le32(avfs_params.ulMeanNsigmaAcontant1);
			pp_table->AConstant[2] = cpu_to_le32(avfs_params.ulMeanNsigmaAcontant2);
			pp_table->DC_tol_sigma = cpu_to_le16(avfs_params.usMeanNsigmaDcTolSigma);
			pp_table->Platक्रमm_mean = cpu_to_le16(avfs_params.usMeanNsigmaPlatक्रमmMean);
			pp_table->Platक्रमm_sigma = cpu_to_le16(avfs_params.usMeanNsigmaDcTolSigma);
			pp_table->PSM_Age_CompFactor = cpu_to_le16(avfs_params.usPsmAgeComfactor);

			pp_table->BtcGbVdroopTableCksOff.a0 =
					cpu_to_le32(avfs_params.ulGbVdroopTableCksoffA0);
			pp_table->BtcGbVdroopTableCksOff.a0_shअगरt = 20;
			pp_table->BtcGbVdroopTableCksOff.a1 =
					cpu_to_le32(avfs_params.ulGbVdroopTableCksoffA1);
			pp_table->BtcGbVdroopTableCksOff.a1_shअगरt = 20;
			pp_table->BtcGbVdroopTableCksOff.a2 =
					cpu_to_le32(avfs_params.ulGbVdroopTableCksoffA2);
			pp_table->BtcGbVdroopTableCksOff.a2_shअगरt = 20;

			pp_table->OverrideBtcGbCksOn = avfs_params.ucEnableGbVdroopTableCkson;
			pp_table->BtcGbVdroopTableCksOn.a0 =
					cpu_to_le32(avfs_params.ulGbVdroopTableCksonA0);
			pp_table->BtcGbVdroopTableCksOn.a0_shअगरt = 20;
			pp_table->BtcGbVdroopTableCksOn.a1 =
					cpu_to_le32(avfs_params.ulGbVdroopTableCksonA1);
			pp_table->BtcGbVdroopTableCksOn.a1_shअगरt = 20;
			pp_table->BtcGbVdroopTableCksOn.a2 =
					cpu_to_le32(avfs_params.ulGbVdroopTableCksonA2);
			pp_table->BtcGbVdroopTableCksOn.a2_shअगरt = 20;

			pp_table->AvfsGbCksOn.m1 =
					cpu_to_le32(avfs_params.ulGbFuseTableCksonM1);
			pp_table->AvfsGbCksOn.m2 =
					cpu_to_le32(avfs_params.ulGbFuseTableCksonM2);
			pp_table->AvfsGbCksOn.b =
					cpu_to_le32(avfs_params.ulGbFuseTableCksonB);
			pp_table->AvfsGbCksOn.m1_shअगरt = 24;
			pp_table->AvfsGbCksOn.m2_shअगरt = 12;
			pp_table->AvfsGbCksOn.b_shअगरt = 0;

			pp_table->OverrideAvfsGbCksOn =
					avfs_params.ucEnableGbFuseTableCkson;
			pp_table->AvfsGbCksOff.m1 =
					cpu_to_le32(avfs_params.ulGbFuseTableCksoffM1);
			pp_table->AvfsGbCksOff.m2 =
					cpu_to_le32(avfs_params.ulGbFuseTableCksoffM2);
			pp_table->AvfsGbCksOff.b =
					cpu_to_le32(avfs_params.ulGbFuseTableCksoffB);
			pp_table->AvfsGbCksOff.m1_shअगरt = 24;
			pp_table->AvfsGbCksOff.m2_shअगरt = 12;
			pp_table->AvfsGbCksOff.b_shअगरt = 0;

			क्रम (i = 0; i < dep_table->count; i++)
				pp_table->StaticVoltageOffsetVid[i] =
						convert_to_vid((uपूर्णांक8_t)(dep_table->entries[i].sclk_offset));

			अगर ((PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->disp_clk_quad_eqn_a) &&
				(PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->disp_clk_quad_eqn_b)) अणु
				pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].m1 =
						(पूर्णांक32_t)data->disp_clk_quad_eqn_a;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].m2 =
						(पूर्णांक32_t)data->disp_clk_quad_eqn_b;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].b =
						(पूर्णांक32_t)data->disp_clk_quad_eqn_c;
			पूर्ण अन्यथा अणु
				pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].m1 =
						(पूर्णांक32_t)avfs_params.ulDispclk2GfxclkM1;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].m2 =
						(पूर्णांक32_t)avfs_params.ulDispclk2GfxclkM2;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].b =
						(पूर्णांक32_t)avfs_params.ulDispclk2GfxclkB;
			पूर्ण

			pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].m1_shअगरt = 24;
			pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].m2_shअगरt = 12;
			pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].b_shअगरt = 12;

			अगर ((PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->dcef_clk_quad_eqn_a) &&
				(PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->dcef_clk_quad_eqn_b)) अणु
				pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].m1 =
						(पूर्णांक32_t)data->dcef_clk_quad_eqn_a;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].m2 =
						(पूर्णांक32_t)data->dcef_clk_quad_eqn_b;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].b =
						(पूर्णांक32_t)data->dcef_clk_quad_eqn_c;
			पूर्ण अन्यथा अणु
				pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].m1 =
						(पूर्णांक32_t)avfs_params.ulDcefclk2GfxclkM1;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].m2 =
						(पूर्णांक32_t)avfs_params.ulDcefclk2GfxclkM2;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].b =
						(पूर्णांक32_t)avfs_params.ulDcefclk2GfxclkB;
			पूर्ण

			pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].m1_shअगरt = 24;
			pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].m2_shअगरt = 12;
			pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].b_shअगरt = 12;

			अगर ((PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->pixel_clk_quad_eqn_a) &&
				(PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->pixel_clk_quad_eqn_b)) अणु
				pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].m1 =
						(पूर्णांक32_t)data->pixel_clk_quad_eqn_a;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].m2 =
						(पूर्णांक32_t)data->pixel_clk_quad_eqn_b;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].b =
						(पूर्णांक32_t)data->pixel_clk_quad_eqn_c;
			पूर्ण अन्यथा अणु
				pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].m1 =
						(पूर्णांक32_t)avfs_params.ulPixelclk2GfxclkM1;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].m2 =
						(पूर्णांक32_t)avfs_params.ulPixelclk2GfxclkM2;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].b =
						(पूर्णांक32_t)avfs_params.ulPixelclk2GfxclkB;
			पूर्ण

			pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].m1_shअगरt = 24;
			pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].m2_shअगरt = 12;
			pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].b_shअगरt = 12;
			अगर ((PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->phy_clk_quad_eqn_a) &&
				(PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->phy_clk_quad_eqn_b)) अणु
				pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].m1 =
						(पूर्णांक32_t)data->phy_clk_quad_eqn_a;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].m2 =
						(पूर्णांक32_t)data->phy_clk_quad_eqn_b;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].b =
						(पूर्णांक32_t)data->phy_clk_quad_eqn_c;
			पूर्ण अन्यथा अणु
				pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].m1 =
						(पूर्णांक32_t)avfs_params.ulPhyclk2GfxclkM1;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].m2 =
						(पूर्णांक32_t)avfs_params.ulPhyclk2GfxclkM2;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].b =
						(पूर्णांक32_t)avfs_params.ulPhyclk2GfxclkB;
			पूर्ण

			pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].m1_shअगरt = 24;
			pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].m2_shअगरt = 12;
			pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].b_shअगरt = 12;

			pp_table->AcgBtcGbVdroopTable.a0       = avfs_params.ulAcgGbVdroopTableA0;
			pp_table->AcgBtcGbVdroopTable.a0_shअगरt = 20;
			pp_table->AcgBtcGbVdroopTable.a1       = avfs_params.ulAcgGbVdroopTableA1;
			pp_table->AcgBtcGbVdroopTable.a1_shअगरt = 20;
			pp_table->AcgBtcGbVdroopTable.a2       = avfs_params.ulAcgGbVdroopTableA2;
			pp_table->AcgBtcGbVdroopTable.a2_shअगरt = 20;

			pp_table->AcgAvfsGb.m1                   = avfs_params.ulAcgGbFuseTableM1;
			pp_table->AcgAvfsGb.m2                   = avfs_params.ulAcgGbFuseTableM2;
			pp_table->AcgAvfsGb.b                    = avfs_params.ulAcgGbFuseTableB;
			pp_table->AcgAvfsGb.m1_shअगरt             = 24;
			pp_table->AcgAvfsGb.m2_shअगरt             = 12;
			pp_table->AcgAvfsGb.b_shअगरt              = 0;

		पूर्ण अन्यथा अणु
			data->smu_features[GNLD_AVFS].supported = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_acg_enable(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t agc_btc_response;

	अगर (data->smu_features[GNLD_ACG].supported) अणु
		अगर (0 == vega10_enable_smc_features(hwmgr, true,
					data->smu_features[GNLD_DPM_PREFETCHER].smu_feature_biपंचांगap))
			data->smu_features[GNLD_DPM_PREFETCHER].enabled = true;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_InitializeAcg, शून्य);

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_RunAcgBtc, &agc_btc_response);

		अगर (1 == agc_btc_response) अणु
			अगर (1 == data->acg_loop_state)
				smum_send_msg_to_smc(hwmgr, PPSMC_MSG_RunAcgInClosedLoop, शून्य);
			अन्यथा अगर (2 == data->acg_loop_state)
				smum_send_msg_to_smc(hwmgr, PPSMC_MSG_RunAcgInOpenLoop, शून्य);
			अगर (0 == vega10_enable_smc_features(hwmgr, true,
				data->smu_features[GNLD_ACG].smu_feature_biपंचांगap))
					data->smu_features[GNLD_ACG].enabled = true;
		पूर्ण अन्यथा अणु
			pr_info("[ACG_Enable] ACG BTC Returned Failed Status!\n");
			data->smu_features[GNLD_ACG].enabled = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_acg_disable(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_ACG].supported &&
	    data->smu_features[GNLD_ACG].enabled)
		अगर (!vega10_enable_smc_features(hwmgr, false,
			data->smu_features[GNLD_ACG].smu_feature_biपंचांगap))
			data->smu_features[GNLD_ACG].enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_populate_gpio_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा pp_atomfwctrl_gpio_parameters gpio_params = अणु0पूर्ण;
	पूर्णांक result;

	result = pp_atomfwctrl_get_gpio_inक्रमmation(hwmgr, &gpio_params);
	अगर (!result) अणु
		अगर (PP_CAP(PHM_Platक्रमmCaps_RegulatorHot) &&
		    data->registry_data.regulator_hot_gpio_support) अणु
			pp_table->VR0HotGpio = gpio_params.ucVR0HotGpio;
			pp_table->VR0HotPolarity = gpio_params.ucVR0HotPolarity;
			pp_table->VR1HotGpio = gpio_params.ucVR1HotGpio;
			pp_table->VR1HotPolarity = gpio_params.ucVR1HotPolarity;
		पूर्ण अन्यथा अणु
			pp_table->VR0HotGpio = 0;
			pp_table->VR0HotPolarity = 0;
			pp_table->VR1HotGpio = 0;
			pp_table->VR1HotPolarity = 0;
		पूर्ण

		अगर (PP_CAP(PHM_Platक्रमmCaps_AutomaticDCTransition) &&
		    data->registry_data.ac_dc_चयन_gpio_support) अणु
			pp_table->AcDcGpio = gpio_params.ucAcDcGpio;
			pp_table->AcDcPolarity = gpio_params.ucAcDcPolarity;
		पूर्ण अन्यथा अणु
			pp_table->AcDcGpio = 0;
			pp_table->AcDcPolarity = 0;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक vega10_avfs_enable(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_AVFS].supported) अणु
		/* Alपढ़ोy enabled or disabled */
		अगर (!(enable ^ data->smu_features[GNLD_AVFS].enabled))
			वापस 0;

		अगर (enable) अणु
			PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
					true,
					data->smu_features[GNLD_AVFS].smu_feature_biपंचांगap),
					"[avfs_control] Attempt to Enable AVFS feature Failed!",
					वापस -1);
			data->smu_features[GNLD_AVFS].enabled = true;
		पूर्ण अन्यथा अणु
			PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
					false,
					data->smu_features[GNLD_AVFS].smu_feature_biपंचांगap),
					"[avfs_control] Attempt to Disable AVFS feature Failed!",
					वापस -1);
			data->smu_features[GNLD_AVFS].enabled = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_update_avfs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->need_update_dpm_table & DPMTABLE_OD_UPDATE_VDDC) अणु
		vega10_avfs_enable(hwmgr, false);
	पूर्ण अन्यथा अगर (data->need_update_dpm_table) अणु
		vega10_avfs_enable(hwmgr, false);
		vega10_avfs_enable(hwmgr, true);
	पूर्ण अन्यथा अणु
		vega10_avfs_enable(hwmgr, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_populate_and_upload_avfs_fuse_override(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;

	uपूर्णांक64_t serial_number = 0;
	uपूर्णांक32_t top32, bottom32;
	काष्ठा phm_fuses_शेष fuse;

	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	AvfsFuseOverride_t *avfs_fuse_table = &(data->smc_state_table.avfs_fuse_override_table);

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ReadSerialNumTop32, &top32);

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ReadSerialNumBottom32, &bottom32);

	serial_number = ((uपूर्णांक64_t)bottom32 << 32) | top32;

	अगर (pp_override_get_शेष_fuse_value(serial_number, &fuse) == 0) अणु
		avfs_fuse_table->VFT0_b  = fuse.VFT0_b;
		avfs_fuse_table->VFT0_m1 = fuse.VFT0_m1;
		avfs_fuse_table->VFT0_m2 = fuse.VFT0_m2;
		avfs_fuse_table->VFT1_b  = fuse.VFT1_b;
		avfs_fuse_table->VFT1_m1 = fuse.VFT1_m1;
		avfs_fuse_table->VFT1_m2 = fuse.VFT1_m2;
		avfs_fuse_table->VFT2_b  = fuse.VFT2_b;
		avfs_fuse_table->VFT2_m1 = fuse.VFT2_m1;
		avfs_fuse_table->VFT2_m2 = fuse.VFT2_m2;
		result = smum_smc_table_manager(hwmgr,  (uपूर्णांक8_t *)avfs_fuse_table,
						AVFSFUSETABLE, false);
		PP_ASSERT_WITH_CODE(!result,
			"Failed to upload FuseOVerride!",
			);
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम vega10_check_dpm_table_updated(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा vega10_odn_dpm_table *odn_table = &(data->odn_dpm_table);
	काष्ठा phm_ppt_v2_inक्रमmation *table_info = hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *odn_dep_table;
	uपूर्णांक32_t i;

	dep_table = table_info->vdd_dep_on_mclk;
	odn_dep_table = (काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *)&(odn_table->vdd_dep_on_mclk);

	क्रम (i = 0; i < dep_table->count; i++) अणु
		अगर (dep_table->entries[i].vddc != odn_dep_table->entries[i].vddc) अणु
			data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_VDDC | DPMTABLE_OD_UPDATE_MCLK;
			वापस;
		पूर्ण
	पूर्ण

	dep_table = table_info->vdd_dep_on_sclk;
	odn_dep_table = (काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *)&(odn_table->vdd_dep_on_sclk);
	क्रम (i = 0; i < dep_table->count; i++) अणु
		अगर (dep_table->entries[i].vddc != odn_dep_table->entries[i].vddc) अणु
			data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_VDDC | DPMTABLE_OD_UPDATE_SCLK;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * Initializes the SMC table and uploads it
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * वापस:  always 0
 */
अटल पूर्णांक vega10_init_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	काष्ठा pp_atomfwctrl_voltage_table voltage_table;
	काष्ठा pp_atomfwctrl_bios_boot_up_values boot_up_values;
	काष्ठा vega10_odn_dpm_table *odn_table = &(data->odn_dpm_table);

	result = vega10_setup_शेष_dpm_tables(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to setup default DPM tables!",
			वापस result);

	अगर (!hwmgr->not_vf)
		वापस 0;

	/* initialize ODN table */
	अगर (hwmgr->od_enabled) अणु
		अगर (odn_table->max_vddc) अणु
			data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_SCLK | DPMTABLE_OD_UPDATE_MCLK;
			vega10_check_dpm_table_updated(hwmgr);
		पूर्ण अन्यथा अणु
			vega10_odn_initial_शेष_setting(hwmgr);
		पूर्ण
	पूर्ण

	pp_atomfwctrl_get_voltage_table_v4(hwmgr, VOLTAGE_TYPE_VDDC,
			VOLTAGE_OBJ_SVID2,  &voltage_table);
	pp_table->MaxVidStep = voltage_table.max_vid_step;

	pp_table->GfxDpmVoltageMode =
			(uपूर्णांक8_t)(table_info->uc_gfx_dpm_voltage_mode);
	pp_table->SocDpmVoltageMode =
			(uपूर्णांक8_t)(table_info->uc_soc_dpm_voltage_mode);
	pp_table->UclkDpmVoltageMode =
			(uपूर्णांक8_t)(table_info->uc_uclk_dpm_voltage_mode);
	pp_table->UvdDpmVoltageMode =
			(uपूर्णांक8_t)(table_info->uc_uvd_dpm_voltage_mode);
	pp_table->VceDpmVoltageMode =
			(uपूर्णांक8_t)(table_info->uc_vce_dpm_voltage_mode);
	pp_table->Mp0DpmVoltageMode =
			(uपूर्णांक8_t)(table_info->uc_mp0_dpm_voltage_mode);

	pp_table->DisplayDpmVoltageMode =
			(uपूर्णांक8_t)(table_info->uc_dcef_dpm_voltage_mode);

	data->vddc_voltage_table.psi0_enable = voltage_table.psi0_enable;
	data->vddc_voltage_table.psi1_enable = voltage_table.psi1_enable;

	अगर (data->registry_data.ulv_support &&
			table_info->us_ulv_voltage_offset) अणु
		result = vega10_populate_ulv_state(hwmgr);
		PP_ASSERT_WITH_CODE(!result,
				"Failed to initialize ULV state!",
				वापस result);
	पूर्ण

	result = vega10_populate_smc_link_levels(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize Link Level!",
			वापस result);

	result = vega10_override_pcie_parameters(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to override pcie parameters!",
			वापस result);

	result = vega10_populate_all_graphic_levels(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize Graphics Level!",
			वापस result);

	result = vega10_populate_all_memory_levels(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize Memory Level!",
			वापस result);

	vega10_populate_vddc_soc_levels(hwmgr);

	result = vega10_populate_all_display_घड़ी_levels(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize Display Level!",
			वापस result);

	result = vega10_populate_smc_vce_levels(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize VCE Level!",
			वापस result);

	result = vega10_populate_smc_uvd_levels(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize UVD Level!",
			वापस result);

	अगर (data->registry_data.घड़ी_stretcher_support) अणु
		result = vega10_populate_घड़ी_stretcher_table(hwmgr);
		PP_ASSERT_WITH_CODE(!result,
				"Failed to populate Clock Stretcher Table!",
				वापस result);
	पूर्ण

	result = pp_atomfwctrl_get_vbios_bootup_values(hwmgr, &boot_up_values);
	अगर (!result) अणु
		data->vbios_boot_state.vddc     = boot_up_values.usVddc;
		data->vbios_boot_state.vddci    = boot_up_values.usVddci;
		data->vbios_boot_state.mvddc    = boot_up_values.usMvddc;
		data->vbios_boot_state.gfx_घड़ी = boot_up_values.ulGfxClk;
		data->vbios_boot_state.mem_घड़ी = boot_up_values.ulUClk;
		pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(hwmgr,
				SMU9_SYSPLL0_SOCCLK_ID, 0, &boot_up_values.ulSocClk);

		pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(hwmgr,
				SMU9_SYSPLL0_DCEFCLK_ID, 0, &boot_up_values.ulDCEFClk);

		data->vbios_boot_state.soc_घड़ी = boot_up_values.ulSocClk;
		data->vbios_boot_state.dcef_घड़ी = boot_up_values.ulDCEFClk;
		अगर (0 != boot_up_values.usVddc) अणु
			smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetFloorSocVoltage,
						(boot_up_values.usVddc * 4),
						शून्य);
			data->vbios_boot_state.bsoc_vddc_lock = true;
		पूर्ण अन्यथा अणु
			data->vbios_boot_state.bsoc_vddc_lock = false;
		पूर्ण
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetMinDeepSleepDcefclk,
			(uपूर्णांक32_t)(data->vbios_boot_state.dcef_घड़ी / 100),
				शून्य);
	पूर्ण

	result = vega10_populate_avfs_parameters(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize AVFS Parameters!",
			वापस result);

	result = vega10_populate_gpio_parameters(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize GPIO Parameters!",
			वापस result);

	pp_table->GfxclkAverageAlpha = (uपूर्णांक8_t)
			(data->gfxclk_average_alpha);
	pp_table->SocclkAverageAlpha = (uपूर्णांक8_t)
			(data->socclk_average_alpha);
	pp_table->UclkAverageAlpha = (uपूर्णांक8_t)
			(data->uclk_average_alpha);
	pp_table->GfxActivityAverageAlpha = (uपूर्णांक8_t)
			(data->gfx_activity_average_alpha);

	vega10_populate_and_upload_avfs_fuse_override(hwmgr);

	result = smum_smc_table_manager(hwmgr, (uपूर्णांक8_t *)pp_table, PPTABLE, false);

	PP_ASSERT_WITH_CODE(!result,
			"Failed to upload PPtable!", वापस result);

	result = vega10_avfs_enable(hwmgr, true);
	PP_ASSERT_WITH_CODE(!result, "Attempt to enable AVFS feature Failed!",
					वापस result);
	vega10_acg_enable(hwmgr);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_enable_thermal_protection(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_THERMAL].supported) अणु
		अगर (data->smu_features[GNLD_THERMAL].enabled)
			pr_info("THERMAL Feature Already enabled!");

		PP_ASSERT_WITH_CODE(
				!vega10_enable_smc_features(hwmgr,
				true,
				data->smu_features[GNLD_THERMAL].smu_feature_biपंचांगap),
				"Enable THERMAL Feature Failed!",
				वापस -1);
		data->smu_features[GNLD_THERMAL].enabled = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_disable_thermal_protection(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_THERMAL].supported) अणु
		अगर (!data->smu_features[GNLD_THERMAL].enabled)
			pr_info("THERMAL Feature Already disabled!");

		PP_ASSERT_WITH_CODE(
				!vega10_enable_smc_features(hwmgr,
				false,
				data->smu_features[GNLD_THERMAL].smu_feature_biपंचांगap),
				"disable THERMAL Feature Failed!",
				वापस -1);
		data->smu_features[GNLD_THERMAL].enabled = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_enable_vrhot_feature(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (PP_CAP(PHM_Platक्रमmCaps_RegulatorHot)) अणु
		अगर (data->smu_features[GNLD_VR0HOT].supported) अणु
			PP_ASSERT_WITH_CODE(
					!vega10_enable_smc_features(hwmgr,
					true,
					data->smu_features[GNLD_VR0HOT].smu_feature_biपंचांगap),
					"Attempt to Enable VR0 Hot feature Failed!",
					वापस -1);
			data->smu_features[GNLD_VR0HOT].enabled = true;
		पूर्ण अन्यथा अणु
			अगर (data->smu_features[GNLD_VR1HOT].supported) अणु
				PP_ASSERT_WITH_CODE(
						!vega10_enable_smc_features(hwmgr,
						true,
						data->smu_features[GNLD_VR1HOT].smu_feature_biपंचांगap),
						"Attempt to Enable VR0 Hot feature Failed!",
						वापस -1);
				data->smu_features[GNLD_VR1HOT].enabled = true;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vega10_enable_ulv(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->registry_data.ulv_support) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				true, data->smu_features[GNLD_ULV].smu_feature_biपंचांगap),
				"Enable ULV Feature Failed!",
				वापस -1);
		data->smu_features[GNLD_ULV].enabled = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_disable_ulv(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->registry_data.ulv_support) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				false, data->smu_features[GNLD_ULV].smu_feature_biपंचांगap),
				"disable ULV Feature Failed!",
				वापस -EINVAL);
		data->smu_features[GNLD_ULV].enabled = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_enable_deep_sleep_master_चयन(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_DS_GFXCLK].supported) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				true, data->smu_features[GNLD_DS_GFXCLK].smu_feature_biपंचांगap),
				"Attempt to Enable DS_GFXCLK Feature Failed!",
				वापस -EINVAL);
		data->smu_features[GNLD_DS_GFXCLK].enabled = true;
	पूर्ण

	अगर (data->smu_features[GNLD_DS_SOCCLK].supported) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				true, data->smu_features[GNLD_DS_SOCCLK].smu_feature_biपंचांगap),
				"Attempt to Enable DS_SOCCLK Feature Failed!",
				वापस -EINVAL);
		data->smu_features[GNLD_DS_SOCCLK].enabled = true;
	पूर्ण

	अगर (data->smu_features[GNLD_DS_LCLK].supported) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				true, data->smu_features[GNLD_DS_LCLK].smu_feature_biपंचांगap),
				"Attempt to Enable DS_LCLK Feature Failed!",
				वापस -EINVAL);
		data->smu_features[GNLD_DS_LCLK].enabled = true;
	पूर्ण

	अगर (data->smu_features[GNLD_DS_DCEFCLK].supported) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				true, data->smu_features[GNLD_DS_DCEFCLK].smu_feature_biपंचांगap),
				"Attempt to Enable DS_DCEFCLK Feature Failed!",
				वापस -EINVAL);
		data->smu_features[GNLD_DS_DCEFCLK].enabled = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_disable_deep_sleep_master_चयन(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_DS_GFXCLK].supported) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				false, data->smu_features[GNLD_DS_GFXCLK].smu_feature_biपंचांगap),
				"Attempt to disable DS_GFXCLK Feature Failed!",
				वापस -EINVAL);
		data->smu_features[GNLD_DS_GFXCLK].enabled = false;
	पूर्ण

	अगर (data->smu_features[GNLD_DS_SOCCLK].supported) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				false, data->smu_features[GNLD_DS_SOCCLK].smu_feature_biपंचांगap),
				"Attempt to disable DS_ Feature Failed!",
				वापस -EINVAL);
		data->smu_features[GNLD_DS_SOCCLK].enabled = false;
	पूर्ण

	अगर (data->smu_features[GNLD_DS_LCLK].supported) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				false, data->smu_features[GNLD_DS_LCLK].smu_feature_biपंचांगap),
				"Attempt to disable DS_LCLK Feature Failed!",
				वापस -EINVAL);
		data->smu_features[GNLD_DS_LCLK].enabled = false;
	पूर्ण

	अगर (data->smu_features[GNLD_DS_DCEFCLK].supported) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				false, data->smu_features[GNLD_DS_DCEFCLK].smu_feature_biपंचांगap),
				"Attempt to disable DS_DCEFCLK Feature Failed!",
				वापस -EINVAL);
		data->smu_features[GNLD_DS_DCEFCLK].enabled = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_stop_dpm(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t biपंचांगap)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t i, feature_mask = 0;

	अगर (!hwmgr->not_vf)
		वापस 0;

	अगर(data->smu_features[GNLD_LED_DISPLAY].supported == true)अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				false, data->smu_features[GNLD_LED_DISPLAY].smu_feature_biपंचांगap),
		"Attempt to disable LED DPM feature failed!", वापस -EINVAL);
		data->smu_features[GNLD_LED_DISPLAY].enabled = false;
	पूर्ण

	क्रम (i = 0; i < GNLD_DPM_MAX; i++) अणु
		अगर (data->smu_features[i].smu_feature_biपंचांगap & biपंचांगap) अणु
			अगर (data->smu_features[i].supported) अणु
				अगर (data->smu_features[i].enabled) अणु
					feature_mask |= data->smu_features[i].
							smu_feature_biपंचांगap;
					data->smu_features[i].enabled = false;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	vega10_enable_smc_features(hwmgr, false, feature_mask);

	वापस 0;
पूर्ण

/**
 * Tell SMC to enabled the supported DPMs.
 *
 * @hwmgr:   the address of the घातerplay hardware manager.
 * @biपंचांगap:  biपंचांगap क्रम the features to enabled.
 * वापस:  0 on at least one DPM is successfully enabled.
 */
अटल पूर्णांक vega10_start_dpm(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t biपंचांगap)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t i, feature_mask = 0;

	क्रम (i = 0; i < GNLD_DPM_MAX; i++) अणु
		अगर (data->smu_features[i].smu_feature_biपंचांगap & biपंचांगap) अणु
			अगर (data->smu_features[i].supported) अणु
				अगर (!data->smu_features[i].enabled) अणु
					feature_mask |= data->smu_features[i].
							smu_feature_biपंचांगap;
					data->smu_features[i].enabled = true;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (vega10_enable_smc_features(hwmgr,
			true, feature_mask)) अणु
		क्रम (i = 0; i < GNLD_DPM_MAX; i++) अणु
			अगर (data->smu_features[i].smu_feature_biपंचांगap &
					feature_mask)
				data->smu_features[i].enabled = false;
		पूर्ण
	पूर्ण

	अगर(data->smu_features[GNLD_LED_DISPLAY].supported == true)अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				true, data->smu_features[GNLD_LED_DISPLAY].smu_feature_biपंचांगap),
		"Attempt to Enable LED DPM feature Failed!", वापस -EINVAL);
		data->smu_features[GNLD_LED_DISPLAY].enabled = true;
	पूर्ण

	अगर (data->vbios_boot_state.bsoc_vddc_lock) अणु
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetFloorSocVoltage, 0,
						शून्य);
		data->vbios_boot_state.bsoc_vddc_lock = false;
	पूर्ण

	अगर (PP_CAP(PHM_Platक्रमmCaps_Falcon_QuickTransition)) अणु
		अगर (data->smu_features[GNLD_ACDC].supported) अणु
			PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
					true, data->smu_features[GNLD_ACDC].smu_feature_biपंचांगap),
					"Attempt to Enable DS_GFXCLK Feature Failed!",
					वापस -1);
			data->smu_features[GNLD_ACDC].enabled = true;
		पूर्ण
	पूर्ण

	अगर (data->registry_data.pcie_dpm_key_disabled) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				false, data->smu_features[GNLD_DPM_LINK].smu_feature_biपंचांगap),
		"Attempt to Disable Link DPM feature Failed!", वापस -EINVAL);
		data->smu_features[GNLD_DPM_LINK].enabled = false;
		data->smu_features[GNLD_DPM_LINK].supported = false;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक vega10_enable_disable_PCC_limit_feature(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_PCC_LIMIT].supported) अणु
		अगर (enable == data->smu_features[GNLD_PCC_LIMIT].enabled)
			pr_info("GNLD_PCC_LIMIT has been %s \n", enable ? "enabled" : "disabled");
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				enable, data->smu_features[GNLD_PCC_LIMIT].smu_feature_biपंचांगap),
				"Attempt to Enable PCC Limit feature Failed!",
				वापस -EINVAL);
		data->smu_features[GNLD_PCC_LIMIT].enabled = enable;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_enable_dpm_tasks(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	पूर्णांक पंचांगp_result, result = 0;

	अगर (hwmgr->not_vf) अणु
		vega10_enable_disable_PCC_limit_feature(hwmgr, true);

		smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_ConfigureTelemetry, data->config_telemetry,
			शून्य);

		पंचांगp_result = vega10_स्थिरruct_voltage_tables(hwmgr);
		PP_ASSERT_WITH_CODE(!पंचांगp_result,
				    "Failed to construct voltage tables!",
				    result = पंचांगp_result);
	पूर्ण

	अगर (hwmgr->not_vf || hwmgr->pp_one_vf) अणु
		पंचांगp_result = vega10_init_smc_table(hwmgr);
		PP_ASSERT_WITH_CODE(!पंचांगp_result,
				    "Failed to initialize SMC table!",
				    result = पंचांगp_result);
	पूर्ण

	अगर (hwmgr->not_vf) अणु
		अगर (PP_CAP(PHM_Platक्रमmCaps_ThermalController)) अणु
			पंचांगp_result = vega10_enable_thermal_protection(hwmgr);
			PP_ASSERT_WITH_CODE(!पंचांगp_result,
					    "Failed to enable thermal protection!",
					    result = पंचांगp_result);
		पूर्ण

		पंचांगp_result = vega10_enable_vrhot_feature(hwmgr);
		PP_ASSERT_WITH_CODE(!पंचांगp_result,
				    "Failed to enable VR hot feature!",
				    result = पंचांगp_result);

		पंचांगp_result = vega10_enable_deep_sleep_master_चयन(hwmgr);
		PP_ASSERT_WITH_CODE(!पंचांगp_result,
				    "Failed to enable deep sleep master switch!",
				    result = पंचांगp_result);
	पूर्ण

	अगर (hwmgr->not_vf) अणु
		पंचांगp_result = vega10_start_dpm(hwmgr, SMC_DPM_FEATURES);
		PP_ASSERT_WITH_CODE(!पंचांगp_result,
				    "Failed to start DPM!", result = पंचांगp_result);
	पूर्ण

	अगर (hwmgr->not_vf) अणु
		/* enable didt, करो not पात अगर failed didt */
		पंचांगp_result = vega10_enable_didt_config(hwmgr);
		PP_ASSERT(!पंचांगp_result,
			  "Failed to enable didt config!");
	पूर्ण

	पंचांगp_result = vega10_enable_घातer_containment(hwmgr);
	PP_ASSERT_WITH_CODE(!पंचांगp_result,
			    "Failed to enable power containment!",
			    result = पंचांगp_result);

	अगर (hwmgr->not_vf) अणु
		पंचांगp_result = vega10_घातer_control_set_level(hwmgr);
		PP_ASSERT_WITH_CODE(!पंचांगp_result,
				    "Failed to power control set level!",
				    result = पंचांगp_result);

		पंचांगp_result = vega10_enable_ulv(hwmgr);
		PP_ASSERT_WITH_CODE(!पंचांगp_result,
				    "Failed to enable ULV!",
				    result = पंचांगp_result);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक vega10_get_घातer_state_size(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस माप(काष्ठा vega10_घातer_state);
पूर्ण

अटल पूर्णांक vega10_get_pp_table_entry_callback_func(काष्ठा pp_hwmgr *hwmgr,
		व्योम *state, काष्ठा pp_घातer_state *घातer_state,
		व्योम *pp_table, uपूर्णांक32_t classअगरication_flag)
अणु
	ATOM_Vega10_GFXCLK_Dependency_Record_V2 *patom_record_V2;
	काष्ठा vega10_घातer_state *vega10_घातer_state =
			cast_phw_vega10_घातer_state(&(घातer_state->hardware));
	काष्ठा vega10_perक्रमmance_level *perक्रमmance_level;
	ATOM_Vega10_State *state_entry = (ATOM_Vega10_State *)state;
	ATOM_Vega10_POWERPLAYTABLE *घातerplay_table =
			(ATOM_Vega10_POWERPLAYTABLE *)pp_table;
	ATOM_Vega10_SOCCLK_Dependency_Table *socclk_dep_table =
			(ATOM_Vega10_SOCCLK_Dependency_Table *)
			(((अचिन्हित दीर्घ)घातerplay_table) +
			le16_to_cpu(घातerplay_table->usSocclkDependencyTableOffset));
	ATOM_Vega10_GFXCLK_Dependency_Table *gfxclk_dep_table =
			(ATOM_Vega10_GFXCLK_Dependency_Table *)
			(((अचिन्हित दीर्घ)घातerplay_table) +
			le16_to_cpu(घातerplay_table->usGfxclkDependencyTableOffset));
	ATOM_Vega10_MCLK_Dependency_Table *mclk_dep_table =
			(ATOM_Vega10_MCLK_Dependency_Table *)
			(((अचिन्हित दीर्घ)घातerplay_table) +
			le16_to_cpu(घातerplay_table->usMclkDependencyTableOffset));


	/* The following fields are not initialized here:
	 * id orderedList allStatesList
	 */
	घातer_state->classअगरication.ui_label =
			(le16_to_cpu(state_entry->usClassअगरication) &
			ATOM_PPLIB_CLASSIFICATION_UI_MASK) >>
			ATOM_PPLIB_CLASSIFICATION_UI_SHIFT;
	घातer_state->classअगरication.flags = classअगरication_flag;
	/* NOTE: There is a classअगरication2 flag in BIOS
	 * that is not being used right now
	 */
	घातer_state->classअगरication.temporary_state = false;
	घातer_state->classअगरication.to_be_deleted = false;

	घातer_state->validation.disallowOnDC =
			((le32_to_cpu(state_entry->ulCapsAndSettings) &
					ATOM_Vega10_DISALLOW_ON_DC) != 0);

	घातer_state->display.disableFrameModulation = false;
	घातer_state->display.limitRefreshrate = false;
	घातer_state->display.enableVariBright =
			((le32_to_cpu(state_entry->ulCapsAndSettings) &
					ATOM_Vega10_ENABLE_VARIBRIGHT) != 0);

	घातer_state->validation.supportedPowerLevels = 0;
	घातer_state->uvd_घड़ीs.VCLK = 0;
	घातer_state->uvd_घड़ीs.DCLK = 0;
	घातer_state->temperatures.min = 0;
	घातer_state->temperatures.max = 0;

	perक्रमmance_level = &(vega10_घातer_state->perक्रमmance_levels
			[vega10_घातer_state->perक्रमmance_level_count++]);

	PP_ASSERT_WITH_CODE(
			(vega10_घातer_state->perक्रमmance_level_count <
					NUM_GFXCLK_DPM_LEVELS),
			"Performance levels exceeds SMC limit!",
			वापस -1);

	PP_ASSERT_WITH_CODE(
			(vega10_घातer_state->perक्रमmance_level_count <=
					hwmgr->platक्रमm_descriptor.
					hardwareActivityPerक्रमmanceLevels),
			"Performance levels exceeds Driver limit!",
			वापस -1);

	/* Perक्रमmance levels are arranged from low to high. */
	perक्रमmance_level->soc_घड़ी = socclk_dep_table->entries
			[state_entry->ucSocClockIndexLow].ulClk;
	perक्रमmance_level->gfx_घड़ी = gfxclk_dep_table->entries
			[state_entry->ucGfxClockIndexLow].ulClk;
	perक्रमmance_level->mem_घड़ी = mclk_dep_table->entries
			[state_entry->ucMemClockIndexLow].ulMemClk;

	perक्रमmance_level = &(vega10_घातer_state->perक्रमmance_levels
				[vega10_घातer_state->perक्रमmance_level_count++]);
	perक्रमmance_level->soc_घड़ी = socclk_dep_table->entries
				[state_entry->ucSocClockIndexHigh].ulClk;
	अगर (gfxclk_dep_table->ucRevId == 0) अणु
		/* under vega10 pp one vf mode, the gfx clk dpm need be lower
		 * to level-4 due to the limited 110w-घातer
		 */
		अगर (hwmgr->pp_one_vf && (state_entry->ucGfxClockIndexHigh > 0))
			perक्रमmance_level->gfx_घड़ी =
				gfxclk_dep_table->entries[4].ulClk;
		अन्यथा
			perक्रमmance_level->gfx_घड़ी = gfxclk_dep_table->entries
				[state_entry->ucGfxClockIndexHigh].ulClk;
	पूर्ण अन्यथा अगर (gfxclk_dep_table->ucRevId == 1) अणु
		patom_record_V2 = (ATOM_Vega10_GFXCLK_Dependency_Record_V2 *)gfxclk_dep_table->entries;
		अगर (hwmgr->pp_one_vf && (state_entry->ucGfxClockIndexHigh > 0))
			perक्रमmance_level->gfx_घड़ी = patom_record_V2[4].ulClk;
		अन्यथा
			perक्रमmance_level->gfx_घड़ी =
				patom_record_V2[state_entry->ucGfxClockIndexHigh].ulClk;
	पूर्ण

	perक्रमmance_level->mem_घड़ी = mclk_dep_table->entries
			[state_entry->ucMemClockIndexHigh].ulMemClk;
	वापस 0;
पूर्ण

अटल पूर्णांक vega10_get_pp_table_entry(काष्ठा pp_hwmgr *hwmgr,
		अचिन्हित दीर्घ entry_index, काष्ठा pp_घातer_state *state)
अणु
	पूर्णांक result;
	काष्ठा vega10_घातer_state *ps;

	state->hardware.magic = PhwVega10_Magic;

	ps = cast_phw_vega10_घातer_state(&state->hardware);

	result = vega10_get_घातerplay_table_entry(hwmgr, entry_index, state,
			vega10_get_pp_table_entry_callback_func);
	अगर (result)
		वापस result;

	/*
	 * This is the earliest समय we have all the dependency table
	 * and the VBIOS boot state
	 */
	/* set DC compatible flag अगर this state supports DC */
	अगर (!state->validation.disallowOnDC)
		ps->dc_compatible = true;

	ps->uvd_clks.vclk = state->uvd_घड़ीs.VCLK;
	ps->uvd_clks.dclk = state->uvd_घड़ीs.DCLK;

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_patch_boot_state(काष्ठा pp_hwmgr *hwmgr,
	     काष्ठा pp_hw_घातer_state *hw_ps)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vega10_apply_state_adjust_rules(काष्ठा pp_hwmgr *hwmgr,
				काष्ठा pp_घातer_state  *request_ps,
			स्थिर काष्ठा pp_घातer_state *current_ps)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	काष्ठा vega10_घातer_state *vega10_ps =
				cast_phw_vega10_घातer_state(&request_ps->hardware);
	uपूर्णांक32_t sclk;
	uपूर्णांक32_t mclk;
	काष्ठा PP_Clocks minimum_घड़ीs = अणु0पूर्ण;
	bool disable_mclk_चयनing;
	bool disable_mclk_चयनing_क्रम_frame_lock;
	bool disable_mclk_चयनing_क्रम_vr;
	bool क्रमce_mclk_high;
	स्थिर काष्ठा phm_घड़ी_and_voltage_limits *max_limits;
	uपूर्णांक32_t i;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	पूर्णांक32_t count;
	uपूर्णांक32_t stable_pstate_sclk_dpm_percentage;
	uपूर्णांक32_t stable_pstate_sclk = 0, stable_pstate_mclk = 0;
	uपूर्णांक32_t latency;

	data->battery_state = (PP_StateUILabel_Battery ==
			request_ps->classअगरication.ui_label);

	अगर (vega10_ps->perक्रमmance_level_count != 2)
		pr_info("VI should always have 2 performance levels");

	max_limits = adev->pm.ac_घातer ?
			&(hwmgr->dyn_state.max_घड़ी_voltage_on_ac) :
			&(hwmgr->dyn_state.max_घड़ी_voltage_on_dc);

	/* Cap घड़ी DPM tables at DC MAX अगर it is in DC. */
	अगर (!adev->pm.ac_घातer) अणु
		क्रम (i = 0; i < vega10_ps->perक्रमmance_level_count; i++) अणु
			अगर (vega10_ps->perक्रमmance_levels[i].mem_घड़ी >
				max_limits->mclk)
				vega10_ps->perक्रमmance_levels[i].mem_घड़ी =
						max_limits->mclk;
			अगर (vega10_ps->perक्रमmance_levels[i].gfx_घड़ी >
				max_limits->sclk)
				vega10_ps->perक्रमmance_levels[i].gfx_घड़ी =
						max_limits->sclk;
		पूर्ण
	पूर्ण

	/* result = PHM_CheckVBlankTime(hwmgr, &vblankTooShort);*/
	minimum_घड़ीs.engineClock = hwmgr->display_config->min_core_set_घड़ी;
	minimum_घड़ीs.memoryClock = hwmgr->display_config->min_mem_set_घड़ी;

	अगर (PP_CAP(PHM_Platक्रमmCaps_StablePState)) अणु
		stable_pstate_sclk_dpm_percentage =
			data->registry_data.stable_pstate_sclk_dpm_percentage;
		PP_ASSERT_WITH_CODE(
			data->registry_data.stable_pstate_sclk_dpm_percentage >= 1 &&
			data->registry_data.stable_pstate_sclk_dpm_percentage <= 100,
			"percent sclk value must range from 1% to 100%, setting default value",
			stable_pstate_sclk_dpm_percentage = 75);

		max_limits = &(hwmgr->dyn_state.max_घड़ी_voltage_on_ac);
		stable_pstate_sclk = (max_limits->sclk *
				stable_pstate_sclk_dpm_percentage) / 100;

		क्रम (count = table_info->vdd_dep_on_sclk->count - 1;
				count >= 0; count--) अणु
			अगर (stable_pstate_sclk >=
					table_info->vdd_dep_on_sclk->entries[count].clk) अणु
				stable_pstate_sclk =
						table_info->vdd_dep_on_sclk->entries[count].clk;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (count < 0)
			stable_pstate_sclk = table_info->vdd_dep_on_sclk->entries[0].clk;

		stable_pstate_mclk = max_limits->mclk;

		minimum_घड़ीs.engineClock = stable_pstate_sclk;
		minimum_घड़ीs.memoryClock = stable_pstate_mclk;
	पूर्ण

	disable_mclk_चयनing_क्रम_frame_lock =
		PP_CAP(PHM_Platक्रमmCaps_DisableMclkSwitchingForFrameLock);
	disable_mclk_चयनing_क्रम_vr =
		PP_CAP(PHM_Platक्रमmCaps_DisableMclkSwitchForVR);
	क्रमce_mclk_high = PP_CAP(PHM_Platक्रमmCaps_ForceMclkHigh);

	अगर (hwmgr->display_config->num_display == 0)
		disable_mclk_चयनing = false;
	अन्यथा
		disable_mclk_चयनing = ((1 < hwmgr->display_config->num_display) &&
					  !hwmgr->display_config->multi_monitor_in_sync) ||
			disable_mclk_चयनing_क्रम_frame_lock ||
			disable_mclk_चयनing_क्रम_vr ||
			क्रमce_mclk_high;

	sclk = vega10_ps->perक्रमmance_levels[0].gfx_घड़ी;
	mclk = vega10_ps->perक्रमmance_levels[0].mem_घड़ी;

	अगर (sclk < minimum_घड़ीs.engineClock)
		sclk = (minimum_घड़ीs.engineClock > max_limits->sclk) ?
				max_limits->sclk : minimum_घड़ीs.engineClock;

	अगर (mclk < minimum_घड़ीs.memoryClock)
		mclk = (minimum_घड़ीs.memoryClock > max_limits->mclk) ?
				max_limits->mclk : minimum_घड़ीs.memoryClock;

	vega10_ps->perक्रमmance_levels[0].gfx_घड़ी = sclk;
	vega10_ps->perक्रमmance_levels[0].mem_घड़ी = mclk;

	अगर (vega10_ps->perक्रमmance_levels[1].gfx_घड़ी <
			vega10_ps->perक्रमmance_levels[0].gfx_घड़ी)
		vega10_ps->perक्रमmance_levels[0].gfx_घड़ी =
				vega10_ps->perक्रमmance_levels[1].gfx_घड़ी;

	अगर (disable_mclk_चयनing) अणु
		/* Set Mclk the max of level 0 and level 1 */
		अगर (mclk < vega10_ps->perक्रमmance_levels[1].mem_घड़ी)
			mclk = vega10_ps->perक्रमmance_levels[1].mem_घड़ी;

		/* Find the lowest MCLK frequency that is within
		 * the tolerable latency defined in DAL
		 */
		latency = hwmgr->display_config->dce_tolerable_mclk_in_active_latency;
		क्रम (i = 0; i < data->mclk_latency_table.count; i++) अणु
			अगर ((data->mclk_latency_table.entries[i].latency <= latency) &&
				(data->mclk_latency_table.entries[i].frequency >=
						vega10_ps->perक्रमmance_levels[0].mem_घड़ी) &&
				(data->mclk_latency_table.entries[i].frequency <=
						vega10_ps->perक्रमmance_levels[1].mem_घड़ी))
				mclk = data->mclk_latency_table.entries[i].frequency;
		पूर्ण
		vega10_ps->perक्रमmance_levels[0].mem_घड़ी = mclk;
	पूर्ण अन्यथा अणु
		अगर (vega10_ps->perक्रमmance_levels[1].mem_घड़ी <
				vega10_ps->perक्रमmance_levels[0].mem_घड़ी)
			vega10_ps->perक्रमmance_levels[0].mem_घड़ी =
					vega10_ps->perक्रमmance_levels[1].mem_घड़ी;
	पूर्ण

	अगर (PP_CAP(PHM_Platक्रमmCaps_StablePState)) अणु
		क्रम (i = 0; i < vega10_ps->perक्रमmance_level_count; i++) अणु
			vega10_ps->perक्रमmance_levels[i].gfx_घड़ी = stable_pstate_sclk;
			vega10_ps->perक्रमmance_levels[i].mem_घड़ी = stable_pstate_mclk;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_find_dpm_states_घड़ीs_in_dpm_table(काष्ठा pp_hwmgr *hwmgr, स्थिर व्योम *input)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	स्थिर काष्ठा phm_set_घातer_state_input *states =
			(स्थिर काष्ठा phm_set_घातer_state_input *)input;
	स्थिर काष्ठा vega10_घातer_state *vega10_ps =
			cast_स्थिर_phw_vega10_घातer_state(states->pnew_state);
	काष्ठा vega10_single_dpm_table *sclk_table = &(data->dpm_table.gfx_table);
	uपूर्णांक32_t sclk = vega10_ps->perक्रमmance_levels
			[vega10_ps->perक्रमmance_level_count - 1].gfx_घड़ी;
	काष्ठा vega10_single_dpm_table *mclk_table = &(data->dpm_table.mem_table);
	uपूर्णांक32_t mclk = vega10_ps->perक्रमmance_levels
			[vega10_ps->perक्रमmance_level_count - 1].mem_घड़ी;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < sclk_table->count; i++) अणु
		अगर (sclk == sclk_table->dpm_levels[i].value)
			अवरोध;
	पूर्ण

	अगर (i >= sclk_table->count) अणु
		अगर (sclk > sclk_table->dpm_levels[i-1].value) अणु
			data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_SCLK;
			sclk_table->dpm_levels[i-1].value = sclk;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < mclk_table->count; i++) अणु
		अगर (mclk == mclk_table->dpm_levels[i].value)
			अवरोध;
	पूर्ण

	अगर (i >= mclk_table->count) अणु
		अगर (mclk > mclk_table->dpm_levels[i-1].value) अणु
			data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_MCLK;
			mclk_table->dpm_levels[i-1].value = mclk;
		पूर्ण
	पूर्ण

	अगर (data->display_timing.num_existing_displays != hwmgr->display_config->num_display)
		data->need_update_dpm_table |= DPMTABLE_UPDATE_MCLK;

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_populate_and_upload_sclk_mclk_dpm_levels(
		काष्ठा pp_hwmgr *hwmgr, स्थिर व्योम *input)
अणु
	पूर्णांक result = 0;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा vega10_dpm_table *dpm_table = &data->dpm_table;
	काष्ठा vega10_odn_dpm_table *odn_table = &data->odn_dpm_table;
	काष्ठा vega10_odn_घड़ी_voltage_dependency_table *odn_clk_table = &odn_table->vdd_dep_on_sclk;
	पूर्णांक count;

	अगर (!data->need_update_dpm_table)
		वापस 0;

	अगर (hwmgr->od_enabled && data->need_update_dpm_table & DPMTABLE_OD_UPDATE_SCLK) अणु
		क्रम (count = 0; count < dpm_table->gfx_table.count; count++)
			dpm_table->gfx_table.dpm_levels[count].value = odn_clk_table->entries[count].clk;
	पूर्ण

	odn_clk_table = &odn_table->vdd_dep_on_mclk;
	अगर (hwmgr->od_enabled && data->need_update_dpm_table & DPMTABLE_OD_UPDATE_MCLK) अणु
		क्रम (count = 0; count < dpm_table->mem_table.count; count++)
			dpm_table->mem_table.dpm_levels[count].value = odn_clk_table->entries[count].clk;
	पूर्ण

	अगर (data->need_update_dpm_table &
			(DPMTABLE_OD_UPDATE_SCLK | DPMTABLE_UPDATE_SCLK | DPMTABLE_UPDATE_SOCCLK)) अणु
		result = vega10_populate_all_graphic_levels(hwmgr);
		PP_ASSERT_WITH_CODE((0 == result),
				"Failed to populate SCLK during PopulateNewDPMClocksStates Function!",
				वापस result);
	पूर्ण

	अगर (data->need_update_dpm_table &
			(DPMTABLE_OD_UPDATE_MCLK | DPMTABLE_UPDATE_MCLK)) अणु
		result = vega10_populate_all_memory_levels(hwmgr);
		PP_ASSERT_WITH_CODE((0 == result),
				"Failed to populate MCLK during PopulateNewDPMClocksStates Function!",
				वापस result);
	पूर्ण

	vega10_populate_vddc_soc_levels(hwmgr);

	वापस result;
पूर्ण

अटल पूर्णांक vega10_trim_single_dpm_states(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा vega10_single_dpm_table *dpm_table,
		uपूर्णांक32_t low_limit, uपूर्णांक32_t high_limit)
अणु
	uपूर्णांक32_t i;

	क्रम (i = 0; i < dpm_table->count; i++) अणु
		अगर ((dpm_table->dpm_levels[i].value < low_limit) ||
		    (dpm_table->dpm_levels[i].value > high_limit))
			dpm_table->dpm_levels[i].enabled = false;
		अन्यथा
			dpm_table->dpm_levels[i].enabled = true;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vega10_trim_single_dpm_states_with_mask(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा vega10_single_dpm_table *dpm_table,
		uपूर्णांक32_t low_limit, uपूर्णांक32_t high_limit,
		uपूर्णांक32_t disable_dpm_mask)
अणु
	uपूर्णांक32_t i;

	क्रम (i = 0; i < dpm_table->count; i++) अणु
		अगर ((dpm_table->dpm_levels[i].value < low_limit) ||
		    (dpm_table->dpm_levels[i].value > high_limit))
			dpm_table->dpm_levels[i].enabled = false;
		अन्यथा अगर (!((1 << i) & disable_dpm_mask))
			dpm_table->dpm_levels[i].enabled = false;
		अन्यथा
			dpm_table->dpm_levels[i].enabled = true;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vega10_trim_dpm_states(काष्ठा pp_hwmgr *hwmgr,
		स्थिर काष्ठा vega10_घातer_state *vega10_ps)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t high_limit_count;

	PP_ASSERT_WITH_CODE((vega10_ps->perक्रमmance_level_count >= 1),
			"power state did not have any performance level",
			वापस -1);

	high_limit_count = (vega10_ps->perक्रमmance_level_count == 1) ? 0 : 1;

	vega10_trim_single_dpm_states(hwmgr,
			&(data->dpm_table.soc_table),
			vega10_ps->perक्रमmance_levels[0].soc_घड़ी,
			vega10_ps->perक्रमmance_levels[high_limit_count].soc_घड़ी);

	vega10_trim_single_dpm_states_with_mask(hwmgr,
			&(data->dpm_table.gfx_table),
			vega10_ps->perक्रमmance_levels[0].gfx_घड़ी,
			vega10_ps->perक्रमmance_levels[high_limit_count].gfx_घड़ी,
			data->disable_dpm_mask);

	vega10_trim_single_dpm_states(hwmgr,
			&(data->dpm_table.mem_table),
			vega10_ps->perक्रमmance_levels[0].mem_घड़ी,
			vega10_ps->perक्रमmance_levels[high_limit_count].mem_घड़ी);

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t vega10_find_lowest_dpm_level(
		काष्ठा vega10_single_dpm_table *table)
अणु
	uपूर्णांक32_t i;

	क्रम (i = 0; i < table->count; i++) अणु
		अगर (table->dpm_levels[i].enabled)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल uपूर्णांक32_t vega10_find_highest_dpm_level(
		काष्ठा vega10_single_dpm_table *table)
अणु
	uपूर्णांक32_t i = 0;

	अगर (table->count <= MAX_REGULAR_DPM_NUMBER) अणु
		क्रम (i = table->count; i > 0; i--) अणु
			अगर (table->dpm_levels[i - 1].enabled)
				वापस i - 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_info("DPM Table Has Too Many Entries!");
		वापस MAX_REGULAR_DPM_NUMBER - 1;
	पूर्ण

	वापस i;
पूर्ण

अटल व्योम vega10_apply_dal_minimum_voltage_request(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस;
पूर्ण

अटल पूर्णांक vega10_get_soc_index_क्रम_max_uclk(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_table_on_mclk;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);

	vdd_dep_table_on_mclk  = table_info->vdd_dep_on_mclk;

	वापस vdd_dep_table_on_mclk->entries[NUM_UCLK_DPM_LEVELS - 1].vddInd + 1;
पूर्ण

अटल पूर्णांक vega10_upload_dpm_bootup_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t socclk_idx;

	vega10_apply_dal_minimum_voltage_request(hwmgr);

	अगर (!data->registry_data.sclk_dpm_key_disabled) अणु
		अगर (data->smc_state_table.gfx_boot_level !=
				data->dpm_table.gfx_table.dpm_state.soft_min_level) अणु
			smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSoftMinGfxclkByIndex,
				data->smc_state_table.gfx_boot_level,
				शून्य);

			data->dpm_table.gfx_table.dpm_state.soft_min_level =
					data->smc_state_table.gfx_boot_level;
		पूर्ण
	पूर्ण

	अगर (!data->registry_data.mclk_dpm_key_disabled) अणु
		अगर (data->smc_state_table.mem_boot_level !=
				data->dpm_table.mem_table.dpm_state.soft_min_level) अणु
			अगर ((data->smc_state_table.mem_boot_level == NUM_UCLK_DPM_LEVELS - 1)
			    && hwmgr->not_vf) अणु
				socclk_idx = vega10_get_soc_index_क्रम_max_uclk(hwmgr);
				smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMinSocclkByIndex,
						socclk_idx,
						शून्य);
			पूर्ण अन्यथा अणु
				smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMinUclkByIndex,
						data->smc_state_table.mem_boot_level,
						शून्य);
			पूर्ण
			data->dpm_table.mem_table.dpm_state.soft_min_level =
					data->smc_state_table.mem_boot_level;
		पूर्ण
	पूर्ण

	अगर (!hwmgr->not_vf)
		वापस 0;

	अगर (!data->registry_data.socclk_dpm_key_disabled) अणु
		अगर (data->smc_state_table.soc_boot_level !=
				data->dpm_table.soc_table.dpm_state.soft_min_level) अणु
			smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSoftMinSocclkByIndex,
				data->smc_state_table.soc_boot_level,
				शून्य);
			data->dpm_table.soc_table.dpm_state.soft_min_level =
					data->smc_state_table.soc_boot_level;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_upload_dpm_max_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	vega10_apply_dal_minimum_voltage_request(hwmgr);

	अगर (!data->registry_data.sclk_dpm_key_disabled) अणु
		अगर (data->smc_state_table.gfx_max_level !=
			data->dpm_table.gfx_table.dpm_state.soft_max_level) अणु
			smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSoftMaxGfxclkByIndex,
				data->smc_state_table.gfx_max_level,
				शून्य);
			data->dpm_table.gfx_table.dpm_state.soft_max_level =
					data->smc_state_table.gfx_max_level;
		पूर्ण
	पूर्ण

	अगर (!data->registry_data.mclk_dpm_key_disabled) अणु
		अगर (data->smc_state_table.mem_max_level !=
			data->dpm_table.mem_table.dpm_state.soft_max_level) अणु
			smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetSoftMaxUclkByIndex,
					data->smc_state_table.mem_max_level,
					शून्य);
			data->dpm_table.mem_table.dpm_state.soft_max_level =
					data->smc_state_table.mem_max_level;
		पूर्ण
	पूर्ण

	अगर (!hwmgr->not_vf)
		वापस 0;

	अगर (!data->registry_data.socclk_dpm_key_disabled) अणु
		अगर (data->smc_state_table.soc_max_level !=
			data->dpm_table.soc_table.dpm_state.soft_max_level) अणु
			smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSoftMaxSocclkByIndex,
				data->smc_state_table.soc_max_level,
				शून्य);
			data->dpm_table.soc_table.dpm_state.soft_max_level =
					data->smc_state_table.soc_max_level;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_generate_dpm_level_enable_mask(
		काष्ठा pp_hwmgr *hwmgr, स्थिर व्योम *input)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	स्थिर काष्ठा phm_set_घातer_state_input *states =
			(स्थिर काष्ठा phm_set_घातer_state_input *)input;
	स्थिर काष्ठा vega10_घातer_state *vega10_ps =
			cast_स्थिर_phw_vega10_घातer_state(states->pnew_state);
	पूर्णांक i;

	PP_ASSERT_WITH_CODE(!vega10_trim_dpm_states(hwmgr, vega10_ps),
			"Attempt to Trim DPM States Failed!",
			वापस -1);

	data->smc_state_table.gfx_boot_level =
			vega10_find_lowest_dpm_level(&(data->dpm_table.gfx_table));
	data->smc_state_table.gfx_max_level =
			vega10_find_highest_dpm_level(&(data->dpm_table.gfx_table));
	data->smc_state_table.mem_boot_level =
			vega10_find_lowest_dpm_level(&(data->dpm_table.mem_table));
	data->smc_state_table.mem_max_level =
			vega10_find_highest_dpm_level(&(data->dpm_table.mem_table));
	data->smc_state_table.soc_boot_level =
			vega10_find_lowest_dpm_level(&(data->dpm_table.soc_table));
	data->smc_state_table.soc_max_level =
			vega10_find_highest_dpm_level(&(data->dpm_table.soc_table));

	PP_ASSERT_WITH_CODE(!vega10_upload_dpm_bootup_level(hwmgr),
			"Attempt to upload DPM Bootup Levels Failed!",
			वापस -1);
	PP_ASSERT_WITH_CODE(!vega10_upload_dpm_max_level(hwmgr),
			"Attempt to upload DPM Max Levels Failed!",
			वापस -1);
	क्रम(i = data->smc_state_table.gfx_boot_level; i < data->smc_state_table.gfx_max_level; i++)
		data->dpm_table.gfx_table.dpm_levels[i].enabled = true;


	क्रम(i = data->smc_state_table.mem_boot_level; i < data->smc_state_table.mem_max_level; i++)
		data->dpm_table.mem_table.dpm_levels[i].enabled = true;

	क्रम (i = data->smc_state_table.soc_boot_level; i < data->smc_state_table.soc_max_level; i++)
		data->dpm_table.soc_table.dpm_levels[i].enabled = true;

	वापस 0;
पूर्ण

पूर्णांक vega10_enable_disable_vce_dpm(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_DPM_VCE].supported) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				enable,
				data->smu_features[GNLD_DPM_VCE].smu_feature_biपंचांगap),
				"Attempt to Enable/Disable DPM VCE Failed!",
				वापस -1);
		data->smu_features[GNLD_DPM_VCE].enabled = enable;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_update_sclk_threshold(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t low_sclk_पूर्णांकerrupt_threshold = 0;

	अगर (PP_CAP(PHM_Platक्रमmCaps_SclkThrottleLowNotअगरication) &&
		(data->low_sclk_पूर्णांकerrupt_threshold != 0)) अणु
		low_sclk_पूर्णांकerrupt_threshold =
				data->low_sclk_पूर्णांकerrupt_threshold;

		data->smc_state_table.pp_table.LowGfxclkInterruptThreshold =
				cpu_to_le32(low_sclk_पूर्णांकerrupt_threshold);

		/* This message will also enable SmcToHost Interrupt */
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetLowGfxclkInterruptThreshold,
				(uपूर्णांक32_t)low_sclk_पूर्णांकerrupt_threshold,
				शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_set_घातer_state_tasks(काष्ठा pp_hwmgr *hwmgr,
		स्थिर व्योम *input)
अणु
	पूर्णांक पंचांगp_result, result = 0;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);

	पंचांगp_result = vega10_find_dpm_states_घड़ीs_in_dpm_table(hwmgr, input);
	PP_ASSERT_WITH_CODE(!पंचांगp_result,
			"Failed to find DPM states clocks in DPM table!",
			result = पंचांगp_result);

	पंचांगp_result = vega10_populate_and_upload_sclk_mclk_dpm_levels(hwmgr, input);
	PP_ASSERT_WITH_CODE(!पंचांगp_result,
			"Failed to populate and upload SCLK MCLK DPM levels!",
			result = पंचांगp_result);

	पंचांगp_result = vega10_generate_dpm_level_enable_mask(hwmgr, input);
	PP_ASSERT_WITH_CODE(!पंचांगp_result,
			"Failed to generate DPM level enabled mask!",
			result = पंचांगp_result);

	पंचांगp_result = vega10_update_sclk_threshold(hwmgr);
	PP_ASSERT_WITH_CODE(!पंचांगp_result,
			"Failed to update SCLK threshold!",
			result = पंचांगp_result);

	result = smum_smc_table_manager(hwmgr, (uपूर्णांक8_t *)pp_table, PPTABLE, false);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to upload PPtable!", वापस result);

	/*
	 * If a custom pp table is loaded, set DPMTABLE_OD_UPDATE_VDDC flag.
	 * That effectively disables AVFS feature.
	 */
	अगर(hwmgr->hardcode_pp_table != शून्य)
		data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_VDDC;

	vega10_update_avfs(hwmgr);

	/*
	 * Clear all OD flags except DPMTABLE_OD_UPDATE_VDDC.
	 * That will help to keep AVFS disabled.
	 */
	data->need_update_dpm_table &= DPMTABLE_OD_UPDATE_VDDC;

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t vega10_dpm_get_sclk(काष्ठा pp_hwmgr *hwmgr, bool low)
अणु
	काष्ठा pp_घातer_state *ps;
	काष्ठा vega10_घातer_state *vega10_ps;

	अगर (hwmgr == शून्य)
		वापस -EINVAL;

	ps = hwmgr->request_ps;

	अगर (ps == शून्य)
		वापस -EINVAL;

	vega10_ps = cast_phw_vega10_घातer_state(&ps->hardware);

	अगर (low)
		वापस vega10_ps->perक्रमmance_levels[0].gfx_घड़ी;
	अन्यथा
		वापस vega10_ps->perक्रमmance_levels
				[vega10_ps->perक्रमmance_level_count - 1].gfx_घड़ी;
पूर्ण

अटल uपूर्णांक32_t vega10_dpm_get_mclk(काष्ठा pp_hwmgr *hwmgr, bool low)
अणु
	काष्ठा pp_घातer_state *ps;
	काष्ठा vega10_घातer_state *vega10_ps;

	अगर (hwmgr == शून्य)
		वापस -EINVAL;

	ps = hwmgr->request_ps;

	अगर (ps == शून्य)
		वापस -EINVAL;

	vega10_ps = cast_phw_vega10_घातer_state(&ps->hardware);

	अगर (low)
		वापस vega10_ps->perक्रमmance_levels[0].mem_घड़ी;
	अन्यथा
		वापस vega10_ps->perक्रमmance_levels
				[vega10_ps->perक्रमmance_level_count-1].mem_घड़ी;
पूर्ण

अटल पूर्णांक vega10_get_gpu_घातer(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t *query)
अणु
	uपूर्णांक32_t value;

	अगर (!query)
		वापस -EINVAL;

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetCurrPkgPwr, &value);

	/* SMC वापसing actual watts, keep consistent with legacy asics, low 8 bit as 8 fractional bits */
	*query = value << 8;

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_पढ़ो_sensor(काष्ठा pp_hwmgr *hwmgr, पूर्णांक idx,
			      व्योम *value, पूर्णांक *size)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t sclk_mhz, mclk_idx, activity_percent = 0;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा vega10_dpm_table *dpm_table = &data->dpm_table;
	पूर्णांक ret = 0;
	uपूर्णांक32_t val_vid;

	चयन (idx) अणु
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetAverageGfxclkActualFrequency, &sclk_mhz);
		*((uपूर्णांक32_t *)value) = sclk_mhz * 100;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_MCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetCurrentUclkIndex, &mclk_idx);
		अगर (mclk_idx < dpm_table->mem_table.count) अणु
			*((uपूर्णांक32_t *)value) = dpm_table->mem_table.dpm_levels[mclk_idx].value;
			*size = 4;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
		smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_GetAverageGfxActivity, 0,
						&activity_percent);
		*((uपूर्णांक32_t *)value) = activity_percent > 100 ? 100 : activity_percent;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_TEMP:
		*((uपूर्णांक32_t *)value) = vega10_thermal_get_temperature(hwmgr);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_HOTSPOT_TEMP:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetTemperatureHotspot, (uपूर्णांक32_t *)value);
		*((uपूर्णांक32_t *)value) = *((uपूर्णांक32_t *)value) *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_MEM_TEMP:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetTemperatureHBM, (uपूर्णांक32_t *)value);
		*((uपूर्णांक32_t *)value) = *((uपूर्णांक32_t *)value) *
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
		ret = vega10_get_gpu_घातer(hwmgr, (uपूर्णांक32_t *)value);
		अवरोध;
	हाल AMDGPU_PP_SENSOR_VDDGFX:
		val_vid = (RREG32_SOC15(SMUIO, 0, mmSMUSVI0_PLANE0_CURRENTVID) &
			SMUSVI0_PLANE0_CURRENTVID__CURRENT_SVI0_PLANE0_VID_MASK) >>
			SMUSVI0_PLANE0_CURRENTVID__CURRENT_SVI0_PLANE0_VID__SHIFT;
		*((uपूर्णांक32_t *)value) = (uपूर्णांक32_t)convert_to_vddc((uपूर्णांक8_t)val_vid);
		वापस 0;
	हाल AMDGPU_PP_SENSOR_ENABLED_SMC_FEATURES_MASK:
		ret = vega10_get_enabled_smc_features(hwmgr, (uपूर्णांक64_t *)value);
		अगर (!ret)
			*size = 8;
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vega10_notअगरy_smc_display_change(काष्ठा pp_hwmgr *hwmgr,
		bool has_disp)
अणु
	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetUclkFastSwitch,
			has_disp ? 1 : 0,
			शून्य);
पूर्ण

अटल पूर्णांक vega10_display_घड़ी_voltage_request(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_display_घड़ी_request *घड़ी_req)
अणु
	पूर्णांक result = 0;
	क्रमागत amd_pp_घड़ी_प्रकारype clk_type = घड़ी_req->घड़ी_प्रकारype;
	uपूर्णांक32_t clk_freq = घड़ी_req->घड़ी_freq_in_khz / 1000;
	DSPCLK_e clk_select = 0;
	uपूर्णांक32_t clk_request = 0;

	चयन (clk_type) अणु
	हाल amd_pp_dcef_घड़ी:
		clk_select = DSPCLK_DCEFCLK;
		अवरोध;
	हाल amd_pp_disp_घड़ी:
		clk_select = DSPCLK_DISPCLK;
		अवरोध;
	हाल amd_pp_pixel_घड़ी:
		clk_select = DSPCLK_PIXCLK;
		अवरोध;
	हाल amd_pp_phy_घड़ी:
		clk_select = DSPCLK_PHYCLK;
		अवरोध;
	शेष:
		pr_info("[DisplayClockVoltageRequest]Invalid Clock Type!");
		result = -1;
		अवरोध;
	पूर्ण

	अगर (!result) अणु
		clk_request = (clk_freq << 16) | clk_select;
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_RequestDisplayClockByFreq,
				clk_request,
				शून्य);
	पूर्ण

	वापस result;
पूर्ण

अटल uपूर्णांक8_t vega10_get_uclk_index(काष्ठा pp_hwmgr *hwmgr,
			काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *mclk_table,
						uपूर्णांक32_t frequency)
अणु
	uपूर्णांक8_t count;
	uपूर्णांक8_t i;

	अगर (mclk_table == शून्य || mclk_table->count == 0)
		वापस 0;

	count = (uपूर्णांक8_t)(mclk_table->count);

	क्रम(i = 0; i < count; i++) अणु
		अगर(mclk_table->entries[i].clk >= frequency)
			वापस i;
	पूर्ण

	वापस i-1;
पूर्ण

अटल पूर्णांक vega10_notअगरy_smc_display_config_after_ps_adjusपंचांगent(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा vega10_single_dpm_table *dpm_table =
			&data->dpm_table.dcef_table;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *mclk_table = table_info->vdd_dep_on_mclk;
	uपूर्णांक32_t idx;
	काष्ठा PP_Clocks min_घड़ीs = अणु0पूर्ण;
	uपूर्णांक32_t i;
	काष्ठा pp_display_घड़ी_request घड़ी_req;

	अगर ((hwmgr->display_config->num_display > 1) &&
	     !hwmgr->display_config->multi_monitor_in_sync &&
	     !hwmgr->display_config->nb_pstate_चयन_disable)
		vega10_notअगरy_smc_display_change(hwmgr, false);
	अन्यथा
		vega10_notअगरy_smc_display_change(hwmgr, true);

	min_घड़ीs.dcefClock = hwmgr->display_config->min_dcef_set_clk;
	min_घड़ीs.dcefClockInSR = hwmgr->display_config->min_dcef_deep_sleep_set_clk;
	min_घड़ीs.memoryClock = hwmgr->display_config->min_mem_set_घड़ी;

	क्रम (i = 0; i < dpm_table->count; i++) अणु
		अगर (dpm_table->dpm_levels[i].value == min_घड़ीs.dcefClock)
			अवरोध;
	पूर्ण

	अगर (i < dpm_table->count) अणु
		घड़ी_req.घड़ी_प्रकारype = amd_pp_dcef_घड़ी;
		घड़ी_req.घड़ी_freq_in_khz = dpm_table->dpm_levels[i].value * 10;
		अगर (!vega10_display_घड़ी_voltage_request(hwmgr, &घड़ी_req)) अणु
			smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetMinDeepSleepDcefclk,
					min_घड़ीs.dcefClockInSR / 100,
					शून्य);
		पूर्ण अन्यथा अणु
			pr_info("Attempt to set Hard Min for DCEFCLK Failed!");
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_debug("Cannot find requested DCEFCLK!");
	पूर्ण

	अगर (min_घड़ीs.memoryClock != 0) अणु
		idx = vega10_get_uclk_index(hwmgr, mclk_table, min_घड़ीs.memoryClock);
		smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_SetSoftMinUclkByIndex, idx,
						शून्य);
		data->dpm_table.mem_table.dpm_state.soft_min_level= idx;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_क्रमce_dpm_highest(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	data->smc_state_table.gfx_boot_level =
	data->smc_state_table.gfx_max_level =
			vega10_find_highest_dpm_level(&(data->dpm_table.gfx_table));
	data->smc_state_table.mem_boot_level =
	data->smc_state_table.mem_max_level =
			vega10_find_highest_dpm_level(&(data->dpm_table.mem_table));

	PP_ASSERT_WITH_CODE(!vega10_upload_dpm_bootup_level(hwmgr),
			"Failed to upload boot level to highest!",
			वापस -1);

	PP_ASSERT_WITH_CODE(!vega10_upload_dpm_max_level(hwmgr),
			"Failed to upload dpm max level to highest!",
			वापस -1);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_क्रमce_dpm_lowest(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	data->smc_state_table.gfx_boot_level =
	data->smc_state_table.gfx_max_level =
			vega10_find_lowest_dpm_level(&(data->dpm_table.gfx_table));
	data->smc_state_table.mem_boot_level =
	data->smc_state_table.mem_max_level =
			vega10_find_lowest_dpm_level(&(data->dpm_table.mem_table));

	PP_ASSERT_WITH_CODE(!vega10_upload_dpm_bootup_level(hwmgr),
			"Failed to upload boot level to highest!",
			वापस -1);

	PP_ASSERT_WITH_CODE(!vega10_upload_dpm_max_level(hwmgr),
			"Failed to upload dpm max level to highest!",
			वापस -1);

	वापस 0;

पूर्ण

अटल पूर्णांक vega10_unक्रमce_dpm_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	data->smc_state_table.gfx_boot_level =
			vega10_find_lowest_dpm_level(&(data->dpm_table.gfx_table));
	data->smc_state_table.gfx_max_level =
			vega10_find_highest_dpm_level(&(data->dpm_table.gfx_table));
	data->smc_state_table.mem_boot_level =
			vega10_find_lowest_dpm_level(&(data->dpm_table.mem_table));
	data->smc_state_table.mem_max_level =
			vega10_find_highest_dpm_level(&(data->dpm_table.mem_table));

	PP_ASSERT_WITH_CODE(!vega10_upload_dpm_bootup_level(hwmgr),
			"Failed to upload DPM Bootup Levels!",
			वापस -1);

	PP_ASSERT_WITH_CODE(!vega10_upload_dpm_max_level(hwmgr),
			"Failed to upload DPM Max Levels!",
			वापस -1);
	वापस 0;
पूर्ण

अटल पूर्णांक vega10_get_profiling_clk_mask(काष्ठा pp_hwmgr *hwmgr, क्रमागत amd_dpm_क्रमced_level level,
				uपूर्णांक32_t *sclk_mask, uपूर्णांक32_t *mclk_mask, uपूर्णांक32_t *soc_mask)
अणु
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);

	अगर (table_info->vdd_dep_on_sclk->count > VEGA10_UMD_PSTATE_GFXCLK_LEVEL &&
		table_info->vdd_dep_on_socclk->count > VEGA10_UMD_PSTATE_SOCCLK_LEVEL &&
		table_info->vdd_dep_on_mclk->count > VEGA10_UMD_PSTATE_MCLK_LEVEL) अणु
		*sclk_mask = VEGA10_UMD_PSTATE_GFXCLK_LEVEL;
		*soc_mask = VEGA10_UMD_PSTATE_SOCCLK_LEVEL;
		*mclk_mask = VEGA10_UMD_PSTATE_MCLK_LEVEL;
		hwmgr->pstate_sclk = table_info->vdd_dep_on_sclk->entries[VEGA10_UMD_PSTATE_GFXCLK_LEVEL].clk;
		hwmgr->pstate_mclk = table_info->vdd_dep_on_mclk->entries[VEGA10_UMD_PSTATE_MCLK_LEVEL].clk;
	पूर्ण

	अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK) अणु
		*sclk_mask = 0;
	पूर्ण अन्यथा अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK) अणु
		*mclk_mask = 0;
	पूर्ण अन्यथा अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
		/* under vega10  pp one vf mode, the gfx clk dpm need be lower
		 * to level-4 due to the limited घातer
		 */
		अगर (hwmgr->pp_one_vf)
			*sclk_mask = 4;
		अन्यथा
			*sclk_mask = table_info->vdd_dep_on_sclk->count - 1;
		*soc_mask = table_info->vdd_dep_on_socclk->count - 1;
		*mclk_mask = table_info->vdd_dep_on_mclk->count - 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vega10_set_fan_control_mode(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t mode)
अणु
	अगर (!hwmgr->not_vf)
		वापस;

	चयन (mode) अणु
	हाल AMD_FAN_CTRL_NONE:
		vega10_fan_ctrl_set_fan_speed_percent(hwmgr, 100);
		अवरोध;
	हाल AMD_FAN_CTRL_MANUAL:
		अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl))
			vega10_fan_ctrl_stop_smc_fan_control(hwmgr);
		अवरोध;
	हाल AMD_FAN_CTRL_AUTO:
		अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl))
			vega10_fan_ctrl_start_smc_fan_control(hwmgr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक vega10_क्रमce_घड़ी_level(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, uपूर्णांक32_t mask)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	चयन (type) अणु
	हाल PP_SCLK:
		data->smc_state_table.gfx_boot_level = mask ? (ffs(mask) - 1) : 0;
		data->smc_state_table.gfx_max_level = mask ? (fls(mask) - 1) : 0;

		PP_ASSERT_WITH_CODE(!vega10_upload_dpm_bootup_level(hwmgr),
			"Failed to upload boot level to lowest!",
			वापस -EINVAL);

		PP_ASSERT_WITH_CODE(!vega10_upload_dpm_max_level(hwmgr),
			"Failed to upload dpm max level to highest!",
			वापस -EINVAL);
		अवरोध;

	हाल PP_MCLK:
		data->smc_state_table.mem_boot_level = mask ? (ffs(mask) - 1) : 0;
		data->smc_state_table.mem_max_level = mask ? (fls(mask) - 1) : 0;

		PP_ASSERT_WITH_CODE(!vega10_upload_dpm_bootup_level(hwmgr),
			"Failed to upload boot level to lowest!",
			वापस -EINVAL);

		PP_ASSERT_WITH_CODE(!vega10_upload_dpm_max_level(hwmgr),
			"Failed to upload dpm max level to highest!",
			वापस -EINVAL);

		अवरोध;

	हाल PP_SOCCLK:
		data->smc_state_table.soc_boot_level = mask ? (ffs(mask) - 1) : 0;
		data->smc_state_table.soc_max_level = mask ? (fls(mask) - 1) : 0;

		PP_ASSERT_WITH_CODE(!vega10_upload_dpm_bootup_level(hwmgr),
			"Failed to upload boot level to lowest!",
			वापस -EINVAL);

		PP_ASSERT_WITH_CODE(!vega10_upload_dpm_max_level(hwmgr),
			"Failed to upload dpm max level to highest!",
			वापस -EINVAL);

		अवरोध;

	हाल PP_DCEFCLK:
		pr_info("Setting DCEFCLK min/max dpm level is not supported!\n");
		अवरोध;

	हाल PP_PCIE:
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_dpm_क्रमce_dpm_level(काष्ठा pp_hwmgr *hwmgr,
				क्रमागत amd_dpm_क्रमced_level level)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t sclk_mask = 0;
	uपूर्णांक32_t mclk_mask = 0;
	uपूर्णांक32_t soc_mask = 0;

	अगर (hwmgr->pstate_sclk == 0)
		vega10_get_profiling_clk_mask(hwmgr, level, &sclk_mask, &mclk_mask, &soc_mask);

	चयन (level) अणु
	हाल AMD_DPM_FORCED_LEVEL_HIGH:
		ret = vega10_क्रमce_dpm_highest(hwmgr);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_LOW:
		ret = vega10_क्रमce_dpm_lowest(hwmgr);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_AUTO:
		ret = vega10_unक्रमce_dpm_levels(hwmgr);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_PEAK:
		ret = vega10_get_profiling_clk_mask(hwmgr, level, &sclk_mask, &mclk_mask, &soc_mask);
		अगर (ret)
			वापस ret;
		vega10_क्रमce_घड़ी_level(hwmgr, PP_SCLK, 1<<sclk_mask);
		vega10_क्रमce_घड़ी_level(hwmgr, PP_MCLK, 1<<mclk_mask);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_MANUAL:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_EXIT:
	शेष:
		अवरोध;
	पूर्ण

	अगर (!hwmgr->not_vf)
		वापस ret;

	अगर (!ret) अणु
		अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK && hwmgr->dpm_level != AMD_DPM_FORCED_LEVEL_PROखाता_PEAK)
			vega10_set_fan_control_mode(hwmgr, AMD_FAN_CTRL_NONE);
		अन्यथा अगर (level != AMD_DPM_FORCED_LEVEL_PROखाता_PEAK && hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK)
			vega10_set_fan_control_mode(hwmgr, AMD_FAN_CTRL_AUTO);
	पूर्ण

	वापस ret;
पूर्ण

अटल uपूर्णांक32_t vega10_get_fan_control_mode(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_FAN_CONTROL].enabled == false)
		वापस AMD_FAN_CTRL_MANUAL;
	अन्यथा
		वापस AMD_FAN_CTRL_AUTO;
पूर्ण

अटल पूर्णांक vega10_get_dal_घातer_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा amd_pp_simple_घड़ी_info *info)
अणु
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_घड़ी_and_voltage_limits *max_limits =
			&table_info->max_घड़ी_voltage_on_ac;

	info->engine_max_घड़ी = max_limits->sclk;
	info->memory_max_घड़ी = max_limits->mclk;

	वापस 0;
पूर्ण

अटल व्योम vega10_get_sclks(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table =
			table_info->vdd_dep_on_sclk;
	uपूर्णांक32_t i;

	घड़ीs->num_levels = 0;
	क्रम (i = 0; i < dep_table->count; i++) अणु
		अगर (dep_table->entries[i].clk) अणु
			घड़ीs->data[घड़ीs->num_levels].घड़ीs_in_khz =
					dep_table->entries[i].clk * 10;
			घड़ीs->num_levels++;
		पूर्ण
	पूर्ण

पूर्ण

अटल व्योम vega10_get_memघड़ीs(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table =
			table_info->vdd_dep_on_mclk;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t j = 0;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < dep_table->count; i++) अणु
		अगर (dep_table->entries[i].clk) अणु

			घड़ीs->data[j].घड़ीs_in_khz =
						dep_table->entries[i].clk * 10;
			data->mclk_latency_table.entries[j].frequency =
							dep_table->entries[i].clk;
			घड़ीs->data[j].latency_in_us =
				data->mclk_latency_table.entries[j].latency = 25;
			j++;
		पूर्ण
	पूर्ण
	घड़ीs->num_levels = data->mclk_latency_table.count = j;
पूर्ण

अटल व्योम vega10_get_dcefघड़ीs(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table =
			table_info->vdd_dep_on_dcefclk;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < dep_table->count; i++) अणु
		घड़ीs->data[i].घड़ीs_in_khz = dep_table->entries[i].clk * 10;
		घड़ीs->data[i].latency_in_us = 0;
		घड़ीs->num_levels++;
	पूर्ण
पूर्ण

अटल व्योम vega10_get_socघड़ीs(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table =
			table_info->vdd_dep_on_socclk;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < dep_table->count; i++) अणु
		घड़ीs->data[i].घड़ीs_in_khz = dep_table->entries[i].clk * 10;
		घड़ीs->data[i].latency_in_us = 0;
		घड़ीs->num_levels++;
	पूर्ण
पूर्ण

अटल पूर्णांक vega10_get_घड़ी_by_type_with_latency(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	चयन (type) अणु
	हाल amd_pp_sys_घड़ी:
		vega10_get_sclks(hwmgr, घड़ीs);
		अवरोध;
	हाल amd_pp_mem_घड़ी:
		vega10_get_memघड़ीs(hwmgr, घड़ीs);
		अवरोध;
	हाल amd_pp_dcef_घड़ी:
		vega10_get_dcefघड़ीs(hwmgr, घड़ीs);
		अवरोध;
	हाल amd_pp_soc_घड़ी:
		vega10_get_socघड़ीs(hwmgr, घड़ीs);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_get_घड़ी_by_type_with_voltage(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_voltage *घड़ीs)
अणु
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table;
	uपूर्णांक32_t i;

	चयन (type) अणु
	हाल amd_pp_mem_घड़ी:
		dep_table = table_info->vdd_dep_on_mclk;
		अवरोध;
	हाल amd_pp_dcef_घड़ी:
		dep_table = table_info->vdd_dep_on_dcefclk;
		अवरोध;
	हाल amd_pp_disp_घड़ी:
		dep_table = table_info->vdd_dep_on_dispclk;
		अवरोध;
	हाल amd_pp_pixel_घड़ी:
		dep_table = table_info->vdd_dep_on_pixclk;
		अवरोध;
	हाल amd_pp_phy_घड़ी:
		dep_table = table_info->vdd_dep_on_phyclk;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < dep_table->count; i++) अणु
		घड़ीs->data[i].घड़ीs_in_khz = dep_table->entries[i].clk  * 10;
		घड़ीs->data[i].voltage_in_mv = (uपूर्णांक32_t)(table_info->vddc_lookup_table->
				entries[dep_table->entries[i].vddInd].us_vdd);
		घड़ीs->num_levels++;
	पूर्ण

	अगर (i < dep_table->count)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_set_watermarks_क्रम_घड़ीs_ranges(काष्ठा pp_hwmgr *hwmgr,
							व्योम *घड़ी_range)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा dm_pp_wm_sets_with_घड़ी_ranges_soc15 *wm_with_घड़ी_ranges = घड़ी_range;
	Watermarks_t *table = &(data->smc_state_table.water_marks_table);

	अगर (!data->registry_data.disable_water_mark) अणु
		smu_set_watermarks_क्रम_घड़ीs_ranges(table, wm_with_घड़ी_ranges);
		data->water_marks_biपंचांगap = WaterMarksExist;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_get_ppfeature_status(काष्ठा pp_hwmgr *hwmgr, अक्षर *buf)
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
				"AVFS",
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
				"FAST_PPT",
				"DIDT",
				"ACG",
				"PCC_LIMIT"पूर्ण;
	अटल स्थिर अक्षर *output_title[] = अणु
				"FEATURES",
				"BITMASK",
				"ENABLEMENT"पूर्ण;
	uपूर्णांक64_t features_enabled;
	पूर्णांक i;
	पूर्णांक ret = 0;
	पूर्णांक size = 0;

	ret = vega10_get_enabled_smc_features(hwmgr, &features_enabled);
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

अटल पूर्णांक vega10_set_ppfeature_status(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक64_t new_ppfeature_masks)
अणु
	uपूर्णांक64_t features_enabled;
	uपूर्णांक64_t features_to_enable;
	uपूर्णांक64_t features_to_disable;
	पूर्णांक ret = 0;

	अगर (new_ppfeature_masks >= (1ULL << GNLD_FEATURES_MAX))
		वापस -EINVAL;

	ret = vega10_get_enabled_smc_features(hwmgr, &features_enabled);
	अगर (ret)
		वापस ret;

	features_to_disable =
		features_enabled & ~new_ppfeature_masks;
	features_to_enable =
		~features_enabled & new_ppfeature_masks;

	pr_debug("features_to_disable 0x%llx\n", features_to_disable);
	pr_debug("features_to_enable 0x%llx\n", features_to_enable);

	अगर (features_to_disable) अणु
		ret = vega10_enable_smc_features(hwmgr, false, features_to_disable);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (features_to_enable) अणु
		ret = vega10_enable_smc_features(hwmgr, true, features_to_enable);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_get_current_pcie_link_width_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	वापस (RREG32_PCIE(smnPCIE_LC_LINK_WIDTH_CNTL) &
		PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD_MASK)
		>> PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD__SHIFT;
पूर्ण

अटल पूर्णांक vega10_get_current_pcie_link_speed_level(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	वापस (RREG32_PCIE(smnPCIE_LC_SPEED_CNTL) &
		PSWUSP0_PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE_MASK)
		>> PSWUSP0_PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE__SHIFT;
पूर्ण

अटल पूर्णांक vega10_prपूर्णांक_घड़ी_levels(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, अक्षर *buf)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा vega10_single_dpm_table *sclk_table = &(data->dpm_table.gfx_table);
	काष्ठा vega10_single_dpm_table *mclk_table = &(data->dpm_table.mem_table);
	काष्ठा vega10_single_dpm_table *soc_table = &(data->dpm_table.soc_table);
	काष्ठा vega10_single_dpm_table *dcef_table = &(data->dpm_table.dcef_table);
	काष्ठा vega10_odn_घड़ी_voltage_dependency_table *podn_vdd_dep = शून्य;
	uपूर्णांक32_t gen_speed, lane_width, current_gen_speed, current_lane_width;
	PPTable_t *pptable = &(data->smc_state_table.pp_table);

	पूर्णांक i, now, size = 0, count = 0;

	चयन (type) अणु
	हाल PP_SCLK:
		अगर (data->registry_data.sclk_dpm_key_disabled)
			अवरोध;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetCurrentGfxclkIndex, &now);

		अगर (hwmgr->pp_one_vf &&
		    (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK))
			count = 5;
		अन्यथा
			count = sclk_table->count;
		क्रम (i = 0; i < count; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
					i, sclk_table->dpm_levels[i].value / 100,
					(i == now) ? "*" : "");
		अवरोध;
	हाल PP_MCLK:
		अगर (data->registry_data.mclk_dpm_key_disabled)
			अवरोध;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetCurrentUclkIndex, &now);

		क्रम (i = 0; i < mclk_table->count; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
					i, mclk_table->dpm_levels[i].value / 100,
					(i == now) ? "*" : "");
		अवरोध;
	हाल PP_SOCCLK:
		अगर (data->registry_data.socclk_dpm_key_disabled)
			अवरोध;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetCurrentSocclkIndex, &now);

		क्रम (i = 0; i < soc_table->count; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
					i, soc_table->dpm_levels[i].value / 100,
					(i == now) ? "*" : "");
		अवरोध;
	हाल PP_DCEFCLK:
		अगर (data->registry_data.dcefclk_dpm_key_disabled)
			अवरोध;

		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_GetClockFreqMHz, CLK_DCEFCLK, &now);

		क्रम (i = 0; i < dcef_table->count; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
					i, dcef_table->dpm_levels[i].value / 100,
					(dcef_table->dpm_levels[i].value / 100 == now) ?
					"*" : "");
		अवरोध;
	हाल PP_PCIE:
		current_gen_speed =
			vega10_get_current_pcie_link_speed_level(hwmgr);
		current_lane_width =
			vega10_get_current_pcie_link_width_level(hwmgr);
		क्रम (i = 0; i < NUM_LINK_LEVELS; i++) अणु
			gen_speed = pptable->PcieGenSpeed[i];
			lane_width = pptable->PcieLaneCount[i];

			size += प्र_लिखो(buf + size, "%d: %s %s %s\n", i,
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
					(current_gen_speed == gen_speed) &&
					(current_lane_width == lane_width) ?
					"*" : "");
		पूर्ण
		अवरोध;

	हाल OD_SCLK:
		अगर (hwmgr->od_enabled) अणु
			size = प्र_लिखो(buf, "%s:\n", "OD_SCLK");
			podn_vdd_dep = &data->odn_dpm_table.vdd_dep_on_sclk;
			क्रम (i = 0; i < podn_vdd_dep->count; i++)
				size += प्र_लिखो(buf + size, "%d: %10uMhz %10umV\n",
					i, podn_vdd_dep->entries[i].clk / 100,
						podn_vdd_dep->entries[i].vddc);
		पूर्ण
		अवरोध;
	हाल OD_MCLK:
		अगर (hwmgr->od_enabled) अणु
			size = प्र_लिखो(buf, "%s:\n", "OD_MCLK");
			podn_vdd_dep = &data->odn_dpm_table.vdd_dep_on_mclk;
			क्रम (i = 0; i < podn_vdd_dep->count; i++)
				size += प्र_लिखो(buf + size, "%d: %10uMhz %10umV\n",
					i, podn_vdd_dep->entries[i].clk/100,
						podn_vdd_dep->entries[i].vddc);
		पूर्ण
		अवरोध;
	हाल OD_RANGE:
		अगर (hwmgr->od_enabled) अणु
			size = प्र_लिखो(buf, "%s:\n", "OD_RANGE");
			size += प्र_लिखो(buf + size, "SCLK: %7uMHz %10uMHz\n",
				data->golden_dpm_table.gfx_table.dpm_levels[0].value/100,
				hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock/100);
			size += प्र_लिखो(buf + size, "MCLK: %7uMHz %10uMHz\n",
				data->golden_dpm_table.mem_table.dpm_levels[0].value/100,
				hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock/100);
			size += प्र_लिखो(buf + size, "VDDC: %7umV %11umV\n",
				data->odn_dpm_table.min_vddc,
				data->odn_dpm_table.max_vddc);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस size;
पूर्ण

अटल पूर्णांक vega10_display_configuration_changed_task(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	Watermarks_t *wm_table = &(data->smc_state_table.water_marks_table);
	पूर्णांक result = 0;

	अगर ((data->water_marks_biपंचांगap & WaterMarksExist) &&
			!(data->water_marks_biपंचांगap & WaterMarksLoaded)) अणु
		result = smum_smc_table_manager(hwmgr, (uपूर्णांक8_t *)wm_table, WMTABLE, false);
		PP_ASSERT_WITH_CODE(result, "Failed to update WMTABLE!", वापस -EINVAL);
		data->water_marks_biपंचांगap |= WaterMarksLoaded;
	पूर्ण

	अगर (data->water_marks_biपंचांगap & WaterMarksLoaded) अणु
		smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_NumOfDisplays, hwmgr->display_config->num_display,
			शून्य);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक vega10_enable_disable_uvd_dpm(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_DPM_UVD].supported) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				enable,
				data->smu_features[GNLD_DPM_UVD].smu_feature_biपंचांगap),
				"Attempt to Enable/Disable DPM UVD Failed!",
				वापस -1);
		data->smu_features[GNLD_DPM_UVD].enabled = enable;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vega10_घातer_gate_vce(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	data->vce_घातer_gated = bgate;
	vega10_enable_disable_vce_dpm(hwmgr, !bgate);
पूर्ण

अटल व्योम vega10_घातer_gate_uvd(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	data->uvd_घातer_gated = bgate;
	vega10_enable_disable_uvd_dpm(hwmgr, !bgate);
पूर्ण

अटल अंतरभूत bool vega10_are_घातer_levels_equal(
				स्थिर काष्ठा vega10_perक्रमmance_level *pl1,
				स्थिर काष्ठा vega10_perक्रमmance_level *pl2)
अणु
	वापस ((pl1->soc_घड़ी == pl2->soc_घड़ी) &&
			(pl1->gfx_घड़ी == pl2->gfx_घड़ी) &&
			(pl1->mem_घड़ी == pl2->mem_घड़ी));
पूर्ण

अटल पूर्णांक vega10_check_states_equal(काष्ठा pp_hwmgr *hwmgr,
				स्थिर काष्ठा pp_hw_घातer_state *pstate1,
			स्थिर काष्ठा pp_hw_घातer_state *pstate2, bool *equal)
अणु
	स्थिर काष्ठा vega10_घातer_state *psa;
	स्थिर काष्ठा vega10_घातer_state *psb;
	पूर्णांक i;

	अगर (pstate1 == शून्य || pstate2 == शून्य || equal == शून्य)
		वापस -EINVAL;

	psa = cast_स्थिर_phw_vega10_घातer_state(pstate1);
	psb = cast_स्थिर_phw_vega10_घातer_state(pstate2);
	/* If the two states करोn't even have the same number of perक्रमmance levels they cannot be the same state. */
	अगर (psa->perक्रमmance_level_count != psb->perक्रमmance_level_count) अणु
		*equal = false;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < psa->perक्रमmance_level_count; i++) अणु
		अगर (!vega10_are_घातer_levels_equal(&(psa->perक्रमmance_levels[i]), &(psb->perक्रमmance_levels[i]))) अणु
			/* If we have found even one perक्रमmance level pair that is dअगरferent the states are dअगरferent. */
			*equal = false;
			वापस 0;
		पूर्ण
	पूर्ण

	/* If all perक्रमmance levels are the same try to use the UVD घड़ीs to अवरोध the tie.*/
	*equal = ((psa->uvd_clks.vclk == psb->uvd_clks.vclk) && (psa->uvd_clks.dclk == psb->uvd_clks.dclk));
	*equal &= ((psa->vce_clks.evclk == psb->vce_clks.evclk) && (psa->vce_clks.ecclk == psb->vce_clks.ecclk));
	*equal &= (psa->sclk_threshold == psb->sclk_threshold);

	वापस 0;
पूर्ण

अटल bool
vega10_check_smc_update_required_क्रम_display_configuration(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	bool is_update_required = false;

	अगर (data->display_timing.num_existing_displays != hwmgr->display_config->num_display)
		is_update_required = true;

	अगर (PP_CAP(PHM_Platक्रमmCaps_SclkDeepSleep)) अणु
		अगर (data->display_timing.min_घड़ी_in_sr != hwmgr->display_config->min_core_set_घड़ी_in_sr)
			is_update_required = true;
	पूर्ण

	वापस is_update_required;
पूर्ण

अटल पूर्णांक vega10_disable_dpm_tasks(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक पंचांगp_result, result = 0;

	अगर (!hwmgr->not_vf)
		वापस 0;

	अगर (PP_CAP(PHM_Platक्रमmCaps_ThermalController))
		vega10_disable_thermal_protection(hwmgr);

	पंचांगp_result = vega10_disable_घातer_containment(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable power containment!", result = पंचांगp_result);

	पंचांगp_result = vega10_disable_didt_config(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable didt config!", result = पंचांगp_result);

	पंचांगp_result = vega10_avfs_enable(hwmgr, false);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable AVFS!", result = पंचांगp_result);

	पंचांगp_result = vega10_stop_dpm(hwmgr, SMC_DPM_FEATURES);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to stop DPM!", result = पंचांगp_result);

	पंचांगp_result = vega10_disable_deep_sleep_master_चयन(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable deep sleep!", result = पंचांगp_result);

	पंचांगp_result = vega10_disable_ulv(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable ulv!", result = पंचांगp_result);

	पंचांगp_result =  vega10_acg_disable(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable acg!", result = पंचांगp_result);

	vega10_enable_disable_PCC_limit_feature(hwmgr, false);
	वापस result;
पूर्ण

अटल पूर्णांक vega10_घातer_off_asic(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	पूर्णांक result;

	result = vega10_disable_dpm_tasks(hwmgr);
	PP_ASSERT_WITH_CODE((0 == result),
			"[disable_dpm_tasks] Failed to disable DPM!",
			);
	data->water_marks_biपंचांगap &= ~(WaterMarksLoaded);

	वापस result;
पूर्ण

अटल पूर्णांक vega10_get_sclk_od(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा vega10_single_dpm_table *sclk_table = &(data->dpm_table.gfx_table);
	काष्ठा vega10_single_dpm_table *golden_sclk_table =
			&(data->golden_dpm_table.gfx_table);
	पूर्णांक value = sclk_table->dpm_levels[sclk_table->count - 1].value;
	पूर्णांक golden_value = golden_sclk_table->dpm_levels
			[golden_sclk_table->count - 1].value;

	value -= golden_value;
	value = DIV_ROUND_UP(value * 100, golden_value);

	वापस value;
पूर्ण

अटल पूर्णांक vega10_set_sclk_od(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t value)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा vega10_single_dpm_table *golden_sclk_table =
			&(data->golden_dpm_table.gfx_table);
	काष्ठा pp_घातer_state *ps;
	काष्ठा vega10_घातer_state *vega10_ps;

	ps = hwmgr->request_ps;

	अगर (ps == शून्य)
		वापस -EINVAL;

	vega10_ps = cast_phw_vega10_घातer_state(&ps->hardware);

	vega10_ps->perक्रमmance_levels
	[vega10_ps->perक्रमmance_level_count - 1].gfx_घड़ी =
			golden_sclk_table->dpm_levels
			[golden_sclk_table->count - 1].value *
			value / 100 +
			golden_sclk_table->dpm_levels
			[golden_sclk_table->count - 1].value;

	अगर (vega10_ps->perक्रमmance_levels
			[vega10_ps->perक्रमmance_level_count - 1].gfx_घड़ी >
			hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock) अणु
		vega10_ps->perक्रमmance_levels
		[vega10_ps->perक्रमmance_level_count - 1].gfx_घड़ी =
				hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock;
		pr_warn("max sclk supported by vbios is %d\n",
				hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vega10_get_mclk_od(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा vega10_single_dpm_table *mclk_table = &(data->dpm_table.mem_table);
	काष्ठा vega10_single_dpm_table *golden_mclk_table =
			&(data->golden_dpm_table.mem_table);
	पूर्णांक value = mclk_table->dpm_levels[mclk_table->count - 1].value;
	पूर्णांक golden_value = golden_mclk_table->dpm_levels
			[golden_mclk_table->count - 1].value;

	value -= golden_value;
	value = DIV_ROUND_UP(value * 100, golden_value);

	वापस value;
पूर्ण

अटल पूर्णांक vega10_set_mclk_od(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t value)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा vega10_single_dpm_table *golden_mclk_table =
			&(data->golden_dpm_table.mem_table);
	काष्ठा pp_घातer_state  *ps;
	काष्ठा vega10_घातer_state  *vega10_ps;

	ps = hwmgr->request_ps;

	अगर (ps == शून्य)
		वापस -EINVAL;

	vega10_ps = cast_phw_vega10_घातer_state(&ps->hardware);

	vega10_ps->perक्रमmance_levels
	[vega10_ps->perक्रमmance_level_count - 1].mem_घड़ी =
			golden_mclk_table->dpm_levels
			[golden_mclk_table->count - 1].value *
			value / 100 +
			golden_mclk_table->dpm_levels
			[golden_mclk_table->count - 1].value;

	अगर (vega10_ps->perक्रमmance_levels
			[vega10_ps->perक्रमmance_level_count - 1].mem_घड़ी >
			hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock) अणु
		vega10_ps->perक्रमmance_levels
		[vega10_ps->perक्रमmance_level_count - 1].mem_घड़ी =
				hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock;
		pr_warn("max mclk supported by vbios is %d\n",
				hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_notअगरy_cac_buffer_info(काष्ठा pp_hwmgr *hwmgr,
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

अटल पूर्णांक vega10_get_thermal_temperature_range(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा PP_TemperatureRange *thermal_data)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
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

अटल पूर्णांक vega10_get_घातer_profile_mode(काष्ठा pp_hwmgr *hwmgr, अक्षर *buf)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t i, size = 0;
	अटल स्थिर uपूर्णांक8_t profile_mode_setting[6][4] = अणुअणु70, 60, 0, 0,पूर्ण,
						अणु70, 60, 1, 3,पूर्ण,
						अणु90, 60, 0, 0,पूर्ण,
						अणु70, 60, 0, 0,पूर्ण,
						अणु70, 90, 0, 0,पूर्ण,
						अणु30, 60, 0, 6,पूर्ण,
						पूर्ण;
	अटल स्थिर अक्षर *profile_name[7] = अणु"BOOTUP_DEFAULT",
					"3D_FULL_SCREEN",
					"POWER_SAVING",
					"VIDEO",
					"VR",
					"COMPUTE",
					"CUSTOM"पूर्ण;
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

	क्रम (i = 0; i < PP_SMC_POWER_PROखाता_CUSTOM; i++)
		size += प्र_लिखो(buf + size, "%3d %14s%s: %14d %3d %10d %14d\n",
			i, profile_name[i], (i == hwmgr->घातer_profile_mode) ? "*" : " ",
			profile_mode_setting[i][0], profile_mode_setting[i][1],
			profile_mode_setting[i][2], profile_mode_setting[i][3]);
	size += प्र_लिखो(buf + size, "%3d %14s%s: %14d %3d %10d %14d\n", i,
			profile_name[i], (i == hwmgr->घातer_profile_mode) ? "*" : " ",
			data->custom_profile_mode[0], data->custom_profile_mode[1],
			data->custom_profile_mode[2], data->custom_profile_mode[3]);
	वापस size;
पूर्ण

अटल पूर्णांक vega10_set_घातer_profile_mode(काष्ठा pp_hwmgr *hwmgr, दीर्घ *input, uपूर्णांक32_t size)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	uपूर्णांक8_t busy_set_poपूर्णांक;
	uपूर्णांक8_t FPS;
	uपूर्णांक8_t use_rlc_busy;
	uपूर्णांक8_t min_active_level;
	uपूर्णांक32_t घातer_profile_mode = input[size];

	अगर (घातer_profile_mode == PP_SMC_POWER_PROखाता_CUSTOM) अणु
		अगर (size != 0 && size != 4)
			वापस -EINVAL;

		/* If size = 0 and the CUSTOM profile has been set alपढ़ोy
		 * then just apply the profile. The copy stored in the hwmgr
		 * is zeroed out on init
		 */
		अगर (size == 0) अणु
			अगर (data->custom_profile_mode[0] != 0)
				जाओ out;
			अन्यथा
				वापस -EINVAL;
		पूर्ण

		data->custom_profile_mode[0] = busy_set_poपूर्णांक = input[0];
		data->custom_profile_mode[1] = FPS = input[1];
		data->custom_profile_mode[2] = use_rlc_busy = input[2];
		data->custom_profile_mode[3] = min_active_level = input[3];
		smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetCustomGfxDpmParameters,
					busy_set_poपूर्णांक | FPS<<8 |
					use_rlc_busy << 16 | min_active_level<<24,
					शून्य);
	पूर्ण

out:
	smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_SetWorkloadMask,
						(!घातer_profile_mode) ? 0 : 1 << (घातer_profile_mode - 1),
						शून्य);
	hwmgr->घातer_profile_mode = घातer_profile_mode;

	वापस 0;
पूर्ण


अटल bool vega10_check_clk_voltage_valid(काष्ठा pp_hwmgr *hwmgr,
					क्रमागत PP_OD_DPM_TABLE_COMMAND type,
					uपूर्णांक32_t clk,
					uपूर्णांक32_t voltage)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा vega10_odn_dpm_table *odn_table = &(data->odn_dpm_table);
	काष्ठा vega10_single_dpm_table *golden_table;

	अगर (voltage < odn_table->min_vddc || voltage > odn_table->max_vddc) अणु
		pr_info("OD voltage is out of range [%d - %d] mV\n", odn_table->min_vddc, odn_table->max_vddc);
		वापस false;
	पूर्ण

	अगर (type == PP_OD_EDIT_SCLK_VDDC_TABLE) अणु
		golden_table = &(data->golden_dpm_table.gfx_table);
		अगर (golden_table->dpm_levels[0].value > clk ||
			hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock < clk) अणु
			pr_info("OD engine clock is out of range [%d - %d] MHz\n",
				golden_table->dpm_levels[0].value/100,
				hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock/100);
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अगर (type == PP_OD_EDIT_MCLK_VDDC_TABLE) अणु
		golden_table = &(data->golden_dpm_table.mem_table);
		अगर (golden_table->dpm_levels[0].value > clk ||
			hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock < clk) अणु
			pr_info("OD memory clock is out of range [%d - %d] MHz\n",
				golden_table->dpm_levels[0].value/100,
				hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock/100);
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम vega10_odn_update_घातer_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा pp_घातer_state *ps = hwmgr->request_ps;
	काष्ठा vega10_घातer_state *vega10_ps;
	काष्ठा vega10_single_dpm_table *gfx_dpm_table =
		&data->dpm_table.gfx_table;
	काष्ठा vega10_single_dpm_table *soc_dpm_table =
		&data->dpm_table.soc_table;
	काष्ठा vega10_single_dpm_table *mem_dpm_table =
		&data->dpm_table.mem_table;
	पूर्णांक max_level;

	अगर (!ps)
		वापस;

	vega10_ps = cast_phw_vega10_घातer_state(&ps->hardware);
	max_level = vega10_ps->perक्रमmance_level_count - 1;

	अगर (vega10_ps->perक्रमmance_levels[max_level].gfx_घड़ी !=
	    gfx_dpm_table->dpm_levels[gfx_dpm_table->count - 1].value)
		vega10_ps->perक्रमmance_levels[max_level].gfx_घड़ी =
			gfx_dpm_table->dpm_levels[gfx_dpm_table->count - 1].value;

	अगर (vega10_ps->perक्रमmance_levels[max_level].soc_घड़ी !=
	    soc_dpm_table->dpm_levels[soc_dpm_table->count - 1].value)
		vega10_ps->perक्रमmance_levels[max_level].soc_घड़ी =
			soc_dpm_table->dpm_levels[soc_dpm_table->count - 1].value;

	अगर (vega10_ps->perक्रमmance_levels[max_level].mem_घड़ी !=
	    mem_dpm_table->dpm_levels[mem_dpm_table->count - 1].value)
		vega10_ps->perक्रमmance_levels[max_level].mem_घड़ी =
			mem_dpm_table->dpm_levels[mem_dpm_table->count - 1].value;

	अगर (!hwmgr->ps)
		वापस;

	ps = (काष्ठा pp_घातer_state *)((अचिन्हित दीर्घ)(hwmgr->ps) + hwmgr->ps_size * (hwmgr->num_ps - 1));
	vega10_ps = cast_phw_vega10_घातer_state(&ps->hardware);
	max_level = vega10_ps->perक्रमmance_level_count - 1;

	अगर (vega10_ps->perक्रमmance_levels[max_level].gfx_घड़ी !=
	    gfx_dpm_table->dpm_levels[gfx_dpm_table->count - 1].value)
		vega10_ps->perक्रमmance_levels[max_level].gfx_घड़ी =
			gfx_dpm_table->dpm_levels[gfx_dpm_table->count - 1].value;

	अगर (vega10_ps->perक्रमmance_levels[max_level].soc_घड़ी !=
	    soc_dpm_table->dpm_levels[soc_dpm_table->count - 1].value)
		vega10_ps->perक्रमmance_levels[max_level].soc_घड़ी =
			soc_dpm_table->dpm_levels[soc_dpm_table->count - 1].value;

	अगर (vega10_ps->perक्रमmance_levels[max_level].mem_घड़ी !=
	    mem_dpm_table->dpm_levels[mem_dpm_table->count - 1].value)
		vega10_ps->perक्रमmance_levels[max_level].mem_घड़ी =
			mem_dpm_table->dpm_levels[mem_dpm_table->count - 1].value;
पूर्ण

अटल व्योम vega10_odn_update_soc_table(काष्ठा pp_hwmgr *hwmgr,
						क्रमागत PP_OD_DPM_TABLE_COMMAND type)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info = hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table = table_info->vdd_dep_on_socclk;
	काष्ठा vega10_single_dpm_table *dpm_table = &data->golden_dpm_table.mem_table;

	काष्ठा vega10_odn_घड़ी_voltage_dependency_table *podn_vdd_dep_on_socclk =
							&data->odn_dpm_table.vdd_dep_on_socclk;
	काष्ठा vega10_odn_vddc_lookup_table *od_vddc_lookup_table = &data->odn_dpm_table.vddc_lookup_table;

	काष्ठा vega10_odn_घड़ी_voltage_dependency_table *podn_vdd_dep;
	uपूर्णांक8_t i, j;

	अगर (type == PP_OD_EDIT_SCLK_VDDC_TABLE) अणु
		podn_vdd_dep = &data->odn_dpm_table.vdd_dep_on_sclk;
		क्रम (i = 0; i < podn_vdd_dep->count; i++)
			od_vddc_lookup_table->entries[i].us_vdd = podn_vdd_dep->entries[i].vddc;
	पूर्ण अन्यथा अगर (type == PP_OD_EDIT_MCLK_VDDC_TABLE) अणु
		podn_vdd_dep = &data->odn_dpm_table.vdd_dep_on_mclk;
		क्रम (i = 0; i < dpm_table->count; i++) अणु
			क्रम (j = 0; j < od_vddc_lookup_table->count; j++) अणु
				अगर (od_vddc_lookup_table->entries[j].us_vdd >
					podn_vdd_dep->entries[i].vddc)
					अवरोध;
			पूर्ण
			अगर (j == od_vddc_lookup_table->count) अणु
				j = od_vddc_lookup_table->count - 1;
				od_vddc_lookup_table->entries[j].us_vdd =
					podn_vdd_dep->entries[i].vddc;
				data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_VDDC;
			पूर्ण
			podn_vdd_dep->entries[i].vddInd = j;
		पूर्ण
		dpm_table = &data->dpm_table.soc_table;
		क्रम (i = 0; i < dep_table->count; i++) अणु
			अगर (dep_table->entries[i].vddInd == podn_vdd_dep->entries[podn_vdd_dep->count-1].vddInd &&
					dep_table->entries[i].clk < podn_vdd_dep->entries[podn_vdd_dep->count-1].clk) अणु
				data->need_update_dpm_table |= DPMTABLE_UPDATE_SOCCLK;
				क्रम (; (i < dep_table->count) &&
				       (dep_table->entries[i].clk < podn_vdd_dep->entries[podn_vdd_dep->count - 1].clk); i++) अणु
					podn_vdd_dep_on_socclk->entries[i].clk = podn_vdd_dep->entries[podn_vdd_dep->count-1].clk;
					dpm_table->dpm_levels[i].value = podn_vdd_dep_on_socclk->entries[i].clk;
				पूर्ण
				अवरोध;
			पूर्ण अन्यथा अणु
				dpm_table->dpm_levels[i].value = dep_table->entries[i].clk;
				podn_vdd_dep_on_socclk->entries[i].vddc = dep_table->entries[i].vddc;
				podn_vdd_dep_on_socclk->entries[i].vddInd = dep_table->entries[i].vddInd;
				podn_vdd_dep_on_socclk->entries[i].clk = dep_table->entries[i].clk;
			पूर्ण
		पूर्ण
		अगर (podn_vdd_dep_on_socclk->entries[podn_vdd_dep_on_socclk->count - 1].clk <
					podn_vdd_dep->entries[podn_vdd_dep->count - 1].clk) अणु
			data->need_update_dpm_table |= DPMTABLE_UPDATE_SOCCLK;
			podn_vdd_dep_on_socclk->entries[podn_vdd_dep_on_socclk->count - 1].clk =
				podn_vdd_dep->entries[podn_vdd_dep->count - 1].clk;
			dpm_table->dpm_levels[podn_vdd_dep_on_socclk->count - 1].value =
				podn_vdd_dep->entries[podn_vdd_dep->count - 1].clk;
		पूर्ण
		अगर (podn_vdd_dep_on_socclk->entries[podn_vdd_dep_on_socclk->count - 1].vddInd <
					podn_vdd_dep->entries[podn_vdd_dep->count - 1].vddInd) अणु
			data->need_update_dpm_table |= DPMTABLE_UPDATE_SOCCLK;
			podn_vdd_dep_on_socclk->entries[podn_vdd_dep_on_socclk->count - 1].vddInd =
				podn_vdd_dep->entries[podn_vdd_dep->count - 1].vddInd;
		पूर्ण
	पूर्ण
	vega10_odn_update_घातer_state(hwmgr);
पूर्ण

अटल पूर्णांक vega10_odn_edit_dpm_table(काष्ठा pp_hwmgr *hwmgr,
					क्रमागत PP_OD_DPM_TABLE_COMMAND type,
					दीर्घ *input, uपूर्णांक32_t size)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	काष्ठा vega10_odn_घड़ी_voltage_dependency_table *podn_vdd_dep_table;
	काष्ठा vega10_single_dpm_table *dpm_table;

	uपूर्णांक32_t input_clk;
	uपूर्णांक32_t input_vol;
	uपूर्णांक32_t input_level;
	uपूर्णांक32_t i;

	PP_ASSERT_WITH_CODE(input, "NULL user input for clock and voltage",
				वापस -EINVAL);

	अगर (!hwmgr->od_enabled) अणु
		pr_info("OverDrive feature not enabled\n");
		वापस -EINVAL;
	पूर्ण

	अगर (PP_OD_EDIT_SCLK_VDDC_TABLE == type) अणु
		dpm_table = &data->dpm_table.gfx_table;
		podn_vdd_dep_table = &data->odn_dpm_table.vdd_dep_on_sclk;
		data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_SCLK;
	पूर्ण अन्यथा अगर (PP_OD_EDIT_MCLK_VDDC_TABLE == type) अणु
		dpm_table = &data->dpm_table.mem_table;
		podn_vdd_dep_table = &data->odn_dpm_table.vdd_dep_on_mclk;
		data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_MCLK;
	पूर्ण अन्यथा अगर (PP_OD_RESTORE_DEFAULT_TABLE == type) अणु
		स_नकल(&(data->dpm_table), &(data->golden_dpm_table), माप(काष्ठा vega10_dpm_table));
		vega10_odn_initial_शेष_setting(hwmgr);
		vega10_odn_update_घातer_state(hwmgr);
		/* क्रमce to update all घड़ी tables */
		data->need_update_dpm_table = DPMTABLE_UPDATE_SCLK |
					      DPMTABLE_UPDATE_MCLK |
					      DPMTABLE_UPDATE_SOCCLK;
		वापस 0;
	पूर्ण अन्यथा अगर (PP_OD_COMMIT_DPM_TABLE == type) अणु
		vega10_check_dpm_table_updated(hwmgr);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < size; i += 3) अणु
		अगर (i + 3 > size || input[i] >= podn_vdd_dep_table->count) अणु
			pr_info("invalid clock voltage input\n");
			वापस 0;
		पूर्ण
		input_level = input[i];
		input_clk = input[i+1] * 100;
		input_vol = input[i+2];

		अगर (vega10_check_clk_voltage_valid(hwmgr, type, input_clk, input_vol)) अणु
			dpm_table->dpm_levels[input_level].value = input_clk;
			podn_vdd_dep_table->entries[input_level].clk = input_clk;
			podn_vdd_dep_table->entries[input_level].vddc = input_vol;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	vega10_odn_update_soc_table(hwmgr, type);
	वापस 0;
पूर्ण

अटल पूर्णांक vega10_set_mp1_state(काष्ठा pp_hwmgr *hwmgr,
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

अटल पूर्णांक vega10_get_perक्रमmance_level(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा pp_hw_घातer_state *state,
				PHM_Perक्रमmanceLevelDesignation designation, uपूर्णांक32_t index,
				PHM_Perक्रमmanceLevel *level)
अणु
	स्थिर काष्ठा vega10_घातer_state *ps;
	uपूर्णांक32_t i;

	अगर (level == शून्य || hwmgr == शून्य || state == शून्य)
		वापस -EINVAL;

	ps = cast_स्थिर_phw_vega10_घातer_state(state);

	i = index > ps->perक्रमmance_level_count - 1 ?
			ps->perक्रमmance_level_count - 1 : index;

	level->coreClock = ps->perक्रमmance_levels[i].gfx_घड़ी;
	level->memory_घड़ी = ps->perक्रमmance_levels[i].mem_घड़ी;

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_disable_घातer_features_क्रम_compute_perक्रमmance(काष्ठा pp_hwmgr *hwmgr, bool disable)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t feature_mask = 0;

	अगर (disable) अणु
		feature_mask |= data->smu_features[GNLD_ULV].enabled ?
			data->smu_features[GNLD_ULV].smu_feature_biपंचांगap : 0;
		feature_mask |= data->smu_features[GNLD_DS_GFXCLK].enabled ?
			data->smu_features[GNLD_DS_GFXCLK].smu_feature_biपंचांगap : 0;
		feature_mask |= data->smu_features[GNLD_DS_SOCCLK].enabled ?
			data->smu_features[GNLD_DS_SOCCLK].smu_feature_biपंचांगap : 0;
		feature_mask |= data->smu_features[GNLD_DS_LCLK].enabled ?
			data->smu_features[GNLD_DS_LCLK].smu_feature_biपंचांगap : 0;
		feature_mask |= data->smu_features[GNLD_DS_DCEFCLK].enabled ?
			data->smu_features[GNLD_DS_DCEFCLK].smu_feature_biपंचांगap : 0;
	पूर्ण अन्यथा अणु
		feature_mask |= (!data->smu_features[GNLD_ULV].enabled) ?
			data->smu_features[GNLD_ULV].smu_feature_biपंचांगap : 0;
		feature_mask |= (!data->smu_features[GNLD_DS_GFXCLK].enabled) ?
			data->smu_features[GNLD_DS_GFXCLK].smu_feature_biपंचांगap : 0;
		feature_mask |= (!data->smu_features[GNLD_DS_SOCCLK].enabled) ?
			data->smu_features[GNLD_DS_SOCCLK].smu_feature_biपंचांगap : 0;
		feature_mask |= (!data->smu_features[GNLD_DS_LCLK].enabled) ?
			data->smu_features[GNLD_DS_LCLK].smu_feature_biपंचांगap : 0;
		feature_mask |= (!data->smu_features[GNLD_DS_DCEFCLK].enabled) ?
			data->smu_features[GNLD_DS_DCEFCLK].smu_feature_biपंचांगap : 0;
	पूर्ण

	अगर (feature_mask)
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				!disable, feature_mask),
				"enable/disable power features for compute performance Failed!",
				वापस -EINVAL);

	अगर (disable) अणु
		data->smu_features[GNLD_ULV].enabled = false;
		data->smu_features[GNLD_DS_GFXCLK].enabled = false;
		data->smu_features[GNLD_DS_SOCCLK].enabled = false;
		data->smu_features[GNLD_DS_LCLK].enabled = false;
		data->smu_features[GNLD_DS_DCEFCLK].enabled = false;
	पूर्ण अन्यथा अणु
		data->smu_features[GNLD_ULV].enabled = true;
		data->smu_features[GNLD_DS_GFXCLK].enabled = true;
		data->smu_features[GNLD_DS_SOCCLK].enabled = true;
		data->smu_features[GNLD_DS_LCLK].enabled = true;
		data->smu_features[GNLD_DS_DCEFCLK].enabled = true;
	पूर्ण

	वापस 0;

पूर्ण

अटल स्थिर काष्ठा pp_hwmgr_func vega10_hwmgr_funcs = अणु
	.backend_init = vega10_hwmgr_backend_init,
	.backend_fini = vega10_hwmgr_backend_fini,
	.asic_setup = vega10_setup_asic_task,
	.dynamic_state_management_enable = vega10_enable_dpm_tasks,
	.dynamic_state_management_disable = vega10_disable_dpm_tasks,
	.get_num_of_pp_table_entries =
			vega10_get_number_of_घातerplay_table_entries,
	.get_घातer_state_size = vega10_get_घातer_state_size,
	.get_pp_table_entry = vega10_get_pp_table_entry,
	.patch_boot_state = vega10_patch_boot_state,
	.apply_state_adjust_rules = vega10_apply_state_adjust_rules,
	.घातer_state_set = vega10_set_घातer_state_tasks,
	.get_sclk = vega10_dpm_get_sclk,
	.get_mclk = vega10_dpm_get_mclk,
	.notअगरy_smc_display_config_after_ps_adjusपंचांगent =
			vega10_notअगरy_smc_display_config_after_ps_adjusपंचांगent,
	.क्रमce_dpm_level = vega10_dpm_क्रमce_dpm_level,
	.stop_thermal_controller = vega10_thermal_stop_thermal_controller,
	.get_fan_speed_info = vega10_fan_ctrl_get_fan_speed_info,
	.get_fan_speed_percent = vega10_fan_ctrl_get_fan_speed_percent,
	.set_fan_speed_percent = vega10_fan_ctrl_set_fan_speed_percent,
	.reset_fan_speed_to_शेष =
			vega10_fan_ctrl_reset_fan_speed_to_शेष,
	.get_fan_speed_rpm = vega10_fan_ctrl_get_fan_speed_rpm,
	.set_fan_speed_rpm = vega10_fan_ctrl_set_fan_speed_rpm,
	.uninitialize_thermal_controller =
			vega10_thermal_ctrl_uninitialize_thermal_controller,
	.set_fan_control_mode = vega10_set_fan_control_mode,
	.get_fan_control_mode = vega10_get_fan_control_mode,
	.पढ़ो_sensor = vega10_पढ़ो_sensor,
	.get_dal_घातer_level = vega10_get_dal_घातer_level,
	.get_घड़ी_by_type_with_latency = vega10_get_घड़ी_by_type_with_latency,
	.get_घड़ी_by_type_with_voltage = vega10_get_घड़ी_by_type_with_voltage,
	.set_watermarks_क्रम_घड़ीs_ranges = vega10_set_watermarks_क्रम_घड़ीs_ranges,
	.display_घड़ी_voltage_request = vega10_display_घड़ी_voltage_request,
	.क्रमce_घड़ी_level = vega10_क्रमce_घड़ी_level,
	.prपूर्णांक_घड़ी_levels = vega10_prपूर्णांक_घड़ी_levels,
	.display_config_changed = vega10_display_configuration_changed_task,
	.घातergate_uvd = vega10_घातer_gate_uvd,
	.घातergate_vce = vega10_घातer_gate_vce,
	.check_states_equal = vega10_check_states_equal,
	.check_smc_update_required_क्रम_display_configuration =
			vega10_check_smc_update_required_क्रम_display_configuration,
	.घातer_off_asic = vega10_घातer_off_asic,
	.disable_smc_firmware_ctf = vega10_thermal_disable_alert,
	.get_sclk_od = vega10_get_sclk_od,
	.set_sclk_od = vega10_set_sclk_od,
	.get_mclk_od = vega10_get_mclk_od,
	.set_mclk_od = vega10_set_mclk_od,
	.avfs_control = vega10_avfs_enable,
	.notअगरy_cac_buffer_info = vega10_notअगरy_cac_buffer_info,
	.get_thermal_temperature_range = vega10_get_thermal_temperature_range,
	.रेजिस्टर_irq_handlers = smu9_रेजिस्टर_irq_handlers,
	.start_thermal_controller = vega10_start_thermal_controller,
	.get_घातer_profile_mode = vega10_get_घातer_profile_mode,
	.set_घातer_profile_mode = vega10_set_घातer_profile_mode,
	.set_घातer_limit = vega10_set_घातer_limit,
	.odn_edit_dpm_table = vega10_odn_edit_dpm_table,
	.get_perक्रमmance_level = vega10_get_perक्रमmance_level,
	.get_asic_baco_capability = smu9_baco_get_capability,
	.get_asic_baco_state = smu9_baco_get_state,
	.set_asic_baco_state = vega10_baco_set_state,
	.enable_mgpu_fan_boost = vega10_enable_mgpu_fan_boost,
	.get_ppfeature_status = vega10_get_ppfeature_status,
	.set_ppfeature_status = vega10_set_ppfeature_status,
	.set_mp1_state = vega10_set_mp1_state,
	.disable_घातer_features_क्रम_compute_perक्रमmance =
			vega10_disable_घातer_features_क्रम_compute_perक्रमmance,
पूर्ण;

पूर्णांक vega10_hwmgr_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	hwmgr->hwmgr_func = &vega10_hwmgr_funcs;
	hwmgr->pptable_func = &vega10_pptable_funcs;
	अगर (amdgpu_passthrough(adev))
		वापस vega10_baco_set_cap(hwmgr);

	वापस 0;
पूर्ण
