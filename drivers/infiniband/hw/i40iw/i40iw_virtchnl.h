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

#अगर_अघोषित I40IW_VIRTCHNL_H
#घोषणा I40IW_VIRTCHNL_H

#समावेश "i40iw_hmc.h"

#आशय pack(push, 1)

काष्ठा i40iw_virtchnl_op_buf अणु
	u16 iw_op_code;
	u16 iw_op_ver;
	u16 iw_chnl_buf_len;
	u16 rsvd;
	u64 iw_chnl_op_ctx;
	/* Member alignment MUST be मुख्यtained above this location */
	u8 iw_chnl_buf[1];
पूर्ण;

काष्ठा i40iw_virtchnl_resp_buf अणु
	u64 iw_chnl_op_ctx;
	u16 iw_chnl_buf_len;
	s16 iw_op_ret_code;
	/* Member alignment MUST be मुख्यtained above this location */
	u16 rsvd[2];
	u8 iw_chnl_buf[1];
पूर्ण;

क्रमागत i40iw_virtchnl_ops अणु
	I40IW_VCHNL_OP_GET_VER = 0,
	I40IW_VCHNL_OP_GET_HMC_FCN,
	I40IW_VCHNL_OP_ADD_HMC_OBJ_RANGE,
	I40IW_VCHNL_OP_DEL_HMC_OBJ_RANGE,
	I40IW_VCHNL_OP_GET_STATS
पूर्ण;

#घोषणा I40IW_VCHNL_OP_GET_VER_V0 0
#घोषणा I40IW_VCHNL_OP_GET_HMC_FCN_V0 0
#घोषणा I40IW_VCHNL_OP_ADD_HMC_OBJ_RANGE_V0 0
#घोषणा I40IW_VCHNL_OP_DEL_HMC_OBJ_RANGE_V0 0
#घोषणा I40IW_VCHNL_OP_GET_STATS_V0 0
#घोषणा I40IW_VCHNL_CHNL_VER_V0 0

काष्ठा i40iw_dev_hw_stats;

काष्ठा i40iw_virtchnl_hmc_obj_range अणु
	u16 obj_type;
	u16 rsvd;
	u32 start_index;
	u32 obj_count;
पूर्ण;

क्रमागत i40iw_status_code i40iw_vchnl_recv_pf(काष्ठा i40iw_sc_dev *dev,
					   u32 vf_id,
					   u8 *msg,
					   u16 len);

क्रमागत i40iw_status_code i40iw_vchnl_recv_vf(काष्ठा i40iw_sc_dev *dev,
					   u32 vf_id,
					   u8 *msg,
					   u16 len);

काष्ठा i40iw_virtchnl_req अणु
	काष्ठा i40iw_sc_dev *dev;
	काष्ठा i40iw_virtchnl_op_buf *vchnl_msg;
	व्योम *parm;
	u32 vf_id;
	u16 parm_len;
	s16 ret_code;
पूर्ण;

#आशय pack(pop)

क्रमागत i40iw_status_code i40iw_vchnl_vf_get_ver(काष्ठा i40iw_sc_dev *dev,
					      u32 *vchnl_ver);

क्रमागत i40iw_status_code i40iw_vchnl_vf_get_hmc_fcn(काष्ठा i40iw_sc_dev *dev,
						  u16 *hmc_fcn);

क्रमागत i40iw_status_code i40iw_vchnl_vf_add_hmc_objs(काष्ठा i40iw_sc_dev *dev,
						   क्रमागत i40iw_hmc_rsrc_type rsrc_type,
						   u32 start_index,
						   u32 rsrc_count);

क्रमागत i40iw_status_code i40iw_vchnl_vf_del_hmc_obj(काष्ठा i40iw_sc_dev *dev,
						  क्रमागत i40iw_hmc_rsrc_type rsrc_type,
						  u32 start_index,
						  u32 rsrc_count);

क्रमागत i40iw_status_code i40iw_vchnl_vf_get_pe_stats(काष्ठा i40iw_sc_dev *dev,
						   काष्ठा i40iw_dev_hw_stats *hw_stats);
#पूर्ण_अगर
