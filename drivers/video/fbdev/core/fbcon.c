<शैली गुरु>
/*
 *  linux/drivers/video/fbcon.c -- Low level frame buffer based console driver
 *
 *	Copyright (C) 1995 Geert Uytterhoeven
 *
 *
 *  This file is based on the original Amiga console driver (amicon.c):
 *
 *	Copyright (C) 1993 Hamish Macकरोnald
 *			   Greg Harp
 *	Copyright (C) 1994 David Carter [carter@compsci.bristol.ac.uk]
 *
 *	      with work by William Rucklidge (wjr@cs.cornell.edu)
 *			   Geert Uytterhoeven
 *			   Jes Sorensen (jds@kom.auc.dk)
 *			   Martin Apel
 *
 *  and on the original Atari console driver (atacon.c):
 *
 *	Copyright (C) 1993 Bjoern Brauel
 *			   Roman Hodek
 *
 *	      with work by Guenther Kelleter
 *			   Martin Schaller
 *			   Andreas Schwab
 *
 *  Hardware cursor support added by Emmanuel Marty (core@ggi-project.org)
 *  Smart redraw scrolling, arbitrary font width support, 512अक्षर font support
 *  and software scrollback added by 
 *                         Jakub Jelinek (jj@ultra.linux.cz)
 *
 *  Ranकरोm hacking by Martin Mares <mj@ucw.cz>
 *
 *	2001 - Documented with DocBook
 *	- Brad Douglas <brad@neruo.com>
 *
 *  The low level operations क्रम the various display memory organizations are
 *  now in separate source files.
 *
 *  Currently the following organizations are supported:
 *
 *    o afb			Amiga bitplanes
 *    o cfbअणु2,4,8,16,24,32पूर्ण	Packed pixels
 *    o ilbm			Amiga पूर्णांकerleaved bitplanes
 *    o iplan2p[248]		Atari पूर्णांकerleaved bitplanes
 *    o mfb			Monochrome
 *    o vga			VGA अक्षरacters/attributes
 *
 *  To करो:
 *
 *    - Implement 16 plane mode (iplan2p16)
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
#समावेश <linux/delay.h>	/* MSch: क्रम IRQ probe */
#समावेश <linux/console.h>
#समावेश <linux/माला.स>
#समावेश <linux/kd.h>
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>
#समावेश <linux/fbcon.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/selection.h>
#समावेश <linux/font.h>
#समावेश <linux/smp.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/crc32.h> /* For counting font checksums */
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/fb.h>
#समावेश <यंत्र/irq.h>

#समावेश "fbcon.h"

/*
 * FIXME: Locking
 *
 * - fbcon state itself is रक्षित by the console_lock, and the code करोes a
 *   pretty good job at making sure that lock is held everywhere it's needed.
 *
 * - access to the रेजिस्टरed_fb array is entirely unरक्षित. This should use
 *   proper object lअगरeसमय handling, i.e. get/put_fb_info. This also means
 *   चयनing from indices to proper poपूर्णांकers क्रम fb_info everywhere.
 *
 * - fbcon करोesn't bother with fb_lock/unlock at all. This is buggy, since it
 *   means concurrent access to the same fbdev from both fbcon and userspace
 *   will blow up. To fix this all fbcon calls from fbmem.c need to be moved out
 *   of fb_lock/unlock रक्षित sections, since otherwise we'll recurse and
 *   deadlock eventually. Aside: Due to these deadlock issues the fbdev code in
 *   fbmem.c cannot use locking निश्चितs, and there's lots of callers which get
 *   the rules wrong, e.g. fbsysfs.c entirely missed fb_lock/unlock calls too.
 */

क्रमागत अणु
	FBCON_LOGO_CANSHOW	= -1,	/* the logo can be shown */
	FBCON_LOGO_DRAW		= -2,	/* draw the logo to a console */
	FBCON_LOGO_DONTSHOW	= -3	/* करो not show the logo */
पूर्ण;

अटल काष्ठा fbcon_display fb_display[MAX_NR_CONSOLES];

अटल चिन्हित अक्षर con2fb_map[MAX_NR_CONSOLES];
अटल चिन्हित अक्षर con2fb_map_boot[MAX_NR_CONSOLES];

अटल पूर्णांक logo_lines;
/* logo_shown is an index to vc_cons when >= 0; otherwise follows FBCON_LOGO
   क्रमागतs.  */
अटल पूर्णांक logo_shown = FBCON_LOGO_CANSHOW;
/* console mappings */
अटल पूर्णांक first_fb_vc;
अटल पूर्णांक last_fb_vc = MAX_NR_CONSOLES - 1;
अटल पूर्णांक fbcon_is_शेष = 1; 
अटल पूर्णांक primary_device = -1;
अटल पूर्णांक fbcon_has_console_bind;

#अगर_घोषित CONFIG_FRAMEBUFFER_CONSOLE_DETECT_PRIMARY
अटल पूर्णांक map_override;

