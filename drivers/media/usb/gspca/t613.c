<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * T613 subdriver
 *
 * Copyright (C) 2010 Jean-Francois Moine (http://moinejf.मुक्त.fr)
 *
 *Notes: * t613  + tas5130A
 *	* Focus to light करो not balance well as in win.
 *	  Quality in win is not good, but its kinda better.
 *	 * Fix some "extraneous bytes", most of apps will show the image anyway
 *	 * Gamma table, is there, but its really करोing something?
 *	 * 7~8 Fps, its ok, max on win its 10.
 *			Costantino Leandro
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "t613"

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश "gspca.h"

MODULE_AUTHOR("Leandro Costantino <le_costantino@pixartargentina.com.ar>");
MODULE_DESCRIPTION("GSPCA/T613 (JPEG Compliance) USB Camera Driver");
MODULE_LICENSE("GPL");

काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */
	काष्ठा v4l2_ctrl *freq;
	काष्ठा अणु /* awb / color gains control cluster */
		काष्ठा v4l2_ctrl *awb;
		काष्ठा v4l2_ctrl *gain;
		काष्ठा v4l2_ctrl *red_balance;
		काष्ठा v4l2_ctrl *blue_balance;
	पूर्ण;

	u8 sensor;
	u8 button_pressed;
पूर्ण;
क्रमागत sensors अणु
	SENSOR_OM6802,
	SENSOR_OTHER,
	SENSOR_TAS5130A,
	SENSOR_LT168G,		/* must verअगरy अगर this is the actual model */
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode_t16[] = अणु
	अणु160, 120, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 160 * 120 * 4 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 4पूर्ण,
#अगर 0 /* HDG: broken with my test cam, so lets disable it */
	अणु176, 144, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 3पूर्ण,
#पूर्ण_अगर
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 2पूर्ण,
#अगर 0 /* HDG: broken with my test cam, so lets disable it */
	अणु352, 288, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
#पूर्ण_अगर
	अणु640, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
पूर्ण;

/* sensor specअगरic data */
काष्ठा additional_sensor_data अणु
	स्थिर u8 n3[6];
	स्थिर u8 *n4, n4sz;
	स्थिर u8 reg80, reg8e;
	स्थिर u8 nset8[6];
	स्थिर u8 data1[10];
	स्थिर u8 data2[9];
	स्थिर u8 data3[9];
	स्थिर u8 data5[6];
	स्थिर u8 stream[4];
पूर्ण;

अटल स्थिर u8 n4_om6802[] = अणु
	0x09, 0x01, 0x12, 0x04, 0x66, 0x8a, 0x80, 0x3c,
	0x81, 0x22, 0x84, 0x50, 0x8a, 0x78, 0x8b, 0x68,
	0x8c, 0x88, 0x8e, 0x33, 0x8f, 0x24, 0xaa, 0xb1,
	0xa2, 0x60, 0xa5, 0x30, 0xa6, 0x3a, 0xa8, 0xe8,
	0xae, 0x05, 0xb1, 0x00, 0xbb, 0x04, 0xbc, 0x48,
	0xbe, 0x36, 0xc6, 0x88, 0xe9, 0x00, 0xc5, 0xc0,
	0x65, 0x0a, 0xbb, 0x86, 0xaf, 0x58, 0xb0, 0x68,
	0x87, 0x40, 0x89, 0x2b, 0x8d, 0xff, 0x83, 0x40,
	0xac, 0x84, 0xad, 0x86, 0xaf, 0x46
पूर्ण;
अटल स्थिर u8 n4_other[] = अणु
	0x66, 0x00, 0x7f, 0x00, 0x80, 0xac, 0x81, 0x69,
	0x84, 0x40, 0x85, 0x70, 0x86, 0x20, 0x8a, 0x68,
	0x8b, 0x58, 0x8c, 0x88, 0x8d, 0xff, 0x8e, 0xb8,
	0x8f, 0x28, 0xa2, 0x60, 0xa5, 0x40, 0xa8, 0xa8,
	0xac, 0x84, 0xad, 0x84, 0xae, 0x24, 0xaf, 0x56,
	0xb0, 0x68, 0xb1, 0x00, 0xb2, 0x88, 0xbb, 0xc5,
	0xbc, 0x4a, 0xbe, 0x36, 0xc2, 0x88, 0xc5, 0xc0,
	0xc6, 0xda, 0xe9, 0x26, 0xeb, 0x00
पूर्ण;
अटल स्थिर u8 n4_tas5130a[] = अणु
	0x80, 0x3c, 0x81, 0x68, 0x83, 0xa0, 0x84, 0x20,
	0x8a, 0x68, 0x8b, 0x58, 0x8c, 0x88, 0x8e, 0xb4,
	0x8f, 0x24, 0xa1, 0xb1, 0xa2, 0x30, 0xa5, 0x10,
	0xa6, 0x4a, 0xae, 0x03, 0xb1, 0x44, 0xb2, 0x08,
	0xb7, 0x06, 0xb9, 0xe7, 0xbb, 0xc4, 0xbc, 0x4a,
	0xbe, 0x36, 0xbf, 0xff, 0xc2, 0x88, 0xc5, 0xc8,
	0xc6, 0xda
पूर्ण;
अटल स्थिर u8 n4_lt168g[] = अणु
	0x66, 0x01, 0x7f, 0x00, 0x80, 0x7c, 0x81, 0x28,
	0x83, 0x44, 0x84, 0x20, 0x86, 0x20, 0x8a, 0x70,
	0x8b, 0x58, 0x8c, 0x88, 0x8d, 0xa0, 0x8e, 0xb3,
	0x8f, 0x24, 0xa1, 0xb0, 0xa2, 0x38, 0xa5, 0x20,
	0xa6, 0x4a, 0xa8, 0xe8, 0xaf, 0x38, 0xb0, 0x68,
	0xb1, 0x44, 0xb2, 0x88, 0xbb, 0x86, 0xbd, 0x40,
	0xbe, 0x26, 0xc1, 0x05, 0xc2, 0x88, 0xc5, 0xc0,
	0xda, 0x8e, 0xdb, 0xca, 0xdc, 0xa8, 0xdd, 0x8c,
	0xde, 0x44, 0xdf, 0x0c, 0xe9, 0x80
पूर्ण;

अटल स्थिर काष्ठा additional_sensor_data sensor_data[] = अणु
[SENSOR_OM6802] = अणु
	.n3 =
		अणु0x61, 0x68, 0x65, 0x0a, 0x60, 0x04पूर्ण,
	.n4 = n4_om6802,
	.n4sz = माप n4_om6802,
	.reg80 = 0x3c,
	.reg8e = 0x33,
	.nset8 = अणु0xa8, 0xf0, 0xc6, 0x88, 0xc0, 0x00पूर्ण,
	.data1 =
		अणु0xc2, 0x28, 0x0f, 0x22, 0xcd, 0x27, 0x2c, 0x06,
		 0xb3, 0xfcपूर्ण,
	.data2 =
		अणु0x80, 0xff, 0xff, 0x80, 0xff, 0xff, 0x80, 0xff,
		 0xffपूर्ण,
	.data3 =
		अणु0x80, 0xff, 0xff, 0x80, 0xff, 0xff, 0x80, 0xff,
		 0xffपूर्ण,
	.data5 =	/* this could be हटाओd later */
		अणु0x0c, 0x03, 0xab, 0x13, 0x81, 0x23पूर्ण,
	.stream =
		अणु0x0b, 0x04, 0x0a, 0x78पूर्ण,
    पूर्ण,
[SENSOR_OTHER] = अणु
	.n3 =
		अणु0x61, 0xc2, 0x65, 0x88, 0x60, 0x00पूर्ण,
	.n4 = n4_other,
	.n4sz = माप n4_other,
	.reg80 = 0xac,
	.reg8e = 0xb8,
	.nset8 = अणु0xa8, 0xa8, 0xc6, 0xda, 0xc0, 0x00पूर्ण,
	.data1 =
		अणु0xc1, 0x48, 0x04, 0x1b, 0xca, 0x2e, 0x33, 0x3a,
		 0xe8, 0xfcपूर्ण,
	.data2 =
		अणु0x4e, 0x9c, 0xec, 0x40, 0x80, 0xc0, 0x48, 0x96,
		 0xd9पूर्ण,
	.data3 =
		अणु0x4e, 0x9c, 0xec, 0x40, 0x80, 0xc0, 0x48, 0x96,
		 0xd9पूर्ण,
	.data5 =
		अणु0x0c, 0x03, 0xab, 0x29, 0x81, 0x69पूर्ण,
	.stream =
		अणु0x0b, 0x04, 0x0a, 0x00पूर्ण,
    पूर्ण,
[SENSOR_TAS5130A] = अणु
	.n3 =
		अणु0x61, 0xc2, 0x65, 0x0d, 0x60, 0x08पूर्ण,
	.n4 = n4_tas5130a,
	.n4sz = माप n4_tas5130a,
	.reg80 = 0x3c,
	.reg8e = 0xb4,
	.nset8 = अणु0xa8, 0xf0, 0xc6, 0xda, 0xc0, 0x00पूर्ण,
	.data1 =
		अणु0xbb, 0x28, 0x10, 0x10, 0xbb, 0x28, 0x1e, 0x27,
		 0xc8, 0xfcपूर्ण,
	.data2 =
		अणु0x60, 0xa8, 0xe0, 0x60, 0xa8, 0xe0, 0x60, 0xa8,
		 0xe0पूर्ण,
	.data3 =
		अणु0x60, 0xa8, 0xe0, 0x60, 0xa8, 0xe0, 0x60, 0xa8,
		 0xe0पूर्ण,
	.data5 =
		अणु0x0c, 0x03, 0xab, 0x10, 0x81, 0x20पूर्ण,
	.stream =
		अणु0x0b, 0x04, 0x0a, 0x40पूर्ण,
    पूर्ण,
[SENSOR_LT168G] = अणु
	.n3 = अणु0x61, 0xc2, 0x65, 0x68, 0x60, 0x00पूर्ण,
	.n4 = n4_lt168g,
	.n4sz = माप n4_lt168g,
	.reg80 = 0x7c,
	.reg8e = 0xb3,
	.nset8 = अणु0xa8, 0xf0, 0xc6, 0xba, 0xc0, 0x00पूर्ण,
	.data1 = अणु0xc0, 0x38, 0x08, 0x10, 0xc0, 0x30, 0x10, 0x40,
		 0xb0, 0xf4पूर्ण,
	.data2 = अणु0x40, 0x80, 0xc0, 0x50, 0xa0, 0xf0, 0x53, 0xa6,
		 0xffपूर्ण,
	.data3 = अणु0x40, 0x80, 0xc0, 0x50, 0xa0, 0xf0, 0x53, 0xa6,
		 0xffपूर्ण,
	.data5 = अणु0x0c, 0x03, 0xab, 0x4b, 0x81, 0x2bपूर्ण,
	.stream = अणु0x0b, 0x04, 0x0a, 0x28पूर्ण,
    पूर्ण,
पूर्ण;

#घोषणा MAX_EFFECTS 7
अटल स्थिर u8 effects_table[MAX_EFFECTS][6] = अणु
	अणु0xa8, 0xe8, 0xc6, 0xd2, 0xc0, 0x00पूर्ण,	/* Normal */
	अणु0xa8, 0xc8, 0xc6, 0x52, 0xc0, 0x04पूर्ण,	/* Repujar */
	अणु0xa8, 0xe8, 0xc6, 0xd2, 0xc0, 0x20पूर्ण,	/* Monochrome */
	अणु0xa8, 0xe8, 0xc6, 0xd2, 0xc0, 0x80पूर्ण,	/* Sepia */
	अणु0xa8, 0xc8, 0xc6, 0x52, 0xc0, 0x02पूर्ण,	/* Croquis */
	अणु0xa8, 0xc8, 0xc6, 0xd2, 0xc0, 0x10पूर्ण,	/* Sun Effect */
	अणु0xa8, 0xc8, 0xc6, 0xd2, 0xc0, 0x40पूर्ण,	/* Negative */
पूर्ण;

#घोषणा GAMMA_MAX (15)
अटल स्थिर u8 gamma_table[GAMMA_MAX+1][17] = अणु
/* gamma table from cam1690.ini */
	अणु0x00, 0x00, 0x01, 0x04, 0x08, 0x0e, 0x16, 0x21,	/* 0 */
	 0x2e, 0x3d, 0x50, 0x65, 0x7d, 0x99, 0xb8, 0xdb,
	 0xffपूर्ण,
	अणु0x00, 0x01, 0x03, 0x08, 0x0e, 0x16, 0x21, 0x2d,	/* 1 */
	 0x3c, 0x4d, 0x60, 0x75, 0x8d, 0xa6, 0xc2, 0xe1,
	 0xffपूर्ण,
	अणु0x00, 0x01, 0x05, 0x0b, 0x12, 0x1c, 0x28, 0x35,	/* 2 */
	 0x45, 0x56, 0x69, 0x7e, 0x95, 0xad, 0xc7, 0xe3,
	 0xffपूर्ण,
	अणु0x00, 0x02, 0x07, 0x0f, 0x18, 0x24, 0x30, 0x3f,	/* 3 */
	 0x4f, 0x61, 0x73, 0x88, 0x9d, 0xb4, 0xcd, 0xe6,
	 0xffपूर्ण,
	अणु0x00, 0x04, 0x0b, 0x15, 0x20, 0x2d, 0x3b, 0x4a,	/* 4 */
	 0x5b, 0x6c, 0x7f, 0x92, 0xa7, 0xbc, 0xd2, 0xe9,
	 0xffपूर्ण,
	अणु0x00, 0x07, 0x11, 0x15, 0x20, 0x2d, 0x48, 0x58,	/* 5 */
	 0x68, 0x79, 0x8b, 0x9d, 0xb0, 0xc4, 0xd7, 0xec,
	 0xffपूर्ण,
	अणु0x00, 0x0c, 0x1a, 0x29, 0x38, 0x47, 0x57, 0x67,	/* 6 */
	 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee,
	 0xffपूर्ण,
	अणु0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70,	/* 7 */
	 0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0,
	 0xffपूर्ण,
	अणु0x00, 0x15, 0x27, 0x38, 0x49, 0x59, 0x69, 0x79,	/* 8 */
	 0x88, 0x97, 0xa7, 0xb6, 0xc4, 0xd3, 0xe2, 0xf0,
	 0xffपूर्ण,
	अणु0x00, 0x1c, 0x30, 0x43, 0x54, 0x65, 0x75, 0x84,	/* 9 */
	 0x93, 0xa1, 0xb0, 0xbd, 0xca, 0xd8, 0xe5, 0xf2,
	 0xffपूर्ण,
	अणु0x00, 0x24, 0x3b, 0x4f, 0x60, 0x70, 0x80, 0x8e,	/* 10 */
	 0x9c, 0xaa, 0xb7, 0xc4, 0xd0, 0xdc, 0xe8, 0xf3,
	 0xffपूर्ण,
	अणु0x00, 0x2a, 0x3c, 0x5d, 0x6e, 0x7e, 0x8d, 0x9b,	/* 11 */
	 0xa8, 0xb4, 0xc0, 0xcb, 0xd6, 0xe1, 0xeb, 0xf5,
	 0xffपूर्ण,
	अणु0x00, 0x3f, 0x5a, 0x6e, 0x7f, 0x8e, 0x9c, 0xa8,	/* 12 */
	 0xb4, 0xbf, 0xc9, 0xd3, 0xdc, 0xe5, 0xee, 0xf6,
	 0xffपूर्ण,
	अणु0x00, 0x54, 0x6f, 0x83, 0x93, 0xa0, 0xad, 0xb7,	/* 13 */
	 0xc2, 0xcb, 0xd4, 0xdc, 0xe4, 0xeb, 0xf2, 0xf9,
	 0xffपूर्ण,
	अणु0x00, 0x6e, 0x88, 0x9a, 0xa8, 0xb3, 0xbd, 0xc6,	/* 14 */
	 0xcf, 0xd6, 0xdd, 0xe3, 0xe9, 0xef, 0xf4, 0xfa,
	 0xffपूर्ण,
	अणु0x00, 0x93, 0xa8, 0xb7, 0xc1, 0xca, 0xd2, 0xd8,	/* 15 */
	 0xde, 0xe3, 0xe8, 0xed, 0xf1, 0xf5, 0xf8, 0xfc,
	 0xffपूर्ण
पूर्ण;

अटल स्थिर u8 tas5130a_sensor_init[][8] = अणु
	अणु0x62, 0x08, 0x63, 0x70, 0x64, 0x1d, 0x60, 0x09पूर्ण,
	अणु0x62, 0x20, 0x63, 0x01, 0x64, 0x02, 0x60, 0x09पूर्ण,
	अणु0x62, 0x07, 0x63, 0x03, 0x64, 0x00, 0x60, 0x09पूर्ण,
पूर्ण;

अटल u8 sensor_reset[] = अणु0x61, 0x68, 0x62, 0xff, 0x60, 0x07पूर्ण;

/* पढ़ो 1 byte */
अटल u8 reg_r(काष्ठा gspca_dev *gspca_dev,
		   u16 index)
अणु
	usb_control_msg(gspca_dev->dev,
			usb_rcvctrlpipe(gspca_dev->dev, 0),
			0,		/* request */
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,		/* value */
			index,
			gspca_dev->usb_buf, 1, 500);
	वापस gspca_dev->usb_buf[0];
पूर्ण

अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev,
		  u16 index)
