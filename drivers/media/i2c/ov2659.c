<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Omnivision OV2659 CMOS Image Sensor driver
 *
 * Copyright (C) 2015 Texas Instruments, Inc.
 *
 * Benoit Parrot <bparrot@ti.com>
 * Lad, Prabhakar <prabhakar.csengg@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <media/i2c/ov2659.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा DRIVER_NAME "ov2659"

/*
 * OV2659 रेजिस्टर definitions
 */
#घोषणा REG_SOFTWARE_STANDBY		0x0100
#घोषणा REG_SOFTWARE_RESET		0x0103
#घोषणा REG_IO_CTRL00			0x3000
#घोषणा REG_IO_CTRL01			0x3001
#घोषणा REG_IO_CTRL02			0x3002
#घोषणा REG_OUTPUT_VALUE00		0x3008
#घोषणा REG_OUTPUT_VALUE01		0x3009
#घोषणा REG_OUTPUT_VALUE02		0x300d
#घोषणा REG_OUTPUT_SELECT00		0x300e
#घोषणा REG_OUTPUT_SELECT01		0x300f
#घोषणा REG_OUTPUT_SELECT02		0x3010
#घोषणा REG_OUTPUT_DRIVE		0x3011
#घोषणा REG_INPUT_READOUT00		0x302d
#घोषणा REG_INPUT_READOUT01		0x302e
#घोषणा REG_INPUT_READOUT02		0x302f

#घोषणा REG_SC_PLL_CTRL0		0x3003
#घोषणा REG_SC_PLL_CTRL1		0x3004
#घोषणा REG_SC_PLL_CTRL2		0x3005
#घोषणा REG_SC_PLL_CTRL3		0x3006
#घोषणा REG_SC_CHIP_ID_H		0x300a
#घोषणा REG_SC_CHIP_ID_L		0x300b
#घोषणा REG_SC_PWC			0x3014
#घोषणा REG_SC_CLKRST0			0x301a
#घोषणा REG_SC_CLKRST1			0x301b
#घोषणा REG_SC_CLKRST2			0x301c
#घोषणा REG_SC_CLKRST3			0x301d
#घोषणा REG_SC_SUB_ID			0x302a
#घोषणा REG_SC_SCCB_ID			0x302b

#घोषणा REG_GROUP_ADDRESS_00		0x3200
#घोषणा REG_GROUP_ADDRESS_01		0x3201
#घोषणा REG_GROUP_ADDRESS_02		0x3202
#घोषणा REG_GROUP_ADDRESS_03		0x3203
#घोषणा REG_GROUP_ACCESS		0x3208

#घोषणा REG_AWB_R_GAIN_H		0x3400
#घोषणा REG_AWB_R_GAIN_L		0x3401
#घोषणा REG_AWB_G_GAIN_H		0x3402
#घोषणा REG_AWB_G_GAIN_L		0x3403
#घोषणा REG_AWB_B_GAIN_H		0x3404
#घोषणा REG_AWB_B_GAIN_L		0x3405
#घोषणा REG_AWB_MANUAL_CONTROL		0x3406

#घोषणा REG_TIMING_HS_H			0x3800
#घोषणा REG_TIMING_HS_L			0x3801
#घोषणा REG_TIMING_VS_H			0x3802
#घोषणा REG_TIMING_VS_L			0x3803
#घोषणा REG_TIMING_HW_H			0x3804
#घोषणा REG_TIMING_HW_L			0x3805
#घोषणा REG_TIMING_VH_H			0x3806
#घोषणा REG_TIMING_VH_L			0x3807
#घोषणा REG_TIMING_DVPHO_H		0x3808
#घोषणा REG_TIMING_DVPHO_L		0x3809
#घोषणा REG_TIMING_DVPVO_H		0x380a
#घोषणा REG_TIMING_DVPVO_L		0x380b
#घोषणा REG_TIMING_HTS_H		0x380c
#घोषणा REG_TIMING_HTS_L		0x380d
#घोषणा REG_TIMING_VTS_H		0x380e
#घोषणा REG_TIMING_VTS_L		0x380f
#घोषणा REG_TIMING_HOFFS_H		0x3810
#घोषणा REG_TIMING_HOFFS_L		0x3811
#घोषणा REG_TIMING_VOFFS_H		0x3812
#घोषणा REG_TIMING_VOFFS_L		0x3813
#घोषणा REG_TIMING_XINC			0x3814
#घोषणा REG_TIMING_YINC			0x3815
#घोषणा REG_TIMING_VERT_FORMAT		0x3820
#घोषणा REG_TIMING_HORIZ_FORMAT		0x3821

#घोषणा REG_FORMAT_CTRL00		0x4300

#घोषणा REG_VFIFO_READ_START_H		0x4608
#घोषणा REG_VFIFO_READ_START_L		0x4609

#घोषणा REG_DVP_CTRL02			0x4708

#घोषणा REG_ISP_CTRL00			0x5000
#घोषणा REG_ISP_CTRL01			0x5001
#घोषणा REG_ISP_CTRL02			0x5002

#घोषणा REG_LENC_RED_X0_H		0x500c
#घोषणा REG_LENC_RED_X0_L		0x500d
#घोषणा REG_LENC_RED_Y0_H		0x500e
#घोषणा REG_LENC_RED_Y0_L		0x500f
#घोषणा REG_LENC_RED_A1			0x5010
#घोषणा REG_LENC_RED_B1			0x5011
#घोषणा REG_LENC_RED_A2_B2		0x5012
#घोषणा REG_LENC_GREEN_X0_H		0x5013
#घोषणा REG_LENC_GREEN_X0_L		0x5014
#घोषणा REG_LENC_GREEN_Y0_H		0x5015
#घोषणा REG_LENC_GREEN_Y0_L		0x5016
#घोषणा REG_LENC_GREEN_A1		0x5017
#घोषणा REG_LENC_GREEN_B1		0x5018
#घोषणा REG_LENC_GREEN_A2_B2		0x5019
#घोषणा REG_LENC_BLUE_X0_H		0x501a
#घोषणा REG_LENC_BLUE_X0_L		0x501b
#घोषणा REG_LENC_BLUE_Y0_H		0x501c
#घोषणा REG_LENC_BLUE_Y0_L		0x501d
#घोषणा REG_LENC_BLUE_A1		0x501e
#घोषणा REG_LENC_BLUE_B1		0x501f
#घोषणा REG_LENC_BLUE_A2_B2		0x5020

#घोषणा REG_AWB_CTRL00			0x5035
#घोषणा REG_AWB_CTRL01			0x5036
#घोषणा REG_AWB_CTRL02			0x5037
#घोषणा REG_AWB_CTRL03			0x5038
#घोषणा REG_AWB_CTRL04			0x5039
#घोषणा REG_AWB_LOCAL_LIMIT		0x503a
#घोषणा REG_AWB_CTRL12			0x5049
#घोषणा REG_AWB_CTRL13			0x504a
#घोषणा REG_AWB_CTRL14			0x504b

#घोषणा REG_SHARPENMT_THRESH1		0x5064
#घोषणा REG_SHARPENMT_THRESH2		0x5065
#घोषणा REG_SHARPENMT_OFFSET1		0x5066
#घोषणा REG_SHARPENMT_OFFSET2		0x5067
#घोषणा REG_DENOISE_THRESH1		0x5068
#घोषणा REG_DENOISE_THRESH2		0x5069
#घोषणा REG_DENOISE_OFFSET1		0x506a
#घोषणा REG_DENOISE_OFFSET2		0x506b
#घोषणा REG_SHARPEN_THRESH1		0x506c
#घोषणा REG_SHARPEN_THRESH2		0x506d
#घोषणा REG_CIP_CTRL00			0x506e
#घोषणा REG_CIP_CTRL01			0x506f

#घोषणा REG_CMX_SIGN			0x5079
#घोषणा REG_CMX_MISC_CTRL		0x507a

#घोषणा REG_PRE_ISP_CTRL00		0x50a0
#घोषणा TEST_PATTERN_ENABLE		BIT(7)
#घोषणा VERTICAL_COLOR_BAR_MASK		0x53

#घोषणा REG_शून्य			0x0000	/* Array end token */

#घोषणा OV265X_ID(_msb, _lsb)		((_msb) << 8 | (_lsb))
#घोषणा OV2659_ID			0x2656

काष्ठा sensor_रेजिस्टर अणु
	u16 addr;
	u8 value;
पूर्ण;

काष्ठा ov2659_framesize अणु
	u16 width;
	u16 height;
	u16 max_exp_lines;
	स्थिर काष्ठा sensor_रेजिस्टर *regs;
पूर्ण;

काष्ठा ov2659_pll_ctrl अणु
	u8 ctrl1;
	u8 ctrl2;
	u8 ctrl3;
पूर्ण;

