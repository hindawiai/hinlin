<शैली गुरु>
/*
 * Copyright तऊ 2006-2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *
 */

/** @file
 * Integrated TV-out support क्रम the 915GM and 945GM.
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>

#समावेश "i915_drv.h"
#समावेश "intel_connector.h"
#समावेश "intel_display_types.h"
#समावेश "intel_hotplug.h"
#समावेश "intel_tv.h"

क्रमागत tv_margin अणु
	TV_MARGIN_LEFT, TV_MARGIN_TOP,
	TV_MARGIN_RIGHT, TV_MARGIN_BOTTOM
पूर्ण;

काष्ठा पूर्णांकel_tv अणु
	काष्ठा पूर्णांकel_encoder base;

	पूर्णांक type;
पूर्ण;

काष्ठा video_levels अणु
	u16 blank, black;
	u8 burst;
पूर्ण;

काष्ठा color_conversion अणु
	u16 ry, gy, by, ay;
	u16 ru, gu, bu, au;
	u16 rv, gv, bv, av;
पूर्ण;

अटल स्थिर u32 filter_table[] = अणु
	0xB1403000, 0x2E203500, 0x35002E20, 0x3000B140,
	0x35A0B160, 0x2DC02E80, 0xB1403480, 0xB1603000,
	0x2EA03640, 0x34002D80, 0x3000B120, 0x36E0B160,
	0x2D202EF0, 0xB1203380, 0xB1603000, 0x2F303780,
	0x33002CC0, 0x3000B100, 0x3820B160, 0x2C802F50,
	0xB10032A0, 0xB1603000, 0x2F9038C0, 0x32202C20,
	0x3000B0E0, 0x3980B160, 0x2BC02FC0, 0xB0E031C0,
	0xB1603000, 0x2FF03A20, 0x31602B60, 0xB020B0C0,
	0x3AE0B160, 0x2B001810, 0xB0C03120, 0xB140B020,
	0x18283BA0, 0x30C02A80, 0xB020B0A0, 0x3C60B140,
	0x2A201838, 0xB0A03080, 0xB120B020, 0x18383D20,
	0x304029C0, 0xB040B080, 0x3DE0B100, 0x29601848,
	0xB0803000, 0xB100B040, 0x18483EC0, 0xB0402900,
	0xB040B060, 0x3F80B0C0, 0x28801858, 0xB060B080,
	0xB0A0B060, 0x18602820, 0xB0A02820, 0x0000B060,
	0xB1403000, 0x2E203500, 0x35002E20, 0x3000B140,
	0x35A0B160, 0x2DC02E80, 0xB1403480, 0xB1603000,
	0x2EA03640, 0x34002D80, 0x3000B120, 0x36E0B160,
	0x2D202EF0, 0xB1203380, 0xB1603000, 0x2F303780,
	0x33002CC0, 0x3000B100, 0x3820B160, 0x2C802F50,
	0xB10032A0, 0xB1603000, 0x2F9038C0, 0x32202C20,
	0x3000B0E0, 0x3980B160, 0x2BC02FC0, 0xB0E031C0,
	0xB1603000, 0x2FF03A20, 0x31602B60, 0xB020B0C0,
	0x3AE0B160, 0x2B001810, 0xB0C03120, 0xB140B020,
	0x18283BA0, 0x30C02A80, 0xB020B0A0, 0x3C60B140,
	0x2A201838, 0xB0A03080, 0xB120B020, 0x18383D20,
	0x304029C0, 0xB040B080, 0x3DE0B100, 0x29601848,
	0xB0803000, 0xB100B040, 0x18483EC0, 0xB0402900,
	0xB040B060, 0x3F80B0C0, 0x28801858, 0xB060B080,
	0xB0A0B060, 0x18602820, 0xB0A02820, 0x0000B060,
	0x36403000, 0x2D002CC0, 0x30003640, 0x2D0036C0,
	0x35C02CC0, 0x37403000, 0x2C802D40, 0x30003540,
	0x2D8037C0, 0x34C02C40, 0x38403000, 0x2BC02E00,
	0x30003440, 0x2E2038C0, 0x34002B80, 0x39803000,
	0x2B402E40, 0x30003380, 0x2E603A00, 0x33402B00,
	0x3A803040, 0x2A802EA0, 0x30403300, 0x2EC03B40,
	0x32802A40, 0x3C003040, 0x2A002EC0, 0x30803240,
	0x2EC03C80, 0x320029C0, 0x3D403080, 0x29402F00,
	0x308031C0, 0x2F203DC0, 0x31802900, 0x3E8030C0,
	0x28802F40, 0x30C03140, 0x2F203F40, 0x31402840,
	0x28003100, 0x28002F00, 0x00003100, 0x36403000,
	0x2D002CC0, 0x30003640, 0x2D0036C0,
	0x35C02CC0, 0x37403000, 0x2C802D40, 0x30003540,
	0x2D8037C0, 0x34C02C40, 0x38403000, 0x2BC02E00,
	0x30003440, 0x2E2038C0, 0x34002B80, 0x39803000,
	0x2B402E40, 0x30003380, 0x2E603A00, 0x33402B00,
	0x3A803040, 0x2A802EA0, 0x30403300, 0x2EC03B40,
	0x32802A40, 0x3C003040, 0x2A002EC0, 0x30803240,
	0x2EC03C80, 0x320029C0, 0x3D403080, 0x29402F00,
	0x308031C0, 0x2F203DC0, 0x31802900, 0x3E8030C0,
	0x28802F40, 0x30C03140, 0x2F203F40, 0x31402840,
	0x28003100, 0x28002F00, 0x00003100,
पूर्ण;

/*
 * Color conversion values have 3 separate fixed poपूर्णांक क्रमmats:
 *
 * 10 bit fields (ay, au)
 *   1.9 fixed poपूर्णांक (b.bbbbbbbbb)
 * 11 bit fields (ry, by, ru, gu, gv)
 *   exp.mantissa (ee.mmmmmmmmm)
 *   ee = 00 = 10^-1 (0.mmmmmmmmm)
 *   ee = 01 = 10^-2 (0.0mmmmmmmmm)
 *   ee = 10 = 10^-3 (0.00mmmmmmmmm)
 *   ee = 11 = 10^-4 (0.000mmmmmmmmm)
 * 12 bit fields (gy, rv, bu)
 *   exp.mantissa (eee.mmmmmmmmm)
 *   eee = 000 = 10^-1 (0.mmmmmmmmm)
 *   eee = 001 = 10^-2 (0.0mmmmmmmmm)
 *   eee = 010 = 10^-3 (0.00mmmmmmmmm)
 *   eee = 011 = 10^-4 (0.000mmmmmmmmm)
 *   eee = 100 = reserved
 *   eee = 101 = reserved
 *   eee = 110 = reserved
 *   eee = 111 = 10^0 (m.mmmmmmmm) (only usable क्रम 1.0 representation)
 *
 * Saturation and contrast are 8 bits, with their own representation:
 * 8 bit field (saturation, contrast)
 *   exp.mantissa (ee.mmmmmm)
 *   ee = 00 = 10^-1 (0.mmmmmm)
 *   ee = 01 = 10^0 (m.mmmmm)
 *   ee = 10 = 10^1 (mm.mmmm)
 *   ee = 11 = 10^2 (mmm.mmm)
 *
 * Simple conversion function:
 *
 * अटल u32
 * भग्न_to_csc_11(भग्न f)
 * अणु
 *     u32 exp;
 *     u32 mant;
 *     u32 ret;
 *
 *     अगर (f < 0)
 *         f = -f;
 *
 *     अगर (f >= 1) अणु
 *         exp = 0x7;
 *	   mant = 1 << 8;
 *     पूर्ण अन्यथा अणु
 *         क्रम (exp = 0; exp < 3 && f < 0.5; exp++)
 *	   f *= 2.0;
 *         mant = (f * (1 << 9) + 0.5);
 *         अगर (mant >= (1 << 9))
 *             mant = (1 << 9) - 1;
 *     पूर्ण
 *     ret = (exp << 9) | mant;
 *     वापस ret;
 * पूर्ण
 */

/*
 * Behold, magic numbers!  If we plant them they might grow a big
 * s-video cable to the sky... or something.
 *
 * Pre-converted to appropriate hex value.
 */

/*
 * PAL & NTSC values क्रम composite & s-video connections
 */
अटल स्थिर काष्ठा color_conversion ntsc_m_csc_composite = अणु
	.ry = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0104,
	.ru = 0x0733, .gu = 0x052d, .bu = 0x05c7, .au = 0x0200,
	.rv = 0x0340, .gv = 0x030c, .bv = 0x06d0, .av = 0x0200,
पूर्ण;

अटल स्थिर काष्ठा video_levels ntsc_m_levels_composite = अणु
	.blank = 225, .black = 267, .burst = 113,
पूर्ण;

अटल स्थिर काष्ठा color_conversion ntsc_m_csc_svideo = अणु
	.ry = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0133,
	.ru = 0x076a, .gu = 0x0564, .bu = 0x030d, .au = 0x0200,
	.rv = 0x037a, .gv = 0x033d, .bv = 0x06f6, .av = 0x0200,
पूर्ण;

अटल स्थिर काष्ठा video_levels ntsc_m_levels_svideo = अणु
	.blank = 266, .black = 316, .burst = 133,
पूर्ण;

अटल स्थिर काष्ठा color_conversion ntsc_j_csc_composite = अणु
	.ry = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0119,
	.ru = 0x074c, .gu = 0x0546, .bu = 0x05ec, .au = 0x0200,
	.rv = 0x035a, .gv = 0x0322, .bv = 0x06e1, .av = 0x0200,
पूर्ण;

अटल स्थिर काष्ठा video_levels ntsc_j_levels_composite = अणु
	.blank = 225, .black = 225, .burst = 113,
पूर्ण;

अटल स्थिर काष्ठा color_conversion ntsc_j_csc_svideo = अणु
	.ry = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x014c,
	.ru = 0x0788, .gu = 0x0581, .bu = 0x0322, .au = 0x0200,
	.rv = 0x0399, .gv = 0x0356, .bv = 0x070a, .av = 0x0200,
पूर्ण;

अटल स्थिर काष्ठा video_levels ntsc_j_levels_svideo = अणु
	.blank = 266, .black = 266, .burst = 133,
पूर्ण;

