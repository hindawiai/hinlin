<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2006 Micronas USA Inc.
 */

/*
 * This file contains code to generate a firmware image क्रम the GO7007SB
 * encoder.  Much of the firmware is पढ़ो verbatim from a file, but some of
 * it concerning bitrate control and other things that can be configured at
 * run-समय are generated dynamically.  Note that the क्रमmat headers
 * generated here करो not affect the functioning of the encoder; they are
 * merely parroted back to the host at the start of each frame.
 */

#समावेश <linux/module.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "go7007-priv.h"

#घोषणा GO7007_FW_NAME "go7007/go7007tv.bin"

/* Constants used in the source firmware image to describe code segments */

#घोषणा	FLAG_MODE_MJPEG		(1)
#घोषणा	FLAG_MODE_MPEG1		(1<<1)
#घोषणा	FLAG_MODE_MPEG2		(1<<2)
#घोषणा	FLAG_MODE_MPEG4		(1<<3)
#घोषणा	FLAG_MODE_H263		(1<<4)
#घोषणा FLAG_MODE_ALL		(FLAG_MODE_MJPEG | FLAG_MODE_MPEG1 | \
					FLAG_MODE_MPEG2 | FLAG_MODE_MPEG4 | \
					FLAG_MODE_H263)
#घोषणा FLAG_SPECIAL		(1<<8)

#घोषणा SPECIAL_FRM_HEAD	0
#घोषणा SPECIAL_BRC_CTRL	1
#घोषणा SPECIAL_CONFIG		2
#घोषणा SPECIAL_SEQHEAD		3
#घोषणा SPECIAL_AV_SYNC		4
#घोषणा SPECIAL_FINAL		5
#घोषणा SPECIAL_AUDIO		6
#घोषणा SPECIAL_MODET		7

/* Little data class क्रम creating MPEG headers bit-by-bit */

काष्ठा code_gen अणु
	अचिन्हित अक्षर *p; /* destination */
	u32 a; /* collects bits at the top of the variable */
	पूर्णांक b; /* bit position of most recently-written bit */
	पूर्णांक len; /* written out so far */
पूर्ण;

#घोषणा CODE_GEN(name, dest) काष्ठा code_gen name = अणु dest, 0, 32, 0 पूर्ण

#घोषणा CODE_ADD(name, val, length) करो अणु \
	name.b -= (length); \
	name.a |= (val) << name.b; \
	जबतक (name.b <= 24) अणु \
		*name.p = name.a >> 24; \
		++name.p; \
		name.a <<= 8; \
		name.b += 8; \
		name.len += 8; \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा CODE_LENGTH(name) (name.len + (32 - name.b))

/* Tables क्रम creating the bitrate control data */

अटल स्थिर s16 converge_speed_ip[101] = अणु
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 3,
	3, 3, 3, 3, 3, 4, 4, 4, 4, 4,
	5, 5, 5, 6, 6, 6, 7, 7, 8, 8,
	9, 10, 10, 11, 12, 13, 14, 15, 16, 17,
	19, 20, 22, 23, 25, 27, 30, 32, 35, 38,
	41, 45, 49, 53, 58, 63, 69, 76, 83, 91,
	100
पूर्ण;

अटल स्थिर s16 converge_speed_ipb[101] = अणु
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 5, 5, 5, 5, 5, 6,
	6, 6, 6, 7, 7, 7, 7, 8, 8, 9,
	9, 9, 10, 10, 11, 12, 12, 13, 14, 14,
	15, 16, 17, 18, 19, 20, 22, 23, 25, 26,
	28, 30, 32, 34, 37, 40, 42, 46, 49, 53,
	57, 61, 66, 71, 77, 83, 90, 97, 106, 115,
	125, 135, 147, 161, 175, 191, 209, 228, 249, 273,
	300
पूर्ण;

अटल स्थिर s16 LAMBDA_table[4][101] = अणु
	अणु	16, 16, 16, 16, 17, 17, 17, 18, 18, 18,
		19, 19, 19, 20, 20, 20, 21, 21, 22, 22,
		22, 23, 23, 24, 24, 25, 25, 25, 26, 26,
		27, 27, 28, 28, 29, 29, 30, 31, 31, 32,
		32, 33, 33, 34, 35, 35, 36, 37, 37, 38,
		39, 39, 40, 41, 42, 42, 43, 44, 45, 46,
		46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
		56, 57, 58, 59, 60, 61, 62, 63, 64, 65,
		67, 68, 69, 70, 72, 73, 74, 76, 77, 78,
		80, 81, 83, 84, 86, 87, 89, 90, 92, 94,
		96
	पूर्ण,
	अणु
		20, 20, 20, 21, 21, 21, 22, 22, 23, 23,
		23, 24, 24, 25, 25, 26, 26, 27, 27, 28,
		28, 29, 29, 30, 30, 31, 31, 32, 33, 33,
		34, 34, 35, 36, 36, 37, 38, 38, 39, 40,
		40, 41, 42, 43, 43, 44, 45, 46, 47, 48,
		48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
		58, 59, 60, 61, 62, 64, 65, 66, 67, 68,
		70, 71, 72, 73, 75, 76, 78, 79, 80, 82,
		83, 85, 86, 88, 90, 91, 93, 95, 96, 98,
		100, 102, 103, 105, 107, 109, 111, 113, 115, 117,
		120
	पूर्ण,
	अणु
		24, 24, 24, 25, 25, 26, 26, 27, 27, 28,
		28, 29, 29, 30, 30, 31, 31, 32, 33, 33,
		34, 34, 35, 36, 36, 37, 38, 38, 39, 40,
		41, 41, 42, 43, 44, 44, 45, 46, 47, 48,
		49, 50, 50, 51, 52, 53, 54, 55, 56, 57,
		58, 59, 60, 62, 63, 64, 65, 66, 67, 69,
		70, 71, 72, 74, 75, 76, 78, 79, 81, 82,
		84, 85, 87, 88, 90, 92, 93, 95, 97, 98,
		100, 102, 104, 106, 108, 110, 112, 114, 116, 118,
		120, 122, 124, 127, 129, 131, 134, 136, 138, 141,
		144
	पूर्ण,
	अणु
		32, 32, 33, 33, 34, 34, 35, 36, 36, 37,
		38, 38, 39, 40, 41, 41, 42, 43, 44, 44,
		45, 46, 47, 48, 49, 50, 50, 51, 52, 53,
		54, 55, 56, 57, 58, 59, 60, 62, 63, 64,
		65, 66, 67, 69, 70, 71, 72, 74, 75, 76,
		78, 79, 81, 82, 84, 85, 87, 88, 90, 92,
		93, 95, 97, 98, 100, 102, 104, 106, 108, 110,
		112, 114, 116, 118, 120, 122, 124, 127, 129, 131,
		134, 136, 139, 141, 144, 146, 149, 152, 154, 157,
		160, 163, 166, 169, 172, 175, 178, 181, 185, 188,
		192
	पूर्ण
पूर्ण;

/* MPEG blank frame generation tables */

क्रमागत mpeg_frame_type अणु
	PFRAME,
	BFRAME_PRE,
	BFRAME_POST,
	BFRAME_BIसूची,
	BFRAME_EMPTY
पूर्ण;

अटल स्थिर u32 addrinctab[33][2] = अणु
	अणु 0x01, 1 पूर्ण,	अणु 0x03, 3 पूर्ण,	अणु 0x02, 3 पूर्ण,	अणु 0x03, 4 पूर्ण,
	अणु 0x02, 4 पूर्ण,	अणु 0x03, 5 पूर्ण,	अणु 0x02, 5 पूर्ण,	अणु 0x07, 7 पूर्ण,
	अणु 0x06, 7 पूर्ण,	अणु 0x0b, 8 पूर्ण,	अणु 0x0a, 8 पूर्ण,	अणु 0x09, 8 पूर्ण,
	अणु 0x08, 8 पूर्ण,	अणु 0x07, 8 पूर्ण,	अणु 0x06, 8 पूर्ण,	अणु 0x17, 10 पूर्ण,
	अणु 0x16, 10 पूर्ण,	अणु 0x15, 10 पूर्ण,	अणु 0x14, 10 पूर्ण,	अणु 0x13, 10 पूर्ण,
	अणु 0x12, 10 पूर्ण,	अणु 0x23, 11 पूर्ण,	अणु 0x22, 11 पूर्ण,	अणु 0x21, 11 पूर्ण,
	अणु 0x20, 11 पूर्ण,	अणु 0x1f, 11 पूर्ण,	अणु 0x1e, 11 पूर्ण,	अणु 0x1d, 11 पूर्ण,
	अणु 0x1c, 11 पूर्ण,	अणु 0x1b, 11 पूर्ण,	अणु 0x1a, 11 पूर्ण,	अणु 0x19, 11 पूर्ण,
	अणु 0x18, 11 पूर्ण
