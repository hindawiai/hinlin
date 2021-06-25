<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम GalaxyCore GC0310 VGA camera sensor.
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

#अगर_अघोषित __GC0310_H__
#घोषणा __GC0310_H__
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/spinlock.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <media/media-entity.h>

#समावेश "../include/linux/atomisp_platform.h"

/* Defines क्रम रेजिस्टर ग_लिखोs and रेजिस्टर array processing */
#घोषणा I2C_MSG_LENGTH		1
#घोषणा I2C_RETRY_COUNT		5

#घोषणा GC0310_FOCAL_LENGTH_NUM	278	/*2.78mm*/
#घोषणा GC0310_FOCAL_LENGTH_DEM	100
#घोषणा GC0310_F_NUMBER_DEFAULT_NUM	26
#घोषणा GC0310_F_NUMBER_DEM	10

#घोषणा MAX_FMTS		1

/*
 * focal length bits definition:
 * bits 31-16: numerator, bits 15-0: denominator
 */
#घोषणा GC0310_FOCAL_LENGTH_DEFAULT 0x1160064

/*
 * current f-number bits definition:
 * bits 31-16: numerator, bits 15-0: denominator
 */
#घोषणा GC0310_F_NUMBER_DEFAULT 0x1a000a

/*
 * f-number range bits definition:
 * bits 31-24: max f-number numerator
 * bits 23-16: max f-number denominator
 * bits 15-8: min f-number numerator
 * bits 7-0: min f-number denominator
 */
#घोषणा GC0310_F_NUMBER_RANGE 0x1a0a1a0a
#घोषणा GC0310_ID	0xa310

#घोषणा GC0310_RESET_RELATED		0xFE
#घोषणा GC0310_REGISTER_PAGE_0		0x0
#घोषणा GC0310_REGISTER_PAGE_3		0x3

#घोषणा GC0310_FINE_INTG_TIME_MIN 0
#घोषणा GC0310_FINE_INTG_TIME_MAX_MARGIN 0
#घोषणा GC0310_COARSE_INTG_TIME_MIN 1
#घोषणा GC0310_COARSE_INTG_TIME_MAX_MARGIN 6

/*
 * GC0310 System control रेजिस्टरs
 */
#घोषणा GC0310_SW_STREAM			0x10

#घोषणा GC0310_SC_CMMN_CHIP_ID_H		0xf0
#घोषणा GC0310_SC_CMMN_CHIP_ID_L		0xf1

#घोषणा GC0310_AEC_PK_EXPO_H			0x03
#घोषणा GC0310_AEC_PK_EXPO_L			0x04
#घोषणा GC0310_AGC_ADJ			0x48
#घोषणा GC0310_DGC_ADJ			0x71
#अगर 0
#घोषणा GC0310_GROUP_ACCESS			0x3208
#पूर्ण_अगर

#घोषणा GC0310_H_CROP_START_H			0x09
#घोषणा GC0310_H_CROP_START_L			0x0A
#घोषणा GC0310_V_CROP_START_H			0x0B
#घोषणा GC0310_V_CROP_START_L			0x0C
#घोषणा GC0310_H_OUTSIZE_H			0x0F
#घोषणा GC0310_H_OUTSIZE_L			0x10
#घोषणा GC0310_V_OUTSIZE_H			0x0D
#घोषणा GC0310_V_OUTSIZE_L			0x0E
#घोषणा GC0310_H_BLANKING_H			0x05
#घोषणा GC0310_H_BLANKING_L			0x06
#घोषणा GC0310_V_BLANKING_H			0x07
#घोषणा GC0310_V_BLANKING_L			0x08
#घोषणा GC0310_SH_DELAY			0x11

#घोषणा GC0310_START_STREAMING			0x94 /* 8-bit enable */
#घोषणा GC0310_STOP_STREAMING			0x0 /* 8-bit disable */

#घोषणा GC0310_BIN_FACTOR_MAX			3

