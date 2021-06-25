<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम OmniVision OV2722 1080p HD camera sensor.
 *
 * Copyright (c) 2013 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#अगर_अघोषित __OV2722_H__
#घोषणा __OV2722_H__
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/spinlock.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-device.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश "../include/linux/atomisp_platform.h"

#घोषणा OV2722_POWER_UP_RETRY_NUM 5

/* Defines क्रम रेजिस्टर ग_लिखोs and रेजिस्टर array processing */
#घोषणा I2C_MSG_LENGTH		0x2
#घोषणा I2C_RETRY_COUNT		5

#घोषणा OV2722_FOCAL_LENGTH_NUM	278	/*2.78mm*/
#घोषणा OV2722_FOCAL_LENGTH_DEM	100
#घोषणा OV2722_F_NUMBER_DEFAULT_NUM	26
#घोषणा OV2722_F_NUMBER_DEM	10

#घोषणा MAX_FMTS		1

/*
 * focal length bits definition:
 * bits 31-16: numerator, bits 15-0: denominator
 */
#घोषणा OV2722_FOCAL_LENGTH_DEFAULT 0x1160064

/*
 * current f-number bits definition:
 * bits 31-16: numerator, bits 15-0: denominator
 */
#घोषणा OV2722_F_NUMBER_DEFAULT 0x1a000a

/*
 * f-number range bits definition:
 * bits 31-24: max f-number numerator
 * bits 23-16: max f-number denominator
 * bits 15-8: min f-number numerator
 * bits 7-0: min f-number denominator
 */
#घोषणा OV2722_F_NUMBER_RANGE 0x1a0a1a0a
#घोषणा OV2720_ID	0x2720
#घोषणा OV2722_ID	0x2722

#घोषणा OV2722_FINE_INTG_TIME_MIN 0
#घोषणा OV2722_FINE_INTG_TIME_MAX_MARGIN 0
#घोषणा OV2722_COARSE_INTG_TIME_MIN 1
#घोषणा OV2722_COARSE_INTG_TIME_MAX_MARGIN 4

/*
 * OV2722 System control रेजिस्टरs
 */
#घोषणा OV2722_SW_SLEEP				0x0100
#घोषणा OV2722_SW_RESET				0x0103
#घोषणा OV2722_SW_STREAM			0x0100

#घोषणा OV2722_SC_CMMN_CHIP_ID_H		0x300A
#घोषणा OV2722_SC_CMMN_CHIP_ID_L		0x300B
#घोषणा OV2722_SC_CMMN_SCCB_ID			0x300C
#घोषणा OV2722_SC_CMMN_SUB_ID			0x302A /* process, version*/

#घोषणा OV2722_SC_CMMN_PAD_OEN0			0x3000
#घोषणा OV2722_SC_CMMN_PAD_OEN1			0x3001
#घोषणा OV2722_SC_CMMN_PAD_OEN2			0x3002
#घोषणा OV2722_SC_CMMN_PAD_OUT0			0x3008
#घोषणा OV2722_SC_CMMN_PAD_OUT1			0x3009
#घोषणा OV2722_SC_CMMN_PAD_OUT2			0x300D
#घोषणा OV2722_SC_CMMN_PAD_SEL0			0x300E
#घोषणा OV2722_SC_CMMN_PAD_SEL1			0x300F
#घोषणा OV2722_SC_CMMN_PAD_SEL2			0x3010

#घोषणा OV2722_SC_CMMN_PAD_PK			0x3011
#घोषणा OV2722_SC_CMMN_A_PWC_PK_O_13		0x3013
#घोषणा OV2722_SC_CMMN_A_PWC_PK_O_14		0x3014

#घोषणा OV2722_SC_CMMN_CLKRST0			0x301A
#घोषणा OV2722_SC_CMMN_CLKRST1			0x301B
#घोषणा OV2722_SC_CMMN_CLKRST2			0x301C
#घोषणा OV2722_SC_CMMN_CLKRST3			0x301D
#घोषणा OV2722_SC_CMMN_CLKRST4			0x301E
#घोषणा OV2722_SC_CMMN_CLKRST5			0x3005
#घोषणा OV2722_SC_CMMN_PCLK_DIV_CTRL		0x3007
#घोषणा OV2722_SC_CMMN_CLOCK_SEL		0x3020
#घोषणा OV2722_SC_SOC_CLKRST5			0x3040

#घोषणा OV2722_SC_CMMN_PLL_CTRL0		0x3034
#घोषणा OV2722_SC_CMMN_PLL_CTRL1		0x3035
#घोषणा OV2722_SC_CMMN_PLL_CTRL2		0x3039
#घोषणा OV2722_SC_CMMN_PLL_CTRL3		0x3037
#घोषणा OV2722_SC_CMMN_PLL_MULTIPLIER		0x3036
#घोषणा OV2722_SC_CMMN_PLL_DEBUG_OPT		0x3038
#घोषणा OV2722_SC_CMMN_PLLS_CTRL0		0x303A
#घोषणा OV2722_SC_CMMN_PLLS_CTRL1		0x303B
#घोषणा OV2722_SC_CMMN_PLLS_CTRL2		0x303C
#घोषणा OV2722_SC_CMMN_PLLS_CTRL3		0x303D

#घोषणा OV2722_SC_CMMN_MIPI_PHY_16		0x3016
#घोषणा OV2722_SC_CMMN_MIPI_PHY_17		0x3017
#घोषणा OV2722_SC_CMMN_MIPI_SC_CTRL_18		0x3018
#घोषणा OV2722_SC_CMMN_MIPI_SC_CTRL_19		0x3019
#घोषणा OV2722_SC_CMMN_MIPI_SC_CTRL_21		0x3021
#घोषणा OV2722_SC_CMMN_MIPI_SC_CTRL_22		0x3022

#घोषणा OV2722_AEC_PK_EXPO_H			0x3500
#घोषणा OV2722_AEC_PK_EXPO_M			0x3501
#घोषणा OV2722_AEC_PK_EXPO_L			0x3502
#घोषणा OV2722_AEC_MANUAL_CTRL			0x3503
#घोषणा OV2722_AGC_ADJ_H			0x3508
#घोषणा OV2722_AGC_ADJ_L			0x3509
#घोषणा OV2722_VTS_DIFF_H			0x350c
#घोषणा OV2722_VTS_DIFF_L			0x350d
#घोषणा OV2722_GROUP_ACCESS			0x3208
#घोषणा OV2722_HTS_H				0x380c
#घोषणा OV2722_HTS_L				0x380d
#घोषणा OV2722_VTS_H				0x380e
#घोषणा OV2722_VTS_L				0x380f

#घोषणा OV2722_MWB_GAIN_R_H			0x5186
#घोषणा OV2722_MWB_GAIN_R_L			0x5187
#घोषणा OV2722_MWB_GAIN_G_H			0x5188
#घोषणा OV2722_MWB_GAIN_G_L			0x5189
#घोषणा OV2722_MWB_GAIN_B_H			0x518a
#घोषणा OV2722_MWB_GAIN_B_L			0x518b

#घोषणा OV2722_H_CROP_START_H			0x3800
#घोषणा OV2722_H_CROP_START_L			0x3801
#घोषणा OV2722_V_CROP_START_H			0x3802
#घोषणा OV2722_V_CROP_START_L			0x3803
#घोषणा OV2722_H_CROP_END_H			0x3804
#घोषणा OV2722_H_CROP_END_L			0x3805
#घोषणा OV2722_V_CROP_END_H			0x3806
#घोषणा OV2722_V_CROP_END_L			0x3807
#घोषणा OV2722_H_OUTSIZE_H			0x3808
#घोषणा OV2722_H_OUTSIZE_L			0x3809
#घोषणा OV2722_V_OUTSIZE_H			0x380a
#घोषणा OV2722_V_OUTSIZE_L			0x380b

#घोषणा OV2722_START_STREAMING			0x01
#घोषणा OV2722_STOP_STREAMING			0x00

