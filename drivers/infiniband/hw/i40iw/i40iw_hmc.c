<शैली गुरु>
/*******************************************************************************
*
* Copyright (c) 2015-2016 Intel Corporation.  All rights reserved.
*
* This software is available to you under a choice of one of two
* licenses.  You may choose to be licensed under the terms of the GNU
* General Public License (GPL) Version 2, available from the file
* COPYING in the मुख्य directory of this source tree, or the
* OpenFabrics.org BSD license below:
*
*   Redistribution and use in source and binary क्रमms, with or
*   without modअगरication, are permitted provided that the following
*   conditions are met:
*
*    - Redistributions of source code must retain the above
*	copyright notice, this list of conditions and the following
*	disclaimer.
*
*    - Redistributions in binary क्रमm must reproduce the above
*	copyright notice, this list of conditions and the following
*	disclaimer in the करोcumentation and/or other materials
*	provided with the distribution.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*******************************************************************************/

#समावेश "i40iw_osdep.h"
#समावेश "i40iw_register.h"
#समावेश "i40iw_status.h"
#समावेश "i40iw_hmc.h"
#समावेश "i40iw_d.h"
#समावेश "i40iw_type.h"
#समावेश "i40iw_p.h"
#समावेश "i40iw_vf.h"
#समावेश "i40iw_virtchnl.h"

/**
 * i40iw_find_sd_index_limit - finds segment descriptor index limit
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठाure
 * @type: type of HMC resources we're searching
 * @idx: starting index क्रम the object
 * @cnt: number of objects we're trying to create
 * @sd_idx: poपूर्णांकer to वापस index of the segment descriptor in question
 * @sd_limit: poपूर्णांकer to वापस the maximum number of segment descriptors
 *
 * This function calculates the segment descriptor index and index limit
 * क्रम the resource defined by i40iw_hmc_rsrc_type.
 */

अटल अंतरभूत व्योम i40iw_find_sd_index_limit(काष्ठा i40iw_hmc_info *hmc_info,
					     u32 type,
					     u32 idx,
					     u32 cnt,
					     u32 *sd_idx,
					     u32 *sd_limit)
अणु
	u64 fpm_addr, fpm_limit;

	fpm_addr = hmc_info->hmc_obj[(type)].base +
			hmc_info->hmc_obj[type].size * idx;
	fpm_limit = fpm_addr + hmc_info->hmc_obj[type].size * cnt;
	*sd_idx = (u32)(fpm_addr / I40IW_HMC_सूचीECT_BP_SIZE);
	*sd_limit = (u32)((fpm_limit - 1) / I40IW_HMC_सूचीECT_BP_SIZE);
	*sd_limit += 1;
पूर्ण

/**
 * i40iw_find_pd_index_limit - finds page descriptor index limit
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठा
 * @type: HMC resource type we're examining
 * @idx: starting index क्रम the object
 * @cnt: number of objects we're trying to create
 * @pd_idx: poपूर्णांकer to वापस page descriptor index
 * @pd_limit: poपूर्णांकer to वापस page descriptor index limit
 *
 * Calculates the page descriptor index and index limit क्रम the resource
 * defined by i40iw_hmc_rsrc_type.
 */

अटल अंतरभूत व्योम i40iw_find_pd_index_limit(काष्ठा i40iw_hmc_info *hmc_info,
					     u32 type,
					     u32 idx,
					     u32 cnt,
					     u32 *pd_idx,
					     u32 *pd_limit)
अणु
	u64 fpm_adr, fpm_limit;

	fpm_adr = hmc_info->hmc_obj[type].base +
			hmc_info->hmc_obj[type].size * idx;
	fpm_limit = fpm_adr + (hmc_info)->hmc_obj[(type)].size * (cnt);
	*(pd_idx) = (u32)(fpm_adr / I40IW_HMC_PAGED_BP_SIZE);
	*(pd_limit) = (u32)((fpm_limit - 1) / I40IW_HMC_PAGED_BP_SIZE);
	*(pd_limit) += 1;
पूर्ण

/**
 * i40iw_set_sd_entry - setup entry क्रम sd programming
 * @pa: physical addr
 * @idx: sd index
 * @type: paged or direct sd
 * @entry: sd entry ptr
 */
अटल अंतरभूत व्योम i40iw_set_sd_entry(u64 pa,
				      u32 idx,
				      क्रमागत i40iw_sd_entry_type type,
				      काष्ठा update_sd_entry *entry)
अणु
	entry->data = pa | (I40IW_HMC_MAX_BP_COUNT << I40E_PFHMC_SDDATALOW_PMSDBPCOUNT_SHIFT) |
			(((type == I40IW_SD_TYPE_PAGED) ? 0 : 1) <<
				I40E_PFHMC_SDDATALOW_PMSDTYPE_SHIFT) |
			(1 << I40E_PFHMC_SDDATALOW_PMSDVALID_SHIFT);
	entry->cmd = (idx | (1 << I40E_PFHMC_SDCMD_PMSDWR_SHIFT) | (1 << 15));
