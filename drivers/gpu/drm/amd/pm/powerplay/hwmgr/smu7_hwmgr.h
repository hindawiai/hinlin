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

#अगर_अघोषित _SMU7_HWMGR_H
#घोषणा _SMU7_HWMGR_H

#समावेश "hwmgr.h"
#समावेश "ppatomctrl.h"

#घोषणा SMU7_MAX_HARDWARE_POWERLEVELS   2

#घोषणा SMU7_VOLTAGE_CONTROL_NONE                   0x0
#घोषणा SMU7_VOLTAGE_CONTROL_BY_GPIO                0x1
#घोषणा SMU7_VOLTAGE_CONTROL_BY_SVID2               0x2
#घोषणा SMU7_VOLTAGE_CONTROL_MERGED                 0x3

क्रमागत gpu_pt_config_reg_type अणु
	GPU_CONFIGREG_MMR = 0,
	GPU_CONFIGREG_SMC_IND,
	GPU_CONFIGREG_DIDT_IND,
	GPU_CONFIGREG_GC_CAC_IND,
	GPU_CONFIGREG_CACHE,
	GPU_CONFIGREG_MAX
पूर्ण;

काष्ठा gpu_pt_config_reg अणु
	uपूर्णांक32_t                           offset;
	uपूर्णांक32_t                           mask;
	uपूर्णांक32_t                           shअगरt;
	uपूर्णांक32_t                           value;
	क्रमागत gpu_pt_config_reg_type       type;
पूर्ण;

काष्ठा smu7_perक्रमmance_level अणु
	uपूर्णांक32_t  memory_घड़ी;
	uपूर्णांक32_t  engine_घड़ी;
	uपूर्णांक16_t  pcie_gen;
	uपूर्णांक16_t  pcie_lane;
पूर्ण;

काष्ठा smu7_thermal_temperature_setting अणु
	दीर्घ temperature_low;
	दीर्घ temperature_high;
	दीर्घ temperature_shutकरोwn;
पूर्ण;

काष्ठा smu7_uvd_घड़ीs अणु
	uपूर्णांक32_t  vclk;
	uपूर्णांक32_t  dclk;
पूर्ण;

काष्ठा smu7_vce_घड़ीs अणु
	uपूर्णांक32_t  evclk;
	uपूर्णांक32_t  ecclk;
पूर्ण;

काष्ठा smu7_घातer_state अणु
	uपूर्णांक32_t                  magic;
	काष्ठा smu7_uvd_घड़ीs    uvd_clks;
	काष्ठा smu7_vce_घड़ीs    vce_clks;
	uपूर्णांक32_t                  sam_clk;
	uपूर्णांक16_t                  perक्रमmance_level_count;
	bool                      dc_compatible;
	uपूर्णांक32_t                  sclk_threshold;
	काष्ठा smu7_perक्रमmance_level  perक्रमmance_levels[SMU7_MAX_HARDWARE_POWERLEVELS];
पूर्ण;

काष्ठा smu7_dpm_level अणु
	bool	enabled;
	uपूर्णांक32_t	value;
	uपूर्णांक32_t	param1;
पूर्ण;

#घोषणा SMU7_MAX_DEEPSLEEP_DIVIDER_ID 5
#घोषणा MAX_REGULAR_DPM_NUMBER 8
#घोषणा SMU7_MINIMUM_ENGINE_CLOCK 2500

काष्ठा smu7_single_dpm_table अणु
	uपूर्णांक32_t		count;
	काष्ठा smu7_dpm_level	dpm_levels[MAX_REGULAR_DPM_NUMBER];
पूर्ण;

काष्ठा smu7_dpm_table अणु
	काष्ठा smu7_single_dpm_table  sclk_table;
	काष्ठा smu7_single_dpm_table  mclk_table;
	काष्ठा smu7_single_dpm_table  pcie_speed_table;
	काष्ठा smu7_single_dpm_table  vddc_table;
	काष्ठा smu7_single_dpm_table  vddci_table;
	काष्ठा smu7_single_dpm_table  mvdd_table;
पूर्ण;