काष्ठा regval_list अणु
	u16 reg_num;
	u8 value;
पूर्ण;

काष्ठा ov2722_resolution अणु
	u8 *desc;
	स्थिर काष्ठा ov2722_reg *regs;
	पूर्णांक res;
	पूर्णांक width;
	पूर्णांक height;
	पूर्णांक fps;
	पूर्णांक pix_clk_freq;
	u32 skip_frames;
	u16 pixels_per_line;
	u16 lines_per_frame;
	u8 bin_factor_x;
	u8 bin_factor_y;
	u8 bin_mode;
	bool used;
	पूर्णांक mipi_freq;
पूर्ण;

काष्ठा ov2722_क्रमmat अणु
	u8 *desc;
	u32 pixelक्रमmat;
	काष्ठा ov2722_reg *regs;
पूर्ण;

/*
 * ov2722 device काष्ठाure.
 */
काष्ठा ov2722_device अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	काष्ठा mutex input_lock;

	काष्ठा camera_sensor_platक्रमm_data *platक्रमm_data;
	पूर्णांक vt_pix_clk_freq_mhz;
	पूर्णांक fmt_idx;
	पूर्णांक run_mode;
	u16 pixels_per_line;
	u16 lines_per_frame;
	u8 res;
	u8 type;

	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl *link_freq;
पूर्ण;

क्रमागत ov2722_tok_type अणु
	OV2722_8BIT  = 0x0001,
	OV2722_16BIT = 0x0002,
	OV2722_32BIT = 0x0004,
	OV2722_TOK_TERM   = 0xf000,	/* terminating token क्रम reg list */
	OV2722_TOK_DELAY  = 0xfe00,	/* delay token क्रम reg list */
	OV2722_TOK_MASK = 0xfff0
पूर्ण;

/**
 * काष्ठा ov2722_reg - MI sensor  रेजिस्टर क्रमmat
 * @type: type of the रेजिस्टर
 * @reg: 16-bit offset to रेजिस्टर
 * @val: 8/16/32-bit रेजिस्टर value
 *
 * Define a काष्ठाure क्रम sensor रेजिस्टर initialization values
 */
काष्ठा ov2722_reg अणु
	क्रमागत ov2722_tok_type type;
	u16 reg;
	u32 val;	/* @set value क्रम पढ़ो/mod/ग_लिखो, @mask */
पूर्ण;

#घोषणा to_ov2722_sensor(x) container_of(x, काष्ठा ov2722_device, sd)

#घोषणा OV2722_MAX_WRITE_BUF_SIZE	30

काष्ठा ov2722_ग_लिखो_buffer अणु
	u16 addr;
	u8 data[OV2722_MAX_WRITE_BUF_SIZE];
पूर्ण;

काष्ठा ov2722_ग_लिखो_ctrl अणु
	पूर्णांक index;
	काष्ठा ov2722_ग_लिखो_buffer buffer;
पूर्ण;

/*
 * Register settings क्रम various resolution
 */
#अगर 0
अटल काष्ठा ov2722_reg स्थिर ov2722_QVGA_30fps[] = अणु
	अणुOV2722_8BIT, 0x3718, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3702, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x373a, 0x1cपूर्ण,
	अणुOV2722_8BIT, 0x3715, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3703, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x3705, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3730, 0x0eपूर्ण,
	अणुOV2722_8BIT, 0x3704, 0x1cपूर्ण,
	अणुOV2722_8BIT, 0x3f06, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x371c, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x371d, 0x46पूर्ण,
	अणुOV2722_8BIT, 0x371e, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x371f, 0x63पूर्ण,
	अणुOV2722_8BIT, 0x3708, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x3709, 0x12पूर्ण,
	अणुOV2722_8BIT, 0x3800, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3801, 0x42पूर्ण, /* H crop start: 322 */
	अणुOV2722_8BIT, 0x3802, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3803, 0x20पूर्ण, /* V crop start: 32 */
	अणुOV2722_8BIT, 0x3804, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3805, 0x95पूर्ण, /* H crop end:  1685 */
	अणुOV2722_8BIT, 0x3806, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3807, 0x27पूर्ण, /* V crop end:  1063 */
	अणुOV2722_8BIT, 0x3808, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3809, 0x50पूर्ण, /* H output size: 336 */
	अणुOV2722_8BIT, 0x380a, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x380b, 0x00पूर्ण, /* V output size: 256 */

	/* H blank timing */
	अणुOV2722_8BIT, 0x380c, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x380d, 0x00पूर्ण, /* H total size: 2048 */
	अणुOV2722_8BIT, 0x380e, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x380f, 0xa0पूर्ण, /* V total size: 1184 */
	अणुOV2722_8BIT, 0x3810, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3811, 0x04पूर्ण, /* H winकरोw offset: 5 */
	अणुOV2722_8BIT, 0x3812, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3813, 0x01पूर्ण, /* V winकरोw offset: 2 */
	अणुOV2722_8BIT, 0x3820, 0xc0पूर्ण,
	अणुOV2722_8BIT, 0x3821, 0x06पूर्ण, /* flip isp*/
	अणुOV2722_8BIT, 0x3814, 0x71पूर्ण,
	अणुOV2722_8BIT, 0x3815, 0x71पूर्ण,
	अणुOV2722_8BIT, 0x3612, 0x49पूर्ण,
	अणुOV2722_8BIT, 0x3618, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a08, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3a09, 0xc3पूर्ण,
	अणुOV2722_8BIT, 0x3a0a, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3a0b, 0x77पूर्ण,
	अणुOV2722_8BIT, 0x3a0d, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a0e, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x4520, 0x09पूर्ण,
	अणुOV2722_8BIT, 0x4837, 0x1bपूर्ण,
	अणुOV2722_8BIT, 0x3000, 0xffपूर्ण,
	अणुOV2722_8BIT, 0x3001, 0xffपूर्ण,
	अणुOV2722_8BIT, 0x3002, 0xf0पूर्ण,
	अणुOV2722_8BIT, 0x3600, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x3621, 0xc0पूर्ण,
	अणुOV2722_8BIT, 0x3632, 0x53पूर्ण, /* added क्रम घातer opt */
	अणुOV2722_8BIT, 0x3633, 0x63पूर्ण,
	अणुOV2722_8BIT, 0x3634, 0x24पूर्ण,
	अणुOV2722_8BIT, 0x3f01, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x5001, 0xc1पूर्ण, /* v_en, h_en, blc_en */
	अणुOV2722_8BIT, 0x3614, 0xf0पूर्ण,
	अणुOV2722_8BIT, 0x3630, 0x2dपूर्ण,
	अणुOV2722_8BIT, 0x370b, 0x62पूर्ण,
	अणुOV2722_8BIT, 0x3706, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x4000, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x4002, 0xc5पूर्ण,
	अणुOV2722_8BIT, 0x4005, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x404f, 0x84पूर्ण,
	अणुOV2722_8BIT, 0x4051, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5000, 0xffपूर्ण,
	अणुOV2722_8BIT, 0x3a18, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a19, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x4521, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5183, 0xb0पूर्ण, /* AWB red */
	अणुOV2722_8BIT, 0x5184, 0xb0पूर्ण, /* AWB green */
	अणुOV2722_8BIT, 0x5185, 0xb0पूर्ण, /* AWB blue */
	अणुOV2722_8BIT, 0x5180, 0x03पूर्ण, /* AWB manual mode */
	अणुOV2722_8BIT, 0x370c, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x4800, 0x24पूर्ण, /* clk lane gate enable */
	अणुOV2722_8BIT, 0x3035, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3036, 0x26पूर्ण,
	अणुOV2722_8BIT, 0x3037, 0xa1पूर्ण,
	अणुOV2722_8BIT, 0x303e, 0x19पूर्ण,
	अणुOV2722_8BIT, 0x3038, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3018, 0x04पूर्ण,

	/* Added क्रम घातer optimization */
	अणुOV2722_8BIT, 0x3000, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3001, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3002, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a0f, 0x40पूर्ण,
	अणुOV2722_8BIT, 0x3a10, 0x38पूर्ण,
	अणुOV2722_8BIT, 0x3a1b, 0x48पूर्ण,
	अणुOV2722_8BIT, 0x3a1e, 0x30पूर्ण,
	अणुOV2722_8BIT, 0x3a11, 0x90पूर्ण,
	अणुOV2722_8BIT, 0x3a1f, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3011, 0x22पूर्ण,
	अणुOV2722_8BIT, 0x3a00, 0x58पूर्ण,
	अणुOV2722_8BIT, 0x3503, 0x17पूर्ण,
	अणुOV2722_8BIT, 0x3500, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3501, 0x46पूर्ण,
	अणुOV2722_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3508, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3509, 0x10पूर्ण,
	अणुOV2722_TOK_TERM, 0, 0पूर्ण,

