<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम GalaxyCore GC2235 2M camera sensor.
 *
 * Copyright (c) 2014 Intel Corporation. All Rights Reserved.
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
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.
 *
 */

#अगर_अघोषित __GC2235_H__
#घोषणा __GC2235_H__
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

#समावेश "../include/linux/atomisp_platform.h"

/*
 * FIXME: non-preview resolutions are currently broken
 */
#घोषणा ENABLE_NON_PREVIEW     0

/* Defines क्रम रेजिस्टर ग_लिखोs and रेजिस्टर array processing */
#घोषणा I2C_MSG_LENGTH		0x2
#घोषणा I2C_RETRY_COUNT		5

#घोषणा GC2235_FOCAL_LENGTH_NUM	278	/*2.78mm*/
#घोषणा GC2235_FOCAL_LENGTH_DEM	100
#घोषणा GC2235_F_NUMBER_DEFAULT_NUM	26
#घोषणा GC2235_F_NUMBER_DEM	10

#घोषणा MAX_FMTS		1

/*
 * focal length bits definition:
 * bits 31-16: numerator, bits 15-0: denominator
 */
#घोषणा GC2235_FOCAL_LENGTH_DEFAULT 0x1160064

/*
 * current f-number bits definition:
 * bits 31-16: numerator, bits 15-0: denominator
 */
#घोषणा GC2235_F_NUMBER_DEFAULT 0x1a000a

/*
 * f-number range bits definition:
 * bits 31-24: max f-number numerator
 * bits 23-16: max f-number denominator
 * bits 15-8: min f-number numerator
 * bits 7-0: min f-number denominator
 */
#घोषणा GC2235_F_NUMBER_RANGE 0x1a0a1a0a
#घोषणा GC2235_ID	0x2235

#घोषणा GC2235_FINE_INTG_TIME_MIN 0
#घोषणा GC2235_FINE_INTG_TIME_MAX_MARGIN 0
#घोषणा GC2235_COARSE_INTG_TIME_MIN 1
#घोषणा GC2235_COARSE_INTG_TIME_MAX_MARGIN 6

/*
 * GC2235 System control रेजिस्टरs
 */
/*
 * GC2235 System control रेजिस्टरs
 */
#घोषणा GC2235_SENSOR_ID_H		0xF0
#घोषणा GC2235_SENSOR_ID_L		0xF1
#घोषणा GC2235_RESET_RELATED		0xFE
#घोषणा GC2235_SW_RESET			0x8
#घोषणा GC2235_MIPI_RESET		0x3
#घोषणा GC2235_RESET_BIT		0x4
#घोषणा GC2235_REGISTER_PAGE_0		0x0
#घोषणा GC2235_REGISTER_PAGE_3		0x3

#घोषणा GC2235_V_CROP_START_H		0x91
#घोषणा GC2235_V_CROP_START_L		0x92
#घोषणा GC2235_H_CROP_START_H		0x93
#घोषणा GC2235_H_CROP_START_L		0x94
#घोषणा GC2235_V_OUTSIZE_H		0x95
#घोषणा GC2235_V_OUTSIZE_L		0x96
#घोषणा GC2235_H_OUTSIZE_H		0x97
#घोषणा GC2235_H_OUTSIZE_L		0x98

#घोषणा GC2235_HB_H			0x5
#घोषणा GC2235_HB_L			0x6
#घोषणा GC2235_VB_H			0x7
#घोषणा GC2235_VB_L			0x8
#घोषणा GC2235_SH_DELAY_H		0x11
#घोषणा GC2235_SH_DELAY_L		0x12

#घोषणा GC2235_CSI2_MODE		0x10

#घोषणा GC2235_EXPOSURE_H		0x3
#घोषणा GC2235_EXPOSURE_L		0x4
#घोषणा GC2235_GLOBAL_GAIN		0xB0
#घोषणा GC2235_PRE_GAIN			0xB1
#घोषणा GC2235_AWB_R_GAIN		0xB3
#घोषणा GC2235_AWB_G_GAIN		0xB4
#घोषणा GC2235_AWB_B_GAIN		0xB5

#घोषणा GC2235_START_STREAMING		0x91
#घोषणा GC2235_STOP_STREAMING		0x0

काष्ठा regval_list अणु
	u16 reg_num;
	u8 value;
पूर्ण;

