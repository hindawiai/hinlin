<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Etoms Et61x151 GPL Linux driver by Michel Xhaard (09/09/2004)
 *
 * V4L2 by Jean-Francois Moine <http://moinejf.मुक्त.fr>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "etoms"

#समावेश "gspca.h"

MODULE_AUTHOR("Michel Xhaard <mxhaard@users.sourceforge.net>");
MODULE_DESCRIPTION("Etoms USB Camera Driver");
MODULE_LICENSE("GPL");

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	अचिन्हित अक्षर स्वतःgain;

	अक्षर sensor;
#घोषणा SENSOR_PAS106 0
#घोषणा SENSOR_TAS5130CXX 1
	चिन्हित अक्षर ag_cnt;
#घोषणा AG_CNT_START 13
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
/*	अणु640, 480, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण, */
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat sअगर_mode[] = अणु
	अणु176, 144, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
पूर्ण;

#घोषणा ETOMS_ALT_SIZE_1000   12

#घोषणा ET_GPIO_सूची_CTRL 0x04	/* Control IO bit[0..5] (0 in  1 out) */
#घोषणा ET_GPIO_OUT 0x05	/* Only IO data */
#घोषणा ET_GPIO_IN 0x06		/* Read Only IO data */
#घोषणा ET_RESET_ALL 0x03
#घोषणा ET_ClCK 0x01
#घोषणा ET_CTRL 0x02		/* enable i2c OutClck Powerकरोwn mode */

#घोषणा ET_COMP 0x12		/* Compression रेजिस्टर */
#घोषणा ET_MAXQt 0x13
#घोषणा ET_MINQt 0x14
#घोषणा ET_COMP_VAL0 0x02
#घोषणा ET_COMP_VAL1 0x03

#घोषणा ET_REG1d 0x1d
#घोषणा ET_REG1e 0x1e
#घोषणा ET_REG1f 0x1f
#घोषणा ET_REG20 0x20
#घोषणा ET_REG21 0x21
#घोषणा ET_REG22 0x22
#घोषणा ET_REG23 0x23
#घोषणा ET_REG24 0x24
#घोषणा ET_REG25 0x25
/* base रेजिस्टरs क्रम luma calculation */
#घोषणा ET_LUMA_CENTER 0x39

#घोषणा ET_G_RED 0x4d
#घोषणा ET_G_GREEN1 0x4e
#घोषणा ET_G_BLUE 0x4f
#घोषणा ET_G_GREEN2 0x50
#घोषणा ET_G_GR_H 0x51
#घोषणा ET_G_GB_H 0x52

#घोषणा ET_O_RED 0x34
#घोषणा ET_O_GREEN1 0x35
#घोषणा ET_O_BLUE 0x36
#घोषणा ET_O_GREEN2 0x37

#घोषणा ET_SYNCHRO 0x68
#घोषणा ET_STARTX 0x69
#घोषणा ET_STARTY 0x6a
#घोषणा ET_WIDTH_LOW 0x6b
#घोषणा ET_HEIGTH_LOW 0x6c
#घोषणा ET_W_H_HEIGTH 0x6d

#घोषणा ET_REG6e 0x6e		/* OBW */
#घोषणा ET_REG6f 0x6f		/* OBW */
#घोषणा ET_REG70 0x70		/* OBW_AWB */
#घोषणा ET_REG71 0x71		/* OBW_AWB */
#घोषणा ET_REG72 0x72		/* OBW_AWB */
#घोषणा ET_REG73 0x73		/* Clkdelay ns */
#घोषणा ET_REG74 0x74		/* test pattern */
#घोषणा ET_REG75 0x75		/* test pattern */

#घोषणा ET_I2C_CLK 0x8c
#घोषणा ET_PXL_CLK 0x60

#घोषणा ET_I2C_BASE 0x89
#घोषणा ET_I2C_COUNT 0x8a
#घोषणा ET_I2C_PREFETCH 0x8b
#घोषणा ET_I2C_REG 0x88
#घोषणा ET_I2C_DATA7 0x87
#घोषणा ET_I2C_DATA6 0x86
#घोषणा ET_I2C_DATA5 0x85
#घोषणा ET_I2C_DATA4 0x84
#घोषणा ET_I2C_DATA3 0x83
#घोषणा ET_I2C_DATA2 0x82
#घोषणा ET_I2C_DATA1 0x81
#घोषणा ET_I2C_DATA0 0x80

#घोषणा PAS106_REG2 0x02	/* pxlClk = प्रणालीClk/(reg2) */
#घोषणा PAS106_REG3 0x03	/* line/frame H [11..4] */
#घोषणा PAS106_REG4 0x04	/* line/frame L [3..0] */
#घोषणा PAS106_REG5 0x05	/* exposure समय line offset(शेष 5) */
#घोषणा PAS106_REG6 0x06	/* exposure समय pixel offset(शेष 6) */
#घोषणा PAS106_REG7 0x07	/* signbit Dac (शेष 0) */
#घोषणा PAS106_REG9 0x09
#घोषणा PAS106_REG0e 0x0e	/* global gain [4..0](शेष 0x0e) */
#घोषणा PAS106_REG13 0x13	/* end i2c ग_लिखो */

अटल स्थिर __u8 GainRGBG[] = अणु 0x80, 0x80, 0x80, 0x80, 0x00, 0x00 पूर्ण;

अटल स्थिर __u8 I2c2[] = अणु 0x08, 0x08, 0x08, 0x08, 0x0d पूर्ण;

अटल स्थिर __u8 I2c3[] = अणु 0x12, 0x05 पूर्ण;

अटल स्थिर __u8 I2c4[] = अणु 0x41, 0x08 पूर्ण;

/* पढ़ो 'len' bytes to gspca_dev->usb_buf */
अटल व्योम reg_r(काष्ठा gspca_dev *gspca_dev,
		  __u16 index,
		  __u16 len)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;

	अगर (len > USB_BUF_SZ) अणु
		gspca_err(gspca_dev, "reg_r: buffer overflow\n");
		वापस;
	पूर्ण

	usb_control_msg(dev,
			usb_rcvctrlpipe(dev, 0),
			0,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			0,
			index, gspca_dev->usb_buf, len, 500);
	gspca_dbg(gspca_dev, D_USBI, "reg read [%02x] -> %02x ..\n",
		  index, gspca_dev->usb_buf[0]);
पूर्ण

अटल व्योम reg_w_val(काष्ठा gspca_dev *gspca_dev,
			__u16 index,
			__u8 val)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;

	gspca_dev->usb_buf[0] = val;
	usb_control_msg(dev,
			usb_sndctrlpipe(dev, 0),
			0,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			0,
			index, gspca_dev->usb_buf, 1, 500);
पूर्ण

अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev,
		  __u16 index,
		  स्थिर __u8 *buffer,
		  __u16 len)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;

	अगर (len > USB_BUF_SZ) अणु
		pr_err("reg_w: buffer overflow\n");
		वापस;
	पूर्ण
	gspca_dbg(gspca_dev, D_USBO, "reg write [%02x] = %02x..\n",
		  index, *buffer);

	स_नकल(gspca_dev->usb_buf, buffer, len);
	usb_control_msg(dev,
			usb_sndctrlpipe(dev, 0),
			0,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			0, index, gspca_dev->usb_buf, len, 500);
पूर्ण

अटल पूर्णांक i2c_w(काष्ठा gspca_dev *gspca_dev,
		 __u8 reg,
		 स्थिर __u8 *buffer,
		 पूर्णांक len, __u8 mode)
अणु
	/* buffer should be [D0..D7] */
	__u8 ptchcount;

	/* set the base address */
	reg_w_val(gspca_dev, ET_I2C_BASE, 0x40);
					 /* sensor base क्रम the pas106 */
	/* set count and prefetch */
	ptchcount = ((len & 0x07) << 4) | (mode & 0x03);
	reg_w_val(gspca_dev, ET_I2C_COUNT, ptchcount);
	/* set the रेजिस्टर base */
	reg_w_val(gspca_dev, ET_I2C_REG, reg);
	जबतक (--len >= 0)
		reg_w_val(gspca_dev, ET_I2C_DATA0 + len, buffer[len]);
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_r(काष्ठा gspca_dev *gspca_dev,
			__u8 reg)
अणु
	/* set the base address */
	reg_w_val(gspca_dev, ET_I2C_BASE, 0x40);
					/* sensor base क्रम the pas106 */
	/* set count and prefetch (cnd: 4 bits - mode: 4 bits) */
	reg_w_val(gspca_dev, ET_I2C_COUNT, 0x11);
	reg_w_val(gspca_dev, ET_I2C_REG, reg);	/* set the रेजिस्टर base */
	reg_w_val(gspca_dev, ET_I2C_PREFETCH, 0x02);	/* prefetch */
	reg_w_val(gspca_dev, ET_I2C_PREFETCH, 0x00);
	reg_r(gspca_dev, ET_I2C_DATA0, 1);	/* पढ़ो one byte */
	वापस 0;
