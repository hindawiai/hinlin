<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम RJ54N1CB0C CMOS Image Sensor from Sharp
 *
 * Copyright (C) 2018, Jacopo Mondi <jacopo@jmondi.org>
 *
 * Copyright (C) 2009, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/videodev2.h>

#समावेश <media/i2c/rj54n1cb0c.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा RJ54N1_DEV_CODE			0x0400
#घोषणा RJ54N1_DEV_CODE2		0x0401
#घोषणा RJ54N1_OUT_SEL			0x0403
#घोषणा RJ54N1_XY_OUTPUT_SIZE_S_H	0x0404
#घोषणा RJ54N1_X_OUTPUT_SIZE_S_L	0x0405
#घोषणा RJ54N1_Y_OUTPUT_SIZE_S_L	0x0406
#घोषणा RJ54N1_XY_OUTPUT_SIZE_P_H	0x0407
#घोषणा RJ54N1_X_OUTPUT_SIZE_P_L	0x0408
#घोषणा RJ54N1_Y_OUTPUT_SIZE_P_L	0x0409
#घोषणा RJ54N1_LINE_LENGTH_PCK_S_H	0x040a
#घोषणा RJ54N1_LINE_LENGTH_PCK_S_L	0x040b
#घोषणा RJ54N1_LINE_LENGTH_PCK_P_H	0x040c
#घोषणा RJ54N1_LINE_LENGTH_PCK_P_L	0x040d
#घोषणा RJ54N1_RESIZE_N			0x040e
#घोषणा RJ54N1_RESIZE_N_STEP		0x040f
#घोषणा RJ54N1_RESIZE_STEP		0x0410
#घोषणा RJ54N1_RESIZE_HOLD_H		0x0411
#घोषणा RJ54N1_RESIZE_HOLD_L		0x0412
#घोषणा RJ54N1_H_OBEN_OFS		0x0413
#घोषणा RJ54N1_V_OBEN_OFS		0x0414
#घोषणा RJ54N1_RESIZE_CONTROL		0x0415
#घोषणा RJ54N1_STILL_CONTROL		0x0417
#घोषणा RJ54N1_INC_USE_SEL_H		0x0425
#घोषणा RJ54N1_INC_USE_SEL_L		0x0426
#घोषणा RJ54N1_MIRROR_STILL_MODE	0x0427
#घोषणा RJ54N1_INIT_START		0x0428
#घोषणा RJ54N1_SCALE_1_2_LEV		0x0429
#घोषणा RJ54N1_SCALE_4_LEV		0x042a
#घोषणा RJ54N1_Y_GAIN			0x04d8
#घोषणा RJ54N1_APT_GAIN_UP		0x04fa
#घोषणा RJ54N1_RA_SEL_UL		0x0530
#घोषणा RJ54N1_BYTE_SWAP		0x0531
#घोषणा RJ54N1_OUT_SIGPO		0x053b
#घोषणा RJ54N1_WB_SEL_WEIGHT_I		0x054e
#घोषणा RJ54N1_BIT8_WB			0x0569
#घोषणा RJ54N1_HCAPS_WB			0x056a
#घोषणा RJ54N1_VCAPS_WB			0x056b
#घोषणा RJ54N1_HCAPE_WB			0x056c
#घोषणा RJ54N1_VCAPE_WB			0x056d
#घोषणा RJ54N1_EXPOSURE_CONTROL		0x058c
#घोषणा RJ54N1_FRAME_LENGTH_S_H		0x0595
#घोषणा RJ54N1_FRAME_LENGTH_S_L		0x0596
#घोषणा RJ54N1_FRAME_LENGTH_P_H		0x0597
#घोषणा RJ54N1_FRAME_LENGTH_P_L		0x0598
#घोषणा RJ54N1_PEAK_H			0x05b7
#घोषणा RJ54N1_PEAK_50			0x05b8
#घोषणा RJ54N1_PEAK_60			0x05b9
#घोषणा RJ54N1_PEAK_DIFF		0x05ba
#घोषणा RJ54N1_IOC			0x05ef
#घोषणा RJ54N1_TG_BYPASS		0x0700
#घोषणा RJ54N1_PLL_L			0x0701
#घोषणा RJ54N1_PLL_N			0x0702
#घोषणा RJ54N1_PLL_EN			0x0704
#घोषणा RJ54N1_RATIO_TG			0x0706
#घोषणा RJ54N1_RATIO_T			0x0707
#घोषणा RJ54N1_RATIO_R			0x0708
#घोषणा RJ54N1_RAMP_TGCLK_EN		0x0709
#घोषणा RJ54N1_OCLK_DSP			0x0710
#घोषणा RJ54N1_RATIO_OP			0x0711
#घोषणा RJ54N1_RATIO_O			0x0712
#घोषणा RJ54N1_OCLK_SEL_EN		0x0713
#घोषणा RJ54N1_CLK_RST			0x0717
#घोषणा RJ54N1_RESET_STANDBY		0x0718
#घोषणा RJ54N1_FWFLG			0x07fe

#घोषणा E_EXCLK				(1 << 7)
#घोषणा SOFT_STDBY			(1 << 4)
#घोषणा SEN_RSTX			(1 << 2)
#घोषणा TG_RSTX				(1 << 1)
#घोषणा DSP_RSTX			(1 << 0)

#घोषणा RESIZE_HOLD_SEL			(1 << 2)
#घोषणा RESIZE_GO			(1 << 1)

/*
 * When cropping, the camera स्वतःmatically centers the cropped region, there
 * करोesn't seem to be a way to specअगरy an explicit location of the rectangle.
 */
#घोषणा RJ54N1_COLUMN_SKIP		0
#घोषणा RJ54N1_ROW_SKIP			0
#घोषणा RJ54N1_MAX_WIDTH		1600
#घोषणा RJ54N1_MAX_HEIGHT		1200

#घोषणा PLL_L				2
#घोषणा PLL_N				0x31

/* I2C addresses: 0x50, 0x51, 0x60, 0x61 */

/* RJ54N1CB0C has only one fixed colorspace per pixelcode */
काष्ठा rj54n1_datafmt अणु
	u32	code;
	क्रमागत v4l2_colorspace		colorspace;
पूर्ण;

/* Find a data क्रमmat by a pixel code in an array */
अटल स्थिर काष्ठा rj54n1_datafmt *rj54n1_find_datafmt(
	u32 code, स्थिर काष्ठा rj54n1_datafmt *fmt,
	पूर्णांक n)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < n; i++)
		अगर (fmt[i].code == code)
			वापस fmt + i;

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा rj54n1_datafmt rj54n1_colour_fmts[] = अणु
	अणुMEDIA_BUS_FMT_YUYV8_2X8, V4L2_COLORSPACE_JPEGपूर्ण,
	अणुMEDIA_BUS_FMT_YVYU8_2X8, V4L2_COLORSPACE_JPEGपूर्ण,
	अणुMEDIA_BUS_FMT_RGB565_2X8_LE, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_RGB565_2X8_BE, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_SBGGR10_2X8_PADLO_LE, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_SBGGR10_2X8_PADHI_BE, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_SBGGR10_2X8_PADLO_BE, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_SBGGR10_1X10, V4L2_COLORSPACE_SRGBपूर्ण,