काष्ठा ov2659_pixfmt अणु
	u32 code;
	/* Output क्रमmat Register Value (REG_FORMAT_CTRL00) */
	काष्ठा sensor_रेजिस्टर *क्रमmat_ctrl_regs;
पूर्ण;

काष्ठा pll_ctrl_reg अणु
	अचिन्हित पूर्णांक भाग;
	अचिन्हित अक्षर reg;
पूर्ण;

काष्ठा ov2659 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	अचिन्हित पूर्णांक xvclk_frequency;
	स्थिर काष्ठा ov2659_platक्रमm_data *pdata;
	काष्ठा mutex lock;
	काष्ठा i2c_client *client;
	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा v4l2_ctrl *link_frequency;
	स्थिर काष्ठा ov2659_framesize *frame_size;
	काष्ठा sensor_रेजिस्टर *क्रमmat_ctrl_regs;
	काष्ठा ov2659_pll_ctrl pll;
	पूर्णांक streaming;
	/* used to control the sensor PWDN pin */
	काष्ठा gpio_desc *pwdn_gpio;
	/* used to control the sensor RESETB pin */
	काष्ठा gpio_desc *resetb_gpio;
पूर्ण;

अटल स्थिर काष्ठा sensor_रेजिस्टर ov2659_init_regs[] = अणु
	अणु REG_IO_CTRL00, 0x03 पूर्ण,
	अणु REG_IO_CTRL01, 0xff पूर्ण,
	अणु REG_IO_CTRL02, 0xe0 पूर्ण,
	अणु 0x3633, 0x3d पूर्ण,
	अणु 0x3620, 0x02 पूर्ण,
	अणु 0x3631, 0x11 पूर्ण,
	अणु 0x3612, 0x04 पूर्ण,
	अणु 0x3630, 0x20 पूर्ण,
	अणु 0x4702, 0x02 पूर्ण,
	अणु 0x370c, 0x34 पूर्ण,
	अणु REG_TIMING_HS_H, 0x00 पूर्ण,
	अणु REG_TIMING_HS_L, 0x00 पूर्ण,
	अणु REG_TIMING_VS_H, 0x00 पूर्ण,
	अणु REG_TIMING_VS_L, 0x00 पूर्ण,
	अणु REG_TIMING_HW_H, 0x06 पूर्ण,
	अणु REG_TIMING_HW_L, 0x5f पूर्ण,
	अणु REG_TIMING_VH_H, 0x04 पूर्ण,
	अणु REG_TIMING_VH_L, 0xb7 पूर्ण,
	अणु REG_TIMING_DVPHO_H, 0x03 पूर्ण,
	अणु REG_TIMING_DVPHO_L, 0x20 पूर्ण,
	अणु REG_TIMING_DVPVO_H, 0x02 पूर्ण,
	अणु REG_TIMING_DVPVO_L, 0x58 पूर्ण,
	अणु REG_TIMING_HTS_H, 0x05 पूर्ण,
	अणु REG_TIMING_HTS_L, 0x14 पूर्ण,
	अणु REG_TIMING_VTS_H, 0x02 पूर्ण,
	अणु REG_TIMING_VTS_L, 0x68 पूर्ण,
	अणु REG_TIMING_HOFFS_L, 0x08 पूर्ण,
	अणु REG_TIMING_VOFFS_L, 0x02 पूर्ण,
	अणु REG_TIMING_XINC, 0x31 पूर्ण,
	अणु REG_TIMING_YINC, 0x31 पूर्ण,
	अणु 0x3a02, 0x02 पूर्ण,
	अणु 0x3a03, 0x68 पूर्ण,
	अणु 0x3a08, 0x00 पूर्ण,
	अणु 0x3a09, 0x5c पूर्ण,
	अणु 0x3a0a, 0x00 पूर्ण,
	अणु 0x3a0b, 0x4d पूर्ण,
	अणु 0x3a0d, 0x08 पूर्ण,
	अणु 0x3a0e, 0x06 पूर्ण,
	अणु 0x3a14, 0x02 पूर्ण,
	अणु 0x3a15, 0x28 पूर्ण,
	अणु REG_DVP_CTRL02, 0x01 पूर्ण,
	अणु 0x3623, 0x00 पूर्ण,
	अणु 0x3634, 0x76 पूर्ण,
	अणु 0x3701, 0x44 पूर्ण,
	अणु 0x3702, 0x18 पूर्ण,
	अणु 0x3703, 0x24 पूर्ण,
	अणु 0x3704, 0x24 पूर्ण,
	अणु 0x3705, 0x0c पूर्ण,
	अणु REG_TIMING_VERT_FORMAT, 0x81 पूर्ण,
	अणु REG_TIMING_HORIZ_FORMAT, 0x01 पूर्ण,
	अणु 0x370a, 0x52 पूर्ण,
	अणु REG_VFIFO_READ_START_H, 0x00 पूर्ण,
	अणु REG_VFIFO_READ_START_L, 0x80 पूर्ण,
	अणु REG_FORMAT_CTRL00, 0x30 पूर्ण,
	अणु 0x5086, 0x02 पूर्ण,
	अणु REG_ISP_CTRL00, 0xfb पूर्ण,
	अणु REG_ISP_CTRL01, 0x1f पूर्ण,
	अणु REG_ISP_CTRL02, 0x00 पूर्ण,
	अणु 0x5025, 0x0e पूर्ण,
	अणु 0x5026, 0x18 पूर्ण,
	अणु 0x5027, 0x34 पूर्ण,
	अणु 0x5028, 0x4c पूर्ण,
	अणु 0x5029, 0x62 पूर्ण,
	अणु 0x502a, 0x74 पूर्ण,
	अणु 0x502b, 0x85 पूर्ण,
	अणु 0x502c, 0x92 पूर्ण,
	अणु 0x502d, 0x9e पूर्ण,
	अणु 0x502e, 0xb2 पूर्ण,
	अणु 0x502f, 0xc0 पूर्ण,
	अणु 0x5030, 0xcc पूर्ण,
	अणु 0x5031, 0xe0 पूर्ण,
	अणु 0x5032, 0xee पूर्ण,
	अणु 0x5033, 0xf6 पूर्ण,
	अणु 0x5034, 0x11 पूर्ण,
	अणु 0x5070, 0x1c पूर्ण,
	अणु 0x5071, 0x5b पूर्ण,
	अणु 0x5072, 0x05 पूर्ण,
	अणु 0x5073, 0x20 पूर्ण,
	अणु 0x5074, 0x94 पूर्ण,
	अणु 0x5075, 0xb4 पूर्ण,
	अणु 0x5076, 0xb4 पूर्ण,
	अणु 0x5077, 0xaf पूर्ण,
	अणु 0x5078, 0x05 पूर्ण,
	अणु REG_CMX_SIGN, 0x98 पूर्ण,
	अणु REG_CMX_MISC_CTRL, 0x21 पूर्ण,
	अणु REG_AWB_CTRL00, 0x6a पूर्ण,
	अणु REG_AWB_CTRL01, 0x11 पूर्ण,
	अणु REG_AWB_CTRL02, 0x92 पूर्ण,
	अणु REG_AWB_CTRL03, 0x21 पूर्ण,
	अणु REG_AWB_CTRL04, 0xe1 पूर्ण,
	अणु REG_AWB_LOCAL_LIMIT, 0x01 पूर्ण,
	अणु 0x503c, 0x05 पूर्ण,
	अणु 0x503d, 0x08 पूर्ण,
	अणु 0x503e, 0x08 पूर्ण,
	अणु 0x503f, 0x64 पूर्ण,
	अणु 0x5040, 0x58 पूर्ण,
	अणु 0x5041, 0x2a पूर्ण,
	अणु 0x5042, 0xc5 पूर्ण,
	अणु 0x5043, 0x2e पूर्ण,
	अणु 0x5044, 0x3a पूर्ण,
	अणु 0x5045, 0x3c पूर्ण,
	अणु 0x5046, 0x44 पूर्ण,
	अणु 0x5047, 0xf8 पूर्ण,
	अणु 0x5048, 0x08 पूर्ण,
	अणु REG_AWB_CTRL12, 0x70 पूर्ण,
	अणु REG_AWB_CTRL13, 0xf0 पूर्ण,
	अणु REG_AWB_CTRL14, 0xf0 पूर्ण,
	अणु REG_LENC_RED_X0_H, 0x03 पूर्ण,
	अणु REG_LENC_RED_X0_L, 0x20 पूर्ण,
	अणु REG_LENC_RED_Y0_H, 0x02 पूर्ण,
	अणु REG_LENC_RED_Y0_L, 0x5c पूर्ण,
	अणु REG_LENC_RED_A1, 0x48 पूर्ण,
	अणु REG_LENC_RED_B1, 0x00 पूर्ण,
	अणु REG_LENC_RED_A2_B2, 0x66 पूर्ण,
	अणु REG_LENC_GREEN_X0_H, 0x03 पूर्ण,
	अणु REG_LENC_GREEN_X0_L, 0x30 पूर्ण,
	अणु REG_LENC_GREEN_Y0_H, 0x02 पूर्ण,
	अणु REG_LENC_GREEN_Y0_L, 0x7c पूर्ण,
	अणु REG_LENC_GREEN_A1, 0x40 पूर्ण,
	अणु REG_LENC_GREEN_B1, 0x00 पूर्ण,
	अणु REG_LENC_GREEN_A2_B2, 0x66 पूर्ण,
	अणु REG_LENC_BLUE_X0_H, 0x03 पूर्ण,
	अणु REG_LENC_BLUE_X0_L, 0x10 पूर्ण,
	अणु REG_LENC_BLUE_Y0_H, 0x02 पूर्ण,
	अणु REG_LENC_BLUE_Y0_L, 0x7c पूर्ण,
	अणु REG_LENC_BLUE_A1, 0x3a पूर्ण,
	अणु REG_LENC_BLUE_B1, 0x00 पूर्ण,
	अणु REG_LENC_BLUE_A2_B2, 0x66 पूर्ण,
	अणु REG_CIP_CTRL00, 0x44 पूर्ण,
	अणु REG_SHARPENMT_THRESH1, 0x08 पूर्ण,
	अणु REG_SHARPENMT_THRESH2, 0x10 पूर्ण,
	अणु REG_SHARPENMT_OFFSET1, 0x12 पूर्ण,
	अणु REG_SHARPENMT_OFFSET2, 0x02 पूर्ण,
	अणु REG_SHARPEN_THRESH1, 0x08 पूर्ण,
	अणु REG_SHARPEN_THRESH2, 0x10 पूर्ण,
	अणु REG_CIP_CTRL01, 0xa6 पूर्ण,
	अणु REG_DENOISE_THRESH1, 0x08 पूर्ण,
	अणु REG_DENOISE_THRESH2, 0x10 पूर्ण,
	अणु REG_DENOISE_OFFSET1, 0x04 पूर्ण,
	अणु REG_DENOISE_OFFSET2, 0x12 पूर्ण,
	अणु 0x507e, 0x40 पूर्ण,
	अणु 0x507f, 0x20 पूर्ण,
	अणु 0x507b, 0x02 पूर्ण,
	अणु REG_CMX_MISC_CTRL, 0x01 पूर्ण,
	अणु 0x5084, 0x0c पूर्ण,
	अणु 0x5085, 0x3e पूर्ण,
	अणु 0x5005, 0x80 पूर्ण,
	अणु 0x3a0f, 0x30 पूर्ण,
	अणु 0x3a10, 0x28 पूर्ण,
	अणु 0x3a1b, 0x32 पूर्ण,
	अणु 0x3a1e, 0x26 पूर्ण,
	अणु 0x3a11, 0x60 पूर्ण,
	अणु 0x3a1f, 0x14 पूर्ण,
	अणु 0x5060, 0x69 पूर्ण,
	अणु 0x5061, 0x7d पूर्ण,
	अणु 0x5062, 0x7d पूर्ण,
	अणु 0x5063, 0x69 पूर्ण,
	अणु REG_शून्य, 0x00 पूर्ण,
