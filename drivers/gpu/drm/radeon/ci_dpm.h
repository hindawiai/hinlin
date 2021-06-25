<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __CI_DPM_H__
#घोषणा __CI_DPM_H__

#समावेश "ppsmc.h"
#समावेश "radeon.h"

#घोषणा SMU__NUM_SCLK_DPM_STATE  8
#घोषणा SMU__NUM_MCLK_DPM_LEVELS 6
#घोषणा SMU__NUM_LCLK_DPM_LEVELS 8
#घोषणा SMU__NUM_PCIE_DPM_LEVELS 8
#समावेश "smu7_discrete.h"

#घोषणा CISLANDS_MAX_HARDWARE_POWERLEVELS 2

#घोषणा CISLANDS_UNUSED_GPIO_PIN 0x7F

काष्ठा ci_pl अणु
	u32 mclk;
	u32 sclk;
	क्रमागत radeon_pcie_gen pcie_gen;
	u16 pcie_lane;
पूर्ण;

काष्ठा ci_ps अणु
	u16 perक्रमmance_level_count;
	bool dc_compatible;
	u32 sclk_t;
	काष्ठा ci_pl perक्रमmance_levels[CISLANDS_MAX_HARDWARE_POWERLEVELS];
पूर्ण;

काष्ठा ci_dpm_level अणु
	bool enabled;
	u32 value;
	u32 param1;
पूर्ण;

#घोषणा CISLAND_MAX_DEEPSLEEP_DIVIDER_ID 5
#घोषणा MAX_REGULAR_DPM_NUMBER 8
#घोषणा CISLAND_MINIMUM_ENGINE_CLOCK 800

काष्ठा ci_single_dpm_table अणु
	u32 count;
	काष्ठा ci_dpm_level dpm_levels[MAX_REGULAR_DPM_NUMBER];
पूर्ण;

काष्ठा ci_dpm_table अणु
	काष्ठा ci_single_dpm_table sclk_table;
	काष्ठा ci_single_dpm_table mclk_table;
	काष्ठा ci_single_dpm_table pcie_speed_table;
	काष्ठा ci_single_dpm_table vddc_table;
	काष्ठा ci_single_dpm_table vddci_table;
	काष्ठा ci_single_dpm_table mvdd_table;
पूर्ण;

