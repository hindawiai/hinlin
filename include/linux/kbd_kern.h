<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _KBD_KERN_H
#घोषणा _KBD_KERN_H

#समावेश <linux/tty.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/keyboard.h>

बाह्य अक्षर *func_table[MAX_NR_FUNC];

/*
 * kbd->xxx contains the VC-local things (flag settings etc..)
 *
 * Note: बाह्यally visible are LED_SCR, LED_NUM, LED_CAP defined in kd.h
 *       The code in KDGETLED / KDSETLED depends on the पूर्णांकernal and
 *       बाह्यal order being the same.
 *
 * Note: lockstate is used as index in the array key_map.
 */
काष्ठा kbd_काष्ठा अणु

	अचिन्हित अक्षर lockstate;
/* 8 modअगरiers - the names करो not have any meaning at all;
   they can be associated to arbitrarily chosen keys */
#घोषणा VC_SHIFTLOCK	KG_SHIFT	/* shअगरt lock mode */
#घोषणा VC_ALTGRLOCK	KG_ALTGR	/* altgr lock mode */
#घोषणा VC_CTRLLOCK	KG_CTRL 	/* control lock mode */
#घोषणा VC_ALTLOCK	KG_ALT  	/* alt lock mode */
#घोषणा VC_SHIFTLLOCK	KG_SHIFTL	/* shअगरtl lock mode */
#घोषणा VC_SHIFTRLOCK	KG_SHIFTR	/* shअगरtr lock mode */
#घोषणा VC_CTRLLLOCK	KG_CTRLL 	/* ctrll lock mode */
#घोषणा VC_CTRLRLOCK	KG_CTRLR 	/* ctrlr lock mode */
	अचिन्हित अक्षर slockstate; 	/* क्रम `sticky' Shअगरt, Ctrl, etc. */

	अचिन्हित अक्षर ledmode:1;
#घोषणा LED_SHOW_FLAGS 0        /* traditional state */
#घोषणा LED_SHOW_IOCTL 1        /* only change leds upon ioctl */

	अचिन्हित अक्षर ledflagstate:4;	/* flags, not lights */
	अचिन्हित अक्षर शेष_ledflagstate:4;
#घोषणा VC_SCROLLOCK	0	/* scroll-lock mode */
#घोषणा VC_NUMLOCK	1	/* numeric lock mode */
#घोषणा VC_CAPSLOCK	2	/* capslock mode */
#घोषणा VC_KANALOCK	3	/* kanalock mode */

	अचिन्हित अक्षर kbdmode:3;	/* one 3-bit value */
#घोषणा VC_XLATE	0	/* translate keycodes using keymap */
#घोषणा VC_MEDIUMRAW	1	/* medium raw (keycode) mode */
#घोषणा VC_RAW		2	/* raw (scancode) mode */
#घोषणा VC_UNICODE	3	/* Unicode mode */
#घोषणा VC_OFF		4	/* disabled mode */

	अचिन्हित अक्षर modeflags:5;
#घोषणा VC_APPLIC	0	/* application key mode */
#घोषणा VC_CKMODE	1	/* cursor key mode */
#घोषणा VC_REPEAT	2	/* keyboard repeat */
#घोषणा VC_CRLF		3	/* 0 - enter sends CR, 1 - enter sends CRLF */
#घोषणा VC_META		4	/* 0 - meta, 1 - meta=prefix with ESC */
पूर्ण;

बाह्य पूर्णांक kbd_init(व्योम);

बाह्य व्योम setledstate(काष्ठा kbd_काष्ठा *kbd, अचिन्हित पूर्णांक led);

बाह्य पूर्णांक करो_poke_blanked_console;

बाह्य व्योम (*kbd_ledfunc)(अचिन्हित पूर्णांक led);

बाह्य पूर्णांक set_console(पूर्णांक nr);
बाह्य व्योम schedule_console_callback(व्योम);

अटल अंतरभूत पूर्णांक vc_kbd_mode(काष्ठा kbd_काष्ठा * kbd, पूर्णांक flag)
अणु
	वापस ((kbd->modeflags >> flag) & 1);
पूर्ण

अटल अंतरभूत पूर्णांक vc_kbd_led(काष्ठा kbd_काष्ठा * kbd, पूर्णांक flag)
अणु
	वापस ((kbd->ledflagstate >> flag) & 1);
पूर्ण

अटल अंतरभूत व्योम set_vc_kbd_mode(काष्ठा kbd_काष्ठा * kbd, पूर्णांक flag)
अणु
	kbd->modeflags |= 1 << flag;
पूर्ण

अटल अंतरभूत व्योम set_vc_kbd_led(काष्ठा kbd_काष्ठा * kbd, पूर्णांक flag)
अणु
	kbd->ledflagstate |= 1 << flag;
पूर्ण

अटल अंतरभूत व्योम clr_vc_kbd_mode(काष्ठा kbd_काष्ठा * kbd, पूर्णांक flag)
अणु
	kbd->modeflags &= ~(1 << flag);
पूर्ण

अटल अंतरभूत व्योम clr_vc_kbd_led(काष्ठा kbd_काष्ठा * kbd, पूर्णांक flag)
अणु
	kbd->ledflagstate &= ~(1 << flag);
पूर्ण

अटल अंतरभूत व्योम chg_vc_kbd_lock(काष्ठा kbd_काष्ठा * kbd, पूर्णांक flag)
अणु
	kbd->lockstate ^= 1 << flag;
पूर्ण

अटल अंतरभूत व्योम chg_vc_kbd_slock(काष्ठा kbd_काष्ठा * kbd, पूर्णांक flag)
अणु
	kbd->slockstate ^= 1 << flag;
पूर्ण

अटल अंतरभूत व्योम chg_vc_kbd_mode(काष्ठा kbd_काष्ठा * kbd, पूर्णांक flag)
अणु
	kbd->modeflags ^= 1 << flag;
पूर्ण

अटल अंतरभूत व्योम chg_vc_kbd_led(काष्ठा kbd_काष्ठा * kbd, पूर्णांक flag)
अणु
	kbd->ledflagstate ^= 1 << flag;
पूर्ण

#घोषणा U(x) ((x) ^ 0xf000)

#घोषणा BRL_UC_ROW 0x2800

/* keyboard.c */

काष्ठा console;

व्योम vt_set_leds_compute_shअगरtstate(व्योम);

/* defkeymap.c */

बाह्य अचिन्हित पूर्णांक keymap_count;

#पूर्ण_अगर
