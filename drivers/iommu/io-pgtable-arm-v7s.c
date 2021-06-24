<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CPU-agnostic ARM page table allocator.
 *
 * ARMv7 Short-descriptor क्रमmat, supporting
 * - Basic memory attributes
 * - Simplअगरied access permissions (AP[2:1] model)
 * - Backwards-compatible TEX remap
 * - Large pages/supersections (अगर indicated by the caller)
 *
 * Not supporting:
 * - Legacy access permissions (AP[2:0] model)
 *
 * Almost certainly never supporting:
 * - PXN
 * - Doमुख्यs
 *
 * Copyright (C) 2014-2015 ARM Limited
 * Copyright (c) 2014-2015 MediaTek Inc.
 */

#घोषणा pr_fmt(fmt)	"arm-v7s io-pgtable: " fmt

#समावेश <linux/atomic.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gfp.h>
#समावेश <linux/io-pgtable.h>
#समावेश <linux/iommu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/barrier.h>

/* Struct accessors */
#घोषणा io_pgtable_to_data(x)						\
	container_of((x), काष्ठा arm_v7s_io_pgtable, iop)

#घोषणा io_pgtable_ops_to_data(x)					\
	io_pgtable_to_data(io_pgtable_ops_to_pgtable(x))

/*
 * We have 32 bits total; 12 bits resolved at level 1, 8 bits at level 2,
 * and 12 bits in a page.
 * MediaTek extend 2 bits to reach 34bits, 14 bits at lvl1 and 8 bits at lvl2.
 */
#घोषणा ARM_V7S_ADDR_BITS		32
#घोषणा _ARM_V7S_LVL_BITS(lvl, cfg)	((lvl) == 1 ? ((cfg)->ias - 20) : 8)
#घोषणा ARM_V7S_LVL_SHIFT(lvl)		((lvl) == 1 ? 20 : 12)
#घोषणा ARM_V7S_TABLE_SHIFT		10

#घोषणा ARM_V7S_PTES_PER_LVL(lvl, cfg)	(1 << _ARM_V7S_LVL_BITS(lvl, cfg))
#घोषणा ARM_V7S_TABLE_SIZE(lvl, cfg)						\
	(ARM_V7S_PTES_PER_LVL(lvl, cfg) * माप(arm_v7s_iopte))

#घोषणा ARM_V7S_BLOCK_SIZE(lvl)		(1UL << ARM_V7S_LVL_SHIFT(lvl))
#घोषणा ARM_V7S_LVL_MASK(lvl)		((u32)(~0U << ARM_V7S_LVL_SHIFT(lvl)))
#घोषणा ARM_V7S_TABLE_MASK		((u32)(~0U << ARM_V7S_TABLE_SHIFT))
#घोषणा _ARM_V7S_IDX_MASK(lvl, cfg)	(ARM_V7S_PTES_PER_LVL(lvl, cfg) - 1)
#घोषणा ARM_V7S_LVL_IDX(addr, lvl, cfg)	(अणु				\
	पूर्णांक _l = lvl;							\
	((addr) >> ARM_V7S_LVL_SHIFT(_l)) & _ARM_V7S_IDX_MASK(_l, cfg); \
पूर्ण)

/*
 * Large page/supersection entries are effectively a block of 16 page/section
 * entries, aदीर्घ the lines of the LPAE contiguous hपूर्णांक, but all with the
 * same output address. For want of a better common name we'll call them
 * "contiguous" versions of their respective page/section entries here, but
 * noting the distinction (WRT to TLB मुख्यtenance) that they represent *one*
 * entry repeated 16 बार, not 16 separate entries (as in the LPAE हाल).
 */
#घोषणा ARM_V7S_CONT_PAGES		16

/* PTE type bits: these are all mixed up with XN/PXN bits in most हालs */
#घोषणा ARM_V7S_PTE_TYPE_TABLE		0x1
#घोषणा ARM_V7S_PTE_TYPE_PAGE		0x2
#घोषणा ARM_V7S_PTE_TYPE_CONT_PAGE	0x1

#घोषणा ARM_V7S_PTE_IS_VALID(pte)	(((pte) & 0x3) != 0)
#घोषणा ARM_V7S_PTE_IS_TABLE(pte, lvl) \
	((lvl) == 1 && (((pte) & 0x3) == ARM_V7S_PTE_TYPE_TABLE))

/* Page table bits */
#घोषणा ARM_V7S_ATTR_XN(lvl)		BIT(4 * (2 - (lvl)))
#घोषणा ARM_V7S_ATTR_B			BIT(2)
#घोषणा ARM_V7S_ATTR_C			BIT(3)
#घोषणा ARM_V7S_ATTR_NS_TABLE		BIT(3)
#घोषणा ARM_V7S_ATTR_NS_SECTION		BIT(19)

#घोषणा ARM_V7S_CONT_SECTION		BIT(18)
#घोषणा ARM_V7S_CONT_PAGE_XN_SHIFT	15

/*
 * The attribute bits are consistently ordered*, but occupy bits [17:10] of
 * a level 1 PTE vs. bits [11:4] at level 2. Thus we define the inभागidual
 * fields relative to that 8-bit block, plus a total shअगरt relative to the PTE.
 */
#घोषणा ARM_V7S_ATTR_SHIFT(lvl)		(16 - (lvl) * 6)

#घोषणा ARM_V7S_ATTR_MASK		0xff
#घोषणा ARM_V7S_ATTR_AP0		BIT(0)
#घोषणा ARM_V7S_ATTR_AP1		BIT(1)
#घोषणा ARM_V7S_ATTR_AP2		BIT(5)
#घोषणा ARM_V7S_ATTR_S			BIT(6)
#घोषणा ARM_V7S_ATTR_NG			BIT(7)
#घोषणा ARM_V7S_TEX_SHIFT		2
#घोषणा ARM_V7S_TEX_MASK		0x7
#घोषणा ARM_V7S_ATTR_TEX(val)		(((val) & ARM_V7S_TEX_MASK) << ARM_V7S_TEX_SHIFT)

