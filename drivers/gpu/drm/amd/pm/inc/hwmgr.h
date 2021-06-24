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
#अगर_अघोषित _HWMGR_H_
#घोषणा _HWMGR_H_

#समावेश <linux/seq_file.h>
#समावेश "amd_powerplay.h"
#समावेश "hardwaremanager.h"
#समावेश "hwmgr_ppt.h"
#समावेश "ppatomctrl.h"
#समावेश "power_state.h"
#समावेश "smu_helper.h"

काष्ठा pp_hwmgr;
काष्ठा phm_fan_speed_info;
काष्ठा pp_atomctrl_voltage_table;

#घोषणा VOLTAGE_SCALE 4
#घोषणा VOLTAGE_VID_OFFSET_SCALE1   625
#घोषणा VOLTAGE_VID_OFFSET_SCALE2   100

क्रमागत DISPLAY_GAP अणु
	DISPLAY_GAP_VBLANK_OR_WM = 0,   /* Wait क्रम vblank or MCHG watermark. */
	DISPLAY_GAP_VBLANK       = 1,   /* Wait क्रम vblank. */
	DISPLAY_GAP_WATERMARK    = 2,   /* Wait क्रम MCHG watermark. (Note that HW may deनिश्चित WM in VBI depending on DC_STUTTER_CNTL.) */
	DISPLAY_GAP_IGNORE       = 3    /* Do not रुको. */
पूर्ण;
प्रकार क्रमागत DISPLAY_GAP DISPLAY_GAP;

क्रमागत BACO_STATE अणु
	BACO_STATE_OUT = 0,
	BACO_STATE_IN,
पूर्ण;

काष्ठा vi_dpm_level अणु
	bool enabled;
	uपूर्णांक32_t value;
	uपूर्णांक32_t param1;
पूर्ण;

काष्ठा vi_dpm_table अणु
	uपूर्णांक32_t count;
	काष्ठा vi_dpm_level dpm_level[];
पूर्ण;

#घोषणा PCIE_PERF_REQ_REMOVE_REGISTRY   0
#घोषणा PCIE_PERF_REQ_FORCE_LOWPOWER    1
#घोषणा PCIE_PERF_REQ_GEN1         2
#घोषणा PCIE_PERF_REQ_GEN2         3
#घोषणा PCIE_PERF_REQ_GEN3         4

क्रमागत PHM_BackEnd_Magic अणु
	PHM_Dummy_Magic       = 0xAA5555AA,
	PHM_RV770_Magic       = 0xDCBAABCD,
	PHM_Kong_Magic        = 0x239478DF,
	PHM_NIslands_Magic    = 0x736C494E,
	PHM_Sumo_Magic        = 0x8339FA11,
	PHM_SIslands_Magic    = 0x369431AC,
	PHM_Trinity_Magic     = 0x96751873,
	PHM_CIslands_Magic    = 0x38AC78B0,
	PHM_Kv_Magic          = 0xDCBBABC0,
	PHM_VIslands_Magic    = 0x20130307,
	PHM_Cz_Magic          = 0x67DCBA25,
	PHM_Rv_Magic          = 0x20161121
पूर्ण;

काष्ठा phm_set_घातer_state_input अणु
	स्थिर काष्ठा pp_hw_घातer_state *pcurrent_state;
	स्थिर काष्ठा pp_hw_घातer_state *pnew_state;
पूर्ण;

काष्ठा phm_घड़ी_array अणु
	uपूर्णांक32_t count;
	uपूर्णांक32_t values[];
पूर्ण;

काष्ठा phm_घड़ी_voltage_dependency_record अणु
	uपूर्णांक32_t clk;
	uपूर्णांक32_t v;
पूर्ण;

काष्ठा phm_vceघड़ी_voltage_dependency_record अणु
	uपूर्णांक32_t ecclk;
	uपूर्णांक32_t evclk;
	uपूर्णांक32_t v;
पूर्ण;

काष्ठा phm_uvdघड़ी_voltage_dependency_record अणु
	uपूर्णांक32_t vclk;
	uपूर्णांक32_t dclk;
	uपूर्णांक32_t v;
पूर्ण;

काष्ठा phm_samuघड़ी_voltage_dependency_record अणु
	uपूर्णांक32_t samclk;
	uपूर्णांक32_t v;
पूर्ण;

काष्ठा phm_acpघड़ी_voltage_dependency_record अणु
	uपूर्णांक32_t acpclk;
	uपूर्णांक32_t v;
पूर्ण;

काष्ठा phm_घड़ी_voltage_dependency_table अणु
	uपूर्णांक32_t count;							/* Number of entries. */
	काष्ठा phm_घड़ी_voltage_dependency_record entries[];		/* Dynamically allocate count entries. */
पूर्ण;

काष्ठा phm_phase_shedding_limits_record अणु
	uपूर्णांक32_t  Voltage;
	uपूर्णांक32_t    Sclk;
	uपूर्णांक32_t    Mclk;
पूर्ण;

काष्ठा phm_uvd_घड़ी_voltage_dependency_record अणु
	uपूर्णांक32_t vclk;
	uपूर्णांक32_t dclk;
	uपूर्णांक32_t v;
पूर्ण;

काष्ठा phm_uvd_घड़ी_voltage_dependency_table अणु
	uपूर्णांक8_t count;
	काष्ठा phm_uvd_घड़ी_voltage_dependency_record entries[];
पूर्ण;

काष्ठा phm_acp_घड़ी_voltage_dependency_record अणु
	uपूर्णांक32_t acpclk;
	uपूर्णांक32_t v;
पूर्ण;

काष्ठा phm_acp_घड़ी_voltage_dependency_table अणु
	uपूर्णांक32_t count;
	काष्ठा phm_acp_घड़ी_voltage_dependency_record entries[];
पूर्ण;

काष्ठा phm_vce_घड़ी_voltage_dependency_record अणु
	uपूर्णांक32_t ecclk;
	uपूर्णांक32_t evclk;
	uपूर्णांक32_t v;
