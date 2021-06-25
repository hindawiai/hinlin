<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * USB IBM C-It Video Camera driver
 *
 * Supports Xirlink C-It Video Camera, IBM PC Camera,
 * IBM NetCamera and Veo Stingray.
 *
 * Copyright (C) 2010 Hans de Goede <hdegoede@redhat.com>
 *
 * This driver is based on earlier work of:
 *
 * (C) Copyright 1999 Johannes Erdfelt
 * (C) Copyright 1999 Randy Dunlap
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "xirlink-cit"

#समावेश <linux/input.h>
#समावेश "gspca.h"

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Xirlink C-IT");
MODULE_LICENSE("GPL");

/* FIXME we should स्वतःdetect this */
अटल पूर्णांक ibm_netcam_pro;
module_param(ibm_netcam_pro, पूर्णांक, 0);
MODULE_PARM_DESC(ibm_netcam_pro,
		 "Use IBM Netcamera Pro init sequences for Model 3 cams");

/* FIXME this should be handled through the V4L2 input selection API */
अटल पूर्णांक rca_input;
module_param(rca_input, पूर्णांक, 0644);
MODULE_PARM_DESC(rca_input,
		 "Use rca input instead of ccd sensor on Model 3 cams");

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;		/* !! must be the first item */
	काष्ठा v4l2_ctrl *lighting;
	u8 model;
#घोषणा CIT_MODEL0 0 /* bcd version 0.01 cams ie the xvp-500 */
#घोषणा CIT_MODEL1 1 /* The model 1 - 4 nomenclature comes from the old */
#घोषणा CIT_MODEL2 2 /* ibmcam driver */
#घोषणा CIT_MODEL3 3
#घोषणा CIT_MODEL4 4
#घोषणा CIT_IBM_NETCAM_PRO 5
	u8 input_index;
	u8 button_state;
	u8 stop_on_control_change;
	u8 sof_पढ़ो;
	u8 sof_len;
पूर्ण;

अटल व्योम sd_stop0(काष्ठा gspca_dev *gspca_dev);

अटल स्थिर काष्ठा v4l2_pix_क्रमmat cअगर_yuv_mode[] = अणु
	अणु176, 144, V4L2_PIX_FMT_CIT_YYVYUY, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144 * 3 / 2 + 4,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु352, 288, V4L2_PIX_FMT_CIT_YYVYUY, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288 * 3 / 2 + 4,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_yuv_mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_CIT_YYVYUY, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 160 * 120 * 3 / 2 + 4,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु320, 240, V4L2_PIX_FMT_CIT_YYVYUY, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 2 + 4,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु640, 480, V4L2_PIX_FMT_CIT_YYVYUY, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 2 + 4,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat model0_mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_CIT_YYVYUY, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 160 * 120 * 3 / 2 + 4,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु176, 144, V4L2_PIX_FMT_CIT_YYVYUY, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144 * 3 / 2 + 4,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु320, 240, V4L2_PIX_FMT_CIT_YYVYUY, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 2 + 4,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat model2_mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_CIT_YYVYUY, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 160 * 120 * 3 / 2 + 4,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु176, 144, V4L2_PIX_FMT_CIT_YYVYUY, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144 * 3 / 2 + 4,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु320, 240, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 + 4,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु352, 288, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288 + 4,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
पूर्ण;

/*
 * 01.01.08 - Added क्रम RCA video in support -LO
 * This काष्ठा is used to init the Model3 cam to use the RCA video in port
 * instead of the CCD sensor.
 */
अटल स्थिर u16 rca_initdata[][3] = अणु
	अणु0, 0x0000, 0x010cपूर्ण,
	अणु0, 0x0006, 0x012cपूर्ण,
	अणु0, 0x0078, 0x012dपूर्ण,
	अणु0, 0x0046, 0x012fपूर्ण,
	अणु0, 0xd141, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfea8, 0x0124पूर्ण,
	अणु1, 0x0000, 0x0116पूर्ण,
	अणु0, 0x0064, 0x0116पूर्ण,
	अणु1, 0x0000, 0x0115पूर्ण,
	अणु0, 0x0003, 0x0115पूर्ण,
	अणु0, 0x0008, 0x0123पूर्ण,
	अणु0, 0x0000, 0x0117पूर्ण,
	अणु0, 0x0000, 0x0112पूर्ण,
	अणु0, 0x0080, 0x0100पूर्ण,
	अणु0, 0x0000, 0x0100पूर्ण,
	अणु1, 0x0000, 0x0116पूर्ण,
	अणु0, 0x0060, 0x0116पूर्ण,
	अणु0, 0x0002, 0x0112पूर्ण,
	अणु0, 0x0000, 0x0123पूर्ण,
	अणु0, 0x0001, 0x0117पूर्ण,
	अणु0, 0x0040, 0x0108पूर्ण,
	अणु0, 0x0019, 0x012cपूर्ण,
	अणु0, 0x0040, 0x0116पूर्ण,
	अणु0, 0x000a, 0x0115पूर्ण,
	अणु0, 0x000b, 0x0115पूर्ण,
	अणु0, 0x0078, 0x012dपूर्ण,
	अणु0, 0x0046, 0x012fपूर्ण,
	अणु0, 0xd141, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfea8, 0x0124पूर्ण,
	अणु0, 0x0064, 0x0116पूर्ण,
	अणु0, 0x0000, 0x0115पूर्ण,
	अणु0, 0x0001, 0x0115पूर्ण,
	अणु0, 0xffff, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x00aa, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xffff, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x00f2, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x000f, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xffff, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x00f8, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x00fc, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xffff, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x00f9, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x003c, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xffff, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0027, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0019, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0021, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0006, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0045, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x002a, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x000e, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x002b, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x00f4, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x002c, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0004, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x002d, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0014, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x002e, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0003, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x002f, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0003, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0014, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0040, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0040, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0053, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0101पूर्ण,
	अणु0, 0x00a0, 0x0103पूर्ण,
	अणु0, 0x0078, 0x0105पूर्ण,
	अणु0, 0x0000, 0x010aपूर्ण,
	अणु0, 0x0024, 0x010bपूर्ण,
	अणु0, 0x0028, 0x0119पूर्ण,
	अणु0, 0x0088, 0x011bपूर्ण,
	अणु0, 0x0002, 0x011dपूर्ण,
	अणु0, 0x0003, 0x011eपूर्ण,
	अणु0, 0x0000, 0x0129पूर्ण,
	अणु0, 0x00fc, 0x012bपूर्ण,
	अणु0, 0x0008, 0x0102पूर्ण,
	अणु0, 0x0000, 0x0104पूर्ण,
	अणु0, 0x0008, 0x011aपूर्ण,
	अणु0, 0x0028, 0x011cपूर्ण,
	अणु0, 0x0021, 0x012aपूर्ण,
	अणु0, 0x0000, 0x0118पूर्ण,
	अणु0, 0x0000, 0x0132पूर्ण,
	अणु0, 0x0000, 0x0109पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0031, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0040, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0040, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x00dc, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0032, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0020, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0001, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0040, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0040, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0037, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0030, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0xfff9, 0x0124पूर्ण,
	अणु0, 0x0086, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0038, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0008, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0x0000, 0x0127पूर्ण,
	अणु0, 0xfff8, 0x0124पूर्ण,
	अणु0, 0xfffd, 0x0124पूर्ण,
	अणु0, 0xfffa, 0x0124पूर्ण,
	अणु0, 0x0003, 0x0111पूर्ण,
पूर्ण;

/* TESTME the old ibmcam driver repeats certain commands to Model1 cameras, we
   करो the same क्रम now (testing needed to see अगर this is really necessary) */
अटल स्थिर पूर्णांक cit_model1_ntries = 5;
अटल स्थिर पूर्णांक cit_model1_ntries2 = 2;

अटल पूर्णांक cit_ग_लिखो_reg(काष्ठा gspca_dev *gspca_dev, u16 value, u16 index)
अणु
	काष्ठा usb_device *udev = gspca_dev->dev;
	पूर्णांक err;

	err = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 0x00,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_ENDPOINT,
			value, index, शून्य, 0, 1000);
	अगर (err < 0)
		pr_err("Failed to write a register (index 0x%04X, value 0x%02X, error %d)\n",
		       index, value, err);

	वापस 0;
पूर्ण

अटल पूर्णांक cit_पढ़ो_reg(काष्ठा gspca_dev *gspca_dev, u16 index, पूर्णांक verbose)
अणु
	काष्ठा usb_device *udev = gspca_dev->dev;
	__u8 *buf = gspca_dev->usb_buf;
	पूर्णांक res;

	res = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), 0x01,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_ENDPOINT,
			0x00, index, buf, 8, 1000);
	अगर (res < 0) अणु
		pr_err("Failed to read a register (index 0x%04X, error %d)\n",
		       index, res);
		वापस res;
	पूर्ण

	अगर (verbose)
		gspca_dbg(gspca_dev, D_PROBE, "Register %04x value: %02x\n",
			  index, buf[0]);

	वापस 0;
पूर्ण

/*
 * cit_send_FF_04_02()
 *
 * This procedure sends magic 3-command prefix to the camera.
 * The purpose of this prefix is not known.
 *
 * History:
 * 1/2/00   Created.
 */
अटल व्योम cit_send_FF_04_02(काष्ठा gspca_dev *gspca_dev)
अणु
	cit_ग_लिखो_reg(gspca_dev, 0x00FF, 0x0127);
	cit_ग_लिखो_reg(gspca_dev, 0x0004, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x0124);
पूर्ण

अटल व्योम cit_send_00_04_06(काष्ठा gspca_dev *gspca_dev)
अणु
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0127);
	cit_ग_लिखो_reg(gspca_dev, 0x0004, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0006, 0x0124);
पूर्ण

अटल व्योम cit_send_x_00(काष्ठा gspca_dev *gspca_dev, अचिन्हित लघु x)
अणु
	cit_ग_लिखो_reg(gspca_dev, x,      0x0127);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0124);
पूर्ण

अटल व्योम cit_send_x_00_05(काष्ठा gspca_dev *gspca_dev, अचिन्हित लघु x)
अणु
	cit_send_x_00(gspca_dev, x);
	cit_ग_लिखो_reg(gspca_dev, 0x0005, 0x0124);
पूर्ण

अटल व्योम cit_send_x_00_05_02(काष्ठा gspca_dev *gspca_dev, अचिन्हित लघु x)
अणु
	cit_ग_लिखो_reg(gspca_dev, x,      0x0127);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0005, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x0124);
पूर्ण

अटल व्योम cit_send_x_01_00_05(काष्ठा gspca_dev *gspca_dev, u16 x)
अणु
	cit_ग_लिखो_reg(gspca_dev, x,      0x0127);
	cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0005, 0x0124);
पूर्ण

अटल व्योम cit_send_x_00_05_02_01(काष्ठा gspca_dev *gspca_dev, u16 x)
अणु
	cit_ग_लिखो_reg(gspca_dev, x,      0x0127);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0005, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0124);
पूर्ण

अटल व्योम cit_send_x_00_05_02_08_01(काष्ठा gspca_dev *gspca_dev, u16 x)
अणु
	cit_ग_लिखो_reg(gspca_dev, x,      0x0127);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0005, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0124);
पूर्ण

अटल व्योम cit_Packet_Format1(काष्ठा gspca_dev *gspca_dev, u16 fkey, u16 val)
अणु
	cit_send_x_01_00_05(gspca_dev, 0x0088);
	cit_send_x_00_05(gspca_dev, fkey);
	cit_send_x_00_05_02_08_01(gspca_dev, val);
	cit_send_x_00_05(gspca_dev, 0x0088);
	cit_send_x_00_05_02_01(gspca_dev, fkey);
	cit_send_x_00_05(gspca_dev, 0x0089);
	cit_send_x_00(gspca_dev, fkey);
	cit_send_00_04_06(gspca_dev);
	cit_पढ़ो_reg(gspca_dev, 0x0126, 0);
	cit_send_FF_04_02(gspca_dev);
पूर्ण

अटल व्योम cit_PacketFormat2(काष्ठा gspca_dev *gspca_dev, u16 fkey, u16 val)
अणु
	cit_send_x_01_00_05(gspca_dev, 0x0088);
	cit_send_x_00_05(gspca_dev, fkey);
	cit_send_x_00_05_02(gspca_dev, val);
पूर्ण

अटल व्योम cit_model2_Packet2(काष्ठा gspca_dev *gspca_dev)
अणु
	cit_ग_लिखो_reg(gspca_dev, 0x00ff, 0x012d);
	cit_ग_लिखो_reg(gspca_dev, 0xfea3, 0x0124);
पूर्ण

अटल व्योम cit_model2_Packet1(काष्ठा gspca_dev *gspca_dev, u16 v1, u16 v2)
अणु
	cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
	cit_ग_लिखो_reg(gspca_dev, 0x00ff, 0x012e);
	cit_ग_लिखो_reg(gspca_dev, v1,     0x012f);
	cit_ग_लिखो_reg(gspca_dev, 0x00ff, 0x0130);
	cit_ग_लिखो_reg(gspca_dev, 0xc719, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, v2,     0x0127);

	cit_model2_Packet2(gspca_dev);
