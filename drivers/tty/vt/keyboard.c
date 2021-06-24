<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Written क्रम linux by Johan Myreen as a translation from
 * the assembly version by Linus (with diacriticals added)
 *
 * Some additional features added by Christoph Niemann (ChN), March 1993
 *
 * Loadable keymaps by Risto Kankkunen, May 1993
 *
 * Diacriticals reकरोne & other small changes, aeb@cwi.nl, June 1993
 * Added decr/incr_console, dynamic keymaps, Unicode support,
 * dynamic function/string keys, led setting,  Sept 1994
 * `Sticky' modअगरier keys, 951006.
 *
 * 11-11-96: SAK should now work in the raw mode (Martin Mares)
 *
 * Modअगरied to provide 'generic' keyboard support by Hamish Macकरोnald
 * Merge with the m68k keyboard driver and split-off of the PC low-level
 * parts by Geert Uytterhoeven, May 1997
 *
 * 27-05-97: Added support क्रम the Magic SysRq Key (Martin Mares)
 * 30-07-98: Dead keys reकरोne, aeb@cwi.nl.
 * 21-08-02: Converted to input API, major cleanup. (Vojtech Pavlik)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/consolemap.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kbd_diacr.h>
#समावेश <linux/kbd_kern.h>
#समावेश <linux/leds.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/nospec.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/tty_flip.h>
#समावेश <linux/tty.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vt_kern.h>

#समावेश <यंत्र/irq_regs.h>

/*
 * Exported functions/variables
 */

#घोषणा KBD_DEFMODE (BIT(VC_REPEAT) | BIT(VC_META))

#अगर defined(CONFIG_X86) || defined(CONFIG_PARISC)
#समावेश <यंत्र/kbdleds.h>
#अन्यथा
अटल अंतरभूत पूर्णांक kbd_defleds(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा KBD_DEFLOCK 0

/*
 * Handler Tables.
 */

#घोषणा K_HANDLERS\
	k_self,		k_fn,		k_spec,		k_pad,\
	k_dead,		k_cons,		k_cur,		k_shअगरt,\
	k_meta,		k_ascii,	k_lock,		k_lowerहाल,\
	k_slock,	k_dead2,	k_brl,		k_ignore

प्रकार व्योम (k_handler_fn)(काष्ठा vc_data *vc, अचिन्हित अक्षर value,
			    अक्षर up_flag);
अटल k_handler_fn K_HANDLERS;
अटल k_handler_fn *k_handler[16] = अणु K_HANDLERS पूर्ण;

#घोषणा FN_HANDLERS\
	fn_null,	fn_enter,	fn_show_ptregs,	fn_show_mem,\
	fn_show_state,	fn_send_पूर्णांकr,	fn_lastcons,	fn_caps_toggle,\
	fn_num,		fn_hold,	fn_scroll_क्रमw,	fn_scroll_back,\
	fn_boot_it,	fn_caps_on,	fn_compose,	fn_SAK,\
	fn_dec_console, fn_inc_console, fn_spawn_con,	fn_bare_num

प्रकार व्योम (fn_handler_fn)(काष्ठा vc_data *vc);
अटल fn_handler_fn FN_HANDLERS;
अटल fn_handler_fn *fn_handler[] = अणु FN_HANDLERS पूर्ण;

/*
 * Variables exported क्रम vt_ioctl.c
 */

काष्ठा vt_spawn_console vt_spawn_con = अणु
	.lock = __SPIN_LOCK_UNLOCKED(vt_spawn_con.lock),
	.pid  = शून्य,
	.sig  = 0,
पूर्ण;


/*
 * Internal Data.
 */

अटल काष्ठा kbd_काष्ठा kbd_table[MAX_NR_CONSOLES];
अटल काष्ठा kbd_काष्ठा *kbd = kbd_table;

/* maximum values each key_handler can handle */
अटल स्थिर अचिन्हित अक्षर max_vals[] = अणु
	[ KT_LATIN	] = 255,
	[ KT_FN		] = ARRAY_SIZE(func_table) - 1,
	[ KT_SPEC	] = ARRAY_SIZE(fn_handler) - 1,
	[ KT_PAD	] = NR_PAD - 1,
	[ KT_DEAD	] = NR_DEAD - 1,
	[ KT_CONS	] = 255,
	[ KT_CUR	] = 3,
	[ KT_SHIFT	] = NR_SHIFT - 1,
	[ KT_META	] = 255,
	[ KT_ASCII	] = NR_ASCII - 1,
	[ KT_LOCK	] = NR_LOCK - 1,
	[ KT_LETTER	] = 255,
	[ KT_SLOCK	] = NR_LOCK - 1,
	[ KT_DEAD2	] = 255,
	[ KT_BRL	] = NR_BRL - 1,
पूर्ण;

अटल स्थिर पूर्णांक NR_TYPES = ARRAY_SIZE(max_vals);

अटल व्योम kbd_bh(काष्ठा tasklet_काष्ठा *unused);
अटल DECLARE_TASKLET_DISABLED(keyboard_tasklet, kbd_bh);

अटल काष्ठा input_handler kbd_handler;
अटल DEFINE_SPINLOCK(kbd_event_lock);
अटल DEFINE_SPINLOCK(led_lock);
अटल DEFINE_SPINLOCK(func_buf_lock); /* guard 'func_buf'  and मित्रs */
अटल DECLARE_BITMAP(key_करोwn, KEY_CNT);	/* keyboard key biपंचांगap */
अटल अचिन्हित अक्षर shअगरt_करोwn[NR_SHIFT];		/* shअगरt state counters.. */
अटल bool dead_key_next;

/* Handles a number being assembled on the number pad */
अटल bool npadch_active;
अटल अचिन्हित पूर्णांक npadch_value;

अटल अचिन्हित पूर्णांक diacr;
अटल bool rep;			/* flag telling अक्षरacter repeat */

अटल पूर्णांक shअगरt_state = 0;

अटल अचिन्हित पूर्णांक ledstate = -1U;			/* undefined */
अटल अचिन्हित अक्षर ledioctl;

/*
 * Notअगरier list क्रम console keyboard events
 */
अटल ATOMIC_NOTIFIER_HEAD(keyboard_notअगरier_list);

पूर्णांक रेजिस्टर_keyboard_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&keyboard_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_keyboard_notअगरier);

पूर्णांक unरेजिस्टर_keyboard_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&keyboard_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_keyboard_notअगरier);

/*
 * Translation of scancodes to keycodes. We set them on only the first
 * keyboard in the list that accepts the scancode and keycode.
 * Explanation क्रम not choosing the first attached keyboard anymore:
 *  USB keyboards क्रम example have two event devices: one क्रम all "normal"
 *  keys and one क्रम extra function keys (like "volume up", "make coffee",
 *  etc.). So this means that scancodes क्रम the extra function keys won't
 *  be valid क्रम the first event device, but will be क्रम the second.
 */

काष्ठा माला_लोet_keycode_data अणु
	काष्ठा input_keymap_entry ke;
	पूर्णांक error;
पूर्ण;

अटल पूर्णांक getkeycode_helper(काष्ठा input_handle *handle, व्योम *data)
अणु
	काष्ठा माला_लोet_keycode_data *d = data;

	d->error = input_get_keycode(handle->dev, &d->ke);

	वापस d->error == 0; /* stop as soon as we successfully get one */
पूर्ण

अटल पूर्णांक getkeycode(अचिन्हित पूर्णांक scancode)
अणु
	काष्ठा माला_लोet_keycode_data d = अणु
		.ke	= अणु
			.flags		= 0,
			.len		= माप(scancode),
			.keycode	= 0,
		पूर्ण,
		.error	= -ENODEV,
	पूर्ण;

	स_नकल(d.ke.scancode, &scancode, माप(scancode));

	input_handler_क्रम_each_handle(&kbd_handler, &d, getkeycode_helper);

	वापस d.error ?: d.ke.keycode;
पूर्ण

अटल पूर्णांक setkeycode_helper(काष्ठा input_handle *handle, व्योम *data)
अणु
	काष्ठा माला_लोet_keycode_data *d = data;

	d->error = input_set_keycode(handle->dev, &d->ke);

	वापस d->error == 0; /* stop as soon as we successfully set one */
पूर्ण

अटल पूर्णांक setkeycode(अचिन्हित पूर्णांक scancode, अचिन्हित पूर्णांक keycode)
अणु
	काष्ठा माला_लोet_keycode_data d = अणु
		.ke	= अणु
			.flags		= 0,
			.len		= माप(scancode),
			.keycode	= keycode,
		पूर्ण,
		.error	= -ENODEV,
	पूर्ण;

	स_नकल(d.ke.scancode, &scancode, माप(scancode));

	input_handler_क्रम_each_handle(&kbd_handler, &d, setkeycode_helper);

	वापस d.error;
पूर्ण

/*
 * Making beeps and bells. Note that we prefer beeps to bells, but when
 * shutting the sound off we करो both.
 */

अटल पूर्णांक kd_sound_helper(काष्ठा input_handle *handle, व्योम *data)
अणु
	अचिन्हित पूर्णांक *hz = data;
	काष्ठा input_dev *dev = handle->dev;

	अगर (test_bit(EV_SND, dev->evbit)) अणु
		अगर (test_bit(SND_TONE, dev->sndbit)) अणु
			input_inject_event(handle, EV_SND, SND_TONE, *hz);
			अगर (*hz)
				वापस 0;
		पूर्ण
		अगर (test_bit(SND_BELL, dev->sndbit))
			input_inject_event(handle, EV_SND, SND_BELL, *hz ? 1 : 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kd_nosound(काष्ठा समयr_list *unused)
अणु
	अटल अचिन्हित पूर्णांक zero;

	input_handler_क्रम_each_handle(&kbd_handler, &zero, kd_sound_helper);
पूर्ण

अटल DEFINE_TIMER(kd_mksound_समयr, kd_nosound);

व्योम kd_mksound(अचिन्हित पूर्णांक hz, अचिन्हित पूर्णांक ticks)
अणु
	del_समयr_sync(&kd_mksound_समयr);

	input_handler_क्रम_each_handle(&kbd_handler, &hz, kd_sound_helper);

	अगर (hz && ticks)
		mod_समयr(&kd_mksound_समयr, jअगरfies + ticks);
पूर्ण
EXPORT_SYMBOL(kd_mksound);

/*
 * Setting the keyboard rate.
 */

अटल पूर्णांक kbd_rate_helper(काष्ठा input_handle *handle, व्योम *data)
अणु
	काष्ठा input_dev *dev = handle->dev;
	काष्ठा kbd_repeat *rpt = data;

	अगर (test_bit(EV_REP, dev->evbit)) अणु

		अगर (rpt[0].delay > 0)
			input_inject_event(handle,
					   EV_REP, REP_DELAY, rpt[0].delay);
		अगर (rpt[0].period > 0)
			input_inject_event(handle,
					   EV_REP, REP_PERIOD, rpt[0].period);

		rpt[1].delay = dev->rep[REP_DELAY];
		rpt[1].period = dev->rep[REP_PERIOD];
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक kbd_rate(काष्ठा kbd_repeat *rpt)
अणु
	काष्ठा kbd_repeat data[2] = अणु *rpt पूर्ण;

	input_handler_क्रम_each_handle(&kbd_handler, data, kbd_rate_helper);
	*rpt = data[1];	/* Copy currently used settings */

	वापस 0;
पूर्ण

/*
 * Helper Functions.
 */
अटल व्योम put_queue(काष्ठा vc_data *vc, पूर्णांक ch)
अणु
	tty_insert_flip_अक्षर(&vc->port, ch, 0);
	tty_schedule_flip(&vc->port);
पूर्ण

अटल व्योम माला_दो_queue(काष्ठा vc_data *vc, स्थिर अक्षर *cp)
अणु
	tty_insert_flip_string(&vc->port, cp, म_माप(cp));
	tty_schedule_flip(&vc->port);
पूर्ण

अटल व्योम applkey(काष्ठा vc_data *vc, पूर्णांक key, अक्षर mode)
अणु
	अटल अक्षर buf[] = अणु 0x1b, 'O', 0x00, 0x00 पूर्ण;

	buf[1] = (mode ? 'O' : '[');
	buf[2] = key;
	माला_दो_queue(vc, buf);
पूर्ण

/*
 * Many other routines करो put_queue, but I think either
 * they produce ASCII, or they produce some user-asचिन्हित
 * string, and in both हालs we might assume that it is
 * in utf-8 alपढ़ोy.
 */
अटल व्योम to_utf8(काष्ठा vc_data *vc, uपूर्णांक c)
अणु
	अगर (c < 0x80)
		/*  0******* */
		put_queue(vc, c);
	अन्यथा अगर (c < 0x800) अणु
		/* 110***** 10****** */
		put_queue(vc, 0xc0 | (c >> 6));
		put_queue(vc, 0x80 | (c & 0x3f));
	पूर्ण अन्यथा अगर (c < 0x10000) अणु
		अगर (c >= 0xD800 && c < 0xE000)
			वापस;
		अगर (c == 0xFFFF)
			वापस;
		/* 1110**** 10****** 10****** */
		put_queue(vc, 0xe0 | (c >> 12));
		put_queue(vc, 0x80 | ((c >> 6) & 0x3f));
		put_queue(vc, 0x80 | (c & 0x3f));
	पूर्ण अन्यथा अगर (c < 0x110000) अणु
		/* 11110*** 10****** 10****** 10****** */
		put_queue(vc, 0xf0 | (c >> 18));
		put_queue(vc, 0x80 | ((c >> 12) & 0x3f));
		put_queue(vc, 0x80 | ((c >> 6) & 0x3f));
		put_queue(vc, 0x80 | (c & 0x3f));
	पूर्ण
पूर्ण

/* FIXME: review locking क्रम vt.c callers */
अटल व्योम set_leds(व्योम)
अणु
	tasklet_schedule(&keyboard_tasklet);
पूर्ण

/*
 * Called after वापसing from RAW mode or when changing consoles - recompute
 * shअगरt_करोwn[] and shअगरt_state from key_करोwn[] maybe called when keymap is
 * undefined, so that shअगरtkey release is seen. The caller must hold the
 * kbd_event_lock.
 */

अटल व्योम करो_compute_shअगरtstate(व्योम)
अणु
	अचिन्हित पूर्णांक k, sym, val;

	shअगरt_state = 0;
	स_रखो(shअगरt_करोwn, 0, माप(shअगरt_करोwn));

	क्रम_each_set_bit(k, key_करोwn, min(NR_KEYS, KEY_CNT)) अणु
		sym = U(key_maps[0][k]);
		अगर (KTYP(sym) != KT_SHIFT && KTYP(sym) != KT_SLOCK)
			जारी;

		val = KVAL(sym);
		अगर (val == KVAL(K_CAPSSHIFT))
			val = KVAL(K_SHIFT);

		shअगरt_करोwn[val]++;
		shअगरt_state |= BIT(val);
	पूर्ण
पूर्ण

/* We still have to export this method to vt.c */
व्योम vt_set_leds_compute_shअगरtstate(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	set_leds();

	spin_lock_irqsave(&kbd_event_lock, flags);
	करो_compute_shअगरtstate();
	spin_unlock_irqrestore(&kbd_event_lock, flags);
पूर्ण

/*
 * We have a combining अक्षरacter DIACR here, followed by the अक्षरacter CH.
 * If the combination occurs in the table, वापस the corresponding value.
 * Otherwise, अगर CH is a space or equals DIACR, वापस DIACR.
 * Otherwise, conclude that DIACR was not combining after all,
 * queue it and वापस CH.
 */
अटल अचिन्हित पूर्णांक handle_diacr(काष्ठा vc_data *vc, अचिन्हित पूर्णांक ch)
अणु
	अचिन्हित पूर्णांक d = diacr;
	अचिन्हित पूर्णांक i;

	diacr = 0;

	अगर ((d & ~0xff) == BRL_UC_ROW) अणु
		अगर ((ch & ~0xff) == BRL_UC_ROW)
			वापस d | ch;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < accent_table_size; i++)
			अगर (accent_table[i].diacr == d && accent_table[i].base == ch)
				वापस accent_table[i].result;
	पूर्ण

	अगर (ch == ' ' || ch == (BRL_UC_ROW|0) || ch == d)
		वापस d;

	अगर (kbd->kbdmode == VC_UNICODE)
		to_utf8(vc, d);
	अन्यथा अणु
		पूर्णांक c = conv_uni_to_8bit(d);
		अगर (c != -1)
			put_queue(vc, c);
	पूर्ण

	वापस ch;
पूर्ण

/*
 * Special function handlers
 */
अटल व्योम fn_enter(काष्ठा vc_data *vc)
अणु
	अगर (diacr) अणु
		अगर (kbd->kbdmode == VC_UNICODE)
			to_utf8(vc, diacr);
		अन्यथा अणु
			पूर्णांक c = conv_uni_to_8bit(diacr);
			अगर (c != -1)
				put_queue(vc, c);
		पूर्ण
		diacr = 0;
	पूर्ण

	put_queue(vc, '\r');
	अगर (vc_kbd_mode(kbd, VC_CRLF))
		put_queue(vc, '\n');
पूर्ण

अटल व्योम fn_caps_toggle(काष्ठा vc_data *vc)
अणु
	अगर (rep)
		वापस;

	chg_vc_kbd_led(kbd, VC_CAPSLOCK);
पूर्ण

अटल व्योम fn_caps_on(काष्ठा vc_data *vc)
अणु
	अगर (rep)
		वापस;

	set_vc_kbd_led(kbd, VC_CAPSLOCK);
पूर्ण

अटल व्योम fn_show_ptregs(काष्ठा vc_data *vc)
अणु
	काष्ठा pt_regs *regs = get_irq_regs();

	अगर (regs)
		show_regs(regs);
पूर्ण

अटल व्योम fn_hold(काष्ठा vc_data *vc)
अणु
	काष्ठा tty_काष्ठा *tty = vc->port.tty;

	अगर (rep || !tty)
		वापस;

	/*
	 * Note: SCROLLOCK will be set (cleared) by stop_tty (start_tty);
	 * these routines are also activated by ^S/^Q.
	 * (And SCROLLOCK can also be set by the ioctl KDSKBLED.)
	 */
	अगर (tty->stopped)
		start_tty(tty);
	अन्यथा
		stop_tty(tty);
पूर्ण

अटल व्योम fn_num(काष्ठा vc_data *vc)
अणु
	अगर (vc_kbd_mode(kbd, VC_APPLIC))
		applkey(vc, 'P', 1);
	अन्यथा
		fn_bare_num(vc);
पूर्ण

/*
 * Bind this to Shअगरt-NumLock अगर you work in application keypad mode
 * but want to be able to change the NumLock flag.
 * Bind this to NumLock अगर you prefer that the NumLock key always
 * changes the NumLock flag.
 */
अटल व्योम fn_bare_num(काष्ठा vc_data *vc)
अणु
	अगर (!rep)
		chg_vc_kbd_led(kbd, VC_NUMLOCK);
पूर्ण

अटल व्योम fn_lastcons(काष्ठा vc_data *vc)
अणु
	/* चयन to the last used console, ChN */
	set_console(last_console);
पूर्ण

अटल व्योम fn_dec_console(काष्ठा vc_data *vc)
अणु
	पूर्णांक i, cur = fg_console;

	/* Currently चयनing?  Queue this next चयन relative to that. */
	अगर (want_console != -1)
		cur = want_console;

	क्रम (i = cur - 1; i != cur; i--) अणु
		अगर (i == -1)
			i = MAX_NR_CONSOLES - 1;
		अगर (vc_cons_allocated(i))
			अवरोध;
	पूर्ण
	set_console(i);
पूर्ण

अटल व्योम fn_inc_console(काष्ठा vc_data *vc)
अणु
	पूर्णांक i, cur = fg_console;

	/* Currently चयनing?  Queue this next चयन relative to that. */
	अगर (want_console != -1)
		cur = want_console;

	क्रम (i = cur+1; i != cur; i++) अणु
		अगर (i == MAX_NR_CONSOLES)
			i = 0;
		अगर (vc_cons_allocated(i))
			अवरोध;
	पूर्ण
	set_console(i);
पूर्ण

अटल व्योम fn_send_पूर्णांकr(काष्ठा vc_data *vc)
अणु
	tty_insert_flip_अक्षर(&vc->port, 0, TTY_BREAK);
	tty_schedule_flip(&vc->port);
पूर्ण

अटल व्योम fn_scroll_क्रमw(काष्ठा vc_data *vc)
अणु
	scrollfront(vc, 0);
पूर्ण

अटल व्योम fn_scroll_back(काष्ठा vc_data *vc)
अणु
	scrollback(vc);
पूर्ण

अटल व्योम fn_show_mem(काष्ठा vc_data *vc)
अणु
	show_mem(0, शून्य);
पूर्ण

अटल व्योम fn_show_state(काष्ठा vc_data *vc)
अणु
	show_state();
पूर्ण

अटल व्योम fn_boot_it(काष्ठा vc_data *vc)
अणु
	ctrl_alt_del();
पूर्ण

अटल व्योम fn_compose(काष्ठा vc_data *vc)
अणु
	dead_key_next = true;
पूर्ण

अटल व्योम fn_spawn_con(काष्ठा vc_data *vc)
अणु
	spin_lock(&vt_spawn_con.lock);
	अगर (vt_spawn_con.pid)
		अगर (समाप्त_pid(vt_spawn_con.pid, vt_spawn_con.sig, 1)) अणु
			put_pid(vt_spawn_con.pid);
			vt_spawn_con.pid = शून्य;
		पूर्ण
	spin_unlock(&vt_spawn_con.lock);
पूर्ण

अटल व्योम fn_SAK(काष्ठा vc_data *vc)
अणु
	काष्ठा work_काष्ठा *SAK_work = &vc_cons[fg_console].SAK_work;
	schedule_work(SAK_work);
पूर्ण

अटल व्योम fn_null(काष्ठा vc_data *vc)
अणु
	करो_compute_shअगरtstate();
पूर्ण

/*
 * Special key handlers
 */
अटल व्योम k_ignore(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
पूर्ण

अटल व्योम k_spec(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	अगर (up_flag)
		वापस;
	अगर (value >= ARRAY_SIZE(fn_handler))
		वापस;
	अगर ((kbd->kbdmode == VC_RAW ||
	     kbd->kbdmode == VC_MEDIUMRAW ||
	     kbd->kbdmode == VC_OFF) &&
	     value != KVAL(K_SAK))
		वापस;		/* SAK is allowed even in raw mode */
	fn_handler[value](vc);
पूर्ण

अटल व्योम k_lowerहाल(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	pr_err("k_lowercase was called - impossible\n");
पूर्ण

अटल व्योम k_unicode(काष्ठा vc_data *vc, अचिन्हित पूर्णांक value, अक्षर up_flag)
अणु
	अगर (up_flag)
		वापस;		/* no action, अगर this is a key release */

	अगर (diacr)
		value = handle_diacr(vc, value);

	अगर (dead_key_next) अणु
		dead_key_next = false;
		diacr = value;
		वापस;
	पूर्ण
	अगर (kbd->kbdmode == VC_UNICODE)
		to_utf8(vc, value);
	अन्यथा अणु
		पूर्णांक c = conv_uni_to_8bit(value);
		अगर (c != -1)
			put_queue(vc, c);
	पूर्ण
पूर्ण

/*
 * Handle dead key. Note that we now may have several
 * dead keys modअगरying the same अक्षरacter. Very useful
 * क्रम Vietnamese.
 */
अटल व्योम k_deadunicode(काष्ठा vc_data *vc, अचिन्हित पूर्णांक value, अक्षर up_flag)
अणु
	अगर (up_flag)
		वापस;

	diacr = (diacr ? handle_diacr(vc, value) : value);
पूर्ण

अटल व्योम k_self(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	k_unicode(vc, conv_8bit_to_uni(value), up_flag);
पूर्ण

अटल व्योम k_dead2(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	k_deadunicode(vc, value, up_flag);
पूर्ण

/*
 * Obsolete - क्रम backwards compatibility only
 */
अटल व्योम k_dead(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	अटल स्थिर अचिन्हित अक्षर ret_diacr[NR_DEAD] = अणु
		'`',	/* dead_grave */
		'\'',	/* dead_acute */
		'^',	/* dead_circumflex */
		'~',	/* dead_tilda */
		'"',	/* dead_diaeresis */
		',',	/* dead_cedilla */
		'_',	/* dead_macron */
		'U',	/* dead_breve */
		'.',	/* dead_aboveकरोt */
		'*',	/* dead_abovering */
		'=',	/* dead_द्विगुनacute */
		'c',	/* dead_caron */
		'k',	/* dead_ogonek */
		'i',	/* dead_iota */
		'#',	/* dead_voiced_sound */
		'o',	/* dead_semivoiced_sound */
		'!',	/* dead_belowकरोt */
		'?',	/* dead_hook */
		'+',	/* dead_horn */
		'-',	/* dead_stroke */
		')',	/* dead_abovecomma */
		'(',	/* dead_abovereversedcomma */
		':',	/* dead_द्विगुनgrave */
		'n',	/* dead_invertedbreve */
		';',	/* dead_belowcomma */
		'$',	/* dead_currency */
		'@',	/* dead_greek */
	पूर्ण;

	k_deadunicode(vc, ret_diacr[value], up_flag);
