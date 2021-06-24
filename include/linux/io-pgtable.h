<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __IO_PGTABLE_H
#घोषणा __IO_PGTABLE_H

#समावेश <linux/bitops.h>
#समावेश <linux/iommu.h>

/*
 * Public API क्रम use by IOMMU drivers
 */
क्रमागत io_pgtable_fmt अणु
	ARM_32_LPAE_S1,
	ARM_32_LPAE_S2,
	ARM_64_LPAE_S1,
	ARM_64_LPAE_S2,
	ARM_V7S,
	ARM_MALI_LPAE,
	AMD_IOMMU_V1,
	IO_PGTABLE_NUM_FMTS,
पूर्ण;

/**
 * काष्ठा iommu_flush_ops - IOMMU callbacks क्रम TLB and page table management.
 *
 * @tlb_flush_all:  Synchronously invalidate the entire TLB context.
 * @tlb_flush_walk: Synchronously invalidate all पूर्णांकermediate TLB state
 *                  (someबार referred to as the "walk cache") क्रम a भव
 *                  address range.
 * @tlb_add_page:   Optional callback to queue up leaf TLB invalidation क्रम a
 *                  single page.  IOMMUs that cannot batch TLB invalidation
 *                  operations efficiently will typically issue them here, but
 *                  others may decide to update the iommu_iotlb_gather काष्ठाure
 *                  and defer the invalidation until iommu_iotlb_sync() instead.
 *
 * Note that these can all be called in atomic context and must thereक्रमe
 * not block.
 */
काष्ठा iommu_flush_ops अणु
	व्योम (*tlb_flush_all)(व्योम *cookie);
	व्योम (*tlb_flush_walk)(अचिन्हित दीर्घ iova, माप_प्रकार size, माप_प्रकार granule,
			       व्योम *cookie);
	व्योम (*tlb_add_page)(काष्ठा iommu_iotlb_gather *gather,
			     अचिन्हित दीर्घ iova, माप_प्रकार granule, व्योम *cookie);
पूर्ण;

/**
 * काष्ठा io_pgtable_cfg - Configuration data क्रम a set of page tables.
 *
 * @quirks:        A biपंचांगap of hardware quirks that require some special
 *                 action by the low-level page table allocator.
 * @pgsize_biपंचांगap: A biपंचांगap of page sizes supported by this set of page
 *                 tables.
 * @ias:           Input address (iova) size, in bits.
 * @oas:           Output address (paddr) size, in bits.
 * @coherent_walk  A flag to indicate whether or not page table walks made
 *                 by the IOMMU are coherent with the CPU caches.
 * @tlb:           TLB management callbacks क्रम this set of tables.
 * @iommu_dev:     The device representing the DMA configuration क्रम the
 *                 page table walker.
 */