अटल अंतरभूत व्योम fbcon_map_override(व्योम)
अणु
	map_override = 1;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम fbcon_map_override(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_FRAMEBUFFER_CONSOLE_DETECT_PRIMARY */

#अगर_घोषित CONFIG_FRAMEBUFFER_CONSOLE_DEFERRED_TAKEOVER
अटल bool deferred_takeover = true;
#अन्यथा
#घोषणा deferred_takeover false
#पूर्ण_अगर

/* font data */
अटल अक्षर fontname[40];

/* current fb_info */
अटल पूर्णांक info_idx = -1;

/* console rotation */
अटल पूर्णांक initial_rotation = -1;
अटल पूर्णांक fbcon_has_sysfs;
अटल पूर्णांक margin_color;

अटल स्थिर काष्ठा consw fb_con;

#घोषणा advance_row(p, delta) (अचिन्हित लघु *)((अचिन्हित दीर्घ)(p) + (delta) * vc->vc_size_row)

अटल पूर्णांक fbcon_cursor_noblink;

#घोषणा भागides(a, b)	((!(a) || (b)%(a)) ? 0 : 1)

/*
 *  Interface used by the world
 */

अटल स्थिर अक्षर *fbcon_startup(व्योम);
अटल व्योम fbcon_init(काष्ठा vc_data *vc, पूर्णांक init);
अटल व्योम fbcon_deinit(काष्ठा vc_data *vc);
अटल व्योम fbcon_clear(काष्ठा vc_data *vc, पूर्णांक sy, पूर्णांक sx, पूर्णांक height,
			पूर्णांक width);
अटल व्योम fbcon_अ_दो(काष्ठा vc_data *vc, पूर्णांक c, पूर्णांक ypos, पूर्णांक xpos);
अटल व्योम fbcon_अ_दोs(काष्ठा vc_data *vc, स्थिर अचिन्हित लघु *s,
			पूर्णांक count, पूर्णांक ypos, पूर्णांक xpos);
अटल व्योम fbcon_clear_margins(काष्ठा vc_data *vc, पूर्णांक bottom_only);
अटल व्योम fbcon_cursor(काष्ठा vc_data *vc, पूर्णांक mode);
अटल व्योम fbcon_bmove(काष्ठा vc_data *vc, पूर्णांक sy, पूर्णांक sx, पूर्णांक dy, पूर्णांक dx,
			पूर्णांक height, पूर्णांक width);
अटल पूर्णांक fbcon_चयन(काष्ठा vc_data *vc);
अटल पूर्णांक fbcon_blank(काष्ठा vc_data *vc, पूर्णांक blank, पूर्णांक mode_चयन);
अटल व्योम fbcon_set_palette(काष्ठा vc_data *vc, स्थिर अचिन्हित अक्षर *table);

/*
 *  Internal routines
 */
अटल __अंतरभूत__ व्योम ywrap_up(काष्ठा vc_data *vc, पूर्णांक count);
अटल __अंतरभूत__ व्योम ywrap_करोwn(काष्ठा vc_data *vc, पूर्णांक count);
अटल __अंतरभूत__ व्योम ypan_up(काष्ठा vc_data *vc, पूर्णांक count);
अटल __अंतरभूत__ व्योम ypan_करोwn(काष्ठा vc_data *vc, पूर्णांक count);
अटल व्योम fbcon_bmove_rec(काष्ठा vc_data *vc, काष्ठा fbcon_display *p, पूर्णांक sy, पूर्णांक sx,
			    पूर्णांक dy, पूर्णांक dx, पूर्णांक height, पूर्णांक width, u_पूर्णांक y_अवरोध);
अटल व्योम fbcon_set_disp(काष्ठा fb_info *info, काष्ठा fb_var_screeninfo *var,
			   पूर्णांक unit);
अटल व्योम fbcon_redraw_move(काष्ठा vc_data *vc, काष्ठा fbcon_display *p,
			      पूर्णांक line, पूर्णांक count, पूर्णांक dy);
अटल व्योम fbcon_modechanged(काष्ठा fb_info *info);
अटल व्योम fbcon_set_all_vcs(काष्ठा fb_info *info);
अटल व्योम fbcon_start(व्योम);
अटल व्योम fbcon_निकास(व्योम);
अटल काष्ठा device *fbcon_device;

#अगर_घोषित CONFIG_FRAMEBUFFER_CONSOLE_ROTATION
अटल अंतरभूत व्योम fbcon_set_rotation(काष्ठा fb_info *info)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	अगर (!(info->flags & FBINFO_MISC_TILEBLITTING) &&
	    ops->p->con_rotate < 4)
		ops->rotate = ops->p->con_rotate;
	अन्यथा
		ops->rotate = 0;
पूर्ण

अटल व्योम fbcon_rotate(काष्ठा fb_info *info, u32 rotate)
अणु
	काष्ठा fbcon_ops *ops= info->fbcon_par;
	काष्ठा fb_info *fb_info;

	अगर (!ops || ops->currcon == -1)
		वापस;

	fb_info = रेजिस्टरed_fb[con2fb_map[ops->currcon]];

	अगर (info == fb_info) अणु
		काष्ठा fbcon_display *p = &fb_display[ops->currcon];

		अगर (rotate < 4)
			p->con_rotate = rotate;
		अन्यथा
			p->con_rotate = 0;

		fbcon_modechanged(info);
	पूर्ण
पूर्ण

अटल व्योम fbcon_rotate_all(काष्ठा fb_info *info, u32 rotate)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	काष्ठा vc_data *vc;
	काष्ठा fbcon_display *p;
	पूर्णांक i;

	अगर (!ops || ops->currcon < 0 || rotate > 3)
		वापस;

	क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
		vc = vc_cons[i].d;
		अगर (!vc || vc->vc_mode != KD_TEXT ||
		    रेजिस्टरed_fb[con2fb_map[i]] != info)
			जारी;

		p = &fb_display[vc->vc_num];
		p->con_rotate = rotate;
	पूर्ण

	fbcon_set_all_vcs(info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम fbcon_set_rotation(काष्ठा fb_info *info)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	ops->rotate = FB_ROTATE_UR;
पूर्ण

अटल व्योम fbcon_rotate(काष्ठा fb_info *info, u32 rotate)
अणु
	वापस;
पूर्ण

अटल व्योम fbcon_rotate_all(काष्ठा fb_info *info, u32 rotate)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर /* CONFIG_FRAMEBUFFER_CONSOLE_ROTATION */

अटल पूर्णांक fbcon_get_rotate(काष्ठा fb_info *info)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	वापस (ops) ? ops->rotate : 0;
पूर्ण

अटल अंतरभूत पूर्णांक fbcon_is_inactive(काष्ठा vc_data *vc, काष्ठा fb_info *info)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	वापस (info->state != FBINFO_STATE_RUNNING ||
		vc->vc_mode != KD_TEXT || ops->graphics);
पूर्ण

अटल पूर्णांक get_color(काष्ठा vc_data *vc, काष्ठा fb_info *info,
	      u16 c, पूर्णांक is_fg)
अणु
	पूर्णांक depth = fb_get_color_depth(&info->var, &info->fix);
	पूर्णांक color = 0;

	अगर (console_blanked) अणु
		अचिन्हित लघु अक्षरmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;

		c = vc->vc_video_erase_अक्षर & अक्षरmask;
	पूर्ण

	अगर (depth != 1)
		color = (is_fg) ? attr_fgcol((vc->vc_hi_font_mask) ? 9 : 8, c)
			: attr_bgcol((vc->vc_hi_font_mask) ? 13 : 12, c);

	चयन (depth) अणु
	हाल 1:
	अणु
		पूर्णांक col = mono_col(info);
		/* 0 or 1 */
		पूर्णांक fg = (info->fix.visual != FB_VISUAL_MONO01) ? col : 0;
		पूर्णांक bg = (info->fix.visual != FB_VISUAL_MONO01) ? 0 : col;

		अगर (console_blanked)
			fg = bg;

		color = (is_fg) ? fg : bg;
		अवरोध;
	पूर्ण
	हाल 2:
		/*
		 * Scale करोwn 16-colors to 4 colors. Default 4-color palette
		 * is grayscale. However, simply भागiding the values by 4
		 * will not work, as colors 1, 2 and 3 will be scaled-करोwn
		 * to zero rendering them invisible.  So empirically convert
		 * colors to a sane 4-level grayscale.
		 */
		चयन (color) अणु
		हाल 0:
			color = 0; /* black */
			अवरोध;
		हाल 1 ... 6:
			color = 2; /* white */
			अवरोध;
		हाल 7 ... 8:
			color = 1; /* gray */
			अवरोध;
		शेष:
			color = 3; /* पूर्णांकense white */
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 3:
		/*
		 * Last 8 entries of शेष 16-color palette is a more पूर्णांकense
		 * version of the first 8 (i.e., same chrominance, dअगरferent
		 * luminance).
		 */
		color &= 7;
		अवरोध;
	पूर्ण


	वापस color;
पूर्ण

अटल व्योम fb_flashcursor(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fb_info *info = container_of(work, काष्ठा fb_info, queue);
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	काष्ठा vc_data *vc = शून्य;
	पूर्णांक c;
	पूर्णांक mode;
	पूर्णांक ret;

	/* FIXME: we should sort out the unbind locking instead */
	/* instead we just fail to flash the cursor अगर we can't get
	 * the lock instead of blocking fbcon deinit */
	ret = console_trylock();
	अगर (ret == 0)
		वापस;

	अगर (ops && ops->currcon != -1)
		vc = vc_cons[ops->currcon].d;

	अगर (!vc || !con_is_visible(vc) ||
 	    रेजिस्टरed_fb[con2fb_map[vc->vc_num]] != info ||
	    vc->vc_deccm != 1) अणु
		console_unlock();
		वापस;
	पूर्ण

	c = scr_पढ़ोw((u16 *) vc->vc_pos);
	mode = (!ops->cursor_flash || ops->cursor_state.enable) ?
		CM_ERASE : CM_DRAW;
	ops->cursor(vc, info, mode, get_color(vc, info, c, 1),
		    get_color(vc, info, c, 0));
	console_unlock();
पूर्ण

अटल व्योम cursor_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा fbcon_ops *ops = from_समयr(ops, t, cursor_समयr);
	काष्ठा fb_info *info = ops->info;

	queue_work(प्रणाली_घातer_efficient_wq, &info->queue);
	mod_समयr(&ops->cursor_समयr, jअगरfies + ops->cur_blink_jअगरfies);
पूर्ण

अटल व्योम fbcon_add_cursor_समयr(काष्ठा fb_info *info)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	अगर ((!info->queue.func || info->queue.func == fb_flashcursor) &&
	    !(ops->flags & FBCON_FLAGS_CURSOR_TIMER) &&
	    !fbcon_cursor_noblink) अणु
		अगर (!info->queue.func)
			INIT_WORK(&info->queue, fb_flashcursor);

		समयr_setup(&ops->cursor_समयr, cursor_समयr_handler, 0);
		mod_समयr(&ops->cursor_समयr, jअगरfies + ops->cur_blink_jअगरfies);
		ops->flags |= FBCON_FLAGS_CURSOR_TIMER;
	पूर्ण
पूर्ण

अटल व्योम fbcon_del_cursor_समयr(काष्ठा fb_info *info)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	अगर (info->queue.func == fb_flashcursor &&
	    ops->flags & FBCON_FLAGS_CURSOR_TIMER) अणु
		del_समयr_sync(&ops->cursor_समयr);
		ops->flags &= ~FBCON_FLAGS_CURSOR_TIMER;
	पूर्ण
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक __init fb_console_setup(अक्षर *this_opt)
अणु
	अक्षर *options;
	पूर्णांक i, j;

	अगर (!this_opt || !*this_opt)
		वापस 1;

	जबतक ((options = strsep(&this_opt, ",")) != शून्य) अणु
		अगर (!म_भेदन(options, "font:", 5)) अणु
			strlcpy(fontname, options + 5, माप(fontname));
			जारी;
		पूर्ण
		
		अगर (!म_भेदन(options, "scrollback:", 11)) अणु
			pr_warn("Ignoring scrollback size option\n");
			जारी;
		पूर्ण
		
		अगर (!म_भेदन(options, "map:", 4)) अणु
			options += 4;
			अगर (*options) अणु
				क्रम (i = 0, j = 0; i < MAX_NR_CONSOLES; i++) अणु
					अगर (!options[j])
						j = 0;
					con2fb_map_boot[i] =
						(options[j++]-'0') % FB_MAX;
				पूर्ण

				fbcon_map_override();
			पूर्ण
			जारी;
		पूर्ण

		अगर (!म_भेदन(options, "vc:", 3)) अणु
			options += 3;
			अगर (*options)
				first_fb_vc = simple_म_से_अदीर्घ(options, &options, 10) - 1;
			अगर (first_fb_vc < 0)
				first_fb_vc = 0;
			अगर (*options++ == '-')
				last_fb_vc = simple_म_से_अदीर्घ(options, &options, 10) - 1;
			fbcon_is_शेष = 0; 
			जारी;
		पूर्ण

		अगर (!म_भेदन(options, "rotate:", 7)) अणु
			options += 7;
			अगर (*options)
				initial_rotation = simple_म_से_अदीर्घ(options, &options, 0);
			अगर (initial_rotation > 3)
				initial_rotation = 0;
			जारी;
		पूर्ण

		अगर (!म_भेदन(options, "margin:", 7)) अणु
			options += 7;
			अगर (*options)
				margin_color = simple_म_से_अदीर्घ(options, &options, 0);
			जारी;
		पूर्ण
#अगर_घोषित CONFIG_FRAMEBUFFER_CONSOLE_DEFERRED_TAKEOVER
		अगर (!म_भेद(options, "nodefer")) अणु
			deferred_takeover = false;
			जारी;
		पूर्ण
#पूर्ण_अगर

		अगर (!म_भेदन(options, "logo-pos:", 9)) अणु
			options += 9;
			अगर (!म_भेद(options, "center"))
				fb_center_logo = true;
			जारी;
		पूर्ण

		अगर (!म_भेदन(options, "logo-count:", 11)) अणु
			options += 11;
			अगर (*options)
				fb_logo_count = simple_म_से_दीर्घ(options, &options, 0);
			जारी;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

__setup("fbcon=", fb_console_setup);
#पूर्ण_अगर

अटल पूर्णांक search_fb_in_map(पूर्णांक idx)
अणु
	पूर्णांक i, retval = 0;

	क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
		अगर (con2fb_map[i] == idx)
			retval = 1;
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक search_क्रम_mapped_con(व्योम)
अणु
	पूर्णांक i, retval = 0;

	क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
		अगर (con2fb_map[i] != -1)
			retval = 1;
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक करो_fbcon_takeover(पूर्णांक show_logo)
अणु
	पूर्णांक err, i;

	अगर (!num_रेजिस्टरed_fb)
		वापस -ENODEV;

	अगर (!show_logo)
		logo_shown = FBCON_LOGO_DONTSHOW;

	क्रम (i = first_fb_vc; i <= last_fb_vc; i++)
		con2fb_map[i] = info_idx;

	err = करो_take_over_console(&fb_con, first_fb_vc, last_fb_vc,
				fbcon_is_शेष);

	अगर (err) अणु
		क्रम (i = first_fb_vc; i <= last_fb_vc; i++)
			con2fb_map[i] = -1;
		info_idx = -1;
	पूर्ण अन्यथा अणु
		fbcon_has_console_bind = 1;
	पूर्ण

	वापस err;
पूर्ण

#अगर_घोषित MODULE
अटल व्योम fbcon_prepare_logo(काष्ठा vc_data *vc, काष्ठा fb_info *info,
			       पूर्णांक cols, पूर्णांक rows, पूर्णांक new_cols, पूर्णांक new_rows)
अणु
	logo_shown = FBCON_LOGO_DONTSHOW;
पूर्ण
#अन्यथा
अटल व्योम fbcon_prepare_logo(काष्ठा vc_data *vc, काष्ठा fb_info *info,
			       पूर्णांक cols, पूर्णांक rows, पूर्णांक new_cols, पूर्णांक new_rows)
अणु
	/* Need to make room क्रम the logo */
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	पूर्णांक cnt, erase = vc->vc_video_erase_अक्षर, step;
	अचिन्हित लघु *save = शून्य, *r, *q;
	पूर्णांक logo_height;

	अगर (info->fbops->owner) अणु
		logo_shown = FBCON_LOGO_DONTSHOW;
		वापस;
	पूर्ण

	/*
	 * हटाओ underline attribute from erase अक्षरacter
	 * अगर black and white framebuffer.
	 */
	अगर (fb_get_color_depth(&info->var, &info->fix) == 1)
		erase &= ~0x400;
	logo_height = fb_prepare_logo(info, ops->rotate);
	logo_lines = DIV_ROUND_UP(logo_height, vc->vc_font.height);
	q = (अचिन्हित लघु *) (vc->vc_origin +
				vc->vc_size_row * rows);
	step = logo_lines * cols;
	क्रम (r = q - logo_lines * cols; r < q; r++)
		अगर (scr_पढ़ोw(r) != vc->vc_video_erase_अक्षर)
			अवरोध;
	अगर (r != q && new_rows >= rows + logo_lines) अणु
		save = kदो_स्मृति(array3_size(logo_lines, new_cols, 2),
			       GFP_KERNEL);
		अगर (save) अणु
			पूर्णांक i = cols < new_cols ? cols : new_cols;
			scr_स_रखोw(save, erase, array3_size(logo_lines, new_cols, 2));
			r = q - step;
			क्रम (cnt = 0; cnt < logo_lines; cnt++, r += i)
				scr_स_नकलw(save + cnt * new_cols, r, 2 * i);
			r = q;
		पूर्ण
	पूर्ण
	अगर (r == q) अणु
		/* We can scroll screen करोwn */
		r = q - step - cols;
		क्रम (cnt = rows - logo_lines; cnt > 0; cnt--) अणु
			scr_स_नकलw(r + step, r, vc->vc_size_row);
			r -= cols;
		पूर्ण
		अगर (!save) अणु
			पूर्णांक lines;
			अगर (vc->state.y + logo_lines >= rows)
				lines = rows - vc->state.y - 1;
			अन्यथा
				lines = logo_lines;
			vc->state.y += lines;
			vc->vc_pos += lines * vc->vc_size_row;
		पूर्ण
	पूर्ण
	scr_स_रखोw((अचिन्हित लघु *) vc->vc_origin,
		    erase,
		    vc->vc_size_row * logo_lines);

	अगर (con_is_visible(vc) && vc->vc_mode == KD_TEXT) अणु
		fbcon_clear_margins(vc, 0);
		update_screen(vc);
	पूर्ण

	अगर (save) अणु
		q = (अचिन्हित लघु *) (vc->vc_origin +
					vc->vc_size_row *
					rows);
		scr_स_नकलw(q, save, array3_size(logo_lines, new_cols, 2));
		vc->state.y += logo_lines;
		vc->vc_pos += logo_lines * vc->vc_size_row;
		kमुक्त(save);
	पूर्ण

	अगर (logo_shown == FBCON_LOGO_DONTSHOW)
		वापस;

	अगर (logo_lines > vc->vc_bottom) अणु
		logo_shown = FBCON_LOGO_CANSHOW;
		prपूर्णांकk(KERN_INFO
		       "fbcon_init: disable boot-logo (boot-logo bigger than screen).\n");
	पूर्ण अन्यथा अणु
		logo_shown = FBCON_LOGO_DRAW;
		vc->vc_top = logo_lines;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* MODULE */

#अगर_घोषित CONFIG_FB_TILEBLITTING
अटल व्योम set_blitting_type(काष्ठा vc_data *vc, काष्ठा fb_info *info)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	ops->p = &fb_display[vc->vc_num];

	अगर ((info->flags & FBINFO_MISC_TILEBLITTING))
		fbcon_set_tileops(vc, info);
	अन्यथा अणु
		fbcon_set_rotation(info);
		fbcon_set_bitops(ops);
	पूर्ण
पूर्ण

अटल पूर्णांक fbcon_invalid_अक्षरcount(काष्ठा fb_info *info, अचिन्हित अक्षरcount)
अणु
	पूर्णांक err = 0;

	अगर (info->flags & FBINFO_MISC_TILEBLITTING &&
	    info->tileops->fb_get_tilemax(info) < अक्षरcount)
		err = 1;

	वापस err;
पूर्ण
#अन्यथा
अटल व्योम set_blitting_type(काष्ठा vc_data *vc, काष्ठा fb_info *info)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	info->flags &= ~FBINFO_MISC_TILEBLITTING;
	ops->p = &fb_display[vc->vc_num];
	fbcon_set_rotation(info);
	fbcon_set_bitops(ops);
पूर्ण

अटल पूर्णांक fbcon_invalid_अक्षरcount(काष्ठा fb_info *info, अचिन्हित अक्षरcount)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_MISC_TILEBLITTING */


अटल पूर्णांक con2fb_acquire_newinfo(काष्ठा vc_data *vc, काष्ठा fb_info *info,
				  पूर्णांक unit, पूर्णांक oldidx)
अणु
	काष्ठा fbcon_ops *ops = शून्य;
	पूर्णांक err = 0;

	अगर (!try_module_get(info->fbops->owner))
		err = -ENODEV;

	अगर (!err && info->fbops->fb_खोलो &&
	    info->fbops->fb_खोलो(info, 0))
		err = -ENODEV;

	अगर (!err) अणु
		ops = kzalloc(माप(काष्ठा fbcon_ops), GFP_KERNEL);
		अगर (!ops)
			err = -ENOMEM;
	पूर्ण

	अगर (!err) अणु
		ops->cur_blink_jअगरfies = HZ / 5;
		ops->info = info;
		info->fbcon_par = ops;

		अगर (vc)
			set_blitting_type(vc, info);
	पूर्ण

	अगर (err) अणु
		con2fb_map[unit] = oldidx;
		module_put(info->fbops->owner);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक con2fb_release_oldinfo(काष्ठा vc_data *vc, काष्ठा fb_info *oldinfo,
				  काष्ठा fb_info *newinfo, पूर्णांक unit,
				  पूर्णांक oldidx, पूर्णांक found)
अणु
	काष्ठा fbcon_ops *ops = oldinfo->fbcon_par;
	पूर्णांक err = 0, ret;

	अगर (oldinfo->fbops->fb_release &&
	    oldinfo->fbops->fb_release(oldinfo, 0)) अणु
		con2fb_map[unit] = oldidx;
		अगर (!found && newinfo->fbops->fb_release)
			newinfo->fbops->fb_release(newinfo, 0);
		अगर (!found)
			module_put(newinfo->fbops->owner);
		err = -ENODEV;
	पूर्ण

	अगर (!err) अणु
		fbcon_del_cursor_समयr(oldinfo);
		kमुक्त(ops->cursor_state.mask);
		kमुक्त(ops->cursor_data);
		kमुक्त(ops->cursor_src);
		kमुक्त(ops->fontbuffer);
		kमुक्त(oldinfo->fbcon_par);
		oldinfo->fbcon_par = शून्य;
		module_put(oldinfo->fbops->owner);
		/*
		  If oldinfo and newinfo are driving the same hardware,
		  the fb_release() method of oldinfo may attempt to
		  restore the hardware state.  This will leave the
		  newinfo in an undefined state. Thus, a call to
		  fb_set_par() may be needed क्रम the newinfo.
		*/
		अगर (newinfo && newinfo->fbops->fb_set_par) अणु
			ret = newinfo->fbops->fb_set_par(newinfo);

			अगर (ret)
				prपूर्णांकk(KERN_ERR "con2fb_release_oldinfo: "
					"detected unhandled fb_set_par error, "
					"error code %d\n", ret);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम con2fb_init_display(काष्ठा vc_data *vc, काष्ठा fb_info *info,
				पूर्णांक unit, पूर्णांक show_logo)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	पूर्णांक ret;

	ops->currcon = fg_console;

	अगर (info->fbops->fb_set_par && !(ops->flags & FBCON_FLAGS_INIT)) अणु
		ret = info->fbops->fb_set_par(info);

		अगर (ret)
			prपूर्णांकk(KERN_ERR "con2fb_init_display: detected "
				"unhandled fb_set_par error, "
				"error code %d\n", ret);
	पूर्ण

	ops->flags |= FBCON_FLAGS_INIT;
	ops->graphics = 0;
	fbcon_set_disp(info, &info->var, unit);

	अगर (show_logo) अणु
		काष्ठा vc_data *fg_vc = vc_cons[fg_console].d;
		काष्ठा fb_info *fg_info =
			रेजिस्टरed_fb[con2fb_map[fg_console]];

		fbcon_prepare_logo(fg_vc, fg_info, fg_vc->vc_cols,
				   fg_vc->vc_rows, fg_vc->vc_cols,
				   fg_vc->vc_rows);
	पूर्ण

	update_screen(vc_cons[fg_console].d);
पूर्ण

/**
 *	set_con2fb_map - map console to frame buffer device
 *	@unit: भव console number to map
 *	@newidx: frame buffer index to map भव console to
 *      @user: user request
 *
 *	Maps a भव console @unit to a frame buffer device
 *	@newidx.
 *
 *	This should be called with the console lock held.
 */
अटल पूर्णांक set_con2fb_map(पूर्णांक unit, पूर्णांक newidx, पूर्णांक user)
अणु
	काष्ठा vc_data *vc = vc_cons[unit].d;
	पूर्णांक oldidx = con2fb_map[unit];
	काष्ठा fb_info *info = रेजिस्टरed_fb[newidx];
	काष्ठा fb_info *oldinfo = शून्य;
	पूर्णांक found, err = 0;

	WARN_CONSOLE_UNLOCKED();

	अगर (oldidx == newidx)
		वापस 0;

	अगर (!info)
		वापस -EINVAL;

	अगर (!search_क्रम_mapped_con() || !con_is_bound(&fb_con)) अणु
		info_idx = newidx;
		वापस करो_fbcon_takeover(0);
	पूर्ण

	अगर (oldidx != -1)
		oldinfo = रेजिस्टरed_fb[oldidx];

	found = search_fb_in_map(newidx);

	con2fb_map[unit] = newidx;
	अगर (!err && !found)
		err = con2fb_acquire_newinfo(vc, info, unit, oldidx);

	/*
	 * If old fb is not mapped to any of the consoles,
	 * fbcon should release it.
	 */
	अगर (!err && oldinfo && !search_fb_in_map(oldidx))
		err = con2fb_release_oldinfo(vc, oldinfo, info, unit, oldidx,
					     found);

	अगर (!err) अणु
		पूर्णांक show_logo = (fg_console == 0 && !user &&
				 logo_shown != FBCON_LOGO_DONTSHOW);

		अगर (!found)
			fbcon_add_cursor_समयr(info);
		con2fb_map_boot[unit] = newidx;
		con2fb_init_display(vc, info, unit, show_logo);
	पूर्ण

	अगर (!search_fb_in_map(info_idx))
		info_idx = newidx;

	वापस err;
पूर्ण

/*
 *  Low Level Operations
 */
/* NOTE: fbcon cannot be __init: it may be called from करो_take_over_console later */
अटल पूर्णांक var_to_display(काष्ठा fbcon_display *disp,
			  काष्ठा fb_var_screeninfo *var,
			  काष्ठा fb_info *info)
अणु
	disp->xres_भव = var->xres_भव;
	disp->yres_भव = var->yres_भव;
	disp->bits_per_pixel = var->bits_per_pixel;
	disp->grayscale = var->grayscale;
	disp->nonstd = var->nonstd;
	disp->accel_flags = var->accel_flags;
	disp->height = var->height;
	disp->width = var->width;
	disp->red = var->red;
	disp->green = var->green;
	disp->blue = var->blue;
	disp->transp = var->transp;
	disp->rotate = var->rotate;
	disp->mode = fb_match_mode(var, &info->modelist);
	अगर (disp->mode == शून्य)
		/* This should not happen */
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम display_to_var(काष्ठा fb_var_screeninfo *var,
			   काष्ठा fbcon_display *disp)
अणु
	fb_videomode_to_var(var, disp->mode);
	var->xres_भव = disp->xres_भव;
	var->yres_भव = disp->yres_भव;
	var->bits_per_pixel = disp->bits_per_pixel;
	var->grayscale = disp->grayscale;
	var->nonstd = disp->nonstd;
	var->accel_flags = disp->accel_flags;
	var->height = disp->height;
	var->width = disp->width;
	var->red = disp->red;
	var->green = disp->green;
	var->blue = disp->blue;
	var->transp = disp->transp;
	var->rotate = disp->rotate;
पूर्ण

अटल स्थिर अक्षर *fbcon_startup(व्योम)
अणु
	स्थिर अक्षर *display_desc = "frame buffer device";
	काष्ठा fbcon_display *p = &fb_display[fg_console];
	काष्ठा vc_data *vc = vc_cons[fg_console].d;
	स्थिर काष्ठा font_desc *font = शून्य;
	काष्ठा module *owner;
	काष्ठा fb_info *info = शून्य;
	काष्ठा fbcon_ops *ops;
	पूर्णांक rows, cols;

	/*
	 *  If num_रेजिस्टरed_fb is zero, this is a call क्रम the dummy part.
	 *  The frame buffer devices weren't initialized yet.
	 */
	अगर (!num_रेजिस्टरed_fb || info_idx == -1)
		वापस display_desc;
	/*
	 * Instead of blindly using रेजिस्टरed_fb[0], we use info_idx, set by
	 * fb_console_init();
	 */
	info = रेजिस्टरed_fb[info_idx];
	अगर (!info)
		वापस शून्य;
	
	owner = info->fbops->owner;
	अगर (!try_module_get(owner))
		वापस शून्य;
	अगर (info->fbops->fb_खोलो && info->fbops->fb_खोलो(info, 0)) अणु
		module_put(owner);
		वापस शून्य;
	पूर्ण

	ops = kzalloc(माप(काष्ठा fbcon_ops), GFP_KERNEL);
	अगर (!ops) अणु
		module_put(owner);
		वापस शून्य;
	पूर्ण

	ops->currcon = -1;
	ops->graphics = 1;
	ops->cur_rotate = -1;
	ops->cur_blink_jअगरfies = HZ / 5;
	ops->info = info;
	info->fbcon_par = ops;

	p->con_rotate = initial_rotation;
	अगर (p->con_rotate == -1)
		p->con_rotate = info->fbcon_rotate_hपूर्णांक;
	अगर (p->con_rotate == -1)
		p->con_rotate = FB_ROTATE_UR;

	set_blitting_type(vc, info);

	/* Setup शेष font */
	अगर (!p->fontdata && !vc->vc_font.data) अणु
		अगर (!fontname[0] || !(font = find_font(fontname)))
			font = get_शेष_font(info->var.xres,
						info->var.yres,
						info->pixmap.blit_x,
						info->pixmap.blit_y);
		vc->vc_font.width = font->width;
		vc->vc_font.height = font->height;
		vc->vc_font.data = (व्योम *)(p->fontdata = font->data);
		vc->vc_font.अक्षरcount = font->अक्षरcount;
	पूर्ण अन्यथा अणु
		p->fontdata = vc->vc_font.data;
	पूर्ण

	cols = FBCON_SWAP(ops->rotate, info->var.xres, info->var.yres);
	rows = FBCON_SWAP(ops->rotate, info->var.yres, info->var.xres);
	cols /= vc->vc_font.width;
	rows /= vc->vc_font.height;
	vc_resize(vc, cols, rows);

	pr_debug("mode:   %s\n", info->fix.id);
	pr_debug("visual: %d\n", info->fix.visual);
	pr_debug("res:    %dx%d-%d\n", info->var.xres,
		 info->var.yres,
		 info->var.bits_per_pixel);

	fbcon_add_cursor_समयr(info);
	वापस display_desc;
पूर्ण

अटल व्योम fbcon_init(काष्ठा vc_data *vc, पूर्णांक init)
अणु
	काष्ठा fb_info *info;
	काष्ठा fbcon_ops *ops;
	काष्ठा vc_data **शेष_mode = vc->vc_display_fg;
	काष्ठा vc_data *svc = *शेष_mode;
	काष्ठा fbcon_display *t, *p = &fb_display[vc->vc_num];
	पूर्णांक logo = 1, new_rows, new_cols, rows, cols;
	पूर्णांक ret;

	अगर (WARN_ON(info_idx == -1))
	    वापस;

	अगर (con2fb_map[vc->vc_num] == -1)
		con2fb_map[vc->vc_num] = info_idx;

	info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];

	अगर (logo_shown < 0 && console_loglevel <= CONSOLE_LOGLEVEL_QUIET)
		logo_shown = FBCON_LOGO_DONTSHOW;

	अगर (vc != svc || logo_shown == FBCON_LOGO_DONTSHOW ||
	    (info->fix.type == FB_TYPE_TEXT))
		logo = 0;

	अगर (var_to_display(p, &info->var, info))
		वापस;

	अगर (!info->fbcon_par)
		con2fb_acquire_newinfo(vc, info, vc->vc_num, -1);

	/* If we are not the first console on this
	   fb, copy the font from that console */
	t = &fb_display[fg_console];
	अगर (!p->fontdata) अणु
		अगर (t->fontdata) अणु
			काष्ठा vc_data *fvc = vc_cons[fg_console].d;

			vc->vc_font.data = (व्योम *)(p->fontdata =
						    fvc->vc_font.data);
			vc->vc_font.width = fvc->vc_font.width;
			vc->vc_font.height = fvc->vc_font.height;
			vc->vc_font.अक्षरcount = fvc->vc_font.अक्षरcount;
			p->userfont = t->userfont;

			अगर (p->userfont)
				REFCOUNT(p->fontdata)++;
		पूर्ण अन्यथा अणु
			स्थिर काष्ठा font_desc *font = शून्य;

			अगर (!fontname[0] || !(font = find_font(fontname)))
				font = get_शेष_font(info->var.xres,
							info->var.yres,
							info->pixmap.blit_x,
							info->pixmap.blit_y);
			vc->vc_font.width = font->width;
			vc->vc_font.height = font->height;
			vc->vc_font.data = (व्योम *)(p->fontdata = font->data);
			vc->vc_font.अक्षरcount = font->अक्षरcount;
		पूर्ण
	पूर्ण

	vc->vc_can_करो_color = (fb_get_color_depth(&info->var, &info->fix)!=1);
	vc->vc_complement_mask = vc->vc_can_करो_color ? 0x7700 : 0x0800;
	अगर (vc->vc_font.अक्षरcount == 256) अणु
		vc->vc_hi_font_mask = 0;
	पूर्ण अन्यथा अणु
		vc->vc_hi_font_mask = 0x100;
		अगर (vc->vc_can_करो_color)
			vc->vc_complement_mask <<= 1;
	पूर्ण

	अगर (!*svc->vc_uni_pagedir_loc)
		con_set_शेष_unimap(svc);
	अगर (!*vc->vc_uni_pagedir_loc)
		con_copy_unimap(vc, svc);

	ops = info->fbcon_par;
	ops->cur_blink_jअगरfies = msecs_to_jअगरfies(vc->vc_cur_blink_ms);

	p->con_rotate = initial_rotation;
	अगर (p->con_rotate == -1)
		p->con_rotate = info->fbcon_rotate_hपूर्णांक;
	अगर (p->con_rotate == -1)
		p->con_rotate = FB_ROTATE_UR;

	set_blitting_type(vc, info);

	cols = vc->vc_cols;
	rows = vc->vc_rows;
	new_cols = FBCON_SWAP(ops->rotate, info->var.xres, info->var.yres);
	new_rows = FBCON_SWAP(ops->rotate, info->var.yres, info->var.xres);
	new_cols /= vc->vc_font.width;
	new_rows /= vc->vc_font.height;

	/*
	 * We must always set the mode. The mode of the previous console
	 * driver could be in the same resolution but we are using dअगरferent
	 * hardware so we have to initialize the hardware.
	 *
	 * We need to करो it in fbcon_init() to prevent screen corruption.
	 */
	अगर (con_is_visible(vc) && vc->vc_mode == KD_TEXT) अणु
		अगर (info->fbops->fb_set_par &&
		    !(ops->flags & FBCON_FLAGS_INIT)) अणु
			ret = info->fbops->fb_set_par(info);

			अगर (ret)
				prपूर्णांकk(KERN_ERR "fbcon_init: detected "
					"unhandled fb_set_par error, "
					"error code %d\n", ret);
		पूर्ण

		ops->flags |= FBCON_FLAGS_INIT;
	पूर्ण

	ops->graphics = 0;

	/*
	 * No more hw acceleration क्रम fbcon.
	 *
	 * FIXME: Garbage collect all the now dead code after sufficient समय
	 * has passed.
	 */
	p->scrollmode = SCROLL_REDRAW;

	/*
	 *  ++guenther: console.c:vc_allocate() relies on initializing
	 *  vc_अणुcols,rowsपूर्ण, but we must not set those अगर we are only
	 *  resizing the console.
	 */
	अगर (init) अणु
		vc->vc_cols = new_cols;
		vc->vc_rows = new_rows;
	पूर्ण अन्यथा
		vc_resize(vc, new_cols, new_rows);

	अगर (logo)
		fbcon_prepare_logo(vc, info, cols, rows, new_cols, new_rows);

	अगर (ops->rotate_font && ops->rotate_font(info, vc)) अणु
		ops->rotate = FB_ROTATE_UR;
		set_blitting_type(vc, info);
	पूर्ण

	ops->p = &fb_display[fg_console];
पूर्ण

अटल व्योम fbcon_मुक्त_font(काष्ठा fbcon_display *p, bool मुक्तfont)
अणु
	अगर (मुक्तfont && p->userfont && p->fontdata && (--REFCOUNT(p->fontdata) == 0))
		kमुक्त(p->fontdata - FONT_EXTRA_WORDS * माप(पूर्णांक));
	p->fontdata = शून्य;
	p->userfont = 0;
पूर्ण

अटल व्योम set_vc_hi_font(काष्ठा vc_data *vc, bool set);

अटल व्योम fbcon_deinit(काष्ठा vc_data *vc)
अणु
	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];
	काष्ठा fb_info *info;
	काष्ठा fbcon_ops *ops;
	पूर्णांक idx;
	bool मुक्त_font = true;

	idx = con2fb_map[vc->vc_num];

	अगर (idx == -1)
		जाओ finished;

	info = रेजिस्टरed_fb[idx];

	अगर (!info)
		जाओ finished;

	अगर (info->flags & FBINFO_MISC_FIRMWARE)
		मुक्त_font = false;
	ops = info->fbcon_par;

	अगर (!ops)
		जाओ finished;

	अगर (con_is_visible(vc))
		fbcon_del_cursor_समयr(info);

	ops->flags &= ~FBCON_FLAGS_INIT;
finished:

	fbcon_मुक्त_font(p, मुक्त_font);
	अगर (मुक्त_font)
		vc->vc_font.data = शून्य;

	अगर (vc->vc_hi_font_mask && vc->vc_screenbuf)
		set_vc_hi_font(vc, false);

	अगर (!con_is_bound(&fb_con))
		fbcon_निकास();

	अगर (vc->vc_num == logo_shown)
		logo_shown = FBCON_LOGO_CANSHOW;

	वापस;
पूर्ण

/* ====================================================================== */

/*  fbcon_XXX routines - पूर्णांकerface used by the world
 *
 *  This प्रणाली is now भागided पूर्णांकo two levels because of complications
 *  caused by hardware scrolling. Top level functions:
 *
 *	fbcon_bmove(), fbcon_clear(), fbcon_अ_दो(), fbcon_clear_margins()
 *
 *  handles y values in range [0, scr_height-1] that correspond to real
 *  screen positions. y_wrap shअगरt means that first line of biपंचांगap may be
 *  anywhere on this display. These functions convert lineoffsets to
 *  biपंचांगap offsets and deal with the wrap-around हाल by splitting blits.
 *
 *	fbcon_bmove_physical_8()    -- These functions fast implementations
 *	fbcon_clear_physical_8()    -- of original fbcon_XXX fns.
 *	fbcon_अ_दो_physical_8()	    -- (font width != 8) may be added later
 *
 *  WARNING:
 *
 *  At the moment fbcon_अ_दो() cannot blit across vertical wrap boundary
 *  Implies should only really hardware scroll in rows. Only reason क्रम
 *  restriction is simplicity & efficiency at the moment.
 */

अटल व्योम fbcon_clear(काष्ठा vc_data *vc, पूर्णांक sy, पूर्णांक sx, पूर्णांक height,
			पूर्णांक width)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];
	u_पूर्णांक y_अवरोध;

	अगर (fbcon_is_inactive(vc, info))
		वापस;

	अगर (!height || !width)
		वापस;

	अगर (sy < vc->vc_top && vc->vc_top == logo_lines) अणु
		vc->vc_top = 0;
		/*
		 * If the font dimensions are not an पूर्णांकegral of the display
		 * dimensions then the ops->clear below won't end up clearing
		 * the margins.  Call clear_margins here in हाल the logo
		 * biपंचांगap stretched पूर्णांकo the margin area.
		 */
		fbcon_clear_margins(vc, 0);
	पूर्ण

	/* Split blits that cross physical y_wrap boundary */

	y_अवरोध = p->vrows - p->yscroll;
	अगर (sy < y_अवरोध && sy + height - 1 >= y_अवरोध) अणु
		u_पूर्णांक b = y_अवरोध - sy;
		ops->clear(vc, info, real_y(p, sy), sx, b, width);
		ops->clear(vc, info, real_y(p, sy + b), sx, height - b,
				 width);
	पूर्ण अन्यथा
		ops->clear(vc, info, real_y(p, sy), sx, height, width);
