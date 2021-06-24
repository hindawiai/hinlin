<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम OmniVision OV5693 5M camera sensor.
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

#अगर_अघोषित __OV5693_H__
#घोषणा __OV5693_H__
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/spinlock.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <media/media-entity.h>

#समावेश "../../include/linux/atomisp_platform.h"

/*
 * FIXME: non-preview resolutions are currently broken
 */
#घोषणा ENABLE_NON_PREVIEW	0

#घोषणा OV5693_POWER_UP_RETRY_NUM 5

/* Defines क्रम रेजिस्टर ग_लिखोs and रेजिस्टर array processing */
#घोषणा I2C_MSG_LENGTH		0x2
#घोषणा I2C_RETRY_COUNT		5

#घोषणा OV5693_FOCAL_LENGTH_NUM	334	/*3.34mm*/
#घोषणा OV5693_FOCAL_LENGTH_DEM	100
#घोषणा OV5693_F_NUMBER_DEFAULT_NUM	24
#घोषणा OV5693_F_NUMBER_DEM	10

#घोषणा MAX_FMTS		1

/* sensor_mode_data पढ़ो_mode adaptation */
#घोषणा OV5693_READ_MODE_BINNING_ON	0x0400
#घोषणा OV5693_READ_MODE_BINNING_OFF	0x00
#घोषणा OV5693_INTEGRATION_TIME_MARGIN	8

#घोषणा OV5693_MAX_EXPOSURE_VALUE	0xFFF1
#घोषणा OV5693_MAX_GAIN_VALUE		0xFF

/*
 * focal length bits definition:
 * bits 31-16: numerator, bits 15-0: denominator
 */
#घोषणा OV5693_FOCAL_LENGTH_DEFAULT 0x1B70064

/*
 * current f-number bits definition:
 * bits 31-16: numerator, bits 15-0: denominator
 */
#घोषणा OV5693_F_NUMBER_DEFAULT 0x18000a

/*
 * f-number range bits definition:
 * bits 31-24: max f-number numerator
 * bits 23-16: max f-number denominator
 * bits 15-8: min f-number numerator
 * bits 7-0: min f-number denominator
 */
#घोषणा OV5693_F_NUMBER_RANGE 0x180a180a
#घोषणा OV5693_ID	0x5690

#घोषणा OV5693_FINE_INTG_TIME_MIN 0
#घोषणा OV5693_FINE_INTG_TIME_MAX_MARGIN 0
#घोषणा OV5693_COARSE_INTG_TIME_MIN 1
#घोषणा OV5693_COARSE_INTG_TIME_MAX_MARGIN 6

#घोषणा OV5693_BIN_FACTOR_MAX 4
/*
 * OV5693 System control रेजिस्टरs
 */
#घोषणा OV5693_SW_SLEEP				0x0100
#घोषणा OV5693_SW_RESET				0x0103
#घोषणा OV5693_SW_STREAM			0x0100

#घोषणा OV5693_SC_CMMN_CHIP_ID_H		0x300A
#घोषणा OV5693_SC_CMMN_CHIP_ID_L		0x300B
#घोषणा OV5693_SC_CMMN_SCCB_ID			0x300C
#घोषणा OV5693_SC_CMMN_SUB_ID			0x302A /* process, version*/
/*Bit[7:4] Group control, Bit[3:0] Group ID*/
#घोषणा OV5693_GROUP_ACCESS			0x3208
/*
*Bit[3:0] Bit[19:16] of exposure,
*reमुख्यing 16 bits lies in Reg0x3501&Reg0x3502
*/
#घोषणा OV5693_EXPOSURE_H			0x3500
#घोषणा OV5693_EXPOSURE_M			0x3501
#घोषणा OV5693_EXPOSURE_L			0x3502
/*Bit[1:0] means Bit[9:8] of gain*/
#घोषणा OV5693_AGC_H				0x350A
#घोषणा OV5693_AGC_L				0x350B /*Bit[7:0] of gain*/

#घोषणा OV5693_HORIZONTAL_START_H		0x3800 /*Bit[11:8]*/
#घोषणा OV5693_HORIZONTAL_START_L		0x3801 /*Bit[7:0]*/
#घोषणा OV5693_VERTICAL_START_H			0x3802 /*Bit[11:8]*/
#घोषणा OV5693_VERTICAL_START_L			0x3803 /*Bit[7:0]*/
#घोषणा OV5693_HORIZONTAL_END_H			0x3804 /*Bit[11:8]*/
#घोषणा OV5693_HORIZONTAL_END_L			0x3805 /*Bit[7:0]*/
#घोषणा OV5693_VERTICAL_END_H			0x3806 /*Bit[11:8]*/
#घोषणा OV5693_VERTICAL_END_L			0x3807 /*Bit[7:0]*/
#घोषणा OV5693_HORIZONTAL_OUTPUT_SIZE_H		0x3808 /*Bit[3:0]*/
#घोषणा OV5693_HORIZONTAL_OUTPUT_SIZE_L		0x3809 /*Bit[7:0]*/
#घोषणा OV5693_VERTICAL_OUTPUT_SIZE_H		0x380a /*Bit[3:0]*/
#घोषणा OV5693_VERTICAL_OUTPUT_SIZE_L		0x380b /*Bit[7:0]*/
/*High 8-bit, and low 8-bit HTS address is 0x380d*/
#घोषणा OV5693_TIMING_HTS_H			0x380C
/*High 8-bit, and low 8-bit HTS address is 0x380d*/
#घोषणा OV5693_TIMING_HTS_L			0x380D
/*High 8-bit, and low 8-bit HTS address is 0x380f*/
#घोषणा OV5693_TIMING_VTS_H			0x380e
/*High 8-bit, and low 8-bit HTS address is 0x380f*/
#घोषणा OV5693_TIMING_VTS_L			0x380f

