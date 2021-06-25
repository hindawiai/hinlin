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

#अगर_अघोषित __KGD_PP_INTERFACE_H__
#घोषणा __KGD_PP_INTERFACE_H__

बाह्य स्थिर काष्ठा amdgpu_ip_block_version pp_smu_ip_block;

काष्ठा amd_vce_state अणु
	/* vce घड़ीs */
	u32 evclk;
	u32 ecclk;
	/* gpu घड़ीs */
	u32 sclk;
	u32 mclk;
	u8 clk_idx;
	u8 pstate;
पूर्ण;


क्रमागत amd_dpm_क्रमced_level अणु
	AMD_DPM_FORCED_LEVEL_AUTO = 0x1,
	AMD_DPM_FORCED_LEVEL_MANUAL = 0x2,
	AMD_DPM_FORCED_LEVEL_LOW = 0x4,
	AMD_DPM_FORCED_LEVEL_HIGH = 0x8,
	AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD = 0x10,
	AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK = 0x20,
	AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK = 0x40,
	AMD_DPM_FORCED_LEVEL_PROखाता_PEAK = 0x80,
	AMD_DPM_FORCED_LEVEL_PROखाता_EXIT = 0x100,
	AMD_DPM_FORCED_LEVEL_PERF_DETERMINISM = 0x200,
पूर्ण;

क्रमागत amd_pm_state_type अणु
	/* not used क्रम dpm */
	POWER_STATE_TYPE_DEFAULT,
	POWER_STATE_TYPE_POWERSAVE,
	/* user selectable states */
	POWER_STATE_TYPE_BATTERY,
	POWER_STATE_TYPE_BALANCED,
	POWER_STATE_TYPE_PERFORMANCE,
	/* पूर्णांकernal states */
	POWER_STATE_TYPE_INTERNAL_UVD,
	POWER_STATE_TYPE_INTERNAL_UVD_SD,
	POWER_STATE_TYPE_INTERNAL_UVD_HD,
	POWER_STATE_TYPE_INTERNAL_UVD_HD2,
	POWER_STATE_TYPE_INTERNAL_UVD_MVC,
	POWER_STATE_TYPE_INTERNAL_BOOT,
	POWER_STATE_TYPE_INTERNAL_THERMAL,
	POWER_STATE_TYPE_INTERNAL_ACPI,
	POWER_STATE_TYPE_INTERNAL_ULV,
	POWER_STATE_TYPE_INTERNAL_3DPERF,
पूर्ण;

#घोषणा AMD_MAX_VCE_LEVELS 6

क्रमागत amd_vce_level अणु
	AMD_VCE_LEVEL_AC_ALL = 0,     /* AC, All हालs */
	AMD_VCE_LEVEL_DC_EE = 1,      /* DC, entropy encoding */
	AMD_VCE_LEVEL_DC_LL_LOW = 2,  /* DC, low latency queue, res <= 720 */
	AMD_VCE_LEVEL_DC_LL_HIGH = 3, /* DC, low latency queue, 1080 >= res > 720 */
	AMD_VCE_LEVEL_DC_GP_LOW = 4,  /* DC, general purpose queue, res <= 720 */
	AMD_VCE_LEVEL_DC_GP_HIGH = 5, /* DC, general purpose queue, 1080 >= res > 720 */
पूर्ण;

क्रमागत amd_fan_ctrl_mode अणु
	AMD_FAN_CTRL_NONE = 0,
	AMD_FAN_CTRL_MANUAL = 1,
	AMD_FAN_CTRL_AUTO = 2,
पूर्ण;

क्रमागत pp_घड़ी_प्रकारype अणु
	PP_SCLK,
	PP_MCLK,
	PP_PCIE,
	PP_SOCCLK,
	PP_FCLK,
	PP_DCEFCLK,
	PP_VCLK,
	PP_DCLK,
	OD_SCLK,
	OD_MCLK,
	OD_VDDC_CURVE,
	OD_RANGE,
	OD_VDDGFX_OFFSET,
	OD_CCLK,
पूर्ण;

