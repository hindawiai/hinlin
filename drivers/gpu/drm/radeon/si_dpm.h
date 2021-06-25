<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __SI_DPM_H__
#घोषणा __SI_DPM_H__

#समावेश "ni_dpm.h"
#समावेश "sislands_smc.h"

क्रमागत si_cac_config_reg_type
अणु
	SISLANDS_CACCONFIG_MMR = 0,
	SISLANDS_CACCONFIG_CGIND,
	SISLANDS_CACCONFIG_MAX
पूर्ण;

काष्ठा si_cac_config_reg
अणु
	u32 offset;
	u32 mask;
	u32 shअगरt;
	u32 value;
	क्रमागत si_cac_config_reg_type type;
पूर्ण;

काष्ठा si_घातertune_data
अणु
	u32 cac_winकरोw;
	u32 l2_lta_winकरोw_size_शेष;
	u8 lts_truncate_शेष;
	u8 shअगरt_n_शेष;
	u8 operating_temp;
	काष्ठा ni_leakage_coeffients leakage_coefficients;
	u32 fixed_kt;
	u32 lkge_lut_v0_percent;
	u8 dc_cac[NISLANDS_DCCAC_MAX_LEVELS];
	bool enable_घातertune_by_शेष;
पूर्ण;

काष्ठा si_dyn_घातertune_data
अणु
	u32 cac_leakage;
	s32 leakage_minimum_temperature;
	u32 wपूर्णांकime;
	u32 l2_lta_winकरोw_size;
	u8 lts_truncate;
	u8 shअगरt_n;
	u8 dc_pwr_value;
	bool disable_uvd_घातertune;
पूर्ण;

काष्ठा si_dte_data
अणु
	u32 tau[SMC_SISLANDS_DTE_MAX_FILTER_STAGES];
	u32 r[SMC_SISLANDS_DTE_MAX_FILTER_STAGES];
	u32 k;
	u32 t0;
	u32 max_t;
	u8 winकरोw_size;
	u8 temp_select;
	u8 dte_mode;
	u8 tdep_count;
	u8 t_limits[SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE];
	u32 tdep_tau[SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE];
	u32 tdep_r[SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE];
	u32 t_threshold;
	bool enable_dte_by_शेष;
पूर्ण;

काष्ठा si_घड़ी_रेजिस्टरs अणु
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

