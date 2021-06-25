<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      uvc_ctrl.c  --  USB Video Class driver - Controls
 *
 *      Copyright (C) 2005-2010
 *          Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/atomic.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश "uvcvideo.h"

#घोषणा UVC_CTRL_DATA_CURRENT	0
#घोषणा UVC_CTRL_DATA_BACKUP	1
#घोषणा UVC_CTRL_DATA_MIN	2
#घोषणा UVC_CTRL_DATA_MAX	3
#घोषणा UVC_CTRL_DATA_RES	4
#घोषणा UVC_CTRL_DATA_DEF	5
#घोषणा UVC_CTRL_DATA_LAST	6

/* ------------------------------------------------------------------------
 * Controls
 */

अटल स्थिर काष्ठा uvc_control_info uvc_ctrls[] = अणु
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_BRIGHTNESS_CONTROL,
		.index		= 0,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_CONTRAST_CONTROL,
		.index		= 1,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_HUE_CONTROL,
		.index		= 2,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_SATURATION_CONTROL,
		.index		= 3,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_SHARPNESS_CONTROL,
		.index		= 4,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_GAMMA_CONTROL,
		.index		= 5,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_WHITE_BALANCE_TEMPERATURE_CONTROL,
		.index		= 6,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_WHITE_BALANCE_COMPONENT_CONTROL,
		.index		= 7,
		.size		= 4,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_BACKLIGHT_COMPENSATION_CONTROL,
		.index		= 8,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_GAIN_CONTROL,
		.index		= 9,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_POWER_LINE_FREQUENCY_CONTROL,
		.index		= 10,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_SET_CUR | UVC_CTRL_FLAG_GET_CUR
				| UVC_CTRL_FLAG_GET_DEF | UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_HUE_AUTO_CONTROL,
		.index		= 11,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_SET_CUR | UVC_CTRL_FLAG_GET_CUR
				| UVC_CTRL_FLAG_GET_DEF | UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL,
		.index		= 12,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_SET_CUR | UVC_CTRL_FLAG_GET_CUR
				| UVC_CTRL_FLAG_GET_DEF | UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL,
		.index		= 13,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_SET_CUR | UVC_CTRL_FLAG_GET_CUR
				| UVC_CTRL_FLAG_GET_DEF | UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_DIGITAL_MULTIPLIER_CONTROL,
		.index		= 14,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL,
		.index		= 15,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_ANALOG_VIDEO_STANDARD_CONTROL,
		.index		= 16,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_GET_CUR,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_ANALOG_LOCK_STATUS_CONTROL,
		.index		= 17,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_GET_CUR,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_SCANNING_MODE_CONTROL,
		.index		= 0,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_SET_CUR | UVC_CTRL_FLAG_GET_CUR
				| UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_AE_MODE_CONTROL,
		.index		= 1,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_SET_CUR | UVC_CTRL_FLAG_GET_CUR
				| UVC_CTRL_FLAG_GET_DEF | UVC_CTRL_FLAG_GET_RES
				| UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_AE_PRIORITY_CONTROL,
		.index		= 2,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_SET_CUR | UVC_CTRL_FLAG_GET_CUR
				| UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_EXPOSURE_TIME_ABSOLUTE_CONTROL,
		.index		= 3,
		.size		= 4,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_EXPOSURE_TIME_RELATIVE_CONTROL,
		.index		= 4,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_SET_CUR | UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_FOCUS_ABSOLUTE_CONTROL,
		.index		= 5,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_FOCUS_RELATIVE_CONTROL,
		.index		= 6,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR | UVC_CTRL_FLAG_GET_MIN
				| UVC_CTRL_FLAG_GET_MAX | UVC_CTRL_FLAG_GET_RES
				| UVC_CTRL_FLAG_GET_DEF
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_IRIS_ABSOLUTE_CONTROL,
		.index		= 7,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_IRIS_RELATIVE_CONTROL,
		.index		= 8,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_ZOOM_ABSOLUTE_CONTROL,
		.index		= 9,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_ZOOM_RELATIVE_CONTROL,
		.index		= 10,
		.size		= 3,
		.flags		= UVC_CTRL_FLAG_SET_CUR | UVC_CTRL_FLAG_GET_MIN
				| UVC_CTRL_FLAG_GET_MAX | UVC_CTRL_FLAG_GET_RES
				| UVC_CTRL_FLAG_GET_DEF
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_PANTILT_ABSOLUTE_CONTROL,
		.index		= 11,
		.size		= 8,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_PANTILT_RELATIVE_CONTROL,
		.index		= 12,
		.size		= 4,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_ROLL_ABSOLUTE_CONTROL,
		.index		= 13,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR
				| UVC_CTRL_FLAG_GET_RANGE
				| UVC_CTRL_FLAG_RESTORE
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_ROLL_RELATIVE_CONTROL,
		.index		= 14,
		.size		= 2,
		.flags		= UVC_CTRL_FLAG_SET_CUR | UVC_CTRL_FLAG_GET_MIN
				| UVC_CTRL_FLAG_GET_MAX | UVC_CTRL_FLAG_GET_RES
				| UVC_CTRL_FLAG_GET_DEF
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_FOCUS_AUTO_CONTROL,
		.index		= 17,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_SET_CUR | UVC_CTRL_FLAG_GET_CUR
				| UVC_CTRL_FLAG_GET_DEF | UVC_CTRL_FLAG_RESTORE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_PRIVACY_CONTROL,
		.index		= 18,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_SET_CUR | UVC_CTRL_FLAG_GET_CUR
				| UVC_CTRL_FLAG_RESTORE
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
	अणु
		.entity		= UVC_GUID_EXT_GPIO_CONTROLLER,
		.selector	= UVC_CT_PRIVACY_CONTROL,
		.index		= 0,
		.size		= 1,
		.flags		= UVC_CTRL_FLAG_GET_CUR
				| UVC_CTRL_FLAG_AUTO_UPDATE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा uvc_menu_info घातer_line_frequency_controls[] = अणु
	अणु 0, "Disabled" पूर्ण,
	अणु 1, "50 Hz" पूर्ण,
	अणु 2, "60 Hz" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा uvc_menu_info exposure_स्वतः_controls[] = अणु
	अणु 2, "Auto Mode" पूर्ण,
	अणु 1, "Manual Mode" पूर्ण,
	अणु 4, "Shutter Priority Mode" पूर्ण,
	अणु 8, "Aperture Priority Mode" पूर्ण,
पूर्ण;

अटल s32 uvc_ctrl_get_zoom(काष्ठा uvc_control_mapping *mapping,
	u8 query, स्थिर u8 *data)
अणु
	s8 zoom = (s8)data[0];

	चयन (query) अणु
	हाल UVC_GET_CUR:
		वापस (zoom == 0) ? 0 : (zoom > 0 ? data[2] : -data[2]);

	हाल UVC_GET_MIN:
	हाल UVC_GET_MAX:
	हाल UVC_GET_RES:
	हाल UVC_GET_DEF:
	शेष:
		वापस data[2];
	पूर्ण
पूर्ण

अटल व्योम uvc_ctrl_set_zoom(काष्ठा uvc_control_mapping *mapping,
	s32 value, u8 *data)
अणु
	data[0] = value == 0 ? 0 : (value > 0) ? 1 : 0xff;
	data[2] = min((पूर्णांक)असल(value), 0xff);
पूर्ण

अटल s32 uvc_ctrl_get_rel_speed(काष्ठा uvc_control_mapping *mapping,
	u8 query, स्थिर u8 *data)
अणु
	अचिन्हित पूर्णांक first = mapping->offset / 8;
	s8 rel = (s8)data[first];

	चयन (query) अणु
	हाल UVC_GET_CUR:
		वापस (rel == 0) ? 0 : (rel > 0 ? data[first+1]
						 : -data[first+1]);
	हाल UVC_GET_MIN:
		वापस -data[first+1];
	हाल UVC_GET_MAX:
	हाल UVC_GET_RES:
	हाल UVC_GET_DEF:
	शेष:
		वापस data[first+1];
	पूर्ण
पूर्ण

अटल व्योम uvc_ctrl_set_rel_speed(काष्ठा uvc_control_mapping *mapping,
	s32 value, u8 *data)
अणु
	अचिन्हित पूर्णांक first = mapping->offset / 8;

	data[first] = value == 0 ? 0 : (value > 0) ? 1 : 0xff;
	data[first+1] = min_t(पूर्णांक, असल(value), 0xff);
पूर्ण