पूर्ण;

काष्ठा phm_phase_shedding_limits_table अणु
	uपूर्णांक32_t                           count;
	काष्ठा phm_phase_shedding_limits_record  entries[];
पूर्ण;

काष्ठा phm_vceघड़ी_voltage_dependency_table अणु
	uपूर्णांक8_t count;                                    /* Number of entries. */
	काष्ठा phm_vceघड़ी_voltage_dependency_record entries[1]; /* Dynamically allocate count entries. */
पूर्ण;

काष्ठा phm_uvdघड़ी_voltage_dependency_table अणु
	uपूर्णांक8_t count;                                    /* Number of entries. */
	काष्ठा phm_uvdघड़ी_voltage_dependency_record entries[1]; /* Dynamically allocate count entries. */
पूर्ण;

काष्ठा phm_samuघड़ी_voltage_dependency_table अणु
	uपूर्णांक8_t count;                                    /* Number of entries. */
	काष्ठा phm_samuघड़ी_voltage_dependency_record entries[1]; /* Dynamically allocate count entries. */
पूर्ण;

काष्ठा phm_acpघड़ी_voltage_dependency_table अणु
	uपूर्णांक32_t count;                                    /* Number of entries. */
	काष्ठा phm_acpघड़ी_voltage_dependency_record entries[1]; /* Dynamically allocate count entries. */
पूर्ण;

काष्ठा phm_vce_घड़ी_voltage_dependency_table अणु
	uपूर्णांक8_t count;
	काष्ठा phm_vce_घड़ी_voltage_dependency_record entries[];
पूर्ण;


क्रमागत SMU_ASIC_RESET_MODE
अणु
    SMU_ASIC_RESET_MODE_0,
    SMU_ASIC_RESET_MODE_1,
    SMU_ASIC_RESET_MODE_2,
पूर्ण;

काष्ठा pp_smumgr_func अणु
	अक्षर *name;
	पूर्णांक (*smu_init)(काष्ठा pp_hwmgr  *hwmgr);
	पूर्णांक (*smu_fini)(काष्ठा pp_hwmgr  *hwmgr);
	पूर्णांक (*start_smu)(काष्ठा pp_hwmgr  *hwmgr);
	पूर्णांक (*check_fw_load_finish)(काष्ठा pp_hwmgr  *hwmgr,
				    uपूर्णांक32_t firmware);
	पूर्णांक (*request_smu_load_fw)(काष्ठा pp_hwmgr  *hwmgr);
	पूर्णांक (*request_smu_load_specअगरic_fw)(काष्ठा pp_hwmgr  *hwmgr,
					    uपूर्णांक32_t firmware);
	uपूर्णांक32_t (*get_argument)(काष्ठा pp_hwmgr  *hwmgr);
	पूर्णांक (*send_msg_to_smc)(काष्ठा pp_hwmgr  *hwmgr, uपूर्णांक16_t msg);
	पूर्णांक (*send_msg_to_smc_with_parameter)(काष्ठा pp_hwmgr  *hwmgr,
					  uपूर्णांक16_t msg, uपूर्णांक32_t parameter);
	पूर्णांक (*करोwnload_pptable_settings)(काष्ठा pp_hwmgr  *hwmgr,
					 व्योम **table);
	पूर्णांक (*upload_pptable_settings)(काष्ठा pp_hwmgr  *hwmgr);
	पूर्णांक (*update_smc_table)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t type);
	पूर्णांक (*process_firmware_header)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*update_sclk_threshold)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*thermal_setup_fan_table)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*thermal_avfs_enable)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*init_smc_table)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*populate_all_graphic_levels)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*populate_all_memory_levels)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*initialize_mc_reg_table)(काष्ठा pp_hwmgr *hwmgr);
	uपूर्णांक32_t (*get_दुरत्व)(uपूर्णांक32_t type, uपूर्णांक32_t member);
	uपूर्णांक32_t (*get_mac_definition)(uपूर्णांक32_t value);
	bool (*is_dpm_running)(काष्ठा pp_hwmgr *hwmgr);
	bool (*is_hw_avfs_present)(काष्ठा pp_hwmgr  *hwmgr);
	पूर्णांक (*update_dpm_settings)(काष्ठा pp_hwmgr *hwmgr, व्योम *profile_setting);
	पूर्णांक (*smc_table_manager)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t *table, uपूर्णांक16_t table_id, bool rw); /*rw: true क्रम पढ़ो, false क्रम ग_लिखो */
	पूर्णांक (*stop_smc)(काष्ठा pp_hwmgr *hwmgr);
पूर्ण;