पूर्ण

/**
 * i40iw_clr_sd_entry - setup entry क्रम sd clear
 * @idx: sd index
 * @type: paged or direct sd
 * @entry: sd entry ptr
 */
अटल अंतरभूत व्योम i40iw_clr_sd_entry(u32 idx, क्रमागत i40iw_sd_entry_type type,
				      काष्ठा update_sd_entry *entry)
अणु
	entry->data = (I40IW_HMC_MAX_BP_COUNT <<
			I40E_PFHMC_SDDATALOW_PMSDBPCOUNT_SHIFT) |
			(((type == I40IW_SD_TYPE_PAGED) ? 0 : 1) <<
				I40E_PFHMC_SDDATALOW_PMSDTYPE_SHIFT);
	entry->cmd = (idx | (1 << I40E_PFHMC_SDCMD_PMSDWR_SHIFT) | (1 << 15));
पूर्ण

/**
 * i40iw_hmc_sd_one - setup 1 sd entry क्रम cqp
 * @dev: poपूर्णांकer to the device काष्ठाure
 * @hmc_fn_id: hmc's function id
 * @pa: physical addr
 * @sd_idx: sd index
 * @type: paged or direct sd
 * @setsd: flag to set or clear sd
 */
क्रमागत i40iw_status_code i40iw_hmc_sd_one(काष्ठा i40iw_sc_dev *dev,
					u8 hmc_fn_id,
					u64 pa, u32 sd_idx,
					क्रमागत i40iw_sd_entry_type type,
					bool setsd)
अणु
	काष्ठा i40iw_update_sds_info sdinfo;

	sdinfo.cnt = 1;
	sdinfo.hmc_fn_id = hmc_fn_id;
	अगर (setsd)
		i40iw_set_sd_entry(pa, sd_idx, type, sdinfo.entry);
	अन्यथा
		i40iw_clr_sd_entry(sd_idx, type, sdinfo.entry);

	वापस dev->cqp->process_cqp_sds(dev, &sdinfo);
पूर्ण

/**
 * i40iw_hmc_sd_grp - setup group od sd entries क्रम cqp
 * @dev: poपूर्णांकer to the device काष्ठाure
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठा
 * @sd_index: sd index
 * @sd_cnt: number of sd entries
 * @setsd: flag to set or clear sd
 */
अटल क्रमागत i40iw_status_code i40iw_hmc_sd_grp(काष्ठा i40iw_sc_dev *dev,
					       काष्ठा i40iw_hmc_info *hmc_info,
					       u32 sd_index,
					       u32 sd_cnt,
					       bool setsd)
अणु
	काष्ठा i40iw_hmc_sd_entry *sd_entry;
	काष्ठा i40iw_update_sds_info sdinfo;
	u64 pa;
	u32 i;
	क्रमागत i40iw_status_code ret_code = 0;

	स_रखो(&sdinfo, 0, माप(sdinfo));
	sdinfo.hmc_fn_id = hmc_info->hmc_fn_id;
	क्रम (i = sd_index; i < sd_index + sd_cnt; i++) अणु
		sd_entry = &hmc_info->sd_table.sd_entry[i];
		अगर (!sd_entry ||
		    (!sd_entry->valid && setsd) ||
		    (sd_entry->valid && !setsd))
			जारी;
		अगर (setsd) अणु
			pa = (sd_entry->entry_type == I40IW_SD_TYPE_PAGED) ?
			    sd_entry->u.pd_table.pd_page_addr.pa :
			    sd_entry->u.bp.addr.pa;
			i40iw_set_sd_entry(pa, i, sd_entry->entry_type,
					   &sdinfo.entry[sdinfo.cnt]);
		पूर्ण अन्यथा अणु
			i40iw_clr_sd_entry(i, sd_entry->entry_type,
					   &sdinfo.entry[sdinfo.cnt]);
		पूर्ण
		sdinfo.cnt++;
		अगर (sdinfo.cnt == I40IW_MAX_SD_ENTRIES) अणु
			ret_code = dev->cqp->process_cqp_sds(dev, &sdinfo);
			अगर (ret_code) अणु
				i40iw_debug(dev, I40IW_DEBUG_HMC,
					    "i40iw_hmc_sd_grp: sd_programming failed err=%d\n",
					    ret_code);
				वापस ret_code;
			पूर्ण
			sdinfo.cnt = 0;
		पूर्ण
	पूर्ण
	अगर (sdinfo.cnt)
		ret_code = dev->cqp->process_cqp_sds(dev, &sdinfo);

	वापस ret_code;
