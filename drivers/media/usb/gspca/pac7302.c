<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Pixart PAC7302 driver
 *
 * Copyright (C) 2008-2012 Jean-Francois Moine <http://moinejf.मुक्त.fr>
 * Copyright (C) 2005 Thomas Kaiser thomas@kaiser-linux.li
 *
 * Separated from Pixart PAC7311 library by Mथँrton Nथऊmeth
 * Camera button input handling by Mथँrton Nथऊmeth <nm127@मुक्तmail.hu>
 * Copyright (C) 2009-2010 Mथँrton Nथऊmeth <nm127@मुक्तmail.hu>
 */

/*
 * Some करोcumentation about various रेजिस्टरs as determined by trial and error.
 *
 * Register page 0:
 *
 * Address	Description
 * 0x01		Red balance control
 * 0x02		Green balance control
 * 0x03		Blue balance control
 *		     The Winकरोws driver uses a quadratic approach to map
 *		     the settable values (0-200) on रेजिस्टर values:
 *		     min=0x20, शेष=0x40, max=0x80
 * 0x0f-0x20	Color and saturation control
 * 0xa2-0xab	Brightness, contrast and gamma control
 * 0xb6		Sharpness control (bits 0-4)
 *
 * Register page 1:
 *
 * Address	Description
 * 0x78		Global control, bit 6 controls the LED (inverted)
 * 0x80		Compression balance, 2 पूर्णांकeresting settings:
 *		0x0f Default
 *		0x50 Values >= this चयन the camera to a lower compression,
 *		     using the same table क्रम both luminance and chrominance.
 *		     This gives a sharper picture. Only usable when running
 *		     at < 15 fps! Note currently the driver करोes not use this
 *		     as the quality gain is small and the generated JPG-s are
 *		     only understood by v4l-utils >= 0.8.9
 *
 * Register page 3:
 *
 * Address	Description
 * 0x02		Clock भागider 3-63, fps = 90 / val. Must be a multiple of 3 on
 *		the 7302, so one of 3, 6, 9, ..., except when between 6 and 12?
 * 0x03		Variable framerate ctrl reg2==3: 0 -> ~30 fps, 255 -> ~22fps
 * 0x04		Another var framerate ctrl reg2==3, reg3==0: 0 -> ~30 fps,
 *		63 -> ~27 fps, the 2 msb's must always be 1 !!
 * 0x05		Another var framerate ctrl reg2==3, reg3==0, reg4==0xc0:
 *		1 -> ~30 fps, 2 -> ~20 fps
 * 0x0e		Exposure bits 0-7, 0-448, 0 = use full frame समय
 * 0x0f		Exposure bit 8, 0-448, 448 = no exposure at all
 * 0x10		Gain 0-31
 * 0x12		Another gain 0-31, unlike 0x10 this one seems to start with an
 *		amplअगरication value of 1 rather then 0 at its lowest setting
 * 0x21		Bitfield: 0-1 unused, 2-3 vflip/hflip, 4-5 unknown, 6-7 unused
 * 0x80		Another framerate control, best left at 1, moving it from 1 to
 *		2 causes the framerate to become 3/4th of what it was, and
 *		also seems to cause pixel averaging, resulting in an effective
 *		resolution of 320x240 and thus a much blockier image
 *
 * The रेजिस्टरs are accessed in the following functions:
 *
 * Page | Register   | Function
 * -----+------------+---------------------------------------------------
 *  0   | 0x01       | setredbalance()
 *  0   | 0x03       | setbluebalance()
 *  0   | 0x0f..0x20 | setcolors()
 *  0   | 0xa2..0xab | setbrightcont()
 *  0   | 0xb6       | setsharpness()
 *  0   | 0xc6       | setwhitebalance()
 *  0   | 0xdc       | setbrightcont(), setcolors()
 *  3   | 0x02       | setexposure()
 *  3   | 0x10, 0x12 | setgain()
 *  3   | 0x11       | setcolors(), setgain(), setexposure(), sethvflip()
 *  3   | 0x21       | sethvflip()
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/input.h>
#समावेश "gspca.h"
/* Include pac common sof detection functions */
#समावेश "pac_common.h"

