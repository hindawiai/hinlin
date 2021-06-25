<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Sunplus spca561 subdriver
 *
 * Copyright (C) 2004 Michel Xhaard mxhaard@magic.fr
 *
 * V4L2 by Jean-Francois Moine <http://moinejf.मुक्त.fr>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "spca561"

#समावेश <linux/input.h>
#समावेश "gspca.h"

MODULE_AUTHOR("Michel Xhaard <mxhaard@users.sourceforge.net>");
MODULE_DESCRIPTION("GSPCA/SPCA561 USB Camera Driver");
MODULE_LICENSE("GPL");

#घोषणा EXPOSURE_MAX (2047 + 325)

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	काष्ठा अणु /* hue/contrast control cluster */
		काष्ठा v4l2_ctrl *contrast;
		काष्ठा v4l2_ctrl *hue;
	पूर्ण;
	काष्ठा v4l2_ctrl *स्वतःgain;

#घोषणा EXPO12A_DEF 3
	__u8 expo12a;		/* expo/gain? क्रम rev 12a */

	__u8 chip_revision;
#घोषणा Rev012A 0
#घोषणा Rev072A 1

	चिन्हित अक्षर ag_cnt;
#घोषणा AG_CNT_START 13
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat sअगर_012a_mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 160 * 120,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 3पूर्ण,
	अणु176, 144, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 2पूर्ण,
	अणु320, 240, V4L2_PIX_FMT_SPCA561, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 4 / 8,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_SPCA561, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288 * 4 / 8,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat sअगर_072a_mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 160 * 120,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 3पूर्ण,
	अणु176, 144, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 2पूर्ण,
	अणु320, 240, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
पूर्ण;

/*
 * Initialization data
 * I'm not very sure how to split initialization from खोलो data
 * chunks. For now, we'll consider everything as initialization
 */
/* Frame packet header offsets क्रम the spca561 */
#घोषणा SPCA561_OFFSET_SNAP 1
#घोषणा SPCA561_OFFSET_TYPE 2
#घोषणा SPCA561_OFFSET_COMPRESS 3
#घोषणा SPCA561_OFFSET_FRAMSEQ   4
#घोषणा SPCA561_OFFSET_GPIO 5
#घोषणा SPCA561_OFFSET_USBBUFF 6
#घोषणा SPCA561_OFFSET_WIN2GRAVE 7
#घोषणा SPCA561_OFFSET_WIN2RAVE 8
#घोषणा SPCA561_OFFSET_WIN2BAVE 9
#घोषणा SPCA561_OFFSET_WIN2GBAVE 10
#घोषणा SPCA561_OFFSET_WIN1GRAVE 11
#घोषणा SPCA561_OFFSET_WIN1RAVE 12
#घोषणा SPCA561_OFFSET_WIN1BAVE 13
#घोषणा SPCA561_OFFSET_WIN1GBAVE 14
#घोषणा SPCA561_OFFSET_FREQ 15
#घोषणा SPCA561_OFFSET_VSYNC 16
#घोषणा SPCA561_INDEX_I2C_BASE 0x8800
#घोषणा SPCA561_SNAPBIT 0x20
#घोषणा SPCA561_SNAPCTRL 0x40

अटल स्थिर u16 rev72a_reset[][2] = अणु
	अणु0x0000, 0x8114पूर्ण,	/* Software GPIO output data */
	अणु0x0001, 0x8114पूर्ण,	/* Software GPIO output data */
	अणु0x0000, 0x8112पूर्ण,	/* Some kind of reset */
	अणुपूर्ण
पूर्ण;
अटल स्थिर __u16 rev72a_init_data1[][2] = अणु
	अणु0x0003, 0x8701पूर्ण,	/* PCLK घड़ी delay adjusपंचांगent */
	अणु0x0001, 0x8703पूर्ण,	/* HSYNC from cmos inverted */
	अणु0x0011, 0x8118पूर्ण,	/* Enable and conf sensor */
	अणु0x0001, 0x8118पूर्ण,	/* Conf sensor */
	अणु0x0092, 0x8804पूर्ण,	/* I know nothing about these */
	अणु0x0010, 0x8802पूर्ण,	/* 0x88xx रेजिस्टरs, so I won't */
	अणुपूर्ण
