<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Page table support क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_PGTABLE_H
#घोषणा _ASM_PGTABLE_H

/*
 * Page table definitions क्रम Qualcomm Hexagon processor.
 */
#समावेश <यंत्र/page.h>
#समावेश <यंत्र-generic/pgtable-nopmd.h>

/* A handy thing to have अगर one has the RAM. Declared in head.S */
बाह्य अचिन्हित दीर्घ empty_zero_page;

/*
 * The PTE model described here is that of the Hexagon Virtual Machine,
 * which स्वतःnomously walks 2-level page tables.  At a lower level, we
 * also describe the RISCish software-loaded TLB entry काष्ठाure of
 * the underlying Hexagon processor. A kernel built to run on the
 * भव machine has no need to know about the underlying hardware.
 */
#समावेश <यंत्र/vm_mmu.h>

/*
 * To maximize the comक्रमt level क्रम the PTE manipulation macros,
 * define the "well known" architecture-specअगरic bits.
 */
#घोषणा _PAGE_READ	__HVM_PTE_R
#घोषणा _PAGE_WRITE	__HVM_PTE_W
#घोषणा _PAGE_EXECUTE	__HVM_PTE_X
#घोषणा _PAGE_USER	__HVM_PTE_U

/*
 * We have a total of 4 "soft" bits available in the असलtract PTE.
 * The two mandatory software bits are Dirty and Accessed.
 * To make nonlinear swap work according to the more recent
 * model, we want a low order "Present" bit to indicate whether
 * the PTE describes MMU programming or swap space.
 */
#घोषणा _PAGE_PRESENT	(1<<0)
#घोषणा _PAGE_सूचीTY	(1<<1)
#घोषणा _PAGE_ACCESSED	(1<<2)

/*
 * For now, let's say that Valid and Present are the same thing.
 * Alternatively, we could say that it's the "or" of R, W, and X
 * permissions.
 */
#घोषणा _PAGE_VALID	_PAGE_PRESENT

/*
 * We're not defining _PAGE_GLOBAL here, since there's no concept
 * of global pages or ASIDs exposed to the Hexagon Virtual Machine,
 * and we want to use the same page table काष्ठाures and macros in
 * the native kernel as we करो in the भव machine kernel.
 * So we'll put up with a bit of inefficiency क्रम now...
 */

/*
 * Top "FOURTH" level (pgd), which क्रम the Hexagon VM is really
 * only the second from the bottom, pgd and pud both being collapsed.
 * Each entry represents 4MB of भव address space, 4K of table
 * thus maps the full 4GB.
 */
#घोषणा PGसूची_SHIFT 22
#घोषणा PTRS_PER_PGD 1024

#घोषणा PGसूची_SIZE (1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK (~(PGसूची_SIZE-1))

#अगर_घोषित CONFIG_PAGE_SIZE_4KB
#घोषणा PTRS_PER_PTE 1024
#पूर्ण_अगर

#अगर_घोषित CONFIG_PAGE_SIZE_16KB
#घोषणा PTRS_PER_PTE 256
#पूर्ण_अगर

#अगर_घोषित CONFIG_PAGE_SIZE_64KB
#घोषणा PTRS_PER_PTE 64
#पूर्ण_अगर

#अगर_घोषित CONFIG_PAGE_SIZE_256KB
#घोषणा PTRS_PER_PTE 16
#पूर्ण_अगर

#अगर_घोषित CONFIG_PAGE_SIZE_1MB
#घोषणा PTRS_PER_PTE 4
#पूर्ण_अगर

/*  Any bigger and the PTE disappears.  */
#घोषणा pgd_ERROR(e) \
	prपूर्णांकk(KERN_ERR "%s:%d: bad pgd %08lx.\n", __खाता__, __LINE__,\
		pgd_val(e))

/*
 * Page Protection Constants. Includes (in this variant) cache attributes.
 */
बाह्य अचिन्हित दीर्घ _dflt_cache_att;

#घोषणा PAGE_NONE	__pgprot(_PAGE_PRESENT | _PAGE_USER | \
				_dflt_cache_att)
#घोषणा PAGE_READONLY	__pgprot(_PAGE_PRESENT | _PAGE_USER | \
				_PAGE_READ | _PAGE_EXECUTE | _dflt_cache_att)
#घोषणा PAGE_COPY	PAGE_READONLY
#घोषणा PAGE_EXEC	__pgprot(_PAGE_PRESENT | _PAGE_USER | \
				_PAGE_READ | _PAGE_EXECUTE | _dflt_cache_att)
#घोषणा PAGE_COPY_EXEC	PAGE_EXEC
#घोषणा PAGE_SHARED	__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_READ | \
				_PAGE_EXECUTE | _PAGE_WRITE | _dflt_cache_att)
#घोषणा PAGE_KERNEL	__pgprot(_PAGE_PRESENT | _PAGE_READ | \
				_PAGE_WRITE | _PAGE_EXECUTE | _dflt_cache_att)


/*
 * Aliases क्रम mapping mmap() protection bits to page protections.
 * These get used क्रम अटल initialization, so using the _dflt_cache_att
 * variable क्रम the शेष cache attribute isn't workable. If the
 * शेष माला_लो changed at boot समय, the boot option code has to
 * update data काष्ठाures like the protaction_map[] array.
 */
#घोषणा CACHEDEF	(CACHE_DEFAULT << 6)

/* Private (copy-on-ग_लिखो) page protections. */
#घोषणा __P000 __pgprot(_PAGE_PRESENT | _PAGE_USER | CACHEDEF)
#घोषणा __P001 __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_READ | CACHEDEF)
#घोषणा __P010 __P000	/* Write-only copy-on-ग_लिखो */
#घोषणा __P011 __P001	/* Read/Write copy-on-ग_लिखो */
#घोषणा __P100 __pgprot(_PAGE_PRESENT | _PAGE_USER | \
			_PAGE_EXECUTE | CACHEDEF)
#घोषणा __P101 __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_EXECUTE | \
			_PAGE_READ | CACHEDEF)
#घोषणा __P110 __P100	/* Write/execute copy-on-ग_लिखो */
#घोषणा __P111 __P101	/* Read/Write/Execute, copy-on-ग_लिखो */

/* Shared page protections. */
#घोषणा __S000 __P000
#घोषणा __S001 __P001
#घोषणा __S010 __pgprot(_PAGE_PRESENT | _PAGE_USER | \
			_PAGE_WRITE | CACHEDEF)
#घोषणा __S011 __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_READ | \
			_PAGE_WRITE | CACHEDEF)
#घोषणा __S100 __pgprot(_PAGE_PRESENT | _PAGE_USER | \
			_PAGE_EXECUTE | CACHEDEF)
#घोषणा __S101 __P101
#घोषणा __S110 __pgprot(_PAGE_PRESENT | _PAGE_USER | \
			_PAGE_EXECUTE | _PAGE_WRITE | CACHEDEF)
#घोषणा __S111 __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_READ | \
			_PAGE_EXECUTE | _PAGE_WRITE | CACHEDEF)

बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD];  /* located in head.S */

/* Seems to be zero even in architectures where the zero page is firewalled? */
#घोषणा FIRST_USER_ADDRESS 0UL

/*  HUGETLB not working currently  */
#अगर_घोषित CONFIG_HUGETLB_PAGE
#घोषणा pte_mkhuge(pte) __pte((pte_val(pte) & ~0x3) | HVM_HUGEPAGE_SIZE)
#पूर्ण_अगर

/*
 * For now, assume that higher-level code will करो TLB/MMU invalidations
 * and करोn't insert that overhead पूर्णांकo this low-level function.
 */
बाह्य व्योम sync_icache_dcache(pte_t pte);

#घोषणा pte_present_exec_user(pte) \
	((pte_val(pte) & (_PAGE_EXECUTE | _PAGE_USER)) == \
	(_PAGE_EXECUTE | _PAGE_USER))

अटल अंतरभूत व्योम set_pte(pte_t *ptep, pte_t pteval)
अणु
	/*  should really be using pte_exec, अगर it weren't declared later. */
	अगर (pte_present_exec_user(pteval))
		sync_icache_dcache(pteval);

	*ptep = pteval;
पूर्ण

/*
 * For the Hexagon Virtual Machine MMU (or its emulation), a null/invalid
 * L1 PTE (PMD/PGD) has 7 in the least signअगरicant bits. For the L2 PTE
 * (Linux PTE), the key is to have bits 11..9 all zero.  We'd use 0x7
 * as a universal null entry, but some of those least signअगरicant bits
 * are पूर्णांकerpreted by software.
 */
#घोषणा _शून्य_PMD	0x7
#घोषणा _शून्य_PTE	0x0

अटल अंतरभूत व्योम pmd_clear(pmd_t *pmd_entry_ptr)
अणु
	 pmd_val(*pmd_entry_ptr) = _शून्य_PMD;
पूर्ण

/*
 * Conveniently, a null PTE value is invalid.
 */
अटल अंतरभूत व्योम pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				pte_t *ptep)
अणु
	pte_val(*ptep) = _शून्य_PTE;
पूर्ण

/**
 * pmd_none - check अगर pmd_entry is mapped
 * @pmd_entry:  pmd entry
 *
 * MIPS checks it against that "invalid pte table" thing.
 */
अटल अंतरभूत पूर्णांक pmd_none(pmd_t pmd)
अणु
	वापस pmd_val(pmd) == _शून्य_PMD;
पूर्ण

/**
 * pmd_present - is there a page table behind this?
 * Essentially the inverse of pmd_none.  We maybe
 * save an अंतरभूत inकाष्ठाion by defining it this
 * way, instead of simply "!pmd_none".
 */
अटल अंतरभूत पूर्णांक pmd_present(pmd_t pmd)
अणु
	वापस pmd_val(pmd) != (अचिन्हित दीर्घ)_शून्य_PMD;
पूर्ण

/**
 * pmd_bad - check अगर a PMD entry is "bad". That might mean swapped out.
 * As we have no known cause of badness, it's null, as it is क्रम many
 * architectures.
 */
अटल अंतरभूत पूर्णांक pmd_bad(pmd_t pmd)
अणु
	वापस 0;
पूर्ण

/*
 * pmd_page - converts a PMD entry to a page poपूर्णांकer
 */
#घोषणा pmd_page(pmd)  (pfn_to_page(pmd_val(pmd) >> PAGE_SHIFT))
#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

/**
 * pte_none - check अगर pte is mapped
 * @pte: pte_t entry
 */
अटल अंतरभूत पूर्णांक pte_none(pte_t pte)
अणु
	वापस pte_val(pte) == _शून्य_PTE;
पूर्ण;

/*
 * pte_present - check अगर page is present
 */
अटल अंतरभूत पूर्णांक pte_present(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_PRESENT;
पूर्ण

/* mk_pte - make a PTE out of a page poपूर्णांकer and protection bits */
#घोषणा mk_pte(page, pgprot) pfn_pte(page_to_pfn(page), (pgprot))

/* pte_page - वापसs a page (frame poपूर्णांकer/descriptor?) based on a PTE */
#घोषणा pte_page(x) pfn_to_page(pte_pfn(x))

/* pte_mkold - mark PTE as not recently accessed */
अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	pte_val(pte) &= ~_PAGE_ACCESSED;
	वापस pte;
पूर्ण

/* pte_mkyoung - mark PTE as recently accessed */
अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_ACCESSED;
	वापस pte;
पूर्ण

/* pte_mkclean - mark page as in sync with backing store */
अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	pte_val(pte) &= ~_PAGE_सूचीTY;
	वापस pte;
पूर्ण

/* pte_सूची_गढ़ोty - mark page as modअगरied */
अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_सूचीTY;
	वापस pte;
पूर्ण

/* pte_young - "is PTE marked as accessed"? */
अटल अंतरभूत पूर्णांक pte_young(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_ACCESSED;
पूर्ण

/* pte_dirty - "is PTE dirty?" */
अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_सूचीTY;
पूर्ण

/* pte_modअगरy - set protection bits on PTE */
अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t prot)
अणु
	pte_val(pte) &= PAGE_MASK;
	pte_val(pte) |= pgprot_val(prot);
	वापस pte;
पूर्ण

/* pte_wrprotect - mark page as not writable */
अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	pte_val(pte) &= ~_PAGE_WRITE;
	वापस pte;
पूर्ण

/* pte_mkग_लिखो - mark page as writable */
अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_WRITE;
	वापस pte;
पूर्ण

/* pte_mkexec - mark PTE as executable */
अटल अंतरभूत pte_t pte_mkexec(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_EXECUTE;
	वापस pte;
पूर्ण

/* pte_पढ़ो - "is PTE marked as readable?" */
अटल अंतरभूत पूर्णांक pte_पढ़ो(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_READ;
पूर्ण

/* pte_ग_लिखो - "is PTE marked as writable?" */
अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_WRITE;
पूर्ण


/* pte_exec - "is PTE marked as executable?" */
अटल अंतरभूत पूर्णांक pte_exec(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_EXECUTE;
पूर्ण

/* __pte_to_swp_entry - extract swap entry from PTE */
#घोषणा __pte_to_swp_entry(pte) ((swp_entry_t) अणु pte_val(pte) पूर्ण)

/* __swp_entry_to_pte - extract PTE from swap entry */
#घोषणा __swp_entry_to_pte(x) ((pte_t) अणु (x).val पूर्ण)

/* pfn_pte - convert page number and protection value to page table entry */
#घोषणा pfn_pte(pfn, pgprot) __pte((pfn << PAGE_SHIFT) | pgprot_val(pgprot))

/* pte_pfn - convert pte to page frame number */
#घोषणा pte_pfn(pte) (pte_val(pte) >> PAGE_SHIFT)
#घोषणा set_pmd(pmdptr, pmdval) (*(pmdptr) = (pmdval))

/*
 * set_pte_at - update page table and करो whatever magic may be
 * necessary to make the underlying hardware/firmware take note.
 *
 * VM may require a भव inकाष्ठाion to alert the MMU.
 */
#घोषणा set_pte_at(mm, addr, ptep, pte) set_pte(ptep, pte)

अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	वापस (अचिन्हित दीर्घ)__va(pmd_val(pmd) & PAGE_MASK);
पूर्ण

/* ZERO_PAGE - वापसs the globally shared zero page */
#घोषणा ZERO_PAGE(vaddr) (virt_to_page(&empty_zero_page))

/*
 * Swap/file PTE definitions.  If _PAGE_PRESENT is zero, the rest of the PTE is
 * पूर्णांकerpreted as swap inक्रमmation.  The reमुख्यing मुक्त bits are पूर्णांकerpreted as
 * swap type/offset tuple.  Rather than have the TLB fill handler test
 * _PAGE_PRESENT, we're going to reserve the permissions bits and set them to
 * all zeros क्रम swap entries, which speeds up the miss handler at the cost of
 * 3 bits of offset.  That trade-off can be revisited अगर necessary, but Hexagon
 * processor architecture and target applications suggest a lot of TLB misses
 * and not much swap space.
 *
 * Format of swap PTE:
 *	bit	0:	Present (zero)
 *	bits	1-5:	swap type (arch independent layer uses 5 bits max)
 *	bits	6-9:	bits 3:0 of offset
 *	bits	10-12:	effectively _PAGE_PROTNONE (all zero)
 *	bits	13-31:  bits 22:4 of swap offset
 *
 * The split offset makes some of the following macros a little gnarly,
 * but there's plenty of precedent क्रम this sort of thing.
 */

/* Used क्रम swap PTEs */
#घोषणा __swp_type(swp_pte)		(((swp_pte).val >> 1) & 0x1f)

#घोषणा __swp_offset(swp_pte) \
	((((swp_pte).val >> 6) & 0xf) | (((swp_pte).val >> 9) & 0x7ffff0))

#घोषणा __swp_entry(type, offset) \
	((swp_entry_t)	अणु \
		((type << 1) | \
		 ((offset & 0x7ffff0) << 9) | ((offset & 0xf) << 6)) पूर्ण)

#पूर्ण_अगर
