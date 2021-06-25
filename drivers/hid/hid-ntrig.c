<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम N-Trig touchscreens
 *
 *  Copyright (c) 2008-2010 Rafi Rubin
 *  Copyright (c) 2009-2010 Stephane Chatty
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/usb.h>
#समावेश "usbhid/usbhid.h"
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "hid-ids.h"

#घोषणा NTRIG_DUPLICATE_USAGES	0x001

अटल अचिन्हित पूर्णांक min_width;
module_param(min_width, uपूर्णांक, 0644);
MODULE_PARM_DESC(min_width, "Minimum touch contact width to accept.");

अटल अचिन्हित पूर्णांक min_height;
module_param(min_height, uपूर्णांक, 0644);
MODULE_PARM_DESC(min_height, "Minimum touch contact height to accept.");

अटल अचिन्हित पूर्णांक activate_slack = 1;
module_param(activate_slack, uपूर्णांक, 0644);
MODULE_PARM_DESC(activate_slack, "Number of touch frames to ignore at "
		 "the start of touch input.");

अटल अचिन्हित पूर्णांक deactivate_slack = 4;
module_param(deactivate_slack, uपूर्णांक, 0644);
MODULE_PARM_DESC(deactivate_slack, "Number of empty frames to ignore before "
		 "deactivating touch.");

अटल अचिन्हित पूर्णांक activation_width = 64;
module_param(activation_width, uपूर्णांक, 0644);
MODULE_PARM_DESC(activation_width, "Width threshold to immediately start "
		 "processing touch events.");

अटल अचिन्हित पूर्णांक activation_height = 32;
module_param(activation_height, uपूर्णांक, 0644);
MODULE_PARM_DESC(activation_height, "Height threshold to immediately start "
		 "processing touch events.");

काष्ठा ntrig_data अणु
	/* Incoming raw values क्रम a single contact */
	__u16 x, y, w, h;
	__u16 id;

	bool tipचयन;
	bool confidence;
	bool first_contact_touch;

	bool पढ़ोing_mt;

	__u8 mt_footer[4];
	__u8 mt_foot_count;

	/* The current activation state. */
	__s8 act_state;

	/* Empty frames to ignore beक्रमe recognizing the end of activity */
	__s8 deactivate_slack;

	/* Frames to ignore beक्रमe acknowledging the start of activity */
	__s8 activate_slack;

	/* Minimum size contact to accept */
	__u16 min_width;
	__u16 min_height;

	/* Threshold to override activation slack */
	__u16 activation_width;
	__u16 activation_height;

	__u16 sensor_logical_width;
	__u16 sensor_logical_height;
	__u16 sensor_physical_width;
	__u16 sensor_physical_height;
पूर्ण;


/*
 * This function converts the 4 byte raw firmware code पूर्णांकo
 * a string containing 5 comma separated numbers.
 */
अटल पूर्णांक ntrig_version_string(अचिन्हित अक्षर *raw, अक्षर *buf)
अणु
	__u8 a =  (raw[1] & 0x0e) >> 1;
	__u8 b =  (raw[0] & 0x3c) >> 2;
	__u8 c = ((raw[0] & 0x03) << 3) | ((raw[3] & 0xe0) >> 5);
	__u8 d = ((raw[3] & 0x07) << 3) | ((raw[2] & 0xe0) >> 5);
	__u8 e =   raw[2] & 0x07;

	/*
	 * As yet unmapped bits:
	 * 0b11000000 0b11110001 0b00011000 0b00011000
	 */

	वापस प्र_लिखो(buf, "%u.%u.%u.%u.%u", a, b, c, d, e);
पूर्ण

अटल अंतरभूत पूर्णांक ntrig_get_mode(काष्ठा hid_device *hdev)
अणु
	काष्ठा hid_report *report = hdev->report_क्रमागत[HID_FEATURE_REPORT].
				    report_id_hash[0x0d];

	अगर (!report || report->maxfield < 1 ||
	    report->field[0]->report_count < 1)
		वापस -EINVAL;

	hid_hw_request(hdev, report, HID_REQ_GET_REPORT);
	hid_hw_रुको(hdev);
	वापस (पूर्णांक)report->field[0]->value[0];