काष्ठा gc2235_resolution अणु
	u8 *desc;
	स्थिर काष्ठा gc2235_reg *regs;
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
पूर्ण;

काष्ठा gc2235_क्रमmat अणु
	u8 *desc;
	u32 pixelक्रमmat;
	काष्ठा gc2235_reg *regs;
पूर्ण;

/*
 * gc2235 device काष्ठाure.
 */
काष्ठा gc2235_device अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	काष्ठा mutex input_lock;
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	काष्ठा camera_sensor_platक्रमm_data *platक्रमm_data;
	पूर्णांक vt_pix_clk_freq_mhz;
	पूर्णांक fmt_idx;
	u8 res;
	u8 type;
पूर्ण;

क्रमागत gc2235_tok_type अणु
	GC2235_8BIT  = 0x0001,
	GC2235_16BIT = 0x0002,
	GC2235_32BIT = 0x0004,
	GC2235_TOK_TERM   = 0xf000,	/* terminating token क्रम reg list */
	GC2235_TOK_DELAY  = 0xfe00,	/* delay token क्रम reg list */
	GC2235_TOK_MASK = 0xfff0
पूर्ण;

/**
 * काष्ठा gc2235_reg - MI sensor  रेजिस्टर क्रमmat
 * @type: type of the रेजिस्टर
 * @reg: 8-bit offset to रेजिस्टर
 * @val: 8/16/32-bit रेजिस्टर value
 *
 * Define a काष्ठाure क्रम sensor रेजिस्टर initialization values
 */
काष्ठा gc2235_reg अणु
	क्रमागत gc2235_tok_type type;
	u8 reg;
	u32 val;	/* @set value क्रम पढ़ो/mod/ग_लिखो, @mask */
पूर्ण;

#घोषणा to_gc2235_sensor(x) container_of(x, काष्ठा gc2235_device, sd)

#घोषणा GC2235_MAX_WRITE_BUF_SIZE	30

काष्ठा gc2235_ग_लिखो_buffer अणु
	u8 addr;
	u8 data[GC2235_MAX_WRITE_BUF_SIZE];
पूर्ण;

काष्ठा gc2235_ग_लिखो_ctrl अणु
	पूर्णांक index;
	काष्ठा gc2235_ग_लिखो_buffer buffer;
पूर्ण;

