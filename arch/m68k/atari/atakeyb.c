<शैली गुरु>
/*
 * Atari Keyboard driver क्रम 680x0 Linux
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

/*
 * Atari support by Robert de Vries
 * enhanced by Bjoern Brauel and Roman Hodek
 *
 * 2.6 and input cleanup (हटाओd स्वतःrepeat stuff) क्रम 2.6.21
 * 06/07 Michael Schmitz
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/keyboard.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kd.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/init.h>
#समावेश <linux/kbd_kern.h>

#समावेश <यंत्र/atariपूर्णांकs.h>
#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/atarikb.h>
#समावेश <यंत्र/atari_joystick.h>
#समावेश <यंत्र/irq.h>


/* Hook क्रम MIDI serial driver */
व्योम (*atari_MIDI_पूर्णांकerrupt_hook) (व्योम);
/* Hook क्रम keyboard inputdev  driver */
व्योम (*atari_input_keyboard_पूर्णांकerrupt_hook) (अचिन्हित अक्षर, अक्षर);
/* Hook क्रम mouse inputdev  driver */
व्योम (*atari_input_mouse_पूर्णांकerrupt_hook) (अक्षर *);
EXPORT_SYMBOL(atari_input_keyboard_पूर्णांकerrupt_hook);
EXPORT_SYMBOL(atari_input_mouse_पूर्णांकerrupt_hook);

/* variables क्रम IKBD self test: */

/* state: 0: off; >0: in progress; >1: 0xf1 received */
अटल अस्थिर पूर्णांक ikbd_self_test;
/* बारtamp when last received a अक्षर */
अटल अस्थिर अचिन्हित दीर्घ self_test_last_rcv;
/* biपंचांगap of keys reported as broken */
अटल अचिन्हित दीर्घ broken_keys[128/(माप(अचिन्हित दीर्घ)*8)] = अणु 0, पूर्ण;

#घोषणा BREAK_MASK	(0x80)

/*
 * ++roman: The following changes were applied manually:
 *
 *  - The Alt (= Meta) key works in combination with Shअगरt and
 *    Control, e.g. Alt+Shअगरt+a sends Meta-A (0xc1), Alt+Control+A sends
 *    Meta-Ctrl-A (0x81) ...
 *
 *  - The parentheses on the keypad send '(' and ')' with all
 *    modअगरiers (as would करो e.g. keypad '+'), but they cannot be used as
 *    application keys (i.e. sending Esc O c).
 *
 *  - HELP and UNDO are mapped to be F21 and F24, resp, that send the
 *    codes "\E[M" and "\E[P". (This is better than the old mapping to
 *    F11 and F12, because these codes are on Shअगरt+F1/2 anyway.) This
 *    way, applications that allow their own keyboard mappings
 *    (e.g. tcsh, X Winकरोws) can be configured to use them in the way
 *    the label suggests (providing help or unकरोing).
 *
 *  - Console चयनing is करोne with Alt+Fx (consoles 1..10) and
 *    Shअगरt+Alt+Fx (consoles 11..20).
 *
 *  - The misc. special function implemented in the kernel are mapped
 *    to the following key combinations:
 *
 *      ClrHome          -> Home/Find
 *      Shअगरt + ClrHome  -> End/Select
 *      Shअगरt + Up       -> Page Up
 *      Shअगरt + Down     -> Page Down
 *      Alt + Help       -> show प्रणाली status
 *      Shअगरt + Help     -> show memory info
 *      Ctrl + Help      -> show रेजिस्टरs
 *      Ctrl + Alt + Del -> Reboot
 *      Alt + Unकरो       -> चयन to last console
 *      Shअगरt + Unकरो     -> send पूर्णांकerrupt
 *      Alt + Insert     -> stop/start output (same as ^S/^Q)
 *      Alt + Up         -> Scroll back console (अगर implemented)
 *      Alt + Down       -> Scroll क्रमward console (अगर implemented)
 *      Alt + CapsLock   -> NumLock
 *
 * ++Andreas:
 *
 *  - Help mapped to K_HELP
 *  - Unकरो mapped to K_UNDO (= K_F246)
 *  - Keypad Left/Right Parenthesis mapped to new K_PPAREN[LR]
 */

प्रकार क्रमागत kb_state_t अणु
	KEYBOARD, AMOUSE, RMOUSE, JOYSTICK, CLOCK, RESYNC
पूर्ण KB_STATE_T;

#घोषणा	IS_SYNC_CODE(sc)	((sc) >= 0x04 && (sc) <= 0xfb)

