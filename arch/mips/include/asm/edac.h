<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASM_EDAC_H
#घोषणा ASM_EDAC_H

#समावेश <यंत्र/compiler.h>

/* ECC atomic, DMA, SMP and पूर्णांकerrupt safe scrub function */

अटल अंतरभूत व्योम edac_atomic_scrub(व्योम *va, u32 size)
अणु
	अचिन्हित दीर्घ *virt_addr = va;
	अचिन्हित दीर्घ temp;
	u32 i;

	क्रम (i = 0; i < size / माप(अचिन्हित दीर्घ); i++) अणु
		/*
		 * Very carefully पढ़ो and ग_लिखो to memory atomically
		 * so we are पूर्णांकerrupt, DMA and SMP safe.
		 *
		 * Intel: यंत्र("lock; addl $0, %0"::"m"(*virt_addr));
		 */

		__यंत्र__ __अस्थिर__ (
		"	.set	push					\n"
		"	.set	mips2					\n"
		"1:	ll	%0, %1		# edac_atomic_scrub	\n"
		"	addu	%0, $0					\n"
		"	sc	%0, %1					\n"
		"	beqz	%0, 1b					\n"
		"	.set	pop					\n"
		: "=&r" (temp), "=" GCC_OFF_SMALL_ASM() (*virt_addr)
		: GCC_OFF_SMALL_ASM() (*virt_addr));

		virt_addr++;
	पूर्ण
पूर्ण

#पूर्ण_अगर
