<शैली गुरु>
/*
 *  linux/drivers/video/console/sticon.c - console driver using HP's STI firmware
 *
 *	Copyright (C) 2000 Philipp Rumpf <prumpf@tux.org>
 *	Copyright (C) 2002-2020 Helge Deller <deller@gmx.de>
 *
 *  Based on linux/drivers/video/vgacon.c and linux/drivers/video/fbcon.c,
 *  which were
 *
 *	Created 28 Sep 1997 by Geert Uytterhoeven
 *	Rewritten by Martin Mares <mj@ucw.cz>, July 1998
 *	Copyright (C) 1991, 1992  Linus Torvalds
 *			    1995  Jay Estabrook
 *	Copyright (C) 1995 Geert Uytterhoeven
 *	Copyright (C) 1993 Bjoern Brauel
 *			   Roman Hodek
 *	Copyright (C) 1993 Hamish Macकरोnald
 *			   Greg Harp
 *	Copyright (C) 1994 David Carter [carter@compsci.bristol.ac.uk]
 *
 *	      with work by William Rucklidge (wjr@cs.cornell.edu)
 *			   Geert Uytterhoeven
 *			   Jes Sorensen (jds@kom.auc.dk)
 *			   Martin Apel
 *	      with work by Guenther Kelleter
 *			   Martin Schaller
 *			   Andreas Schwab
 *			   Emmanuel Marty (core@ggi-project.org)
 *			   Jakub Jelinek (jj@ultra.linux.cz)
 *			   Martin Mares <mj@ucw.cz>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/vt_kern.h>
#समावेश <linux/kd.h>
#समावेश <linux/selection.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/font.h>
#समावेश <linux/crc32.h>

#समावेश <यंत्र/पन.स>

#समावेश "../fbdev/sticore.h"

/* चयनing to graphics mode */
#घोषणा BLANK 0
अटल पूर्णांक vga_is_gfx;

#घोषणा STI_DEF_FONT	sticon_sti->font

/* borrowed from fbcon.c */
#घोषणा FNTREFCOUNT(fd)	(fd->refcount)
#घोषणा FNTCRC(fd)	(fd->crc)
अटल काष्ठा sti_cooked_font *font_data[MAX_NR_CONSOLES];

/* this is the sti_काष्ठा used क्रम this console */
अटल काष्ठा sti_काष्ठा *sticon_sti;

अटल स्थिर अक्षर *sticon_startup(व्योम)
अणु
    वापस "STI console";
पूर्ण

अटल व्योम sticon_अ_दो(काष्ठा vc_data *conp, पूर्णांक c, पूर्णांक ypos, पूर्णांक xpos)
अणु
    अगर (vga_is_gfx || console_blanked)
	    वापस;

    अगर (conp->vc_mode != KD_TEXT)
    	    वापस;

    sti_अ_दो(sticon_sti, c, ypos, xpos, font_data[conp->vc_num]);
पूर्ण

अटल व्योम sticon_अ_दोs(काष्ठा vc_data *conp, स्थिर अचिन्हित लघु *s,
			 पूर्णांक count, पूर्णांक ypos, पूर्णांक xpos)
अणु
    अगर (vga_is_gfx || console_blanked)
	    वापस;

    अगर (conp->vc_mode != KD_TEXT)
    	    वापस;

    जबतक (count--) अणु
	sti_अ_दो(sticon_sti, scr_पढ़ोw(s++), ypos, xpos++,
		 font_data[conp->vc_num]);
    पूर्ण
पूर्ण