काष्ठा smu7_घड़ी_रेजिस्टरs अणु
	uपूर्णांक32_t  vCG_SPLL_FUNC_CNTL;
	uपूर्णांक32_t  vCG_SPLL_FUNC_CNTL_2;
	uपूर्णांक32_t  vCG_SPLL_FUNC_CNTL_3;
	uपूर्णांक32_t  vCG_SPLL_FUNC_CNTL_4;
	uपूर्णांक32_t  vCG_SPLL_SPREAD_SPECTRUM;
	uपूर्णांक32_t  vCG_SPLL_SPREAD_SPECTRUM_2;
	uपूर्णांक32_t  vDLL_CNTL;
	uपूर्णांक32_t  vMCLK_PWRMGT_CNTL;
	uपूर्णांक32_t  vMPLL_AD_FUNC_CNTL;
	uपूर्णांक32_t  vMPLL_DQ_FUNC_CNTL;
	uपूर्णांक32_t  vMPLL_FUNC_CNTL;
	uपूर्णांक32_t  vMPLL_FUNC_CNTL_1;
	uपूर्णांक32_t  vMPLL_FUNC_CNTL_2;
	uपूर्णांक32_t  vMPLL_SS1;
	uपूर्णांक32_t  vMPLL_SS2;
पूर्ण;

#घोषणा DISABLE_MC_LOADMICROCODE   1
#घोषणा DISABLE_MC_CFGPROGRAMMING  2

काष्ठा smu7_voltage_smio_रेजिस्टरs अणु
	uपूर्णांक32_t vS0_VID_LOWER_SMIO_CNTL;
पूर्ण;

#घोषणा SMU7_MAX_LEAKAGE_COUNT  8

काष्ठा smu7_leakage_voltage अणु
	uपूर्णांक16_t  count;
	uपूर्णांक16_t  leakage_id[SMU7_MAX_LEAKAGE_COUNT];
	uपूर्णांक16_t  actual_voltage[SMU7_MAX_LEAKAGE_COUNT];
पूर्ण;

काष्ठा smu7_vbios_boot_state अणु
	uपूर्णांक16_t    mvdd_bootup_value;
	uपूर्णांक16_t    vddc_bootup_value;
	uपूर्णांक16_t    vddci_bootup_value;
	uपूर्णांक16_t    vddgfx_bootup_value;
	uपूर्णांक32_t    sclk_bootup_value;
	uपूर्णांक32_t    mclk_bootup_value;
	uपूर्णांक16_t    pcie_gen_bootup_value;
	uपूर्णांक16_t    pcie_lane_bootup_value;
पूर्ण;

काष्ठा smu7_display_timing अणु
	uपूर्णांक32_t  min_घड़ी_in_sr;
	uपूर्णांक32_t  num_existing_displays;
	uपूर्णांक32_t  vrefresh;
पूर्ण;

काष्ठा smu7_dpmlevel_enable_mask अणु
	uपूर्णांक32_t  uvd_dpm_enable_mask;
	uपूर्णांक32_t  vce_dpm_enable_mask;
	uपूर्णांक32_t  acp_dpm_enable_mask;
	uपूर्णांक32_t  samu_dpm_enable_mask;
	uपूर्णांक32_t  sclk_dpm_enable_mask;
	uपूर्णांक32_t  mclk_dpm_enable_mask;
	uपूर्णांक32_t  pcie_dpm_enable_mask;
पूर्ण;

काष्ठा smu7_pcie_perf_range अणु
	uपूर्णांक16_t  max;
	uपूर्णांक16_t  min;
पूर्ण;

काष्ठा smu7_odn_घड़ी_voltage_dependency_table अणु
	uपूर्णांक32_t count;
	phm_ppt_v1_घड़ी_voltage_dependency_record entries[MAX_REGULAR_DPM_NUMBER];
पूर्ण;

काष्ठा smu7_odn_dpm_table अणु
	काष्ठा phm_odn_घड़ी_levels		odn_core_घड़ी_dpm_levels;
	काष्ठा phm_odn_घड़ी_levels		odn_memory_घड़ी_dpm_levels;
	काष्ठा smu7_odn_घड़ी_voltage_dependency_table	vdd_dependency_on_sclk;
	काष्ठा smu7_odn_घड़ी_voltage_dependency_table	vdd_dependency_on_mclk;
	uपूर्णांक32_t					odn_mclk_min_limit;
	uपूर्णांक32_t min_vddc;
	uपूर्णांक32_t max_vddc;
पूर्ण;

काष्ठा profile_mode_setting अणु
	uपूर्णांक8_t bupdate_sclk;
	uपूर्णांक8_t sclk_up_hyst;
	uपूर्णांक8_t sclk_करोwn_hyst;
	uपूर्णांक16_t sclk_activity;
	uपूर्णांक8_t bupdate_mclk;
	uपूर्णांक8_t mclk_up_hyst;
	uपूर्णांक8_t mclk_करोwn_hyst;
	uपूर्णांक16_t mclk_activity;
पूर्ण;

काष्ठा smu7_mclk_latency_entries अणु
	uपूर्णांक32_t  frequency;
	uपूर्णांक32_t  latency;
पूर्ण;

काष्ठा smu7_mclk_latency_table अणु
	uपूर्णांक32_t  count;
	काष्ठा smu7_mclk_latency_entries  entries[MAX_REGULAR_DPM_NUMBER];
