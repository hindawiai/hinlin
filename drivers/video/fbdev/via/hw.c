<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#समावेश <linux/via-core.h>
#समावेश "global.h"
#समावेश "via_clock.h"

अटल काष्ठा pll_limit cle266_pll_limits[] = अणु
	अणु19, 19, 4, 0पूर्ण,
	अणु26, 102, 5, 0पूर्ण,
	अणु53, 112, 6, 0पूर्ण,
	अणु41, 100, 7, 0पूर्ण,
	अणु83, 108, 8, 0पूर्ण,
	अणु87, 118, 9, 0पूर्ण,
	अणु95, 115, 12, 0पूर्ण,
	अणु108, 108, 13, 0पूर्ण,
	अणु83, 83, 17, 0पूर्ण,
	अणु67, 98, 20, 0पूर्ण,
	अणु121, 121, 24, 0पूर्ण,
	अणु99, 99, 29, 0पूर्ण,
	अणु33, 33, 3, 1पूर्ण,
	अणु15, 23, 4, 1पूर्ण,
	अणु37, 121, 5, 1पूर्ण,
	अणु82, 82, 6, 1पूर्ण,
	अणु31, 84, 7, 1पूर्ण,
	अणु83, 83, 8, 1पूर्ण,
	अणु76, 127, 9, 1पूर्ण,
	अणु33, 121, 4, 2पूर्ण,
	अणु91, 118, 5, 2पूर्ण,
	अणु83, 109, 6, 2पूर्ण,
	अणु90, 90, 7, 2पूर्ण,
	अणु93, 93, 2, 3पूर्ण,
	अणु53, 53, 3, 3पूर्ण,
	अणु73, 117, 4, 3पूर्ण,
	अणु101, 127, 5, 3पूर्ण,
	अणु99, 99, 7, 3पूर्ण
पूर्ण;

अटल काष्ठा pll_limit k800_pll_limits[] = अणु
	अणु22, 22, 2, 0पूर्ण,
	अणु28, 28, 3, 0पूर्ण,
	अणु81, 112, 3, 1पूर्ण,
	अणु86, 166, 4, 1पूर्ण,
	अणु109, 153, 5, 1पूर्ण,
	अणु66, 116, 3, 2पूर्ण,
	अणु93, 137, 4, 2पूर्ण,
	अणु117, 208, 5, 2पूर्ण,
	अणु30, 30, 2, 3पूर्ण,
	अणु69, 125, 3, 3पूर्ण,
	अणु89, 161, 4, 3पूर्ण,
	अणु121, 208, 5, 3पूर्ण,
	अणु66, 66, 2, 4पूर्ण,
	अणु85, 85, 3, 4पूर्ण,
	अणु141, 161, 4, 4पूर्ण,
	अणु177, 177, 5, 4पूर्ण
पूर्ण;

अटल काष्ठा pll_limit cx700_pll_limits[] = अणु
	अणु98, 98, 3, 1पूर्ण,
	अणु86, 86, 4, 1पूर्ण,
	अणु109, 208, 5, 1पूर्ण,
	अणु68, 68, 2, 2पूर्ण,
	अणु95, 116, 3, 2पूर्ण,
	अणु93, 166, 4, 2पूर्ण,
	अणु110, 206, 5, 2पूर्ण,
	अणु174, 174, 7, 2पूर्ण,
	अणु82, 109, 3, 3पूर्ण,
	अणु117, 161, 4, 3पूर्ण,
	अणु112, 208, 5, 3पूर्ण,
	अणु141, 202, 5, 4पूर्ण
पूर्ण;

अटल काष्ठा pll_limit vx855_pll_limits[] = अणु
	अणु86, 86, 4, 1पूर्ण,
	अणु108, 208, 5, 1पूर्ण,
	अणु110, 208, 5, 2पूर्ण,
	अणु83, 112, 3, 3पूर्ण,
	अणु103, 161, 4, 3पूर्ण,
	अणु112, 209, 5, 3पूर्ण,
	अणु142, 161, 4, 4पूर्ण,
	अणु141, 176, 5, 4पूर्ण
पूर्ण;

/* according to VIA Technologies these values are based on experiment */
अटल काष्ठा io_reg scaling_parameters[] = अणु
	अणुVIACR, CR7A, 0xFF, 0x01पूर्ण,	/* LCD Scaling Parameter 1 */
	अणुVIACR, CR7B, 0xFF, 0x02पूर्ण,	/* LCD Scaling Parameter 2 */
	अणुVIACR, CR7C, 0xFF, 0x03पूर्ण,	/* LCD Scaling Parameter 3 */
	अणुVIACR, CR7D, 0xFF, 0x04पूर्ण,	/* LCD Scaling Parameter 4 */
	अणुVIACR, CR7E, 0xFF, 0x07पूर्ण,	/* LCD Scaling Parameter 5 */
	अणुVIACR, CR7F, 0xFF, 0x0Aपूर्ण,	/* LCD Scaling Parameter 6 */
	अणुVIACR, CR80, 0xFF, 0x0Dपूर्ण,	/* LCD Scaling Parameter 7 */
	अणुVIACR, CR81, 0xFF, 0x13पूर्ण,	/* LCD Scaling Parameter 8 */
	अणुVIACR, CR82, 0xFF, 0x16पूर्ण,	/* LCD Scaling Parameter 9 */
	अणुVIACR, CR83, 0xFF, 0x19पूर्ण,	/* LCD Scaling Parameter 10 */
	अणुVIACR, CR84, 0xFF, 0x1Cपूर्ण,	/* LCD Scaling Parameter 11 */
	अणुVIACR, CR85, 0xFF, 0x1Dपूर्ण,	/* LCD Scaling Parameter 12 */
	अणुVIACR, CR86, 0xFF, 0x1Eपूर्ण,	/* LCD Scaling Parameter 13 */
	अणुVIACR, CR87, 0xFF, 0x1Fपूर्ण,	/* LCD Scaling Parameter 14 */
पूर्ण;

अटल काष्ठा io_reg common_vga[] = अणु
	अणुVIACR, CR07, 0x10, 0x10पूर्ण, /* [0] vertical total (bit 8)
					[1] vertical display end (bit 8)
					[2] vertical retrace start (bit 8)
					[3] start vertical blanking (bit 8)
					[4] line compare (bit 8)
					[5] vertical total (bit 9)
					[6] vertical display end (bit 9)
					[7] vertical retrace start (bit 9) */
	अणुVIACR, CR08, 0xFF, 0x00पूर्ण, /* [0-4] preset row scan
					[5-6] byte panning */
	अणुVIACR, CR09, 0xDF, 0x40पूर्ण, /* [0-4] max scan line
					[5] start vertical blanking (bit 9)
					[6] line compare (bit 9)
					[7] scan करोubling */
	अणुVIACR, CR0A, 0xFF, 0x1Eपूर्ण, /* [0-4] cursor start
					[5] cursor disable */
	अणुVIACR, CR0B, 0xFF, 0x00पूर्ण, /* [0-4] cursor end
					[5-6] cursor skew */
	अणुVIACR, CR0E, 0xFF, 0x00पूर्ण, /* [0-7] cursor location (high) */
	अणुVIACR, CR0F, 0xFF, 0x00पूर्ण, /* [0-7] cursor location (low) */
	अणुVIACR, CR11, 0xF0, 0x80पूर्ण, /* [0-3] vertical retrace end
					[6] memory refresh bandwidth
					[7] CRTC रेजिस्टर protect enable */
	अणुVIACR, CR14, 0xFF, 0x00पूर्ण, /* [0-4] underline location
					[5] भागide memory address घड़ी by 4
					[6] द्विगुन word addressing */
	अणुVIACR, CR17, 0xFF, 0x63पूर्ण, /* [0-1] mapping of display address 13-14
					[2] भागide scan line घड़ी by 2
					[3] भागide memory address घड़ी by 2
					[5] address wrap
					[6] byte mode select
					[7] sync enable */
	अणुVIACR, CR18, 0xFF, 0xFFपूर्ण, /* [0-7] line compare */
पूर्ण;

अटल काष्ठा fअगरo_depth_select display_fअगरo_depth_reg = अणु
	/* IGA1 FIFO Depth_Select */
	अणुIGA1_FIFO_DEPTH_SELECT_REG_NUM, अणुअणुSR17, 0, 7पूर्ण पूर्ण पूर्ण,
	/* IGA2 FIFO Depth_Select */
	अणुIGA2_FIFO_DEPTH_SELECT_REG_NUM,
	 अणुअणुCR68, 4, 7पूर्ण, अणुCR94, 7, 7पूर्ण, अणुCR95, 7, 7पूर्ण पूर्ण पूर्ण
पूर्ण;

अटल काष्ठा fअगरo_threshold_select fअगरo_threshold_select_reg = अणु
	/* IGA1 FIFO Threshold Select */
	अणुIGA1_FIFO_THRESHOLD_REG_NUM, अणुअणुSR16, 0, 5पूर्ण, अणुSR16, 7, 7पूर्ण पूर्ण पूर्ण,
	/* IGA2 FIFO Threshold Select */
	अणुIGA2_FIFO_THRESHOLD_REG_NUM, अणुअणुCR68, 0, 3पूर्ण, अणुCR95, 4, 6पूर्ण पूर्ण पूर्ण
पूर्ण;

अटल काष्ठा fअगरo_high_threshold_select fअगरo_high_threshold_select_reg = अणु
	/* IGA1 FIFO High Threshold Select */
	अणुIGA1_FIFO_HIGH_THRESHOLD_REG_NUM, अणुअणुSR18, 0, 5पूर्ण, अणुSR18, 7, 7पूर्ण पूर्ण पूर्ण,
	/* IGA2 FIFO High Threshold Select */
	अणुIGA2_FIFO_HIGH_THRESHOLD_REG_NUM, अणुअणुCR92, 0, 3पूर्ण, अणुCR95, 0, 2पूर्ण पूर्ण पूर्ण
पूर्ण;

अटल काष्ठा display_queue_expire_num display_queue_expire_num_reg = अणु
	/* IGA1 Display Queue Expire Num */
	अणुIGA1_DISPLAY_QUEUE_EXPIRE_NUM_REG_NUM, अणुअणुSR22, 0, 4पूर्ण पूर्ण पूर्ण,
	/* IGA2 Display Queue Expire Num */
	अणुIGA2_DISPLAY_QUEUE_EXPIRE_NUM_REG_NUM, अणुअणुCR94, 0, 6पूर्ण पूर्ण पूर्ण
पूर्ण;

/* Definition Fetch Count Registers*/
अटल काष्ठा fetch_count fetch_count_reg = अणु
	/* IGA1 Fetch Count Register */
	अणुIGA1_FETCH_COUNT_REG_NUM, अणुअणुSR1C, 0, 7पूर्ण, अणुSR1D, 0, 1पूर्ण पूर्ण पूर्ण,
	/* IGA2 Fetch Count Register */
	अणुIGA2_FETCH_COUNT_REG_NUM, अणुअणुCR65, 0, 7पूर्ण, अणुCR67, 2, 3पूर्ण पूर्ण पूर्ण
पूर्ण;

