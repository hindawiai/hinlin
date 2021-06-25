<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_PAGE_H
#घोषणा __ASM_CSKY_PAGE_H

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/cache.h>
#समावेश <linux/स्थिर.h>

/*
 * PAGE_SHIFT determines the page size: 4KB
 */
#घोषणा PAGE_SHIFT	12
#घोषणा PAGE_SIZE	(_AC(1, UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK	(~(PAGE_SIZE - 1))
#घोषणा THREAD_SIZE	(PAGE_SIZE * 2)
#घोषणा THREAD_MASK	(~(THREAD_SIZE - 1))
#घोषणा THREAD_SHIFT	(PAGE_SHIFT + 1)


/*
 * For C-SKY "User-space:Kernel-space" is "2GB:2GB" fixed by hardware and there
 * are two segment रेजिस्टरs (MSA0 + MSA1) to mapping 512MB + 512MB physical
 * address region. We use them mapping kernel 1GB direct-map address area and
 * क्रम more than 1GB of memory we use highmem.
 */
#घोषणा PAGE_OFFSET	CONFIG_PAGE_OFFSET
#घोषणा SSEG_SIZE	0x20000000
#घोषणा LOWMEM_LIMIT	(SSEG_SIZE * 2)

#घोषणा PHYS_OFFSET_OFFSET (CONFIG_DRAM_BASE & (SSEG_SIZE - 1))

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/pfn.h>

#घोषणा virt_to_pfn(kaddr)      (__pa(kaddr) >> PAGE_SHIFT)
#घोषणा pfn_to_virt(pfn)        __va((pfn) << PAGE_SHIFT)

#घोषणा virt_addr_valid(kaddr)  ((व्योम *)(kaddr) >= (व्योम *)PAGE_OFFSET && \
			(व्योम *)(kaddr) < high_memory)
#घोषणा pfn_valid(pfn)		((pfn) >= ARCH_PFN_OFFSET && ((pfn) - ARCH_PFN_OFFSET) < max_mapnr)

बाह्य व्योम *स_रखो(व्योम *dest, पूर्णांक c, माप_प्रकार l);
बाह्य व्योम *स_नकल(व्योम *to, स्थिर व्योम *from, माप_प्रकार l);

#घोषणा clear_page(page)	स_रखो((page), 0, PAGE_SIZE)
#घोषणा copy_page(to, from)	स_नकल((to), (from), PAGE_SIZE)

#घोषणा page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)
#घोषणा phys_to_page(paddr)	(pfn_to_page(PFN_DOWN(paddr)))

काष्ठा page;

#समावेश <abi/page.h>

काष्ठा vm_area_काष्ठा;

प्रकार काष्ठा अणु अचिन्हित दीर्घ pte_low; पूर्ण pte_t;
#घोषणा pte_val(x)	((x).pte_low)

प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;
प्रकार काष्ठा page *pgtable_t;

#घोषणा pgd_val(x)	((x).pgd)
#घोषणा pgprot_val(x)	((x).pgprot)

#घोषणा ptep_buddy(x)	((pte_t *)((अचिन्हित दीर्घ)(x) ^ माप(pte_t)))

#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण)
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण)
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण)

बाह्य अचिन्हित दीर्घ va_pa_offset;

#घोषणा ARCH_PFN_OFFSET	PFN_DOWN(va_pa_offset + PHYS_OFFSET_OFFSET)

#घोषणा __pa(x)		 ((अचिन्हित दीर्घ)(x) - PAGE_OFFSET + va_pa_offset)
#घोषणा __va(x) ((व्योम *)((अचिन्हित दीर्घ)(x) + PAGE_OFFSET - va_pa_offset))

#घोषणा __pa_symbol(x)	__pa(RELOC_HIDE((अचिन्हित दीर्घ)(x), 0))

#घोषणा MAP_NR(x)	PFN_DOWN((अचिन्हित दीर्घ)(x) - PAGE_OFFSET - \
				 PHYS_OFFSET_OFFSET)
#घोषणा virt_to_page(x)	(mem_map + MAP_NR(x))

#घोषणा pfn_to_kaddr(x)	__va(PFN_PHYS(x))

#समावेश <यंत्र-generic/memory_model.h>
#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_CSKY_PAGE_H */
