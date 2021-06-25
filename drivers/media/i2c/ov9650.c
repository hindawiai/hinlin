<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Omnivision OV9650/OV9652 CMOS Image Sensor driver
 *
 * Copyright (C) 2013, Sylwester Nawrocki <sylvester.nawrocki@gmail.com>
 *
 * Register definitions and initial settings based on a driver written
 * by Vladimir Fonov.
 * Copyright (c) 2010, Vladimir Fonov
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/media.h>
#समावेश <linux/module.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/videodev2.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/i2c/ov9650.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level (0-2)");

#घोषणा DRIVER_NAME "OV9650"

/*
 * OV9650/OV9652 रेजिस्टर definitions
 */
#घोषणा REG_GAIN		0x00	/* Gain control, AGC[7:0] */
#घोषणा REG_BLUE		0x01	/* AWB - Blue channel gain */
#घोषणा REG_RED			0x02	/* AWB - Red channel gain */
#घोषणा REG_VREF		0x03	/* [7:6] - AGC[9:8], [5:3]/[2:0] */
#घोषणा  VREF_GAIN_MASK		0xc0	/* - VREF end/start low 3 bits */
#घोषणा REG_COM1		0x04
#घोषणा  COM1_CCIR656		0x40
#घोषणा REG_B_AVE		0x05
#घोषणा REG_GB_AVE		0x06
#घोषणा REG_GR_AVE		0x07
#घोषणा REG_R_AVE		0x08
#घोषणा REG_COM2		0x09
#घोषणा REG_PID			0x0a	/* Product ID MSB */
#घोषणा REG_VER			0x0b	/* Product ID LSB */
#घोषणा REG_COM3		0x0c
#घोषणा  COM3_SWAP		0x40
#घोषणा  COM3_VARIOPIXEL1	0x04
#घोषणा REG_COM4		0x0d	/* Vario Pixels  */
#घोषणा  COM4_VARIOPIXEL2	0x80
#घोषणा REG_COM5		0x0e	/* System घड़ी options */
#घोषणा  COM5_SLAVE_MODE	0x10
#घोषणा  COM5_SYSTEMCLOCK48MHZ	0x80
#घोषणा REG_COM6		0x0f	/* HREF & ADBLC options */
#घोषणा REG_AECH		0x10	/* Exposure value, AEC[9:2] */
#घोषणा REG_CLKRC		0x11	/* Clock control */
#घोषणा  CLK_EXT		0x40	/* Use बाह्यal घड़ी directly */
#घोषणा  CLK_SCALE		0x3f	/* Mask क्रम पूर्णांकernal घड़ी scale */
#घोषणा REG_COM7		0x12	/* SCCB reset, output क्रमmat */
#घोषणा  COM7_RESET		0x80
#घोषणा  COM7_FMT_MASK		0x38
#घोषणा  COM7_FMT_VGA		0x40
#घोषणा	 COM7_FMT_CIF		0x20
#घोषणा  COM7_FMT_QVGA		0x10
#घोषणा  COM7_FMT_QCIF		0x08
#घोषणा	 COM7_RGB		0x04
#घोषणा	 COM7_YUV		0x00
#घोषणा	 COM7_BAYER		0x01
#घोषणा	 COM7_PBAYER		0x05
#घोषणा REG_COM8		0x13	/* AGC/AEC options */
#घोषणा  COM8_FASTAEC		0x80	/* Enable fast AGC/AEC */
#घोषणा  COM8_AECSTEP		0x40	/* Unlimited AEC step size */
#घोषणा  COM8_BFILT		0x20	/* Band filter enable */
#घोषणा  COM8_AGC		0x04	/* Auto gain enable */
#घोषणा  COM8_AWB		0x02	/* White balance enable */
#घोषणा  COM8_AEC		0x01	/* Auto exposure enable */
#घोषणा REG_COM9		0x14	/* Gain उच्चमानing */
#घोषणा  COM9_GAIN_CEIL_MASK	0x70	/* */
#घोषणा REG_COM10		0x15	/* PCLK, HREF, HSYNC संकेतs polarity */
#घोषणा  COM10_HSYNC		0x40	/* HSYNC instead of HREF */
#घोषणा  COM10_PCLK_HB		0x20	/* Suppress PCLK on horiz blank */
#घोषणा  COM10_HREF_REV		0x08	/* Reverse HREF */
#घोषणा  COM10_VS_LEAD		0x04	/* VSYNC on घड़ी leading edge */
#घोषणा  COM10_VS_NEG		0x02	/* VSYNC negative */
#घोषणा  COM10_HS_NEG		0x01	/* HSYNC negative */
#घोषणा REG_HSTART		0x17	/* Horiz start high bits */
#घोषणा REG_HSTOP		0x18	/* Horiz stop high bits */
#घोषणा REG_VSTART		0x19	/* Vert start high bits */
#घोषणा REG_VSTOP		0x1a	/* Vert stop high bits */
#घोषणा REG_PSHFT		0x1b	/* Pixel delay after HREF */
#घोषणा REG_MIDH		0x1c	/* Manufacturer ID MSB */
#घोषणा REG_MIDL		0x1d	/* Manufufacturer ID LSB */
#घोषणा REG_MVFP		0x1e	/* Image mirror/flip */
#घोषणा  MVFP_MIRROR		0x20	/* Mirror image */
#घोषणा  MVFP_FLIP		0x10	/* Vertical flip */
#घोषणा REG_BOS			0x20	/* B channel Offset */
#घोषणा REG_GBOS		0x21	/* Gb channel Offset */
#घोषणा REG_GROS		0x22	/* Gr channel Offset */
#घोषणा REG_ROS			0x23	/* R channel Offset */
#घोषणा REG_AEW			0x24	/* AGC upper limit */
#घोषणा REG_AEB			0x25	/* AGC lower limit */
#घोषणा REG_VPT			0x26	/* AGC/AEC fast mode op region */
#घोषणा REG_BBIAS		0x27	/* B channel output bias */
#घोषणा REG_GBBIAS		0x28	/* Gb channel output bias */
#घोषणा REG_GRCOM		0x29	/* Analog BLC & regulator */
#घोषणा REG_EXHCH		0x2a	/* Dummy pixel insert MSB */
#घोषणा REG_EXHCL		0x2b	/* Dummy pixel insert LSB */
#घोषणा REG_RBIAS		0x2c	/* R channel output bias */
#घोषणा REG_ADVFL		0x2d	/* LSB of dummy line insert */
#घोषणा REG_ADVFH		0x2e	/* MSB of dummy line insert */
#घोषणा REG_YAVE		0x2f	/* Y/G channel average value */
#घोषणा REG_HSYST		0x30	/* HSYNC rising edge delay LSB*/
#घोषणा REG_HSYEN		0x31	/* HSYNC falling edge delay LSB*/
#घोषणा REG_HREF		0x32	/* HREF pieces */
#घोषणा REG_CHLF		0x33	/* reserved */
#घोषणा REG_ADC			0x37	/* reserved */
#घोषणा REG_ACOM		0x38	/* reserved */
#घोषणा REG_OFON		0x39	/* Power करोwn रेजिस्टर */
#घोषणा  OFON_PWRDN		0x08	/* Power करोwn bit */
#घोषणा REG_TSLB		0x3a	/* YUVU क्रमmat */
#घोषणा  TSLB_YUYV_MASK		0x0c	/* UYVY or VYUY - see com13 */
#घोषणा REG_COM11		0x3b	/* Night mode, banding filter enable */
#घोषणा  COM11_NIGHT		0x80	/* Night mode enable */
#घोषणा  COM11_NMFR		0x60	/* Two bit NM frame rate */
#घोषणा  COM11_BANDING		0x01	/* Banding filter */
#घोषणा  COM11_AEC_REF_MASK	0x18	/* AEC reference area selection */
#घोषणा REG_COM12		0x3c	/* HREF option, UV average */
#घोषणा  COM12_HREF		0x80	/* HREF always */
#घोषणा REG_COM13		0x3d	/* Gamma selection, Color matrix en. */
#घोषणा  COM13_GAMMA		0x80	/* Gamma enable */
#घोषणा	 COM13_UVSAT		0x40	/* UV saturation स्वतः adjusपंचांगent */
#घोषणा  COM13_UVSWAP		0x01	/* V beक्रमe U - w/TSLB */
#घोषणा REG_COM14		0x3e	/* Edge enhancement options */
#घोषणा  COM14_EDGE_EN		0x02
#घोषणा  COM14_EEF_X2		0x01
#घोषणा REG_EDGE		0x3f	/* Edge enhancement factor */
#घोषणा  EDGE_FACTOR_MASK	0x0f
#घोषणा REG_COM15		0x40	/* Output range, RGB 555/565 */
#घोषणा  COM15_R10F0		0x00	/* Data range 10 to F0 */
#घोषणा	 COM15_R01FE		0x80	/* 01 to FE */
#घोषणा  COM15_R00FF		0xc0	/* 00 to FF */
#घोषणा  COM15_RGB565		0x10	/* RGB565 output */
#घोषणा  COM15_RGB555		0x30	/* RGB555 output */
#घोषणा  COM15_SWAPRB		0x04	/* Swap R&B */
#घोषणा REG_COM16		0x41	/* Color matrix coeff options */
#घोषणा REG_COM17		0x42	/* Single frame out, banding filter */
/* n = 1...9, 0x4f..0x57 */
#घोषणा	REG_MTX(__n)		(0x4f + (__n) - 1)
#घोषणा REG_MTXS		0x58
/* Lens Correction Option 1...5, __n = 0...5 */
#घोषणा REG_LCC(__n)		(0x62 + (__n) - 1)
#घोषणा  LCC5_LCC_ENABLE	0x01	/* LCC5, enable lens correction */
#घोषणा  LCC5_LCC_COLOR		0x04
#घोषणा REG_MANU		0x67	/* Manual U value */
#घोषणा REG_MANV		0x68	/* Manual V value */
#घोषणा REG_HV			0x69	/* Manual banding filter MSB */
#घोषणा REG_MBD			0x6a	/* Manual banding filter value */
#घोषणा REG_DBLV		0x6b	/* reserved */
#घोषणा REG_GSP			0x6c	/* Gamma curve */
#घोषणा  GSP_LEN		15
#घोषणा REG_GST			0x7c	/* Gamma curve */
#घोषणा  GST_LEN		15
#घोषणा REG_COM21		0x8b
#घोषणा REG_COM22		0x8c	/* Edge enhancement, denoising */
#घोषणा  COM22_WHTPCOR		0x02	/* White pixel correction enable */
#घोषणा  COM22_WHTPCOROPT	0x01	/* White pixel correction option */
#घोषणा  COM22_DENOISE		0x10	/* White pixel correction option */
#घोषणा REG_COM23		0x8d	/* Color bar test, color gain */
#घोषणा  COM23_TEST_MODE	0x10
#घोषणा REG_DBLC1		0x8f	/* Digital BLC */
#घोषणा REG_DBLC_B		0x90	/* Digital BLC B channel offset */
#घोषणा REG_DBLC_R		0x91	/* Digital BLC R channel offset */
#घोषणा REG_DM_LNL		0x92	/* Dummy line low 8 bits */
#घोषणा REG_DM_LNH		0x93	/* Dummy line high 8 bits */
#घोषणा REG_LCCFB		0x9d	/* Lens Correction B channel */
#घोषणा REG_LCCFR		0x9e	/* Lens Correction R channel */
#घोषणा REG_DBLC_GB		0x9f	/* Digital BLC GB chan offset */
#घोषणा REG_DBLC_GR		0xa0	/* Digital BLC GR chan offset */
#घोषणा REG_AECHM		0xa1	/* Exposure value - bits AEC[15:10] */
#घोषणा REG_BD50ST		0xa2	/* Banding filter value क्रम 50Hz */
#घोषणा REG_BD60ST		0xa3	/* Banding filter value क्रम 60Hz */
#घोषणा REG_शून्य		0xff	/* Array end token */

