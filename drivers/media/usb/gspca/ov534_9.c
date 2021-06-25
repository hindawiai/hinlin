<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ov534-ov9xxx gspca driver
 *
 * Copyright (C) 2009-2011 Jean-Francois Moine http://moinejf.मुक्त.fr
 * Copyright (C) 2008 Antonio Ospite <ospite@studenti.unina.it>
 * Copyright (C) 2008 Jim Paris <jim@jtan.com>
 *
 * Based on a prototype written by Mark Ferrell <majortrips@gmail.com>
 * USB protocol reverse engineered by Jim Paris <jim@jtan.com>
 * https://jim.sh/svn/jim/devl/playstation/ps3/eye/test/
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "ov534_9"

#समावेश "gspca.h"

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

MODULE_AUTHOR("Jean-Francois Moine <moinejf@free.fr>");
MODULE_DESCRIPTION("GSPCA/OV534_9 USB Camera Driver");
MODULE_LICENSE("GPL");

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */
	__u32 last_pts;
	u8 last_fid;

	u8 sensor;
पूर्ण;
क्रमागत sensors अणु
	SENSOR_OV965x,		/* ov9657 */
	SENSOR_OV971x,		/* ov9712 */
	SENSOR_OV562x,		/* ov5621 */
	SENSOR_OV361x,		/* ov3610 */
	NSENSORS
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat ov965x_mode[] = अणु
#घोषणा QVGA_MODE 0
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEGपूर्ण,
#घोषणा VGA_MODE 1
	अणु640, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEGपूर्ण,
#घोषणा SVGA_MODE 2
	अणु800, 600, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 800,
		.sizeimage = 800 * 600 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEGपूर्ण,
#घोषणा XGA_MODE 3
	अणु1024, 768, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 1024,
		.sizeimage = 1024 * 768 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEGपूर्ण,
#घोषणा SXGA_MODE 4
	अणु1280, 1024, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 1280,
		.sizeimage = 1280 * 1024 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEGपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat ov971x_mode[] = अणु
	अणु640, 480, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGB
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat ov562x_mode[] = अणु
	अणु2592, 1680, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 2592,
		.sizeimage = 2592 * 1680,
		.colorspace = V4L2_COLORSPACE_SRGB
	पूर्ण
पूर्ण;

क्रमागत ov361x अणु
	ov361x_2048 = 0,
	ov361x_1600,
	ov361x_1024,
	ov361x_640,
	ov361x_320,
	ov361x_160,
	ov361x_last
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat ov361x_mode[] = अणु
	अणु0x800, 0x600, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 0x800,
		.sizeimage = 0x800 * 0x600,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु1600, 1200, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 1600,
		.sizeimage = 1600 * 1200,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु1024, 768, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 768,
		.sizeimage = 1024 * 768,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु640, 480, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु320, 240, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु160, 120, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 160 * 120,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण
पूर्ण;

अटल स्थिर u8 ov361x_start_2048[][2] = अणु
	अणु0x12, 0x80पूर्ण,
	अणु0x13, 0xcfपूर्ण,
	अणु0x14, 0x40पूर्ण,
	अणु0x15, 0x00पूर्ण,
	अणु0x01, 0x80पूर्ण,
	अणु0x02, 0x80पूर्ण,
	अणु0x04, 0x70पूर्ण,
	अणु0x0d, 0x40पूर्ण,
	अणु0x0f, 0x47पूर्ण,
	अणु0x11, 0x81पूर्ण,
	अणु0x32, 0x36पूर्ण,
	अणु0x33, 0x0cपूर्ण,
	अणु0x34, 0x00पूर्ण,
	अणु0x35, 0x90पूर्ण,
	अणु0x12, 0x00पूर्ण,
	अणु0x17, 0x10पूर्ण,
	अणु0x18, 0x90पूर्ण,
	अणु0x19, 0x00पूर्ण,
	अणु0x1a, 0xc0पूर्ण,
पूर्ण;
अटल स्थिर u8 ov361x_bridge_start_2048[][2] = अणु
	अणु0xf1, 0x60पूर्ण,
	अणु0x88, 0x00पूर्ण,
	अणु0x89, 0x08पूर्ण,
	अणु0x8a, 0x00पूर्ण,
	अणु0x8b, 0x06पूर्ण,
	अणु0x8c, 0x01पूर्ण,
	अणु0x8d, 0x10पूर्ण,
	अणु0x1c, 0x00पूर्ण,
	अणु0x1d, 0x48पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0xffपूर्ण,
	अणु0x1c, 0x0aपूर्ण,
	अणु0x1d, 0x2eपूर्ण,
	अणु0x1d, 0x1eपूर्ण,
पूर्ण;

अटल स्थिर u8 ov361x_start_1600[][2] = अणु
	अणु0x12, 0x80पूर्ण,
	अणु0x13, 0xcfपूर्ण,
	अणु0x14, 0x40पूर्ण,
	अणु0x15, 0x00पूर्ण,
	अणु0x01, 0x80पूर्ण,
	अणु0x02, 0x80पूर्ण,
	अणु0x04, 0x70पूर्ण,
	अणु0x0d, 0x40पूर्ण,
	अणु0x0f, 0x47पूर्ण,
	अणु0x11, 0x81पूर्ण,
	अणु0x32, 0x36पूर्ण,
	अणु0x33, 0x0Cपूर्ण,
	अणु0x34, 0x00पूर्ण,
	अणु0x35, 0x90पूर्ण,
	अणु0x12, 0x00पूर्ण,
	अणु0x17, 0x10पूर्ण,
	अणु0x18, 0x90पूर्ण,
	अणु0x19, 0x00पूर्ण,
	अणु0x1a, 0xc0पूर्ण,
पूर्ण;
अटल स्थिर u8 ov361x_bridge_start_1600[][2] = अणु
	अणु0xf1, 0x60पूर्ण,  /* Hsize[7:0] */
	अणु0x88, 0x00पूर्ण,  /* Hsize[15:8] Write Only, can't पढ़ो */
	अणु0x89, 0x08पूर्ण,  /* Vsize[7:0] */
	अणु0x8a, 0x00पूर्ण,  /* Vsize[15:8] Write Only, can't पढ़ो */
	अणु0x8b, 0x06पूर्ण,  /* क्रम Iso */
	अणु0x8c, 0x01पूर्ण,  /* RAW input */
	अणु0x8d, 0x10पूर्ण,
	अणु0x1c, 0x00पूर्ण,  /* RAW output, Iso transfer */
	अणु0x1d, 0x48पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0xffपूर्ण,
	अणु0x1c, 0x0aपूर्ण,  /* turn off JPEG, Iso mode */
	अणु0x1d, 0x2eपूर्ण,  /* क्रम Iso */
	अणु0x1d, 0x1eपूर्ण,
पूर्ण;

अटल स्थिर u8 ov361x_start_1024[][2] = अणु
	अणु0x12, 0x80पूर्ण,
	अणु0x13, 0xcfपूर्ण,
	अणु0x14, 0x40पूर्ण,
	अणु0x15, 0x00पूर्ण,
	अणु0x01, 0x80पूर्ण,
	अणु0x02, 0x80पूर्ण,
	अणु0x04, 0x70पूर्ण,
	अणु0x0d, 0x40पूर्ण,
	अणु0x0f, 0x47पूर्ण,
	अणु0x11, 0x81पूर्ण,
	अणु0x32, 0x36पूर्ण,
	अणु0x33, 0x0Cपूर्ण,
	अणु0x34, 0x00पूर्ण,
	अणु0x35, 0x90पूर्ण,
	अणु0x12, 0x40पूर्ण,
	अणु0x17, 0x1fपूर्ण,
	अणु0x18, 0x5fपूर्ण,
	अणु0x19, 0x00पूर्ण,
	अणु0x1a, 0x68पूर्ण,
पूर्ण;
अटल स्थिर u8 ov361x_bridge_start_1024[][2] = अणु
	अणु0xf1, 0x60पूर्ण,  /* Hsize[7:0] */
	अणु0x88, 0x00पूर्ण,  /* Hsize[15:8] Write Only, can't पढ़ो */
	अणु0x89, 0x04पूर्ण,  /* Vsize[7:0] */
	अणु0x8a, 0x00पूर्ण,  /* Vsize[15:8] Write Only, can't पढ़ो */
	अणु0x8b, 0x03पूर्ण,  /* क्रम Iso */
	अणु0x8c, 0x01पूर्ण,  /* RAW input  */
	अणु0x8d, 0x10पूर्ण,
	अणु0x1c, 0x00पूर्ण,  /* RAW output, Iso transfer */
	अणु0x1d, 0x48पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0xffपूर्ण,
	अणु0x1c, 0x0aपूर्ण,  /* turn off JPEG, Iso mode */
	अणु0x1d, 0x2eपूर्ण,  /* क्रम Iso */
	अणु0x1d, 0x1eपूर्ण,
पूर्ण;

अटल स्थिर u8 ov361x_start_640[][2] = अणु
	अणु0x12, 0x80पूर्ण,
	अणु0x13, 0xcfपूर्ण,
	अणु0x14, 0x40पूर्ण,
	अणु0x15, 0x00पूर्ण,
	अणु0x01, 0x80पूर्ण,
	अणु0x02, 0x80पूर्ण,
	अणु0x04, 0x70पूर्ण,
	अणु0x0d, 0x40पूर्ण,
	अणु0x0f, 0x47पूर्ण,
	अणु0x11, 0x81पूर्ण,
	अणु0x32, 0x36पूर्ण,
	अणु0x33, 0x0Cपूर्ण,
	अणु0x34, 0x00पूर्ण,
	अणु0x35, 0x90पूर्ण,
	अणु0x12, 0x40पूर्ण,
	अणु0x17, 0x1fपूर्ण,
	अणु0x18, 0x5fपूर्ण,
	अणु0x19, 0x00पूर्ण,
	अणु0x1a, 0x68पूर्ण,
