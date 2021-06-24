<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * et8ek8_mode.c
 *
 * Copyright (C) 2008 Nokia Corporation
 *
 * Contact: Sakari Ailus <sakari.ailus@iki.fi>
 *          Tuukka Toivonen <tuukkat76@gmail.com>
 */

#समावेश "et8ek8_reg.h"

/*
 * Stingray sensor mode settings क्रम Scooby
 */

/* Mode1_घातeron_Mode2_16VGA_2592x1968_12.07fps */
अटल काष्ठा et8ek8_reglist mode1_घातeron_mode2_16vga_2592x1968_12_07fps = अणु
/* (without the +1)
 * SPCK       = 80 MHz
 * CCP2       = 640 MHz
 * VCO        = 640 MHz
 * VCOUNT     = 84 (2016)
 * HCOUNT     = 137 (3288)
 * CKREF_DIV  = 2
 * CKVAR_DIV  = 200
 * VCO_DIV    = 0
 * SPCK_DIV   = 7
 * MRCK_DIV   = 7
 * LVDSCK_DIV = 0
 */
	.type = ET8EK8_REGLIST_POWERON,
	.mode = अणु
		.sensor_width = 2592,
		.sensor_height = 1968,
		.sensor_winकरोw_origin_x = 0,
		.sensor_winकरोw_origin_y = 0,
		.sensor_winकरोw_width = 2592,
		.sensor_winकरोw_height = 1968,
		.width = 3288,
		.height = 2016,
		.winकरोw_origin_x = 0,
		.winकरोw_origin_y = 0,
		.winकरोw_width = 2592,
		.winकरोw_height = 1968,
		.pixel_घड़ी = 80000000,
		.ext_घड़ी = 9600000,
		.समयperframe = अणु
			.numerator = 100,
			.denominator = 1207
		पूर्ण,
		.max_exp = 2012,
		/* .max_gain = 0, */
		.bus_क्रमmat = MEDIA_BUS_FMT_SGRBG10_1X10,
		.sensitivity = 65536
	पूर्ण,
	.regs = अणु
		/* Need to set firstly */
		अणु ET8EK8_REG_8BIT, 0x126C, 0xCC पूर्ण,
		/* Strobe and Data of CCP2 delay are minimized. */
		अणु ET8EK8_REG_8BIT, 0x1269, 0x00 पूर्ण,
		/* Refined value of Min H_COUNT  */
		अणु ET8EK8_REG_8BIT, 0x1220, 0x89 पूर्ण,
		/* Frequency of SPCK setting (SPCK=MRCK) */
		अणु ET8EK8_REG_8BIT, 0x123A, 0x07 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1241, 0x94 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1242, 0x02 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x124B, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1255, 0xFF पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1256, 0x9F पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1258, 0x00 पूर्ण,
		/* From parallel out to serial out */
		अणु ET8EK8_REG_8BIT, 0x125D, 0x88 पूर्ण,
		/* From w/ embedded data to w/o embedded data */
		अणु ET8EK8_REG_8BIT, 0x125E, 0xC0 पूर्ण,
		/* CCP2 out is from STOP to ACTIVE */
		अणु ET8EK8_REG_8BIT, 0x1263, 0x98 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1268, 0xC6 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1434, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1163, 0x44 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1166, 0x29 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1140, 0x02 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1011, 0x24 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1151, 0x80 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1152, 0x23 पूर्ण,
		/* Initial setting क्रम improvement2 of lower frequency noise */
		अणु ET8EK8_REG_8BIT, 0x1014, 0x05 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1033, 0x06 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1034, 0x79 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1423, 0x3F पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1424, 0x3F पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1426, 0x00 पूर्ण,
		/* Switch of Preset-White-balance (0d:disable / 1d:enable) */
		अणु ET8EK8_REG_8BIT, 0x1439, 0x00 पूर्ण,
		/* Switch of blemish correction (0d:disable / 1d:enable) */
		अणु ET8EK8_REG_8BIT, 0x161F, 0x60 पूर्ण,
		/* Switch of स्वतः noise correction (0d:disable / 1d:enable) */
		अणु ET8EK8_REG_8BIT, 0x1634, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1646, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1648, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x113E, 0x01 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x113F, 0x22 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1239, 0x64 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1238, 0x02 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123B, 0x70 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123A, 0x07 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121B, 0x64 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121D, 0x64 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1221, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1220, 0x89 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1223, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1222, 0x54 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x125D, 0x88 पूर्ण, /* CCP_LVDS_MODE/  */
		अणु ET8EK8_REG_TERM, 0, 0पूर्ण
	पूर्ण
