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
 * Standard video BIOS modes
 *
 * We have two options क्रम this; silent and scanned.
 */

#समावेश "boot.h"
#समावेश "video.h"

अटल __videocard video_bios;

/* Set a conventional BIOS mode */
अटल पूर्णांक set_bios_mode(u8 mode);

अटल पूर्णांक bios_set_mode(काष्ठा mode_info *mi)
अणु
	वापस set_bios_mode(mi->mode - VIDEO_FIRST_BIOS);
पूर्ण

अटल पूर्णांक set_bios_mode(u8 mode)
अणु
	काष्ठा biosregs ireg, oreg;
	u8 new_mode;

	initregs(&ireg);
	ireg.al = mode;		/* AH=0x00 Set Video Mode */
	पूर्णांकcall(0x10, &ireg, शून्य);

	ireg.ah = 0x0f;		/* Get Current Video Mode */
	पूर्णांकcall(0x10, &ireg, &oreg);

	करो_restore = 1;		/* Assume video contents were lost */

	/* Not all BIOSes are clean with the top bit */
	new_mode = oreg.al & 0x7f;

	अगर (new_mode == mode)
		वापस 0;	/* Mode change OK */

#अगर_अघोषित _WAKEUP
	अगर (new_mode != boot_params.screen_info.orig_video_mode) अणु
		/* Mode setting failed, but we didn't end up where we
		   started.  That's bad.  Try to revert to the original
		   video mode. */
		ireg.ax = boot_params.screen_info.orig_video_mode;
		पूर्णांकcall(0x10, &ireg, शून्य);
	पूर्ण
#पूर्ण_अगर
	वापस -1;
पूर्ण

अटल पूर्णांक bios_probe(व्योम)
अणु
	u8 mode;
#अगर_घोषित _WAKEUP
	u8 saved_mode = 0x03;
#अन्यथा
	u8 saved_mode = boot_params.screen_info.orig_video_mode;
#पूर्ण_अगर
	u16 crtc;
	काष्ठा mode_info *mi;
	पूर्णांक nmodes = 0;

	अगर (adapter != ADAPTER_EGA && adapter != ADAPTER_VGA)
		वापस 0;

	set_fs(0);
	crtc = vga_crtc();

	video_bios.modes = GET_HEAP(काष्ठा mode_info, 0);

	क्रम (mode = 0x14; mode <= 0x7f; mode++) अणु
		अगर (!heap_मुक्त(माप(काष्ठा mode_info)))
			अवरोध;

		अगर (mode_defined(VIDEO_FIRST_BIOS+mode))
			जारी;

		अगर (set_bios_mode(mode))
			जारी;

		/* Try to verअगरy that it's a text mode. */

		/* Attribute Controller: make graphics controller disabled */
		अगर (in_idx(0x3c0, 0x10) & 0x01)
			जारी;

		/* Graphics Controller: verअगरy Alpha addressing enabled */
		अगर (in_idx(0x3ce, 0x06) & 0x01)
			जारी;

		/* CRTC cursor location low should be zero(?) */
		अगर (in_idx(crtc, 0x0f))
			जारी;

		mi = GET_HEAP(काष्ठा mode_info, 1);
		mi->mode = VIDEO_FIRST_BIOS+mode;
		mi->depth = 0;	/* text */
		mi->x = rdfs16(0x44a);
		mi->y = rdfs8(0x484)+1;
		nmodes++;
	पूर्ण

	set_bios_mode(saved_mode);

	वापस nmodes;
पूर्ण

अटल __videocard video_bios =
अणु
	.card_name	= "BIOS",
	.probe		= bios_probe,
	.set_mode	= bios_set_mode,
	.unsafe		= 1,
	.xmode_first	= VIDEO_FIRST_BIOS,
	.xmode_n	= 0x80,
पूर्ण;