प्रकार काष्ठा keyboard_state अणु
	अचिन्हित अक्षर buf[6];
	पूर्णांक len;
	KB_STATE_T state;
पूर्ण KEYBOARD_STATE;

KEYBOARD_STATE kb_state;

/* ++roman: If a keyboard overrun happened, we can't tell in general how much
 * bytes have been lost and in which state of the packet काष्ठाure we are now.
 * This usually causes keyboards bytes to be पूर्णांकerpreted as mouse movements
 * and vice versa, which is very annoying. It seems better to throw away some
 * bytes (that are usually mouse bytes) than to misपूर्णांकerpret them. Thereक्रमe I
 * पूर्णांकroduced the RESYNC state क्रम IKBD data. In this state, the bytes up to
 * one that really looks like a key event (0x04..0xf2) or the start of a mouse
 * packet (0xf8..0xfb) are thrown away, but at most 2 bytes. This at least
 * speeds up the resynchronization of the event काष्ठाure, even अगर maybe a
 * mouse movement is lost. However, nothing is perfect. For bytes 0x01..0x03,
 * it's really hard to decide whether they're mouse or keyboard bytes. Since
 * overruns usually occur when moving the Atari mouse rapidly, they're seen as
 * mouse bytes here. If this is wrong, only a make code of the keyboard माला_लो
 * lost, which isn't too bad. Losing a अवरोध code would be disastrous,
 * because then the keyboard repeat strikes...
 */

अटल irqवापस_t atari_keyboard_पूर्णांकerrupt(पूर्णांक irq, व्योम *dummy)
अणु
	u_अक्षर acia_stat;
	पूर्णांक scancode;
	पूर्णांक अवरोध_flag;

repeat:
	अगर (acia.mid_ctrl & ACIA_IRQ)
		अगर (atari_MIDI_पूर्णांकerrupt_hook)
			atari_MIDI_पूर्णांकerrupt_hook();
	acia_stat = acia.key_ctrl;
	/* check out अगर the पूर्णांकerrupt came from this ACIA */
	अगर (!((acia_stat | acia.mid_ctrl) & ACIA_IRQ))
		वापस IRQ_HANDLED;

	अगर (acia_stat & ACIA_OVRN) अणु
		/* a very fast typist or a slow प्रणाली, give a warning */
		/* ...happens often अगर पूर्णांकerrupts were disabled क्रम too दीर्घ */
		pr_debug("Keyboard overrun\n");
		scancode = acia.key_data;
		अगर (ikbd_self_test)
			/* During self test, करोn't करो resyncing, just process the code */
			जाओ पूर्णांकerpret_scancode;
		अन्यथा अगर (IS_SYNC_CODE(scancode)) अणु
			/* This code seem alपढ़ोy to be the start of a new packet or a
			 * single scancode */
			kb_state.state = KEYBOARD;
			जाओ पूर्णांकerpret_scancode;
		पूर्ण अन्यथा अणु
			/* Go to RESYNC state and skip this byte */
			kb_state.state = RESYNC;
			kb_state.len = 1;	/* skip max. 1 another byte */
			जाओ repeat;
		पूर्ण
	पूर्ण

	अगर (acia_stat & ACIA_RDRF) अणु
		/* received a अक्षरacter */
		scancode = acia.key_data;	/* get it or reset the ACIA, I'll get it! */
	पूर्णांकerpret_scancode:
		चयन (kb_state.state) अणु
		हाल KEYBOARD:
			चयन (scancode) अणु
			हाल 0xF7:
				kb_state.state = AMOUSE;
				kb_state.len = 0;
				अवरोध;

			हाल 0xF8:
			हाल 0xF9:
			हाल 0xFA:
			हाल 0xFB:
				kb_state.state = RMOUSE;
				kb_state.len = 1;
				kb_state.buf[0] = scancode;
				अवरोध;

			हाल 0xFC:
				kb_state.state = CLOCK;
				kb_state.len = 0;
				अवरोध;

			हाल 0xFE:
			हाल 0xFF:
				kb_state.state = JOYSTICK;
				kb_state.len = 1;
				kb_state.buf[0] = scancode;
				अवरोध;

			हाल 0xF1:
				/* during self-test, note that 0xf1 received */
				अगर (ikbd_self_test) अणु
					++ikbd_self_test;
					self_test_last_rcv = jअगरfies;
					अवरोध;
				पूर्ण
				fallthrough;

			शेष:
				अवरोध_flag = scancode & BREAK_MASK;
				scancode &= ~BREAK_MASK;
				अगर (ikbd_self_test) अणु
					/* Scancodes sent during the self-test stand क्रम broken
					 * keys (keys being करोwn). The code *should* be a अवरोध
					 * code, but nevertheless some AT keyboard पूर्णांकerfaces send
					 * make codes instead. Thereक्रमe, simply ignore
					 * अवरोध_flag...
					 */
					पूर्णांक keyval, keytyp;

					set_bit(scancode, broken_keys);
					self_test_last_rcv = jअगरfies;
					/* new Linux scancodes; approx. */
					keyval = scancode;
					keytyp = KTYP(keyval) - 0xf0;
					keyval = KVAL(keyval);

					pr_warn("Key with scancode %d ", scancode);
					अगर (keytyp == KT_LATIN || keytyp == KT_LETTER) अणु
						अगर (keyval < ' ')
							pr_cont("('^%c') ", keyval + '@');
						अन्यथा
							pr_cont("('%c') ", keyval);
					पूर्ण
					pr_cont("is broken -- will be ignored.\n");
					अवरोध;
				पूर्ण अन्यथा अगर (test_bit(scancode, broken_keys))
					अवरोध;

				अगर (atari_input_keyboard_पूर्णांकerrupt_hook)
					atari_input_keyboard_पूर्णांकerrupt_hook((अचिन्हित अक्षर)scancode, !अवरोध_flag);
				अवरोध;
			पूर्ण
			अवरोध;

		हाल AMOUSE:
			kb_state.buf[kb_state.len++] = scancode;
			अगर (kb_state.len == 5) अणु
				kb_state.state = KEYBOARD;
				/* not yet used */
				/* wake up someone रुकोing क्रम this */
			पूर्ण
			अवरोध;

		हाल RMOUSE:
			kb_state.buf[kb_state.len++] = scancode;
			अगर (kb_state.len == 3) अणु
				kb_state.state = KEYBOARD;
				अगर (atari_input_mouse_पूर्णांकerrupt_hook)
					atari_input_mouse_पूर्णांकerrupt_hook(kb_state.buf);
			पूर्ण
			अवरोध;

		हाल JOYSTICK:
			kb_state.buf[1] = scancode;
			kb_state.state = KEYBOARD;
