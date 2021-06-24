<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2011-2016 Synaptics Incorporated
 * Copyright (c) 2011 Unixphere
 */

#अगर_अघोषित _RMI_2D_SENSOR_H
#घोषणा _RMI_2D_SENSOR_H

क्रमागत rmi_2d_sensor_object_type अणु
	RMI_2D_OBJECT_NONE,
	RMI_2D_OBJECT_FINGER,
	RMI_2D_OBJECT_STYLUS,
	RMI_2D_OBJECT_PALM,
	RMI_2D_OBJECT_UNCLASSIFIED,
पूर्ण;

काष्ठा rmi_2d_sensor_असल_object अणु
	क्रमागत rmi_2d_sensor_object_type type;
	पूर्णांक mt_tool;
	u16 x;
	u16 y;
	u8 z;
	u8 wx;
	u8 wy;
पूर्ण;

/**
 * @axis_align - controls parameters that are useful in प्रणाली prototyping
 * and bring up.
 * @max_x - The maximum X coordinate that will be reported by this sensor.
 * @max_y - The maximum Y coordinate that will be reported by this sensor.
 * @nbr_fingers - How many fingers can this sensor report?
 * @data_pkt - buffer क्रम data reported by this sensor.
 * @pkt_size - number of bytes in that buffer.
 * @attn_size - Size of the HID attention report (only contains असल data).
 * position when two fingers are on the device.  When this is true, we
 * assume we have one of those sensors and report events appropriately.
 * @sensor_type - indicates whether we're touchscreen or touchpad.
 * @input - input device क्रम असलolute poपूर्णांकing stream
 * @input_phys - buffer क्रम the असलolute phys name क्रम this sensor.
 */
काष्ठा rmi_2d_sensor अणु
	काष्ठा rmi_2d_axis_alignment axis_align;
	काष्ठा input_mt_pos *tracking_pos;
	पूर्णांक *tracking_slots;
	bool kernel_tracking;
	काष्ठा rmi_2d_sensor_असल_object *objs;
	पूर्णांक dmax;
	u16 min_x;
	u16 max_x;
	u16 min_y;
	u16 max_y;
	u8 nbr_fingers;
	u8 *data_pkt;
	पूर्णांक pkt_size;
	पूर्णांक attn_size;
	bool topbuttonpad;
	क्रमागत rmi_sensor_type sensor_type;
	काष्ठा input_dev *input;
	काष्ठा rmi_function *fn;
	अक्षर input_phys[32];
	u8 report_असल;
	u8 report_rel;
	u8 x_mm;
	u8 y_mm;
	क्रमागत rmi_reg_state dribble;
	क्रमागत rmi_reg_state palm_detect;
पूर्ण;

पूर्णांक rmi_2d_sensor_of_probe(काष्ठा device *dev,
				काष्ठा rmi_2d_sensor_platक्रमm_data *pdata);

व्योम rmi_2d_sensor_असल_process(काष्ठा rmi_2d_sensor *sensor,
				काष्ठा rmi_2d_sensor_असल_object *obj,
				पूर्णांक slot);

व्योम rmi_2d_sensor_असल_report(काष्ठा rmi_2d_sensor *sensor,
				काष्ठा rmi_2d_sensor_असल_object *obj,
				पूर्णांक slot);

व्योम rmi_2d_sensor_rel_report(काष्ठा rmi_2d_sensor *sensor, पूर्णांक x, पूर्णांक y);

पूर्णांक rmi_2d_sensor_configure_input(काष्ठा rmi_function *fn,
					काष्ठा rmi_2d_sensor *sensor);
#पूर्ण_अगर /* _RMI_2D_SENSOR_H */