#घोषणा PAC7302_RGB_BALANCE_MIN		  0
#घोषणा PAC7302_RGB_BALANCE_MAX		200
#घोषणा PAC7302_RGB_BALANCE_DEFAULT	100
#घोषणा PAC7302_GAIN_DEFAULT		 15
#घोषणा PAC7302_GAIN_KNEE		 42
#घोषणा PAC7302_EXPOSURE_DEFAULT	 66 /* 33 ms / 30 fps */
#घोषणा PAC7302_EXPOSURE_KNEE		133 /* 66 ms / 15 fps */

MODULE_AUTHOR("Jean-Francois Moine <http://moinejf.free.fr>, Thomas Kaiser thomas@kaiser-linux.li");
MODULE_DESCRIPTION("Pixart PAC7302");
MODULE_LICENSE("GPL");

काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;		/* !! must be the first item */

	काष्ठा अणु /* brightness / contrast cluster */
		काष्ठा v4l2_ctrl *brightness;
		काष्ठा v4l2_ctrl *contrast;
	पूर्ण;
	काष्ठा v4l2_ctrl *saturation;
	काष्ठा v4l2_ctrl *white_balance;
	काष्ठा v4l2_ctrl *red_balance;
	काष्ठा v4l2_ctrl *blue_balance;
	काष्ठा अणु /* flip cluster */
		काष्ठा v4l2_ctrl *hflip;
		काष्ठा v4l2_ctrl *vflip;
	पूर्ण;
	काष्ठा v4l2_ctrl *sharpness;
	u8 flags;
#घोषणा FL_HFLIP 0x01		/* mirrored by शेष */
#घोषणा FL_VFLIP 0x02		/* vertical flipped by शेष */

	u8 sof_पढ़ो;
	s8 स्वतःgain_ignore_frames;

	atomic_t avg_lum;
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु640, 480, V4L2_PIX_FMT_PJPG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
	पूर्ण,
पूर्ण;

#घोषणा LOAD_PAGE3		255
#घोषणा END_OF_SEQUENCE		0

अटल स्थिर u8 init_7302[] = अणु
/*	index,value */
	0xff, 0x01,		/* page 1 */
	0x78, 0x00,		/* deactivate */
	0xff, 0x01,
	0x78, 0x40,		/* led off */
पूर्ण;
अटल स्थिर u8 start_7302[] = अणु
/*	index, len, [value]* */
	0xff, 1,	0x00,		/* page 0 */
	0x00, 12,	0x01, 0x40, 0x40, 0x40, 0x01, 0xe0, 0x02, 0x80,
			0x00, 0x00, 0x00, 0x00,
	0x0d, 24,	0x03, 0x01, 0x00, 0xb5, 0x07, 0xcb, 0x00, 0x00,
			0x07, 0xc8, 0x00, 0xea, 0x07, 0xcf, 0x07, 0xf7,
			0x07, 0x7e, 0x01, 0x0b, 0x00, 0x00, 0x00, 0x11,
	0x26, 2,	0xaa, 0xaa,
	0x2e, 1,	0x31,
	0x38, 1,	0x01,
	0x3a, 3,	0x14, 0xff, 0x5a,
	0x43, 11,	0x00, 0x0a, 0x18, 0x11, 0x01, 0x2c, 0x88, 0x11,
			0x00, 0x54, 0x11,
	0x55, 1,	0x00,
	0x62, 4,	0x10, 0x1e, 0x1e, 0x18,
	0x6b, 1,	0x00,
	0x6e, 3,	0x08, 0x06, 0x00,
	0x72, 3,	0x00, 0xff, 0x00,
	0x7d, 23,	0x01, 0x01, 0x58, 0x46, 0x50, 0x3c, 0x50, 0x3c,
			0x54, 0x46, 0x54, 0x56, 0x52, 0x50, 0x52, 0x50,
			0x56, 0x64, 0xa4, 0x00, 0xda, 0x00, 0x00,
	0xa2, 10,	0x22, 0x2c, 0x3c, 0x54, 0x69, 0x7c, 0x9c, 0xb9,
			0xd2, 0xeb,
	0xaf, 1,	0x02,
	0xb5, 2,	0x08, 0x08,
	0xb8, 2,	0x08, 0x88,
	0xc4, 4,	0xae, 0x01, 0x04, 0x01,
	0xcc, 1,	0x00,
	0xd1, 11,	0x01, 0x30, 0x49, 0x5e, 0x6f, 0x7f, 0x8e, 0xa9,
			0xc1, 0xd7, 0xec,
	0xdc, 1,	0x01,
	0xff, 1,	0x01,		/* page 1 */
	0x12, 3,	0x02, 0x00, 0x01,
	0x3e, 2,	0x00, 0x00,
	0x76, 5,	0x01, 0x20, 0x40, 0x00, 0xf2,
	0x7c, 1,	0x00,
	0x7f, 10,	0x4b, 0x0f, 0x01, 0x2c, 0x02, 0x58, 0x03, 0x20,
			0x02, 0x00,
	0x96, 5,	0x01, 0x10, 0x04, 0x01, 0x04,
	0xc8, 14,	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00,
			0x07, 0x00, 0x01, 0x07, 0x04, 0x01,
	0xd8, 1,	0x01,
	0xdb, 2,	0x00, 0x01,
	0xde, 7,	0x00, 0x01, 0x04, 0x04, 0x00, 0x00, 0x00,
	0xe6, 4,	0x00, 0x00, 0x00, 0x01,
	0xeb, 1,	0x00,
	0xff, 1,	0x02,		/* page 2 */
	0x22, 1,	0x00,
	0xff, 1,	0x03,		/* page 3 */
	0, LOAD_PAGE3,			/* load the page 3 */
	0x11, 1,	0x01,
	0xff, 1,	0x02,		/* page 2 */
	0x13, 1,	0x00,
	0x22, 4,	0x1f, 0xa4, 0xf0, 0x96,
	0x27, 2,	0x14, 0x0c,
	0x2a, 5,	0xc8, 0x00, 0x18, 0x12, 0x22,
	0x64, 8,	0x00, 0x00, 0xf0, 0x01, 0x14, 0x44, 0x44, 0x44,
	0x6e, 1,	0x08,
	0xff, 1,	0x01,		/* page 1 */
	0x78, 1,	0x00,
	0, END_OF_SEQUENCE		/* end of sequence */
