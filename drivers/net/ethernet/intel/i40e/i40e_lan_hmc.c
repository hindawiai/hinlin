<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश "i40e.h"
#समावेश "i40e_osdep.h"
#समावेश "i40e_register.h"
#समावेश "i40e_type.h"
#समावेश "i40e_hmc.h"
#समावेश "i40e_lan_hmc.h"
#समावेश "i40e_prototype.h"

/* lan specअगरic पूर्णांकerface functions */

/**
 * i40e_align_l2obj_base - aligns base object poपूर्णांकer to 512 bytes
 * @offset: base address offset needing alignment
 *
 * Aligns the layer 2 function निजी memory so it's 512-byte aligned.
 **/
अटल u64 i40e_align_l2obj_base(u64 offset)
अणु
	u64 aligned_offset = offset;

	अगर ((offset % I40E_HMC_L2OBJ_BASE_ALIGNMENT) > 0)
		aligned_offset += (I40E_HMC_L2OBJ_BASE_ALIGNMENT -
				   (offset % I40E_HMC_L2OBJ_BASE_ALIGNMENT));

	वापस aligned_offset;
पूर्ण

/**
 * i40e_calculate_l2fpm_size - calculates layer 2 FPM memory size
 * @txq_num: number of Tx queues needing backing context
 * @rxq_num: number of Rx queues needing backing context
 * @fcoe_cntx_num: amount of FCoE statefull contexts needing backing context
 * @fcoe_filt_num: number of FCoE filters needing backing context
 *
 * Calculates the maximum amount of memory क्रम the function required, based
 * on the number of resources it must provide context क्रम.
 **/
अटल u64 i40e_calculate_l2fpm_size(u32 txq_num, u32 rxq_num,
			      u32 fcoe_cntx_num, u32 fcoe_filt_num)
अणु
	u64 fpm_size = 0;

	fpm_size = txq_num * I40E_HMC_OBJ_SIZE_TXQ;
	fpm_size = i40e_align_l2obj_base(fpm_size);

	fpm_size += (rxq_num * I40E_HMC_OBJ_SIZE_RXQ);
	fpm_size = i40e_align_l2obj_base(fpm_size);

	fpm_size += (fcoe_cntx_num * I40E_HMC_OBJ_SIZE_FCOE_CNTX);
	fpm_size = i40e_align_l2obj_base(fpm_size);

	fpm_size += (fcoe_filt_num * I40E_HMC_OBJ_SIZE_FCOE_FILT);
	fpm_size = i40e_align_l2obj_base(fpm_size);

	वापस fpm_size;
पूर्ण

/**
 * i40e_init_lan_hmc - initialize i40e_hmc_info काष्ठा
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @txq_num: number of Tx queues needing backing context
 * @rxq_num: number of Rx queues needing backing context
 * @fcoe_cntx_num: amount of FCoE statefull contexts needing backing context
 * @fcoe_filt_num: number of FCoE filters needing backing context
 *
 * This function will be called once per physical function initialization.
 * It will fill out the i40e_hmc_obj_info काष्ठाure क्रम LAN objects based on
 * the driver's provided input, as well as inक्रमmation from the HMC itself
 * loaded from NVRAM.
 *
 * Assumptions:
 *   - HMC Resource Profile has been selected beक्रमe calling this function.
 **/
i40e_status i40e_init_lan_hmc(काष्ठा i40e_hw *hw, u32 txq_num,
					u32 rxq_num, u32 fcoe_cntx_num,
					u32 fcoe_filt_num)
