<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश "i40e.h"
#समावेश "i40e_osdep.h"
#समावेश "i40e_register.h"
#समावेश "i40e_status.h"
#समावेश "i40e_alloc.h"
#समावेश "i40e_hmc.h"
#समावेश "i40e_type.h"

/**
 * i40e_add_sd_table_entry - Adds a segment descriptor to the table
 * @hw: poपूर्णांकer to our hw काष्ठा
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठा
 * @sd_index: segment descriptor index to manipulate
 * @type: what type of segment descriptor we're manipulating
 * @direct_mode_sz: size to alloc in direct mode
 **/
i40e_status i40e_add_sd_table_entry(काष्ठा i40e_hw *hw,
					      काष्ठा i40e_hmc_info *hmc_info,
					      u32 sd_index,
					      क्रमागत i40e_sd_entry_type type,
					      u64 direct_mode_sz)
अणु
	क्रमागत i40e_memory_type mem_type __attribute__((unused));
	काष्ठा i40e_hmc_sd_entry *sd_entry;
	bool dma_mem_alloc_करोne = false;
	काष्ठा i40e_dma_mem mem;
	i40e_status ret_code = I40E_SUCCESS;
	u64 alloc_len;

	अगर (शून्य == hmc_info->sd_table.sd_entry) अणु
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_add_sd_table_entry: bad sd_entry\n");
		जाओ निकास;
	पूर्ण

	अगर (sd_index >= hmc_info->sd_table.sd_cnt) अणु
		ret_code = I40E_ERR_INVALID_SD_INDEX;
		hw_dbg(hw, "i40e_add_sd_table_entry: bad sd_index\n");
		जाओ निकास;
	पूर्ण

	sd_entry = &hmc_info->sd_table.sd_entry[sd_index];
	अगर (!sd_entry->valid) अणु
		अगर (I40E_SD_TYPE_PAGED == type) अणु
			mem_type = i40e_mem_pd;
			alloc_len = I40E_HMC_PAGED_BP_SIZE;
		पूर्ण अन्यथा अणु
			mem_type = i40e_mem_bp_jumbo;
			alloc_len = direct_mode_sz;
		पूर्ण

		/* allocate a 4K pd page or 2M backing page */
		ret_code = i40e_allocate_dma_mem(hw, &mem, mem_type, alloc_len,
						 I40E_HMC_PD_BP_BUF_ALIGNMENT);
		अगर (ret_code)
			जाओ निकास;
		dma_mem_alloc_करोne = true;
		अगर (I40E_SD_TYPE_PAGED == type) अणु
			ret_code = i40e_allocate_virt_mem(hw,
					&sd_entry->u.pd_table.pd_entry_virt_mem,
					माप(काष्ठा i40e_hmc_pd_entry) * 512);
			अगर (ret_code)
				जाओ निकास;
			sd_entry->u.pd_table.pd_entry =
				(काष्ठा i40e_hmc_pd_entry *)
				sd_entry->u.pd_table.pd_entry_virt_mem.va;
			sd_entry->u.pd_table.pd_page_addr = mem;
		पूर्ण अन्यथा अणु
			sd_entry->u.bp.addr = mem;
			sd_entry->u.bp.sd_pd_index = sd_index;
		पूर्ण
		/* initialize the sd entry */
		hmc_info->sd_table.sd_entry[sd_index].entry_type = type;

		/* increment the ref count */
		I40E_INC_SD_REFCNT(&hmc_info->sd_table);
	पूर्ण
	/* Increment backing page reference count */
	अगर (I40E_SD_TYPE_सूचीECT == sd_entry->entry_type)
		I40E_INC_BP_REFCNT(&sd_entry->u.bp);
निकास:
	अगर (ret_code)
		अगर (dma_mem_alloc_करोne)
			i40e_मुक्त_dma_mem(hw, &mem);

	वापस ret_code;
पूर्ण

/**
 * i40e_add_pd_table_entry - Adds page descriptor to the specअगरied table
 * @hw: poपूर्णांकer to our HW काष्ठाure
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठाure
 * @pd_index: which page descriptor index to manipulate
 * @rsrc_pg: अगर not शून्य, use pपुनः_स्मृतिated page instead of allocating new one.
 *
 * This function:
 *	1. Initializes the pd entry
 *	2. Adds pd_entry in the pd_table
 *	3. Mark the entry valid in i40e_hmc_pd_entry काष्ठाure
 *	4. Initializes the pd_entry's ref count to 1
 * assumptions:
 *	1. The memory क्रम pd should be pinned करोwn, physically contiguous and
 *	   aligned on 4K boundary and zeroed memory.
 *	2. It should be 4K in size.
 **/
i40e_status i40e_add_pd_table_entry(काष्ठा i40e_hw *hw,
					      काष्ठा i40e_hmc_info *hmc_info,
					      u32 pd_index,
					      काष्ठा i40e_dma_mem *rsrc_pg)