पूर्ण

/*
 * cit_model3_Packet1()
 *
 * 00_0078_012d
 * 00_0097_012f
 * 00_d141_0124
 * 00_0096_0127
 * 00_fea8_0124
*/
अटल व्योम cit_model3_Packet1(काष्ठा gspca_dev *gspca_dev, u16 v1, u16 v2)
अणु
	cit_ग_लिखो_reg(gspca_dev, 0x0078, 0x012d);
	cit_ग_लिखो_reg(gspca_dev, v1,     0x012f);
	cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, v2,     0x0127);
	cit_ग_लिखो_reg(gspca_dev, 0xfea8, 0x0124);
पूर्ण

अटल व्योम cit_model4_Packet1(काष्ठा gspca_dev *gspca_dev, u16 v1, u16 v2)
अणु
	cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
	cit_ग_लिखो_reg(gspca_dev, v1,     0x012f);
	cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, v2,     0x0127);
	cit_ग_लिखो_reg(gspca_dev, 0xfea8, 0x0124);
पूर्ण

अटल व्योम cit_model4_BrightnessPacket(काष्ठा gspca_dev *gspca_dev, u16 val)
अणु
	cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
	cit_ग_लिखो_reg(gspca_dev, 0x0026, 0x012f);
	cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, val,    0x0127);
	cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0130);
	cit_ग_लिखो_reg(gspca_dev, 0x82a8, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0038, 0x012d);
	cit_ग_लिखो_reg(gspca_dev, 0x0004, 0x012f);
	cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0xfffa, 0x0124);
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;

	sd->model = id->driver_info;
	अगर (sd->model == CIT_MODEL3 && ibm_netcam_pro)
		sd->model = CIT_IBM_NETCAM_PRO;

	cam = &gspca_dev->cam;
	चयन (sd->model) अणु
	हाल CIT_MODEL0:
		cam->cam_mode = model0_mode;
		cam->nmodes = ARRAY_SIZE(model0_mode);
		sd->sof_len = 4;
		अवरोध;
	हाल CIT_MODEL1:
		cam->cam_mode = cअगर_yuv_mode;
		cam->nmodes = ARRAY_SIZE(cअगर_yuv_mode);
		sd->sof_len = 4;
		अवरोध;
	हाल CIT_MODEL2:
		cam->cam_mode = model2_mode + 1; /* no 160x120 */
		cam->nmodes = 3;
		अवरोध;
	हाल CIT_MODEL3:
		cam->cam_mode = vga_yuv_mode;
		cam->nmodes = ARRAY_SIZE(vga_yuv_mode);
		sd->stop_on_control_change = 1;
		sd->sof_len = 4;
		अवरोध;
	हाल CIT_MODEL4:
		cam->cam_mode = model2_mode;
		cam->nmodes = ARRAY_SIZE(model2_mode);
		अवरोध;
	हाल CIT_IBM_NETCAM_PRO:
		cam->cam_mode = vga_yuv_mode;
		cam->nmodes = 2; /* no 640 x 480 */
		cam->input_flags = V4L2_IN_ST_VFLIP;
		sd->stop_on_control_change = 1;
		sd->sof_len = 4;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cit_init_model0(काष्ठा gspca_dev *gspca_dev)
अणु
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0100); /* turn on led */
	cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0112); /* turn on स्वतःgain ? */
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0400);
	cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0400);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0420);
	cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0420);
	cit_ग_लिखो_reg(gspca_dev, 0x000d, 0x0409);
	cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x040a);
	cit_ग_लिखो_reg(gspca_dev, 0x0018, 0x0405);
	cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x0435);
	cit_ग_लिखो_reg(gspca_dev, 0x0026, 0x040b);
	cit_ग_लिखो_reg(gspca_dev, 0x0007, 0x0437);
	cit_ग_लिखो_reg(gspca_dev, 0x0015, 0x042f);
	cit_ग_लिखो_reg(gspca_dev, 0x002b, 0x0439);
	cit_ग_लिखो_reg(gspca_dev, 0x0026, 0x043a);
	cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x0438);
	cit_ग_लिखो_reg(gspca_dev, 0x001e, 0x042b);
	cit_ग_लिखो_reg(gspca_dev, 0x0041, 0x042c);

	वापस 0;
पूर्ण