/* MediaTek extend the bits below क्रम PA 32bit/33bit/34bit */
#घोषणा ARM_V7S_ATTR_MTK_PA_BIT32	BIT(9)
#घोषणा ARM_V7S_ATTR_MTK_PA_BIT33	BIT(4)
#घोषणा ARM_V7S_ATTR_MTK_PA_BIT34	BIT(5)

/* *well, except क्रम TEX on level 2 large pages, of course :( */
#घोषणा ARM_V7S_CONT_PAGE_TEX_SHIFT	6
#घोषणा ARM_V7S_CONT_PAGE_TEX_MASK	(ARM_V7S_TEX_MASK << ARM_V7S_CONT_PAGE_TEX_SHIFT)

/* Simplअगरied access permissions */
#घोषणा ARM_V7S_PTE_AF			ARM_V7S_ATTR_AP0
#घोषणा ARM_V7S_PTE_AP_UNPRIV		ARM_V7S_ATTR_AP1
#घोषणा ARM_V7S_PTE_AP_RDONLY		ARM_V7S_ATTR_AP2

/* Register bits */
#घोषणा ARM_V7S_RGN_NC			0
#घोषणा ARM_V7S_RGN_WBWA		1
#घोषणा ARM_V7S_RGN_WT			2
#घोषणा ARM_V7S_RGN_WB			3

#घोषणा ARM_V7S_PRRR_TYPE_DEVICE	1
#घोषणा ARM_V7S_PRRR_TYPE_NORMAL	2
#घोषणा ARM_V7S_PRRR_TR(n, type)	(((type) & 0x3) << ((n) * 2))
#घोषणा ARM_V7S_PRRR_DS0		BIT(16)
#घोषणा ARM_V7S_PRRR_DS1		BIT(17)
#घोषणा ARM_V7S_PRRR_NS0		BIT(18)
#घोषणा ARM_V7S_PRRR_NS1		BIT(19)
#घोषणा ARM_V7S_PRRR_NOS(n)		BIT((n) + 24)

#घोषणा ARM_V7S_NMRR_IR(n, attr)	(((attr) & 0x3) << ((n) * 2))
#घोषणा ARM_V7S_NMRR_OR(n, attr)	(((attr) & 0x3) << ((n) * 2 + 16))

#घोषणा ARM_V7S_TTBR_S			BIT(1)
#घोषणा ARM_V7S_TTBR_NOS		BIT(5)
#घोषणा ARM_V7S_TTBR_ORGN_ATTR(attr)	(((attr) & 0x3) << 3)
#घोषणा ARM_V7S_TTBR_IRGN_ATTR(attr)					\
	((((attr) & 0x1) << 6) | (((attr) & 0x2) >> 1))

#अगर_घोषित CONFIG_ZONE_DMA32
#घोषणा ARM_V7S_TABLE_GFP_DMA GFP_DMA32
#घोषणा ARM_V7S_TABLE_SLAB_FLAGS SLAB_CACHE_DMA32
#अन्यथा
#घोषणा ARM_V7S_TABLE_GFP_DMA GFP_DMA
#घोषणा ARM_V7S_TABLE_SLAB_FLAGS SLAB_CACHE_DMA
#पूर्ण_अगर

प्रकार u32 arm_v7s_iopte;

अटल bool selftest_running;

काष्ठा arm_v7s_io_pgtable अणु
	काष्ठा io_pgtable	iop;

	arm_v7s_iopte		*pgd;
	काष्ठा kmem_cache	*l2_tables;
	spinlock_t		split_lock;
पूर्ण;

अटल bool arm_v7s_pte_is_cont(arm_v7s_iopte pte, पूर्णांक lvl);

अटल dma_addr_t __arm_v7s_dma_addr(व्योम *pages)
अणु
	वापस (dma_addr_t)virt_to_phys(pages);
पूर्ण

अटल bool arm_v7s_is_mtk_enabled(काष्ठा io_pgtable_cfg *cfg)
अणु
	वापस IS_ENABLED(CONFIG_PHYS_ADDR_T_64BIT) &&
		(cfg->quirks & IO_PGTABLE_QUIRK_ARM_MTK_EXT);
पूर्ण

अटल arm_v7s_iopte paddr_to_iopte(phys_addr_t paddr, पूर्णांक lvl,
				    काष्ठा io_pgtable_cfg *cfg)
अणु
	arm_v7s_iopte pte = paddr & ARM_V7S_LVL_MASK(lvl);

	अगर (!arm_v7s_is_mtk_enabled(cfg))
		वापस pte;

	अगर (paddr & BIT_ULL(32))
		pte |= ARM_V7S_ATTR_MTK_PA_BIT32;
	अगर (paddr & BIT_ULL(33))
		pte |= ARM_V7S_ATTR_MTK_PA_BIT33;
	अगर (paddr & BIT_ULL(34))
		pte |= ARM_V7S_ATTR_MTK_PA_BIT34;
	वापस pte;
पूर्ण

अटल phys_addr_t iopte_to_paddr(arm_v7s_iopte pte, पूर्णांक lvl,
				  काष्ठा io_pgtable_cfg *cfg)