अटल स्थिर काष्ठा uvc_control_mapping uvc_ctrl_mappings[] = अणु
	अणु
		.id		= V4L2_CID_BRIGHTNESS,
		.name		= "Brightness",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_BRIGHTNESS_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_SIGNED,
	पूर्ण,
	अणु
		.id		= V4L2_CID_CONTRAST,
		.name		= "Contrast",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_CONTRAST_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_UNSIGNED,
	पूर्ण,
	अणु
		.id		= V4L2_CID_HUE,
		.name		= "Hue",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_HUE_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_SIGNED,
		.master_id	= V4L2_CID_HUE_AUTO,
		.master_manual	= 0,
	पूर्ण,
	अणु
		.id		= V4L2_CID_SATURATION,
		.name		= "Saturation",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_SATURATION_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_UNSIGNED,
	पूर्ण,
	अणु
		.id		= V4L2_CID_SHARPNESS,
		.name		= "Sharpness",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_SHARPNESS_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_UNSIGNED,
	पूर्ण,
	अणु
		.id		= V4L2_CID_GAMMA,
		.name		= "Gamma",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_GAMMA_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_UNSIGNED,
	पूर्ण,
	अणु
		.id		= V4L2_CID_BACKLIGHT_COMPENSATION,
		.name		= "Backlight Compensation",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_BACKLIGHT_COMPENSATION_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_UNSIGNED,
	पूर्ण,
	अणु
		.id		= V4L2_CID_GAIN,
		.name		= "Gain",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_GAIN_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_UNSIGNED,
	पूर्ण,
	अणु
		.id		= V4L2_CID_POWER_LINE_FREQUENCY,
		.name		= "Power Line Frequency",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_POWER_LINE_FREQUENCY_CONTROL,
		.size		= 2,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_MENU,
		.data_type	= UVC_CTRL_DATA_TYPE_ENUM,
		.menu_info	= घातer_line_frequency_controls,
		.menu_count	= ARRAY_SIZE(घातer_line_frequency_controls),
	पूर्ण,
	अणु
		.id		= V4L2_CID_HUE_AUTO,
		.name		= "Hue, Auto",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_HUE_AUTO_CONTROL,
		.size		= 1,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_BOOLEAN,
		.data_type	= UVC_CTRL_DATA_TYPE_BOOLEAN,
		.slave_ids	= अणु V4L2_CID_HUE, पूर्ण,
	पूर्ण,
	अणु
		.id		= V4L2_CID_EXPOSURE_AUTO,
		.name		= "Exposure, Auto",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_AE_MODE_CONTROL,
		.size		= 4,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_MENU,
		.data_type	= UVC_CTRL_DATA_TYPE_BITMASK,
		.menu_info	= exposure_स्वतः_controls,
		.menu_count	= ARRAY_SIZE(exposure_स्वतः_controls),
		.slave_ids	= अणु V4L2_CID_EXPOSURE_ABSOLUTE, पूर्ण,
	पूर्ण,
	अणु
		.id		= V4L2_CID_EXPOSURE_AUTO_PRIORITY,
		.name		= "Exposure, Auto Priority",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_AE_PRIORITY_CONTROL,
		.size		= 1,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_BOOLEAN,
		.data_type	= UVC_CTRL_DATA_TYPE_BOOLEAN,
	पूर्ण,
	अणु
		.id		= V4L2_CID_EXPOSURE_ABSOLUTE,
		.name		= "Exposure (Absolute)",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_EXPOSURE_TIME_ABSOLUTE_CONTROL,
		.size		= 32,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_UNSIGNED,
		.master_id	= V4L2_CID_EXPOSURE_AUTO,
		.master_manual	= V4L2_EXPOSURE_MANUAL,
	पूर्ण,
	अणु
		.id		= V4L2_CID_AUTO_WHITE_BALANCE,
		.name		= "White Balance Temperature, Auto",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL,
		.size		= 1,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_BOOLEAN,
		.data_type	= UVC_CTRL_DATA_TYPE_BOOLEAN,
		.slave_ids	= अणु V4L2_CID_WHITE_BALANCE_TEMPERATURE, पूर्ण,
	पूर्ण,
	अणु
		.id		= V4L2_CID_WHITE_BALANCE_TEMPERATURE,
		.name		= "White Balance Temperature",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_WHITE_BALANCE_TEMPERATURE_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_UNSIGNED,
		.master_id	= V4L2_CID_AUTO_WHITE_BALANCE,
		.master_manual	= 0,
	पूर्ण,
	अणु
		.id		= V4L2_CID_AUTO_WHITE_BALANCE,
		.name		= "White Balance Component, Auto",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL,
		.size		= 1,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_BOOLEAN,
		.data_type	= UVC_CTRL_DATA_TYPE_BOOLEAN,
		.slave_ids	= अणु V4L2_CID_BLUE_BALANCE,
				    V4L2_CID_RED_BALANCE पूर्ण,
	पूर्ण,
	अणु
		.id		= V4L2_CID_BLUE_BALANCE,
		.name		= "White Balance Blue Component",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_WHITE_BALANCE_COMPONENT_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_SIGNED,
		.master_id	= V4L2_CID_AUTO_WHITE_BALANCE,
		.master_manual	= 0,
	पूर्ण,
	अणु
		.id		= V4L2_CID_RED_BALANCE,
		.name		= "White Balance Red Component",
		.entity		= UVC_GUID_UVC_PROCESSING,
		.selector	= UVC_PU_WHITE_BALANCE_COMPONENT_CONTROL,
		.size		= 16,
		.offset		= 16,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_SIGNED,
		.master_id	= V4L2_CID_AUTO_WHITE_BALANCE,
		.master_manual	= 0,
	पूर्ण,
	अणु
		.id		= V4L2_CID_FOCUS_ABSOLUTE,
		.name		= "Focus (absolute)",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_FOCUS_ABSOLUTE_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_UNSIGNED,
		.master_id	= V4L2_CID_FOCUS_AUTO,
		.master_manual	= 0,
	पूर्ण,
	अणु
		.id		= V4L2_CID_FOCUS_AUTO,
		.name		= "Focus, Auto",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_FOCUS_AUTO_CONTROL,
		.size		= 1,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_BOOLEAN,
		.data_type	= UVC_CTRL_DATA_TYPE_BOOLEAN,
		.slave_ids	= अणु V4L2_CID_FOCUS_ABSOLUTE, पूर्ण,
	पूर्ण,
	अणु
		.id		= V4L2_CID_IRIS_ABSOLUTE,
		.name		= "Iris, Absolute",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_IRIS_ABSOLUTE_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_UNSIGNED,
	पूर्ण,
	अणु
		.id		= V4L2_CID_IRIS_RELATIVE,
		.name		= "Iris, Relative",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_IRIS_RELATIVE_CONTROL,
		.size		= 8,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_SIGNED,
	पूर्ण,
	अणु
		.id		= V4L2_CID_ZOOM_ABSOLUTE,
		.name		= "Zoom, Absolute",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_ZOOM_ABSOLUTE_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_UNSIGNED,
	पूर्ण,
	अणु
		.id		= V4L2_CID_ZOOM_CONTINUOUS,
		.name		= "Zoom, Continuous",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_ZOOM_RELATIVE_CONTROL,
		.size		= 0,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_SIGNED,
		.get		= uvc_ctrl_get_zoom,
		.set		= uvc_ctrl_set_zoom,
	पूर्ण,
	अणु
		.id		= V4L2_CID_PAN_ABSOLUTE,
		.name		= "Pan (Absolute)",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_PANTILT_ABSOLUTE_CONTROL,
		.size		= 32,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_SIGNED,
	पूर्ण,
	अणु
		.id		= V4L2_CID_TILT_ABSOLUTE,
		.name		= "Tilt (Absolute)",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_PANTILT_ABSOLUTE_CONTROL,
		.size		= 32,
		.offset		= 32,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_SIGNED,
	पूर्ण,
	अणु
		.id		= V4L2_CID_PAN_SPEED,
		.name		= "Pan (Speed)",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_PANTILT_RELATIVE_CONTROL,
		.size		= 16,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_SIGNED,
		.get		= uvc_ctrl_get_rel_speed,
		.set		= uvc_ctrl_set_rel_speed,
	पूर्ण,
	अणु
		.id		= V4L2_CID_TILT_SPEED,
		.name		= "Tilt (Speed)",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_PANTILT_RELATIVE_CONTROL,
		.size		= 16,
		.offset		= 16,
		.v4l2_type	= V4L2_CTRL_TYPE_INTEGER,
		.data_type	= UVC_CTRL_DATA_TYPE_SIGNED,
		.get		= uvc_ctrl_get_rel_speed,
		.set		= uvc_ctrl_set_rel_speed,
	पूर्ण,
	अणु
		.id		= V4L2_CID_PRIVACY,
		.name		= "Privacy",
		.entity		= UVC_GUID_UVC_CAMERA,
		.selector	= UVC_CT_PRIVACY_CONTROL,
		.size		= 1,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_BOOLEAN,
		.data_type	= UVC_CTRL_DATA_TYPE_BOOLEAN,
	पूर्ण,
	अणु
		.id		= V4L2_CID_PRIVACY,
		.name		= "Privacy",
		.entity		= UVC_GUID_EXT_GPIO_CONTROLLER,
		.selector	= UVC_CT_PRIVACY_CONTROL,
		.size		= 1,
		.offset		= 0,
		.v4l2_type	= V4L2_CTRL_TYPE_BOOLEAN,
		.data_type	= UVC_CTRL_DATA_TYPE_BOOLEAN,
	पूर्ण,
पूर्ण;

/* ------------------------------------------------------------------------
 * Utility functions
 */

अटल अंतरभूत u8 *uvc_ctrl_data(काष्ठा uvc_control *ctrl, पूर्णांक id)
अणु
	वापस ctrl->uvc_data + id * ctrl->info.size;
पूर्ण

अटल अंतरभूत पूर्णांक uvc_test_bit(स्थिर u8 *data, पूर्णांक bit)
अणु
	वापस (data[bit >> 3] >> (bit & 7)) & 1;
पूर्ण

अटल अंतरभूत व्योम uvc_clear_bit(u8 *data, पूर्णांक bit)
अणु
	data[bit >> 3] &= ~(1 << (bit & 7));
पूर्ण

/* Extract the bit string specअगरied by mapping->offset and mapping->size
 * from the little-endian data stored at 'data' and वापस the result as
 * a चिन्हित 32bit पूर्णांकeger. Sign extension will be perक्रमmed अगर the mapping
 * references a चिन्हित data type.
 */
अटल s32 uvc_get_le_value(काष्ठा uvc_control_mapping *mapping,
	u8 query, स्थिर u8 *data)
अणु
	पूर्णांक bits = mapping->size;
	पूर्णांक offset = mapping->offset;
	s32 value = 0;
	u8 mask;

	data += offset / 8;
	offset &= 7;
	mask = ((1LL << bits) - 1) << offset;

	जबतक (1) अणु
		u8 byte = *data & mask;
		value |= offset > 0 ? (byte >> offset) : (byte << (-offset));
		bits -= 8 - (offset > 0 ? offset : 0);
		अगर (bits <= 0)
			अवरोध;

		offset -= 8;
		mask = (1 << bits) - 1;
		data++;
	पूर्ण

	/* Sign-extend the value अगर needed. */
	अगर (mapping->data_type == UVC_CTRL_DATA_TYPE_SIGNED)
		value |= -(value & (1 << (mapping->size - 1)));

	वापस value;