#घोषणा OV5693_MWB_RED_GAIN_H			0x3400
#घोषणा OV5693_MWB_GREEN_GAIN_H			0x3402
#घोषणा OV5693_MWB_BLUE_GAIN_H			0x3404
#घोषणा OV5693_MWB_GAIN_MAX			0x0fff

#घोषणा OV5693_START_STREAMING			0x01
#घोषणा OV5693_STOP_STREAMING			0x00

#घोषणा VCM_ADDR           0x0c
#घोषणा VCM_CODE_MSB       0x04

#घोषणा OV5693_INVALID_CONFIG	0xffffffff

#घोषणा OV5693_VCM_SLEW_STEP			0x30F0
#घोषणा OV5693_VCM_SLEW_STEP_MAX		0x7
#घोषणा OV5693_VCM_SLEW_STEP_MASK		0x7
#घोषणा OV5693_VCM_CODE				0x30F2
#घोषणा OV5693_VCM_SLEW_TIME			0x30F4
#घोषणा OV5693_VCM_SLEW_TIME_MAX		0xffff
#घोषणा OV5693_VCM_ENABLE			0x8000

#घोषणा OV5693_VCM_MAX_FOCUS_NEG       -1023
#घोषणा OV5693_VCM_MAX_FOCUS_POS       1023

#घोषणा DLC_ENABLE 1
#घोषणा DLC_DISABLE 0
#घोषणा VCM_PROTECTION_OFF     0xeca3
#घोषणा VCM_PROTECTION_ON      0xdc51
#घोषणा VCM_DEFAULT_S 0x0
#घोषणा vcm_step_s(a) (u8)(a & 0xf)
#घोषणा vcm_step_mclk(a) (u8)((a >> 4) & 0x3)
#घोषणा vcm_dlc_mclk(dlc, mclk) (u16)((dlc << 3) | mclk | 0xa104)
#घोषणा vcm_tsrc(tsrc) (u16)(tsrc << 3 | 0xf200)
#घोषणा vcm_val(data, s) (u16)(data << 4 | s)
#घोषणा सूचीECT_VCM vcm_dlc_mclk(0, 0)

/* Defines क्रम OTP Data Registers */
#घोषणा OV5693_FRAME_OFF_NUM		0x4202
#घोषणा OV5693_OTP_BYTE_MAX		32	//change to 32 as needed by otpdata
#घोषणा OV5693_OTP_SHORT_MAX		16
#घोषणा OV5693_OTP_START_ADDR		0x3D00
#घोषणा OV5693_OTP_END_ADDR		0x3D0F
#घोषणा OV5693_OTP_DATA_SIZE		320
#घोषणा OV5693_OTP_PROGRAM_REG		0x3D80
#घोषणा OV5693_OTP_READ_REG		0x3D81	// 1:Enable 0:disable
#घोषणा OV5693_OTP_BANK_REG		0x3D84	//otp bank and mode
#घोषणा OV5693_OTP_READY_REG_DONE	1
#घोषणा OV5693_OTP_BANK_MAX		28
#घोषणा OV5693_OTP_BANK_SIZE		16	//16 bytes per bank
#घोषणा OV5693_OTP_READ_ONETIME		16
#घोषणा OV5693_OTP_MODE_READ		1

काष्ठा regval_list अणु
	u16 reg_num;
	u8 value;
पूर्ण;

काष्ठा ov5693_resolution अणु
	u8 *desc;
	स्थिर काष्ठा ov5693_reg *regs;
	पूर्णांक res;
	पूर्णांक width;
	पूर्णांक height;
	पूर्णांक fps;
	पूर्णांक pix_clk_freq;
	u16 pixels_per_line;
	u16 lines_per_frame;
	u8 bin_factor_x;
	u8 bin_factor_y;
	u8 bin_mode;
	bool used;
पूर्ण;

काष्ठा ov5693_क्रमmat अणु
	u8 *desc;
	u32 pixelक्रमmat;
	काष्ठा ov5693_reg *regs;
पूर्ण;

क्रमागत vcm_type अणु
	VCM_UNKNOWN,
	VCM_AD5823,
	VCM_DW9714,
पूर्ण;

/*
 * ov5693 device काष्ठाure.
 */
काष्ठा ov5693_device अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	काष्ठा mutex input_lock;
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	काष्ठा camera_sensor_platक्रमm_data *platक्रमm_data;
	kसमय_प्रकार बारtamp_t_focus_असल;
	पूर्णांक vt_pix_clk_freq_mhz;
	पूर्णांक fmt_idx;
	पूर्णांक run_mode;
	पूर्णांक otp_size;
	u8 *otp_data;
	u32 focus;
	s16 number_of_steps;
	u8 res;
	u8 type;
	bool vcm_update;
	क्रमागत vcm_type vcm;
पूर्ण;

क्रमागत ov5693_tok_type अणु
	OV5693_8BIT  = 0x0001,
	OV5693_16BIT = 0x0002,
	OV5693_32BIT = 0x0004,
	OV5693_TOK_TERM   = 0xf000,	/* terminating token क्रम reg list */
	OV5693_TOK_DELAY  = 0xfe00,	/* delay token क्रम reg list */
	OV5693_TOK_MASK = 0xfff0
पूर्ण;

/**
 * काष्ठा ov5693_reg - MI sensor  रेजिस्टर क्रमmat
 * @type: type of the रेजिस्टर
 * @reg: 16-bit offset to रेजिस्टर
 * @val: 8/16/32-bit रेजिस्टर value
 *
 * Define a काष्ठाure क्रम sensor रेजिस्टर initialization values
 */
काष्ठा ov5693_reg अणु
	क्रमागत ov5693_tok_type type;
	u16 reg;
	u32 val;	/* @set value क्रम पढ़ो/mod/ग_लिखो, @mask */
पूर्ण;

#घोषणा to_ov5693_sensor(x) container_of(x, काष्ठा ov5693_device, sd)

#घोषणा OV5693_MAX_WRITE_BUF_SIZE	30