अणु
	arm_v7s_iopte mask;
	phys_addr_t paddr;

	अगर (ARM_V7S_PTE_IS_TABLE(pte, lvl))
		mask = ARM_V7S_TABLE_MASK;
	अन्यथा अगर (arm_v7s_pte_is_cont(pte, lvl))
		mask = ARM_V7S_LVL_MASK(lvl) * ARM_V7S_CONT_PAGES;
	अन्यथा
		mask = ARM_V7S_LVL_MASK(lvl);

	paddr = pte & mask;
	अगर (!arm_v7s_is_mtk_enabled(cfg))
		वापस paddr;

	अगर (pte & ARM_V7S_ATTR_MTK_PA_BIT32)
		paddr |= BIT_ULL(32);
	अगर (pte & ARM_V7S_ATTR_MTK_PA_BIT33)
		paddr |= BIT_ULL(33);
	अगर (pte & ARM_V7S_ATTR_MTK_PA_BIT34)
		paddr |= BIT_ULL(34);
	वापस paddr;
पूर्ण

अटल arm_v7s_iopte *iopte_deref(arm_v7s_iopte pte, पूर्णांक lvl,
				  काष्ठा arm_v7s_io_pgtable *data)
अणु
	वापस phys_to_virt(iopte_to_paddr(pte, lvl, &data->iop.cfg));
पूर्ण

अटल व्योम *__arm_v7s_alloc_table(पूर्णांक lvl, gfp_t gfp,
				   काष्ठा arm_v7s_io_pgtable *data)
अणु
	काष्ठा io_pgtable_cfg *cfg = &data->iop.cfg;
	काष्ठा device *dev = cfg->iommu_dev;
	phys_addr_t phys;
	dma_addr_t dma;
	माप_प्रकार size = ARM_V7S_TABLE_SIZE(lvl, cfg);
	व्योम *table = शून्य;

	अगर (lvl == 1)
		table = (व्योम *)__get_मुक्त_pages(
			__GFP_ZERO | ARM_V7S_TABLE_GFP_DMA, get_order(size));
	अन्यथा अगर (lvl == 2)
		table = kmem_cache_zalloc(data->l2_tables, gfp);
	phys = virt_to_phys(table);
	अगर (phys != (arm_v7s_iopte)phys) अणु
		/* Doesn't fit in PTE */
		dev_err(dev, "Page table does not fit in PTE: %pa", &phys);
		जाओ out_मुक्त;
	पूर्ण
	अगर (table && !cfg->coherent_walk) अणु
		dma = dma_map_single(dev, table, size, DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, dma))
			जाओ out_मुक्त;
		/*
		 * We depend on the IOMMU being able to work with any physical
		 * address directly, so अगर the DMA layer suggests otherwise by
		 * translating or truncating them, that bodes very badly...
		 */
		अगर (dma != phys)
			जाओ out_unmap;
	पूर्ण
	अगर (lvl == 2)
		kmemleak_ignore(table);
	वापस table;

out_unmap:
	dev_err(dev, "Cannot accommodate DMA translation for IOMMU page tables\n");
	dma_unmap_single(dev, dma, size, DMA_TO_DEVICE);
out_मुक्त:
	अगर (lvl == 1)
		मुक्त_pages((अचिन्हित दीर्घ)table, get_order(size));
	अन्यथा
		kmem_cache_मुक्त(data->l2_tables, table);
	वापस शून्य;
पूर्ण

अटल व्योम __arm_v7s_मुक्त_table(व्योम *table, पूर्णांक lvl,
				 काष्ठा arm_v7s_io_pgtable *data)
अणु
	काष्ठा io_pgtable_cfg *cfg = &data->iop.cfg;
	काष्ठा device *dev = cfg->iommu_dev;
	माप_प्रकार size = ARM_V7S_TABLE_SIZE(lvl, cfg);

	अगर (!cfg->coherent_walk)
		dma_unmap_single(dev, __arm_v7s_dma_addr(table), size,
				 DMA_TO_DEVICE);
	अगर (lvl == 1)
		मुक्त_pages((अचिन्हित दीर्घ)table, get_order(size));
	अन्यथा
		kmem_cache_मुक्त(data->l2_tables, table);
पूर्ण

अटल व्योम __arm_v7s_pte_sync(arm_v7s_iopte *ptep, पूर्णांक num_entries,
			       काष्ठा io_pgtable_cfg *cfg)
अणु
	अगर (cfg->coherent_walk)
		वापस;

	dma_sync_single_क्रम_device(cfg->iommu_dev, __arm_v7s_dma_addr(ptep),
				   num_entries * माप(*ptep), DMA_TO_DEVICE);
पूर्ण
अटल व्योम __arm_v7s_set_pte(arm_v7s_iopte *ptep, arm_v7s_iopte pte,
			      पूर्णांक num_entries, काष्ठा io_pgtable_cfg *cfg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_entries; i++)
		ptep[i] = pte;

	__arm_v7s_pte_sync(ptep, num_entries, cfg);
पूर्ण

अटल arm_v7s_iopte arm_v7s_prot_to_pte(पूर्णांक prot, पूर्णांक lvl,
					 काष्ठा io_pgtable_cfg *cfg)
अणु
	bool ap = !(cfg->quirks & IO_PGTABLE_QUIRK_NO_PERMS);
	arm_v7s_iopte pte = ARM_V7S_ATTR_NG | ARM_V7S_ATTR_S;

	अगर (!(prot & IOMMU_MMIO))
		pte |= ARM_V7S_ATTR_TEX(1);
	अगर (ap) अणु
		pte |= ARM_V7S_PTE_AF;
		अगर (!(prot & IOMMU_PRIV))
			pte |= ARM_V7S_PTE_AP_UNPRIV;
		अगर (!(prot & IOMMU_WRITE))
			pte |= ARM_V7S_PTE_AP_RDONLY;
	पूर्ण
	pte <<= ARM_V7S_ATTR_SHIFT(lvl);

	अगर ((prot & IOMMU_NOEXEC) && ap)
		pte |= ARM_V7S_ATTR_XN(lvl);
	अगर (prot & IOMMU_MMIO)
		pte |= ARM_V7S_ATTR_B;
	अन्यथा अगर (prot & IOMMU_CACHE)
		pte |= ARM_V7S_ATTR_B | ARM_V7S_ATTR_C;

	pte |= ARM_V7S_PTE_TYPE_PAGE;
	अगर (lvl == 1 && (cfg->quirks & IO_PGTABLE_QUIRK_ARM_NS))
		pte |= ARM_V7S_ATTR_NS_SECTION;

	वापस pte;