अणु
	usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, index,
			शून्य, 0, 500);
पूर्ण

अटल व्योम reg_w_buf(काष्ठा gspca_dev *gspca_dev,
		  स्थिर u8 *buffer, u16 len)
अणु
	अगर (len <= USB_BUF_SZ) अणु
		स_नकल(gspca_dev->usb_buf, buffer, len);
		usb_control_msg(gspca_dev->dev,
				usb_sndctrlpipe(gspca_dev->dev, 0),
				0,
			   USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0x01, 0,
				gspca_dev->usb_buf, len, 500);
	पूर्ण अन्यथा अणु
		u8 *पंचांगpbuf;

		पंचांगpbuf = kmemdup(buffer, len, GFP_KERNEL);
		अगर (!पंचांगpbuf) अणु
			pr_err("Out of memory\n");
			वापस;
		पूर्ण
		usb_control_msg(gspca_dev->dev,
				usb_sndctrlpipe(gspca_dev->dev, 0),
				0,
			   USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0x01, 0,
				पंचांगpbuf, len, 500);
		kमुक्त(पंचांगpbuf);
	पूर्ण
पूर्ण

/* ग_लिखो values to consecutive रेजिस्टरs */
अटल व्योम reg_w_ixbuf(काष्ठा gspca_dev *gspca_dev,
			u8 reg,
			स्थिर u8 *buffer, u16 len)