काष्ठा pp_hwmgr_func अणु
	पूर्णांक (*backend_init)(काष्ठा pp_hwmgr *hw_mgr);
	पूर्णांक (*backend_fini)(काष्ठा pp_hwmgr *hw_mgr);
	पूर्णांक (*asic_setup)(काष्ठा pp_hwmgr *hw_mgr);
	पूर्णांक (*get_घातer_state_size)(काष्ठा pp_hwmgr *hw_mgr);

	पूर्णांक (*apply_state_adjust_rules)(काष्ठा pp_hwmgr *hwmgr,
				काष्ठा pp_घातer_state  *prequest_ps,
			स्थिर काष्ठा pp_घातer_state *pcurrent_ps);

	पूर्णांक (*apply_घड़ीs_adjust_rules)(काष्ठा pp_hwmgr *hwmgr);

	पूर्णांक (*क्रमce_dpm_level)(काष्ठा pp_hwmgr *hw_mgr,
					क्रमागत amd_dpm_क्रमced_level level);

	पूर्णांक (*dynamic_state_management_enable)(
						काष्ठा pp_hwmgr *hw_mgr);
	पूर्णांक (*dynamic_state_management_disable)(
						काष्ठा pp_hwmgr *hw_mgr);

	पूर्णांक (*patch_boot_state)(काष्ठा pp_hwmgr *hwmgr,
				     काष्ठा pp_hw_घातer_state *hw_ps);

	पूर्णांक (*get_pp_table_entry)(काष्ठा pp_hwmgr *hwmgr,
			    अचिन्हित दीर्घ, काष्ठा pp_घातer_state *);
	पूर्णांक (*get_num_of_pp_table_entries)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*घातerकरोwn_uvd)(काष्ठा pp_hwmgr *hwmgr);
	व्योम (*घातergate_vce)(काष्ठा pp_hwmgr *hwmgr, bool bgate);
	व्योम (*घातergate_uvd)(काष्ठा pp_hwmgr *hwmgr, bool bgate);
	व्योम (*घातergate_acp)(काष्ठा pp_hwmgr *hwmgr, bool bgate);
	uपूर्णांक32_t (*get_mclk)(काष्ठा pp_hwmgr *hwmgr, bool low);
	uपूर्णांक32_t (*get_sclk)(काष्ठा pp_hwmgr *hwmgr, bool low);
	पूर्णांक (*घातer_state_set)(काष्ठा pp_hwmgr *hwmgr,
						स्थिर व्योम *state);
	पूर्णांक (*notअगरy_smc_display_config_after_ps_adjusपंचांगent)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*pre_display_config_changed)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*display_config_changed)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*disable_घड़ी_घातer_gating)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*update_घड़ी_gatings)(काष्ठा pp_hwmgr *hwmgr,
						स्थिर uपूर्णांक32_t *msg_id);
	पूर्णांक (*set_max_fan_rpm_output)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t us_max_fan_pwm);
	पूर्णांक (*set_max_fan_pwm_output)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t us_max_fan_pwm);
	पूर्णांक (*stop_thermal_controller)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*get_fan_speed_info)(काष्ठा pp_hwmgr *hwmgr, काष्ठा phm_fan_speed_info *fan_speed_info);
	व्योम (*set_fan_control_mode)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t mode);
	uपूर्णांक32_t (*get_fan_control_mode)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*set_fan_speed_percent)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t percent);
	पूर्णांक (*get_fan_speed_percent)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *speed);
	पूर्णांक (*set_fan_speed_rpm)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t percent);
	पूर्णांक (*get_fan_speed_rpm)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *speed);
	पूर्णांक (*reset_fan_speed_to_शेष)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*uninitialize_thermal_controller)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*रेजिस्टर_irq_handlers)(काष्ठा pp_hwmgr *hwmgr);
	bool (*check_smc_update_required_क्रम_display_configuration)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*check_states_equal)(काष्ठा pp_hwmgr *hwmgr,
					स्थिर काष्ठा pp_hw_घातer_state *pstate1,
					स्थिर काष्ठा pp_hw_घातer_state *pstate2,
					bool *equal);
	पूर्णांक (*set_cpu_घातer_state)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*store_cc6_data)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t separation_समय,
				bool cc6_disable, bool pstate_disable,
				bool pstate_चयन_disable);
	पूर्णांक (*get_dal_घातer_level)(काष्ठा pp_hwmgr *hwmgr,
			काष्ठा amd_pp_simple_घड़ी_info *info);
	पूर्णांक (*get_perक्रमmance_level)(काष्ठा pp_hwmgr *, स्थिर काष्ठा pp_hw_घातer_state *,
			PHM_Perक्रमmanceLevelDesignation, uपूर्णांक32_t, PHM_Perक्रमmanceLevel *);
	पूर्णांक (*get_current_shallow_sleep_घड़ीs)(काष्ठा pp_hwmgr *hwmgr,
				स्थिर काष्ठा pp_hw_घातer_state *state, काष्ठा pp_घड़ी_info *घड़ी_info);
	पूर्णांक (*get_घड़ी_by_type)(काष्ठा pp_hwmgr *hwmgr, क्रमागत amd_pp_घड़ी_प्रकारype type, काष्ठा amd_pp_घड़ीs *घड़ीs);
	पूर्णांक (*get_घड़ी_by_type_with_latency)(काष्ठा pp_hwmgr *hwmgr,
			क्रमागत amd_pp_घड़ी_प्रकारype type,
			काष्ठा pp_घड़ी_levels_with_latency *घड़ीs);
	पूर्णांक (*get_घड़ी_by_type_with_voltage)(काष्ठा pp_hwmgr *hwmgr,
			क्रमागत amd_pp_घड़ी_प्रकारype type,
			काष्ठा pp_घड़ी_levels_with_voltage *घड़ीs);
	पूर्णांक (*set_watermarks_क्रम_घड़ीs_ranges)(काष्ठा pp_hwmgr *hwmgr, व्योम *घड़ी_ranges);
	पूर्णांक (*display_घड़ी_voltage_request)(काष्ठा pp_hwmgr *hwmgr,
			काष्ठा pp_display_घड़ी_request *घड़ी);
	पूर्णांक (*get_max_high_घड़ीs)(काष्ठा pp_hwmgr *hwmgr, काष्ठा amd_pp_simple_घड़ी_info *घड़ीs);
	पूर्णांक (*घातer_off_asic)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*क्रमce_घड़ी_level)(काष्ठा pp_hwmgr *hwmgr, क्रमागत pp_घड़ी_प्रकारype type, uपूर्णांक32_t mask);
	पूर्णांक (*prपूर्णांक_घड़ी_levels)(काष्ठा pp_hwmgr *hwmgr, क्रमागत pp_घड़ी_प्रकारype type, अक्षर *buf);
	पूर्णांक (*घातergate_gfx)(काष्ठा pp_hwmgr *hwmgr, bool enable);
	पूर्णांक (*get_sclk_od)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*set_sclk_od)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t value);
	पूर्णांक (*get_mclk_od)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*set_mclk_od)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t value);
	पूर्णांक (*पढ़ो_sensor)(काष्ठा pp_hwmgr *hwmgr, पूर्णांक idx, व्योम *value, पूर्णांक *size);
	पूर्णांक (*avfs_control)(काष्ठा pp_hwmgr *hwmgr, bool enable);
	पूर्णांक (*disable_smc_firmware_ctf)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*set_active_display_count)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t count);
	पूर्णांक (*set_min_deep_sleep_dcefclk)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी);
	पूर्णांक (*start_thermal_controller)(काष्ठा pp_hwmgr *hwmgr, काष्ठा PP_TemperatureRange *range);
	पूर्णांक (*notअगरy_cac_buffer_info)(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक32_t भव_addr_low,
					uपूर्णांक32_t भव_addr_hi,
					uपूर्णांक32_t mc_addr_low,
					uपूर्णांक32_t mc_addr_hi,
					uपूर्णांक32_t size);
	पूर्णांक (*update_nbdpm_pstate)(काष्ठा pp_hwmgr *hwmgr,
					bool enable,
					bool lock);
	पूर्णांक (*get_thermal_temperature_range)(काष्ठा pp_hwmgr *hwmgr,
					काष्ठा PP_TemperatureRange *range);
	पूर्णांक (*get_घातer_profile_mode)(काष्ठा pp_hwmgr *hwmgr, अक्षर *buf);
	पूर्णांक (*set_घातer_profile_mode)(काष्ठा pp_hwmgr *hwmgr, दीर्घ *input, uपूर्णांक32_t size);
	पूर्णांक (*odn_edit_dpm_table)(काष्ठा pp_hwmgr *hwmgr,
					क्रमागत PP_OD_DPM_TABLE_COMMAND type,
					दीर्घ *input, uपूर्णांक32_t size);
	पूर्णांक (*set_fine_grain_clk_vol)(काष्ठा pp_hwmgr *hwmgr,
				      क्रमागत PP_OD_DPM_TABLE_COMMAND type,
				      दीर्घ *input, uपूर्णांक32_t size);
	पूर्णांक (*set_घातer_limit)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t n);
	पूर्णांक (*घातergate_mmhub)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*smus_notअगरy_pwe)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*घातergate_sdma)(काष्ठा pp_hwmgr *hwmgr, bool bgate);
	पूर्णांक (*enable_mgpu_fan_boost)(काष्ठा pp_hwmgr *hwmgr);
	पूर्णांक (*set_hard_min_dcefclk_by_freq)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी);
	पूर्णांक (*set_hard_min_fclk_by_freq)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी);
	पूर्णांक (*set_hard_min_gfxclk_by_freq)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी);
	पूर्णांक (*set_soft_max_gfxclk_by_freq)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी);
	पूर्णांक (*get_asic_baco_capability)(काष्ठा pp_hwmgr *hwmgr, bool *cap);
	पूर्णांक (*get_asic_baco_state)(काष्ठा pp_hwmgr *hwmgr, क्रमागत BACO_STATE *state);
	पूर्णांक (*set_asic_baco_state)(काष्ठा pp_hwmgr *hwmgr, क्रमागत BACO_STATE state);
	पूर्णांक (*get_ppfeature_status)(काष्ठा pp_hwmgr *hwmgr, अक्षर *buf);
	पूर्णांक (*set_ppfeature_status)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक64_t ppfeature_masks);
	पूर्णांक (*set_mp1_state)(काष्ठा pp_hwmgr *hwmgr, क्रमागत pp_mp1_state mp1_state);
	पूर्णांक (*asic_reset)(काष्ठा pp_hwmgr *hwmgr, क्रमागत SMU_ASIC_RESET_MODE mode);
	पूर्णांक (*smu_i2c_bus_access)(काष्ठा pp_hwmgr *hwmgr, bool aquire);
	पूर्णांक (*set_df_cstate)(काष्ठा pp_hwmgr *hwmgr, क्रमागत pp_df_cstate state);
	पूर्णांक (*set_xgmi_pstate)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t pstate);
	पूर्णांक (*disable_घातer_features_क्रम_compute_perक्रमmance)(काष्ठा pp_hwmgr *hwmgr,
					bool disable);
	sमाप_प्रकार (*get_gpu_metrics)(काष्ठा pp_hwmgr *hwmgr, व्योम **table);
	पूर्णांक (*gfx_state_change)(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t state);