पूर्ण

/**
 * i40iw_vfdev_from_fpm - वापस vf dev ptr क्रम hmc function id
 * @dev: poपूर्णांकer to the device काष्ठाure
 * @hmc_fn_id: hmc's function id
 */
काष्ठा i40iw_vfdev *i40iw_vfdev_from_fpm(काष्ठा i40iw_sc_dev *dev, u8 hmc_fn_id)
अणु
	काष्ठा i40iw_vfdev *vf_dev = शून्य;
	u16 idx;

	क्रम (idx = 0; idx < I40IW_MAX_PE_ENABLED_VF_COUNT; idx++) अणु
		अगर (dev->vf_dev[idx] &&
		    ((u8)dev->vf_dev[idx]->pmf_index == hmc_fn_id)) अणु
			vf_dev = dev->vf_dev[idx];
			अवरोध;
		पूर्ण
	पूर्ण
	वापस vf_dev;
पूर्ण

/**
 * i40iw_vf_hmcinfo_from_fpm - get ptr to hmc क्रम func_id
 * @dev: poपूर्णांकer to the device काष्ठाure
 * @hmc_fn_id: hmc's function id
 */
काष्ठा i40iw_hmc_info *i40iw_vf_hmcinfo_from_fpm(काष्ठा i40iw_sc_dev *dev,
						 u8 hmc_fn_id)
अणु
	काष्ठा i40iw_hmc_info *hmc_info = शून्य;
	u16 idx;

	क्रम (idx = 0; idx < I40IW_MAX_PE_ENABLED_VF_COUNT; idx++) अणु
		अगर (dev->vf_dev[idx] &&
		    ((u8)dev->vf_dev[idx]->pmf_index == hmc_fn_id)) अणु
			hmc_info = &dev->vf_dev[idx]->hmc_info;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस hmc_info;
पूर्ण

/**
 * i40iw_hmc_finish_add_sd_reg - program sd entries क्रम objects
 * @dev: poपूर्णांकer to the device काष्ठाure
 * @info: create obj info
 */
अटल क्रमागत i40iw_status_code i40iw_hmc_finish_add_sd_reg(काष्ठा i40iw_sc_dev *dev,
							  काष्ठा i40iw_hmc_create_obj_info *info)
अणु
	अगर (info->start_idx >= info->hmc_info->hmc_obj[info->rsrc_type].cnt)
		वापस I40IW_ERR_INVALID_HMC_OBJ_INDEX;

	अगर ((info->start_idx + info->count) >
			info->hmc_info->hmc_obj[info->rsrc_type].cnt)
		वापस I40IW_ERR_INVALID_HMC_OBJ_COUNT;

	अगर (!info->add_sd_cnt)
		वापस 0;

	वापस i40iw_hmc_sd_grp(dev, info->hmc_info,
				info->hmc_info->sd_indexes[0],
				info->add_sd_cnt, true);
पूर्ण

/**
 * i40iw_sc_create_hmc_obj - allocate backing store क्रम hmc objects
 * @dev: poपूर्णांकer to the device काष्ठाure
 * @info: poपूर्णांकer to i40iw_hmc_iw_create_obj_info काष्ठा
 *
 * This will allocate memory क्रम PDs and backing pages and populate
 * the sd and pd entries.
 */
क्रमागत i40iw_status_code i40iw_sc_create_hmc_obj(काष्ठा i40iw_sc_dev *dev,
					       काष्ठा i40iw_hmc_create_obj_info *info)
