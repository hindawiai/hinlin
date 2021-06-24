<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AT and PS/2 keyboard driver
 *
 * Copyright (c) 1999-2002 Vojtech Pavlik
 */


/*
 * This driver can handle standard AT keyboards and PS/2 keyboards in
 * Translated and Raw Set 2 and Set 3, as well as AT keyboards on dumb
 * input-only controllers and AT keyboards connected over a one way RS232
 * converter.
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/libps2.h>
#समावेश <linux/mutex.h>
#समावेश <linux/dmi.h>
#समावेश <linux/property.h>

#घोषणा DRIVER_DESC	"AT and PS/2 keyboard driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@suse.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

अटल पूर्णांक atkbd_set = 2;
module_param_named(set, atkbd_set, पूर्णांक, 0);
MODULE_PARM_DESC(set, "Select keyboard code set (2 = default, 3 = PS/2 native)");

#अगर defined(__i386__) || defined(__x86_64__) || defined(__hppa__)
अटल bool atkbd_reset;
#अन्यथा
अटल bool atkbd_reset = true;
#पूर्ण_अगर
module_param_named(reset, atkbd_reset, bool, 0);
MODULE_PARM_DESC(reset, "Reset keyboard during initialization");

अटल bool atkbd_softrepeat;
module_param_named(softrepeat, atkbd_softrepeat, bool, 0);
MODULE_PARM_DESC(softrepeat, "Use software keyboard repeat");

अटल bool atkbd_softraw = true;
module_param_named(softraw, atkbd_softraw, bool, 0);
MODULE_PARM_DESC(softraw, "Use software generated rawmode");

अटल bool atkbd_scroll;
module_param_named(scroll, atkbd_scroll, bool, 0);
MODULE_PARM_DESC(scroll, "Enable scroll-wheel on MS Office and similar keyboards");

अटल bool atkbd_extra;
module_param_named(extra, atkbd_extra, bool, 0);
MODULE_PARM_DESC(extra, "Enable extra LEDs and keys on IBM RapidAcces, EzKey and similar keyboards");

अटल bool atkbd_terminal;
module_param_named(terminal, atkbd_terminal, bool, 0);
MODULE_PARM_DESC(terminal, "Enable break codes on an IBM Terminal keyboard connected via AT/PS2");

#घोषणा MAX_FUNCTION_ROW_KEYS	24

#घोषणा SCANCODE(keymap)	((keymap >> 16) & 0xFFFF)
#घोषणा KEYCODE(keymap)		(keymap & 0xFFFF)

/*
 * Scancode to keycode tables. These are just the शेष setting, and
 * are loadable via a userland utility.
 */

#घोषणा ATKBD_KEYMAP_SIZE	512

अटल स्थिर अचिन्हित लघु atkbd_set2_keycode[ATKBD_KEYMAP_SIZE] = अणु

#अगर_घोषित CONFIG_KEYBOARD_ATKBD_HP_KEYCODES

/* XXX: need a more general approach */

#समावेश "hpps2atkbd.h"	/* include the keyboard scancodes */

#अन्यथा
	  0, 67, 65, 63, 61, 59, 60, 88,  0, 68, 66, 64, 62, 15, 41,117,
	  0, 56, 42, 93, 29, 16,  2,  0,  0,  0, 44, 31, 30, 17,  3,  0,
	  0, 46, 45, 32, 18,  5,  4, 95,  0, 57, 47, 33, 20, 19,  6,183,
	  0, 49, 48, 35, 34, 21,  7,184,  0,  0, 50, 36, 22,  8,  9,185,
	  0, 51, 37, 23, 24, 11, 10,  0,  0, 52, 53, 38, 39, 25, 12,  0,
	  0, 89, 40,  0, 26, 13,  0,  0, 58, 54, 28, 27,  0, 43,  0, 85,
	  0, 86, 91, 90, 92,  0, 14, 94,  0, 79,124, 75, 71,121,  0,  0,
	 82, 83, 80, 76, 77, 72,  1, 69, 87, 78, 81, 74, 55, 73, 70, 99,

	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	217,100,255,  0, 97,165,  0,  0,156,  0,  0,  0,  0,  0,  0,125,
	173,114,  0,113,  0,  0,  0,126,128,  0,  0,140,  0,  0,  0,127,
	159,  0,115,  0,164,  0,  0,116,158,  0,172,166,  0,  0,  0,142,
	157,  0,  0,  0,  0,  0,  0,  0,155,  0, 98,  0,  0,163,  0,  0,
	226,  0,  0,  0,  0,  0,  0,  0,  0,255, 96,  0,  0,  0,143,  0,
	  0,  0,  0,  0,  0,  0,  0,  0,  0,107,  0,105,102,  0,  0,112,
	110,111,108,112,106,103,  0,119,  0,118,109,  0, 99,104,119,  0,

	  0,  0,  0, 65, 99,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर अचिन्हित लघु atkbd_set3_keycode[ATKBD_KEYMAP_SIZE] = अणु

	  0,  0,  0,  0,  0,  0,  0, 59,  1,138,128,129,130, 15, 41, 60,
	131, 29, 42, 86, 58, 16,  2, 61,133, 56, 44, 31, 30, 17,  3, 62,
	134, 46, 45, 32, 18,  5,  4, 63,135, 57, 47, 33, 20, 19,  6, 64,
	136, 49, 48, 35, 34, 21,  7, 65,137,100, 50, 36, 22,  8,  9, 66,
	125, 51, 37, 23, 24, 11, 10, 67,126, 52, 53, 38, 39, 25, 12, 68,
	113,114, 40, 43, 26, 13, 87, 99, 97, 54, 28, 27, 43, 43, 88, 70,
	108,105,119,103,111,107, 14,110,  0, 79,106, 75, 71,109,102,104,
	 82, 83, 80, 76, 77, 72, 69, 98,  0, 96, 81,  0, 78, 73, 55,183,

	184,185,186,187, 74, 94, 92, 93,  0,  0,  0,125,126,127,112,  0,
	  0,139,172,163,165,115,152,172,166,140,160,154,113,114,167,168,
	148,149,147,140
पूर्ण;

अटल स्थिर अचिन्हित लघु atkbd_unxlate_table[128] = अणु
          0,118, 22, 30, 38, 37, 46, 54, 61, 62, 70, 69, 78, 85,102, 13,
         21, 29, 36, 45, 44, 53, 60, 67, 68, 77, 84, 91, 90, 20, 28, 27,
         35, 43, 52, 51, 59, 66, 75, 76, 82, 14, 18, 93, 26, 34, 33, 42,
         50, 49, 58, 65, 73, 74, 89,124, 17, 41, 88,  5,  6,  4, 12,  3,
         11,  2, 10,  1,  9,119,126,108,117,125,123,107,115,116,121,105,
        114,122,112,113,127, 96, 97,120,  7, 15, 23, 31, 39, 47, 55, 63,
         71, 79, 86, 94,  8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 87,111,
         19, 25, 57, 81, 83, 92, 95, 98, 99,100,101,103,104,106,109,110
पूर्ण;

#घोषणा ATKBD_CMD_SETLEDS	0x10ed
#घोषणा ATKBD_CMD_GSCANSET	0x11f0
#घोषणा ATKBD_CMD_SSCANSET	0x10f0
#घोषणा ATKBD_CMD_GETID		0x02f2
#घोषणा ATKBD_CMD_SETREP	0x10f3
#घोषणा ATKBD_CMD_ENABLE	0x00f4
#घोषणा ATKBD_CMD_RESET_DIS	0x00f5	/* Reset to शेषs and disable */
#घोषणा ATKBD_CMD_RESET_DEF	0x00f6	/* Reset to शेषs */
#घोषणा ATKBD_CMD_SETALL_MB	0x00f8	/* Set all keys to give अवरोध codes */
#घोषणा ATKBD_CMD_SETALL_MBR	0x00fa  /* ... and repeat */
#घोषणा ATKBD_CMD_RESET_BAT	0x02ff
#घोषणा ATKBD_CMD_RESEND	0x00fe
#घोषणा ATKBD_CMD_EX_ENABLE	0x10ea
#घोषणा ATKBD_CMD_EX_SETLEDS	0x20eb
#घोषणा ATKBD_CMD_OK_GETID	0x02e8

