<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_32_PGTABLE_H
#घोषणा _ASM_POWERPC_NOHASH_32_PGTABLE_H

#समावेश <यंत्र-generic/pgtable-nopmd.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/sched.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/mmu.h>			/* For sub-arch specअगरic PPC_PIN_SIZE */

#अगर_घोषित CONFIG_44x
बाह्य पूर्णांक icache_44x_need_flush;
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#घोषणा PTE_INDEX_SIZE	PTE_SHIFT
#घोषणा PMD_INDEX_SIZE	0
#घोषणा PUD_INDEX_SIZE	0
#घोषणा PGD_INDEX_SIZE	(32 - PGसूची_SHIFT)

#घोषणा PMD_CACHE_INDEX	PMD_INDEX_SIZE
#घोषणा PUD_CACHE_INDEX	PUD_INDEX_SIZE

#अगर_अघोषित __ASSEMBLY__
#घोषणा PTE_TABLE_SIZE	(माप(pte_t) << PTE_INDEX_SIZE)
#घोषणा PMD_TABLE_SIZE	0
#घोषणा PUD_TABLE_SIZE	0
#घोषणा PGD_TABLE_SIZE	(माप(pgd_t) << PGD_INDEX_SIZE)

#घोषणा PMD_MASKED_BITS (PTE_TABLE_SIZE - 1)
#पूर्ण_अगर	/* __ASSEMBLY__ */

#घोषणा PTRS_PER_PTE	(1 << PTE_INDEX_SIZE)
#घोषणा PTRS_PER_PGD	(1 << PGD_INDEX_SIZE)

/*
 * The normal हाल is that PTEs are 32-bits and we have a 1-page
 * 1024-entry pgdir poपूर्णांकing to 1-page 1024-entry PTE pages.  -- paulus
 *
 * For any >32-bit physical address platक्रमm, we can use the following
 * two level page table layout where the pgdir is 8KB and the MS 13 bits
 * are an index to the second level table.  The combined pgdir/pmd first
 * level has 2048 entries and the second level has 512 64-bit PTE entries.
 * -Matt
 */
/* PGसूची_SHIFT determines what a top-level page table entry can map */
#घोषणा PGसूची_SHIFT	(PAGE_SHIFT + PTE_INDEX_SIZE)
#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/* Bits to mask out from a PGD to get to the PUD page */
#घोषणा PGD_MASKED_BITS		0

#घोषणा USER_PTRS_PER_PGD	(TASK_SIZE / PGसूची_SIZE)
#घोषणा FIRST_USER_ADDRESS	0UL

#घोषणा pte_ERROR(e) \
	pr_err("%s:%d: bad pte %llx.\n", __खाता__, __LINE__, \
		(अचिन्हित दीर्घ दीर्घ)pte_val(e))
#घोषणा pgd_ERROR(e) \
	pr_err("%s:%d: bad pgd %08lx.\n", __खाता__, __LINE__, pgd_val(e))

#अगर_अघोषित __ASSEMBLY__

पूर्णांक map_kernel_page(अचिन्हित दीर्घ va, phys_addr_t pa, pgprot_t prot);

#पूर्ण_अगर /* !__ASSEMBLY__ */


/*
 * This is the bottom of the PKMAP area with HIGHMEM or an arbitrary
 * value (क्रम now) on others, from where we can start layout kernel
 * भव space that goes below PKMAP and FIXMAP
 */
#समावेश <यंत्र/fixmap.h>

/*
 * ioremap_bot starts at that address. Early ioremaps move करोwn from there,
 * until mem_init() at which poपूर्णांक this becomes the top of the vदो_स्मृति
 * and ioremap space
 */
#अगर_घोषित CONFIG_HIGHMEM
#घोषणा IOREMAP_TOP	PKMAP_BASE
#अन्यथा
#घोषणा IOREMAP_TOP	FIXADDR_START
#पूर्ण_अगर

/* PPC32 shares vदो_स्मृति area with ioremap */
#घोषणा IOREMAP_START	VMALLOC_START
#घोषणा IOREMAP_END	VMALLOC_END