अणु
	काष्ठा i40iw_hmc_sd_entry *sd_entry;
	u32 sd_idx, sd_lmt;
	u32 pd_idx = 0, pd_lmt = 0;
	u32 pd_idx1 = 0, pd_lmt1 = 0;
	u32 i, j;
	bool pd_error = false;
	क्रमागत i40iw_status_code ret_code = 0;

	अगर (info->start_idx >= info->hmc_info->hmc_obj[info->rsrc_type].cnt)
		वापस I40IW_ERR_INVALID_HMC_OBJ_INDEX;

	अगर ((info->start_idx + info->count) >
	    info->hmc_info->hmc_obj[info->rsrc_type].cnt) अणु
		i40iw_debug(dev, I40IW_DEBUG_HMC,
			    "%s: error type %u, start = %u, req cnt %u, cnt = %u\n",
			    __func__, info->rsrc_type, info->start_idx, info->count,
			    info->hmc_info->hmc_obj[info->rsrc_type].cnt);
		वापस I40IW_ERR_INVALID_HMC_OBJ_COUNT;
	पूर्ण

	अगर (!dev->is_pf)
		वापस i40iw_vchnl_vf_add_hmc_objs(dev, info->rsrc_type, 0, info->count);

	i40iw_find_sd_index_limit(info->hmc_info, info->rsrc_type,
				  info->start_idx, info->count,
				  &sd_idx, &sd_lmt);
	अगर (sd_idx >= info->hmc_info->sd_table.sd_cnt ||
	    sd_lmt > info->hmc_info->sd_table.sd_cnt) अणु
		वापस I40IW_ERR_INVALID_SD_INDEX;
	पूर्ण
	i40iw_find_pd_index_limit(info->hmc_info, info->rsrc_type,
				  info->start_idx, info->count, &pd_idx, &pd_lmt);

	क्रम (j = sd_idx; j < sd_lmt; j++) अणु
		ret_code = i40iw_add_sd_table_entry(dev->hw, info->hmc_info,
						    j,
						    info->entry_type,
						    I40IW_HMC_सूचीECT_BP_SIZE);
		अगर (ret_code)
			जाओ निकास_sd_error;
		sd_entry = &info->hmc_info->sd_table.sd_entry[j];

		अगर ((sd_entry->entry_type == I40IW_SD_TYPE_PAGED) &&
		    ((dev->hmc_info == info->hmc_info) &&
		     (info->rsrc_type != I40IW_HMC_IW_PBLE))) अणु
			pd_idx1 = max(pd_idx, (j * I40IW_HMC_MAX_BP_COUNT));
			pd_lmt1 = min(pd_lmt,
				      (j + 1) * I40IW_HMC_MAX_BP_COUNT);
			क्रम (i = pd_idx1; i < pd_lmt1; i++) अणु
				/* update the pd table entry */
				ret_code = i40iw_add_pd_table_entry(dev->hw, info->hmc_info,
								    i, शून्य);
				अगर (ret_code) अणु
					pd_error = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (pd_error) अणु
				जबतक (i && (i > pd_idx1)) अणु
					i40iw_हटाओ_pd_bp(dev->hw, info->hmc_info, (i - 1),
							   info->is_pf);
					i--;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (sd_entry->valid)
			जारी;

		info->hmc_info->sd_indexes[info->add_sd_cnt] = (u16)j;
		info->add_sd_cnt++;
		sd_entry->valid = true;
	पूर्ण
	वापस i40iw_hmc_finish_add_sd_reg(dev, info);

निकास_sd_error:
	जबतक (j && (j > sd_idx)) अणु
		sd_entry = &info->hmc_info->sd_table.sd_entry[j - 1];
		चयन (sd_entry->entry_type) अणु
		हाल I40IW_SD_TYPE_PAGED:
			pd_idx1 = max(pd_idx,
				      (j - 1) * I40IW_HMC_MAX_BP_COUNT);
			pd_lmt1 = min(pd_lmt, (j * I40IW_HMC_MAX_BP_COUNT));
			क्रम (i = pd_idx1; i < pd_lmt1; i++)
				i40iw_prep_हटाओ_pd_page(info->hmc_info, i);
			अवरोध;
		हाल I40IW_SD_TYPE_सूचीECT:
			i40iw_prep_हटाओ_pd_page(info->hmc_info, (j - 1));
			अवरोध;
		शेष:
			ret_code = I40IW_ERR_INVALID_SD_TYPE;
			अवरोध;
		पूर्ण
		j--;
	पूर्ण

	वापस ret_code;
पूर्ण

/**
 * i40iw_finish_del_sd_reg - delete sd entries क्रम objects
 * @dev: poपूर्णांकer to the device काष्ठाure
 * @info: dele obj info
 * @reset: true अगर called beक्रमe reset
 */
अटल क्रमागत i40iw_status_code i40iw_finish_del_sd_reg(काष्ठा i40iw_sc_dev *dev,
						      काष्ठा i40iw_hmc_del_obj_info *info,
						      bool reset)
अणु
	काष्ठा i40iw_hmc_sd_entry *sd_entry;
	क्रमागत i40iw_status_code ret_code = 0;
	u32 i, sd_idx;
	काष्ठा i40iw_dma_mem *mem;

	अगर (dev->is_pf && !reset)
		ret_code = i40iw_hmc_sd_grp(dev, info->hmc_info,
					    info->hmc_info->sd_indexes[0],
					    info->del_sd_cnt, false);

	अगर (ret_code)
		i40iw_debug(dev, I40IW_DEBUG_HMC, "%s: error cqp sd sd_grp\n", __func__);

	क्रम (i = 0; i < info->del_sd_cnt; i++) अणु
		sd_idx = info->hmc_info->sd_indexes[i];
		sd_entry = &info->hmc_info->sd_table.sd_entry[sd_idx];
		अगर (!sd_entry)
			जारी;
		mem = (sd_entry->entry_type == I40IW_SD_TYPE_PAGED) ?
			&sd_entry->u.pd_table.pd_page_addr :
			&sd_entry->u.bp.addr;

		अगर (!mem || !mem->va)
			i40iw_debug(dev, I40IW_DEBUG_HMC, "%s: error cqp sd mem\n", __func__);
		अन्यथा
			i40iw_मुक्त_dma_mem(dev->hw, mem);
	पूर्ण
	वापस ret_code;