अटल स्थिर काष्ठा color_conversion pal_csc_composite = अणु
	.ry = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0113,
	.ru = 0x0745, .gu = 0x053f, .bu = 0x05e1, .au = 0x0200,
	.rv = 0x0353, .gv = 0x031c, .bv = 0x06dc, .av = 0x0200,
पूर्ण;

अटल स्थिर काष्ठा video_levels pal_levels_composite = अणु
	.blank = 237, .black = 237, .burst = 118,
पूर्ण;

अटल स्थिर काष्ठा color_conversion pal_csc_svideo = अणु
	.ry = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0145,
	.ru = 0x0780, .gu = 0x0579, .bu = 0x031c, .au = 0x0200,
	.rv = 0x0390, .gv = 0x034f, .bv = 0x0705, .av = 0x0200,
पूर्ण;

अटल स्थिर काष्ठा video_levels pal_levels_svideo = अणु
	.blank = 280, .black = 280, .burst = 139,
पूर्ण;

अटल स्थिर काष्ठा color_conversion pal_m_csc_composite = अणु
	.ry = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0104,
	.ru = 0x0733, .gu = 0x052d, .bu = 0x05c7, .au = 0x0200,
	.rv = 0x0340, .gv = 0x030c, .bv = 0x06d0, .av = 0x0200,
पूर्ण;

अटल स्थिर काष्ठा video_levels pal_m_levels_composite = अणु
	.blank = 225, .black = 267, .burst = 113,
पूर्ण;

अटल स्थिर काष्ठा color_conversion pal_m_csc_svideo = अणु
	.ry = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0133,
	.ru = 0x076a, .gu = 0x0564, .bu = 0x030d, .au = 0x0200,
	.rv = 0x037a, .gv = 0x033d, .bv = 0x06f6, .av = 0x0200,
पूर्ण;

अटल स्थिर काष्ठा video_levels pal_m_levels_svideo = अणु
	.blank = 266, .black = 316, .burst = 133,
पूर्ण;

अटल स्थिर काष्ठा color_conversion pal_n_csc_composite = अणु
	.ry = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0104,
	.ru = 0x0733, .gu = 0x052d, .bu = 0x05c7, .au = 0x0200,
	.rv = 0x0340, .gv = 0x030c, .bv = 0x06d0, .av = 0x0200,
पूर्ण;

अटल स्थिर काष्ठा video_levels pal_n_levels_composite = अणु
	.blank = 225, .black = 267, .burst = 118,
पूर्ण;

अटल स्थिर काष्ठा color_conversion pal_n_csc_svideo = अणु
	.ry = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0133,
	.ru = 0x076a, .gu = 0x0564, .bu = 0x030d, .au = 0x0200,
	.rv = 0x037a, .gv = 0x033d, .bv = 0x06f6, .av = 0x0200,
पूर्ण;

अटल स्थिर काष्ठा video_levels pal_n_levels_svideo = अणु
	.blank = 266, .black = 316, .burst = 139,
पूर्ण;

/*
 * Component connections
 */
अटल स्थिर काष्ठा color_conversion sdtv_csc_yprpb = अणु
	.ry = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0145,
	.ru = 0x0559, .gu = 0x0353, .bu = 0x0100, .au = 0x0200,
	.rv = 0x0100, .gv = 0x03ad, .bv = 0x074d, .av = 0x0200,
पूर्ण;

अटल स्थिर काष्ठा color_conversion hdtv_csc_yprpb = अणु
	.ry = 0x05b3, .gy = 0x016e, .by = 0x0728, .ay = 0x0145,
	.ru = 0x07d5, .gu = 0x038b, .bu = 0x0100, .au = 0x0200,
	.rv = 0x0100, .gv = 0x03d1, .bv = 0x06bc, .av = 0x0200,
पूर्ण;

अटल स्थिर काष्ठा video_levels component_levels = अणु
	.blank = 279, .black = 279, .burst = 0,
पूर्ण;


काष्ठा tv_mode अणु
	स्थिर अक्षर *name;

	u32 घड़ी;
	u16 refresh; /* in millihertz (क्रम precision) */
	u8 oversample;
	u8 hsync_end;
	u16 hblank_start, hblank_end, htotal;
	bool progressive : 1, trilevel_sync : 1, component_only : 1;
	u8 vsync_start_f1, vsync_start_f2, vsync_len;
	bool veq_ena : 1;
	u8 veq_start_f1, veq_start_f2, veq_len;
	u8 vi_end_f1, vi_end_f2;
	u16 nbr_end;
	bool burst_ena : 1;
	u8 hburst_start, hburst_len;
	u8 vburst_start_f1;
	u16 vburst_end_f1;
	u8 vburst_start_f2;
	u16 vburst_end_f2;
	u8 vburst_start_f3;
	u16 vburst_end_f3;
	u8 vburst_start_f4;
	u16 vburst_end_f4;
	/*
	 * subcarrier programming
	 */
	u16 dda2_size, dda3_size;
	u8 dda1_inc;
	u16 dda2_inc, dda3_inc;
	u32 sc_reset;
	bool pal_burst : 1;
	/*
	 * blank/black levels
	 */
	स्थिर काष्ठा video_levels *composite_levels, *svideo_levels;
	स्थिर काष्ठा color_conversion *composite_color, *svideo_color;
	स्थिर u32 *filter_table;
पूर्ण;


/*
 * Sub carrier DDA
 *
 *  I think this works as follows:
 *
 *  subcarrier freq = pixel_घड़ी * (dda1_inc + dda2_inc / dda2_size) / 4096
 *
 * Presumably, when dda3 is added in, it माला_लो to adjust the dda2_inc value
 *
 * So,
 *  dda1_ideal = subcarrier/pixel * 4096
 *  dda1_inc = न्यूनमान (dda1_ideal)
 *  dda2 = dda1_ideal - dda1_inc
 *
 *  then pick a ratio क्रम dda2 that gives the बंदst approximation. If
 *  you can't get बंद enough, you can play with dda3 as well. This
 *  seems likely to happen when dda2 is small as the jumps would be larger
 *
 * To invert this,
 *
 *  pixel_घड़ी = subcarrier * 4096 / (dda1_inc + dda2_inc / dda2_size)
 *
 * The स्थिरants below were all computed using a 107.520MHz घड़ी
 */

/*
 * Register programming values क्रम TV modes.
 *
 * These values account क्रम -1s required.
 */