पूर्ण;

अटल काष्ठा ov2722_reg स्थिर ov2722_480P_30fps[] = अणु
	अणुOV2722_8BIT, 0x3718, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3702, 0x18पूर्ण,
	अणुOV2722_8BIT, 0x373a, 0x3cपूर्ण,
	अणुOV2722_8BIT, 0x3715, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3703, 0x1dपूर्ण,
	अणुOV2722_8BIT, 0x3705, 0x12पूर्ण,
	अणुOV2722_8BIT, 0x3730, 0x1fपूर्ण,
	अणुOV2722_8BIT, 0x3704, 0x3fपूर्ण,
	अणुOV2722_8BIT, 0x3f06, 0x1dपूर्ण,
	अणुOV2722_8BIT, 0x371c, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x371d, 0x83पूर्ण,
	अणुOV2722_8BIT, 0x371e, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x371f, 0xbdपूर्ण,
	अणुOV2722_8BIT, 0x3708, 0x63पूर्ण,
	अणुOV2722_8BIT, 0x3709, 0x52पूर्ण,
	अणुOV2722_8BIT, 0x3800, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3801, 0xf2पूर्ण, /* H crop start: 322 - 80 = 242*/
	अणुOV2722_8BIT, 0x3802, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3803, 0x20पूर्ण, /* V crop start:  32*/
	अणुOV2722_8BIT, 0x3804, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3805, 0xBBपूर्ण, /* H crop end:   1643 + 80 = 1723*/
	अणुOV2722_8BIT, 0x3806, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3807, 0x03पूर्ण, /* V crop end:   1027*/
	अणुOV2722_8BIT, 0x3808, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x3809, 0xE0पूर्ण, /* H output size: 656 +80 = 736*/
	अणुOV2722_8BIT, 0x380a, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x380b, 0xF0पूर्ण, /* V output size: 496 */

	/* H blank timing */
	अणुOV2722_8BIT, 0x380c, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x380d, 0x00पूर्ण, /* H total size: 2048 */
	अणुOV2722_8BIT, 0x380e, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x380f, 0xa0पूर्ण, /* V total size: 1184 */
	अणुOV2722_8BIT, 0x3810, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3811, 0x04पूर्ण, /* H winकरोw offset: 5 */
	अणुOV2722_8BIT, 0x3812, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3813, 0x01पूर्ण, /* V winकरोw offset: 2 */
	अणुOV2722_8BIT, 0x3820, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x3821, 0x06पूर्ण, /* flip isp*/
	अणुOV2722_8BIT, 0x3814, 0x31पूर्ण,
	अणुOV2722_8BIT, 0x3815, 0x31पूर्ण,
	अणुOV2722_8BIT, 0x3612, 0x4bपूर्ण,
	अणुOV2722_8BIT, 0x3618, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3a08, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x3a09, 0x67पूर्ण,
	अणुOV2722_8BIT, 0x3a0a, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x3a0b, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a0d, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a0e, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x4520, 0x0aपूर्ण,
	अणुOV2722_8BIT, 0x4837, 0x1bपूर्ण,
	अणुOV2722_8BIT, 0x3000, 0xffपूर्ण,
	अणुOV2722_8BIT, 0x3001, 0xffपूर्ण,
	अणुOV2722_8BIT, 0x3002, 0xf0पूर्ण,
	अणुOV2722_8BIT, 0x3600, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x3621, 0xc0पूर्ण,
	अणुOV2722_8BIT, 0x3632, 0x53पूर्ण, /* added क्रम घातer opt */
	अणुOV2722_8BIT, 0x3633, 0x63पूर्ण,
	अणुOV2722_8BIT, 0x3634, 0x24पूर्ण,
	अणुOV2722_8BIT, 0x3f01, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x5001, 0xc1पूर्ण, /* v_en, h_en, blc_en */
	अणुOV2722_8BIT, 0x3614, 0xf0पूर्ण,
	अणुOV2722_8BIT, 0x3630, 0x2dपूर्ण,
	अणुOV2722_8BIT, 0x370b, 0x62पूर्ण,
	अणुOV2722_8BIT, 0x3706, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x4000, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x4002, 0xc5पूर्ण,
	अणुOV2722_8BIT, 0x4005, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x404f, 0x84पूर्ण,
	अणुOV2722_8BIT, 0x4051, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5000, 0xffपूर्ण,
	अणुOV2722_8BIT, 0x3a18, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a19, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x4521, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5183, 0xb0पूर्ण, /* AWB red */
	अणुOV2722_8BIT, 0x5184, 0xb0पूर्ण, /* AWB green */
	अणुOV2722_8BIT, 0x5185, 0xb0पूर्ण, /* AWB blue */
	अणुOV2722_8BIT, 0x5180, 0x03पूर्ण, /* AWB manual mode */
	अणुOV2722_8BIT, 0x370c, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x4800, 0x24पूर्ण, /* clk lane gate enable */
	अणुOV2722_8BIT, 0x3035, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3036, 0x26पूर्ण,
	अणुOV2722_8BIT, 0x3037, 0xa1पूर्ण,
	अणुOV2722_8BIT, 0x303e, 0x19पूर्ण,
	अणुOV2722_8BIT, 0x3038, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3018, 0x04पूर्ण,

	/* Added क्रम घातer optimization */
	अणुOV2722_8BIT, 0x3000, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3001, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3002, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a0f, 0x40पूर्ण,
	अणुOV2722_8BIT, 0x3a10, 0x38पूर्ण,
	अणुOV2722_8BIT, 0x3a1b, 0x48पूर्ण,
	अणुOV2722_8BIT, 0x3a1e, 0x30पूर्ण,
	अणुOV2722_8BIT, 0x3a11, 0x90पूर्ण,
	अणुOV2722_8BIT, 0x3a1f, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3011, 0x22पूर्ण,
	अणुOV2722_8BIT, 0x3a00, 0x58पूर्ण,
	अणुOV2722_8BIT, 0x3503, 0x17पूर्ण,
	अणुOV2722_8BIT, 0x3500, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3501, 0x46पूर्ण,
	अणुOV2722_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3508, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3509, 0x10पूर्ण,
	अणुOV2722_TOK_TERM, 0, 0पूर्ण,
पूर्ण;