पूर्ण

/**
 * i40iw_sc_del_hmc_obj - हटाओ pe hmc objects
 * @dev: poपूर्णांकer to the device काष्ठाure
 * @info: poपूर्णांकer to i40iw_hmc_del_obj_info काष्ठा
 * @reset: true अगर called beक्रमe reset
 *
 * This will de-populate the SDs and PDs.  It मुक्तs
 * the memory क्रम PDS and backing storage.  After this function is वापसed,
 * caller should deallocate memory allocated previously क्रम
 * book-keeping inक्रमmation about PDs and backing storage.
 */
क्रमागत i40iw_status_code i40iw_sc_del_hmc_obj(काष्ठा i40iw_sc_dev *dev,
					    काष्ठा i40iw_hmc_del_obj_info *info,
					    bool reset)
अणु
	काष्ठा i40iw_hmc_pd_table *pd_table;
	u32 sd_idx, sd_lmt;
	u32 pd_idx, pd_lmt, rel_pd_idx;
	u32 i, j;
	क्रमागत i40iw_status_code ret_code = 0;

	अगर (info->start_idx >= info->hmc_info->hmc_obj[info->rsrc_type].cnt) अणु
		i40iw_debug(dev, I40IW_DEBUG_HMC,
			    "%s: error start_idx[%04d]  >= [type %04d].cnt[%04d]\n",
			    __func__, info->start_idx, info->rsrc_type,
			    info->hmc_info->hmc_obj[info->rsrc_type].cnt);
		वापस I40IW_ERR_INVALID_HMC_OBJ_INDEX;
	पूर्ण

	अगर ((info->start_idx + info->count) >
	    info->hmc_info->hmc_obj[info->rsrc_type].cnt) अणु
		i40iw_debug(dev, I40IW_DEBUG_HMC,
			    "%s: error start_idx[%04d] + count %04d  >= [type %04d].cnt[%04d]\n",
			    __func__, info->start_idx, info->count,
			    info->rsrc_type,
			    info->hmc_info->hmc_obj[info->rsrc_type].cnt);
		वापस I40IW_ERR_INVALID_HMC_OBJ_COUNT;
	पूर्ण
	अगर (!dev->is_pf) अणु
		ret_code = i40iw_vchnl_vf_del_hmc_obj(dev, info->rsrc_type, 0,
						      info->count);
		अगर (info->rsrc_type != I40IW_HMC_IW_PBLE)
			वापस ret_code;
	पूर्ण

	i40iw_find_pd_index_limit(info->hmc_info, info->rsrc_type,
				  info->start_idx, info->count, &pd_idx, &pd_lmt);

	क्रम (j = pd_idx; j < pd_lmt; j++) अणु
		sd_idx = j / I40IW_HMC_PD_CNT_IN_SD;

		अगर (info->hmc_info->sd_table.sd_entry[sd_idx].entry_type !=
		    I40IW_SD_TYPE_PAGED)
			जारी;

		rel_pd_idx = j % I40IW_HMC_PD_CNT_IN_SD;
		pd_table = &info->hmc_info->sd_table.sd_entry[sd_idx].u.pd_table;
		अगर (pd_table->pd_entry[rel_pd_idx].valid) अणु
			ret_code = i40iw_हटाओ_pd_bp(dev->hw, info->hmc_info, j,
						      info->is_pf);
			अगर (ret_code) अणु
				i40iw_debug(dev, I40IW_DEBUG_HMC, "%s: error\n", __func__);
				वापस ret_code;
			पूर्ण
		पूर्ण
	पूर्ण

	i40iw_find_sd_index_limit(info->hmc_info, info->rsrc_type,
				  info->start_idx, info->count, &sd_idx, &sd_lmt);
	अगर (sd_idx >= info->hmc_info->sd_table.sd_cnt ||
	    sd_lmt > info->hmc_info->sd_table.sd_cnt) अणु
		i40iw_debug(dev, I40IW_DEBUG_HMC, "%s: error invalid sd_idx\n", __func__);
		वापस I40IW_ERR_INVALID_SD_INDEX;
	पूर्ण

	क्रम (i = sd_idx; i < sd_lmt; i++) अणु
		अगर (!info->hmc_info->sd_table.sd_entry[i].valid)
			जारी;
		चयन (info->hmc_info->sd_table.sd_entry[i].entry_type) अणु
		हाल I40IW_SD_TYPE_सूचीECT:
			ret_code = i40iw_prep_हटाओ_sd_bp(info->hmc_info, i);
			अगर (!ret_code) अणु
				info->hmc_info->sd_indexes[info->del_sd_cnt] = (u16)i;
				info->del_sd_cnt++;
			पूर्ण
			अवरोध;
		हाल I40IW_SD_TYPE_PAGED:
			ret_code = i40iw_prep_हटाओ_pd_page(info->hmc_info, i);
			अगर (!ret_code) अणु
				info->hmc_info->sd_indexes[info->del_sd_cnt] = (u16)i;
				info->del_sd_cnt++;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस i40iw_finish_del_sd_reg(dev, info, reset);