पूर्ण;

#घोषणा SKIP		0xaa
/* page 3 - the value SKIP says skip the index - see reg_w_page() */
अटल स्थिर u8 page3_7302[] = अणु
	0x90, 0x40, 0x03, 0x00, 0xc0, 0x01, 0x14, 0x16,
	0x14, 0x12, 0x00, 0x00, 0x00, 0x02, 0x33, 0x00,
	0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x47, 0x01, 0xb3, 0x01, 0x00,
	0x00, 0x08, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x21,
	0x00, 0x00, 0x00, 0x54, 0xf4, 0x02, 0x52, 0x54,
	0xa4, 0xb8, 0xe0, 0x2a, 0xf6, 0x00, 0x00, 0x00,
	0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xfc, 0x00, 0xf2, 0x1f, 0x04, 0x00, 0x00,
	SKIP, 0x00, 0x00, 0xc0, 0xc0, 0x10, 0x00, 0x00,
	0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x40, 0xff, 0x03, 0x19, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0xc8, 0xc8,
	0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50,
	0x08, 0x10, 0x24, 0x40, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x02, 0x47, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x02, 0xfa, 0x00, 0x64, 0x5a, 0x28, 0x00,
	0x00
पूर्ण;

अटल व्योम reg_w_buf(काष्ठा gspca_dev *gspca_dev,
		u8 index,
		  स्थिर u8 *buffer, पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	स_नकल(gspca_dev->usb_buf, buffer, len);
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0,		/* request */
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,		/* value */
			index, gspca_dev->usb_buf, len,
			500);
	अगर (ret < 0) अणु
		pr_err("reg_w_buf failed i: %02x error %d\n",
		       index, ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण


अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev,
		u8 index,
		u8 value)