पूर्ण;

अटल स्थिर u8 ov361x_bridge_start_640[][2] = अणु
	अणु0xf1, 0x60पूर्ण,  /* Hsize[7:0]*/
	अणु0x88, 0x00पूर्ण,  /* Hsize[15:8] Write Only, can't पढ़ो */
	अणु0x89, 0x04पूर्ण,  /* Vsize[7:0] */
	अणु0x8a, 0x00पूर्ण,  /* Vsize[15:8] Write Only, can't पढ़ो */
	अणु0x8b, 0x03पूर्ण,  /* क्रम Iso */
	अणु0x8c, 0x01पूर्ण,  /* RAW input */
	अणु0x8d, 0x10पूर्ण,
	अणु0x1c, 0x00पूर्ण,  /* RAW output, Iso transfer */
	अणु0x1d, 0x48पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0xffपूर्ण,
	अणु0x1c, 0x0aपूर्ण,  /* turn off JPEG, Iso mode */
	अणु0x1d, 0x2eपूर्ण,  /* क्रम Iso */
	अणु0x1d, 0x1eपूर्ण,
पूर्ण;

अटल स्थिर u8 ov361x_start_320[][2] = अणु
	अणु0x12, 0x80पूर्ण,
	अणु0x13, 0xcfपूर्ण,
	अणु0x14, 0x40पूर्ण,
	अणु0x15, 0x00पूर्ण,
	अणु0x01, 0x80पूर्ण,
	अणु0x02, 0x80पूर्ण,
	अणु0x04, 0x70पूर्ण,
	अणु0x0d, 0x40पूर्ण,
	अणु0x0f, 0x47पूर्ण,
	अणु0x11, 0x81पूर्ण,
	अणु0x32, 0x36पूर्ण,
	अणु0x33, 0x0Cपूर्ण,
	अणु0x34, 0x00पूर्ण,
	अणु0x35, 0x90पूर्ण,
	अणु0x12, 0x40पूर्ण,
	अणु0x17, 0x1fपूर्ण,
	अणु0x18, 0x5fपूर्ण,
	अणु0x19, 0x00पूर्ण,
	अणु0x1a, 0x68पूर्ण,
पूर्ण;

अटल स्थिर u8 ov361x_bridge_start_320[][2] = अणु
	अणु0xf1, 0x60पूर्ण,  /* Hsize[7:0] */
	अणु0x88, 0x00पूर्ण,  /* Hsize[15:8] Write Only, can't पढ़ो */
	अणु0x89, 0x04पूर्ण,  /* Vsize[7:0] */
	अणु0x8a, 0x00पूर्ण,  /* Vsize[15:8] Write Only, can't पढ़ो */
	अणु0x8b, 0x03पूर्ण,  /* क्रम Iso */
	अणु0x8c, 0x01पूर्ण,  /* RAW input */
	अणु0x8d, 0x10पूर्ण,
	अणु0x1c, 0x00पूर्ण,  /* RAW output, Iso transfer; */
	अणु0x1d, 0x48पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0xffपूर्ण,
	अणु0x1c, 0x0aपूर्ण,  /* turn off JPEG, Iso mode */
	अणु0x1d, 0x2eपूर्ण,  /* क्रम Iso */
	अणु0x1d, 0x1eपूर्ण,
पूर्ण;

अटल स्थिर u8 ov361x_start_160[][2] = अणु
	अणु0x12, 0x80पूर्ण,
	अणु0x13, 0xcfपूर्ण,
	अणु0x14, 0x40पूर्ण,
	अणु0x15, 0x00पूर्ण,
	अणु0x01, 0x80पूर्ण,
	अणु0x02, 0x80पूर्ण,
	अणु0x04, 0x70पूर्ण,
	अणु0x0d, 0x40पूर्ण,
	अणु0x0f, 0x47पूर्ण,
	अणु0x11, 0x81पूर्ण,
	अणु0x32, 0x36पूर्ण,
	अणु0x33, 0x0Cपूर्ण,
	अणु0x34, 0x00पूर्ण,
	अणु0x35, 0x90पूर्ण,
	अणु0x12, 0x40पूर्ण,
	अणु0x17, 0x1fपूर्ण,
	अणु0x18, 0x5fपूर्ण,
	अणु0x19, 0x00पूर्ण,
	अणु0x1a, 0x68पूर्ण,
पूर्ण;

अटल स्थिर u8 ov361x_bridge_start_160[][2] = अणु
	अणु0xf1, 0x60पूर्ण,  /* Hsize[7:0] */
	अणु0x88, 0x00पूर्ण,  /* Hsize[15:8] Write Only, can't पढ़ो */
	अणु0x89, 0x04पूर्ण,  /* Vsize[7:0] */
	अणु0x8a, 0x00पूर्ण,  /* Vsize[15:8] Write Only, can't पढ़ो */
	अणु0x8b, 0x03पूर्ण,  /* क्रम Iso */
	अणु0x8c, 0x01पूर्ण,  /* RAW input */
	अणु0x8d, 0x10पूर्ण,
	अणु0x1c, 0x00पूर्ण,  /* RAW output, Iso transfer */
	अणु0x1d, 0x48पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0xffपूर्ण,
	अणु0x1c, 0x0aपूर्ण,  /* turn off JPEG, Iso mode */
	अणु0x1d, 0x2eपूर्ण,  /* क्रम Iso */
	अणु0x1d, 0x1eपूर्ण,
पूर्ण;

अटल स्थिर u8 bridge_init[][2] = अणु
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
	अणु0x1c, 0x0aपूर्ण,
	अणु0x1d, 0x48पूर्ण,
	अणु0xc0, 0x50पूर्ण,
	अणु0xc1, 0x3cपूर्ण,
	अणु0x34, 0x05पूर्ण,
	अणु0xc2, 0x0cपूर्ण,
	अणु0xc3, 0xf9पूर्ण,
	अणु0x34, 0x05पूर्ण,
	अणु0xe7, 0x2eपूर्ण,
	अणु0x31, 0xf9पूर्ण,
	अणु0x35, 0x02पूर्ण,
	अणु0xd9, 0x10पूर्ण,
	अणु0x25, 0x42पूर्ण,
	अणु0x94, 0x11पूर्ण,
पूर्ण;