अटल पूर्णांक cit_init_ibm_netcam_pro(काष्ठा gspca_dev *gspca_dev)
अणु
	cit_पढ़ो_reg(gspca_dev, 0x128, 1);
	cit_ग_लिखो_reg(gspca_dev, 0x0003, 0x0133);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0117);
	cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x0123);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0100);
	cit_पढ़ो_reg(gspca_dev, 0x0116, 0);
	cit_ग_लिखो_reg(gspca_dev, 0x0060, 0x0116);
	cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x0112);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0133);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0123);
	cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0117);
	cit_ग_लिखो_reg(gspca_dev, 0x0040, 0x0108);
	cit_ग_लिखो_reg(gspca_dev, 0x0019, 0x012c);
	cit_ग_लिखो_reg(gspca_dev, 0x0060, 0x0116);
	cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x0115);
	cit_ग_लिखो_reg(gspca_dev, 0x000b, 0x0115);

	cit_ग_लिखो_reg(gspca_dev, 0x0078, 0x012d);
	cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x012f);
	cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0079, 0x012d);
	cit_ग_लिखो_reg(gspca_dev, 0x00ff, 0x0130);
	cit_ग_लिखो_reg(gspca_dev, 0xcd41, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0xfffa, 0x0124);
	cit_पढ़ो_reg(gspca_dev, 0x0126, 1);

	cit_model3_Packet1(gspca_dev, 0x0000, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0000, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x000b, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x000c, 0x0008);
	cit_model3_Packet1(gspca_dev, 0x000d, 0x003a);
	cit_model3_Packet1(gspca_dev, 0x000e, 0x0060);
	cit_model3_Packet1(gspca_dev, 0x000f, 0x0060);
	cit_model3_Packet1(gspca_dev, 0x0010, 0x0008);
	cit_model3_Packet1(gspca_dev, 0x0011, 0x0004);
	cit_model3_Packet1(gspca_dev, 0x0012, 0x0028);
	cit_model3_Packet1(gspca_dev, 0x0013, 0x0002);
	cit_model3_Packet1(gspca_dev, 0x0014, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0015, 0x00fb);
	cit_model3_Packet1(gspca_dev, 0x0016, 0x0002);
	cit_model3_Packet1(gspca_dev, 0x0017, 0x0037);
	cit_model3_Packet1(gspca_dev, 0x0018, 0x0036);
	cit_model3_Packet1(gspca_dev, 0x001e, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x001f, 0x0008);
	cit_model3_Packet1(gspca_dev, 0x0020, 0x00c1);
	cit_model3_Packet1(gspca_dev, 0x0021, 0x0034);
	cit_model3_Packet1(gspca_dev, 0x0022, 0x0034);
	cit_model3_Packet1(gspca_dev, 0x0025, 0x0002);
	cit_model3_Packet1(gspca_dev, 0x0028, 0x0022);
	cit_model3_Packet1(gspca_dev, 0x0029, 0x000a);
	cit_model3_Packet1(gspca_dev, 0x002b, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x002c, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x002d, 0x00ff);
	cit_model3_Packet1(gspca_dev, 0x002e, 0x00ff);
	cit_model3_Packet1(gspca_dev, 0x002f, 0x00ff);
	cit_model3_Packet1(gspca_dev, 0x0030, 0x00ff);
	cit_model3_Packet1(gspca_dev, 0x0031, 0x00ff);
	cit_model3_Packet1(gspca_dev, 0x0032, 0x0007);
	cit_model3_Packet1(gspca_dev, 0x0033, 0x0005);
	cit_model3_Packet1(gspca_dev, 0x0037, 0x0040);
	cit_model3_Packet1(gspca_dev, 0x0039, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x003a, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x003b, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x003c, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0040, 0x000c);
	cit_model3_Packet1(gspca_dev, 0x0041, 0x00fb);
	cit_model3_Packet1(gspca_dev, 0x0042, 0x0002);
	cit_model3_Packet1(gspca_dev, 0x0043, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0045, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0046, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0047, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0048, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0049, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x004a, 0x00ff);
	cit_model3_Packet1(gspca_dev, 0x004b, 0x00ff);
	cit_model3_Packet1(gspca_dev, 0x004c, 0x00ff);
	cit_model3_Packet1(gspca_dev, 0x004f, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0050, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0051, 0x0002);
	cit_model3_Packet1(gspca_dev, 0x0055, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0056, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0057, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0058, 0x0002);
	cit_model3_Packet1(gspca_dev, 0x0059, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x005c, 0x0016);
	cit_model3_Packet1(gspca_dev, 0x005d, 0x0022);
	cit_model3_Packet1(gspca_dev, 0x005e, 0x003c);
	cit_model3_Packet1(gspca_dev, 0x005f, 0x0050);
	cit_model3_Packet1(gspca_dev, 0x0060, 0x0044);
	cit_model3_Packet1(gspca_dev, 0x0061, 0x0005);
	cit_model3_Packet1(gspca_dev, 0x006a, 0x007e);
	cit_model3_Packet1(gspca_dev, 0x006f, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0072, 0x001b);
	cit_model3_Packet1(gspca_dev, 0x0073, 0x0005);
	cit_model3_Packet1(gspca_dev, 0x0074, 0x000a);
	cit_model3_Packet1(gspca_dev, 0x0075, 0x001b);
	cit_model3_Packet1(gspca_dev, 0x0076, 0x002a);
	cit_model3_Packet1(gspca_dev, 0x0077, 0x003c);
	cit_model3_Packet1(gspca_dev, 0x0078, 0x0050);
	cit_model3_Packet1(gspca_dev, 0x007b, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x007c, 0x0011);
	cit_model3_Packet1(gspca_dev, 0x007d, 0x0024);
	cit_model3_Packet1(gspca_dev, 0x007e, 0x0043);
	cit_model3_Packet1(gspca_dev, 0x007f, 0x005a);
	cit_model3_Packet1(gspca_dev, 0x0084, 0x0020);
	cit_model3_Packet1(gspca_dev, 0x0085, 0x0033);
	cit_model3_Packet1(gspca_dev, 0x0086, 0x000a);
	cit_model3_Packet1(gspca_dev, 0x0087, 0x0030);
	cit_model3_Packet1(gspca_dev, 0x0088, 0x0070);
	cit_model3_Packet1(gspca_dev, 0x008b, 0x0008);
	cit_model3_Packet1(gspca_dev, 0x008f, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0090, 0x0006);
	cit_model3_Packet1(gspca_dev, 0x0091, 0x0028);
	cit_model3_Packet1(gspca_dev, 0x0092, 0x005a);
	cit_model3_Packet1(gspca_dev, 0x0093, 0x0082);
	cit_model3_Packet1(gspca_dev, 0x0096, 0x0014);
	cit_model3_Packet1(gspca_dev, 0x0097, 0x0020);
	cit_model3_Packet1(gspca_dev, 0x0098, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00b0, 0x0046);
	cit_model3_Packet1(gspca_dev, 0x00b1, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00b2, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00b3, 0x0004);
	cit_model3_Packet1(gspca_dev, 0x00b4, 0x0007);
	cit_model3_Packet1(gspca_dev, 0x00b6, 0x0002);
	cit_model3_Packet1(gspca_dev, 0x00b7, 0x0004);
	cit_model3_Packet1(gspca_dev, 0x00bb, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00bc, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x00bd, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00bf, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00c0, 0x00c8);
	cit_model3_Packet1(gspca_dev, 0x00c1, 0x0014);
	cit_model3_Packet1(gspca_dev, 0x00c2, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x00c3, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00c4, 0x0004);
	cit_model3_Packet1(gspca_dev, 0x00cb, 0x00bf);
	cit_model3_Packet1(gspca_dev, 0x00cc, 0x00bf);
	cit_model3_Packet1(gspca_dev, 0x00cd, 0x00bf);
	cit_model3_Packet1(gspca_dev, 0x00ce, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00cf, 0x0020);
	cit_model3_Packet1(gspca_dev, 0x00d0, 0x0040);
	cit_model3_Packet1(gspca_dev, 0x00d1, 0x00bf);
	cit_model3_Packet1(gspca_dev, 0x00d1, 0x00bf);
	cit_model3_Packet1(gspca_dev, 0x00d2, 0x00bf);
	cit_model3_Packet1(gspca_dev, 0x00d3, 0x00bf);
	cit_model3_Packet1(gspca_dev, 0x00ea, 0x0008);
	cit_model3_Packet1(gspca_dev, 0x00eb, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00ec, 0x00e8);
	cit_model3_Packet1(gspca_dev, 0x00ed, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x00ef, 0x0022);
	cit_model3_Packet1(gspca_dev, 0x00f0, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00f2, 0x0028);
	cit_model3_Packet1(gspca_dev, 0x00f4, 0x0002);
	cit_model3_Packet1(gspca_dev, 0x00f5, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00fa, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00fb, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x00fc, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00fd, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00fe, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00ff, 0x0000);

	cit_model3_Packet1(gspca_dev, 0x00be, 0x0003);
	cit_model3_Packet1(gspca_dev, 0x00c8, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00c9, 0x0020);
	cit_model3_Packet1(gspca_dev, 0x00ca, 0x0040);
	cit_model3_Packet1(gspca_dev, 0x0053, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x0082, 0x000e);
	cit_model3_Packet1(gspca_dev, 0x0083, 0x0020);
	cit_model3_Packet1(gspca_dev, 0x0034, 0x003c);
	cit_model3_Packet1(gspca_dev, 0x006e, 0x0055);
	cit_model3_Packet1(gspca_dev, 0x0062, 0x0005);
	cit_model3_Packet1(gspca_dev, 0x0063, 0x0008);
	cit_model3_Packet1(gspca_dev, 0x0066, 0x000a);
	cit_model3_Packet1(gspca_dev, 0x0067, 0x0006);
	cit_model3_Packet1(gspca_dev, 0x006b, 0x0010);
	cit_model3_Packet1(gspca_dev, 0x005a, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x005b, 0x000a);
	cit_model3_Packet1(gspca_dev, 0x0023, 0x0006);
	cit_model3_Packet1(gspca_dev, 0x0026, 0x0004);
	cit_model3_Packet1(gspca_dev, 0x0036, 0x0069);
	cit_model3_Packet1(gspca_dev, 0x0038, 0x0064);
	cit_model3_Packet1(gspca_dev, 0x003d, 0x0003);
	cit_model3_Packet1(gspca_dev, 0x003e, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x00b8, 0x0014);
	cit_model3_Packet1(gspca_dev, 0x00b9, 0x0014);
	cit_model3_Packet1(gspca_dev, 0x00e6, 0x0004);
	cit_model3_Packet1(gspca_dev, 0x00e8, 0x0001);

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (sd->model) अणु
	हाल CIT_MODEL0:
		cit_init_model0(gspca_dev);
		sd_stop0(gspca_dev);
		अवरोध;
	हाल CIT_MODEL1:
	हाल CIT_MODEL2:
	हाल CIT_MODEL3:
	हाल CIT_MODEL4:
		अवरोध; /* All is करोne in sd_start */
	हाल CIT_IBM_NETCAM_PRO:
		cit_init_ibm_netcam_pro(gspca_dev);
		sd_stop0(gspca_dev);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cit_set_brightness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक i;

	चयन (sd->model) अणु
	हाल CIT_MODEL0:
	हाल CIT_IBM_NETCAM_PRO:
		/* No (known) brightness control क्रम these */
		अवरोध;
	हाल CIT_MODEL1:
		/* Model 1: Brightness range 0 - 63 */
		cit_Packet_Format1(gspca_dev, 0x0031, val);
		cit_Packet_Format1(gspca_dev, 0x0032, val);
		cit_Packet_Format1(gspca_dev, 0x0033, val);
		अवरोध;
	हाल CIT_MODEL2:
		/* Model 2: Brightness range 0x60 - 0xee */
		/* Scale 0 - 63 to 0x60 - 0xee */
		i = 0x60 + val * 2254 / 1000;
		cit_model2_Packet1(gspca_dev, 0x001a, i);
		अवरोध;
	हाल CIT_MODEL3:
		/* Model 3: Brightness range 'i' in [0x0C..0x3F] */
		i = val;
		अगर (i < 0x0c)
			i = 0x0c;
		cit_model3_Packet1(gspca_dev, 0x0036, i);
		अवरोध;
	हाल CIT_MODEL4:
		/* Model 4: Brightness range 'i' in [0x04..0xb4] */
		/* Scale 0 - 63 to 0x04 - 0xb4 */
		i = 0x04 + val * 2794 / 1000;
		cit_model4_BrightnessPacket(gspca_dev, i);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cit_set_contrast(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (sd->model) अणु
	हाल CIT_MODEL0: अणु
		पूर्णांक i;
		/* gain 0-15, 0-20 -> 0-15 */
		i = val * 1000 / 1333;
		cit_ग_लिखो_reg(gspca_dev, i, 0x0422);
		/* gain 0-31, may not be lower then 0x0422, 0-20 -> 0-31 */
		i = val * 2000 / 1333;
		cit_ग_लिखो_reg(gspca_dev, i, 0x0423);
		/* gain 0-127, may not be lower then 0x0423, 0-20 -> 0-63  */
		i = val * 4000 / 1333;
		cit_ग_लिखो_reg(gspca_dev, i, 0x0424);
		/* gain 0-127, may not be lower then 0x0424, , 0-20 -> 0-127 */
		i = val * 8000 / 1333;
		cit_ग_लिखो_reg(gspca_dev, i, 0x0425);
		अवरोध;
	पूर्ण
	हाल CIT_MODEL2:
	हाल CIT_MODEL4:
		/* These models करो not have this control. */
		अवरोध;
	हाल CIT_MODEL1:
	अणु
		/* Scale 0 - 20 to 15 - 0 */
		पूर्णांक i, new_contrast = (20 - val) * 1000 / 1333;
		क्रम (i = 0; i < cit_model1_ntries; i++) अणु
			cit_Packet_Format1(gspca_dev, 0x0014, new_contrast);
			cit_send_FF_04_02(gspca_dev);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल CIT_MODEL3:
	अणु	/* Preset hardware values */
		अटल स्थिर काष्ठा अणु
			अचिन्हित लघु cv1;
			अचिन्हित लघु cv2;
			अचिन्हित लघु cv3;
		पूर्ण cv[7] = अणु
			अणु 0x05, 0x05, 0x0f पूर्ण,	/* Minimum */
			अणु 0x04, 0x04, 0x16 पूर्ण,
			अणु 0x02, 0x03, 0x16 पूर्ण,
			अणु 0x02, 0x08, 0x16 पूर्ण,
			अणु 0x01, 0x0c, 0x16 पूर्ण,
			अणु 0x01, 0x0e, 0x16 पूर्ण,
			अणु 0x01, 0x10, 0x16 पूर्ण	/* Maximum */
		पूर्ण;
		पूर्णांक i = val / 3;
		cit_model3_Packet1(gspca_dev, 0x0067, cv[i].cv1);
		cit_model3_Packet1(gspca_dev, 0x005b, cv[i].cv2);
		cit_model3_Packet1(gspca_dev, 0x005c, cv[i].cv3);
		अवरोध;
	पूर्ण
	हाल CIT_IBM_NETCAM_PRO:
		cit_model3_Packet1(gspca_dev, 0x005b, val + 1);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cit_set_hue(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (sd->model) अणु
	हाल CIT_MODEL0:
	हाल CIT_MODEL1:
	हाल CIT_IBM_NETCAM_PRO:
		/* No hue control क्रम these models */
		अवरोध;
	हाल CIT_MODEL2:
		cit_model2_Packet1(gspca_dev, 0x0024, val);
		/* cit_model2_Packet1(gspca_dev, 0x0020, sat); */
		अवरोध;
	हाल CIT_MODEL3: अणु
		/* Model 3: Brightness range 'i' in [0x05..0x37] */
		/* TESTME according to the ibmcam driver this करोes not work */
		अगर (0) अणु
			/* Scale 0 - 127 to 0x05 - 0x37 */
			पूर्णांक i = 0x05 + val * 1000 / 2540;
			cit_model3_Packet1(gspca_dev, 0x007e, i);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल CIT_MODEL4:
		/* HDG: taken from ibmcam, setting the color gains करोes not
		 * really beदीर्घ here.
		 *
		 * I am not sure r/g/b_gain variables exactly control gain
		 * of those channels. Most likely they subtly change some
		 * very पूर्णांकernal image processing settings in the camera.
		 * In any हाल, here is what they करो, and feel मुक्त to tweak:
		 *
		 * r_gain: seriously affects red gain
		 * g_gain: seriously affects green gain
		 * b_gain: seriously affects blue gain
		 * hue: changes average color from violet (0) to red (0xFF)
		 */
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x001e, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev,    160, 0x0127);  /* Green gain */
		cit_ग_लिखो_reg(gspca_dev,    160, 0x012e);  /* Red gain */
		cit_ग_लिखो_reg(gspca_dev,    160, 0x0130);  /* Blue gain */
		cit_ग_लिखो_reg(gspca_dev, 0x8a28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, val, 0x012d); /* Hue */
		cit_ग_लिखो_reg(gspca_dev, 0xf545, 0x0124);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cit_set_sharpness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (sd->model) अणु
	हाल CIT_MODEL0:
	हाल CIT_MODEL2:
	हाल CIT_MODEL4:
	हाल CIT_IBM_NETCAM_PRO:
		/* These models करो not have this control */
		अवरोध;
	हाल CIT_MODEL1: अणु
		पूर्णांक i;
		अटल स्थिर अचिन्हित लघु sa[] = अणु
			0x11, 0x13, 0x16, 0x18, 0x1a, 0x8, 0x0a पूर्ण;

		क्रम (i = 0; i < cit_model1_ntries; i++)
			cit_PacketFormat2(gspca_dev, 0x0013, sa[val]);
		अवरोध;
	पूर्ण
	हाल CIT_MODEL3:
	अणु	/*
		 * "Use a table of magic numbers.
		 *  This setting करोesn't really change much.
		 *  But that's how Winकरोws करोes it."
		 */
		अटल स्थिर काष्ठा अणु
			अचिन्हित लघु sv1;
			अचिन्हित लघु sv2;
			अचिन्हित लघु sv3;
			अचिन्हित लघु sv4;
		पूर्ण sv[7] = अणु
			अणु 0x00, 0x00, 0x05, 0x14 पूर्ण,	/* Smoothest */
			अणु 0x01, 0x04, 0x05, 0x14 पूर्ण,
			अणु 0x02, 0x04, 0x05, 0x14 पूर्ण,
			अणु 0x03, 0x04, 0x05, 0x14 पूर्ण,
			अणु 0x03, 0x05, 0x05, 0x14 पूर्ण,
			अणु 0x03, 0x06, 0x05, 0x14 पूर्ण,
			अणु 0x03, 0x07, 0x05, 0x14 पूर्ण	/* Sharpest */
		पूर्ण;
		cit_model3_Packet1(gspca_dev, 0x0060, sv[val].sv1);
		cit_model3_Packet1(gspca_dev, 0x0061, sv[val].sv2);
		cit_model3_Packet1(gspca_dev, 0x0062, sv[val].sv3);
		cit_model3_Packet1(gspca_dev, 0x0063, sv[val].sv4);
		अवरोध;
	पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * cit_set_lighting()
 *
 * Camera model 1:
 * We have 3 levels of lighting conditions: 0=Bright, 1=Medium, 2=Low.
 *
 * Camera model 2:
 * We have 16 levels of lighting, 0 क्रम bright light and up to 15 क्रम
 * low light. But values above 5 or so are useless because camera is
 * not really capable to produce anything worth viewing at such light.
 * This setting may be altered only in certain camera state.
 *
 * Low lighting क्रमces slower FPS.
 *
 * History:
 * 1/5/00   Created.
 * 2/20/00  Added support क्रम Model 2 cameras.
 */
अटल व्योम cit_set_lighting(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (sd->model) अणु
	हाल CIT_MODEL0:
	हाल CIT_MODEL2:
	हाल CIT_MODEL3:
	हाल CIT_MODEL4:
	हाल CIT_IBM_NETCAM_PRO:
		अवरोध;
	हाल CIT_MODEL1: अणु
		पूर्णांक i;
		क्रम (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x0027, val);
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cit_set_hflip(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (sd->model) अणु
	हाल CIT_MODEL0:
		अगर (val)
			cit_ग_लिखो_reg(gspca_dev, 0x0020, 0x0115);
		अन्यथा
			cit_ग_लिखो_reg(gspca_dev, 0x0040, 0x0115);
		अवरोध;
	हाल CIT_MODEL1:
	हाल CIT_MODEL2:
	हाल CIT_MODEL3:
	हाल CIT_MODEL4:
	हाल CIT_IBM_NETCAM_PRO:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cit_restart_stream(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (sd->model) अणु
	हाल CIT_MODEL0:
	हाल CIT_MODEL1:
		cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0114);
		fallthrough;
	हाल CIT_MODEL2:
	हाल CIT_MODEL4:
		cit_ग_लिखो_reg(gspca_dev, 0x00c0, 0x010c); /* Go! */
		usb_clear_halt(gspca_dev->dev, gspca_dev->urb[0]->pipe);
		अवरोध;
	हाल CIT_MODEL3:
	हाल CIT_IBM_NETCAM_PRO:
		cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0114);
		cit_ग_लिखो_reg(gspca_dev, 0x00c0, 0x010c); /* Go! */
		usb_clear_halt(gspca_dev->dev, gspca_dev->urb[0]->pipe);
		/* Clear button events from जबतक we were not streaming */
		cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0113);
		अवरोध;
	पूर्ण

	sd->sof_पढ़ो = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक cit_get_packet_size(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा usb_host_पूर्णांकerface *alt;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	पूर्णांकf = usb_अगरnum_to_अगर(gspca_dev->dev, gspca_dev->अगरace);
	alt = usb_altnum_to_altsetting(पूर्णांकf, gspca_dev->alt);
	अगर (!alt) अणु
		pr_err("Couldn't get altsetting\n");
		वापस -EIO;
	पूर्ण

	अगर (alt->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;

	वापस le16_to_cpu(alt->endpoपूर्णांक[0].desc.wMaxPacketSize);
पूर्ण

/* Calculate the घड़ीभाग giving us max fps given the available bandwidth */
अटल पूर्णांक cit_get_घड़ी_भाग(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक घड़ी_भाग = 7; /* 0=30 1=25 2=20 3=15 4=12 5=7.5 6=6 7=3fps ?? */
	पूर्णांक fps[8] = अणु 30, 25, 20, 15, 12, 8, 6, 3 पूर्ण;
	पूर्णांक packet_size;

	packet_size = cit_get_packet_size(gspca_dev);
	अगर (packet_size < 0)
		वापस packet_size;

	जबतक (घड़ी_भाग > 3 &&
			1000 * packet_size >
			gspca_dev->pixfmt.width * gspca_dev->pixfmt.height *
			fps[घड़ी_भाग - 1] * 3 / 2)
		घड़ी_भाग--;

	gspca_dbg(gspca_dev, D_PROBE,
		  "PacketSize: %d, res: %dx%d -> using clockdiv: %d (%d fps)\n",
		  packet_size,
		  gspca_dev->pixfmt.width, gspca_dev->pixfmt.height,
		  घड़ी_भाग, fps[घड़ी_भाग]);

	वापस घड़ी_भाग;
पूर्ण

अटल पूर्णांक cit_start_model0(काष्ठा gspca_dev *gspca_dev)
अणु
	स्थिर अचिन्हित लघु compression = 0; /* 0=none, 7=best frame rate */
	पूर्णांक घड़ी_भाग;

	घड़ी_भाग = cit_get_घड़ी_भाग(gspca_dev);
	अगर (घड़ी_भाग < 0)
		वापस घड़ी_भाग;

	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0100); /* turn on led */
	cit_ग_लिखो_reg(gspca_dev, 0x0003, 0x0438);
	cit_ग_लिखो_reg(gspca_dev, 0x001e, 0x042b);
	cit_ग_लिखो_reg(gspca_dev, 0x0041, 0x042c);
	cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x0436);
	cit_ग_लिखो_reg(gspca_dev, 0x0024, 0x0403);
	cit_ग_लिखो_reg(gspca_dev, 0x002c, 0x0404);
	cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x0426);
	cit_ग_लिखो_reg(gspca_dev, 0x0014, 0x0427);

	चयन (gspca_dev->pixfmt.width) अणु
	हाल 160: /* 160x120 */
		cit_ग_लिखो_reg(gspca_dev, 0x0004, 0x010b);
		cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x010a);
		cit_ग_लिखो_reg(gspca_dev, 0x0010, 0x0102);
		cit_ग_लिखो_reg(gspca_dev, 0x00a0, 0x0103);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x0078, 0x0105);
		अवरोध;

	हाल 176: /* 176x144 */
		cit_ग_लिखो_reg(gspca_dev, 0x0006, 0x010b);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x010a);
		cit_ग_लिखो_reg(gspca_dev, 0x0005, 0x0102);
		cit_ग_लिखो_reg(gspca_dev, 0x00b0, 0x0103);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x0090, 0x0105);
		अवरोध;

	हाल 320: /* 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x010b);
		cit_ग_लिखो_reg(gspca_dev, 0x0004, 0x010a);
		cit_ग_लिखो_reg(gspca_dev, 0x0005, 0x0102);
		cit_ग_लिखो_reg(gspca_dev, 0x00a0, 0x0103);
		cit_ग_लिखो_reg(gspca_dev, 0x0010, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x0078, 0x0105);
		अवरोध;
	पूर्ण

	cit_ग_लिखो_reg(gspca_dev, compression, 0x0109);
	cit_ग_लिखो_reg(gspca_dev, घड़ी_भाग, 0x0111);

	वापस 0;
पूर्ण

अटल पूर्णांक cit_start_model1(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक i, घड़ी_भाग;

	घड़ी_भाग = cit_get_घड़ी_भाग(gspca_dev);
	अगर (घड़ी_भाग < 0)
		वापस घड़ी_भाग;

	cit_पढ़ो_reg(gspca_dev, 0x0128, 1);
	cit_पढ़ो_reg(gspca_dev, 0x0100, 0);
	cit_ग_लिखो_reg(gspca_dev, 0x01, 0x0100);	/* LED On  */
	cit_पढ़ो_reg(gspca_dev, 0x0100, 0);
	cit_ग_लिखो_reg(gspca_dev, 0x81, 0x0100);	/* LED Off */
	cit_पढ़ो_reg(gspca_dev, 0x0100, 0);
	cit_ग_लिखो_reg(gspca_dev, 0x01, 0x0100);	/* LED On  */
	cit_ग_लिखो_reg(gspca_dev, 0x01, 0x0108);

	cit_ग_लिखो_reg(gspca_dev, 0x03, 0x0112);
	cit_पढ़ो_reg(gspca_dev, 0x0115, 0);
	cit_ग_लिखो_reg(gspca_dev, 0x06, 0x0115);
	cit_पढ़ो_reg(gspca_dev, 0x0116, 0);
	cit_ग_लिखो_reg(gspca_dev, 0x44, 0x0116);
	cit_पढ़ो_reg(gspca_dev, 0x0116, 0);
	cit_ग_लिखो_reg(gspca_dev, 0x40, 0x0116);
	cit_पढ़ो_reg(gspca_dev, 0x0115, 0);
	cit_ग_लिखो_reg(gspca_dev, 0x0e, 0x0115);
	cit_ग_लिखो_reg(gspca_dev, 0x19, 0x012c);

	cit_Packet_Format1(gspca_dev, 0x00, 0x1e);
	cit_Packet_Format1(gspca_dev, 0x39, 0x0d);
	cit_Packet_Format1(gspca_dev, 0x39, 0x09);
	cit_Packet_Format1(gspca_dev, 0x3b, 0x00);
	cit_Packet_Format1(gspca_dev, 0x28, 0x22);
	cit_Packet_Format1(gspca_dev, 0x27, 0x00);
	cit_Packet_Format1(gspca_dev, 0x2b, 0x1f);
	cit_Packet_Format1(gspca_dev, 0x39, 0x08);

	क्रम (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x2c, 0x00);

	क्रम (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x30, 0x14);

	cit_PacketFormat2(gspca_dev, 0x39, 0x02);
	cit_PacketFormat2(gspca_dev, 0x01, 0xe1);
	cit_PacketFormat2(gspca_dev, 0x02, 0xcd);
	cit_PacketFormat2(gspca_dev, 0x03, 0xcd);
	cit_PacketFormat2(gspca_dev, 0x04, 0xfa);
	cit_PacketFormat2(gspca_dev, 0x3f, 0xff);
	cit_PacketFormat2(gspca_dev, 0x39, 0x00);

	cit_PacketFormat2(gspca_dev, 0x39, 0x02);
	cit_PacketFormat2(gspca_dev, 0x0a, 0x37);
	cit_PacketFormat2(gspca_dev, 0x0b, 0xb8);
	cit_PacketFormat2(gspca_dev, 0x0c, 0xf3);
	cit_PacketFormat2(gspca_dev, 0x0d, 0xe3);
	cit_PacketFormat2(gspca_dev, 0x0e, 0x0d);
	cit_PacketFormat2(gspca_dev, 0x0f, 0xf2);
	cit_PacketFormat2(gspca_dev, 0x10, 0xd5);
	cit_PacketFormat2(gspca_dev, 0x11, 0xba);
	cit_PacketFormat2(gspca_dev, 0x12, 0x53);
	cit_PacketFormat2(gspca_dev, 0x3f, 0xff);
	cit_PacketFormat2(gspca_dev, 0x39, 0x00);

	cit_PacketFormat2(gspca_dev, 0x39, 0x02);
	cit_PacketFormat2(gspca_dev, 0x16, 0x00);
	cit_PacketFormat2(gspca_dev, 0x17, 0x28);
	cit_PacketFormat2(gspca_dev, 0x18, 0x7d);
	cit_PacketFormat2(gspca_dev, 0x19, 0xbe);
	cit_PacketFormat2(gspca_dev, 0x3f, 0xff);
	cit_PacketFormat2(gspca_dev, 0x39, 0x00);

	क्रम (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x00, 0x18);
	क्रम (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x13, 0x18);
	क्रम (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x14, 0x06);

	/* TESTME These are handled through controls
	   KEEP until someone can test leaving this out is ok */
	अगर (0) अणु
		/* This is शेष brightness */
		क्रम (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x31, 0x37);
		क्रम (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x32, 0x46);
		क्रम (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x33, 0x55);
	पूर्ण

	cit_Packet_Format1(gspca_dev, 0x2e, 0x04);
	क्रम (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x2d, 0x04);
	क्रम (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x29, 0x80);
	cit_Packet_Format1(gspca_dev, 0x2c, 0x01);
	cit_Packet_Format1(gspca_dev, 0x30, 0x17);
	cit_Packet_Format1(gspca_dev, 0x39, 0x08);
	क्रम (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x34, 0x00);

	cit_ग_लिखो_reg(gspca_dev, 0x00, 0x0101);
	cit_ग_लिखो_reg(gspca_dev, 0x00, 0x010a);

	चयन (gspca_dev->pixfmt.width) अणु
	हाल 128: /* 128x96 */
		cit_ग_लिखो_reg(gspca_dev, 0x80, 0x0103);
		cit_ग_लिखो_reg(gspca_dev, 0x60, 0x0105);
		cit_ग_लिखो_reg(gspca_dev, 0x0c, 0x010b);
		cit_ग_लिखो_reg(gspca_dev, 0x04, 0x011b);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x0b, 0x011d);
		cit_ग_लिखो_reg(gspca_dev, 0x00, 0x011e);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x00, 0x0129);
		अवरोध;
	हाल 176: /* 176x144 */
		cit_ग_लिखो_reg(gspca_dev, 0xb0, 0x0103);
		cit_ग_लिखो_reg(gspca_dev, 0x8f, 0x0105);
		cit_ग_लिखो_reg(gspca_dev, 0x06, 0x010b);
		cit_ग_लिखो_reg(gspca_dev, 0x04, 0x011b);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x0d, 0x011d);
		cit_ग_लिखो_reg(gspca_dev, 0x00, 0x011e);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x03, 0x0129);
		अवरोध;
	हाल 352: /* 352x288 */
		cit_ग_लिखो_reg(gspca_dev, 0xb0, 0x0103);
		cit_ग_लिखो_reg(gspca_dev, 0x90, 0x0105);
		cit_ग_लिखो_reg(gspca_dev, 0x02, 0x010b);
		cit_ग_लिखो_reg(gspca_dev, 0x04, 0x011b);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x05, 0x011d);
		cit_ग_लिखो_reg(gspca_dev, 0x00, 0x011e);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x00, 0x0129);
		अवरोध;
	पूर्ण

	cit_ग_लिखो_reg(gspca_dev, 0xff, 0x012b);

	/* TESTME These are handled through controls
	   KEEP until someone can test leaving this out is ok */
	अगर (0) अणु
		/* This is another brightness - करोn't know why */
		क्रम (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x31, 0xc3);
		क्रम (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x32, 0xd2);
		क्रम (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x33, 0xe1);

		/* Default contrast */
		क्रम (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x14, 0x0a);

		/* Default sharpness */
		क्रम (i = 0; i < cit_model1_ntries2; i++)
			cit_PacketFormat2(gspca_dev, 0x13, 0x1a);

		/* Default lighting conditions */
		cit_Packet_Format1(gspca_dev, 0x0027,
				   v4l2_ctrl_g_ctrl(sd->lighting));
	पूर्ण

	/* Assorted init */
	चयन (gspca_dev->pixfmt.width) अणु
	हाल 128: /* 128x96 */
		cit_Packet_Format1(gspca_dev, 0x2b, 0x1e);
		cit_ग_लिखो_reg(gspca_dev, 0xc9, 0x0119);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x80, 0x0109);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x36, 0x0102);
		cit_ग_लिखो_reg(gspca_dev, 0x1a, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x04, 0x011a);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x2b, 0x011c);
		cit_ग_लिखो_reg(gspca_dev, 0x23, 0x012a);	/* Same everywhere */
		अवरोध;
	हाल 176: /* 176x144 */
		cit_Packet_Format1(gspca_dev, 0x2b, 0x1e);
		cit_ग_लिखो_reg(gspca_dev, 0xc9, 0x0119);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x80, 0x0109);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x04, 0x0102);
		cit_ग_लिखो_reg(gspca_dev, 0x02, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x04, 0x011a);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x2b, 0x011c);
		cit_ग_लिखो_reg(gspca_dev, 0x23, 0x012a);	/* Same everywhere */
		अवरोध;
	हाल 352: /* 352x288 */
		cit_Packet_Format1(gspca_dev, 0x2b, 0x1f);
		cit_ग_लिखो_reg(gspca_dev, 0xc9, 0x0119);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x80, 0x0109);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x08, 0x0102);
		cit_ग_लिखो_reg(gspca_dev, 0x01, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x04, 0x011a);	/* Same everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x2f, 0x011c);
		cit_ग_लिखो_reg(gspca_dev, 0x23, 0x012a);	/* Same everywhere */
		अवरोध;
	पूर्ण

	cit_ग_लिखो_reg(gspca_dev, 0x01, 0x0100);	/* LED On  */
	cit_ग_लिखो_reg(gspca_dev, घड़ी_भाग, 0x0111);

	वापस 0;