अणु
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	gspca_dev->usb_buf[0] = value;
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0,			/* request */
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, index, gspca_dev->usb_buf, 1,
			500);
	अगर (ret < 0) अणु
		pr_err("reg_w() failed i: %02x v: %02x error %d\n",
		       index, value, ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

अटल व्योम reg_w_seq(काष्ठा gspca_dev *gspca_dev,
		स्थिर u8 *seq, पूर्णांक len)
अणु
	जबतक (--len >= 0) अणु
		reg_w(gspca_dev, seq[0], seq[1]);
		seq += 2;
	पूर्ण
पूर्ण

/* load the beginning of a page */
अटल व्योम reg_w_page(काष्ठा gspca_dev *gspca_dev,
			स्थिर u8 *page, पूर्णांक len)
अणु
	पूर्णांक index;
	पूर्णांक ret = 0;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	क्रम (index = 0; index < len; index++) अणु
		अगर (page[index] == SKIP)		/* skip this index */
			जारी;
		gspca_dev->usb_buf[0] = page[index];
		ret = usb_control_msg(gspca_dev->dev,
				usb_sndctrlpipe(gspca_dev->dev, 0),
				0,			/* request */
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0, index, gspca_dev->usb_buf, 1,
				500);
		अगर (ret < 0) अणु
			pr_err("reg_w_page() failed i: %02x v: %02x error %d\n",
			       index, page[index], ret);
			gspca_dev->usb_err = ret;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* output a variable sequence */
अटल व्योम reg_w_var(काष्ठा gspca_dev *gspca_dev,
			स्थिर u8 *seq,
			स्थिर u8 *page3, अचिन्हित पूर्णांक page3_len)
अणु
	पूर्णांक index, len;

	क्रम (;;) अणु
		index = *seq++;
		len = *seq++;
		चयन (len) अणु
		हाल END_OF_SEQUENCE:
			वापस;
		हाल LOAD_PAGE3:
			reg_w_page(gspca_dev, page3, page3_len);
			अवरोध;
		शेष:
			अगर (len > USB_BUF_SZ) अणु
				gspca_err(gspca_dev, "Incorrect variable sequence\n");
				वापस;
			पूर्ण
			जबतक (len > 0) अणु
				अगर (len < 8) अणु
					reg_w_buf(gspca_dev,
						index, seq, len);
					seq += len;
					अवरोध;
				पूर्ण
				reg_w_buf(gspca_dev, index, seq, 8);
				seq += 8;
				index += 8;
				len -= 8;
			पूर्ण
		पूर्ण
	पूर्ण
	/* not reached */
पूर्ण

/* this function is called at probe समय क्रम pac7302 */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;

	cam = &gspca_dev->cam;

	cam->cam_mode = vga_mode;	/* only 640x480 */
	cam->nmodes = ARRAY_SIZE(vga_mode);

	sd->flags = id->driver_info;
	वापस 0;
पूर्ण

अटल व्योम setbrightcont(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक i, v;
	अटल स्थिर u8 max[10] =
		अणु0x29, 0x33, 0x42, 0x5a, 0x6e, 0x80, 0x9f, 0xbb,
		 0xd4, 0xecपूर्ण;
	अटल स्थिर u8 delta[10] =
		अणु0x35, 0x33, 0x33, 0x2f, 0x2a, 0x25, 0x1e, 0x17,
		 0x11, 0x0bपूर्ण;

	reg_w(gspca_dev, 0xff, 0x00);		/* page 0 */
	क्रम (i = 0; i < 10; i++) अणु
		v = max[i];
		v += (sd->brightness->val - (s32)sd->brightness->maximum)
			* 150 / (s32)sd->brightness->maximum; /* 200 ? */
		v -= delta[i] * sd->contrast->val / (s32)sd->contrast->maximum;
		अगर (v < 0)
			v = 0;
		अन्यथा अगर (v > 0xff)
			v = 0xff;
		reg_w(gspca_dev, 0xa2 + i, v);
	पूर्ण
	reg_w(gspca_dev, 0xdc, 0x01);
पूर्ण

अटल व्योम setcolors(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक i, v;
	अटल स्थिर पूर्णांक a[9] =
		अणु217, -212, 0, -101, 170, -67, -38, -315, 355पूर्ण;
	अटल स्थिर पूर्णांक b[9] =
		अणु19, 106, 0, 19, 106, 1, 19, 106, 1पूर्ण;

	reg_w(gspca_dev, 0xff, 0x03);			/* page 3 */
	reg_w(gspca_dev, 0x11, 0x01);
	reg_w(gspca_dev, 0xff, 0x00);			/* page 0 */
	क्रम (i = 0; i < 9; i++) अणु
		v = a[i] * sd->saturation->val / (s32)sd->saturation->maximum;
		v += b[i];
		reg_w(gspca_dev, 0x0f + 2 * i, (v >> 8) & 0x07);
		reg_w(gspca_dev, 0x0f + 2 * i + 1, v);
	पूर्ण
	reg_w(gspca_dev, 0xdc, 0x01);
पूर्ण

अटल व्योम setwhitebalance(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	reg_w(gspca_dev, 0xff, 0x00);		/* page 0 */
	reg_w(gspca_dev, 0xc6, sd->white_balance->val);

	reg_w(gspca_dev, 0xdc, 0x01);
पूर्ण

अटल u8 rgbbalance_ctrl_to_reg_value(s32 rgb_ctrl_val)
अणु
	स्थिर अचिन्हित पूर्णांक k = 1000;	/* precision factor */
	अचिन्हित पूर्णांक norm;

	/* Normed value [0...k] */
	norm = k * (rgb_ctrl_val - PAC7302_RGB_BALANCE_MIN)
		    / (PAC7302_RGB_BALANCE_MAX - PAC7302_RGB_BALANCE_MIN);
	/* Qudratic apporach improves control at small (रेजिस्टर) values: */
	वापस 64 * norm * norm / (k*k)  +  32 * norm / k  +  32;
	/* Y = 64*X*X + 32*X + 32
	 * => रेजिस्टर values 0x20-0x80; Winकरोws driver uses these limits */

	/* NOTE: क्रम full value range (0x00-0xff) use
	 *         Y = 254*X*X + X
	 *         => 254 * norm * norm / (k*k)  +  1 * norm / k	*/
पूर्ण

अटल व्योम setredbalance(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	reg_w(gspca_dev, 0xff, 0x00);			/* page 0 */
	reg_w(gspca_dev, 0x01,
	      rgbbalance_ctrl_to_reg_value(sd->red_balance->val));

	reg_w(gspca_dev, 0xdc, 0x01);
पूर्ण

अटल व्योम setbluebalance(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	reg_w(gspca_dev, 0xff, 0x00);			/* page 0 */
	reg_w(gspca_dev, 0x03,
	      rgbbalance_ctrl_to_reg_value(sd->blue_balance->val));

	reg_w(gspca_dev, 0xdc, 0x01);
पूर्ण

अटल व्योम setgain(काष्ठा gspca_dev *gspca_dev)
अणु
	u8 reg10, reg12;

	अगर (gspca_dev->gain->val < 32) अणु
		reg10 = gspca_dev->gain->val;
		reg12 = 0;
	पूर्ण अन्यथा अणु
		reg10 = 31;
		reg12 = gspca_dev->gain->val - 31;
	पूर्ण

	reg_w(gspca_dev, 0xff, 0x03);			/* page 3 */
	reg_w(gspca_dev, 0x10, reg10);
	reg_w(gspca_dev, 0x12, reg12);

	/* load रेजिस्टरs to sensor (Bit 0, स्वतः clear) */
	reg_w(gspca_dev, 0x11, 0x01);
पूर्ण

अटल व्योम setexposure(काष्ठा gspca_dev *gspca_dev)
अणु
	u8 घड़ीभाग;
	u16 exposure;

	/*
	 * Register 2 of frame 3 contains the घड़ी भागider configuring the
	 * no fps according to the क्रमmula: 90 / reg. sd->exposure is the
	 * desired exposure समय in 0.5 ms.
	 */
	घड़ीभाग = (90 * gspca_dev->exposure->val + 1999) / 2000;

	/*
	 * Note घड़ीभाग = 3 also works, but when running at 30 fps, depending
	 * on the scene being recorded, the camera चयनes to another
	 * quantization table क्रम certain JPEG blocks, and we करोn't know how
	 * to decompress these blocks. So we cap the framerate at 15 fps.
	 */
	अगर (घड़ीभाग < 6)
		घड़ीभाग = 6;
	अन्यथा अगर (घड़ीभाग > 63)
		घड़ीभाग = 63;

	/*
	 * Register 2 MUST be a multiple of 3, except when between 6 and 12?
	 * Always round up, otherwise we cannot get the desired frameसमय
	 * using the partial frame समय exposure control.
	 */
	अगर (घड़ीभाग < 6 || घड़ीभाग > 12)
		घड़ीभाग = ((घड़ीभाग + 2) / 3) * 3;

	/*
	 * frame exposure समय in ms = 1000 * घड़ीभाग / 90    ->
	 * exposure = (sd->exposure / 2) * 448 / (1000 * घड़ीभाग / 90)
	 */
	exposure = (gspca_dev->exposure->val * 45 * 448) / (1000 * घड़ीभाग);
	/* 0 = use full frameसमय, 448 = no exposure, reverse it */
	exposure = 448 - exposure;

	reg_w(gspca_dev, 0xff, 0x03);			/* page 3 */
	reg_w(gspca_dev, 0x02, घड़ीभाग);
	reg_w(gspca_dev, 0x0e, exposure & 0xff);
	reg_w(gspca_dev, 0x0f, exposure >> 8);

	/* load रेजिस्टरs to sensor (Bit 0, स्वतः clear) */
	reg_w(gspca_dev, 0x11, 0x01);
पूर्ण

अटल व्योम sethvflip(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 data, hflip, vflip;

	hflip = sd->hflip->val;
	अगर (sd->flags & FL_HFLIP)
		hflip = !hflip;
	vflip = sd->vflip->val;
	अगर (sd->flags & FL_VFLIP)
		vflip = !vflip;

	reg_w(gspca_dev, 0xff, 0x03);			/* page 3 */
	data = (hflip ? 0x08 : 0x00) | (vflip ? 0x04 : 0x00);
	reg_w(gspca_dev, 0x21, data);

	/* load रेजिस्टरs to sensor (Bit 0, स्वतः clear) */
	reg_w(gspca_dev, 0x11, 0x01);
पूर्ण

अटल व्योम setsharpness(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	reg_w(gspca_dev, 0xff, 0x00);		/* page 0 */
	reg_w(gspca_dev, 0xb6, sd->sharpness->val);

	reg_w(gspca_dev, 0xdc, 0x01);
पूर्ण

/* this function is called at probe and resume समय क्रम pac7302 */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_w_seq(gspca_dev, init_7302, माप(init_7302)/2);
	वापस gspca_dev->usb_err;
पूर्ण

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	gspca_dev->usb_err = 0;

	अगर (ctrl->id == V4L2_CID_AUTOGAIN && ctrl->is_new && ctrl->val) अणु
		/* when चयनing to स्वतःgain set शेषs to make sure
		   we are on a valid poपूर्णांक of the स्वतःgain gain /
		   exposure knee graph, and give this change समय to
		   take effect beक्रमe करोing स्वतःgain. */
		gspca_dev->exposure->val    = PAC7302_EXPOSURE_DEFAULT;
		gspca_dev->gain->val        = PAC7302_GAIN_DEFAULT;
		sd->स्वतःgain_ignore_frames  = PAC_AUTOGAIN_IGNORE_FRAMES;
	पूर्ण

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		setbrightcont(gspca_dev);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		setcolors(gspca_dev);
		अवरोध;
	हाल V4L2_CID_WHITE_BALANCE_TEMPERATURE:
		setwhitebalance(gspca_dev);
		अवरोध;
	हाल V4L2_CID_RED_BALANCE:
		setredbalance(gspca_dev);
		अवरोध;
	हाल V4L2_CID_BLUE_BALANCE:
		setbluebalance(gspca_dev);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		अगर (gspca_dev->exposure->is_new || (ctrl->is_new && ctrl->val))
			setexposure(gspca_dev);
		अगर (gspca_dev->gain->is_new || (ctrl->is_new && ctrl->val))
			setgain(gspca_dev);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		sethvflip(gspca_dev);
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		setsharpness(gspca_dev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

/* this function is called at probe समय */
अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 12);

	sd->brightness = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_BRIGHTNESS, 0, 32, 1, 16);
	sd->contrast = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_CONTRAST, 0, 255, 1, 127);

	sd->saturation = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_SATURATION, 0, 255, 1, 127);
	sd->white_balance = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_WHITE_BALANCE_TEMPERATURE,
					0, 255, 1, 55);
	sd->red_balance = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_RED_BALANCE,
					PAC7302_RGB_BALANCE_MIN,
					PAC7302_RGB_BALANCE_MAX,
					1, PAC7302_RGB_BALANCE_DEFAULT);
	sd->blue_balance = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_BLUE_BALANCE,
					PAC7302_RGB_BALANCE_MIN,
					PAC7302_RGB_BALANCE_MAX,
					1, PAC7302_RGB_BALANCE_DEFAULT);

	gspca_dev->स्वतःgain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	gspca_dev->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_EXPOSURE, 0, 1023, 1,
					PAC7302_EXPOSURE_DEFAULT);
	gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_GAIN, 0, 62, 1,
					PAC7302_GAIN_DEFAULT);

	sd->hflip = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
		V4L2_CID_HFLIP, 0, 1, 1, 0);
	sd->vflip = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
		V4L2_CID_VFLIP, 0, 1, 1, 0);

	sd->sharpness = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_SHARPNESS, 0, 15, 1, 8);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण

	v4l2_ctrl_cluster(2, &sd->brightness);
	v4l2_ctrl_स्वतः_cluster(3, &gspca_dev->स्वतःgain, 0, false);
	v4l2_ctrl_cluster(2, &sd->hflip);
	वापस 0;