पूर्ण

अटल पूर्णांक arm_v7s_pte_to_prot(arm_v7s_iopte pte, पूर्णांक lvl)
अणु
	पूर्णांक prot = IOMMU_READ;
	arm_v7s_iopte attr = pte >> ARM_V7S_ATTR_SHIFT(lvl);

	अगर (!(attr & ARM_V7S_PTE_AP_RDONLY))
		prot |= IOMMU_WRITE;
	अगर (!(attr & ARM_V7S_PTE_AP_UNPRIV))
		prot |= IOMMU_PRIV;
	अगर ((attr & (ARM_V7S_TEX_MASK << ARM_V7S_TEX_SHIFT)) == 0)
		prot |= IOMMU_MMIO;
	अन्यथा अगर (pte & ARM_V7S_ATTR_C)
		prot |= IOMMU_CACHE;
	अगर (pte & ARM_V7S_ATTR_XN(lvl))
		prot |= IOMMU_NOEXEC;

	वापस prot;
पूर्ण

अटल arm_v7s_iopte arm_v7s_pte_to_cont(arm_v7s_iopte pte, पूर्णांक lvl)
अणु
	अगर (lvl == 1) अणु
		pte |= ARM_V7S_CONT_SECTION;
	पूर्ण अन्यथा अगर (lvl == 2) अणु
		arm_v7s_iopte xn = pte & ARM_V7S_ATTR_XN(lvl);
		arm_v7s_iopte tex = pte & ARM_V7S_CONT_PAGE_TEX_MASK;

		pte ^= xn | tex | ARM_V7S_PTE_TYPE_PAGE;
		pte |= (xn << ARM_V7S_CONT_PAGE_XN_SHIFT) |
		       (tex << ARM_V7S_CONT_PAGE_TEX_SHIFT) |
		       ARM_V7S_PTE_TYPE_CONT_PAGE;
	पूर्ण
	वापस pte;
पूर्ण

अटल arm_v7s_iopte arm_v7s_cont_to_pte(arm_v7s_iopte pte, पूर्णांक lvl)
अणु
	अगर (lvl == 1) अणु
		pte &= ~ARM_V7S_CONT_SECTION;
	पूर्ण अन्यथा अगर (lvl == 2) अणु
		arm_v7s_iopte xn = pte & BIT(ARM_V7S_CONT_PAGE_XN_SHIFT);
		arm_v7s_iopte tex = pte & (ARM_V7S_CONT_PAGE_TEX_MASK <<
					   ARM_V7S_CONT_PAGE_TEX_SHIFT);

		pte ^= xn | tex | ARM_V7S_PTE_TYPE_CONT_PAGE;
		pte |= (xn >> ARM_V7S_CONT_PAGE_XN_SHIFT) |
		       (tex >> ARM_V7S_CONT_PAGE_TEX_SHIFT) |
		       ARM_V7S_PTE_TYPE_PAGE;
	पूर्ण
	वापस pte;
पूर्ण

अटल bool arm_v7s_pte_is_cont(arm_v7s_iopte pte, पूर्णांक lvl)
अणु
	अगर (lvl == 1 && !ARM_V7S_PTE_IS_TABLE(pte, lvl))
		वापस pte & ARM_V7S_CONT_SECTION;
	अन्यथा अगर (lvl == 2)
		वापस !(pte & ARM_V7S_PTE_TYPE_PAGE);
	वापस false;
पूर्ण

अटल माप_प्रकार __arm_v7s_unmap(काष्ठा arm_v7s_io_pgtable *,
			      काष्ठा iommu_iotlb_gather *, अचिन्हित दीर्घ,
			      माप_प्रकार, पूर्णांक, arm_v7s_iopte *);

अटल पूर्णांक arm_v7s_init_pte(काष्ठा arm_v7s_io_pgtable *data,
			    अचिन्हित दीर्घ iova, phys_addr_t paddr, पूर्णांक prot,
			    पूर्णांक lvl, पूर्णांक num_entries, arm_v7s_iopte *ptep)
अणु
	काष्ठा io_pgtable_cfg *cfg = &data->iop.cfg;
	arm_v7s_iopte pte;
	पूर्णांक i;

	क्रम (i = 0; i < num_entries; i++)
		अगर (ARM_V7S_PTE_IS_TABLE(ptep[i], lvl)) अणु
			/*
			 * We need to unmap and मुक्त the old table beक्रमe
			 * overwriting it with a block entry.
			 */
			arm_v7s_iopte *tblp;
			माप_प्रकार sz = ARM_V7S_BLOCK_SIZE(lvl);

			tblp = ptep - ARM_V7S_LVL_IDX(iova, lvl, cfg);
			अगर (WARN_ON(__arm_v7s_unmap(data, शून्य, iova + i * sz,
						    sz, lvl, tblp) != sz))
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (ptep[i]) अणु
			/* We require an unmap first */
			WARN_ON(!selftest_running);
			वापस -EEXIST;
		पूर्ण

	pte = arm_v7s_prot_to_pte(prot, lvl, cfg);
	अगर (num_entries > 1)
		pte = arm_v7s_pte_to_cont(pte, lvl);

	pte |= paddr_to_iopte(paddr, lvl, cfg);

	__arm_v7s_set_pte(ptep, pte, num_entries, cfg);
	वापस 0;