/*
 * Just any arbitrary offset to the start of the vदो_स्मृति VM area: the
 * current 16MB value just means that there will be a 64MB "hole" after the
 * physical memory until the kernel भव memory starts.  That means that
 * any out-of-bounds memory accesses will hopefully be caught.
 * The vदो_स्मृति() routines leaves a hole of 4kB between each vदो_स्मृतिed
 * area क्रम the same reason. ;)
 *
 * We no दीर्घer map larger than phys RAM with the BATs so we करोn't have
 * to worry about the VMALLOC_OFFSET causing problems.  We करो have to worry
 * about clashes between our early calls to ioremap() that start growing करोwn
 * from IOREMAP_TOP being run पूर्णांकo the VM area allocations (growing upwards
 * from VMALLOC_START).  For this reason we have ioremap_bot to check when
 * we actually run पूर्णांकo our mappings setup in the early boot with the VM
 * प्रणाली.  This really करोes become a problem क्रम machines with good amounts
 * of RAM.  -- Cort
 */
#घोषणा VMALLOC_OFFSET (0x1000000) /* 16M */
#अगर_घोषित PPC_PIN_SIZE
#घोषणा VMALLOC_START (((ALIGN((दीर्घ)high_memory, PPC_PIN_SIZE) + VMALLOC_OFFSET) & ~(VMALLOC_OFFSET-1)))
#अन्यथा
#घोषणा VMALLOC_START ((((दीर्घ)high_memory + VMALLOC_OFFSET) & ~(VMALLOC_OFFSET-1)))
#पूर्ण_अगर

#अगर_घोषित CONFIG_KASAN_VMALLOC
#घोषणा VMALLOC_END	ALIGN_DOWN(ioremap_bot, PAGE_SIZE << KASAN_SHADOW_SCALE_SHIFT)
#अन्यथा
#घोषणा VMALLOC_END	ioremap_bot
#पूर्ण_अगर

/*
 * Bits in a linux-style PTE.  These match the bits in the
 * (hardware-defined) PowerPC PTE as बंदly as possible.
 */

#अगर defined(CONFIG_40x)
#समावेश <यंत्र/nohash/32/pte-40x.h>
#या_अगर defined(CONFIG_44x)
#समावेश <यंत्र/nohash/32/pte-44x.h>
#या_अगर defined(CONFIG_FSL_BOOKE) && defined(CONFIG_PTE_64BIT)
#समावेश <यंत्र/nohash/pte-book3e.h>
#या_अगर defined(CONFIG_FSL_BOOKE)
#समावेश <यंत्र/nohash/32/pte-fsl-booke.h>
#या_अगर defined(CONFIG_PPC_8xx)
#समावेश <यंत्र/nohash/32/pte-8xx.h>
#पूर्ण_अगर

/*
 * Location of the PFN in the PTE. Most 32-bit platक्रमms use the same
 * as _PAGE_SHIFT here (ie, naturally aligned).
 * Platक्रमm who करोn't just pre-define the value so we don't override it here.
 */
#अगर_अघोषित PTE_RPN_SHIFT
#घोषणा PTE_RPN_SHIFT	(PAGE_SHIFT)
#पूर्ण_अगर

/*
 * The mask covered by the RPN must be a ULL on 32-bit platक्रमms with
 * 64-bit PTEs.
 */
#अगर defined(CONFIG_PPC32) && defined(CONFIG_PTE_64BIT)
#घोषणा PTE_RPN_MASK	(~((1ULL << PTE_RPN_SHIFT) - 1))
#घोषणा MAX_POSSIBLE_PHYSMEM_BITS 36
#अन्यथा
#घोषणा PTE_RPN_MASK	(~((1UL << PTE_RPN_SHIFT) - 1))
#घोषणा MAX_POSSIBLE_PHYSMEM_BITS 32
#पूर्ण_अगर

/*
 * _PAGE_CHG_MASK masks of bits that are to be preserved across
 * pgprot changes.
 */
#घोषणा _PAGE_CHG_MASK	(PTE_RPN_MASK | _PAGE_सूचीTY | _PAGE_ACCESSED | _PAGE_SPECIAL)

