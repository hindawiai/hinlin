<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "odm_precomp.h"

/*  Global var */

u32 OFDMSwingTable[OFDM_TABLE_SIZE] = अणु
	0x7f8001fe, /*  0, +6.0dB */
	0x788001e2, /*  1, +5.5dB */
	0x71c001c7, /*  2, +5.0dB */
	0x6b8001ae, /*  3, +4.5dB */
	0x65400195, /*  4, +4.0dB */
	0x5fc0017f, /*  5, +3.5dB */
	0x5a400169, /*  6, +3.0dB */
	0x55400155, /*  7, +2.5dB */
	0x50800142, /*  8, +2.0dB */
	0x4c000130, /*  9, +1.5dB */
	0x47c0011f, /*  10, +1.0dB */
	0x43c0010f, /*  11, +0.5dB */
	0x40000100, /*  12, +0dB */
	0x3c8000f2, /*  13, -0.5dB */
	0x390000e4, /*  14, -1.0dB */
	0x35c000d7, /*  15, -1.5dB */
	0x32c000cb, /*  16, -2.0dB */
	0x300000c0, /*  17, -2.5dB */
	0x2d4000b5, /*  18, -3.0dB */
	0x2ac000ab, /*  19, -3.5dB */
	0x288000a2, /*  20, -4.0dB */
	0x26000098, /*  21, -4.5dB */
	0x24000090, /*  22, -5.0dB */
	0x22000088, /*  23, -5.5dB */
	0x20000080, /*  24, -6.0dB */
	0x1e400079, /*  25, -6.5dB */
	0x1c800072, /*  26, -7.0dB */
	0x1b00006c, /*  27. -7.5dB */
	0x19800066, /*  28, -8.0dB */
	0x18000060, /*  29, -8.5dB */
	0x16c0005b, /*  30, -9.0dB */
	0x15800056, /*  31, -9.5dB */
	0x14400051, /*  32, -10.0dB */
	0x1300004c, /*  33, -10.5dB */
	0x12000048, /*  34, -11.0dB */
	0x11000044, /*  35, -11.5dB */
	0x10000040, /*  36, -12.0dB */
पूर्ण;