पूर्ण

अटल व्योम k_cons(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	अगर (up_flag)
		वापस;

	set_console(value);
पूर्ण

अटल व्योम k_fn(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	अगर (up_flag)
		वापस;

	अगर ((अचिन्हित)value < ARRAY_SIZE(func_table)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&func_buf_lock, flags);
		अगर (func_table[value])
			माला_दो_queue(vc, func_table[value]);
		spin_unlock_irqrestore(&func_buf_lock, flags);

	पूर्ण अन्यथा
		pr_err("k_fn called with value=%d\n", value);
पूर्ण

अटल व्योम k_cur(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	अटल स्थिर अक्षर cur_अक्षरs[] = "BDCA";

	अगर (up_flag)
		वापस;

	applkey(vc, cur_अक्षरs[value], vc_kbd_mode(kbd, VC_CKMODE));
पूर्ण

अटल व्योम k_pad(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	अटल स्थिर अक्षर pad_अक्षरs[] = "0123456789+-*/\015,.?()#";
	अटल स्थिर अक्षर app_map[] = "pqrstuvwxylSRQMnnmPQS";

	अगर (up_flag)
		वापस;		/* no action, अगर this is a key release */

	/* kludge... shअगरt क्रमces cursor/number keys */
	अगर (vc_kbd_mode(kbd, VC_APPLIC) && !shअगरt_करोwn[KG_SHIFT]) अणु
		applkey(vc, app_map[value], 1);
		वापस;
	पूर्ण

	अगर (!vc_kbd_led(kbd, VC_NUMLOCK)) अणु

		चयन (value) अणु
		हाल KVAL(K_PCOMMA):
		हाल KVAL(K_PDOT):
			k_fn(vc, KVAL(K_REMOVE), 0);
			वापस;
		हाल KVAL(K_P0):
			k_fn(vc, KVAL(K_INSERT), 0);
			वापस;
		हाल KVAL(K_P1):
			k_fn(vc, KVAL(K_SELECT), 0);
			वापस;
		हाल KVAL(K_P2):
			k_cur(vc, KVAL(K_DOWN), 0);
			वापस;
		हाल KVAL(K_P3):
			k_fn(vc, KVAL(K_PGDN), 0);
			वापस;
		हाल KVAL(K_P4):
			k_cur(vc, KVAL(K_LEFT), 0);
			वापस;
		हाल KVAL(K_P6):
			k_cur(vc, KVAL(K_RIGHT), 0);
			वापस;
		हाल KVAL(K_P7):
			k_fn(vc, KVAL(K_FIND), 0);
			वापस;
		हाल KVAL(K_P8):
			k_cur(vc, KVAL(K_UP), 0);
			वापस;
		हाल KVAL(K_P9):
			k_fn(vc, KVAL(K_PGUP), 0);
			वापस;
		हाल KVAL(K_P5):
			applkey(vc, 'G', vc_kbd_mode(kbd, VC_APPLIC));
			वापस;
		पूर्ण
	पूर्ण

	put_queue(vc, pad_अक्षरs[value]);
	अगर (value == KVAL(K_PENTER) && vc_kbd_mode(kbd, VC_CRLF))
		put_queue(vc, '\n');
पूर्ण

अटल व्योम k_shअगरt(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	पूर्णांक old_state = shअगरt_state;

	अगर (rep)
		वापस;
	/*
	 * Mimic typeग_लिखोr:
	 * a CapsShअगरt key acts like Shअगरt but unकरोes CapsLock
	 */
	अगर (value == KVAL(K_CAPSSHIFT)) अणु
		value = KVAL(K_SHIFT);
		अगर (!up_flag)
			clr_vc_kbd_led(kbd, VC_CAPSLOCK);
	पूर्ण

	अगर (up_flag) अणु
		/*
		 * handle the हाल that two shअगरt or control
		 * keys are depressed simultaneously
		 */
		अगर (shअगरt_करोwn[value])
			shअगरt_करोwn[value]--;
	पूर्ण अन्यथा
		shअगरt_करोwn[value]++;

	अगर (shअगरt_करोwn[value])
		shअगरt_state |= BIT(value);
	अन्यथा
		shअगरt_state &= ~BIT(value);

	/* kludge */
	अगर (up_flag && shअगरt_state != old_state && npadch_active) अणु
		अगर (kbd->kbdmode == VC_UNICODE)
			to_utf8(vc, npadch_value);
		अन्यथा
			put_queue(vc, npadch_value & 0xff);
		npadch_active = false;
	पूर्ण
पूर्ण

अटल व्योम k_meta(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	अगर (up_flag)
		वापस;

	अगर (vc_kbd_mode(kbd, VC_META)) अणु
		put_queue(vc, '\033');
		put_queue(vc, value);
	पूर्ण अन्यथा
		put_queue(vc, value | BIT(7));
पूर्ण

अटल व्योम k_ascii(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	अचिन्हित पूर्णांक base;

	अगर (up_flag)
		वापस;

	अगर (value < 10) अणु
		/* decimal input of code, जबतक Alt depressed */
		base = 10;
	पूर्ण अन्यथा अणु
		/* hexadecimal input of code, जबतक AltGr depressed */
		value -= 10;
		base = 16;
	पूर्ण

	अगर (!npadch_active) अणु
		npadch_value = 0;
		npadch_active = true;
	पूर्ण

	npadch_value = npadch_value * base + value;
पूर्ण

अटल व्योम k_lock(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	अगर (up_flag || rep)
		वापस;

	chg_vc_kbd_lock(kbd, value);
पूर्ण

अटल व्योम k_slock(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	k_shअगरt(vc, value, up_flag);
	अगर (up_flag || rep)
		वापस;

	chg_vc_kbd_slock(kbd, value);
	/* try to make Alt, oops, AltGr and such work */
	अगर (!key_maps[kbd->lockstate ^ kbd->slockstate]) अणु
		kbd->slockstate = 0;
		chg_vc_kbd_slock(kbd, value);
	पूर्ण
पूर्ण

/* by शेष, 300ms पूर्णांकerval क्रम combination release */
अटल अचिन्हित brl_समयout = 300;
MODULE_PARM_DESC(brl_समयout, "Braille keys release delay in ms (0 for commit on first key release)");
module_param(brl_समयout, uपूर्णांक, 0644);

अटल अचिन्हित brl_nbchords = 1;
MODULE_PARM_DESC(brl_nbchords, "Number of chords that produce a braille pattern (0 for dead chords)");
module_param(brl_nbchords, uपूर्णांक, 0644);

अटल व्योम k_brlcommit(काष्ठा vc_data *vc, अचिन्हित पूर्णांक pattern, अक्षर up_flag)
अणु
	अटल अचिन्हित दीर्घ chords;
	अटल अचिन्हित committed;

	अगर (!brl_nbchords)
		k_deadunicode(vc, BRL_UC_ROW | pattern, up_flag);
	अन्यथा अणु
		committed |= pattern;
		chords++;
		अगर (chords == brl_nbchords) अणु
			k_unicode(vc, BRL_UC_ROW | committed, up_flag);
			chords = 0;
			committed = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम k_brl(काष्ठा vc_data *vc, अचिन्हित अक्षर value, अक्षर up_flag)
अणु
	अटल अचिन्हित pressed, committing;
	अटल अचिन्हित दीर्घ releasestart;

	अगर (kbd->kbdmode != VC_UNICODE) अणु
		अगर (!up_flag)
			pr_warn("keyboard mode must be unicode for braille patterns\n");
		वापस;
	पूर्ण

	अगर (!value) अणु
		k_unicode(vc, BRL_UC_ROW, up_flag);
		वापस;
	पूर्ण

	अगर (value > 8)
		वापस;

	अगर (!up_flag) अणु
		pressed |= BIT(value - 1);
		अगर (!brl_समयout)
			committing = pressed;
	पूर्ण अन्यथा अगर (brl_समयout) अणु
		अगर (!committing ||
		    समय_after(jअगरfies,
			       releasestart + msecs_to_jअगरfies(brl_समयout))) अणु
			committing = pressed;
			releasestart = jअगरfies;
		पूर्ण
		pressed &= ~BIT(value - 1);
		अगर (!pressed && committing) अणु
			k_brlcommit(vc, committing, 0);
			committing = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (committing) अणु
			k_brlcommit(vc, committing, 0);
			committing = 0;
		पूर्ण
		pressed &= ~BIT(value - 1);
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_INPUT_LEDS) && IS_ENABLED(CONFIG_LEDS_TRIGGERS)

काष्ठा kbd_led_trigger अणु
	काष्ठा led_trigger trigger;
	अचिन्हित पूर्णांक mask;
पूर्ण;

अटल पूर्णांक kbd_led_trigger_activate(काष्ठा led_classdev *cdev)
अणु
	काष्ठा kbd_led_trigger *trigger =
		container_of(cdev->trigger, काष्ठा kbd_led_trigger, trigger);

	tasklet_disable(&keyboard_tasklet);
	अगर (ledstate != -1U)
		led_trigger_event(&trigger->trigger,
				  ledstate & trigger->mask ?
					LED_FULL : LED_OFF);
	tasklet_enable(&keyboard_tasklet);

	वापस 0;
पूर्ण

#घोषणा KBD_LED_TRIGGER(_led_bit, _name) अणु			\
		.trigger = अणु					\
			.name = _name,				\
			.activate = kbd_led_trigger_activate,	\
		पूर्ण,						\
		.mask	= BIT(_led_bit),			\
	पूर्ण

#घोषणा KBD_LOCKSTATE_TRIGGER(_led_bit, _name)		\
	KBD_LED_TRIGGER((_led_bit) + 8, _name)

अटल काष्ठा kbd_led_trigger kbd_led_triggers[] = अणु
	KBD_LED_TRIGGER(VC_SCROLLOCK, "kbd-scrolllock"),
	KBD_LED_TRIGGER(VC_NUMLOCK,   "kbd-numlock"),
	KBD_LED_TRIGGER(VC_CAPSLOCK,  "kbd-capslock"),
	KBD_LED_TRIGGER(VC_KANALOCK,  "kbd-kanalock"),

	KBD_LOCKSTATE_TRIGGER(VC_SHIFTLOCK,  "kbd-shiftlock"),
	KBD_LOCKSTATE_TRIGGER(VC_ALTGRLOCK,  "kbd-altgrlock"),
	KBD_LOCKSTATE_TRIGGER(VC_CTRLLOCK,   "kbd-ctrllock"),
	KBD_LOCKSTATE_TRIGGER(VC_ALTLOCK,    "kbd-altlock"),
	KBD_LOCKSTATE_TRIGGER(VC_SHIFTLLOCK, "kbd-shiftllock"),
	KBD_LOCKSTATE_TRIGGER(VC_SHIFTRLOCK, "kbd-shiftrlock"),
	KBD_LOCKSTATE_TRIGGER(VC_CTRLLLOCK,  "kbd-ctrlllock"),
	KBD_LOCKSTATE_TRIGGER(VC_CTRLRLOCK,  "kbd-ctrlrlock"),
पूर्ण;

अटल व्योम kbd_propagate_led_state(अचिन्हित पूर्णांक old_state,
				    अचिन्हित पूर्णांक new_state)
अणु
	काष्ठा kbd_led_trigger *trigger;
	अचिन्हित पूर्णांक changed = old_state ^ new_state;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(kbd_led_triggers); i++) अणु
		trigger = &kbd_led_triggers[i];

		अगर (changed & trigger->mask)
			led_trigger_event(&trigger->trigger,
					  new_state & trigger->mask ?
						LED_FULL : LED_OFF);
	पूर्ण
पूर्ण

अटल पूर्णांक kbd_update_leds_helper(काष्ठा input_handle *handle, व्योम *data)
अणु
	अचिन्हित पूर्णांक led_state = *(अचिन्हित पूर्णांक *)data;

	अगर (test_bit(EV_LED, handle->dev->evbit))
		kbd_propagate_led_state(~led_state, led_state);

	वापस 0;
पूर्ण

अटल व्योम kbd_init_leds(व्योम)
अणु
	पूर्णांक error;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(kbd_led_triggers); i++) अणु
		error = led_trigger_रेजिस्टर(&kbd_led_triggers[i].trigger);
		अगर (error)
			pr_err("error %d while registering trigger %s\n",
			       error, kbd_led_triggers[i].trigger.name);
	पूर्ण
पूर्ण

#अन्यथा

अटल पूर्णांक kbd_update_leds_helper(काष्ठा input_handle *handle, व्योम *data)
अणु
	अचिन्हित पूर्णांक leds = *(अचिन्हित पूर्णांक *)data;

	अगर (test_bit(EV_LED, handle->dev->evbit)) अणु
		input_inject_event(handle, EV_LED, LED_SCROLLL, !!(leds & BIT(0)));
		input_inject_event(handle, EV_LED, LED_NUML,    !!(leds & BIT(1)));
		input_inject_event(handle, EV_LED, LED_CAPSL,   !!(leds & BIT(2)));
		input_inject_event(handle, EV_SYN, SYN_REPORT, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kbd_propagate_led_state(अचिन्हित पूर्णांक old_state,
				    अचिन्हित पूर्णांक new_state)
अणु
	input_handler_क्रम_each_handle(&kbd_handler, &new_state,
				      kbd_update_leds_helper);
पूर्ण

अटल व्योम kbd_init_leds(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

/*
 * The leds display either (i) the status of NumLock, CapsLock, ScrollLock,
 * or (ii) whatever pattern of lights people want to show using KDSETLED,
 * or (iii) specअगरied bits of specअगरied words in kernel memory.
 */
अटल अचिन्हित अक्षर getledstate(व्योम)
अणु
	वापस ledstate & 0xff;
पूर्ण

व्योम setledstate(काष्ठा kbd_काष्ठा *kb, अचिन्हित पूर्णांक led)
अणु
        अचिन्हित दीर्घ flags;
        spin_lock_irqsave(&led_lock, flags);
	अगर (!(led & ~7)) अणु
		ledioctl = led;
		kb->ledmode = LED_SHOW_IOCTL;
	पूर्ण अन्यथा
		kb->ledmode = LED_SHOW_FLAGS;

	set_leds();
	spin_unlock_irqrestore(&led_lock, flags);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर getleds(व्योम)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + fg_console;

	अगर (kb->ledmode == LED_SHOW_IOCTL)
		वापस ledioctl;

	वापस kb->ledflagstate;
पूर्ण

/**
 *	vt_get_leds	-	helper क्रम braille console
 *	@console: console to पढ़ो
 *	@flag: flag we want to check
 *
 *	Check the status of a keyboard led flag and report it back
 */
पूर्णांक vt_get_leds(पूर्णांक console, पूर्णांक flag)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&led_lock, flags);
	ret = vc_kbd_led(kb, flag);
	spin_unlock_irqrestore(&led_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vt_get_leds);

/**
 *	vt_set_led_state	-	set LED state of a console
 *	@console: console to set
 *	@leds: LED bits
 *
 *	Set the LEDs on a console. This is a wrapper क्रम the VT layer
 *	so that we can keep kbd knowledge पूर्णांकernal
 */
व्योम vt_set_led_state(पूर्णांक console, पूर्णांक leds)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
	setledstate(kb, leds);
पूर्ण

/**
 *	vt_kbd_con_start	-	Keyboard side of console start
 *	@console: console
 *
 *	Handle console start. This is a wrapper क्रम the VT layer
 *	so that we can keep kbd knowledge पूर्णांकernal
 *
 *	FIXME: We eventually need to hold the kbd lock here to protect
 *	the LED updating. We can't करो it yet because fn_hold calls stop_tty
 *	and start_tty under the kbd_event_lock, जबतक normal tty paths
 *	करोn't hold the lock. We probably need to split out an LED lock
 *	but not during an -rc release!
 */
व्योम vt_kbd_con_start(पूर्णांक console)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&led_lock, flags);
	clr_vc_kbd_led(kb, VC_SCROLLOCK);
	set_leds();
	spin_unlock_irqrestore(&led_lock, flags);
पूर्ण

/**
 *	vt_kbd_con_stop		-	Keyboard side of console stop
 *	@console: console
 *
 *	Handle console stop. This is a wrapper क्रम the VT layer
 *	so that we can keep kbd knowledge पूर्णांकernal
 */
व्योम vt_kbd_con_stop(पूर्णांक console)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&led_lock, flags);
	set_vc_kbd_led(kb, VC_SCROLLOCK);
	set_leds();
	spin_unlock_irqrestore(&led_lock, flags);
पूर्ण

/*
 * This is the tasklet that updates LED state of LEDs using standard
 * keyboard triggers. The reason we use tasklet is that we need to
 * handle the scenario when keyboard handler is not रेजिस्टरed yet
 * but we alपढ़ोy getting updates from the VT to update led state.
 */
अटल व्योम kbd_bh(काष्ठा tasklet_काष्ठा *unused)
अणु
	अचिन्हित पूर्णांक leds;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&led_lock, flags);
	leds = getleds();
	leds |= (अचिन्हित पूर्णांक)kbd->lockstate << 8;
	spin_unlock_irqrestore(&led_lock, flags);

	अगर (leds != ledstate) अणु
		kbd_propagate_led_state(ledstate, leds);
		ledstate = leds;
	पूर्ण
पूर्ण

#अगर defined(CONFIG_X86) || defined(CONFIG_IA64) || defined(CONFIG_ALPHA) ||\
    defined(CONFIG_MIPS) || defined(CONFIG_PPC) || defined(CONFIG_SPARC) ||\
    defined(CONFIG_PARISC) || defined(CONFIG_SUPERH) ||\
    (defined(CONFIG_ARM) && defined(CONFIG_KEYBOARD_ATKBD) && !defined(CONFIG_ARCH_RPC))

अटल अंतरभूत bool kbd_is_hw_raw(स्थिर काष्ठा input_dev *dev)
अणु
	अगर (!test_bit(EV_MSC, dev->evbit) || !test_bit(MSC_RAW, dev->mscbit))
		वापस false;

	वापस dev->id.bustype == BUS_I8042 &&
		dev->id.venकरोr == 0x0001 && dev->id.product == 0x0001;
पूर्ण

अटल स्थिर अचिन्हित लघु x86_keycodes[256] =
	अणु 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
	 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
	 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
	 80, 81, 82, 83, 84,118, 86, 87, 88,115,120,119,121,112,123, 92,
	284,285,309,  0,312, 91,327,328,329,331,333,335,336,337,338,339,
	367,288,302,304,350, 89,334,326,267,126,268,269,125,347,348,349,
	360,261,262,263,268,376,100,101,321,316,373,286,289,102,351,355,
	103,104,105,275,287,279,258,106,274,107,294,364,358,363,362,361,
	291,108,381,281,290,272,292,305,280, 99,112,257,306,359,113,114,
	264,117,271,374,379,265,266, 93, 94, 95, 85,259,375,260, 90,116,
	377,109,111,277,278,282,283,295,296,297,299,300,301,293,303,307,
	308,310,313,314,315,317,318,319,320,357,322,323,324,325,276,330,
	332,340,365,342,343,344,345,346,356,270,341,368,369,370,371,372 पूर्ण;

#अगर_घोषित CONFIG_SPARC
अटल पूर्णांक sparc_l1_a_state;
बाह्य व्योम sun_करो_अवरोध(व्योम);
#पूर्ण_अगर

अटल पूर्णांक emulate_raw(काष्ठा vc_data *vc, अचिन्हित पूर्णांक keycode,
		       अचिन्हित अक्षर up_flag)
अणु
	पूर्णांक code;

	चयन (keycode) अणु

	हाल KEY_PAUSE:
		put_queue(vc, 0xe1);
		put_queue(vc, 0x1d | up_flag);
		put_queue(vc, 0x45 | up_flag);
		अवरोध;

	हाल KEY_HANGEUL:
		अगर (!up_flag)
			put_queue(vc, 0xf2);
		अवरोध;

	हाल KEY_HANJA:
		अगर (!up_flag)
			put_queue(vc, 0xf1);
		अवरोध;

	हाल KEY_SYSRQ:
		/*
		 * Real AT keyboards (that's what we're trying
		 * to emulate here) emit 0xe0 0x2a 0xe0 0x37 when
		 * pressing PrtSc/SysRq alone, but simply 0x54
		 * when pressing Alt+PrtSc/SysRq.
		 */
		अगर (test_bit(KEY_LEFTALT, key_करोwn) ||
		    test_bit(KEY_RIGHTALT, key_करोwn)) अणु
			put_queue(vc, 0x54 | up_flag);
		पूर्ण अन्यथा अणु
			put_queue(vc, 0xe0);
			put_queue(vc, 0x2a | up_flag);
			put_queue(vc, 0xe0);
			put_queue(vc, 0x37 | up_flag);
		पूर्ण
		अवरोध;

	शेष:
		अगर (keycode > 255)
			वापस -1;

		code = x86_keycodes[keycode];
		अगर (!code)
			वापस -1;

		अगर (code & 0x100)
			put_queue(vc, 0xe0);
		put_queue(vc, (code & 0x7f) | up_flag);

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा

अटल अंतरभूत bool kbd_is_hw_raw(स्थिर काष्ठा input_dev *dev)
अणु
	वापस false;
पूर्ण

अटल पूर्णांक emulate_raw(काष्ठा vc_data *vc, अचिन्हित पूर्णांक keycode, अचिन्हित अक्षर up_flag)
अणु
	अगर (keycode > 127)
		वापस -1;

	put_queue(vc, keycode | up_flag);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम kbd_rawcode(अचिन्हित अक्षर data)
अणु
	काष्ठा vc_data *vc = vc_cons[fg_console].d;

	kbd = kbd_table + vc->vc_num;
	अगर (kbd->kbdmode == VC_RAW)
		put_queue(vc, data);
पूर्ण

अटल व्योम kbd_keycode(अचिन्हित पूर्णांक keycode, पूर्णांक करोwn, bool hw_raw)
अणु
	काष्ठा vc_data *vc = vc_cons[fg_console].d;
	अचिन्हित लघु keysym, *key_map;
	अचिन्हित अक्षर type;
	bool raw_mode;
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक shअगरt_final;
	काष्ठा keyboard_notअगरier_param param = अणु .vc = vc, .value = keycode, .करोwn = करोwn पूर्ण;
	पूर्णांक rc;

	tty = vc->port.tty;

	अगर (tty && (!tty->driver_data)) अणु
		/* No driver data? Strange. Okay we fix it then. */
		tty->driver_data = vc;
	पूर्ण

	kbd = kbd_table + vc->vc_num;

#अगर_घोषित CONFIG_SPARC
	अगर (keycode == KEY_STOP)
		sparc_l1_a_state = करोwn;
#पूर्ण_अगर

	rep = (करोwn == 2);

	raw_mode = (kbd->kbdmode == VC_RAW);
	अगर (raw_mode && !hw_raw)
		अगर (emulate_raw(vc, keycode, !करोwn << 7))
			अगर (keycode < BTN_MISC && prपूर्णांकk_ratelimit())
				pr_warn("can't emulate rawmode for keycode %d\n",
					keycode);

#अगर_घोषित CONFIG_SPARC
	अगर (keycode == KEY_A && sparc_l1_a_state) अणु
		sparc_l1_a_state = false;
		sun_करो_अवरोध();
	पूर्ण
#पूर्ण_अगर

	अगर (kbd->kbdmode == VC_MEDIUMRAW) अणु
		/*
		 * This is extended medium raw mode, with keys above 127
		 * encoded as 0, high 7 bits, low 7 bits, with the 0 bearing
		 * the 'up' flag if needed. 0 is reserved, so this shouldn't
		 * पूर्णांकerfere with anything अन्यथा. The two bytes after 0 will
		 * always have the up flag set not to पूर्णांकerfere with older
		 * applications. This allows क्रम 16384 dअगरferent keycodes,
		 * which should be enough.
		 */
		अगर (keycode < 128) अणु
			put_queue(vc, keycode | (!करोwn << 7));
		पूर्ण अन्यथा अणु
			put_queue(vc, !करोwn << 7);
			put_queue(vc, (keycode >> 7) | BIT(7));
			put_queue(vc, keycode | BIT(7));
		पूर्ण
		raw_mode = true;
	पूर्ण

	assign_bit(keycode, key_करोwn, करोwn);

	अगर (rep &&
	    (!vc_kbd_mode(kbd, VC_REPEAT) ||
	     (tty && !L_ECHO(tty) && tty_अक्षरs_in_buffer(tty)))) अणु
		/*
		 * Don't repeat a key अगर the input buffers are not empty and the
		 * अक्षरacters get aren't echoed locally. This makes key repeat
		 * usable with slow applications and under heavy loads.
		 */
		वापस;
	पूर्ण

	param.shअगरt = shअगरt_final = (shअगरt_state | kbd->slockstate) ^ kbd->lockstate;
	param.ledstate = kbd->ledflagstate;
	key_map = key_maps[shअगरt_final];

	rc = atomic_notअगरier_call_chain(&keyboard_notअगरier_list,
					KBD_KEYCODE, &param);
	अगर (rc == NOTIFY_STOP || !key_map) अणु
		atomic_notअगरier_call_chain(&keyboard_notअगरier_list,
					   KBD_UNBOUND_KEYCODE, &param);
		करो_compute_shअगरtstate();
		kbd->slockstate = 0;
		वापस;
	पूर्ण

	अगर (keycode < NR_KEYS)
		keysym = key_map[keycode];
	अन्यथा अगर (keycode >= KEY_BRL_DOT1 && keycode <= KEY_BRL_DOT8)
		keysym = U(K(KT_BRL, keycode - KEY_BRL_DOT1 + 1));
	अन्यथा
		वापस;

	type = KTYP(keysym);

	अगर (type < 0xf0) अणु
		param.value = keysym;
		rc = atomic_notअगरier_call_chain(&keyboard_notअगरier_list,
						KBD_UNICODE, &param);
		अगर (rc != NOTIFY_STOP)
			अगर (करोwn && !raw_mode)
				k_unicode(vc, keysym, !करोwn);
		वापस;
	पूर्ण

	type -= 0xf0;

	अगर (type == KT_LETTER) अणु
		type = KT_LATIN;
		अगर (vc_kbd_led(kbd, VC_CAPSLOCK)) अणु
			key_map = key_maps[shअगरt_final ^ BIT(KG_SHIFT)];
			अगर (key_map)
				keysym = key_map[keycode];
		पूर्ण
	पूर्ण

	param.value = keysym;
	rc = atomic_notअगरier_call_chain(&keyboard_notअगरier_list,
					KBD_KEYSYM, &param);
	अगर (rc == NOTIFY_STOP)
		वापस;

	अगर ((raw_mode || kbd->kbdmode == VC_OFF) && type != KT_SPEC && type != KT_SHIFT)
		वापस;

	(*k_handler[type])(vc, keysym & 0xff, !करोwn);

	param.ledstate = kbd->ledflagstate;
	atomic_notअगरier_call_chain(&keyboard_notअगरier_list, KBD_POST_KEYSYM, &param);

	अगर (type != KT_SLOCK)
		kbd->slockstate = 0;
पूर्ण

अटल व्योम kbd_event(काष्ठा input_handle *handle, अचिन्हित पूर्णांक event_type,
		      अचिन्हित पूर्णांक event_code, पूर्णांक value)
अणु
	/* We are called with पूर्णांकerrupts disabled, just take the lock */
	spin_lock(&kbd_event_lock);

	अगर (event_type == EV_MSC && event_code == MSC_RAW &&
			kbd_is_hw_raw(handle->dev))
		kbd_rawcode(value);
	अगर (event_type == EV_KEY && event_code <= KEY_MAX)
		kbd_keycode(event_code, value, kbd_is_hw_raw(handle->dev));

	spin_unlock(&kbd_event_lock);

	tasklet_schedule(&keyboard_tasklet);
	करो_poke_blanked_console = 1;
	schedule_console_callback();
पूर्ण

अटल bool kbd_match(काष्ठा input_handler *handler, काष्ठा input_dev *dev)
अणु
	अगर (test_bit(EV_SND, dev->evbit))
		वापस true;

	अगर (test_bit(EV_KEY, dev->evbit)) अणु
		अगर (find_next_bit(dev->keybit, BTN_MISC, KEY_RESERVED) <
				BTN_MISC)
			वापस true;
		अगर (find_next_bit(dev->keybit, KEY_BRL_DOT10 + 1,
					KEY_BRL_DOT1) <= KEY_BRL_DOT10)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * When a keyboard (or other input device) is found, the kbd_connect
 * function is called. The function then looks at the device, and अगर it
 * likes it, it can खोलो it and get events from it. In this (kbd_connect)
 * function, we should decide which VT to bind that keyboard to initially.
 */
अटल पूर्णांक kbd_connect(काष्ठा input_handler *handler, काष्ठा input_dev *dev,
			स्थिर काष्ठा input_device_id *id)
अणु
	काष्ठा input_handle *handle;
	पूर्णांक error;

	handle = kzalloc(माप(काष्ठा input_handle), GFP_KERNEL);
	अगर (!handle)
		वापस -ENOMEM;

	handle->dev = dev;
	handle->handler = handler;
	handle->name = "kbd";

	error = input_रेजिस्टर_handle(handle);
	अगर (error)
		जाओ err_मुक्त_handle;

	error = input_खोलो_device(handle);
	अगर (error)
		जाओ err_unरेजिस्टर_handle;

	वापस 0;

 err_unरेजिस्टर_handle:
	input_unरेजिस्टर_handle(handle);
 err_मुक्त_handle:
	kमुक्त(handle);
	वापस error;
पूर्ण

अटल व्योम kbd_disconnect(काष्ठा input_handle *handle)
अणु
	input_बंद_device(handle);
	input_unरेजिस्टर_handle(handle);
	kमुक्त(handle);
पूर्ण

/*
 * Start keyboard handler on the new keyboard by refreshing LED state to
 * match the rest of the प्रणाली.
 */
अटल व्योम kbd_start(काष्ठा input_handle *handle)
अणु
	tasklet_disable(&keyboard_tasklet);

	अगर (ledstate != -1U)
		kbd_update_leds_helper(handle, &ledstate);

	tasklet_enable(&keyboard_tasklet);
पूर्ण

अटल स्थिर काष्ठा input_device_id kbd_ids[] = अणु
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = अणु BIT_MASK(EV_KEY) पूर्ण,
	पूर्ण,

	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = अणु BIT_MASK(EV_SND) पूर्ण,
	पूर्ण,

	अणु पूर्ण,    /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(input, kbd_ids);

अटल काष्ठा input_handler kbd_handler = अणु
	.event		= kbd_event,
	.match		= kbd_match,
	.connect	= kbd_connect,
	.disconnect	= kbd_disconnect,
	.start		= kbd_start,
	.name		= "kbd",
	.id_table	= kbd_ids,
पूर्ण;

पूर्णांक __init kbd_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक error;

	क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
		kbd_table[i].ledflagstate = kbd_defleds();
		kbd_table[i].शेष_ledflagstate = kbd_defleds();
		kbd_table[i].ledmode = LED_SHOW_FLAGS;
		kbd_table[i].lockstate = KBD_DEFLOCK;
		kbd_table[i].slockstate = 0;
		kbd_table[i].modeflags = KBD_DEFMODE;
		kbd_table[i].kbdmode = शेष_utf8 ? VC_UNICODE : VC_XLATE;
	पूर्ण

	kbd_init_leds();

	error = input_रेजिस्टर_handler(&kbd_handler);
	अगर (error)
		वापस error;

	tasklet_enable(&keyboard_tasklet);
	tasklet_schedule(&keyboard_tasklet);

	वापस 0;
पूर्ण

/* Ioctl support code */

/**
 *	vt_करो_diacrit		-	diacritical table updates
 *	@cmd: ioctl request
 *	@udp: poपूर्णांकer to user data क्रम ioctl
 *	@perm: permissions check computed by caller
 *
 *	Update the diacritical tables atomically and safely. Lock them
 *	against simultaneous keypresses
 */
पूर्णांक vt_करो_diacrit(अचिन्हित पूर्णांक cmd, व्योम __user *udp, पूर्णांक perm)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक asize;
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल KDGKBDIACR:
	अणु
		काष्ठा kbdiacrs __user *a = udp;
		काष्ठा kbdiacr *dia;
		पूर्णांक i;

		dia = kदो_स्मृति_array(MAX_DIACR, माप(काष्ठा kbdiacr),
								GFP_KERNEL);
		अगर (!dia)
			वापस -ENOMEM;

		/* Lock the diacriticals table, make a copy and then
		   copy it after we unlock */
		spin_lock_irqsave(&kbd_event_lock, flags);

		asize = accent_table_size;
		क्रम (i = 0; i < asize; i++) अणु
			dia[i].diacr = conv_uni_to_8bit(
						accent_table[i].diacr);
			dia[i].base = conv_uni_to_8bit(
						accent_table[i].base);
			dia[i].result = conv_uni_to_8bit(
						accent_table[i].result);
		पूर्ण
		spin_unlock_irqrestore(&kbd_event_lock, flags);

		अगर (put_user(asize, &a->kb_cnt))
			ret = -EFAULT;
		अन्यथा  अगर (copy_to_user(a->kbdiacr, dia,
				asize * माप(काष्ठा kbdiacr)))
			ret = -EFAULT;
		kमुक्त(dia);
		वापस ret;
	पूर्ण
	हाल KDGKBDIACRUC:
	अणु
		काष्ठा kbdiacrsuc __user *a = udp;
		व्योम *buf;

		buf = kदो_स्मृति_array(MAX_DIACR, माप(काष्ठा kbdiacruc),
								GFP_KERNEL);
		अगर (buf == शून्य)
			वापस -ENOMEM;

		/* Lock the diacriticals table, make a copy and then
		   copy it after we unlock */
		spin_lock_irqsave(&kbd_event_lock, flags);

		asize = accent_table_size;
		स_नकल(buf, accent_table, asize * माप(काष्ठा kbdiacruc));

		spin_unlock_irqrestore(&kbd_event_lock, flags);

		अगर (put_user(asize, &a->kb_cnt))
			ret = -EFAULT;
		अन्यथा अगर (copy_to_user(a->kbdiacruc, buf,
				asize*माप(काष्ठा kbdiacruc)))
			ret = -EFAULT;
		kमुक्त(buf);
		वापस ret;
	पूर्ण

	हाल KDSKBDIACR:
	अणु
		काष्ठा kbdiacrs __user *a = udp;
		काष्ठा kbdiacr *dia = शून्य;
		अचिन्हित पूर्णांक ct;
		पूर्णांक i;

		अगर (!perm)
			वापस -EPERM;
		अगर (get_user(ct, &a->kb_cnt))
			वापस -EFAULT;
		अगर (ct >= MAX_DIACR)
			वापस -EINVAL;

		अगर (ct) अणु

			dia = memdup_user(a->kbdiacr,
					माप(काष्ठा kbdiacr) * ct);
			अगर (IS_ERR(dia))
				वापस PTR_ERR(dia);

		पूर्ण

		spin_lock_irqsave(&kbd_event_lock, flags);
		accent_table_size = ct;
		क्रम (i = 0; i < ct; i++) अणु
			accent_table[i].diacr =
					conv_8bit_to_uni(dia[i].diacr);
			accent_table[i].base =
					conv_8bit_to_uni(dia[i].base);
			accent_table[i].result =
					conv_8bit_to_uni(dia[i].result);
		पूर्ण
		spin_unlock_irqrestore(&kbd_event_lock, flags);
		kमुक्त(dia);
		वापस 0;
	पूर्ण

	हाल KDSKBDIACRUC:
	अणु
		काष्ठा kbdiacrsuc __user *a = udp;
		अचिन्हित पूर्णांक ct;
		व्योम *buf = शून्य;

		अगर (!perm)
			वापस -EPERM;

		अगर (get_user(ct, &a->kb_cnt))
			वापस -EFAULT;

		अगर (ct >= MAX_DIACR)
			वापस -EINVAL;

		अगर (ct) अणु
			buf = memdup_user(a->kbdiacruc,
					  ct * माप(काष्ठा kbdiacruc));
			अगर (IS_ERR(buf))
				वापस PTR_ERR(buf);
		पूर्ण 
		spin_lock_irqsave(&kbd_event_lock, flags);
		अगर (ct)
			स_नकल(accent_table, buf,
					ct * माप(काष्ठा kbdiacruc));
		accent_table_size = ct;
		spin_unlock_irqrestore(&kbd_event_lock, flags);
		kमुक्त(buf);
		वापस 0;
	पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 *	vt_करो_kdskbmode		-	set keyboard mode ioctl
 *	@console: the console to use
 *	@arg: the requested mode
 *
 *	Update the keyboard mode bits जबतक holding the correct locks.
 *	Return 0 क्रम success or an error code.
 */
पूर्णांक vt_करो_kdskbmode(पूर्णांक console, अचिन्हित पूर्णांक arg)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kbd_event_lock, flags);
	चयन(arg) अणु
	हाल K_RAW:
		kb->kbdmode = VC_RAW;
		अवरोध;
	हाल K_MEDIUMRAW:
		kb->kbdmode = VC_MEDIUMRAW;
		अवरोध;
	हाल K_XLATE:
		kb->kbdmode = VC_XLATE;
		करो_compute_shअगरtstate();
		अवरोध;
	हाल K_UNICODE:
		kb->kbdmode = VC_UNICODE;
		करो_compute_shअगरtstate();
		अवरोध;
	हाल K_OFF:
		kb->kbdmode = VC_OFF;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&kbd_event_lock, flags);
	वापस ret;
पूर्ण

/**
 *	vt_करो_kdskbmeta		-	set keyboard meta state
 *	@console: the console to use
 *	@arg: the requested meta state
 *
 *	Update the keyboard meta bits जबतक holding the correct locks.
 *	Return 0 क्रम success or an error code.
 */
पूर्णांक vt_करो_kdskbmeta(पूर्णांक console, अचिन्हित पूर्णांक arg)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kbd_event_lock, flags);
	चयन(arg) अणु
	हाल K_METABIT:
		clr_vc_kbd_mode(kb, VC_META);
		अवरोध;
	हाल K_ESCPREFIX:
		set_vc_kbd_mode(kb, VC_META);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&kbd_event_lock, flags);
	वापस ret;
