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

#अगर_अघोषित _SMU7_THERMAL_H_
#घोषणा _SMU7_THERMAL_H_

#समावेश "hwmgr.h"

#घोषणा SMU7_THERMAL_HIGH_ALERT_MASK         0x1
#घोषणा SMU7_THERMAL_LOW_ALERT_MASK          0x2

#घोषणा SMU7_THERMAL_MINIMUM_TEMP_READING    -256
#घोषणा SMU7_THERMAL_MAXIMUM_TEMP_READING    255

#घोषणा SMU7_THERMAL_MINIMUM_ALERT_TEMP      0
#घोषणा SMU7_THERMAL_MAXIMUM_ALERT_TEMP      255

#घोषणा FDO_PWM_MODE_STATIC  1
#घोषणा FDO_PWM_MODE_STATIC_RPM 5

बाह्य पूर्णांक smu7_thermal_get_temperature(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smu7_thermal_stop_thermal_controller(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smu7_fan_ctrl_get_fan_speed_info(काष्ठा pp_hwmgr *hwmgr, काष्ठा phm_fan_speed_info *fan_speed_info);
बाह्य पूर्णांक smu7_fan_ctrl_get_fan_speed_percent(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *speed);
बाह्य पूर्णांक smu7_fan_ctrl_set_शेष_mode(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smu7_fan_ctrl_set_अटल_mode(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t mode);
बाह्य पूर्णांक smu7_fan_ctrl_set_fan_speed_percent(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t speed);
बाह्य पूर्णांक smu7_fan_ctrl_reset_fan_speed_to_शेष(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smu7_thermal_ctrl_uninitialize_thermal_controller(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smu7_fan_ctrl_set_fan_speed_rpm(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t speed);
बाह्य पूर्णांक smu7_fan_ctrl_get_fan_speed_rpm(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *speed);
बाह्य पूर्णांक smu7_fan_ctrl_stop_smc_fan_control(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smu7_thermal_disable_alert(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smu7_fan_ctrl_start_smc_fan_control(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smu7_start_thermal_controller(काष्ठा pp_hwmgr *hwmgr,
				काष्ठा PP_TemperatureRange *temperature_range);
#पूर्ण_अगर