पूर्ण;

/* Mode1_16VGA_2592x1968_13.12fps_DPCM10-8 */
अटल काष्ठा et8ek8_reglist mode1_16vga_2592x1968_13_12fps_dpcm10_8 = अणु
/* (without the +1)
 * SPCK       = 80 MHz
 * CCP2       = 560 MHz
 * VCO        = 560 MHz
 * VCOUNT     = 84 (2016)
 * HCOUNT     = 128 (3072)
 * CKREF_DIV  = 2
 * CKVAR_DIV  = 175
 * VCO_DIV    = 0
 * SPCK_DIV   = 6
 * MRCK_DIV   = 7
 * LVDSCK_DIV = 0
 */
	.type = ET8EK8_REGLIST_MODE,
	.mode = अणु
		.sensor_width = 2592,
		.sensor_height = 1968,
		.sensor_winकरोw_origin_x = 0,
		.sensor_winकरोw_origin_y = 0,
		.sensor_winकरोw_width = 2592,
		.sensor_winकरोw_height = 1968,
		.width = 3072,
		.height = 2016,
		.winकरोw_origin_x = 0,
		.winकरोw_origin_y = 0,
		.winकरोw_width = 2592,
		.winकरोw_height = 1968,
		.pixel_घड़ी = 80000000,
		.ext_घड़ी = 9600000,
		.समयperframe = अणु
			.numerator = 100,
			.denominator = 1292
		पूर्ण,
		.max_exp = 2012,
		/* .max_gain = 0, */
		.bus_क्रमmat = MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8,
		.sensitivity = 65536
	पूर्ण,
	.regs = अणु
		अणु ET8EK8_REG_8BIT, 0x1239, 0x57 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1238, 0x82 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123B, 0x70 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123A, 0x06 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121B, 0x64 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121D, 0x64 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1221, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1220, 0x80 पूर्ण, /* <-changed to v14 7E->80 */
		अणु ET8EK8_REG_8BIT, 0x1223, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1222, 0x54 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x125D, 0x83 पूर्ण, /* CCP_LVDS_MODE/  */
		अणु ET8EK8_REG_TERM, 0, 0पूर्ण
	पूर्ण
पूर्ण;

/* Mode3_4VGA_1296x984_29.99fps_DPCM10-8 */
अटल काष्ठा et8ek8_reglist mode3_4vga_1296x984_29_99fps_dpcm10_8 = अणु
/* (without the +1)
 * SPCK       = 96.5333333333333 MHz
 * CCP2       = 579.2 MHz
 * VCO        = 579.2 MHz
 * VCOUNT     = 84 (2016)
 * HCOUNT     = 133 (3192)
 * CKREF_DIV  = 2
 * CKVAR_DIV  = 181
 * VCO_DIV    = 0
 * SPCK_DIV   = 5
 * MRCK_DIV   = 7
 * LVDSCK_DIV = 0
 */
	.type = ET8EK8_REGLIST_MODE,
	.mode = अणु
		.sensor_width = 2592,
		.sensor_height = 1968,
		.sensor_winकरोw_origin_x = 0,
		.sensor_winकरोw_origin_y = 0,
		.sensor_winकरोw_width = 2592,
		.sensor_winकरोw_height = 1968,
		.width = 3192,
		.height = 1008,
		.winकरोw_origin_x = 0,
		.winकरोw_origin_y = 0,
		.winकरोw_width = 1296,
		.winकरोw_height = 984,
		.pixel_घड़ी = 96533333,
		.ext_घड़ी = 9600000,
		.समयperframe = अणु
			.numerator = 100,
			.denominator = 3000
		पूर्ण,
		.max_exp = 1004,
		/* .max_gain = 0, */
		.bus_क्रमmat = MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8,
		.sensitivity = 65536
	पूर्ण,
	.regs = अणु
		अणु ET8EK8_REG_8BIT, 0x1239, 0x5A पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1238, 0x82 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123B, 0x70 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123A, 0x05 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121B, 0x63 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1220, 0x85 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1221, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1222, 0x54 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1223, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121D, 0x63 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x125D, 0x83 पूर्ण, /* CCP_LVDS_MODE/  */
		अणु ET8EK8_REG_TERM, 0, 0पूर्ण
	पूर्ण
पूर्ण;