पूर्ण

पूर्णांक vt_करो_kbkeycode_ioctl(पूर्णांक cmd, काष्ठा kbkeycode __user *user_kbkc,
								पूर्णांक perm)
अणु
	काष्ठा kbkeycode पंचांगp;
	पूर्णांक kc = 0;

	अगर (copy_from_user(&पंचांगp, user_kbkc, माप(काष्ठा kbkeycode)))
		वापस -EFAULT;
	चयन (cmd) अणु
	हाल KDGETKEYCODE:
		kc = getkeycode(पंचांगp.scancode);
		अगर (kc >= 0)
			kc = put_user(kc, &user_kbkc->keycode);
		अवरोध;
	हाल KDSETKEYCODE:
		अगर (!perm)
			वापस -EPERM;
		kc = setkeycode(पंचांगp.scancode, पंचांगp.keycode);
		अवरोध;
	पूर्ण
	वापस kc;
पूर्ण

अटल अचिन्हित लघु vt_kdgkbent(अचिन्हित अक्षर kbdmode, अचिन्हित अक्षर idx,
		अचिन्हित अक्षर map)
अणु
	अचिन्हित लघु *key_map, val;
	अचिन्हित दीर्घ flags;

	/* Ensure another thपढ़ो करोesn't मुक्त it under us */
	spin_lock_irqsave(&kbd_event_lock, flags);
	key_map = key_maps[map];
	अगर (key_map) अणु
		val = U(key_map[idx]);
		अगर (kbdmode != VC_UNICODE && KTYP(val) >= NR_TYPES)
			val = K_HOLE;
	पूर्ण अन्यथा
		val = idx ? K_HOLE : K_NOSUCHMAP;
	spin_unlock_irqrestore(&kbd_event_lock, flags);

	वापस val;