u8 CCKSwingTable_Ch1_Ch13[CCK_TABLE_SIZE][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04पूर्ण, /*  0, +0dB */
	अणु0x33, 0x32, 0x2b, 0x23, 0x1a, 0x11, 0x08, 0x04पूर्ण, /*  1, -0.5dB */
	अणु0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03पूर्ण, /*  2, -1.0dB */
	अणु0x2d, 0x2d, 0x27, 0x1f, 0x18, 0x0f, 0x08, 0x03पूर्ण, /*  3, -1.5dB */
	अणु0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03पूर्ण, /*  4, -2.0dB */
	अणु0x28, 0x28, 0x22, 0x1c, 0x15, 0x0d, 0x07, 0x03पूर्ण, /*  5, -2.5dB */
	अणु0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03पूर्ण, /*  6, -3.0dB */
	अणु0x24, 0x23, 0x1f, 0x19, 0x13, 0x0c, 0x06, 0x03पूर्ण, /*  7, -3.5dB */
	अणु0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02पूर्ण, /*  8, -4.0dB */
	अणु0x20, 0x20, 0x1b, 0x16, 0x11, 0x08, 0x05, 0x02पूर्ण, /*  9, -4.5dB */
	अणु0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02पूर्ण, /*  10, -5.0dB */
	अणु0x1d, 0x1c, 0x18, 0x14, 0x0f, 0x0a, 0x05, 0x02पूर्ण, /*  11, -5.5dB */
	अणु0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02पूर्ण, /*  12, -6.0dB <== शेष */
	अणु0x1a, 0x19, 0x16, 0x12, 0x0d, 0x09, 0x04, 0x02पूर्ण, /*  13, -6.5dB */
	अणु0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02पूर्ण, /*  14, -7.0dB */
	अणु0x17, 0x16, 0x13, 0x10, 0x0c, 0x08, 0x04, 0x02पूर्ण, /*  15, -7.5dB */
	अणु0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01पूर्ण, /*  16, -8.0dB */
	अणु0x14, 0x14, 0x11, 0x0e, 0x0b, 0x07, 0x03, 0x02पूर्ण, /*  17, -8.5dB */
	अणु0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01पूर्ण, /*  18, -9.0dB */
	अणु0x12, 0x12, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण, /*  19, -9.5dB */
	अणु0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण, /*  20, -10.0dB */
	अणु0x10, 0x10, 0x0e, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण, /*  21, -10.5dB */
	अणु0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण, /*  22, -11.0dB */
	अणु0x0e, 0x0e, 0x0c, 0x0a, 0x08, 0x05, 0x02, 0x01पूर्ण, /*  23, -11.5dB */
	अणु0x0d, 0x0d, 0x0c, 0x0a, 0x07, 0x05, 0x02, 0x01पूर्ण, /*  24, -12.0dB */
	अणु0x0d, 0x0c, 0x0b, 0x09, 0x07, 0x04, 0x02, 0x01पूर्ण, /*  25, -12.5dB */
	अणु0x0c, 0x0c, 0x0a, 0x09, 0x06, 0x04, 0x02, 0x01पूर्ण, /*  26, -13.0dB */
	अणु0x0b, 0x0b, 0x0a, 0x08, 0x06, 0x04, 0x02, 0x01पूर्ण, /*  27, -13.5dB */
	अणु0x0b, 0x0a, 0x09, 0x08, 0x06, 0x04, 0x02, 0x01पूर्ण, /*  28, -14.0dB */
	अणु0x0a, 0x0a, 0x09, 0x07, 0x05, 0x03, 0x02, 0x01पूर्ण, /*  29, -14.5dB */
	अणु0x0a, 0x09, 0x08, 0x07, 0x05, 0x03, 0x02, 0x01पूर्ण, /*  30, -15.0dB */
	अणु0x09, 0x09, 0x08, 0x06, 0x05, 0x03, 0x01, 0x01पूर्ण, /*  31, -15.5dB */
	अणु0x09, 0x08, 0x07, 0x06, 0x04, 0x03, 0x01, 0x01पूर्ण	/*  32, -16.0dB */
पूर्ण;

u8 CCKSwingTable_Ch14[CCK_TABLE_SIZE][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  0, +0dB */
	अणु0x33, 0x32, 0x2b, 0x19, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  1, -0.5dB */
	अणु0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  2, -1.0dB */
	अणु0x2d, 0x2d, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  3, -1.5dB */
	अणु0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  4, -2.0dB */
	अणु0x28, 0x28, 0x24, 0x14, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  5, -2.5dB */
	अणु0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  6, -3.0dB */
	अणु0x24, 0x23, 0x1f, 0x12, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  7, -3.5dB */
	अणु0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  8, -4.0dB */
	अणु0x20, 0x20, 0x1b, 0x10, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  9, -4.5dB */
	अणु0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  10, -5.0dB */
	अणु0x1d, 0x1c, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  11, -5.5dB */
	अणु0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  12, -6.0dB  <== शेष */
	अणु0x1a, 0x19, 0x16, 0x0d, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  13, -6.5dB */
	अणु0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  14, -7.0dB */
	अणु0x17, 0x16, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  15, -7.5dB */
	अणु0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  16, -8.0dB */
	अणु0x14, 0x14, 0x11, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  17, -8.5dB */
	अणु0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  18, -9.0dB */
	अणु0x12, 0x12, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  19, -9.5dB */
	अणु0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  20, -10.0dB */
	अणु0x10, 0x10, 0x0e, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  21, -10.5dB */
	अणु0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  22, -11.0dB */
	अणु0x0e, 0x0e, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  23, -11.5dB */
	अणु0x0d, 0x0d, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  24, -12.0dB */
	अणु0x0d, 0x0c, 0x0b, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  25, -12.5dB */
	अणु0x0c, 0x0c, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  26, -13.0dB */
	अणु0x0b, 0x0b, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  27, -13.5dB */
	अणु0x0b, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  28, -14.0dB */
	अणु0x0a, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  29, -14.5dB */
	अणु0x0a, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  30, -15.0dB */
	अणु0x09, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  31, -15.5dB */
	अणु0x09, 0x08, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00पूर्ण	/*  32, -16.0dB */
पूर्ण;

u32 OFDMSwingTable_New[OFDM_TABLE_SIZE] = अणु
	0x0b40002d, /*  0,  -15.0dB */
	0x0c000030, /*  1,  -14.5dB */
	0x0cc00033, /*  2,  -14.0dB */
	0x0d800036, /*  3,  -13.5dB */
	0x0e400039, /*  4,  -13.0dB */
	0x0f00003c, /*  5,  -12.5dB */
	0x10000040, /*  6,  -12.0dB */
	0x11000044, /*  7,  -11.5dB */
	0x12000048, /*  8,  -11.0dB */
	0x1300004c, /*  9,  -10.5dB */
	0x14400051, /*  10, -10.0dB */
	0x15800056, /*  11, -9.5dB */
	0x16c0005b, /*  12, -9.0dB */
	0x18000060, /*  13, -8.5dB */
	0x19800066, /*  14, -8.0dB */
	0x1b00006c, /*  15, -7.5dB */
	0x1c800072, /*  16, -7.0dB */
	0x1e400079, /*  17, -6.5dB */
	0x20000080, /*  18, -6.0dB */
	0x22000088, /*  19, -5.5dB */
	0x24000090, /*  20, -5.0dB */
	0x26000098, /*  21, -4.5dB */
	0x288000a2, /*  22, -4.0dB */
	0x2ac000ab, /*  23, -3.5dB */
	0x2d4000b5, /*  24, -3.0dB */
	0x300000c0, /*  25, -2.5dB */
	0x32c000cb, /*  26, -2.0dB */
	0x35c000d7, /*  27, -1.5dB */
	0x390000e4, /*  28, -1.0dB */
	0x3c8000f2, /*  29, -0.5dB */
	0x40000100, /*  30, +0dB */
	0x43c0010f, /*  31, +0.5dB */
	0x47c0011f, /*  32, +1.0dB */
	0x4c000130, /*  33, +1.5dB */
	0x50800142, /*  34, +2.0dB */
	0x55400155, /*  35, +2.5dB */
	0x5a400169, /*  36, +3.0dB */
	0x5fc0017f, /*  37, +3.5dB */
	0x65400195, /*  38, +4.0dB */
	0x6b8001ae, /*  39, +4.5dB */
	0x71c001c7, /*  40, +5.0dB */
	0x788001e2, /*  41, +5.5dB */
	0x7f8001fe  /*  42, +6.0dB */
पूर्ण;

u8 CCKSwingTable_Ch1_Ch13_New[CCK_TABLE_SIZE][8] = अणु
	अणु0x09, 0x08, 0x07, 0x06, 0x04, 0x03, 0x01, 0x01पूर्ण, /*   0, -16.0dB */
	अणु0x09, 0x09, 0x08, 0x06, 0x05, 0x03, 0x01, 0x01पूर्ण, /*   1, -15.5dB */
	अणु0x0a, 0x09, 0x08, 0x07, 0x05, 0x03, 0x02, 0x01पूर्ण, /*   2, -15.0dB */
	अणु0x0a, 0x0a, 0x09, 0x07, 0x05, 0x03, 0x02, 0x01पूर्ण, /*   3, -14.5dB */
	अणु0x0b, 0x0a, 0x09, 0x08, 0x06, 0x04, 0x02, 0x01पूर्ण, /*   4, -14.0dB */
	अणु0x0b, 0x0b, 0x0a, 0x08, 0x06, 0x04, 0x02, 0x01पूर्ण, /*   5, -13.5dB */
	अणु0x0c, 0x0c, 0x0a, 0x09, 0x06, 0x04, 0x02, 0x01पूर्ण, /*   6, -13.0dB */
	अणु0x0d, 0x0c, 0x0b, 0x09, 0x07, 0x04, 0x02, 0x01पूर्ण, /*   7, -12.5dB */
	अणु0x0d, 0x0d, 0x0c, 0x0a, 0x07, 0x05, 0x02, 0x01पूर्ण, /*   8, -12.0dB */
	अणु0x0e, 0x0e, 0x0c, 0x0a, 0x08, 0x05, 0x02, 0x01पूर्ण, /*   9, -11.5dB */
	अणु0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण, /*  10, -11.0dB */
	अणु0x10, 0x10, 0x0e, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण, /*  11, -10.5dB */
	अणु0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण, /*  12, -10.0dB */
	अणु0x12, 0x12, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण, /*  13, -9.5dB */
	अणु0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01पूर्ण, /*  14, -9.0dB */
	अणु0x14, 0x14, 0x11, 0x0e, 0x0b, 0x07, 0x03, 0x02पूर्ण, /*  15, -8.5dB */
	अणु0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01पूर्ण, /*  16, -8.0dB */
	अणु0x17, 0x16, 0x13, 0x10, 0x0c, 0x08, 0x04, 0x02पूर्ण, /*  17, -7.5dB */
	अणु0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02पूर्ण, /*  18, -7.0dB */
	अणु0x1a, 0x19, 0x16, 0x12, 0x0d, 0x09, 0x04, 0x02पूर्ण, /*  19, -6.5dB */
	अणु0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02पूर्ण, /*  20, -6.0dB */
	अणु0x1d, 0x1c, 0x18, 0x14, 0x0f, 0x0a, 0x05, 0x02पूर्ण, /*  21, -5.5dB */
	अणु0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02पूर्ण, /*  22, -5.0dB */
	अणु0x20, 0x20, 0x1b, 0x16, 0x11, 0x08, 0x05, 0x02पूर्ण, /*  23, -4.5dB */
	अणु0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02पूर्ण, /*  24, -4.0dB */
	अणु0x24, 0x23, 0x1f, 0x19, 0x13, 0x0c, 0x06, 0x03पूर्ण, /*  25, -3.5dB */
	अणु0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03पूर्ण, /*  26, -3.0dB */
	अणु0x28, 0x28, 0x22, 0x1c, 0x15, 0x0d, 0x07, 0x03पूर्ण, /*  27, -2.5dB */
	अणु0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03पूर्ण, /*  28, -2.0dB */
	अणु0x2d, 0x2d, 0x27, 0x1f, 0x18, 0x0f, 0x08, 0x03पूर्ण, /*  29, -1.5dB */
	अणु0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03पूर्ण, /*  30, -1.0dB */
	अणु0x33, 0x32, 0x2b, 0x23, 0x1a, 0x11, 0x08, 0x04पूर्ण, /*  31, -0.5dB */
	अणु0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04पूर्ण	/*  32, +0dB */
पूर्ण;

u8 CCKSwingTable_Ch14_New[CCK_TABLE_SIZE][8] = अणु
	अणु0x09, 0x08, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00पूर्ण, /*   0, -16.0dB */
	अणु0x09, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण, /*   1, -15.5dB */
	अणु0x0a, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण, /*   2, -15.0dB */
	अणु0x0a, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण, /*   3, -14.5dB */
	अणु0x0b, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण, /*   4, -14.0dB */
	अणु0x0b, 0x0b, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण, /*   5, -13.5dB */
	अणु0x0c, 0x0c, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण, /*   6, -13.0dB */
	अणु0x0d, 0x0c, 0x0b, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण, /*   7, -12.5dB */
	अणु0x0d, 0x0d, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00पूर्ण, /*   8, -12.0dB */
	अणु0x0e, 0x0e, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00पूर्ण, /*   9, -11.5dB */
	अणु0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  10, -11.0dB */
	अणु0x10, 0x10, 0x0e, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  11, -10.5dB */
	अणु0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  12, -10.0dB */
	अणु0x12, 0x12, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  13, -9.5dB */
	अणु0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  14, -9.0dB */
	अणु0x14, 0x14, 0x11, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  15, -8.5dB */
	अणु0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  16, -8.0dB */
	अणु0x17, 0x16, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  17, -7.5dB */
	अणु0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  18, -7.0dB */
	अणु0x1a, 0x19, 0x16, 0x0d, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  19, -6.5dB */
	अणु0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  20, -6.0dB */
	अणु0x1d, 0x1c, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  21, -5.5dB */
	अणु0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  22, -5.0dB */
	अणु0x20, 0x20, 0x1b, 0x10, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  23, -4.5dB */
	अणु0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  24, -4.0dB */
	अणु0x24, 0x23, 0x1f, 0x12, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  25, -3.5dB */
	अणु0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  26, -3.0dB */
	अणु0x28, 0x28, 0x24, 0x14, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  27, -2.5dB */
	अणु0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  28, -2.0dB */
	अणु0x2d, 0x2d, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  29, -1.5dB */
	अणु0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  30, -1.0dB */
	अणु0x33, 0x32, 0x2b, 0x19, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  31, -0.5dB */
	अणु0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00पूर्ण	/*  32, +0dB */
पूर्ण;

u32 TxScalingTable_Jaguar[TXSCALE_TABLE_SIZE] = अणु
	0x081, /*  0,  -12.0dB */
	0x088, /*  1,  -11.5dB */
	0x090, /*  2,  -11.0dB */
	0x099, /*  3,  -10.5dB */
	0x0A2, /*  4,  -10.0dB */
	0x0AC, /*  5,  -9.5dB */
	0x0B6, /*  6,  -9.0dB */
	0x0C0, /*  7,  -8.5dB */
	0x0CC, /*  8,  -8.0dB */
	0x0D8, /*  9,  -7.5dB */
	0x0E5, /*  10, -7.0dB */
	0x0F2, /*  11, -6.5dB */
	0x101, /*  12, -6.0dB */
	0x110, /*  13, -5.5dB */
	0x120, /*  14, -5.0dB */
	0x131, /*  15, -4.5dB */
	0x143, /*  16, -4.0dB */
	0x156, /*  17, -3.5dB */
	0x16A, /*  18, -3.0dB */
	0x180, /*  19, -2.5dB */
	0x197, /*  20, -2.0dB */
	0x1AF, /*  21, -1.5dB */
	0x1C8, /*  22, -1.0dB */
	0x1E3, /*  23, -0.5dB */
	0x200, /*  24, +0  dB */
	0x21E, /*  25, +0.5dB */
	0x23E, /*  26, +1.0dB */
	0x261, /*  27, +1.5dB */
	0x285, /*  28, +2.0dB */
	0x2AB, /*  29, +2.5dB */
	0x2D3, /*  30, +3.0dB */
	0x2FE, /*  31, +3.5dB */
	0x32B, /*  32, +4.0dB */
	0x35C, /*  33, +4.5dB */
	0x38E, /*  34, +5.0dB */
	0x3C4, /*  35, +5.5dB */
	0x3FE  /*  36, +6.0dB */
पूर्ण;

/* Remove Edca by Yu Chen */


#घोषणा RxDefaultAnt1		0x65a9
#घोषणा RxDefaultAnt2		0x569a

अटल व्योम odm_CommonInfoSelfInit(काष्ठा dm_odm_t *pDM_Odm)
अणु
	pDM_Odm->bCckHighPower = (bool) PHY_QueryBBReg(pDM_Odm->Adapter, ODM_REG(CCK_RPT_FORMAT, pDM_Odm), ODM_BIT(CCK_RPT_FORMAT, pDM_Odm));
	pDM_Odm->RFPathRxEnable = (u8) PHY_QueryBBReg(pDM_Odm->Adapter, ODM_REG(BB_RX_PATH, pDM_Odm), ODM_BIT(BB_RX_PATH, pDM_Odm));

	ODM_InitDebugSetting(pDM_Odm);

	pDM_Odm->TxRate = 0xFF;
पूर्ण

अटल व्योम odm_CommonInfoSelfUpdate(काष्ठा dm_odm_t *pDM_Odm)
अणु
	u8 EntryCnt = 0;
	u8 i;
	PSTA_INFO_T	pEntry;

	अगर (*(pDM_Odm->pBandWidth) == ODM_BW40M) अणु
		अगर (*(pDM_Odm->pSecChOffset) == 1)
			pDM_Odm->ControlChannel = *(pDM_Odm->pChannel)-2;
		अन्यथा अगर (*(pDM_Odm->pSecChOffset) == 2)
			pDM_Odm->ControlChannel = *(pDM_Odm->pChannel)+2;
	पूर्ण अन्यथा
		pDM_Odm->ControlChannel = *(pDM_Odm->pChannel);

	क्रम (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++) अणु
		pEntry = pDM_Odm->pODM_StaInfo[i];
		अगर (IS_STA_VALID(pEntry))
			EntryCnt++;
	पूर्ण

	अगर (EntryCnt == 1)
		pDM_Odm->bOneEntryOnly = true;
	अन्यथा
		pDM_Odm->bOneEntryOnly = false;
पूर्ण

अटल व्योम odm_CmnInfoInit_Debug(काष्ठा dm_odm_t *pDM_Odm)
अणु
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("odm_CmnInfoInit_Debug ==>\n"));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("SupportPlatform =%d\n", pDM_Odm->SupportPlatक्रमm));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("SupportAbility = 0x%x\n", pDM_Odm->SupportAbility));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("SupportInterface =%d\n", pDM_Odm->SupportInterface));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("SupportICType = 0x%x\n", pDM_Odm->SupportICType));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("CutVersion =%d\n", pDM_Odm->CutVersion));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("FabVersion =%d\n", pDM_Odm->FabVersion));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("RFType =%d\n", pDM_Odm->RFType));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("BoardType =%d\n", pDM_Odm->BoardType));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("ExtLNA =%d\n", pDM_Odm->ExtLNA));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("ExtPA =%d\n", pDM_Odm->ExtPA));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("ExtTRSW =%d\n", pDM_Odm->ExtTRSW));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("PatchID =%d\n", pDM_Odm->PatchID));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("bInHctTest =%d\n", pDM_Odm->bInHctTest));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("bWIFITest =%d\n", pDM_Odm->bWIFITest));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("bDualMacSmartConcurrent =%d\n", pDM_Odm->bDualMacSmartConcurrent));

