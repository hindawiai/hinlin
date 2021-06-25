<शैली गुरु>
/*
 *  linux/drivers/video/vgacon.c -- Low level VGA based console driver
 *
 *	Created 28 Sep 1997 by Geert Uytterhoeven
 *
 *	Rewritten by Martin Mares <mj@ucw.cz>, July 1998
 *
 *  This file is based on the old console.c, vga.c and vesa_blank.c drivers.
 *
 *	Copyright (C) 1991, 1992  Linus Torvalds
 *			    1995  Jay Estabrook
 *
 *	User definable mapping table and font loading by Eugene G. Crosser,
 *	<crosser@average.org>
 *
 *	Improved loadable font/UTF-8 support by H. Peter Anvin
 *	Feb-Sep 1995 <peter.anvin@linux.org>
 *
 *	Colour palette handling, by Simon Tatham
 *	17-Jun-95 <sgt20@cam.ac.uk>
 *
 *	अगर 512 अक्षर mode is alपढ़ोy enabled करोn't re-enable it,
 *	because it causes screen to flicker, by Mitja Horvat
 *	5-May-96 <mitja.horvat@guest.arnes.si>
 *
 *	Use 2 outw instead of 4 outb_p to reduce erroneous text
 *	flashing on RHS of screen during heavy console scrolling .
 *	Oct 1996, Paul Gorपंचांगaker.
 *
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/माला.स>
#समावेश <linux/kd.h>
#समावेश <linux/slab.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/sched.h>
#समावेश <linux/selection.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/screen_info.h>
#समावेश <video/vga.h>
#समावेश <यंत्र/पन.स>

अटल DEFINE_RAW_SPINLOCK(vga_lock);
अटल पूर्णांक cursor_size_lastfrom;
अटल पूर्णांक cursor_size_lastto;
अटल u32 vgacon_xres;
अटल u32 vgacon_yres;
अटल काष्ठा vgastate vgastate;

#घोषणा BLANK 0x0020

#घोषणा VGA_FONTWIDTH       8   /* VGA करोes not support fontwidths != 8 */
/*
 *  Interface used by the world
 */

अटल स्थिर अक्षर *vgacon_startup(व्योम);
अटल व्योम vgacon_init(काष्ठा vc_data *c, पूर्णांक init);
अटल व्योम vgacon_deinit(काष्ठा vc_data *c);
अटल व्योम vgacon_cursor(काष्ठा vc_data *c, पूर्णांक mode);
अटल पूर्णांक vgacon_चयन(काष्ठा vc_data *c);
अटल पूर्णांक vgacon_blank(काष्ठा vc_data *c, पूर्णांक blank, पूर्णांक mode_चयन);
अटल व्योम vgacon_scrolldelta(काष्ठा vc_data *c, पूर्णांक lines);
अटल पूर्णांक vgacon_set_origin(काष्ठा vc_data *c);
अटल व्योम vgacon_save_screen(काष्ठा vc_data *c);
अटल व्योम vgacon_invert_region(काष्ठा vc_data *c, u16 * p, पूर्णांक count);
अटल काष्ठा uni_pagedir *vgacon_uni_pagedir;
अटल पूर्णांक vgacon_refcount;

/* Description of the hardware situation */
अटल अचिन्हित दीर्घ	vga_vram_base		__पढ़ो_mostly;	/* Base of video memory */
अटल अचिन्हित दीर्घ	vga_vram_end		__पढ़ो_mostly;	/* End of video memory */
अटल अचिन्हित पूर्णांक	vga_vram_size		__पढ़ो_mostly;	/* Size of video memory */
अटल u16		vga_video_port_reg	__पढ़ो_mostly;	/* Video रेजिस्टर select port */
अटल u16		vga_video_port_val	__पढ़ो_mostly;	/* Video रेजिस्टर value port */
अटल अचिन्हित पूर्णांक	vga_video_num_columns;			/* Number of text columns */
अटल अचिन्हित पूर्णांक	vga_video_num_lines;			/* Number of text lines */
अटल bool		vga_can_करो_color;			/* Do we support colors? */
अटल अचिन्हित पूर्णांक	vga_शेष_font_height __पढ़ो_mostly;	/* Height of शेष screen font */
अटल अचिन्हित अक्षर	vga_video_type		__पढ़ो_mostly;	/* Card type */
अटल पूर्णांक		vga_vesa_blanked;
अटल bool 		vga_palette_blanked;
अटल bool 		vga_is_gfx;
अटल bool 		vga_512_अक्षरs;
अटल पूर्णांक 		vga_video_font_height;
अटल पूर्णांक 		vga_scan_lines		__पढ़ो_mostly;
अटल अचिन्हित पूर्णांक 	vga_rolled_over; /* last vc_origin offset beक्रमe wrap */

अटल bool vgacon_text_mode_क्रमce;
अटल bool vga_hardscroll_enabled;
अटल bool vga_hardscroll_user_enable = true;

bool vgacon_text_क्रमce(व्योम)
अणु
	वापस vgacon_text_mode_क्रमce;
पूर्ण
EXPORT_SYMBOL(vgacon_text_क्रमce);

अटल पूर्णांक __init text_mode(अक्षर *str)
अणु
	vgacon_text_mode_क्रमce = true;

	pr_warn("You have booted with nomodeset. This means your GPU drivers are DISABLED\n");
	pr_warn("Any video related functionality will be severely degraded, and you may not even be able to suspend the system properly\n");
	pr_warn("Unless you actually understand what nomodeset does, you should reboot without enabling it\n");

	वापस 1;
पूर्ण

/* क्रमce text mode - used by kernel modesetting */
__setup("nomodeset", text_mode);

अटल पूर्णांक __init no_scroll(अक्षर *str)
अणु
	/*
	 * Disabling scrollback is required क्रम the Braillex ib80-piezo
	 * Braille पढ़ोer made by F.H. Papenmeier (Germany).
	 * Use the "no-scroll" bootflag.
	 */
	vga_hardscroll_user_enable = vga_hardscroll_enabled = false;
	वापस 1;
पूर्ण

__setup("no-scroll", no_scroll);

/*
 * By replacing the four outb_p with two back to back outw, we can reduce
 * the winकरोw of opportunity to see text mislocated to the RHS of the
 * console during heavy scrolling activity. However there is the remote
 * possibility that some pre-dinosaur hardware won't like the back to back
 * I/O. Since the Xservers get away with it, we should be able to as well.
 */