पूर्ण

/* Set the bit string specअगरied by mapping->offset and mapping->size
 * in the little-endian data stored at 'data' to the value 'value'.
 */
अटल व्योम uvc_set_le_value(काष्ठा uvc_control_mapping *mapping,
	s32 value, u8 *data)
अणु
	पूर्णांक bits = mapping->size;
	पूर्णांक offset = mapping->offset;
	u8 mask;

	/* According to the v4l2 spec, writing any value to a button control
	 * should result in the action beदीर्घing to the button control being
	 * triggered. UVC devices however want to see a 1 written -> override
	 * value.
	 */
	अगर (mapping->v4l2_type == V4L2_CTRL_TYPE_BUTTON)
		value = -1;

	data += offset / 8;
	offset &= 7;

	क्रम (; bits > 0; data++) अणु
		mask = ((1LL << bits) - 1) << offset;
		*data = (*data & ~mask) | ((value << offset) & mask);
		value >>= offset ? offset : 8;
		bits -= 8 - offset;
		offset = 0;
	पूर्ण
पूर्ण

/* ------------------------------------------------------------------------
 * Terminal and unit management
 */

अटल पूर्णांक uvc_entity_match_guid(स्थिर काष्ठा uvc_entity *entity,
				 स्थिर u8 guid[16])
अणु
	वापस स_भेद(entity->guid, guid, माप(entity->guid)) == 0;
पूर्ण

/* ------------------------------------------------------------------------
 * UVC Controls
 */

अटल व्योम __uvc_find_control(काष्ठा uvc_entity *entity, u32 v4l2_id,
	काष्ठा uvc_control_mapping **mapping, काष्ठा uvc_control **control,
	पूर्णांक next)
अणु
	काष्ठा uvc_control *ctrl;
	काष्ठा uvc_control_mapping *map;
	अचिन्हित पूर्णांक i;

	अगर (entity == शून्य)
		वापस;

	क्रम (i = 0; i < entity->ncontrols; ++i) अणु
		ctrl = &entity->controls[i];
		अगर (!ctrl->initialized)
			जारी;

		list_क्रम_each_entry(map, &ctrl->info.mappings, list) अणु
			अगर ((map->id == v4l2_id) && !next) अणु
				*control = ctrl;
				*mapping = map;
				वापस;
			पूर्ण

			अगर ((*mapping == शून्य || (*mapping)->id > map->id) &&
			    (map->id > v4l2_id) && next) अणु
				*control = ctrl;
				*mapping = map;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा uvc_control *uvc_find_control(काष्ठा uvc_video_chain *chain,
	u32 v4l2_id, काष्ठा uvc_control_mapping **mapping)
अणु
	काष्ठा uvc_control *ctrl = शून्य;
	काष्ठा uvc_entity *entity;
	पूर्णांक next = v4l2_id & V4L2_CTRL_FLAG_NEXT_CTRL;

	*mapping = शून्य;

	/* Mask the query flags. */
	v4l2_id &= V4L2_CTRL_ID_MASK;

	/* Find the control. */
	list_क्रम_each_entry(entity, &chain->entities, chain) अणु
		__uvc_find_control(entity, v4l2_id, mapping, &ctrl, next);
		अगर (ctrl && !next)
			वापस ctrl;
	पूर्ण

	अगर (ctrl == शून्य && !next)
		uvc_dbg(chain->dev, CONTROL, "Control 0x%08x not found\n",
			v4l2_id);

	वापस ctrl;
पूर्ण

अटल पूर्णांक uvc_ctrl_populate_cache(काष्ठा uvc_video_chain *chain,
	काष्ठा uvc_control *ctrl)
अणु
	पूर्णांक ret;

	अगर (ctrl->info.flags & UVC_CTRL_FLAG_GET_DEF) अणु
		ret = uvc_query_ctrl(chain->dev, UVC_GET_DEF, ctrl->entity->id,
				     chain->dev->पूर्णांकfnum, ctrl->info.selector,
				     uvc_ctrl_data(ctrl, UVC_CTRL_DATA_DEF),
				     ctrl->info.size);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (ctrl->info.flags & UVC_CTRL_FLAG_GET_MIN) अणु
		ret = uvc_query_ctrl(chain->dev, UVC_GET_MIN, ctrl->entity->id,
				     chain->dev->पूर्णांकfnum, ctrl->info.selector,
				     uvc_ctrl_data(ctrl, UVC_CTRL_DATA_MIN),
				     ctrl->info.size);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	अगर (ctrl->info.flags & UVC_CTRL_FLAG_GET_MAX) अणु
		ret = uvc_query_ctrl(chain->dev, UVC_GET_MAX, ctrl->entity->id,
				     chain->dev->पूर्णांकfnum, ctrl->info.selector,
				     uvc_ctrl_data(ctrl, UVC_CTRL_DATA_MAX),
				     ctrl->info.size);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	अगर (ctrl->info.flags & UVC_CTRL_FLAG_GET_RES) अणु
		ret = uvc_query_ctrl(chain->dev, UVC_GET_RES, ctrl->entity->id,
				     chain->dev->पूर्णांकfnum, ctrl->info.selector,
				     uvc_ctrl_data(ctrl, UVC_CTRL_DATA_RES),
				     ctrl->info.size);
		अगर (ret < 0) अणु
			अगर (UVC_ENTITY_TYPE(ctrl->entity) !=
			    UVC_VC_EXTENSION_UNIT)
				वापस ret;

			/* GET_RES is mandatory क्रम XU controls, but some
			 * cameras still choke on it. Ignore errors and set the
			 * resolution value to zero.
			 */
			uvc_warn_once(chain->dev, UVC_WARN_XU_GET_RES,
				      "UVC non compliance - GET_RES failed on "
				      "an XU control. Enabling workaround.\n");
			स_रखो(uvc_ctrl_data(ctrl, UVC_CTRL_DATA_RES), 0,
			       ctrl->info.size);
		पूर्ण
	पूर्ण

	ctrl->cached = 1;
	वापस 0;
पूर्ण

अटल s32 __uvc_ctrl_get_value(काष्ठा uvc_control_mapping *mapping,
				स्थिर u8 *data)
अणु
	s32 value = mapping->get(mapping, UVC_GET_CUR, data);

	अगर (mapping->v4l2_type == V4L2_CTRL_TYPE_MENU) अणु
		स्थिर काष्ठा uvc_menu_info *menu = mapping->menu_info;
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < mapping->menu_count; ++i, ++menu) अणु
			अगर (menu->value == value) अणु
				value = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक __uvc_ctrl_get(काष्ठा uvc_video_chain *chain,
	काष्ठा uvc_control *ctrl, काष्ठा uvc_control_mapping *mapping,
	s32 *value)
अणु
	पूर्णांक ret;

	अगर ((ctrl->info.flags & UVC_CTRL_FLAG_GET_CUR) == 0)
		वापस -EACCES;

	अगर (!ctrl->loaded) अणु
		अगर (ctrl->entity->get_cur) अणु
			ret = ctrl->entity->get_cur(chain->dev,
				ctrl->entity,
				ctrl->info.selector,
				uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT),
				ctrl->info.size);
		पूर्ण अन्यथा अणु
			ret = uvc_query_ctrl(chain->dev, UVC_GET_CUR,
				ctrl->entity->id,
				chain->dev->पूर्णांकfnum,
				ctrl->info.selector,
				uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT),
				ctrl->info.size);
		पूर्ण
		अगर (ret < 0)
			वापस ret;

		ctrl->loaded = 1;
	पूर्ण

	*value = __uvc_ctrl_get_value(mapping,
				uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT));

	वापस 0;
पूर्ण

अटल पूर्णांक __uvc_query_v4l2_ctrl(काष्ठा uvc_video_chain *chain,
	काष्ठा uvc_control *ctrl,
	काष्ठा uvc_control_mapping *mapping,
	काष्ठा v4l2_queryctrl *v4l2_ctrl)
