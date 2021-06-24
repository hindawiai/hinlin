<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ov534-ov7xxx gspca driver
 *
 * Copyright (C) 2008 Antonio Ospite <ospite@studenti.unina.it>
 * Copyright (C) 2008 Jim Paris <jim@jtan.com>
 * Copyright (C) 2009 Jean-Francois Moine http://moinejf.मुक्त.fr
 *
 * Based on a prototype written by Mark Ferrell <majortrips@gmail.com>
 * USB protocol reverse engineered by Jim Paris <jim@jtan.com>
 * https://jim.sh/svn/jim/devl/playstation/ps3/eye/test/
 *
 * PS3 Eye camera enhanced by Riअक्षरd Kaswy http://kaswy.मुक्त.fr
 * PS3 Eye camera - brightness, contrast, awb, agc, aec controls
 *                  added by Max Thrun <bear24rw@gmail.com>
 * PS3 Eye camera - FPS range extended by Joseph Howse
 *                  <josephhowse@nummist.com> https://nummist.com
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "ov534"

#समावेश "gspca.h"

#समावेश <linux/fixp-arith.h>
#समावेश <media/v4l2-ctrls.h>

#घोषणा OV534_REG_ADDRESS	0xf1	/* sensor address */
#घोषणा OV534_REG_SUBADDR	0xf2
#घोषणा OV534_REG_WRITE		0xf3
#घोषणा OV534_REG_READ		0xf4
#घोषणा OV534_REG_OPERATION	0xf5
#घोषणा OV534_REG_STATUS	0xf6

#घोषणा OV534_OP_WRITE_3	0x37
#घोषणा OV534_OP_WRITE_2	0x33
#घोषणा OV534_OP_READ_2		0xf9

#घोषणा CTRL_TIMEOUT 500
#घोषणा DEFAULT_FRAME_RATE 30

MODULE_AUTHOR("Antonio Ospite <ospite@studenti.unina.it>");
MODULE_DESCRIPTION("GSPCA/OV534 USB Camera Driver");
MODULE_LICENSE("GPL");

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl *hue;
	काष्ठा v4l2_ctrl *saturation;
	काष्ठा v4l2_ctrl *brightness;
	काष्ठा v4l2_ctrl *contrast;
	काष्ठा अणु /* gain control cluster */
		काष्ठा v4l2_ctrl *स्वतःgain;
		काष्ठा v4l2_ctrl *gain;
	पूर्ण;
	काष्ठा v4l2_ctrl *स्वतःwhitebalance;
	काष्ठा अणु /* exposure control cluster */
		काष्ठा v4l2_ctrl *स्वतःexposure;
		काष्ठा v4l2_ctrl *exposure;
	पूर्ण;
	काष्ठा v4l2_ctrl *sharpness;
	काष्ठा v4l2_ctrl *hflip;
	काष्ठा v4l2_ctrl *vflip;
	काष्ठा v4l2_ctrl *plfreq;

	__u32 last_pts;
	u16 last_fid;
	u8 frame_rate;

	u8 sensor;
पूर्ण;
क्रमागत sensors अणु
	SENSOR_OV767x,
	SENSOR_OV772x,
	NSENSORS
पूर्ण;

अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev);
अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev);


अटल स्थिर काष्ठा v4l2_pix_क्रमmat ov772x_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_YUYV, V4L2_FIELD_NONE,
	 .bytesperline = 320 * 2,
	 .sizeimage = 320 * 240 * 2,
	 .colorspace = V4L2_COLORSPACE_SRGB,
	 .priv = 1पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_YUYV, V4L2_FIELD_NONE,
	 .bytesperline = 640 * 2,
	 .sizeimage = 640 * 480 * 2,
	 .colorspace = V4L2_COLORSPACE_SRGB,
	 .priv = 0पूर्ण,
	अणु320, 240, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
	 .bytesperline = 320,
	 .sizeimage = 320 * 240,
	 .colorspace = V4L2_COLORSPACE_SRGB,
	 .priv = 1पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
	 .bytesperline = 640,
	 .sizeimage = 640 * 480,
	 .colorspace = V4L2_COLORSPACE_SRGB,
	 .priv = 0पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा v4l2_pix_क्रमmat ov767x_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEGपूर्ण,
	अणु640, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEGपूर्ण,
पूर्ण;

अटल स्थिर u8 qvga_rates[] = अणु187, 150, 137, 125, 100, 75, 60, 50, 37, 30पूर्ण;
अटल स्थिर u8 vga_rates[] = अणु60, 50, 40, 30, 15पूर्ण;

अटल स्थिर काष्ठा framerates ov772x_framerates[] = अणु
	अणु /* 320x240 */
		.rates = qvga_rates,
		.nrates = ARRAY_SIZE(qvga_rates),
	पूर्ण,
	अणु /* 640x480 */
		.rates = vga_rates,
		.nrates = ARRAY_SIZE(vga_rates),
	पूर्ण,
	अणु /* 320x240 SGBRG8 */
		.rates = qvga_rates,
		.nrates = ARRAY_SIZE(qvga_rates),
	पूर्ण,
	अणु /* 640x480 SGBRG8 */
		.rates = vga_rates,
		.nrates = ARRAY_SIZE(vga_rates),
	पूर्ण,
पूर्ण;

काष्ठा reg_array अणु
	स्थिर u8 (*val)[2];
	पूर्णांक len;
पूर्ण;

अटल स्थिर u8 bridge_init_767x[][2] = अणु
/* comments from the ms-win file apollo7670.set */
/* str1 */
	अणु0xf1, 0x42पूर्ण,
	अणु0x88, 0xf8पूर्ण,
	अणु0x89, 0xffपूर्ण,
	अणु0x76, 0x03पूर्ण,
	अणु0x92, 0x03पूर्ण,
	अणु0x95, 0x10पूर्ण,
	अणु0xe2, 0x00पूर्ण,
	अणु0xe7, 0x3eपूर्ण,
	अणु0x8d, 0x1cपूर्ण,
	अणु0x8e, 0x00पूर्ण,
	अणु0x8f, 0x00पूर्ण,
	अणु0x1f, 0x00पूर्ण,
	अणु0xc3, 0xf9पूर्ण,
	अणु0x89, 0xffपूर्ण,
	अणु0x88, 0xf8पूर्ण,
	अणु0x76, 0x03पूर्ण,
	अणु0x92, 0x01पूर्ण,
	अणु0x93, 0x18पूर्ण,
	अणु0x1c, 0x00पूर्ण,
	अणु0x1d, 0x48पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0xffपूर्ण,
	अणु0x1d, 0x02पूर्ण,
	अणु0x1d, 0x58पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1c, 0x0aपूर्ण,
	अणु0x1d, 0x0aपूर्ण,
	अणु0x1d, 0x0eपूर्ण,
	अणु0xc0, 0x50पूर्ण,	/* HSize 640 */
	अणु0xc1, 0x3cपूर्ण,	/* VSize 480 */
	अणु0x34, 0x05पूर्ण,	/* enable Audio Suspend mode */
	अणु0xc2, 0x0cपूर्ण,	/* Input YUV */
	अणु0xc3, 0xf9पूर्ण,	/* enable PRE */
	अणु0x34, 0x05पूर्ण,	/* enable Audio Suspend mode */
	अणु0xe7, 0x2eपूर्ण,	/* this solves failure of "SuspendResumeTest" */
	अणु0x31, 0xf9पूर्ण,	/* enable 1.8V Suspend */
	अणु0x35, 0x02पूर्ण,	/* turn on JPEG */
	अणु0xd9, 0x10पूर्ण,
	अणु0x25, 0x42पूर्ण,	/* GPIO[8]:Input */
	अणु0x94, 0x11पूर्ण,	/* If the शेष setting is loaded when
			 * प्रणाली boots up, this flag is बंदd here */
