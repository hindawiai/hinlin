<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम mt9m114 Camera Sensor.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
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

#अगर_अघोषित __A1040_H__
#घोषणा __A1040_H__

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
#समावेश "../include/linux/atomisp.h"

#घोषणा V4L2_IDENT_MT9M114 8245

#घोषणा MT9P111_REV3
#घोषणा FULLINISUPPORT

/* #घोषणाs क्रम रेजिस्टर ग_लिखोs and रेजिस्टर array processing */
#घोषणा MISENSOR_8BIT		1
#घोषणा MISENSOR_16BIT		2
#घोषणा MISENSOR_32BIT		4

#घोषणा MISENSOR_FWBURST0	0x80
#घोषणा MISENSOR_FWBURST1	0x81
#घोषणा MISENSOR_FWBURST4	0x84
#घोषणा MISENSOR_FWBURST	0x88

#घोषणा MISENSOR_TOK_TERM	0xf000	/* terminating token क्रम reg list */
#घोषणा MISENSOR_TOK_DELAY	0xfe00	/* delay token क्रम reg list */
#घोषणा MISENSOR_TOK_FWLOAD	0xfd00	/* token indicating load FW */
#घोषणा MISENSOR_TOK_POLL	0xfc00	/* token indicating poll inकाष्ठाion */
#घोषणा MISENSOR_TOK_RMW	0x0010  /* RMW operation */
#घोषणा MISENSOR_TOK_MASK	0xfff0
#घोषणा MISENSOR_AWB_STEADY	BIT(0)	/* awb steady */
#घोषणा MISENSOR_AE_READY	BIT(3)	/* ae status पढ़ोy */

/* mask to set sensor पढ़ो_mode via misensor_rmw_reg */
#घोषणा MISENSOR_R_MODE_MASK	0x0330
/* mask to set sensor vert_flip and horz_mirror */
#घोषणा MISENSOR_VFLIP_MASK	0x0002
#घोषणा MISENSOR_HFLIP_MASK	0x0001
#घोषणा MISENSOR_FLIP_EN	1
#घोषणा MISENSOR_FLIP_DIS	0

/* bits set to set sensor पढ़ो_mode via misensor_rmw_reg */
#घोषणा MISENSOR_SKIPPING_SET	0x0011
#घोषणा MISENSOR_SUMMING_SET	0x0033
#घोषणा MISENSOR_NORMAL_SET	0x0000

/* sensor रेजिस्टर that control sensor पढ़ो-mode and mirror */
#घोषणा MISENSOR_READ_MODE	0xC834
/* sensor ae-track status रेजिस्टर */
#घोषणा MISENSOR_AE_TRACK_STATUS	0xA800
/* sensor awb status रेजिस्टर */
#घोषणा MISENSOR_AWB_STATUS	0xAC00
/* sensor coarse पूर्णांकegration समय रेजिस्टर */
#घोषणा MISENSOR_COARSE_INTEGRATION_TIME 0xC83C

/* रेजिस्टरs */
#घोषणा REG_SW_RESET                    0x301A
#घोषणा REG_SW_STREAM                   0xDC00
#घोषणा REG_SCCB_CTRL                   0x3100
#घोषणा REG_SC_CMMN_CHIP_ID             0x0000
#घोषणा REG_V_START                     0xc800 /* 16bits */
#घोषणा REG_H_START                     0xc802 /* 16bits */
#घोषणा REG_V_END                       0xc804 /* 16bits */
#घोषणा REG_H_END                       0xc806 /* 16bits */
#घोषणा REG_PIXEL_CLK                   0xc808 /* 32bits */
#घोषणा REG_TIMING_VTS                  0xc812 /* 16bits */
#घोषणा REG_TIMING_HTS                  0xc814 /* 16bits */
#घोषणा REG_WIDTH                       0xC868 /* 16bits */
#घोषणा REG_HEIGHT                      0xC86A /* 16bits */
#घोषणा REG_EXPO_COARSE                 0x3012 /* 16bits */
#घोषणा REG_EXPO_FINE                   0x3014 /* 16bits */
#घोषणा REG_GAIN                        0x305E
#घोषणा REG_ANALOGGAIN                  0x305F
#घोषणा REG_ADDR_ACESSS                 0x098E /* logical_address_access */
#घोषणा REG_COMM_Register               0x0080 /* command_रेजिस्टर */

#घोषणा SENSOR_DETECTED		1
#घोषणा SENSOR_NOT_DETECTED	0

#घोषणा I2C_RETRY_COUNT		5
#घोषणा MSG_LEN_OFFSET		2

#अगर_अघोषित MIPI_CONTROL
#घोषणा MIPI_CONTROL		0x3400	/* MIPI_Control */
#पूर्ण_अगर

/* GPIO pin on Moorestown */
#घोषणा GPIO_SCLK_25		44
#घोषणा GPIO_STB_PIN		47

#घोषणा GPIO_STDBY_PIN		49   /* ab:new */
#घोषणा GPIO_RESET_PIN		50

/* System control रेजिस्टर क्रम Aptina A-1040SOC*/
#घोषणा MT9M114_PID		0x0

/* MT9P111_DEVICE_ID */
#घोषणा MT9M114_MOD_ID		0x2481

#घोषणा MT9M114_FINE_INTG_TIME_MIN 0
#घोषणा MT9M114_FINE_INTG_TIME_MAX_MARGIN 0
#घोषणा MT9M114_COARSE_INTG_TIME_MIN 1
#घोषणा MT9M114_COARSE_INTG_TIME_MAX_MARGIN 6

/* ulBPat; */

#घोषणा MT9M114_BPAT_RGRGGBGB	BIT(0)
#घोषणा MT9M114_BPAT_GRGRBGBG	BIT(1)
#घोषणा MT9M114_BPAT_GBGBRGRG	BIT(2)
#घोषणा MT9M114_BPAT_BGBGGRGR	BIT(3)

#घोषणा MT9M114_FOCAL_LENGTH_NUM	208	/*2.08mm*/
#घोषणा MT9M114_FOCAL_LENGTH_DEM	100
#घोषणा MT9M114_F_NUMBER_DEFAULT_NUM	24
#घोषणा MT9M114_F_NUMBER_DEM	10
#घोषणा MT9M114_WAIT_STAT_TIMEOUT	100
#घोषणा MT9M114_FLICKER_MODE_50HZ	1
#घोषणा MT9M114_FLICKER_MODE_60HZ	2
/*
 * focal length bits definition:
 * bits 31-16: numerator, bits 15-0: denominator
 */
#घोषणा MT9M114_FOCAL_LENGTH_DEFAULT 0xD00064

/*
 * current f-number bits definition:
 * bits 31-16: numerator, bits 15-0: denominator
 */
#घोषणा MT9M114_F_NUMBER_DEFAULT 0x18000a

/*
 * f-number range bits definition:
 * bits 31-24: max f-number numerator
 * bits 23-16: max f-number denominator
 * bits 15-8: min f-number numerator
 * bits 7-0: min f-number denominator
 */
#घोषणा MT9M114_F_NUMBER_RANGE 0x180a180a

/* Supported resolutions */
क्रमागत अणु
	MT9M114_RES_736P,
	MT9M114_RES_864P,
	MT9M114_RES_960P,
पूर्ण;

#घोषणा MT9M114_RES_960P_SIZE_H		1296
#घोषणा MT9M114_RES_960P_SIZE_V		976
#घोषणा MT9M114_RES_720P_SIZE_H		1280
#घोषणा MT9M114_RES_720P_SIZE_V		720
#घोषणा MT9M114_RES_576P_SIZE_H		1024
#घोषणा MT9M114_RES_576P_SIZE_V		576
#घोषणा MT9M114_RES_480P_SIZE_H		768
#घोषणा MT9M114_RES_480P_SIZE_V		480
#घोषणा MT9M114_RES_VGA_SIZE_H		640
#घोषणा MT9M114_RES_VGA_SIZE_V		480
#घोषणा MT9M114_RES_QVGA_SIZE_H		320
#घोषणा MT9M114_RES_QVGA_SIZE_V		240
#घोषणा MT9M114_RES_QCIF_SIZE_H		176
#घोषणा MT9M114_RES_QCIF_SIZE_V		144

#घोषणा MT9M114_RES_720_480p_768_SIZE_H 736
#घोषणा MT9M114_RES_720_480p_768_SIZE_V 496
#घोषणा MT9M114_RES_736P_SIZE_H 1296
#घोषणा MT9M114_RES_736P_SIZE_V 736
#घोषणा MT9M114_RES_864P_SIZE_H 1296
#घोषणा MT9M114_RES_864P_SIZE_V 864
#घोषणा MT9M114_RES_976P_SIZE_H 1296
#घोषणा MT9M114_RES_976P_SIZE_V 976

#घोषणा MT9M114_BIN_FACTOR_MAX			3

#घोषणा MT9M114_DEFAULT_FIRST_EXP 0x10
#घोषणा MT9M114_MAX_FIRST_EXP 0x302

/* completion status polling requirements, usage based on Aptina .INI Rev2 */
क्रमागत poll_reg अणु
	NO_POLLING,
	PRE_POLLING,
	POST_POLLING,
पूर्ण;

/*
 * काष्ठा misensor_reg - MI sensor  रेजिस्टर क्रमmat
 * @length: length of the रेजिस्टर
 * @reg: 16-bit offset to रेजिस्टर
 * @val: 8/16/32-bit रेजिस्टर value
 * Define a काष्ठाure क्रम sensor रेजिस्टर initialization values
 */
काष्ठा misensor_reg अणु
	u32 length;
	u32 reg;
	u32 val;	/* value or क्रम पढ़ो/mod/ग_लिखो, AND mask */
	u32 val2;	/* optional; क्रम rmw, OR mask */
पूर्ण;

/*
 * काष्ठा misensor_fwreg - Firmware burst command
 * @type: FW burst or 8/16 bit रेजिस्टर
 * @addr: 16-bit offset to रेजिस्टर or other values depending on type
 * @valx: data value क्रम burst (or other commands)
 *
 * Define a काष्ठाure क्रम sensor रेजिस्टर initialization values
 */
काष्ठा misensor_fwreg अणु
	u32	type;	/* type of value, रेजिस्टर or FW burst string */
	u32	addr;	/* target address */
	u32	val0;
	u32	val1;
	u32	val2;
	u32	val3;
	u32	val4;
	u32	val5;
	u32	val6;
	u32	val7;
पूर्ण;

काष्ठा regval_list अणु
	u16 reg_num;
	u8 value;
पूर्ण;

काष्ठा mt9m114_device अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	काष्ठा camera_sensor_platक्रमm_data *platक्रमm_data;
	काष्ठा mutex input_lock;	/* serialize sensor's ioctl */
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	पूर्णांक real_model_id;
	पूर्णांक nctx;
	पूर्णांक घातer;

	अचिन्हित पूर्णांक bus_width;
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक field_inv;
	अचिन्हित पूर्णांक field_sel;
	अचिन्हित पूर्णांक ycseq;
	अचिन्हित पूर्णांक conv422;
	अचिन्हित पूर्णांक bpat;
	अचिन्हित पूर्णांक hpol;
	अचिन्हित पूर्णांक vpol;
	अचिन्हित पूर्णांक edge;
	अचिन्हित पूर्णांक bls;
	अचिन्हित पूर्णांक gamma;
	अचिन्हित पूर्णांक cconv;
	अचिन्हित पूर्णांक res;
	अचिन्हित पूर्णांक dwn_sz;
	अचिन्हित पूर्णांक blc;
	अचिन्हित पूर्णांक agc;
	अचिन्हित पूर्णांक awb;
	अचिन्हित पूर्णांक aec;
	/* extension SENSOR version 2 */
	अचिन्हित पूर्णांक cie_profile;

	/* extension SENSOR version 3 */
	अचिन्हित पूर्णांक flicker_freq;

	/* extension SENSOR version 4 */
	अचिन्हित पूर्णांक smia_mode;
	अचिन्हित पूर्णांक mipi_mode;

	/* Add name here to load shared library */
	अचिन्हित पूर्णांक type;

	/*Number of MIPI lanes*/
	अचिन्हित पूर्णांक mipi_lanes;
	/*WA क्रम low light AE*/
	अचिन्हित पूर्णांक first_exp;
	अचिन्हित पूर्णांक first_gain;
	अचिन्हित पूर्णांक first_diggain;
	अक्षर name[32];

	u8 lightfreq;
	u8 streamon;
पूर्ण;

काष्ठा mt9m114_क्रमmat_काष्ठा अणु
	u8 *desc;
	u32 pixelक्रमmat;
	काष्ठा regval_list *regs;
पूर्ण;

काष्ठा mt9m114_res_काष्ठा अणु
	u8 *desc;
	पूर्णांक res;
	पूर्णांक width;
	पूर्णांक height;
	पूर्णांक fps;
	पूर्णांक skip_frames;
	bool used;
	काष्ठा regval_list *regs;
	u16 pixels_per_line;
	u16 lines_per_frame;
	u8 bin_factor_x;
	u8 bin_factor_y;
	u8 bin_mode;
पूर्ण;

/* 2 bytes used क्रम address: 256 bytes total */
#घोषणा MT9M114_MAX_WRITE_BUF_SIZE	254
काष्ठा mt9m114_ग_लिखो_buffer अणु
	u16 addr;
	u8 data[MT9M114_MAX_WRITE_BUF_SIZE];
पूर्ण;

काष्ठा mt9m114_ग_लिखो_ctrl अणु
	पूर्णांक index;
	काष्ठा mt9m114_ग_लिखो_buffer buffer;
पूर्ण;

/*
 * Modes supported by the mt9m114 driver.
 * Please, keep them in ascending order.
 */
अटल काष्ठा mt9m114_res_काष्ठा mt9m114_res[] = अणु
	अणु
		.desc	= "720P",
		.res	= MT9M114_RES_736P,
		.width	= 1296,
		.height = 736,
		.fps	= 30,
		.used	= false,
		.regs	= शून्य,
		.skip_frames = 1,

		.pixels_per_line = 0x0640,
		.lines_per_frame = 0x0307,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
	पूर्ण,
	अणु
		.desc	= "848P",
		.res	= MT9M114_RES_864P,
		.width	= 1296,
		.height = 864,
		.fps	= 30,
		.used	= false,
		.regs	= शून्य,
		.skip_frames = 1,

		.pixels_per_line = 0x0640,
		.lines_per_frame = 0x03E8,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
	पूर्ण,
	अणु
		.desc	= "960P",
		.res	= MT9M114_RES_960P,
		.width	= 1296,
		.height	= 976,
		.fps	= 30,
		.used	= false,
		.regs	= शून्य,
		.skip_frames = 1,

		.pixels_per_line = 0x0644, /* consistent with regs arrays */
		.lines_per_frame = 0x03E5, /* consistent with regs arrays */
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.bin_mode = 0,
	पूर्ण,
पूर्ण;

#घोषणा N_RES (ARRAY_SIZE(mt9m114_res))