पूर्ण

अटल पूर्णांक cit_start_model2(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक घड़ी_भाग = 0;

	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0100);	/* LED on */
	cit_पढ़ो_reg(gspca_dev, 0x0116, 0);
	cit_ग_लिखो_reg(gspca_dev, 0x0060, 0x0116);
	cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x0112);
	cit_ग_लिखो_reg(gspca_dev, 0x00bc, 0x012c);
	cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x012b);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0108);
	cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0133);
	cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0102);
	चयन (gspca_dev->pixfmt.width) अणु
	हाल 176: /* 176x144 */
		cit_ग_लिखो_reg(gspca_dev, 0x002c, 0x0103);	/* All except 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0104);	/* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x0024, 0x0105);	/* 176x144, 352x288 */
		cit_ग_लिखो_reg(gspca_dev, 0x00b9, 0x010a);	/* Unique to this mode */
		cit_ग_लिखो_reg(gspca_dev, 0x0038, 0x0119);	/* Unique to this mode */
		/* TESTME HDG: this करोes not seem right
		   (it is 2 क्रम all other resolutions) */
		sd->sof_len = 10;
		अवरोध;
	हाल 320: /* 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0028, 0x0103);	/* Unique to this mode */
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0104);	/* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x001e, 0x0105);	/* 320x240, 352x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0039, 0x010a);	/* All except 176x144 */
		cit_ग_लिखो_reg(gspca_dev, 0x0070, 0x0119);	/* All except 176x144 */
		sd->sof_len = 2;
		अवरोध;
