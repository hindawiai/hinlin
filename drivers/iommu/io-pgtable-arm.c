<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CPU-agnostic ARM page table allocator.
 *
 * Copyright (C) 2014 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#घोषणा pr_fmt(fmt)	"arm-lpae io-pgtable: " fmt

#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/io-pgtable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/barrier.h>

#समावेश "io-pgtable-arm.h"

#घोषणा ARM_LPAE_MAX_ADDR_BITS		52
#घोषणा ARM_LPAE_S2_MAX_CONCAT_PAGES	16
#घोषणा ARM_LPAE_MAX_LEVELS		4

/* Struct accessors */
#घोषणा io_pgtable_to_data(x)						\
	container_of((x), काष्ठा arm_lpae_io_pgtable, iop)

#घोषणा io_pgtable_ops_to_data(x)					\
	io_pgtable_to_data(io_pgtable_ops_to_pgtable(x))

/*
 * Calculate the right shअगरt amount to get to the portion describing level l
 * in a भव address mapped by the pagetable in d.
 */
#घोषणा ARM_LPAE_LVL_SHIFT(l,d)						\
	(((ARM_LPAE_MAX_LEVELS - (l)) * (d)->bits_per_level) +		\
	ilog2(माप(arm_lpae_iopte)))

#घोषणा ARM_LPAE_GRANULE(d)						\
	(माप(arm_lpae_iopte) << (d)->bits_per_level)
#घोषणा ARM_LPAE_PGD_SIZE(d)						\
	(माप(arm_lpae_iopte) << (d)->pgd_bits)

/*
 * Calculate the index at level l used to map भव address a using the
 * pagetable in d.
 */
#घोषणा ARM_LPAE_PGD_IDX(l,d)						\
	((l) == (d)->start_level ? (d)->pgd_bits - (d)->bits_per_level : 0)

#घोषणा ARM_LPAE_LVL_IDX(a,l,d)						\
	(((u64)(a) >> ARM_LPAE_LVL_SHIFT(l,d)) &			\
	 ((1 << ((d)->bits_per_level + ARM_LPAE_PGD_IDX(l,d))) - 1))

/* Calculate the block/page mapping size at level l क्रम pagetable in d. */
#घोषणा ARM_LPAE_BLOCK_SIZE(l,d)	(1ULL << ARM_LPAE_LVL_SHIFT(l,d))

/* Page table bits */
#घोषणा ARM_LPAE_PTE_TYPE_SHIFT		0
#घोषणा ARM_LPAE_PTE_TYPE_MASK		0x3

#घोषणा ARM_LPAE_PTE_TYPE_BLOCK		1
#घोषणा ARM_LPAE_PTE_TYPE_TABLE		3
#घोषणा ARM_LPAE_PTE_TYPE_PAGE		3

#घोषणा ARM_LPAE_PTE_ADDR_MASK		GENMASK_ULL(47,12)

#घोषणा ARM_LPAE_PTE_NSTABLE		(((arm_lpae_iopte)1) << 63)
#घोषणा ARM_LPAE_PTE_XN			(((arm_lpae_iopte)3) << 53)
#घोषणा ARM_LPAE_PTE_AF			(((arm_lpae_iopte)1) << 10)
#घोषणा ARM_LPAE_PTE_SH_NS		(((arm_lpae_iopte)0) << 8)
#घोषणा ARM_LPAE_PTE_SH_OS		(((arm_lpae_iopte)2) << 8)
#घोषणा ARM_LPAE_PTE_SH_IS		(((arm_lpae_iopte)3) << 8)
#घोषणा ARM_LPAE_PTE_NS			(((arm_lpae_iopte)1) << 5)
#घोषणा ARM_LPAE_PTE_VALID		(((arm_lpae_iopte)1) << 0)

#घोषणा ARM_LPAE_PTE_ATTR_LO_MASK	(((arm_lpae_iopte)0x3ff) << 2)
/* Ignore the contiguous bit क्रम block splitting */
#घोषणा ARM_LPAE_PTE_ATTR_HI_MASK	(((arm_lpae_iopte)6) << 52)
#घोषणा ARM_LPAE_PTE_ATTR_MASK		(ARM_LPAE_PTE_ATTR_LO_MASK |	\
					 ARM_LPAE_PTE_ATTR_HI_MASK)
/* Software bit क्रम solving coherency races */
#घोषणा ARM_LPAE_PTE_SW_SYNC		(((arm_lpae_iopte)1) << 55)

/* Stage-1 PTE */
#घोषणा ARM_LPAE_PTE_AP_UNPRIV		(((arm_lpae_iopte)1) << 6)
#घोषणा ARM_LPAE_PTE_AP_RDONLY		(((arm_lpae_iopte)2) << 6)
#घोषणा ARM_LPAE_PTE_ATTRINDX_SHIFT	2
#घोषणा ARM_LPAE_PTE_nG			(((arm_lpae_iopte)1) << 11)

/* Stage-2 PTE */
#घोषणा ARM_LPAE_PTE_HAP_FAULT		(((arm_lpae_iopte)0) << 6)
#घोषणा ARM_LPAE_PTE_HAP_READ		(((arm_lpae_iopte)1) << 6)
#घोषणा ARM_LPAE_PTE_HAP_WRITE		(((arm_lpae_iopte)2) << 6)
#घोषणा ARM_LPAE_PTE_MEMATTR_OIWB	(((arm_lpae_iopte)0xf) << 2)
#घोषणा ARM_LPAE_PTE_MEMATTR_NC		(((arm_lpae_iopte)0x5) << 2)
#घोषणा ARM_LPAE_PTE_MEMATTR_DEV	(((arm_lpae_iopte)0x1) << 2)

/* Register bits */
#घोषणा ARM_LPAE_VTCR_SL0_MASK		0x3

#घोषणा ARM_LPAE_TCR_T0SZ_SHIFT		0

#घोषणा ARM_LPAE_VTCR_PS_SHIFT		16
#घोषणा ARM_LPAE_VTCR_PS_MASK		0x7

#घोषणा ARM_LPAE_MAIR_ATTR_SHIFT(n)	((n) << 3)
#घोषणा ARM_LPAE_MAIR_ATTR_MASK		0xff
#घोषणा ARM_LPAE_MAIR_ATTR_DEVICE	0x04
#घोषणा ARM_LPAE_MAIR_ATTR_NC		0x44
#घोषणा ARM_LPAE_MAIR_ATTR_INC_OWBRWA	0xf4
#घोषणा ARM_LPAE_MAIR_ATTR_WBRWA	0xff
#घोषणा ARM_LPAE_MAIR_ATTR_IDX_NC	0
#घोषणा ARM_LPAE_MAIR_ATTR_IDX_CACHE	1
#घोषणा ARM_LPAE_MAIR_ATTR_IDX_DEV	2
#घोषणा ARM_LPAE_MAIR_ATTR_IDX_INC_OCACHE	3

