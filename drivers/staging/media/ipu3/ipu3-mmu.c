<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Intel Corporation.
 * Copyright 2018 Google LLC.
 *
 * Author: Tuukka Toivonen <tuukka.toivonen@पूर्णांकel.com>
 * Author: Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com>
 * Author: Samu Onkalo <samu.onkalo@पूर्णांकel.com>
 * Author: Tomasz Figa <tfiga@chromium.org>
 *
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/set_memory.h>

#समावेश "ipu3-mmu.h"

#घोषणा IPU3_PT_BITS		10
#घोषणा IPU3_PT_PTES		(1UL << IPU3_PT_BITS)
#घोषणा IPU3_PT_SIZE		(IPU3_PT_PTES << 2)
#घोषणा IPU3_PT_ORDER		(IPU3_PT_SIZE >> PAGE_SHIFT)

#घोषणा IPU3_ADDR2PTE(addr)	((addr) >> IPU3_PAGE_SHIFT)
#घोषणा IPU3_PTE2ADDR(pte)	((phys_addr_t)(pte) << IPU3_PAGE_SHIFT)

#घोषणा IPU3_L2PT_SHIFT		IPU3_PT_BITS
#घोषणा IPU3_L2PT_MASK		((1UL << IPU3_L2PT_SHIFT) - 1)

#घोषणा IPU3_L1PT_SHIFT		IPU3_PT_BITS
#घोषणा IPU3_L1PT_MASK		((1UL << IPU3_L1PT_SHIFT) - 1)

#घोषणा IPU3_MMU_ADDRESS_BITS	(IPU3_PAGE_SHIFT + \
				 IPU3_L2PT_SHIFT + \
				 IPU3_L1PT_SHIFT)

#घोषणा IMGU_REG_BASE		0x4000
#घोषणा REG_TLB_INVALIDATE	(IMGU_REG_BASE + 0x300)
#घोषणा TLB_INVALIDATE		1
#घोषणा REG_L1_PHYS		(IMGU_REG_BASE + 0x304) /* 27-bit pfn */
#घोषणा REG_GP_HALT		(IMGU_REG_BASE + 0x5dc)
#घोषणा REG_GP_HALTED		(IMGU_REG_BASE + 0x5e0)

काष्ठा imgu_mmu अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	/* protect access to l2pts, l1pt */
	spinlock_t lock;

	व्योम *dummy_page;
	u32 dummy_page_pteval;

	u32 *dummy_l2pt;
	u32 dummy_l2pt_pteval;

	u32 **l2pts;
	u32 *l1pt;

	काष्ठा imgu_mmu_info geometry;
पूर्ण;

अटल अंतरभूत काष्ठा imgu_mmu *to_imgu_mmu(काष्ठा imgu_mmu_info *info)
अणु
	वापस container_of(info, काष्ठा imgu_mmu, geometry);
पूर्ण

/**
 * imgu_mmu_tlb_invalidate - invalidate translation look-aside buffer
 * @mmu: MMU to perक्रमm the invalidate operation on
 *
 * This function invalidates the whole TLB. Must be called when the hardware
 * is घातered on.
 */
अटल व्योम imgu_mmu_tlb_invalidate(काष्ठा imgu_mmu *mmu)
अणु
	ग_लिखोl(TLB_INVALIDATE, mmu->base + REG_TLB_INVALIDATE);
पूर्ण

अटल व्योम call_अगर_imgu_is_घातered(काष्ठा imgu_mmu *mmu,
				    व्योम (*func)(काष्ठा imgu_mmu *mmu))
अणु
	अगर (!pm_runसमय_get_अगर_in_use(mmu->dev))
		वापस;

	func(mmu);
	pm_runसमय_put(mmu->dev);
पूर्ण

/**
 * imgu_mmu_set_halt - set CIO gate halt bit
 * @mmu: MMU to set the CIO gate bit in.
 * @halt: Desired state of the gate bit.
 *
 * This function sets the CIO gate bit that controls whether बाह्यal memory
 * accesses are allowed. Must be called when the hardware is घातered on.
 */