#घोषणा DEF_CLKRC		0x80

#घोषणा OV965X_ID(_msb, _lsb)	((_msb) << 8 | (_lsb))
#घोषणा OV9650_ID		0x9650
#घोषणा OV9652_ID		0x9652

काष्ठा ov965x_ctrls अणु
	काष्ठा v4l2_ctrl_handler handler;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *स्वतः_exp;
		काष्ठा v4l2_ctrl *exposure;
	पूर्ण;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *स्वतः_wb;
		काष्ठा v4l2_ctrl *blue_balance;
		काष्ठा v4l2_ctrl *red_balance;
	पूर्ण;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *hflip;
		काष्ठा v4l2_ctrl *vflip;
	पूर्ण;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *स्वतः_gain;
		काष्ठा v4l2_ctrl *gain;
	पूर्ण;
	काष्ठा v4l2_ctrl *brightness;
	काष्ठा v4l2_ctrl *saturation;
	काष्ठा v4l2_ctrl *sharpness;
	काष्ठा v4l2_ctrl *light_freq;
	u8 update;
पूर्ण;

काष्ठा ov965x_framesize अणु
	u16 width;
	u16 height;
	u16 max_exp_lines;
	स्थिर u8 *regs;
पूर्ण;

काष्ठा ov965x_पूर्णांकerval अणु
	काष्ठा v4l2_fract पूर्णांकerval;
	/* Maximum resolution क्रम this पूर्णांकerval */
	काष्ठा v4l2_frmsize_discrete size;
	u8 clkrc_भाग;
पूर्ण;

क्रमागत gpio_id अणु
	GPIO_PWDN,
	GPIO_RST,
	NUM_GPIOS,
पूर्ण;

काष्ठा ov965x अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	क्रमागत v4l2_mbus_type bus_type;
	काष्ठा gpio_desc *gpios[NUM_GPIOS];
	/* External master घड़ी frequency */
	अचिन्हित दीर्घ mclk_frequency;
	काष्ठा clk *clk;

	/* Protects the काष्ठा fields below */
	काष्ठा mutex lock;

	काष्ठा regmap *regmap;

	/* Exposure row पूर्णांकerval in us */
	अचिन्हित पूर्णांक exp_row_पूर्णांकerval;

	अचिन्हित लघु id;
	स्थिर काष्ठा ov965x_framesize *frame_size;
	/* YUYV sequence (pixel क्रमmat) control रेजिस्टर */
	u8 tslb_reg;
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	काष्ठा ov965x_ctrls ctrls;
	/* Poपूर्णांकer to frame rate control data काष्ठाure */
	स्थिर काष्ठा ov965x_पूर्णांकerval *fiv;

	पूर्णांक streaming;
	पूर्णांक घातer;

	u8 apply_frame_fmt;
पूर्ण;

काष्ठा i2c_rv अणु
	u8 addr;
	u8 value;
पूर्ण;