अटल स्थिर u8 ov965x_init[][2] = अणु
	अणु0x12, 0x80पूर्ण,	/* com7 - SSCB reset */
	अणु0x00, 0x00पूर्ण,	/* gain */
	अणु0x01, 0x80पूर्ण,	/* blue */
	अणु0x02, 0x80पूर्ण,	/* red */
	अणु0x03, 0x1bपूर्ण,	/* vref */
	अणु0x04, 0x03पूर्ण,	/* com1 - exposure low bits */
	अणु0x0b, 0x57पूर्ण,	/* ver */
	अणु0x0e, 0x61पूर्ण,	/* com5 */
	अणु0x0f, 0x42पूर्ण,	/* com6 */
	अणु0x11, 0x00पूर्ण,	/* clkrc */
	अणु0x12, 0x02पूर्ण,	/* com7 - 15fps VGA YUYV */
	अणु0x13, 0xe7पूर्ण,	/* com8 - everything (AGC, AWB and AEC) */
	अणु0x14, 0x28पूर्ण,	/* com9 */
	अणु0x16, 0x24पूर्ण,	/* reg16 */
	अणु0x17, 0x1dपूर्ण,	/* hstart*/
	अणु0x18, 0xbdपूर्ण,	/* hstop */
	अणु0x19, 0x01पूर्ण,	/* vstrt */
	अणु0x1a, 0x81पूर्ण,	/* vstop*/
	अणु0x1e, 0x04पूर्ण,	/* mvfp */
	अणु0x24, 0x3cपूर्ण,	/* aew */
	अणु0x25, 0x36पूर्ण,	/* aeb */
	अणु0x26, 0x71पूर्ण,	/* vpt */
	अणु0x27, 0x08पूर्ण,	/* bbias */
	अणु0x28, 0x08पूर्ण,	/* gbbias */
	अणु0x29, 0x15पूर्ण,	/* gr com */
	अणु0x2a, 0x00पूर्ण,	/* exhch */
	अणु0x2b, 0x00पूर्ण,	/* exhcl */
	अणु0x2c, 0x08पूर्ण,	/* rbias */
	अणु0x32, 0xffपूर्ण,	/* href */
	अणु0x33, 0x00पूर्ण,	/* chlf */
	अणु0x34, 0x3fपूर्ण,	/* aref1 */
	अणु0x35, 0x00पूर्ण,	/* aref2 */
	अणु0x36, 0xf8पूर्ण,	/* aref3 */
	अणु0x38, 0x72पूर्ण,	/* adc2 */
	अणु0x39, 0x57पूर्ण,	/* aref4 */
	अणु0x3a, 0x80पूर्ण,	/* tslb - yuyv */
	अणु0x3b, 0xc4पूर्ण,	/* com11 - night mode 1/4 frame rate */
	अणु0x3d, 0x99पूर्ण,	/* com13 */
	अणु0x3f, 0xc1पूर्ण,	/* edge */
	अणु0x40, 0xc0पूर्ण,	/* com15 */
	अणु0x41, 0x40पूर्ण,	/* com16 */
	अणु0x42, 0xc0पूर्ण,	/* com17 */
	अणु0x43, 0x0aपूर्ण,	/* rsvd */
	अणु0x44, 0xf0पूर्ण,
	अणु0x45, 0x46पूर्ण,
	अणु0x46, 0x62पूर्ण,
	अणु0x47, 0x2aपूर्ण,
	अणु0x48, 0x3cपूर्ण,
	अणु0x4a, 0xfcपूर्ण,
	अणु0x4b, 0xfcपूर्ण,
	अणु0x4c, 0x7fपूर्ण,
	अणु0x4d, 0x7fपूर्ण,
	अणु0x4e, 0x7fपूर्ण,
	अणु0x4f, 0x98पूर्ण,	/* matrix */
	अणु0x50, 0x98पूर्ण,
	अणु0x51, 0x00पूर्ण,
	अणु0x52, 0x28पूर्ण,
	अणु0x53, 0x70पूर्ण,
	अणु0x54, 0x98पूर्ण,
	अणु0x58, 0x1aपूर्ण,	/* matrix coef sign */
	अणु0x59, 0x85पूर्ण,	/* AWB control */
	अणु0x5a, 0xa9पूर्ण,
	अणु0x5b, 0x64पूर्ण,
	अणु0x5c, 0x84पूर्ण,
	अणु0x5d, 0x53पूर्ण,
	अणु0x5e, 0x0eपूर्ण,
	अणु0x5f, 0xf0पूर्ण,	/* AWB blue limit */
	अणु0x60, 0xf0पूर्ण,	/* AWB red limit */
	अणु0x61, 0xf0पूर्ण,	/* AWB green limit */
	अणु0x62, 0x00पूर्ण,	/* lcc1 */
	अणु0x63, 0x00पूर्ण,	/* lcc2 */
	अणु0x64, 0x02पूर्ण,	/* lcc3 */
	अणु0x65, 0x16पूर्ण,	/* lcc4 */
	अणु0x66, 0x01पूर्ण,	/* lcc5 */
	अणु0x69, 0x02पूर्ण,	/* hv */
	अणु0x6b, 0x5aपूर्ण,	/* dbvl */
	अणु0x6c, 0x04पूर्ण,
	अणु0x6d, 0x55पूर्ण,
	अणु0x6e, 0x00पूर्ण,
	अणु0x6f, 0x9dपूर्ण,
	अणु0x70, 0x21पूर्ण,	/* dnsth */
	अणु0x71, 0x78पूर्ण,
	अणु0x72, 0x00पूर्ण,	/* poidx */
	अणु0x73, 0x01पूर्ण,	/* pckdv */
	अणु0x74, 0x3aपूर्ण,	/* xindx */
	अणु0x75, 0x35पूर्ण,	/* yindx */
	अणु0x76, 0x01पूर्ण,
	अणु0x77, 0x02पूर्ण,
	अणु0x7a, 0x12पूर्ण,	/* gamma curve */
	अणु0x7b, 0x08पूर्ण,
	अणु0x7c, 0x16पूर्ण,
	अणु0x7d, 0x30पूर्ण,
	अणु0x7e, 0x5eपूर्ण,
	अणु0x7f, 0x72पूर्ण,
	अणु0x80, 0x82पूर्ण,
	अणु0x81, 0x8eपूर्ण,
	अणु0x82, 0x9aपूर्ण,
	अणु0x83, 0xa4पूर्ण,
	अणु0x84, 0xacपूर्ण,
	अणु0x85, 0xb8पूर्ण,
	अणु0x86, 0xc3पूर्ण,
	अणु0x87, 0xd6पूर्ण,
	अणु0x88, 0xe6पूर्ण,
	अणु0x89, 0xf2पूर्ण,
	अणु0x8a, 0x03पूर्ण,
	अणु0x8c, 0x89पूर्ण,	/* com19 */
	अणु0x14, 0x28पूर्ण,	/* com9 */
	अणु0x90, 0x7dपूर्ण,
	अणु0x91, 0x7bपूर्ण,
	अणु0x9d, 0x03पूर्ण,	/* lcc6 */
	अणु0x9e, 0x04पूर्ण,	/* lcc7 */
	अणु0x9f, 0x7aपूर्ण,
	अणु0xa0, 0x79पूर्ण,
	अणु0xa1, 0x40पूर्ण,	/* aechm */
	अणु0xa4, 0x50पूर्ण,	/* com21 */
	अणु0xa5, 0x68पूर्ण,	/* com26 */
	अणु0xa6, 0x4aपूर्ण,	/* AWB green */
	अणु0xa8, 0xc1पूर्ण,	/* refa8 */
	अणु0xa9, 0xefपूर्ण,	/* refa9 */
	अणु0xaa, 0x92पूर्ण,
	अणु0xab, 0x04पूर्ण,
	अणु0xac, 0x80पूर्ण,	/* black level control */
	अणु0xad, 0x80पूर्ण,
	अणु0xae, 0x80पूर्ण,
	अणु0xaf, 0x80पूर्ण,
	अणु0xb2, 0xf2पूर्ण,
	अणु0xb3, 0x20पूर्ण,
	अणु0xb4, 0x20पूर्ण,	/* ctrlb4 */
	अणु0xb5, 0x00पूर्ण,
	अणु0xb6, 0xafपूर्ण,
	अणु0xbb, 0xaeपूर्ण,
	अणु0xbc, 0x7fपूर्ण,	/* ADC channel offsets */
	अणु0xdb, 0x7fपूर्ण,
	अणु0xbe, 0x7fपूर्ण,
	अणु0xbf, 0x7fपूर्ण,
	अणु0xc0, 0xe2पूर्ण,
	अणु0xc1, 0xc0पूर्ण,
	अणु0xc2, 0x01पूर्ण,
	अणु0xc3, 0x4eपूर्ण,
	अणु0xc6, 0x85पूर्ण,
	अणु0xc7, 0x80पूर्ण,	/* com24 */
	अणु0xc9, 0xe0पूर्ण,
	अणु0xca, 0xe8पूर्ण,
	अणु0xcb, 0xf0पूर्ण,
	अणु0xcc, 0xd8पूर्ण,
	अणु0xcd, 0xf1पूर्ण,
	अणु0x4f, 0x98पूर्ण,	/* matrix */
	अणु0x50, 0x98पूर्ण,
	अणु0x51, 0x00पूर्ण,
	अणु0x52, 0x28पूर्ण,
	अणु0x53, 0x70पूर्ण,
	अणु0x54, 0x98पूर्ण,
	अणु0x58, 0x1aपूर्ण,
	अणु0xff, 0x41पूर्ण,	/* पढ़ो 41, ग_लिखो ff 00 */
	अणु0x41, 0x40पूर्ण,	/* com16 */

	अणु0xc5, 0x03पूर्ण,	/* 60 Hz banding filter */
	अणु0x6a, 0x02पूर्ण,	/* 50 Hz banding filter */

	अणु0x12, 0x62पूर्ण,	/* com7 - 30fps VGA YUV */
	अणु0x36, 0xfaपूर्ण,	/* aref3 */
	अणु0x69, 0x0aपूर्ण,	/* hv */
	अणु0x8c, 0x89पूर्ण,	/* com22 */
	अणु0x14, 0x28पूर्ण,	/* com9 */
	अणु0x3e, 0x0cपूर्ण,
	अणु0x41, 0x40पूर्ण,	/* com16 */
	अणु0x72, 0x00पूर्ण,
	अणु0x73, 0x00पूर्ण,
	अणु0x74, 0x3aपूर्ण,
	अणु0x75, 0x35पूर्ण,
	अणु0x76, 0x01पूर्ण,
	अणु0xc7, 0x80पूर्ण,
	अणु0x03, 0x12पूर्ण,	/* vref */
	अणु0x17, 0x16पूर्ण,	/* hstart */
	अणु0x18, 0x02पूर्ण,	/* hstop */
	अणु0x19, 0x01पूर्ण,	/* vstrt */
	अणु0x1a, 0x3dपूर्ण,	/* vstop */
	अणु0x32, 0xffपूर्ण,	/* href */
	अणु0xc0, 0xaaपूर्ण,
पूर्ण;

अटल स्थिर u8 bridge_init_2[][2] = अणु
	अणु0x94, 0xaaपूर्ण,
	अणु0xf1, 0x60पूर्ण,
	अणु0xe5, 0x04पूर्ण,
	अणु0xc0, 0x50पूर्ण,
	अणु0xc1, 0x3cपूर्ण,
	अणु0x8c, 0x00पूर्ण,
	अणु0x8d, 0x1cपूर्ण,
	अणु0x34, 0x05पूर्ण,

	अणु0xc2, 0x0cपूर्ण,
	अणु0xc3, 0xf9पूर्ण,
	अणु0xda, 0x01पूर्ण,
	अणु0x50, 0x00पूर्ण,
	अणु0x51, 0xa0पूर्ण,
	अणु0x52, 0x3cपूर्ण,
	अणु0x53, 0x00पूर्ण,
	अणु0x54, 0x00पूर्ण,
	अणु0x55, 0x00पूर्ण,
	अणु0x57, 0x00पूर्ण,
	अणु0x5c, 0x00पूर्ण,
	अणु0x5a, 0xa0पूर्ण,
	अणु0x5b, 0x78पूर्ण,
	अणु0x35, 0x02पूर्ण,
	अणु0xd9, 0x10पूर्ण,
	अणु0x94, 0x11पूर्ण,
पूर्ण;

अटल स्थिर u8 ov965x_init_2[][2] = अणु
	अणु0x3b, 0xc4पूर्ण,
	अणु0x1e, 0x04पूर्ण,	/* mvfp */
	अणु0x13, 0xe0पूर्ण,	/* com8 */
	अणु0x00, 0x00पूर्ण,	/* gain */
	अणु0x13, 0xe7पूर्ण,	/* com8 - everything (AGC, AWB and AEC) */
	अणु0x11, 0x03पूर्ण,	/* clkrc */
	अणु0x6b, 0x5aपूर्ण,	/* dblv */
	अणु0x6a, 0x05पूर्ण,
	अणु0xc5, 0x07पूर्ण,
	अणु0xa2, 0x4bपूर्ण,
	अणु0xa3, 0x3eपूर्ण,
	अणु0x2d, 0x00पूर्ण,
	अणु0xff, 0x42पूर्ण,	/* पढ़ो 42, ग_लिखो ff 00 */
	अणु0x42, 0xc0पूर्ण,	/* com17 */
	अणु0x2d, 0x00पूर्ण,
	अणु0xff, 0x42पूर्ण,	/* पढ़ो 42, ग_लिखो ff 00 */
	अणु0x42, 0xc1पूर्ण,	/* com17 */