अटल काष्ठा ov2722_reg स्थिर ov2722_VGA_30fps[] = अणु
	अणुOV2722_8BIT, 0x3718, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3702, 0x18पूर्ण,
	अणुOV2722_8BIT, 0x373a, 0x3cपूर्ण,
	अणुOV2722_8BIT, 0x3715, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3703, 0x1dपूर्ण,
	अणुOV2722_8BIT, 0x3705, 0x12पूर्ण,
	अणुOV2722_8BIT, 0x3730, 0x1fपूर्ण,
	अणुOV2722_8BIT, 0x3704, 0x3fपूर्ण,
	अणुOV2722_8BIT, 0x3f06, 0x1dपूर्ण,
	अणुOV2722_8BIT, 0x371c, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x371d, 0x83पूर्ण,
	अणुOV2722_8BIT, 0x371e, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x371f, 0xbdपूर्ण,
	अणुOV2722_8BIT, 0x3708, 0x63पूर्ण,
	अणुOV2722_8BIT, 0x3709, 0x52पूर्ण,
	अणुOV2722_8BIT, 0x3800, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3801, 0x42पूर्ण, /* H crop start: 322 */
	अणुOV2722_8BIT, 0x3802, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3803, 0x20पूर्ण, /* V crop start:  32*/
	अणुOV2722_8BIT, 0x3804, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3805, 0x6Bपूर्ण, /* H crop end:   1643*/
	अणुOV2722_8BIT, 0x3806, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3807, 0x03पूर्ण, /* V crop end:   1027*/
	अणुOV2722_8BIT, 0x3808, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x3809, 0x90पूर्ण, /* H output size: 656 */
	अणुOV2722_8BIT, 0x380a, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x380b, 0xF0पूर्ण, /* V output size: 496 */

	/* H blank timing */
	अणुOV2722_8BIT, 0x380c, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x380d, 0x00पूर्ण, /* H total size: 2048 */
	अणुOV2722_8BIT, 0x380e, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x380f, 0xa0पूर्ण, /* V total size: 1184 */
	अणुOV2722_8BIT, 0x3810, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3811, 0x04पूर्ण, /* H winकरोw offset: 5 */
	अणुOV2722_8BIT, 0x3812, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3813, 0x01पूर्ण, /* V winकरोw offset: 2 */
	अणुOV2722_8BIT, 0x3820, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x3821, 0x06पूर्ण, /* flip isp*/
	अणुOV2722_8BIT, 0x3814, 0x31पूर्ण,
	अणुOV2722_8BIT, 0x3815, 0x31पूर्ण,
	अणुOV2722_8BIT, 0x3612, 0x4bपूर्ण,
	अणुOV2722_8BIT, 0x3618, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3a08, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x3a09, 0x67पूर्ण,
	अणुOV2722_8BIT, 0x3a0a, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x3a0b, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a0d, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a0e, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x4520, 0x0aपूर्ण,
	अणुOV2722_8BIT, 0x4837, 0x29पूर्ण,
	अणुOV2722_8BIT, 0x3000, 0xffपूर्ण,
	अणुOV2722_8BIT, 0x3001, 0xffपूर्ण,
	अणुOV2722_8BIT, 0x3002, 0xf0पूर्ण,
	अणुOV2722_8BIT, 0x3600, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x3621, 0xc0पूर्ण,
	अणुOV2722_8BIT, 0x3632, 0x53पूर्ण, /* added क्रम घातer opt */
	अणुOV2722_8BIT, 0x3633, 0x63पूर्ण,
	अणुOV2722_8BIT, 0x3634, 0x24पूर्ण,
	अणुOV2722_8BIT, 0x3f01, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x5001, 0xc1पूर्ण, /* v_en, h_en, blc_en */
	अणुOV2722_8BIT, 0x3614, 0xf0पूर्ण,
	अणुOV2722_8BIT, 0x3630, 0x2dपूर्ण,
	अणुOV2722_8BIT, 0x370b, 0x62पूर्ण,
	अणुOV2722_8BIT, 0x3706, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x4000, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x4002, 0xc5पूर्ण,
	अणुOV2722_8BIT, 0x4005, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x404f, 0x84पूर्ण,
	अणुOV2722_8BIT, 0x4051, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5000, 0xffपूर्ण,
	अणुOV2722_8BIT, 0x3a18, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a19, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x4521, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5183, 0xb0पूर्ण, /* AWB red */
	अणुOV2722_8BIT, 0x5184, 0xb0पूर्ण, /* AWB green */
	अणुOV2722_8BIT, 0x5185, 0xb0पूर्ण, /* AWB blue */
	अणुOV2722_8BIT, 0x5180, 0x03पूर्ण, /* AWB manual mode */
	अणुOV2722_8BIT, 0x370c, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x4800, 0x24पूर्ण, /* clk lane gate enable */
	अणुOV2722_8BIT, 0x3035, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3036, 0x26पूर्ण,
	अणुOV2722_8BIT, 0x3037, 0xa1पूर्ण,
	अणुOV2722_8BIT, 0x303e, 0x19पूर्ण,
	अणुOV2722_8BIT, 0x3038, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3018, 0x04पूर्ण,

	/* Added क्रम घातer optimization */
	अणुOV2722_8BIT, 0x3000, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3001, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3002, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a0f, 0x40पूर्ण,
	अणुOV2722_8BIT, 0x3a10, 0x38पूर्ण,
	अणुOV2722_8BIT, 0x3a1b, 0x48पूर्ण,
	अणुOV2722_8BIT, 0x3a1e, 0x30पूर्ण,
	अणुOV2722_8BIT, 0x3a11, 0x90पूर्ण,
	अणुOV2722_8BIT, 0x3a1f, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3011, 0x22पूर्ण,
	अणुOV2722_8BIT, 0x3a00, 0x58पूर्ण,
	अणुOV2722_8BIT, 0x3503, 0x17पूर्ण,
	अणुOV2722_8BIT, 0x3500, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3501, 0x46पूर्ण,
	अणुOV2722_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3508, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3509, 0x10पूर्ण,
	अणुOV2722_TOK_TERM, 0, 0पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा ov2722_reg स्थिर ov2722_1632_1092_30fps[] = अणु
	अणुOV2722_8BIT, 0x3021, 0x03पूर्ण, /* For stand रुको क्रम
				a whole frame complete.(vblank) */
	अणुOV2722_8BIT, 0x3718, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3702, 0x24पूर्ण,
	अणुOV2722_8BIT, 0x373a, 0x60पूर्ण,
	अणुOV2722_8BIT, 0x3715, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3703, 0x2eपूर्ण,
	अणुOV2722_8BIT, 0x3705, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3730, 0x30पूर्ण,
	अणुOV2722_8BIT, 0x3704, 0x62पूर्ण,
	अणुOV2722_8BIT, 0x3f06, 0x3aपूर्ण,
	अणुOV2722_8BIT, 0x371c, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x371d, 0xc4पूर्ण,
	अणुOV2722_8BIT, 0x371e, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x371f, 0x0dपूर्ण,
	अणुOV2722_8BIT, 0x3708, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x3709, 0x12पूर्ण,
	अणुOV2722_8BIT, 0x3800, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3801, 0x9Eपूर्ण, /* H crop start: 158 */
	अणुOV2722_8BIT, 0x3802, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3803, 0x01पूर्ण, /* V crop start: 1 */
	अणुOV2722_8BIT, 0x3804, 0x07पूर्ण,
	अणुOV2722_8BIT, 0x3805, 0x05पूर्ण, /* H crop end: 1797 */
	अणुOV2722_8BIT, 0x3806, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3807, 0x45पूर्ण, /* V crop end: 1093 */

	अणुOV2722_8BIT, 0x3808, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3809, 0x60पूर्ण, /* H output size: 1632 */
	अणुOV2722_8BIT, 0x380a, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x380b, 0x44पूर्ण, /* V output size: 1092 */
	अणुOV2722_8BIT, 0x380c, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x380d, 0xd4पूर्ण, /* H timing: 2260 */
	अणुOV2722_8BIT, 0x380e, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x380f, 0xdcपूर्ण, /* V timing: 1244 */
	अणुOV2722_8BIT, 0x3810, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3811, 0x03पूर्ण, /* H winकरोw offset: 3 */
	अणुOV2722_8BIT, 0x3812, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3813, 0x02पूर्ण, /* V winकरोw offset: 2 */
	अणुOV2722_8BIT, 0x3820, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x3821, 0x06पूर्ण, /*  mirror */
	अणुOV2722_8BIT, 0x3814, 0x11पूर्ण,
	अणुOV2722_8BIT, 0x3815, 0x11पूर्ण,
	अणुOV2722_8BIT, 0x3612, 0x0bपूर्ण,
	अणुOV2722_8BIT, 0x3618, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3a08, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3a09, 0x50पूर्ण,
	अणुOV2722_8BIT, 0x3a0a, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3a0b, 0x18पूर्ण,
	अणुOV2722_8BIT, 0x3a0d, 0x03पूर्ण,
	अणुOV2722_8BIT, 0x3a0e, 0x03पूर्ण,
	अणुOV2722_8BIT, 0x4520, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x4837, 0x1bपूर्ण,
	अणुOV2722_8BIT, 0x3600, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x3621, 0xc0पूर्ण,
	अणुOV2722_8BIT, 0x3632, 0xd2पूर्ण, /* added क्रम घातer opt */
	अणुOV2722_8BIT, 0x3633, 0x23पूर्ण,
	अणुOV2722_8BIT, 0x3634, 0x54पूर्ण,
	अणुOV2722_8BIT, 0x3f01, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x5001, 0xc1पूर्ण,
	अणुOV2722_8BIT, 0x3614, 0xf0पूर्ण,
	अणुOV2722_8BIT, 0x3630, 0x2dपूर्ण,
	अणुOV2722_8BIT, 0x370b, 0x62पूर्ण,
	अणुOV2722_8BIT, 0x3706, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x4000, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x4002, 0xc5पूर्ण,
	अणुOV2722_8BIT, 0x4005, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x404f, 0x84पूर्ण,
	अणुOV2722_8BIT, 0x4051, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5000, 0xcfपूर्ण, /* manual 3a */
	अणुOV2722_8BIT, 0x301d, 0xf0पूर्ण, /* enable group hold */
	अणुOV2722_8BIT, 0x3a18, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a19, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x4521, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5183, 0xb0पूर्ण,
	अणुOV2722_8BIT, 0x5184, 0xb0पूर्ण,
	अणुOV2722_8BIT, 0x5185, 0xb0पूर्ण,
	अणुOV2722_8BIT, 0x370c, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x3035, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3036, 0x2cपूर्ण, /* 422.4 MHz */
	अणुOV2722_8BIT, 0x3037, 0xa1पूर्ण,
	अणुOV2722_8BIT, 0x303e, 0x19पूर्ण,
	अणुOV2722_8BIT, 0x3038, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3018, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3000, 0x00पूर्ण, /* added क्रम घातer optimization */
	अणुOV2722_8BIT, 0x3001, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3002, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a0f, 0x40पूर्ण,
	अणुOV2722_8BIT, 0x3a10, 0x38पूर्ण,
	अणुOV2722_8BIT, 0x3a1b, 0x48पूर्ण,
	अणुOV2722_8BIT, 0x3a1e, 0x30पूर्ण,
	अणुOV2722_8BIT, 0x3a11, 0x90पूर्ण,
	अणुOV2722_8BIT, 0x3a1f, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3503, 0x17पूर्ण, /* manual 3a */
	अणुOV2722_8BIT, 0x3500, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3501, 0x3Fपूर्ण,
	अणुOV2722_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3508, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3509, 0x00पूर्ण,
	अणुOV2722_TOK_TERM, 0, 0पूर्ण