अणु
	काष्ठा i40e_hmc_obj_info *obj, *full_obj;
	i40e_status ret_code = 0;
	u64 l2fpm_size;
	u32 size_exp;

	hw->hmc.signature = I40E_HMC_INFO_SIGNATURE;
	hw->hmc.hmc_fn_id = hw->pf_id;

	/* allocate memory क्रम hmc_obj */
	ret_code = i40e_allocate_virt_mem(hw, &hw->hmc.hmc_obj_virt_mem,
			माप(काष्ठा i40e_hmc_obj_info) * I40E_HMC_LAN_MAX);
	अगर (ret_code)
		जाओ init_lan_hmc_out;
	hw->hmc.hmc_obj = (काष्ठा i40e_hmc_obj_info *)
			  hw->hmc.hmc_obj_virt_mem.va;

	/* The full object will be used to create the LAN HMC SD */
	full_obj = &hw->hmc.hmc_obj[I40E_HMC_LAN_FULL];
	full_obj->max_cnt = 0;
	full_obj->cnt = 0;
	full_obj->base = 0;
	full_obj->size = 0;

	/* Tx queue context inक्रमmation */
	obj = &hw->hmc.hmc_obj[I40E_HMC_LAN_TX];
	obj->max_cnt = rd32(hw, I40E_GLHMC_LANQMAX);
	obj->cnt = txq_num;
	obj->base = 0;
	size_exp = rd32(hw, I40E_GLHMC_LANTXOBJSZ);
	obj->size = BIT_ULL(size_exp);

	/* validate values requested by driver करोn't exceed HMC capacity */
	अगर (txq_num > obj->max_cnt) अणु
		ret_code = I40E_ERR_INVALID_HMC_OBJ_COUNT;
		hw_dbg(hw, "i40e_init_lan_hmc: Tx context: asks for 0x%x but max allowed is 0x%x, returns error %d\n",
			  txq_num, obj->max_cnt, ret_code);
		जाओ init_lan_hmc_out;
	पूर्ण

	/* aggregate values पूर्णांकo the full LAN object क्रम later */
	full_obj->max_cnt += obj->max_cnt;
	full_obj->cnt += obj->cnt;

	/* Rx queue context inक्रमmation */
	obj = &hw->hmc.hmc_obj[I40E_HMC_LAN_RX];
	obj->max_cnt = rd32(hw, I40E_GLHMC_LANQMAX);
	obj->cnt = rxq_num;
	obj->base = hw->hmc.hmc_obj[I40E_HMC_LAN_TX].base +
		    (hw->hmc.hmc_obj[I40E_HMC_LAN_TX].cnt *
		     hw->hmc.hmc_obj[I40E_HMC_LAN_TX].size);
	obj->base = i40e_align_l2obj_base(obj->base);
	size_exp = rd32(hw, I40E_GLHMC_LANRXOBJSZ);
	obj->size = BIT_ULL(size_exp);

	/* validate values requested by driver करोn't exceed HMC capacity */
	अगर (rxq_num > obj->max_cnt) अणु
		ret_code = I40E_ERR_INVALID_HMC_OBJ_COUNT;
		hw_dbg(hw, "i40e_init_lan_hmc: Rx context: asks for 0x%x but max allowed is 0x%x, returns error %d\n",
			  rxq_num, obj->max_cnt, ret_code);
		जाओ init_lan_hmc_out;
	पूर्ण

	/* aggregate values पूर्णांकo the full LAN object क्रम later */
	full_obj->max_cnt += obj->max_cnt;
	full_obj->cnt += obj->cnt;

	/* FCoE context inक्रमmation */
	obj = &hw->hmc.hmc_obj[I40E_HMC_FCOE_CTX];
	obj->max_cnt = rd32(hw, I40E_GLHMC_FCOEMAX);
	obj->cnt = fcoe_cntx_num;
	obj->base = hw->hmc.hmc_obj[I40E_HMC_LAN_RX].base +
		    (hw->hmc.hmc_obj[I40E_HMC_LAN_RX].cnt *
		     hw->hmc.hmc_obj[I40E_HMC_LAN_RX].size);
	obj->base = i40e_align_l2obj_base(obj->base);
	size_exp = rd32(hw, I40E_GLHMC_FCOEDDPOBJSZ);
	obj->size = BIT_ULL(size_exp);

	/* validate values requested by driver करोn't exceed HMC capacity */
	अगर (fcoe_cntx_num > obj->max_cnt) अणु
		ret_code = I40E_ERR_INVALID_HMC_OBJ_COUNT;
		hw_dbg(hw, "i40e_init_lan_hmc: FCoE context: asks for 0x%x but max allowed is 0x%x, returns error %d\n",
			  fcoe_cntx_num, obj->max_cnt, ret_code);
		जाओ init_lan_hmc_out;
	पूर्ण

	/* aggregate values पूर्णांकo the full LAN object क्रम later */
	full_obj->max_cnt += obj->max_cnt;
	full_obj->cnt += obj->cnt;

	/* FCoE filter inक्रमmation */
	obj = &hw->hmc.hmc_obj[I40E_HMC_FCOE_FILT];
	obj->max_cnt = rd32(hw, I40E_GLHMC_FCOEFMAX);
	obj->cnt = fcoe_filt_num;
	obj->base = hw->hmc.hmc_obj[I40E_HMC_FCOE_CTX].base +
		    (hw->hmc.hmc_obj[I40E_HMC_FCOE_CTX].cnt *
		     hw->hmc.hmc_obj[I40E_HMC_FCOE_CTX].size);
	obj->base = i40e_align_l2obj_base(obj->base);
	size_exp = rd32(hw, I40E_GLHMC_FCOEFOBJSZ);
	obj->size = BIT_ULL(size_exp);

	/* validate values requested by driver करोn't exceed HMC capacity */
	अगर (fcoe_filt_num > obj->max_cnt) अणु
		ret_code = I40E_ERR_INVALID_HMC_OBJ_COUNT;
		hw_dbg(hw, "i40e_init_lan_hmc: FCoE filter: asks for 0x%x but max allowed is 0x%x, returns error %d\n",
			  fcoe_filt_num, obj->max_cnt, ret_code);
		जाओ init_lan_hmc_out;
	पूर्ण

	/* aggregate values पूर्णांकo the full LAN object क्रम later */
	full_obj->max_cnt += obj->max_cnt;
	full_obj->cnt += obj->cnt;

	hw->hmc.first_sd_index = 0;
	hw->hmc.sd_table.ref_cnt = 0;
	l2fpm_size = i40e_calculate_l2fpm_size(txq_num, rxq_num, fcoe_cntx_num,
					       fcoe_filt_num);
	अगर (शून्य == hw->hmc.sd_table.sd_entry) अणु
		hw->hmc.sd_table.sd_cnt = (u32)
				   (l2fpm_size + I40E_HMC_सूचीECT_BP_SIZE - 1) /
				   I40E_HMC_सूचीECT_BP_SIZE;

		/* allocate the sd_entry members in the sd_table */
		ret_code = i40e_allocate_virt_mem(hw, &hw->hmc.sd_table.addr,
					  (माप(काष्ठा i40e_hmc_sd_entry) *
					  hw->hmc.sd_table.sd_cnt));
		अगर (ret_code)
			जाओ init_lan_hmc_out;
		hw->hmc.sd_table.sd_entry =
			(काष्ठा i40e_hmc_sd_entry *)hw->hmc.sd_table.addr.va;
	पूर्ण
	/* store in the LAN full object क्रम later */
	full_obj->size = l2fpm_size;

init_lan_hmc_out:
	वापस ret_code;
पूर्ण

/**
 * i40e_हटाओ_pd_page - Remove a page from the page descriptor table
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठाure
 * @idx: segment descriptor index to find the relevant page descriptor
 *
 * This function:
 *	1. Marks the entry in pd table (क्रम paged address mode) invalid
 *	2. ग_लिखो to रेजिस्टर PMPDINV to invalidate the backing page in FV cache
 *	3. Decrement the ref count क्रम  pd_entry
 * assumptions:
 *	1. caller can deallocate the memory used by pd after this function
 *	   वापसs.
 **/
अटल i40e_status i40e_हटाओ_pd_page(काष्ठा i40e_hw *hw,
						 काष्ठा i40e_hmc_info *hmc_info,
						 u32 idx)