पूर्ण;

काष्ठा rj54n1_घड़ी_भाग अणु
	u8 ratio_tg;	/* can be 0 or an odd number */
	u8 ratio_t;
	u8 ratio_r;
	u8 ratio_op;
	u8 ratio_o;
पूर्ण;

काष्ठा rj54n1 अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा clk *clk;
	काष्ठा gpio_desc *pwup_gpio;
	काष्ठा gpio_desc *enable_gpio;
	काष्ठा rj54n1_घड़ी_भाग clk_भाग;
	स्थिर काष्ठा rj54n1_datafmt *fmt;
	काष्ठा v4l2_rect rect;	/* Sensor winकरोw */
	अचिन्हित पूर्णांक tgclk_mhz;
	bool स्वतः_wb;
	अचिन्हित लघु width;	/* Output winकरोw */
	अचिन्हित लघु height;
	अचिन्हित लघु resize;	/* Sensor * 1024 / resize = Output */
	अचिन्हित लघु scale;
	u8 bank;
पूर्ण;

काष्ठा rj54n1_reg_val अणु
	u16 reg;
	u8 val;
पूर्ण;

अटल स्थिर काष्ठा rj54n1_reg_val bank_4[] = अणु
	अणु0x417, 0पूर्ण,
	अणु0x42c, 0पूर्ण,
	अणु0x42d, 0xf0पूर्ण,
	अणु0x42e, 0पूर्ण,
	अणु0x42f, 0x50पूर्ण,
	अणु0x430, 0xf5पूर्ण,
	अणु0x431, 0x16पूर्ण,
	अणु0x432, 0x20पूर्ण,
	अणु0x433, 0पूर्ण,
	अणु0x434, 0xc8पूर्ण,
	अणु0x43c, 8पूर्ण,
	अणु0x43e, 0x90पूर्ण,
	अणु0x445, 0x83पूर्ण,
	अणु0x4ba, 0x58पूर्ण,
	अणु0x4bb, 4पूर्ण,
	अणु0x4bc, 0x20पूर्ण,
	अणु0x4db, 4पूर्ण,
	अणु0x4fe, 2पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rj54n1_reg_val bank_5[] = अणु
	अणु0x514, 0पूर्ण,
	अणु0x516, 0पूर्ण,
	अणु0x518, 0पूर्ण,
	अणु0x51a, 0पूर्ण,
	अणु0x51d, 0xffपूर्ण,
	अणु0x56f, 0x28पूर्ण,
	अणु0x575, 0x40पूर्ण,
	अणु0x5bc, 0x48पूर्ण,
	अणु0x5c1, 6पूर्ण,
	अणु0x5e5, 0x11पूर्ण,
	अणु0x5e6, 0x43पूर्ण,
	अणु0x5e7, 0x33पूर्ण,
	अणु0x5e8, 0x21पूर्ण,
	अणु0x5e9, 0x30पूर्ण,
	अणु0x5ea, 0x0पूर्ण,
	अणु0x5eb, 0xa5पूर्ण,
	अणु0x5ec, 0xffपूर्ण,
	अणु0x5fe, 2पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rj54n1_reg_val bank_7[] = अणु
	अणु0x70a, 0पूर्ण,
	अणु0x714, 0xffपूर्ण,
	अणु0x715, 0xffपूर्ण,
	अणु0x716, 0x1fपूर्ण,
	अणु0x7FE, 2पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rj54n1_reg_val bank_8[] = अणु
	अणु0x800, 0x00पूर्ण,
	अणु0x801, 0x01पूर्ण,
	अणु0x802, 0x61पूर्ण,
	अणु0x805, 0x00पूर्ण,
	अणु0x806, 0x00पूर्ण,
	अणु0x807, 0x00पूर्ण,
	अणु0x808, 0x00पूर्ण,
	अणु0x809, 0x01पूर्ण,
	अणु0x80A, 0x61पूर्ण,
	अणु0x80B, 0x00पूर्ण,
	अणु0x80C, 0x01पूर्ण,
	अणु0x80D, 0x00पूर्ण,
	अणु0x80E, 0x00पूर्ण,
	अणु0x80F, 0x00पूर्ण,
	अणु0x810, 0x00पूर्ण,
	अणु0x811, 0x01पूर्ण,
	अणु0x812, 0x61पूर्ण,
	अणु0x813, 0x00पूर्ण,
	अणु0x814, 0x11पूर्ण,
	अणु0x815, 0x00पूर्ण,
	अणु0x816, 0x41पूर्ण,
	अणु0x817, 0x00पूर्ण,
	अणु0x818, 0x51पूर्ण,
	अणु0x819, 0x01पूर्ण,
	अणु0x81A, 0x1Fपूर्ण,
	अणु0x81B, 0x00पूर्ण,
	अणु0x81C, 0x01पूर्ण,
	अणु0x81D, 0x00पूर्ण,
	अणु0x81E, 0x11पूर्ण,
	अणु0x81F, 0x00पूर्ण,
	अणु0x820, 0x41पूर्ण,
	अणु0x821, 0x00पूर्ण,
	अणु0x822, 0x51पूर्ण,
	अणु0x823, 0x00पूर्ण,
	अणु0x824, 0x00पूर्ण,
	अणु0x825, 0x00पूर्ण,
	अणु0x826, 0x47पूर्ण,
	अणु0x827, 0x01पूर्ण,
	अणु0x828, 0x4Fपूर्ण,
	अणु0x829, 0x00पूर्ण,
	अणु0x82A, 0x00पूर्ण,
	अणु0x82B, 0x00पूर्ण,
	अणु0x82C, 0x30पूर्ण,
	अणु0x82D, 0x00पूर्ण,
	अणु0x82E, 0x40पूर्ण,
	अणु0x82F, 0x00पूर्ण,
	अणु0x830, 0xB3पूर्ण,
	अणु0x831, 0x00पूर्ण,
	अणु0x832, 0xE3पूर्ण,
	अणु0x833, 0x00पूर्ण,
	अणु0x834, 0x00पूर्ण,
	अणु0x835, 0x00पूर्ण,
	अणु0x836, 0x00पूर्ण,
	अणु0x837, 0x00पूर्ण,
	अणु0x838, 0x00पूर्ण,
	अणु0x839, 0x01पूर्ण,
	अणु0x83A, 0x61पूर्ण,
	अणु0x83B, 0x00पूर्ण,
	अणु0x83C, 0x01पूर्ण,
	अणु0x83D, 0x00पूर्ण,
	अणु0x83E, 0x00पूर्ण,
	अणु0x83F, 0x00पूर्ण,
	अणु0x840, 0x00पूर्ण,
	अणु0x841, 0x01पूर्ण,
	अणु0x842, 0x61पूर्ण,
	अणु0x843, 0x00पूर्ण,
	अणु0x844, 0x1Dपूर्ण,
	अणु0x845, 0x00पूर्ण,
	अणु0x846, 0x00पूर्ण,
	अणु0x847, 0x00पूर्ण,
	अणु0x848, 0x00पूर्ण,
	अणु0x849, 0x01पूर्ण,
	अणु0x84A, 0x1Fपूर्ण,
	अणु0x84B, 0x00पूर्ण,
	अणु0x84C, 0x05पूर्ण,
	अणु0x84D, 0x00पूर्ण,
	अणु0x84E, 0x19पूर्ण,
	अणु0x84F, 0x01पूर्ण,
	अणु0x850, 0x21पूर्ण,
	अणु0x851, 0x01पूर्ण,
	अणु0x852, 0x5Dपूर्ण,
	अणु0x853, 0x00पूर्ण,
	अणु0x854, 0x00पूर्ण,
	अणु0x855, 0x00पूर्ण,
	अणु0x856, 0x19पूर्ण,
	अणु0x857, 0x01पूर्ण,
	अणु0x858, 0x21पूर्ण,
	अणु0x859, 0x00पूर्ण,
	अणु0x85A, 0x00पूर्ण,
	अणु0x85B, 0x00पूर्ण,
	अणु0x85C, 0x00पूर्ण,
	अणु0x85D, 0x00पूर्ण,
	अणु0x85E, 0x00पूर्ण,
	अणु0x85F, 0x00पूर्ण,
	अणु0x860, 0xB3पूर्ण,
	अणु0x861, 0x00पूर्ण,
	अणु0x862, 0xE3पूर्ण,
	अणु0x863, 0x00पूर्ण,
	अणु0x864, 0x00पूर्ण,
	अणु0x865, 0x00पूर्ण,
	अणु0x866, 0x00पूर्ण,
	अणु0x867, 0x00पूर्ण,
	अणु0x868, 0x00पूर्ण,
	अणु0x869, 0xE2पूर्ण,
	अणु0x86A, 0x00पूर्ण,
	अणु0x86B, 0x01पूर्ण,
	अणु0x86C, 0x06पूर्ण,
	अणु0x86D, 0x00पूर्ण,
	अणु0x86E, 0x00पूर्ण,
	अणु0x86F, 0x00पूर्ण,
	अणु0x870, 0x60पूर्ण,
	अणु0x871, 0x8Cपूर्ण,
	अणु0x872, 0x10पूर्ण,
	अणु0x873, 0x00पूर्ण,
	अणु0x874, 0xE0पूर्ण,
	अणु0x875, 0x00पूर्ण,
	अणु0x876, 0x27पूर्ण,
	अणु0x877, 0x01पूर्ण,
	अणु0x878, 0x00पूर्ण,
	अणु0x879, 0x00पूर्ण,
	अणु0x87A, 0x00पूर्ण,
	अणु0x87B, 0x03पूर्ण,
	अणु0x87C, 0x00पूर्ण,
	अणु0x87D, 0x00पूर्ण,
	अणु0x87E, 0x00पूर्ण,
	अणु0x87F, 0x00पूर्ण,
	अणु0x880, 0x00पूर्ण,
	अणु0x881, 0x00पूर्ण,
	अणु0x882, 0x00पूर्ण,
	अणु0x883, 0x00पूर्ण,
	अणु0x884, 0x00पूर्ण,
	अणु0x885, 0x00पूर्ण,
	अणु0x886, 0xF8पूर्ण,
	अणु0x887, 0x00पूर्ण,
	अणु0x888, 0x03पूर्ण,
	अणु0x889, 0x00पूर्ण,
	अणु0x88A, 0x64पूर्ण,
	अणु0x88B, 0x00पूर्ण,
	अणु0x88C, 0x03पूर्ण,
	अणु0x88D, 0x00पूर्ण,
	अणु0x88E, 0xB1पूर्ण,
	अणु0x88F, 0x00पूर्ण,
	अणु0x890, 0x03पूर्ण,
	अणु0x891, 0x01पूर्ण,
	अणु0x892, 0x1Dपूर्ण,
	अणु0x893, 0x00पूर्ण,
	अणु0x894, 0x03पूर्ण,
	अणु0x895, 0x01पूर्ण,
	अणु0x896, 0x4Bपूर्ण,
	अणु0x897, 0x00पूर्ण,
	अणु0x898, 0xE5पूर्ण,
	अणु0x899, 0x00पूर्ण,
	अणु0x89A, 0x01पूर्ण,
	अणु0x89B, 0x00पूर्ण,
	अणु0x89C, 0x01पूर्ण,
	अणु0x89D, 0x04पूर्ण,
	अणु0x89E, 0xC8पूर्ण,
	अणु0x89F, 0x00पूर्ण,
	अणु0x8A0, 0x01पूर्ण,
	अणु0x8A1, 0x01पूर्ण,
	अणु0x8A2, 0x61पूर्ण,
	अणु0x8A3, 0x00पूर्ण,
	अणु0x8A4, 0x01पूर्ण,
	अणु0x8A5, 0x00पूर्ण,
	अणु0x8A6, 0x00पूर्ण,
	अणु0x8A7, 0x00पूर्ण,
	अणु0x8A8, 0x00पूर्ण,
	अणु0x8A9, 0x00पूर्ण,
	अणु0x8AA, 0x7Fपूर्ण,
	अणु0x8AB, 0x03पूर्ण,
	अणु0x8AC, 0x00पूर्ण,
	अणु0x8AD, 0x00पूर्ण,
	अणु0x8AE, 0x00पूर्ण,
	अणु0x8AF, 0x00पूर्ण,
	अणु0x8B0, 0x00पूर्ण,
	अणु0x8B1, 0x00पूर्ण,
	अणु0x8B6, 0x00पूर्ण,
	अणु0x8B7, 0x01पूर्ण,
	अणु0x8B8, 0x00पूर्ण,
	अणु0x8B9, 0x00पूर्ण,
	अणु0x8BA, 0x02पूर्ण,
	अणु0x8BB, 0x00पूर्ण,
	अणु0x8BC, 0xFFपूर्ण,
	अणु0x8BD, 0x00पूर्ण,
	अणु0x8FE, 2पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rj54n1_reg_val bank_10[] = अणु
	अणु0x10bf, 0x69पूर्ण
