<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_CACHETYPE_H
#घोषणा __ASM_ARM_CACHETYPE_H

#घोषणा CACHEID_VIVT			(1 << 0)
#घोषणा CACHEID_VIPT_NONALIASING	(1 << 1)
#घोषणा CACHEID_VIPT_ALIASING		(1 << 2)
#घोषणा CACHEID_VIPT			(CACHEID_VIPT_ALIASING|CACHEID_VIPT_NONALIASING)
#घोषणा CACHEID_ASID_TAGGED		(1 << 3)
#घोषणा CACHEID_VIPT_I_ALIASING		(1 << 4)
#घोषणा CACHEID_PIPT			(1 << 5)

बाह्य अचिन्हित पूर्णांक cacheid;

#घोषणा cache_is_vivt()			cacheid_is(CACHEID_VIVT)
#घोषणा cache_is_vipt()			cacheid_is(CACHEID_VIPT)
#घोषणा cache_is_vipt_nonaliasing()	cacheid_is(CACHEID_VIPT_NONALIASING)
#घोषणा cache_is_vipt_aliasing()	cacheid_is(CACHEID_VIPT_ALIASING)
#घोषणा icache_is_vivt_asid_tagged()	cacheid_is(CACHEID_ASID_TAGGED)
#घोषणा icache_is_vipt_aliasing()	cacheid_is(CACHEID_VIPT_I_ALIASING)
#घोषणा icache_is_pipt()		cacheid_is(CACHEID_PIPT)

/*
 * __LINUX_ARM_ARCH__ is the minimum supported CPU architecture
 * Mask out support which will never be present on newer CPUs.
 * - v6+ is never VIVT
 * - v7+ VIPT never aliases on D-side
 */
#अगर __LINUX_ARM_ARCH__ >= 7
#घोषणा __CACHEID_ARCH_MIN	(CACHEID_VIPT_NONALIASING |\
				 CACHEID_ASID_TAGGED |\
				 CACHEID_VIPT_I_ALIASING |\
				 CACHEID_PIPT)
#या_अगर __LINUX_ARM_ARCH__ >= 6
#घोषणा	__CACHEID_ARCH_MIN	(~CACHEID_VIVT)
#अन्यथा
#घोषणा __CACHEID_ARCH_MIN	(~0)
#पूर्ण_अगर

/*
 * Mask out support which isn't configured
 */
#अगर defined(CONFIG_CPU_CACHE_VIVT) && !defined(CONFIG_CPU_CACHE_VIPT)
#घोषणा __CACHEID_ALWAYS	(CACHEID_VIVT)
#घोषणा __CACHEID_NEVER		(~CACHEID_VIVT)
#या_अगर !defined(CONFIG_CPU_CACHE_VIVT) && defined(CONFIG_CPU_CACHE_VIPT)
#घोषणा __CACHEID_ALWAYS	(0)
#घोषणा __CACHEID_NEVER		(CACHEID_VIVT)
#अन्यथा
#घोषणा __CACHEID_ALWAYS	(0)
#घोषणा __CACHEID_NEVER		(0)
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक __attribute__((pure)) cacheid_is(अचिन्हित पूर्णांक mask)
अणु
	वापस (__CACHEID_ALWAYS & mask) |
	       (~__CACHEID_NEVER & __CACHEID_ARCH_MIN & mask & cacheid);
पूर्ण

#घोषणा CSSELR_ICACHE	1
#घोषणा CSSELR_DCACHE	0

#घोषणा CSSELR_L1	(0 << 1)
#घोषणा CSSELR_L2	(1 << 1)
#घोषणा CSSELR_L3	(2 << 1)
#घोषणा CSSELR_L4	(3 << 1)
#घोषणा CSSELR_L5	(4 << 1)
#घोषणा CSSELR_L6	(5 << 1)
#घोषणा CSSELR_L7	(6 << 1)

#अगर_अघोषित CONFIG_CPU_V7M
अटल अंतरभूत व्योम set_csselr(अचिन्हित पूर्णांक cache_selector)
अणु
	यंत्र अस्थिर("mcr p15, 2, %0, c0, c0, 0" : : "r" (cache_selector));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक पढ़ो_ccsidr(व्योम)
अणु
	अचिन्हित पूर्णांक val;

	यंत्र अस्थिर("mrc p15, 1, %0, c0, c0, 0" : "=r" (val));
	वापस val;
पूर्ण
#अन्यथा /* CONFIG_CPU_V7M */
#समावेश <linux/पन.स>
#समावेश "asm/v7m.h"

अटल अंतरभूत व्योम set_csselr(अचिन्हित पूर्णांक cache_selector)
अणु
	ग_लिखोl(cache_selector, BASEADDR_V7M_SCB + V7M_SCB_CTR);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक पढ़ो_ccsidr(व्योम)
अणु
	वापस पढ़ोl(BASEADDR_V7M_SCB + V7M_SCB_CCSIDR);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