#घोषणा ARM_MALI_LPAE_TTBR_ADRMODE_TABLE (3u << 0)
#घोषणा ARM_MALI_LPAE_TTBR_READ_INNER	BIT(2)
#घोषणा ARM_MALI_LPAE_TTBR_SHARE_OUTER	BIT(4)

#घोषणा ARM_MALI_LPAE_MEMATTR_IMP_DEF	0x88ULL
#घोषणा ARM_MALI_LPAE_MEMATTR_WRITE_ALLOC 0x8DULL

/* IOPTE accessors */
#घोषणा iopte_deref(pte,d) __va(iopte_to_paddr(pte, d))

#घोषणा iopte_type(pte)					\
	(((pte) >> ARM_LPAE_PTE_TYPE_SHIFT) & ARM_LPAE_PTE_TYPE_MASK)

#घोषणा iopte_prot(pte)	((pte) & ARM_LPAE_PTE_ATTR_MASK)

काष्ठा arm_lpae_io_pgtable अणु
	काष्ठा io_pgtable	iop;

	पूर्णांक			pgd_bits;
	पूर्णांक			start_level;
	पूर्णांक			bits_per_level;

	व्योम			*pgd;
पूर्ण;

प्रकार u64 arm_lpae_iopte;

अटल अंतरभूत bool iopte_leaf(arm_lpae_iopte pte, पूर्णांक lvl,
			      क्रमागत io_pgtable_fmt fmt)
अणु
	अगर (lvl == (ARM_LPAE_MAX_LEVELS - 1) && fmt != ARM_MALI_LPAE)
		वापस iopte_type(pte) == ARM_LPAE_PTE_TYPE_PAGE;

	वापस iopte_type(pte) == ARM_LPAE_PTE_TYPE_BLOCK;
पूर्ण

अटल arm_lpae_iopte paddr_to_iopte(phys_addr_t paddr,
				     काष्ठा arm_lpae_io_pgtable *data)
अणु
	arm_lpae_iopte pte = paddr;

	/* Of the bits which overlap, either 51:48 or 15:12 are always RES0 */
	वापस (pte | (pte >> (48 - 12))) & ARM_LPAE_PTE_ADDR_MASK;
पूर्ण

अटल phys_addr_t iopte_to_paddr(arm_lpae_iopte pte,
				  काष्ठा arm_lpae_io_pgtable *data)
अणु
	u64 paddr = pte & ARM_LPAE_PTE_ADDR_MASK;

	अगर (ARM_LPAE_GRANULE(data) < SZ_64K)
		वापस paddr;

	/* Rotate the packed high-order bits back to the top */
	वापस (paddr | (paddr << (48 - 12))) & (ARM_LPAE_PTE_ADDR_MASK << 4);
पूर्ण

अटल bool selftest_running = false;

अटल dma_addr_t __arm_lpae_dma_addr(व्योम *pages)
अणु
	वापस (dma_addr_t)virt_to_phys(pages);
पूर्ण

अटल व्योम *__arm_lpae_alloc_pages(माप_प्रकार size, gfp_t gfp,
				    काष्ठा io_pgtable_cfg *cfg)
अणु
	काष्ठा device *dev = cfg->iommu_dev;
	पूर्णांक order = get_order(size);
	काष्ठा page *p;
	dma_addr_t dma;
	व्योम *pages;

	VM_BUG_ON((gfp & __GFP_HIGHMEM));
	p = alloc_pages_node(dev ? dev_to_node(dev) : NUMA_NO_NODE,
			     gfp | __GFP_ZERO, order);
	अगर (!p)
		वापस शून्य;

	pages = page_address(p);
	अगर (!cfg->coherent_walk) अणु
		dma = dma_map_single(dev, pages, size, DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, dma))
			जाओ out_मुक्त;
		/*
		 * We depend on the IOMMU being able to work with any physical
		 * address directly, so अगर the DMA layer suggests otherwise by
		 * translating or truncating them, that bodes very badly...
		 */
		अगर (dma != virt_to_phys(pages))
			जाओ out_unmap;
	पूर्ण

	वापस pages;

out_unmap:
	dev_err(dev, "Cannot accommodate DMA translation for IOMMU page tables\n");
	dma_unmap_single(dev, dma, size, DMA_TO_DEVICE);
out_मुक्त:
	__मुक्त_pages(p, order);
	वापस शून्य;
पूर्ण

अटल व्योम __arm_lpae_मुक्त_pages(व्योम *pages, माप_प्रकार size,
				  काष्ठा io_pgtable_cfg *cfg)
अणु
	अगर (!cfg->coherent_walk)
		dma_unmap_single(cfg->iommu_dev, __arm_lpae_dma_addr(pages),
				 size, DMA_TO_DEVICE);
	मुक्त_pages((अचिन्हित दीर्घ)pages, get_order(size));
पूर्ण

अटल व्योम __arm_lpae_sync_pte(arm_lpae_iopte *ptep,
				काष्ठा io_pgtable_cfg *cfg)
अणु
	dma_sync_single_क्रम_device(cfg->iommu_dev, __arm_lpae_dma_addr(ptep),
				   माप(*ptep), DMA_TO_DEVICE);
पूर्ण

अटल व्योम __arm_lpae_set_pte(arm_lpae_iopte *ptep, arm_lpae_iopte pte,
			       काष्ठा io_pgtable_cfg *cfg)
अणु
	*ptep = pte;

	अगर (!cfg->coherent_walk)
		__arm_lpae_sync_pte(ptep, cfg);
पूर्ण

अटल माप_प्रकार __arm_lpae_unmap(काष्ठा arm_lpae_io_pgtable *data,
			       काष्ठा iommu_iotlb_gather *gather,
			       अचिन्हित दीर्घ iova, माप_प्रकार size, पूर्णांक lvl,
			       arm_lpae_iopte *ptep);

अटल व्योम __arm_lpae_init_pte(काष्ठा arm_lpae_io_pgtable *data,
				phys_addr_t paddr, arm_lpae_iopte prot,
				पूर्णांक lvl, arm_lpae_iopte *ptep)
अणु
	arm_lpae_iopte pte = prot;

	अगर (data->iop.fmt != ARM_MALI_LPAE && lvl == ARM_LPAE_MAX_LEVELS - 1)
		pte |= ARM_LPAE_PTE_TYPE_PAGE;
	अन्यथा
		pte |= ARM_LPAE_PTE_TYPE_BLOCK;

	pte |= paddr_to_iopte(paddr, data);

	__arm_lpae_set_pte(ptep, pte, &data->iop.cfg);
पूर्ण

अटल पूर्णांक arm_lpae_init_pte(काष्ठा arm_lpae_io_pgtable *data,
			     अचिन्हित दीर्घ iova, phys_addr_t paddr,
			     arm_lpae_iopte prot, पूर्णांक lvl,
			     arm_lpae_iopte *ptep)
