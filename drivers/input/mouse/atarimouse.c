<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Atari mouse driver क्रम Linux/m68k
 *
 *  Copyright (c) 2005 Michael Schmitz
 *
 *  Based on:
 *  Amiga mouse driver क्रम Linux/m68k
 *
 *  Copyright (c) 2000-2002 Vojtech Pavlik
 */
/*
 * The low level init and पूर्णांकerrupt stuff is handled in arch/mm68k/atari/atakeyb.c
 * (the keyboard ACIA also handles the mouse and joystick data, and the keyboard
 * पूर्णांकerrupt is shared with the MIDI ACIA so MIDI data also get handled there).
 * This driver only deals with handing key events off to the input layer.
 *
 * Largely based on the old:
 *
 * Atari Mouse Driver क्रम Linux
 * by Robert de Vries (robert@and.nl) 19Jul93
 *
 * 16 Nov 1994 Andreas Schwab
 * Compatibility with busmouse
 * Support क्रम three button mouse (shamelessly stolen from MiNT)
 * third button wired to one of the joystick directions on joystick 1
 *
 * 1996/02/11 Andreas Schwab
 * Module support
 * Allow multiple खोलो's
 *
 * Converted to use new generic busmouse code.  5 Apr 1998
 *   Russell King <rmk@arm.uk.linux.org>
 */



#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/setup.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/atarikb.h>
#समावेश <यंत्र/atariपूर्णांकs.h>

MODULE_AUTHOR("Michael Schmitz <schmitz@biophys.uni-duesseldorf.de>");
MODULE_DESCRIPTION("Atari mouse driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक mouse_threshold[2] = अणु2, 2पूर्ण;
module_param_array(mouse_threshold, पूर्णांक, शून्य, 0);

#अगर_घोषित FIXED_ATARI_JOYSTICK
बाह्य पूर्णांक atari_mouse_buttons;
#पूर्ण_अगर

अटल काष्ठा input_dev *atamouse_dev;

अटल व्योम atamouse_पूर्णांकerrupt(अक्षर *buf)
अणु
	पूर्णांक buttons, dx, dy;

	buttons = (buf[0] & 1) | ((buf[0] & 2) << 1);
#अगर_घोषित FIXED_ATARI_JOYSTICK
	buttons |= atari_mouse_buttons & 2;
	atari_mouse_buttons = buttons;
#पूर्ण_अगर

	/* only relative events get here */
	dx = buf[1];
	dy = buf[2];

	input_report_rel(atamouse_dev, REL_X, dx);
	input_report_rel(atamouse_dev, REL_Y, dy);

	input_report_key(atamouse_dev, BTN_LEFT,   buttons & 0x4);
	input_report_key(atamouse_dev, BTN_MIDDLE, buttons & 0x2);
	input_report_key(atamouse_dev, BTN_RIGHT,  buttons & 0x1);

	input_sync(atamouse_dev);

	वापस;
पूर्ण

अटल पूर्णांक atamouse_खोलो(काष्ठा input_dev *dev)
अणु
#अगर_घोषित FIXED_ATARI_JOYSTICK
	atari_mouse_buttons = 0;
#पूर्ण_अगर
	ikbd_mouse_y0_top();
	ikbd_mouse_thresh(mouse_threshold[0], mouse_threshold[1]);
	ikbd_mouse_rel_pos();
	atari_input_mouse_पूर्णांकerrupt_hook = atamouse_पूर्णांकerrupt;

	वापस 0;
पूर्ण

अटल व्योम atamouse_बंद(काष्ठा input_dev *dev)
अणु
	ikbd_mouse_disable();
	atari_input_mouse_पूर्णांकerrupt_hook = शून्य;
पूर्ण

अटल पूर्णांक __init atamouse_init(व्योम)
अणु
	पूर्णांक error;

	अगर (!MACH_IS_ATARI || !ATARIHW_PRESENT(ST_MFP))
		वापस -ENODEV;

	error = atari_keyb_init();
	अगर (error)
		वापस error;

	atamouse_dev = input_allocate_device();
	अगर (!atamouse_dev)
		वापस -ENOMEM;

	atamouse_dev->name = "Atari mouse";
	atamouse_dev->phys = "atamouse/input0";
	atamouse_dev->id.bustype = BUS_HOST;
	atamouse_dev->id.venकरोr = 0x0001;
	atamouse_dev->id.product = 0x0002;
	atamouse_dev->id.version = 0x0100;

	atamouse_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
	atamouse_dev->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y);
	atamouse_dev->keybit[BIT_WORD(BTN_LEFT)] = BIT_MASK(BTN_LEFT) |
		BIT_MASK(BTN_MIDDLE) | BIT_MASK(BTN_RIGHT);

	atamouse_dev->खोलो = atamouse_खोलो;
	atamouse_dev->बंद = atamouse_बंद;

	error = input_रेजिस्टर_device(atamouse_dev);
	अगर (error) अणु
		input_मुक्त_device(atamouse_dev);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास atamouse_निकास(व्योम)
अणु
	input_unरेजिस्टर_device(atamouse_dev);
पूर्ण

module_init(atamouse_init);
module_निकास(atamouse_निकास);