अटल काष्ठा rgbLUT palLUT_table[] = अणु
	/* अणुR,G,Bपूर्ण */
	/* Index 0x00~0x03 */
	अणु0x00, 0x00, 0x00पूर्ण, अणु0x00, 0x00, 0x2Aपूर्ण, अणु0x00, 0x2A, 0x00पूर्ण, अणु0x00,
								     0x2A,
								     0x2Aपूर्ण,
	/* Index 0x04~0x07 */
	अणु0x2A, 0x00, 0x00पूर्ण, अणु0x2A, 0x00, 0x2Aपूर्ण, अणु0x2A, 0x15, 0x00पूर्ण, अणु0x2A,
								     0x2A,
								     0x2Aपूर्ण,
	/* Index 0x08~0x0B */
	अणु0x15, 0x15, 0x15पूर्ण, अणु0x15, 0x15, 0x3Fपूर्ण, अणु0x15, 0x3F, 0x15पूर्ण, अणु0x15,
								     0x3F,
								     0x3Fपूर्ण,
	/* Index 0x0C~0x0F */
	अणु0x3F, 0x15, 0x15पूर्ण, अणु0x3F, 0x15, 0x3Fपूर्ण, अणु0x3F, 0x3F, 0x15पूर्ण, अणु0x3F,
								     0x3F,
								     0x3Fपूर्ण,
	/* Index 0x10~0x13 */
	अणु0x00, 0x00, 0x00पूर्ण, अणु0x05, 0x05, 0x05पूर्ण, अणु0x08, 0x08, 0x08पूर्ण, अणु0x0B,
								     0x0B,
								     0x0Bपूर्ण,
	/* Index 0x14~0x17 */
	अणु0x0E, 0x0E, 0x0Eपूर्ण, अणु0x11, 0x11, 0x11पूर्ण, अणु0x14, 0x14, 0x14पूर्ण, अणु0x18,
								     0x18,
								     0x18पूर्ण,
	/* Index 0x18~0x1B */
	अणु0x1C, 0x1C, 0x1Cपूर्ण, अणु0x20, 0x20, 0x20पूर्ण, अणु0x24, 0x24, 0x24पूर्ण, अणु0x28,
								     0x28,
								     0x28पूर्ण,
	/* Index 0x1C~0x1F */
	अणु0x2D, 0x2D, 0x2Dपूर्ण, अणु0x32, 0x32, 0x32पूर्ण, अणु0x38, 0x38, 0x38पूर्ण, अणु0x3F,
								     0x3F,
								     0x3Fपूर्ण,
	/* Index 0x20~0x23 */
	अणु0x00, 0x00, 0x3Fपूर्ण, अणु0x10, 0x00, 0x3Fपूर्ण, अणु0x1F, 0x00, 0x3Fपूर्ण, अणु0x2F,
								     0x00,
								     0x3Fपूर्ण,
	/* Index 0x24~0x27 */
	अणु0x3F, 0x00, 0x3Fपूर्ण, अणु0x3F, 0x00, 0x2Fपूर्ण, अणु0x3F, 0x00, 0x1Fपूर्ण, अणु0x3F,
								     0x00,
								     0x10पूर्ण,
	/* Index 0x28~0x2B */
	अणु0x3F, 0x00, 0x00पूर्ण, अणु0x3F, 0x10, 0x00पूर्ण, अणु0x3F, 0x1F, 0x00पूर्ण, अणु0x3F,
								     0x2F,
								     0x00पूर्ण,
	/* Index 0x2C~0x2F */
	अणु0x3F, 0x3F, 0x00पूर्ण, अणु0x2F, 0x3F, 0x00पूर्ण, अणु0x1F, 0x3F, 0x00पूर्ण, अणु0x10,
								     0x3F,
								     0x00पूर्ण,
	/* Index 0x30~0x33 */
	अणु0x00, 0x3F, 0x00पूर्ण, अणु0x00, 0x3F, 0x10पूर्ण, अणु0x00, 0x3F, 0x1Fपूर्ण, अणु0x00,
								     0x3F,
								     0x2Fपूर्ण,
	/* Index 0x34~0x37 */
	अणु0x00, 0x3F, 0x3Fपूर्ण, अणु0x00, 0x2F, 0x3Fपूर्ण, अणु0x00, 0x1F, 0x3Fपूर्ण, अणु0x00,
								     0x10,
								     0x3Fपूर्ण,
	/* Index 0x38~0x3B */
	अणु0x1F, 0x1F, 0x3Fपूर्ण, अणु0x27, 0x1F, 0x3Fपूर्ण, अणु0x2F, 0x1F, 0x3Fपूर्ण, अणु0x37,
								     0x1F,
								     0x3Fपूर्ण,
	/* Index 0x3C~0x3F */
	अणु0x3F, 0x1F, 0x3Fपूर्ण, अणु0x3F, 0x1F, 0x37पूर्ण, अणु0x3F, 0x1F, 0x2Fपूर्ण, अणु0x3F,
								     0x1F,
								     0x27पूर्ण,
	/* Index 0x40~0x43 */
	अणु0x3F, 0x1F, 0x1Fपूर्ण, अणु0x3F, 0x27, 0x1Fपूर्ण, अणु0x3F, 0x2F, 0x1Fपूर्ण, अणु0x3F,
								     0x3F,
								     0x1Fपूर्ण,
	/* Index 0x44~0x47 */
	अणु0x3F, 0x3F, 0x1Fपूर्ण, अणु0x37, 0x3F, 0x1Fपूर्ण, अणु0x2F, 0x3F, 0x1Fपूर्ण, अणु0x27,
								     0x3F,
								     0x1Fपूर्ण,
	/* Index 0x48~0x4B */
	अणु0x1F, 0x3F, 0x1Fपूर्ण, अणु0x1F, 0x3F, 0x27पूर्ण, अणु0x1F, 0x3F, 0x2Fपूर्ण, अणु0x1F,
								     0x3F,
								     0x37पूर्ण,
	/* Index 0x4C~0x4F */
	अणु0x1F, 0x3F, 0x3Fपूर्ण, अणु0x1F, 0x37, 0x3Fपूर्ण, अणु0x1F, 0x2F, 0x3Fपूर्ण, अणु0x1F,
								     0x27,
								     0x3Fपूर्ण,
	/* Index 0x50~0x53 */
	अणु0x2D, 0x2D, 0x3Fपूर्ण, अणु0x31, 0x2D, 0x3Fपूर्ण, अणु0x36, 0x2D, 0x3Fपूर्ण, अणु0x3A,
								     0x2D,
								     0x3Fपूर्ण,
	/* Index 0x54~0x57 */
	अणु0x3F, 0x2D, 0x3Fपूर्ण, अणु0x3F, 0x2D, 0x3Aपूर्ण, अणु0x3F, 0x2D, 0x36पूर्ण, अणु0x3F,
								     0x2D,
								     0x31पूर्ण,
	/* Index 0x58~0x5B */
	अणु0x3F, 0x2D, 0x2Dपूर्ण, अणु0x3F, 0x31, 0x2Dपूर्ण, अणु0x3F, 0x36, 0x2Dपूर्ण, अणु0x3F,
								     0x3A,
								     0x2Dपूर्ण,
	/* Index 0x5C~0x5F */
	अणु0x3F, 0x3F, 0x2Dपूर्ण, अणु0x3A, 0x3F, 0x2Dपूर्ण, अणु0x36, 0x3F, 0x2Dपूर्ण, अणु0x31,
								     0x3F,
								     0x2Dपूर्ण,
	/* Index 0x60~0x63 */
	अणु0x2D, 0x3F, 0x2Dपूर्ण, अणु0x2D, 0x3F, 0x31पूर्ण, अणु0x2D, 0x3F, 0x36पूर्ण, अणु0x2D,
								     0x3F,
								     0x3Aपूर्ण,
	/* Index 0x64~0x67 */
	अणु0x2D, 0x3F, 0x3Fपूर्ण, अणु0x2D, 0x3A, 0x3Fपूर्ण, अणु0x2D, 0x36, 0x3Fपूर्ण, अणु0x2D,
								     0x31,
								     0x3Fपूर्ण,
	/* Index 0x68~0x6B */
	अणु0x00, 0x00, 0x1Cपूर्ण, अणु0x07, 0x00, 0x1Cपूर्ण, अणु0x0E, 0x00, 0x1Cपूर्ण, अणु0x15,
								     0x00,
								     0x1Cपूर्ण,
	/* Index 0x6C~0x6F */
	अणु0x1C, 0x00, 0x1Cपूर्ण, अणु0x1C, 0x00, 0x15पूर्ण, अणु0x1C, 0x00, 0x0Eपूर्ण, अणु0x1C,
								     0x00,
								     0x07पूर्ण,
	/* Index 0x70~0x73 */
	अणु0x1C, 0x00, 0x00पूर्ण, अणु0x1C, 0x07, 0x00पूर्ण, अणु0x1C, 0x0E, 0x00पूर्ण, अणु0x1C,
								     0x15,
								     0x00पूर्ण,
	/* Index 0x74~0x77 */
	अणु0x1C, 0x1C, 0x00पूर्ण, अणु0x15, 0x1C, 0x00पूर्ण, अणु0x0E, 0x1C, 0x00पूर्ण, अणु0x07,
								     0x1C,
								     0x00पूर्ण,
	/* Index 0x78~0x7B */
	अणु0x00, 0x1C, 0x00पूर्ण, अणु0x00, 0x1C, 0x07पूर्ण, अणु0x00, 0x1C, 0x0Eपूर्ण, अणु0x00,
								     0x1C,
								     0x15पूर्ण,
	/* Index 0x7C~0x7F */
	अणु0x00, 0x1C, 0x1Cपूर्ण, अणु0x00, 0x15, 0x1Cपूर्ण, अणु0x00, 0x0E, 0x1Cपूर्ण, अणु0x00,
								     0x07,
								     0x1Cपूर्ण,
	/* Index 0x80~0x83 */
	अणु0x0E, 0x0E, 0x1Cपूर्ण, अणु0x11, 0x0E, 0x1Cपूर्ण, अणु0x15, 0x0E, 0x1Cपूर्ण, अणु0x18,
								     0x0E,
								     0x1Cपूर्ण,
	/* Index 0x84~0x87 */
	अणु0x1C, 0x0E, 0x1Cपूर्ण, अणु0x1C, 0x0E, 0x18पूर्ण, अणु0x1C, 0x0E, 0x15पूर्ण, अणु0x1C,
								     0x0E,
								     0x11पूर्ण,
	/* Index 0x88~0x8B */
	अणु0x1C, 0x0E, 0x0Eपूर्ण, अणु0x1C, 0x11, 0x0Eपूर्ण, अणु0x1C, 0x15, 0x0Eपूर्ण, अणु0x1C,
								     0x18,
								     0x0Eपूर्ण,
	/* Index 0x8C~0x8F */
	अणु0x1C, 0x1C, 0x0Eपूर्ण, अणु0x18, 0x1C, 0x0Eपूर्ण, अणु0x15, 0x1C, 0x0Eपूर्ण, अणु0x11,
								     0x1C,
								     0x0Eपूर्ण,
	/* Index 0x90~0x93 */
	अणु0x0E, 0x1C, 0x0Eपूर्ण, अणु0x0E, 0x1C, 0x11पूर्ण, अणु0x0E, 0x1C, 0x15पूर्ण, अणु0x0E,
								     0x1C,
								     0x18पूर्ण,
	/* Index 0x94~0x97 */
	अणु0x0E, 0x1C, 0x1Cपूर्ण, अणु0x0E, 0x18, 0x1Cपूर्ण, अणु0x0E, 0x15, 0x1Cपूर्ण, अणु0x0E,
								     0x11,
								     0x1Cपूर्ण,
	/* Index 0x98~0x9B */
	अणु0x14, 0x14, 0x1Cपूर्ण, अणु0x16, 0x14, 0x1Cपूर्ण, अणु0x18, 0x14, 0x1Cपूर्ण, अणु0x1A,
								     0x14,
								     0x1Cपूर्ण,
	/* Index 0x9C~0x9F */
	अणु0x1C, 0x14, 0x1Cपूर्ण, अणु0x1C, 0x14, 0x1Aपूर्ण, अणु0x1C, 0x14, 0x18पूर्ण, अणु0x1C,
								     0x14,
								     0x16पूर्ण,
	/* Index 0xA0~0xA3 */
	अणु0x1C, 0x14, 0x14पूर्ण, अणु0x1C, 0x16, 0x14पूर्ण, अणु0x1C, 0x18, 0x14पूर्ण, अणु0x1C,
								     0x1A,
								     0x14पूर्ण,
	/* Index 0xA4~0xA7 */
	अणु0x1C, 0x1C, 0x14पूर्ण, अणु0x1A, 0x1C, 0x14पूर्ण, अणु0x18, 0x1C, 0x14पूर्ण, अणु0x16,
								     0x1C,
								     0x14पूर्ण,
	/* Index 0xA8~0xAB */
	अणु0x14, 0x1C, 0x14पूर्ण, अणु0x14, 0x1C, 0x16पूर्ण, अणु0x14, 0x1C, 0x18पूर्ण, अणु0x14,
								     0x1C,
								     0x1Aपूर्ण,
	/* Index 0xAC~0xAF */
	अणु0x14, 0x1C, 0x1Cपूर्ण, अणु0x14, 0x1A, 0x1Cपूर्ण, अणु0x14, 0x18, 0x1Cपूर्ण, अणु0x14,
								     0x16,
								     0x1Cपूर्ण,
	/* Index 0xB0~0xB3 */
	अणु0x00, 0x00, 0x10पूर्ण, अणु0x04, 0x00, 0x10पूर्ण, अणु0x08, 0x00, 0x10पूर्ण, अणु0x0C,
								     0x00,
								     0x10पूर्ण,
	/* Index 0xB4~0xB7 */
	अणु0x10, 0x00, 0x10पूर्ण, अणु0x10, 0x00, 0x0Cपूर्ण, अणु0x10, 0x00, 0x08पूर्ण, अणु0x10,
								     0x00,
								     0x04पूर्ण,
	/* Index 0xB8~0xBB */
	अणु0x10, 0x00, 0x00पूर्ण, अणु0x10, 0x04, 0x00पूर्ण, अणु0x10, 0x08, 0x00पूर्ण, अणु0x10,
								     0x0C,
								     0x00पूर्ण,
	/* Index 0xBC~0xBF */
	अणु0x10, 0x10, 0x00पूर्ण, अणु0x0C, 0x10, 0x00पूर्ण, अणु0x08, 0x10, 0x00पूर्ण, अणु0x04,
								     0x10,
								     0x00पूर्ण,
	/* Index 0xC0~0xC3 */
	अणु0x00, 0x10, 0x00पूर्ण, अणु0x00, 0x10, 0x04पूर्ण, अणु0x00, 0x10, 0x08पूर्ण, अणु0x00,
								     0x10,
								     0x0Cपूर्ण,
	/* Index 0xC4~0xC7 */
	अणु0x00, 0x10, 0x10पूर्ण, अणु0x00, 0x0C, 0x10पूर्ण, अणु0x00, 0x08, 0x10पूर्ण, अणु0x00,
								     0x04,
								     0x10पूर्ण,
	/* Index 0xC8~0xCB */
	अणु0x08, 0x08, 0x10पूर्ण, अणु0x0A, 0x08, 0x10पूर्ण, अणु0x0C, 0x08, 0x10पूर्ण, अणु0x0E,
								     0x08,
								     0x10पूर्ण,
	/* Index 0xCC~0xCF */
	अणु0x10, 0x08, 0x10पूर्ण, अणु0x10, 0x08, 0x0Eपूर्ण, अणु0x10, 0x08, 0x0Cपूर्ण, अणु0x10,
								     0x08,
								     0x0Aपूर्ण,
	/* Index 0xD0~0xD3 */
	अणु0x10, 0x08, 0x08पूर्ण, अणु0x10, 0x0A, 0x08पूर्ण, अणु0x10, 0x0C, 0x08पूर्ण, अणु0x10,
								     0x0E,
								     0x08पूर्ण,
	/* Index 0xD4~0xD7 */
	अणु0x10, 0x10, 0x08पूर्ण, अणु0x0E, 0x10, 0x08पूर्ण, अणु0x0C, 0x10, 0x08पूर्ण, अणु0x0A,
								     0x10,
								     0x08पूर्ण,
	/* Index 0xD8~0xDB */
	अणु0x08, 0x10, 0x08पूर्ण, अणु0x08, 0x10, 0x0Aपूर्ण, अणु0x08, 0x10, 0x0Cपूर्ण, अणु0x08,
								     0x10,
								     0x0Eपूर्ण,
	/* Index 0xDC~0xDF */
	अणु0x08, 0x10, 0x10पूर्ण, अणु0x08, 0x0E, 0x10पूर्ण, अणु0x08, 0x0C, 0x10पूर्ण, अणु0x08,
								     0x0A,
								     0x10पूर्ण,
	/* Index 0xE0~0xE3 */
	अणु0x0B, 0x0B, 0x10पूर्ण, अणु0x0C, 0x0B, 0x10पूर्ण, अणु0x0D, 0x0B, 0x10पूर्ण, अणु0x0F,
								     0x0B,
								     0x10पूर्ण,
	/* Index 0xE4~0xE7 */
	अणु0x10, 0x0B, 0x10पूर्ण, अणु0x10, 0x0B, 0x0Fपूर्ण, अणु0x10, 0x0B, 0x0Dपूर्ण, अणु0x10,
								     0x0B,
								     0x0Cपूर्ण,
	/* Index 0xE8~0xEB */
	अणु0x10, 0x0B, 0x0Bपूर्ण, अणु0x10, 0x0C, 0x0Bपूर्ण, अणु0x10, 0x0D, 0x0Bपूर्ण, अणु0x10,
								     0x0F,
								     0x0Bपूर्ण,
	/* Index 0xEC~0xEF */
	अणु0x10, 0x10, 0x0Bपूर्ण, अणु0x0F, 0x10, 0x0Bपूर्ण, अणु0x0D, 0x10, 0x0Bपूर्ण, अणु0x0C,
								     0x10,
								     0x0Bपूर्ण,
	/* Index 0xF0~0xF3 */
	अणु0x0B, 0x10, 0x0Bपूर्ण, अणु0x0B, 0x10, 0x0Cपूर्ण, अणु0x0B, 0x10, 0x0Dपूर्ण, अणु0x0B,
								     0x10,
								     0x0Fपूर्ण,
	/* Index 0xF4~0xF7 */
	अणु0x0B, 0x10, 0x10पूर्ण, अणु0x0B, 0x0F, 0x10पूर्ण, अणु0x0B, 0x0D, 0x10पूर्ण, अणु0x0B,
								     0x0C,
								     0x10पूर्ण,
	/* Index 0xF8~0xFB */
	अणु0x00, 0x00, 0x00पूर्ण, अणु0x00, 0x00, 0x00पूर्ण, अणु0x00, 0x00, 0x00पूर्ण, अणु0x00,
								     0x00,
								     0x00पूर्ण,
	/* Index 0xFC~0xFF */
	अणु0x00, 0x00, 0x00पूर्ण, अणु0x00, 0x00, 0x00पूर्ण, अणु0x00, 0x00, 0x00पूर्ण, अणु0x00,
								     0x00,
								     0x00पूर्ण