काष्ठा ci_mc_reg_entry अणु
	u32 mclk_max;
	u32 mc_data[SMU7_DISCRETE_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा ci_mc_reg_table अणु
	u8 last;
	u8 num_entries;
	u16 valid_flag;
	काष्ठा ci_mc_reg_entry mc_reg_table_entry[MAX_AC_TIMING_ENTRIES];
	SMU7_Discrete_MCRegisterAddress mc_reg_address[SMU7_DISCRETE_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा ci_ulv_parm
अणु
	bool supported;
	u32 cg_ulv_parameter;
	u32 volt_change_delay;
	काष्ठा ci_pl pl;
पूर्ण;

#घोषणा CISLANDS_MAX_LEAKAGE_COUNT  8

काष्ठा ci_leakage_voltage अणु
	u16 count;
	u16 leakage_id[CISLANDS_MAX_LEAKAGE_COUNT];
	u16 actual_voltage[CISLANDS_MAX_LEAKAGE_COUNT];
पूर्ण;

काष्ठा ci_dpm_level_enable_mask अणु
	u32 uvd_dpm_enable_mask;
	u32 vce_dpm_enable_mask;
	u32 acp_dpm_enable_mask;
	u32 samu_dpm_enable_mask;
	u32 sclk_dpm_enable_mask;
	u32 mclk_dpm_enable_mask;
	u32 pcie_dpm_enable_mask;
पूर्ण;

काष्ठा ci_vbios_boot_state
अणु
	u16 mvdd_bootup_value;
	u16 vddc_bootup_value;
	u16 vddci_bootup_value;
	u32 sclk_bootup_value;
	u32 mclk_bootup_value;
	u16 pcie_gen_bootup_value;
	u16 pcie_lane_bootup_value;
पूर्ण;

काष्ठा ci_घड़ी_रेजिस्टरs अणु
	u32 cg_spll_func_cntl;
	u32 cg_spll_func_cntl_2;
	u32 cg_spll_func_cntl_3;
	u32 cg_spll_func_cntl_4;
	u32 cg_spll_spपढ़ो_spectrum;
	u32 cg_spll_spपढ़ो_spectrum_2;
	u32 dll_cntl;
	u32 mclk_pwrmgt_cntl;
	u32 mpll_ad_func_cntl;
	u32 mpll_dq_func_cntl;
	u32 mpll_func_cntl;
	u32 mpll_func_cntl_1;
	u32 mpll_func_cntl_2;
	u32 mpll_ss1;
	u32 mpll_ss2;
पूर्ण;

काष्ठा ci_thermal_temperature_setting अणु
	s32 temperature_low;
	s32 temperature_high;
	s32 temperature_shutकरोwn;
पूर्ण;

काष्ठा ci_pcie_perf_range अणु
	u16 max;
	u16 min;
पूर्ण;

क्रमागत ci_pt_config_reg_type अणु
	CISLANDS_CONFIGREG_MMR = 0,
	CISLANDS_CONFIGREG_SMC_IND,
	CISLANDS_CONFIGREG_DIDT_IND,
	CISLANDS_CONFIGREG_CACHE,
	CISLANDS_CONFIGREG_MAX
पूर्ण;

#घोषणा POWERCONTAINMENT_FEATURE_BAPM            0x00000001
#घोषणा POWERCONTAINMENT_FEATURE_TDCLimit        0x00000002
#घोषणा POWERCONTAINMENT_FEATURE_PkgPwrLimit     0x00000004

काष्ठा ci_pt_config_reg अणु
	u32 offset;
	u32 mask;
	u32 shअगरt;
	u32 value;
	क्रमागत ci_pt_config_reg_type type;
पूर्ण;

काष्ठा ci_pt_शेषs अणु
	u8 svi_load_line_en;
	u8 svi_load_line_vddc;
	u8 tdc_vddc_throttle_release_limit_perc;
	u8 tdc_mawt;
	u8 tdc_waterfall_ctl;
	u8 dte_ambient_temp_base;
	u32 display_cac;
	u32 bapm_temp_gradient;
	u16 bapmti_r[SMU7_DTE_ITERATIONS * SMU7_DTE_SOURCES * SMU7_DTE_SINKS];
	u16 bapmti_rc[SMU7_DTE_ITERATIONS * SMU7_DTE_SOURCES * SMU7_DTE_SINKS];
पूर्ण;

#घोषणा DPMTABLE_OD_UPDATE_SCLK     0x00000001
#घोषणा DPMTABLE_OD_UPDATE_MCLK     0x00000002
#घोषणा DPMTABLE_UPDATE_SCLK        0x00000004
#घोषणा DPMTABLE_UPDATE_MCLK        0x00000008

काष्ठा ci_घातer_info अणु
	काष्ठा ci_dpm_table dpm_table;
	u32 voltage_control;
	u32 mvdd_control;
	u32 vddci_control;
	u32 active_स्वतः_throttle_sources;
	काष्ठा ci_घड़ी_रेजिस्टरs घड़ी_रेजिस्टरs;
	u16 acpi_vddc;
	u16 acpi_vddci;
	क्रमागत radeon_pcie_gen क्रमce_pcie_gen;
	क्रमागत radeon_pcie_gen acpi_pcie_gen;
	काष्ठा ci_leakage_voltage vddc_leakage;
	काष्ठा ci_leakage_voltage vddci_leakage;
	u16 max_vddc_in_pp_table;
	u16 min_vddc_in_pp_table;
	u16 max_vddci_in_pp_table;
	u16 min_vddci_in_pp_table;
	u32 mclk_strobe_mode_threshold;
	u32 mclk_stutter_mode_threshold;
	u32 mclk_edc_enable_threshold;
	u32 mclk_edc_wr_enable_threshold;
	काष्ठा ci_vbios_boot_state vbios_boot_state;
	/* smc offsets */
	u32 sram_end;
	u32 dpm_table_start;
	u32 soft_regs_start;
	u32 mc_reg_table_start;
	u32 fan_table_start;
	u32 arb_table_start;
	/* smc tables */
	SMU7_Discrete_DpmTable smc_state_table;
	SMU7_Discrete_MCRegisters smc_mc_reg_table;
	SMU7_Discrete_PmFuses smc_घातertune_table;
	/* other stuff */
	काष्ठा ci_mc_reg_table mc_reg_table;
	काष्ठा atom_voltage_table vddc_voltage_table;
	काष्ठा atom_voltage_table vddci_voltage_table;
	काष्ठा atom_voltage_table mvdd_voltage_table;
	काष्ठा ci_ulv_parm ulv;
	u32 घातer_containment_features;
	स्थिर काष्ठा ci_pt_शेषs *घातertune_शेषs;
	u32 dte_tj_offset;
	bool vddc_phase_shed_control;
	काष्ठा ci_thermal_temperature_setting thermal_temp_setting;
	काष्ठा ci_dpm_level_enable_mask dpm_level_enable_mask;
	u32 need_update_smu7_dpm_table;
	u32 sclk_dpm_key_disabled;
	u32 mclk_dpm_key_disabled;
	u32 pcie_dpm_key_disabled;
	u32 thermal_sclk_dpm_enabled;
	काष्ठा ci_pcie_perf_range pcie_gen_perक्रमmance;
	काष्ठा ci_pcie_perf_range pcie_lane_perक्रमmance;
	काष्ठा ci_pcie_perf_range pcie_gen_घातersaving;
	काष्ठा ci_pcie_perf_range pcie_lane_घातersaving;
	u32 activity_target[SMU7_MAX_LEVELS_GRAPHICS];
	u32 mclk_activity_target;
	u32 low_sclk_पूर्णांकerrupt_t;
	u32 last_mclk_dpm_enable_mask;
	u32 sys_pcie_mask;
	/* caps */
	bool caps_घातer_containment;
	bool caps_cac;
	bool caps_sq_ramping;
	bool caps_db_ramping;
	bool caps_td_ramping;
	bool caps_tcp_ramping;
	bool caps_fps;
	bool caps_sclk_ds;
	bool caps_sclk_ss_support;
	bool caps_mclk_ss_support;
	bool caps_uvd_dpm;
	bool caps_vce_dpm;
	bool caps_samu_dpm;
	bool caps_acp_dpm;
	bool caps_स्वतःmatic_dc_transition;
	bool caps_sclk_throttle_low_notअगरication;
	bool caps_dynamic_ac_timing;
	bool caps_od_fuzzy_fan_control_support;
	/* flags */
	bool thermal_protection;
	bool pcie_perक्रमmance_request;
	bool dynamic_ss;
	bool dll_शेष_on;
	bool cac_enabled;
	bool uvd_enabled;
	bool battery_state;
	bool pspp_notअगरy_required;
	bool mem_gddr5;
	bool enable_bapm_feature;
	bool enable_tdc_limit_feature;
	bool enable_pkg_pwr_tracking_feature;
	bool use_pcie_perक्रमmance_levels;
	bool use_pcie_घातersaving_levels;
	bool uvd_घातer_gated;
	/* driver states */
	काष्ठा radeon_ps current_rps;
	काष्ठा ci_ps current_ps;
	काष्ठा radeon_ps requested_rps;
	काष्ठा ci_ps requested_ps;
	/* fan control */
	bool fan_ctrl_is_in_शेष_mode;
	bool fan_is_controlled_by_smc;
	u32 t_min;
	u32 fan_ctrl_शेष_mode;
पूर्ण;

#घोषणा CISLANDS_VOLTAGE_CONTROL_NONE                   0x0
#घोषणा CISLANDS_VOLTAGE_CONTROL_BY_GPIO                0x1
#घोषणा CISLANDS_VOLTAGE_CONTROL_BY_SVID2               0x2

#घोषणा CISLANDS_Q88_FORMAT_CONVERSION_UNIT             256

#घोषणा CISLANDS_VRC_DFLT0                              0x3FFFC000
#घोषणा CISLANDS_VRC_DFLT1                              0x000400
#घोषणा CISLANDS_VRC_DFLT2                              0xC00080
#घोषणा CISLANDS_VRC_DFLT3                              0xC00200
#घोषणा CISLANDS_VRC_DFLT4                              0xC01680
#घोषणा CISLANDS_VRC_DFLT5                              0xC00033
#घोषणा CISLANDS_VRC_DFLT6                              0xC00033
#घोषणा CISLANDS_VRC_DFLT7                              0x3FFFC000

#घोषणा CISLANDS_CGULVPARAMETER_DFLT                    0x00040035
#घोषणा CISLAND_TARGETACTIVITY_DFLT                     30
#घोषणा CISLAND_MCLK_TARGETACTIVITY_DFLT                10

#घोषणा PCIE_PERF_REQ_REMOVE_REGISTRY   0
#घोषणा PCIE_PERF_REQ_FORCE_LOWPOWER    1
#घोषणा PCIE_PERF_REQ_PECI_GEN1         2
#घोषणा PCIE_PERF_REQ_PECI_GEN2         3
#घोषणा PCIE_PERF_REQ_PECI_GEN3         4

पूर्णांक ci_copy_bytes_to_smc(काष्ठा radeon_device *rdev,
			 u32 smc_start_address,
			 स्थिर u8 *src, u32 byte_count, u32 limit);
व्योम ci_start_smc(काष्ठा radeon_device *rdev);
व्योम ci_reset_smc(काष्ठा radeon_device *rdev);
पूर्णांक ci_program_jump_on_start(काष्ठा radeon_device *rdev);
व्योम ci_stop_smc_घड़ी(काष्ठा radeon_device *rdev);
व्योम ci_start_smc_घड़ी(काष्ठा radeon_device *rdev);
bool ci_is_smc_running(काष्ठा radeon_device *rdev);
PPSMC_Result ci_रुको_क्रम_smc_inactive(काष्ठा radeon_device *rdev);
पूर्णांक ci_load_smc_ucode(काष्ठा radeon_device *rdev, u32 limit);
पूर्णांक ci_पढ़ो_smc_sram_dword(काष्ठा radeon_device *rdev,
			   u32 smc_address, u32 *value, u32 limit);
पूर्णांक ci_ग_लिखो_smc_sram_dword(काष्ठा radeon_device *rdev,
			    u32 smc_address, u32 value, u32 limit);

#पूर्ण_अगर