अटल स्थिर काष्ठा tv_mode tv_modes[] = अणु
	अणु
		.name		= "NTSC-M",
		.घड़ी		= 108000,
		.refresh	= 59940,
		.oversample	= 8,
		.component_only = false,
		/* 525 Lines, 60 Fields, 15.734KHz line, Sub-Carrier 3.580MHz */

		.hsync_end	= 64,		    .hblank_end		= 124,
		.hblank_start	= 836,		    .htotal		= 857,

		.progressive	= false,	    .trilevel_sync = false,

		.vsync_start_f1	= 6,		    .vsync_start_f2	= 7,
		.vsync_len	= 6,

		.veq_ena	= true,		    .veq_start_f1	= 0,
		.veq_start_f2	= 1,		    .veq_len		= 18,

		.vi_end_f1	= 20,		    .vi_end_f2		= 21,
		.nbr_end	= 240,

		.burst_ena	= true,
		.hburst_start	= 72,		    .hburst_len		= 34,
		.vburst_start_f1 = 9,		    .vburst_end_f1	= 240,
		.vburst_start_f2 = 10,		    .vburst_end_f2	= 240,
		.vburst_start_f3 = 9,		    .vburst_end_f3	= 240,
		.vburst_start_f4 = 10,		    .vburst_end_f4	= 240,

		/* desired 3.5800000 actual 3.5800000 घड़ी 107.52 */
		.dda1_inc	=    135,
		.dda2_inc	=  20800,	    .dda2_size		=  27456,
		.dda3_inc	=      0,	    .dda3_size		=      0,
		.sc_reset	= TV_SC_RESET_EVERY_4,
		.pal_burst	= false,

		.composite_levels = &ntsc_m_levels_composite,
		.composite_color = &ntsc_m_csc_composite,
		.svideo_levels  = &ntsc_m_levels_svideo,
		.svideo_color = &ntsc_m_csc_svideo,

		.filter_table = filter_table,
	पूर्ण,
	अणु
		.name		= "NTSC-443",
		.घड़ी		= 108000,
		.refresh	= 59940,
		.oversample	= 8,
		.component_only = false,
		/* 525 Lines, 60 Fields, 15.734KHz line, Sub-Carrier 4.43MHz */
		.hsync_end	= 64,		    .hblank_end		= 124,
		.hblank_start	= 836,		    .htotal		= 857,

		.progressive	= false,	    .trilevel_sync = false,

		.vsync_start_f1 = 6,		    .vsync_start_f2	= 7,
		.vsync_len	= 6,

		.veq_ena	= true,		    .veq_start_f1	= 0,
		.veq_start_f2	= 1,		    .veq_len		= 18,

		.vi_end_f1	= 20,		    .vi_end_f2		= 21,
		.nbr_end	= 240,

		.burst_ena	= true,
		.hburst_start	= 72,		    .hburst_len		= 34,
		.vburst_start_f1 = 9,		    .vburst_end_f1	= 240,
		.vburst_start_f2 = 10,		    .vburst_end_f2	= 240,
		.vburst_start_f3 = 9,		    .vburst_end_f3	= 240,
		.vburst_start_f4 = 10,		    .vburst_end_f4	= 240,

		/* desired 4.4336180 actual 4.4336180 घड़ी 107.52 */
		.dda1_inc       =    168,
		.dda2_inc       =   4093,       .dda2_size      =  27456,
		.dda3_inc       =    310,       .dda3_size      =    525,
		.sc_reset   = TV_SC_RESET_NEVER,
		.pal_burst  = false,

		.composite_levels = &ntsc_m_levels_composite,
		.composite_color = &ntsc_m_csc_composite,
		.svideo_levels  = &ntsc_m_levels_svideo,
		.svideo_color = &ntsc_m_csc_svideo,

		.filter_table = filter_table,
	पूर्ण,
	अणु
		.name		= "NTSC-J",
		.घड़ी		= 108000,
		.refresh	= 59940,
		.oversample	= 8,
		.component_only = false,

		/* 525 Lines, 60 Fields, 15.734KHz line, Sub-Carrier 3.580MHz */
		.hsync_end	= 64,		    .hblank_end		= 124,
		.hblank_start = 836,	    .htotal		= 857,

		.progressive	= false,    .trilevel_sync = false,

		.vsync_start_f1	= 6,	    .vsync_start_f2	= 7,
		.vsync_len	= 6,

		.veq_ena      = true,	    .veq_start_f1	= 0,
		.veq_start_f2 = 1,	    .veq_len		= 18,

		.vi_end_f1	= 20,		    .vi_end_f2		= 21,
		.nbr_end	= 240,

		.burst_ena	= true,
		.hburst_start	= 72,		    .hburst_len		= 34,
		.vburst_start_f1 = 9,		    .vburst_end_f1	= 240,
		.vburst_start_f2 = 10,		    .vburst_end_f2	= 240,
		.vburst_start_f3 = 9,		    .vburst_end_f3	= 240,
		.vburst_start_f4 = 10,		    .vburst_end_f4	= 240,

		/* desired 3.5800000 actual 3.5800000 घड़ी 107.52 */
		.dda1_inc	=    135,
		.dda2_inc	=  20800,	    .dda2_size		=  27456,
		.dda3_inc	=      0,	    .dda3_size		=      0,
		.sc_reset	= TV_SC_RESET_EVERY_4,
		.pal_burst	= false,

		.composite_levels = &ntsc_j_levels_composite,
		.composite_color = &ntsc_j_csc_composite,
		.svideo_levels  = &ntsc_j_levels_svideo,
		.svideo_color = &ntsc_j_csc_svideo,

		.filter_table = filter_table,
	पूर्ण,
	अणु
		.name		= "PAL-M",
		.घड़ी		= 108000,
		.refresh	= 59940,
		.oversample	= 8,
		.component_only = false,

		/* 525 Lines, 60 Fields, 15.734KHz line, Sub-Carrier 3.580MHz */
		.hsync_end	= 64,		  .hblank_end		= 124,
		.hblank_start = 836,	  .htotal		= 857,

		.progressive	= false,	    .trilevel_sync = false,

		.vsync_start_f1	= 6,		    .vsync_start_f2	= 7,
		.vsync_len	= 6,

		.veq_ena	= true,		    .veq_start_f1	= 0,
		.veq_start_f2	= 1,		    .veq_len		= 18,

		.vi_end_f1	= 20,		    .vi_end_f2		= 21,
		.nbr_end	= 240,

		.burst_ena	= true,
		.hburst_start	= 72,		    .hburst_len		= 34,
		.vburst_start_f1 = 9,		    .vburst_end_f1	= 240,
		.vburst_start_f2 = 10,		    .vburst_end_f2	= 240,
		.vburst_start_f3 = 9,		    .vburst_end_f3	= 240,
		.vburst_start_f4 = 10,		    .vburst_end_f4	= 240,

		/* desired 3.5800000 actual 3.5800000 घड़ी 107.52 */
		.dda1_inc	=    135,
		.dda2_inc	=  16704,	    .dda2_size		=  27456,
		.dda3_inc	=      0,	    .dda3_size		=      0,
		.sc_reset	= TV_SC_RESET_EVERY_8,
		.pal_burst  = true,

		.composite_levels = &pal_m_levels_composite,
		.composite_color = &pal_m_csc_composite,
		.svideo_levels  = &pal_m_levels_svideo,
		.svideo_color = &pal_m_csc_svideo,

		.filter_table = filter_table,
	पूर्ण,
	अणु
		/* 625 Lines, 50 Fields, 15.625KHz line, Sub-Carrier 4.434MHz */
		.name	    = "PAL-N",
		.घड़ी		= 108000,
		.refresh	= 50000,
		.oversample	= 8,
		.component_only = false,

		.hsync_end	= 64,		    .hblank_end		= 128,
		.hblank_start = 844,	    .htotal		= 863,

		.progressive  = false,    .trilevel_sync = false,


		.vsync_start_f1	= 6,	   .vsync_start_f2	= 7,
		.vsync_len	= 6,

		.veq_ena	= true,		    .veq_start_f1	= 0,
		.veq_start_f2	= 1,		    .veq_len		= 18,

		.vi_end_f1	= 24,		    .vi_end_f2		= 25,
		.nbr_end	= 286,

		.burst_ena	= true,
		.hburst_start = 73,	    .hburst_len		= 34,
		.vburst_start_f1 = 8,	    .vburst_end_f1	= 285,
		.vburst_start_f2 = 8,	    .vburst_end_f2	= 286,
		.vburst_start_f3 = 9,	    .vburst_end_f3	= 286,
		.vburst_start_f4 = 9,	    .vburst_end_f4	= 285,


		/* desired 4.4336180 actual 4.4336180 घड़ी 107.52 */
		.dda1_inc       =    135,
		.dda2_inc       =  23578,       .dda2_size      =  27648,
		.dda3_inc       =    134,       .dda3_size      =    625,
		.sc_reset   = TV_SC_RESET_EVERY_8,
		.pal_burst  = true,

		.composite_levels = &pal_n_levels_composite,
		.composite_color = &pal_n_csc_composite,
		.svideo_levels  = &pal_n_levels_svideo,
		.svideo_color = &pal_n_csc_svideo,

		.filter_table = filter_table,
	पूर्ण,
	अणु
		/* 625 Lines, 50 Fields, 15.625KHz line, Sub-Carrier 4.434MHz */
		.name	    = "PAL",
		.घड़ी		= 108000,
		.refresh	= 50000,
		.oversample	= 8,
		.component_only = false,

		.hsync_end	= 64,		    .hblank_end		= 142,
		.hblank_start	= 844,	    .htotal		= 863,

		.progressive	= false,    .trilevel_sync = false,

		.vsync_start_f1	= 5,	    .vsync_start_f2	= 6,
		.vsync_len	= 5,

		.veq_ena	= true,	    .veq_start_f1	= 0,
		.veq_start_f2	= 1,	    .veq_len		= 15,

		.vi_end_f1	= 24,		    .vi_end_f2		= 25,
		.nbr_end	= 286,

		.burst_ena	= true,
		.hburst_start	= 73,		    .hburst_len		= 32,
		.vburst_start_f1 = 8,		    .vburst_end_f1	= 285,
		.vburst_start_f2 = 8,		    .vburst_end_f2	= 286,
		.vburst_start_f3 = 9,		    .vburst_end_f3	= 286,
		.vburst_start_f4 = 9,		    .vburst_end_f4	= 285,

		/* desired 4.4336180 actual 4.4336180 घड़ी 107.52 */
		.dda1_inc       =    168,
		.dda2_inc       =   4122,       .dda2_size      =  27648,
		.dda3_inc       =     67,       .dda3_size      =    625,
		.sc_reset   = TV_SC_RESET_EVERY_8,
		.pal_burst  = true,

		.composite_levels = &pal_levels_composite,
		.composite_color = &pal_csc_composite,
		.svideo_levels  = &pal_levels_svideo,
		.svideo_color = &pal_csc_svideo,

		.filter_table = filter_table,
	पूर्ण,
	अणु
		.name       = "480p",
		.घड़ी		= 108000,
		.refresh	= 59940,
		.oversample     = 4,
		.component_only = true,

		.hsync_end      = 64,               .hblank_end         = 122,
		.hblank_start   = 842,              .htotal             = 857,

		.progressive    = true,		    .trilevel_sync = false,

		.vsync_start_f1 = 12,               .vsync_start_f2     = 12,
		.vsync_len      = 12,

		.veq_ena        = false,

		.vi_end_f1      = 44,               .vi_end_f2          = 44,
		.nbr_end        = 479,

		.burst_ena      = false,

		.filter_table = filter_table,
	पूर्ण,
	अणु
		.name       = "576p",
		.घड़ी		= 108000,
		.refresh	= 50000,
		.oversample     = 4,
		.component_only = true,

		.hsync_end      = 64,               .hblank_end         = 139,
		.hblank_start   = 859,              .htotal             = 863,

		.progressive    = true,		    .trilevel_sync = false,

		.vsync_start_f1 = 10,               .vsync_start_f2     = 10,
		.vsync_len      = 10,

		.veq_ena        = false,

		.vi_end_f1      = 48,               .vi_end_f2          = 48,
		.nbr_end        = 575,

		.burst_ena      = false,

		.filter_table = filter_table,
	पूर्ण,
	अणु
		.name       = "720p@60Hz",
		.घड़ी		= 148500,
		.refresh	= 60000,
		.oversample     = 2,
		.component_only = true,

		.hsync_end      = 80,               .hblank_end         = 300,
		.hblank_start   = 1580,             .htotal             = 1649,

		.progressive	= true,		    .trilevel_sync = true,

		.vsync_start_f1 = 10,               .vsync_start_f2     = 10,
		.vsync_len      = 10,

		.veq_ena        = false,

		.vi_end_f1      = 29,               .vi_end_f2          = 29,
		.nbr_end        = 719,

		.burst_ena      = false,

		.filter_table = filter_table,
	पूर्ण,
	अणु
		.name       = "720p@50Hz",
		.घड़ी		= 148500,
		.refresh	= 50000,
		.oversample     = 2,
		.component_only = true,

		.hsync_end      = 80,               .hblank_end         = 300,
		.hblank_start   = 1580,             .htotal             = 1979,

		.progressive	= true,		    .trilevel_sync = true,

		.vsync_start_f1 = 10,               .vsync_start_f2     = 10,
		.vsync_len      = 10,

		.veq_ena        = false,

		.vi_end_f1      = 29,               .vi_end_f2          = 29,
		.nbr_end        = 719,

		.burst_ena      = false,

		.filter_table = filter_table,
	पूर्ण,
	अणु
		.name       = "1080i@50Hz",
		.घड़ी		= 148500,
		.refresh	= 50000,
		.oversample     = 2,
		.component_only = true,

		.hsync_end      = 88,               .hblank_end         = 235,
		.hblank_start   = 2155,             .htotal             = 2639,

		.progressive	= false,	  .trilevel_sync = true,

		.vsync_start_f1 = 4,              .vsync_start_f2     = 5,
		.vsync_len      = 10,

		.veq_ena	= true,	    .veq_start_f1	= 4,
		.veq_start_f2   = 4,	    .veq_len		= 10,


		.vi_end_f1      = 21,           .vi_end_f2          = 22,
		.nbr_end        = 539,

		.burst_ena      = false,

		.filter_table = filter_table,
	पूर्ण,
	अणु
		.name       = "1080i@60Hz",
		.घड़ी		= 148500,
		.refresh	= 60000,
		.oversample     = 2,
		.component_only = true,

		.hsync_end      = 88,               .hblank_end         = 235,
		.hblank_start   = 2155,             .htotal             = 2199,

		.progressive	= false,	    .trilevel_sync = true,

		.vsync_start_f1 = 4,               .vsync_start_f2     = 5,
		.vsync_len      = 10,

		.veq_ena	= true,		    .veq_start_f1	= 4,
		.veq_start_f2	= 4,		    .veq_len		= 10,


		.vi_end_f1      = 21,               .vi_end_f2          = 22,
		.nbr_end        = 539,

		.burst_ena      = false,

		.filter_table = filter_table,
	पूर्ण,

	अणु
		.name       = "1080p@30Hz",
		.घड़ी		= 148500,
		.refresh	= 30000,
		.oversample     = 2,
		.component_only = true,

		.hsync_end      = 88,               .hblank_end         = 235,
		.hblank_start   = 2155,             .htotal             = 2199,

		.progressive	= true,		    .trilevel_sync = true,

		.vsync_start_f1 = 8,               .vsync_start_f2     = 8,
		.vsync_len      = 10,

		.veq_ena	= false,	.veq_start_f1	= 0,
		.veq_start_f2	= 0,		    .veq_len		= 0,

		.vi_end_f1      = 44,               .vi_end_f2          = 44,
		.nbr_end        = 1079,

		.burst_ena      = false,

		.filter_table = filter_table,
	पूर्ण,

	अणु
		.name       = "1080p@50Hz",
		.घड़ी		= 148500,
		.refresh	= 50000,
		.oversample     = 1,
		.component_only = true,

		.hsync_end      = 88,               .hblank_end         = 235,
		.hblank_start   = 2155,             .htotal             = 2639,

		.progressive	= true,		    .trilevel_sync = true,

		.vsync_start_f1 = 8,               .vsync_start_f2     = 8,
		.vsync_len      = 10,

		.veq_ena	= false,	.veq_start_f1	= 0,
		.veq_start_f2	= 0,		    .veq_len		= 0,

		.vi_end_f1      = 44,               .vi_end_f2          = 44,
		.nbr_end        = 1079,

		.burst_ena      = false,

		.filter_table = filter_table,
	पूर्ण,

	अणु
		.name       = "1080p@60Hz",
		.घड़ी		= 148500,
		.refresh	= 60000,
		.oversample     = 1,
		.component_only = true,

		.hsync_end      = 88,               .hblank_end         = 235,
		.hblank_start   = 2155,             .htotal             = 2199,

		.progressive	= true,		    .trilevel_sync = true,

		.vsync_start_f1 = 8,               .vsync_start_f2     = 8,
		.vsync_len      = 10,

		.veq_ena	= false,		    .veq_start_f1	= 0,
		.veq_start_f2	= 0,		    .veq_len		= 0,

		.vi_end_f1      = 44,               .vi_end_f2          = 44,
		.nbr_end        = 1079,

		.burst_ena      = false,

		.filter_table = filter_table,
	पूर्ण,
