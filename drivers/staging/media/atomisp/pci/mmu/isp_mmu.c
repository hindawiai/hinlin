<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * Copyright (c) 2010 Silicon Hive www.siliconhive.com.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */
/*
 * ISP MMU management wrap code
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>		/* क्रम GFP_ATOMIC */
#समावेश <linux/slab.h>		/* क्रम kदो_स्मृति */
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sizes.h>

#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/set_memory.h>
#पूर्ण_अगर

#समावेश "atomisp_internal.h"
#समावेश "mmu/isp_mmu.h"

/*
 * 64-bit x86 processor physical address layout:
 * 0		- 0x7fffffff		DDR RAM	(2GB)
 * 0x80000000	- 0xffffffff		MMIO	(2GB)
 * 0x100000000	- 0x3fffffffffff	DDR RAM	(64TB)
 * So अगर the प्रणाली has more than 2GB DDR memory, the lower 2GB occupies the
 * physical address 0 - 0x7fffffff and the rest will start from 0x100000000.
 * We have to make sure memory is allocated from the lower 2GB क्रम devices
 * that are only 32-bit capable(e.g. the ISP MMU).
 *
 * For any confusion, contact bin.gao@पूर्णांकel.com.
 */
#घोषणा NR_PAGES_2GB	(SZ_2G / PAGE_SIZE)

अटल व्योम मुक्त_mmu_map(काष्ठा isp_mmu *mmu, अचिन्हित पूर्णांक start_isp_virt,
			 अचिन्हित पूर्णांक end_isp_virt);