अणु
	पूर्णांक i;
	u8 *p, *पंचांगpbuf;

	अगर (len * 2 <= USB_BUF_SZ) अणु
		p = पंचांगpbuf = gspca_dev->usb_buf;
	पूर्ण अन्यथा अणु
		p = पंचांगpbuf = kदो_स्मृति_array(len, 2, GFP_KERNEL);
		अगर (!पंचांगpbuf) अणु
			pr_err("Out of memory\n");
			वापस;
		पूर्ण
	पूर्ण
	i = len;
	जबतक (--i >= 0) अणु
		*p++ = reg++;
		*p++ = *buffer++;
	पूर्ण
	usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0x01, 0,
			पंचांगpbuf, len * 2, 500);
	अगर (len * 2 > USB_BUF_SZ)
		kमुक्त(पंचांगpbuf);
पूर्ण

अटल व्योम om6802_sensor_init(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i;
	स्थिर u8 *p;
	u8 byte;
	u8 val[6] = अणु0x62, 0, 0x64, 0, 0x60, 0x05पूर्ण;
	अटल स्थिर u8 sensor_init[] = अणु
		0xdf, 0x6d,
		0xdd, 0x18,
		0x5a, 0xe0,
		0x5c, 0x07,
		0x5d, 0xb0,
		0x5e, 0x1e,
		0x60, 0x71,
		0xef, 0x00,
		0xe9, 0x00,
		0xea, 0x00,
		0x90, 0x24,
		0x91, 0xb2,
		0x82, 0x32,
		0xfd, 0x41,
		0x00			/* table end */
	पूर्ण;

	reg_w_buf(gspca_dev, sensor_reset, माप sensor_reset);
	msleep(100);
	i = 4;
	जबतक (--i > 0) अणु
		byte = reg_r(gspca_dev, 0x0060);
		अगर (!(byte & 0x01))
			अवरोध;
		msleep(100);
	पूर्ण
	byte = reg_r(gspca_dev, 0x0063);
	अगर (byte != 0x17) अणु
		pr_err("Bad sensor reset %02x\n", byte);
		/* जारी? */
	पूर्ण

	p = sensor_init;
	जबतक (*p != 0) अणु
		val[1] = *p++;
		val[3] = *p++;
		अगर (*p == 0)
			reg_w(gspca_dev, 0x3c80);
		reg_w_buf(gspca_dev, val, माप val);
		i = 4;
		जबतक (--i >= 0) अणु
			msleep(15);
			byte = reg_r(gspca_dev, 0x60);
			अगर (!(byte & 0x01))
				अवरोध;
		पूर्ण
	पूर्ण
	msleep(15);
	reg_w(gspca_dev, 0x3c80);
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा cam *cam  = &gspca_dev->cam;

	cam->cam_mode = vga_mode_t16;
	cam->nmodes = ARRAY_SIZE(vga_mode_t16);

	वापस 0;
पूर्ण

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 brightness)
अणु
	u8 set6[4] = अणु 0x8f, 0x24, 0xc3, 0x00 पूर्ण;

	अगर (brightness < 7) अणु
		set6[1] = 0x26;
		set6[3] = 0x70 - brightness * 0x10;
	पूर्ण अन्यथा अणु
		set6[3] = 0x00 + ((brightness - 7) * 0x10);
	पूर्ण

	reg_w_buf(gspca_dev, set6, माप set6);