पूर्ण

अटल व्योम odm_BasicDbgMessage(काष्ठा dm_odm_t *pDM_Odm)
अणु
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("odm_BasicDbgMsg ==>\n"));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("bLinked = %d, RSSI_Min = %d,\n",
		pDM_Odm->bLinked, pDM_Odm->RSSI_Min));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("RxRate = 0x%x, RSSI_A = %d, RSSI_B = %d\n",
		pDM_Odm->RxRate, pDM_Odm->RSSI_A, pDM_Odm->RSSI_B));
पूर्ण

/* 3 ============================================================ */
/* 3 RATR MASK */
/* 3 ============================================================ */
/* 3 ============================================================ */
/* 3 Rate Adaptive */
/* 3 ============================================================ */

अटल व्योम odm_RateAdaptiveMaskInit(काष्ठा dm_odm_t *pDM_Odm)
अणु
	काष्ठा odm_rate_adaptive *pOdmRA = &pDM_Odm->RateAdaptive;

	pOdmRA->Type = DM_Type_ByDriver;
	अगर (pOdmRA->Type == DM_Type_ByDriver)
		pDM_Odm->bUseRAMask = true;
	अन्यथा
		pDM_Odm->bUseRAMask = false;

	pOdmRA->RATRState = DM_RATR_STA_INIT;
	pOdmRA->LdpcThres = 35;
	pOdmRA->bUseLdpc = false;
	pOdmRA->HighRSSIThresh = 50;
	pOdmRA->LowRSSIThresh = 20;
