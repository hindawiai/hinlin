<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * Copyright (c) 2010 Silicon Hive www.siliconhive.com.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>

#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf-vदो_स्मृति.h>

#समावेश "atomisp_acc.h"
#समावेश "atomisp_cmd.h"
#समावेश "atomisp_common.h"
#समावेश "atomisp_fops.h"
#समावेश "atomisp_internal.h"
#समावेश "atomisp_ioctl.h"
#समावेश "atomisp-regs.h"
#समावेश "atomisp_compat.h"

#समावेश "sh_css_hrt.h"

#समावेश "gp_device.h"
#समावेश "device_access.h"
#समावेश "irq.h"

अटल स्थिर अक्षर *DRIVER = "atomisp";	/* max size 15 */
अटल स्थिर अक्षर *CARD = "ATOM ISP";	/* max size 31 */

/*
 * FIXME: ISP should not know beक्रमehand all CIDs supported by sensor.
 * Instead, it needs to propagate to sensor unkonwn CIDs.
 */
अटल काष्ठा v4l2_queryctrl ci_v4l2_controls[] = अणु
	अणु
		.id = V4L2_CID_AUTO_WHITE_BALANCE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Automatic White Balance",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_RED_BALANCE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Red Balance",
		.minimum = 0x00,
		.maximum = 0xff,
		.step = 1,
		.शेष_value = 0x00,
	पूर्ण,
	अणु
		.id = V4L2_CID_BLUE_BALANCE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Blue Balance",
		.minimum = 0x00,
		.maximum = 0xff,
		.step = 1,
		.शेष_value = 0x00,
	पूर्ण,
	अणु
		.id = V4L2_CID_GAMMA,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Gamma",
		.minimum = 0x00,
		.maximum = 0xff,
		.step = 1,
		.शेष_value = 0x00,
	पूर्ण,
	अणु
		.id = V4L2_CID_POWER_LINE_FREQUENCY,
		.type = V4L2_CTRL_TYPE_MENU,
		.name = "Light frequency filter",
		.minimum = 1,
		.maximum = 2,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_COLORFX,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Image Color Effect",
		.minimum = 0,
		.maximum = 9,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_COLORFX_CBCR,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Image Color Effect CbCr",
		.minimum = 0,
		.maximum = 0xffff,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_ATOMISP_BAD_PIXEL_DETECTION,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Bad Pixel Correction",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_ATOMISP_POSTPROCESS_GDC_CAC,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "GDC/CAC",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_ATOMISP_VIDEO_STABLIZATION,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Video Stablization",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_ATOMISP_FIXED_PATTERN_NR,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Fixed Pattern Noise Reduction",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_ATOMISP_FALSE_COLOR_CORRECTION,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "False Color Correction",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_REQUEST_FLASH,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Request flash frames",
		.minimum = 0,
		.maximum = 10,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_ATOMISP_LOW_LIGHT,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Low light mode",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_BIN_FACTOR_HORZ,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Horizontal binning factor",
		.minimum = 0,
		.maximum = 10,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_BIN_FACTOR_VERT,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Vertical binning factor",
		.minimum = 0,
		.maximum = 10,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_2A_STATUS,
		.type = V4L2_CTRL_TYPE_BITMASK,
		.name = "AE and AWB status",
		.minimum = 0,
		.maximum = V4L2_2A_STATUS_AE_READY | V4L2_2A_STATUS_AWB_READY,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_EXPOSURE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "exposure",
		.minimum = -4,
		.maximum = 4,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_EXPOSURE_ZONE_NUM,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "one-time exposure zone number",
		.minimum = 0x0,
		.maximum = 0xffff,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_EXPOSURE_AUTO_PRIORITY,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Exposure auto priority",
		.minimum = V4L2_EXPOSURE_AUTO,
		.maximum = V4L2_EXPOSURE_APERTURE_PRIORITY,
		.step = 1,
		.शेष_value = V4L2_EXPOSURE_AUTO,
	पूर्ण,
	अणु
		.id = V4L2_CID_SCENE_MODE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "scene mode",
		.minimum = 0,
		.maximum = 13,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_ISO_SENSITIVITY,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "iso",
		.minimum = -4,
		.maximum = 4,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_ISO_SENSITIVITY_AUTO,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "iso mode",
		.minimum = V4L2_ISO_SENSITIVITY_MANUAL,
		.maximum = V4L2_ISO_SENSITIVITY_AUTO,
		.step = 1,
		.शेष_value = V4L2_ISO_SENSITIVITY_AUTO,
	पूर्ण,
	अणु
		.id = V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "white balance",
		.minimum = 0,
		.maximum = 9,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_EXPOSURE_METERING,
		.type = V4L2_CTRL_TYPE_MENU,
		.name = "metering",
		.minimum = 0,
		.maximum = 3,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_3A_LOCK,
		.type = V4L2_CTRL_TYPE_BITMASK,
		.name = "3a lock",
		.minimum = 0,
		.maximum = V4L2_LOCK_EXPOSURE | V4L2_LOCK_WHITE_BALANCE
		| V4L2_LOCK_FOCUS,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_TEST_PATTERN,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Test Pattern",
		.minimum = 0,
		.maximum = 0xffff,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_TEST_PATTERN_COLOR_R,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Test Pattern Solid Color R",
		.minimum = पूर्णांक_न्यून,
		.maximum = पूर्णांक_उच्च,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_TEST_PATTERN_COLOR_GR,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Test Pattern Solid Color GR",
		.minimum = पूर्णांक_न्यून,
		.maximum = पूर्णांक_उच्च,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_TEST_PATTERN_COLOR_GB,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Test Pattern Solid Color GB",
		.minimum = पूर्णांक_न्यून,
		.maximum = पूर्णांक_उच्च,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_TEST_PATTERN_COLOR_B,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Test Pattern Solid Color B",
		.minimum = पूर्णांक_न्यून,
		.maximum = पूर्णांक_उच्च,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर u32 ctrls_num = ARRAY_SIZE(ci_v4l2_controls);

/*
 * supported V4L2 fmts and resolutions
 */
स्थिर काष्ठा atomisp_क्रमmat_bridge atomisp_output_fmts[] = अणु
	अणु
		.pixelक्रमmat = V4L2_PIX_FMT_YUV420,
		.depth = 12,
		.mbus_code = V4L2_MBUS_FMT_CUSTOM_YUV420,
		.sh_fmt = IA_CSS_FRAME_FORMAT_YUV420,
		.description = "YUV420, planar",
		.planar = true
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_YVU420,
		.depth = 12,
		.mbus_code = V4L2_MBUS_FMT_CUSTOM_YVU420,
		.sh_fmt = IA_CSS_FRAME_FORMAT_YV12,
		.description = "YVU420, planar",
		.planar = true
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_YUV422P,
		.depth = 16,
		.mbus_code = V4L2_MBUS_FMT_CUSTOM_YUV422P,
		.sh_fmt = IA_CSS_FRAME_FORMAT_YUV422,
		.description = "YUV422, planar",
		.planar = true
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_YUV444,
		.depth = 24,
		.mbus_code = V4L2_MBUS_FMT_CUSTOM_YUV444,
		.sh_fmt = IA_CSS_FRAME_FORMAT_YUV444,
		.description = "YUV444"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_NV12,
		.depth = 12,
		.mbus_code = V4L2_MBUS_FMT_CUSTOM_NV12,
		.sh_fmt = IA_CSS_FRAME_FORMAT_NV12,
		.description = "NV12, Y-plane, CbCr interleaved",
		.planar = true
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_NV21,
		.depth = 12,
		.mbus_code = V4L2_MBUS_FMT_CUSTOM_NV21,
		.sh_fmt = IA_CSS_FRAME_FORMAT_NV21,
		.description = "NV21, Y-plane, CbCr interleaved",
		.planar = true
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_NV16,
		.depth = 16,
		.mbus_code = V4L2_MBUS_FMT_CUSTOM_NV16,
		.sh_fmt = IA_CSS_FRAME_FORMAT_NV16,
		.description = "NV16, Y-plane, CbCr interleaved",
		.planar = true
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_YUYV,
		.depth = 16,
		.mbus_code = V4L2_MBUS_FMT_CUSTOM_YUYV,
		.sh_fmt = IA_CSS_FRAME_FORMAT_YUYV,
		.description = "YUYV, interleaved"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_UYVY,
		.depth = 16,
		.mbus_code = MEDIA_BUS_FMT_UYVY8_1X16,
		.sh_fmt = IA_CSS_FRAME_FORMAT_UYVY,
		.description = "UYVY, interleaved"
	पूर्ण, अणु /* This one is क्रम parallel sensors! DO NOT USE! */
		.pixelक्रमmat = V4L2_PIX_FMT_UYVY,
		.depth = 16,
		.mbus_code = MEDIA_BUS_FMT_UYVY8_2X8,
		.sh_fmt = IA_CSS_FRAME_FORMAT_UYVY,
		.description = "UYVY, interleaved"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SBGGR16,
		.depth = 16,
		.mbus_code = V4L2_MBUS_FMT_CUSTOM_SBGGR16,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RAW,
		.description = "Bayer 16"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SBGGR8,
		.depth = 8,
		.mbus_code = MEDIA_BUS_FMT_SBGGR8_1X8,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RAW,
		.description = "Bayer 8"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SGBRG8,
		.depth = 8,
		.mbus_code = MEDIA_BUS_FMT_SGBRG8_1X8,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RAW,
		.description = "Bayer 8"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SGRBG8,
		.depth = 8,
		.mbus_code = MEDIA_BUS_FMT_SGRBG8_1X8,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RAW,
		.description = "Bayer 8"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SRGGB8,
		.depth = 8,
		.mbus_code = MEDIA_BUS_FMT_SRGGB8_1X8,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RAW,
		.description = "Bayer 8"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SBGGR10,
		.depth = 16,
		.mbus_code = MEDIA_BUS_FMT_SBGGR10_1X10,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RAW,
		.description = "Bayer 10"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SGBRG10,
		.depth = 16,
		.mbus_code = MEDIA_BUS_FMT_SGBRG10_1X10,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RAW,
		.description = "Bayer 10"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SGRBG10,
		.depth = 16,
		.mbus_code = MEDIA_BUS_FMT_SGRBG10_1X10,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RAW,
		.description = "Bayer 10"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SRGGB10,
		.depth = 16,
		.mbus_code = MEDIA_BUS_FMT_SRGGB10_1X10,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RAW,
		.description = "Bayer 10"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SBGGR12,
		.depth = 16,
		.mbus_code = MEDIA_BUS_FMT_SBGGR12_1X12,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RAW,
		.description = "Bayer 12"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SGBRG12,
		.depth = 16,
		.mbus_code = MEDIA_BUS_FMT_SGBRG12_1X12,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RAW,
		.description = "Bayer 12"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SGRBG12,
		.depth = 16,
		.mbus_code = MEDIA_BUS_FMT_SGRBG12_1X12,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RAW,
		.description = "Bayer 12"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SRGGB12,
		.depth = 16,
		.mbus_code = MEDIA_BUS_FMT_SRGGB12_1X12,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RAW,
		.description = "Bayer 12"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_RGB32,
		.depth = 32,
		.mbus_code = V4L2_MBUS_FMT_CUSTOM_RGB32,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RGBA888,
		.description = "32 RGB 8-8-8-8"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_RGB565,
		.depth = 16,
		.mbus_code = MEDIA_BUS_FMT_BGR565_2X8_LE,
		.sh_fmt = IA_CSS_FRAME_FORMAT_RGB565,
		.description = "16 RGB 5-6-5"
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_JPEG,
		.depth = 8,
		.mbus_code = MEDIA_BUS_FMT_JPEG_1X8,
		.sh_fmt = IA_CSS_FRAME_FORMAT_BINARY_8,
		.description = "JPEG"
	पूर्ण,
#अगर 0
	अणु
		/* This is a custom क्रमmat being used by M10MO to send the RAW data */
		.pixelक्रमmat = V4L2_PIX_FMT_CUSTOM_M10MO_RAW,
		.depth = 8,
		.mbus_code = V4L2_MBUS_FMT_CUSTOM_M10MO_RAW,
		.sh_fmt = IA_CSS_FRAME_FORMAT_BINARY_8,
		.description = "Custom RAW for M10MO"
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

स्थिर काष्ठा atomisp_क्रमmat_bridge *
atomisp_get_क्रमmat_bridge(अचिन्हित पूर्णांक pixelक्रमmat)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(atomisp_output_fmts); i++) अणु
		अगर (atomisp_output_fmts[i].pixelक्रमmat == pixelक्रमmat)
			वापस &atomisp_output_fmts[i];
	पूर्ण

	वापस शून्य;
पूर्ण