काष्ठा io_pgtable_cfg अणु
	/*
	 * IO_PGTABLE_QUIRK_ARM_NS: (ARM क्रमmats) Set NS and NSTABLE bits in
	 *	stage 1 PTEs, क्रम hardware which insists on validating them
	 *	even in	non-secure state where they should normally be ignored.
	 *
	 * IO_PGTABLE_QUIRK_NO_PERMS: Ignore the IOMMU_READ, IOMMU_WRITE and
	 *	IOMMU_NOEXEC flags and map everything with full access, क्रम
	 *	hardware which करोes not implement the permissions of a given
	 *	क्रमmat, and/or requires some क्रमmat-specअगरic शेष value.
	 *
	 * IO_PGTABLE_QUIRK_ARM_MTK_EXT: (ARM v7s क्रमmat) MediaTek IOMMUs extend
	 *	to support up to 35 bits PA where the bit32, bit33 and bit34 are
	 *	encoded in the bit9, bit4 and bit5 of the PTE respectively.
	 *
	 * IO_PGTABLE_QUIRK_NON_STRICT: Skip issuing synchronous leaf TLBIs
	 *	on unmap, क्रम DMA करोमुख्यs using the flush queue mechanism क्रम
	 *	delayed invalidation.
	 *
	 * IO_PGTABLE_QUIRK_ARM_TTBR1: (ARM LPAE क्रमmat) Configure the table
	 *	क्रम use in the upper half of a split address space.
	 *
	 * IO_PGTABLE_QUIRK_ARM_OUTER_WBWA: Override the outer-cacheability
	 *	attributes set in the TCR क्रम a non-coherent page-table walker.
	 */
	#घोषणा IO_PGTABLE_QUIRK_ARM_NS		BIT(0)
	#घोषणा IO_PGTABLE_QUIRK_NO_PERMS	BIT(1)
	#घोषणा IO_PGTABLE_QUIRK_ARM_MTK_EXT	BIT(3)
	#घोषणा IO_PGTABLE_QUIRK_NON_STRICT	BIT(4)
	#घोषणा IO_PGTABLE_QUIRK_ARM_TTBR1	BIT(5)
	#घोषणा IO_PGTABLE_QUIRK_ARM_OUTER_WBWA	BIT(6)
	अचिन्हित दीर्घ			quirks;
	अचिन्हित दीर्घ			pgsize_biपंचांगap;
	अचिन्हित पूर्णांक			ias;
	अचिन्हित पूर्णांक			oas;
	bool				coherent_walk;
	स्थिर काष्ठा iommu_flush_ops	*tlb;
	काष्ठा device			*iommu_dev;

	/* Low-level data specअगरic to the table क्रमmat */
	जोड़ अणु
		काष्ठा अणु
			u64	ttbr;
			काष्ठा अणु
				u32	ips:3;
				u32	tg:2;
				u32	sh:2;
				u32	orgn:2;
				u32	irgn:2;
				u32	tsz:6;
			पूर्ण	tcr;
			u64	mair;
		पूर्ण arm_lpae_s1_cfg;

		काष्ठा अणु
			u64	vttbr;
			काष्ठा अणु
				u32	ps:3;
				u32	tg:2;
				u32	sh:2;
				u32	orgn:2;
				u32	irgn:2;
				u32	sl:2;
				u32	tsz:6;
			पूर्ण	vtcr;
		पूर्ण arm_lpae_s2_cfg;

		काष्ठा अणु
			u32	ttbr;
			u32	tcr;
			u32	nmrr;
			u32	prrr;
		पूर्ण arm_v7s_cfg;

		काष्ठा अणु
			u64	transtab;
			u64	memattr;
		पूर्ण arm_mali_lpae_cfg;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा io_pgtable_ops - Page table manipulation API क्रम IOMMU drivers.
 *
 * @map:          Map a physically contiguous memory region.
 * @unmap:        Unmap a physically contiguous memory region.
 * @iova_to_phys: Translate iova to physical address.
 *
 * These functions map directly onto the iommu_ops member functions with
 * the same names.
 */
काष्ठा io_pgtable_ops अणु
	पूर्णांक (*map)(काष्ठा io_pgtable_ops *ops, अचिन्हित दीर्घ iova,
		   phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp);
	माप_प्रकार (*unmap)(काष्ठा io_pgtable_ops *ops, अचिन्हित दीर्घ iova,
			माप_प्रकार size, काष्ठा iommu_iotlb_gather *gather);
	phys_addr_t (*iova_to_phys)(काष्ठा io_pgtable_ops *ops,
				    अचिन्हित दीर्घ iova);
पूर्ण;

/**
 * alloc_io_pgtable_ops() - Allocate a page table allocator क्रम use by an IOMMU.
 *
 * @fmt:    The page table क्रमmat.
 * @cfg:    The page table configuration. This will be modअगरied to represent
 *          the configuration actually provided by the allocator (e.g. the
 *          pgsize_biपंचांगap may be restricted).
 * @cookie: An opaque token provided by the IOMMU driver and passed back to
 *          the callback routines in cfg->tlb.
 */
काष्ठा io_pgtable_ops *alloc_io_pgtable_ops(क्रमागत io_pgtable_fmt fmt,
					    काष्ठा io_pgtable_cfg *cfg,
					    व्योम *cookie);