#अगर 0
	हाल VIDEOSIZE_352x240:
		cit_ग_लिखो_reg(gspca_dev, 0x002c, 0x0103);	/* All except 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0104);	/* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x001e, 0x0105);	/* 320x240, 352x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0039, 0x010a);	/* All except 176x144 */
		cit_ग_लिखो_reg(gspca_dev, 0x0070, 0x0119);	/* All except 176x144 */
		sd->sof_len = 2;
		अवरोध;
#पूर्ण_अगर
	हाल 352: /* 352x288 */
		cit_ग_लिखो_reg(gspca_dev, 0x002c, 0x0103);	/* All except 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0104);	/* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x0024, 0x0105);	/* 176x144, 352x288 */
		cit_ग_लिखो_reg(gspca_dev, 0x0039, 0x010a);	/* All except 176x144 */
		cit_ग_लिखो_reg(gspca_dev, 0x0070, 0x0119);	/* All except 176x144 */
		sd->sof_len = 2;
		अवरोध;
	पूर्ण

	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0100);	/* LED on */

	चयन (gspca_dev->pixfmt.width) अणु
	हाल 176: /* 176x144 */
		cit_ग_लिखो_reg(gspca_dev, 0x0050, 0x0111);
		cit_ग_लिखो_reg(gspca_dev, 0x00d0, 0x0111);
		अवरोध;
	हाल 320: /* 320x240 */
	हाल 352: /* 352x288 */
		cit_ग_लिखो_reg(gspca_dev, 0x0040, 0x0111);
		cit_ग_लिखो_reg(gspca_dev, 0x00c0, 0x0111);
		अवरोध;
	पूर्ण
	cit_ग_लिखो_reg(gspca_dev, 0x009b, 0x010f);
	cit_ग_लिखो_reg(gspca_dev, 0x00bb, 0x010f);

	/*
	 * Hardware settings, may affect CMOS sensor; not user controls!
	 * -------------------------------------------------------------
	 * 0x0004: no effect
	 * 0x0006: hardware effect
	 * 0x0008: no effect
	 * 0x000a: stops video stream, probably important h/w setting
	 * 0x000c: changes color in hardware manner (not user setting)
	 * 0x0012: changes number of colors (करोes not affect speed)
	 * 0x002a: no effect
	 * 0x002c: hardware setting (related to scan lines)
	 * 0x002e: stops video stream, probably important h/w setting
	 */
	cit_model2_Packet1(gspca_dev, 0x000a, 0x005c);
	cit_model2_Packet1(gspca_dev, 0x0004, 0x0000);
	cit_model2_Packet1(gspca_dev, 0x0006, 0x00fb);
	cit_model2_Packet1(gspca_dev, 0x0008, 0x0000);
	cit_model2_Packet1(gspca_dev, 0x000c, 0x0009);
	cit_model2_Packet1(gspca_dev, 0x0012, 0x000a);
	cit_model2_Packet1(gspca_dev, 0x002a, 0x0000);
	cit_model2_Packet1(gspca_dev, 0x002c, 0x0000);
	cit_model2_Packet1(gspca_dev, 0x002e, 0x0008);

	/*
	 * Function 0x0030 pops up all over the place. Apparently
	 * it is a hardware control रेजिस्टर, with every bit asचिन्हित to
	 * करो something.
	 */
	cit_model2_Packet1(gspca_dev, 0x0030, 0x0000);

	/*
	 * Magic control of CMOS sensor. Only lower values like
	 * 0-3 work, and picture shअगरts left or right. Don't change.
	 */
	चयन (gspca_dev->pixfmt.width) अणु
	हाल 176: /* 176x144 */
		cit_model2_Packet1(gspca_dev, 0x0014, 0x0002);
		cit_model2_Packet1(gspca_dev, 0x0016, 0x0002); /* Horizontal shअगरt */
		cit_model2_Packet1(gspca_dev, 0x0018, 0x004a); /* Another hardware setting */
		घड़ी_भाग = 6;
		अवरोध;
	हाल 320: /* 320x240 */
		cit_model2_Packet1(gspca_dev, 0x0014, 0x0009);
		cit_model2_Packet1(gspca_dev, 0x0016, 0x0005); /* Horizontal shअगरt */
		cit_model2_Packet1(gspca_dev, 0x0018, 0x0044); /* Another hardware setting */
		घड़ी_भाग = 8;
		अवरोध;
#अगर 0
	हाल VIDEOSIZE_352x240:
		/* This mode करोesn't work as Winकरोws programs it; changed to work */
		cit_model2_Packet1(gspca_dev, 0x0014, 0x0009); /* Winकरोws sets this to 8 */
		cit_model2_Packet1(gspca_dev, 0x0016, 0x0003); /* Horizontal shअगरt */
		cit_model2_Packet1(gspca_dev, 0x0018, 0x0044); /* Winकरोws sets this to 0x0045 */
		घड़ी_भाग = 10;
		अवरोध;
#पूर्ण_अगर
	हाल 352: /* 352x288 */
		cit_model2_Packet1(gspca_dev, 0x0014, 0x0003);
		cit_model2_Packet1(gspca_dev, 0x0016, 0x0002); /* Horizontal shअगरt */
		cit_model2_Packet1(gspca_dev, 0x0018, 0x004a); /* Another hardware setting */
		घड़ी_भाग = 16;
		अवरोध;
	पूर्ण

	/* TESTME These are handled through controls
	   KEEP until someone can test leaving this out is ok */
	अगर (0)
		cit_model2_Packet1(gspca_dev, 0x001a, 0x005a);

	/*
	 * We have our own frame rate setting varying from 0 (slowest) to 6
	 * (fastest). The camera model 2 allows frame rate in range [0..0x1F]
	 # where 0 is also the slowest setting. However क्रम all practical
	 # reasons high settings make no sense because USB is not fast enough
	 # to support high FPS. Be aware that the picture datastream will be
	 # severely disrupted अगर you ask क्रम frame rate faster than allowed
	 # क्रम the video size - see below:
	 *
	 * Allowable ranges (obtained experimentally on OHCI, K6-3, 450 MHz):
	 * -----------------------------------------------------------------
	 * 176x144: [6..31]
	 * 320x240: [8..31]
	 * 352x240: [10..31]
	 * 352x288: [16..31] I have to उठाओ lower threshold क्रम stability...
	 *
	 * As usual, slower FPS provides better sensitivity.
	 */
	cit_model2_Packet1(gspca_dev, 0x001c, घड़ी_भाग);

	/*
	 * This setting करोes not visibly affect pictures; left it here
	 * because it was present in Winकरोws USB data stream. This function
	 * करोes not allow arbitrary values and apparently is a bit mask, to
	 * be activated only at appropriate समय. Don't change it अक्रमomly!
	 */
	चयन (gspca_dev->pixfmt.width) अणु
	हाल 176: /* 176x144 */
		cit_model2_Packet1(gspca_dev, 0x0026, 0x00c2);
		अवरोध;
	हाल 320: /* 320x240 */
		cit_model2_Packet1(gspca_dev, 0x0026, 0x0044);
		अवरोध;
#अगर 0
	हाल VIDEOSIZE_352x240:
		cit_model2_Packet1(gspca_dev, 0x0026, 0x0046);
		अवरोध;
#पूर्ण_अगर
	हाल 352: /* 352x288 */
		cit_model2_Packet1(gspca_dev, 0x0026, 0x0048);
		अवरोध;
	पूर्ण

	cit_model2_Packet1(gspca_dev, 0x0028, v4l2_ctrl_g_ctrl(sd->lighting));
	/* model2 cannot change the backlight compensation जबतक streaming */
	v4l2_ctrl_grab(sd->lighting, true);

	/* color balance rg2 */
	cit_model2_Packet1(gspca_dev, 0x001e, 0x002f);
	/* saturation */
	cit_model2_Packet1(gspca_dev, 0x0020, 0x0034);
	/* color balance yb */
	cit_model2_Packet1(gspca_dev, 0x0022, 0x00a0);

	/* Hardware control command */
	cit_model2_Packet1(gspca_dev, 0x0030, 0x0004);

	वापस 0;
पूर्ण

