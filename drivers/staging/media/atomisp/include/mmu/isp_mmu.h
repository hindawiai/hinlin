<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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
 * ISP MMU driver क्रम classic two-level page tables
 */
#अगर_अघोषित	__ISP_MMU_H__
#घोषणा	__ISP_MMU_H__

#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

/*
 * करो not change these values, the page size क्रम ISP must be the
 * same as kernel's page size.
 */
#घोषणा	ISP_PAGE_OFFSET		12
#घोषणा	ISP_PAGE_SIZE		BIT(ISP_PAGE_OFFSET)
#घोषणा	ISP_PAGE_MASK		(~(phys_addr_t)(ISP_PAGE_SIZE - 1))

#घोषणा	ISP_L1PT_OFFSET		22
#घोषणा	ISP_L1PT_MASK		(~((1U << ISP_L1PT_OFFSET) - 1))

#घोषणा	ISP_L2PT_OFFSET		12
#घोषणा	ISP_L2PT_MASK		(~(ISP_L1PT_MASK | (~(ISP_PAGE_MASK))))

#घोषणा	ISP_L1PT_PTES		1024
#घोषणा	ISP_L2PT_PTES		1024

#घोषणा	ISP_PTR_TO_L1_IDX(x)	((((x) & ISP_L1PT_MASK)) \
					>> ISP_L1PT_OFFSET)

#घोषणा	ISP_PTR_TO_L2_IDX(x)	((((x) & ISP_L2PT_MASK)) \
					>> ISP_L2PT_OFFSET)

#घोषणा	ISP_PAGE_ALIGN(x)	(((x) + (ISP_PAGE_SIZE - 1)) \
					& ISP_PAGE_MASK)

#घोषणा	ISP_PT_TO_VIRT(l1_idx, l2_idx, offset) करो अणु\
		((l1_idx) << ISP_L1PT_OFFSET) | \
		((l2_idx) << ISP_L2PT_OFFSET) | \
		(offset)\
पूर्ण जबतक (0)

#घोषणा	pgnr_to_size(pgnr)	((pgnr) << ISP_PAGE_OFFSET)
#घोषणा	माप_प्रकारo_pgnr_उच्चमान(size)	(((size) + (1 << ISP_PAGE_OFFSET) - 1)\
						>> ISP_PAGE_OFFSET)
#घोषणा	माप_प्रकारo_pgnr_bottom(size)	((size) >> ISP_PAGE_OFFSET)

काष्ठा isp_mmu;

काष्ठा isp_mmu_client अणु
	/*
	 * स्थिर value
	 *
	 * @name:
	 *      driver name
	 * @pte_valid_mask:
	 *      should be 1 bit valid data, meaning the value should
	 *      be घातer of 2.
	 */
	अक्षर *name;
	अचिन्हित पूर्णांक pte_valid_mask;
	अचिन्हित पूर्णांक null_pte;

	/*
	 * get page directory base address (physical address).
	 *
	 * must be provided.
	 */
	अचिन्हित पूर्णांक (*get_pd_base)(काष्ठा isp_mmu *mmu, phys_addr_t pd_base);
	/*
	 * callback to flush tlb.
	 *
	 * tlb_flush_range will at least flush TLBs containing
	 * address mapping from addr to addr + size.
	 *
	 * tlb_flush_all will flush all TLBs.
	 *
	 * tlb_flush_all is must be provided. अगर tlb_flush_range is
	 * not valid, it will set to tlb_flush_all by शेष.
	 */
	व्योम (*tlb_flush_range)(काष्ठा isp_mmu *mmu,
				अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक size);
	व्योम (*tlb_flush_all)(काष्ठा isp_mmu *mmu);
	अचिन्हित पूर्णांक (*phys_to_pte)(काष्ठा isp_mmu *mmu,
				    phys_addr_t phys);
	phys_addr_t (*pte_to_phys)(काष्ठा isp_mmu *mmu,
				   अचिन्हित पूर्णांक pte);

पूर्ण;

काष्ठा isp_mmu अणु
	काष्ठा isp_mmu_client *driver;
	अचिन्हित पूर्णांक l1_pte;
	पूर्णांक l2_pgt_refcount[ISP_L1PT_PTES];
	phys_addr_t base_address;

	काष्ठा mutex pt_mutex;
पूर्ण;

/* flags क्रम PDE and PTE */
#घोषणा	ISP_PTE_VALID_MASK(mmu)	\
	((mmu)->driver->pte_valid_mask)

#घोषणा	ISP_PTE_VALID(mmu, pte)	\
	((pte) & ISP_PTE_VALID_MASK(mmu))

#घोषणा	शून्य_PAGE	((phys_addr_t)(-1) & ISP_PAGE_MASK)
#घोषणा	PAGE_VALID(page)	((page) != शून्य_PAGE)

/*
 * init mmu with specअगरic mmu driver.
 */
पूर्णांक isp_mmu_init(काष्ठा isp_mmu *mmu, काष्ठा isp_mmu_client *driver);
/*
 * cleanup all mmu related things.
 */
व्योम isp_mmu_निकास(काष्ठा isp_mmu *mmu);

/*
 * setup/हटाओ address mapping क्रम pgnr continuous physical pages
 * and isp_virt.
 *
 * map/unmap is mutex lock रक्षित, and caller करोes not have
 * to करो lock/unlock operation.
 *
 * map/unmap will not flush tlb, and caller needs to deal with
 * this itself.
 */
पूर्णांक isp_mmu_map(काष्ठा isp_mmu *mmu, अचिन्हित पूर्णांक isp_virt,
		phys_addr_t phys, अचिन्हित पूर्णांक pgnr);

व्योम isp_mmu_unmap(काष्ठा isp_mmu *mmu, अचिन्हित पूर्णांक isp_virt,
		   अचिन्हित पूर्णांक pgnr);

अटल अंतरभूत व्योम isp_mmu_flush_tlb_all(काष्ठा isp_mmu *mmu)
अणु
	अगर (mmu->driver && mmu->driver->tlb_flush_all)
		mmu->driver->tlb_flush_all(mmu);
पूर्ण

#घोषणा isp_mmu_flush_tlb isp_mmu_flush_tlb_all

अटल अंतरभूत व्योम isp_mmu_flush_tlb_range(काष्ठा isp_mmu *mmu,
	अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक size)
अणु
	अगर (mmu->driver && mmu->driver->tlb_flush_range)
		mmu->driver->tlb_flush_range(mmu, start, size);
पूर्ण

#पूर्ण_अगर /* ISP_MMU_H_ */