पूर्ण

/* -- start the camera -- */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	reg_w_var(gspca_dev, start_7302,
		page3_7302, माप(page3_7302));

	sd->sof_पढ़ो = 0;
	sd->स्वतःgain_ignore_frames = 0;
	atomic_set(&sd->avg_lum, 270 + sd->brightness->val);

	/* start stream */
	reg_w(gspca_dev, 0xff, 0x01);
	reg_w(gspca_dev, 0x78, 0x01);

	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु

	/* stop stream */
	reg_w(gspca_dev, 0xff, 0x01);
	reg_w(gspca_dev, 0x78, 0x00);
पूर्ण

/* called on streamoff with alt 0 and on disconnect क्रम pac7302 */
अटल व्योम sd_stop0(काष्ठा gspca_dev *gspca_dev)
अणु
	अगर (!gspca_dev->present)
		वापस;
	reg_w(gspca_dev, 0xff, 0x01);
	reg_w(gspca_dev, 0x78, 0x40);
पूर्ण

अटल व्योम करो_स्वतःgain(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक avg_lum = atomic_पढ़ो(&sd->avg_lum);
	पूर्णांक desired_lum;
	स्थिर पूर्णांक deadzone = 30;

	अगर (sd->स्वतःgain_ignore_frames < 0)
		वापस;

	अगर (sd->स्वतःgain_ignore_frames > 0) अणु
		sd->स्वतःgain_ignore_frames--;
	पूर्ण अन्यथा अणु
		desired_lum = 270 + sd->brightness->val;

		अगर (gspca_expo_स्वतःgain(gspca_dev, avg_lum, desired_lum,
					deadzone, PAC7302_GAIN_KNEE,
					PAC7302_EXPOSURE_KNEE))
			sd->स्वतःgain_ignore_frames =
						PAC_AUTOGAIN_IGNORE_FRAMES;
	पूर्ण
पूर्ण

/* JPEG header */
अटल स्थिर u8 jpeg_header[] = अणु
	0xff, 0xd8,	/* SOI: Start of Image */

	0xff, 0xc0,	/* SOF0: Start of Frame (Baseline DCT) */
	0x00, 0x11,	/* length = 17 bytes (including this length field) */
	0x08,		/* Precision: 8 */
	0x02, 0x80,	/* height = 640 (image rotated) */
	0x01, 0xe0,	/* width = 480 */
	0x03,		/* Number of image components: 3 */
	0x01, 0x21, 0x00, /* ID=1, Subsampling 1x1, Quantization table: 0 */
	0x02, 0x11, 0x01, /* ID=2, Subsampling 2x1, Quantization table: 1 */
	0x03, 0x11, 0x01, /* ID=3, Subsampling 2x1, Quantization table: 1 */

	0xff, 0xda,	/* SOS: Start Of Scan */
	0x00, 0x0c,	/* length = 12 bytes (including this length field) */
	0x03,		/* number of components: 3 */
	0x01, 0x00,	/* selector 1, table 0x00 */
	0x02, 0x11,	/* selector 2, table 0x11 */
	0x03, 0x11,	/* selector 3, table 0x11 */
	0x00, 0x3f,	/* Spectral selection: 0 .. 63 */
	0x00		/* Successive approximation: 0 */
पूर्ण;

/* this function is run at पूर्णांकerrupt level */
अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 *image;
	u8 *sof;

	sof = pac_find_sof(gspca_dev, &sd->sof_पढ़ो, data, len);
	अगर (sof) अणु
		पूर्णांक n, lum_offset, footer_length;

		/*
		 * 6 bytes after the FF D9 खातापूर्ण marker a number of lumination
		 * bytes are send corresponding to dअगरferent parts of the
		 * image, the 14th and 15th byte after the खातापूर्ण seem to
		 * correspond to the center of the image.
		 */
		lum_offset = 61 + माप pac_sof_marker;
		footer_length = 74;

		/* Finish decoding current frame */
		n = (sof - data) - (footer_length + माप pac_sof_marker);
		अगर (n < 0) अणु
			gspca_dev->image_len += n;
			n = 0;
		पूर्ण अन्यथा अणु
			gspca_frame_add(gspca_dev, INTER_PACKET, data, n);
		पूर्ण

		image = gspca_dev->image;
		अगर (image != शून्य
		 && image[gspca_dev->image_len - 2] == 0xff
		 && image[gspca_dev->image_len - 1] == 0xd9)
			gspca_frame_add(gspca_dev, LAST_PACKET, शून्य, 0);

		n = sof - data;
		len -= n;
		data = sof;

		/* Get average lumination */
		अगर (gspca_dev->last_packet_type == LAST_PACKET &&
				n >= lum_offset)
			atomic_set(&sd->avg_lum, data[-lum_offset] +
						data[-lum_offset + 1]);

		/* Start the new frame with the jpeg header */
		/* The PAC7302 has the image rotated 90 degrees */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
				jpeg_header, माप jpeg_header);
	पूर्ण
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक sd_dbg_s_रेजिस्टर(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	u8 index;
	u8 value;

	/*
	 * reg->reg: bit0..15: reserved क्रम रेजिस्टर index (wIndex is 16bit
	 *		       दीर्घ on the USB bus)
	 */
	अगर (reg->match.addr == 0 &&
	    (reg->reg < 0x000000ff) &&
	    (reg->val <= 0x000000ff)
	) अणु
		/* Currently writing to page 0 is only supported. */
		/* reg_w() only supports 8bit index */
		index = reg->reg;
		value = reg->val;

		/*
		 * Note that there shall be no access to other page
		 * by any other function between the page चयन and
		 * the actual रेजिस्टर ग_लिखो.
		 */
		reg_w(gspca_dev, 0xff, 0x00);		/* page 0 */
		reg_w(gspca_dev, index, value);

		reg_w(gspca_dev, 0xdc, 0x01);
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_INPUT)
अटल पूर्णांक sd_पूर्णांक_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,		/* पूर्णांकerrupt packet data */
			पूर्णांक len)		/* पूर्णांकerrupt packet length */