अटल पूर्णांक cit_start_model3(काष्ठा gspca_dev *gspca_dev)
अणु
	स्थिर अचिन्हित लघु compression = 0; /* 0=none, 7=best frame rate */
	पूर्णांक i, घड़ी_भाग = 0;

	/* HDG not in ibmcam driver, added to see अगर it helps with
	   स्वतः-detecting between model3 and ibm netcamera pro */
	cit_पढ़ो_reg(gspca_dev, 0x128, 1);

	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0100);
	cit_पढ़ो_reg(gspca_dev, 0x0116, 0);
	cit_ग_लिखो_reg(gspca_dev, 0x0060, 0x0116);
	cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x0112);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0123);
	cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0117);
	cit_ग_लिखो_reg(gspca_dev, 0x0040, 0x0108);
	cit_ग_लिखो_reg(gspca_dev, 0x0019, 0x012c);
	cit_ग_लिखो_reg(gspca_dev, 0x0060, 0x0116);
	cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x0115);
	cit_ग_लिखो_reg(gspca_dev, 0x0003, 0x0115);
	cit_पढ़ो_reg(gspca_dev, 0x0115, 0);
	cit_ग_लिखो_reg(gspca_dev, 0x000b, 0x0115);

	/* TESTME HDG not in ibmcam driver, added to see अगर it helps with
	   स्वतः-detecting between model3 and ibm netcamera pro */
	अगर (0) अणु
		cit_ग_लिखो_reg(gspca_dev, 0x0078, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0079, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x00ff, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0xcd41, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0xfffa, 0x0124);
		cit_पढ़ो_reg(gspca_dev, 0x0126, 1);
	पूर्ण

	cit_model3_Packet1(gspca_dev, 0x000a, 0x0040);
	cit_model3_Packet1(gspca_dev, 0x000b, 0x00f6);
	cit_model3_Packet1(gspca_dev, 0x000c, 0x0002);
	cit_model3_Packet1(gspca_dev, 0x000d, 0x0020);
	cit_model3_Packet1(gspca_dev, 0x000e, 0x0033);
	cit_model3_Packet1(gspca_dev, 0x000f, 0x0007);
	cit_model3_Packet1(gspca_dev, 0x0010, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0011, 0x0070);
	cit_model3_Packet1(gspca_dev, 0x0012, 0x0030);
	cit_model3_Packet1(gspca_dev, 0x0013, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0014, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x0015, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x0016, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x0017, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x0018, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x001e, 0x00c3);
	cit_model3_Packet1(gspca_dev, 0x0020, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0028, 0x0010);
	cit_model3_Packet1(gspca_dev, 0x0029, 0x0054);
	cit_model3_Packet1(gspca_dev, 0x002a, 0x0013);
	cit_model3_Packet1(gspca_dev, 0x002b, 0x0007);
	cit_model3_Packet1(gspca_dev, 0x002d, 0x0028);
	cit_model3_Packet1(gspca_dev, 0x002e, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0031, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0032, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0033, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0034, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0035, 0x0038);
	cit_model3_Packet1(gspca_dev, 0x003a, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x003c, 0x001e);
	cit_model3_Packet1(gspca_dev, 0x003f, 0x000a);
	cit_model3_Packet1(gspca_dev, 0x0041, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0046, 0x003f);
	cit_model3_Packet1(gspca_dev, 0x0047, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0050, 0x0005);
	cit_model3_Packet1(gspca_dev, 0x0052, 0x001a);
	cit_model3_Packet1(gspca_dev, 0x0053, 0x0003);
	cit_model3_Packet1(gspca_dev, 0x005a, 0x006b);
	cit_model3_Packet1(gspca_dev, 0x005d, 0x001e);
	cit_model3_Packet1(gspca_dev, 0x005e, 0x0030);
	cit_model3_Packet1(gspca_dev, 0x005f, 0x0041);
	cit_model3_Packet1(gspca_dev, 0x0064, 0x0008);
	cit_model3_Packet1(gspca_dev, 0x0065, 0x0015);
	cit_model3_Packet1(gspca_dev, 0x0068, 0x000f);
	cit_model3_Packet1(gspca_dev, 0x0079, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x007a, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x007c, 0x003f);
	cit_model3_Packet1(gspca_dev, 0x0082, 0x000f);
	cit_model3_Packet1(gspca_dev, 0x0085, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0099, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x009b, 0x0023);
	cit_model3_Packet1(gspca_dev, 0x009c, 0x0022);
	cit_model3_Packet1(gspca_dev, 0x009d, 0x0096);
	cit_model3_Packet1(gspca_dev, 0x009e, 0x0096);
	cit_model3_Packet1(gspca_dev, 0x009f, 0x000a);

	चयन (gspca_dev->pixfmt.width) अणु
	हाल 160:
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0101); /* Same on 160x120, 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x00a0, 0x0103); /* Same on 160x120, 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0078, 0x0105); /* Same on 160x120, 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x010a); /* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x0024, 0x010b); /* Dअगरfers everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x00a9, 0x0119);
		cit_ग_लिखो_reg(gspca_dev, 0x0016, 0x011b);
		cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x011d); /* Same on 160x120, 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0003, 0x011e); /* Same on 160x120, 640x480 */
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0129); /* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x00fc, 0x012b); /* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x0018, 0x0102);
		cit_ग_लिखो_reg(gspca_dev, 0x0004, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x0004, 0x011a);
		cit_ग_लिखो_reg(gspca_dev, 0x0028, 0x011c);
		cit_ग_लिखो_reg(gspca_dev, 0x0022, 0x012a); /* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0118);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0132);
		cit_model3_Packet1(gspca_dev, 0x0021, 0x0001); /* Same */
		cit_ग_लिखो_reg(gspca_dev, compression, 0x0109);
		घड़ी_भाग = 3;
		अवरोध;
	हाल 320:
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0101); /* Same on 160x120, 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x00a0, 0x0103); /* Same on 160x120, 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0078, 0x0105); /* Same on 160x120, 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x010a); /* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x0028, 0x010b); /* Dअगरfers everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x011d); /* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x011e);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0129); /* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x00fc, 0x012b); /* Same */
		/* 4 commands from 160x120 skipped */
		cit_ग_लिखो_reg(gspca_dev, 0x0022, 0x012a); /* Same */
		cit_model3_Packet1(gspca_dev, 0x0021, 0x0001); /* Same */
		cit_ग_लिखो_reg(gspca_dev, compression, 0x0109);
		cit_ग_लिखो_reg(gspca_dev, 0x00d9, 0x0119);
		cit_ग_लिखो_reg(gspca_dev, 0x0006, 0x011b);
		cit_ग_लिखो_reg(gspca_dev, 0x0021, 0x0102); /* Same on 320x240, 640x480 */
		cit_ग_लिखो_reg(gspca_dev, 0x0010, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x0004, 0x011a);
		cit_ग_लिखो_reg(gspca_dev, 0x003f, 0x011c);
		cit_ग_लिखो_reg(gspca_dev, 0x001c, 0x0118);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0132);
		घड़ी_भाग = 5;
		अवरोध;
	हाल 640:
		cit_ग_लिखो_reg(gspca_dev, 0x00f0, 0x0105);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x010a); /* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x0038, 0x010b); /* Dअगरfers everywhere */
		cit_ग_लिखो_reg(gspca_dev, 0x00d9, 0x0119); /* Same on 320x240, 640x480 */
		cit_ग_लिखो_reg(gspca_dev, 0x0006, 0x011b); /* Same on 320x240, 640x480 */
		cit_ग_लिखो_reg(gspca_dev, 0x0004, 0x011d); /* NC */
		cit_ग_लिखो_reg(gspca_dev, 0x0003, 0x011e); /* Same on 160x120, 640x480 */
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0129); /* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x00fc, 0x012b); /* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x0021, 0x0102); /* Same on 320x240, 640x480 */
		cit_ग_लिखो_reg(gspca_dev, 0x0016, 0x0104); /* NC */
		cit_ग_लिखो_reg(gspca_dev, 0x0004, 0x011a); /* Same on 320x240, 640x480 */
		cit_ग_लिखो_reg(gspca_dev, 0x003f, 0x011c); /* Same on 320x240, 640x480 */
		cit_ग_लिखो_reg(gspca_dev, 0x0022, 0x012a); /* Same */
		cit_ग_लिखो_reg(gspca_dev, 0x001c, 0x0118); /* Same on 320x240, 640x480 */
		cit_model3_Packet1(gspca_dev, 0x0021, 0x0001); /* Same */
		cit_ग_लिखो_reg(gspca_dev, compression, 0x0109);
		cit_ग_लिखो_reg(gspca_dev, 0x0040, 0x0101);
		cit_ग_लिखो_reg(gspca_dev, 0x0040, 0x0103);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0132); /* Same on 320x240, 640x480 */
		घड़ी_भाग = 7;
		अवरोध;
	पूर्ण

	cit_model3_Packet1(gspca_dev, 0x007e, 0x000e);	/* Hue */
	cit_model3_Packet1(gspca_dev, 0x0036, 0x0011);	/* Brightness */
	cit_model3_Packet1(gspca_dev, 0x0060, 0x0002);	/* Sharpness */
	cit_model3_Packet1(gspca_dev, 0x0061, 0x0004);	/* Sharpness */
	cit_model3_Packet1(gspca_dev, 0x0062, 0x0005);	/* Sharpness */
	cit_model3_Packet1(gspca_dev, 0x0063, 0x0014);	/* Sharpness */
	cit_model3_Packet1(gspca_dev, 0x0096, 0x00a0);	/* Red sharpness */
	cit_model3_Packet1(gspca_dev, 0x0097, 0x0096);	/* Blue sharpness */
	cit_model3_Packet1(gspca_dev, 0x0067, 0x0001);	/* Contrast */
	cit_model3_Packet1(gspca_dev, 0x005b, 0x000c);	/* Contrast */
	cit_model3_Packet1(gspca_dev, 0x005c, 0x0016);	/* Contrast */
	cit_model3_Packet1(gspca_dev, 0x0098, 0x000b);
	cit_model3_Packet1(gspca_dev, 0x002c, 0x0003);	/* Was 1, broke 640x480 */
	cit_model3_Packet1(gspca_dev, 0x002f, 0x002a);
	cit_model3_Packet1(gspca_dev, 0x0030, 0x0029);
	cit_model3_Packet1(gspca_dev, 0x0037, 0x0002);
	cit_model3_Packet1(gspca_dev, 0x0038, 0x0059);
	cit_model3_Packet1(gspca_dev, 0x003d, 0x002e);
	cit_model3_Packet1(gspca_dev, 0x003e, 0x0028);
	cit_model3_Packet1(gspca_dev, 0x0078, 0x0005);
	cit_model3_Packet1(gspca_dev, 0x007b, 0x0011);
	cit_model3_Packet1(gspca_dev, 0x007d, 0x004b);
	cit_model3_Packet1(gspca_dev, 0x007f, 0x0022);
	cit_model3_Packet1(gspca_dev, 0x0080, 0x000c);
	cit_model3_Packet1(gspca_dev, 0x0081, 0x000b);
	cit_model3_Packet1(gspca_dev, 0x0083, 0x00fd);
	cit_model3_Packet1(gspca_dev, 0x0086, 0x000b);
	cit_model3_Packet1(gspca_dev, 0x0087, 0x000b);
	cit_model3_Packet1(gspca_dev, 0x007e, 0x000e);
	cit_model3_Packet1(gspca_dev, 0x0096, 0x00a0);	/* Red sharpness */
	cit_model3_Packet1(gspca_dev, 0x0097, 0x0096);	/* Blue sharpness */
	cit_model3_Packet1(gspca_dev, 0x0098, 0x000b);

	/* FIXME we should probably use cit_get_घड़ी_भाग() here (in
	   combination with isoc negotiation using the programmable isoc size)
	   like with the IBM netcam pro). */
	cit_ग_लिखो_reg(gspca_dev, घड़ी_भाग, 0x0111); /* Clock Divider */

	चयन (gspca_dev->pixfmt.width) अणु
	हाल 160:
		cit_model3_Packet1(gspca_dev, 0x001f, 0x0000); /* Same */
		cit_model3_Packet1(gspca_dev, 0x0039, 0x001f); /* Same */
		cit_model3_Packet1(gspca_dev, 0x003b, 0x003c); /* Same */
		cit_model3_Packet1(gspca_dev, 0x0040, 0x000a);
		cit_model3_Packet1(gspca_dev, 0x0051, 0x000a);
		अवरोध;
	हाल 320:
		cit_model3_Packet1(gspca_dev, 0x001f, 0x0000); /* Same */
		cit_model3_Packet1(gspca_dev, 0x0039, 0x001f); /* Same */
		cit_model3_Packet1(gspca_dev, 0x003b, 0x003c); /* Same */
		cit_model3_Packet1(gspca_dev, 0x0040, 0x0008);
		cit_model3_Packet1(gspca_dev, 0x0051, 0x000b);
		अवरोध;
	हाल 640:
		cit_model3_Packet1(gspca_dev, 0x001f, 0x0002);	/* !Same */
		cit_model3_Packet1(gspca_dev, 0x0039, 0x003e);	/* !Same */
		cit_model3_Packet1(gspca_dev, 0x0040, 0x0008);
		cit_model3_Packet1(gspca_dev, 0x0051, 0x000a);
		अवरोध;
	पूर्ण