पूर्ण

अटल व्योम fbcon_अ_दोs(काष्ठा vc_data *vc, स्थिर अचिन्हित लघु *s,
			पूर्णांक count, पूर्णांक ypos, पूर्णांक xpos)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	अगर (!fbcon_is_inactive(vc, info))
		ops->अ_दोs(vc, info, s, count, real_y(p, ypos), xpos,
			   get_color(vc, info, scr_पढ़ोw(s), 1),
			   get_color(vc, info, scr_पढ़ोw(s), 0));
पूर्ण

अटल व्योम fbcon_अ_दो(काष्ठा vc_data *vc, पूर्णांक c, पूर्णांक ypos, पूर्णांक xpos)
अणु
	अचिन्हित लघु chr;

	scr_ग_लिखोw(c, &chr);
	fbcon_अ_दोs(vc, &chr, 1, ypos, xpos);
पूर्ण

अटल व्योम fbcon_clear_margins(काष्ठा vc_data *vc, पूर्णांक bottom_only)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	अगर (!fbcon_is_inactive(vc, info))
		ops->clear_margins(vc, info, margin_color, bottom_only);
पूर्ण

अटल व्योम fbcon_cursor(काष्ठा vc_data *vc, पूर्णांक mode)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_ops *ops = info->fbcon_par;
 	पूर्णांक c = scr_पढ़ोw((u16 *) vc->vc_pos);

	ops->cur_blink_jअगरfies = msecs_to_jअगरfies(vc->vc_cur_blink_ms);

	अगर (fbcon_is_inactive(vc, info) || vc->vc_deccm != 1)
		वापस;

	अगर (vc->vc_cursor_type & CUR_SW)
		fbcon_del_cursor_समयr(info);
	अन्यथा
		fbcon_add_cursor_समयr(info);

	ops->cursor_flash = (mode == CM_ERASE) ? 0 : 1;

	अगर (!ops->cursor)
		वापस;

	ops->cursor(vc, info, mode, get_color(vc, info, c, 1),
		    get_color(vc, info, c, 0));
