<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_PAGE_32_H
#घोषणा _ASM_POWERPC_PAGE_32_H

#समावेश <यंत्र/cache.h>

#अगर defined(CONFIG_PHYSICAL_ALIGN) && (CONFIG_PHYSICAL_START != 0)
#अगर (CONFIG_PHYSICAL_START % CONFIG_PHYSICAL_ALIGN) != 0
#त्रुटि "CONFIG_PHYSICAL_START must be a multiple of CONFIG_PHYSICAL_ALIGN"
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा VM_DATA_DEFAULT_FLAGS	VM_DATA_DEFAULT_FLAGS32

#अगर_घोषित CONFIG_NOT_COHERENT_CACHE
#घोषणा ARCH_DMA_MINALIGN	L1_CACHE_BYTES
#पूर्ण_अगर

#अगर defined(CONFIG_PPC_256K_PAGES) || \
    (defined(CONFIG_PPC_8xx) && defined(CONFIG_PPC_16K_PAGES))
#घोषणा PTE_SHIFT	(PAGE_SHIFT - PTE_T_LOG2 - 2)	/* 1/4 of a page */
#अन्यथा
#घोषणा PTE_SHIFT	(PAGE_SHIFT - PTE_T_LOG2)	/* full page */
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
/*
 * The basic type of a PTE - 64 bits क्रम those CPUs with > 32 bit
 * physical addressing.
 */
#अगर_घोषित CONFIG_PTE_64BIT
प्रकार अचिन्हित दीर्घ दीर्घ pte_basic_t;
#अन्यथा
प्रकार अचिन्हित दीर्घ pte_basic_t;
#पूर्ण_अगर

#समावेश <यंत्र/bug.h>

/*
 * Clear page using the dcbz inकाष्ठाion, which करोesn't cause any
 * memory traffic (except to ग_लिखो out any cache lines which get
 * displaced).  This only works on cacheable memory.
 */
अटल अंतरभूत व्योम clear_page(व्योम *addr)
अणु
	अचिन्हित पूर्णांक i;

	WARN_ON((अचिन्हित दीर्घ)addr & (L1_CACHE_BYTES - 1));

	क्रम (i = 0; i < PAGE_SIZE / L1_CACHE_BYTES; i++, addr += L1_CACHE_BYTES)
		dcbz(addr);
पूर्ण
बाह्य व्योम copy_page(व्योम *to, व्योम *from);

#समावेश <यंत्र-generic/getorder.h>

#घोषणा PGD_T_LOG2	(__builtin_ffs(माप(pgd_t)) - 1)
#घोषणा PTE_T_LOG2	(__builtin_ffs(माप(pte_t)) - 1)

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_PAGE_32_H */
