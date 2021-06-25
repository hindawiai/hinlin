<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This module exports the functions:
 *
 *     'पूर्णांक set_selection_user(काष्ठा tiocl_selection __user *,
 *			       काष्ठा tty_काष्ठा *)'
 *     'int set_selection_kernel(struct tiocl_selection *, struct tty_struct *)'
 *     'void clear_selection(void)'
 *     'int paste_selection(struct tty_struct *)'
 *     'int sel_loadlut(char __user *)'
 *
 * Now that /dev/vcs exists, most of this can disappear again.
 */

#समावेश <linux/module.h>
#समावेश <linux/tty.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <linux/uaccess.h>

#समावेश <linux/kbd_kern.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/consolemap.h>
#समावेश <linux/selection.h>
#समावेश <linux/tiocl.h>
#समावेश <linux/console.h>
#समावेश <linux/tty_flip.h>

#समावेश <linux/sched/संकेत.स>

/* Don't take this from <ctype.h>: 011-015 on the screen aren't spaces */
#घोषणा है_खाली(c)	((c) == ' ')

/* FIXME: all this needs locking */
अटल काष्ठा vc_selection अणु
	काष्ठा mutex lock;
	काष्ठा vc_data *cons;			/* must not be deallocated */
	अक्षर *buffer;
	अचिन्हित पूर्णांक buf_len;
	अस्थिर पूर्णांक start;			/* cleared by clear_selection */
	पूर्णांक end;
पूर्ण vc_sel = अणु
	.lock = __MUTEX_INITIALIZER(vc_sel.lock),
	.start = -1,
पूर्ण;

/* clear_selection, highlight and highlight_poपूर्णांकer can be called
   from पूर्णांकerrupt (via scrollback/front) */

/* set reverse video on अक्षरacters s-e of console with selection. */
अटल अंतरभूत व्योम highlight(स्थिर पूर्णांक s, स्थिर पूर्णांक e)
अणु
	invert_screen(vc_sel.cons, s, e-s+2, true);
पूर्ण

/* use complementary color to show the poपूर्णांकer */
अटल अंतरभूत व्योम highlight_poपूर्णांकer(स्थिर पूर्णांक where)
अणु
	complement_pos(vc_sel.cons, where);
पूर्ण

अटल u32
sel_pos(पूर्णांक n, bool unicode)
अणु
	अगर (unicode)
		वापस screen_glyph_unicode(vc_sel.cons, n / 2);
	वापस inverse_translate(vc_sel.cons, screen_glyph(vc_sel.cons, n), 0);
पूर्ण

/**
 *	clear_selection		-	हटाओ current selection
 *
 *	Remove the current selection highlight, अगर any from the console
 *	holding the selection. The caller must hold the console lock.
 */
व्योम clear_selection(व्योम)
अणु
	highlight_poपूर्णांकer(-1); /* hide the poपूर्णांकer */
	अगर (vc_sel.start != -1) अणु
		highlight(vc_sel.start, vc_sel.end);
		vc_sel.start = -1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(clear_selection);

bool vc_is_sel(काष्ठा vc_data *vc)
अणु
	वापस vc == vc_sel.cons;
पूर्ण

/*
 * User settable table: what अक्षरacters are to be considered alphabetic?
 * 128 bits. Locked by the console lock.
 */
अटल u32 inwordLut[]=अणु
  0x00000000, /* control अक्षरs     */
  0x03FFE000, /* digits and "-./"  */
  0x87FFFFFE, /* upperहाल and '_' */
  0x07FFFFFE, /* lowerहाल         */
पूर्ण;

अटल अंतरभूत पूर्णांक inword(स्थिर u32 c)
अणु
	वापस c > 0x7f || (( inwordLut[c>>5] >> (c & 0x1F) ) & 1);
पूर्ण

/**
 *	set loadlut		-	load the LUT table
 *	@p: user table
 *
 *	Load the LUT table from user space. The caller must hold the console
 *	lock. Make a temporary copy so a partial update करोesn't make a mess.
 */