अटल व्योम sticon_cursor(काष्ठा vc_data *conp, पूर्णांक mode)
अणु
    अचिन्हित लघु car1;

    /* no cursor update अगर screen is blanked */
    अगर (vga_is_gfx || console_blanked)
	वापस;

    car1 = conp->vc_screenbuf[conp->state.x + conp->state.y * conp->vc_cols];
    चयन (mode) अणु
    हाल CM_ERASE:
	sti_अ_दो(sticon_sti, car1, conp->state.y, conp->state.x,
		 font_data[conp->vc_num]);
	अवरोध;
    हाल CM_MOVE:
    हाल CM_DRAW:
	चयन (CUR_SIZE(conp->vc_cursor_type)) अणु
	हाल CUR_UNDERLINE:
	हाल CUR_LOWER_THIRD:
	हाल CUR_LOWER_HALF:
	हाल CUR_TWO_THIRDS:
	हाल CUR_BLOCK:
	    sti_अ_दो(sticon_sti, (car1 & 255) + (0 << 8) + (7 << 11),
		     conp->state.y, conp->state.x, font_data[conp->vc_num]);
	    अवरोध;
	पूर्ण
	अवरोध;
    पूर्ण
पूर्ण

अटल bool sticon_scroll(काष्ठा vc_data *conp, अचिन्हित पूर्णांक t,
		अचिन्हित पूर्णांक b, क्रमागत con_scroll dir, अचिन्हित पूर्णांक count)
अणु
    काष्ठा sti_काष्ठा *sti = sticon_sti;

    अगर (vga_is_gfx)
        वापस false;

    sticon_cursor(conp, CM_ERASE);

    चयन (dir) अणु
    हाल SM_UP:
	sti_bmove(sti, t + count, 0, t, 0, b - t - count, conp->vc_cols,
		  font_data[conp->vc_num]);
	sti_clear(sti, b - count, 0, count, conp->vc_cols,
		  conp->vc_video_erase_अक्षर, font_data[conp->vc_num]);
	अवरोध;

    हाल SM_DOWN:
	sti_bmove(sti, t, 0, t + count, 0, b - t - count, conp->vc_cols,
		  font_data[conp->vc_num]);
	sti_clear(sti, t, 0, count, conp->vc_cols,
		  conp->vc_video_erase_अक्षर, font_data[conp->vc_num]);
	अवरोध;
    पूर्ण

    वापस false;
पूर्ण

अटल पूर्णांक sticon_set_def_font(पूर्णांक unit, काष्ठा console_font *op)
अणु
	अगर (font_data[unit] != STI_DEF_FONT) अणु
		अगर (--FNTREFCOUNT(font_data[unit]) == 0) अणु
			kमुक्त(font_data[unit]->raw_ptr);
			kमुक्त(font_data[unit]);
		पूर्ण
		font_data[unit] = STI_DEF_FONT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sticon_set_font(काष्ठा vc_data *vc, काष्ठा console_font *op)
