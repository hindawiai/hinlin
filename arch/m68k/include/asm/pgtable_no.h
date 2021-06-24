<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68KNOMMU_PGTABLE_H
#घोषणा _M68KNOMMU_PGTABLE_H

#समावेश <यंत्र-generic/pgtable-nopud.h>

/*
 * (C) Copyright 2000-2002, Greg Ungerer <gerg@snapgear.com>
 */

#समावेश <linux/slab.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/पन.स>

/*
 * Trivial page table functions.
 */
#घोषणा pgd_present(pgd)	(1)
#घोषणा pgd_none(pgd)		(0)
#घोषणा pgd_bad(pgd)		(0)
#घोषणा pgd_clear(pgdp)
#घोषणा kern_addr_valid(addr)	(1)
#घोषणा	pmd_offset(a, b)	((व्योम *)0)

#घोषणा PAGE_NONE	__pgprot(0)
#घोषणा PAGE_SHARED	__pgprot(0)
#घोषणा PAGE_COPY	__pgprot(0)
#घोषणा PAGE_READONLY	__pgprot(0)
#घोषणा PAGE_KERNEL	__pgprot(0)

बाह्य व्योम paging_init(व्योम);
#घोषणा swapper_pg_dir ((pgd_t *) 0)

#घोषणा __swp_type(x)		(0)
#घोषणा __swp_offset(x)		(0)
#घोषणा __swp_entry(typ,off)	((swp_entry_t) अणु ((typ) | ((off) << 7)) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)	((pte_t) अणु (x).val पूर्ण)

/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
#घोषणा ZERO_PAGE(vaddr)	(virt_to_page(0))

/*
 * All 32bit addresses are effectively valid क्रम vदो_स्मृति...
 * Sort of meaningless क्रम non-VM tarमाला_लो.
 */
#घोषणा	VMALLOC_START	0
#घोषणा	VMALLOC_END	0xffffffff
#घोषणा	KMAP_START	0
#घोषणा	KMAP_END	0xffffffff

#पूर्ण_अगर /* _M68KNOMMU_PGTABLE_H */