पूर्ण

u32 ODM_Get_Rate_Biपंचांगap(
	काष्ठा dm_odm_t *pDM_Odm,
	u32 macid,
	u32 ra_mask,
	u8 rssi_level
)
अणु
	PSTA_INFO_T	pEntry;
	u32 rate_biपंचांगap = 0;
	u8 WirelessMode;

	pEntry = pDM_Odm->pODM_StaInfo[macid];
	अगर (!IS_STA_VALID(pEntry))
		वापस ra_mask;

	WirelessMode = pEntry->wireless_mode;

	चयन (WirelessMode) अणु
	हाल ODM_WM_B:
		अगर (ra_mask & 0x0000000c)		/* 11M or 5.5M enable */
			rate_biपंचांगap = 0x0000000d;
		अन्यथा
			rate_biपंचांगap = 0x0000000f;
		अवरोध;

	हाल (ODM_WM_G):
	हाल (ODM_WM_A):
		अगर (rssi_level == DM_RATR_STA_HIGH)
			rate_biपंचांगap = 0x00000f00;
		अन्यथा
			rate_biपंचांगap = 0x00000ff0;
		अवरोध;

	हाल (ODM_WM_B|ODM_WM_G):
		अगर (rssi_level == DM_RATR_STA_HIGH)
			rate_biपंचांगap = 0x00000f00;
		अन्यथा अगर (rssi_level == DM_RATR_STA_MIDDLE)
			rate_biपंचांगap = 0x00000ff0;
		अन्यथा
			rate_biपंचांगap = 0x00000ff5;
		अवरोध;

	हाल (ODM_WM_B|ODM_WM_G|ODM_WM_N24G):
	हाल (ODM_WM_B|ODM_WM_N24G):
	हाल (ODM_WM_G|ODM_WM_N24G):
	हाल (ODM_WM_A|ODM_WM_N5G):
		अगर (pDM_Odm->RFType == ODM_1T2R || pDM_Odm->RFType == ODM_1T1R) अणु
			अगर (rssi_level == DM_RATR_STA_HIGH)
				rate_biपंचांगap = 0x000f0000;
			अन्यथा अगर (rssi_level == DM_RATR_STA_MIDDLE)
				rate_biपंचांगap = 0x000ff000;
			अन्यथा अणु
				अगर (*(pDM_Odm->pBandWidth) == ODM_BW40M)
					rate_biपंचांगap = 0x000ff015;
				अन्यथा
					rate_biपंचांगap = 0x000ff005;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (rssi_level == DM_RATR_STA_HIGH)
				rate_biपंचांगap = 0x0f8f0000;
			अन्यथा अगर (rssi_level == DM_RATR_STA_MIDDLE)
				rate_biपंचांगap = 0x0f8ff000;
			अन्यथा अणु
				अगर (*(pDM_Odm->pBandWidth) == ODM_BW40M)
					rate_biपंचांगap = 0x0f8ff015;
				अन्यथा
					rate_biपंचांगap = 0x0f8ff005;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल (ODM_WM_AC|ODM_WM_G):
		अगर (rssi_level == 1)
			rate_biपंचांगap = 0xfc3f0000;
		अन्यथा अगर (rssi_level == 2)
			rate_biपंचांगap = 0xfffff000;
		अन्यथा
			rate_biपंचांगap = 0xffffffff;
		अवरोध;

	हाल (ODM_WM_AC|ODM_WM_A):

		अगर (pDM_Odm->RFType == RF_1T1R) अणु
			अगर (rssi_level == 1)				/*  add by Gary क्रम ac-series */
				rate_biपंचांगap = 0x003f8000;
			अन्यथा अगर (rssi_level == 2)
				rate_biपंचांगap = 0x003ff000;
			अन्यथा
				rate_biपंचांगap = 0x003ff010;
		पूर्ण अन्यथा अणु
			अगर (rssi_level == 1)				/*  add by Gary क्रम ac-series */
				rate_biपंचांगap = 0xfe3f8000;       /*  VHT 2SS MCS3~9 */
			अन्यथा अगर (rssi_level == 2)
				rate_biपंचांगap = 0xfffff000;       /*  VHT 2SS MCS0~9 */
			अन्यथा
				rate_biपंचांगap = 0xfffff010;       /*  All */
		पूर्ण
		अवरोध;

	शेष:
		अगर (pDM_Odm->RFType == RF_1T2R)
			rate_biपंचांगap = 0x000fffff;
		अन्यथा
			rate_biपंचांगap = 0x0fffffff;
		अवरोध;
	पूर्ण

	/* prपूर्णांकk("%s ==> rssi_level:0x%02x, WirelessMode:0x%02x, rate_bitmap:0x%08x\n", __func__, rssi_level, WirelessMode, rate_biपंचांगap); */
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_RA_MASK, ODM_DBG_LOUD, (" ==> rssi_level:0x%02x, WirelessMode:0x%02x, rate_bitmap:0x%08x\n", rssi_level, WirelessMode, rate_biपंचांगap));

	वापस ra_mask & rate_biपंचांगap;

पूर्ण

अटल व्योम odm_RefreshRateAdaptiveMaskCE(काष्ठा dm_odm_t *pDM_Odm)
अणु
	u8 i;
	काष्ठा adapter *padapter =  pDM_Odm->Adapter;

	अगर (padapter->bDriverStopped) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_RA_MASK, ODM_DBG_TRACE, ("<---- odm_RefreshRateAdaptiveMask(): driver is going to unload\n"));
		वापस;
	पूर्ण

	अगर (!pDM_Odm->bUseRAMask) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_RA_MASK, ODM_DBG_LOUD, ("<---- odm_RefreshRateAdaptiveMask(): driver does not control rate adaptive mask\n"));
		वापस;
	पूर्ण

	क्रम (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++) अणु
		PSTA_INFO_T pstat = pDM_Odm->pODM_StaInfo[i];

		अगर (IS_STA_VALID(pstat)) अणु
			अगर (IS_MCAST(pstat->hwaddr))  /* अगर (psta->mac_id == 1) */
				जारी;

			अगर (true == ODM_RAStateCheck(pDM_Odm, pstat->rssi_stat.UndecoratedSmoothedPWDB, false, &pstat->rssi_level)) अणु
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_RA_MASK, ODM_DBG_LOUD, ("RSSI:%d, RSSI_LEVEL:%d\n", pstat->rssi_stat.UndecoratedSmoothedPWDB, pstat->rssi_level));
				/* prपूर्णांकk("RSSI:%d, RSSI_LEVEL:%d\n", pstat->rssi_stat.UndecoratedSmoothedPWDB, pstat->rssi_level); */
				rtw_hal_update_ra_mask(pstat, pstat->rssi_level);
			पूर्ण

		पूर्ण
	पूर्ण
पूर्ण

