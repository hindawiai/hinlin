<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
 */

#अगर_अघोषित __SMU_INTERNAL_H__
#घोषणा __SMU_INTERNAL_H__

#समावेश "amdgpu_smu.h"

#अगर defined(SWSMU_CODE_LAYER_L1)

#घोषणा smu_ppt_funcs(पूर्णांकf, ret, smu, args...) \
	((smu)->ppt_funcs ? ((smu)->ppt_funcs->पूर्णांकf ? (smu)->ppt_funcs->पूर्णांकf(smu, ##args) : ret) : -EINVAL)

#घोषणा smu_init_microcode(smu)						smu_ppt_funcs(init_microcode, 0, smu)
#घोषणा smu_fini_microcode(smu)						smu_ppt_funcs(fini_microcode, 0, smu)
#घोषणा smu_init_smc_tables(smu)					smu_ppt_funcs(init_smc_tables, 0, smu)
#घोषणा smu_fini_smc_tables(smu)					smu_ppt_funcs(fini_smc_tables, 0, smu)
#घोषणा smu_init_घातer(smu)						smu_ppt_funcs(init_घातer,	0, smu)
#घोषणा smu_fini_घातer(smu)						smu_ppt_funcs(fini_घातer, 0, smu)
#घोषणा smu_setup_pptable(smu)						smu_ppt_funcs(setup_pptable, 0, smu)
#घोषणा smu_घातergate_sdma(smu, gate)					smu_ppt_funcs(घातergate_sdma, 0, smu, gate)
#घोषणा smu_get_vbios_bootup_values(smu)				smu_ppt_funcs(get_vbios_bootup_values, 0, smu)
#घोषणा smu_check_fw_version(smu)					smu_ppt_funcs(check_fw_version, 0, smu)
#घोषणा smu_ग_लिखो_pptable(smu)						smu_ppt_funcs(ग_लिखो_pptable, 0, smu)
#घोषणा smu_set_min_dcef_deep_sleep(smu, clk)				smu_ppt_funcs(set_min_dcef_deep_sleep, 0, smu, clk)
#घोषणा smu_set_driver_table_location(smu)				smu_ppt_funcs(set_driver_table_location, 0, smu)
#घोषणा smu_set_tool_table_location(smu)				smu_ppt_funcs(set_tool_table_location, 0, smu)
#घोषणा smu_notअगरy_memory_pool_location(smu)				smu_ppt_funcs(notअगरy_memory_pool_location, 0, smu)
#घोषणा smu_gfx_off_control(smu, enable)				smu_ppt_funcs(gfx_off_control, 0, smu, enable)
#घोषणा smu_get_gfx_off_status(smu)						smu_ppt_funcs(get_gfx_off_status, 0, smu)
#घोषणा smu_set_last_dcef_min_deep_sleep_clk(smu)			smu_ppt_funcs(set_last_dcef_min_deep_sleep_clk, 0, smu)
#घोषणा smu_प्रणाली_features_control(smu, en)				smu_ppt_funcs(प्रणाली_features_control, 0, smu, en)
#घोषणा smu_init_max_sustainable_घड़ीs(smu)				smu_ppt_funcs(init_max_sustainable_घड़ीs, 0, smu)
#घोषणा smu_set_शेष_od_settings(smu)				smu_ppt_funcs(set_शेष_od_settings, 0, smu)
#घोषणा smu_send_smc_msg_with_param(smu, msg, param, पढ़ो_arg)		smu_ppt_funcs(send_smc_msg_with_param, 0, smu, msg, param, पढ़ो_arg)
#घोषणा smu_send_smc_msg(smu, msg, पढ़ो_arg)				smu_ppt_funcs(send_smc_msg, 0, smu, msg, पढ़ो_arg)
#घोषणा smu_init_display_count(smu, count)				smu_ppt_funcs(init_display_count, 0, smu, count)
#घोषणा smu_feature_set_allowed_mask(smu)				smu_ppt_funcs(set_allowed_mask, 0, smu)
#घोषणा smu_feature_get_enabled_mask(smu, mask, num)			smu_ppt_funcs(get_enabled_mask, 0, smu, mask, num)
#घोषणा smu_feature_is_enabled(smu, mask)				smu_ppt_funcs(feature_is_enabled, 0, smu, mask)
#घोषणा smu_disable_all_features_with_exception(smu, mask)		smu_ppt_funcs(disable_all_features_with_exception, 0, smu, mask)
#घोषणा smu_is_dpm_running(smu)						smu_ppt_funcs(is_dpm_running, 0 , smu)
#घोषणा smu_notअगरy_display_change(smu)					smu_ppt_funcs(notअगरy_display_change, 0, smu)
#घोषणा smu_populate_umd_state_clk(smu)					smu_ppt_funcs(populate_umd_state_clk, 0, smu)
#घोषणा smu_enable_thermal_alert(smu)					smu_ppt_funcs(enable_thermal_alert, 0, smu)
#घोषणा smu_disable_thermal_alert(smu)					smu_ppt_funcs(disable_thermal_alert, 0, smu)
#घोषणा smu_smc_पढ़ो_sensor(smu, sensor, data, size)			smu_ppt_funcs(पढ़ो_sensor, -EINVAL, smu, sensor, data, size)
#घोषणा smu_pre_display_config_changed(smu)				smu_ppt_funcs(pre_display_config_changed, 0, smu)
#घोषणा smu_display_config_changed(smu)					smu_ppt_funcs(display_config_changed, 0 , smu)
#घोषणा smu_apply_घड़ीs_adjust_rules(smu)				smu_ppt_funcs(apply_घड़ीs_adjust_rules, 0, smu)
#घोषणा smu_notअगरy_smc_display_config(smu)				smu_ppt_funcs(notअगरy_smc_display_config, 0, smu)
#घोषणा smu_run_btc(smu)						smu_ppt_funcs(run_btc, 0, smu)
#घोषणा smu_get_allowed_feature_mask(smu, feature_mask, num)		smu_ppt_funcs(get_allowed_feature_mask, 0, smu, feature_mask, num)
#घोषणा smu_set_watermarks_table(smu, घड़ी_ranges)			smu_ppt_funcs(set_watermarks_table, 0, smu, घड़ी_ranges)
#घोषणा smu_thermal_temperature_range_update(smu, range, rw)		smu_ppt_funcs(thermal_temperature_range_update, 0, smu, range, rw)
#घोषणा smu_रेजिस्टर_irq_handler(smu)					smu_ppt_funcs(रेजिस्टर_irq_handler, 0, smu)
#घोषणा smu_get_dpm_ultimate_freq(smu, param, min, max)			smu_ppt_funcs(get_dpm_ultimate_freq, 0, smu, param, min, max)
#घोषणा smu_asic_set_perक्रमmance_level(smu, level)			smu_ppt_funcs(set_perक्रमmance_level, -EINVAL, smu, level)
#घोषणा smu_dump_pptable(smu)						smu_ppt_funcs(dump_pptable, 0, smu)
#घोषणा smu_update_pcie_parameters(smu, pcie_gen_cap, pcie_width_cap)	smu_ppt_funcs(update_pcie_parameters, 0, smu, pcie_gen_cap, pcie_width_cap)
#घोषणा smu_set_घातer_source(smu, घातer_src)				smu_ppt_funcs(set_घातer_source, 0, smu, घातer_src)
#घोषणा smu_i2c_init(smu, control)					smu_ppt_funcs(i2c_init, 0, smu, control)
#घोषणा smu_i2c_fini(smu, control)					smu_ppt_funcs(i2c_fini, 0, smu, control)
#घोषणा smu_get_unique_id(smu)						smu_ppt_funcs(get_unique_id, 0, smu)
#घोषणा smu_log_thermal_throttling(smu)					smu_ppt_funcs(log_thermal_throttling_event, 0, smu)
#घोषणा smu_get_asic_घातer_limits(smu)					smu_ppt_funcs(get_घातer_limit, 0, smu)
#घोषणा smu_get_pp_feature_mask(smu, buf)				smu_ppt_funcs(get_pp_feature_mask, 0, smu, buf)
#घोषणा smu_set_pp_feature_mask(smu, new_mask)				smu_ppt_funcs(set_pp_feature_mask, 0, smu, new_mask)
#घोषणा smu_gfx_ulv_control(smu, enablement)				smu_ppt_funcs(gfx_ulv_control, 0, smu, enablement)
#घोषणा smu_deep_sleep_control(smu, enablement)				smu_ppt_funcs(deep_sleep_control, 0, smu, enablement)
#घोषणा smu_get_fan_parameters(smu)					smu_ppt_funcs(get_fan_parameters, 0, smu)
#घोषणा smu_post_init(smu)						smu_ppt_funcs(post_init, 0, smu)
#घोषणा smu_gpo_control(smu, enablement)				smu_ppt_funcs(gpo_control, 0, smu, enablement)
#घोषणा smu_set_fine_grain_gfx_freq_parameters(smu)					smu_ppt_funcs(set_fine_grain_gfx_freq_parameters, 0, smu)

#पूर्ण_अगर
#पूर्ण_अगर