/* sharpness */
	अणु0x3f, 0x01पूर्ण,
	अणु0xff, 0x42पूर्ण,	/* पढ़ो 42, ग_लिखो ff 00 */
	अणु0x42, 0xc1पूर्ण,	/* com17 */
/* saturation */
	अणु0x4f, 0x98पूर्ण,	/* matrix */
	अणु0x50, 0x98पूर्ण,
	अणु0x51, 0x00पूर्ण,
	अणु0x52, 0x28पूर्ण,
	अणु0x53, 0x70पूर्ण,
	अणु0x54, 0x98पूर्ण,
	अणु0x58, 0x1aपूर्ण,
	अणु0xff, 0x41पूर्ण,	/* पढ़ो 41, ग_लिखो ff 00 */
	अणु0x41, 0x40पूर्ण,	/* com16 */
/* contrast */
	अणु0x56, 0x40पूर्ण,
/* brightness */
	अणु0x55, 0x8fपूर्ण,
/* expo */
	अणु0x10, 0x25पूर्ण,	/* aech - exposure high bits */
	अणु0xff, 0x13पूर्ण,	/* पढ़ो 13, ग_लिखो ff 00 */
	अणु0x13, 0xe7पूर्ण,	/* com8 - everything (AGC, AWB and AEC) */
पूर्ण;

अटल स्थिर u8 ov971x_init[][2] = अणु
	अणु0x12, 0x80पूर्ण,
	अणु0x09, 0x10पूर्ण,
	अणु0x1e, 0x07पूर्ण,
	अणु0x5f, 0x18पूर्ण,
	अणु0x69, 0x04पूर्ण,
	अणु0x65, 0x2aपूर्ण,
	अणु0x68, 0x0aपूर्ण,
	अणु0x39, 0x28पूर्ण,
	अणु0x4d, 0x90पूर्ण,
	अणु0xc1, 0x80पूर्ण,
	अणु0x0c, 0x30पूर्ण,
	अणु0x6d, 0x02पूर्ण,
	अणु0x96, 0xf1पूर्ण,
	अणु0xbc, 0x68पूर्ण,
	अणु0x12, 0x00पूर्ण,
	अणु0x3b, 0x00पूर्ण,
	अणु0x97, 0x80पूर्ण,
	अणु0x17, 0x25पूर्ण,
	अणु0x18, 0xa2पूर्ण,
	अणु0x19, 0x01पूर्ण,
	अणु0x1a, 0xcaपूर्ण,
	अणु0x03, 0x0aपूर्ण,
	अणु0x32, 0x07पूर्ण,
	अणु0x98, 0x40पूर्ण,	/*अणु0x98, 0x00पूर्ण,*/
	अणु0x99, 0xA0पूर्ण,	/*अणु0x99, 0x00पूर्ण,*/
	अणु0x9a, 0x01पूर्ण,	/*अणु0x9a, 0x00पूर्ण,*/
	अणु0x57, 0x00पूर्ण,
	अणु0x58, 0x78पूर्ण,	/*अणु0x58, 0xc8पूर्ण,*/
	अणु0x59, 0x50पूर्ण,	/*अणु0x59, 0xa0पूर्ण,*/
	अणु0x4c, 0x13पूर्ण,
	अणु0x4b, 0x36पूर्ण,
	अणु0x3d, 0x3cपूर्ण,
	अणु0x3e, 0x03पूर्ण,
	अणु0xbd, 0x50पूर्ण,	/*अणु0xbd, 0xa0पूर्ण,*/
	अणु0xbe, 0x78पूर्ण,	/*अणु0xbe, 0xc8पूर्ण,*/
	अणु0x4e, 0x55पूर्ण,
	अणु0x4f, 0x55पूर्ण,
	अणु0x50, 0x55पूर्ण,
	अणु0x51, 0x55पूर्ण,
	अणु0x24, 0x55पूर्ण,
	अणु0x25, 0x40पूर्ण,
	अणु0x26, 0xa1पूर्ण,
	अणु0x5c, 0x59पूर्ण,
	अणु0x5d, 0x00पूर्ण,
	अणु0x11, 0x00पूर्ण,
	अणु0x2a, 0x98पूर्ण,
	अणु0x2b, 0x06पूर्ण,
	अणु0x2d, 0x00पूर्ण,
	अणु0x2e, 0x00पूर्ण,
	अणु0x13, 0xa5पूर्ण,
	अणु0x14, 0x40पूर्ण,
	अणु0x4a, 0x00पूर्ण,
	अणु0x49, 0xceपूर्ण,
	अणु0x22, 0x03पूर्ण,
	अणु0x09, 0x00पूर्ण
पूर्ण;

अटल स्थिर u8 ov965x_start_1_vga[][2] = अणु	/* same क्रम qvga */
	अणु0x12, 0x62पूर्ण,	/* com7 - 30fps VGA YUV */
	अणु0x36, 0xfaपूर्ण,	/* aref3 */
	अणु0x69, 0x0aपूर्ण,	/* hv */
	अणु0x8c, 0x89पूर्ण,	/* com22 */
	अणु0x14, 0x28पूर्ण,	/* com9 */
	अणु0x3e, 0x0cपूर्ण,	/* com14 */
	अणु0x41, 0x40पूर्ण,	/* com16 */
	अणु0x72, 0x00पूर्ण,
	अणु0x73, 0x00पूर्ण,
	अणु0x74, 0x3aपूर्ण,
	अणु0x75, 0x35पूर्ण,
	अणु0x76, 0x01पूर्ण,
	अणु0xc7, 0x80पूर्ण,	/* com24 */
	अणु0x03, 0x12पूर्ण,	/* vref */
	अणु0x17, 0x16पूर्ण,	/* hstart */
	अणु0x18, 0x02पूर्ण,	/* hstop */
	अणु0x19, 0x01पूर्ण,	/* vstrt */
	अणु0x1a, 0x3dपूर्ण,	/* vstop */
	अणु0x32, 0xffपूर्ण,	/* href */
	अणु0xc0, 0xaaपूर्ण,
पूर्ण;

अटल स्थिर u8 ov965x_start_1_svga[][2] = अणु
	अणु0x12, 0x02पूर्ण,	/* com7 - YUYV - VGA 15 full resolution */
	अणु0x36, 0xf8पूर्ण,	/* aref3 */
	अणु0x69, 0x02पूर्ण,	/* hv */
	अणु0x8c, 0x0dपूर्ण,	/* com22 */
	अणु0x3e, 0x0cपूर्ण,	/* com14 */
	अणु0x41, 0x40पूर्ण,	/* com16 */
	अणु0x72, 0x00पूर्ण,
	अणु0x73, 0x01पूर्ण,
	अणु0x74, 0x3aपूर्ण,
	अणु0x75, 0x35पूर्ण,
	अणु0x76, 0x01पूर्ण,
	अणु0xc7, 0x80पूर्ण,	/* com24 */
	अणु0x03, 0x1bपूर्ण,	/* vref */
	अणु0x17, 0x1dपूर्ण,	/* hstart */
	अणु0x18, 0xbdपूर्ण,	/* hstop */
	अणु0x19, 0x01पूर्ण,	/* vstrt */
	अणु0x1a, 0x81पूर्ण,	/* vstop */
	अणु0x32, 0xffपूर्ण,	/* href */
	अणु0xc0, 0xe2पूर्ण,
पूर्ण;

अटल स्थिर u8 ov965x_start_1_xga[][2] = अणु
	अणु0x12, 0x02पूर्ण,	/* com7 */
	अणु0x36, 0xf8पूर्ण,	/* aref3 */
	अणु0x69, 0x02पूर्ण,	/* hv */
	अणु0x8c, 0x89पूर्ण,	/* com22 */
	अणु0x14, 0x28पूर्ण,	/* com9 */
	अणु0x3e, 0x0cपूर्ण,	/* com14 */
	अणु0x41, 0x40पूर्ण,	/* com16 */
	अणु0x72, 0x00पूर्ण,
	अणु0x73, 0x01पूर्ण,
	अणु0x74, 0x3aपूर्ण,
	अणु0x75, 0x35पूर्ण,
	अणु0x76, 0x01पूर्ण,
	अणु0xc7, 0x80पूर्ण,	/* com24 */
	अणु0x03, 0x1bपूर्ण,	/* vref */
	अणु0x17, 0x1dपूर्ण,	/* hstart */
	अणु0x18, 0xbdपूर्ण,	/* hstop */
	अणु0x19, 0x01पूर्ण,	/* vstrt */
	अणु0x1a, 0x81पूर्ण,	/* vstop */
	अणु0x32, 0xffपूर्ण,	/* href */
	अणु0xc0, 0xe2पूर्ण,
पूर्ण;

अटल स्थिर u8 ov965x_start_1_sxga[][2] = अणु
	अणु0x12, 0x02पूर्ण,	/* com7 */
	अणु0x36, 0xf8पूर्ण,	/* aref3 */
	अणु0x69, 0x02पूर्ण,	/* hv */
	अणु0x8c, 0x89पूर्ण,	/* com22 */
	अणु0x14, 0x28पूर्ण,	/* com9 */
	अणु0x3e, 0x0cपूर्ण,	/* com14 */
	अणु0x41, 0x40पूर्ण,	/* com16 */
	अणु0x72, 0x00पूर्ण,
	अणु0x73, 0x01पूर्ण,
	अणु0x74, 0x3aपूर्ण,
	अणु0x75, 0x35पूर्ण,
	अणु0x76, 0x01पूर्ण,
	अणु0xc7, 0x80पूर्ण,	/* com24 */
	अणु0x03, 0x1bपूर्ण,	/* vref */
	अणु0x17, 0x1dपूर्ण,	/* hstart */
	अणु0x18, 0x02पूर्ण,	/* hstop */
	अणु0x19, 0x01पूर्ण,	/* vstrt */
	अणु0x1a, 0x81पूर्ण,	/* vstop */
	अणु0x32, 0xffपूर्ण,	/* href */
	अणु0xc0, 0xe2पूर्ण,