अणु
	i40e_status ret_code = 0;
	काष्ठा i40e_hmc_pd_table *pd_table;
	काष्ठा i40e_hmc_pd_entry *pd_entry;
	काष्ठा i40e_dma_mem mem;
	काष्ठा i40e_dma_mem *page = &mem;
	u32 sd_idx, rel_pd_idx;
	u64 *pd_addr;
	u64 page_desc;

	अगर (pd_index / I40E_HMC_PD_CNT_IN_SD >= hmc_info->sd_table.sd_cnt) अणु
		ret_code = I40E_ERR_INVALID_PAGE_DESC_INDEX;
		hw_dbg(hw, "i40e_add_pd_table_entry: bad pd_index\n");
		जाओ निकास;
	पूर्ण

	/* find corresponding sd */
	sd_idx = (pd_index / I40E_HMC_PD_CNT_IN_SD);
	अगर (I40E_SD_TYPE_PAGED !=
	    hmc_info->sd_table.sd_entry[sd_idx].entry_type)
		जाओ निकास;

	rel_pd_idx = (pd_index % I40E_HMC_PD_CNT_IN_SD);
	pd_table = &hmc_info->sd_table.sd_entry[sd_idx].u.pd_table;
	pd_entry = &pd_table->pd_entry[rel_pd_idx];
	अगर (!pd_entry->valid) अणु
		अगर (rsrc_pg) अणु
			pd_entry->rsrc_pg = true;
			page = rsrc_pg;
		पूर्ण अन्यथा अणु
			/* allocate a 4K backing page */
			ret_code = i40e_allocate_dma_mem(hw, page, i40e_mem_bp,
						I40E_HMC_PAGED_BP_SIZE,
						I40E_HMC_PD_BP_BUF_ALIGNMENT);
			अगर (ret_code)
				जाओ निकास;
			pd_entry->rsrc_pg = false;
		पूर्ण

		pd_entry->bp.addr = *page;
		pd_entry->bp.sd_pd_index = pd_index;
		pd_entry->bp.entry_type = I40E_SD_TYPE_PAGED;
		/* Set page address and valid bit */
		page_desc = page->pa | 0x1;

		pd_addr = (u64 *)pd_table->pd_page_addr.va;
		pd_addr += rel_pd_idx;

		/* Add the backing page physical address in the pd entry */
		स_नकल(pd_addr, &page_desc, माप(u64));

		pd_entry->sd_index = sd_idx;
		pd_entry->valid = true;
		I40E_INC_PD_REFCNT(pd_table);
	पूर्ण
	I40E_INC_BP_REFCNT(&pd_entry->bp);
निकास:
	वापस ret_code;
पूर्ण

/**
 * i40e_हटाओ_pd_bp - हटाओ a backing page from a page descriptor
 * @hw: poपूर्णांकer to our HW काष्ठाure
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठाure
 * @idx: the page index
 *
 * This function:
 *	1. Marks the entry in pd tabe (क्रम paged address mode) or in sd table
 *	   (क्रम direct address mode) invalid.
 *	2. Write to रेजिस्टर PMPDINV to invalidate the backing page in FV cache
 *	3. Decrement the ref count क्रम the pd _entry
 * assumptions:
 *	1. Caller can deallocate the memory used by backing storage after this
 *	   function वापसs.
 **/
i40e_status i40e_हटाओ_pd_bp(काष्ठा i40e_hw *hw,
					काष्ठा i40e_hmc_info *hmc_info,
					u32 idx)
अणु
	i40e_status ret_code = 0;
	काष्ठा i40e_hmc_pd_entry *pd_entry;
	काष्ठा i40e_hmc_pd_table *pd_table;
	काष्ठा i40e_hmc_sd_entry *sd_entry;
	u32 sd_idx, rel_pd_idx;
	u64 *pd_addr;

	/* calculate index */
	sd_idx = idx / I40E_HMC_PD_CNT_IN_SD;
	rel_pd_idx = idx % I40E_HMC_PD_CNT_IN_SD;
	अगर (sd_idx >= hmc_info->sd_table.sd_cnt) अणु
		ret_code = I40E_ERR_INVALID_PAGE_DESC_INDEX;
		hw_dbg(hw, "i40e_remove_pd_bp: bad idx\n");
		जाओ निकास;
	पूर्ण
	sd_entry = &hmc_info->sd_table.sd_entry[sd_idx];
	अगर (I40E_SD_TYPE_PAGED != sd_entry->entry_type) अणु
		ret_code = I40E_ERR_INVALID_SD_TYPE;
		hw_dbg(hw, "i40e_remove_pd_bp: wrong sd_entry type\n");
		जाओ निकास;
	पूर्ण
	/* get the entry and decrease its ref counter */
	pd_table = &hmc_info->sd_table.sd_entry[sd_idx].u.pd_table;
	pd_entry = &pd_table->pd_entry[rel_pd_idx];
	I40E_DEC_BP_REFCNT(&pd_entry->bp);
	अगर (pd_entry->bp.ref_cnt)
		जाओ निकास;

	/* mark the entry invalid */
	pd_entry->valid = false;
	I40E_DEC_PD_REFCNT(pd_table);
	pd_addr = (u64 *)pd_table->pd_page_addr.va;
	pd_addr += rel_pd_idx;
	स_रखो(pd_addr, 0, माप(u64));
	I40E_INVALIDATE_PF_HMC_PD(hw, sd_idx, idx);

	/* मुक्त memory here */
	अगर (!pd_entry->rsrc_pg)
		ret_code = i40e_मुक्त_dma_mem(hw, &pd_entry->bp.addr);
	अगर (ret_code)
		जाओ निकास;
	अगर (!pd_table->ref_cnt)
		i40e_मुक्त_virt_mem(hw, &pd_table->pd_entry_virt_mem);
