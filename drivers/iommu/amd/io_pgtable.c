<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CPU-agnostic AMD IO page table allocator.
 *
 * Copyright (C) 2020 Advanced Micro Devices, Inc.
 * Author: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
 */

#घोषणा pr_fmt(fmt)     "AMD-Vi: " fmt
#घोषणा dev_fmt(fmt)    pr_fmt(fmt)

#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/io-pgtable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/barrier.h>

#समावेश "amd_iommu_types.h"
#समावेश "amd_iommu.h"

अटल व्योम v1_tlb_flush_all(व्योम *cookie)
अणु
पूर्ण

अटल व्योम v1_tlb_flush_walk(अचिन्हित दीर्घ iova, माप_प्रकार size,
				  माप_प्रकार granule, व्योम *cookie)
अणु
पूर्ण

अटल व्योम v1_tlb_add_page(काष्ठा iommu_iotlb_gather *gather,
					 अचिन्हित दीर्घ iova, माप_प्रकार granule,
					 व्योम *cookie)
अणु
पूर्ण

अटल स्थिर काष्ठा iommu_flush_ops v1_flush_ops = अणु
	.tlb_flush_all	= v1_tlb_flush_all,
	.tlb_flush_walk = v1_tlb_flush_walk,
	.tlb_add_page	= v1_tlb_add_page,
पूर्ण;

/*
 * Helper function to get the first pte of a large mapping
 */
अटल u64 *first_pte_l7(u64 *pte, अचिन्हित दीर्घ *page_size,
			 अचिन्हित दीर्घ *count)
अणु
	अचिन्हित दीर्घ pte_mask, pg_size, cnt;
	u64 *fpte;

	pg_size  = PTE_PAGE_SIZE(*pte);
	cnt      = PAGE_SIZE_PTE_COUNT(pg_size);
	pte_mask = ~((cnt << 3) - 1);
	fpte     = (u64 *)(((अचिन्हित दीर्घ)pte) & pte_mask);

	अगर (page_size)
		*page_size = pg_size;

	अगर (count)
		*count = cnt;

	वापस fpte;
पूर्ण

/****************************************************************************
 *
 * The functions below are used the create the page table mappings क्रम
 * unity mapped regions.
 *
 ****************************************************************************/

अटल व्योम मुक्त_page_list(काष्ठा page *मुक्तlist)
अणु
	जबतक (मुक्तlist != शून्य) अणु
		अचिन्हित दीर्घ p = (अचिन्हित दीर्घ)page_address(मुक्तlist);

		मुक्तlist = मुक्तlist->मुक्तlist;
		मुक्त_page(p);
	पूर्ण
पूर्ण

अटल काष्ठा page *मुक्त_pt_page(अचिन्हित दीर्घ pt, काष्ठा page *मुक्तlist)
अणु
	काष्ठा page *p = virt_to_page((व्योम *)pt);

	p->मुक्तlist = मुक्तlist;

	वापस p;
पूर्ण

#घोषणा DEFINE_FREE_PT_FN(LVL, FN)						\
अटल काष्ठा page *मुक्त_pt_##LVL (अचिन्हित दीर्घ __pt, काष्ठा page *मुक्तlist)	\
अणु										\
	अचिन्हित दीर्घ p;							\
	u64 *pt;								\
	पूर्णांक i;									\
										\
	pt = (u64 *)__pt;							\
										\
	क्रम (i = 0; i < 512; ++i) अणु						\
		/* PTE present? */						\
		अगर (!IOMMU_PTE_PRESENT(pt[i]))					\
			जारी;						\
										\
		/* Large PTE? */						\
		अगर (PM_PTE_LEVEL(pt[i]) == 0 ||					\
		    PM_PTE_LEVEL(pt[i]) == 7)					\
			जारी;						\
										\
		p = (अचिन्हित दीर्घ)IOMMU_PTE_PAGE(pt[i]);			\
		मुक्तlist = FN(p, मुक्तlist);					\
	पूर्ण									\
										\
	वापस मुक्त_pt_page((अचिन्हित दीर्घ)pt, मुक्तlist);			\