पूर्ण;

अटल काष्ठा ov2722_reg स्थिर ov2722_1452_1092_30fps[] = अणु
	अणुOV2722_8BIT, 0x3021, 0x03पूर्ण, /* For stand रुको क्रम
				a whole frame complete.(vblank) */
	अणुOV2722_8BIT, 0x3718, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3702, 0x24पूर्ण,
	अणुOV2722_8BIT, 0x373a, 0x60पूर्ण,
	अणुOV2722_8BIT, 0x3715, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3703, 0x2eपूर्ण,
	अणुOV2722_8BIT, 0x3705, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3730, 0x30पूर्ण,
	अणुOV2722_8BIT, 0x3704, 0x62पूर्ण,
	अणुOV2722_8BIT, 0x3f06, 0x3aपूर्ण,
	अणुOV2722_8BIT, 0x371c, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x371d, 0xc4पूर्ण,
	अणुOV2722_8BIT, 0x371e, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x371f, 0x0dपूर्ण,
	अणुOV2722_8BIT, 0x3708, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x3709, 0x12पूर्ण,
	अणुOV2722_8BIT, 0x3800, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3801, 0xF8पूर्ण, /* H crop start: 248 */
	अणुOV2722_8BIT, 0x3802, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3803, 0x01पूर्ण, /* V crop start: 1 */
	अणुOV2722_8BIT, 0x3804, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3805, 0xabपूर्ण, /* H crop end: 1707 */
	अणुOV2722_8BIT, 0x3806, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3807, 0x45पूर्ण, /* V crop end: 1093 */
	अणुOV2722_8BIT, 0x3808, 0x05पूर्ण,
	अणुOV2722_8BIT, 0x3809, 0xacपूर्ण, /* H output size: 1452 */
	अणुOV2722_8BIT, 0x380a, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x380b, 0x44पूर्ण, /* V output size: 1092 */
	अणुOV2722_8BIT, 0x380c, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x380d, 0xd4पूर्ण, /* H timing: 2260 */
	अणुOV2722_8BIT, 0x380e, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x380f, 0xdcपूर्ण, /* V timing: 1244 */
	अणुOV2722_8BIT, 0x3810, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3811, 0x03पूर्ण, /* H winकरोw offset: 3 */
	अणुOV2722_8BIT, 0x3812, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3813, 0x02पूर्ण, /* V winकरोw offset: 2 */
	अणुOV2722_8BIT, 0x3820, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x3821, 0x06पूर्ण, /*  mirror */
	अणुOV2722_8BIT, 0x3814, 0x11पूर्ण,
	अणुOV2722_8BIT, 0x3815, 0x11पूर्ण,
	अणुOV2722_8BIT, 0x3612, 0x0bपूर्ण,
	अणुOV2722_8BIT, 0x3618, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3a08, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3a09, 0x50पूर्ण,
	अणुOV2722_8BIT, 0x3a0a, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3a0b, 0x18पूर्ण,
	अणुOV2722_8BIT, 0x3a0d, 0x03पूर्ण,
	अणुOV2722_8BIT, 0x3a0e, 0x03पूर्ण,
	अणुOV2722_8BIT, 0x4520, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x4837, 0x1bपूर्ण,
	अणुOV2722_8BIT, 0x3600, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x3621, 0xc0पूर्ण,
	अणुOV2722_8BIT, 0x3632, 0xd2पूर्ण, /* added क्रम घातer opt */
	अणुOV2722_8BIT, 0x3633, 0x23पूर्ण,
	अणुOV2722_8BIT, 0x3634, 0x54पूर्ण,
	अणुOV2722_8BIT, 0x3f01, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x5001, 0xc1पूर्ण,
	अणुOV2722_8BIT, 0x3614, 0xf0पूर्ण,
	अणुOV2722_8BIT, 0x3630, 0x2dपूर्ण,
	अणुOV2722_8BIT, 0x370b, 0x62पूर्ण,
	अणुOV2722_8BIT, 0x3706, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x4000, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x4002, 0xc5पूर्ण,
	अणुOV2722_8BIT, 0x4005, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x404f, 0x84पूर्ण,
	अणुOV2722_8BIT, 0x4051, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5000, 0xcfपूर्ण, /* manual 3a */
	अणुOV2722_8BIT, 0x301d, 0xf0पूर्ण, /* enable group hold */
	अणुOV2722_8BIT, 0x3a18, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a19, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x4521, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5183, 0xb0पूर्ण,
	अणुOV2722_8BIT, 0x5184, 0xb0पूर्ण,
	अणुOV2722_8BIT, 0x5185, 0xb0पूर्ण,
	अणुOV2722_8BIT, 0x370c, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x3035, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3036, 0x2cपूर्ण, /* 422.4 MHz */
	अणुOV2722_8BIT, 0x3037, 0xa1पूर्ण,
	अणुOV2722_8BIT, 0x303e, 0x19पूर्ण,
	अणुOV2722_8BIT, 0x3038, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3018, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3000, 0x00पूर्ण, /* added क्रम घातer optimization */
	अणुOV2722_8BIT, 0x3001, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3002, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a0f, 0x40पूर्ण,
	अणुOV2722_8BIT, 0x3a10, 0x38पूर्ण,
	अणुOV2722_8BIT, 0x3a1b, 0x48पूर्ण,
	अणुOV2722_8BIT, 0x3a1e, 0x30पूर्ण,
	अणुOV2722_8BIT, 0x3a11, 0x90पूर्ण,
	अणुOV2722_8BIT, 0x3a1f, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3503, 0x17पूर्ण, /* manual 3a */
	अणुOV2722_8BIT, 0x3500, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3501, 0x3Fपूर्ण,
	अणुOV2722_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3508, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3509, 0x00पूर्ण,
	अणुOV2722_TOK_TERM, 0, 0पूर्ण