पूर्ण

अटल arm_v7s_iopte arm_v7s_install_table(arm_v7s_iopte *table,
					   arm_v7s_iopte *ptep,
					   arm_v7s_iopte curr,
					   काष्ठा io_pgtable_cfg *cfg)
अणु
	arm_v7s_iopte old, new;

	new = virt_to_phys(table) | ARM_V7S_PTE_TYPE_TABLE;
	अगर (cfg->quirks & IO_PGTABLE_QUIRK_ARM_NS)
		new |= ARM_V7S_ATTR_NS_TABLE;

	/*
	 * Ensure the table itself is visible beक्रमe its PTE can be.
	 * Whilst we could get away with cmpxchg64_release below, this
	 * करोesn't have any ordering semantics when !CONFIG_SMP.
	 */
	dma_wmb();

	old = cmpxchg_relaxed(ptep, curr, new);
	__arm_v7s_pte_sync(ptep, 1, cfg);

	वापस old;
पूर्ण

अटल पूर्णांक __arm_v7s_map(काष्ठा arm_v7s_io_pgtable *data, अचिन्हित दीर्घ iova,
			 phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot,
			 पूर्णांक lvl, arm_v7s_iopte *ptep, gfp_t gfp)
अणु
	काष्ठा io_pgtable_cfg *cfg = &data->iop.cfg;
	arm_v7s_iopte pte, *cptep;
	पूर्णांक num_entries = size >> ARM_V7S_LVL_SHIFT(lvl);

	/* Find our entry at the current level */
	ptep += ARM_V7S_LVL_IDX(iova, lvl, cfg);

	/* If we can install a leaf entry at this level, then करो so */
	अगर (num_entries)
		वापस arm_v7s_init_pte(data, iova, paddr, prot,
					lvl, num_entries, ptep);

	/* We can't allocate tables at the final level */
	अगर (WARN_ON(lvl == 2))
		वापस -EINVAL;

	/* Grab a poपूर्णांकer to the next level */
	pte = READ_ONCE(*ptep);
	अगर (!pte) अणु
		cptep = __arm_v7s_alloc_table(lvl + 1, gfp, data);
		अगर (!cptep)
			वापस -ENOMEM;

		pte = arm_v7s_install_table(cptep, ptep, 0, cfg);
		अगर (pte)
			__arm_v7s_मुक्त_table(cptep, lvl + 1, data);
	पूर्ण अन्यथा अणु
		/* We've no easy way of knowing if it's synced yet, so... */
		__arm_v7s_pte_sync(ptep, 1, cfg);
	पूर्ण

	अगर (ARM_V7S_PTE_IS_TABLE(pte, lvl)) अणु
		cptep = iopte_deref(pte, lvl, data);
	पूर्ण अन्यथा अगर (pte) अणु
		/* We require an unmap first */
		WARN_ON(!selftest_running);
		वापस -EEXIST;
	पूर्ण

	/* Rinse, repeat */
	वापस __arm_v7s_map(data, iova, paddr, size, prot, lvl + 1, cptep, gfp);
पूर्ण

