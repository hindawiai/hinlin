<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

/*
 * Hopefully this will be a rather complete VT102 implementation.
 *
 * Beeping thanks to John T Kohl.
 *
 * Virtual Consoles, Screen Blanking, Screen Dumping, Color, Graphics
 *   Chars, and VT100 enhancements by Peter MacDonald.
 *
 * Copy and paste function by Andrew Haylett,
 *   some enhancements by Alessandro Rubini.
 *
 * Code to check क्रम dअगरferent video-cards mostly by Galen Hunt,
 * <g-hunt@ee.utah.edu>
 *
 * Rudimentary ISO 10646/Unicode/UTF-8 अक्षरacter set support by
 * Markus Kuhn, <mskuhn@immd4.inक्रमmatik.uni-erlangen.de>.
 *
 * Dynamic allocation of consoles, aeb@cwi.nl, May 1994
 * Resizing of consoles, aeb, 940926
 *
 * Code क्रम xterm like mouse click reporting by Peter Orbaek 20-Jul-94
 * <poe@daimi.aau.dk>
 *
 * User-defined bell sound, new setterm control sequences and prपूर्णांकk
 * redirection by Martin Mares <mj@k332.feld.cvut.cz> 19-Nov-95
 *
 * APM screenblank bug fixed Takashi Manabe <manabe@roy.dsl.tutics.tut.jp>
 *
 * Merge with the असलtract console driver by Geert Uytterhoeven
 * <geert@linux-m68k.org>, Jan 1997.
 *
 *   Original m68k console driver modअगरications by
 *
 *     - Arno Grअगरfioen <arno@usn.nl>
 *     - David Carter <carter@cs.bris.ac.uk>
 * 
 *   The असलtract console driver provides a generic पूर्णांकerface क्रम a text
 *   console. It supports VGA text mode, frame buffer based graphical consoles
 *   and special graphics processors that are only accessible through some
 *   रेजिस्टरs (e.g. a TMS340x0 GSP).
 *
 *   The पूर्णांकerface to the hardware is specअगरied using a special काष्ठाure
 *   (काष्ठा consw) which contains function poपूर्णांकers to console operations
 *   (see <linux/console.h> क्रम more inक्रमmation).
 *
 * Support क्रम changeable cursor shape
 * by Pavel Machek <pavel@atrey.karlin.mff.cuni.cz>, August 1997
 *
 * Ported to i386 and con_scrolldelta fixed
 * by Emmanuel Marty <core@ggi-project.org>, April 1998
 *
 * Resurrected अक्षरacter buffers in videoram plus lots of other trickery
 * by Martin Mares <mj@atrey.karlin.mff.cuni.cz>, July 1998
 *
 * Removed old-style समयrs, पूर्णांकroduced console_समयr, made समयr
 * deletion SMP-safe.  17Jun00, Andrew Morton
 *
 * Removed console_lock, enabled पूर्णांकerrupts across all console operations
 * 13 March 2001, Andrew Morton
 *
 * Fixed UTF-8 mode so alternate अक्षरset modes always work according
 * to control sequences पूर्णांकerpreted in करो_con_trol function
 * preserving backward VT100 semigraphics compatibility,
 * malक्रमmed UTF sequences represented as sequences of replacement glyphs,
 * original codes or '?' as a last resort अगर replacement glyph is undefined
 * by Adam Tla/lka <atlka@pg.gda.pl>, Aug 2006
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kd.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/major.h>
#समावेश <linux/mm.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/selection.h>
#समावेश <linux/tiocl.h>
#समावेश <linux/kbd_kern.h>
#समावेश <linux/consolemap.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pm.h>
#समावेश <linux/font.h>
#समावेश <linux/bitops.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/kdb.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/gcd.h>

#घोषणा MAX_NR_CON_DRIVER 16

#घोषणा CON_DRIVER_FLAG_MODULE 1
#घोषणा CON_DRIVER_FLAG_INIT   2
#घोषणा CON_DRIVER_FLAG_ATTR   4
#घोषणा CON_DRIVER_FLAG_ZOMBIE 8

काष्ठा con_driver अणु
	स्थिर काष्ठा consw *con;
	स्थिर अक्षर *desc;
	काष्ठा device *dev;
	पूर्णांक node;
	पूर्णांक first;
	पूर्णांक last;
	पूर्णांक flag;
पूर्ण;

अटल काष्ठा con_driver रेजिस्टरed_con_driver[MAX_NR_CON_DRIVER];
स्थिर काष्ठा consw *conचयनp;

/*
 * Here is the शेष bell parameters: 750HZ, 1/8th of a second
 */
#घोषणा DEFAULT_BELL_PITCH	750
#घोषणा DEFAULT_BELL_DURATION	(HZ/8)
#घोषणा DEFAULT_CURSOR_BLINK_MS	200

काष्ठा vc vc_cons [MAX_NR_CONSOLES];

#अगर_अघोषित VT_SINGLE_DRIVER
अटल स्थिर काष्ठा consw *con_driver_map[MAX_NR_CONSOLES];
#पूर्ण_अगर

अटल पूर्णांक con_खोलो(काष्ठा tty_काष्ठा *, काष्ठा file *);
अटल व्योम vc_init(काष्ठा vc_data *vc, अचिन्हित पूर्णांक rows,
		    अचिन्हित पूर्णांक cols, पूर्णांक करो_clear);
अटल व्योम जाओxy(काष्ठा vc_data *vc, पूर्णांक new_x, पूर्णांक new_y);
अटल व्योम save_cur(काष्ठा vc_data *vc);
अटल व्योम reset_terminal(काष्ठा vc_data *vc, पूर्णांक करो_clear);
अटल व्योम con_flush_अक्षरs(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक set_vesa_blanking(अक्षर __user *p);
अटल व्योम set_cursor(काष्ठा vc_data *vc);
अटल व्योम hide_cursor(काष्ठा vc_data *vc);
अटल व्योम console_callback(काष्ठा work_काष्ठा *ignored);
अटल व्योम con_driver_unरेजिस्टर_callback(काष्ठा work_काष्ठा *ignored);
अटल व्योम blank_screen_t(काष्ठा समयr_list *unused);
अटल व्योम set_palette(काष्ठा vc_data *vc);

#घोषणा vt_get_kmsg_redirect() vt_kmsg_redirect(-1)

अटल पूर्णांक prपूर्णांकable;		/* Is console पढ़ोy क्रम prपूर्णांकing? */
पूर्णांक शेष_utf8 = true;
module_param(शेष_utf8, पूर्णांक, S_IRUGO | S_IWUSR);
पूर्णांक global_cursor_शेष = -1;
module_param(global_cursor_शेष, पूर्णांक, S_IRUGO | S_IWUSR);

अटल पूर्णांक cur_शेष = CUR_UNDERLINE;
module_param(cur_शेष, पूर्णांक, S_IRUGO | S_IWUSR);

/*
 * ignore_poke: करोn't unblank the screen when things are typed.  This is
 * मुख्यly क्रम the privacy of braille terminal users.
 */
अटल पूर्णांक ignore_poke;

पूर्णांक करो_poke_blanked_console;
पूर्णांक console_blanked;

अटल पूर्णांक vesa_blank_mode; /* 0:none 1:suspendV 2:suspendH 3:घातerकरोwn */
अटल पूर्णांक vesa_off_पूर्णांकerval;
अटल पूर्णांक blankपूर्णांकerval;
core_param(consoleblank, blankपूर्णांकerval, पूर्णांक, 0444);

अटल DECLARE_WORK(console_work, console_callback);
अटल DECLARE_WORK(con_driver_unरेजिस्टर_work, con_driver_unरेजिस्टर_callback);

/*
 * fg_console is the current भव console,
 * last_console is the last used one,
 * want_console is the console we want to चयन to,
 * saved_* variants are क्रम save/restore around kernel debugger enter/leave
 */
पूर्णांक fg_console;
पूर्णांक last_console;
पूर्णांक want_console = -1;
अटल पूर्णांक saved_fg_console;
अटल पूर्णांक saved_last_console;
अटल पूर्णांक saved_want_console;
अटल पूर्णांक saved_vc_mode;
अटल पूर्णांक saved_console_blanked;

/*
 * For each existing display, we have a poपूर्णांकer to console currently visible
 * on that display, allowing consoles other than fg_console to be refreshed
 * appropriately. Unless the low-level driver supplies its own display_fg
 * variable, we use this one क्रम the "master display".
 */
अटल काष्ठा vc_data *master_display_fg;

/*
 * Unक्रमtunately, we need to delay tty echo when we're currently writing to the
 * console since the code is (and always was) not re-entrant, so we schedule
 * all flip requests to process context with schedule-task() and run it from
 * console_callback().
 */

/*
 * For the same reason, we defer scrollback to the console callback.
 */
अटल पूर्णांक scrollback_delta;

/*
 * Hook so that the घातer management routines can (un)blank
 * the console on our behalf.
 */
पूर्णांक (*console_blank_hook)(पूर्णांक);

अटल DEFINE_TIMER(console_समयr, blank_screen_t);
अटल पूर्णांक blank_state;
अटल पूर्णांक blank_समयr_expired;
क्रमागत अणु
	blank_off = 0,
	blank_normal_रुको,
	blank_vesa_रुको,
पूर्ण;

/*
 * /sys/class/tty/tty0/
 *
 * the attribute 'active' contains the name of the current vc
 * console and it supports poll() to detect vc चयनes
 */
अटल काष्ठा device *tty0dev;

/*
 * Notअगरier list क्रम console events.
 */
अटल ATOMIC_NOTIFIER_HEAD(vt_notअगरier_list);

पूर्णांक रेजिस्टर_vt_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&vt_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_vt_notअगरier);

पूर्णांक unरेजिस्टर_vt_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&vt_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_vt_notअगरier);

अटल व्योम notअगरy_ग_लिखो(काष्ठा vc_data *vc, अचिन्हित पूर्णांक unicode)
अणु
	काष्ठा vt_notअगरier_param param = अणु .vc = vc, .c = unicode पूर्ण;
	atomic_notअगरier_call_chain(&vt_notअगरier_list, VT_WRITE, &param);
पूर्ण

अटल व्योम notअगरy_update(काष्ठा vc_data *vc)
अणु
	काष्ठा vt_notअगरier_param param = अणु .vc = vc पूर्ण;
	atomic_notअगरier_call_chain(&vt_notअगरier_list, VT_UPDATE, &param);
पूर्ण
/*
 *	Low-Level Functions
 */

अटल अंतरभूत bool con_is_fg(स्थिर काष्ठा vc_data *vc)
अणु
	वापस vc->vc_num == fg_console;
पूर्ण

अटल अंतरभूत bool con_should_update(स्थिर काष्ठा vc_data *vc)
अणु
	वापस con_is_visible(vc) && !console_blanked;
पूर्ण

अटल अंतरभूत अचिन्हित लघु *screenpos(स्थिर काष्ठा vc_data *vc, पूर्णांक offset,
		bool viewed)
अणु
	अचिन्हित लघु *p;
	
	अगर (!viewed)
		p = (अचिन्हित लघु *)(vc->vc_origin + offset);
	अन्यथा अगर (!vc->vc_sw->con_screen_pos)
		p = (अचिन्हित लघु *)(vc->vc_visible_origin + offset);
	अन्यथा
		p = vc->vc_sw->con_screen_pos(vc, offset);
	वापस p;
पूर्ण

/* Called  from the keyboard irq path.. */
अटल अंतरभूत व्योम scrolldelta(पूर्णांक lines)
अणु
	/* FIXME */
	/* scrolldelta needs some kind of consistency lock, but the BKL was
	   and still is not protecting versus the scheduled back end */
	scrollback_delta += lines;
	schedule_console_callback();
पूर्ण

व्योम schedule_console_callback(व्योम)
अणु
	schedule_work(&console_work);
पूर्ण

/*
 * Code to manage unicode-based screen buffers
 */

#अगर_घोषित NO_VC_UNI_SCREEN
/* this disables and optimizes related code away at compile समय */
#घोषणा get_vc_uniscr(vc) शून्य
#अन्यथा
#घोषणा get_vc_uniscr(vc) vc->vc_uni_screen
#पूर्ण_अगर

#घोषणा VC_UNI_SCREEN_DEBUG 0

प्रकार uपूर्णांक32_t अक्षर32_t;

/*
 * Our screen buffer is preceded by an array of line poपूर्णांकers so that
 * scrolling only implies some poपूर्णांकer shuffling.
 */
काष्ठा uni_screen अणु
	अक्षर32_t *lines[0];
पूर्ण;

अटल काष्ठा uni_screen *vc_uniscr_alloc(अचिन्हित पूर्णांक cols, अचिन्हित पूर्णांक rows)
अणु
	काष्ठा uni_screen *uniscr;
	व्योम *p;
	अचिन्हित पूर्णांक memsize, i;

	/* allocate everything in one go */
	memsize = cols * rows * माप(अक्षर32_t);
	memsize += rows * माप(अक्षर32_t *);
	p = vदो_स्मृति(memsize);
	अगर (!p)
		वापस शून्य;

	/* initial line poपूर्णांकers */
	uniscr = p;
	p = uniscr->lines + rows;
	क्रम (i = 0; i < rows; i++) अणु
		uniscr->lines[i] = p;
		p += cols * माप(अक्षर32_t);
	पूर्ण
	वापस uniscr;
पूर्ण

अटल व्योम vc_uniscr_मुक्त(काष्ठा uni_screen *uniscr)
अणु
	vमुक्त(uniscr);
पूर्ण

अटल व्योम vc_uniscr_set(काष्ठा vc_data *vc, काष्ठा uni_screen *new_uniscr)
अणु
	vc_uniscr_मुक्त(vc->vc_uni_screen);
	vc->vc_uni_screen = new_uniscr;
पूर्ण

अटल व्योम vc_uniscr_अ_दो(काष्ठा vc_data *vc, अक्षर32_t uc)
अणु
	काष्ठा uni_screen *uniscr = get_vc_uniscr(vc);

	अगर (uniscr)
		uniscr->lines[vc->state.y][vc->state.x] = uc;
पूर्ण

