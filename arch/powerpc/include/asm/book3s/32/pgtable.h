<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_32_PGTABLE_H
#घोषणा _ASM_POWERPC_BOOK3S_32_PGTABLE_H

#समावेश <यंत्र-generic/pgtable-nopmd.h>

#समावेश <यंत्र/book3s/32/hash.h>

/* And here we include common definitions */

#घोषणा _PAGE_KERNEL_RO		0
#घोषणा _PAGE_KERNEL_ROX	(_PAGE_EXEC)
#घोषणा _PAGE_KERNEL_RW		(_PAGE_सूचीTY | _PAGE_RW)
#घोषणा _PAGE_KERNEL_RWX	(_PAGE_सूचीTY | _PAGE_RW | _PAGE_EXEC)

#घोषणा _PAGE_HPTEFLAGS _PAGE_HASHPTE

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत bool pte_user(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_USER;
पूर्ण
#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * Location of the PFN in the PTE. Most 32-bit platक्रमms use the same
 * as _PAGE_SHIFT here (ie, naturally aligned).
 * Platक्रमm who करोn't just pre-define the value so we don't override it here.
 */
#घोषणा PTE_RPN_SHIFT	(PAGE_SHIFT)

/*
 * The mask covered by the RPN must be a ULL on 32-bit platक्रमms with
 * 64-bit PTEs.
 */
#अगर_घोषित CONFIG_PTE_64BIT
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
#घोषणा _PAGE_CHG_MASK	(PTE_RPN_MASK | _PAGE_HASHPTE | _PAGE_सूचीTY | \
			 _PAGE_ACCESSED | _PAGE_SPECIAL)

/*
 * We define 2 sets of base prot bits, one क्रम basic pages (ie,
 * cacheable kernel and user pages) and one क्रम non cacheable
 * pages. We always set _PAGE_COHERENT when SMP is enabled or
 * the processor might need it क्रम DMA coherency.
 */
#घोषणा _PAGE_BASE_NC	(_PAGE_PRESENT | _PAGE_ACCESSED)
#घोषणा _PAGE_BASE	(_PAGE_BASE_NC | _PAGE_COHERENT)

/*
 * Permission masks used to generate the __P and __S table.
 *
 * Note:__pgprot is defined in arch/घातerpc/include/यंत्र/page.h
 *
 * Write permissions imply पढ़ो permissions क्रम now.
 */
#घोषणा PAGE_NONE	__pgprot(_PAGE_BASE)
#घोषणा PAGE_SHARED	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_RW)
#घोषणा PAGE_SHARED_X	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_RW | _PAGE_EXEC)
#घोषणा PAGE_COPY	__pgprot(_PAGE_BASE | _PAGE_USER)
#घोषणा PAGE_COPY_X	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_EXEC)
#घोषणा PAGE_READONLY	__pgprot(_PAGE_BASE | _PAGE_USER)
#घोषणा PAGE_READONLY_X	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_EXEC)

/* Permission masks used क्रम kernel mappings */
#घोषणा PAGE_KERNEL	__pgprot(_PAGE_BASE | _PAGE_KERNEL_RW)
#घोषणा PAGE_KERNEL_NC	__pgprot(_PAGE_BASE_NC | _PAGE_KERNEL_RW | _PAGE_NO_CACHE)
#घोषणा PAGE_KERNEL_NCG	__pgprot(_PAGE_BASE_NC | _PAGE_KERNEL_RW | \
				 _PAGE_NO_CACHE | _PAGE_GUARDED)
#घोषणा PAGE_KERNEL_X	__pgprot(_PAGE_BASE | _PAGE_KERNEL_RWX)
#घोषणा PAGE_KERNEL_RO	__pgprot(_PAGE_BASE | _PAGE_KERNEL_RO)
#घोषणा PAGE_KERNEL_ROX	__pgprot(_PAGE_BASE | _PAGE_KERNEL_ROX)

/*
 * Protection used क्रम kernel text. We want the debuggers to be able to
 * set अवरोधpoपूर्णांकs anywhere, so करोn't ग_लिखो protect the kernel text
 * on platक्रमms where such control is possible.
 */
#अगर defined(CONFIG_KGDB) || defined(CONFIG_XMON) || defined(CONFIG_BDI_SWITCH) ||\
	defined(CONFIG_KPROBES) || defined(CONFIG_DYNAMIC_FTRACE)
