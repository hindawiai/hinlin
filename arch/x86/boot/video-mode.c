<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007-2008 rPath, Inc. - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * arch/i386/boot/video-mode.c
 *
 * Set the video mode.  This is separated out पूर्णांकo a dअगरferent
 * file in order to be shared with the ACPI wakeup code.
 */

#समावेश "boot.h"
#समावेश "video.h"
#समावेश "vesa.h"

#समावेश <uapi/यंत्र/boot.h>

/*
 * Common variables
 */
पूर्णांक adapter;		/* 0=CGA/MDA/HGC, 1=EGA, 2=VGA+ */
पूर्णांक क्रमce_x, क्रमce_y;	/* Don't query the BIOS क्रम cols/rows */
पूर्णांक करो_restore;		/* Screen contents changed during mode flip */
पूर्णांक graphic_mode;	/* Graphic mode with linear frame buffer */

/* Probe the video drivers and have them generate their mode lists. */
व्योम probe_cards(पूर्णांक unsafe)
अणु
	काष्ठा card_info *card;
	अटल u8 probed[2];

	अगर (probed[unsafe])
		वापस;

	probed[unsafe] = 1;

	क्रम (card = video_cards; card < video_cards_end; card++) अणु
		अगर (card->unsafe == unsafe) अणु
			अगर (card->probe)
				card->nmodes = card->probe();
			अन्यथा
				card->nmodes = 0;
		पूर्ण
	पूर्ण
पूर्ण

/* Test अगर a mode is defined */
पूर्णांक mode_defined(u16 mode)
अणु
	काष्ठा card_info *card;
	काष्ठा mode_info *mi;
	पूर्णांक i;

	क्रम (card = video_cards; card < video_cards_end; card++) अणु
		mi = card->modes;
		क्रम (i = 0; i < card->nmodes; i++, mi++) अणु
			अगर (mi->mode == mode)
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Set mode (without recalc) */
अटल पूर्णांक raw_set_mode(u16 mode, u16 *real_mode)
अणु
	पूर्णांक nmode, i;
	काष्ठा card_info *card;
	काष्ठा mode_info *mi;

	/* Drop the recalc bit अगर set */
	mode &= ~VIDEO_RECALC;

	/* Scan क्रम mode based on fixed ID, position, or resolution */
	nmode = 0;
	क्रम (card = video_cards; card < video_cards_end; card++) अणु
		mi = card->modes;
		क्रम (i = 0; i < card->nmodes; i++, mi++) अणु
			पूर्णांक visible = mi->x || mi->y;

			अगर ((mode == nmode && visible) ||
			    mode == mi->mode ||
			    mode == (mi->y << 8)+mi->x) अणु
				*real_mode = mi->mode;
				वापस card->set_mode(mi);
			पूर्ण

			अगर (visible)
				nmode++;
		पूर्ण
	पूर्ण

	/* Nothing found?  Is it an "exceptional" (unprobed) mode? */
	क्रम (card = video_cards; card < video_cards_end; card++) अणु
		अगर (mode >= card->xmode_first &&
		    mode < card->xmode_first+card->xmode_n) अणु
			काष्ठा mode_info mix;
			*real_mode = mix.mode = mode;
			mix.x = mix.y = 0;
			वापस card->set_mode(&mix);
		पूर्ण
	पूर्ण

	/* Otherwise, failure... */
	वापस -1;
पूर्ण

/*
 * Recalculate the vertical video cutoff (hack!)
 */
अटल व्योम vga_recalc_vertical(व्योम)
अणु
	अचिन्हित पूर्णांक font_size, rows;
	u16 crtc;
	u8 pt, ov;

	set_fs(0);
	font_size = rdfs8(0x485); /* BIOS: font size (pixels) */
	rows = क्रमce_y ? क्रमce_y : rdfs8(0x484)+1; /* Text rows */

	rows *= font_size;	/* Visible scan lines */
	rows--;			/* ... minus one */

	crtc = vga_crtc();

	pt = in_idx(crtc, 0x11);
	pt &= ~0x80;		/* Unlock CR0-7 */
	out_idx(pt, crtc, 0x11);

	out_idx((u8)rows, crtc, 0x12); /* Lower height रेजिस्टर */

	ov = in_idx(crtc, 0x07); /* Overflow रेजिस्टर */
	ov &= 0xbd;
	ov |= (rows >> (8-1)) & 0x02;
	ov |= (rows >> (9-6)) & 0x40;
	out_idx(ov, crtc, 0x07);
पूर्ण

/* Set mode (with recalc अगर specअगरied) */
पूर्णांक set_mode(u16 mode)
अणु
	पूर्णांक rv;
	u16 real_mode;

	/* Very special mode numbers... */
	अगर (mode == VIDEO_CURRENT_MODE)
		वापस 0;	/* Nothing to करो... */
	अन्यथा अगर (mode == NORMAL_VGA)
		mode = VIDEO_80x25;
	अन्यथा अगर (mode == EXTENDED_VGA)
		mode = VIDEO_8POINT;

	rv = raw_set_mode(mode, &real_mode);
	अगर (rv)
		वापस rv;

	अगर (mode & VIDEO_RECALC)
		vga_recalc_vertical();

	/* Save the canonical mode number क्रम the kernel, not
	   an alias, size specअगरication or menu position */
#अगर_अघोषित _WAKEUP
	boot_params.hdr.vid_mode = real_mode;
#पूर्ण_अगर
	वापस 0;
पूर्ण