अणु
	पूर्णांक ret = -EINVAL;
	u8 data0, data1;

	अगर (len == 2) अणु
		data0 = data[0];
		data1 = data[1];
		अगर ((data0 == 0x00 && data1 == 0x11) ||
		    (data0 == 0x22 && data1 == 0x33) ||
		    (data0 == 0x44 && data1 == 0x55) ||
		    (data0 == 0x66 && data1 == 0x77) ||
		    (data0 == 0x88 && data1 == 0x99) ||
		    (data0 == 0xaa && data1 == 0xbb) ||
		    (data0 == 0xcc && data1 == 0xdd) ||
		    (data0 == 0xee && data1 == 0xff)) अणु
			input_report_key(gspca_dev->input_dev, KEY_CAMERA, 1);
			input_sync(gspca_dev->input_dev);
			input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
			input_sync(gspca_dev->input_dev);
			ret = 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

/* sub-driver description क्रम pac7302 */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = KBUILD_MODNAME,
	.config = sd_config,
	.init = sd_init,
	.init_controls = sd_init_controls,
	.start = sd_start,
	.stopN = sd_stopN,
	.stop0 = sd_stop0,
	.pkt_scan = sd_pkt_scan,
	.dq_callback = करो_स्वतःgain,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.set_रेजिस्टर = sd_dbg_s_रेजिस्टर,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_INPUT)
	.पूर्णांक_pkt_scan = sd_पूर्णांक_pkt_scan,
#पूर्ण_अगर
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x06f8, 0x3009)पूर्ण,
	अणुUSB_DEVICE(0x06f8, 0x301b)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2620)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2621)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2622), .driver_info = FL_VFLIPपूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2623), .driver_info = FL_VFLIPपूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2624), .driver_info = FL_VFLIPपूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2625)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2626)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2627), .driver_info = FL_VFLIPपूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2628)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2629), .driver_info = FL_VFLIPपूर्ण,
	अणुUSB_DEVICE(0x093a, 0x262a)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x262c)पूर्ण,
	अणुUSB_DEVICE(0x145f, 0x013c)पूर्ण,
	अणुUSB_DEVICE(0x1ae7, 0x2001)पूर्ण, /* SpeedLink Snappy Mic SL-6825-SBK */
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
	.name = KBUILD_MODNAME,
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