पूर्ण;

/* Clock भागiders - these are शेष रेजिस्टर values, भागider = रेजिस्टर + 1 */
अटल स्थिर काष्ठा rj54n1_घड़ी_भाग clk_भाग = अणु
	.ratio_tg	= 3 /* शेष: 5 */,
	.ratio_t	= 4 /* शेष: 1 */,
	.ratio_r	= 4 /* शेष: 0 */,
	.ratio_op	= 1 /* शेष: 5 */,
	.ratio_o	= 9 /* शेष: 0 */,
पूर्ण;

अटल काष्ठा rj54n1 *to_rj54n1(स्थिर काष्ठा i2c_client *client)
अणु
	वापस container_of(i2c_get_clientdata(client), काष्ठा rj54n1, subdev);
पूर्ण

अटल पूर्णांक reg_पढ़ो(काष्ठा i2c_client *client, स्थिर u16 reg)
अणु
	काष्ठा rj54n1 *rj54n1 = to_rj54n1(client);
	पूर्णांक ret;

	/* set bank */
	अगर (rj54n1->bank != reg >> 8) अणु
		dev_dbg(&client->dev, "[0x%x] = 0x%x\n", 0xff, reg >> 8);
		ret = i2c_smbus_ग_लिखो_byte_data(client, 0xff, reg >> 8);
		अगर (ret < 0)
			वापस ret;
		rj54n1->bank = reg >> 8;
	पूर्ण
	वापस i2c_smbus_पढ़ो_byte_data(client, reg & 0xff);
