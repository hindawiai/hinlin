<शैली गुरु>
/*
 * Kernel Debugger Architecture Dependent Console I/O handler
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.
 *
 * Copyright (c) 1999-2006 Silicon Graphics, Inc.  All Rights Reserved.
 * Copyright (c) 2009 Wind River Systems, Inc.  All Rights Reserved.
 */

#समावेश <linux/kdb.h>
#समावेश <linux/keyboard.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>

/* Keyboard Controller Registers on normal PCs. */

#घोषणा KBD_STATUS_REG		0x64	/* Status रेजिस्टर (R) */
#घोषणा KBD_DATA_REG		0x60	/* Keyboard data रेजिस्टर (R/W) */

/* Status Register Bits */

#घोषणा KBD_STAT_OBF 		0x01	/* Keyboard output buffer full */
#घोषणा KBD_STAT_MOUSE_OBF	0x20	/* Mouse output buffer full */

अटल पूर्णांक kbd_exists;
अटल पूर्णांक kbd_last_ret;

/*
 * Check अगर the keyboard controller has a keypress क्रम us.
 * Some parts (Enter Release, LED change) are still blocking polled here,
 * but hopefully they are all लघु.
 */
पूर्णांक kdb_get_kbd_अक्षर(व्योम)
अणु
	पूर्णांक scancode, scanstatus;
	अटल पूर्णांक shअगरt_lock;	/* CAPS LOCK state (0-off, 1-on) */
	अटल पूर्णांक shअगरt_key;	/* Shअगरt next keypress */
	अटल पूर्णांक ctrl_key;
	u_लघु keyअक्षर;

	अगर (KDB_FLAG(NO_I8042) || KDB_FLAG(NO_VT_CONSOLE) ||
	    (inb(KBD_STATUS_REG) == 0xff && inb(KBD_DATA_REG) == 0xff)) अणु
		kbd_exists = 0;
		वापस -1;
	पूर्ण
	kbd_exists = 1;

	अगर ((inb(KBD_STATUS_REG) & KBD_STAT_OBF) == 0)
		वापस -1;

	/*
	 * Fetch the scancode
	 */
	scancode = inb(KBD_DATA_REG);
	scanstatus = inb(KBD_STATUS_REG);

	/*
	 * Ignore mouse events.
	 */
	अगर (scanstatus & KBD_STAT_MOUSE_OBF)
		वापस -1;

	/*
	 * Ignore release, trigger on make
	 * (except क्रम shअगरt keys, where we want to
	 *  keep the shअगरt state so दीर्घ as the key is
	 *  held करोwn).
	 */

	अगर (((scancode&0x7f) == 0x2a) || ((scancode&0x7f) == 0x36)) अणु
		/*
		 * Next key may use shअगरt table
		 */
		अगर ((scancode & 0x80) == 0)
			shअगरt_key = 1;
		अन्यथा
			shअगरt_key = 0;
		वापस -1;
	पूर्ण

	अगर ((scancode&0x7f) == 0x1d) अणु
		/*
		 * Left ctrl key
		 */
		अगर ((scancode & 0x80) == 0)
			ctrl_key = 1;
		अन्यथा
			ctrl_key = 0;
		वापस -1;
	पूर्ण

	अगर ((scancode & 0x80) != 0) अणु
		अगर (scancode == 0x9c)
			kbd_last_ret = 0;
		वापस -1;
	पूर्ण

	scancode &= 0x7f;

	/*
	 * Translate scancode
	 */

	अगर (scancode == 0x3a) अणु
		/*
		 * Toggle caps lock
		 */
		shअगरt_lock ^= 1;

#अगर_घोषित	KDB_BLINK_LED
		kdb_toggleled(0x4);
