<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Merrअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2012 Intel Corporation. All Rights Reserved.
 *
 * Copyright (c) 2012 Silicon Hive www.siliconhive.com.
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
#समावेश "type_support.h"
#समावेश "mmu/isp_mmu.h"
#समावेश "mmu/sh_mmu_mrfld.h"
#समावेश "atomisp_compat.h"

#घोषणा MERR_VALID_PTE_MASK	0x80000000

/*
 * include SH header file here
 */

अटल अचिन्हित पूर्णांक sh_phys_to_pte(काष्ठा isp_mmu *mmu,
				   phys_addr_t phys)
अणु
	वापस phys >> ISP_PAGE_OFFSET;
पूर्ण

अटल phys_addr_t sh_pte_to_phys(काष्ठा isp_mmu *mmu,
				  अचिन्हित पूर्णांक pte)
अणु
	अचिन्हित पूर्णांक mask = mmu->driver->pte_valid_mask;

	वापस (phys_addr_t)((pte & ~mask) << ISP_PAGE_OFFSET);
पूर्ण

अटल अचिन्हित पूर्णांक sh_get_pd_base(काष्ठा isp_mmu *mmu,
				   phys_addr_t phys)
अणु
	अचिन्हित पूर्णांक pte = sh_phys_to_pte(mmu, phys);

	वापस HOST_ADDRESS(pte);
पूर्ण

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
अटल व्योम sh_tlb_flush(काष्ठा isp_mmu *mmu)
अणु
	ia_css_mmu_invalidate_cache();
पूर्ण

काष्ठा isp_mmu_client sh_mmu_mrfld = अणु
	.name = "Silicon Hive ISP3000 MMU",
	.pte_valid_mask = MERR_VALID_PTE_MASK,
	.null_pte = ~MERR_VALID_PTE_MASK,
	.get_pd_base = sh_get_pd_base,
	.tlb_flush_all = sh_tlb_flush,
	.phys_to_pte = sh_phys_to_pte,
	.pte_to_phys = sh_pte_to_phys,
पूर्ण;