#अगर_अघोषित __ASSEMBLY__

#घोषणा pte_clear(mm, addr, ptep) \
	करो अणु pte_update(mm, addr, ptep, ~0, 0, 0); पूर्ण जबतक (0)

#अगर_अघोषित pte_mkग_लिखो
अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_RW);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_सूचीTY);
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_ACCESSED);
पूर्ण

#अगर_अघोषित pte_wrprotect
अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~_PAGE_RW);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत pte_t pte_mkexec(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_EXEC);
पूर्ण

#घोषणा pmd_none(pmd)		(!pmd_val(pmd))
#घोषणा	pmd_bad(pmd)		(pmd_val(pmd) & _PMD_BAD)
#घोषणा	pmd_present(pmd)	(pmd_val(pmd) & _PMD_PRESENT_MASK)
अटल अंतरभूत व्योम pmd_clear(pmd_t *pmdp)
अणु
	*pmdp = __pmd(0);
पूर्ण

/*
 * PTE updates. This function is called whenever an existing
 * valid PTE is updated. This करोes -not- include set_pte_at()
 * which nowadays only sets a new PTE.
 *
 * Depending on the type of MMU, we may need to use atomic updates
 * and the PTE may be either 32 or 64 bit wide. In the later हाल,
 * when using atomic updates, only the low part of the PTE is
 * accessed atomically.
 *
 * In addition, on 44x, we also मुख्यtain a global flag indicating
 * that an executable user mapping was modअगरied, which is needed
 * to properly flush the भवly tagged inकाष्ठाion cache of
 * those implementations.
 *
 * On the 8xx, the page tables are a bit special. For 16k pages, we have
 * 4 identical entries. For 512k pages, we have 128 entries as अगर it was
 * 4k pages, but they are flagged as 512k pages क्रम the hardware.
 * For other page sizes, we have a single entry in the table.
 */
#अगर_घोषित CONFIG_PPC_8xx
अटल pmd_t *pmd_off(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);
अटल पूर्णांक hugepd_ok(hugepd_t hpd);

अटल पूर्णांक number_of_cells_per_pte(pmd_t *pmd, pte_basic_t val, पूर्णांक huge)
अणु
	अगर (!huge)
		वापस PAGE_SIZE / SZ_4K;
	अन्यथा अगर (hugepd_ok(*((hugepd_t *)pmd)))
		वापस 1;
	अन्यथा अगर (IS_ENABLED(CONFIG_PPC_4K_PAGES) && !(val & _PAGE_HUGE))
		वापस SZ_16K / SZ_4K;
	अन्यथा
		वापस SZ_512K / SZ_4K;
पूर्ण

अटल अंतरभूत pte_basic_t pte_update(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *p,
				     अचिन्हित दीर्घ clr, अचिन्हित दीर्घ set, पूर्णांक huge)
अणु
	pte_basic_t *entry = &p->pte;
	pte_basic_t old = pte_val(*p);
	pte_basic_t new = (old & ~(pte_basic_t)clr) | set;
	पूर्णांक num, i;
	pmd_t *pmd = pmd_off(mm, addr);

	num = number_of_cells_per_pte(pmd, new, huge);

	क्रम (i = 0; i < num; i++, entry++, new += SZ_4K)
		*entry = new;

	वापस old;
पूर्ण

#अगर_घोषित CONFIG_PPC_16K_PAGES
#घोषणा __HAVE_ARCH_PTEP_GET
अटल अंतरभूत pte_t ptep_get(pte_t *ptep)
अणु
	pte_basic_t val = READ_ONCE(ptep->pte);
	pte_t pte = अणुval, val, val, valपूर्ण;

	वापस pte;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_16K_PAGES */

#अन्यथा
अटल अंतरभूत pte_basic_t pte_update(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *p,
				     अचिन्हित दीर्घ clr, अचिन्हित दीर्घ set, पूर्णांक huge)
अणु
	pte_basic_t old = pte_val(*p);
	pte_basic_t new = (old & ~(pte_basic_t)clr) | set;

	*p = __pte(new);