पूर्णांक sel_loadlut(अक्षर __user *p)
अणु
	u32 पंचांगplut[ARRAY_SIZE(inwordLut)];
	अगर (copy_from_user(पंचांगplut, (u32 __user *)(p+4), माप(inwordLut)))
		वापस -EFAULT;
	स_नकल(inwordLut, पंचांगplut, माप(inwordLut));
	वापस 0;
पूर्ण

/* करोes screen address p correspond to अक्षरacter at LH/RH edge of screen? */
अटल अंतरभूत पूर्णांक atedge(स्थिर पूर्णांक p, पूर्णांक size_row)
अणु
	वापस (!(p % size_row)	|| !((p + 2) % size_row));
पूर्ण

/* stores the अक्षर in UTF8 and वापसs the number of bytes used (1-4) */
अटल पूर्णांक store_utf8(u32 c, अक्षर *p)
अणु
	अगर (c < 0x80) अणु
		/*  0******* */
		p[0] = c;
		वापस 1;
	पूर्ण अन्यथा अगर (c < 0x800) अणु
		/* 110***** 10****** */
		p[0] = 0xc0 | (c >> 6);
		p[1] = 0x80 | (c & 0x3f);
		वापस 2;
	पूर्ण अन्यथा अगर (c < 0x10000) अणु
		/* 1110**** 10****** 10****** */
		p[0] = 0xe0 | (c >> 12);
		p[1] = 0x80 | ((c >> 6) & 0x3f);
		p[2] = 0x80 | (c & 0x3f);
		वापस 3;
	पूर्ण अन्यथा अगर (c < 0x110000) अणु
		/* 11110*** 10****** 10****** 10****** */
		p[0] = 0xf0 | (c >> 18);
		p[1] = 0x80 | ((c >> 12) & 0x3f);
		p[2] = 0x80 | ((c >> 6) & 0x3f);
		p[3] = 0x80 | (c & 0x3f);
		वापस 4;
	पूर्ण अन्यथा अणु
		/* outside Unicode, replace with U+FFFD */
		p[0] = 0xef;
		p[1] = 0xbf;
		p[2] = 0xbd;
		वापस 3;
	पूर्ण
पूर्ण

/**
 *	set_selection_user	-	set the current selection.
 *	@sel: user selection info
 *	@tty: the console tty
 *
 *	Invoked by the ioctl handle क्रम the vt layer.
 *
 *	The entire selection process is managed under the console_lock. It's
 *	 a lot under the lock but its hardly a perक्रमmance path
 */
