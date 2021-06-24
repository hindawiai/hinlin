<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

/* The name "mmu.h is already taken" */
#समावेश "mmu_device.h"

व्योम mmu_set_page_table_base_index(
    स्थिर mmu_ID_t		ID,
    स्थिर hrt_data		base_index)
अणु
	mmu_reg_store(ID, _HRT_MMU_PAGE_TABLE_BASE_ADDRESS_REG_IDX, base_index);
	वापस;
पूर्ण

hrt_data mmu_get_page_table_base_index(
    स्थिर mmu_ID_t		ID)
अणु
	वापस mmu_reg_load(ID, _HRT_MMU_PAGE_TABLE_BASE_ADDRESS_REG_IDX);
पूर्ण

व्योम mmu_invalidate_cache(
    स्थिर mmu_ID_t		ID)
अणु
	mmu_reg_store(ID, _HRT_MMU_INVALIDATE_TLB_REG_IDX, 1);
	वापस;
पूर्ण

व्योम mmu_invalidate_cache_all(व्योम)
अणु
	mmu_ID_t	mmu_id;

	क्रम (mmu_id = (mmu_ID_t)0; mmu_id < N_MMU_ID; mmu_id++) अणु
		mmu_invalidate_cache(mmu_id);
	पूर्ण
पूर्ण