/*-----------------------------------------------------------------------------
* Function:	odm_RefreshRateAdaptiveMask()
*
* Overview:	Update rate table mask according to rssi
*
* Input:		NONE
*
* Output:		NONE
*
* Return:		NONE
*
* Revised History:
*When		Who		Remark
*05/27/2009	hpfan	Create Version 0.
*
* --------------------------------------------------------------------------
*/
अटल व्योम odm_RefreshRateAdaptiveMask(काष्ठा dm_odm_t *pDM_Odm)
अणु

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_RA_MASK, ODM_DBG_TRACE, ("odm_RefreshRateAdaptiveMask()---------->\n"));
	अगर (!(pDM_Odm->SupportAbility & ODM_BB_RA_MASK)) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_RA_MASK, ODM_DBG_TRACE, ("odm_RefreshRateAdaptiveMask(): Return cos not supported\n"));
		वापस;
	पूर्ण
	odm_RefreshRateAdaptiveMaskCE(pDM_Odm);
पूर्ण

/*  Return Value: bool */
/*  - true: RATRState is changed. */
bool ODM_RAStateCheck(
	काष्ठा dm_odm_t *pDM_Odm,
	s32 RSSI,
	bool bForceUpdate,
	u8 *pRATRState
)
अणु
	काष्ठा odm_rate_adaptive *pRA = &pDM_Odm->RateAdaptive;
	स्थिर u8 GoUpGap = 5;
	u8 HighRSSIThreshForRA = pRA->HighRSSIThresh;
	u8 LowRSSIThreshForRA = pRA->LowRSSIThresh;
	u8 RATRState;

	/*  Threshold Adjusपंचांगent: */
	/*  when RSSI state trends to go up one or two levels, make sure RSSI is high enough. */
	/*  Here GoUpGap is added to solve the boundary's level alternation issue. */
	चयन (*pRATRState) अणु
	हाल DM_RATR_STA_INIT:
	हाल DM_RATR_STA_HIGH:
		अवरोध;

	हाल DM_RATR_STA_MIDDLE:
		HighRSSIThreshForRA += GoUpGap;
		अवरोध;

	हाल DM_RATR_STA_LOW:
		HighRSSIThreshForRA += GoUpGap;
		LowRSSIThreshForRA += GoUpGap;
		अवरोध;

	शेष:
		ODM_RT_ASSERT(pDM_Odm, false, ("wrong rssi level setting %d !", *pRATRState));
		अवरोध;
	पूर्ण

	/*  Decide RATRState by RSSI. */
	अगर (RSSI > HighRSSIThreshForRA)
		RATRState = DM_RATR_STA_HIGH;
	अन्यथा अगर (RSSI > LowRSSIThreshForRA)
		RATRState = DM_RATR_STA_MIDDLE;
	अन्यथा
		RATRState = DM_RATR_STA_LOW;
	/* prपूर्णांकk("==>%s, RATRState:0x%02x , RSSI:%d\n", __func__, RATRState, RSSI); */

	अगर (*pRATRState != RATRState || bForceUpdate) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_RA_MASK, ODM_DBG_LOUD, ("RSSI Level %d -> %d\n", *pRATRState, RATRState));
		*pRATRState = RATRState;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*  */

/* 3 ============================================================ */
/* 3 RSSI Monitor */
/* 3 ============================================================ */

अटल व्योम odm_RSSIMonitorInit(काष्ठा dm_odm_t *pDM_Odm)
अणु
	काष्ठा ra_t *pRA_Table = &pDM_Odm->DM_RA_Table;

	pRA_Table->firstconnect = false;

पूर्ण