पूर्ण;
अटल स्थिर u8 sensor_init_767x[][2] = अणु
	अणु0x12, 0x80पूर्ण,
	अणु0x11, 0x03पूर्ण,
	अणु0x3a, 0x04पूर्ण,
	अणु0x12, 0x00पूर्ण,
	अणु0x17, 0x13पूर्ण,
	अणु0x18, 0x01पूर्ण,
	अणु0x32, 0xb6पूर्ण,
	अणु0x19, 0x02पूर्ण,
	अणु0x1a, 0x7aपूर्ण,
	अणु0x03, 0x0aपूर्ण,
	अणु0x0c, 0x00पूर्ण,
	अणु0x3e, 0x00पूर्ण,
	अणु0x70, 0x3aपूर्ण,
	अणु0x71, 0x35पूर्ण,
	अणु0x72, 0x11पूर्ण,
	अणु0x73, 0xf0पूर्ण,
	अणु0xa2, 0x02पूर्ण,
	अणु0x7a, 0x2aपूर्ण,	/* set Gamma=1.6 below */
	अणु0x7b, 0x12पूर्ण,
	अणु0x7c, 0x1dपूर्ण,
	अणु0x7d, 0x2dपूर्ण,
	अणु0x7e, 0x45पूर्ण,
	अणु0x7f, 0x50पूर्ण,
	अणु0x80, 0x59पूर्ण,
	अणु0x81, 0x62पूर्ण,
	अणु0x82, 0x6bपूर्ण,
	अणु0x83, 0x73पूर्ण,
	अणु0x84, 0x7bपूर्ण,
	अणु0x85, 0x8aपूर्ण,
	अणु0x86, 0x98पूर्ण,
	अणु0x87, 0xb2पूर्ण,
	अणु0x88, 0xcaपूर्ण,
	अणु0x89, 0xe0पूर्ण,
	अणु0x13, 0xe0पूर्ण,
	अणु0x00, 0x00पूर्ण,
	अणु0x10, 0x00पूर्ण,
	अणु0x0d, 0x40पूर्ण,
	अणु0x14, 0x38पूर्ण,	/* gain max 16x */
	अणु0xa5, 0x05पूर्ण,
	अणु0xab, 0x07पूर्ण,
	अणु0x24, 0x95पूर्ण,
	अणु0x25, 0x33पूर्ण,
	अणु0x26, 0xe3पूर्ण,
	अणु0x9f, 0x78पूर्ण,
	अणु0xa0, 0x68पूर्ण,
	अणु0xa1, 0x03पूर्ण,
	अणु0xa6, 0xd8पूर्ण,
	अणु0xa7, 0xd8पूर्ण,
	अणु0xa8, 0xf0पूर्ण,
	अणु0xa9, 0x90पूर्ण,
	अणु0xaa, 0x94पूर्ण,
	अणु0x13, 0xe5पूर्ण,
	अणु0x0e, 0x61पूर्ण,
	अणु0x0f, 0x4bपूर्ण,
	अणु0x16, 0x02पूर्ण,
	अणु0x21, 0x02पूर्ण,
	अणु0x22, 0x91पूर्ण,
	अणु0x29, 0x07पूर्ण,
	अणु0x33, 0x0bपूर्ण,
	अणु0x35, 0x0bपूर्ण,
	अणु0x37, 0x1dपूर्ण,
	अणु0x38, 0x71पूर्ण,
	अणु0x39, 0x2aपूर्ण,
	अणु0x3c, 0x78पूर्ण,
	अणु0x4d, 0x40पूर्ण,
	अणु0x4e, 0x20पूर्ण,
	अणु0x69, 0x00पूर्ण,
	अणु0x6b, 0x4aपूर्ण,
	अणु0x74, 0x10पूर्ण,
	अणु0x8d, 0x4fपूर्ण,
	अणु0x8e, 0x00पूर्ण,
	अणु0x8f, 0x00पूर्ण,
	अणु0x90, 0x00पूर्ण,
	अणु0x91, 0x00पूर्ण,
	अणु0x96, 0x00पूर्ण,
	अणु0x9a, 0x80पूर्ण,
	अणु0xb0, 0x84पूर्ण,
	अणु0xb1, 0x0cपूर्ण,
	अणु0xb2, 0x0eपूर्ण,
	अणु0xb3, 0x82पूर्ण,
	अणु0xb8, 0x0aपूर्ण,
	अणु0x43, 0x0aपूर्ण,
	अणु0x44, 0xf0पूर्ण,
	अणु0x45, 0x34पूर्ण,
	अणु0x46, 0x58पूर्ण,
	अणु0x47, 0x28पूर्ण,
	अणु0x48, 0x3aपूर्ण,
	अणु0x59, 0x88पूर्ण,
	अणु0x5a, 0x88पूर्ण,
	अणु0x5b, 0x44पूर्ण,
	अणु0x5c, 0x67पूर्ण,
	अणु0x5d, 0x49पूर्ण,
	अणु0x5e, 0x0eपूर्ण,
	अणु0x6c, 0x0aपूर्ण,
	अणु0x6d, 0x55पूर्ण,
	अणु0x6e, 0x11पूर्ण,
	अणु0x6f, 0x9fपूर्ण,
	अणु0x6a, 0x40पूर्ण,
	अणु0x01, 0x40पूर्ण,
	अणु0x02, 0x40पूर्ण,
	अणु0x13, 0xe7पूर्ण,
	अणु0x4f, 0x80पूर्ण,
	अणु0x50, 0x80पूर्ण,
	अणु0x51, 0x00पूर्ण,
	अणु0x52, 0x22पूर्ण,
	अणु0x53, 0x5eपूर्ण,
	अणु0x54, 0x80पूर्ण,
	अणु0x58, 0x9eपूर्ण,
	अणु0x41, 0x08पूर्ण,
	अणु0x3f, 0x00पूर्ण,
	अणु0x75, 0x04पूर्ण,
	अणु0x76, 0xe1पूर्ण,
	अणु0x4c, 0x00पूर्ण,
	अणु0x77, 0x01पूर्ण,
	अणु0x3d, 0xc2पूर्ण,
	अणु0x4b, 0x09पूर्ण,
	अणु0xc9, 0x60पूर्ण,
	अणु0x41, 0x38पूर्ण,	/* jfm: स्वतः sharpness + स्वतः de-noise  */
	अणु0x56, 0x40पूर्ण,
	अणु0x34, 0x11पूर्ण,
	अणु0x3b, 0xc2पूर्ण,
	अणु0xa4, 0x8aपूर्ण,	/* Night mode trigger poपूर्णांक */
	अणु0x96, 0x00पूर्ण,
	अणु0x97, 0x30पूर्ण,
	अणु0x98, 0x20पूर्ण,
	अणु0x99, 0x20पूर्ण,
	अणु0x9a, 0x84पूर्ण,
	अणु0x9b, 0x29पूर्ण,
	अणु0x9c, 0x03पूर्ण,
	अणु0x9d, 0x4cपूर्ण,
	अणु0x9e, 0x3fपूर्ण,
	अणु0x78, 0x04पूर्ण,
	अणु0x79, 0x01पूर्ण,
	अणु0xc8, 0xf0पूर्ण,
	अणु0x79, 0x0fपूर्ण,
	अणु0xc8, 0x00पूर्ण,
	अणु0x79, 0x10पूर्ण,
	अणु0xc8, 0x7eपूर्ण,
	अणु0x79, 0x0aपूर्ण,
	अणु0xc8, 0x80पूर्ण,
	अणु0x79, 0x0bपूर्ण,
	अणु0xc8, 0x01पूर्ण,
	अणु0x79, 0x0cपूर्ण,
	अणु0xc8, 0x0fपूर्ण,
	अणु0x79, 0x0dपूर्ण,
	अणु0xc8, 0x20पूर्ण,
	अणु0x79, 0x09पूर्ण,
	अणु0xc8, 0x80पूर्ण,
	अणु0x79, 0x02पूर्ण,
	अणु0xc8, 0xc0पूर्ण,
	अणु0x79, 0x03पूर्ण,
	अणु0xc8, 0x20पूर्ण,
	अणु0x79, 0x26पूर्ण,
पूर्ण;
अटल स्थिर u8 bridge_start_vga_767x[][2] = अणु
/* str59 JPG */
	अणु0x94, 0xaaपूर्ण,
	अणु0xf1, 0x42पूर्ण,
	अणु0xe5, 0x04पूर्ण,
	अणु0xc0, 0x50पूर्ण,
	अणु0xc1, 0x3cपूर्ण,
	अणु0xc2, 0x0cपूर्ण,
	अणु0x35, 0x02पूर्ण,	/* turn on JPEG */
	अणु0xd9, 0x10पूर्ण,
	अणु0xda, 0x00पूर्ण,	/* क्रम higher घड़ी rate(30fps) */
	अणु0x34, 0x05पूर्ण,	/* enable Audio Suspend mode */
	अणु0xc3, 0xf9पूर्ण,	/* enable PRE */
	अणु0x8c, 0x00पूर्ण,	/* CIF VSize LSB[2:0] */
	अणु0x8d, 0x1cपूर्ण,	/* output YUV */
