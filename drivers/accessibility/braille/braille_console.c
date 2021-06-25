<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Minimalistic braille device kernel support.
 *
 * By शेष, shows console messages on the braille device.
 * Pressing Insert चयनes to VC browsing.
 *
 *  Copyright (C) Samuel Thibault <samuel.thibault@ens-lyon.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/console.h>
#समावेश <linux/notअगरier.h>

#समावेश <linux/selection.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/consolemap.h>

#समावेश <linux/keyboard.h>
#समावेश <linux/kbd_kern.h>
#समावेश <linux/input.h>

MODULE_AUTHOR("samuel.thibault@ens-lyon.org");
MODULE_DESCRIPTION("braille device");
MODULE_LICENSE("GPL");

/*
 * Braille device support part.
 */

/* Emit various sounds */
अटल bool sound;
module_param(sound, bool, 0);
MODULE_PARM_DESC(sound, "emit sounds");

अटल व्योम beep(अचिन्हित पूर्णांक freq)
अणु
	अगर (sound)
		kd_mksound(freq, HZ/10);
पूर्ण

/* mini console */
#घोषणा WIDTH 40
#घोषणा BRAILLE_KEY KEY_INSERT
अटल u16 console_buf[WIDTH];
अटल पूर्णांक console_cursor;

/* mini view of VC */
अटल पूर्णांक vc_x, vc_y, lastvc_x, lastvc_y;

/* show console ? (or show VC) */
अटल पूर्णांक console_show = 1;
/* pending newline ? */
अटल पूर्णांक console_newline = 1;
अटल पूर्णांक lastVC = -1;

अटल काष्ठा console *braille_co;

/* Very VisioBraille-specअगरic */
अटल व्योम braille_ग_लिखो(u16 *buf)
अणु
	अटल u16 lastग_लिखो[WIDTH];
	अचिन्हित अक्षर data[1 + 1 + 2*WIDTH + 2 + 1], csum = 0, *c;
	u16 out;
	पूर्णांक i;

	अगर (!braille_co)
		वापस;

	अगर (!स_भेद(lastग_लिखो, buf, WIDTH * माप(*buf)))
		वापस;
	स_नकल(lastग_लिखो, buf, WIDTH * माप(*buf));

#घोषणा SOH 1
#घोषणा STX 2
#घोषणा ETX 2
#घोषणा EOT 4
#घोषणा ENQ 5
	data[0] = STX;
	data[1] = '>';
	csum ^= '>';
	c = &data[2];
	क्रम (i = 0; i < WIDTH; i++) अणु
		out = buf[i];
		अगर (out >= 0x100)
			out = '?';
		अन्यथा अगर (out == 0x00)
			out = ' ';
		csum ^= out;
		अगर (out <= 0x05) अणु
			*c++ = SOH;
			out |= 0x40;
		पूर्ण
		*c++ = out;
	पूर्ण

	अगर (csum <= 0x05) अणु
		*c++ = SOH;
		csum |= 0x40;
	पूर्ण
	*c++ = csum;
	*c++ = ETX;

	braille_co->ग_लिखो(braille_co, data, c - data);
पूर्ण

/* Follow the VC cursor*/
अटल व्योम vc_follow_cursor(काष्ठा vc_data *vc)
अणु
	vc_x = vc->state.x - (vc->state.x % WIDTH);
	vc_y = vc->state.y;
	lastvc_x = vc->state.x;
	lastvc_y = vc->state.y;
पूर्ण

/* Maybe the VC cursor moved, अगर so follow it */
अटल व्योम vc_maybe_cursor_moved(काष्ठा vc_data *vc)
अणु
	अगर (vc->state.x != lastvc_x || vc->state.y != lastvc_y)
		vc_follow_cursor(vc);
पूर्ण

