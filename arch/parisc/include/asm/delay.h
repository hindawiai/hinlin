<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_DELAY_H
#घोषणा _ASM_PARISC_DELAY_H

अटल __अंतरभूत__ व्योम __delay(अचिन्हित दीर्घ loops) अणु
	यंत्र अस्थिर(
	"	.balignl	64,0x34000034\n"
	"	addib,UV -1,%0,.\n"
	"	nop\n"
		: "=r" (loops) : "0" (loops));
पूर्ण

बाह्य व्योम __udelay(अचिन्हित दीर्घ usecs);
बाह्य व्योम __udelay_bad(अचिन्हित दीर्घ usecs);

अटल अंतरभूत व्योम udelay(अचिन्हित दीर्घ usecs)
अणु
	अगर (__builtin_स्थिरant_p(usecs) && (usecs) > 20000)
		__udelay_bad(usecs);
	__udelay(usecs);
पूर्ण

#पूर्ण_अगर /* _ASM_PARISC_DELAY_H */
