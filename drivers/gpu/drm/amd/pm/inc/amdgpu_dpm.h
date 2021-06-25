<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __AMDGPU_DPM_H__
#घोषणा __AMDGPU_DPM_H__

क्रमागत amdgpu_पूर्णांक_thermal_type अणु
	THERMAL_TYPE_NONE,
	THERMAL_TYPE_EXTERNAL,
	THERMAL_TYPE_EXTERNAL_GPIO,
	THERMAL_TYPE_RV6XX,
	THERMAL_TYPE_RV770,
	THERMAL_TYPE_ADT7473_WITH_INTERNAL,
	THERMAL_TYPE_EVERGREEN,
	THERMAL_TYPE_SUMO,
	THERMAL_TYPE_NI,
	THERMAL_TYPE_SI,
	THERMAL_TYPE_EMC2103_WITH_INTERNAL,
	THERMAL_TYPE_CI,
	THERMAL_TYPE_KV,
पूर्ण;

क्रमागत amdgpu_dpm_स्वतः_throttle_src अणु
	AMDGPU_DPM_AUTO_THROTTLE_SRC_THERMAL,
	AMDGPU_DPM_AUTO_THROTTLE_SRC_EXTERNAL
पूर्ण;

क्रमागत amdgpu_dpm_event_src अणु
	AMDGPU_DPM_EVENT_SRC_ANALOG = 0,
	AMDGPU_DPM_EVENT_SRC_EXTERNAL = 1,
	AMDGPU_DPM_EVENT_SRC_DIGITAL = 2,
	AMDGPU_DPM_EVENT_SRC_ANALOG_OR_EXTERNAL = 3,
	AMDGPU_DPM_EVENT_SRC_DIGIAL_OR_EXTERNAL = 4
पूर्ण;

काष्ठा amdgpu_ps अणु
	u32 caps; /* vbios flags */
	u32 class; /* vbios flags */
	u32 class2; /* vbios flags */
	/* UVD घड़ीs */
	u32 vclk;
	u32 dclk;
	/* VCE घड़ीs */
	u32 evclk;
	u32 ecclk;
	bool vce_active;
	क्रमागत amd_vce_level vce_level;
	/* asic priv */
	व्योम *ps_priv;
पूर्ण;

काष्ठा amdgpu_dpm_thermal अणु
	/* thermal पूर्णांकerrupt work */
	काष्ठा work_काष्ठा work;
	/* low temperature threshold */
	पूर्णांक                min_temp;
	/* high temperature threshold */
	पूर्णांक                max_temp;
	/* edge max emergency(shutकरोwn) temp */
	पूर्णांक                max_edge_emergency_temp;
	/* hotspot low temperature threshold */
	पूर्णांक                min_hotspot_temp;
	/* hotspot high temperature critical threshold */
	पूर्णांक                max_hotspot_crit_temp;
	/* hotspot max emergency(shutकरोwn) temp */
	पूर्णांक                max_hotspot_emergency_temp;
	/* memory low temperature threshold */
	पूर्णांक                min_mem_temp;
	/* memory high temperature critical threshold */
	पूर्णांक                max_mem_crit_temp;
	/* memory max emergency(shutकरोwn) temp */
	पूर्णांक                max_mem_emergency_temp;
	/* was last पूर्णांकerrupt low to high or high to low */
	bool               high_to_low;
	/* पूर्णांकerrupt source */
	काष्ठा amdgpu_irq_src	irq;
पूर्ण;

क्रमागत amdgpu_clk_action
अणु
	AMDGPU_SCLK_UP = 1,
	AMDGPU_SCLK_DOWN
पूर्ण;

काष्ठा amdgpu_blacklist_घड़ीs
अणु
	u32 sclk;
	u32 mclk;
	क्रमागत amdgpu_clk_action action;
पूर्ण;

काष्ठा amdgpu_घड़ी_and_voltage_limits अणु
	u32 sclk;
	u32 mclk;
	u16 vddc;
	u16 vddci;
पूर्ण;

काष्ठा amdgpu_घड़ी_array अणु
	u32 count;
	u32 *values;
पूर्ण;

काष्ठा amdgpu_घड़ी_voltage_dependency_entry अणु
	u32 clk;
	u16 v;
पूर्ण;

काष्ठा amdgpu_घड़ी_voltage_dependency_table अणु
	u32 count;
	काष्ठा amdgpu_घड़ी_voltage_dependency_entry *entries;
पूर्ण;