अटल काष्ठा gc2235_reg स्थिर gc2235_stream_on[] = अणु
	अणु GC2235_8BIT, 0xfe, 0x03पूर्ण, /* चयन to P3 */
	अणु GC2235_8BIT, 0x10, 0x91पूर्ण, /* start mipi */
	अणु GC2235_8BIT, 0xfe, 0x00पूर्ण, /* चयन to P0 */
	अणु GC2235_TOK_TERM, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा gc2235_reg स्थिर gc2235_stream_off[] = अणु
	अणु GC2235_8BIT, 0xfe, 0x03पूर्ण, /* चयन to P3 */
	अणु GC2235_8BIT, 0x10, 0x01पूर्ण, /* stop mipi */
	अणु GC2235_8BIT, 0xfe, 0x00पूर्ण, /* चयन to P0 */
	अणु GC2235_TOK_TERM, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा gc2235_reg स्थिर gc2235_init_settings[] = अणु
	/* System */
	अणु GC2235_8BIT, 0xfe, 0x80 पूर्ण,
	अणु GC2235_8BIT, 0xfe, 0x80 पूर्ण,
	अणु GC2235_8BIT, 0xfe, 0x80 पूर्ण,
	अणु GC2235_8BIT, 0xf2, 0x00 पूर्ण,
	अणु GC2235_8BIT, 0xf6, 0x00 पूर्ण,
	अणु GC2235_8BIT, 0xfc, 0x06 पूर्ण,
	अणु GC2235_8BIT, 0xf7, 0x15 पूर्ण,
	अणु GC2235_8BIT, 0xf8, 0x84 पूर्ण,
	अणु GC2235_8BIT, 0xf9, 0xfe पूर्ण,
	अणु GC2235_8BIT, 0xfa, 0x00 पूर्ण,
	अणु GC2235_8BIT, 0xfe, 0x00 पूर्ण,
	/* Analog & cisctl */
	अणु GC2235_8BIT, 0x03, 0x04 पूर्ण,
	अणु GC2235_8BIT, 0x04, 0x9E पूर्ण,
	अणु GC2235_8BIT, 0x05, 0x00 पूर्ण,
	अणु GC2235_8BIT, 0x06, 0xfd पूर्ण,
	अणु GC2235_8BIT, 0x07, 0x00 पूर्ण,
	अणु GC2235_8BIT, 0x08, 0x14 पूर्ण,
	अणु GC2235_8BIT, 0x0a, 0x02 पूर्ण, /* row start */
	अणु GC2235_8BIT, 0x0c, 0x00 पूर्ण, /* col start */
	अणु GC2235_8BIT, 0x0d, 0x04 पूर्ण, /* win height 1232 */
	अणु GC2235_8BIT, 0x0e, 0xd0 पूर्ण,
	अणु GC2235_8BIT, 0x0f, 0x06 पूर्ण, /* win width: 1616 */
	अणु GC2235_8BIT, 0x10, 0x60 पूर्ण,
	अणु GC2235_8BIT, 0x17, 0x15 पूर्ण, /* mirror flip */
	अणु GC2235_8BIT, 0x18, 0x1a पूर्ण,
	अणु GC2235_8BIT, 0x19, 0x06 पूर्ण,
	अणु GC2235_8BIT, 0x1a, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x1b, 0x4d पूर्ण,
	अणु GC2235_8BIT, 0x1e, 0x88 पूर्ण,
	अणु GC2235_8BIT, 0x1f, 0x48 पूर्ण,
	अणु GC2235_8BIT, 0x20, 0x03 पूर्ण,
	अणु GC2235_8BIT, 0x21, 0x7f पूर्ण,
	अणु GC2235_8BIT, 0x22, 0x83 पूर्ण,
	अणु GC2235_8BIT, 0x23, 0x42 पूर्ण,
	अणु GC2235_8BIT, 0x24, 0x16 पूर्ण,
	अणु GC2235_8BIT, 0x26, 0x01 पूर्ण, /*analog gain*/
	अणु GC2235_8BIT, 0x27, 0x30 पूर्ण,
	अणु GC2235_8BIT, 0x3f, 0x00 पूर्ण, /* PRC */
	/* blk */
	अणु GC2235_8BIT, 0x40, 0xa3 पूर्ण,
	अणु GC2235_8BIT, 0x41, 0x82 पूर्ण,
	अणु GC2235_8BIT, 0x43, 0x20 पूर्ण,
	अणु GC2235_8BIT, 0x5e, 0x18 पूर्ण,
	अणु GC2235_8BIT, 0x5f, 0x18 पूर्ण,
	अणु GC2235_8BIT, 0x60, 0x18 पूर्ण,
	अणु GC2235_8BIT, 0x61, 0x18 पूर्ण,
	अणु GC2235_8BIT, 0x62, 0x18 पूर्ण,
	अणु GC2235_8BIT, 0x63, 0x18 पूर्ण,
	अणु GC2235_8BIT, 0x64, 0x18 पूर्ण,
	अणु GC2235_8BIT, 0x65, 0x18 पूर्ण,
	अणु GC2235_8BIT, 0x66, 0x20 पूर्ण,
	अणु GC2235_8BIT, 0x67, 0x20 पूर्ण,
	अणु GC2235_8BIT, 0x68, 0x20 पूर्ण,
	अणु GC2235_8BIT, 0x69, 0x20 पूर्ण,
	/* Gain */
	अणु GC2235_8BIT, 0xb2, 0x00 पूर्ण,
	अणु GC2235_8BIT, 0xb3, 0x40 पूर्ण,
	अणु GC2235_8BIT, 0xb4, 0x40 पूर्ण,
	अणु GC2235_8BIT, 0xb5, 0x40 पूर्ण,
	/* Dark sun */
	अणु GC2235_8BIT, 0xbc, 0x00 पूर्ण,

	अणु GC2235_8BIT, 0xfe, 0x03 पूर्ण,
	अणु GC2235_8BIT, 0x10, 0x01 पूर्ण, /* disable mipi */
	अणु GC2235_8BIT, 0xfe, 0x00 पूर्ण, /* चयन to P0 */
	अणु GC2235_TOK_TERM, 0, 0 पूर्ण
पूर्ण;

/*
 * Register settings क्रम various resolution
 */