अणु
	काष्ठा uvc_control_mapping *master_map = शून्य;
	काष्ठा uvc_control *master_ctrl = शून्य;
	स्थिर काष्ठा uvc_menu_info *menu;
	अचिन्हित पूर्णांक i;

	स_रखो(v4l2_ctrl, 0, माप(*v4l2_ctrl));
	v4l2_ctrl->id = mapping->id;
	v4l2_ctrl->type = mapping->v4l2_type;
	strscpy(v4l2_ctrl->name, mapping->name, माप(v4l2_ctrl->name));
	v4l2_ctrl->flags = 0;

	अगर (!(ctrl->info.flags & UVC_CTRL_FLAG_GET_CUR))
		v4l2_ctrl->flags |= V4L2_CTRL_FLAG_WRITE_ONLY;
	अगर (!(ctrl->info.flags & UVC_CTRL_FLAG_SET_CUR))
		v4l2_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	अगर (mapping->master_id)
		__uvc_find_control(ctrl->entity, mapping->master_id,
				   &master_map, &master_ctrl, 0);
	अगर (master_ctrl && (master_ctrl->info.flags & UVC_CTRL_FLAG_GET_CUR)) अणु
		s32 val;
		पूर्णांक ret = __uvc_ctrl_get(chain, master_ctrl, master_map, &val);
		अगर (ret < 0)
			वापस ret;

		अगर (val != mapping->master_manual)
				v4l2_ctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
	पूर्ण

	अगर (!ctrl->cached) अणु
		पूर्णांक ret = uvc_ctrl_populate_cache(chain, ctrl);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (ctrl->info.flags & UVC_CTRL_FLAG_GET_DEF) अणु
		v4l2_ctrl->शेष_value = mapping->get(mapping, UVC_GET_DEF,
				uvc_ctrl_data(ctrl, UVC_CTRL_DATA_DEF));
	पूर्ण

	चयन (mapping->v4l2_type) अणु
	हाल V4L2_CTRL_TYPE_MENU:
		v4l2_ctrl->minimum = 0;
		v4l2_ctrl->maximum = mapping->menu_count - 1;
		v4l2_ctrl->step = 1;

		menu = mapping->menu_info;
		क्रम (i = 0; i < mapping->menu_count; ++i, ++menu) अणु
			अगर (menu->value == v4l2_ctrl->शेष_value) अणु
				v4l2_ctrl->शेष_value = i;
				अवरोध;
			पूर्ण
		पूर्ण

		वापस 0;

	हाल V4L2_CTRL_TYPE_BOOLEAN:
		v4l2_ctrl->minimum = 0;
		v4l2_ctrl->maximum = 1;
		v4l2_ctrl->step = 1;
		वापस 0;

	हाल V4L2_CTRL_TYPE_BUTTON:
		v4l2_ctrl->minimum = 0;
		v4l2_ctrl->maximum = 0;
		v4l2_ctrl->step = 0;
		वापस 0;

	शेष:
		अवरोध;
	पूर्ण

	अगर (ctrl->info.flags & UVC_CTRL_FLAG_GET_MIN)
		v4l2_ctrl->minimum = mapping->get(mapping, UVC_GET_MIN,
				     uvc_ctrl_data(ctrl, UVC_CTRL_DATA_MIN));

	अगर (ctrl->info.flags & UVC_CTRL_FLAG_GET_MAX)
		v4l2_ctrl->maximum = mapping->get(mapping, UVC_GET_MAX,
				     uvc_ctrl_data(ctrl, UVC_CTRL_DATA_MAX));

	अगर (ctrl->info.flags & UVC_CTRL_FLAG_GET_RES)
		v4l2_ctrl->step = mapping->get(mapping, UVC_GET_RES,
				  uvc_ctrl_data(ctrl, UVC_CTRL_DATA_RES));

	वापस 0;
पूर्ण

पूर्णांक uvc_query_v4l2_ctrl(काष्ठा uvc_video_chain *chain,
	काष्ठा v4l2_queryctrl *v4l2_ctrl)
अणु
	काष्ठा uvc_control *ctrl;
	काष्ठा uvc_control_mapping *mapping;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&chain->ctrl_mutex);
	अगर (ret < 0)
		वापस -ERESTARTSYS;

	ctrl = uvc_find_control(chain, v4l2_ctrl->id, &mapping);
	अगर (ctrl == शून्य) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	ret = __uvc_query_v4l2_ctrl(chain, ctrl, mapping, v4l2_ctrl);
करोne:
	mutex_unlock(&chain->ctrl_mutex);
	वापस ret;
पूर्ण

/*
 * Mapping V4L2 controls to UVC controls can be straightक्रमward अगर करोne well.
 * Most of the UVC controls exist in V4L2, and can be mapped directly. Some
 * must be grouped (क्रम instance the Red Balance, Blue Balance and Do White
 * Balance V4L2 controls use the White Balance Component UVC control) or
 * otherwise translated. The approach we take here is to use a translation
 * table क्रम the controls that can be mapped directly, and handle the others
 * manually.
 */
पूर्णांक uvc_query_v4l2_menu(काष्ठा uvc_video_chain *chain,
	काष्ठा v4l2_querymenu *query_menu)
अणु
	स्थिर काष्ठा uvc_menu_info *menu_info;
	काष्ठा uvc_control_mapping *mapping;
	काष्ठा uvc_control *ctrl;
	u32 index = query_menu->index;
	u32 id = query_menu->id;
	पूर्णांक ret;

	स_रखो(query_menu, 0, माप(*query_menu));
	query_menu->id = id;
	query_menu->index = index;

	ret = mutex_lock_पूर्णांकerruptible(&chain->ctrl_mutex);
	अगर (ret < 0)
		वापस -ERESTARTSYS;

	ctrl = uvc_find_control(chain, query_menu->id, &mapping);
	अगर (ctrl == शून्य || mapping->v4l2_type != V4L2_CTRL_TYPE_MENU) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (query_menu->index >= mapping->menu_count) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	menu_info = &mapping->menu_info[query_menu->index];

	अगर (mapping->data_type == UVC_CTRL_DATA_TYPE_BITMASK &&
	    (ctrl->info.flags & UVC_CTRL_FLAG_GET_RES)) अणु
		s32 biपंचांगap;

		अगर (!ctrl->cached) अणु
			ret = uvc_ctrl_populate_cache(chain, ctrl);
			अगर (ret < 0)
				जाओ करोne;
		पूर्ण

		biपंचांगap = mapping->get(mapping, UVC_GET_RES,
				      uvc_ctrl_data(ctrl, UVC_CTRL_DATA_RES));
		अगर (!(biपंचांगap & menu_info->value)) अणु
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
	पूर्ण

	strscpy(query_menu->name, menu_info->name, माप(query_menu->name));

करोne:
	mutex_unlock(&chain->ctrl_mutex);
	वापस ret;
पूर्ण

/* --------------------------------------------------------------------------
 * Ctrl event handling
 */

अटल व्योम uvc_ctrl_fill_event(काष्ठा uvc_video_chain *chain,
	काष्ठा v4l2_event *ev,
	काष्ठा uvc_control *ctrl,
	काष्ठा uvc_control_mapping *mapping,
	s32 value, u32 changes)
अणु
	काष्ठा v4l2_queryctrl v4l2_ctrl;

	__uvc_query_v4l2_ctrl(chain, ctrl, mapping, &v4l2_ctrl);

	स_रखो(ev, 0, माप(*ev));
	ev->type = V4L2_EVENT_CTRL;
	ev->id = v4l2_ctrl.id;
	ev->u.ctrl.value = value;
	ev->u.ctrl.changes = changes;
	ev->u.ctrl.type = v4l2_ctrl.type;
	ev->u.ctrl.flags = v4l2_ctrl.flags;
	ev->u.ctrl.minimum = v4l2_ctrl.minimum;
	ev->u.ctrl.maximum = v4l2_ctrl.maximum;
	ev->u.ctrl.step = v4l2_ctrl.step;
	ev->u.ctrl.शेष_value = v4l2_ctrl.शेष_value;
पूर्ण

/*
 * Send control change events to all subscribers क्रम the @ctrl control. By
 * शेष the subscriber that generated the event, as identअगरied by @handle,
 * is not notअगरied unless it has set the V4L2_EVENT_SUB_FL_ALLOW_FEEDBACK flag.
 * @handle can be शून्य क्रम asynchronous events related to स्वतः-update controls,
 * in which हाल all subscribers are notअगरied.
 */
अटल व्योम uvc_ctrl_send_event(काष्ठा uvc_video_chain *chain,
	काष्ठा uvc_fh *handle, काष्ठा uvc_control *ctrl,
	काष्ठा uvc_control_mapping *mapping, s32 value, u32 changes)
अणु
	काष्ठा v4l2_fh *originator = handle ? &handle->vfh : शून्य;
	काष्ठा v4l2_subscribed_event *sev;
	काष्ठा v4l2_event ev;

	अगर (list_empty(&mapping->ev_subs))
		वापस;

	uvc_ctrl_fill_event(chain, &ev, ctrl, mapping, value, changes);

	list_क्रम_each_entry(sev, &mapping->ev_subs, node) अणु
		अगर (sev->fh != originator ||
		    (sev->flags & V4L2_EVENT_SUB_FL_ALLOW_FEEDBACK) ||
		    (changes & V4L2_EVENT_CTRL_CH_FLAGS))
			v4l2_event_queue_fh(sev->fh, &ev);
	पूर्ण
पूर्ण

/*
 * Send control change events क्रम the slave of the @master control identअगरied
 * by the V4L2 ID @slave_id. The @handle identअगरies the event subscriber that
 * generated the event and may be शून्य क्रम स्वतः-update events.
 */
अटल व्योम uvc_ctrl_send_slave_event(काष्ठा uvc_video_chain *chain,
	काष्ठा uvc_fh *handle, काष्ठा uvc_control *master, u32 slave_id)
अणु
	काष्ठा uvc_control_mapping *mapping = शून्य;
	काष्ठा uvc_control *ctrl = शून्य;
	u32 changes = V4L2_EVENT_CTRL_CH_FLAGS;
	s32 val = 0;

	__uvc_find_control(master->entity, slave_id, &mapping, &ctrl, 0);
	अगर (ctrl == शून्य)
		वापस;

	अगर (__uvc_ctrl_get(chain, ctrl, mapping, &val) == 0)
		changes |= V4L2_EVENT_CTRL_CH_VALUE;

	uvc_ctrl_send_event(chain, handle, ctrl, mapping, val, changes);
पूर्ण

व्योम uvc_ctrl_status_event(काष्ठा uvc_video_chain *chain,
			   काष्ठा uvc_control *ctrl, स्थिर u8 *data)
अणु
	काष्ठा uvc_control_mapping *mapping;
	काष्ठा uvc_fh *handle;
	अचिन्हित पूर्णांक i;

	mutex_lock(&chain->ctrl_mutex);

	handle = ctrl->handle;
	ctrl->handle = शून्य;

	list_क्रम_each_entry(mapping, &ctrl->info.mappings, list) अणु
		s32 value = __uvc_ctrl_get_value(mapping, data);

		/*
		 * handle may be शून्य here अगर the device sends स्वतः-update
		 * events without a prior related control set from userspace.
		 */
		क्रम (i = 0; i < ARRAY_SIZE(mapping->slave_ids); ++i) अणु
			अगर (!mapping->slave_ids[i])
				अवरोध;

			uvc_ctrl_send_slave_event(chain, handle, ctrl,
						  mapping->slave_ids[i]);
		पूर्ण

		uvc_ctrl_send_event(chain, handle, ctrl, mapping, value,
				    V4L2_EVENT_CTRL_CH_VALUE);
	पूर्ण

	mutex_unlock(&chain->ctrl_mutex);