पूर्ण

अटल अंतरभूत व्योम ntrig_set_mode(काष्ठा hid_device *hdev, स्थिर पूर्णांक mode)
अणु
	काष्ठा hid_report *report;
	__u8 mode_commands[4] = अणु 0xe, 0xf, 0x1b, 0x10 पूर्ण;

	अगर (mode < 0 || mode > 3)
		वापस;

	report = hdev->report_क्रमागत[HID_FEATURE_REPORT].
		 report_id_hash[mode_commands[mode]];

	अगर (!report)
		वापस;

	hid_hw_request(hdev, report, HID_REQ_GET_REPORT);
पूर्ण

अटल व्योम ntrig_report_version(काष्ठा hid_device *hdev)
अणु
	पूर्णांक ret;
	अक्षर buf[20];
	काष्ठा usb_device *usb_dev = hid_to_usb_dev(hdev);
	अचिन्हित अक्षर *data = kदो_स्मृति(8, GFP_KERNEL);

	अगर (!data)
		जाओ err_मुक्त;

	ret = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			      USB_REQ_CLEAR_FEATURE,
			      USB_TYPE_CLASS | USB_RECIP_INTERFACE |
			      USB_सूची_IN,
			      0x30c, 1, data, 8,
			      USB_CTRL_SET_TIMEOUT);

	अगर (ret == 8) अणु
		ret = ntrig_version_string(&data[2], buf);

		hid_info(hdev, "Firmware version: %s (%02x%02x %02x%02x)\n",
			 buf, data[2], data[3], data[4], data[5]);
	पूर्ण

err_मुक्त:
	kमुक्त(data);
पूर्ण

