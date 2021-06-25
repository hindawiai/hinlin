<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Generic helper functions क्रम touchscreens and other two-dimensional
 *  poपूर्णांकing devices
 *
 *  Copyright (c) 2014 Sebastian Reichel <sre@kernel.org>
 */

#समावेश <linux/property.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/module.h>

अटल bool touchscreen_get_prop_u32(काष्ठा device *dev,
				     स्थिर अक्षर *property,
				     अचिन्हित पूर्णांक शेष_value,
				     अचिन्हित पूर्णांक *value)
अणु
	u32 val;
	पूर्णांक error;

	error = device_property_पढ़ो_u32(dev, property, &val);
	अगर (error) अणु
		*value = शेष_value;
		वापस false;
	पूर्ण

	*value = val;
	वापस true;
पूर्ण

अटल व्योम touchscreen_set_params(काष्ठा input_dev *dev,
				   अचिन्हित दीर्घ axis,
				   पूर्णांक min, पूर्णांक max, पूर्णांक fuzz)
अणु
	काष्ठा input_असलinfo *असलinfo;

	अगर (!test_bit(axis, dev->असलbit)) अणु
		dev_warn(&dev->dev,
			 "Parameters are specified but the axis %lu is not set up\n",
			 axis);
		वापस;
	पूर्ण

	असलinfo = &dev->असलinfo[axis];
	असलinfo->minimum = min;
	असलinfo->maximum = max;
	असलinfo->fuzz = fuzz;
पूर्ण

/**
 * touchscreen_parse_properties - parse common touchscreen properties
 * @input: input device that should be parsed
 * @multitouch: specअगरies whether parsed properties should be applied to
 *	single-touch or multi-touch axes
 * @prop: poपूर्णांकer to a काष्ठा touchscreen_properties पूर्णांकo which to store
 *	axis swap and invert info क्रम use with touchscreen_report_x_y();
 *	or %शून्य
 *
 * This function parses common properties क्रम touchscreens and sets up the
 * input device accordingly. The function keeps previously set up शेष
 * values अगर no value is specअगरied.
 */
व्योम touchscreen_parse_properties(काष्ठा input_dev *input, bool multitouch,
				  काष्ठा touchscreen_properties *prop)
अणु
	काष्ठा device *dev = input->dev.parent;
	काष्ठा input_असलinfo *असलinfo;
	अचिन्हित पूर्णांक axis, axis_x, axis_y;
	अचिन्हित पूर्णांक minimum, maximum, fuzz;
	bool data_present;

	input_alloc_असलinfo(input);
	अगर (!input->असलinfo)
		वापस;

	axis_x = multitouch ? ABS_MT_POSITION_X : ABS_X;
	axis_y = multitouch ? ABS_MT_POSITION_Y : ABS_Y;

	data_present = touchscreen_get_prop_u32(dev, "touchscreen-min-x",
						input_असल_get_min(input, axis_x),
						&minimum) |
		       touchscreen_get_prop_u32(dev, "touchscreen-size-x",
						input_असल_get_max(input,
								  axis_x) + 1,
						&maximum) |
		       touchscreen_get_prop_u32(dev, "touchscreen-fuzz-x",
						input_असल_get_fuzz(input, axis_x),
						&fuzz);
	अगर (data_present)
		touchscreen_set_params(input, axis_x, minimum, maximum - 1, fuzz);

	data_present = touchscreen_get_prop_u32(dev, "touchscreen-min-y",
						input_असल_get_min(input, axis_y),
						&minimum) |
		       touchscreen_get_prop_u32(dev, "touchscreen-size-y",
						input_असल_get_max(input,
								  axis_y) + 1,
						&maximum) |
		       touchscreen_get_prop_u32(dev, "touchscreen-fuzz-y",
						input_असल_get_fuzz(input, axis_y),
						&fuzz);
	अगर (data_present)
		touchscreen_set_params(input, axis_y, minimum, maximum - 1, fuzz);

	axis = multitouch ? ABS_MT_PRESSURE : ABS_PRESSURE;
	data_present = touchscreen_get_prop_u32(dev,
						"touchscreen-max-pressure",
						input_असल_get_max(input, axis),
						&maximum) |
		       touchscreen_get_prop_u32(dev,
						"touchscreen-fuzz-pressure",
						input_असल_get_fuzz(input, axis),
						&fuzz);
	अगर (data_present)
		touchscreen_set_params(input, axis, 0, maximum, fuzz);

	अगर (!prop)
		वापस;

	prop->max_x = input_असल_get_max(input, axis_x);
	prop->max_y = input_असल_get_max(input, axis_y);

	prop->invert_x =
		device_property_पढ़ो_bool(dev, "touchscreen-inverted-x");
	अगर (prop->invert_x) अणु
		असलinfo = &input->असलinfo[axis_x];
		असलinfo->maximum -= असलinfo->minimum;
		असलinfo->minimum = 0;
	पूर्ण

	prop->invert_y =
		device_property_पढ़ो_bool(dev, "touchscreen-inverted-y");
	अगर (prop->invert_y) अणु
		असलinfo = &input->असलinfo[axis_y];
		असलinfo->maximum -= असलinfo->minimum;
		असलinfo->minimum = 0;
	पूर्ण

	prop->swap_x_y =
		device_property_पढ़ो_bool(dev, "touchscreen-swapped-x-y");
	अगर (prop->swap_x_y)
		swap(input->असलinfo[axis_x], input->असलinfo[axis_y]);
