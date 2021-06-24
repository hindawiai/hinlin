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
 * Select video mode
 */

#समावेश <uapi/यंत्र/boot.h>

#समावेश "boot.h"
#समावेश "video.h"
#समावेश "vesa.h"

अटल u16 video_segment;

अटल व्योम store_cursor_position(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;

	initregs(&ireg);
	ireg.ah = 0x03;
	पूर्णांकcall(0x10, &ireg, &oreg);

	boot_params.screen_info.orig_x = oreg.dl;
	boot_params.screen_info.orig_y = oreg.dh;

	अगर (oreg.ch & 0x20)
		boot_params.screen_info.flags |= VIDEO_FLAGS_NOCURSOR;

	अगर ((oreg.ch & 0x1f) > (oreg.cl & 0x1f))
		boot_params.screen_info.flags |= VIDEO_FLAGS_NOCURSOR;
पूर्ण

अटल व्योम store_video_mode(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;

	/* N.B.: the saving of the video page here is a bit silly,
	   since we pretty much assume page 0 everywhere. */
	initregs(&ireg);
	ireg.ah = 0x0f;
	पूर्णांकcall(0x10, &ireg, &oreg);

	/* Not all BIOSes are clean with respect to the top bit */
	boot_params.screen_info.orig_video_mode = oreg.al & 0x7f;
	boot_params.screen_info.orig_video_page = oreg.bh;
पूर्ण

/*
 * Store the video mode parameters क्रम later usage by the kernel.
 * This is करोne by asking the BIOS except क्रम the rows/columns
 * parameters in the शेष 80x25 mode -- these are set directly,
 * because some very obscure BIOSes supply insane values.
 */
अटल व्योम store_mode_params(व्योम)
अणु
	u16 font_size;
	पूर्णांक x, y;

	/* For graphics mode, it is up to the mode-setting driver
	   (currently only video-vesa.c) to store the parameters */
	अगर (graphic_mode)
		वापस;

	store_cursor_position();
	store_video_mode();

	अगर (boot_params.screen_info.orig_video_mode == 0x07) अणु
		/* MDA, HGC, or VGA in monochrome mode */
		video_segment = 0xb000;
	पूर्ण अन्यथा अणु
		/* CGA, EGA, VGA and so क्रमth */
		video_segment = 0xb800;
	पूर्ण

	set_fs(0);
	font_size = rdfs16(0x485); /* Font size, BIOS area */
	boot_params.screen_info.orig_video_poपूर्णांकs = font_size;

	x = rdfs16(0x44a);
	y = (adapter == ADAPTER_CGA) ? 25 : rdfs8(0x484)+1;

	अगर (क्रमce_x)
		x = क्रमce_x;
	अगर (क्रमce_y)
		y = क्रमce_y;

	boot_params.screen_info.orig_video_cols  = x;
	boot_params.screen_info.orig_video_lines = y;
पूर्ण

अटल अचिन्हित पूर्णांक get_entry(व्योम)
अणु
	अक्षर entry_buf[4];
	पूर्णांक i, len = 0;
	पूर्णांक key;
	अचिन्हित पूर्णांक v;

	करो अणु
		key = अक्षर_लो();

		अगर (key == '\b') अणु
			अगर (len > 0) अणु
				माला_दो("\b \b");
				len--;
			पूर्ण
		पूर्ण अन्यथा अगर ((key >= '0' && key <= '9') ||
			   (key >= 'A' && key <= 'Z') ||
			   (key >= 'a' && key <= 'z')) अणु
			अगर (len < माप(entry_buf)) अणु
				entry_buf[len++] = key;
				अक्षर_दो(key);
			पूर्ण
		पूर्ण
	पूर्ण जबतक (key != '\r');
	अक्षर_दो('\n');

	अगर (len == 0)
		वापस VIDEO_CURRENT_MODE; /* Default */

	v = 0;
	क्रम (i = 0; i < len; i++) अणु
		v <<= 4;
		key = entry_buf[i] | 0x20;
		v += (key > '9') ? key-'a'+10 : key-'0';
	पूर्ण

	वापस v;
पूर्ण

अटल व्योम display_menu(व्योम)
अणु
	काष्ठा card_info *card;
	काष्ठा mode_info *mi;
	अक्षर ch;
	पूर्णांक i;
	पूर्णांक nmodes;
	पूर्णांक modes_per_line;
	पूर्णांक col;

	nmodes = 0;
	क्रम (card = video_cards; card < video_cards_end; card++)
		nmodes += card->nmodes;

	modes_per_line = 1;
	अगर (nmodes >= 20)
		modes_per_line = 3;

	क्रम (col = 0; col < modes_per_line; col++)
		माला_दो("Mode: Resolution:  Type: ");
	अक्षर_दो('\n');

	col = 0;
	ch = '0';
	क्रम (card = video_cards; card < video_cards_end; card++) अणु
		mi = card->modes;
		क्रम (i = 0; i < card->nmodes; i++, mi++) अणु
			अक्षर resbuf[32];
			पूर्णांक visible = mi->x && mi->y;
			u16 mode_id = mi->mode ? mi->mode :
				(mi->y << 8)+mi->x;

			अगर (!visible)
				जारी; /* Hidden mode */

			अगर (mi->depth)
				प्र_लिखो(resbuf, "%dx%d", mi->y, mi->depth);
			अन्यथा
				प्र_लिखो(resbuf, "%d", mi->y);

			म_लिखो("%c %03X %4dx%-7s %-6s",
			       ch, mode_id, mi->x, resbuf, card->card_name);
			col++;
			अगर (col >= modes_per_line) अणु
				अक्षर_दो('\n');
				col = 0;
			पूर्ण

			अगर (ch == '9')
				ch = 'a';
			अन्यथा अगर (ch == 'z' || ch == ' ')
				ch = ' '; /* Out of keys... */
			अन्यथा
				ch++;
		पूर्ण
	पूर्ण
	अगर (col)
		अक्षर_दो('\n');
पूर्ण

#घोषणा H(x)	((x)-'a'+10)
#घोषणा SCAN	((H('s')<<12)+(H('c')<<8)+(H('a')<<4)+H('n'))

अटल अचिन्हित पूर्णांक mode_menu(व्योम)
अणु
	पूर्णांक key;
	अचिन्हित पूर्णांक sel;

	माला_दो("Press <ENTER> to see video modes available, "
	     "<SPACE> to continue, or wait 30 sec\n");

	kbd_flush();
	जबतक (1) अणु
		key = अक्षर_लो_समयout();
		अगर (key == ' ' || key == 0)
			वापस VIDEO_CURRENT_MODE; /* Default */
		अगर (key == '\r')
			अवरोध;
		अक्षर_दो('\a');	/* Beep! */
	पूर्ण


	क्रम (;;) अणु
		display_menu();

		माला_दो("Enter a video mode or \"scan\" to scan for "
		     "additional modes: ");
		sel = get_entry();
		अगर (sel != SCAN)
			वापस sel;

		probe_cards(1);
	पूर्ण
पूर्ण

/* Save screen content to the heap */
अटल काष्ठा saved_screen अणु
	पूर्णांक x, y;
	पूर्णांक curx, cury;
	u16 *data;
पूर्ण saved;

अटल व्योम save_screen(व्योम)
अणु
	/* Should be called after store_mode_params() */
	saved.x = boot_params.screen_info.orig_video_cols;
	saved.y = boot_params.screen_info.orig_video_lines;
	saved.curx = boot_params.screen_info.orig_x;
	saved.cury = boot_params.screen_info.orig_y;

	अगर (!heap_मुक्त(saved.x*saved.y*माप(u16)+512))
		वापस;		/* Not enough heap to save the screen */

	saved.data = GET_HEAP(u16, saved.x*saved.y);

	set_fs(video_segment);
	copy_from_fs(saved.data, 0, saved.x*saved.y*माप(u16));
पूर्ण

अटल व्योम restore_screen(व्योम)
अणु
	/* Should be called after store_mode_params() */
	पूर्णांक xs = boot_params.screen_info.orig_video_cols;
	पूर्णांक ys = boot_params.screen_info.orig_video_lines;
	पूर्णांक y;
	addr_t dst = 0;
	u16 *src = saved.data;
	काष्ठा biosregs ireg;

	अगर (graphic_mode)
		वापस;		/* Can't restore onto a graphic mode */

	अगर (!src)
		वापस;		/* No saved screen contents */

	/* Restore screen contents */

	set_fs(video_segment);
	क्रम (y = 0; y < ys; y++) अणु
		पूर्णांक npad;

		अगर (y < saved.y) अणु
			पूर्णांक copy = (xs < saved.x) ? xs : saved.x;
			copy_to_fs(dst, src, copy*माप(u16));
			dst += copy*माप(u16);
			src += saved.x;
			npad = (xs < saved.x) ? 0 : xs-saved.x;
		पूर्ण अन्यथा अणु
			npad = xs;
		पूर्ण

		/* Writes "npad" blank अक्षरacters to
		   video_segment:dst and advances dst */
		यंत्र अस्थिर("pushw %%es ; "
			     "movw %2,%%es ; "
			     "shrw %%cx ; "
			     "jnc 1f ; "
			     "stosw \n\t"
			     "1: rep;stosl ; "
			     "popw %%es"
			     : "+D" (dst), "+c" (npad)
			     : "bdS" (video_segment),
			       "a" (0x07200720));
	पूर्ण

	/* Restore cursor position */
	अगर (saved.curx >= xs)
		saved.curx = xs-1;
	अगर (saved.cury >= ys)
		saved.cury = ys-1;

	initregs(&ireg);
	ireg.ah = 0x02;		/* Set cursor position */
	ireg.dh = saved.cury;
	ireg.dl = saved.curx;
	पूर्णांकcall(0x10, &ireg, शून्य);

	store_cursor_position();
पूर्ण

व्योम set_video(व्योम)
अणु
	u16 mode = boot_params.hdr.vid_mode;

	RESET_HEAP();

	store_mode_params();
	save_screen();
	probe_cards(0);

	क्रम (;;) अणु
		अगर (mode == ASK_VGA)
			mode = mode_menu();

		अगर (!set_mode(mode))
			अवरोध;

		म_लिखो("Undefined video mode number: %x\n", mode);
		mode = ASK_VGA;
	पूर्ण
	boot_params.hdr.vid_mode = mode;
	vesa_store_edid();
	store_mode_params();

	अगर (करो_restore)
		restore_screen();
पूर्ण