पूर्ण;

अटल काष्ठा via_device_mapping device_mapping[] = अणु
	अणुVIA_LDVP0, "LDVP0"पूर्ण,
	अणुVIA_LDVP1, "LDVP1"पूर्ण,
	अणुVIA_DVP0, "DVP0"पूर्ण,
	अणुVIA_CRT, "CRT"पूर्ण,
	अणुVIA_DVP1, "DVP1"पूर्ण,
	अणुVIA_LVDS1, "LVDS1"पूर्ण,
	अणुVIA_LVDS2, "LVDS2"पूर्ण
पूर्ण;

/* काष्ठाure with function poपूर्णांकers to support घड़ी control */
अटल काष्ठा via_घड़ी घड़ी;

अटल व्योम load_fix_bit_crtc_reg(व्योम);
अटल व्योम init_gfx_chip_info(पूर्णांक chip_type);
अटल व्योम init_पंचांगds_chip_info(व्योम);
अटल व्योम init_lvds_chip_info(व्योम);
अटल व्योम device_screen_off(व्योम);
अटल व्योम device_screen_on(व्योम);
अटल व्योम set_display_channel(व्योम);
अटल व्योम device_off(व्योम);
अटल व्योम device_on(व्योम);
अटल व्योम enable_second_display_channel(व्योम);
अटल व्योम disable_second_display_channel(व्योम);

व्योम viafb_lock_crt(व्योम)
अणु
	viafb_ग_लिखो_reg_mask(CR11, VIACR, BIT7, BIT7);
पूर्ण

व्योम viafb_unlock_crt(व्योम)
अणु
	viafb_ग_लिखो_reg_mask(CR11, VIACR, 0, BIT7);
	viafb_ग_लिखो_reg_mask(CR47, VIACR, 0, BIT0);
पूर्ण

अटल व्योम ग_लिखो_dac_reg(u8 index, u8 r, u8 g, u8 b)
अणु
	outb(index, LUT_INDEX_WRITE);
	outb(r, LUT_DATA);
	outb(g, LUT_DATA);
	outb(b, LUT_DATA);
पूर्ण

अटल u32 get_dvi_devices(पूर्णांक output_पूर्णांकerface)
अणु
	चयन (output_पूर्णांकerface) अणु
	हाल INTERFACE_DVP0:
		वापस VIA_DVP0 | VIA_LDVP0;

	हाल INTERFACE_DVP1:
		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)
			वापस VIA_LDVP1;
		अन्यथा
			वापस VIA_DVP1;

	हाल INTERFACE_DFP_HIGH:
		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)
			वापस 0;
		अन्यथा
			वापस VIA_LVDS2 | VIA_DVP0;

	हाल INTERFACE_DFP_LOW:
		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)
			वापस 0;
		अन्यथा
			वापस VIA_DVP1 | VIA_LVDS1;

	हाल INTERFACE_TMDS:
		वापस VIA_LVDS1;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 get_lcd_devices(पूर्णांक output_पूर्णांकerface)
अणु
	चयन (output_पूर्णांकerface) अणु
	हाल INTERFACE_DVP0:
		वापस VIA_DVP0;

	हाल INTERFACE_DVP1:
		वापस VIA_DVP1;

	हाल INTERFACE_DFP_HIGH:
		वापस VIA_LVDS2 | VIA_DVP0;

	हाल INTERFACE_DFP_LOW:
		वापस VIA_LVDS1 | VIA_DVP1;

	हाल INTERFACE_DFP:
		वापस VIA_LVDS1 | VIA_LVDS2;

	हाल INTERFACE_LVDS0:
	हाल INTERFACE_LVDS0LVDS1:
		वापस VIA_LVDS1;

	हाल INTERFACE_LVDS1:
		वापस VIA_LVDS2;
	पूर्ण

	वापस 0;
पूर्ण