अटल sमाप_प्रकार show_phys_width(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	वापस प्र_लिखो(buf, "%d\n", nd->sensor_physical_width);
पूर्ण

अटल DEVICE_ATTR(sensor_physical_width, S_IRUGO, show_phys_width, शून्य);

अटल sमाप_प्रकार show_phys_height(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	वापस प्र_लिखो(buf, "%d\n", nd->sensor_physical_height);
पूर्ण

अटल DEVICE_ATTR(sensor_physical_height, S_IRUGO, show_phys_height, शून्य);

अटल sमाप_प्रकार show_log_width(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	वापस प्र_लिखो(buf, "%d\n", nd->sensor_logical_width);
पूर्ण

अटल DEVICE_ATTR(sensor_logical_width, S_IRUGO, show_log_width, शून्य);

अटल sमाप_प्रकार show_log_height(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	वापस प्र_लिखो(buf, "%d\n", nd->sensor_logical_height);
पूर्ण

अटल DEVICE_ATTR(sensor_logical_height, S_IRUGO, show_log_height, शून्य);

अटल sमाप_प्रकार show_min_width(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	वापस प्र_लिखो(buf, "%d\n", nd->min_width *
				    nd->sensor_physical_width /
				    nd->sensor_logical_width);
पूर्ण

अटल sमाप_प्रकार set_min_width(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > nd->sensor_physical_width)
		वापस -EINVAL;

	nd->min_width = val * nd->sensor_logical_width /
			      nd->sensor_physical_width;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(min_width, S_IWUSR | S_IRUGO, show_min_width, set_min_width);

अटल sमाप_प्रकार show_min_height(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	वापस प्र_लिखो(buf, "%d\n", nd->min_height *
				    nd->sensor_physical_height /
				    nd->sensor_logical_height);
पूर्ण

अटल sमाप_प्रकार set_min_height(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > nd->sensor_physical_height)
		वापस -EINVAL;

	nd->min_height = val * nd->sensor_logical_height /
			       nd->sensor_physical_height;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(min_height, S_IWUSR | S_IRUGO, show_min_height,
		   set_min_height);

अटल sमाप_प्रकार show_activate_slack(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	वापस प्र_लिखो(buf, "%d\n", nd->activate_slack);
पूर्ण

अटल sमाप_प्रकार set_activate_slack(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > 0x7f)
		वापस -EINVAL;

	nd->activate_slack = val;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(activate_slack, S_IWUSR | S_IRUGO, show_activate_slack,
		   set_activate_slack);

अटल sमाप_प्रकार show_activation_width(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	वापस प्र_लिखो(buf, "%d\n", nd->activation_width *
				    nd->sensor_physical_width /
				    nd->sensor_logical_width);
पूर्ण

अटल sमाप_प्रकार set_activation_width(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > nd->sensor_physical_width)
		वापस -EINVAL;

	nd->activation_width = val * nd->sensor_logical_width /
				     nd->sensor_physical_width;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(activation_width, S_IWUSR | S_IRUGO, show_activation_width,
		   set_activation_width);

अटल sमाप_प्रकार show_activation_height(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	वापस प्र_लिखो(buf, "%d\n", nd->activation_height *
				    nd->sensor_physical_height /
				    nd->sensor_logical_height);
पूर्ण

अटल sमाप_प्रकार set_activation_height(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > nd->sensor_physical_height)
		वापस -EINVAL;

	nd->activation_height = val * nd->sensor_logical_height /
				      nd->sensor_physical_height;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(activation_height, S_IWUSR | S_IRUGO,
		   show_activation_height, set_activation_height);

अटल sमाप_प्रकार show_deactivate_slack(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	वापस प्र_लिखो(buf, "%d\n", -nd->deactivate_slack);
पूर्ण

अटल sमाप_प्रकार set_deactivate_slack(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	/*
	 * No more than 8 terminal frames have been observed so far
	 * and higher slack is highly likely to leave the single
	 * touch emulation stuck करोwn.
	 */
	अगर (val > 7)
		वापस -EINVAL;

	nd->deactivate_slack = -val;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(deactivate_slack, S_IWUSR | S_IRUGO, show_deactivate_slack,
		   set_deactivate_slack);

अटल काष्ठा attribute *sysfs_attrs[] = अणु
	&dev_attr_sensor_physical_width.attr,
	&dev_attr_sensor_physical_height.attr,
	&dev_attr_sensor_logical_width.attr,
	&dev_attr_sensor_logical_height.attr,
	&dev_attr_min_height.attr,
	&dev_attr_min_width.attr,
	&dev_attr_activate_slack.attr,
	&dev_attr_activation_width.attr,
	&dev_attr_activation_height.attr,
	&dev_attr_deactivate_slack.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ntrig_attribute_group = अणु
	.attrs = sysfs_attrs
पूर्ण;

/*
 * this driver is aimed at two firmware versions in circulation:
 *  - dual pen/finger single touch
 *  - finger multitouch, pen not working
 */

अटल पूर्णांक ntrig_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
			       काष्ठा hid_field *field, काष्ठा hid_usage *usage,
			       अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा ntrig_data *nd = hid_get_drvdata(hdev);

	/* No special mappings needed क्रम the pen and single touch */
	अगर (field->physical)
		वापस 0;

	चयन (usage->hid & HID_USAGE_PAGE) अणु
	हाल HID_UP_GENDESK:
		चयन (usage->hid) अणु
		हाल HID_GD_X:
			hid_map_usage(hi, usage, bit, max,
					EV_ABS, ABS_MT_POSITION_X);
			input_set_असल_params(hi->input, ABS_X,
					field->logical_minimum,
					field->logical_maximum, 0, 0);

			अगर (!nd->sensor_logical_width) अणु
				nd->sensor_logical_width =
					field->logical_maximum -
					field->logical_minimum;
				nd->sensor_physical_width =
					field->physical_maximum -
					field->physical_minimum;
				nd->activation_width = activation_width *
					nd->sensor_logical_width /
					nd->sensor_physical_width;
				nd->min_width = min_width *
					nd->sensor_logical_width /
					nd->sensor_physical_width;
			पूर्ण
			वापस 1;
		हाल HID_GD_Y:
			hid_map_usage(hi, usage, bit, max,
					EV_ABS, ABS_MT_POSITION_Y);
			input_set_असल_params(hi->input, ABS_Y,
					field->logical_minimum,
					field->logical_maximum, 0, 0);

			अगर (!nd->sensor_logical_height) अणु
				nd->sensor_logical_height =
					field->logical_maximum -
					field->logical_minimum;
				nd->sensor_physical_height =
					field->physical_maximum -
					field->physical_minimum;
				nd->activation_height = activation_height *
					nd->sensor_logical_height /
					nd->sensor_physical_height;
				nd->min_height = min_height *
					nd->sensor_logical_height /
					nd->sensor_physical_height;
			पूर्ण
			वापस 1;
		पूर्ण
		वापस 0;

	हाल HID_UP_DIGITIZER:
		चयन (usage->hid) अणु
		/* we करो not want to map these क्रम now */
		हाल HID_DG_CONTACTID: /* Not trustworthy, squelch क्रम now */
		हाल HID_DG_INPUTMODE:
		हाल HID_DG_DEVICEINDEX:
		हाल HID_DG_CONTACTMAX:
			वापस -1;

		/* width/height mapped on TouchMajor/TouchMinor/Orientation */
		हाल HID_DG_WIDTH:
			hid_map_usage(hi, usage, bit, max,
				      EV_ABS, ABS_MT_TOUCH_MAJOR);
			वापस 1;
		हाल HID_DG_HEIGHT:
			hid_map_usage(hi, usage, bit, max,
				      EV_ABS, ABS_MT_TOUCH_MINOR);
			input_set_असल_params(hi->input, ABS_MT_ORIENTATION,
					     0, 1, 0, 0);
			वापस 1;
		पूर्ण
		वापस 0;

	हाल 0xff000000:
		/* we करो not want to map these: no input-oriented meaning */
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ntrig_input_mapped(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
			      काष्ठा hid_field *field, काष्ठा hid_usage *usage,
			      अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	/* No special mappings needed क्रम the pen and single touch */
	अगर (field->physical)
		वापस 0;

	अगर (usage->type == EV_KEY || usage->type == EV_REL
			|| usage->type == EV_ABS)
		clear_bit(usage->code, *bit);

	वापस 0;
पूर्ण

/*
 * this function is called upon all reports
 * so that we can filter contact poपूर्णांक inक्रमmation,
 * decide whether we are in multi or single touch mode
 * and call input_mt_sync after each poपूर्णांक अगर necessary
 */
अटल पूर्णांक ntrig_event (काष्ठा hid_device *hid, काष्ठा hid_field *field,
			काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा ntrig_data *nd = hid_get_drvdata(hid);
	काष्ठा input_dev *input;

	/* Skip processing अगर not a claimed input */
	अगर (!(hid->claimed & HID_CLAIMED_INPUT))
		जाओ not_claimed_input;

	/* This function is being called beक्रमe the काष्ठाures are fully
	 * initialized */
	अगर(!(field->hidinput && field->hidinput->input))
		वापस -EINVAL;

	input = field->hidinput->input;

	/* No special handling needed क्रम the pen */
	अगर (field->application == HID_DG_PEN)
		वापस 0;

	चयन (usage->hid) अणु
	हाल 0xff000001:
		/* Tag indicating the start of a multitouch group */
		nd->पढ़ोing_mt = true;
		nd->first_contact_touch = false;
		अवरोध;
	हाल HID_DG_TIPSWITCH:
		nd->tipचयन = value;
		/* Prevent emission of touch until validated */
		वापस 1;
	हाल HID_DG_CONFIDENCE:
		nd->confidence = value;
		अवरोध;
	हाल HID_GD_X:
		nd->x = value;
		/* Clear the contact footer */
		nd->mt_foot_count = 0;
		अवरोध;
	हाल HID_GD_Y:
		nd->y = value;
		अवरोध;
	हाल HID_DG_CONTACTID:
		nd->id = value;
		अवरोध;
	हाल HID_DG_WIDTH:
		nd->w = value;
		अवरोध;
	हाल HID_DG_HEIGHT:
		nd->h = value;
		/*
		 * when in single touch mode, this is the last
		 * report received in a finger event. We want
		 * to emit a normal (X, Y) position
		 */
		अगर (!nd->पढ़ोing_mt) अणु
			/*
			 * TipSwitch indicates the presence of a
			 * finger in single touch mode.
			 */
			input_report_key(input, BTN_TOUCH,
					 nd->tipचयन);
			input_report_key(input, BTN_TOOL_DOUBLETAP,
					 nd->tipचयन);
			input_event(input, EV_ABS, ABS_X, nd->x);
			input_event(input, EV_ABS, ABS_Y, nd->y);
		पूर्ण
		अवरोध;
	हाल 0xff000002:
		/*
		 * we receive this when the device is in multitouch
		 * mode. The first of the three values tagged with
		 * this usage tells अगर the contact poपूर्णांक is real
		 * or a placeholder
		 */

		/* Shouldn't get more than 4 footer packets, so skip */
		अगर (nd->mt_foot_count >= 4)
			अवरोध;

		nd->mt_footer[nd->mt_foot_count++] = value;

		/* अगर the footer isn't complete अवरोध */
		अगर (nd->mt_foot_count != 4)
			अवरोध;

		/* Pen activity संकेत. */
		अगर (nd->mt_footer[2]) अणु
			/*
			 * When the pen deactivates touch, we see a
			 * bogus frame with ContactCount > 0.
			 * We can
			 * save a bit of work by ensuring act_state < 0
			 * even अगर deactivation slack is turned off.
			 */
			nd->act_state = deactivate_slack - 1;
			nd->confidence = false;
			अवरोध;
		पूर्ण

		/*
		 * The first footer value indicates the presence of a
		 * finger.
		 */
		अगर (nd->mt_footer[0]) अणु
			/*
			 * We करो not want to process contacts under
			 * the size threshold, but करो not want to
			 * ignore them क्रम activation state
			 */
			अगर (nd->w < nd->min_width ||
			    nd->h < nd->min_height)
				nd->confidence = false;
		पूर्ण अन्यथा
			अवरोध;

		अगर (nd->act_state > 0) अणु
			/*
			 * Contact meets the activation size threshold
			 */
			अगर (nd->w >= nd->activation_width &&
			    nd->h >= nd->activation_height) अणु
				अगर (nd->id)
					/*
					 * first contact, activate now
					 */
					nd->act_state = 0;
				अन्यथा अणु
					/*
					 * aव्योम corrupting this frame
					 * but ensure next frame will
					 * be active
					 */
					nd->act_state = 1;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा
				/*
				 * Defer adjusting the activation state
				 * until the end of the frame.
				 */
				अवरोध;
		पूर्ण

		/* Discarding this contact */
		अगर (!nd->confidence)
			अवरोध;

		/* emit a normal (X, Y) क्रम the first poपूर्णांक only */
		अगर (nd->id == 0) अणु
			/*
			 * TipSwitch is superfluous in multitouch
			 * mode.  The footer events tell us
			 * अगर there is a finger on the screen or
			 * not.
			 */
			nd->first_contact_touch = nd->confidence;
			input_event(input, EV_ABS, ABS_X, nd->x);
			input_event(input, EV_ABS, ABS_Y, nd->y);
		पूर्ण

		/* Emit MT events */
		input_event(input, EV_ABS, ABS_MT_POSITION_X, nd->x);
		input_event(input, EV_ABS, ABS_MT_POSITION_Y, nd->y);

		/*
		 * Translate from height and width to size
		 * and orientation.
		 */
		अगर (nd->w > nd->h) अणु
			input_event(input, EV_ABS,
					ABS_MT_ORIENTATION, 1);
			input_event(input, EV_ABS,
					ABS_MT_TOUCH_MAJOR, nd->w);
			input_event(input, EV_ABS,
					ABS_MT_TOUCH_MINOR, nd->h);
		पूर्ण अन्यथा अणु
			input_event(input, EV_ABS,
					ABS_MT_ORIENTATION, 0);
			input_event(input, EV_ABS,
					ABS_MT_TOUCH_MAJOR, nd->h);
			input_event(input, EV_ABS,
					ABS_MT_TOUCH_MINOR, nd->w);
		पूर्ण
		input_mt_sync(field->hidinput->input);
		अवरोध;

	हाल HID_DG_CONTACTCOUNT: /* End of a multitouch group */
		अगर (!nd->पढ़ोing_mt) /* Just to be sure */
			अवरोध;

		nd->पढ़ोing_mt = false;


		/*
		 * Activation state machine logic:
		 *
		 * Fundamental states:
		 *	state >  0: Inactive
		 *	state <= 0: Active
		 *	state <  -deactivate_slack:
		 *		 Pen termination of touch
		 *
		 * Specअगरic values of पूर्णांकerest
		 *	state == activate_slack
		 *		 no valid input since the last reset
		 *
		 *	state == 0
		 *		 general operational state
		 *
		 *	state == -deactivate_slack
		 *		 पढ़ो sufficient empty frames to accept
		 *		 the end of input and reset
		 */

		अगर (nd->act_state > 0) अणु /* Currently inactive */
			अगर (value)
				/*
				 * Consider each live contact as
				 * evidence of पूर्णांकentional activity.
				 */
				nd->act_state = (nd->act_state > value)
						? nd->act_state - value
						: 0;
			अन्यथा
				/*
				 * Empty frame beक्रमe we hit the
				 * activity threshold, reset.
				 */
				nd->act_state = nd->activate_slack;

			/*
			 * Entered this block inactive and no
			 * coordinates sent this frame, so hold off
			 * on button state.
			 */
			अवरोध;
		पूर्ण अन्यथा अणु /* Currently active */
			अगर (value && nd->act_state >=
				     nd->deactivate_slack)
				/*
				 * Live poपूर्णांक: clear accumulated
				 * deactivation count.
				 */
				nd->act_state = 0;
			अन्यथा अगर (nd->act_state <= nd->deactivate_slack)
				/*
				 * We've consumed the deactivation
				 * slack, समय to deactivate and reset.
				 */
				nd->act_state =
					nd->activate_slack;
			अन्यथा अणु /* Move towards deactivation */
				nd->act_state--;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (nd->first_contact_touch && nd->act_state <= 0) अणु
			/*
			 * Check to see अगर we're पढ़ोy to start
			 * emitting touch events.
			 *
			 * Note: activation slack will decrease over
			 * the course of the frame, and it will be
			 * inconsistent from the start to the end of
			 * the frame.  However अगर the frame starts
			 * with slack, first_contact_touch will still
			 * be 0 and we will not get to this poपूर्णांक.
			 */
			input_report_key(input, BTN_TOOL_DOUBLETAP, 1);
			input_report_key(input, BTN_TOUCH, 1);
		पूर्ण अन्यथा अणु
			input_report_key(input, BTN_TOOL_DOUBLETAP, 0);
			input_report_key(input, BTN_TOUCH, 0);
		पूर्ण
		अवरोध;

	शेष:
		/* fall-back to the generic hidinput handling */
		वापस 0;
	पूर्ण

not_claimed_input:

	/* we have handled the hidinput part, now reमुख्यs hiddev */
	अगर ((hid->claimed & HID_CLAIMED_HIDDEV) && hid->hiddev_hid_event)
		hid->hiddev_hid_event(hid, field, usage, value);

	वापस 1;
पूर्ण

अटल पूर्णांक ntrig_input_configured(काष्ठा hid_device *hid,
		काष्ठा hid_input *hidinput)

अणु
	काष्ठा input_dev *input = hidinput->input;

	अगर (hidinput->report->maxfield < 1)
		वापस 0;

	चयन (hidinput->report->field[0]->application) अणु
	हाल HID_DG_PEN:
		input->name = "N-Trig Pen";
		अवरोध;
	हाल HID_DG_TOUCHSCREEN:
		/* These keys are redundant क्रम fingers, clear them
		 * to prevent incorrect identअगरication */
		__clear_bit(BTN_TOOL_PEN, input->keybit);
		__clear_bit(BTN_TOOL_FINGER, input->keybit);
		__clear_bit(BTN_0, input->keybit);
		__set_bit(BTN_TOOL_DOUBLETAP, input->keybit);
		/*
		 * The physical touchscreen (single touch)
		 * input has a value क्रम physical, whereas
		 * the multitouch only has logical input
		 * fields.
		 */
		input->name = (hidinput->report->field[0]->physical) ?
							"N-Trig Touchscreen" :
							"N-Trig MultiTouch";
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ntrig_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा ntrig_data *nd;
	काष्ठा hid_report *report;

	अगर (id->driver_data)
		hdev->quirks |= HID_QUIRK_MULTI_INPUT
				| HID_QUIRK_NO_INIT_REPORTS;

	nd = kदो_स्मृति(माप(काष्ठा ntrig_data), GFP_KERNEL);
	अगर (!nd) अणु
		hid_err(hdev, "cannot allocate N-Trig data\n");
		वापस -ENOMEM;
	पूर्ण

	nd->पढ़ोing_mt = false;
	nd->min_width = 0;
	nd->min_height = 0;
	nd->activate_slack = activate_slack;
	nd->act_state = activate_slack;
	nd->deactivate_slack = -deactivate_slack;
	nd->sensor_logical_width = 1;
	nd->sensor_logical_height = 1;
	nd->sensor_physical_width = 1;
	nd->sensor_physical_height = 1;

	hid_set_drvdata(hdev, nd);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		जाओ err_मुक्त;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT & ~HID_CONNECT_FF);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ err_मुक्त;
	पूर्ण

	/* This is needed क्रम devices with more recent firmware versions */
	report = hdev->report_क्रमागत[HID_FEATURE_REPORT].report_id_hash[0x0a];
	अगर (report) अणु
		/* Let the device settle to ensure the wakeup message माला_लो
		 * through */
		hid_hw_रुको(hdev);
		hid_hw_request(hdev, report, HID_REQ_GET_REPORT);

		/*
		 * Sanity check: अगर the current mode is invalid reset it to
		 * something reasonable.
		 */
		अगर (ntrig_get_mode(hdev) >= 4)
			ntrig_set_mode(hdev, 3);
	पूर्ण

	ntrig_report_version(hdev);

	ret = sysfs_create_group(&hdev->dev.kobj,
			&ntrig_attribute_group);
	अगर (ret)
		hid_err(hdev, "cannot create sysfs group\n");

	वापस 0;
err_मुक्त:
	kमुक्त(nd);
	वापस ret;
पूर्ण

अटल व्योम ntrig_हटाओ(काष्ठा hid_device *hdev)
अणु
	sysfs_हटाओ_group(&hdev->dev.kobj,
			   &ntrig_attribute_group);
	hid_hw_stop(hdev);
	kमुक्त(hid_get_drvdata(hdev));
पूर्ण

अटल स्थिर काष्ठा hid_device_id ntrig_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_1),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_2),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_3),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_4),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_5),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_6),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_7),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_8),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_9),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_10),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_11),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_12),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_13),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_14),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_15),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_16),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_17),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTRIG, USB_DEVICE_ID_NTRIG_TOUCH_SCREEN_18),
		.driver_data = NTRIG_DUPLICATE_USAGES पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ntrig_devices);

अटल स्थिर काष्ठा hid_usage_id ntrig_grabbed_usages[] = अणु
	अणु HID_ANY_ID, HID_ANY_ID, HID_ANY_ID पूर्ण,
	अणु HID_ANY_ID - 1, HID_ANY_ID - 1, HID_ANY_ID - 1 पूर्ण
पूर्ण;

अटल काष्ठा hid_driver ntrig_driver = अणु
	.name = "ntrig",
	.id_table = ntrig_devices,
	.probe = ntrig_probe,
	.हटाओ = ntrig_हटाओ,
	.input_mapping = ntrig_input_mapping,
	.input_mapped = ntrig_input_mapped,
	.input_configured = ntrig_input_configured,
	.usage_table = ntrig_grabbed_usages,
	.event = ntrig_event,
पूर्ण;
module_hid_driver(ntrig_driver);

MODULE_LICENSE("GPL");
