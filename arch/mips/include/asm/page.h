<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 - 1999, 2000, 03 Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_PAGE_H
#घोषणा _ASM_PAGE_H

#समावेश <spaces.h>
#समावेश <linux/स्थिर.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/mipsregs.h>

/*
 * PAGE_SHIFT determines the page size
 */
#अगर_घोषित CONFIG_PAGE_SIZE_4KB
#घोषणा PAGE_SHIFT	12
#पूर्ण_अगर
#अगर_घोषित CONFIG_PAGE_SIZE_8KB
#घोषणा PAGE_SHIFT	13
#पूर्ण_अगर
#अगर_घोषित CONFIG_PAGE_SIZE_16KB
#घोषणा PAGE_SHIFT	14
#पूर्ण_अगर
#अगर_घोषित CONFIG_PAGE_SIZE_32KB
#घोषणा PAGE_SHIFT	15
#पूर्ण_अगर
#अगर_घोषित CONFIG_PAGE_SIZE_64KB
#घोषणा PAGE_SHIFT	16
#पूर्ण_अगर
#घोषणा PAGE_SIZE	(_AC(1,UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK	(~((1 << PAGE_SHIFT) - 1))

/*
 * This is used क्रम calculating the real page sizes
 * क्रम FTLB or VTLB + FTLB configurations.
 */
अटल अंतरभूत अचिन्हित पूर्णांक page_size_ftlb(अचिन्हित पूर्णांक mmuextdef)
अणु
	चयन (mmuextdef) अणु
	हाल MIPS_CONF4_MMUEXTDEF_FTLBSIZEEXT:
		अगर (PAGE_SIZE == (1 << 30))
			वापस 5;
		अगर (PAGE_SIZE == (1llu << 32))
			वापस 6;
		अगर (PAGE_SIZE > (256 << 10))
			वापस 7; /* reserved */
		fallthrough;
	हाल MIPS_CONF4_MMUEXTDEF_VTLBSIZEEXT:
		वापस (PAGE_SHIFT - 10) / 2;
	शेष:
		panic("Invalid FTLB configuration with Conf4_mmuextdef=%d value\n",
		      mmuextdef >> 14);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
#घोषणा HPAGE_SHIFT	(PAGE_SHIFT + PAGE_SHIFT - 3)
#घोषणा HPAGE_SIZE	(_AC(1,UL) << HPAGE_SHIFT)
#घोषणा HPAGE_MASK	(~(HPAGE_SIZE - 1))
#घोषणा HUGETLB_PAGE_ORDER	(HPAGE_SHIFT - PAGE_SHIFT)
#अन्यथा /* !CONFIG_MIPS_HUGE_TLB_SUPPORT */
#घोषणा HPAGE_SHIFT	(अणुBUILD_BUG(); 0; पूर्ण)
#घोषणा HPAGE_SIZE	(अणुBUILD_BUG(); 0; पूर्ण)
#घोषणा HPAGE_MASK	(अणुBUILD_BUG(); 0; पूर्ण)
#घोषणा HUGETLB_PAGE_ORDER	(अणुBUILD_BUG(); 0; पूर्ण)
#पूर्ण_अगर /* CONFIG_MIPS_HUGE_TLB_SUPPORT */

#समावेश <linux/pfn.h>

बाह्य व्योम build_clear_page(व्योम);
बाह्य व्योम build_copy_page(व्योम);

/*
 * It's normally defined only for FLATMEM config but it's
 * used in our early mem init code क्रम all memory models.
 * So always define it.
 */
#अगर_घोषित CONFIG_MIPS_AUTO_PFN_OFFSET
बाह्य अचिन्हित दीर्घ ARCH_PFN_OFFSET;
# define ARCH_PFN_OFFSET	ARCH_PFN_OFFSET
#अन्यथा
# define ARCH_PFN_OFFSET	PFN_UP(PHYS_OFFSET)
#पूर्ण_अगर

बाह्य व्योम clear_page(व्योम * page);
बाह्य व्योम copy_page(व्योम * to, व्योम * from);