#पूर्ण_अगर
		वापस -1;
	पूर्ण

	अगर (scancode == 0x0e) अणु
		/*
		 * Backspace
		 */
		वापस 8;
	पूर्ण

	/* Special Key */
	चयन (scancode) अणु
	हाल 0xF: /* Tab */
		वापस 9;
	हाल 0x53: /* Del */
		वापस 4;
	हाल 0x47: /* Home */
		वापस 1;
	हाल 0x4F: /* End */
		वापस 5;
	हाल 0x4B: /* Left */
		वापस 2;
	हाल 0x48: /* Up */
		वापस 16;
	हाल 0x50: /* Down */
		वापस 14;
	हाल 0x4D: /* Right */
		वापस 6;
	पूर्ण

	अगर (scancode == 0xe0)
		वापस -1;

	/*
	 * For Japanese 86/106 keyboards
	 * 	See comment in drivers/अक्षर/pc_keyb.c.
	 * 	- Masahiro Adegawa
	 */
	अगर (scancode == 0x73)
		scancode = 0x59;
	अन्यथा अगर (scancode == 0x7d)
		scancode = 0x7c;

	अगर (!shअगरt_lock && !shअगरt_key && !ctrl_key) अणु
		keyअक्षर = plain_map[scancode];
	पूर्ण अन्यथा अगर ((shअगरt_lock || shअगरt_key) && key_maps[1]) अणु
		keyअक्षर = key_maps[1][scancode];
	पूर्ण अन्यथा अगर (ctrl_key && key_maps[4]) अणु
		keyअक्षर = key_maps[4][scancode];
	पूर्ण अन्यथा अणु
		keyअक्षर = 0x0020;
		kdb_म_लिखो("Unknown state/scancode (%d)\n", scancode);
	पूर्ण
	keyअक्षर &= 0x0fff;
	अगर (keyअक्षर == '\t')
		keyअक्षर = ' ';
	चयन (KTYP(keyअक्षर)) अणु
	हाल KT_LETTER:
	हाल KT_LATIN:
		अगर (है_छाप(keyअक्षर))
			अवरोध;		/* prपूर्णांकable अक्षरacters */
		fallthrough;
	हाल KT_SPEC:
		अगर (keyअक्षर == K_ENTER)
			अवरोध;
		fallthrough;
	शेष:
		वापस -1;	/* ignore unprपूर्णांकables */
	पूर्ण

	अगर (scancode == 0x1c) अणु
		kbd_last_ret = 1;
		वापस 13;
	पूर्ण

	वापस keyअक्षर & 0xff;
पूर्ण
EXPORT_SYMBOL_GPL(kdb_get_kbd_अक्षर);

/*
 * Best efक्रमt cleanup of ENTER अवरोध codes on leaving KDB. Called on
 * निकासing KDB, when we know we processed an ENTER or KP ENTER scan
 * code.
 */
व्योम kdb_kbd_cleanup_state(व्योम)
अणु
	पूर्णांक scancode, scanstatus;

	/*
	 * Nothing to clean up, since either
	 * ENTER was never pressed, or has alपढ़ोy
	 * gotten cleaned up.
	 */
	अगर (!kbd_last_ret)
		वापस;

	kbd_last_ret = 0;
	/*
	 * Enter key. Need to असलorb the अवरोध code here, lest it माला_लो
	 * leaked out अगर we निकास KDB as the result of processing 'g'.
	 *
	 * This has several पूर्णांकeresting implications:
	 * + Need to handle KP ENTER, which has अवरोध code 0xe0 0x9c.
	 * + Need to handle repeat ENTER and repeat KP ENTER. Repeats
	 *   only get a अवरोध code at the end of the repeated
	 *   sequence. This means we can't propagate the repeated key
	 *   press, and must swallow it away.
	 * + Need to handle possible PS/2 mouse input.
	 * + Need to handle mashed keys.
	 */

	जबतक (1) अणु
		जबतक ((inb(KBD_STATUS_REG) & KBD_STAT_OBF) == 0)
			cpu_relax();

		/*
		 * Fetch the scancode.
		 */
		scancode = inb(KBD_DATA_REG);
		scanstatus = inb(KBD_STATUS_REG);

		/*
		 * Skip mouse input.
		 */
		अगर (scanstatus & KBD_STAT_MOUSE_OBF)
			जारी;

		/*
		 * If we see 0xe0, this is either a अवरोध code क्रम KP
		 * ENTER, or a repeat make क्रम KP ENTER. Either way,
		 * since the second byte is equivalent to an ENTER,
		 * skip the 0xe0 and try again.
		 *
		 * If we see 0x1c, this must be a repeat ENTER or KP
		 * ENTER (and we swallowed 0xe0 beक्रमe). Try again.
		 *
		 * We can also see make and अवरोध codes क्रम other keys
		 * mashed beक्रमe or after pressing ENTER. Thus, अगर we
		 * see anything other than 0x9c, we have to try again.
		 *
		 * Note, अगर you held some key as ENTER was depressed,
		 * that अवरोध code would get leaked out.
		 */
		अगर (scancode != 0x9c)
			जारी;

		वापस;
	पूर्ण
पूर्ण
