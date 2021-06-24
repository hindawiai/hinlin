<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * HID report descriptors, काष्ठाures and routines
 * Copyright 2020 Advanced Micro Devices, Inc.
 * Authors: Nehal Bakulchandra Shah <Nehal-bakulchandra.shah@amd.com>
 *	    Sandeep Singh <Sandeep.singh@amd.com>
 */

#अगर_अघोषित AMD_SFH_HID_DESCRIPTOR_H
#घोषणा AMD_SFH_HID_DESCRIPTOR_H

क्रमागत desc_type अणु
	/* Report descriptor name */
	descr_size = 1,
	input_size,
	feature_size,
पूर्ण;

काष्ठा common_feature_property अणु
	/* common properties */
	u8 report_id;
	u8 connection_type;
	u8 report_state;
	u8 घातer_state;
	u8 sensor_state;
	u32 report_पूर्णांकerval;
पूर्ण __packed;

काष्ठा common_input_property अणु
	/* common properties */
	u8 report_id;
	u8 sensor_state;
	u8 event_type;
पूर्ण __packed;

काष्ठा accel3_feature_report अणु
	काष्ठा common_feature_property common_property;
	/* properties specअगरic to this sensor */
	u16 accel_change_sesnitivity;
	s16 accel_sensitivity_max;
	s16 accel_sensitivity_min;
पूर्ण __packed;

काष्ठा accel3_input_report अणु
	काष्ठा	common_input_property common_property;
	/* values specअगरic to this sensor */
	पूर्णांक in_accel_x_value;
	पूर्णांक in_accel_y_value;
	पूर्णांक in_accel_z_value;
	/* include अगर required to support the "shake" event */
	u8 in_accel_shake_detection;
पूर्ण __packed;

काष्ठा gyro_feature_report अणु
	काष्ठा common_feature_property common_property;
	/* properties specअगरic to this sensor */
	u16 gyro_change_sesnitivity;
	s16 gyro_sensitivity_max;
	s16 gyro_sensitivity_min;
पूर्ण __packed;

काष्ठा gyro_input_report अणु
	काष्ठा	common_input_property common_property;
	/* values specअगरic to this sensor */
	पूर्णांक in_angel_x_value;
	पूर्णांक in_angel_y_value;
	पूर्णांक in_angel_z_value;
पूर्ण __packed;

काष्ठा magno_feature_report अणु
	काष्ठा common_feature_property common_property;
	/*properties specअगरic to this sensor */
	u16 magno_headingchange_sensitivity;
	s16 heading_min;
	s16 heading_max;
	u16 flux_change_sensitivity;
	s16 flux_min;
	s16 flux_max;
पूर्ण __packed;

काष्ठा magno_input_report अणु
	काष्ठा	common_input_property common_property;
	पूर्णांक in_magno_x;
	पूर्णांक in_magno_y;
	पूर्णांक in_magno_z;
	पूर्णांक in_magno_accuracy;
पूर्ण __packed;

काष्ठा als_feature_report अणु
	काष्ठा common_feature_property common_property;
	/* properties specअगरic to this sensor */
	u16 als_change_sesnitivity;
	s16 als_sensitivity_max;
	s16 als_sensitivity_min;
पूर्ण __packed;

काष्ठा als_input_report अणु
	काष्ठा common_input_property common_property;
	/* values specअगरic to this sensor */
	पूर्णांक illuminance_value;
पूर्ण __packed;

पूर्णांक get_report_descriptor(पूर्णांक sensor_idx, u8 rep_desc[]);
u32 get_descr_sz(पूर्णांक sensor_idx, पूर्णांक descriptor_name);
u8 get_feature_report(पूर्णांक sensor_idx, पूर्णांक report_id, u8 *feature_report);
u8 get_input_report(पूर्णांक sensor_idx, पूर्णांक report_id, u8 *input_report, u32 *sensor_virt_addr);
#पूर्ण_अगर