पूर्ण;

काष्ठा पूर्णांकel_tv_connector_state अणु
	काष्ठा drm_connector_state base;

	/*
	 * May need to override the user margins क्रम
	 * gen3 >1024 wide source vertical centering.
	 */
	काष्ठा अणु
		u16 top, bottom;
	पूर्ण margins;

	bool bypass_vfilter;
पूर्ण;

#घोषणा to_पूर्णांकel_tv_connector_state(x) container_of(x, काष्ठा पूर्णांकel_tv_connector_state, base)

अटल काष्ठा drm_connector_state *
पूर्णांकel_tv_connector_duplicate_state(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_tv_connector_state *state;

	state = kmemdup(connector->state, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_connector_duplicate_state(connector, &state->base);
	वापस &state->base;
पूर्ण

अटल काष्ठा पूर्णांकel_tv *enc_to_tv(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा पूर्णांकel_tv, base);
पूर्ण

अटल काष्ठा पूर्णांकel_tv *पूर्णांकel_attached_tv(काष्ठा पूर्णांकel_connector *connector)
अणु
	वापस enc_to_tv(पूर्णांकel_attached_encoder(connector));
पूर्ण

अटल bool
पूर्णांकel_tv_get_hw_state(काष्ठा पूर्णांकel_encoder *encoder, क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, TV_CTL);

	*pipe = (पंचांगp & TV_ENC_PIPE_SEL_MASK) >> TV_ENC_PIPE_SEL_SHIFT;

	वापस पंचांगp & TV_ENC_ENABLE;
पूर्ण

अटल व्योम
पूर्णांकel_enable_tv(काष्ठा पूर्णांकel_atomic_state *state,
		काष्ठा पूर्णांकel_encoder *encoder,
		स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
		स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);

	/* Prevents vblank रुकोs from timing out in पूर्णांकel_tv_detect_type() */
	पूर्णांकel_रुको_क्रम_vblank(dev_priv,
			      to_पूर्णांकel_crtc(pipe_config->uapi.crtc)->pipe);

	पूर्णांकel_de_ग_लिखो(dev_priv, TV_CTL,
		       पूर्णांकel_de_पढ़ो(dev_priv, TV_CTL) | TV_ENC_ENABLE);
पूर्ण

अटल व्योम
पूर्णांकel_disable_tv(काष्ठा पूर्णांकel_atomic_state *state,
		 काष्ठा पूर्णांकel_encoder *encoder,
		 स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
		 स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);

	पूर्णांकel_de_ग_लिखो(dev_priv, TV_CTL,
		       पूर्णांकel_de_पढ़ो(dev_priv, TV_CTL) & ~TV_ENC_ENABLE);
पूर्ण

अटल स्थिर काष्ठा tv_mode *पूर्णांकel_tv_mode_find(स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	पूर्णांक क्रमmat = conn_state->tv.mode;

	वापस &tv_modes[क्रमmat];
पूर्ण

अटल क्रमागत drm_mode_status
पूर्णांकel_tv_mode_valid(काष्ठा drm_connector *connector,
		    काष्ठा drm_display_mode *mode)
अणु
	स्थिर काष्ठा tv_mode *tv_mode = पूर्णांकel_tv_mode_find(connector->state);
	पूर्णांक max_करोtclk = to_i915(connector->dev)->max_करोtclk_freq;

	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;

	अगर (mode->घड़ी > max_करोtclk)
		वापस MODE_CLOCK_HIGH;

	/* Ensure TV refresh is बंद to desired refresh */
	अगर (असल(tv_mode->refresh - drm_mode_vrefresh(mode) * 1000) >= 1000)
		वापस MODE_CLOCK_RANGE;

	वापस MODE_OK;
पूर्ण

अटल पूर्णांक
पूर्णांकel_tv_mode_vdisplay(स्थिर काष्ठा tv_mode *tv_mode)
अणु
	अगर (tv_mode->progressive)
		वापस tv_mode->nbr_end + 1;
	अन्यथा
		वापस 2 * (tv_mode->nbr_end + 1);
पूर्ण

अटल व्योम
पूर्णांकel_tv_mode_to_mode(काष्ठा drm_display_mode *mode,
		      स्थिर काष्ठा tv_mode *tv_mode)
अणु
	mode->घड़ी = tv_mode->घड़ी /
		(tv_mode->oversample >> !tv_mode->progressive);

	/*
	 * tv_mode horizontal timings:
	 *
	 * hsync_end
	 *    | hblank_end
	 *    |    | hblank_start
	 *    |    |       | htotal
	 *    |     _______    |
	 *     ____/       \___
	 * \__/                \
	 */
	mode->hdisplay =
		tv_mode->hblank_start - tv_mode->hblank_end;
	mode->hsync_start = mode->hdisplay +
		tv_mode->htotal - tv_mode->hblank_start;
	mode->hsync_end = mode->hsync_start +
		tv_mode->hsync_end;
	mode->htotal = tv_mode->htotal + 1;

	/*
	 * tv_mode vertical timings:
	 *
	 * vsync_start
	 *    | vsync_end
	 *    |  | vi_end nbr_end
	 *    |  |    |       |
	 *    |  |     _______
	 * \__    ____/       \
	 *    \__/
	 */
	mode->vdisplay = पूर्णांकel_tv_mode_vdisplay(tv_mode);
	अगर (tv_mode->progressive) अणु
		mode->vsync_start = mode->vdisplay +
			tv_mode->vsync_start_f1 + 1;
		mode->vsync_end = mode->vsync_start +
			tv_mode->vsync_len;
		mode->vtotal = mode->vdisplay +
			tv_mode->vi_end_f1 + 1;
	पूर्ण अन्यथा अणु
		mode->vsync_start = mode->vdisplay +
			tv_mode->vsync_start_f1 + 1 +
			tv_mode->vsync_start_f2 + 1;
		mode->vsync_end = mode->vsync_start +
			2 * tv_mode->vsync_len;
		mode->vtotal = mode->vdisplay +
			tv_mode->vi_end_f1 + 1 +
			tv_mode->vi_end_f2 + 1;
	पूर्ण

	/* TV has it's own notion of sync and other mode flags, so clear them. */
	mode->flags = 0;

	snम_लिखो(mode->name, माप(mode->name),
		 "%dx%d%c (%s)",
		 mode->hdisplay, mode->vdisplay,
		 tv_mode->progressive ? 'p' : 'i',
		 tv_mode->name);
पूर्ण

अटल व्योम पूर्णांकel_tv_scale_mode_horiz(काष्ठा drm_display_mode *mode,
				      पूर्णांक hdisplay, पूर्णांक left_margin,
				      पूर्णांक right_margin)
अणु
	पूर्णांक hsync_start = mode->hsync_start - mode->hdisplay + right_margin;
	पूर्णांक hsync_end = mode->hsync_end - mode->hdisplay + right_margin;
	पूर्णांक new_htotal = mode->htotal * hdisplay /
		(mode->hdisplay - left_margin - right_margin);

	mode->घड़ी = mode->घड़ी * new_htotal / mode->htotal;

	mode->hdisplay = hdisplay;
	mode->hsync_start = hdisplay + hsync_start * new_htotal / mode->htotal;
	mode->hsync_end = hdisplay + hsync_end * new_htotal / mode->htotal;
	mode->htotal = new_htotal;
पूर्ण

अटल व्योम पूर्णांकel_tv_scale_mode_vert(काष्ठा drm_display_mode *mode,
				     पूर्णांक vdisplay, पूर्णांक top_margin,
				     पूर्णांक bottom_margin)
अणु
	पूर्णांक vsync_start = mode->vsync_start - mode->vdisplay + bottom_margin;
	पूर्णांक vsync_end = mode->vsync_end - mode->vdisplay + bottom_margin;
	पूर्णांक new_vtotal = mode->vtotal * vdisplay /
		(mode->vdisplay - top_margin - bottom_margin);

	mode->घड़ी = mode->घड़ी * new_vtotal / mode->vtotal;

	mode->vdisplay = vdisplay;
	mode->vsync_start = vdisplay + vsync_start * new_vtotal / mode->vtotal;
	mode->vsync_end = vdisplay + vsync_end * new_vtotal / mode->vtotal;
	mode->vtotal = new_vtotal;
पूर्ण

अटल व्योम
पूर्णांकel_tv_get_config(काष्ठा पूर्णांकel_encoder *encoder,
		    काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा drm_display_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;
	काष्ठा drm_display_mode mode = अणुपूर्ण;
	u32 tv_ctl, hctl1, hctl3, vctl1, vctl2, पंचांगp;
	काष्ठा tv_mode tv_mode = अणुपूर्ण;
	पूर्णांक hdisplay = adjusted_mode->crtc_hdisplay;
	पूर्णांक vdisplay = adjusted_mode->crtc_vdisplay;
	पूर्णांक xsize, ysize, xpos, ypos;

	pipe_config->output_types |= BIT(INTEL_OUTPUT_TVOUT);

	tv_ctl = पूर्णांकel_de_पढ़ो(dev_priv, TV_CTL);
	hctl1 = पूर्णांकel_de_पढ़ो(dev_priv, TV_H_CTL_1);
	hctl3 = पूर्णांकel_de_पढ़ो(dev_priv, TV_H_CTL_3);
	vctl1 = पूर्णांकel_de_पढ़ो(dev_priv, TV_V_CTL_1);
	vctl2 = पूर्णांकel_de_पढ़ो(dev_priv, TV_V_CTL_2);

	tv_mode.htotal = (hctl1 & TV_HTOTAL_MASK) >> TV_HTOTAL_SHIFT;
	tv_mode.hsync_end = (hctl1 & TV_HSYNC_END_MASK) >> TV_HSYNC_END_SHIFT;

	tv_mode.hblank_start = (hctl3 & TV_HBLANK_START_MASK) >> TV_HBLANK_START_SHIFT;
	tv_mode.hblank_end = (hctl3 & TV_HSYNC_END_MASK) >> TV_HBLANK_END_SHIFT;

	tv_mode.nbr_end = (vctl1 & TV_NBR_END_MASK) >> TV_NBR_END_SHIFT;
	tv_mode.vi_end_f1 = (vctl1 & TV_VI_END_F1_MASK) >> TV_VI_END_F1_SHIFT;
	tv_mode.vi_end_f2 = (vctl1 & TV_VI_END_F2_MASK) >> TV_VI_END_F2_SHIFT;

	tv_mode.vsync_len = (vctl2 & TV_VSYNC_LEN_MASK) >> TV_VSYNC_LEN_SHIFT;
	tv_mode.vsync_start_f1 = (vctl2 & TV_VSYNC_START_F1_MASK) >> TV_VSYNC_START_F1_SHIFT;
	tv_mode.vsync_start_f2 = (vctl2 & TV_VSYNC_START_F2_MASK) >> TV_VSYNC_START_F2_SHIFT;

	tv_mode.घड़ी = pipe_config->port_घड़ी;

	tv_mode.progressive = tv_ctl & TV_PROGRESSIVE;

	चयन (tv_ctl & TV_OVERSAMPLE_MASK) अणु
	हाल TV_OVERSAMPLE_8X:
		tv_mode.oversample = 8;
		अवरोध;
	हाल TV_OVERSAMPLE_4X:
		tv_mode.oversample = 4;
		अवरोध;
	हाल TV_OVERSAMPLE_2X:
		tv_mode.oversample = 2;
		अवरोध;
	शेष:
		tv_mode.oversample = 1;
		अवरोध;
	पूर्ण

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, TV_WIN_POS);
	xpos = पंचांगp >> 16;
	ypos = पंचांगp & 0xffff;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, TV_WIN_SIZE);
	xsize = पंचांगp >> 16;
	ysize = पंचांगp & 0xffff;

	पूर्णांकel_tv_mode_to_mode(&mode, &tv_mode);

	drm_dbg_kms(&dev_priv->drm, "TV mode:\n");
	drm_mode_debug_prपूर्णांकmodeline(&mode);

	पूर्णांकel_tv_scale_mode_horiz(&mode, hdisplay,
				  xpos, mode.hdisplay - xsize - xpos);
	पूर्णांकel_tv_scale_mode_vert(&mode, vdisplay,
				 ypos, mode.vdisplay - ysize - ypos);

	adjusted_mode->crtc_घड़ी = mode.घड़ी;
	अगर (adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE)
		adjusted_mode->crtc_घड़ी /= 2;

	/* pixel counter करोesn't work on i965gm TV output */
	अगर (IS_I965GM(dev_priv))
		pipe_config->mode_flags |=
			I915_MODE_FLAG_USE_SCANLINE_COUNTER;
पूर्ण

अटल bool पूर्णांकel_tv_source_too_wide(काष्ठा drm_i915_निजी *dev_priv,
				     पूर्णांक hdisplay)
अणु
	वापस IS_DISPLAY_VER(dev_priv, 3) && hdisplay > 1024;
पूर्ण

अटल bool पूर्णांकel_tv_vert_scaling(स्थिर काष्ठा drm_display_mode *tv_mode,
				  स्थिर काष्ठा drm_connector_state *conn_state,
				  पूर्णांक vdisplay)
अणु
	वापस tv_mode->crtc_vdisplay -
		conn_state->tv.margins.top -
		conn_state->tv.margins.bottom !=
		vdisplay;
पूर्ण

अटल पूर्णांक
पूर्णांकel_tv_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
			काष्ठा पूर्णांकel_crtc_state *pipe_config,
			काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_tv_connector_state *tv_conn_state =
		to_पूर्णांकel_tv_connector_state(conn_state);
	स्थिर काष्ठा tv_mode *tv_mode = पूर्णांकel_tv_mode_find(conn_state);
	काष्ठा drm_display_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;
	पूर्णांक hdisplay = adjusted_mode->crtc_hdisplay;
	पूर्णांक vdisplay = adjusted_mode->crtc_vdisplay;

	अगर (!tv_mode)
		वापस -EINVAL;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस -EINVAL;

	pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;

	drm_dbg_kms(&dev_priv->drm, "forcing bpc to 8 for TV\n");
	pipe_config->pipe_bpp = 8*3;

	pipe_config->port_घड़ी = tv_mode->घड़ी;

	पूर्णांकel_tv_mode_to_mode(adjusted_mode, tv_mode);
	drm_mode_set_crtcinfo(adjusted_mode, 0);

	अगर (पूर्णांकel_tv_source_too_wide(dev_priv, hdisplay) ||
	    !पूर्णांकel_tv_vert_scaling(adjusted_mode, conn_state, vdisplay)) अणु
		पूर्णांक extra, top, bottom;

		extra = adjusted_mode->crtc_vdisplay - vdisplay;

		अगर (extra < 0) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "No vertical scaling for >1024 pixel wide modes\n");
			वापस -EINVAL;
		पूर्ण

		/* Need to turn off the vertical filter and center the image */

		/* Attempt to मुख्यtain the relative sizes of the margins */
		top = conn_state->tv.margins.top;
		bottom = conn_state->tv.margins.bottom;

		अगर (top + bottom)
			top = extra * top / (top + bottom);
		अन्यथा
			top = extra / 2;
		bottom = extra - top;

		tv_conn_state->margins.top = top;
		tv_conn_state->margins.bottom = bottom;

		tv_conn_state->bypass_vfilter = true;

		अगर (!tv_mode->progressive) अणु
			adjusted_mode->घड़ी /= 2;
			adjusted_mode->crtc_घड़ी /= 2;
			adjusted_mode->flags |= DRM_MODE_FLAG_INTERLACE;
		पूर्ण
	पूर्ण अन्यथा अणु
		tv_conn_state->margins.top = conn_state->tv.margins.top;
		tv_conn_state->margins.bottom = conn_state->tv.margins.bottom;

		tv_conn_state->bypass_vfilter = false;
	पूर्ण

	drm_dbg_kms(&dev_priv->drm, "TV mode:\n");
	drm_mode_debug_prपूर्णांकmodeline(adjusted_mode);

	/*
	 * The pipe scanline counter behaviour looks as follows when
	 * using the TV encoder:
	 *
	 * समय ->
	 *
	 * dsl=vtotal-1       |             |
	 *                   ||            ||
	 *               ___| |        ___| |
	 *              /     |       /     |
	 *             /      |      /      |
	 * dsl=0   ___/       |_____/       |
	 *        | | |  |  | |
	 *         ^ ^ ^   ^ ^
	 *         | | |   | pipe vblank/first part of tv vblank
	 *         | | |   bottom margin
	 *         | | active
	 *         | top margin
	 *         reमुख्यder of tv vblank
	 *
	 * When the TV encoder is used the pipe wants to run faster
	 * than expected rate. During the active portion the TV
	 * encoder stalls the pipe every few lines to keep it in
	 * check. When the TV encoder reaches the bottom margin the
	 * pipe simply stops. Once we reach the TV vblank the pipe is
	 * no दीर्घer stalled and it runs at the max rate (apparently
	 * oversample घड़ी on gen3, cdclk on gen4). Once the pipe
	 * reaches the pipe vtotal the pipe stops क्रम the reमुख्यder
	 * of the TV vblank/top margin. The pipe starts up again when
	 * the TV encoder निकासs the top margin.
	 *
	 * To aव्योम huge hassles क्रम vblank बारtamping we scale
	 * the pipe timings as अगर the pipe always runs at the average
	 * rate it मुख्यtains during the active period. This also
	 * gives us a reasonable guesstimate as to the pixel rate.
	 * Due to the variation in the actual pipe speed the scanline
	 * counter will give us slightly erroneous results during the
	 * TV vblank/margins. But since vtotal was selected such that
	 * it matches the average rate of the pipe during the active
	 * portion the error shouldn't cause any serious grief to
	 * vblank बारtamps.
	 *
	 * For posterity here is the empirically derived क्रमmula
	 * that gives us the maximum length of the pipe vblank
	 * we can use without causing display corruption. Following
	 * this would allow us to have a ticking scanline counter
	 * everywhere except during the bottom margin (there the
	 * pipe always stops). Ie. this would eliminate the second
	 * flat portion of the above graph. However this would also
	 * complicate vblank बारtamping as the pipe vtotal would
	 * no दीर्घer match the average rate the pipe runs at during
	 * the active portion. Hence following this क्रमmula seems
	 * more trouble that it's worth.
	 *
	 * अगर (IS_GEN(dev_priv, 4)) अणु
	 *	num = cdclk * (tv_mode->oversample >> !tv_mode->progressive);
	 *	den = tv_mode->घड़ी;
	 * पूर्ण अन्यथा अणु
	 *	num = tv_mode->oversample >> !tv_mode->progressive;
	 *	den = 1;
	 * पूर्ण
	 * max_pipe_vblank_len ~=
	 *	(num * tv_htotal * (tv_vblank_len + top_margin)) /
	 *	(den * pipe_htotal);
	 */
	पूर्णांकel_tv_scale_mode_horiz(adjusted_mode, hdisplay,
				  conn_state->tv.margins.left,
				  conn_state->tv.margins.right);
	पूर्णांकel_tv_scale_mode_vert(adjusted_mode, vdisplay,
				 tv_conn_state->margins.top,
				 tv_conn_state->margins.bottom);
	drm_mode_set_crtcinfo(adjusted_mode, 0);
	adjusted_mode->name[0] = '\0';

	/* pixel counter करोesn't work on i965gm TV output */
	अगर (IS_I965GM(dev_priv))
		pipe_config->mode_flags |=
			I915_MODE_FLAG_USE_SCANLINE_COUNTER;

	वापस 0;
पूर्ण

अटल व्योम
set_tv_mode_timings(काष्ठा drm_i915_निजी *dev_priv,
		    स्थिर काष्ठा tv_mode *tv_mode,
		    bool burst_ena)
अणु
	u32 hctl1, hctl2, hctl3;
	u32 vctl1, vctl2, vctl3, vctl4, vctl5, vctl6, vctl7;

	hctl1 = (tv_mode->hsync_end << TV_HSYNC_END_SHIFT) |
		(tv_mode->htotal << TV_HTOTAL_SHIFT);

	hctl2 = (tv_mode->hburst_start << 16) |
		(tv_mode->hburst_len << TV_HBURST_LEN_SHIFT);

	अगर (burst_ena)
		hctl2 |= TV_BURST_ENA;

	hctl3 = (tv_mode->hblank_start << TV_HBLANK_START_SHIFT) |
		(tv_mode->hblank_end << TV_HBLANK_END_SHIFT);

	vctl1 = (tv_mode->nbr_end << TV_NBR_END_SHIFT) |
		(tv_mode->vi_end_f1 << TV_VI_END_F1_SHIFT) |
		(tv_mode->vi_end_f2 << TV_VI_END_F2_SHIFT);

	vctl2 = (tv_mode->vsync_len << TV_VSYNC_LEN_SHIFT) |
		(tv_mode->vsync_start_f1 << TV_VSYNC_START_F1_SHIFT) |
		(tv_mode->vsync_start_f2 << TV_VSYNC_START_F2_SHIFT);

	vctl3 = (tv_mode->veq_len << TV_VEQ_LEN_SHIFT) |
		(tv_mode->veq_start_f1 << TV_VEQ_START_F1_SHIFT) |
		(tv_mode->veq_start_f2 << TV_VEQ_START_F2_SHIFT);

	अगर (tv_mode->veq_ena)
		vctl3 |= TV_EQUAL_ENA;

	vctl4 = (tv_mode->vburst_start_f1 << TV_VBURST_START_F1_SHIFT) |
		(tv_mode->vburst_end_f1 << TV_VBURST_END_F1_SHIFT);

	vctl5 = (tv_mode->vburst_start_f2 << TV_VBURST_START_F2_SHIFT) |
		(tv_mode->vburst_end_f2 << TV_VBURST_END_F2_SHIFT);

	vctl6 = (tv_mode->vburst_start_f3 << TV_VBURST_START_F3_SHIFT) |
		(tv_mode->vburst_end_f3 << TV_VBURST_END_F3_SHIFT);

	vctl7 = (tv_mode->vburst_start_f4 << TV_VBURST_START_F4_SHIFT) |
		(tv_mode->vburst_end_f4 << TV_VBURST_END_F4_SHIFT);

	पूर्णांकel_de_ग_लिखो(dev_priv, TV_H_CTL_1, hctl1);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_H_CTL_2, hctl2);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_H_CTL_3, hctl3);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_V_CTL_1, vctl1);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_V_CTL_2, vctl2);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_V_CTL_3, vctl3);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_V_CTL_4, vctl4);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_V_CTL_5, vctl5);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_V_CTL_6, vctl6);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_V_CTL_7, vctl7);