पूर्ण;
अटल स्थिर u16 rev72a_init_sensor1[][2] = अणु
	अणु0x0001, 0x000dपूर्ण,
	अणु0x0002, 0x0018पूर्ण,
	अणु0x0004, 0x0165पूर्ण,
	अणु0x0005, 0x0021पूर्ण,
	अणु0x0007, 0x00aaपूर्ण,
	अणु0x0020, 0x1504पूर्ण,
	अणु0x0039, 0x0002पूर्ण,
	अणु0x0035, 0x0010पूर्ण,
	अणु0x0009, 0x1049पूर्ण,
	अणु0x0028, 0x000bपूर्ण,
	अणु0x003b, 0x000fपूर्ण,
	अणु0x003c, 0x0000पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर __u16 rev72a_init_data2[][2] = अणु
	अणु0x0018, 0x8601पूर्ण,	/* Pixel/line selection क्रम color separation */
	अणु0x0000, 0x8602पूर्ण,	/* Optical black level क्रम user setting */
	अणु0x0060, 0x8604पूर्ण,	/* Optical black horizontal offset */
	अणु0x0002, 0x8605पूर्ण,	/* Optical black vertical offset */
	अणु0x0000, 0x8603पूर्ण,	/* Non-स्वतःmatic optical black level */
	अणु0x0002, 0x865bपूर्ण,	/* Horizontal offset क्रम valid pixels */
	अणु0x0000, 0x865fपूर्ण,	/* Vertical valid pixels winकरोw (x2) */
	अणु0x00b0, 0x865dपूर्ण,	/* Horizontal valid pixels winकरोw (x2) */
	अणु0x0090, 0x865eपूर्ण,	/* Vertical valid lines winकरोw (x2) */
	अणु0x00e0, 0x8406पूर्ण,	/* Memory buffer threshold */
	अणु0x0000, 0x8660पूर्ण,	/* Compensation memory stuff */
	अणु0x0002, 0x8201पूर्ण,	/* Output address क्रम r/w serial EEPROM */
	अणु0x0008, 0x8200पूर्ण,	/* Clear valid bit क्रम serial EEPROM */
	अणु0x0001, 0x8200पूर्ण,	/* OprMode to be executed by hardware */
/* from ms-win */
	अणु0x0000, 0x8611पूर्ण,	/* R offset क्रम white balance */
	अणु0x00fd, 0x8612पूर्ण,	/* Gr offset क्रम white balance */
	अणु0x0003, 0x8613पूर्ण,	/* B offset क्रम white balance */
	अणु0x0000, 0x8614पूर्ण,	/* Gb offset क्रम white balance */
/* from ms-win */
	अणु0x0035, 0x8651पूर्ण,	/* R gain क्रम white balance */
	अणु0x0040, 0x8652पूर्ण,	/* Gr gain क्रम white balance */
	अणु0x005f, 0x8653पूर्ण,	/* B gain क्रम white balance */
	अणु0x0040, 0x8654पूर्ण,	/* Gb gain क्रम white balance */
	अणु0x0002, 0x8502पूर्ण,	/* Maximum average bit rate stuff */
	अणु0x0011, 0x8802पूर्ण,

	अणु0x0087, 0x8700पूर्ण,	/* Set master घड़ी (96Mhz????) */
	अणु0x0081, 0x8702पूर्ण,	/* Master घड़ी output enable */

	अणु0x0000, 0x8500पूर्ण,	/* Set image type (352x288 no compression) */
	/* Originally was 0x0010 (352x288 compression) */

	अणु0x0002, 0x865bपूर्ण,	/* Horizontal offset क्रम valid pixels */
	अणु0x0003, 0x865cपूर्ण,	/* Vertical offset क्रम valid lines */
	अणुपूर्ण
पूर्ण;
अटल स्थिर u16 rev72a_init_sensor2[][2] = अणु
	अणु0x0003, 0x0121पूर्ण,
	अणु0x0004, 0x0165पूर्ण,
	अणु0x0005, 0x002fपूर्ण,	/* blanking control column */
	अणु0x0006, 0x0000पूर्ण,	/* blanking mode row*/
	अणु0x000a, 0x0002पूर्ण,
	अणु0x0009, 0x1061पूर्ण,	/* setexposure बार && pixel घड़ी
				 * 0001 0 | 000 0110 0001 */
	अणु0x0035, 0x0014पूर्ण,
	अणुपूर्ण
पूर्ण;