क्रमागत amd_pp_sensors अणु
	AMDGPU_PP_SENSOR_GFX_SCLK = 0,
	AMDGPU_PP_SENSOR_CPU_CLK,
	AMDGPU_PP_SENSOR_VDDNB,
	AMDGPU_PP_SENSOR_VDDGFX,
	AMDGPU_PP_SENSOR_UVD_VCLK,
	AMDGPU_PP_SENSOR_UVD_DCLK,
	AMDGPU_PP_SENSOR_VCE_ECCLK,
	AMDGPU_PP_SENSOR_GPU_LOAD,
	AMDGPU_PP_SENSOR_MEM_LOAD,
	AMDGPU_PP_SENSOR_GFX_MCLK,
	AMDGPU_PP_SENSOR_GPU_TEMP,
	AMDGPU_PP_SENSOR_EDGE_TEMP = AMDGPU_PP_SENSOR_GPU_TEMP,
	AMDGPU_PP_SENSOR_HOTSPOT_TEMP,
	AMDGPU_PP_SENSOR_MEM_TEMP,
	AMDGPU_PP_SENSOR_VCE_POWER,
	AMDGPU_PP_SENSOR_UVD_POWER,
	AMDGPU_PP_SENSOR_GPU_POWER,
	AMDGPU_PP_SENSOR_STABLE_PSTATE_SCLK,
	AMDGPU_PP_SENSOR_STABLE_PSTATE_MCLK,
	AMDGPU_PP_SENSOR_ENABLED_SMC_FEATURES_MASK,
	AMDGPU_PP_SENSOR_MIN_FAN_RPM,
	AMDGPU_PP_SENSOR_MAX_FAN_RPM,
	AMDGPU_PP_SENSOR_VCN_POWER_STATE,
पूर्ण;

क्रमागत amd_pp_task अणु
	AMD_PP_TASK_DISPLAY_CONFIG_CHANGE,
	AMD_PP_TASK_ENABLE_USER_STATE,
	AMD_PP_TASK_READJUST_POWER_STATE,
	AMD_PP_TASK_COMPLETE_INIT,
	AMD_PP_TASK_MAX
पूर्ण;

क्रमागत PP_SMC_POWER_PROखाता अणु
	PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT = 0x0,
	PP_SMC_POWER_PROखाता_FULLSCREEN3D = 0x1,
	PP_SMC_POWER_PROखाता_POWERSAVING  = 0x2,
	PP_SMC_POWER_PROखाता_VIDEO        = 0x3,
	PP_SMC_POWER_PROखाता_VR           = 0x4,
	PP_SMC_POWER_PROखाता_COMPUTE      = 0x5,
	PP_SMC_POWER_PROखाता_CUSTOM       = 0x6,
	PP_SMC_POWER_PROखाता_COUNT,
पूर्ण;

क्रमागत अणु
	PP_GROUP_UNKNOWN = 0,
	PP_GROUP_GFX = 1,
	PP_GROUP_SYS,
	PP_GROUP_MAX
पूर्ण;

क्रमागत PP_OD_DPM_TABLE_COMMAND अणु
	PP_OD_EDIT_SCLK_VDDC_TABLE,
	PP_OD_EDIT_MCLK_VDDC_TABLE,
	PP_OD_EDIT_CCLK_VDDC_TABLE,
	PP_OD_EDIT_VDDC_CURVE,
	PP_OD_RESTORE_DEFAULT_TABLE,
	PP_OD_COMMIT_DPM_TABLE,
	PP_OD_EDIT_VDDGFX_OFFSET
पूर्ण;

काष्ठा pp_states_info अणु
	uपूर्णांक32_t nums;
	uपूर्णांक32_t states[16];
पूर्ण;

क्रमागत PP_HWMON_TEMP अणु
	PP_TEMP_EDGE = 0,
	PP_TEMP_JUNCTION,
	PP_TEMP_MEM,
	PP_TEMP_MAX
पूर्ण;

क्रमागत pp_mp1_state अणु
	PP_MP1_STATE_NONE,
	PP_MP1_STATE_SHUTDOWN,
	PP_MP1_STATE_UNLOAD,
	PP_MP1_STATE_RESET,
पूर्ण;

क्रमागत pp_df_cstate अणु
	DF_CSTATE_DISALLOW = 0,
	DF_CSTATE_ALLOW,
पूर्ण;

#घोषणा PP_GROUP_MASK        0xF0000000
#घोषणा PP_GROUP_SHIFT       28

