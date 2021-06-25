<शैली गुरु>
/*
 * linux/drivers/video/platinumfb-hw.c -- Frame buffer device क्रम the
 * Platinum on-board video in PowerMac 7200s (and some clones based
 * on the same motherboard.)
 *
 *  Created 09 Feb 1998 by Jon Howell <jonh@cs.darपंचांगouth.edu>
 *
 * Copyright (C) 1998 Jon Howell
 *
 *  based on drivers/macपूर्णांकosh/platinum.c: Console support
 * 	क्रम PowerMac "platinum" display adaptor.
 *  Copyright (C) 1996 Paul Mackerras and Mark Abene.
 *
 *  based on skeletonfb.c:
 *  Created 28 Dec 1997 by Geert Uytterhoeven
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

/*
 * Structure of the रेजिस्टरs क्रम the DACula colormap device.
 */
काष्ठा cmap_regs अणु
	अचिन्हित अक्षर addr;
	अक्षर pad1[15];
	अचिन्हित अक्षर d1;
	अक्षर pad2[15];
	अचिन्हित अक्षर d2;
	अक्षर pad3[15];
	अचिन्हित अक्षर lut;
	अक्षर pad4[15];
पूर्ण;

/*
 * Structure of the रेजिस्टरs क्रम the "platinum" display adaptor".
 */
काष्ठा preg अणु			/* padded रेजिस्टर */
	अचिन्हित r;			/* notice this is 32 bits. */
	अक्षर pad[12];
पूर्ण;

काष्ठा platinum_regs अणु
	काष्ठा preg reg[128];
पूर्ण;

/*
 * Register initialization tables क्रम the platinum display.
 *
 * It seems that there are two dअगरferent types of platinum display
 * out there.  Older ones use the values in घड़ीsel[1], क्रम which
 * the क्रमmula क्रम the घड़ी frequency seems to be
 *	F = 14.3MHz * c0 / (c1 & 0x1f) / (1 << (c1 >> 5))
 * Newer ones use the values in घड़ीsel[0], क्रम which the क्रमmula
 * seems to be
 *	F = 15MHz * c0 / ((c1 & 0x1f) + 2) / (1 << (c1 >> 5))
 */
काष्ठा platinum_regvals अणु
	पूर्णांक	fb_offset;
	पूर्णांक	pitch[3];
	अचिन्हित regs[26];
	अचिन्हित अक्षर offset[3];
	अचिन्हित अक्षर mode[3];
	अचिन्हित अक्षर dacula_ctrl[3];
	अचिन्हित अक्षर घड़ी_params[2][2];
पूर्ण;

#घोषणा DIV2	0x20
#घोषणा DIV4	0x40
#घोषणा DIV8	0x60
#घोषणा DIV16	0x80

/* 1280x1024, 75Hz (20) */
अटल काष्ठा platinum_regvals platinum_reg_init_20 = अणु
	0x5c00,
	अणु 1312, 2592, 2592 पूर्ण,
	अणु 0xffc, 4, 0, 0, 0, 0, 0x428, 0,
	  0, 0xb3, 0xd3, 0x12, 0x1a5, 0x23, 0x28, 0x2d,
	  0x5e, 0x19e, 0x1a4, 0x854, 0x852, 4, 9, 0x50,
	  0x850, 0x851 पूर्ण, अणु 0x58, 0x5d, 0x5d पूर्ण,
	अणु 0, 0xff, 0xff पूर्ण, अणु 0x51, 0x55, 0x55 पूर्ण,
	अणुअणु 45, 3 पूर्ण, अणु 66, 7 पूर्णपूर्ण
पूर्ण;

/* 1280x960, 75Hz (19) */
अटल काष्ठा platinum_regvals platinum_reg_init_19 = अणु
	0x5c00,
	अणु 1312, 2592, 2592 पूर्ण,
	अणु 0xffc, 4, 0, 0, 0, 0, 0x428, 0,
	  0, 0xb2, 0xd2, 0x12, 0x1a3, 0x23, 0x28, 0x2d,
	  0x5c, 0x19c, 0x1a2, 0x7d0, 0x7ce, 4, 9, 0x4c,
	  0x7cc, 0x7cd पूर्ण, अणु 0x56, 0x5b, 0x5b पूर्ण,
	अणु 0, 0xff, 0xff पूर्ण, अणु 0x51, 0x55, 0x55 पूर्ण,
	अणुअणु 42, 3 पूर्ण, अणु 44, 5 पूर्णपूर्ण
पूर्ण;