अटल स्थिर काष्ठा i2c_rv ov965x_init_regs[] = अणु
	अणु REG_COM2, 0x10 पूर्ण,	/* Set soft sleep mode */
	अणु REG_COM5, 0x00 पूर्ण,	/* System घड़ी options */
	अणु REG_COM2, 0x01 पूर्ण,	/* Output drive, soft sleep mode */
	अणु REG_COM10, 0x00 पूर्ण,	/* Slave mode, HREF vs HSYNC, संकेतs negate */
	अणु REG_EDGE, 0xa6 पूर्ण,	/* Edge enhancement treshhold and factor */
	अणु REG_COM16, 0x02 पूर्ण,	/* Color matrix coeff द्विगुन option */
	अणु REG_COM17, 0x08 पूर्ण,	/* Single frame out, banding filter */
	अणु 0x16, 0x06 पूर्ण,
	अणु REG_CHLF, 0xc0 पूर्ण,	/* Reserved  */
	अणु 0x34, 0xbf पूर्ण,
	अणु 0xa8, 0x80 पूर्ण,
	अणु 0x96, 0x04 पूर्ण,
	अणु 0x8e, 0x00 पूर्ण,
	अणु REG_COM12, 0x77 पूर्ण,	/* HREF option, UV average  */
	अणु 0x8b, 0x06 पूर्ण,
	अणु 0x35, 0x91 पूर्ण,
	अणु 0x94, 0x88 पूर्ण,
	अणु 0x95, 0x88 पूर्ण,
	अणु REG_COM15, 0xc1 पूर्ण,	/* Output range, RGB 555/565 */
	अणु REG_GRCOM, 0x2f पूर्ण,	/* Analog BLC & regulator */
	अणु REG_COM6, 0x43 पूर्ण,	/* HREF & ADBLC options */
	अणु REG_COM8, 0xe5 पूर्ण,	/* AGC/AEC options */
	अणु REG_COM13, 0x90 पूर्ण,	/* Gamma selection, colour matrix, UV delay */
	अणु REG_HV, 0x80 पूर्ण,	/* Manual banding filter MSB  */
	अणु 0x5c, 0x96 पूर्ण,		/* Reserved up to 0xa5 */
	अणु 0x5d, 0x96 पूर्ण,
	अणु 0x5e, 0x10 पूर्ण,
	अणु 0x59, 0xeb पूर्ण,
	अणु 0x5a, 0x9c पूर्ण,
	अणु 0x5b, 0x55 पूर्ण,
	अणु 0x43, 0xf0 पूर्ण,
	अणु 0x44, 0x10 पूर्ण,
	अणु 0x45, 0x55 पूर्ण,
	अणु 0x46, 0x86 पूर्ण,
	अणु 0x47, 0x64 पूर्ण,
	अणु 0x48, 0x86 पूर्ण,
	अणु 0x5f, 0xe0 पूर्ण,
	अणु 0x60, 0x8c पूर्ण,
	अणु 0x61, 0x20 पूर्ण,
	अणु 0xa5, 0xd9 पूर्ण,
	अणु 0xa4, 0x74 पूर्ण,		/* reserved */
	अणु REG_COM23, 0x02 पूर्ण,	/* Color gain analog/_digital_ */
	अणु REG_COM8, 0xe7 पूर्ण,	/* Enable AEC, AWB, AEC */
	अणु REG_COM22, 0x23 पूर्ण,	/* Edge enhancement, denoising */
	अणु 0xa9, 0xb8 पूर्ण,
	अणु 0xaa, 0x92 पूर्ण,
	अणु 0xab, 0x0a पूर्ण,
	अणु REG_DBLC1, 0xdf पूर्ण,	/* Digital BLC */
	अणु REG_DBLC_B, 0x00 पूर्ण,	/* Digital BLC B chan offset */
	अणु REG_DBLC_R, 0x00 पूर्ण,	/* Digital BLC R chan offset */
	अणु REG_DBLC_GB, 0x00 पूर्ण,	/* Digital BLC GB chan offset */
	अणु REG_DBLC_GR, 0x00 पूर्ण,
	अणु REG_COM9, 0x3a पूर्ण,	/* Gain उच्चमानing 16x */
	अणु REG_शून्य, 0 पूर्ण
पूर्ण;

#घोषणा NUM_FMT_REGS 14
/*
 * COM7,  COM3,  COM4, HSTART, HSTOP, HREF, VSTART, VSTOP, VREF,
 * EXHCH, EXHCL, ADC,  OCOM,   OFON
 */
अटल स्थिर u8 frame_size_reg_addr[NUM_FMT_REGS] = अणु
	0x12, 0x0c, 0x0d, 0x17, 0x18, 0x32, 0x19, 0x1a, 0x03,
	0x2a, 0x2b, 0x37, 0x38, 0x39,
पूर्ण;

अटल स्थिर u8 ov965x_sxga_regs[NUM_FMT_REGS] = अणु
	0x00, 0x00, 0x00, 0x1e, 0xbe, 0xbf, 0x01, 0x81, 0x12,
	0x10, 0x34, 0x81, 0x93, 0x51,
पूर्ण;

अटल स्थिर u8 ov965x_vga_regs[NUM_FMT_REGS] = अणु
	0x40, 0x04, 0x80, 0x26, 0xc6, 0xed, 0x01, 0x3d, 0x00,
	0x10, 0x40, 0x91, 0x12, 0x43,
पूर्ण;

/* Determined empirically. */
अटल स्थिर u8 ov965x_qvga_regs[NUM_FMT_REGS] = अणु
	0x10, 0x04, 0x80, 0x25, 0xc5, 0xbf, 0x00, 0x80, 0x12,
	0x10, 0x40, 0x91, 0x12, 0x43,
पूर्ण;

अटल स्थिर काष्ठा ov965x_framesize ov965x_framesizes[] = अणु
	अणु
		.width		= SXGA_WIDTH,
		.height		= SXGA_HEIGHT,
		.regs		= ov965x_sxga_regs,
		.max_exp_lines	= 1048,
	पूर्ण, अणु
		.width		= VGA_WIDTH,
		.height		= VGA_HEIGHT,
		.regs		= ov965x_vga_regs,
		.max_exp_lines	= 498,
	पूर्ण, अणु
		.width		= QVGA_WIDTH,
		.height		= QVGA_HEIGHT,
		.regs		= ov965x_qvga_regs,
		.max_exp_lines	= 248,
	पूर्ण,
पूर्ण;

काष्ठा ov965x_pixfmt अणु
	u32 code;
	u32 colorspace;
	/* REG_TSLB value, only bits [3:2] may be set. */
	u8 tslb_reg;
पूर्ण;

अटल स्थिर काष्ठा ov965x_pixfmt ov965x_क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_YUYV8_2X8, V4L2_COLORSPACE_JPEG, 0x00पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, V4L2_COLORSPACE_JPEG, 0x04पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_2X8, V4L2_COLORSPACE_JPEG, 0x0cपूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, V4L2_COLORSPACE_JPEG, 0x08पूर्ण,
पूर्ण;

/*
 * This table specअगरies possible frame resolution and पूर्णांकerval
 * combinations. Default CLKRC[5:0] भागider values are valid
 * only क्रम 24 MHz बाह्यal घड़ी frequency.
 */
अटल काष्ठा ov965x_पूर्णांकerval ov965x_पूर्णांकervals[] = अणु
	अणुअणु 100, 625 पूर्ण, अणु SXGA_WIDTH, SXGA_HEIGHT पूर्ण, 0 पूर्ण,  /* 6.25 fps */
	अणुअणु 10,  125 पूर्ण, अणु VGA_WIDTH, VGA_HEIGHT पूर्ण,   1 पूर्ण,  /* 12.5 fps */
	अणुअणु 10,  125 पूर्ण, अणु QVGA_WIDTH, QVGA_HEIGHT पूर्ण, 3 पूर्ण,  /* 12.5 fps */
	अणुअणु 1,   25  पूर्ण, अणु VGA_WIDTH, VGA_HEIGHT पूर्ण,   0 पूर्ण,  /* 25 fps */
	अणुअणु 1,   25  पूर्ण, अणु QVGA_WIDTH, QVGA_HEIGHT पूर्ण, 1 पूर्ण,  /* 25 fps */
पूर्ण;

अटल अंतरभूत काष्ठा v4l2_subdev *ctrl_to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा ov965x, ctrls.handler)->sd;
पूर्ण

अटल अंतरभूत काष्ठा ov965x *to_ov965x(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ov965x, sd);
पूर्ण

अटल पूर्णांक ov965x_पढ़ो(काष्ठा ov965x *ov965x, u8 addr, u8 *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक buf;

	ret = regmap_पढ़ो(ov965x->regmap, addr, &buf);
	अगर (!ret)
		*val = buf;
	अन्यथा
		*val = -1;

	v4l2_dbg(2, debug, &ov965x->sd, "%s: 0x%02x @ 0x%02x. (%d)\n",
		 __func__, *val, addr, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ov965x_ग_लिखो(काष्ठा ov965x *ov965x, u8 addr, u8 val)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(ov965x->regmap, addr, val);

	v4l2_dbg(2, debug, &ov965x->sd, "%s: 0x%02x @ 0x%02X (%d)\n",
		 __func__, val, addr, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ov965x_ग_लिखो_array(काष्ठा ov965x *ov965x,
			      स्थिर काष्ठा i2c_rv *regs)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; ret == 0 && regs[i].addr != REG_शून्य; i++)
		ret = ov965x_ग_लिखो(ov965x, regs[i].addr, regs[i].value);

	वापस ret;
पूर्ण

अटल पूर्णांक ov965x_set_शेष_gamma_curve(काष्ठा ov965x *ov965x)
अणु
	अटल स्थिर u8 gamma_curve[] = अणु
		/* Values taken from OV application note. */
		0x40, 0x30, 0x4b, 0x60, 0x70, 0x70, 0x70, 0x70,
		0x60, 0x60, 0x50, 0x48, 0x3a, 0x2e, 0x28, 0x22,
		0x04, 0x07, 0x10, 0x28,	0x36, 0x44, 0x52, 0x60,
		0x6c, 0x78, 0x8c, 0x9e, 0xbb, 0xd2, 0xe6
	पूर्ण;
	u8 addr = REG_GSP;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(gamma_curve); i++) अणु
		पूर्णांक ret = ov965x_ग_लिखो(ov965x, addr, gamma_curve[i]);

		अगर (ret < 0)
			वापस ret;
		addr++;
	पूर्ण

	वापस 0;
पूर्ण;

अटल पूर्णांक ov965x_set_color_matrix(काष्ठा ov965x *ov965x)
अणु
	अटल स्थिर u8 mtx[] = अणु
		/* MTX1..MTX9, MTXS */
		0x3a, 0x3d, 0x03, 0x12, 0x26, 0x38, 0x40, 0x40, 0x40, 0x0d
	पूर्ण;
	u8 addr = REG_MTX(1);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mtx); i++) अणु
		पूर्णांक ret = ov965x_ग_लिखो(ov965x, addr, mtx[i]);

		अगर (ret < 0)
			वापस ret;
		addr++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __ov965x_set_घातer(काष्ठा ov965x *ov965x, पूर्णांक on)