पूर्ण;

अटल स्थिर u8 bridge_start_qvga[][2] = अणु
	अणु0x94, 0xaaपूर्ण,
	अणु0xf1, 0x60पूर्ण,
	अणु0xe5, 0x04पूर्ण,
	अणु0xc0, 0x50पूर्ण,
	अणु0xc1, 0x3cपूर्ण,
	अणु0x8c, 0x00पूर्ण,
	अणु0x8d, 0x1cपूर्ण,
	अणु0x34, 0x05पूर्ण,

	अणु0xc2, 0x4cपूर्ण,
	अणु0xc3, 0xf9पूर्ण,
	अणु0xda, 0x00पूर्ण,
	अणु0x50, 0x00पूर्ण,
	अणु0x51, 0xa0पूर्ण,
	अणु0x52, 0x78पूर्ण,
	अणु0x53, 0x00पूर्ण,
	अणु0x54, 0x00पूर्ण,
	अणु0x55, 0x00पूर्ण,
	अणु0x57, 0x00पूर्ण,
	अणु0x5c, 0x00पूर्ण,
	अणु0x5a, 0x50पूर्ण,
	अणु0x5b, 0x3cपूर्ण,
	अणु0x35, 0x02पूर्ण,
	अणु0xd9, 0x10पूर्ण,
	अणु0x94, 0x11पूर्ण,
पूर्ण;

अटल स्थिर u8 bridge_start_vga[][2] = अणु
	अणु0x94, 0xaaपूर्ण,
	अणु0xf1, 0x60पूर्ण,
	अणु0xe5, 0x04पूर्ण,
	अणु0xc0, 0x50पूर्ण,
	अणु0xc1, 0x3cपूर्ण,
	अणु0x8c, 0x00पूर्ण,
	अणु0x8d, 0x1cपूर्ण,
	अणु0x34, 0x05पूर्ण,
	अणु0xc2, 0x0cपूर्ण,
	अणु0xc3, 0xf9पूर्ण,
	अणु0xda, 0x01पूर्ण,
	अणु0x50, 0x00पूर्ण,
	अणु0x51, 0xa0पूर्ण,
	अणु0x52, 0x3cपूर्ण,
	अणु0x53, 0x00पूर्ण,
	अणु0x54, 0x00पूर्ण,
	अणु0x55, 0x00पूर्ण,
	अणु0x57, 0x00पूर्ण,
	अणु0x5c, 0x00पूर्ण,
	अणु0x5a, 0xa0पूर्ण,
	अणु0x5b, 0x78पूर्ण,
	अणु0x35, 0x02पूर्ण,
	अणु0xd9, 0x10पूर्ण,
	अणु0x94, 0x11पूर्ण,
पूर्ण;

अटल स्थिर u8 bridge_start_svga[][2] = अणु
	अणु0x94, 0xaaपूर्ण,
	अणु0xf1, 0x60पूर्ण,
	अणु0xe5, 0x04पूर्ण,
	अणु0xc0, 0xa0पूर्ण,
	अणु0xc1, 0x80पूर्ण,
	अणु0x8c, 0x00पूर्ण,
	अणु0x8d, 0x1cपूर्ण,
	अणु0x34, 0x05पूर्ण,
	अणु0xc2, 0x4cपूर्ण,
	अणु0xc3, 0xf9पूर्ण,
	अणु0x50, 0x00पूर्ण,
	अणु0x51, 0x40पूर्ण,
	अणु0x52, 0x00पूर्ण,
	अणु0x53, 0x00पूर्ण,
	अणु0x54, 0x00पूर्ण,
	अणु0x55, 0x88पूर्ण,
	अणु0x57, 0x00पूर्ण,
	अणु0x5c, 0x00पूर्ण,
	अणु0x5a, 0xc8पूर्ण,
	अणु0x5b, 0x96पूर्ण,
	अणु0x35, 0x02पूर्ण,
	अणु0xd9, 0x10पूर्ण,
	अणु0xda, 0x00पूर्ण,
	अणु0x94, 0x11पूर्ण,
पूर्ण;

अटल स्थिर u8 bridge_start_xga[][2] = अणु
	अणु0x94, 0xaaपूर्ण,
	अणु0xf1, 0x60पूर्ण,
	अणु0xe5, 0x04पूर्ण,
	अणु0xc0, 0xa0पूर्ण,
	अणु0xc1, 0x80पूर्ण,
	अणु0x8c, 0x00पूर्ण,
	अणु0x8d, 0x1cपूर्ण,
	अणु0x34, 0x05पूर्ण,
	अणु0xc2, 0x4cपूर्ण,
	अणु0xc3, 0xf9पूर्ण,
	अणु0x50, 0x00पूर्ण,
	अणु0x51, 0x40पूर्ण,
	अणु0x52, 0x00पूर्ण,
	अणु0x53, 0x00पूर्ण,
	अणु0x54, 0x00पूर्ण,
	अणु0x55, 0x88पूर्ण,
	अणु0x57, 0x00पूर्ण,
	अणु0x5c, 0x01पूर्ण,
	अणु0x5a, 0x00पूर्ण,
	अणु0x5b, 0xc0पूर्ण,
	अणु0x35, 0x02पूर्ण,
	अणु0xd9, 0x10पूर्ण,
	अणु0xda, 0x01पूर्ण,
	अणु0x94, 0x11पूर्ण,
पूर्ण;

अटल स्थिर u8 bridge_start_sxga[][2] = अणु
	अणु0x94, 0xaaपूर्ण,
	अणु0xf1, 0x60पूर्ण,
	अणु0xe5, 0x04पूर्ण,
	अणु0xc0, 0xa0पूर्ण,
	अणु0xc1, 0x80पूर्ण,
	अणु0x8c, 0x00पूर्ण,
	अणु0x8d, 0x1cपूर्ण,
	अणु0x34, 0x05पूर्ण,
	अणु0xc2, 0x0cपूर्ण,
	अणु0xc3, 0xf9पूर्ण,
	अणु0xda, 0x00पूर्ण,
	अणु0x35, 0x02पूर्ण,
	अणु0xd9, 0x10पूर्ण,
	अणु0x94, 0x11पूर्ण,
पूर्ण;

अटल स्थिर u8 ov965x_start_2_qvga[][2] = अणु
	अणु0x3b, 0xe4पूर्ण,	/* com11 - night mode 1/4 frame rate */
	अणु0x1e, 0x04पूर्ण,	/* mvfp */
	अणु0x13, 0xe0पूर्ण,	/* com8 */
	अणु0x00, 0x00पूर्ण,
	अणु0x13, 0xe7पूर्ण,	/* com8 - everything (AGC, AWB and AEC) */
	अणु0x11, 0x01पूर्ण,	/* clkrc */
	अणु0x6b, 0x5aपूर्ण,	/* dblv */
	अणु0x6a, 0x02पूर्ण,	/* 50 Hz banding filter */
	अणु0xc5, 0x03पूर्ण,	/* 60 Hz banding filter */
	अणु0xa2, 0x96पूर्ण,	/* bd50 */
	अणु0xa3, 0x7dपूर्ण,	/* bd60 */

	अणु0xff, 0x13पूर्ण,	/* पढ़ो 13, ग_लिखो ff 00 */
	अणु0x13, 0xe7पूर्ण,
	अणु0x3a, 0x80पूर्ण,	/* tslb - yuyv */
पूर्ण;

अटल स्थिर u8 ov965x_start_2_vga[][2] = अणु
	अणु0x3b, 0xc4पूर्ण,	/* com11 - night mode 1/4 frame rate */
	अणु0x1e, 0x04पूर्ण,	/* mvfp */
	अणु0x13, 0xe0पूर्ण,	/* com8 */
	अणु0x00, 0x00पूर्ण,
	अणु0x13, 0xe7पूर्ण,	/* com8 - everything (AGC, AWB and AEC) */
	अणु0x11, 0x03पूर्ण,	/* clkrc */
	अणु0x6b, 0x5aपूर्ण,	/* dblv */
	अणु0x6a, 0x05पूर्ण,	/* 50 Hz banding filter */
	अणु0xc5, 0x07पूर्ण,	/* 60 Hz banding filter */
	अणु0xa2, 0x4bपूर्ण,	/* bd50 */
	अणु0xa3, 0x3eपूर्ण,	/* bd60 */

	अणु0x2d, 0x00पूर्ण,	/* advfl */
पूर्ण;

अटल स्थिर u8 ov965x_start_2_svga[][2] = अणु	/* same क्रम xga */
	अणु0x3b, 0xc4पूर्ण,	/* com11 - night mode 1/4 frame rate */
	अणु0x1e, 0x04पूर्ण,	/* mvfp */
	अणु0x13, 0xe0पूर्ण,	/* com8 */
	अणु0x00, 0x00पूर्ण,
	अणु0x13, 0xe7पूर्ण,	/* com8 - everything (AGC, AWB and AEC) */
	अणु0x11, 0x01पूर्ण,	/* clkrc */
	अणु0x6b, 0x5aपूर्ण,	/* dblv */
	अणु0x6a, 0x0cपूर्ण,	/* 50 Hz banding filter */
	अणु0xc5, 0x0fपूर्ण,	/* 60 Hz banding filter */
	अणु0xa2, 0x4eपूर्ण,	/* bd50 */
	अणु0xa3, 0x41पूर्ण,	/* bd60 */