पूर्ण;

/* 1280X720 720p */
अटल काष्ठा sensor_रेजिस्टर ov2659_720p[] = अणु
	अणु REG_TIMING_HS_H, 0x00 पूर्ण,
	अणु REG_TIMING_HS_L, 0xa0 पूर्ण,
	अणु REG_TIMING_VS_H, 0x00 पूर्ण,
	अणु REG_TIMING_VS_L, 0xf0 पूर्ण,
	अणु REG_TIMING_HW_H, 0x05 पूर्ण,
	अणु REG_TIMING_HW_L, 0xbf पूर्ण,
	अणु REG_TIMING_VH_H, 0x03 पूर्ण,
	अणु REG_TIMING_VH_L, 0xcb पूर्ण,
	अणु REG_TIMING_DVPHO_H, 0x05 पूर्ण,
	अणु REG_TIMING_DVPHO_L, 0x00 पूर्ण,
	अणु REG_TIMING_DVPVO_H, 0x02 पूर्ण,
	अणु REG_TIMING_DVPVO_L, 0xd0 पूर्ण,
	अणु REG_TIMING_HTS_H, 0x06 पूर्ण,
	अणु REG_TIMING_HTS_L, 0x4c पूर्ण,
	अणु REG_TIMING_VTS_H, 0x02 पूर्ण,
	अणु REG_TIMING_VTS_L, 0xe8 पूर्ण,
	अणु REG_TIMING_HOFFS_L, 0x10 पूर्ण,
	अणु REG_TIMING_VOFFS_L, 0x06 पूर्ण,
	अणु REG_TIMING_XINC, 0x11 पूर्ण,
	अणु REG_TIMING_YINC, 0x11 पूर्ण,
	अणु REG_TIMING_VERT_FORMAT, 0x80 पूर्ण,
	अणु REG_TIMING_HORIZ_FORMAT, 0x00 पूर्ण,
	अणु 0x370a, 0x12 पूर्ण,
	अणु 0x3a03, 0xe8 पूर्ण,
	अणु 0x3a09, 0x6f पूर्ण,
	अणु 0x3a0b, 0x5d पूर्ण,
	अणु 0x3a15, 0x9a पूर्ण,
	अणु REG_VFIFO_READ_START_H, 0x00 पूर्ण,
	अणु REG_VFIFO_READ_START_L, 0x80 पूर्ण,
	अणु REG_ISP_CTRL02, 0x00 पूर्ण,
	अणु REG_शून्य, 0x00 पूर्ण,
पूर्ण;

/* 1600X1200 UXGA */
अटल काष्ठा sensor_रेजिस्टर ov2659_uxga[] = अणु
	अणु REG_TIMING_HS_H, 0x00 पूर्ण,
	अणु REG_TIMING_HS_L, 0x00 पूर्ण,
	अणु REG_TIMING_VS_H, 0x00 पूर्ण,
	अणु REG_TIMING_VS_L, 0x00 पूर्ण,
	अणु REG_TIMING_HW_H, 0x06 पूर्ण,
	अणु REG_TIMING_HW_L, 0x5f पूर्ण,
	अणु REG_TIMING_VH_H, 0x04 पूर्ण,
	अणु REG_TIMING_VH_L, 0xbb पूर्ण,
	अणु REG_TIMING_DVPHO_H, 0x06 पूर्ण,
	अणु REG_TIMING_DVPHO_L, 0x40 पूर्ण,
	अणु REG_TIMING_DVPVO_H, 0x04 पूर्ण,
	अणु REG_TIMING_DVPVO_L, 0xb0 पूर्ण,
	अणु REG_TIMING_HTS_H, 0x07 पूर्ण,
	अणु REG_TIMING_HTS_L, 0x9f पूर्ण,
	अणु REG_TIMING_VTS_H, 0x04 पूर्ण,
	अणु REG_TIMING_VTS_L, 0xd0 पूर्ण,
	अणु REG_TIMING_HOFFS_L, 0x10 पूर्ण,
	अणु REG_TIMING_VOFFS_L, 0x06 पूर्ण,
	अणु REG_TIMING_XINC, 0x11 पूर्ण,
	अणु REG_TIMING_YINC, 0x11 पूर्ण,
	अणु 0x3a02, 0x04 पूर्ण,
	अणु 0x3a03, 0xd0 पूर्ण,
	अणु 0x3a08, 0x00 पूर्ण,
	अणु 0x3a09, 0xb8 पूर्ण,
	अणु 0x3a0a, 0x00 पूर्ण,
	अणु 0x3a0b, 0x9a पूर्ण,
	अणु 0x3a0d, 0x08 पूर्ण,
	अणु 0x3a0e, 0x06 पूर्ण,
	अणु 0x3a14, 0x04 पूर्ण,
	अणु 0x3a15, 0x50 पूर्ण,
	अणु 0x3623, 0x00 पूर्ण,
	अणु 0x3634, 0x44 पूर्ण,
	अणु 0x3701, 0x44 पूर्ण,
	अणु 0x3702, 0x30 पूर्ण,
	अणु 0x3703, 0x48 पूर्ण,
	अणु 0x3704, 0x48 पूर्ण,
	अणु 0x3705, 0x18 पूर्ण,
	अणु REG_TIMING_VERT_FORMAT, 0x80 पूर्ण,
	अणु REG_TIMING_HORIZ_FORMAT, 0x00 पूर्ण,
	अणु 0x370a, 0x12 पूर्ण,
	अणु REG_VFIFO_READ_START_H, 0x00 पूर्ण,
	अणु REG_VFIFO_READ_START_L, 0x80 पूर्ण,
	अणु REG_ISP_CTRL02, 0x00 पूर्ण,
	अणु REG_शून्य, 0x00 पूर्ण,
