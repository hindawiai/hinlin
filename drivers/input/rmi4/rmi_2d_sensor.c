<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011-2016 Synaptics Incorporated
 * Copyright (c) 2011 Unixphere
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/rmi.h>
#समावेश "rmi_driver.h"
#समावेश "rmi_2d_sensor.h"

#घोषणा RMI_2D_REL_POS_MIN		-128
#घोषणा RMI_2D_REL_POS_MAX		127

/* maximum ABS_MT_POSITION displacement (in mm) */
#घोषणा DMAX 10

व्योम rmi_2d_sensor_असल_process(काष्ठा rmi_2d_sensor *sensor,
				काष्ठा rmi_2d_sensor_असल_object *obj,
				पूर्णांक slot)
अणु
	काष्ठा rmi_2d_axis_alignment *axis_align = &sensor->axis_align;

	/* we keep the previous values अगर the finger is released */
	अगर (obj->type == RMI_2D_OBJECT_NONE)
		वापस;

	अगर (axis_align->flip_x)
		obj->x = sensor->max_x - obj->x;

	अगर (axis_align->flip_y)
		obj->y = sensor->max_y - obj->y;

	अगर (axis_align->swap_axes)
		swap(obj->x, obj->y);

	/*
	 * Here checking अगर X offset or y offset are specअगरied is
	 * redundant. We just add the offsets or clip the values.
	 *
	 * Note: offsets need to be applied beक्रमe clipping occurs,
	 * or we could get funny values that are outside of
	 * clipping boundaries.
	 */
	obj->x += axis_align->offset_x;
	obj->y += axis_align->offset_y;

	obj->x =  max(axis_align->clip_x_low, obj->x);
	obj->y =  max(axis_align->clip_y_low, obj->y);

	अगर (axis_align->clip_x_high)
		obj->x = min(sensor->max_x, obj->x);

	अगर (axis_align->clip_y_high)
		obj->y =  min(sensor->max_y, obj->y);

	sensor->tracking_pos[slot].x = obj->x;
	sensor->tracking_pos[slot].y = obj->y;
पूर्ण
EXPORT_SYMBOL_GPL(rmi_2d_sensor_असल_process);

व्योम rmi_2d_sensor_असल_report(काष्ठा rmi_2d_sensor *sensor,
				काष्ठा rmi_2d_sensor_असल_object *obj,
				पूर्णांक slot)
अणु
	काष्ठा rmi_2d_axis_alignment *axis_align = &sensor->axis_align;
	काष्ठा input_dev *input = sensor->input;
	पूर्णांक wide, major, minor;

	अगर (sensor->kernel_tracking)
		input_mt_slot(input, sensor->tracking_slots[slot]);
	अन्यथा
		input_mt_slot(input, slot);

	input_mt_report_slot_state(input, obj->mt_tool,
				   obj->type != RMI_2D_OBJECT_NONE);

	अगर (obj->type != RMI_2D_OBJECT_NONE) अणु
		obj->x = sensor->tracking_pos[slot].x;
		obj->y = sensor->tracking_pos[slot].y;

		अगर (axis_align->swap_axes)
			swap(obj->wx, obj->wy);

		wide = (obj->wx > obj->wy);
		major = max(obj->wx, obj->wy);
		minor = min(obj->wx, obj->wy);

		अगर (obj->type == RMI_2D_OBJECT_STYLUS) अणु
			major = max(1, major);
			minor = max(1, minor);
		पूर्ण

		input_event(sensor->input, EV_ABS, ABS_MT_POSITION_X, obj->x);
		input_event(sensor->input, EV_ABS, ABS_MT_POSITION_Y, obj->y);
		input_event(sensor->input, EV_ABS, ABS_MT_ORIENTATION, wide);
		input_event(sensor->input, EV_ABS, ABS_MT_PRESSURE, obj->z);
		input_event(sensor->input, EV_ABS, ABS_MT_TOUCH_MAJOR, major);
		input_event(sensor->input, EV_ABS, ABS_MT_TOUCH_MINOR, minor);

		rmi_dbg(RMI_DEBUG_2D_SENSOR, &sensor->input->dev,
			"%s: obj[%d]: type: 0x%02x X: %d Y: %d Z: %d WX: %d WY: %d\n",
			__func__, slot, obj->type, obj->x, obj->y, obj->z,
			obj->wx, obj->wy);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rmi_2d_sensor_असल_report);