पूर्ण;

अटल स्थिर u8 ov965x_start_2_sxga[][2] = अणु
	अणु0x13, 0xe0पूर्ण,	/* com8 */
	अणु0x00, 0x00पूर्ण,
	अणु0x13, 0xe7पूर्ण,	/* com8 - everything (AGC, AWB and AEC) */
	अणु0x3b, 0xc4पूर्ण,	/* com11 - night mode 1/4 frame rate */
	अणु0x1e, 0x04पूर्ण,	/* mvfp */
	अणु0x11, 0x01पूर्ण,	/* clkrc */
	अणु0x6b, 0x5aपूर्ण,	/* dblv */
	अणु0x6a, 0x0cपूर्ण,	/* 50 Hz banding filter */
	अणु0xc5, 0x0fपूर्ण,	/* 60 Hz banding filter */
	अणु0xa2, 0x4eपूर्ण,	/* bd50 */
	अणु0xa3, 0x41पूर्ण,	/* bd60 */
पूर्ण;

अटल स्थिर u8 ov562x_init[][2] = अणु
	अणु0x88, 0x20पूर्ण,
	अणु0x89, 0x0aपूर्ण,
	अणु0x8a, 0x90पूर्ण,
	अणु0x8b, 0x06पूर्ण,
	अणु0x8c, 0x01पूर्ण,
	अणु0x8d, 0x10पूर्ण,
	अणु0x1c, 0x00पूर्ण,
	अणु0x1d, 0x48पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1d, 0xffपूर्ण,
	अणु0x1c, 0x0aपूर्ण,
	अणु0x1d, 0x2eपूर्ण,
	अणु0x1d, 0x1eपूर्ण,
पूर्ण;

अटल स्थिर u8 ov562x_init_2[][2] = अणु
	अणु0x12, 0x80पूर्ण,
	अणु0x11, 0x41पूर्ण,
	अणु0x13, 0x00पूर्ण,
	अणु0x10, 0x1eपूर्ण,
	अणु0x3b, 0x07पूर्ण,
	अणु0x5b, 0x40पूर्ण,
	अणु0x39, 0x07पूर्ण,
	अणु0x53, 0x02पूर्ण,
	अणु0x54, 0x60पूर्ण,
	अणु0x04, 0x20पूर्ण,
	अणु0x27, 0x04पूर्ण,
	अणु0x3d, 0x40पूर्ण,
	अणु0x36, 0x00पूर्ण,
	अणु0xc5, 0x04पूर्ण,
	अणु0x4e, 0x00पूर्ण,
	अणु0x4f, 0x93पूर्ण,
	अणु0x50, 0x7bपूर्ण,
	अणु0xca, 0x0cपूर्ण,
	अणु0xcb, 0x0fपूर्ण,
	अणु0x39, 0x07पूर्ण,
	अणु0x4a, 0x10पूर्ण,
	अणु0x3e, 0x0aपूर्ण,
	अणु0x3d, 0x00पूर्ण,
	अणु0x0c, 0x38पूर्ण,
	अणु0x38, 0x90पूर्ण,
	अणु0x46, 0x30पूर्ण,
	अणु0x4f, 0x93पूर्ण,
	अणु0x50, 0x7bपूर्ण,
	अणु0xab, 0x00पूर्ण,
	अणु0xca, 0x0cपूर्ण,
	अणु0xcb, 0x0fपूर्ण,
	अणु0x37, 0x02पूर्ण,
	अणु0x44, 0x48पूर्ण,
	अणु0x8d, 0x44पूर्ण,
	अणु0x2a, 0x00पूर्ण,
	अणु0x2b, 0x00पूर्ण,
	अणु0x32, 0x00पूर्ण,
	अणु0x38, 0x90पूर्ण,
	अणु0x53, 0x02पूर्ण,
	अणु0x54, 0x60पूर्ण,
	अणु0x12, 0x00पूर्ण,
	अणु0x17, 0x12पूर्ण,
	अणु0x18, 0xb4पूर्ण,
	अणु0x19, 0x0cपूर्ण,
	अणु0x1a, 0xf4पूर्ण,
	अणु0x03, 0x4aपूर्ण,
	अणु0x89, 0x20पूर्ण,
	अणु0x83, 0x80पूर्ण,
	अणु0xb7, 0x9dपूर्ण,
	अणु0xb6, 0x11पूर्ण,
	अणु0xb5, 0x55पूर्ण,
	अणु0xb4, 0x00पूर्ण,
	अणु0xa9, 0xf0पूर्ण,
	अणु0xa8, 0x0aपूर्ण,
	अणु0xb8, 0xf0पूर्ण,
	अणु0xb9, 0xf0पूर्ण,
	अणु0xba, 0xf0पूर्ण,
	अणु0x81, 0x07पूर्ण,
	अणु0x63, 0x44पूर्ण,
	अणु0x13, 0xc7पूर्ण,
	अणु0x14, 0x60पूर्ण,
	अणु0x33, 0x75पूर्ण,
	अणु0x2c, 0x00पूर्ण,
	अणु0x09, 0x00पूर्ण,
	अणु0x35, 0x30पूर्ण,
	अणु0x27, 0x04पूर्ण,
	अणु0x3c, 0x07पूर्ण,
	अणु0x3a, 0x0aपूर्ण,
	अणु0x3b, 0x07पूर्ण,
	अणु0x01, 0x40पूर्ण,
	अणु0x02, 0x40पूर्ण,
	अणु0x16, 0x40पूर्ण,
	अणु0x52, 0xb0पूर्ण,
	अणु0x51, 0x83पूर्ण,
	अणु0x21, 0xbbपूर्ण,
	अणु0x22, 0x10पूर्ण,
	अणु0x23, 0x03पूर्ण,
	अणु0x35, 0x38पूर्ण,
	अणु0x20, 0x90पूर्ण,
	अणु0x28, 0x30पूर्ण,
	अणु0x73, 0xe1पूर्ण,
	अणु0x6c, 0x00पूर्ण,
	अणु0x6d, 0x80पूर्ण,
	अणु0x6e, 0x00पूर्ण,
	अणु0x70, 0x04पूर्ण,
	अणु0x71, 0x00पूर्ण,
	अणु0x8d, 0x04पूर्ण,
	अणु0x64, 0x00पूर्ण,
	अणु0x65, 0x00पूर्ण,
	अणु0x66, 0x00पूर्ण,
	अणु0x67, 0x00पूर्ण,
	अणु0x68, 0x00पूर्ण,
	अणु0x69, 0x00पूर्ण,
	अणु0x6a, 0x00पूर्ण,
	अणु0x6b, 0x00पूर्ण,
	अणु0x71, 0x94पूर्ण,
	अणु0x74, 0x20पूर्ण,
	अणु0x80, 0x09पूर्ण,
	अणु0x85, 0xc0पूर्ण,
पूर्ण;

अटल व्योम reg_w_i(काष्ठा gspca_dev *gspca_dev, u16 reg, u8 val)
अणु
	काष्ठा usb_device *udev = gspca_dev->dev;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	gspca_dev->usb_buf[0] = val;
	ret = usb_control_msg(udev,
			      usb_sndctrlpipe(udev, 0),
			      0x01,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0x00, reg, gspca_dev->usb_buf, 1, CTRL_TIMEOUT);
	अगर (ret < 0) अणु
		pr_err("reg_w failed %d\n", ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev, u16 reg, u8 val)
अणु
	gspca_dbg(gspca_dev, D_USBO, "reg_w [%04x] = %02x\n", reg, val);
	reg_w_i(gspca_dev, reg, val);
पूर्ण

अटल u8 reg_r(काष्ठा gspca_dev *gspca_dev, u16 reg)
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
	gspca_dbg(gspca_dev, D_USBI, "reg_r [%04x] -> %02x\n",
		  reg, gspca_dev->usb_buf[0]);
	अगर (ret < 0) अणु
		pr_err("reg_r err %d\n", ret);
		gspca_dev->usb_err = ret;
		वापस 0;
	पूर्ण
	वापस gspca_dev->usb_buf[0];
पूर्ण

अटल पूर्णांक sccb_check_status(काष्ठा gspca_dev *gspca_dev)
अणु
	u8 data;
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		msleep(20);
		data = reg_r(gspca_dev, OV534_REG_STATUS);

		चयन (data) अणु
		हाल 0x00:
			वापस 1;
		हाल 0x04:
			वापस 0;
		हाल 0x03:
			अवरोध;
		शेष:
			gspca_dbg(gspca_dev, D_USBI|D_USBO,
				  "sccb status 0x%02x, attempt %d/5\n",
				  data, i + 1);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sccb_ग_लिखो(काष्ठा gspca_dev *gspca_dev, u8 reg, u8 val)
अणु
	gspca_dbg(gspca_dev, D_USBO, "sccb_write [%02x] = %02x\n", reg, val);
	reg_w_i(gspca_dev, OV534_REG_SUBADDR, reg);
	reg_w_i(gspca_dev, OV534_REG_WRITE, val);
	reg_w_i(gspca_dev, OV534_REG_OPERATION, OV534_OP_WRITE_3);

	अगर (!sccb_check_status(gspca_dev))
		pr_err("sccb_write failed\n");
पूर्ण

अटल u8 sccb_पढ़ो(काष्ठा gspca_dev *gspca_dev, u16 reg)
अणु
	reg_w(gspca_dev, OV534_REG_SUBADDR, reg);
	reg_w(gspca_dev, OV534_REG_OPERATION, OV534_OP_WRITE_2);
	अगर (!sccb_check_status(gspca_dev))
		pr_err("sccb_read failed 1\n");

	reg_w(gspca_dev, OV534_REG_OPERATION, OV534_OP_READ_2);
	अगर (!sccb_check_status(gspca_dev))
		pr_err("sccb_read failed 2\n");

	वापस reg_r(gspca_dev, OV534_REG_READ);