/* Show portion of VC at vc_x, vc_y */
अटल व्योम vc_refresh(काष्ठा vc_data *vc)
अणु
	u16 buf[WIDTH];
	पूर्णांक i;

	क्रम (i = 0; i < WIDTH; i++) अणु
		u16 glyph = screen_glyph(vc,
				2 * (vc_x + i) + vc_y * vc->vc_size_row);
		buf[i] = inverse_translate(vc, glyph, 1);
	पूर्ण
	braille_ग_लिखो(buf);
पूर्ण

/*
 * Link to keyboard
 */

अटल पूर्णांक keyboard_notअगरier_call(काष्ठा notअगरier_block *blk,
				  अचिन्हित दीर्घ code, व्योम *_param)
अणु
	काष्ठा keyboard_notअगरier_param *param = _param;
	काष्ठा vc_data *vc = param->vc;
	पूर्णांक ret = NOTIFY_OK;

	अगर (!param->करोwn)
		वापस ret;

	चयन (code) अणु
	हाल KBD_KEYCODE:
		अगर (console_show) अणु
			अगर (param->value == BRAILLE_KEY) अणु
				console_show = 0;
				beep(880);
				vc_maybe_cursor_moved(vc);
				vc_refresh(vc);
				ret = NOTIFY_STOP;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = NOTIFY_STOP;
			चयन (param->value) अणु
			हाल KEY_INSERT:
				beep(440);
				console_show = 1;
				lastVC = -1;
				braille_ग_लिखो(console_buf);
				अवरोध;
			हाल KEY_LEFT:
				अगर (vc_x > 0) अणु
					vc_x -= WIDTH;
					अगर (vc_x < 0)
						vc_x = 0;
				पूर्ण अन्यथा अगर (vc_y >= 1) अणु
					beep(880);
					vc_y--;
					vc_x = vc->vc_cols-WIDTH;
				पूर्ण अन्यथा
					beep(220);
				अवरोध;
			हाल KEY_RIGHT:
				अगर (vc_x + WIDTH < vc->vc_cols) अणु
					vc_x += WIDTH;
				पूर्ण अन्यथा अगर (vc_y + 1 < vc->vc_rows) अणु
					beep(880);
					vc_y++;
					vc_x = 0;
				पूर्ण अन्यथा
					beep(220);
				अवरोध;
			हाल KEY_DOWN:
				अगर (vc_y + 1 < vc->vc_rows)
					vc_y++;
				अन्यथा
					beep(220);
				अवरोध;
			हाल KEY_UP:
				अगर (vc_y >= 1)
					vc_y--;
				अन्यथा
					beep(220);
				अवरोध;
			हाल KEY_HOME:
				vc_follow_cursor(vc);
				अवरोध;
			हाल KEY_PAGEUP:
				vc_x = 0;
				vc_y = 0;
				अवरोध;
			हाल KEY_PAGEDOWN:
				vc_x = 0;
				vc_y = vc->vc_rows-1;
				अवरोध;
			शेष:
				ret = NOTIFY_OK;
				अवरोध;
			पूर्ण
			अगर (ret == NOTIFY_STOP)
				vc_refresh(vc);
		पूर्ण
		अवरोध;
	हाल KBD_POST_KEYSYM:
	अणु
		अचिन्हित अक्षर type = KTYP(param->value) - 0xf0;
		अगर (type == KT_SPEC) अणु
			अचिन्हित अक्षर val = KVAL(param->value);
			पूर्णांक on_off = -1;

			चयन (val) अणु
			हाल KVAL(K_CAPS):
				on_off = vt_get_leds(fg_console, VC_CAPSLOCK);
				अवरोध;
			हाल KVAL(K_NUM):
				on_off = vt_get_leds(fg_console, VC_NUMLOCK);
				अवरोध;
			हाल KVAL(K_HOLD):
				on_off = vt_get_leds(fg_console, VC_SCROLLOCK);
				अवरोध;
			पूर्ण
			अगर (on_off == 1)
				beep(880);
			अन्यथा अगर (on_off == 0)
				beep(440);
		पूर्ण
	पूर्ण
	हाल KBD_UNBOUND_KEYCODE:
	हाल KBD_UNICODE:
	हाल KBD_KEYSYM:
		/* Unused */
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block keyboard_notअगरier_block = अणु
	.notअगरier_call = keyboard_notअगरier_call,