पूर्ण

अटल पूर्णांक scrollback_phys_max = 0;
अटल पूर्णांक scrollback_max = 0;
अटल पूर्णांक scrollback_current = 0;

अटल व्योम fbcon_set_disp(काष्ठा fb_info *info, काष्ठा fb_var_screeninfo *var,
			   पूर्णांक unit)
अणु
	काष्ठा fbcon_display *p, *t;
	काष्ठा vc_data **शेष_mode, *vc;
	काष्ठा vc_data *svc;
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	पूर्णांक rows, cols;

	p = &fb_display[unit];

	अगर (var_to_display(p, var, info))
		वापस;

	vc = vc_cons[unit].d;

	अगर (!vc)
		वापस;

	शेष_mode = vc->vc_display_fg;
	svc = *शेष_mode;
	t = &fb_display[svc->vc_num];

	अगर (!vc->vc_font.data) अणु
		vc->vc_font.data = (व्योम *)(p->fontdata = t->fontdata);
		vc->vc_font.width = (*शेष_mode)->vc_font.width;
		vc->vc_font.height = (*शेष_mode)->vc_font.height;
		vc->vc_font.अक्षरcount = (*शेष_mode)->vc_font.अक्षरcount;
		p->userfont = t->userfont;
		अगर (p->userfont)
			REFCOUNT(p->fontdata)++;
	पूर्ण

	var->activate = FB_ACTIVATE_NOW;
	info->var.activate = var->activate;
	var->yoffset = info->var.yoffset;
	var->xoffset = info->var.xoffset;
	fb_set_var(info, var);
	ops->var = info->var;
	vc->vc_can_करो_color = (fb_get_color_depth(&info->var, &info->fix)!=1);
	vc->vc_complement_mask = vc->vc_can_करो_color ? 0x7700 : 0x0800;
	अगर (vc->vc_font.अक्षरcount == 256) अणु
		vc->vc_hi_font_mask = 0;
	पूर्ण अन्यथा अणु
		vc->vc_hi_font_mask = 0x100;
		अगर (vc->vc_can_करो_color)
			vc->vc_complement_mask <<= 1;
	पूर्ण

	अगर (!*svc->vc_uni_pagedir_loc)
		con_set_शेष_unimap(svc);
	अगर (!*vc->vc_uni_pagedir_loc)
		con_copy_unimap(vc, svc);

	cols = FBCON_SWAP(ops->rotate, info->var.xres, info->var.yres);
	rows = FBCON_SWAP(ops->rotate, info->var.yres, info->var.xres);
	cols /= vc->vc_font.width;
	rows /= vc->vc_font.height;
	vc_resize(vc, cols, rows);

	अगर (con_is_visible(vc)) अणु
		update_screen(vc);
	पूर्ण
पूर्ण

अटल __अंतरभूत__ व्योम ywrap_up(काष्ठा vc_data *vc, पूर्णांक count)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];
	
	p->yscroll += count;
	अगर (p->yscroll >= p->vrows)	/* Deal with wrap */
		p->yscroll -= p->vrows;
	ops->var.xoffset = 0;
	ops->var.yoffset = p->yscroll * vc->vc_font.height;
	ops->var.vmode |= FB_VMODE_YWRAP;
	ops->update_start(info);
	scrollback_max += count;
	अगर (scrollback_max > scrollback_phys_max)
		scrollback_max = scrollback_phys_max;
	scrollback_current = 0;
पूर्ण

अटल __अंतरभूत__ व्योम ywrap_करोwn(काष्ठा vc_data *vc, पूर्णांक count)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];
	
	p->yscroll -= count;
	अगर (p->yscroll < 0)	/* Deal with wrap */
		p->yscroll += p->vrows;
	ops->var.xoffset = 0;
	ops->var.yoffset = p->yscroll * vc->vc_font.height;
	ops->var.vmode |= FB_VMODE_YWRAP;
	ops->update_start(info);
	scrollback_max -= count;
	अगर (scrollback_max < 0)
		scrollback_max = 0;
	scrollback_current = 0;
पूर्ण

अटल __अंतरभूत__ व्योम ypan_up(काष्ठा vc_data *vc, पूर्णांक count)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	p->yscroll += count;
	अगर (p->yscroll > p->vrows - vc->vc_rows) अणु
		ops->bmove(vc, info, p->vrows - vc->vc_rows,
			    0, 0, 0, vc->vc_rows, vc->vc_cols);
		p->yscroll -= p->vrows - vc->vc_rows;
	पूर्ण

	ops->var.xoffset = 0;
	ops->var.yoffset = p->yscroll * vc->vc_font.height;
	ops->var.vmode &= ~FB_VMODE_YWRAP;
	ops->update_start(info);
	fbcon_clear_margins(vc, 1);
	scrollback_max += count;
	अगर (scrollback_max > scrollback_phys_max)
		scrollback_max = scrollback_phys_max;
	scrollback_current = 0;
पूर्ण

अटल __अंतरभूत__ व्योम ypan_up_redraw(काष्ठा vc_data *vc, पूर्णांक t, पूर्णांक count)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];

	p->yscroll += count;

	अगर (p->yscroll > p->vrows - vc->vc_rows) अणु
		p->yscroll -= p->vrows - vc->vc_rows;
		fbcon_redraw_move(vc, p, t + count, vc->vc_rows - count, t);
	पूर्ण

	ops->var.xoffset = 0;
	ops->var.yoffset = p->yscroll * vc->vc_font.height;
	ops->var.vmode &= ~FB_VMODE_YWRAP;
	ops->update_start(info);
	fbcon_clear_margins(vc, 1);
	scrollback_max += count;
	अगर (scrollback_max > scrollback_phys_max)
		scrollback_max = scrollback_phys_max;
	scrollback_current = 0;
पूर्ण

अटल __अंतरभूत__ व्योम ypan_करोwn(काष्ठा vc_data *vc, पूर्णांक count)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	
	p->yscroll -= count;
	अगर (p->yscroll < 0) अणु
		ops->bmove(vc, info, 0, 0, p->vrows - vc->vc_rows,
			    0, vc->vc_rows, vc->vc_cols);
		p->yscroll += p->vrows - vc->vc_rows;
	पूर्ण

	ops->var.xoffset = 0;
	ops->var.yoffset = p->yscroll * vc->vc_font.height;
	ops->var.vmode &= ~FB_VMODE_YWRAP;
	ops->update_start(info);
	fbcon_clear_margins(vc, 1);
	scrollback_max -= count;
	अगर (scrollback_max < 0)
		scrollback_max = 0;
	scrollback_current = 0;
पूर्ण

अटल __अंतरभूत__ व्योम ypan_करोwn_redraw(काष्ठा vc_data *vc, पूर्णांक t, पूर्णांक count)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];

	p->yscroll -= count;

	अगर (p->yscroll < 0) अणु
		p->yscroll += p->vrows - vc->vc_rows;
		fbcon_redraw_move(vc, p, t, vc->vc_rows - count, t + count);
	पूर्ण

	ops->var.xoffset = 0;
	ops->var.yoffset = p->yscroll * vc->vc_font.height;
	ops->var.vmode &= ~FB_VMODE_YWRAP;
	ops->update_start(info);
	fbcon_clear_margins(vc, 1);
	scrollback_max -= count;
	अगर (scrollback_max < 0)
		scrollback_max = 0;
	scrollback_current = 0;
पूर्ण

अटल व्योम fbcon_redraw_move(काष्ठा vc_data *vc, काष्ठा fbcon_display *p,
			      पूर्णांक line, पूर्णांक count, पूर्णांक dy)
अणु
	अचिन्हित लघु *s = (अचिन्हित लघु *)
		(vc->vc_origin + vc->vc_size_row * line);

	जबतक (count--) अणु
		अचिन्हित लघु *start = s;
		अचिन्हित लघु *le = advance_row(s, 1);
		अचिन्हित लघु c;
		पूर्णांक x = 0;
		अचिन्हित लघु attr = 1;

		करो अणु
			c = scr_पढ़ोw(s);
			अगर (attr != (c & 0xff00)) अणु
				attr = c & 0xff00;
				अगर (s > start) अणु
					fbcon_अ_दोs(vc, start, s - start,
						    dy, x);
					x += s - start;
					start = s;
				पूर्ण
			पूर्ण
			console_conditional_schedule();
			s++;
		पूर्ण जबतक (s < le);
		अगर (s > start)
			fbcon_अ_दोs(vc, start, s - start, dy, x);
		console_conditional_schedule();
		dy++;
	पूर्ण
पूर्ण

अटल व्योम fbcon_redraw_blit(काष्ठा vc_data *vc, काष्ठा fb_info *info,
			काष्ठा fbcon_display *p, पूर्णांक line, पूर्णांक count, पूर्णांक ycount)
अणु
	पूर्णांक offset = ycount * vc->vc_cols;
	अचिन्हित लघु *d = (अचिन्हित लघु *)
	    (vc->vc_origin + vc->vc_size_row * line);
	अचिन्हित लघु *s = d + offset;
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	जबतक (count--) अणु
		अचिन्हित लघु *start = s;
		अचिन्हित लघु *le = advance_row(s, 1);
		अचिन्हित लघु c;
		पूर्णांक x = 0;

		करो अणु
			c = scr_पढ़ोw(s);

			अगर (c == scr_पढ़ोw(d)) अणु
				अगर (s > start) अणु
					ops->bmove(vc, info, line + ycount, x,
						   line, x, 1, s-start);
					x += s - start + 1;
					start = s + 1;
				पूर्ण अन्यथा अणु
					x++;
					start++;
				पूर्ण
			पूर्ण

			scr_ग_लिखोw(c, d);
			console_conditional_schedule();
			s++;
			d++;
		पूर्ण जबतक (s < le);
		अगर (s > start)
			ops->bmove(vc, info, line + ycount, x, line, x, 1,
				   s-start);
		console_conditional_schedule();
		अगर (ycount > 0)
			line++;
		अन्यथा अणु
			line--;
			/* NOTE: We subtract two lines from these poपूर्णांकers */
			s -= vc->vc_size_row;
			d -= vc->vc_size_row;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fbcon_redraw(काष्ठा vc_data *vc, काष्ठा fbcon_display *p,
			 पूर्णांक line, पूर्णांक count, पूर्णांक offset)