पूर्ण;

काष्ठा pp_table_func अणु
	पूर्णांक (*pptable_init)(काष्ठा pp_hwmgr *hw_mgr);
	पूर्णांक (*pptable_fini)(काष्ठा pp_hwmgr *hw_mgr);
	पूर्णांक (*pptable_get_number_of_vce_state_table_entries)(काष्ठा pp_hwmgr *hw_mgr);
	पूर्णांक (*pptable_get_vce_state_table_entry)(
						काष्ठा pp_hwmgr *hwmgr,
						अचिन्हित दीर्घ i,
						काष्ठा amd_vce_state *vce_state,
						व्योम **घड़ी_info,
						अचिन्हित दीर्घ *flag);
पूर्ण;

जोड़ phm_cac_leakage_record अणु
	काष्ठा अणु
		uपूर्णांक16_t Vddc;          /* in CI, we use it क्रम StdVoltageHiSidd */
		uपूर्णांक32_t Leakage;       /* in CI, we use it क्रम StdVoltageLoSidd */
	पूर्ण;
	काष्ठा अणु
		uपूर्णांक16_t Vddc1;
		uपूर्णांक16_t Vddc2;
		uपूर्णांक16_t Vddc3;
	पूर्ण;
पूर्ण;

काष्ठा phm_cac_leakage_table अणु
	uपूर्णांक32_t count;
	जोड़ phm_cac_leakage_record entries[];
पूर्ण;

काष्ठा phm_samu_घड़ी_voltage_dependency_record अणु
	uपूर्णांक32_t samclk;
	uपूर्णांक32_t v;
पूर्ण;


काष्ठा phm_samu_घड़ी_voltage_dependency_table अणु
	uपूर्णांक8_t count;
	काष्ठा phm_samu_घड़ी_voltage_dependency_record entries[];
पूर्ण;