पूर्ण;

/* 1280X1024 SXGA */
अटल काष्ठा sensor_रेजिस्टर ov2659_sxga[] = अणु
	अणु REG_TIMING_HS_H, 0x00 पूर्ण,
	अणु REG_TIMING_HS_L, 0x00 पूर्ण,
	अणु REG_TIMING_VS_H, 0x00 पूर्ण,
	अणु REG_TIMING_VS_L, 0x00 पूर्ण,
	अणु REG_TIMING_HW_H, 0x06 पूर्ण,
	अणु REG_TIMING_HW_L, 0x5f पूर्ण,
	अणु REG_TIMING_VH_H, 0x04 पूर्ण,
	अणु REG_TIMING_VH_L, 0xb7 पूर्ण,
	अणु REG_TIMING_DVPHO_H, 0x05 पूर्ण,
	अणु REG_TIMING_DVPHO_L, 0x00 पूर्ण,
	अणु REG_TIMING_DVPVO_H, 0x04 पूर्ण,
	अणु REG_TIMING_DVPVO_L, 0x00 पूर्ण,
	अणु REG_TIMING_HTS_H, 0x07 पूर्ण,
	अणु REG_TIMING_HTS_L, 0x9c पूर्ण,
	अणु REG_TIMING_VTS_H, 0x04 पूर्ण,
	अणु REG_TIMING_VTS_L, 0xd0 पूर्ण,
	अणु REG_TIMING_HOFFS_L, 0x10 पूर्ण,
	अणु REG_TIMING_VOFFS_L, 0x06 पूर्ण,
	अणु REG_TIMING_XINC, 0x11 पूर्ण,
	अणु REG_TIMING_YINC, 0x11 पूर्ण,
	अणु 0x3a02, 0x02 पूर्ण,
	अणु 0x3a03, 0x68 पूर्ण,
	अणु 0x3a08, 0x00 पूर्ण,
	अणु 0x3a09, 0x5c पूर्ण,
	अणु 0x3a0a, 0x00 पूर्ण,
	अणु 0x3a0b, 0x4d पूर्ण,
	अणु 0x3a0d, 0x08 पूर्ण,
	अणु 0x3a0e, 0x06 पूर्ण,
	अणु 0x3a14, 0x02 पूर्ण,
	अणु 0x3a15, 0x28 पूर्ण,
	अणु 0x3623, 0x00 पूर्ण,
	अणु 0x3634, 0x76 पूर्ण,
	अणु 0x3701, 0x44 पूर्ण,
	अणु 0x3702, 0x18 पूर्ण,
	अणु 0x3703, 0x24 पूर्ण,
	अणु 0x3704, 0x24 पूर्ण,
	अणु 0x3705, 0x0c पूर्ण,
	अणु REG_TIMING_VERT_FORMAT, 0x80 पूर्ण,
	अणु REG_TIMING_HORIZ_FORMAT, 0x00 पूर्ण,
	अणु 0x370a, 0x52 पूर्ण,
	अणु REG_VFIFO_READ_START_H, 0x00 पूर्ण,
	अणु REG_VFIFO_READ_START_L, 0x80 पूर्ण,
	अणु REG_ISP_CTRL02, 0x00 पूर्ण,
	अणु REG_शून्य, 0x00 पूर्ण,
पूर्ण;

/* 1024X768 SXGA */
अटल काष्ठा sensor_रेजिस्टर ov2659_xga[] = अणु
	अणु REG_TIMING_HS_H, 0x00 पूर्ण,
	अणु REG_TIMING_HS_L, 0x00 पूर्ण,
	अणु REG_TIMING_VS_H, 0x00 पूर्ण,
	अणु REG_TIMING_VS_L, 0x00 पूर्ण,
	अणु REG_TIMING_HW_H, 0x06 पूर्ण,
	अणु REG_TIMING_HW_L, 0x5f पूर्ण,
	अणु REG_TIMING_VH_H, 0x04 पूर्ण,
	अणु REG_TIMING_VH_L, 0xb7 पूर्ण,
	अणु REG_TIMING_DVPHO_H, 0x04 पूर्ण,
	अणु REG_TIMING_DVPHO_L, 0x00 पूर्ण,
	अणु REG_TIMING_DVPVO_H, 0x03 पूर्ण,
	अणु REG_TIMING_DVPVO_L, 0x00 पूर्ण,
	अणु REG_TIMING_HTS_H, 0x07 पूर्ण,
	अणु REG_TIMING_HTS_L, 0x9c पूर्ण,
	अणु REG_TIMING_VTS_H, 0x04 पूर्ण,
	अणु REG_TIMING_VTS_L, 0xd0 पूर्ण,
	अणु REG_TIMING_HOFFS_L, 0x10 पूर्ण,
	अणु REG_TIMING_VOFFS_L, 0x06 पूर्ण,
	अणु REG_TIMING_XINC, 0x11 पूर्ण,
	अणु REG_TIMING_YINC, 0x11 पूर्ण,
	अणु 0x3a02, 0x02 पूर्ण,
	अणु 0x3a03, 0x68 पूर्ण,
	अणु 0x3a08, 0x00 पूर्ण,
	अणु 0x3a09, 0x5c पूर्ण,
	अणु 0x3a0a, 0x00 पूर्ण,
	अणु 0x3a0b, 0x4d पूर्ण,
	अणु 0x3a0d, 0x08 पूर्ण,
	अणु 0x3a0e, 0x06 पूर्ण,
	अणु 0x3a14, 0x02 पूर्ण,
	अणु 0x3a15, 0x28 पूर्ण,
	अणु 0x3623, 0x00 पूर्ण,
	अणु 0x3634, 0x76 पूर्ण,
	अणु 0x3701, 0x44 पूर्ण,
	अणु 0x3702, 0x18 पूर्ण,
	अणु 0x3703, 0x24 पूर्ण,
	अणु 0x3704, 0x24 पूर्ण,
	अणु 0x3705, 0x0c पूर्ण,
	अणु REG_TIMING_VERT_FORMAT, 0x80 पूर्ण,
	अणु REG_TIMING_HORIZ_FORMAT, 0x00 पूर्ण,
	अणु 0x370a, 0x52 पूर्ण,
	अणु REG_VFIFO_READ_START_H, 0x00 पूर्ण,
	अणु REG_VFIFO_READ_START_L, 0x80 पूर्ण,
	अणु REG_ISP_CTRL02, 0x00 पूर्ण,
	अणु REG_शून्य, 0x00 पूर्ण,
पूर्ण;

/* 800X600 SVGA */
अटल काष्ठा sensor_रेजिस्टर ov2659_svga[] = अणु
	अणु REG_TIMING_HS_H, 0x00 पूर्ण,
	अणु REG_TIMING_HS_L, 0x00 पूर्ण,
	अणु REG_TIMING_VS_H, 0x00 पूर्ण,
	अणु REG_TIMING_VS_L, 0x00 पूर्ण,
	अणु REG_TIMING_HW_H, 0x06 पूर्ण,
	अणु REG_TIMING_HW_L, 0x5f पूर्ण,
	अणु REG_TIMING_VH_H, 0x04 पूर्ण,
	अणु REG_TIMING_VH_L, 0xb7 पूर्ण,
	अणु REG_TIMING_DVPHO_H, 0x03 पूर्ण,
	अणु REG_TIMING_DVPHO_L, 0x20 पूर्ण,
	अणु REG_TIMING_DVPVO_H, 0x02 पूर्ण,
	अणु REG_TIMING_DVPVO_L, 0x58 पूर्ण,
	अणु REG_TIMING_HTS_H, 0x05 पूर्ण,
	अणु REG_TIMING_HTS_L, 0x14 पूर्ण,
	अणु REG_TIMING_VTS_H, 0x02 पूर्ण,
	अणु REG_TIMING_VTS_L, 0x68 पूर्ण,
	अणु REG_TIMING_HOFFS_L, 0x08 पूर्ण,
	अणु REG_TIMING_VOFFS_L, 0x02 पूर्ण,
	अणु REG_TIMING_XINC, 0x31 पूर्ण,
	अणु REG_TIMING_YINC, 0x31 पूर्ण,
	अणु 0x3a02, 0x02 पूर्ण,
	अणु 0x3a03, 0x68 पूर्ण,
	अणु 0x3a08, 0x00 पूर्ण,
	अणु 0x3a09, 0x5c पूर्ण,
	अणु 0x3a0a, 0x00 पूर्ण,
	अणु 0x3a0b, 0x4d पूर्ण,
	अणु 0x3a0d, 0x08 पूर्ण,
	अणु 0x3a0e, 0x06 पूर्ण,
	अणु 0x3a14, 0x02 पूर्ण,
	अणु 0x3a15, 0x28 पूर्ण,
	अणु 0x3623, 0x00 पूर्ण,
	अणु 0x3634, 0x76 पूर्ण,
	अणु 0x3701, 0x44 पूर्ण,
	अणु 0x3702, 0x18 पूर्ण,
	अणु 0x3703, 0x24 पूर्ण,
	अणु 0x3704, 0x24 पूर्ण,
	अणु 0x3705, 0x0c पूर्ण,
	अणु REG_TIMING_VERT_FORMAT, 0x81 पूर्ण,
	अणु REG_TIMING_HORIZ_FORMAT, 0x01 पूर्ण,
	अणु 0x370a, 0x52 पूर्ण,
	अणु REG_VFIFO_READ_START_H, 0x00 पूर्ण,
	अणु REG_VFIFO_READ_START_L, 0x80 पूर्ण,
	अणु REG_ISP_CTRL02, 0x00 पूर्ण,
	अणु REG_शून्य, 0x00 पूर्ण,
