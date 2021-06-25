<शैली गुरु>
/*
 * PPC EDAC common defs
 *
 * Author: Dave Jiang <djiang@mvista.com>
 *
 * 2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#अगर_अघोषित ASM_EDAC_H
#घोषणा ASM_EDAC_H
/*
 * ECC atomic, DMA, SMP and पूर्णांकerrupt safe scrub function.
 * Implements the per arch edac_atomic_scrub() that EDAC use क्रम software
 * ECC scrubbing.  It पढ़ोs memory and then ग_लिखोs back the original
 * value, allowing the hardware to detect and correct memory errors.
 */
अटल __अंतरभूत__ व्योम edac_atomic_scrub(व्योम *va, u32 size)
अणु
	अचिन्हित पूर्णांक *virt_addr = va;
	अचिन्हित पूर्णांक temp;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size / माप(*virt_addr); i++, virt_addr++) अणु
		/* Very carefully पढ़ो and ग_लिखो to memory atomically
		 * so we are पूर्णांकerrupt, DMA and SMP safe.
		 */
		__यंत्र__ __अस्थिर__ ("\न\
				1:	lwarx	%0,0,%1\न\
					stwcx.	%0,0,%1\न\
					bne-	1b\न\
					isync"
					: "=&r"(temp)
					: "r"(virt_addr)
					: "cr0", "memory");
	पूर्ण
पूर्ण

#पूर्ण_अगर