अटल व्योम imgu_mmu_set_halt(काष्ठा imgu_mmu *mmu, bool halt)
अणु
	पूर्णांक ret;
	u32 val;

	ग_लिखोl(halt, mmu->base + REG_GP_HALT);
	ret = पढ़ोl_poll_समयout(mmu->base + REG_GP_HALTED,
				 val, (val & 1) == halt, 1000, 100000);

	अगर (ret)
		dev_err(mmu->dev, "failed to %s CIO gate halt\n",
			halt ? "set" : "clear");
पूर्ण

/**
 * imgu_mmu_alloc_page_table - allocate a pre-filled page table
 * @pteval: Value to initialize क्रम page table entries with.
 *
 * Return: Poपूर्णांकer to allocated page table or शून्य on failure.
 */
अटल u32 *imgu_mmu_alloc_page_table(u32 pteval)
अणु
	u32 *pt;
	पूर्णांक pte;

	pt = (u32 *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!pt)
		वापस शून्य;

	क्रम (pte = 0; pte < IPU3_PT_PTES; pte++)
		pt[pte] = pteval;

	set_memory_uc((अचिन्हित दीर्घ)pt, IPU3_PT_ORDER);

	वापस pt;
पूर्ण

/**
 * imgu_mmu_मुक्त_page_table - मुक्त page table
 * @pt: Page table to मुक्त.
 */
अटल व्योम imgu_mmu_मुक्त_page_table(u32 *pt)
अणु
	set_memory_wb((अचिन्हित दीर्घ)pt, IPU3_PT_ORDER);
	मुक्त_page((अचिन्हित दीर्घ)pt);
पूर्ण

/**
 * address_to_pte_idx - split IOVA पूर्णांकo L1 and L2 page table indices
 * @iova: IOVA to split.
 * @l1pt_idx: Output क्रम the L1 page table index.
 * @l2pt_idx: Output क्रम the L2 page index.
 */
अटल अंतरभूत व्योम address_to_pte_idx(अचिन्हित दीर्घ iova, u32 *l1pt_idx,
				      u32 *l2pt_idx)
अणु
	iova >>= IPU3_PAGE_SHIFT;

	अगर (l2pt_idx)
		*l2pt_idx = iova & IPU3_L2PT_MASK;

	iova >>= IPU3_L2PT_SHIFT;

	अगर (l1pt_idx)
		*l1pt_idx = iova & IPU3_L1PT_MASK;
पूर्ण

अटल u32 *imgu_mmu_get_l2pt(काष्ठा imgu_mmu *mmu, u32 l1pt_idx)
अणु
	अचिन्हित दीर्घ flags;
	u32 *l2pt, *new_l2pt;
	u32 pteval;

	spin_lock_irqsave(&mmu->lock, flags);

	l2pt = mmu->l2pts[l1pt_idx];
	अगर (l2pt) अणु
		spin_unlock_irqrestore(&mmu->lock, flags);
		वापस l2pt;
	पूर्ण

	spin_unlock_irqrestore(&mmu->lock, flags);

	new_l2pt = imgu_mmu_alloc_page_table(mmu->dummy_page_pteval);
	अगर (!new_l2pt)
		वापस शून्य;

	spin_lock_irqsave(&mmu->lock, flags);

	dev_dbg(mmu->dev, "allocated page table %p for l1pt_idx %u\n",
		new_l2pt, l1pt_idx);

	l2pt = mmu->l2pts[l1pt_idx];
	अगर (l2pt) अणु
		spin_unlock_irqrestore(&mmu->lock, flags);
		imgu_mmu_मुक्त_page_table(new_l2pt);
		वापस l2pt;
	पूर्ण

	l2pt = new_l2pt;
	mmu->l2pts[l1pt_idx] = new_l2pt;

	pteval = IPU3_ADDR2PTE(virt_to_phys(new_l2pt));
	mmu->l1pt[l1pt_idx] = pteval;

	spin_unlock_irqrestore(&mmu->lock, flags);
	वापस l2pt;
पूर्ण

