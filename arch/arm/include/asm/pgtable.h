<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/pgtable.h
 *
 *  Copyright (C) 1995-2002 Russell King
 */
#अगर_अघोषित _ASMARM_PGTABLE_H
#घोषणा _ASMARM_PGTABLE_H

#समावेश <linux/स्थिर.h>
#समावेश <यंत्र/proc-fns.h>

#अगर_अघोषित CONFIG_MMU

#समावेश <यंत्र-generic/pgtable-nopud.h>
#समावेश <यंत्र/pgtable-nommu.h>

#अन्यथा

#समावेश <यंत्र-generic/pgtable-nopud.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/pgtable-hwdef.h>


#समावेश <यंत्र/tlbflush.h>

#अगर_घोषित CONFIG_ARM_LPAE
#समावेश <यंत्र/pgtable-3level.h>
#अन्यथा
#समावेश <यंत्र/pgtable-2level.h>
#पूर्ण_अगर

/*
 * Just any arbitrary offset to the start of the vदो_स्मृति VM area: the
 * current 8MB value just means that there will be a 8MB "hole" after the
 * physical memory until the kernel भव memory starts.  That means that
 * any out-of-bounds memory accesses will hopefully be caught.
 * The vदो_स्मृति() routines leaves a hole of 4kB between each vदो_स्मृतिed
 * area क्रम the same reason. ;)
 */
#घोषणा VMALLOC_OFFSET		(8*1024*1024)
#घोषणा VMALLOC_START		(((अचिन्हित दीर्घ)high_memory + VMALLOC_OFFSET) & ~(VMALLOC_OFFSET-1))
#घोषणा VMALLOC_END		0xff800000UL

#घोषणा LIBRARY_TEXT_START	0x0c000000

#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम __pte_error(स्थिर अक्षर *file, पूर्णांक line, pte_t);
बाह्य व्योम __pmd_error(स्थिर अक्षर *file, पूर्णांक line, pmd_t);
बाह्य व्योम __pgd_error(स्थिर अक्षर *file, पूर्णांक line, pgd_t);

#घोषणा pte_ERROR(pte)		__pte_error(__खाता__, __LINE__, pte)
#घोषणा pmd_ERROR(pmd)		__pmd_error(__खाता__, __LINE__, pmd)
#घोषणा pgd_ERROR(pgd)		__pgd_error(__खाता__, __LINE__, pgd)

/*
 * This is the lowest भव address we can permit any user space
 * mapping to be mapped at.  This is particularly important क्रम
 * non-high vector CPUs.
 */
#घोषणा FIRST_USER_ADDRESS	(PAGE_SIZE * 2)

/*
 * Use TASK_SIZE as the उच्चमानing argument क्रम मुक्त_pgtables() and
 * मुक्त_pgd_range() to aव्योम मुक्तing the modules pmd when LPAE is enabled (pmd
 * page shared between user and kernel).
 */
#अगर_घोषित CONFIG_ARM_LPAE
#घोषणा USER_PGTABLES_CEILING	TASK_SIZE
#पूर्ण_अगर

/*
 * The pgprot_* and protection_map entries will be fixed up in runसमय
 * to include the cachable and bufferable bits based on memory policy,
 * as well as any architecture dependent bits like global/ASID and SMP
 * shared mapping bits.
 */
#घोषणा _L_PTE_DEFAULT	L_PTE_PRESENT | L_PTE_YOUNG

बाह्य pgprot_t		pgprot_user;
बाह्य pgprot_t		pgprot_kernel;

#घोषणा _MOD_PROT(p, b)	__pgprot(pgprot_val(p) | (b))