/******************** QC Express etch2 stuff ********************/
अटल स्थिर __u16 Pb100_1map8300[][2] = अणु
	/* reg, value */
	अणु0x8320, 0x3304पूर्ण,

	अणु0x8303, 0x0125पूर्ण,	/* image area */
	अणु0x8304, 0x0169पूर्ण,
	अणु0x8328, 0x000bपूर्ण,
	अणु0x833c, 0x0001पूर्ण,		/*fixme: win:07*/

	अणु0x832f, 0x1904पूर्ण,		/*fixme: was 0419*/
	अणु0x8307, 0x00aaपूर्ण,
	अणु0x8301, 0x0003पूर्ण,
	अणु0x8302, 0x000eपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर __u16 Pb100_2map8300[][2] = अणु
	/* reg, value */
	अणु0x8339, 0x0000पूर्ण,
	अणु0x8307, 0x00aaपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर __u16 spca561_161rev12A_data1[][2] = अणु
	अणु0x29, 0x8118पूर्ण,		/* Control रेजिस्टर (various enable bits) */
	अणु0x08, 0x8114पूर्ण,		/* GPIO: Led off */
	अणु0x0e, 0x8112पूर्ण,		/* 0x0e stream off 0x3e stream on */
	अणु0x00, 0x8102पूर्ण,		/* white balance - new */
	अणु0x92, 0x8804पूर्ण,
	अणु0x04, 0x8802पूर्ण,		/* winकरोws uses 08 */
	अणुपूर्ण
पूर्ण;
अटल स्थिर __u16 spca561_161rev12A_data2[][2] = अणु
	अणु0x21, 0x8118पूर्ण,
	अणु0x10, 0x8500पूर्ण,
	अणु0x07, 0x8601पूर्ण,
	अणु0x07, 0x8602पूर्ण,
	अणु0x04, 0x8501पूर्ण,

	अणु0x07, 0x8201पूर्ण,		/* winकरोws uses 02 */
	अणु0x08, 0x8200पूर्ण,
	अणु0x01, 0x8200पूर्ण,

	अणु0x90, 0x8604पूर्ण,
	अणु0x00, 0x8605पूर्ण,
	अणु0xb0, 0x8603पूर्ण,

	/* sensor gains */
	अणु0x07, 0x8601पूर्ण,		/* white balance - new */
	अणु0x07, 0x8602पूर्ण,		/* white balance - new */
	अणु0x00, 0x8610पूर्ण,		/* *red */
	अणु0x00, 0x8611पूर्ण,		/* 3f   *green */
	अणु0x00, 0x8612पूर्ण,		/* green *blue */
	अणु0x00, 0x8613पूर्ण,		/* blue *green */
	अणु0x43, 0x8614पूर्ण,		/* green *red - white balance - was 0x35 */
	अणु0x40, 0x8615पूर्ण,		/* 40   *green - white balance - was 0x35 */
	अणु0x71, 0x8616पूर्ण,		/* 7a   *blue - white balance - was 0x35 */
	अणु0x40, 0x8617पूर्ण,		/* 40   *green - white balance - was 0x35 */

	अणु0x0c, 0x8620पूर्ण,		/* 0c */
	अणु0xc8, 0x8631पूर्ण,		/* c8 */
	अणु0xc8, 0x8634पूर्ण,		/* c8 */
	अणु0x23, 0x8635पूर्ण,		/* 23 */
	अणु0x1f, 0x8636पूर्ण,		/* 1f */
	अणु0xdd, 0x8637पूर्ण,		/* dd */
	अणु0xe1, 0x8638पूर्ण,		/* e1 */
	अणु0x1d, 0x8639पूर्ण,		/* 1d */
	अणु0x21, 0x863aपूर्ण,		/* 21 */
	अणु0xe3, 0x863bपूर्ण,		/* e3 */
	अणु0xdf, 0x863cपूर्ण,		/* df */
	अणु0xf0, 0x8505पूर्ण,
	अणु0x32, 0x850aपूर्ण,
/*	अणु0x99, 0x8700पूर्ण,		 * - white balance - new (हटाओd) */
	/* HDG we used to करो this in stop0, making the init state and the state
	   after a start / stop dअगरferent, so करो this here instead. */
	अणु0x29, 0x8118पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम reg_w_val(काष्ठा gspca_dev *gspca_dev, __u16 index, __u8 value)