अटल पूर्णांक __imgu_mmu_map(काष्ठा imgu_mmu *mmu, अचिन्हित दीर्घ iova,
			  phys_addr_t paddr)
अणु
	u32 l1pt_idx, l2pt_idx;
	अचिन्हित दीर्घ flags;
	u32 *l2pt;

	अगर (!mmu)
		वापस -ENODEV;

	address_to_pte_idx(iova, &l1pt_idx, &l2pt_idx);

	l2pt = imgu_mmu_get_l2pt(mmu, l1pt_idx);
	अगर (!l2pt)
		वापस -ENOMEM;

	spin_lock_irqsave(&mmu->lock, flags);

	अगर (l2pt[l2pt_idx] != mmu->dummy_page_pteval) अणु
		spin_unlock_irqrestore(&mmu->lock, flags);
		वापस -EBUSY;
	पूर्ण

	l2pt[l2pt_idx] = IPU3_ADDR2PTE(paddr);

	spin_unlock_irqrestore(&mmu->lock, flags);

	वापस 0;
पूर्ण

/**
 * imgu_mmu_map - map a buffer to a physical address
 *
 * @info: MMU mappable range
 * @iova: the भव address
 * @paddr: the physical address
 * @size: length of the mappable area
 *
 * The function has been adapted from iommu_map() in
 * drivers/iommu/iommu.c .
 */
पूर्णांक imgu_mmu_map(काष्ठा imgu_mmu_info *info, अचिन्हित दीर्घ iova,
		 phys_addr_t paddr, माप_प्रकार size)
अणु
	काष्ठा imgu_mmu *mmu = to_imgu_mmu(info);
	पूर्णांक ret = 0;

	/*
	 * both the भव address and the physical one, as well as
	 * the size of the mapping, must be aligned (at least) to the
	 * size of the smallest page supported by the hardware
	 */
	अगर (!IS_ALIGNED(iova | paddr | size, IPU3_PAGE_SIZE)) अणु
		dev_err(mmu->dev, "unaligned: iova 0x%lx pa %pa size 0x%zx\n",
			iova, &paddr, size);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(mmu->dev, "map: iova 0x%lx pa %pa size 0x%zx\n",
		iova, &paddr, size);

	जबतक (size) अणु
		dev_dbg(mmu->dev, "mapping: iova 0x%lx pa %pa\n", iova, &paddr);

		ret = __imgu_mmu_map(mmu, iova, paddr);
		अगर (ret)
			अवरोध;

		iova += IPU3_PAGE_SIZE;
		paddr += IPU3_PAGE_SIZE;
		size -= IPU3_PAGE_SIZE;
	पूर्ण

	call_अगर_imgu_is_घातered(mmu, imgu_mmu_tlb_invalidate);

	वापस ret;
पूर्ण

/**
 * imgu_mmu_map_sg - Map a scatterlist
 *
 * @info: MMU mappable range
 * @iova: the भव address
 * @sg: the scatterlist to map
 * @nents: number of entries in the scatterlist
 *
 * The function has been adapted from शेष_iommu_map_sg() in
 * drivers/iommu/iommu.c .
 */
माप_प्रकार imgu_mmu_map_sg(काष्ठा imgu_mmu_info *info, अचिन्हित दीर्घ iova,
		       काष्ठा scatterlist *sg, अचिन्हित पूर्णांक nents)
अणु
	काष्ठा imgu_mmu *mmu = to_imgu_mmu(info);
	काष्ठा scatterlist *s;
	माप_प्रकार s_length, mapped = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम_each_sg(sg, s, nents, i) अणु
		phys_addr_t phys = page_to_phys(sg_page(s)) + s->offset;

		s_length = s->length;

		अगर (!IS_ALIGNED(s->offset, IPU3_PAGE_SIZE))
			जाओ out_err;

		/* must be IPU3_PAGE_SIZE aligned to be mapped singlely */
		अगर (i == nents - 1 && !IS_ALIGNED(s->length, IPU3_PAGE_SIZE))
			s_length = PAGE_ALIGN(s->length);

		ret = imgu_mmu_map(info, iova + mapped, phys, s_length);
		अगर (ret)
			जाओ out_err;

		mapped += s_length;
	पूर्ण

	call_अगर_imgu_is_घातered(mmu, imgu_mmu_tlb_invalidate);

	वापस mapped;