पूर्ण;

/* 640X480 VGA */
अटल काष्ठा sensor_रेजिस्टर ov2659_vga[] = अणु
	अणु REG_TIMING_HS_H, 0x00 पूर्ण,
	अणु REG_TIMING_HS_L, 0x00 पूर्ण,
	अणु REG_TIMING_VS_H, 0x00 पूर्ण,
	अणु REG_TIMING_VS_L, 0x00 पूर्ण,
	अणु REG_TIMING_HW_H, 0x06 पूर्ण,
	अणु REG_TIMING_HW_L, 0x5f पूर्ण,
	अणु REG_TIMING_VH_H, 0x04 पूर्ण,
	अणु REG_TIMING_VH_L, 0xb7 पूर्ण,
	अणु REG_TIMING_DVPHO_H, 0x02 पूर्ण,
	अणु REG_TIMING_DVPHO_L, 0x80 पूर्ण,
	अणु REG_TIMING_DVPVO_H, 0x01 पूर्ण,
	अणु REG_TIMING_DVPVO_L, 0xe0 पूर्ण,
	अणु REG_TIMING_HTS_H, 0x05 पूर्ण,
	अणु REG_TIMING_HTS_L, 0x14 पूर्ण,
	अणु REG_TIMING_VTS_H, 0x02 पूर्ण,
	अणु REG_TIMING_VTS_L, 0x68 पूर्ण,
	अणु REG_TIMING_HOFFS_L, 0x08 पूर्ण,
	अणु REG_TIMING_VOFFS_L, 0x02 पूर्ण,
	अणु REG_TIMING_XINC, 0x31 पूर्ण,
	अणु REG_TIMING_YINC, 0x31 पूर्ण,
	अणु 0x3a02, 0x02 पूर्ण,
	अणु 0x3a03, 0x68 पूर्ण,
	अणु 0x3a08, 0x00 पूर्ण,
	अणु 0x3a09, 0x5c पूर्ण,
	अणु 0x3a0a, 0x00 पूर्ण,
	अणु 0x3a0b, 0x4d पूर्ण,
	अणु 0x3a0d, 0x08 पूर्ण,
	अणु 0x3a0e, 0x06 पूर्ण,
	अणु 0x3a14, 0x02 पूर्ण,
	अणु 0x3a15, 0x28 पूर्ण,
	अणु 0x3623, 0x00 पूर्ण,
	अणु 0x3634, 0x76 पूर्ण,
	अणु 0x3701, 0x44 पूर्ण,
	अणु 0x3702, 0x18 पूर्ण,
	अणु 0x3703, 0x24 पूर्ण,
	अणु 0x3704, 0x24 पूर्ण,
	अणु 0x3705, 0x0c पूर्ण,
	अणु REG_TIMING_VERT_FORMAT, 0x81 पूर्ण,
	अणु REG_TIMING_HORIZ_FORMAT, 0x01 पूर्ण,
	अणु 0x370a, 0x52 पूर्ण,
	अणु REG_VFIFO_READ_START_H, 0x00 पूर्ण,
	अणु REG_VFIFO_READ_START_L, 0xa0 पूर्ण,
	अणु REG_ISP_CTRL02, 0x10 पूर्ण,
	अणु REG_शून्य, 0x00 पूर्ण,
पूर्ण;

/* 320X240 QVGA */
अटल  काष्ठा sensor_रेजिस्टर ov2659_qvga[] = अणु
	अणु REG_TIMING_HS_H, 0x00 पूर्ण,
	अणु REG_TIMING_HS_L, 0x00 पूर्ण,
	अणु REG_TIMING_VS_H, 0x00 पूर्ण,
	अणु REG_TIMING_VS_L, 0x00 पूर्ण,
	अणु REG_TIMING_HW_H, 0x06 पूर्ण,
	अणु REG_TIMING_HW_L, 0x5f पूर्ण,
	अणु REG_TIMING_VH_H, 0x04 पूर्ण,
	अणु REG_TIMING_VH_L, 0xb7 पूर्ण,
	अणु REG_TIMING_DVPHO_H, 0x01 पूर्ण,
	अणु REG_TIMING_DVPHO_L, 0x40 पूर्ण,
	अणु REG_TIMING_DVPVO_H, 0x00 पूर्ण,
	अणु REG_TIMING_DVPVO_L, 0xf0 पूर्ण,
	अणु REG_TIMING_HTS_H, 0x05 पूर्ण,
	अणु REG_TIMING_HTS_L, 0x14 पूर्ण,
	अणु REG_TIMING_VTS_H, 0x02 पूर्ण,
	अणु REG_TIMING_VTS_L, 0x68 पूर्ण,
	अणु REG_TIMING_HOFFS_L, 0x08 पूर्ण,
	अणु REG_TIMING_VOFFS_L, 0x02 पूर्ण,
	अणु REG_TIMING_XINC, 0x31 पूर्ण,
	अणु REG_TIMING_YINC, 0x31 पूर्ण,
	अणु 0x3a02, 0x02 पूर्ण,
	अणु 0x3a03, 0x68 पूर्ण,
	अणु 0x3a08, 0x00 पूर्ण,
	अणु 0x3a09, 0x5c पूर्ण,
	अणु 0x3a0a, 0x00 पूर्ण,
	अणु 0x3a0b, 0x4d पूर्ण,
	अणु 0x3a0d, 0x08 पूर्ण,
	अणु 0x3a0e, 0x06 पूर्ण,
	अणु 0x3a14, 0x02 पूर्ण,
	अणु 0x3a15, 0x28 पूर्ण,
	अणु 0x3623, 0x00 पूर्ण,
	अणु 0x3634, 0x76 पूर्ण,
	अणु 0x3701, 0x44 पूर्ण,
	अणु 0x3702, 0x18 पूर्ण,
	अणु 0x3703, 0x24 पूर्ण,
	अणु 0x3704, 0x24 पूर्ण,
	अणु 0x3705, 0x0c पूर्ण,
	अणु REG_TIMING_VERT_FORMAT, 0x81 पूर्ण,
	अणु REG_TIMING_HORIZ_FORMAT, 0x01 पूर्ण,
	अणु 0x370a, 0x52 पूर्ण,
	अणु REG_VFIFO_READ_START_H, 0x00 पूर्ण,
	अणु REG_VFIFO_READ_START_L, 0xa0 पूर्ण,
	अणु REG_ISP_CTRL02, 0x10 पूर्ण,
	अणु REG_शून्य, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pll_ctrl_reg ctrl3[] = अणु
	अणु 1, 0x00 पूर्ण,
	अणु 2, 0x02 पूर्ण,
	अणु 3, 0x03 पूर्ण,
	अणु 4, 0x06 पूर्ण,
	अणु 6, 0x0d पूर्ण,
	अणु 8, 0x0e पूर्ण,
	अणु 12, 0x0f पूर्ण,
	अणु 16, 0x12 पूर्ण,
	अणु 24, 0x13 पूर्ण,
	अणु 32, 0x16 पूर्ण,
	अणु 48, 0x1b पूर्ण,
	अणु 64, 0x1e पूर्ण,
	अणु 96, 0x1f पूर्ण,
	अणु 0, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pll_ctrl_reg ctrl1[] = अणु
	अणु 2, 0x10 पूर्ण,
	अणु 4, 0x20 पूर्ण,
	अणु 6, 0x30 पूर्ण,
	अणु 8, 0x40 पूर्ण,
	अणु 10, 0x50 पूर्ण,
	अणु 12, 0x60 पूर्ण,
	अणु 14, 0x70 पूर्ण,
	अणु 16, 0x80 पूर्ण,
	अणु 18, 0x90 पूर्ण,
	अणु 20, 0xa0 पूर्ण,
	अणु 22, 0xb0 पूर्ण,
	अणु 24, 0xc0 पूर्ण,
	अणु 26, 0xd0 पूर्ण,
	अणु 28, 0xe0 पूर्ण,
	अणु 30, 0xf0 पूर्ण,
	अणु 0, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov2659_framesize ov2659_framesizes[] = अणु
	अणु /* QVGA */
		.width		= 320,
		.height		= 240,
		.regs		= ov2659_qvga,
		.max_exp_lines	= 248,
	पूर्ण, अणु /* VGA */
		.width		= 640,
		.height		= 480,
		.regs		= ov2659_vga,
		.max_exp_lines	= 498,
	पूर्ण, अणु /* SVGA */
		.width		= 800,
		.height		= 600,
		.regs		= ov2659_svga,
		.max_exp_lines	= 498,
	पूर्ण, अणु /* XGA */
		.width		= 1024,
		.height		= 768,
		.regs		= ov2659_xga,
		.max_exp_lines	= 498,
	पूर्ण, अणु /* 720P */
		.width		= 1280,
		.height		= 720,
		.regs		= ov2659_720p,
		.max_exp_lines	= 498,
	पूर्ण, अणु /* SXGA */
		.width		= 1280,
		.height		= 1024,
		.regs		= ov2659_sxga,
		.max_exp_lines	= 1048,
	पूर्ण, अणु /* UXGA */
		.width		= 1600,
		.height		= 1200,
		.regs		= ov2659_uxga,
		.max_exp_lines	= 498,
	पूर्ण,