#अगर 0 /* Currently unused */
अटल काष्ठा misensor_reg स्थिर mt9m114_निकासstandby[] = अणु
	अणुMISENSOR_16BIT,  0x098E, 0xDC00पूर्ण,
	/* निकास-standby */
	अणुMISENSOR_8BIT,  0xDC00, 0x54पूर्ण,
	अणुMISENSOR_16BIT,  0x0080, 0x8002पूर्ण,
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा misensor_reg स्थिर mt9m114_exp_win[5][5] = अणु
	अणु
		अणुMISENSOR_8BIT,  0xA407, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA408, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA409, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA40A, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA40B, 0x64पूर्ण,
	पूर्ण,
	अणु
		अणुMISENSOR_8BIT,  0xA40C, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA40D, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA40E, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA40F, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA410, 0x64पूर्ण,
	पूर्ण,
	अणु
		अणुMISENSOR_8BIT,  0xA411, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA412, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA413, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA414, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA415, 0x64पूर्ण,
	पूर्ण,
	अणु
		अणुMISENSOR_8BIT,  0xA416, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA417, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA418, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA419, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA41A, 0x64पूर्ण,
	पूर्ण,
	अणु
		अणुMISENSOR_8BIT,  0xA41B, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA41C, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA41D, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA41E, 0x64पूर्ण,
		अणुMISENSOR_8BIT,  0xA41F, 0x64पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा misensor_reg स्थिर mt9m114_exp_average[] = अणु
	अणुMISENSOR_8BIT,  0xA407, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA408, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA409, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA40A, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA40B, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA40C, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA40D, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA40E, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA40F, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA410, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA411, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA412, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA413, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA414, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA415, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA416, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA417, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA418, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA419, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA41A, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA41B, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA41C, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA41D, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA41E, 0x00पूर्ण,
	अणुMISENSOR_8BIT,  0xA41F, 0x00पूर्ण,
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;

अटल काष्ठा misensor_reg स्थिर mt9m114_exp_center[] = अणु
	अणुMISENSOR_8BIT,  0xA407, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA408, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA409, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA40A, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA40B, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA40C, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA40D, 0x4Bपूर्ण,
	अणुMISENSOR_8BIT,  0xA40E, 0x4Bपूर्ण,
	अणुMISENSOR_8BIT,  0xA40F, 0x4Bपूर्ण,
	अणुMISENSOR_8BIT,  0xA410, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA411, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA412, 0x4Bपूर्ण,
	अणुMISENSOR_8BIT,  0xA413, 0x64पूर्ण,
	अणुMISENSOR_8BIT,  0xA414, 0x4Bपूर्ण,
	अणुMISENSOR_8BIT,  0xA415, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA416, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA417, 0x4Bपूर्ण,
	अणुMISENSOR_8BIT,  0xA418, 0x4Bपूर्ण,
	अणुMISENSOR_8BIT,  0xA419, 0x4Bपूर्ण,
	अणुMISENSOR_8BIT,  0xA41A, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA41B, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA41C, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA41D, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA41E, 0x19पूर्ण,
	अणुMISENSOR_8BIT,  0xA41F, 0x19पूर्ण,
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;

#अगर 0 /* Currently unused */
अटल काष्ठा misensor_reg स्थिर mt9m114_suspend[] = अणु
	अणुMISENSOR_16BIT,  0x098E, 0xDC00पूर्ण,
	अणुMISENSOR_8BIT,  0xDC00, 0x40पूर्ण,
	अणुMISENSOR_16BIT,  0x0080, 0x8002पूर्ण,
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;

अटल काष्ठा misensor_reg स्थिर mt9m114_streaming[] = अणु
	अणुMISENSOR_16BIT,  0x098E, 0xDC00पूर्ण,
	अणुMISENSOR_8BIT,  0xDC00, 0x34पूर्ण,
	अणुMISENSOR_16BIT,  0x0080, 0x8002पूर्ण,
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा misensor_reg स्थिर mt9m114_standby_reg[] = अणु
	अणुMISENSOR_16BIT,  0x098E, 0xDC00पूर्ण,
	अणुMISENSOR_8BIT,  0xDC00, 0x50पूर्ण,
	अणुMISENSOR_16BIT,  0x0080, 0x8002पूर्ण,
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;

#अगर 0 /* Currently unused */
अटल काष्ठा misensor_reg स्थिर mt9m114_wakeup_reg[] = अणु
	अणुMISENSOR_16BIT,  0x098E, 0xDC00पूर्ण,
	अणुMISENSOR_8BIT,  0xDC00, 0x54पूर्ण,
	अणुMISENSOR_16BIT,  0x0080, 0x8002पूर्ण,
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा misensor_reg स्थिर mt9m114_chgstat_reg[] = अणु
	अणुMISENSOR_16BIT,  0x098E, 0xDC00पूर्ण,
	अणुMISENSOR_8BIT,  0xDC00, 0x28पूर्ण,
	अणुMISENSOR_16BIT,  0x0080, 0x8002पूर्ण,
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;

/* [1296x976_30fps] - Intel */
#अगर 0
अटल काष्ठा misensor_reg स्थिर mt9m114_960P_init[] = अणु
	अणुMISENSOR_16BIT, 0x098E, 0x1000पूर्ण,
	अणुMISENSOR_8BIT, 0xC97E, 0x01पूर्ण,	  /* cam_sysctl_pll_enable = 1 */
	अणुMISENSOR_16BIT, 0xC980, 0x0128पूर्ण, /* cam_sysctl_pll_भागider_m_n = 276 */
	अणुMISENSOR_16BIT, 0xC982, 0x0700पूर्ण, /* cam_sysctl_pll_भागider_p = 1792 */
	अणुMISENSOR_16BIT, 0xC800, 0x0000पूर्ण, /* cam_sensor_cfg_y_addr_start = 0 */
	अणुMISENSOR_16BIT, 0xC802, 0x0000पूर्ण, /* cam_sensor_cfg_x_addr_start = 0 */
	अणुMISENSOR_16BIT, 0xC804, 0x03CFपूर्ण, /* cam_sensor_cfg_y_addr_end = 971 */
	अणुMISENSOR_16BIT, 0xC806, 0x050Fपूर्ण, /* cam_sensor_cfg_x_addr_end = 1291 */
	अणुMISENSOR_16BIT, 0xC808, 0x02DCपूर्ण, /* cam_sensor_cfg_pixclk = 48000000 */
	अणुMISENSOR_16BIT, 0xC80A, 0x6C00पूर्ण,
	अणुMISENSOR_16BIT, 0xC80C, 0x0001पूर्ण, /* cam_sensor_cfg_row_speed = 1 */
	/* cam_sensor_cfg_fine_पूर्णांकeg_समय_min = 219 */
	अणुMISENSOR_16BIT, 0xC80E, 0x00DBपूर्ण,
	/* cam_sensor_cfg_fine_पूर्णांकeg_समय_max = 1459 */
	अणुMISENSOR_16BIT, 0xC810, 0x05B3पूर्ण,
	/* cam_sensor_cfg_frame_length_lines = 1006 */
	अणुMISENSOR_16BIT, 0xC812, 0x03F6पूर्ण,
	/* cam_sensor_cfg_line_length_pck = 1590 */
	अणुMISENSOR_16BIT, 0xC814, 0x063Eपूर्ण,
	/* cam_sensor_cfg_fine_correction = 96 */
	अणुMISENSOR_16BIT, 0xC816, 0x0060पूर्ण,
	/* cam_sensor_cfg_cpipe_last_row = 963 */
	अणुMISENSOR_16BIT, 0xC818, 0x03C3पूर्ण,
	अणुMISENSOR_16BIT, 0xC826, 0x0020पूर्ण, /* cam_sensor_cfg_reg_0_data = 32 */
	अणुMISENSOR_16BIT, 0xC834, 0x0000पूर्ण, /* cam_sensor_control_पढ़ो_mode = 0 */
	अणुMISENSOR_16BIT, 0xC854, 0x0000पूर्ण, /* cam_crop_winकरोw_xoffset = 0 */
	अणुMISENSOR_16BIT, 0xC856, 0x0000पूर्ण, /* cam_crop_winकरोw_yoffset = 0 */
	अणुMISENSOR_16BIT, 0xC858, 0x0508पूर्ण, /* cam_crop_winकरोw_width = 1280 */
	अणुMISENSOR_16BIT, 0xC85A, 0x03C8पूर्ण, /* cam_crop_winकरोw_height = 960 */
	अणुMISENSOR_8BIT,  0xC85C, 0x03पूर्ण,   /* cam_crop_cropmode = 3 */
	अणुMISENSOR_16BIT, 0xC868, 0x0508पूर्ण, /* cam_output_width = 1280 */
	अणुMISENSOR_16BIT, 0xC86A, 0x03C8पूर्ण, /* cam_output_height = 960 */
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण,
पूर्ण;
#पूर्ण_अगर

/* [1296x976_30fps_768Mbps] */
अटल काष्ठा misensor_reg स्थिर mt9m114_976P_init[] = अणु
	अणुMISENSOR_16BIT, 0x98E, 0x1000पूर्ण,
	अणुMISENSOR_8BIT, 0xC97E, 0x01पूर्ण,	  /* cam_sysctl_pll_enable = 1 */
	अणुMISENSOR_16BIT, 0xC980, 0x0128पूर्ण, /* cam_sysctl_pll_भागider_m_n = 276 */
	अणुMISENSOR_16BIT, 0xC982, 0x0700पूर्ण, /* cam_sysctl_pll_भागider_p = 1792 */
	अणुMISENSOR_16BIT, 0xC800, 0x0000पूर्ण, /* cam_sensor_cfg_y_addr_start = 0 */
	अणुMISENSOR_16BIT, 0xC802, 0x0000पूर्ण, /* cam_sensor_cfg_x_addr_start = 0 */
	अणुMISENSOR_16BIT, 0xC804, 0x03CFपूर्ण, /* cam_sensor_cfg_y_addr_end = 975 */
	अणुMISENSOR_16BIT, 0xC806, 0x050Fपूर्ण, /* cam_sensor_cfg_x_addr_end = 1295 */
	अणुMISENSOR_32BIT, 0xC808, 0x2DC6C00पूर्ण,/* cam_sensor_cfg_pixclk = 480000*/
	अणुMISENSOR_16BIT, 0xC80C, 0x0001पूर्ण, /* cam_sensor_cfg_row_speed = 1 */
	/* cam_sensor_cfg_fine_पूर्णांकeg_समय_min = 219 */
	अणुMISENSOR_16BIT, 0xC80E, 0x00DBपूर्ण,
	/* 0x062E //cam_sensor_cfg_fine_पूर्णांकeg_समय_max = 1459 */
	अणुMISENSOR_16BIT, 0xC810, 0x05B3पूर्ण,
	/* 0x074C //cam_sensor_cfg_frame_length_lines = 1006 */
	अणुMISENSOR_16BIT, 0xC812, 0x03E5पूर्ण,
	/* 0x06B1 /cam_sensor_cfg_line_length_pck = 1590 */
	अणुMISENSOR_16BIT, 0xC814, 0x0644पूर्ण,
	/* cam_sensor_cfg_fine_correction = 96 */
	अणुMISENSOR_16BIT, 0xC816, 0x0060पूर्ण,
	/* cam_sensor_cfg_cpipe_last_row = 963 */
	अणुMISENSOR_16BIT, 0xC818, 0x03C3पूर्ण,
	अणुMISENSOR_16BIT, 0xC826, 0x0020पूर्ण, /* cam_sensor_cfg_reg_0_data = 32 */
	अणुMISENSOR_16BIT, 0xC834, 0x0000पूर्ण, /* cam_sensor_control_पढ़ो_mode = 0 */
	अणुMISENSOR_16BIT, 0xC854, 0x0000पूर्ण, /* cam_crop_winकरोw_xoffset = 0 */
	अणुMISENSOR_16BIT, 0xC856, 0x0000पूर्ण, /* cam_crop_winकरोw_yoffset = 0 */
	अणुMISENSOR_16BIT, 0xC858, 0x0508पूर्ण, /* cam_crop_winकरोw_width = 1288 */
	अणुMISENSOR_16BIT, 0xC85A, 0x03C8पूर्ण, /* cam_crop_winकरोw_height = 968 */
	अणुMISENSOR_8BIT, 0xC85C, 0x03पूर्ण, /* cam_crop_cropmode = 3 */
	अणुMISENSOR_16BIT, 0xC868, 0x0508पूर्ण, /* cam_output_width = 1288 */
	अणुMISENSOR_16BIT, 0xC86A, 0x03C8पूर्ण, /* cam_output_height = 968 */
	अणुMISENSOR_8BIT, 0xC878, 0x00पूर्ण, /* 0x0E //cam_aet_aemode = 0 */
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;

/* [1296x864_30fps] */
अटल काष्ठा misensor_reg स्थिर mt9m114_864P_init[] = अणु
	अणुMISENSOR_16BIT, 0x98E, 0x1000पूर्ण,
	अणुMISENSOR_8BIT, 0xC97E, 0x01पूर्ण,	  /* cam_sysctl_pll_enable = 1 */
	अणुMISENSOR_16BIT, 0xC980, 0x0128पूर्ण, /* cam_sysctl_pll_भागider_m_n = 276 */
	अणुMISENSOR_16BIT, 0xC982, 0x0700पूर्ण, /* cam_sysctl_pll_भागider_p = 1792 */
	अणुMISENSOR_16BIT, 0xC800, 0x0038पूर्ण, /* cam_sensor_cfg_y_addr_start = 56 */
	अणुMISENSOR_16BIT, 0xC802, 0x0000पूर्ण, /* cam_sensor_cfg_x_addr_start = 0 */
	अणुMISENSOR_16BIT, 0xC804, 0x0397पूर्ण, /* cam_sensor_cfg_y_addr_end = 919 */
	अणुMISENSOR_16BIT, 0xC806, 0x050Fपूर्ण, /* cam_sensor_cfg_x_addr_end = 1295 */
	/* cam_sensor_cfg_pixclk = 48000000 */
	अणुMISENSOR_32BIT, 0xC808, 0x2DC6C00पूर्ण,
	अणुMISENSOR_16BIT, 0xC80C, 0x0001पूर्ण, /* cam_sensor_cfg_row_speed = 1 */
	/* cam_sensor_cfg_fine_पूर्णांकeg_समय_min = 219 */
	अणुMISENSOR_16BIT, 0xC80E, 0x00DBपूर्ण,
	/* cam_sensor_cfg_fine_पूर्णांकeg_समय_max = 1469 */
	अणुMISENSOR_16BIT, 0xC810, 0x05BDपूर्ण,
	/* cam_sensor_cfg_frame_length_lines = 1000 */
	अणुMISENSOR_16BIT, 0xC812, 0x03E8पूर्ण,
	/* cam_sensor_cfg_line_length_pck = 1600 */
	अणुMISENSOR_16BIT, 0xC814, 0x0640पूर्ण,
	/* cam_sensor_cfg_fine_correction = 96 */
	अणुMISENSOR_16BIT, 0xC816, 0x0060पूर्ण,
	/* cam_sensor_cfg_cpipe_last_row = 859 */
	अणुMISENSOR_16BIT, 0xC818, 0x035Bपूर्ण,
	अणुMISENSOR_16BIT, 0xC826, 0x0020पूर्ण, /* cam_sensor_cfg_reg_0_data = 32 */
	अणुMISENSOR_16BIT, 0xC834, 0x0000पूर्ण, /* cam_sensor_control_पढ़ो_mode = 0 */
	अणुMISENSOR_16BIT, 0xC854, 0x0000पूर्ण, /* cam_crop_winकरोw_xoffset = 0 */
	अणुMISENSOR_16BIT, 0xC856, 0x0000पूर्ण, /* cam_crop_winकरोw_yoffset = 0 */
	अणुMISENSOR_16BIT, 0xC858, 0x0508पूर्ण, /* cam_crop_winकरोw_width = 1288 */
	अणुMISENSOR_16BIT, 0xC85A, 0x0358पूर्ण, /* cam_crop_winकरोw_height = 856 */
	अणुMISENSOR_8BIT, 0xC85C, 0x03पूर्ण, /* cam_crop_cropmode = 3 */
	अणुMISENSOR_16BIT, 0xC868, 0x0508पूर्ण, /* cam_output_width = 1288 */
	अणुMISENSOR_16BIT, 0xC86A, 0x0358पूर्ण, /* cam_output_height = 856 */
	अणुMISENSOR_8BIT, 0xC878, 0x00पूर्ण, /* 0x0E //cam_aet_aemode = 0 */
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;

