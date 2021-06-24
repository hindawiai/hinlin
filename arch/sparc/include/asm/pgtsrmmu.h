<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * pgtsrmmu.h:  SRMMU page table defines and code.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _SPARC_PGTSRMMU_H
#घोषणा _SPARC_PGTSRMMU_H

#समावेश <यंत्र/page.h>

#अगर_घोषित __ASSEMBLY__
#समावेश <यंत्र/thपढ़ो_info.h>	/* TI_UWINMASK क्रम WINDOW_FLUSH */
#पूर्ण_अगर

/* Number of contexts is implementation-dependent; 64k is the most we support */
#घोषणा SRMMU_MAX_CONTEXTS	65536

#घोषणा SRMMU_PTE_TABLE_SIZE		(PTRS_PER_PTE*4)
#घोषणा SRMMU_PMD_TABLE_SIZE		(PTRS_PER_PMD*4)
#घोषणा SRMMU_PGD_TABLE_SIZE		(PTRS_PER_PGD*4)

/* Definition of the values in the ET field of PTD's and PTE's */
#घोषणा SRMMU_ET_MASK         0x3
#घोषणा SRMMU_ET_INVALID      0x0
#घोषणा SRMMU_ET_PTD          0x1
#घोषणा SRMMU_ET_PTE          0x2
#घोषणा SRMMU_ET_REPTE        0x3 /* AIEEE, SuperSparc II reverse endian page! */

/* Physical page extraction from PTP's and PTE's. */
#घोषणा SRMMU_CTX_PMASK    0xfffffff0
#घोषणा SRMMU_PTD_PMASK    0xfffffff0
#घोषणा SRMMU_PTE_PMASK    0xffffff00

/* The pte non-page bits.  Some notes:
 * 1) cache, dirty, valid, and ref are frobbable
 *    क्रम both supervisor and user pages.
 * 2) exec and ग_लिखो will only give the desired effect
 *    on user pages
 * 3) use priv and priv_पढ़ोonly क्रम changing the
 *    अक्षरacteristics of supervisor ptes
 */
#घोषणा SRMMU_CACHE        0x80
#घोषणा SRMMU_सूचीTY        0x40
#घोषणा SRMMU_REF          0x20
#घोषणा SRMMU_NOREAD       0x10
#घोषणा SRMMU_EXEC         0x08
#घोषणा SRMMU_WRITE        0x04
#घोषणा SRMMU_VALID        0x02 /* SRMMU_ET_PTE */
#घोषणा SRMMU_PRIV         0x1c
#घोषणा SRMMU_PRIV_RDONLY  0x18

#घोषणा SRMMU_CHG_MASK    (0xffffff00 | SRMMU_REF | SRMMU_सूचीTY)

/* SRMMU swap entry encoding
 *
 * We use 5 bits क्रम the type and 19 क्रम the offset.  This gives us
 * 32 swapfiles of 4GB each.  Encoding looks like:
 *
 * oooooooooooooooooootttttRRRRRRRR
 * fedcba9876543210fedcba9876543210
 *
 * The bottom 7 bits are reserved क्रम protection and status bits, especially
 * PRESENT.
 */
#घोषणा SRMMU_SWP_TYPE_MASK	0x1f
#घोषणा SRMMU_SWP_TYPE_SHIFT	7
#घोषणा SRMMU_SWP_OFF_MASK	0xfffff
#घोषणा SRMMU_SWP_OFF_SHIFT	(SRMMU_SWP_TYPE_SHIFT + 5)

/* Some day I will implement true fine grained access bits क्रम
 * user pages because the SRMMU gives us the capabilities to
 * enक्रमce all the protection levels that vma's can have.
 * XXX But क्रम now...
 */
#घोषणा SRMMU_PAGE_NONE    __pgprot(SRMMU_CACHE | \
				    SRMMU_PRIV | SRMMU_REF)
#घोषणा SRMMU_PAGE_SHARED  __pgprot(SRMMU_VALID | SRMMU_CACHE | \
				    SRMMU_EXEC | SRMMU_WRITE | SRMMU_REF)
