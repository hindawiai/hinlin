<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  AMD SFH Report Descriptor generator
 *  Copyright 2020 Advanced Micro Devices, Inc.
 *  Authors: Nehal Bakulchandra Shah <Nehal-Bakulchandra.Shah@amd.com>
 *	     Sandeep Singh <sandeep.singh@amd.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश "amd_sfh_pcie.h"
#समावेश "amd_sfh_hid_desc.h"
#समावेश "amd_sfh_hid_report_desc.h"

#घोषणा	AMD_SFH_FW_MULTIPLIER (1000)
#घोषणा HID_USAGE_SENSOR_PROP_REPORTING_STATE_ALL_EVENTS_ENUM	0x41
#घोषणा HID_USAGE_SENSOR_PROP_POWER_STATE_D0_FULL_POWER_ENUM	0x51
#घोषणा HID_DEFAULT_REPORT_INTERVAL				0x50
#घोषणा HID_DEFAULT_MIN_VALUE					0X7F
#घोषणा HID_DEFAULT_MAX_VALUE					0x80
#घोषणा HID_DEFAULT_SENSITIVITY					0x7F
#घोषणा HID_USAGE_SENSOR_PROPERTY_CONNECTION_TYPE_PC_INTEGRATED_ENUM  0x01
/* state क्रमागतs */
#घोषणा HID_USAGE_SENSOR_STATE_READY_ENUM                             0x02
#घोषणा HID_USAGE_SENSOR_STATE_INITIALIZING_ENUM                      0x05
#घोषणा HID_USAGE_SENSOR_EVENT_DATA_UPDATED_ENUM                      0x04

पूर्णांक get_report_descriptor(पूर्णांक sensor_idx, u8 *rep_desc)
अणु
	चयन (sensor_idx) अणु
	हाल accel_idx: /* accel */
		स_रखो(rep_desc, 0, माप(accel3_report_descriptor));
		स_नकल(rep_desc, accel3_report_descriptor,
		       माप(accel3_report_descriptor));
		अवरोध;
	हाल gyro_idx: /* gyro */
		स_रखो(rep_desc, 0, माप(gyro3_report_descriptor));
		स_नकल(rep_desc, gyro3_report_descriptor,
		       माप(gyro3_report_descriptor));
		अवरोध;
	हाल mag_idx: /* Magnetometer */
		स_रखो(rep_desc, 0, माप(comp3_report_descriptor));
		स_नकल(rep_desc, comp3_report_descriptor,
		       माप(comp3_report_descriptor));
		अवरोध;
	हाल als_idx: /* ambient light sensor */
		स_रखो(rep_desc, 0, माप(als_report_descriptor));
		स_नकल(rep_desc, als_report_descriptor,
		       माप(als_report_descriptor));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

u32 get_descr_sz(पूर्णांक sensor_idx, पूर्णांक descriptor_name)
अणु
	चयन (sensor_idx) अणु
	हाल accel_idx:
		चयन (descriptor_name) अणु
		हाल descr_size:
			वापस माप(accel3_report_descriptor);
		हाल input_size:
			वापस माप(काष्ठा accel3_input_report);
		हाल feature_size:
			वापस माप(काष्ठा accel3_feature_report);
		पूर्ण
		अवरोध;
	हाल gyro_idx:
		चयन (descriptor_name) अणु
		हाल descr_size:
			वापस माप(gyro3_report_descriptor);
		हाल input_size:
			वापस माप(काष्ठा gyro_input_report);
		हाल feature_size:
			वापस माप(काष्ठा gyro_feature_report);
		पूर्ण
		अवरोध;
	हाल mag_idx:
		चयन (descriptor_name) अणु
		हाल descr_size:
			वापस माप(comp3_report_descriptor);
		हाल input_size:
			वापस माप(काष्ठा magno_input_report);
		हाल feature_size:
			वापस माप(काष्ठा magno_feature_report);
		पूर्ण
		अवरोध;
	हाल als_idx:
		चयन (descriptor_name) अणु
		हाल descr_size:
			वापस माप(als_report_descriptor);
		हाल input_size:
			वापस माप(काष्ठा als_input_report);
		हाल feature_size:
			वापस माप(काष्ठा als_feature_report);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम get_common_features(काष्ठा common_feature_property *common, पूर्णांक report_id)
अणु
	common->report_id = report_id;
	common->connection_type = HID_USAGE_SENSOR_PROPERTY_CONNECTION_TYPE_PC_INTEGRATED_ENUM;
	common->report_state = HID_USAGE_SENSOR_PROP_REPORTING_STATE_ALL_EVENTS_ENUM;
	common->घातer_state = HID_USAGE_SENSOR_PROP_POWER_STATE_D0_FULL_POWER_ENUM;
	common->sensor_state = HID_USAGE_SENSOR_STATE_INITIALIZING_ENUM;
	common->report_पूर्णांकerval =  HID_DEFAULT_REPORT_INTERVAL;
पूर्ण