अणु
	पूर्णांक ret;
	काष्ठा usb_device *dev = gspca_dev->dev;

	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			      0,		/* request */
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      value, index, शून्य, 0, 500);
	gspca_dbg(gspca_dev, D_USBO, "reg write: 0x%02x:0x%02x\n",
		  index, value);
	अगर (ret < 0)
		pr_err("reg write: error %d\n", ret);
पूर्ण

अटल व्योम ग_लिखो_vector(काष्ठा gspca_dev *gspca_dev,
			स्थिर __u16 data[][2])
अणु
	पूर्णांक i;

	i = 0;
	जबतक (data[i][1] != 0) अणु
		reg_w_val(gspca_dev, data[i][1], data[i][0]);
		i++;
	पूर्ण
पूर्ण

/* पढ़ो 'len' bytes to gspca_dev->usb_buf */
अटल व्योम reg_r(काष्ठा gspca_dev *gspca_dev,
		  __u16 index, __u16 length)
अणु
	usb_control_msg(gspca_dev->dev,
			usb_rcvctrlpipe(gspca_dev->dev, 0),
			0,			/* request */
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,			/* value */
			index, gspca_dev->usb_buf, length, 500);
पूर्ण

/* ग_लिखो 'len' bytes from gspca_dev->usb_buf */
अटल व्योम reg_w_buf(काष्ठा gspca_dev *gspca_dev,
		      __u16 index, __u16 len)
अणु
	usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0,			/* request */
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,			/* value */
			index, gspca_dev->usb_buf, len, 500);
पूर्ण

अटल व्योम i2c_ग_लिखो(काष्ठा gspca_dev *gspca_dev, __u16 value, __u16 reg)
अणु
	पूर्णांक retry = 60;

	reg_w_val(gspca_dev, 0x8801, reg);
	reg_w_val(gspca_dev, 0x8805, value);
	reg_w_val(gspca_dev, 0x8800, value >> 8);
	करो अणु
		reg_r(gspca_dev, 0x8803, 1);
		अगर (!gspca_dev->usb_buf[0])
			वापस;
		msleep(10);
	पूर्ण जबतक (--retry);
पूर्ण

अटल पूर्णांक i2c_पढ़ो(काष्ठा gspca_dev *gspca_dev, __u16 reg, __u8 mode)
अणु
	पूर्णांक retry = 60;
	__u8 value;

	reg_w_val(gspca_dev, 0x8804, 0x92);
	reg_w_val(gspca_dev, 0x8801, reg);
	reg_w_val(gspca_dev, 0x8802, mode | 0x01);
	करो अणु
		reg_r(gspca_dev, 0x8803, 1);
		अगर (!gspca_dev->usb_buf[0]) अणु
			reg_r(gspca_dev, 0x8800, 1);
			value = gspca_dev->usb_buf[0];
			reg_r(gspca_dev, 0x8805, 1);
			वापस ((पूर्णांक) value << 8) | gspca_dev->usb_buf[0];
		पूर्ण
		msleep(10);
	पूर्ण जबतक (--retry);
	वापस -1;
पूर्ण

अटल व्योम sensor_mapग_लिखो(काष्ठा gspca_dev *gspca_dev,
			    स्थिर __u16 (*sensormap)[2])
अणु
	जबतक ((*sensormap)[0]) अणु
		gspca_dev->usb_buf[0] = (*sensormap)[1];
		gspca_dev->usb_buf[1] = (*sensormap)[1] >> 8;
		reg_w_buf(gspca_dev, (*sensormap)[0], 2);
		sensormap++;
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_sensor_72a(काष्ठा gspca_dev *gspca_dev,
			    स्थिर __u16 (*sensor)[2])
अणु
	जबतक ((*sensor)[0]) अणु
		i2c_ग_लिखो(gspca_dev, (*sensor)[1], (*sensor)[0]);
		sensor++;
	पूर्ण
पूर्ण

अटल व्योम init_161rev12A(काष्ठा gspca_dev *gspca_dev)
अणु
	ग_लिखो_vector(gspca_dev, spca561_161rev12A_data1);
	sensor_mapग_लिखो(gspca_dev, Pb100_1map8300);