काष्ठा regval_list अणु
	u16 reg_num;
	u8 value;
पूर्ण;

काष्ठा gc0310_resolution अणु
	u8 *desc;
	स्थिर काष्ठा gc0310_reg *regs;
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

काष्ठा gc0310_क्रमmat अणु
	u8 *desc;
	u32 pixelक्रमmat;
	काष्ठा gc0310_reg *regs;
पूर्ण;

/*
 * gc0310 device काष्ठाure.
 */
काष्ठा gc0310_device अणु
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

क्रमागत gc0310_tok_type अणु
	GC0310_8BIT  = 0x0001,
	GC0310_TOK_TERM   = 0xf000,	/* terminating token क्रम reg list */
	GC0310_TOK_DELAY  = 0xfe00,	/* delay token क्रम reg list */
	GC0310_TOK_MASK = 0xfff0
पूर्ण;

/**
 * काष्ठा gc0310_reg - MI sensor  रेजिस्टर क्रमmat
 * @type: type of the रेजिस्टर
 * @reg: 16-bit offset to रेजिस्टर
 * @val: 8/16/32-bit रेजिस्टर value
 *
 * Define a काष्ठाure क्रम sensor रेजिस्टर initialization values
 */
काष्ठा gc0310_reg अणु
	क्रमागत gc0310_tok_type type;
	u8 reg;
	u8 val;	/* @set value क्रम पढ़ो/mod/ग_लिखो, @mask */
पूर्ण;

#घोषणा to_gc0310_sensor(x) container_of(x, काष्ठा gc0310_device, sd)

#घोषणा GC0310_MAX_WRITE_BUF_SIZE	30

काष्ठा gc0310_ग_लिखो_buffer अणु
	u8 addr;
	u8 data[GC0310_MAX_WRITE_BUF_SIZE];
पूर्ण;

काष्ठा gc0310_ग_लिखो_ctrl अणु
	पूर्णांक index;
	काष्ठा gc0310_ग_लिखो_buffer buffer;
पूर्ण;

/*
 * Register settings क्रम various resolution
 */
अटल स्थिर काष्ठा gc0310_reg gc0310_reset_रेजिस्टर[] = अणु
/////////////////////////////////////////////////
/////////////////	प्रणाली reg	/////////////////
/////////////////////////////////////////////////
	अणुGC0310_8BIT, 0xfe, 0xf0पूर्ण,
	अणुGC0310_8BIT, 0xfe, 0xf0पूर्ण,
	अणुGC0310_8BIT, 0xfe, 0x00पूर्ण,

	अणुGC0310_8BIT, 0xfc, 0x0eपूर्ण, //4e
	अणुGC0310_8BIT, 0xfc, 0x0eपूर्ण, //16//4e // [0]apwd [6]regf_clk_gate
	अणुGC0310_8BIT, 0xf2, 0x80पूर्ण, //sync output
	अणुGC0310_8BIT, 0xf3, 0x00पूर्ण, //1f//01 data output
	अणुGC0310_8BIT, 0xf7, 0x33पूर्ण, //f9
	अणुGC0310_8BIT, 0xf8, 0x05पूर्ण, //00
	अणुGC0310_8BIT, 0xf9, 0x0eपूर्ण, // 0x8e //0f
	अणुGC0310_8BIT, 0xfa, 0x11पूर्ण,