/*	अणु0x34, 0x05पूर्ण,	 * enable Audio Suspend mode (?) */
	अणु0x50, 0x00पूर्ण,	/* H/V भागider=0 */
	अणु0x51, 0xa0पूर्ण,	/* input H=640/4 */
	अणु0x52, 0x3cपूर्ण,	/* input V=480/4 */
	अणु0x53, 0x00पूर्ण,	/* offset X=0 */
	अणु0x54, 0x00पूर्ण,	/* offset Y=0 */
	अणु0x55, 0x00पूर्ण,	/* H/V size[8]=0 */
	अणु0x57, 0x00पूर्ण,	/* H-size[9]=0 */
	अणु0x5c, 0x00पूर्ण,	/* output size[9:8]=0 */
	अणु0x5a, 0xa0पूर्ण,	/* output H=640/4 */
	अणु0x5b, 0x78पूर्ण,	/* output V=480/4 */
	अणु0x1c, 0x0aपूर्ण,
	अणु0x1d, 0x0aपूर्ण,
	अणु0x94, 0x11पूर्ण,
पूर्ण;
अटल स्थिर u8 sensor_start_vga_767x[][2] = अणु
	अणु0x11, 0x01पूर्ण,
	अणु0x1e, 0x04पूर्ण,
	अणु0x19, 0x02पूर्ण,
	अणु0x1a, 0x7aपूर्ण,
पूर्ण;
अटल स्थिर u8 bridge_start_qvga_767x[][2] = अणु
/* str86 JPG */
	अणु0x94, 0xaaपूर्ण,
	अणु0xf1, 0x42पूर्ण,
	अणु0xe5, 0x04पूर्ण,
	अणु0xc0, 0x80पूर्ण,
	अणु0xc1, 0x60पूर्ण,
	अणु0xc2, 0x0cपूर्ण,
	अणु0x35, 0x02पूर्ण,	/* turn on JPEG */
	अणु0xd9, 0x10पूर्ण,
	अणु0xc0, 0x50पूर्ण,	/* CIF HSize 640 */
	अणु0xc1, 0x3cपूर्ण,	/* CIF VSize 480 */
	अणु0x8c, 0x00पूर्ण,	/* CIF VSize LSB[2:0] */
	अणु0x8d, 0x1cपूर्ण,	/* output YUV */
	अणु0x34, 0x05पूर्ण,	/* enable Audio Suspend mode */
	अणु0xc2, 0x4cपूर्ण,	/* output YUV and Enable DCW */
	अणु0xc3, 0xf9पूर्ण,	/* enable PRE */
	अणु0x1c, 0x00पूर्ण,	/* indirect addressing */
	अणु0x1d, 0x48पूर्ण,	/* output YUV422 */
	अणु0x50, 0x89पूर्ण,	/* H/V भागider=/2; plus DCW AVG */
	अणु0x51, 0xa0पूर्ण,	/* DCW input H=640/4 */
	अणु0x52, 0x78पूर्ण,	/* DCW input V=480/4 */
	अणु0x53, 0x00पूर्ण,	/* offset X=0 */
	अणु0x54, 0x00पूर्ण,	/* offset Y=0 */
	अणु0x55, 0x00पूर्ण,	/* H/V size[8]=0 */
	अणु0x57, 0x00पूर्ण,	/* H-size[9]=0 */
	अणु0x5c, 0x00पूर्ण,	/* DCW output size[9:8]=0 */
	अणु0x5a, 0x50पूर्ण,	/* DCW output H=320/4 */
	अणु0x5b, 0x3cपूर्ण,	/* DCW output V=240/4 */
	अणु0x1c, 0x0aपूर्ण,
	अणु0x1d, 0x0aपूर्ण,
	अणु0x94, 0x11पूर्ण,
पूर्ण;
अटल स्थिर u8 sensor_start_qvga_767x[][2] = अणु
	अणु0x11, 0x01पूर्ण,
	अणु0x1e, 0x04पूर्ण,
	अणु0x19, 0x02पूर्ण,
	अणु0x1a, 0x7aपूर्ण,
पूर्ण;

अटल स्थिर u8 bridge_init_772x[][2] = अणु
	अणु 0x88, 0xf8 पूर्ण,
	अणु 0x89, 0xff पूर्ण,
	अणु 0x76, 0x03 पूर्ण,
	अणु 0x92, 0x01 पूर्ण,
	अणु 0x93, 0x18 पूर्ण,
	अणु 0x94, 0x10 पूर्ण,
	अणु 0x95, 0x10 पूर्ण,
	अणु 0xe2, 0x00 पूर्ण,
	अणु 0xe7, 0x3e पूर्ण,

	अणु 0x96, 0x00 पूर्ण,

	अणु 0x97, 0x20 पूर्ण,
	अणु 0x97, 0x20 पूर्ण,
	अणु 0x97, 0x20 पूर्ण,
	अणु 0x97, 0x0a पूर्ण,
	अणु 0x97, 0x3f पूर्ण,
	अणु 0x97, 0x4a पूर्ण,
	अणु 0x97, 0x20 पूर्ण,
	अणु 0x97, 0x15 पूर्ण,
	अणु 0x97, 0x0b पूर्ण,

	अणु 0x8e, 0x40 पूर्ण,
	अणु 0x1f, 0x81 पूर्ण,
	अणु 0x34, 0x05 पूर्ण,
	अणु 0xe3, 0x04 पूर्ण,
	अणु 0x89, 0x00 पूर्ण,
	अणु 0x76, 0x00 पूर्ण,
	अणु 0xe7, 0x2e पूर्ण,
	अणु 0x31, 0xf9 पूर्ण,
	अणु 0x25, 0x42 पूर्ण,
	अणु 0x21, 0xf0 पूर्ण,

	अणु 0x1c, 0x0a पूर्ण,
	अणु 0x1d, 0x08 पूर्ण, /* turn on UVC header */
	अणु 0x1d, 0x0e पूर्ण, /* .. */
पूर्ण;
अटल स्थिर u8 sensor_init_772x[][2] = अणु
	अणु 0x12, 0x80 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
/*fixme: better have a delay?*/
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,

	अणु 0x3d, 0x03 पूर्ण,
	अणु 0x17, 0x26 पूर्ण,
	अणु 0x18, 0xa0 पूर्ण,
	अणु 0x19, 0x07 पूर्ण,
	अणु 0x1a, 0xf0 पूर्ण,
	अणु 0x32, 0x00 पूर्ण,
	अणु 0x29, 0xa0 पूर्ण,
	अणु 0x2c, 0xf0 पूर्ण,
	अणु 0x65, 0x20 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x42, 0x7f पूर्ण,
	अणु 0x63, 0xaa पूर्ण,		/* AWB - was e0 */
	अणु 0x64, 0xff पूर्ण,
	अणु 0x66, 0x00 पूर्ण,
	अणु 0x13, 0xf0 पूर्ण,		/* com8 */
	अणु 0x0d, 0x41 पूर्ण,
	अणु 0x0f, 0xc5 पूर्ण,
	अणु 0x14, 0x11 पूर्ण,

	अणु 0x22, 0x7f पूर्ण,
	अणु 0x23, 0x03 पूर्ण,
	अणु 0x24, 0x40 पूर्ण,
	अणु 0x25, 0x30 पूर्ण,
	अणु 0x26, 0xa1 पूर्ण,
	अणु 0x2a, 0x00 पूर्ण,
	अणु 0x2b, 0x00 पूर्ण,
	अणु 0x6b, 0xaa पूर्ण,
	अणु 0x13, 0xff पूर्ण,		/* AWB */

	अणु 0x90, 0x05 पूर्ण,
	अणु 0x91, 0x01 पूर्ण,
	अणु 0x92, 0x03 पूर्ण,
	अणु 0x93, 0x00 पूर्ण,
	अणु 0x94, 0x60 पूर्ण,
	अणु 0x95, 0x3c पूर्ण,
	अणु 0x96, 0x24 पूर्ण,
	अणु 0x97, 0x1e पूर्ण,
	अणु 0x98, 0x62 पूर्ण,
	अणु 0x99, 0x80 पूर्ण,
	अणु 0x9a, 0x1e पूर्ण,
	अणु 0x9b, 0x08 पूर्ण,
	अणु 0x9c, 0x20 पूर्ण,
	अणु 0x9e, 0x81 पूर्ण,

	अणु 0xa6, 0x07 पूर्ण,
	अणु 0x7e, 0x0c पूर्ण,
	अणु 0x7f, 0x16 पूर्ण,
	अणु 0x80, 0x2a पूर्ण,
	अणु 0x81, 0x4e पूर्ण,
	अणु 0x82, 0x61 पूर्ण,
	अणु 0x83, 0x6f पूर्ण,
	अणु 0x84, 0x7b पूर्ण,
	अणु 0x85, 0x86 पूर्ण,
	अणु 0x86, 0x8e पूर्ण,
	अणु 0x87, 0x97 पूर्ण,
	अणु 0x88, 0xa4 पूर्ण,
	अणु 0x89, 0xaf पूर्ण,
	अणु 0x8a, 0xc5 पूर्ण,
	अणु 0x8b, 0xd7 पूर्ण,
	अणु 0x8c, 0xe8 पूर्ण,
	अणु 0x8d, 0x20 पूर्ण,

	अणु 0x2b, 0x00 पूर्ण,
	अणु 0x22, 0x7f पूर्ण,
	अणु 0x23, 0x03 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x64, 0xff पूर्ण,
	अणु 0x0d, 0x41 पूर्ण,

	अणु 0x14, 0x41 पूर्ण,
	अणु 0x0e, 0xcd पूर्ण,
	अणु 0xac, 0xbf पूर्ण,
	अणु 0x8e, 0x00 पूर्ण,		/* De-noise threshold */
