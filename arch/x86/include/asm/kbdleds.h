<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_KBDLEDS_H
#घोषणा _ASM_X86_KBDLEDS_H

/*
 * Some laptops take the 789uiojklm,. keys as number pad when NumLock is on.
 * This seems a good reason to start with NumLock off. That's why on X86 we
 * ask the bios क्रम the correct state.
 */

#समावेश <यंत्र/setup.h>

अटल अंतरभूत पूर्णांक kbd_defleds(व्योम)
अणु
	वापस boot_params.kbd_status & 0x20 ? (1 << VC_NUMLOCK) : 0;
पूर्ण

#पूर्ण_अगर /* _ASM_X86_KBDLEDS_H */