#अगर_घोषित CONFIG_44x
	अगर ((old & _PAGE_USER) && (old & _PAGE_EXEC))
		icache_44x_need_flush = 1;
#पूर्ण_अगर
	वापस old;
पूर्ण
#पूर्ण_अगर

#घोषणा __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
अटल अंतरभूत पूर्णांक __ptep_test_and_clear_young(काष्ठा mm_काष्ठा *mm,
					      अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	अचिन्हित दीर्घ old;
	old = pte_update(mm, addr, ptep, _PAGE_ACCESSED, 0, 0);
	वापस (old & _PAGE_ACCESSED) != 0;
पूर्ण
#घोषणा ptep_test_and_clear_young(__vma, __addr, __ptep) \
	__ptep_test_and_clear_young((__vma)->vm_mm, __addr, __ptep)

#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR
अटल अंतरभूत pte_t ptep_get_and_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				       pte_t *ptep)
अणु
	वापस __pte(pte_update(mm, addr, ptep, ~0, 0, 0));
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_SET_WRPROTECT
अटल अंतरभूत व्योम ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				      pte_t *ptep)
अणु
	अचिन्हित दीर्घ clr = ~pte_val(pte_wrprotect(__pte(~0)));
	अचिन्हित दीर्घ set = pte_val(pte_wrprotect(__pte(0)));

	pte_update(mm, addr, ptep, clr, set, 0);
पूर्ण

अटल अंतरभूत व्योम __ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					   pte_t *ptep, pte_t entry,
					   अचिन्हित दीर्घ address,
					   पूर्णांक psize)
अणु
	pte_t pte_set = pte_mkyoung(pte_सूची_गढ़ोty(pte_mkग_लिखो(pte_mkexec(__pte(0)))));
	pte_t pte_clr = pte_mkyoung(pte_सूची_गढ़ोty(pte_mkग_लिखो(pte_mkexec(__pte(~0)))));
	अचिन्हित दीर्घ set = pte_val(entry) & pte_val(pte_set);
	अचिन्हित दीर्घ clr = ~pte_val(entry) & ~pte_val(pte_clr);
	पूर्णांक huge = psize > mmu_भव_psize ? 1 : 0;

	pte_update(vma->vm_mm, address, ptep, clr, set, huge);

	flush_tlb_page(vma, address);
पूर्ण

अटल अंतरभूत पूर्णांक pte_young(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_ACCESSED;
पूर्ण

#घोषणा __HAVE_ARCH_PTE_SAME
#घोषणा pte_same(A,B)	((pte_val(A) ^ pte_val(B)) == 0)

/*
 * Note that on Book E processors, the pmd contains the kernel भव
 * (lowmem) address of the pte page.  The physical address is less useful
 * because everything runs with translation enabled (even the TLB miss
 * handler).  On everything अन्यथा the pmd contains the physical address
 * of the pte page.  -- paulus
 */
#अगर_अघोषित CONFIG_BOOKE
#घोषणा pmd_page(pmd)		\
	pfn_to_page(pmd_val(pmd) >> PAGE_SHIFT)
#अन्यथा
#घोषणा pmd_page_vaddr(pmd)	\
	((अचिन्हित दीर्घ)(pmd_val(pmd) & ~(PTE_TABLE_SIZE - 1)))
#घोषणा pmd_page(pmd)		\
	pfn_to_page((__pa(pmd_val(pmd)) >> PAGE_SHIFT))
#पूर्ण_अगर

/*
 * Encode and decode a swap entry.
 * Note that the bits we use in a PTE क्रम representing a swap entry
 * must not include the _PAGE_PRESENT bit.
 *   -- paulus
 */
#घोषणा __swp_type(entry)		((entry).val & 0x1f)
#घोषणा __swp_offset(entry)		((entry).val >> 5)
#घोषणा __swp_entry(type, offset)	((swp_entry_t) अणु (type) | ((offset) << 5) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु pte_val(pte) >> 3 पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु (x).val << 3 पूर्ण)

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_POWERPC_NOHASH_32_PGTABLE_H */