स्थिर काष्ठा atomisp_क्रमmat_bridge *
atomisp_get_क्रमmat_bridge_from_mbus(u32 mbus_code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(atomisp_output_fmts); i++) अणु
		अगर (mbus_code == atomisp_output_fmts[i].mbus_code)
			वापस &atomisp_output_fmts[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * v4l2 ioctls
 * वापस ISP capabilities
 */
अटल पूर्णांक atomisp_querycap(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_capability *cap)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);

	strscpy(cap->driver, DRIVER, माप(cap->driver));
	strscpy(cap->card, CARD, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "PCI:%s", dev_name(isp->dev));

	वापस 0;
पूर्ण

/*
 * क्रमागत input are used to check primary/secondary camera
 */
अटल पूर्णांक atomisp_क्रमागत_input(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_input *input)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	पूर्णांक index = input->index;
	काष्ठा v4l2_subdev *motor;

	अगर (index >= isp->input_cnt)
		वापस -EINVAL;

	अगर (!isp->inमाला_दो[index].camera)
		वापस -EINVAL;

	स_रखो(input, 0, माप(काष्ठा v4l2_input));
	strscpy(input->name, isp->inमाला_दो[index].camera->name,
		माप(input->name));

	/*
	 * HACK: append actuator's name to sensor's
	 * As currently userspace can't talk directly to subdev nodes, this
	 * ioctl is the only way to क्रमागत inमाला_दो + possible बाह्यal actuators
	 * क्रम 3A tuning purpose.
	 */
	अगर (!IS_ISP2401)
		motor = isp->inमाला_दो[index].motor;
	अन्यथा
		motor = isp->motor;

	अगर (motor && म_माप(motor->name) > 0) अणु
		स्थिर पूर्णांक cur_len = म_माप(input->name);
		स्थिर पूर्णांक max_size = माप(input->name) - cur_len - 1;

		अगर (max_size > 1) अणु
			input->name[cur_len] = '+';
			strscpy(&input->name[cur_len + 1],
				motor->name, max_size);
		पूर्ण
	पूर्ण

	input->type = V4L2_INPUT_TYPE_CAMERA;
	input->index = index;
	input->reserved[0] = isp->inमाला_दो[index].type;
	input->reserved[1] = isp->inमाला_दो[index].port;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
atomisp_subdev_streaming_count(काष्ठा atomisp_sub_device *asd)
अणु
	वापस asd->video_out_preview.capq.streaming
	       + asd->video_out_capture.capq.streaming
	       + asd->video_out_video_capture.capq.streaming
	       + asd->video_out_vf.capq.streaming
	       + asd->video_in.capq.streaming;
पूर्ण

अचिन्हित पूर्णांक atomisp_streaming_count(काष्ठा atomisp_device *isp)
अणु
	अचिन्हित पूर्णांक i, sum;

	क्रम (i = 0, sum = 0; i < isp->num_of_streams; i++)
		sum += isp->asd[i].streaming ==
		       ATOMISP_DEVICE_STREAMING_ENABLED;

	वापस sum;
पूर्ण

अचिन्हित पूर्णांक atomisp_is_acc_enabled(काष्ठा atomisp_device *isp)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < isp->num_of_streams; i++)
		अगर (isp->asd[i].acc.pipeline)
			वापस 1;

	वापस 0;
पूर्ण

/*
 * get input are used to get current primary/secondary camera
 */
अटल पूर्णांक atomisp_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *input)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_sub_device *asd = atomisp_to_video_pipe(vdev)->asd;

	rt_mutex_lock(&isp->mutex);
	*input = asd->input_curr;
	rt_mutex_unlock(&isp->mutex);

	वापस 0;
पूर्ण

/*
 * set input are used to set current primary/secondary camera
 */
अटल पूर्णांक atomisp_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक input)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_sub_device *asd = atomisp_to_video_pipe(vdev)->asd;
	काष्ठा v4l2_subdev *camera = शून्य;
	काष्ठा v4l2_subdev *motor;
	पूर्णांक ret;

	rt_mutex_lock(&isp->mutex);
	अगर (input >= ATOM_ISP_MAX_INPUTS || input >= isp->input_cnt) अणु
		dev_dbg(isp->dev, "input_cnt: %d\n", isp->input_cnt);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/*
	 * check whether the request camera:
	 * 1: alपढ़ोy in use
	 * 2: अगर in use, whether it is used by other streams
	 */
	अगर (isp->inमाला_दो[input].asd && isp->inमाला_दो[input].asd != asd) अणु
		dev_err(isp->dev,
			"%s, camera is already used by stream: %d\n", __func__,
			isp->inमाला_दो[input].asd->index);
		ret = -EBUSY;
		जाओ error;
	पूर्ण

	camera = isp->inमाला_दो[input].camera;
	अगर (!camera) अणु
		dev_err(isp->dev, "%s, no camera\n", __func__);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (atomisp_subdev_streaming_count(asd)) अणु
		dev_err(isp->dev,
			"ISP is still streaming, stop first\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* घातer off the current owned sensor, as it is not used this समय */
	अगर (isp->inमाला_दो[asd->input_curr].asd == asd &&
	    asd->input_curr != input) अणु
		ret = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
				       core, s_घातer, 0);
		अगर (ret)
			dev_warn(isp->dev,
				 "Failed to power-off sensor\n");
		/* clear the asd field to show this camera is not used */
		isp->inमाला_दो[asd->input_curr].asd = शून्य;
	पूर्ण

	/* घातe on the new sensor */
	ret = v4l2_subdev_call(isp->inमाला_दो[input].camera, core, s_घातer, 1);
	अगर (ret) अणु
		dev_err(isp->dev, "Failed to power-on sensor\n");
		जाओ error;
	पूर्ण
	/*
	 * Some sensor driver resets the run mode during घातer-on, thus क्रमce
	 * update the run mode to sensor after घातer-on.
	 */
	atomisp_update_run_mode(asd);

	/* select operating sensor */
	ret = v4l2_subdev_call(isp->inमाला_दो[input].camera, video, s_routing,
			       0, isp->inमाला_दो[input].sensor_index, 0);
	अगर (ret && (ret != -ENOIOCTLCMD)) अणु
		dev_err(isp->dev, "Failed to select sensor\n");
		जाओ error;
	पूर्ण

	अगर (!IS_ISP2401) अणु
		motor = isp->inमाला_दो[input].motor;
	पूर्ण अन्यथा अणु
		motor = isp->motor;
		अगर (motor)
			ret = v4l2_subdev_call(motor, core, s_घातer, 1);
	पूर्ण

	अगर (!isp->sw_contex.file_input && motor)
		ret = v4l2_subdev_call(motor, core, init, 1);

	asd->input_curr = input;
	/* mark this camera is used by the current stream */
	isp->inमाला_दो[input].asd = asd;
	rt_mutex_unlock(&isp->mutex);

	वापस 0;