पूर्ण;
अटल स्थिर u8 bridge_start_vga_yuyv_772x[][2] = अणु
	अणु0x88, 0x00पूर्ण,
	अणु0x1c, 0x00पूर्ण,
	अणु0x1d, 0x40पूर्ण,
	अणु0x1d, 0x02पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0x02पूर्ण,
	अणु0x1d, 0x58पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x8d, 0x1cपूर्ण,
	अणु0x8e, 0x80पूर्ण,
	अणु0xc0, 0x50पूर्ण,
	अणु0xc1, 0x3cपूर्ण,
	अणु0xc2, 0x0cपूर्ण,
	अणु0xc3, 0x69पूर्ण,
पूर्ण;
अटल स्थिर u8 sensor_start_vga_yuyv_772x[][2] = अणु
	अणु0x12, 0x00पूर्ण,
	अणु0x17, 0x26पूर्ण,
	अणु0x18, 0xa0पूर्ण,
	अणु0x19, 0x07पूर्ण,
	अणु0x1a, 0xf0पूर्ण,
	अणु0x29, 0xa0पूर्ण,
	अणु0x2c, 0xf0पूर्ण,
	अणु0x65, 0x20पूर्ण,
	अणु0x67, 0x00पूर्ण,
पूर्ण;
अटल स्थिर u8 bridge_start_qvga_yuyv_772x[][2] = अणु
	अणु0x88, 0x00पूर्ण,
	अणु0x1c, 0x00पूर्ण,
	अणु0x1d, 0x40पूर्ण,
	अणु0x1d, 0x02पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0x01पूर्ण,
	अणु0x1d, 0x4bपूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x8d, 0x1cपूर्ण,
	अणु0x8e, 0x80पूर्ण,
	अणु0xc0, 0x28पूर्ण,
	अणु0xc1, 0x1eपूर्ण,
	अणु0xc2, 0x0cपूर्ण,
	अणु0xc3, 0x69पूर्ण,
पूर्ण;
अटल स्थिर u8 sensor_start_qvga_yuyv_772x[][2] = अणु
	अणु0x12, 0x40पूर्ण,
	अणु0x17, 0x3fपूर्ण,
	अणु0x18, 0x50पूर्ण,
	अणु0x19, 0x03पूर्ण,
	अणु0x1a, 0x78पूर्ण,
	अणु0x29, 0x50पूर्ण,
	अणु0x2c, 0x78पूर्ण,
	अणु0x65, 0x2fपूर्ण,
	अणु0x67, 0x00पूर्ण,
पूर्ण;
अटल स्थिर u8 bridge_start_vga_gbrg_772x[][2] = अणु
	अणु0x88, 0x08पूर्ण,
	अणु0x1c, 0x00पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0x02पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0x01पूर्ण,
	अणु0x1d, 0x2cपूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x8d, 0x00पूर्ण,
	अणु0x8e, 0x00पूर्ण,
	अणु0xc0, 0x50पूर्ण,
	अणु0xc1, 0x3cपूर्ण,
	अणु0xc2, 0x01पूर्ण,
	अणु0xc3, 0x01पूर्ण,
पूर्ण;
अटल स्थिर u8 sensor_start_vga_gbrg_772x[][2] = अणु
	अणु0x12, 0x01पूर्ण,
	अणु0x17, 0x26पूर्ण,
	अणु0x18, 0xa0पूर्ण,
	अणु0x19, 0x07पूर्ण,
	अणु0x1a, 0xf0पूर्ण,
	अणु0x29, 0xa0पूर्ण,
	अणु0x2c, 0xf0पूर्ण,
	अणु0x65, 0x20पूर्ण,
	अणु0x67, 0x02पूर्ण,
पूर्ण;
अटल स्थिर u8 bridge_start_qvga_gbrg_772x[][2] = अणु
	अणु0x88, 0x08पूर्ण,
	अणु0x1c, 0x00पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0x02पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0x4bपूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x8d, 0x00पूर्ण,
	अणु0x8e, 0x00पूर्ण,
	अणु0xc0, 0x28पूर्ण,
	अणु0xc1, 0x1eपूर्ण,
	अणु0xc2, 0x01पूर्ण,
	अणु0xc3, 0x01पूर्ण,
पूर्ण;
अटल स्थिर u8 sensor_start_qvga_gbrg_772x[][2] = अणु
	अणु0x12, 0x41पूर्ण,
	अणु0x17, 0x3fपूर्ण,
	अणु0x18, 0x50पूर्ण,
	अणु0x19, 0x03पूर्ण,
	अणु0x1a, 0x78पूर्ण,
	अणु0x29, 0x50पूर्ण,
	अणु0x2c, 0x78पूर्ण,
	अणु0x65, 0x2fपूर्ण,
	अणु0x67, 0x02पूर्ण,
पूर्ण;

