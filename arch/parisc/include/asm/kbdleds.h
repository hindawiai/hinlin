<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_KBDLEDS_H
#घोषणा _ASM_PARISC_KBDLEDS_H

/*
 * On HIL keyboards of PARISC machines there is no NumLock key and
 * everyone expects the keypad to be used क्रम numbers. That's why
 * we can safely turn on the NUMLOCK bit.
 */

अटल अंतरभूत पूर्णांक kbd_defleds(व्योम)
अणु
#अगर defined(CONFIG_KEYBOARD_HIL) || defined(CONFIG_KEYBOARD_HIL_OLD)
	वापस 1 << VC_NUMLOCK;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _ASM_PARISC_KBDLEDS_H */