/*	अगर (sd->input_index) अणु */
	अगर (rca_input) अणु
		क्रम (i = 0; i < ARRAY_SIZE(rca_initdata); i++) अणु
			अगर (rca_initdata[i][0])
				cit_पढ़ो_reg(gspca_dev, rca_initdata[i][2], 0);
			अन्यथा
				cit_ग_लिखो_reg(gspca_dev, rca_initdata[i][1],
					      rca_initdata[i][2]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cit_start_model4(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0100);
	cit_ग_लिखो_reg(gspca_dev, 0x00c0, 0x0111);
	cit_ग_लिखो_reg(gspca_dev, 0x00bc, 0x012c);
	cit_ग_लिखो_reg(gspca_dev, 0x0080, 0x012b);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0108);
	cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0133);
	cit_ग_लिखो_reg(gspca_dev, 0x009b, 0x010f);
	cit_ग_लिखो_reg(gspca_dev, 0x00bb, 0x010f);
	cit_model4_Packet1(gspca_dev, 0x0038, 0x0000);
	cit_model4_Packet1(gspca_dev, 0x000a, 0x005c);

	cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
	cit_ग_लिखो_reg(gspca_dev, 0x0004, 0x012f);
	cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0127);
	cit_ग_लिखो_reg(gspca_dev, 0x00fb, 0x012e);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0130);
	cit_ग_लिखो_reg(gspca_dev, 0x8a28, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012f);
	cit_ग_लिखो_reg(gspca_dev, 0xd055, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x000c, 0x0127);
	cit_ग_लिखो_reg(gspca_dev, 0x0009, 0x012e);
	cit_ग_लिखो_reg(gspca_dev, 0xaa28, 0x0124);

	cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
	cit_ग_लिखो_reg(gspca_dev, 0x0012, 0x012f);
	cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x0127);
	cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0130);
	cit_ग_लिखो_reg(gspca_dev, 0x82a8, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0x002a, 0x012d);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x012f);
	cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
	cit_ग_लिखो_reg(gspca_dev, 0xfffa, 0x0124);
	cit_model4_Packet1(gspca_dev, 0x0034, 0x0000);

	चयन (gspca_dev->pixfmt.width) अणु
	हाल 128: /* 128x96 */
		cit_ग_लिखो_reg(gspca_dev, 0x0070, 0x0119);
		cit_ग_लिखो_reg(gspca_dev, 0x00d0, 0x0111);
		cit_ग_लिखो_reg(gspca_dev, 0x0039, 0x010a);
		cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0102);
		cit_ग_लिखो_reg(gspca_dev, 0x0028, 0x0103);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x001e, 0x0105);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0016, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x000a, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x82a8, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0014, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x001a, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a0a, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x005a, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x9545, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x0018, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x0043, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd055, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x001c, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00eb, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0xaa28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0032, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x82a8, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0036, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0xfffa, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x001e, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0017, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x0013, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x0031, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0017, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0078, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0xfea8, 0x0124);
		sd->sof_len = 2;
		अवरोध;
	हाल 160: /* 160x120 */
		cit_ग_लिखो_reg(gspca_dev, 0x0038, 0x0119);
		cit_ग_लिखो_reg(gspca_dev, 0x00d0, 0x0111);
		cit_ग_लिखो_reg(gspca_dev, 0x00b9, 0x010a);
		cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0102);
		cit_ग_लिखो_reg(gspca_dev, 0x0028, 0x0103);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x001e, 0x0105);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0016, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x000b, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x82a8, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0014, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x001a, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a0a, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x005a, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x9545, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x0018, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x0043, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd055, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x001c, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00c7, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0xaa28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0032, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0025, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x82a8, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0036, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0xfffa, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x001e, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0048, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x0035, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x00d0, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0048, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0090, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0xfea8, 0x0124);
		sd->sof_len = 2;
		अवरोध;
	हाल 176: /* 176x144 */
		cit_ग_लिखो_reg(gspca_dev, 0x0038, 0x0119);
		cit_ग_लिखो_reg(gspca_dev, 0x00d0, 0x0111);
		cit_ग_लिखो_reg(gspca_dev, 0x00b9, 0x010a);
		cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0102);
		cit_ग_लिखो_reg(gspca_dev, 0x002c, 0x0103);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x0024, 0x0105);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0016, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0007, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x82a8, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0014, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x001a, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a0a, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x005e, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x9545, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x0018, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x0049, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd055, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x001c, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00c7, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0xaa28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0032, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0028, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x82a8, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0036, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0xfffa, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x001e, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0010, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x0013, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x002a, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0010, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x006d, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0xfea8, 0x0124);
		/* TESTME HDG: this करोes not seem right
		   (it is 2 क्रम all other resolutions) */
		sd->sof_len = 10;
		अवरोध;
	हाल 320: /* 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0070, 0x0119);
		cit_ग_लिखो_reg(gspca_dev, 0x00d0, 0x0111);
		cit_ग_लिखो_reg(gspca_dev, 0x0039, 0x010a);
		cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0102);
		cit_ग_लिखो_reg(gspca_dev, 0x0028, 0x0103);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x001e, 0x0105);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0016, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x000a, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x82a8, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0014, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x001a, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a0a, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x005a, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x9545, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x0018, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x0043, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd055, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x001c, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00eb, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0xaa28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0032, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x82a8, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0036, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0xfffa, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x001e, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0017, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x0013, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x0031, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0017, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0078, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0xfea8, 0x0124);
		sd->sof_len = 2;
		अवरोध;
	हाल 352: /* 352x288 */
		cit_ग_लिखो_reg(gspca_dev, 0x0070, 0x0119);
		cit_ग_लिखो_reg(gspca_dev, 0x00c0, 0x0111);
		cit_ग_लिखो_reg(gspca_dev, 0x0039, 0x010a);
		cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0102);
		cit_ग_लिखो_reg(gspca_dev, 0x002c, 0x0103);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x0024, 0x0105);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0016, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0006, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x82a8, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0014, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x001a, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a0a, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x005e, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x9545, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x0018, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x0049, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd055, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x001c, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00cf, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0xaa28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0032, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x82a8, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0036, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0xfffa, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x00aa, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x001e, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd141, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0010, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0x0013, 0x012e);
		cit_ग_लिखो_reg(gspca_dev, 0x0025, 0x0130);
		cit_ग_लिखो_reg(gspca_dev, 0x8a28, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0010, 0x012d);
		cit_ग_लिखो_reg(gspca_dev, 0x0048, 0x012f);
		cit_ग_लिखो_reg(gspca_dev, 0xd145, 0x0124);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0127);
		cit_ग_लिखो_reg(gspca_dev, 0xfea8, 0x0124);
		sd->sof_len = 2;
		अवरोध;
	पूर्ण

	cit_model4_Packet1(gspca_dev, 0x0038, 0x0004);

	वापस 0;
पूर्ण

अटल पूर्णांक cit_start_ibm_netcam_pro(काष्ठा gspca_dev *gspca_dev)
अणु
	स्थिर अचिन्हित लघु compression = 0; /* 0=none, 7=best frame rate */
	पूर्णांक i, घड़ी_भाग;

	घड़ी_भाग = cit_get_घड़ी_भाग(gspca_dev);
	अगर (घड़ी_भाग < 0)
		वापस घड़ी_भाग;

	cit_ग_लिखो_reg(gspca_dev, 0x0003, 0x0133);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0117);
	cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x0123);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0100);
	cit_ग_लिखो_reg(gspca_dev, 0x0060, 0x0116);
	/* cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x0112); see sd_stop0 */
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0133);
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0123);
	cit_ग_लिखो_reg(gspca_dev, 0x0001, 0x0117);
	cit_ग_लिखो_reg(gspca_dev, 0x0040, 0x0108);
	cit_ग_लिखो_reg(gspca_dev, 0x0019, 0x012c);
	cit_ग_लिखो_reg(gspca_dev, 0x0060, 0x0116);
	/* cit_ग_लिखो_reg(gspca_dev, 0x000b, 0x0115); see sd_stop0 */

	cit_model3_Packet1(gspca_dev, 0x0049, 0x0000);

	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0101); /* Same on 160x120, 320x240 */
	cit_ग_लिखो_reg(gspca_dev, 0x003a, 0x0102); /* Hstart */
	cit_ग_लिखो_reg(gspca_dev, 0x00a0, 0x0103); /* Same on 160x120, 320x240 */
	cit_ग_लिखो_reg(gspca_dev, 0x0078, 0x0105); /* Same on 160x120, 320x240 */
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x010a); /* Same */
	cit_ग_लिखो_reg(gspca_dev, 0x0002, 0x011d); /* Same on 160x120, 320x240 */
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0129); /* Same */
	cit_ग_लिखो_reg(gspca_dev, 0x00fc, 0x012b); /* Same */
	cit_ग_लिखो_reg(gspca_dev, 0x0022, 0x012a); /* Same */

	चयन (gspca_dev->pixfmt.width) अणु
	हाल 160: /* 160x120 */
		cit_ग_लिखो_reg(gspca_dev, 0x0024, 0x010b);
		cit_ग_लिखो_reg(gspca_dev, 0x0089, 0x0119);
		cit_ग_लिखो_reg(gspca_dev, 0x000a, 0x011b);
		cit_ग_लिखो_reg(gspca_dev, 0x0003, 0x011e);
		cit_ग_लिखो_reg(gspca_dev, 0x0007, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x0009, 0x011a);
		cit_ग_लिखो_reg(gspca_dev, 0x008b, 0x011c);
		cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x0118);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0132);
		अवरोध;
	हाल 320: /* 320x240 */
		cit_ग_लिखो_reg(gspca_dev, 0x0028, 0x010b);
		cit_ग_लिखो_reg(gspca_dev, 0x00d9, 0x0119);
		cit_ग_लिखो_reg(gspca_dev, 0x0006, 0x011b);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x011e);
		cit_ग_लिखो_reg(gspca_dev, 0x000e, 0x0104);
		cit_ग_लिखो_reg(gspca_dev, 0x0004, 0x011a);
		cit_ग_लिखो_reg(gspca_dev, 0x003f, 0x011c);
		cit_ग_लिखो_reg(gspca_dev, 0x000c, 0x0118);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0132);
		अवरोध;
	पूर्ण

	cit_model3_Packet1(gspca_dev, 0x0019, 0x0031);
	cit_model3_Packet1(gspca_dev, 0x001a, 0x0003);
	cit_model3_Packet1(gspca_dev, 0x001b, 0x0038);
	cit_model3_Packet1(gspca_dev, 0x001c, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0024, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x0027, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x002a, 0x0004);
	cit_model3_Packet1(gspca_dev, 0x0035, 0x000b);
	cit_model3_Packet1(gspca_dev, 0x003f, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x0044, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x0054, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00c4, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00e7, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x00e9, 0x0001);
	cit_model3_Packet1(gspca_dev, 0x00ee, 0x0000);
	cit_model3_Packet1(gspca_dev, 0x00f3, 0x00c0);

	cit_ग_लिखो_reg(gspca_dev, compression, 0x0109);
	cit_ग_लिखो_reg(gspca_dev, घड़ी_भाग, 0x0111);

/*	अगर (sd->input_index) अणु */
	अगर (rca_input) अणु
		क्रम (i = 0; i < ARRAY_SIZE(rca_initdata); i++) अणु
			अगर (rca_initdata[i][0])
				cit_पढ़ो_reg(gspca_dev, rca_initdata[i][2], 0);
			अन्यथा
				cit_ग_लिखो_reg(gspca_dev, rca_initdata[i][1],
					      rca_initdata[i][2]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* -- start the camera -- */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक packet_size;

	packet_size = cit_get_packet_size(gspca_dev);
	अगर (packet_size < 0)
		वापस packet_size;

	चयन (sd->model) अणु
	हाल CIT_MODEL0:
		cit_start_model0(gspca_dev);
		अवरोध;
	हाल CIT_MODEL1:
		cit_start_model1(gspca_dev);
		अवरोध;
	हाल CIT_MODEL2:
		cit_start_model2(gspca_dev);
		अवरोध;
	हाल CIT_MODEL3:
		cit_start_model3(gspca_dev);
		अवरोध;
	हाल CIT_MODEL4:
		cit_start_model4(gspca_dev);
		अवरोध;
	हाल CIT_IBM_NETCAM_PRO:
		cit_start_ibm_netcam_pro(gspca_dev);
		अवरोध;
	पूर्ण

	/* Program max isoc packet size */
	cit_ग_लिखो_reg(gspca_dev, packet_size >> 8, 0x0106);
	cit_ग_लिखो_reg(gspca_dev, packet_size & 0xff, 0x0107);

	cit_restart_stream(gspca_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sd_isoc_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा usb_पूर्णांकerface_cache *पूर्णांकfc;
	काष्ठा usb_host_पूर्णांकerface *alt;
	पूर्णांक max_packet_size;

	चयन (gspca_dev->pixfmt.width) अणु
	हाल 160:
		max_packet_size = 450;
		अवरोध;
	हाल 176:
		max_packet_size = 600;
		अवरोध;
	शेष:
		max_packet_size = 1022;
		अवरोध;
	पूर्ण

	पूर्णांकfc = gspca_dev->dev->actconfig->पूर्णांकf_cache[0];

	अगर (पूर्णांकfc->num_altsetting < 2)
		वापस -ENODEV;

	alt = &पूर्णांकfc->altsetting[1];

	अगर (alt->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;

	/* Start isoc bandwidth "negotiation" at max isoc bandwidth */
	alt->endpoपूर्णांक[0].desc.wMaxPacketSize = cpu_to_le16(max_packet_size);

	वापस 0;
पूर्ण

अटल पूर्णांक sd_isoc_nego(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक ret, packet_size, min_packet_size;
	काष्ठा usb_host_पूर्णांकerface *alt;

	चयन (gspca_dev->pixfmt.width) अणु
	हाल 160:
		min_packet_size = 200;
		अवरोध;
	हाल 176:
		min_packet_size = 266;
		अवरोध;
	शेष:
		min_packet_size = 400;
		अवरोध;
	पूर्ण

	/*
	 * Existence of altsetting and endpoपूर्णांक was verअगरied in sd_isoc_init()
	 */
	alt = &gspca_dev->dev->actconfig->पूर्णांकf_cache[0]->altsetting[1];
	packet_size = le16_to_cpu(alt->endpoपूर्णांक[0].desc.wMaxPacketSize);
	अगर (packet_size <= min_packet_size)
		वापस -EIO;

	packet_size -= 100;
	अगर (packet_size < min_packet_size)
		packet_size = min_packet_size;
	alt->endpoपूर्णांक[0].desc.wMaxPacketSize = cpu_to_le16(packet_size);

	ret = usb_set_पूर्णांकerface(gspca_dev->dev, gspca_dev->अगरace, 1);
	अगर (ret < 0)
		pr_err("set alt 1 err %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x010c);
पूर्ण

अटल व्योम sd_stop0(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (!gspca_dev->present)
		वापस;

	चयन (sd->model) अणु
	हाल CIT_MODEL0:
		/* HDG winकरोws करोes this, but it causes the cams स्वतःgain to
		   restart from a gain of 0, which करोes not look good when
		   changing resolutions. */
		/* cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0112); */
		cit_ग_लिखो_reg(gspca_dev, 0x00c0, 0x0100); /* LED Off */
		अवरोध;
	हाल CIT_MODEL1:
		cit_send_FF_04_02(gspca_dev);
		cit_पढ़ो_reg(gspca_dev, 0x0100, 0);
		cit_ग_लिखो_reg(gspca_dev, 0x81, 0x0100);	/* LED Off */
		अवरोध;
	हाल CIT_MODEL2:
		v4l2_ctrl_grab(sd->lighting, false);
		fallthrough;
	हाल CIT_MODEL4:
		cit_model2_Packet1(gspca_dev, 0x0030, 0x0004);

		cit_ग_लिखो_reg(gspca_dev, 0x0080, 0x0100);	/* LED Off */
		cit_ग_लिखो_reg(gspca_dev, 0x0020, 0x0111);
		cit_ग_लिखो_reg(gspca_dev, 0x00a0, 0x0111);

		cit_model2_Packet1(gspca_dev, 0x0030, 0x0002);

		cit_ग_लिखो_reg(gspca_dev, 0x0020, 0x0111);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0112);
		अवरोध;
	हाल CIT_MODEL3:
		cit_ग_लिखो_reg(gspca_dev, 0x0006, 0x012c);
		cit_model3_Packet1(gspca_dev, 0x0046, 0x0000);
		cit_पढ़ो_reg(gspca_dev, 0x0116, 0);
		cit_ग_लिखो_reg(gspca_dev, 0x0064, 0x0116);
		cit_पढ़ो_reg(gspca_dev, 0x0115, 0);
		cit_ग_लिखो_reg(gspca_dev, 0x0003, 0x0115);
		cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x0123);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0117);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0112);
		cit_ग_लिखो_reg(gspca_dev, 0x0080, 0x0100);
		अवरोध;
	हाल CIT_IBM_NETCAM_PRO:
		cit_model3_Packet1(gspca_dev, 0x0049, 0x00ff);
		cit_ग_लिखो_reg(gspca_dev, 0x0006, 0x012c);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0116);
		/* HDG winकरोws करोes this, but I cannot get the camera
		   to restart with this without reकरोing the entire init
		   sequence which makes चयनing modes really slow */
		/* cit_ग_लिखो_reg(gspca_dev, 0x0006, 0x0115); */
		cit_ग_लिखो_reg(gspca_dev, 0x0008, 0x0123);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0117);
		cit_ग_लिखो_reg(gspca_dev, 0x0003, 0x0133);
		cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0111);
		/* HDG winकरोws करोes this, but I get a green picture when
		   restarting the stream after this */
		/* cit_ग_लिखो_reg(gspca_dev, 0x0000, 0x0112); */
		cit_ग_लिखो_reg(gspca_dev, 0x00c0, 0x0100);
		अवरोध;
	पूर्ण

