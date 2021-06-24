<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/pgtable-nommu.h
 *
 *  Copyright (C) 1995-2002 Russell King
 *  Copyright (C) 2004  Hyok S. Choi
 */
#अगर_अघोषित _ASMARM_PGTABLE_NOMMU_H
#घोषणा _ASMARM_PGTABLE_NOMMU_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/slab.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/page.h>

/*
 * Trivial page table functions.
 */
#घोषणा pgd_present(pgd)	(1)
#घोषणा pgd_none(pgd)		(0)
#घोषणा pgd_bad(pgd)		(0)
#घोषणा pgd_clear(pgdp)
#घोषणा kern_addr_valid(addr)	(1)
/* FIXME */
/*
 * PMD_SHIFT determines the size of the area a second-level page table can map
 * PGसूची_SHIFT determines what a third-level page table entry can map
 */
#घोषणा PGसूची_SHIFT		21

#घोषणा PGसूची_SIZE		(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK		(~(PGसूची_SIZE-1))
/* FIXME */

#घोषणा PAGE_NONE	__pgprot(0)
#घोषणा PAGE_SHARED	__pgprot(0)
#घोषणा PAGE_COPY	__pgprot(0)
#घोषणा PAGE_READONLY	__pgprot(0)
#घोषणा PAGE_KERNEL	__pgprot(0)

#घोषणा swapper_pg_dir ((pgd_t *) 0)


प्रकार pte_t *pte_addr_t;

/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
#घोषणा ZERO_PAGE(vaddr)	(virt_to_page(0))

/*
 * Mark the prot value as uncacheable and unbufferable.
 */
#घोषणा pgprot_noncached(prot)	(prot)
#घोषणा pgprot_ग_लिखोcombine(prot) (prot)
#घोषणा pgprot_device(prot)	(prot)


/*
 * These would be in other places but having them here reduces the dअगरfs.
 */
बाह्य अचिन्हित पूर्णांक kobjsize(स्थिर व्योम *objp);

/*
 * All 32bit addresses are effectively valid क्रम vदो_स्मृति...
 * Sort of meaningless क्रम non-VM tarमाला_लो.
 */
#घोषणा	VMALLOC_START	0UL
#घोषणा	VMALLOC_END	0xffffffffUL

#घोषणा FIRST_USER_ADDRESS      0UL

#अन्यथा 

/*
 * dummy tlb and user काष्ठाures.
 */
#घोषणा v3_tlb_fns	(0)
#घोषणा v4_tlb_fns	(0)
#घोषणा v4wb_tlb_fns	(0)
#घोषणा v4wbi_tlb_fns	(0)
#घोषणा v6wbi_tlb_fns	(0)
#घोषणा v7wbi_tlb_fns	(0)

#घोषणा v3_user_fns	(0)
#घोषणा v4_user_fns	(0)
#घोषणा v4_mc_user_fns	(0)
#घोषणा v4wb_user_fns	(0)
#घोषणा v4wt_user_fns	(0)
#घोषणा v6_user_fns	(0)
#घोषणा xscale_mc_user_fns (0)

#पूर्ण_अगर /*__ASSEMBLY__*/

#पूर्ण_अगर /* _ASMARM_PGTABLE_H */