काष्ठा phm_cac_tdp_table अणु
	uपूर्णांक16_t usTDP;
	uपूर्णांक16_t usConfigurableTDP;
	uपूर्णांक16_t usTDC;
	uपूर्णांक16_t usBatteryPowerLimit;
	uपूर्णांक16_t usSmallPowerLimit;
	uपूर्णांक16_t usLowCACLeakage;
	uपूर्णांक16_t usHighCACLeakage;
	uपूर्णांक16_t usMaximumPowerDeliveryLimit;
	uपूर्णांक16_t usEDCLimit;
	uपूर्णांक16_t usOperatingTempMinLimit;
	uपूर्णांक16_t usOperatingTempMaxLimit;
	uपूर्णांक16_t usOperatingTempStep;
	uपूर्णांक16_t usOperatingTempHyst;
	uपूर्णांक16_t usDefaultTargetOperatingTemp;
	uपूर्णांक16_t usTargetOperatingTemp;
	uपूर्णांक16_t usPowerTuneDataSetID;
	uपूर्णांक16_t usSoftwareShutकरोwnTemp;
	uपूर्णांक16_t usClockStretchAmount;
	uपूर्णांक16_t usTemperatureLimitHotspot;
	uपूर्णांक16_t usTemperatureLimitLiquid1;
	uपूर्णांक16_t usTemperatureLimitLiquid2;
	uपूर्णांक16_t usTemperatureLimitVrVddc;
	uपूर्णांक16_t usTemperatureLimitVrMvdd;
	uपूर्णांक16_t usTemperatureLimitPlx;
	uपूर्णांक8_t  ucLiquid1_I2C_address;
	uपूर्णांक8_t  ucLiquid2_I2C_address;
	uपूर्णांक8_t  ucLiquid_I2C_Line;
	uपूर्णांक8_t  ucVr_I2C_address;
	uपूर्णांक8_t  ucVr_I2C_Line;
	uपूर्णांक8_t  ucPlx_I2C_address;
	uपूर्णांक8_t  ucPlx_I2C_Line;
	uपूर्णांक32_t usBoostPowerLimit;
	uपूर्णांक8_t  ucCKS_LDO_REFSEL;
	uपूर्णांक8_t  ucHotSpotOnly;
पूर्ण;

काष्ठा phm_tdp_table अणु
	uपूर्णांक16_t usTDP;
	uपूर्णांक16_t usConfigurableTDP;
	uपूर्णांक16_t usTDC;
	uपूर्णांक16_t usBatteryPowerLimit;
	uपूर्णांक16_t usSmallPowerLimit;
	uपूर्णांक16_t usLowCACLeakage;
	uपूर्णांक16_t usHighCACLeakage;
	uपूर्णांक16_t usMaximumPowerDeliveryLimit;
	uपूर्णांक16_t usEDCLimit;
	uपूर्णांक16_t usOperatingTempMinLimit;
	uपूर्णांक16_t usOperatingTempMaxLimit;
	uपूर्णांक16_t usOperatingTempStep;
	uपूर्णांक16_t usOperatingTempHyst;
	uपूर्णांक16_t usDefaultTargetOperatingTemp;
	uपूर्णांक16_t usTargetOperatingTemp;
	uपूर्णांक16_t usPowerTuneDataSetID;
	uपूर्णांक16_t usSoftwareShutकरोwnTemp;
	uपूर्णांक16_t usClockStretchAmount;
	uपूर्णांक16_t usTemperatureLimitTedge;
	uपूर्णांक16_t usTemperatureLimitHotspot;
	uपूर्णांक16_t usTemperatureLimitLiquid1;
	uपूर्णांक16_t usTemperatureLimitLiquid2;
	uपूर्णांक16_t usTemperatureLimitHBM;
	uपूर्णांक16_t usTemperatureLimitVrVddc;
	uपूर्णांक16_t usTemperatureLimitVrMvdd;
	uपूर्णांक16_t usTemperatureLimitPlx;
	uपूर्णांक8_t  ucLiquid1_I2C_address;
	uपूर्णांक8_t  ucLiquid2_I2C_address;
	uपूर्णांक8_t  ucLiquid_I2C_Line;
	uपूर्णांक8_t  ucVr_I2C_address;
	uपूर्णांक8_t  ucVr_I2C_Line;
	uपूर्णांक8_t  ucPlx_I2C_address;
	uपूर्णांक8_t  ucPlx_I2C_Line;
	uपूर्णांक8_t  ucLiquid_I2C_LineSDA;
	uपूर्णांक8_t  ucVr_I2C_LineSDA;
	uपूर्णांक8_t  ucPlx_I2C_LineSDA;
	uपूर्णांक32_t usBoostPowerLimit;
	uपूर्णांक16_t usBoostStartTemperature;
	uपूर्णांक16_t usBoostStopTemperature;
	uपूर्णांक32_t  ulBoostClock;
पूर्ण;

काष्ठा phm_ppm_table अणु
	uपूर्णांक8_t   ppm_design;
	uपूर्णांक16_t  cpu_core_number;
	uपूर्णांक32_t  platक्रमm_tdp;
	uपूर्णांक32_t  small_ac_platक्रमm_tdp;
	uपूर्णांक32_t  platक्रमm_tdc;
	uपूर्णांक32_t  small_ac_platक्रमm_tdc;
	uपूर्णांक32_t  apu_tdp;
	uपूर्णांक32_t  dgpu_tdp;
	uपूर्णांक32_t  dgpu_ulv_घातer;
	uपूर्णांक32_t  tj_max;
पूर्ण;

काष्ठा phm_vq_budgeting_record अणु
	uपूर्णांक32_t ulCUs;
	uपूर्णांक32_t ulSustainableSOCPowerLimitLow;
	uपूर्णांक32_t ulSustainableSOCPowerLimitHigh;
	uपूर्णांक32_t ulMinSclkLow;
	uपूर्णांक32_t ulMinSclkHigh;
	uपूर्णांक8_t  ucDispConfig;
	uपूर्णांक32_t ulDClk;
	uपूर्णांक32_t ulEClk;
	uपूर्णांक32_t ulSustainableSclk;
	uपूर्णांक32_t ulSustainableCUs;