अटल अंतरभूत व्योम ग_लिखो_vga(अचिन्हित अक्षर reg, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक v1, v2;
	अचिन्हित दीर्घ flags;

	/*
	 * ddprपूर्णांकk might set the console position from पूर्णांकerrupt
	 * handlers, thus the ग_लिखो has to be IRQ-atomic.
	 */
	raw_spin_lock_irqsave(&vga_lock, flags);
	v1 = reg + (val & 0xff00);
	v2 = reg + 1 + ((val << 8) & 0xff00);
	outw(v1, vga_video_port_reg);
	outw(v2, vga_video_port_reg);
	raw_spin_unlock_irqrestore(&vga_lock, flags);
पूर्ण

अटल अंतरभूत व्योम vga_set_mem_top(काष्ठा vc_data *c)
अणु
	ग_लिखो_vga(12, (c->vc_visible_origin - vga_vram_base) / 2);
पूर्ण

अटल व्योम vgacon_restore_screen(काष्ठा vc_data *c)
अणु
	अगर (c->vc_origin != c->vc_visible_origin)
		vgacon_scrolldelta(c, 0);
पूर्ण

अटल व्योम vgacon_scrolldelta(काष्ठा vc_data *c, पूर्णांक lines)
अणु
	vc_scrolldelta_helper(c, lines, vga_rolled_over, (व्योम *)vga_vram_base,
			vga_vram_size);
	vga_set_mem_top(c);
पूर्ण

अटल स्थिर अक्षर *vgacon_startup(व्योम)
अणु
	स्थिर अक्षर *display_desc = शून्य;
	u16 saved1, saved2;
	अस्थिर u16 *p;

	अगर (screen_info.orig_video_isVGA == VIDEO_TYPE_VLFB ||
	    screen_info.orig_video_isVGA == VIDEO_TYPE_EFI) अणु
	      no_vga:
#अगर_घोषित CONFIG_DUMMY_CONSOLE
		conचयनp = &dummy_con;
		वापस conचयनp->con_startup();
#अन्यथा
		वापस शून्य;
#पूर्ण_अगर
	पूर्ण

	/* boot_params.screen_info reasonably initialized? */
	अगर ((screen_info.orig_video_lines == 0) ||
	    (screen_info.orig_video_cols  == 0))
		जाओ no_vga;

	/* VGA16 modes are not handled by VGACON */
	अगर ((screen_info.orig_video_mode == 0x0D) ||	/* 320x200/4 */
	    (screen_info.orig_video_mode == 0x0E) ||	/* 640x200/4 */
	    (screen_info.orig_video_mode == 0x10) ||	/* 640x350/4 */
	    (screen_info.orig_video_mode == 0x12) ||	/* 640x480/4 */
	    (screen_info.orig_video_mode == 0x6A))	/* 800x600/4 (VESA) */
		जाओ no_vga;

	vga_video_num_lines = screen_info.orig_video_lines;
	vga_video_num_columns = screen_info.orig_video_cols;
	vgastate.vgabase = शून्य;

	अगर (screen_info.orig_video_mode == 7) अणु
		/* Monochrome display */
		vga_vram_base = 0xb0000;
		vga_video_port_reg = VGA_CRT_IM;
		vga_video_port_val = VGA_CRT_DM;
		अगर ((screen_info.orig_video_ega_bx & 0xff) != 0x10) अणु
			अटल काष्ठा resource ega_console_resource =
			    अणु .name	= "ega",
			      .flags	= IORESOURCE_IO,
			      .start	= 0x3B0,
			      .end	= 0x3BF पूर्ण;
			vga_video_type = VIDEO_TYPE_EGAM;
			vga_vram_size = 0x8000;
			display_desc = "EGA+";
			request_resource(&ioport_resource,
					 &ega_console_resource);
		पूर्ण अन्यथा अणु
			अटल काष्ठा resource mda1_console_resource =
			    अणु .name	= "mda",
			      .flags	= IORESOURCE_IO,
			      .start	= 0x3B0,
			      .end	= 0x3BB पूर्ण;
			अटल काष्ठा resource mda2_console_resource =
			    अणु .name	= "mda",
			      .flags	= IORESOURCE_IO,
			      .start	= 0x3BF,
			      .end	= 0x3BF पूर्ण;
			vga_video_type = VIDEO_TYPE_MDA;
			vga_vram_size = 0x2000;
			display_desc = "*MDA";
			request_resource(&ioport_resource,
					 &mda1_console_resource);
			request_resource(&ioport_resource,
					 &mda2_console_resource);
			vga_video_font_height = 14;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If not, it is color. */
		vga_can_करो_color = true;
		vga_vram_base = 0xb8000;
		vga_video_port_reg = VGA_CRT_IC;
		vga_video_port_val = VGA_CRT_DC;
		अगर ((screen_info.orig_video_ega_bx & 0xff) != 0x10) अणु
			पूर्णांक i;

			vga_vram_size = 0x8000;

			अगर (!screen_info.orig_video_isVGA) अणु
				अटल काष्ठा resource ega_console_resource =
				    अणु .name	= "ega",
				      .flags	= IORESOURCE_IO,
				      .start	= 0x3C0,
				      .end	= 0x3DF पूर्ण;
				vga_video_type = VIDEO_TYPE_EGAC;
				display_desc = "EGA";
				request_resource(&ioport_resource,
						 &ega_console_resource);
			पूर्ण अन्यथा अणु
				अटल काष्ठा resource vga_console_resource =
				    अणु .name	= "vga+",
				      .flags	= IORESOURCE_IO,
				      .start	= 0x3C0,
				      .end	= 0x3DF पूर्ण;
				vga_video_type = VIDEO_TYPE_VGAC;
				display_desc = "VGA+";
				request_resource(&ioport_resource,
						 &vga_console_resource);

				/*
				 * Normalise the palette रेजिस्टरs, to poपूर्णांक
				 * the 16 screen colours to the first 16
				 * DAC entries.
				 */

				क्रम (i = 0; i < 16; i++) अणु
					inb_p(VGA_IS1_RC);
					outb_p(i, VGA_ATT_W);
					outb_p(i, VGA_ATT_W);
				पूर्ण
				outb_p(0x20, VGA_ATT_W);

				/*
				 * Now set the DAC रेजिस्टरs back to their
				 * शेष values
				 */
				क्रम (i = 0; i < 16; i++) अणु
					outb_p(color_table[i], VGA_PEL_IW);
					outb_p(शेष_red[i], VGA_PEL_D);
					outb_p(शेष_grn[i], VGA_PEL_D);
					outb_p(शेष_blu[i], VGA_PEL_D);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अटल काष्ठा resource cga_console_resource =
			    अणु .name	= "cga",
			      .flags	= IORESOURCE_IO,
			      .start	= 0x3D4,
			      .end	= 0x3D5 पूर्ण;
			vga_video_type = VIDEO_TYPE_CGA;
			vga_vram_size = 0x2000;
			display_desc = "*CGA";
			request_resource(&ioport_resource,
					 &cga_console_resource);
			vga_video_font_height = 8;
		पूर्ण
	पूर्ण

	vga_vram_base = VGA_MAP_MEM(vga_vram_base, vga_vram_size);
	vga_vram_end = vga_vram_base + vga_vram_size;

	/*
	 *      Find out अगर there is a graphics card present.
	 *      Are there smarter methods around?
	 */
	p = (अस्थिर u16 *) vga_vram_base;
	saved1 = scr_पढ़ोw(p);
	saved2 = scr_पढ़ोw(p + 1);
	scr_ग_लिखोw(0xAA55, p);
	scr_ग_लिखोw(0x55AA, p + 1);
	अगर (scr_पढ़ोw(p) != 0xAA55 || scr_पढ़ोw(p + 1) != 0x55AA) अणु
		scr_ग_लिखोw(saved1, p);
		scr_ग_लिखोw(saved2, p + 1);
		जाओ no_vga;
	पूर्ण
	scr_ग_लिखोw(0x55AA, p);
	scr_ग_लिखोw(0xAA55, p + 1);
	अगर (scr_पढ़ोw(p) != 0x55AA || scr_पढ़ोw(p + 1) != 0xAA55) अणु
		scr_ग_लिखोw(saved1, p);
		scr_ग_लिखोw(saved2, p + 1);
		जाओ no_vga;
	पूर्ण
	scr_ग_लिखोw(saved1, p);
	scr_ग_लिखोw(saved2, p + 1);

	अगर (vga_video_type == VIDEO_TYPE_EGAC
	    || vga_video_type == VIDEO_TYPE_VGAC
	    || vga_video_type == VIDEO_TYPE_EGAM) अणु
		vga_hardscroll_enabled = vga_hardscroll_user_enable;
		vga_शेष_font_height = screen_info.orig_video_poपूर्णांकs;
		vga_video_font_height = screen_info.orig_video_poपूर्णांकs;
		/* This may be suboptimal but is a safe bet - go with it */
		vga_scan_lines =
		    vga_video_font_height * vga_video_num_lines;
	पूर्ण

	vgacon_xres = screen_info.orig_video_cols * VGA_FONTWIDTH;
	vgacon_yres = vga_scan_lines;

	वापस display_desc;
पूर्ण

अटल व्योम vgacon_init(काष्ठा vc_data *c, पूर्णांक init)
अणु
	काष्ठा uni_pagedir *p;

	/*
	 * We cannot be loaded as a module, thereक्रमe init is always 1,
	 * but vgacon_init can be called more than once, and init will
	 * not be 1.
	 */
	c->vc_can_करो_color = vga_can_करो_color;

	/* set dimensions manually अगर init != 0 since vc_resize() will fail */
	अगर (init) अणु
		c->vc_cols = vga_video_num_columns;
		c->vc_rows = vga_video_num_lines;
	पूर्ण अन्यथा
		vc_resize(c, vga_video_num_columns, vga_video_num_lines);

	c->vc_scan_lines = vga_scan_lines;
	c->vc_font.height = c->vc_cell_height = vga_video_font_height;
	c->vc_complement_mask = 0x7700;
	अगर (vga_512_अक्षरs)
		c->vc_hi_font_mask = 0x0800;
	p = *c->vc_uni_pagedir_loc;
	अगर (c->vc_uni_pagedir_loc != &vgacon_uni_pagedir) अणु
		con_मुक्त_unimap(c);
		c->vc_uni_pagedir_loc = &vgacon_uni_pagedir;
		vgacon_refcount++;
	पूर्ण
	अगर (!vgacon_uni_pagedir && p)
		con_set_शेष_unimap(c);

	/* Only set the शेष अगर the user didn't deliberately override it */
	अगर (global_cursor_शेष == -1)
		global_cursor_शेष =
			!(screen_info.flags & VIDEO_FLAGS_NOCURSOR);
पूर्ण

अटल व्योम vgacon_deinit(काष्ठा vc_data *c)
अणु
	/* When closing the active console, reset video origin */
	अगर (con_is_visible(c)) अणु
		c->vc_visible_origin = vga_vram_base;
		vga_set_mem_top(c);
	पूर्ण

	अगर (!--vgacon_refcount)
		con_मुक्त_unimap(c);
	c->vc_uni_pagedir_loc = &c->vc_uni_pagedir;
	con_set_शेष_unimap(c);
पूर्ण

अटल u8 vgacon_build_attr(काष्ठा vc_data *c, u8 color,
			    क्रमागत vc_पूर्णांकensity पूर्णांकensity,
			    bool blink, bool underline, bool reverse,
			    bool italic)
अणु
	u8 attr = color;

	अगर (vga_can_करो_color) अणु
		अगर (italic)
			attr = (attr & 0xF0) | c->vc_itcolor;
		अन्यथा अगर (underline)
			attr = (attr & 0xf0) | c->vc_ulcolor;
		अन्यथा अगर (पूर्णांकensity == VCI_HALF_BRIGHT)
			attr = (attr & 0xf0) | c->vc_halfcolor;
	पूर्ण
	अगर (reverse)
		attr =
		    ((attr) & 0x88) | ((((attr) >> 4) | ((attr) << 4)) &
				       0x77);
	अगर (blink)
		attr ^= 0x80;
	अगर (पूर्णांकensity == VCI_BOLD)
		attr ^= 0x08;
	अगर (!vga_can_करो_color) अणु
		अगर (italic)
			attr = (attr & 0xF8) | 0x02;
		अन्यथा अगर (underline)
			attr = (attr & 0xf8) | 0x01;
		अन्यथा अगर (पूर्णांकensity == VCI_HALF_BRIGHT)
			attr = (attr & 0xf0) | 0x08;
	पूर्ण
	वापस attr;
पूर्ण

अटल व्योम vgacon_invert_region(काष्ठा vc_data *c, u16 * p, पूर्णांक count)
अणु
	स्थिर bool col = vga_can_करो_color;

	जबतक (count--) अणु
		u16 a = scr_पढ़ोw(p);
		अगर (col)
			a = ((a) & 0x88ff) | (((a) & 0x7000) >> 4) |
			    (((a) & 0x0700) << 4);
		अन्यथा
			a ^= ((a & 0x0700) == 0x0100) ? 0x7000 : 0x7700;
		scr_ग_लिखोw(a, p++);
	पूर्ण
पूर्ण

अटल व्योम vgacon_set_cursor_size(पूर्णांक xpos, पूर्णांक from, पूर्णांक to)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक curs, cure;

	अगर ((from == cursor_size_lastfrom) && (to == cursor_size_lastto))
		वापस;
	cursor_size_lastfrom = from;
	cursor_size_lastto = to;

	raw_spin_lock_irqsave(&vga_lock, flags);
	अगर (vga_video_type >= VIDEO_TYPE_VGAC) अणु
		outb_p(VGA_CRTC_CURSOR_START, vga_video_port_reg);
		curs = inb_p(vga_video_port_val);
		outb_p(VGA_CRTC_CURSOR_END, vga_video_port_reg);
		cure = inb_p(vga_video_port_val);
	पूर्ण अन्यथा अणु
		curs = 0;
		cure = 0;
	पूर्ण

	curs = (curs & 0xc0) | from;
	cure = (cure & 0xe0) | to;

	outb_p(VGA_CRTC_CURSOR_START, vga_video_port_reg);
	outb_p(curs, vga_video_port_val);
	outb_p(VGA_CRTC_CURSOR_END, vga_video_port_reg);
	outb_p(cure, vga_video_port_val);
	raw_spin_unlock_irqrestore(&vga_lock, flags);
पूर्ण

अटल व्योम vgacon_cursor(काष्ठा vc_data *c, पूर्णांक mode)
अणु
	अगर (c->vc_mode != KD_TEXT)
		वापस;

	vgacon_restore_screen(c);

	चयन (mode) अणु
	हाल CM_ERASE:
		ग_लिखो_vga(14, (c->vc_pos - vga_vram_base) / 2);
	        अगर (vga_video_type >= VIDEO_TYPE_VGAC)
			vgacon_set_cursor_size(c->state.x, 31, 30);
		अन्यथा
			vgacon_set_cursor_size(c->state.x, 31, 31);
		अवरोध;

	हाल CM_MOVE:
	हाल CM_DRAW:
		ग_लिखो_vga(14, (c->vc_pos - vga_vram_base) / 2);
		चयन (CUR_SIZE(c->vc_cursor_type)) अणु
		हाल CUR_UNDERLINE:
			vgacon_set_cursor_size(c->state.x,
					       c->vc_cell_height -
					       (c->vc_cell_height <
						10 ? 2 : 3),
					       c->vc_cell_height -
					       (c->vc_cell_height <
						10 ? 1 : 2));
			अवरोध;
		हाल CUR_TWO_THIRDS:
			vgacon_set_cursor_size(c->state.x,
					       c->vc_cell_height / 3,
					       c->vc_cell_height -
					       (c->vc_cell_height <
						10 ? 1 : 2));
			अवरोध;
		हाल CUR_LOWER_THIRD:
			vgacon_set_cursor_size(c->state.x,
					       (c->vc_cell_height * 2) / 3,
					       c->vc_cell_height -
					       (c->vc_cell_height <
						10 ? 1 : 2));
			अवरोध;
		हाल CUR_LOWER_HALF:
			vgacon_set_cursor_size(c->state.x,
					       c->vc_cell_height / 2,
					       c->vc_cell_height -
					       (c->vc_cell_height <
						10 ? 1 : 2));
			अवरोध;
		हाल CUR_NONE:
			अगर (vga_video_type >= VIDEO_TYPE_VGAC)
				vgacon_set_cursor_size(c->state.x, 31, 30);
			अन्यथा
				vgacon_set_cursor_size(c->state.x, 31, 31);
			अवरोध;
		शेष:
			vgacon_set_cursor_size(c->state.x, 1,
					       c->vc_cell_height);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक vgacon_करोresize(काष्ठा vc_data *c,
		अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक scanlines = height * c->vc_cell_height;
	u8 scanlines_lo = 0, r7 = 0, vsync_end = 0, mode, max_scan;

	raw_spin_lock_irqsave(&vga_lock, flags);

	vgacon_xres = width * VGA_FONTWIDTH;
	vgacon_yres = height * c->vc_cell_height;
	अगर (vga_video_type >= VIDEO_TYPE_VGAC) अणु
		outb_p(VGA_CRTC_MAX_SCAN, vga_video_port_reg);
		max_scan = inb_p(vga_video_port_val);

		अगर (max_scan & 0x80)
			scanlines <<= 1;

		outb_p(VGA_CRTC_MODE, vga_video_port_reg);
		mode = inb_p(vga_video_port_val);

		अगर (mode & 0x04)
			scanlines >>= 1;

		scanlines -= 1;
		scanlines_lo = scanlines & 0xff;

		outb_p(VGA_CRTC_OVERFLOW, vga_video_port_reg);
		r7 = inb_p(vga_video_port_val) & ~0x42;

		अगर (scanlines & 0x100)
			r7 |= 0x02;
		अगर (scanlines & 0x200)
			r7 |= 0x40;

		/* deprotect रेजिस्टरs */
		outb_p(VGA_CRTC_V_SYNC_END, vga_video_port_reg);
		vsync_end = inb_p(vga_video_port_val);
		outb_p(VGA_CRTC_V_SYNC_END, vga_video_port_reg);
		outb_p(vsync_end & ~0x80, vga_video_port_val);
	पूर्ण

	outb_p(VGA_CRTC_H_DISP, vga_video_port_reg);
	outb_p(width - 1, vga_video_port_val);
	outb_p(VGA_CRTC_OFFSET, vga_video_port_reg);
	outb_p(width >> 1, vga_video_port_val);

	अगर (vga_video_type >= VIDEO_TYPE_VGAC) अणु
		outb_p(VGA_CRTC_V_DISP_END, vga_video_port_reg);
		outb_p(scanlines_lo, vga_video_port_val);
		outb_p(VGA_CRTC_OVERFLOW, vga_video_port_reg);
		outb_p(r7,vga_video_port_val);

		/* reprotect रेजिस्टरs */
		outb_p(VGA_CRTC_V_SYNC_END, vga_video_port_reg);
		outb_p(vsync_end, vga_video_port_val);
	पूर्ण

	raw_spin_unlock_irqrestore(&vga_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक vgacon_चयन(काष्ठा vc_data *c)
अणु
	पूर्णांक x = c->vc_cols * VGA_FONTWIDTH;
	पूर्णांक y = c->vc_rows * c->vc_cell_height;
	पूर्णांक rows = screen_info.orig_video_lines * vga_शेष_font_height/
		c->vc_cell_height;
	/*
	 * We need to save screen size here as it's the only way
	 * we can spot the screen has been resized and we need to
	 * set size of freshly allocated screens ourselves.
	 */
	vga_video_num_columns = c->vc_cols;
	vga_video_num_lines = c->vc_rows;

	/* We can only copy out the size of the video buffer here,
	 * otherwise we get पूर्णांकo VGA BIOS */

	अगर (!vga_is_gfx) अणु
		scr_स_नकलw((u16 *) c->vc_origin, (u16 *) c->vc_screenbuf,
			    c->vc_screenbuf_size > vga_vram_size ?
				vga_vram_size : c->vc_screenbuf_size);

		अगर ((vgacon_xres != x || vgacon_yres != y) &&
		    (!(vga_video_num_columns % 2) &&
		     vga_video_num_columns <= screen_info.orig_video_cols &&
		     vga_video_num_lines <= rows))
			vgacon_करोresize(c, c->vc_cols, c->vc_rows);
	पूर्ण

	वापस 0;		/* Redrawing not needed */
पूर्ण

अटल व्योम vga_set_palette(काष्ठा vc_data *vc, स्थिर अचिन्हित अक्षर *table)
अणु
	पूर्णांक i, j;

	vga_w(vgastate.vgabase, VGA_PEL_MSK, 0xff);
	क्रम (i = j = 0; i < 16; i++) अणु
		vga_w(vgastate.vgabase, VGA_PEL_IW, table[i]);
		vga_w(vgastate.vgabase, VGA_PEL_D, vc->vc_palette[j++] >> 2);
		vga_w(vgastate.vgabase, VGA_PEL_D, vc->vc_palette[j++] >> 2);
		vga_w(vgastate.vgabase, VGA_PEL_D, vc->vc_palette[j++] >> 2);
	पूर्ण
पूर्ण

अटल व्योम vgacon_set_palette(काष्ठा vc_data *vc, स्थिर अचिन्हित अक्षर *table)
अणु
	अगर (vga_video_type != VIDEO_TYPE_VGAC || vga_palette_blanked
	    || !con_is_visible(vc))
		वापस;
	vga_set_palette(vc, table);
पूर्ण

/* काष्ठाure holding original VGA रेजिस्टर settings */
अटल काष्ठा अणु
	अचिन्हित अक्षर SeqCtrlIndex;	/* Sequencer Index reg.   */
	अचिन्हित अक्षर CrtCtrlIndex;	/* CRT-Contr. Index reg.  */
	अचिन्हित अक्षर CrtMiscIO;	/* Miscellaneous रेजिस्टर */
	अचिन्हित अक्षर HorizontalTotal;	/* CRT-Controller:00h */
	अचिन्हित अक्षर HorizDisplayEnd;	/* CRT-Controller:01h */
	अचिन्हित अक्षर StartHorizRetrace;	/* CRT-Controller:04h */
	अचिन्हित अक्षर EndHorizRetrace;	/* CRT-Controller:05h */
	अचिन्हित अक्षर Overflow;	/* CRT-Controller:07h */
	अचिन्हित अक्षर StartVertRetrace;	/* CRT-Controller:10h */
	अचिन्हित अक्षर EndVertRetrace;	/* CRT-Controller:11h */
	अचिन्हित अक्षर ModeControl;	/* CRT-Controller:17h */
	अचिन्हित अक्षर ClockingMode;	/* Seq-Controller:01h */
पूर्ण vga_state;

अटल व्योम vga_vesa_blank(काष्ठा vgastate *state, पूर्णांक mode)
अणु
	/* save original values of VGA controller रेजिस्टरs */
	अगर (!vga_vesa_blanked) अणु
		raw_spin_lock_irq(&vga_lock);
		vga_state.SeqCtrlIndex = vga_r(state->vgabase, VGA_SEQ_I);
		vga_state.CrtCtrlIndex = inb_p(vga_video_port_reg);
		vga_state.CrtMiscIO = vga_r(state->vgabase, VGA_MIS_R);
		raw_spin_unlock_irq(&vga_lock);

		outb_p(0x00, vga_video_port_reg);	/* HorizontalTotal */
		vga_state.HorizontalTotal = inb_p(vga_video_port_val);
		outb_p(0x01, vga_video_port_reg);	/* HorizDisplayEnd */
		vga_state.HorizDisplayEnd = inb_p(vga_video_port_val);
		outb_p(0x04, vga_video_port_reg);	/* StartHorizRetrace */
		vga_state.StartHorizRetrace = inb_p(vga_video_port_val);
		outb_p(0x05, vga_video_port_reg);	/* EndHorizRetrace */
		vga_state.EndHorizRetrace = inb_p(vga_video_port_val);
		outb_p(0x07, vga_video_port_reg);	/* Overflow */
		vga_state.Overflow = inb_p(vga_video_port_val);
		outb_p(0x10, vga_video_port_reg);	/* StartVertRetrace */
		vga_state.StartVertRetrace = inb_p(vga_video_port_val);
		outb_p(0x11, vga_video_port_reg);	/* EndVertRetrace */
		vga_state.EndVertRetrace = inb_p(vga_video_port_val);
		outb_p(0x17, vga_video_port_reg);	/* ModeControl */
		vga_state.ModeControl = inb_p(vga_video_port_val);
		vga_state.ClockingMode = vga_rseq(state->vgabase, VGA_SEQ_CLOCK_MODE);
	पूर्ण

	/* assure that video is enabled */
	/* "0x20" is VIDEO_ENABLE_bit in रेजिस्टर 01 of sequencer */
	raw_spin_lock_irq(&vga_lock);
	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE, vga_state.ClockingMode | 0x20);

	/* test क्रम vertical retrace in process.... */
	अगर ((vga_state.CrtMiscIO & 0x80) == 0x80)
		vga_w(state->vgabase, VGA_MIS_W, vga_state.CrtMiscIO & 0xEF);

	/*
	 * Set <End of vertical retrace> to minimum (0) and
	 * <Start of vertical Retrace> to maximum (incl. overflow)
	 * Result: turn off vertical sync (VSync) pulse.
	 */
	अगर (mode & VESA_VSYNC_SUSPEND) अणु
		outb_p(0x10, vga_video_port_reg);	/* StartVertRetrace */
		outb_p(0xff, vga_video_port_val);	/* maximum value */
		outb_p(0x11, vga_video_port_reg);	/* EndVertRetrace */
		outb_p(0x40, vga_video_port_val);	/* minimum (bits 0..3)  */
		outb_p(0x07, vga_video_port_reg);	/* Overflow */
		outb_p(vga_state.Overflow | 0x84, vga_video_port_val);	/* bits 9,10 of vert. retrace */
	पूर्ण

	अगर (mode & VESA_HSYNC_SUSPEND) अणु
		/*
		 * Set <End of horizontal retrace> to minimum (0) and
		 *  <Start of horizontal Retrace> to maximum
		 * Result: turn off horizontal sync (HSync) pulse.
		 */
		outb_p(0x04, vga_video_port_reg);	/* StartHorizRetrace */
		outb_p(0xff, vga_video_port_val);	/* maximum */
		outb_p(0x05, vga_video_port_reg);	/* EndHorizRetrace */
		outb_p(0x00, vga_video_port_val);	/* minimum (0) */
	पूर्ण

	/* restore both index रेजिस्टरs */
	vga_w(state->vgabase, VGA_SEQ_I, vga_state.SeqCtrlIndex);
	outb_p(vga_state.CrtCtrlIndex, vga_video_port_reg);
	raw_spin_unlock_irq(&vga_lock);
पूर्ण

अटल व्योम vga_vesa_unblank(काष्ठा vgastate *state)
अणु
	/* restore original values of VGA controller रेजिस्टरs */
	raw_spin_lock_irq(&vga_lock);
	vga_w(state->vgabase, VGA_MIS_W, vga_state.CrtMiscIO);

	outb_p(0x00, vga_video_port_reg);	/* HorizontalTotal */
	outb_p(vga_state.HorizontalTotal, vga_video_port_val);
	outb_p(0x01, vga_video_port_reg);	/* HorizDisplayEnd */
	outb_p(vga_state.HorizDisplayEnd, vga_video_port_val);
	outb_p(0x04, vga_video_port_reg);	/* StartHorizRetrace */
	outb_p(vga_state.StartHorizRetrace, vga_video_port_val);
	outb_p(0x05, vga_video_port_reg);	/* EndHorizRetrace */
	outb_p(vga_state.EndHorizRetrace, vga_video_port_val);
	outb_p(0x07, vga_video_port_reg);	/* Overflow */
	outb_p(vga_state.Overflow, vga_video_port_val);
	outb_p(0x10, vga_video_port_reg);	/* StartVertRetrace */
	outb_p(vga_state.StartVertRetrace, vga_video_port_val);
	outb_p(0x11, vga_video_port_reg);	/* EndVertRetrace */
	outb_p(vga_state.EndVertRetrace, vga_video_port_val);
	outb_p(0x17, vga_video_port_reg);	/* ModeControl */
	outb_p(vga_state.ModeControl, vga_video_port_val);
	/* ClockingMode */
	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE, vga_state.ClockingMode);

	/* restore index/control रेजिस्टरs */
	vga_w(state->vgabase, VGA_SEQ_I, vga_state.SeqCtrlIndex);
	outb_p(vga_state.CrtCtrlIndex, vga_video_port_reg);
	raw_spin_unlock_irq(&vga_lock);
पूर्ण

अटल व्योम vga_pal_blank(काष्ठा vgastate *state)
अणु
	पूर्णांक i;

	vga_w(state->vgabase, VGA_PEL_MSK, 0xff);
	क्रम (i = 0; i < 16; i++) अणु
		vga_w(state->vgabase, VGA_PEL_IW, i);
		vga_w(state->vgabase, VGA_PEL_D, 0);
		vga_w(state->vgabase, VGA_PEL_D, 0);
		vga_w(state->vgabase, VGA_PEL_D, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक vgacon_blank(काष्ठा vc_data *c, पूर्णांक blank, पूर्णांक mode_चयन)
अणु
	चयन (blank) अणु
	हाल 0:		/* Unblank */
		अगर (vga_vesa_blanked) अणु
			vga_vesa_unblank(&vgastate);
			vga_vesa_blanked = 0;
		पूर्ण
		अगर (vga_palette_blanked) अणु
			vga_set_palette(c, color_table);
			vga_palette_blanked = false;
			वापस 0;
		पूर्ण
		vga_is_gfx = false;
		/* Tell console.c that it has to restore the screen itself */
		वापस 1;
	हाल 1:		/* Normal blanking */
	हाल -1:	/* Obsolete */
		अगर (!mode_चयन && vga_video_type == VIDEO_TYPE_VGAC) अणु
			vga_pal_blank(&vgastate);
			vga_palette_blanked = true;
			वापस 0;
		पूर्ण
		vgacon_set_origin(c);
		scr_स_रखोw((व्योम *) vga_vram_base, BLANK,
			    c->vc_screenbuf_size);
		अगर (mode_चयन)
			vga_is_gfx = true;
		वापस 1;
	शेष:		/* VESA blanking */
		अगर (vga_video_type == VIDEO_TYPE_VGAC) अणु
			vga_vesa_blank(&vgastate, blank - 1);
			vga_vesa_blanked = blank;
		पूर्ण
		वापस 0;
	पूर्ण
पूर्ण

/*
 * PIO_FONT support.
 *
 * The font loading code goes back to the codepage package by
 * Joel Hoffman (joel@wam.umd.edu). (He reports that the original
 * reference is: "From: p. 307 of _Programmer's Guide to PC & PS/2
 * Video Systems_ by Riअक्षरd Wilton. 1987.  Microsoft Press".)
 *
 * Change क्रम certain monochrome monitors by Yury Shevchuck
 * (sizअगर@botik.yaroslavl.su).
 */

#घोषणा colourmap 0xa0000
/* Pauline Middelink <middelin@polyware.iaf.nl> reports that we
   should use 0xA0000 क्रम the bwmap as well.. */
#घोषणा blackwmap 0xa0000
#घोषणा cmapsz 8192

अटल पूर्णांक vgacon_करो_font_op(काष्ठा vgastate *state, अक्षर *arg, पूर्णांक set,
		bool ch512)
अणु
	अचिन्हित लघु video_port_status = vga_video_port_reg + 6;
	पूर्णांक font_select = 0x00, beg, i;
	अक्षर *अक्षरmap;
	bool clear_attribs = false;
	अगर (vga_video_type != VIDEO_TYPE_EGAM) अणु
		अक्षरmap = (अक्षर *) VGA_MAP_MEM(colourmap, 0);
		beg = 0x0e;
	पूर्ण अन्यथा अणु
		अक्षरmap = (अक्षर *) VGA_MAP_MEM(blackwmap, 0);
		beg = 0x0a;
	पूर्ण

	/*
	 * All fonts are loaded in slot 0 (0:1 क्रम 512 ch)
	 */

	अगर (!arg)
		वापस -EINVAL;	/* Return to शेष font not supported */

	font_select = ch512 ? 0x04 : 0x00;

	raw_spin_lock_irq(&vga_lock);
	/* First, the Sequencer */
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x1);
	/* CPU ग_लिखोs only to map 2 */
	vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, 0x04);	
	/* Sequential addressing */
	vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, 0x07);	
	/* Clear synchronous reset */
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x03);

	/* Now, the graphics controller, select map 2 */
	vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, 0x02);		
	/* disable odd-even addressing */
	vga_wgfx(state->vgabase, VGA_GFX_MODE, 0x00);
	/* map start at A000:0000 */
	vga_wgfx(state->vgabase, VGA_GFX_MISC, 0x00);
	raw_spin_unlock_irq(&vga_lock);

	अगर (arg) अणु
		अगर (set)
			क्रम (i = 0; i < cmapsz; i++) अणु
				vga_ग_लिखोb(arg[i], अक्षरmap + i);
				cond_resched();
			पूर्ण
		अन्यथा
			क्रम (i = 0; i < cmapsz; i++) अणु
				arg[i] = vga_पढ़ोb(अक्षरmap + i);
				cond_resched();
			पूर्ण

		/*
		 * In 512-अक्षरacter mode, the अक्षरacter map is not contiguous अगर
		 * we want to reमुख्य EGA compatible -- which we करो
		 */

		अगर (ch512) अणु
			अक्षरmap += 2 * cmapsz;
			arg += cmapsz;
			अगर (set)
				क्रम (i = 0; i < cmapsz; i++) अणु
					vga_ग_लिखोb(arg[i], अक्षरmap + i);
					cond_resched();
				पूर्ण
			अन्यथा
				क्रम (i = 0; i < cmapsz; i++) अणु
					arg[i] = vga_पढ़ोb(अक्षरmap + i);
					cond_resched();
				पूर्ण
		पूर्ण
	पूर्ण

	raw_spin_lock_irq(&vga_lock);
	/* First, the sequencer, Synchronous reset */
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x01);	
	/* CPU ग_लिखोs to maps 0 and 1 */
	vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, 0x03);
	/* odd-even addressing */
	vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, 0x03);
	/* Character Map Select */
	अगर (set)
		vga_wseq(state->vgabase, VGA_SEQ_CHARACTER_MAP, font_select);
	/* clear synchronous reset */
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x03);

	/* Now, the graphics controller, select map 0 क्रम CPU */
	vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, 0x00);
	/* enable even-odd addressing */
	vga_wgfx(state->vgabase, VGA_GFX_MODE, 0x10);
	/* map starts at b800:0 or b000:0 */
	vga_wgfx(state->vgabase, VGA_GFX_MISC, beg);

	/* अगर 512 अक्षर mode is alपढ़ोy enabled करोn't re-enable it. */
	अगर ((set) && (ch512 != vga_512_अक्षरs)) अणु
		vga_512_अक्षरs = ch512;
		/* 256-अक्षर: enable पूर्णांकensity bit
		   512-अक्षर: disable पूर्णांकensity bit */
		inb_p(video_port_status);	/* clear address flip-flop */
		/* color plane enable रेजिस्टर */
		vga_wattr(state->vgabase, VGA_ATC_PLANE_ENABLE, ch512 ? 0x07 : 0x0f);
		/* Wilton (1987) mentions the following; I करोn't know what
		   it means, but it works, and it appears necessary */
		inb_p(video_port_status);
		vga_wattr(state->vgabase, VGA_AR_ENABLE_DISPLAY, 0);	
		clear_attribs = true;
	पूर्ण
	raw_spin_unlock_irq(&vga_lock);

	अगर (clear_attribs) अणु
		क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
			काष्ठा vc_data *c = vc_cons[i].d;
			अगर (c && c->vc_sw == &vga_con) अणु
				/* क्रमce hi font mask to 0, so we always clear
				   the bit on either transition */
				c->vc_hi_font_mask = 0x00;
				clear_buffer_attributes(c);
				c->vc_hi_font_mask = ch512 ? 0x0800 : 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Adjust the screen to fit a font of a certain height
 */