u8 get_feature_report(पूर्णांक sensor_idx, पूर्णांक report_id, u8 *feature_report)
अणु
	काष्ठा accel3_feature_report acc_feature;
	काष्ठा gyro_feature_report gyro_feature;
	काष्ठा magno_feature_report magno_feature;
	काष्ठा als_feature_report als_feature;
	u8 report_size = 0;

	अगर (!feature_report)
		वापस report_size;

	चयन (sensor_idx) अणु
	हाल accel_idx: /* accel */
		get_common_features(&acc_feature.common_property, report_id);
		acc_feature.accel_change_sesnitivity = HID_DEFAULT_SENSITIVITY;
		acc_feature.accel_sensitivity_min = HID_DEFAULT_MIN_VALUE;
		acc_feature.accel_sensitivity_max = HID_DEFAULT_MAX_VALUE;
		स_नकल(feature_report, &acc_feature, माप(acc_feature));
		report_size = माप(acc_feature);
		अवरोध;
	हाल gyro_idx: /* gyro */
		get_common_features(&gyro_feature.common_property, report_id);
		gyro_feature.gyro_change_sesnitivity = HID_DEFAULT_SENSITIVITY;
		gyro_feature.gyro_sensitivity_min = HID_DEFAULT_MIN_VALUE;
		gyro_feature.gyro_sensitivity_max = HID_DEFAULT_MAX_VALUE;
		स_नकल(feature_report, &gyro_feature, माप(gyro_feature));
		report_size = माप(gyro_feature);
		अवरोध;
	हाल mag_idx: /* Magnetometer */
		get_common_features(&magno_feature.common_property, report_id);
		magno_feature.magno_headingchange_sensitivity = HID_DEFAULT_SENSITIVITY;
		magno_feature.heading_min = HID_DEFAULT_MIN_VALUE;
		magno_feature.heading_max = HID_DEFAULT_MAX_VALUE;
		magno_feature.flux_change_sensitivity = HID_DEFAULT_MIN_VALUE;
		magno_feature.flux_min = HID_DEFAULT_MIN_VALUE;
		magno_feature.flux_max = HID_DEFAULT_MAX_VALUE;
		स_नकल(feature_report, &magno_feature, माप(magno_feature));
		report_size = माप(magno_feature);
		अवरोध;
	हाल als_idx:  /* ambient light sensor */
		get_common_features(&als_feature.common_property, report_id);
		als_feature.als_change_sesnitivity = HID_DEFAULT_SENSITIVITY;
		als_feature.als_sensitivity_min = HID_DEFAULT_MIN_VALUE;
		als_feature.als_sensitivity_max = HID_DEFAULT_MAX_VALUE;
		स_नकल(feature_report, &als_feature, माप(als_feature));
		report_size = माप(als_feature);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस report_size;
पूर्ण

अटल व्योम get_common_inमाला_दो(काष्ठा common_input_property *common, पूर्णांक report_id)
अणु
	common->report_id = report_id;
	common->sensor_state = HID_USAGE_SENSOR_STATE_READY_ENUM;
	common->event_type = HID_USAGE_SENSOR_EVENT_DATA_UPDATED_ENUM;
पूर्ण

u8 get_input_report(पूर्णांक sensor_idx, पूर्णांक report_id, u8 *input_report, u32 *sensor_virt_addr)
अणु
	काष्ठा accel3_input_report acc_input;
	काष्ठा gyro_input_report gyro_input;
	काष्ठा magno_input_report magno_input;
	काष्ठा als_input_report als_input;
	u8 report_size = 0;

	अगर (!sensor_virt_addr || !input_report)
		वापस report_size;

	चयन (sensor_idx) अणु
	हाल accel_idx: /* accel */
		get_common_inमाला_दो(&acc_input.common_property, report_id);
		acc_input.in_accel_x_value = (पूर्णांक)sensor_virt_addr[0] / AMD_SFH_FW_MULTIPLIER;
		acc_input.in_accel_y_value = (पूर्णांक)sensor_virt_addr[1] / AMD_SFH_FW_MULTIPLIER;
		acc_input.in_accel_z_value =  (पूर्णांक)sensor_virt_addr[2] / AMD_SFH_FW_MULTIPLIER;
		स_नकल(input_report, &acc_input, माप(acc_input));
		report_size = माप(acc_input);
		अवरोध;
	हाल gyro_idx: /* gyro */
		get_common_inमाला_दो(&gyro_input.common_property, report_id);
		gyro_input.in_angel_x_value = (पूर्णांक)sensor_virt_addr[0] / AMD_SFH_FW_MULTIPLIER;
		gyro_input.in_angel_y_value = (पूर्णांक)sensor_virt_addr[1] / AMD_SFH_FW_MULTIPLIER;
		gyro_input.in_angel_z_value =  (पूर्णांक)sensor_virt_addr[2] / AMD_SFH_FW_MULTIPLIER;
		स_नकल(input_report, &gyro_input, माप(gyro_input));
		report_size = माप(gyro_input);
		अवरोध;
	हाल mag_idx: /* Magnetometer */
		get_common_inमाला_दो(&magno_input.common_property, report_id);
		magno_input.in_magno_x = (पूर्णांक)sensor_virt_addr[0] / AMD_SFH_FW_MULTIPLIER;
		magno_input.in_magno_y = (पूर्णांक)sensor_virt_addr[1] / AMD_SFH_FW_MULTIPLIER;
		magno_input.in_magno_z = (पूर्णांक)sensor_virt_addr[2] / AMD_SFH_FW_MULTIPLIER;
		magno_input.in_magno_accuracy = (u16)sensor_virt_addr[3] / AMD_SFH_FW_MULTIPLIER;
		स_नकल(input_report, &magno_input, माप(magno_input));
		report_size = माप(magno_input);
		अवरोध;
	हाल als_idx: /* Als */
		get_common_inमाला_दो(&als_input.common_property, report_id);
		als_input.illuminance_value =  (पूर्णांक)sensor_virt_addr[0] / AMD_SFH_FW_MULTIPLIER;
		report_size = माप(als_input);
		स_नकल(input_report, &als_input, माप(als_input));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस report_size;
पूर्ण