जोड़ amdgpu_cac_leakage_entry अणु
	काष्ठा अणु
		u16 vddc;
		u32 leakage;
	पूर्ण;
	काष्ठा अणु
		u16 vddc1;
		u16 vddc2;
		u16 vddc3;
	पूर्ण;
पूर्ण;

काष्ठा amdgpu_cac_leakage_table अणु
	u32 count;
	जोड़ amdgpu_cac_leakage_entry *entries;
पूर्ण;

काष्ठा amdgpu_phase_shedding_limits_entry अणु
	u16 voltage;
	u32 sclk;
	u32 mclk;
पूर्ण;

काष्ठा amdgpu_phase_shedding_limits_table अणु
	u32 count;
	काष्ठा amdgpu_phase_shedding_limits_entry *entries;
पूर्ण;

काष्ठा amdgpu_uvd_घड़ी_voltage_dependency_entry अणु
	u32 vclk;
	u32 dclk;
	u16 v;
पूर्ण;

काष्ठा amdgpu_uvd_घड़ी_voltage_dependency_table अणु
	u8 count;
	काष्ठा amdgpu_uvd_घड़ी_voltage_dependency_entry *entries;
पूर्ण;

काष्ठा amdgpu_vce_घड़ी_voltage_dependency_entry अणु
	u32 ecclk;
	u32 evclk;
	u16 v;
पूर्ण;

काष्ठा amdgpu_vce_घड़ी_voltage_dependency_table अणु
	u8 count;
	काष्ठा amdgpu_vce_घड़ी_voltage_dependency_entry *entries;
पूर्ण;

काष्ठा amdgpu_ppm_table अणु
	u8 ppm_design;
	u16 cpu_core_number;
	u32 platक्रमm_tdp;
	u32 small_ac_platक्रमm_tdp;
	u32 platक्रमm_tdc;
	u32 small_ac_platक्रमm_tdc;
	u32 apu_tdp;
	u32 dgpu_tdp;
	u32 dgpu_ulv_घातer;
	u32 tj_max;
पूर्ण;

काष्ठा amdgpu_cac_tdp_table अणु
	u16 tdp;
	u16 configurable_tdp;
	u16 tdc;
	u16 battery_घातer_limit;
	u16 small_घातer_limit;
	u16 low_cac_leakage;
	u16 high_cac_leakage;
	u16 maximum_घातer_delivery_limit;
पूर्ण;

काष्ठा amdgpu_dpm_dynamic_state अणु
	काष्ठा amdgpu_घड़ी_voltage_dependency_table vddc_dependency_on_sclk;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table vddci_dependency_on_mclk;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table vddc_dependency_on_mclk;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table mvdd_dependency_on_mclk;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table vddc_dependency_on_dispclk;
	काष्ठा amdgpu_uvd_घड़ी_voltage_dependency_table uvd_घड़ी_voltage_dependency_table;
	काष्ठा amdgpu_vce_घड़ी_voltage_dependency_table vce_घड़ी_voltage_dependency_table;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table samu_घड़ी_voltage_dependency_table;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table acp_घड़ी_voltage_dependency_table;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table vddgfx_dependency_on_sclk;
	काष्ठा amdgpu_घड़ी_array valid_sclk_values;
	काष्ठा amdgpu_घड़ी_array valid_mclk_values;
	काष्ठा amdgpu_घड़ी_and_voltage_limits max_घड़ी_voltage_on_dc;
	काष्ठा amdgpu_घड़ी_and_voltage_limits max_घड़ी_voltage_on_ac;
	u32 mclk_sclk_ratio;
	u32 sclk_mclk_delta;
	u16 vddc_vddci_delta;
	u16 min_vddc_क्रम_pcie_gen2;
	काष्ठा amdgpu_cac_leakage_table cac_leakage_table;
	काष्ठा amdgpu_phase_shedding_limits_table phase_shedding_limits_table;
	काष्ठा amdgpu_ppm_table *ppm_table;
	काष्ठा amdgpu_cac_tdp_table *cac_tdp_table;
पूर्ण;

काष्ठा amdgpu_dpm_fan अणु
	u16 t_min;
	u16 t_med;
	u16 t_high;
	u16 pwm_min;
	u16 pwm_med;
	u16 pwm_high;
	u8 t_hyst;
	u32 cycle_delay;
	u16 t_max;
	u8 control_mode;
	u16 शेष_max_fan_pwm;
	u16 शेष_fan_output_sensitivity;
	u16 fan_output_sensitivity;
	bool ucode_fan_control;