अणु
	i40e_status ret_code = 0;

	अगर (!i40e_prep_हटाओ_pd_page(hmc_info, idx))
		ret_code = i40e_हटाओ_pd_page_new(hw, hmc_info, idx, true);

	वापस ret_code;
पूर्ण

/**
 * i40e_हटाओ_sd_bp - हटाओ a backing page from a segment descriptor
 * @hw: poपूर्णांकer to our HW काष्ठाure
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठाure
 * @idx: the page index
 *
 * This function:
 *	1. Marks the entry in sd table (क्रम direct address mode) invalid
 *	2. ग_लिखो to रेजिस्टर PMSDCMD, PMSDDATALOW(PMSDDATALOW.PMSDVALID set
 *	   to 0) and PMSDDATAHIGH to invalidate the sd page
 *	3. Decrement the ref count क्रम the sd_entry
 * assumptions:
 *	1. caller can deallocate the memory used by backing storage after this
 *	   function वापसs.
 **/
अटल i40e_status i40e_हटाओ_sd_bp(काष्ठा i40e_hw *hw,
					       काष्ठा i40e_hmc_info *hmc_info,
					       u32 idx)
अणु
	i40e_status ret_code = 0;

	अगर (!i40e_prep_हटाओ_sd_bp(hmc_info, idx))
		ret_code = i40e_हटाओ_sd_bp_new(hw, hmc_info, idx, true);

	वापस ret_code;
पूर्ण

/**
 * i40e_create_lan_hmc_object - allocate backing store क्रम hmc objects
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @info: poपूर्णांकer to i40e_hmc_create_obj_info काष्ठा
 *
 * This will allocate memory क्रम PDs and backing pages and populate
 * the sd and pd entries.
 **/
अटल i40e_status i40e_create_lan_hmc_object(काष्ठा i40e_hw *hw,
				काष्ठा i40e_hmc_lan_create_obj_info *info)
अणु
	i40e_status ret_code = 0;
	काष्ठा i40e_hmc_sd_entry *sd_entry;
	u32 pd_idx1 = 0, pd_lmt1 = 0;
	u32 pd_idx = 0, pd_lmt = 0;
	bool pd_error = false;
	u32 sd_idx, sd_lmt;
	u64 sd_size;
	u32 i, j;

	अगर (शून्य == info) अणु
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_create_lan_hmc_object: bad info ptr\n");
		जाओ निकास;
	पूर्ण
	अगर (शून्य == info->hmc_info) अणु
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_create_lan_hmc_object: bad hmc_info ptr\n");
		जाओ निकास;
	पूर्ण
	अगर (I40E_HMC_INFO_SIGNATURE != info->hmc_info->signature) अणु
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_create_lan_hmc_object: bad signature\n");
		जाओ निकास;
	पूर्ण

	अगर (info->start_idx >= info->hmc_info->hmc_obj[info->rsrc_type].cnt) अणु
		ret_code = I40E_ERR_INVALID_HMC_OBJ_INDEX;
		hw_dbg(hw, "i40e_create_lan_hmc_object: returns error %d\n",
			  ret_code);
		जाओ निकास;
	पूर्ण
	अगर ((info->start_idx + info->count) >
	    info->hmc_info->hmc_obj[info->rsrc_type].cnt) अणु
		ret_code = I40E_ERR_INVALID_HMC_OBJ_COUNT;
		hw_dbg(hw, "i40e_create_lan_hmc_object: returns error %d\n",
			  ret_code);
		जाओ निकास;
	पूर्ण

	/* find sd index and limit */
	I40E_FIND_SD_INDEX_LIMIT(info->hmc_info, info->rsrc_type,
				 info->start_idx, info->count,
				 &sd_idx, &sd_lmt);
	अगर (sd_idx >= info->hmc_info->sd_table.sd_cnt ||
	    sd_lmt > info->hmc_info->sd_table.sd_cnt) अणु
			ret_code = I40E_ERR_INVALID_SD_INDEX;
			जाओ निकास;
	पूर्ण
	/* find pd index */
	I40E_FIND_PD_INDEX_LIMIT(info->hmc_info, info->rsrc_type,
				 info->start_idx, info->count, &pd_idx,
				 &pd_lmt);

	/* This is to cover क्रम हालs where you may not want to have an SD with
	 * the full 2M memory but something smaller. By not filling out any
	 * size, the function will शेष the SD size to be 2M.
	 */
	अगर (info->direct_mode_sz == 0)
		sd_size = I40E_HMC_सूचीECT_BP_SIZE;
	अन्यथा
		sd_size = info->direct_mode_sz;

	/* check अगर all the sds are valid. If not, allocate a page and
	 * initialize it.
	 */
	क्रम (j = sd_idx; j < sd_lmt; j++) अणु
		/* update the sd table entry */
		ret_code = i40e_add_sd_table_entry(hw, info->hmc_info, j,
						   info->entry_type,
						   sd_size);
		अगर (ret_code)
			जाओ निकास_sd_error;
		sd_entry = &info->hmc_info->sd_table.sd_entry[j];
		अगर (I40E_SD_TYPE_PAGED == sd_entry->entry_type) अणु
			/* check अगर all the pds in this sd are valid. If not,
			 * allocate a page and initialize it.
			 */

			/* find pd_idx and pd_lmt in this sd */
			pd_idx1 = max(pd_idx, (j * I40E_HMC_MAX_BP_COUNT));
			pd_lmt1 = min(pd_lmt,
				      ((j + 1) * I40E_HMC_MAX_BP_COUNT));
			क्रम (i = pd_idx1; i < pd_lmt1; i++) अणु
				/* update the pd table entry */
				ret_code = i40e_add_pd_table_entry(hw,
								info->hmc_info,
								i, शून्य);
				अगर (ret_code) अणु
					pd_error = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (pd_error) अणु
				/* हटाओ the backing pages from pd_idx1 to i */
				जबतक (i && (i > pd_idx1)) अणु
					i40e_हटाओ_pd_bp(hw, info->hmc_info,
							  (i - 1));
					i--;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!sd_entry->valid) अणु
			sd_entry->valid = true;
			चयन (sd_entry->entry_type) अणु
			हाल I40E_SD_TYPE_PAGED:
				I40E_SET_PF_SD_ENTRY(hw,
					sd_entry->u.pd_table.pd_page_addr.pa,
					j, sd_entry->entry_type);
				अवरोध;
			हाल I40E_SD_TYPE_सूचीECT:
				I40E_SET_PF_SD_ENTRY(hw, sd_entry->u.bp.addr.pa,
						     j, sd_entry->entry_type);
				अवरोध;
			शेष:
				ret_code = I40E_ERR_INVALID_SD_TYPE;
				जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण
	जाओ निकास;