#घोषणा PP_BLOCK_MASK        0x0FFFFF00
#घोषणा PP_BLOCK_SHIFT       8

#घोषणा PP_BLOCK_GFX_CG         0x01
#घोषणा PP_BLOCK_GFX_MG         0x02
#घोषणा PP_BLOCK_GFX_3D         0x04
#घोषणा PP_BLOCK_GFX_RLC        0x08
#घोषणा PP_BLOCK_GFX_CP         0x10
#घोषणा PP_BLOCK_SYS_BIF        0x01
#घोषणा PP_BLOCK_SYS_MC         0x02
#घोषणा PP_BLOCK_SYS_ROM        0x04
#घोषणा PP_BLOCK_SYS_DRM        0x08
#घोषणा PP_BLOCK_SYS_HDP        0x10
#घोषणा PP_BLOCK_SYS_SDMA       0x20

#घोषणा PP_STATE_MASK           0x0000000F
#घोषणा PP_STATE_SHIFT          0
#घोषणा PP_STATE_SUPPORT_MASK   0x000000F0
#घोषणा PP_STATE_SUPPORT_SHIFT  0

#घोषणा PP_STATE_CG             0x01
#घोषणा PP_STATE_LS             0x02
#घोषणा PP_STATE_DS             0x04
#घोषणा PP_STATE_SD             0x08
#घोषणा PP_STATE_SUPPORT_CG     0x10
#घोषणा PP_STATE_SUPPORT_LS     0x20
#घोषणा PP_STATE_SUPPORT_DS     0x40
#घोषणा PP_STATE_SUPPORT_SD     0x80

#घोषणा PP_CG_MSG_ID(group, block, support, state) \
		((group) << PP_GROUP_SHIFT | (block) << PP_BLOCK_SHIFT | \
		(support) << PP_STATE_SUPPORT_SHIFT | (state) << PP_STATE_SHIFT)

#घोषणा XGMI_MODE_PSTATE_D3 0
#घोषणा XGMI_MODE_PSTATE_D0 1

#घोषणा NUM_HBM_INSTANCES 4

काष्ठा seq_file;
क्रमागत amd_pp_घड़ी_प्रकारype;
काष्ठा amd_pp_simple_घड़ी_info;
काष्ठा amd_pp_display_configuration;
काष्ठा amd_pp_घड़ी_info;
काष्ठा pp_display_घड़ी_request;
काष्ठा pp_घड़ी_levels_with_voltage;
काष्ठा pp_घड़ी_levels_with_latency;
काष्ठा amd_pp_घड़ीs;
काष्ठा pp_smu_wm_range_sets;
काष्ठा pp_smu_nv_घड़ी_प्रकारable;
काष्ठा dpm_घड़ीs;

काष्ठा amd_pm_funcs अणु
/* export क्रम dpm on ci and si */
	पूर्णांक (*pre_set_घातer_state)(व्योम *handle);
	पूर्णांक (*set_घातer_state)(व्योम *handle);
	व्योम (*post_set_घातer_state)(व्योम *handle);
	व्योम (*display_configuration_changed)(व्योम *handle);
	व्योम (*prपूर्णांक_घातer_state)(व्योम *handle, व्योम *ps);
	bool (*vblank_too_लघु)(व्योम *handle);
	व्योम (*enable_bapm)(व्योम *handle, bool enable);
	पूर्णांक (*check_state_equal)(व्योम *handle,
				व्योम  *cps,
				व्योम  *rps,
				bool  *equal);