पूर्ण

DEFINE_FREE_PT_FN(l2, मुक्त_pt_page)
DEFINE_FREE_PT_FN(l3, मुक्त_pt_l2)
DEFINE_FREE_PT_FN(l4, मुक्त_pt_l3)
DEFINE_FREE_PT_FN(l5, मुक्त_pt_l4)
DEFINE_FREE_PT_FN(l6, मुक्त_pt_l5)

अटल काष्ठा page *मुक्त_sub_pt(अचिन्हित दीर्घ root, पूर्णांक mode,
				काष्ठा page *मुक्तlist)
अणु
	चयन (mode) अणु
	हाल PAGE_MODE_NONE:
	हाल PAGE_MODE_7_LEVEL:
		अवरोध;
	हाल PAGE_MODE_1_LEVEL:
		मुक्तlist = मुक्त_pt_page(root, मुक्तlist);
		अवरोध;
	हाल PAGE_MODE_2_LEVEL:
		मुक्तlist = मुक्त_pt_l2(root, मुक्तlist);
		अवरोध;
	हाल PAGE_MODE_3_LEVEL:
		मुक्तlist = मुक्त_pt_l3(root, मुक्तlist);
		अवरोध;
	हाल PAGE_MODE_4_LEVEL:
		मुक्तlist = मुक्त_pt_l4(root, मुक्तlist);
		अवरोध;
	हाल PAGE_MODE_5_LEVEL:
		मुक्तlist = मुक्त_pt_l5(root, मुक्तlist);
		अवरोध;
	हाल PAGE_MODE_6_LEVEL:
		मुक्तlist = मुक्त_pt_l6(root, मुक्तlist);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस मुक्तlist;
पूर्ण

व्योम amd_iommu_करोमुख्य_set_pgtable(काष्ठा protection_करोमुख्य *करोमुख्य,
				  u64 *root, पूर्णांक mode)
अणु
	u64 pt_root;

	/* lowest 3 bits encode pgtable mode */
	pt_root = mode & 7;
	pt_root |= (u64)root;

	amd_iommu_करोमुख्य_set_pt_root(करोमुख्य, pt_root);
पूर्ण

/*
 * This function is used to add another level to an IO page table. Adding
 * another level increases the size of the address space by 9 bits to a size up
 * to 64 bits.
 */
अटल bool increase_address_space(काष्ठा protection_करोमुख्य *करोमुख्य,
				   अचिन्हित दीर्घ address,
				   gfp_t gfp)
अणु
	अचिन्हित दीर्घ flags;
	bool ret = true;
	u64 *pte;

	pte = (व्योम *)get_zeroed_page(gfp);
	अगर (!pte)
		वापस false;

	spin_lock_irqsave(&करोमुख्य->lock, flags);

	अगर (address <= PM_LEVEL_SIZE(करोमुख्य->iop.mode))
		जाओ out;

	ret = false;
	अगर (WARN_ON_ONCE(करोमुख्य->iop.mode == PAGE_MODE_6_LEVEL))
		जाओ out;

	*pte = PM_LEVEL_PDE(करोमुख्य->iop.mode, iommu_virt_to_phys(करोमुख्य->iop.root));

	करोमुख्य->iop.root  = pte;
	करोमुख्य->iop.mode += 1;
	amd_iommu_update_and_flush_device_table(करोमुख्य);
	amd_iommu_करोमुख्य_flush_complete(करोमुख्य);

	/*
	 * Device Table needs to be updated and flushed beक्रमe the new root can
	 * be published.
	 */
	amd_iommu_करोमुख्य_set_pgtable(करोमुख्य, pte, करोमुख्य->iop.mode);

	pte = शून्य;
	ret = true;

out:
	spin_unlock_irqrestore(&करोमुख्य->lock, flags);
	मुक्त_page((अचिन्हित दीर्घ)pte);

	वापस ret;
पूर्ण

अटल u64 *alloc_pte(काष्ठा protection_करोमुख्य *करोमुख्य,
		      अचिन्हित दीर्घ address,
		      अचिन्हित दीर्घ page_size,
		      u64 **pte_page,
		      gfp_t gfp,
		      bool *updated)