पूर्ण

अटल पूर्णांक reg_ग_लिखो(काष्ठा i2c_client *client, स्थिर u16 reg,
		     स्थिर u8 data)
अणु
	काष्ठा rj54n1 *rj54n1 = to_rj54n1(client);
	पूर्णांक ret;

	/* set bank */
	अगर (rj54n1->bank != reg >> 8) अणु
		dev_dbg(&client->dev, "[0x%x] = 0x%x\n", 0xff, reg >> 8);
		ret = i2c_smbus_ग_लिखो_byte_data(client, 0xff, reg >> 8);
		अगर (ret < 0)
			वापस ret;
		rj54n1->bank = reg >> 8;
	पूर्ण
	dev_dbg(&client->dev, "[0x%x] = 0x%x\n", reg & 0xff, data);
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg & 0xff, data);
पूर्ण

अटल पूर्णांक reg_set(काष्ठा i2c_client *client, स्थिर u16 reg,
		   स्थिर u8 data, स्थिर u8 mask)
अणु
	पूर्णांक ret;

	ret = reg_पढ़ो(client, reg);
	अगर (ret < 0)
		वापस ret;
	वापस reg_ग_लिखो(client, reg, (ret & ~mask) | (data & mask));
पूर्ण

अटल पूर्णांक reg_ग_लिखो_multiple(काष्ठा i2c_client *client,
			      स्थिर काष्ठा rj54n1_reg_val *rv, स्थिर पूर्णांक n)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < n; i++) अणु
		ret = reg_ग_लिखो(client, rv->reg, rv->val);
		अगर (ret < 0)
			वापस ret;
		rv++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rj54n1_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index >= ARRAY_SIZE(rj54n1_colour_fmts))
		वापस -EINVAL;

	code->code = rj54n1_colour_fmts[code->index].code;
	वापस 0;
पूर्ण

अटल पूर्णांक rj54n1_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	/* Switch between preview and still shot modes */
	वापस reg_set(client, RJ54N1_STILL_CONTROL, (!enable) << 7, 0x80);
पूर्ण

अटल पूर्णांक rj54n1_set_rect(काष्ठा i2c_client *client,
			   u16 reg_x, u16 reg_y, u16 reg_xy,
			   u32 width, u32 height)
अणु
	पूर्णांक ret;

	ret = reg_ग_लिखो(client, reg_xy,
			((width >> 4) & 0x70) |
			((height >> 8) & 7));

	अगर (!ret)
		ret = reg_ग_लिखो(client, reg_x, width & 0xff);
	अगर (!ret)
		ret = reg_ग_लिखो(client, reg_y, height & 0xff);

	वापस ret;
पूर्ण

/*
 * Some commands, specअगरically certain initialisation sequences, require
 * a commit operation.
 */