पूर्ण;

क्रमागत amdgpu_pcie_gen अणु
	AMDGPU_PCIE_GEN1 = 0,
	AMDGPU_PCIE_GEN2 = 1,
	AMDGPU_PCIE_GEN3 = 2,
	AMDGPU_PCIE_GEN_INVALID = 0xffff
पूर्ण;

#घोषणा amdgpu_dpm_pre_set_घातer_state(adev) \
		((adev)->घातerplay.pp_funcs->pre_set_घातer_state((adev)->घातerplay.pp_handle))

#घोषणा amdgpu_dpm_set_घातer_state(adev) \
		((adev)->घातerplay.pp_funcs->set_घातer_state((adev)->घातerplay.pp_handle))

#घोषणा amdgpu_dpm_post_set_घातer_state(adev) \
		((adev)->घातerplay.pp_funcs->post_set_घातer_state((adev)->घातerplay.pp_handle))

#घोषणा amdgpu_dpm_display_configuration_changed(adev) \
		((adev)->घातerplay.pp_funcs->display_configuration_changed((adev)->घातerplay.pp_handle))

#घोषणा amdgpu_dpm_prपूर्णांक_घातer_state(adev, ps) \
		((adev)->घातerplay.pp_funcs->prपूर्णांक_घातer_state((adev)->घातerplay.pp_handle, (ps)))

#घोषणा amdgpu_dpm_vblank_too_लघु(adev) \
		((adev)->घातerplay.pp_funcs->vblank_too_लघु((adev)->घातerplay.pp_handle))

#घोषणा amdgpu_dpm_enable_bapm(adev, e) \
		((adev)->घातerplay.pp_funcs->enable_bapm((adev)->घातerplay.pp_handle, (e)))

#घोषणा amdgpu_dpm_set_fan_control_mode(adev, m) \
		((adev)->घातerplay.pp_funcs->set_fan_control_mode((adev)->घातerplay.pp_handle, (m)))

#घोषणा amdgpu_dpm_get_fan_control_mode(adev) \
		((adev)->घातerplay.pp_funcs->get_fan_control_mode((adev)->घातerplay.pp_handle))

#घोषणा amdgpu_dpm_set_fan_speed_percent(adev, s) \
		((adev)->घातerplay.pp_funcs->set_fan_speed_percent((adev)->घातerplay.pp_handle, (s)))

#घोषणा amdgpu_dpm_get_fan_speed_percent(adev, s) \
		((adev)->घातerplay.pp_funcs->get_fan_speed_percent((adev)->घातerplay.pp_handle, (s)))

#घोषणा amdgpu_dpm_get_fan_speed_rpm(adev, s) \
		((adev)->घातerplay.pp_funcs->get_fan_speed_rpm)((adev)->घातerplay.pp_handle, (s))

#घोषणा amdgpu_dpm_set_fan_speed_rpm(adev, s) \
		((adev)->घातerplay.pp_funcs->set_fan_speed_rpm)((adev)->घातerplay.pp_handle, (s))

#घोषणा amdgpu_dpm_क्रमce_perक्रमmance_level(adev, l) \
		((adev)->घातerplay.pp_funcs->क्रमce_perक्रमmance_level((adev)->घातerplay.pp_handle, (l)))

#घोषणा amdgpu_dpm_get_current_घातer_state(adev) \
		((adev)->घातerplay.pp_funcs->get_current_घातer_state((adev)->घातerplay.pp_handle))

#घोषणा amdgpu_dpm_get_pp_num_states(adev, data) \
		((adev)->घातerplay.pp_funcs->get_pp_num_states((adev)->घातerplay.pp_handle, data))

#घोषणा amdgpu_dpm_get_pp_table(adev, table) \
		((adev)->घातerplay.pp_funcs->get_pp_table((adev)->घातerplay.pp_handle, table))

#घोषणा amdgpu_dpm_set_pp_table(adev, buf, size) \
		((adev)->घातerplay.pp_funcs->set_pp_table((adev)->घातerplay.pp_handle, buf, size))

#घोषणा amdgpu_dpm_prपूर्णांक_घड़ी_levels(adev, type, buf) \
		((adev)->घातerplay.pp_funcs->prपूर्णांक_घड़ी_levels((adev)->घातerplay.pp_handle, type, buf))