निकास:
	वापस ret_code;
पूर्ण

/**
 * i40e_prep_हटाओ_sd_bp - Prepares to हटाओ a backing page from a sd entry
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठाure
 * @idx: the page index
 **/
i40e_status i40e_prep_हटाओ_sd_bp(काष्ठा i40e_hmc_info *hmc_info,
					     u32 idx)
अणु
	i40e_status ret_code = 0;
	काष्ठा i40e_hmc_sd_entry *sd_entry;

	/* get the entry and decrease its ref counter */
	sd_entry = &hmc_info->sd_table.sd_entry[idx];
	I40E_DEC_BP_REFCNT(&sd_entry->u.bp);
	अगर (sd_entry->u.bp.ref_cnt) अणु
		ret_code = I40E_ERR_NOT_READY;
		जाओ निकास;
	पूर्ण
	I40E_DEC_SD_REFCNT(&hmc_info->sd_table);

	/* mark the entry invalid */
	sd_entry->valid = false;
निकास:
	वापस ret_code;
पूर्ण

/**
 * i40e_हटाओ_sd_bp_new - Removes a backing page from a segment descriptor
 * @hw: poपूर्णांकer to our hw काष्ठा
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठाure
 * @idx: the page index
 * @is_pf: used to distinguish between VF and PF
 **/
i40e_status i40e_हटाओ_sd_bp_new(काष्ठा i40e_hw *hw,
					    काष्ठा i40e_hmc_info *hmc_info,
					    u32 idx, bool is_pf)
अणु
	काष्ठा i40e_hmc_sd_entry *sd_entry;

	अगर (!is_pf)
		वापस I40E_NOT_SUPPORTED;

	/* get the entry and decrease its ref counter */
	sd_entry = &hmc_info->sd_table.sd_entry[idx];
	I40E_CLEAR_PF_SD_ENTRY(hw, idx, I40E_SD_TYPE_सूचीECT);

	वापस i40e_मुक्त_dma_mem(hw, &sd_entry->u.bp.addr);
पूर्ण

/**
 * i40e_prep_हटाओ_pd_page - Prepares to हटाओ a PD page from sd entry.
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठाure
 * @idx: segment descriptor index to find the relevant page descriptor
 **/
i40e_status i40e_prep_हटाओ_pd_page(काष्ठा i40e_hmc_info *hmc_info,
					       u32 idx)
अणु
	i40e_status ret_code = 0;
	काष्ठा i40e_hmc_sd_entry *sd_entry;

	sd_entry = &hmc_info->sd_table.sd_entry[idx];

	अगर (sd_entry->u.pd_table.ref_cnt) अणु
		ret_code = I40E_ERR_NOT_READY;
		जाओ निकास;
	पूर्ण

	/* mark the entry invalid */
	sd_entry->valid = false;

	I40E_DEC_SD_REFCNT(&hmc_info->sd_table);
निकास:
	वापस ret_code;
पूर्ण

/**
 * i40e_हटाओ_pd_page_new - Removes a PD page from sd entry.
 * @hw: poपूर्णांकer to our hw काष्ठा
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठाure
 * @idx: segment descriptor index to find the relevant page descriptor
 * @is_pf: used to distinguish between VF and PF
 **/
i40e_status i40e_हटाओ_pd_page_new(काष्ठा i40e_hw *hw,
					      काष्ठा i40e_hmc_info *hmc_info,
					      u32 idx, bool is_pf)
अणु
	काष्ठा i40e_hmc_sd_entry *sd_entry;

	अगर (!is_pf)
		वापस I40E_NOT_SUPPORTED;

	sd_entry = &hmc_info->sd_table.sd_entry[idx];
	I40E_CLEAR_PF_SD_ENTRY(hw, idx, I40E_SD_TYPE_PAGED);

	वापस  i40e_मुक्त_dma_mem(hw, &sd_entry->u.pd_table.pd_page_addr);
पूर्ण