अणु
	अचिन्हित लघु *d = (अचिन्हित लघु *)
	    (vc->vc_origin + vc->vc_size_row * line);
	अचिन्हित लघु *s = d + offset;

	जबतक (count--) अणु
		अचिन्हित लघु *start = s;
		अचिन्हित लघु *le = advance_row(s, 1);
		अचिन्हित लघु c;
		पूर्णांक x = 0;
		अचिन्हित लघु attr = 1;

		करो अणु
			c = scr_पढ़ोw(s);
			अगर (attr != (c & 0xff00)) अणु
				attr = c & 0xff00;
				अगर (s > start) अणु
					fbcon_अ_दोs(vc, start, s - start,
						    line, x);
					x += s - start;
					start = s;
				पूर्ण
			पूर्ण
			अगर (c == scr_पढ़ोw(d)) अणु
				अगर (s > start) अणु
					fbcon_अ_दोs(vc, start, s - start,
						     line, x);
					x += s - start + 1;
					start = s + 1;
				पूर्ण अन्यथा अणु
					x++;
					start++;
				पूर्ण
			पूर्ण
			scr_ग_लिखोw(c, d);
			console_conditional_schedule();
			s++;
			d++;
		पूर्ण जबतक (s < le);
		अगर (s > start)
			fbcon_अ_दोs(vc, start, s - start, line, x);
		console_conditional_schedule();
		अगर (offset > 0)
			line++;
		अन्यथा अणु
			line--;
			/* NOTE: We subtract two lines from these poपूर्णांकers */
			s -= vc->vc_size_row;
			d -= vc->vc_size_row;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool fbcon_scroll(काष्ठा vc_data *vc, अचिन्हित पूर्णांक t, अचिन्हित पूर्णांक b,
		क्रमागत con_scroll dir, अचिन्हित पूर्णांक count)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];
	पूर्णांक scroll_partial = info->flags & FBINFO_PARTIAL_PAN_OK;

	अगर (fbcon_is_inactive(vc, info))
		वापस true;

	fbcon_cursor(vc, CM_ERASE);

	/*
	 * ++Geert: Only use ywrap/ypan अगर the console is in text mode
	 * ++Andrew: Only use ypan on hardware text mode when scrolling the
	 *           whole screen (prevents flicker).
	 */

	चयन (dir) अणु
	हाल SM_UP:
		अगर (count > vc->vc_rows)	/* Maximum realistic size */
			count = vc->vc_rows;
		अगर (logo_shown >= 0)
			जाओ redraw_up;
		चयन (p->scrollmode) अणु
		हाल SCROLL_MOVE:
			fbcon_redraw_blit(vc, info, p, t, b - t - count,
				     count);
			fbcon_clear(vc, b - count, 0, count, vc->vc_cols);
			scr_स_रखोw((अचिन्हित लघु *) (vc->vc_origin +
							vc->vc_size_row *
							(b - count)),
				    vc->vc_video_erase_अक्षर,
				    vc->vc_size_row * count);
			वापस true;

		हाल SCROLL_WRAP_MOVE:
			अगर (b - t - count > 3 * vc->vc_rows >> 2) अणु
				अगर (t > 0)
					fbcon_bmove(vc, 0, 0, count, 0, t,
						    vc->vc_cols);
				ywrap_up(vc, count);
				अगर (vc->vc_rows - b > 0)
					fbcon_bmove(vc, b - count, 0, b, 0,
						    vc->vc_rows - b,
						    vc->vc_cols);
			पूर्ण अन्यथा अगर (info->flags & FBINFO_READS_FAST)
				fbcon_bmove(vc, t + count, 0, t, 0,
					    b - t - count, vc->vc_cols);
			अन्यथा
				जाओ redraw_up;
			fbcon_clear(vc, b - count, 0, count, vc->vc_cols);
			अवरोध;

		हाल SCROLL_PAN_REDRAW:
			अगर ((p->yscroll + count <=
			     2 * (p->vrows - vc->vc_rows))
			    && ((!scroll_partial && (b - t == vc->vc_rows))
				|| (scroll_partial
				    && (b - t - count >
					3 * vc->vc_rows >> 2)))) अणु
				अगर (t > 0)
					fbcon_redraw_move(vc, p, 0, t, count);
				ypan_up_redraw(vc, t, count);
				अगर (vc->vc_rows - b > 0)
					fbcon_redraw_move(vc, p, b,
							  vc->vc_rows - b, b);
			पूर्ण अन्यथा
				fbcon_redraw_move(vc, p, t + count, b - t - count, t);
			fbcon_clear(vc, b - count, 0, count, vc->vc_cols);
			अवरोध;

		हाल SCROLL_PAN_MOVE:
			अगर ((p->yscroll + count <=
			     2 * (p->vrows - vc->vc_rows))
			    && ((!scroll_partial && (b - t == vc->vc_rows))
				|| (scroll_partial
				    && (b - t - count >
					3 * vc->vc_rows >> 2)))) अणु
				अगर (t > 0)
					fbcon_bmove(vc, 0, 0, count, 0, t,
						    vc->vc_cols);
				ypan_up(vc, count);
				अगर (vc->vc_rows - b > 0)
					fbcon_bmove(vc, b - count, 0, b, 0,
						    vc->vc_rows - b,
						    vc->vc_cols);
			पूर्ण अन्यथा अगर (info->flags & FBINFO_READS_FAST)
				fbcon_bmove(vc, t + count, 0, t, 0,
					    b - t - count, vc->vc_cols);
			अन्यथा
				जाओ redraw_up;
			fbcon_clear(vc, b - count, 0, count, vc->vc_cols);
			अवरोध;

		हाल SCROLL_REDRAW:
		      redraw_up:
			fbcon_redraw(vc, p, t, b - t - count,
				     count * vc->vc_cols);
			fbcon_clear(vc, b - count, 0, count, vc->vc_cols);
			scr_स_रखोw((अचिन्हित लघु *) (vc->vc_origin +
							vc->vc_size_row *
							(b - count)),
				    vc->vc_video_erase_अक्षर,
				    vc->vc_size_row * count);
			वापस true;
		पूर्ण
		अवरोध;

	हाल SM_DOWN:
		अगर (count > vc->vc_rows)	/* Maximum realistic size */
			count = vc->vc_rows;
		अगर (logo_shown >= 0)
			जाओ redraw_करोwn;
		चयन (p->scrollmode) अणु
		हाल SCROLL_MOVE:
			fbcon_redraw_blit(vc, info, p, b - 1, b - t - count,
				     -count);
			fbcon_clear(vc, t, 0, count, vc->vc_cols);
			scr_स_रखोw((अचिन्हित लघु *) (vc->vc_origin +
							vc->vc_size_row *
							t),
				    vc->vc_video_erase_अक्षर,
				    vc->vc_size_row * count);
			वापस true;

		हाल SCROLL_WRAP_MOVE:
			अगर (b - t - count > 3 * vc->vc_rows >> 2) अणु
				अगर (vc->vc_rows - b > 0)
					fbcon_bmove(vc, b, 0, b - count, 0,
						    vc->vc_rows - b,
						    vc->vc_cols);
				ywrap_करोwn(vc, count);
				अगर (t > 0)
					fbcon_bmove(vc, count, 0, 0, 0, t,
						    vc->vc_cols);
			पूर्ण अन्यथा अगर (info->flags & FBINFO_READS_FAST)
				fbcon_bmove(vc, t, 0, t + count, 0,
					    b - t - count, vc->vc_cols);
			अन्यथा
				जाओ redraw_करोwn;
			fbcon_clear(vc, t, 0, count, vc->vc_cols);
			अवरोध;

		हाल SCROLL_PAN_MOVE:
			अगर ((count - p->yscroll <= p->vrows - vc->vc_rows)
			    && ((!scroll_partial && (b - t == vc->vc_rows))
				|| (scroll_partial
				    && (b - t - count >
					3 * vc->vc_rows >> 2)))) अणु
				अगर (vc->vc_rows - b > 0)
					fbcon_bmove(vc, b, 0, b - count, 0,
						    vc->vc_rows - b,
						    vc->vc_cols);
				ypan_करोwn(vc, count);
				अगर (t > 0)
					fbcon_bmove(vc, count, 0, 0, 0, t,
						    vc->vc_cols);
			पूर्ण अन्यथा अगर (info->flags & FBINFO_READS_FAST)
				fbcon_bmove(vc, t, 0, t + count, 0,
					    b - t - count, vc->vc_cols);
			अन्यथा
				जाओ redraw_करोwn;
			fbcon_clear(vc, t, 0, count, vc->vc_cols);
			अवरोध;

		हाल SCROLL_PAN_REDRAW:
			अगर ((count - p->yscroll <= p->vrows - vc->vc_rows)
			    && ((!scroll_partial && (b - t == vc->vc_rows))
				|| (scroll_partial
				    && (b - t - count >
					3 * vc->vc_rows >> 2)))) अणु
				अगर (vc->vc_rows - b > 0)
					fbcon_redraw_move(vc, p, b, vc->vc_rows - b,
							  b - count);
				ypan_करोwn_redraw(vc, t, count);
				अगर (t > 0)
					fbcon_redraw_move(vc, p, count, t, 0);
			पूर्ण अन्यथा
				fbcon_redraw_move(vc, p, t, b - t - count, t + count);
			fbcon_clear(vc, t, 0, count, vc->vc_cols);
			अवरोध;

		हाल SCROLL_REDRAW:
		      redraw_करोwn:
			fbcon_redraw(vc, p, b - 1, b - t - count,
				     -count * vc->vc_cols);
			fbcon_clear(vc, t, 0, count, vc->vc_cols);
			scr_स_रखोw((अचिन्हित लघु *) (vc->vc_origin +
							vc->vc_size_row *
							t),
				    vc->vc_video_erase_अक्षर,
				    vc->vc_size_row * count);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण


अटल व्योम fbcon_bmove(काष्ठा vc_data *vc, पूर्णांक sy, पूर्णांक sx, पूर्णांक dy, पूर्णांक dx,
			पूर्णांक height, पूर्णांक width)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];
	
	अगर (fbcon_is_inactive(vc, info))
		वापस;

	अगर (!width || !height)
		वापस;

	/*  Split blits that cross physical y_wrap हाल.
	 *  Pathological हाल involves 4 blits, better to use recursive
	 *  code rather than unrolled हाल
	 *
	 *  Recursive invocations करोn't need to erase the cursor over and
	 *  over again, so we use fbcon_bmove_rec()
	 */
	fbcon_bmove_rec(vc, p, sy, sx, dy, dx, height, width,
			p->vrows - p->yscroll);
पूर्ण

अटल व्योम fbcon_bmove_rec(काष्ठा vc_data *vc, काष्ठा fbcon_display *p, पूर्णांक sy, पूर्णांक sx,
			    पूर्णांक dy, पूर्णांक dx, पूर्णांक height, पूर्णांक width, u_पूर्णांक y_अवरोध)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	u_पूर्णांक b;

	अगर (sy < y_अवरोध && sy + height > y_अवरोध) अणु
		b = y_अवरोध - sy;
		अगर (dy < sy) अणु	/* Aव्योम trashing self */
			fbcon_bmove_rec(vc, p, sy, sx, dy, dx, b, width,
					y_अवरोध);
			fbcon_bmove_rec(vc, p, sy + b, sx, dy + b, dx,
					height - b, width, y_अवरोध);
		पूर्ण अन्यथा अणु
			fbcon_bmove_rec(vc, p, sy + b, sx, dy + b, dx,
					height - b, width, y_अवरोध);
			fbcon_bmove_rec(vc, p, sy, sx, dy, dx, b, width,
					y_अवरोध);
		पूर्ण
		वापस;
	पूर्ण

	अगर (dy < y_अवरोध && dy + height > y_अवरोध) अणु
		b = y_अवरोध - dy;
		अगर (dy < sy) अणु	/* Aव्योम trashing self */
			fbcon_bmove_rec(vc, p, sy, sx, dy, dx, b, width,
					y_अवरोध);
			fbcon_bmove_rec(vc, p, sy + b, sx, dy + b, dx,
					height - b, width, y_अवरोध);
		पूर्ण अन्यथा अणु
			fbcon_bmove_rec(vc, p, sy + b, sx, dy + b, dx,
					height - b, width, y_अवरोध);
			fbcon_bmove_rec(vc, p, sy, sx, dy, dx, b, width,
					y_अवरोध);
		पूर्ण
		वापस;
	पूर्ण
	ops->bmove(vc, info, real_y(p, sy), sx, real_y(p, dy), dx,
		   height, width);
पूर्ण

अटल व्योम updatescrollmode(काष्ठा fbcon_display *p,
					काष्ठा fb_info *info,
					काष्ठा vc_data *vc)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	पूर्णांक fh = vc->vc_font.height;
	पूर्णांक yres = FBCON_SWAP(ops->rotate, info->var.yres, info->var.xres);
	पूर्णांक vyres = FBCON_SWAP(ops->rotate, info->var.yres_भव,
				   info->var.xres_भव);

	p->vrows = vyres/fh;
	अगर (yres > (fh * (vc->vc_rows + 1)))
		p->vrows -= (yres - (fh * vc->vc_rows)) / fh;
	अगर ((yres % fh) && (vyres % fh < yres % fh))
		p->vrows--;
पूर्ण

#घोषणा PITCH(w) (((w) + 7) >> 3)
#घोषणा CALC_FONTSZ(h, p, c) ((h) * (p) * (c)) /* size = height * pitch * अक्षरcount */

अटल पूर्णांक fbcon_resize(काष्ठा vc_data *vc, अचिन्हित पूर्णांक width, 
			अचिन्हित पूर्णांक height, अचिन्हित पूर्णांक user)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];
	काष्ठा fb_var_screeninfo var = info->var;
	पूर्णांक x_dअगरf, y_dअगरf, virt_w, virt_h, virt_fw, virt_fh;

	अगर (p->userfont && FNTSIZE(vc->vc_font.data)) अणु
		पूर्णांक size;
		पूर्णांक pitch = PITCH(vc->vc_font.width);

		/*
		 * If user font, ensure that a possible change to user font
		 * height or width will not allow a font data out-of-bounds access.
		 * NOTE: must use original अक्षरcount in calculation as font
		 * अक्षरcount can change and cannot be used to determine the
		 * font data allocated size.
		 */
		अगर (pitch <= 0)
			वापस -EINVAL;
		size = CALC_FONTSZ(vc->vc_font.height, pitch, vc->vc_font.अक्षरcount);
		अगर (size > FNTSIZE(vc->vc_font.data))
			वापस -EINVAL;
	पूर्ण

	virt_w = FBCON_SWAP(ops->rotate, width, height);
	virt_h = FBCON_SWAP(ops->rotate, height, width);
	virt_fw = FBCON_SWAP(ops->rotate, vc->vc_font.width,
				 vc->vc_font.height);
	virt_fh = FBCON_SWAP(ops->rotate, vc->vc_font.height,
				 vc->vc_font.width);
	var.xres = virt_w * virt_fw;
	var.yres = virt_h * virt_fh;
	x_dअगरf = info->var.xres - var.xres;
	y_dअगरf = info->var.yres - var.yres;
	अगर (x_dअगरf < 0 || x_dअगरf > virt_fw ||
	    y_dअगरf < 0 || y_dअगरf > virt_fh) अणु
		स्थिर काष्ठा fb_videomode *mode;

		pr_debug("attempting resize %ix%i\n", var.xres, var.yres);
		mode = fb_find_best_mode(&var, &info->modelist);
		अगर (mode == शून्य)
			वापस -EINVAL;
		display_to_var(&var, p);
		fb_videomode_to_var(&var, mode);

		अगर (virt_w > var.xres/virt_fw || virt_h > var.yres/virt_fh)
			वापस -EINVAL;

		pr_debug("resize now %ix%i\n", var.xres, var.yres);
		अगर (con_is_visible(vc) && vc->vc_mode == KD_TEXT) अणु
			var.activate = FB_ACTIVATE_NOW |
				FB_ACTIVATE_FORCE;
			fb_set_var(info, &var);
		पूर्ण
		var_to_display(p, &info->var, info);
		ops->var = info->var;
	पूर्ण
	updatescrollmode(p, info, vc);
	वापस 0;