पूर्ण

अटल व्योम set_color_conversion(काष्ठा drm_i915_निजी *dev_priv,
				 स्थिर काष्ठा color_conversion *color_conversion)
अणु
	अगर (!color_conversion)
		वापस;

	पूर्णांकel_de_ग_लिखो(dev_priv, TV_CSC_Y,
		       (color_conversion->ry << 16) | color_conversion->gy);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_CSC_Y2,
		       (color_conversion->by << 16) | color_conversion->ay);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_CSC_U,
		       (color_conversion->ru << 16) | color_conversion->gu);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_CSC_U2,
		       (color_conversion->bu << 16) | color_conversion->au);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_CSC_V,
		       (color_conversion->rv << 16) | color_conversion->gv);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_CSC_V2,
		       (color_conversion->bv << 16) | color_conversion->av);
पूर्ण

अटल व्योम पूर्णांकel_tv_pre_enable(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	काष्ठा पूर्णांकel_tv *पूर्णांकel_tv = enc_to_tv(encoder);
	स्थिर काष्ठा पूर्णांकel_tv_connector_state *tv_conn_state =
		to_पूर्णांकel_tv_connector_state(conn_state);
	स्थिर काष्ठा tv_mode *tv_mode = पूर्णांकel_tv_mode_find(conn_state);
	u32 tv_ctl, tv_filter_ctl;
	u32 scctl1, scctl2, scctl3;
	पूर्णांक i, j;
	स्थिर काष्ठा video_levels *video_levels;
	स्थिर काष्ठा color_conversion *color_conversion;
	bool burst_ena;
	पूर्णांक xpos, ypos;
	अचिन्हित पूर्णांक xsize, ysize;

	अगर (!tv_mode)
		वापस;	/* can't happen (mode_prepare prevents this) */

	tv_ctl = पूर्णांकel_de_पढ़ो(dev_priv, TV_CTL);
	tv_ctl &= TV_CTL_SAVE;

	चयन (पूर्णांकel_tv->type) अणु
	शेष:
	हाल DRM_MODE_CONNECTOR_Unknown:
	हाल DRM_MODE_CONNECTOR_Composite:
		tv_ctl |= TV_ENC_OUTPUT_COMPOSITE;
		video_levels = tv_mode->composite_levels;
		color_conversion = tv_mode->composite_color;
		burst_ena = tv_mode->burst_ena;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_Component:
		tv_ctl |= TV_ENC_OUTPUT_COMPONENT;
		video_levels = &component_levels;
		अगर (tv_mode->burst_ena)
			color_conversion = &sdtv_csc_yprpb;
		अन्यथा
			color_conversion = &hdtv_csc_yprpb;
		burst_ena = false;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_SVIDEO:
		tv_ctl |= TV_ENC_OUTPUT_SVIDEO;
		video_levels = tv_mode->svideo_levels;
		color_conversion = tv_mode->svideo_color;
		burst_ena = tv_mode->burst_ena;
		अवरोध;
	पूर्ण

	tv_ctl |= TV_ENC_PIPE_SEL(पूर्णांकel_crtc->pipe);

	चयन (tv_mode->oversample) अणु
	हाल 8:
		tv_ctl |= TV_OVERSAMPLE_8X;
		अवरोध;
	हाल 4:
		tv_ctl |= TV_OVERSAMPLE_4X;
		अवरोध;
	हाल 2:
		tv_ctl |= TV_OVERSAMPLE_2X;
		अवरोध;
	शेष:
		tv_ctl |= TV_OVERSAMPLE_NONE;
		अवरोध;
	पूर्ण

	अगर (tv_mode->progressive)
		tv_ctl |= TV_PROGRESSIVE;
	अगर (tv_mode->trilevel_sync)
		tv_ctl |= TV_TRILEVEL_SYNC;
	अगर (tv_mode->pal_burst)
		tv_ctl |= TV_PAL_BURST;

	scctl1 = 0;
	अगर (tv_mode->dda1_inc)
		scctl1 |= TV_SC_DDA1_EN;
	अगर (tv_mode->dda2_inc)
		scctl1 |= TV_SC_DDA2_EN;
	अगर (tv_mode->dda3_inc)
		scctl1 |= TV_SC_DDA3_EN;
	scctl1 |= tv_mode->sc_reset;
	अगर (video_levels)
		scctl1 |= video_levels->burst << TV_BURST_LEVEL_SHIFT;
	scctl1 |= tv_mode->dda1_inc << TV_SCDDA1_INC_SHIFT;

	scctl2 = tv_mode->dda2_size << TV_SCDDA2_SIZE_SHIFT |
		tv_mode->dda2_inc << TV_SCDDA2_INC_SHIFT;

	scctl3 = tv_mode->dda3_size << TV_SCDDA3_SIZE_SHIFT |
		tv_mode->dda3_inc << TV_SCDDA3_INC_SHIFT;

	/* Enable two fixes क्रम the chips that need them. */
	अगर (IS_I915GM(dev_priv))
		tv_ctl |= TV_ENC_C0_FIX | TV_ENC_SDP_FIX;

	set_tv_mode_timings(dev_priv, tv_mode, burst_ena);

	पूर्णांकel_de_ग_लिखो(dev_priv, TV_SC_CTL_1, scctl1);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_SC_CTL_2, scctl2);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_SC_CTL_3, scctl3);

	set_color_conversion(dev_priv, color_conversion);

	अगर (DISPLAY_VER(dev_priv) >= 4)
		पूर्णांकel_de_ग_लिखो(dev_priv, TV_CLR_KNOBS, 0x00404000);
	अन्यथा
		पूर्णांकel_de_ग_लिखो(dev_priv, TV_CLR_KNOBS, 0x00606000);

	अगर (video_levels)
		पूर्णांकel_de_ग_लिखो(dev_priv, TV_CLR_LEVEL,
			       ((video_levels->black << TV_BLACK_LEVEL_SHIFT) | (video_levels->blank << TV_BLANK_LEVEL_SHIFT)));

	निश्चित_pipe_disabled(dev_priv, pipe_config->cpu_transcoder);

	/* Filter ctl must be set beक्रमe TV_WIN_SIZE */
	tv_filter_ctl = TV_AUTO_SCALE;
	अगर (tv_conn_state->bypass_vfilter)
		tv_filter_ctl |= TV_V_FILTER_BYPASS;
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_FILTER_CTL_1, tv_filter_ctl);

	xsize = tv_mode->hblank_start - tv_mode->hblank_end;
	ysize = पूर्णांकel_tv_mode_vdisplay(tv_mode);

	xpos = conn_state->tv.margins.left;
	ypos = tv_conn_state->margins.top;
	xsize -= (conn_state->tv.margins.left +
		  conn_state->tv.margins.right);
	ysize -= (tv_conn_state->margins.top +
		  tv_conn_state->margins.bottom);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_WIN_POS, (xpos << 16) | ypos);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_WIN_SIZE, (xsize << 16) | ysize);

	j = 0;
	क्रम (i = 0; i < 60; i++)
		पूर्णांकel_de_ग_लिखो(dev_priv, TV_H_LUMA(i),
			       tv_mode->filter_table[j++]);
	क्रम (i = 0; i < 60; i++)
		पूर्णांकel_de_ग_लिखो(dev_priv, TV_H_CHROMA(i),
			       tv_mode->filter_table[j++]);
	क्रम (i = 0; i < 43; i++)
		पूर्णांकel_de_ग_लिखो(dev_priv, TV_V_LUMA(i),
			       tv_mode->filter_table[j++]);
	क्रम (i = 0; i < 43; i++)
		पूर्णांकel_de_ग_लिखो(dev_priv, TV_V_CHROMA(i),
			       tv_mode->filter_table[j++]);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_DAC,
		       पूर्णांकel_de_पढ़ो(dev_priv, TV_DAC) & TV_DAC_SAVE);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_CTL, tv_ctl);