#घोषणा PAGE_NONE		_MOD_PROT(pgprot_user, L_PTE_XN | L_PTE_RDONLY | L_PTE_NONE)
#घोषणा PAGE_SHARED		_MOD_PROT(pgprot_user, L_PTE_USER | L_PTE_XN)
#घोषणा PAGE_SHARED_EXEC	_MOD_PROT(pgprot_user, L_PTE_USER)
#घोषणा PAGE_COPY		_MOD_PROT(pgprot_user, L_PTE_USER | L_PTE_RDONLY | L_PTE_XN)
#घोषणा PAGE_COPY_EXEC		_MOD_PROT(pgprot_user, L_PTE_USER | L_PTE_RDONLY)
#घोषणा PAGE_READONLY		_MOD_PROT(pgprot_user, L_PTE_USER | L_PTE_RDONLY | L_PTE_XN)
#घोषणा PAGE_READONLY_EXEC	_MOD_PROT(pgprot_user, L_PTE_USER | L_PTE_RDONLY)
#घोषणा PAGE_KERNEL		_MOD_PROT(pgprot_kernel, L_PTE_XN)
#घोषणा PAGE_KERNEL_EXEC	pgprot_kernel

#घोषणा __PAGE_NONE		__pgprot(_L_PTE_DEFAULT | L_PTE_RDONLY | L_PTE_XN | L_PTE_NONE)
#घोषणा __PAGE_SHARED		__pgprot(_L_PTE_DEFAULT | L_PTE_USER | L_PTE_XN)
#घोषणा __PAGE_SHARED_EXEC	__pgprot(_L_PTE_DEFAULT | L_PTE_USER)
#घोषणा __PAGE_COPY		__pgprot(_L_PTE_DEFAULT | L_PTE_USER | L_PTE_RDONLY | L_PTE_XN)
#घोषणा __PAGE_COPY_EXEC	__pgprot(_L_PTE_DEFAULT | L_PTE_USER | L_PTE_RDONLY)
#घोषणा __PAGE_READONLY		__pgprot(_L_PTE_DEFAULT | L_PTE_USER | L_PTE_RDONLY | L_PTE_XN)
#घोषणा __PAGE_READONLY_EXEC	__pgprot(_L_PTE_DEFAULT | L_PTE_USER | L_PTE_RDONLY)

#घोषणा __pgprot_modअगरy(prot,mask,bits)		\
	__pgprot((pgprot_val(prot) & ~(mask)) | (bits))

#घोषणा pgprot_noncached(prot) \
	__pgprot_modअगरy(prot, L_PTE_MT_MASK, L_PTE_MT_UNCACHED)

#घोषणा pgprot_ग_लिखोcombine(prot) \
	__pgprot_modअगरy(prot, L_PTE_MT_MASK, L_PTE_MT_BUFFERABLE)

#घोषणा pgprot_stronglyordered(prot) \
	__pgprot_modअगरy(prot, L_PTE_MT_MASK, L_PTE_MT_UNCACHED)

#घोषणा pgprot_device(prot) \
	__pgprot_modअगरy(prot, L_PTE_MT_MASK, L_PTE_MT_DEV_SHARED | L_PTE_SHARED | L_PTE_सूचीTY | L_PTE_XN)

#अगर_घोषित CONFIG_ARM_DMA_MEM_BUFFERABLE
#घोषणा pgprot_dmacoherent(prot) \
	__pgprot_modअगरy(prot, L_PTE_MT_MASK, L_PTE_MT_BUFFERABLE | L_PTE_XN)
#घोषणा __HAVE_PHYS_MEM_ACCESS_PROT
काष्ठा file;
बाह्य pgprot_t phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn,
				     अचिन्हित दीर्घ size, pgprot_t vma_prot);
#अन्यथा
#घोषणा pgprot_dmacoherent(prot) \
	__pgprot_modअगरy(prot, L_PTE_MT_MASK, L_PTE_MT_UNCACHED | L_PTE_XN)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * The table below defines the page protection levels that we insert पूर्णांकo our
 * Linux page table version.  These get translated पूर्णांकo the best that the
 * architecture can perक्रमm.  Note that on most ARM hardware:
 *  1) We cannot करो execute protection
 *  2) If we could करो execute protection, then पढ़ो is implied
 *  3) ग_लिखो implies पढ़ो permissions
 */