#अगर_घोषित FIXED_ATARI_JOYSTICK
			atari_joystick_पूर्णांकerrupt(kb_state.buf);
#पूर्ण_अगर
			अवरोध;

		हाल CLOCK:
			kb_state.buf[kb_state.len++] = scancode;
			अगर (kb_state.len == 6) अणु
				kb_state.state = KEYBOARD;
				/* wake up someone रुकोing क्रम this.
				   But will this ever be used, as Linux keeps its own समय.
				   Perhaps क्रम synchronization purposes? */
				/* wake_up_पूर्णांकerruptible(&घड़ी_रुको); */
			पूर्ण
			अवरोध;

		हाल RESYNC:
			अगर (kb_state.len <= 0 || IS_SYNC_CODE(scancode)) अणु
				kb_state.state = KEYBOARD;
				जाओ पूर्णांकerpret_scancode;
			पूर्ण
			kb_state.len--;
			अवरोध;
		पूर्ण
	पूर्ण

#अगर 0
	अगर (acia_stat & ACIA_CTS)
		/* cannot happen */;
#पूर्ण_अगर

	अगर (acia_stat & (ACIA_FE | ACIA_PE)) अणु
		pr_err("Error in keyboard communication\n");
	पूर्ण

	/* handle_scancode() can take a lot of समय, so check again अगर
	 * some अक्षरacter arrived
	 */
	जाओ repeat;
पूर्ण

/*
 * I ग_लिखो to the keyboard without using पूर्णांकerrupts, I poll instead.
 * This takes क्रम the maximum length string allowed (7) at 7812.5 baud
 * 8 data 1 start 1 stop bit: 9.0 ms
 * If this takes too दीर्घ क्रम normal operation, पूर्णांकerrupt driven writing
 * is the solution. (I made a feeble attempt in that direction but I
 * kept it simple क्रम now.)
 */
व्योम ikbd_ग_लिखो(स्थिर अक्षर *str, पूर्णांक len)
अणु
	u_अक्षर acia_stat;

	अगर ((len < 1) || (len > 7))
		panic("ikbd: maximum string length exceeded");
	जबतक (len) अणु
		acia_stat = acia.key_ctrl;
		अगर (acia_stat & ACIA_TDRE) अणु
			acia.key_data = *str++;
			len--;
		पूर्ण
	पूर्ण