पूर्ण

अटल पूर्णांक
पूर्णांकel_tv_detect_type(काष्ठा पूर्णांकel_tv *पूर्णांकel_tv,
		      काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_crtc *crtc = connector->state->crtc;
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc);
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 tv_ctl, save_tv_ctl;
	u32 tv_dac, save_tv_dac;
	पूर्णांक type;

	/* Disable TV पूर्णांकerrupts around load detect or we'll recurse */
	अगर (connector->polled & DRM_CONNECTOR_POLL_HPD) अणु
		spin_lock_irq(&dev_priv->irq_lock);
		i915_disable_pipestat(dev_priv, 0,
				      PIPE_HOTPLUG_INTERRUPT_STATUS |
				      PIPE_HOTPLUG_TV_INTERRUPT_STATUS);
		spin_unlock_irq(&dev_priv->irq_lock);
	पूर्ण

	save_tv_dac = tv_dac = पूर्णांकel_de_पढ़ो(dev_priv, TV_DAC);
	save_tv_ctl = tv_ctl = पूर्णांकel_de_पढ़ो(dev_priv, TV_CTL);

	/* Poll क्रम TV detection */
	tv_ctl &= ~(TV_ENC_ENABLE | TV_ENC_PIPE_SEL_MASK | TV_TEST_MODE_MASK);
	tv_ctl |= TV_TEST_MODE_MONITOR_DETECT;
	tv_ctl |= TV_ENC_PIPE_SEL(पूर्णांकel_crtc->pipe);

	tv_dac &= ~(TVDAC_SENSE_MASK | DAC_A_MASK | DAC_B_MASK | DAC_C_MASK);
	tv_dac |= (TVDAC_STATE_CHG_EN |
		   TVDAC_A_SENSE_CTL |
		   TVDAC_B_SENSE_CTL |
		   TVDAC_C_SENSE_CTL |
		   DAC_CTL_OVERRIDE |
		   DAC_A_0_7_V |
		   DAC_B_0_7_V |
		   DAC_C_0_7_V);


	/*
	 * The TV sense state should be cleared to zero on cantiga platक्रमm. Otherwise
	 * the TV is misdetected. This is hardware requirement.
	 */
	अगर (IS_GM45(dev_priv))
		tv_dac &= ~(TVDAC_STATE_CHG_EN | TVDAC_A_SENSE_CTL |
			    TVDAC_B_SENSE_CTL | TVDAC_C_SENSE_CTL);

	पूर्णांकel_de_ग_लिखो(dev_priv, TV_CTL, tv_ctl);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_DAC, tv_dac);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, TV_DAC);

	पूर्णांकel_रुको_क्रम_vblank(dev_priv, पूर्णांकel_crtc->pipe);

	type = -1;
	tv_dac = पूर्णांकel_de_पढ़ो(dev_priv, TV_DAC);
	drm_dbg_kms(&dev_priv->drm, "TV detected: %x, %x\n", tv_ctl, tv_dac);
	/*
	 *  A B C
	 *  0 1 1 Composite
	 *  1 0 X svideo
	 *  0 0 0 Component
	 */
	अगर ((tv_dac & TVDAC_SENSE_MASK) == (TVDAC_B_SENSE | TVDAC_C_SENSE)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Detected Composite TV connection\n");
		type = DRM_MODE_CONNECTOR_Composite;
	पूर्ण अन्यथा अगर ((tv_dac & (TVDAC_A_SENSE|TVDAC_B_SENSE)) == TVDAC_A_SENSE) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Detected S-Video TV connection\n");
		type = DRM_MODE_CONNECTOR_SVIDEO;
	पूर्ण अन्यथा अगर ((tv_dac & TVDAC_SENSE_MASK) == 0) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Detected Component TV connection\n");
		type = DRM_MODE_CONNECTOR_Component;
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&dev_priv->drm, "Unrecognised TV connection\n");
		type = -1;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, TV_DAC, save_tv_dac & ~TVDAC_STATE_CHG_EN);
	पूर्णांकel_de_ग_लिखो(dev_priv, TV_CTL, save_tv_ctl);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, TV_CTL);

	/* For unknown reasons the hw barfs अगर we करोn't करो this vblank रुको. */
	पूर्णांकel_रुको_क्रम_vblank(dev_priv, पूर्णांकel_crtc->pipe);

	/* Restore पूर्णांकerrupt config */
	अगर (connector->polled & DRM_CONNECTOR_POLL_HPD) अणु
		spin_lock_irq(&dev_priv->irq_lock);
		i915_enable_pipestat(dev_priv, 0,
				     PIPE_HOTPLUG_INTERRUPT_STATUS |
				     PIPE_HOTPLUG_TV_INTERRUPT_STATUS);
		spin_unlock_irq(&dev_priv->irq_lock);
	पूर्ण

	वापस type;