व्योम rmi_2d_sensor_rel_report(काष्ठा rmi_2d_sensor *sensor, पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा rmi_2d_axis_alignment *axis_align = &sensor->axis_align;

	x = min(RMI_2D_REL_POS_MAX, max(RMI_2D_REL_POS_MIN, (पूर्णांक)x));
	y = min(RMI_2D_REL_POS_MAX, max(RMI_2D_REL_POS_MIN, (पूर्णांक)y));

	अगर (axis_align->flip_x)
		x = min(RMI_2D_REL_POS_MAX, -x);

	अगर (axis_align->flip_y)
		y = min(RMI_2D_REL_POS_MAX, -y);

	अगर (axis_align->swap_axes)
		swap(x, y);

	अगर (x || y) अणु
		input_report_rel(sensor->input, REL_X, x);
		input_report_rel(sensor->input, REL_Y, y);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rmi_2d_sensor_rel_report);

अटल व्योम rmi_2d_sensor_set_input_params(काष्ठा rmi_2d_sensor *sensor)
अणु
	काष्ठा input_dev *input = sensor->input;
	पूर्णांक res_x;
	पूर्णांक res_y;
	पूर्णांक max_x, max_y;
	पूर्णांक input_flags = 0;

	अगर (sensor->report_असल) अणु
		sensor->min_x = sensor->axis_align.clip_x_low;
		अगर (sensor->axis_align.clip_x_high)
			sensor->max_x = min(sensor->max_x,
				sensor->axis_align.clip_x_high);

		sensor->min_y = sensor->axis_align.clip_y_low;
		अगर (sensor->axis_align.clip_y_high)
			sensor->max_y = min(sensor->max_y,
				sensor->axis_align.clip_y_high);

		set_bit(EV_ABS, input->evbit);

		max_x = sensor->max_x;
		max_y = sensor->max_y;
		अगर (sensor->axis_align.swap_axes)
			swap(max_x, max_y);
		input_set_असल_params(input, ABS_MT_POSITION_X, 0, max_x, 0, 0);
		input_set_असल_params(input, ABS_MT_POSITION_Y, 0, max_y, 0, 0);

		अगर (sensor->x_mm && sensor->y_mm) अणु
			res_x = (sensor->max_x - sensor->min_x) / sensor->x_mm;
			res_y = (sensor->max_y - sensor->min_y) / sensor->y_mm;
			अगर (sensor->axis_align.swap_axes)
				swap(res_x, res_y);

			input_असल_set_res(input, ABS_X, res_x);
			input_असल_set_res(input, ABS_Y, res_y);

			input_असल_set_res(input, ABS_MT_POSITION_X, res_x);
			input_असल_set_res(input, ABS_MT_POSITION_Y, res_y);

			अगर (!sensor->dmax)
				sensor->dmax = DMAX * res_x;
		पूर्ण

		input_set_असल_params(input, ABS_MT_PRESSURE, 0, 0xff, 0, 0);
		input_set_असल_params(input, ABS_MT_TOUCH_MAJOR, 0, 0x0f, 0, 0);
		input_set_असल_params(input, ABS_MT_TOUCH_MINOR, 0, 0x0f, 0, 0);
		input_set_असल_params(input, ABS_MT_ORIENTATION, 0, 1, 0, 0);
		input_set_असल_params(input, ABS_MT_TOOL_TYPE,
				     0, MT_TOOL_MAX, 0, 0);

		अगर (sensor->sensor_type == rmi_sensor_touchpad)
			input_flags = INPUT_MT_POINTER;
		अन्यथा
			input_flags = INPUT_MT_सूचीECT;

		अगर (sensor->kernel_tracking)
			input_flags |= INPUT_MT_TRACK;

		input_mt_init_slots(input, sensor->nbr_fingers, input_flags);
	पूर्ण

	अगर (sensor->report_rel) अणु
		set_bit(EV_REL, input->evbit);
		set_bit(REL_X, input->relbit);
		set_bit(REL_Y, input->relbit);
	पूर्ण

	अगर (sensor->topbuttonpad)
		set_bit(INPUT_PROP_TOPBUTTONPAD, input->propbit);