अणु
	arm_lpae_iopte pte = *ptep;

	अगर (iopte_leaf(pte, lvl, data->iop.fmt)) अणु
		/* We require an unmap first */
		WARN_ON(!selftest_running);
		वापस -EEXIST;
	पूर्ण अन्यथा अगर (iopte_type(pte) == ARM_LPAE_PTE_TYPE_TABLE) अणु
		/*
		 * We need to unmap and मुक्त the old table beक्रमe
		 * overwriting it with a block entry.
		 */
		arm_lpae_iopte *tblp;
		माप_प्रकार sz = ARM_LPAE_BLOCK_SIZE(lvl, data);

		tblp = ptep - ARM_LPAE_LVL_IDX(iova, lvl, data);
		अगर (__arm_lpae_unmap(data, शून्य, iova, sz, lvl, tblp) != sz) अणु
			WARN_ON(1);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	__arm_lpae_init_pte(data, paddr, prot, lvl, ptep);
	वापस 0;
पूर्ण

अटल arm_lpae_iopte arm_lpae_install_table(arm_lpae_iopte *table,
					     arm_lpae_iopte *ptep,
					     arm_lpae_iopte curr,
					     काष्ठा io_pgtable_cfg *cfg)
अणु
	arm_lpae_iopte old, new;

	new = __pa(table) | ARM_LPAE_PTE_TYPE_TABLE;
	अगर (cfg->quirks & IO_PGTABLE_QUIRK_ARM_NS)
		new |= ARM_LPAE_PTE_NSTABLE;

	/*
	 * Ensure the table itself is visible beक्रमe its PTE can be.
	 * Whilst we could get away with cmpxchg64_release below, this
	 * करोesn't have any ordering semantics when !CONFIG_SMP.
	 */
	dma_wmb();

	old = cmpxchg64_relaxed(ptep, curr, new);

	अगर (cfg->coherent_walk || (old & ARM_LPAE_PTE_SW_SYNC))
		वापस old;

	/* Even अगर it's not ours, there's no poपूर्णांक रुकोing; just kick it */
	__arm_lpae_sync_pte(ptep, cfg);
	अगर (old == curr)
		WRITE_ONCE(*ptep, new | ARM_LPAE_PTE_SW_SYNC);

	वापस old;
पूर्ण

अटल पूर्णांक __arm_lpae_map(काष्ठा arm_lpae_io_pgtable *data, अचिन्हित दीर्घ iova,
			  phys_addr_t paddr, माप_प्रकार size, arm_lpae_iopte prot,
			  पूर्णांक lvl, arm_lpae_iopte *ptep, gfp_t gfp)
अणु
	arm_lpae_iopte *cptep, pte;
	माप_प्रकार block_size = ARM_LPAE_BLOCK_SIZE(lvl, data);
	माप_प्रकार tblsz = ARM_LPAE_GRANULE(data);
	काष्ठा io_pgtable_cfg *cfg = &data->iop.cfg;

	/* Find our entry at the current level */
	ptep += ARM_LPAE_LVL_IDX(iova, lvl, data);

	/* If we can install a leaf entry at this level, then करो so */
	अगर (size == block_size)
		वापस arm_lpae_init_pte(data, iova, paddr, prot, lvl, ptep);

	/* We can't allocate tables at the final level */
	अगर (WARN_ON(lvl >= ARM_LPAE_MAX_LEVELS - 1))
		वापस -EINVAL;

	/* Grab a poपूर्णांकer to the next level */
	pte = READ_ONCE(*ptep);
	अगर (!pte) अणु
		cptep = __arm_lpae_alloc_pages(tblsz, gfp, cfg);
		अगर (!cptep)
			वापस -ENOMEM;

		pte = arm_lpae_install_table(cptep, ptep, 0, cfg);
		अगर (pte)
			__arm_lpae_मुक्त_pages(cptep, tblsz, cfg);
	पूर्ण अन्यथा अगर (!cfg->coherent_walk && !(pte & ARM_LPAE_PTE_SW_SYNC)) अणु
		__arm_lpae_sync_pte(ptep, cfg);
	पूर्ण

	अगर (pte && !iopte_leaf(pte, lvl, data->iop.fmt)) अणु
		cptep = iopte_deref(pte, data);
	पूर्ण अन्यथा अगर (pte) अणु
		/* We require an unmap first */
		WARN_ON(!selftest_running);
		वापस -EEXIST;
	पूर्ण

	/* Rinse, repeat */
	वापस __arm_lpae_map(data, iova, paddr, size, prot, lvl + 1, cptep, gfp);
पूर्ण

अटल arm_lpae_iopte arm_lpae_prot_to_pte(काष्ठा arm_lpae_io_pgtable *data,
					   पूर्णांक prot)
अणु
	arm_lpae_iopte pte;

	अगर (data->iop.fmt == ARM_64_LPAE_S1 ||
	    data->iop.fmt == ARM_32_LPAE_S1) अणु
		pte = ARM_LPAE_PTE_nG;
		अगर (!(prot & IOMMU_WRITE) && (prot & IOMMU_READ))
			pte |= ARM_LPAE_PTE_AP_RDONLY;
		अगर (!(prot & IOMMU_PRIV))
			pte |= ARM_LPAE_PTE_AP_UNPRIV;
	पूर्ण अन्यथा अणु
		pte = ARM_LPAE_PTE_HAP_FAULT;
		अगर (prot & IOMMU_READ)
			pte |= ARM_LPAE_PTE_HAP_READ;
		अगर (prot & IOMMU_WRITE)
			pte |= ARM_LPAE_PTE_HAP_WRITE;
	पूर्ण

	/*
	 * Note that this logic is काष्ठाured to accommodate Mali LPAE
	 * having stage-1-like attributes but stage-2-like permissions.
	 */
	अगर (data->iop.fmt == ARM_64_LPAE_S2 ||
	    data->iop.fmt == ARM_32_LPAE_S2) अणु
		अगर (prot & IOMMU_MMIO)
			pte |= ARM_LPAE_PTE_MEMATTR_DEV;
		अन्यथा अगर (prot & IOMMU_CACHE)
			pte |= ARM_LPAE_PTE_MEMATTR_OIWB;
		अन्यथा
			pte |= ARM_LPAE_PTE_MEMATTR_NC;
	पूर्ण अन्यथा अणु
		अगर (prot & IOMMU_MMIO)
			pte |= (ARM_LPAE_MAIR_ATTR_IDX_DEV
				<< ARM_LPAE_PTE_ATTRINDX_SHIFT);
		अन्यथा अगर (prot & IOMMU_CACHE)
			pte |= (ARM_LPAE_MAIR_ATTR_IDX_CACHE
				<< ARM_LPAE_PTE_ATTRINDX_SHIFT);
	पूर्ण

	/*
	 * Also Mali has its own notions of shareability wherein its Inner
	 * करोमुख्य covers the cores within the GPU, and its Outer करोमुख्य is
	 * "outside the GPU" (i.e. either the Inner or System करोमुख्य in CPU
	 * terms, depending on coherency).
	 */
	अगर (prot & IOMMU_CACHE && data->iop.fmt != ARM_MALI_LPAE)
		pte |= ARM_LPAE_PTE_SH_IS;
	अन्यथा
		pte |= ARM_LPAE_PTE_SH_OS;

	अगर (prot & IOMMU_NOEXEC)
		pte |= ARM_LPAE_PTE_XN;

	अगर (data->iop.cfg.quirks & IO_PGTABLE_QUIRK_ARM_NS)
		pte |= ARM_LPAE_PTE_NS;

	अगर (data->iop.fmt != ARM_MALI_LPAE)
		pte |= ARM_LPAE_PTE_AF;

	वापस pte;