काष्ठा ov5693_ग_लिखो_buffer अणु
	u16 addr;
	u8 data[OV5693_MAX_WRITE_BUF_SIZE];
पूर्ण;

काष्ठा ov5693_ग_लिखो_ctrl अणु
	पूर्णांक index;
	काष्ठा ov5693_ग_लिखो_buffer buffer;
पूर्ण;

अटल काष्ठा ov5693_reg स्थिर ov5693_global_setting[] = अणु
	अणुOV5693_8BIT, 0x0103, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x3001, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x3002, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x3006, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3011, 0x21पूर्ण,
	अणुOV5693_8BIT, 0x3012, 0x09पूर्ण,
	अणुOV5693_8BIT, 0x3013, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x3014, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3015, 0x08पूर्ण,
	अणुOV5693_8BIT, 0x3016, 0xf0पूर्ण,
	अणुOV5693_8BIT, 0x3017, 0xf0पूर्ण,
	अणुOV5693_8BIT, 0x3018, 0xf0पूर्ण,
	अणुOV5693_8BIT, 0x301b, 0xb4पूर्ण,
	अणुOV5693_8BIT, 0x301d, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3021, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3022, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x3028, 0x44पूर्ण,
	अणुOV5693_8BIT, 0x3098, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3099, 0x19पूर्ण,
	अणुOV5693_8BIT, 0x309a, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x309b, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x309c, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x30a0, 0xd2पूर्ण,
	अणुOV5693_8BIT, 0x30a2, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x30b2, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x30b3, 0x7dपूर्ण,
	अणुOV5693_8BIT, 0x30b4, 0x03पूर्ण,
	अणुOV5693_8BIT, 0x30b5, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x30b6, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x3104, 0x21पूर्ण,
	अणुOV5693_8BIT, 0x3106, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3400, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x3401, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3402, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x3403, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3404, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x3405, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3406, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x3500, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3503, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x3504, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3505, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3506, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3507, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3508, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3509, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x350a, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x350b, 0x40पूर्ण,
	अणुOV5693_8BIT, 0x3601, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x3602, 0x38पूर्ण,
	अणुOV5693_8BIT, 0x3612, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x3620, 0x54पूर्ण,
	अणुOV5693_8BIT, 0x3621, 0xc7पूर्ण,
	अणुOV5693_8BIT, 0x3622, 0x0fपूर्ण,
	अणुOV5693_8BIT, 0x3625, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x3630, 0x55पूर्ण,
	अणुOV5693_8BIT, 0x3631, 0xf4पूर्ण,
	अणुOV5693_8BIT, 0x3632, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3633, 0x34पूर्ण,
	अणुOV5693_8BIT, 0x3634, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x364d, 0x0dपूर्ण,
	अणुOV5693_8BIT, 0x364f, 0xddपूर्ण,
	अणुOV5693_8BIT, 0x3660, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x3662, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x3663, 0xf1पूर्ण,
	अणुOV5693_8BIT, 0x3665, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3666, 0x20पूर्ण,
	अणुOV5693_8BIT, 0x3667, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x366a, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x3680, 0xe0पूर्ण,
	अणुOV5693_8BIT, 0x3681, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3700, 0x42पूर्ण,
	अणुOV5693_8BIT, 0x3701, 0x14पूर्ण,
	अणुOV5693_8BIT, 0x3702, 0xa0पूर्ण,
	अणुOV5693_8BIT, 0x3703, 0xd8पूर्ण,
	अणुOV5693_8BIT, 0x3704, 0x78पूर्ण,
	अणुOV5693_8BIT, 0x3705, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x370a, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x370b, 0x20पूर्ण,
	अणुOV5693_8BIT, 0x370c, 0x0cपूर्ण,
	अणुOV5693_8BIT, 0x370d, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x370e, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x370f, 0x40पूर्ण,
	अणुOV5693_8BIT, 0x3710, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x371a, 0x1cपूर्ण,
	अणुOV5693_8BIT, 0x371b, 0x05पूर्ण,
	अणुOV5693_8BIT, 0x371c, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x371e, 0xa1पूर्ण,
	अणुOV5693_8BIT, 0x371f, 0x0cपूर्ण,
	अणुOV5693_8BIT, 0x3721, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3724, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x3726, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x372a, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x3730, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x3738, 0x22पूर्ण,
	अणुOV5693_8BIT, 0x3739, 0xe5पूर्ण,
	अणुOV5693_8BIT, 0x373a, 0x50पूर्ण,
	अणुOV5693_8BIT, 0x373b, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x373c, 0x41पूर्ण,
	अणुOV5693_8BIT, 0x373f, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3740, 0x42पूर्ण,
	अणुOV5693_8BIT, 0x3741, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3742, 0x18पूर्ण,
	अणुOV5693_8BIT, 0x3743, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x3744, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3747, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x374c, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x3751, 0xf0पूर्ण,
	अणुOV5693_8BIT, 0x3752, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3753, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3754, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3755, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3756, 0x1aपूर्ण,
	अणुOV5693_8BIT, 0x3758, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3759, 0x0fपूर्ण,
	अणुOV5693_8BIT, 0x376b, 0x44पूर्ण,
	अणुOV5693_8BIT, 0x375c, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x3774, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x3776, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x377f, 0x08पूर्ण,
	अणुOV5693_8BIT, 0x3780, 0x22पूर्ण,
	अणुOV5693_8BIT, 0x3781, 0x0cपूर्ण,
	अणुOV5693_8BIT, 0x3784, 0x2cपूर्ण,
	अणुOV5693_8BIT, 0x3785, 0x1eपूर्ण,
	अणुOV5693_8BIT, 0x378f, 0xf5पूर्ण,
	अणुOV5693_8BIT, 0x3791, 0xb0पूर्ण,
	अणुOV5693_8BIT, 0x3795, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3796, 0x64पूर्ण,
	अणुOV5693_8BIT, 0x3797, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3798, 0x30पूर्ण,
	अणुOV5693_8BIT, 0x3799, 0x41पूर्ण,
	अणुOV5693_8BIT, 0x379a, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x379b, 0xb0पूर्ण,
	अणुOV5693_8BIT, 0x379c, 0x0cपूर्ण,
	अणुOV5693_8BIT, 0x37c5, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x37c6, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x37c7, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x37c9, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x37ca, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x37cb, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x37de, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x37df, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3800, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3801, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3802, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3804, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x3805, 0x3fपूर्ण,
	अणुOV5693_8BIT, 0x3810, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3812, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3823, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3824, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3825, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3826, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3827, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x382a, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x3a04, 0x06पूर्ण,
	अणुOV5693_8BIT, 0x3a05, 0x14पूर्ण,
	अणुOV5693_8BIT, 0x3a06, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3a07, 0xfeपूर्ण,
	अणुOV5693_8BIT, 0x3b00, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3b02, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3b03, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3b04, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3b05, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3e07, 0x20पूर्ण,
	अणुOV5693_8BIT, 0x4000, 0x08पूर्ण,
	अणुOV5693_8BIT, 0x4001, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x4002, 0x45पूर्ण,
	अणुOV5693_8BIT, 0x4004, 0x08पूर्ण,
	अणुOV5693_8BIT, 0x4005, 0x18पूर्ण,
	अणुOV5693_8BIT, 0x4006, 0x20पूर्ण,
	अणुOV5693_8BIT, 0x4008, 0x24पूर्ण,
	अणुOV5693_8BIT, 0x4009, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x400c, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x400d, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x4058, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x404e, 0x37पूर्ण,
	अणुOV5693_8BIT, 0x404f, 0x8fपूर्ण,
	अणुOV5693_8BIT, 0x4058, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x4101, 0xb2पूर्ण,
	अणुOV5693_8BIT, 0x4303, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x4304, 0x08पूर्ण,
	अणुOV5693_8BIT, 0x4307, 0x31पूर्ण,
	अणुOV5693_8BIT, 0x4311, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x4315, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x4511, 0x05पूर्ण,
	अणुOV5693_8BIT, 0x4512, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x4806, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x4816, 0x52पूर्ण,
	अणुOV5693_8BIT, 0x481f, 0x30पूर्ण,
	अणुOV5693_8BIT, 0x4826, 0x2cपूर्ण,
	अणुOV5693_8BIT, 0x4831, 0x64पूर्ण,
	अणुOV5693_8BIT, 0x4d00, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x4d01, 0x71पूर्ण,
	अणुOV5693_8BIT, 0x4d02, 0xfdपूर्ण,
	अणुOV5693_8BIT, 0x4d03, 0xf5पूर्ण,
	अणुOV5693_8BIT, 0x4d04, 0x0cपूर्ण,
	अणुOV5693_8BIT, 0x4d05, 0xccपूर्ण,
	अणुOV5693_8BIT, 0x4837, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x5000, 0x06पूर्ण,
	अणुOV5693_8BIT, 0x5001, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x5003, 0x20पूर्ण,
	अणुOV5693_8BIT, 0x5046, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x5013, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x5046, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x5780, 0x1cपूर्ण,
	अणुOV5693_8BIT, 0x5786, 0x20पूर्ण,
	अणुOV5693_8BIT, 0x5787, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x5788, 0x18पूर्ण,
	अणुOV5693_8BIT, 0x578a, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x578b, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x578c, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x578e, 0x06पूर्ण,
	अणुOV5693_8BIT, 0x578f, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x5790, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x5791, 0xffपूर्ण,
	अणुOV5693_8BIT, 0x5842, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x5843, 0x2bपूर्ण,
	अणुOV5693_8BIT, 0x5844, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x5845, 0x92पूर्ण,
	अणुOV5693_8BIT, 0x5846, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x5847, 0x8fपूर्ण,
	अणुOV5693_8BIT, 0x5848, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x5849, 0x0cपूर्ण,
	अणुOV5693_8BIT, 0x5e00, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x5e10, 0x0cपूर्ण,
	अणुOV5693_8BIT, 0x0100, 0x00पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;

