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

#अगर_अघोषित I40IW_OSDEP_H
#घोषणा I40IW_OSDEP_H

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/bitops.h>
#समावेश <net/tcp.h>
#समावेश <crypto/hash.h>
/* get पढ़ोq/ग_लिखोq support क्रम 32 bit kernels, use the low-first version */
#समावेश <linux/io-64-nonatomic-lo-hi.h>

#घोषणा STATS_TIMER_DELAY 1000

अटल अंतरभूत व्योम set_64bit_val(u64 *wqe_words, u32 byte_index, u64 value)
अणु
	wqe_words[byte_index >> 3] = value;
पूर्ण

/**
 * get_64bit_val - पढ़ो 64 bit value from wqe
 * @wqe_words: wqe addr
 * @byte_index: index to पढ़ो from
 * @value: पढ़ो value
 **/
अटल अंतरभूत व्योम get_64bit_val(u64 *wqe_words, u32 byte_index, u64 *value)
अणु
	*value = wqe_words[byte_index >> 3];
पूर्ण

काष्ठा i40iw_dma_mem अणु
	व्योम *va;
	dma_addr_t pa;
	u32 size;
पूर्ण __packed;

काष्ठा i40iw_virt_mem अणु
	व्योम *va;
	u32 size;
पूर्ण __packed;

#घोषणा i40iw_debug(h, m, s, ...)                               \
करो अणु                                                            \
	अगर (((m) & (h)->debug_mask))                            \
		pr_info("i40iw " s, ##__VA_ARGS__);             \
पूर्ण जबतक (0)

#घोषणा i40iw_flush(a)          पढ़ोl((a)->hw_addr + I40E_GLGEN_STAT)

#घोषणा I40E_GLHMC_VFSDCMD(_i)  (0x000C8000 + ((_i) * 4)) \
				/* _i=0...31 */
#घोषणा I40E_GLHMC_VFSDCMD_MAX_INDEX    31
#घोषणा I40E_GLHMC_VFSDCMD_PMSDIDX_SHIFT  0
#घोषणा I40E_GLHMC_VFSDCMD_PMSDIDX_MASK  (0xFFF \
					  << I40E_GLHMC_VFSDCMD_PMSDIDX_SHIFT)
#घोषणा I40E_GLHMC_VFSDCMD_PF_SHIFT       16
#घोषणा I40E_GLHMC_VFSDCMD_PF_MASK        (0xF << I40E_GLHMC_VFSDCMD_PF_SHIFT)
#घोषणा I40E_GLHMC_VFSDCMD_VF_SHIFT       20
#घोषणा I40E_GLHMC_VFSDCMD_VF_MASK        (0x1FF << I40E_GLHMC_VFSDCMD_VF_SHIFT)
#घोषणा I40E_GLHMC_VFSDCMD_PMF_TYPE_SHIFT 29
#घोषणा I40E_GLHMC_VFSDCMD_PMF_TYPE_MASK  (0x3 \
					   << I40E_GLHMC_VFSDCMD_PMF_TYPE_SHIFT)
#घोषणा I40E_GLHMC_VFSDCMD_PMSDWR_SHIFT   31
#घोषणा I40E_GLHMC_VFSDCMD_PMSDWR_MASK  (0x1 << I40E_GLHMC_VFSDCMD_PMSDWR_SHIFT)

#घोषणा I40E_GLHMC_VFSDDATAHIGH(_i)     (0x000C8200 + ((_i) * 4)) \
				/* _i=0...31 */
#घोषणा I40E_GLHMC_VFSDDATAHIGH_MAX_INDEX       31
#घोषणा I40E_GLHMC_VFSDDATAHIGH_PMSDDATAHIGH_SHIFT 0
#घोषणा I40E_GLHMC_VFSDDATAHIGH_PMSDDATAHIGH_MASK  (0xFFFFFFFF \
			<< I40E_GLHMC_VFSDDATAHIGH_PMSDDATAHIGH_SHIFT)