/*Set IGA path क्रम each device*/
व्योम viafb_set_iga_path(व्योम)
अणु
	पूर्णांक crt_iga_path = 0;

	अगर (viafb_SAMM_ON == 1) अणु
		अगर (viafb_CRT_ON) अणु
			अगर (viafb_primary_dev == CRT_Device)
				crt_iga_path = IGA1;
			अन्यथा
				crt_iga_path = IGA2;
		पूर्ण

		अगर (viafb_DVI_ON) अणु
			अगर (viafb_primary_dev == DVI_Device)
				viaparinfo->पंचांगds_setting_info->iga_path = IGA1;
			अन्यथा
				viaparinfo->पंचांगds_setting_info->iga_path = IGA2;
		पूर्ण

		अगर (viafb_LCD_ON) अणु
			अगर (viafb_primary_dev == LCD_Device) अणु
				अगर (viafb_dual_fb &&
					(viaparinfo->chip_info->gfx_chip_name ==
					UNICHROME_CLE266)) अणु
					viaparinfo->
					lvds_setting_info->iga_path = IGA2;
					crt_iga_path = IGA1;
					viaparinfo->
					पंचांगds_setting_info->iga_path = IGA1;
				पूर्ण अन्यथा
					viaparinfo->
					lvds_setting_info->iga_path = IGA1;
			पूर्ण अन्यथा अणु
				viaparinfo->lvds_setting_info->iga_path = IGA2;
			पूर्ण
		पूर्ण
		अगर (viafb_LCD2_ON) अणु
			अगर (LCD2_Device == viafb_primary_dev)
				viaparinfo->lvds_setting_info2->iga_path = IGA1;
			अन्यथा
				viaparinfo->lvds_setting_info2->iga_path = IGA2;
		पूर्ण
	पूर्ण अन्यथा अणु
		viafb_SAMM_ON = 0;

		अगर (viafb_CRT_ON && viafb_LCD_ON) अणु
			crt_iga_path = IGA1;
			viaparinfo->lvds_setting_info->iga_path = IGA2;
		पूर्ण अन्यथा अगर (viafb_CRT_ON && viafb_DVI_ON) अणु
			crt_iga_path = IGA1;
			viaparinfo->पंचांगds_setting_info->iga_path = IGA2;
		पूर्ण अन्यथा अगर (viafb_LCD_ON && viafb_DVI_ON) अणु
			viaparinfo->पंचांगds_setting_info->iga_path = IGA1;
			viaparinfo->lvds_setting_info->iga_path = IGA2;
		पूर्ण अन्यथा अगर (viafb_LCD_ON && viafb_LCD2_ON) अणु
			viaparinfo->lvds_setting_info->iga_path = IGA2;
			viaparinfo->lvds_setting_info2->iga_path = IGA2;
		पूर्ण अन्यथा अगर (viafb_CRT_ON) अणु
			crt_iga_path = IGA1;
		पूर्ण अन्यथा अगर (viafb_LCD_ON) अणु
			viaparinfo->lvds_setting_info->iga_path = IGA2;
		पूर्ण अन्यथा अगर (viafb_DVI_ON) अणु
			viaparinfo->पंचांगds_setting_info->iga_path = IGA1;
		पूर्ण
	पूर्ण

	viaparinfo->shared->iga1_devices = 0;
	viaparinfo->shared->iga2_devices = 0;
	अगर (viafb_CRT_ON) अणु
		अगर (crt_iga_path == IGA1)
			viaparinfo->shared->iga1_devices |= VIA_CRT;
		अन्यथा
			viaparinfo->shared->iga2_devices |= VIA_CRT;
	पूर्ण

	अगर (viafb_DVI_ON) अणु
		अगर (viaparinfo->पंचांगds_setting_info->iga_path == IGA1)
			viaparinfo->shared->iga1_devices |= get_dvi_devices(
				viaparinfo->chip_info->
				पंचांगds_chip_info.output_पूर्णांकerface);
		अन्यथा
			viaparinfo->shared->iga2_devices |= get_dvi_devices(
				viaparinfo->chip_info->
				पंचांगds_chip_info.output_पूर्णांकerface);
	पूर्ण

	अगर (viafb_LCD_ON) अणु
		अगर (viaparinfo->lvds_setting_info->iga_path == IGA1)
			viaparinfo->shared->iga1_devices |= get_lcd_devices(
				viaparinfo->chip_info->
				lvds_chip_info.output_पूर्णांकerface);
		अन्यथा
			viaparinfo->shared->iga2_devices |= get_lcd_devices(
				viaparinfo->chip_info->
				lvds_chip_info.output_पूर्णांकerface);
	पूर्ण

	अगर (viafb_LCD2_ON) अणु
		अगर (viaparinfo->lvds_setting_info2->iga_path == IGA1)
			viaparinfo->shared->iga1_devices |= get_lcd_devices(
				viaparinfo->chip_info->
				lvds_chip_info2.output_पूर्णांकerface);
		अन्यथा
			viaparinfo->shared->iga2_devices |= get_lcd_devices(
				viaparinfo->chip_info->
				lvds_chip_info2.output_पूर्णांकerface);
	पूर्ण

	/* looks like the OLPC has its display wired to DVP1 and LVDS2 */
	अगर (machine_is_olpc())
		viaparinfo->shared->iga2_devices = VIA_DVP1 | VIA_LVDS2;
पूर्ण

अटल व्योम set_color_रेजिस्टर(u8 index, u8 red, u8 green, u8 blue)
अणु
	outb(0xFF, 0x3C6); /* bit mask of palette */
	outb(index, 0x3C8);
	outb(red, 0x3C9);
	outb(green, 0x3C9);
	outb(blue, 0x3C9);
पूर्ण

व्योम viafb_set_primary_color_रेजिस्टर(u8 index, u8 red, u8 green, u8 blue)
अणु
	viafb_ग_लिखो_reg_mask(0x1A, VIASR, 0x00, 0x01);
	set_color_रेजिस्टर(index, red, green, blue);
पूर्ण

व्योम viafb_set_secondary_color_रेजिस्टर(u8 index, u8 red, u8 green, u8 blue)
अणु
	viafb_ग_लिखो_reg_mask(0x1A, VIASR, 0x01, 0x01);
	set_color_रेजिस्टर(index, red, green, blue);
पूर्ण

अटल व्योम set_source_common(u8 index, u8 offset, u8 iga)
अणु
	u8 value, mask = 1 << offset;

	चयन (iga) अणु
	हाल IGA1:
		value = 0x00;
		अवरोध;
	हाल IGA2:
		value = mask;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "viafb: Unsupported source: %d\n", iga);
		वापस;
	पूर्ण

	via_ग_लिखो_reg_mask(VIACR, index, value, mask);
पूर्ण

अटल व्योम set_crt_source(u8 iga)
अणु
	u8 value;

	चयन (iga) अणु
	हाल IGA1:
		value = 0x00;
		अवरोध;
	हाल IGA2:
		value = 0x40;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "viafb: Unsupported source: %d\n", iga);
		वापस;
	पूर्ण

	via_ग_लिखो_reg_mask(VIASR, 0x16, value, 0x40);
पूर्ण

अटल अंतरभूत व्योम set_ldvp0_source(u8 iga)
अणु
	set_source_common(0x6C, 7, iga);
पूर्ण

अटल अंतरभूत व्योम set_ldvp1_source(u8 iga)
अणु
	set_source_common(0x93, 7, iga);
पूर्ण

अटल अंतरभूत व्योम set_dvp0_source(u8 iga)
अणु
	set_source_common(0x96, 4, iga);
पूर्ण

अटल अंतरभूत व्योम set_dvp1_source(u8 iga)
अणु
	set_source_common(0x9B, 4, iga);
पूर्ण

अटल अंतरभूत व्योम set_lvds1_source(u8 iga)
अणु
	set_source_common(0x99, 4, iga);
पूर्ण

अटल अंतरभूत व्योम set_lvds2_source(u8 iga)
अणु
	set_source_common(0x97, 4, iga);
पूर्ण

व्योम via_set_source(u32 devices, u8 iga)
अणु
	अगर (devices & VIA_LDVP0)
		set_ldvp0_source(iga);
	अगर (devices & VIA_LDVP1)
		set_ldvp1_source(iga);
	अगर (devices & VIA_DVP0)
		set_dvp0_source(iga);
	अगर (devices & VIA_CRT)
		set_crt_source(iga);
	अगर (devices & VIA_DVP1)
		set_dvp1_source(iga);
	अगर (devices & VIA_LVDS1)
		set_lvds1_source(iga);
	अगर (devices & VIA_LVDS2)
		set_lvds2_source(iga);
पूर्ण

अटल व्योम set_crt_state(u8 state)
अणु
	u8 value;

	चयन (state) अणु
	हाल VIA_STATE_ON:
		value = 0x00;
		अवरोध;
	हाल VIA_STATE_STANDBY:
		value = 0x10;
		अवरोध;
	हाल VIA_STATE_SUSPEND:
		value = 0x20;
		अवरोध;
	हाल VIA_STATE_OFF:
		value = 0x30;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	via_ग_लिखो_reg_mask(VIACR, 0x36, value, 0x30);
पूर्ण

अटल व्योम set_dvp0_state(u8 state)
अणु
	u8 value;

	चयन (state) अणु
	हाल VIA_STATE_ON:
		value = 0xC0;
		अवरोध;
	हाल VIA_STATE_OFF:
		value = 0x00;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	via_ग_लिखो_reg_mask(VIASR, 0x1E, value, 0xC0);
पूर्ण

अटल व्योम set_dvp1_state(u8 state)
अणु
	u8 value;

	चयन (state) अणु
	हाल VIA_STATE_ON:
		value = 0x30;
		अवरोध;
	हाल VIA_STATE_OFF:
		value = 0x00;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	via_ग_लिखो_reg_mask(VIASR, 0x1E, value, 0x30);
पूर्ण

अटल व्योम set_lvds1_state(u8 state)
अणु
	u8 value;

	चयन (state) अणु
	हाल VIA_STATE_ON:
		value = 0x03;
		अवरोध;
	हाल VIA_STATE_OFF:
		value = 0x00;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	via_ग_लिखो_reg_mask(VIASR, 0x2A, value, 0x03);
पूर्ण

अटल व्योम set_lvds2_state(u8 state)
अणु
	u8 value;

	चयन (state) अणु
	हाल VIA_STATE_ON:
		value = 0x0C;
		अवरोध;
	हाल VIA_STATE_OFF:
		value = 0x00;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	via_ग_लिखो_reg_mask(VIASR, 0x2A, value, 0x0C);
पूर्ण

व्योम via_set_state(u32 devices, u8 state)
अणु
	/*
	TODO: Can we enable/disable these devices? How?
	अगर (devices & VIA_LDVP0)
	अगर (devices & VIA_LDVP1)
	*/
	अगर (devices & VIA_DVP0)
		set_dvp0_state(state);
	अगर (devices & VIA_CRT)
		set_crt_state(state);
	अगर (devices & VIA_DVP1)
		set_dvp1_state(state);
	अगर (devices & VIA_LVDS1)
		set_lvds1_state(state);
	अगर (devices & VIA_LVDS2)
		set_lvds2_state(state);
पूर्ण

व्योम via_set_sync_polarity(u32 devices, u8 polarity)
अणु
	अगर (polarity & ~(VIA_HSYNC_NEGATIVE | VIA_VSYNC_NEGATIVE)) अणु
		prपूर्णांकk(KERN_WARNING "viafb: Unsupported polarity: %d\n",
			polarity);
		वापस;
	पूर्ण

	अगर (devices & VIA_CRT)
		via_ग_लिखो_misc_reg_mask(polarity << 6, 0xC0);
	अगर (devices & VIA_DVP1)
		via_ग_लिखो_reg_mask(VIACR, 0x9B, polarity << 5, 0x60);
	अगर (devices & VIA_LVDS1)
		via_ग_लिखो_reg_mask(VIACR, 0x99, polarity << 5, 0x60);
	अगर (devices & VIA_LVDS2)
		via_ग_लिखो_reg_mask(VIACR, 0x97, polarity << 5, 0x60);
पूर्ण

u32 via_parse_odev(अक्षर *input, अक्षर **end)
अणु
	अक्षर *ptr = input;
	u32 odev = 0;
	bool next = true;
	पूर्णांक i, len;

	जबतक (next) अणु
		next = false;
		क्रम (i = 0; i < ARRAY_SIZE(device_mapping); i++) अणु
			len = म_माप(device_mapping[i].name);
			अगर (!म_भेदन(ptr, device_mapping[i].name, len)) अणु
				odev |= device_mapping[i].device;
				ptr += len;
				अगर (*ptr == ',') अणु
					ptr++;
					next = true;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	*end = ptr;
	वापस odev;
पूर्ण

व्योम via_odev_to_seq(काष्ठा seq_file *m, u32 odev)
अणु
	पूर्णांक i, count = 0;

	क्रम (i = 0; i < ARRAY_SIZE(device_mapping); i++) अणु
		अगर (odev & device_mapping[i].device) अणु
			अगर (count > 0)
				seq_अ_दो(m, ',');

			seq_माला_दो(m, device_mapping[i].name);
			count++;
		पूर्ण
	पूर्ण

	seq_अ_दो(m, '\n');
पूर्ण

अटल व्योम load_fix_bit_crtc_reg(व्योम)
अणु
	viafb_unlock_crt();

	/* always set to 1 */
	viafb_ग_लिखो_reg_mask(CR03, VIACR, 0x80, BIT7);
	/* line compare should set all bits = 1 (extend modes) */
	viafb_ग_लिखो_reg_mask(CR35, VIACR, 0x10, BIT4);
	/* line compare should set all bits = 1 (extend modes) */
	viafb_ग_लिखो_reg_mask(CR33, VIACR, 0x06, BIT0 + BIT1 + BIT2);
	/*viafb_ग_लिखो_reg_mask(CR32, VIACR, 0x01, BIT0); */

	viafb_lock_crt();

	/* If K8M800, enable Prefetch Mode. */
	अगर ((viaparinfo->chip_info->gfx_chip_name == UNICHROME_K800)
		|| (viaparinfo->chip_info->gfx_chip_name == UNICHROME_K8M890))
		viafb_ग_लिखो_reg_mask(CR33, VIACR, 0x08, BIT3);
	अगर ((viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)
	    && (viaparinfo->chip_info->gfx_chip_revision == CLE266_REVISION_AX))
		viafb_ग_लिखो_reg_mask(SR1A, VIASR, 0x02, BIT1);

पूर्ण

व्योम viafb_load_reg(पूर्णांक timing_value, पूर्णांक viafb_load_reg_num,
	काष्ठा io_रेजिस्टर *reg,
	      पूर्णांक io_type)