#घोषणा amdgpu_dpm_क्रमce_घड़ी_level(adev, type, level) \
		((adev)->घातerplay.pp_funcs->क्रमce_घड़ी_level((adev)->घातerplay.pp_handle, type, level))

#घोषणा amdgpu_dpm_get_sclk_od(adev) \
		((adev)->घातerplay.pp_funcs->get_sclk_od((adev)->घातerplay.pp_handle))

#घोषणा amdgpu_dpm_set_sclk_od(adev, value) \
		((adev)->घातerplay.pp_funcs->set_sclk_od((adev)->घातerplay.pp_handle, value))

#घोषणा amdgpu_dpm_get_mclk_od(adev) \
		((adev)->घातerplay.pp_funcs->get_mclk_od((adev)->घातerplay.pp_handle))

#घोषणा amdgpu_dpm_set_mclk_od(adev, value) \
		((adev)->घातerplay.pp_funcs->set_mclk_od((adev)->घातerplay.pp_handle, value))

#घोषणा amdgpu_dpm_dispatch_task(adev, task_id, user_state)		\
		((adev)->घातerplay.pp_funcs->dispatch_tasks)((adev)->घातerplay.pp_handle, (task_id), (user_state))

#घोषणा amdgpu_dpm_check_state_equal(adev, cps, rps, equal) \
		((adev)->घातerplay.pp_funcs->check_state_equal((adev)->घातerplay.pp_handle, (cps), (rps), (equal)))

#घोषणा amdgpu_dpm_get_vce_घड़ी_state(adev, i)				\
		((adev)->घातerplay.pp_funcs->get_vce_घड़ी_state((adev)->घातerplay.pp_handle, (i)))

#घोषणा amdgpu_dpm_get_perक्रमmance_level(adev)				\
		((adev)->घातerplay.pp_funcs->get_perक्रमmance_level((adev)->घातerplay.pp_handle))

#घोषणा amdgpu_dpm_reset_घातer_profile_state(adev, request) \
		((adev)->घातerplay.pp_funcs->reset_घातer_profile_state(\
			(adev)->घातerplay.pp_handle, request))

#घोषणा amdgpu_dpm_get_घातer_profile_mode(adev, buf) \
		((adev)->घातerplay.pp_funcs->get_घातer_profile_mode(\
			(adev)->घातerplay.pp_handle, buf))

#घोषणा amdgpu_dpm_set_घातer_profile_mode(adev, parameter, size) \
		((adev)->घातerplay.pp_funcs->set_घातer_profile_mode(\
			(adev)->घातerplay.pp_handle, parameter, size))

#घोषणा amdgpu_dpm_set_fine_grain_clk_vol(adev, type, parameter, size) \
		((adev)->घातerplay.pp_funcs->set_fine_grain_clk_vol(\
			(adev)->घातerplay.pp_handle, type, parameter, size))

#घोषणा amdgpu_dpm_odn_edit_dpm_table(adev, type, parameter, size) \
		((adev)->घातerplay.pp_funcs->odn_edit_dpm_table(\
			(adev)->घातerplay.pp_handle, type, parameter, size))

#घोषणा amdgpu_dpm_get_ppfeature_status(adev, buf) \
		((adev)->घातerplay.pp_funcs->get_ppfeature_status(\
			(adev)->घातerplay.pp_handle, (buf)))

#घोषणा amdgpu_dpm_set_ppfeature_status(adev, ppfeatures) \
		((adev)->घातerplay.pp_funcs->set_ppfeature_status(\
			(adev)->घातerplay.pp_handle, (ppfeatures)))

#घोषणा amdgpu_dpm_get_gpu_metrics(adev, table) \
		((adev)->घातerplay.pp_funcs->get_gpu_metrics((adev)->घातerplay.pp_handle, table))