अणु
	पूर्णांक level, end_lvl;
	u64 *pte, *page;

	BUG_ON(!is_घातer_of_2(page_size));

	जबतक (address > PM_LEVEL_SIZE(करोमुख्य->iop.mode)) अणु
		/*
		 * Return an error अगर there is no memory to update the
		 * page-table.
		 */
		अगर (!increase_address_space(करोमुख्य, address, gfp))
			वापस शून्य;
	पूर्ण


	level   = करोमुख्य->iop.mode - 1;
	pte     = &करोमुख्य->iop.root[PM_LEVEL_INDEX(level, address)];
	address = PAGE_SIZE_ALIGN(address, page_size);
	end_lvl = PAGE_SIZE_LEVEL(page_size);

	जबतक (level > end_lvl) अणु
		u64 __pte, __npte;
		पूर्णांक pte_level;

		__pte     = *pte;
		pte_level = PM_PTE_LEVEL(__pte);

		/*
		 * If we replace a series of large PTEs, we need
		 * to tear करोwn all of them.
		 */
		अगर (IOMMU_PTE_PRESENT(__pte) &&
		    pte_level == PAGE_MODE_7_LEVEL) अणु
			अचिन्हित दीर्घ count, i;
			u64 *lpte;

			lpte = first_pte_l7(pte, शून्य, &count);

			/*
			 * Unmap the replicated PTEs that still match the
			 * original large mapping
			 */
			क्रम (i = 0; i < count; ++i)
				cmpxchg64(&lpte[i], __pte, 0ULL);

			*updated = true;
			जारी;
		पूर्ण

		अगर (!IOMMU_PTE_PRESENT(__pte) ||
		    pte_level == PAGE_MODE_NONE) अणु
			page = (u64 *)get_zeroed_page(gfp);

			अगर (!page)
				वापस शून्य;

			__npte = PM_LEVEL_PDE(level, iommu_virt_to_phys(page));

			/* pte could have been changed somewhere. */
			अगर (cmpxchg64(pte, __pte, __npte) != __pte)
				मुक्त_page((अचिन्हित दीर्घ)page);
			अन्यथा अगर (IOMMU_PTE_PRESENT(__pte))
				*updated = true;

			जारी;
		पूर्ण

		/* No level skipping support yet */
		अगर (pte_level != level)
			वापस शून्य;

		level -= 1;

		pte = IOMMU_PTE_PAGE(__pte);

		अगर (pte_page && level == end_lvl)
			*pte_page = pte;

		pte = &pte[PM_LEVEL_INDEX(level, address)];
	पूर्ण

	वापस pte;
पूर्ण

/*
 * This function checks अगर there is a PTE क्रम a given dma address. If
 * there is one, it वापसs the poपूर्णांकer to it.
 */
अटल u64 *fetch_pte(काष्ठा amd_io_pgtable *pgtable,
		      अचिन्हित दीर्घ address,
		      अचिन्हित दीर्घ *page_size)
अणु
	पूर्णांक level;
	u64 *pte;

	*page_size = 0;

	अगर (address > PM_LEVEL_SIZE(pgtable->mode))
		वापस शून्य;

	level	   =  pgtable->mode - 1;
	pte	   = &pgtable->root[PM_LEVEL_INDEX(level, address)];
	*page_size =  PTE_LEVEL_PAGE_SIZE(level);

	जबतक (level > 0) अणु

		/* Not Present */
		अगर (!IOMMU_PTE_PRESENT(*pte))
			वापस शून्य;

		/* Large PTE */
		अगर (PM_PTE_LEVEL(*pte) == 7 ||
		    PM_PTE_LEVEL(*pte) == 0)
			अवरोध;

		/* No level skipping support yet */
		अगर (PM_PTE_LEVEL(*pte) != level)
			वापस शून्य;

		level -= 1;

		/* Walk to the next level */
		pte	   = IOMMU_PTE_PAGE(*pte);
		pte	   = &pte[PM_LEVEL_INDEX(level, address)];
		*page_size = PTE_LEVEL_PAGE_SIZE(level);
	पूर्ण

	/*
	 * If we have a series of large PTEs, make
	 * sure to वापस a poपूर्णांकer to the first one.
	 */
	अगर (PM_PTE_LEVEL(*pte) == PAGE_MODE_7_LEVEL)
		pte = first_pte_l7(pte, page_size, शून्य);

	वापस pte;