अटल पूर्णांक arm_v7s_map(काष्ठा io_pgtable_ops *ops, अचिन्हित दीर्घ iova,
			phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा arm_v7s_io_pgtable *data = io_pgtable_ops_to_data(ops);
	पूर्णांक ret;

	अगर (WARN_ON(iova >= (1ULL << data->iop.cfg.ias) ||
		    paddr >= (1ULL << data->iop.cfg.oas)))
		वापस -दुस्फल;

	/* If no access, then nothing to करो */
	अगर (!(prot & (IOMMU_READ | IOMMU_WRITE)))
		वापस 0;

	ret = __arm_v7s_map(data, iova, paddr, size, prot, 1, data->pgd, gfp);
	/*
	 * Synchronise all PTE updates क्रम the new mapping beक्रमe there's
	 * a chance क्रम anything to kick off a table walk क्रम the new iova.
	 */
	wmb();

	वापस ret;
पूर्ण

अटल व्योम arm_v7s_मुक्त_pgtable(काष्ठा io_pgtable *iop)
अणु
	काष्ठा arm_v7s_io_pgtable *data = io_pgtable_to_data(iop);
	पूर्णांक i;

	क्रम (i = 0; i < ARM_V7S_PTES_PER_LVL(1, &data->iop.cfg); i++) अणु
		arm_v7s_iopte pte = data->pgd[i];

		अगर (ARM_V7S_PTE_IS_TABLE(pte, 1))
			__arm_v7s_मुक्त_table(iopte_deref(pte, 1, data),
					     2, data);
	पूर्ण
	__arm_v7s_मुक्त_table(data->pgd, 1, data);
	kmem_cache_destroy(data->l2_tables);
	kमुक्त(data);
पूर्ण

अटल arm_v7s_iopte arm_v7s_split_cont(काष्ठा arm_v7s_io_pgtable *data,
					अचिन्हित दीर्घ iova, पूर्णांक idx, पूर्णांक lvl,
					arm_v7s_iopte *ptep)
अणु
	काष्ठा io_pgtable *iop = &data->iop;
	arm_v7s_iopte pte;
	माप_प्रकार size = ARM_V7S_BLOCK_SIZE(lvl);
	पूर्णांक i;

	/* Check that we didn't lose a race to get the lock */
	pte = *ptep;
	अगर (!arm_v7s_pte_is_cont(pte, lvl))
		वापस pte;

	ptep -= idx & (ARM_V7S_CONT_PAGES - 1);
	pte = arm_v7s_cont_to_pte(pte, lvl);
	क्रम (i = 0; i < ARM_V7S_CONT_PAGES; i++)
		ptep[i] = pte + i * size;

	__arm_v7s_pte_sync(ptep, ARM_V7S_CONT_PAGES, &iop->cfg);

	size *= ARM_V7S_CONT_PAGES;
	io_pgtable_tlb_flush_walk(iop, iova, size, size);
	वापस pte;
पूर्ण

अटल माप_प्रकार arm_v7s_split_blk_unmap(काष्ठा arm_v7s_io_pgtable *data,
				      काष्ठा iommu_iotlb_gather *gather,
				      अचिन्हित दीर्घ iova, माप_प्रकार size,
				      arm_v7s_iopte blk_pte,
				      arm_v7s_iopte *ptep)
अणु
	काष्ठा io_pgtable_cfg *cfg = &data->iop.cfg;
	arm_v7s_iopte pte, *tablep;
	पूर्णांक i, unmap_idx, num_entries, num_ptes;

	tablep = __arm_v7s_alloc_table(2, GFP_ATOMIC, data);
	अगर (!tablep)
		वापस 0; /* Bytes unmapped */

	num_ptes = ARM_V7S_PTES_PER_LVL(2, cfg);
	num_entries = size >> ARM_V7S_LVL_SHIFT(2);
	unmap_idx = ARM_V7S_LVL_IDX(iova, 2, cfg);

	pte = arm_v7s_prot_to_pte(arm_v7s_pte_to_prot(blk_pte, 1), 2, cfg);
	अगर (num_entries > 1)
		pte = arm_v7s_pte_to_cont(pte, 2);

	क्रम (i = 0; i < num_ptes; i += num_entries, pte += size) अणु
		/* Unmap! */
		अगर (i == unmap_idx)
			जारी;

		__arm_v7s_set_pte(&tablep[i], pte, num_entries, cfg);
	पूर्ण

	pte = arm_v7s_install_table(tablep, ptep, blk_pte, cfg);
	अगर (pte != blk_pte) अणु
		__arm_v7s_मुक्त_table(tablep, 2, data);

		अगर (!ARM_V7S_PTE_IS_TABLE(pte, 1))
			वापस 0;

		tablep = iopte_deref(pte, 1, data);
		वापस __arm_v7s_unmap(data, gather, iova, size, 2, tablep);
	पूर्ण

	io_pgtable_tlb_add_page(&data->iop, gather, iova, size);
	वापस size;
पूर्ण

अटल माप_प्रकार __arm_v7s_unmap(काष्ठा arm_v7s_io_pgtable *data,
			      काष्ठा iommu_iotlb_gather *gather,
			      अचिन्हित दीर्घ iova, माप_प्रकार size, पूर्णांक lvl,
			      arm_v7s_iopte *ptep)
अणु
	arm_v7s_iopte pte[ARM_V7S_CONT_PAGES];
	काष्ठा io_pgtable *iop = &data->iop;
	पूर्णांक idx, i = 0, num_entries = size >> ARM_V7S_LVL_SHIFT(lvl);

	/* Something went horribly wrong and we ran out of page table */
	अगर (WARN_ON(lvl > 2))
		वापस 0;

	idx = ARM_V7S_LVL_IDX(iova, lvl, &iop->cfg);
	ptep += idx;
	करो अणु
		pte[i] = READ_ONCE(ptep[i]);
		अगर (WARN_ON(!ARM_V7S_PTE_IS_VALID(pte[i])))
			वापस 0;
	पूर्ण जबतक (++i < num_entries);

	/*
	 * If we've hit a contiguous 'large page' entry at this level, it
	 * needs splitting first, unless we're unmapping the whole lot.
	 *
	 * For splitting, we can't reग_लिखो 16 PTEs atomically, and since we
	 * can't necessarily assume TEX remap we don't have a software bit to
	 * mark live entries being split. In practice (i.e. DMA API code), we
	 * will never be splitting large pages anyway, so just wrap this edge
	 * हाल in a lock क्रम the sake of correctness and be करोne with it.
	 */
	अगर (num_entries <= 1 && arm_v7s_pte_is_cont(pte[0], lvl)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&data->split_lock, flags);
		pte[0] = arm_v7s_split_cont(data, iova, idx, lvl, ptep);
		spin_unlock_irqrestore(&data->split_lock, flags);
	पूर्ण

	/* If the size matches this level, we're in the right place */
	अगर (num_entries) अणु
		माप_प्रकार blk_size = ARM_V7S_BLOCK_SIZE(lvl);

		__arm_v7s_set_pte(ptep, 0, num_entries, &iop->cfg);

		क्रम (i = 0; i < num_entries; i++) अणु
			अगर (ARM_V7S_PTE_IS_TABLE(pte[i], lvl)) अणु
				/* Also flush any partial walks */
				io_pgtable_tlb_flush_walk(iop, iova, blk_size,
						ARM_V7S_BLOCK_SIZE(lvl + 1));
				ptep = iopte_deref(pte[i], lvl, data);
				__arm_v7s_मुक्त_table(ptep, lvl + 1, data);
			पूर्ण अन्यथा अगर (iop->cfg.quirks & IO_PGTABLE_QUIRK_NON_STRICT) अणु
				/*
				 * Order the PTE update against queueing the IOVA, to
				 * guarantee that a flush callback from a dअगरferent CPU
				 * has observed it beक्रमe the TLBIALL can be issued.
				 */
				smp_wmb();
			पूर्ण अन्यथा अणु
				io_pgtable_tlb_add_page(iop, gather, iova, blk_size);
			पूर्ण
			iova += blk_size;
		पूर्ण
		वापस size;
	पूर्ण अन्यथा अगर (lvl == 1 && !ARM_V7S_PTE_IS_TABLE(pte[0], lvl)) अणु
		/*
		 * Insert a table at the next level to map the old region,
		 * minus the part we want to unmap
		 */
		वापस arm_v7s_split_blk_unmap(data, gather, iova, size, pte[0],
					       ptep);
	पूर्ण

	/* Keep on walkin' */
	ptep = iopte_deref(pte[0], lvl, data);
	वापस __arm_v7s_unmap(data, gather, iova, size, lvl + 1, ptep);
पूर्ण

अटल माप_प्रकार arm_v7s_unmap(काष्ठा io_pgtable_ops *ops, अचिन्हित दीर्घ iova,
			    माप_प्रकार size, काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा arm_v7s_io_pgtable *data = io_pgtable_ops_to_data(ops);

	अगर (WARN_ON(iova >= (1ULL << data->iop.cfg.ias)))
		वापस 0;

	वापस __arm_v7s_unmap(data, gather, iova, size, 1, data->pgd);
पूर्ण

अटल phys_addr_t arm_v7s_iova_to_phys(काष्ठा io_pgtable_ops *ops,
					अचिन्हित दीर्घ iova)
अणु
	काष्ठा arm_v7s_io_pgtable *data = io_pgtable_ops_to_data(ops);
	arm_v7s_iopte *ptep = data->pgd, pte;
	पूर्णांक lvl = 0;
	u32 mask;

	करो अणु
		ptep += ARM_V7S_LVL_IDX(iova, ++lvl, &data->iop.cfg);
		pte = READ_ONCE(*ptep);
		ptep = iopte_deref(pte, lvl, data);
	पूर्ण जबतक (ARM_V7S_PTE_IS_TABLE(pte, lvl));

	अगर (!ARM_V7S_PTE_IS_VALID(pte))
		वापस 0;

	mask = ARM_V7S_LVL_MASK(lvl);
	अगर (arm_v7s_pte_is_cont(pte, lvl))
		mask *= ARM_V7S_CONT_PAGES;
	वापस iopte_to_paddr(pte, lvl, &data->iop.cfg) | (iova & ~mask);
पूर्ण

अटल काष्ठा io_pgtable *arm_v7s_alloc_pgtable(काष्ठा io_pgtable_cfg *cfg,
						व्योम *cookie)
अणु
	काष्ठा arm_v7s_io_pgtable *data;

	अगर (cfg->ias > (arm_v7s_is_mtk_enabled(cfg) ? 34 : ARM_V7S_ADDR_BITS))
		वापस शून्य;

	अगर (cfg->oas > (arm_v7s_is_mtk_enabled(cfg) ? 35 : ARM_V7S_ADDR_BITS))
		वापस शून्य;

	अगर (cfg->quirks & ~(IO_PGTABLE_QUIRK_ARM_NS |
			    IO_PGTABLE_QUIRK_NO_PERMS |
			    IO_PGTABLE_QUIRK_ARM_MTK_EXT |
			    IO_PGTABLE_QUIRK_NON_STRICT))
		वापस शून्य;

	/* If ARM_MTK_4GB is enabled, the NO_PERMS is also expected. */
	अगर (cfg->quirks & IO_PGTABLE_QUIRK_ARM_MTK_EXT &&
	    !(cfg->quirks & IO_PGTABLE_QUIRK_NO_PERMS))
			वापस शून्य;

	data = kदो_स्मृति(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस शून्य;

	spin_lock_init(&data->split_lock);
	data->l2_tables = kmem_cache_create("io-pgtable_armv7s_l2",
					    ARM_V7S_TABLE_SIZE(2, cfg),
					    ARM_V7S_TABLE_SIZE(2, cfg),
					    ARM_V7S_TABLE_SLAB_FLAGS, शून्य);
	अगर (!data->l2_tables)
		जाओ out_मुक्त_data;

	data->iop.ops = (काष्ठा io_pgtable_ops) अणु
		.map		= arm_v7s_map,
		.unmap		= arm_v7s_unmap,
		.iova_to_phys	= arm_v7s_iova_to_phys,
	पूर्ण;

	/* We have to करो this early क्रम __arm_v7s_alloc_table to work... */
	data->iop.cfg = *cfg;

	/*
	 * Unless the IOMMU driver indicates supersection support by
	 * having SZ_16M set in the initial biपंचांगap, they won't be used.
	 */
	cfg->pgsize_biपंचांगap &= SZ_4K | SZ_64K | SZ_1M | SZ_16M;

	/* TCR: T0SZ=0, EAE=0 (अगर applicable) */
	cfg->arm_v7s_cfg.tcr = 0;

	/*
	 * TEX remap: the indices used map to the बंदst equivalent types
	 * under the non-TEX-remap पूर्णांकerpretation of those attribute bits,
	 * excepting various implementation-defined aspects of shareability.
	 */
	cfg->arm_v7s_cfg.prrr = ARM_V7S_PRRR_TR(1, ARM_V7S_PRRR_TYPE_DEVICE) |
				ARM_V7S_PRRR_TR(4, ARM_V7S_PRRR_TYPE_NORMAL) |
				ARM_V7S_PRRR_TR(7, ARM_V7S_PRRR_TYPE_NORMAL) |
				ARM_V7S_PRRR_DS0 | ARM_V7S_PRRR_DS1 |
				ARM_V7S_PRRR_NS1 | ARM_V7S_PRRR_NOS(7);
	cfg->arm_v7s_cfg.nmrr = ARM_V7S_NMRR_IR(7, ARM_V7S_RGN_WBWA) |
				ARM_V7S_NMRR_OR(7, ARM_V7S_RGN_WBWA);

	/* Looking good; allocate a pgd */
	data->pgd = __arm_v7s_alloc_table(1, GFP_KERNEL, data);
	अगर (!data->pgd)
		जाओ out_मुक्त_data;

	/* Ensure the empty pgd is visible beक्रमe any actual TTBR ग_लिखो */
	wmb();

	/* TTBR */
	cfg->arm_v7s_cfg.ttbr = virt_to_phys(data->pgd) | ARM_V7S_TTBR_S |
				(cfg->coherent_walk ? (ARM_V7S_TTBR_NOS |
				 ARM_V7S_TTBR_IRGN_ATTR(ARM_V7S_RGN_WBWA) |
				 ARM_V7S_TTBR_ORGN_ATTR(ARM_V7S_RGN_WBWA)) :
				(ARM_V7S_TTBR_IRGN_ATTR(ARM_V7S_RGN_NC) |
				 ARM_V7S_TTBR_ORGN_ATTR(ARM_V7S_RGN_NC)));
	वापस &data->iop;

out_मुक्त_data:
	kmem_cache_destroy(data->l2_tables);
	kमुक्त(data);
	वापस शून्य;
पूर्ण

काष्ठा io_pgtable_init_fns io_pgtable_arm_v7s_init_fns = अणु
	.alloc	= arm_v7s_alloc_pgtable,
	.मुक्त	= arm_v7s_मुक्त_pgtable,
पूर्ण;

#अगर_घोषित CONFIG_IOMMU_IO_PGTABLE_ARMV7S_SELFTEST

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

#घोषणा __FAIL(ops)	(अणु				\
		WARN(1, "selftest: test failed\n");	\
		selftest_running = false;		\
		-EFAULT;				\
पूर्ण)

अटल पूर्णांक __init arm_v7s_करो_selftests(व्योम)
अणु
	काष्ठा io_pgtable_ops *ops;
	काष्ठा io_pgtable_cfg cfg = अणु
		.tlb = &dummy_tlb_ops,
		.oas = 32,
		.ias = 32,
		.coherent_walk = true,
		.quirks = IO_PGTABLE_QUIRK_ARM_NS,
		.pgsize_biपंचांगap = SZ_4K | SZ_64K | SZ_1M | SZ_16M,
	पूर्ण;
	अचिन्हित पूर्णांक iova, size, ioबहु_शुरू;
	अचिन्हित पूर्णांक i, loopnr = 0;

	selftest_running = true;

	cfg_cookie = &cfg;

	ops = alloc_io_pgtable_ops(ARM_V7S, &cfg, &cfg);
	अगर (!ops) अणु
		pr_err("selftest: failed to allocate io pgtable ops\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Initial sanity checks.
	 * Empty page tables shouldn't provide any translations.
	 */
	अगर (ops->iova_to_phys(ops, 42))
		वापस __FAIL(ops);

	अगर (ops->iova_to_phys(ops, SZ_1G + 42))
		वापस __FAIL(ops);

	अगर (ops->iova_to_phys(ops, SZ_2G + 42))
		वापस __FAIL(ops);

	/*
	 * Distinct mappings of dअगरferent granule sizes.
	 */
	iova = 0;
	क्रम_each_set_bit(i, &cfg.pgsize_biपंचांगap, BITS_PER_LONG) अणु
		size = 1UL << i;
		अगर (ops->map(ops, iova, iova, size, IOMMU_READ |
						    IOMMU_WRITE |
						    IOMMU_NOEXEC |
						    IOMMU_CACHE, GFP_KERNEL))
			वापस __FAIL(ops);

		/* Overlapping mappings */
		अगर (!ops->map(ops, iova, iova + size, size,
			      IOMMU_READ | IOMMU_NOEXEC, GFP_KERNEL))
			वापस __FAIL(ops);

		अगर (ops->iova_to_phys(ops, iova + 42) != (iova + 42))
			वापस __FAIL(ops);

		iova += SZ_16M;
		loopnr++;
	पूर्ण

	/* Partial unmap */
	i = 1;
	size = 1UL << __ffs(cfg.pgsize_biपंचांगap);
	जबतक (i < loopnr) अणु
		ioबहु_शुरू = i * SZ_16M;
		अगर (ops->unmap(ops, ioबहु_शुरू + size, size, शून्य) != size)
			वापस __FAIL(ops);

		/* Remap of partial unmap */
		अगर (ops->map(ops, ioबहु_शुरू + size, size, size, IOMMU_READ, GFP_KERNEL))
			वापस __FAIL(ops);

		अगर (ops->iova_to_phys(ops, ioबहु_शुरू + size + 42)
		    != (size + 42))
			वापस __FAIL(ops);
		i++;
	पूर्ण

	/* Full unmap */
	iova = 0;
	क्रम_each_set_bit(i, &cfg.pgsize_biपंचांगap, BITS_PER_LONG) अणु
		size = 1UL << i;

		अगर (ops->unmap(ops, iova, size, शून्य) != size)
			वापस __FAIL(ops);

		अगर (ops->iova_to_phys(ops, iova + 42))
			वापस __FAIL(ops);

		/* Remap full block */
		अगर (ops->map(ops, iova, iova, size, IOMMU_WRITE, GFP_KERNEL))
			वापस __FAIL(ops);

		अगर (ops->iova_to_phys(ops, iova + 42) != (iova + 42))
			वापस __FAIL(ops);

		iova += SZ_16M;
	पूर्ण

	मुक्त_io_pgtable_ops(ops);

	selftest_running = false;

	pr_info("self test ok\n");
	वापस 0;
पूर्ण
subsys_initcall(arm_v7s_करो_selftests);
#पूर्ण_अगर