अटल पूर्णांक vgacon_adjust_height(काष्ठा vc_data *vc, अचिन्हित fontheight)
अणु
	अचिन्हित अक्षर ovr, vde, fsr;
	पूर्णांक rows, maxscan, i;

	rows = vc->vc_scan_lines / fontheight;	/* Number of video rows we end up with */
	maxscan = rows * fontheight - 1;	/* Scan lines to actually display-1 */

	/* Reprogram the CRTC क्रम the new font size
	   Note: the attempt to पढ़ो the overflow रेजिस्टर will fail
	   on an EGA, but using 0xff क्रम the previous value appears to
	   be OK क्रम EGA text modes in the range 257-512 scan lines, so I
	   guess we करोn't need to worry about it.

	   The same applies क्रम the spill bits in the font size and cursor
	   रेजिस्टरs; they are ग_लिखो-only on EGA, but it appears that they
	   are all करोn't care bits on EGA, so I guess it doesn't matter. */

	raw_spin_lock_irq(&vga_lock);
	outb_p(0x07, vga_video_port_reg);	/* CRTC overflow रेजिस्टर */
	ovr = inb_p(vga_video_port_val);
	outb_p(0x09, vga_video_port_reg);	/* Font size रेजिस्टर */
	fsr = inb_p(vga_video_port_val);
	raw_spin_unlock_irq(&vga_lock);

	vde = maxscan & 0xff;	/* Vertical display end reg */
	ovr = (ovr & 0xbd) +	/* Overflow रेजिस्टर */
	    ((maxscan & 0x100) >> 7) + ((maxscan & 0x200) >> 3);
	fsr = (fsr & 0xe0) + (fontheight - 1);	/*  Font size रेजिस्टर */

	raw_spin_lock_irq(&vga_lock);
	outb_p(0x07, vga_video_port_reg);	/* CRTC overflow रेजिस्टर */
	outb_p(ovr, vga_video_port_val);
	outb_p(0x09, vga_video_port_reg);	/* Font size */
	outb_p(fsr, vga_video_port_val);
	outb_p(0x12, vga_video_port_reg);	/* Vertical display limit */
	outb_p(vde, vga_video_port_val);
	raw_spin_unlock_irq(&vga_lock);
	vga_video_font_height = fontheight;

	क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
		काष्ठा vc_data *c = vc_cons[i].d;

		अगर (c && c->vc_sw == &vga_con) अणु
			अगर (con_is_visible(c)) अणु
			        /* व्योम size to cause regs to be rewritten */
				cursor_size_lastfrom = 0;
				cursor_size_lastto = 0;
				c->vc_sw->con_cursor(c, CM_DRAW);
			पूर्ण
			c->vc_font.height = c->vc_cell_height = fontheight;
			vc_resize(c, 0, rows);	/* Adjust console size */
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vgacon_font_set(काष्ठा vc_data *c, काष्ठा console_font *font,
			   अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित अक्षरcount = font->अक्षरcount;
	पूर्णांक rc;

	अगर (vga_video_type < VIDEO_TYPE_EGAM)
		वापस -EINVAL;

	अगर (font->width != VGA_FONTWIDTH ||
	    (अक्षरcount != 256 && अक्षरcount != 512))
		वापस -EINVAL;

	rc = vgacon_करो_font_op(&vgastate, font->data, 1, अक्षरcount == 512);
	अगर (rc)
		वापस rc;

	अगर (!(flags & KD_FONT_FLAG_DONT_RECALC))
		rc = vgacon_adjust_height(c, font->height);
	वापस rc;
पूर्ण

अटल पूर्णांक vgacon_font_get(काष्ठा vc_data *c, काष्ठा console_font *font)
अणु
	अगर (vga_video_type < VIDEO_TYPE_EGAM)
		वापस -EINVAL;

	font->width = VGA_FONTWIDTH;
	font->height = c->vc_font.height;
	font->अक्षरcount = vga_512_अक्षरs ? 512 : 256;
	अगर (!font->data)
		वापस 0;
	वापस vgacon_करो_font_op(&vgastate, font->data, 0, vga_512_अक्षरs);
पूर्ण

अटल पूर्णांक vgacon_resize(काष्ठा vc_data *c, अचिन्हित पूर्णांक width,
			 अचिन्हित पूर्णांक height, अचिन्हित पूर्णांक user)
अणु
	अगर ((width << 1) * height > vga_vram_size)
		वापस -EINVAL;

	अगर (user) अणु
		/*
		 * Ho ho!  Someone (svgatexपंचांगode, eh?) may have reprogrammed
		 * the video mode!  Set the new शेषs then and go away.
		 */
		screen_info.orig_video_cols = width;
		screen_info.orig_video_lines = height;
		vga_शेष_font_height = c->vc_cell_height;
		वापस 0;
	पूर्ण
	अगर (width % 2 || width > screen_info.orig_video_cols ||
	    height > (screen_info.orig_video_lines * vga_शेष_font_height)/
	    c->vc_cell_height)
		वापस -EINVAL;

	अगर (con_is_visible(c) && !vga_is_gfx) /* who knows */
		vgacon_करोresize(c, width, height);
	वापस 0;
पूर्ण

अटल पूर्णांक vgacon_set_origin(काष्ठा vc_data *c)
अणु
	अगर (vga_is_gfx ||	/* We करोn't play origin tricks in graphic modes */
	    (console_blanked && !vga_palette_blanked))	/* Nor we ग_लिखो to blanked screens */
		वापस 0;
	c->vc_origin = c->vc_visible_origin = vga_vram_base;
	vga_set_mem_top(c);
	vga_rolled_over = 0;
	वापस 1;
पूर्ण

अटल व्योम vgacon_save_screen(काष्ठा vc_data *c)
अणु
	अटल पूर्णांक vga_bootup_console = 0;

	अगर (!vga_bootup_console) अणु
		/* This is a gross hack, but here is the only place we can
		 * set bootup console parameters without messing up generic
		 * console initialization routines.
		 */
		vga_bootup_console = 1;
		c->state.x = screen_info.orig_x;
		c->state.y = screen_info.orig_y;
	पूर्ण

	/* We can't copy in more than the size of the video buffer,
	 * or we'll be copying in VGA BIOS */

	अगर (!vga_is_gfx)
		scr_स_नकलw((u16 *) c->vc_screenbuf, (u16 *) c->vc_origin,
			    c->vc_screenbuf_size > vga_vram_size ? vga_vram_size : c->vc_screenbuf_size);
पूर्ण

अटल bool vgacon_scroll(काष्ठा vc_data *c, अचिन्हित पूर्णांक t, अचिन्हित पूर्णांक b,
		क्रमागत con_scroll dir, अचिन्हित पूर्णांक lines)
अणु
	अचिन्हित दीर्घ olकरो;
	अचिन्हित पूर्णांक delta;

	अगर (t || b != c->vc_rows || vga_is_gfx || c->vc_mode != KD_TEXT)
		वापस false;

	अगर (!vga_hardscroll_enabled || lines >= c->vc_rows / 2)
		वापस false;

	vgacon_restore_screen(c);
	olकरो = c->vc_origin;
	delta = lines * c->vc_size_row;
	अगर (dir == SM_UP) अणु
		अगर (c->vc_scr_end + delta >= vga_vram_end) अणु
			scr_स_नकलw((u16 *) vga_vram_base,
				    (u16 *) (olकरो + delta),
				    c->vc_screenbuf_size - delta);
			c->vc_origin = vga_vram_base;
			vga_rolled_over = olकरो - vga_vram_base;
		पूर्ण अन्यथा
			c->vc_origin += delta;
		scr_स_रखोw((u16 *) (c->vc_origin + c->vc_screenbuf_size -
				     delta), c->vc_video_erase_अक्षर,
			    delta);
	पूर्ण अन्यथा अणु
		अगर (olकरो - delta < vga_vram_base) अणु
			scr_स_हटाओw((u16 *) (vga_vram_end -
					      c->vc_screenbuf_size +
					      delta), (u16 *) olकरो,
				     c->vc_screenbuf_size - delta);
			c->vc_origin = vga_vram_end - c->vc_screenbuf_size;
			vga_rolled_over = 0;
		पूर्ण अन्यथा
			c->vc_origin -= delta;
		c->vc_scr_end = c->vc_origin + c->vc_screenbuf_size;
		scr_स_रखोw((u16 *) (c->vc_origin), c->vc_video_erase_अक्षर,
			    delta);
	पूर्ण
	c->vc_scr_end = c->vc_origin + c->vc_screenbuf_size;
	c->vc_visible_origin = c->vc_origin;
	vga_set_mem_top(c);
	c->vc_pos = (c->vc_pos - olकरो) + c->vc_origin;
	वापस true;
पूर्ण

/*
 *  The console `चयन' काष्ठाure क्रम the VGA based console
 */

अटल व्योम vgacon_clear(काष्ठा vc_data *vc, पूर्णांक sy, पूर्णांक sx, पूर्णांक height,
			 पूर्णांक width) अणु पूर्ण
अटल व्योम vgacon_अ_दो(काष्ठा vc_data *vc, पूर्णांक c, पूर्णांक ypos, पूर्णांक xpos) अणु पूर्ण
अटल व्योम vgacon_अ_दोs(काष्ठा vc_data *vc, स्थिर अचिन्हित लघु *s,
			 पूर्णांक count, पूर्णांक ypos, पूर्णांक xpos) अणु पूर्ण

स्थिर काष्ठा consw vga_con = अणु
	.owner = THIS_MODULE,
	.con_startup = vgacon_startup,
	.con_init = vgacon_init,
	.con_deinit = vgacon_deinit,
	.con_clear = vgacon_clear,
	.con_अ_दो = vgacon_अ_दो,
	.con_अ_दोs = vgacon_अ_दोs,
	.con_cursor = vgacon_cursor,
	.con_scroll = vgacon_scroll,
	.con_चयन = vgacon_चयन,
	.con_blank = vgacon_blank,
	.con_font_set = vgacon_font_set,
	.con_font_get = vgacon_font_get,
	.con_resize = vgacon_resize,
	.con_set_palette = vgacon_set_palette,
	.con_scrolldelta = vgacon_scrolldelta,
	.con_set_origin = vgacon_set_origin,
	.con_save_screen = vgacon_save_screen,
	.con_build_attr = vgacon_build_attr,
	.con_invert_region = vgacon_invert_region,
पूर्ण;
EXPORT_SYMBOL(vga_con);

MODULE_LICENSE("GPL");