पूर्ण

अटल पूर्णांक vt_kdskbent(अचिन्हित अक्षर kbdmode, अचिन्हित अक्षर idx,
		अचिन्हित अक्षर map, अचिन्हित लघु val)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु *key_map, *new_map, oldval;

	अगर (!idx && val == K_NOSUCHMAP) अणु
		spin_lock_irqsave(&kbd_event_lock, flags);
		/* deallocate map */
		key_map = key_maps[map];
		अगर (map && key_map) अणु
			key_maps[map] = शून्य;
			अगर (key_map[0] == U(K_ALLOCATED)) अणु
				kमुक्त(key_map);
				keymap_count--;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&kbd_event_lock, flags);

		वापस 0;
	पूर्ण

	अगर (KTYP(val) < NR_TYPES) अणु
		अगर (KVAL(val) > max_vals[KTYP(val)])
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (kbdmode != VC_UNICODE)
		वापस -EINVAL;

	/* ++Geert: non-PC keyboards may generate keycode zero */
#अगर !defined(__mc68000__) && !defined(__घातerpc__)
	/* assignment to entry 0 only tests validity of args */
	अगर (!idx)
		वापस 0;
#पूर्ण_अगर

	new_map = kदो_स्मृति(माप(plain_map), GFP_KERNEL);
	अगर (!new_map)
		वापस -ENOMEM;

	spin_lock_irqsave(&kbd_event_lock, flags);
	key_map = key_maps[map];
	अगर (key_map == शून्य) अणु
		पूर्णांक j;

		अगर (keymap_count >= MAX_NR_OF_USER_KEYMAPS &&
		    !capable(CAP_SYS_RESOURCE)) अणु
			spin_unlock_irqrestore(&kbd_event_lock, flags);
			kमुक्त(new_map);
			वापस -EPERM;
		पूर्ण
		key_maps[map] = new_map;
		key_map = new_map;
		key_map[0] = U(K_ALLOCATED);
		क्रम (j = 1; j < NR_KEYS; j++)
			key_map[j] = U(K_HOLE);
		keymap_count++;
	पूर्ण अन्यथा
		kमुक्त(new_map);

	oldval = U(key_map[idx]);
	अगर (val == oldval)
		जाओ out;

	/* Attention Key */
	अगर ((oldval == K_SAK || val == K_SAK) && !capable(CAP_SYS_ADMIN)) अणु
		spin_unlock_irqrestore(&kbd_event_lock, flags);
		वापस -EPERM;
	पूर्ण

	key_map[idx] = U(val);
	अगर (!map && (KTYP(oldval) == KT_SHIFT || KTYP(val) == KT_SHIFT))
		करो_compute_shअगरtstate();