पूर्ण

अटल पूर्णांक Et_WaitStatus(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक retry = 10;

	जबतक (retry--) अणु
		reg_r(gspca_dev, ET_ClCK, 1);
		अगर (gspca_dev->usb_buf[0] != 0)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक et_video(काष्ठा gspca_dev *gspca_dev,
		    पूर्णांक on)
अणु
	पूर्णांक ret;

	reg_w_val(gspca_dev, ET_GPIO_OUT,
		  on ? 0x10		/* startvideo - set Bit5 */
		     : 0);		/* stopvideo */
	ret = Et_WaitStatus(gspca_dev);
	अगर (ret != 0)
		gspca_err(gspca_dev, "timeout video on/off\n");
	वापस ret;
पूर्ण

अटल व्योम Et_init2(काष्ठा gspca_dev *gspca_dev)
अणु
	__u8 value;
	अटल स्थिर __u8 FormLine[] = अणु 0x84, 0x03, 0x14, 0xf4, 0x01, 0x05 पूर्ण;

	gspca_dbg(gspca_dev, D_STREAM, "Open Init2 ET\n");
	reg_w_val(gspca_dev, ET_GPIO_सूची_CTRL, 0x2f);
	reg_w_val(gspca_dev, ET_GPIO_OUT, 0x10);
	reg_r(gspca_dev, ET_GPIO_IN, 1);
	reg_w_val(gspca_dev, ET_ClCK, 0x14); /* 0x14 // 0x16 enabled pattern */
	reg_w_val(gspca_dev, ET_CTRL, 0x1b);

	/*  compression et subsampling */
	अगर (gspca_dev->cam.cam_mode[(पूर्णांक) gspca_dev->curr_mode].priv)
		value = ET_COMP_VAL1;	/* 320 */
	अन्यथा
		value = ET_COMP_VAL0;	/* 640 */
	reg_w_val(gspca_dev, ET_COMP, value);
	reg_w_val(gspca_dev, ET_MAXQt, 0x1f);
	reg_w_val(gspca_dev, ET_MINQt, 0x04);
	/* unकरोcumented रेजिस्टरs */
	reg_w_val(gspca_dev, ET_REG1d, 0xff);
	reg_w_val(gspca_dev, ET_REG1e, 0xff);
	reg_w_val(gspca_dev, ET_REG1f, 0xff);
	reg_w_val(gspca_dev, ET_REG20, 0x35);
	reg_w_val(gspca_dev, ET_REG21, 0x01);
	reg_w_val(gspca_dev, ET_REG22, 0x00);
	reg_w_val(gspca_dev, ET_REG23, 0xff);
	reg_w_val(gspca_dev, ET_REG24, 0xff);
	reg_w_val(gspca_dev, ET_REG25, 0x0f);
	/* colors setting */
	reg_w_val(gspca_dev, 0x30, 0x11);		/* 0x30 */
	reg_w_val(gspca_dev, 0x31, 0x40);
	reg_w_val(gspca_dev, 0x32, 0x00);
	reg_w_val(gspca_dev, ET_O_RED, 0x00);		/* 0x34 */
	reg_w_val(gspca_dev, ET_O_GREEN1, 0x00);
	reg_w_val(gspca_dev, ET_O_BLUE, 0x00);
	reg_w_val(gspca_dev, ET_O_GREEN2, 0x00);
	/*************/
	reg_w_val(gspca_dev, ET_G_RED, 0x80);		/* 0x4d */
	reg_w_val(gspca_dev, ET_G_GREEN1, 0x80);
	reg_w_val(gspca_dev, ET_G_BLUE, 0x80);
	reg_w_val(gspca_dev, ET_G_GREEN2, 0x80);
	reg_w_val(gspca_dev, ET_G_GR_H, 0x00);
	reg_w_val(gspca_dev, ET_G_GB_H, 0x00);		/* 0x52 */
	/* Winकरोw control रेजिस्टरs */
	reg_w_val(gspca_dev, 0x61, 0x80);		/* use cmc_out */
	reg_w_val(gspca_dev, 0x62, 0x02);
	reg_w_val(gspca_dev, 0x63, 0x03);
	reg_w_val(gspca_dev, 0x64, 0x14);
	reg_w_val(gspca_dev, 0x65, 0x0e);
	reg_w_val(gspca_dev, 0x66, 0x02);
	reg_w_val(gspca_dev, 0x67, 0x02);

	/**************************************/
	reg_w_val(gspca_dev, ET_SYNCHRO, 0x8f);		/* 0x68 */
	reg_w_val(gspca_dev, ET_STARTX, 0x69);		/* 0x6a //0x69 */
	reg_w_val(gspca_dev, ET_STARTY, 0x0d);		/* 0x0d //0x0c */
	reg_w_val(gspca_dev, ET_WIDTH_LOW, 0x80);
	reg_w_val(gspca_dev, ET_HEIGTH_LOW, 0xe0);
	reg_w_val(gspca_dev, ET_W_H_HEIGTH, 0x60);	/* 6d */
	reg_w_val(gspca_dev, ET_REG6e, 0x86);
	reg_w_val(gspca_dev, ET_REG6f, 0x01);
	reg_w_val(gspca_dev, ET_REG70, 0x26);
	reg_w_val(gspca_dev, ET_REG71, 0x7a);
	reg_w_val(gspca_dev, ET_REG72, 0x01);
	/* Clock Pattern रेजिस्टरs ***************** */
	reg_w_val(gspca_dev, ET_REG73, 0x00);
	reg_w_val(gspca_dev, ET_REG74, 0x18);		/* 0x28 */
	reg_w_val(gspca_dev, ET_REG75, 0x0f);		/* 0x01 */
	/**********************************************/
	reg_w_val(gspca_dev, 0x8a, 0x20);
	reg_w_val(gspca_dev, 0x8d, 0x0f);
	reg_w_val(gspca_dev, 0x8e, 0x08);
	/**************************************/
	reg_w_val(gspca_dev, 0x03, 0x08);
	reg_w_val(gspca_dev, ET_PXL_CLK, 0x03);
	reg_w_val(gspca_dev, 0x81, 0xff);
	reg_w_val(gspca_dev, 0x80, 0x00);
	reg_w_val(gspca_dev, 0x81, 0xff);
	reg_w_val(gspca_dev, 0x80, 0x20);
	reg_w_val(gspca_dev, 0x03, 0x01);
	reg_w_val(gspca_dev, 0x03, 0x00);
	reg_w_val(gspca_dev, 0x03, 0x08);
	/********************************************/

/*	reg_r(gspca_dev, ET_I2C_BASE, 1);
					 always 0x40 as the pas106 ??? */
	/* set the sensor */
	अगर (gspca_dev->cam.cam_mode[(पूर्णांक) gspca_dev->curr_mode].priv)
		value = 0x04;		/* 320 */
	अन्यथा				/* 640 */
		value = 0x1e;	/* 0x17	 * setting PixelClock
					 * 0x03 mean 24/(3+1) = 6 Mhz
					 * 0x05 -> 24/(5+1) = 4 Mhz
					 * 0x0b -> 24/(11+1) = 2 Mhz
					 * 0x17 -> 24/(23+1) = 1 Mhz
					 */
	reg_w_val(gspca_dev, ET_PXL_CLK, value);
	/* now set by fअगरo the FormatLine setting */
	reg_w(gspca_dev, 0x62, FormLine, 6);

	/* set exposure बार [ 0..0x78] 0->दीर्घvalue 0x78->लघुvalue */
	reg_w_val(gspca_dev, 0x81, 0x47);	/* 0x47; */
	reg_w_val(gspca_dev, 0x80, 0x40);	/* 0x40; */
	/* Pedro change */
	/* Brightness change Brith+ decrease value */
	/* Brigth- increase value */
	/* original value = 0x70; */
	reg_w_val(gspca_dev, 0x81, 0x30);	/* 0x20; - set brightness */
	reg_w_val(gspca_dev, 0x80, 0x20);	/* 0x20; */
पूर्ण

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		reg_w_val(gspca_dev, ET_O_RED + i, val);
पूर्ण

अटल व्योम setcontrast(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	__u8 RGBG[] = अणु 0x80, 0x80, 0x80, 0x80, 0x00, 0x00 पूर्ण;

	स_रखो(RGBG, val, माप(RGBG) - 2);
	reg_w(gspca_dev, ET_G_RED, RGBG, 6);
पूर्ण

अटल व्योम setcolors(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	__u8 I2cc[] = अणु 0x05, 0x02, 0x02, 0x05, 0x0d पूर्ण;
	__u8 i2cflags = 0x01;
	/* __u8 green = 0; */

	I2cc[3] = val;	/* red */
	I2cc[0] = 15 - val;	/* blue */
	/* green = 15 - ((((7*I2cc[0]) >> 2 ) + I2cc[3]) >> 1); */
	/* I2cc[1] = I2cc[2] = green; */
	अगर (sd->sensor == SENSOR_PAS106) अणु
		i2c_w(gspca_dev, PAS106_REG13, &i2cflags, 1, 3);
		i2c_w(gspca_dev, PAS106_REG9, I2cc, माप I2cc, 1);
	पूर्ण
पूर्ण

अटल s32 अ_लोolors(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_PAS106) अणु
/*		i2c_r(gspca_dev, PAS106_REG9);		 * blue */
		i2c_r(gspca_dev, PAS106_REG9 + 3);	/* red */
		वापस gspca_dev->usb_buf[0] & 0x0f;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम setस्वतःgain(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->स्वतःgain)
		sd->ag_cnt = AG_CNT_START;
	अन्यथा
		sd->ag_cnt = -1;
पूर्ण

अटल व्योम Et_init1(काष्ठा gspca_dev *gspca_dev)
अणु
	__u8 value;
/*	__u8 I2c0 [] = अणु0x0a, 0x12, 0x05, 0x22, 0xac, 0x00, 0x01, 0x00पूर्ण; */
	__u8 I2c0[] = अणु 0x0a, 0x12, 0x05, 0x6d, 0xcd, 0x00, 0x01, 0x00 पूर्ण;
						/* try 1/120 0x6d 0xcd 0x40 */
/*	__u8 I2c0 [] = अणु0x0a, 0x12, 0x05, 0xfe, 0xfe, 0xc0, 0x01, 0x00पूर्ण;
						 * 1/60000 hmm ?? */

	gspca_dbg(gspca_dev, D_STREAM, "Open Init1 ET\n\n");
	reg_w_val(gspca_dev, ET_GPIO_सूची_CTRL, 7);
	reg_r(gspca_dev, ET_GPIO_IN, 1);
	reg_w_val(gspca_dev, ET_RESET_ALL, 1);
	reg_w_val(gspca_dev, ET_RESET_ALL, 0);
	reg_w_val(gspca_dev, ET_ClCK, 0x10);
	reg_w_val(gspca_dev, ET_CTRL, 0x19);
	/*   compression et subsampling */
	अगर (gspca_dev->cam.cam_mode[(पूर्णांक) gspca_dev->curr_mode].priv)
		value = ET_COMP_VAL1;
	अन्यथा
		value = ET_COMP_VAL0;
	gspca_dbg(gspca_dev, D_STREAM, "Open mode %d Compression %d\n",
		  gspca_dev->cam.cam_mode[(पूर्णांक) gspca_dev->curr_mode].priv,
		  value);
	reg_w_val(gspca_dev, ET_COMP, value);
	reg_w_val(gspca_dev, ET_MAXQt, 0x1d);
	reg_w_val(gspca_dev, ET_MINQt, 0x02);
	/* unकरोcumented रेजिस्टरs */
	reg_w_val(gspca_dev, ET_REG1d, 0xff);
	reg_w_val(gspca_dev, ET_REG1e, 0xff);
	reg_w_val(gspca_dev, ET_REG1f, 0xff);
	reg_w_val(gspca_dev, ET_REG20, 0x35);
	reg_w_val(gspca_dev, ET_REG21, 0x01);
	reg_w_val(gspca_dev, ET_REG22, 0x00);
	reg_w_val(gspca_dev, ET_REG23, 0xf7);
	reg_w_val(gspca_dev, ET_REG24, 0xff);
	reg_w_val(gspca_dev, ET_REG25, 0x07);
	/* colors setting */
	reg_w_val(gspca_dev, ET_G_RED, 0x80);
	reg_w_val(gspca_dev, ET_G_GREEN1, 0x80);
	reg_w_val(gspca_dev, ET_G_BLUE, 0x80);
	reg_w_val(gspca_dev, ET_G_GREEN2, 0x80);
	reg_w_val(gspca_dev, ET_G_GR_H, 0x00);
	reg_w_val(gspca_dev, ET_G_GB_H, 0x00);
	/* Winकरोw control रेजिस्टरs */
	reg_w_val(gspca_dev, ET_SYNCHRO, 0xf0);
	reg_w_val(gspca_dev, ET_STARTX, 0x56);		/* 0x56 */
	reg_w_val(gspca_dev, ET_STARTY, 0x05);		/* 0x04 */
	reg_w_val(gspca_dev, ET_WIDTH_LOW, 0x60);
	reg_w_val(gspca_dev, ET_HEIGTH_LOW, 0x20);
	reg_w_val(gspca_dev, ET_W_H_HEIGTH, 0x50);
	reg_w_val(gspca_dev, ET_REG6e, 0x86);
	reg_w_val(gspca_dev, ET_REG6f, 0x01);
	reg_w_val(gspca_dev, ET_REG70, 0x86);
	reg_w_val(gspca_dev, ET_REG71, 0x14);
	reg_w_val(gspca_dev, ET_REG72, 0x00);
	/* Clock Pattern रेजिस्टरs */
	reg_w_val(gspca_dev, ET_REG73, 0x00);
	reg_w_val(gspca_dev, ET_REG74, 0x00);
	reg_w_val(gspca_dev, ET_REG75, 0x0a);
	reg_w_val(gspca_dev, ET_I2C_CLK, 0x04);
	reg_w_val(gspca_dev, ET_PXL_CLK, 0x01);
	/* set the sensor */
	अगर (gspca_dev->cam.cam_mode[(पूर्णांक) gspca_dev->curr_mode].priv) अणु
		I2c0[0] = 0x06;
		i2c_w(gspca_dev, PAS106_REG2, I2c0, माप I2c0, 1);
		i2c_w(gspca_dev, PAS106_REG9, I2c2, माप I2c2, 1);
		value = 0x06;
		i2c_w(gspca_dev, PAS106_REG2, &value, 1, 1);
		i2c_w(gspca_dev, PAS106_REG3, I2c3, माप I2c3, 1);
		/* value = 0x1f; */
		value = 0x04;
		i2c_w(gspca_dev, PAS106_REG0e, &value, 1, 1);
	पूर्ण अन्यथा अणु
		I2c0[0] = 0x0a;

		i2c_w(gspca_dev, PAS106_REG2, I2c0, माप I2c0, 1);
		i2c_w(gspca_dev, PAS106_REG9, I2c2, माप I2c2, 1);
		value = 0x0a;
		i2c_w(gspca_dev, PAS106_REG2, &value, 1, 1);
		i2c_w(gspca_dev, PAS106_REG3, I2c3, माप I2c3, 1);
		value = 0x04;
		/* value = 0x10; */
		i2c_w(gspca_dev, PAS106_REG0e, &value, 1, 1);
		/* bit 2 enable bit 1:2 select 0 1 2 3
		   value = 0x07;                                * curve 0 *
		   i2c_w(gspca_dev, PAS106_REG0f, &value, 1, 1);
		 */
	पूर्ण

/*	value = 0x01; */
/*	value = 0x22; */
/*	i2c_w(gspca_dev, PAS106_REG5, &value, 1, 1); */
	/* magnetude and sign bit क्रम DAC */
	i2c_w(gspca_dev, PAS106_REG7, I2c4, माप I2c4, 1);
	/* now set by fअगरo the whole colors setting */
	reg_w(gspca_dev, ET_G_RED, GainRGBG, 6);
	setcolors(gspca_dev, अ_लोolors(gspca_dev));
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;

	cam = &gspca_dev->cam;
	sd->sensor = id->driver_info;
	अगर (sd->sensor == SENSOR_PAS106) अणु
		cam->cam_mode = sअगर_mode;
		cam->nmodes = ARRAY_SIZE(sअगर_mode);
	पूर्ण अन्यथा अणु
		cam->cam_mode = vga_mode;
		cam->nmodes = ARRAY_SIZE(vga_mode);
	पूर्ण
	sd->ag_cnt = -1;
	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_PAS106)
		Et_init1(gspca_dev);
	अन्यथा
		Et_init2(gspca_dev);
	reg_w_val(gspca_dev, ET_RESET_ALL, 0x08);
	et_video(gspca_dev, 0);		/* video off */
	वापस 0;
पूर्ण

/* -- start the camera -- */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_PAS106)
		Et_init1(gspca_dev);
	अन्यथा
		Et_init2(gspca_dev);

	setस्वतःgain(gspca_dev);

	reg_w_val(gspca_dev, ET_RESET_ALL, 0x08);
	et_video(gspca_dev, 1);		/* video on */
	वापस 0;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	et_video(gspca_dev, 0);		/* video off */
पूर्ण

अटल __u8 Et_getgainG(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_PAS106) अणु
		i2c_r(gspca_dev, PAS106_REG0e);
		gspca_dbg(gspca_dev, D_CONF, "Etoms gain G %d\n",
			  gspca_dev->usb_buf[0]);
		वापस gspca_dev->usb_buf[0];
	पूर्ण
	वापस 0x1f;
पूर्ण

अटल व्योम Et_setgainG(काष्ठा gspca_dev *gspca_dev, __u8 gain)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_PAS106) अणु
		__u8 i2cflags = 0x01;

		i2c_w(gspca_dev, PAS106_REG13, &i2cflags, 1, 3);
		i2c_w(gspca_dev, PAS106_REG0e, &gain, 1, 1);
	पूर्ण