#घोषणा PAGE_KERNEL_TEXT	PAGE_KERNEL_X
#अन्यथा
#घोषणा PAGE_KERNEL_TEXT	PAGE_KERNEL_ROX
#पूर्ण_अगर

/* Make modules code happy. We करोn't set RO yet */
#घोषणा PAGE_KERNEL_EXEC	PAGE_KERNEL_X

/* Advertise special mapping type क्रम AGP */
#घोषणा PAGE_AGP		(PAGE_KERNEL_NC)
#घोषणा HAVE_PAGE_AGP

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

/* Bits to mask out from a PMD to get to the PTE page */
#घोषणा PMD_MASKED_BITS		(PTE_TABLE_SIZE - 1)
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

#घोषणा USER_PTRS_PER_PGD	(TASK_SIZE / PGसूची_SIZE)

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
 * from ioremap_base being run पूर्णांकo the VM area allocations (growing upwards
 * from VMALLOC_START).  For this reason we have ioremap_bot to check when
 * we actually run पूर्णांकo our mappings setup in the early boot with the VM
 * प्रणाली.  This really करोes become a problem क्रम machines with good amounts
 * of RAM.  -- Cort
 */
#घोषणा VMALLOC_OFFSET (0x1000000) /* 16M */

#घोषणा VMALLOC_START ((((दीर्घ)high_memory + VMALLOC_OFFSET) & ~(VMALLOC_OFFSET-1)))

#अगर_घोषित CONFIG_KASAN_VMALLOC
#घोषणा VMALLOC_END	ALIGN_DOWN(ioremap_bot, PAGE_SIZE << KASAN_SHADOW_SCALE_SHIFT)
#अन्यथा
#घोषणा VMALLOC_END	ioremap_bot
#पूर्ण_अगर

#घोषणा MODULES_END	ALIGN_DOWN(PAGE_OFFSET, SZ_256M)
#घोषणा MODULES_VADDR	(MODULES_END - SZ_256M)

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/sched.h>
#समावेश <linux/thपढ़ोs.h>

/* Bits to mask out from a PGD to get to the PUD page */
#घोषणा PGD_MASKED_BITS		0

#घोषणा pte_ERROR(e) \
	pr_err("%s:%d: bad pte %llx.\n", __खाता__, __LINE__, \
		(अचिन्हित दीर्घ दीर्घ)pte_val(e))
#घोषणा pgd_ERROR(e) \
	pr_err("%s:%d: bad pgd %08lx.\n", __खाता__, __LINE__, pgd_val(e))
/*
 * Bits in a linux-style PTE.  These match the bits in the
 * (hardware-defined) PowerPC PTE as बंदly as possible.
 */

#घोषणा pte_clear(mm, addr, ptep) \
	करो अणु pte_update(mm, addr, ptep, ~_PAGE_HASHPTE, 0, 0); पूर्ण जबतक (0)

#घोषणा pmd_none(pmd)		(!pmd_val(pmd))
#घोषणा	pmd_bad(pmd)		(pmd_val(pmd) & _PMD_BAD)
#घोषणा	pmd_present(pmd)	(pmd_val(pmd) & _PMD_PRESENT_MASK)
अटल अंतरभूत व्योम pmd_clear(pmd_t *pmdp)
अणु
	*pmdp = __pmd(0);
पूर्ण


/*
 * When flushing the tlb entry क्रम a page, we also need to flush the hash
 * table entry.  flush_hash_pages is assembler (क्रम speed) in hashtable.S.
 */
बाह्य पूर्णांक flush_hash_pages(अचिन्हित context, अचिन्हित दीर्घ va,
			    अचिन्हित दीर्घ pmdval, पूर्णांक count);

/* Add an HPTE to the hash table */
बाह्य व्योम add_hash_page(अचिन्हित context, अचिन्हित दीर्घ va,
			  अचिन्हित दीर्घ pmdval);

/* Flush an entry from the TLB/hash table */
अटल अंतरभूत व्योम flush_hash_entry(काष्ठा mm_काष्ठा *mm, pte_t *ptep, अचिन्हित दीर्घ addr)
अणु
	अगर (mmu_has_feature(MMU_FTR_HPTE_TABLE)) अणु
		अचिन्हित दीर्घ ptephys = __pa(ptep) & PAGE_MASK;

		flush_hash_pages(mm->context.id, addr, ptephys, 1);
	पूर्ण
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
 */