/////////////////////////////////////////////////
///////////////////   MIPI	 ////////////////////
/////////////////////////////////////////////////
	अणुGC0310_8BIT, 0xfe, 0x03पूर्ण,
	अणुGC0310_8BIT, 0x01, 0x03पूर्ण, ///mipi 1lane
	अणुGC0310_8BIT, 0x02, 0x22पूर्ण, // 0x33
	अणुGC0310_8BIT, 0x03, 0x94पूर्ण,
	अणुGC0310_8BIT, 0x04, 0x01पूर्ण, // fअगरo_prog
	अणुGC0310_8BIT, 0x05, 0x00पूर्ण, //fअगरo_prog
	अणुGC0310_8BIT, 0x06, 0x80पूर्ण, //b0  //YUV ISP data
	अणुGC0310_8BIT, 0x11, 0x2aपूर्ण,//1e //LDI set YUV422
	अणुGC0310_8BIT, 0x12, 0x90पूर्ण,//00 //04 //00 //04//00 //LWC[7:0]  //
	अणुGC0310_8BIT, 0x13, 0x02पूर्ण,//05 //05 //LWC[15:8]
	अणुGC0310_8BIT, 0x15, 0x12पूर्ण, // 0x10 //DPHYY_MODE पढ़ो_पढ़ोy
	अणुGC0310_8BIT, 0x17, 0x01पूर्ण,
	अणुGC0310_8BIT, 0x40, 0x08पूर्ण,
	अणुGC0310_8BIT, 0x41, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x42, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x43, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x21, 0x02पूर्ण, // 0x01
	अणुGC0310_8BIT, 0x22, 0x02पूर्ण, // 0x01
	अणुGC0310_8BIT, 0x23, 0x01पूर्ण, // 0x05 //Nor:0x05 DOU:0x06
	अणुGC0310_8BIT, 0x29, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x2A, 0x25पूर्ण, // 0x05 //data zero 0x7a de
	अणुGC0310_8BIT, 0x2B, 0x02पूर्ण,

	अणुGC0310_8BIT, 0xfe, 0x00पूर्ण,

/////////////////////////////////////////////////
/////////////////	CISCTL reg	/////////////////
/////////////////////////////////////////////////
	अणुGC0310_8BIT, 0x00, 0x2fपूर्ण, //2f//0f//02//01
	अणुGC0310_8BIT, 0x01, 0x0fपूर्ण, //06
	अणुGC0310_8BIT, 0x02, 0x04पूर्ण,
	अणुGC0310_8BIT, 0x4f, 0x00पूर्ण, //AEC 0FF
	अणुGC0310_8BIT, 0x03, 0x01पूर्ण, // 0x03 //04
	अणुGC0310_8BIT, 0x04, 0xc0पूर्ण, // 0xe8 //58
	अणुGC0310_8BIT, 0x05, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x06, 0xb2पूर्ण, // 0x0a //HB
	अणुGC0310_8BIT, 0x07, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x08, 0x0cपूर्ण, // 0x89 //VB
	अणुGC0310_8BIT, 0x09, 0x00पूर्ण, //row start
	अणुGC0310_8BIT, 0x0a, 0x00पूर्ण, //
	अणुGC0310_8BIT, 0x0b, 0x00पूर्ण, //col start
	अणुGC0310_8BIT, 0x0c, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x0d, 0x01पूर्ण, //height
	अणुGC0310_8BIT, 0x0e, 0xf2पूर्ण, // 0xf7 //height
	अणुGC0310_8BIT, 0x0f, 0x02पूर्ण, //width
	अणुGC0310_8BIT, 0x10, 0x94पूर्ण, // 0xa0 //height
	अणुGC0310_8BIT, 0x17, 0x14पूर्ण,
	अणुGC0310_8BIT, 0x18, 0x1aपूर्ण, //0a//[4]द्विगुन reset
	अणुGC0310_8BIT, 0x19, 0x14पूर्ण, //AD pipeline
	अणुGC0310_8BIT, 0x1b, 0x48पूर्ण,
	अणुGC0310_8BIT, 0x1e, 0x6bपूर्ण, //3b//col bias
	अणुGC0310_8BIT, 0x1f, 0x28पूर्ण, //20//00//08//txlow
	अणुGC0310_8BIT, 0x20, 0x89पूर्ण, //88//0c//[3:2]DA15
	अणुGC0310_8BIT, 0x21, 0x49पूर्ण, //48//[3] txhigh
	अणुGC0310_8BIT, 0x22, 0xb0पूर्ण,
	अणुGC0310_8BIT, 0x23, 0x04पूर्ण, //[1:0]vcm_r
	अणुGC0310_8BIT, 0x24, 0x16पूर्ण, //15
	अणुGC0310_8BIT, 0x34, 0x20पूर्ण, //[6:4] rsg high//range