पूर्ण;

अटल पूर्णांक vt_notअगरier_call(काष्ठा notअगरier_block *blk,
			    अचिन्हित दीर्घ code, व्योम *_param)
अणु
	काष्ठा vt_notअगरier_param *param = _param;
	काष्ठा vc_data *vc = param->vc;
	चयन (code) अणु
	हाल VT_ALLOCATE:
		अवरोध;
	हाल VT_DEALLOCATE:
		अवरोध;
	हाल VT_WRITE:
	अणु
		अचिन्हित अक्षर c = param->c;
		अगर (vc->vc_num != fg_console)
			अवरोध;
		चयन (c) अणु
		हाल '\b':
		हाल 127:
			अगर (console_cursor > 0) अणु
				console_cursor--;
				console_buf[console_cursor] = ' ';
			पूर्ण
			अवरोध;
		हाल '\n':
		हाल '\v':
		हाल '\f':
		हाल '\r':
			console_newline = 1;
			अवरोध;
		हाल '\t':
			c = ' ';
			fallthrough;
		शेष:
			अगर (c < 32)
				/* Ignore other control sequences */
				अवरोध;
			अगर (console_newline) अणु
				स_रखो(console_buf, 0, माप(console_buf));
				console_cursor = 0;
				console_newline = 0;
			पूर्ण
			अगर (console_cursor == WIDTH)
				स_हटाओ(console_buf, &console_buf[1],
					(WIDTH-1) * माप(*console_buf));
			अन्यथा
				console_cursor++;
			console_buf[console_cursor-1] = c;
			अवरोध;
		पूर्ण
		अगर (console_show)
			braille_ग_लिखो(console_buf);
		अन्यथा अणु
			vc_maybe_cursor_moved(vc);
			vc_refresh(vc);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल VT_UPDATE:
		/* Maybe a VT चयन, flush */
		अगर (console_show) अणु
			अगर (vc->vc_num != lastVC) अणु
				lastVC = vc->vc_num;
				स_रखो(console_buf, 0, माप(console_buf));
				console_cursor = 0;
				braille_ग_लिखो(console_buf);
			पूर्ण
		पूर्ण अन्यथा अणु
			vc_maybe_cursor_moved(vc);
			vc_refresh(vc);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block vt_notअगरier_block = अणु
	.notअगरier_call = vt_notअगरier_call,
पूर्ण;

/*
 * Called from prपूर्णांकk.c when console=brl is given
 */

पूर्णांक braille_रेजिस्टर_console(काष्ठा console *console, पूर्णांक index,
		अक्षर *console_options, अक्षर *braille_options)
अणु
	पूर्णांक ret;

	अगर (!console_options)
		/* Only support VisioBraille क्रम now */
		console_options = "57600o8";
	अगर (braille_co)
		वापस -ENODEV;
	अगर (console->setup) अणु
		ret = console->setup(console, console_options);
		अगर (ret != 0)
			वापस ret;
	पूर्ण
	console->flags |= CON_ENABLED;
	console->index = index;
	braille_co = console;
	रेजिस्टर_keyboard_notअगरier(&keyboard_notअगरier_block);
	रेजिस्टर_vt_notअगरier(&vt_notअगरier_block);
	वापस 1;
पूर्ण

पूर्णांक braille_unरेजिस्टर_console(काष्ठा console *console)
अणु
	अगर (braille_co != console)
		वापस -EINVAL;
	unरेजिस्टर_keyboard_notअगरier(&keyboard_notअगरier_block);
	unरेजिस्टर_vt_notअगरier(&vt_notअगरier_block);
	braille_co = शून्य;
	वापस 1;
पूर्ण