/* export क्रम sysfs */
	व्योम (*set_fan_control_mode)(व्योम *handle, u32 mode);
	u32 (*get_fan_control_mode)(व्योम *handle);
	पूर्णांक (*set_fan_speed_percent)(व्योम *handle, u32 speed);
	पूर्णांक (*get_fan_speed_percent)(व्योम *handle, u32 *speed);
	पूर्णांक (*क्रमce_घड़ी_level)(व्योम *handle, क्रमागत pp_घड़ी_प्रकारype type, uपूर्णांक32_t mask);
	पूर्णांक (*prपूर्णांक_घड़ी_levels)(व्योम *handle, क्रमागत pp_घड़ी_प्रकारype type, अक्षर *buf);
	पूर्णांक (*क्रमce_perक्रमmance_level)(व्योम *handle, क्रमागत amd_dpm_क्रमced_level level);
	पूर्णांक (*get_sclk_od)(व्योम *handle);
	पूर्णांक (*set_sclk_od)(व्योम *handle, uपूर्णांक32_t value);
	पूर्णांक (*get_mclk_od)(व्योम *handle);
	पूर्णांक (*set_mclk_od)(व्योम *handle, uपूर्णांक32_t value);
	पूर्णांक (*पढ़ो_sensor)(व्योम *handle, पूर्णांक idx, व्योम *value, पूर्णांक *size);
	क्रमागत amd_dpm_क्रमced_level (*get_perक्रमmance_level)(व्योम *handle);
	क्रमागत amd_pm_state_type (*get_current_घातer_state)(व्योम *handle);
	पूर्णांक (*get_fan_speed_rpm)(व्योम *handle, uपूर्णांक32_t *rpm);
	पूर्णांक (*set_fan_speed_rpm)(व्योम *handle, uपूर्णांक32_t rpm);
	पूर्णांक (*get_pp_num_states)(व्योम *handle, काष्ठा pp_states_info *data);
	पूर्णांक (*get_pp_table)(व्योम *handle, अक्षर **table);
	पूर्णांक (*set_pp_table)(व्योम *handle, स्थिर अक्षर *buf, माप_प्रकार size);
	व्योम (*debugfs_prपूर्णांक_current_perक्रमmance_level)(व्योम *handle, काष्ठा seq_file *m);
	पूर्णांक (*चयन_घातer_profile)(व्योम *handle, क्रमागत PP_SMC_POWER_PROखाता type, bool en);
/* export to amdgpu */
	काष्ठा amd_vce_state *(*get_vce_घड़ी_state)(व्योम *handle, u32 idx);
	पूर्णांक (*dispatch_tasks)(व्योम *handle, क्रमागत amd_pp_task task_id,
			क्रमागत amd_pm_state_type *user_state);
	पूर्णांक (*load_firmware)(व्योम *handle);
	पूर्णांक (*रुको_क्रम_fw_loading_complete)(व्योम *handle);
	पूर्णांक (*set_घातergating_by_smu)(व्योम *handle,
				uपूर्णांक32_t block_type, bool gate);
	पूर्णांक (*set_घड़ीgating_by_smu)(व्योम *handle, uपूर्णांक32_t msg_id);
	पूर्णांक (*set_घातer_limit)(व्योम *handle, uपूर्णांक32_t n);
	पूर्णांक (*get_घातer_limit)(व्योम *handle, uपूर्णांक32_t *limit, uपूर्णांक32_t *max_limit,
			bool शेष_limit);
	पूर्णांक (*get_घातer_profile_mode)(व्योम *handle, अक्षर *buf);
	पूर्णांक (*set_घातer_profile_mode)(व्योम *handle, दीर्घ *input, uपूर्णांक32_t size);
	पूर्णांक (*set_fine_grain_clk_vol)(व्योम *handle, uपूर्णांक32_t type, दीर्घ *input, uपूर्णांक32_t size);
	पूर्णांक (*odn_edit_dpm_table)(व्योम *handle, uपूर्णांक32_t type, दीर्घ *input, uपूर्णांक32_t size);
	पूर्णांक (*set_mp1_state)(व्योम *handle, क्रमागत pp_mp1_state mp1_state);
	पूर्णांक (*smu_i2c_bus_access)(व्योम *handle, bool acquire);
	पूर्णांक (*gfx_state_change_set)(व्योम *handle, uपूर्णांक32_t state);