#अगर ENABLE_NON_PREVIEW
अटल काष्ठा gc2235_reg स्थिर gc2235_1296_736_30fps[] = अणु
	अणु GC2235_8BIT, 0x8b, 0xa0 पूर्ण,
	अणु GC2235_8BIT, 0x8c, 0x02 पूर्ण,

	अणु GC2235_8BIT, 0x07, 0x01 पूर्ण, /* VBI */
	अणु GC2235_8BIT, 0x08, 0x44 पूर्ण,
	अणु GC2235_8BIT, 0x09, 0x00 पूर्ण, /* row start */
	अणु GC2235_8BIT, 0x0a, 0xf0 पूर्ण,
	अणु GC2235_8BIT, 0x0b, 0x00 पूर्ण, /* col start */
	अणु GC2235_8BIT, 0x0c, 0xa0 पूर्ण,
	अणु GC2235_8BIT, 0x0d, 0x02 पूर्ण, /* win height 736 */
	अणु GC2235_8BIT, 0x0e, 0xf0 पूर्ण,
	अणु GC2235_8BIT, 0x0f, 0x05 पूर्ण, /* win width: 1296 */
	अणु GC2235_8BIT, 0x10, 0x20 पूर्ण,

	अणु GC2235_8BIT, 0x90, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x92, 0x08 पूर्ण,
	अणु GC2235_8BIT, 0x94, 0x08 पूर्ण,
	अणु GC2235_8BIT, 0x95, 0x02 पूर्ण, /* crop win height 736 */
	अणु GC2235_8BIT, 0x96, 0xe0 पूर्ण,
	अणु GC2235_8BIT, 0x97, 0x05 पूर्ण, /* crop win width 1296 */
	अणु GC2235_8BIT, 0x98, 0x10 पूर्ण,
	/* mimi init */
	अणु GC2235_8BIT, 0xfe, 0x03 पूर्ण, /* चयन to P3 */
	अणु GC2235_8BIT, 0x01, 0x07 पूर्ण,
	अणु GC2235_8BIT, 0x02, 0x11 पूर्ण,
	अणु GC2235_8BIT, 0x03, 0x11 पूर्ण,
	अणु GC2235_8BIT, 0x06, 0x80 पूर्ण,
	अणु GC2235_8BIT, 0x11, 0x2b पूर्ण,
	/* set mipi buffer */
	अणु GC2235_8BIT, 0x12, 0x54 पूर्ण, /* val_low = (width * 10 / 8) & 0xFF */
	अणु GC2235_8BIT, 0x13, 0x06 पूर्ण, /* val_high = (width * 10 / 8) >> 8 */

	अणु GC2235_8BIT, 0x15, 0x12 पूर्ण, /* DPHY mode*/
	अणु GC2235_8BIT, 0x04, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x05, 0x00 पूर्ण,
	अणु GC2235_8BIT, 0x17, 0x01 पूर्ण,

	अणु GC2235_8BIT, 0x22, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x23, 0x05 पूर्ण,
	अणु GC2235_8BIT, 0x24, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x25, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x26, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x21, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x29, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x2a, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x2b, 0x02 पूर्ण,

	अणु GC2235_8BIT, 0x10, 0x01 पूर्ण, /* disable mipi */
	अणु GC2235_8BIT, 0xfe, 0x00 पूर्ण, /* चयन to P0 */
	अणु GC2235_TOK_TERM, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा gc2235_reg स्थिर gc2235_960_640_30fps[] = अणु
	अणु GC2235_8BIT, 0x8b, 0xa0 पूर्ण,
	अणु GC2235_8BIT, 0x8c, 0x02 पूर्ण,

	अणु GC2235_8BIT, 0x07, 0x02 पूर्ण, /* VBI */
	अणु GC2235_8BIT, 0x08, 0xA4 पूर्ण,
	अणु GC2235_8BIT, 0x09, 0x01 पूर्ण, /* row start */
	अणु GC2235_8BIT, 0x0a, 0x18 पूर्ण,
	अणु GC2235_8BIT, 0x0b, 0x01 पूर्ण, /* col start */
	अणु GC2235_8BIT, 0x0c, 0x40 पूर्ण,
	अणु GC2235_8BIT, 0x0d, 0x02 पूर्ण, /* win height 656 */
	अणु GC2235_8BIT, 0x0e, 0x90 पूर्ण,
	अणु GC2235_8BIT, 0x0f, 0x03 पूर्ण, /* win width: 976 */
	अणु GC2235_8BIT, 0x10, 0xd0 पूर्ण,

	अणु GC2235_8BIT, 0x90, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x92, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x94, 0x06 पूर्ण,
	अणु GC2235_8BIT, 0x95, 0x02 पूर्ण, /* crop win height 640 */
	अणु GC2235_8BIT, 0x96, 0x80 पूर्ण,
	अणु GC2235_8BIT, 0x97, 0x03 पूर्ण, /* crop win width 960 */
	अणु GC2235_8BIT, 0x98, 0xc0 पूर्ण,
	/* mimp init */
	अणु GC2235_8BIT, 0xfe, 0x03 पूर्ण, /* चयन to P3 */
	अणु GC2235_8BIT, 0x01, 0x07 पूर्ण,
	अणु GC2235_8BIT, 0x02, 0x11 पूर्ण,
	अणु GC2235_8BIT, 0x03, 0x11 पूर्ण,
	अणु GC2235_8BIT, 0x06, 0x80 पूर्ण,
	अणु GC2235_8BIT, 0x11, 0x2b पूर्ण,
	/* set mipi buffer */
	अणु GC2235_8BIT, 0x12, 0xb0 पूर्ण, /* val_low = (width * 10 / 8) & 0xFF */
	अणु GC2235_8BIT, 0x13, 0x04 पूर्ण, /* val_high = (width * 10 / 8) >> 8 */

	अणु GC2235_8BIT, 0x15, 0x12 पूर्ण, /* DPHY mode*/
	अणु GC2235_8BIT, 0x04, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x05, 0x00 पूर्ण,
	अणु GC2235_8BIT, 0x17, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x22, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x23, 0x05 पूर्ण,
	अणु GC2235_8BIT, 0x24, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x25, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x26, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x21, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x29, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x2a, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x2b, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x10, 0x01 पूर्ण, /* disable mipi */
	अणु GC2235_8BIT, 0xfe, 0x00 पूर्ण, /* चयन to P0 */
	अणु GC2235_TOK_TERM, 0, 0 पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा gc2235_reg स्थिर gc2235_1600_900_30fps[] = अणु
	अणु GC2235_8BIT, 0x8b, 0xa0 पूर्ण,
	अणु GC2235_8BIT, 0x8c, 0x02 पूर्ण,

	अणु GC2235_8BIT, 0x0d, 0x03 पूर्ण, /* win height 932 */
	अणु GC2235_8BIT, 0x0e, 0xa4 पूर्ण,
	अणु GC2235_8BIT, 0x0f, 0x06 पूर्ण, /* win width: 1632 */
	अणु GC2235_8BIT, 0x10, 0x50 पूर्ण,

	अणु GC2235_8BIT, 0x90, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x92, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x94, 0x06 पूर्ण,
	अणु GC2235_8BIT, 0x95, 0x03 पूर्ण, /* crop win height 900 */
	अणु GC2235_8BIT, 0x96, 0x84 पूर्ण,
	अणु GC2235_8BIT, 0x97, 0x06 पूर्ण, /* crop win width 1600 */
	अणु GC2235_8BIT, 0x98, 0x40 पूर्ण,
	/* mimi init */
	अणु GC2235_8BIT, 0xfe, 0x03 पूर्ण, /* चयन to P3 */
	अणु GC2235_8BIT, 0x01, 0x07 पूर्ण,
	अणु GC2235_8BIT, 0x02, 0x11 पूर्ण,
	अणु GC2235_8BIT, 0x03, 0x11 पूर्ण,
	अणु GC2235_8BIT, 0x06, 0x80 पूर्ण,
	अणु GC2235_8BIT, 0x11, 0x2b पूर्ण,
	/* set mipi buffer */
	अणु GC2235_8BIT, 0x12, 0xd0 पूर्ण, /* val_low = (width * 10 / 8) & 0xFF */
	अणु GC2235_8BIT, 0x13, 0x07 पूर्ण, /* val_high = (width * 10 / 8) >> 8 */

	अणु GC2235_8BIT, 0x15, 0x12 पूर्ण, /* DPHY mode*/
	अणु GC2235_8BIT, 0x04, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x05, 0x00 पूर्ण,
	अणु GC2235_8BIT, 0x17, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x22, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x23, 0x05 पूर्ण,
	अणु GC2235_8BIT, 0x24, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x25, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x26, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x21, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x29, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x2a, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x2b, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x10, 0x01 पूर्ण, /* disable mipi */
	अणु GC2235_8BIT, 0xfe, 0x00 पूर्ण, /* चयन to P0 */
	अणु GC2235_TOK_TERM, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा gc2235_reg स्थिर gc2235_1616_1082_30fps[] = अणु
	अणु GC2235_8BIT, 0x8b, 0xa0 पूर्ण,
	अणु GC2235_8BIT, 0x8c, 0x02 पूर्ण,

	अणु GC2235_8BIT, 0x0d, 0x04 पूर्ण, /* win height 1232 */
	अणु GC2235_8BIT, 0x0e, 0xd0 पूर्ण,
	अणु GC2235_8BIT, 0x0f, 0x06 पूर्ण, /* win width: 1616 */
	अणु GC2235_8BIT, 0x10, 0x50 पूर्ण,

	अणु GC2235_8BIT, 0x90, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x92, 0x4a पूर्ण,
	अणु GC2235_8BIT, 0x94, 0x00 पूर्ण,
	अणु GC2235_8BIT, 0x95, 0x04 पूर्ण, /* crop win height 1082 */
	अणु GC2235_8BIT, 0x96, 0x3a पूर्ण,
	अणु GC2235_8BIT, 0x97, 0x06 पूर्ण, /* crop win width 1616 */
	अणु GC2235_8BIT, 0x98, 0x50 पूर्ण,
	/* mimp init */
	अणु GC2235_8BIT, 0xfe, 0x03 पूर्ण, /* चयन to P3 */
	अणु GC2235_8BIT, 0x01, 0x07 पूर्ण,
	अणु GC2235_8BIT, 0x02, 0x11 पूर्ण,
	अणु GC2235_8BIT, 0x03, 0x11 पूर्ण,
	अणु GC2235_8BIT, 0x06, 0x80 पूर्ण,
	अणु GC2235_8BIT, 0x11, 0x2b पूर्ण,
	/* set mipi buffer */
	अणु GC2235_8BIT, 0x12, 0xe4 पूर्ण, /* val_low = (width * 10 / 8) & 0xFF */
	अणु GC2235_8BIT, 0x13, 0x07 पूर्ण, /* val_high = (width * 10 / 8) >> 8 */

	अणु GC2235_8BIT, 0x15, 0x12 पूर्ण, /* DPHY mode*/
	अणु GC2235_8BIT, 0x04, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x05, 0x00 पूर्ण,
	अणु GC2235_8BIT, 0x17, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x22, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x23, 0x05 पूर्ण,
	अणु GC2235_8BIT, 0x24, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x25, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x26, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x21, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x29, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x2a, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x2b, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x10, 0x01 पूर्ण, /* disable mipi */
	अणु GC2235_8BIT, 0xfe, 0x00 पूर्ण, /* चयन to P0 */
	अणु GC2235_TOK_TERM, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा gc2235_reg स्थिर gc2235_1616_1216_30fps[] = अणु
	अणु GC2235_8BIT, 0x8b, 0xa0 पूर्ण,
	अणु GC2235_8BIT, 0x8c, 0x02 पूर्ण,

	अणु GC2235_8BIT, 0x0d, 0x04 पूर्ण, /* win height 1232 */
	अणु GC2235_8BIT, 0x0e, 0xd0 पूर्ण,
	अणु GC2235_8BIT, 0x0f, 0x06 पूर्ण, /* win width: 1616 */
	अणु GC2235_8BIT, 0x10, 0x50 पूर्ण,

	अणु GC2235_8BIT, 0x90, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x92, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x94, 0x00 पूर्ण,
	अणु GC2235_8BIT, 0x95, 0x04 पूर्ण, /* crop win height 1216 */
	अणु GC2235_8BIT, 0x96, 0xc0 पूर्ण,
	अणु GC2235_8BIT, 0x97, 0x06 पूर्ण, /* crop win width 1616 */
	अणु GC2235_8BIT, 0x98, 0x50 पूर्ण,
	/* mimi init */
	अणु GC2235_8BIT, 0xfe, 0x03 पूर्ण, /* चयन to P3 */
	अणु GC2235_8BIT, 0x01, 0x07 पूर्ण,
	अणु GC2235_8BIT, 0x02, 0x11 पूर्ण,
	अणु GC2235_8BIT, 0x03, 0x11 पूर्ण,
	अणु GC2235_8BIT, 0x06, 0x80 पूर्ण,
	अणु GC2235_8BIT, 0x11, 0x2b पूर्ण,
	/* set mipi buffer */
	अणु GC2235_8BIT, 0x12, 0xe4 पूर्ण, /* val_low = (width * 10 / 8) & 0xFF */
	अणु GC2235_8BIT, 0x13, 0x07 पूर्ण, /* val_high = (width * 10 / 8) >> 8 */
	अणु GC2235_8BIT, 0x15, 0x12 पूर्ण, /* DPHY mode*/
	अणु GC2235_8BIT, 0x04, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x05, 0x00 पूर्ण,
	अणु GC2235_8BIT, 0x17, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x22, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x23, 0x05 पूर्ण,
	अणु GC2235_8BIT, 0x24, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x25, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x26, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x21, 0x10 पूर्ण,
	अणु GC2235_8BIT, 0x29, 0x01 पूर्ण,
	अणु GC2235_8BIT, 0x2a, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x2b, 0x02 पूर्ण,
	अणु GC2235_8BIT, 0x10, 0x01 पूर्ण, /* disable mipi */
	अणु GC2235_8BIT, 0xfe, 0x00 पूर्ण, /* चयन to P0 */
	अणु GC2235_TOK_TERM, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा gc2235_resolution gc2235_res_preview[] = अणु
	अणु
		.desc = "gc2235_1600_900_30fps",
		.width = 1600,
		.height = 900,
		.pix_clk_freq = 30,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2132,
		.lines_per_frame = 1068,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = gc2235_1600_900_30fps,
	पूर्ण,

	अणु
		.desc = "gc2235_1600_1066_30fps",
		.width = 1616,
		.height = 1082,
		.pix_clk_freq = 30,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2132,
		.lines_per_frame = 1368,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = gc2235_1616_1082_30fps,
	पूर्ण,
	अणु
		.desc = "gc2235_1600_1200_30fps",
		.width = 1616,
		.height = 1216,
		.pix_clk_freq = 30,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2132,
		.lines_per_frame = 1368,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = gc2235_1616_1216_30fps,
	पूर्ण,