निकास_sd_error:
	/* cleanup क्रम sd entries from j to sd_idx */
	जबतक (j && (j > sd_idx)) अणु
		sd_entry = &info->hmc_info->sd_table.sd_entry[j - 1];
		चयन (sd_entry->entry_type) अणु
		हाल I40E_SD_TYPE_PAGED:
			pd_idx1 = max(pd_idx,
				      ((j - 1) * I40E_HMC_MAX_BP_COUNT));
			pd_lmt1 = min(pd_lmt, (j * I40E_HMC_MAX_BP_COUNT));
			क्रम (i = pd_idx1; i < pd_lmt1; i++)
				i40e_हटाओ_pd_bp(hw, info->hmc_info, i);
			i40e_हटाओ_pd_page(hw, info->hmc_info, (j - 1));
			अवरोध;
		हाल I40E_SD_TYPE_सूचीECT:
			i40e_हटाओ_sd_bp(hw, info->hmc_info, (j - 1));
			अवरोध;
		शेष:
			ret_code = I40E_ERR_INVALID_SD_TYPE;
			अवरोध;
		पूर्ण
		j--;
	पूर्ण
निकास:
	वापस ret_code;
पूर्ण

/**
 * i40e_configure_lan_hmc - prepare the HMC backing store
 * @hw: poपूर्णांकer to the hw काष्ठाure
 * @model: the model क्रम the layout of the SD/PD tables
 *
 * - This function will be called once per physical function initialization.
 * - This function will be called after i40e_init_lan_hmc() and beक्रमe
 *   any LAN/FCoE HMC objects can be created.
 **/
i40e_status i40e_configure_lan_hmc(काष्ठा i40e_hw *hw,
					     क्रमागत i40e_hmc_model model)
अणु
	काष्ठा i40e_hmc_lan_create_obj_info info;
	i40e_status ret_code = 0;
	u8 hmc_fn_id = hw->hmc.hmc_fn_id;
	काष्ठा i40e_hmc_obj_info *obj;

	/* Initialize part of the create object info काष्ठा */
	info.hmc_info = &hw->hmc;
	info.rsrc_type = I40E_HMC_LAN_FULL;
	info.start_idx = 0;
	info.direct_mode_sz = hw->hmc.hmc_obj[I40E_HMC_LAN_FULL].size;

	/* Build the SD entry क्रम the LAN objects */
	चयन (model) अणु
	हाल I40E_HMC_MODEL_सूचीECT_PREFERRED:
	हाल I40E_HMC_MODEL_सूचीECT_ONLY:
		info.entry_type = I40E_SD_TYPE_सूचीECT;
		/* Make one big object, a single SD */
		info.count = 1;
		ret_code = i40e_create_lan_hmc_object(hw, &info);
		अगर (ret_code && (model == I40E_HMC_MODEL_सूचीECT_PREFERRED))
			जाओ try_type_paged;
		अन्यथा अगर (ret_code)
			जाओ configure_lan_hmc_out;
		/* अन्यथा clause falls through the अवरोध */
		अवरोध;
	हाल I40E_HMC_MODEL_PAGED_ONLY:
try_type_paged:
		info.entry_type = I40E_SD_TYPE_PAGED;
		/* Make one big object in the PD table */
		info.count = 1;
		ret_code = i40e_create_lan_hmc_object(hw, &info);
		अगर (ret_code)
			जाओ configure_lan_hmc_out;
		अवरोध;
	शेष:
		/* unsupported type */
		ret_code = I40E_ERR_INVALID_SD_TYPE;
		hw_dbg(hw, "i40e_configure_lan_hmc: Unknown SD type: %d\n",
			  ret_code);
		जाओ configure_lan_hmc_out;
	पूर्ण

	/* Configure and program the FPM रेजिस्टरs so objects can be created */

	/* Tx contexts */
	obj = &hw->hmc.hmc_obj[I40E_HMC_LAN_TX];
	wr32(hw, I40E_GLHMC_LANTXBASE(hmc_fn_id),
	     (u32)((obj->base & I40E_GLHMC_LANTXBASE_FPMLANTXBASE_MASK) / 512));
	wr32(hw, I40E_GLHMC_LANTXCNT(hmc_fn_id), obj->cnt);

	/* Rx contexts */
	obj = &hw->hmc.hmc_obj[I40E_HMC_LAN_RX];
	wr32(hw, I40E_GLHMC_LANRXBASE(hmc_fn_id),
	     (u32)((obj->base & I40E_GLHMC_LANRXBASE_FPMLANRXBASE_MASK) / 512));
	wr32(hw, I40E_GLHMC_LANRXCNT(hmc_fn_id), obj->cnt);

	/* FCoE contexts */
	obj = &hw->hmc.hmc_obj[I40E_HMC_FCOE_CTX];
	wr32(hw, I40E_GLHMC_FCOEDDPBASE(hmc_fn_id),
	 (u32)((obj->base & I40E_GLHMC_FCOEDDPBASE_FPMFCOEDDPBASE_MASK) / 512));
	wr32(hw, I40E_GLHMC_FCOEDDPCNT(hmc_fn_id), obj->cnt);

	/* FCoE filters */
	obj = &hw->hmc.hmc_obj[I40E_HMC_FCOE_FILT];
	wr32(hw, I40E_GLHMC_FCOEFBASE(hmc_fn_id),
	     (u32)((obj->base & I40E_GLHMC_FCOEFBASE_FPMFCOEFBASE_MASK) / 512));
	wr32(hw, I40E_GLHMC_FCOEFCNT(hmc_fn_id), obj->cnt);