/* export to DC */
	u32 (*get_sclk)(व्योम *handle, bool low);
	u32 (*get_mclk)(व्योम *handle, bool low);
	पूर्णांक (*display_configuration_change)(व्योम *handle,
		स्थिर काष्ठा amd_pp_display_configuration *input);
	पूर्णांक (*get_display_घातer_level)(व्योम *handle,
		काष्ठा amd_pp_simple_घड़ी_info *output);
	पूर्णांक (*get_current_घड़ीs)(व्योम *handle,
		काष्ठा amd_pp_घड़ी_info *घड़ीs);
	पूर्णांक (*get_घड़ी_by_type)(व्योम *handle,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा amd_pp_घड़ीs *घड़ीs);
	पूर्णांक (*get_घड़ी_by_type_with_latency)(व्योम *handle,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs);
	पूर्णांक (*get_घड़ी_by_type_with_voltage)(व्योम *handle,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_voltage *घड़ीs);
	पूर्णांक (*set_watermarks_क्रम_घड़ीs_ranges)(व्योम *handle,
						व्योम *घड़ी_ranges);
	पूर्णांक (*display_घड़ी_voltage_request)(व्योम *handle,
				काष्ठा pp_display_घड़ी_request *घड़ी);
	पूर्णांक (*get_display_mode_validation_घड़ीs)(व्योम *handle,
		काष्ठा amd_pp_simple_घड़ी_info *घड़ीs);
	पूर्णांक (*notअगरy_smu_enable_pwe)(व्योम *handle);
	पूर्णांक (*enable_mgpu_fan_boost)(व्योम *handle);
	पूर्णांक (*set_active_display_count)(व्योम *handle, uपूर्णांक32_t count);
	पूर्णांक (*set_hard_min_dcefclk_by_freq)(व्योम *handle, uपूर्णांक32_t घड़ी);
	पूर्णांक (*set_hard_min_fclk_by_freq)(व्योम *handle, uपूर्णांक32_t घड़ी);
	पूर्णांक (*set_min_deep_sleep_dcefclk)(व्योम *handle, uपूर्णांक32_t घड़ी);
	पूर्णांक (*get_asic_baco_capability)(व्योम *handle, bool *cap);
	पूर्णांक (*get_asic_baco_state)(व्योम *handle, पूर्णांक *state);
	पूर्णांक (*set_asic_baco_state)(व्योम *handle, पूर्णांक state);
	पूर्णांक (*get_ppfeature_status)(व्योम *handle, अक्षर *buf);
	पूर्णांक (*set_ppfeature_status)(व्योम *handle, uपूर्णांक64_t ppfeature_masks);
	पूर्णांक (*asic_reset_mode_2)(व्योम *handle);
	पूर्णांक (*set_df_cstate)(व्योम *handle, क्रमागत pp_df_cstate state);
	पूर्णांक (*set_xgmi_pstate)(व्योम *handle, uपूर्णांक32_t pstate);
	sमाप_प्रकार (*get_gpu_metrics)(व्योम *handle, व्योम **table);
	पूर्णांक (*set_watermarks_क्रम_घड़ी_ranges)(व्योम *handle,
					       काष्ठा pp_smu_wm_range_sets *ranges);
	पूर्णांक (*display_disable_memory_घड़ी_चयन)(व्योम *handle,
						   bool disable_memory_घड़ी_चयन);
	पूर्णांक (*get_max_sustainable_घड़ीs_by_dc)(व्योम *handle,
						काष्ठा pp_smu_nv_घड़ी_प्रकारable *max_घड़ीs);
	पूर्णांक (*get_uclk_dpm_states)(व्योम *handle,
				   अचिन्हित पूर्णांक *घड़ी_values_in_khz,
				   अचिन्हित पूर्णांक *num_states);
	पूर्णांक (*get_dpm_घड़ी_प्रकारable)(व्योम *handle,
				   काष्ठा dpm_घड़ीs *घड़ी_प्रकारable);
पूर्ण;

काष्ठा metrics_table_header अणु
	uपूर्णांक16_t			काष्ठाure_size;
	uपूर्णांक8_t				क्रमmat_revision;
	uपूर्णांक8_t				content_revision;
पूर्ण;

/*
 * gpu_metrics_v1_0 is not recommended as it's not naturally aligned.
 * Use gpu_metrics_v1_1 or later instead.
 */