पूर्ण;

काष्ठा smu7_hwmgr अणु
	काष्ठा smu7_dpm_table			dpm_table;
	काष्ठा smu7_dpm_table			golden_dpm_table;
	काष्ठा smu7_odn_dpm_table		odn_dpm_table;
	काष्ठा smu7_mclk_latency_table		mclk_latency_table;

	uपूर्णांक32_t						voting_rights_clients[8];
	uपूर्णांक32_t						अटल_screen_threshold_unit;
	uपूर्णांक32_t						अटल_screen_threshold;
	uपूर्णांक32_t						voltage_control;
	uपूर्णांक32_t						vdd_gfx_control;
	uपूर्णांक32_t						vddc_vddgfx_delta;
	uपूर्णांक32_t						active_स्वतः_throttle_sources;

	काष्ठा smu7_घड़ी_रेजिस्टरs            घड़ी_रेजिस्टरs;

	bool                           is_memory_gddr5;
	uपूर्णांक16_t                       acpi_vddc;
	bool                           pspp_notअगरy_required;
	uपूर्णांक16_t                       क्रमce_pcie_gen;
	uपूर्णांक16_t                       acpi_pcie_gen;
	uपूर्णांक32_t                       pcie_gen_cap;
	uपूर्णांक32_t                       pcie_lane_cap;
	uपूर्णांक32_t                       pcie_spc_cap;
	काष्ठा smu7_leakage_voltage          vddc_leakage;
	काष्ठा smu7_leakage_voltage          vddci_leakage;
	काष्ठा smu7_leakage_voltage          vddcgfx_leakage;

	uपूर्णांक32_t                             mvdd_control;
	uपूर्णांक32_t                             vddc_mask_low;
	uपूर्णांक32_t                             mvdd_mask_low;
	uपूर्णांक16_t                            max_vddc_in_pptable;
	uपूर्णांक16_t                            min_vddc_in_pptable;
	uपूर्णांक16_t                            max_vddci_in_pptable;
	uपूर्णांक16_t                            min_vddci_in_pptable;
	bool                                is_uvd_enabled;
	काष्ठा smu7_vbios_boot_state        vbios_boot_state;

	bool                           pcie_perक्रमmance_request;
	bool                           battery_state;
	bool                           mclk_ignore_संकेत;
	bool                           is_tlu_enabled;
	bool                           disable_handshake;
	bool                           smc_voltage_control_enabled;
	bool                           vbi_समय_out_support;

	uपूर्णांक32_t                       soft_regs_start;
	/* ---- Stuff originally coming from Evergreen ---- */
	uपूर्णांक32_t                             vddci_control;
	काष्ठा pp_atomctrl_voltage_table     vddc_voltage_table;
	काष्ठा pp_atomctrl_voltage_table     vddci_voltage_table;
	काष्ठा pp_atomctrl_voltage_table     mvdd_voltage_table;
	काष्ठा pp_atomctrl_voltage_table     vddgfx_voltage_table;

	uपूर्णांक32_t                             mgcg_cgtt_local2;
	uपूर्णांक32_t                             mgcg_cgtt_local3;
	uपूर्णांक32_t                             gpio_debug;
	uपूर्णांक32_t                             mc_micro_code_feature;
	uपूर्णांक32_t                             highest_mclk;
	uपूर्णांक16_t                             acpi_vddci;
	uपूर्णांक8_t                              mvdd_high_index;
	uपूर्णांक8_t                              mvdd_low_index;
	bool                                 dll_शेष_on;
	bool                                 perक्रमmance_request_रेजिस्टरed;

	/* ---- Low Power Features ---- */
	bool                           ulv_supported;

	/* ---- CAC Stuff ---- */
	uपूर्णांक32_t                       cac_table_start;
	bool                           cac_configuration_required;
	bool                           driver_calculate_cac_leakage;
	bool                           cac_enabled;

	/* ---- DPM2 Parameters ---- */
	uपूर्णांक32_t                       घातer_containment_features;
	bool                           enable_dte_feature;
	bool                           enable_tdc_limit_feature;
	bool                           enable_pkg_pwr_tracking_feature;
	bool                           disable_uvd_घातer_tune_feature;


	uपूर्णांक32_t                       dte_tj_offset;
	uपूर्णांक32_t                       fast_watermark_threshold;

	/* ---- Phase Shedding ---- */
	uपूर्णांक8_t                           vddc_phase_shed_control;

	/* ---- DI/DT ---- */
	काष्ठा smu7_display_timing        display_timing;

	/* ---- Thermal Temperature Setting ---- */
	काष्ठा smu7_thermal_temperature_setting  thermal_temp_setting;
	काष्ठा smu7_dpmlevel_enable_mask     dpm_level_enable_mask;
	uपूर्णांक32_t                                  need_update_smu7_dpm_table;
	uपूर्णांक32_t                                  sclk_dpm_key_disabled;
	uपूर्णांक32_t                                  mclk_dpm_key_disabled;
	uपूर्णांक32_t                                  pcie_dpm_key_disabled;
	uपूर्णांक32_t                                  min_engine_घड़ीs;
	काष्ठा smu7_pcie_perf_range          pcie_gen_perक्रमmance;
	काष्ठा smu7_pcie_perf_range          pcie_lane_perक्रमmance;
	काष्ठा smu7_pcie_perf_range          pcie_gen_घातer_saving;
	काष्ठा smu7_pcie_perf_range          pcie_lane_घातer_saving;
	bool                                      use_pcie_perक्रमmance_levels;
	bool                                      use_pcie_घातer_saving_levels;
	uपूर्णांक32_t                                  mclk_dpm0_activity_target;
	uपूर्णांक32_t                                  low_sclk_पूर्णांकerrupt_threshold;
	uपूर्णांक32_t                                  last_mclk_dpm_enable_mask;
	bool                                      uvd_enabled;

	/* ---- Power Gating States ---- */
	bool                           uvd_घातer_gated;
	bool                           vce_घातer_gated;
	bool                           need_दीर्घ_memory_training;

	/* Application घातer optimization parameters */
	bool                               update_up_hyst;
	bool                               update_करोwn_hyst;
	uपूर्णांक32_t                           करोwn_hyst;
	uपूर्णांक32_t                           up_hyst;
	uपूर्णांक32_t disable_dpm_mask;
	bool apply_optimized_settings;

	uपूर्णांक32_t                              avfs_vdroop_override_setting;
	bool                                  apply_avfs_cks_off_voltage;
	uपूर्णांक32_t                              frame_समय_x2;
	uपूर्णांक32_t                              last_sent_vbi_समयout;
	uपूर्णांक16_t                              mem_latency_high;
	uपूर्णांक16_t                              mem_latency_low;
	uपूर्णांक32_t                              vr_config;
	काष्ठा profile_mode_setting           current_profile_setting;

	uपूर्णांक32_t                              ro_range_minimum;
	uपूर्णांक32_t                              ro_range_maximum;

	bool                                  disable_edc_leakage_controller;
	AtomCtrl_HiLoLeakageOffsetTable       edc_hilo_leakage_offset_from_vbios;
	AtomCtrl_EDCLeakgeTable               edc_leakage_table;