पूर्ण

/* output a bridge sequence (reg - val) */
अटल व्योम reg_w_array(काष्ठा gspca_dev *gspca_dev,
			स्थिर u8 (*data)[2], पूर्णांक len)
अणु
	जबतक (--len >= 0) अणु
		reg_w(gspca_dev, (*data)[0], (*data)[1]);
		data++;
	पूर्ण
पूर्ण

/* output a sensor sequence (reg - val) */
अटल व्योम sccb_w_array(काष्ठा gspca_dev *gspca_dev,
			स्थिर u8 (*data)[2], पूर्णांक len)
अणु
	जबतक (--len >= 0) अणु
		अगर ((*data)[0] != 0xff) अणु
			sccb_ग_लिखो(gspca_dev, (*data)[0], (*data)[1]);
		पूर्ण अन्यथा अणु
			sccb_पढ़ो(gspca_dev, (*data)[1]);
			sccb_ग_लिखो(gspca_dev, 0xff, 0x00);
		पूर्ण
		data++;
	पूर्ण
पूर्ण

/* Two bits control LED: 0x21 bit 7 and 0x23 bit 7.
 * (direction and output)? */
अटल व्योम set_led(काष्ठा gspca_dev *gspca_dev, पूर्णांक status)
अणु
	u8 data;

	gspca_dbg(gspca_dev, D_CONF, "led status: %d\n", status);

	data = reg_r(gspca_dev, 0x21);
	data |= 0x80;
	reg_w(gspca_dev, 0x21, data);

	data = reg_r(gspca_dev, 0x23);
	अगर (status)
		data |= 0x80;
	अन्यथा
		data &= ~0x80;

	reg_w(gspca_dev, 0x23, data);

	अगर (!status) अणु
		data = reg_r(gspca_dev, 0x21);
		data &= ~0x80;
		reg_w(gspca_dev, 0x21, data);
	पूर्ण
पूर्ण

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 brightness)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 val;
	s8 sval;

	अगर (sd->sensor == SENSOR_OV562x) अणु
		sval = brightness;
		val = 0x76;
		val += sval;
		sccb_ग_लिखो(gspca_dev, 0x24, val);
		val = 0x6a;
		val += sval;
		sccb_ग_लिखो(gspca_dev, 0x25, val);
		अगर (sval < -40)
			val = 0x71;
		अन्यथा अगर (sval < 20)
			val = 0x94;
		अन्यथा
			val = 0xe6;
		sccb_ग_लिखो(gspca_dev, 0x26, val);
	पूर्ण अन्यथा अणु
		val = brightness;
		अगर (val < 8)
			val = 15 - val;		/* f .. 8 */
		अन्यथा
			val = val - 8;		/* 0 .. 7 */
		sccb_ग_लिखो(gspca_dev, 0x55,	/* brtn - brightness adjusपंचांगent */
				0x0f | (val << 4));
	पूर्ण
पूर्ण