अटल अचिन्हित पूर्णांक atomisp_get_pte(phys_addr_t pt, अचिन्हित पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक *pt_virt = phys_to_virt(pt);

	वापस *(pt_virt + idx);
पूर्ण

अटल व्योम atomisp_set_pte(phys_addr_t pt,
			    अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक pte)
अणु
	अचिन्हित पूर्णांक *pt_virt = phys_to_virt(pt);
	*(pt_virt + idx) = pte;
पूर्ण

अटल व्योम *isp_pt_phys_to_virt(phys_addr_t phys)
अणु
	वापस phys_to_virt(phys);
पूर्ण

अटल phys_addr_t isp_pte_to_pgaddr(काष्ठा isp_mmu *mmu,
				     अचिन्हित पूर्णांक pte)
अणु
	वापस mmu->driver->pte_to_phys(mmu, pte);
पूर्ण

अटल अचिन्हित पूर्णांक isp_pgaddr_to_pte_valid(काष्ठा isp_mmu *mmu,
	phys_addr_t phys)
अणु
	अचिन्हित पूर्णांक pte = mmu->driver->phys_to_pte(mmu, phys);

	वापस (अचिन्हित पूर्णांक)(pte | ISP_PTE_VALID_MASK(mmu));
पूर्ण

/*
 * allocate a uncacheable page table.
 * वापस physical address.
 */
अटल phys_addr_t alloc_page_table(काष्ठा isp_mmu *mmu)
अणु
	पूर्णांक i;
	phys_addr_t page;
	व्योम *virt;

	virt = (व्योम *)__get_मुक्त_page(GFP_KERNEL | GFP_DMA32);

	अगर (!virt)
		वापस (phys_addr_t)शून्य_PAGE;

	/*
	 * we need a uncacheable page table.
	 */
#अगर_घोषित	CONFIG_X86
	set_memory_uc((अचिन्हित दीर्घ)virt, 1);
#पूर्ण_अगर

	page = virt_to_phys(virt);

	क्रम (i = 0; i < 1024; i++) अणु
		/* NEED CHECK */
		atomisp_set_pte(page, i, mmu->driver->null_pte);
	पूर्ण

	वापस page;
पूर्ण

अटल व्योम मुक्त_page_table(काष्ठा isp_mmu *mmu, phys_addr_t page)
अणु
	व्योम *virt;

	page &= ISP_PAGE_MASK;
	/*
	 * reset the page to ग_लिखो back beक्रमe मुक्त
	 */
	virt = phys_to_virt(page);

#अगर_घोषित	CONFIG_X86
	set_memory_wb((अचिन्हित दीर्घ)virt, 1);
#पूर्ण_अगर

	मुक्त_page((अचिन्हित दीर्घ)virt);
पूर्ण

अटल व्योम mmu_remap_error(काष्ठा isp_mmu *mmu,
			    phys_addr_t l1_pt, अचिन्हित पूर्णांक l1_idx,
			    phys_addr_t l2_pt, अचिन्हित पूर्णांक l2_idx,
			    अचिन्हित पूर्णांक isp_virt, phys_addr_t old_phys,
			    phys_addr_t new_phys)
अणु
	dev_err(atomisp_dev, "address remap:\n\n"
		"\tL1 PT: virt = %p, phys = 0x%llx, idx = %d\n"
		"\tL2 PT: virt = %p, phys = 0x%llx, idx = %d\n"
		"\told: isp_virt = 0x%x, phys = 0x%llx\n"
		"\tnew: isp_virt = 0x%x, phys = 0x%llx\n",
		isp_pt_phys_to_virt(l1_pt),
		(u64)l1_pt, l1_idx,
		isp_pt_phys_to_virt(l2_pt),
		(u64)l2_pt, l2_idx, isp_virt,
		(u64)old_phys, isp_virt,
		(u64)new_phys);
पूर्ण

अटल व्योम mmu_unmap_l2_pte_error(काष्ठा isp_mmu *mmu,
				   phys_addr_t l1_pt, अचिन्हित पूर्णांक l1_idx,
				   phys_addr_t l2_pt, अचिन्हित पूर्णांक l2_idx,
				   अचिन्हित पूर्णांक isp_virt, अचिन्हित पूर्णांक pte)
अणु
	dev_err(atomisp_dev, "unmap invalid L2 pte:\n\n"
		"\tL1 PT: virt = %p, phys = 0x%llx, idx = %d\n"
		"\tL2 PT: virt = %p, phys = 0x%llx, idx = %d\n"
		"\tisp_virt = 0x%x, pte(page phys) = 0x%x\n",
		isp_pt_phys_to_virt(l1_pt),
		(u64)l1_pt, l1_idx,
		isp_pt_phys_to_virt(l2_pt),
		(u64)l2_pt, l2_idx, isp_virt,
		pte);
पूर्ण

अटल व्योम mmu_unmap_l1_pte_error(काष्ठा isp_mmu *mmu,
				   phys_addr_t l1_pt, अचिन्हित पूर्णांक l1_idx,
				   अचिन्हित पूर्णांक isp_virt, अचिन्हित पूर्णांक pte)
अणु
	dev_err(atomisp_dev, "unmap invalid L1 pte (L2 PT):\n\n"
		"\tL1 PT: virt = %p, phys = 0x%llx, idx = %d\n"
		"\tisp_virt = 0x%x, l1_pte(L2 PT) = 0x%x\n",
		isp_pt_phys_to_virt(l1_pt),
		(u64)l1_pt, l1_idx, (अचिन्हित पूर्णांक)isp_virt,
		pte);
पूर्ण

अटल व्योम mmu_unmap_l1_pt_error(काष्ठा isp_mmu *mmu, अचिन्हित पूर्णांक pte)
अणु
	dev_err(atomisp_dev, "unmap invalid L1PT:\n\n"
		"L1PT = 0x%x\n", (अचिन्हित पूर्णांक)pte);
पूर्ण

/*
 * Update L2 page table according to isp भव address and page physical
 * address
 */
अटल पूर्णांक mmu_l2_map(काष्ठा isp_mmu *mmu, phys_addr_t l1_pt,
		      अचिन्हित पूर्णांक l1_idx, phys_addr_t l2_pt,
		      अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end, phys_addr_t phys)
अणु
	अचिन्हित पूर्णांक ptr;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक pte;

	l2_pt &= ISP_PAGE_MASK;

	start = start & ISP_PAGE_MASK;
	end = ISP_PAGE_ALIGN(end);
	phys &= ISP_PAGE_MASK;

	ptr = start;
	करो अणु
		idx = ISP_PTR_TO_L2_IDX(ptr);

		pte = atomisp_get_pte(l2_pt, idx);

		अगर (ISP_PTE_VALID(mmu, pte)) अणु
			mmu_remap_error(mmu, l1_pt, l1_idx,
					l2_pt, idx, ptr, pte, phys);

			/* मुक्त all mapped pages */
			मुक्त_mmu_map(mmu, start, ptr);

			वापस -EINVAL;
		पूर्ण

		pte = isp_pgaddr_to_pte_valid(mmu, phys);

		atomisp_set_pte(l2_pt, idx, pte);
		mmu->l2_pgt_refcount[l1_idx]++;
		ptr += (1U << ISP_L2PT_OFFSET);
		phys += (1U << ISP_L2PT_OFFSET);
	पूर्ण जबतक (ptr < end && idx < ISP_L2PT_PTES - 1);

	वापस 0;
पूर्ण

/*
 * Update L1 page table according to isp भव address and page physical
 * address
 */
अटल पूर्णांक mmu_l1_map(काष्ठा isp_mmu *mmu, phys_addr_t l1_pt,
		      अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end,
		      phys_addr_t phys)
अणु
	phys_addr_t l2_pt;
	अचिन्हित पूर्णांक ptr, l1_aligned;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक l2_pte;
	पूर्णांक ret;

	l1_pt &= ISP_PAGE_MASK;

	start = start & ISP_PAGE_MASK;
	end = ISP_PAGE_ALIGN(end);
	phys &= ISP_PAGE_MASK;

	ptr = start;
	करो अणु
		idx = ISP_PTR_TO_L1_IDX(ptr);

		l2_pte = atomisp_get_pte(l1_pt, idx);

		अगर (!ISP_PTE_VALID(mmu, l2_pte)) अणु
			l2_pt = alloc_page_table(mmu);
			अगर (l2_pt == शून्य_PAGE) अणु
				dev_err(atomisp_dev,
					"alloc page table fail.\n");

				/* मुक्त all mapped pages */
				मुक्त_mmu_map(mmu, start, ptr);

				वापस -ENOMEM;
			पूर्ण

			l2_pte = isp_pgaddr_to_pte_valid(mmu, l2_pt);

			atomisp_set_pte(l1_pt, idx, l2_pte);
			mmu->l2_pgt_refcount[idx] = 0;
		पूर्ण

		l2_pt = isp_pte_to_pgaddr(mmu, l2_pte);

		l1_aligned = (ptr & ISP_PAGE_MASK) + (1U << ISP_L1PT_OFFSET);

		अगर (l1_aligned < end) अणु
			ret = mmu_l2_map(mmu, l1_pt, idx,
					 l2_pt, ptr, l1_aligned, phys);
			phys += (l1_aligned - ptr);
			ptr = l1_aligned;
		पूर्ण अन्यथा अणु
			ret = mmu_l2_map(mmu, l1_pt, idx,
					 l2_pt, ptr, end, phys);
			phys += (end - ptr);
			ptr = end;
		पूर्ण

		अगर (ret) अणु
			dev_err(atomisp_dev, "setup mapping in L2PT fail.\n");

			/* मुक्त all mapped pages */
			मुक्त_mmu_map(mmu, start, ptr);

			वापस -EINVAL;
		पूर्ण
	पूर्ण जबतक (ptr < end && idx < ISP_L1PT_PTES);

	वापस 0;
पूर्ण

/*
 * Update page table according to isp भव address and page physical
 * address
 */
अटल पूर्णांक mmu_map(काष्ठा isp_mmu *mmu, अचिन्हित पूर्णांक isp_virt,
		   phys_addr_t phys, अचिन्हित पूर्णांक pgnr)
अणु
	अचिन्हित पूर्णांक start, end;
	phys_addr_t l1_pt;
	पूर्णांक ret;

	mutex_lock(&mmu->pt_mutex);
	अगर (!ISP_PTE_VALID(mmu, mmu->l1_pte)) अणु
		/*
		 * allocate 1 new page क्रम L1 page table
		 */
		l1_pt = alloc_page_table(mmu);
		अगर (l1_pt == शून्य_PAGE) अणु
			dev_err(atomisp_dev, "alloc page table fail.\n");
			mutex_unlock(&mmu->pt_mutex);
			वापस -ENOMEM;
		पूर्ण

		/*
		 * setup L1 page table physical addr to MMU
		 */
		mmu->base_address = l1_pt;
		mmu->l1_pte = isp_pgaddr_to_pte_valid(mmu, l1_pt);
		स_रखो(mmu->l2_pgt_refcount, 0, माप(पूर्णांक) * ISP_L1PT_PTES);
	पूर्ण

	l1_pt = isp_pte_to_pgaddr(mmu, mmu->l1_pte);

	start = (isp_virt) & ISP_PAGE_MASK;
	end = start + (pgnr << ISP_PAGE_OFFSET);
	phys &= ISP_PAGE_MASK;

	ret = mmu_l1_map(mmu, l1_pt, start, end, phys);

	अगर (ret)
		dev_err(atomisp_dev, "setup mapping in L1PT fail.\n");

	mutex_unlock(&mmu->pt_mutex);
	वापस ret;
पूर्ण

/*
 * Free L2 page table according to isp भव address and page physical
 * address
 */
अटल व्योम mmu_l2_unmap(काष्ठा isp_mmu *mmu, phys_addr_t l1_pt,
			 अचिन्हित पूर्णांक l1_idx, phys_addr_t l2_pt,
			 अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end)
अणु
	अचिन्हित पूर्णांक ptr;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक pte;

	l2_pt &= ISP_PAGE_MASK;

	start = start & ISP_PAGE_MASK;
	end = ISP_PAGE_ALIGN(end);

	ptr = start;
	करो अणु
		idx = ISP_PTR_TO_L2_IDX(ptr);

		pte = atomisp_get_pte(l2_pt, idx);

		अगर (!ISP_PTE_VALID(mmu, pte))
			mmu_unmap_l2_pte_error(mmu, l1_pt, l1_idx,
					       l2_pt, idx, ptr, pte);

		atomisp_set_pte(l2_pt, idx, mmu->driver->null_pte);
		mmu->l2_pgt_refcount[l1_idx]--;
		ptr += (1U << ISP_L2PT_OFFSET);
	पूर्ण जबतक (ptr < end && idx < ISP_L2PT_PTES - 1);

	अगर (mmu->l2_pgt_refcount[l1_idx] == 0) अणु
		मुक्त_page_table(mmu, l2_pt);
		atomisp_set_pte(l1_pt, l1_idx, mmu->driver->null_pte);
	पूर्ण
पूर्ण

/*
 * Free L1 page table according to isp भव address and page physical
 * address
 */
अटल व्योम mmu_l1_unmap(काष्ठा isp_mmu *mmu, phys_addr_t l1_pt,
			 अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end)
अणु
	phys_addr_t l2_pt;
	अचिन्हित पूर्णांक ptr, l1_aligned;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक l2_pte;

	l1_pt &= ISP_PAGE_MASK;

	start = start & ISP_PAGE_MASK;
	end = ISP_PAGE_ALIGN(end);

	ptr = start;
	करो अणु
		idx = ISP_PTR_TO_L1_IDX(ptr);

		l2_pte = atomisp_get_pte(l1_pt, idx);

		अगर (!ISP_PTE_VALID(mmu, l2_pte)) अणु
			mmu_unmap_l1_pte_error(mmu, l1_pt, idx, ptr, l2_pte);
			जारी;
		पूर्ण

		l2_pt = isp_pte_to_pgaddr(mmu, l2_pte);

		l1_aligned = (ptr & ISP_PAGE_MASK) + (1U << ISP_L1PT_OFFSET);

		अगर (l1_aligned < end) अणु
			mmu_l2_unmap(mmu, l1_pt, idx, l2_pt, ptr, l1_aligned);
			ptr = l1_aligned;
		पूर्ण अन्यथा अणु
			mmu_l2_unmap(mmu, l1_pt, idx, l2_pt, ptr, end);
			ptr = end;
		पूर्ण
		/*
		 * use the same L2 page next समय, so we करोn't
		 * need to invalidate and मुक्त this PT.
		 */
		/*      atomisp_set_pte(l1_pt, idx, शून्य_PTE); */
	पूर्ण जबतक (ptr < end && idx < ISP_L1PT_PTES);
पूर्ण

/*
 * Free page table according to isp भव address and page physical
 * address
 */
अटल व्योम mmu_unmap(काष्ठा isp_mmu *mmu, अचिन्हित पूर्णांक isp_virt,
		      अचिन्हित पूर्णांक pgnr)
अणु
	अचिन्हित पूर्णांक start, end;
	phys_addr_t l1_pt;

	mutex_lock(&mmu->pt_mutex);
	अगर (!ISP_PTE_VALID(mmu, mmu->l1_pte)) अणु
		mmu_unmap_l1_pt_error(mmu, mmu->l1_pte);
		mutex_unlock(&mmu->pt_mutex);
		वापस;
	पूर्ण

	l1_pt = isp_pte_to_pgaddr(mmu, mmu->l1_pte);

	start = (isp_virt) & ISP_PAGE_MASK;
	end = start + (pgnr << ISP_PAGE_OFFSET);

	mmu_l1_unmap(mmu, l1_pt, start, end);
	mutex_unlock(&mmu->pt_mutex);
पूर्ण

/*
 * Free page tables according to isp start भव address and end भव
 * address.
 */
अटल व्योम मुक्त_mmu_map(काष्ठा isp_mmu *mmu, अचिन्हित पूर्णांक start_isp_virt,
			 अचिन्हित पूर्णांक end_isp_virt)
अणु
	अचिन्हित पूर्णांक pgnr;
	अचिन्हित पूर्णांक start, end;

	start = (start_isp_virt) & ISP_PAGE_MASK;
	end = (end_isp_virt) & ISP_PAGE_MASK;
	pgnr = (end - start) >> ISP_PAGE_OFFSET;
	mmu_unmap(mmu, start, pgnr);
पूर्ण

पूर्णांक isp_mmu_map(काष्ठा isp_mmu *mmu, अचिन्हित पूर्णांक isp_virt,
		phys_addr_t phys, अचिन्हित पूर्णांक pgnr)
अणु
	वापस mmu_map(mmu, isp_virt, phys, pgnr);
पूर्ण

व्योम isp_mmu_unmap(काष्ठा isp_mmu *mmu, अचिन्हित पूर्णांक isp_virt,
		   अचिन्हित पूर्णांक pgnr)
अणु
	mmu_unmap(mmu, isp_virt, pgnr);
पूर्ण

अटल व्योम isp_mmu_flush_tlb_range_शेष(काष्ठा isp_mmu *mmu,
	अचिन्हित पूर्णांक start,
	अचिन्हित पूर्णांक size)
अणु
	isp_mmu_flush_tlb(mmu);
पूर्ण

/*MMU init क्रम पूर्णांकernal काष्ठाure*/
पूर्णांक isp_mmu_init(काष्ठा isp_mmu *mmu, काष्ठा isp_mmu_client *driver)
अणु
	अगर (!mmu)		/* error */
		वापस -EINVAL;
	अगर (!driver)		/* error */
		वापस -EINVAL;

	अगर (!driver->name)
		dev_warn(atomisp_dev, "NULL name for MMU driver...\n");

	mmu->driver = driver;

	अगर (!driver->tlb_flush_all) अणु
		dev_err(atomisp_dev, "tlb_flush_all operation not provided.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!driver->tlb_flush_range)
		driver->tlb_flush_range = isp_mmu_flush_tlb_range_शेष;

	अगर (!driver->pte_valid_mask) अणु
		dev_err(atomisp_dev, "PTE_MASK is missing from mmu driver\n");
		वापस -EINVAL;
	पूर्ण

	mmu->l1_pte = driver->null_pte;

	mutex_init(&mmu->pt_mutex);

	वापस 0;
पूर्ण

/*Free L1 and L2 page table*/
व्योम isp_mmu_निकास(काष्ठा isp_mmu *mmu)
अणु
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक pte;
	phys_addr_t l1_pt, l2_pt;

	अगर (!mmu)
		वापस;

	अगर (!ISP_PTE_VALID(mmu, mmu->l1_pte)) अणु
		dev_warn(atomisp_dev, "invalid L1PT: pte = 0x%x\n",
			 (अचिन्हित पूर्णांक)mmu->l1_pte);
		वापस;
	पूर्ण

	l1_pt = isp_pte_to_pgaddr(mmu, mmu->l1_pte);

	क्रम (idx = 0; idx < ISP_L1PT_PTES; idx++) अणु
		pte = atomisp_get_pte(l1_pt, idx);

		अगर (ISP_PTE_VALID(mmu, pte)) अणु
			l2_pt = isp_pte_to_pgaddr(mmu, pte);

			मुक्त_page_table(mmu, l2_pt);
		पूर्ण
	पूर्ण

	मुक्त_page_table(mmu, l1_pt);
पूर्ण