/* [1296x736_30fps] */
अटल काष्ठा misensor_reg स्थिर mt9m114_736P_init[] = अणु
	अणुMISENSOR_16BIT, 0x98E, 0x1000पूर्ण,
	अणुMISENSOR_8BIT, 0xC97E, 0x01पूर्ण,	  /* cam_sysctl_pll_enable = 1 */
	अणुMISENSOR_16BIT, 0xC980, 0x011Fपूर्ण, /* cam_sysctl_pll_भागider_m_n = 287 */
	अणुMISENSOR_16BIT, 0xC982, 0x0700पूर्ण, /* cam_sysctl_pll_भागider_p = 1792 */
	अणुMISENSOR_16BIT, 0xC800, 0x0078पूर्ण, /* cam_sensor_cfg_y_addr_start = 120*/
	अणुMISENSOR_16BIT, 0xC802, 0x0000पूर्ण, /* cam_sensor_cfg_x_addr_start = 0 */
	अणुMISENSOR_16BIT, 0xC804, 0x0357पूर्ण, /* cam_sensor_cfg_y_addr_end = 855 */
	अणुMISENSOR_16BIT, 0xC806, 0x050Fपूर्ण, /* cam_sensor_cfg_x_addr_end = 1295 */
	अणुMISENSOR_32BIT, 0xC808, 0x237A07Fपूर्ण, /* cam_sensor_cfg_pixclk=37199999*/
	अणुMISENSOR_16BIT, 0xC80C, 0x0001पूर्ण, /* cam_sensor_cfg_row_speed = 1 */
	/* cam_sensor_cfg_fine_पूर्णांकeg_समय_min = 219 */
	अणुMISENSOR_16BIT, 0xC80E, 0x00DBपूर्ण,
	/* 0x062E //cam_sensor_cfg_fine_पूर्णांकeg_समय_max = 1469 */
	अणुMISENSOR_16BIT, 0xC810, 0x05BDपूर्ण,
	/* 0x074C //cam_sensor_cfg_frame_length_lines = 775 */
	अणुMISENSOR_16BIT, 0xC812, 0x0307पूर्ण,
	/* 0x06B1 /cam_sensor_cfg_line_length_pck = 1600 */
	अणुMISENSOR_16BIT, 0xC814, 0x0640पूर्ण,
	/* cam_sensor_cfg_fine_correction = 96 */
	अणुMISENSOR_16BIT, 0xC816, 0x0060पूर्ण,
	/* cam_sensor_cfg_cpipe_last_row = 731 */
	अणुMISENSOR_16BIT, 0xC818, 0x02DBपूर्ण,
	अणुMISENSOR_16BIT, 0xC826, 0x0020पूर्ण, /* cam_sensor_cfg_reg_0_data = 32 */
	अणुMISENSOR_16BIT, 0xC834, 0x0000पूर्ण, /* cam_sensor_control_पढ़ो_mode = 0 */
	अणुMISENSOR_16BIT, 0xC854, 0x0000पूर्ण, /* cam_crop_winकरोw_xoffset = 0 */
	अणुMISENSOR_16BIT, 0xC856, 0x0000पूर्ण, /* cam_crop_winकरोw_yoffset = 0 */
	अणुMISENSOR_16BIT, 0xC858, 0x0508पूर्ण, /* cam_crop_winकरोw_width = 1288 */
	अणुMISENSOR_16BIT, 0xC85A, 0x02D8पूर्ण, /* cam_crop_winकरोw_height = 728 */
	अणुMISENSOR_8BIT, 0xC85C, 0x03पूर्ण, /* cam_crop_cropmode = 3 */
	अणुMISENSOR_16BIT, 0xC868, 0x0508पूर्ण, /* cam_output_width = 1288 */
	अणुMISENSOR_16BIT, 0xC86A, 0x02D8पूर्ण, /* cam_output_height = 728 */
	अणुMISENSOR_8BIT, 0xC878, 0x00पूर्ण, /* 0x0E //cam_aet_aemode = 0 */
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;

/* [736x496_30fps_768Mbps] */
#अगर 0 /* Currently unused */
अटल काष्ठा misensor_reg स्थिर mt9m114_720_480P_init[] = अणु
	अणुMISENSOR_16BIT, 0x98E, 0x1000पूर्ण,
	अणुMISENSOR_8BIT, 0xC97E, 0x01पूर्ण,	  /* cam_sysctl_pll_enable = 1 */
	अणुMISENSOR_16BIT, 0xC980, 0x0128पूर्ण, /* cam_sysctl_pll_भागider_m_n = 276 */
	अणुMISENSOR_16BIT, 0xC982, 0x0700पूर्ण, /* cam_sysctl_pll_भागider_p = 1792 */
	अणुMISENSOR_16BIT, 0xC800, 0x00F0पूर्ण, /* cam_sensor_cfg_y_addr_start = 240*/
	अणुMISENSOR_16BIT, 0xC802, 0x0118पूर्ण, /* cam_sensor_cfg_x_addr_start = 280*/
	अणुMISENSOR_16BIT, 0xC804, 0x02DFपूर्ण, /* cam_sensor_cfg_y_addr_end = 735 */
	अणुMISENSOR_16BIT, 0xC806, 0x03F7पूर्ण, /* cam_sensor_cfg_x_addr_end = 1015 */
	/* cam_sensor_cfg_pixclk = 48000000 */
	अणुMISENSOR_32BIT, 0xC808, 0x2DC6C00पूर्ण,
	अणुMISENSOR_16BIT, 0xC80C, 0x0001पूर्ण, /* cam_sensor_cfg_row_speed = 1 */
	/* cam_sensor_cfg_fine_पूर्णांकeg_समय_min = 219 */
	अणुMISENSOR_16BIT, 0xC80E, 0x00DBपूर्ण,
	/* 0x062E //cam_sensor_cfg_fine_पूर्णांकeg_समय_max = 1459 */
	अणुMISENSOR_16BIT, 0xC810, 0x05B3पूर्ण,
	/* 0x074C //cam_sensor_cfg_frame_length_lines = 997 */
	अणुMISENSOR_16BIT, 0xC812, 0x03E5पूर्ण,
	/* 0x06B1 /cam_sensor_cfg_line_length_pck = 1604 */
	अणुMISENSOR_16BIT, 0xC814, 0x0644पूर्ण,
	/* cam_sensor_cfg_fine_correction = 96 */
	अणुMISENSOR_16BIT, 0xC816, 0x0060पूर्ण,
	अणुMISENSOR_16BIT, 0xC818, 0x03C3पूर्ण, /* cam_sensor_cfg_cpipe_last_row=963*/
	अणुMISENSOR_16BIT, 0xC826, 0x0020पूर्ण, /* cam_sensor_cfg_reg_0_data = 32 */
	अणुMISENSOR_16BIT, 0xC834, 0x0000पूर्ण, /* cam_sensor_control_पढ़ो_mode = 0*/
	अणुMISENSOR_16BIT, 0xC854, 0x0000पूर्ण, /* cam_crop_winकरोw_xoffset = 0 */
	अणुMISENSOR_16BIT, 0xC856, 0x0000पूर्ण, /* cam_crop_winकरोw_yoffset = 0 */
	अणुMISENSOR_16BIT, 0xC858, 0x02D8पूर्ण, /* cam_crop_winकरोw_width = 728 */
	अणुMISENSOR_16BIT, 0xC85A, 0x01E8पूर्ण, /* cam_crop_winकरोw_height = 488 */
	अणुMISENSOR_8BIT, 0xC85C, 0x03पूर्ण, /* cam_crop_cropmode = 3 */
	अणुMISENSOR_16BIT, 0xC868, 0x02D8पूर्ण, /* cam_output_width = 728 */
	अणुMISENSOR_16BIT, 0xC86A, 0x01E8पूर्ण, /* cam_output_height = 488 */
	अणुMISENSOR_8BIT, 0xC878, 0x00पूर्ण, /* 0x0E //cam_aet_aemode = 0 */
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा misensor_reg स्थिर mt9m114_common[] = अणु
	/* reset */
	अणुMISENSOR_16BIT,  0x301A, 0x0234पूर्ण,
	/* LOAD = Step2-PLL_Timing      //PLL and Timing */
	अणुMISENSOR_16BIT, 0x098E, 0x1000पूर्ण, /* LOGICAL_ADDRESS_ACCESS */
	अणुMISENSOR_8BIT, 0xC97E, 0x01पूर्ण,    /* cam_sysctl_pll_enable = 1 */
	अणुMISENSOR_16BIT, 0xC980, 0x0128पूर्ण, /* cam_sysctl_pll_भागider_m_n = 276 */
	अणुMISENSOR_16BIT, 0xC982, 0x0700पूर्ण, /* cam_sysctl_pll_भागider_p = 1792 */
	अणुMISENSOR_16BIT, 0xC800, 0x0000पूर्ण, /* cam_sensor_cfg_y_addr_start = 216*/
	अणुMISENSOR_16BIT, 0xC802, 0x0000पूर्ण, /* cam_sensor_cfg_x_addr_start = 168*/
	अणुMISENSOR_16BIT, 0xC804, 0x03CDपूर्ण, /* cam_sensor_cfg_y_addr_end = 761 */
	अणुMISENSOR_16BIT, 0xC806, 0x050Dपूर्ण, /* cam_sensor_cfg_x_addr_end = 1127 */
	अणुMISENSOR_16BIT, 0xC808, 0x02DCपूर्ण, /* cam_sensor_cfg_pixclk = 24000000 */
	अणुMISENSOR_16BIT, 0xC80A, 0x6C00पूर्ण,
	अणुMISENSOR_16BIT, 0xC80C, 0x0001पूर्ण, /* cam_sensor_cfg_row_speed = 1 */
	/* cam_sensor_cfg_fine_पूर्णांकeg_समय_min = 219 */
	अणुMISENSOR_16BIT, 0xC80E, 0x01C3पूर्ण,
	/* cam_sensor_cfg_fine_पूर्णांकeg_समय_max = 1149 */
	अणुMISENSOR_16BIT, 0xC810, 0x03F7पूर्ण,
	/* cam_sensor_cfg_frame_length_lines = 625 */
	अणुMISENSOR_16BIT, 0xC812, 0x0500पूर्ण,
	/* cam_sensor_cfg_line_length_pck = 1280 */
	अणुMISENSOR_16BIT, 0xC814, 0x04E2पूर्ण,
	/* cam_sensor_cfg_fine_correction = 96 */
	अणुMISENSOR_16BIT, 0xC816, 0x00E0पूर्ण,
	/* cam_sensor_cfg_cpipe_last_row = 541 */
	अणुMISENSOR_16BIT, 0xC818, 0x01E3पूर्ण,
	अणुMISENSOR_16BIT, 0xC826, 0x0020पूर्ण, /* cam_sensor_cfg_reg_0_data = 32 */
	अणुMISENSOR_16BIT, 0xC834, 0x0330पूर्ण, /* cam_sensor_control_पढ़ो_mode = 0 */
	अणुMISENSOR_16BIT, 0xC854, 0x0000पूर्ण, /* cam_crop_winकरोw_xoffset = 0 */
	अणुMISENSOR_16BIT, 0xC856, 0x0000पूर्ण, /* cam_crop_winकरोw_yoffset = 0 */
	अणुMISENSOR_16BIT, 0xC858, 0x0280पूर्ण, /* cam_crop_winकरोw_width = 952 */
	अणुMISENSOR_16BIT, 0xC85A, 0x01E0पूर्ण, /* cam_crop_winकरोw_height = 538 */
	अणुMISENSOR_8BIT, 0xC85C, 0x03पूर्ण,    /* cam_crop_cropmode = 3 */
	अणुMISENSOR_16BIT, 0xC868, 0x0280पूर्ण, /* cam_output_width = 952 */
	अणुMISENSOR_16BIT, 0xC86A, 0x01E0पूर्ण, /* cam_output_height = 538 */
	/* LOAD = Step3-Recommended
	 * Patch,Errata and Sensor optimization Setting */
	अणुMISENSOR_16BIT, 0x316A, 0x8270पूर्ण, /* DAC_TXLO_ROW */
	अणुMISENSOR_16BIT, 0x316C, 0x8270पूर्ण, /* DAC_TXLO */
	अणुMISENSOR_16BIT, 0x3ED0, 0x2305पूर्ण, /* DAC_LD_4_5 */
	अणुMISENSOR_16BIT, 0x3ED2, 0x77CFपूर्ण, /* DAC_LD_6_7 */
	अणुMISENSOR_16BIT, 0x316E, 0x8202पूर्ण, /* DAC_ECL */
	अणुMISENSOR_16BIT, 0x3180, 0x87FFपूर्ण, /* DELTA_DK_CONTROL */
	अणुMISENSOR_16BIT, 0x30D4, 0x6080पूर्ण, /* COLUMN_CORRECTION */
	अणुMISENSOR_16BIT, 0xA802, 0x0008पूर्ण, /* AE_TRACK_MODE */
	अणुMISENSOR_16BIT, 0x3E14, 0xFF39पूर्ण, /* SAMP_COL_PUP2 */
	अणुMISENSOR_16BIT, 0x31E0, 0x0003पूर्ण, /* PIX_DEF_ID */
	/* LOAD = Step8-Features	//Ports, special features, etc. */
	अणुMISENSOR_16BIT, 0x098E, 0x0000पूर्ण, /* LOGICAL_ADDRESS_ACCESS */
	अणुMISENSOR_16BIT, 0x001E, 0x0777पूर्ण, /* PAD_SLEW */
	अणुMISENSOR_16BIT, 0x098E, 0x0000पूर्ण, /* LOGICAL_ADDRESS_ACCESS */
	अणुMISENSOR_16BIT, 0xC984, 0x8001पूर्ण, /* CAM_PORT_OUTPUT_CONTROL */
	अणुMISENSOR_16BIT, 0xC988, 0x0F00पूर्ण, /* CAM_PORT_MIPI_TIMING_T_HS_ZERO */
	/* CAM_PORT_MIPI_TIMING_T_HS_EXIT_HS_TRAIL */
	अणुMISENSOR_16BIT, 0xC98A, 0x0B07पूर्ण,
	/* CAM_PORT_MIPI_TIMING_T_CLK_POST_CLK_PRE */
	अणुMISENSOR_16BIT, 0xC98C, 0x0D01पूर्ण,
	/* CAM_PORT_MIPI_TIMING_T_CLK_TRAIL_CLK_ZERO */
	अणुMISENSOR_16BIT, 0xC98E, 0x071Dपूर्ण,
	अणुMISENSOR_16BIT, 0xC990, 0x0006पूर्ण, /* CAM_PORT_MIPI_TIMING_T_LPX */
	अणुMISENSOR_16BIT, 0xC992, 0x0A0Cपूर्ण, /* CAM_PORT_MIPI_TIMING_INIT_TIMING */
	अणुMISENSOR_16BIT, 0x3C5A, 0x0009पूर्ण, /* MIPI_DELAY_TRIM */
	अणुMISENSOR_16BIT, 0xC86C, 0x0210पूर्ण, /* CAM_OUTPUT_FORMAT */
	अणुMISENSOR_16BIT, 0xA804, 0x0000पूर्ण, /* AE_TRACK_ALGO */
	/* शेष exposure */
	अणुMISENSOR_16BIT, 0x3012, 0x0110पूर्ण, /* COMMAND_REGISTER */
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण,