error:
	rt_mutex_unlock(&isp->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_क्रमागत_fmt_cap(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_sub_device *asd = atomisp_to_video_pipe(vdev)->asd;
	काष्ठा v4l2_subdev_mbus_code_क्रमागत code = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक i, fi = 0;
	पूर्णांक rval;

	rt_mutex_lock(&isp->mutex);
	rval = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera, pad,
				क्रमागत_mbus_code, शून्य, &code);
	अगर (rval == -ENOIOCTLCMD) अणु
		dev_warn(isp->dev,
			 "enum_mbus_code pad op not supported. Please fix your sensor driver!\n");
		//	rval = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
		//				video, क्रमागत_mbus_fmt, 0, &code.code);
	पूर्ण
	rt_mutex_unlock(&isp->mutex);

	अगर (rval)
		वापस rval;

	क्रम (i = 0; i < ARRAY_SIZE(atomisp_output_fmts); i++) अणु
		स्थिर काष्ठा atomisp_क्रमmat_bridge *क्रमmat =
			    &atomisp_output_fmts[i];

		/*
		 * Is the atomisp-supported क्रमmat is valid क्रम the
		 * sensor (configuration)? If not, skip it.
		 */
		अगर (क्रमmat->sh_fmt == IA_CSS_FRAME_FORMAT_RAW
		    && क्रमmat->mbus_code != code.code)
			जारी;

		/* Found a match. Now let's pick f->index'th one. */
		अगर (fi < f->index) अणु
			fi++;
			जारी;
		पूर्ण

		strscpy(f->description, क्रमmat->description,
			माप(f->description));
		f->pixelक्रमmat = क्रमmat->pixelक्रमmat;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक atomisp_g_fmt_cap(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);

	पूर्णांक ret;

	rt_mutex_lock(&isp->mutex);
	ret = atomisp_get_fmt(vdev, f);
	rt_mutex_unlock(&isp->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_g_fmt_file(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);

	rt_mutex_lock(&isp->mutex);
	f->fmt.pix = pipe->pix;
	rt_mutex_unlock(&isp->mutex);

	वापस 0;
पूर्ण

/* This function looks up the बंदst available resolution. */
अटल पूर्णांक atomisp_try_fmt_cap(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	पूर्णांक ret;

	rt_mutex_lock(&isp->mutex);
	ret = atomisp_try_fmt(vdev, &f->fmt.pix, शून्य);
	rt_mutex_unlock(&isp->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_s_fmt_cap(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	पूर्णांक ret;

	rt_mutex_lock(&isp->mutex);
	अगर (isp->isp_fatal_error) अणु
		ret = -EIO;
		rt_mutex_unlock(&isp->mutex);
		वापस ret;
	पूर्ण
	ret = atomisp_set_fmt(vdev, f);
	rt_mutex_unlock(&isp->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_s_fmt_file(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	पूर्णांक ret;

	rt_mutex_lock(&isp->mutex);
	ret = atomisp_set_fmt_file(vdev, f);
	rt_mutex_unlock(&isp->mutex);
	वापस ret;
पूर्ण

/*
 * Free videobuffer buffer priv data
 */
व्योम atomisp_videobuf_मुक्त_buf(काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा videobuf_vदो_स्मृति_memory *vm_mem;

	अगर (!vb)
		वापस;

	vm_mem = vb->priv;
	अगर (vm_mem && vm_mem->vaddr) अणु
		ia_css_frame_मुक्त(vm_mem->vaddr);
		vm_mem->vaddr = शून्य;
	पूर्ण
पूर्ण

/*
 * this function is used to मुक्त video buffer queue
 */
अटल व्योम atomisp_videobuf_मुक्त_queue(काष्ठा videobuf_queue *q)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VIDEO_MAX_FRAME; i++) अणु
		atomisp_videobuf_मुक्त_buf(q->bufs[i]);
		kमुक्त(q->bufs[i]);
		q->bufs[i] = शून्य;
	पूर्ण
पूर्ण

पूर्णांक atomisp_alloc_css_stat_bufs(काष्ठा atomisp_sub_device *asd,
				uपूर्णांक16_t stream_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा atomisp_s3a_buf *s3a_buf = शून्य, *_s3a_buf;
	काष्ठा atomisp_dis_buf *dis_buf = शून्य, *_dis_buf;
	काष्ठा atomisp_metadata_buf *md_buf = शून्य, *_md_buf;
	पूर्णांक count;
	काष्ठा ia_css_dvs_grid_info *dvs_grid_info =
	    atomisp_css_get_dvs_grid_info(&asd->params.curr_grid_info);
	अचिन्हित पूर्णांक i;

	अगर (list_empty(&asd->s3a_stats) &&
	    asd->params.curr_grid_info.s3a_grid.enable) अणु
		count = ATOMISP_CSS_Q_DEPTH +
			ATOMISP_S3A_BUF_QUEUE_DEPTH_FOR_HAL;
		dev_dbg(isp->dev, "allocating %d 3a buffers\n", count);
		जबतक (count--) अणु
			s3a_buf = kzalloc(माप(काष्ठा atomisp_s3a_buf), GFP_KERNEL);
			अगर (!s3a_buf)
				जाओ error;

			अगर (atomisp_css_allocate_stat_buffers(
				asd, stream_id, s3a_buf, शून्य, शून्य)) अणु
				kमुक्त(s3a_buf);
				जाओ error;
			पूर्ण

			list_add_tail(&s3a_buf->list, &asd->s3a_stats);
		पूर्ण
	पूर्ण

	अगर (list_empty(&asd->dis_stats) && dvs_grid_info &&
	    dvs_grid_info->enable) अणु
		count = ATOMISP_CSS_Q_DEPTH + 1;
		dev_dbg(isp->dev, "allocating %d dis buffers\n", count);
		जबतक (count--) अणु
			dis_buf = kzalloc(माप(काष्ठा atomisp_dis_buf), GFP_KERNEL);
			अगर (!dis_buf)
				जाओ error;
			अगर (atomisp_css_allocate_stat_buffers(
				asd, stream_id, शून्य, dis_buf, शून्य)) अणु
				kमुक्त(dis_buf);
				जाओ error;
			पूर्ण

			list_add_tail(&dis_buf->list, &asd->dis_stats);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ATOMISP_METADATA_TYPE_NUM; i++) अणु
		अगर (list_empty(&asd->metadata[i]) &&
		    list_empty(&asd->metadata_पढ़ोy[i]) &&
		    list_empty(&asd->metadata_in_css[i])) अणु
			count = ATOMISP_CSS_Q_DEPTH +
				ATOMISP_METADATA_QUEUE_DEPTH_FOR_HAL;
			dev_dbg(isp->dev, "allocating %d metadata buffers for type %d\n",
				count, i);
			जबतक (count--) अणु
				md_buf = kzalloc(माप(काष्ठा atomisp_metadata_buf),
						 GFP_KERNEL);
				अगर (!md_buf)
					जाओ error;

				अगर (atomisp_css_allocate_stat_buffers(
					asd, stream_id, शून्य, शून्य, md_buf)) अणु
					kमुक्त(md_buf);
					जाओ error;
				पूर्ण
				list_add_tail(&md_buf->list, &asd->metadata[i]);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;

error:
	dev_err(isp->dev, "failed to allocate statistics buffers\n");

	list_क्रम_each_entry_safe(dis_buf, _dis_buf, &asd->dis_stats, list) अणु
		atomisp_css_मुक्त_dis_buffer(dis_buf);
		list_del(&dis_buf->list);
		kमुक्त(dis_buf);
	पूर्ण

	list_क्रम_each_entry_safe(s3a_buf, _s3a_buf, &asd->s3a_stats, list) अणु
		atomisp_css_मुक्त_3a_buffer(s3a_buf);
		list_del(&s3a_buf->list);
		kमुक्त(s3a_buf);
	पूर्ण

	क्रम (i = 0; i < ATOMISP_METADATA_TYPE_NUM; i++) अणु
		list_क्रम_each_entry_safe(md_buf, _md_buf, &asd->metadata[i],
					 list) अणु
			atomisp_css_मुक्त_metadata_buffer(md_buf);
			list_del(&md_buf->list);
			kमुक्त(md_buf);
		पूर्ण
	पूर्ण
	वापस -ENOMEM;
पूर्ण

/*
 * Initiate Memory Mapping or User Poपूर्णांकer I/O
 */
पूर्णांक __atomisp_reqbufs(काष्ठा file *file, व्योम *fh,
		      काष्ठा v4l2_requestbuffers *req)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);
	काष्ठा atomisp_sub_device *asd = pipe->asd;
	काष्ठा ia_css_frame_info frame_info;
	काष्ठा ia_css_frame *frame;
	काष्ठा videobuf_vदो_स्मृति_memory *vm_mem;
	u16 source_pad = atomisp_subdev_source_pad(vdev);
	u16 stream_id = atomisp_source_pad_to_stream_id(asd, source_pad);
	पूर्णांक ret = 0, i = 0;

	अगर (req->count == 0) अणु
		mutex_lock(&pipe->capq.vb_lock);
		अगर (!list_empty(&pipe->capq.stream))
			videobuf_queue_cancel(&pipe->capq);

		atomisp_videobuf_मुक्त_queue(&pipe->capq);
		mutex_unlock(&pipe->capq.vb_lock);
		/* clear request config id */
		स_रखो(pipe->frame_request_config_id, 0,
		       VIDEO_MAX_FRAME * माप(अचिन्हित पूर्णांक));
		स_रखो(pipe->frame_params, 0,
		       VIDEO_MAX_FRAME *
		       माप(काष्ठा atomisp_css_params_with_list *));
		वापस 0;
	पूर्ण

	ret = videobuf_reqbufs(&pipe->capq, req);
	अगर (ret)
		वापस ret;

	atomisp_alloc_css_stat_bufs(asd, stream_id);

	/*
	 * क्रम user poपूर्णांकer type, buffers are not really allocated here,
	 * buffers are setup in QBUF operation through v4l2_buffer काष्ठाure
	 */
	अगर (req->memory == V4L2_MEMORY_USERPTR)
		वापस 0;

	ret = atomisp_get_css_frame_info(asd, source_pad, &frame_info);
	अगर (ret)
		वापस ret;

	/*
	 * Allocate the real frame here क्रम selected node using our
	 * memory management function
	 */
	क्रम (i = 0; i < req->count; i++) अणु
		अगर (ia_css_frame_allocate_from_info(&frame, &frame_info))
			जाओ error;
		vm_mem = pipe->capq.bufs[i]->priv;
		vm_mem->vaddr = frame;
	पूर्ण

	वापस ret;

error:
	जबतक (i--) अणु
		vm_mem = pipe->capq.bufs[i]->priv;
		ia_css_frame_मुक्त(vm_mem->vaddr);
	पूर्ण

	अगर (asd->vf_frame)
		ia_css_frame_मुक्त(asd->vf_frame);

	वापस -ENOMEM;
पूर्ण

पूर्णांक atomisp_reqbufs(काष्ठा file *file, व्योम *fh,
		    काष्ठा v4l2_requestbuffers *req)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	पूर्णांक ret;

	rt_mutex_lock(&isp->mutex);
	ret = __atomisp_reqbufs(file, fh, req);
	rt_mutex_unlock(&isp->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_reqbufs_file(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_requestbuffers *req)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);

	अगर (req->count == 0) अणु
		mutex_lock(&pipe->outq.vb_lock);
		atomisp_videobuf_मुक्त_queue(&pipe->outq);
		mutex_unlock(&pipe->outq.vb_lock);
		वापस 0;
	पूर्ण

	वापस videobuf_reqbufs(&pipe->outq, req);
पूर्ण

/* application query the status of a buffer */
अटल पूर्णांक atomisp_querybuf(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);

	वापस videobuf_querybuf(&pipe->capq, buf);
पूर्ण

अटल पूर्णांक atomisp_querybuf_file(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);

	वापस videobuf_querybuf(&pipe->outq, buf);
पूर्ण

/*
 * Applications call the VIDIOC_QBUF ioctl to enqueue an empty (capturing) or
 * filled (output) buffer in the drivers incoming queue.
 */
अटल पूर्णांक atomisp_qbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *buf)
अणु
	अटल स्थिर पूर्णांक NOFLUSH_FLAGS = V4L2_BUF_FLAG_NO_CACHE_INVALIDATE |
					 V4L2_BUF_FLAG_NO_CACHE_CLEAN;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);
	काष्ठा atomisp_sub_device *asd = pipe->asd;
	काष्ठा videobuf_buffer *vb;
	काष्ठा videobuf_vदो_स्मृति_memory *vm_mem;
	काष्ठा ia_css_frame_info frame_info;
	काष्ठा ia_css_frame *handle = शून्य;
	u32 length;
	u32 pgnr;
	पूर्णांक ret = 0;

	rt_mutex_lock(&isp->mutex);
	अगर (isp->isp_fatal_error) अणु
		ret = -EIO;
		जाओ error;
	पूर्ण

	अगर (asd->streaming == ATOMISP_DEVICE_STREAMING_STOPPING) अणु
		dev_err(isp->dev, "%s: reject, as ISP at stopping.\n",
			__func__);
		ret = -EIO;
		जाओ error;
	पूर्ण

	अगर (!buf || buf->index >= VIDEO_MAX_FRAME ||
	    !pipe->capq.bufs[buf->index]) अणु
		dev_err(isp->dev, "Invalid index for qbuf.\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/*
	 * For userptr type frame, we convert user space address to physic
	 * address and reprograme out page table properly
	 */
	अगर (buf->memory == V4L2_MEMORY_USERPTR) अणु
		vb = pipe->capq.bufs[buf->index];
		vm_mem = vb->priv;
		अगर (!vm_mem) अणु
			ret = -EINVAL;
			जाओ error;
		पूर्ण

		length = vb->bsize;
		pgnr = (length + (PAGE_SIZE - 1)) >> PAGE_SHIFT;

		अगर (vb->baddr == buf->m.userptr && vm_mem->vaddr)
			जाओ करोne;

		अगर (atomisp_get_css_frame_info(asd,
					       atomisp_subdev_source_pad(vdev), &frame_info)) अणु
			ret = -EIO;
			जाओ error;
		पूर्ण

		ret = ia_css_frame_map(&handle, &frame_info,
					    (व्योम __user *)buf->m.userptr,
					    0, pgnr);
		अगर (ret) अणु
			dev_err(isp->dev, "Failed to map user buffer\n");
			जाओ error;
		पूर्ण

		अगर (vm_mem->vaddr) अणु
			mutex_lock(&pipe->capq.vb_lock);
			ia_css_frame_मुक्त(vm_mem->vaddr);
			vm_mem->vaddr = शून्य;
			vb->state = VIDEOBUF_NEEDS_INIT;
			mutex_unlock(&pipe->capq.vb_lock);
		पूर्ण

		vm_mem->vaddr = handle;

		buf->flags &= ~V4L2_BUF_FLAG_MAPPED;
		buf->flags |= V4L2_BUF_FLAG_QUEUED;
		buf->flags &= ~V4L2_BUF_FLAG_DONE;
	पूर्ण अन्यथा अगर (buf->memory == V4L2_MEMORY_MMAP) अणु
		buf->flags |= V4L2_BUF_FLAG_MAPPED;
		buf->flags |= V4L2_BUF_FLAG_QUEUED;
		buf->flags &= ~V4L2_BUF_FLAG_DONE;

		/*
		 * For mmap, frames were allocated at request buffers
		 */
	पूर्ण

करोne:
	अगर (!((buf->flags & NOFLUSH_FLAGS) == NOFLUSH_FLAGS))
		wbinvd();

	अगर (!atomisp_is_vf_pipe(pipe) &&
	    (buf->reserved2 & ATOMISP_BUFFER_HAS_PER_FRAME_SETTING)) अणु
		/* this buffer will have a per-frame parameter */
		pipe->frame_request_config_id[buf->index] = buf->reserved2 &
			~ATOMISP_BUFFER_HAS_PER_FRAME_SETTING;
		dev_dbg(isp->dev,
			"This buffer requires per_frame setting which has isp_config_id %d\n",
			pipe->frame_request_config_id[buf->index]);
	पूर्ण अन्यथा अणु
		pipe->frame_request_config_id[buf->index] = 0;
	पूर्ण

	pipe->frame_params[buf->index] = शून्य;

	rt_mutex_unlock(&isp->mutex);

	ret = videobuf_qbuf(&pipe->capq, buf);
	rt_mutex_lock(&isp->mutex);
	अगर (ret)
		जाओ error;

	/* TODO: करो this better, not best way to queue to css */
	अगर (asd->streaming == ATOMISP_DEVICE_STREAMING_ENABLED) अणु
		अगर (!list_empty(&pipe->buffers_रुकोing_क्रम_param)) अणु
			atomisp_handle_parameter_and_buffer(pipe);
		पूर्ण अन्यथा अणु
			atomisp_qbuffers_to_css(asd);

			अगर (!IS_ISP2401) अणु
				अगर (!atomisp_is_wdt_running(asd) && atomisp_buffers_queued(asd))
					atomisp_wdt_start(asd);
			पूर्ण अन्यथा अणु
				अगर (!atomisp_is_wdt_running(pipe) &&
				    atomisp_buffers_queued_pipe(pipe))
					atomisp_wdt_start_pipe(pipe);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Workaround: Due to the design of HALv3,
	 * someबार in ZSL or SDV mode HAL needs to
	 * capture multiple images within one streaming cycle.
	 * But the capture number cannot be determined by HAL.
	 * So HAL only sets the capture number to be 1 and queue multiple
	 * buffers. Atomisp driver needs to check this हाल and re-trigger
	 * CSS to करो capture when new buffer is queued.
	 */
	अगर (asd->continuous_mode->val &&
	    atomisp_subdev_source_pad(vdev)
	    == ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE &&
	    pipe->capq.streaming &&
	    !asd->enable_raw_buffer_lock->val &&
	    asd->params.offline_parm.num_captures == 1) अणु
		अगर (!IS_ISP2401) अणु
			asd->pending_capture_request++;
			dev_dbg(isp->dev, "Add one pending capture request.\n");
		पूर्ण अन्यथा अणु
			अगर (asd->re_trigger_capture) अणु
				ret = atomisp_css_offline_capture_configure(asd,
					asd->params.offline_parm.num_captures,
					asd->params.offline_parm.skip_frames,
					asd->params.offline_parm.offset);
				asd->re_trigger_capture = false;
				dev_dbg(isp->dev, "%s Trigger capture again ret=%d\n",
					__func__, ret);

			पूर्ण अन्यथा अणु
				asd->pending_capture_request++;
				asd->re_trigger_capture = false;
				dev_dbg(isp->dev, "Add one pending capture request.\n");
			पूर्ण
		पूर्ण
	पूर्ण
	rt_mutex_unlock(&isp->mutex);

	dev_dbg(isp->dev, "qbuf buffer %d (%s) for asd%d\n", buf->index,
		vdev->name, asd->index);

	वापस ret;

error:
	rt_mutex_unlock(&isp->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_qbuf_file(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);
	पूर्णांक ret;

	rt_mutex_lock(&isp->mutex);
	अगर (isp->isp_fatal_error) अणु
		ret = -EIO;
		जाओ error;
	पूर्ण

	अगर (!buf || buf->index >= VIDEO_MAX_FRAME ||
	    !pipe->outq.bufs[buf->index]) अणु
		dev_err(isp->dev, "Invalid index for qbuf.\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (buf->memory != V4L2_MEMORY_MMAP) अणु
		dev_err(isp->dev, "Unsupported memory method\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (buf->type != V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		dev_err(isp->dev, "Unsupported buffer type\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण
	rt_mutex_unlock(&isp->mutex);

	वापस videobuf_qbuf(&pipe->outq, buf);

error:
	rt_mutex_unlock(&isp->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __get_frame_exp_id(काष्ठा atomisp_video_pipe *pipe,
			      काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा videobuf_vदो_स्मृति_memory *vm_mem;
	काष्ठा ia_css_frame *handle;
	पूर्णांक i;

	क्रम (i = 0; pipe->capq.bufs[i]; i++) अणु
		vm_mem = pipe->capq.bufs[i]->priv;
		handle = vm_mem->vaddr;
		अगर (buf->index == pipe->capq.bufs[i]->i && handle)
			वापस handle->exp_id;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * Applications call the VIDIOC_DQBUF ioctl to dequeue a filled (capturing) or
 * displayed (output buffer)from the driver's outgoing queue
 */
अटल पूर्णांक atomisp_dqbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);
	काष्ठा atomisp_sub_device *asd = pipe->asd;
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	पूर्णांक ret = 0;

	rt_mutex_lock(&isp->mutex);

	अगर (isp->isp_fatal_error) अणु
		rt_mutex_unlock(&isp->mutex);
		वापस -EIO;
	पूर्ण

	अगर (asd->streaming == ATOMISP_DEVICE_STREAMING_STOPPING) अणु
		rt_mutex_unlock(&isp->mutex);
		dev_err(isp->dev, "%s: reject, as ISP at stopping.\n",
			__func__);
		वापस -EIO;
	पूर्ण

	rt_mutex_unlock(&isp->mutex);

	ret = videobuf_dqbuf(&pipe->capq, buf, file->f_flags & O_NONBLOCK);
	अगर (ret) अणु
		अगर (ret != -EAGAIN)
			dev_dbg(isp->dev, "<%s: %d\n", __func__, ret);
		वापस ret;
	पूर्ण
	rt_mutex_lock(&isp->mutex);
	buf->bytesused = pipe->pix.sizeimage;
	buf->reserved = asd->frame_status[buf->index];

	/*
	 * Hack:
	 * Currently frame_status in the क्रमागत type which takes no more lower
	 * 8 bit.
	 * use bit[31:16] क्रम exp_id as it is only in the range of 1~255
	 */
	buf->reserved &= 0x0000ffff;
	अगर (!(buf->flags & V4L2_BUF_FLAG_ERROR))
		buf->reserved |= __get_frame_exp_id(pipe, buf) << 16;
	buf->reserved2 = pipe->frame_config_id[buf->index];
	rt_mutex_unlock(&isp->mutex);

	dev_dbg(isp->dev,
		"dqbuf buffer %d (%s) for asd%d with exp_id %d, isp_config_id %d\n",
		buf->index, vdev->name, asd->index, buf->reserved >> 16,
		buf->reserved2);
	वापस 0;
पूर्ण

क्रमागत ia_css_pipe_id atomisp_get_css_pipe_id(काष्ठा atomisp_sub_device *asd)
अणु
	अगर (ATOMISP_USE_YUVPP(asd))
		वापस IA_CSS_PIPE_ID_YUVPP;

	अगर (asd->continuous_mode->val) अणु
		अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO)
			वापस IA_CSS_PIPE_ID_VIDEO;
		अन्यथा
			वापस IA_CSS_PIPE_ID_PREVIEW;
	पूर्ण

	/*
	 * Disable vf_pp and run CSS in video mode. This allows using ISP
	 * scaling but it has one frame delay due to CSS पूर्णांकernal buffering.
	 */
	अगर (asd->vfpp->val == ATOMISP_VFPP_DISABLE_SCALER)
		वापस IA_CSS_PIPE_ID_VIDEO;

	/*
	 * Disable vf_pp and run CSS in still capture mode. In this mode
	 * CSS करोes not cause extra latency with buffering, but scaling
	 * is not available.
	 */
	अगर (asd->vfpp->val == ATOMISP_VFPP_DISABLE_LOWLAT)
		वापस IA_CSS_PIPE_ID_CAPTURE;

	चयन (asd->run_mode->val) अणु
	हाल ATOMISP_RUN_MODE_PREVIEW:
		वापस IA_CSS_PIPE_ID_PREVIEW;
	हाल ATOMISP_RUN_MODE_VIDEO:
		वापस IA_CSS_PIPE_ID_VIDEO;
	हाल ATOMISP_RUN_MODE_STILL_CAPTURE:
	शेष:
		वापस IA_CSS_PIPE_ID_CAPTURE;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक atomisp_sensor_start_stream(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (isp->inमाला_दो[asd->input_curr].camera_caps->
	    sensor[asd->sensor_curr].stream_num > 1) अणु
		अगर (asd->high_speed_mode)
			वापस 1;
		अन्यथा
			वापस 2;
	पूर्ण

	अगर (asd->vfpp->val != ATOMISP_VFPP_ENABLE ||
	    asd->copy_mode)
		वापस 1;

	अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO ||
	    (asd->run_mode->val == ATOMISP_RUN_MODE_STILL_CAPTURE &&
	     !atomisp_is_mbuscode_raw(
		 asd->fmt[
		  asd->capture_pad].fmt.code) &&
	     !asd->continuous_mode->val))
		वापस 2;
	अन्यथा
		वापस 1;
पूर्ण

पूर्णांक atomisp_stream_on_master_slave_sensor(काष्ठा atomisp_device *isp,
	bool isp_समयout)
अणु
	अचिन्हित पूर्णांक master = -1, slave = -1, delay_slave = 0;
	पूर्णांक i, ret;

	/*
	 * ISP only support 2 streams now so ignore multiple master/slave
	 * हाल to reduce the delay between 2 stream_on calls.
	 */
	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		पूर्णांक sensor_index = isp->asd[i].input_curr;

		अगर (isp->inमाला_दो[sensor_index].camera_caps->
		    sensor[isp->asd[i].sensor_curr].is_slave)
			slave = sensor_index;
		अन्यथा
			master = sensor_index;
	पूर्ण

	अगर (master == -1 || slave == -1) अणु
		master = ATOMISP_DEPTH_DEFAULT_MASTER_SENSOR;
		slave = ATOMISP_DEPTH_DEFAULT_SLAVE_SENSOR;
		dev_warn(isp->dev,
			 "depth mode use default master=%s.slave=%s.\n",
			 isp->inमाला_दो[master].camera->name,
			 isp->inमाला_दो[slave].camera->name);
	पूर्ण

	ret = v4l2_subdev_call(isp->inमाला_दो[master].camera, core,
			       ioctl, ATOMISP_IOC_G_DEPTH_SYNC_COMP,
			       &delay_slave);
	अगर (ret)
		dev_warn(isp->dev,
			 "get depth sensor %s compensation delay failed.\n",
			 isp->inमाला_दो[master].camera->name);

	ret = v4l2_subdev_call(isp->inमाला_दो[master].camera,
			       video, s_stream, 1);
	अगर (ret) अणु
		dev_err(isp->dev, "depth mode master sensor %s stream-on failed.\n",
			isp->inमाला_दो[master].camera->name);
		वापस -EINVAL;
	पूर्ण

	अगर (delay_slave != 0)
		udelay(delay_slave);

	ret = v4l2_subdev_call(isp->inमाला_दो[slave].camera,
			       video, s_stream, 1);
	अगर (ret) अणु
		dev_err(isp->dev, "depth mode slave sensor %s stream-on failed.\n",
			isp->inमाला_दो[slave].camera->name);
		v4l2_subdev_call(isp->inमाला_दो[master].camera, video, s_stream, 0);

		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* FIXME! ISP2400 */
अटल व्योम __wdt_on_master_slave_sensor(काष्ठा atomisp_device *isp,
					 अचिन्हित पूर्णांक wdt_duration)
अणु
	अगर (atomisp_buffers_queued(&isp->asd[0]))
		atomisp_wdt_refresh(&isp->asd[0], wdt_duration);
	अगर (atomisp_buffers_queued(&isp->asd[1]))
		atomisp_wdt_refresh(&isp->asd[1], wdt_duration);
पूर्ण

/* FIXME! ISP2401 */
अटल व्योम __wdt_on_master_slave_sensor_pipe(काष्ठा atomisp_video_pipe *pipe,
					      अचिन्हित पूर्णांक wdt_duration,
					      bool enable)
अणु
	अटल काष्ठा atomisp_video_pipe *pipe0;

	अगर (enable) अणु
		अगर (atomisp_buffers_queued_pipe(pipe0))
			atomisp_wdt_refresh_pipe(pipe0, wdt_duration);
		अगर (atomisp_buffers_queued_pipe(pipe))
			atomisp_wdt_refresh_pipe(pipe, wdt_duration);
	पूर्ण अन्यथा अणु
		pipe0 = pipe;
	पूर्ण
पूर्ण

अटल व्योम atomisp_छोड़ो_buffer_event(काष्ठा atomisp_device *isp)
अणु
	काष्ठा v4l2_event event = अणु0पूर्ण;
	पूर्णांक i;

	event.type = V4L2_EVENT_ATOMISP_PAUSE_BUFFER;

	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		पूर्णांक sensor_index = isp->asd[i].input_curr;

		अगर (isp->inमाला_दो[sensor_index].camera_caps->
		    sensor[isp->asd[i].sensor_curr].is_slave) अणु
			v4l2_event_queue(isp->asd[i].subdev.devnode, &event);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Input प्रणाली HW workaround */
/* Input प्रणाली address translation corrupts burst during */
/* invalidate. SW workaround क्रम this is to set burst length */
/* manually to 128 in हाल of 13MPx snapshot and to 1 otherwise. */
अटल व्योम atomisp_dma_burst_len_cfg(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा v4l2_mbus_framefmt *sink;

	sink = atomisp_subdev_get_ffmt(&asd->subdev, शून्य,
				       V4L2_SUBDEV_FORMAT_ACTIVE,
				       ATOMISP_SUBDEV_PAD_SINK);

	अगर (sink->width * sink->height >= 4096 * 3072)
		atomisp_css2_hw_store_32(DMA_BURST_SIZE_REG, 0x7F);
	अन्यथा
		atomisp_css2_hw_store_32(DMA_BURST_SIZE_REG, 0x00);
पूर्ण

/*
 * This ioctl start the capture during streaming I/O.
 */
अटल पूर्णांक atomisp_streamon(काष्ठा file *file, व्योम *fh,
			    क्रमागत v4l2_buf_type type)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);
	काष्ठा atomisp_sub_device *asd = pipe->asd;
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा pci_dev *pdev = to_pci_dev(isp->dev);
	क्रमागत ia_css_pipe_id css_pipe_id;
	अचिन्हित पूर्णांक sensor_start_stream;
	अचिन्हित पूर्णांक wdt_duration = ATOMISP_ISP_TIMEOUT_DURATION;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ irqflags;

	dev_dbg(isp->dev, "Start stream on pad %d for asd%d\n",
		atomisp_subdev_source_pad(vdev), asd->index);

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		dev_dbg(isp->dev, "unsupported v4l2 buf type\n");
		वापस -EINVAL;
	पूर्ण

	rt_mutex_lock(&isp->mutex);
	अगर (isp->isp_fatal_error) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (asd->streaming == ATOMISP_DEVICE_STREAMING_STOPPING) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (pipe->capq.streaming)
		जाओ out;

	/* Input प्रणाली HW workaround */
	atomisp_dma_burst_len_cfg(asd);

	/*
	 * The number of streaming video nodes is based on which
	 * binary is going to be run.
	 */
	sensor_start_stream = atomisp_sensor_start_stream(asd);

	spin_lock_irqsave(&pipe->irq_lock, irqflags);
	अगर (list_empty(&pipe->capq.stream)) अणु
		spin_unlock_irqrestore(&pipe->irq_lock, irqflags);
		dev_dbg(isp->dev, "no buffer in the queue\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	spin_unlock_irqrestore(&pipe->irq_lock, irqflags);

	ret = videobuf_streamon(&pipe->capq);
	अगर (ret)
		जाओ out;

	/* Reset pending capture request count. */
	asd->pending_capture_request = 0;
	अगर (IS_ISP2401)
		asd->re_trigger_capture = false;

	अगर ((atomisp_subdev_streaming_count(asd) > sensor_start_stream) &&
	    (!isp->inमाला_दो[asd->input_curr].camera_caps->multi_stream_ctrl)) अणु
		/* trigger still capture */
		अगर (asd->continuous_mode->val &&
		    atomisp_subdev_source_pad(vdev)
		    == ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE) अणु
			अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO)
				dev_dbg(isp->dev, "SDV last video raw buffer id: %u\n",
					asd->latest_preview_exp_id);
			अन्यथा
				dev_dbg(isp->dev, "ZSL last preview raw buffer id: %u\n",
					asd->latest_preview_exp_id);

			अगर (asd->delayed_init == ATOMISP_DELAYED_INIT_QUEUED) अणु
				flush_work(&asd->delayed_init_work);
				rt_mutex_unlock(&isp->mutex);
				अगर (रुको_क्रम_completion_पूर्णांकerruptible(
					&asd->init_करोne) != 0)
					वापस -ERESTARTSYS;
				rt_mutex_lock(&isp->mutex);
			पूर्ण

			/* handle per_frame_setting parameter and buffers */
			atomisp_handle_parameter_and_buffer(pipe);

			/*
			 * only ZSL/SDV capture request will be here, उठाओ
			 * the ISP freq to the highest possible to minimize
			 * the S2S latency.
			 */
			atomisp_freq_scaling(isp, ATOMISP_DFS_MODE_MAX, false);
			/*
			 * When asd->enable_raw_buffer_lock->val is true,
			 * An extra IOCTL is needed to call
			 * atomisp_css_exp_id_capture and trigger real capture
			 */
			अगर (!asd->enable_raw_buffer_lock->val) अणु
				ret = atomisp_css_offline_capture_configure(asd,
					asd->params.offline_parm.num_captures,
					asd->params.offline_parm.skip_frames,
					asd->params.offline_parm.offset);
				अगर (ret) अणु
					ret = -EINVAL;
					जाओ out;
				पूर्ण
				अगर (asd->depth_mode->val)
					atomisp_छोड़ो_buffer_event(isp);
			पूर्ण
		पूर्ण
		atomisp_qbuffers_to_css(asd);
		जाओ out;
	पूर्ण

	अगर (asd->streaming == ATOMISP_DEVICE_STREAMING_ENABLED) अणु
		atomisp_qbuffers_to_css(asd);
		जाओ start_sensor;
	पूर्ण

	css_pipe_id = atomisp_get_css_pipe_id(asd);

	ret = atomisp_acc_load_extensions(asd);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "acc extension failed to load\n");
		जाओ out;
	पूर्ण

	अगर (asd->params.css_update_params_needed) अणु
		atomisp_apply_css_parameters(asd, &asd->params.css_param);
		अगर (asd->params.css_param.update_flag.dz_config)
			asd->params.config.dz_config = &asd->params.css_param.dz_config;
		atomisp_css_update_isp_params(asd);
		asd->params.css_update_params_needed = false;
		स_रखो(&asd->params.css_param.update_flag, 0,
		       माप(काष्ठा atomisp_parameters));
	पूर्ण
	asd->params.dvs_6axis = शून्य;

	ret = atomisp_css_start(asd, css_pipe_id, false);
	अगर (ret)
		जाओ out;

	asd->streaming = ATOMISP_DEVICE_STREAMING_ENABLED;
	atomic_set(&asd->sof_count, -1);
	atomic_set(&asd->sequence, -1);
	atomic_set(&asd->sequence_temp, -1);
	अगर (isp->sw_contex.file_input)
		wdt_duration = ATOMISP_ISP_खाता_TIMEOUT_DURATION;

	asd->params.dis_proj_data_valid = false;
	asd->latest_preview_exp_id = 0;
	asd->postview_exp_id = 1;
	asd->preview_exp_id = 1;

	/* handle per_frame_setting parameter and buffers */
	atomisp_handle_parameter_and_buffer(pipe);

	atomisp_qbuffers_to_css(asd);

	/* Only start sensor when the last streaming instance started */
	अगर (atomisp_subdev_streaming_count(asd) < sensor_start_stream)
		जाओ out;

start_sensor:
	अगर (isp->flash) अणु
		asd->params.num_flash_frames = 0;
		asd->params.flash_state = ATOMISP_FLASH_IDLE;
		atomisp_setup_flash(asd);
	पूर्ण

	अगर (!isp->sw_contex.file_input) अणु
		atomisp_css_irq_enable(isp, IA_CSS_IRQ_INFO_CSS_RECEIVER_SOF,
				       atomisp_css_valid_sof(isp));
		atomisp_csi2_configure(asd);
		/*
		 * set freq to max when streaming count > 1 which indicate
		 * dual camera would run
		 */
		अगर (atomisp_streaming_count(isp) > 1) अणु
			अगर (atomisp_freq_scaling(isp,
						 ATOMISP_DFS_MODE_MAX, false) < 0)
				dev_dbg(isp->dev, "DFS max mode failed!\n");
		पूर्ण अन्यथा अणु
			अगर (atomisp_freq_scaling(isp,
						 ATOMISP_DFS_MODE_AUTO, false) < 0)
				dev_dbg(isp->dev, "DFS auto mode failed!\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (atomisp_freq_scaling(isp, ATOMISP_DFS_MODE_MAX, false) < 0)
			dev_dbg(isp->dev, "DFS max mode failed!\n");
	पूर्ण

	अगर (asd->depth_mode->val && atomisp_streaming_count(isp) ==
	    ATOMISP_DEPTH_SENSOR_STREAMON_COUNT) अणु
		ret = atomisp_stream_on_master_slave_sensor(isp, false);
		अगर (ret) अणु
			dev_err(isp->dev, "master slave sensor stream on failed!\n");
			जाओ out;
		पूर्ण
		अगर (!IS_ISP2401)
			__wdt_on_master_slave_sensor(isp, wdt_duration);
		अन्यथा
			__wdt_on_master_slave_sensor_pipe(pipe, wdt_duration, true);
		जाओ start_delay_wq;
	पूर्ण अन्यथा अगर (asd->depth_mode->val && (atomisp_streaming_count(isp) <
					    ATOMISP_DEPTH_SENSOR_STREAMON_COUNT)) अणु
		अगर (IS_ISP2401)
			__wdt_on_master_slave_sensor_pipe(pipe, wdt_duration, false);
		जाओ start_delay_wq;
	पूर्ण

	/* Enable the CSI पूर्णांकerface on ANN B0/K0 */
	अगर (isp->media_dev.hw_revision >= ((ATOMISP_HW_REVISION_ISP2401 <<
					    ATOMISP_HW_REVISION_SHIFT) | ATOMISP_HW_STEPPING_B0)) अणु
		pci_ग_लिखो_config_word(pdev, MRFLD_PCI_CSI_CONTROL,
				      isp->saved_regs.csi_control | MRFLD_PCI_CSI_CONTROL_CSI_READY);
	पूर्ण

	/* stream on the sensor */
	ret = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
			       video, s_stream, 1);
	अगर (ret) अणु
		asd->streaming = ATOMISP_DEVICE_STREAMING_DISABLED;
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!IS_ISP2401) अणु
		अगर (atomisp_buffers_queued(asd))
			atomisp_wdt_refresh(asd, wdt_duration);
	पूर्ण अन्यथा अणु
		अगर (atomisp_buffers_queued_pipe(pipe))
			atomisp_wdt_refresh_pipe(pipe, wdt_duration);
	पूर्ण

start_delay_wq:
	अगर (asd->continuous_mode->val) अणु
		काष्ठा v4l2_mbus_framefmt *sink;

		sink = atomisp_subdev_get_ffmt(&asd->subdev, शून्य,
					       V4L2_SUBDEV_FORMAT_ACTIVE,
					       ATOMISP_SUBDEV_PAD_SINK);

		reinit_completion(&asd->init_करोne);
		asd->delayed_init = ATOMISP_DELAYED_INIT_QUEUED;
		queue_work(asd->delayed_init_workq, &asd->delayed_init_work);
		atomisp_css_set_cont_prev_start_समय(isp,
						     ATOMISP_CALC_CSS_PREV_OVERLAP(sink->height));
	पूर्ण अन्यथा अणु
		asd->delayed_init = ATOMISP_DELAYED_INIT_NOT_QUEUED;
	पूर्ण
out:
	rt_mutex_unlock(&isp->mutex);
	वापस ret;
पूर्ण

पूर्णांक __atomisp_streamoff(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा pci_dev *pdev = to_pci_dev(isp->dev);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);
	काष्ठा atomisp_sub_device *asd = pipe->asd;
	काष्ठा atomisp_video_pipe *capture_pipe = शून्य;
	काष्ठा atomisp_video_pipe *vf_pipe = शून्य;
	काष्ठा atomisp_video_pipe *preview_pipe = शून्य;
	काष्ठा atomisp_video_pipe *video_pipe = शून्य;
	काष्ठा videobuf_buffer *vb, *_vb;
	क्रमागत ia_css_pipe_id css_pipe_id;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	bool first_streamoff = false;

	dev_dbg(isp->dev, "Stop stream on pad %d for asd%d\n",
		atomisp_subdev_source_pad(vdev), asd->index);

	BUG_ON(!rt_mutex_is_locked(&isp->mutex));
	BUG_ON(!mutex_is_locked(&isp->streamoff_mutex));

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		dev_dbg(isp->dev, "unsupported v4l2 buf type\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * करो only videobuf_streamoff क्रम capture & vf pipes in
	 * हाल of continuous capture
	 */
	अगर ((asd->continuous_mode->val ||
	     isp->inमाला_दो[asd->input_curr].camera_caps->multi_stream_ctrl) &&
	    atomisp_subdev_source_pad(vdev) !=
	    ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW &&
	    atomisp_subdev_source_pad(vdev) !=
	    ATOMISP_SUBDEV_PAD_SOURCE_VIDEO) अणु
		अगर (isp->inमाला_दो[asd->input_curr].camera_caps->multi_stream_ctrl) अणु
			v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
					 video, s_stream, 0);
		पूर्ण अन्यथा अगर (atomisp_subdev_source_pad(vdev)
			   == ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE) अणु
			/* stop continuous still capture अगर needed */
			अगर (asd->params.offline_parm.num_captures == -1)
				atomisp_css_offline_capture_configure(asd,
								      0, 0, 0);
			atomisp_freq_scaling(isp, ATOMISP_DFS_MODE_AUTO, false);
		पूर्ण
		/*
		 * Currently there is no way to flush buffers queued to css.
		 * When करोing videobuf_streamoff, active buffers will be
		 * marked as VIDEOBUF_NEEDS_INIT. HAL will be able to use
		 * these buffers again, and these buffers might be queued to
		 * css more than once! Warn here, अगर HAL has not dequeued all
		 * buffers back beक्रमe calling streamoff.
		 */
		अगर (pipe->buffers_in_css != 0) अणु
			WARN(1, "%s: buffers of vdev %s still in CSS!\n",
			     __func__, pipe->vdev.name);

			/*
			 * Buffers reमुख्यed in css maybe dequeued out in the
			 * next stream on, जबतक this will causes serious
			 * issues as buffers alपढ़ोy get invalid after
			 * previous stream off.
			 *
			 * No way to flush buffers but to reset the whole css
			 */
			dev_warn(isp->dev, "Reset CSS to clean up css buffers.\n");
			atomisp_css_flush(isp);
		पूर्ण

		वापस videobuf_streamoff(&pipe->capq);
	पूर्ण

	अगर (!pipe->capq.streaming)
		वापस 0;

	spin_lock_irqsave(&isp->lock, flags);
	अगर (asd->streaming == ATOMISP_DEVICE_STREAMING_ENABLED) अणु
		asd->streaming = ATOMISP_DEVICE_STREAMING_STOPPING;
		first_streamoff = true;
	पूर्ण
	spin_unlock_irqrestore(&isp->lock, flags);

	अगर (first_streamoff) अणु
		/* अगर other streams are running, should not disable watch करोg */
		rt_mutex_unlock(&isp->mutex);
		atomisp_wdt_stop(asd, true);

		/*
		 * must stop sending pixels पूर्णांकo GP_FIFO beक्रमe stop
		 * the pipeline.
		 */
		अगर (isp->sw_contex.file_input)
			v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
					 video, s_stream, 0);

		rt_mutex_lock(&isp->mutex);
		atomisp_acc_unload_extensions(asd);
	पूर्ण

	spin_lock_irqsave(&isp->lock, flags);
	अगर (atomisp_subdev_streaming_count(asd) == 1)
		asd->streaming = ATOMISP_DEVICE_STREAMING_DISABLED;
	spin_unlock_irqrestore(&isp->lock, flags);

	अगर (!first_streamoff) अणु
		ret = videobuf_streamoff(&pipe->capq);
		अगर (ret)
			वापस ret;
		जाओ stopsensor;
	पूर्ण

	atomisp_clear_css_buffer_counters(asd);

	अगर (!isp->sw_contex.file_input)
		atomisp_css_irq_enable(isp, IA_CSS_IRQ_INFO_CSS_RECEIVER_SOF,
				       false);

	अगर (asd->delayed_init == ATOMISP_DELAYED_INIT_QUEUED) अणु
		cancel_work_sync(&asd->delayed_init_work);
		asd->delayed_init = ATOMISP_DELAYED_INIT_NOT_QUEUED;
	पूर्ण
	अगर (first_streamoff) अणु
		css_pipe_id = atomisp_get_css_pipe_id(asd);
		atomisp_css_stop(asd, css_pipe_id, false);
	पूर्ण
	/* cancel work queue*/
	अगर (asd->video_out_capture.users) अणु
		capture_pipe = &asd->video_out_capture;
		wake_up_पूर्णांकerruptible(&capture_pipe->capq.रुको);
	पूर्ण
	अगर (asd->video_out_vf.users) अणु
		vf_pipe = &asd->video_out_vf;
		wake_up_पूर्णांकerruptible(&vf_pipe->capq.रुको);
	पूर्ण
	अगर (asd->video_out_preview.users) अणु
		preview_pipe = &asd->video_out_preview;
		wake_up_पूर्णांकerruptible(&preview_pipe->capq.रुको);
	पूर्ण
	अगर (asd->video_out_video_capture.users) अणु
		video_pipe = &asd->video_out_video_capture;
		wake_up_पूर्णांकerruptible(&video_pipe->capq.रुको);
	पूर्ण
	ret = videobuf_streamoff(&pipe->capq);
	अगर (ret)
		वापस ret;

	/* cleanup css here */
	/* no need क्रम this, as ISP will be reset anyway */
	/*atomisp_flush_bufs_in_css(isp);*/

	spin_lock_irqsave(&pipe->irq_lock, flags);
	list_क्रम_each_entry_safe(vb, _vb, &pipe->activeq, queue) अणु
		vb->state = VIDEOBUF_PREPARED;
		list_del(&vb->queue);
	पूर्ण
	list_क्रम_each_entry_safe(vb, _vb, &pipe->buffers_रुकोing_क्रम_param, queue) अणु
		vb->state = VIDEOBUF_PREPARED;
		list_del(&vb->queue);
		pipe->frame_request_config_id[vb->i] = 0;
	पूर्ण
	spin_unlock_irqrestore(&pipe->irq_lock, flags);

	atomisp_subdev_cleanup_pending_events(asd);
stopsensor:
	अगर (atomisp_subdev_streaming_count(asd) + 1
	    != atomisp_sensor_start_stream(asd))
		वापस 0;

	अगर (!isp->sw_contex.file_input)
		ret = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
				       video, s_stream, 0);

	अगर (isp->flash) अणु
		asd->params.num_flash_frames = 0;
		asd->params.flash_state = ATOMISP_FLASH_IDLE;
	पूर्ण

	/* अगर other streams are running, isp should not be घातered off */
	अगर (atomisp_streaming_count(isp)) अणु
		atomisp_css_flush(isp);
		वापस 0;
	पूर्ण

	/* Disable the CSI पूर्णांकerface on ANN B0/K0 */
	अगर (isp->media_dev.hw_revision >= ((ATOMISP_HW_REVISION_ISP2401 <<
					    ATOMISP_HW_REVISION_SHIFT) | ATOMISP_HW_STEPPING_B0)) अणु
		pci_ग_लिखो_config_word(pdev, MRFLD_PCI_CSI_CONTROL,
				      isp->saved_regs.csi_control & ~MRFLD_PCI_CSI_CONTROL_CSI_READY);
	पूर्ण

	अगर (atomisp_freq_scaling(isp, ATOMISP_DFS_MODE_LOW, false))
		dev_warn(isp->dev, "DFS failed.\n");
	/*
	 * ISP work around, need to reset isp
	 * Is it correct समय to reset ISP when first node करोes streamoff?
	 */
	अगर (isp->sw_contex.घातer_state == ATOM_ISP_POWER_UP) अणु
		अचिन्हित पूर्णांक i;
		bool recreate_streams[MAX_STREAM_NUM] = अणु0पूर्ण;

		अगर (isp->isp_समयout)
			dev_err(isp->dev, "%s: Resetting with WA activated",
				__func__);
		/*
		 * It is possible that the other asd stream is in the stage
		 * that v4l2_setfmt is just get called on it, which will
		 * create css stream on that stream. But at this poपूर्णांक, there
		 * is no way to destroy the css stream created on that stream.
		 *
		 * So क्रमce stream destroy here.
		 */
		क्रम (i = 0; i < isp->num_of_streams; i++) अणु
			अगर (isp->asd[i].stream_prepared) अणु
				atomisp_destroy_pipes_stream_क्रमce(&isp->
								   asd[i]);
				recreate_streams[i] = true;
			पूर्ण
		पूर्ण

		/* disable  PUNIT/ISP acknowlede/handshake - SRSE=3 */
		pci_ग_लिखो_config_dword(pdev, PCI_I_CONTROL,
				       isp->saved_regs.i_control | MRFLD_PCI_I_CONTROL_SRSE_RESET_MASK);
		dev_err(isp->dev, "atomisp_reset");
		atomisp_reset(isp);
		क्रम (i = 0; i < isp->num_of_streams; i++) अणु
			अगर (recreate_streams[i])
				atomisp_create_pipes_stream(&isp->asd[i]);
		पूर्ण
		isp->isp_समयout = false;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_streamoff(काष्ठा file *file, व्योम *fh,
			     क्रमागत v4l2_buf_type type)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	पूर्णांक rval;

	mutex_lock(&isp->streamoff_mutex);
	rt_mutex_lock(&isp->mutex);
	rval = __atomisp_streamoff(file, fh, type);
	rt_mutex_unlock(&isp->mutex);
	mutex_unlock(&isp->streamoff_mutex);

	वापस rval;
पूर्ण

/*
 * To get the current value of a control.
 * applications initialize the id field of a काष्ठा v4l2_control and
 * call this ioctl with a poपूर्णांकer to this काष्ठाure
 */
अटल पूर्णांक atomisp_g_ctrl(काष्ठा file *file, व्योम *fh,
			  काष्ठा v4l2_control *control)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_sub_device *asd = atomisp_to_video_pipe(vdev)->asd;
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	पूर्णांक i, ret = -EINVAL;

	क्रम (i = 0; i < ctrls_num; i++) अणु
		अगर (ci_v4l2_controls[i].id == control->id) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		वापस ret;

	rt_mutex_lock(&isp->mutex);

	चयन (control->id) अणु
	हाल V4L2_CID_IRIS_ABSOLUTE:
	हाल V4L2_CID_EXPOSURE_ABSOLUTE:
	हाल V4L2_CID_FNUMBER_ABSOLUTE:
	हाल V4L2_CID_2A_STATUS:
	हाल V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
	हाल V4L2_CID_EXPOSURE:
	हाल V4L2_CID_EXPOSURE_AUTO:
	हाल V4L2_CID_SCENE_MODE:
	हाल V4L2_CID_ISO_SENSITIVITY:
	हाल V4L2_CID_ISO_SENSITIVITY_AUTO:
	हाल V4L2_CID_CONTRAST:
	हाल V4L2_CID_SATURATION:
	हाल V4L2_CID_SHARPNESS:
	हाल V4L2_CID_3A_LOCK:
	हाल V4L2_CID_EXPOSURE_ZONE_NUM:
	हाल V4L2_CID_TEST_PATTERN:
	हाल V4L2_CID_TEST_PATTERN_COLOR_R:
	हाल V4L2_CID_TEST_PATTERN_COLOR_GR:
	हाल V4L2_CID_TEST_PATTERN_COLOR_GB:
	हाल V4L2_CID_TEST_PATTERN_COLOR_B:
		rt_mutex_unlock(&isp->mutex);
		वापस v4l2_g_ctrl(isp->inमाला_दो[asd->input_curr].camera->
				   ctrl_handler, control);
	हाल V4L2_CID_COLORFX:
		ret = atomisp_color_effect(asd, 0, &control->value);
		अवरोध;
	हाल V4L2_CID_ATOMISP_BAD_PIXEL_DETECTION:
		ret = atomisp_bad_pixel(asd, 0, &control->value);
		अवरोध;
	हाल V4L2_CID_ATOMISP_POSTPROCESS_GDC_CAC:
		ret = atomisp_gdc_cac(asd, 0, &control->value);
		अवरोध;
	हाल V4L2_CID_ATOMISP_VIDEO_STABLIZATION:
		ret = atomisp_video_stable(asd, 0, &control->value);
		अवरोध;
	हाल V4L2_CID_ATOMISP_FIXED_PATTERN_NR:
		ret = atomisp_fixed_pattern(asd, 0, &control->value);
		अवरोध;
	हाल V4L2_CID_ATOMISP_FALSE_COLOR_CORRECTION:
		ret = atomisp_false_color(asd, 0, &control->value);
		अवरोध;
	हाल V4L2_CID_ATOMISP_LOW_LIGHT:
		ret = atomisp_low_light(asd, 0, &control->value);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	rt_mutex_unlock(&isp->mutex);
	वापस ret;
पूर्ण

/*
 * To change the value of a control.
 * applications initialize the id and value fields of a काष्ठा v4l2_control
 * and call this ioctl.
 */
अटल पूर्णांक atomisp_s_ctrl(काष्ठा file *file, व्योम *fh,
			  काष्ठा v4l2_control *control)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_sub_device *asd = atomisp_to_video_pipe(vdev)->asd;
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	पूर्णांक i, ret = -EINVAL;

	क्रम (i = 0; i < ctrls_num; i++) अणु
		अगर (ci_v4l2_controls[i].id == control->id) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		वापस ret;

	rt_mutex_lock(&isp->mutex);
	चयन (control->id) अणु
	हाल V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
	हाल V4L2_CID_EXPOSURE:
	हाल V4L2_CID_EXPOSURE_AUTO:
	हाल V4L2_CID_EXPOSURE_AUTO_PRIORITY:
	हाल V4L2_CID_SCENE_MODE:
	हाल V4L2_CID_ISO_SENSITIVITY:
	हाल V4L2_CID_ISO_SENSITIVITY_AUTO:
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
	हाल V4L2_CID_EXPOSURE_METERING:
	हाल V4L2_CID_CONTRAST:
	हाल V4L2_CID_SATURATION:
	हाल V4L2_CID_SHARPNESS:
	हाल V4L2_CID_3A_LOCK:
	हाल V4L2_CID_COLORFX_CBCR:
	हाल V4L2_CID_TEST_PATTERN:
	हाल V4L2_CID_TEST_PATTERN_COLOR_R:
	हाल V4L2_CID_TEST_PATTERN_COLOR_GR:
	हाल V4L2_CID_TEST_PATTERN_COLOR_GB:
	हाल V4L2_CID_TEST_PATTERN_COLOR_B:
		rt_mutex_unlock(&isp->mutex);
		वापस v4l2_s_ctrl(शून्य,
				   isp->inमाला_दो[asd->input_curr].camera->
				   ctrl_handler, control);
	हाल V4L2_CID_COLORFX:
		ret = atomisp_color_effect(asd, 1, &control->value);
		अवरोध;
	हाल V4L2_CID_ATOMISP_BAD_PIXEL_DETECTION:
		ret = atomisp_bad_pixel(asd, 1, &control->value);
		अवरोध;
	हाल V4L2_CID_ATOMISP_POSTPROCESS_GDC_CAC:
		ret = atomisp_gdc_cac(asd, 1, &control->value);
		अवरोध;
	हाल V4L2_CID_ATOMISP_VIDEO_STABLIZATION:
		ret = atomisp_video_stable(asd, 1, &control->value);
		अवरोध;
	हाल V4L2_CID_ATOMISP_FIXED_PATTERN_NR:
		ret = atomisp_fixed_pattern(asd, 1, &control->value);
		अवरोध;
	हाल V4L2_CID_ATOMISP_FALSE_COLOR_CORRECTION:
		ret = atomisp_false_color(asd, 1, &control->value);
		अवरोध;
	हाल V4L2_CID_REQUEST_FLASH:
		ret = atomisp_flash_enable(asd, control->value);
		अवरोध;
	हाल V4L2_CID_ATOMISP_LOW_LIGHT:
		ret = atomisp_low_light(asd, 1, &control->value);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	rt_mutex_unlock(&isp->mutex);
	वापस ret;
पूर्ण

/*
 * To query the attributes of a control.
 * applications set the id field of a काष्ठा v4l2_queryctrl and call the
 * this ioctl with a poपूर्णांकer to this काष्ठाure. The driver fills
 * the rest of the काष्ठाure.
 */
अटल पूर्णांक atomisp_queryctl(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_queryctrl *qc)
अणु
	पूर्णांक i, ret = -EINVAL;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_sub_device *asd = atomisp_to_video_pipe(vdev)->asd;
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);

	चयन (qc->id) अणु
	हाल V4L2_CID_FOCUS_ABSOLUTE:
	हाल V4L2_CID_FOCUS_RELATIVE:
	हाल V4L2_CID_FOCUS_STATUS:
		अगर (!IS_ISP2401) अणु
			वापस v4l2_queryctrl(isp->inमाला_दो[asd->input_curr].camera->
					    ctrl_handler, qc);
		पूर्ण
		/* ISP2401 */
		अगर (isp->motor)
			वापस v4l2_queryctrl(isp->motor->ctrl_handler, qc);
		अन्यथा
			वापस v4l2_queryctrl(isp->inमाला_दो[asd->input_curr].
					      camera->ctrl_handler, qc);
	पूर्ण

	अगर (qc->id & V4L2_CTRL_FLAG_NEXT_CTRL)
		वापस ret;

	क्रम (i = 0; i < ctrls_num; i++) अणु
		अगर (ci_v4l2_controls[i].id == qc->id) अणु
			स_नकल(qc, &ci_v4l2_controls[i],
			       माप(काष्ठा v4l2_queryctrl));
			qc->reserved[0] = 0;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ret != 0)
		qc->flags = V4L2_CTRL_FLAG_DISABLED;

	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_camera_g_ext_ctrls(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_ext_controls *c)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_sub_device *asd = atomisp_to_video_pipe(vdev)->asd;
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा v4l2_subdev *motor;
	काष्ठा v4l2_control ctrl;
	पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (!IS_ISP2401)
		motor = isp->inमाला_दो[asd->input_curr].motor;
	अन्यथा
		motor = isp->motor;

	क्रम (i = 0; i < c->count; i++) अणु
		ctrl.id = c->controls[i].id;
		ctrl.value = c->controls[i].value;
		चयन (ctrl.id) अणु
		हाल V4L2_CID_EXPOSURE_ABSOLUTE:
		हाल V4L2_CID_EXPOSURE_AUTO:
		हाल V4L2_CID_IRIS_ABSOLUTE:
		हाल V4L2_CID_FNUMBER_ABSOLUTE:
		हाल V4L2_CID_BIN_FACTOR_HORZ:
		हाल V4L2_CID_BIN_FACTOR_VERT:
		हाल V4L2_CID_3A_LOCK:
		हाल V4L2_CID_TEST_PATTERN:
		हाल V4L2_CID_TEST_PATTERN_COLOR_R:
		हाल V4L2_CID_TEST_PATTERN_COLOR_GR:
		हाल V4L2_CID_TEST_PATTERN_COLOR_GB:
		हाल V4L2_CID_TEST_PATTERN_COLOR_B:
			/*
			 * Exposure related control will be handled by sensor
			 * driver
			 */
			ret =
			    v4l2_g_ctrl(isp->inमाला_दो[asd->input_curr].camera->
					ctrl_handler, &ctrl);
			अवरोध;
		हाल V4L2_CID_FOCUS_ABSOLUTE:
		हाल V4L2_CID_FOCUS_RELATIVE:
		हाल V4L2_CID_FOCUS_STATUS:
		हाल V4L2_CID_FOCUS_AUTO:
			अगर (motor)
				ret = v4l2_g_ctrl(motor->ctrl_handler, &ctrl);
			अवरोध;
		हाल V4L2_CID_FLASH_STATUS:
		हाल V4L2_CID_FLASH_INTENSITY:
		हाल V4L2_CID_FLASH_TORCH_INTENSITY:
		हाल V4L2_CID_FLASH_INDICATOR_INTENSITY:
		हाल V4L2_CID_FLASH_TIMEOUT:
		हाल V4L2_CID_FLASH_STROBE:
		हाल V4L2_CID_FLASH_MODE:
		हाल V4L2_CID_FLASH_STATUS_REGISTER:
			अगर (isp->flash)
				ret =
				    v4l2_g_ctrl(isp->flash->ctrl_handler,
						&ctrl);
			अवरोध;
		हाल V4L2_CID_ZOOM_ABSOLUTE:
			rt_mutex_lock(&isp->mutex);
			ret = atomisp_digital_zoom(asd, 0, &ctrl.value);
			rt_mutex_unlock(&isp->mutex);
			अवरोध;
		हाल V4L2_CID_G_SKIP_FRAMES:
			ret = v4l2_subdev_call(
				  isp->inमाला_दो[asd->input_curr].camera,
				  sensor, g_skip_frames, (u32 *)&ctrl.value);
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण

		अगर (ret) अणु
			c->error_idx = i;
			अवरोध;
		पूर्ण
		c->controls[i].value = ctrl.value;
	पूर्ण
	वापस ret;
पूर्ण

/* This ioctl allows the application to get multiple controls by class */
अटल पूर्णांक atomisp_g_ext_ctrls(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_ext_controls *c)
अणु
	काष्ठा v4l2_control ctrl;
	पूर्णांक i, ret = 0;

	/*
	 * input_lock is not need क्रम the Camera related IOCTLs
	 * The input_lock करोwngrade the FPS of 3A
	 */
	ret = atomisp_camera_g_ext_ctrls(file, fh, c);
	अगर (ret != -EINVAL)
		वापस ret;

	क्रम (i = 0; i < c->count; i++) अणु
		ctrl.id = c->controls[i].id;
		ctrl.value = c->controls[i].value;
		ret = atomisp_g_ctrl(file, fh, &ctrl);
		c->controls[i].value = ctrl.value;
		अगर (ret) अणु
			c->error_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_camera_s_ext_ctrls(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_ext_controls *c)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_sub_device *asd = atomisp_to_video_pipe(vdev)->asd;
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा v4l2_subdev *motor;
	काष्ठा v4l2_control ctrl;
	पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (!IS_ISP2401)
		motor = isp->inमाला_दो[asd->input_curr].motor;
	अन्यथा
		motor = isp->motor;

	क्रम (i = 0; i < c->count; i++) अणु
		काष्ठा v4l2_ctrl *ctr;

		ctrl.id = c->controls[i].id;
		ctrl.value = c->controls[i].value;
		चयन (ctrl.id) अणु
		हाल V4L2_CID_EXPOSURE_ABSOLUTE:
		हाल V4L2_CID_EXPOSURE_AUTO:
		हाल V4L2_CID_EXPOSURE_METERING:
		हाल V4L2_CID_IRIS_ABSOLUTE:
		हाल V4L2_CID_FNUMBER_ABSOLUTE:
		हाल V4L2_CID_VCM_TIMING:
		हाल V4L2_CID_VCM_SLEW:
		हाल V4L2_CID_3A_LOCK:
		हाल V4L2_CID_TEST_PATTERN:
		हाल V4L2_CID_TEST_PATTERN_COLOR_R:
		हाल V4L2_CID_TEST_PATTERN_COLOR_GR:
		हाल V4L2_CID_TEST_PATTERN_COLOR_GB:
		हाल V4L2_CID_TEST_PATTERN_COLOR_B:
			ret = v4l2_s_ctrl(शून्य,
					  isp->inमाला_दो[asd->input_curr].camera->
					  ctrl_handler, &ctrl);
			अवरोध;
		हाल V4L2_CID_FOCUS_ABSOLUTE:
		हाल V4L2_CID_FOCUS_RELATIVE:
		हाल V4L2_CID_FOCUS_STATUS:
		हाल V4L2_CID_FOCUS_AUTO:
			अगर (motor)
				ret = v4l2_s_ctrl(शून्य, motor->ctrl_handler,
						  &ctrl);
			अन्यथा
				ret = v4l2_s_ctrl(शून्य,
						  isp->inमाला_दो[asd->input_curr].
						  camera->ctrl_handler, &ctrl);
			अवरोध;
		हाल V4L2_CID_FLASH_STATUS:
		हाल V4L2_CID_FLASH_INTENSITY:
		हाल V4L2_CID_FLASH_TORCH_INTENSITY:
		हाल V4L2_CID_FLASH_INDICATOR_INTENSITY:
		हाल V4L2_CID_FLASH_TIMEOUT:
		हाल V4L2_CID_FLASH_STROBE:
		हाल V4L2_CID_FLASH_MODE:
		हाल V4L2_CID_FLASH_STATUS_REGISTER:
			rt_mutex_lock(&isp->mutex);
			अगर (isp->flash) अणु
				ret =
				    v4l2_s_ctrl(शून्य, isp->flash->ctrl_handler,
						&ctrl);
				/*
				 * When flash mode is changed we need to reset
				 * flash state
				 */
				अगर (ctrl.id == V4L2_CID_FLASH_MODE) अणु
					asd->params.flash_state =
					    ATOMISP_FLASH_IDLE;
					asd->params.num_flash_frames = 0;
				पूर्ण
			पूर्ण
			rt_mutex_unlock(&isp->mutex);
			अवरोध;
		हाल V4L2_CID_ZOOM_ABSOLUTE:
			rt_mutex_lock(&isp->mutex);
			ret = atomisp_digital_zoom(asd, 1, &ctrl.value);
			rt_mutex_unlock(&isp->mutex);
			अवरोध;
		शेष:
			ctr = v4l2_ctrl_find(&asd->ctrl_handler, ctrl.id);
			अगर (ctr)
				ret = v4l2_ctrl_s_ctrl(ctr, ctrl.value);
			अन्यथा
				ret = -EINVAL;
		पूर्ण

		अगर (ret) अणु
			c->error_idx = i;
			अवरोध;
		पूर्ण
		c->controls[i].value = ctrl.value;
	पूर्ण
	वापस ret;
पूर्ण

/* This ioctl allows the application to set multiple controls by class */
अटल पूर्णांक atomisp_s_ext_ctrls(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_ext_controls *c)
अणु
	काष्ठा v4l2_control ctrl;
	पूर्णांक i, ret = 0;

	/*
	 * input_lock is not need क्रम the Camera related IOCTLs
	 * The input_lock करोwngrade the FPS of 3A
	 */
	ret = atomisp_camera_s_ext_ctrls(file, fh, c);
	अगर (ret != -EINVAL)
		वापस ret;

	क्रम (i = 0; i < c->count; i++) अणु
		ctrl.id = c->controls[i].id;
		ctrl.value = c->controls[i].value;
		ret = atomisp_s_ctrl(file, fh, &ctrl);
		c->controls[i].value = ctrl.value;
		अगर (ret) अणु
			c->error_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * vidioc_g/s_param are used to चयन isp running mode
 */
अटल पूर्णांक atomisp_g_parm(काष्ठा file *file, व्योम *fh,
			  काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_sub_device *asd = atomisp_to_video_pipe(vdev)->asd;
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);

	अगर (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		dev_err(isp->dev, "unsupported v4l2 buf type\n");
		वापस -EINVAL;
	पूर्ण

	rt_mutex_lock(&isp->mutex);
	parm->parm.capture.capturemode = asd->run_mode->val;
	rt_mutex_unlock(&isp->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक atomisp_s_parm(काष्ठा file *file, व्योम *fh,
			  काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_sub_device *asd = atomisp_to_video_pipe(vdev)->asd;
	पूर्णांक mode;
	पूर्णांक rval;
	पूर्णांक fps;

	अगर (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		dev_err(isp->dev, "unsupported v4l2 buf type\n");
		वापस -EINVAL;
	पूर्ण

	rt_mutex_lock(&isp->mutex);

	asd->high_speed_mode = false;
	चयन (parm->parm.capture.capturemode) अणु
	हाल CI_MODE_NONE: अणु
		काष्ठा v4l2_subdev_frame_पूर्णांकerval fi = अणु0पूर्ण;

		fi.पूर्णांकerval = parm->parm.capture.समयperframe;

		rval = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
					video, s_frame_पूर्णांकerval, &fi);
		अगर (!rval)
			parm->parm.capture.समयperframe = fi.पूर्णांकerval;

		अगर (fi.पूर्णांकerval.numerator != 0) अणु
			fps = fi.पूर्णांकerval.denominator / fi.पूर्णांकerval.numerator;
			अगर (fps > 30)
				asd->high_speed_mode = true;
		पूर्ण

		जाओ out;
	पूर्ण
	हाल CI_MODE_VIDEO:
		mode = ATOMISP_RUN_MODE_VIDEO;
		अवरोध;
	हाल CI_MODE_STILL_CAPTURE:
		mode = ATOMISP_RUN_MODE_STILL_CAPTURE;
		अवरोध;
	हाल CI_MODE_CONTINUOUS:
		mode = ATOMISP_RUN_MODE_CONTINUOUS_CAPTURE;
		अवरोध;
	हाल CI_MODE_PREVIEW:
		mode = ATOMISP_RUN_MODE_PREVIEW;
		अवरोध;
	शेष:
		rval = -EINVAL;
		जाओ out;
	पूर्ण

	rval = v4l2_ctrl_s_ctrl(asd->run_mode, mode);

out:
	rt_mutex_unlock(&isp->mutex);

	वापस rval == -ENOIOCTLCMD ? 0 : rval;
पूर्ण

अटल पूर्णांक atomisp_s_parm_file(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);

	अगर (parm->type != V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		dev_err(isp->dev, "unsupported v4l2 buf type for output\n");
		वापस -EINVAL;
	पूर्ण

	rt_mutex_lock(&isp->mutex);
	isp->sw_contex.file_input = true;
	rt_mutex_unlock(&isp->mutex);

	वापस 0;
पूर्ण

अटल दीर्घ atomisp_vidioc_शेष(काष्ठा file *file, व्योम *fh,
				   bool valid_prio, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_sub_device *asd;
	काष्ठा v4l2_subdev *motor;
	bool acc_node;
	पूर्णांक err;

	acc_node = !म_भेद(vdev->name, "ATOMISP ISP ACC");
	अगर (acc_node)
		asd = atomisp_to_acc_pipe(vdev)->asd;
	अन्यथा
		asd = atomisp_to_video_pipe(vdev)->asd;

	अगर (!IS_ISP2401)
		motor = isp->inमाला_दो[asd->input_curr].motor;
	अन्यथा
		motor = isp->motor;

	चयन (cmd) अणु
	हाल ATOMISP_IOC_G_MOTOR_PRIV_INT_DATA:
	हाल ATOMISP_IOC_S_EXPOSURE:
	हाल ATOMISP_IOC_G_SENSOR_CALIBRATION_GROUP:
	हाल ATOMISP_IOC_G_SENSOR_PRIV_INT_DATA:
	हाल ATOMISP_IOC_EXT_ISP_CTRL:
	हाल ATOMISP_IOC_G_SENSOR_AE_BRACKETING_INFO:
	हाल ATOMISP_IOC_S_SENSOR_AE_BRACKETING_MODE:
	हाल ATOMISP_IOC_G_SENSOR_AE_BRACKETING_MODE:
	हाल ATOMISP_IOC_S_SENSOR_AE_BRACKETING_LUT:
	हाल ATOMISP_IOC_S_SENSOR_EE_CONFIG:
	हाल ATOMISP_IOC_G_UPDATE_EXPOSURE:
		/* we करो not need take isp->mutex क्रम these IOCTLs */
		अवरोध;
	शेष:
		rt_mutex_lock(&isp->mutex);
		अवरोध;
	पूर्ण
	चयन (cmd) अणु
	हाल ATOMISP_IOC_S_SENSOR_RUNMODE:
		अगर (IS_ISP2401)
			err = atomisp_set_sensor_runmode(asd, arg);
		अन्यथा
			err = -EINVAL;
		अवरोध;

	हाल ATOMISP_IOC_G_XNR:
		err = atomisp_xnr(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_XNR:
		err = atomisp_xnr(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_NR:
		err = atomisp_nr(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_NR:
		err = atomisp_nr(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_TNR:
		err = atomisp_tnr(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_TNR:
		err = atomisp_tnr(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_BLACK_LEVEL_COMP:
		err = atomisp_black_level(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_BLACK_LEVEL_COMP:
		err = atomisp_black_level(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_EE:
		err = atomisp_ee(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_EE:
		err = atomisp_ee(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_DIS_STAT:
		err = atomisp_get_dis_stat(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_DVS2_BQ_RESOLUTIONS:
		err = atomisp_get_dvs2_bq_resolutions(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_DIS_COEFS:
		err = atomisp_css_cp_dvs2_coefs(asd, arg,
						&asd->params.css_param, true);
		अगर (!err && arg)
			asd->params.css_update_params_needed = true;
		अवरोध;

	हाल ATOMISP_IOC_S_DIS_VECTOR:
		err = atomisp_cp_dvs_6axis_config(asd, arg,
						  &asd->params.css_param, true);
		अगर (!err && arg)
			asd->params.css_update_params_needed = true;
		अवरोध;

	हाल ATOMISP_IOC_G_ISP_PARM:
		err = atomisp_param(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_ISP_PARM:
		err = atomisp_param(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_3A_STAT:
		err = atomisp_3a_stat(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_ISP_GAMMA:
		err = atomisp_gamma(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_ISP_GAMMA:
		err = atomisp_gamma(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_ISP_GDC_TAB:
		err = atomisp_gdc_cac_table(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_ISP_GDC_TAB:
		err = atomisp_gdc_cac_table(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_ISP_MACC:
		err = atomisp_macc_table(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_ISP_MACC:
		err = atomisp_macc_table(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_ISP_BAD_PIXEL_DETECTION:
		err = atomisp_bad_pixel_param(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_ISP_BAD_PIXEL_DETECTION:
		err = atomisp_bad_pixel_param(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_ISP_FALSE_COLOR_CORRECTION:
		err = atomisp_false_color_param(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_ISP_FALSE_COLOR_CORRECTION:
		err = atomisp_false_color_param(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_ISP_CTC:
		err = atomisp_ctc(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_ISP_CTC:
		err = atomisp_ctc(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_ISP_WHITE_BALANCE:
		err = atomisp_white_balance_param(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_ISP_WHITE_BALANCE:
		err = atomisp_white_balance_param(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_3A_CONFIG:
		err = atomisp_3a_config_param(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_3A_CONFIG:
		err = atomisp_3a_config_param(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_ISP_FPN_TABLE:
		err = atomisp_fixed_pattern_table(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_ISP_MAKERNOTE:
		err = atomisp_exअगर_makernote(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_SENSOR_MODE_DATA:
		err = atomisp_get_sensor_mode_data(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_MOTOR_PRIV_INT_DATA:
		अगर (motor)
			err = v4l2_subdev_call(motor, core, ioctl, cmd, arg);
		अन्यथा
			err = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
					       core, ioctl, cmd, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_EXPOSURE:
	हाल ATOMISP_IOC_G_SENSOR_CALIBRATION_GROUP:
	हाल ATOMISP_IOC_G_SENSOR_PRIV_INT_DATA:
	हाल ATOMISP_IOC_G_SENSOR_AE_BRACKETING_INFO:
	हाल ATOMISP_IOC_S_SENSOR_AE_BRACKETING_MODE:
	हाल ATOMISP_IOC_G_SENSOR_AE_BRACKETING_MODE:
	हाल ATOMISP_IOC_S_SENSOR_AE_BRACKETING_LUT:
		err = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
				       core, ioctl, cmd, arg);
		अवरोध;
	हाल ATOMISP_IOC_G_UPDATE_EXPOSURE:
		अगर (IS_ISP2401)
			err = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
					       core, ioctl, cmd, arg);
		अन्यथा
			err = -EINVAL;
		अवरोध;

	हाल ATOMISP_IOC_ACC_LOAD:
		err = atomisp_acc_load(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_ACC_LOAD_TO_PIPE:
		err = atomisp_acc_load_to_pipe(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_ACC_UNLOAD:
		err = atomisp_acc_unload(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_ACC_START:
		err = atomisp_acc_start(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_ACC_WAIT:
		err = atomisp_acc_रुको(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_ACC_MAP:
		err = atomisp_acc_map(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_ACC_UNMAP:
		err = atomisp_acc_unmap(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_ACC_S_MAPPED_ARG:
		err = atomisp_acc_s_mapped_arg(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_ISP_SHD_TAB:
		err = atomisp_set_shading_table(asd, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_ISP_GAMMA_CORRECTION:
		err = atomisp_gamma_correction(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_ISP_GAMMA_CORRECTION:
		err = atomisp_gamma_correction(asd, 1, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_PARAMETERS:
		err = atomisp_set_parameters(vdev, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_CONT_CAPTURE_CONFIG:
		err = atomisp_offline_capture_configure(asd, arg);
		अवरोध;
	हाल ATOMISP_IOC_G_METADATA:
		err = atomisp_get_metadata(asd, 0, arg);
		अवरोध;
	हाल ATOMISP_IOC_G_METADATA_BY_TYPE:
		err = atomisp_get_metadata_by_type(asd, 0, arg);
		अवरोध;
	हाल ATOMISP_IOC_EXT_ISP_CTRL:
		err = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
				       core, ioctl, cmd, arg);
		अवरोध;
	हाल ATOMISP_IOC_EXP_ID_UNLOCK:
		err = atomisp_exp_id_unlock(asd, arg);
		अवरोध;
	हाल ATOMISP_IOC_EXP_ID_CAPTURE:
		err = atomisp_exp_id_capture(asd, arg);
		अवरोध;
	हाल ATOMISP_IOC_S_ENABLE_DZ_CAPT_PIPE:
		err = atomisp_enable_dz_capt_pipe(asd, arg);
		अवरोध;
	हाल ATOMISP_IOC_G_FORMATS_CONFIG:
		err = atomisp_क्रमmats(asd, 0, arg);
		अवरोध;

	हाल ATOMISP_IOC_S_FORMATS_CONFIG:
		err = atomisp_क्रमmats(asd, 1, arg);
		अवरोध;
	हाल ATOMISP_IOC_S_EXPOSURE_WINDOW:
		err = atomisp_s_ae_winकरोw(asd, arg);
		अवरोध;
	हाल ATOMISP_IOC_S_ACC_STATE:
		err = atomisp_acc_set_state(asd, arg);
		अवरोध;
	हाल ATOMISP_IOC_G_ACC_STATE:
		err = atomisp_acc_get_state(asd, arg);
		अवरोध;
	हाल ATOMISP_IOC_INJECT_A_FAKE_EVENT:
		err = atomisp_inject_a_fake_event(asd, arg);
		अवरोध;
	हाल ATOMISP_IOC_G_INVALID_FRAME_NUM:
		err = atomisp_get_invalid_frame_num(vdev, arg);
		अवरोध;
	हाल ATOMISP_IOC_S_ARRAY_RESOLUTION:
		err = atomisp_set_array_res(asd, arg);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	चयन (cmd) अणु
	हाल ATOMISP_IOC_G_MOTOR_PRIV_INT_DATA:
	हाल ATOMISP_IOC_S_EXPOSURE:
	हाल ATOMISP_IOC_G_SENSOR_CALIBRATION_GROUP:
	हाल ATOMISP_IOC_G_SENSOR_PRIV_INT_DATA:
	हाल ATOMISP_IOC_EXT_ISP_CTRL:
	हाल ATOMISP_IOC_G_SENSOR_AE_BRACKETING_INFO:
	हाल ATOMISP_IOC_S_SENSOR_AE_BRACKETING_MODE:
	हाल ATOMISP_IOC_G_SENSOR_AE_BRACKETING_MODE:
	हाल ATOMISP_IOC_S_SENSOR_AE_BRACKETING_LUT:
	हाल ATOMISP_IOC_G_UPDATE_EXPOSURE:
		अवरोध;
	शेष:
		rt_mutex_unlock(&isp->mutex);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

स्थिर काष्ठा v4l2_ioctl_ops atomisp_ioctl_ops = अणु
	.vidioc_querycap = atomisp_querycap,
	.vidioc_क्रमागत_input = atomisp_क्रमागत_input,
	.vidioc_g_input = atomisp_g_input,
	.vidioc_s_input = atomisp_s_input,
	.vidioc_queryctrl = atomisp_queryctl,
	.vidioc_s_ctrl = atomisp_s_ctrl,
	.vidioc_g_ctrl = atomisp_g_ctrl,
	.vidioc_s_ext_ctrls = atomisp_s_ext_ctrls,
	.vidioc_g_ext_ctrls = atomisp_g_ext_ctrls,
	.vidioc_क्रमागत_fmt_vid_cap = atomisp_क्रमागत_fmt_cap,
	.vidioc_try_fmt_vid_cap = atomisp_try_fmt_cap,
	.vidioc_g_fmt_vid_cap = atomisp_g_fmt_cap,
	.vidioc_s_fmt_vid_cap = atomisp_s_fmt_cap,
	.vidioc_reqbufs = atomisp_reqbufs,
	.vidioc_querybuf = atomisp_querybuf,
	.vidioc_qbuf = atomisp_qbuf,
	.vidioc_dqbuf = atomisp_dqbuf,
	.vidioc_streamon = atomisp_streamon,
	.vidioc_streamoff = atomisp_streamoff,
	.vidioc_शेष = atomisp_vidioc_शेष,
	.vidioc_s_parm = atomisp_s_parm,
	.vidioc_g_parm = atomisp_g_parm,
पूर्ण;

स्थिर काष्ठा v4l2_ioctl_ops atomisp_file_ioctl_ops = अणु
	.vidioc_querycap = atomisp_querycap,
	.vidioc_g_fmt_vid_out = atomisp_g_fmt_file,
	.vidioc_s_fmt_vid_out = atomisp_s_fmt_file,
	.vidioc_s_parm = atomisp_s_parm_file,
	.vidioc_reqbufs = atomisp_reqbufs_file,
	.vidioc_querybuf = atomisp_querybuf_file,
	.vidioc_qbuf = atomisp_qbuf_file,
पूर्ण;