अटल पूर्णांक rj54n1_commit(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret = reg_ग_लिखो(client, RJ54N1_INIT_START, 1);
	msleep(10);
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_INIT_START, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक rj54n1_sensor_scale(काष्ठा v4l2_subdev *sd, s32 *in_w, s32 *in_h,
			       s32 *out_w, s32 *out_h);

अटल पूर्णांक rj54n1_set_selection(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा rj54n1 *rj54n1 = to_rj54n1(client);
	स्थिर काष्ठा v4l2_rect *rect = &sel->r;
	पूर्णांक output_w, output_h, input_w = rect->width, input_h = rect->height;
	पूर्णांक ret;

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE ||
	    sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	/* arbitrary minimum width and height, edges unimportant */
	v4l_bound_align_image(&input_w, 8, RJ54N1_MAX_WIDTH, 0,
			      &input_h, 8, RJ54N1_MAX_HEIGHT, 0, 0);

	output_w = (input_w * 1024 + rj54n1->resize / 2) / rj54n1->resize;
	output_h = (input_h * 1024 + rj54n1->resize / 2) / rj54n1->resize;

	dev_dbg(&client->dev, "Scaling for %dx%d : %u = %dx%d\n",
		input_w, input_h, rj54n1->resize, output_w, output_h);

	ret = rj54n1_sensor_scale(sd, &input_w, &input_h, &output_w, &output_h);
	अगर (ret < 0)
		वापस ret;

	rj54n1->width		= output_w;
	rj54n1->height		= output_h;
	rj54n1->resize		= ret;
	rj54n1->rect.width	= input_w;
	rj54n1->rect.height	= input_h;

	वापस 0;
पूर्ण

अटल पूर्णांक rj54n1_get_selection(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा rj54n1 *rj54n1 = to_rj54n1(client);

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = RJ54N1_COLUMN_SKIP;
		sel->r.top = RJ54N1_ROW_SKIP;
		sel->r.width = RJ54N1_MAX_WIDTH;
		sel->r.height = RJ54N1_MAX_HEIGHT;
		वापस 0;
	हाल V4L2_SEL_TGT_CROP:
		sel->r = rj54n1->rect;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक rj54n1_get_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा rj54n1 *rj54n1 = to_rj54n1(client);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	mf->code	= rj54n1->fmt->code;
	mf->colorspace	= rj54n1->fmt->colorspace;
	mf->ycbcr_enc	= V4L2_YCBCR_ENC_601;
	mf->xfer_func	= V4L2_XFER_FUNC_SRGB;
	mf->quantization = V4L2_QUANTIZATION_DEFAULT;
	mf->field	= V4L2_FIELD_NONE;
	mf->width	= rj54n1->width;
	mf->height	= rj54n1->height;

	वापस 0;
पूर्ण

/*
 * The actual geometry configuration routine. It scales the input winकरोw पूर्णांकo
 * the output one, updates the winकरोw sizes and वापसs an error or the resize
 * coefficient on success. Note: we only use the "Fixed Scaling" on this camera.
 */
अटल पूर्णांक rj54n1_sensor_scale(काष्ठा v4l2_subdev *sd, s32 *in_w, s32 *in_h,
			       s32 *out_w, s32 *out_h)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा rj54n1 *rj54n1 = to_rj54n1(client);
	अचिन्हित पूर्णांक skip, resize, input_w = *in_w, input_h = *in_h,
		output_w = *out_w, output_h = *out_h;
	u16 inc_sel, wb_bit8, wb_left, wb_right, wb_top, wb_bottom;
	अचिन्हित पूर्णांक peak, peak_50, peak_60;
	पूर्णांक ret;

	/*
	 * We have a problem with crops, where the winकरोw is larger than 512x384
	 * and output winकरोw is larger than a half of the input one. In this
	 * हाल we have to either reduce the input winकरोw to equal or below
	 * 512x384 or the output winकरोw to equal or below 1/2 of the input.
	 */
	अगर (output_w > max(512U, input_w / 2)) अणु
		अगर (2 * output_w > RJ54N1_MAX_WIDTH) अणु
			input_w = RJ54N1_MAX_WIDTH;
			output_w = RJ54N1_MAX_WIDTH / 2;
		पूर्ण अन्यथा अणु
			input_w = output_w * 2;
		पूर्ण

		dev_dbg(&client->dev, "Adjusted output width: in %u, out %u\n",
			input_w, output_w);
	पूर्ण

	अगर (output_h > max(384U, input_h / 2)) अणु
		अगर (2 * output_h > RJ54N1_MAX_HEIGHT) अणु
			input_h = RJ54N1_MAX_HEIGHT;
			output_h = RJ54N1_MAX_HEIGHT / 2;
		पूर्ण अन्यथा अणु
			input_h = output_h * 2;
		पूर्ण

		dev_dbg(&client->dev, "Adjusted output height: in %u, out %u\n",
			input_h, output_h);
	पूर्ण

	/* Idea: use the पढ़ो mode क्रम snapshots, handle separate geometries */
	ret = rj54n1_set_rect(client, RJ54N1_X_OUTPUT_SIZE_S_L,
			      RJ54N1_Y_OUTPUT_SIZE_S_L,
			      RJ54N1_XY_OUTPUT_SIZE_S_H, output_w, output_h);
	अगर (!ret)
		ret = rj54n1_set_rect(client, RJ54N1_X_OUTPUT_SIZE_P_L,
			      RJ54N1_Y_OUTPUT_SIZE_P_L,
			      RJ54N1_XY_OUTPUT_SIZE_P_H, output_w, output_h);

	अगर (ret < 0)
		वापस ret;

	अगर (output_w > input_w && output_h > input_h) अणु
		input_w = output_w;
		input_h = output_h;

		resize = 1024;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक resize_x, resize_y;
		resize_x = (input_w * 1024 + output_w / 2) / output_w;
		resize_y = (input_h * 1024 + output_h / 2) / output_h;

		/* We want max(resize_x, resize_y), check अगर it still fits */
		अगर (resize_x > resize_y &&
		    (output_h * resize_x + 512) / 1024 > RJ54N1_MAX_HEIGHT)
			resize = (RJ54N1_MAX_HEIGHT * 1024 + output_h / 2) /
				output_h;
		अन्यथा अगर (resize_y > resize_x &&
			 (output_w * resize_y + 512) / 1024 > RJ54N1_MAX_WIDTH)
			resize = (RJ54N1_MAX_WIDTH * 1024 + output_w / 2) /
				output_w;
		अन्यथा
			resize = max(resize_x, resize_y);

		/* Prohibited value ranges */
		चयन (resize) अणु
		हाल 2040 ... 2047:
			resize = 2039;
			अवरोध;
		हाल 4080 ... 4095:
			resize = 4079;
			अवरोध;
		हाल 8160 ... 8191:
			resize = 8159;
			अवरोध;
		हाल 16320 ... 16384:
			resize = 16319;
		पूर्ण
	पूर्ण

	/* Set scaling */
	ret = reg_ग_लिखो(client, RJ54N1_RESIZE_HOLD_L, resize & 0xff);
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_RESIZE_HOLD_H, resize >> 8);

	अगर (ret < 0)
		वापस ret;

	/*
	 * Configure a skipping biपंचांगask. The sensor will select a skipping value
	 * among set bits स्वतःmatically. This is very unclear in the datasheet
	 * too. I was told, in this रेजिस्टर one enables all skipping values,
	 * that are required क्रम a specअगरic resize, and the camera selects
	 * स्वतःmatically, which ones to use. But it is unclear how to identअगरy,
	 * which cropping values are needed. Secondly, why करोn't we just set all
	 * bits and let the camera choose? Would it increase processing समय and
	 * reduce the framerate? Using 0xfffc क्रम INC_USE_SEL करोesn't seem to
	 * improve the image quality or stability क्रम larger frames (see comment
	 * above), but I didn't check the framerate.
	 */
	skip = min(resize / 1024, 15U);

	inc_sel = 1 << skip;

	अगर (inc_sel <= 2)
		inc_sel = 0xc;
	अन्यथा अगर (resize & 1023 && skip < 15)
		inc_sel |= 1 << (skip + 1);

	ret = reg_ग_लिखो(client, RJ54N1_INC_USE_SEL_L, inc_sel & 0xfc);
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_INC_USE_SEL_H, inc_sel >> 8);

	अगर (!rj54n1->स्वतः_wb) अणु
		/* Auto white balance winकरोw */
		wb_left	  = output_w / 16;
		wb_right  = (3 * output_w / 4 - 3) / 4;
		wb_top	  = output_h / 16;
		wb_bottom = (3 * output_h / 4 - 3) / 4;
		wb_bit8	  = ((wb_left >> 2) & 0x40) | ((wb_top >> 4) & 0x10) |
			((wb_right >> 6) & 4) | ((wb_bottom >> 8) & 1);

		अगर (!ret)
			ret = reg_ग_लिखो(client, RJ54N1_BIT8_WB, wb_bit8);
		अगर (!ret)
			ret = reg_ग_लिखो(client, RJ54N1_HCAPS_WB, wb_left);
		अगर (!ret)
			ret = reg_ग_लिखो(client, RJ54N1_VCAPS_WB, wb_top);
		अगर (!ret)
			ret = reg_ग_लिखो(client, RJ54N1_HCAPE_WB, wb_right);
		अगर (!ret)
			ret = reg_ग_लिखो(client, RJ54N1_VCAPE_WB, wb_bottom);
	पूर्ण

	/* Antअगरlicker */
	peak = 12 * RJ54N1_MAX_WIDTH * (1 << 14) * resize / rj54n1->tgclk_mhz /
		10000;
	peak_50 = peak / 6;
	peak_60 = peak / 5;

	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_PEAK_H,
				((peak_50 >> 4) & 0xf0) | (peak_60 >> 8));
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_PEAK_50, peak_50);
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_PEAK_60, peak_60);
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_PEAK_DIFF, peak / 150);

	/* Start resizing */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_RESIZE_CONTROL,
				RESIZE_HOLD_SEL | RESIZE_GO | 1);

	अगर (ret < 0)
		वापस ret;

	/* Constant taken from manufacturer's example */
	msleep(230);

	ret = reg_ग_लिखो(client, RJ54N1_RESIZE_CONTROL, RESIZE_HOLD_SEL | 1);
	अगर (ret < 0)
		वापस ret;

	*in_w = (output_w * resize + 512) / 1024;
	*in_h = (output_h * resize + 512) / 1024;
	*out_w = output_w;
	*out_h = output_h;

	dev_dbg(&client->dev, "Scaled for %dx%d : %u = %ux%u, skip %u\n",
		*in_w, *in_h, resize, output_w, output_h, skip);

	वापस resize;
पूर्ण