काष्ठा amdgpu_dpm अणु
	काष्ठा amdgpu_ps        *ps;
	/* number of valid घातer states */
	पूर्णांक                     num_ps;
	/* current घातer state that is active */
	काष्ठा amdgpu_ps        *current_ps;
	/* requested घातer state */
	काष्ठा amdgpu_ps        *requested_ps;
	/* boot up घातer state */
	काष्ठा amdgpu_ps        *boot_ps;
	/* शेष uvd घातer state */
	काष्ठा amdgpu_ps        *uvd_ps;
	/* vce requirements */
	u32                  num_of_vce_states;
	काष्ठा amd_vce_state vce_states[AMD_MAX_VCE_LEVELS];
	क्रमागत amd_vce_level vce_level;
	क्रमागत amd_pm_state_type state;
	क्रमागत amd_pm_state_type user_state;
	क्रमागत amd_pm_state_type last_state;
	क्रमागत amd_pm_state_type last_user_state;
	u32                     platक्रमm_caps;
	u32                     voltage_response_समय;
	u32                     backbias_response_समय;
	व्योम                    *priv;
	u32			new_active_crtcs;
	पूर्णांक			new_active_crtc_count;
	u32			current_active_crtcs;
	पूर्णांक			current_active_crtc_count;
	काष्ठा amdgpu_dpm_dynamic_state dyn_state;
	काष्ठा amdgpu_dpm_fan fan;
	u32 tdp_limit;
	u32 near_tdp_limit;
	u32 near_tdp_limit_adjusted;
	u32 sq_ramping_threshold;
	u32 cac_leakage;
	u16 tdp_od_limit;
	u32 tdp_adjusपंचांगent;
	u16 load_line_slope;
	bool घातer_control;
	/* special states active */
	bool                    thermal_active;
	bool                    uvd_active;
	bool                    vce_active;
	/* thermal handling */
	काष्ठा amdgpu_dpm_thermal thermal;
	/* क्रमced levels */
	क्रमागत amd_dpm_क्रमced_level क्रमced_level;
पूर्ण;

काष्ठा amdgpu_pm अणु
	काष्ठा mutex		mutex;
	u32                     current_sclk;
	u32                     current_mclk;
	u32                     शेष_sclk;
	u32                     शेष_mclk;
	काष्ठा amdgpu_i2c_chan *i2c_bus;
	bool                    bus_locked;
	/* पूर्णांकernal thermal controller on rv6xx+ */
	क्रमागत amdgpu_पूर्णांक_thermal_type पूर्णांक_thermal_type;
	काष्ठा device	        *पूर्णांक_hwmon_dev;
	/* fan control parameters */
	bool                    no_fan;
	u8                      fan_pulses_per_revolution;
	u8                      fan_min_rpm;
	u8                      fan_max_rpm;
	/* dpm */
	bool                    dpm_enabled;
	bool                    sysfs_initialized;
	काष्ठा amdgpu_dpm       dpm;
	स्थिर काष्ठा firmware	*fw;	/* SMC firmware */
	uपूर्णांक32_t                fw_version;
	uपूर्णांक32_t                pcie_gen_mask;
	uपूर्णांक32_t                pcie_mlw_mask;
	काष्ठा amd_pp_display_configuration pm_display_cfg;/* set by dc */
	uपूर्णांक32_t                smu_prv_buffer_size;
	काष्ठा amdgpu_bo        *smu_prv_buffer;
	bool ac_घातer;
	/* घातerplay feature */
	uपूर्णांक32_t pp_feature;

	/* Used क्रम I2C access to various EEPROMs on relevant ASICs */
	काष्ठा i2c_adapter smu_i2c;
	काष्ठा list_head	pm_attr_list;
पूर्ण;

#घोषणा R600_SSTU_DFLT                               0
#घोषणा R600_SST_DFLT                                0x00C8

/* XXX are these ok? */
#घोषणा R600_TEMP_RANGE_MIN (90 * 1000)
#घोषणा R600_TEMP_RANGE_MAX (120 * 1000)

#घोषणा FDO_PWM_MODE_STATIC  1
#घोषणा FDO_PWM_MODE_STATIC_RPM 5

क्रमागत amdgpu_td अणु
	AMDGPU_TD_AUTO,
	AMDGPU_TD_UP,
	AMDGPU_TD_DOWN,
पूर्ण;

क्रमागत amdgpu_display_watermark अणु
	AMDGPU_DISPLAY_WATERMARK_LOW = 0,
	AMDGPU_DISPLAY_WATERMARK_HIGH = 1,
पूर्ण;

क्रमागत amdgpu_display_gap
अणु
    AMDGPU_PM_DISPLAY_GAP_VBLANK_OR_WM = 0,
    AMDGPU_PM_DISPLAY_GAP_VBLANK       = 1,
    AMDGPU_PM_DISPLAY_GAP_WATERMARK    = 2,
    AMDGPU_PM_DISPLAY_GAP_IGNORE       = 3,
पूर्ण;