/*fixme: should be in sd_start*/
	ग_लिखो_vector(gspca_dev, spca561_161rev12A_data2);
	sensor_mapग_लिखो(gspca_dev, Pb100_2map8300);
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;
	__u16 venकरोr, product;
	__u8 data1, data2;

	/* Read frm global रेजिस्टर the USB product and venकरोr IDs, just to
	 * prove that we can communicate with the device.  This works, which
	 * confirms at we are communicating properly and that the device
	 * is a 561. */
	reg_r(gspca_dev, 0x8104, 1);
	data1 = gspca_dev->usb_buf[0];
	reg_r(gspca_dev, 0x8105, 1);
	data2 = gspca_dev->usb_buf[0];
	venकरोr = (data2 << 8) | data1;
	reg_r(gspca_dev, 0x8106, 1);
	data1 = gspca_dev->usb_buf[0];
	reg_r(gspca_dev, 0x8107, 1);
	data2 = gspca_dev->usb_buf[0];
	product = (data2 << 8) | data1;
	अगर (venकरोr != id->idVenकरोr || product != id->idProduct) अणु
		gspca_dbg(gspca_dev, D_PROBE, "Bad vendor / product from device\n");
		वापस -EINVAL;
	पूर्ण

	cam = &gspca_dev->cam;
	cam->needs_full_bandwidth = 1;

	sd->chip_revision = id->driver_info;
	अगर (sd->chip_revision == Rev012A) अणु
		cam->cam_mode = sअगर_012a_mode;
		cam->nmodes = ARRAY_SIZE(sअगर_012a_mode);
	पूर्ण अन्यथा अणु
		cam->cam_mode = sअगर_072a_mode;
		cam->nmodes = ARRAY_SIZE(sअगर_072a_mode);
	पूर्ण
	sd->expo12a = EXPO12A_DEF;
	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init_12a(काष्ठा gspca_dev *gspca_dev)
अणु
	gspca_dbg(gspca_dev, D_STREAM, "Chip revision: 012a\n");
	init_161rev12A(gspca_dev);
	वापस 0;
पूर्ण
अटल पूर्णांक sd_init_72a(काष्ठा gspca_dev *gspca_dev)
अणु
	gspca_dbg(gspca_dev, D_STREAM, "Chip revision: 072a\n");
	ग_लिखो_vector(gspca_dev, rev72a_reset);
	msleep(200);
	ग_लिखो_vector(gspca_dev, rev72a_init_data1);
	ग_लिखो_sensor_72a(gspca_dev, rev72a_init_sensor1);
	ग_लिखो_vector(gspca_dev, rev72a_init_data2);
	ग_लिखो_sensor_72a(gspca_dev, rev72a_init_sensor2);
	reg_w_val(gspca_dev, 0x8112, 0x30);
	वापस 0;
पूर्ण

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	__u16 reg;

	अगर (sd->chip_revision == Rev012A)
		reg = 0x8610;
	अन्यथा
		reg = 0x8611;

	reg_w_val(gspca_dev, reg + 0, val);		/* R */
	reg_w_val(gspca_dev, reg + 1, val);		/* Gr */
	reg_w_val(gspca_dev, reg + 2, val);		/* B */
	reg_w_val(gspca_dev, reg + 3, val);		/* Gb */
पूर्ण

अटल व्योम setwhite(काष्ठा gspca_dev *gspca_dev, s32 white, s32 contrast)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	__u8 blue, red;
	__u16 reg;

	/* try to emulate MS-win as possible */
	red = 0x20 + white * 3 / 8;
	blue = 0x90 - white * 5 / 8;
	अगर (sd->chip_revision == Rev012A) अणु
		reg = 0x8614;
	पूर्ण अन्यथा अणु
		reg = 0x8651;
		red += contrast - 0x20;
		blue += contrast - 0x20;
		reg_w_val(gspca_dev, 0x8652, contrast + 0x20); /* Gr */
		reg_w_val(gspca_dev, 0x8654, contrast + 0x20); /* Gb */
	पूर्ण
	reg_w_val(gspca_dev, reg, red);
	reg_w_val(gspca_dev, reg + 2, blue);
पूर्ण