#अगर ENABLE_NON_PREVIEW
/*
 * 654x496 30fps 17ms VBlanking 2lane 10Bit (Scaling)
 */
अटल काष्ठा ov5693_reg स्थिर ov5693_654x496[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x3dपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe6पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc7पूर्ण,
	अणुOV5693_8BIT, 0x3803, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0xa3पूर्ण,
	अणुOV5693_8BIT, 0x3808, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3809, 0x90पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0xf0पूर्ण,
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x08पूर्ण,
	अणुOV5693_8BIT, 0x3813, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3814, 0x31पूर्ण,
	अणुOV5693_8BIT, 0x3815, 0x31पूर्ण,
	अणुOV5693_8BIT, 0x3820, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1fपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;

/*
 * 1296x976 30fps 17ms VBlanking 2lane 10Bit (Scaling)
*DS from 2592x1952
*/
अटल काष्ठा ov5693_reg स्थिर ov5693_1296x976[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x7bपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe2पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,

	अणुOV5693_8BIT, 0x3800, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3801, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3802, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3803, 0x00पूर्ण,

	अणुOV5693_8BIT, 0x3804, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x3805, 0x3fपूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0xA3पूर्ण,

	अणुOV5693_8BIT, 0x3808, 0x05पूर्ण,
	अणुOV5693_8BIT, 0x3809, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x03पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0xD0पूर्ण,

	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,

	अणुOV5693_8BIT, 0x3810, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x3812, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3813, 0x02पूर्ण,

	अणुOV5693_8BIT, 0x3814, 0x11पूर्ण,	/*X subsample control*/
	अणुOV5693_8BIT, 0x3815, 0x11पूर्ण,	/*Y subsample control*/
	अणुOV5693_8BIT, 0x3820, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1eपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x5041, 0x84पूर्ण, /* scale is स्वतः enabled */
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण

पूर्ण;

/*
 * 336x256 30fps 17ms VBlanking 2lane 10Bit (Scaling)
 DS from 2564x1956
 */
अटल काष्ठा ov5693_reg स्थिर ov5693_336x256[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x3dपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe6पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc7पूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0xa3पूर्ण,
	अणुOV5693_8BIT, 0x3808, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x3809, 0x50पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x1Eपूर्ण,
	अणुOV5693_8BIT, 0x3814, 0x31पूर्ण,
	अणुOV5693_8BIT, 0x3815, 0x31पूर्ण,
	अणुOV5693_8BIT, 0x3820, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1fपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;

/*
 * 336x256 30fps 17ms VBlanking 2lane 10Bit (Scaling)
 DS from 2368x1956
 */
अटल काष्ठा ov5693_reg स्थिर ov5693_368x304[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x3dपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe6पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc7पूर्ण,
	अणुOV5693_8BIT, 0x3808, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x3809, 0x70पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0x30पूर्ण,
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x3814, 0x31पूर्ण,
	अणुOV5693_8BIT, 0x3815, 0x31पूर्ण,
	अणुOV5693_8BIT, 0x3820, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1fपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;

/*
 * ov5693_192x160 30fps 17ms VBlanking 2lane 10Bit (Scaling)
 DS from 2460x1956
 */
अटल काष्ठा ov5693_reg स्थिर ov5693_192x160[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x7bपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe2पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,
	अणुOV5693_8BIT, 0x3804, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x3805, 0x3fपूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0xA3पूर्ण,
	अणुOV5693_8BIT, 0x3808, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3809, 0xC0पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0xA0पूर्ण,
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x40पूर्ण,
	अणुOV5693_8BIT, 0x3813, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3814, 0x31पूर्ण,
	अणुOV5693_8BIT, 0x3815, 0x31पूर्ण,
	अणुOV5693_8BIT, 0x3820, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1fपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;

अटल काष्ठा ov5693_reg स्थिर ov5693_736x496[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x3dपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe6पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc7पूर्ण,
	अणुOV5693_8BIT, 0x3803, 0x68पूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0x3bपूर्ण,
	अणुOV5693_8BIT, 0x3808, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3809, 0xe0पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0xf0पूर्ण,
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण, /*hts*/
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण, /*vts*/
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x08पूर्ण,
	अणुOV5693_8BIT, 0x3813, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3814, 0x31पूर्ण,
	अणुOV5693_8BIT, 0x3815, 0x31पूर्ण,
	अणुOV5693_8BIT, 0x3820, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1fपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;
#पूर्ण_अगर

/*
अटल काष्ठा ov5693_reg स्थिर ov5693_736x496[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x7bपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe6पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,
	अणुOV5693_8BIT, 0x3803, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0xa3पूर्ण,
	अणुOV5693_8BIT, 0x3808, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3809, 0xe0पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0xf0पूर्ण,
	अणुOV5693_8BIT, 0x380c, 0x0dपूर्ण,
	अणुOV5693_8BIT, 0x380d, 0xb0पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x05पूर्ण,
	अणुOV5693_8BIT, 0x380f, 0xf2पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x08पूर्ण,
	अणुOV5693_8BIT, 0x3813, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3814, 0x31पूर्ण,
	अणुOV5693_8BIT, 0x3815, 0x31पूर्ण,
	अणुOV5693_8BIT, 0x3820, 0x01पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1fपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;
*/
/*
 * 976x556 30fps 8.8ms VBlanking 2lane 10Bit (Scaling)
 */
#अगर ENABLE_NON_PREVIEW
अटल काष्ठा ov5693_reg स्थिर ov5693_976x556[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x7bपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe2पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,
	अणुOV5693_8BIT, 0x3803, 0xf0पूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x06पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0xa7पूर्ण,
	अणुOV5693_8BIT, 0x3808, 0x03पूर्ण,
	अणुOV5693_8BIT, 0x3809, 0xd0पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0x2Cपूर्ण,
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x3813, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3814, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3815, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3820, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1eपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;

/*DS from 2624x1492*/
अटल काष्ठा ov5693_reg स्थिर ov5693_1296x736[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x7bपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe2पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,

	अणुOV5693_8BIT, 0x3800, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3801, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3802, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3803, 0x00पूर्ण,

	अणुOV5693_8BIT, 0x3804, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x3805, 0x3fपूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0xA3पूर्ण,

	अणुOV5693_8BIT, 0x3808, 0x05पूर्ण,
	अणुOV5693_8BIT, 0x3809, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0xe0पूर्ण,

	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,

	अणुOV5693_8BIT, 0x3813, 0xE8पूर्ण,

	अणुOV5693_8BIT, 0x3814, 0x11पूर्ण,	/*X subsample control*/
	अणुOV5693_8BIT, 0x3815, 0x11पूर्ण,	/*Y subsample control*/
	अणुOV5693_8BIT, 0x3820, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1eपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x5041, 0x84पूर्ण, /* scale is स्वतः enabled */
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;

अटल काष्ठा ov5693_reg स्थिर ov5693_1636p_30fps[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x7bपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe2पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,
	अणुOV5693_8BIT, 0x3803, 0xf0पूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x06पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0xa7पूर्ण,
	अणुOV5693_8BIT, 0x3808, 0x06पूर्ण,
	अणुOV5693_8BIT, 0x3809, 0x64पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0x48पूर्ण,
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण, /*hts*/
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण, /*vts*/
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3813, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3814, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3815, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3820, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1eपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा ov5693_reg स्थिर ov5693_1616x1216_30fps[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x7bपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe2पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,
	अणुOV5693_8BIT, 0x3800, 0x00पूर्ण,	/*अणु3800,3801पूर्ण Array X start*/
	अणुOV5693_8BIT, 0x3801, 0x08पूर्ण,	/* 04 //अणु3800,3801पूर्ण Array X start*/
	अणुOV5693_8BIT, 0x3802, 0x00पूर्ण,	/*अणु3802,3803पूर्ण Array Y start*/
	अणुOV5693_8BIT, 0x3803, 0x04पूर्ण,	/* 00  //अणु3802,3803पूर्ण Array Y start*/
	अणुOV5693_8BIT, 0x3804, 0x0aपूर्ण,	/*अणु3804,3805पूर्ण Array X end*/
	अणुOV5693_8BIT, 0x3805, 0x37पूर्ण,	/* 3b  //अणु3804,3805पूर्ण Array X end*/
	अणुOV5693_8BIT, 0x3806, 0x07पूर्ण,	/*अणु3806,3807पूर्ण Array Y end*/
	अणुOV5693_8BIT, 0x3807, 0x9fपूर्ण,	/* a3  //अणु3806,3807पूर्ण Array Y end*/
	अणुOV5693_8BIT, 0x3808, 0x06पूर्ण,	/*अणु3808,3809पूर्ण Final output H size*/
	अणुOV5693_8BIT, 0x3809, 0x50पूर्ण,	/*अणु3808,3809पूर्ण Final output H size*/
	अणुOV5693_8BIT, 0x380a, 0x04पूर्ण,	/*अणु380a,380bपूर्ण Final output V size*/
	अणुOV5693_8BIT, 0x380b, 0xc0पूर्ण,	/*अणु380a,380bपूर्ण Final output V size*/
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण,	/*अणु380c,380dपूर्ण HTS*/
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,	/*अणु380c,380dपूर्ण HTS*/
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण,	/*अणु380e,380fपूर्ण VTS*/
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,	/* bc	//अणु380e,380fपूर्ण VTS*/
	अणुOV5693_8BIT, 0x3810, 0x00पूर्ण,	/*अणु3810,3811पूर्ण winकरोwing X offset*/
	अणुOV5693_8BIT, 0x3811, 0x10पूर्ण,	/*अणु3810,3811पूर्ण winकरोwing X offset*/
	अणुOV5693_8BIT, 0x3812, 0x00पूर्ण,	/*अणु3812,3813पूर्ण winकरोwing Y offset*/
	अणुOV5693_8BIT, 0x3813, 0x06पूर्ण,	/*अणु3812,3813पूर्ण winकरोwing Y offset*/
	अणुOV5693_8BIT, 0x3814, 0x11पूर्ण,	/*X subsample control*/
	अणुOV5693_8BIT, 0x3815, 0x11पूर्ण,	/*Y subsample control*/
	अणुOV5693_8BIT, 0x3820, 0x00पूर्ण,	/*FLIP/Binnning control*/
	अणुOV5693_8BIT, 0x3821, 0x1eपूर्ण,	/*MIRROR control*/
	अणुOV5693_8BIT, 0x5002, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x5041, 0x84पूर्ण,
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;

/*
 * 1940x1096 30fps 8.8ms VBlanking 2lane 10bit (Scaling)
 */
#अगर ENABLE_NON_PREVIEW
अटल काष्ठा ov5693_reg स्थिर ov5693_1940x1096[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x7bपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe2पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,
	अणुOV5693_8BIT, 0x3803, 0xf0पूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x06पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0xa7पूर्ण,
	अणुOV5693_8BIT, 0x3808, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x3809, 0x94पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x04पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0x48पूर्ण,
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3813, 0x02पूर्ण,
	अणुOV5693_8BIT, 0x3814, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3815, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3820, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1eपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;

अटल काष्ठा ov5693_reg स्थिर ov5693_2592x1456_30fps[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x7bपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe2पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,
	अणुOV5693_8BIT, 0x3800, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3801, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3802, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3803, 0xf0पूर्ण,
	अणुOV5693_8BIT, 0x3804, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x3805, 0x3fपूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x06पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0xa4पूर्ण,
	अणुOV5693_8BIT, 0x3808, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x3809, 0x20पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x05पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0xb0पूर्ण,
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x3813, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3814, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3815, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3820, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1eपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x00पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा ov5693_reg स्थिर ov5693_2576x1456_30fps[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x7bपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe2पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,
	अणुOV5693_8BIT, 0x3800, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3801, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3802, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3803, 0xf0पूर्ण,
	अणुOV5693_8BIT, 0x3804, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x3805, 0x3fपूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x06पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0xa4पूर्ण,
	अणुOV5693_8BIT, 0x3808, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x3809, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x05पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0xb0पूर्ण,
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x18पूर्ण,
	अणुOV5693_8BIT, 0x3813, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3814, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3815, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3820, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1eपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x00पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;

/*
 * 2592x1944 30fps 0.6ms VBlanking 2lane 10Bit
 */
#अगर ENABLE_NON_PREVIEW
अटल काष्ठा ov5693_reg स्थिर ov5693_2592x1944_30fps[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x7bपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe2पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,
	अणुOV5693_8BIT, 0x3803, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0xa3पूर्ण,
	अणुOV5693_8BIT, 0x3808, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x3809, 0x20पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0x98पूर्ण,
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x3813, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3814, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3815, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3820, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1eपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;
#पूर्ण_अगर

/*
 * 11:9 Full FOV Output, expected FOV Res: 2346x1920
 * ISP Effect Res: 1408x1152
 * Sensor out: 1424x1168, DS From: 2380x1952
 *
 * WA: Left Offset: 8, Hor scal: 64
 */
#अगर ENABLE_NON_PREVIEW
अटल काष्ठा ov5693_reg स्थिर ov5693_1424x1168_30fps[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x3bपूर्ण, /* दीर्घ exposure[15:8] */
	अणुOV5693_8BIT, 0x3502, 0x80पूर्ण, /* दीर्घ exposure[7:0] */
	अणुOV5693_8BIT, 0x3708, 0xe2पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,
	अणुOV5693_8BIT, 0x3800, 0x00पूर्ण, /* TIMING_X_ADDR_START */
	अणुOV5693_8BIT, 0x3801, 0x50पूर्ण, /* 80 */
	अणुOV5693_8BIT, 0x3802, 0x00पूर्ण, /* TIMING_Y_ADDR_START */
	अणुOV5693_8BIT, 0x3803, 0x02पूर्ण, /* 2 */
	अणुOV5693_8BIT, 0x3804, 0x09पूर्ण, /* TIMING_X_ADDR_END */
	अणुOV5693_8BIT, 0x3805, 0xddपूर्ण, /* 2525 */
	अणुOV5693_8BIT, 0x3806, 0x07पूर्ण, /* TIMING_Y_ADDR_END */
	अणुOV5693_8BIT, 0x3807, 0xa1पूर्ण, /* 1953 */
	अणुOV5693_8BIT, 0x3808, 0x05पूर्ण, /* TIMING_X_OUTPUT_SIZE */
	अणुOV5693_8BIT, 0x3809, 0x90पूर्ण, /* 1424 */
	अणुOV5693_8BIT, 0x380a, 0x04पूर्ण, /* TIMING_Y_OUTPUT_SIZE */
	अणुOV5693_8BIT, 0x380b, 0x90पूर्ण, /* 1168 */
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण, /* TIMING_HTS */
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण, /* TIMING_VTS */
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3810, 0x00पूर्ण, /* TIMING_ISP_X_WIN */
	अणुOV5693_8BIT, 0x3811, 0x02पूर्ण, /* 2 */
	अणुOV5693_8BIT, 0x3812, 0x00पूर्ण, /* TIMING_ISP_Y_WIN */
	अणुOV5693_8BIT, 0x3813, 0x00पूर्ण, /* 0 */
	अणुOV5693_8BIT, 0x3814, 0x11पूर्ण, /* TIME_X_INC */
	अणुOV5693_8BIT, 0x3815, 0x11पूर्ण, /* TIME_Y_INC */
	अणुOV5693_8BIT, 0x3820, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1eपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x5041, 0x84पूर्ण, /* scale is स्वतः enabled */
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;
#पूर्ण_अगर

/*
 * 3:2 Full FOV Output, expected FOV Res: 2560x1706
 * ISP Effect Res: 720x480
 * Sensor out: 736x496, DS From 2616x1764
 */
अटल काष्ठा ov5693_reg स्थिर ov5693_736x496_30fps[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x3bपूर्ण, /* दीर्घ exposure[15:8] */
	अणुOV5693_8BIT, 0x3502, 0x80पूर्ण, /* दीर्घ exposure[7:0] */
	अणुOV5693_8BIT, 0x3708, 0xe2पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,
	अणुOV5693_8BIT, 0x3800, 0x00पूर्ण, /* TIMING_X_ADDR_START */
	अणुOV5693_8BIT, 0x3801, 0x02पूर्ण, /* 2 */
	अणुOV5693_8BIT, 0x3802, 0x00पूर्ण, /* TIMING_Y_ADDR_START */
	अणुOV5693_8BIT, 0x3803, 0x62पूर्ण, /* 98 */
	अणुOV5693_8BIT, 0x3804, 0x0aपूर्ण, /* TIMING_X_ADDR_END */
	अणुOV5693_8BIT, 0x3805, 0x3bपूर्ण, /* 2619 */
	अणुOV5693_8BIT, 0x3806, 0x07पूर्ण, /* TIMING_Y_ADDR_END */
	अणुOV5693_8BIT, 0x3807, 0x43पूर्ण, /* 1859 */
	अणुOV5693_8BIT, 0x3808, 0x02पूर्ण, /* TIMING_X_OUTPUT_SIZE */
	अणुOV5693_8BIT, 0x3809, 0xe0पूर्ण, /* 736 */
	अणुOV5693_8BIT, 0x380a, 0x01पूर्ण, /* TIMING_Y_OUTPUT_SIZE */
	अणुOV5693_8BIT, 0x380b, 0xf0पूर्ण, /* 496 */
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण, /* TIMING_HTS */
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण, /* TIMING_VTS */
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3810, 0x00पूर्ण, /* TIMING_ISP_X_WIN */
	अणुOV5693_8BIT, 0x3811, 0x02पूर्ण, /* 2 */
	अणुOV5693_8BIT, 0x3812, 0x00पूर्ण, /* TIMING_ISP_Y_WIN */
	अणुOV5693_8BIT, 0x3813, 0x00पूर्ण, /* 0 */
	अणुOV5693_8BIT, 0x3814, 0x11पूर्ण, /* TIME_X_INC */
	अणुOV5693_8BIT, 0x3815, 0x11पूर्ण, /* TIME_Y_INC */
	अणुOV5693_8BIT, 0x3820, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1eपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x5041, 0x84पूर्ण, /* scale is स्वतः enabled */
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;

अटल काष्ठा ov5693_reg स्थिर ov5693_2576x1936_30fps[] = अणु
	अणुOV5693_8BIT, 0x3501, 0x7bपूर्ण,
	अणुOV5693_8BIT, 0x3502, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3708, 0xe2पूर्ण,
	अणुOV5693_8BIT, 0x3709, 0xc3पूर्ण,
	अणुOV5693_8BIT, 0x3803, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3806, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x3807, 0xa3पूर्ण,
	अणुOV5693_8BIT, 0x3808, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x3809, 0x10पूर्ण,
	अणुOV5693_8BIT, 0x380a, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380b, 0x90पूर्ण,
	अणुOV5693_8BIT, 0x380c, 0x0aपूर्ण,
	अणुOV5693_8BIT, 0x380d, 0x80पूर्ण,
	अणुOV5693_8BIT, 0x380e, 0x07पूर्ण,
	अणुOV5693_8BIT, 0x380f, 0xc0पूर्ण,
	अणुOV5693_8BIT, 0x3811, 0x18पूर्ण,
	अणुOV5693_8BIT, 0x3813, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3814, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3815, 0x11पूर्ण,
	अणुOV5693_8BIT, 0x3820, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x3821, 0x1eपूर्ण,
	अणुOV5693_8BIT, 0x5002, 0x00पूर्ण,
	अणुOV5693_8BIT, 0x0100, 0x01पूर्ण,
	अणुOV5693_TOK_TERM, 0, 0पूर्ण
पूर्ण;

अटल काष्ठा ov5693_resolution ov5693_res_preview[] = अणु
	अणु
		.desc = "ov5693_736x496_30fps",
		.width = 736,
		.height = 496,
		.pix_clk_freq = 160,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.regs = ov5693_736x496_30fps,
	पूर्ण,
	अणु
		.desc = "ov5693_1616x1216_30fps",
		.width = 1616,
		.height = 1216,
		.pix_clk_freq = 160,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.regs = ov5693_1616x1216_30fps,
	पूर्ण,
	अणु
		.desc = "ov5693_5M_30fps",
		.width = 2576,
		.height = 1456,
		.pix_clk_freq = 160,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.regs = ov5693_2576x1456_30fps,
	पूर्ण,
	अणु
		.desc = "ov5693_5M_30fps",
		.width = 2576,
		.height = 1936,
		.pix_clk_freq = 160,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.regs = ov5693_2576x1936_30fps,
	पूर्ण,
पूर्ण;

#घोषणा N_RES_PREVIEW (ARRAY_SIZE(ov5693_res_preview))

/*
 * Disable non-preview configurations until the configuration selection is
 * improved.
 */
#अगर ENABLE_NON_PREVIEW
काष्ठा ov5693_resolution ov5693_res_still[] = अणु
	अणु
		.desc = "ov5693_736x496_30fps",
		.width = 736,
		.height = 496,
		.pix_clk_freq = 160,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.regs = ov5693_736x496_30fps,
	पूर्ण,
	अणु
		.desc = "ov5693_1424x1168_30fps",
		.width = 1424,
		.height = 1168,
		.pix_clk_freq = 160,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.regs = ov5693_1424x1168_30fps,
	पूर्ण,
	अणु
		.desc = "ov5693_1616x1216_30fps",
		.width = 1616,
		.height = 1216,
		.pix_clk_freq = 160,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.regs = ov5693_1616x1216_30fps,
	पूर्ण,
	अणु
		.desc = "ov5693_5M_30fps",
		.width = 2592,
		.height = 1456,
		.pix_clk_freq = 160,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.regs = ov5693_2592x1456_30fps,
	पूर्ण,
	अणु
		.desc = "ov5693_5M_30fps",
		.width = 2592,
		.height = 1944,
		.pix_clk_freq = 160,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.regs = ov5693_2592x1944_30fps,
	पूर्ण,
पूर्ण;

#घोषणा N_RES_STILL (ARRAY_SIZE(ov5693_res_still))

काष्ठा ov5693_resolution ov5693_res_video[] = अणु
	अणु
		.desc = "ov5693_736x496_30fps",
		.width = 736,
		.height = 496,
		.fps = 30,
		.pix_clk_freq = 160,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 2,
		.bin_factor_y = 2,
		.bin_mode = 1,
		.regs = ov5693_736x496,
	पूर्ण,
	अणु
		.desc = "ov5693_336x256_30fps",
		.width = 336,
		.height = 256,
		.fps = 30,
		.pix_clk_freq = 160,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 2,
		.bin_factor_y = 2,
		.bin_mode = 1,
		.regs = ov5693_336x256,
	पूर्ण,
	अणु
		.desc = "ov5693_368x304_30fps",
		.width = 368,
		.height = 304,
		.fps = 30,
		.pix_clk_freq = 160,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 2,
		.bin_factor_y = 2,
		.bin_mode = 1,
		.regs = ov5693_368x304,
	पूर्ण,
	अणु
		.desc = "ov5693_192x160_30fps",
		.width = 192,
		.height = 160,
		.fps = 30,
		.pix_clk_freq = 160,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 2,
		.bin_factor_y = 2,
		.bin_mode = 1,
		.regs = ov5693_192x160,
	पूर्ण,
	अणु
		.desc = "ov5693_1296x736_30fps",
		.width = 1296,
		.height = 736,
		.fps = 30,
		.pix_clk_freq = 160,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 2,
		.bin_factor_y = 2,
		.bin_mode = 0,
		.regs = ov5693_1296x736,
	पूर्ण,
	अणु
		.desc = "ov5693_1296x976_30fps",
		.width = 1296,
		.height = 976,
		.fps = 30,
		.pix_clk_freq = 160,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 2,
		.bin_factor_y = 2,
		.bin_mode = 0,
		.regs = ov5693_1296x976,
	पूर्ण,
	अणु
		.desc = "ov5693_1636P_30fps",
		.width = 1636,
		.height = 1096,
		.fps = 30,
		.pix_clk_freq = 160,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.regs = ov5693_1636p_30fps,
	पूर्ण,
	अणु
		.desc = "ov5693_1080P_30fps",
		.width = 1940,
		.height = 1096,
		.fps = 30,
		.pix_clk_freq = 160,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.regs = ov5693_1940x1096,
	पूर्ण,
	अणु
		.desc = "ov5693_5M_30fps",
		.width = 2592,
		.height = 1456,
		.pix_clk_freq = 160,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.regs = ov5693_2592x1456_30fps,
	पूर्ण,
	अणु
		.desc = "ov5693_5M_30fps",
		.width = 2592,
		.height = 1944,
		.pix_clk_freq = 160,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2688,
		.lines_per_frame = 1984,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.regs = ov5693_2592x1944_30fps,
	पूर्ण,
पूर्ण;

#घोषणा N_RES_VIDEO (ARRAY_SIZE(ov5693_res_video))
#पूर्ण_अगर

अटल काष्ठा ov5693_resolution *ov5693_res = ov5693_res_preview;
अटल अचिन्हित दीर्घ N_RES = N_RES_PREVIEW;
#पूर्ण_अगर