अटल व्योम FindMinimumRSSI(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_priv *pdmpriv = &pHalData->dmpriv;
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	/* 1 1.Determine the minimum RSSI */

	अगर (
		(pDM_Odm->bLinked != true) &&
		(pdmpriv->EntryMinUndecoratedSmoothedPWDB == 0)
	) अणु
		pdmpriv->MinUndecoratedPWDBForDM = 0;
		/* ODM_RT_TRACE(pDM_Odm, COMP_BB_POWERSAVING, DBG_LOUD, ("Not connected to any\n")); */
	पूर्ण अन्यथा
		pdmpriv->MinUndecoratedPWDBForDM = pdmpriv->EntryMinUndecoratedSmoothedPWDB;

	/* ODM_RT_TRACE(pDM_Odm, COMP_DIG, DBG_LOUD, ("MinUndecoratedPWDBForDM =%d\n", pHalData->MinUndecoratedPWDBForDM)); */
पूर्ण

अटल व्योम odm_RSSIMonitorCheckCE(काष्ठा dm_odm_t *pDM_Odm)
अणु
	काष्ठा adapter *Adapter = pDM_Odm->Adapter;
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(Adapter);
	काष्ठा dm_priv *pdmpriv = &pHalData->dmpriv;
	पूर्णांक i;
	पूर्णांक पंचांगpEntryMaxPWDB = 0, पंचांगpEntryMinPWDB = 0xff;
	u8 sta_cnt = 0;
	u32 PWDB_rssi[NUM_STA] = अणु0पूर्ण;/* 0~15]:MACID, [16~31]:PWDB_rssi */
	काष्ठा ra_t *pRA_Table = &pDM_Odm->DM_RA_Table;

	अगर (pDM_Odm->bLinked != true)
		वापस;

	pRA_Table->firstconnect = pDM_Odm->bLinked;

	/* अगर (check_fwstate(&Adapter->mlmepriv, WIFI_AP_STATE|WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE) == true) */
	अणु
		काष्ठा sta_info *psta;

		क्रम (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++) अणु
			psta = pDM_Odm->pODM_StaInfo[i];
			अगर (IS_STA_VALID(psta)) अणु
				अगर (IS_MCAST(psta->hwaddr))  /* अगर (psta->mac_id == 1) */
					जारी;

				अगर (psta->rssi_stat.UndecoratedSmoothedPWDB == (-1))
					जारी;

				अगर (psta->rssi_stat.UndecoratedSmoothedPWDB < पंचांगpEntryMinPWDB)
					पंचांगpEntryMinPWDB = psta->rssi_stat.UndecoratedSmoothedPWDB;

				अगर (psta->rssi_stat.UndecoratedSmoothedPWDB > पंचांगpEntryMaxPWDB)
					पंचांगpEntryMaxPWDB = psta->rssi_stat.UndecoratedSmoothedPWDB;

				अगर (psta->rssi_stat.UndecoratedSmoothedPWDB != (-1))
					PWDB_rssi[sta_cnt++] = (psta->mac_id | (psta->rssi_stat.UndecoratedSmoothedPWDB<<16));
			पूर्ण
		पूर्ण

		/* prपूर्णांकk("%s ==> sta_cnt(%d)\n", __func__, sta_cnt); */

		क्रम (i = 0; i < sta_cnt; i++) अणु
			अगर (PWDB_rssi[i] != (0)) अणु
				अगर (pHalData->fw_ractrl == true)/*  Report every sta's RSSI to FW */
					rtl8723b_set_rssi_cmd(Adapter, (u8 *)(&PWDB_rssi[i]));
			पूर्ण
		पूर्ण
	पूर्ण



	अगर (पंचांगpEntryMaxPWDB != 0)	/*  If associated entry is found */
		pdmpriv->EntryMaxUndecoratedSmoothedPWDB = पंचांगpEntryMaxPWDB;
	अन्यथा
		pdmpriv->EntryMaxUndecoratedSmoothedPWDB = 0;

	अगर (पंचांगpEntryMinPWDB != 0xff) /*  If associated entry is found */
		pdmpriv->EntryMinUndecoratedSmoothedPWDB = पंचांगpEntryMinPWDB;
	अन्यथा
		pdmpriv->EntryMinUndecoratedSmoothedPWDB = 0;

	FindMinimumRSSI(Adapter);/* get pdmpriv->MinUndecoratedPWDBForDM */

	pDM_Odm->RSSI_Min = pdmpriv->MinUndecoratedPWDBForDM;
	/* ODM_CmnInfoUpdate(&pHalData->odmpriv , ODM_CMNINFO_RSSI_MIN, pdmpriv->MinUndecoratedPWDBForDM); */
पूर्ण

अटल व्योम odm_RSSIMonitorCheck(काष्ठा dm_odm_t *pDM_Odm)
अणु
	अगर (!(pDM_Odm->SupportAbility & ODM_BB_RSSI_MONITOR))
		वापस;

	odm_RSSIMonitorCheckCE(pDM_Odm);

पूर्ण	/*  odm_RSSIMonitorCheck */

/* 3 ============================================================ */
/* 3 SW Antenna Diversity */
/* 3 ============================================================ */
अटल व्योम odm_SwAntDetectInit(काष्ठा dm_odm_t *pDM_Odm)
अणु
	काष्ठा swat_t *pDM_SWAT_Table = &pDM_Odm->DM_SWAT_Table;

	pDM_SWAT_Table->SWAS_NoLink_BK_Reg92c = rtw_पढ़ो32(pDM_Odm->Adapter, rDPDT_control);
	pDM_SWAT_Table->PreAntenna = MAIN_ANT;
	pDM_SWAT_Table->CurAntenna = MAIN_ANT;
	pDM_SWAT_Table->SWAS_NoLink_State = 0;
पूर्ण

/* 3 ============================================================ */
/* 3 Tx Power Tracking */
/* 3 ============================================================ */

अटल u8 getSwingIndex(काष्ठा dm_odm_t *pDM_Odm)
अणु
	काष्ठा adapter *Adapter = pDM_Odm->Adapter;
	u8 i = 0;
	u32 bbSwing;
	u32 swingTableSize;
	u32 *pSwingTable;

	bbSwing = PHY_QueryBBReg(Adapter, rOFDM0_XATxIQImbalance, 0xFFC00000);

	pSwingTable = OFDMSwingTable_New;
	swingTableSize = OFDM_TABLE_SIZE;

	क्रम (i = 0; i < swingTableSize; ++i) अणु
		u32 tableValue = pSwingTable[i];

		अगर (tableValue >= 0x100000)
			tableValue >>= 22;
		अगर (bbSwing == tableValue)
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

व्योम odm_TXPowerTrackingInit(काष्ठा dm_odm_t *pDM_Odm)
अणु
	u8 शेषSwingIndex = getSwingIndex(pDM_Odm);
	u8 p = 0;
	काष्ठा adapter *Adapter = pDM_Odm->Adapter;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);


	काष्ठा dm_priv *pdmpriv = &pHalData->dmpriv;

	pdmpriv->bTXPowerTracking = true;
	pdmpriv->TXPowercount = 0;
	pdmpriv->bTXPowerTrackingInit = false;

	अगर (*(pDM_Odm->mp_mode) != 1)
		pdmpriv->TxPowerTrackControl = true;
	अन्यथा
		pdmpriv->TxPowerTrackControl = false;

	/* pDM_Odm->RFCalibrateInfo.TxPowerTrackControl = true; */
	pDM_Odm->RFCalibrateInfo.ThermalValue = pHalData->EEPROMThermalMeter;
	pDM_Odm->RFCalibrateInfo.ThermalValue_IQK = pHalData->EEPROMThermalMeter;
	pDM_Odm->RFCalibrateInfo.ThermalValue_LCK = pHalData->EEPROMThermalMeter;

	/*  The index of "0 dB" in SwingTable. */
	pDM_Odm->DefaultOfdmIndex = (शेषSwingIndex >= OFDM_TABLE_SIZE) ? 30 : शेषSwingIndex;
	pDM_Odm->DefaultCckIndex = 20;

	pDM_Odm->BbSwingIdxCckBase = pDM_Odm->DefaultCckIndex;
	pDM_Odm->RFCalibrateInfo.CCK_index = pDM_Odm->DefaultCckIndex;

	क्रम (p = ODM_RF_PATH_A; p < MAX_RF_PATH; ++p) अणु
		pDM_Odm->BbSwingIdxOfdmBase[p] = pDM_Odm->DefaultOfdmIndex;
		pDM_Odm->RFCalibrateInfo.OFDM_index[p] = pDM_Odm->DefaultOfdmIndex;
		pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[p] = 0;
		pDM_Odm->RFCalibrateInfo.DeltaPowerIndexLast[p] = 0;
		pDM_Odm->RFCalibrateInfo.PowerIndexOffset[p] = 0;
	पूर्ण

पूर्ण

व्योम ODM_TXPowerTrackingCheck(काष्ठा dm_odm_t *pDM_Odm)
अणु
	काष्ठा adapter *Adapter = pDM_Odm->Adapter;

	अगर (!(pDM_Odm->SupportAbility & ODM_RF_TX_PWR_TRACK))
		वापस;

	अगर (!pDM_Odm->RFCalibrateInfo.TM_Trigger) अणु /* at least delay 1 sec */
		PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_T_METER_NEW, (BIT17 | BIT16), 0x03);

		pDM_Odm->RFCalibrateInfo.TM_Trigger = 1;
		वापस;
	पूर्ण अन्यथा अणु
		ODM_TXPowerTrackingCallback_ThermalMeter(Adapter);
		pDM_Odm->RFCalibrateInfo.TM_Trigger = 0;
	पूर्ण
पूर्ण

/*  */
/* 3 Export Interface */
/*  */

/*  */
/*  2011/09/21 MH Add to describe dअगरferent team necessary resource allocate?? */
/*  */
व्योम ODM_DMInit(काष्ठा dm_odm_t *pDM_Odm)
अणु

	odm_CommonInfoSelfInit(pDM_Odm);
	odm_CmnInfoInit_Debug(pDM_Odm);
	odm_DIGInit(pDM_Odm);
	odm_NHMCounterStatisticsInit(pDM_Odm);
	odm_AdaptivityInit(pDM_Odm);
	odm_RateAdaptiveMaskInit(pDM_Odm);
	ODM_CfoTrackingInit(pDM_Odm);
	ODM_EdcaTurboInit(pDM_Odm);
	odm_RSSIMonitorInit(pDM_Odm);
	odm_TXPowerTrackingInit(pDM_Odm);

	ODM_ClearTxPowerTrackingState(pDM_Odm);

	अगर (*(pDM_Odm->mp_mode) != 1)
		odm_PathDiversityInit(pDM_Odm);

	odm_DynamicBBPowerSavingInit(pDM_Odm);
	odm_DynamicTxPowerInit(pDM_Odm);

	odm_SwAntDetectInit(pDM_Odm);
पूर्ण