अणु
	पूर्णांक reg_mask;
	पूर्णांक bit_num = 0;
	पूर्णांक data;
	पूर्णांक i, j;
	पूर्णांक shअगरt_next_reg;
	पूर्णांक start_index, end_index, cr_index;
	u16 get_bit;

	क्रम (i = 0; i < viafb_load_reg_num; i++) अणु
		reg_mask = 0;
		data = 0;
		start_index = reg[i].start_bit;
		end_index = reg[i].end_bit;
		cr_index = reg[i].io_addr;

		shअगरt_next_reg = bit_num;
		क्रम (j = start_index; j <= end_index; j++) अणु
			/*अगर (bit_num==8) timing_value = timing_value >>8; */
			reg_mask = reg_mask | (BIT0 << j);
			get_bit = (timing_value & (BIT0 << bit_num));
			data =
			    data | ((get_bit >> shअगरt_next_reg) << start_index);
			bit_num++;
		पूर्ण
		अगर (io_type == VIACR)
			viafb_ग_लिखो_reg_mask(cr_index, VIACR, data, reg_mask);
		अन्यथा
			viafb_ग_लिखो_reg_mask(cr_index, VIASR, data, reg_mask);
	पूर्ण

पूर्ण

/* Write Registers */
व्योम viafb_ग_लिखो_regx(काष्ठा io_reg RegTable[], पूर्णांक ItemNum)
अणु
	पूर्णांक i;

	/*DEBUG_MSG(KERN_INFO "Table Size : %x!!\n",ItemNum ); */

	क्रम (i = 0; i < ItemNum; i++)
		via_ग_लिखो_reg_mask(RegTable[i].port, RegTable[i].index,
			RegTable[i].value, RegTable[i].mask);
पूर्ण

व्योम viafb_load_fetch_count_reg(पूर्णांक h_addr, पूर्णांक bpp_byte, पूर्णांक set_iga)
अणु
	पूर्णांक reg_value;
	पूर्णांक viafb_load_reg_num;
	काष्ठा io_रेजिस्टर *reg = शून्य;

	चयन (set_iga) अणु
	हाल IGA1:
		reg_value = IGA1_FETCH_COUNT_FORMULA(h_addr, bpp_byte);
		viafb_load_reg_num = fetch_count_reg.
			iga1_fetch_count_reg.reg_num;
		reg = fetch_count_reg.iga1_fetch_count_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIASR);
		अवरोध;
	हाल IGA2:
		reg_value = IGA2_FETCH_COUNT_FORMULA(h_addr, bpp_byte);
		viafb_load_reg_num = fetch_count_reg.
			iga2_fetch_count_reg.reg_num;
		reg = fetch_count_reg.iga2_fetch_count_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIACR);
		अवरोध;
	पूर्ण

पूर्ण

व्योम viafb_load_FIFO_reg(पूर्णांक set_iga, पूर्णांक hor_active, पूर्णांक ver_active)
अणु
	पूर्णांक reg_value;
	पूर्णांक viafb_load_reg_num;
	काष्ठा io_रेजिस्टर *reg = शून्य;
	पूर्णांक iga1_fअगरo_max_depth = 0, iga1_fअगरo_threshold =
	    0, iga1_fअगरo_high_threshold = 0, iga1_display_queue_expire_num = 0;
	पूर्णांक iga2_fअगरo_max_depth = 0, iga2_fअगरo_threshold =
	    0, iga2_fअगरo_high_threshold = 0, iga2_display_queue_expire_num = 0;

	अगर (set_iga == IGA1) अणु
		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_K800) अणु
			iga1_fअगरo_max_depth = K800_IGA1_FIFO_MAX_DEPTH;
			iga1_fअगरo_threshold = K800_IGA1_FIFO_THRESHOLD;
			iga1_fअगरo_high_threshold =
			    K800_IGA1_FIFO_HIGH_THRESHOLD;
			/* If resolution > 1280x1024, expire length = 64, अन्यथा
			   expire length = 128 */
			अगर ((hor_active > 1280) && (ver_active > 1024))
				iga1_display_queue_expire_num = 16;
			अन्यथा
				iga1_display_queue_expire_num =
				    K800_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;

		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_PM800) अणु
			iga1_fअगरo_max_depth = P880_IGA1_FIFO_MAX_DEPTH;
			iga1_fअगरo_threshold = P880_IGA1_FIFO_THRESHOLD;
			iga1_fअगरo_high_threshold =
			    P880_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    P880_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;

			/* If resolution > 1280x1024, expire length = 64, अन्यथा
			   expire length = 128 */
			अगर ((hor_active > 1280) && (ver_active > 1024))
				iga1_display_queue_expire_num = 16;
			अन्यथा
				iga1_display_queue_expire_num =
				    P880_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CN700) अणु
			iga1_fअगरo_max_depth = CN700_IGA1_FIFO_MAX_DEPTH;
			iga1_fअगरo_threshold = CN700_IGA1_FIFO_THRESHOLD;
			iga1_fअगरo_high_threshold =
			    CN700_IGA1_FIFO_HIGH_THRESHOLD;

			/* If resolution > 1280x1024, expire length = 64,
			   अन्यथा expire length = 128 */
			अगर ((hor_active > 1280) && (ver_active > 1024))
				iga1_display_queue_expire_num = 16;
			अन्यथा
				iga1_display_queue_expire_num =
				    CN700_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CX700) अणु
			iga1_fअगरo_max_depth = CX700_IGA1_FIFO_MAX_DEPTH;
			iga1_fअगरo_threshold = CX700_IGA1_FIFO_THRESHOLD;
			iga1_fअगरo_high_threshold =
			    CX700_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    CX700_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_K8M890) अणु
			iga1_fअगरo_max_depth = K8M890_IGA1_FIFO_MAX_DEPTH;
			iga1_fअगरo_threshold = K8M890_IGA1_FIFO_THRESHOLD;
			iga1_fअगरo_high_threshold =
			    K8M890_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    K8M890_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_P4M890) अणु
			iga1_fअगरo_max_depth = P4M890_IGA1_FIFO_MAX_DEPTH;
			iga1_fअगरo_threshold = P4M890_IGA1_FIFO_THRESHOLD;
			iga1_fअगरo_high_threshold =
			    P4M890_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    P4M890_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_P4M900) अणु
			iga1_fअगरo_max_depth = P4M900_IGA1_FIFO_MAX_DEPTH;
			iga1_fअगरo_threshold = P4M900_IGA1_FIFO_THRESHOLD;
			iga1_fअगरo_high_threshold =
			    P4M900_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    P4M900_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_VX800) अणु
			iga1_fअगरo_max_depth = VX800_IGA1_FIFO_MAX_DEPTH;
			iga1_fअगरo_threshold = VX800_IGA1_FIFO_THRESHOLD;
			iga1_fअगरo_high_threshold =
			    VX800_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    VX800_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_VX855) अणु
			iga1_fअगरo_max_depth = VX855_IGA1_FIFO_MAX_DEPTH;
			iga1_fअगरo_threshold = VX855_IGA1_FIFO_THRESHOLD;
			iga1_fअगरo_high_threshold =
			    VX855_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    VX855_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_VX900) अणु
			iga1_fअगरo_max_depth = VX900_IGA1_FIFO_MAX_DEPTH;
			iga1_fअगरo_threshold = VX900_IGA1_FIFO_THRESHOLD;
			iga1_fअगरo_high_threshold =
			    VX900_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    VX900_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		/* Set Display FIFO Depath Select */
		reg_value = IGA1_FIFO_DEPTH_SELECT_FORMULA(iga1_fअगरo_max_depth);
		viafb_load_reg_num =
		    display_fअगरo_depth_reg.iga1_fअगरo_depth_select_reg.reg_num;
		reg = display_fअगरo_depth_reg.iga1_fअगरo_depth_select_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIASR);

		/* Set Display FIFO Threshold Select */
		reg_value = IGA1_FIFO_THRESHOLD_FORMULA(iga1_fअगरo_threshold);
		viafb_load_reg_num =
		    fअगरo_threshold_select_reg.
		    iga1_fअगरo_threshold_select_reg.reg_num;
		reg =
		    fअगरo_threshold_select_reg.
		    iga1_fअगरo_threshold_select_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIASR);

		/* Set FIFO High Threshold Select */
		reg_value =
		    IGA1_FIFO_HIGH_THRESHOLD_FORMULA(iga1_fअगरo_high_threshold);
		viafb_load_reg_num =
		    fअगरo_high_threshold_select_reg.
		    iga1_fअगरo_high_threshold_select_reg.reg_num;
		reg =
		    fअगरo_high_threshold_select_reg.
		    iga1_fअगरo_high_threshold_select_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIASR);

		/* Set Display Queue Expire Num */
		reg_value =
		    IGA1_DISPLAY_QUEUE_EXPIRE_NUM_FORMULA
		    (iga1_display_queue_expire_num);
		viafb_load_reg_num =
		    display_queue_expire_num_reg.
		    iga1_display_queue_expire_num_reg.reg_num;
		reg =
		    display_queue_expire_num_reg.
		    iga1_display_queue_expire_num_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIASR);

	पूर्ण अन्यथा अणु
		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_K800) अणु
			iga2_fअगरo_max_depth = K800_IGA2_FIFO_MAX_DEPTH;
			iga2_fअगरo_threshold = K800_IGA2_FIFO_THRESHOLD;
			iga2_fअगरo_high_threshold =
			    K800_IGA2_FIFO_HIGH_THRESHOLD;

			/* If resolution > 1280x1024, expire length = 64,
			   अन्यथा  expire length = 128 */
			अगर ((hor_active > 1280) && (ver_active > 1024))
				iga2_display_queue_expire_num = 16;
			अन्यथा
				iga2_display_queue_expire_num =
				    K800_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_PM800) अणु
			iga2_fअगरo_max_depth = P880_IGA2_FIFO_MAX_DEPTH;
			iga2_fअगरo_threshold = P880_IGA2_FIFO_THRESHOLD;
			iga2_fअगरo_high_threshold =
			    P880_IGA2_FIFO_HIGH_THRESHOLD;

			/* If resolution > 1280x1024, expire length = 64,
			   अन्यथा  expire length = 128 */
			अगर ((hor_active > 1280) && (ver_active > 1024))
				iga2_display_queue_expire_num = 16;
			अन्यथा
				iga2_display_queue_expire_num =
				    P880_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CN700) अणु
			iga2_fअगरo_max_depth = CN700_IGA2_FIFO_MAX_DEPTH;
			iga2_fअगरo_threshold = CN700_IGA2_FIFO_THRESHOLD;
			iga2_fअगरo_high_threshold =
			    CN700_IGA2_FIFO_HIGH_THRESHOLD;

			/* If resolution > 1280x1024, expire length = 64,
			   अन्यथा expire length = 128 */
			अगर ((hor_active > 1280) && (ver_active > 1024))
				iga2_display_queue_expire_num = 16;
			अन्यथा
				iga2_display_queue_expire_num =
				    CN700_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CX700) अणु
			iga2_fअगरo_max_depth = CX700_IGA2_FIFO_MAX_DEPTH;
			iga2_fअगरo_threshold = CX700_IGA2_FIFO_THRESHOLD;
			iga2_fअगरo_high_threshold =
			    CX700_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    CX700_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_K8M890) अणु
			iga2_fअगरo_max_depth = K8M890_IGA2_FIFO_MAX_DEPTH;
			iga2_fअगरo_threshold = K8M890_IGA2_FIFO_THRESHOLD;
			iga2_fअगरo_high_threshold =
			    K8M890_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    K8M890_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_P4M890) अणु
			iga2_fअगरo_max_depth = P4M890_IGA2_FIFO_MAX_DEPTH;
			iga2_fअगरo_threshold = P4M890_IGA2_FIFO_THRESHOLD;
			iga2_fअगरo_high_threshold =
			    P4M890_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    P4M890_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_P4M900) अणु
			iga2_fअगरo_max_depth = P4M900_IGA2_FIFO_MAX_DEPTH;
			iga2_fअगरo_threshold = P4M900_IGA2_FIFO_THRESHOLD;
			iga2_fअगरo_high_threshold =
			    P4M900_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    P4M900_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_VX800) अणु
			iga2_fअगरo_max_depth = VX800_IGA2_FIFO_MAX_DEPTH;
			iga2_fअगरo_threshold = VX800_IGA2_FIFO_THRESHOLD;
			iga2_fअगरo_high_threshold =
			    VX800_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    VX800_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_VX855) अणु
			iga2_fअगरo_max_depth = VX855_IGA2_FIFO_MAX_DEPTH;
			iga2_fअगरo_threshold = VX855_IGA2_FIFO_THRESHOLD;
			iga2_fअगरo_high_threshold =
			    VX855_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    VX855_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_VX900) अणु
			iga2_fअगरo_max_depth = VX900_IGA2_FIFO_MAX_DEPTH;
			iga2_fअगरo_threshold = VX900_IGA2_FIFO_THRESHOLD;
			iga2_fअगरo_high_threshold =
			    VX900_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    VX900_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		पूर्ण

		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_K800) अणु
			/* Set Display FIFO Depath Select */
			reg_value =
			    IGA2_FIFO_DEPTH_SELECT_FORMULA(iga2_fअगरo_max_depth)
			    - 1;
			/* Patch LCD in IGA2 हाल */
			viafb_load_reg_num =
			    display_fअगरo_depth_reg.
			    iga2_fअगरo_depth_select_reg.reg_num;
			reg =
			    display_fअगरo_depth_reg.
			    iga2_fअगरo_depth_select_reg.reg;
			viafb_load_reg(reg_value,
				viafb_load_reg_num, reg, VIACR);
		पूर्ण अन्यथा अणु

			/* Set Display FIFO Depath Select */
			reg_value =
			    IGA2_FIFO_DEPTH_SELECT_FORMULA(iga2_fअगरo_max_depth);
			viafb_load_reg_num =
			    display_fअगरo_depth_reg.
			    iga2_fअगरo_depth_select_reg.reg_num;
			reg =
			    display_fअगरo_depth_reg.
			    iga2_fअगरo_depth_select_reg.reg;
			viafb_load_reg(reg_value,
				viafb_load_reg_num, reg, VIACR);
		पूर्ण

		/* Set Display FIFO Threshold Select */
		reg_value = IGA2_FIFO_THRESHOLD_FORMULA(iga2_fअगरo_threshold);
		viafb_load_reg_num =
		    fअगरo_threshold_select_reg.
		    iga2_fअगरo_threshold_select_reg.reg_num;
		reg =
		    fअगरo_threshold_select_reg.
		    iga2_fअगरo_threshold_select_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIACR);

		/* Set FIFO High Threshold Select */
		reg_value =
		    IGA2_FIFO_HIGH_THRESHOLD_FORMULA(iga2_fअगरo_high_threshold);
		viafb_load_reg_num =
		    fअगरo_high_threshold_select_reg.
		    iga2_fअगरo_high_threshold_select_reg.reg_num;
		reg =
		    fअगरo_high_threshold_select_reg.
		    iga2_fअगरo_high_threshold_select_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIACR);

		/* Set Display Queue Expire Num */
		reg_value =
		    IGA2_DISPLAY_QUEUE_EXPIRE_NUM_FORMULA
		    (iga2_display_queue_expire_num);
		viafb_load_reg_num =
		    display_queue_expire_num_reg.
		    iga2_display_queue_expire_num_reg.reg_num;
		reg =
		    display_queue_expire_num_reg.
		    iga2_display_queue_expire_num_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIACR);

	पूर्ण