पूर्ण

अटल पूर्णांक arm_lpae_map(काष्ठा io_pgtable_ops *ops, अचिन्हित दीर्घ iova,
			phys_addr_t paddr, माप_प्रकार size, पूर्णांक iommu_prot, gfp_t gfp)
अणु
	काष्ठा arm_lpae_io_pgtable *data = io_pgtable_ops_to_data(ops);
	काष्ठा io_pgtable_cfg *cfg = &data->iop.cfg;
	arm_lpae_iopte *ptep = data->pgd;
	पूर्णांक ret, lvl = data->start_level;
	arm_lpae_iopte prot;
	दीर्घ iaext = (s64)iova >> cfg->ias;

	अगर (WARN_ON(!size || (size & cfg->pgsize_biपंचांगap) != size))
		वापस -EINVAL;

	अगर (cfg->quirks & IO_PGTABLE_QUIRK_ARM_TTBR1)
		iaext = ~iaext;
	अगर (WARN_ON(iaext || paddr >> cfg->oas))
		वापस -दुस्फल;

	/* If no access, then nothing to करो */
	अगर (!(iommu_prot & (IOMMU_READ | IOMMU_WRITE)))
		वापस 0;

	prot = arm_lpae_prot_to_pte(data, iommu_prot);
	ret = __arm_lpae_map(data, iova, paddr, size, prot, lvl, ptep, gfp);
	/*
	 * Synchronise all PTE updates क्रम the new mapping beक्रमe there's
	 * a chance क्रम anything to kick off a table walk क्रम the new iova.
	 */
	wmb();

	वापस ret;
पूर्ण

अटल व्योम __arm_lpae_मुक्त_pgtable(काष्ठा arm_lpae_io_pgtable *data, पूर्णांक lvl,
				    arm_lpae_iopte *ptep)
अणु
	arm_lpae_iopte *start, *end;
	अचिन्हित दीर्घ table_size;

	अगर (lvl == data->start_level)
		table_size = ARM_LPAE_PGD_SIZE(data);
	अन्यथा
		table_size = ARM_LPAE_GRANULE(data);

	start = ptep;

	/* Only leaf entries at the last level */
	अगर (lvl == ARM_LPAE_MAX_LEVELS - 1)
		end = ptep;
	अन्यथा
		end = (व्योम *)ptep + table_size;

	जबतक (ptep != end) अणु
		arm_lpae_iopte pte = *ptep++;

		अगर (!pte || iopte_leaf(pte, lvl, data->iop.fmt))
			जारी;

		__arm_lpae_मुक्त_pgtable(data, lvl + 1, iopte_deref(pte, data));
	पूर्ण

	__arm_lpae_मुक्त_pages(start, table_size, &data->iop.cfg);
पूर्ण

अटल व्योम arm_lpae_मुक्त_pgtable(काष्ठा io_pgtable *iop)
अणु
	काष्ठा arm_lpae_io_pgtable *data = io_pgtable_to_data(iop);

	__arm_lpae_मुक्त_pgtable(data, data->start_level, data->pgd);
	kमुक्त(data);
पूर्ण

अटल माप_प्रकार arm_lpae_split_blk_unmap(काष्ठा arm_lpae_io_pgtable *data,
				       काष्ठा iommu_iotlb_gather *gather,
				       अचिन्हित दीर्घ iova, माप_प्रकार size,
				       arm_lpae_iopte blk_pte, पूर्णांक lvl,
				       arm_lpae_iopte *ptep)
अणु
	काष्ठा io_pgtable_cfg *cfg = &data->iop.cfg;
	arm_lpae_iopte pte, *tablep;
	phys_addr_t blk_paddr;
	माप_प्रकार tablesz = ARM_LPAE_GRANULE(data);
	माप_प्रकार split_sz = ARM_LPAE_BLOCK_SIZE(lvl, data);
	पूर्णांक i, unmap_idx = -1;

	अगर (WARN_ON(lvl == ARM_LPAE_MAX_LEVELS))
		वापस 0;

	tablep = __arm_lpae_alloc_pages(tablesz, GFP_ATOMIC, cfg);
	अगर (!tablep)
		वापस 0; /* Bytes unmapped */

	अगर (size == split_sz)
		unmap_idx = ARM_LPAE_LVL_IDX(iova, lvl, data);

	blk_paddr = iopte_to_paddr(blk_pte, data);
	pte = iopte_prot(blk_pte);

	क्रम (i = 0; i < tablesz / माप(pte); i++, blk_paddr += split_sz) अणु
		/* Unmap! */
		अगर (i == unmap_idx)
			जारी;

		__arm_lpae_init_pte(data, blk_paddr, pte, lvl, &tablep[i]);
	पूर्ण

	pte = arm_lpae_install_table(tablep, ptep, blk_pte, cfg);
	अगर (pte != blk_pte) अणु
		__arm_lpae_मुक्त_pages(tablep, tablesz, cfg);
		/*
		 * We may race against someone unmapping another part of this
		 * block, but anything अन्यथा is invalid. We can't misपूर्णांकerpret
		 * a page entry here since we're never at the last level.
		 */
		अगर (iopte_type(pte) != ARM_LPAE_PTE_TYPE_TABLE)
			वापस 0;

		tablep = iopte_deref(pte, data);
	पूर्ण अन्यथा अगर (unmap_idx >= 0) अणु
		io_pgtable_tlb_add_page(&data->iop, gather, iova, size);
		वापस size;
	पूर्ण

	वापस __arm_lpae_unmap(data, gather, iova, size, lvl, tablep);
पूर्ण

अटल माप_प्रकार __arm_lpae_unmap(काष्ठा arm_lpae_io_pgtable *data,
			       काष्ठा iommu_iotlb_gather *gather,
			       अचिन्हित दीर्घ iova, माप_प्रकार size, पूर्णांक lvl,
			       arm_lpae_iopte *ptep)