पूर्ण;

/* YUV422 YUYV*/
अटल काष्ठा sensor_रेजिस्टर ov2659_क्रमmat_yuyv[] = अणु
	अणु REG_FORMAT_CTRL00, 0x30 पूर्ण,
	अणु REG_शून्य, 0x0 पूर्ण,
पूर्ण;

/* YUV422 UYVY  */
अटल काष्ठा sensor_रेजिस्टर ov2659_क्रमmat_uyvy[] = अणु
	अणु REG_FORMAT_CTRL00, 0x32 पूर्ण,
	अणु REG_शून्य, 0x0 पूर्ण,
पूर्ण;

/* Raw Bayer BGGR */
अटल काष्ठा sensor_रेजिस्टर ov2659_क्रमmat_bggr[] = अणु
	अणु REG_FORMAT_CTRL00, 0x00 पूर्ण,
	अणु REG_शून्य, 0x0 पूर्ण,
पूर्ण;

/* RGB565 */
अटल काष्ठा sensor_रेजिस्टर ov2659_क्रमmat_rgb565[] = अणु
	अणु REG_FORMAT_CTRL00, 0x60 पूर्ण,
	अणु REG_शून्य, 0x0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov2659_pixfmt ov2659_क्रमmats[] = अणु
	अणु
		.code = MEDIA_BUS_FMT_YUYV8_2X8,
		.क्रमmat_ctrl_regs = ov2659_क्रमmat_yuyv,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_UYVY8_2X8,
		.क्रमmat_ctrl_regs = ov2659_क्रमmat_uyvy,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_RGB565_2X8_BE,
		.क्रमmat_ctrl_regs = ov2659_क्रमmat_rgb565,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SBGGR8_1X8,
		.क्रमmat_ctrl_regs = ov2659_क्रमmat_bggr,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा ov2659 *to_ov2659(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ov2659, sd);
पूर्ण

/* sensor रेजिस्टर ग_लिखो */
अटल पूर्णांक ov2659_ग_लिखो(काष्ठा i2c_client *client, u16 reg, u8 val)
अणु
	काष्ठा i2c_msg msg;
	u8 buf[3];
	पूर्णांक ret;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xFF;
	buf[2] = val;

	msg.addr = client->addr;
	msg.flags = client->flags;
	msg.buf = buf;
	msg.len = माप(buf);

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret >= 0)
		वापस 0;

	dev_dbg(&client->dev,
		"ov2659 write reg(0x%x val:0x%x) failed !\n", reg, val);

	वापस ret;
पूर्ण

/* sensor रेजिस्टर पढ़ो */
अटल पूर्णांक ov2659_पढ़ो(काष्ठा i2c_client *client, u16 reg, u8 *val)
अणु
	काष्ठा i2c_msg msg[2];
	u8 buf[2];
	पूर्णांक ret;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xFF;

	msg[0].addr = client->addr;
	msg[0].flags = client->flags;
	msg[0].buf = buf;
	msg[0].len = माप(buf);

	msg[1].addr = client->addr;
	msg[1].flags = client->flags | I2C_M_RD;
	msg[1].buf = buf;
	msg[1].len = 1;

	ret = i2c_transfer(client->adapter, msg, 2);
	अगर (ret >= 0) अणु
		*val = buf[0];
		वापस 0;
	पूर्ण

	dev_dbg(&client->dev,
		"ov2659 read reg(0x%x val:0x%x) failed !\n", reg, *val);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2659_ग_लिखो_array(काष्ठा i2c_client *client,
			      स्थिर काष्ठा sensor_रेजिस्टर *regs)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; ret == 0 && regs[i].addr; i++)
		ret = ov2659_ग_लिखो(client, regs[i].addr, regs[i].value);

	वापस ret;
पूर्ण

अटल व्योम ov2659_pll_calc_params(काष्ठा ov2659 *ov2659)
अणु
	स्थिर काष्ठा ov2659_platक्रमm_data *pdata = ov2659->pdata;
	u8 ctrl1_reg = 0, ctrl2_reg = 0, ctrl3_reg = 0;
	काष्ठा i2c_client *client = ov2659->client;
	अचिन्हित पूर्णांक desired = pdata->link_frequency;
	u32 preभाग, postभाग, mult;
	u32 bestdelta = -1;
	u32 delta, actual;
	पूर्णांक i, j;

	क्रम (i = 0; ctrl1[i].भाग != 0; i++) अणु
		postभाग = ctrl1[i].भाग;
		क्रम (j = 0; ctrl3[j].भाग != 0; j++) अणु
			preभाग = ctrl3[j].भाग;
			क्रम (mult = 1; mult <= 63; mult++) अणु
				actual  = ov2659->xvclk_frequency;
				actual *= mult;
				actual /= preभाग;
				actual /= postभाग;
				delta = actual - desired;
				delta = असल(delta);

				अगर ((delta < bestdelta) || (bestdelta == -1)) अणु
					bestdelta = delta;
					ctrl1_reg = ctrl1[i].reg;
					ctrl2_reg = mult;
					ctrl3_reg = ctrl3[j].reg;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	ov2659->pll.ctrl1 = ctrl1_reg;
	ov2659->pll.ctrl2 = ctrl2_reg;
	ov2659->pll.ctrl3 = ctrl3_reg;

	dev_dbg(&client->dev,
		"Actual reg config: ctrl1_reg: %02x ctrl2_reg: %02x ctrl3_reg: %02x\n",
		ctrl1_reg, ctrl2_reg, ctrl3_reg);
पूर्ण

अटल पूर्णांक ov2659_set_pixel_घड़ी(काष्ठा ov2659 *ov2659)
अणु
	काष्ठा i2c_client *client = ov2659->client;
	काष्ठा sensor_रेजिस्टर pll_regs[] = अणु
		अणुREG_SC_PLL_CTRL1, ov2659->pll.ctrl1पूर्ण,
		अणुREG_SC_PLL_CTRL2, ov2659->pll.ctrl2पूर्ण,
		अणुREG_SC_PLL_CTRL3, ov2659->pll.ctrl3पूर्ण,
		अणुREG_शून्य, 0x00पूर्ण,
	पूर्ण;

	dev_dbg(&client->dev, "%s\n", __func__);

	वापस ov2659_ग_लिखो_array(client, pll_regs);
पूर्ण;

अटल व्योम ov2659_get_शेष_क्रमmat(काष्ठा v4l2_mbus_framefmt *क्रमmat)
अणु
	क्रमmat->width = ov2659_framesizes[2].width;
	क्रमmat->height = ov2659_framesizes[2].height;
	क्रमmat->colorspace = V4L2_COLORSPACE_SRGB;
	क्रमmat->code = ov2659_क्रमmats[0].code;
	क्रमmat->field = V4L2_FIELD_NONE;
पूर्ण

अटल व्योम ov2659_set_streaming(काष्ठा ov2659 *ov2659, पूर्णांक on)
अणु
	काष्ठा i2c_client *client = ov2659->client;
	पूर्णांक ret;

	on = !!on;

	dev_dbg(&client->dev, "%s: on: %d\n", __func__, on);

	ret = ov2659_ग_लिखो(client, REG_SOFTWARE_STANDBY, on);
	अगर (ret)
		dev_err(&client->dev, "ov2659 soft standby failed\n");
पूर्ण