अणु
	काष्ठा sti_काष्ठा *sti = sticon_sti;
	पूर्णांक vc_cols, vc_rows, vc_old_cols, vc_old_rows;
	पूर्णांक unit = vc->vc_num;
	पूर्णांक w = op->width;
	पूर्णांक h = op->height;
	पूर्णांक size, i, bpc, pitch;
	काष्ठा sti_rom_font *new_font;
	काष्ठा sti_cooked_font *cooked_font;
	अचिन्हित अक्षर *data = op->data, *p;

	अगर ((w < 6) || (h < 6) || (w > 32) || (h > 32)
	    || (op->अक्षरcount != 256 && op->अक्षरcount != 512))
		वापस -EINVAL;
	pitch = ALIGN(w, 8) / 8;
	bpc = pitch * h;
	size = bpc * op->अक्षरcount;

	new_font = kदो_स्मृति(माप(*new_font) + size, STI_LOWMEM);
	अगर (!new_font)
		वापस -ENOMEM;

	new_font->first_अक्षर = 0;
	new_font->last_अक्षर = op->अक्षरcount - 1;
	new_font->width = w;
	new_font->height = h;
	new_font->font_type = STI_FONT_HPROMAN8;
	new_font->bytes_per_अक्षर = bpc;
	new_font->underline_height = 0;
	new_font->underline_pos = 0;

	cooked_font = kzalloc(माप(*cooked_font), GFP_KERNEL);
	अगर (!cooked_font) अणु
		kमुक्त(new_font);
		वापस -ENOMEM;
	पूर्ण
	cooked_font->raw = new_font;
	cooked_font->raw_ptr = new_font;
	cooked_font->width = w;
	cooked_font->height = h;
	FNTREFCOUNT(cooked_font) = 0;	/* usage counter */

	p = (अचिन्हित अक्षर *) new_font;
	p += माप(*new_font);
	क्रम (i = 0; i < op->अक्षरcount; i++) अणु
		स_नकल(p, data, bpc);
		data += pitch*32;
		p += bpc;
	पूर्ण
	FNTCRC(cooked_font) = crc32(0, new_font, size + माप(*new_font));
	sti_font_convert_bytemode(sti, cooked_font);
	new_font = cooked_font->raw_ptr;

	/* check अगर font is alपढ़ोy used by other console */
	क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
		अगर (font_data[i] != STI_DEF_FONT
		    && (FNTCRC(font_data[i]) == FNTCRC(cooked_font))) अणु
			kमुक्त(new_font);
			kमुक्त(cooked_font);
			/* current font is the same as the new one */
			अगर (i == unit)
				वापस 0;
			cooked_font = font_data[i];
			new_font = cooked_font->raw_ptr;
			अवरोध;
		पूर्ण
	पूर्ण

	/* clear screen with old font: we now may have less rows */
	vc_old_rows = vc->vc_rows;
	vc_old_cols = vc->vc_cols;
	sti_clear(sticon_sti, 0, 0, vc_old_rows, vc_old_cols,
		  vc->vc_video_erase_अक्षर, font_data[vc->vc_num]);

	/* delete old font in हाल it is a user font */
	sticon_set_def_font(unit, शून्य);

	FNTREFCOUNT(cooked_font)++;
	font_data[unit] = cooked_font;

	vc_cols = sti_onscreen_x(sti) / cooked_font->width;
	vc_rows = sti_onscreen_y(sti) / cooked_font->height;
	vc_resize(vc, vc_cols, vc_rows);

	/* need to repaपूर्णांक screen अगर cols & rows are same as old font */
	अगर (vc_cols == vc_old_cols && vc_rows == vc_old_rows)
		update_screen(vc);

	वापस 0;
पूर्ण

अटल पूर्णांक sticon_font_शेष(काष्ठा vc_data *vc, काष्ठा console_font *op, अक्षर *name)
अणु
	वापस sticon_set_def_font(vc->vc_num, op);
पूर्ण

अटल पूर्णांक sticon_font_set(काष्ठा vc_data *vc, काष्ठा console_font *font,
			   अचिन्हित पूर्णांक flags)
अणु
	वापस sticon_set_font(vc, font);
पूर्ण

अटल व्योम sticon_init(काष्ठा vc_data *c, पूर्णांक init)
अणु
    काष्ठा sti_काष्ठा *sti = sticon_sti;
    पूर्णांक vc_cols, vc_rows;

    sti_set(sti, 0, 0, sti_onscreen_y(sti), sti_onscreen_x(sti), 0);
    vc_cols = sti_onscreen_x(sti) / sti->font->width;
    vc_rows = sti_onscreen_y(sti) / sti->font->height;
    c->vc_can_करो_color = 1;
    
    अगर (init) अणु
	c->vc_cols = vc_cols;
	c->vc_rows = vc_rows;
    पूर्ण अन्यथा अणु
	vc_resize(c, vc_cols, vc_rows);
    पूर्ण
पूर्ण

अटल व्योम sticon_deinit(काष्ठा vc_data *c)
अणु
    पूर्णांक i;

    /* मुक्त memory used by user font */
    क्रम (i = 0; i < MAX_NR_CONSOLES; i++)
	sticon_set_def_font(i, शून्य);
