<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
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

#समावेश "ia_css_mmu.h"
#समावेश "ia_css_mmu_private.h"
#समावेश <ia_css_debug.h>
#समावेश "sh_css_sp.h"
#समावेश "sh_css_firmware.h"
#समावेश "sp.h"
#समावेश "mmu_device.h"

व्योम
ia_css_mmu_invalidate_cache(व्योम)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw = &sh_css_sp_fw;
	अचिन्हित पूर्णांक HIVE_ADDR_ia_css_dmaproxy_sp_invalidate_tlb;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_mmu_invalidate_cache() enter\n");

	/* अगर the SP is not running we should not access its dmem */
	अगर (sh_css_sp_is_running()) अणु
		HIVE_ADDR_ia_css_dmaproxy_sp_invalidate_tlb = fw->info.sp.invalidate_tlb;

		(व्योम)HIVE_ADDR_ia_css_dmaproxy_sp_invalidate_tlb; /* Suppres warnings in CRUN */

		sp_dmem_store_uपूर्णांक32(SP0_ID,
				     (अचिन्हित पूर्णांक)sp_address_of(ia_css_dmaproxy_sp_invalidate_tlb),
				     true);
	पूर्ण
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_mmu_invalidate_cache() leave\n");
पूर्ण

व्योम
sh_css_mmu_set_page_table_base_index(hrt_data base_index)
अणु
	पूर्णांक i;

	IA_CSS_ENTER_PRIVATE("base_index=0x%08x\n", base_index);
	क्रम (i = 0; i < N_MMU_ID; i++) अणु
		mmu_ID_t mmu_id = i;

		mmu_set_page_table_base_index(mmu_id, base_index);
		mmu_invalidate_cache(mmu_id);
	पूर्ण
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण
