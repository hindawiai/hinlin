<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/यंत्र-xtensa/pgtable.h
 *
 * Copyright (C) 2001 - 2013 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_PGTABLE_H
#घोषणा _XTENSA_PGTABLE_H

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/kmem_layout.h>
#समावेश <यंत्र-generic/pgtable-nopmd.h>

/*
 * We only use two ring levels, user and kernel space.
 */

#अगर_घोषित CONFIG_MMU
#घोषणा USER_RING		1	/* user ring level */
#अन्यथा
#घोषणा USER_RING		0
#पूर्ण_अगर
#घोषणा KERNEL_RING		0	/* kernel ring level */

/*
 * The Xtensa architecture port of Linux has a two-level page table प्रणाली,
 * i.e. the logical three-level Linux page table layout is folded.
 * Each task has the following memory page tables:
 *
 *   PGD table (page directory), ie. 3rd-level page table:
 *	One page (4 kB) of 1024 (PTRS_PER_PGD) poपूर्णांकers to PTE tables
 *	(Architectures that करोn't have the PMD folded poपूर्णांक to the PMD tables)
 *
 *	The poपूर्णांकer to the PGD table क्रम a given task can be retrieved from
 *	the task काष्ठाure (काष्ठा task_काष्ठा*) t, e.g. current():
 *	  (t->mm ? t->mm : t->active_mm)->pgd
 *
 *   PMD tables (page middle-directory), ie. 2nd-level page tables:
 *	Absent क्रम the Xtensa architecture (folded, PTRS_PER_PMD == 1).
 *
 *   PTE tables (page table entry), ie. 1st-level page tables:
 *	One page (4 kB) of 1024 (PTRS_PER_PTE) PTEs with a special PTE
 *	invalid_pte_table क्रम असलent mappings.
 *
 * The inभागidual pages are 4 kB big with special pages क्रम the empty_zero_page.
 */

#घोषणा PGसूची_SHIFT	22
#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/*
 * Entries per page directory level: we use two-level, so
 * we करोn't really have any PMD directory physically.
 */
#घोषणा PTRS_PER_PTE		1024
#घोषणा PTRS_PER_PTE_SHIFT	10
#घोषणा PTRS_PER_PGD		1024
#घोषणा PGD_ORDER		0
#घोषणा USER_PTRS_PER_PGD	(TASK_SIZE/PGसूची_SIZE)
#घोषणा FIRST_USER_ADDRESS	0UL
#घोषणा FIRST_USER_PGD_NR	(FIRST_USER_ADDRESS >> PGसूची_SHIFT)

#अगर_घोषित CONFIG_MMU
/*
 * Virtual memory area. We keep a distance to other memory regions to be
 * on the safe side. We also use this area क्रम cache aliasing.
 */
#घोषणा VMALLOC_START		(XCHAL_KSEG_CACHED_VADDR - 0x10000000)
#घोषणा VMALLOC_END		(VMALLOC_START + 0x07FEFFFF)
#घोषणा TLBTEMP_BASE_1		(VMALLOC_START + 0x08000000)
#घोषणा TLBTEMP_BASE_2		(TLBTEMP_BASE_1 + DCACHE_WAY_SIZE)
#अगर 2 * DCACHE_WAY_SIZE > ICACHE_WAY_SIZE
#घोषणा TLBTEMP_SIZE		(2 * DCACHE_WAY_SIZE)
#अन्यथा
#घोषणा TLBTEMP_SIZE		ICACHE_WAY_SIZE
#पूर्ण_अगर

#अन्यथा

#घोषणा VMALLOC_START		__XTENSA_UL_CONST(0)
#घोषणा VMALLOC_END		__XTENSA_UL_CONST(0xffffffff)

#पूर्ण_अगर

/*
 * For the Xtensa architecture, the PTE layout is as follows:
 *
 *		31------12  11  10-9   8-6  5-4  3-2  1-0
 *		+-----------------------------------------+
 *		|           |   Software   |   HARDWARE   |
 *		|    PPN    |          ADW | RI |Attribute|
 *		+-----------------------------------------+
 *   pte_none	|             MBZ          | 01 | 11 | 00 |
 *		+-----------------------------------------+
 *   present	|    PPN    | 0 | 00 | ADW | RI | CA | wx |
 *		+- - - - - - - - - - - - - - - - - - - - -+
 *   (PAGE_NONE)|    PPN    | 0 | 00 | ADW | 01 | 11 | 11 |
 *		+-----------------------------------------+
 *   swap	|     index     |   type   | 01 | 11 | 00 |
 *		+-----------------------------------------+
 *
 * For T1050 hardware and earlier the layout dअगरfers क्रम present and (PAGE_NONE)
 *		+-----------------------------------------+
 *   present	|    PPN    | 0 | 00 | ADW | RI | CA | w1 |
 *		+-----------------------------------------+
 *   (PAGE_NONE)|    PPN    | 0 | 00 | ADW | 01 | 01 | 00 |
 *		+-----------------------------------------+
 *
 *  Legend:
 *   PPN        Physical Page Number
 *   ADW	software: accessed (young) / dirty / writable
 *   RI         ring (0=privileged, 1=user, 2 and 3 are unused)
 *   CA		cache attribute: 00 bypass, 01 ग_लिखोback, 10 ग_लिखोthrough
 *		(11 is invalid and used to mark pages that are not present)
 *   w		page is writable (hw)
 *   x		page is executable (hw)
 *   index      swap offset / PAGE_SIZE (bit 11-31: 21 bits -> 8 GB)
 *		(note that the index is always non-zero)
 *   type       swap type (5 bits -> 32 types)
 *
 *  Notes:
 *   - (PROT_NONE) is a special हाल of 'present' but causes an exception क्रम
 *     any access (पढ़ो, ग_लिखो, and execute).
 *   - 'multihit-exception' has the highest priority of all MMU exceptions,
 *     so the ring must be set to 'RING_USER' even for 'non-present' pages.
 *   - on older hardware, the exectuable flag was not supported and
 *     used as a 'valid' flag, so it needs to be always set.
 *   - we need to keep track of certain flags in software (dirty and young)
 *     to करो this, we use ग_लिखो exceptions and have a separate software w-flag.
 *   - attribute value 1101 (and 1111 on T1050 and earlier) is reserved
 */

#घोषणा _PAGE_ATTRIB_MASK	0xf

#घोषणा _PAGE_HW_EXEC		(1<<0)	/* hardware: page is executable */
#घोषणा _PAGE_HW_WRITE		(1<<1)	/* hardware: page is writable */

#घोषणा _PAGE_CA_BYPASS		(0<<2)	/* bypass, non-speculative */
#घोषणा _PAGE_CA_WB		(1<<2)	/* ग_लिखो-back */
#घोषणा _PAGE_CA_WT		(2<<2)	/* ग_लिखो-through */
#घोषणा _PAGE_CA_MASK		(3<<2)
#घोषणा _PAGE_CA_INVALID	(3<<2)

/* We use invalid attribute values to distinguish special pte entries */
#अगर XCHAL_HW_VERSION_MAJOR < 2000
#घोषणा _PAGE_HW_VALID		0x01	/* older HW needed this bit set */
#घोषणा _PAGE_NONE		0x04
#अन्यथा
#घोषणा _PAGE_HW_VALID		0x00
#घोषणा _PAGE_NONE		0x0f
#पूर्ण_अगर

#घोषणा _PAGE_USER		(1<<4)	/* user access (ring=1) */

/* Software */
#घोषणा _PAGE_WRITABLE_BIT	6
#घोषणा _PAGE_WRITABLE		(1<<6)	/* software: page writable */
#घोषणा _PAGE_सूचीTY		(1<<7)	/* software: page dirty */
#घोषणा _PAGE_ACCESSED		(1<<8)	/* software: page accessed (पढ़ो) */

#अगर_घोषित CONFIG_MMU

#घोषणा _PAGE_CHG_MASK	   (PAGE_MASK | _PAGE_ACCESSED | _PAGE_सूचीTY)
#घोषणा _PAGE_PRESENT	   (_PAGE_HW_VALID | _PAGE_CA_WB | _PAGE_ACCESSED)

#घोषणा PAGE_NONE	   __pgprot(_PAGE_NONE | _PAGE_USER)
#घोषणा PAGE_COPY	   __pgprot(_PAGE_PRESENT | _PAGE_USER)
#घोषणा PAGE_COPY_EXEC	   __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_HW_EXEC)
#घोषणा PAGE_READONLY	   __pgprot(_PAGE_PRESENT | _PAGE_USER)
#घोषणा PAGE_READONLY_EXEC __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_HW_EXEC)
#घोषणा PAGE_SHARED	   __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_WRITABLE)
#घोषणा PAGE_SHARED_EXEC \
	__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_WRITABLE | _PAGE_HW_EXEC)
#घोषणा PAGE_KERNEL	   __pgprot(_PAGE_PRESENT | _PAGE_HW_WRITE)
#घोषणा PAGE_KERNEL_RO	   __pgprot(_PAGE_PRESENT)
#घोषणा PAGE_KERNEL_EXEC   __pgprot(_PAGE_PRESENT|_PAGE_HW_WRITE|_PAGE_HW_EXEC)

#अगर (DCACHE_WAY_SIZE > PAGE_SIZE)
# define _PAGE_सूचीECTORY   (_PAGE_HW_VALID | _PAGE_ACCESSED | _PAGE_CA_BYPASS)
#अन्यथा
# define _PAGE_सूचीECTORY   (_PAGE_HW_VALID | _PAGE_ACCESSED | _PAGE_CA_WB)
#पूर्ण_अगर

#अन्यथा /* no mmu */

# define _PAGE_CHG_MASK  (PAGE_MASK | _PAGE_ACCESSED | _PAGE_सूचीTY)
# define PAGE_NONE       __pgprot(0)
# define PAGE_SHARED     __pgprot(0)
# define PAGE_COPY       __pgprot(0)
# define PAGE_READONLY   __pgprot(0)
# define PAGE_KERNEL     __pgprot(0)

#पूर्ण_अगर

/*
 * On certain configurations of Xtensa MMUs (eg. the initial Linux config),
 * the MMU can't करो page protection क्रम execute, and considers that the same as
 * पढ़ो.  Also, ग_लिखो permissions may imply पढ़ो permissions.
 * What follows is the बंदst we can get by reasonable means..
 * See linux/mm/mmap.c क्रम protection_map[] array that uses these definitions.
 */
#घोषणा __P000	PAGE_NONE		/* निजी --- */
#घोषणा __P001	PAGE_READONLY		/* निजी --r */
#घोषणा __P010	PAGE_COPY		/* निजी -w- */
#घोषणा __P011	PAGE_COPY		/* निजी -wr */
#घोषणा __P100	PAGE_READONLY_EXEC	/* निजी x-- */
#घोषणा __P101	PAGE_READONLY_EXEC	/* निजी x-r */
#घोषणा __P110	PAGE_COPY_EXEC		/* निजी xw- */
#घोषणा __P111	PAGE_COPY_EXEC		/* निजी xwr */

#घोषणा __S000	PAGE_NONE		/* shared  --- */
#घोषणा __S001	PAGE_READONLY		/* shared  --r */
#घोषणा __S010	PAGE_SHARED		/* shared  -w- */
#घोषणा __S011	PAGE_SHARED		/* shared  -wr */
#घोषणा __S100	PAGE_READONLY_EXEC	/* shared  x-- */
#घोषणा __S101	PAGE_READONLY_EXEC	/* shared  x-r */
#घोषणा __S110	PAGE_SHARED_EXEC	/* shared  xw- */
#घोषणा __S111	PAGE_SHARED_EXEC	/* shared  xwr */

#अगर_अघोषित __ASSEMBLY__

#घोषणा pte_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pte %08lx.\n", __खाता__, __LINE__, pte_val(e))
#घोषणा pgd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pgd entry %08lx.\n", __खाता__, __LINE__, pgd_val(e))

बाह्य अचिन्हित दीर्घ empty_zero_page[1024];

#घोषणा ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))

#अगर_घोषित CONFIG_MMU
बाह्य pgd_t swapper_pg_dir[PAGE_SIZE/माप(pgd_t)];
बाह्य व्योम paging_init(व्योम);
#अन्यथा
# define swapper_pg_dir शून्य
अटल अंतरभूत व्योम paging_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

/*
 * The pmd contains the kernel भव address of the pte page.
 */
#घोषणा pmd_page_vaddr(pmd) ((अचिन्हित दीर्घ)(pmd_val(pmd) & PAGE_MASK))
#घोषणा pmd_page(pmd) virt_to_page(pmd_val(pmd))

/*
 * pte status.
 */
# define pte_none(pte)	 (pte_val(pte) == (_PAGE_CA_INVALID | _PAGE_USER))
#अगर XCHAL_HW_VERSION_MAJOR < 2000
# define pte_present(pte) ((pte_val(pte) & _PAGE_CA_MASK) != _PAGE_CA_INVALID)
#अन्यथा
# define pte_present(pte)						\
	(((pte_val(pte) & _PAGE_CA_MASK) != _PAGE_CA_INVALID)		\
	 || ((pte_val(pte) & _PAGE_ATTRIB_MASK) == _PAGE_NONE))
#पूर्ण_अगर
#घोषणा pte_clear(mm,addr,ptep)						\
	करो अणु update_pte(ptep, __pte(_PAGE_CA_INVALID | _PAGE_USER)); पूर्ण जबतक (0)

#घोषणा pmd_none(pmd)	 (!pmd_val(pmd))
#घोषणा pmd_present(pmd) (pmd_val(pmd) & PAGE_MASK)
#घोषणा pmd_bad(pmd)	 (pmd_val(pmd) & ~PAGE_MASK)
#घोषणा pmd_clear(pmdp)	 करो अणु set_pmd(pmdp, __pmd(0)); पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte) अणु वापस pte_val(pte) & _PAGE_WRITABLE; पूर्ण
अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte) अणु वापस pte_val(pte) & _PAGE_सूचीTY; पूर्ण
अटल अंतरभूत पूर्णांक pte_young(pte_t pte) अणु वापस pte_val(pte) & _PAGE_ACCESSED; पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
	अणु pte_val(pte) &= ~(_PAGE_WRITABLE | _PAGE_HW_WRITE); वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
	अणु pte_val(pte) &= ~(_PAGE_सूचीTY | _PAGE_HW_WRITE); वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkold(pte_t pte)
	अणु pte_val(pte) &= ~_PAGE_ACCESSED; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
	अणु pte_val(pte) |= _PAGE_सूचीTY; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
	अणु pte_val(pte) |= _PAGE_ACCESSED; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
	अणु pte_val(pte) |= _PAGE_WRITABLE; वापस pte; पूर्ण

#घोषणा pgprot_noncached(prot) \
		((__pgprot((pgprot_val(prot) & ~_PAGE_CA_MASK) | \
			   _PAGE_CA_BYPASS)))

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */

#घोषणा pte_pfn(pte)		(pte_val(pte) >> PAGE_SHIFT)
#घोषणा pte_same(a,b)		(pte_val(a) == pte_val(b))
#घोषणा pte_page(x)		pfn_to_page(pte_pfn(x))
#घोषणा pfn_pte(pfn, prot)	__pte(((pfn) << PAGE_SHIFT) | pgprot_val(prot))
#घोषणा mk_pte(page, prot)	pfn_pte(page_to_pfn(page), prot)

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	वापस __pte((pte_val(pte) & _PAGE_CHG_MASK) | pgprot_val(newprot));
पूर्ण

/*
 * Certain architectures need to करो special things when pte's
 * within a page table are directly modअगरied.  Thus, the following
 * hook is made available.
 */
अटल अंतरभूत व्योम update_pte(pte_t *ptep, pte_t pteval)
अणु
	*ptep = pteval;
#अगर (DCACHE_WAY_SIZE > PAGE_SIZE) && XCHAL_DCACHE_IS_WRITEBACK
	__यंत्र__ __अस्थिर__ ("dhwb %0, 0" :: "a" (ptep));
#पूर्ण_अगर

पूर्ण

काष्ठा mm_काष्ठा;

अटल अंतरभूत व्योम
set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep, pte_t pteval)
अणु
	update_pte(ptep, pteval);
पूर्ण