पूर्ण

अटल काष्ठा via_pll_config get_pll_config(काष्ठा pll_limit *limits, पूर्णांक size,
	पूर्णांक clk)
अणु
	काष्ठा via_pll_config cur, up, करोwn, best = अणु0, 1, 0पूर्ण;
	स्थिर u32 f0 = 14318180; /* X1 frequency */
	पूर्णांक i, f;

	क्रम (i = 0; i < size; i++) अणु
		cur.rshअगरt = limits[i].rshअगरt;
		cur.भागisor = limits[i].भागisor;
		cur.multiplier = clk / ((f0 / cur.भागisor)>>cur.rshअगरt);
		f = असल(get_pll_output_frequency(f0, cur) - clk);
		up = करोwn = cur;
		up.multiplier++;
		करोwn.multiplier--;
		अगर (असल(get_pll_output_frequency(f0, up) - clk) < f)
			cur = up;
		अन्यथा अगर (असल(get_pll_output_frequency(f0, करोwn) - clk) < f)
			cur = करोwn;

		अगर (cur.multiplier < limits[i].multiplier_min)
			cur.multiplier = limits[i].multiplier_min;
		अन्यथा अगर (cur.multiplier > limits[i].multiplier_max)
			cur.multiplier = limits[i].multiplier_max;

		f = असल(get_pll_output_frequency(f0, cur) - clk);
		अगर (f < असल(get_pll_output_frequency(f0, best) - clk))
			best = cur;
	पूर्ण

	वापस best;
पूर्ण

अटल काष्ठा via_pll_config get_best_pll_config(पूर्णांक clk)
अणु
	काष्ठा via_pll_config config;

	चयन (viaparinfo->chip_info->gfx_chip_name) अणु
	हाल UNICHROME_CLE266:
	हाल UNICHROME_K400:
		config = get_pll_config(cle266_pll_limits,
			ARRAY_SIZE(cle266_pll_limits), clk);
		अवरोध;
	हाल UNICHROME_K800:
	हाल UNICHROME_PM800:
	हाल UNICHROME_CN700:
		config = get_pll_config(k800_pll_limits,
			ARRAY_SIZE(k800_pll_limits), clk);
		अवरोध;
	हाल UNICHROME_CX700:
	हाल UNICHROME_CN750:
	हाल UNICHROME_K8M890:
	हाल UNICHROME_P4M890:
	हाल UNICHROME_P4M900:
	हाल UNICHROME_VX800:
		config = get_pll_config(cx700_pll_limits,
			ARRAY_SIZE(cx700_pll_limits), clk);
		अवरोध;
	हाल UNICHROME_VX855:
	हाल UNICHROME_VX900:
		config = get_pll_config(vx855_pll_limits,
			ARRAY_SIZE(vx855_pll_limits), clk);
		अवरोध;
	पूर्ण

	वापस config;
पूर्ण

/* Set VCLK*/
व्योम viafb_set_vघड़ी(u32 clk, पूर्णांक set_iga)
अणु
	काष्ठा via_pll_config config = get_best_pll_config(clk);

	अगर (set_iga == IGA1)
		घड़ी.set_primary_pll(config);
	अगर (set_iga == IGA2)
		घड़ी.set_secondary_pll(config);

	/* Fire! */
	via_ग_लिखो_misc_reg_mask(0x0C, 0x0C); /* select बाह्यal घड़ी */
पूर्ण

काष्ठा via_display_timing var_to_timing(स्थिर काष्ठा fb_var_screeninfo *var,
	u16 cxres, u16 cyres)
अणु
	काष्ठा via_display_timing timing;
	u16 dx = (var->xres - cxres) / 2, dy = (var->yres - cyres) / 2;

	timing.hor_addr = cxres;
	timing.hor_sync_start = timing.hor_addr + var->right_margin + dx;
	timing.hor_sync_end = timing.hor_sync_start + var->hsync_len;
	timing.hor_total = timing.hor_sync_end + var->left_margin + dx;
	timing.hor_blank_start = timing.hor_addr + dx;
	timing.hor_blank_end = timing.hor_total - dx;
	timing.ver_addr = cyres;
	timing.ver_sync_start = timing.ver_addr + var->lower_margin + dy;
	timing.ver_sync_end = timing.ver_sync_start + var->vsync_len;
	timing.ver_total = timing.ver_sync_end + var->upper_margin + dy;
	timing.ver_blank_start = timing.ver_addr + dy;
	timing.ver_blank_end = timing.ver_total - dy;
	वापस timing;
पूर्ण

व्योम viafb_fill_crtc_timing(स्थिर काष्ठा fb_var_screeninfo *var,
	u16 cxres, u16 cyres, पूर्णांक iga)
अणु
	काष्ठा via_display_timing crt_reg = var_to_timing(var,
		cxres ? cxres : var->xres, cyres ? cyres : var->yres);

	अगर (iga == IGA1)
		via_set_primary_timing(&crt_reg);
	अन्यथा अगर (iga == IGA2)
		via_set_secondary_timing(&crt_reg);

	viafb_load_fetch_count_reg(var->xres, var->bits_per_pixel / 8, iga);
	अगर (viaparinfo->chip_info->gfx_chip_name != UNICHROME_CLE266
		&& viaparinfo->chip_info->gfx_chip_name != UNICHROME_K400)
		viafb_load_FIFO_reg(iga, var->xres, var->yres);

	viafb_set_vघड़ी(PICOS2KHZ(var->pixघड़ी) * 1000, iga);
पूर्ण

व्योम viafb_init_chip_info(पूर्णांक chip_type)
अणु
	via_घड़ी_init(&घड़ी, chip_type);
	init_gfx_chip_info(chip_type);
	init_पंचांगds_chip_info();
	init_lvds_chip_info();

	/*Set IGA path क्रम each device */
	viafb_set_iga_path();

	viaparinfo->lvds_setting_info->display_method = viafb_lcd_dsp_method;
	viaparinfo->lvds_setting_info->lcd_mode = viafb_lcd_mode;
	viaparinfo->lvds_setting_info2->display_method =
		viaparinfo->lvds_setting_info->display_method;
	viaparinfo->lvds_setting_info2->lcd_mode =
		viaparinfo->lvds_setting_info->lcd_mode;
पूर्ण

व्योम viafb_update_device_setting(पूर्णांक hres, पूर्णांक vres, पूर्णांक bpp, पूर्णांक flag)
अणु
	अगर (flag == 0) अणु
		viaparinfo->पंचांगds_setting_info->h_active = hres;
		viaparinfo->पंचांगds_setting_info->v_active = vres;
	पूर्ण अन्यथा अणु

		अगर (viaparinfo->पंचांगds_setting_info->iga_path == IGA2) अणु
			viaparinfo->पंचांगds_setting_info->h_active = hres;
			viaparinfo->पंचांगds_setting_info->v_active = vres;
		पूर्ण

	पूर्ण
पूर्ण

अटल व्योम init_gfx_chip_info(पूर्णांक chip_type)
अणु
	u8 पंचांगp;

	viaparinfo->chip_info->gfx_chip_name = chip_type;

	/* Check revision of CLE266 Chip */
	अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266) अणु
		/* CR4F only define in CLE266.CX chip */
		पंचांगp = viafb_पढ़ो_reg(VIACR, CR4F);
		viafb_ग_लिखो_reg(CR4F, VIACR, 0x55);
		अगर (viafb_पढ़ो_reg(VIACR, CR4F) != 0x55)
			viaparinfo->chip_info->gfx_chip_revision =
			CLE266_REVISION_AX;
		अन्यथा
			viaparinfo->chip_info->gfx_chip_revision =
			CLE266_REVISION_CX;
		/* restore orignal CR4F value */
		viafb_ग_लिखो_reg(CR4F, VIACR, पंचांगp);
	पूर्ण

	अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CX700) अणु
		पंचांगp = viafb_पढ़ो_reg(VIASR, SR43);
		DEBUG_MSG(KERN_INFO "SR43:%X\n", पंचांगp);
		अगर (पंचांगp & 0x02) अणु
			viaparinfo->chip_info->gfx_chip_revision =
				CX700_REVISION_700M2;
		पूर्ण अन्यथा अगर (पंचांगp & 0x40) अणु
			viaparinfo->chip_info->gfx_chip_revision =
				CX700_REVISION_700M;
		पूर्ण अन्यथा अणु
			viaparinfo->chip_info->gfx_chip_revision =
				CX700_REVISION_700;
		पूर्ण
	पूर्ण

	/* Determine which 2D engine we have */
	चयन (viaparinfo->chip_info->gfx_chip_name) अणु
	हाल UNICHROME_VX800:
	हाल UNICHROME_VX855:
	हाल UNICHROME_VX900:
		viaparinfo->chip_info->twod_engine = VIA_2D_ENG_M1;
		अवरोध;
	हाल UNICHROME_K8M890:
	हाल UNICHROME_P4M900:
		viaparinfo->chip_info->twod_engine = VIA_2D_ENG_H5;
		अवरोध;
	शेष:
		viaparinfo->chip_info->twod_engine = VIA_2D_ENG_H2;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम init_पंचांगds_chip_info(व्योम)
