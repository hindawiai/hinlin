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

#अगर_अघोषित I40IW_HMC_H
#घोषणा I40IW_HMC_H

#समावेश "i40iw_d.h"

काष्ठा i40iw_hw;
क्रमागत i40iw_status_code;

#घोषणा I40IW_HMC_MAX_BP_COUNT 512
#घोषणा I40IW_MAX_SD_ENTRIES 11
#घोषणा I40IW_HW_DBG_HMC_INVALID_BP_MARK     0xCA

#घोषणा I40IW_HMC_INFO_SIGNATURE	0x484D5347
#घोषणा I40IW_HMC_PD_CNT_IN_SD		512
#घोषणा I40IW_HMC_सूचीECT_BP_SIZE	0x200000
#घोषणा I40IW_HMC_MAX_SD_COUNT		4096
#घोषणा I40IW_HMC_PAGED_BP_SIZE		4096
#घोषणा I40IW_HMC_PD_BP_BUF_ALIGNMENT	4096
#घोषणा I40IW_FIRST_VF_FPM_ID		16
#घोषणा FPM_MULTIPLIER			1024

#घोषणा I40IW_INC_SD_REFCNT(sd_table)   ((sd_table)->ref_cnt++)
#घोषणा I40IW_INC_PD_REFCNT(pd_table)   ((pd_table)->ref_cnt++)
#घोषणा I40IW_INC_BP_REFCNT(bp)         ((bp)->ref_cnt++)

#घोषणा I40IW_DEC_SD_REFCNT(sd_table)   ((sd_table)->ref_cnt--)
#घोषणा I40IW_DEC_PD_REFCNT(pd_table)   ((pd_table)->ref_cnt--)
#घोषणा I40IW_DEC_BP_REFCNT(bp)         ((bp)->ref_cnt--)

/**
 * I40IW_INVALIDATE_PF_HMC_PD - Invalidates the pd cache in the hardware
 * @hw: poपूर्णांकer to our hw काष्ठा
 * @sd_idx: segment descriptor index
 * @pd_idx: page descriptor index
 */
#घोषणा I40IW_INVALIDATE_PF_HMC_PD(hw, sd_idx, pd_idx)                  \
	i40iw_wr32((hw), I40E_PFHMC_PDINV,                                    \
		(((sd_idx) << I40E_PFHMC_PDINV_PMSDIDX_SHIFT) |             \
		(0x1 << I40E_PFHMC_PDINV_PMSDPARTSEL_SHIFT) | \
		((pd_idx) << I40E_PFHMC_PDINV_PMPDIDX_SHIFT)))

/**
 * I40IW_INVALIDATE_VF_HMC_PD - Invalidates the pd cache in the hardware
 * @hw: poपूर्णांकer to our hw काष्ठा
 * @sd_idx: segment descriptor index
 * @pd_idx: page descriptor index
 * @hmc_fn_id: VF's function id
 */
#घोषणा I40IW_INVALIDATE_VF_HMC_PD(hw, sd_idx, pd_idx, hmc_fn_id)        \
	i40iw_wr32(hw, I40E_GLHMC_VFPDINV(hmc_fn_id - I40IW_FIRST_VF_FPM_ID),  \
	     ((sd_idx << I40E_PFHMC_PDINV_PMSDIDX_SHIFT) |              \
	      (pd_idx << I40E_PFHMC_PDINV_PMPDIDX_SHIFT)))

काष्ठा i40iw_hmc_obj_info अणु
	u64 base;
	u32 max_cnt;
	u32 cnt;
	u64 size;
पूर्ण;

क्रमागत i40iw_sd_entry_type अणु
	I40IW_SD_TYPE_INVALID = 0,
	I40IW_SD_TYPE_PAGED = 1,
	I40IW_SD_TYPE_सूचीECT = 2
पूर्ण;

काष्ठा i40iw_hmc_bp अणु
	क्रमागत i40iw_sd_entry_type entry_type;
	काष्ठा i40iw_dma_mem addr;
	u32 sd_pd_index;
	u32 ref_cnt;
पूर्ण;

काष्ठा i40iw_hmc_pd_entry अणु
	काष्ठा i40iw_hmc_bp bp;
	u32 sd_index;
	bool rsrc_pg;
	bool valid;
पूर्ण;

काष्ठा i40iw_hmc_pd_table अणु
	काष्ठा i40iw_dma_mem pd_page_addr;
	काष्ठा i40iw_hmc_pd_entry *pd_entry;
	काष्ठा i40iw_virt_mem pd_entry_virt_mem;
	u32 ref_cnt;
	u32 sd_index;
पूर्ण;

काष्ठा i40iw_hmc_sd_entry अणु
	क्रमागत i40iw_sd_entry_type entry_type;
	bool valid;

	जोड़ अणु
		काष्ठा i40iw_hmc_pd_table pd_table;
		काष्ठा i40iw_hmc_bp bp;
	पूर्ण u;
पूर्ण;

काष्ठा i40iw_hmc_sd_table अणु
	काष्ठा i40iw_virt_mem addr;
	u32 sd_cnt;
	u32 ref_cnt;
	काष्ठा i40iw_hmc_sd_entry *sd_entry;
पूर्ण;

काष्ठा i40iw_hmc_info अणु
	u32 signature;
	u8 hmc_fn_id;
	u16 first_sd_index;

	काष्ठा i40iw_hmc_obj_info *hmc_obj;
	काष्ठा i40iw_virt_mem hmc_obj_virt_mem;
	काष्ठा i40iw_hmc_sd_table sd_table;
	u16 sd_indexes[I40IW_HMC_MAX_SD_COUNT];