अटल पूर्णांक ov2659_init(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस ov2659_ग_लिखो_array(client, ov2659_init_regs);
पूर्ण

/*
 * V4L2 subdev video and pad level operations
 */

अटल पूर्णांक ov2659_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	dev_dbg(&client->dev, "%s:\n", __func__);

	अगर (code->index >= ARRAY_SIZE(ov2659_क्रमmats))
		वापस -EINVAL;

	code->code = ov2659_क्रमmats[code->index].code;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2659_क्रमागत_frame_sizes(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक i = ARRAY_SIZE(ov2659_क्रमmats);

	dev_dbg(&client->dev, "%s:\n", __func__);

	अगर (fse->index >= ARRAY_SIZE(ov2659_framesizes))
		वापस -EINVAL;

	जबतक (--i)
		अगर (fse->code == ov2659_क्रमmats[i].code)
			अवरोध;

	fse->code = ov2659_क्रमmats[i].code;

	fse->min_width  = ov2659_framesizes[fse->index].width;
	fse->max_width  = fse->min_width;
	fse->max_height = ov2659_framesizes[fse->index].height;
	fse->min_height = fse->max_height;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2659_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov2659 *ov2659 = to_ov2659(sd);

	dev_dbg(&client->dev, "ov2659_get_fmt\n");

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
		काष्ठा v4l2_mbus_framefmt *mf;

		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		mutex_lock(&ov2659->lock);
		fmt->क्रमmat = *mf;
		mutex_unlock(&ov2659->lock);
		वापस 0;
#अन्यथा
		वापस -EINVAL;
#पूर्ण_अगर
	पूर्ण

	mutex_lock(&ov2659->lock);
	fmt->क्रमmat = ov2659->क्रमmat;
	mutex_unlock(&ov2659->lock);

	dev_dbg(&client->dev, "ov2659_get_fmt: %x %dx%d\n",
		ov2659->क्रमmat.code, ov2659->क्रमmat.width,
		ov2659->क्रमmat.height);

	वापस 0;
पूर्ण

अटल व्योम __ov2659_try_frame_size(काष्ठा v4l2_mbus_framefmt *mf,
				    स्थिर काष्ठा ov2659_framesize **size)
अणु
	स्थिर काष्ठा ov2659_framesize *fsize = &ov2659_framesizes[0];
	स्थिर काष्ठा ov2659_framesize *match = शून्य;
	पूर्णांक i = ARRAY_SIZE(ov2659_framesizes);
	अचिन्हित पूर्णांक min_err = अच_पूर्णांक_उच्च;

	जबतक (i--) अणु
		पूर्णांक err = असल(fsize->width - mf->width)
				+ असल(fsize->height - mf->height);
		अगर ((err < min_err) && (fsize->regs[0].addr)) अणु
			min_err = err;
			match = fsize;
		पूर्ण
		fsize++;
	पूर्ण

	अगर (!match)
		match = &ov2659_framesizes[2];

	mf->width  = match->width;
	mf->height = match->height;

	अगर (size)
		*size = match;
पूर्ण

अटल पूर्णांक ov2659_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक index = ARRAY_SIZE(ov2659_क्रमmats);
	काष्ठा v4l2_mbus_framefmt *mf = &fmt->क्रमmat;
	स्थिर काष्ठा ov2659_framesize *size = शून्य;
	काष्ठा ov2659 *ov2659 = to_ov2659(sd);
	पूर्णांक ret = 0;

	dev_dbg(&client->dev, "ov2659_set_fmt\n");

	__ov2659_try_frame_size(mf, &size);

	जबतक (--index >= 0)
		अगर (ov2659_क्रमmats[index].code == mf->code)
			अवरोध;

	अगर (index < 0) अणु
		index = 0;
		mf->code = ov2659_क्रमmats[index].code;
	पूर्ण

	mf->colorspace = V4L2_COLORSPACE_SRGB;
	mf->field = V4L2_FIELD_NONE;

	mutex_lock(&ov2659->lock);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		*mf = fmt->क्रमmat;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		s64 val;

		अगर (ov2659->streaming) अणु
			mutex_unlock(&ov2659->lock);
			वापस -EBUSY;
		पूर्ण

		ov2659->frame_size = size;
		ov2659->क्रमmat = fmt->क्रमmat;
		ov2659->क्रमmat_ctrl_regs =
			ov2659_क्रमmats[index].क्रमmat_ctrl_regs;

		अगर (ov2659->क्रमmat.code != MEDIA_BUS_FMT_SBGGR8_1X8)
			val = ov2659->pdata->link_frequency / 2;
		अन्यथा
			val = ov2659->pdata->link_frequency;

		ret = v4l2_ctrl_s_ctrl_पूर्णांक64(ov2659->link_frequency, val);
		अगर (ret < 0)
			dev_warn(&client->dev,
				 "failed to set link_frequency rate (%d)\n",
				 ret);
	पूर्ण

	mutex_unlock(&ov2659->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov2659_set_frame_size(काष्ठा ov2659 *ov2659)
अणु
	काष्ठा i2c_client *client = ov2659->client;

	dev_dbg(&client->dev, "%s\n", __func__);

	वापस ov2659_ग_लिखो_array(ov2659->client, ov2659->frame_size->regs);
पूर्ण

अटल पूर्णांक ov2659_set_क्रमmat(काष्ठा ov2659 *ov2659)
अणु
	काष्ठा i2c_client *client = ov2659->client;

	dev_dbg(&client->dev, "%s\n", __func__);

	वापस ov2659_ग_लिखो_array(ov2659->client, ov2659->क्रमmat_ctrl_regs);
पूर्ण

अटल पूर्णांक ov2659_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov2659 *ov2659 = to_ov2659(sd);
	पूर्णांक ret = 0;

	dev_dbg(&client->dev, "%s: on: %d\n", __func__, on);

	mutex_lock(&ov2659->lock);

	on = !!on;

	अगर (ov2659->streaming == on)
		जाओ unlock;

	अगर (!on) अणु
		/* Stop Streaming Sequence */
		ov2659_set_streaming(ov2659, 0);
		ov2659->streaming = on;
		pm_runसमय_put(&client->dev);
		जाओ unlock;
	पूर्ण

	ret = pm_runसमय_get_sync(&client->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&client->dev);
		जाओ unlock;
	पूर्ण

	ret = ov2659_init(sd, 0);
	अगर (!ret)
		ret = ov2659_set_pixel_घड़ी(ov2659);
	अगर (!ret)
		ret = ov2659_set_frame_size(ov2659);
	अगर (!ret)
		ret = ov2659_set_क्रमmat(ov2659);
	अगर (!ret) अणु
		ov2659_set_streaming(ov2659, 1);
		ov2659->streaming = on;
	पूर्ण

unlock:
	mutex_unlock(&ov2659->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov2659_set_test_pattern(काष्ठा ov2659 *ov2659, पूर्णांक value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov2659->sd);
	पूर्णांक ret;
	u8 val;

	ret = ov2659_पढ़ो(client, REG_PRE_ISP_CTRL00, &val);
	अगर (ret < 0)
		वापस ret;

	चयन (value) अणु
	हाल 0:
		val &= ~TEST_PATTERN_ENABLE;
		अवरोध;
	हाल 1:
		val &= VERTICAL_COLOR_BAR_MASK;
		val |= TEST_PATTERN_ENABLE;
		अवरोध;
	पूर्ण

	वापस ov2659_ग_लिखो(client, REG_PRE_ISP_CTRL00, val);
पूर्ण

अटल पूर्णांक ov2659_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov2659 *ov2659 =
			container_of(ctrl->handler, काष्ठा ov2659, ctrls);
	काष्ठा i2c_client *client = ov2659->client;

	/* V4L2 controls values will be applied only when घातer is alपढ़ोy up */
	अगर (!pm_runसमय_get_अगर_in_use(&client->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_TEST_PATTERN:
		वापस ov2659_set_test_pattern(ov2659, ctrl->val);
	पूर्ण

	pm_runसमय_put(&client->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov2659_ctrl_ops = अणु
	.s_ctrl = ov2659_s_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ov2659_test_pattern_menu[] = अणु
	"Disabled",
	"Vertical Color Bars",
पूर्ण;

अटल पूर्णांक ov2659_घातer_off(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov2659 *ov2659 = to_ov2659(sd);

	dev_dbg(&client->dev, "%s:\n", __func__);

	gpiod_set_value(ov2659->pwdn_gpio, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2659_घातer_on(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov2659 *ov2659 = to_ov2659(sd);

	dev_dbg(&client->dev, "%s:\n", __func__);

	gpiod_set_value(ov2659->pwdn_gpio, 0);

	अगर (ov2659->resetb_gpio) अणु
		gpiod_set_value(ov2659->resetb_gpio, 1);
		usleep_range(500, 1000);
		gpiod_set_value(ov2659->resetb_gpio, 0);
		usleep_range(3000, 5000);
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 subdev पूर्णांकernal operations
 */

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
अटल पूर्णांक ov2659_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat =
				v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);

	dev_dbg(&client->dev, "%s:\n", __func__);

	ov2659_get_शेष_क्रमmat(क्रमmat);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov2659_subdev_core_ops = अणु
	.log_status = v4l2_ctrl_subdev_log_status,
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov2659_subdev_video_ops = अणु
	.s_stream = ov2659_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov2659_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = ov2659_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov2659_क्रमागत_frame_sizes,
	.get_fmt = ov2659_get_fmt,
	.set_fmt = ov2659_set_fmt,
पूर्ण;

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
अटल स्थिर काष्ठा v4l2_subdev_ops ov2659_subdev_ops = अणु
	.core  = &ov2659_subdev_core_ops,
	.video = &ov2659_subdev_video_ops,
	.pad   = &ov2659_subdev_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ov2659_subdev_पूर्णांकernal_ops = अणु
	.खोलो = ov2659_खोलो,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक ov2659_detect(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 pid = 0;
	u8 ver = 0;
	पूर्णांक ret;

	dev_dbg(&client->dev, "%s:\n", __func__);

	ret = ov2659_ग_लिखो(client, REG_SOFTWARE_RESET, 0x01);
	अगर (ret != 0) अणु
		dev_err(&client->dev, "Sensor soft reset failed\n");
		वापस -ENODEV;
	पूर्ण
	usleep_range(1000, 2000);

	/* Check sensor revision */
	ret = ov2659_पढ़ो(client, REG_SC_CHIP_ID_H, &pid);
	अगर (!ret)
		ret = ov2659_पढ़ो(client, REG_SC_CHIP_ID_L, &ver);

	अगर (!ret) अणु
		अचिन्हित लघु id;

		id = OV265X_ID(pid, ver);
		अगर (id != OV2659_ID) अणु
			dev_err(&client->dev,
				"Sensor detection failed (%04X, %d)\n",
				id, ret);
			ret = -ENODEV;
		पूर्ण अन्यथा अणु
			dev_info(&client->dev, "Found OV%04X sensor\n", id);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा ov2659_platक्रमm_data *
ov2659_get_pdata(काष्ठा i2c_client *client)
अणु
	काष्ठा ov2659_platक्रमm_data *pdata;
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु .bus_type = 0 पूर्ण;
	काष्ठा device_node *endpoपूर्णांक;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_OF) || !client->dev.of_node)
		वापस client->dev.platक्रमm_data;

	endpoपूर्णांक = of_graph_get_next_endpoपूर्णांक(client->dev.of_node, शून्य);
	अगर (!endpoपूर्णांक)
		वापस शून्य;

	ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(of_fwnode_handle(endpoपूर्णांक),
					       &bus_cfg);
	अगर (ret) अणु
		pdata = शून्य;
		जाओ करोne;
	पूर्ण

	pdata = devm_kzalloc(&client->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		जाओ करोne;

	अगर (!bus_cfg.nr_of_link_frequencies) अणु
		dev_err(&client->dev,
			"link-frequencies property not found or too many\n");
		pdata = शून्य;
		जाओ करोne;
	पूर्ण

	pdata->link_frequency = bus_cfg.link_frequencies[0];

करोne:
	v4l2_fwnode_endpoपूर्णांक_मुक्त(&bus_cfg);
	of_node_put(endpoपूर्णांक);
	वापस pdata;
पूर्ण

अटल पूर्णांक ov2659_probe(काष्ठा i2c_client *client)
अणु
	स्थिर काष्ठा ov2659_platक्रमm_data *pdata = ov2659_get_pdata(client);
	काष्ठा v4l2_subdev *sd;
	काष्ठा ov2659 *ov2659;
	काष्ठा clk *clk;
	पूर्णांक ret;

	अगर (!pdata) अणु
		dev_err(&client->dev, "platform data not specified\n");
		वापस -EINVAL;
	पूर्ण

	ov2659 = devm_kzalloc(&client->dev, माप(*ov2659), GFP_KERNEL);
	अगर (!ov2659)
		वापस -ENOMEM;

	ov2659->pdata = pdata;
	ov2659->client = client;

	clk = devm_clk_get(&client->dev, "xvclk");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ov2659->xvclk_frequency = clk_get_rate(clk);
	अगर (ov2659->xvclk_frequency < 6000000 ||
	    ov2659->xvclk_frequency > 27000000)
		वापस -EINVAL;

	/* Optional gpio करोn't fail अगर not present */
	ov2659->pwdn_gpio = devm_gpiod_get_optional(&client->dev, "powerdown",
						    GPIOD_OUT_LOW);
	अगर (IS_ERR(ov2659->pwdn_gpio))
		वापस PTR_ERR(ov2659->pwdn_gpio);

	/* Optional gpio करोn't fail अगर not present */
	ov2659->resetb_gpio = devm_gpiod_get_optional(&client->dev, "reset",
						      GPIOD_OUT_HIGH);
	अगर (IS_ERR(ov2659->resetb_gpio))
		वापस PTR_ERR(ov2659->resetb_gpio);

	v4l2_ctrl_handler_init(&ov2659->ctrls, 2);
	ov2659->link_frequency =
			v4l2_ctrl_new_std(&ov2659->ctrls, &ov2659_ctrl_ops,
					  V4L2_CID_PIXEL_RATE,
					  pdata->link_frequency / 2,
					  pdata->link_frequency, 1,
					  pdata->link_frequency);
	v4l2_ctrl_new_std_menu_items(&ov2659->ctrls, &ov2659_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(ov2659_test_pattern_menu) - 1,
				     0, 0, ov2659_test_pattern_menu);
	ov2659->sd.ctrl_handler = &ov2659->ctrls;

	अगर (ov2659->ctrls.error) अणु
		dev_err(&client->dev, "%s: control initialization error %d\n",
			__func__, ov2659->ctrls.error);
		वापस  ov2659->ctrls.error;
	पूर्ण

	sd = &ov2659->sd;
	client->flags |= I2C_CLIENT_SCCB;
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
	v4l2_i2c_subdev_init(sd, client, &ov2659_subdev_ops);

	sd->पूर्णांकernal_ops = &ov2659_subdev_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
		     V4L2_SUBDEV_FL_HAS_EVENTS;
#पूर्ण_अगर

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	ov2659->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sd->entity, 1, &ov2659->pad);
	अगर (ret < 0) अणु
		v4l2_ctrl_handler_मुक्त(&ov2659->ctrls);
		वापस ret;
	पूर्ण
#पूर्ण_अगर

	mutex_init(&ov2659->lock);

	ov2659_get_शेष_क्रमmat(&ov2659->क्रमmat);
	ov2659->frame_size = &ov2659_framesizes[2];
	ov2659->क्रमmat_ctrl_regs = ov2659_क्रमmats[0].क्रमmat_ctrl_regs;

	ov2659_घातer_on(&client->dev);

	ret = ov2659_detect(sd);
	अगर (ret < 0)
		जाओ error;

	/* Calculate the PLL रेजिस्टर value needed */
	ov2659_pll_calc_params(ov2659);

	ret = v4l2_async_रेजिस्टर_subdev(&ov2659->sd);
	अगर (ret)
		जाओ error;

	dev_info(&client->dev, "%s sensor driver registered !!\n", sd->name);

	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);
	pm_runसमय_idle(&client->dev);

	वापस 0;

error:
	v4l2_ctrl_handler_मुक्त(&ov2659->ctrls);
	ov2659_घातer_off(&client->dev);
	media_entity_cleanup(&sd->entity);
	mutex_destroy(&ov2659->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov2659_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov2659 *ov2659 = to_ov2659(sd);

	v4l2_ctrl_handler_मुक्त(&ov2659->ctrls);
	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	mutex_destroy(&ov2659->lock);

	pm_runसमय_disable(&client->dev);
	अगर (!pm_runसमय_status_suspended(&client->dev))
		ov2659_घातer_off(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ov2659_pm_ops = अणु
	SET_RUNTIME_PM_OPS(ov2659_घातer_off, ov2659_घातer_on, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id ov2659_id[] = अणु
	अणु "ov2659", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ov2659_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id ov2659_of_match[] = अणु
	अणु .compatible = "ovti,ov2659", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ov2659_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ov2659_i2c_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
		.pm	= &ov2659_pm_ops,
		.of_match_table = of_match_ptr(ov2659_of_match),
	पूर्ण,
	.probe_new	= ov2659_probe,
	.हटाओ		= ov2659_हटाओ,
	.id_table	= ov2659_id,
पूर्ण;

module_i2c_driver(ov2659_i2c_driver);

MODULE_AUTHOR("Benoit Parrot <bparrot@ti.com>");
MODULE_DESCRIPTION("OV2659 CMOS Image Sensor driver");
MODULE_LICENSE("GPL v2");