/* 1152x870, 75Hz (18) */
अटल काष्ठा platinum_regvals platinum_reg_init_18 = अणु
	0x11b0,
	अणु 1184, 2336, 4640 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x38f, 0,
	  0, 0x294, 0x16c, 0x20, 0x2d7, 0x3f, 0x49, 0x53,
	  0x82, 0x2c2, 0x2d6, 0x726, 0x724, 4, 9, 0x52,
	  0x71e, 0x722 पूर्ण, अणु 0x74, 0x7c, 0x81 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 26, 0 + DIV2 पूर्ण, अणु 42, 6 पूर्णपूर्ण
पूर्ण;

/* 1024x768, 75Hz (17) */
अटल काष्ठा platinum_regvals platinum_reg_init_17 = अणु
	0x10b0,
	अणु 1056, 2080, 4128 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0x254, 0x14b, 0x18, 0x295, 0x2f, 0x32, 0x3b,
	  0x80, 0x280, 0x296, 0x648, 0x646, 4, 9, 0x40,
	  0x640, 0x644 पूर्ण, अणु 0x72, 0x7a, 0x7f पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 54, 3 + DIV2 पूर्ण, अणु 67, 12 पूर्णपूर्ण
पूर्ण;

/* 1024x768, 75Hz (16) */
अटल काष्ठा platinum_regvals platinum_reg_init_16 = अणु
	0x10b0,
	अणु 1056, 2080, 4128 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0x250, 0x147, 0x17, 0x28f, 0x2f, 0x35, 0x47,
	  0x82, 0x282, 0x28e, 0x640, 0x63e, 4, 9, 0x3c,
	  0x63c, 0x63d पूर्ण, अणु 0x74, 0x7c, 0x81 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 20, 0 + DIV2 पूर्ण, अणु 11, 2 पूर्णपूर्ण
पूर्ण;

/* 1024x768, 70Hz (15) */
अटल काष्ठा platinum_regvals platinum_reg_init_15 = अणु
	0x10b0,
	अणु 1056, 2080, 4128 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0x254, 0x14b, 0x22, 0x297, 0x43, 0x49, 0x5b,
	  0x86, 0x286, 0x296, 0x64c, 0x64a, 0xa, 0xf, 0x44,
	  0x644, 0x646 पूर्ण, अणु 0x78, 0x80, 0x85 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 19, 0 + DIV2 पूर्ण, अणु 110, 21 पूर्णपूर्ण
पूर्ण;

/* 1024x768, 60Hz (14) */
अटल काष्ठा platinum_regvals platinum_reg_init_14 = अणु
	0x10b0,
	अणु 1056, 2080, 4128 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0x25a, 0x14f, 0x22, 0x29f, 0x43, 0x49, 0x5b,
	  0x8e, 0x28e, 0x29e, 0x64c, 0x64a, 0xa, 0xf, 0x44,
	  0x644, 0x646 पूर्ण, अणु 0x80, 0x88, 0x8d पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 71, 6 + DIV2 पूर्ण, अणु 118, 13 + DIV2 पूर्णपूर्ण
पूर्ण;

/* 832x624, 75Hz (13) */
अटल काष्ठा platinum_regvals platinum_reg_init_13 = अणु
	0x70,
	अणु 864, 1680, 3344 पूर्ण,	/* MacOS करोes 1680 instead of 1696 to fit 16bpp in 1MB,
				 * and we use 3344 instead of 3360 to fit in 2Mb
				 */
	अणु 0xff0, 4, 0, 0, 0, 0, 0x299, 0,
	  0, 0x21e, 0x120, 0x10, 0x23f, 0x1f, 0x25, 0x37,
	  0x8a, 0x22a, 0x23e, 0x536, 0x534, 4, 9, 0x52,
	  0x532, 0x533 पूर्ण, अणु 0x7c, 0x84, 0x89 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 30, 0 + DIV4 पूर्ण, अणु 56, 7 + DIV2 पूर्णपूर्ण
पूर्ण;

/* 800x600, 75Hz (12) */
अटल काष्ठा platinum_regvals platinum_reg_init_12 = अणु
	0x1010,
	अणु 832, 1632, 3232 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0x1ce, 0x108, 0x14, 0x20f, 0x27, 0x30, 0x39,
	  0x72, 0x202, 0x20e, 0x4e2, 0x4e0, 4, 9, 0x2e,
	  0x4de, 0x4df पूर्ण, अणु 0x64, 0x6c, 0x71 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 122, 7 + DIV4 पूर्ण, अणु 62, 9 + DIV2 पूर्णपूर्ण
पूर्ण;