/* Mode4_SVGA_864x656_29.88fps */
अटल काष्ठा et8ek8_reglist mode4_svga_864x656_29_88fps = अणु
/* (without the +1)
 * SPCK       = 80 MHz
 * CCP2       = 320 MHz
 * VCO        = 640 MHz
 * VCOUNT     = 84 (2016)
 * HCOUNT     = 166 (3984)
 * CKREF_DIV  = 2
 * CKVAR_DIV  = 200
 * VCO_DIV    = 0
 * SPCK_DIV   = 7
 * MRCK_DIV   = 7
 * LVDSCK_DIV = 1
 */
	.type = ET8EK8_REGLIST_MODE,
	.mode = अणु
		.sensor_width = 2592,
		.sensor_height = 1968,
		.sensor_winकरोw_origin_x = 0,
		.sensor_winकरोw_origin_y = 0,
		.sensor_winकरोw_width = 2592,
		.sensor_winकरोw_height = 1968,
		.width = 3984,
		.height = 672,
		.winकरोw_origin_x = 0,
		.winकरोw_origin_y = 0,
		.winकरोw_width = 864,
		.winकरोw_height = 656,
		.pixel_घड़ी = 80000000,
		.ext_घड़ी = 9600000,
		.समयperframe = अणु
			.numerator = 100,
			.denominator = 2988
		पूर्ण,
		.max_exp = 668,
		/* .max_gain = 0, */
		.bus_क्रमmat = MEDIA_BUS_FMT_SGRBG10_1X10,
		.sensitivity = 65536
	पूर्ण,
	.regs = अणु
		अणु ET8EK8_REG_8BIT, 0x1239, 0x64 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1238, 0x02 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123B, 0x71 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123A, 0x07 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121B, 0x62 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121D, 0x62 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1221, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1220, 0xA6 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1223, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1222, 0x54 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x125D, 0x88 पूर्ण, /* CCP_LVDS_MODE/  */
		अणु ET8EK8_REG_TERM, 0, 0पूर्ण
	पूर्ण
पूर्ण;

/* Mode5_VGA_648x492_29.93fps */
अटल काष्ठा et8ek8_reglist mode5_vga_648x492_29_93fps = अणु
/* (without the +1)
 * SPCK       = 80 MHz
 * CCP2       = 320 MHz
 * VCO        = 640 MHz
 * VCOUNT     = 84 (2016)
 * HCOUNT     = 221 (5304)
 * CKREF_DIV  = 2
 * CKVAR_DIV  = 200
 * VCO_DIV    = 0
 * SPCK_DIV   = 7
 * MRCK_DIV   = 7
 * LVDSCK_DIV = 1
 */
	.type = ET8EK8_REGLIST_MODE,
	.mode = अणु
		.sensor_width = 2592,
		.sensor_height = 1968,
		.sensor_winकरोw_origin_x = 0,
		.sensor_winकरोw_origin_y = 0,
		.sensor_winकरोw_width = 2592,
		.sensor_winकरोw_height = 1968,
		.width = 5304,
		.height = 504,
		.winकरोw_origin_x = 0,
		.winकरोw_origin_y = 0,
		.winकरोw_width = 648,
		.winकरोw_height = 492,
		.pixel_घड़ी = 80000000,
		.ext_घड़ी = 9600000,
		.समयperframe = अणु
			.numerator = 100,
			.denominator = 2993
		पूर्ण,
		.max_exp = 500,
		/* .max_gain = 0, */
		.bus_क्रमmat = MEDIA_BUS_FMT_SGRBG10_1X10,
		.sensitivity = 65536
	पूर्ण,
	.regs = अणु
		अणु ET8EK8_REG_8BIT, 0x1239, 0x64 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1238, 0x02 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123B, 0x71 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123A, 0x07 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121B, 0x61 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121D, 0x61 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1221, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1220, 0xDD पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1223, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1222, 0x54 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x125D, 0x88 पूर्ण, /* CCP_LVDS_MODE/  */
		अणु ET8EK8_REG_TERM, 0, 0पूर्ण
	पूर्ण
पूर्ण;