पूर्ण

अटल काष्ठा page *मुक्त_clear_pte(u64 *pte, u64 pteval, काष्ठा page *मुक्तlist)
अणु
	अचिन्हित दीर्घ pt;
	पूर्णांक mode;

	जबतक (cmpxchg64(pte, pteval, 0) != pteval) अणु
		pr_warn("AMD-Vi: IOMMU pte changed since we read it\n");
		pteval = *pte;
	पूर्ण

	अगर (!IOMMU_PTE_PRESENT(pteval))
		वापस मुक्तlist;

	pt   = (अचिन्हित दीर्घ)IOMMU_PTE_PAGE(pteval);
	mode = IOMMU_PTE_MODE(pteval);

	वापस मुक्त_sub_pt(pt, mode, मुक्तlist);
पूर्ण

/*
 * Generic mapping functions. It maps a physical address पूर्णांकo a DMA
 * address space. It allocates the page table pages अगर necessary.
 * In the future it can be extended to a generic mapping function
 * supporting all features of AMD IOMMU page tables like level skipping
 * and full 64 bit address spaces.
 */
अटल पूर्णांक iommu_v1_map_page(काष्ठा io_pgtable_ops *ops, अचिन्हित दीर्घ iova,
			  phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा protection_करोमुख्य *करोm = io_pgtable_ops_to_करोमुख्य(ops);
	काष्ठा page *मुक्तlist = शून्य;
	bool updated = false;
	u64 __pte, *pte;
	पूर्णांक ret, i, count;

	BUG_ON(!IS_ALIGNED(iova, size));
	BUG_ON(!IS_ALIGNED(paddr, size));

	ret = -EINVAL;
	अगर (!(prot & IOMMU_PROT_MASK))
		जाओ out;

	count = PAGE_SIZE_PTE_COUNT(size);
	pte   = alloc_pte(करोm, iova, size, शून्य, gfp, &updated);

	ret = -ENOMEM;
	अगर (!pte)
		जाओ out;

	क्रम (i = 0; i < count; ++i)
		मुक्तlist = मुक्त_clear_pte(&pte[i], pte[i], मुक्तlist);

	अगर (मुक्तlist != शून्य)
		updated = true;

	अगर (count > 1) अणु
		__pte = PAGE_SIZE_PTE(__sme_set(paddr), size);
		__pte |= PM_LEVEL_ENC(7) | IOMMU_PTE_PR | IOMMU_PTE_FC;
	पूर्ण अन्यथा
		__pte = __sme_set(paddr) | IOMMU_PTE_PR | IOMMU_PTE_FC;

	अगर (prot & IOMMU_PROT_IR)
		__pte |= IOMMU_PTE_IR;
	अगर (prot & IOMMU_PROT_IW)
		__pte |= IOMMU_PTE_IW;

	क्रम (i = 0; i < count; ++i)
		pte[i] = __pte;

	ret = 0;

out:
	अगर (updated) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&करोm->lock, flags);
		/*
		 * Flush करोमुख्य TLB(s) and रुको क्रम completion. Any Device-Table
		 * Updates and flushing alपढ़ोy happened in
		 * increase_address_space().
		 */
		amd_iommu_करोमुख्य_flush_tlb_pde(करोm);
		amd_iommu_करोमुख्य_flush_complete(करोm);
		spin_unlock_irqrestore(&करोm->lock, flags);
	पूर्ण

	/* Everything flushed out, मुक्त pages now */
	मुक्त_page_list(मुक्तlist);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ iommu_v1_unmap_page(काष्ठा io_pgtable_ops *ops,
				      अचिन्हित दीर्घ iova,
				      माप_प्रकार size,
				      काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा amd_io_pgtable *pgtable = io_pgtable_ops_to_data(ops);
	अचिन्हित दीर्घ दीर्घ unmapped;
	अचिन्हित दीर्घ unmap_size;
	u64 *pte;

	BUG_ON(!is_घातer_of_2(size));

	unmapped = 0;

	जबतक (unmapped < size) अणु
		pte = fetch_pte(pgtable, iova, &unmap_size);
		अगर (pte) अणु
			पूर्णांक i, count;

			count = PAGE_SIZE_PTE_COUNT(unmap_size);
			क्रम (i = 0; i < count; i++)
				pte[i] = 0ULL;
		पूर्ण

		iova = (iova & ~(unmap_size - 1)) + unmap_size;
		unmapped += unmap_size;
	पूर्ण

	BUG_ON(unmapped && !is_घातer_of_2(unmapped));

	वापस unmapped;
पूर्ण

अटल phys_addr_t iommu_v1_iova_to_phys(काष्ठा io_pgtable_ops *ops, अचिन्हित दीर्घ iova)
अणु
	काष्ठा amd_io_pgtable *pgtable = io_pgtable_ops_to_data(ops);
	अचिन्हित दीर्घ offset_mask, pte_pgsize;
	u64 *pte, __pte;

	अगर (pgtable->mode == PAGE_MODE_NONE)
		वापस iova;

	pte = fetch_pte(pgtable, iova, &pte_pgsize);

	अगर (!pte || !IOMMU_PTE_PRESENT(*pte))
		वापस 0;

	offset_mask = pte_pgsize - 1;
	__pte	    = __sme_clr(*pte & PM_ADDR_MASK);

	वापस (__pte & ~offset_mask) | (iova & offset_mask);
पूर्ण

/*
 * ----------------------------------------------------
 */
अटल व्योम v1_मुक्त_pgtable(काष्ठा io_pgtable *iop)
अणु
	काष्ठा amd_io_pgtable *pgtable = container_of(iop, काष्ठा amd_io_pgtable, iop);
	काष्ठा protection_करोमुख्य *करोm;
	काष्ठा page *मुक्तlist = शून्य;
	अचिन्हित दीर्घ root;

	अगर (pgtable->mode == PAGE_MODE_NONE)
		वापस;

	करोm = container_of(pgtable, काष्ठा protection_करोमुख्य, iop);

	/* Update data काष्ठाure */
	amd_iommu_करोमुख्य_clr_pt_root(करोm);

	/* Make changes visible to IOMMUs */
	amd_iommu_करोमुख्य_update(करोm);

	/* Page-table is not visible to IOMMU anymore, so मुक्त it */
	BUG_ON(pgtable->mode < PAGE_MODE_NONE ||
	       pgtable->mode > PAGE_MODE_6_LEVEL);

	root = (अचिन्हित दीर्घ)pgtable->root;
	मुक्तlist = मुक्त_sub_pt(root, pgtable->mode, मुक्तlist);

	मुक्त_page_list(मुक्तlist);
पूर्ण

अटल काष्ठा io_pgtable *v1_alloc_pgtable(काष्ठा io_pgtable_cfg *cfg, व्योम *cookie)
अणु
	काष्ठा amd_io_pgtable *pgtable = io_pgtable_cfg_to_data(cfg);

	cfg->pgsize_biपंचांगap  = AMD_IOMMU_PGSIZES,
	cfg->ias            = IOMMU_IN_ADDR_BIT_SIZE,
	cfg->oas            = IOMMU_OUT_ADDR_BIT_SIZE,
	cfg->tlb            = &v1_flush_ops;

	pgtable->iop.ops.map          = iommu_v1_map_page;
	pgtable->iop.ops.unmap        = iommu_v1_unmap_page;
	pgtable->iop.ops.iova_to_phys = iommu_v1_iova_to_phys;

	वापस &pgtable->iop;
पूर्ण

काष्ठा io_pgtable_init_fns io_pgtable_amd_iommu_v1_init_fns = अणु
	.alloc	= v1_alloc_pgtable,
	.मुक्त	= v1_मुक्त_pgtable,
पूर्ण;