/* 800x600, 72Hz (11) */
अटल काष्ठा platinum_regvals platinum_reg_init_11 = अणु
	0x1010,
	अणु 832, 1632, 3232 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0x1ca, 0x104, 0x1e, 0x207, 0x3b, 0x44, 0x4d,
	  0x56, 0x1e6, 0x206, 0x534, 0x532, 0xa, 0xe, 0x38,
	  0x4e8, 0x4ec पूर्ण, अणु 0x48, 0x50, 0x55 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 26, 0 + DIV4 पूर्ण, अणु 42, 6 + DIV2 पूर्णपूर्ण
पूर्ण;

/* 800x600, 60Hz (10) */
अटल काष्ठा platinum_regvals platinum_reg_init_10 = अणु
	0x1010,
	अणु 832, 1632, 3232 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0x1ce, 0x108, 0x20, 0x20f, 0x3f, 0x45, 0x5d,
	  0x66, 0x1f6, 0x20e, 0x4e8, 0x4e6, 6, 0xa, 0x34,
	  0x4e4, 0x4e5 पूर्ण, अणु 0x58, 0x60, 0x65 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 54, 3 + DIV4 पूर्ण, अणु 95, 1 + DIV8 पूर्णपूर्ण
पूर्ण;

/* 800x600, 56Hz (9) --unsupported? copy of mode 10 क्रम now... */
अटल काष्ठा platinum_regvals platinum_reg_init_9 = अणु
	0x1010,
	अणु 832, 1632, 3232 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0x1ce, 0x108, 0x20, 0x20f, 0x3f, 0x45, 0x5d,
	  0x66, 0x1f6, 0x20e, 0x4e8, 0x4e6, 6, 0xa, 0x34,
	  0x4e4, 0x4e5 पूर्ण, अणु 0x58, 0x60, 0x65 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 54, 3 + DIV4 पूर्ण, अणु 88, 1 + DIV8 पूर्णपूर्ण
पूर्ण;

/* 768x576, 50Hz Interlaced-PAL (8) */
अटल काष्ठा platinum_regvals platinum_reg_init_8 = अणु
	0x1010,
	अणु 800, 1568, 3104 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0xc8, 0xec, 0x11, 0x1d7, 0x22, 0x25, 0x36,
	  0x47, 0x1c7, 0x1d6, 0x271, 0x270, 4, 9, 0x27,
	  0x267, 0x26b पूर्ण, अणु 0x39, 0x41, 0x46 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 31, 0 + DIV16 पूर्ण, अणु 74, 9 + DIV8 पूर्णपूर्ण
पूर्ण;

/* 640x870, 75Hz Portrait (7) */
अटल काष्ठा platinum_regvals platinum_reg_init_7 = अणु
	0xb10,
	अणु 672, 1312, 2592 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0x176, 0xd0, 0x14, 0x19f, 0x27, 0x2d, 0x3f,
	  0x4a, 0x18a, 0x19e, 0x72c, 0x72a, 4, 9, 0x58,
	  0x724, 0x72a पूर्ण, अणु 0x3c, 0x44, 0x49 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 30, 0 + DIV4 पूर्ण, अणु 56, 7 + DIV2 पूर्णपूर्ण
पूर्ण;

/* 640x480, 67Hz (6) */
अटल काष्ठा platinum_regvals platinum_reg_init_6 = अणु
	0x1010,
	अणु 672, 1312, 2592 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x209, 0,
	  0, 0x18e, 0xd8, 0x10, 0x1af, 0x1f, 0x25, 0x37,
	  0x4a, 0x18a, 0x1ae, 0x41a, 0x418, 4, 9, 0x52,
	  0x412, 0x416 पूर्ण, अणु 0x3c, 0x44, 0x49 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 99, 4 + DIV8 पूर्ण, अणु 42, 5 + DIV4 पूर्णपूर्ण
पूर्ण;

/* 640x480, 60Hz (5) */
अटल काष्ठा platinum_regvals platinum_reg_init_5 = अणु
	0x1010,
	अणु 672, 1312, 2592 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0x15e, 0xc8, 0x18, 0x18f, 0x2f, 0x35, 0x3e,
	  0x42, 0x182, 0x18e, 0x41a, 0x418, 2, 7, 0x44,
	  0x404, 0x408 पूर्ण, अणु 0x34, 0x3c, 0x41 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 26, 0 + DIV8 पूर्ण, अणु 14, 2 + DIV4 पूर्णपूर्ण
पूर्ण;

/* 640x480, 60Hz Interlaced-NTSC (4) */
अटल काष्ठा platinum_regvals platinum_reg_init_4 = अणु
	0x1010,
	अणु 672, 1312, 2592 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0xa5, 0xc3, 0xe, 0x185, 0x1c, 0x1f, 0x30,
	  0x37, 0x177, 0x184, 0x20d, 0x20c, 5, 0xb, 0x23,
	  0x203, 0x206 पूर्ण, अणु 0x29, 0x31, 0x36 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 94, 5 + DIV16 पूर्ण, अणु 48, 7 + DIV8 पूर्णपूर्ण
पूर्ण;

/* 640x480, 50Hz Interlaced-PAL (3) */
अटल काष्ठा platinum_regvals platinum_reg_init_3 = अणु
	0x1010,
	अणु 672, 1312, 2592 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0xc8, 0xec, 0x11, 0x1d7, 0x22, 0x25, 0x36,
	  0x67, 0x1a7, 0x1d6, 0x271, 0x270, 4, 9, 0x57,
	  0x237, 0x26b पूर्ण, अणु 0x59, 0x61, 0x66 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 31, 0 + DIV16 पूर्ण, अणु 74, 9 + DIV8 पूर्णपूर्ण
पूर्ण;

/* 512x384, 60Hz (2) */
अटल काष्ठा platinum_regvals platinum_reg_init_2 = अणु
	0x1010,
	अणु 544, 1056, 2080 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0x25c, 0x140, 0x10, 0x27f, 0x1f, 0x2b, 0x4f,
	  0x68, 0x268, 0x27e, 0x32e, 0x32c, 4, 9, 0x2a,
	  0x32a, 0x32b पूर्ण, अणु 0x5a, 0x62, 0x67 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 33, 2 + DIV8 पूर्ण, अणु 79, 9 + DIV8 पूर्णपूर्ण
पूर्ण;

/* 512x384, 60Hz Interlaced-NTSC (1) */
अटल काष्ठा platinum_regvals platinum_reg_init_1 = अणु
	0x1010,
	अणु 544, 1056, 2080 पूर्ण,
	अणु 0xff0, 4, 0, 0, 0, 0, 0x320, 0,
	  0, 0xa5, 0xc3, 0xe, 0x185, 0x1c, 0x1f, 0x30,
	  0x57, 0x157, 0x184, 0x20d, 0x20c, 5, 0xb, 0x53,
	  0x1d3, 0x206 पूर्ण, अणु 0x49, 0x51, 0x56 पूर्ण,
	अणु 2, 0, 0xff पूर्ण, अणु 0x11, 0x15, 0x19 पूर्ण,
	अणुअणु 94, 5 + DIV16 पूर्ण, अणु 48, 7 + DIV8 पूर्णपूर्ण
पूर्ण;

अटल काष्ठा platinum_regvals *platinum_reg_init[VMODE_MAX] = अणु
	&platinum_reg_init_1,
	&platinum_reg_init_2,
	&platinum_reg_init_3,
	&platinum_reg_init_4,
	&platinum_reg_init_5,
	&platinum_reg_init_6,
	&platinum_reg_init_7,
	&platinum_reg_init_8,
	&platinum_reg_init_9,
	&platinum_reg_init_10,
	&platinum_reg_init_11,
	&platinum_reg_init_12,
	&platinum_reg_init_13,
	&platinum_reg_init_14,
	&platinum_reg_init_15,
	&platinum_reg_init_16,
	&platinum_reg_init_17,
	&platinum_reg_init_18,
	&platinum_reg_init_19,
	&platinum_reg_init_20
पूर्ण;

काष्ठा vmode_attr अणु
	पूर्णांक hres;
	पूर्णांक vres;
	पूर्णांक vfreq;
	पूर्णांक पूर्णांकerlaced;
पूर्ण;

काष्ठा vmode_attr vmode_attrs[VMODE_MAX] = अणु
	अणु512, 384, 60, 1पूर्ण,
	अणु512, 384, 60पूर्ण,
	अणु640, 480, 50, 1पूर्ण,
	अणु640, 480, 60, 1पूर्ण,
	अणु640, 480, 60पूर्ण,
	अणु640, 480, 67पूर्ण,
	अणु640, 870, 75पूर्ण,
	अणु768, 576, 50, 1पूर्ण,
	अणु800, 600, 56पूर्ण,
	अणु800, 600, 60पूर्ण,
	अणु800, 600, 72पूर्ण,
	अणु800, 600, 75पूर्ण,
	अणु832, 624, 75पूर्ण,
	अणु1024, 768, 60पूर्ण,
	अणु1024, 768, 72पूर्ण,
	अणु1024, 768, 75पूर्ण,
	अणु1024, 768, 75पूर्ण,
	अणु1152, 870, 75पूर्ण,
	अणु1280, 960, 75पूर्ण,
	अणु1280, 1024, 75पूर्ण
पूर्ण;