काष्ठा gpu_metrics_v1_0 अणु
	काष्ठा metrics_table_header	common_header;

	/* Driver attached बारtamp (in ns) */
	uपूर्णांक64_t			प्रणाली_घड़ी_counter;

	/* Temperature */
	uपूर्णांक16_t			temperature_edge;
	uपूर्णांक16_t			temperature_hotspot;
	uपूर्णांक16_t			temperature_mem;
	uपूर्णांक16_t			temperature_vrgfx;
	uपूर्णांक16_t			temperature_vrsoc;
	uपूर्णांक16_t			temperature_vrmem;

	/* Utilization */
	uपूर्णांक16_t			average_gfx_activity;
	uपूर्णांक16_t			average_umc_activity; // memory controller
	uपूर्णांक16_t			average_mm_activity; // UVD or VCN

	/* Power/Energy */
	uपूर्णांक16_t			average_socket_घातer;
	uपूर्णांक32_t			energy_accumulator;

	/* Average घड़ीs */
	uपूर्णांक16_t			average_gfxclk_frequency;
	uपूर्णांक16_t			average_socclk_frequency;
	uपूर्णांक16_t			average_uclk_frequency;
	uपूर्णांक16_t			average_vclk0_frequency;
	uपूर्णांक16_t			average_dclk0_frequency;
	uपूर्णांक16_t			average_vclk1_frequency;
	uपूर्णांक16_t			average_dclk1_frequency;

	/* Current घड़ीs */
	uपूर्णांक16_t			current_gfxclk;
	uपूर्णांक16_t			current_socclk;
	uपूर्णांक16_t			current_uclk;
	uपूर्णांक16_t			current_vclk0;
	uपूर्णांक16_t			current_dclk0;
	uपूर्णांक16_t			current_vclk1;
	uपूर्णांक16_t			current_dclk1;

	/* Throttle status */
	uपूर्णांक32_t			throttle_status;

	/* Fans */
	uपूर्णांक16_t			current_fan_speed;

	/* Link width/speed */
	uपूर्णांक8_t				pcie_link_width;
	uपूर्णांक8_t				pcie_link_speed; // in 0.1 GT/s
पूर्ण;

काष्ठा gpu_metrics_v1_1 अणु
	काष्ठा metrics_table_header	common_header;

	/* Temperature */
	uपूर्णांक16_t			temperature_edge;
	uपूर्णांक16_t			temperature_hotspot;
	uपूर्णांक16_t			temperature_mem;
	uपूर्णांक16_t			temperature_vrgfx;
	uपूर्णांक16_t			temperature_vrsoc;
	uपूर्णांक16_t			temperature_vrmem;

	/* Utilization */
	uपूर्णांक16_t			average_gfx_activity;
	uपूर्णांक16_t			average_umc_activity; // memory controller
	uपूर्णांक16_t			average_mm_activity; // UVD or VCN

	/* Power/Energy */
	uपूर्णांक16_t			average_socket_घातer;
	uपूर्णांक64_t			energy_accumulator;

	/* Driver attached बारtamp (in ns) */
	uपूर्णांक64_t			प्रणाली_घड़ी_counter;

	/* Average घड़ीs */
	uपूर्णांक16_t			average_gfxclk_frequency;
	uपूर्णांक16_t			average_socclk_frequency;
	uपूर्णांक16_t			average_uclk_frequency;
	uपूर्णांक16_t			average_vclk0_frequency;
	uपूर्णांक16_t			average_dclk0_frequency;
	uपूर्णांक16_t			average_vclk1_frequency;
	uपूर्णांक16_t			average_dclk1_frequency;

	/* Current घड़ीs */
	uपूर्णांक16_t			current_gfxclk;
	uपूर्णांक16_t			current_socclk;
	uपूर्णांक16_t			current_uclk;
	uपूर्णांक16_t			current_vclk0;
	uपूर्णांक16_t			current_dclk0;
	uपूर्णांक16_t			current_vclk1;
	uपूर्णांक16_t			current_dclk1;

	/* Throttle status */
	uपूर्णांक32_t			throttle_status;

	/* Fans */
	uपूर्णांक16_t			current_fan_speed;

	/* Link width/speed */
	uपूर्णांक16_t			pcie_link_width;
	uपूर्णांक16_t			pcie_link_speed; // in 0.1 GT/s

	uपूर्णांक16_t			padding;

	uपूर्णांक32_t			gfx_activity_acc;
	uपूर्णांक32_t			mem_activity_acc;

	uपूर्णांक16_t			temperature_hbm[NUM_HBM_INSTANCES];
पूर्ण;

/*
 * gpu_metrics_v2_0 is not recommended as it's not naturally aligned.
 * Use gpu_metrics_v2_1 or later instead.
 */