पूर्ण
EXPORT_SYMBOL(touchscreen_parse_properties);

अटल व्योम
touchscreen_apply_prop_to_x_y(स्थिर काष्ठा touchscreen_properties *prop,
			      अचिन्हित पूर्णांक *x, अचिन्हित पूर्णांक *y)
अणु
	अगर (prop->invert_x)
		*x = prop->max_x - *x;

	अगर (prop->invert_y)
		*y = prop->max_y - *y;

	अगर (prop->swap_x_y)
		swap(*x, *y);
पूर्ण

/**
 * touchscreen_set_mt_pos - Set input_mt_pos coordinates
 * @pos: input_mt_pos to set coordinates of
 * @prop: poपूर्णांकer to a काष्ठा touchscreen_properties
 * @x: X coordinate to store in pos
 * @y: Y coordinate to store in pos
 *
 * Adjust the passed in x and y values applying any axis inversion and
 * swapping requested in the passed in touchscreen_properties and store
 * the result in a काष्ठा input_mt_pos.
 */
व्योम touchscreen_set_mt_pos(काष्ठा input_mt_pos *pos,
			    स्थिर काष्ठा touchscreen_properties *prop,
			    अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y)
अणु
	touchscreen_apply_prop_to_x_y(prop, &x, &y);
	pos->x = x;
	pos->y = y;
पूर्ण
EXPORT_SYMBOL(touchscreen_set_mt_pos);

/**
 * touchscreen_report_pos - Report touchscreen coordinates
 * @input: input_device to report coordinates क्रम
 * @prop: poपूर्णांकer to a काष्ठा touchscreen_properties
 * @x: X coordinate to report
 * @y: Y coordinate to report
 * @multitouch: Report coordinates on single-touch or multi-touch axes
 *
 * Adjust the passed in x and y values applying any axis inversion and
 * swapping requested in the passed in touchscreen_properties and then
 * report the resulting coordinates on the input_dev's x and y axis.
 */
व्योम touchscreen_report_pos(काष्ठा input_dev *input,
			    स्थिर काष्ठा touchscreen_properties *prop,
			    अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y,
			    bool multitouch)
अणु
	touchscreen_apply_prop_to_x_y(prop, &x, &y);
	input_report_असल(input, multitouch ? ABS_MT_POSITION_X : ABS_X, x);
	input_report_असल(input, multitouch ? ABS_MT_POSITION_Y : ABS_Y, y);
पूर्ण
EXPORT_SYMBOL(touchscreen_report_pos);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Helper functions for touchscreens and other devices");