पूर्ण

अटल व्योम uvc_ctrl_status_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा uvc_device *dev = container_of(work, काष्ठा uvc_device,
					      async_ctrl.work);
	काष्ठा uvc_ctrl_work *w = &dev->async_ctrl;
	पूर्णांक ret;

	uvc_ctrl_status_event(w->chain, w->ctrl, w->data);

	/* Resubmit the URB. */
	w->urb->पूर्णांकerval = dev->पूर्णांक_ep->desc.bInterval;
	ret = usb_submit_urb(w->urb, GFP_KERNEL);
	अगर (ret < 0)
		dev_err(&dev->udev->dev,
			"Failed to resubmit status URB (%d).\n", ret);
पूर्ण

bool uvc_ctrl_status_event_async(काष्ठा urb *urb, काष्ठा uvc_video_chain *chain,
				 काष्ठा uvc_control *ctrl, स्थिर u8 *data)
अणु
	काष्ठा uvc_device *dev = chain->dev;
	काष्ठा uvc_ctrl_work *w = &dev->async_ctrl;

	अगर (list_empty(&ctrl->info.mappings)) अणु
		ctrl->handle = शून्य;
		वापस false;
	पूर्ण

	w->data = data;
	w->urb = urb;
	w->chain = chain;
	w->ctrl = ctrl;

	schedule_work(&w->work);

	वापस true;
पूर्ण

अटल bool uvc_ctrl_xctrls_has_control(स्थिर काष्ठा v4l2_ext_control *xctrls,
					अचिन्हित पूर्णांक xctrls_count, u32 id)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < xctrls_count; ++i) अणु
		अगर (xctrls[i].id == id)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम uvc_ctrl_send_events(काष्ठा uvc_fh *handle,
	स्थिर काष्ठा v4l2_ext_control *xctrls, अचिन्हित पूर्णांक xctrls_count)
अणु
	काष्ठा uvc_control_mapping *mapping;
	काष्ठा uvc_control *ctrl;
	u32 changes = V4L2_EVENT_CTRL_CH_VALUE;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक j;

	क्रम (i = 0; i < xctrls_count; ++i) अणु
		ctrl = uvc_find_control(handle->chain, xctrls[i].id, &mapping);

		अगर (ctrl->info.flags & UVC_CTRL_FLAG_ASYNCHRONOUS)
			/* Notअगरication will be sent from an Interrupt event. */
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(mapping->slave_ids); ++j) अणु
			u32 slave_id = mapping->slave_ids[j];

			अगर (!slave_id)
				अवरोध;

			/*
			 * We can skip sending an event क्रम the slave अगर the
			 * slave is being modअगरied in the same transaction.
			 */
			अगर (uvc_ctrl_xctrls_has_control(xctrls, xctrls_count,
							slave_id))
				जारी;

			uvc_ctrl_send_slave_event(handle->chain, handle, ctrl,
						  slave_id);
		पूर्ण

		/*
		 * If the master is being modअगरied in the same transaction
		 * flags may change too.
		 */
		अगर (mapping->master_id &&
		    uvc_ctrl_xctrls_has_control(xctrls, xctrls_count,
						mapping->master_id))
			changes |= V4L2_EVENT_CTRL_CH_FLAGS;

		uvc_ctrl_send_event(handle->chain, handle, ctrl, mapping,
				    xctrls[i].value, changes);
	पूर्ण
पूर्ण

अटल पूर्णांक uvc_ctrl_add_event(काष्ठा v4l2_subscribed_event *sev, अचिन्हित elems)
अणु
	काष्ठा uvc_fh *handle = container_of(sev->fh, काष्ठा uvc_fh, vfh);
	काष्ठा uvc_control_mapping *mapping;
	काष्ठा uvc_control *ctrl;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&handle->chain->ctrl_mutex);
	अगर (ret < 0)
		वापस -ERESTARTSYS;

	ctrl = uvc_find_control(handle->chain, sev->id, &mapping);
	अगर (ctrl == शून्य) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	list_add_tail(&sev->node, &mapping->ev_subs);
	अगर (sev->flags & V4L2_EVENT_SUB_FL_SEND_INITIAL) अणु
		काष्ठा v4l2_event ev;
		u32 changes = V4L2_EVENT_CTRL_CH_FLAGS;
		s32 val = 0;

		अगर (__uvc_ctrl_get(handle->chain, ctrl, mapping, &val) == 0)
			changes |= V4L2_EVENT_CTRL_CH_VALUE;

		uvc_ctrl_fill_event(handle->chain, &ev, ctrl, mapping, val,
				    changes);
		/* Mark the queue as active, allowing this initial
		   event to be accepted. */
		sev->elems = elems;
		v4l2_event_queue_fh(sev->fh, &ev);
	पूर्ण

करोne:
	mutex_unlock(&handle->chain->ctrl_mutex);
	वापस ret;
पूर्ण

अटल व्योम uvc_ctrl_del_event(काष्ठा v4l2_subscribed_event *sev)
अणु
	काष्ठा uvc_fh *handle = container_of(sev->fh, काष्ठा uvc_fh, vfh);

	mutex_lock(&handle->chain->ctrl_mutex);
	list_del(&sev->node);
	mutex_unlock(&handle->chain->ctrl_mutex);
पूर्ण

स्थिर काष्ठा v4l2_subscribed_event_ops uvc_ctrl_sub_ev_ops = अणु
	.add = uvc_ctrl_add_event,
	.del = uvc_ctrl_del_event,
	.replace = v4l2_ctrl_replace,
	.merge = v4l2_ctrl_merge,
पूर्ण;

/* --------------------------------------------------------------------------
 * Control transactions
 *
 * To make extended set operations as atomic as the hardware allows, controls
 * are handled using begin/commit/rollback operations.
 *
 * At the beginning of a set request, uvc_ctrl_begin should be called to
 * initialize the request. This function acquires the control lock.
 *
 * When setting a control, the new value is stored in the control data field
 * at position UVC_CTRL_DATA_CURRENT. The control is then marked as dirty क्रम
 * later processing. If the UVC and V4L2 control sizes dअगरfer, the current
 * value is loaded from the hardware beक्रमe storing the new value in the data
 * field.
 *
 * After processing all controls in the transaction, uvc_ctrl_commit or
 * uvc_ctrl_rollback must be called to apply the pending changes to the
 * hardware or revert them. When applying changes, all controls marked as
 * dirty will be modअगरied in the UVC device, and the dirty flag will be
 * cleared. When reverting controls, the control data field
 * UVC_CTRL_DATA_CURRENT is reverted to its previous value
 * (UVC_CTRL_DATA_BACKUP) क्रम all dirty controls. Both functions release the
 * control lock.
 */
पूर्णांक uvc_ctrl_begin(काष्ठा uvc_video_chain *chain)
अणु
	वापस mutex_lock_पूर्णांकerruptible(&chain->ctrl_mutex) ? -ERESTARTSYS : 0;
पूर्ण

अटल पूर्णांक uvc_ctrl_commit_entity(काष्ठा uvc_device *dev,
	काष्ठा uvc_entity *entity, पूर्णांक rollback)
अणु
	काष्ठा uvc_control *ctrl;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (entity == शून्य)
		वापस 0;

	क्रम (i = 0; i < entity->ncontrols; ++i) अणु
		ctrl = &entity->controls[i];
		अगर (!ctrl->initialized)
			जारी;

		/* Reset the loaded flag क्रम स्वतः-update controls that were
		 * marked as loaded in uvc_ctrl_get/uvc_ctrl_set to prevent
		 * uvc_ctrl_get from using the cached value, and क्रम ग_लिखो-only
		 * controls to prevent uvc_ctrl_set from setting bits not
		 * explicitly set by the user.
		 */
		अगर (ctrl->info.flags & UVC_CTRL_FLAG_AUTO_UPDATE ||
		    !(ctrl->info.flags & UVC_CTRL_FLAG_GET_CUR))
			ctrl->loaded = 0;

		अगर (!ctrl->dirty)
			जारी;

		अगर (!rollback)
			ret = uvc_query_ctrl(dev, UVC_SET_CUR, ctrl->entity->id,
				dev->पूर्णांकfnum, ctrl->info.selector,
				uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT),
				ctrl->info.size);
		अन्यथा
			ret = 0;

		अगर (rollback || ret < 0)
			स_नकल(uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT),
			       uvc_ctrl_data(ctrl, UVC_CTRL_DATA_BACKUP),
			       ctrl->info.size);

		ctrl->dirty = 0;

		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __uvc_ctrl_commit(काष्ठा uvc_fh *handle, पूर्णांक rollback,
		      स्थिर काष्ठा v4l2_ext_control *xctrls,
		      अचिन्हित पूर्णांक xctrls_count)
अणु
	काष्ठा uvc_video_chain *chain = handle->chain;
	काष्ठा uvc_entity *entity;
	पूर्णांक ret = 0;

	/* Find the control. */
	list_क्रम_each_entry(entity, &chain->entities, chain) अणु
		ret = uvc_ctrl_commit_entity(chain->dev, entity, rollback);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	अगर (!rollback)
		uvc_ctrl_send_events(handle, xctrls, xctrls_count);
करोne:
	mutex_unlock(&chain->ctrl_mutex);
	वापस ret;
पूर्ण

पूर्णांक uvc_ctrl_get(काष्ठा uvc_video_chain *chain,
	काष्ठा v4l2_ext_control *xctrl)