#अगर IS_ENABLED(CONFIG_INPUT)
	/* If the last button state is pressed, release it now! */
	अगर (sd->button_state) अणु
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
		input_sync(gspca_dev->input_dev);
		sd->button_state = 0;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल u8 *cit_find_sof(काष्ठा gspca_dev *gspca_dev, u8 *data, पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 byte3 = 0, byte4 = 0;
	पूर्णांक i;

	चयन (sd->model) अणु
	हाल CIT_MODEL0:
	हाल CIT_MODEL1:
	हाल CIT_MODEL3:
	हाल CIT_IBM_NETCAM_PRO:
		चयन (gspca_dev->pixfmt.width) अणु
		हाल 160: /* 160x120 */
			byte3 = 0x02;
			byte4 = 0x0a;
			अवरोध;
		हाल 176: /* 176x144 */
			byte3 = 0x02;
			byte4 = 0x0e;
			अवरोध;
		हाल 320: /* 320x240 */
			byte3 = 0x02;
			byte4 = 0x08;
			अवरोध;
		हाल 352: /* 352x288 */
			byte3 = 0x02;
			byte4 = 0x00;
			अवरोध;
		हाल 640:
			byte3 = 0x03;
			byte4 = 0x08;
			अवरोध;
		पूर्ण

		/* These have a dअगरferent byte3 */
		अगर (sd->model <= CIT_MODEL1)
			byte3 = 0x00;

		क्रम (i = 0; i < len; i++) अणु
			/* For this model the SOF always starts at offset 0
			   so no need to search the entire frame */
			अगर (sd->model == CIT_MODEL0 && sd->sof_पढ़ो != i)
				अवरोध;

			चयन (sd->sof_पढ़ो) अणु
			हाल 0:
				अगर (data[i] == 0x00)
					sd->sof_पढ़ो++;
				अवरोध;
			हाल 1:
				अगर (data[i] == 0xff)
					sd->sof_पढ़ो++;
				अन्यथा अगर (data[i] == 0x00)
					sd->sof_पढ़ो = 1;
				अन्यथा
					sd->sof_पढ़ो = 0;
				अवरोध;
			हाल 2:
				अगर (data[i] == byte3)
					sd->sof_पढ़ो++;
				अन्यथा अगर (data[i] == 0x00)
					sd->sof_पढ़ो = 1;
				अन्यथा
					sd->sof_पढ़ो = 0;
				अवरोध;
			हाल 3:
				अगर (data[i] == byte4) अणु
					sd->sof_पढ़ो = 0;
					वापस data + i + (sd->sof_len - 3);
				पूर्ण
				अगर (byte3 == 0x00 && data[i] == 0xff)
					sd->sof_पढ़ो = 2;
				अन्यथा अगर (data[i] == 0x00)
					sd->sof_पढ़ो = 1;
				अन्यथा
					sd->sof_पढ़ो = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल CIT_MODEL2:
	हाल CIT_MODEL4:
		/* TESTME we need to find a दीर्घer sof signature to aव्योम
		   false positives */
		क्रम (i = 0; i < len; i++) अणु
			चयन (sd->sof_पढ़ो) अणु
			हाल 0:
				अगर (data[i] == 0x00)
					sd->sof_पढ़ो++;
				अवरोध;
			हाल 1:
				sd->sof_पढ़ो = 0;
				अगर (data[i] == 0xff) अणु
					अगर (i >= 4)
						gspca_dbg(gspca_dev, D_FRAM,
							  "header found at offset: %d: %02x %02x 00 %3ph\n\n",
							  i - 1,
							  data[i - 4],
							  data[i - 3],
							  &data[i]);
					अन्यथा
						gspca_dbg(gspca_dev, D_FRAM,
							  "header found at offset: %d: 00 %3ph\n\n",
							  i - 1,
							  &data[i]);
					वापस data + i + (sd->sof_len - 1);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data, पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	अचिन्हित अक्षर *sof;

	sof = cit_find_sof(gspca_dev, data, len);
	अगर (sof) अणु
		पूर्णांक n;

		/* finish decoding current frame */
		n = sof - data;
		अगर (n > sd->sof_len)
			n -= sd->sof_len;
		अन्यथा
			n = 0;
		gspca_frame_add(gspca_dev, LAST_PACKET,
				data, n);
		gspca_frame_add(gspca_dev, FIRST_PACKET, शून्य, 0);
		len -= sof - data;
		data = sof;
	पूर्ण

	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण

#अगर IS_ENABLED(CONFIG_INPUT)
अटल व्योम cit_check_button(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक new_button_state;
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	चयन (sd->model) अणु
	हाल CIT_MODEL3:
	हाल CIT_IBM_NETCAM_PRO:
		अवरोध;
	शेष: /* TEST ME unknown अगर this works on other models too */
		वापस;
	पूर्ण

	/* Read the button state */
	cit_पढ़ो_reg(gspca_dev, 0x0113, 0);
	new_button_state = !gspca_dev->usb_buf[0];

	/* Tell the cam we've seen the button press, notice that this
	   is a nop (iow the cam keeps reporting pressed) until the
	   button is actually released. */
	अगर (new_button_state)
		cit_ग_लिखो_reg(gspca_dev, 0x01, 0x0113);

	अगर (sd->button_state != new_button_state) अणु
		input_report_key(gspca_dev->input_dev, KEY_CAMERA,
				 new_button_state);
		input_sync(gspca_dev->input_dev);
		sd->button_state = new_button_state;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming)
		वापस 0;

	अगर (sd->stop_on_control_change)
		sd_stopN(gspca_dev);
	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		cit_set_brightness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		cit_set_contrast(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		cit_set_hue(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		cit_set_hflip(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		cit_set_sharpness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_BACKLIGHT_COMPENSATION:
		cit_set_lighting(gspca_dev, ctrl->val);
		अवरोध;
	पूर्ण
	अगर (sd->stop_on_control_change)
		cit_restart_stream(gspca_dev);
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;
	bool has_brightness;
	bool has_contrast;
	bool has_hue;
	bool has_sharpness;
	bool has_lighting;
	bool has_hflip;

	has_brightness = has_contrast = has_hue =
		has_sharpness = has_hflip = has_lighting = false;
	चयन (sd->model) अणु
	हाल CIT_MODEL0:
		has_contrast = has_hflip = true;
		अवरोध;
	हाल CIT_MODEL1:
		has_brightness = has_contrast =
			has_sharpness = has_lighting = true;
		अवरोध;
	हाल CIT_MODEL2:
		has_brightness = has_hue = has_lighting = true;
		अवरोध;
	हाल CIT_MODEL3:
		has_brightness = has_contrast = has_sharpness = true;
		अवरोध;
	हाल CIT_MODEL4:
		has_brightness = has_hue = true;
		अवरोध;
	हाल CIT_IBM_NETCAM_PRO:
		has_brightness = has_hue =
			has_sharpness = has_hflip = has_lighting = true;
		अवरोध;
	पूर्ण
	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 5);
	अगर (has_brightness)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 63, 1, 32);
	अगर (has_contrast)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 20, 1, 10);
	अगर (has_hue)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_HUE, 0, 127, 1, 63);
	अगर (has_sharpness)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SHARPNESS, 0, 6, 1, 3);
	अगर (has_lighting)
		sd->lighting = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BACKLIGHT_COMPENSATION, 0, 2, 1, 1);
	अगर (has_hflip)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	वापस 0;
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = MODULE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_controls = sd_init_controls,
	.start = sd_start,
	.stopN = sd_stopN,
	.stop0 = sd_stop0,
	.pkt_scan = sd_pkt_scan,
#अगर IS_ENABLED(CONFIG_INPUT)
	.dq_callback = cit_check_button,
	.other_input = 1,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा sd_desc sd_desc_isoc_nego = अणु
	.name = MODULE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_controls = sd_init_controls,
	.start = sd_start,
	.isoc_init = sd_isoc_init,
	.isoc_nego = sd_isoc_nego,
	.stopN = sd_stopN,
	.stop0 = sd_stop0,
	.pkt_scan = sd_pkt_scan,
#अगर IS_ENABLED(CONFIG_INPUT)
	.dq_callback = cit_check_button,
	.other_input = 1,
#पूर्ण_अगर
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणु USB_DEVICE_VER(0x0545, 0x8080, 0x0001, 0x0001), .driver_info = CIT_MODEL0 पूर्ण,
	अणु USB_DEVICE_VER(0x0545, 0x8080, 0x0002, 0x0002), .driver_info = CIT_MODEL1 पूर्ण,
	अणु USB_DEVICE_VER(0x0545, 0x8080, 0x030a, 0x030a), .driver_info = CIT_MODEL2 पूर्ण,
	अणु USB_DEVICE_VER(0x0545, 0x8080, 0x0301, 0x0301), .driver_info = CIT_MODEL3 पूर्ण,
	अणु USB_DEVICE_VER(0x0545, 0x8002, 0x030a, 0x030a), .driver_info = CIT_MODEL4 पूर्ण,
	अणु USB_DEVICE_VER(0x0545, 0x800c, 0x030a, 0x030a), .driver_info = CIT_MODEL2 पूर्ण,
	अणु USB_DEVICE_VER(0x0545, 0x800d, 0x030a, 0x030a), .driver_info = CIT_MODEL4 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, device_table);

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	स्थिर काष्ठा sd_desc *desc = &sd_desc;

	चयन (id->driver_info) अणु
	हाल CIT_MODEL0:
	हाल CIT_MODEL1:
		अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber != 2)
			वापस -ENODEV;
		अवरोध;
	हाल CIT_MODEL2:
	हाल CIT_MODEL4:
		अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber != 0)
			वापस -ENODEV;
		अवरोध;
	हाल CIT_MODEL3:
		अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber != 0)
			वापस -ENODEV;
		/* FIXME this likely applies to all model3 cams and probably
		   to other models too. */
		अगर (ibm_netcam_pro)
			desc = &sd_desc_isoc_nego;
		अवरोध;
	पूर्ण

	वापस gspca_dev_probe2(पूर्णांकf, id, desc, माप(काष्ठा sd), THIS_MODULE);
पूर्ण

अटल काष्ठा usb_driver sd_driver = अणु
	.name = MODULE_NAME,
	.id_table = device_table,
	.probe = sd_probe,
	.disconnect = gspca_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = gspca_suspend,
	.resume = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(sd_driver);
