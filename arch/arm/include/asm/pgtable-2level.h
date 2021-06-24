<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/pgtable-2level.h
 *
 *  Copyright (C) 1995-2002 Russell King
 */
#अगर_अघोषित _ASM_PGTABLE_2LEVEL_H
#घोषणा _ASM_PGTABLE_2LEVEL_H

#घोषणा __PAGETABLE_PMD_FOLDED 1

/*
 * Hardware-wise, we have a two level page table काष्ठाure, where the first
 * level has 4096 entries, and the second level has 256 entries.  Each entry
 * is one 32-bit word.  Most of the bits in the second level entry are used
 * by hardware, and there aren't any "accessed" and "dirty" bits.
 *
 * Linux on the other hand has a three level page table काष्ठाure, which can
 * be wrapped to fit a two level page table काष्ठाure easily - using the PGD
 * and PTE only.  However, Linux also expects one "PTE" table per page, and
 * at least a "dirty" bit.
 *
 * Thereक्रमe, we tweak the implementation slightly - we tell Linux that we
 * have 2048 entries in the first level, each of which is 8 bytes (iow, two
 * hardware poपूर्णांकers to the second level.)  The second level contains two
 * hardware PTE tables arranged contiguously, preceded by Linux versions
 * which contain the state inक्रमmation Linux needs.  We, thereक्रमe, end up
 * with 512 entries in the "PTE" level.
 *
 * This leads to the page tables having the following layout:
 *
 *    pgd             pte
 * |        |
 * +--------+
 * |        |       +------------+ +0
 * +- - - - +       | Linux pt 0 |
 * |        |       +------------+ +1024
 * +--------+ +0    | Linux pt 1 |
 * |        |-----> +------------+ +2048
 * +- - - - + +4    |  h/w pt 0  |
 * |        |-----> +------------+ +3072
 * +--------+ +8    |  h/w pt 1  |
 * |        |       +------------+ +4096
 *
 * See L_PTE_xxx below क्रम definitions of bits in the "Linux pt", and
 * PTE_xxx क्रम definitions of bits appearing in the "h/w pt".
 *
 * PMD_xxx definitions refer to bits in the first level page table.
 *
 * The "dirty" bit is emulated by only granting hardware ग_लिखो permission
 * अगरf the page is marked "writable" and "dirty" in the Linux PTE.  This
 * means that a ग_लिखो to a clean page will cause a permission fault, and
 * the Linux MM layer will mark the page dirty via handle_pte_fault().
 * For the hardware to notice the permission change, the TLB entry must
 * be flushed, and ptep_set_access_flags() करोes that क्रम us.
 *
 * The "accessed" or "young" bit is emulated by a similar method; we only
 * allow accesses to the page अगर the "young" bit is set.  Accesses to the
 * page will cause a fault, and handle_pte_fault() will set the young bit
 * क्रम us as दीर्घ as the page is marked present in the corresponding Linux
 * PTE entry.  Again, ptep_set_access_flags() will ensure that the TLB is
 * up to date.
 *
 * However, when the "young" bit is cleared, we deny access to the page
 * by clearing the hardware PTE.  Currently Linux करोes not flush the TLB
 * क्रम us in this हाल, which means the TLB will retain the transation
 * until either the TLB entry is evicted under pressure, or a context
 * चयन which changes the user space mapping occurs.
 */
#घोषणा PTRS_PER_PTE		512
#घोषणा PTRS_PER_PMD		1
#घोषणा PTRS_PER_PGD		2048

#घोषणा PTE_HWTABLE_PTRS	(PTRS_PER_PTE)
#घोषणा PTE_HWTABLE_OFF		(PTE_HWTABLE_PTRS * माप(pte_t))
#घोषणा PTE_HWTABLE_SIZE	(PTRS_PER_PTE * माप(u32))

#घोषणा MAX_POSSIBLE_PHYSMEM_BITS	32

/*
 * PMD_SHIFT determines the size of the area a second-level page table can map
 * PGसूची_SHIFT determines what a third-level page table entry can map
 */