अटल अंतरभूत pte_basic_t pte_update(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *p,
				     अचिन्हित दीर्घ clr, अचिन्हित दीर्घ set, पूर्णांक huge)
अणु
	pte_basic_t old;
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
#अगर_अघोषित CONFIG_PTE_64BIT
"1:	lwarx	%0, 0, %3\n"
"	andc	%1, %0, %4\n"
#अन्यथा
"1:	lwarx	%L0, 0, %3\n"
"	lwz	%0, -4(%3)\n"
"	andc	%1, %L0, %4\n"
#पूर्ण_अगर
"	or	%1, %1, %5\n"
"	stwcx.	%1, 0, %3\n"
"	bne-	1b"
	: "=&r" (old), "=&r" (पंचांगp), "=m" (*p)
#अगर_अघोषित CONFIG_PTE_64BIT
	: "r" (p),
#अन्यथा
	: "b" ((अचिन्हित दीर्घ)(p) + 4),
#पूर्ण_अगर
	  "r" (clr), "r" (set), "m" (*p)
	: "cc" );

	वापस old;
पूर्ण

/*
 * 2.6 calls this without flushing the TLB entry; this is wrong
 * क्रम our hash-based implementation, we fix that up here.
 */
#घोषणा __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
अटल अंतरभूत पूर्णांक __ptep_test_and_clear_young(काष्ठा mm_काष्ठा *mm,
					      अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	अचिन्हित दीर्घ old;
	old = pte_update(mm, addr, ptep, _PAGE_ACCESSED, 0, 0);
	अगर (old & _PAGE_HASHPTE)
		flush_hash_entry(mm, ptep, addr);

	वापस (old & _PAGE_ACCESSED) != 0;
पूर्ण
#घोषणा ptep_test_and_clear_young(__vma, __addr, __ptep) \
	__ptep_test_and_clear_young((__vma)->vm_mm, __addr, __ptep)

#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR
अटल अंतरभूत pte_t ptep_get_and_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				       pte_t *ptep)
अणु
	वापस __pte(pte_update(mm, addr, ptep, ~_PAGE_HASHPTE, 0, 0));
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_SET_WRPROTECT
अटल अंतरभूत व्योम ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				      pte_t *ptep)
अणु
	pte_update(mm, addr, ptep, _PAGE_RW, 0, 0);
पूर्ण

अटल अंतरभूत व्योम __ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					   pte_t *ptep, pte_t entry,
					   अचिन्हित दीर्घ address,
					   पूर्णांक psize)
अणु
	अचिन्हित दीर्घ set = pte_val(entry) &
		(_PAGE_सूचीTY | _PAGE_ACCESSED | _PAGE_RW | _PAGE_EXEC);

	pte_update(vma->vm_mm, address, ptep, 0, set, 0);

	flush_tlb_page(vma, address);
पूर्ण

#घोषणा __HAVE_ARCH_PTE_SAME
#घोषणा pte_same(A,B)	(((pte_val(A) ^ pte_val(B)) & ~_PAGE_HASHPTE) == 0)

#घोषणा pmd_page(pmd)		\
	pfn_to_page(pmd_val(pmd) >> PAGE_SHIFT)

/*
 * Encode and decode a swap entry.
 * Note that the bits we use in a PTE क्रम representing a swap entry
 * must not include the _PAGE_PRESENT bit or the _PAGE_HASHPTE bit (अगर used).
 *   -- paulus
 */
#घोषणा __swp_type(entry)		((entry).val & 0x1f)
#घोषणा __swp_offset(entry)		((entry).val >> 5)
#घोषणा __swp_entry(type, offset)	((swp_entry_t) अणु (type) | ((offset) << 5) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु pte_val(pte) >> 3 पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु (x).val << 3 पूर्ण)