पूर्ण

अटल व्योम setcontrast(काष्ठा gspca_dev *gspca_dev, s32 contrast)
अणु
	u16 reg_to_ग_लिखो;

	अगर (contrast < 7)
		reg_to_ग_लिखो = 0x8ea9 - contrast * 0x200;
	अन्यथा
		reg_to_ग_लिखो = 0x00a9 + (contrast - 7) * 0x200;

	reg_w(gspca_dev, reg_to_ग_लिखो);
पूर्ण

अटल व्योम setcolors(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	u16 reg_to_ग_लिखो;

	reg_to_ग_लिखो = 0x80bb + val * 0x100;	/* was 0xc0 */
	reg_w(gspca_dev, reg_to_ग_लिखो);
पूर्ण

अटल व्योम setgamma(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	gspca_dbg(gspca_dev, D_CONF, "Gamma: %d\n", val);
	reg_w_ixbuf(gspca_dev, 0x90,
		gamma_table[val], माप gamma_table[0]);
पूर्ण

अटल व्योम setawb_n_RGB(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 all_gain_reg[8] = अणु
		0x87, 0x00, 0x88, 0x00, 0x89, 0x00, 0x80, 0x00 पूर्ण;
	s32 red_gain, blue_gain, green_gain;

	green_gain = sd->gain->val;

	red_gain = green_gain + sd->red_balance->val;
	अगर (red_gain > 0x40)
		red_gain = 0x40;
	अन्यथा अगर (red_gain < 0x10)
		red_gain = 0x10;

	blue_gain = green_gain + sd->blue_balance->val;
	अगर (blue_gain > 0x40)
		blue_gain = 0x40;
	अन्यथा अगर (blue_gain < 0x10)
		blue_gain = 0x10;

	all_gain_reg[1] = red_gain;
	all_gain_reg[3] = blue_gain;
	all_gain_reg[5] = green_gain;
	all_gain_reg[7] = sensor_data[sd->sensor].reg80;
	अगर (!sd->awb->val)
		all_gain_reg[7] &= ~0x04; /* AWB off */

	reg_w_buf(gspca_dev, all_gain_reg, माप all_gain_reg);
पूर्ण

अटल व्योम setsharpness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	u16 reg_to_ग_लिखो;

	reg_to_ग_लिखो = 0x0aa6 + 0x1000 * val;

	reg_w(gspca_dev, reg_to_ग_लिखो);
पूर्ण

अटल व्योम setfreq(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 reg66;
	u8 freq[4] = अणु 0x66, 0x00, 0xa8, 0xe8 पूर्ण;

	चयन (sd->sensor) अणु
	हाल SENSOR_LT168G:
		अगर (val != 0)
			freq[3] = 0xa8;
		reg66 = 0x41;
		अवरोध;
	हाल SENSOR_OM6802:
		reg66 = 0xca;
		अवरोध;
	शेष:
		reg66 = 0x40;
		अवरोध;
	पूर्ण
	चयन (val) अणु
	हाल 0:				/* no flicker */
		freq[3] = 0xf0;
		अवरोध;
	हाल 2:				/* 60Hz */
		reg66 &= ~0x40;
		अवरोध;
	पूर्ण
	freq[1] = reg66;

	reg_w_buf(gspca_dev, freq, माप freq);
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	/* some of this रेजिस्टरs are not really needed, because
	 * they are overridden by setbrigthness, setcontrast, etc.,
	 * but won't hurt anyway, and can help someone with similar webcam
	 * to see the initial parameters.*/
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	स्थिर काष्ठा additional_sensor_data *sensor;
	पूर्णांक i;
	u16 sensor_id;
	u8 test_byte = 0;

	अटल स्थिर u8 पढ़ो_indexs[] =
		अणु 0x0a, 0x0b, 0x66, 0x80, 0x81, 0x8e, 0x8f, 0xa5,
		  0xa6, 0xa8, 0xbb, 0xbc, 0xc6, 0x00 पूर्ण;
	अटल स्थिर u8 n1[] =
			अणु0x08, 0x03, 0x09, 0x03, 0x12, 0x04पूर्ण;
	अटल स्थिर u8 n2[] =
			अणु0x08, 0x00पूर्ण;

	sensor_id = (reg_r(gspca_dev, 0x06) << 8)
			| reg_r(gspca_dev, 0x07);
	चयन (sensor_id & 0xff0f) अणु
	हाल 0x0801:
		gspca_dbg(gspca_dev, D_PROBE, "sensor tas5130a\n");
		sd->sensor = SENSOR_TAS5130A;
		अवरोध;
	हाल 0x0802:
		gspca_dbg(gspca_dev, D_PROBE, "sensor lt168g\n");
		sd->sensor = SENSOR_LT168G;
		अवरोध;
	हाल 0x0803:
		gspca_dbg(gspca_dev, D_PROBE, "sensor 'other'\n");
		sd->sensor = SENSOR_OTHER;
		अवरोध;
	हाल 0x0807:
		gspca_dbg(gspca_dev, D_PROBE, "sensor om6802\n");
		sd->sensor = SENSOR_OM6802;
		अवरोध;
	शेष:
		pr_err("unknown sensor %04x\n", sensor_id);
		वापस -EINVAL;
	पूर्ण

	अगर (sd->sensor == SENSOR_OM6802) अणु
		reg_w_buf(gspca_dev, n1, माप n1);
		i = 5;
		जबतक (--i >= 0) अणु
			reg_w_buf(gspca_dev, sensor_reset, माप sensor_reset);
			test_byte = reg_r(gspca_dev, 0x0063);
			msleep(100);
			अगर (test_byte == 0x17)
				अवरोध;		/* OK */
		पूर्ण
		अगर (i < 0) अणु
			pr_err("Bad sensor reset %02x\n", test_byte);
			वापस -EIO;
		पूर्ण
		reg_w_buf(gspca_dev, n2, माप n2);
	पूर्ण

	i = 0;
	जबतक (पढ़ो_indexs[i] != 0x00) अणु
		test_byte = reg_r(gspca_dev, पढ़ो_indexs[i]);
		gspca_dbg(gspca_dev, D_STREAM, "Reg 0x%02x = 0x%02x\n",
			  पढ़ो_indexs[i], test_byte);
		i++;
	पूर्ण

	sensor = &sensor_data[sd->sensor];
	reg_w_buf(gspca_dev, sensor->n3, माप sensor->n3);
	reg_w_buf(gspca_dev, sensor->n4, sensor->n4sz);

	अगर (sd->sensor == SENSOR_LT168G) अणु
		test_byte = reg_r(gspca_dev, 0x80);
		gspca_dbg(gspca_dev, D_STREAM, "Reg 0x%02x = 0x%02x\n", 0x80,
			  test_byte);
		reg_w(gspca_dev, 0x6c80);
	पूर्ण

	reg_w_ixbuf(gspca_dev, 0xd0, sensor->data1, माप sensor->data1);
	reg_w_ixbuf(gspca_dev, 0xc7, sensor->data2, माप sensor->data2);
	reg_w_ixbuf(gspca_dev, 0xe0, sensor->data3, माप sensor->data3);

	reg_w(gspca_dev, (sensor->reg80 << 8) + 0x80);
	reg_w(gspca_dev, (sensor->reg80 << 8) + 0x80);
	reg_w(gspca_dev, (sensor->reg8e << 8) + 0x8e);
	reg_w(gspca_dev, (0x20 << 8) + 0x87);
	reg_w(gspca_dev, (0x20 << 8) + 0x88);
	reg_w(gspca_dev, (0x20 << 8) + 0x89);

	reg_w_buf(gspca_dev, sensor->data5, माप sensor->data5);
	reg_w_buf(gspca_dev, sensor->nset8, माप sensor->nset8);
	reg_w_buf(gspca_dev, sensor->stream, माप sensor->stream);

	अगर (sd->sensor == SENSOR_LT168G) अणु
		test_byte = reg_r(gspca_dev, 0x80);
		gspca_dbg(gspca_dev, D_STREAM, "Reg 0x%02x = 0x%02x\n", 0x80,
			  test_byte);
		reg_w(gspca_dev, 0x6c80);
	पूर्ण

	reg_w_ixbuf(gspca_dev, 0xd0, sensor->data1, माप sensor->data1);
	reg_w_ixbuf(gspca_dev, 0xc7, sensor->data2, माप sensor->data2);
	reg_w_ixbuf(gspca_dev, 0xe0, sensor->data3, माप sensor->data3);

	वापस 0;
पूर्ण

अटल व्योम seपंचांगirror(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	u8 hflipcmd[8] =
		अणु0x62, 0x07, 0x63, 0x03, 0x64, 0x00, 0x60, 0x09पूर्ण;

	अगर (val)
		hflipcmd[3] = 0x01;

	reg_w_buf(gspca_dev, hflipcmd, माप hflipcmd);
पूर्ण

अटल व्योम seteffect(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	पूर्णांक idx = 0;

	चयन (val) अणु
	हाल V4L2_COLORFX_NONE:
		अवरोध;
	हाल V4L2_COLORFX_BW:
		idx = 2;
		अवरोध;
	हाल V4L2_COLORFX_SEPIA:
		idx = 3;
		अवरोध;
	हाल V4L2_COLORFX_SKETCH:
		idx = 4;
		अवरोध;
	हाल V4L2_COLORFX_NEGATIVE:
		idx = 6;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	reg_w_buf(gspca_dev, effects_table[idx],
				माप effects_table[0]);

	अगर (val == V4L2_COLORFX_SKETCH)
		reg_w(gspca_dev, 0x4aa6);
	अन्यथा
		reg_w(gspca_dev, 0xfaa6);
पूर्ण

/* Is this really needed?
 * i added some module parameters क्रम test with some users */
अटल व्योम poll_sensor(काष्ठा gspca_dev *gspca_dev)
अणु
	अटल स्थिर u8 poll1[] =
		अणु0x67, 0x05, 0x68, 0x81, 0x69, 0x80, 0x6a, 0x82,
		 0x6b, 0x68, 0x6c, 0x69, 0x72, 0xd9, 0x73, 0x34,
		 0x74, 0x32, 0x75, 0x92, 0x76, 0x00, 0x09, 0x01,
		 0x60, 0x14पूर्ण;
	अटल स्थिर u8 poll2[] =
		अणु0x67, 0x02, 0x68, 0x71, 0x69, 0x72, 0x72, 0xa9,
		 0x73, 0x02, 0x73, 0x02, 0x60, 0x14पूर्ण;
	अटल स्थिर u8 noise03[] =	/* (some dअगरferences / ms-drv) */
		अणु0xa6, 0x0a, 0xea, 0xcf, 0xbe, 0x26, 0xb1, 0x5f,
		 0xa1, 0xb1, 0xda, 0x6b, 0xdb, 0x98, 0xdf, 0x0c,
		 0xc2, 0x80, 0xc3, 0x10पूर्ण;

	gspca_dbg(gspca_dev, D_STREAM, "[Sensor requires polling]\n");
	reg_w_buf(gspca_dev, poll1, माप poll1);
	reg_w_buf(gspca_dev, poll2, माप poll2);
	reg_w_buf(gspca_dev, noise03, माप noise03);
पूर्ण

अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	स्थिर काष्ठा additional_sensor_data *sensor;
	पूर्णांक i, mode;
	u8 t2[] = अणु 0x07, 0x00, 0x0d, 0x60, 0x0e, 0x80 पूर्ण;
	अटल स्थिर u8 t3[] =
		अणु 0x07, 0x00, 0x88, 0x02, 0x06, 0x00, 0xe7, 0x01 पूर्ण;

	mode = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	चयन (mode) अणु
	हाल 0:		/* 640x480 (0x00) */
		अवरोध;
	हाल 1:		/* 352x288 */
		t2[1] = 0x40;
		अवरोध;
	हाल 2:		/* 320x240 */
		t2[1] = 0x10;
		अवरोध;
	हाल 3:		/* 176x144 */
		t2[1] = 0x50;
		अवरोध;
	शेष:
/*	हाल 4:		 * 160x120 */
		t2[1] = 0x20;
		अवरोध;
	पूर्ण

	चयन (sd->sensor) अणु
	हाल SENSOR_OM6802:
		om6802_sensor_init(gspca_dev);
		अवरोध;
	हाल SENSOR_TAS5130A:
		i = 0;
		क्रम (;;) अणु
			reg_w_buf(gspca_dev, tas5130a_sensor_init[i],
					 माप tas5130a_sensor_init[0]);
			अगर (i >= ARRAY_SIZE(tas5130a_sensor_init) - 1)
				अवरोध;
			i++;
		पूर्ण
		reg_w(gspca_dev, 0x3c80);
		/* just in हाल and to keep sync with logs (क्रम mine) */
		reg_w_buf(gspca_dev, tas5130a_sensor_init[i],
				 माप tas5130a_sensor_init[0]);
		reg_w(gspca_dev, 0x3c80);
		अवरोध;
	पूर्ण
	sensor = &sensor_data[sd->sensor];
	setfreq(gspca_dev, v4l2_ctrl_g_ctrl(sd->freq));
	reg_r(gspca_dev, 0x0012);
	reg_w_buf(gspca_dev, t2, माप t2);
	reg_w_ixbuf(gspca_dev, 0xb3, t3, माप t3);
	reg_w(gspca_dev, 0x0013);
	msleep(15);
	reg_w_buf(gspca_dev, sensor->stream, माप sensor->stream);
	reg_w_buf(gspca_dev, sensor->stream, माप sensor->stream);

	अगर (sd->sensor == SENSOR_OM6802)
		poll_sensor(gspca_dev);

	वापस 0;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	reg_w_buf(gspca_dev, sensor_data[sd->sensor].stream,
			माप sensor_data[sd->sensor].stream);
	reg_w_buf(gspca_dev, sensor_data[sd->sensor].stream,
			माप sensor_data[sd->sensor].stream);
	अगर (sd->sensor == SENSOR_OM6802) अणु
		msleep(20);
		reg_w(gspca_dev, 0x0309);
	पूर्ण
#अगर IS_ENABLED(CONFIG_INPUT)
	/* If the last button state is pressed, release it now! */
	अगर (sd->button_pressed) अणु
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
		input_sync(gspca_dev->input_dev);
		sd->button_pressed = 0;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd __maybe_unused = (काष्ठा sd *) gspca_dev;
	पूर्णांक pkt_type;

	अगर (data[0] == 0x5a) अणु
#अगर IS_ENABLED(CONFIG_INPUT)
		अगर (len > 20) अणु
			u8 state = (data[20] & 0x80) ? 1 : 0;
			अगर (sd->button_pressed != state) अणु
				input_report_key(gspca_dev->input_dev,
						 KEY_CAMERA, state);
				input_sync(gspca_dev->input_dev);
				sd->button_pressed = state;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		/* Control Packet, after this came the header again,
		 * but extra bytes came in the packet beक्रमe this,
		 * someबार an खातापूर्ण arrives, someबार not... */
		वापस;
	पूर्ण
	data += 2;
	len -= 2;
	अगर (data[0] == 0xff && data[1] == 0xd8)
		pkt_type = FIRST_PACKET;
	अन्यथा अगर (data[len - 2] == 0xff && data[len - 1] == 0xd9)
		pkt_type = LAST_PACKET;
	अन्यथा
		pkt_type = INTER_PACKET;
	gspca_frame_add(gspca_dev, pkt_type, data, len);
पूर्ण

अटल पूर्णांक sd_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	s32 red_gain, blue_gain, green_gain;

	gspca_dev->usb_err = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		red_gain = reg_r(gspca_dev, 0x0087);
		अगर (red_gain > 0x40)
			red_gain = 0x40;
		अन्यथा अगर (red_gain < 0x10)
			red_gain = 0x10;

		blue_gain = reg_r(gspca_dev, 0x0088);
		अगर (blue_gain > 0x40)
			blue_gain = 0x40;
		अन्यथा अगर (blue_gain < 0x10)
			blue_gain = 0x10;

		green_gain = reg_r(gspca_dev, 0x0089);
		अगर (green_gain > 0x40)
			green_gain = 0x40;
		अन्यथा अगर (green_gain < 0x10)
			green_gain = 0x10;

		sd->gain->val = green_gain;
		sd->red_balance->val = red_gain - green_gain;
		sd->blue_balance->val = blue_gain - green_gain;
		अवरोध;
	पूर्ण
	वापस 0;
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
		setcolors(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_GAMMA:
		setgamma(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		seपंचांगirror(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		setsharpness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		setfreq(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_BACKLIGHT_COMPENSATION:
		reg_w(gspca_dev, ctrl->val ? 0xf48e : 0xb48e);
		अवरोध;
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		setawb_n_RGB(gspca_dev);
		अवरोध;
	हाल V4L2_CID_COLORFX:
		seteffect(gspca_dev, ctrl->val);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.g_अस्थिर_ctrl = sd_g_अस्थिर_ctrl,
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 12);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 14, 1, 8);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 0x0d, 1, 7);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SATURATION, 0, 0xf, 1, 5);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAMMA, 0, GAMMA_MAX, 1, 10);
	/* Activate lowlight, some apps करोn't bring up the
	   backlight_compensation control) */
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BACKLIGHT_COMPENSATION, 0, 1, 1, 1);
	अगर (sd->sensor == SENSOR_TAS5130A)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_HFLIP, 0, 1, 1, 0);
	sd->awb = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);
	sd->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAIN, 0x10, 0x40, 1, 0x20);
	sd->blue_balance = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BLUE_BALANCE, -0x30, 0x30, 1, 0);
	sd->red_balance = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_RED_BALANCE, -0x30, 0x30, 1, 0);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SHARPNESS, 0, 15, 1, 6);
	v4l2_ctrl_new_std_menu(hdl, &sd_ctrl_ops,
			V4L2_CID_COLORFX, V4L2_COLORFX_SKETCH,
			~((1 << V4L2_COLORFX_NONE) |
			  (1 << V4L2_COLORFX_BW) |
			  (1 << V4L2_COLORFX_SEPIA) |
			  (1 << V4L2_COLORFX_SKETCH) |
			  (1 << V4L2_COLORFX_NEGATIVE)),
			V4L2_COLORFX_NONE);
	sd->freq = v4l2_ctrl_new_std_menu(hdl, &sd_ctrl_ops,
			V4L2_CID_POWER_LINE_FREQUENCY,
			V4L2_CID_POWER_LINE_FREQUENCY_60HZ, 1,
			V4L2_CID_POWER_LINE_FREQUENCY_50HZ);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण

	v4l2_ctrl_स्वतः_cluster(4, &sd->awb, 0, true);

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
	.pkt_scan = sd_pkt_scan,
#अगर IS_ENABLED(CONFIG_INPUT)
	.other_input = 1,
#पूर्ण_अगर
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x17a1, 0x0128)पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, device_table);

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		    स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id, &sd_desc, माप(काष्ठा sd),
			       THIS_MODULE);
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