#घोषणा __P000  __PAGE_NONE
#घोषणा __P001  __PAGE_READONLY
#घोषणा __P010  __PAGE_COPY
#घोषणा __P011  __PAGE_COPY
#घोषणा __P100  __PAGE_READONLY_EXEC
#घोषणा __P101  __PAGE_READONLY_EXEC
#घोषणा __P110  __PAGE_COPY_EXEC
#घोषणा __P111  __PAGE_COPY_EXEC

#घोषणा __S000  __PAGE_NONE
#घोषणा __S001  __PAGE_READONLY
#घोषणा __S010  __PAGE_SHARED
#घोषणा __S011  __PAGE_SHARED
#घोषणा __S100  __PAGE_READONLY_EXEC
#घोषणा __S101  __PAGE_READONLY_EXEC
#घोषणा __S110  __PAGE_SHARED_EXEC
#घोषणा __S111  __PAGE_SHARED_EXEC

#अगर_अघोषित __ASSEMBLY__
/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
बाह्य काष्ठा page *empty_zero_page;
#घोषणा ZERO_PAGE(vaddr)	(empty_zero_page)


बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD];

#घोषणा pud_page(pud)		pmd_page(__pmd(pud_val(pud)))
#घोषणा pud_ग_लिखो(pud)		pmd_ग_लिखो(__pmd(pud_val(pud)))

#घोषणा pmd_none(pmd)		(!pmd_val(pmd))

अटल अंतरभूत pte_t *pmd_page_vaddr(pmd_t pmd)
अणु
	वापस __va(pmd_val(pmd) & PHYS_MASK & (s32)PAGE_MASK);
पूर्ण

#घोषणा pmd_page(pmd)		pfn_to_page(__phys_to_pfn(pmd_val(pmd) & PHYS_MASK))

#घोषणा pte_pfn(pte)		((pte_val(pte) & PHYS_MASK) >> PAGE_SHIFT)
#घोषणा pfn_pte(pfn,prot)	__pte(__pfn_to_phys(pfn) | pgprot_val(prot))

#घोषणा pte_page(pte)		pfn_to_page(pte_pfn(pte))
#घोषणा mk_pte(page,prot)	pfn_pte(page_to_pfn(page), prot)

#घोषणा pte_clear(mm,addr,ptep)	set_pte_ext(ptep, __pte(0), 0)

#घोषणा pte_isset(pte, val)	((u32)(val) == (val) ? pte_val(pte) & (val) \
						: !!(pte_val(pte) & (val)))
#घोषणा pte_isclear(pte, val)	(!(pte_val(pte) & (val)))

#घोषणा pte_none(pte)		(!pte_val(pte))
#घोषणा pte_present(pte)	(pte_isset((pte), L_PTE_PRESENT))
#घोषणा pte_valid(pte)		(pte_isset((pte), L_PTE_VALID))
#घोषणा pte_accessible(mm, pte)	(mm_tlb_flush_pending(mm) ? pte_present(pte) : pte_valid(pte))
#घोषणा pte_ग_लिखो(pte)		(pte_isclear((pte), L_PTE_RDONLY))
#घोषणा pte_dirty(pte)		(pte_isset((pte), L_PTE_सूचीTY))
#घोषणा pte_young(pte)		(pte_isset((pte), L_PTE_YOUNG))
#घोषणा pte_exec(pte)		(pte_isclear((pte), L_PTE_XN))

#घोषणा pte_valid_user(pte)	\
	(pte_valid(pte) && pte_isset((pte), L_PTE_USER) && pte_young(pte))

अटल अंतरभूत bool pte_access_permitted(pte_t pte, bool ग_लिखो)
अणु
	pteval_t mask = L_PTE_PRESENT | L_PTE_USER;
	pteval_t needed = mask;

	अगर (ग_लिखो)
		mask |= L_PTE_RDONLY;

	वापस (pte_val(pte) & mask) == needed;