/* rev 12a only */
अटल व्योम setexposure(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	पूर्णांक i, expo = 0;

	/* Register 0x8309 controls exposure क्रम the spca561,
	   the basic exposure setting goes from 1-2047, where 1 is completely
	   dark and 2047 is very bright. It not only influences exposure but
	   also the framerate (to allow क्रम दीर्घer exposure) from 1 - 300 it
	   only उठाओs the exposure समय then from 300 - 600 it halves the
	   framerate to be able to further उठाओ the exposure समय and क्रम every
	   300 more it halves the framerate again. This allows क्रम a maximum
	   exposure समय of circa 0.2 - 0.25 seconds (30 / (2000/3000) fps).
	   Someबार this is not enough, the 1-2047 uses bits 0-10, bits 11-12
	   configure a भागider क्रम the base framerate which us used at the
	   exposure setting of 1-300. These bits configure the base framerate
	   according to the following क्रमmula: fps = 60 / (value + 2) */

	/* We choose to use the high bits setting the fixed framerate भागisor
	   asap, as setting high basic exposure setting without the fixed
	   भागider in combination with high gains makes the cam stop */
	पूर्णांक table[] =  अणु 0, 450, 550, 625, EXPOSURE_MAX पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(table) - 1; i++) अणु
		अगर (val <= table[i + 1]) अणु
			expo  = val - table[i];
			अगर (i)
				expo += 300;
			expo |= i << 11;
			अवरोध;
		पूर्ण
	पूर्ण

	gspca_dev->usb_buf[0] = expo;
	gspca_dev->usb_buf[1] = expo >> 8;
	reg_w_buf(gspca_dev, 0x8309, 2);
पूर्ण