#घोषणा PMD_SHIFT		21
#घोषणा PGसूची_SHIFT		21

#घोषणा PMD_SIZE		(1UL << PMD_SHIFT)
#घोषणा PMD_MASK		(~(PMD_SIZE-1))
#घोषणा PGसूची_SIZE		(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK		(~(PGसूची_SIZE-1))

/*
 * section address mask and size definitions.
 */
#घोषणा SECTION_SHIFT		20
#घोषणा SECTION_SIZE		(1UL << SECTION_SHIFT)
#घोषणा SECTION_MASK		(~(SECTION_SIZE-1))

/*
 * ARMv6 supersection address mask and size definitions.
 */
#घोषणा SUPERSECTION_SHIFT	24
#घोषणा SUPERSECTION_SIZE	(1UL << SUPERSECTION_SHIFT)
#घोषणा SUPERSECTION_MASK	(~(SUPERSECTION_SIZE-1))

#घोषणा USER_PTRS_PER_PGD	(TASK_SIZE / PGसूची_SIZE)

/*
 * "Linux" PTE definitions.
 *
 * We keep two sets of PTEs - the hardware and the linux version.
 * This allows greater flexibility in the way we map the Linux bits
 * onto the hardware tables, and allows us to have YOUNG and सूचीTY
 * bits.
 *
 * The PTE table poपूर्णांकer refers to the hardware entries; the "Linux"
 * entries are stored 1024 bytes below.
 */
#घोषणा L_PTE_VALID		(_AT(pteval_t, 1) << 0)		/* Valid */
#घोषणा L_PTE_PRESENT		(_AT(pteval_t, 1) << 0)
#घोषणा L_PTE_YOUNG		(_AT(pteval_t, 1) << 1)
#घोषणा L_PTE_सूचीTY		(_AT(pteval_t, 1) << 6)
#घोषणा L_PTE_RDONLY		(_AT(pteval_t, 1) << 7)
#घोषणा L_PTE_USER		(_AT(pteval_t, 1) << 8)
#घोषणा L_PTE_XN		(_AT(pteval_t, 1) << 9)
#घोषणा L_PTE_SHARED		(_AT(pteval_t, 1) << 10)	/* shared(v6), coherent(xsc3) */
#घोषणा L_PTE_NONE		(_AT(pteval_t, 1) << 11)

/*
 * These are the memory types, defined to be compatible with
 * pre-ARMv6 CPUs cacheable and bufferable bits: n/a,n/a,C,B
 * ARMv6+ without TEX remapping, they are a table index.
 * ARMv6+ with TEX remapping, they correspond to n/a,TEX(0),C,B
 *
 * MT type		Pre-ARMv6	ARMv6+ type / cacheable status
 * UNCACHED		Uncached	Strongly ordered
 * BUFFERABLE		Bufferable	Normal memory / non-cacheable
 * WRITETHROUGH		Writethrough	Normal memory / ग_लिखो through
 * WRITEBACK		Writeback	Normal memory / ग_लिखो back, पढ़ो alloc
 * MINICACHE		Minicache	N/A
 * WRITEALLOC		Writeback	Normal memory / ग_लिखो back, ग_लिखो alloc
 * DEV_SHARED		Uncached	Device memory (shared)
 * DEV_NONSHARED	Uncached	Device memory (non-shared)
 * DEV_WC		Bufferable	Normal memory / non-cacheable
 * DEV_CACHED		Writeback	Normal memory / ग_लिखो back, पढ़ो alloc
 * VECTORS		Variable	Normal memory / variable
 *
 * All normal memory mappings have the following properties:
 * - पढ़ोs can be repeated with no side effects
 * - repeated पढ़ोs वापस the last value written
 * - पढ़ोs can fetch additional locations without side effects
 * - ग_लिखोs can be repeated (in certain हालs) with no side effects
 * - ग_लिखोs can be merged beक्रमe accessing the target
 * - unaligned accesses can be supported
 *
 * All device mappings have the following properties:
 * - no access speculation
 * - no repetition (eg, on वापस from an exception)
 * - number, order and size of accesses are मुख्यtained
 * - unaligned accesses are "unpredictable"
 */