पूर्ण

पूर्णांक rmi_2d_sensor_configure_input(काष्ठा rmi_function *fn,
					काष्ठा rmi_2d_sensor *sensor)
अणु
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	काष्ठा rmi_driver_data *drv_data = dev_get_drvdata(&rmi_dev->dev);

	अगर (!drv_data->input)
		वापस -ENODEV;

	sensor->input = drv_data->input;
	rmi_2d_sensor_set_input_params(sensor);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rmi_2d_sensor_configure_input);

#अगर_घोषित CONFIG_OF
पूर्णांक rmi_2d_sensor_of_probe(काष्ठा device *dev,
			काष्ठा rmi_2d_sensor_platक्रमm_data *pdata)
अणु
	पूर्णांक retval;
	u32 val;

	pdata->axis_align.swap_axes = of_property_पढ़ो_bool(dev->of_node,
						"touchscreen-swapped-x-y");

	pdata->axis_align.flip_x = of_property_पढ़ो_bool(dev->of_node,
						"touchscreen-inverted-x");

	pdata->axis_align.flip_y = of_property_पढ़ो_bool(dev->of_node,
						"touchscreen-inverted-y");

	retval = rmi_of_property_पढ़ो_u32(dev, &val, "syna,clip-x-low", 1);
	अगर (retval)
		वापस retval;

	pdata->axis_align.clip_x_low = val;

	retval = rmi_of_property_पढ़ो_u32(dev, &val, "syna,clip-y-low",	1);
	अगर (retval)
		वापस retval;

	pdata->axis_align.clip_y_low = val;

	retval = rmi_of_property_पढ़ो_u32(dev, &val, "syna,clip-x-high", 1);
	अगर (retval)
		वापस retval;

	pdata->axis_align.clip_x_high = val;

	retval = rmi_of_property_पढ़ो_u32(dev, &val, "syna,clip-y-high", 1);
	अगर (retval)
		वापस retval;

	pdata->axis_align.clip_y_high = val;

	retval = rmi_of_property_पढ़ो_u32(dev, &val, "syna,offset-x", 1);
	अगर (retval)
		वापस retval;

	pdata->axis_align.offset_x = val;

	retval = rmi_of_property_पढ़ो_u32(dev, &val, "syna,offset-y", 1);
	अगर (retval)
		वापस retval;

	pdata->axis_align.offset_y = val;

	retval = rmi_of_property_पढ़ो_u32(dev, &val, "syna,delta-x-threshold",
						1);
	अगर (retval)
		वापस retval;

	pdata->axis_align.delta_x_threshold = val;

	retval = rmi_of_property_पढ़ो_u32(dev, &val, "syna,delta-y-threshold",
						1);
	अगर (retval)
		वापस retval;

	pdata->axis_align.delta_y_threshold = val;

	retval = rmi_of_property_पढ़ो_u32(dev, (u32 *)&pdata->sensor_type,
			"syna,sensor-type", 1);
	अगर (retval)
		वापस retval;

	retval = rmi_of_property_पढ़ो_u32(dev, &val, "touchscreen-x-mm", 1);
	अगर (retval)
		वापस retval;

	pdata->x_mm = val;

	retval = rmi_of_property_पढ़ो_u32(dev, &val, "touchscreen-y-mm", 1);
	अगर (retval)
		वापस retval;

	pdata->y_mm = val;

	retval = rmi_of_property_पढ़ो_u32(dev, &val,
				"syna,disable-report-mask", 1);
	अगर (retval)
		वापस retval;

	pdata->disable_report_mask = val;

	retval = rmi_of_property_पढ़ो_u32(dev, &val, "syna,rezero-wait-ms",
						1);
	अगर (retval)
		वापस retval;

	pdata->rezero_रुको = val;

	वापस 0;
पूर्ण
#अन्यथा
अंतरभूत पूर्णांक rmi_2d_sensor_of_probe(काष्ठा device *dev,
			काष्ठा rmi_2d_sensor_platक्रमm_data *pdata)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर
EXPORT_SYMBOL_GPL(rmi_2d_sensor_of_probe);