पूर्ण;

काष्ठा phm_vq_budgeting_table अणु
	uपूर्णांक8_t numEntries;
	काष्ठा phm_vq_budgeting_record entries[1];
पूर्ण;

काष्ठा phm_घड़ी_and_voltage_limits अणु
	uपूर्णांक32_t sclk;
	uपूर्णांक32_t mclk;
	uपूर्णांक32_t gfxclk;
	uपूर्णांक16_t vddc;
	uपूर्णांक16_t vddci;
	uपूर्णांक16_t vddgfx;
	uपूर्णांक16_t vddmem;
पूर्ण;

/* Structure to hold PPTable inक्रमmation */

काष्ठा phm_ppt_v1_inक्रमmation अणु
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_on_sclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_on_mclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_on_socclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_on_dcefclk;
	काष्ठा phm_घड़ी_array *valid_sclk_values;
	काष्ठा phm_घड़ी_array *valid_mclk_values;
	काष्ठा phm_घड़ी_array *valid_socclk_values;
	काष्ठा phm_घड़ी_array *valid_dcefclk_values;
	काष्ठा phm_घड़ी_and_voltage_limits max_घड़ी_voltage_on_dc;
	काष्ठा phm_घड़ी_and_voltage_limits max_घड़ी_voltage_on_ac;
	काष्ठा phm_घड़ी_voltage_dependency_table *vddc_dep_on_dal_pwrl;
	काष्ठा phm_ppm_table *ppm_parameter_table;
	काष्ठा phm_cac_tdp_table *cac_dtp_table;
	काष्ठा phm_tdp_table *tdp_table;
	काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_dep_table;
	काष्ठा phm_ppt_v1_voltage_lookup_table *vddc_lookup_table;
	काष्ठा phm_ppt_v1_voltage_lookup_table *vddgfx_lookup_table;
	काष्ठा phm_ppt_v1_voltage_lookup_table *vddmem_lookup_table;
	काष्ठा phm_ppt_v1_pcie_table *pcie_table;
	काष्ठा phm_ppt_v1_gpio_table *gpio_table;
	uपूर्णांक16_t us_ulv_voltage_offset;
	uपूर्णांक16_t us_ulv_smnclk_did;
	uपूर्णांक16_t us_ulv_mp1clk_did;
	uपूर्णांक16_t us_ulv_gfxclk_bypass;
	uपूर्णांक16_t us_gfxclk_slew_rate;
	uपूर्णांक16_t us_min_gfxclk_freq_limit;
पूर्ण;

काष्ठा phm_ppt_v2_inक्रमmation अणु
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_on_sclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_on_mclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_on_socclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_on_dcefclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_on_pixclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_on_dispclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_on_phyclk;
	काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_dep_table;

	काष्ठा phm_घड़ी_voltage_dependency_table *vddc_dep_on_dalpwrl;

	काष्ठा phm_घड़ी_array *valid_sclk_values;
	काष्ठा phm_घड़ी_array *valid_mclk_values;
	काष्ठा phm_घड़ी_array *valid_socclk_values;
	काष्ठा phm_घड़ी_array *valid_dcefclk_values;

	काष्ठा phm_घड़ी_and_voltage_limits max_घड़ी_voltage_on_dc;
	काष्ठा phm_घड़ी_and_voltage_limits max_घड़ी_voltage_on_ac;

	काष्ठा phm_ppm_table *ppm_parameter_table;
	काष्ठा phm_cac_tdp_table *cac_dtp_table;
	काष्ठा phm_tdp_table *tdp_table;

	काष्ठा phm_ppt_v1_voltage_lookup_table *vddc_lookup_table;
	काष्ठा phm_ppt_v1_voltage_lookup_table *vddgfx_lookup_table;
	काष्ठा phm_ppt_v1_voltage_lookup_table *vddmem_lookup_table;
	काष्ठा phm_ppt_v1_voltage_lookup_table *vddci_lookup_table;

	काष्ठा phm_ppt_v1_pcie_table *pcie_table;

	uपूर्णांक16_t us_ulv_voltage_offset;
	uपूर्णांक16_t us_ulv_smnclk_did;
	uपूर्णांक16_t us_ulv_mp1clk_did;
	uपूर्णांक16_t us_ulv_gfxclk_bypass;
	uपूर्णांक16_t us_gfxclk_slew_rate;
	uपूर्णांक16_t us_min_gfxclk_freq_limit;

	uपूर्णांक8_t  uc_gfx_dpm_voltage_mode;
	uपूर्णांक8_t  uc_soc_dpm_voltage_mode;
	uपूर्णांक8_t  uc_uclk_dpm_voltage_mode;
	uपूर्णांक8_t  uc_uvd_dpm_voltage_mode;
	uपूर्णांक8_t  uc_vce_dpm_voltage_mode;
	uपूर्णांक8_t  uc_mp0_dpm_voltage_mode;
	uपूर्णांक8_t  uc_dcef_dpm_voltage_mode;
पूर्ण;

काष्ठा phm_ppt_v3_inक्रमmation
अणु
	uपूर्णांक8_t uc_thermal_controller_type;

	uपूर्णांक16_t us_small_घातer_limit1;
	uपूर्णांक16_t us_small_घातer_limit2;
	uपूर्णांक16_t us_boost_घातer_limit;

	uपूर्णांक16_t us_od_turbo_घातer_limit;
	uपूर्णांक16_t us_od_घातersave_घातer_limit;
	uपूर्णांक16_t us_software_shutकरोwn_temp;

	uपूर्णांक32_t *घातer_saving_घड़ी_max;
	uपूर्णांक32_t *घातer_saving_घड़ी_min;

	uपूर्णांक8_t *od_feature_capabilities;
	uपूर्णांक32_t *od_settings_max;
	uपूर्णांक32_t *od_settings_min;

	व्योम *smc_pptable;