पूर्ण;

/* Standard JPEG tables */

अटल स्थिर u8 शेष_पूर्णांकra_quant_table[] = अणु
	 8, 16, 19, 22, 26, 27, 29, 34,
	16, 16, 22, 24, 27, 29, 34, 37,
	19, 22, 26, 27, 29, 34, 34, 38,
	22, 22, 26, 27, 29, 34, 37, 40,
	22, 26, 27, 29, 32, 35, 40, 48,
	26, 27, 29, 32, 35, 40, 48, 58,
	26, 27, 29, 34, 38, 46, 56, 69,
	27, 29, 35, 38, 46, 56, 69, 83
पूर्ण;

अटल स्थिर u8 bits_dc_luminance[] = अणु
	0, 0, 1, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0
पूर्ण;

अटल स्थिर u8 val_dc_luminance[] = अणु
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
पूर्ण;

अटल स्थिर u8 bits_dc_chrominance[] = अणु
	0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0
पूर्ण;

अटल स्थिर u8 val_dc_chrominance[] = अणु
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
पूर्ण;

अटल स्थिर u8 bits_ac_luminance[] = अणु
	0, 0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7d
पूर्ण;

अटल स्थिर u8 val_ac_luminance[] = अणु
	0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
	0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
	0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
	0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
	0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
	0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
	0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
	0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
	0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
	0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
	0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
	0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
	0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
	0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
	0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
	0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
	0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
	0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
	0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa
पूर्ण;

अटल स्थिर u8 bits_ac_chrominance[] = अणु
	0, 0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77
पूर्ण;

अटल स्थिर u8 val_ac_chrominance[] = अणु
	0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
	0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
	0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
	0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
	0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
	0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
	0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
	0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
	0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
	0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
	0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
	0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
	0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
	0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
	0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
	0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
	0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
	0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa
पूर्ण;

/* Zig-zag mapping क्रम quant table
 *
 * OK, let's do this mapping on the actual table above so it doesn't have
 * to be करोne on the fly.
 */
अटल स्थिर पूर्णांक zz[64] = अणु
	0,   1,  8, 16,  9,  2,  3, 10, 17, 24, 32, 25, 18, 11,  4,  5,
	12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13,  6,  7, 14, 21, 28,
	35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51,
	58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63
पूर्ण;

अटल पूर्णांक copy_packages(__le16 *dest, u16 *src, पूर्णांक pkg_cnt, पूर्णांक space)
अणु
	पूर्णांक i, cnt = pkg_cnt * 32;

	अगर (space < cnt)
		वापस -1;

	क्रम (i = 0; i < cnt; ++i)
		dest[i] = cpu_to_le16p(src + i);

	वापस cnt;
पूर्ण

अटल पूर्णांक mjpeg_frame_header(काष्ठा go7007 *go, अचिन्हित अक्षर *buf, पूर्णांक q)
अणु
	पूर्णांक i, p = 0;

	buf[p++] = 0xff;
	buf[p++] = 0xd8;
	buf[p++] = 0xff;
	buf[p++] = 0xdb;
	buf[p++] = 0;
	buf[p++] = 2 + 65;
	buf[p++] = 0;
	buf[p++] = शेष_पूर्णांकra_quant_table[0];
	क्रम (i = 1; i < 64; ++i)
		/* buf[p++] = (शेष_पूर्णांकra_quant_table[i] * q) >> 3; */
		buf[p++] = (शेष_पूर्णांकra_quant_table[zz[i]] * q) >> 3;
	buf[p++] = 0xff;
	buf[p++] = 0xc0;
	buf[p++] = 0;
	buf[p++] = 17;
	buf[p++] = 8;
	buf[p++] = go->height >> 8;
	buf[p++] = go->height & 0xff;
	buf[p++] = go->width >> 8;
	buf[p++] = go->width & 0xff;
	buf[p++] = 3;
	buf[p++] = 1;
	buf[p++] = 0x22;
	buf[p++] = 0;
	buf[p++] = 2;
	buf[p++] = 0x11;
	buf[p++] = 0;
	buf[p++] = 3;
	buf[p++] = 0x11;
	buf[p++] = 0;
	buf[p++] = 0xff;
	buf[p++] = 0xc4;
	buf[p++] = 418 >> 8;
	buf[p++] = 418 & 0xff;
	buf[p++] = 0x00;
	स_नकल(buf + p, bits_dc_luminance + 1, 16);
	p += 16;
	स_नकल(buf + p, val_dc_luminance, माप(val_dc_luminance));
	p += माप(val_dc_luminance);
	buf[p++] = 0x01;
	स_नकल(buf + p, bits_dc_chrominance + 1, 16);
	p += 16;
	स_नकल(buf + p, val_dc_chrominance, माप(val_dc_chrominance));
	p += माप(val_dc_chrominance);
	buf[p++] = 0x10;
	स_नकल(buf + p, bits_ac_luminance + 1, 16);
	p += 16;
	स_नकल(buf + p, val_ac_luminance, माप(val_ac_luminance));
	p += माप(val_ac_luminance);
	buf[p++] = 0x11;
	स_नकल(buf + p, bits_ac_chrominance + 1, 16);
	p += 16;
	स_नकल(buf + p, val_ac_chrominance, माप(val_ac_chrominance));
	p += माप(val_ac_chrominance);
	buf[p++] = 0xff;
	buf[p++] = 0xda;
	buf[p++] = 0;
	buf[p++] = 12;
	buf[p++] = 3;
	buf[p++] = 1;
	buf[p++] = 0x00;
	buf[p++] = 2;
	buf[p++] = 0x11;
	buf[p++] = 3;
	buf[p++] = 0x11;
	buf[p++] = 0;
	buf[p++] = 63;
	buf[p++] = 0;
	वापस p;
पूर्ण