काष्ठा gpu_metrics_v2_0 अणु
	काष्ठा metrics_table_header	common_header;

	/* Driver attached बारtamp (in ns) */
	uपूर्णांक64_t			प्रणाली_घड़ी_counter;

	/* Temperature */
	uपूर्णांक16_t			temperature_gfx; // gfx temperature on APUs
	uपूर्णांक16_t			temperature_soc; // soc temperature on APUs
	uपूर्णांक16_t			temperature_core[8]; // CPU core temperature on APUs
	uपूर्णांक16_t			temperature_l3[2];

	/* Utilization */
	uपूर्णांक16_t			average_gfx_activity;
	uपूर्णांक16_t			average_mm_activity; // UVD or VCN

	/* Power/Energy */
	uपूर्णांक16_t			average_socket_घातer; // dGPU + APU घातer on A + A platक्रमm
	uपूर्णांक16_t			average_cpu_घातer;
	uपूर्णांक16_t			average_soc_घातer;
	uपूर्णांक16_t			average_gfx_घातer;
	uपूर्णांक16_t			average_core_घातer[8]; // CPU core घातer on APUs

	/* Average घड़ीs */
	uपूर्णांक16_t			average_gfxclk_frequency;
	uपूर्णांक16_t			average_socclk_frequency;
	uपूर्णांक16_t			average_uclk_frequency;
	uपूर्णांक16_t			average_fclk_frequency;
	uपूर्णांक16_t			average_vclk_frequency;
	uपूर्णांक16_t			average_dclk_frequency;

	/* Current घड़ीs */
	uपूर्णांक16_t			current_gfxclk;
	uपूर्णांक16_t			current_socclk;
	uपूर्णांक16_t			current_uclk;
	uपूर्णांक16_t			current_fclk;
	uपूर्णांक16_t			current_vclk;
	uपूर्णांक16_t			current_dclk;
	uपूर्णांक16_t			current_coreclk[8]; // CPU core घड़ीs
	uपूर्णांक16_t			current_l3clk[2];

	/* Throttle status */
	uपूर्णांक32_t			throttle_status;

	/* Fans */
	uपूर्णांक16_t			fan_pwm;

	uपूर्णांक16_t			padding;
पूर्ण;

काष्ठा gpu_metrics_v2_1 अणु
	काष्ठा metrics_table_header	common_header;

	/* Temperature */
	uपूर्णांक16_t			temperature_gfx; // gfx temperature on APUs
	uपूर्णांक16_t			temperature_soc; // soc temperature on APUs
	uपूर्णांक16_t			temperature_core[8]; // CPU core temperature on APUs
	uपूर्णांक16_t			temperature_l3[2];

	/* Utilization */
	uपूर्णांक16_t			average_gfx_activity;
	uपूर्णांक16_t			average_mm_activity; // UVD or VCN

	/* Driver attached बारtamp (in ns) */
	uपूर्णांक64_t			प्रणाली_घड़ी_counter;

	/* Power/Energy */
	uपूर्णांक16_t			average_socket_घातer; // dGPU + APU घातer on A + A platक्रमm
	uपूर्णांक16_t			average_cpu_घातer;
	uपूर्णांक16_t			average_soc_घातer;
	uपूर्णांक16_t			average_gfx_घातer;
	uपूर्णांक16_t			average_core_घातer[8]; // CPU core घातer on APUs

	/* Average घड़ीs */
	uपूर्णांक16_t			average_gfxclk_frequency;
	uपूर्णांक16_t			average_socclk_frequency;
	uपूर्णांक16_t			average_uclk_frequency;
	uपूर्णांक16_t			average_fclk_frequency;
	uपूर्णांक16_t			average_vclk_frequency;
	uपूर्णांक16_t			average_dclk_frequency;

	/* Current घड़ीs */
	uपूर्णांक16_t			current_gfxclk;
	uपूर्णांक16_t			current_socclk;
	uपूर्णांक16_t			current_uclk;
	uपूर्णांक16_t			current_fclk;
	uपूर्णांक16_t			current_vclk;
	uपूर्णांक16_t			current_dclk;
	uपूर्णांक16_t			current_coreclk[8]; // CPU core घड़ीs
	uपूर्णांक16_t			current_l3clk[2];

	/* Throttle status */
	uपूर्णांक32_t			throttle_status;

	/* Fans */
	uपूर्णांक16_t			fan_pwm;

	uपूर्णांक16_t			padding[3];
पूर्ण;

#पूर्ण_अगर