पूर्ण;

/* To convert to Q8.8 क्रमmat क्रम firmware */
#घोषणा SMU7_Q88_FORMAT_CONVERSION_UNIT             256

क्रमागत SMU7_I2CLineID अणु
	SMU7_I2CLineID_DDC1 = 0x90,
	SMU7_I2CLineID_DDC2 = 0x91,
	SMU7_I2CLineID_DDC3 = 0x92,
	SMU7_I2CLineID_DDC4 = 0x93,
	SMU7_I2CLineID_DDC5 = 0x94,
	SMU7_I2CLineID_DDC6 = 0x95,
	SMU7_I2CLineID_SCLSDA = 0x96,
	SMU7_I2CLineID_DDCVGA = 0x97
पूर्ण;

#घोषणा SMU7_I2C_DDC1DATA          0
#घोषणा SMU7_I2C_DDC1CLK           1
#घोषणा SMU7_I2C_DDC2DATA          2
#घोषणा SMU7_I2C_DDC2CLK           3
#घोषणा SMU7_I2C_DDC3DATA          4
#घोषणा SMU7_I2C_DDC3CLK           5
#घोषणा SMU7_I2C_SDA               40
#घोषणा SMU7_I2C_SCL               41
#घोषणा SMU7_I2C_DDC4DATA          65
#घोषणा SMU7_I2C_DDC4CLK           66
#घोषणा SMU7_I2C_DDC5DATA          0x48
#घोषणा SMU7_I2C_DDC5CLK           0x49
#घोषणा SMU7_I2C_DDC6DATA          0x4a
#घोषणा SMU7_I2C_DDC6CLK           0x4b
#घोषणा SMU7_I2C_DDCVGADATA        0x4c
#घोषणा SMU7_I2C_DDCVGACLK         0x4d

#घोषणा SMU7_UNUSED_GPIO_PIN       0x7F
uपूर्णांक8_t smu7_get_sleep_भागider_id_from_घड़ी(uपूर्णांक32_t घड़ी,
		uपूर्णांक32_t घड़ी_insr);
#पूर्ण_अगर