पूर्ण

अटल पूर्णांक fbcon_चयन(काष्ठा vc_data *vc)
अणु
	काष्ठा fb_info *info, *old_info = शून्य;
	काष्ठा fbcon_ops *ops;
	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];
	काष्ठा fb_var_screeninfo var;
	पूर्णांक i, ret, prev_console;

	info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	ops = info->fbcon_par;

	अगर (logo_shown >= 0) अणु
		काष्ठा vc_data *conp2 = vc_cons[logo_shown].d;

		अगर (conp2->vc_top == logo_lines
		    && conp2->vc_bottom == conp2->vc_rows)
			conp2->vc_top = 0;
		logo_shown = FBCON_LOGO_CANSHOW;
	पूर्ण

	prev_console = ops->currcon;
	अगर (prev_console != -1)
		old_info = रेजिस्टरed_fb[con2fb_map[prev_console]];
	/*
	 * FIXME: If we have multiple fbdev's loaded, we need to
	 * update all info->currcon.  Perhaps, we can place this
	 * in a centralized काष्ठाure, but this might अवरोध some
	 * drivers.
	 *
	 * info->currcon = vc->vc_num;
	 */
	क्रम_each_रेजिस्टरed_fb(i) अणु
		अगर (रेजिस्टरed_fb[i]->fbcon_par) अणु
			काष्ठा fbcon_ops *o = रेजिस्टरed_fb[i]->fbcon_par;

			o->currcon = vc->vc_num;
		पूर्ण
	पूर्ण
	स_रखो(&var, 0, माप(काष्ठा fb_var_screeninfo));
	display_to_var(&var, p);
	var.activate = FB_ACTIVATE_NOW;

	/*
	 * make sure we करोn't unnecessarily trip the स_भेद()
	 * in fb_set_var()
	 */
	info->var.activate = var.activate;
	var.vmode |= info->var.vmode & ~FB_VMODE_MASK;
	fb_set_var(info, &var);
	ops->var = info->var;

	अगर (old_info != शून्य && (old_info != info ||
				 info->flags & FBINFO_MISC_ALWAYS_SETPAR)) अणु
		अगर (info->fbops->fb_set_par) अणु
			ret = info->fbops->fb_set_par(info);

			अगर (ret)
				prपूर्णांकk(KERN_ERR "fbcon_switch: detected "
					"unhandled fb_set_par error, "
					"error code %d\n", ret);
		पूर्ण

		अगर (old_info != info)
			fbcon_del_cursor_समयr(old_info);
	पूर्ण

	अगर (fbcon_is_inactive(vc, info) ||
	    ops->blank_state != FB_BLANK_UNBLANK)
		fbcon_del_cursor_समयr(info);
	अन्यथा
		fbcon_add_cursor_समयr(info);

	set_blitting_type(vc, info);
	ops->cursor_reset = 1;

	अगर (ops->rotate_font && ops->rotate_font(info, vc)) अणु
		ops->rotate = FB_ROTATE_UR;
		set_blitting_type(vc, info);
	पूर्ण

	vc->vc_can_करो_color = (fb_get_color_depth(&info->var, &info->fix)!=1);
	vc->vc_complement_mask = vc->vc_can_करो_color ? 0x7700 : 0x0800;

	अगर (vc->vc_font.अक्षरcount > 256)
		vc->vc_complement_mask <<= 1;

	updatescrollmode(p, info, vc);

	चयन (p->scrollmode) अणु
	हाल SCROLL_WRAP_MOVE:
		scrollback_phys_max = p->vrows - vc->vc_rows;
		अवरोध;
	हाल SCROLL_PAN_MOVE:
	हाल SCROLL_PAN_REDRAW:
		scrollback_phys_max = p->vrows - 2 * vc->vc_rows;
		अगर (scrollback_phys_max < 0)
			scrollback_phys_max = 0;
		अवरोध;
	शेष:
		scrollback_phys_max = 0;
		अवरोध;
	पूर्ण

	scrollback_max = 0;
	scrollback_current = 0;

	अगर (!fbcon_is_inactive(vc, info)) अणु
	    ops->var.xoffset = ops->var.yoffset = p->yscroll = 0;
	    ops->update_start(info);
	पूर्ण

	fbcon_set_palette(vc, color_table); 	
	fbcon_clear_margins(vc, 0);

	अगर (logo_shown == FBCON_LOGO_DRAW) अणु

		logo_shown = fg_console;
		/* This is रक्षित above by iniपंचांगem_मुक्तd */
		fb_show_logo(info, ops->rotate);
		update_region(vc,
			      vc->vc_origin + vc->vc_size_row * vc->vc_top,
			      vc->vc_size_row * (vc->vc_bottom -
						 vc->vc_top) / 2);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम fbcon_generic_blank(काष्ठा vc_data *vc, काष्ठा fb_info *info,
				पूर्णांक blank)
अणु
	अगर (blank) अणु
		अचिन्हित लघु अक्षरmask = vc->vc_hi_font_mask ?
			0x1ff : 0xff;
		अचिन्हित लघु oldc;

		oldc = vc->vc_video_erase_अक्षर;
		vc->vc_video_erase_अक्षर &= अक्षरmask;
		fbcon_clear(vc, 0, 0, vc->vc_rows, vc->vc_cols);
		vc->vc_video_erase_अक्षर = oldc;
	पूर्ण
पूर्ण

अटल पूर्णांक fbcon_blank(काष्ठा vc_data *vc, पूर्णांक blank, पूर्णांक mode_चयन)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	अगर (mode_चयन) अणु
		काष्ठा fb_var_screeninfo var = info->var;

		ops->graphics = 1;

		अगर (!blank) अणु
			var.activate = FB_ACTIVATE_NOW | FB_ACTIVATE_FORCE |
				FB_ACTIVATE_KD_TEXT;
			fb_set_var(info, &var);
			ops->graphics = 0;
			ops->var = info->var;
		पूर्ण
	पूर्ण

 	अगर (!fbcon_is_inactive(vc, info)) अणु
		अगर (ops->blank_state != blank) अणु
			ops->blank_state = blank;
			fbcon_cursor(vc, blank ? CM_ERASE : CM_DRAW);
			ops->cursor_flash = (!blank);

			अगर (fb_blank(info, blank))
				fbcon_generic_blank(vc, info, blank);
		पूर्ण

		अगर (!blank)
			update_screen(vc);
	पूर्ण

	अगर (mode_चयन || fbcon_is_inactive(vc, info) ||
	    ops->blank_state != FB_BLANK_UNBLANK)
		fbcon_del_cursor_समयr(info);
	अन्यथा
		fbcon_add_cursor_समयr(info);

	वापस 0;
पूर्ण

अटल पूर्णांक fbcon_debug_enter(काष्ठा vc_data *vc)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	ops->save_graphics = ops->graphics;
	ops->graphics = 0;
	अगर (info->fbops->fb_debug_enter)
		info->fbops->fb_debug_enter(info);
	fbcon_set_palette(vc, color_table);
	वापस 0;
पूर्ण

अटल पूर्णांक fbcon_debug_leave(काष्ठा vc_data *vc)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	ops->graphics = ops->save_graphics;
	अगर (info->fbops->fb_debug_leave)
		info->fbops->fb_debug_leave(info);
	वापस 0;
पूर्ण

अटल पूर्णांक fbcon_get_font(काष्ठा vc_data *vc, काष्ठा console_font *font)
अणु
	u8 *fontdata = vc->vc_font.data;
	u8 *data = font->data;
	पूर्णांक i, j;

	font->width = vc->vc_font.width;
	font->height = vc->vc_font.height;
	font->अक्षरcount = vc->vc_hi_font_mask ? 512 : 256;
	अगर (!font->data)
		वापस 0;

	अगर (font->width <= 8) अणु
		j = vc->vc_font.height;
		अगर (font->अक्षरcount * j > FNTSIZE(fontdata))
			वापस -EINVAL;

		क्रम (i = 0; i < font->अक्षरcount; i++) अणु
			स_नकल(data, fontdata, j);
			स_रखो(data + j, 0, 32 - j);
			data += 32;
			fontdata += j;
		पूर्ण
	पूर्ण अन्यथा अगर (font->width <= 16) अणु
		j = vc->vc_font.height * 2;
		अगर (font->अक्षरcount * j > FNTSIZE(fontdata))
			वापस -EINVAL;

		क्रम (i = 0; i < font->अक्षरcount; i++) अणु
			स_नकल(data, fontdata, j);
			स_रखो(data + j, 0, 64 - j);
			data += 64;
			fontdata += j;
		पूर्ण
	पूर्ण अन्यथा अगर (font->width <= 24) अणु
		अगर (font->अक्षरcount * (vc->vc_font.height * माप(u32)) > FNTSIZE(fontdata))
			वापस -EINVAL;

		क्रम (i = 0; i < font->अक्षरcount; i++) अणु
			क्रम (j = 0; j < vc->vc_font.height; j++) अणु
				*data++ = fontdata[0];
				*data++ = fontdata[1];
				*data++ = fontdata[2];
				fontdata += माप(u32);
			पूर्ण
			स_रखो(data, 0, 3 * (32 - j));
			data += 3 * (32 - j);
		पूर्ण
	पूर्ण अन्यथा अणु
		j = vc->vc_font.height * 4;
		अगर (font->अक्षरcount * j > FNTSIZE(fontdata))
			वापस -EINVAL;

		क्रम (i = 0; i < font->अक्षरcount; i++) अणु
			स_नकल(data, fontdata, j);
			स_रखो(data + j, 0, 128 - j);
			data += 128;
			fontdata += j;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* set/clear vc_hi_font_mask and update vc attrs accordingly */
अटल व्योम set_vc_hi_font(काष्ठा vc_data *vc, bool set)
अणु
	अगर (!set) अणु
		vc->vc_hi_font_mask = 0;
		अगर (vc->vc_can_करो_color) अणु
			vc->vc_complement_mask >>= 1;
			vc->vc_s_complement_mask >>= 1;
		पूर्ण
			
		/* ++Edmund: reorder the attribute bits */
		अगर (vc->vc_can_करो_color) अणु
			अचिन्हित लघु *cp =
			    (अचिन्हित लघु *) vc->vc_origin;
			पूर्णांक count = vc->vc_screenbuf_size / 2;
			अचिन्हित लघु c;
			क्रम (; count > 0; count--, cp++) अणु
				c = scr_पढ़ोw(cp);
				scr_ग_लिखोw(((c & 0xfe00) >> 1) |
					   (c & 0xff), cp);
			पूर्ण
			c = vc->vc_video_erase_अक्षर;
			vc->vc_video_erase_अक्षर =
			    ((c & 0xfe00) >> 1) | (c & 0xff);
			vc->vc_attr >>= 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		vc->vc_hi_font_mask = 0x100;
		अगर (vc->vc_can_करो_color) अणु
			vc->vc_complement_mask <<= 1;
			vc->vc_s_complement_mask <<= 1;
		पूर्ण
			
		/* ++Edmund: reorder the attribute bits */
		अणु
			अचिन्हित लघु *cp =
			    (अचिन्हित लघु *) vc->vc_origin;
			पूर्णांक count = vc->vc_screenbuf_size / 2;
			अचिन्हित लघु c;
			क्रम (; count > 0; count--, cp++) अणु
				अचिन्हित लघु newc;
				c = scr_पढ़ोw(cp);
				अगर (vc->vc_can_करो_color)
					newc =
					    ((c & 0xff00) << 1) | (c &
								   0xff);
				अन्यथा
					newc = c & ~0x100;
				scr_ग_लिखोw(newc, cp);
			पूर्ण
			c = vc->vc_video_erase_अक्षर;
			अगर (vc->vc_can_करो_color) अणु
				vc->vc_video_erase_अक्षर =
				    ((c & 0xff00) << 1) | (c & 0xff);
				vc->vc_attr <<= 1;
			पूर्ण अन्यथा
				vc->vc_video_erase_अक्षर = c & ~0x100;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक fbcon_करो_set_font(काष्ठा vc_data *vc, पूर्णांक w, पूर्णांक h, पूर्णांक अक्षरcount,
			     स्थिर u8 * data, पूर्णांक userfont)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	काष्ठा fbcon_display *p = &fb_display[vc->vc_num];
	पूर्णांक resize;
	अक्षर *old_data = शून्य;

	resize = (w != vc->vc_font.width) || (h != vc->vc_font.height);
	अगर (p->userfont)
		old_data = vc->vc_font.data;
	vc->vc_font.data = (व्योम *)(p->fontdata = data);
	अगर ((p->userfont = userfont))
		REFCOUNT(data)++;
	vc->vc_font.width = w;
	vc->vc_font.height = h;
	vc->vc_font.अक्षरcount = अक्षरcount;
	अगर (vc->vc_hi_font_mask && अक्षरcount == 256)
		set_vc_hi_font(vc, false);
	अन्यथा अगर (!vc->vc_hi_font_mask && अक्षरcount == 512)
		set_vc_hi_font(vc, true);

	अगर (resize) अणु
		पूर्णांक cols, rows;

		cols = FBCON_SWAP(ops->rotate, info->var.xres, info->var.yres);
		rows = FBCON_SWAP(ops->rotate, info->var.yres, info->var.xres);
		cols /= w;
		rows /= h;
		vc_resize(vc, cols, rows);
	पूर्ण अन्यथा अगर (con_is_visible(vc)
		   && vc->vc_mode == KD_TEXT) अणु
		fbcon_clear_margins(vc, 0);
		update_screen(vc);
	पूर्ण

	अगर (old_data && (--REFCOUNT(old_data) == 0))
		kमुक्त(old_data - FONT_EXTRA_WORDS * माप(पूर्णांक));
	वापस 0;
पूर्ण

/*
 *  User asked to set font; we are guaranteed that
 *	a) width and height are in range 1..32
 *	b) अक्षरcount करोes not exceed 512
 *  but lets not assume that, since someone might someday want to use larger
 *  fonts. And अक्षरcount of 512 is small क्रम unicode support.
 *
 *  However, user space gives the font in 32 rows , regardless of
 *  actual font height. So a new API is needed अगर support क्रम larger fonts
 *  is ever implemented.
 */