#घोषणा I40E_GLHMC_VFSDDATALOW(_i)      (0x000C8100 + ((_i) * 4)) \
				/* _i=0...31 */
#घोषणा I40E_GLHMC_VFSDDATALOW_MAX_INDEX        31
#घोषणा I40E_GLHMC_VFSDDATALOW_PMSDVALID_SHIFT   0
#घोषणा I40E_GLHMC_VFSDDATALOW_PMSDVALID_MASK  (0x1 \
			<< I40E_GLHMC_VFSDDATALOW_PMSDVALID_SHIFT)
#घोषणा I40E_GLHMC_VFSDDATALOW_PMSDTYPE_SHIFT    1
#घोषणा I40E_GLHMC_VFSDDATALOW_PMSDTYPE_MASK  (0x1 \
			<< I40E_GLHMC_VFSDDATALOW_PMSDTYPE_SHIFT)
#घोषणा I40E_GLHMC_VFSDDATALOW_PMSDBPCOUNT_SHIFT 2
#घोषणा I40E_GLHMC_VFSDDATALOW_PMSDBPCOUNT_MASK  (0x3FF \
			<< I40E_GLHMC_VFSDDATALOW_PMSDBPCOUNT_SHIFT)
#घोषणा I40E_GLHMC_VFSDDATALOW_PMSDDATALOW_SHIFT 12
#घोषणा I40E_GLHMC_VFSDDATALOW_PMSDDATALOW_MASK  (0xFFFFF \
			<< I40E_GLHMC_VFSDDATALOW_PMSDDATALOW_SHIFT)

#घोषणा I40E_GLPE_FWLDSTATUS                     0x0000D200
#घोषणा I40E_GLPE_FWLDSTATUS_LOAD_REQUESTED_SHIFT 0
#घोषणा I40E_GLPE_FWLDSTATUS_LOAD_REQUESTED_MASK  (0x1 \
			<< I40E_GLPE_FWLDSTATUS_LOAD_REQUESTED_SHIFT)
#घोषणा I40E_GLPE_FWLDSTATUS_DONE_SHIFT           1
#घोषणा I40E_GLPE_FWLDSTATUS_DONE_MASK  (0x1 << I40E_GLPE_FWLDSTATUS_DONE_SHIFT)
#घोषणा I40E_GLPE_FWLDSTATUS_CQP_FAIL_SHIFT       2
#घोषणा I40E_GLPE_FWLDSTATUS_CQP_FAIL_MASK  (0x1 \
			 << I40E_GLPE_FWLDSTATUS_CQP_FAIL_SHIFT)
#घोषणा I40E_GLPE_FWLDSTATUS_TEP_FAIL_SHIFT       3
#घोषणा I40E_GLPE_FWLDSTATUS_TEP_FAIL_MASK  (0x1 \
			 << I40E_GLPE_FWLDSTATUS_TEP_FAIL_SHIFT)
#घोषणा I40E_GLPE_FWLDSTATUS_OOP_FAIL_SHIFT       4
#घोषणा I40E_GLPE_FWLDSTATUS_OOP_FAIL_MASK  (0x1 \
			 << I40E_GLPE_FWLDSTATUS_OOP_FAIL_SHIFT)

काष्ठा i40iw_sc_dev;
काष्ठा i40iw_sc_qp;
काष्ठा i40iw_puda_buf;
काष्ठा i40iw_puda_completion_info;
काष्ठा i40iw_update_sds_info;
काष्ठा i40iw_hmc_fcn_info;
काष्ठा i40iw_virtchnl_work_info;
काष्ठा i40iw_manage_vf_pble_info;
काष्ठा i40iw_device;
काष्ठा i40iw_hmc_info;
काष्ठा i40iw_hw;