पूर्ण

/*
 * Here we set accurate tv क्रमmat according to connector type
 * i.e Component TV should not be asचिन्हित by NTSC or PAL
 */
अटल व्योम पूर्णांकel_tv_find_better_क्रमmat(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_tv *पूर्णांकel_tv = पूर्णांकel_attached_tv(to_पूर्णांकel_connector(connector));
	स्थिर काष्ठा tv_mode *tv_mode = पूर्णांकel_tv_mode_find(connector->state);
	पूर्णांक i;

	/* Component supports everything so we can keep the current mode */
	अगर (पूर्णांकel_tv->type == DRM_MODE_CONNECTOR_Component)
		वापस;

	/* If the current mode is fine करोn't change it */
	अगर (!tv_mode->component_only)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(tv_modes); i++) अणु
		tv_mode = &tv_modes[i];

		अगर (!tv_mode->component_only)
			अवरोध;
	पूर्ण

	connector->state->tv.mode = i;
पूर्ण

अटल पूर्णांक
पूर्णांकel_tv_detect(काष्ठा drm_connector *connector,
		काष्ठा drm_modeset_acquire_ctx *ctx,
		bool क्रमce)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->dev);
	काष्ठा पूर्णांकel_tv *पूर्णांकel_tv = पूर्णांकel_attached_tv(to_पूर्णांकel_connector(connector));
	क्रमागत drm_connector_status status;
	पूर्णांक type;

	drm_dbg_kms(&i915->drm, "[CONNECTOR:%d:%s] force=%d\n",
		    connector->base.id, connector->name, क्रमce);

	अगर (!INTEL_DISPLAY_ENABLED(i915))
		वापस connector_status_disconnected;

	अगर (क्रमce) अणु
		काष्ठा पूर्णांकel_load_detect_pipe पंचांगp;
		पूर्णांक ret;

		ret = पूर्णांकel_get_load_detect_pipe(connector, &पंचांगp, ctx);
		अगर (ret < 0)
			वापस ret;

		अगर (ret > 0) अणु
			type = पूर्णांकel_tv_detect_type(पूर्णांकel_tv, connector);
			पूर्णांकel_release_load_detect_pipe(connector, &पंचांगp, ctx);
			status = type < 0 ?
				connector_status_disconnected :
				connector_status_connected;
		पूर्ण अन्यथा
			status = connector_status_unknown;

		अगर (status == connector_status_connected) अणु
			पूर्णांकel_tv->type = type;
			पूर्णांकel_tv_find_better_क्रमmat(connector);
		पूर्ण

		वापस status;
	पूर्ण अन्यथा
		वापस connector->status;
पूर्ण

अटल स्थिर काष्ठा input_res अणु
	u16 w, h;
पूर्ण input_res_table[] = अणु
	अणु 640, 480 पूर्ण,
	अणु 800, 600 पूर्ण,
	अणु 1024, 768 पूर्ण,
	अणु 1280, 1024 पूर्ण,
	अणु 848, 480 पूर्ण,
	अणु 1280, 720 पूर्ण,
	अणु 1920, 1080 पूर्ण,
पूर्ण;