पूर्ण;

#अगर 0
अटल काष्ठा ov2722_reg स्थिर ov2722_1M3_30fps[] = अणु
	अणुOV2722_8BIT, 0x3718, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3702, 0x24पूर्ण,
	अणुOV2722_8BIT, 0x373a, 0x60पूर्ण,
	अणुOV2722_8BIT, 0x3715, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3703, 0x2eपूर्ण,
	अणुOV2722_8BIT, 0x3705, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3730, 0x30पूर्ण,
	अणुOV2722_8BIT, 0x3704, 0x62पूर्ण,
	अणुOV2722_8BIT, 0x3f06, 0x3aपूर्ण,
	अणुOV2722_8BIT, 0x371c, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x371d, 0xc4पूर्ण,
	अणुOV2722_8BIT, 0x371e, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x371f, 0x0dपूर्ण,
	अणुOV2722_8BIT, 0x3708, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x3709, 0x12पूर्ण,
	अणुOV2722_8BIT, 0x3800, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3801, 0x4aपूर्ण,	/* H crop start: 330 */
	अणुOV2722_8BIT, 0x3802, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3803, 0x03पूर्ण,	/* V crop start: 3 */
	अणुOV2722_8BIT, 0x3804, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3805, 0xe1पूर्ण,	/* H crop end:  1761 */
	अणुOV2722_8BIT, 0x3806, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3807, 0x47पूर्ण,	/* V crop end:  1095 */
	अणुOV2722_8BIT, 0x3808, 0x05पूर्ण,
	अणुOV2722_8BIT, 0x3809, 0x88पूर्ण,	/* H output size: 1416 */
	अणुOV2722_8BIT, 0x380a, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x380b, 0x0aपूर्ण,	/* V output size: 1034 */

	/* H blank timing */
	अणुOV2722_8BIT, 0x380c, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x380d, 0x00पूर्ण,	/* H total size: 2048 */
	अणुOV2722_8BIT, 0x380e, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x380f, 0xa0पूर्ण,	/* V total size: 1184 */
	अणुOV2722_8BIT, 0x3810, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3811, 0x05पूर्ण,	/* H winकरोw offset: 5 */
	अणुOV2722_8BIT, 0x3812, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3813, 0x02पूर्ण,	/* V winकरोw offset: 2 */
	अणुOV2722_8BIT, 0x3820, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x3821, 0x06पूर्ण,	/* flip isp */
	अणुOV2722_8BIT, 0x3814, 0x11पूर्ण,
	अणुOV2722_8BIT, 0x3815, 0x11पूर्ण,
	अणुOV2722_8BIT, 0x3612, 0x0bपूर्ण,
	अणुOV2722_8BIT, 0x3618, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3a08, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3a09, 0x50पूर्ण,
	अणुOV2722_8BIT, 0x3a0a, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3a0b, 0x18पूर्ण,
	अणुOV2722_8BIT, 0x3a0d, 0x03पूर्ण,
	अणुOV2722_8BIT, 0x3a0e, 0x03पूर्ण,
	अणुOV2722_8BIT, 0x4520, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x4837, 0x1bपूर्ण,
	अणुOV2722_8BIT, 0x3000, 0xffपूर्ण,
	अणुOV2722_8BIT, 0x3001, 0xffपूर्ण,
	अणुOV2722_8BIT, 0x3002, 0xf0पूर्ण,
	अणुOV2722_8BIT, 0x3600, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x3621, 0xc0पूर्ण,
	अणुOV2722_8BIT, 0x3632, 0xd2पूर्ण,	/* added क्रम घातer opt */
	अणुOV2722_8BIT, 0x3633, 0x23पूर्ण,
	अणुOV2722_8BIT, 0x3634, 0x54पूर्ण,
	अणुOV2722_8BIT, 0x3f01, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x5001, 0xc1पूर्ण,	/* v_en, h_en, blc_en */
	अणुOV2722_8BIT, 0x3614, 0xf0पूर्ण,
	अणुOV2722_8BIT, 0x3630, 0x2dपूर्ण,
	अणुOV2722_8BIT, 0x370b, 0x62पूर्ण,
	अणुOV2722_8BIT, 0x3706, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x4000, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x4002, 0xc5पूर्ण,
	अणुOV2722_8BIT, 0x4005, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x404f, 0x84पूर्ण,
	अणुOV2722_8BIT, 0x4051, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5000, 0xcfपूर्ण,
	अणुOV2722_8BIT, 0x3a18, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a19, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x4521, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5183, 0xb0पूर्ण,	/* AWB red */
	अणुOV2722_8BIT, 0x5184, 0xb0पूर्ण,	/* AWB green */
	अणुOV2722_8BIT, 0x5185, 0xb0पूर्ण,	/* AWB blue */
	अणुOV2722_8BIT, 0x5180, 0x03पूर्ण,	/* AWB manual mode */
	अणुOV2722_8BIT, 0x370c, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x4800, 0x24पूर्ण,	/* clk lane gate enable */
	अणुOV2722_8BIT, 0x3035, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3036, 0x26पूर्ण,
	अणुOV2722_8BIT, 0x3037, 0xa1पूर्ण,
	अणुOV2722_8BIT, 0x303e, 0x19पूर्ण,
	अणुOV2722_8BIT, 0x3038, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3018, 0x04पूर्ण,

	/* Added क्रम घातer optimization */
	अणुOV2722_8BIT, 0x3000, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3001, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3002, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a0f, 0x40पूर्ण,
	अणुOV2722_8BIT, 0x3a10, 0x38पूर्ण,
	अणुOV2722_8BIT, 0x3a1b, 0x48पूर्ण,
	अणुOV2722_8BIT, 0x3a1e, 0x30पूर्ण,
	अणुOV2722_8BIT, 0x3a11, 0x90पूर्ण,
	अणुOV2722_8BIT, 0x3a1f, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3503, 0x17पूर्ण,
	अणुOV2722_8BIT, 0x3500, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3501, 0x46पूर्ण,
	अणुOV2722_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3508, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3509, 0x10पूर्ण,
	अणुOV2722_TOK_TERM, 0, 0पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा ov2722_reg स्थिर ov2722_1080p_30fps[] = अणु
	अणुOV2722_8BIT, 0x3021, 0x03पूर्ण, /* For stand रुको क्रम a whole
					frame complete.(vblank) */
	अणुOV2722_8BIT, 0x3718, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3702, 0x24पूर्ण,
	अणुOV2722_8BIT, 0x373a, 0x60पूर्ण,
	अणुOV2722_8BIT, 0x3715, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3703, 0x2eपूर्ण,
	अणुOV2722_8BIT, 0x3705, 0x2bपूर्ण,
	अणुOV2722_8BIT, 0x3730, 0x30पूर्ण,
	अणुOV2722_8BIT, 0x3704, 0x62पूर्ण,
	अणुOV2722_8BIT, 0x3f06, 0x3aपूर्ण,
	अणुOV2722_8BIT, 0x371c, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x371d, 0xc4पूर्ण,
	अणुOV2722_8BIT, 0x371e, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x371f, 0x28पूर्ण,
	अणुOV2722_8BIT, 0x3708, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x3709, 0x12पूर्ण,
	अणुOV2722_8BIT, 0x3800, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3801, 0x08पूर्ण, /* H crop start: 8 */
	अणुOV2722_8BIT, 0x3802, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3803, 0x01पूर्ण, /* V crop start: 1 */
	अणुOV2722_8BIT, 0x3804, 0x07पूर्ण,
	अणुOV2722_8BIT, 0x3805, 0x9bपूर्ण, /* H crop end: 1947 */
	अणुOV2722_8BIT, 0x3806, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3807, 0x45पूर्ण, /* V crop end: 1093 */
	अणुOV2722_8BIT, 0x3808, 0x07पूर्ण,
	अणुOV2722_8BIT, 0x3809, 0x8cपूर्ण, /* H output size: 1932 */
	अणुOV2722_8BIT, 0x380a, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x380b, 0x44पूर्ण, /* V output size: 1092 */
	अणुOV2722_8BIT, 0x380c, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x380d, 0x14पूर्ण, /* H timing: 2068 */
	अणुOV2722_8BIT, 0x380e, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x380f, 0x5aपूर्ण, /* V timing: 1114 */
	अणुOV2722_8BIT, 0x3810, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3811, 0x03पूर्ण, /* H winकरोw offset: 3 */
	अणुOV2722_8BIT, 0x3812, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3813, 0x02पूर्ण, /* V winकरोw offset: 2 */
	अणुOV2722_8BIT, 0x3820, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x3821, 0x06पूर्ण, /*  mirror */
	अणुOV2722_8BIT, 0x3814, 0x11पूर्ण,
	अणुOV2722_8BIT, 0x3815, 0x11पूर्ण,
	अणुOV2722_8BIT, 0x3612, 0x4bपूर्ण,
	अणुOV2722_8BIT, 0x3618, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3a08, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3a09, 0x50पूर्ण,
	अणुOV2722_8BIT, 0x3a0a, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3a0b, 0x18पूर्ण,
	अणुOV2722_8BIT, 0x3a0d, 0x03पूर्ण,
	अणुOV2722_8BIT, 0x3a0e, 0x03पूर्ण,
	अणुOV2722_8BIT, 0x4520, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x4837, 0x1bपूर्ण,
	अणुOV2722_8BIT, 0x3000, 0xffपूर्ण,
	अणुOV2722_8BIT, 0x3001, 0xffपूर्ण,
	अणुOV2722_8BIT, 0x3002, 0xf0पूर्ण,
	अणुOV2722_8BIT, 0x3600, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x3621, 0xc0पूर्ण,
	अणुOV2722_8BIT, 0x3632, 0x53पूर्ण, /* added क्रम घातer opt */
	अणुOV2722_8BIT, 0x3633, 0x63पूर्ण,
	अणुOV2722_8BIT, 0x3634, 0x24पूर्ण,
	अणुOV2722_8BIT, 0x3f01, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x5001, 0xc1पूर्ण,
	अणुOV2722_8BIT, 0x3614, 0xf0पूर्ण,
	अणुOV2722_8BIT, 0x3630, 0x2dपूर्ण,
	अणुOV2722_8BIT, 0x370b, 0x62पूर्ण,
	अणुOV2722_8BIT, 0x3706, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x4000, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x4002, 0xc5पूर्ण,
	अणुOV2722_8BIT, 0x4005, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x404f, 0x84पूर्ण,
	अणुOV2722_8BIT, 0x4051, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5000, 0xcdपूर्ण, /* manual 3a */
	अणुOV2722_8BIT, 0x301d, 0xf0पूर्ण, /* enable group hold */
	अणुOV2722_8BIT, 0x3a18, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a19, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x3503, 0x17पूर्ण,
	अणुOV2722_8BIT, 0x4521, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5183, 0xb0पूर्ण,
	अणुOV2722_8BIT, 0x5184, 0xb0पूर्ण,
	अणुOV2722_8BIT, 0x5185, 0xb0पूर्ण,
	अणुOV2722_8BIT, 0x370c, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x3035, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3036, 0x24पूर्ण, /* 345.6 MHz */
	अणुOV2722_8BIT, 0x3037, 0xa1पूर्ण,
	अणुOV2722_8BIT, 0x303e, 0x19पूर्ण,
	अणुOV2722_8BIT, 0x3038, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3018, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3000, 0x00पूर्ण, /* added क्रम घातer optimization */
	अणुOV2722_8BIT, 0x3001, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3002, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a0f, 0x40पूर्ण,
	अणुOV2722_8BIT, 0x3a10, 0x38पूर्ण,
	अणुOV2722_8BIT, 0x3a1b, 0x48पूर्ण,
	अणुOV2722_8BIT, 0x3a1e, 0x30पूर्ण,
	अणुOV2722_8BIT, 0x3a11, 0x90पूर्ण,
	अणुOV2722_8BIT, 0x3a1f, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3011, 0x22पूर्ण,
	अणुOV2722_8BIT, 0x3500, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3501, 0x3Fपूर्ण,
	अणुOV2722_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3508, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3509, 0x00पूर्ण,
	अणुOV2722_TOK_TERM, 0, 0पूर्ण