#घोषणा L_PTE_MT_UNCACHED	(_AT(pteval_t, 0x00) << 2)	/* 0000 */
#घोषणा L_PTE_MT_BUFFERABLE	(_AT(pteval_t, 0x01) << 2)	/* 0001 */
#घोषणा L_PTE_MT_WRITETHROUGH	(_AT(pteval_t, 0x02) << 2)	/* 0010 */
#घोषणा L_PTE_MT_WRITEBACK	(_AT(pteval_t, 0x03) << 2)	/* 0011 */
#घोषणा L_PTE_MT_MINICACHE	(_AT(pteval_t, 0x06) << 2)	/* 0110 (sa1100, xscale) */
#घोषणा L_PTE_MT_WRITEALLOC	(_AT(pteval_t, 0x07) << 2)	/* 0111 */
#घोषणा L_PTE_MT_DEV_SHARED	(_AT(pteval_t, 0x04) << 2)	/* 0100 */
#घोषणा L_PTE_MT_DEV_NONSHARED	(_AT(pteval_t, 0x0c) << 2)	/* 1100 */
#घोषणा L_PTE_MT_DEV_WC		(_AT(pteval_t, 0x09) << 2)	/* 1001 */
#घोषणा L_PTE_MT_DEV_CACHED	(_AT(pteval_t, 0x0b) << 2)	/* 1011 */
#घोषणा L_PTE_MT_VECTORS	(_AT(pteval_t, 0x0f) << 2)	/* 1111 */
#घोषणा L_PTE_MT_MASK		(_AT(pteval_t, 0x0f) << 2)

#अगर_अघोषित __ASSEMBLY__

/*
 * The "pud_xxx()" functions here are trivial when the pmd is folded पूर्णांकo
 * the pud: the pud entry is never bad, always exists, and can't be set or
 * cleared.
 */
अटल अंतरभूत पूर्णांक pud_none(pud_t pud)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pud_bad(pud_t pud)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pud_present(pud_t pud)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम pud_clear(pud_t *pudp)
अणु
पूर्ण

अटल अंतरभूत व्योम set_pud(pud_t *pudp, pud_t pud)
अणु
पूर्ण

अटल अंतरभूत pmd_t *pmd_offset(pud_t *pud, अचिन्हित दीर्घ addr)
अणु
	वापस (pmd_t *)pud;
पूर्ण
#घोषणा pmd_offset pmd_offset

#घोषणा pmd_large(pmd)		(pmd_val(pmd) & 2)
#घोषणा pmd_leaf(pmd)		(pmd_val(pmd) & 2)
#घोषणा pmd_bad(pmd)		(pmd_val(pmd) & 2)
#घोषणा pmd_present(pmd)	(pmd_val(pmd))

#घोषणा copy_pmd(pmdpd,pmdps)		\
	करो अणु				\
		pmdpd[0] = pmdps[0];	\
		pmdpd[1] = pmdps[1];	\
		flush_pmd_entry(pmdpd);	\
	पूर्ण जबतक (0)

#घोषणा pmd_clear(pmdp)			\
	करो अणु				\
		pmdp[0] = __pmd(0);	\
		pmdp[1] = __pmd(0);	\
		clean_pmd_entry(pmdp);	\
	पूर्ण जबतक (0)

/* we करोn't need complex calculations here as the pmd is folded पूर्णांकo the pgd */
#घोषणा pmd_addr_end(addr,end) (end)

#घोषणा set_pte_ext(ptep,pte,ext) cpu_set_pte_ext(ptep,pte,ext)

/*
 * We करोn't have huge page support क्रम लघु descriptors, क्रम the moment
 * define empty stubs क्रम use by pin_page_क्रम_ग_लिखो.
 */
#घोषणा pmd_hugewillfault(pmd)	(0)
#घोषणा pmd_thp_or_huge(pmd)	(0)

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_PGTABLE_2LEVEL_H */