अटल अंतरभूत व्योम set_pte(pte_t *ptep, pte_t pteval)
अणु
	update_pte(ptep, pteval);
पूर्ण

अटल अंतरभूत व्योम
set_pmd(pmd_t *pmdp, pmd_t pmdval)
अणु
	*pmdp = pmdval;
पूर्ण

काष्ठा vm_area_काष्ठा;

अटल अंतरभूत पूर्णांक
ptep_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			  pte_t *ptep)
अणु
	pte_t pte = *ptep;
	अगर (!pte_young(pte))
		वापस 0;
	update_pte(ptep, pte_mkold(pte));
	वापस 1;
पूर्ण

अटल अंतरभूत pte_t
ptep_get_and_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t pte = *ptep;
	pte_clear(mm, addr, ptep);
	वापस pte;
पूर्ण

अटल अंतरभूत व्योम
ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t pte = *ptep;
	update_pte(ptep, pte_wrprotect(pte));
पूर्ण

/*
 * Encode and decode a swap and file entry.
 */
#घोषणा SWP_TYPE_BITS		5
#घोषणा MAX_SWAPखाताS_CHECK() BUILD_BUG_ON(MAX_SWAPखाताS_SHIFT > SWP_TYPE_BITS)

#घोषणा __swp_type(entry)	(((entry).val >> 6) & 0x1f)
#घोषणा __swp_offset(entry)	((entry).val >> 11)
#घोषणा __swp_entry(type,offs)	\
	((swp_entry_t)अणु((type) << 6) | ((offs) << 11) | \
	 _PAGE_CA_INVALID | _PAGE_USERपूर्ण)
#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)	((pte_t) अणु (x).val पूर्ण)

#पूर्ण_अगर /*  !defined (__ASSEMBLY__) */


#अगर_घोषित __ASSEMBLY__

/* Assembly macro _PGD_INDEX is the same as C pgd_index(अचिन्हित दीर्घ),
 *                _PGD_OFFSET as C pgd_offset(काष्ठा mm_काष्ठा*, अचिन्हित दीर्घ),
 *                _PMD_OFFSET as C pmd_offset(pgd_t*, अचिन्हित दीर्घ)
 *                _PTE_OFFSET as C pte_offset(pmd_t*, अचिन्हित दीर्घ)
 *
 * Note: We require an additional temporary रेजिस्टर which can be the same as
 *       the रेजिस्टर that holds the address.
 *
 * ((pte_t*) ((अचिन्हित दीर्घ)(pmd_val(*pmd) & PAGE_MASK)) + pte_index(addr))
 *
 */
#घोषणा _PGD_INDEX(rt,rs)	extui	rt, rs, PGसूची_SHIFT, 32-PGसूची_SHIFT
#घोषणा _PTE_INDEX(rt,rs)	extui	rt, rs, PAGE_SHIFT, PTRS_PER_PTE_SHIFT

#घोषणा _PGD_OFFSET(mm,adr,पंचांगp)		l32i	mm, mm, MM_PGD;		\
					_PGD_INDEX(पंचांगp, adr);		\
					addx4	mm, पंचांगp, mm

#घोषणा _PTE_OFFSET(pmd,adr,पंचांगp)	_PTE_INDEX(पंचांगp, adr);		\
					srli	pmd, pmd, PAGE_SHIFT;	\
					slli	pmd, pmd, PAGE_SHIFT;	\
					addx4	pmd, पंचांगp, pmd

#अन्यथा

#घोषणा kern_addr_valid(addr)	(1)

बाह्य  व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा * vma,
			      अचिन्हित दीर्घ address, pte_t *ptep);

प्रकार pte_t *pte_addr_t;

#पूर्ण_अगर /* !defined (__ASSEMBLY__) */

#घोषणा __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR
#घोषणा __HAVE_ARCH_PTEP_SET_WRPROTECT
#घोषणा __HAVE_ARCH_PTEP_MKसूचीTY
#घोषणा __HAVE_ARCH_PTE_SAME
/* We provide our own get_unmapped_area to cope with
 * SHM area cache aliasing क्रम userland.
 */
#घोषणा HAVE_ARCH_UNMAPPED_AREA

#पूर्ण_अगर /* _XTENSA_PGTABLE_H */