पूर्ण

/**
 * i40iw_add_sd_table_entry - Adds a segment descriptor to the table
 * @hw: poपूर्णांकer to our hw काष्ठा
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठा
 * @sd_index: segment descriptor index to manipulate
 * @type: what type of segment descriptor we're manipulating
 * @direct_mode_sz: size to alloc in direct mode
 */
क्रमागत i40iw_status_code i40iw_add_sd_table_entry(काष्ठा i40iw_hw *hw,
						काष्ठा i40iw_hmc_info *hmc_info,
						u32 sd_index,
						क्रमागत i40iw_sd_entry_type type,
						u64 direct_mode_sz)
अणु
	क्रमागत i40iw_status_code ret_code = 0;
	काष्ठा i40iw_hmc_sd_entry *sd_entry;
	bool dma_mem_alloc_करोne = false;
	काष्ठा i40iw_dma_mem mem;
	u64 alloc_len;

	sd_entry = &hmc_info->sd_table.sd_entry[sd_index];
	अगर (!sd_entry->valid) अणु
		अगर (type == I40IW_SD_TYPE_PAGED)
			alloc_len = I40IW_HMC_PAGED_BP_SIZE;
		अन्यथा
			alloc_len = direct_mode_sz;

		/* allocate a 4K pd page or 2M backing page */
		ret_code = i40iw_allocate_dma_mem(hw, &mem, alloc_len,
						  I40IW_HMC_PD_BP_BUF_ALIGNMENT);
		अगर (ret_code)
			जाओ निकास;
		dma_mem_alloc_करोne = true;
		अगर (type == I40IW_SD_TYPE_PAGED) अणु
			ret_code = i40iw_allocate_virt_mem(hw,
							   &sd_entry->u.pd_table.pd_entry_virt_mem,
							   माप(काष्ठा i40iw_hmc_pd_entry) * 512);
			अगर (ret_code)
				जाओ निकास;
			sd_entry->u.pd_table.pd_entry = (काष्ठा i40iw_hmc_pd_entry *)
							 sd_entry->u.pd_table.pd_entry_virt_mem.va;

			स_नकल(&sd_entry->u.pd_table.pd_page_addr, &mem, माप(काष्ठा i40iw_dma_mem));
		पूर्ण अन्यथा अणु
			स_नकल(&sd_entry->u.bp.addr, &mem, माप(काष्ठा i40iw_dma_mem));
			sd_entry->u.bp.sd_pd_index = sd_index;
		पूर्ण

		hmc_info->sd_table.sd_entry[sd_index].entry_type = type;

		I40IW_INC_SD_REFCNT(&hmc_info->sd_table);
	पूर्ण
	अगर (sd_entry->entry_type == I40IW_SD_TYPE_सूचीECT)
		I40IW_INC_BP_REFCNT(&sd_entry->u.bp);
निकास:
	अगर (ret_code)
		अगर (dma_mem_alloc_करोne)
			i40iw_मुक्त_dma_mem(hw, &mem);

	वापस ret_code;
पूर्ण

/**
 * i40iw_add_pd_table_entry - Adds page descriptor to the specअगरied table
 * @hw: poपूर्णांकer to our HW काष्ठाure
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठाure
 * @pd_index: which page descriptor index to manipulate
 * @rsrc_pg: अगर not शून्य, use pपुनः_स्मृतिated page instead of allocating new one.
 *
 * This function:
 *	1. Initializes the pd entry
 *	2. Adds pd_entry in the pd_table
 *	3. Mark the entry valid in i40iw_hmc_pd_entry काष्ठाure
 *	4. Initializes the pd_entry's ref count to 1
 * assumptions:
 *	1. The memory क्रम pd should be pinned करोwn, physically contiguous and
 *	   aligned on 4K boundary and zeroed memory.
 *	2. It should be 4K in size.
 */
क्रमागत i40iw_status_code i40iw_add_pd_table_entry(काष्ठा i40iw_hw *hw,
						काष्ठा i40iw_hmc_info *hmc_info,
						u32 pd_index,
						काष्ठा i40iw_dma_mem *rsrc_pg)