अणु
	arm_lpae_iopte pte;
	काष्ठा io_pgtable *iop = &data->iop;

	/* Something went horribly wrong and we ran out of page table */
	अगर (WARN_ON(lvl == ARM_LPAE_MAX_LEVELS))
		वापस 0;

	ptep += ARM_LPAE_LVL_IDX(iova, lvl, data);
	pte = READ_ONCE(*ptep);
	अगर (WARN_ON(!pte))
		वापस 0;

	/* If the size matches this level, we're in the right place */
	अगर (size == ARM_LPAE_BLOCK_SIZE(lvl, data)) अणु
		__arm_lpae_set_pte(ptep, 0, &iop->cfg);

		अगर (!iopte_leaf(pte, lvl, iop->fmt)) अणु
			/* Also flush any partial walks */
			io_pgtable_tlb_flush_walk(iop, iova, size,
						  ARM_LPAE_GRANULE(data));
			ptep = iopte_deref(pte, data);
			__arm_lpae_मुक्त_pgtable(data, lvl + 1, ptep);
		पूर्ण अन्यथा अगर (iop->cfg.quirks & IO_PGTABLE_QUIRK_NON_STRICT) अणु
			/*
			 * Order the PTE update against queueing the IOVA, to
			 * guarantee that a flush callback from a dअगरferent CPU
			 * has observed it beक्रमe the TLBIALL can be issued.
			 */
			smp_wmb();
		पूर्ण अन्यथा अणु
			io_pgtable_tlb_add_page(iop, gather, iova, size);
		पूर्ण

		वापस size;
	पूर्ण अन्यथा अगर (iopte_leaf(pte, lvl, iop->fmt)) अणु
		/*
		 * Insert a table at the next level to map the old region,
		 * minus the part we want to unmap
		 */
		वापस arm_lpae_split_blk_unmap(data, gather, iova, size, pte,
						lvl + 1, ptep);
	पूर्ण

	/* Keep on walkin' */
	ptep = iopte_deref(pte, data);
	वापस __arm_lpae_unmap(data, gather, iova, size, lvl + 1, ptep);
पूर्ण

अटल माप_प्रकार arm_lpae_unmap(काष्ठा io_pgtable_ops *ops, अचिन्हित दीर्घ iova,
			     माप_प्रकार size, काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा arm_lpae_io_pgtable *data = io_pgtable_ops_to_data(ops);
	काष्ठा io_pgtable_cfg *cfg = &data->iop.cfg;
	arm_lpae_iopte *ptep = data->pgd;
	दीर्घ iaext = (s64)iova >> cfg->ias;

	अगर (WARN_ON(!size || (size & cfg->pgsize_biपंचांगap) != size))
		वापस 0;

	अगर (cfg->quirks & IO_PGTABLE_QUIRK_ARM_TTBR1)
		iaext = ~iaext;
	अगर (WARN_ON(iaext))
		वापस 0;

	वापस __arm_lpae_unmap(data, gather, iova, size, data->start_level, ptep);
पूर्ण

अटल phys_addr_t arm_lpae_iova_to_phys(काष्ठा io_pgtable_ops *ops,
					 अचिन्हित दीर्घ iova)
अणु
	काष्ठा arm_lpae_io_pgtable *data = io_pgtable_ops_to_data(ops);
	arm_lpae_iopte pte, *ptep = data->pgd;
	पूर्णांक lvl = data->start_level;

	करो अणु
		/* Valid IOPTE poपूर्णांकer? */
		अगर (!ptep)
			वापस 0;

		/* Grab the IOPTE we're पूर्णांकerested in */
		ptep += ARM_LPAE_LVL_IDX(iova, lvl, data);
		pte = READ_ONCE(*ptep);

		/* Valid entry? */
		अगर (!pte)
			वापस 0;

		/* Leaf entry? */
		अगर (iopte_leaf(pte, lvl, data->iop.fmt))
			जाओ found_translation;

		/* Take it to the next level */
		ptep = iopte_deref(pte, data);
	पूर्ण जबतक (++lvl < ARM_LPAE_MAX_LEVELS);

	/* Ran out of page tables to walk */
	वापस 0;

found_translation:
	iova &= (ARM_LPAE_BLOCK_SIZE(lvl, data) - 1);
	वापस iopte_to_paddr(pte, data) | iova;
पूर्ण

अटल व्योम arm_lpae_restrict_pgsizes(काष्ठा io_pgtable_cfg *cfg)
अणु
	अचिन्हित दीर्घ granule, page_sizes;
	अचिन्हित पूर्णांक max_addr_bits = 48;

	/*
	 * We need to restrict the supported page sizes to match the
	 * translation regime क्रम a particular granule. Aim to match
	 * the CPU page size अगर possible, otherwise prefer smaller sizes.
	 * While we're at it, restrict the block sizes to match the
	 * chosen granule.
	 */
	अगर (cfg->pgsize_biपंचांगap & PAGE_SIZE)
		granule = PAGE_SIZE;
	अन्यथा अगर (cfg->pgsize_biपंचांगap & ~PAGE_MASK)
		granule = 1UL << __fls(cfg->pgsize_biपंचांगap & ~PAGE_MASK);
	अन्यथा अगर (cfg->pgsize_biपंचांगap & PAGE_MASK)
		granule = 1UL << __ffs(cfg->pgsize_biपंचांगap & PAGE_MASK);
	अन्यथा
		granule = 0;

	चयन (granule) अणु
	हाल SZ_4K:
		page_sizes = (SZ_4K | SZ_2M | SZ_1G);
		अवरोध;
	हाल SZ_16K:
		page_sizes = (SZ_16K | SZ_32M);
		अवरोध;
	हाल SZ_64K:
		max_addr_bits = 52;
		page_sizes = (SZ_64K | SZ_512M);
		अगर (cfg->oas > 48)
			page_sizes |= 1ULL << 42; /* 4TB */
		अवरोध;
	शेष:
		page_sizes = 0;
	पूर्ण

	cfg->pgsize_biपंचांगap &= page_sizes;
	cfg->ias = min(cfg->ias, max_addr_bits);
	cfg->oas = min(cfg->oas, max_addr_bits);
पूर्ण

अटल काष्ठा arm_lpae_io_pgtable *
arm_lpae_alloc_pgtable(काष्ठा io_pgtable_cfg *cfg)
अणु
	काष्ठा arm_lpae_io_pgtable *data;
	पूर्णांक levels, va_bits, pg_shअगरt;

	arm_lpae_restrict_pgsizes(cfg);

	अगर (!(cfg->pgsize_biपंचांगap & (SZ_4K | SZ_16K | SZ_64K)))
		वापस शून्य;

	अगर (cfg->ias > ARM_LPAE_MAX_ADDR_BITS)
		वापस शून्य;

	अगर (cfg->oas > ARM_LPAE_MAX_ADDR_BITS)
		वापस शून्य;

	data = kदो_स्मृति(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस शून्य;

	pg_shअगरt = __ffs(cfg->pgsize_biपंचांगap);
	data->bits_per_level = pg_shअगरt - ilog2(माप(arm_lpae_iopte));

	va_bits = cfg->ias - pg_shअगरt;
	levels = DIV_ROUND_UP(va_bits, data->bits_per_level);
	data->start_level = ARM_LPAE_MAX_LEVELS - levels;

	/* Calculate the actual size of our pgd (without concatenation) */
	data->pgd_bits = va_bits - (data->bits_per_level * (levels - 1));

	data->iop.ops = (काष्ठा io_pgtable_ops) अणु
		.map		= arm_lpae_map,
		.unmap		= arm_lpae_unmap,
		.iova_to_phys	= arm_lpae_iova_to_phys,
	पूर्ण;

	वापस data;
पूर्ण

अटल काष्ठा io_pgtable *
arm_64_lpae_alloc_pgtable_s1(काष्ठा io_pgtable_cfg *cfg, व्योम *cookie)
अणु
	u64 reg;
	काष्ठा arm_lpae_io_pgtable *data;
	typeof(&cfg->arm_lpae_s1_cfg.tcr) tcr = &cfg->arm_lpae_s1_cfg.tcr;
	bool tg1;

	अगर (cfg->quirks & ~(IO_PGTABLE_QUIRK_ARM_NS |
			    IO_PGTABLE_QUIRK_NON_STRICT |
			    IO_PGTABLE_QUIRK_ARM_TTBR1 |
			    IO_PGTABLE_QUIRK_ARM_OUTER_WBWA))
		वापस शून्य;

	data = arm_lpae_alloc_pgtable(cfg);
	अगर (!data)
		वापस शून्य;

	/* TCR */
	अगर (cfg->coherent_walk) अणु
		tcr->sh = ARM_LPAE_TCR_SH_IS;
		tcr->irgn = ARM_LPAE_TCR_RGN_WBWA;
		tcr->orgn = ARM_LPAE_TCR_RGN_WBWA;
		अगर (cfg->quirks & IO_PGTABLE_QUIRK_ARM_OUTER_WBWA)
			जाओ out_मुक्त_data;
	पूर्ण अन्यथा अणु
		tcr->sh = ARM_LPAE_TCR_SH_OS;
		tcr->irgn = ARM_LPAE_TCR_RGN_NC;
		अगर (!(cfg->quirks & IO_PGTABLE_QUIRK_ARM_OUTER_WBWA))
			tcr->orgn = ARM_LPAE_TCR_RGN_NC;
		अन्यथा
			tcr->orgn = ARM_LPAE_TCR_RGN_WBWA;
	पूर्ण

	tg1 = cfg->quirks & IO_PGTABLE_QUIRK_ARM_TTBR1;
	चयन (ARM_LPAE_GRANULE(data)) अणु
	हाल SZ_4K:
		tcr->tg = tg1 ? ARM_LPAE_TCR_TG1_4K : ARM_LPAE_TCR_TG0_4K;
		अवरोध;
	हाल SZ_16K:
		tcr->tg = tg1 ? ARM_LPAE_TCR_TG1_16K : ARM_LPAE_TCR_TG0_16K;
		अवरोध;
	हाल SZ_64K:
		tcr->tg = tg1 ? ARM_LPAE_TCR_TG1_64K : ARM_LPAE_TCR_TG0_64K;
		अवरोध;
	पूर्ण

	चयन (cfg->oas) अणु
	हाल 32:
		tcr->ips = ARM_LPAE_TCR_PS_32_BIT;
		अवरोध;
	हाल 36:
		tcr->ips = ARM_LPAE_TCR_PS_36_BIT;
		अवरोध;
	हाल 40:
		tcr->ips = ARM_LPAE_TCR_PS_40_BIT;
		अवरोध;
	हाल 42:
		tcr->ips = ARM_LPAE_TCR_PS_42_BIT;
		अवरोध;
	हाल 44:
		tcr->ips = ARM_LPAE_TCR_PS_44_BIT;
		अवरोध;
	हाल 48:
		tcr->ips = ARM_LPAE_TCR_PS_48_BIT;
		अवरोध;
	हाल 52:
		tcr->ips = ARM_LPAE_TCR_PS_52_BIT;
		अवरोध;
	शेष:
		जाओ out_मुक्त_data;
	पूर्ण

	tcr->tsz = 64ULL - cfg->ias;

	/* MAIRs */
	reg = (ARM_LPAE_MAIR_ATTR_NC
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_NC)) |
	      (ARM_LPAE_MAIR_ATTR_WBRWA
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_CACHE)) |
	      (ARM_LPAE_MAIR_ATTR_DEVICE
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_DEV)) |
	      (ARM_LPAE_MAIR_ATTR_INC_OWBRWA
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_INC_OCACHE));

	cfg->arm_lpae_s1_cfg.mair = reg;

	/* Looking good; allocate a pgd */
	data->pgd = __arm_lpae_alloc_pages(ARM_LPAE_PGD_SIZE(data),
					   GFP_KERNEL, cfg);
	अगर (!data->pgd)
		जाओ out_मुक्त_data;

	/* Ensure the empty pgd is visible beक्रमe any actual TTBR ग_लिखो */
	wmb();

	/* TTBR */
	cfg->arm_lpae_s1_cfg.ttbr = virt_to_phys(data->pgd);
	वापस &data->iop;