पूर्ण;

#घोषणा N_RES_PREVIEW (ARRAY_SIZE(gc2235_res_preview))

/*
 * Disable non-preview configurations until the configuration selection is
 * improved.
 */
#अगर ENABLE_NON_PREVIEW
अटल काष्ठा gc2235_resolution gc2235_res_still[] = अणु
	अणु
		.desc = "gc2235_1600_900_30fps",
		.width = 1600,
		.height = 900,
		.pix_clk_freq = 30,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2132,
		.lines_per_frame = 1068,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = gc2235_1600_900_30fps,
	पूर्ण,
	अणु
		.desc = "gc2235_1600_1066_30fps",
		.width = 1616,
		.height = 1082,
		.pix_clk_freq = 30,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2132,
		.lines_per_frame = 1368,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = gc2235_1616_1082_30fps,
	पूर्ण,
	अणु
		.desc = "gc2235_1600_1200_30fps",
		.width = 1616,
		.height = 1216,
		.pix_clk_freq = 30,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 2132,
		.lines_per_frame = 1368,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = gc2235_1616_1216_30fps,
	पूर्ण,

पूर्ण;

#घोषणा N_RES_STILL (ARRAY_SIZE(gc2235_res_still))

अटल काष्ठा gc2235_resolution gc2235_res_video[] = अणु
	अणु
		.desc = "gc2235_1296_736_30fps",
		.width = 1296,
		.height = 736,
		.pix_clk_freq = 30,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 1828,
		.lines_per_frame = 888,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = gc2235_1296_736_30fps,
	पूर्ण,
	अणु
		.desc = "gc2235_960_640_30fps",
		.width = 960,
		.height = 640,
		.pix_clk_freq = 30,
		.fps = 30,
		.used = 0,
		.pixels_per_line = 1492,
		.lines_per_frame = 792,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.bin_mode = 0,
		.skip_frames = 3,
		.regs = gc2235_960_640_30fps,
	पूर्ण,

पूर्ण;

#घोषणा N_RES_VIDEO (ARRAY_SIZE(gc2235_res_video))
#पूर्ण_अगर

अटल काष्ठा gc2235_resolution *gc2235_res = gc2235_res_preview;
अटल अचिन्हित दीर्घ N_RES = N_RES_PREVIEW;
#पूर्ण_अगर