अणु
	काष्ठा uvc_control *ctrl;
	काष्ठा uvc_control_mapping *mapping;

	ctrl = uvc_find_control(chain, xctrl->id, &mapping);
	अगर (ctrl == शून्य)
		वापस -EINVAL;

	वापस __uvc_ctrl_get(chain, ctrl, mapping, &xctrl->value);
पूर्ण

पूर्णांक uvc_ctrl_set(काष्ठा uvc_fh *handle,
	काष्ठा v4l2_ext_control *xctrl)
अणु
	काष्ठा uvc_video_chain *chain = handle->chain;
	काष्ठा uvc_control *ctrl;
	काष्ठा uvc_control_mapping *mapping;
	s32 value;
	u32 step;
	s32 min;
	s32 max;
	पूर्णांक ret;

	ctrl = uvc_find_control(chain, xctrl->id, &mapping);
	अगर (ctrl == शून्य)
		वापस -EINVAL;
	अगर (!(ctrl->info.flags & UVC_CTRL_FLAG_SET_CUR))
		वापस -EACCES;

	/* Clamp out of range values. */
	चयन (mapping->v4l2_type) अणु
	हाल V4L2_CTRL_TYPE_INTEGER:
		अगर (!ctrl->cached) अणु
			ret = uvc_ctrl_populate_cache(chain, ctrl);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		min = mapping->get(mapping, UVC_GET_MIN,
				   uvc_ctrl_data(ctrl, UVC_CTRL_DATA_MIN));
		max = mapping->get(mapping, UVC_GET_MAX,
				   uvc_ctrl_data(ctrl, UVC_CTRL_DATA_MAX));
		step = mapping->get(mapping, UVC_GET_RES,
				    uvc_ctrl_data(ctrl, UVC_CTRL_DATA_RES));
		अगर (step == 0)
			step = 1;

		xctrl->value = min + DIV_ROUND_CLOSEST((u32)(xctrl->value - min),
							step) * step;
		अगर (mapping->data_type == UVC_CTRL_DATA_TYPE_SIGNED)
			xctrl->value = clamp(xctrl->value, min, max);
		अन्यथा
			xctrl->value = clamp_t(u32, xctrl->value, min, max);
		value = xctrl->value;
		अवरोध;

	हाल V4L2_CTRL_TYPE_BOOLEAN:
		xctrl->value = clamp(xctrl->value, 0, 1);
		value = xctrl->value;
		अवरोध;

	हाल V4L2_CTRL_TYPE_MENU:
		अगर (xctrl->value < 0 || xctrl->value >= mapping->menu_count)
			वापस -दुस्फल;
		value = mapping->menu_info[xctrl->value].value;

		/* Valid menu indices are reported by the GET_RES request क्रम
		 * UVC controls that support it.
		 */
		अगर (mapping->data_type == UVC_CTRL_DATA_TYPE_BITMASK &&
		    (ctrl->info.flags & UVC_CTRL_FLAG_GET_RES)) अणु
			अगर (!ctrl->cached) अणु
				ret = uvc_ctrl_populate_cache(chain, ctrl);
				अगर (ret < 0)
					वापस ret;
			पूर्ण

			step = mapping->get(mapping, UVC_GET_RES,
					uvc_ctrl_data(ctrl, UVC_CTRL_DATA_RES));
			अगर (!(step & value))
				वापस -EINVAL;
		पूर्ण

		अवरोध;

	शेष:
		value = xctrl->value;
		अवरोध;
	पूर्ण

	/* If the mapping करोesn't span the whole UVC control, the current value
	 * needs to be loaded from the device to perक्रमm the पढ़ो-modअगरy-ग_लिखो
	 * operation.
	 */
	अगर (!ctrl->loaded && (ctrl->info.size * 8) != mapping->size) अणु
		अगर ((ctrl->info.flags & UVC_CTRL_FLAG_GET_CUR) == 0) अणु
			स_रखो(uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT),
				0, ctrl->info.size);
		पूर्ण अन्यथा अणु
			ret = uvc_query_ctrl(chain->dev, UVC_GET_CUR,
				ctrl->entity->id, chain->dev->पूर्णांकfnum,
				ctrl->info.selector,
				uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT),
				ctrl->info.size);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		ctrl->loaded = 1;
	पूर्ण

	/* Backup the current value in हाल we need to rollback later. */
	अगर (!ctrl->dirty) अणु
		स_नकल(uvc_ctrl_data(ctrl, UVC_CTRL_DATA_BACKUP),
		       uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT),
		       ctrl->info.size);
	पूर्ण

	mapping->set(mapping, value,
		uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT));

	अगर (ctrl->info.flags & UVC_CTRL_FLAG_ASYNCHRONOUS)
		ctrl->handle = handle;

	ctrl->dirty = 1;
	ctrl->modअगरied = 1;
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------------
 * Dynamic controls
 */

/*
 * Retrieve flags क्रम a given control
 */
अटल पूर्णांक uvc_ctrl_get_flags(काष्ठा uvc_device *dev,
			      स्थिर काष्ठा uvc_control *ctrl,
			      काष्ठा uvc_control_info *info)
अणु
	u8 *data;
	पूर्णांक ret;

	data = kदो_स्मृति(1, GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	अगर (ctrl->entity->get_info)
		ret = ctrl->entity->get_info(dev, ctrl->entity,
					     ctrl->info.selector, data);
	अन्यथा
		ret = uvc_query_ctrl(dev, UVC_GET_INFO, ctrl->entity->id,
				     dev->पूर्णांकfnum, info->selector, data, 1);
	अगर (!ret)
		info->flags |= (data[0] & UVC_CONTROL_CAP_GET ?
				UVC_CTRL_FLAG_GET_CUR : 0)
			    |  (data[0] & UVC_CONTROL_CAP_SET ?
				UVC_CTRL_FLAG_SET_CUR : 0)
			    |  (data[0] & UVC_CONTROL_CAP_AUTOUPDATE ?
				UVC_CTRL_FLAG_AUTO_UPDATE : 0)
			    |  (data[0] & UVC_CONTROL_CAP_ASYNCHRONOUS ?
				UVC_CTRL_FLAG_ASYNCHRONOUS : 0);

	kमुक्त(data);
	वापस ret;
पूर्ण

अटल व्योम uvc_ctrl_fixup_xu_info(काष्ठा uvc_device *dev,
	स्थिर काष्ठा uvc_control *ctrl, काष्ठा uvc_control_info *info)
अणु
	काष्ठा uvc_ctrl_fixup अणु
		काष्ठा usb_device_id id;
		u8 entity;
		u8 selector;
		u8 flags;
	पूर्ण;

	अटल स्थिर काष्ठा uvc_ctrl_fixup fixups[] = अणु
		अणु अणु USB_DEVICE(0x046d, 0x08c2) पूर्ण, 9, 1,
			UVC_CTRL_FLAG_GET_MIN | UVC_CTRL_FLAG_GET_MAX |
			UVC_CTRL_FLAG_GET_DEF | UVC_CTRL_FLAG_SET_CUR |
			UVC_CTRL_FLAG_AUTO_UPDATE पूर्ण,
		अणु अणु USB_DEVICE(0x046d, 0x08cc) पूर्ण, 9, 1,
			UVC_CTRL_FLAG_GET_MIN | UVC_CTRL_FLAG_GET_MAX |
			UVC_CTRL_FLAG_GET_DEF | UVC_CTRL_FLAG_SET_CUR |
			UVC_CTRL_FLAG_AUTO_UPDATE पूर्ण,
		अणु अणु USB_DEVICE(0x046d, 0x0994) पूर्ण, 9, 1,
			UVC_CTRL_FLAG_GET_MIN | UVC_CTRL_FLAG_GET_MAX |
			UVC_CTRL_FLAG_GET_DEF | UVC_CTRL_FLAG_SET_CUR |
			UVC_CTRL_FLAG_AUTO_UPDATE पूर्ण,
	पूर्ण;

	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fixups); ++i) अणु
		अगर (!usb_match_one_id(dev->पूर्णांकf, &fixups[i].id))
			जारी;

		अगर (fixups[i].entity == ctrl->entity->id &&
		    fixups[i].selector == info->selector) अणु
			info->flags = fixups[i].flags;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Query control inक्रमmation (size and flags) क्रम XU controls.
 */
अटल पूर्णांक uvc_ctrl_fill_xu_info(काष्ठा uvc_device *dev,
	स्थिर काष्ठा uvc_control *ctrl, काष्ठा uvc_control_info *info)