/* Generic accessors to PTE bits */
अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)		अणु वापस !!(pte_val(pte) & _PAGE_RW);पूर्ण
अटल अंतरभूत पूर्णांक pte_पढ़ो(pte_t pte)		अणु वापस 1; पूर्ण
अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)		अणु वापस !!(pte_val(pte) & _PAGE_सूचीTY); पूर्ण
अटल अंतरभूत पूर्णांक pte_young(pte_t pte)		अणु वापस !!(pte_val(pte) & _PAGE_ACCESSED); पूर्ण
अटल अंतरभूत पूर्णांक pte_special(pte_t pte)	अणु वापस !!(pte_val(pte) & _PAGE_SPECIAL); पूर्ण
अटल अंतरभूत पूर्णांक pte_none(pte_t pte)		अणु वापस (pte_val(pte) & ~_PTE_NONE_MASK) == 0; पूर्ण
अटल अंतरभूत bool pte_exec(pte_t pte)		अणु वापस pte_val(pte) & _PAGE_EXEC; पूर्ण

अटल अंतरभूत पूर्णांक pte_present(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_PRESENT;
पूर्ण

अटल अंतरभूत bool pte_hw_valid(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_PRESENT;
पूर्ण

अटल अंतरभूत bool pte_hashpte(pte_t pte)
अणु
	वापस !!(pte_val(pte) & _PAGE_HASHPTE);
पूर्ण

अटल अंतरभूत bool pte_ci(pte_t pte)
अणु
	वापस !!(pte_val(pte) & _PAGE_NO_CACHE);
पूर्ण

/*
 * We only find page table entry in the last level
 * Hence no need क्रम other accessors
 */
#घोषणा pte_access_permitted pte_access_permitted
अटल अंतरभूत bool pte_access_permitted(pte_t pte, bool ग_लिखो)
अणु
	/*
	 * A पढ़ो-only access is controlled by _PAGE_USER bit.
	 * We have _PAGE_READ set क्रम WRITE and EXECUTE
	 */
	अगर (!pte_present(pte) || !pte_user(pte) || !pte_पढ़ो(pte))
		वापस false;

	अगर (ग_लिखो && !pte_ग_लिखो(pte))
		वापस false;

	वापस true;
पूर्ण

/* Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 *
 * Even अगर PTEs can be अचिन्हित दीर्घ दीर्घ, a PFN is always an अचिन्हित
 * दीर्घ क्रम now.
 */
अटल अंतरभूत pte_t pfn_pte(अचिन्हित दीर्घ pfn, pgprot_t pgprot)
अणु
	वापस __pte(((pte_basic_t)(pfn) << PTE_RPN_SHIFT) |
		     pgprot_val(pgprot));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pte_pfn(pte_t pte)
अणु
	वापस pte_val(pte) >> PTE_RPN_SHIFT;
पूर्ण

/* Generic modअगरiers क्रम PTE bits */
अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~_PAGE_RW);
पूर्ण

अटल अंतरभूत pte_t pte_exprotect(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~_PAGE_EXEC);
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~_PAGE_सूचीTY);
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~_PAGE_ACCESSED);
पूर्ण

अटल अंतरभूत pte_t pte_mkexec(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_EXEC);
पूर्ण

अटल अंतरभूत pte_t pte_mkpte(pte_t pte)
अणु
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_RW);
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_सूचीTY);
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_ACCESSED);
पूर्ण

अटल अंतरभूत pte_t pte_mkspecial(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_SPECIAL);
पूर्ण

अटल अंतरभूत pte_t pte_mkhuge(pte_t pte)
अणु
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkprivileged(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~_PAGE_USER);
पूर्ण

अटल अंतरभूत pte_t pte_mkuser(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_USER);
पूर्ण

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	वापस __pte((pte_val(pte) & _PAGE_CHG_MASK) | pgprot_val(newprot));
पूर्ण



/* This low level function perक्रमms the actual PTE insertion
 * Setting the PTE depends on the MMU type and other factors. It's
 * an horrible mess that I'm not going to try to clean up now but
 * I'm keeping it in one place rather than spपढ़ो around
 */
अटल अंतरभूत व्योम __set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				pte_t *ptep, pte_t pte, पूर्णांक percpu)
अणु
#अगर defined(CONFIG_SMP) && !defined(CONFIG_PTE_64BIT)
	/* First हाल is 32-bit Hash MMU in SMP mode with 32-bit PTEs. We use the
	 * helper pte_update() which करोes an atomic update. We need to करो that
	 * because a concurrent invalidation can clear _PAGE_HASHPTE. If it's a
	 * per-CPU PTE such as a kmap_atomic, we करो a simple update preserving
	 * the hash bits instead (ie, same as the non-SMP हाल)
	 */
	अगर (percpu)
		*ptep = __pte((pte_val(*ptep) & _PAGE_HASHPTE)
			      | (pte_val(pte) & ~_PAGE_HASHPTE));
	अन्यथा
		pte_update(mm, addr, ptep, ~_PAGE_HASHPTE, pte_val(pte), 0);