out:
	spin_unlock_irqrestore(&kbd_event_lock, flags);

	वापस 0;
पूर्ण

पूर्णांक vt_करो_kdsk_ioctl(पूर्णांक cmd, काष्ठा kbentry __user *user_kbe, पूर्णांक perm,
						पूर्णांक console)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
	काष्ठा kbentry kbe;

	अगर (copy_from_user(&kbe, user_kbe, माप(काष्ठा kbentry)))
		वापस -EFAULT;

	चयन (cmd) अणु
	हाल KDGKBENT:
		वापस put_user(vt_kdgkbent(kb->kbdmode, kbe.kb_index,
					kbe.kb_table),
				&user_kbe->kb_value);
	हाल KDSKBENT:
		अगर (!perm || !capable(CAP_SYS_TTY_CONFIG))
			वापस -EPERM;
		वापस vt_kdskbent(kb->kbdmode, kbe.kb_index, kbe.kb_table,
				kbe.kb_value);
	पूर्ण
	वापस 0;
पूर्ण

अटल अक्षर *vt_kdskbsent(अक्षर *kbs, अचिन्हित अक्षर cur)
अणु
	अटल DECLARE_BITMAP(is_kदो_स्मृति, MAX_NR_FUNC);
	अक्षर *cur_f = func_table[cur];

	अगर (cur_f && म_माप(cur_f) >= म_माप(kbs)) अणु
		म_नकल(cur_f, kbs);
		वापस kbs;
	पूर्ण

	func_table[cur] = kbs;

	वापस __test_and_set_bit(cur, is_kदो_स्मृति) ? cur_f : शून्य;