configure_lan_hmc_out:
	वापस ret_code;
पूर्ण

/**
 * i40e_delete_lan_hmc_object - हटाओ hmc objects
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @info: poपूर्णांकer to i40e_hmc_delete_obj_info काष्ठा
 *
 * This will de-populate the SDs and PDs.  It मुक्तs
 * the memory क्रम PDS and backing storage.  After this function is वापसed,
 * caller should deallocate memory allocated previously क्रम
 * book-keeping inक्रमmation about PDs and backing storage.
 **/
अटल i40e_status i40e_delete_lan_hmc_object(काष्ठा i40e_hw *hw,
				काष्ठा i40e_hmc_lan_delete_obj_info *info)
अणु
	i40e_status ret_code = 0;
	काष्ठा i40e_hmc_pd_table *pd_table;
	u32 pd_idx, pd_lmt, rel_pd_idx;
	u32 sd_idx, sd_lmt;
	u32 i, j;

	अगर (शून्य == info) अणु
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_delete_hmc_object: bad info ptr\n");
		जाओ निकास;
	पूर्ण
	अगर (शून्य == info->hmc_info) अणु
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_delete_hmc_object: bad info->hmc_info ptr\n");
		जाओ निकास;
	पूर्ण
	अगर (I40E_HMC_INFO_SIGNATURE != info->hmc_info->signature) अणु
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_delete_hmc_object: bad hmc_info->signature\n");
		जाओ निकास;
	पूर्ण

	अगर (शून्य == info->hmc_info->sd_table.sd_entry) अणु
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_delete_hmc_object: bad sd_entry\n");
		जाओ निकास;
	पूर्ण

	अगर (शून्य == info->hmc_info->hmc_obj) अणु
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_delete_hmc_object: bad hmc_info->hmc_obj\n");
		जाओ निकास;
	पूर्ण
	अगर (info->start_idx >= info->hmc_info->hmc_obj[info->rsrc_type].cnt) अणु
		ret_code = I40E_ERR_INVALID_HMC_OBJ_INDEX;
		hw_dbg(hw, "i40e_delete_hmc_object: returns error %d\n",
			  ret_code);
		जाओ निकास;
	पूर्ण

	अगर ((info->start_idx + info->count) >
	    info->hmc_info->hmc_obj[info->rsrc_type].cnt) अणु
		ret_code = I40E_ERR_INVALID_HMC_OBJ_COUNT;
		hw_dbg(hw, "i40e_delete_hmc_object: returns error %d\n",
			  ret_code);
		जाओ निकास;
	पूर्ण

	I40E_FIND_PD_INDEX_LIMIT(info->hmc_info, info->rsrc_type,
				 info->start_idx, info->count, &pd_idx,
				 &pd_lmt);

	क्रम (j = pd_idx; j < pd_lmt; j++) अणु
		sd_idx = j / I40E_HMC_PD_CNT_IN_SD;

		अगर (I40E_SD_TYPE_PAGED !=
		    info->hmc_info->sd_table.sd_entry[sd_idx].entry_type)
			जारी;

		rel_pd_idx = j % I40E_HMC_PD_CNT_IN_SD;

		pd_table =
			&info->hmc_info->sd_table.sd_entry[sd_idx].u.pd_table;
		अगर (pd_table->pd_entry[rel_pd_idx].valid) अणु
			ret_code = i40e_हटाओ_pd_bp(hw, info->hmc_info, j);
			अगर (ret_code)
				जाओ निकास;
		पूर्ण
	पूर्ण

	/* find sd index and limit */
	I40E_FIND_SD_INDEX_LIMIT(info->hmc_info, info->rsrc_type,
				 info->start_idx, info->count,
				 &sd_idx, &sd_lmt);
	अगर (sd_idx >= info->hmc_info->sd_table.sd_cnt ||
	    sd_lmt > info->hmc_info->sd_table.sd_cnt) अणु
		ret_code = I40E_ERR_INVALID_SD_INDEX;
		जाओ निकास;
	पूर्ण

	क्रम (i = sd_idx; i < sd_lmt; i++) अणु
		अगर (!info->hmc_info->sd_table.sd_entry[i].valid)
			जारी;
		चयन (info->hmc_info->sd_table.sd_entry[i].entry_type) अणु
		हाल I40E_SD_TYPE_सूचीECT:
			ret_code = i40e_हटाओ_sd_bp(hw, info->hmc_info, i);
			अगर (ret_code)
				जाओ निकास;
			अवरोध;
		हाल I40E_SD_TYPE_PAGED:
			ret_code = i40e_हटाओ_pd_page(hw, info->hmc_info, i);
			अगर (ret_code)
				जाओ निकास;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
निकास:
	वापस ret_code;
पूर्ण

/**
 * i40e_shutकरोwn_lan_hmc - Remove HMC backing store, मुक्त allocated memory
 * @hw: poपूर्णांकer to the hw काष्ठाure
 *
 * This must be called by drivers as they are shutting करोwn and being
 * हटाओd from the OS.
 **/
i40e_status i40e_shutकरोwn_lan_hmc(काष्ठा i40e_hw *hw)
अणु
	काष्ठा i40e_hmc_lan_delete_obj_info info;
	i40e_status ret_code;

	info.hmc_info = &hw->hmc;
	info.rsrc_type = I40E_HMC_LAN_FULL;
	info.start_idx = 0;
	info.count = 1;

	/* delete the object */
	ret_code = i40e_delete_lan_hmc_object(hw, &info);

	/* मुक्त the SD table entry क्रम LAN */
	i40e_मुक्त_virt_mem(hw, &hw->hmc.sd_table.addr);
	hw->hmc.sd_table.sd_cnt = 0;
	hw->hmc.sd_table.sd_entry = शून्य;

	/* मुक्त memory used क्रम hmc_obj */
	i40e_मुक्त_virt_mem(hw, &hw->hmc.hmc_obj_virt_mem);
	hw->hmc.hmc_obj = शून्य;

	वापस ret_code;