अणु
	क्रमागत i40iw_status_code ret_code = 0;
	काष्ठा i40iw_hmc_pd_table *pd_table;
	काष्ठा i40iw_hmc_pd_entry *pd_entry;
	काष्ठा i40iw_dma_mem mem;
	काष्ठा i40iw_dma_mem *page = &mem;
	u32 sd_idx, rel_pd_idx;
	u64 *pd_addr;
	u64 page_desc;

	अगर (pd_index / I40IW_HMC_PD_CNT_IN_SD >= hmc_info->sd_table.sd_cnt)
		वापस I40IW_ERR_INVALID_PAGE_DESC_INDEX;

	sd_idx = (pd_index / I40IW_HMC_PD_CNT_IN_SD);
	अगर (hmc_info->sd_table.sd_entry[sd_idx].entry_type != I40IW_SD_TYPE_PAGED)
		वापस 0;

	rel_pd_idx = (pd_index % I40IW_HMC_PD_CNT_IN_SD);
	pd_table = &hmc_info->sd_table.sd_entry[sd_idx].u.pd_table;
	pd_entry = &pd_table->pd_entry[rel_pd_idx];
	अगर (!pd_entry->valid) अणु
		अगर (rsrc_pg) अणु
			pd_entry->rsrc_pg = true;
			page = rsrc_pg;
		पूर्ण अन्यथा अणु
			ret_code = i40iw_allocate_dma_mem(hw, page,
							  I40IW_HMC_PAGED_BP_SIZE,
							  I40IW_HMC_PD_BP_BUF_ALIGNMENT);
			अगर (ret_code)
				वापस ret_code;
			pd_entry->rsrc_pg = false;
		पूर्ण

		स_नकल(&pd_entry->bp.addr, page, माप(काष्ठा i40iw_dma_mem));
		pd_entry->bp.sd_pd_index = pd_index;
		pd_entry->bp.entry_type = I40IW_SD_TYPE_PAGED;
		page_desc = page->pa | 0x1;

		pd_addr = (u64 *)pd_table->pd_page_addr.va;
		pd_addr += rel_pd_idx;

		स_नकल(pd_addr, &page_desc, माप(*pd_addr));

		pd_entry->sd_index = sd_idx;
		pd_entry->valid = true;
		I40IW_INC_PD_REFCNT(pd_table);
		अगर (hmc_info->hmc_fn_id < I40IW_FIRST_VF_FPM_ID)
			I40IW_INVALIDATE_PF_HMC_PD(hw, sd_idx, rel_pd_idx);
		अन्यथा अगर (hw->hmc.hmc_fn_id != hmc_info->hmc_fn_id)
			I40IW_INVALIDATE_VF_HMC_PD(hw, sd_idx, rel_pd_idx,
						   hmc_info->hmc_fn_id);
	पूर्ण
	I40IW_INC_BP_REFCNT(&pd_entry->bp);

	वापस 0;
पूर्ण

/**
 * i40iw_हटाओ_pd_bp - हटाओ a backing page from a page descriptor
 * @hw: poपूर्णांकer to our HW काष्ठाure
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठाure
 * @idx: the page index
 * @is_pf: distinguishes a VF from a PF
 *
 * This function:
 *	1. Marks the entry in pd table (क्रम paged address mode) or in sd table
 *	   (क्रम direct address mode) invalid.
 *	2. Write to रेजिस्टर PMPDINV to invalidate the backing page in FV cache
 *	3. Decrement the ref count क्रम the pd _entry
 * assumptions:
 *	1. Caller can deallocate the memory used by backing storage after this
 *	   function वापसs.
 */
क्रमागत i40iw_status_code i40iw_हटाओ_pd_bp(काष्ठा i40iw_hw *hw,
					  काष्ठा i40iw_hmc_info *hmc_info,
					  u32 idx,
					  bool is_pf)
अणु
	काष्ठा i40iw_hmc_pd_entry *pd_entry;
	काष्ठा i40iw_hmc_pd_table *pd_table;
	काष्ठा i40iw_hmc_sd_entry *sd_entry;
	u32 sd_idx, rel_pd_idx;
	काष्ठा i40iw_dma_mem *mem;
	u64 *pd_addr;

	sd_idx = idx / I40IW_HMC_PD_CNT_IN_SD;
	rel_pd_idx = idx % I40IW_HMC_PD_CNT_IN_SD;
	अगर (sd_idx >= hmc_info->sd_table.sd_cnt)
		वापस I40IW_ERR_INVALID_PAGE_DESC_INDEX;

	sd_entry = &hmc_info->sd_table.sd_entry[sd_idx];
	अगर (sd_entry->entry_type != I40IW_SD_TYPE_PAGED)
		वापस I40IW_ERR_INVALID_SD_TYPE;

	pd_table = &hmc_info->sd_table.sd_entry[sd_idx].u.pd_table;
	pd_entry = &pd_table->pd_entry[rel_pd_idx];
	I40IW_DEC_BP_REFCNT(&pd_entry->bp);
	अगर (pd_entry->bp.ref_cnt)
		वापस 0;

	pd_entry->valid = false;
	I40IW_DEC_PD_REFCNT(pd_table);
	pd_addr = (u64 *)pd_table->pd_page_addr.va;
	pd_addr += rel_pd_idx;
	स_रखो(pd_addr, 0, माप(u64));
	अगर (is_pf)
		I40IW_INVALIDATE_PF_HMC_PD(hw, sd_idx, idx);
	अन्यथा
		I40IW_INVALIDATE_VF_HMC_PD(hw, sd_idx, idx,
					   hmc_info->hmc_fn_id);

	अगर (!pd_entry->rsrc_pg) अणु
		mem = &pd_entry->bp.addr;
		अगर (!mem || !mem->va)
			वापस I40IW_ERR_PARAM;
		i40iw_मुक्त_dma_mem(hw, mem);
	पूर्ण
	अगर (!pd_table->ref_cnt)
		i40iw_मुक्त_virt_mem(hw, &pd_table->pd_entry_virt_mem);

	वापस 0;