/*  */
/*  2011/09/20 MH This is the entry poपूर्णांकer क्रम all team to execute HW out source DM. */
/*  You can not add any dummy function here, be care, you can only use DM काष्ठाure */
/*  to perक्रमm any new ODM_DM. */
/*  */
व्योम ODM_DMWatchकरोg(काष्ठा dm_odm_t *pDM_Odm)
अणु
	odm_CommonInfoSelfUpdate(pDM_Odm);
	odm_BasicDbgMessage(pDM_Odm);
	odm_FalseAlarmCounterStatistics(pDM_Odm);
	odm_NHMCounterStatistics(pDM_Odm);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): RSSI = 0x%x\n", pDM_Odm->RSSI_Min));

	odm_RSSIMonitorCheck(pDM_Odm);

	/* For CE Platक्रमm(SPRD or Tablet) */
	/* 8723A or 8189ES platक्रमm */
	/* NeilChen--2012--08--24-- */
	/* Fix Leave LPS issue */
	अगर ((adapter_to_pwrctl(pDM_Odm->Adapter)->pwr_mode != PS_MODE_ACTIVE) /*  in LPS mode */
		/*  */
		/* (pDM_Odm->SupportICType & (ODM_RTL8723A))|| */
		/* (pDM_Odm->SupportICType & (ODM_RTL8188E) &&(&&(((pDM_Odm->SupportInterface  == ODM_ITRF_SDIO))) */
		/*  */
	) अणु
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("----Step1: odm_DIG is in LPS mode\n"));
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("---Step2: 8723AS is in LPS mode\n"));
			odm_DIGbyRSSI_LPS(pDM_Odm);
	पूर्ण अन्यथा
		odm_DIG(pDM_Odm);

	अणु
		काष्ठा dig_t *pDM_DigTable = &pDM_Odm->DM_DigTable;

		odm_Adaptivity(pDM_Odm, pDM_DigTable->CurIGValue);
	पूर्ण
	odm_CCKPacketDetectionThresh(pDM_Odm);

	अगर (*(pDM_Odm->pbPowerSaving) == true)
		वापस;


	odm_RefreshRateAdaptiveMask(pDM_Odm);
	odm_EdcaTurboCheck(pDM_Odm);
	odm_PathDiversity(pDM_Odm);
	ODM_CfoTracking(pDM_Odm);

	ODM_TXPowerTrackingCheck(pDM_Odm);

	/* odm_EdcaTurboCheck(pDM_Odm); */

	/* 2010.05.30 LukeLee: For CE platक्रमm, files in IC subfolders may not be included to be compiled, */
	/*  so compile flags must be left here to prevent from compile errors */
	pDM_Odm->PhyDbgInfo.NumQryBeaconPkt = 0;
पूर्ण


/*  */
/*  Init /.. Fixed HW value. Only init समय. */
/*  */
व्योम ODM_CmnInfoInit(काष्ठा dm_odm_t *pDM_Odm, क्रमागत odm_cmninfo_e CmnInfo, u32 Value)
अणु
	/*  */
	/*  This section is used क्रम init value */
	/*  */
	चयन (CmnInfo) अणु
	/*  */
	/*  Fixed ODM value. */
	/*  */
	हाल ODM_CMNINFO_ABILITY:
		pDM_Odm->SupportAbility = (u32)Value;
		अवरोध;

	हाल ODM_CMNINFO_RF_TYPE:
		pDM_Odm->RFType = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_PLATFORM:
		pDM_Odm->SupportPlatक्रमm = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_INTERFACE:
		pDM_Odm->SupportInterface = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_MP_TEST_CHIP:
		pDM_Odm->bIsMPChip = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_IC_TYPE:
		pDM_Odm->SupportICType = Value;
		अवरोध;

	हाल ODM_CMNINFO_CUT_VER:
		pDM_Odm->CutVersion = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_FAB_VER:
		pDM_Odm->FabVersion = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_RFE_TYPE:
		pDM_Odm->RFEType = (u8)Value;
		अवरोध;

	हाल    ODM_CMNINFO_RF_ANTENNA_TYPE:
		pDM_Odm->AntDivType = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_BOARD_TYPE:
		pDM_Odm->BoardType = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_PACKAGE_TYPE:
		pDM_Odm->PackageType = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_EXT_LNA:
		pDM_Odm->ExtLNA = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_5G_EXT_LNA:
		pDM_Odm->ExtLNA5G = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_EXT_PA:
		pDM_Odm->ExtPA = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_5G_EXT_PA:
		pDM_Odm->ExtPA5G = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_GPA:
		pDM_Odm->TypeGPA = (क्रमागत odm_type_gpa_e)Value;
		अवरोध;
	हाल ODM_CMNINFO_APA:
		pDM_Odm->TypeAPA = (क्रमागत odm_type_apa_e)Value;
		अवरोध;
	हाल ODM_CMNINFO_GLNA:
		pDM_Odm->TypeGLNA = (क्रमागत odm_type_glna_e)Value;
		अवरोध;
	हाल ODM_CMNINFO_ALNA:
		pDM_Odm->TypeALNA = (क्रमागत odm_type_alna_e)Value;
		अवरोध;

	हाल ODM_CMNINFO_EXT_TRSW:
		pDM_Odm->ExtTRSW = (u8)Value;
		अवरोध;
	हाल ODM_CMNINFO_PATCH_ID:
		pDM_Odm->PatchID = (u8)Value;
		अवरोध;
	हाल ODM_CMNINFO_BINHCT_TEST:
		pDM_Odm->bInHctTest = (bool)Value;
		अवरोध;
	हाल ODM_CMNINFO_BWIFI_TEST:
		pDM_Odm->bWIFITest = (bool)Value;
		अवरोध;

	हाल ODM_CMNINFO_SMART_CONCURRENT:
		pDM_Odm->bDualMacSmartConcurrent = (bool)Value;
		अवरोध;

	/* To हटाओ the compiler warning, must add an empty शेष statement to handle the other values. */
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

पूर्ण


व्योम ODM_CmnInfoHook(काष्ठा dm_odm_t *pDM_Odm, क्रमागत odm_cmninfo_e CmnInfo, व्योम *pValue)
अणु
	/*  */
	/*  Hook call by reference poपूर्णांकer. */
	/*  */
	चयन (CmnInfo) अणु
	/*  */
	/*  Dynamic call by reference poपूर्णांकer. */
	/*  */
	हाल ODM_CMNINFO_MAC_PHY_MODE:
		pDM_Odm->pMacPhyMode = pValue;
		अवरोध;

	हाल ODM_CMNINFO_TX_UNI:
		pDM_Odm->pNumTxBytesUnicast = pValue;
		अवरोध;

	हाल ODM_CMNINFO_RX_UNI:
		pDM_Odm->pNumRxBytesUnicast = pValue;
		अवरोध;

	हाल ODM_CMNINFO_WM_MODE:
		pDM_Odm->pwirelessmode = pValue;
		अवरोध;

	हाल ODM_CMNINFO_BAND:
		pDM_Odm->pBandType = pValue;
		अवरोध;

	हाल ODM_CMNINFO_SEC_CHNL_OFFSET:
		pDM_Odm->pSecChOffset = pValue;
		अवरोध;

	हाल ODM_CMNINFO_SEC_MODE:
		pDM_Odm->pSecurity = pValue;
		अवरोध;

	हाल ODM_CMNINFO_BW:
		pDM_Odm->pBandWidth = pValue;
		अवरोध;

	हाल ODM_CMNINFO_CHNL:
		pDM_Odm->pChannel = pValue;
		अवरोध;

	हाल ODM_CMNINFO_DMSP_GET_VALUE:
		pDM_Odm->pbGetValueFromOtherMac = pValue;
		अवरोध;

	हाल ODM_CMNINFO_BUDDY_ADAPTOR:
		pDM_Odm->pBuddyAdapter = pValue;
		अवरोध;

	हाल ODM_CMNINFO_DMSP_IS_MASTER:
		pDM_Odm->pbMasterOfDMSP = pValue;
		अवरोध;

	हाल ODM_CMNINFO_SCAN:
		pDM_Odm->pbScanInProcess = pValue;
		अवरोध;

	हाल ODM_CMNINFO_POWER_SAVING:
		pDM_Odm->pbPowerSaving = pValue;
		अवरोध;

	हाल ODM_CMNINFO_ONE_PATH_CCA:
		pDM_Odm->pOnePathCCA = pValue;
		अवरोध;

	हाल ODM_CMNINFO_DRV_STOP:
		pDM_Odm->pbDriverStopped =  pValue;
		अवरोध;

	हाल ODM_CMNINFO_PNP_IN:
		pDM_Odm->pbDriverIsGoingToPnpSetPowerSleep =  pValue;
		अवरोध;

	हाल ODM_CMNINFO_INIT_ON:
		pDM_Odm->pinit_adpt_in_progress =  pValue;
		अवरोध;

	हाल ODM_CMNINFO_ANT_TEST:
		pDM_Odm->pAntennaTest =  pValue;
		अवरोध;

	हाल ODM_CMNINFO_NET_CLOSED:
		pDM_Odm->pbNet_बंदd = pValue;
		अवरोध;

	हाल ODM_CMNINFO_FORCED_RATE:
		pDM_Odm->pForcedDataRate = pValue;
		अवरोध;

	हाल ODM_CMNINFO_FORCED_IGI_LB:
		pDM_Odm->pu1ForcedIgiLb = pValue;
		अवरोध;

	हाल ODM_CMNINFO_MP_MODE:
		pDM_Odm->mp_mode = pValue;
		अवरोध;

	/* हाल ODM_CMNINFO_RTSTA_AID: */
	/* pDM_Odm->pAidMap =  (u8 *)pValue; */
	/* अवरोध; */

	/* हाल ODM_CMNINFO_BT_COEXIST: */
	/* pDM_Odm->BTCoexist = (bool *)pValue; */

	/* हाल ODM_CMNINFO_STA_STATUS: */
	/* pDM_Odm->pODM_StaInfo[] = (PSTA_INFO_T)pValue; */
	/* अवरोध; */

	/* हाल ODM_CMNINFO_PHY_STATUS: */
	/* pDM_Odm->pPhyInfo = (ODM_PHY_INFO *)pValue; */
	/* अवरोध; */

	/* हाल ODM_CMNINFO_MAC_STATUS: */
	/* pDM_Odm->pMacInfo = (काष्ठा odm_mac_status_info *)pValue; */
	/* अवरोध; */
	/* To हटाओ the compiler warning, must add an empty शेष statement to handle the other values. */
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