#घोषणा SRMMU_PAGE_COPY    __pgprot(SRMMU_VALID | SRMMU_CACHE | \
				    SRMMU_EXEC | SRMMU_REF)
#घोषणा SRMMU_PAGE_RDONLY  __pgprot(SRMMU_VALID | SRMMU_CACHE | \
				    SRMMU_EXEC | SRMMU_REF)
#घोषणा SRMMU_PAGE_KERNEL  __pgprot(SRMMU_VALID | SRMMU_CACHE | SRMMU_PRIV | \
				    SRMMU_सूचीTY | SRMMU_REF)

/* SRMMU Register addresses in ASI 0x4.  These are valid क्रम all
 * current SRMMU implementations that exist.
 */
#घोषणा SRMMU_CTRL_REG           0x00000000
#घोषणा SRMMU_CTXTBL_PTR         0x00000100
#घोषणा SRMMU_CTX_REG            0x00000200
#घोषणा SRMMU_FAULT_STATUS       0x00000300
#घोषणा SRMMU_FAULT_ADDR         0x00000400

#घोषणा WINDOW_FLUSH(पंचांगp1, पंचांगp2)					\
	mov	0, पंचांगp1;						\
98:	ld	[%g6 + TI_UWINMASK], पंचांगp2;				\
	orcc	%g0, पंचांगp2, %g0;						\
	add	पंचांगp1, 1, पंचांगp1;						\
	bne	98b;							\
	 save	%sp, -64, %sp;						\
99:	subcc	पंचांगp1, 1, पंचांगp1;						\
	bne	99b;							\
	 restore %g0, %g0, %g0;

#अगर_अघोषित __ASSEMBLY__
बाह्य अचिन्हित दीर्घ last_valid_pfn;

/* This makes sense. Honest it करोes - Anton */
/* XXX Yes but it's ugly as sin.  FIXME. -KMW */
बाह्य व्योम *srmmu_nocache_pool;
#घोषणा __nocache_pa(VADDR) (((अचिन्हित दीर्घ)VADDR) - SRMMU_NOCACHE_VADDR + __pa((अचिन्हित दीर्घ)srmmu_nocache_pool))
#घोषणा __nocache_va(PADDR) (__va((अचिन्हित दीर्घ)PADDR) - (अचिन्हित दीर्घ)srmmu_nocache_pool + SRMMU_NOCACHE_VADDR)
#घोषणा __nocache_fix(VADDR) ((__typeof__(VADDR))__va(__nocache_pa(VADDR)))

/* Accessing the MMU control रेजिस्टर. */
अचिन्हित पूर्णांक srmmu_get_mmureg(व्योम);
व्योम srmmu_set_mmureg(अचिन्हित दीर्घ regval);
व्योम srmmu_set_ctable_ptr(अचिन्हित दीर्घ paddr);
व्योम srmmu_set_context(पूर्णांक context);
पूर्णांक srmmu_get_context(व्योम);
अचिन्हित पूर्णांक srmmu_get_ख_स्थितिus(व्योम);
अचिन्हित पूर्णांक srmmu_get_faddr(व्योम);

/* This is guaranteed on all SRMMU's. */
अटल अंतरभूत व्योम srmmu_flush_whole_tlb(व्योम)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t": :
			     "r" (0x400),        /* Flush entire TLB!! */
			     "i" (ASI_M_FLUSH_PROBE) : "memory");

पूर्ण

अटल अंतरभूत पूर्णांक
srmmu_get_pte (अचिन्हित दीर्घ addr)
अणु
	रेजिस्टर अचिन्हित दीर्घ entry;
        
	__यंत्र__ __अस्थिर__("\n\tlda [%1] %2,%0\n\t" :
				"=r" (entry):
				"r" ((addr & 0xfffff000) | 0x400), "i" (ASI_M_FLUSH_PROBE));
	वापस entry;
पूर्ण

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#पूर्ण_अगर /* !(_SPARC_PGTSRMMU_H) */