पूर्ण;

काष्ठा phm_dynamic_state_info अणु
	काष्ठा phm_घड़ी_voltage_dependency_table *vddc_dependency_on_sclk;
	काष्ठा phm_घड़ी_voltage_dependency_table *vddci_dependency_on_mclk;
	काष्ठा phm_घड़ी_voltage_dependency_table *vddc_dependency_on_mclk;
	काष्ठा phm_घड़ी_voltage_dependency_table *mvdd_dependency_on_mclk;
	काष्ठा phm_घड़ी_voltage_dependency_table *vddc_dep_on_dal_pwrl;
	काष्ठा phm_घड़ी_array                    *valid_sclk_values;
	काष्ठा phm_घड़ी_array                    *valid_mclk_values;
	काष्ठा phm_घड़ी_and_voltage_limits       max_घड़ी_voltage_on_dc;
	काष्ठा phm_घड़ी_and_voltage_limits       max_घड़ी_voltage_on_ac;
	uपूर्णांक32_t                                  mclk_sclk_ratio;
	uपूर्णांक32_t                                  sclk_mclk_delta;
	uपूर्णांक32_t                                  vddc_vddci_delta;
	uपूर्णांक32_t                                  min_vddc_क्रम_pcie_gen2;
	काष्ठा phm_cac_leakage_table              *cac_leakage_table;
	काष्ठा phm_phase_shedding_limits_table  *vddc_phase_shed_limits_table;

	काष्ठा phm_vce_घड़ी_voltage_dependency_table
					    *vce_घड़ी_voltage_dependency_table;
	काष्ठा phm_uvd_घड़ी_voltage_dependency_table
					    *uvd_घड़ी_voltage_dependency_table;
	काष्ठा phm_acp_घड़ी_voltage_dependency_table
					    *acp_घड़ी_voltage_dependency_table;
	काष्ठा phm_samu_घड़ी_voltage_dependency_table
					   *samu_घड़ी_voltage_dependency_table;

	काष्ठा phm_ppm_table                          *ppm_parameter_table;
	काष्ठा phm_cac_tdp_table                      *cac_dtp_table;
	काष्ठा phm_घड़ी_voltage_dependency_table	*vdd_gfx_dependency_on_sclk;
पूर्ण;

काष्ठा pp_fan_info अणु
	bool bNoFan;
	uपूर्णांक8_t   ucTachometerPulsesPerRevolution;
	uपूर्णांक32_t   ulMinRPM;
	uपूर्णांक32_t   ulMaxRPM;
पूर्ण;

काष्ठा pp_advance_fan_control_parameters अणु
	uपूर्णांक16_t  usTMin;                          /* The temperature, in 0.01 centigrades, below which we just run at a minimal PWM. */
	uपूर्णांक16_t  usTMed;                          /* The middle temperature where we change slopes. */
	uपूर्णांक16_t  usTHigh;                         /* The high temperature क्रम setting the second slope. */
	uपूर्णांक16_t  usPWMMin;                        /* The minimum PWM value in percent (0.01% increments). */
	uपूर्णांक16_t  usPWMMed;                        /* The PWM value (in percent) at TMed. */
	uपूर्णांक16_t  usPWMHigh;                       /* The PWM value at THigh. */
	uपूर्णांक8_t   ucTHyst;                         /* Temperature hysteresis. Integer. */
	uपूर्णांक32_t   ulCycleDelay;                   /* The समय between two invocations of the fan control routine in microseconds. */
	uपूर्णांक16_t  usTMax;                          /* The max temperature */
	uपूर्णांक8_t   ucFanControlMode;
	uपूर्णांक16_t  usFanPWMMinLimit;
	uपूर्णांक16_t  usFanPWMMaxLimit;
	uपूर्णांक16_t  usFanPWMStep;
	uपूर्णांक16_t  usDefaultMaxFanPWM;
	uपूर्णांक16_t  usFanOutputSensitivity;
	uपूर्णांक16_t  usDefaultFanOutputSensitivity;
	uपूर्णांक16_t  usMaxFanPWM;                     /* The max Fan PWM value क्रम Fuzzy Fan Control feature */
	uपूर्णांक16_t  usFanRPMMinLimit;                /* Minimum limit range in percentage, need to calculate based on minRPM/MaxRpm */
	uपूर्णांक16_t  usFanRPMMaxLimit;                /* Maximum limit range in percentage, usually set to 100% by शेष */
	uपूर्णांक16_t  usFanRPMStep;                    /* Step increments/decerements, in percent */
	uपूर्णांक16_t  usDefaultMaxFanRPM;              /* The max Fan RPM value क्रम Fuzzy Fan Control feature, शेष from PPTable */
	uपूर्णांक16_t  usMaxFanRPM;                     /* The max Fan RPM value क्रम Fuzzy Fan Control feature, user defined */
	uपूर्णांक16_t  usFanCurrentLow;                 /* Low current */
	uपूर्णांक16_t  usFanCurrentHigh;                /* High current */
	uपूर्णांक16_t  usFanRPMLow;                     /* Low RPM */
	uपूर्णांक16_t  usFanRPMHigh;                    /* High RPM */
	uपूर्णांक32_t   ulMinFanSCLKAcousticLimit;      /* Minimum Fan Controller SCLK Frequency Acoustic Limit. */
	uपूर्णांक8_t   ucTargetTemperature;             /* Advanced fan controller target temperature. */
	uपूर्णांक8_t   ucMinimumPWMLimit;               /* The minimum PWM that the advanced fan controller can set.  This should be set to the highest PWM that will run the fan at its lowest RPM. */
	uपूर्णांक16_t  usFanGainEdge;                   /* The following is added क्रम Fiji */
	uपूर्णांक16_t  usFanGainHotspot;
	uपूर्णांक16_t  usFanGainLiquid;
	uपूर्णांक16_t  usFanGainVrVddc;
	uपूर्णांक16_t  usFanGainVrMvdd;
	uपूर्णांक16_t  usFanGainPlx;
	uपूर्णांक16_t  usFanGainHbm;
	uपूर्णांक8_t   ucEnableZeroRPM;
	uपूर्णांक8_t   ucFanStopTemperature;
	uपूर्णांक8_t   ucFanStartTemperature;
	uपूर्णांक32_t  ulMaxFanSCLKAcousticLimit;       /* Maximum Fan Controller SCLK Frequency Acoustic Limit. */
	uपूर्णांक32_t  ulTargetGfxClk;
	uपूर्णांक16_t  usZeroRPMStartTemperature;
	uपूर्णांक16_t  usZeroRPMStopTemperature;
	uपूर्णांक16_t  usMGpuThrottlingRPMLimit;