अटल व्योम ov534_reg_ग_लिखो(काष्ठा gspca_dev *gspca_dev, u16 reg, u8 val)
अणु
	काष्ठा usb_device *udev = gspca_dev->dev;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;

	gspca_dbg(gspca_dev, D_USBO, "SET 01 0000 %04x %02x\n", reg, val);
	gspca_dev->usb_buf[0] = val;
	ret = usb_control_msg(udev,
			      usb_sndctrlpipe(udev, 0),
			      0x01,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0x00, reg, gspca_dev->usb_buf, 1, CTRL_TIMEOUT);
	अगर (ret < 0) अणु
		pr_err("write failed %d\n", ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

अटल u8 ov534_reg_पढ़ो(काष्ठा gspca_dev *gspca_dev, u16 reg)
अणु
	काष्ठा usb_device *udev = gspca_dev->dev;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस 0;
	ret = usb_control_msg(udev,
			      usb_rcvctrlpipe(udev, 0),
			      0x01,
			      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0x00, reg, gspca_dev->usb_buf, 1, CTRL_TIMEOUT);
	gspca_dbg(gspca_dev, D_USBI, "GET 01 0000 %04x %02x\n",
		  reg, gspca_dev->usb_buf[0]);
	अगर (ret < 0) अणु
		pr_err("read failed %d\n", ret);
		gspca_dev->usb_err = ret;
		/*
		 * Make sure the result is zeroed to aव्योम uninitialized
		 * values.
		 */
		gspca_dev->usb_buf[0] = 0;
	पूर्ण
	वापस gspca_dev->usb_buf[0];
पूर्ण

/* Two bits control LED: 0x21 bit 7 and 0x23 bit 7.
 * (direction and output)? */
अटल व्योम ov534_set_led(काष्ठा gspca_dev *gspca_dev, पूर्णांक status)
अणु
	u8 data;

	gspca_dbg(gspca_dev, D_CONF, "led status: %d\n", status);

	data = ov534_reg_पढ़ो(gspca_dev, 0x21);
	data |= 0x80;
	ov534_reg_ग_लिखो(gspca_dev, 0x21, data);

	data = ov534_reg_पढ़ो(gspca_dev, 0x23);
	अगर (status)
		data |= 0x80;
	अन्यथा
		data &= ~0x80;

	ov534_reg_ग_लिखो(gspca_dev, 0x23, data);

	अगर (!status) अणु
		data = ov534_reg_पढ़ो(gspca_dev, 0x21);
		data &= ~0x80;
		ov534_reg_ग_लिखो(gspca_dev, 0x21, data);
	पूर्ण
पूर्ण

अटल पूर्णांक sccb_check_status(काष्ठा gspca_dev *gspca_dev)
अणु
	u8 data;
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		usleep_range(10000, 20000);
		data = ov534_reg_पढ़ो(gspca_dev, OV534_REG_STATUS);

		चयन (data) अणु
		हाल 0x00:
			वापस 1;
		हाल 0x04:
			वापस 0;
		हाल 0x03:
			अवरोध;
		शेष:
			gspca_err(gspca_dev, "sccb status 0x%02x, attempt %d/5\n",
				  data, i + 1);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sccb_reg_ग_लिखो(काष्ठा gspca_dev *gspca_dev, u8 reg, u8 val)
अणु
	gspca_dbg(gspca_dev, D_USBO, "sccb write: %02x %02x\n", reg, val);
	ov534_reg_ग_लिखो(gspca_dev, OV534_REG_SUBADDR, reg);
	ov534_reg_ग_लिखो(gspca_dev, OV534_REG_WRITE, val);
	ov534_reg_ग_लिखो(gspca_dev, OV534_REG_OPERATION, OV534_OP_WRITE_3);

	अगर (!sccb_check_status(gspca_dev)) अणु
		pr_err("sccb_reg_write failed\n");
		gspca_dev->usb_err = -EIO;
	पूर्ण
पूर्ण

अटल u8 sccb_reg_पढ़ो(काष्ठा gspca_dev *gspca_dev, u16 reg)
अणु
	ov534_reg_ग_लिखो(gspca_dev, OV534_REG_SUBADDR, reg);
	ov534_reg_ग_लिखो(gspca_dev, OV534_REG_OPERATION, OV534_OP_WRITE_2);
	अगर (!sccb_check_status(gspca_dev))
		pr_err("sccb_reg_read failed 1\n");

	ov534_reg_ग_लिखो(gspca_dev, OV534_REG_OPERATION, OV534_OP_READ_2);
	अगर (!sccb_check_status(gspca_dev))
		pr_err("sccb_reg_read failed 2\n");

	वापस ov534_reg_पढ़ो(gspca_dev, OV534_REG_READ);
पूर्ण

/* output a bridge sequence (reg - val) */
अटल व्योम reg_w_array(काष्ठा gspca_dev *gspca_dev,
			स्थिर u8 (*data)[2], पूर्णांक len)
अणु
	जबतक (--len >= 0) अणु
		ov534_reg_ग_लिखो(gspca_dev, (*data)[0], (*data)[1]);
		data++;
	पूर्ण
पूर्ण

/* output a sensor sequence (reg - val) */
अटल व्योम sccb_w_array(काष्ठा gspca_dev *gspca_dev,
			स्थिर u8 (*data)[2], पूर्णांक len)
अणु
	जबतक (--len >= 0) अणु
		अगर ((*data)[0] != 0xff) अणु
			sccb_reg_ग_लिखो(gspca_dev, (*data)[0], (*data)[1]);
		पूर्ण अन्यथा अणु
			sccb_reg_पढ़ो(gspca_dev, (*data)[1]);
			sccb_reg_ग_लिखो(gspca_dev, 0xff, 0x00);
		पूर्ण
		data++;
	पूर्ण
पूर्ण

/* ov772x specअगरic controls */
अटल व्योम set_frame_rate(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक i;
	काष्ठा rate_s अणु
		u8 fps;
		u8 r11;
		u8 r0d;
		u8 re5;
	पूर्ण;
	स्थिर काष्ठा rate_s *r;
	अटल स्थिर काष्ठा rate_s rate_0[] = अणु	/* 640x480 */
		अणु60, 0x01, 0xc1, 0x04पूर्ण,
		अणु50, 0x01, 0x41, 0x02पूर्ण,
		अणु40, 0x02, 0xc1, 0x04पूर्ण,
		अणु30, 0x04, 0x81, 0x02पूर्ण,
		अणु15, 0x03, 0x41, 0x04पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा rate_s rate_1[] = अणु	/* 320x240 */
/*		अणु205, 0x01, 0xc1, 0x02पूर्ण,  * 205 FPS: video is partly corrupt */
		अणु187, 0x01, 0x81, 0x02पूर्ण, /* 187 FPS or below: video is valid */
		अणु150, 0x01, 0xc1, 0x04पूर्ण,
		अणु137, 0x02, 0xc1, 0x02पूर्ण,
		अणु125, 0x02, 0x81, 0x02पूर्ण,
		अणु100, 0x02, 0xc1, 0x04पूर्ण,
		अणु75, 0x03, 0xc1, 0x04पूर्ण,
		अणु60, 0x04, 0xc1, 0x04पूर्ण,
		अणु50, 0x02, 0x41, 0x04पूर्ण,
		अणु37, 0x03, 0x41, 0x04पूर्ण,
		अणु30, 0x04, 0x41, 0x04पूर्ण,
	पूर्ण;

	अगर (sd->sensor != SENSOR_OV772x)
		वापस;
	अगर (gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv == 0) अणु
		r = rate_0;
		i = ARRAY_SIZE(rate_0);
	पूर्ण अन्यथा अणु
		r = rate_1;
		i = ARRAY_SIZE(rate_1);
	पूर्ण
	जबतक (--i > 0) अणु
		अगर (sd->frame_rate >= r->fps)
			अवरोध;
		r++;
	पूर्ण

	sccb_reg_ग_लिखो(gspca_dev, 0x11, r->r11);
	sccb_reg_ग_लिखो(gspca_dev, 0x0d, r->r0d);
	ov534_reg_ग_लिखो(gspca_dev, 0xe5, r->re5);

	gspca_dbg(gspca_dev, D_PROBE, "frame_rate: %d\n", r->fps);
पूर्ण

अटल व्योम sethue(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_OV767x) अणु
		/* TBD */
	पूर्ण अन्यथा अणु
		s16 huesin;
		s16 huecos;

		/* According to the datasheet the रेजिस्टरs expect HUESIN and
		 * HUECOS to be the result of the trigonometric functions,
		 * scaled by 0x80.
		 *
		 * The 0x7fff here represents the maximum असलolute value
		 * वापसed byt fixp_sin and fixp_cos, so the scaling will
		 * consider the result like in the पूर्णांकerval [-1.0, 1.0].
		 */
		huesin = fixp_sin16(val) * 0x80 / 0x7fff;
		huecos = fixp_cos16(val) * 0x80 / 0x7fff;

		अगर (huesin < 0) अणु
			sccb_reg_ग_लिखो(gspca_dev, 0xab,
				sccb_reg_पढ़ो(gspca_dev, 0xab) | 0x2);
			huesin = -huesin;
		पूर्ण अन्यथा अणु
			sccb_reg_ग_लिखो(gspca_dev, 0xab,
				sccb_reg_पढ़ो(gspca_dev, 0xab) & ~0x2);

		पूर्ण
		sccb_reg_ग_लिखो(gspca_dev, 0xa9, (u8)huecos);
		sccb_reg_ग_लिखो(gspca_dev, 0xaa, (u8)huesin);
	पूर्ण
पूर्ण

अटल व्योम setsaturation(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_OV767x) अणु
		पूर्णांक i;
		अटल u8 color_tb[][6] = अणु
			अणु0x42, 0x42, 0x00, 0x11, 0x30, 0x41पूर्ण,
			अणु0x52, 0x52, 0x00, 0x16, 0x3c, 0x52पूर्ण,
			अणु0x66, 0x66, 0x00, 0x1b, 0x4b, 0x66पूर्ण,
			अणु0x80, 0x80, 0x00, 0x22, 0x5e, 0x80पूर्ण,
			अणु0x9a, 0x9a, 0x00, 0x29, 0x71, 0x9aपूर्ण,
			अणु0xb8, 0xb8, 0x00, 0x31, 0x87, 0xb8पूर्ण,
			अणु0xdd, 0xdd, 0x00, 0x3b, 0xa2, 0xddपूर्ण,
		पूर्ण;

		क्रम (i = 0; i < ARRAY_SIZE(color_tb[0]); i++)
			sccb_reg_ग_लिखो(gspca_dev, 0x4f + i, color_tb[val][i]);
	पूर्ण अन्यथा अणु
		sccb_reg_ग_लिखो(gspca_dev, 0xa7, val); /* U saturation */
		sccb_reg_ग_लिखो(gspca_dev, 0xa8, val); /* V saturation */
	पूर्ण
पूर्ण

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_OV767x) अणु
		अगर (val < 0)
			val = 0x80 - val;
		sccb_reg_ग_लिखो(gspca_dev, 0x55, val);	/* bright */
	पूर्ण अन्यथा अणु
		sccb_reg_ग_लिखो(gspca_dev, 0x9b, val);
	पूर्ण
पूर्ण

अटल व्योम setcontrast(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_OV767x)
		sccb_reg_ग_लिखो(gspca_dev, 0x56, val);	/* contras */
	अन्यथा
		sccb_reg_ग_लिखो(gspca_dev, 0x9c, val);
पूर्ण

अटल व्योम setgain(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	चयन (val & 0x30) अणु
	हाल 0x00:
		val &= 0x0f;
		अवरोध;
	हाल 0x10:
		val &= 0x0f;
		val |= 0x30;
		अवरोध;
	हाल 0x20:
		val &= 0x0f;
		val |= 0x70;
		अवरोध;
	शेष:
/*	हाल 0x30: */
		val &= 0x0f;
		val |= 0xf0;
		अवरोध;
	पूर्ण
	sccb_reg_ग_लिखो(gspca_dev, 0x00, val);
पूर्ण

अटल s32 getgain(काष्ठा gspca_dev *gspca_dev)
अणु
	वापस sccb_reg_पढ़ो(gspca_dev, 0x00);
पूर्ण

अटल व्योम setexposure(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_OV767x) अणु

		/* set only aec[9:2] */
		sccb_reg_ग_लिखो(gspca_dev, 0x10, val);	/* aech */
	पूर्ण अन्यथा अणु

		/* 'val' is one byte and represents half of the exposure value
		 * we are going to set पूर्णांकo रेजिस्टरs, a two bytes value:
		 *
		 *    MSB: ((u16) val << 1) >> 8   == val >> 7
		 *    LSB: ((u16) val << 1) & 0xff == val << 1
		 */
		sccb_reg_ग_लिखो(gspca_dev, 0x08, val >> 7);
		sccb_reg_ग_लिखो(gspca_dev, 0x10, val << 1);
	पूर्ण
पूर्ण

अटल s32 getexposure(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_OV767x) अणु
		/* get only aec[9:2] */
		वापस sccb_reg_पढ़ो(gspca_dev, 0x10);	/* aech */
	पूर्ण अन्यथा अणु
		u8 hi = sccb_reg_पढ़ो(gspca_dev, 0x08);
		u8 lo = sccb_reg_पढ़ो(gspca_dev, 0x10);
		वापस (hi << 8 | lo) >> 1;
	पूर्ण
पूर्ण

अटल व्योम setagc(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	अगर (val) अणु
		sccb_reg_ग_लिखो(gspca_dev, 0x13,
				sccb_reg_पढ़ो(gspca_dev, 0x13) | 0x04);
		sccb_reg_ग_लिखो(gspca_dev, 0x64,
				sccb_reg_पढ़ो(gspca_dev, 0x64) | 0x03);
	पूर्ण अन्यथा अणु
		sccb_reg_ग_लिखो(gspca_dev, 0x13,
				sccb_reg_पढ़ो(gspca_dev, 0x13) & ~0x04);
		sccb_reg_ग_लिखो(gspca_dev, 0x64,
				sccb_reg_पढ़ो(gspca_dev, 0x64) & ~0x03);
	पूर्ण
पूर्ण

अटल व्योम setawb(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (val) अणु
		sccb_reg_ग_लिखो(gspca_dev, 0x13,
				sccb_reg_पढ़ो(gspca_dev, 0x13) | 0x02);
		अगर (sd->sensor == SENSOR_OV772x)
			sccb_reg_ग_लिखो(gspca_dev, 0x63,
				sccb_reg_पढ़ो(gspca_dev, 0x63) | 0xc0);
	पूर्ण अन्यथा अणु
		sccb_reg_ग_लिखो(gspca_dev, 0x13,
				sccb_reg_पढ़ो(gspca_dev, 0x13) & ~0x02);
		अगर (sd->sensor == SENSOR_OV772x)
			sccb_reg_ग_लिखो(gspca_dev, 0x63,
				sccb_reg_पढ़ो(gspca_dev, 0x63) & ~0xc0);
	पूर्ण
पूर्ण

अटल व्योम setaec(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 data;

	data = sd->sensor == SENSOR_OV767x ?
			0x05 :		/* agc + aec */
			0x01;		/* agc */
	चयन (val) अणु
	हाल V4L2_EXPOSURE_AUTO:
		sccb_reg_ग_लिखो(gspca_dev, 0x13,
				sccb_reg_पढ़ो(gspca_dev, 0x13) | data);
		अवरोध;
	हाल V4L2_EXPOSURE_MANUAL:
		sccb_reg_ग_लिखो(gspca_dev, 0x13,
				sccb_reg_पढ़ो(gspca_dev, 0x13) & ~data);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम setsharpness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	sccb_reg_ग_लिखो(gspca_dev, 0x91, val);	/* Auto de-noise threshold */
	sccb_reg_ग_लिखो(gspca_dev, 0x8e, val);	/* De-noise threshold */
पूर्ण

अटल व्योम sethvflip(काष्ठा gspca_dev *gspca_dev, s32 hflip, s32 vflip)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 val;

	अगर (sd->sensor == SENSOR_OV767x) अणु
		val = sccb_reg_पढ़ो(gspca_dev, 0x1e);	/* mvfp */
		val &= ~0x30;
		अगर (hflip)
			val |= 0x20;
		अगर (vflip)
			val |= 0x10;
		sccb_reg_ग_लिखो(gspca_dev, 0x1e, val);
	पूर्ण अन्यथा अणु
		val = sccb_reg_पढ़ो(gspca_dev, 0x0c);
		val &= ~0xc0;
		अगर (hflip == 0)
			val |= 0x40;
		अगर (vflip == 0)
			val |= 0x80;
		sccb_reg_ग_लिखो(gspca_dev, 0x0c, val);
	पूर्ण
पूर्ण

अटल व्योम setlightfreq(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	val = val ? 0x9e : 0x00;
	अगर (sd->sensor == SENSOR_OV767x) अणु
		sccb_reg_ग_लिखो(gspca_dev, 0x2a, 0x00);
		अगर (val)
			val = 0x9d;	/* insert dummy to 25fps क्रम 50Hz */
	पूर्ण
	sccb_reg_ग_लिखो(gspca_dev, 0x2b, val);
पूर्ण


/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;

	cam = &gspca_dev->cam;

	cam->cam_mode = ov772x_mode;
	cam->nmodes = ARRAY_SIZE(ov772x_mode);

	sd->frame_rate = DEFAULT_FRAME_RATE;

	वापस 0;
पूर्ण

अटल पूर्णांक ov534_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा sd *sd = container_of(ctrl->handler, काष्ठा sd, ctrl_handler);
	काष्ठा gspca_dev *gspca_dev = &sd->gspca_dev;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		gspca_dev->usb_err = 0;
		अगर (ctrl->val && sd->gain && gspca_dev->streaming)
			sd->gain->val = getgain(gspca_dev);
		वापस gspca_dev->usb_err;

	हाल V4L2_CID_EXPOSURE_AUTO:
		gspca_dev->usb_err = 0;
		अगर (ctrl->val == V4L2_EXPOSURE_AUTO && sd->exposure &&
		    gspca_dev->streaming)
			sd->exposure->val = getexposure(gspca_dev);
		वापस gspca_dev->usb_err;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ov534_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा sd *sd = container_of(ctrl->handler, काष्ठा sd, ctrl_handler);
	काष्ठा gspca_dev *gspca_dev = &sd->gspca_dev;

	gspca_dev->usb_err = 0;
	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_HUE:
		sethue(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		setsaturation(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_BRIGHTNESS:
		setbrightness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		setcontrast(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
	/* हाल V4L2_CID_GAIN: */
		setagc(gspca_dev, ctrl->val);
		अगर (!gspca_dev->usb_err && !ctrl->val && sd->gain)
			setgain(gspca_dev, sd->gain->val);
		अवरोध;
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		setawb(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE_AUTO:
	/* हाल V4L2_CID_EXPOSURE: */
		setaec(gspca_dev, ctrl->val);
		अगर (!gspca_dev->usb_err && ctrl->val == V4L2_EXPOSURE_MANUAL &&
		    sd->exposure)
			setexposure(gspca_dev, sd->exposure->val);
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		setsharpness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		sethvflip(gspca_dev, ctrl->val, sd->vflip->val);
		अवरोध;
	हाल V4L2_CID_VFLIP:
		sethvflip(gspca_dev, sd->hflip->val, ctrl->val);
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		setlightfreq(gspca_dev, ctrl->val);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov534_ctrl_ops = अणु
	.g_अस्थिर_ctrl = ov534_g_अस्थिर_ctrl,
	.s_ctrl = ov534_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &sd->ctrl_handler;
	/* parameters with dअगरferent values between the supported sensors */
	पूर्णांक saturation_min;
	पूर्णांक saturation_max;
	पूर्णांक saturation_def;
	पूर्णांक brightness_min;
	पूर्णांक brightness_max;
	पूर्णांक brightness_def;
	पूर्णांक contrast_max;
	पूर्णांक contrast_def;
	पूर्णांक exposure_min;
	पूर्णांक exposure_max;
	पूर्णांक exposure_def;
	पूर्णांक hflip_def;

	अगर (sd->sensor == SENSOR_OV767x) अणु
		saturation_min = 0;
		saturation_max = 6;
		saturation_def = 3;
		brightness_min = -127;
		brightness_max = 127;
		brightness_def = 0;
		contrast_max = 0x80;
		contrast_def = 0x40;
		exposure_min = 0x08;
		exposure_max = 0x60;
		exposure_def = 0x13;
		hflip_def = 1;
	पूर्ण अन्यथा अणु
		saturation_min = 0;
		saturation_max = 255;
		saturation_def = 64;
		brightness_min = 0;
		brightness_max = 255;
		brightness_def = 0;
		contrast_max = 255;
		contrast_def = 32;
		exposure_min = 0;
		exposure_max = 255;
		exposure_def = 120;
		hflip_def = 0;
	पूर्ण

	gspca_dev->vdev.ctrl_handler = hdl;

	v4l2_ctrl_handler_init(hdl, 13);

	अगर (sd->sensor == SENSOR_OV772x)
		sd->hue = v4l2_ctrl_new_std(hdl, &ov534_ctrl_ops,
				V4L2_CID_HUE, -90, 90, 1, 0);

	sd->saturation = v4l2_ctrl_new_std(hdl, &ov534_ctrl_ops,
			V4L2_CID_SATURATION, saturation_min, saturation_max, 1,
			saturation_def);
	sd->brightness = v4l2_ctrl_new_std(hdl, &ov534_ctrl_ops,
			V4L2_CID_BRIGHTNESS, brightness_min, brightness_max, 1,
			brightness_def);
	sd->contrast = v4l2_ctrl_new_std(hdl, &ov534_ctrl_ops,
			V4L2_CID_CONTRAST, 0, contrast_max, 1, contrast_def);

	अगर (sd->sensor == SENSOR_OV772x) अणु
		sd->स्वतःgain = v4l2_ctrl_new_std(hdl, &ov534_ctrl_ops,
				V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
		sd->gain = v4l2_ctrl_new_std(hdl, &ov534_ctrl_ops,
				V4L2_CID_GAIN, 0, 63, 1, 20);
	पूर्ण

	sd->स्वतःexposure = v4l2_ctrl_new_std_menu(hdl, &ov534_ctrl_ops,
			V4L2_CID_EXPOSURE_AUTO,
			V4L2_EXPOSURE_MANUAL, 0,
			V4L2_EXPOSURE_AUTO);
	sd->exposure = v4l2_ctrl_new_std(hdl, &ov534_ctrl_ops,
			V4L2_CID_EXPOSURE, exposure_min, exposure_max, 1,
			exposure_def);

	sd->स्वतःwhitebalance = v4l2_ctrl_new_std(hdl, &ov534_ctrl_ops,
			V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);

	अगर (sd->sensor == SENSOR_OV772x)
		sd->sharpness = v4l2_ctrl_new_std(hdl, &ov534_ctrl_ops,
				V4L2_CID_SHARPNESS, 0, 63, 1, 0);

	sd->hflip = v4l2_ctrl_new_std(hdl, &ov534_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, hflip_def);
	sd->vflip = v4l2_ctrl_new_std(hdl, &ov534_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	sd->plfreq = v4l2_ctrl_new_std_menu(hdl, &ov534_ctrl_ops,
			V4L2_CID_POWER_LINE_FREQUENCY,
			V4L2_CID_POWER_LINE_FREQUENCY_50HZ, 0,
			V4L2_CID_POWER_LINE_FREQUENCY_DISABLED);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण

	अगर (sd->sensor == SENSOR_OV772x)
		v4l2_ctrl_स्वतः_cluster(2, &sd->स्वतःgain, 0, true);

	v4l2_ctrl_स्वतः_cluster(2, &sd->स्वतःexposure, V4L2_EXPOSURE_MANUAL,
			       true);

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u16 sensor_id;
	अटल स्थिर काष्ठा reg_array bridge_init[NSENSORS] = अणु
	[SENSOR_OV767x] = अणुbridge_init_767x, ARRAY_SIZE(bridge_init_767x)पूर्ण,
	[SENSOR_OV772x] = अणुbridge_init_772x, ARRAY_SIZE(bridge_init_772x)पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा reg_array sensor_init[NSENSORS] = अणु
	[SENSOR_OV767x] = अणुsensor_init_767x, ARRAY_SIZE(sensor_init_767x)पूर्ण,
	[SENSOR_OV772x] = अणुsensor_init_772x, ARRAY_SIZE(sensor_init_772x)पूर्ण,
	पूर्ण;

	/* reset bridge */
	ov534_reg_ग_लिखो(gspca_dev, 0xe7, 0x3a);
	ov534_reg_ग_लिखो(gspca_dev, 0xe0, 0x08);
	msleep(100);

	/* initialize the sensor address */
	ov534_reg_ग_लिखो(gspca_dev, OV534_REG_ADDRESS, 0x42);

	/* reset sensor */
	sccb_reg_ग_लिखो(gspca_dev, 0x12, 0x80);
	usleep_range(10000, 20000);

	/* probe the sensor */
	sccb_reg_पढ़ो(gspca_dev, 0x0a);
	sensor_id = sccb_reg_पढ़ो(gspca_dev, 0x0a) << 8;
	sccb_reg_पढ़ो(gspca_dev, 0x0b);
	sensor_id |= sccb_reg_पढ़ो(gspca_dev, 0x0b);
	gspca_dbg(gspca_dev, D_PROBE, "Sensor ID: %04x\n", sensor_id);

	अगर ((sensor_id & 0xfff0) == 0x7670) अणु
		sd->sensor = SENSOR_OV767x;
		gspca_dev->cam.cam_mode = ov767x_mode;
		gspca_dev->cam.nmodes = ARRAY_SIZE(ov767x_mode);
	पूर्ण अन्यथा अणु
		sd->sensor = SENSOR_OV772x;
		gspca_dev->cam.bulk = 1;
		gspca_dev->cam.bulk_size = 16384;
		gspca_dev->cam.bulk_nurbs = 2;
		gspca_dev->cam.mode_framerates = ov772x_framerates;
	पूर्ण

	/* initialize */
	reg_w_array(gspca_dev, bridge_init[sd->sensor].val,
			bridge_init[sd->sensor].len);
	ov534_set_led(gspca_dev, 1);
	sccb_w_array(gspca_dev, sensor_init[sd->sensor].val,
			sensor_init[sd->sensor].len);

	sd_stopN(gspca_dev);
/*	set_frame_rate(gspca_dev);	*/

	वापस gspca_dev->usb_err;
पूर्ण

अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक mode;
	अटल स्थिर काष्ठा reg_array bridge_start[NSENSORS][4] = अणु
	[SENSOR_OV767x] = अणुअणुbridge_start_qvga_767x,
					ARRAY_SIZE(bridge_start_qvga_767x)पूर्ण,
			अणुbridge_start_vga_767x,
					ARRAY_SIZE(bridge_start_vga_767x)पूर्णपूर्ण,
	[SENSOR_OV772x] = अणुअणुbridge_start_qvga_yuyv_772x,
				ARRAY_SIZE(bridge_start_qvga_yuyv_772x)पूर्ण,
			अणुbridge_start_vga_yuyv_772x,
				ARRAY_SIZE(bridge_start_vga_yuyv_772x)पूर्ण,
			अणुbridge_start_qvga_gbrg_772x,
				ARRAY_SIZE(bridge_start_qvga_gbrg_772x)पूर्ण,
			अणुbridge_start_vga_gbrg_772x,
				ARRAY_SIZE(bridge_start_vga_gbrg_772x)पूर्ण पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा reg_array sensor_start[NSENSORS][4] = अणु
	[SENSOR_OV767x] = अणुअणुsensor_start_qvga_767x,
					ARRAY_SIZE(sensor_start_qvga_767x)पूर्ण,
			अणुsensor_start_vga_767x,
					ARRAY_SIZE(sensor_start_vga_767x)पूर्णपूर्ण,
	[SENSOR_OV772x] = अणुअणुsensor_start_qvga_yuyv_772x,
				ARRAY_SIZE(sensor_start_qvga_yuyv_772x)पूर्ण,
			अणुsensor_start_vga_yuyv_772x,
				ARRAY_SIZE(sensor_start_vga_yuyv_772x)पूर्ण,
			अणुsensor_start_qvga_gbrg_772x,
				ARRAY_SIZE(sensor_start_qvga_gbrg_772x)पूर्ण,
			अणुsensor_start_vga_gbrg_772x,
				ARRAY_SIZE(sensor_start_vga_gbrg_772x)पूर्ण पूर्ण,
	पूर्ण;

	/* (from ms-win trace) */
	अगर (sd->sensor == SENSOR_OV767x)
		sccb_reg_ग_लिखो(gspca_dev, 0x1e, 0x04);
					/* black sun enable ? */

	mode = gspca_dev->curr_mode;	/* 0: 320x240, 1: 640x480 */
	reg_w_array(gspca_dev, bridge_start[sd->sensor][mode].val,
				bridge_start[sd->sensor][mode].len);
	sccb_w_array(gspca_dev, sensor_start[sd->sensor][mode].val,
				sensor_start[sd->sensor][mode].len);

	set_frame_rate(gspca_dev);

	अगर (sd->hue)
		sethue(gspca_dev, v4l2_ctrl_g_ctrl(sd->hue));
	setsaturation(gspca_dev, v4l2_ctrl_g_ctrl(sd->saturation));
	अगर (sd->स्वतःgain)
		setagc(gspca_dev, v4l2_ctrl_g_ctrl(sd->स्वतःgain));
	setawb(gspca_dev, v4l2_ctrl_g_ctrl(sd->स्वतःwhitebalance));
	setaec(gspca_dev, v4l2_ctrl_g_ctrl(sd->स्वतःexposure));
	अगर (sd->gain)
		setgain(gspca_dev, v4l2_ctrl_g_ctrl(sd->gain));
	setexposure(gspca_dev, v4l2_ctrl_g_ctrl(sd->exposure));
	setbrightness(gspca_dev, v4l2_ctrl_g_ctrl(sd->brightness));
	setcontrast(gspca_dev, v4l2_ctrl_g_ctrl(sd->contrast));
	अगर (sd->sharpness)
		setsharpness(gspca_dev, v4l2_ctrl_g_ctrl(sd->sharpness));
	sethvflip(gspca_dev, v4l2_ctrl_g_ctrl(sd->hflip),
		  v4l2_ctrl_g_ctrl(sd->vflip));
	setlightfreq(gspca_dev, v4l2_ctrl_g_ctrl(sd->plfreq));

	ov534_set_led(gspca_dev, 1);
	ov534_reg_ग_लिखो(gspca_dev, 0xe0, 0x00);
	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	ov534_reg_ग_लिखो(gspca_dev, 0xe0, 0x09);
	ov534_set_led(gspca_dev, 0);
पूर्ण

/* Values क्रम bmHeaderInfo (Video and Still Image Payload Headers, 2.4.3.3) */
#घोषणा UVC_STREAM_EOH	(1 << 7)
#घोषणा UVC_STREAM_ERR	(1 << 6)
#घोषणा UVC_STREAM_STI	(1 << 5)
#घोषणा UVC_STREAM_RES	(1 << 4)
#घोषणा UVC_STREAM_SCR	(1 << 3)
#घोषणा UVC_STREAM_PTS	(1 << 2)
#घोषणा UVC_STREAM_खातापूर्ण	(1 << 1)
#घोषणा UVC_STREAM_FID	(1 << 0)

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data, पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	__u32 this_pts;
	u16 this_fid;
	पूर्णांक reमुख्यing_len = len;
	पूर्णांक payload_len;

	payload_len = gspca_dev->cam.bulk ? 2048 : 2040;
	करो अणु
		len = min(reमुख्यing_len, payload_len);

		/* Payloads are prefixed with a UVC-style header.  We
		   consider a frame to start when the FID toggles, or the PTS
		   changes.  A frame ends when खातापूर्ण is set, and we've received
		   the correct number of bytes. */

		/* Verअगरy UVC header.  Header length is always 12 */
		अगर (data[0] != 12 || len < 12) अणु
			gspca_dbg(gspca_dev, D_PACK, "bad header\n");
			जाओ discard;
		पूर्ण

		/* Check errors */
		अगर (data[1] & UVC_STREAM_ERR) अणु
			gspca_dbg(gspca_dev, D_PACK, "payload error\n");
			जाओ discard;
		पूर्ण

		/* Extract PTS and FID */
		अगर (!(data[1] & UVC_STREAM_PTS)) अणु
			gspca_dbg(gspca_dev, D_PACK, "PTS not present\n");
			जाओ discard;
		पूर्ण
		this_pts = (data[5] << 24) | (data[4] << 16)
						| (data[3] << 8) | data[2];
		this_fid = (data[1] & UVC_STREAM_FID) ? 1 : 0;

		/* If PTS or FID has changed, start a new frame. */
		अगर (this_pts != sd->last_pts || this_fid != sd->last_fid) अणु
			अगर (gspca_dev->last_packet_type == INTER_PACKET)
				gspca_frame_add(gspca_dev, LAST_PACKET,
						शून्य, 0);
			sd->last_pts = this_pts;
			sd->last_fid = this_fid;
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					data + 12, len - 12);
		/* If this packet is marked as खातापूर्ण, end the frame */
		पूर्ण अन्यथा अगर (data[1] & UVC_STREAM_खातापूर्ण) अणु
			sd->last_pts = 0;
			अगर (gspca_dev->pixfmt.pixelक्रमmat != V4L2_PIX_FMT_JPEG
			 && gspca_dev->image_len + len - 12 !=
			    gspca_dev->pixfmt.sizeimage) अणु
				gspca_dbg(gspca_dev, D_PACK, "wrong sized frame\n");
				जाओ discard;
			पूर्ण
			gspca_frame_add(gspca_dev, LAST_PACKET,
					data + 12, len - 12);
		पूर्ण अन्यथा अणु

			/* Add the data from this payload */
			gspca_frame_add(gspca_dev, INTER_PACKET,
					data + 12, len - 12);
		पूर्ण

		/* Done this payload */
		जाओ scan_next;

discard:
		/* Discard data until a new frame starts. */
		gspca_dev->last_packet_type = DISCARD_PACKET;

scan_next:
		reमुख्यing_len -= len;
		data += len;
	पूर्ण जबतक (reमुख्यing_len > 0);
पूर्ण

/* get stream parameters (framerate) */
अटल व्योम sd_get_streamparm(काष्ठा gspca_dev *gspca_dev,
			     काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा v4l2_captureparm *cp = &parm->parm.capture;
	काष्ठा v4l2_fract *tpf = &cp->समयperframe;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	tpf->numerator = 1;
	tpf->denominator = sd->frame_rate;
पूर्ण

/* set stream parameters (framerate) */
अटल व्योम sd_set_streamparm(काष्ठा gspca_dev *gspca_dev,
			     काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा v4l2_captureparm *cp = &parm->parm.capture;
	काष्ठा v4l2_fract *tpf = &cp->समयperframe;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (tpf->numerator == 0 || tpf->denominator == 0)
		sd->frame_rate = DEFAULT_FRAME_RATE;
	अन्यथा
		sd->frame_rate = tpf->denominator / tpf->numerator;

	अगर (gspca_dev->streaming)
		set_frame_rate(gspca_dev);

	/* Return the actual framerate */
	tpf->numerator = 1;
	tpf->denominator = sd->frame_rate;
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name     = MODULE_NAME,
	.config   = sd_config,
	.init     = sd_init,
	.init_controls = sd_init_controls,
	.start    = sd_start,
	.stopN    = sd_stopN,
	.pkt_scan = sd_pkt_scan,
	.get_streamparm = sd_get_streamparm,
	.set_streamparm = sd_set_streamparm,
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x1415, 0x2000)पूर्ण,
	अणुUSB_DEVICE(0x06f8, 0x3002)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, device_table);

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id, &sd_desc, माप(काष्ठा sd),
				THIS_MODULE);
पूर्ण

अटल काष्ठा usb_driver sd_driver = अणु
	.name       = MODULE_NAME,
	.id_table   = device_table,
	.probe      = sd_probe,
	.disconnect = gspca_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend    = gspca_suspend,
	.resume     = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(sd_driver);