/////////////////////////////////////////////////
////////////////////   BLK	 ////////////////////
/////////////////////////////////////////////////
	अणुGC0310_8BIT, 0x26, 0x23पूर्ण, //[1]dark_current_en [0]offset_en
	अणुGC0310_8BIT, 0x28, 0xffपूर्ण, //BLK_limie_value
	अणुGC0310_8BIT, 0x29, 0x00पूर्ण, //global offset
	अणुGC0310_8BIT, 0x33, 0x18पूर्ण, //offset_ratio
	अणुGC0310_8BIT, 0x37, 0x20पूर्ण, //dark_current_ratio
	अणुGC0310_8BIT, 0x2a, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x2b, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x2c, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x2d, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x2e, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x2f, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x30, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x31, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x47, 0x80पूर्ण, //a7
	अणुGC0310_8BIT, 0x4e, 0x66पूर्ण, //select_row
	अणुGC0310_8BIT, 0xa8, 0x02पूर्ण, //win_width_dark, same with crop_win_width
	अणुGC0310_8BIT, 0xa9, 0x80पूर्ण,

/////////////////////////////////////////////////
//////////////////	 ISP reg  ///////////////////
/////////////////////////////////////////////////
	अणुGC0310_8BIT, 0x40, 0x06पूर्ण, // 0xff //ff //48
	अणुGC0310_8BIT, 0x41, 0x00पूर्ण, // 0x21 //00//[0]curve_en
	अणुGC0310_8BIT, 0x42, 0x04पूर्ण, // 0xcf //0a//[1]awn_en
	अणुGC0310_8BIT, 0x44, 0x18पूर्ण, // 0x18 //02
	अणुGC0310_8BIT, 0x46, 0x02पूर्ण, // 0x03 //sync
	अणुGC0310_8BIT, 0x49, 0x03पूर्ण,
	अणुGC0310_8BIT, 0x4c, 0x20पूर्ण, //00[5]pretect exp
	अणुGC0310_8BIT, 0x50, 0x01पूर्ण, //crop enable
	अणुGC0310_8BIT, 0x51, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x52, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x53, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x54, 0x01पूर्ण,
	अणुGC0310_8BIT, 0x55, 0x01पूर्ण, //crop winकरोw height
	अणुGC0310_8BIT, 0x56, 0xf0पूर्ण,
	अणुGC0310_8BIT, 0x57, 0x02पूर्ण, //crop winकरोw width
	अणुGC0310_8BIT, 0x58, 0x90पूर्ण,

/////////////////////////////////////////////////
///////////////////   GAIN	 ////////////////////
/////////////////////////////////////////////////
	अणुGC0310_8BIT, 0x70, 0x70पूर्ण, //70 //80//global gain
	अणुGC0310_8BIT, 0x71, 0x20पूर्ण, // pregain gain
	अणुGC0310_8BIT, 0x72, 0x40पूर्ण, // post gain
	अणुGC0310_8BIT, 0x5a, 0x84पूर्ण, //84//analog gain 0
	अणुGC0310_8BIT, 0x5b, 0xc9पूर्ण, //c9
	अणुGC0310_8BIT, 0x5c, 0xedपूर्ण, //ed//not use pga gain highest level
	अणुGC0310_8BIT, 0x77, 0x40पूर्ण, // R gain 0x74 //awb gain
	अणुGC0310_8BIT, 0x78, 0x40पूर्ण, // G gain
	अणुGC0310_8BIT, 0x79, 0x40पूर्ण, // B gain 0x5f

	अणुGC0310_8BIT, 0x48, 0x00पूर्ण,
	अणुGC0310_8BIT, 0xfe, 0x01पूर्ण,
	अणुGC0310_8BIT, 0x0a, 0x45पूर्ण, //[7]col gain mode

	अणुGC0310_8BIT, 0x3e, 0x40पूर्ण,
	अणुGC0310_8BIT, 0x3f, 0x5cपूर्ण,
	अणुGC0310_8BIT, 0x40, 0x7bपूर्ण,
	अणुGC0310_8BIT, 0x41, 0xbdपूर्ण,
	अणुGC0310_8BIT, 0x42, 0xf6पूर्ण,
	अणुGC0310_8BIT, 0x43, 0x63पूर्ण,
	अणुGC0310_8BIT, 0x03, 0x60पूर्ण,
	अणुGC0310_8BIT, 0x44, 0x03पूर्ण,

