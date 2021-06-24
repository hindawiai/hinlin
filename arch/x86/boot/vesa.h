<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* ----------------------------------------------------------------------- *
 *
 *   Copyright 1999-2007 H. Peter Anvin - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

#अगर_अघोषित BOOT_VESA_H
#घोषणा BOOT_VESA_H

प्रकार काष्ठा अणु
	u16 off, seg;
पूर्ण far_ptr;

/* VESA General Inक्रमmation table */
काष्ठा vesa_general_info अणु
	u32 signature;		/* 0 Magic number = "VESA" */
	u16 version;		/* 4 */
	far_ptr venकरोr_string;	/* 6 */
	u32 capabilities;	/* 10 */
	far_ptr video_mode_ptr;	/* 14 */
	u16 total_memory;	/* 18 */

	u8 reserved[236];	/* 20 */
पूर्ण __attribute__ ((packed));

#घोषणा VESA_MAGIC ('V' + ('E' << 8) + ('S' << 16) + ('A' << 24))

काष्ठा vesa_mode_info अणु
	u16 mode_attr;		/* 0 */
	u8 win_attr[2];		/* 2 */
	u16 win_grain;		/* 4 */
	u16 win_size;		/* 6 */
	u16 win_seg[2];		/* 8 */
	far_ptr win_scheme;	/* 12 */
	u16 logical_scan;	/* 16 */

	u16 h_res;		/* 18 */
	u16 v_res;		/* 20 */
	u8 अक्षर_width;		/* 22 */
	u8 अक्षर_height;		/* 23 */
	u8 memory_planes;	/* 24 */
	u8 bpp;			/* 25 */
	u8 banks;		/* 26 */
	u8 memory_layout;	/* 27 */
	u8 bank_size;		/* 28 */
	u8 image_planes;	/* 29 */
	u8 page_function;	/* 30 */

	u8 rmask;		/* 31 */
	u8 rpos;		/* 32 */
	u8 gmask;		/* 33 */
	u8 gpos;		/* 34 */
	u8 bmask;		/* 35 */
	u8 bpos;		/* 36 */
	u8 resv_mask;		/* 37 */
	u8 resv_pos;		/* 38 */
	u8 dcm_info;		/* 39 */

	u32 lfb_ptr;		/* 40 Linear frame buffer address */
	u32 offscreen_ptr;	/* 44 Offscreen memory address */
	u16 offscreen_size;	/* 48 */

	u8 reserved[206];	/* 50 */
पूर्ण __attribute__ ((packed));

#पूर्ण_अगर				/* LIB_SYS_VESA_H */
