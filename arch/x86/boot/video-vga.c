<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author H. Peter Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Common all-VGA modes
 */

#समावेश "boot.h"
#समावेश "video.h"

अटल काष्ठा mode_info vga_modes[] = अणु
	अणु VIDEO_80x25,  80, 25, 0 पूर्ण,
	अणु VIDEO_8POINT, 80, 50, 0 पूर्ण,
	अणु VIDEO_80x43,  80, 43, 0 पूर्ण,
	अणु VIDEO_80x28,  80, 28, 0 पूर्ण,
	अणु VIDEO_80x30,  80, 30, 0 पूर्ण,
	अणु VIDEO_80x34,  80, 34, 0 पूर्ण,
	अणु VIDEO_80x60,  80, 60, 0 पूर्ण,
पूर्ण;

अटल काष्ठा mode_info ega_modes[] = अणु
	अणु VIDEO_80x25,  80, 25, 0 पूर्ण,
	अणु VIDEO_8POINT, 80, 43, 0 पूर्ण,
पूर्ण;

अटल काष्ठा mode_info cga_modes[] = अणु
	अणु VIDEO_80x25,  80, 25, 0 पूर्ण,
पूर्ण;

अटल __videocard video_vga;

/* Set basic 80x25 mode */
अटल u8 vga_set_basic_mode(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;
	u8 mode;

	initregs(&ireg);

	/* Query current mode */
	ireg.ax = 0x0f00;
	पूर्णांकcall(0x10, &ireg, &oreg);
	mode = oreg.al;

	अगर (mode != 3 && mode != 7)
		mode = 3;

	/* Set the mode */
	ireg.ax = mode;		/* AH=0: set mode */
	पूर्णांकcall(0x10, &ireg, शून्य);
	करो_restore = 1;
	वापस mode;
पूर्ण

अटल व्योम vga_set_8font(व्योम)
अणु
	/* Set 8x8 font - 80x43 on EGA, 80x50 on VGA */
	काष्ठा biosregs ireg;

	initregs(&ireg);

	/* Set 8x8 font */
	ireg.ax = 0x1112;
	/* ireg.bl = 0; */
	पूर्णांकcall(0x10, &ireg, शून्य);

	/* Use alternate prपूर्णांक screen */
	ireg.ax = 0x1200;
	ireg.bl = 0x20;
	पूर्णांकcall(0x10, &ireg, शून्य);

	/* Turn off cursor emulation */
	ireg.ax = 0x1201;
	ireg.bl = 0x34;
	पूर्णांकcall(0x10, &ireg, शून्य);

	/* Cursor is scan lines 6-7 */
	ireg.ax = 0x0100;
	ireg.cx = 0x0607;
	पूर्णांकcall(0x10, &ireg, शून्य);
पूर्ण

अटल व्योम vga_set_14font(व्योम)
अणु
	/* Set 9x14 font - 80x28 on VGA */
	काष्ठा biosregs ireg;

	initregs(&ireg);

	/* Set 9x14 font */
	ireg.ax = 0x1111;
	/* ireg.bl = 0; */
	पूर्णांकcall(0x10, &ireg, शून्य);

	/* Turn off cursor emulation */
	ireg.ax = 0x1201;
	ireg.bl = 0x34;
	पूर्णांकcall(0x10, &ireg, शून्य);

	/* Cursor is scan lines 11-12 */
	ireg.ax = 0x0100;
	ireg.cx = 0x0b0c;
	पूर्णांकcall(0x10, &ireg, शून्य);
पूर्ण

अटल व्योम vga_set_80x43(व्योम)
अणु
	/* Set 80x43 mode on VGA (not EGA) */
	काष्ठा biosregs ireg;

	initregs(&ireg);

	/* Set 350 scans */
	ireg.ax = 0x1201;
	ireg.bl = 0x30;
	पूर्णांकcall(0x10, &ireg, शून्य);

	/* Reset video mode */
	ireg.ax = 0x0003;
	पूर्णांकcall(0x10, &ireg, शून्य);

	vga_set_8font();
पूर्ण

/* I/O address of the VGA CRTC */
u16 vga_crtc(व्योम)
अणु
	वापस (inb(0x3cc) & 1) ? 0x3d4 : 0x3b4;
पूर्ण

अटल व्योम vga_set_480_scanlines(व्योम)
अणु
	u16 crtc;		/* CRTC base address */
	u8  csel;		/* CRTC miscellaneous output रेजिस्टर */

	crtc = vga_crtc();

	out_idx(0x0c, crtc, 0x11); /* Vertical sync end, unlock CR0-7 */
	out_idx(0x0b, crtc, 0x06); /* Vertical total */
	out_idx(0x3e, crtc, 0x07); /* Vertical overflow */
	out_idx(0xea, crtc, 0x10); /* Vertical sync start */
	out_idx(0xdf, crtc, 0x12); /* Vertical display end */
	out_idx(0xe7, crtc, 0x15); /* Vertical blank start */
	out_idx(0x04, crtc, 0x16); /* Vertical blank end */
	csel = inb(0x3cc);
	csel &= 0x0d;
	csel |= 0xe2;
	outb(csel, 0x3c2);
पूर्ण

अटल व्योम vga_set_vertical_end(पूर्णांक lines)
अणु
	u16 crtc;		/* CRTC base address */
	u8  ovfw;		/* CRTC overflow रेजिस्टर */
	पूर्णांक end = lines-1;

	crtc = vga_crtc();

	ovfw = 0x3c | ((end >> (8-1)) & 0x02) | ((end >> (9-6)) & 0x40);

	out_idx(ovfw, crtc, 0x07); /* Vertical overflow */
	out_idx(end,  crtc, 0x12); /* Vertical display end */
पूर्ण

अटल व्योम vga_set_80x30(व्योम)
अणु
	vga_set_480_scanlines();
	vga_set_vertical_end(30*16);
पूर्ण

अटल व्योम vga_set_80x34(व्योम)
अणु
	vga_set_480_scanlines();
	vga_set_14font();
	vga_set_vertical_end(34*14);
पूर्ण

अटल व्योम vga_set_80x60(व्योम)
अणु
	vga_set_480_scanlines();
	vga_set_8font();
	vga_set_vertical_end(60*8);
पूर्ण

अटल पूर्णांक vga_set_mode(काष्ठा mode_info *mode)
अणु
	/* Set the basic mode */
	vga_set_basic_mode();

	/* Override a possibly broken BIOS */
	क्रमce_x = mode->x;
	क्रमce_y = mode->y;

	चयन (mode->mode) अणु
	हाल VIDEO_80x25:
		अवरोध;
	हाल VIDEO_8POINT:
		vga_set_8font();
		अवरोध;
	हाल VIDEO_80x43:
		vga_set_80x43();
		अवरोध;
	हाल VIDEO_80x28:
		vga_set_14font();
		अवरोध;
	हाल VIDEO_80x30:
		vga_set_80x30();
		अवरोध;
	हाल VIDEO_80x34:
		vga_set_80x34();
		अवरोध;
	हाल VIDEO_80x60:
		vga_set_80x60();
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Note: this probe includes basic inक्रमmation required by all
 * प्रणालीs.  It should be executed first, by making sure
 * video-vga.c is listed first in the Makefile.
 */
अटल पूर्णांक vga_probe(व्योम)
अणु
	अटल स्थिर अक्षर *card_name[] = अणु
		"CGA/MDA/HGC", "EGA", "VGA"
	पूर्ण;
	अटल काष्ठा mode_info *mode_lists[] = अणु
		cga_modes,
		ega_modes,
		vga_modes,
	पूर्ण;
	अटल पूर्णांक mode_count[] = अणु
		ARRAY_SIZE(cga_modes),
		ARRAY_SIZE(ega_modes),
		ARRAY_SIZE(vga_modes),
	पूर्ण;

	काष्ठा biosregs ireg, oreg;

	initregs(&ireg);

	ireg.ax = 0x1200;
	ireg.bl = 0x10;		/* Check EGA/VGA */
	पूर्णांकcall(0x10, &ireg, &oreg);

#अगर_अघोषित _WAKEUP
	boot_params.screen_info.orig_video_ega_bx = oreg.bx;
#पूर्ण_अगर

	/* If we have MDA/CGA/HGC then BL will be unchanged at 0x10 */
	अगर (oreg.bl != 0x10) अणु
		/* EGA/VGA */
		ireg.ax = 0x1a00;
		पूर्णांकcall(0x10, &ireg, &oreg);

		अगर (oreg.al == 0x1a) अणु
			adapter = ADAPTER_VGA;
#अगर_अघोषित _WAKEUP
			boot_params.screen_info.orig_video_isVGA = 1;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			adapter = ADAPTER_EGA;
		पूर्ण
	पूर्ण अन्यथा अणु
		adapter = ADAPTER_CGA;
	पूर्ण

	video_vga.modes = mode_lists[adapter];
	video_vga.card_name = card_name[adapter];
	वापस mode_count[adapter];
पूर्ण

अटल __videocard video_vga = अणु
	.card_name	= "VGA",
	.probe		= vga_probe,
	.set_mode	= vga_set_mode,
पूर्ण;