पूर्ण
#घोषणा pte_access_permitted pte_access_permitted

#अगर __LINUX_ARM_ARCH__ < 6
अटल अंतरभूत व्योम __sync_icache_dcache(pte_t pteval)
अणु
पूर्ण
#अन्यथा
बाह्य व्योम __sync_icache_dcache(pte_t pteval);
#पूर्ण_अगर

व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		      pte_t *ptep, pte_t pteval);

अटल अंतरभूत pte_t clear_pte_bit(pte_t pte, pgprot_t prot)
अणु
	pte_val(pte) &= ~pgprot_val(prot);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t set_pte_bit(pte_t pte, pgprot_t prot)
अणु
	pte_val(pte) |= pgprot_val(prot);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	वापस set_pte_bit(pte, __pgprot(L_PTE_RDONLY));
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	वापस clear_pte_bit(pte, __pgprot(L_PTE_RDONLY));
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	वापस clear_pte_bit(pte, __pgprot(L_PTE_सूचीTY));
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	वापस set_pte_bit(pte, __pgprot(L_PTE_सूचीTY));
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	वापस clear_pte_bit(pte, __pgprot(L_PTE_YOUNG));
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	वापस set_pte_bit(pte, __pgprot(L_PTE_YOUNG));
पूर्ण

अटल अंतरभूत pte_t pte_mkexec(pte_t pte)
अणु
	वापस clear_pte_bit(pte, __pgprot(L_PTE_XN));
पूर्ण

अटल अंतरभूत pte_t pte_mknexec(pte_t pte)
अणु
	वापस set_pte_bit(pte, __pgprot(L_PTE_XN));
पूर्ण

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	स्थिर pteval_t mask = L_PTE_XN | L_PTE_RDONLY | L_PTE_USER |
		L_PTE_NONE | L_PTE_VALID;
	pte_val(pte) = (pte_val(pte) & ~mask) | (pgprot_val(newprot) & mask);
	वापस pte;
पूर्ण

/*
 * Encode and decode a swap entry.  Swap entries are stored in the Linux
 * page tables as follows:
 *
 *   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *   <--------------- offset ------------------------> < type -> 0 0
 *
 * This gives us up to 31 swap files and 128GB per swap file.  Note that
 * the offset field is always non-zero.
 */
#घोषणा __SWP_TYPE_SHIFT	2
#घोषणा __SWP_TYPE_BITS		5
#घोषणा __SWP_TYPE_MASK		((1 << __SWP_TYPE_BITS) - 1)
#घोषणा __SWP_OFFSET_SHIFT	(__SWP_TYPE_BITS + __SWP_TYPE_SHIFT)

#घोषणा __swp_type(x)		(((x).val >> __SWP_TYPE_SHIFT) & __SWP_TYPE_MASK)
#घोषणा __swp_offset(x)		((x).val >> __SWP_OFFSET_SHIFT)
#घोषणा __swp_entry(type,offset) ((swp_entry_t) अणु ((type) << __SWP_TYPE_SHIFT) | ((offset) << __SWP_OFFSET_SHIFT) पूर्ण)

#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(swp)	((pte_t) अणु (swp).val पूर्ण)

/*
 * It is an error क्रम the kernel to have more swap files than we can
 * encode in the PTEs.  This ensures that we know when MAX_SWAPखाताS
 * is increased beyond what we presently support.
 */
#घोषणा MAX_SWAPखाताS_CHECK() BUILD_BUG_ON(MAX_SWAPखाताS_SHIFT > __SWP_TYPE_BITS)

/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
/* FIXME: this is not correct */
#घोषणा kern_addr_valid(addr)	(1)

/*
 * We provide our own arch_get_unmapped_area to cope with VIPT caches.
 */
#घोषणा HAVE_ARCH_UNMAPPED_AREA
#घोषणा HAVE_ARCH_UNMAPPED_AREA_TOPDOWN

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* CONFIG_MMU */

#पूर्ण_अगर /* _ASMARM_PGTABLE_H */
