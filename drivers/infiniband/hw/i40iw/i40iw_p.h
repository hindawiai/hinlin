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

#अगर_अघोषित I40IW_P_H
#घोषणा I40IW_P_H

#घोषणा PAUSE_TIMER_VALUE       0xFFFF
#घोषणा REFRESH_THRESHOLD       0x7FFF
#घोषणा HIGH_THRESHOLD          0x800
#घोषणा LOW_THRESHOLD           0x200
#घोषणा ALL_TC2PFC              0xFF
#घोषणा CQP_COMPL_WAIT_TIME     0x3E8
#घोषणा CQP_TIMEOUT_THRESHOLD   5

व्योम i40iw_debug_buf(काष्ठा i40iw_sc_dev *dev, क्रमागत i40iw_debug_flag mask,
		     अक्षर *desc, u64 *buf, u32 size);
/* init operations */
क्रमागत i40iw_status_code i40iw_device_init(काष्ठा i40iw_sc_dev *dev,
					 काष्ठा i40iw_device_init_info *info);

व्योम i40iw_sc_cqp_post_sq(काष्ठा i40iw_sc_cqp *cqp);

u64 *i40iw_sc_cqp_get_next_send_wqe(काष्ठा i40iw_sc_cqp *cqp, u64 scratch);

व्योम i40iw_check_cqp_progress(काष्ठा i40iw_cqp_समयout *cqp_समयout, काष्ठा i40iw_sc_dev *dev);

क्रमागत i40iw_status_code i40iw_sc_mr_fast_रेजिस्टर(काष्ठा i40iw_sc_qp *qp,
						 काष्ठा i40iw_fast_reg_stag_info *info,
						 bool post_sq);

व्योम i40iw_insert_wqe_hdr(u64 *wqe, u64 header);

/* HMC/FPM functions */
क्रमागत i40iw_status_code i40iw_sc_init_iw_hmc(काष्ठा i40iw_sc_dev *dev,
					    u8 hmc_fn_id);

क्रमागत i40iw_status_code i40iw_pf_init_vfhmc(काष्ठा i40iw_sc_dev *dev, u8 vf_hmc_fn_id,
					   u32 *vf_cnt_array);

/* stats functions */
व्योम i40iw_hw_stats_refresh_all(काष्ठा i40iw_vsi_pestat *stats);
व्योम i40iw_hw_stats_पढ़ो_all(काष्ठा i40iw_vsi_pestat *stats, काष्ठा i40iw_dev_hw_stats *stats_values);
व्योम i40iw_hw_stats_पढ़ो_32(काष्ठा i40iw_vsi_pestat *stats,
			    क्रमागत i40iw_hw_stats_index_32b index,
			    u64 *value);
व्योम i40iw_hw_stats_पढ़ो_64(काष्ठा i40iw_vsi_pestat *stats,
			    क्रमागत i40iw_hw_stats_index_64b index,
			    u64 *value);
व्योम i40iw_hw_stats_init(काष्ठा i40iw_vsi_pestat *stats, u8 index, bool is_pf);

/* vsi misc functions */
क्रमागत i40iw_status_code i40iw_vsi_stats_init(काष्ठा i40iw_sc_vsi *vsi, काष्ठा i40iw_vsi_stats_info *info);
व्योम i40iw_vsi_stats_मुक्त(काष्ठा i40iw_sc_vsi *vsi);
व्योम i40iw_sc_vsi_init(काष्ठा i40iw_sc_vsi *vsi, काष्ठा i40iw_vsi_init_info *info);

व्योम i40iw_change_l2params(काष्ठा i40iw_sc_vsi *vsi, काष्ठा i40iw_l2params *l2params);
व्योम i40iw_qp_add_qos(काष्ठा i40iw_sc_qp *qp);
व्योम i40iw_qp_rem_qos(काष्ठा i40iw_sc_qp *qp);
व्योम i40iw_terminate_send_fin(काष्ठा i40iw_sc_qp *qp);

व्योम i40iw_terminate_connection(काष्ठा i40iw_sc_qp *qp, काष्ठा i40iw_aeqe_info *info);

व्योम i40iw_terminate_received(काष्ठा i40iw_sc_qp *qp, काष्ठा i40iw_aeqe_info *info);

क्रमागत i40iw_status_code i40iw_sc_suspend_qp(काष्ठा i40iw_sc_cqp *cqp,
					   काष्ठा i40iw_sc_qp *qp, u64 scratch);

क्रमागत i40iw_status_code i40iw_sc_resume_qp(काष्ठा i40iw_sc_cqp *cqp,
					  काष्ठा i40iw_sc_qp *qp, u64 scratch);

क्रमागत i40iw_status_code i40iw_sc_अटल_hmc_pages_allocated(काष्ठा i40iw_sc_cqp *cqp,
							   u64 scratch, u8 hmc_fn_id,
							   bool post_sq,
							   bool poll_रेजिस्टरs);

क्रमागत i40iw_status_code i40iw_config_fpm_values(काष्ठा i40iw_sc_dev *dev, u32 qp_count);
क्रमागत i40iw_status_code i40iw_get_rdma_features(काष्ठा i40iw_sc_dev *dev);

व्योम मुक्त_sd_mem(काष्ठा i40iw_sc_dev *dev);

क्रमागत i40iw_status_code i40iw_process_cqp_cmd(काष्ठा i40iw_sc_dev *dev,
					     काष्ठा cqp_commands_info *pcmdinfo);

क्रमागत i40iw_status_code i40iw_process_bh(काष्ठा i40iw_sc_dev *dev);

/* prototype क्रम functions used क्रम dynamic memory allocation */
क्रमागत i40iw_status_code i40iw_allocate_dma_mem(काष्ठा i40iw_hw *hw,
					      काष्ठा i40iw_dma_mem *mem, u64 size,
					      u32 alignment);
व्योम i40iw_मुक्त_dma_mem(काष्ठा i40iw_hw *hw, काष्ठा i40iw_dma_mem *mem);
क्रमागत i40iw_status_code i40iw_allocate_virt_mem(काष्ठा i40iw_hw *hw,
					       काष्ठा i40iw_virt_mem *mem, u32 size);
क्रमागत i40iw_status_code i40iw_मुक्त_virt_mem(काष्ठा i40iw_hw *hw,
					   काष्ठा i40iw_virt_mem *mem);
u8 i40iw_get_encoded_wqe_size(u32 wqsize, bool cqpsq);
व्योम i40iw_reinitialize_ieq(काष्ठा i40iw_sc_dev *dev);

#पूर्ण_अगर