u8 __iomem *i40iw_get_hw_addr(व्योम *dev);
व्योम i40iw_ieq_mpa_crc_ae(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_sc_qp *qp);
क्रमागत i40iw_status_code i40iw_vf_रुको_vchnl_resp(काष्ठा i40iw_sc_dev *dev);
bool i40iw_vf_clear_to_send(काष्ठा i40iw_sc_dev *dev);
क्रमागत i40iw_status_code i40iw_ieq_check_mpacrc(काष्ठा shash_desc *desc, व्योम *addr,
					      u32 length, u32 value);
काष्ठा i40iw_sc_qp *i40iw_ieq_get_qp(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_puda_buf *buf);
व्योम i40iw_ieq_update_tcpip_info(काष्ठा i40iw_puda_buf *buf, u16 length, u32 seqnum);
व्योम i40iw_मुक्त_hash_desc(काष्ठा shash_desc *);
क्रमागत i40iw_status_code i40iw_init_hash_desc(काष्ठा shash_desc **);
क्रमागत i40iw_status_code i40iw_puda_get_tcpip_info(काष्ठा i40iw_puda_completion_info *info,
						 काष्ठा i40iw_puda_buf *buf);
क्रमागत i40iw_status_code i40iw_cqp_sds_cmd(काष्ठा i40iw_sc_dev *dev,
					 काष्ठा i40iw_update_sds_info *info);
क्रमागत i40iw_status_code i40iw_cqp_manage_hmc_fcn_cmd(काष्ठा i40iw_sc_dev *dev,
						    काष्ठा i40iw_hmc_fcn_info *hmcfcninfo);
क्रमागत i40iw_status_code i40iw_cqp_query_fpm_values_cmd(काष्ठा i40iw_sc_dev *dev,
						      काष्ठा i40iw_dma_mem *values_mem,
						      u8 hmc_fn_id);
क्रमागत i40iw_status_code i40iw_cqp_commit_fpm_values_cmd(काष्ठा i40iw_sc_dev *dev,
						       काष्ठा i40iw_dma_mem *values_mem,
						       u8 hmc_fn_id);
क्रमागत i40iw_status_code i40iw_alloc_query_fpm_buf(काष्ठा i40iw_sc_dev *dev,
						 काष्ठा i40iw_dma_mem *mem);
क्रमागत i40iw_status_code i40iw_cqp_manage_vf_pble_bp(काष्ठा i40iw_sc_dev *dev,
						   काष्ठा i40iw_manage_vf_pble_info *info);
व्योम i40iw_cqp_spawn_worker(काष्ठा i40iw_sc_dev *dev,
			    काष्ठा i40iw_virtchnl_work_info *work_info, u32 iw_vf_idx);
व्योम *i40iw_हटाओ_head(काष्ठा list_head *list);
व्योम i40iw_qp_suspend_resume(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_sc_qp *qp, bool suspend);

व्योम i40iw_term_modअगरy_qp(काष्ठा i40iw_sc_qp *qp, u8 next_state, u8 term, u8 term_len);
व्योम i40iw_terminate_करोne(काष्ठा i40iw_sc_qp *qp, पूर्णांक समयout_occurred);
व्योम i40iw_terminate_start_समयr(काष्ठा i40iw_sc_qp *qp);
व्योम i40iw_terminate_del_समयr(काष्ठा i40iw_sc_qp *qp);

क्रमागत i40iw_status_code i40iw_hw_manage_vf_pble_bp(काष्ठा i40iw_device *iwdev,
						  काष्ठा i40iw_manage_vf_pble_info *info,
						  bool रुको);
काष्ठा i40iw_sc_vsi;
व्योम i40iw_hw_stats_start_समयr(काष्ठा i40iw_sc_vsi *vsi);
व्योम i40iw_hw_stats_stop_समयr(काष्ठा i40iw_sc_vsi *vsi);
#घोषणा i40iw_mmiowb() करो अणु पूर्ण जबतक (0)
व्योम i40iw_wr32(काष्ठा i40iw_hw *hw, u32 reg, u32 value);
u32  i40iw_rd32(काष्ठा i40iw_hw *hw, u32 reg);
#पूर्ण_अगर				/* _I40IW_OSDEP_H_ */
