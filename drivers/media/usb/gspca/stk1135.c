<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Syntek STK1135 subdriver
 *
 * Copyright (c) 2013 Ondrej Zary
 *
 * Based on Syntekdriver (stk11xx) by Nicolas VIVIEN:
 *   http://syntekdriver.sourceक्रमge.net
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "stk1135"

#समावेश "gspca.h"
#समावेश "stk1135.h"

MODULE_AUTHOR("Ondrej Zary");
MODULE_DESCRIPTION("Syntek STK1135 USB Camera Driver");
MODULE_LICENSE("GPL");


/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	u8 pkt_seq;
	u8 sensor_page;

	bool flip_status;
	u8 flip_debounce;

	काष्ठा v4l2_ctrl *hflip;
	काष्ठा v4l2_ctrl *vflip;
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat stk1135_modes[] = अणु
	/* शेष mode (this driver supports variable resolution) */
	अणु640, 480, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
पूर्ण;

/* -- पढ़ो a रेजिस्टर -- */
अटल u8 reg_r(काष्ठा gspca_dev *gspca_dev, u16 index)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस 0;
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			0x00,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0x00,
			index,
			gspca_dev->usb_buf, 1,
			500);

	gspca_dbg(gspca_dev, D_USBI, "reg_r 0x%x=0x%02x\n",
		  index, gspca_dev->usb_buf[0]);
	अगर (ret < 0) अणु
		pr_err("reg_r 0x%x err %d\n", index, ret);
		gspca_dev->usb_err = ret;
		वापस 0;
	पूर्ण

	वापस gspca_dev->usb_buf[0];
पूर्ण