पूर्णांक set_selection_user(स्थिर काष्ठा tiocl_selection __user *sel,
		       काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा tiocl_selection v;

	अगर (copy_from_user(&v, sel, माप(*sel)))
		वापस -EFAULT;

	वापस set_selection_kernel(&v, tty);
पूर्ण

अटल पूर्णांक vc_selection_store_अक्षरs(काष्ठा vc_data *vc, bool unicode)
अणु
	अक्षर *bp, *obp;
	अचिन्हित पूर्णांक i;

	/* Allocate a new buffer beक्रमe मुक्तing the old one ... */
	/* अक्षरs can take up to 4 bytes with unicode */
	bp = kदो_स्मृति_array((vc_sel.end - vc_sel.start) / 2 + 1, unicode ? 4 : 1,
			   GFP_KERNEL | __GFP_NOWARN);
	अगर (!bp) अणु
		prपूर्णांकk(KERN_WARNING "selection: kmalloc() failed\n");
		clear_selection();
		वापस -ENOMEM;
	पूर्ण
	kमुक्त(vc_sel.buffer);
	vc_sel.buffer = bp;

	obp = bp;
	क्रम (i = vc_sel.start; i <= vc_sel.end; i += 2) अणु
		u32 c = sel_pos(i, unicode);
		अगर (unicode)
			bp += store_utf8(c, bp);
		अन्यथा
			*bp++ = c;
		अगर (!है_खाली(c))
			obp = bp;
		अगर (!((i + 2) % vc->vc_size_row)) अणु
			/* strip trailing blanks from line and add newline,
			   unless non-space at end of line. */
			अगर (obp != bp) अणु
				bp = obp;
				*bp++ = '\r';
			पूर्ण
			obp = bp;
		पूर्ण
	पूर्ण
	vc_sel.buf_len = bp - vc_sel.buffer;

	वापस 0;
पूर्ण

अटल पूर्णांक vc_करो_selection(काष्ठा vc_data *vc, अचिन्हित लघु mode, पूर्णांक ps,
		पूर्णांक pe)
अणु
	पूर्णांक new_sel_start, new_sel_end, spc;
	bool unicode = vt_करो_kdgkbmode(fg_console) == K_UNICODE;

	चयन (mode) अणु
	हाल TIOCL_SELCHAR:	/* अक्षरacter-by-अक्षरacter selection */
		new_sel_start = ps;
		new_sel_end = pe;
		अवरोध;
	हाल TIOCL_SELWORD:	/* word-by-word selection */
		spc = है_खाली(sel_pos(ps, unicode));
		क्रम (new_sel_start = ps; ; ps -= 2) अणु
			अगर ((spc && !है_खाली(sel_pos(ps, unicode))) ||
			    (!spc && !inword(sel_pos(ps, unicode))))
				अवरोध;
			new_sel_start = ps;
			अगर (!(ps % vc->vc_size_row))
				अवरोध;
		पूर्ण

		spc = है_खाली(sel_pos(pe, unicode));
		क्रम (new_sel_end = pe; ; pe += 2) अणु
			अगर ((spc && !है_खाली(sel_pos(pe, unicode))) ||
			    (!spc && !inword(sel_pos(pe, unicode))))
				अवरोध;
			new_sel_end = pe;
			अगर (!((pe + 2) % vc->vc_size_row))
				अवरोध;
		पूर्ण
		अवरोध;
	हाल TIOCL_SELLINE:	/* line-by-line selection */
		new_sel_start = roundकरोwn(ps, vc->vc_size_row);
		new_sel_end = roundकरोwn(pe, vc->vc_size_row) +
			vc->vc_size_row - 2;
		अवरोध;
	हाल TIOCL_SELPOINTER:
		highlight_poपूर्णांकer(pe);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* हटाओ the poपूर्णांकer */
	highlight_poपूर्णांकer(-1);

	/* select to end of line अगर on trailing space */
	अगर (new_sel_end > new_sel_start &&
		!atedge(new_sel_end, vc->vc_size_row) &&
		है_खाली(sel_pos(new_sel_end, unicode))) अणु
		क्रम (pe = new_sel_end + 2; ; pe += 2)
			अगर (!है_खाली(sel_pos(pe, unicode)) ||
			    atedge(pe, vc->vc_size_row))
				अवरोध;
		अगर (है_खाली(sel_pos(pe, unicode)))
			new_sel_end = pe;
	पूर्ण
	अगर (vc_sel.start == -1)	/* no current selection */
		highlight(new_sel_start, new_sel_end);
	अन्यथा अगर (new_sel_start == vc_sel.start)
	अणु
		अगर (new_sel_end == vc_sel.end)	/* no action required */
			वापस 0;
		अन्यथा अगर (new_sel_end > vc_sel.end)	/* extend to right */
			highlight(vc_sel.end + 2, new_sel_end);
		अन्यथा				/* contract from right */
			highlight(new_sel_end + 2, vc_sel.end);
	पूर्ण
	अन्यथा अगर (new_sel_end == vc_sel.end)
	अणु
		अगर (new_sel_start < vc_sel.start) /* extend to left */
			highlight(new_sel_start, vc_sel.start - 2);
		अन्यथा				/* contract from left */
			highlight(vc_sel.start, new_sel_start - 2);
	पूर्ण
	अन्यथा	/* some other हाल; start selection from scratch */
	अणु
		clear_selection();
		highlight(new_sel_start, new_sel_end);
	पूर्ण
	vc_sel.start = new_sel_start;
	vc_sel.end = new_sel_end;

	वापस vc_selection_store_अक्षरs(vc, unicode);
पूर्ण

अटल पूर्णांक vc_selection(काष्ठा vc_data *vc, काष्ठा tiocl_selection *v,
		काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक ps, pe;

	poke_blanked_console();

	अगर (v->sel_mode == TIOCL_SELCLEAR) अणु
		/* useful क्रम screendump without selection highlights */
		clear_selection();
		वापस 0;
	पूर्ण

	v->xs = min_t(u16, v->xs - 1, vc->vc_cols - 1);
	v->ys = min_t(u16, v->ys - 1, vc->vc_rows - 1);
	v->xe = min_t(u16, v->xe - 1, vc->vc_cols - 1);
	v->ye = min_t(u16, v->ye - 1, vc->vc_rows - 1);

	अगर (mouse_reporting() && (v->sel_mode & TIOCL_SELMOUSEREPORT)) अणु
		mouse_report(tty, v->sel_mode & TIOCL_SELBUTTONMASK, v->xs,
			     v->ys);
		वापस 0;
	पूर्ण

	ps = v->ys * vc->vc_size_row + (v->xs << 1);
	pe = v->ye * vc->vc_size_row + (v->xe << 1);
	अगर (ps > pe)	/* make vc_sel.start <= vc_sel.end */
		swap(ps, pe);

	अगर (vc_sel.cons != vc) अणु
		clear_selection();
		vc_sel.cons = vc;
	पूर्ण

	वापस vc_करो_selection(vc, v->sel_mode, ps, pe);
पूर्ण

पूर्णांक set_selection_kernel(काष्ठा tiocl_selection *v, काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक ret;

	mutex_lock(&vc_sel.lock);
	console_lock();
	ret = vc_selection(vc_cons[fg_console].d, v, tty);
	console_unlock();
	mutex_unlock(&vc_sel.lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(set_selection_kernel);

/* Insert the contents of the selection buffer पूर्णांकo the
 * queue of the tty associated with the current console.
 * Invoked by ioctl().
 *
 * Locking: called without locks. Calls the ldisc wrongly with
 * unsafe methods,
 */
पूर्णांक paste_selection(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा vc_data *vc = tty->driver_data;
	पूर्णांक	pasted = 0;
	अचिन्हित पूर्णांक count;
	काष्ठा  tty_ldisc *ld;
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक ret = 0;

	console_lock();
	poke_blanked_console();
	console_unlock();

	ld = tty_ldisc_ref_रुको(tty);
	अगर (!ld)
		वापस -EIO;	/* ldisc was hung up */
	tty_buffer_lock_exclusive(&vc->port);

	add_रुको_queue(&vc->paste_रुको, &रुको);
	mutex_lock(&vc_sel.lock);
	जबतक (vc_sel.buffer && vc_sel.buf_len > pasted) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (संकेत_pending(current)) अणु
			ret = -EINTR;
			अवरोध;
		पूर्ण
		अगर (tty_throttled(tty)) अणु
			mutex_unlock(&vc_sel.lock);
			schedule();
			mutex_lock(&vc_sel.lock);
			जारी;
		पूर्ण
		__set_current_state(TASK_RUNNING);
		count = vc_sel.buf_len - pasted;
		count = tty_ldisc_receive_buf(ld, vc_sel.buffer + pasted, शून्य,
					      count);
		pasted += count;
	पूर्ण
	mutex_unlock(&vc_sel.lock);
	हटाओ_रुको_queue(&vc->paste_रुको, &रुको);
	__set_current_state(TASK_RUNNING);

	tty_buffer_unlock_exclusive(&vc->port);
	tty_ldisc_deref(ld);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(paste_selection);