पूर्ण;

#अगर 0 /* Currently unused */
अटल काष्ठा ov2722_reg स्थिर ov2722_720p_30fps[] = अणु
	अणुOV2722_8BIT, 0x3021, 0x03पूर्ण,
	अणुOV2722_8BIT, 0x3718, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3702, 0x24पूर्ण,
	अणुOV2722_8BIT, 0x373a, 0x60पूर्ण,
	अणुOV2722_8BIT, 0x3715, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3703, 0x2eपूर्ण,
	अणुOV2722_8BIT, 0x3705, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3730, 0x30पूर्ण,
	अणुOV2722_8BIT, 0x3704, 0x62पूर्ण,
	अणुOV2722_8BIT, 0x3f06, 0x3aपूर्ण,
	अणुOV2722_8BIT, 0x371c, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x371d, 0xc4पूर्ण,
	अणुOV2722_8BIT, 0x371e, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x371f, 0x0dपूर्ण,
	अणुOV2722_8BIT, 0x3708, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x3709, 0x12पूर्ण,
	अणुOV2722_8BIT, 0x3800, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3801, 0x40पूर्ण, /* H crop start: 320 */
	अणुOV2722_8BIT, 0x3802, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3803, 0xb1पूर्ण, /* V crop start: 177 */
	अणुOV2722_8BIT, 0x3804, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3805, 0x55पूर्ण, /* H crop end: 1621 */
	अणुOV2722_8BIT, 0x3806, 0x03पूर्ण,
	अणुOV2722_8BIT, 0x3807, 0x95पूर्ण, /* V crop end: 918 */
	अणुOV2722_8BIT, 0x3808, 0x05पूर्ण,
	अणुOV2722_8BIT, 0x3809, 0x10पूर्ण, /* H output size: 0x0788==1928 */
	अणुOV2722_8BIT, 0x380a, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x380b, 0xe0पूर्ण, /* output size: 0x02DE==734 */
	अणुOV2722_8BIT, 0x380c, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x380d, 0x00पूर्ण, /* H timing: 2048 */
	अणुOV2722_8BIT, 0x380e, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x380f, 0xa3पूर्ण, /* V timing: 1187 */
	अणुOV2722_8BIT, 0x3810, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3811, 0x03पूर्ण, /* H winकरोw offset: 3 */
	अणुOV2722_8BIT, 0x3812, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3813, 0x02पूर्ण, /* V winकरोw offset: 2 */
	अणुOV2722_8BIT, 0x3820, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x3821, 0x06पूर्ण, /* mirror */
	अणुOV2722_8BIT, 0x3814, 0x11पूर्ण,
	अणुOV2722_8BIT, 0x3815, 0x11पूर्ण,
	अणुOV2722_8BIT, 0x3612, 0x0bपूर्ण,
	अणुOV2722_8BIT, 0x3618, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3a08, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3a09, 0x50पूर्ण,
	अणुOV2722_8BIT, 0x3a0a, 0x01पूर्ण,
	अणुOV2722_8BIT, 0x3a0b, 0x18पूर्ण,
	अणुOV2722_8BIT, 0x3a0d, 0x03पूर्ण,
	अणुOV2722_8BIT, 0x3a0e, 0x03पूर्ण,
	अणुOV2722_8BIT, 0x4520, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x4837, 0x1bपूर्ण,
	अणुOV2722_8BIT, 0x3600, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x3621, 0xc0पूर्ण,
	अणुOV2722_8BIT, 0x3632, 0xd2पूर्ण, /* added क्रम घातer opt */
	अणुOV2722_8BIT, 0x3633, 0x23पूर्ण,
	अणुOV2722_8BIT, 0x3634, 0x54पूर्ण,
	अणुOV2722_8BIT, 0x3f01, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x5001, 0xc1पूर्ण,
	अणुOV2722_8BIT, 0x3614, 0xf0पूर्ण,
	अणुOV2722_8BIT, 0x3630, 0x2dपूर्ण,
	अणुOV2722_8BIT, 0x370b, 0x62पूर्ण,
	अणुOV2722_8BIT, 0x3706, 0x61पूर्ण,
	अणुOV2722_8BIT, 0x4000, 0x02पूर्ण,
	अणुOV2722_8BIT, 0x4002, 0xc5पूर्ण,
	अणुOV2722_8BIT, 0x4005, 0x08पूर्ण,
	अणुOV2722_8BIT, 0x404f, 0x84पूर्ण,
	अणुOV2722_8BIT, 0x4051, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5000, 0xcfपूर्ण, /* manual 3a */
	अणुOV2722_8BIT, 0x301d, 0xf0पूर्ण, /* enable group hold */
	अणुOV2722_8BIT, 0x3a18, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a19, 0x80पूर्ण,
	अणुOV2722_8BIT, 0x4521, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x5183, 0xb0पूर्ण,
	अणुOV2722_8BIT, 0x5184, 0xb0पूर्ण,
	अणुOV2722_8BIT, 0x5185, 0xb0पूर्ण,
	अणुOV2722_8BIT, 0x370c, 0x0cपूर्ण,
	अणुOV2722_8BIT, 0x3035, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3036, 0x26पूर्ण, /* अणु0x3036, 0x2cपूर्ण, //422.4 MHz */
	अणुOV2722_8BIT, 0x3037, 0xa1पूर्ण,
	अणुOV2722_8BIT, 0x303e, 0x19पूर्ण,
	अणुOV2722_8BIT, 0x3038, 0x06पूर्ण,
	अणुOV2722_8BIT, 0x3018, 0x04पूर्ण,
	अणुOV2722_8BIT, 0x3000, 0x00पूर्ण, /* added क्रम घातer optimization */
	अणुOV2722_8BIT, 0x3001, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3002, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3a0f, 0x40पूर्ण,
	अणुOV2722_8BIT, 0x3a10, 0x38पूर्ण,
	अणुOV2722_8BIT, 0x3a1b, 0x48पूर्ण,
	अणुOV2722_8BIT, 0x3a1e, 0x30पूर्ण,
	अणुOV2722_8BIT, 0x3a11, 0x90पूर्ण,
	अणुOV2722_8BIT, 0x3a1f, 0x10पूर्ण,
	अणुOV2722_8BIT, 0x3503, 0x17पूर्ण, /* manual 3a */
	अणुOV2722_8BIT, 0x3500, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3501, 0x3Fपूर्ण,
	अणुOV2722_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3508, 0x00पूर्ण,
	अणुOV2722_8BIT, 0x3509, 0x00पूर्ण,
	अणुOV2722_TOK_TERM, 0, 0पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा ov2722_resolution ov2722_res_preview[] = अणु
	अणु
		.desc = "ov2722_1632_1092_30fps",
		.width = 1632,
		.height = 1092,
		.fps = 30,
		.pix_clk_freq = 85,
		.used = 0,
		.pixels_per_line = 2260,
		.lines_per_frame = 1244,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = ov2722_1632_1092_30fps,
		.mipi_freq = 422400,
	पूर्ण,
	अणु
		.desc = "ov2722_1452_1092_30fps",
		.width = 1452,
		.height = 1092,
		.fps = 30,
		.pix_clk_freq = 85,
		.used = 0,
		.pixels_per_line = 2260,
		.lines_per_frame = 1244,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = ov2722_1452_1092_30fps,
		.mipi_freq = 422400,
	पूर्ण,
	अणु
		.desc = "ov2722_1080P_30fps",
		.width = 1932,
		.height = 1092,
		.pix_clk_freq = 69,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2068,
		.lines_per_frame = 1114,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = ov2722_1080p_30fps,
		.mipi_freq = 345600,
	पूर्ण,
