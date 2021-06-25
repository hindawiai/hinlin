<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Machine specअगरic NMI handling क्रम generic.
 *  Split out from traps.c by Osamu Tomita <tomita@cinet.co.jp>
 */
#अगर_अघोषित _ASM_X86_MACH_DEFAULT_MACH_TRAPS_H
#घोषणा _ASM_X86_MACH_DEFAULT_MACH_TRAPS_H

#समावेश <यंत्र/mc146818rtc.h>

#घोषणा NMI_REASON_PORT		0x61

#घोषणा NMI_REASON_SERR		0x80
#घोषणा NMI_REASON_IOCHK	0x40
#घोषणा NMI_REASON_MASK		(NMI_REASON_SERR | NMI_REASON_IOCHK)

#घोषणा NMI_REASON_CLEAR_SERR	0x04
#घोषणा NMI_REASON_CLEAR_IOCHK	0x08
#घोषणा NMI_REASON_CLEAR_MASK	0x0f

अटल अंतरभूत अचिन्हित अक्षर शेष_get_nmi_reason(व्योम)
अणु
	वापस inb(NMI_REASON_PORT);
पूर्ण

अटल अंतरभूत व्योम reनिश्चित_nmi(व्योम)
अणु
	पूर्णांक old_reg = -1;

	अगर (करो_i_have_lock_cmos())
		old_reg = current_lock_cmos_reg();
	अन्यथा
		lock_cmos(0); /* रेजिस्टर करोesn't matter here */
	outb(0x8f, 0x70);
	inb(0x71);		/* dummy */
	outb(0x0f, 0x70);
	inb(0x71);		/* dummy */
	अगर (old_reg >= 0)
		outb(old_reg, 0x70);
	अन्यथा
		unlock_cmos();
पूर्ण

#पूर्ण_अगर /* _ASM_X86_MACH_DEFAULT_MACH_TRAPS_H */