बाह्य अचिन्हित दीर्घ shm_align_mask;

अटल अंतरभूत अचिन्हित दीर्घ pages_करो_alias(अचिन्हित दीर्घ addr1,
	अचिन्हित दीर्घ addr2)
अणु
	वापस (addr1 ^ addr2) & shm_align_mask;
पूर्ण

काष्ठा page;

अटल अंतरभूत व्योम clear_user_page(व्योम *addr, अचिन्हित दीर्घ vaddr,
	काष्ठा page *page)
अणु
	बाह्य व्योम (*flush_data_cache_page)(अचिन्हित दीर्घ addr);

	clear_page(addr);
	अगर (pages_करो_alias((अचिन्हित दीर्घ) addr, vaddr & PAGE_MASK))
		flush_data_cache_page((अचिन्हित दीर्घ)addr);
पूर्ण

काष्ठा vm_area_काष्ठा;
बाह्य व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
	अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma);

#घोषणा __HAVE_ARCH_COPY_USER_HIGHPAGE

/*
 * These are used to make use of C type-checking..
 */
#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
  #अगर_घोषित CONFIG_CPU_MIPS32
    प्रकार काष्ठा अणु अचिन्हित दीर्घ pte_low, pte_high; पूर्ण pte_t;
    #घोषणा pte_val(x)	  ((x).pte_low | ((अचिन्हित दीर्घ दीर्घ)(x).pte_high << 32))
    #घोषणा __pte(x)	  (अणु pte_t __pte = अणु(x), ((अचिन्हित दीर्घ दीर्घ)(x)) >> 32पूर्ण; __pte; पूर्ण)
  #अन्यथा
     प्रकार काष्ठा अणु अचिन्हित दीर्घ दीर्घ pte; पूर्ण pte_t;
     #घोषणा pte_val(x) ((x).pte)
     #घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण )
  #पूर्ण_अगर
#अन्यथा
प्रकार काष्ठा अणु अचिन्हित दीर्घ pte; पूर्ण pte_t;
#घोषणा pte_val(x)	((x).pte)
#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण )
#पूर्ण_अगर
प्रकार काष्ठा page *pgtable_t;

/*
 * Right now we करोn't support 4-level pagetables, so all pud-related
 * definitions come from <यंत्र-generic/pgtable-nopud.h>.
 */

/*
 * Finall the top of the hierarchy, the pgd
 */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;
#घोषणा pgd_val(x)	((x).pgd)
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण )

/*
 * Manipulate page protection bits
 */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;
#घोषणा pgprot_val(x)	((x).pgprot)
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण )
#घोषणा pte_pgprot(x)	__pgprot(pte_val(x) & ~_PFN_MASK)

/*
 * On R4000-style MMUs where a TLB entry is mapping a adjacent even / odd
 * pair of pages we only have a single global bit per pair of pages.  When
 * writing to the TLB make sure we always have the bit set क्रम both pages
 * or none.  This macro is used to access the `buddy' of the pte we're just
 * working on.
 */
#घोषणा ptep_buddy(x)	((pte_t *)((अचिन्हित दीर्घ)(x) ^ माप(pte_t)))

/*
 * __pa()/__va() should be used only during mem init.
 */
अटल अंतरभूत अचिन्हित दीर्घ ___pa(अचिन्हित दीर्घ x)
अणु
	अगर (IS_ENABLED(CONFIG_64BIT)) अणु
		/*
		 * For MIPS64 the भव address may either be in one of
		 * the compatibility segements ckseg0 or ckseg1, or it may
		 * be in xkphys.
		 */
		वापस x < CKSEG0 ? XPHYSADDR(x) : CPHYSADDR(x);
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_EVA)) अणु
		/*
		 * We're using the standard MIPS32 legacy memory map, ie.
		 * the address x is going to be in kseg0 or kseg1. We can
		 * handle either हाल by masking out the desired bits using
		 * CPHYSADDR.
		 */
		वापस CPHYSADDR(x);
	पूर्ण

	/*
	 * EVA is in use so the memory map could be anything, making it not
	 * safe to just mask out bits.
	 */
	वापस x - PAGE_OFFSET + PHYS_OFFSET;
