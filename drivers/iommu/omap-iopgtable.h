<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap iommu: pagetable definitions
 *
 * Copyright (C) 2008-2010 Nokia Corporation
 *
 * Written by Hiroshi DOYU <Hiroshi.DOYU@nokia.com>
 */

#अगर_अघोषित _OMAP_IOPGTABLE_H
#घोषणा _OMAP_IOPGTABLE_H

#समावेश <linux/bitops.h>

/*
 * "L2 table" address mask and size definitions.
 */
#घोषणा IOPGD_SHIFT		20
#घोषणा IOPGD_SIZE		BIT(IOPGD_SHIFT)
#घोषणा IOPGD_MASK		(~(IOPGD_SIZE - 1))

/*
 * "section" address mask and size definitions.
 */
#घोषणा IOSECTION_SHIFT		20
#घोषणा IOSECTION_SIZE		BIT(IOSECTION_SHIFT)
#घोषणा IOSECTION_MASK		(~(IOSECTION_SIZE - 1))

/*
 * "supersection" address mask and size definitions.
 */
#घोषणा IOSUPER_SHIFT		24
#घोषणा IOSUPER_SIZE		BIT(IOSUPER_SHIFT)
#घोषणा IOSUPER_MASK		(~(IOSUPER_SIZE - 1))

#घोषणा PTRS_PER_IOPGD		(1UL << (32 - IOPGD_SHIFT))
#घोषणा IOPGD_TABLE_SIZE	(PTRS_PER_IOPGD * माप(u32))

/*
 * "small page" address mask and size definitions.
 */
#घोषणा IOPTE_SHIFT		12
#घोषणा IOPTE_SIZE		BIT(IOPTE_SHIFT)
#घोषणा IOPTE_MASK		(~(IOPTE_SIZE - 1))

/*
 * "large page" address mask and size definitions.
 */
#घोषणा IOLARGE_SHIFT		16
#घोषणा IOLARGE_SIZE		BIT(IOLARGE_SHIFT)
#घोषणा IOLARGE_MASK		(~(IOLARGE_SIZE - 1))

#घोषणा PTRS_PER_IOPTE		(1UL << (IOPGD_SHIFT - IOPTE_SHIFT))
#घोषणा IOPTE_TABLE_SIZE	(PTRS_PER_IOPTE * माप(u32))

#घोषणा IOPAGE_MASK		IOPTE_MASK

/**
 * omap_iommu_translate() - va to pa translation
 * @d:		omap iommu descriptor
 * @va:		भव address
 * @mask:	omap iommu descriptor mask
 *
 * va to pa translation
 */
अटल अंतरभूत phys_addr_t omap_iommu_translate(अचिन्हित दीर्घ d, dma_addr_t va,
					       dma_addr_t mask)
अणु
	वापस (d & mask) | (va & (~mask));
पूर्ण

/*
 * some descriptor attributes.
 */
#घोषणा IOPGD_TABLE		(1)
#घोषणा IOPGD_SECTION		(2)
#घोषणा IOPGD_SUPER		(BIT(18) | IOPGD_SECTION)

#घोषणा iopgd_is_table(x)	(((x) & 3) == IOPGD_TABLE)
#घोषणा iopgd_is_section(x)	(((x) & (1 << 18 | 3)) == IOPGD_SECTION)
#घोषणा iopgd_is_super(x)	(((x) & (1 << 18 | 3)) == IOPGD_SUPER)

#घोषणा IOPTE_SMALL		(2)
#घोषणा IOPTE_LARGE		(1)

#घोषणा iopte_is_small(x)	(((x) & 2) == IOPTE_SMALL)
#घोषणा iopte_is_large(x)	(((x) & 3) == IOPTE_LARGE)

/* to find an entry in a page-table-directory */
#घोषणा iopgd_index(da)		(((da) >> IOPGD_SHIFT) & (PTRS_PER_IOPGD - 1))
#घोषणा iopgd_offset(obj, da)	((obj)->iopgd + iopgd_index(da))

#घोषणा iopgd_page_paddr(iopgd)	(*iopgd & ~((1 << 10) - 1))
#घोषणा iopgd_page_vaddr(iopgd)	((u32 *)phys_to_virt(iopgd_page_paddr(iopgd)))

/* to find an entry in the second-level page table. */
#घोषणा iopte_index(da)		(((da) >> IOPTE_SHIFT) & (PTRS_PER_IOPTE - 1))
#घोषणा iopte_offset(iopgd, da)	(iopgd_page_vaddr(iopgd) + iopte_index(da))

#पूर्ण_अगर /* _OMAP_IOPGTABLE_H */
