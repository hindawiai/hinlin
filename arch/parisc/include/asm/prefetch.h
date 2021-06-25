<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र-parisc/prefetch.h
 *
 * PA 2.0 defines data prefetch inकाष्ठाions on page 6-11 of the Kane book.
 * In addition, many implementations करो hardware prefetching of both
 * inकाष्ठाions and data.
 *
 * PA7300LC (page 14-4 of the ERS) also implements prefetching by a load
 * to gr0 but not in a way that Linux can use.  If the load would cause an
 * पूर्णांकerruption (eg due to prefetching 0), it is suppressed on PA2.0
 * processors, but not on 7300LC.
 *
 */

#अगर_अघोषित __ASM_PARISC_PREFETCH_H
#घोषणा __ASM_PARISC_PREFETCH_H

#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित CONFIG_PREFETCH

#घोषणा ARCH_HAS_PREFETCH
अटल अंतरभूत व्योम prefetch(स्थिर व्योम *addr)
अणु
	__यंत्र__(
#अगर_अघोषित CONFIG_PA20
		/* Need to aव्योम prefetch of शून्य on PA7300LC */
		"	extrw,u,= %0,31,32,%%r0\n"
#पूर्ण_अगर
		"	ldw 0(%0), %%r0" : : "r" (addr));
पूर्ण

/* LDD is a PA2.0 addition. */
#अगर_घोषित CONFIG_PA20
#घोषणा ARCH_HAS_PREFETCHW
अटल अंतरभूत व्योम prefetchw(स्थिर व्योम *addr)
अणु
	__यंत्र__("ldd 0(%0), %%r0" : : "r" (addr));
पूर्ण
#पूर्ण_अगर /* CONFIG_PA20 */

#पूर्ण_अगर /* CONFIG_PREFETCH */
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_PARISC_PROCESSOR_H */