अटल पूर्णांक gen_mjpeghdr_to_package(काष्ठा go7007 *go, __le16 *code, पूर्णांक space)
अणु
	u8 *buf;
	u16 mem = 0x3e00;
	अचिन्हित पूर्णांक addr = 0x19;
	पूर्णांक size = 0, i, off = 0, chunk;

	buf = kzalloc(4096, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	क्रम (i = 1; i < 32; ++i) अणु
		mjpeg_frame_header(go, buf + size, i);
		size += 80;
	पूर्ण
	chunk = mjpeg_frame_header(go, buf + size, 1);
	स_हटाओ(buf + size, buf + size + 80, chunk - 80);
	size += chunk - 80;

	क्रम (i = 0; i < size; i += chunk * 2) अणु
		अगर (space - off < 32) अणु
			off = -1;
			जाओ करोne;
		पूर्ण

		code[off + 1] = __cpu_to_le16(0x8000 | mem);

		chunk = 28;
		अगर (mem + chunk > 0x4000)
			chunk = 0x4000 - mem;
		अगर (i + 2 * chunk > size)
			chunk = (size - i) / 2;

		अगर (chunk < 28) अणु
			code[off] = __cpu_to_le16(0x4000 | chunk);
			code[off + 31] = __cpu_to_le16(addr++);
			mem = 0x3e00;
		पूर्ण अन्यथा अणु
			code[off] = __cpu_to_le16(0x1000 | 28);
			code[off + 31] = 0;
			mem += 28;
		पूर्ण

		स_नकल(&code[off + 2], buf + i, chunk * 2);
		off += 32;
	पूर्ण
करोne:
	kमुक्त(buf);
	वापस off;
पूर्ण

अटल पूर्णांक mpeg1_frame_header(काष्ठा go7007 *go, अचिन्हित अक्षर *buf,
		पूर्णांक modulo, पूर्णांक pict_काष्ठा, क्रमागत mpeg_frame_type frame)
अणु
	पूर्णांक i, j, mb_code, mb_len;
	पूर्णांक rows = go->पूर्णांकerlace_coding ? go->height / 32 : go->height / 16;
	CODE_GEN(c, buf + 6);

	चयन (frame) अणु
	हाल PFRAME:
		mb_code = 0x1;
		mb_len = 3;
		अवरोध;
	हाल BFRAME_PRE:
		mb_code = 0x2;
		mb_len = 4;
		अवरोध;
	हाल BFRAME_POST:
		mb_code = 0x2;
		mb_len = 3;
		अवरोध;
	हाल BFRAME_BIसूची:
		mb_code = 0x2;
		mb_len = 2;
		अवरोध;
	शेष: /* keep the compiler happy */
		mb_code = mb_len = 0;
		अवरोध;
	पूर्ण

	CODE_ADD(c, frame == PFRAME ? 0x2 : 0x3, 13);
	CODE_ADD(c, 0xffff, 16);
	CODE_ADD(c, go->क्रमmat == V4L2_PIX_FMT_MPEG2 ? 0x7 : 0x4, 4);
	अगर (frame != PFRAME)
		CODE_ADD(c, go->क्रमmat == V4L2_PIX_FMT_MPEG2 ? 0x7 : 0x4, 4);
	अन्यथा
		CODE_ADD(c, 0, 4); /* Is this supposed to be here?? */
	CODE_ADD(c, 0, 3); /* What is this?? */
	/* Byte-align with zeros */
	j = 8 - (CODE_LENGTH(c) % 8);
	अगर (j != 8)
		CODE_ADD(c, 0, j);

	अगर (go->क्रमmat == V4L2_PIX_FMT_MPEG2) अणु
		CODE_ADD(c, 0x1, 24);
		CODE_ADD(c, 0xb5, 8);
		CODE_ADD(c, 0x844, 12);
		CODE_ADD(c, frame == PFRAME ? 0xff : 0x44, 8);
		अगर (go->पूर्णांकerlace_coding) अणु
			CODE_ADD(c, pict_काष्ठा, 4);
			अगर (go->dvd_mode)
				CODE_ADD(c, 0x000, 11);
			अन्यथा
				CODE_ADD(c, 0x200, 11);
		पूर्ण अन्यथा अणु
			CODE_ADD(c, 0x3, 4);
			CODE_ADD(c, 0x20c, 11);
		पूर्ण
		/* Byte-align with zeros */
		j = 8 - (CODE_LENGTH(c) % 8);
		अगर (j != 8)
			CODE_ADD(c, 0, j);
	पूर्ण

	क्रम (i = 0; i < rows; ++i) अणु
		CODE_ADD(c, 1, 24);
		CODE_ADD(c, i + 1, 8);
		CODE_ADD(c, 0x2, 6);
		CODE_ADD(c, 0x1, 1);
		CODE_ADD(c, mb_code, mb_len);
		अगर (go->पूर्णांकerlace_coding) अणु
			CODE_ADD(c, 0x1, 2);
			CODE_ADD(c, pict_काष्ठा == 1 ? 0x0 : 0x1, 1);
		पूर्ण
		अगर (frame == BFRAME_BIसूची) अणु
			CODE_ADD(c, 0x3, 2);
			अगर (go->पूर्णांकerlace_coding)
				CODE_ADD(c, pict_काष्ठा == 1 ? 0x0 : 0x1, 1);
		पूर्ण
		CODE_ADD(c, 0x3, 2);
		क्रम (j = (go->width >> 4) - 2; j >= 33; j -= 33)
			CODE_ADD(c, 0x8, 11);
		CODE_ADD(c, addrinctab[j][0], addrinctab[j][1]);
		CODE_ADD(c, mb_code, mb_len);
		अगर (go->पूर्णांकerlace_coding) अणु
			CODE_ADD(c, 0x1, 2);
			CODE_ADD(c, pict_काष्ठा == 1 ? 0x0 : 0x1, 1);
		पूर्ण
		अगर (frame == BFRAME_BIसूची) अणु
			CODE_ADD(c, 0x3, 2);
			अगर (go->पूर्णांकerlace_coding)
				CODE_ADD(c, pict_काष्ठा == 1 ? 0x0 : 0x1, 1);
		पूर्ण
		CODE_ADD(c, 0x3, 2);

		/* Byte-align with zeros */
		j = 8 - (CODE_LENGTH(c) % 8);
		अगर (j != 8)
			CODE_ADD(c, 0, j);
	पूर्ण

	i = CODE_LENGTH(c) + 4 * 8;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x01;
	buf[5] = 0x00;
	वापस i;
पूर्ण

अटल पूर्णांक mpeg1_sequence_header(काष्ठा go7007 *go, अचिन्हित अक्षर *buf, पूर्णांक ext)
अणु
	पूर्णांक i, aspect_ratio, picture_rate;
	CODE_GEN(c, buf + 6);

	अगर (go->क्रमmat == V4L2_PIX_FMT_MPEG1) अणु
		चयन (go->aspect_ratio) अणु
		हाल GO7007_RATIO_4_3:
			aspect_ratio = go->standard == GO7007_STD_NTSC ? 3 : 2;
			अवरोध;
		हाल GO7007_RATIO_16_9:
			aspect_ratio = go->standard == GO7007_STD_NTSC ? 5 : 4;
			अवरोध;
		शेष:
			aspect_ratio = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (go->aspect_ratio) अणु
		हाल GO7007_RATIO_4_3:
			aspect_ratio = 2;
			अवरोध;
		हाल GO7007_RATIO_16_9:
			aspect_ratio = 3;
			अवरोध;
		शेष:
			aspect_ratio = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	चयन (go->sensor_framerate) अणु
	हाल 24000:
		picture_rate = 1;
		अवरोध;
	हाल 24024:
		picture_rate = 2;
		अवरोध;
	हाल 25025:
		picture_rate = go->पूर्णांकerlace_coding ? 6 : 3;
		अवरोध;
	हाल 30000:
		picture_rate = go->पूर्णांकerlace_coding ? 7 : 4;
		अवरोध;
	हाल 30030:
		picture_rate = go->पूर्णांकerlace_coding ? 8 : 5;
		अवरोध;
	शेष:
		picture_rate = 5; /* 30 fps seems like a reasonable शेष */
		अवरोध;
	पूर्ण

	CODE_ADD(c, go->width, 12);
	CODE_ADD(c, go->height, 12);
	CODE_ADD(c, aspect_ratio, 4);
	CODE_ADD(c, picture_rate, 4);
	CODE_ADD(c, go->क्रमmat == V4L2_PIX_FMT_MPEG2 ? 20000 : 0x3ffff, 18);
	CODE_ADD(c, 1, 1);
	CODE_ADD(c, go->क्रमmat == V4L2_PIX_FMT_MPEG2 ? 112 : 20, 10);
	CODE_ADD(c, 0, 3);

	/* Byte-align with zeros */
	i = 8 - (CODE_LENGTH(c) % 8);
	अगर (i != 8)
		CODE_ADD(c, 0, i);

	अगर (go->क्रमmat == V4L2_PIX_FMT_MPEG2) अणु
		CODE_ADD(c, 0x1, 24);
		CODE_ADD(c, 0xb5, 8);
		CODE_ADD(c, 0x148, 12);
		अगर (go->पूर्णांकerlace_coding)
			CODE_ADD(c, 0x20001, 20);
		अन्यथा
			CODE_ADD(c, 0xa0001, 20);
		CODE_ADD(c, 0, 16);

		/* Byte-align with zeros */
		i = 8 - (CODE_LENGTH(c) % 8);
		अगर (i != 8)
			CODE_ADD(c, 0, i);

		अगर (ext) अणु
			CODE_ADD(c, 0x1, 24);
			CODE_ADD(c, 0xb52, 12);
			CODE_ADD(c, go->standard == GO7007_STD_NTSC ? 2 : 1, 3);
			CODE_ADD(c, 0x105, 9);
			CODE_ADD(c, 0x505, 16);
			CODE_ADD(c, go->width, 14);
			CODE_ADD(c, 1, 1);
			CODE_ADD(c, go->height, 14);

			/* Byte-align with zeros */
			i = 8 - (CODE_LENGTH(c) % 8);
			अगर (i != 8)
				CODE_ADD(c, 0, i);
		पूर्ण
	पूर्ण

	i = CODE_LENGTH(c) + 4 * 8;
	buf[0] = i & 0xff;
	buf[1] = i >> 8;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x01;
	buf[5] = 0xb3;
	वापस i;
पूर्ण

अटल पूर्णांक gen_mpeg1hdr_to_package(काष्ठा go7007 *go,
					__le16 *code, पूर्णांक space, पूर्णांक *framelen)
अणु
	u8 *buf;
	u16 mem = 0x3e00;
	अचिन्हित पूर्णांक addr = 0x19;
	पूर्णांक i, off = 0, chunk;

	buf = kzalloc(5120, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	framelen[0] = mpeg1_frame_header(go, buf, 0, 1, PFRAME);
	अगर (go->पूर्णांकerlace_coding)
		framelen[0] += mpeg1_frame_header(go, buf + framelen[0] / 8,
							0, 2, PFRAME);
	buf[0] = framelen[0] & 0xff;
	buf[1] = framelen[0] >> 8;
	i = 368;
	framelen[1] = mpeg1_frame_header(go, buf + i, 0, 1, BFRAME_PRE);
	अगर (go->पूर्णांकerlace_coding)
		framelen[1] += mpeg1_frame_header(go, buf + i + framelen[1] / 8,
							0, 2, BFRAME_PRE);
	buf[i] = framelen[1] & 0xff;
	buf[i + 1] = framelen[1] >> 8;
	i += 1632;
	framelen[2] = mpeg1_frame_header(go, buf + i, 0, 1, BFRAME_POST);
	अगर (go->पूर्णांकerlace_coding)
		framelen[2] += mpeg1_frame_header(go, buf + i + framelen[2] / 8,
							0, 2, BFRAME_POST);
	buf[i] = framelen[2] & 0xff;
	buf[i + 1] = framelen[2] >> 8;
	i += 1432;
	framelen[3] = mpeg1_frame_header(go, buf + i, 0, 1, BFRAME_BIसूची);
	अगर (go->पूर्णांकerlace_coding)
		framelen[3] += mpeg1_frame_header(go, buf + i + framelen[3] / 8,
							0, 2, BFRAME_BIसूची);
	buf[i] = framelen[3] & 0xff;
	buf[i + 1] = framelen[3] >> 8;
	i += 1632 + 16;
	mpeg1_sequence_header(go, buf + i, 0);
	i += 40;
	क्रम (i = 0; i < 5120; i += chunk * 2) अणु
		अगर (space - off < 32) अणु
			off = -1;
			जाओ करोne;
		पूर्ण

		code[off + 1] = __cpu_to_le16(0x8000 | mem);

		chunk = 28;
		अगर (mem + chunk > 0x4000)
			chunk = 0x4000 - mem;
		अगर (i + 2 * chunk > 5120)
			chunk = (5120 - i) / 2;

		अगर (chunk < 28) अणु
			code[off] = __cpu_to_le16(0x4000 | chunk);
			code[off + 31] = __cpu_to_le16(addr);
			अगर (mem + chunk == 0x4000) अणु
				mem = 0x3e00;
				++addr;
			पूर्ण
		पूर्ण अन्यथा अणु
			code[off] = __cpu_to_le16(0x1000 | 28);
			code[off + 31] = 0;
			mem += 28;
		पूर्ण

		स_नकल(&code[off + 2], buf + i, chunk * 2);
		off += 32;
	पूर्ण
करोne:
	kमुक्त(buf);
	वापस off;
पूर्ण

अटल पूर्णांक vti_bitlen(काष्ठा go7007 *go)
अणु
	अचिन्हित पूर्णांक i, max_समय_incr = go->sensor_framerate / go->fps_scale;

	क्रम (i = 31; (max_समय_incr & ((1 << i) - 1)) == max_समय_incr; --i)
		;
	वापस i + 1;
पूर्ण

अटल पूर्णांक mpeg4_frame_header(काष्ठा go7007 *go, अचिन्हित अक्षर *buf,
		पूर्णांक modulo, क्रमागत mpeg_frame_type frame)
अणु
	पूर्णांक i;
	CODE_GEN(c, buf + 6);
	पूर्णांक mb_count = (go->width >> 4) * (go->height >> 4);

	CODE_ADD(c, frame == PFRAME ? 0x1 : 0x2, 2);
	अगर (modulo)
		CODE_ADD(c, 0x1, 1);
	CODE_ADD(c, 0x1, 2);
	CODE_ADD(c, 0, vti_bitlen(go));
	CODE_ADD(c, 0x3, 2);
	अगर (frame == PFRAME)
		CODE_ADD(c, 0, 1);
	CODE_ADD(c, 0xc, 11);
	अगर (frame != PFRAME)
		CODE_ADD(c, 0x4, 3);
	अगर (frame != BFRAME_EMPTY) अणु
		क्रम (i = 0; i < mb_count; ++i) अणु
			चयन (frame) अणु
			हाल PFRAME:
				CODE_ADD(c, 0x1, 1);
				अवरोध;
			हाल BFRAME_PRE:
				CODE_ADD(c, 0x47, 8);
				अवरोध;
			हाल BFRAME_POST:
				CODE_ADD(c, 0x27, 7);
				अवरोध;
			हाल BFRAME_BIसूची:
				CODE_ADD(c, 0x5f, 8);
				अवरोध;
			हाल BFRAME_EMPTY: /* keep compiler quiet */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Byte-align with a zero followed by ones */
	i = 8 - (CODE_LENGTH(c) % 8);
	CODE_ADD(c, 0, 1);
	CODE_ADD(c, (1 << (i - 1)) - 1, i - 1);

	i = CODE_LENGTH(c) + 4 * 8;
	buf[0] = i & 0xff;
	buf[1] = i >> 8;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x01;
	buf[5] = 0xb6;
	वापस i;
पूर्ण

अटल पूर्णांक mpeg4_sequence_header(काष्ठा go7007 *go, अचिन्हित अक्षर *buf, पूर्णांक ext)
अणु
	स्थिर अचिन्हित अक्षर head[] = अणु 0x00, 0x00, 0x01, 0xb0, go->pali,
		0x00, 0x00, 0x01, 0xb5, 0x09,
		0x00, 0x00, 0x01, 0x00,
		0x00, 0x00, 0x01, 0x20, पूर्ण;
	पूर्णांक i, aspect_ratio;
	पूर्णांक fps = go->sensor_framerate / go->fps_scale;
	CODE_GEN(c, buf + 2 + माप(head));

	चयन (go->aspect_ratio) अणु
	हाल GO7007_RATIO_4_3:
		aspect_ratio = go->standard == GO7007_STD_NTSC ? 3 : 2;
		अवरोध;
	हाल GO7007_RATIO_16_9:
		aspect_ratio = go->standard == GO7007_STD_NTSC ? 5 : 4;
		अवरोध;
	शेष:
		aspect_ratio = 1;
		अवरोध;
	पूर्ण

	स_नकल(buf + 2, head, माप(head));
	CODE_ADD(c, 0x191, 17);
	CODE_ADD(c, aspect_ratio, 4);
	CODE_ADD(c, 0x1, 4);
	CODE_ADD(c, fps, 16);
	CODE_ADD(c, 0x3, 2);
	CODE_ADD(c, 1001, vti_bitlen(go));
	CODE_ADD(c, 1, 1);
	CODE_ADD(c, go->width, 13);
	CODE_ADD(c, 1, 1);
	CODE_ADD(c, go->height, 13);
	CODE_ADD(c, 0x2830, 14);

	/* Byte-align */
	i = 8 - (CODE_LENGTH(c) % 8);
	CODE_ADD(c, 0, 1);
	CODE_ADD(c, (1 << (i - 1)) - 1, i - 1);

	i = CODE_LENGTH(c) + माप(head) * 8;
	buf[0] = i & 0xff;
	buf[1] = i >> 8;
	वापस i;
पूर्ण

अटल पूर्णांक gen_mpeg4hdr_to_package(काष्ठा go7007 *go,
					__le16 *code, पूर्णांक space, पूर्णांक *framelen)
अणु
	u8 *buf;
	u16 mem = 0x3e00;
	अचिन्हित पूर्णांक addr = 0x19;
	पूर्णांक i, off = 0, chunk;

	buf = kzalloc(5120, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	framelen[0] = mpeg4_frame_header(go, buf, 0, PFRAME);
	i = 368;
	framelen[1] = mpeg4_frame_header(go, buf + i, 0, BFRAME_PRE);
	i += 1632;
	framelen[2] = mpeg4_frame_header(go, buf + i, 0, BFRAME_POST);
	i += 1432;
	framelen[3] = mpeg4_frame_header(go, buf + i, 0, BFRAME_BIसूची);
	i += 1632;
	mpeg4_frame_header(go, buf + i, 0, BFRAME_EMPTY);
	i += 16;
	mpeg4_sequence_header(go, buf + i, 0);
	i += 40;
	क्रम (i = 0; i < 5120; i += chunk * 2) अणु
		अगर (space - off < 32) अणु
			off = -1;
			जाओ करोne;
		पूर्ण

		code[off + 1] = __cpu_to_le16(0x8000 | mem);

		chunk = 28;
		अगर (mem + chunk > 0x4000)
			chunk = 0x4000 - mem;
		अगर (i + 2 * chunk > 5120)
			chunk = (5120 - i) / 2;

		अगर (chunk < 28) अणु
			code[off] = __cpu_to_le16(0x4000 | chunk);
			code[off + 31] = __cpu_to_le16(addr);
			अगर (mem + chunk == 0x4000) अणु
				mem = 0x3e00;
				++addr;
			पूर्ण
		पूर्ण अन्यथा अणु
			code[off] = __cpu_to_le16(0x1000 | 28);
			code[off + 31] = 0;
			mem += 28;
		पूर्ण

		स_नकल(&code[off + 2], buf + i, chunk * 2);
		off += 32;
	पूर्ण
	mem = 0x3e00;
	addr = go->ipb ? 0x14f9 : 0x0af9;
	स_रखो(buf, 0, 5120);
	framelen[4] = mpeg4_frame_header(go, buf, 1, PFRAME);
	i = 368;
	framelen[5] = mpeg4_frame_header(go, buf + i, 1, BFRAME_PRE);
	i += 1632;
	framelen[6] = mpeg4_frame_header(go, buf + i, 1, BFRAME_POST);
	i += 1432;
	framelen[7] = mpeg4_frame_header(go, buf + i, 1, BFRAME_BIसूची);
	i += 1632;
	mpeg4_frame_header(go, buf + i, 1, BFRAME_EMPTY);
	i += 16;
	क्रम (i = 0; i < 5120; i += chunk * 2) अणु
		अगर (space - off < 32) अणु
			off = -1;
			जाओ करोne;
		पूर्ण

		code[off + 1] = __cpu_to_le16(0x8000 | mem);

		chunk = 28;
		अगर (mem + chunk > 0x4000)
			chunk = 0x4000 - mem;
		अगर (i + 2 * chunk > 5120)
			chunk = (5120 - i) / 2;

		अगर (chunk < 28) अणु
			code[off] = __cpu_to_le16(0x4000 | chunk);
			code[off + 31] = __cpu_to_le16(addr);
			अगर (mem + chunk == 0x4000) अणु
				mem = 0x3e00;
				++addr;
			पूर्ण
		पूर्ण अन्यथा अणु
			code[off] = __cpu_to_le16(0x1000 | 28);
			code[off + 31] = 0;
			mem += 28;
		पूर्ण

		स_नकल(&code[off + 2], buf + i, chunk * 2);
		off += 32;
	पूर्ण
करोne:
	kमुक्त(buf);
	वापस off;
पूर्ण

अटल पूर्णांक brctrl_to_package(काष्ठा go7007 *go,
					__le16 *code, पूर्णांक space, पूर्णांक *framelen)
अणु
	पूर्णांक converge_speed = 0;
	पूर्णांक lambda = (go->क्रमmat == V4L2_PIX_FMT_MJPEG || go->dvd_mode) ?
				100 : 0;
	पूर्णांक peak_rate = 6 * go->bitrate / 5;
	पूर्णांक vbv_buffer = go->क्रमmat == V4L2_PIX_FMT_MJPEG ?
				go->bitrate :
				(go->dvd_mode ? 900000 : peak_rate);
	पूर्णांक fps = go->sensor_framerate / go->fps_scale;
	पूर्णांक q = 0;
	/* Bizarre math below depends on rounding errors in भागision */
	u32 sgop_expt_addr = go->bitrate / 32 * (go->ipb ? 3 : 1) * 1001 / fps;
	u32 sgop_peak_addr = peak_rate / 32 * 1001 / fps;
	u32 total_expt_addr = go->bitrate / 32 * 1000 / fps * (fps / 1000);
	u32 vbv_alert_addr = vbv_buffer * 3 / (4 * 32);
	u32 cplx[] = अणु
		q > 0 ? sgop_expt_addr * q :
			2 * go->width * go->height * (go->ipb ? 6 : 4) / 32,
		q > 0 ? sgop_expt_addr * q :
			2 * go->width * go->height * (go->ipb ? 6 : 4) / 32,
		q > 0 ? sgop_expt_addr * q :
			2 * go->width * go->height * (go->ipb ? 6 : 4) / 32,
		q > 0 ? sgop_expt_addr * q :
			2 * go->width * go->height * (go->ipb ? 6 : 4) / 32,
	पूर्ण;
	u32 calc_q = q > 0 ? q : cplx[0] / sgop_expt_addr;
	u16 pack[] = अणु
		0x200e,		0x0000,
		0xBF20,		go->ipb ? converge_speed_ipb[converge_speed]
					: converge_speed_ip[converge_speed],
		0xBF21,		go->ipb ? 2 : 0,
		0xBF22,		go->ipb ? LAMBDA_table[0][lambda / 2 + 50]
					: 32767,
		0xBF23,		go->ipb ? LAMBDA_table[1][lambda] : 32767,
		0xBF24,		32767,
		0xBF25,		lambda > 99 ? 32767 : LAMBDA_table[3][lambda],
		0xBF26,		sgop_expt_addr & 0x0000FFFF,
		0xBF27,		sgop_expt_addr >> 16,
		0xBF28,		sgop_peak_addr & 0x0000FFFF,
		0xBF29,		sgop_peak_addr >> 16,
		0xBF2A,		vbv_alert_addr & 0x0000FFFF,
		0xBF2B,		vbv_alert_addr >> 16,
		0xBF2C,		0,
		0xBF2D,		0,
		0,		0,

		0x200e,		0x0000,
		0xBF2E,		vbv_alert_addr & 0x0000FFFF,
		0xBF2F,		vbv_alert_addr >> 16,
		0xBF30,		cplx[0] & 0x0000FFFF,
		0xBF31,		cplx[0] >> 16,
		0xBF32,		cplx[1] & 0x0000FFFF,
		0xBF33,		cplx[1] >> 16,
		0xBF34,		cplx[2] & 0x0000FFFF,
		0xBF35,		cplx[2] >> 16,
		0xBF36,		cplx[3] & 0x0000FFFF,
		0xBF37,		cplx[3] >> 16,
		0xBF38,		0,
		0xBF39,		0,
		0xBF3A,		total_expt_addr & 0x0000FFFF,
		0xBF3B,		total_expt_addr >> 16,
		0,		0,

		0x200e,		0x0000,
		0xBF3C,		total_expt_addr & 0x0000FFFF,
		0xBF3D,		total_expt_addr >> 16,
		0xBF3E,		0,
		0xBF3F,		0,
		0xBF48,		0,
		0xBF49,		0,
		0xBF4A,		calc_q < 4 ? 4 : (calc_q > 124 ? 124 : calc_q),
		0xBF4B,		4,
		0xBF4C,		0,
		0xBF4D,		0,
		0xBF4E,		0,
		0xBF4F,		0,
		0xBF50,		0,
		0xBF51,		0,
		0,		0,

		0x200e,		0x0000,
		0xBF40,		sgop_expt_addr & 0x0000FFFF,
		0xBF41,		sgop_expt_addr >> 16,
		0xBF42,		0,
		0xBF43,		0,
		0xBF44,		0,
		0xBF45,		0,
		0xBF46,		(go->width >> 4) * (go->height >> 4),
		0xBF47,		0,
		0xBF64,		0,
		0xBF65,		0,
		0xBF18,		framelen[4],
		0xBF19,		framelen[5],
		0xBF1A,		framelen[6],
		0xBF1B,		framelen[7],
		0,		0,

#अगर 0
		/* Remove once we करोn't care about matching */
		0x200e,		0x0000,
		0xBF56,		4,
		0xBF57,		0,
		0xBF58,		5,
		0xBF59,		0,
		0xBF5A,		6,
		0xBF5B,		0,
		0xBF5C,		8,
		0xBF5D,		0,
		0xBF5E,		1,
		0xBF5F,		0,
		0xBF60,		1,
		0xBF61,		0,
		0xBF62,		0,
		0xBF63,		0,
		0,		0,
#अन्यथा
		0x2008,		0x0000,
		0xBF56,		4,
		0xBF57,		0,
		0xBF58,		5,
		0xBF59,		0,
		0xBF5A,		6,
		0xBF5B,		0,
		0xBF5C,		8,
		0xBF5D,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
#पूर्ण_अगर

		0x200e,		0x0000,
		0xBF10,		0,
		0xBF11,		0,
		0xBF12,		0,
		0xBF13,		0,
		0xBF14,		0,
		0xBF15,		0,
		0xBF16,		0,
		0xBF17,		0,
		0xBF7E,		0,
		0xBF7F,		1,
		0xBF52,		framelen[0],
		0xBF53,		framelen[1],
		0xBF54,		framelen[2],
		0xBF55,		framelen[3],
		0,		0,
	पूर्ण;

	वापस copy_packages(code, pack, 6, space);
पूर्ण

अटल पूर्णांक config_package(काष्ठा go7007 *go, __le16 *code, पूर्णांक space)
अणु
	पूर्णांक fps = go->sensor_framerate / go->fps_scale / 1000;
	पूर्णांक rows = go->पूर्णांकerlace_coding ? go->height / 32 : go->height / 16;
	पूर्णांक brc_winकरोw_size = fps;
	पूर्णांक q_min = 2, q_max = 31;
	पूर्णांक THACCoeffSet0 = 0;
	u16 pack[] = अणु
		0x200e,		0x0000,
		0xc002,		0x14b4,
		0xc003,		0x28b4,
		0xc004,		0x3c5a,
		0xdc05,		0x2a77,
		0xc6c3,		go->क्रमmat == V4L2_PIX_FMT_MPEG4 ? 0 :
				(go->क्रमmat == V4L2_PIX_FMT_H263 ? 0 : 1),
		0xc680,		go->क्रमmat == V4L2_PIX_FMT_MPEG4 ? 0xf1 :
				(go->क्रमmat == V4L2_PIX_FMT_H263 ? 0x61 :
									0xd3),
		0xc780,		0x0140,
		0xe009,		0x0001,
		0xc60f,		0x0008,
		0xd4ff,		0x0002,
		0xe403,		2340,
		0xe406,		75,
		0xd411,		0x0001,
		0xd410,		0xa1d6,
		0x0001,		0x2801,

		0x200d,		0x0000,
		0xe402,		0x018b,
		0xe401,		0x8b01,
		0xd472,		(go->board_info->sensor_flags &
							GO7007_SENSOR_TV) &&
						(!go->पूर्णांकerlace_coding) ?
					0x01b0 : 0x0170,
		0xd475,		(go->board_info->sensor_flags &
							GO7007_SENSOR_TV) &&
						(!go->पूर्णांकerlace_coding) ?
					0x0008 : 0x0009,
		0xc404,		go->पूर्णांकerlace_coding ? 0x44 :
				(go->क्रमmat == V4L2_PIX_FMT_MPEG4 ? 0x11 :
				(go->क्रमmat == V4L2_PIX_FMT_MPEG1 ? 0x02 :
				(go->क्रमmat == V4L2_PIX_FMT_MPEG2 ? 0x04 :
				(go->क्रमmat == V4L2_PIX_FMT_H263  ? 0x08 :
								     0x20)))),
		0xbf0a,		(go->क्रमmat == V4L2_PIX_FMT_MPEG4 ? 8 :
				(go->क्रमmat == V4L2_PIX_FMT_MPEG1 ? 1 :
				(go->क्रमmat == V4L2_PIX_FMT_MPEG2 ? 2 :
				(go->क्रमmat == V4L2_PIX_FMT_H263 ? 4 : 16)))) |
				((go->repeat_seqhead ? 1 : 0) << 6) |
				((go->dvd_mode ? 1 : 0) << 9) |
				((go->gop_header_enable ? 1 : 0) << 10),
		0xbf0b,		0,
		0xdd5a,		go->ipb ? 0x14 : 0x0a,
		0xbf0c,		0,
		0xbf0d,		0,
		0xc683,		THACCoeffSet0,
		0xc40a,		(go->width << 4) | rows,
		0xe01a,		go->board_info->hpi_buffer_cap,
		0,		0,
		0,		0,

		0x2008,		0,
		0xe402,		0x88,
		0xe401,		0x8f01,
		0xbf6a,		0,
		0xbf6b,		0,
		0xbf6c,		0,
		0xbf6d,		0,
		0xbf6e,		0,
		0xbf6f,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,

		0x200e,		0,
		0xbf66,		brc_winकरोw_size,
		0xbf67,		0,
		0xbf68,		q_min,
		0xbf69,		q_max,
		0xbfe0,		0,
		0xbfe1,		0,
		0xbfe2,		0,
		0xbfe3,		go->ipb ? 3 : 1,
		0xc031,		go->board_info->sensor_flags &
					GO7007_SENSOR_VBI ? 1 : 0,
		0xc01c,		0x1f,
		0xdd8c,		0x15,
		0xdd94,		0x15,
		0xdd88,		go->ipb ? 0x1401 : 0x0a01,
		0xdd90,		go->ipb ? 0x1401 : 0x0a01,
		0,		0,

		0x200e,		0,
		0xbfe4,		0,
		0xbfe5,		0,
		0xbfe6,		0,
		0xbfe7,		fps << 8,
		0xbfe8,		0x3a00,
		0xbfe9,		0,
		0xbfea,		0,
		0xbfeb,		0,
		0xbfec,		(go->पूर्णांकerlace_coding ? 1 << 15 : 0) |
					(go->modet_enable ? 0xa : 0) |
					(go->board_info->sensor_flags &
						GO7007_SENSOR_VBI ? 1 : 0),
		0xbfed,		0,
		0xbfee,		0,
		0xbfef,		0,
		0xbff0,		go->board_info->sensor_flags &
					GO7007_SENSOR_TV ? 0xf060 : 0xb060,
		0xbff1,		0,
		0,		0,
	पूर्ण;

	वापस copy_packages(code, pack, 5, space);
पूर्ण

अटल पूर्णांक seqhead_to_package(काष्ठा go7007 *go, __le16 *code, पूर्णांक space,
	पूर्णांक (*sequence_header_func)(काष्ठा go7007 *go,
		अचिन्हित अक्षर *buf, पूर्णांक ext))
अणु
	पूर्णांक vop_समय_increment_bitlength = vti_bitlen(go);
	पूर्णांक fps = go->sensor_framerate / go->fps_scale *
					(go->पूर्णांकerlace_coding ? 2 : 1);
	अचिन्हित अक्षर buf[40] = अणु पूर्ण;
	पूर्णांक len = sequence_header_func(go, buf, 1);
	u16 pack[] = अणु
		0x2006,		0,
		0xbf08,		fps,
		0xbf09,		0,
		0xbff2,		vop_समय_increment_bitlength,
		0xbff3,		(1 << vop_समय_increment_bitlength) - 1,
		0xbfe6,		0,
		0xbfe7,		(fps / 1000) << 8,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,

		0x2007,		0,
		0xc800,		buf[2] << 8 | buf[3],
		0xc801,		buf[4] << 8 | buf[5],
		0xc802,		buf[6] << 8 | buf[7],
		0xc803,		buf[8] << 8 | buf[9],
		0xc406,		64,
		0xc407,		len - 64,
		0xc61b,		1,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,

		0x200e,		0,
		0xc808,		buf[10] << 8 | buf[11],
		0xc809,		buf[12] << 8 | buf[13],
		0xc80a,		buf[14] << 8 | buf[15],
		0xc80b,		buf[16] << 8 | buf[17],
		0xc80c,		buf[18] << 8 | buf[19],
		0xc80d,		buf[20] << 8 | buf[21],
		0xc80e,		buf[22] << 8 | buf[23],
		0xc80f,		buf[24] << 8 | buf[25],
		0xc810,		buf[26] << 8 | buf[27],
		0xc811,		buf[28] << 8 | buf[29],
		0xc812,		buf[30] << 8 | buf[31],
		0xc813,		buf[32] << 8 | buf[33],
		0xc814,		buf[34] << 8 | buf[35],
		0xc815,		buf[36] << 8 | buf[37],
		0,		0,
		0,		0,
		0,		0,
	पूर्ण;

	वापस copy_packages(code, pack, 3, space);
पूर्ण

अटल पूर्णांक relative_prime(पूर्णांक big, पूर्णांक little)
अणु
	पूर्णांक reमुख्यder;

	जबतक (little != 0) अणु
		reमुख्यder = big % little;
		big = little;
		little = reमुख्यder;
	पूर्ण
	वापस big;
पूर्ण

अटल पूर्णांक avsync_to_package(काष्ठा go7007 *go, __le16 *code, पूर्णांक space)
अणु
	पूर्णांक arate = go->board_info->audio_rate * 1001 * go->fps_scale;
	पूर्णांक ratio = arate / go->sensor_framerate;
	पूर्णांक adjratio = ratio * 215 / 100;
	पूर्णांक rprime = relative_prime(go->sensor_framerate,
					arate % go->sensor_framerate);
	पूर्णांक f1 = (arate % go->sensor_framerate) / rprime;
	पूर्णांक f2 = (go->sensor_framerate - arate % go->sensor_framerate) / rprime;
	u16 pack[] = अणु
		0x200e,		0,
		0xbf98,		(u16)((-adjratio) & 0xffff),
		0xbf99,		(u16)((-adjratio) >> 16),
		0xbf92,		0,
		0xbf93,		0,
		0xbff4,		f1 > f2 ? f1 : f2,
		0xbff5,		f1 < f2 ? f1 : f2,
		0xbff6,		f1 < f2 ? ratio : ratio + 1,
		0xbff7,		f1 > f2 ? ratio : ratio + 1,
		0xbff8,		0,
		0xbff9,		0,
		0xbffa,		adjratio & 0xffff,
		0xbffb,		adjratio >> 16,
		0xbf94,		0,
		0xbf95,		0,
		0,		0,
	पूर्ण;

	वापस copy_packages(code, pack, 1, space);
पूर्ण

अटल पूर्णांक final_package(काष्ठा go7007 *go, __le16 *code, पूर्णांक space)
अणु
	पूर्णांक rows = go->पूर्णांकerlace_coding ? go->height / 32 : go->height / 16;
	u16 pack[] = अणु
		0x8000,
		0,
		0,
		0,
		0,
		0,
		0,
		2,
		((go->board_info->sensor_flags & GO7007_SENSOR_TV) &&
						(!go->पूर्णांकerlace_coding) ?
					(1 << 14) | (1 << 9) : 0) |
			((go->encoder_subsample ? 1 : 0) << 8) |
			(go->board_info->sensor_flags &
				GO7007_SENSOR_CONFIG_MASK),
		((go->encoder_v_halve ? 1 : 0) << 14) |
			(go->encoder_v_halve ? rows << 9 : rows << 8) |
			(go->encoder_h_halve ? 1 << 6 : 0) |
			(go->encoder_h_halve ? go->width >> 3 : go->width >> 4),
		(1 << 15) | (go->encoder_v_offset << 6) |
			(1 << 7) | (go->encoder_h_offset >> 2),
		(1 << 6),
		0,
		0,
		((go->fps_scale - 1) << 8) |
			(go->board_info->sensor_flags & GO7007_SENSOR_TV ?
						(1 << 7) : 0) |
			0x41,
		go->ipb ? 0xd4c : 0x36b,
		(rows << 8) | (go->width >> 4),
		go->क्रमmat == V4L2_PIX_FMT_MPEG4 ? 0x0404 : 0,
		(1 << 15) | ((go->पूर्णांकerlace_coding ? 1 : 0) << 13) |
			((go->बंदd_gop ? 1 : 0) << 12) |
			((go->क्रमmat == V4L2_PIX_FMT_MPEG4 ? 1 : 0) << 11) |
		/*	(1 << 9) |   */
			((go->ipb ? 3 : 0) << 7) |
			((go->modet_enable ? 1 : 0) << 2) |
			((go->dvd_mode ? 1 : 0) << 1) | 1,
		(go->क्रमmat == V4L2_PIX_FMT_MPEG1 ? 0x89a0 :
			(go->क्रमmat == V4L2_PIX_FMT_MPEG2 ? 0x89a0 :
			(go->क्रमmat == V4L2_PIX_FMT_MJPEG ? 0x89a0 :
			(go->क्रमmat == V4L2_PIX_FMT_MPEG4 ? 0x8920 :
			(go->क्रमmat == V4L2_PIX_FMT_H263 ? 0x8920 : 0))))),
		go->ipb ? 0x1f15 : 0x1f0b,
		go->ipb ? 0x0015 : 0x000b,
		go->ipb ? 0xa800 : 0x5800,
		0xffff,
		0x0020 + 0x034b * 0,
		0x0020 + 0x034b * 1,
		0x0020 + 0x034b * 2,
		0x0020 + 0x034b * 3,
		0x0020 + 0x034b * 4,
		0x0020 + 0x034b * 5,
		go->ipb ? (go->gop_size / 3) : go->gop_size,
		(go->height >> 4) * (go->width >> 4) * 110 / 100,
	पूर्ण;

	वापस copy_packages(code, pack, 1, space);
पूर्ण

अटल पूर्णांक audio_to_package(काष्ठा go7007 *go, __le16 *code, पूर्णांक space)
अणु
	पूर्णांक घड़ी_config = ((go->board_info->audio_flags &
				GO7007_AUDIO_I2S_MASTER ? 1 : 0) << 11) |
			((go->board_info->audio_flags &
				GO7007_AUDIO_OKI_MODE ? 1 : 0) << 8) |
			(((go->board_info->audio_bclk_भाग / 4) - 1) << 4) |
			(go->board_info->audio_मुख्य_भाग - 1);
	u16 pack[] = अणु
		0x200d,		0,
		0x9002,		0,
		0x9002,		0,
		0x9031,		0,
		0x9032,		0,
		0x9033,		0,
		0x9034,		0,
		0x9035,		0,
		0x9036,		0,
		0x9037,		0,
		0x9040,		0,
		0x9000,		घड़ी_config,
		0x9001,		(go->board_info->audio_flags & 0xffff) |
					(1 << 9),
		0x9000,		((go->board_info->audio_flags &
						GO7007_AUDIO_I2S_MASTER ?
						1 : 0) << 10) |
					घड़ी_config,
		0,		0,
		0,		0,
		0x2005,		0,
		0x9041,		0,
		0x9042,		256,
		0x9043,		0,
		0x9044,		16,
		0x9045,		16,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
	पूर्ण;

	वापस copy_packages(code, pack, 2, space);
पूर्ण

अटल पूर्णांक modet_to_package(काष्ठा go7007 *go, __le16 *code, पूर्णांक space)
अणु
	bool has_modet0 = go->modet[0].enable;
	bool has_modet1 = go->modet[1].enable;
	bool has_modet2 = go->modet[2].enable;
	bool has_modet3 = go->modet[3].enable;
	पूर्णांक ret, mb, i, addr, cnt = 0;
	u16 pack[32];
	u16 thresholds[] = अणु
		0x200e,		0,
		0xbf82,		has_modet0 ? go->modet[0].pixel_threshold : 32767,
		0xbf83,		has_modet1 ? go->modet[1].pixel_threshold : 32767,
		0xbf84,		has_modet2 ? go->modet[2].pixel_threshold : 32767,
		0xbf85,		has_modet3 ? go->modet[3].pixel_threshold : 32767,
		0xbf86,		has_modet0 ? go->modet[0].motion_threshold : 32767,
		0xbf87,		has_modet1 ? go->modet[1].motion_threshold : 32767,
		0xbf88,		has_modet2 ? go->modet[2].motion_threshold : 32767,
		0xbf89,		has_modet3 ? go->modet[3].motion_threshold : 32767,
		0xbf8a,		has_modet0 ? go->modet[0].mb_threshold : 32767,
		0xbf8b,		has_modet1 ? go->modet[1].mb_threshold : 32767,
		0xbf8c,		has_modet2 ? go->modet[2].mb_threshold : 32767,
		0xbf8d,		has_modet3 ? go->modet[3].mb_threshold : 32767,
		0xbf8e,		0,
		0xbf8f,		0,
		0,		0,
	पूर्ण;

	ret = copy_packages(code, thresholds, 1, space);
	अगर (ret < 0)
		वापस -1;
	cnt += ret;

	addr = 0xbac0;
	स_रखो(pack, 0, 64);
	i = 0;
	क्रम (mb = 0; mb < 1624; ++mb) अणु
		pack[i * 2 + 3] <<= 2;
		pack[i * 2 + 3] |= go->modet_map[mb];
		अगर (mb % 8 != 7)
			जारी;
		pack[i * 2 + 2] = addr++;
		++i;
		अगर (i == 10 || mb == 1623) अणु
			pack[0] = 0x2000 | i;
			ret = copy_packages(code + cnt, pack, 1, space - cnt);
			अगर (ret < 0)
				वापस -1;
			cnt += ret;
			i = 0;
			स_रखो(pack, 0, 64);
		पूर्ण
		pack[i * 2 + 3] = 0;
	पूर्ण

	स_रखो(pack, 0, 64);
	i = 0;
	क्रम (addr = 0xbb90; addr < 0xbbfa; ++addr) अणु
		pack[i * 2 + 2] = addr;
		pack[i * 2 + 3] = 0;
		++i;
		अगर (i == 10 || addr == 0xbbf9) अणु
			pack[0] = 0x2000 | i;
			ret = copy_packages(code + cnt, pack, 1, space - cnt);
			अगर (ret < 0)
				वापस -1;
			cnt += ret;
			i = 0;
			स_रखो(pack, 0, 64);
		पूर्ण
	पूर्ण
	वापस cnt;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक करो_special(काष्ठा go7007 *go, u16 type,
					 __le16 *code, पूर्णांक space, पूर्णांक *framelen)
अणु
	चयन (type) अणु
	हाल SPECIAL_FRM_HEAD:
		चयन (go->क्रमmat) अणु
		हाल V4L2_PIX_FMT_MJPEG:
			वापस gen_mjpeghdr_to_package(go, code, space);
		हाल V4L2_PIX_FMT_MPEG1:
		हाल V4L2_PIX_FMT_MPEG2:
			वापस gen_mpeg1hdr_to_package(go, code, space,
								framelen);
		हाल V4L2_PIX_FMT_MPEG4:
			वापस gen_mpeg4hdr_to_package(go, code, space,
								framelen);
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SPECIAL_BRC_CTRL:
		वापस brctrl_to_package(go, code, space, framelen);
	हाल SPECIAL_CONFIG:
		वापस config_package(go, code, space);
	हाल SPECIAL_SEQHEAD:
		चयन (go->क्रमmat) अणु
		हाल V4L2_PIX_FMT_MPEG1:
		हाल V4L2_PIX_FMT_MPEG2:
			वापस seqhead_to_package(go, code, space,
					mpeg1_sequence_header);
		हाल V4L2_PIX_FMT_MPEG4:
			वापस seqhead_to_package(go, code, space,
					mpeg4_sequence_header);
		शेष:
			वापस 0;
		पूर्ण
	हाल SPECIAL_AV_SYNC:
		वापस avsync_to_package(go, code, space);
	हाल SPECIAL_FINAL:
		वापस final_package(go, code, space);
	हाल SPECIAL_AUDIO:
		वापस audio_to_package(go, code, space);
	हाल SPECIAL_MODET:
		वापस modet_to_package(go, code, space);
	पूर्ण
	dev_err(go->dev,
		"firmware file contains unsupported feature %04x\n", type);
	वापस -1;
पूर्ण

पूर्णांक go7007_स्थिरruct_fw_image(काष्ठा go7007 *go, u8 **fw, पूर्णांक *fwlen)
अणु
	स्थिर काष्ठा firmware *fw_entry;
	__le16 *code, *src;
	पूर्णांक framelen[8] = अणु पूर्ण; /* holds the lengths of empty frame ढाँचाs */
	पूर्णांक codespace = 64 * 1024, i = 0, srclen, chunk_len, chunk_flags;
	पूर्णांक mode_flag;
	पूर्णांक ret;

	चयन (go->क्रमmat) अणु
	हाल V4L2_PIX_FMT_MJPEG:
		mode_flag = FLAG_MODE_MJPEG;
		अवरोध;
	हाल V4L2_PIX_FMT_MPEG1:
		mode_flag = FLAG_MODE_MPEG1;
		अवरोध;
	हाल V4L2_PIX_FMT_MPEG2:
		mode_flag = FLAG_MODE_MPEG2;
		अवरोध;
	हाल V4L2_PIX_FMT_MPEG4:
		mode_flag = FLAG_MODE_MPEG4;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	अगर (request_firmware(&fw_entry, GO7007_FW_NAME, go->dev)) अणु
		dev_err(go->dev,
			"unable to load firmware from file \"%s\"\n",
			GO7007_FW_NAME);
		वापस -1;
	पूर्ण
	code = kसुस्मृति(codespace, 2, GFP_KERNEL);
	अगर (code == शून्य)
		जाओ fw_failed;

	src = (__le16 *)fw_entry->data;
	srclen = fw_entry->size / 2;
	जबतक (srclen >= 2) अणु
		chunk_flags = __le16_to_cpu(src[0]);
		chunk_len = __le16_to_cpu(src[1]);
		अगर (chunk_len + 2 > srclen) अणु
			dev_err(go->dev,
				"firmware file \"%s\" appears to be corrupted\n",
				GO7007_FW_NAME);
			जाओ fw_failed;
		पूर्ण
		अगर (chunk_flags & mode_flag) अणु
			अगर (chunk_flags & FLAG_SPECIAL) अणु
				ret = करो_special(go, __le16_to_cpu(src[2]),
					&code[i], codespace - i, framelen);
				अगर (ret < 0) अणु
					dev_err(go->dev,
						"insufficient memory for firmware construction\n");
					जाओ fw_failed;
				पूर्ण
				i += ret;
			पूर्ण अन्यथा अणु
				अगर (codespace - i < chunk_len) अणु
					dev_err(go->dev,
						"insufficient memory for firmware construction\n");
					जाओ fw_failed;
				पूर्ण
				स_नकल(&code[i], &src[2], chunk_len * 2);
				i += chunk_len;
			पूर्ण
		पूर्ण
		srclen -= chunk_len + 2;
		src += chunk_len + 2;
	पूर्ण
	release_firmware(fw_entry);
	*fw = (u8 *)code;
	*fwlen = i * 2;
	वापस 0;

fw_failed:
	kमुक्त(code);
	release_firmware(fw_entry);
	वापस -1;
पूर्ण

MODULE_FIRMWARE(GO7007_FW_NAME);