काष्ठा si_mc_reg_entry अणु
	u32 mclk_max;
	u32 mc_data[SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा si_mc_reg_table अणु
	u8 last;
	u8 num_entries;
	u16 valid_flag;
	काष्ठा si_mc_reg_entry mc_reg_table_entry[MAX_AC_TIMING_ENTRIES];
	SMC_NIslands_MCRegisterAddress mc_reg_address[SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

#घोषणा SISLANDS_MCREGISTERTABLE_INITIAL_SLOT               0
#घोषणा SISLANDS_MCREGISTERTABLE_ACPI_SLOT                  1
#घोषणा SISLANDS_MCREGISTERTABLE_ULV_SLOT                   2
#घोषणा SISLANDS_MCREGISTERTABLE_FIRST_DRIVERSTATE_SLOT     3

काष्ठा si_leakage_voltage_entry
अणु
	u16 voltage;
	u16 leakage_index;
पूर्ण;

#घोषणा SISLANDS_LEAKAGE_INDEX0     0xff01
#घोषणा SISLANDS_MAX_LEAKAGE_COUNT  4

काष्ठा si_leakage_voltage
अणु
	u16 count;
	काष्ठा si_leakage_voltage_entry entries[SISLANDS_MAX_LEAKAGE_COUNT];
पूर्ण;

#घोषणा SISLANDS_MAX_HARDWARE_POWERLEVELS 5

काष्ठा si_ulv_param अणु
	bool supported;
	u32 cg_ulv_control;
	u32 cg_ulv_parameter;
	u32 volt_change_delay;
	काष्ठा rv7xx_pl pl;
	bool one_pcie_lane_in_ulv;
पूर्ण;

काष्ठा si_घातer_info अणु
	/* must be first! */
	काष्ठा ni_घातer_info ni;
	काष्ठा si_घड़ी_रेजिस्टरs घड़ी_रेजिस्टरs;
	काष्ठा si_mc_reg_table mc_reg_table;
	काष्ठा atom_voltage_table mvdd_voltage_table;
	काष्ठा atom_voltage_table vddc_phase_shed_table;
	काष्ठा si_leakage_voltage leakage_voltage;
	u16 mvdd_bootup_value;
	काष्ठा si_ulv_param ulv;
	u32 max_cu;
	/* pcie gen */
	क्रमागत radeon_pcie_gen क्रमce_pcie_gen;
	क्रमागत radeon_pcie_gen boot_pcie_gen;
	क्रमागत radeon_pcie_gen acpi_pcie_gen;
	u32 sys_pcie_mask;
	/* flags */
	bool enable_dte;
	bool enable_ppm;
	bool vddc_phase_shed_control;
	bool pspp_notअगरy_required;
	bool sclk_deep_sleep_above_low;
	bool voltage_control_svi2;
	bool vddci_control_svi2;
	/* smc offsets */
	u32 sram_end;
	u32 state_table_start;
	u32 soft_regs_start;
	u32 mc_reg_table_start;
	u32 arb_table_start;
	u32 cac_table_start;
	u32 dte_table_start;
	u32 spll_table_start;
	u32 papm_cfg_table_start;
	u32 fan_table_start;
	/* CAC stuff */
	स्थिर काष्ठा si_cac_config_reg *cac_weights;
	स्थिर काष्ठा si_cac_config_reg *lcac_config;
	स्थिर काष्ठा si_cac_config_reg *cac_override;
	स्थिर काष्ठा si_घातertune_data *घातertune_data;
	काष्ठा si_dyn_घातertune_data dyn_घातertune_data;
	/* DTE stuff */
	काष्ठा si_dte_data dte_data;
	/* scratch काष्ठाs */
	SMC_SIslands_MCRegisters smc_mc_reg_table;
	SISLANDS_SMC_STATETABLE smc_statetable;
	PP_SIslands_PAPMParameters papm_parm;
	/* SVI2 */
	u8 svd_gpio_id;
	u8 svc_gpio_id;
	/* fan control */
	bool fan_ctrl_is_in_शेष_mode;
	u32 t_min;
	u32 fan_ctrl_शेष_mode;
	bool fan_is_controlled_by_smc;
पूर्ण;

#घोषणा SISLANDS_INITIAL_STATE_ARB_INDEX    0
#घोषणा SISLANDS_ACPI_STATE_ARB_INDEX       1
#घोषणा SISLANDS_ULV_STATE_ARB_INDEX        2
#घोषणा SISLANDS_DRIVER_STATE_ARB_INDEX     3

#घोषणा SISLANDS_DPM2_MAX_PULSE_SKIP        256

#घोषणा SISLANDS_DPM2_NEAR_TDP_DEC          10
#घोषणा SISLANDS_DPM2_ABOVE_SAFE_INC        5
#घोषणा SISLANDS_DPM2_BELOW_SAFE_INC        20

#घोषणा SISLANDS_DPM2_TDP_SAFE_LIMIT_PERCENT            80

#घोषणा SISLANDS_DPM2_MAXPS_PERCENT_H                   99
#घोषणा SISLANDS_DPM2_MAXPS_PERCENT_M                   99

#घोषणा SISLANDS_DPM2_SQ_RAMP_MAX_POWER                 0x3FFF
#घोषणा SISLANDS_DPM2_SQ_RAMP_MIN_POWER                 0x12
#घोषणा SISLANDS_DPM2_SQ_RAMP_MAX_POWER_DELTA           0x15
#घोषणा SISLANDS_DPM2_SQ_RAMP_STI_SIZE                  0x1E
#घोषणा SISLANDS_DPM2_SQ_RAMP_LTI_RATIO                 0xF

#घोषणा SISLANDS_DPM2_PWREFFICIENCYRATIO_MARGIN         10

#घोषणा SISLANDS_VRC_DFLT                               0xC000B3
#घोषणा SISLANDS_ULVVOLTAGECHANGEDELAY_DFLT             1687
#घोषणा SISLANDS_CGULVPARAMETER_DFLT                    0x00040035
#घोषणा SISLANDS_CGULVCONTROL_DFLT                      0x1f007550

u8 si_get_ddr3_mclk_frequency_ratio(u32 memory_घड़ी);
u8 si_get_mclk_frequency_ratio(u32 memory_घड़ी, bool strobe_mode);
व्योम si_trim_voltage_table_to_fit_state_table(काष्ठा radeon_device *rdev,
					      u32 max_voltage_steps,
					      काष्ठा atom_voltage_table *voltage_table);

#पूर्ण_अगर