/**
 * मुक्त_io_pgtable_ops() - Free an io_pgtable_ops काष्ठाure. The caller
 *                         *must* ensure that the page table is no दीर्घer
 *                         live, but the TLB can be dirty.
 *
 * @ops: The ops वापसed from alloc_io_pgtable_ops.
 */
व्योम मुक्त_io_pgtable_ops(काष्ठा io_pgtable_ops *ops);


/*
 * Internal काष्ठाures क्रम page table allocator implementations.
 */

/**
 * काष्ठा io_pgtable - Internal काष्ठाure describing a set of page tables.
 *
 * @fmt:    The page table क्रमmat.
 * @cookie: An opaque token provided by the IOMMU driver and passed back to
 *          any callback routines.
 * @cfg:    A copy of the page table configuration.
 * @ops:    The page table operations in use क्रम this set of page tables.
 */
काष्ठा io_pgtable अणु
	क्रमागत io_pgtable_fmt	fmt;
	व्योम			*cookie;
	काष्ठा io_pgtable_cfg	cfg;
	काष्ठा io_pgtable_ops	ops;
पूर्ण;

#घोषणा io_pgtable_ops_to_pgtable(x) container_of((x), काष्ठा io_pgtable, ops)

अटल अंतरभूत व्योम io_pgtable_tlb_flush_all(काष्ठा io_pgtable *iop)
अणु
	अगर (iop->cfg.tlb && iop->cfg.tlb->tlb_flush_all)
		iop->cfg.tlb->tlb_flush_all(iop->cookie);
पूर्ण

अटल अंतरभूत व्योम
io_pgtable_tlb_flush_walk(काष्ठा io_pgtable *iop, अचिन्हित दीर्घ iova,
			  माप_प्रकार size, माप_प्रकार granule)
अणु
	अगर (iop->cfg.tlb && iop->cfg.tlb->tlb_flush_walk)
		iop->cfg.tlb->tlb_flush_walk(iova, size, granule, iop->cookie);
पूर्ण

अटल अंतरभूत व्योम
io_pgtable_tlb_add_page(काष्ठा io_pgtable *iop,
			काष्ठा iommu_iotlb_gather * gather, अचिन्हित दीर्घ iova,
			माप_प्रकार granule)
अणु
	अगर (iop->cfg.tlb && iop->cfg.tlb->tlb_add_page)
		iop->cfg.tlb->tlb_add_page(gather, iova, granule, iop->cookie);
पूर्ण

/**
 * काष्ठा io_pgtable_init_fns - Alloc/मुक्त a set of page tables क्रम a
 *                              particular क्रमmat.
 *
 * @alloc: Allocate a set of page tables described by cfg.
 * @मुक्त:  Free the page tables associated with iop.
 */
काष्ठा io_pgtable_init_fns अणु
	काष्ठा io_pgtable *(*alloc)(काष्ठा io_pgtable_cfg *cfg, व्योम *cookie);
	व्योम (*मुक्त)(काष्ठा io_pgtable *iop);
पूर्ण;

बाह्य काष्ठा io_pgtable_init_fns io_pgtable_arm_32_lpae_s1_init_fns;
बाह्य काष्ठा io_pgtable_init_fns io_pgtable_arm_32_lpae_s2_init_fns;
बाह्य काष्ठा io_pgtable_init_fns io_pgtable_arm_64_lpae_s1_init_fns;
बाह्य काष्ठा io_pgtable_init_fns io_pgtable_arm_64_lpae_s2_init_fns;
बाह्य काष्ठा io_pgtable_init_fns io_pgtable_arm_v7s_init_fns;
बाह्य काष्ठा io_pgtable_init_fns io_pgtable_arm_mali_lpae_init_fns;
बाह्य काष्ठा io_pgtable_init_fns io_pgtable_amd_iommu_v1_init_fns;

#पूर्ण_अगर /* __IO_PGTABLE_H */