/* Mode2_16VGA_2592x1968_3.99fps */
अटल काष्ठा et8ek8_reglist mode2_16vga_2592x1968_3_99fps = अणु
/* (without the +1)
 * SPCK       = 80 MHz
 * CCP2       = 640 MHz
 * VCO        = 640 MHz
 * VCOUNT     = 254 (6096)
 * HCOUNT     = 137 (3288)
 * CKREF_DIV  = 2
 * CKVAR_DIV  = 200
 * VCO_DIV    = 0
 * SPCK_DIV   = 7
 * MRCK_DIV   = 7
 * LVDSCK_DIV = 0
 */
	.type = ET8EK8_REGLIST_MODE,
	.mode = अणु
		.sensor_width = 2592,
		.sensor_height = 1968,
		.sensor_winकरोw_origin_x = 0,
		.sensor_winकरोw_origin_y = 0,
		.sensor_winकरोw_width = 2592,
		.sensor_winकरोw_height = 1968,
		.width = 3288,
		.height = 6096,
		.winकरोw_origin_x = 0,
		.winकरोw_origin_y = 0,
		.winकरोw_width = 2592,
		.winकरोw_height = 1968,
		.pixel_घड़ी = 80000000,
		.ext_घड़ी = 9600000,
		.समयperframe = अणु
			.numerator = 100,
			.denominator = 399
		पूर्ण,
		.max_exp = 6092,
		/* .max_gain = 0, */
		.bus_क्रमmat = MEDIA_BUS_FMT_SGRBG10_1X10,
		.sensitivity = 65536
	पूर्ण,
	.regs = अणु
		अणु ET8EK8_REG_8BIT, 0x1239, 0x64 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1238, 0x02 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123B, 0x70 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123A, 0x07 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121B, 0x64 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121D, 0x64 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1221, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1220, 0x89 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1223, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1222, 0xFE पूर्ण,
		अणु ET8EK8_REG_TERM, 0, 0पूर्ण
	पूर्ण
पूर्ण;

/* Mode_648x492_5fps */
अटल काष्ठा et8ek8_reglist mode_648x492_5fps = अणु
/* (without the +1)
 * SPCK       = 13.3333333333333 MHz
 * CCP2       = 53.3333333333333 MHz
 * VCO        = 640 MHz
 * VCOUNT     = 84 (2016)
 * HCOUNT     = 221 (5304)
 * CKREF_DIV  = 2
 * CKVAR_DIV  = 200
 * VCO_DIV    = 5
 * SPCK_DIV   = 7
 * MRCK_DIV   = 7
 * LVDSCK_DIV = 1
 */
	.type = ET8EK8_REGLIST_MODE,
	.mode = अणु
		.sensor_width = 2592,
		.sensor_height = 1968,
		.sensor_winकरोw_origin_x = 0,
		.sensor_winकरोw_origin_y = 0,
		.sensor_winकरोw_width = 2592,
		.sensor_winकरोw_height = 1968,
		.width = 5304,
		.height = 504,
		.winकरोw_origin_x = 0,
		.winकरोw_origin_y = 0,
		.winकरोw_width = 648,
		.winकरोw_height = 492,
		.pixel_घड़ी = 13333333,
		.ext_घड़ी = 9600000,
		.समयperframe = अणु
			.numerator = 100,
			.denominator = 499
		पूर्ण,
		.max_exp = 500,
		/* .max_gain = 0, */
		.bus_क्रमmat = MEDIA_BUS_FMT_SGRBG10_1X10,
		.sensitivity = 65536
	पूर्ण,
	.regs = अणु
		अणु ET8EK8_REG_8BIT, 0x1239, 0x64 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1238, 0x02 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123B, 0x71 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123A, 0x57 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121B, 0x61 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121D, 0x61 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1221, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1220, 0xDD पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1223, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1222, 0x54 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x125D, 0x88 पूर्ण, /* CCP_LVDS_MODE/  */
		अणु ET8EK8_REG_TERM, 0, 0पूर्ण
	पूर्ण
पूर्ण;