out_err:
	/* unकरो mappings alपढ़ोy करोne */
	imgu_mmu_unmap(info, iova, mapped);

	वापस 0;
पूर्ण

अटल माप_प्रकार __imgu_mmu_unmap(काष्ठा imgu_mmu *mmu,
			       अचिन्हित दीर्घ iova, माप_प्रकार size)
अणु
	u32 l1pt_idx, l2pt_idx;
	अचिन्हित दीर्घ flags;
	माप_प्रकार unmap = size;
	u32 *l2pt;

	अगर (!mmu)
		वापस 0;

	address_to_pte_idx(iova, &l1pt_idx, &l2pt_idx);

	spin_lock_irqsave(&mmu->lock, flags);

	l2pt = mmu->l2pts[l1pt_idx];
	अगर (!l2pt) अणु
		spin_unlock_irqrestore(&mmu->lock, flags);
		वापस 0;
	पूर्ण

	अगर (l2pt[l2pt_idx] == mmu->dummy_page_pteval)
		unmap = 0;

	l2pt[l2pt_idx] = mmu->dummy_page_pteval;

	spin_unlock_irqrestore(&mmu->lock, flags);

	वापस unmap;
पूर्ण

/**
 * imgu_mmu_unmap - Unmap a buffer
 *
 * @info: MMU mappable range
 * @iova: the भव address
 * @size: the length of the buffer
 *
 * The function has been adapted from iommu_unmap() in
 * drivers/iommu/iommu.c .
 */
माप_प्रकार imgu_mmu_unmap(काष्ठा imgu_mmu_info *info, अचिन्हित दीर्घ iova,
		      माप_प्रकार size)
अणु
	काष्ठा imgu_mmu *mmu = to_imgu_mmu(info);
	माप_प्रकार unmapped_page, unmapped = 0;

	/*
	 * The भव address, as well as the size of the mapping, must be
	 * aligned (at least) to the size of the smallest page supported
	 * by the hardware
	 */
	अगर (!IS_ALIGNED(iova | size, IPU3_PAGE_SIZE)) अणु
		dev_err(mmu->dev, "unaligned: iova 0x%lx size 0x%zx\n",
			iova, size);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(mmu->dev, "unmap this: iova 0x%lx size 0x%zx\n", iova, size);

	/*
	 * Keep iterating until we either unmap 'size' bytes (or more)
	 * or we hit an area that isn't mapped.
	 */
	जबतक (unmapped < size) अणु
		unmapped_page = __imgu_mmu_unmap(mmu, iova, IPU3_PAGE_SIZE);
		अगर (!unmapped_page)
			अवरोध;

		dev_dbg(mmu->dev, "unmapped: iova 0x%lx size 0x%zx\n",
			iova, unmapped_page);

		iova += unmapped_page;
		unmapped += unmapped_page;
	पूर्ण

	call_अगर_imgu_is_घातered(mmu, imgu_mmu_tlb_invalidate);

	वापस unmapped;
पूर्ण

/**
 * imgu_mmu_init() - initialize IPU3 MMU block
 *
 * @parent:	काष्ठा device parent
 * @base:	IOMEM base of hardware रेजिस्टरs.
 *
 * Return: Poपूर्णांकer to IPU3 MMU निजी data poपूर्णांकer or ERR_PTR() on error.
 */
