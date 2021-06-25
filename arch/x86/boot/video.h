<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * Header file क्रम the real-mode video probing code
 */

#अगर_अघोषित BOOT_VIDEO_H
#घोषणा BOOT_VIDEO_H

#समावेश <linux/types.h>

/*
 * This code uses an extended set of video mode numbers. These include:
 * Aliases क्रम standard modes
 *      NORMAL_VGA (-1)
 *      EXTENDED_VGA (-2)
 *      ASK_VGA (-3)
 * Video modes numbered by menu position -- NOT RECOMMENDED because of lack
 * of compatibility when extending the table. These are between 0x00 and 0xff.
 */
#घोषणा VIDEO_FIRST_MENU 0x0000

/* Standard BIOS video modes (BIOS number + 0x0100) */
#घोषणा VIDEO_FIRST_BIOS 0x0100

/* VESA BIOS video modes (VESA number + 0x0200) */
#घोषणा VIDEO_FIRST_VESA 0x0200

/* Video7 special modes (BIOS number + 0x0900) */
#घोषणा VIDEO_FIRST_V7 0x0900

/* Special video modes */
#घोषणा VIDEO_FIRST_SPECIAL 0x0f00
#घोषणा VIDEO_80x25 0x0f00
#घोषणा VIDEO_8POINT 0x0f01
#घोषणा VIDEO_80x43 0x0f02
#घोषणा VIDEO_80x28 0x0f03
#घोषणा VIDEO_CURRENT_MODE 0x0f04
#घोषणा VIDEO_80x30 0x0f05
#घोषणा VIDEO_80x34 0x0f06
#घोषणा VIDEO_80x60 0x0f07
#घोषणा VIDEO_GFX_HACK 0x0f08
#घोषणा VIDEO_LAST_SPECIAL 0x0f09

/* Video modes given by resolution */
#घोषणा VIDEO_FIRST_RESOLUTION 0x1000

/* The "recalculate timings" flag */
#घोषणा VIDEO_RECALC 0x8000

व्योम store_screen(व्योम);
#घोषणा DO_STORE() store_screen()

/*
 * Mode table काष्ठाures
 */

काष्ठा mode_info अणु
	u16 mode;		/* Mode number (vga= style) */
	u16 x, y;		/* Width, height */
	u16 depth;		/* Bits per pixel, 0 क्रम text mode */
पूर्ण;

काष्ठा card_info अणु
	स्थिर अक्षर *card_name;
	पूर्णांक (*set_mode)(काष्ठा mode_info *mode);
	पूर्णांक (*probe)(व्योम);
	काष्ठा mode_info *modes;
	पूर्णांक nmodes;		/* Number of probed modes so far */
	पूर्णांक unsafe;		/* Probing is unsafe, only करो after "scan" */
	u16 xmode_first;	/* Unprobed modes to try to call anyway */
	u16 xmode_n;		/* Size of unprobed mode range */
पूर्ण;

#घोषणा __videocard काष्ठा card_info __section(".videocards") __attribute__((used))
बाह्य काष्ठा card_info video_cards[], video_cards_end[];

पूर्णांक mode_defined(u16 mode);	/* video.c */

/* Basic video inक्रमmation */
#घोषणा ADAPTER_CGA	0	/* CGA/MDA/HGC */
#घोषणा ADAPTER_EGA	1
#घोषणा ADAPTER_VGA	2

बाह्य पूर्णांक adapter;
बाह्य पूर्णांक क्रमce_x, क्रमce_y;	/* Don't query the BIOS क्रम cols/rows */
बाह्य पूर्णांक करो_restore;		/* Restore screen contents */
बाह्य पूर्णांक graphic_mode;	/* Graphics mode with linear frame buffer */

/* Accessing VGA indexed रेजिस्टरs */
अटल अंतरभूत u8 in_idx(u16 port, u8 index)
अणु
	outb(index, port);
	वापस inb(port+1);
पूर्ण

अटल अंतरभूत व्योम out_idx(u8 v, u16 port, u8 index)
अणु
	outw(index+(v << 8), port);
पूर्ण

/* Writes a value to an indexed port and then पढ़ोs the port again */
अटल अंतरभूत u8 tst_idx(u8 v, u16 port, u8 index)
अणु
	out_idx(port, index, v);
	वापस in_idx(port, index);
पूर्ण

/* Get the I/O port of the VGA CRTC */
u16 vga_crtc(व्योम);		/* video-vga.c */

#पूर्ण_अगर /* BOOT_VIDEO_H */