व्योम amdgpu_dpm_prपूर्णांक_class_info(u32 class, u32 class2);
व्योम amdgpu_dpm_prपूर्णांक_cap_info(u32 caps);
व्योम amdgpu_dpm_prपूर्णांक_ps_status(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_ps *rps);
u32 amdgpu_dpm_get_vblank_समय(काष्ठा amdgpu_device *adev);
u32 amdgpu_dpm_get_vrefresh(काष्ठा amdgpu_device *adev);
व्योम amdgpu_dpm_get_active_displays(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_dpm_पढ़ो_sensor(काष्ठा amdgpu_device *adev, क्रमागत amd_pp_sensors sensor,
			   व्योम *data, uपूर्णांक32_t *size);

bool amdgpu_is_पूर्णांकernal_thermal_sensor(क्रमागत amdgpu_पूर्णांक_thermal_type sensor);

पूर्णांक amdgpu_get_platक्रमm_caps(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_parse_extended_घातer_table(काष्ठा amdgpu_device *adev);
व्योम amdgpu_मुक्त_extended_घातer_table(काष्ठा amdgpu_device *adev);

व्योम amdgpu_add_thermal_controller(काष्ठा amdgpu_device *adev);

क्रमागत amdgpu_pcie_gen amdgpu_get_pcie_gen_support(काष्ठा amdgpu_device *adev,
						 u32 sys_mask,
						 क्रमागत amdgpu_pcie_gen asic_gen,
						 क्रमागत amdgpu_pcie_gen शेष_gen);

काष्ठा amd_vce_state*
amdgpu_get_vce_घड़ी_state(व्योम *handle, u32 idx);

पूर्णांक amdgpu_dpm_set_घातergating_by_smu(काष्ठा amdgpu_device *adev,
				      uपूर्णांक32_t block_type, bool gate);

बाह्य पूर्णांक amdgpu_dpm_get_sclk(काष्ठा amdgpu_device *adev, bool low);

बाह्य पूर्णांक amdgpu_dpm_get_mclk(काष्ठा amdgpu_device *adev, bool low);

पूर्णांक amdgpu_dpm_set_xgmi_pstate(काष्ठा amdgpu_device *adev,
			       uपूर्णांक32_t pstate);

पूर्णांक amdgpu_dpm_चयन_घातer_profile(काष्ठा amdgpu_device *adev,
				    क्रमागत PP_SMC_POWER_PROखाता type,
				    bool en);

पूर्णांक amdgpu_dpm_baco_reset(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_dpm_mode2_reset(काष्ठा amdgpu_device *adev);

bool amdgpu_dpm_is_baco_supported(काष्ठा amdgpu_device *adev);

bool amdgpu_dpm_is_mode1_reset_supported(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_dpm_mode1_reset(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_dpm_set_mp1_state(काष्ठा amdgpu_device *adev,
			     क्रमागत pp_mp1_state mp1_state);

पूर्णांक amdgpu_dpm_baco_निकास(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_dpm_baco_enter(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_dpm_set_df_cstate(काष्ठा amdgpu_device *adev,
			     uपूर्णांक32_t cstate);

पूर्णांक amdgpu_dpm_allow_xgmi_घातer_करोwn(काष्ठा amdgpu_device *adev, bool en);

पूर्णांक amdgpu_dpm_enable_mgpu_fan_boost(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_dpm_set_घड़ीgating_by_smu(काष्ठा amdgpu_device *adev,
				      uपूर्णांक32_t msg_id);

पूर्णांक amdgpu_dpm_smu_i2c_bus_access(काष्ठा amdgpu_device *adev,
				  bool acquire);

व्योम amdgpu_pm_acpi_event_handler(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_dpm_पढ़ो_sensor(काष्ठा amdgpu_device *adev, क्रमागत amd_pp_sensors sensor,
			   व्योम *data, uपूर्णांक32_t *size);

व्योम amdgpu_dpm_thermal_work_handler(काष्ठा work_काष्ठा *work);

व्योम amdgpu_pm_compute_घड़ीs(काष्ठा amdgpu_device *adev);
व्योम amdgpu_dpm_enable_uvd(काष्ठा amdgpu_device *adev, bool enable);
व्योम amdgpu_dpm_enable_vce(काष्ठा amdgpu_device *adev, bool enable);
व्योम amdgpu_dpm_enable_jpeg(काष्ठा amdgpu_device *adev, bool enable);
व्योम amdgpu_pm_prपूर्णांक_घातer_states(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_pm_load_smu_firmware(काष्ठा amdgpu_device *adev, uपूर्णांक32_t *smu_version);

#पूर्ण_अगर