पूर्ण;

काष्ठा pp_thermal_controller_info अणु
	uपूर्णांक8_t ucType;
	uपूर्णांक8_t ucI2cLine;
	uपूर्णांक8_t ucI2cAddress;
	uपूर्णांक8_t use_hw_fan_control;
	काष्ठा pp_fan_info fanInfo;
	काष्ठा pp_advance_fan_control_parameters advanceFanControlParameters;
पूर्ण;

काष्ठा phm_microcode_version_info अणु
	uपूर्णांक32_t SMC;
	uपूर्णांक32_t DMCU;
	uपूर्णांक32_t MC;
	uपूर्णांक32_t NB;
पूर्ण;

क्रमागत PP_TABLE_VERSION अणु
	PP_TABLE_V0 = 0,
	PP_TABLE_V1,
	PP_TABLE_V2,
	PP_TABLE_MAX
पूर्ण;

/**
 * The मुख्य hardware manager काष्ठाure.
 */
#घोषणा Workload_Policy_Max 6

काष्ठा pp_hwmgr अणु
	व्योम *adev;
	uपूर्णांक32_t chip_family;
	uपूर्णांक32_t chip_id;
	uपूर्णांक32_t smu_version;
	bool not_vf;
	bool pm_en;
	bool pp_one_vf;
	काष्ठा mutex smu_lock;
	काष्ठा mutex msg_lock;

	uपूर्णांक32_t pp_table_version;
	व्योम *device;
	काष्ठा pp_smumgr *smumgr;
	स्थिर व्योम *soft_pp_table;
	uपूर्णांक32_t soft_pp_table_size;
	व्योम *hardcode_pp_table;
	bool need_pp_table_upload;

	काष्ठा amd_vce_state vce_states[AMD_MAX_VCE_LEVELS];
	uपूर्णांक32_t num_vce_state_tables;

	क्रमागत amd_dpm_क्रमced_level dpm_level;
	क्रमागत amd_dpm_क्रमced_level saved_dpm_level;
	क्रमागत amd_dpm_क्रमced_level request_dpm_level;
	uपूर्णांक32_t usec_समयout;
	व्योम *pptable;
	काष्ठा phm_platक्रमm_descriptor platक्रमm_descriptor;
	व्योम *backend;

	व्योम *smu_backend;
	स्थिर काष्ठा pp_smumgr_func *smumgr_funcs;
	bool is_kicker;

	क्रमागत PP_DAL_POWERLEVEL dal_घातer_level;
	काष्ठा phm_dynamic_state_info dyn_state;
	स्थिर काष्ठा pp_hwmgr_func *hwmgr_func;
	स्थिर काष्ठा pp_table_func *pptable_func;

	काष्ठा pp_घातer_state    *ps;
	uपूर्णांक32_t num_ps;
	काष्ठा pp_thermal_controller_info thermal_controller;
	bool fan_ctrl_is_in_शेष_mode;
	uपूर्णांक32_t fan_ctrl_शेष_mode;
	bool fan_ctrl_enabled;
	uपूर्णांक32_t पंचांगin;
	काष्ठा phm_microcode_version_info microcode_version_info;
	uपूर्णांक32_t ps_size;
	काष्ठा pp_घातer_state    *current_ps;
	काष्ठा pp_घातer_state    *request_ps;
	काष्ठा pp_घातer_state    *boot_ps;
	काष्ठा pp_घातer_state    *uvd_ps;
	स्थिर काष्ठा amd_pp_display_configuration *display_config;
	uपूर्णांक32_t feature_mask;
	bool avfs_supported;
	/* UMD Pstate */
	bool en_umd_pstate;
	uपूर्णांक32_t घातer_profile_mode;
	uपूर्णांक32_t शेष_घातer_profile_mode;
	uपूर्णांक32_t pstate_sclk;
	uपूर्णांक32_t pstate_mclk;
	bool od_enabled;
	uपूर्णांक32_t घातer_limit;
	uपूर्णांक32_t शेष_घातer_limit;
	uपूर्णांक32_t workload_mask;
	uपूर्णांक32_t workload_prority[Workload_Policy_Max];
	uपूर्णांक32_t workload_setting[Workload_Policy_Max];
	bool gfxoff_state_changed_by_workload;
पूर्ण;

पूर्णांक hwmgr_early_init(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक hwmgr_sw_init(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक hwmgr_sw_fini(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक hwmgr_hw_init(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक hwmgr_hw_fini(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक hwmgr_suspend(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक hwmgr_resume(काष्ठा pp_hwmgr *hwmgr);

पूर्णांक hwmgr_handle_task(काष्ठा pp_hwmgr *hwmgr,
				क्रमागत amd_pp_task task_id,
				क्रमागत amd_pm_state_type *user_state);


#घोषणा PHM_ENTIRE_REGISTER_MASK 0xFFFFFFFFU

पूर्णांक smu7_init_function_poपूर्णांकers(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu8_init_function_poपूर्णांकers(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक vega12_hwmgr_init(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक vega20_hwmgr_init(काष्ठा pp_hwmgr *hwmgr);

#पूर्ण_अगर /* _HWMGR_H_ */