अटल पूर्णांक rj54n1_set_घड़ी(काष्ठा i2c_client *client)
अणु
	काष्ठा rj54n1 *rj54n1 = to_rj54n1(client);
	पूर्णांक ret;

	/* Enable बाह्यal घड़ी */
	ret = reg_ग_लिखो(client, RJ54N1_RESET_STANDBY, E_EXCLK | SOFT_STDBY);
	/* Leave stand-by. Note: use this when implementing suspend / resume */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_RESET_STANDBY, E_EXCLK);

	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_PLL_L, PLL_L);
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_PLL_N, PLL_N);

	/* TGCLK भागiders */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_RATIO_TG,
				rj54n1->clk_भाग.ratio_tg);
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_RATIO_T,
				rj54n1->clk_भाग.ratio_t);
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_RATIO_R,
				rj54n1->clk_भाग.ratio_r);

	/* Enable TGCLK & RAMP */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_RAMP_TGCLK_EN, 3);

	/* Disable घड़ी output */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_OCLK_DSP, 0);

	/* Set भागisors */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_RATIO_OP,
				rj54n1->clk_भाग.ratio_op);
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_RATIO_O,
				rj54n1->clk_भाग.ratio_o);

	/* Enable OCLK */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_OCLK_SEL_EN, 1);

	/* Use PLL क्रम Timing Generator, ग_लिखो 2 to reserved bits */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_TG_BYPASS, 2);

	/* Take sensor out of reset */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_RESET_STANDBY,
				E_EXCLK | SEN_RSTX);
	/* Enable PLL */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_PLL_EN, 1);

	/* Wait क्रम PLL to stabilise */
	msleep(10);

	/* Enable घड़ी to frequency भागider */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_CLK_RST, 1);

	अगर (!ret)
		ret = reg_पढ़ो(client, RJ54N1_CLK_RST);
	अगर (ret != 1) अणु
		dev_err(&client->dev,
			"Resetting RJ54N1CB0C clock failed: %d!\n", ret);
		वापस -EIO;
	पूर्ण

	/* Start the PLL */
	ret = reg_set(client, RJ54N1_OCLK_DSP, 1, 1);

	/* Enable OCLK */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_OCLK_SEL_EN, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक rj54n1_reg_init(काष्ठा i2c_client *client)
अणु
	काष्ठा rj54n1 *rj54n1 = to_rj54n1(client);
	पूर्णांक ret = rj54n1_set_घड़ी(client);

	अगर (!ret)
		ret = reg_ग_लिखो_multiple(client, bank_7, ARRAY_SIZE(bank_7));
	अगर (!ret)
		ret = reg_ग_लिखो_multiple(client, bank_10, ARRAY_SIZE(bank_10));

	/* Set binning भागisors */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_SCALE_1_2_LEV, 3 | (7 << 4));
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_SCALE_4_LEV, 0xf);

	/* Switch to fixed resize mode */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_RESIZE_CONTROL,
				RESIZE_HOLD_SEL | 1);

	/* Set gain */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_Y_GAIN, 0x84);

	/*
	 * Mirror the image back: शेष is upside करोwn and left-to-right...
	 * Set manual preview / still shot चयनing
	 */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_MIRROR_STILL_MODE, 0x27);

	अगर (!ret)
		ret = reg_ग_लिखो_multiple(client, bank_4, ARRAY_SIZE(bank_4));

	/* Auto exposure area */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_EXPOSURE_CONTROL, 0x80);
	/* Check current स्वतः WB config */
	अगर (!ret)
		ret = reg_पढ़ो(client, RJ54N1_WB_SEL_WEIGHT_I);
	अगर (ret >= 0) अणु
		rj54n1->स्वतः_wb = ret & 0x80;
		ret = reg_ग_लिखो_multiple(client, bank_5, ARRAY_SIZE(bank_5));
	पूर्ण
	अगर (!ret)
		ret = reg_ग_लिखो_multiple(client, bank_8, ARRAY_SIZE(bank_8));

	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_RESET_STANDBY,
				E_EXCLK | DSP_RSTX | SEN_RSTX);

	/* Commit init */
	अगर (!ret)
		ret = rj54n1_commit(client);

	/* Take DSP, TG, sensor out of reset */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_RESET_STANDBY,
				E_EXCLK | DSP_RSTX | TG_RSTX | SEN_RSTX);

	/* Start रेजिस्टर update? Same रेजिस्टर as 0x?FE in many bank_* sets */
	अगर (!ret)
		ret = reg_ग_लिखो(client, RJ54N1_FWFLG, 2);

	/* Constant taken from manufacturer's example */
	msleep(700);

	वापस ret;
पूर्ण