पूर्ण

पूर्णांक vt_करो_kdgkb_ioctl(पूर्णांक cmd, काष्ठा kbsentry __user *user_kdgkb, पूर्णांक perm)
अणु
	अचिन्हित अक्षर kb_func;
	अचिन्हित दीर्घ flags;
	अक्षर *kbs;
	पूर्णांक ret;

	अगर (get_user(kb_func, &user_kdgkb->kb_func))
		वापस -EFAULT;

	kb_func = array_index_nospec(kb_func, MAX_NR_FUNC);

	चयन (cmd) अणु
	हाल KDGKBSENT: अणु
		/* size should have been a काष्ठा member */
		sमाप_प्रकार len = माप(user_kdgkb->kb_string);

		kbs = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!kbs)
			वापस -ENOMEM;

		spin_lock_irqsave(&func_buf_lock, flags);
		len = strlcpy(kbs, func_table[kb_func] ? : "", len);
		spin_unlock_irqrestore(&func_buf_lock, flags);

		ret = copy_to_user(user_kdgkb->kb_string, kbs, len + 1) ?
			-EFAULT : 0;

		अवरोध;
	पूर्ण
	हाल KDSKBSENT:
		अगर (!perm || !capable(CAP_SYS_TTY_CONFIG))
			वापस -EPERM;

		kbs = strndup_user(user_kdgkb->kb_string,
				माप(user_kdgkb->kb_string));
		अगर (IS_ERR(kbs))
			वापस PTR_ERR(kbs);

		spin_lock_irqsave(&func_buf_lock, flags);
		kbs = vt_kdskbsent(kbs, kb_func);
		spin_unlock_irqrestore(&func_buf_lock, flags);

		ret = 0;
		अवरोध;
	पूर्ण

	kमुक्त(kbs);

	वापस ret;