पूर्ण

#घोषणा BLIMIT(bright) \
	(u8)((bright > 0x1f) ? 0x1f : ((bright < 4) ? 3 : bright))
#घोषणा LIMIT(color) \
	(u8)((color > 0xff) ? 0xff : ((color < 0) ? 0 : color))

अटल व्योम करो_स्वतःgain(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	__u8 luma;
	__u8 luma_mean = 128;
	__u8 luma_delta = 20;
	__u8 spring = 4;
	पूर्णांक Gbright;
	__u8 r, g, b;

	अगर (sd->ag_cnt < 0)
		वापस;
	अगर (--sd->ag_cnt >= 0)
		वापस;
	sd->ag_cnt = AG_CNT_START;

	Gbright = Et_getgainG(gspca_dev);
	reg_r(gspca_dev, ET_LUMA_CENTER, 4);
	g = (gspca_dev->usb_buf[0] + gspca_dev->usb_buf[3]) >> 1;
	r = gspca_dev->usb_buf[1];
	b = gspca_dev->usb_buf[2];
	r = ((r << 8) - (r << 4) - (r << 3)) >> 10;
	b = ((b << 7) >> 10);
	g = ((g << 9) + (g << 7) + (g << 5)) >> 10;
	luma = LIMIT(r + g + b);
	gspca_dbg(gspca_dev, D_FRAM, "Etoms luma G %d\n", luma);
	अगर (luma < luma_mean - luma_delta || luma > luma_mean + luma_delta) अणु
		Gbright += (luma_mean - luma) >> spring;
		Gbright = BLIMIT(Gbright);
		gspca_dbg(gspca_dev, D_FRAM, "Etoms Gbright %d\n", Gbright);
		Et_setgainG(gspca_dev, (__u8) Gbright);
	पूर्ण
पूर्ण

#अघोषित BLIMIT
#अघोषित LIMIT

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	पूर्णांक seqframe;

	seqframe = data[0] & 0x3f;
	len = (पूर्णांक) (((data[0] & 0xc0) << 2) | data[1]);
	अगर (seqframe == 0x3f) अणु
		gspca_dbg(gspca_dev, D_FRAM,
			  "header packet found datalength %d !!\n", len);
		gspca_dbg(gspca_dev, D_FRAM, "G %d R %d G %d B %d",
			  data[2], data[3], data[4], data[5]);
		data += 30;
		/* करोn't change datalength as the chips provided it */
		gspca_frame_add(gspca_dev, LAST_PACKET, शून्य, 0);
		gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
		वापस;
	पूर्ण
	अगर (len) अणु
		data += 8;
		gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
	पूर्ण अन्यथा अणु			/* Drop Packet */
		gspca_dev->last_packet_type = DISCARD_PACKET;
	पूर्ण
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
		setcontrast(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		setcolors(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		sd->स्वतःgain = ctrl->val;
		setस्वतःgain(gspca_dev);
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

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 1, 127, 1, 63);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 127);
	अगर (sd->sensor == SENSOR_PAS106)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SATURATION, 0, 15, 1, 7);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
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
	.pkt_scan = sd_pkt_scan,
	.dq_callback = करो_स्वतःgain,
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x102c, 0x6151), .driver_info = SENSOR_PAS106पूर्ण,
	अणुUSB_DEVICE(0x102c, 0x6251), .driver_info = SENSOR_TAS5130CXXपूर्ण,
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