पूर्ण

#घोषणा I40E_HMC_STORE(_काष्ठा, _ele)		\
	दुरत्व(काष्ठा _काष्ठा, _ele),		\
	माप_field(काष्ठा _काष्ठा, _ele)

काष्ठा i40e_context_ele अणु
	u16 offset;
	u16 size_of;
	u16 width;
	u16 lsb;
पूर्ण;

/* LAN Tx Queue Context */
अटल काष्ठा i40e_context_ele i40e_hmc_txq_ce_info[] = अणु
					     /* Field      Width    LSB */
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, head),           13,      0 पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, new_context),     1,     30 पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, base),           57,     32 पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, fc_ena),          1,     89 पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, बारync_ena),    1,     90 पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, fd_ena),          1,     91 पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, alt_vlan_ena),    1,     92 पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, cpuid),           8,     96 पूर्ण,
/* line 1 */
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, thead_wb),       13,  0 + 128 पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, head_wb_ena),     1, 32 + 128 पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, qlen),           13, 33 + 128 पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, tphrdesc_ena),    1, 46 + 128 पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, tphrpacket_ena),  1, 47 + 128 पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, tphwdesc_ena),    1, 48 + 128 पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, head_wb_addr),   64, 64 + 128 पूर्ण,
/* line 7 */
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, crc),            32,  0 + (7 * 128) पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, rdylist),        10, 84 + (7 * 128) पूर्ण,
	अणुI40E_HMC_STORE(i40e_hmc_obj_txq, rdylist_act),     1, 94 + (7 * 128) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

/* LAN Rx Queue Context */
अटल काष्ठा i40e_context_ele i40e_hmc_rxq_ce_info[] = अणु
					 /* Field      Width    LSB */
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, head),        13,	0   पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, cpuid),        8,	13  पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, base),        57,	32  पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, qlen),        13,	89  पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, dbuff),        7,	102 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, hbuff),        5,	109 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, dtype),        2,	114 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, dsize),        1,	116 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, crcstrip),     1,	117 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, fc_ena),       1,	118 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, l2tsel),       1,	119 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, hsplit_0),     4,	120 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, hsplit_1),     2,	124 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, showiv),       1,	127 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, rxmax),       14,	174 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, tphrdesc_ena), 1,	193 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, tphwdesc_ena), 1,	194 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, tphdata_ena),  1,	195 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, tphhead_ena),  1,	196 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, lrxqthresh),   3,	198 पूर्ण,
	अणु I40E_HMC_STORE(i40e_hmc_obj_rxq, prefena),      1,	201 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

/**
 * i40e_ग_लिखो_byte - replace HMC context byte
 * @hmc_bits: poपूर्णांकer to the HMC memory
 * @ce_info: a description of the काष्ठा to be पढ़ो from
 * @src: the काष्ठा to be पढ़ो from
 **/
अटल व्योम i40e_ग_लिखो_byte(u8 *hmc_bits,
			    काष्ठा i40e_context_ele *ce_info,
			    u8 *src)
अणु
	u8 src_byte, dest_byte, mask;
	u8 *from, *dest;
	u16 shअगरt_width;

	/* copy from the next काष्ठा field */
	from = src + ce_info->offset;

	/* prepare the bits and mask */
	shअगरt_width = ce_info->lsb % 8;
	mask = (u8)(BIT(ce_info->width) - 1);

	src_byte = *from;
	src_byte &= mask;

	/* shअगरt to correct alignment */
	mask <<= shअगरt_width;
	src_byte <<= shअगरt_width;

	/* get the current bits from the target bit string */
	dest = hmc_bits + (ce_info->lsb / 8);

	स_नकल(&dest_byte, dest, माप(dest_byte));

	dest_byte &= ~mask;	/* get the bits not changing */
	dest_byte |= src_byte;	/* add in the new bits */

	/* put it all back */
	स_नकल(dest, &dest_byte, माप(dest_byte));
पूर्ण

/**
 * i40e_ग_लिखो_word - replace HMC context word
 * @hmc_bits: poपूर्णांकer to the HMC memory
 * @ce_info: a description of the काष्ठा to be पढ़ो from
 * @src: the काष्ठा to be पढ़ो from
 **/
अटल व्योम i40e_ग_लिखो_word(u8 *hmc_bits,
			    काष्ठा i40e_context_ele *ce_info,
			    u8 *src)
अणु
	u16 src_word, mask;
	u8 *from, *dest;
	u16 shअगरt_width;
	__le16 dest_word;

	/* copy from the next काष्ठा field */
	from = src + ce_info->offset;

	/* prepare the bits and mask */
	shअगरt_width = ce_info->lsb % 8;
	mask = BIT(ce_info->width) - 1;

	/* करोn't swizzle the bits until after the mask because the mask bits
	 * will be in a dअगरferent bit position on big endian machines
	 */
	src_word = *(u16 *)from;
	src_word &= mask;

	/* shअगरt to correct alignment */
	mask <<= shअगरt_width;
	src_word <<= shअगरt_width;

	/* get the current bits from the target bit string */
	dest = hmc_bits + (ce_info->lsb / 8);

	स_नकल(&dest_word, dest, माप(dest_word));

	dest_word &= ~(cpu_to_le16(mask));	/* get the bits not changing */
	dest_word |= cpu_to_le16(src_word);	/* add in the new bits */

	/* put it all back */
	स_नकल(dest, &dest_word, माप(dest_word));
पूर्ण

/**
 * i40e_ग_लिखो_dword - replace HMC context dword
 * @hmc_bits: poपूर्णांकer to the HMC memory
 * @ce_info: a description of the काष्ठा to be पढ़ो from
 * @src: the काष्ठा to be पढ़ो from
 **/