out_मुक्त_data:
	kमुक्त(data);
	वापस शून्य;
पूर्ण

अटल काष्ठा io_pgtable *
arm_64_lpae_alloc_pgtable_s2(काष्ठा io_pgtable_cfg *cfg, व्योम *cookie)
अणु
	u64 sl;
	काष्ठा arm_lpae_io_pgtable *data;
	typeof(&cfg->arm_lpae_s2_cfg.vtcr) vtcr = &cfg->arm_lpae_s2_cfg.vtcr;

	/* The NS quirk करोesn't apply at stage 2 */
	अगर (cfg->quirks & ~(IO_PGTABLE_QUIRK_NON_STRICT))
		वापस शून्य;

	data = arm_lpae_alloc_pgtable(cfg);
	अगर (!data)
		वापस शून्य;

	/*
	 * Concatenate PGDs at level 1 अगर possible in order to reduce
	 * the depth of the stage-2 walk.
	 */
	अगर (data->start_level == 0) अणु
		अचिन्हित दीर्घ pgd_pages;

		pgd_pages = ARM_LPAE_PGD_SIZE(data) / माप(arm_lpae_iopte);
		अगर (pgd_pages <= ARM_LPAE_S2_MAX_CONCAT_PAGES) अणु
			data->pgd_bits += data->bits_per_level;
			data->start_level++;
		पूर्ण
	पूर्ण

	/* VTCR */
	अगर (cfg->coherent_walk) अणु
		vtcr->sh = ARM_LPAE_TCR_SH_IS;
		vtcr->irgn = ARM_LPAE_TCR_RGN_WBWA;
		vtcr->orgn = ARM_LPAE_TCR_RGN_WBWA;
	पूर्ण अन्यथा अणु
		vtcr->sh = ARM_LPAE_TCR_SH_OS;
		vtcr->irgn = ARM_LPAE_TCR_RGN_NC;
		vtcr->orgn = ARM_LPAE_TCR_RGN_NC;
	पूर्ण

	sl = data->start_level;

	चयन (ARM_LPAE_GRANULE(data)) अणु
	हाल SZ_4K:
		vtcr->tg = ARM_LPAE_TCR_TG0_4K;
		sl++; /* SL0 क्रमmat is dअगरferent क्रम 4K granule size */
		अवरोध;
	हाल SZ_16K:
		vtcr->tg = ARM_LPAE_TCR_TG0_16K;
		अवरोध;
	हाल SZ_64K:
		vtcr->tg = ARM_LPAE_TCR_TG0_64K;
		अवरोध;
	पूर्ण

	चयन (cfg->oas) अणु
	हाल 32:
		vtcr->ps = ARM_LPAE_TCR_PS_32_BIT;
		अवरोध;
	हाल 36:
		vtcr->ps = ARM_LPAE_TCR_PS_36_BIT;
		अवरोध;
	हाल 40:
		vtcr->ps = ARM_LPAE_TCR_PS_40_BIT;
		अवरोध;
	हाल 42:
		vtcr->ps = ARM_LPAE_TCR_PS_42_BIT;
		अवरोध;
	हाल 44:
		vtcr->ps = ARM_LPAE_TCR_PS_44_BIT;
		अवरोध;
	हाल 48:
		vtcr->ps = ARM_LPAE_TCR_PS_48_BIT;
		अवरोध;
	हाल 52:
		vtcr->ps = ARM_LPAE_TCR_PS_52_BIT;
		अवरोध;
	शेष:
		जाओ out_मुक्त_data;
	पूर्ण

	vtcr->tsz = 64ULL - cfg->ias;
	vtcr->sl = ~sl & ARM_LPAE_VTCR_SL0_MASK;

	/* Allocate pgd pages */
	data->pgd = __arm_lpae_alloc_pages(ARM_LPAE_PGD_SIZE(data),
					   GFP_KERNEL, cfg);
	अगर (!data->pgd)
		जाओ out_मुक्त_data;

	/* Ensure the empty pgd is visible beक्रमe any actual TTBR ग_लिखो */
	wmb();

	/* VTTBR */
	cfg->arm_lpae_s2_cfg.vttbr = virt_to_phys(data->pgd);
	वापस &data->iop;