अटल व्योम vc_uniscr_insert(काष्ठा vc_data *vc, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा uni_screen *uniscr = get_vc_uniscr(vc);

	अगर (uniscr) अणु
		अक्षर32_t *ln = uniscr->lines[vc->state.y];
		अचिन्हित पूर्णांक x = vc->state.x, cols = vc->vc_cols;

		स_हटाओ(&ln[x + nr], &ln[x], (cols - x - nr) * माप(*ln));
		स_रखो32(&ln[x], ' ', nr);
	पूर्ण
पूर्ण

अटल व्योम vc_uniscr_delete(काष्ठा vc_data *vc, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा uni_screen *uniscr = get_vc_uniscr(vc);

	अगर (uniscr) अणु
		अक्षर32_t *ln = uniscr->lines[vc->state.y];
		अचिन्हित पूर्णांक x = vc->state.x, cols = vc->vc_cols;

		स_नकल(&ln[x], &ln[x + nr], (cols - x - nr) * माप(*ln));
		स_रखो32(&ln[cols - nr], ' ', nr);
	पूर्ण
पूर्ण

अटल व्योम vc_uniscr_clear_line(काष्ठा vc_data *vc, अचिन्हित पूर्णांक x,
				 अचिन्हित पूर्णांक nr)
अणु
	काष्ठा uni_screen *uniscr = get_vc_uniscr(vc);

	अगर (uniscr) अणु
		अक्षर32_t *ln = uniscr->lines[vc->state.y];

		स_रखो32(&ln[x], ' ', nr);
	पूर्ण
पूर्ण

अटल व्योम vc_uniscr_clear_lines(काष्ठा vc_data *vc, अचिन्हित पूर्णांक y,
				  अचिन्हित पूर्णांक nr)
अणु
	काष्ठा uni_screen *uniscr = get_vc_uniscr(vc);

	अगर (uniscr) अणु
		अचिन्हित पूर्णांक cols = vc->vc_cols;

		जबतक (nr--)
			स_रखो32(uniscr->lines[y++], ' ', cols);
	पूर्ण
पूर्ण

अटल व्योम vc_uniscr_scroll(काष्ठा vc_data *vc, अचिन्हित पूर्णांक t, अचिन्हित पूर्णांक b,
			     क्रमागत con_scroll dir, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा uni_screen *uniscr = get_vc_uniscr(vc);

	अगर (uniscr) अणु
		अचिन्हित पूर्णांक i, j, k, sz, d, clear;

		sz = b - t;
		clear = b - nr;
		d = nr;
		अगर (dir == SM_DOWN) अणु
			clear = t;
			d = sz - nr;
		पूर्ण
		क्रम (i = 0; i < gcd(d, sz); i++) अणु
			अक्षर32_t *पंचांगp = uniscr->lines[t + i];
			j = i;
			जबतक (1) अणु
				k = j + d;
				अगर (k >= sz)
					k -= sz;
				अगर (k == i)
					अवरोध;
				uniscr->lines[t + j] = uniscr->lines[t + k];
				j = k;
			पूर्ण
			uniscr->lines[t + j] = पंचांगp;
		पूर्ण
		vc_uniscr_clear_lines(vc, clear, nr);
	पूर्ण
पूर्ण

अटल व्योम vc_uniscr_copy_area(काष्ठा uni_screen *dst,
				अचिन्हित पूर्णांक dst_cols,
				अचिन्हित पूर्णांक dst_rows,
				काष्ठा uni_screen *src,
				अचिन्हित पूर्णांक src_cols,
				अचिन्हित पूर्णांक src_top_row,
				अचिन्हित पूर्णांक src_bot_row)
अणु
	अचिन्हित पूर्णांक dst_row = 0;

	अगर (!dst)
		वापस;

	जबतक (src_top_row < src_bot_row) अणु
		अक्षर32_t *src_line = src->lines[src_top_row];
		अक्षर32_t *dst_line = dst->lines[dst_row];

		स_नकल(dst_line, src_line, src_cols * माप(अक्षर32_t));
		अगर (dst_cols - src_cols)
			स_रखो32(dst_line + src_cols, ' ', dst_cols - src_cols);
		src_top_row++;
		dst_row++;
	पूर्ण
	जबतक (dst_row < dst_rows) अणु
		अक्षर32_t *dst_line = dst->lines[dst_row];

		स_रखो32(dst_line, ' ', dst_cols);
		dst_row++;
	पूर्ण
पूर्ण

/*
 * Called from vcs_पढ़ो() to make sure unicode screen retrieval is possible.
 * This will initialize the unicode screen buffer अगर not alपढ़ोy करोne.
 * This वापसs 0 अगर OK, or a negative error code otherwise.
 * In particular, -ENODATA is वापसed अगर the console is not in UTF-8 mode.
 */
पूर्णांक vc_uniscr_check(काष्ठा vc_data *vc)
अणु
	काष्ठा uni_screen *uniscr;
	अचिन्हित लघु *p;
	पूर्णांक x, y, mask;

	अगर (__is_defined(NO_VC_UNI_SCREEN))
		वापस -EOPNOTSUPP;

	WARN_CONSOLE_UNLOCKED();

	अगर (!vc->vc_utf)
		वापस -ENODATA;

	अगर (vc->vc_uni_screen)
		वापस 0;

	uniscr = vc_uniscr_alloc(vc->vc_cols, vc->vc_rows);
	अगर (!uniscr)
		वापस -ENOMEM;

	/*
	 * Let's populate it initially with (imperfect) reverse translation.
	 * This is the next best thing we can करो लघु of having it enabled
	 * from the start even when no users rely on this functionality. True
	 * unicode content will be available after a complete screen refresh.
	 */
	p = (अचिन्हित लघु *)vc->vc_origin;
	mask = vc->vc_hi_font_mask | 0xff;
	क्रम (y = 0; y < vc->vc_rows; y++) अणु
		अक्षर32_t *line = uniscr->lines[y];
		क्रम (x = 0; x < vc->vc_cols; x++) अणु
			u16 glyph = scr_पढ़ोw(p++) & mask;
			line[x] = inverse_translate(vc, glyph, true);
		पूर्ण
	पूर्ण

	vc->vc_uni_screen = uniscr;
	वापस 0;
पूर्ण

/*
 * Called from vcs_पढ़ो() to get the unicode data from the screen.
 * This must be preceded by a successful call to vc_uniscr_check() once
 * the console lock has been taken.
 */
व्योम vc_uniscr_copy_line(स्थिर काष्ठा vc_data *vc, व्योम *dest, bool viewed,
			 अचिन्हित पूर्णांक row, अचिन्हित पूर्णांक col, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा uni_screen *uniscr = get_vc_uniscr(vc);
	पूर्णांक offset = row * vc->vc_size_row + col * 2;
	अचिन्हित दीर्घ pos;

	BUG_ON(!uniscr);

	pos = (अचिन्हित दीर्घ)screenpos(vc, offset, viewed);
	अगर (pos >= vc->vc_origin && pos < vc->vc_scr_end) अणु
		/*
		 * Desired position falls in the मुख्य screen buffer.
		 * However the actual row/col might be dअगरferent अगर
		 * scrollback is active.
		 */
		row = (pos - vc->vc_origin) / vc->vc_size_row;
		col = ((pos - vc->vc_origin) % vc->vc_size_row) / 2;
		स_नकल(dest, &uniscr->lines[row][col], nr * माप(अक्षर32_t));
	पूर्ण अन्यथा अणु
		/*
		 * Scrollback is active. For now let's simply backtranslate
		 * the screen glyphs until the unicode screen buffer करोes
		 * synchronize with console display drivers क्रम a scrollback
		 * buffer of its own.
		 */
		u16 *p = (u16 *)pos;
		पूर्णांक mask = vc->vc_hi_font_mask | 0xff;
		अक्षर32_t *uni_buf = dest;
		जबतक (nr--) अणु
			u16 glyph = scr_पढ़ोw(p++) & mask;
			*uni_buf++ = inverse_translate(vc, glyph, true);
		पूर्ण
	पूर्ण
पूर्ण

/* this is क्रम validation and debugging only */
अटल व्योम vc_uniscr_debug_check(काष्ठा vc_data *vc)
अणु
	काष्ठा uni_screen *uniscr = get_vc_uniscr(vc);
	अचिन्हित लघु *p;
	पूर्णांक x, y, mask;

	अगर (!VC_UNI_SCREEN_DEBUG || !uniscr)
		वापस;

	WARN_CONSOLE_UNLOCKED();

	/*
	 * Make sure our unicode screen translates पूर्णांकo the same glyphs
	 * as the actual screen. This is brutal indeed.
	 */
	p = (अचिन्हित लघु *)vc->vc_origin;
	mask = vc->vc_hi_font_mask | 0xff;
	क्रम (y = 0; y < vc->vc_rows; y++) अणु
		अक्षर32_t *line = uniscr->lines[y];
		क्रम (x = 0; x < vc->vc_cols; x++) अणु
			u16 glyph = scr_पढ़ोw(p++) & mask;
			अक्षर32_t uc = line[x];
			पूर्णांक tc = conv_uni_to_pc(vc, uc);
			अगर (tc == -4)
				tc = conv_uni_to_pc(vc, 0xfffd);
			अगर (tc == -4)
				tc = conv_uni_to_pc(vc, '?');
			अगर (tc != glyph)
				pr_err_ratelimited(
					"%s: mismatch at %d,%d: glyph=%#x tc=%#x\n",
					__func__, x, y, glyph, tc);
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम con_scroll(काष्ठा vc_data *vc, अचिन्हित पूर्णांक t, अचिन्हित पूर्णांक b,
		क्रमागत con_scroll dir, अचिन्हित पूर्णांक nr)
अणु
	u16 *clear, *d, *s;

	अगर (t + nr >= b)
		nr = b - t - 1;
	अगर (b > vc->vc_rows || t >= b || nr < 1)
		वापस;
	vc_uniscr_scroll(vc, t, b, dir, nr);
	अगर (con_is_visible(vc) && vc->vc_sw->con_scroll(vc, t, b, dir, nr))
		वापस;

	s = clear = (u16 *)(vc->vc_origin + vc->vc_size_row * t);
	d = (u16 *)(vc->vc_origin + vc->vc_size_row * (t + nr));

	अगर (dir == SM_UP) अणु
		clear = s + (b - t - nr) * vc->vc_cols;
		swap(s, d);
	पूर्ण
	scr_स_हटाओw(d, s, (b - t - nr) * vc->vc_size_row);
	scr_स_रखोw(clear, vc->vc_video_erase_अक्षर, vc->vc_size_row * nr);
पूर्ण

अटल व्योम करो_update_region(काष्ठा vc_data *vc, अचिन्हित दीर्घ start, पूर्णांक count)
अणु
	अचिन्हित पूर्णांक xx, yy, offset;
	u16 *p;

	p = (u16 *) start;
	अगर (!vc->vc_sw->con_getxy) अणु
		offset = (start - vc->vc_origin) / 2;
		xx = offset % vc->vc_cols;
		yy = offset / vc->vc_cols;
	पूर्ण अन्यथा अणु
		पूर्णांक nxx, nyy;
		start = vc->vc_sw->con_getxy(vc, start, &nxx, &nyy);
		xx = nxx; yy = nyy;
	पूर्ण
	क्रम(;;) अणु
		u16 attrib = scr_पढ़ोw(p) & 0xff00;
		पूर्णांक startx = xx;
		u16 *q = p;
		जबतक (xx < vc->vc_cols && count) अणु
			अगर (attrib != (scr_पढ़ोw(p) & 0xff00)) अणु
				अगर (p > q)
					vc->vc_sw->con_अ_दोs(vc, q, p-q, yy, startx);
				startx = xx;
				q = p;
				attrib = scr_पढ़ोw(p) & 0xff00;
			पूर्ण
			p++;
			xx++;
			count--;
		पूर्ण
		अगर (p > q)
			vc->vc_sw->con_अ_दोs(vc, q, p-q, yy, startx);
		अगर (!count)
			अवरोध;
		xx = 0;
		yy++;
		अगर (vc->vc_sw->con_getxy) अणु
			p = (u16 *)start;
			start = vc->vc_sw->con_getxy(vc, start, शून्य, शून्य);
		पूर्ण
	पूर्ण
पूर्ण

व्योम update_region(काष्ठा vc_data *vc, अचिन्हित दीर्घ start, पूर्णांक count)
अणु
	WARN_CONSOLE_UNLOCKED();

	अगर (con_should_update(vc)) अणु
		hide_cursor(vc);
		करो_update_region(vc, start, count);
		set_cursor(vc);
	पूर्ण
पूर्ण

/* Structure of attributes is hardware-dependent */

अटल u8 build_attr(काष्ठा vc_data *vc, u8 _color,
		क्रमागत vc_पूर्णांकensity _पूर्णांकensity, bool _blink, bool _underline,
		bool _reverse, bool _italic)
अणु
	अगर (vc->vc_sw->con_build_attr)
		वापस vc->vc_sw->con_build_attr(vc, _color, _पूर्णांकensity,
		       _blink, _underline, _reverse, _italic);

/*
 * ++roman: I completely changed the attribute क्रमmat क्रम monochrome
 * mode (!can_करो_color). The क्रमmerly used MDA (monochrome display
 * adapter) क्रमmat didn't allow the combination of certain effects.
 * Now the attribute is just a bit vector:
 *  Bit 0..1: पूर्णांकensity (0..2)
 *  Bit 2   : underline
 *  Bit 3   : reverse
 *  Bit 7   : blink
 */
	अणु
	u8 a = _color;
	अगर (!vc->vc_can_करो_color)
		वापस _पूर्णांकensity |
		       (_italic    << 1) |
		       (_underline << 2) |
		       (_reverse   << 3) |
		       (_blink     << 7);
	अगर (_italic)
		a = (a & 0xF0) | vc->vc_itcolor;
	अन्यथा अगर (_underline)
		a = (a & 0xf0) | vc->vc_ulcolor;
	अन्यथा अगर (_पूर्णांकensity == VCI_HALF_BRIGHT)
		a = (a & 0xf0) | vc->vc_halfcolor;
	अगर (_reverse)
		a = (a & 0x88) | (((a >> 4) | (a << 4)) & 0x77);
	अगर (_blink)
		a ^= 0x80;
	अगर (_पूर्णांकensity == VCI_BOLD)
		a ^= 0x08;
	अगर (vc->vc_hi_font_mask == 0x100)
		a <<= 1;
	वापस a;
	पूर्ण
पूर्ण

अटल व्योम update_attr(काष्ठा vc_data *vc)
अणु
	vc->vc_attr = build_attr(vc, vc->state.color, vc->state.पूर्णांकensity,
	              vc->state.blink, vc->state.underline,
	              vc->state.reverse ^ vc->vc_decscnm, vc->state.italic);
	vc->vc_video_erase_अक्षर = ' ' | (build_attr(vc, vc->state.color,
				VCI_NORMAL, vc->state.blink, false,
				vc->vc_decscnm, false) << 8);
पूर्ण

/* Note: inverting the screen twice should revert to the original state */
व्योम invert_screen(काष्ठा vc_data *vc, पूर्णांक offset, पूर्णांक count, bool viewed)
अणु
	अचिन्हित लघु *p;

	WARN_CONSOLE_UNLOCKED();

	count /= 2;
	p = screenpos(vc, offset, viewed);
	अगर (vc->vc_sw->con_invert_region) अणु
		vc->vc_sw->con_invert_region(vc, p, count);
	पूर्ण अन्यथा अणु
		u16 *q = p;
		पूर्णांक cnt = count;
		u16 a;

		अगर (!vc->vc_can_करो_color) अणु
			जबतक (cnt--) अणु
			    a = scr_पढ़ोw(q);
			    a ^= 0x0800;
			    scr_ग_लिखोw(a, q);
			    q++;
			पूर्ण
		पूर्ण अन्यथा अगर (vc->vc_hi_font_mask == 0x100) अणु
			जबतक (cnt--) अणु
				a = scr_पढ़ोw(q);
				a = (a & 0x11ff) |
				   ((a & 0xe000) >> 4) |
				   ((a & 0x0e00) << 4);
				scr_ग_लिखोw(a, q);
				q++;
			पूर्ण
		पूर्ण अन्यथा अणु
			जबतक (cnt--) अणु
				a = scr_पढ़ोw(q);
				a = (a & 0x88ff) |
				   ((a & 0x7000) >> 4) |
				   ((a & 0x0700) << 4);
				scr_ग_लिखोw(a, q);
				q++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (con_should_update(vc))
		करो_update_region(vc, (अचिन्हित दीर्घ) p, count);
	notअगरy_update(vc);
पूर्ण

/* used by selection: complement poपूर्णांकer position */
व्योम complement_pos(काष्ठा vc_data *vc, पूर्णांक offset)
अणु
	अटल पूर्णांक old_offset = -1;
	अटल अचिन्हित लघु old;
	अटल अचिन्हित लघु oldx, oldy;

	WARN_CONSOLE_UNLOCKED();

	अगर (old_offset != -1 && old_offset >= 0 &&
	    old_offset < vc->vc_screenbuf_size) अणु
		scr_ग_लिखोw(old, screenpos(vc, old_offset, true));
		अगर (con_should_update(vc))
			vc->vc_sw->con_अ_दो(vc, old, oldy, oldx);
		notअगरy_update(vc);
	पूर्ण

	old_offset = offset;

	अगर (offset != -1 && offset >= 0 &&
	    offset < vc->vc_screenbuf_size) अणु
		अचिन्हित लघु new;
		अचिन्हित लघु *p;
		p = screenpos(vc, offset, true);
		old = scr_पढ़ोw(p);
		new = old ^ vc->vc_complement_mask;
		scr_ग_लिखोw(new, p);
		अगर (con_should_update(vc)) अणु
			oldx = (offset >> 1) % vc->vc_cols;
			oldy = (offset >> 1) / vc->vc_cols;
			vc->vc_sw->con_अ_दो(vc, new, oldy, oldx);
		पूर्ण
		notअगरy_update(vc);
	पूर्ण
पूर्ण

अटल व्योम insert_अक्षर(काष्ठा vc_data *vc, अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित लघु *p = (अचिन्हित लघु *) vc->vc_pos;

	vc_uniscr_insert(vc, nr);
	scr_स_हटाओw(p + nr, p, (vc->vc_cols - vc->state.x - nr) * 2);
	scr_स_रखोw(p, vc->vc_video_erase_अक्षर, nr * 2);
	vc->vc_need_wrap = 0;
	अगर (con_should_update(vc))
		करो_update_region(vc, (अचिन्हित दीर्घ) p,
			vc->vc_cols - vc->state.x);
पूर्ण

अटल व्योम delete_अक्षर(काष्ठा vc_data *vc, अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित लघु *p = (अचिन्हित लघु *) vc->vc_pos;

	vc_uniscr_delete(vc, nr);
	scr_स_नकलw(p, p + nr, (vc->vc_cols - vc->state.x - nr) * 2);
	scr_स_रखोw(p + vc->vc_cols - vc->state.x - nr, vc->vc_video_erase_अक्षर,
			nr * 2);
	vc->vc_need_wrap = 0;
	अगर (con_should_update(vc))
		करो_update_region(vc, (अचिन्हित दीर्घ) p,
			vc->vc_cols - vc->state.x);
पूर्ण

अटल पूर्णांक softcursor_original = -1;

अटल व्योम add_softcursor(काष्ठा vc_data *vc)
अणु
	पूर्णांक i = scr_पढ़ोw((u16 *) vc->vc_pos);
	u32 type = vc->vc_cursor_type;

	अगर (!(type & CUR_SW))
		वापस;
	अगर (softcursor_original != -1)
		वापस;
	softcursor_original = i;
	i |= CUR_SET(type);
	i ^= CUR_CHANGE(type);
	अगर ((type & CUR_ALWAYS_BG) &&
			(softcursor_original & CUR_BG) == (i & CUR_BG))
		i ^= CUR_BG;
	अगर ((type & CUR_INVERT_FG_BG) && (i & CUR_FG) == ((i & CUR_BG) >> 4))
		i ^= CUR_FG;
	scr_ग_लिखोw(i, (u16 *)vc->vc_pos);
	अगर (con_should_update(vc))
		vc->vc_sw->con_अ_दो(vc, i, vc->state.y, vc->state.x);
पूर्ण

अटल व्योम hide_softcursor(काष्ठा vc_data *vc)
अणु
	अगर (softcursor_original != -1) अणु
		scr_ग_लिखोw(softcursor_original, (u16 *)vc->vc_pos);
		अगर (con_should_update(vc))
			vc->vc_sw->con_अ_दो(vc, softcursor_original,
					vc->state.y, vc->state.x);
		softcursor_original = -1;
	पूर्ण
पूर्ण

अटल व्योम hide_cursor(काष्ठा vc_data *vc)
अणु
	अगर (vc_is_sel(vc))
		clear_selection();

	vc->vc_sw->con_cursor(vc, CM_ERASE);
	hide_softcursor(vc);
पूर्ण

अटल व्योम set_cursor(काष्ठा vc_data *vc)
अणु
	अगर (!con_is_fg(vc) || console_blanked || vc->vc_mode == KD_GRAPHICS)
		वापस;
	अगर (vc->vc_deccm) अणु
		अगर (vc_is_sel(vc))
			clear_selection();
		add_softcursor(vc);
		अगर (CUR_SIZE(vc->vc_cursor_type) != CUR_NONE)
			vc->vc_sw->con_cursor(vc, CM_DRAW);
	पूर्ण अन्यथा
		hide_cursor(vc);
पूर्ण

अटल व्योम set_origin(काष्ठा vc_data *vc)
अणु
	WARN_CONSOLE_UNLOCKED();

	अगर (!con_is_visible(vc) ||
	    !vc->vc_sw->con_set_origin ||
	    !vc->vc_sw->con_set_origin(vc))
		vc->vc_origin = (अचिन्हित दीर्घ)vc->vc_screenbuf;
	vc->vc_visible_origin = vc->vc_origin;
	vc->vc_scr_end = vc->vc_origin + vc->vc_screenbuf_size;
	vc->vc_pos = vc->vc_origin + vc->vc_size_row * vc->state.y +
		2 * vc->state.x;
पूर्ण

अटल व्योम save_screen(काष्ठा vc_data *vc)
अणु
	WARN_CONSOLE_UNLOCKED();

	अगर (vc->vc_sw->con_save_screen)
		vc->vc_sw->con_save_screen(vc);
पूर्ण

अटल व्योम flush_scrollback(काष्ठा vc_data *vc)
अणु
	WARN_CONSOLE_UNLOCKED();

	set_origin(vc);
	अगर (vc->vc_sw->con_flush_scrollback) अणु
		vc->vc_sw->con_flush_scrollback(vc);
	पूर्ण अन्यथा अगर (con_is_visible(vc)) अणु
		/*
		 * When no con_flush_scrollback method is provided then the
		 * legacy way क्रम flushing the scrollback buffer is to use
		 * a side effect of the con_चयन method. We करो it only on
		 * the क्रमeground console as background consoles have no
		 * scrollback buffers in that हाल and we obviously करोn't
		 * want to चयन to them.
		 */
		hide_cursor(vc);
		vc->vc_sw->con_चयन(vc);
		set_cursor(vc);
	पूर्ण
पूर्ण

/*
 *	Redrawing of screen
 */

व्योम clear_buffer_attributes(काष्ठा vc_data *vc)
अणु
	अचिन्हित लघु *p = (अचिन्हित लघु *)vc->vc_origin;
	पूर्णांक count = vc->vc_screenbuf_size / 2;
	पूर्णांक mask = vc->vc_hi_font_mask | 0xff;

	क्रम (; count > 0; count--, p++) अणु
		scr_ग_लिखोw((scr_पढ़ोw(p)&mask) | (vc->vc_video_erase_अक्षर & ~mask), p);
	पूर्ण
पूर्ण

व्योम redraw_screen(काष्ठा vc_data *vc, पूर्णांक is_चयन)
अणु
	पूर्णांक redraw = 0;

	WARN_CONSOLE_UNLOCKED();

	अगर (!vc) अणु
		/* strange ... */
		/* prपूर्णांकk("redraw_screen: tty %d not allocated ??\n", new_console+1); */
		वापस;
	पूर्ण

	अगर (is_चयन) अणु
		काष्ठा vc_data *old_vc = vc_cons[fg_console].d;
		अगर (old_vc == vc)
			वापस;
		अगर (!con_is_visible(vc))
			redraw = 1;
		*vc->vc_display_fg = vc;
		fg_console = vc->vc_num;
		hide_cursor(old_vc);
		अगर (!con_is_visible(old_vc)) अणु
			save_screen(old_vc);
			set_origin(old_vc);
		पूर्ण
		अगर (tty0dev)
			sysfs_notअगरy(&tty0dev->kobj, शून्य, "active");
	पूर्ण अन्यथा अणु
		hide_cursor(vc);
		redraw = 1;
	पूर्ण

	अगर (redraw) अणु
		पूर्णांक update;
		पूर्णांक old_was_color = vc->vc_can_करो_color;

		set_origin(vc);
		update = vc->vc_sw->con_चयन(vc);
		set_palette(vc);
		/*
		 * If console changed from mono<->color, the best we can करो
		 * is to clear the buffer attributes. As it currently stands,
		 * rebuilding new attributes from the old buffer is not करोable
		 * without overly complex code.
		 */
		अगर (old_was_color != vc->vc_can_करो_color) अणु
			update_attr(vc);
			clear_buffer_attributes(vc);
		पूर्ण

		अगर (update && vc->vc_mode != KD_GRAPHICS)
			करो_update_region(vc, vc->vc_origin, vc->vc_screenbuf_size / 2);
	पूर्ण
	set_cursor(vc);
	अगर (is_चयन) अणु
		vt_set_leds_compute_shअगरtstate();
		notअगरy_update(vc);
	पूर्ण
पूर्ण

/*
 *	Allocation, मुक्तing and resizing of VTs.
 */

पूर्णांक vc_cons_allocated(अचिन्हित पूर्णांक i)
अणु
	वापस (i < MAX_NR_CONSOLES && vc_cons[i].d);
पूर्ण

अटल व्योम visual_init(काष्ठा vc_data *vc, पूर्णांक num, पूर्णांक init)
अणु
	/* ++Geert: vc->vc_sw->con_init determines console size */
	अगर (vc->vc_sw)
		module_put(vc->vc_sw->owner);
	vc->vc_sw = conचयनp;
#अगर_अघोषित VT_SINGLE_DRIVER
	अगर (con_driver_map[num])
		vc->vc_sw = con_driver_map[num];
#पूर्ण_अगर
	__module_get(vc->vc_sw->owner);
	vc->vc_num = num;
	vc->vc_display_fg = &master_display_fg;
	अगर (vc->vc_uni_pagedir_loc)
		con_मुक्त_unimap(vc);
	vc->vc_uni_pagedir_loc = &vc->vc_uni_pagedir;
	vc->vc_uni_pagedir = शून्य;
	vc->vc_hi_font_mask = 0;
	vc->vc_complement_mask = 0;
	vc->vc_can_करो_color = 0;
	vc->vc_cur_blink_ms = DEFAULT_CURSOR_BLINK_MS;
	vc->vc_sw->con_init(vc, init);
	अगर (!vc->vc_complement_mask)
		vc->vc_complement_mask = vc->vc_can_करो_color ? 0x7700 : 0x0800;
	vc->vc_s_complement_mask = vc->vc_complement_mask;
	vc->vc_size_row = vc->vc_cols << 1;
	vc->vc_screenbuf_size = vc->vc_rows * vc->vc_size_row;
पूर्ण


अटल व्योम visual_deinit(काष्ठा vc_data *vc)
अणु
	vc->vc_sw->con_deinit(vc);
	module_put(vc->vc_sw->owner);
पूर्ण

अटल व्योम vc_port_deकाष्ठा(काष्ठा tty_port *port)
अणु
	काष्ठा vc_data *vc = container_of(port, काष्ठा vc_data, port);

	kमुक्त(vc);
पूर्ण

अटल स्थिर काष्ठा tty_port_operations vc_port_ops = अणु
	.deकाष्ठा = vc_port_deकाष्ठा,
पूर्ण;

/*
 * Change # of rows and columns (0 means unchanged/the size of fg_console)
 * [this is to be used together with some user program
 * like resize that changes the hardware videomode]
 */
#घोषणा VC_MAXCOL (32767)
#घोषणा VC_MAXROW (32767)

पूर्णांक vc_allocate(अचिन्हित पूर्णांक currcons)	/* वापस 0 on success */
अणु
	काष्ठा vt_notअगरier_param param;
	काष्ठा vc_data *vc;
	पूर्णांक err;

	WARN_CONSOLE_UNLOCKED();

	अगर (currcons >= MAX_NR_CONSOLES)
		वापस -ENXIO;

	अगर (vc_cons[currcons].d)
		वापस 0;

	/* due to the granularity of kदो_स्मृति, we waste some memory here */
	/* the alloc is करोne in two steps, to optimize the common situation
	   of a 25x80 console (काष्ठाsize=216, screenbuf_size=4000) */
	/* although the numbers above are not valid since दीर्घ ago, the
	   poपूर्णांक is still up-to-date and the comment still has its value
	   even अगर only as a historical artअगरact.  --mj, July 1998 */
	param.vc = vc = kzalloc(माप(काष्ठा vc_data), GFP_KERNEL);
	अगर (!vc)
		वापस -ENOMEM;

	vc_cons[currcons].d = vc;
	tty_port_init(&vc->port);
	vc->port.ops = &vc_port_ops;
	INIT_WORK(&vc_cons[currcons].SAK_work, vc_SAK);

	visual_init(vc, currcons, 1);

	अगर (!*vc->vc_uni_pagedir_loc)
		con_set_शेष_unimap(vc);

	err = -EINVAL;
	अगर (vc->vc_cols > VC_MAXCOL || vc->vc_rows > VC_MAXROW ||
	    vc->vc_screenbuf_size > KMALLOC_MAX_SIZE || !vc->vc_screenbuf_size)
		जाओ err_मुक्त;
	err = -ENOMEM;
	vc->vc_screenbuf = kzalloc(vc->vc_screenbuf_size, GFP_KERNEL);
	अगर (!vc->vc_screenbuf)
		जाओ err_मुक्त;

	/* If no drivers have overridden us and the user didn't pass a
	   boot option, शेष to displaying the cursor */
	अगर (global_cursor_शेष == -1)
		global_cursor_शेष = 1;

	vc_init(vc, vc->vc_rows, vc->vc_cols, 1);
	vcs_make_sysfs(currcons);
	atomic_notअगरier_call_chain(&vt_notअगरier_list, VT_ALLOCATE, &param);

	वापस 0;
err_मुक्त:
	visual_deinit(vc);
	kमुक्त(vc);
	vc_cons[currcons].d = शून्य;
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक resize_screen(काष्ठा vc_data *vc, पूर्णांक width, पूर्णांक height,
				पूर्णांक user)
अणु
	/* Resizes the resolution of the display adapater */
	पूर्णांक err = 0;

	अगर (vc->vc_sw->con_resize)
		err = vc->vc_sw->con_resize(vc, width, height, user);

	वापस err;
पूर्ण

/**
 *	vc_करो_resize	-	resizing method क्रम the tty
 *	@tty: tty being resized
 *	@vc: भव console निजी data
 *	@cols: columns
 *	@lines: lines
 *
 *	Resize a भव console, clipping according to the actual स्थिरraपूर्णांकs.
 *	If the caller passes a tty काष्ठाure then update the termios winsize
 *	inक्रमmation and perक्रमm any necessary संकेत handling.
 *
 *	Caller must hold the console semaphore. Takes the termios rwsem and
 *	ctrl_lock of the tty IFF a tty is passed.
 */

अटल पूर्णांक vc_करो_resize(काष्ठा tty_काष्ठा *tty, काष्ठा vc_data *vc,
				अचिन्हित पूर्णांक cols, अचिन्हित पूर्णांक lines)
अणु
	अचिन्हित दीर्घ old_origin, new_origin, new_scr_end, rlth, rrem, err = 0;
	अचिन्हित दीर्घ end;
	अचिन्हित पूर्णांक old_rows, old_row_size, first_copied_row;
	अचिन्हित पूर्णांक new_cols, new_rows, new_row_size, new_screen_size;
	अचिन्हित पूर्णांक user;
	अचिन्हित लघु *oldscreen, *newscreen;
	काष्ठा uni_screen *new_uniscr = शून्य;

	WARN_CONSOLE_UNLOCKED();

	अगर (!vc)
		वापस -ENXIO;

	user = vc->vc_resize_user;
	vc->vc_resize_user = 0;

	अगर (cols > VC_MAXCOL || lines > VC_MAXROW)
		वापस -EINVAL;

	new_cols = (cols ? cols : vc->vc_cols);
	new_rows = (lines ? lines : vc->vc_rows);
	new_row_size = new_cols << 1;
	new_screen_size = new_row_size * new_rows;

	अगर (new_cols == vc->vc_cols && new_rows == vc->vc_rows)
		वापस 0;

	अगर (new_screen_size > KMALLOC_MAX_SIZE || !new_screen_size)
		वापस -EINVAL;
	newscreen = kzalloc(new_screen_size, GFP_USER);
	अगर (!newscreen)
		वापस -ENOMEM;

	अगर (get_vc_uniscr(vc)) अणु
		new_uniscr = vc_uniscr_alloc(new_cols, new_rows);
		अगर (!new_uniscr) अणु
			kमुक्त(newscreen);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (vc_is_sel(vc))
		clear_selection();

	old_rows = vc->vc_rows;
	old_row_size = vc->vc_size_row;

	err = resize_screen(vc, new_cols, new_rows, user);
	अगर (err) अणु
		kमुक्त(newscreen);
		vc_uniscr_मुक्त(new_uniscr);
		वापस err;
	पूर्ण

	vc->vc_rows = new_rows;
	vc->vc_cols = new_cols;
	vc->vc_size_row = new_row_size;
	vc->vc_screenbuf_size = new_screen_size;

	rlth = min(old_row_size, new_row_size);
	rrem = new_row_size - rlth;
	old_origin = vc->vc_origin;
	new_origin = (दीर्घ) newscreen;
	new_scr_end = new_origin + new_screen_size;

	अगर (vc->state.y > new_rows) अणु
		अगर (old_rows - vc->state.y < new_rows) अणु
			/*
			 * Cursor near the bottom, copy contents from the
			 * bottom of buffer
			 */
			first_copied_row = (old_rows - new_rows);
		पूर्ण अन्यथा अणु
			/*
			 * Cursor is in no man's land, copy 1/2 screenful
			 * from the top and bottom of cursor position
			 */
			first_copied_row = (vc->state.y - new_rows/2);
		पूर्ण
		old_origin += first_copied_row * old_row_size;
	पूर्ण अन्यथा
		first_copied_row = 0;
	end = old_origin + old_row_size * min(old_rows, new_rows);

	vc_uniscr_copy_area(new_uniscr, new_cols, new_rows,
			    get_vc_uniscr(vc), rlth/2, first_copied_row,
			    min(old_rows, new_rows));
	vc_uniscr_set(vc, new_uniscr);

	update_attr(vc);

	जबतक (old_origin < end) अणु
		scr_स_नकलw((अचिन्हित लघु *) new_origin,
			    (अचिन्हित लघु *) old_origin, rlth);
		अगर (rrem)
			scr_स_रखोw((व्योम *)(new_origin + rlth),
				    vc->vc_video_erase_अक्षर, rrem);
		old_origin += old_row_size;
		new_origin += new_row_size;
	पूर्ण
	अगर (new_scr_end > new_origin)
		scr_स_रखोw((व्योम *)new_origin, vc->vc_video_erase_अक्षर,
			    new_scr_end - new_origin);
	oldscreen = vc->vc_screenbuf;
	vc->vc_screenbuf = newscreen;
	vc->vc_screenbuf_size = new_screen_size;
	set_origin(vc);
	kमुक्त(oldscreen);

	/* करो part of a reset_terminal() */
	vc->vc_top = 0;
	vc->vc_bottom = vc->vc_rows;
	जाओxy(vc, vc->state.x, vc->state.y);
	save_cur(vc);

	अगर (tty) अणु
		/* Reग_लिखो the requested winsize data with the actual
		   resulting sizes */
		काष्ठा winsize ws;
		स_रखो(&ws, 0, माप(ws));
		ws.ws_row = vc->vc_rows;
		ws.ws_col = vc->vc_cols;
		ws.ws_ypixel = vc->vc_scan_lines;
		tty_करो_resize(tty, &ws);
	पूर्ण

	अगर (con_is_visible(vc))
		update_screen(vc);
	vt_event_post(VT_EVENT_RESIZE, vc->vc_num, vc->vc_num);
	notअगरy_update(vc);
	वापस err;
पूर्ण

/**
 *	vc_resize		-	resize a VT
 *	@vc: भव console
 *	@cols: columns
 *	@rows: rows
 *
 *	Resize a भव console as seen from the console end of things. We
 *	use the common vc_करो_resize methods to update the काष्ठाures. The
 *	caller must hold the console sem to protect console पूर्णांकernals and
 *	vc->port.tty
 */

पूर्णांक vc_resize(काष्ठा vc_data *vc, अचिन्हित पूर्णांक cols, अचिन्हित पूर्णांक rows)
अणु
	वापस vc_करो_resize(vc->port.tty, vc, cols, rows);
पूर्ण

/**
 *	vt_resize		-	resize a VT
 *	@tty: tty to resize
 *	@ws: winsize attributes
 *
 *	Resize a भव terminal. This is called by the tty layer as we
 *	रेजिस्टर our own handler क्रम resizing. The mutual helper करोes all
 *	the actual work.
 *
 *	Takes the console sem and the called methods then take the tty
 *	termios_rwsem and the tty ctrl_lock in that order.
 */
अटल पूर्णांक vt_resize(काष्ठा tty_काष्ठा *tty, काष्ठा winsize *ws)
अणु
	काष्ठा vc_data *vc = tty->driver_data;
	पूर्णांक ret;

	console_lock();
	ret = vc_करो_resize(tty, vc, ws->ws_col, ws->ws_row);
	console_unlock();
	वापस ret;
पूर्ण

काष्ठा vc_data *vc_deallocate(अचिन्हित पूर्णांक currcons)
अणु
	काष्ठा vc_data *vc = शून्य;

	WARN_CONSOLE_UNLOCKED();

	अगर (vc_cons_allocated(currcons)) अणु
		काष्ठा vt_notअगरier_param param;

		param.vc = vc = vc_cons[currcons].d;
		atomic_notअगरier_call_chain(&vt_notअगरier_list, VT_DEALLOCATE, &param);
		vcs_हटाओ_sysfs(currcons);
		visual_deinit(vc);
		con_मुक्त_unimap(vc);
		put_pid(vc->vt_pid);
		vc_uniscr_set(vc, शून्य);
		kमुक्त(vc->vc_screenbuf);
		vc_cons[currcons].d = शून्य;
	पूर्ण
	वापस vc;
पूर्ण

/*
 *	VT102 emulator
 */

क्रमागत अणु EPecma = 0, EPdec, EPeq, EPgt, EPltपूर्ण;

#घोषणा set_kbd(vc, x)	vt_set_kbd_mode_bit((vc)->vc_num, (x))
#घोषणा clr_kbd(vc, x)	vt_clr_kbd_mode_bit((vc)->vc_num, (x))
#घोषणा is_kbd(vc, x)	vt_get_kbd_mode_bit((vc)->vc_num, (x))

#घोषणा decarm		VC_REPEAT
#घोषणा decckm		VC_CKMODE
#घोषणा kbdapplic	VC_APPLIC
#घोषणा lnm		VC_CRLF

स्थिर अचिन्हित अक्षर color_table[] = अणु 0, 4, 2, 6, 1, 5, 3, 7,
				       8,12,10,14, 9,13,11,15 पूर्ण;

/* the शेष colour table, क्रम VGA+ colour प्रणालीs */
अचिन्हित अक्षर शेष_red[] = अणु
	0x00, 0xaa, 0x00, 0xaa, 0x00, 0xaa, 0x00, 0xaa,
	0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff
पूर्ण;
module_param_array(शेष_red, byte, शून्य, S_IRUGO | S_IWUSR);

अचिन्हित अक्षर शेष_grn[] = अणु
	0x00, 0x00, 0xaa, 0x55, 0x00, 0x00, 0xaa, 0xaa,
	0x55, 0x55, 0xff, 0xff, 0x55, 0x55, 0xff, 0xff
पूर्ण;
module_param_array(शेष_grn, byte, शून्य, S_IRUGO | S_IWUSR);

अचिन्हित अक्षर शेष_blu[] = अणु
	0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0xaa, 0xaa,
	0x55, 0x55, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff
पूर्ण;
module_param_array(शेष_blu, byte, शून्य, S_IRUGO | S_IWUSR);

/*
 * जाओxy() must verअगरy all boundaries, because the arguments
 * might also be negative. If the given position is out of
 * bounds, the cursor is placed at the nearest margin.
 */
अटल व्योम जाओxy(काष्ठा vc_data *vc, पूर्णांक new_x, पूर्णांक new_y)
अणु
	पूर्णांक min_y, max_y;

	अगर (new_x < 0)
		vc->state.x = 0;
	अन्यथा अणु
		अगर (new_x >= vc->vc_cols)
			vc->state.x = vc->vc_cols - 1;
		अन्यथा
			vc->state.x = new_x;
	पूर्ण

 	अगर (vc->vc_decom) अणु
		min_y = vc->vc_top;
		max_y = vc->vc_bottom;
	पूर्ण अन्यथा अणु
		min_y = 0;
		max_y = vc->vc_rows;
	पूर्ण
	अगर (new_y < min_y)
		vc->state.y = min_y;
	अन्यथा अगर (new_y >= max_y)
		vc->state.y = max_y - 1;
	अन्यथा
		vc->state.y = new_y;
	vc->vc_pos = vc->vc_origin + vc->state.y * vc->vc_size_row +
		(vc->state.x << 1);
	vc->vc_need_wrap = 0;
पूर्ण

/* क्रम असलolute user moves, when decom is set */
अटल व्योम जाओxay(काष्ठा vc_data *vc, पूर्णांक new_x, पूर्णांक new_y)
अणु
	जाओxy(vc, new_x, vc->vc_decom ? (vc->vc_top + new_y) : new_y);
पूर्ण

व्योम scrollback(काष्ठा vc_data *vc)
अणु
	scrolldelta(-(vc->vc_rows / 2));
पूर्ण

व्योम scrollfront(काष्ठा vc_data *vc, पूर्णांक lines)
अणु
	अगर (!lines)
		lines = vc->vc_rows / 2;
	scrolldelta(lines);
पूर्ण

अटल व्योम lf(काष्ठा vc_data *vc)
अणु
    	/* करोn't scroll अगर above bottom of scrolling region, or
	 * अगर below scrolling region
	 */
	अगर (vc->state.y + 1 == vc->vc_bottom)
		con_scroll(vc, vc->vc_top, vc->vc_bottom, SM_UP, 1);
	अन्यथा अगर (vc->state.y < vc->vc_rows - 1) अणु
		vc->state.y++;
		vc->vc_pos += vc->vc_size_row;
	पूर्ण
	vc->vc_need_wrap = 0;
	notअगरy_ग_लिखो(vc, '\n');
पूर्ण

अटल व्योम ri(काष्ठा vc_data *vc)
अणु
    	/* करोn't scroll अगर below top of scrolling region, or
	 * अगर above scrolling region
	 */
	अगर (vc->state.y == vc->vc_top)
		con_scroll(vc, vc->vc_top, vc->vc_bottom, SM_DOWN, 1);
	अन्यथा अगर (vc->state.y > 0) अणु
		vc->state.y--;
		vc->vc_pos -= vc->vc_size_row;
	पूर्ण
	vc->vc_need_wrap = 0;
पूर्ण

अटल अंतरभूत व्योम cr(काष्ठा vc_data *vc)
अणु
	vc->vc_pos -= vc->state.x << 1;
	vc->vc_need_wrap = vc->state.x = 0;
	notअगरy_ग_लिखो(vc, '\r');
पूर्ण

अटल अंतरभूत व्योम bs(काष्ठा vc_data *vc)
अणु
	अगर (vc->state.x) अणु
		vc->vc_pos -= 2;
		vc->state.x--;
		vc->vc_need_wrap = 0;
		notअगरy_ग_लिखो(vc, '\b');
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम del(काष्ठा vc_data *vc)
अणु
	/* ignored */
पूर्ण

अटल व्योम csi_J(काष्ठा vc_data *vc, पूर्णांक vpar)
अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित लघु * start;

	चयन (vpar) अणु
		हाल 0:	/* erase from cursor to end of display */
			vc_uniscr_clear_line(vc, vc->state.x,
					     vc->vc_cols - vc->state.x);
			vc_uniscr_clear_lines(vc, vc->state.y + 1,
					      vc->vc_rows - vc->state.y - 1);
			count = (vc->vc_scr_end - vc->vc_pos) >> 1;
			start = (अचिन्हित लघु *)vc->vc_pos;
			अवरोध;
		हाल 1:	/* erase from start to cursor */
			vc_uniscr_clear_line(vc, 0, vc->state.x + 1);
			vc_uniscr_clear_lines(vc, 0, vc->state.y);
			count = ((vc->vc_pos - vc->vc_origin) >> 1) + 1;
			start = (अचिन्हित लघु *)vc->vc_origin;
			अवरोध;
		हाल 3: /* include scrollback */
			flush_scrollback(vc);
			fallthrough;
		हाल 2: /* erase whole display */
			vc_uniscr_clear_lines(vc, 0, vc->vc_rows);
			count = vc->vc_cols * vc->vc_rows;
			start = (अचिन्हित लघु *)vc->vc_origin;
			अवरोध;
		शेष:
			वापस;
	पूर्ण
	scr_स_रखोw(start, vc->vc_video_erase_अक्षर, 2 * count);
	अगर (con_should_update(vc))
		करो_update_region(vc, (अचिन्हित दीर्घ) start, count);
	vc->vc_need_wrap = 0;
पूर्ण

अटल व्योम csi_K(काष्ठा vc_data *vc, पूर्णांक vpar)
अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित लघु *start = (अचिन्हित लघु *)vc->vc_pos;
	पूर्णांक offset;

	चयन (vpar) अणु
		हाल 0:	/* erase from cursor to end of line */
			offset = 0;
			count = vc->vc_cols - vc->state.x;
			अवरोध;
		हाल 1:	/* erase from start of line to cursor */
			offset = -vc->state.x;
			count = vc->state.x + 1;
			अवरोध;
		हाल 2: /* erase whole line */
			offset = -vc->state.x;
			count = vc->vc_cols;
			अवरोध;
		शेष:
			वापस;
	पूर्ण
	vc_uniscr_clear_line(vc, vc->state.x + offset, count);
	scr_स_रखोw(start + offset, vc->vc_video_erase_अक्षर, 2 * count);
	vc->vc_need_wrap = 0;
	अगर (con_should_update(vc))
		करो_update_region(vc, (अचिन्हित दीर्घ)(start + offset), count);
पूर्ण

/* erase the following vpar positions */
अटल व्योम csi_X(काष्ठा vc_data *vc, अचिन्हित पूर्णांक vpar)
अणु					  /* not vt100? */
	अचिन्हित पूर्णांक count;

	अगर (!vpar)
		vpar++;

	count = min(vpar, vc->vc_cols - vc->state.x);

	vc_uniscr_clear_line(vc, vc->state.x, count);
	scr_स_रखोw((अचिन्हित लघु *)vc->vc_pos, vc->vc_video_erase_अक्षर, 2 * count);
	अगर (con_should_update(vc))
		vc->vc_sw->con_clear(vc, vc->state.y, vc->state.x, 1, count);
	vc->vc_need_wrap = 0;
पूर्ण

अटल व्योम शेष_attr(काष्ठा vc_data *vc)
अणु
	vc->state.पूर्णांकensity = VCI_NORMAL;
	vc->state.italic = false;
	vc->state.underline = false;
	vc->state.reverse = false;
	vc->state.blink = false;
	vc->state.color = vc->vc_def_color;
पूर्ण

काष्ठा rgb अणु u8 r; u8 g; u8 b; पूर्ण;

अटल व्योम rgb_from_256(पूर्णांक i, काष्ठा rgb *c)
अणु
	अगर (i < 8) अणु            /* Standard colours. */
		c->r = i&1 ? 0xaa : 0x00;
		c->g = i&2 ? 0xaa : 0x00;
		c->b = i&4 ? 0xaa : 0x00;
	पूर्ण अन्यथा अगर (i < 16) अणु
		c->r = i&1 ? 0xff : 0x55;
		c->g = i&2 ? 0xff : 0x55;
		c->b = i&4 ? 0xff : 0x55;
	पूर्ण अन्यथा अगर (i < 232) अणु   /* 6x6x6 colour cube. */
		c->r = (i - 16) / 36 * 85 / 2;
		c->g = (i - 16) / 6 % 6 * 85 / 2;
		c->b = (i - 16) % 6 * 85 / 2;
	पूर्ण अन्यथा                  /* Grayscale ramp. */
		c->r = c->g = c->b = i * 10 - 2312;
पूर्ण

अटल व्योम rgb_क्रमeground(काष्ठा vc_data *vc, स्थिर काष्ठा rgb *c)
अणु
	u8 hue = 0, max = max3(c->r, c->g, c->b);

	अगर (c->r > max / 2)
		hue |= 4;
	अगर (c->g > max / 2)
		hue |= 2;
	अगर (c->b > max / 2)
		hue |= 1;

	अगर (hue == 7 && max <= 0x55) अणु
		hue = 0;
		vc->state.पूर्णांकensity = VCI_BOLD;
	पूर्ण अन्यथा अगर (max > 0xaa)
		vc->state.पूर्णांकensity = VCI_BOLD;
	अन्यथा
		vc->state.पूर्णांकensity = VCI_NORMAL;

	vc->state.color = (vc->state.color & 0xf0) | hue;
पूर्ण

अटल व्योम rgb_background(काष्ठा vc_data *vc, स्थिर काष्ठा rgb *c)
अणु
	/* For backgrounds, err on the dark side. */
	vc->state.color = (vc->state.color & 0x0f)
		| (c->r&0x80) >> 1 | (c->g&0x80) >> 2 | (c->b&0x80) >> 3;
पूर्ण

/*
 * ITU T.416 Higher colour modes. They अवरोध the usual properties of SGR codes
 * and thus need to be detected and ignored by hand. That standard also
 * wants : rather than ; as separators but sequences containing : are currently
 * completely ignored by the parser.
 *
 * Subcommands 3 (CMY) and 4 (CMYK) are so insane there's no poपूर्णांक in
 * supporting them.
 */
अटल पूर्णांक vc_t416_color(काष्ठा vc_data *vc, पूर्णांक i,
		व्योम(*set_color)(काष्ठा vc_data *vc, स्थिर काष्ठा rgb *c))
अणु
	काष्ठा rgb c;

	i++;
	अगर (i > vc->vc_npar)
		वापस i;

	अगर (vc->vc_par[i] == 5 && i + 1 <= vc->vc_npar) अणु
		/* 256 colours */
		i++;
		rgb_from_256(vc->vc_par[i], &c);
	पूर्ण अन्यथा अगर (vc->vc_par[i] == 2 && i + 3 <= vc->vc_npar) अणु
		/* 24 bit */
		c.r = vc->vc_par[i + 1];
		c.g = vc->vc_par[i + 2];
		c.b = vc->vc_par[i + 3];
		i += 3;
	पूर्ण अन्यथा
		वापस i;

	set_color(vc, &c);

	वापस i;
पूर्ण

/* console_lock is held */
अटल व्योम csi_m(काष्ठा vc_data *vc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= vc->vc_npar; i++)
		चयन (vc->vc_par[i]) अणु
		हाल 0:	/* all attributes off */
			शेष_attr(vc);
			अवरोध;
		हाल 1:
			vc->state.पूर्णांकensity = VCI_BOLD;
			अवरोध;
		हाल 2:
			vc->state.पूर्णांकensity = VCI_HALF_BRIGHT;
			अवरोध;
		हाल 3:
			vc->state.italic = true;
			अवरोध;
		हाल 21:
			/*
			 * No console drivers support द्विगुन underline, so
			 * convert it to a single underline.
			 */
		हाल 4:
			vc->state.underline = true;
			अवरोध;
		हाल 5:
			vc->state.blink = true;
			अवरोध;
		हाल 7:
			vc->state.reverse = true;
			अवरोध;
		हाल 10: /* ANSI X3.64-1979 (SCO-ish?)
			  * Select primary font, करोn't display control अक्षरs अगर
			  * defined, करोn't set bit 8 on output.
			  */
			vc->vc_translate = set_translate(vc->state.Gx_अक्षरset[vc->state.अक्षरset], vc);
			vc->vc_disp_ctrl = 0;
			vc->vc_toggle_meta = 0;
			अवरोध;
		हाल 11: /* ANSI X3.64-1979 (SCO-ish?)
			  * Select first alternate font, lets अक्षरs < 32 be
			  * displayed as ROM अक्षरs.
			  */
			vc->vc_translate = set_translate(IBMPC_MAP, vc);
			vc->vc_disp_ctrl = 1;
			vc->vc_toggle_meta = 0;
			अवरोध;
		हाल 12: /* ANSI X3.64-1979 (SCO-ish?)
			  * Select second alternate font, toggle high bit
			  * beक्रमe displaying as ROM अक्षर.
			  */
			vc->vc_translate = set_translate(IBMPC_MAP, vc);
			vc->vc_disp_ctrl = 1;
			vc->vc_toggle_meta = 1;
			अवरोध;
		हाल 22:
			vc->state.पूर्णांकensity = VCI_NORMAL;
			अवरोध;
		हाल 23:
			vc->state.italic = false;
			अवरोध;
		हाल 24:
			vc->state.underline = false;
			अवरोध;
		हाल 25:
			vc->state.blink = false;
			अवरोध;
		हाल 27:
			vc->state.reverse = false;
			अवरोध;
		हाल 38:
			i = vc_t416_color(vc, i, rgb_क्रमeground);
			अवरोध;
		हाल 48:
			i = vc_t416_color(vc, i, rgb_background);
			अवरोध;
		हाल 39:
			vc->state.color = (vc->vc_def_color & 0x0f) |
				(vc->state.color & 0xf0);
			अवरोध;
		हाल 49:
			vc->state.color = (vc->vc_def_color & 0xf0) |
				(vc->state.color & 0x0f);
			अवरोध;
		शेष:
			अगर (vc->vc_par[i] >= 90 && vc->vc_par[i] <= 107) अणु
				अगर (vc->vc_par[i] < 100)
					vc->state.पूर्णांकensity = VCI_BOLD;
				vc->vc_par[i] -= 60;
			पूर्ण
			अगर (vc->vc_par[i] >= 30 && vc->vc_par[i] <= 37)
				vc->state.color = color_table[vc->vc_par[i] - 30]
					| (vc->state.color & 0xf0);
			अन्यथा अगर (vc->vc_par[i] >= 40 && vc->vc_par[i] <= 47)
				vc->state.color = (color_table[vc->vc_par[i] - 40] << 4)
					| (vc->state.color & 0x0f);
			अवरोध;
		पूर्ण
	update_attr(vc);
पूर्ण

अटल व्योम respond_string(स्थिर अक्षर *p, माप_प्रकार len, काष्ठा tty_port *port)
अणु
	tty_insert_flip_string(port, p, len);
	tty_schedule_flip(port);
पूर्ण

अटल व्योम cursor_report(काष्ठा vc_data *vc, काष्ठा tty_काष्ठा *tty)
अणु
	अक्षर buf[40];
	पूर्णांक len;

	len = प्र_लिखो(buf, "\033[%d;%dR", vc->state.y +
			(vc->vc_decom ? vc->vc_top + 1 : 1),
			vc->state.x + 1);
	respond_string(buf, len, tty->port);
पूर्ण

अटल अंतरभूत व्योम status_report(काष्ठा tty_काष्ठा *tty)
अणु
	अटल स्थिर अक्षर teminal_ok[] = "\033[0n";

	respond_string(teminal_ok, म_माप(teminal_ok), tty->port);
पूर्ण

अटल अंतरभूत व्योम respond_ID(काष्ठा tty_काष्ठा *tty)
अणु
	/* terminal answer to an ESC-Z or csi0c query. */
	अटल स्थिर अक्षर vt102_id[] = "\033[?6c";

	respond_string(vt102_id, म_माप(vt102_id), tty->port);
पूर्ण

व्योम mouse_report(काष्ठा tty_काष्ठा *tty, पूर्णांक butt, पूर्णांक mrx, पूर्णांक mry)
अणु
	अक्षर buf[8];
	पूर्णांक len;

	len = प्र_लिखो(buf, "\033[M%c%c%c", (अक्षर)(' ' + butt),
			(अक्षर)('!' + mrx), (char)('!' + mry));
	respond_string(buf, len, tty->port);
पूर्ण

/* invoked via ioctl(TIOCLINUX) and through set_selection_user */
पूर्णांक mouse_reporting(व्योम)
अणु
	वापस vc_cons[fg_console].d->vc_report_mouse;
पूर्ण

/* console_lock is held */
अटल व्योम set_mode(काष्ठा vc_data *vc, पूर्णांक on_off)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= vc->vc_npar; i++)
		अगर (vc->vc_priv == EPdec) अणु
			चयन(vc->vc_par[i]) अणु	/* DEC निजी modes set/reset */
			हाल 1:			/* Cursor keys send ^[Ox/^[[x */
				अगर (on_off)
					set_kbd(vc, decckm);
				अन्यथा
					clr_kbd(vc, decckm);
				अवरोध;
			हाल 3:	/* 80/132 mode चयन unimplemented */
#अगर 0
				vc_resize(deccolm ? 132 : 80, vc->vc_rows);
				/* this alone करोes not suffice; some user mode
				   utility has to change the hardware regs */
#पूर्ण_अगर
				अवरोध;
			हाल 5:			/* Inverted screen on/off */
				अगर (vc->vc_decscnm != on_off) अणु
					vc->vc_decscnm = on_off;
					invert_screen(vc, 0,
							vc->vc_screenbuf_size,
							false);
					update_attr(vc);
				पूर्ण
				अवरोध;
			हाल 6:			/* Origin relative/असलolute */
				vc->vc_decom = on_off;
				जाओxay(vc, 0, 0);
				अवरोध;
			हाल 7:			/* Autowrap on/off */
				vc->vc_decawm = on_off;
				अवरोध;
			हाल 8:			/* Autorepeat on/off */
				अगर (on_off)
					set_kbd(vc, decarm);
				अन्यथा
					clr_kbd(vc, decarm);
				अवरोध;
			हाल 9:
				vc->vc_report_mouse = on_off ? 1 : 0;
				अवरोध;
			हाल 25:		/* Cursor on/off */
				vc->vc_deccm = on_off;
				अवरोध;
			हाल 1000:
				vc->vc_report_mouse = on_off ? 2 : 0;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन(vc->vc_par[i]) अणु	/* ANSI modes set/reset */
			हाल 3:			/* Monitor (display ctrls) */
				vc->vc_disp_ctrl = on_off;
				अवरोध;
			हाल 4:			/* Insert Mode on/off */
				vc->vc_decim = on_off;
				अवरोध;
			हाल 20:		/* Lf, Enter == CrLf/Lf */
				अगर (on_off)
					set_kbd(vc, lnm);
				अन्यथा
					clr_kbd(vc, lnm);
				अवरोध;
			पूर्ण
		पूर्ण
पूर्ण

/* console_lock is held */
अटल व्योम setterm_command(काष्ठा vc_data *vc)
अणु
	चयन (vc->vc_par[0]) अणु
	हाल 1:	/* set color क्रम underline mode */
		अगर (vc->vc_can_करो_color && vc->vc_par[1] < 16) अणु
			vc->vc_ulcolor = color_table[vc->vc_par[1]];
			अगर (vc->state.underline)
				update_attr(vc);
		पूर्ण
		अवरोध;
	हाल 2:	/* set color क्रम half पूर्णांकensity mode */
		अगर (vc->vc_can_करो_color && vc->vc_par[1] < 16) अणु
			vc->vc_halfcolor = color_table[vc->vc_par[1]];
			अगर (vc->state.पूर्णांकensity == VCI_HALF_BRIGHT)
				update_attr(vc);
		पूर्ण
		अवरोध;
	हाल 8:	/* store colors as शेषs */
		vc->vc_def_color = vc->vc_attr;
		अगर (vc->vc_hi_font_mask == 0x100)
			vc->vc_def_color >>= 1;
		शेष_attr(vc);
		update_attr(vc);
		अवरोध;
	हाल 9:	/* set blanking पूर्णांकerval */
		blankपूर्णांकerval = min(vc->vc_par[1], 60U) * 60;
		poke_blanked_console();
		अवरोध;
	हाल 10: /* set bell frequency in Hz */
		अगर (vc->vc_npar >= 1)
			vc->vc_bell_pitch = vc->vc_par[1];
		अन्यथा
			vc->vc_bell_pitch = DEFAULT_BELL_PITCH;
		अवरोध;
	हाल 11: /* set bell duration in msec */
		अगर (vc->vc_npar >= 1)
			vc->vc_bell_duration = (vc->vc_par[1] < 2000) ?
				msecs_to_jअगरfies(vc->vc_par[1]) : 0;
		अन्यथा
			vc->vc_bell_duration = DEFAULT_BELL_DURATION;
		अवरोध;
	हाल 12: /* bring specअगरied console to the front */
		अगर (vc->vc_par[1] >= 1 && vc_cons_allocated(vc->vc_par[1] - 1))
			set_console(vc->vc_par[1] - 1);
		अवरोध;
	हाल 13: /* unblank the screen */
		poke_blanked_console();
		अवरोध;
	हाल 14: /* set vesa घातerकरोwn पूर्णांकerval */
		vesa_off_पूर्णांकerval = min(vc->vc_par[1], 60U) * 60 * HZ;
		अवरोध;
	हाल 15: /* activate the previous console */
		set_console(last_console);
		अवरोध;
	हाल 16: /* set cursor blink duration in msec */
		अगर (vc->vc_npar >= 1 && vc->vc_par[1] >= 50 &&
				vc->vc_par[1] <= अच_लघु_उच्च)
			vc->vc_cur_blink_ms = vc->vc_par[1];
		अन्यथा
			vc->vc_cur_blink_ms = DEFAULT_CURSOR_BLINK_MS;
		अवरोध;
	पूर्ण
पूर्ण

/* console_lock is held */
अटल व्योम csi_at(काष्ठा vc_data *vc, अचिन्हित पूर्णांक nr)
अणु
	अगर (nr > vc->vc_cols - vc->state.x)
		nr = vc->vc_cols - vc->state.x;
	अन्यथा अगर (!nr)
		nr = 1;
	insert_अक्षर(vc, nr);
पूर्ण

/* console_lock is held */
अटल व्योम csi_L(काष्ठा vc_data *vc, अचिन्हित पूर्णांक nr)
अणु
	अगर (nr > vc->vc_rows - vc->state.y)
		nr = vc->vc_rows - vc->state.y;
	अन्यथा अगर (!nr)
		nr = 1;
	con_scroll(vc, vc->state.y, vc->vc_bottom, SM_DOWN, nr);
	vc->vc_need_wrap = 0;
पूर्ण

/* console_lock is held */
अटल व्योम csi_P(काष्ठा vc_data *vc, अचिन्हित पूर्णांक nr)
अणु
	अगर (nr > vc->vc_cols - vc->state.x)
		nr = vc->vc_cols - vc->state.x;
	अन्यथा अगर (!nr)
		nr = 1;
	delete_अक्षर(vc, nr);
पूर्ण

/* console_lock is held */
अटल व्योम csi_M(काष्ठा vc_data *vc, अचिन्हित पूर्णांक nr)
अणु
	अगर (nr > vc->vc_rows - vc->state.y)
		nr = vc->vc_rows - vc->state.y;
	अन्यथा अगर (!nr)
		nr=1;
	con_scroll(vc, vc->state.y, vc->vc_bottom, SM_UP, nr);
	vc->vc_need_wrap = 0;
पूर्ण

/* console_lock is held (except via vc_init->reset_terminal */
अटल व्योम save_cur(काष्ठा vc_data *vc)
अणु
	स_नकल(&vc->saved_state, &vc->state, माप(vc->state));
पूर्ण

/* console_lock is held */
अटल व्योम restore_cur(काष्ठा vc_data *vc)
अणु
	स_नकल(&vc->state, &vc->saved_state, माप(vc->state));

	जाओxy(vc, vc->state.x, vc->state.y);
	vc->vc_translate = set_translate(vc->state.Gx_अक्षरset[vc->state.अक्षरset],
			vc);
	update_attr(vc);
	vc->vc_need_wrap = 0;
पूर्ण

क्रमागत अणु ESnormal, ESesc, ESsquare, ESgetpars, ESfunckey,
	EShash, ESsetG0, ESsetG1, ESpercent, EScsiignore, ESnonstd,
	ESpalette, ESosc पूर्ण;

/* console_lock is held (except via vc_init()) */
अटल व्योम reset_terminal(काष्ठा vc_data *vc, पूर्णांक करो_clear)
अणु
	अचिन्हित पूर्णांक i;

	vc->vc_top		= 0;
	vc->vc_bottom		= vc->vc_rows;
	vc->vc_state		= ESnormal;
	vc->vc_priv		= EPecma;
	vc->vc_translate	= set_translate(LAT1_MAP, vc);
	vc->state.Gx_अक्षरset[0]	= LAT1_MAP;
	vc->state.Gx_अक्षरset[1]	= GRAF_MAP;
	vc->state.अक्षरset	= 0;
	vc->vc_need_wrap	= 0;
	vc->vc_report_mouse	= 0;
	vc->vc_utf              = शेष_utf8;
	vc->vc_utf_count	= 0;

	vc->vc_disp_ctrl	= 0;
	vc->vc_toggle_meta	= 0;

	vc->vc_decscnm		= 0;
	vc->vc_decom		= 0;
	vc->vc_decawm		= 1;
	vc->vc_deccm		= global_cursor_शेष;
	vc->vc_decim		= 0;

	vt_reset_keyboard(vc->vc_num);

	vc->vc_cursor_type = cur_शेष;
	vc->vc_complement_mask = vc->vc_s_complement_mask;

	शेष_attr(vc);
	update_attr(vc);

	biपंचांगap_zero(vc->vc_tab_stop, VC_TABSTOPS_COUNT);
	क्रम (i = 0; i < VC_TABSTOPS_COUNT; i += 8)
		set_bit(i, vc->vc_tab_stop);

	vc->vc_bell_pitch = DEFAULT_BELL_PITCH;
	vc->vc_bell_duration = DEFAULT_BELL_DURATION;
	vc->vc_cur_blink_ms = DEFAULT_CURSOR_BLINK_MS;

	जाओxy(vc, 0, 0);
	save_cur(vc);
	अगर (करो_clear)
	    csi_J(vc, 2);
पूर्ण

अटल व्योम vc_setGx(काष्ठा vc_data *vc, अचिन्हित पूर्णांक which, पूर्णांक c)
अणु
	अचिन्हित अक्षर *अक्षरset = &vc->state.Gx_अक्षरset[which];

	चयन (c) अणु
	हाल '0':
		*अक्षरset = GRAF_MAP;
		अवरोध;
	हाल 'B':
		*अक्षरset = LAT1_MAP;
		अवरोध;
	हाल 'U':
		*अक्षरset = IBMPC_MAP;
		अवरोध;
	हाल 'K':
		*अक्षरset = USER_MAP;
		अवरोध;
	पूर्ण

	अगर (vc->state.अक्षरset == which)
		vc->vc_translate = set_translate(*अक्षरset, vc);
पूर्ण

/* console_lock is held */
अटल व्योम करो_con_trol(काष्ठा tty_काष्ठा *tty, काष्ठा vc_data *vc, पूर्णांक c)
अणु
	/*
	 *  Control अक्षरacters can be used in the _middle_
	 *  of an escape sequence.
	 */
	अगर (vc->vc_state == ESosc && c>=8 && c<=13) /* ... except क्रम OSC */
		वापस;
	चयन (c) अणु
	हाल 0:
		वापस;
	हाल 7:
		अगर (vc->vc_state == ESosc)
			vc->vc_state = ESnormal;
		अन्यथा अगर (vc->vc_bell_duration)
			kd_mksound(vc->vc_bell_pitch, vc->vc_bell_duration);
		वापस;
	हाल 8:
		bs(vc);
		वापस;
	हाल 9:
		vc->vc_pos -= (vc->state.x << 1);

		vc->state.x = find_next_bit(vc->vc_tab_stop,
				min(vc->vc_cols - 1, VC_TABSTOPS_COUNT),
				vc->state.x + 1);
		अगर (vc->state.x >= VC_TABSTOPS_COUNT)
			vc->state.x = vc->vc_cols - 1;

		vc->vc_pos += (vc->state.x << 1);
		notअगरy_ग_लिखो(vc, '\t');
		वापस;
	हाल 10: हाल 11: हाल 12:
		lf(vc);
		अगर (!is_kbd(vc, lnm))
			वापस;
		fallthrough;
	हाल 13:
		cr(vc);
		वापस;
	हाल 14:
		vc->state.अक्षरset = 1;
		vc->vc_translate = set_translate(vc->state.Gx_अक्षरset[1], vc);
		vc->vc_disp_ctrl = 1;
		वापस;
	हाल 15:
		vc->state.अक्षरset = 0;
		vc->vc_translate = set_translate(vc->state.Gx_अक्षरset[0], vc);
		vc->vc_disp_ctrl = 0;
		वापस;
	हाल 24: हाल 26:
		vc->vc_state = ESnormal;
		वापस;
	हाल 27:
		vc->vc_state = ESesc;
		वापस;
	हाल 127:
		del(vc);
		वापस;
	हाल 128+27:
		vc->vc_state = ESsquare;
		वापस;
	पूर्ण
	चयन(vc->vc_state) अणु
	हाल ESesc:
		vc->vc_state = ESnormal;
		चयन (c) अणु
		हाल '[':
			vc->vc_state = ESsquare;
			वापस;
		हाल ']':
			vc->vc_state = ESnonstd;
			वापस;
		हाल '%':
			vc->vc_state = ESpercent;
			वापस;
		हाल 'E':
			cr(vc);
			lf(vc);
			वापस;
		हाल 'M':
			ri(vc);
			वापस;
		हाल 'D':
			lf(vc);
			वापस;
		हाल 'H':
			अगर (vc->state.x < VC_TABSTOPS_COUNT)
				set_bit(vc->state.x, vc->vc_tab_stop);
			वापस;
		हाल 'Z':
			respond_ID(tty);
			वापस;
		हाल '7':
			save_cur(vc);
			वापस;
		हाल '8':
			restore_cur(vc);
			वापस;
		हाल '(':
			vc->vc_state = ESsetG0;
			वापस;
		हाल ')':
			vc->vc_state = ESsetG1;
			वापस;
		हाल '#':
			vc->vc_state = EShash;
			वापस;
		हाल 'c':
			reset_terminal(vc, 1);
			वापस;
		हाल '>':  /* Numeric keypad */
			clr_kbd(vc, kbdapplic);
			वापस;
		हाल '=':  /* Appl. keypad */
			set_kbd(vc, kbdapplic);
			वापस;
		पूर्ण
		वापस;
	हाल ESnonstd:
		अगर (c=='P') अणु   /* palette escape sequence */
			क्रम (vc->vc_npar = 0; vc->vc_npar < NPAR; vc->vc_npar++)
				vc->vc_par[vc->vc_npar] = 0;
			vc->vc_npar = 0;
			vc->vc_state = ESpalette;
			वापस;
		पूर्ण अन्यथा अगर (c=='R') अणु   /* reset palette */
			reset_palette(vc);
			vc->vc_state = ESnormal;
		पूर्ण अन्यथा अगर (c>='0' && c<='9')
			vc->vc_state = ESosc;
		अन्यथा
			vc->vc_state = ESnormal;
		वापस;
	हाल ESpalette:
		अगर (है_षष्ठादशक(c)) अणु
			vc->vc_par[vc->vc_npar++] = hex_to_bin(c);
			अगर (vc->vc_npar == 7) अणु
				पूर्णांक i = vc->vc_par[0] * 3, j = 1;
				vc->vc_palette[i] = 16 * vc->vc_par[j++];
				vc->vc_palette[i++] += vc->vc_par[j++];
				vc->vc_palette[i] = 16 * vc->vc_par[j++];
				vc->vc_palette[i++] += vc->vc_par[j++];
				vc->vc_palette[i] = 16 * vc->vc_par[j++];
				vc->vc_palette[i] += vc->vc_par[j];
				set_palette(vc);
				vc->vc_state = ESnormal;
			पूर्ण
		पूर्ण अन्यथा
			vc->vc_state = ESnormal;
		वापस;
	हाल ESsquare:
		क्रम (vc->vc_npar = 0; vc->vc_npar < NPAR; vc->vc_npar++)
			vc->vc_par[vc->vc_npar] = 0;
		vc->vc_npar = 0;
		vc->vc_state = ESgetpars;
		अगर (c == '[') अणु /* Function key */
			vc->vc_state=ESfunckey;
			वापस;
		पूर्ण
		चयन (c) अणु
		हाल '?':
			vc->vc_priv = EPdec;
			वापस;
		हाल '>':
			vc->vc_priv = EPgt;
			वापस;
		हाल '=':
			vc->vc_priv = EPeq;
			वापस;
		हाल '<':
			vc->vc_priv = EPlt;
			वापस;
		पूर्ण
		vc->vc_priv = EPecma;
		fallthrough;
	हाल ESgetpars:
		अगर (c == ';' && vc->vc_npar < NPAR - 1) अणु
			vc->vc_npar++;
			वापस;
		पूर्ण अन्यथा अगर (c>='0' && c<='9') अणु
			vc->vc_par[vc->vc_npar] *= 10;
			vc->vc_par[vc->vc_npar] += c - '0';
			वापस;
		पूर्ण
		अगर (c >= 0x20 && c <= 0x3f) अणु /* 0x2x, 0x3a and 0x3c - 0x3f */
			vc->vc_state = EScsiignore;
			वापस;
		पूर्ण
		vc->vc_state = ESnormal;
		चयन(c) अणु
		हाल 'h':
			अगर (vc->vc_priv <= EPdec)
				set_mode(vc, 1);
			वापस;
		हाल 'l':
			अगर (vc->vc_priv <= EPdec)
				set_mode(vc, 0);
			वापस;
		हाल 'c':
			अगर (vc->vc_priv == EPdec) अणु
				अगर (vc->vc_par[0])
					vc->vc_cursor_type =
						CUR_MAKE(vc->vc_par[0],
							 vc->vc_par[1],
							 vc->vc_par[2]);
				अन्यथा
					vc->vc_cursor_type = cur_शेष;
				वापस;
			पूर्ण
			अवरोध;
		हाल 'm':
			अगर (vc->vc_priv == EPdec) अणु
				clear_selection();
				अगर (vc->vc_par[0])
					vc->vc_complement_mask = vc->vc_par[0] << 8 | vc->vc_par[1];
				अन्यथा
					vc->vc_complement_mask = vc->vc_s_complement_mask;
				वापस;
			पूर्ण
			अवरोध;
		हाल 'n':
			अगर (vc->vc_priv == EPecma) अणु
				अगर (vc->vc_par[0] == 5)
					status_report(tty);
				अन्यथा अगर (vc->vc_par[0] == 6)
					cursor_report(vc, tty);
			पूर्ण
			वापस;
		पूर्ण
		अगर (vc->vc_priv != EPecma) अणु
			vc->vc_priv = EPecma;
			वापस;
		पूर्ण
		चयन(c) अणु
		हाल 'G': case '`':
			अगर (vc->vc_par[0])
				vc->vc_par[0]--;
			जाओxy(vc, vc->vc_par[0], vc->state.y);
			वापस;
		हाल 'A':
			अगर (!vc->vc_par[0])
				vc->vc_par[0]++;
			जाओxy(vc, vc->state.x, vc->state.y - vc->vc_par[0]);
			वापस;
		हाल 'B': case 'e':
			अगर (!vc->vc_par[0])
				vc->vc_par[0]++;
			जाओxy(vc, vc->state.x, vc->state.y + vc->vc_par[0]);
			वापस;
		हाल 'C': case 'a':
			अगर (!vc->vc_par[0])
				vc->vc_par[0]++;
			जाओxy(vc, vc->state.x + vc->vc_par[0], vc->state.y);
			वापस;
		हाल 'D':
			अगर (!vc->vc_par[0])
				vc->vc_par[0]++;
			जाओxy(vc, vc->state.x - vc->vc_par[0], vc->state.y);
			वापस;
		हाल 'E':
			अगर (!vc->vc_par[0])
				vc->vc_par[0]++;
			जाओxy(vc, 0, vc->state.y + vc->vc_par[0]);
			वापस;
		हाल 'F':
			अगर (!vc->vc_par[0])
				vc->vc_par[0]++;
			जाओxy(vc, 0, vc->state.y - vc->vc_par[0]);
			वापस;
		हाल 'd':
			अगर (vc->vc_par[0])
				vc->vc_par[0]--;
			जाओxay(vc, vc->state.x ,vc->vc_par[0]);
			वापस;
		हाल 'H': case 'f':
			अगर (vc->vc_par[0])
				vc->vc_par[0]--;
			अगर (vc->vc_par[1])
				vc->vc_par[1]--;
			जाओxay(vc, vc->vc_par[1], vc->vc_par[0]);
			वापस;
		हाल 'J':
			csi_J(vc, vc->vc_par[0]);
			वापस;
		हाल 'K':
			csi_K(vc, vc->vc_par[0]);
			वापस;
		हाल 'L':
			csi_L(vc, vc->vc_par[0]);
			वापस;
		हाल 'M':
			csi_M(vc, vc->vc_par[0]);
			वापस;
		हाल 'P':
			csi_P(vc, vc->vc_par[0]);
			वापस;
		हाल 'c':
			अगर (!vc->vc_par[0])
				respond_ID(tty);
			वापस;
		हाल 'g':
			अगर (!vc->vc_par[0] && vc->state.x < VC_TABSTOPS_COUNT)
				set_bit(vc->state.x, vc->vc_tab_stop);
			अन्यथा अगर (vc->vc_par[0] == 3)
				biपंचांगap_zero(vc->vc_tab_stop, VC_TABSTOPS_COUNT);
			वापस;
		हाल 'm':
			csi_m(vc);
			वापस;
		हाल 'q': /* DECLL - but only 3 leds */
			/* map 0,1,2,3 to 0,1,2,4 */
			अगर (vc->vc_par[0] < 4)
				vt_set_led_state(vc->vc_num,
					    (vc->vc_par[0] < 3) ? vc->vc_par[0] : 4);
			वापस;
		हाल 'r':
			अगर (!vc->vc_par[0])
				vc->vc_par[0]++;
			अगर (!vc->vc_par[1])
				vc->vc_par[1] = vc->vc_rows;
			/* Minimum allowed region is 2 lines */
			अगर (vc->vc_par[0] < vc->vc_par[1] &&
			    vc->vc_par[1] <= vc->vc_rows) अणु
				vc->vc_top = vc->vc_par[0] - 1;
				vc->vc_bottom = vc->vc_par[1];
				जाओxay(vc, 0, 0);
			पूर्ण
			वापस;
		हाल 's':
			save_cur(vc);
			वापस;
		हाल 'u':
			restore_cur(vc);
			वापस;
		हाल 'X':
			csi_X(vc, vc->vc_par[0]);
			वापस;
		हाल '@':
			csi_at(vc, vc->vc_par[0]);
			वापस;
		हाल ']': /* setterm functions */
			setterm_command(vc);
			वापस;
		पूर्ण
		वापस;
	हाल EScsiignore:
		अगर (c >= 20 && c <= 0x3f)
			वापस;
		vc->vc_state = ESnormal;
		वापस;
	हाल ESpercent:
		vc->vc_state = ESnormal;
		चयन (c) अणु
		हाल '@':  /* defined in ISO 2022 */
			vc->vc_utf = 0;
			वापस;
		हाल 'G':  /* prelim official escape code */
		हाल '8':  /* retained क्रम compatibility */
			vc->vc_utf = 1;
			वापस;
		पूर्ण
		वापस;
	हाल ESfunckey:
		vc->vc_state = ESnormal;
		वापस;
	हाल EShash:
		vc->vc_state = ESnormal;
		अगर (c == '8') अणु
			/* DEC screen alignment test. kludge :-) */
			vc->vc_video_erase_अक्षर =
				(vc->vc_video_erase_अक्षर & 0xff00) | 'E';
			csi_J(vc, 2);
			vc->vc_video_erase_अक्षर =
				(vc->vc_video_erase_अक्षर & 0xff00) | ' ';
			करो_update_region(vc, vc->vc_origin, vc->vc_screenbuf_size / 2);
		पूर्ण
		वापस;
	हाल ESsetG0:
		vc_setGx(vc, 0, c);
		vc->vc_state = ESnormal;
		वापस;
	हाल ESsetG1:
		vc_setGx(vc, 1, c);
		vc->vc_state = ESnormal;
		वापस;
	हाल ESosc:
		वापस;
	शेष:
		vc->vc_state = ESnormal;
	पूर्ण
पूर्ण

/* is_द्विगुन_width() is based on the wcwidth() implementation by
 * Markus Kuhn -- 2007-05-26 (Unicode 5.0)
 * Latest version: https://www.cl.cam.ac.uk/~mgk25/ucs/wcwidth.c
 */
काष्ठा पूर्णांकerval अणु
	uपूर्णांक32_t first;
	uपूर्णांक32_t last;
पूर्ण;

अटल पूर्णांक ucs_cmp(स्थिर व्योम *key, स्थिर व्योम *elt)
अणु
	uपूर्णांक32_t ucs = *(uपूर्णांक32_t *)key;
	काष्ठा पूर्णांकerval e = *(काष्ठा पूर्णांकerval *) elt;

	अगर (ucs > e.last)
		वापस 1;
	अन्यथा अगर (ucs < e.first)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक is_द्विगुन_width(uपूर्णांक32_t ucs)
अणु
	अटल स्थिर काष्ठा पूर्णांकerval द्विगुन_width[] = अणु
		अणु 0x1100, 0x115F पूर्ण, अणु 0x2329, 0x232A पूर्ण, अणु 0x2E80, 0x303E पूर्ण,
		अणु 0x3040, 0xA4CF पूर्ण, अणु 0xAC00, 0xD7A3 पूर्ण, अणु 0xF900, 0xFAFF पूर्ण,
		अणु 0xFE10, 0xFE19 पूर्ण, अणु 0xFE30, 0xFE6F पूर्ण, अणु 0xFF00, 0xFF60 पूर्ण,
		अणु 0xFFE0, 0xFFE6 पूर्ण, अणु 0x20000, 0x2FFFD पूर्ण, अणु 0x30000, 0x3FFFD पूर्ण
	पूर्ण;
	अगर (ucs < द्विगुन_width[0].first ||
	    ucs > द्विगुन_width[ARRAY_SIZE(द्विगुन_width) - 1].last)
		वापस 0;

	वापस द्वा_खोज(&ucs, द्विगुन_width, ARRAY_SIZE(द्विगुन_width),
			माप(काष्ठा पूर्णांकerval), ucs_cmp) != शून्य;
पूर्ण

काष्ठा vc_draw_region अणु
	अचिन्हित दीर्घ from, to;
	पूर्णांक x;
पूर्ण;

अटल व्योम con_flush(काष्ठा vc_data *vc, काष्ठा vc_draw_region *draw)
अणु
	अगर (draw->x < 0)
		वापस;

	vc->vc_sw->con_अ_दोs(vc, (u16 *)draw->from,
			(u16 *)draw->to - (u16 *)draw->from, vc->state.y,
			draw->x);
	draw->x = -1;
पूर्ण

अटल अंतरभूत पूर्णांक vc_translate_ascii(स्थिर काष्ठा vc_data *vc, पूर्णांक c)
अणु
	अगर (IS_ENABLED(CONFIG_CONSOLE_TRANSLATIONS)) अणु
		अगर (vc->vc_toggle_meta)
			c |= 0x80;

		वापस vc->vc_translate[c];
	पूर्ण

	वापस c;
पूर्ण


/**
 * vc_sanitize_unicode -- Replace invalid Unicode code poपूर्णांकs with U+FFFD
 * @c: the received अक्षरacter, or U+FFFD क्रम invalid sequences.
 */
अटल अंतरभूत पूर्णांक vc_sanitize_unicode(स्थिर पूर्णांक c)
अणु
	अगर ((c >= 0xd800 && c <= 0xdfff) || c == 0xfffe || c == 0xffff)
		वापस 0xfffd;

	वापस c;
पूर्ण

/**
 * vc_translate_unicode -- Combine UTF-8 पूर्णांकo Unicode in @vc_utf_अक्षर
 * @vc: भव console
 * @c: अक्षरacter to translate
 * @rescan: we वापस true अगर we need more (continuation) data
 *
 * @vc_utf_अक्षर is the being-स्थिरructed unicode अक्षरacter.
 * @vc_utf_count is the number of continuation bytes still expected to arrive.
 * @vc_npar is the number of continuation bytes arrived so far.
 */
अटल पूर्णांक vc_translate_unicode(काष्ठा vc_data *vc, पूर्णांक c, bool *rescan)
अणु
	अटल स्थिर u32 utf8_length_changes[] = अणु
		0x0000007f, 0x000007ff, 0x0000ffff,
		0x001fffff, 0x03ffffff, 0x7fffffff
	पूर्ण;

	/* Continuation byte received */
	अगर ((c & 0xc0) == 0x80) अणु
		/* Unexpected continuation byte? */
		अगर (!vc->vc_utf_count)
			वापस 0xfffd;

		vc->vc_utf_अक्षर = (vc->vc_utf_अक्षर << 6) | (c & 0x3f);
		vc->vc_npar++;
		अगर (--vc->vc_utf_count)
			जाओ need_more_bytes;

		/* Got a whole अक्षरacter */
		c = vc->vc_utf_अक्षर;
		/* Reject overदीर्घ sequences */
		अगर (c <= utf8_length_changes[vc->vc_npar - 1] ||
				c > utf8_length_changes[vc->vc_npar])
			वापस 0xfffd;

		वापस vc_sanitize_unicode(c);
	पूर्ण

	/* Single ASCII byte or first byte of a sequence received */
	अगर (vc->vc_utf_count) अणु
		/* Continuation byte expected */
		*rescan = true;
		vc->vc_utf_count = 0;
		वापस 0xfffd;
	पूर्ण

	/* Nothing to करो अगर an ASCII byte was received */
	अगर (c <= 0x7f)
		वापस c;

	/* First byte of a multibyte sequence received */
	vc->vc_npar = 0;
	अगर ((c & 0xe0) == 0xc0) अणु
		vc->vc_utf_count = 1;
		vc->vc_utf_अक्षर = (c & 0x1f);
	पूर्ण अन्यथा अगर ((c & 0xf0) == 0xe0) अणु
		vc->vc_utf_count = 2;
		vc->vc_utf_अक्षर = (c & 0x0f);
	पूर्ण अन्यथा अगर ((c & 0xf8) == 0xf0) अणु
		vc->vc_utf_count = 3;
		vc->vc_utf_अक्षर = (c & 0x07);
	पूर्ण अन्यथा अगर ((c & 0xfc) == 0xf8) अणु
		vc->vc_utf_count = 4;
		vc->vc_utf_अक्षर = (c & 0x03);
	पूर्ण अन्यथा अगर ((c & 0xfe) == 0xfc) अणु
		vc->vc_utf_count = 5;
		vc->vc_utf_अक्षर = (c & 0x01);
	पूर्ण अन्यथा अणु
		/* 254 and 255 are invalid */
		वापस 0xfffd;
	पूर्ण

need_more_bytes:
	वापस -1;
पूर्ण

अटल पूर्णांक vc_translate(काष्ठा vc_data *vc, पूर्णांक *c, bool *rescan)
अणु
	/* Do no translation at all in control states */
	अगर (vc->vc_state != ESnormal)
		वापस *c;

	अगर (vc->vc_utf && !vc->vc_disp_ctrl)
		वापस *c = vc_translate_unicode(vc, *c, rescan);

	/* no utf or alternate अक्षरset mode */
	वापस vc_translate_ascii(vc, *c);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर vc_invert_attr(स्थिर काष्ठा vc_data *vc)
अणु
	अगर (!vc->vc_can_करो_color)
		वापस vc->vc_attr ^ 0x08;

	अगर (vc->vc_hi_font_mask == 0x100)
		वापस   (vc->vc_attr & 0x11) |
			((vc->vc_attr & 0xe0) >> 4) |
			((vc->vc_attr & 0x0e) << 4);

	वापस   (vc->vc_attr & 0x88) |
		((vc->vc_attr & 0x70) >> 4) |
		((vc->vc_attr & 0x07) << 4);
पूर्ण

अटल bool vc_is_control(काष्ठा vc_data *vc, पूर्णांक tc, पूर्णांक c)
अणु
	/*
	 * A biपंचांगap क्रम codes <32. A bit of 1 indicates that the code
	 * corresponding to that bit number invokes some special action (such
	 * as cursor movement) and should not be displayed as a glyph unless
	 * the disp_ctrl mode is explicitly enabled.
	 */
	अटल स्थिर u32 CTRL_ACTION = 0x0d00ff81;
	/* Cannot be overridden by disp_ctrl */
	अटल स्थिर u32 CTRL_ALWAYS = 0x0800f501;

	अगर (vc->vc_state != ESnormal)
		वापस true;

	अगर (!tc)
		वापस true;

	/*
	 * If the original code was a control अक्षरacter we only allow a glyph
	 * to be displayed अगर the code is not normally used (such as क्रम cursor
	 * movement) or अगर the disp_ctrl mode has been explicitly enabled.
	 * Certain अक्षरacters (as given by the CTRL_ALWAYS biपंचांगap) are always
	 * displayed as control अक्षरacters, as the console would be pretty
	 * useless without them; to display an arbitrary font position use the
	 * direct-to-font zone in UTF-8 mode.
	 */
	अगर (c < 32) अणु
		अगर (vc->vc_disp_ctrl)
			वापस CTRL_ALWAYS & BIT(c);
		अन्यथा
			वापस vc->vc_utf || (CTRL_ACTION & BIT(c));
	पूर्ण

	अगर (c == 127 && !vc->vc_disp_ctrl)
		वापस true;

	अगर (c == 128 + 27)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक vc_con_ग_लिखो_normal(काष्ठा vc_data *vc, पूर्णांक tc, पूर्णांक c,
		काष्ठा vc_draw_region *draw)
अणु
	पूर्णांक next_c;
	अचिन्हित अक्षर vc_attr = vc->vc_attr;
	u16 himask = vc->vc_hi_font_mask, अक्षरmask = himask ? 0x1ff : 0xff;
	u8 width = 1;
	bool inverse = false;

	अगर (vc->vc_utf && !vc->vc_disp_ctrl) अणु
		अगर (is_द्विगुन_width(c))
			width = 2;
	पूर्ण

	/* Now try to find out how to display it */
	tc = conv_uni_to_pc(vc, tc);
	अगर (tc & ~अक्षरmask) अणु
		अगर (tc == -1 || tc == -2)
			वापस -1; /* nothing to display */

		/* Glyph not found */
		अगर ((!vc->vc_utf || vc->vc_disp_ctrl || c < 128) &&
				!(c & ~अक्षरmask)) अणु
			/*
			 * In legacy mode use the glyph we get by a 1:1
			 * mapping.
			 * This would make असलolutely no sense with Unicode in
			 * mind, but करो this क्रम ASCII अक्षरacters since a font
			 * may lack Unicode mapping info and we करोn't want to
			 * end up with having question marks only.
			 */
			tc = c;
		पूर्ण अन्यथा अणु
			/*
			 * Display U+FFFD. If it's not found, display an inverse
			 * question mark.
			 */
			tc = conv_uni_to_pc(vc, 0xfffd);
			अगर (tc < 0) अणु
				inverse = true;
				tc = conv_uni_to_pc(vc, '?');
				अगर (tc < 0)
					tc = '?';

				vc_attr = vc_invert_attr(vc);
				con_flush(vc, draw);
			पूर्ण
		पूर्ण
	पूर्ण

	next_c = c;
	जबतक (1) अणु
		अगर (vc->vc_need_wrap || vc->vc_decim)
			con_flush(vc, draw);
		अगर (vc->vc_need_wrap) अणु
			cr(vc);
			lf(vc);
		पूर्ण
		अगर (vc->vc_decim)
			insert_अक्षर(vc, 1);
		vc_uniscr_अ_दो(vc, next_c);

		अगर (himask)
			tc = ((tc & 0x100) ? himask : 0) |
			      (tc &  0xff);
		tc |= (vc_attr << 8) & ~himask;

		scr_ग_लिखोw(tc, (u16 *)vc->vc_pos);

		अगर (con_should_update(vc) && draw->x < 0) अणु
			draw->x = vc->state.x;
			draw->from = vc->vc_pos;
		पूर्ण
		अगर (vc->state.x == vc->vc_cols - 1) अणु
			vc->vc_need_wrap = vc->vc_decawm;
			draw->to = vc->vc_pos + 2;
		पूर्ण अन्यथा अणु
			vc->state.x++;
			draw->to = (vc->vc_pos += 2);
		पूर्ण

		अगर (!--width)
			अवरोध;

		/* A space is prपूर्णांकed in the second column */
		tc = conv_uni_to_pc(vc, ' ');
		अगर (tc < 0)
			tc = ' ';
		next_c = ' ';
	पूर्ण
	notअगरy_ग_लिखो(vc, c);

	अगर (inverse)
		con_flush(vc, draw);

	वापस 0;
पूर्ण

/* acquires console_lock */
अटल पूर्णांक करो_con_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा vc_draw_region draw = अणु
		.x = -1,
	पूर्ण;
	पूर्णांक c, tc, n = 0;
	अचिन्हित पूर्णांक currcons;
	काष्ठा vc_data *vc;
	काष्ठा vt_notअगरier_param param;
	bool rescan;

	अगर (in_पूर्णांकerrupt())
		वापस count;

	console_lock();
	vc = tty->driver_data;
	अगर (vc == शून्य) अणु
		pr_err("vt: argh, driver_data is NULL !\n");
		console_unlock();
		वापस 0;
	पूर्ण

	currcons = vc->vc_num;
	अगर (!vc_cons_allocated(currcons)) अणु
		/* could this happen? */
		pr_warn_once("con_write: tty %d not allocated\n", currcons+1);
		console_unlock();
		वापस 0;
	पूर्ण


	/* undraw cursor first */
	अगर (con_is_fg(vc))
		hide_cursor(vc);

	param.vc = vc;

	जबतक (!tty->stopped && count) अणु
		पूर्णांक orig = *buf;
		buf++;
		n++;
		count--;
rescan_last_byte:
		c = orig;
		rescan = false;

		tc = vc_translate(vc, &c, &rescan);
		अगर (tc == -1)
			जारी;

		param.c = tc;
		अगर (atomic_notअगरier_call_chain(&vt_notअगरier_list, VT_PREWRITE,
					&param) == NOTIFY_STOP)
			जारी;

		अगर (vc_is_control(vc, tc, c)) अणु
			con_flush(vc, &draw);
			करो_con_trol(tty, vc, orig);
			जारी;
		पूर्ण

		अगर (vc_con_ग_लिखो_normal(vc, tc, c, &draw) < 0)
			जारी;

		अगर (rescan)
			जाओ rescan_last_byte;
	पूर्ण
	con_flush(vc, &draw);
	vc_uniscr_debug_check(vc);
	console_conditional_schedule();
	notअगरy_update(vc);
	console_unlock();
	वापस n;
पूर्ण

/*
 * This is the console चयनing callback.
 *
 * Doing console चयनing in a process context allows
 * us to करो the चयनes asynchronously (needed when we want
 * to चयन due to a keyboard पूर्णांकerrupt).  Synchronization
 * with other console code and prevention of re-entrancy is
 * ensured with console_lock.
 */
अटल व्योम console_callback(काष्ठा work_काष्ठा *ignored)
अणु
	console_lock();

	अगर (want_console >= 0) अणु
		अगर (want_console != fg_console &&
		    vc_cons_allocated(want_console)) अणु
			hide_cursor(vc_cons[fg_console].d);
			change_console(vc_cons[want_console].d);
			/* we only changed when the console had alपढ़ोy
			   been allocated - a new console is not created
			   in an पूर्णांकerrupt routine */
		पूर्ण
		want_console = -1;
	पूर्ण
	अगर (करो_poke_blanked_console) अणु /* करो not unblank क्रम a LED change */
		करो_poke_blanked_console = 0;
		poke_blanked_console();
	पूर्ण
	अगर (scrollback_delta) अणु
		काष्ठा vc_data *vc = vc_cons[fg_console].d;
		clear_selection();
		अगर (vc->vc_mode == KD_TEXT && vc->vc_sw->con_scrolldelta)
			vc->vc_sw->con_scrolldelta(vc, scrollback_delta);
		scrollback_delta = 0;
	पूर्ण
	अगर (blank_समयr_expired) अणु
		करो_blank_screen(0);
		blank_समयr_expired = 0;
	पूर्ण
	notअगरy_update(vc_cons[fg_console].d);

	console_unlock();
पूर्ण

पूर्णांक set_console(पूर्णांक nr)
अणु
	काष्ठा vc_data *vc = vc_cons[fg_console].d;

	अगर (!vc_cons_allocated(nr) || vt_करोnt_चयन ||
		(vc->vt_mode.mode == VT_AUTO && vc->vc_mode == KD_GRAPHICS)) अणु

		/*
		 * Console चयन will fail in console_callback() or
		 * change_console() so there is no poपूर्णांक scheduling
		 * the callback
		 *
		 * Existing set_console() users करोn't check the वापस
		 * value so this shouldn't अवरोध anything
		 */
		वापस -EINVAL;
	पूर्ण

	want_console = nr;
	schedule_console_callback();

	वापस 0;
पूर्ण

काष्ठा tty_driver *console_driver;

#अगर_घोषित CONFIG_VT_CONSOLE

/**
 * vt_kmsg_redirect() - Sets/माला_लो the kernel message console
 * @new:	The new भव terminal number or -1 अगर the console should stay
 * 		unchanged
 *
 * By शेष, the kernel messages are always prपूर्णांकed on the current भव
 * console. However, the user may modअगरy that शेष with the
 * TIOCL_SETKMSGREसूचीECT ioctl call.
 *
 * This function sets the kernel message console to be @new. It वापसs the old
 * भव console number. The भव terminal number 0 (both as parameter and
 * वापस value) means no redirection (i.e. always prपूर्णांकed on the currently
 * active console).
 *
 * The parameter -1 means that only the current console is वापसed, but the
 * value is not modअगरied. You may use the macro vt_get_kmsg_redirect() in that
 * हाल to make the code more understandable.
 *
 * When the kernel is compiled without CONFIG_VT_CONSOLE, this function ignores
 * the parameter and always वापसs 0.
 */
पूर्णांक vt_kmsg_redirect(पूर्णांक new)
अणु
	अटल पूर्णांक kmsg_con;

	अगर (new != -1)
		वापस xchg(&kmsg_con, new);
	अन्यथा
		वापस kmsg_con;
पूर्ण

/*
 *	Console on भव terminal
 *
 * The console must be locked when we get here.
 */

अटल व्योम vt_console_prपूर्णांक(काष्ठा console *co, स्थिर अक्षर *b, अचिन्हित count)
अणु
	काष्ठा vc_data *vc = vc_cons[fg_console].d;
	अचिन्हित अक्षर c;
	अटल DEFINE_SPINLOCK(prपूर्णांकing_lock);
	स्थिर uलघु *start;
	uलघु start_x, cnt;
	पूर्णांक kmsg_console;

	/* console busy or not yet initialized */
	अगर (!prपूर्णांकable)
		वापस;
	अगर (!spin_trylock(&prपूर्णांकing_lock))
		वापस;

	kmsg_console = vt_get_kmsg_redirect();
	अगर (kmsg_console && vc_cons_allocated(kmsg_console - 1))
		vc = vc_cons[kmsg_console - 1].d;

	अगर (!vc_cons_allocated(fg_console)) अणु
		/* impossible */
		/* prपूर्णांकk("vt_console_print: tty %d not allocated ??\n", currcons+1); */
		जाओ quit;
	पूर्ण

	अगर (vc->vc_mode != KD_TEXT)
		जाओ quit;

	/* undraw cursor first */
	अगर (con_is_fg(vc))
		hide_cursor(vc);

	start = (uलघु *)vc->vc_pos;
	start_x = vc->state.x;
	cnt = 0;
	जबतक (count--) अणु
		c = *b++;
		अगर (c == 10 || c == 13 || c == 8 || vc->vc_need_wrap) अणु
			अगर (cnt && con_is_visible(vc))
				vc->vc_sw->con_अ_दोs(vc, start, cnt, vc->state.y, start_x);
			cnt = 0;
			अगर (c == 8) अणु		/* backspace */
				bs(vc);
				start = (uलघु *)vc->vc_pos;
				start_x = vc->state.x;
				जारी;
			पूर्ण
			अगर (c != 13)
				lf(vc);
			cr(vc);
			start = (uलघु *)vc->vc_pos;
			start_x = vc->state.x;
			अगर (c == 10 || c == 13)
				जारी;
		पूर्ण
		vc_uniscr_अ_दो(vc, c);
		scr_ग_लिखोw((vc->vc_attr << 8) + c, (अचिन्हित लघु *)vc->vc_pos);
		notअगरy_ग_लिखो(vc, c);
		cnt++;
		अगर (vc->state.x == vc->vc_cols - 1) अणु
			vc->vc_need_wrap = 1;
		पूर्ण अन्यथा अणु
			vc->vc_pos += 2;
			vc->state.x++;
		पूर्ण
	पूर्ण
	अगर (cnt && con_is_visible(vc))
		vc->vc_sw->con_अ_दोs(vc, start, cnt, vc->state.y, start_x);
	set_cursor(vc);
	notअगरy_update(vc);

quit:
	spin_unlock(&prपूर्णांकing_lock);
पूर्ण

अटल काष्ठा tty_driver *vt_console_device(काष्ठा console *c, पूर्णांक *index)
अणु
	*index = c->index ? c->index-1 : fg_console;
	वापस console_driver;
पूर्ण

अटल काष्ठा console vt_console_driver = अणु
	.name		= "tty",
	.ग_लिखो		= vt_console_prपूर्णांक,
	.device		= vt_console_device,
	.unblank	= unblank_screen,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
पूर्ण;
#पूर्ण_अगर

/*
 *	Handling of Linux-specअगरic VC ioctls
 */

/*
 * Generally a bit racy with respect to console_lock();.
 *
 * There are some functions which करोn't need it.
 *
 * There are some functions which can sleep क्रम arbitrary periods
 * (paste_selection) but we करोn't need the lock there anyway.
 *
 * set_selection_user has locking, and definitely needs it
 */

पूर्णांक tioclinux(काष्ठा tty_काष्ठा *tty, अचिन्हित दीर्घ arg)
अणु
	अक्षर type, data;
	अक्षर __user *p = (अक्षर __user *)arg;
	पूर्णांक lines;
	पूर्णांक ret;

	अगर (current->संकेत->tty != tty && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (get_user(type, p))
		वापस -EFAULT;
	ret = 0;

	चयन (type)
	अणु
		हाल TIOCL_SETSEL:
			ret = set_selection_user((काष्ठा tiocl_selection
						 __user *)(p+1), tty);
			अवरोध;
		हाल TIOCL_PASTESEL:
			ret = paste_selection(tty);
			अवरोध;
		हाल TIOCL_UNBLANKSCREEN:
			console_lock();
			unblank_screen();
			console_unlock();
			अवरोध;
		हाल TIOCL_SELLOADLUT:
			console_lock();
			ret = sel_loadlut(p);
			console_unlock();
			अवरोध;
		हाल TIOCL_GETSHIFTSTATE:

	/*
	 * Make it possible to react to Shअगरt+Mousebutton.
	 * Note that 'shift_state' is an unकरोcumented
	 * kernel-पूर्णांकernal variable; programs not बंदly
	 * related to the kernel should not use this.
	 */
			data = vt_get_shअगरt_state();
			ret = put_user(data, p);
			अवरोध;
		हाल TIOCL_GETMOUSEREPORTING:
			console_lock();	/* May be overसमाप्त */
			data = mouse_reporting();
			console_unlock();
			ret = put_user(data, p);
			अवरोध;
		हाल TIOCL_SETVESABLANK:
			console_lock();
			ret = set_vesa_blanking(p);
			console_unlock();
			अवरोध;
		हाल TIOCL_GETKMSGREसूचीECT:
			data = vt_get_kmsg_redirect();
			ret = put_user(data, p);
			अवरोध;
		हाल TIOCL_SETKMSGREसूचीECT:
			अगर (!capable(CAP_SYS_ADMIN)) अणु
				ret = -EPERM;
			पूर्ण अन्यथा अणु
				अगर (get_user(data, p+1))
					ret = -EFAULT;
				अन्यथा
					vt_kmsg_redirect(data);
			पूर्ण
			अवरोध;
		हाल TIOCL_GETFGCONSOLE:
			/* No locking needed as this is a transiently
			   correct वापस anyway अगर the caller hasn't
			   disabled चयनing */
			ret = fg_console;
			अवरोध;
		हाल TIOCL_SCROLLCONSOLE:
			अगर (get_user(lines, (s32 __user *)(p+4))) अणु
				ret = -EFAULT;
			पूर्ण अन्यथा अणु
				/* Need the console lock here. Note that lots
				   of other calls need fixing beक्रमe the lock
				   is actually useful ! */
				console_lock();
				scrollfront(vc_cons[fg_console].d, lines);
				console_unlock();
				ret = 0;
			पूर्ण
			अवरोध;
		हाल TIOCL_BLANKSCREEN:	/* until explicitly unblanked, not only poked */
			console_lock();
			ignore_poke = 1;
			करो_blank_screen(0);
			console_unlock();
			अवरोध;
		हाल TIOCL_BLANKEDSCREEN:
			ret = console_blanked;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * /dev/ttyN handling
 */

अटल पूर्णांक con_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक	retval;

	retval = करो_con_ग_लिखो(tty, buf, count);
	con_flush_अक्षरs(tty);

	वापस retval;
पूर्ण

अटल पूर्णांक con_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	अगर (in_पूर्णांकerrupt())
		वापस 0;	/* n_r3964 calls put_अक्षर() from पूर्णांकerrupt context */
	वापस करो_con_ग_लिखो(tty, &ch, 1);
पूर्ण

अटल पूर्णांक con_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (tty->stopped)
		वापस 0;
	वापस 32768;		/* No limit, really; we're not buffering */
पूर्ण

अटल पूर्णांक con_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	वापस 0;		/* we're not buffering */
पूर्ण

/*
 * con_throttle and con_unthrottle are only used क्रम
 * paste_selection(), which has to stuff in a large number of
 * अक्षरacters...
 */
अटल व्योम con_throttle(काष्ठा tty_काष्ठा *tty)
अणु
पूर्ण

अटल व्योम con_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा vc_data *vc = tty->driver_data;

	wake_up_पूर्णांकerruptible(&vc->paste_रुको);
पूर्ण

/*
 * Turn the Scroll-Lock LED on when the tty is stopped
 */
अटल व्योम con_stop(काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक console_num;
	अगर (!tty)
		वापस;
	console_num = tty->index;
	अगर (!vc_cons_allocated(console_num))
		वापस;
	vt_kbd_con_stop(console_num);
पूर्ण

/*
 * Turn the Scroll-Lock LED off when the console is started
 */
अटल व्योम con_start(काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक console_num;
	अगर (!tty)
		वापस;
	console_num = tty->index;
	अगर (!vc_cons_allocated(console_num))
		वापस;
	vt_kbd_con_start(console_num);
पूर्ण

अटल व्योम con_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा vc_data *vc;

	अगर (in_पूर्णांकerrupt())	/* from flush_to_ldisc */
		वापस;

	/* अगर we race with con_बंद(), vt may be null */
	console_lock();
	vc = tty->driver_data;
	अगर (vc)
		set_cursor(vc);
	console_unlock();
पूर्ण

/*
 * Allocate the console screen memory.
 */
अटल पूर्णांक con_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित पूर्णांक currcons = tty->index;
	काष्ठा vc_data *vc;
	पूर्णांक ret;

	console_lock();
	ret = vc_allocate(currcons);
	अगर (ret)
		जाओ unlock;

	vc = vc_cons[currcons].d;

	/* Still being मुक्तd */
	अगर (vc->port.tty) अणु
		ret = -ERESTARTSYS;
		जाओ unlock;
	पूर्ण

	ret = tty_port_install(&vc->port, driver, tty);
	अगर (ret)
		जाओ unlock;

	tty->driver_data = vc;
	vc->port.tty = tty;
	tty_port_get(&vc->port);

	अगर (!tty->winsize.ws_row && !tty->winsize.ws_col) अणु
		tty->winsize.ws_row = vc_cons[currcons].d->vc_rows;
		tty->winsize.ws_col = vc_cons[currcons].d->vc_cols;
	पूर्ण
	अगर (vc->vc_utf)
		tty->termios.c_अगरlag |= IUTF8;
	अन्यथा
		tty->termios.c_अगरlag &= ~IUTF8;
unlock:
	console_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक con_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	/* everything करोne in install */
	वापस 0;
पूर्ण


अटल व्योम con_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	/* Nothing to करो - we defer to shutकरोwn */
पूर्ण

अटल व्योम con_shutकरोwn(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा vc_data *vc = tty->driver_data;
	BUG_ON(vc == शून्य);
	console_lock();
	vc->port.tty = शून्य;
	console_unlock();
पूर्ण

अटल व्योम con_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा vc_data *vc = tty->driver_data;

	tty_port_put(&vc->port);
पूर्ण

अटल पूर्णांक शेष_color           = 7; /* white */
अटल पूर्णांक शेष_italic_color    = 2; // green (ASCII)
अटल पूर्णांक शेष_underline_color = 3; // cyan (ASCII)
module_param_named(color, शेष_color, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(italic, शेष_italic_color, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(underline, शेष_underline_color, पूर्णांक, S_IRUGO | S_IWUSR);

अटल व्योम vc_init(काष्ठा vc_data *vc, अचिन्हित पूर्णांक rows,
		    अचिन्हित पूर्णांक cols, पूर्णांक करो_clear)
अणु
	पूर्णांक j, k ;

	vc->vc_cols = cols;
	vc->vc_rows = rows;
	vc->vc_size_row = cols << 1;
	vc->vc_screenbuf_size = vc->vc_rows * vc->vc_size_row;

	set_origin(vc);
	vc->vc_pos = vc->vc_origin;
	reset_vc(vc);
	क्रम (j=k=0; j<16; j++) अणु
		vc->vc_palette[k++] = शेष_red[j] ;
		vc->vc_palette[k++] = शेष_grn[j] ;
		vc->vc_palette[k++] = शेष_blu[j] ;
	पूर्ण
	vc->vc_def_color       = शेष_color;
	vc->vc_ulcolor         = शेष_underline_color;
	vc->vc_itcolor         = शेष_italic_color;
	vc->vc_halfcolor       = 0x08;   /* grey */
	init_रुकोqueue_head(&vc->paste_रुको);
	reset_terminal(vc, करो_clear);
पूर्ण

/*
 * This routine initializes console पूर्णांकerrupts, and करोes nothing
 * अन्यथा. If you want the screen to clear, call tty_ग_लिखो with
 * the appropriate escape-sequence.
 */

अटल पूर्णांक __init con_init(व्योम)
अणु
	स्थिर अक्षर *display_desc = शून्य;
	काष्ठा vc_data *vc;
	अचिन्हित पूर्णांक currcons = 0, i;

	console_lock();

	अगर (!conचयनp)
		conचयनp = &dummy_con;
	display_desc = conचयनp->con_startup();
	अगर (!display_desc) अणु
		fg_console = 0;
		console_unlock();
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < MAX_NR_CON_DRIVER; i++) अणु
		काष्ठा con_driver *con_driver = &रेजिस्टरed_con_driver[i];

		अगर (con_driver->con == शून्य) अणु
			con_driver->con = conचयनp;
			con_driver->desc = display_desc;
			con_driver->flag = CON_DRIVER_FLAG_INIT;
			con_driver->first = 0;
			con_driver->last = MAX_NR_CONSOLES - 1;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MAX_NR_CONSOLES; i++)
		con_driver_map[i] = conचयनp;

	अगर (blankपूर्णांकerval) अणु
		blank_state = blank_normal_रुको;
		mod_समयr(&console_समयr, jअगरfies + (blankपूर्णांकerval * HZ));
	पूर्ण

	क्रम (currcons = 0; currcons < MIN_NR_CONSOLES; currcons++) अणु
		vc_cons[currcons].d = vc = kzalloc(माप(काष्ठा vc_data), GFP_NOWAIT);
		INIT_WORK(&vc_cons[currcons].SAK_work, vc_SAK);
		tty_port_init(&vc->port);
		visual_init(vc, currcons, 1);
		/* Assuming vc->vc_अणुcols,rows,screenbuf_sizeपूर्ण are sane here. */
		vc->vc_screenbuf = kzalloc(vc->vc_screenbuf_size, GFP_NOWAIT);
		vc_init(vc, vc->vc_rows, vc->vc_cols,
			currcons || !vc->vc_sw->con_save_screen);
	पूर्ण
	currcons = fg_console = 0;
	master_display_fg = vc = vc_cons[currcons].d;
	set_origin(vc);
	save_screen(vc);
	जाओxy(vc, vc->state.x, vc->state.y);
	csi_J(vc, 0);
	update_screen(vc);
	pr_info("Console: %s %s %dx%d\n",
		vc->vc_can_करो_color ? "colour" : "mono",
		display_desc, vc->vc_cols, vc->vc_rows);
	prपूर्णांकable = 1;

	console_unlock();

#अगर_घोषित CONFIG_VT_CONSOLE
	रेजिस्टर_console(&vt_console_driver);
#पूर्ण_अगर
	वापस 0;
पूर्ण
console_initcall(con_init);

अटल स्थिर काष्ठा tty_operations con_ops = अणु
	.install = con_install,
	.खोलो = con_खोलो,
	.बंद = con_बंद,
	.ग_लिखो = con_ग_लिखो,
	.ग_लिखो_room = con_ग_लिखो_room,
	.put_अक्षर = con_put_अक्षर,
	.flush_अक्षरs = con_flush_अक्षरs,
	.अक्षरs_in_buffer = con_अक्षरs_in_buffer,
	.ioctl = vt_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = vt_compat_ioctl,
#पूर्ण_अगर
	.stop = con_stop,
	.start = con_start,
	.throttle = con_throttle,
	.unthrottle = con_unthrottle,
	.resize = vt_resize,
	.shutकरोwn = con_shutकरोwn,
	.cleanup = con_cleanup,
पूर्ण;

अटल काष्ठा cdev vc0_cdev;

अटल sमाप_प्रकार show_tty_active(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "tty%d\n", fg_console + 1);
पूर्ण
अटल DEVICE_ATTR(active, S_IRUGO, show_tty_active, शून्य);

अटल काष्ठा attribute *vt_dev_attrs[] = अणु
	&dev_attr_active.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(vt_dev);

पूर्णांक __init vty_init(स्थिर काष्ठा file_operations *console_fops)
अणु
	cdev_init(&vc0_cdev, console_fops);
	अगर (cdev_add(&vc0_cdev, MKDEV(TTY_MAJOR, 0), 1) ||
	    रेजिस्टर_chrdev_region(MKDEV(TTY_MAJOR, 0), 1, "/dev/vc/0") < 0)
		panic("Couldn't register /dev/tty0 driver\n");
	tty0dev = device_create_with_groups(tty_class, शून्य,
					    MKDEV(TTY_MAJOR, 0), शून्य,
					    vt_dev_groups, "tty0");
	अगर (IS_ERR(tty0dev))
		tty0dev = शून्य;

	vcs_init();

	console_driver = alloc_tty_driver(MAX_NR_CONSOLES);
	अगर (!console_driver)
		panic("Couldn't allocate console driver\n");

	console_driver->name = "tty";
	console_driver->name_base = 1;
	console_driver->major = TTY_MAJOR;
	console_driver->minor_start = 1;
	console_driver->type = TTY_DRIVER_TYPE_CONSOLE;
	console_driver->init_termios = tty_std_termios;
	अगर (शेष_utf8)
		console_driver->init_termios.c_अगरlag |= IUTF8;
	console_driver->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_RESET_TERMIOS;
	tty_set_operations(console_driver, &con_ops);
	अगर (tty_रेजिस्टर_driver(console_driver))
		panic("Couldn't register console driver\n");
	kbd_init();
	console_map_init();
#अगर_घोषित CONFIG_MDA_CONSOLE
	mda_console_init();
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_अघोषित VT_SINGLE_DRIVER

अटल काष्ठा class *vtconsole_class;

अटल पूर्णांक करो_bind_con_driver(स्थिर काष्ठा consw *csw, पूर्णांक first, पूर्णांक last,
			   पूर्णांक deflt)
अणु
	काष्ठा module *owner = csw->owner;
	स्थिर अक्षर *desc = शून्य;
	काष्ठा con_driver *con_driver;
	पूर्णांक i, j = -1, k = -1, retval = -ENODEV;

	अगर (!try_module_get(owner))
		वापस -ENODEV;

	WARN_CONSOLE_UNLOCKED();

	/* check अगर driver is रेजिस्टरed */
	क्रम (i = 0; i < MAX_NR_CON_DRIVER; i++) अणु
		con_driver = &रेजिस्टरed_con_driver[i];

		अगर (con_driver->con == csw) अणु
			desc = con_driver->desc;
			retval = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (retval)
		जाओ err;

	अगर (!(con_driver->flag & CON_DRIVER_FLAG_INIT)) अणु
		csw->con_startup();
		con_driver->flag |= CON_DRIVER_FLAG_INIT;
	पूर्ण

	अगर (deflt) अणु
		अगर (conचयनp)
			module_put(conचयनp->owner);

		__module_get(owner);
		conचयनp = csw;
	पूर्ण

	first = max(first, con_driver->first);
	last = min(last, con_driver->last);

	क्रम (i = first; i <= last; i++) अणु
		पूर्णांक old_was_color;
		काष्ठा vc_data *vc = vc_cons[i].d;

		अगर (con_driver_map[i])
			module_put(con_driver_map[i]->owner);
		__module_get(owner);
		con_driver_map[i] = csw;

		अगर (!vc || !vc->vc_sw)
			जारी;

		j = i;

		अगर (con_is_visible(vc)) अणु
			k = i;
			save_screen(vc);
		पूर्ण

		old_was_color = vc->vc_can_करो_color;
		vc->vc_sw->con_deinit(vc);
		vc->vc_origin = (अचिन्हित दीर्घ)vc->vc_screenbuf;
		visual_init(vc, i, 0);
		set_origin(vc);
		update_attr(vc);

		/* If the console changed between mono <-> color, then
		 * the attributes in the screenbuf will be wrong.  The
		 * following resets all attributes to something sane.
		 */
		अगर (old_was_color != vc->vc_can_करो_color)
			clear_buffer_attributes(vc);
	पूर्ण

	pr_info("Console: switching ");
	अगर (!deflt)
		pr_cont("consoles %d-%d ", first + 1, last + 1);
	अगर (j >= 0) अणु
		काष्ठा vc_data *vc = vc_cons[j].d;

		pr_cont("to %s %s %dx%d\n",
			vc->vc_can_करो_color ? "colour" : "mono",
			desc, vc->vc_cols, vc->vc_rows);

		अगर (k >= 0) अणु
			vc = vc_cons[k].d;
			update_screen(vc);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_cont("to %s\n", desc);
	पूर्ण

	retval = 0;
err:
	module_put(owner);
	वापस retval;
पूर्ण;


#अगर_घोषित CONFIG_VT_HW_CONSOLE_BINDING
पूर्णांक करो_unbind_con_driver(स्थिर काष्ठा consw *csw, पूर्णांक first, पूर्णांक last, पूर्णांक deflt)
अणु
	काष्ठा module *owner = csw->owner;
	स्थिर काष्ठा consw *defcsw = शून्य;
	काष्ठा con_driver *con_driver = शून्य, *con_back = शून्य;
	पूर्णांक i, retval = -ENODEV;

	अगर (!try_module_get(owner))
		वापस -ENODEV;

	WARN_CONSOLE_UNLOCKED();

	/* check अगर driver is रेजिस्टरed and अगर it is unbindable */
	क्रम (i = 0; i < MAX_NR_CON_DRIVER; i++) अणु
		con_driver = &रेजिस्टरed_con_driver[i];

		अगर (con_driver->con == csw &&
		    con_driver->flag & CON_DRIVER_FLAG_MODULE) अणु
			retval = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (retval)
		जाओ err;

	retval = -ENODEV;

	/* check अगर backup driver exists */
	क्रम (i = 0; i < MAX_NR_CON_DRIVER; i++) अणु
		con_back = &रेजिस्टरed_con_driver[i];

		अगर (con_back->con && con_back->con != csw) अणु
			defcsw = con_back->con;
			retval = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (retval)
		जाओ err;

	अगर (!con_is_bound(csw))
		जाओ err;

	first = max(first, con_driver->first);
	last = min(last, con_driver->last);

	क्रम (i = first; i <= last; i++) अणु
		अगर (con_driver_map[i] == csw) अणु
			module_put(csw->owner);
			con_driver_map[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (!con_is_bound(defcsw)) अणु
		स्थिर काष्ठा consw *defconsw = conचयनp;

		defcsw->con_startup();
		con_back->flag |= CON_DRIVER_FLAG_INIT;
		/*
		 * vgacon may change the शेष driver to poपूर्णांक
		 * to dummycon, we restore it here...
		 */
		conचयनp = defconsw;
	पूर्ण

	अगर (!con_is_bound(csw))
		con_driver->flag &= ~CON_DRIVER_FLAG_INIT;

	/* ignore वापस value, binding should not fail */
	करो_bind_con_driver(defcsw, first, last, deflt);
err:
	module_put(owner);
	वापस retval;

पूर्ण
EXPORT_SYMBOL_GPL(करो_unbind_con_driver);

अटल पूर्णांक vt_bind(काष्ठा con_driver *con)
अणु
	स्थिर काष्ठा consw *defcsw = शून्य, *csw = शून्य;
	पूर्णांक i, more = 1, first = -1, last = -1, deflt = 0;

 	अगर (!con->con || !(con->flag & CON_DRIVER_FLAG_MODULE))
		जाओ err;

	csw = con->con;

	क्रम (i = 0; i < MAX_NR_CON_DRIVER; i++) अणु
		काष्ठा con_driver *con = &रेजिस्टरed_con_driver[i];

		अगर (con->con && !(con->flag & CON_DRIVER_FLAG_MODULE)) अणु
			defcsw = con->con;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!defcsw)
		जाओ err;

	जबतक (more) अणु
		more = 0;

		क्रम (i = con->first; i <= con->last; i++) अणु
			अगर (con_driver_map[i] == defcsw) अणु
				अगर (first == -1)
					first = i;
				last = i;
				more = 1;
			पूर्ण अन्यथा अगर (first != -1)
				अवरोध;
		पूर्ण

		अगर (first == 0 && last == MAX_NR_CONSOLES -1)
			deflt = 1;

		अगर (first != -1)
			करो_bind_con_driver(csw, first, last, deflt);

		first = -1;
		last = -1;
		deflt = 0;
	पूर्ण

err:
	वापस 0;
पूर्ण

अटल पूर्णांक vt_unbind(काष्ठा con_driver *con)
अणु
	स्थिर काष्ठा consw *csw = शून्य;
	पूर्णांक i, more = 1, first = -1, last = -1, deflt = 0;
	पूर्णांक ret;

 	अगर (!con->con || !(con->flag & CON_DRIVER_FLAG_MODULE))
		जाओ err;

	csw = con->con;

	जबतक (more) अणु
		more = 0;

		क्रम (i = con->first; i <= con->last; i++) अणु
			अगर (con_driver_map[i] == csw) अणु
				अगर (first == -1)
					first = i;
				last = i;
				more = 1;
			पूर्ण अन्यथा अगर (first != -1)
				अवरोध;
		पूर्ण

		अगर (first == 0 && last == MAX_NR_CONSOLES -1)
			deflt = 1;

		अगर (first != -1) अणु
			ret = करो_unbind_con_driver(csw, first, last, deflt);
			अगर (ret != 0)
				वापस ret;
		पूर्ण

		first = -1;
		last = -1;
		deflt = 0;
	पूर्ण

err:
	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक vt_bind(काष्ठा con_driver *con)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक vt_unbind(काष्ठा con_driver *con)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_VT_HW_CONSOLE_BINDING */

अटल sमाप_प्रकार store_bind(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा con_driver *con = dev_get_drvdata(dev);
	पूर्णांक bind = simple_म_से_अदीर्घ(buf, शून्य, 0);

	console_lock();

	अगर (bind)
		vt_bind(con);
	अन्यथा
		vt_unbind(con);

	console_unlock();

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_bind(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा con_driver *con = dev_get_drvdata(dev);
	पूर्णांक bind;

	console_lock();
	bind = con_is_bound(con->con);
	console_unlock();

	वापस snम_लिखो(buf, PAGE_SIZE, "%i\n", bind);
पूर्ण

अटल sमाप_प्रकार show_name(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा con_driver *con = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s %s\n",
			(con->flag & CON_DRIVER_FLAG_MODULE) ? "(M)" : "(S)",
			 con->desc);

पूर्ण

अटल DEVICE_ATTR(bind, S_IRUGO|S_IWUSR, show_bind, store_bind);
अटल DEVICE_ATTR(name, S_IRUGO, show_name, शून्य);

अटल काष्ठा attribute *con_dev_attrs[] = अणु
	&dev_attr_bind.attr,
	&dev_attr_name.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(con_dev);

अटल पूर्णांक vtconsole_init_device(काष्ठा con_driver *con)
अणु
	con->flag |= CON_DRIVER_FLAG_ATTR;
	वापस 0;
पूर्ण

अटल व्योम vtconsole_deinit_device(काष्ठा con_driver *con)
अणु
	con->flag &= ~CON_DRIVER_FLAG_ATTR;
पूर्ण

/**
 * con_is_bound - checks अगर driver is bound to the console
 * @csw: console driver
 *
 * RETURNS: zero अगर unbound, nonzero अगर bound
 *
 * Drivers can call this and अगर zero, they should release
 * all resources allocated on con_startup()
 */
पूर्णांक con_is_bound(स्थिर काष्ठा consw *csw)
अणु
	पूर्णांक i, bound = 0;

	WARN_CONSOLE_UNLOCKED();

	क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
		अगर (con_driver_map[i] == csw) अणु
			bound = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस bound;
पूर्ण
EXPORT_SYMBOL(con_is_bound);

/**
 * con_is_visible - checks whether the current console is visible
 * @vc: भव console
 *
 * RETURNS: zero अगर not visible, nonzero अगर visible
 */
bool con_is_visible(स्थिर काष्ठा vc_data *vc)
अणु
	WARN_CONSOLE_UNLOCKED();

	वापस *vc->vc_display_fg == vc;
पूर्ण
EXPORT_SYMBOL(con_is_visible);

/**
 * con_debug_enter - prepare the console क्रम the kernel debugger
 * @vc: भव console
 *
 * Called when the console is taken over by the kernel debugger, this
 * function needs to save the current console state, then put the console
 * पूर्णांकo a state suitable क्रम the kernel debugger.
 *
 * RETURNS:
 * Zero on success, nonzero अगर a failure occurred when trying to prepare
 * the console क्रम the debugger.
 */
पूर्णांक con_debug_enter(काष्ठा vc_data *vc)
अणु
	पूर्णांक ret = 0;

	saved_fg_console = fg_console;
	saved_last_console = last_console;
	saved_want_console = want_console;
	saved_vc_mode = vc->vc_mode;
	saved_console_blanked = console_blanked;
	vc->vc_mode = KD_TEXT;
	console_blanked = 0;
	अगर (vc->vc_sw->con_debug_enter)
		ret = vc->vc_sw->con_debug_enter(vc);
#अगर_घोषित CONFIG_KGDB_KDB
	/* Set the initial LINES variable अगर it is not alपढ़ोy set */
	अगर (vc->vc_rows < 999) अणु
		पूर्णांक linecount;
		अक्षर lns[4];
		स्थिर अक्षर *setargs[3] = अणु
			"set",
			"LINES",
			lns,
		पूर्ण;
		अगर (kdbgetपूर्णांकenv(setargs[0], &linecount)) अणु
			snम_लिखो(lns, 4, "%i", vc->vc_rows);
			kdb_set(2, setargs);
		पूर्ण
	पूर्ण
	अगर (vc->vc_cols < 999) अणु
		पूर्णांक colcount;
		अक्षर cols[4];
		स्थिर अक्षर *setargs[3] = अणु
			"set",
			"COLUMNS",
			cols,
		पूर्ण;
		अगर (kdbgetपूर्णांकenv(setargs[0], &colcount)) अणु
			snम_लिखो(cols, 4, "%i", vc->vc_cols);
			kdb_set(2, setargs);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_KGDB_KDB */
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(con_debug_enter);

/**
 * con_debug_leave - restore console state
 *
 * Restore the console state to what it was beक्रमe the kernel debugger
 * was invoked.
 *
 * RETURNS:
 * Zero on success, nonzero अगर a failure occurred when trying to restore
 * the console.
 */
पूर्णांक con_debug_leave(व्योम)
अणु
	काष्ठा vc_data *vc;
	पूर्णांक ret = 0;

	fg_console = saved_fg_console;
	last_console = saved_last_console;
	want_console = saved_want_console;
	console_blanked = saved_console_blanked;
	vc_cons[fg_console].d->vc_mode = saved_vc_mode;

	vc = vc_cons[fg_console].d;
	अगर (vc->vc_sw->con_debug_leave)
		ret = vc->vc_sw->con_debug_leave(vc);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(con_debug_leave);

अटल पूर्णांक करो_रेजिस्टर_con_driver(स्थिर काष्ठा consw *csw, पूर्णांक first, पूर्णांक last)
अणु
	काष्ठा module *owner = csw->owner;
	काष्ठा con_driver *con_driver;
	स्थिर अक्षर *desc;
	पूर्णांक i, retval;

	WARN_CONSOLE_UNLOCKED();

	अगर (!try_module_get(owner))
		वापस -ENODEV;

	क्रम (i = 0; i < MAX_NR_CON_DRIVER; i++) अणु
		con_driver = &रेजिस्टरed_con_driver[i];

		/* alपढ़ोy रेजिस्टरed */
		अगर (con_driver->con == csw) अणु
			retval = -EBUSY;
			जाओ err;
		पूर्ण
	पूर्ण

	desc = csw->con_startup();
	अगर (!desc) अणु
		retval = -ENODEV;
		जाओ err;
	पूर्ण

	retval = -EINVAL;

	क्रम (i = 0; i < MAX_NR_CON_DRIVER; i++) अणु
		con_driver = &रेजिस्टरed_con_driver[i];

		अगर (con_driver->con == शून्य &&
		    !(con_driver->flag & CON_DRIVER_FLAG_ZOMBIE)) अणु
			con_driver->con = csw;
			con_driver->desc = desc;
			con_driver->node = i;
			con_driver->flag = CON_DRIVER_FLAG_MODULE |
			                   CON_DRIVER_FLAG_INIT;
			con_driver->first = first;
			con_driver->last = last;
			retval = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (retval)
		जाओ err;

	con_driver->dev =
		device_create_with_groups(vtconsole_class, शून्य,
					  MKDEV(0, con_driver->node),
					  con_driver, con_dev_groups,
					  "vtcon%i", con_driver->node);
	अगर (IS_ERR(con_driver->dev)) अणु
		pr_warn("Unable to create device for %s; errno = %ld\n",
			con_driver->desc, PTR_ERR(con_driver->dev));
		con_driver->dev = शून्य;
	पूर्ण अन्यथा अणु
		vtconsole_init_device(con_driver);
	पूर्ण

err:
	module_put(owner);
	वापस retval;
पूर्ण


/**
 * करो_unरेजिस्टर_con_driver - unरेजिस्टर console driver from console layer
 * @csw: console driver
 *
 * DESCRIPTION: All drivers that रेजिस्टरs to the console layer must
 * call this function upon निकास, or अगर the console driver is in a state
 * where it won't be able to handle console services, such as the
 * framebuffer console without loaded framebuffer drivers.
 *
 * The driver must unbind first prior to unregistration.
 */
पूर्णांक करो_unरेजिस्टर_con_driver(स्थिर काष्ठा consw *csw)
अणु
	पूर्णांक i;

	/* cannot unरेजिस्टर a bound driver */
	अगर (con_is_bound(csw))
		वापस -EBUSY;

	अगर (csw == conचयनp)
		वापस -EINVAL;

	क्रम (i = 0; i < MAX_NR_CON_DRIVER; i++) अणु
		काष्ठा con_driver *con_driver = &रेजिस्टरed_con_driver[i];

		अगर (con_driver->con == csw) अणु
			/*
			 * Defer the removal of the sysfs entries since that
			 * will acquire the kernfs s_active lock and we can't
			 * acquire this lock जबतक holding the console lock:
			 * the unbind sysfs entry imposes alपढ़ोy the opposite
			 * order. Reset con alपढ़ोy here to prevent any later
			 * lookup to succeed and mark this slot as zombie, so
			 * it won't get reused until we complete the removal
			 * in the deferred work.
			 */
			con_driver->con = शून्य;
			con_driver->flag = CON_DRIVER_FLAG_ZOMBIE;
			schedule_work(&con_driver_unरेजिस्टर_work);

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(करो_unरेजिस्टर_con_driver);

अटल व्योम con_driver_unरेजिस्टर_callback(काष्ठा work_काष्ठा *ignored)
अणु
	पूर्णांक i;

	console_lock();

	क्रम (i = 0; i < MAX_NR_CON_DRIVER; i++) अणु
		काष्ठा con_driver *con_driver = &रेजिस्टरed_con_driver[i];

		अगर (!(con_driver->flag & CON_DRIVER_FLAG_ZOMBIE))
			जारी;

		console_unlock();

		vtconsole_deinit_device(con_driver);
		device_destroy(vtconsole_class, MKDEV(0, con_driver->node));

		console_lock();

		अगर (WARN_ON_ONCE(con_driver->con))
			con_driver->con = शून्य;
		con_driver->desc = शून्य;
		con_driver->dev = शून्य;
		con_driver->node = 0;
		WARN_ON_ONCE(con_driver->flag != CON_DRIVER_FLAG_ZOMBIE);
		con_driver->flag = 0;
		con_driver->first = 0;
		con_driver->last = 0;
	पूर्ण

	console_unlock();
पूर्ण

/*
 *	If we support more console drivers, this function is used
 *	when a driver wants to take over some existing consoles
 *	and become शेष driver क्रम newly खोलोed ones.
 *
 *	करो_take_over_console is basically a रेजिस्टर followed by bind
 */
पूर्णांक करो_take_over_console(स्थिर काष्ठा consw *csw, पूर्णांक first, पूर्णांक last, पूर्णांक deflt)
अणु
	पूर्णांक err;

	err = करो_रेजिस्टर_con_driver(csw, first, last);
	/*
	 * If we get an busy error we still want to bind the console driver
	 * and वापस success, as we may have unbound the console driver
	 * but not unरेजिस्टरed it.
	 */
	अगर (err == -EBUSY)
		err = 0;
	अगर (!err)
		करो_bind_con_driver(csw, first, last, deflt);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(करो_take_over_console);


/*
 * give_up_console is a wrapper to unरेजिस्टर_con_driver. It will only
 * work अगर driver is fully unbound.
 */
व्योम give_up_console(स्थिर काष्ठा consw *csw)
अणु
	console_lock();
	करो_unरेजिस्टर_con_driver(csw);
	console_unlock();
पूर्ण

अटल पूर्णांक __init vtconsole_class_init(व्योम)
अणु
	पूर्णांक i;

	vtconsole_class = class_create(THIS_MODULE, "vtconsole");
	अगर (IS_ERR(vtconsole_class)) अणु
		pr_warn("Unable to create vt console class; errno = %ld\n",
			PTR_ERR(vtconsole_class));
		vtconsole_class = शून्य;
	पूर्ण

	/* Add प्रणाली drivers to sysfs */
	क्रम (i = 0; i < MAX_NR_CON_DRIVER; i++) अणु
		काष्ठा con_driver *con = &रेजिस्टरed_con_driver[i];

		अगर (con->con && !con->dev) अणु
			con->dev =
				device_create_with_groups(vtconsole_class, शून्य,
							  MKDEV(0, con->node),
							  con, con_dev_groups,
							  "vtcon%i", con->node);

			अगर (IS_ERR(con->dev)) अणु
				pr_warn("Unable to create device for %s; errno = %ld\n",
					con->desc, PTR_ERR(con->dev));
				con->dev = शून्य;
			पूर्ण अन्यथा अणु
				vtconsole_init_device(con);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
postcore_initcall(vtconsole_class_init);

#पूर्ण_अगर

/*
 *	Screen blanking
 */

अटल पूर्णांक set_vesa_blanking(अक्षर __user *p)
अणु
	अचिन्हित पूर्णांक mode;

	अगर (get_user(mode, p + 1))
		वापस -EFAULT;

	vesa_blank_mode = (mode < 4) ? mode : 0;
	वापस 0;
पूर्ण

व्योम करो_blank_screen(पूर्णांक entering_gfx)
अणु
	काष्ठा vc_data *vc = vc_cons[fg_console].d;
	पूर्णांक i;

	might_sleep();

	WARN_CONSOLE_UNLOCKED();

	अगर (console_blanked) अणु
		अगर (blank_state == blank_vesa_रुको) अणु
			blank_state = blank_off;
			vc->vc_sw->con_blank(vc, vesa_blank_mode + 1, 0);
		पूर्ण
		वापस;
	पूर्ण

	/* entering graphics mode? */
	अगर (entering_gfx) अणु
		hide_cursor(vc);
		save_screen(vc);
		vc->vc_sw->con_blank(vc, -1, 1);
		console_blanked = fg_console + 1;
		blank_state = blank_off;
		set_origin(vc);
		वापस;
	पूर्ण

	blank_state = blank_off;

	/* करोn't blank graphics */
	अगर (vc->vc_mode != KD_TEXT) अणु
		console_blanked = fg_console + 1;
		वापस;
	पूर्ण

	hide_cursor(vc);
	del_समयr_sync(&console_समयr);
	blank_समयr_expired = 0;

	save_screen(vc);
	/* In हाल we need to reset origin, blanking hook वापसs 1 */
	i = vc->vc_sw->con_blank(vc, vesa_off_पूर्णांकerval ? 1 : (vesa_blank_mode + 1), 0);
	console_blanked = fg_console + 1;
	अगर (i)
		set_origin(vc);

	अगर (console_blank_hook && console_blank_hook(1))
		वापस;

	अगर (vesa_off_पूर्णांकerval && vesa_blank_mode) अणु
		blank_state = blank_vesa_रुको;
		mod_समयr(&console_समयr, jअगरfies + vesa_off_पूर्णांकerval);
	पूर्ण
	vt_event_post(VT_EVENT_BLANK, vc->vc_num, vc->vc_num);
पूर्ण
EXPORT_SYMBOL(करो_blank_screen);

/*
 * Called by समयr as well as from vt_console_driver
 */
व्योम करो_unblank_screen(पूर्णांक leaving_gfx)
अणु
	काष्ठा vc_data *vc;

	/* This should now always be called from a "sane" (पढ़ो: can schedule)
	 * context क्रम the sake of the low level drivers, except in the special
	 * हाल of oops_in_progress
	 */
	अगर (!oops_in_progress)
		might_sleep();

	WARN_CONSOLE_UNLOCKED();

	ignore_poke = 0;
	अगर (!console_blanked)
		वापस;
	अगर (!vc_cons_allocated(fg_console)) अणु
		/* impossible */
		pr_warn("unblank_screen: tty %d not allocated ??\n",
			fg_console + 1);
		वापस;
	पूर्ण
	vc = vc_cons[fg_console].d;
	अगर (vc->vc_mode != KD_TEXT)
		वापस; /* but leave console_blanked != 0 */

	अगर (blankपूर्णांकerval) अणु
		mod_समयr(&console_समयr, jअगरfies + (blankपूर्णांकerval * HZ));
		blank_state = blank_normal_रुको;
	पूर्ण

	console_blanked = 0;
	अगर (vc->vc_sw->con_blank(vc, 0, leaving_gfx))
		/* Low-level driver cannot restore -> करो it ourselves */
		update_screen(vc);
	अगर (console_blank_hook)
		console_blank_hook(0);
	set_palette(vc);
	set_cursor(vc);
	vt_event_post(VT_EVENT_UNBLANK, vc->vc_num, vc->vc_num);
पूर्ण
EXPORT_SYMBOL(करो_unblank_screen);

/*
 * This is called by the outside world to cause a क्रमced unblank, mostly क्रम
 * oopses. Currently, I just call करो_unblank_screen(0), but we could eventually
 * call it with 1 as an argument and so क्रमce a mode restore... that may समाप्त
 * X or at least garbage the screen but would also make the Oops visible...
 */
व्योम unblank_screen(व्योम)
अणु
	करो_unblank_screen(0);
पूर्ण

/*
 * We defer the समयr blanking to work queue so it can take the console mutex
 * (console operations can still happen at irq समय, but only from prपूर्णांकk which
 * has the console mutex. Not perfect yet, but better than no locking
 */
अटल व्योम blank_screen_t(काष्ठा समयr_list *unused)
अणु
	blank_समयr_expired = 1;
	schedule_work(&console_work);
पूर्ण

व्योम poke_blanked_console(व्योम)
अणु
	WARN_CONSOLE_UNLOCKED();

	/* Add this so we quickly catch whoever might call us in a non
	 * safe context. Nowadays, unblank_screen() isn't to be called in
	 * atomic contexts and is allowed to schedule (with the special हाल
	 * of oops_in_progress, but that isn't of any concern क्रम this
	 * function. --BenH.
	 */
	might_sleep();

	/* This isn't perfectly race मुक्त, but a race here would be mostly harmless,
	 * at worst, we'll do a spurious blank and it's unlikely
	 */
	del_समयr(&console_समयr);
	blank_समयr_expired = 0;

	अगर (ignore_poke || !vc_cons[fg_console].d || vc_cons[fg_console].d->vc_mode == KD_GRAPHICS)
		वापस;
	अगर (console_blanked)
		unblank_screen();
	अन्यथा अगर (blankपूर्णांकerval) अणु
		mod_समयr(&console_समयr, jअगरfies + (blankपूर्णांकerval * HZ));
		blank_state = blank_normal_रुको;
	पूर्ण
पूर्ण

/*
 *	Palettes
 */

अटल व्योम set_palette(काष्ठा vc_data *vc)
अणु
	WARN_CONSOLE_UNLOCKED();

	अगर (vc->vc_mode != KD_GRAPHICS && vc->vc_sw->con_set_palette)
		vc->vc_sw->con_set_palette(vc, color_table);
पूर्ण

/*
 * Load palette पूर्णांकo the DAC रेजिस्टरs. arg poपूर्णांकs to a colour
 * map, 3 bytes per colour, 16 colours, range from 0 to 255.
 */

पूर्णांक con_set_cmap(अचिन्हित अक्षर __user *arg)
अणु
	पूर्णांक i, j, k;
	अचिन्हित अक्षर colormap[3*16];

	अगर (copy_from_user(colormap, arg, माप(colormap)))
		वापस -EFAULT;

	console_lock();
	क्रम (i = k = 0; i < 16; i++) अणु
		शेष_red[i] = colormap[k++];
		शेष_grn[i] = colormap[k++];
		शेष_blu[i] = colormap[k++];
	पूर्ण
	क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
		अगर (!vc_cons_allocated(i))
			जारी;
		क्रम (j = k = 0; j < 16; j++) अणु
			vc_cons[i].d->vc_palette[k++] = शेष_red[j];
			vc_cons[i].d->vc_palette[k++] = शेष_grn[j];
			vc_cons[i].d->vc_palette[k++] = शेष_blu[j];
		पूर्ण
		set_palette(vc_cons[i].d);
	पूर्ण
	console_unlock();

	वापस 0;
पूर्ण

पूर्णांक con_get_cmap(अचिन्हित अक्षर __user *arg)
अणु
	पूर्णांक i, k;
	अचिन्हित अक्षर colormap[3*16];

	console_lock();
	क्रम (i = k = 0; i < 16; i++) अणु
		colormap[k++] = शेष_red[i];
		colormap[k++] = शेष_grn[i];
		colormap[k++] = शेष_blu[i];
	पूर्ण
	console_unlock();

	अगर (copy_to_user(arg, colormap, माप(colormap)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

व्योम reset_palette(काष्ठा vc_data *vc)
अणु
	पूर्णांक j, k;
	क्रम (j=k=0; j<16; j++) अणु
		vc->vc_palette[k++] = शेष_red[j];
		vc->vc_palette[k++] = शेष_grn[j];
		vc->vc_palette[k++] = शेष_blu[j];
	पूर्ण
	set_palette(vc);
पूर्ण

/*
 *  Font चयनing
 *
 *  Currently we only support fonts up to 32 pixels wide, at a maximum height
 *  of 32 pixels. Userspace fontdata is stored with 32 bytes (लघुs/पूर्णांकs, 
 *  depending on width) reserved क्रम each अक्षरacter which is kinda wasty, but 
 *  this is करोne in order to मुख्यtain compatibility with the EGA/VGA fonts. It 
 *  is up to the actual low-level console-driver convert data पूर्णांकo its favorite
 *  क्रमmat (maybe we should add a `fontoffset' field to the `display'
 *  काष्ठाure so we won't have to convert the fontdata all the समय.
 *  /Jes
 */

#घोषणा max_font_size 65536

अटल पूर्णांक con_font_get(काष्ठा vc_data *vc, काष्ठा console_font_op *op)
अणु
	काष्ठा console_font font;
	पूर्णांक rc = -EINVAL;
	पूर्णांक c;

	अगर (op->data) अणु
		font.data = kदो_स्मृति(max_font_size, GFP_KERNEL);
		अगर (!font.data)
			वापस -ENOMEM;
	पूर्ण अन्यथा
		font.data = शून्य;

	console_lock();
	अगर (vc->vc_mode != KD_TEXT)
		rc = -EINVAL;
	अन्यथा अगर (vc->vc_sw->con_font_get)
		rc = vc->vc_sw->con_font_get(vc, &font);
	अन्यथा
		rc = -ENOSYS;
	console_unlock();

	अगर (rc)
		जाओ out;

	c = (font.width+7)/8 * 32 * font.अक्षरcount;

	अगर (op->data && font.अक्षरcount > op->अक्षरcount)
		rc = -ENOSPC;
	अगर (font.width > op->width || font.height > op->height)
		rc = -ENOSPC;
	अगर (rc)
		जाओ out;

	op->height = font.height;
	op->width = font.width;
	op->अक्षरcount = font.अक्षरcount;

	अगर (op->data && copy_to_user(op->data, font.data, c))
		rc = -EFAULT;

out:
	kमुक्त(font.data);
	वापस rc;
पूर्ण

अटल पूर्णांक con_font_set(काष्ठा vc_data *vc, काष्ठा console_font_op *op)
अणु
	काष्ठा console_font font;
	पूर्णांक rc = -EINVAL;
	पूर्णांक size;

	अगर (vc->vc_mode != KD_TEXT)
		वापस -EINVAL;
	अगर (!op->data)
		वापस -EINVAL;
	अगर (op->अक्षरcount > 512)
		वापस -EINVAL;
	अगर (op->width <= 0 || op->width > 32 || !op->height || op->height > 32)
		वापस -EINVAL;
	size = (op->width+7)/8 * 32 * op->अक्षरcount;
	अगर (size > max_font_size)
		वापस -ENOSPC;

	font.data = memdup_user(op->data, size);
	अगर (IS_ERR(font.data))
		वापस PTR_ERR(font.data);

	font.अक्षरcount = op->अक्षरcount;
	font.width = op->width;
	font.height = op->height;

	console_lock();
	अगर (vc->vc_mode != KD_TEXT)
		rc = -EINVAL;
	अन्यथा अगर (vc->vc_sw->con_font_set)
		rc = vc->vc_sw->con_font_set(vc, &font, op->flags);
	अन्यथा
		rc = -ENOSYS;
	console_unlock();
	kमुक्त(font.data);
	वापस rc;
पूर्ण

अटल पूर्णांक con_font_शेष(काष्ठा vc_data *vc, काष्ठा console_font_op *op)
अणु
	काष्ठा console_font font = अणु.width = op->width, .height = op->heightपूर्ण;
	अक्षर name[MAX_FONT_NAME];
	अक्षर *s = name;
	पूर्णांक rc;


	अगर (!op->data)
		s = शून्य;
	अन्यथा अगर (म_नकलन_from_user(name, op->data, MAX_FONT_NAME - 1) < 0)
		वापस -EFAULT;
	अन्यथा
		name[MAX_FONT_NAME - 1] = 0;

	console_lock();
	अगर (vc->vc_mode != KD_TEXT) अणु
		console_unlock();
		वापस -EINVAL;
	पूर्ण
	अगर (vc->vc_sw->con_font_शेष)
		rc = vc->vc_sw->con_font_शेष(vc, &font, s);
	अन्यथा
		rc = -ENOSYS;
	console_unlock();
	अगर (!rc) अणु
		op->width = font.width;
		op->height = font.height;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक con_font_op(काष्ठा vc_data *vc, काष्ठा console_font_op *op)
अणु
	चयन (op->op) अणु
	हाल KD_FONT_OP_SET:
		वापस con_font_set(vc, op);
	हाल KD_FONT_OP_GET:
		वापस con_font_get(vc, op);
	हाल KD_FONT_OP_SET_DEFAULT:
		वापस con_font_शेष(vc, op);
	हाल KD_FONT_OP_COPY:
		/* was buggy and never really used */
		वापस -EINVAL;
	पूर्ण
	वापस -ENOSYS;
पूर्ण

/*
 *	Interface exported to selection and vcs.
 */

/* used by selection */
u16 screen_glyph(स्थिर काष्ठा vc_data *vc, पूर्णांक offset)
अणु
	u16 w = scr_पढ़ोw(screenpos(vc, offset, true));
	u16 c = w & 0xff;

	अगर (w & vc->vc_hi_font_mask)
		c |= 0x100;
	वापस c;
पूर्ण
EXPORT_SYMBOL_GPL(screen_glyph);

u32 screen_glyph_unicode(स्थिर काष्ठा vc_data *vc, पूर्णांक n)
अणु
	काष्ठा uni_screen *uniscr = get_vc_uniscr(vc);

	अगर (uniscr)
		वापस uniscr->lines[n / vc->vc_cols][n % vc->vc_cols];
	वापस inverse_translate(vc, screen_glyph(vc, n * 2), 1);
पूर्ण
EXPORT_SYMBOL_GPL(screen_glyph_unicode);

/* used by vcs - note the word offset */
अचिन्हित लघु *screen_pos(स्थिर काष्ठा vc_data *vc, पूर्णांक w_offset, bool viewed)
अणु
	वापस screenpos(vc, 2 * w_offset, viewed);
पूर्ण
EXPORT_SYMBOL_GPL(screen_pos);

व्योम अ_लोonsxy(स्थिर काष्ठा vc_data *vc, अचिन्हित अक्षर xy[अटल 2])
अणु
	/* clamp values अगर they करोn't fit */
	xy[0] = min(vc->state.x, 0xFFu);
	xy[1] = min(vc->state.y, 0xFFu);
पूर्ण

व्योम अ_दोonsxy(काष्ठा vc_data *vc, अचिन्हित अक्षर xy[अटल स्थिर 2])
अणु
	hide_cursor(vc);
	जाओxy(vc, xy[0], xy[1]);
	set_cursor(vc);
पूर्ण

u16 vcs_scr_पढ़ोw(स्थिर काष्ठा vc_data *vc, स्थिर u16 *org)
अणु
	अगर ((अचिन्हित दीर्घ)org == vc->vc_pos && softcursor_original != -1)
		वापस softcursor_original;
	वापस scr_पढ़ोw(org);
पूर्ण

व्योम vcs_scr_ग_लिखोw(काष्ठा vc_data *vc, u16 val, u16 *org)
अणु
	scr_ग_लिखोw(val, org);
	अगर ((अचिन्हित दीर्घ)org == vc->vc_pos) अणु
		softcursor_original = -1;
		add_softcursor(vc);
	पूर्ण
पूर्ण

व्योम vcs_scr_updated(काष्ठा vc_data *vc)
अणु
	notअगरy_update(vc);
पूर्ण

व्योम vc_scrolldelta_helper(काष्ठा vc_data *c, पूर्णांक lines,
		अचिन्हित पूर्णांक rolled_over, व्योम *base, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित दीर्घ ubase = (अचिन्हित दीर्घ)base;
	सूचक_भेद_प्रकार scr_end = (व्योम *)c->vc_scr_end - base;
	सूचक_भेद_प्रकार vorigin = (व्योम *)c->vc_visible_origin - base;
	सूचक_भेद_प्रकार origin = (व्योम *)c->vc_origin - base;
	पूर्णांक margin = c->vc_size_row * 4;
	पूर्णांक from, wrap, from_off, avail;

	/* Turn scrollback off */
	अगर (!lines) अणु
		c->vc_visible_origin = c->vc_origin;
		वापस;
	पूर्ण

	/* Do we have alपढ़ोy enough to allow jumping from 0 to the end? */
	अगर (rolled_over > scr_end + margin) अणु
		from = scr_end;
		wrap = rolled_over + c->vc_size_row;
	पूर्ण अन्यथा अणु
		from = 0;
		wrap = size;
	पूर्ण

	from_off = (vorigin - from + wrap) % wrap + lines * c->vc_size_row;
	avail = (origin - from + wrap) % wrap;

	/* Only a little piece would be left? Show all incl. the piece! */
	अगर (avail < 2 * margin)
		margin = 0;
	अगर (from_off < margin)
		from_off = 0;
	अगर (from_off > avail - margin)
		from_off = avail;

	c->vc_visible_origin = ubase + (from + from_off) % wrap;
पूर्ण
EXPORT_SYMBOL_GPL(vc_scrolldelta_helper);

/*
 *	Visible symbols क्रम modules
 */

EXPORT_SYMBOL(color_table);
EXPORT_SYMBOL(शेष_red);
EXPORT_SYMBOL(शेष_grn);
EXPORT_SYMBOL(शेष_blu);
EXPORT_SYMBOL(update_region);
EXPORT_SYMBOL(redraw_screen);
EXPORT_SYMBOL(vc_resize);
EXPORT_SYMBOL(fg_console);
EXPORT_SYMBOL(console_blank_hook);
EXPORT_SYMBOL(console_blanked);
EXPORT_SYMBOL(vc_cons);
EXPORT_SYMBOL(global_cursor_शेष);
#अगर_अघोषित VT_SINGLE_DRIVER
EXPORT_SYMBOL(give_up_console);
#पूर्ण_अगर