अटल व्योम i40e_ग_लिखो_dword(u8 *hmc_bits,
			     काष्ठा i40e_context_ele *ce_info,
			     u8 *src)
अणु
	u32 src_dword, mask;
	u8 *from, *dest;
	u16 shअगरt_width;
	__le32 dest_dword;

	/* copy from the next काष्ठा field */
	from = src + ce_info->offset;

	/* prepare the bits and mask */
	shअगरt_width = ce_info->lsb % 8;

	/* अगर the field width is exactly 32 on an x86 machine, then the shअगरt
	 * operation will not work because the SHL inकाष्ठाions count is masked
	 * to 5 bits so the shअगरt will करो nothing
	 */
	अगर (ce_info->width < 32)
		mask = BIT(ce_info->width) - 1;
	अन्यथा
		mask = ~(u32)0;

	/* करोn't swizzle the bits until after the mask because the mask bits
	 * will be in a dअगरferent bit position on big endian machines
	 */
	src_dword = *(u32 *)from;
	src_dword &= mask;

	/* shअगरt to correct alignment */
	mask <<= shअगरt_width;
	src_dword <<= shअगरt_width;

	/* get the current bits from the target bit string */
	dest = hmc_bits + (ce_info->lsb / 8);

	स_नकल(&dest_dword, dest, माप(dest_dword));

	dest_dword &= ~(cpu_to_le32(mask));	/* get the bits not changing */
	dest_dword |= cpu_to_le32(src_dword);	/* add in the new bits */

	/* put it all back */
	स_नकल(dest, &dest_dword, माप(dest_dword));
पूर्ण

/**
 * i40e_ग_लिखो_qword - replace HMC context qword
 * @hmc_bits: poपूर्णांकer to the HMC memory
 * @ce_info: a description of the काष्ठा to be पढ़ो from
 * @src: the काष्ठा to be पढ़ो from
 **/
अटल व्योम i40e_ग_लिखो_qword(u8 *hmc_bits,
			     काष्ठा i40e_context_ele *ce_info,
			     u8 *src)
अणु
	u64 src_qword, mask;
	u8 *from, *dest;
	u16 shअगरt_width;
	__le64 dest_qword;

	/* copy from the next काष्ठा field */
	from = src + ce_info->offset;

	/* prepare the bits and mask */
	shअगरt_width = ce_info->lsb % 8;

	/* अगर the field width is exactly 64 on an x86 machine, then the shअगरt
	 * operation will not work because the SHL inकाष्ठाions count is masked
	 * to 6 bits so the shअगरt will करो nothing
	 */
	अगर (ce_info->width < 64)
		mask = BIT_ULL(ce_info->width) - 1;
	अन्यथा
		mask = ~(u64)0;

	/* करोn't swizzle the bits until after the mask because the mask bits
	 * will be in a dअगरferent bit position on big endian machines
	 */
	src_qword = *(u64 *)from;
	src_qword &= mask;

	/* shअगरt to correct alignment */
	mask <<= shअगरt_width;
	src_qword <<= shअगरt_width;

	/* get the current bits from the target bit string */
	dest = hmc_bits + (ce_info->lsb / 8);

	स_नकल(&dest_qword, dest, माप(dest_qword));

	dest_qword &= ~(cpu_to_le64(mask));	/* get the bits not changing */
	dest_qword |= cpu_to_le64(src_qword);	/* add in the new bits */

	/* put it all back */
	स_नकल(dest, &dest_qword, माप(dest_qword));
पूर्ण

/**
 * i40e_clear_hmc_context - zero out the HMC context bits
 * @hw:       the hardware काष्ठा
 * @context_bytes: poपूर्णांकer to the context bit array (DMA memory)
 * @hmc_type: the type of HMC resource
 **/
अटल i40e_status i40e_clear_hmc_context(काष्ठा i40e_hw *hw,
					u8 *context_bytes,
					क्रमागत i40e_hmc_lan_rsrc_type hmc_type)
अणु
	/* clean the bit array */
	स_रखो(context_bytes, 0, (u32)hw->hmc.hmc_obj[hmc_type].size);

	वापस 0;
पूर्ण

/**
 * i40e_set_hmc_context - replace HMC context bits
 * @context_bytes: poपूर्णांकer to the context bit array
 * @ce_info:  a description of the काष्ठा to be filled
 * @dest:     the काष्ठा to be filled
 **/
अटल i40e_status i40e_set_hmc_context(u8 *context_bytes,
					काष्ठा i40e_context_ele *ce_info,
					u8 *dest)
अणु
	पूर्णांक f;

	क्रम (f = 0; ce_info[f].width != 0; f++) अणु

		/* we have to deal with each element of the HMC using the
		 * correct size so that we are correct regardless of the
		 * endianness of the machine
		 */
		चयन (ce_info[f].size_of) अणु
		हाल 1:
			i40e_ग_लिखो_byte(context_bytes, &ce_info[f], dest);
			अवरोध;
		हाल 2:
			i40e_ग_लिखो_word(context_bytes, &ce_info[f], dest);
			अवरोध;
		हाल 4:
			i40e_ग_लिखो_dword(context_bytes, &ce_info[f], dest);
			अवरोध;
		हाल 8:
			i40e_ग_लिखो_qword(context_bytes, &ce_info[f], dest);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_hmc_get_object_va - retrieves an object's भव address
 * @hw: the hardware काष्ठा, from which we obtain the i40e_hmc_info poपूर्णांकer
 * @object_base: poपूर्णांकer to u64 to get the va
 * @rsrc_type: the hmc resource type
 * @obj_idx: hmc object index
 *
 * This function retrieves the object's भव address from the object
 * base poपूर्णांकer.  This function is used क्रम LAN Queue contexts.
 **/
अटल
i40e_status i40e_hmc_get_object_va(काष्ठा i40e_hw *hw, u8 **object_base,
				   क्रमागत i40e_hmc_lan_rsrc_type rsrc_type,
				   u32 obj_idx)