out_मुक्त_data:
	kमुक्त(data);
	वापस शून्य;
पूर्ण

अटल काष्ठा io_pgtable *
arm_32_lpae_alloc_pgtable_s1(काष्ठा io_pgtable_cfg *cfg, व्योम *cookie)
अणु
	अगर (cfg->ias > 32 || cfg->oas > 40)
		वापस शून्य;

	cfg->pgsize_biपंचांगap &= (SZ_4K | SZ_2M | SZ_1G);
	वापस arm_64_lpae_alloc_pgtable_s1(cfg, cookie);
पूर्ण

अटल काष्ठा io_pgtable *
arm_32_lpae_alloc_pgtable_s2(काष्ठा io_pgtable_cfg *cfg, व्योम *cookie)
अणु
	अगर (cfg->ias > 40 || cfg->oas > 40)
		वापस शून्य;

	cfg->pgsize_biपंचांगap &= (SZ_4K | SZ_2M | SZ_1G);
	वापस arm_64_lpae_alloc_pgtable_s2(cfg, cookie);
पूर्ण

अटल काष्ठा io_pgtable *
arm_mali_lpae_alloc_pgtable(काष्ठा io_pgtable_cfg *cfg, व्योम *cookie)
अणु
	काष्ठा arm_lpae_io_pgtable *data;

	/* No quirks क्रम Mali (hopefully) */
	अगर (cfg->quirks)
		वापस शून्य;

	अगर (cfg->ias > 48 || cfg->oas > 40)
		वापस शून्य;

	cfg->pgsize_biपंचांगap &= (SZ_4K | SZ_2M | SZ_1G);

	data = arm_lpae_alloc_pgtable(cfg);
	अगर (!data)
		वापस शून्य;

	/* Mali seems to need a full 4-level table regardless of IAS */
	अगर (data->start_level > 0) अणु
		data->start_level = 0;
		data->pgd_bits = 0;
	पूर्ण
	/*
	 * MEMATTR: Mali has no actual notion of a non-cacheable type, so the
	 * best we can करो is mimic the out-of-tree driver and hope that the
	 * "implementation-defined caching policy" is good enough. Similarly,
	 * we'll use it for the sake of a valid attribute for our 'device'
	 * index, although callers should never request that in practice.
	 */
	cfg->arm_mali_lpae_cfg.memattr =
		(ARM_MALI_LPAE_MEMATTR_IMP_DEF
		 << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_NC)) |
		(ARM_MALI_LPAE_MEMATTR_WRITE_ALLOC
		 << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_CACHE)) |
		(ARM_MALI_LPAE_MEMATTR_IMP_DEF
		 << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_DEV));

	data->pgd = __arm_lpae_alloc_pages(ARM_LPAE_PGD_SIZE(data), GFP_KERNEL,
					   cfg);
	अगर (!data->pgd)
		जाओ out_मुक्त_data;

	/* Ensure the empty pgd is visible beक्रमe TRANSTAB can be written */
	wmb();

	cfg->arm_mali_lpae_cfg.transtab = virt_to_phys(data->pgd) |
					  ARM_MALI_LPAE_TTBR_READ_INNER |
					  ARM_MALI_LPAE_TTBR_ADRMODE_TABLE;
	अगर (cfg->coherent_walk)
		cfg->arm_mali_lpae_cfg.transtab |= ARM_MALI_LPAE_TTBR_SHARE_OUTER;

	वापस &data->iop;

out_मुक्त_data:
	kमुक्त(data);
	वापस शून्य;
पूर्ण

काष्ठा io_pgtable_init_fns io_pgtable_arm_64_lpae_s1_init_fns = अणु
	.alloc	= arm_64_lpae_alloc_pgtable_s1,
	.मुक्त	= arm_lpae_मुक्त_pgtable,
पूर्ण;

काष्ठा io_pgtable_init_fns io_pgtable_arm_64_lpae_s2_init_fns = अणु
	.alloc	= arm_64_lpae_alloc_pgtable_s2,
	.मुक्त	= arm_lpae_मुक्त_pgtable,
पूर्ण;

काष्ठा io_pgtable_init_fns io_pgtable_arm_32_lpae_s1_init_fns = अणु
	.alloc	= arm_32_lpae_alloc_pgtable_s1,
	.मुक्त	= arm_lpae_मुक्त_pgtable,
पूर्ण;

काष्ठा io_pgtable_init_fns io_pgtable_arm_32_lpae_s2_init_fns = अणु
	.alloc	= arm_32_lpae_alloc_pgtable_s2,
	.मुक्त	= arm_lpae_मुक्त_pgtable,
पूर्ण;

काष्ठा io_pgtable_init_fns io_pgtable_arm_mali_lpae_init_fns = अणु
	.alloc	= arm_mali_lpae_alloc_pgtable,
	.मुक्त	= arm_lpae_मुक्त_pgtable,
पूर्ण;

#अगर_घोषित CONFIG_IOMMU_IO_PGTABLE_LPAE_SELFTEST

अटल काष्ठा io_pgtable_cfg *cfg_cookie __initdata;

अटल व्योम __init dummy_tlb_flush_all(व्योम *cookie)
अणु
	WARN_ON(cookie != cfg_cookie);
पूर्ण

अटल व्योम __init dummy_tlb_flush(अचिन्हित दीर्घ iova, माप_प्रकार size,
				   माप_प्रकार granule, व्योम *cookie)