#घोषणा ATKBD_RET_ACK		0xfa
#घोषणा ATKBD_RET_NAK		0xfe
#घोषणा ATKBD_RET_BAT		0xaa
#घोषणा ATKBD_RET_EMUL0		0xe0
#घोषणा ATKBD_RET_EMUL1		0xe1
#घोषणा ATKBD_RET_RELEASE	0xf0
#घोषणा ATKBD_RET_HANJA		0xf1
#घोषणा ATKBD_RET_HANGEUL	0xf2
#घोषणा ATKBD_RET_ERR		0xff

#घोषणा ATKBD_KEY_UNKNOWN	0
#घोषणा ATKBD_KEY_शून्य		255

#घोषणा ATKBD_SCR_1		0xfffe
#घोषणा ATKBD_SCR_2		0xfffd
#घोषणा ATKBD_SCR_4		0xfffc
#घोषणा ATKBD_SCR_8		0xfffb
#घोषणा ATKBD_SCR_CLICK		0xfffa
#घोषणा ATKBD_SCR_LEFT		0xfff9
#घोषणा ATKBD_SCR_RIGHT		0xfff8

#घोषणा ATKBD_SPECIAL		ATKBD_SCR_RIGHT

#घोषणा ATKBD_LED_EVENT_BIT	0
#घोषणा ATKBD_REP_EVENT_BIT	1

#घोषणा ATKBD_XL_ERR		0x01
#घोषणा ATKBD_XL_BAT		0x02
#घोषणा ATKBD_XL_ACK		0x04
#घोषणा ATKBD_XL_NAK		0x08
#घोषणा ATKBD_XL_HANGEUL	0x10
#घोषणा ATKBD_XL_HANJA		0x20

अटल स्थिर काष्ठा अणु
	अचिन्हित लघु keycode;
	अचिन्हित अक्षर set2;
पूर्ण atkbd_scroll_keys[] = अणु
	अणु ATKBD_SCR_1,     0xc5 पूर्ण,
	अणु ATKBD_SCR_2,     0x9d पूर्ण,
	अणु ATKBD_SCR_4,     0xa4 पूर्ण,
	अणु ATKBD_SCR_8,     0x9b पूर्ण,
	अणु ATKBD_SCR_CLICK, 0xe0 पूर्ण,
	अणु ATKBD_SCR_LEFT,  0xcb पूर्ण,
	अणु ATKBD_SCR_RIGHT, 0xd2 पूर्ण,
पूर्ण;

/*
 * The atkbd control काष्ठाure
 */

काष्ठा atkbd अणु

	काष्ठा ps2dev ps2dev;
	काष्ठा input_dev *dev;

	/* Written only during init */
	अक्षर name[64];
	अक्षर phys[32];

	अचिन्हित लघु id;
	अचिन्हित लघु keycode[ATKBD_KEYMAP_SIZE];
	DECLARE_BITMAP(क्रमce_release_mask, ATKBD_KEYMAP_SIZE);
	अचिन्हित अक्षर set;
	bool translated;
	bool extra;
	bool ग_लिखो;
	bool softrepeat;
	bool softraw;
	bool scroll;
	bool enabled;

	/* Accessed only from पूर्णांकerrupt */
	अचिन्हित अक्षर emul;
	bool resend;
	bool release;
	अचिन्हित दीर्घ xl_bit;
	अचिन्हित पूर्णांक last;
	अचिन्हित दीर्घ समय;
	अचिन्हित दीर्घ err_count;

	काष्ठा delayed_work event_work;
	अचिन्हित दीर्घ event_jअगरfies;
	अचिन्हित दीर्घ event_mask;

	/* Serializes reconnect(), attr->set() and event work */
	काष्ठा mutex mutex;

	u32 function_row_physmap[MAX_FUNCTION_ROW_KEYS];
	पूर्णांक num_function_row_keys;
पूर्ण;

/*
 * System-specअगरic keymap fixup routine
 */
अटल व्योम (*atkbd_platक्रमm_fixup)(काष्ठा atkbd *, स्थिर व्योम *data);
अटल व्योम *atkbd_platक्रमm_fixup_data;
अटल अचिन्हित पूर्णांक (*atkbd_platक्रमm_scancode_fixup)(काष्ठा atkbd *, अचिन्हित पूर्णांक);

/*
 * Certain keyboards to not like ATKBD_CMD_RESET_DIS and stop responding
 * to many commands until full reset (ATKBD_CMD_RESET_BAT) is perक्रमmed.
 */
अटल bool atkbd_skip_deactivate;

अटल sमाप_प्रकार atkbd_attr_show_helper(काष्ठा device *dev, अक्षर *buf,
				sमाप_प्रकार (*handler)(काष्ठा atkbd *, अक्षर *));
अटल sमाप_प्रकार atkbd_attr_set_helper(काष्ठा device *dev, स्थिर अक्षर *buf, माप_प्रकार count,
				sमाप_प्रकार (*handler)(काष्ठा atkbd *, स्थिर अक्षर *, माप_प्रकार));
#घोषणा ATKBD_DEFINE_ATTR(_name)						\
अटल sमाप_प्रकार atkbd_show_##_name(काष्ठा atkbd *, अक्षर *);			\
अटल sमाप_प्रकार atkbd_set_##_name(काष्ठा atkbd *, स्थिर अक्षर *, माप_प्रकार);		\
अटल sमाप_प्रकार atkbd_करो_show_##_name(काष्ठा device *d,				\
				काष्ठा device_attribute *attr, अक्षर *b)		\
अणु										\
	वापस atkbd_attr_show_helper(d, b, atkbd_show_##_name);		\
पूर्ण										\
अटल sमाप_प्रकार atkbd_करो_set_##_name(काष्ठा device *d,				\
			काष्ठा device_attribute *attr, स्थिर अक्षर *b, माप_प्रकार s)	\