/* Choose preferred mode according to line number of TV क्रमmat */
अटल bool
पूर्णांकel_tv_is_preferred_mode(स्थिर काष्ठा drm_display_mode *mode,
			   स्थिर काष्ठा tv_mode *tv_mode)
अणु
	पूर्णांक vdisplay = पूर्णांकel_tv_mode_vdisplay(tv_mode);

	/* prefer 480 line modes क्रम all SD TV modes */
	अगर (vdisplay <= 576)
		vdisplay = 480;

	वापस vdisplay == mode->vdisplay;
पूर्ण

अटल व्योम
पूर्णांकel_tv_set_mode_type(काष्ठा drm_display_mode *mode,
		       स्थिर काष्ठा tv_mode *tv_mode)
अणु
	mode->type = DRM_MODE_TYPE_DRIVER;

	अगर (पूर्णांकel_tv_is_preferred_mode(mode, tv_mode))
		mode->type |= DRM_MODE_TYPE_PREFERRED;
पूर्ण

अटल पूर्णांक
पूर्णांकel_tv_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	स्थिर काष्ठा tv_mode *tv_mode = पूर्णांकel_tv_mode_find(connector->state);
	पूर्णांक i, count = 0;

	क्रम (i = 0; i < ARRAY_SIZE(input_res_table); i++) अणु
		स्थिर काष्ठा input_res *input = &input_res_table[i];
		काष्ठा drm_display_mode *mode;

		अगर (input->w > 1024 &&
		    !tv_mode->progressive &&
		    !tv_mode->component_only)
			जारी;

		/* no vertical scaling with wide sources on gen3 */
		अगर (IS_DISPLAY_VER(dev_priv, 3) && input->w > 1024 &&
		    input->h > पूर्णांकel_tv_mode_vdisplay(tv_mode))
			जारी;

		mode = drm_mode_create(connector->dev);
		अगर (!mode)
			जारी;

		/*
		 * We take the TV mode and scale it to look
		 * like it had the expected h/vdisplay. This
		 * provides the most inक्रमmation to userspace
		 * about the actual timings of the mode. We
		 * करो ignore the margins though.
		 */
		पूर्णांकel_tv_mode_to_mode(mode, tv_mode);
		अगर (count == 0) अणु
			drm_dbg_kms(&dev_priv->drm, "TV mode:\n");
			drm_mode_debug_prपूर्णांकmodeline(mode);
		पूर्ण
		पूर्णांकel_tv_scale_mode_horiz(mode, input->w, 0, 0);
		पूर्णांकel_tv_scale_mode_vert(mode, input->h, 0, 0);
		पूर्णांकel_tv_set_mode_type(mode, tv_mode);

		drm_mode_set_name(mode);

		drm_mode_probed_add(connector, mode);
		count++;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs पूर्णांकel_tv_connector_funcs = अणु
	.late_रेजिस्टर = पूर्णांकel_connector_रेजिस्टर,
	.early_unरेजिस्टर = पूर्णांकel_connector_unरेजिस्टर,
	.destroy = पूर्णांकel_connector_destroy,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.atomic_duplicate_state = पूर्णांकel_tv_connector_duplicate_state,
पूर्ण;

अटल पूर्णांक पूर्णांकel_tv_atomic_check(काष्ठा drm_connector *connector,
				 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *new_state;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_connector_state *old_state;

	new_state = drm_atomic_get_new_connector_state(state, connector);
	अगर (!new_state->crtc)
		वापस 0;

	old_state = drm_atomic_get_old_connector_state(state, connector);
	new_crtc_state = drm_atomic_get_new_crtc_state(state, new_state->crtc);

	अगर (old_state->tv.mode != new_state->tv.mode ||
	    old_state->tv.margins.left != new_state->tv.margins.left ||
	    old_state->tv.margins.right != new_state->tv.margins.right ||
	    old_state->tv.margins.top != new_state->tv.margins.top ||
	    old_state->tv.margins.bottom != new_state->tv.margins.bottom) अणु
		/* Force a modeset. */

		new_crtc_state->connectors_changed = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs पूर्णांकel_tv_connector_helper_funcs = अणु
	.detect_ctx = पूर्णांकel_tv_detect,
	.mode_valid = पूर्णांकel_tv_mode_valid,
	.get_modes = पूर्णांकel_tv_get_modes,
	.atomic_check = पूर्णांकel_tv_atomic_check,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_funcs पूर्णांकel_tv_enc_funcs = अणु
	.destroy = पूर्णांकel_encoder_destroy,
पूर्ण;

व्योम
पूर्णांकel_tv_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_connector *connector;
	काष्ठा पूर्णांकel_tv *पूर्णांकel_tv;
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
	u32 tv_dac_on, tv_dac_off, save_tv_dac;
	स्थिर अक्षर *tv_क्रमmat_names[ARRAY_SIZE(tv_modes)];
	पूर्णांक i, initial_mode = 0;
	काष्ठा drm_connector_state *state;

	अगर ((पूर्णांकel_de_पढ़ो(dev_priv, TV_CTL) & TV_FUSE_STATE_MASK) == TV_FUSE_STATE_DISABLED)
		वापस;

	अगर (!पूर्णांकel_bios_is_tv_present(dev_priv)) अणु
		drm_dbg_kms(&dev_priv->drm, "Integrated TV is not present.\n");
		वापस;
	पूर्ण

	/*
	 * Sanity check the TV output by checking to see अगर the
	 * DAC रेजिस्टर holds a value
	 */
	save_tv_dac = पूर्णांकel_de_पढ़ो(dev_priv, TV_DAC);

	पूर्णांकel_de_ग_लिखो(dev_priv, TV_DAC, save_tv_dac | TVDAC_STATE_CHG_EN);
	tv_dac_on = पूर्णांकel_de_पढ़ो(dev_priv, TV_DAC);

	पूर्णांकel_de_ग_लिखो(dev_priv, TV_DAC, save_tv_dac & ~TVDAC_STATE_CHG_EN);
	tv_dac_off = पूर्णांकel_de_पढ़ो(dev_priv, TV_DAC);

	पूर्णांकel_de_ग_लिखो(dev_priv, TV_DAC, save_tv_dac);

	/*
	 * If the रेजिस्टर करोes not hold the state change enable
	 * bit, (either as a 0 or a 1), assume it करोesn't really
	 * exist
	 */
	अगर ((tv_dac_on & TVDAC_STATE_CHG_EN) == 0 ||
	    (tv_dac_off & TVDAC_STATE_CHG_EN) != 0)
		वापस;

	पूर्णांकel_tv = kzalloc(माप(*पूर्णांकel_tv), GFP_KERNEL);
	अगर (!पूर्णांकel_tv) अणु
		वापस;
	पूर्ण

	पूर्णांकel_connector = पूर्णांकel_connector_alloc();
	अगर (!पूर्णांकel_connector) अणु
		kमुक्त(पूर्णांकel_tv);
		वापस;
	पूर्ण

	पूर्णांकel_encoder = &पूर्णांकel_tv->base;
	connector = &पूर्णांकel_connector->base;
	state = connector->state;

	/*
	 * The करोcumentation, क्रम the older chipsets at least, recommend
	 * using a polling method rather than hotplug detection क्रम TVs.
	 * This is because in order to perक्रमm the hotplug detection, the PLLs
	 * क्रम the TV must be kept alive increasing घातer drain and starving
	 * bandwidth from other encoders. Notably क्रम instance, it causes
	 * pipe underruns on Crestline when this encoder is supposedly idle.
	 *
	 * More recent chipsets favour HDMI rather than पूर्णांकegrated S-Video.
	 */
	पूर्णांकel_connector->polled = DRM_CONNECTOR_POLL_CONNECT;

	drm_connector_init(dev, connector, &पूर्णांकel_tv_connector_funcs,
			   DRM_MODE_CONNECTOR_SVIDEO);

	drm_encoder_init(dev, &पूर्णांकel_encoder->base, &पूर्णांकel_tv_enc_funcs,
			 DRM_MODE_ENCODER_TVDAC, "TV");

	पूर्णांकel_encoder->compute_config = पूर्णांकel_tv_compute_config;
	पूर्णांकel_encoder->get_config = पूर्णांकel_tv_get_config;
	पूर्णांकel_encoder->pre_enable = पूर्णांकel_tv_pre_enable;
	पूर्णांकel_encoder->enable = पूर्णांकel_enable_tv;
	पूर्णांकel_encoder->disable = पूर्णांकel_disable_tv;
	पूर्णांकel_encoder->get_hw_state = पूर्णांकel_tv_get_hw_state;
	पूर्णांकel_connector->get_hw_state = पूर्णांकel_connector_get_hw_state;

	पूर्णांकel_connector_attach_encoder(पूर्णांकel_connector, पूर्णांकel_encoder);

	पूर्णांकel_encoder->type = INTEL_OUTPUT_TVOUT;
	पूर्णांकel_encoder->घातer_करोमुख्य = POWER_DOMAIN_PORT_OTHER;
	पूर्णांकel_encoder->port = PORT_NONE;
	पूर्णांकel_encoder->pipe_mask = ~0;
	पूर्णांकel_encoder->cloneable = 0;
	पूर्णांकel_tv->type = DRM_MODE_CONNECTOR_Unknown;

	/* BIOS margin values */
	state->tv.margins.left = 54;
	state->tv.margins.top = 36;
	state->tv.margins.right = 46;
	state->tv.margins.bottom = 37;

	state->tv.mode = initial_mode;

	drm_connector_helper_add(connector, &पूर्णांकel_tv_connector_helper_funcs);
	connector->पूर्णांकerlace_allowed = false;
	connector->द्विगुनscan_allowed = false;

	/* Create TV properties then attach current values */
	क्रम (i = 0; i < ARRAY_SIZE(tv_modes); i++) अणु
		/* 1080p50/1080p60 not supported on gen3 */
		अगर (IS_DISPLAY_VER(dev_priv, 3) &&
		    tv_modes[i].oversample == 1)
			अवरोध;

		tv_क्रमmat_names[i] = tv_modes[i].name;
	पूर्ण
	drm_mode_create_tv_properties(dev, i, tv_क्रमmat_names);

	drm_object_attach_property(&connector->base, dev->mode_config.tv_mode_property,
				   state->tv.mode);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_left_margin_property,
				   state->tv.margins.left);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_top_margin_property,
				   state->tv.margins.top);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_right_margin_property,
				   state->tv.margins.right);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_bottom_margin_property,
				   state->tv.margins.bottom);
पूर्ण