अटल पूर्णांक fbcon_set_font(काष्ठा vc_data *vc, काष्ठा console_font *font,
			  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	अचिन्हित अक्षरcount = font->अक्षरcount;
	पूर्णांक w = font->width;
	पूर्णांक h = font->height;
	पूर्णांक size;
	पूर्णांक i, csum;
	u8 *new_data, *data = font->data;
	पूर्णांक pitch = PITCH(font->width);

	/* Is there a reason why fbconsole couldn't handle any अक्षरcount >256?
	 * If not this check should be changed to अक्षरcount < 256 */
	अगर (अक्षरcount != 256 && अक्षरcount != 512)
		वापस -EINVAL;

	/* Make sure drawing engine can handle the font */
	अगर (!(info->pixmap.blit_x & (1 << (font->width - 1))) ||
	    !(info->pixmap.blit_y & (1 << (font->height - 1))))
		वापस -EINVAL;

	/* Make sure driver can handle the font length */
	अगर (fbcon_invalid_अक्षरcount(info, अक्षरcount))
		वापस -EINVAL;

	size = CALC_FONTSZ(h, pitch, अक्षरcount);

	new_data = kदो_स्मृति(FONT_EXTRA_WORDS * माप(पूर्णांक) + size, GFP_USER);

	अगर (!new_data)
		वापस -ENOMEM;

	स_रखो(new_data, 0, FONT_EXTRA_WORDS * माप(पूर्णांक));

	new_data += FONT_EXTRA_WORDS * माप(पूर्णांक);
	FNTSIZE(new_data) = size;
	REFCOUNT(new_data) = 0;	/* usage counter */
	क्रम (i=0; i< अक्षरcount; i++) अणु
		स_नकल(new_data + i*h*pitch, data +  i*32*pitch, h*pitch);
	पूर्ण

	/* Since linux has a nice crc32 function use it क्रम counting font
	 * checksums. */
	csum = crc32(0, new_data, size);

	FNTSUM(new_data) = csum;
	/* Check अगर the same font is on some other console alपढ़ोy */
	क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
		काष्ठा vc_data *पंचांगp = vc_cons[i].d;
		
		अगर (fb_display[i].userfont &&
		    fb_display[i].fontdata &&
		    FNTSUM(fb_display[i].fontdata) == csum &&
		    FNTSIZE(fb_display[i].fontdata) == size &&
		    पंचांगp->vc_font.width == w &&
		    !स_भेद(fb_display[i].fontdata, new_data, size)) अणु
			kमुक्त(new_data - FONT_EXTRA_WORDS * माप(पूर्णांक));
			new_data = (u8 *)fb_display[i].fontdata;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस fbcon_करो_set_font(vc, font->width, font->height, अक्षरcount, new_data, 1);
पूर्ण

अटल पूर्णांक fbcon_set_def_font(काष्ठा vc_data *vc, काष्ठा console_font *font, अक्षर *name)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	स्थिर काष्ठा font_desc *f;

	अगर (!name)
		f = get_शेष_font(info->var.xres, info->var.yres,
				     info->pixmap.blit_x, info->pixmap.blit_y);
	अन्यथा अगर (!(f = find_font(name)))
		वापस -ENOENT;

	font->width = f->width;
	font->height = f->height;
	वापस fbcon_करो_set_font(vc, f->width, f->height, f->अक्षरcount, f->data, 0);
पूर्ण

अटल u16 palette_red[16];
अटल u16 palette_green[16];
अटल u16 palette_blue[16];

अटल काष्ठा fb_cmap palette_cmap = अणु
	0, 16, palette_red, palette_green, palette_blue, शून्य
पूर्ण;

अटल व्योम fbcon_set_palette(काष्ठा vc_data *vc, स्थिर अचिन्हित अक्षर *table)
अणु
	काष्ठा fb_info *info = रेजिस्टरed_fb[con2fb_map[vc->vc_num]];
	पूर्णांक i, j, k, depth;
	u8 val;

	अगर (fbcon_is_inactive(vc, info))
		वापस;

	अगर (!con_is_visible(vc))
		वापस;

	depth = fb_get_color_depth(&info->var, &info->fix);
	अगर (depth > 3) अणु
		क्रम (i = j = 0; i < 16; i++) अणु
			k = table[i];
			val = vc->vc_palette[j++];
			palette_red[k] = (val << 8) | val;
			val = vc->vc_palette[j++];
			palette_green[k] = (val << 8) | val;
			val = vc->vc_palette[j++];
			palette_blue[k] = (val << 8) | val;
		पूर्ण
		palette_cmap.len = 16;
		palette_cmap.start = 0;
	/*
	 * If framebuffer is capable of less than 16 colors,
	 * use शेष palette of fbcon.
	 */
	पूर्ण अन्यथा
		fb_copy_cmap(fb_शेष_cmap(1 << depth), &palette_cmap);

	fb_set_cmap(&palette_cmap, info);
पूर्ण

अटल u16 *fbcon_screen_pos(स्थिर काष्ठा vc_data *vc, पूर्णांक offset)
अणु
	वापस (u16 *) (vc->vc_origin + offset);
पूर्ण

अटल अचिन्हित दीर्घ fbcon_getxy(काष्ठा vc_data *vc, अचिन्हित दीर्घ pos,
				 पूर्णांक *px, पूर्णांक *py)
अणु
	अचिन्हित दीर्घ ret;
	पूर्णांक x, y;

	अगर (pos >= vc->vc_origin && pos < vc->vc_scr_end) अणु
		अचिन्हित दीर्घ offset = (pos - vc->vc_origin) / 2;

		x = offset % vc->vc_cols;
		y = offset / vc->vc_cols;
		ret = pos + (vc->vc_cols - x) * 2;
	पूर्ण अन्यथा अणु
		/* Should not happen */
		x = y = 0;
		ret = vc->vc_origin;
	पूर्ण
	अगर (px)
		*px = x;
	अगर (py)
		*py = y;
	वापस ret;
पूर्ण

/* As we might be inside of softback, we may work with non-contiguous buffer,
   that's why we have to use a separate routine. */
अटल व्योम fbcon_invert_region(काष्ठा vc_data *vc, u16 * p, पूर्णांक cnt)
अणु
	जबतक (cnt--) अणु
		u16 a = scr_पढ़ोw(p);
		अगर (!vc->vc_can_करो_color)
			a ^= 0x0800;
		अन्यथा अगर (vc->vc_hi_font_mask == 0x100)
			a = ((a) & 0x11ff) | (((a) & 0xe000) >> 4) |
			    (((a) & 0x0e00) << 4);
		अन्यथा
			a = ((a) & 0x88ff) | (((a) & 0x7000) >> 4) |
			    (((a) & 0x0700) << 4);
		scr_ग_लिखोw(a, p++);
	पूर्ण
पूर्ण

व्योम fbcon_suspended(काष्ठा fb_info *info)
अणु
	काष्ठा vc_data *vc = शून्य;
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	अगर (!ops || ops->currcon < 0)
		वापस;
	vc = vc_cons[ops->currcon].d;

	/* Clear cursor, restore saved data */
	fbcon_cursor(vc, CM_ERASE);
पूर्ण

व्योम fbcon_resumed(काष्ठा fb_info *info)
अणु
	काष्ठा vc_data *vc;
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	अगर (!ops || ops->currcon < 0)
		वापस;
	vc = vc_cons[ops->currcon].d;

	update_screen(vc);
पूर्ण

अटल व्योम fbcon_modechanged(काष्ठा fb_info *info)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	काष्ठा vc_data *vc;
	काष्ठा fbcon_display *p;
	पूर्णांक rows, cols;

	अगर (!ops || ops->currcon < 0)
		वापस;
	vc = vc_cons[ops->currcon].d;
	अगर (vc->vc_mode != KD_TEXT ||
	    रेजिस्टरed_fb[con2fb_map[ops->currcon]] != info)
		वापस;

	p = &fb_display[vc->vc_num];
	set_blitting_type(vc, info);

	अगर (con_is_visible(vc)) अणु
		var_to_display(p, &info->var, info);
		cols = FBCON_SWAP(ops->rotate, info->var.xres, info->var.yres);
		rows = FBCON_SWAP(ops->rotate, info->var.yres, info->var.xres);
		cols /= vc->vc_font.width;
		rows /= vc->vc_font.height;
		vc_resize(vc, cols, rows);
		updatescrollmode(p, info, vc);
		scrollback_max = 0;
		scrollback_current = 0;

		अगर (!fbcon_is_inactive(vc, info)) अणु
		    ops->var.xoffset = ops->var.yoffset = p->yscroll = 0;
		    ops->update_start(info);
		पूर्ण

		fbcon_set_palette(vc, color_table);
		update_screen(vc);
	पूर्ण
पूर्ण

अटल व्योम fbcon_set_all_vcs(काष्ठा fb_info *info)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	काष्ठा vc_data *vc;
	काष्ठा fbcon_display *p;
	पूर्णांक i, rows, cols, fg = -1;

	अगर (!ops || ops->currcon < 0)
		वापस;

	क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
		vc = vc_cons[i].d;
		अगर (!vc || vc->vc_mode != KD_TEXT ||
		    रेजिस्टरed_fb[con2fb_map[i]] != info)
			जारी;

		अगर (con_is_visible(vc)) अणु
			fg = i;
			जारी;
		पूर्ण

		p = &fb_display[vc->vc_num];
		set_blitting_type(vc, info);
		var_to_display(p, &info->var, info);
		cols = FBCON_SWAP(ops->rotate, info->var.xres, info->var.yres);
		rows = FBCON_SWAP(ops->rotate, info->var.yres, info->var.xres);
		cols /= vc->vc_font.width;
		rows /= vc->vc_font.height;
		vc_resize(vc, cols, rows);
	पूर्ण

	अगर (fg != -1)
		fbcon_modechanged(info);
पूर्ण


व्योम fbcon_update_vcs(काष्ठा fb_info *info, bool all)
अणु
	अगर (all)
		fbcon_set_all_vcs(info);
	अन्यथा
		fbcon_modechanged(info);
पूर्ण
EXPORT_SYMBOL(fbcon_update_vcs);

पूर्णांक fbcon_mode_deleted(काष्ठा fb_info *info,
		       काष्ठा fb_videomode *mode)
अणु
	काष्ठा fb_info *fb_info;
	काष्ठा fbcon_display *p;
	पूर्णांक i, j, found = 0;

	/* beक्रमe deletion, ensure that mode is not in use */
	क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
		j = con2fb_map[i];
		अगर (j == -1)
			जारी;
		fb_info = रेजिस्टरed_fb[j];
		अगर (fb_info != info)
			जारी;
		p = &fb_display[i];
		अगर (!p || !p->mode)
			जारी;
		अगर (fb_mode_is_equal(p->mode, mode)) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस found;
पूर्ण

#अगर_घोषित CONFIG_VT_HW_CONSOLE_BINDING
अटल व्योम fbcon_unbind(व्योम)
अणु
	पूर्णांक ret;

	ret = करो_unbind_con_driver(&fb_con, first_fb_vc, last_fb_vc,
				fbcon_is_शेष);

	अगर (!ret)
		fbcon_has_console_bind = 0;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम fbcon_unbind(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_VT_HW_CONSOLE_BINDING */

/* called with console_lock held */
व्योम fbcon_fb_unbind(काष्ठा fb_info *info)
अणु
	पूर्णांक i, new_idx = -1, ret = 0;
	पूर्णांक idx = info->node;

	WARN_CONSOLE_UNLOCKED();

	अगर (!fbcon_has_console_bind)
		वापस;

	क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
		अगर (con2fb_map[i] != idx &&
		    con2fb_map[i] != -1) अणु
			new_idx = con2fb_map[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (new_idx != -1) अणु
		क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
			अगर (con2fb_map[i] == idx)
				set_con2fb_map(i, new_idx, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा fb_info *info = रेजिस्टरed_fb[idx];

		/* This is sort of like set_con2fb_map, except it maps
		 * the consoles to no device and then releases the
		 * oldinfo to मुक्त memory and cancel the cursor blink
		 * समयr. I can imagine this just becoming part of
		 * set_con2fb_map where new_idx is -1
		 */
		क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
			अगर (con2fb_map[i] == idx) अणु
				con2fb_map[i] = -1;
				अगर (!search_fb_in_map(idx)) अणु
					ret = con2fb_release_oldinfo(vc_cons[i].d,
								     info, शून्य, i,
								     idx, 0);
					अगर (ret) अणु
						con2fb_map[i] = idx;
						वापस;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		fbcon_unbind();
	पूर्ण
पूर्ण

/* called with console_lock held */
व्योम fbcon_fb_unरेजिस्टरed(काष्ठा fb_info *info)
अणु
	पूर्णांक i, idx;

	WARN_CONSOLE_UNLOCKED();

	अगर (deferred_takeover)
		वापस;

	idx = info->node;
	क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
		अगर (con2fb_map[i] == idx)
			con2fb_map[i] = -1;
	पूर्ण

	अगर (idx == info_idx) अणु
		info_idx = -1;

		क्रम_each_रेजिस्टरed_fb(i) अणु
			info_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (info_idx != -1) अणु
		क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
			अगर (con2fb_map[i] == -1)
				con2fb_map[i] = info_idx;
		पूर्ण
	पूर्ण

	अगर (primary_device == idx)
		primary_device = -1;

	अगर (!num_रेजिस्टरed_fb)
		करो_unरेजिस्टर_con_driver(&fb_con);
पूर्ण

व्योम fbcon_remap_all(काष्ठा fb_info *info)
अणु
	पूर्णांक i, idx = info->node;

	console_lock();
	अगर (deferred_takeover) अणु
		क्रम (i = first_fb_vc; i <= last_fb_vc; i++)
			con2fb_map_boot[i] = idx;
		fbcon_map_override();
		console_unlock();
		वापस;
	पूर्ण

	क्रम (i = first_fb_vc; i <= last_fb_vc; i++)
		set_con2fb_map(i, idx, 0);

	अगर (con_is_bound(&fb_con)) अणु
		prपूर्णांकk(KERN_INFO "fbcon: Remapping primary device, "
		       "fb%i, to tty %i-%i\n", idx,
		       first_fb_vc + 1, last_fb_vc + 1);
		info_idx = idx;
	पूर्ण
	console_unlock();
पूर्ण

#अगर_घोषित CONFIG_FRAMEBUFFER_CONSOLE_DETECT_PRIMARY
अटल व्योम fbcon_select_primary(काष्ठा fb_info *info)
अणु
	अगर (!map_override && primary_device == -1 &&
	    fb_is_primary_device(info)) अणु
		पूर्णांक i;

		prपूर्णांकk(KERN_INFO "fbcon: %s (fb%i) is primary device\n",
		       info->fix.id, info->node);
		primary_device = info->node;

		क्रम (i = first_fb_vc; i <= last_fb_vc; i++)
			con2fb_map_boot[i] = primary_device;

		अगर (con_is_bound(&fb_con)) अणु
			prपूर्णांकk(KERN_INFO "fbcon: Remapping primary device, "
			       "fb%i, to tty %i-%i\n", info->node,
			       first_fb_vc + 1, last_fb_vc + 1);
			info_idx = primary_device;
		पूर्ण
	पूर्ण

पूर्ण
#अन्यथा
अटल अंतरभूत व्योम fbcon_select_primary(काष्ठा fb_info *info)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर /* CONFIG_FRAMEBUFFER_DETECT_PRIMARY */

/* called with console_lock held */
पूर्णांक fbcon_fb_रेजिस्टरed(काष्ठा fb_info *info)
अणु
	पूर्णांक ret = 0, i, idx;

	WARN_CONSOLE_UNLOCKED();

	idx = info->node;
	fbcon_select_primary(info);

	अगर (deferred_takeover) अणु
		pr_info("fbcon: Deferring console take-over\n");
		वापस 0;
	पूर्ण

	अगर (info_idx == -1) अणु
		क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
			अगर (con2fb_map_boot[i] == idx) अणु
				info_idx = idx;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (info_idx != -1)
			ret = करो_fbcon_takeover(1);
	पूर्ण अन्यथा अणु
		क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
			अगर (con2fb_map_boot[i] == idx)
				set_con2fb_map(i, idx, 0);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

व्योम fbcon_fb_blanked(काष्ठा fb_info *info, पूर्णांक blank)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	काष्ठा vc_data *vc;

	अगर (!ops || ops->currcon < 0)
		वापस;

	vc = vc_cons[ops->currcon].d;
	अगर (vc->vc_mode != KD_TEXT ||
			रेजिस्टरed_fb[con2fb_map[ops->currcon]] != info)
		वापस;

	अगर (con_is_visible(vc)) अणु
		अगर (blank)
			करो_blank_screen(0);
		अन्यथा
			करो_unblank_screen(0);
	पूर्ण
	ops->blank_state = blank;
पूर्ण

व्योम fbcon_new_modelist(काष्ठा fb_info *info)
अणु
	पूर्णांक i;
	काष्ठा vc_data *vc;
	काष्ठा fb_var_screeninfo var;
	स्थिर काष्ठा fb_videomode *mode;

	क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
		अगर (रेजिस्टरed_fb[con2fb_map[i]] != info)
			जारी;
		अगर (!fb_display[i].mode)
			जारी;
		vc = vc_cons[i].d;
		display_to_var(&var, &fb_display[i]);
		mode = fb_find_nearest_mode(fb_display[i].mode,
					    &info->modelist);
		fb_videomode_to_var(&var, mode);
		fbcon_set_disp(info, &var, vc->vc_num);
	पूर्ण
पूर्ण

व्योम fbcon_get_requirement(काष्ठा fb_info *info,
			   काष्ठा fb_blit_caps *caps)
अणु
	काष्ठा vc_data *vc;

	अगर (caps->flags) अणु
		पूर्णांक i, अक्षरcnt;

		क्रम (i = first_fb_vc; i <= last_fb_vc; i++) अणु
			vc = vc_cons[i].d;
			अगर (vc && vc->vc_mode == KD_TEXT &&
			    info->node == con2fb_map[i]) अणु
				caps->x |= 1 << (vc->vc_font.width - 1);
				caps->y |= 1 << (vc->vc_font.height - 1);
				अक्षरcnt = vc->vc_font.अक्षरcount;
				अगर (caps->len < अक्षरcnt)
					caps->len = अक्षरcnt;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		vc = vc_cons[fg_console].d;

		अगर (vc && vc->vc_mode == KD_TEXT &&
		    info->node == con2fb_map[fg_console]) अणु
			caps->x = 1 << (vc->vc_font.width - 1);
			caps->y = 1 << (vc->vc_font.height - 1);
			caps->len = vc->vc_font.अक्षरcount;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक fbcon_set_con2fb_map_ioctl(व्योम __user *argp)
अणु
	काष्ठा fb_con2fbmap con2fb;
	पूर्णांक ret;

	अगर (copy_from_user(&con2fb, argp, माप(con2fb)))
		वापस -EFAULT;
	अगर (con2fb.console < 1 || con2fb.console > MAX_NR_CONSOLES)
		वापस -EINVAL;
	अगर (con2fb.framebuffer >= FB_MAX)
		वापस -EINVAL;
	अगर (!रेजिस्टरed_fb[con2fb.framebuffer])
		request_module("fb%d", con2fb.framebuffer);
	अगर (!रेजिस्टरed_fb[con2fb.framebuffer]) अणु
		वापस -EINVAL;
	पूर्ण

	console_lock();
	ret = set_con2fb_map(con2fb.console - 1,
			     con2fb.framebuffer, 1);
	console_unlock();

	वापस ret;
पूर्ण

पूर्णांक fbcon_get_con2fb_map_ioctl(व्योम __user *argp)
अणु
	काष्ठा fb_con2fbmap con2fb;

	अगर (copy_from_user(&con2fb, argp, माप(con2fb)))
		वापस -EFAULT;
	अगर (con2fb.console < 1 || con2fb.console > MAX_NR_CONSOLES)
		वापस -EINVAL;

	console_lock();
	con2fb.framebuffer = con2fb_map[con2fb.console - 1];
	console_unlock();

	वापस copy_to_user(argp, &con2fb, माप(con2fb)) ? -EFAULT : 0;
पूर्ण

/*
 *  The console `चयन' काष्ठाure क्रम the frame buffer based console
 */

अटल स्थिर काष्ठा consw fb_con = अणु
	.owner			= THIS_MODULE,
	.con_startup 		= fbcon_startup,
	.con_init 		= fbcon_init,
	.con_deinit 		= fbcon_deinit,
	.con_clear 		= fbcon_clear,
	.con_अ_दो 		= fbcon_अ_दो,
	.con_अ_दोs 		= fbcon_अ_दोs,
	.con_cursor 		= fbcon_cursor,
	.con_scroll 		= fbcon_scroll,
	.con_चयन 		= fbcon_चयन,
	.con_blank 		= fbcon_blank,
	.con_font_set 		= fbcon_set_font,
	.con_font_get 		= fbcon_get_font,
	.con_font_शेष	= fbcon_set_def_font,
	.con_set_palette 	= fbcon_set_palette,
	.con_invert_region 	= fbcon_invert_region,
	.con_screen_pos 	= fbcon_screen_pos,
	.con_getxy 		= fbcon_getxy,
	.con_resize             = fbcon_resize,
	.con_debug_enter	= fbcon_debug_enter,
	.con_debug_leave	= fbcon_debug_leave,
पूर्ण;

अटल sमाप_प्रकार store_rotate(काष्ठा device *device,
			    काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	काष्ठा fb_info *info;
	पूर्णांक rotate, idx;
	अक्षर **last = शून्य;

	console_lock();
	idx = con2fb_map[fg_console];

	अगर (idx == -1 || रेजिस्टरed_fb[idx] == शून्य)
		जाओ err;

	info = रेजिस्टरed_fb[idx];
	rotate = simple_म_से_अदीर्घ(buf, last, 0);
	fbcon_rotate(info, rotate);
err:
	console_unlock();
	वापस count;
पूर्ण

अटल sमाप_प्रकार store_rotate_all(काष्ठा device *device,
				काष्ठा device_attribute *attr,स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा fb_info *info;
	पूर्णांक rotate, idx;
	अक्षर **last = शून्य;

	console_lock();
	idx = con2fb_map[fg_console];

	अगर (idx == -1 || रेजिस्टरed_fb[idx] == शून्य)
		जाओ err;

	info = रेजिस्टरed_fb[idx];
	rotate = simple_म_से_अदीर्घ(buf, last, 0);
	fbcon_rotate_all(info, rotate);
err:
	console_unlock();
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_rotate(काष्ठा device *device,
			   काष्ठा device_attribute *attr,अक्षर *buf)
अणु
	काष्ठा fb_info *info;
	पूर्णांक rotate = 0, idx;

	console_lock();
	idx = con2fb_map[fg_console];

	अगर (idx == -1 || रेजिस्टरed_fb[idx] == शून्य)
		जाओ err;

	info = रेजिस्टरed_fb[idx];
	rotate = fbcon_get_rotate(info);
err:
	console_unlock();
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", rotate);
पूर्ण

अटल sमाप_प्रकार show_cursor_blink(काष्ठा device *device,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info;
	काष्ठा fbcon_ops *ops;
	पूर्णांक idx, blink = -1;

	console_lock();
	idx = con2fb_map[fg_console];

	अगर (idx == -1 || रेजिस्टरed_fb[idx] == शून्य)
		जाओ err;

	info = रेजिस्टरed_fb[idx];
	ops = info->fbcon_par;

	अगर (!ops)
		जाओ err;

	blink = (ops->flags & FBCON_FLAGS_CURSOR_TIMER) ? 1 : 0;
err:
	console_unlock();
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", blink);
पूर्ण

अटल sमाप_प्रकार store_cursor_blink(काष्ठा device *device,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *info;
	पूर्णांक blink, idx;
	अक्षर **last = शून्य;

	console_lock();
	idx = con2fb_map[fg_console];

	अगर (idx == -1 || रेजिस्टरed_fb[idx] == शून्य)
		जाओ err;

	info = रेजिस्टरed_fb[idx];

	अगर (!info->fbcon_par)
		जाओ err;

	blink = simple_म_से_अदीर्घ(buf, last, 0);

	अगर (blink) अणु
		fbcon_cursor_noblink = 0;
		fbcon_add_cursor_समयr(info);
	पूर्ण अन्यथा अणु
		fbcon_cursor_noblink = 1;
		fbcon_del_cursor_समयr(info);
	पूर्ण

err:
	console_unlock();
	वापस count;
पूर्ण

अटल काष्ठा device_attribute device_attrs[] = अणु
	__ATTR(rotate, S_IRUGO|S_IWUSR, show_rotate, store_rotate),
	__ATTR(rotate_all, S_IWUSR, शून्य, store_rotate_all),
	__ATTR(cursor_blink, S_IRUGO|S_IWUSR, show_cursor_blink,
	       store_cursor_blink),
पूर्ण;

अटल पूर्णांक fbcon_init_device(व्योम)
अणु
	पूर्णांक i, error = 0;

	fbcon_has_sysfs = 1;

	क्रम (i = 0; i < ARRAY_SIZE(device_attrs); i++) अणु
		error = device_create_file(fbcon_device, &device_attrs[i]);

		अगर (error)
			अवरोध;
	पूर्ण

	अगर (error) अणु
		जबतक (--i >= 0)
			device_हटाओ_file(fbcon_device, &device_attrs[i]);

		fbcon_has_sysfs = 0;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_FRAMEBUFFER_CONSOLE_DEFERRED_TAKEOVER
अटल व्योम fbcon_रेजिस्टर_existing_fbs(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक i;

	console_lock();

	क्रम_each_रेजिस्टरed_fb(i)
		fbcon_fb_रेजिस्टरed(रेजिस्टरed_fb[i]);

	console_unlock();
पूर्ण

अटल काष्ठा notअगरier_block fbcon_output_nb;
अटल DECLARE_WORK(fbcon_deferred_takeover_work, fbcon_रेजिस्टर_existing_fbs);

अटल पूर्णांक fbcon_output_notअगरier(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ action, व्योम *data)
अणु
	WARN_CONSOLE_UNLOCKED();

	pr_info("fbcon: Taking over console\n");

	dummycon_unरेजिस्टर_output_notअगरier(&fbcon_output_nb);
	deferred_takeover = false;
	logo_shown = FBCON_LOGO_DONTSHOW;

	/* We may get called in atomic context */
	schedule_work(&fbcon_deferred_takeover_work);

	वापस NOTIFY_OK;
पूर्ण
#पूर्ण_अगर

अटल व्योम fbcon_start(व्योम)
अणु
	WARN_CONSOLE_UNLOCKED();

#अगर_घोषित CONFIG_FRAMEBUFFER_CONSOLE_DEFERRED_TAKEOVER
	अगर (conचयनp != &dummy_con)
		deferred_takeover = false;

	अगर (deferred_takeover) अणु
		fbcon_output_nb.notअगरier_call = fbcon_output_notअगरier;
		dummycon_रेजिस्टर_output_notअगरier(&fbcon_output_nb);
		वापस;
	पूर्ण
#पूर्ण_अगर

	अगर (num_रेजिस्टरed_fb) अणु
		पूर्णांक i;

		क्रम_each_रेजिस्टरed_fb(i) अणु
			info_idx = i;
			अवरोध;
		पूर्ण

		करो_fbcon_takeover(0);
	पूर्ण
पूर्ण

अटल व्योम fbcon_निकास(व्योम)
अणु
	काष्ठा fb_info *info;
	पूर्णांक i, j, mapped;

#अगर_घोषित CONFIG_FRAMEBUFFER_CONSOLE_DEFERRED_TAKEOVER
	अगर (deferred_takeover) अणु
		dummycon_unरेजिस्टर_output_notअगरier(&fbcon_output_nb);
		deferred_takeover = false;
	पूर्ण
#पूर्ण_अगर

	क्रम_each_रेजिस्टरed_fb(i) अणु
		पूर्णांक pending = 0;

		mapped = 0;
		info = रेजिस्टरed_fb[i];

		अगर (info->queue.func)
			pending = cancel_work_sync(&info->queue);
		pr_debug("fbcon: %s pending work\n", (pending ? "canceled" : "no"));

		क्रम (j = first_fb_vc; j <= last_fb_vc; j++) अणु
			अगर (con2fb_map[j] == i) अणु
				mapped = 1;
				con2fb_map[j] = -1;
			पूर्ण
		पूर्ण

		अगर (mapped) अणु
			अगर (info->fbops->fb_release)
				info->fbops->fb_release(info, 0);
			module_put(info->fbops->owner);

			अगर (info->fbcon_par) अणु
				काष्ठा fbcon_ops *ops = info->fbcon_par;

				fbcon_del_cursor_समयr(info);
				kमुक्त(ops->cursor_src);
				kमुक्त(ops->cursor_state.mask);
				kमुक्त(info->fbcon_par);
				info->fbcon_par = शून्य;
			पूर्ण

			अगर (info->queue.func == fb_flashcursor)
				info->queue.func = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init fb_console_init(व्योम)
अणु
	पूर्णांक i;

	console_lock();
	fbcon_device = device_create(fb_class, शून्य, MKDEV(0, 0), शून्य,
				     "fbcon");

	अगर (IS_ERR(fbcon_device)) अणु
		prपूर्णांकk(KERN_WARNING "Unable to create device "
		       "for fbcon; errno = %ld\n",
		       PTR_ERR(fbcon_device));
		fbcon_device = शून्य;
	पूर्ण अन्यथा
		fbcon_init_device();

	क्रम (i = 0; i < MAX_NR_CONSOLES; i++)
		con2fb_map[i] = -1;

	fbcon_start();
	console_unlock();
पूर्ण

#अगर_घोषित MODULE

अटल व्योम __निकास fbcon_deinit_device(व्योम)
अणु
	पूर्णांक i;

	अगर (fbcon_has_sysfs) अणु
		क्रम (i = 0; i < ARRAY_SIZE(device_attrs); i++)
			device_हटाओ_file(fbcon_device, &device_attrs[i]);

		fbcon_has_sysfs = 0;
	पूर्ण
पूर्ण

व्योम __निकास fb_console_निकास(व्योम)
अणु
	console_lock();
	fbcon_deinit_device();
	device_destroy(fb_class, MKDEV(0, 0));
	fbcon_निकास();
	करो_unरेजिस्टर_con_driver(&fb_con);
	console_unlock();
पूर्ण	
#पूर्ण_अगर