पूर्ण

/* Reset (without touching the घड़ी) */
व्योम ikbd_reset(व्योम)
अणु
	अटल स्थिर अक्षर cmd[2] = अणु 0x80, 0x01 पूर्ण;

	ikbd_ग_लिखो(cmd, 2);

	/*
	 * अगर all's well code 0xF1 is वापसed, अन्यथा the अवरोध codes of
	 * all keys making contact
	 */
पूर्ण

/* Set mouse button action */
व्योम ikbd_mouse_button_action(पूर्णांक mode)
अणु
	अक्षर cmd[2] = अणु 0x07, mode पूर्ण;

	ikbd_ग_लिखो(cmd, 2);
पूर्ण

/* Set relative mouse position reporting */
व्योम ikbd_mouse_rel_pos(व्योम)
अणु
	अटल स्थिर अक्षर cmd[1] = अणु 0x08 पूर्ण;

	ikbd_ग_लिखो(cmd, 1);
पूर्ण
EXPORT_SYMBOL(ikbd_mouse_rel_pos);

/* Set असलolute mouse position reporting */
व्योम ikbd_mouse_असल_pos(पूर्णांक xmax, पूर्णांक ymax)
अणु
	अक्षर cmd[5] = अणु 0x09, xmax>>8, xmax&0xFF, ymax>>8, ymax&0xFF पूर्ण;

	ikbd_ग_लिखो(cmd, 5);
पूर्ण

/* Set mouse keycode mode */
व्योम ikbd_mouse_kbd_mode(पूर्णांक dx, पूर्णांक dy)
अणु
	अक्षर cmd[3] = अणु 0x0A, dx, dy पूर्ण;

	ikbd_ग_लिखो(cmd, 3);
पूर्ण

/* Set mouse threshold */
व्योम ikbd_mouse_thresh(पूर्णांक x, पूर्णांक y)
अणु
	अक्षर cmd[3] = अणु 0x0B, x, y पूर्ण;

	ikbd_ग_लिखो(cmd, 3);
पूर्ण
EXPORT_SYMBOL(ikbd_mouse_thresh);

/* Set mouse scale */
व्योम ikbd_mouse_scale(पूर्णांक x, पूर्णांक y)
अणु
	अक्षर cmd[3] = अणु 0x0C, x, y पूर्ण;

	ikbd_ग_लिखो(cmd, 3);
पूर्ण

/* Interrogate mouse position */
व्योम ikbd_mouse_pos_get(पूर्णांक *x, पूर्णांक *y)
अणु
	अटल स्थिर अक्षर cmd[1] = अणु 0x0D पूर्ण;

	ikbd_ग_लिखो(cmd, 1);

	/* रुको क्रम वापसing bytes */
पूर्ण

/* Load mouse position */
व्योम ikbd_mouse_pos_set(पूर्णांक x, पूर्णांक y)
अणु
	अक्षर cmd[6] = अणु 0x0E, 0x00, x>>8, x&0xFF, y>>8, y&0xFF पूर्ण;

	ikbd_ग_लिखो(cmd, 6);
पूर्ण

/* Set Y=0 at bottom */
व्योम ikbd_mouse_y0_bot(व्योम)
अणु
	अटल स्थिर अक्षर cmd[1] = अणु 0x0F पूर्ण;

	ikbd_ग_लिखो(cmd, 1);
पूर्ण

/* Set Y=0 at top */
व्योम ikbd_mouse_y0_top(व्योम)
अणु
	अटल स्थिर अक्षर cmd[1] = अणु 0x10 पूर्ण;

	ikbd_ग_लिखो(cmd, 1);
पूर्ण
EXPORT_SYMBOL(ikbd_mouse_y0_top);

/* Disable mouse */
व्योम ikbd_mouse_disable(व्योम)
अणु
	अटल स्थिर अक्षर cmd[1] = अणु 0x12 पूर्ण;

	ikbd_ग_लिखो(cmd, 1);
पूर्ण
EXPORT_SYMBOL(ikbd_mouse_disable);

/* Set joystick event reporting */
व्योम ikbd_joystick_event_on(व्योम)
अणु
	अटल स्थिर अक्षर cmd[1] = अणु 0x14 पूर्ण;

	ikbd_ग_लिखो(cmd, 1);
पूर्ण