अणु
	u8 *data;
	पूर्णांक ret;

	data = kदो_स्मृति(2, GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	स_नकल(info->entity, ctrl->entity->guid, माप(info->entity));
	info->index = ctrl->index;
	info->selector = ctrl->index + 1;

	/* Query and verअगरy the control length (GET_LEN) */
	ret = uvc_query_ctrl(dev, UVC_GET_LEN, ctrl->entity->id, dev->पूर्णांकfnum,
			     info->selector, data, 2);
	अगर (ret < 0) अणु
		uvc_dbg(dev, CONTROL,
			"GET_LEN failed on control %pUl/%u (%d)\n",
			info->entity, info->selector, ret);
		जाओ करोne;
	पूर्ण

	info->size = le16_to_cpup((__le16 *)data);

	info->flags = UVC_CTRL_FLAG_GET_MIN | UVC_CTRL_FLAG_GET_MAX
		    | UVC_CTRL_FLAG_GET_RES | UVC_CTRL_FLAG_GET_DEF;

	ret = uvc_ctrl_get_flags(dev, ctrl, info);
	अगर (ret < 0) अणु
		uvc_dbg(dev, CONTROL,
			"Failed to get flags for control %pUl/%u (%d)\n",
			info->entity, info->selector, ret);
		जाओ करोne;
	पूर्ण

	uvc_ctrl_fixup_xu_info(dev, ctrl, info);

	uvc_dbg(dev, CONTROL,
		"XU control %pUl/%u queried: len %u, flags { get %u set %u auto %u }\n",
		info->entity, info->selector, info->size,
		(info->flags & UVC_CTRL_FLAG_GET_CUR) ? 1 : 0,
		(info->flags & UVC_CTRL_FLAG_SET_CUR) ? 1 : 0,
		(info->flags & UVC_CTRL_FLAG_AUTO_UPDATE) ? 1 : 0);

करोne:
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक uvc_ctrl_add_info(काष्ठा uvc_device *dev, काष्ठा uvc_control *ctrl,
	स्थिर काष्ठा uvc_control_info *info);

अटल पूर्णांक uvc_ctrl_init_xu_ctrl(काष्ठा uvc_device *dev,
	काष्ठा uvc_control *ctrl)
अणु
	काष्ठा uvc_control_info info;
	पूर्णांक ret;

	अगर (ctrl->initialized)
		वापस 0;

	ret = uvc_ctrl_fill_xu_info(dev, ctrl, &info);
	अगर (ret < 0)
		वापस ret;

	ret = uvc_ctrl_add_info(dev, ctrl, &info);
	अगर (ret < 0)
		uvc_dbg(dev, CONTROL,
			"Failed to initialize control %pUl/%u on device %s entity %u\n",
			info.entity, info.selector, dev->udev->devpath,
			ctrl->entity->id);

	वापस ret;
पूर्ण

पूर्णांक uvc_xu_ctrl_query(काष्ठा uvc_video_chain *chain,
	काष्ठा uvc_xu_control_query *xqry)
अणु
	काष्ठा uvc_entity *entity;
	काष्ठा uvc_control *ctrl;
	अचिन्हित पूर्णांक i;
	bool found;
	u32 reqflags;
	u16 size;
	u8 *data = शून्य;
	पूर्णांक ret;

	/* Find the extension unit. */
	found = false;
	list_क्रम_each_entry(entity, &chain->entities, chain) अणु
		अगर (UVC_ENTITY_TYPE(entity) == UVC_VC_EXTENSION_UNIT &&
		    entity->id == xqry->unit) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		uvc_dbg(chain->dev, CONTROL, "Extension unit %u not found\n",
			xqry->unit);
		वापस -ENOENT;
	पूर्ण

	/* Find the control and perक्रमm delayed initialization अगर needed. */
	found = false;
	क्रम (i = 0; i < entity->ncontrols; ++i) अणु
		ctrl = &entity->controls[i];
		अगर (ctrl->index == xqry->selector - 1) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		uvc_dbg(chain->dev, CONTROL, "Control %pUl/%u not found\n",
			entity->guid, xqry->selector);
		वापस -ENOENT;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&chain->ctrl_mutex))
		वापस -ERESTARTSYS;

	ret = uvc_ctrl_init_xu_ctrl(chain->dev, ctrl);
	अगर (ret < 0) अणु
		ret = -ENOENT;
		जाओ करोne;
	पूर्ण

	/* Validate the required buffer size and flags क्रम the request */
	reqflags = 0;
	size = ctrl->info.size;

	चयन (xqry->query) अणु
	हाल UVC_GET_CUR:
		reqflags = UVC_CTRL_FLAG_GET_CUR;
		अवरोध;
	हाल UVC_GET_MIN:
		reqflags = UVC_CTRL_FLAG_GET_MIN;
		अवरोध;
	हाल UVC_GET_MAX:
		reqflags = UVC_CTRL_FLAG_GET_MAX;
		अवरोध;
	हाल UVC_GET_DEF:
		reqflags = UVC_CTRL_FLAG_GET_DEF;
		अवरोध;
	हाल UVC_GET_RES:
		reqflags = UVC_CTRL_FLAG_GET_RES;
		अवरोध;
	हाल UVC_SET_CUR:
		reqflags = UVC_CTRL_FLAG_SET_CUR;
		अवरोध;
	हाल UVC_GET_LEN:
		size = 2;
		अवरोध;
	हाल UVC_GET_INFO:
		size = 1;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (size != xqry->size) अणु
		ret = -ENOBUFS;
		जाओ करोne;
	पूर्ण

	अगर (reqflags && !(ctrl->info.flags & reqflags)) अणु
		ret = -EBADRQC;
		जाओ करोne;
	पूर्ण

	data = kदो_स्मृति(size, GFP_KERNEL);
	अगर (data == शून्य) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	अगर (xqry->query == UVC_SET_CUR &&
	    copy_from_user(data, xqry->data, size)) अणु
		ret = -EFAULT;
		जाओ करोne;
	पूर्ण

	ret = uvc_query_ctrl(chain->dev, xqry->query, xqry->unit,
			     chain->dev->पूर्णांकfnum, xqry->selector, data, size);
	अगर (ret < 0)
		जाओ करोne;

	अगर (xqry->query != UVC_SET_CUR &&
	    copy_to_user(xqry->data, data, size))
		ret = -EFAULT;
करोne:
	kमुक्त(data);
	mutex_unlock(&chain->ctrl_mutex);
	वापस ret;
पूर्ण

/* --------------------------------------------------------------------------
 * Suspend/resume
 */

/*
 * Restore control values after resume, skipping controls that haven't been
 * changed.
 *
 * TODO
 * - Don't restore modअगरied controls that are back to their शेष value.
 * - Handle restore order (Auto-Exposure Mode should be restored beक्रमe
 *   Exposure Time).
 */
पूर्णांक uvc_ctrl_restore_values(काष्ठा uvc_device *dev)
अणु
	काष्ठा uvc_control *ctrl;
	काष्ठा uvc_entity *entity;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Walk the entities list and restore controls when possible. */
	list_क्रम_each_entry(entity, &dev->entities, list) अणु

		क्रम (i = 0; i < entity->ncontrols; ++i) अणु
			ctrl = &entity->controls[i];

			अगर (!ctrl->initialized || !ctrl->modअगरied ||
			    (ctrl->info.flags & UVC_CTRL_FLAG_RESTORE) == 0)
				जारी;
			dev_info(&dev->udev->dev,
				 "restoring control %pUl/%u/%u\n",
				 ctrl->info.entity, ctrl->info.index,
				 ctrl->info.selector);
			ctrl->dirty = 1;
		पूर्ण

		ret = uvc_ctrl_commit_entity(dev, entity, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* --------------------------------------------------------------------------
 * Control and mapping handling
 */

/*
 * Add control inक्रमmation to a given control.
 */
अटल पूर्णांक uvc_ctrl_add_info(काष्ठा uvc_device *dev, काष्ठा uvc_control *ctrl,
	स्थिर काष्ठा uvc_control_info *info)
अणु
	ctrl->info = *info;
	INIT_LIST_HEAD(&ctrl->info.mappings);

	/* Allocate an array to save control values (cur, def, max, etc.) */
	ctrl->uvc_data = kzalloc(ctrl->info.size * UVC_CTRL_DATA_LAST + 1,
				 GFP_KERNEL);
	अगर (!ctrl->uvc_data)
		वापस -ENOMEM;

	ctrl->initialized = 1;

	uvc_dbg(dev, CONTROL, "Added control %pUl/%u to device %s entity %u\n",
		ctrl->info.entity, ctrl->info.selector, dev->udev->devpath,
		ctrl->entity->id);

	वापस 0;
पूर्ण

/*
 * Add a control mapping to a given control.
 */
अटल पूर्णांक __uvc_ctrl_add_mapping(काष्ठा uvc_device *dev,
	काष्ठा uvc_control *ctrl, स्थिर काष्ठा uvc_control_mapping *mapping)
अणु
	काष्ठा uvc_control_mapping *map;
	अचिन्हित पूर्णांक size;

	/* Most mappings come from अटल kernel data and need to be duplicated.
	 * Mappings that come from userspace will be unnecessarily duplicated,
	 * this could be optimized.
	 */
	map = kmemdup(mapping, माप(*mapping), GFP_KERNEL);
	अगर (map == शून्य)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&map->ev_subs);

	size = माप(*mapping->menu_info) * mapping->menu_count;
	map->menu_info = kmemdup(mapping->menu_info, size, GFP_KERNEL);
	अगर (map->menu_info == शून्य) अणु
		kमुक्त(map);
		वापस -ENOMEM;
	पूर्ण

	अगर (map->get == शून्य)
		map->get = uvc_get_le_value;
	अगर (map->set == शून्य)
		map->set = uvc_set_le_value;

	list_add_tail(&map->list, &ctrl->info.mappings);
	uvc_dbg(dev, CONTROL, "Adding mapping '%s' to control %pUl/%u\n",
		map->name, ctrl->info.entity, ctrl->info.selector);

	वापस 0;
पूर्ण

पूर्णांक uvc_ctrl_add_mapping(काष्ठा uvc_video_chain *chain,
	स्थिर काष्ठा uvc_control_mapping *mapping)