अणु
	अगर (on) अणु
		पूर्णांक ret = clk_prepare_enable(ov965x->clk);

		अगर (ret)
			वापस ret;

		gpiod_set_value_cansleep(ov965x->gpios[GPIO_PWDN], 0);
		gpiod_set_value_cansleep(ov965x->gpios[GPIO_RST], 0);
		msleep(25);
	पूर्ण अन्यथा अणु
		gpiod_set_value_cansleep(ov965x->gpios[GPIO_RST], 1);
		gpiod_set_value_cansleep(ov965x->gpios[GPIO_PWDN], 1);

		clk_disable_unprepare(ov965x->clk);
	पूर्ण

	ov965x->streaming = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ov965x_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ov965x *ov965x = to_ov965x(sd);
	पूर्णांक ret = 0;

	v4l2_dbg(1, debug, sd, "%s: on: %d\n", __func__, on);

	mutex_lock(&ov965x->lock);
	अगर (ov965x->घातer == !on) अणु
		ret = __ov965x_set_घातer(ov965x, on);
		अगर (!ret && on) अणु
			ret = ov965x_ग_लिखो_array(ov965x,
						 ov965x_init_regs);
			ov965x->apply_frame_fmt = 1;
			ov965x->ctrls.update = 1;
		पूर्ण
	पूर्ण
	अगर (!ret)
		ov965x->घातer += on ? 1 : -1;

	WARN_ON(ov965x->घातer < 0);
	mutex_unlock(&ov965x->lock);
	वापस ret;
पूर्ण

/*
 * V4L2 controls
 */

अटल व्योम ov965x_update_exposure_ctrl(काष्ठा ov965x *ov965x)
अणु
	काष्ठा v4l2_ctrl *ctrl = ov965x->ctrls.exposure;
	अचिन्हित दीर्घ fपूर्णांक, trow;
	पूर्णांक min, max, def;
	u8 clkrc;

	mutex_lock(&ov965x->lock);
	अगर (WARN_ON(!ctrl || !ov965x->frame_size)) अणु
		mutex_unlock(&ov965x->lock);
		वापस;
	पूर्ण
	clkrc = DEF_CLKRC + ov965x->fiv->clkrc_भाग;
	/* Calculate पूर्णांकernal घड़ी frequency */
	fपूर्णांक = ov965x->mclk_frequency * ((clkrc >> 7) + 1) /
				((2 * ((clkrc & 0x3f) + 1)));
	/* and the row पूर्णांकerval (in us). */
	trow = (2 * 1520 * 1000000UL) / fपूर्णांक;
	max = ov965x->frame_size->max_exp_lines * trow;
	ov965x->exp_row_पूर्णांकerval = trow;
	mutex_unlock(&ov965x->lock);

	v4l2_dbg(1, debug, &ov965x->sd, "clkrc: %#x, fi: %lu, tr: %lu, %d\n",
		 clkrc, fपूर्णांक, trow, max);

	/* Update exposure समय range to match current frame क्रमmat. */
	min = (trow + 100) / 100;
	max = (max - 100) / 100;
	def = min + (max - min) / 2;

	अगर (v4l2_ctrl_modअगरy_range(ctrl, min, max, 1, def))
		v4l2_err(&ov965x->sd, "Exposure ctrl range update failed\n");
पूर्ण

अटल पूर्णांक ov965x_set_banding_filter(काष्ठा ov965x *ov965x, पूर्णांक value)
अणु
	अचिन्हित दीर्घ mbd, light_freq;
	पूर्णांक ret;
	u8 reg;

	ret = ov965x_पढ़ो(ov965x, REG_COM8, &reg);
	अगर (!ret) अणु
		अगर (value == V4L2_CID_POWER_LINE_FREQUENCY_DISABLED)
			reg &= ~COM8_BFILT;
		अन्यथा
			reg |= COM8_BFILT;
		ret = ov965x_ग_लिखो(ov965x, REG_COM8, reg);
	पूर्ण
	अगर (value == V4L2_CID_POWER_LINE_FREQUENCY_DISABLED)
		वापस 0;
	अगर (WARN_ON(!ov965x->fiv))
		वापस -EINVAL;
	/* Set minimal exposure समय क्रम 50/60 HZ lighting */
	अगर (value == V4L2_CID_POWER_LINE_FREQUENCY_50HZ)
		light_freq = 50;
	अन्यथा
		light_freq = 60;
	mbd = (1000UL * ov965x->fiv->पूर्णांकerval.denominator *
	       ov965x->frame_size->max_exp_lines) /
	       ov965x->fiv->पूर्णांकerval.numerator;
	mbd = ((mbd / (light_freq * 2)) + 500) / 1000UL;

	वापस ov965x_ग_लिखो(ov965x, REG_MBD, mbd);
पूर्ण

अटल पूर्णांक ov965x_set_white_balance(काष्ठा ov965x *ov965x, पूर्णांक awb)
अणु
	पूर्णांक ret;
	u8 reg;

	ret = ov965x_पढ़ो(ov965x, REG_COM8, &reg);
	अगर (!ret) अणु
		reg = awb ? reg | REG_COM8 : reg & ~REG_COM8;
		ret = ov965x_ग_लिखो(ov965x, REG_COM8, reg);
	पूर्ण
	अगर (!ret && !awb) अणु
		ret = ov965x_ग_लिखो(ov965x, REG_BLUE,
				   ov965x->ctrls.blue_balance->val);
		अगर (ret < 0)
			वापस ret;
		ret = ov965x_ग_लिखो(ov965x, REG_RED,
				   ov965x->ctrls.red_balance->val);
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा NUM_BR_LEVELS	7
#घोषणा NUM_BR_REGS	3

अटल पूर्णांक ov965x_set_brightness(काष्ठा ov965x *ov965x, पूर्णांक val)
अणु
	अटल स्थिर u8 regs[NUM_BR_LEVELS + 1][NUM_BR_REGS] = अणु
		अणु REG_AEW, REG_AEB, REG_VPT पूर्ण,
		अणु 0x1c, 0x12, 0x50 पूर्ण, /* -3 */
		अणु 0x3d, 0x30, 0x71 पूर्ण, /* -2 */
		अणु 0x50, 0x44, 0x92 पूर्ण, /* -1 */
		अणु 0x70, 0x64, 0xc3 पूर्ण, /*  0 */
		अणु 0x90, 0x84, 0xd4 पूर्ण, /* +1 */
		अणु 0xc4, 0xbf, 0xf9 पूर्ण, /* +2 */
		अणु 0xd8, 0xd0, 0xfa पूर्ण, /* +3 */
	पूर्ण;
	पूर्णांक i, ret = 0;

	val += (NUM_BR_LEVELS / 2 + 1);
	अगर (val > NUM_BR_LEVELS)
		वापस -EINVAL;

	क्रम (i = 0; i < NUM_BR_REGS && !ret; i++)
		ret = ov965x_ग_लिखो(ov965x, regs[0][i],
				   regs[val][i]);
	वापस ret;
पूर्ण