/* Set joystick पूर्णांकerrogation mode */
व्योम ikbd_joystick_event_off(व्योम)
अणु
	अटल स्थिर अक्षर cmd[1] = अणु 0x15 पूर्ण;

	ikbd_ग_लिखो(cmd, 1);
पूर्ण

/* Joystick पूर्णांकerrogation */
व्योम ikbd_joystick_get_state(व्योम)
अणु
	अटल स्थिर अक्षर cmd[1] = अणु 0x16 पूर्ण;

	ikbd_ग_लिखो(cmd, 1);
पूर्ण

#अगर 0
/* This disables all other ikbd activities !!!! */
/* Set joystick monitoring */
व्योम ikbd_joystick_monitor(पूर्णांक rate)
अणु
	अटल स्थिर अक्षर cmd[2] = अणु 0x17, rate पूर्ण;

	ikbd_ग_लिखो(cmd, 2);

	kb_state.state = JOYSTICK_MONITOR;
पूर्ण
#पूर्ण_अगर

/* some joystick routines not in yet (0x18-0x19) */

/* Disable joysticks */
व्योम ikbd_joystick_disable(व्योम)
अणु
	अटल स्थिर अक्षर cmd[1] = अणु 0x1A पूर्ण;

	ikbd_ग_लिखो(cmd, 1);
पूर्ण

/*
 * The original code someबार left the पूर्णांकerrupt line of
 * the ACIAs low क्रमever. I hope, it is fixed now.
 *
 * Martin Rogge, 20 Aug 1995
 */

अटल पूर्णांक atari_keyb_करोne = 0;

पूर्णांक atari_keyb_init(व्योम)
अणु
	पूर्णांक error;

	अगर (atari_keyb_करोne)
		वापस 0;

	kb_state.state = KEYBOARD;
	kb_state.len = 0;

	error = request_irq(IRQ_MFP_ACIA, atari_keyboard_पूर्णांकerrupt, 0,
			    "keyboard,mouse,MIDI", atari_keyboard_पूर्णांकerrupt);
	अगर (error)
		वापस error;

	atari_turnoff_irq(IRQ_MFP_ACIA);
	करो अणु
		/* reset IKBD ACIA */
		acia.key_ctrl = ACIA_RESET |
				((atari_चयनes & ATARI_SWITCH_IKBD) ?
				 ACIA_RHTID : 0);
		(व्योम)acia.key_ctrl;
		(व्योम)acia.key_data;

		/* reset MIDI ACIA */
		acia.mid_ctrl = ACIA_RESET |
				((atari_चयनes & ATARI_SWITCH_MIDI) ?
				 ACIA_RHTID : 0);
		(व्योम)acia.mid_ctrl;
		(व्योम)acia.mid_data;

		/* भागide 500kHz by 64 gives 7812.5 baud */
		/* 8 data no parity 1 start 1 stop bit */
		/* receive पूर्णांकerrupt enabled */
		/* RTS low (except अगर चयन selected), transmit पूर्णांकerrupt disabled */
		acia.key_ctrl = (ACIA_DIV64|ACIA_D8N1S|ACIA_RIE) |
				((atari_चयनes & ATARI_SWITCH_IKBD) ?
				 ACIA_RHTID : ACIA_RLTID);

		acia.mid_ctrl = ACIA_DIV16 | ACIA_D8N1S |
				((atari_चयनes & ATARI_SWITCH_MIDI) ?
				 ACIA_RHTID : 0);

	/* make sure the पूर्णांकerrupt line is up */
	पूर्ण जबतक ((st_mfp.par_dt_reg & 0x10) == 0);

	/* enable ACIA Interrupts */
	st_mfp.active_edge &= ~0x10;
	atari_turnon_irq(IRQ_MFP_ACIA);

	ikbd_self_test = 1;
	ikbd_reset();
	/* रुको क्रम a period of inactivity (here: 0.25s), then assume the IKBD's
	 * self-test is finished */
	self_test_last_rcv = jअगरfies;
	जबतक (समय_beक्रमe(jअगरfies, self_test_last_rcv + HZ/4))
		barrier();
	/* अगर not incremented: no 0xf1 received */
	अगर (ikbd_self_test == 1)
		pr_err("Keyboard self test failed!\n");
	ikbd_self_test = 0;

	ikbd_mouse_disable();
	ikbd_joystick_disable();

#अगर_घोषित FIXED_ATARI_JOYSTICK
	atari_joystick_init();
#पूर्ण_अगर

	// flag init करोne
	atari_keyb_करोne = 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(atari_keyb_init);