अटल व्योम setcontrast(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	sccb_ग_लिखो(gspca_dev, 0x56,	/* cnst1 - contrast 1 ctrl coeff */
			val << 4);
पूर्ण

अटल व्योम setस्वतःgain(काष्ठा gspca_dev *gspca_dev, s32 स्वतःgain)
अणु
	u8 val;

/*fixme: should adjust agc/awb/aec by dअगरferent controls */
	val = sccb_पढ़ो(gspca_dev, 0x13);		/* com8 */
	sccb_ग_लिखो(gspca_dev, 0xff, 0x00);
	अगर (स्वतःgain)
		val |= 0x05;		/* agc & aec */
	अन्यथा
		val &= 0xfa;
	sccb_ग_लिखो(gspca_dev, 0x13, val);
पूर्ण

अटल व्योम setexposure(काष्ठा gspca_dev *gspca_dev, s32 exposure)
अणु
	अटल स्थिर u8 expo[4] = अणु0x00, 0x25, 0x38, 0x5eपूर्ण;
	u8 val;

	sccb_ग_लिखो(gspca_dev, 0x10, expo[exposure]);	/* aec[9:2] */

	val = sccb_पढ़ो(gspca_dev, 0x13);		/* com8 */
	sccb_ग_लिखो(gspca_dev, 0xff, 0x00);
	sccb_ग_लिखो(gspca_dev, 0x13, val);

	val = sccb_पढ़ो(gspca_dev, 0xa1);		/* aech */
	sccb_ग_लिखो(gspca_dev, 0xff, 0x00);
	sccb_ग_लिखो(gspca_dev, 0xa1, val & 0xe0);	/* aec[15:10] = 0 */
पूर्ण

अटल व्योम setsharpness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	अगर (val < 0) अणु				/* स्वतः */
		val = sccb_पढ़ो(gspca_dev, 0x42);	/* com17 */
		sccb_ग_लिखो(gspca_dev, 0xff, 0x00);
		sccb_ग_लिखो(gspca_dev, 0x42, val | 0x40);
				/* Edge enhancement strength स्वतः adjust */
		वापस;
	पूर्ण
	अगर (val != 0)
		val = 1 << (val - 1);
	sccb_ग_लिखो(gspca_dev, 0x3f,	/* edge - edge enhance. factor */
			val);
	val = sccb_पढ़ो(gspca_dev, 0x42);		/* com17 */
	sccb_ग_लिखो(gspca_dev, 0xff, 0x00);
	sccb_ग_लिखो(gspca_dev, 0x42, val & 0xbf);
पूर्ण

अटल व्योम setsatur(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	u8 val1, val2, val3;
	अटल स्थिर u8 matrix[5][2] = अणु
		अणु0x14, 0x38पूर्ण,
		अणु0x1e, 0x54पूर्ण,
		अणु0x28, 0x70पूर्ण,
		अणु0x32, 0x8cपूर्ण,
		अणु0x48, 0x90पूर्ण
	पूर्ण;

	val1 = matrix[val][0];
	val2 = matrix[val][1];
	val3 = val1 + val2;
	sccb_ग_लिखो(gspca_dev, 0x4f, val3);	/* matrix coeff */
	sccb_ग_लिखो(gspca_dev, 0x50, val3);
	sccb_ग_लिखो(gspca_dev, 0x51, 0x00);
	sccb_ग_लिखो(gspca_dev, 0x52, val1);
	sccb_ग_लिखो(gspca_dev, 0x53, val2);
	sccb_ग_लिखो(gspca_dev, 0x54, val3);
	sccb_ग_लिखो(gspca_dev, 0x58, 0x1a);	/* mtxs - coeff signs */

	val1 = sccb_पढ़ो(gspca_dev, 0x41);	/* com16 */
	sccb_ग_लिखो(gspca_dev, 0xff, 0x00);
	sccb_ग_लिखो(gspca_dev, 0x41, val1);
पूर्ण

अटल व्योम setlightfreq(काष्ठा gspca_dev *gspca_dev, s32 freq)
अणु
	u8 val;

	val = sccb_पढ़ो(gspca_dev, 0x13);		/* com8 */
	sccb_ग_लिखो(gspca_dev, 0xff, 0x00);
	अगर (freq == 0) अणु
		sccb_ग_लिखो(gspca_dev, 0x13, val & 0xdf);
		वापस;
	पूर्ण
	sccb_ग_लिखो(gspca_dev, 0x13, val | 0x20);

	val = sccb_पढ़ो(gspca_dev, 0x42);		/* com17 */
	sccb_ग_लिखो(gspca_dev, 0xff, 0x00);
	अगर (freq == 1)
		val |= 0x01;
	अन्यथा
		val &= 0xfe;
	sccb_ग_लिखो(gspca_dev, 0x42, val);
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u16 sensor_id;

	/* reset bridge */
	reg_w(gspca_dev, 0xe7, 0x3a);
	reg_w(gspca_dev, 0xe0, 0x08);
	msleep(100);

	/* initialize the sensor address */
	reg_w(gspca_dev, OV534_REG_ADDRESS, 0x60);

	/* reset sensor */
	sccb_ग_लिखो(gspca_dev, 0x12, 0x80);
	msleep(10);

	/* probe the sensor */
	sccb_पढ़ो(gspca_dev, 0x0a);
	sensor_id = sccb_पढ़ो(gspca_dev, 0x0a) << 8;
	sccb_पढ़ो(gspca_dev, 0x0b);
	sensor_id |= sccb_पढ़ो(gspca_dev, 0x0b);
	gspca_dbg(gspca_dev, D_PROBE, "Sensor ID: %04x\n", sensor_id);

	/* initialize */
	अगर ((sensor_id & 0xfff0) == 0x9650) अणु
		sd->sensor = SENSOR_OV965x;

		gspca_dev->cam.cam_mode = ov965x_mode;
		gspca_dev->cam.nmodes = ARRAY_SIZE(ov965x_mode);

		reg_w_array(gspca_dev, bridge_init,
				ARRAY_SIZE(bridge_init));
		sccb_w_array(gspca_dev, ov965x_init,
				ARRAY_SIZE(ov965x_init));
		reg_w_array(gspca_dev, bridge_init_2,
				ARRAY_SIZE(bridge_init_2));
		sccb_w_array(gspca_dev, ov965x_init_2,
				ARRAY_SIZE(ov965x_init_2));
		reg_w(gspca_dev, 0xe0, 0x00);
		reg_w(gspca_dev, 0xe0, 0x01);
		set_led(gspca_dev, 0);
		reg_w(gspca_dev, 0xe0, 0x00);
	पूर्ण अन्यथा अगर ((sensor_id & 0xfff0) == 0x9710) अणु
		स्थिर अक्षर *p;
		पूर्णांक l;

		sd->sensor = SENSOR_OV971x;

		gspca_dev->cam.cam_mode = ov971x_mode;
		gspca_dev->cam.nmodes = ARRAY_SIZE(ov971x_mode);

		gspca_dev->cam.bulk = 1;
		gspca_dev->cam.bulk_size = 16384;
		gspca_dev->cam.bulk_nurbs = 2;

		sccb_w_array(gspca_dev, ov971x_init,
				ARRAY_SIZE(ov971x_init));

		/* set video क्रमmat on bridge processor */
		/* access bridge processor's video क्रमmat रेजिस्टरs at: 0x00 */
		reg_w(gspca_dev, 0x1c, 0x00);
		/*set रेजिस्टर: 0x00 is 'RAW8', 0x40 is 'YUV422' (YUYV?)*/
		reg_w(gspca_dev, 0x1d, 0x00);

		/* Will W. specअगरic stuff
		 * set VSYNC to
		 *	output (0x1f) अगर first webcam
		 *	input (0x17) अगर 2nd or 3rd webcam */
		p = video_device_node_name(&gspca_dev->vdev);
		l = म_माप(p) - 1;
		अगर (p[l] == '0')
			reg_w(gspca_dev, 0x56, 0x1f);
		अन्यथा
			reg_w(gspca_dev, 0x56, 0x17);
	पूर्ण अन्यथा अगर ((sensor_id & 0xfff0) == 0x5620) अणु
		sd->sensor = SENSOR_OV562x;
		gspca_dev->cam.cam_mode = ov562x_mode;
		gspca_dev->cam.nmodes = ARRAY_SIZE(ov562x_mode);

		reg_w_array(gspca_dev, ov562x_init,
				ARRAY_SIZE(ov562x_init));
		sccb_w_array(gspca_dev, ov562x_init_2,
				ARRAY_SIZE(ov562x_init_2));
		reg_w(gspca_dev, 0xe0, 0x00);
	पूर्ण अन्यथा अगर ((sensor_id & 0xfff0) == 0x3610) अणु
		sd->sensor = SENSOR_OV361x;
		gspca_dev->cam.cam_mode = ov361x_mode;
		gspca_dev->cam.nmodes = ARRAY_SIZE(ov361x_mode);
		reg_w(gspca_dev, 0xe7, 0x3a);
		reg_w(gspca_dev, 0xf1, 0x60);
		sccb_ग_लिखो(gspca_dev, 0x12, 0x80);
	पूर्ण अन्यथा अणु
		pr_err("Unknown sensor %04x", sensor_id);
		वापस -EINVAL;
	पूर्ण

	वापस gspca_dev->usb_err;
पूर्ण

अटल पूर्णांक sd_start_ov361x(काष्ठा gspca_dev *gspca_dev)
अणु
	sccb_ग_लिखो(gspca_dev, 0x12, 0x80);
	msleep(20);
	चयन (gspca_dev->curr_mode % (ov361x_last)) अणु
	हाल ov361x_2048:
		reg_w_array(gspca_dev, ov361x_bridge_start_2048,
			    ARRAY_SIZE(ov361x_bridge_start_2048));
		sccb_w_array(gspca_dev, ov361x_start_2048,
			     ARRAY_SIZE(ov361x_start_2048));
		अवरोध;
	हाल ov361x_1600:
		reg_w_array(gspca_dev, ov361x_bridge_start_1600,
			    ARRAY_SIZE(ov361x_bridge_start_1600));
		sccb_w_array(gspca_dev, ov361x_start_1600,
			     ARRAY_SIZE(ov361x_start_1600));
		अवरोध;
	हाल ov361x_1024:
		reg_w_array(gspca_dev, ov361x_bridge_start_1024,
			    ARRAY_SIZE(ov361x_bridge_start_1024));
		sccb_w_array(gspca_dev, ov361x_start_1024,
			     ARRAY_SIZE(ov361x_start_1024));
		अवरोध;
	हाल ov361x_640:
		reg_w_array(gspca_dev, ov361x_bridge_start_640,
			    ARRAY_SIZE(ov361x_bridge_start_640));
		sccb_w_array(gspca_dev, ov361x_start_640,
			     ARRAY_SIZE(ov361x_start_640));
		अवरोध;
	हाल ov361x_320:
		reg_w_array(gspca_dev, ov361x_bridge_start_320,
			    ARRAY_SIZE(ov361x_bridge_start_320));
		sccb_w_array(gspca_dev, ov361x_start_320,
			     ARRAY_SIZE(ov361x_start_320));
		अवरोध;
	हाल ov361x_160:
		reg_w_array(gspca_dev, ov361x_bridge_start_160,
			    ARRAY_SIZE(ov361x_bridge_start_160));
		sccb_w_array(gspca_dev, ov361x_start_160,
			     ARRAY_SIZE(ov361x_start_160));
		अवरोध;
	पूर्ण
	reg_w(gspca_dev, 0xe0, 0x00); /* start transfer */

	वापस gspca_dev->usb_err;
पूर्ण

अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_OV971x)
		वापस gspca_dev->usb_err;
	अगर (sd->sensor == SENSOR_OV562x)
		वापस gspca_dev->usb_err;
	अगर (sd->sensor == SENSOR_OV361x)
		वापस sd_start_ov361x(gspca_dev);

	चयन (gspca_dev->curr_mode) अणु
	हाल QVGA_MODE:			/* 320x240 */
		sccb_w_array(gspca_dev, ov965x_start_1_vga,
				ARRAY_SIZE(ov965x_start_1_vga));
		reg_w_array(gspca_dev, bridge_start_qvga,
				ARRAY_SIZE(bridge_start_qvga));
		sccb_w_array(gspca_dev, ov965x_start_2_qvga,
				ARRAY_SIZE(ov965x_start_2_qvga));
		अवरोध;
	हाल VGA_MODE:			/* 640x480 */
		sccb_w_array(gspca_dev, ov965x_start_1_vga,
				ARRAY_SIZE(ov965x_start_1_vga));
		reg_w_array(gspca_dev, bridge_start_vga,
				ARRAY_SIZE(bridge_start_vga));
		sccb_w_array(gspca_dev, ov965x_start_2_vga,
				ARRAY_SIZE(ov965x_start_2_vga));
		अवरोध;
	हाल SVGA_MODE:			/* 800x600 */
		sccb_w_array(gspca_dev, ov965x_start_1_svga,
				ARRAY_SIZE(ov965x_start_1_svga));
		reg_w_array(gspca_dev, bridge_start_svga,
				ARRAY_SIZE(bridge_start_svga));
		sccb_w_array(gspca_dev, ov965x_start_2_svga,
				ARRAY_SIZE(ov965x_start_2_svga));
		अवरोध;
	हाल XGA_MODE:			/* 1024x768 */
		sccb_w_array(gspca_dev, ov965x_start_1_xga,
				ARRAY_SIZE(ov965x_start_1_xga));
		reg_w_array(gspca_dev, bridge_start_xga,
				ARRAY_SIZE(bridge_start_xga));
		sccb_w_array(gspca_dev, ov965x_start_2_svga,
				ARRAY_SIZE(ov965x_start_2_svga));
		अवरोध;
	शेष:
/*	हाल SXGA_MODE:			 * 1280x1024 */
		sccb_w_array(gspca_dev, ov965x_start_1_sxga,
				ARRAY_SIZE(ov965x_start_1_sxga));
		reg_w_array(gspca_dev, bridge_start_sxga,
				ARRAY_SIZE(bridge_start_sxga));
		sccb_w_array(gspca_dev, ov965x_start_2_sxga,
				ARRAY_SIZE(ov965x_start_2_sxga));
		अवरोध;
	पूर्ण

	reg_w(gspca_dev, 0xe0, 0x00);
	reg_w(gspca_dev, 0xe0, 0x00);
	set_led(gspca_dev, 1);
	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	अगर (((काष्ठा sd *)gspca_dev)->sensor == SENSOR_OV361x) अणु
		reg_w(gspca_dev, 0xe0, 0x01); /* stop transfer */
		/* reg_w(gspca_dev, 0x31, 0x09); */
		वापस;
	पूर्ण
	reg_w(gspca_dev, 0xe0, 0x01);
	set_led(gspca_dev, 0);
	reg_w(gspca_dev, 0xe0, 0x00);
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
	u8 this_fid;
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
		this_fid = data[1] & UVC_STREAM_FID;

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

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		setbrightness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		setcontrast(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		setsatur(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		setlightfreq(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		setsharpness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		अगर (ctrl->is_new)
			setस्वतःgain(gspca_dev, ctrl->val);
		अगर (!ctrl->val && gspca_dev->exposure->is_new)
			setexposure(gspca_dev, gspca_dev->exposure->val);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	अगर (sd->sensor == SENSOR_OV971x)
		वापस 0;
	अगर (sd->sensor == SENSOR_OV361x)
		वापस 0;
	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 7);
	अगर (sd->sensor == SENSOR_OV562x) अणु
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, -90, 90, 1, 0);
	पूर्ण अन्यथा अणु
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 15, 1, 7);
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 15, 1, 3);
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SATURATION, 0, 4, 1, 2);
		/* -1 = स्वतः */
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SHARPNESS, -1, 4, 1, -1);
		gspca_dev->स्वतःgain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
		gspca_dev->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 3, 1, 0);
		v4l2_ctrl_new_std_menu(hdl, &sd_ctrl_ops,
			V4L2_CID_POWER_LINE_FREQUENCY,
			V4L2_CID_POWER_LINE_FREQUENCY_60HZ, 0, 0);
		v4l2_ctrl_स्वतः_cluster(3, &gspca_dev->स्वतःgain, 0, false);
	पूर्ण

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	वापस 0;
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
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x05a9, 0x8065)पूर्ण,
	अणुUSB_DEVICE(0x06f8, 0x3003)पूर्ण,
	अणुUSB_DEVICE(0x05a9, 0x1550)पूर्ण,
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