पूर्ण

पूर्णांक vt_करो_kdskled(पूर्णांक console, पूर्णांक cmd, अचिन्हित दीर्घ arg, पूर्णांक perm)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
        अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर ucval;

        चयन(cmd) अणु
	/* the ioctls below पढ़ो/set the flags usually shown in the leds */
	/* करोn't use them - they will go away without warning */
	हाल KDGKBLED:
                spin_lock_irqsave(&kbd_event_lock, flags);
		ucval = kb->ledflagstate | (kb->शेष_ledflagstate << 4);
                spin_unlock_irqrestore(&kbd_event_lock, flags);
		वापस put_user(ucval, (अक्षर __user *)arg);

	हाल KDSKBLED:
		अगर (!perm)
			वापस -EPERM;
		अगर (arg & ~0x77)
			वापस -EINVAL;
                spin_lock_irqsave(&led_lock, flags);
		kb->ledflagstate = (arg & 7);
		kb->शेष_ledflagstate = ((arg >> 4) & 7);
		set_leds();
                spin_unlock_irqrestore(&led_lock, flags);
		वापस 0;

	/* the ioctls below only set the lights, not the functions */
	/* क्रम those, see KDGKBLED and KDSKBLED above */
	हाल KDGETLED:
		ucval = getledstate();
		वापस put_user(ucval, (अक्षर __user *)arg);

	हाल KDSETLED:
		अगर (!perm)
			वापस -EPERM;
		setledstate(kb, arg);
		वापस 0;
        पूर्ण
        वापस -ENOIOCTLCMD;