पूर्ण

अटल व्योम sticon_clear(काष्ठा vc_data *conp, पूर्णांक sy, पूर्णांक sx, पूर्णांक height,
			 पूर्णांक width)
अणु
    अगर (!height || !width)
	वापस;

    sti_clear(sticon_sti, sy, sx, height, width,
	      conp->vc_video_erase_अक्षर, font_data[conp->vc_num]);
पूर्ण

अटल पूर्णांक sticon_चयन(काष्ठा vc_data *conp)
अणु
    वापस 1;	/* needs refreshing */
पूर्ण

अटल पूर्णांक sticon_blank(काष्ठा vc_data *c, पूर्णांक blank, पूर्णांक mode_चयन)
अणु
    अगर (blank == 0) अणु
	अगर (mode_चयन)
	    vga_is_gfx = 0;
	वापस 1;
    पूर्ण
    sti_clear(sticon_sti, 0, 0, c->vc_rows, c->vc_cols, BLANK,
	      font_data[c->vc_num]);
    अगर (mode_चयन)
	vga_is_gfx = 1;
    वापस 1;
पूर्ण

अटल u8 sticon_build_attr(काष्ठा vc_data *conp, u8 color,
			    क्रमागत vc_पूर्णांकensity पूर्णांकens,
			    bool blink, bool underline, bool reverse,
			    bool italic)
अणु
    u8 attr = ((color & 0x70) >> 1) | ((color & 7));

    अगर (reverse) अणु
	color = ((color >> 3) & 0x7) | ((color & 0x7) << 3);
    पूर्ण

    वापस attr;
पूर्ण

अटल व्योम sticon_invert_region(काष्ठा vc_data *conp, u16 *p, पूर्णांक count)
अणु
    पूर्णांक col = 1; /* vga_can_करो_color; */

    जबतक (count--) अणु
	u16 a = scr_पढ़ोw(p);

	अगर (col)
		a = ((a) & 0x88ff) | (((a) & 0x7000) >> 4) | (((a) & 0x0700) << 4);
	अन्यथा
		a = ((a & 0x0700) == 0x0100) ? 0x7000 : 0x7700;

	scr_ग_लिखोw(a, p++);
    पूर्ण
पूर्ण

अटल स्थिर काष्ठा consw sti_con = अणु
	.owner			= THIS_MODULE,
	.con_startup		= sticon_startup,
	.con_init		= sticon_init,
	.con_deinit		= sticon_deinit,
	.con_clear		= sticon_clear,
	.con_अ_दो		= sticon_अ_दो,
	.con_अ_दोs		= sticon_अ_दोs,
	.con_cursor		= sticon_cursor,
	.con_scroll		= sticon_scroll,
	.con_चयन		= sticon_चयन,
	.con_blank		= sticon_blank,
	.con_font_set		= sticon_font_set,
	.con_font_शेष	= sticon_font_शेष,
	.con_build_attr		= sticon_build_attr,
	.con_invert_region	= sticon_invert_region, 
पूर्ण;



अटल पूर्णांक __init sticonsole_init(व्योम)
अणु
    पूर्णांक err, i;

    /* alपढ़ोy initialized ? */
    अगर (sticon_sti)
	 वापस 0;

    sticon_sti = sti_get_rom(0);
    अगर (!sticon_sti)
	वापस -ENODEV;

    क्रम (i = 0; i < MAX_NR_CONSOLES; i++)
	font_data[i] = STI_DEF_FONT;

    pr_info("sticon: Initializing STI text console.\n");
    console_lock();
    err = करो_take_over_console(&sti_con, 0, MAX_NR_CONSOLES - 1,
		PAGE0->mem_cons.cl_class != CL_DUPLEX);
    console_unlock();

    वापस err;
पूर्ण

module_init(sticonsole_init);
MODULE_LICENSE("GPL");