अटल पूर्णांक rj54n1_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा rj54n1 *rj54n1 = to_rj54n1(client);
	स्थिर काष्ठा rj54n1_datafmt *fmt;
	पूर्णांक output_w, output_h, max_w, max_h,
		input_w = rj54n1->rect.width, input_h = rj54n1->rect.height;
	पूर्णांक align = mf->code == MEDIA_BUS_FMT_SBGGR10_1X10 ||
		mf->code == MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_BE ||
		mf->code == MEDIA_BUS_FMT_SBGGR10_2X8_PADLO_BE ||
		mf->code == MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE ||
		mf->code == MEDIA_BUS_FMT_SBGGR10_2X8_PADLO_LE;
	पूर्णांक ret;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	dev_dbg(&client->dev, "%s: code = %d, width = %u, height = %u\n",
		__func__, mf->code, mf->width, mf->height);

	fmt = rj54n1_find_datafmt(mf->code, rj54n1_colour_fmts,
				  ARRAY_SIZE(rj54n1_colour_fmts));
	अगर (!fmt) अणु
		fmt = rj54n1->fmt;
		mf->code = fmt->code;
	पूर्ण

	mf->field	= V4L2_FIELD_NONE;
	mf->colorspace	= fmt->colorspace;

	v4l_bound_align_image(&mf->width, 112, RJ54N1_MAX_WIDTH, align,
			      &mf->height, 84, RJ54N1_MAX_HEIGHT, align, 0);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		cfg->try_fmt = *mf;
		वापस 0;
	पूर्ण

	/*
	 * Verअगरy अगर the sensor has just been घातered on. TODO: replace this
	 * with proper PM, when a suitable API is available.
	 */
	ret = reg_पढ़ो(client, RJ54N1_RESET_STANDBY);
	अगर (ret < 0)
		वापस ret;

	अगर (!(ret & E_EXCLK)) अणु
		ret = rj54n1_reg_init(client);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* RA_SEL_UL is only relevant क्रम raw modes, ignored otherwise. */
	चयन (mf->code) अणु
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
		ret = reg_ग_लिखो(client, RJ54N1_OUT_SEL, 0);
		अगर (!ret)
			ret = reg_set(client, RJ54N1_BYTE_SWAP, 8, 8);
		अवरोध;
	हाल MEDIA_BUS_FMT_YVYU8_2X8:
		ret = reg_ग_लिखो(client, RJ54N1_OUT_SEL, 0);
		अगर (!ret)
			ret = reg_set(client, RJ54N1_BYTE_SWAP, 0, 8);
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB565_2X8_LE:
		ret = reg_ग_लिखो(client, RJ54N1_OUT_SEL, 0x11);
		अगर (!ret)
			ret = reg_set(client, RJ54N1_BYTE_SWAP, 8, 8);
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB565_2X8_BE:
		ret = reg_ग_लिखो(client, RJ54N1_OUT_SEL, 0x11);
		अगर (!ret)
			ret = reg_set(client, RJ54N1_BYTE_SWAP, 0, 8);
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_2X8_PADLO_LE:
		ret = reg_ग_लिखो(client, RJ54N1_OUT_SEL, 4);
		अगर (!ret)
			ret = reg_set(client, RJ54N1_BYTE_SWAP, 8, 8);
		अगर (!ret)
			ret = reg_ग_लिखो(client, RJ54N1_RA_SEL_UL, 0);
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE:
		ret = reg_ग_लिखो(client, RJ54N1_OUT_SEL, 4);
		अगर (!ret)
			ret = reg_set(client, RJ54N1_BYTE_SWAP, 8, 8);
		अगर (!ret)
			ret = reg_ग_लिखो(client, RJ54N1_RA_SEL_UL, 8);
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_2X8_PADLO_BE:
		ret = reg_ग_लिखो(client, RJ54N1_OUT_SEL, 4);
		अगर (!ret)
			ret = reg_set(client, RJ54N1_BYTE_SWAP, 0, 8);
		अगर (!ret)
			ret = reg_ग_लिखो(client, RJ54N1_RA_SEL_UL, 0);
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_BE:
		ret = reg_ग_लिखो(client, RJ54N1_OUT_SEL, 4);
		अगर (!ret)
			ret = reg_set(client, RJ54N1_BYTE_SWAP, 0, 8);
		अगर (!ret)
			ret = reg_ग_लिखो(client, RJ54N1_RA_SEL_UL, 8);
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
		ret = reg_ग_लिखो(client, RJ54N1_OUT_SEL, 5);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	/* Special हाल: a raw mode with 10 bits of data per घड़ी tick */
	अगर (!ret)
		ret = reg_set(client, RJ54N1_OCLK_SEL_EN,
			      (mf->code == MEDIA_BUS_FMT_SBGGR10_1X10) << 1, 2);

	अगर (ret < 0)
		वापस ret;

	/* Supported scales 1:1 >= scale > 1:16 */
	max_w = mf->width * (16 * 1024 - 1) / 1024;
	अगर (input_w > max_w)
		input_w = max_w;
	max_h = mf->height * (16 * 1024 - 1) / 1024;
	अगर (input_h > max_h)
		input_h = max_h;

	output_w = mf->width;
	output_h = mf->height;

	ret = rj54n1_sensor_scale(sd, &input_w, &input_h, &output_w, &output_h);
	अगर (ret < 0)
		वापस ret;

	fmt = rj54n1_find_datafmt(mf->code, rj54n1_colour_fmts,
				  ARRAY_SIZE(rj54n1_colour_fmts));

	rj54n1->fmt		= fmt;
	rj54n1->resize		= ret;
	rj54n1->rect.width	= input_w;
	rj54n1->rect.height	= input_h;
	rj54n1->width		= output_w;
	rj54n1->height		= output_h;

	mf->width		= output_w;
	mf->height		= output_h;
	mf->field		= V4L2_FIELD_NONE;
	mf->colorspace		= fmt->colorspace;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक rj54n1_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (reg->reg < 0x400 || reg->reg > 0x1fff)
		/* Registers > 0x0800 are only available from Sharp support */
		वापस -EINVAL;

	reg->size = 1;
	reg->val = reg_पढ़ो(client, reg->reg);

	अगर (reg->val > 0xff)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक rj54n1_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			     स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (reg->reg < 0x400 || reg->reg > 0x1fff)
		/* Registers >= 0x0800 are only available from Sharp support */
		वापस -EINVAL;

	अगर (reg_ग_लिखो(client, reg->reg, reg->val) < 0)
		वापस -EIO;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rj54n1_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा rj54n1 *rj54n1 = to_rj54n1(client);

	अगर (on) अणु
		अगर (rj54n1->pwup_gpio)
			gpiod_set_value(rj54n1->pwup_gpio, 1);
		अगर (rj54n1->enable_gpio)
			gpiod_set_value(rj54n1->enable_gpio, 1);

		msleep(1);

		वापस clk_prepare_enable(rj54n1->clk);
	पूर्ण

	clk_disable_unprepare(rj54n1->clk);

	अगर (rj54n1->enable_gpio)
		gpiod_set_value(rj54n1->enable_gpio, 0);
	अगर (rj54n1->pwup_gpio)
		gpiod_set_value(rj54n1->pwup_gpio, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक rj54n1_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा rj54n1 *rj54n1 = container_of(ctrl->handler, काष्ठा rj54n1, hdl);
	काष्ठा v4l2_subdev *sd = &rj54n1->subdev;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक data;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VFLIP:
		अगर (ctrl->val)
			data = reg_set(client, RJ54N1_MIRROR_STILL_MODE, 0, 1);
		अन्यथा
			data = reg_set(client, RJ54N1_MIRROR_STILL_MODE, 1, 1);
		अगर (data < 0)
			वापस -EIO;
		वापस 0;
	हाल V4L2_CID_HFLIP:
		अगर (ctrl->val)
			data = reg_set(client, RJ54N1_MIRROR_STILL_MODE, 0, 2);
		अन्यथा
			data = reg_set(client, RJ54N1_MIRROR_STILL_MODE, 2, 2);
		अगर (data < 0)
			वापस -EIO;
		वापस 0;
	हाल V4L2_CID_GAIN:
		अगर (reg_ग_लिखो(client, RJ54N1_Y_GAIN, ctrl->val * 2) < 0)
			वापस -EIO;
		वापस 0;
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		/* Auto WB area - whole image */
		अगर (reg_set(client, RJ54N1_WB_SEL_WEIGHT_I, ctrl->val << 7,
			    0x80) < 0)
			वापस -EIO;
		rj54n1->स्वतः_wb = ctrl->val;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops rj54n1_ctrl_ops = अणु
	.s_ctrl = rj54n1_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops rj54n1_subdev_core_ops = अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर	= rj54n1_g_रेजिस्टर,
	.s_रेजिस्टर	= rj54n1_s_रेजिस्टर,
#पूर्ण_अगर
	.s_घातer	= rj54n1_s_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops rj54n1_subdev_video_ops = अणु
	.s_stream	= rj54n1_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops rj54n1_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = rj54n1_क्रमागत_mbus_code,
	.get_selection	= rj54n1_get_selection,
	.set_selection	= rj54n1_set_selection,
	.get_fmt	= rj54n1_get_fmt,
	.set_fmt	= rj54n1_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops rj54n1_subdev_ops = अणु
	.core	= &rj54n1_subdev_core_ops,
	.video	= &rj54n1_subdev_video_ops,
	.pad	= &rj54n1_subdev_pad_ops,
पूर्ण;

/*
 * Interface active, can use i2c. If it fails, it can indeed mean, that
 * this wasn't our capture पूर्णांकerface, so, we रुको क्रम the right one
 */
अटल पूर्णांक rj54n1_video_probe(काष्ठा i2c_client *client,
			      काष्ठा rj54n1_pdata *priv)
अणु
	काष्ठा rj54n1 *rj54n1 = to_rj54n1(client);
	पूर्णांक data1, data2;
	पूर्णांक ret;

	ret = rj54n1_s_घातer(&rj54n1->subdev, 1);
	अगर (ret < 0)
		वापस ret;

	/* Read out the chip version रेजिस्टर */
	data1 = reg_पढ़ो(client, RJ54N1_DEV_CODE);
	data2 = reg_पढ़ो(client, RJ54N1_DEV_CODE2);

	अगर (data1 != 0x51 || data2 != 0x10) अणु
		ret = -ENODEV;
		dev_info(&client->dev, "No RJ54N1CB0C found, read 0x%x:0x%x\n",
			 data1, data2);
		जाओ करोne;
	पूर्ण

	/* Configure IOCTL polarity from the platक्रमm data: 0 or 1 << 7. */
	ret = reg_ग_लिखो(client, RJ54N1_IOC, priv->ioctl_high << 7);
	अगर (ret < 0)
		जाओ करोne;

	dev_info(&client->dev, "Detected a RJ54N1CB0C chip ID 0x%x:0x%x\n",
		 data1, data2);

	ret = v4l2_ctrl_handler_setup(&rj54n1->hdl);

करोne:
	rj54n1_s_घातer(&rj54n1->subdev, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक rj54n1_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *did)
अणु
	काष्ठा rj54n1 *rj54n1;
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा rj54n1_pdata *rj54n1_priv;
	पूर्णांक ret;

	अगर (!client->dev.platक्रमm_data) अणु
		dev_err(&client->dev, "RJ54N1CB0C: missing platform data!\n");
		वापस -EINVAL;
	पूर्ण

	rj54n1_priv = client->dev.platक्रमm_data;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_warn(&adapter->dev,
			 "I2C-Adapter doesn't support I2C_FUNC_SMBUS_BYTE\n");
		वापस -EIO;
	पूर्ण

	rj54n1 = devm_kzalloc(&client->dev, माप(काष्ठा rj54n1), GFP_KERNEL);
	अगर (!rj54n1)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(&rj54n1->subdev, client, &rj54n1_subdev_ops);
	v4l2_ctrl_handler_init(&rj54n1->hdl, 4);
	v4l2_ctrl_new_std(&rj54n1->hdl, &rj54n1_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&rj54n1->hdl, &rj54n1_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&rj54n1->hdl, &rj54n1_ctrl_ops,
			V4L2_CID_GAIN, 0, 127, 1, 66);
	v4l2_ctrl_new_std(&rj54n1->hdl, &rj54n1_ctrl_ops,
			V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);
	rj54n1->subdev.ctrl_handler = &rj54n1->hdl;
	अगर (rj54n1->hdl.error)
		वापस rj54n1->hdl.error;

	rj54n1->clk_भाग		= clk_भाग;
	rj54n1->rect.left	= RJ54N1_COLUMN_SKIP;
	rj54n1->rect.top	= RJ54N1_ROW_SKIP;
	rj54n1->rect.width	= RJ54N1_MAX_WIDTH;
	rj54n1->rect.height	= RJ54N1_MAX_HEIGHT;
	rj54n1->width		= RJ54N1_MAX_WIDTH;
	rj54n1->height		= RJ54N1_MAX_HEIGHT;
	rj54n1->fmt		= &rj54n1_colour_fmts[0];
	rj54n1->resize		= 1024;
	rj54n1->tgclk_mhz	= (rj54n1_priv->mclk_freq / PLL_L * PLL_N) /
		(clk_भाग.ratio_tg + 1) / (clk_भाग.ratio_t + 1);

	rj54n1->clk = clk_get(&client->dev, शून्य);
	अगर (IS_ERR(rj54n1->clk)) अणु
		ret = PTR_ERR(rj54n1->clk);
		जाओ err_मुक्त_ctrl;
	पूर्ण

	rj54n1->pwup_gpio = gpiod_get_optional(&client->dev, "powerup",
					       GPIOD_OUT_LOW);
	अगर (IS_ERR(rj54n1->pwup_gpio)) अणु
		dev_info(&client->dev, "Unable to get GPIO \"powerup\": %ld\n",
			 PTR_ERR(rj54n1->pwup_gpio));
		ret = PTR_ERR(rj54n1->pwup_gpio);
		जाओ err_clk_put;
	पूर्ण

	rj54n1->enable_gpio = gpiod_get_optional(&client->dev, "enable",
						 GPIOD_OUT_LOW);
	अगर (IS_ERR(rj54n1->enable_gpio)) अणु
		dev_info(&client->dev, "Unable to get GPIO \"enable\": %ld\n",
			 PTR_ERR(rj54n1->enable_gpio));
		ret = PTR_ERR(rj54n1->enable_gpio);
		जाओ err_gpio_put;
	पूर्ण

	ret = rj54n1_video_probe(client, rj54n1_priv);
	अगर (ret < 0)
		जाओ err_gpio_put;

	ret = v4l2_async_रेजिस्टर_subdev(&rj54n1->subdev);
	अगर (ret)
		जाओ err_gpio_put;

	वापस 0;

err_gpio_put:
	अगर (rj54n1->enable_gpio)
		gpiod_put(rj54n1->enable_gpio);

	अगर (rj54n1->pwup_gpio)
		gpiod_put(rj54n1->pwup_gpio);

err_clk_put:
	clk_put(rj54n1->clk);

err_मुक्त_ctrl:
	v4l2_ctrl_handler_मुक्त(&rj54n1->hdl);

	वापस ret;
पूर्ण

अटल पूर्णांक rj54n1_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा rj54n1 *rj54n1 = to_rj54n1(client);

	अगर (rj54n1->enable_gpio)
		gpiod_put(rj54n1->enable_gpio);
	अगर (rj54n1->pwup_gpio)
		gpiod_put(rj54n1->pwup_gpio);

	clk_put(rj54n1->clk);
	v4l2_ctrl_handler_मुक्त(&rj54n1->hdl);
	v4l2_async_unरेजिस्टर_subdev(&rj54n1->subdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id rj54n1_id[] = अणु
	अणु "rj54n1cb0c", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rj54n1_id);

अटल काष्ठा i2c_driver rj54n1_i2c_driver = अणु
	.driver = अणु
		.name = "rj54n1cb0c",
	पूर्ण,
	.probe		= rj54n1_probe,
	.हटाओ		= rj54n1_हटाओ,
	.id_table	= rj54n1_id,
पूर्ण;

module_i2c_driver(rj54n1_i2c_driver);

MODULE_DESCRIPTION("Sharp RJ54N1CB0C Camera driver");
MODULE_AUTHOR("Guennadi Liakhovetski <g.liakhovetski@gmx.de>");
MODULE_LICENSE("GPL v2");