अणु
	viafb_पंचांगds_trयंत्रitter_identअगरy();

	अगर (INTERFACE_NONE == viaparinfo->chip_info->पंचांगds_chip_info.
		output_पूर्णांकerface) अणु
		चयन (viaparinfo->chip_info->gfx_chip_name) अणु
		हाल UNICHROME_CX700:
			अणु
				/* we should check support by hardware layout.*/
				अगर ((viafb_display_hardware_layout ==
				     HW_LAYOUT_DVI_ONLY)
				    || (viafb_display_hardware_layout ==
					HW_LAYOUT_LCD_DVI)) अणु
					viaparinfo->chip_info->पंचांगds_chip_info.
					    output_पूर्णांकerface = INTERFACE_TMDS;
				पूर्ण अन्यथा अणु
					viaparinfo->chip_info->पंचांगds_chip_info.
						output_पूर्णांकerface =
						INTERFACE_NONE;
				पूर्ण
				अवरोध;
			पूर्ण
		हाल UNICHROME_K8M890:
		हाल UNICHROME_P4M900:
		हाल UNICHROME_P4M890:
			/* TMDS on PCIE, we set DFPLOW as शेष. */
			viaparinfo->chip_info->पंचांगds_chip_info.output_पूर्णांकerface =
			    INTERFACE_DFP_LOW;
			अवरोध;
		शेष:
			अणु
				/* set DVP1 शेष क्रम DVI */
				viaparinfo->chip_info->पंचांगds_chip_info
				.output_पूर्णांकerface = INTERFACE_DVP1;
			पूर्ण
		पूर्ण
	पूर्ण

	DEBUG_MSG(KERN_INFO "TMDS Chip = %d\n",
		  viaparinfo->chip_info->पंचांगds_chip_info.पंचांगds_chip_name);
	viafb_init_dvi_size(&viaparinfo->shared->chip_info.पंचांगds_chip_info,
		&viaparinfo->shared->पंचांगds_setting_info);
पूर्ण

अटल व्योम init_lvds_chip_info(व्योम)
अणु
	viafb_lvds_trयंत्रitter_identअगरy();
	viafb_init_lcd_size();
	viafb_init_lvds_output_पूर्णांकerface(&viaparinfo->chip_info->lvds_chip_info,
				   viaparinfo->lvds_setting_info);
	अगर (viaparinfo->chip_info->lvds_chip_info2.lvds_chip_name) अणु
		viafb_init_lvds_output_पूर्णांकerface(&viaparinfo->chip_info->
			lvds_chip_info2, viaparinfo->lvds_setting_info2);
	पूर्ण
	/*If CX700,two singel LCD, we need to reassign
	   LCD पूर्णांकerface to dअगरferent LVDS port */
	अगर ((UNICHROME_CX700 == viaparinfo->chip_info->gfx_chip_name)
	    && (HW_LAYOUT_LCD1_LCD2 == viafb_display_hardware_layout)) अणु
		अगर ((INTEGRATED_LVDS == viaparinfo->chip_info->lvds_chip_info.
			lvds_chip_name) && (INTEGRATED_LVDS ==
			viaparinfo->chip_info->
			lvds_chip_info2.lvds_chip_name)) अणु
			viaparinfo->chip_info->lvds_chip_info.output_पूर्णांकerface =
				INTERFACE_LVDS0;
			viaparinfo->chip_info->lvds_chip_info2.
				output_पूर्णांकerface =
			    INTERFACE_LVDS1;
		पूर्ण
	पूर्ण

	DEBUG_MSG(KERN_INFO "LVDS Chip = %d\n",
		  viaparinfo->chip_info->lvds_chip_info.lvds_chip_name);
	DEBUG_MSG(KERN_INFO "LVDS1 output_interface = %d\n",
		  viaparinfo->chip_info->lvds_chip_info.output_पूर्णांकerface);
	DEBUG_MSG(KERN_INFO "LVDS2 output_interface = %d\n",
		  viaparinfo->chip_info->lvds_chip_info.output_पूर्णांकerface);
पूर्ण

व्योम viafb_init_dac(पूर्णांक set_iga)
अणु
	पूर्णांक i;
	u8 पंचांगp;

	अगर (set_iga == IGA1) अणु
		/* access Primary Display's LUT */
		viafb_ग_लिखो_reg_mask(SR1A, VIASR, 0x00, BIT0);
		/* turn off LCK */
		viafb_ग_लिखो_reg_mask(SR1B, VIASR, 0x00, BIT7 + BIT6);
		क्रम (i = 0; i < 256; i++) अणु
			ग_लिखो_dac_reg(i, palLUT_table[i].red,
				      palLUT_table[i].green,
				      palLUT_table[i].blue);
		पूर्ण
		/* turn on LCK */
		viafb_ग_लिखो_reg_mask(SR1B, VIASR, 0xC0, BIT7 + BIT6);
	पूर्ण अन्यथा अणु
		पंचांगp = viafb_पढ़ो_reg(VIACR, CR6A);
		/* access Secondary Display's LUT */
		viafb_ग_लिखो_reg_mask(CR6A, VIACR, 0x40, BIT6);
		viafb_ग_लिखो_reg_mask(SR1A, VIASR, 0x01, BIT0);
		क्रम (i = 0; i < 256; i++) अणु
			ग_लिखो_dac_reg(i, palLUT_table[i].red,
				      palLUT_table[i].green,
				      palLUT_table[i].blue);
		पूर्ण
		/* set IGA1 DAC क्रम शेष */
		viafb_ग_लिखो_reg_mask(SR1A, VIASR, 0x00, BIT0);
		viafb_ग_लिखो_reg(CR6A, VIACR, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम device_screen_off(व्योम)
अणु
	/* turn off CRT screen (IGA1) */
	viafb_ग_लिखो_reg_mask(SR01, VIASR, 0x20, BIT5);
पूर्ण

अटल व्योम device_screen_on(व्योम)
अणु
	/* turn on CRT screen (IGA1) */
	viafb_ग_लिखो_reg_mask(SR01, VIASR, 0x00, BIT5);
पूर्ण

अटल व्योम set_display_channel(व्योम)
अणु
	/*If viafb_LCD2_ON, on cx700, पूर्णांकernal lvds's inक्रमmation
	is keeped on lvds_setting_info2 */
	अगर (viafb_LCD2_ON &&
		viaparinfo->lvds_setting_info2->device_lcd_dualedge) अणु
		/* For dual channel LCD: */
		/* Set to Dual LVDS channel. */
		viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0x20, BIT4 + BIT5);
	पूर्ण अन्यथा अगर (viafb_LCD_ON && viafb_DVI_ON) अणु
		/* For LCD+DFP: */
		/* Set to LVDS1 + TMDS channel. */
		viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0x10, BIT4 + BIT5);
	पूर्ण अन्यथा अगर (viafb_DVI_ON) अणु
		/* Set to single TMDS channel. */
		viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0x30, BIT4 + BIT5);
	पूर्ण अन्यथा अगर (viafb_LCD_ON) अणु
		अगर (viaparinfo->lvds_setting_info->device_lcd_dualedge) अणु
			/* For dual channel LCD: */
			/* Set to Dual LVDS channel. */
			viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0x20, BIT4 + BIT5);
		पूर्ण अन्यथा अणु
			/* Set to LVDS0 + LVDS1 channel. */
			viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0x00, BIT4 + BIT5);
		पूर्ण
	पूर्ण
पूर्ण

अटल u8 get_sync(काष्ठा fb_var_screeninfo *var)
अणु
	u8 polarity = 0;

	अगर (!(var->sync & FB_SYNC_HOR_HIGH_ACT))
		polarity |= VIA_HSYNC_NEGATIVE;
	अगर (!(var->sync & FB_SYNC_VERT_HIGH_ACT))
		polarity |= VIA_VSYNC_NEGATIVE;
	वापस polarity;
पूर्ण

अटल व्योम hw_init(व्योम)
अणु
	पूर्णांक i;

	inb(VIAStatus);
	outb(0x00, VIAAR);

	/* Write Common Setting क्रम Video Mode */
	viafb_ग_लिखो_regx(common_vga, ARRAY_SIZE(common_vga));
	चयन (viaparinfo->chip_info->gfx_chip_name) अणु
	हाल UNICHROME_CLE266:
		viafb_ग_लिखो_regx(CLE266_ModeXregs, NUM_TOTAL_CLE266_ModeXregs);
		अवरोध;

	हाल UNICHROME_K400:
		viafb_ग_लिखो_regx(KM400_ModeXregs, NUM_TOTAL_KM400_ModeXregs);
		अवरोध;

	हाल UNICHROME_K800:
	हाल UNICHROME_PM800:
		viafb_ग_लिखो_regx(CN400_ModeXregs, NUM_TOTAL_CN400_ModeXregs);
		अवरोध;

	हाल UNICHROME_CN700:
	हाल UNICHROME_K8M890:
	हाल UNICHROME_P4M890:
	हाल UNICHROME_P4M900:
		viafb_ग_लिखो_regx(CN700_ModeXregs, NUM_TOTAL_CN700_ModeXregs);
		अवरोध;

	हाल UNICHROME_CX700:
	हाल UNICHROME_VX800:
		viafb_ग_लिखो_regx(CX700_ModeXregs, NUM_TOTAL_CX700_ModeXregs);
		अवरोध;

	हाल UNICHROME_VX855:
	हाल UNICHROME_VX900:
		viafb_ग_लिखो_regx(VX855_ModeXregs, NUM_TOTAL_VX855_ModeXregs);
		अवरोध;
	पूर्ण

	/* magic required on VX900 क्रम correct modesetting on IGA1 */
	via_ग_लिखो_reg_mask(VIACR, 0x45, 0x00, 0x01);

	/* probably this should go to the scaling code one day */
	via_ग_लिखो_reg_mask(VIACR, 0xFD, 0, 0x80); /* VX900 hw scale on IGA2 */
	viafb_ग_लिखो_regx(scaling_parameters, ARRAY_SIZE(scaling_parameters));

	/* Fill VPIT Parameters */
	/* Write Misc Register */
	outb(VPIT.Misc, VIA_MISC_REG_WRITE);

	/* Write Sequencer */
	क्रम (i = 1; i <= StdSR; i++)
		via_ग_लिखो_reg(VIASR, i, VPIT.SR[i - 1]);

	viafb_ग_लिखो_reg_mask(0x15, VIASR, 0xA2, 0xA2);

	/* Write Graphic Controller */
	क्रम (i = 0; i < StdGR; i++)
		via_ग_लिखो_reg(VIAGR, i, VPIT.GR[i]);

	/* Write Attribute Controller */
	क्रम (i = 0; i < StdAR; i++) अणु
		inb(VIAStatus);
		outb(i, VIAAR);
		outb(VPIT.AR[i], VIAAR);
	पूर्ण

	inb(VIAStatus);
	outb(0x20, VIAAR);

	load_fix_bit_crtc_reg();
पूर्ण