पूर्ण;

काष्ठा update_sd_entry अणु
	u64 cmd;
	u64 data;
पूर्ण;

काष्ठा i40iw_update_sds_info अणु
	u32 cnt;
	u8 hmc_fn_id;
	काष्ठा update_sd_entry entry[I40IW_MAX_SD_ENTRIES];
पूर्ण;

काष्ठा i40iw_ccq_cqe_info;
काष्ठा i40iw_hmc_fcn_info अणु
	व्योम (*callback_fcn)(काष्ठा i40iw_sc_dev *, व्योम *,
			     काष्ठा i40iw_ccq_cqe_info *);
	व्योम *cqp_callback_param;
	u32 vf_id;
	u16 iw_vf_idx;
	bool मुक्त_fcn;
पूर्ण;

क्रमागत i40iw_hmc_rsrc_type अणु
	I40IW_HMC_IW_QP = 0,
	I40IW_HMC_IW_CQ = 1,
	I40IW_HMC_IW_SRQ = 2,
	I40IW_HMC_IW_HTE = 3,
	I40IW_HMC_IW_ARP = 4,
	I40IW_HMC_IW_APBVT_ENTRY = 5,
	I40IW_HMC_IW_MR = 6,
	I40IW_HMC_IW_XF = 7,
	I40IW_HMC_IW_XFFL = 8,
	I40IW_HMC_IW_Q1 = 9,
	I40IW_HMC_IW_Q1FL = 10,
	I40IW_HMC_IW_TIMER = 11,
	I40IW_HMC_IW_FSIMC = 12,
	I40IW_HMC_IW_FSIAV = 13,
	I40IW_HMC_IW_PBLE = 14,
	I40IW_HMC_IW_MAX = 15,
पूर्ण;

काष्ठा i40iw_hmc_create_obj_info अणु
	काष्ठा i40iw_hmc_info *hmc_info;
	काष्ठा i40iw_virt_mem add_sd_virt_mem;
	u32 rsrc_type;
	u32 start_idx;
	u32 count;
	u32 add_sd_cnt;
	क्रमागत i40iw_sd_entry_type entry_type;
	bool is_pf;
पूर्ण;

काष्ठा i40iw_hmc_del_obj_info अणु
	काष्ठा i40iw_hmc_info *hmc_info;
	काष्ठा i40iw_virt_mem del_sd_virt_mem;
	u32 rsrc_type;
	u32 start_idx;
	u32 count;
	u32 del_sd_cnt;
	bool is_pf;
पूर्ण;

क्रमागत i40iw_status_code i40iw_copy_dma_mem(काष्ठा i40iw_hw *hw, व्योम *dest_buf,
					  काष्ठा i40iw_dma_mem *src_mem, u64 src_offset, u64 size);
क्रमागत i40iw_status_code i40iw_sc_create_hmc_obj(काष्ठा i40iw_sc_dev *dev,
					       काष्ठा i40iw_hmc_create_obj_info *info);
क्रमागत i40iw_status_code i40iw_sc_del_hmc_obj(काष्ठा i40iw_sc_dev *dev,
					    काष्ठा i40iw_hmc_del_obj_info *info,
					    bool reset);
क्रमागत i40iw_status_code i40iw_hmc_sd_one(काष्ठा i40iw_sc_dev *dev, u8 hmc_fn_id,
					u64 pa, u32 sd_idx, क्रमागत i40iw_sd_entry_type type,
					bool setsd);
क्रमागत i40iw_status_code i40iw_update_sds_noccq(काष्ठा i40iw_sc_dev *dev,
					      काष्ठा i40iw_update_sds_info *info);
काष्ठा i40iw_vfdev *i40iw_vfdev_from_fpm(काष्ठा i40iw_sc_dev *dev, u8 hmc_fn_id);
काष्ठा i40iw_hmc_info *i40iw_vf_hmcinfo_from_fpm(काष्ठा i40iw_sc_dev *dev,
						 u8 hmc_fn_id);
क्रमागत i40iw_status_code i40iw_add_sd_table_entry(काष्ठा i40iw_hw *hw,
						काष्ठा i40iw_hmc_info *hmc_info, u32 sd_index,
						क्रमागत i40iw_sd_entry_type type, u64 direct_mode_sz);
क्रमागत i40iw_status_code i40iw_add_pd_table_entry(काष्ठा i40iw_hw *hw,
						काष्ठा i40iw_hmc_info *hmc_info, u32 pd_index,
						काष्ठा i40iw_dma_mem *rsrc_pg);
क्रमागत i40iw_status_code i40iw_हटाओ_pd_bp(काष्ठा i40iw_hw *hw,
					  काष्ठा i40iw_hmc_info *hmc_info, u32 idx, bool is_pf);
क्रमागत i40iw_status_code i40iw_prep_हटाओ_sd_bp(काष्ठा i40iw_hmc_info *hmc_info, u32 idx);
क्रमागत i40iw_status_code i40iw_prep_हटाओ_pd_page(काष्ठा i40iw_hmc_info *hmc_info, u32 idx);

#घोषणा     ENTER_SHARED_FUNCTION()
#घोषणा     EXIT_SHARED_FUNCTION()

#पूर्ण_अगर				/* I40IW_HMC_H */
