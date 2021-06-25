<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2011 Calxeda, Inc.
 * Based on PPC version Copyright 2007 MontaVista Software, Inc.
 */
#अगर_अघोषित ASM_EDAC_H
#घोषणा ASM_EDAC_H
/*
 * ECC atomic, DMA, SMP and पूर्णांकerrupt safe scrub function.
 * Implements the per arch edac_atomic_scrub() that EDAC use क्रम software
 * ECC scrubbing.  It पढ़ोs memory and then ग_लिखोs back the original
 * value, allowing the hardware to detect and correct memory errors.
 */

अटल अंतरभूत व्योम edac_atomic_scrub(व्योम *va, u32 size)
अणु
#अगर __LINUX_ARM_ARCH__ >= 6
	अचिन्हित पूर्णांक *virt_addr = va;
	अचिन्हित पूर्णांक temp, temp2;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size / माप(*virt_addr); i++, virt_addr++) अणु
		/* Very carefully पढ़ो and ग_लिखो to memory atomically
		 * so we are पूर्णांकerrupt, DMA and SMP safe.
		 */
		__यंत्र__ __अस्थिर__("\n"
			"1:	ldrex	%0, [%2]\n"
			"	strex	%1, %0, [%2]\n"
			"	teq	%1, #0\n"
			"	bne	1b\n"
			: "=&r"(temp), "=&r"(temp2)
			: "r"(virt_addr)
			: "cc");
	पूर्ण
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर
