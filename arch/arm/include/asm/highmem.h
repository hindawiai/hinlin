<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_HIGHMEM_H
#घोषणा _ASM_HIGHMEM_H

#समावेश <यंत्र/cachetype.h>
#समावेश <यंत्र/fixmap.h>

#घोषणा PKMAP_BASE		(PAGE_OFFSET - PMD_SIZE)
#घोषणा LAST_PKMAP		PTRS_PER_PTE
#घोषणा LAST_PKMAP_MASK		(LAST_PKMAP - 1)
#घोषणा PKMAP_NR(virt)		(((virt) - PKMAP_BASE) >> PAGE_SHIFT)
#घोषणा PKMAP_ADDR(nr)		(PKMAP_BASE + ((nr) << PAGE_SHIFT))

#घोषणा flush_cache_kmaps() \
	करो अणु \
		अगर (cache_is_vivt()) \
			flush_cache_all(); \
	पूर्ण जबतक (0)

बाह्य pte_t *pkmap_page_table;

/*
 * The reason क्रम kmap_high_get() is to ensure that the currently kmap'd
 * page usage count करोes not decrease to zero जबतक we're using its
 * existing भव mapping in an atomic context.  With a VIVT cache this
 * is essential to करो, but with a VIPT cache this is only an optimization
 * so not to pay the price of establishing a second mapping अगर an existing
 * one can be used.  However, on platक्रमms without hardware TLB मुख्यtenance
 * broadcast, we simply cannot use ARCH_NEEDS_KMAP_HIGH_GET at all since
 * the locking involved must also disable IRQs which is incompatible with
 * the IPI mechanism used by global TLB operations.
 */
#घोषणा ARCH_NEEDS_KMAP_HIGH_GET
#अगर defined(CONFIG_SMP) && defined(CONFIG_CPU_TLB_V6)
#अघोषित ARCH_NEEDS_KMAP_HIGH_GET
#अगर defined(CONFIG_HIGHMEM) && defined(CONFIG_CPU_CACHE_VIVT)
#त्रुटि "The sum of features in your kernel config cannot be supported together"
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * Needed to be able to broadcast the TLB invalidation क्रम kmap.
 */
#अगर_घोषित CONFIG_ARM_ERRATA_798181
#अघोषित ARCH_NEEDS_KMAP_HIGH_GET
#पूर्ण_अगर

#अगर_घोषित ARCH_NEEDS_KMAP_HIGH_GET
बाह्य व्योम *kmap_high_get(काष्ठा page *page);

अटल अंतरभूत व्योम *arch_kmap_local_high_get(काष्ठा page *page)
अणु
	अगर (IS_ENABLED(CONFIG_DEBUG_HIGHMEM) && !cache_is_vivt())
		वापस शून्य;
	वापस kmap_high_get(page);
पूर्ण
#घोषणा arch_kmap_local_high_get arch_kmap_local_high_get

#अन्यथा /* ARCH_NEEDS_KMAP_HIGH_GET */
अटल अंतरभूत व्योम *kmap_high_get(काष्ठा page *page)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* !ARCH_NEEDS_KMAP_HIGH_GET */

#घोषणा arch_kmap_local_post_map(vaddr, pteval)				\
	local_flush_tlb_kernel_page(vaddr)

#घोषणा arch_kmap_local_pre_unmap(vaddr)				\
करो अणु									\
	अगर (cache_is_vivt())						\
		__cpuc_flush_dcache_area((व्योम *)vaddr, PAGE_SIZE);	\
पूर्ण जबतक (0)

#घोषणा arch_kmap_local_post_unmap(vaddr)				\
	local_flush_tlb_kernel_page(vaddr)

#पूर्ण_अगर