पूर्णांक viafb_seपंचांगode(व्योम)
अणु
	पूर्णांक j, cxres = 0, cyres = 0;
	पूर्णांक port;
	u32 devices = viaparinfo->shared->iga1_devices
		| viaparinfo->shared->iga2_devices;
	u8 value, index, mask;
	काष्ठा fb_var_screeninfo var2;

	device_screen_off();
	device_off();
	via_set_state(devices, VIA_STATE_OFF);

	hw_init();

	/* Update Patch Register */

	अगर ((viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266
		|| viaparinfo->chip_info->gfx_chip_name == UNICHROME_K400)
		&& viafbinfo->var.xres == 1024 && viafbinfo->var.yres == 768) अणु
		क्रम (j = 0; j < res_patch_table[0].table_length; j++) अणु
			index = res_patch_table[0].io_reg_table[j].index;
			port = res_patch_table[0].io_reg_table[j].port;
			value = res_patch_table[0].io_reg_table[j].value;
			mask = res_patch_table[0].io_reg_table[j].mask;
			viafb_ग_लिखो_reg_mask(index, port, value, mask);
		पूर्ण
	पूर्ण

	via_set_primary_pitch(viafbinfo->fix.line_length);
	via_set_secondary_pitch(viafb_dual_fb ? viafbinfo1->fix.line_length
		: viafbinfo->fix.line_length);
	via_set_primary_color_depth(viaparinfo->depth);
	via_set_secondary_color_depth(viafb_dual_fb ? viaparinfo1->depth
		: viaparinfo->depth);
	via_set_source(viaparinfo->shared->iga1_devices, IGA1);
	via_set_source(viaparinfo->shared->iga2_devices, IGA2);
	अगर (viaparinfo->shared->iga2_devices)
		enable_second_display_channel();
	अन्यथा
		disable_second_display_channel();

	/* Update Refresh Rate Setting */

	/* Clear On Screen */

	अगर (viafb_dual_fb) अणु
		var2 = viafbinfo1->var;
	पूर्ण अन्यथा अगर (viafb_SAMM_ON) अणु
		viafb_fill_var_timing_info(&var2, viafb_get_best_mode(
			viafb_second_xres, viafb_second_yres, viafb_refresh1));
		cxres = viafbinfo->var.xres;
		cyres = viafbinfo->var.yres;
		var2.bits_per_pixel = viafbinfo->var.bits_per_pixel;
	पूर्ण

	/* CRT set mode */
	अगर (viafb_CRT_ON) अणु
		अगर (viaparinfo->shared->iga2_devices & VIA_CRT
			&& viafb_SAMM_ON)
			viafb_fill_crtc_timing(&var2, cxres, cyres, IGA2);
		अन्यथा
			viafb_fill_crtc_timing(&viafbinfo->var, 0, 0,
				(viaparinfo->shared->iga1_devices & VIA_CRT)
				? IGA1 : IGA2);

		/* Patch अगर set_hres is not 8 alignment (1366) to viafb_seपंचांगode
		to 8 alignment (1368),there is several pixels (2 pixels)
		on right side of screen. */
		अगर (viafbinfo->var.xres % 8) अणु
			viafb_unlock_crt();
			viafb_ग_लिखो_reg(CR02, VIACR,
				viafb_पढ़ो_reg(VIACR, CR02) - 1);
			viafb_lock_crt();
		पूर्ण
	पूर्ण

	अगर (viafb_DVI_ON) अणु
		अगर (viaparinfo->shared->पंचांगds_setting_info.iga_path == IGA2
			&& viafb_SAMM_ON)
			viafb_dvi_set_mode(&var2, cxres, cyres, IGA2);
		अन्यथा
			viafb_dvi_set_mode(&viafbinfo->var, 0, 0,
				viaparinfo->पंचांगds_setting_info->iga_path);
	पूर्ण

	अगर (viafb_LCD_ON) अणु
		अगर (viafb_SAMM_ON &&
			(viaparinfo->lvds_setting_info->iga_path == IGA2)) अणु
			viafb_lcd_set_mode(&var2, cxres, cyres,
				viaparinfo->lvds_setting_info,
				&viaparinfo->chip_info->lvds_chip_info);
		पूर्ण अन्यथा अणु
			/* IGA1 करोesn't have LCD scaling, so set it center. */
			अगर (viaparinfo->lvds_setting_info->iga_path == IGA1) अणु
				viaparinfo->lvds_setting_info->display_method =
				    LCD_CENTERING;
			पूर्ण
			viafb_lcd_set_mode(&viafbinfo->var, 0, 0,
				viaparinfo->lvds_setting_info,
				&viaparinfo->chip_info->lvds_chip_info);
		पूर्ण
	पूर्ण
	अगर (viafb_LCD2_ON) अणु
		अगर (viafb_SAMM_ON &&
			(viaparinfo->lvds_setting_info2->iga_path == IGA2)) अणु
			viafb_lcd_set_mode(&var2, cxres, cyres,
				viaparinfo->lvds_setting_info2,
				&viaparinfo->chip_info->lvds_chip_info2);
		पूर्ण अन्यथा अणु
			/* IGA1 करोesn't have LCD scaling, so set it center. */
			अगर (viaparinfo->lvds_setting_info2->iga_path == IGA1) अणु
				viaparinfo->lvds_setting_info2->display_method =
				    LCD_CENTERING;
			पूर्ण
			viafb_lcd_set_mode(&viafbinfo->var, 0, 0,
				viaparinfo->lvds_setting_info2,
				&viaparinfo->chip_info->lvds_chip_info2);
		पूर्ण
	पूर्ण

	अगर ((viaparinfo->chip_info->gfx_chip_name == UNICHROME_CX700)
	    && (viafb_LCD_ON || viafb_DVI_ON))
		set_display_channel();

	/* If set mode normally, save resolution inक्रमmation क्रम hot-plug . */
	अगर (!viafb_hotplug) अणु
		viafb_hotplug_Xres = viafbinfo->var.xres;
		viafb_hotplug_Yres = viafbinfo->var.yres;
		viafb_hotplug_bpp = viafbinfo->var.bits_per_pixel;
		viafb_hotplug_refresh = viafb_refresh;

		अगर (viafb_DVI_ON)
			viafb_DeviceStatus = DVI_Device;
		अन्यथा
			viafb_DeviceStatus = CRT_Device;
	पूर्ण
	device_on();
	अगर (!viafb_SAMM_ON)
		via_set_sync_polarity(devices, get_sync(&viafbinfo->var));
	अन्यथा अणु
		via_set_sync_polarity(viaparinfo->shared->iga1_devices,
			get_sync(&viafbinfo->var));
		via_set_sync_polarity(viaparinfo->shared->iga2_devices,
			get_sync(&var2));
	पूर्ण

	घड़ी.set_engine_pll_state(VIA_STATE_ON);
	घड़ी.set_primary_घड़ी_source(VIA_CLKSRC_X1, true);
	घड़ी.set_secondary_घड़ी_source(VIA_CLKSRC_X1, true);

#अगर_घोषित CONFIG_FB_VIA_X_COMPATIBILITY
	घड़ी.set_primary_pll_state(VIA_STATE_ON);
	घड़ी.set_primary_घड़ी_state(VIA_STATE_ON);
	घड़ी.set_secondary_pll_state(VIA_STATE_ON);
	घड़ी.set_secondary_घड़ी_state(VIA_STATE_ON);
#अन्यथा
	अगर (viaparinfo->shared->iga1_devices) अणु
		घड़ी.set_primary_pll_state(VIA_STATE_ON);
		घड़ी.set_primary_घड़ी_state(VIA_STATE_ON);
	पूर्ण अन्यथा अणु
		घड़ी.set_primary_pll_state(VIA_STATE_OFF);
		घड़ी.set_primary_घड़ी_state(VIA_STATE_OFF);
	पूर्ण

	अगर (viaparinfo->shared->iga2_devices) अणु
		घड़ी.set_secondary_pll_state(VIA_STATE_ON);
		घड़ी.set_secondary_घड़ी_state(VIA_STATE_ON);
	पूर्ण अन्यथा अणु
		घड़ी.set_secondary_pll_state(VIA_STATE_OFF);
		घड़ी.set_secondary_घड़ी_state(VIA_STATE_OFF);
	पूर्ण
#पूर्ण_अगर /*CONFIG_FB_VIA_X_COMPATIBILITY*/

	via_set_state(devices, VIA_STATE_ON);
	device_screen_on();
	वापस 1;
पूर्ण

पूर्णांक viafb_get_refresh(पूर्णांक hres, पूर्णांक vres, u32 दीर्घ_refresh)
अणु
	स्थिर काष्ठा fb_videomode *best;

	best = viafb_get_best_mode(hres, vres, दीर्घ_refresh);
	अगर (!best)
		वापस 60;

	अगर (असल(best->refresh - दीर्घ_refresh) > 3) अणु
		अगर (hres == 1200 && vres == 900)
			वापस 49; /* OLPC DCON only supports 50 Hz */
		अन्यथा
			वापस 60;
	पूर्ण

	वापस best->refresh;
पूर्ण

अटल व्योम device_off(व्योम)
अणु
	viafb_dvi_disable();
	viafb_lcd_disable();
पूर्ण

अटल व्योम device_on(व्योम)
अणु
	अगर (viafb_DVI_ON == 1)
		viafb_dvi_enable();
	अगर (viafb_LCD_ON == 1)
		viafb_lcd_enable();
पूर्ण

अटल व्योम enable_second_display_channel(व्योम)
अणु
	/* to enable second display channel. */
	viafb_ग_लिखो_reg_mask(CR6A, VIACR, 0x00, BIT6);
	viafb_ग_लिखो_reg_mask(CR6A, VIACR, BIT7, BIT7);
	viafb_ग_लिखो_reg_mask(CR6A, VIACR, BIT6, BIT6);
पूर्ण

अटल व्योम disable_second_display_channel(व्योम)
अणु
	/* to disable second display channel. */
	viafb_ग_लिखो_reg_mask(CR6A, VIACR, 0x00, BIT6);
	viafb_ग_लिखो_reg_mask(CR6A, VIACR, 0x00, BIT7);
	viafb_ग_लिखो_reg_mask(CR6A, VIACR, BIT6, BIT6);
पूर्ण

व्योम viafb_set_dpa_gfx(पूर्णांक output_पूर्णांकerface, काष्ठा GFX_DPA_SETTING\
					*p_gfx_dpa_setting)
अणु
	चयन (output_पूर्णांकerface) अणु
	हाल INTERFACE_DVP0:
		अणु
			/* DVP0 Clock Polarity and Adjust: */
			viafb_ग_लिखो_reg_mask(CR96, VIACR,
				       p_gfx_dpa_setting->DVP0, 0x0F);

			/* DVP0 Clock and Data Pads Driving: */
			viafb_ग_लिखो_reg_mask(SR1E, VIASR,
				       p_gfx_dpa_setting->DVP0ClockDri_S, BIT2);
			viafb_ग_लिखो_reg_mask(SR2A, VIASR,
				       p_gfx_dpa_setting->DVP0ClockDri_S1,
				       BIT4);
			viafb_ग_लिखो_reg_mask(SR1B, VIASR,
				       p_gfx_dpa_setting->DVP0DataDri_S, BIT1);
			viafb_ग_लिखो_reg_mask(SR2A, VIASR,
				       p_gfx_dpa_setting->DVP0DataDri_S1, BIT5);
			अवरोध;
		पूर्ण

	हाल INTERFACE_DVP1:
		अणु
			/* DVP1 Clock Polarity and Adjust: */
			viafb_ग_लिखो_reg_mask(CR9B, VIACR,
				       p_gfx_dpa_setting->DVP1, 0x0F);

			/* DVP1 Clock and Data Pads Driving: */
			viafb_ग_लिखो_reg_mask(SR65, VIASR,
				       p_gfx_dpa_setting->DVP1Driving, 0x0F);
			अवरोध;
		पूर्ण

	हाल INTERFACE_DFP_HIGH:
		अणु
			viafb_ग_लिखो_reg_mask(CR97, VIACR,
				       p_gfx_dpa_setting->DFPHigh, 0x0F);
			अवरोध;
		पूर्ण

	हाल INTERFACE_DFP_LOW:
		अणु
			viafb_ग_लिखो_reg_mask(CR99, VIACR,
				       p_gfx_dpa_setting->DFPLow, 0x0F);
			अवरोध;
		पूर्ण

	हाल INTERFACE_DFP:
		अणु
			viafb_ग_लिखो_reg_mask(CR97, VIACR,
				       p_gfx_dpa_setting->DFPHigh, 0x0F);
			viafb_ग_लिखो_reg_mask(CR99, VIACR,
				       p_gfx_dpa_setting->DFPLow, 0x0F);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम viafb_fill_var_timing_info(काष्ठा fb_var_screeninfo *var,
	स्थिर काष्ठा fb_videomode *mode)
अणु
	var->pixघड़ी = mode->pixघड़ी;
	var->xres = mode->xres;
	var->yres = mode->yres;
	var->left_margin = mode->left_margin;
	var->right_margin = mode->right_margin;
	var->hsync_len = mode->hsync_len;
	var->upper_margin = mode->upper_margin;
	var->lower_margin = mode->lower_margin;
	var->vsync_len = mode->vsync_len;
	var->sync = mode->sync;
पूर्ण
