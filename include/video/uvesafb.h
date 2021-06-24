<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _UVESAFB_H
#घोषणा _UVESAFB_H

#समावेश <uapi/video/uvesafb.h>


/* VBE CRTC Info Block */
काष्ठा vbe_crtc_ib अणु
	u16 horiz_total;
	u16 horiz_start;
	u16 horiz_end;
	u16 vert_total;
	u16 vert_start;
	u16 vert_end;
	u8  flags;
	u32 pixel_घड़ी;
	u16 refresh_rate;
	u8  reserved[40];
पूर्ण __attribute__ ((packed));

#घोषणा VBE_MODE_VGACOMPAT	0x20
#घोषणा VBE_MODE_COLOR		0x08
#घोषणा VBE_MODE_SUPPORTEDHW	0x01
#घोषणा VBE_MODE_GRAPHICS	0x10
#घोषणा VBE_MODE_LFB		0x80

#घोषणा VBE_MODE_MASK		(VBE_MODE_COLOR | VBE_MODE_SUPPORTEDHW | \
				VBE_MODE_GRAPHICS | VBE_MODE_LFB)

/* VBE Mode Info Block */
काष्ठा vbe_mode_ib अणु
	/* क्रम all VBE revisions */
	u16 mode_attr;
	u8  winA_attr;
	u8  winB_attr;
	u16 win_granularity;
	u16 win_size;
	u16 winA_seg;
	u16 winB_seg;
	u32 win_func_ptr;
	u16 bytes_per_scan_line;

	/* क्रम VBE 1.2+ */
	u16 x_res;
	u16 y_res;
	u8  x_अक्षर_size;
	u8  y_अक्षर_size;
	u8  planes;
	u8  bits_per_pixel;
	u8  banks;
	u8  memory_model;
	u8  bank_size;
	u8  image_pages;
	u8  reserved1;

	/* Direct color fields क्रम direct/6 and YUV/7 memory models. */
	/* Offsets are bit positions of lsb in the mask. */
	u8  red_len;
	u8  red_off;
	u8  green_len;
	u8  green_off;
	u8  blue_len;
	u8  blue_off;
	u8  rsvd_len;
	u8  rsvd_off;
	u8  direct_color_info;	/* direct color mode attributes */

	/* क्रम VBE 2.0+ */
	u32 phys_base_ptr;
	u8  reserved2[6];

	/* क्रम VBE 3.0+ */
	u16 lin_bytes_per_scan_line;
	u8  bnk_image_pages;
	u8  lin_image_pages;
	u8  lin_red_len;
	u8  lin_red_off;
	u8  lin_green_len;
	u8  lin_green_off;
	u8  lin_blue_len;
	u8  lin_blue_off;
	u8  lin_rsvd_len;
	u8  lin_rsvd_off;
	u32 max_pixel_घड़ी;
	u16 mode_id;
	u8  depth;
पूर्ण __attribute__ ((packed));

#घोषणा UVESAFB_DEFAULT_MODE "640x480-16"

/* How दीर्घ to रुको क्रम a reply from userspace [ms] */
#घोषणा UVESAFB_TIMEOUT 5000

/* Max number of concurrent tasks */
#घोषणा UVESAFB_TASKS_MAX 16

#घोषणा dac_reg	(0x3c8)
#घोषणा dac_val	(0x3c9)

काष्ठा uvesafb_pal_entry अणु
	u_अक्षर blue, green, red, pad;
पूर्ण __attribute__ ((packed));

काष्ठा uvesafb_ktask अणु
	काष्ठा uvesafb_task t;
	व्योम *buf;
	काष्ठा completion *करोne;
	u32 ack;
पूर्ण;

अटल पूर्णांक uvesafb_exec(काष्ठा uvesafb_ktask *tsk);

#घोषणा UVESAFB_EXACT_RES	1
#घोषणा UVESAFB_EXACT_DEPTH	2

काष्ठा uvesafb_par अणु
	काष्ठा vbe_ib vbe_ib;		/* VBE Info Block */
	काष्ठा vbe_mode_ib *vbe_modes;	/* list of supported VBE modes */
	पूर्णांक vbe_modes_cnt;

	u8 nocrtc;
	u8 ypan;			/* 0 - nothing, 1 - ypan, 2 - ywrap */
	u8 pmi_setpal;			/* PMI क्रम palette changes */
	u16 *pmi_base;			/* रक्षित mode पूर्णांकerface location */
	व्योम *pmi_start;
	व्योम *pmi_pal;
	u8 *vbe_state_orig;		/*
					 * original hardware state, beक्रमe the
					 * driver was loaded
					 */
	u8 *vbe_state_saved;		/* state saved by fb_save_state */
	पूर्णांक vbe_state_size;
	atomic_t ref_count;

	पूर्णांक mode_idx;
	काष्ठा vbe_crtc_ib crtc;
	पूर्णांक mtrr_handle;
पूर्ण;

#पूर्ण_अगर /* _UVESAFB_H */