अणु
	काष्ठा uvc_device *dev = chain->dev;
	काष्ठा uvc_control_mapping *map;
	काष्ठा uvc_entity *entity;
	काष्ठा uvc_control *ctrl;
	पूर्णांक found = 0;
	पूर्णांक ret;

	अगर (mapping->id & ~V4L2_CTRL_ID_MASK) अणु
		uvc_dbg(dev, CONTROL,
			"Can't add mapping '%s', control id 0x%08x is invalid\n",
			mapping->name, mapping->id);
		वापस -EINVAL;
	पूर्ण

	/* Search क्रम the matching (GUID/CS) control on the current chain */
	list_क्रम_each_entry(entity, &chain->entities, chain) अणु
		अचिन्हित पूर्णांक i;

		अगर (UVC_ENTITY_TYPE(entity) != UVC_VC_EXTENSION_UNIT ||
		    !uvc_entity_match_guid(entity, mapping->entity))
			जारी;

		क्रम (i = 0; i < entity->ncontrols; ++i) अणु
			ctrl = &entity->controls[i];
			अगर (ctrl->index == mapping->selector - 1) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (found)
			अवरोध;
	पूर्ण
	अगर (!found)
		वापस -ENOENT;

	अगर (mutex_lock_पूर्णांकerruptible(&chain->ctrl_mutex))
		वापस -ERESTARTSYS;

	/* Perक्रमm delayed initialization of XU controls */
	ret = uvc_ctrl_init_xu_ctrl(dev, ctrl);
	अगर (ret < 0) अणु
		ret = -ENOENT;
		जाओ करोne;
	पूर्ण

	/* Validate the user-provided bit-size and offset */
	अगर (mapping->size > 32 ||
	    mapping->offset + mapping->size > ctrl->info.size * 8) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	list_क्रम_each_entry(map, &ctrl->info.mappings, list) अणु
		अगर (mapping->id == map->id) अणु
			uvc_dbg(dev, CONTROL,
				"Can't add mapping '%s', control id 0x%08x already exists\n",
				mapping->name, mapping->id);
			ret = -EEXIST;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* Prevent excess memory consumption */
	अगर (atomic_inc_वापस(&dev->nmappings) > UVC_MAX_CONTROL_MAPPINGS) अणु
		atomic_dec(&dev->nmappings);
		uvc_dbg(dev, CONTROL,
			"Can't add mapping '%s', maximum mappings count (%u) exceeded\n",
			mapping->name, UVC_MAX_CONTROL_MAPPINGS);
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	ret = __uvc_ctrl_add_mapping(dev, ctrl, mapping);
	अगर (ret < 0)
		atomic_dec(&dev->nmappings);

करोne:
	mutex_unlock(&chain->ctrl_mutex);
	वापस ret;
पूर्ण

/*
 * Prune an entity of its bogus controls using a blacklist. Bogus controls
 * are currently the ones that crash the camera or unconditionally वापस an
 * error when queried.
 */
अटल व्योम uvc_ctrl_prune_entity(काष्ठा uvc_device *dev,
	काष्ठा uvc_entity *entity)
अणु
	काष्ठा uvc_ctrl_blacklist अणु
		काष्ठा usb_device_id id;
		u8 index;
	पूर्ण;

	अटल स्थिर काष्ठा uvc_ctrl_blacklist processing_blacklist[] = अणु
		अणु अणु USB_DEVICE(0x13d3, 0x509b) पूर्ण, 9 पूर्ण, /* Gain */
		अणु अणु USB_DEVICE(0x1c4f, 0x3000) पूर्ण, 6 पूर्ण, /* WB Temperature */
		अणु अणु USB_DEVICE(0x5986, 0x0241) पूर्ण, 2 पूर्ण, /* Hue */
	पूर्ण;
	अटल स्थिर काष्ठा uvc_ctrl_blacklist camera_blacklist[] = अणु
		अणु अणु USB_DEVICE(0x06f8, 0x3005) पूर्ण, 9 पूर्ण, /* Zoom, Absolute */
	पूर्ण;

	स्थिर काष्ठा uvc_ctrl_blacklist *blacklist;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक i;
	u8 *controls;

	चयन (UVC_ENTITY_TYPE(entity)) अणु
	हाल UVC_VC_PROCESSING_UNIT:
		blacklist = processing_blacklist;
		count = ARRAY_SIZE(processing_blacklist);
		controls = entity->processing.bmControls;
		size = entity->processing.bControlSize;
		अवरोध;

	हाल UVC_ITT_CAMERA:
		blacklist = camera_blacklist;
		count = ARRAY_SIZE(camera_blacklist);
		controls = entity->camera.bmControls;
		size = entity->camera.bControlSize;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	क्रम (i = 0; i < count; ++i) अणु
		अगर (!usb_match_one_id(dev->पूर्णांकf, &blacklist[i].id))
			जारी;

		अगर (blacklist[i].index >= 8 * size ||
		    !uvc_test_bit(controls, blacklist[i].index))
			जारी;

		uvc_dbg(dev, CONTROL,
			"%u/%u control is black listed, removing it\n",
			entity->id, blacklist[i].index);

		uvc_clear_bit(controls, blacklist[i].index);
	पूर्ण
पूर्ण

/*
 * Add control inक्रमmation and hardcoded stock control mappings to the given
 * device.
 */
अटल व्योम uvc_ctrl_init_ctrl(काष्ठा uvc_device *dev, काष्ठा uvc_control *ctrl)
अणु
	स्थिर काष्ठा uvc_control_info *info = uvc_ctrls;
	स्थिर काष्ठा uvc_control_info *iend = info + ARRAY_SIZE(uvc_ctrls);
	स्थिर काष्ठा uvc_control_mapping *mapping = uvc_ctrl_mappings;
	स्थिर काष्ठा uvc_control_mapping *mend =
		mapping + ARRAY_SIZE(uvc_ctrl_mappings);

	/* XU controls initialization requires querying the device क्रम control
	 * inक्रमmation. As some buggy UVC devices will crash when queried
	 * repeatedly in a tight loop, delay XU controls initialization until
	 * first use.
	 */
	अगर (UVC_ENTITY_TYPE(ctrl->entity) == UVC_VC_EXTENSION_UNIT)
		वापस;

	क्रम (; info < iend; ++info) अणु
		अगर (uvc_entity_match_guid(ctrl->entity, info->entity) &&
		    ctrl->index == info->index) अणु
			uvc_ctrl_add_info(dev, ctrl, info);
			/*
			 * Retrieve control flags from the device. Ignore errors
			 * and work with शेष flag values from the uvc_ctrl
			 * array when the device करोesn't properly implement
			 * GET_INFO on standard controls.
			 */
			uvc_ctrl_get_flags(dev, ctrl, &ctrl->info);
			अवरोध;
		 पूर्ण
	पूर्ण

	अगर (!ctrl->initialized)
		वापस;

	क्रम (; mapping < mend; ++mapping) अणु
		अगर (uvc_entity_match_guid(ctrl->entity, mapping->entity) &&
		    ctrl->info.selector == mapping->selector)
			__uvc_ctrl_add_mapping(dev, ctrl, mapping);
	पूर्ण
पूर्ण

/*
 * Initialize device controls.
 */
पूर्णांक uvc_ctrl_init_device(काष्ठा uvc_device *dev)
अणु
	काष्ठा uvc_entity *entity;
	अचिन्हित पूर्णांक i;

	INIT_WORK(&dev->async_ctrl.work, uvc_ctrl_status_event_work);

	/* Walk the entities list and instantiate controls */
	list_क्रम_each_entry(entity, &dev->entities, list) अणु
		काष्ठा uvc_control *ctrl;
		अचिन्हित पूर्णांक bControlSize = 0, ncontrols;
		u8 *bmControls = शून्य;

		अगर (UVC_ENTITY_TYPE(entity) == UVC_VC_EXTENSION_UNIT) अणु
			bmControls = entity->extension.bmControls;
			bControlSize = entity->extension.bControlSize;
		पूर्ण अन्यथा अगर (UVC_ENTITY_TYPE(entity) == UVC_VC_PROCESSING_UNIT) अणु
			bmControls = entity->processing.bmControls;
			bControlSize = entity->processing.bControlSize;
		पूर्ण अन्यथा अगर (UVC_ENTITY_TYPE(entity) == UVC_ITT_CAMERA) अणु
			bmControls = entity->camera.bmControls;
			bControlSize = entity->camera.bControlSize;
		पूर्ण अन्यथा अगर (UVC_ENTITY_TYPE(entity) == UVC_EXT_GPIO_UNIT) अणु
			bmControls = entity->gpio.bmControls;
			bControlSize = entity->gpio.bControlSize;
		पूर्ण

		/* Remove bogus/blacklisted controls */
		uvc_ctrl_prune_entity(dev, entity);

		/* Count supported controls and allocate the controls array */
		ncontrols = memweight(bmControls, bControlSize);
		अगर (ncontrols == 0)
			जारी;

		entity->controls = kसुस्मृति(ncontrols, माप(*ctrl),
					   GFP_KERNEL);
		अगर (entity->controls == शून्य)
			वापस -ENOMEM;
		entity->ncontrols = ncontrols;

		/* Initialize all supported controls */
		ctrl = entity->controls;
		क्रम (i = 0; i < bControlSize * 8; ++i) अणु
			अगर (uvc_test_bit(bmControls, i) == 0)
				जारी;

			ctrl->entity = entity;
			ctrl->index = i;

			uvc_ctrl_init_ctrl(dev, ctrl);
			ctrl++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Cleanup device controls.
 */
अटल व्योम uvc_ctrl_cleanup_mappings(काष्ठा uvc_device *dev,
	काष्ठा uvc_control *ctrl)
अणु
	काष्ठा uvc_control_mapping *mapping, *nm;

	list_क्रम_each_entry_safe(mapping, nm, &ctrl->info.mappings, list) अणु
		list_del(&mapping->list);
		kमुक्त(mapping->menu_info);
		kमुक्त(mapping);
	पूर्ण
पूर्ण

व्योम uvc_ctrl_cleanup_device(काष्ठा uvc_device *dev)
अणु
	काष्ठा uvc_entity *entity;
	अचिन्हित पूर्णांक i;

	/* Can be uninitialized अगर we are पातing on probe error. */
	अगर (dev->async_ctrl.work.func)
		cancel_work_sync(&dev->async_ctrl.work);

	/* Free controls and control mappings क्रम all entities. */
	list_क्रम_each_entry(entity, &dev->entities, list) अणु
		क्रम (i = 0; i < entity->ncontrols; ++i) अणु
			काष्ठा uvc_control *ctrl = &entity->controls[i];

			अगर (!ctrl->initialized)
				जारी;

			uvc_ctrl_cleanup_mappings(dev, ctrl);
			kमुक्त(ctrl->uvc_data);
		पूर्ण

		kमुक्त(entity->controls);
	पूर्ण
पूर्ण