पूर्ण
#घोषणा __pa(x)		___pa((अचिन्हित दीर्घ)(x))
#घोषणा __va(x)		((व्योम *)((अचिन्हित दीर्घ)(x) + PAGE_OFFSET - PHYS_OFFSET))
#समावेश <यंत्र/पन.स>

/*
 * RELOC_HIDE was originally added by 6007b903dfe5f1d13e0c711ac2894bdd4a61b1ad
 * (lmo) rsp. 8431fd094d625b94d364fe393076ccef88e6ce18 (kernel.org).  The
 * discussion can be found in
 * https://lore.kernel.org/lkml/a2ebde260608230500o3407b108hc03debb9da6e62c@mail.gmail.com
 *
 * It is unclear अगर the misscompilations mentioned in
 * https://lore.kernel.org/lkml/1281303490-390-1-git-send-email-namhyung@gmail.com
 * also affect MIPS so we keep this one until GCC 3.x has been retired
 * beक्रमe we can apply https://patchwork.linux-mips.org/patch/1541/
 */
#घोषणा __pa_symbol_nodebug(x)	__pa(RELOC_HIDE((अचिन्हित दीर्घ)(x), 0))

#अगर_घोषित CONFIG_DEBUG_VIRTUAL
बाह्य phys_addr_t __phys_addr_symbol(अचिन्हित दीर्घ x);
#अन्यथा
#घोषणा __phys_addr_symbol(x)	__pa_symbol_nodebug(x)
#पूर्ण_अगर

#अगर_अघोषित __pa_symbol
#घोषणा __pa_symbol(x)		__phys_addr_symbol((अचिन्हित दीर्घ)(x))
#पूर्ण_अगर

#घोषणा pfn_to_kaddr(pfn)	__va((pfn) << PAGE_SHIFT)

#अगर_घोषित CONFIG_FLATMEM

अटल अंतरभूत पूर्णांक pfn_valid(अचिन्हित दीर्घ pfn)
अणु
	/* aव्योम <linux/mm.h> include hell */
	बाह्य अचिन्हित दीर्घ max_mapnr;
	अचिन्हित दीर्घ pfn_offset = ARCH_PFN_OFFSET;

	वापस pfn >= pfn_offset && pfn < max_mapnr;
पूर्ण

#या_अगर defined(CONFIG_SPARSEMEM)

/* pfn_valid is defined in linux/mmzone.h */

#या_अगर defined(CONFIG_NEED_MULTIPLE_NODES)

#घोषणा pfn_valid(pfn)							\
(अणु									\
	अचिन्हित दीर्घ __pfn = (pfn);					\
	पूर्णांक __n = pfn_to_nid(__pfn);					\
	((__n >= 0) ? (__pfn < NODE_DATA(__n)->node_start_pfn +		\
			       NODE_DATA(__n)->node_spanned_pages)	\
		    : 0);						\
पूर्ण)

#पूर्ण_अगर

#घोषणा virt_to_pfn(kaddr)   	PFN_DOWN(virt_to_phys((व्योम *)(kaddr)))
#घोषणा virt_to_page(kaddr)	pfn_to_page(virt_to_pfn(kaddr))

बाह्य bool __virt_addr_valid(स्थिर अस्थिर व्योम *kaddr);
#घोषणा virt_addr_valid(kaddr)						\
	__virt_addr_valid((स्थिर अस्थिर व्योम *) (kaddr))

#घोषणा VM_DATA_DEFAULT_FLAGS	VM_DATA_FLAGS_TSK_EXEC

बाह्य अचिन्हित दीर्घ __kaslr_offset;
अटल अंतरभूत अचिन्हित दीर्घ kaslr_offset(व्योम)
अणु
	वापस __kaslr_offset;
पूर्ण

#समावेश <यंत्र-generic/memory_model.h>
#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* _ASM_PAGE_H */