पूर्ण

पूर्णांक vt_करो_kdgkbmode(पूर्णांक console)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
	/* This is a spot पढ़ो so needs no locking */
	चयन (kb->kbdmode) अणु
	हाल VC_RAW:
		वापस K_RAW;
	हाल VC_MEDIUMRAW:
		वापस K_MEDIUMRAW;
	हाल VC_UNICODE:
		वापस K_UNICODE;
	हाल VC_OFF:
		वापस K_OFF;
	शेष:
		वापस K_XLATE;
	पूर्ण
पूर्ण

/**
 *	vt_करो_kdgkbmeta		-	report meta status
 *	@console: console to report
 *
 *	Report the meta flag status of this console
 */
पूर्णांक vt_करो_kdgkbmeta(पूर्णांक console)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
        /* Again a spot पढ़ो so no locking */
	वापस vc_kbd_mode(kb, VC_META) ? K_ESCPREFIX : K_METABIT;
पूर्ण

/**
 *	vt_reset_unicode	-	reset the unicode status
 *	@console: console being reset
 *
 *	Restore the unicode console state to its शेष
 */
व्योम vt_reset_unicode(पूर्णांक console)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kbd_event_lock, flags);
	kbd_table[console].kbdmode = शेष_utf8 ? VC_UNICODE : VC_XLATE;
	spin_unlock_irqrestore(&kbd_event_lock, flags);
पूर्ण

/**
 *	vt_get_shअगरt_state	-	shअगरt bit state
 *
 *	Report the shअगरt bits from the keyboard state. We have to export
 *	this to support some oddities in the vt layer.
 */
पूर्णांक vt_get_shअगरt_state(व्योम)
अणु
        /* Don't lock as this is a transient report */
        वापस shअगरt_state;
पूर्ण

/**
 *	vt_reset_keyboard	-	reset keyboard state
 *	@console: console to reset
 *
 *	Reset the keyboard bits क्रम a console as part of a general console
 *	reset event
 */
व्योम vt_reset_keyboard(पूर्णांक console)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kbd_event_lock, flags);
	set_vc_kbd_mode(kb, VC_REPEAT);
	clr_vc_kbd_mode(kb, VC_CKMODE);
	clr_vc_kbd_mode(kb, VC_APPLIC);
	clr_vc_kbd_mode(kb, VC_CRLF);
	kb->lockstate = 0;
	kb->slockstate = 0;
	spin_lock(&led_lock);
	kb->ledmode = LED_SHOW_FLAGS;
	kb->ledflagstate = kb->शेष_ledflagstate;
	spin_unlock(&led_lock);
	/* करो not करो set_leds here because this causes an endless tasklet loop
	   when the keyboard hasn't been initialized yet */
	spin_unlock_irqrestore(&kbd_event_lock, flags);
पूर्ण

/**
 *	vt_get_kbd_mode_bit	-	पढ़ो keyboard status bits
 *	@console: console to पढ़ो from
 *	@bit: mode bit to पढ़ो
 *
 *	Report back a vt mode bit. We करो this without locking so the
 *	caller must be sure that there are no synchronization needs
 */

पूर्णांक vt_get_kbd_mode_bit(पूर्णांक console, पूर्णांक bit)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
	वापस vc_kbd_mode(kb, bit);
पूर्ण

/**
 *	vt_set_kbd_mode_bit	-	पढ़ो keyboard status bits
 *	@console: console to पढ़ो from
 *	@bit: mode bit to पढ़ो
 *
 *	Set a vt mode bit. We करो this without locking so the
 *	caller must be sure that there are no synchronization needs
 */

व्योम vt_set_kbd_mode_bit(पूर्णांक console, पूर्णांक bit)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kbd_event_lock, flags);
	set_vc_kbd_mode(kb, bit);
	spin_unlock_irqrestore(&kbd_event_lock, flags);
पूर्ण

/**
 *	vt_clr_kbd_mode_bit	-	पढ़ो keyboard status bits
 *	@console: console to पढ़ो from
 *	@bit: mode bit to पढ़ो
 *
 *	Report back a vt mode bit. We करो this without locking so the
 *	caller must be sure that there are no synchronization needs
 */

व्योम vt_clr_kbd_mode_bit(पूर्णांक console, पूर्णांक bit)
अणु
	काष्ठा kbd_काष्ठा *kb = kbd_table + console;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kbd_event_lock, flags);
	clr_vc_kbd_mode(kb, bit);
	spin_unlock_irqrestore(&kbd_event_lock, flags);
पूर्ण