/* rev 12a only */
अटल व्योम setgain(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	/* gain reg low 6 bits  0-63 gain, bit 6 and 7, both द्विगुन the
	   sensitivity when set, so 31 + one of them set == 63, and 15
	   with both of them set == 63 */
	अगर (val < 64)
		gspca_dev->usb_buf[0] = val;
	अन्यथा अगर (val < 128)
		gspca_dev->usb_buf[0] = (val / 2) | 0x40;
	अन्यथा
		gspca_dev->usb_buf[0] = (val / 4) | 0xc0;

	gspca_dev->usb_buf[1] = 0;
	reg_w_buf(gspca_dev, 0x8335, 2);
पूर्ण

अटल व्योम setस्वतःgain(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (val)
		sd->ag_cnt = AG_CNT_START;
	अन्यथा
		sd->ag_cnt = -1;
पूर्ण

अटल पूर्णांक sd_start_12a(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक mode;
	अटल स्थिर __u8 Reg8391[8] =
		अणु0x92, 0x30, 0x20, 0x00, 0x0c, 0x00, 0x00, 0x00पूर्ण;

	mode = gspca_dev->cam.cam_mode[(पूर्णांक) gspca_dev->curr_mode].priv;
	अगर (mode <= 1) अणु
		/* Use compression on 320x240 and above */
		reg_w_val(gspca_dev, 0x8500, 0x10 | mode);
	पूर्ण अन्यथा अणु
		/* I couldn't get the compression to work below 320x240
		 * Fortunately at these resolutions the bandwidth
		 * is sufficient to push raw frames at ~20fps */
		reg_w_val(gspca_dev, 0x8500, mode);
	पूर्ण		/* -- qq@kuku.eu.org */

	gspca_dev->usb_buf[0] = 0xaa;
	gspca_dev->usb_buf[1] = 0x00;
	reg_w_buf(gspca_dev, 0x8307, 2);
	/* घड़ी - lower 0x8X values lead to fps > 30 */
	reg_w_val(gspca_dev, 0x8700, 0x8a);
					/* 0x8f 0x85 0x27 घड़ी */
	reg_w_val(gspca_dev, 0x8112, 0x1e | 0x20);
	reg_w_val(gspca_dev, 0x850b, 0x03);
	स_नकल(gspca_dev->usb_buf, Reg8391, 8);
	reg_w_buf(gspca_dev, 0x8391, 8);
	reg_w_buf(gspca_dev, 0x8390, 8);

	/* Led ON (bit 3 -> 0 */
	reg_w_val(gspca_dev, 0x8114, 0x00);
	वापस 0;
पूर्ण
अटल पूर्णांक sd_start_72a(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक Clck;
	पूर्णांक mode;

	ग_लिखो_vector(gspca_dev, rev72a_reset);
	msleep(200);
	ग_लिखो_vector(gspca_dev, rev72a_init_data1);
	ग_लिखो_sensor_72a(gspca_dev, rev72a_init_sensor1);

	mode = gspca_dev->cam.cam_mode[(पूर्णांक) gspca_dev->curr_mode].priv;
	चयन (mode) अणु
	शेष:
	हाल 0:
		Clck = 0x27;		/* ms-win 0x87 */
		अवरोध;
	हाल 1:
		Clck = 0x25;
		अवरोध;
	हाल 2:
		Clck = 0x22;
		अवरोध;
	हाल 3:
		Clck = 0x21;
		अवरोध;
	पूर्ण
	reg_w_val(gspca_dev, 0x8700, Clck);	/* 0x27 घड़ी */
	reg_w_val(gspca_dev, 0x8702, 0x81);
	reg_w_val(gspca_dev, 0x8500, mode);	/* mode */
	ग_लिखो_sensor_72a(gspca_dev, rev72a_init_sensor2);
	setwhite(gspca_dev, v4l2_ctrl_g_ctrl(sd->hue),
			v4l2_ctrl_g_ctrl(sd->contrast));
/*	setbrightness(gspca_dev);	 * fixme: bad values */
	setस्वतःgain(gspca_dev, v4l2_ctrl_g_ctrl(sd->स्वतःgain));
	reg_w_val(gspca_dev, 0x8112, 0x10 | 0x20);
	वापस 0;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->chip_revision == Rev012A) अणु
		reg_w_val(gspca_dev, 0x8112, 0x0e);
		/* Led Off (bit 3 -> 1 */
		reg_w_val(gspca_dev, 0x8114, 0x08);
	पूर्ण अन्यथा अणु
		reg_w_val(gspca_dev, 0x8112, 0x20);
/*		reg_w_val(gspca_dev, 0x8102, 0x00); ?? */
	पूर्ण
पूर्ण

अटल व्योम करो_स्वतःgain(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक expoबार;
	पूर्णांक pixelclk;
	पूर्णांक gainG;
	__u8 R, Gr, Gb, B;
	पूर्णांक y;
	__u8 luma_mean = 110;
	__u8 luma_delta = 20;
	__u8 spring = 4;

	अगर (sd->ag_cnt < 0)
		वापस;
	अगर (--sd->ag_cnt >= 0)
		वापस;
	sd->ag_cnt = AG_CNT_START;

	चयन (sd->chip_revision) अणु
	हाल Rev072A:
		reg_r(gspca_dev, 0x8621, 1);
		Gr = gspca_dev->usb_buf[0];
		reg_r(gspca_dev, 0x8622, 1);
		R = gspca_dev->usb_buf[0];
		reg_r(gspca_dev, 0x8623, 1);
		B = gspca_dev->usb_buf[0];
		reg_r(gspca_dev, 0x8624, 1);
		Gb = gspca_dev->usb_buf[0];
		y = (77 * R + 75 * (Gr + Gb) + 29 * B) >> 8;
		/* u= (128*B-(43*(Gr+Gb+R))) >> 8; */
		/* v= (128*R-(53*(Gr+Gb))-21*B) >> 8; */

		अगर (y < luma_mean - luma_delta ||
		    y > luma_mean + luma_delta) अणु
			expoबार = i2c_पढ़ो(gspca_dev, 0x09, 0x10);
			pixelclk = 0x0800;
			expoबार = expoबार & 0x07ff;
			gainG = i2c_पढ़ो(gspca_dev, 0x35, 0x10);

			expoबार += (luma_mean - y) >> spring;
			gainG += (luma_mean - y) / 50;

			अगर (gainG > 0x3f)
				gainG = 0x3f;
			अन्यथा अगर (gainG < 3)
				gainG = 3;
			i2c_ग_लिखो(gspca_dev, gainG, 0x35);

			अगर (expoबार > 0x0256)
				expoबार = 0x0256;
			अन्यथा अगर (expoबार < 3)
				expoबार = 3;
			i2c_ग_लिखो(gspca_dev, expoबार | pixelclk, 0x09);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,		/* isoc packet */
			पूर्णांक len)		/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	len--;
	चयन (*data++) अणु			/* sequence number */
	हाल 0:					/* start of frame */
		gspca_frame_add(gspca_dev, LAST_PACKET, शून्य, 0);

		/* This should never happen */
		अगर (len < 2) अणु
			gspca_err(gspca_dev, "Short SOF packet, ignoring\n\n\n\n\n");
			gspca_dev->last_packet_type = DISCARD_PACKET;
			वापस;
		पूर्ण

#अगर IS_ENABLED(CONFIG_INPUT)
		अगर (data[0] & 0x20) अणु
			input_report_key(gspca_dev->input_dev, KEY_CAMERA, 1);
			input_sync(gspca_dev->input_dev);
			input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
			input_sync(gspca_dev->input_dev);
		पूर्ण
#पूर्ण_अगर

		अगर (data[1] & 0x10) अणु
			/* compressed bayer */
			gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
		पूर्ण अन्यथा अणु
			/* raw bayer (with a header, which we skip) */
			अगर (sd->chip_revision == Rev012A) अणु
				data += 20;
				len -= 20;
			पूर्ण अन्यथा अणु
				data += 16;
				len -= 16;
			पूर्ण
			gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
		पूर्ण
		वापस;
	हाल 0xff:			/* drop (empty mpackets) */
		वापस;
	पूर्ण
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		setbrightness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		/* hue/contrast control cluster क्रम 72a */
		setwhite(gspca_dev, sd->hue->val, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		/* just plain hue control क्रम 12a */
		setwhite(gspca_dev, ctrl->val, 0);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		setexposure(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_GAIN:
		setgain(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		setस्वतःgain(gspca_dev, ctrl->val);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls_12a(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 3);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_HUE, 1, 0x7f, 1, 0x40);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, -128, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_EXPOSURE, 1, EXPOSURE_MAX, 1, 700);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAIN, 0, 255, 1, 63);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sd_init_controls_72a(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	sd->contrast = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 0x3f, 1, 0x20);
	sd->hue = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_HUE, 1, 0x7f, 1, 0x40);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 0x3f, 1, 0x20);
	sd->स्वतःgain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	v4l2_ctrl_cluster(2, &sd->contrast);
	वापस 0;
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc_12a = अणु
	.name = MODULE_NAME,
	.init_controls = sd_init_controls_12a,
	.config = sd_config,
	.init = sd_init_12a,
	.start = sd_start_12a,
	.stopN = sd_stopN,
	.pkt_scan = sd_pkt_scan,
#अगर IS_ENABLED(CONFIG_INPUT)
	.other_input = 1,
#पूर्ण_अगर
पूर्ण;
अटल स्थिर काष्ठा sd_desc sd_desc_72a = अणु
	.name = MODULE_NAME,
	.init_controls = sd_init_controls_72a,
	.config = sd_config,
	.init = sd_init_72a,
	.start = sd_start_72a,
	.stopN = sd_stopN,
	.pkt_scan = sd_pkt_scan,
	.dq_callback = करो_स्वतःgain,
#अगर IS_ENABLED(CONFIG_INPUT)
	.other_input = 1,
#पूर्ण_अगर
पूर्ण;
अटल स्थिर काष्ठा sd_desc *sd_desc[2] = अणु
	&sd_desc_12a,
	&sd_desc_72a
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x041e, 0x401a), .driver_info = Rev072Aपूर्ण,
	अणुUSB_DEVICE(0x041e, 0x403b), .driver_info = Rev012Aपूर्ण,
	अणुUSB_DEVICE(0x0458, 0x7004), .driver_info = Rev072Aपूर्ण,
	अणुUSB_DEVICE(0x0461, 0x0815), .driver_info = Rev072Aपूर्ण,
	अणुUSB_DEVICE(0x046d, 0x0928), .driver_info = Rev012Aपूर्ण,
	अणुUSB_DEVICE(0x046d, 0x0929), .driver_info = Rev012Aपूर्ण,
	अणुUSB_DEVICE(0x046d, 0x092a), .driver_info = Rev012Aपूर्ण,
	अणुUSB_DEVICE(0x046d, 0x092b), .driver_info = Rev012Aपूर्ण,
	अणुUSB_DEVICE(0x046d, 0x092c), .driver_info = Rev012Aपूर्ण,
	अणुUSB_DEVICE(0x046d, 0x092d), .driver_info = Rev012Aपूर्ण,
	अणुUSB_DEVICE(0x046d, 0x092e), .driver_info = Rev012Aपूर्ण,
	अणुUSB_DEVICE(0x046d, 0x092f), .driver_info = Rev012Aपूर्ण,
	अणुUSB_DEVICE(0x04fc, 0x0561), .driver_info = Rev072Aपूर्ण,
	अणुUSB_DEVICE(0x060b, 0xa001), .driver_info = Rev072Aपूर्ण,
	अणुUSB_DEVICE(0x10fd, 0x7e50), .driver_info = Rev072Aपूर्ण,
	अणुUSB_DEVICE(0xabcd, 0xcdee), .driver_info = Rev072Aपूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, device_table);

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		    स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id,
				sd_desc[id->driver_info],
				माप(काष्ठा sd),
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