#या_अगर defined(CONFIG_PTE_64BIT)
	/* Second हाल is 32-bit with 64-bit PTE.  In this हाल, we
	 * can just store as दीर्घ as we करो the two halves in the right order
	 * with a barrier in between. This is possible because we take care,
	 * in the hash code, to pre-invalidate अगर the PTE was alपढ़ोy hashed,
	 * which synchronizes us with any concurrent invalidation.
	 * In the percpu हाल, we also fallback to the simple update preserving
	 * the hash bits
	 */
	अगर (percpu) अणु
		*ptep = __pte((pte_val(*ptep) & _PAGE_HASHPTE)
			      | (pte_val(pte) & ~_PAGE_HASHPTE));
		वापस;
	पूर्ण
	अगर (pte_val(*ptep) & _PAGE_HASHPTE)
		flush_hash_entry(mm, ptep, addr);
	__यंत्र__ __अस्थिर__("\
		stw%X0 %2,%0\न\
		eieio\न\
		stw%X1 %L2,%1"
	: "=m" (*ptep), "=m" (*((अचिन्हित अक्षर *)ptep+4))
	: "r" (pte) : "memory");

#अन्यथा
	/* Third हाल is 32-bit hash table in UP mode, we need to preserve
	 * the _PAGE_HASHPTE bit since we may not have invalidated the previous
	 * translation in the hash yet (करोne in a subsequent flush_tlb_xxx())
	 * and see we need to keep track that this PTE needs invalidating
	 */
	*ptep = __pte((pte_val(*ptep) & _PAGE_HASHPTE)
		      | (pte_val(pte) & ~_PAGE_HASHPTE));
#पूर्ण_अगर
पूर्ण

/*
 * Macro to mark a page protection value as "uncacheable".
 */

#घोषणा _PAGE_CACHE_CTL	(_PAGE_COHERENT | _PAGE_GUARDED | _PAGE_NO_CACHE | \
			 _PAGE_WRITETHRU)

#घोषणा pgprot_noncached pgprot_noncached
अटल अंतरभूत pgprot_t pgprot_noncached(pgprot_t prot)
अणु
	वापस __pgprot((pgprot_val(prot) & ~_PAGE_CACHE_CTL) |
			_PAGE_NO_CACHE | _PAGE_GUARDED);
पूर्ण

#घोषणा pgprot_noncached_wc pgprot_noncached_wc
अटल अंतरभूत pgprot_t pgprot_noncached_wc(pgprot_t prot)
अणु
	वापस __pgprot((pgprot_val(prot) & ~_PAGE_CACHE_CTL) |
			_PAGE_NO_CACHE);
पूर्ण

#घोषणा pgprot_cached pgprot_cached
अटल अंतरभूत pgprot_t pgprot_cached(pgprot_t prot)
अणु
	वापस __pgprot((pgprot_val(prot) & ~_PAGE_CACHE_CTL) |
			_PAGE_COHERENT);
पूर्ण

#घोषणा pgprot_cached_wthru pgprot_cached_wthru
अटल अंतरभूत pgprot_t pgprot_cached_wthru(pgprot_t prot)
अणु
	वापस __pgprot((pgprot_val(prot) & ~_PAGE_CACHE_CTL) |
			_PAGE_COHERENT | _PAGE_WRITETHRU);
पूर्ण

#घोषणा pgprot_cached_noncoherent pgprot_cached_noncoherent
अटल अंतरभूत pgprot_t pgprot_cached_noncoherent(pgprot_t prot)
अणु
	वापस __pgprot(pgprot_val(prot) & ~_PAGE_CACHE_CTL);
पूर्ण

#घोषणा pgprot_ग_लिखोcombine pgprot_ग_लिखोcombine
अटल अंतरभूत pgprot_t pgprot_ग_लिखोcombine(pgprot_t prot)
अणु
	वापस pgprot_noncached_wc(prot);
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /*  _ASM_POWERPC_BOOK3S_32_PGTABLE_H */