अणु
	WARN_ON(cookie != cfg_cookie);
	WARN_ON(!(size & cfg_cookie->pgsize_biपंचांगap));
पूर्ण

अटल व्योम __init dummy_tlb_add_page(काष्ठा iommu_iotlb_gather *gather,
				      अचिन्हित दीर्घ iova, माप_प्रकार granule,
				      व्योम *cookie)
अणु
	dummy_tlb_flush(iova, granule, granule, cookie);
पूर्ण

अटल स्थिर काष्ठा iommu_flush_ops dummy_tlb_ops __initस्थिर = अणु
	.tlb_flush_all	= dummy_tlb_flush_all,
	.tlb_flush_walk	= dummy_tlb_flush,
	.tlb_add_page	= dummy_tlb_add_page,
पूर्ण;

अटल व्योम __init arm_lpae_dump_ops(काष्ठा io_pgtable_ops *ops)
अणु
	काष्ठा arm_lpae_io_pgtable *data = io_pgtable_ops_to_data(ops);
	काष्ठा io_pgtable_cfg *cfg = &data->iop.cfg;

	pr_err("cfg: pgsize_bitmap 0x%lx, ias %u-bit\n",
		cfg->pgsize_biपंचांगap, cfg->ias);
	pr_err("data: %d levels, 0x%zx pgd_size, %u pg_shift, %u bits_per_level, pgd @ %p\n",
		ARM_LPAE_MAX_LEVELS - data->start_level, ARM_LPAE_PGD_SIZE(data),
		ilog2(ARM_LPAE_GRANULE(data)), data->bits_per_level, data->pgd);
पूर्ण

#घोषणा __FAIL(ops, i)	(अणु						\
		WARN(1, "selftest: test failed for fmt idx %d\n", (i));	\
		arm_lpae_dump_ops(ops);					\
		selftest_running = false;				\
		-EFAULT;						\
पूर्ण)

अटल पूर्णांक __init arm_lpae_run_tests(काष्ठा io_pgtable_cfg *cfg)
अणु
	अटल स्थिर क्रमागत io_pgtable_fmt fmts[] __initस्थिर = अणु
		ARM_64_LPAE_S1,
		ARM_64_LPAE_S2,
	पूर्ण;

	पूर्णांक i, j;
	अचिन्हित दीर्घ iova;
	माप_प्रकार size;
	काष्ठा io_pgtable_ops *ops;

	selftest_running = true;

	क्रम (i = 0; i < ARRAY_SIZE(fmts); ++i) अणु
		cfg_cookie = cfg;
		ops = alloc_io_pgtable_ops(fmts[i], cfg, cfg);
		अगर (!ops) अणु
			pr_err("selftest: failed to allocate io pgtable ops\n");
			वापस -ENOMEM;
		पूर्ण

		/*
		 * Initial sanity checks.
		 * Empty page tables shouldn't provide any translations.
		 */
		अगर (ops->iova_to_phys(ops, 42))
			वापस __FAIL(ops, i);

		अगर (ops->iova_to_phys(ops, SZ_1G + 42))
			वापस __FAIL(ops, i);

		अगर (ops->iova_to_phys(ops, SZ_2G + 42))
			वापस __FAIL(ops, i);

		/*
		 * Distinct mappings of dअगरferent granule sizes.
		 */
		iova = 0;
		क्रम_each_set_bit(j, &cfg->pgsize_biपंचांगap, BITS_PER_LONG) अणु
			size = 1UL << j;

			अगर (ops->map(ops, iova, iova, size, IOMMU_READ |
							    IOMMU_WRITE |
							    IOMMU_NOEXEC |
							    IOMMU_CACHE, GFP_KERNEL))
				वापस __FAIL(ops, i);

			/* Overlapping mappings */
			अगर (!ops->map(ops, iova, iova + size, size,
				      IOMMU_READ | IOMMU_NOEXEC, GFP_KERNEL))
				वापस __FAIL(ops, i);

			अगर (ops->iova_to_phys(ops, iova + 42) != (iova + 42))
				वापस __FAIL(ops, i);

			iova += SZ_1G;
		पूर्ण

		/* Partial unmap */
		size = 1UL << __ffs(cfg->pgsize_biपंचांगap);
		अगर (ops->unmap(ops, SZ_1G + size, size, शून्य) != size)
			वापस __FAIL(ops, i);

		/* Remap of partial unmap */
		अगर (ops->map(ops, SZ_1G + size, size, size, IOMMU_READ, GFP_KERNEL))
			वापस __FAIL(ops, i);

		अगर (ops->iova_to_phys(ops, SZ_1G + size + 42) != (size + 42))
			वापस __FAIL(ops, i);

		/* Full unmap */
		iova = 0;
		क्रम_each_set_bit(j, &cfg->pgsize_biपंचांगap, BITS_PER_LONG) अणु
			size = 1UL << j;

			अगर (ops->unmap(ops, iova, size, शून्य) != size)
				वापस __FAIL(ops, i);

			अगर (ops->iova_to_phys(ops, iova + 42))
				वापस __FAIL(ops, i);

			/* Remap full block */
			अगर (ops->map(ops, iova, iova, size, IOMMU_WRITE, GFP_KERNEL))
				वापस __FAIL(ops, i);

			अगर (ops->iova_to_phys(ops, iova + 42) != (iova + 42))
				वापस __FAIL(ops, i);

			iova += SZ_1G;
		पूर्ण

		मुक्त_io_pgtable_ops(ops);
	पूर्ण

	selftest_running = false;
	वापस 0;
पूर्ण

अटल पूर्णांक __init arm_lpae_करो_selftests(व्योम)
अणु
	अटल स्थिर अचिन्हित दीर्घ pgsize[] __initस्थिर = अणु
		SZ_4K | SZ_2M | SZ_1G,
		SZ_16K | SZ_32M,
		SZ_64K | SZ_512M,
	पूर्ण;

	अटल स्थिर अचिन्हित पूर्णांक ias[] __initस्थिर = अणु
		32, 36, 40, 42, 44, 48,
	पूर्ण;

	पूर्णांक i, j, pass = 0, fail = 0;
	काष्ठा io_pgtable_cfg cfg = अणु
		.tlb = &dummy_tlb_ops,
		.oas = 48,
		.coherent_walk = true,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(pgsize); ++i) अणु
		क्रम (j = 0; j < ARRAY_SIZE(ias); ++j) अणु
			cfg.pgsize_biपंचांगap = pgsize[i];
			cfg.ias = ias[j];
			pr_info("selftest: pgsize_bitmap 0x%08lx, IAS %u\n",
				pgsize[i], ias[j]);
			अगर (arm_lpae_run_tests(&cfg))
				fail++;
			अन्यथा
				pass++;
		पूर्ण
	पूर्ण

	pr_info("selftest: completed with %d PASS %d FAIL\n", pass, fail);
	वापस fail ? -EFAULT : 0;
पूर्ण
subsys_initcall(arm_lpae_करो_selftests);
#पूर्ण_अगर