अटल पूर्णांक ov965x_set_gain(काष्ठा ov965x *ov965x, पूर्णांक स्वतः_gain)
अणु
	काष्ठा ov965x_ctrls *ctrls = &ov965x->ctrls;
	पूर्णांक ret = 0;
	u8 reg;
	/*
	 * For manual mode we need to disable AGC first, so
	 * gain value in REG_VREF, REG_GAIN is not overwritten.
	 */
	अगर (ctrls->स्वतः_gain->is_new) अणु
		ret = ov965x_पढ़ो(ov965x, REG_COM8, &reg);
		अगर (ret < 0)
			वापस ret;
		अगर (ctrls->स्वतः_gain->val)
			reg |= COM8_AGC;
		अन्यथा
			reg &= ~COM8_AGC;
		ret = ov965x_ग_लिखो(ov965x, REG_COM8, reg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (ctrls->gain->is_new && !स्वतः_gain) अणु
		अचिन्हित पूर्णांक gain = ctrls->gain->val;
		अचिन्हित पूर्णांक rgain;
		पूर्णांक m;
		/*
		 * Convert gain control value to the sensor's gain
		 * रेजिस्टरs (VREF[7:6], GAIN[7:0]) क्रमmat.
		 */
		क्रम (m = 6; m >= 0; m--)
			अगर (gain >= (1 << m) * 16)
				अवरोध;

		/* Sanity check: करोn't adjust the gain with a negative value */
		अगर (m < 0)
			वापस -EINVAL;

		rgain = (gain - ((1 << m) * 16)) / (1 << m);
		rgain |= (((1 << m) - 1) << 4);

		ret = ov965x_ग_लिखो(ov965x, REG_GAIN, rgain & 0xff);
		अगर (ret < 0)
			वापस ret;
		ret = ov965x_पढ़ो(ov965x, REG_VREF, &reg);
		अगर (ret < 0)
			वापस ret;
		reg &= ~VREF_GAIN_MASK;
		reg |= (((rgain >> 8) & 0x3) << 6);
		ret = ov965x_ग_लिखो(ov965x, REG_VREF, reg);
		अगर (ret < 0)
			वापस ret;
		/* Return updated control's value to userspace */
		ctrls->gain->val = (1 << m) * (16 + (rgain & 0xf));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ov965x_set_sharpness(काष्ठा ov965x *ov965x, अचिन्हित पूर्णांक value)
अणु
	u8 com14, edge;
	पूर्णांक ret;

	ret = ov965x_पढ़ो(ov965x, REG_COM14, &com14);
	अगर (ret < 0)
		वापस ret;
	ret = ov965x_पढ़ो(ov965x, REG_EDGE, &edge);
	अगर (ret < 0)
		वापस ret;
	com14 = value ? com14 | COM14_EDGE_EN : com14 & ~COM14_EDGE_EN;
	value--;
	अगर (value > 0x0f) अणु
		com14 |= COM14_EEF_X2;
		value >>= 1;
	पूर्ण अन्यथा अणु
		com14 &= ~COM14_EEF_X2;
	पूर्ण
	ret = ov965x_ग_लिखो(ov965x, REG_COM14, com14);
	अगर (ret < 0)
		वापस ret;

	edge &= ~EDGE_FACTOR_MASK;
	edge |= ((u8)value & 0x0f);

	वापस ov965x_ग_लिखो(ov965x, REG_EDGE, edge);
पूर्ण

अटल पूर्णांक ov965x_set_exposure(काष्ठा ov965x *ov965x, पूर्णांक exp)
अणु
	काष्ठा ov965x_ctrls *ctrls = &ov965x->ctrls;
	bool स्वतः_exposure = (exp == V4L2_EXPOSURE_AUTO);
	पूर्णांक ret;
	u8 reg;

	अगर (ctrls->स्वतः_exp->is_new) अणु
		ret = ov965x_पढ़ो(ov965x, REG_COM8, &reg);
		अगर (ret < 0)
			वापस ret;
		अगर (स्वतः_exposure)
			reg |= (COM8_AEC | COM8_AGC);
		अन्यथा
			reg &= ~(COM8_AEC | COM8_AGC);
		ret = ov965x_ग_लिखो(ov965x, REG_COM8, reg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (!स्वतः_exposure && ctrls->exposure->is_new) अणु
		अचिन्हित पूर्णांक exposure = (ctrls->exposure->val * 100)
					 / ov965x->exp_row_पूर्णांकerval;
		/*
		 * Manual exposure value
		 * [b15:b0] - AECHM (b15:b10), AECH (b9:b2), COM1 (b1:b0)
		 */
		ret = ov965x_ग_लिखो(ov965x, REG_COM1, exposure & 0x3);
		अगर (!ret)
			ret = ov965x_ग_लिखो(ov965x, REG_AECH,
					   (exposure >> 2) & 0xff);
		अगर (!ret)
			ret = ov965x_ग_लिखो(ov965x, REG_AECHM,
					   (exposure >> 10) & 0x3f);
		/* Update the value to minimize rounding errors */
		ctrls->exposure->val = ((exposure * ov965x->exp_row_पूर्णांकerval)
							+ 50) / 100;
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	v4l2_ctrl_activate(ov965x->ctrls.brightness, !exp);
	वापस 0;
पूर्ण

अटल पूर्णांक ov965x_set_flip(काष्ठा ov965x *ov965x)
अणु
	u8 mvfp = 0;

	अगर (ov965x->ctrls.hflip->val)
		mvfp |= MVFP_MIRROR;

	अगर (ov965x->ctrls.vflip->val)
		mvfp |= MVFP_FLIP;

	वापस ov965x_ग_लिखो(ov965x, REG_MVFP, mvfp);
पूर्ण

#घोषणा NUM_SAT_LEVELS	5
#घोषणा NUM_SAT_REGS	6

अटल पूर्णांक ov965x_set_saturation(काष्ठा ov965x *ov965x, पूर्णांक val)
अणु
	अटल स्थिर u8 regs[NUM_SAT_LEVELS][NUM_SAT_REGS] = अणु
		/* MTX(1)...MTX(6) */
		अणु 0x1d, 0x1f, 0x02, 0x09, 0x13, 0x1c पूर्ण, /* -2 */
		अणु 0x2e, 0x31, 0x02, 0x0e, 0x1e, 0x2d पूर्ण, /* -1 */
		अणु 0x3a, 0x3d, 0x03, 0x12, 0x26, 0x38 पूर्ण, /*  0 */
		अणु 0x46, 0x49, 0x04, 0x16, 0x2e, 0x43 पूर्ण, /* +1 */
		अणु 0x57, 0x5c, 0x05, 0x1b, 0x39, 0x54 पूर्ण, /* +2 */
	पूर्ण;
	u8 addr = REG_MTX(1);
	पूर्णांक i, ret = 0;

	val += (NUM_SAT_LEVELS / 2);
	अगर (val >= NUM_SAT_LEVELS)
		वापस -EINVAL;

	क्रम (i = 0; i < NUM_SAT_REGS && !ret; i++)
		ret = ov965x_ग_लिखो(ov965x, addr + i, regs[val][i]);

	वापस ret;
पूर्ण

अटल पूर्णांक ov965x_set_test_pattern(काष्ठा ov965x *ov965x, पूर्णांक value)
अणु
	पूर्णांक ret;
	u8 reg;

	ret = ov965x_पढ़ो(ov965x, REG_COM23, &reg);
	अगर (ret < 0)
		वापस ret;
	reg = value ? reg | COM23_TEST_MODE : reg & ~COM23_TEST_MODE;
	वापस ov965x_ग_लिखो(ov965x, REG_COM23, reg);
पूर्ण

अटल पूर्णांक __g_अस्थिर_ctrl(काष्ठा ov965x *ov965x, काष्ठा v4l2_ctrl *ctrl)
अणु
	अचिन्हित पूर्णांक exposure, gain, m;
	u8 reg0, reg1, reg2;
	पूर्णांक ret;

	अगर (!ov965x->घातer)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		अगर (!ctrl->val)
			वापस 0;
		ret = ov965x_पढ़ो(ov965x, REG_GAIN, &reg0);
		अगर (ret < 0)
			वापस ret;
		ret = ov965x_पढ़ो(ov965x, REG_VREF, &reg1);
		अगर (ret < 0)
			वापस ret;
		gain = ((reg1 >> 6) << 8) | reg0;
		m = 0x01 << fls(gain >> 4);
		ov965x->ctrls.gain->val = m * (16 + (gain & 0xf));
		अवरोध;

	हाल V4L2_CID_EXPOSURE_AUTO:
		अगर (ctrl->val == V4L2_EXPOSURE_MANUAL)
			वापस 0;
		ret = ov965x_पढ़ो(ov965x, REG_COM1, &reg0);
		अगर (ret < 0)
			वापस ret;
		ret = ov965x_पढ़ो(ov965x, REG_AECH, &reg1);
		अगर (ret < 0)
			वापस ret;
		ret = ov965x_पढ़ो(ov965x, REG_AECHM, &reg2);
		अगर (ret < 0)
			वापस ret;
		exposure = ((reg2 & 0x3f) << 10) | (reg1 << 2) |
						(reg0 & 0x3);
		ov965x->ctrls.exposure->val = ((exposure *
				ov965x->exp_row_पूर्णांकerval) + 50) / 100;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov965x_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = ctrl_to_sd(ctrl);
	काष्ठा ov965x *ov965x = to_ov965x(sd);
	पूर्णांक ret;

	v4l2_dbg(1, debug, sd, "g_ctrl: %s\n", ctrl->name);

	mutex_lock(&ov965x->lock);
	ret = __g_अस्थिर_ctrl(ov965x, ctrl);
	mutex_unlock(&ov965x->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov965x_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = ctrl_to_sd(ctrl);
	काष्ठा ov965x *ov965x = to_ov965x(sd);
	पूर्णांक ret = -EINVAL;

	v4l2_dbg(1, debug, sd, "s_ctrl: %s, value: %d. power: %d\n",
		 ctrl->name, ctrl->val, ov965x->घातer);

	mutex_lock(&ov965x->lock);
	/*
	 * If the device is not घातered up now postpone applying control's
	 * value to the hardware, until it is पढ़ोy to accept commands.
	 */
	अगर (ov965x->घातer == 0) अणु
		mutex_unlock(&ov965x->lock);
		वापस 0;
	पूर्ण

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		ret = ov965x_set_white_balance(ov965x, ctrl->val);
		अवरोध;

	हाल V4L2_CID_BRIGHTNESS:
		ret = ov965x_set_brightness(ov965x, ctrl->val);
		अवरोध;

	हाल V4L2_CID_EXPOSURE_AUTO:
		ret = ov965x_set_exposure(ov965x, ctrl->val);
		अवरोध;

	हाल V4L2_CID_AUTOGAIN:
		ret = ov965x_set_gain(ov965x, ctrl->val);
		अवरोध;

	हाल V4L2_CID_HFLIP:
		ret = ov965x_set_flip(ov965x);
		अवरोध;

	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		ret = ov965x_set_banding_filter(ov965x, ctrl->val);
		अवरोध;

	हाल V4L2_CID_SATURATION:
		ret = ov965x_set_saturation(ov965x, ctrl->val);
		अवरोध;

	हाल V4L2_CID_SHARPNESS:
		ret = ov965x_set_sharpness(ov965x, ctrl->val);
		अवरोध;

	हाल V4L2_CID_TEST_PATTERN:
		ret = ov965x_set_test_pattern(ov965x, ctrl->val);
		अवरोध;
	पूर्ण

	mutex_unlock(&ov965x->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov965x_ctrl_ops = अणु
	.g_अस्थिर_ctrl = ov965x_g_अस्थिर_ctrl,
	.s_ctrl	= ov965x_s_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर test_pattern_menu[] = अणु
	"Disabled",
	"Color bars",
पूर्ण;

अटल पूर्णांक ov965x_initialize_controls(काष्ठा ov965x *ov965x)
अणु
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &ov965x_ctrl_ops;
	काष्ठा ov965x_ctrls *ctrls = &ov965x->ctrls;
	काष्ठा v4l2_ctrl_handler *hdl = &ctrls->handler;
	पूर्णांक ret;

	ret = v4l2_ctrl_handler_init(hdl, 16);
	अगर (ret < 0)
		वापस ret;

	/* Auto/manual white balance */
	ctrls->स्वतः_wb = v4l2_ctrl_new_std(hdl, ops,
					   V4L2_CID_AUTO_WHITE_BALANCE,
					   0, 1, 1, 1);
	ctrls->blue_balance = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_BLUE_BALANCE,
						0, 0xff, 1, 0x80);
	ctrls->red_balance = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_RED_BALANCE,
					       0, 0xff, 1, 0x80);
	/* Auto/manual exposure */
	ctrls->स्वतः_exp =
		v4l2_ctrl_new_std_menu(hdl, ops,
				       V4L2_CID_EXPOSURE_AUTO,
				       V4L2_EXPOSURE_MANUAL, 0,
				       V4L2_EXPOSURE_AUTO);
	/* Exposure समय, in 100 us units. min/max is updated dynamically. */
	ctrls->exposure = v4l2_ctrl_new_std(hdl, ops,
					    V4L2_CID_EXPOSURE_ABSOLUTE,
					    2, 1500, 1, 500);
	/* Auto/manual gain */
	ctrls->स्वतः_gain = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_AUTOGAIN,
					     0, 1, 1, 1);
	ctrls->gain = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_GAIN,
					16, 64 * (16 + 15), 1, 64 * 16);

	ctrls->saturation = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_SATURATION,
					      -2, 2, 1, 0);
	ctrls->brightness = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_BRIGHTNESS,
					      -3, 3, 1, 0);
	ctrls->sharpness = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_SHARPNESS,
					     0, 32, 1, 6);

	ctrls->hflip = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_HFLIP, 0, 1, 1, 0);
	ctrls->vflip = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_VFLIP, 0, 1, 1, 0);

	ctrls->light_freq =
		v4l2_ctrl_new_std_menu(hdl, ops,
				       V4L2_CID_POWER_LINE_FREQUENCY,
				       V4L2_CID_POWER_LINE_FREQUENCY_60HZ, ~0x7,
				       V4L2_CID_POWER_LINE_FREQUENCY_50HZ);

	v4l2_ctrl_new_std_menu_items(hdl, ops, V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(test_pattern_menu) - 1, 0, 0,
				     test_pattern_menu);
	अगर (hdl->error) अणु
		ret = hdl->error;
		v4l2_ctrl_handler_मुक्त(hdl);
		वापस ret;
	पूर्ण

	ctrls->gain->flags |= V4L2_CTRL_FLAG_VOLATILE;
	ctrls->exposure->flags |= V4L2_CTRL_FLAG_VOLATILE;

	v4l2_ctrl_स्वतः_cluster(3, &ctrls->स्वतः_wb, 0, false);
	v4l2_ctrl_स्वतः_cluster(2, &ctrls->स्वतः_gain, 0, true);
	v4l2_ctrl_स्वतः_cluster(2, &ctrls->स्वतः_exp, 1, true);
	v4l2_ctrl_cluster(2, &ctrls->hflip);

	ov965x->sd.ctrl_handler = hdl;
	वापस 0;