पूर्ण;

#घोषणा N_RES_PREVIEW (ARRAY_SIZE(ov2722_res_preview))

/*
 * Disable non-preview configurations until the configuration selection is
 * improved.
 */
#अगर 0
काष्ठा ov2722_resolution ov2722_res_still[] = अणु
	अणु
		.desc = "ov2722_480P_30fps",
		.width = 1632,
		.height = 1092,
		.fps = 30,
		.pix_clk_freq = 85,
		.used = 0,
		.pixels_per_line = 2260,
		.lines_per_frame = 1244,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = ov2722_1632_1092_30fps,
		.mipi_freq = 422400,
	पूर्ण,
	अणु
		.desc = "ov2722_1452_1092_30fps",
		.width = 1452,
		.height = 1092,
		.fps = 30,
		.pix_clk_freq = 85,
		.used = 0,
		.pixels_per_line = 2260,
		.lines_per_frame = 1244,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = ov2722_1452_1092_30fps,
		.mipi_freq = 422400,
	पूर्ण,
	अणु
		.desc = "ov2722_1080P_30fps",
		.width = 1932,
		.height = 1092,
		.pix_clk_freq = 69,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2068,
		.lines_per_frame = 1114,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = ov2722_1080p_30fps,
		.mipi_freq = 345600,
	पूर्ण,
पूर्ण;

#घोषणा N_RES_STILL (ARRAY_SIZE(ov2722_res_still))

काष्ठा ov2722_resolution ov2722_res_video[] = अणु
	अणु
		.desc = "ov2722_QVGA_30fps",
		.width = 336,
		.height = 256,
		.fps = 30,
		.pix_clk_freq = 73,
		.used = 0,
		.pixels_per_line = 2048,
		.lines_per_frame = 1184,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = ov2722_QVGA_30fps,
		.mipi_freq = 364800,
	पूर्ण,
	अणु
		.desc = "ov2722_480P_30fps",
		.width = 736,
		.height = 496,
		.fps = 30,
		.pix_clk_freq = 73,
		.used = 0,
		.pixels_per_line = 2048,
		.lines_per_frame = 1184,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = ov2722_480P_30fps,
	पूर्ण,
	अणु
		.desc = "ov2722_1080P_30fps",
		.width = 1932,
		.height = 1092,
		.pix_clk_freq = 69,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2068,
		.lines_per_frame = 1114,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = ov2722_1080p_30fps,
		.mipi_freq = 345600,
	पूर्ण,
पूर्ण;

#घोषणा N_RES_VIDEO (ARRAY_SIZE(ov2722_res_video))
#पूर्ण_अगर

अटल काष्ठा ov2722_resolution *ov2722_res = ov2722_res_preview;
अटल अचिन्हित दीर्घ N_RES = N_RES_PREVIEW;
#पूर्ण_अगर