/////////////////////////////////////////////////
/////////////////	dark sun   //////////////////
/////////////////////////////////////////////////
	अणुGC0310_8BIT, 0xfe, 0x01पूर्ण,
	अणुGC0310_8BIT, 0x45, 0xa4पूर्ण, // 0xf7
	अणुGC0310_8BIT, 0x46, 0xf0पूर्ण, // 0xff //f0//sun value th
	अणुGC0310_8BIT, 0x48, 0x03पूर्ण, //sun mode
	अणुGC0310_8BIT, 0x4f, 0x60पूर्ण, //sun_clamp
	अणुGC0310_8BIT, 0xfe, 0x00पूर्ण,

	अणुGC0310_TOK_TERM, 0, 0पूर्ण,
पूर्ण;

अटल काष्ठा gc0310_reg स्थिर gc0310_VGA_30fps[] = अणु
	अणुGC0310_8BIT, 0xfe, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x0d, 0x01पूर्ण, //height
	अणुGC0310_8BIT, 0x0e, 0xf2पूर्ण, // 0xf7 //height
	अणुGC0310_8BIT, 0x0f, 0x02पूर्ण, //width
	अणुGC0310_8BIT, 0x10, 0x94पूर्ण, // 0xa0 //height

	अणुGC0310_8BIT, 0x50, 0x01पूर्ण, //crop enable
	अणुGC0310_8BIT, 0x51, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x52, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x53, 0x00पूर्ण,
	अणुGC0310_8BIT, 0x54, 0x01पूर्ण,
	अणुGC0310_8BIT, 0x55, 0x01पूर्ण, //crop winकरोw height
	अणुGC0310_8BIT, 0x56, 0xf0पूर्ण,
	अणुGC0310_8BIT, 0x57, 0x02पूर्ण, //crop winकरोw width
	अणुGC0310_8BIT, 0x58, 0x90पूर्ण,

	अणुGC0310_8BIT, 0xfe, 0x03पूर्ण,
	अणुGC0310_8BIT, 0x12, 0x90पूर्ण,//00 //04 //00 //04//00 //LWC[7:0]  //
	अणुGC0310_8BIT, 0x13, 0x02पूर्ण,//05 //05 //LWC[15:8]

	अणुGC0310_8BIT, 0xfe, 0x00पूर्ण,

	अणुGC0310_TOK_TERM, 0, 0पूर्ण,
पूर्ण;

अटल काष्ठा gc0310_resolution gc0310_res_preview[] = अणु
	अणु
		.desc = "gc0310_VGA_30fps",
		.width = 656, // 648,
		.height = 496, // 488,
		.fps = 30,
		//.pix_clk_freq = 73,
		.used = 0,
#अगर 0
		.pixels_per_line = 0x0314,
		.lines_per_frame = 0x0213,
#पूर्ण_अगर
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
		.skip_frames = 2,
		.regs = gc0310_VGA_30fps,
	पूर्ण,
पूर्ण;

#घोषणा N_RES_PREVIEW (ARRAY_SIZE(gc0310_res_preview))

अटल काष्ठा gc0310_resolution *gc0310_res = gc0310_res_preview;
अटल अचिन्हित दीर्घ N_RES = N_RES_PREVIEW;
#पूर्ण_अगर