पूर्ण

/*
 * V4L2 subdev video and pad level operations
 */
अटल व्योम ov965x_get_शेष_क्रमmat(काष्ठा v4l2_mbus_framefmt *mf)
अणु
	mf->width = ov965x_framesizes[0].width;
	mf->height = ov965x_framesizes[0].height;
	mf->colorspace = ov965x_क्रमmats[0].colorspace;
	mf->code = ov965x_क्रमmats[0].code;
	mf->field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक ov965x_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= ARRAY_SIZE(ov965x_क्रमmats))
		वापस -EINVAL;

	code->code = ov965x_क्रमmats[code->index].code;
	वापस 0;
पूर्ण

अटल पूर्णांक ov965x_क्रमागत_frame_sizes(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	पूर्णांक i = ARRAY_SIZE(ov965x_क्रमmats);

	अगर (fse->index >= ARRAY_SIZE(ov965x_framesizes))
		वापस -EINVAL;

	जबतक (--i)
		अगर (fse->code == ov965x_क्रमmats[i].code)
			अवरोध;

	fse->code = ov965x_क्रमmats[i].code;

	fse->min_width  = ov965x_framesizes[fse->index].width;
	fse->max_width  = fse->min_width;
	fse->max_height = ov965x_framesizes[fse->index].height;
	fse->min_height = fse->max_height;

	वापस 0;
पूर्ण

अटल पूर्णांक ov965x_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा ov965x *ov965x = to_ov965x(sd);

	mutex_lock(&ov965x->lock);
	fi->पूर्णांकerval = ov965x->fiv->पूर्णांकerval;
	mutex_unlock(&ov965x->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __ov965x_set_frame_पूर्णांकerval(काष्ठा ov965x *ov965x,
				       काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &ov965x->क्रमmat;
	स्थिर काष्ठा ov965x_पूर्णांकerval *fiv = &ov965x_पूर्णांकervals[0];
	u64 req_पूर्णांक, err, min_err = ~0ULL;
	अचिन्हित पूर्णांक i;

	अगर (fi->पूर्णांकerval.denominator == 0)
		वापस -EINVAL;

	req_पूर्णांक = (u64)fi->पूर्णांकerval.numerator * 10000;
	करो_भाग(req_पूर्णांक, fi->पूर्णांकerval.denominator);

	क्रम (i = 0; i < ARRAY_SIZE(ov965x_पूर्णांकervals); i++) अणु
		स्थिर काष्ठा ov965x_पूर्णांकerval *iv = &ov965x_पूर्णांकervals[i];

		अगर (mbus_fmt->width != iv->size.width ||
		    mbus_fmt->height != iv->size.height)
			जारी;
		err = असल((u64)(iv->पूर्णांकerval.numerator * 10000) /
			    iv->पूर्णांकerval.denominator - req_पूर्णांक);
		अगर (err < min_err) अणु
			fiv = iv;
			min_err = err;
		पूर्ण
	पूर्ण
	ov965x->fiv = fiv;

	v4l2_dbg(1, debug, &ov965x->sd, "Changed frame interval to %u us\n",
		 fiv->पूर्णांकerval.numerator * 1000000 / fiv->पूर्णांकerval.denominator);

	वापस 0;
पूर्ण

अटल पूर्णांक ov965x_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा ov965x *ov965x = to_ov965x(sd);
	पूर्णांक ret;

	v4l2_dbg(1, debug, sd, "Setting %d/%d frame interval\n",
		 fi->पूर्णांकerval.numerator, fi->पूर्णांकerval.denominator);

	mutex_lock(&ov965x->lock);
	ret = __ov965x_set_frame_पूर्णांकerval(ov965x, fi);
	ov965x->apply_frame_fmt = 1;
	mutex_unlock(&ov965x->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov965x_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov965x *ov965x = to_ov965x(sd);
	काष्ठा v4l2_mbus_framefmt *mf;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		fmt->क्रमmat = *mf;
		वापस 0;
	पूर्ण

	mutex_lock(&ov965x->lock);
	fmt->क्रमmat = ov965x->क्रमmat;
	mutex_unlock(&ov965x->lock);

	वापस 0;
पूर्ण

अटल व्योम __ov965x_try_frame_size(काष्ठा v4l2_mbus_framefmt *mf,
				    स्थिर काष्ठा ov965x_framesize **size)
अणु
	स्थिर काष्ठा ov965x_framesize *fsize = &ov965x_framesizes[0],
		*match = शून्य;
	पूर्णांक i = ARRAY_SIZE(ov965x_framesizes);
	अचिन्हित पूर्णांक min_err = अच_पूर्णांक_उच्च;

	जबतक (i--) अणु
		पूर्णांक err = असल(fsize->width - mf->width)
				+ असल(fsize->height - mf->height);
		अगर (err < min_err) अणु
			min_err = err;
			match = fsize;
		पूर्ण
		fsize++;
	पूर्ण
	अगर (!match)
		match = &ov965x_framesizes[0];
	mf->width  = match->width;
	mf->height = match->height;
	अगर (size)
		*size = match;
पूर्ण

अटल पूर्णांक ov965x_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	अचिन्हित पूर्णांक index = ARRAY_SIZE(ov965x_क्रमmats);
	काष्ठा v4l2_mbus_framefmt *mf = &fmt->क्रमmat;
	काष्ठा ov965x *ov965x = to_ov965x(sd);
	स्थिर काष्ठा ov965x_framesize *size = शून्य;
	पूर्णांक ret = 0;

	__ov965x_try_frame_size(mf, &size);

	जबतक (--index)
		अगर (ov965x_क्रमmats[index].code == mf->code)
			अवरोध;

	mf->colorspace	= V4L2_COLORSPACE_JPEG;
	mf->code	= ov965x_क्रमmats[index].code;
	mf->field	= V4L2_FIELD_NONE;

	mutex_lock(&ov965x->lock);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		अगर (cfg) अणु
			mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
			*mf = fmt->क्रमmat;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ov965x->streaming) अणु
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			ov965x->frame_size = size;
			ov965x->क्रमmat = fmt->क्रमmat;
			ov965x->tslb_reg = ov965x_क्रमmats[index].tslb_reg;
			ov965x->apply_frame_fmt = 1;
		पूर्ण
	पूर्ण

	अगर (!ret && fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		काष्ठा v4l2_subdev_frame_पूर्णांकerval fiv = अणु
			.पूर्णांकerval = अणु 0, 1 पूर्ण
		पूर्ण;
		/* Reset to minimum possible frame पूर्णांकerval */
		__ov965x_set_frame_पूर्णांकerval(ov965x, &fiv);
	पूर्ण
	mutex_unlock(&ov965x->lock);

	अगर (!ret)
		ov965x_update_exposure_ctrl(ov965x);

	वापस ret;
पूर्ण

अटल पूर्णांक ov965x_set_frame_size(काष्ठा ov965x *ov965x)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; ret == 0 && i < NUM_FMT_REGS; i++)
		ret = ov965x_ग_लिखो(ov965x, frame_size_reg_addr[i],
				   ov965x->frame_size->regs[i]);
	वापस ret;
पूर्ण

अटल पूर्णांक __ov965x_set_params(काष्ठा ov965x *ov965x)
अणु
	काष्ठा ov965x_ctrls *ctrls = &ov965x->ctrls;
	पूर्णांक ret = 0;
	u8 reg;

	अगर (ov965x->apply_frame_fmt) अणु
		reg = DEF_CLKRC + ov965x->fiv->clkrc_भाग;
		ret = ov965x_ग_लिखो(ov965x, REG_CLKRC, reg);
		अगर (ret < 0)
			वापस ret;
		ret = ov965x_set_frame_size(ov965x);
		अगर (ret < 0)
			वापस ret;
		ret = ov965x_पढ़ो(ov965x, REG_TSLB, &reg);
		अगर (ret < 0)
			वापस ret;
		reg &= ~TSLB_YUYV_MASK;
		reg |= ov965x->tslb_reg;
		ret = ov965x_ग_लिखो(ov965x, REG_TSLB, reg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	ret = ov965x_set_शेष_gamma_curve(ov965x);
	अगर (ret < 0)
		वापस ret;
	ret = ov965x_set_color_matrix(ov965x);
	अगर (ret < 0)
		वापस ret;
	/*
	 * Select manual banding filter, the filter will
	 * be enabled further अगर required.
	 */
	ret = ov965x_पढ़ो(ov965x, REG_COM11, &reg);
	अगर (!ret)
		reg |= COM11_BANDING;
	ret = ov965x_ग_लिखो(ov965x, REG_COM11, reg);
	अगर (ret < 0)
		वापस ret;
	/*
	 * Banding filter (REG_MBD value) needs to match selected
	 * resolution and frame rate, so it's always updated here.
	 */
	वापस ov965x_set_banding_filter(ov965x, ctrls->light_freq->val);
पूर्ण

अटल पूर्णांक ov965x_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ov965x *ov965x = to_ov965x(sd);
	काष्ठा ov965x_ctrls *ctrls = &ov965x->ctrls;
	पूर्णांक ret = 0;

	v4l2_dbg(1, debug, sd, "%s: on: %d\n", __func__, on);

	mutex_lock(&ov965x->lock);
	अगर (ov965x->streaming == !on) अणु
		अगर (on)
			ret = __ov965x_set_params(ov965x);

		अगर (!ret && ctrls->update) अणु
			/*
			 * ov965x_s_ctrl callback takes the mutex
			 * so it needs to be released here.
			 */
			mutex_unlock(&ov965x->lock);
			ret = v4l2_ctrl_handler_setup(&ctrls->handler);

			mutex_lock(&ov965x->lock);
			अगर (!ret)
				ctrls->update = 0;
		पूर्ण
		अगर (!ret)
			ret = ov965x_ग_लिखो(ov965x, REG_COM2,
					   on ? 0x01 : 0x11);
	पूर्ण
	अगर (!ret)
		ov965x->streaming += on ? 1 : -1;

	WARN_ON(ov965x->streaming < 0);
	mutex_unlock(&ov965x->lock);

	वापस ret;
पूर्ण

/*
 * V4L2 subdev पूर्णांकernal operations
 */
अटल पूर्णांक ov965x_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *mf =
		v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);

	ov965x_get_शेष_क्रमmat(mf);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov965x_pad_ops = अणु
	.क्रमागत_mbus_code = ov965x_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov965x_क्रमागत_frame_sizes,
	.get_fmt = ov965x_get_fmt,
	.set_fmt = ov965x_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov965x_video_ops = अणु
	.s_stream = ov965x_s_stream,
	.g_frame_पूर्णांकerval = ov965x_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = ov965x_s_frame_पूर्णांकerval,

पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ov965x_sd_पूर्णांकernal_ops = अणु
	.खोलो = ov965x_खोलो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov965x_core_ops = अणु
	.s_घातer = ov965x_s_घातer,
	.log_status = v4l2_ctrl_subdev_log_status,
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov965x_subdev_ops = अणु
	.core = &ov965x_core_ops,
	.pad = &ov965x_pad_ops,
	.video = &ov965x_video_ops,
पूर्ण;

/*
 * Reset and घातer करोwn GPIOs configuration
 */
अटल पूर्णांक ov965x_configure_gpios_pdata(काष्ठा ov965x *ov965x,
				स्थिर काष्ठा ov9650_platक्रमm_data *pdata)
अणु
	पूर्णांक ret, i;
	पूर्णांक gpios[NUM_GPIOS];
	काष्ठा device *dev = regmap_get_device(ov965x->regmap);

	gpios[GPIO_PWDN] = pdata->gpio_pwdn;
	gpios[GPIO_RST]  = pdata->gpio_reset;

	क्रम (i = 0; i < ARRAY_SIZE(ov965x->gpios); i++) अणु
		पूर्णांक gpio = gpios[i];

		अगर (!gpio_is_valid(gpio))
			जारी;
		ret = devm_gpio_request_one(dev, gpio,
					    GPIOF_OUT_INIT_HIGH, "OV965X");
		अगर (ret < 0)
			वापस ret;
		v4l2_dbg(1, debug, &ov965x->sd, "set gpio %d to 1\n", gpio);

		gpio_set_value_cansleep(gpio, 1);
		gpio_export(gpio, 0);
		ov965x->gpios[i] = gpio_to_desc(gpio);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov965x_configure_gpios(काष्ठा ov965x *ov965x)
अणु
	काष्ठा device *dev = regmap_get_device(ov965x->regmap);

	ov965x->gpios[GPIO_PWDN] = devm_gpiod_get_optional(dev, "powerdown",
							GPIOD_OUT_HIGH);
	अगर (IS_ERR(ov965x->gpios[GPIO_PWDN])) अणु
		dev_info(dev, "can't get %s GPIO\n", "powerdown");
		वापस PTR_ERR(ov965x->gpios[GPIO_PWDN]);
	पूर्ण

	ov965x->gpios[GPIO_RST] = devm_gpiod_get_optional(dev, "reset",
							GPIOD_OUT_HIGH);
	अगर (IS_ERR(ov965x->gpios[GPIO_RST])) अणु
		dev_info(dev, "can't get %s GPIO\n", "reset");
		वापस PTR_ERR(ov965x->gpios[GPIO_RST]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov965x_detect_sensor(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ov965x *ov965x = to_ov965x(sd);
	u8 pid, ver;
	पूर्णांक ret;

	mutex_lock(&ov965x->lock);
	ret = __ov965x_set_घातer(ov965x, 1);
	अगर (ret)
		जाओ out;

	msleep(25);

	/* Check sensor revision */
	ret = ov965x_पढ़ो(ov965x, REG_PID, &pid);
	अगर (!ret)
		ret = ov965x_पढ़ो(ov965x, REG_VER, &ver);

	__ov965x_set_घातer(ov965x, 0);

	अगर (!ret) अणु
		ov965x->id = OV965X_ID(pid, ver);
		अगर (ov965x->id == OV9650_ID || ov965x->id == OV9652_ID) अणु
			v4l2_info(sd, "Found OV%04X sensor\n", ov965x->id);
		पूर्ण अन्यथा अणु
			v4l2_err(sd, "Sensor detection failed (%04X, %d)\n",
				 ov965x->id, ret);
			ret = -ENODEV;
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&ov965x->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov965x_probe(काष्ठा i2c_client *client)
अणु
	स्थिर काष्ठा ov9650_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा v4l2_subdev *sd;
	काष्ठा ov965x *ov965x;
	पूर्णांक ret;
	अटल स्थिर काष्ठा regmap_config ov965x_regmap_config = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0xab,
	पूर्ण;

	ov965x = devm_kzalloc(&client->dev, माप(*ov965x), GFP_KERNEL);
	अगर (!ov965x)
		वापस -ENOMEM;

	ov965x->regmap = devm_regmap_init_sccb(client, &ov965x_regmap_config);
	अगर (IS_ERR(ov965x->regmap)) अणु
		dev_err(&client->dev, "Failed to allocate register map\n");
		वापस PTR_ERR(ov965x->regmap);
	पूर्ण

	अगर (pdata) अणु
		अगर (pdata->mclk_frequency == 0) अणु
			dev_err(&client->dev, "MCLK frequency not specified\n");
			वापस -EINVAL;
		पूर्ण
		ov965x->mclk_frequency = pdata->mclk_frequency;

		ret = ov965x_configure_gpios_pdata(ov965x, pdata);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (dev_fwnode(&client->dev)) अणु
		ov965x->clk = devm_clk_get(&client->dev, शून्य);
		अगर (IS_ERR(ov965x->clk))
			वापस PTR_ERR(ov965x->clk);
		ov965x->mclk_frequency = clk_get_rate(ov965x->clk);

		ret = ov965x_configure_gpios(ov965x);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		dev_err(&client->dev,
			"Neither platform data nor device property specified\n");

		वापस -EINVAL;
	पूर्ण

	mutex_init(&ov965x->lock);

	sd = &ov965x->sd;
	v4l2_i2c_subdev_init(sd, client, &ov965x_subdev_ops);
	strscpy(sd->name, DRIVER_NAME, माप(sd->name));

	sd->पूर्णांकernal_ops = &ov965x_sd_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
		     V4L2_SUBDEV_FL_HAS_EVENTS;

	ov965x->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sd->entity, 1, &ov965x->pad);
	अगर (ret < 0)
		जाओ err_mutex;

	ret = ov965x_initialize_controls(ov965x);
	अगर (ret < 0)
		जाओ err_me;

	ov965x_get_शेष_क्रमmat(&ov965x->क्रमmat);
	ov965x->frame_size = &ov965x_framesizes[0];
	ov965x->fiv = &ov965x_पूर्णांकervals[0];

	ret = ov965x_detect_sensor(sd);
	अगर (ret < 0)
		जाओ err_ctrls;

	/* Update exposure समय min/max to match frame क्रमmat */
	ov965x_update_exposure_ctrl(ov965x);

	ret = v4l2_async_रेजिस्टर_subdev(sd);
	अगर (ret < 0)
		जाओ err_ctrls;

	वापस 0;
err_ctrls:
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
err_me:
	media_entity_cleanup(&sd->entity);
err_mutex:
	mutex_destroy(&ov965x->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov965x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov965x *ov965x = to_ov965x(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	media_entity_cleanup(&sd->entity);
	mutex_destroy(&ov965x->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ov965x_id[] = अणु
	अणु "OV9650", 0 पूर्ण,
	अणु "OV9652", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ov965x_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id ov965x_of_match[] = अणु
	अणु .compatible = "ovti,ov9650", पूर्ण,
	अणु .compatible = "ovti,ov9652", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ov965x_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ov965x_i2c_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
		.of_match_table = of_match_ptr(ov965x_of_match),
	पूर्ण,
	.probe_new	= ov965x_probe,
	.हटाओ		= ov965x_हटाओ,
	.id_table	= ov965x_id,
पूर्ण;

module_i2c_driver(ov965x_i2c_driver);

MODULE_AUTHOR("Sylwester Nawrocki <sylvester.nawrocki@gmail.com>");
MODULE_DESCRIPTION("OV9650/OV9652 CMOS Image Sensor driver");
MODULE_LICENSE("GPL");