पूर्ण;

#अगर 0 /* Currently unused */
अटल काष्ठा misensor_reg स्थिर mt9m114_antअगरlicker_50hz[] = अणु
	अणुMISENSOR_16BIT,  0x098E, 0xC88Bपूर्ण,
	अणुMISENSOR_8BIT,  0xC88B, 0x32पूर्ण,
	अणुMISENSOR_8BIT,  0xDC00, 0x28पूर्ण,
	अणुMISENSOR_16BIT,  0x0080, 0x8002पूर्ण,
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;

अटल काष्ठा misensor_reg स्थिर mt9m114_antअगरlicker_60hz[] = अणु
	अणुMISENSOR_16BIT,  0x098E, 0xC88Bपूर्ण,
	अणुMISENSOR_8BIT,  0xC88B, 0x3Cपूर्ण,
	अणुMISENSOR_8BIT,  0xDC00, 0x28पूर्ण,
	अणुMISENSOR_16BIT,  0x0080, 0x8002पूर्ण,
	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;

अटल काष्ठा misensor_reg स्थिर mt9m114_iq[] = अणु
	/* [Step3-Recommended] [Sensor optimization] */
	अणुMISENSOR_16BIT,	0x316A, 0x8270पूर्ण,
	अणुMISENSOR_16BIT,	0x316C, 0x8270पूर्ण,
	अणुMISENSOR_16BIT,	0x3ED0, 0x2305पूर्ण,
	अणुMISENSOR_16BIT,	0x3ED2, 0x77CFपूर्ण,
	अणुMISENSOR_16BIT,	0x316E, 0x8202पूर्ण,
	अणुMISENSOR_16BIT,	0x3180, 0x87FFपूर्ण,
	अणुMISENSOR_16BIT,	0x30D4, 0x6080पूर्ण,
	अणुMISENSOR_16BIT,	0xA802, 0x0008पूर्ण,

	/* This रेजिस्टर is from vender to aव्योम low light color noise */
	अणुMISENSOR_16BIT,	0x31E0, 0x0001पूर्ण,

	/* LOAD=Errata item 1 */
	अणुMISENSOR_16BIT,	0x3E14, 0xFF39पूर्ण,

	/* LOAD=Errata item 2 */
	अणुMISENSOR_16BIT,	0x301A, 0x8234पूर्ण,

	/*
	 * LOAD=Errata item 3
	 * LOAD=Patch 0202;
	 * Feature Recommended; Black level correction fix
	 */
	अणुMISENSOR_16BIT,	0x0982, 0x0001पूर्ण,
	अणुMISENSOR_16BIT,	0x098A, 0x5000पूर्ण,
	अणुMISENSOR_16BIT,	0xD000, 0x70CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD002, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD004, 0xC5D4पूर्ण,
	अणुMISENSOR_16BIT,	0xD006, 0x903Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD008, 0x2144पूर्ण,
	अणुMISENSOR_16BIT,	0xD00A, 0x0C00पूर्ण,
	अणुMISENSOR_16BIT,	0xD00C, 0x2186पूर्ण,
	अणुMISENSOR_16BIT,	0xD00E, 0x0FF3पूर्ण,
	अणुMISENSOR_16BIT,	0xD010, 0xB844पूर्ण,
	अणुMISENSOR_16BIT,	0xD012, 0xB948पूर्ण,
	अणुMISENSOR_16BIT,	0xD014, 0xE082पूर्ण,
	अणुMISENSOR_16BIT,	0xD016, 0x20CCपूर्ण,
	अणुMISENSOR_16BIT,	0xD018, 0x80E2पूर्ण,
	अणुMISENSOR_16BIT,	0xD01A, 0x21CCपूर्ण,
	अणुMISENSOR_16BIT,	0xD01C, 0x80A2पूर्ण,
	अणुMISENSOR_16BIT,	0xD01E, 0x21CCपूर्ण,
	अणुMISENSOR_16BIT,	0xD020, 0x80E2पूर्ण,
	अणुMISENSOR_16BIT,	0xD022, 0xF404पूर्ण,
	अणुMISENSOR_16BIT,	0xD024, 0xD801पूर्ण,
	अणुMISENSOR_16BIT,	0xD026, 0xF003पूर्ण,
	अणुMISENSOR_16BIT,	0xD028, 0xD800पूर्ण,
	अणुMISENSOR_16BIT,	0xD02A, 0x7EE0पूर्ण,
	अणुMISENSOR_16BIT,	0xD02C, 0xC0F1पूर्ण,
	अणुMISENSOR_16BIT,	0xD02E, 0x08BAपूर्ण,

	अणुMISENSOR_16BIT,	0xD030, 0x0600पूर्ण,
	अणुMISENSOR_16BIT,	0xD032, 0xC1A1पूर्ण,
	अणुMISENSOR_16BIT,	0xD034, 0x76CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD036, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD038, 0xC130पूर्ण,
	अणुMISENSOR_16BIT,	0xD03A, 0x6E04पूर्ण,
	अणुMISENSOR_16BIT,	0xD03C, 0xC040पूर्ण,
	अणुMISENSOR_16BIT,	0xD03E, 0x71CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD040, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD042, 0xC790पूर्ण,
	अणुMISENSOR_16BIT,	0xD044, 0x8103पूर्ण,
	अणुMISENSOR_16BIT,	0xD046, 0x77CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD048, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD04A, 0xC7C0पूर्ण,
	अणुMISENSOR_16BIT,	0xD04C, 0xE001पूर्ण,
	अणुMISENSOR_16BIT,	0xD04E, 0xA103पूर्ण,
	अणुMISENSOR_16BIT,	0xD050, 0xD800पूर्ण,
	अणुMISENSOR_16BIT,	0xD052, 0x0C6Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD054, 0x04E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD056, 0xB89Eपूर्ण,
	अणुMISENSOR_16BIT,	0xD058, 0x7508पूर्ण,
	अणुMISENSOR_16BIT,	0xD05A, 0x8E1Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD05C, 0x0809पूर्ण,
	अणुMISENSOR_16BIT,	0xD05E, 0x0191पूर्ण,

	अणुMISENSOR_16BIT,	0xD060, 0xD801पूर्ण,
	अणुMISENSOR_16BIT,	0xD062, 0xAE1Dपूर्ण,
	अणुMISENSOR_16BIT,	0xD064, 0xE580पूर्ण,
	अणुMISENSOR_16BIT,	0xD066, 0x20CAपूर्ण,
	अणुMISENSOR_16BIT,	0xD068, 0x0022पूर्ण,
	अणुMISENSOR_16BIT,	0xD06A, 0x20CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD06C, 0x0522पूर्ण,
	अणुMISENSOR_16BIT,	0xD06E, 0x0C5Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD070, 0x04E2पूर्ण,
	अणुMISENSOR_16BIT,	0xD072, 0x21CAपूर्ण,
	अणुMISENSOR_16BIT,	0xD074, 0x0062पूर्ण,
	अणुMISENSOR_16BIT,	0xD076, 0xE580पूर्ण,
	अणुMISENSOR_16BIT,	0xD078, 0xD901पूर्ण,
	अणुMISENSOR_16BIT,	0xD07A, 0x79C0पूर्ण,
	अणुMISENSOR_16BIT,	0xD07C, 0xD800पूर्ण,
	अणुMISENSOR_16BIT,	0xD07E, 0x0BE6पूर्ण,
	अणुMISENSOR_16BIT,	0xD080, 0x04E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD082, 0xB89Eपूर्ण,
	अणुMISENSOR_16BIT,	0xD084, 0x70CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD086, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD088, 0xC8D4पूर्ण,
	अणुMISENSOR_16BIT,	0xD08A, 0x9002पूर्ण,
	अणुMISENSOR_16BIT,	0xD08C, 0x0857पूर्ण,
	अणुMISENSOR_16BIT,	0xD08E, 0x025Eपूर्ण,

	अणुMISENSOR_16BIT,	0xD090, 0xFFDCपूर्ण,
	अणुMISENSOR_16BIT,	0xD092, 0xE080पूर्ण,
	अणुMISENSOR_16BIT,	0xD094, 0x25CCपूर्ण,
	अणुMISENSOR_16BIT,	0xD096, 0x9022पूर्ण,
	अणुMISENSOR_16BIT,	0xD098, 0xF225पूर्ण,
	अणुMISENSOR_16BIT,	0xD09A, 0x1700पूर्ण,
	अणुMISENSOR_16BIT,	0xD09C, 0x108Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD09E, 0x73CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD0A0, 0xFF00पूर्ण,
	अणुMISENSOR_16BIT,	0xD0A2, 0x3174पूर्ण,
	अणुMISENSOR_16BIT,	0xD0A4, 0x9307पूर्ण,
	अणुMISENSOR_16BIT,	0xD0A6, 0x2A04पूर्ण,
	अणुMISENSOR_16BIT,	0xD0A8, 0x103Eपूर्ण,
	अणुMISENSOR_16BIT,	0xD0AA, 0x9328पूर्ण,
	अणुMISENSOR_16BIT,	0xD0AC, 0x2942पूर्ण,
	अणुMISENSOR_16BIT,	0xD0AE, 0x7140पूर्ण,
	अणुMISENSOR_16BIT,	0xD0B0, 0x2A04पूर्ण,
	अणुMISENSOR_16BIT,	0xD0B2, 0x107Eपूर्ण,
	अणुMISENSOR_16BIT,	0xD0B4, 0x9349पूर्ण,
	अणुMISENSOR_16BIT,	0xD0B6, 0x2942पूर्ण,
	अणुMISENSOR_16BIT,	0xD0B8, 0x7141पूर्ण,
	अणुMISENSOR_16BIT,	0xD0BA, 0x2A04पूर्ण,
	अणुMISENSOR_16BIT,	0xD0BC, 0x10BEपूर्ण,
	अणुMISENSOR_16BIT,	0xD0BE, 0x934Aपूर्ण,

	अणुMISENSOR_16BIT,	0xD0C0, 0x2942पूर्ण,
	अणुMISENSOR_16BIT,	0xD0C2, 0x714Bपूर्ण,
	अणुMISENSOR_16BIT,	0xD0C4, 0x2A04पूर्ण,
	अणुMISENSOR_16BIT,	0xD0C6, 0x10BEपूर्ण,
	अणुMISENSOR_16BIT,	0xD0C8, 0x130Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD0CA, 0x010Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD0CC, 0x2942पूर्ण,
	अणुMISENSOR_16BIT,	0xD0CE, 0x7142पूर्ण,
	अणुMISENSOR_16BIT,	0xD0D0, 0x2250पूर्ण,
	अणुMISENSOR_16BIT,	0xD0D2, 0x13CAपूर्ण,
	अणुMISENSOR_16BIT,	0xD0D4, 0x1B0Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD0D6, 0x0284पूर्ण,
	अणुMISENSOR_16BIT,	0xD0D8, 0xB307पूर्ण,
	अणुMISENSOR_16BIT,	0xD0DA, 0xB328पूर्ण,
	अणुMISENSOR_16BIT,	0xD0DC, 0x1B12पूर्ण,
	अणुMISENSOR_16BIT,	0xD0DE, 0x02C4पूर्ण,
	अणुMISENSOR_16BIT,	0xD0E0, 0xB34Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD0E2, 0xED88पूर्ण,
	अणुMISENSOR_16BIT,	0xD0E4, 0x71CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD0E6, 0xFF00पूर्ण,
	अणुMISENSOR_16BIT,	0xD0E8, 0x3174पूर्ण,
	अणुMISENSOR_16BIT,	0xD0EA, 0x9106पूर्ण,
	अणुMISENSOR_16BIT,	0xD0EC, 0xB88Fपूर्ण,
	अणुMISENSOR_16BIT,	0xD0EE, 0xB106पूर्ण,

	अणुMISENSOR_16BIT,	0xD0F0, 0x210Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD0F2, 0x8340पूर्ण,
	अणुMISENSOR_16BIT,	0xD0F4, 0xC000पूर्ण,
	अणुMISENSOR_16BIT,	0xD0F6, 0x21CAपूर्ण,
	अणुMISENSOR_16BIT,	0xD0F8, 0x0062पूर्ण,
	अणुMISENSOR_16BIT,	0xD0FA, 0x20F0पूर्ण,
	अणुMISENSOR_16BIT,	0xD0FC, 0x0040पूर्ण,
	अणुMISENSOR_16BIT,	0xD0FE, 0x0B02पूर्ण,
	अणुMISENSOR_16BIT,	0xD100, 0x0320पूर्ण,
	अणुMISENSOR_16BIT,	0xD102, 0xD901पूर्ण,
	अणुMISENSOR_16BIT,	0xD104, 0x07F1पूर्ण,
	अणुMISENSOR_16BIT,	0xD106, 0x05E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD108, 0xC0A1पूर्ण,
	अणुMISENSOR_16BIT,	0xD10A, 0x78E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD10C, 0xC0F1पूर्ण,
	अणुMISENSOR_16BIT,	0xD10E, 0x71CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD110, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD112, 0xC7C0पूर्ण,
	अणुMISENSOR_16BIT,	0xD114, 0xD840पूर्ण,
	अणुMISENSOR_16BIT,	0xD116, 0xA900पूर्ण,
	अणुMISENSOR_16BIT,	0xD118, 0x71CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD11A, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD11C, 0xD02Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD11E, 0xD81Eपूर्ण,

	अणुMISENSOR_16BIT,	0xD120, 0x0A5Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD122, 0x04E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD124, 0xDA00पूर्ण,
	अणुMISENSOR_16BIT,	0xD126, 0xD800पूर्ण,
	अणुMISENSOR_16BIT,	0xD128, 0xC0D1पूर्ण,
	अणुMISENSOR_16BIT,	0xD12A, 0x7EE0पूर्ण,

	अणुMISENSOR_16BIT,	0x098E, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xE000, 0x010Cपूर्ण,
	अणुMISENSOR_16BIT,	0xE002, 0x0202पूर्ण,
	अणुMISENSOR_16BIT,	0xE004, 0x4103पूर्ण,
	अणुMISENSOR_16BIT,	0xE006, 0x0202पूर्ण,
	अणुMISENSOR_16BIT,	0x0080, 0xFFF0पूर्ण,
	अणुMISENSOR_16BIT,	0x0080, 0xFFF1पूर्ण,

	/* LOAD=Patch 0302; Feature Recommended; Adaptive Sensitivity */
	अणुMISENSOR_16BIT,	0x0982, 0x0001पूर्ण,
	अणुMISENSOR_16BIT,	0x098A, 0x512Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD12C, 0x70CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD12E, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD130, 0xC5D4पूर्ण,
	अणुMISENSOR_16BIT,	0xD132, 0x903Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD134, 0x2144पूर्ण,
	अणुMISENSOR_16BIT,	0xD136, 0x0C00पूर्ण,
	अणुMISENSOR_16BIT,	0xD138, 0x2186पूर्ण,
	अणुMISENSOR_16BIT,	0xD13A, 0x0FF3पूर्ण,
	अणुMISENSOR_16BIT,	0xD13C, 0xB844पूर्ण,
	अणुMISENSOR_16BIT,	0xD13E, 0x262Fपूर्ण,
	अणुMISENSOR_16BIT,	0xD140, 0xF008पूर्ण,
	अणुMISENSOR_16BIT,	0xD142, 0xB948पूर्ण,
	अणुMISENSOR_16BIT,	0xD144, 0x21CCपूर्ण,
	अणुMISENSOR_16BIT,	0xD146, 0x8021पूर्ण,
	अणुMISENSOR_16BIT,	0xD148, 0xD801पूर्ण,
	अणुMISENSOR_16BIT,	0xD14A, 0xF203पूर्ण,
	अणुMISENSOR_16BIT,	0xD14C, 0xD800पूर्ण,
	अणुMISENSOR_16BIT,	0xD14E, 0x7EE0पूर्ण,
	अणुMISENSOR_16BIT,	0xD150, 0xC0F1पूर्ण,
	अणुMISENSOR_16BIT,	0xD152, 0x71CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD154, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD156, 0xC610पूर्ण,
	अणुMISENSOR_16BIT,	0xD158, 0x910Eपूर्ण,
	अणुMISENSOR_16BIT,	0xD15A, 0x208Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD15C, 0x8014पूर्ण,
	अणुMISENSOR_16BIT,	0xD15E, 0xF418पूर्ण,
	अणुMISENSOR_16BIT,	0xD160, 0x910Fपूर्ण,
	अणुMISENSOR_16BIT,	0xD162, 0x208Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD164, 0x800Fपूर्ण,
	अणुMISENSOR_16BIT,	0xD166, 0xF414पूर्ण,
	अणुMISENSOR_16BIT,	0xD168, 0x9116पूर्ण,
	अणुMISENSOR_16BIT,	0xD16A, 0x208Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD16C, 0x800Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD16E, 0xF410पूर्ण,
	अणुMISENSOR_16BIT,	0xD170, 0x9117पूर्ण,
	अणुMISENSOR_16BIT,	0xD172, 0x208Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD174, 0x8807पूर्ण,
	अणुMISENSOR_16BIT,	0xD176, 0xF40Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD178, 0x9118पूर्ण,
	अणुMISENSOR_16BIT,	0xD17A, 0x2086पूर्ण,
	अणुMISENSOR_16BIT,	0xD17C, 0x0FF3पूर्ण,
	अणुMISENSOR_16BIT,	0xD17E, 0xB848पूर्ण,
	अणुMISENSOR_16BIT,	0xD180, 0x080Dपूर्ण,
	अणुMISENSOR_16BIT,	0xD182, 0x0090पूर्ण,
	अणुMISENSOR_16BIT,	0xD184, 0xFFEAपूर्ण,
	अणुMISENSOR_16BIT,	0xD186, 0xE081पूर्ण,
	अणुMISENSOR_16BIT,	0xD188, 0xD801पूर्ण,
	अणुMISENSOR_16BIT,	0xD18A, 0xF203पूर्ण,
	अणुMISENSOR_16BIT,	0xD18C, 0xD800पूर्ण,
	अणुMISENSOR_16BIT,	0xD18E, 0xC0D1पूर्ण,
	अणुMISENSOR_16BIT,	0xD190, 0x7EE0पूर्ण,
	अणुMISENSOR_16BIT,	0xD192, 0x78E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD194, 0xC0F1पूर्ण,
	अणुMISENSOR_16BIT,	0xD196, 0x71CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD198, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD19A, 0xC610पूर्ण,
	अणुMISENSOR_16BIT,	0xD19C, 0x910Eपूर्ण,
	अणुMISENSOR_16BIT,	0xD19E, 0x208Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD1A0, 0x800Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD1A2, 0xF418पूर्ण,
	अणुMISENSOR_16BIT,	0xD1A4, 0x910Fपूर्ण,
	अणुMISENSOR_16BIT,	0xD1A6, 0x208Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD1A8, 0x8807पूर्ण,
	अणुMISENSOR_16BIT,	0xD1AA, 0xF414पूर्ण,
	अणुMISENSOR_16BIT,	0xD1AC, 0x9116पूर्ण,
	अणुMISENSOR_16BIT,	0xD1AE, 0x208Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD1B0, 0x800Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD1B2, 0xF410पूर्ण,
	अणुMISENSOR_16BIT,	0xD1B4, 0x9117पूर्ण,
	अणुMISENSOR_16BIT,	0xD1B6, 0x208Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD1B8, 0x8807पूर्ण,
	अणुMISENSOR_16BIT,	0xD1BA, 0xF40Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD1BC, 0x9118पूर्ण,
	अणुMISENSOR_16BIT,	0xD1BE, 0x2086पूर्ण,
	अणुMISENSOR_16BIT,	0xD1C0, 0x0FF3पूर्ण,
	अणुMISENSOR_16BIT,	0xD1C2, 0xB848पूर्ण,
	अणुMISENSOR_16BIT,	0xD1C4, 0x080Dपूर्ण,
	अणुMISENSOR_16BIT,	0xD1C6, 0x0090पूर्ण,
	अणुMISENSOR_16BIT,	0xD1C8, 0xFFD9पूर्ण,
	अणुMISENSOR_16BIT,	0xD1CA, 0xE080पूर्ण,
	अणुMISENSOR_16BIT,	0xD1CC, 0xD801पूर्ण,
	अणुMISENSOR_16BIT,	0xD1CE, 0xF203पूर्ण,
	अणुMISENSOR_16BIT,	0xD1D0, 0xD800पूर्ण,
	अणुMISENSOR_16BIT,	0xD1D2, 0xF1DFपूर्ण,
	अणुMISENSOR_16BIT,	0xD1D4, 0x9040पूर्ण,
	अणुMISENSOR_16BIT,	0xD1D6, 0x71CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD1D8, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD1DA, 0xC5D4पूर्ण,
	अणुMISENSOR_16BIT,	0xD1DC, 0xB15Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD1DE, 0x9041पूर्ण,
	अणुMISENSOR_16BIT,	0xD1E0, 0x73CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD1E2, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD1E4, 0xC7D0पूर्ण,
	अणुMISENSOR_16BIT,	0xD1E6, 0xB140पूर्ण,
	अणुMISENSOR_16BIT,	0xD1E8, 0x9042पूर्ण,
	अणुMISENSOR_16BIT,	0xD1EA, 0xB141पूर्ण,
	अणुMISENSOR_16BIT,	0xD1EC, 0x9043पूर्ण,
	अणुMISENSOR_16BIT,	0xD1EE, 0xB142पूर्ण,
	अणुMISENSOR_16BIT,	0xD1F0, 0x9044पूर्ण,
	अणुMISENSOR_16BIT,	0xD1F2, 0xB143पूर्ण,
	अणुMISENSOR_16BIT,	0xD1F4, 0x9045पूर्ण,
	अणुMISENSOR_16BIT,	0xD1F6, 0xB147पूर्ण,
	अणुMISENSOR_16BIT,	0xD1F8, 0x9046पूर्ण,
	अणुMISENSOR_16BIT,	0xD1FA, 0xB148पूर्ण,
	अणुMISENSOR_16BIT,	0xD1FC, 0x9047पूर्ण,
	अणुMISENSOR_16BIT,	0xD1FE, 0xB14Bपूर्ण,
	अणुMISENSOR_16BIT,	0xD200, 0x9048पूर्ण,
	अणुMISENSOR_16BIT,	0xD202, 0xB14Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD204, 0x9049पूर्ण,
	अणुMISENSOR_16BIT,	0xD206, 0x1958पूर्ण,
	अणुMISENSOR_16BIT,	0xD208, 0x0084पूर्ण,
	अणुMISENSOR_16BIT,	0xD20A, 0x904Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD20C, 0x195Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD20E, 0x0084पूर्ण,
	अणुMISENSOR_16BIT,	0xD210, 0x8856पूर्ण,
	अणुMISENSOR_16BIT,	0xD212, 0x1B36पूर्ण,
	अणुMISENSOR_16BIT,	0xD214, 0x8082पूर्ण,
	अणुMISENSOR_16BIT,	0xD216, 0x8857पूर्ण,
	अणुMISENSOR_16BIT,	0xD218, 0x1B37पूर्ण,
	अणुMISENSOR_16BIT,	0xD21A, 0x8082पूर्ण,
	अणुMISENSOR_16BIT,	0xD21C, 0x904Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD21E, 0x19A7पूर्ण,
	अणुMISENSOR_16BIT,	0xD220, 0x009Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD222, 0x881Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD224, 0x7FE0पूर्ण,
	अणुMISENSOR_16BIT,	0xD226, 0x1B54पूर्ण,
	अणुMISENSOR_16BIT,	0xD228, 0x8002पूर्ण,
	अणुMISENSOR_16BIT,	0xD22A, 0x78E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD22C, 0x71CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD22E, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD230, 0xC350पूर्ण,
	अणुMISENSOR_16BIT,	0xD232, 0xD828पूर्ण,
	अणुMISENSOR_16BIT,	0xD234, 0xA90Bपूर्ण,
	अणुMISENSOR_16BIT,	0xD236, 0x8100पूर्ण,
	अणुMISENSOR_16BIT,	0xD238, 0x01C5पूर्ण,
	अणुMISENSOR_16BIT,	0xD23A, 0x0320पूर्ण,
	अणुMISENSOR_16BIT,	0xD23C, 0xD900पूर्ण,
	अणुMISENSOR_16BIT,	0xD23E, 0x78E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD240, 0x220Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD242, 0x1F80पूर्ण,
	अणुMISENSOR_16BIT,	0xD244, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD246, 0xD4E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD248, 0xC0F1पूर्ण,
	अणुMISENSOR_16BIT,	0xD24A, 0x0811पूर्ण,
	अणुMISENSOR_16BIT,	0xD24C, 0x0051पूर्ण,
	अणुMISENSOR_16BIT,	0xD24E, 0x2240पूर्ण,
	अणुMISENSOR_16BIT,	0xD250, 0x1200पूर्ण,
	अणुMISENSOR_16BIT,	0xD252, 0xFFE1पूर्ण,
	अणुMISENSOR_16BIT,	0xD254, 0xD801पूर्ण,
	अणुMISENSOR_16BIT,	0xD256, 0xF006पूर्ण,
	अणुMISENSOR_16BIT,	0xD258, 0x2240पूर्ण,
	अणुMISENSOR_16BIT,	0xD25A, 0x1900पूर्ण,
	अणुMISENSOR_16BIT,	0xD25C, 0xFFDEपूर्ण,
	अणुMISENSOR_16BIT,	0xD25E, 0xD802पूर्ण,
	अणुMISENSOR_16BIT,	0xD260, 0x1A05पूर्ण,
	अणुMISENSOR_16BIT,	0xD262, 0x1002पूर्ण,
	अणुMISENSOR_16BIT,	0xD264, 0xFFF2पूर्ण,
	अणुMISENSOR_16BIT,	0xD266, 0xF195पूर्ण,
	अणुMISENSOR_16BIT,	0xD268, 0xC0F1पूर्ण,
	अणुMISENSOR_16BIT,	0xD26A, 0x0E7Eपूर्ण,
	अणुMISENSOR_16BIT,	0xD26C, 0x05C0पूर्ण,
	अणुMISENSOR_16BIT,	0xD26E, 0x75CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD270, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD272, 0xC84Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD274, 0x9502पूर्ण,
	अणुMISENSOR_16BIT,	0xD276, 0x77CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD278, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD27A, 0xC344पूर्ण,
	अणुMISENSOR_16BIT,	0xD27C, 0x2044पूर्ण,
	अणुMISENSOR_16BIT,	0xD27E, 0x008Eपूर्ण,
	अणुMISENSOR_16BIT,	0xD280, 0xB8A1पूर्ण,
	अणुMISENSOR_16BIT,	0xD282, 0x0926पूर्ण,
	अणुMISENSOR_16BIT,	0xD284, 0x03E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD286, 0xB502पूर्ण,
	अणुMISENSOR_16BIT,	0xD288, 0x9502पूर्ण,
	अणुMISENSOR_16BIT,	0xD28A, 0x952Eपूर्ण,
	अणुMISENSOR_16BIT,	0xD28C, 0x7E05पूर्ण,
	अणुMISENSOR_16BIT,	0xD28E, 0xB5C2पूर्ण,
	अणुMISENSOR_16BIT,	0xD290, 0x70CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD292, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD294, 0xC610पूर्ण,
	अणुMISENSOR_16BIT,	0xD296, 0x099Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD298, 0x04A0पूर्ण,
	अणुMISENSOR_16BIT,	0xD29A, 0xB026पूर्ण,
	अणुMISENSOR_16BIT,	0xD29C, 0x0E02पूर्ण,
	अणुMISENSOR_16BIT,	0xD29E, 0x0560पूर्ण,
	अणुMISENSOR_16BIT,	0xD2A0, 0xDE00पूर्ण,
	अणुMISENSOR_16BIT,	0xD2A2, 0x0A12पूर्ण,
	अणुMISENSOR_16BIT,	0xD2A4, 0x0320पूर्ण,
	अणुMISENSOR_16BIT,	0xD2A6, 0xB7C4पूर्ण,
	अणुMISENSOR_16BIT,	0xD2A8, 0x0B36पूर्ण,
	अणुMISENSOR_16BIT,	0xD2AA, 0x03A0पूर्ण,
	अणुMISENSOR_16BIT,	0xD2AC, 0x70C9पूर्ण,
	अणुMISENSOR_16BIT,	0xD2AE, 0x9502पूर्ण,
	अणुMISENSOR_16BIT,	0xD2B0, 0x7608पूर्ण,
	अणुMISENSOR_16BIT,	0xD2B2, 0xB8A8पूर्ण,
	अणुMISENSOR_16BIT,	0xD2B4, 0xB502पूर्ण,
	अणुMISENSOR_16BIT,	0xD2B6, 0x70CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD2B8, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD2BA, 0x5536पूर्ण,
	अणुMISENSOR_16BIT,	0xD2BC, 0x7860पूर्ण,
	अणुMISENSOR_16BIT,	0xD2BE, 0x2686पूर्ण,
	अणुMISENSOR_16BIT,	0xD2C0, 0x1FFBपूर्ण,
	अणुMISENSOR_16BIT,	0xD2C2, 0x9502पूर्ण,
	अणुMISENSOR_16BIT,	0xD2C4, 0x78C5पूर्ण,
	अणुMISENSOR_16BIT,	0xD2C6, 0x0631पूर्ण,
	अणुMISENSOR_16BIT,	0xD2C8, 0x05E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD2CA, 0xB502पूर्ण,
	अणुMISENSOR_16BIT,	0xD2CC, 0x72CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD2CE, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD2D0, 0xC5D4पूर्ण,
	अणुMISENSOR_16BIT,	0xD2D2, 0x923Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD2D4, 0x73CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD2D6, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD2D8, 0xC7D0पूर्ण,
	अणुMISENSOR_16BIT,	0xD2DA, 0xB020पूर्ण,
	अणुMISENSOR_16BIT,	0xD2DC, 0x9220पूर्ण,
	अणुMISENSOR_16BIT,	0xD2DE, 0xB021पूर्ण,
	अणुMISENSOR_16BIT,	0xD2E0, 0x9221पूर्ण,
	अणुMISENSOR_16BIT,	0xD2E2, 0xB022पूर्ण,
	अणुMISENSOR_16BIT,	0xD2E4, 0x9222पूर्ण,
	अणुMISENSOR_16BIT,	0xD2E6, 0xB023पूर्ण,
	अणुMISENSOR_16BIT,	0xD2E8, 0x9223पूर्ण,
	अणुMISENSOR_16BIT,	0xD2EA, 0xB024पूर्ण,
	अणुMISENSOR_16BIT,	0xD2EC, 0x9227पूर्ण,
	अणुMISENSOR_16BIT,	0xD2EE, 0xB025पूर्ण,
	अणुMISENSOR_16BIT,	0xD2F0, 0x9228पूर्ण,
	अणुMISENSOR_16BIT,	0xD2F2, 0xB026पूर्ण,
	अणुMISENSOR_16BIT,	0xD2F4, 0x922Bपूर्ण,
	अणुMISENSOR_16BIT,	0xD2F6, 0xB027पूर्ण,
	अणुMISENSOR_16BIT,	0xD2F8, 0x922Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD2FA, 0xB028पूर्ण,
	अणुMISENSOR_16BIT,	0xD2FC, 0x1258पूर्ण,
	अणुMISENSOR_16BIT,	0xD2FE, 0x0101पूर्ण,
	अणुMISENSOR_16BIT,	0xD300, 0xB029पूर्ण,
	अणुMISENSOR_16BIT,	0xD302, 0x125Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD304, 0x0101पूर्ण,
	अणुMISENSOR_16BIT,	0xD306, 0xB02Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD308, 0x1336पूर्ण,
	अणुMISENSOR_16BIT,	0xD30A, 0x8081पूर्ण,
	अणुMISENSOR_16BIT,	0xD30C, 0xA836पूर्ण,
	अणुMISENSOR_16BIT,	0xD30E, 0x1337पूर्ण,
	अणुMISENSOR_16BIT,	0xD310, 0x8081पूर्ण,
	अणुMISENSOR_16BIT,	0xD312, 0xA837पूर्ण,
	अणुMISENSOR_16BIT,	0xD314, 0x12A7पूर्ण,
	अणुMISENSOR_16BIT,	0xD316, 0x0701पूर्ण,
	अणुMISENSOR_16BIT,	0xD318, 0xB02Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD31A, 0x1354पूर्ण,
	अणुMISENSOR_16BIT,	0xD31C, 0x8081पूर्ण,
	अणुMISENSOR_16BIT,	0xD31E, 0x7FE0पूर्ण,
	अणुMISENSOR_16BIT,	0xD320, 0xA83Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD322, 0x78E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD324, 0xC0F1पूर्ण,
	अणुMISENSOR_16BIT,	0xD326, 0x0DC2पूर्ण,
	अणुMISENSOR_16BIT,	0xD328, 0x05C0पूर्ण,
	अणुMISENSOR_16BIT,	0xD32A, 0x7608पूर्ण,
	अणुMISENSOR_16BIT,	0xD32C, 0x09BBपूर्ण,
	अणुMISENSOR_16BIT,	0xD32E, 0x0010पूर्ण,
	अणुMISENSOR_16BIT,	0xD330, 0x75CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD332, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD334, 0xD4E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD336, 0x8D21पूर्ण,
	अणुMISENSOR_16BIT,	0xD338, 0x8D00पूर्ण,
	अणुMISENSOR_16BIT,	0xD33A, 0x2153पूर्ण,
	अणुMISENSOR_16BIT,	0xD33C, 0x0003पूर्ण,
	अणुMISENSOR_16BIT,	0xD33E, 0xB8C0पूर्ण,
	अणुMISENSOR_16BIT,	0xD340, 0x8D45पूर्ण,
	अणुMISENSOR_16BIT,	0xD342, 0x0B23पूर्ण,
	अणुMISENSOR_16BIT,	0xD344, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD346, 0xEA8Fपूर्ण,
	अणुMISENSOR_16BIT,	0xD348, 0x0915पूर्ण,
	अणुMISENSOR_16BIT,	0xD34A, 0x001Eपूर्ण,
	अणुMISENSOR_16BIT,	0xD34C, 0xFF81पूर्ण,
	अणुMISENSOR_16BIT,	0xD34E, 0xE808पूर्ण,
	अणुMISENSOR_16BIT,	0xD350, 0x2540पूर्ण,
	अणुMISENSOR_16BIT,	0xD352, 0x1900पूर्ण,
	अणुMISENSOR_16BIT,	0xD354, 0xFFDEपूर्ण,
	अणुMISENSOR_16BIT,	0xD356, 0x8D00पूर्ण,
	अणुMISENSOR_16BIT,	0xD358, 0xB880पूर्ण,
	अणुMISENSOR_16BIT,	0xD35A, 0xF004पूर्ण,
	अणुMISENSOR_16BIT,	0xD35C, 0x8D00पूर्ण,
	अणुMISENSOR_16BIT,	0xD35E, 0xB8A0पूर्ण,
	अणुMISENSOR_16BIT,	0xD360, 0xAD00पूर्ण,
	अणुMISENSOR_16BIT,	0xD362, 0x8D05पूर्ण,
	अणुMISENSOR_16BIT,	0xD364, 0xE081पूर्ण,
	अणुMISENSOR_16BIT,	0xD366, 0x20CCपूर्ण,
	अणुMISENSOR_16BIT,	0xD368, 0x80A2पूर्ण,
	अणुMISENSOR_16BIT,	0xD36A, 0xDF00पूर्ण,
	अणुMISENSOR_16BIT,	0xD36C, 0xF40Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD36E, 0x71CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD370, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD372, 0xC84Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD374, 0x9102पूर्ण,
	अणुMISENSOR_16BIT,	0xD376, 0x7708पूर्ण,
	अणुMISENSOR_16BIT,	0xD378, 0xB8A6पूर्ण,
	अणुMISENSOR_16BIT,	0xD37A, 0x2786पूर्ण,
	अणुMISENSOR_16BIT,	0xD37C, 0x1FFEपूर्ण,
	अणुMISENSOR_16BIT,	0xD37E, 0xB102पूर्ण,
	अणुMISENSOR_16BIT,	0xD380, 0x0B42पूर्ण,
	अणुMISENSOR_16BIT,	0xD382, 0x0180पूर्ण,
	अणुMISENSOR_16BIT,	0xD384, 0x0E3Eपूर्ण,
	अणुMISENSOR_16BIT,	0xD386, 0x0180पूर्ण,
	अणुMISENSOR_16BIT,	0xD388, 0x0F4Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD38A, 0x0160पूर्ण,
	अणुMISENSOR_16BIT,	0xD38C, 0x70C9पूर्ण,
	अणुMISENSOR_16BIT,	0xD38E, 0x8D05पूर्ण,
	अणुMISENSOR_16BIT,	0xD390, 0xE081पूर्ण,
	अणुMISENSOR_16BIT,	0xD392, 0x20CCपूर्ण,
	अणुMISENSOR_16BIT,	0xD394, 0x80A2पूर्ण,
	अणुMISENSOR_16BIT,	0xD396, 0xF429पूर्ण,
	अणुMISENSOR_16BIT,	0xD398, 0x76CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD39A, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD39C, 0xC84Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD39E, 0x082Dपूर्ण,
	अणुMISENSOR_16BIT,	0xD3A0, 0x0051पूर्ण,
	अणुMISENSOR_16BIT,	0xD3A2, 0x70CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD3A4, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD3A6, 0xC90Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD3A8, 0x8805पूर्ण,
	अणुMISENSOR_16BIT,	0xD3AA, 0x09B6पूर्ण,
	अणुMISENSOR_16BIT,	0xD3AC, 0x0360पूर्ण,
	अणुMISENSOR_16BIT,	0xD3AE, 0xD908पूर्ण,
	अणुMISENSOR_16BIT,	0xD3B0, 0x2099पूर्ण,
	अणुMISENSOR_16BIT,	0xD3B2, 0x0802पूर्ण,
	अणुMISENSOR_16BIT,	0xD3B4, 0x9634पूर्ण,
	अणुMISENSOR_16BIT,	0xD3B6, 0xB503पूर्ण,
	अणुMISENSOR_16BIT,	0xD3B8, 0x7902पूर्ण,
	अणुMISENSOR_16BIT,	0xD3BA, 0x1523पूर्ण,
	अणुMISENSOR_16BIT,	0xD3BC, 0x1080पूर्ण,
	अणुMISENSOR_16BIT,	0xD3BE, 0xB634पूर्ण,
	अणुMISENSOR_16BIT,	0xD3C0, 0xE001पूर्ण,
	अणुMISENSOR_16BIT,	0xD3C2, 0x1D23पूर्ण,
	अणुMISENSOR_16BIT,	0xD3C4, 0x1002पूर्ण,
	अणुMISENSOR_16BIT,	0xD3C6, 0xF00Bपूर्ण,
	अणुMISENSOR_16BIT,	0xD3C8, 0x9634पूर्ण,
	अणुMISENSOR_16BIT,	0xD3CA, 0x9503पूर्ण,
	अणुMISENSOR_16BIT,	0xD3CC, 0x6038पूर्ण,
	अणुMISENSOR_16BIT,	0xD3CE, 0xB614पूर्ण,
	अणुMISENSOR_16BIT,	0xD3D0, 0x153Fपूर्ण,
	अणुMISENSOR_16BIT,	0xD3D2, 0x1080पूर्ण,
	अणुMISENSOR_16BIT,	0xD3D4, 0xE001पूर्ण,
	अणुMISENSOR_16BIT,	0xD3D6, 0x1D3Fपूर्ण,
	अणुMISENSOR_16BIT,	0xD3D8, 0x1002पूर्ण,
	अणुMISENSOR_16BIT,	0xD3DA, 0xFFA4पूर्ण,
	अणुMISENSOR_16BIT,	0xD3DC, 0x9602पूर्ण,
	अणुMISENSOR_16BIT,	0xD3DE, 0x7F05पूर्ण,
	अणुMISENSOR_16BIT,	0xD3E0, 0xD800पूर्ण,
	अणुMISENSOR_16BIT,	0xD3E2, 0xB6E2पूर्ण,
	अणुMISENSOR_16BIT,	0xD3E4, 0xAD05पूर्ण,
	अणुMISENSOR_16BIT,	0xD3E6, 0x0511पूर्ण,
	अणुMISENSOR_16BIT,	0xD3E8, 0x05E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD3EA, 0xD800पूर्ण,
	अणुMISENSOR_16BIT,	0xD3EC, 0xC0F1पूर्ण,
	अणुMISENSOR_16BIT,	0xD3EE, 0x0CFEपूर्ण,
	अणुMISENSOR_16BIT,	0xD3F0, 0x05C0पूर्ण,
	अणुMISENSOR_16BIT,	0xD3F2, 0x0A96पूर्ण,
	अणुMISENSOR_16BIT,	0xD3F4, 0x05A0पूर्ण,
	अणुMISENSOR_16BIT,	0xD3F6, 0x7608पूर्ण,
	अणुMISENSOR_16BIT,	0xD3F8, 0x0C22पूर्ण,
	अणुMISENSOR_16BIT,	0xD3FA, 0x0240पूर्ण,
	अणुMISENSOR_16BIT,	0xD3FC, 0xE080पूर्ण,
	अणुMISENSOR_16BIT,	0xD3FE, 0x20CAपूर्ण,
	अणुMISENSOR_16BIT,	0xD400, 0x0F82पूर्ण,
	अणुMISENSOR_16BIT,	0xD402, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD404, 0x190Bपूर्ण,
	अणुMISENSOR_16BIT,	0xD406, 0x0C60पूर्ण,
	अणुMISENSOR_16BIT,	0xD408, 0x05A2पूर्ण,
	अणुMISENSOR_16BIT,	0xD40A, 0x21CAपूर्ण,
	अणुMISENSOR_16BIT,	0xD40C, 0x0022पूर्ण,
	अणुMISENSOR_16BIT,	0xD40E, 0x0C56पूर्ण,
	अणुMISENSOR_16BIT,	0xD410, 0x0240पूर्ण,
	अणुMISENSOR_16BIT,	0xD412, 0xE806पूर्ण,
	अणुMISENSOR_16BIT,	0xD414, 0x0E0Eपूर्ण,
	अणुMISENSOR_16BIT,	0xD416, 0x0220पूर्ण,
	अणुMISENSOR_16BIT,	0xD418, 0x70C9पूर्ण,
	अणुMISENSOR_16BIT,	0xD41A, 0xF048पूर्ण,
	अणुMISENSOR_16BIT,	0xD41C, 0x0896पूर्ण,
	अणुMISENSOR_16BIT,	0xD41E, 0x0440पूर्ण,
	अणुMISENSOR_16BIT,	0xD420, 0x0E96पूर्ण,
	अणुMISENSOR_16BIT,	0xD422, 0x0400पूर्ण,
	अणुMISENSOR_16BIT,	0xD424, 0x0966पूर्ण,
	अणुMISENSOR_16BIT,	0xD426, 0x0380पूर्ण,
	अणुMISENSOR_16BIT,	0xD428, 0x75CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD42A, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD42C, 0xD4E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD42E, 0x8D00पूर्ण,
	अणुMISENSOR_16BIT,	0xD430, 0x084Dपूर्ण,
	अणुMISENSOR_16BIT,	0xD432, 0x001Eपूर्ण,
	अणुMISENSOR_16BIT,	0xD434, 0xFF47पूर्ण,
	अणुMISENSOR_16BIT,	0xD436, 0x080Dपूर्ण,
	अणुMISENSOR_16BIT,	0xD438, 0x0050पूर्ण,
	अणुMISENSOR_16BIT,	0xD43A, 0xFF57पूर्ण,
	अणुMISENSOR_16BIT,	0xD43C, 0x0841पूर्ण,
	अणुMISENSOR_16BIT,	0xD43E, 0x0051पूर्ण,
	अणुMISENSOR_16BIT,	0xD440, 0x8D04पूर्ण,
	अणुMISENSOR_16BIT,	0xD442, 0x9521पूर्ण,
	अणुMISENSOR_16BIT,	0xD444, 0xE064पूर्ण,
	अणुMISENSOR_16BIT,	0xD446, 0x790Cपूर्ण,
	अणुMISENSOR_16BIT,	0xD448, 0x702Fपूर्ण,
	अणुMISENSOR_16BIT,	0xD44A, 0x0CE2पूर्ण,
	अणुMISENSOR_16BIT,	0xD44C, 0x05E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD44E, 0xD964पूर्ण,
	अणुMISENSOR_16BIT,	0xD450, 0x72CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD452, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD454, 0xC700पूर्ण,
	अणुMISENSOR_16BIT,	0xD456, 0x9235पूर्ण,
	अणुMISENSOR_16BIT,	0xD458, 0x0811पूर्ण,
	अणुMISENSOR_16BIT,	0xD45A, 0x0043पूर्ण,
	अणुMISENSOR_16BIT,	0xD45C, 0xFF3Dपूर्ण,
	अणुMISENSOR_16BIT,	0xD45E, 0x080Dपूर्ण,
	अणुMISENSOR_16BIT,	0xD460, 0x0051पूर्ण,
	अणुMISENSOR_16BIT,	0xD462, 0xD801पूर्ण,
	अणुMISENSOR_16BIT,	0xD464, 0xFF77पूर्ण,
	अणुMISENSOR_16BIT,	0xD466, 0xF025पूर्ण,
	अणुMISENSOR_16BIT,	0xD468, 0x9501पूर्ण,
	अणुMISENSOR_16BIT,	0xD46A, 0x9235पूर्ण,
	अणुMISENSOR_16BIT,	0xD46C, 0x0911पूर्ण,
	अणुMISENSOR_16BIT,	0xD46E, 0x0003पूर्ण,
	अणुMISENSOR_16BIT,	0xD470, 0xFF49पूर्ण,
	अणुMISENSOR_16BIT,	0xD472, 0x080Dपूर्ण,
	अणुMISENSOR_16BIT,	0xD474, 0x0051पूर्ण,
	अणुMISENSOR_16BIT,	0xD476, 0xD800पूर्ण,
	अणुMISENSOR_16BIT,	0xD478, 0xFF72पूर्ण,
	अणुMISENSOR_16BIT,	0xD47A, 0xF01Bपूर्ण,
	अणुMISENSOR_16BIT,	0xD47C, 0x0886पूर्ण,
	अणुMISENSOR_16BIT,	0xD47E, 0x03E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD480, 0xD801पूर्ण,
	अणुMISENSOR_16BIT,	0xD482, 0x0EF6पूर्ण,
	अणुMISENSOR_16BIT,	0xD484, 0x03C0पूर्ण,
	अणुMISENSOR_16BIT,	0xD486, 0x0F52पूर्ण,
	अणुMISENSOR_16BIT,	0xD488, 0x0340पूर्ण,
	अणुMISENSOR_16BIT,	0xD48A, 0x0DBAपूर्ण,
	अणुMISENSOR_16BIT,	0xD48C, 0x0200पूर्ण,
	अणुMISENSOR_16BIT,	0xD48E, 0x0AF6पूर्ण,
	अणुMISENSOR_16BIT,	0xD490, 0x0440पूर्ण,
	अणुMISENSOR_16BIT,	0xD492, 0x0C22पूर्ण,
	अणुMISENSOR_16BIT,	0xD494, 0x0400पूर्ण,
	अणुMISENSOR_16BIT,	0xD496, 0x0D72पूर्ण,
	अणुMISENSOR_16BIT,	0xD498, 0x0440पूर्ण,
	अणुMISENSOR_16BIT,	0xD49A, 0x0DC2पूर्ण,
	अणुMISENSOR_16BIT,	0xD49C, 0x0200पूर्ण,
	अणुMISENSOR_16BIT,	0xD49E, 0x0972पूर्ण,
	अणुMISENSOR_16BIT,	0xD4A0, 0x0440पूर्ण,
	अणुMISENSOR_16BIT,	0xD4A2, 0x0D3Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD4A4, 0x0220पूर्ण,
	अणुMISENSOR_16BIT,	0xD4A6, 0xD820पूर्ण,
	अणुMISENSOR_16BIT,	0xD4A8, 0x0BFAपूर्ण,
	अणुMISENSOR_16BIT,	0xD4AA, 0x0260पूर्ण,
	अणुMISENSOR_16BIT,	0xD4AC, 0x70C9पूर्ण,
	अणुMISENSOR_16BIT,	0xD4AE, 0x0451पूर्ण,
	अणुMISENSOR_16BIT,	0xD4B0, 0x05C0पूर्ण,
	अणुMISENSOR_16BIT,	0xD4B2, 0x78E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD4B4, 0xD900पूर्ण,
	अणुMISENSOR_16BIT,	0xD4B6, 0xF00Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD4B8, 0x70CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD4BA, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD4BC, 0xD520पूर्ण,
	अणुMISENSOR_16BIT,	0xD4BE, 0x7835पूर्ण,
	अणुMISENSOR_16BIT,	0xD4C0, 0x8041पूर्ण,
	अणुMISENSOR_16BIT,	0xD4C2, 0x8000पूर्ण,
	अणुMISENSOR_16BIT,	0xD4C4, 0xE102पूर्ण,
	अणुMISENSOR_16BIT,	0xD4C6, 0xA040पूर्ण,
	अणुMISENSOR_16BIT,	0xD4C8, 0x09F1पूर्ण,
	अणुMISENSOR_16BIT,	0xD4CA, 0x8114पूर्ण,
	अणुMISENSOR_16BIT,	0xD4CC, 0x71CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD4CE, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD4D0, 0xD4E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD4D2, 0x70CFपूर्ण,
	अणुMISENSOR_16BIT,	0xD4D4, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD4D6, 0xC594पूर्ण,
	अणुMISENSOR_16BIT,	0xD4D8, 0xB03Aपूर्ण,
	अणुMISENSOR_16BIT,	0xD4DA, 0x7FE0पूर्ण,
	अणुMISENSOR_16BIT,	0xD4DC, 0xD800पूर्ण,
	अणुMISENSOR_16BIT,	0xD4DE, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD4E0, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD4E2, 0x0500पूर्ण,
	अणुMISENSOR_16BIT,	0xD4E4, 0x0500पूर्ण,
	अणुMISENSOR_16BIT,	0xD4E6, 0x0200पूर्ण,
	अणुMISENSOR_16BIT,	0xD4E8, 0x0330पूर्ण,
	अणुMISENSOR_16BIT,	0xD4EA, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD4EC, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD4EE, 0x03CDपूर्ण,
	अणुMISENSOR_16BIT,	0xD4F0, 0x050Dपूर्ण,
	अणुMISENSOR_16BIT,	0xD4F2, 0x01C5पूर्ण,
	अणुMISENSOR_16BIT,	0xD4F4, 0x03B3पूर्ण,
	अणुMISENSOR_16BIT,	0xD4F6, 0x00E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD4F8, 0x01E3पूर्ण,
	अणुMISENSOR_16BIT,	0xD4FA, 0x0280पूर्ण,
	अणुMISENSOR_16BIT,	0xD4FC, 0x01E0पूर्ण,
	अणुMISENSOR_16BIT,	0xD4FE, 0x0109पूर्ण,
	अणुMISENSOR_16BIT,	0xD500, 0x0080पूर्ण,
	अणुMISENSOR_16BIT,	0xD502, 0x0500पूर्ण,
	अणुMISENSOR_16BIT,	0xD504, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD506, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD508, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD50A, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD50C, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD50E, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD510, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD512, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD514, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD516, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD518, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD51A, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD51C, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD51E, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xD520, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD522, 0xC9B4पूर्ण,
	अणुMISENSOR_16BIT,	0xD524, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD526, 0xD324पूर्ण,
	अणुMISENSOR_16BIT,	0xD528, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD52A, 0xCA34पूर्ण,
	अणुMISENSOR_16BIT,	0xD52C, 0xFFFFपूर्ण,
	अणुMISENSOR_16BIT,	0xD52E, 0xD3ECपूर्ण,
	अणुMISENSOR_16BIT,	0x098E, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xE000, 0x04B4पूर्ण,
	अणुMISENSOR_16BIT,	0xE002, 0x0302पूर्ण,
	अणुMISENSOR_16BIT,	0xE004, 0x4103पूर्ण,
	अणुMISENSOR_16BIT,	0xE006, 0x0202पूर्ण,
	अणुMISENSOR_16BIT,	0x0080, 0xFFF0पूर्ण,
	अणुMISENSOR_16BIT,	0x0080, 0xFFF1पूर्ण,

	/* PGA parameter and APGA
	 * [Step4-APGA] [TP101_MT9M114_APGA]
	 */
	अणुMISENSOR_16BIT,	0x098E, 0x495Eपूर्ण,
	अणुMISENSOR_16BIT,	0xC95E, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0x3640, 0x02B0पूर्ण,
	अणुMISENSOR_16BIT,	0x3642, 0x8063पूर्ण,
	अणुMISENSOR_16BIT,	0x3644, 0x78D0पूर्ण,
	अणुMISENSOR_16BIT,	0x3646, 0x50CCपूर्ण,
	अणुMISENSOR_16BIT,	0x3648, 0x3511पूर्ण,
	अणुMISENSOR_16BIT,	0x364A, 0x0110पूर्ण,
	अणुMISENSOR_16BIT,	0x364C, 0xBD8Aपूर्ण,
	अणुMISENSOR_16BIT,	0x364E, 0x0CD1पूर्ण,
	अणुMISENSOR_16BIT,	0x3650, 0x24EDपूर्ण,
	अणुMISENSOR_16BIT,	0x3652, 0x7C11पूर्ण,
	अणुMISENSOR_16BIT,	0x3654, 0x0150पूर्ण,
	अणुMISENSOR_16BIT,	0x3656, 0x124Cपूर्ण,
	अणुMISENSOR_16BIT,	0x3658, 0x3130पूर्ण,
	अणुMISENSOR_16BIT,	0x365A, 0x508Cपूर्ण,
	अणुMISENSOR_16BIT,	0x365C, 0x21F1पूर्ण,
	अणुMISENSOR_16BIT,	0x365E, 0x0090पूर्ण,
	अणुMISENSOR_16BIT,	0x3660, 0xBFCAपूर्ण,
	अणुMISENSOR_16BIT,	0x3662, 0x0A11पूर्ण,
	अणुMISENSOR_16BIT,	0x3664, 0x4F4Bपूर्ण,
	अणुMISENSOR_16BIT,	0x3666, 0x28B1पूर्ण,
	अणुMISENSOR_16BIT,	0x3680, 0x50A9पूर्ण,
	अणुMISENSOR_16BIT,	0x3682, 0xA04Bपूर्ण,
	अणुMISENSOR_16BIT,	0x3684, 0x0E2Dपूर्ण,
	अणुMISENSOR_16BIT,	0x3686, 0x73ECपूर्ण,
	अणुMISENSOR_16BIT,	0x3688, 0x164Fपूर्ण,
	अणुMISENSOR_16BIT,	0x368A, 0xF829पूर्ण,
	अणुMISENSOR_16BIT,	0x368C, 0xC1A8पूर्ण,
	अणुMISENSOR_16BIT,	0x368E, 0xB0ECपूर्ण,
	अणुMISENSOR_16BIT,	0x3690, 0xE76Aपूर्ण,
	अणुMISENSOR_16BIT,	0x3692, 0x69AFपूर्ण,
	अणुMISENSOR_16BIT,	0x3694, 0x378Cपूर्ण,
	अणुMISENSOR_16BIT,	0x3696, 0xA70Dपूर्ण,
	अणुMISENSOR_16BIT,	0x3698, 0x884Fपूर्ण,
	अणुMISENSOR_16BIT,	0x369A, 0xEE8Bपूर्ण,
	अणुMISENSOR_16BIT,	0x369C, 0x5DEFपूर्ण,
	अणुMISENSOR_16BIT,	0x369E, 0x27CCपूर्ण,
	अणुMISENSOR_16BIT,	0x36A0, 0xCAACपूर्ण,
	अणुMISENSOR_16BIT,	0x36A2, 0x840Eपूर्ण,
	अणुMISENSOR_16BIT,	0x36A4, 0xDAA9पूर्ण,
	अणुMISENSOR_16BIT,	0x36A6, 0xF00Cपूर्ण,
	अणुMISENSOR_16BIT,	0x36C0, 0x1371पूर्ण,
	अणुMISENSOR_16BIT,	0x36C2, 0x272Fपूर्ण,
	अणुMISENSOR_16BIT,	0x36C4, 0x2293पूर्ण,
	अणुMISENSOR_16BIT,	0x36C6, 0xE6D0पूर्ण,
	अणुMISENSOR_16BIT,	0x36C8, 0xEC32पूर्ण,
	अणुMISENSOR_16BIT,	0x36CA, 0x11B1पूर्ण,
	अणुMISENSOR_16BIT,	0x36CC, 0x7BAFपूर्ण,
	अणुMISENSOR_16BIT,	0x36CE, 0x5813पूर्ण,
	अणुMISENSOR_16BIT,	0x36D0, 0xB871पूर्ण,
	अणुMISENSOR_16BIT,	0x36D2, 0x8913पूर्ण,
	अणुMISENSOR_16BIT,	0x36D4, 0x4610पूर्ण,
	अणुMISENSOR_16BIT,	0x36D6, 0x7EEEपूर्ण,
	अणुMISENSOR_16BIT,	0x36D8, 0x0DF3पूर्ण,
	अणुMISENSOR_16BIT,	0x36DA, 0xB84Fपूर्ण,
	अणुMISENSOR_16BIT,	0x36DC, 0xB532पूर्ण,
	अणुMISENSOR_16BIT,	0x36DE, 0x1171पूर्ण,
	अणुMISENSOR_16BIT,	0x36E0, 0x13CFपूर्ण,
	अणुMISENSOR_16BIT,	0x36E2, 0x22F3पूर्ण,
	अणुMISENSOR_16BIT,	0x36E4, 0xE090पूर्ण,
	अणुMISENSOR_16BIT,	0x36E6, 0x8133पूर्ण,
	अणुMISENSOR_16BIT,	0x3700, 0x88AEपूर्ण,
	अणुMISENSOR_16BIT,	0x3702, 0x00EAपूर्ण,
	अणुMISENSOR_16BIT,	0x3704, 0x344Fपूर्ण,
	अणुMISENSOR_16BIT,	0x3706, 0xEC88पूर्ण,
	अणुMISENSOR_16BIT,	0x3708, 0x3E91पूर्ण,
	अणुMISENSOR_16BIT,	0x370A, 0xF12Dपूर्ण,
	अणुMISENSOR_16BIT,	0x370C, 0xB0EFपूर्ण,
	अणुMISENSOR_16BIT,	0x370E, 0x77CDपूर्ण,
	अणुMISENSOR_16BIT,	0x3710, 0x7930पूर्ण,
	अणुMISENSOR_16BIT,	0x3712, 0x5C12पूर्ण,
	अणुMISENSOR_16BIT,	0x3714, 0x500Cपूर्ण,
	अणुMISENSOR_16BIT,	0x3716, 0x22CEपूर्ण,
	अणुMISENSOR_16BIT,	0x3718, 0x2370पूर्ण,
	अणुMISENSOR_16BIT,	0x371A, 0x258Fपूर्ण,
	अणुMISENSOR_16BIT,	0x371C, 0x3D30पूर्ण,
	अणुMISENSOR_16BIT,	0x371E, 0x370Cपूर्ण,
	अणुMISENSOR_16BIT,	0x3720, 0x03EDपूर्ण,
	अणुMISENSOR_16BIT,	0x3722, 0x9AD0पूर्ण,
	अणुMISENSOR_16BIT,	0x3724, 0x7ECFपूर्ण,
	अणुMISENSOR_16BIT,	0x3726, 0x1093पूर्ण,
	अणुMISENSOR_16BIT,	0x3740, 0x2391पूर्ण,
	अणुMISENSOR_16BIT,	0x3742, 0xAAD0पूर्ण,
	अणुMISENSOR_16BIT,	0x3744, 0x28F2पूर्ण,
	अणुMISENSOR_16BIT,	0x3746, 0xBA4Fपूर्ण,
	अणुMISENSOR_16BIT,	0x3748, 0xC536पूर्ण,
	अणुMISENSOR_16BIT,	0x374A, 0x1472पूर्ण,
	अणुMISENSOR_16BIT,	0x374C, 0xD110पूर्ण,
	अणुMISENSOR_16BIT,	0x374E, 0x2933पूर्ण,
	अणुMISENSOR_16BIT,	0x3750, 0xD0D1पूर्ण,
	अणुMISENSOR_16BIT,	0x3752, 0x9F37पूर्ण,
	अणुMISENSOR_16BIT,	0x3754, 0x34D1पूर्ण,
	अणुMISENSOR_16BIT,	0x3756, 0x1C6Cपूर्ण,
	अणुMISENSOR_16BIT,	0x3758, 0x3FD2पूर्ण,
	अणुMISENSOR_16BIT,	0x375A, 0xCB72पूर्ण,
	अणुMISENSOR_16BIT,	0x375C, 0xBA96पूर्ण,
	अणुMISENSOR_16BIT,	0x375E, 0x1551पूर्ण,
	अणुMISENSOR_16BIT,	0x3760, 0xB74Fपूर्ण,
	अणुMISENSOR_16BIT,	0x3762, 0x1672पूर्ण,
	अणुMISENSOR_16BIT,	0x3764, 0x84F1पूर्ण,
	अणुMISENSOR_16BIT,	0x3766, 0xC2D6पूर्ण,
	अणुMISENSOR_16BIT,	0x3782, 0x01E0पूर्ण,
	अणुMISENSOR_16BIT,	0x3784, 0x0280पूर्ण,
	अणुMISENSOR_16BIT,	0x37C0, 0xA6EAपूर्ण,
	अणुMISENSOR_16BIT,	0x37C2, 0x874Bपूर्ण,
	अणुMISENSOR_16BIT,	0x37C4, 0x85CBपूर्ण,
	अणुMISENSOR_16BIT,	0x37C6, 0x968Aपूर्ण,
	अणुMISENSOR_16BIT,	0x098E, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xC960, 0x0AF0पूर्ण,
	अणुMISENSOR_16BIT,	0xC962, 0x79E2पूर्ण,
	अणुMISENSOR_16BIT,	0xC964, 0x5EC8पूर्ण,
	अणुMISENSOR_16BIT,	0xC966, 0x791Fपूर्ण,
	अणुMISENSOR_16BIT,	0xC968, 0x76EEपूर्ण,
	अणुMISENSOR_16BIT,	0xC96A, 0x0FA0पूर्ण,
	अणुMISENSOR_16BIT,	0xC96C, 0x7DFAपूर्ण,
	अणुMISENSOR_16BIT,	0xC96E, 0x7DAFपूर्ण,
	अणुMISENSOR_16BIT,	0xC970, 0x7E02पूर्ण,
	अणुMISENSOR_16BIT,	0xC972, 0x7E0Aपूर्ण,
	अणुMISENSOR_16BIT,	0xC974, 0x1964पूर्ण,
	अणुMISENSOR_16BIT,	0xC976, 0x7CDCपूर्ण,
	अणुMISENSOR_16BIT,	0xC978, 0x7838पूर्ण,
	अणुMISENSOR_16BIT,	0xC97A, 0x7C2Fपूर्ण,
	अणुMISENSOR_16BIT,	0xC97C, 0x7792पूर्ण,
	अणुMISENSOR_16BIT,	0xC95E, 0x0003पूर्ण,

	/* [Step4-APGA] */
	अणुMISENSOR_16BIT,	0x098E, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xC95E, 0x0003पूर्ण,

	/* [Step5-AWB_CCM]1: LOAD=CCM */
	अणुMISENSOR_16BIT,	0xC892, 0x0267पूर्ण,
	अणुMISENSOR_16BIT,	0xC894, 0xFF1Aपूर्ण,
	अणुMISENSOR_16BIT,	0xC896, 0xFFB3पूर्ण,
	अणुMISENSOR_16BIT,	0xC898, 0xFF80पूर्ण,
	अणुMISENSOR_16BIT,	0xC89A, 0x0166पूर्ण,
	अणुMISENSOR_16BIT,	0xC89C, 0x0003पूर्ण,
	अणुMISENSOR_16BIT,	0xC89E, 0xFF9Aपूर्ण,
	अणुMISENSOR_16BIT,	0xC8A0, 0xFEB4पूर्ण,
	अणुMISENSOR_16BIT,	0xC8A2, 0x024Dपूर्ण,
	अणुMISENSOR_16BIT,	0xC8A4, 0x01BFपूर्ण,
	अणुMISENSOR_16BIT,	0xC8A6, 0xFF01पूर्ण,
	अणुMISENSOR_16BIT,	0xC8A8, 0xFFF3पूर्ण,
	अणुMISENSOR_16BIT,	0xC8AA, 0xFF75पूर्ण,
	अणुMISENSOR_16BIT,	0xC8AC, 0x0198पूर्ण,
	अणुMISENSOR_16BIT,	0xC8AE, 0xFFFDपूर्ण,
	अणुMISENSOR_16BIT,	0xC8B0, 0xFF9Aपूर्ण,
	अणुMISENSOR_16BIT,	0xC8B2, 0xFEE7पूर्ण,
	अणुMISENSOR_16BIT,	0xC8B4, 0x02A8पूर्ण,
	अणुMISENSOR_16BIT,	0xC8B6, 0x01D9पूर्ण,
	अणुMISENSOR_16BIT,	0xC8B8, 0xFF26पूर्ण,
	अणुMISENSOR_16BIT,	0xC8BA, 0xFFF3पूर्ण,
	अणुMISENSOR_16BIT,	0xC8BC, 0xFFB3पूर्ण,
	अणुMISENSOR_16BIT,	0xC8BE, 0x0132पूर्ण,
	अणुMISENSOR_16BIT,	0xC8C0, 0xFFE8पूर्ण,
	अणुMISENSOR_16BIT,	0xC8C2, 0xFFDAपूर्ण,
	अणुMISENSOR_16BIT,	0xC8C4, 0xFECDपूर्ण,
	अणुMISENSOR_16BIT,	0xC8C6, 0x02C2पूर्ण,
	अणुMISENSOR_16BIT,	0xC8C8, 0x0075पूर्ण,
	अणुMISENSOR_16BIT,	0xC8CA, 0x011Cपूर्ण,
	अणुMISENSOR_16BIT,	0xC8CC, 0x009Aपूर्ण,
	अणुMISENSOR_16BIT,	0xC8CE, 0x0105पूर्ण,
	अणुMISENSOR_16BIT,	0xC8D0, 0x00A4पूर्ण,
	अणुMISENSOR_16BIT,	0xC8D2, 0x00ACपूर्ण,
	अणुMISENSOR_16BIT,	0xC8D4, 0x0A8Cपूर्ण,
	अणुMISENSOR_16BIT,	0xC8D6, 0x0F0Aपूर्ण,
	अणुMISENSOR_16BIT,	0xC8D8, 0x1964पूर्ण,

	/* LOAD=AWB */
	अणुMISENSOR_16BIT,	0xC914, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xC916, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xC918, 0x04FFपूर्ण,
	अणुMISENSOR_16BIT,	0xC91A, 0x02CFपूर्ण,
	अणुMISENSOR_16BIT,	0xC904, 0x0033पूर्ण,
	अणुMISENSOR_16BIT,	0xC906, 0x0040पूर्ण,
	अणुMISENSOR_8BIT,   0xC8F2, 0x03पूर्ण,
	अणुMISENSOR_8BIT,   0xC8F3, 0x02पूर्ण,
	अणुMISENSOR_16BIT,	0xC906, 0x003Cपूर्ण,
	अणुMISENSOR_16BIT,	0xC8F4, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xC8F6, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xC8F8, 0x0000पूर्ण,
	अणुMISENSOR_16BIT,	0xC8FA, 0xE724पूर्ण,
	अणुMISENSOR_16BIT,	0xC8FC, 0x1583पूर्ण,
	अणुMISENSOR_16BIT,	0xC8FE, 0x2045पूर्ण,
	अणुMISENSOR_16BIT,	0xC900, 0x05DCपूर्ण,
	अणुMISENSOR_16BIT,	0xC902, 0x007Cपूर्ण,
	अणुMISENSOR_8BIT,   0xC90C, 0x80पूर्ण,
	अणुMISENSOR_8BIT,   0xC90D, 0x80पूर्ण,
	अणुMISENSOR_8BIT,   0xC90E, 0x80पूर्ण,
	अणुMISENSOR_8BIT,   0xC90F, 0x88पूर्ण,
	अणुMISENSOR_8BIT,   0xC910, 0x80पूर्ण,
	अणुMISENSOR_8BIT,   0xC911, 0x80पूर्ण,

	/* LOAD=Step7-CPIPE_Preference */
	अणुMISENSOR_16BIT,	0xC926, 0x0020पूर्ण,
	अणुMISENSOR_16BIT,	0xC928, 0x009Aपूर्ण,
	अणुMISENSOR_16BIT,	0xC946, 0x0070पूर्ण,
	अणुMISENSOR_16BIT,	0xC948, 0x00F3पूर्ण,
	अणुMISENSOR_16BIT,	0xC952, 0x0020पूर्ण,
	अणुMISENSOR_16BIT,	0xC954, 0x009Aपूर्ण,
	अणुMISENSOR_8BIT,   0xC92A, 0x80पूर्ण,
	अणुMISENSOR_8BIT,   0xC92B, 0x4Bपूर्ण,
	अणुMISENSOR_8BIT,   0xC92C, 0x00पूर्ण,
	अणुMISENSOR_8BIT,   0xC92D, 0xFFपूर्ण,
	अणुMISENSOR_8BIT,   0xC92E, 0x3Cपूर्ण,
	अणुMISENSOR_8BIT,   0xC92F, 0x02पूर्ण,
	अणुMISENSOR_8BIT,   0xC930, 0x06पूर्ण,
	अणुMISENSOR_8BIT,   0xC931, 0x64पूर्ण,
	अणुMISENSOR_8BIT,   0xC932, 0x01पूर्ण,
	अणुMISENSOR_8BIT,   0xC933, 0x0Cपूर्ण,
	अणुMISENSOR_8BIT,   0xC934, 0x3Cपूर्ण,
	अणुMISENSOR_8BIT,   0xC935, 0x3Cपूर्ण,
	अणुMISENSOR_8BIT,   0xC936, 0x3Cपूर्ण,
	अणुMISENSOR_8BIT,   0xC937, 0x0Fपूर्ण,
	अणुMISENSOR_8BIT,   0xC938, 0x64पूर्ण,
	अणुMISENSOR_8BIT,   0xC939, 0x64पूर्ण,
	अणुMISENSOR_8BIT,   0xC93A, 0x64पूर्ण,
	अणुMISENSOR_8BIT,   0xC93B, 0x32पूर्ण,
	अणुMISENSOR_16BIT,	0xC93C, 0x0020पूर्ण,
	अणुMISENSOR_16BIT,	0xC93E, 0x009Aपूर्ण,
	अणुMISENSOR_16BIT,	0xC940, 0x00DCपूर्ण,
	अणुMISENSOR_8BIT,   0xC942, 0x38पूर्ण,
	अणुMISENSOR_8BIT,   0xC943, 0x30पूर्ण,
	अणुMISENSOR_8BIT,   0xC944, 0x50पूर्ण,
	अणुMISENSOR_8BIT,   0xC945, 0x19पूर्ण,
	अणुMISENSOR_16BIT,	0xC94A, 0x0230पूर्ण,
	अणुMISENSOR_16BIT,	0xC94C, 0x0010पूर्ण,
	अणुMISENSOR_16BIT,	0xC94E, 0x01CDपूर्ण,
	अणुMISENSOR_8BIT,   0xC950, 0x05पूर्ण,
	अणुMISENSOR_8BIT,   0xC951, 0x40पूर्ण,
	अणुMISENSOR_8BIT,   0xC87B, 0x1Bपूर्ण,
	अणुMISENSOR_8BIT,   0xC878, 0x0Eपूर्ण,
	अणुMISENSOR_16BIT,	0xC890, 0x0080पूर्ण,
	अणुMISENSOR_16BIT,	0xC886, 0x0100पूर्ण,
	अणुMISENSOR_16BIT,	0xC87C, 0x005Aपूर्ण,
	अणुMISENSOR_8BIT,   0xB42A, 0x05पूर्ण,
	अणुMISENSOR_8BIT,   0xA80A, 0x20पूर्ण,

	/* Speed up AE/AWB */
	अणुMISENSOR_16BIT,	0x098E, 0x2802पूर्ण,
	अणुMISENSOR_16BIT,	0xA802, 0x0008पूर्ण,
	अणुMISENSOR_8BIT,   0xC908, 0x01पूर्ण,
	अणुMISENSOR_8BIT,   0xC879, 0x01पूर्ण,
	अणुMISENSOR_8BIT,   0xC909, 0x02पूर्ण,
	अणुMISENSOR_8BIT,   0xA80A, 0x18पूर्ण,
	अणुMISENSOR_8BIT,   0xA80B, 0x18पूर्ण,
	अणुMISENSOR_8BIT,   0xAC16, 0x18पूर्ण,
	अणुMISENSOR_8BIT,   0xC878, 0x0Eपूर्ण,

	अणुMISENSOR_TOK_TERM, 0, 0पूर्ण
पूर्ण;

#पूर्ण_अगर
#पूर्ण_अगर