अणु
	काष्ठा i40e_hmc_info *hmc_info = &hw->hmc;
	u32 obj_offset_in_sd, obj_offset_in_pd;
	काष्ठा i40e_hmc_sd_entry *sd_entry;
	काष्ठा i40e_hmc_pd_entry *pd_entry;
	u32 pd_idx, pd_lmt, rel_pd_idx;
	i40e_status ret_code = 0;
	u64 obj_offset_in_fpm;
	u32 sd_idx, sd_lmt;

	अगर (शून्य == hmc_info) अणु
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_hmc_get_object_va: bad hmc_info ptr\n");
		जाओ निकास;
	पूर्ण
	अगर (शून्य == hmc_info->hmc_obj) अणु
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_hmc_get_object_va: bad hmc_info->hmc_obj ptr\n");
		जाओ निकास;
	पूर्ण
	अगर (शून्य == object_base) अणु
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_hmc_get_object_va: bad object_base ptr\n");
		जाओ निकास;
	पूर्ण
	अगर (I40E_HMC_INFO_SIGNATURE != hmc_info->signature) अणु
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_hmc_get_object_va: bad hmc_info->signature\n");
		जाओ निकास;
	पूर्ण
	अगर (obj_idx >= hmc_info->hmc_obj[rsrc_type].cnt) अणु
		hw_dbg(hw, "i40e_hmc_get_object_va: returns error %d\n",
			  ret_code);
		ret_code = I40E_ERR_INVALID_HMC_OBJ_INDEX;
		जाओ निकास;
	पूर्ण
	/* find sd index and limit */
	I40E_FIND_SD_INDEX_LIMIT(hmc_info, rsrc_type, obj_idx, 1,
				 &sd_idx, &sd_lmt);

	sd_entry = &hmc_info->sd_table.sd_entry[sd_idx];
	obj_offset_in_fpm = hmc_info->hmc_obj[rsrc_type].base +
			    hmc_info->hmc_obj[rsrc_type].size * obj_idx;

	अगर (I40E_SD_TYPE_PAGED == sd_entry->entry_type) अणु
		I40E_FIND_PD_INDEX_LIMIT(hmc_info, rsrc_type, obj_idx, 1,
					 &pd_idx, &pd_lmt);
		rel_pd_idx = pd_idx % I40E_HMC_PD_CNT_IN_SD;
		pd_entry = &sd_entry->u.pd_table.pd_entry[rel_pd_idx];
		obj_offset_in_pd = (u32)(obj_offset_in_fpm %
					 I40E_HMC_PAGED_BP_SIZE);
		*object_base = (u8 *)pd_entry->bp.addr.va + obj_offset_in_pd;
	पूर्ण अन्यथा अणु
		obj_offset_in_sd = (u32)(obj_offset_in_fpm %
					 I40E_HMC_सूचीECT_BP_SIZE);
		*object_base = (u8 *)sd_entry->u.bp.addr.va + obj_offset_in_sd;
	पूर्ण
निकास:
	वापस ret_code;
पूर्ण

/**
 * i40e_clear_lan_tx_queue_context - clear the HMC context क्रम the queue
 * @hw:    the hardware काष्ठा
 * @queue: the queue we care about
 **/
i40e_status i40e_clear_lan_tx_queue_context(काष्ठा i40e_hw *hw,
						      u16 queue)
अणु
	i40e_status err;
	u8 *context_bytes;

	err = i40e_hmc_get_object_va(hw, &context_bytes,
				     I40E_HMC_LAN_TX, queue);
	अगर (err < 0)
		वापस err;

	वापस i40e_clear_hmc_context(hw, context_bytes, I40E_HMC_LAN_TX);
पूर्ण

/**
 * i40e_set_lan_tx_queue_context - set the HMC context क्रम the queue
 * @hw:    the hardware काष्ठा
 * @queue: the queue we care about
 * @s:     the काष्ठा to be filled
 **/
i40e_status i40e_set_lan_tx_queue_context(काष्ठा i40e_hw *hw,
						    u16 queue,
						    काष्ठा i40e_hmc_obj_txq *s)
अणु
	i40e_status err;
	u8 *context_bytes;

	err = i40e_hmc_get_object_va(hw, &context_bytes,
				     I40E_HMC_LAN_TX, queue);
	अगर (err < 0)
		वापस err;

	वापस i40e_set_hmc_context(context_bytes,
				    i40e_hmc_txq_ce_info, (u8 *)s);
पूर्ण

/**
 * i40e_clear_lan_rx_queue_context - clear the HMC context क्रम the queue
 * @hw:    the hardware काष्ठा
 * @queue: the queue we care about
 **/
i40e_status i40e_clear_lan_rx_queue_context(काष्ठा i40e_hw *hw,
						      u16 queue)
अणु
	i40e_status err;
	u8 *context_bytes;

	err = i40e_hmc_get_object_va(hw, &context_bytes,
				     I40E_HMC_LAN_RX, queue);
	अगर (err < 0)
		वापस err;

	वापस i40e_clear_hmc_context(hw, context_bytes, I40E_HMC_LAN_RX);
पूर्ण

/**
 * i40e_set_lan_rx_queue_context - set the HMC context क्रम the queue
 * @hw:    the hardware काष्ठा
 * @queue: the queue we care about
 * @s:     the काष्ठा to be filled
 **/
i40e_status i40e_set_lan_rx_queue_context(काष्ठा i40e_hw *hw,
						    u16 queue,
						    काष्ठा i40e_hmc_obj_rxq *s)
अणु
	i40e_status err;
	u8 *context_bytes;

	err = i40e_hmc_get_object_va(hw, &context_bytes,
				     I40E_HMC_LAN_RX, queue);
	अगर (err < 0)
		वापस err;

	वापस i40e_set_hmc_context(context_bytes,
				    i40e_hmc_rxq_ce_info, (u8 *)s);
पूर्ण