काष्ठा imgu_mmu_info *imgu_mmu_init(काष्ठा device *parent, व्योम __iomem *base)
अणु
	काष्ठा imgu_mmu *mmu;
	u32 pteval;

	mmu = kzalloc(माप(*mmu), GFP_KERNEL);
	अगर (!mmu)
		वापस ERR_PTR(-ENOMEM);

	mmu->dev = parent;
	mmu->base = base;
	spin_lock_init(&mmu->lock);

	/* Disallow बाह्यal memory access when having no valid page tables. */
	imgu_mmu_set_halt(mmu, true);

	/*
	 * The MMU करोes not have a "valid" bit, so we have to use a dummy
	 * page क्रम invalid entries.
	 */
	mmu->dummy_page = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!mmu->dummy_page)
		जाओ fail_group;
	pteval = IPU3_ADDR2PTE(virt_to_phys(mmu->dummy_page));
	mmu->dummy_page_pteval = pteval;

	/*
	 * Allocate a dummy L2 page table with all entries poपूर्णांकing to
	 * the dummy page.
	 */
	mmu->dummy_l2pt = imgu_mmu_alloc_page_table(pteval);
	अगर (!mmu->dummy_l2pt)
		जाओ fail_dummy_page;
	pteval = IPU3_ADDR2PTE(virt_to_phys(mmu->dummy_l2pt));
	mmu->dummy_l2pt_pteval = pteval;

	/*
	 * Allocate the array of L2PT CPU poपूर्णांकers, initialized to zero,
	 * which means the dummy L2PT allocated above.
	 */
	mmu->l2pts = vzalloc(IPU3_PT_PTES * माप(*mmu->l2pts));
	अगर (!mmu->l2pts)
		जाओ fail_l2pt;

	/* Allocate the L1 page table. */
	mmu->l1pt = imgu_mmu_alloc_page_table(mmu->dummy_l2pt_pteval);
	अगर (!mmu->l1pt)
		जाओ fail_l2pts;

	pteval = IPU3_ADDR2PTE(virt_to_phys(mmu->l1pt));
	ग_लिखोl(pteval, mmu->base + REG_L1_PHYS);
	imgu_mmu_tlb_invalidate(mmu);
	imgu_mmu_set_halt(mmu, false);

	mmu->geometry.aperture_start = 0;
	mmu->geometry.aperture_end = DMA_BIT_MASK(IPU3_MMU_ADDRESS_BITS);

	वापस &mmu->geometry;

fail_l2pts:
	vमुक्त(mmu->l2pts);
fail_l2pt:
	imgu_mmu_मुक्त_page_table(mmu->dummy_l2pt);
fail_dummy_page:
	मुक्त_page((अचिन्हित दीर्घ)mmu->dummy_page);
fail_group:
	kमुक्त(mmu);

	वापस ERR_PTR(-ENOMEM);
पूर्ण

/**
 * imgu_mmu_निकास() - clean up IPU3 MMU block
 *
 * @info: MMU mappable range
 */
व्योम imgu_mmu_निकास(काष्ठा imgu_mmu_info *info)
अणु
	काष्ठा imgu_mmu *mmu = to_imgu_mmu(info);

	/* We are going to मुक्त our page tables, no more memory access. */
	imgu_mmu_set_halt(mmu, true);
	imgu_mmu_tlb_invalidate(mmu);

	imgu_mmu_मुक्त_page_table(mmu->l1pt);
	vमुक्त(mmu->l2pts);
	imgu_mmu_मुक्त_page_table(mmu->dummy_l2pt);
	मुक्त_page((अचिन्हित दीर्घ)mmu->dummy_page);
	kमुक्त(mmu);
पूर्ण

व्योम imgu_mmu_suspend(काष्ठा imgu_mmu_info *info)
अणु
	काष्ठा imgu_mmu *mmu = to_imgu_mmu(info);

	imgu_mmu_set_halt(mmu, true);
पूर्ण

व्योम imgu_mmu_resume(काष्ठा imgu_mmu_info *info)
अणु
	काष्ठा imgu_mmu *mmu = to_imgu_mmu(info);
	u32 pteval;

	imgu_mmu_set_halt(mmu, true);

	pteval = IPU3_ADDR2PTE(virt_to_phys(mmu->l1pt));
	ग_लिखोl(pteval, mmu->base + REG_L1_PHYS);

	imgu_mmu_tlb_invalidate(mmu);
	imgu_mmu_set_halt(mmu, false);
पूर्ण