/* Mode3_4VGA_1296x984_5fps */
अटल काष्ठा et8ek8_reglist mode3_4vga_1296x984_5fps = अणु
/* (without the +1)
 * SPCK       = 49.4 MHz
 * CCP2       = 395.2 MHz
 * VCO        = 790.4 MHz
 * VCOUNT     = 250 (6000)
 * HCOUNT     = 137 (3288)
 * CKREF_DIV  = 2
 * CKVAR_DIV  = 247
 * VCO_DIV    = 1
 * SPCK_DIV   = 7
 * MRCK_DIV   = 7
 * LVDSCK_DIV = 0
 */
	.type = ET8EK8_REGLIST_MODE,
	.mode = अणु
		.sensor_width = 2592,
		.sensor_height = 1968,
		.sensor_winकरोw_origin_x = 0,
		.sensor_winकरोw_origin_y = 0,
		.sensor_winकरोw_width = 2592,
		.sensor_winकरोw_height = 1968,
		.width = 3288,
		.height = 3000,
		.winकरोw_origin_x = 0,
		.winकरोw_origin_y = 0,
		.winकरोw_width = 1296,
		.winकरोw_height = 984,
		.pixel_घड़ी = 49400000,
		.ext_घड़ी = 9600000,
		.समयperframe = अणु
			.numerator = 100,
			.denominator = 501
		पूर्ण,
		.max_exp = 2996,
		/* .max_gain = 0, */
		.bus_क्रमmat = MEDIA_BUS_FMT_SGRBG10_1X10,
		.sensitivity = 65536
	पूर्ण,
	.regs = अणु
		अणु ET8EK8_REG_8BIT, 0x1239, 0x7B पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1238, 0x82 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123B, 0x70 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123A, 0x17 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121B, 0x63 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121D, 0x63 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1221, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1220, 0x89 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1223, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1222, 0xFA पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x125D, 0x88 पूर्ण, /* CCP_LVDS_MODE/  */
		अणु ET8EK8_REG_TERM, 0, 0पूर्ण
	पूर्ण
पूर्ण;

/* Mode_4VGA_1296x984_25fps_DPCM10-8 */
अटल काष्ठा et8ek8_reglist mode_4vga_1296x984_25fps_dpcm10_8 = अणु
/* (without the +1)
 * SPCK       = 84.2666666666667 MHz
 * CCP2       = 505.6 MHz
 * VCO        = 505.6 MHz
 * VCOUNT     = 88 (2112)
 * HCOUNT     = 133 (3192)
 * CKREF_DIV  = 2
 * CKVAR_DIV  = 158
 * VCO_DIV    = 0
 * SPCK_DIV   = 5
 * MRCK_DIV   = 7
 * LVDSCK_DIV = 0
 */
	.type = ET8EK8_REGLIST_MODE,
	.mode = अणु
		.sensor_width = 2592,
		.sensor_height = 1968,
		.sensor_winकरोw_origin_x = 0,
		.sensor_winकरोw_origin_y = 0,
		.sensor_winकरोw_width = 2592,
		.sensor_winकरोw_height = 1968,
		.width = 3192,
		.height = 1056,
		.winकरोw_origin_x = 0,
		.winकरोw_origin_y = 0,
		.winकरोw_width = 1296,
		.winकरोw_height = 984,
		.pixel_घड़ी = 84266667,
		.ext_घड़ी = 9600000,
		.समयperframe = अणु
			.numerator = 100,
			.denominator = 2500
		पूर्ण,
		.max_exp = 1052,
		/* .max_gain = 0, */
		.bus_क्रमmat = MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8,
		.sensitivity = 65536
	पूर्ण,
	.regs = अणु
		अणु ET8EK8_REG_8BIT, 0x1239, 0x4F पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1238, 0x02 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123B, 0x70 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x123A, 0x05 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121B, 0x63 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1220, 0x85 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1221, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1222, 0x58 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x1223, 0x00 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x121D, 0x63 पूर्ण,
		अणु ET8EK8_REG_8BIT, 0x125D, 0x83 पूर्ण,
		अणु ET8EK8_REG_TERM, 0, 0पूर्ण
	पूर्ण
पूर्ण;

काष्ठा et8ek8_meta_reglist meta_reglist = अणु
	.version = "V14 03-June-2008",
	.reglist = अणु
		अणु .ptr = &mode1_घातeron_mode2_16vga_2592x1968_12_07fps पूर्ण,
		अणु .ptr = &mode1_16vga_2592x1968_13_12fps_dpcm10_8 पूर्ण,
		अणु .ptr = &mode3_4vga_1296x984_29_99fps_dpcm10_8 पूर्ण,
		अणु .ptr = &mode4_svga_864x656_29_88fps पूर्ण,
		अणु .ptr = &mode5_vga_648x492_29_93fps पूर्ण,
		अणु .ptr = &mode2_16vga_2592x1968_3_99fps पूर्ण,
		अणु .ptr = &mode_648x492_5fps पूर्ण,
		अणु .ptr = &mode3_4vga_1296x984_5fps पूर्ण,
		अणु .ptr = &mode_4vga_1296x984_25fps_dpcm10_8 पूर्ण,
		अणु .ptr = शून्य पूर्ण
	पूर्ण
पूर्ण;