पूर्ण


व्योम ODM_CmnInfoPtrArrayHook(
	काष्ठा dm_odm_t *pDM_Odm,
	क्रमागत odm_cmninfo_e CmnInfo,
	u16 Index,
	व्योम *pValue
)
अणु
	/*  */
	/*  Hook call by reference poपूर्णांकer. */
	/*  */
	चयन (CmnInfo) अणु
	/*  */
	/*  Dynamic call by reference poपूर्णांकer. */
	/*  */
	हाल ODM_CMNINFO_STA_STATUS:
		pDM_Odm->pODM_StaInfo[Index] = (PSTA_INFO_T)pValue;
		अवरोध;
	/* To हटाओ the compiler warning, must add an empty शेष statement to handle the other values. */
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

पूर्ण


/*  */
/*  Update Band/CHannel/.. The values are dynamic but non-per-packet. */
/*  */
व्योम ODM_CmnInfoUpdate(काष्ठा dm_odm_t *pDM_Odm, u32 CmnInfo, u64 Value)
अणु
	/*  */
	/*  This init variable may be changed in run समय. */
	/*  */
	चयन (CmnInfo) अणु
	हाल ODM_CMNINFO_LINK_IN_PROGRESS:
		pDM_Odm->bLinkInProcess = (bool)Value;
		अवरोध;

	हाल ODM_CMNINFO_ABILITY:
		pDM_Odm->SupportAbility = (u32)Value;
		अवरोध;

	हाल ODM_CMNINFO_RF_TYPE:
		pDM_Odm->RFType = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_WIFI_सूचीECT:
		pDM_Odm->bWIFI_Direct = (bool)Value;
		अवरोध;

	हाल ODM_CMNINFO_WIFI_DISPLAY:
		pDM_Odm->bWIFI_Display = (bool)Value;
		अवरोध;

	हाल ODM_CMNINFO_LINK:
		pDM_Odm->bLinked = (bool)Value;
		अवरोध;

	हाल ODM_CMNINFO_STATION_STATE:
		pDM_Odm->bsta_state = (bool)Value;
		अवरोध;

	हाल ODM_CMNINFO_RSSI_MIN:
		pDM_Odm->RSSI_Min = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_DBG_COMP:
		pDM_Odm->DebugComponents = Value;
		अवरोध;

	हाल ODM_CMNINFO_DBG_LEVEL:
		pDM_Odm->DebugLevel = (u32)Value;
		अवरोध;
	हाल ODM_CMNINFO_RA_THRESHOLD_HIGH:
		pDM_Odm->RateAdaptive.HighRSSIThresh = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_RA_THRESHOLD_LOW:
		pDM_Odm->RateAdaptive.LowRSSIThresh = (u8)Value;
		अवरोध;
	/*  The following is क्रम BT HS mode and BT coexist mechanism. */
	हाल ODM_CMNINFO_BT_ENABLED:
		pDM_Odm->bBtEnabled = (bool)Value;
		अवरोध;

	हाल ODM_CMNINFO_BT_HS_CONNECT_PROCESS:
		pDM_Odm->bBtConnectProcess = (bool)Value;
		अवरोध;

	हाल ODM_CMNINFO_BT_HS_RSSI:
		pDM_Odm->btHsRssi = (u8)Value;
		अवरोध;

	हाल ODM_CMNINFO_BT_OPERATION:
		pDM_Odm->bBtHsOperation = (bool)Value;
		अवरोध;

	हाल ODM_CMNINFO_BT_LIMITED_DIG:
		pDM_Odm->bBtLimitedDig = (bool)Value;
		अवरोध;

	हाल ODM_CMNINFO_BT_DISABLE_EDCA:
		pDM_Odm->bBtDisableEdcaTurbo = (bool)Value;
		अवरोध;

/*
	हाल	ODM_CMNINFO_OP_MODE:
		pDM_Odm->OPMode = (u8)Value;
		अवरोध;

	हाल	ODM_CMNINFO_WM_MODE:
		pDM_Odm->WirelessMode = (u8)Value;
		अवरोध;

	हाल	ODM_CMNINFO_BAND:
		pDM_Odm->BandType = (u8)Value;
		अवरोध;

	हाल	ODM_CMNINFO_SEC_CHNL_OFFSET:
		pDM_Odm->SecChOffset = (u8)Value;
		अवरोध;

	हाल	ODM_CMNINFO_SEC_MODE:
		pDM_Odm->Security = (u8)Value;
		अवरोध;

	हाल	ODM_CMNINFO_BW:
		pDM_Odm->BandWidth = (u8)Value;
		अवरोध;

	हाल	ODM_CMNINFO_CHNL:
		pDM_Odm->Channel = (u8)Value;
		अवरोध;
*/
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण


पूर्ण

/* 3 ============================================================ */
/* 3 DIG */
/* 3 ============================================================ */
/*-----------------------------------------------------------------------------
 * Function:	odm_DIGInit()
 *
 * Overview:	Set DIG scheme init value.
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *When		Who		Remark
 *
 *---------------------------------------------------------------------------
 */

/* Remove DIG by yuchen */

/* Remove DIG and FA check by Yu Chen */

/* 3 ============================================================ */
/* 3 BB Power Save */
/* 3 ============================================================ */

/* Remove BB घातer saving by Yuchen */

/* 3 ============================================================ */
/* 3 Dynamic Tx Power */
/* 3 ============================================================ */

/* Remove BY YuChen */