अणु										\
	वापस atkbd_attr_set_helper(d, b, s, atkbd_set_##_name);		\
पूर्ण										\
अटल काष्ठा device_attribute atkbd_attr_##_name =				\
	__ATTR(_name, S_IWUSR | S_IRUGO, atkbd_करो_show_##_name, atkbd_करो_set_##_name);

ATKBD_DEFINE_ATTR(extra);
ATKBD_DEFINE_ATTR(क्रमce_release);
ATKBD_DEFINE_ATTR(scroll);
ATKBD_DEFINE_ATTR(set);
ATKBD_DEFINE_ATTR(softrepeat);
ATKBD_DEFINE_ATTR(softraw);

#घोषणा ATKBD_DEFINE_RO_ATTR(_name)						\
अटल sमाप_प्रकार atkbd_show_##_name(काष्ठा atkbd *, अक्षर *);			\
अटल sमाप_प्रकार atkbd_करो_show_##_name(काष्ठा device *d,				\
				काष्ठा device_attribute *attr, अक्षर *b)		\
अणु										\
	वापस atkbd_attr_show_helper(d, b, atkbd_show_##_name);		\
पूर्ण										\
अटल काष्ठा device_attribute atkbd_attr_##_name =				\
	__ATTR(_name, S_IRUGO, atkbd_करो_show_##_name, शून्य);

ATKBD_DEFINE_RO_ATTR(err_count);
ATKBD_DEFINE_RO_ATTR(function_row_physmap);

अटल काष्ठा attribute *atkbd_attributes[] = अणु
	&atkbd_attr_extra.attr,
	&atkbd_attr_क्रमce_release.attr,
	&atkbd_attr_scroll.attr,
	&atkbd_attr_set.attr,
	&atkbd_attr_softrepeat.attr,
	&atkbd_attr_softraw.attr,
	&atkbd_attr_err_count.attr,
	&atkbd_attr_function_row_physmap.attr,
	शून्य
पूर्ण;

अटल sमाप_प्रकार atkbd_show_function_row_physmap(काष्ठा atkbd *atkbd, अक्षर *buf)
अणु
	sमाप_प्रकार size = 0;
	पूर्णांक i;

	अगर (!atkbd->num_function_row_keys)
		वापस 0;

	क्रम (i = 0; i < atkbd->num_function_row_keys; i++)
		size += scnम_लिखो(buf + size, PAGE_SIZE - size, "%02X ",
				  atkbd->function_row_physmap[i]);
	size += scnम_लिखो(buf + size, PAGE_SIZE - size, "\n");
	वापस size;
पूर्ण

अटल umode_t atkbd_attr_is_visible(काष्ठा kobject *kobj,
				काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा serio *serio = to_serio_port(dev);
	काष्ठा atkbd *atkbd = serio_get_drvdata(serio);

	अगर (attr == &atkbd_attr_function_row_physmap.attr &&
	    !atkbd->num_function_row_keys)
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल काष्ठा attribute_group atkbd_attribute_group = अणु
	.attrs	= atkbd_attributes,
	.is_visible = atkbd_attr_is_visible,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक xl_table[] = अणु
	ATKBD_RET_BAT, ATKBD_RET_ERR, ATKBD_RET_ACK,
	ATKBD_RET_NAK, ATKBD_RET_HANJA, ATKBD_RET_HANGEUL,
पूर्ण;

/*
 * Checks अगर we should mangle the scancode to extract 'release' bit
 * in translated mode.
 */
अटल bool atkbd_need_xlate(अचिन्हित दीर्घ xl_bit, अचिन्हित अक्षर code)
अणु
	पूर्णांक i;

	अगर (code == ATKBD_RET_EMUL0 || code == ATKBD_RET_EMUL1)
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(xl_table); i++)
		अगर (code == xl_table[i])
			वापस test_bit(i, &xl_bit);

	वापस true;
पूर्ण

/*
 * Calculates new value of xl_bit so the driver can distinguish
 * between make/अवरोध pair of scancodes क्रम select keys and PS/2
 * protocol responses.
 */
अटल व्योम atkbd_calculate_xl_bit(काष्ठा atkbd *atkbd, अचिन्हित अक्षर code)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(xl_table); i++) अणु
		अगर (!((code ^ xl_table[i]) & 0x7f)) अणु
			अगर (code & 0x80)
				__clear_bit(i, &atkbd->xl_bit);
			अन्यथा
				__set_bit(i, &atkbd->xl_bit);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Encode the scancode, 0xe0 prefix, and high bit पूर्णांकo a single पूर्णांकeger,
 * keeping kernel 2.4 compatibility क्रम set 2
 */
अटल अचिन्हित पूर्णांक atkbd_compat_scancode(काष्ठा atkbd *atkbd, अचिन्हित पूर्णांक code)
अणु
	अगर (atkbd->set == 3) अणु
		अगर (atkbd->emul == 1)
			code |= 0x100;
        पूर्ण अन्यथा अणु
		code = (code & 0x7f) | ((code & 0x80) << 1);
		अगर (atkbd->emul == 1)
			code |= 0x80;
	पूर्ण

	वापस code;
पूर्ण

/*
 * atkbd_पूर्णांकerrupt(). Here takes place processing of data received from
 * the keyboard पूर्णांकo events.
 */

अटल irqवापस_t atkbd_पूर्णांकerrupt(काष्ठा serio *serio, अचिन्हित अक्षर data,
				   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा atkbd *atkbd = serio_get_drvdata(serio);
	काष्ठा input_dev *dev = atkbd->dev;
	अचिन्हित पूर्णांक code = data;
	पूर्णांक scroll = 0, hscroll = 0, click = -1;
	पूर्णांक value;
	अचिन्हित लघु keycode;

	dev_dbg(&serio->dev, "Received %02x flags %02x\n", data, flags);

#अगर !defined(__i386__) && !defined (__x86_64__)
	अगर ((flags & (SERIO_FRAME | SERIO_PARITY)) && (~flags & SERIO_TIMEOUT) && !atkbd->resend && atkbd->ग_लिखो) अणु
		dev_warn(&serio->dev, "Frame/parity error: %02x\n", flags);
		serio_ग_लिखो(serio, ATKBD_CMD_RESEND);
		atkbd->resend = true;
		जाओ out;
	पूर्ण

	अगर (!flags && data == ATKBD_RET_ACK)
		atkbd->resend = false;
#पूर्ण_अगर

	अगर (unlikely(atkbd->ps2dev.flags & PS2_FLAG_ACK))
		अगर  (ps2_handle_ack(&atkbd->ps2dev, data))
			जाओ out;

	अगर (unlikely(atkbd->ps2dev.flags & PS2_FLAG_CMD))
		अगर  (ps2_handle_response(&atkbd->ps2dev, data))
			जाओ out;

	pm_wakeup_event(&serio->dev, 0);

	अगर (!atkbd->enabled)
		जाओ out;

	input_event(dev, EV_MSC, MSC_RAW, code);

	अगर (atkbd_platक्रमm_scancode_fixup)
		code = atkbd_platक्रमm_scancode_fixup(atkbd, code);

	अगर (atkbd->translated) अणु

		अगर (atkbd->emul || atkbd_need_xlate(atkbd->xl_bit, code)) अणु
			atkbd->release = code >> 7;
			code &= 0x7f;
		पूर्ण

		अगर (!atkbd->emul)
			atkbd_calculate_xl_bit(atkbd, data);
	पूर्ण

	चयन (code) अणु
	हाल ATKBD_RET_BAT:
		atkbd->enabled = false;
		serio_reconnect(atkbd->ps2dev.serio);
		जाओ out;
	हाल ATKBD_RET_EMUL0:
		atkbd->emul = 1;
		जाओ out;
	हाल ATKBD_RET_EMUL1:
		atkbd->emul = 2;
		जाओ out;
	हाल ATKBD_RET_RELEASE:
		atkbd->release = true;
		जाओ out;
	हाल ATKBD_RET_ACK:
	हाल ATKBD_RET_NAK:
		अगर (prपूर्णांकk_ratelimit())
			dev_warn(&serio->dev,
				 "Spurious %s on %s. "
				 "Some program might be trying to access hardware directly.\n",
				 data == ATKBD_RET_ACK ? "ACK" : "NAK", serio->phys);
		जाओ out;
	हाल ATKBD_RET_ERR:
		atkbd->err_count++;
		dev_dbg(&serio->dev, "Keyboard on %s reports too many keys pressed.\n",
			serio->phys);
		जाओ out;
	पूर्ण

	code = atkbd_compat_scancode(atkbd, code);

	अगर (atkbd->emul && --atkbd->emul)
		जाओ out;

	keycode = atkbd->keycode[code];

	अगर (!(atkbd->release && test_bit(code, atkbd->क्रमce_release_mask)))
		अगर (keycode != ATKBD_KEY_शून्य)
			input_event(dev, EV_MSC, MSC_SCAN, code);

	चयन (keycode) अणु
	हाल ATKBD_KEY_शून्य:
		अवरोध;
	हाल ATKBD_KEY_UNKNOWN:
		dev_warn(&serio->dev,
			 "Unknown key %s (%s set %d, code %#x on %s).\n",
			 atkbd->release ? "released" : "pressed",
			 atkbd->translated ? "translated" : "raw",
			 atkbd->set, code, serio->phys);
		dev_warn(&serio->dev,
			 "Use 'setkeycodes %s%02x <keycode>' to make it known.\n",
			 code & 0x80 ? "e0" : "", code & 0x7f);
		input_sync(dev);
		अवरोध;
	हाल ATKBD_SCR_1:
		scroll = 1;
		अवरोध;
	हाल ATKBD_SCR_2:
		scroll = 2;
		अवरोध;
	हाल ATKBD_SCR_4:
		scroll = 4;
		अवरोध;
	हाल ATKBD_SCR_8:
		scroll = 8;
		अवरोध;
	हाल ATKBD_SCR_CLICK:
		click = !atkbd->release;
		अवरोध;
	हाल ATKBD_SCR_LEFT:
		hscroll = -1;
		अवरोध;
	हाल ATKBD_SCR_RIGHT:
		hscroll = 1;
		अवरोध;
	शेष:
		अगर (atkbd->release) अणु
			value = 0;
			atkbd->last = 0;
		पूर्ण अन्यथा अगर (!atkbd->softrepeat && test_bit(keycode, dev->key)) अणु
			/* Workaround Toshiba laptop multiple keypress */
			value = समय_beक्रमe(jअगरfies, atkbd->समय) && atkbd->last == code ? 1 : 2;
		पूर्ण अन्यथा अणु
			value = 1;
			atkbd->last = code;
			atkbd->समय = jअगरfies + msecs_to_jअगरfies(dev->rep[REP_DELAY]) / 2;
		पूर्ण

		input_event(dev, EV_KEY, keycode, value);
		input_sync(dev);

		अगर (value && test_bit(code, atkbd->क्रमce_release_mask)) अणु
			input_event(dev, EV_MSC, MSC_SCAN, code);
			input_report_key(dev, keycode, 0);
			input_sync(dev);
		पूर्ण
	पूर्ण

	अगर (atkbd->scroll) अणु
		अगर (click != -1)
			input_report_key(dev, BTN_MIDDLE, click);
		input_report_rel(dev, REL_WHEEL,
				 atkbd->release ? -scroll : scroll);
		input_report_rel(dev, REL_HWHEEL, hscroll);
		input_sync(dev);
	पूर्ण

	atkbd->release = false;
out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक atkbd_set_repeat_rate(काष्ठा atkbd *atkbd)
अणु
	स्थिर लघु period[32] =
		अणु 33,  37,  42,  46,  50,  54,  58,  63,  67,  75,  83,  92, 100, 109, 116, 125,
		 133, 149, 167, 182, 200, 217, 232, 250, 270, 303, 333, 370, 400, 435, 470, 500 पूर्ण;
	स्थिर लघु delay[4] =
		अणु 250, 500, 750, 1000 पूर्ण;

	काष्ठा input_dev *dev = atkbd->dev;
	अचिन्हित अक्षर param;
	पूर्णांक i = 0, j = 0;

	जबतक (i < ARRAY_SIZE(period) - 1 && period[i] < dev->rep[REP_PERIOD])
		i++;
	dev->rep[REP_PERIOD] = period[i];

	जबतक (j < ARRAY_SIZE(delay) - 1 && delay[j] < dev->rep[REP_DELAY])
		j++;
	dev->rep[REP_DELAY] = delay[j];

	param = i | (j << 5);
	वापस ps2_command(&atkbd->ps2dev, &param, ATKBD_CMD_SETREP);
पूर्ण

अटल पूर्णांक atkbd_set_leds(काष्ठा atkbd *atkbd)
अणु
	काष्ठा input_dev *dev = atkbd->dev;
	अचिन्हित अक्षर param[2];

	param[0] = (test_bit(LED_SCROLLL, dev->led) ? 1 : 0)
		 | (test_bit(LED_NUML,    dev->led) ? 2 : 0)
		 | (test_bit(LED_CAPSL,   dev->led) ? 4 : 0);
	अगर (ps2_command(&atkbd->ps2dev, param, ATKBD_CMD_SETLEDS))
		वापस -1;

	अगर (atkbd->extra) अणु
		param[0] = 0;
		param[1] = (test_bit(LED_COMPOSE, dev->led) ? 0x01 : 0)
			 | (test_bit(LED_SLEEP,   dev->led) ? 0x02 : 0)
			 | (test_bit(LED_SUSPEND, dev->led) ? 0x04 : 0)
			 | (test_bit(LED_MISC,    dev->led) ? 0x10 : 0)
			 | (test_bit(LED_MUTE,    dev->led) ? 0x20 : 0);
		अगर (ps2_command(&atkbd->ps2dev, param, ATKBD_CMD_EX_SETLEDS))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * atkbd_event_work() is used to complete processing of events that
 * can not be processed by input_event() which is often called from
 * पूर्णांकerrupt context.
 */

अटल व्योम atkbd_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atkbd *atkbd = container_of(work, काष्ठा atkbd, event_work.work);

	mutex_lock(&atkbd->mutex);

	अगर (!atkbd->enabled) अणु
		/*
		 * Serio ports are resumed asynchronously so जबतक driver core
		 * thinks that device is alपढ़ोy fully operational in reality
		 * it may not be पढ़ोy yet. In this हाल we need to keep
		 * rescheduling till reconnect completes.
		 */
		schedule_delayed_work(&atkbd->event_work,
					msecs_to_jअगरfies(100));
	पूर्ण अन्यथा अणु
		अगर (test_and_clear_bit(ATKBD_LED_EVENT_BIT, &atkbd->event_mask))
			atkbd_set_leds(atkbd);

		अगर (test_and_clear_bit(ATKBD_REP_EVENT_BIT, &atkbd->event_mask))
			atkbd_set_repeat_rate(atkbd);
	पूर्ण

	mutex_unlock(&atkbd->mutex);
पूर्ण

/*
 * Schedule चयन क्रम execution. We need to throttle requests,
 * otherwise keyboard may become unresponsive.
 */
अटल व्योम atkbd_schedule_event_work(काष्ठा atkbd *atkbd, पूर्णांक event_bit)
अणु
	अचिन्हित दीर्घ delay = msecs_to_jअगरfies(50);

	अगर (समय_after(jअगरfies, atkbd->event_jअगरfies + delay))
		delay = 0;

	atkbd->event_jअगरfies = jअगरfies;
	set_bit(event_bit, &atkbd->event_mask);
	mb();
	schedule_delayed_work(&atkbd->event_work, delay);
पूर्ण

/*
 * Event callback from the input module. Events that change the state of
 * the hardware are processed here. If action can not be perक्रमmed in
 * पूर्णांकerrupt context it is offloaded to atkbd_event_work.
 */

अटल पूर्णांक atkbd_event(काष्ठा input_dev *dev,
			अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा atkbd *atkbd = input_get_drvdata(dev);

	अगर (!atkbd->ग_लिखो)
		वापस -1;

	चयन (type) अणु

	हाल EV_LED:
		atkbd_schedule_event_work(atkbd, ATKBD_LED_EVENT_BIT);
		वापस 0;

	हाल EV_REP:
		अगर (!atkbd->softrepeat)
			atkbd_schedule_event_work(atkbd, ATKBD_REP_EVENT_BIT);
		वापस 0;

	शेष:
		वापस -1;
	पूर्ण
पूर्ण

/*
 * atkbd_enable() संकेतs that पूर्णांकerrupt handler is allowed to
 * generate input events.
 */

अटल अंतरभूत व्योम atkbd_enable(काष्ठा atkbd *atkbd)
अणु
	serio_छोड़ो_rx(atkbd->ps2dev.serio);
	atkbd->enabled = true;
	serio_जारी_rx(atkbd->ps2dev.serio);
पूर्ण

/*
 * atkbd_disable() tells input handler that all incoming data except
 * क्रम ACKs and command response should be dropped.
 */

अटल अंतरभूत व्योम atkbd_disable(काष्ठा atkbd *atkbd)
अणु
	serio_छोड़ो_rx(atkbd->ps2dev.serio);
	atkbd->enabled = false;
	serio_जारी_rx(atkbd->ps2dev.serio);
पूर्ण

अटल पूर्णांक atkbd_activate(काष्ठा atkbd *atkbd)
अणु
	काष्ठा ps2dev *ps2dev = &atkbd->ps2dev;

/*
 * Enable the keyboard to receive keystrokes.
 */

	अगर (ps2_command(ps2dev, शून्य, ATKBD_CMD_ENABLE)) अणु
		dev_err(&ps2dev->serio->dev,
			"Failed to enable keyboard on %s\n",
			ps2dev->serio->phys);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * atkbd_deactivate() resets and disables the keyboard from sending
 * keystrokes.
 */

अटल व्योम atkbd_deactivate(काष्ठा atkbd *atkbd)
अणु
	काष्ठा ps2dev *ps2dev = &atkbd->ps2dev;

	अगर (ps2_command(ps2dev, शून्य, ATKBD_CMD_RESET_DIS))
		dev_err(&ps2dev->serio->dev,
			"Failed to deactivate keyboard on %s\n",
			ps2dev->serio->phys);
पूर्ण

/*
 * atkbd_probe() probes क्रम an AT keyboard on a serio port.
 */

अटल पूर्णांक atkbd_probe(काष्ठा atkbd *atkbd)
अणु
	काष्ठा ps2dev *ps2dev = &atkbd->ps2dev;
	अचिन्हित अक्षर param[2];

/*
 * Some प्रणालीs, where the bit-twiddling when testing the io-lines of the
 * controller may confuse the keyboard need a full reset of the keyboard. On
 * these प्रणालीs the BIOS also usually करोesn't करो it क्रम us.
 */

	अगर (atkbd_reset)
		अगर (ps2_command(ps2dev, शून्य, ATKBD_CMD_RESET_BAT))
			dev_warn(&ps2dev->serio->dev,
				 "keyboard reset failed on %s\n",
				 ps2dev->serio->phys);

/*
 * Then we check the keyboard ID. We should get 0xab83 under normal conditions.
 * Some keyboards report dअगरferent values, but the first byte is always 0xab or
 * 0xac. Some old AT keyboards करोn't report anything. If a mouse is connected, this
 * should make sure we करोn't try to set the LEDs on it.
 */

	param[0] = param[1] = 0xa5;	/* initialize with invalid values */
	अगर (ps2_command(ps2dev, param, ATKBD_CMD_GETID)) अणु

/*
 * If the get ID command failed, we check अगर we can at least set the LEDs on
 * the keyboard. This should work on every keyboard out there. It also turns
 * the LEDs off, which we want anyway.
 */
		param[0] = 0;
		अगर (ps2_command(ps2dev, param, ATKBD_CMD_SETLEDS))
			वापस -1;
		atkbd->id = 0xabba;
		वापस 0;
	पूर्ण

	अगर (!ps2_is_keyboard_id(param[0]))
		वापस -1;

	atkbd->id = (param[0] << 8) | param[1];

	अगर (atkbd->id == 0xaca1 && atkbd->translated) अणु
		dev_err(&ps2dev->serio->dev,
			"NCD terminal keyboards are only supported on non-translating controllers. "
			"Use i8042.direct=1 to disable translation.\n");
		वापस -1;
	पूर्ण

/*
 * Make sure nothing is coming from the keyboard and disturbs our
 * पूर्णांकernal state.
 */
	अगर (!atkbd_skip_deactivate)
		atkbd_deactivate(atkbd);

	वापस 0;
पूर्ण

/*
 * atkbd_select_set checks अगर a keyboard has a working Set 3 support, and
 * sets it पूर्णांकo that. Unक्रमtunately there are keyboards that can be चयनed
 * to Set 3, but करोn't work well in that (BTC Mulसमयdia ...)
 */

अटल पूर्णांक atkbd_select_set(काष्ठा atkbd *atkbd, पूर्णांक target_set, पूर्णांक allow_extra)
अणु
	काष्ठा ps2dev *ps2dev = &atkbd->ps2dev;
	अचिन्हित अक्षर param[2];

	atkbd->extra = false;
/*
 * For known special keyboards we can go ahead and set the correct set.
 * We check क्रम NCD PS/2 Sun, NorthGate OmniKey 101 and
 * IBM RapidAccess / IBM EzButton / Chicony KBP-8993 keyboards.
 */

	अगर (atkbd->translated)
		वापस 2;

	अगर (atkbd->id == 0xaca1) अणु
		param[0] = 3;
		ps2_command(ps2dev, param, ATKBD_CMD_SSCANSET);
		वापस 3;
	पूर्ण

	अगर (allow_extra) अणु
		param[0] = 0x71;
		अगर (!ps2_command(ps2dev, param, ATKBD_CMD_EX_ENABLE)) अणु
			atkbd->extra = true;
			वापस 2;
		पूर्ण
	पूर्ण

	अगर (atkbd_terminal) अणु
		ps2_command(ps2dev, param, ATKBD_CMD_SETALL_MB);
		वापस 3;
	पूर्ण

	अगर (target_set != 3)
		वापस 2;

	अगर (!ps2_command(ps2dev, param, ATKBD_CMD_OK_GETID)) अणु
		atkbd->id = param[0] << 8 | param[1];
		वापस 2;
	पूर्ण

	param[0] = 3;
	अगर (ps2_command(ps2dev, param, ATKBD_CMD_SSCANSET))
		वापस 2;

	param[0] = 0;
	अगर (ps2_command(ps2dev, param, ATKBD_CMD_GSCANSET))
		वापस 2;

	अगर (param[0] != 3) अणु
		param[0] = 2;
		अगर (ps2_command(ps2dev, param, ATKBD_CMD_SSCANSET))
			वापस 2;
	पूर्ण

	ps2_command(ps2dev, param, ATKBD_CMD_SETALL_MBR);

	वापस 3;
पूर्ण

अटल पूर्णांक atkbd_reset_state(काष्ठा atkbd *atkbd)
अणु
        काष्ठा ps2dev *ps2dev = &atkbd->ps2dev;
	अचिन्हित अक्षर param[1];

/*
 * Set the LEDs to a predefined state (all off).
 */

	param[0] = 0;
	अगर (ps2_command(ps2dev, param, ATKBD_CMD_SETLEDS))
		वापस -1;

/*
 * Set स्वतःrepeat to fastest possible.
 */

	param[0] = 0;
	अगर (ps2_command(ps2dev, param, ATKBD_CMD_SETREP))
		वापस -1;

	वापस 0;
पूर्ण

/*
 * atkbd_cleanup() restores the keyboard state so that BIOS is happy after a
 * reboot.
 */

अटल व्योम atkbd_cleanup(काष्ठा serio *serio)
अणु
	काष्ठा atkbd *atkbd = serio_get_drvdata(serio);

	atkbd_disable(atkbd);
	ps2_command(&atkbd->ps2dev, शून्य, ATKBD_CMD_RESET_DEF);
पूर्ण


/*
 * atkbd_disconnect() बंदs and मुक्तs.
 */

अटल व्योम atkbd_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा atkbd *atkbd = serio_get_drvdata(serio);

	sysfs_हटाओ_group(&serio->dev.kobj, &atkbd_attribute_group);

	atkbd_disable(atkbd);

	input_unरेजिस्टर_device(atkbd->dev);

	/*
	 * Make sure we करोn't have a command in flight.
	 * Note that since atkbd->enabled is false event work will keep
	 * rescheduling itself until it माला_लो canceled and will not try
	 * accessing मुक्तd input device or serio port.
	 */
	cancel_delayed_work_sync(&atkbd->event_work);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	kमुक्त(atkbd);
पूर्ण

/*
 * generate release events क्रम the keycodes given in data
 */
अटल व्योम atkbd_apply_क्रमced_release_keylist(काष्ठा atkbd* atkbd,
						स्थिर व्योम *data)
अणु
	स्थिर अचिन्हित पूर्णांक *keys = data;
	अचिन्हित पूर्णांक i;

	अगर (atkbd->set == 2)
		क्रम (i = 0; keys[i] != -1U; i++)
			__set_bit(keys[i], atkbd->क्रमce_release_mask);
पूर्ण

/*
 * Most special keys (Fn+F?) on Dell laptops करो not generate release
 * events so we have to करो it ourselves.
 */
अटल अचिन्हित पूर्णांक atkbd_dell_laptop_क्रमced_release_keys[] = अणु
	0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8f, 0x93, -1U
पूर्ण;

/*
 * Perक्रमm fixup क्रम HP प्रणाली that करोesn't generate release
 * क्रम its video चयन
 */
अटल अचिन्हित पूर्णांक atkbd_hp_क्रमced_release_keys[] = अणु
	0x94, -1U
पूर्ण;

/*
 * Samsung NC10,NC20 with Fn+F? key release not working
 */
अटल अचिन्हित पूर्णांक atkbd_samsung_क्रमced_release_keys[] = अणु
	0x82, 0x83, 0x84, 0x86, 0x88, 0x89, 0xb3, 0xf7, 0xf9, -1U
पूर्ण;

/*
 * Amilo Pi 3525 key release क्रम Fn+Volume keys not working
 */
अटल अचिन्हित पूर्णांक atkbd_amilo_pi3525_क्रमced_release_keys[] = अणु
	0x20, 0xa0, 0x2e, 0xae, 0x30, 0xb0, -1U
पूर्ण;

/*
 * Amilo Xi 3650 key release क्रम light touch bar not working
 */
अटल अचिन्हित पूर्णांक atkbd_amilo_xi3650_क्रमced_release_keys[] = अणु
	0x67, 0xed, 0x90, 0xa2, 0x99, 0xa4, 0xae, 0xb0, -1U
पूर्ण;

/*
 * Soltech TA12 प्रणाली with broken key release on volume keys and mute key
 */
अटल अचिन्हित पूर्णांक atkdb_soltech_ta12_क्रमced_release_keys[] = अणु
	0xa0, 0xae, 0xb0, -1U
पूर्ण;

/*
 * Many notebooks करोn't send key release event क्रम volume up/करोwn
 * keys, with key list below common among them
 */
अटल अचिन्हित पूर्णांक atkbd_volume_क्रमced_release_keys[] = अणु
	0xae, 0xb0, -1U
पूर्ण;

/*
 * OQO 01+ mulसमयdia keys (64--66) generate e0 6x upon release whereas
 * they should be generating e4-e6 (0x80 | code).
 */
अटल अचिन्हित पूर्णांक atkbd_oqo_01plus_scancode_fixup(काष्ठा atkbd *atkbd,
						    अचिन्हित पूर्णांक code)
अणु
	अगर (atkbd->translated && atkbd->emul == 1 &&
	    (code == 0x64 || code == 0x65 || code == 0x66)) अणु
		atkbd->emul = 0;
		code |= 0x80;
	पूर्ण

	वापस code;
पूर्ण

अटल पूर्णांक atkbd_get_keymap_from_fwnode(काष्ठा atkbd *atkbd)
अणु
	काष्ठा device *dev = &atkbd->ps2dev.serio->dev;
	पूर्णांक i, n;
	u32 *ptr;
	u16 scancode, keycode;

	/* Parse "linux,keymap" property */
	n = device_property_count_u32(dev, "linux,keymap");
	अगर (n <= 0 || n > ATKBD_KEYMAP_SIZE)
		वापस -ENXIO;

	ptr = kसुस्मृति(n, माप(u32), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	अगर (device_property_पढ़ो_u32_array(dev, "linux,keymap", ptr, n)) अणु
		dev_err(dev, "problem parsing FW keymap property\n");
		kमुक्त(ptr);
		वापस -EINVAL;
	पूर्ण

	स_रखो(atkbd->keycode, 0, माप(atkbd->keycode));
	क्रम (i = 0; i < n; i++) अणु
		scancode = SCANCODE(ptr[i]);
		keycode = KEYCODE(ptr[i]);
		atkbd->keycode[scancode] = keycode;
	पूर्ण

	kमुक्त(ptr);
	वापस 0;
पूर्ण

/*
 * atkbd_set_keycode_table() initializes keyboard's keycode table
 * according to the selected scancode set
 */

अटल व्योम atkbd_set_keycode_table(काष्ठा atkbd *atkbd)
अणु
	काष्ठा device *dev = &atkbd->ps2dev.serio->dev;
	अचिन्हित पूर्णांक scancode;
	पूर्णांक i, j;

	स_रखो(atkbd->keycode, 0, माप(atkbd->keycode));
	biपंचांगap_zero(atkbd->क्रमce_release_mask, ATKBD_KEYMAP_SIZE);

	अगर (!atkbd_get_keymap_from_fwnode(atkbd)) अणु
		dev_dbg(dev, "Using FW keymap\n");
	पूर्ण अन्यथा अगर (atkbd->translated) अणु
		क्रम (i = 0; i < 128; i++) अणु
			scancode = atkbd_unxlate_table[i];
			atkbd->keycode[i] = atkbd_set2_keycode[scancode];
			atkbd->keycode[i | 0x80] = atkbd_set2_keycode[scancode | 0x80];
			अगर (atkbd->scroll)
				क्रम (j = 0; j < ARRAY_SIZE(atkbd_scroll_keys); j++)
					अगर ((scancode | 0x80) == atkbd_scroll_keys[j].set2)
						atkbd->keycode[i | 0x80] = atkbd_scroll_keys[j].keycode;
		पूर्ण
	पूर्ण अन्यथा अगर (atkbd->set == 3) अणु
		स_नकल(atkbd->keycode, atkbd_set3_keycode, माप(atkbd->keycode));
	पूर्ण अन्यथा अणु
		स_नकल(atkbd->keycode, atkbd_set2_keycode, माप(atkbd->keycode));

		अगर (atkbd->scroll)
			क्रम (i = 0; i < ARRAY_SIZE(atkbd_scroll_keys); i++) अणु
				scancode = atkbd_scroll_keys[i].set2;
				atkbd->keycode[scancode] = atkbd_scroll_keys[i].keycode;
		पूर्ण
	पूर्ण

/*
 * HANGEUL and HANJA keys करो not send release events so we need to
 * generate such events ourselves
 */
	scancode = atkbd_compat_scancode(atkbd, ATKBD_RET_HANGEUL);
	atkbd->keycode[scancode] = KEY_HANGEUL;
	__set_bit(scancode, atkbd->क्रमce_release_mask);

	scancode = atkbd_compat_scancode(atkbd, ATKBD_RET_HANJA);
	atkbd->keycode[scancode] = KEY_HANJA;
	__set_bit(scancode, atkbd->क्रमce_release_mask);

/*
 * Perक्रमm additional fixups
 */
	अगर (atkbd_platक्रमm_fixup)
		atkbd_platक्रमm_fixup(atkbd, atkbd_platक्रमm_fixup_data);
पूर्ण

/*
 * atkbd_set_device_attrs() sets up keyboard's input device काष्ठाure
 */

अटल व्योम atkbd_set_device_attrs(काष्ठा atkbd *atkbd)
अणु
	काष्ठा input_dev *input_dev = atkbd->dev;
	पूर्णांक i;

	अगर (atkbd->extra)
		snम_लिखो(atkbd->name, माप(atkbd->name),
			 "AT Set 2 Extra keyboard");
	अन्यथा
		snम_लिखो(atkbd->name, माप(atkbd->name),
			 "AT %s Set %d keyboard",
			 atkbd->translated ? "Translated" : "Raw", atkbd->set);

	snम_लिखो(atkbd->phys, माप(atkbd->phys),
		 "%s/input0", atkbd->ps2dev.serio->phys);

	input_dev->name = atkbd->name;
	input_dev->phys = atkbd->phys;
	input_dev->id.bustype = BUS_I8042;
	input_dev->id.venकरोr = 0x0001;
	input_dev->id.product = atkbd->translated ? 1 : atkbd->set;
	input_dev->id.version = atkbd->id;
	input_dev->event = atkbd_event;
	input_dev->dev.parent = &atkbd->ps2dev.serio->dev;

	input_set_drvdata(input_dev, atkbd);

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP) |
		BIT_MASK(EV_MSC);

	अगर (atkbd->ग_लिखो) अणु
		input_dev->evbit[0] |= BIT_MASK(EV_LED);
		input_dev->ledbit[0] = BIT_MASK(LED_NUML) |
			BIT_MASK(LED_CAPSL) | BIT_MASK(LED_SCROLLL);
	पूर्ण

	अगर (atkbd->extra)
		input_dev->ledbit[0] |= BIT_MASK(LED_COMPOSE) |
			BIT_MASK(LED_SUSPEND) | BIT_MASK(LED_SLEEP) |
			BIT_MASK(LED_MUTE) | BIT_MASK(LED_MISC);

	अगर (!atkbd->softrepeat) अणु
		input_dev->rep[REP_DELAY] = 250;
		input_dev->rep[REP_PERIOD] = 33;
	पूर्ण

	input_dev->mscbit[0] = atkbd->softraw ? BIT_MASK(MSC_SCAN) :
		BIT_MASK(MSC_RAW) | BIT_MASK(MSC_SCAN);

	अगर (atkbd->scroll) अणु
		input_dev->evbit[0] |= BIT_MASK(EV_REL);
		input_dev->relbit[0] = BIT_MASK(REL_WHEEL) |
			BIT_MASK(REL_HWHEEL);
		__set_bit(BTN_MIDDLE, input_dev->keybit);
	पूर्ण

	input_dev->keycode = atkbd->keycode;
	input_dev->keycodesize = माप(अचिन्हित लघु);
	input_dev->keycodemax = ARRAY_SIZE(atkbd_set2_keycode);

	क्रम (i = 0; i < ATKBD_KEYMAP_SIZE; i++) अणु
		अगर (atkbd->keycode[i] != KEY_RESERVED &&
		    atkbd->keycode[i] != ATKBD_KEY_शून्य &&
		    atkbd->keycode[i] < ATKBD_SPECIAL) अणु
			__set_bit(atkbd->keycode[i], input_dev->keybit);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम atkbd_parse_fwnode_data(काष्ठा serio *serio)
अणु
	काष्ठा atkbd *atkbd = serio_get_drvdata(serio);
	काष्ठा device *dev = &serio->dev;
	पूर्णांक n;

	/* Parse "function-row-physmap" property */
	n = device_property_count_u32(dev, "function-row-physmap");
	अगर (n > 0 && n <= MAX_FUNCTION_ROW_KEYS &&
	    !device_property_पढ़ो_u32_array(dev, "function-row-physmap",
					    atkbd->function_row_physmap, n)) अणु
		atkbd->num_function_row_keys = n;
		dev_dbg(dev, "FW reported %d function-row key locations\n", n);
	पूर्ण
पूर्ण

/*
 * atkbd_connect() is called when the serio module finds an पूर्णांकerface
 * that isn't handled yet by an appropriate device driver. We check अगर
 * there is an AT keyboard out there and अगर yes, we रेजिस्टर ourselves
 * to the input module.
 */

अटल पूर्णांक atkbd_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा atkbd *atkbd;
	काष्ठा input_dev *dev;
	पूर्णांक err = -ENOMEM;

	atkbd = kzalloc(माप(काष्ठा atkbd), GFP_KERNEL);
	dev = input_allocate_device();
	अगर (!atkbd || !dev)
		जाओ fail1;

	atkbd->dev = dev;
	ps2_init(&atkbd->ps2dev, serio);
	INIT_DELAYED_WORK(&atkbd->event_work, atkbd_event_work);
	mutex_init(&atkbd->mutex);

	चयन (serio->id.type) अणु

	हाल SERIO_8042_XL:
		atkbd->translated = true;
		fallthrough;

	हाल SERIO_8042:
		अगर (serio->ग_लिखो)
			atkbd->ग_लिखो = true;
		अवरोध;
	पूर्ण

	atkbd->softraw = atkbd_softraw;
	atkbd->softrepeat = atkbd_softrepeat;
	atkbd->scroll = atkbd_scroll;

	अगर (atkbd->softrepeat)
		atkbd->softraw = true;

	serio_set_drvdata(serio, atkbd);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	अगर (atkbd->ग_लिखो) अणु

		अगर (atkbd_probe(atkbd)) अणु
			err = -ENODEV;
			जाओ fail3;
		पूर्ण

		atkbd->set = atkbd_select_set(atkbd, atkbd_set, atkbd_extra);
		atkbd_reset_state(atkbd);

	पूर्ण अन्यथा अणु
		atkbd->set = 2;
		atkbd->id = 0xab00;
	पूर्ण

	atkbd_parse_fwnode_data(serio);

	atkbd_set_keycode_table(atkbd);
	atkbd_set_device_attrs(atkbd);

	err = sysfs_create_group(&serio->dev.kobj, &atkbd_attribute_group);
	अगर (err)
		जाओ fail3;

	atkbd_enable(atkbd);
	अगर (serio->ग_लिखो)
		atkbd_activate(atkbd);

	err = input_रेजिस्टर_device(atkbd->dev);
	अगर (err)
		जाओ fail4;

	वापस 0;

 fail4: sysfs_हटाओ_group(&serio->dev.kobj, &atkbd_attribute_group);
 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(dev);
	kमुक्त(atkbd);
	वापस err;
पूर्ण

/*
 * atkbd_reconnect() tries to restore keyboard पूर्णांकo a sane state and is
 * most likely called on resume.
 */

अटल पूर्णांक atkbd_reconnect(काष्ठा serio *serio)
अणु
	काष्ठा atkbd *atkbd = serio_get_drvdata(serio);
	काष्ठा serio_driver *drv = serio->drv;
	पूर्णांक retval = -1;

	अगर (!atkbd || !drv) अणु
		dev_dbg(&serio->dev,
			"reconnect request, but serio is disconnected, ignoring...\n");
		वापस -1;
	पूर्ण

	mutex_lock(&atkbd->mutex);

	atkbd_disable(atkbd);

	अगर (atkbd->ग_लिखो) अणु
		अगर (atkbd_probe(atkbd))
			जाओ out;

		अगर (atkbd->set != atkbd_select_set(atkbd, atkbd->set, atkbd->extra))
			जाओ out;

		/*
		 * Restore LED state and repeat rate. While input core
		 * will करो this क्रम us at resume समय reconnect may happen
		 * because user requested it via sysfs or simply because
		 * keyboard was unplugged and plugged in again so we need
		 * to करो it ourselves here.
		 */
		atkbd_set_leds(atkbd);
		अगर (!atkbd->softrepeat)
			atkbd_set_repeat_rate(atkbd);

	पूर्ण

	/*
	 * Reset our state machine in हाल reconnect happened in the middle
	 * of multi-byte scancode.
	 */
	atkbd->xl_bit = 0;
	atkbd->emul = 0;

	atkbd_enable(atkbd);
	अगर (atkbd->ग_लिखो)
		atkbd_activate(atkbd);

	retval = 0;

 out:
	mutex_unlock(&atkbd->mutex);
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा serio_device_id atkbd_serio_ids[] = अणु
	अणु
		.type	= SERIO_8042,
		.proto	= SERIO_ANY,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु
		.type	= SERIO_8042_XL,
		.proto	= SERIO_ANY,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_PS2SER,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, atkbd_serio_ids);

अटल काष्ठा serio_driver atkbd_drv = अणु
	.driver		= अणु
		.name	= "atkbd",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= atkbd_serio_ids,
	.पूर्णांकerrupt	= atkbd_पूर्णांकerrupt,
	.connect	= atkbd_connect,
	.reconnect	= atkbd_reconnect,
	.disconnect	= atkbd_disconnect,
	.cleanup	= atkbd_cleanup,
पूर्ण;

अटल sमाप_प्रकार atkbd_attr_show_helper(काष्ठा device *dev, अक्षर *buf,
				sमाप_प्रकार (*handler)(काष्ठा atkbd *, अक्षर *))
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	काष्ठा atkbd *atkbd = serio_get_drvdata(serio);

	वापस handler(atkbd, buf);
पूर्ण

अटल sमाप_प्रकार atkbd_attr_set_helper(काष्ठा device *dev, स्थिर अक्षर *buf, माप_प्रकार count,
				sमाप_प्रकार (*handler)(काष्ठा atkbd *, स्थिर अक्षर *, माप_प्रकार))
अणु
	काष्ठा serio *serio = to_serio_port(dev);
	काष्ठा atkbd *atkbd = serio_get_drvdata(serio);
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&atkbd->mutex);
	अगर (retval)
		वापस retval;

	atkbd_disable(atkbd);
	retval = handler(atkbd, buf, count);
	atkbd_enable(atkbd);

	mutex_unlock(&atkbd->mutex);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार atkbd_show_extra(काष्ठा atkbd *atkbd, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", atkbd->extra ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार atkbd_set_extra(काष्ठा atkbd *atkbd, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा input_dev *old_dev, *new_dev;
	अचिन्हित पूर्णांक value;
	पूर्णांक err;
	bool old_extra;
	अचिन्हित अक्षर old_set;

	अगर (!atkbd->ग_लिखो)
		वापस -EIO;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	अगर (value > 1)
		वापस -EINVAL;

	अगर (atkbd->extra != value) अणु
		/*
		 * Since device's properties will change we need to
		 * unरेजिस्टर old device. But allocate and रेजिस्टर
		 * new one first to make sure we have it.
		 */
		old_dev = atkbd->dev;
		old_extra = atkbd->extra;
		old_set = atkbd->set;

		new_dev = input_allocate_device();
		अगर (!new_dev)
			वापस -ENOMEM;

		atkbd->dev = new_dev;
		atkbd->set = atkbd_select_set(atkbd, atkbd->set, value);
		atkbd_reset_state(atkbd);
		atkbd_activate(atkbd);
		atkbd_set_keycode_table(atkbd);
		atkbd_set_device_attrs(atkbd);

		err = input_रेजिस्टर_device(atkbd->dev);
		अगर (err) अणु
			input_मुक्त_device(new_dev);

			atkbd->dev = old_dev;
			atkbd->set = atkbd_select_set(atkbd, old_set, old_extra);
			atkbd_set_keycode_table(atkbd);
			atkbd_set_device_attrs(atkbd);

			वापस err;
		पूर्ण
		input_unरेजिस्टर_device(old_dev);

	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार atkbd_show_क्रमce_release(काष्ठा atkbd *atkbd, अक्षर *buf)
अणु
	माप_प्रकार len = scnम_लिखो(buf, PAGE_SIZE - 1, "%*pbl",
			       ATKBD_KEYMAP_SIZE, atkbd->क्रमce_release_mask);

	buf[len++] = '\n';
	buf[len] = '\0';

	वापस len;
पूर्ण

अटल sमाप_प्रकार atkbd_set_क्रमce_release(काष्ठा atkbd *atkbd,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	/* 64 bytes on stack should be acceptable */
	DECLARE_BITMAP(new_mask, ATKBD_KEYMAP_SIZE);
	पूर्णांक err;

	err = biपंचांगap_parselist(buf, new_mask, ATKBD_KEYMAP_SIZE);
	अगर (err)
		वापस err;

	स_नकल(atkbd->क्रमce_release_mask, new_mask, माप(atkbd->क्रमce_release_mask));
	वापस count;
पूर्ण


अटल sमाप_प्रकार atkbd_show_scroll(काष्ठा atkbd *atkbd, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", atkbd->scroll ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार atkbd_set_scroll(काष्ठा atkbd *atkbd, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा input_dev *old_dev, *new_dev;
	अचिन्हित पूर्णांक value;
	पूर्णांक err;
	bool old_scroll;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	अगर (value > 1)
		वापस -EINVAL;

	अगर (atkbd->scroll != value) अणु
		old_dev = atkbd->dev;
		old_scroll = atkbd->scroll;

		new_dev = input_allocate_device();
		अगर (!new_dev)
			वापस -ENOMEM;

		atkbd->dev = new_dev;
		atkbd->scroll = value;
		atkbd_set_keycode_table(atkbd);
		atkbd_set_device_attrs(atkbd);

		err = input_रेजिस्टर_device(atkbd->dev);
		अगर (err) अणु
			input_मुक्त_device(new_dev);

			atkbd->scroll = old_scroll;
			atkbd->dev = old_dev;
			atkbd_set_keycode_table(atkbd);
			atkbd_set_device_attrs(atkbd);

			वापस err;
		पूर्ण
		input_unरेजिस्टर_device(old_dev);
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार atkbd_show_set(काष्ठा atkbd *atkbd, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", atkbd->set);
पूर्ण

अटल sमाप_प्रकार atkbd_set_set(काष्ठा atkbd *atkbd, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा input_dev *old_dev, *new_dev;
	अचिन्हित पूर्णांक value;
	पूर्णांक err;
	अचिन्हित अक्षर old_set;
	bool old_extra;

	अगर (!atkbd->ग_लिखो)
		वापस -EIO;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	अगर (value != 2 && value != 3)
		वापस -EINVAL;

	अगर (atkbd->set != value) अणु
		old_dev = atkbd->dev;
		old_extra = atkbd->extra;
		old_set = atkbd->set;

		new_dev = input_allocate_device();
		अगर (!new_dev)
			वापस -ENOMEM;

		atkbd->dev = new_dev;
		atkbd->set = atkbd_select_set(atkbd, value, atkbd->extra);
		atkbd_reset_state(atkbd);
		atkbd_activate(atkbd);
		atkbd_set_keycode_table(atkbd);
		atkbd_set_device_attrs(atkbd);

		err = input_रेजिस्टर_device(atkbd->dev);
		अगर (err) अणु
			input_मुक्त_device(new_dev);

			atkbd->dev = old_dev;
			atkbd->set = atkbd_select_set(atkbd, old_set, old_extra);
			atkbd_set_keycode_table(atkbd);
			atkbd_set_device_attrs(atkbd);

			वापस err;
		पूर्ण
		input_unरेजिस्टर_device(old_dev);
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार atkbd_show_softrepeat(काष्ठा atkbd *atkbd, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", atkbd->softrepeat ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार atkbd_set_softrepeat(काष्ठा atkbd *atkbd, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा input_dev *old_dev, *new_dev;
	अचिन्हित पूर्णांक value;
	पूर्णांक err;
	bool old_softrepeat, old_softraw;

	अगर (!atkbd->ग_लिखो)
		वापस -EIO;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	अगर (value > 1)
		वापस -EINVAL;

	अगर (atkbd->softrepeat != value) अणु
		old_dev = atkbd->dev;
		old_softrepeat = atkbd->softrepeat;
		old_softraw = atkbd->softraw;

		new_dev = input_allocate_device();
		अगर (!new_dev)
			वापस -ENOMEM;

		atkbd->dev = new_dev;
		atkbd->softrepeat = value;
		अगर (atkbd->softrepeat)
			atkbd->softraw = true;
		atkbd_set_device_attrs(atkbd);

		err = input_रेजिस्टर_device(atkbd->dev);
		अगर (err) अणु
			input_मुक्त_device(new_dev);

			atkbd->dev = old_dev;
			atkbd->softrepeat = old_softrepeat;
			atkbd->softraw = old_softraw;
			atkbd_set_device_attrs(atkbd);

			वापस err;
		पूर्ण
		input_unरेजिस्टर_device(old_dev);
	पूर्ण
	वापस count;
पूर्ण


अटल sमाप_प्रकार atkbd_show_softraw(काष्ठा atkbd *atkbd, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", atkbd->softraw ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार atkbd_set_softraw(काष्ठा atkbd *atkbd, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा input_dev *old_dev, *new_dev;
	अचिन्हित पूर्णांक value;
	पूर्णांक err;
	bool old_softraw;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	अगर (value > 1)
		वापस -EINVAL;

	अगर (atkbd->softraw != value) अणु
		old_dev = atkbd->dev;
		old_softraw = atkbd->softraw;

		new_dev = input_allocate_device();
		अगर (!new_dev)
			वापस -ENOMEM;

		atkbd->dev = new_dev;
		atkbd->softraw = value;
		atkbd_set_device_attrs(atkbd);

		err = input_रेजिस्टर_device(atkbd->dev);
		अगर (err) अणु
			input_मुक्त_device(new_dev);

			atkbd->dev = old_dev;
			atkbd->softraw = old_softraw;
			atkbd_set_device_attrs(atkbd);

			वापस err;
		पूर्ण
		input_unरेजिस्टर_device(old_dev);
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार atkbd_show_err_count(काष्ठा atkbd *atkbd, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lu\n", atkbd->err_count);
पूर्ण

अटल पूर्णांक __init atkbd_setup_क्रमced_release(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	atkbd_platक्रमm_fixup = atkbd_apply_क्रमced_release_keylist;
	atkbd_platक्रमm_fixup_data = id->driver_data;

	वापस 1;
पूर्ण

अटल पूर्णांक __init atkbd_setup_scancode_fixup(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	atkbd_platक्रमm_scancode_fixup = id->driver_data;

	वापस 1;
पूर्ण

अटल पूर्णांक __init atkbd_deactivate_fixup(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	atkbd_skip_deactivate = true;
	वापस 1;
पूर्ण

/*
 * NOTE: करो not add any more "force release" quirks to this table.  The
 * task of adjusting list of keys that should be "released" स्वतःmatically
 * by the driver is now delegated to userspace tools, such as udev, so
 * submit such quirks there.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id atkbd_dmi_quirk_table[] __initस्थिर = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "8"), /* Portable */
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_dell_laptop_क्रमced_release_keys,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer Corporation"),
			DMI_MATCH(DMI_CHASSIS_TYPE, "8"), /* Portable */
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_dell_laptop_क्रमced_release_keys,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP 2133"),
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_hp_क्रमced_release_keys,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Pavilion ZV6100"),
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_volume_क्रमced_release_keys,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Presario R4000"),
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_volume_क्रमced_release_keys,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Presario R4100"),
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_volume_क्रमced_release_keys,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Presario R4200"),
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_volume_क्रमced_release_keys,
	पूर्ण,
	अणु
		/* Inventec Symphony */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "INVENTEC"),
			DMI_MATCH(DMI_PRODUCT_NAME, "SYMPHONY 6.0/7.0"),
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_volume_क्रमced_release_keys,
	पूर्ण,
	अणु
		/* Samsung NC10 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
			DMI_MATCH(DMI_PRODUCT_NAME, "NC10"),
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_samsung_क्रमced_release_keys,
	पूर्ण,
	अणु
		/* Samsung NC20 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
			DMI_MATCH(DMI_PRODUCT_NAME, "NC20"),
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_samsung_क्रमced_release_keys,
	पूर्ण,
	अणु
		/* Samsung SQ45S70S */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
			DMI_MATCH(DMI_PRODUCT_NAME, "SQ45S70S"),
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_samsung_क्रमced_release_keys,
	पूर्ण,
	अणु
		/* Fujitsu Amilo PA 1510 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Pa 1510"),
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_volume_क्रमced_release_keys,
	पूर्ण,
	अणु
		/* Fujitsu Amilo Pi 3525 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Pi 3525"),
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_amilo_pi3525_क्रमced_release_keys,
	पूर्ण,
	अणु
		/* Fujitsu Amilo Xi 3650 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Xi 3650"),
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkbd_amilo_xi3650_क्रमced_release_keys,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Soltech Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TA12"),
		पूर्ण,
		.callback = atkbd_setup_क्रमced_release,
		.driver_data = atkdb_soltech_ta12_क्रमced_release_keys,
	पूर्ण,
	अणु
		/* OQO Model 01+ */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "OQO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ZEPTO"),
		पूर्ण,
		.callback = atkbd_setup_scancode_fixup,
		.driver_data = atkbd_oqo_01plus_scancode_fixup,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LG Electronics"),
		पूर्ण,
		.callback = atkbd_deactivate_fixup,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init atkbd_init(व्योम)
अणु
	dmi_check_प्रणाली(atkbd_dmi_quirk_table);

	वापस serio_रेजिस्टर_driver(&atkbd_drv);
पूर्ण

अटल व्योम __निकास atkbd_निकास(व्योम)
अणु
	serio_unरेजिस्टर_driver(&atkbd_drv);
पूर्ण

module_init(atkbd_init);
module_निकास(atkbd_निकास);