/* -- ग_लिखो a रेजिस्टर -- */
अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev, u16 index, u8 val)
अणु
	पूर्णांक ret;
	काष्ठा usb_device *dev = gspca_dev->dev;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			0x01,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			val,
			index,
			शून्य,
			0,
			500);
	gspca_dbg(gspca_dev, D_USBO, "reg_w 0x%x:=0x%02x\n", index, val);
	अगर (ret < 0) अणु
		pr_err("reg_w 0x%x err %d\n", index, ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

अटल व्योम reg_w_mask(काष्ठा gspca_dev *gspca_dev, u16 index, u8 val, u8 mask)
अणु
	val = (reg_r(gspca_dev, index) & ~mask) | (val & mask);
	reg_w(gspca_dev, index, val);
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	gspca_dev->cam.cam_mode = stk1135_modes;
	gspca_dev->cam.nmodes = ARRAY_SIZE(stk1135_modes);
	वापस 0;
पूर्ण

अटल पूर्णांक stk1135_serial_रुको_पढ़ोy(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i = 0;
	u8 val;

	करो अणु
		val = reg_r(gspca_dev, STK1135_REG_SICTL + 1);
		अगर (i++ > 500) अणु /* maximum retry count */
			pr_err("serial bus timeout: status=0x%02x\n", val);
			वापस -1;
		पूर्ण
	/* repeat अगर BUSY or WRITE/READ not finished */
	पूर्ण जबतक ((val & 0x10) || !(val & 0x05));

	वापस 0;
पूर्ण

अटल u8 sensor_पढ़ो_8(काष्ठा gspca_dev *gspca_dev, u8 addr)
अणु
	reg_w(gspca_dev, STK1135_REG_SBUSR, addr);
	/* begin पढ़ो */
	reg_w(gspca_dev, STK1135_REG_SICTL, 0x20);
	/* रुको until finished */
	अगर (stk1135_serial_रुको_पढ़ोy(gspca_dev)) अणु
		pr_err("Sensor read failed\n");
		वापस 0;
	पूर्ण

	वापस reg_r(gspca_dev, STK1135_REG_SBUSR + 1);
पूर्ण

अटल u16 sensor_पढ़ो_16(काष्ठा gspca_dev *gspca_dev, u8 addr)
अणु
	वापस (sensor_पढ़ो_8(gspca_dev, addr) << 8) |
		sensor_पढ़ो_8(gspca_dev, 0xf1);
पूर्ण

अटल व्योम sensor_ग_लिखो_8(काष्ठा gspca_dev *gspca_dev, u8 addr, u8 data)
अणु
	/* load address and data रेजिस्टरs */
	reg_w(gspca_dev, STK1135_REG_SBUSW, addr);
	reg_w(gspca_dev, STK1135_REG_SBUSW + 1, data);
	/* begin ग_लिखो */
	reg_w(gspca_dev, STK1135_REG_SICTL, 0x01);
	/* रुको until finished */
	अगर (stk1135_serial_रुको_पढ़ोy(gspca_dev)) अणु
		pr_err("Sensor write failed\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम sensor_ग_लिखो_16(काष्ठा gspca_dev *gspca_dev, u8 addr, u16 data)
अणु
	sensor_ग_लिखो_8(gspca_dev, addr, data >> 8);
	sensor_ग_लिखो_8(gspca_dev, 0xf1, data & 0xff);
पूर्ण

अटल व्योम sensor_set_page(काष्ठा gspca_dev *gspca_dev, u8 page)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (page != sd->sensor_page) अणु
		sensor_ग_लिखो_16(gspca_dev, 0xf0, page);
		sd->sensor_page = page;
	पूर्ण
पूर्ण

अटल u16 sensor_पढ़ो(काष्ठा gspca_dev *gspca_dev, u16 reg)
अणु
	sensor_set_page(gspca_dev, reg >> 8);
	वापस sensor_पढ़ो_16(gspca_dev, reg & 0xff);
पूर्ण

अटल व्योम sensor_ग_लिखो(काष्ठा gspca_dev *gspca_dev, u16 reg, u16 val)
अणु
	sensor_set_page(gspca_dev, reg >> 8);
	sensor_ग_लिखो_16(gspca_dev, reg & 0xff, val);
पूर्ण

अटल व्योम sensor_ग_लिखो_mask(काष्ठा gspca_dev *gspca_dev,
			u16 reg, u16 val, u16 mask)
अणु
	val = (sensor_पढ़ो(gspca_dev, reg) & ~mask) | (val & mask);
	sensor_ग_लिखो(gspca_dev, reg, val);
पूर्ण

काष्ठा sensor_val अणु
	u16 reg;
	u16 val;
पूर्ण;

/* configure MT9M112 sensor */
अटल व्योम stk1135_configure_mt9m112(काष्ठा gspca_dev *gspca_dev)
अणु
	अटल स्थिर काष्ठा sensor_val cfg[] = अणु
		/* restart&reset, chip enable, reserved */
		अणु 0x00d, 0x000b पूर्ण, अणु 0x00d, 0x0008 पूर्ण, अणु 0x035, 0x0022 पूर्ण,
		/* mode ctl: AWB on, AE both, clip aper corr, defect corr, AE */
		अणु 0x106, 0x700e पूर्ण,

		अणु 0x2dd, 0x18e0 पूर्ण, /* B-R thresholds, */

		/* AWB */
		अणु 0x21f, 0x0180 पूर्ण, /* Cb and Cr limits */
		अणु 0x220, 0xc814 पूर्ण, अणु 0x221, 0x8080 पूर्ण, /* lum limits, RGB gain */
		अणु 0x222, 0xa078 पूर्ण, अणु 0x223, 0xa078 पूर्ण, /* R, B limit */
		अणु 0x224, 0x5f20 पूर्ण, अणु 0x228, 0xea02 पूर्ण, /* mtx adj lim, adv ctl */
		अणु 0x229, 0x867a पूर्ण, /* wide gates */

		/* Color correction */
		/* imager gains base, delta, delta signs */
		अणु 0x25e, 0x594c पूर्ण, अणु 0x25f, 0x4d51 पूर्ण, अणु 0x260, 0x0002 पूर्ण,
		/* AWB adv ctl 2, gain offs */
		अणु 0x2ef, 0x0008 पूर्ण, अणु 0x2f2, 0x0000 पूर्ण,
		/* base matrix signs, scale K1-5, K6-9 */
		अणु 0x202, 0x00ee पूर्ण, अणु 0x203, 0x3923 पूर्ण, अणु 0x204, 0x0724 पूर्ण,
		/* base matrix coef */
		अणु 0x209, 0x00cd पूर्ण, अणु 0x20a, 0x0093 पूर्ण, अणु 0x20b, 0x0004 पूर्ण,/*K1-3*/
		अणु 0x20c, 0x005c पूर्ण, अणु 0x20d, 0x00d9 पूर्ण, अणु 0x20e, 0x0053 पूर्ण,/*K4-6*/
		अणु 0x20f, 0x0008 पूर्ण, अणु 0x210, 0x0091 पूर्ण, अणु 0x211, 0x00cf पूर्ण,/*K7-9*/
		अणु 0x215, 0x0000 पूर्ण, /* delta mtx signs */
		/* delta matrix coef */
		अणु 0x216, 0x0000 पूर्ण, अणु 0x217, 0x0000 पूर्ण, अणु 0x218, 0x0000 पूर्ण,/*D1-3*/
		अणु 0x219, 0x0000 पूर्ण, अणु 0x21a, 0x0000 पूर्ण, अणु 0x21b, 0x0000 पूर्ण,/*D4-6*/
		अणु 0x21c, 0x0000 पूर्ण, अणु 0x21d, 0x0000 पूर्ण, अणु 0x21e, 0x0000 पूर्ण,/*D7-9*/
		/* enable & disable manual WB to apply color corr. settings */
		अणु 0x106, 0xf00e पूर्ण, अणु 0x106, 0x700e पूर्ण,

		/* Lens shading correction */
		अणु 0x180, 0x0007 पूर्ण, /* control */
		/* vertical knee 0, 2+1, 4+3 */
		अणु 0x181, 0xde13 पूर्ण, अणु 0x182, 0xebe2 पूर्ण, अणु 0x183, 0x00f6 पूर्ण, /* R */
		अणु 0x184, 0xe114 पूर्ण, अणु 0x185, 0xeadd पूर्ण, अणु 0x186, 0xfdf6 पूर्ण, /* G */
		अणु 0x187, 0xe511 पूर्ण, अणु 0x188, 0xede6 पूर्ण, अणु 0x189, 0xfbf7 पूर्ण, /* B */
		/* horizontal knee 0, 2+1, 4+3, 5 */
		अणु 0x18a, 0xd613 पूर्ण, अणु 0x18b, 0xedec पूर्ण, /* R .. */
		अणु 0x18c, 0xf9f2 पूर्ण, अणु 0x18d, 0x0000 पूर्ण, /* .. R */
		अणु 0x18e, 0xd815 पूर्ण, अणु 0x18f, 0xe9ea पूर्ण, /* G .. */
		अणु 0x190, 0xf9f1 पूर्ण, अणु 0x191, 0x0002 पूर्ण, /* .. G */
		अणु 0x192, 0xde10 पूर्ण, अणु 0x193, 0xefef पूर्ण, /* B .. */
		अणु 0x194, 0xfbf4 पूर्ण, अणु 0x195, 0x0002 पूर्ण, /* .. B */
		/* vertical knee 6+5, 8+7 */
		अणु 0x1b6, 0x0e06 पूर्ण, अणु 0x1b7, 0x2713 पूर्ण, /* R */
		अणु 0x1b8, 0x1106 पूर्ण, अणु 0x1b9, 0x2713 पूर्ण, /* G */
		अणु 0x1ba, 0x0c03 पूर्ण, अणु 0x1bb, 0x2a0f पूर्ण, /* B */
		/* horizontal knee 7+6, 9+8, 10 */
		अणु 0x1bc, 0x1208 पूर्ण, अणु 0x1bd, 0x1a16 पूर्ण, अणु 0x1be, 0x0022 पूर्ण, /* R */
		अणु 0x1bf, 0x150a पूर्ण, अणु 0x1c0, 0x1c1a पूर्ण, अणु 0x1c1, 0x002d पूर्ण, /* G */
		अणु 0x1c2, 0x1109 पूर्ण, अणु 0x1c3, 0x1414 पूर्ण, अणु 0x1c4, 0x002a पूर्ण, /* B */
		अणु 0x106, 0x740e पूर्ण, /* enable lens shading correction */

		/* Gamma correction - context A */
		अणु 0x153, 0x0b03 पूर्ण, अणु 0x154, 0x4722 पूर्ण, अणु 0x155, 0xac82 पूर्ण,
		अणु 0x156, 0xdac7 पूर्ण, अणु 0x157, 0xf5e9 पूर्ण, अणु 0x158, 0xff00 पूर्ण,
		/* Gamma correction - context B */
		अणु 0x1dc, 0x0b03 पूर्ण, अणु 0x1dd, 0x4722 पूर्ण, अणु 0x1de, 0xac82 पूर्ण,
		अणु 0x1df, 0xdac7 पूर्ण, अणु 0x1e0, 0xf5e9 पूर्ण, अणु 0x1e1, 0xff00 पूर्ण,

		/* output क्रमmat: RGB, invert output pixघड़ी, output bayer */
		अणु 0x13a, 0x4300 पूर्ण, अणु 0x19b, 0x4300 पूर्ण, /* क्रम context A, B */
		अणु 0x108, 0x0180 पूर्ण, /* क्रमmat control - enable bayer row flip */

		अणु 0x22f, 0xd100 पूर्ण, अणु 0x29c, 0xd100 पूर्ण, /* AE A, B */

		/* शेष prg conf, prg ctl - by 0x2d2, prg advance - PA1 */
		अणु 0x2d2, 0x0000 पूर्ण, अणु 0x2cc, 0x0004 पूर्ण, अणु 0x2cb, 0x0001 पूर्ण,

		अणु 0x22e, 0x0c3c पूर्ण, अणु 0x267, 0x1010 पूर्ण, /* AE tgt ctl, gain lim */

		/* PLL */
		अणु 0x065, 0xa000 पूर्ण, /* clk ctl - enable PLL (clear bit 14) */
		अणु 0x066, 0x2003 पूर्ण, अणु 0x067, 0x0501 पूर्ण, /* PLL M=128, N=3, P=1 */
		अणु 0x065, 0x2000 पूर्ण, /* disable PLL bypass (clear bit 15) */

		अणु 0x005, 0x01b8 पूर्ण, अणु 0x007, 0x00d8 पूर्ण, /* horiz blanking B, A */

		/* AE line size, shutter delay limit */
		अणु 0x239, 0x06c0 पूर्ण, अणु 0x23b, 0x040e पूर्ण, /* क्रम context A */
		अणु 0x23a, 0x06c0 पूर्ण, अणु 0x23c, 0x0564 पूर्ण, /* क्रम context B */
		/* shutter width basis 60Hz, 50Hz */
		अणु 0x257, 0x0208 पूर्ण, अणु 0x258, 0x0271 पूर्ण, /* क्रम context A */
		अणु 0x259, 0x0209 पूर्ण, अणु 0x25a, 0x0271 पूर्ण, /* क्रम context B */

		अणु 0x25c, 0x120d पूर्ण, अणु 0x25d, 0x1712 पूर्ण, /* flicker 60Hz, 50Hz */
		अणु 0x264, 0x5e1c पूर्ण, /* reserved */
		/* flicker, AE gain limits, gain zone limits */
		अणु 0x25b, 0x0003 पूर्ण, अणु 0x236, 0x7810 पूर्ण, अणु 0x237, 0x8304 पूर्ण,

		अणु 0x008, 0x0021 पूर्ण, /* vert blanking A */
	पूर्ण;
	पूर्णांक i;
	u16 width, height;

	क्रम (i = 0; i < ARRAY_SIZE(cfg); i++)
		sensor_ग_लिखो(gspca_dev, cfg[i].reg, cfg[i].val);

	/* set output size */
	width = gspca_dev->pixfmt.width;
	height = gspca_dev->pixfmt.height;
	अगर (width <= 640 && height <= 512) अणु /* context A (half पढ़ोout speed)*/
		sensor_ग_लिखो(gspca_dev, 0x1a7, width);
		sensor_ग_लिखो(gspca_dev, 0x1aa, height);
		/* set पढ़ो mode context A */
		sensor_ग_लिखो(gspca_dev, 0x0c8, 0x0000);
		/* set resize, पढ़ो mode, vblank, hblank context A */
		sensor_ग_लिखो(gspca_dev, 0x2c8, 0x0000);
	पूर्ण अन्यथा अणु /* context B (full पढ़ोout speed) */
		sensor_ग_लिखो(gspca_dev, 0x1a1, width);
		sensor_ग_लिखो(gspca_dev, 0x1a4, height);
		/* set पढ़ो mode context B */
		sensor_ग_लिखो(gspca_dev, 0x0c8, 0x0008);
		/* set resize, पढ़ो mode, vblank, hblank context B */
		sensor_ग_लिखो(gspca_dev, 0x2c8, 0x040b);
	पूर्ण
पूर्ण

अटल व्योम stk1135_configure_घड़ी(काष्ठा gspca_dev *gspca_dev)
अणु
	/* configure SCLKOUT */
	reg_w(gspca_dev, STK1135_REG_TMGEN, 0x12);
	/* set 1 घड़ी per pixel */
	/* and positive edge घड़ीed pulse high when pixel counter = 0 */
	reg_w(gspca_dev, STK1135_REG_TCP1 + 0, 0x41);
	reg_w(gspca_dev, STK1135_REG_TCP1 + 1, 0x00);
	reg_w(gspca_dev, STK1135_REG_TCP1 + 2, 0x00);
	reg_w(gspca_dev, STK1135_REG_TCP1 + 3, 0x00);

	/* enable CLKOUT क्रम sensor */
	reg_w(gspca_dev, STK1135_REG_SENSO + 0, 0x10);
	/* disable STOP घड़ी */
	reg_w(gspca_dev, STK1135_REG_SENSO + 1, 0x00);
	/* set lower 8 bits of PLL feedback भागider */
	reg_w(gspca_dev, STK1135_REG_SENSO + 3, 0x07);
	/* set other PLL parameters */
	reg_w(gspca_dev, STK1135_REG_PLLFD, 0x06);
	/* enable timing generator */
	reg_w(gspca_dev, STK1135_REG_TMGEN, 0x80);
	/* enable PLL */
	reg_w(gspca_dev, STK1135_REG_SENSO + 2, 0x04);

	/* set serial पूर्णांकerface घड़ी भागider (30MHz/0x1f*16+2) = 60240 kHz) */
	reg_w(gspca_dev, STK1135_REG_SICTL + 2, 0x1f);

	/* रुको a जबतक क्रम sensor to catch up */
	udelay(1000);
पूर्ण

अटल व्योम stk1135_camera_disable(काष्ठा gspca_dev *gspca_dev)
अणु
	/* set capture end Y position to 0 */
	reg_w(gspca_dev, STK1135_REG_CIEPO + 2, 0x00);
	reg_w(gspca_dev, STK1135_REG_CIEPO + 3, 0x00);
	/* disable capture */
	reg_w_mask(gspca_dev, STK1135_REG_SCTRL, 0x00, 0x80);

	/* enable sensor standby and diasble chip enable */
	sensor_ग_लिखो_mask(gspca_dev, 0x00d, 0x0004, 0x000c);

	/* disable PLL */
	reg_w_mask(gspca_dev, STK1135_REG_SENSO + 2, 0x00, 0x01);
	/* disable timing generator */
	reg_w(gspca_dev, STK1135_REG_TMGEN, 0x00);
	/* enable STOP घड़ी */
	reg_w(gspca_dev, STK1135_REG_SENSO + 1, 0x20);
	/* disable CLKOUT क्रम sensor */
	reg_w(gspca_dev, STK1135_REG_SENSO, 0x00);

	/* disable sensor (GPIO5) and enable GPIO0,3,6 (?) - sensor standby? */
	reg_w(gspca_dev, STK1135_REG_GCTRL, 0x49);
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	u16 sensor_id;
	अक्षर *sensor_name;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* set GPIO3,4,5,6 direction to output */
	reg_w(gspca_dev, STK1135_REG_GCTRL + 2, 0x78);
	/* enable sensor (GPIO5) */
	reg_w(gspca_dev, STK1135_REG_GCTRL, (1 << 5));
	/* disable ROM पूर्णांकerface */
	reg_w(gspca_dev, STK1135_REG_GCTRL + 3, 0x80);
	/* enable पूर्णांकerrupts from GPIO8 (flip sensor) and GPIO9 (???) */
	reg_w(gspca_dev, STK1135_REG_ICTRL + 1, 0x00);
	reg_w(gspca_dev, STK1135_REG_ICTRL + 3, 0x03);
	/* enable remote wakeup from GPIO9 (???) */
	reg_w(gspca_dev, STK1135_REG_RMCTL + 1, 0x00);
	reg_w(gspca_dev, STK1135_REG_RMCTL + 3, 0x02);

	/* reset serial पूर्णांकerface */
	reg_w(gspca_dev, STK1135_REG_SICTL, 0x80);
	reg_w(gspca_dev, STK1135_REG_SICTL, 0x00);
	/* set sensor address */
	reg_w(gspca_dev, STK1135_REG_SICTL + 3, 0xba);
	/* disable alt 2-wire serial पूर्णांकerface */
	reg_w(gspca_dev, STK1135_REG_ASIC + 3, 0x00);

	stk1135_configure_घड़ी(gspca_dev);

	/* पढ़ो sensor ID */
	sd->sensor_page = 0xff;
	sensor_id = sensor_पढ़ो(gspca_dev, 0x000);

	चयन (sensor_id) अणु
	हाल 0x148c:
		sensor_name = "MT9M112";
		अवरोध;
	शेष:
		sensor_name = "unknown";
	पूर्ण
	pr_info("Detected sensor type %s (0x%x)\n", sensor_name, sensor_id);

	stk1135_camera_disable(gspca_dev);

	वापस gspca_dev->usb_err;
पूर्ण

/* -- start the camera -- */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u16 width, height;

	/* enable sensor (GPIO5) */
	reg_w(gspca_dev, STK1135_REG_GCTRL, (1 << 5));

	stk1135_configure_घड़ी(gspca_dev);

	/* set capture start position X = 0, Y = 0 */
	reg_w(gspca_dev, STK1135_REG_CISPO + 0, 0x00);
	reg_w(gspca_dev, STK1135_REG_CISPO + 1, 0x00);
	reg_w(gspca_dev, STK1135_REG_CISPO + 2, 0x00);
	reg_w(gspca_dev, STK1135_REG_CISPO + 3, 0x00);

	/* set capture end position */
	width = gspca_dev->pixfmt.width;
	height = gspca_dev->pixfmt.height;
	reg_w(gspca_dev, STK1135_REG_CIEPO + 0, width & 0xff);
	reg_w(gspca_dev, STK1135_REG_CIEPO + 1, width >> 8);
	reg_w(gspca_dev, STK1135_REG_CIEPO + 2, height & 0xff);
	reg_w(gspca_dev, STK1135_REG_CIEPO + 3, height >> 8);

	/* set 8-bit mode */
	reg_w(gspca_dev, STK1135_REG_SCTRL, 0x20);

	stk1135_configure_mt9m112(gspca_dev);

	/* enable capture */
	reg_w_mask(gspca_dev, STK1135_REG_SCTRL, 0x80, 0x80);

	अगर (gspca_dev->usb_err >= 0)
		gspca_dbg(gspca_dev, D_STREAM, "camera started alt: 0x%02x\n",
			  gspca_dev->alt);

	sd->pkt_seq = 0;

	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;

	usb_set_पूर्णांकerface(dev, gspca_dev->अगरace, 0);

	stk1135_camera_disable(gspca_dev);

	gspca_dbg(gspca_dev, D_STREAM, "camera stopped\n");
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक skip = माप(काष्ठा stk1135_pkt_header);
	bool flip;
	क्रमागत gspca_packet_type pkt_type = INTER_PACKET;
	काष्ठा stk1135_pkt_header *hdr = (व्योम *)data;
	u8 seq;

	अगर (len < 4) अणु
		gspca_dbg(gspca_dev, D_PACK, "received short packet (less than 4 bytes)\n");
		वापस;
	पूर्ण

	/* GPIO 8 is flip sensor (1 = normal position, 0 = flipped to back) */
	flip = !(le16_to_cpu(hdr->gpio) & (1 << 8));
	/* it's a चयन, needs software debounce */
	अगर (sd->flip_status != flip)
		sd->flip_debounce++;
	अन्यथा
		sd->flip_debounce = 0;

	/* check sequence number (not present in new frame packets) */
	अगर (!(hdr->flags & STK1135_HDR_FRAME_START)) अणु
		seq = hdr->seq & STK1135_HDR_SEQ_MASK;
		अगर (seq != sd->pkt_seq) अणु
			gspca_dbg(gspca_dev, D_PACK, "received out-of-sequence packet\n");
			/* resync sequence and discard packet */
			sd->pkt_seq = seq;
			gspca_dev->last_packet_type = DISCARD_PACKET;
			वापस;
		पूर्ण
	पूर्ण
	sd->pkt_seq++;
	अगर (sd->pkt_seq > STK1135_HDR_SEQ_MASK)
		sd->pkt_seq = 0;

	अगर (len == माप(काष्ठा stk1135_pkt_header))
		वापस;

	अगर (hdr->flags & STK1135_HDR_FRAME_START) अणु /* new frame */
		skip = 8;	/* the header is दीर्घer */
		gspca_frame_add(gspca_dev, LAST_PACKET, data, 0);
		pkt_type = FIRST_PACKET;
	पूर्ण
	gspca_frame_add(gspca_dev, pkt_type, data + skip, len - skip);
पूर्ण

अटल व्योम sethflip(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->flip_status)
		val = !val;
	sensor_ग_लिखो_mask(gspca_dev, 0x020, val ? 0x0002 : 0x0000 , 0x0002);
पूर्ण

अटल व्योम setvflip(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->flip_status)
		val = !val;
	sensor_ग_लिखो_mask(gspca_dev, 0x020, val ? 0x0001 : 0x0000 , 0x0001);
पूर्ण

अटल व्योम stk1135_dq_callback(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->flip_debounce > 100) अणु
		sd->flip_status = !sd->flip_status;
		sethflip(gspca_dev, v4l2_ctrl_g_ctrl(sd->hflip));
		setvflip(gspca_dev, v4l2_ctrl_g_ctrl(sd->vflip));
	पूर्ण
पूर्ण

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_HFLIP:
		sethflip(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_VFLIP:
		setvflip(gspca_dev, ctrl->val);
		अवरोध;
	पूर्ण

	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 2);
	sd->hflip = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	sd->vflip = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम stk1135_try_fmt(काष्ठा gspca_dev *gspca_dev, काष्ठा v4l2_क्रमmat *fmt)
अणु
	fmt->fmt.pix.width = clamp(fmt->fmt.pix.width, 32U, 1280U);
	fmt->fmt.pix.height = clamp(fmt->fmt.pix.height, 32U, 1024U);
	/* round up to even numbers */
	fmt->fmt.pix.width += (fmt->fmt.pix.width & 1);
	fmt->fmt.pix.height += (fmt->fmt.pix.height & 1);

	fmt->fmt.pix.bytesperline = fmt->fmt.pix.width;
	fmt->fmt.pix.sizeimage = fmt->fmt.pix.width * fmt->fmt.pix.height;
पूर्ण

अटल पूर्णांक stk1135_क्रमागत_framesizes(काष्ठा gspca_dev *gspca_dev,
			काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	अगर (fsize->index != 0 || fsize->pixel_क्रमmat != V4L2_PIX_FMT_SBGGR8)
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise.min_width = 32;
	fsize->stepwise.min_height = 32;
	fsize->stepwise.max_width = 1280;
	fsize->stepwise.max_height = 1024;
	fsize->stepwise.step_width = 2;
	fsize->stepwise.step_height = 2;

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
	.dq_callback = stk1135_dq_callback,
	.try_fmt = stk1135_try_fmt,
	.क्रमागत_framesizes = stk1135_क्रमागत_framesizes,
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x174f, 0x6a31)पूर्ण,	/* ASUS laptop, MT9M112 sensor */
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