पूर्ण

/**
 * i40iw_prep_हटाओ_sd_bp - Prepares to हटाओ a backing page from a sd entry
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठाure
 * @idx: the page index
 */
क्रमागत i40iw_status_code i40iw_prep_हटाओ_sd_bp(काष्ठा i40iw_hmc_info *hmc_info, u32 idx)
अणु
	काष्ठा i40iw_hmc_sd_entry *sd_entry;

	sd_entry = &hmc_info->sd_table.sd_entry[idx];
	I40IW_DEC_BP_REFCNT(&sd_entry->u.bp);
	अगर (sd_entry->u.bp.ref_cnt)
		वापस I40IW_ERR_NOT_READY;

	I40IW_DEC_SD_REFCNT(&hmc_info->sd_table);
	sd_entry->valid = false;

	वापस 0;
पूर्ण

/**
 * i40iw_prep_हटाओ_pd_page - Prepares to हटाओ a PD page from sd entry.
 * @hmc_info: poपूर्णांकer to the HMC configuration inक्रमmation काष्ठाure
 * @idx: segment descriptor index to find the relevant page descriptor
 */
क्रमागत i40iw_status_code i40iw_prep_हटाओ_pd_page(काष्ठा i40iw_hmc_info *hmc_info,
						 u32 idx)
अणु
	काष्ठा i40iw_hmc_sd_entry *sd_entry;

	sd_entry = &hmc_info->sd_table.sd_entry[idx];

	अगर (sd_entry->u.pd_table.ref_cnt)
		वापस I40IW_ERR_NOT_READY;

	sd_entry->valid = false;
	I40IW_DEC_SD_REFCNT(&hmc_info->sd_table);

	वापस 0;
पूर्ण

/**
 * i40iw_pf_init_vfhmc -
 * @vf_cnt_array: array of cnt values of iwarp hmc objects
 * @vf_hmc_fn_id: hmc function id ofr vf driver
 * @dev: poपूर्णांकer to i40iw_dev काष्ठा
 *
 * Called by pf driver to initialize hmc_info क्रम vf driver instance.
 */
क्रमागत i40iw_status_code i40iw_pf_init_vfhmc(काष्ठा i40iw_sc_dev *dev,
					   u8 vf_hmc_fn_id,
					   u32 *vf_cnt_array)
अणु
	काष्ठा i40iw_hmc_info *hmc_info;
	क्रमागत i40iw_status_code ret_code = 0;
	u32 i;

	अगर ((vf_hmc_fn_id < I40IW_FIRST_VF_FPM_ID) ||
	    (vf_hmc_fn_id >= I40IW_FIRST_VF_FPM_ID +
	     I40IW_MAX_PE_ENABLED_VF_COUNT)) अणु
		i40iw_debug(dev, I40IW_DEBUG_HMC, "%s: invalid vf_hmc_fn_id  0x%x\n",
			    __func__, vf_hmc_fn_id);
		वापस I40IW_ERR_INVALID_HMCFN_ID;
	पूर्ण

	ret_code = i40iw_sc_init_iw_hmc(dev, vf_hmc_fn_id);
	अगर (ret_code)
		वापस ret_code;

	hmc_info = i40iw_vf_hmcinfo_from_fpm(dev, vf_hmc_fn_id);

	क्रम (i = I40IW_HMC_IW_QP; i < I40IW_HMC_IW_MAX; i++)
		अगर (vf_cnt_array)
			hmc_info->hmc_obj[i].cnt =
			    vf_cnt_array[i - I40IW_HMC_IW_QP];
		अन्यथा
			hmc_info->hmc_obj[i].cnt = hmc_info->hmc_obj[i].max_cnt;

	वापस 0;
पूर्ण
