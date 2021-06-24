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
#समावेश "i40iw_virtchnl.h"

/**
 * vchnl_vf_send_get_ver_req - Request Channel version
 * @dev: IWARP device poपूर्णांकer
 * @vchnl_req: Virtual channel message request poपूर्णांकer
 */
अटल क्रमागत i40iw_status_code vchnl_vf_send_get_ver_req(काष्ठा i40iw_sc_dev *dev,
							काष्ठा i40iw_virtchnl_req *vchnl_req)
अणु
	क्रमागत i40iw_status_code ret_code = I40IW_ERR_NOT_READY;
	काष्ठा i40iw_virtchnl_op_buf *vchnl_msg = vchnl_req->vchnl_msg;

	अगर (!dev->vchnl_up)
		वापस ret_code;

	स_रखो(vchnl_msg, 0, माप(*vchnl_msg));
	vchnl_msg->iw_chnl_op_ctx = (uपूर्णांकptr_t)vchnl_req;
	vchnl_msg->iw_chnl_buf_len = माप(*vchnl_msg);
	vchnl_msg->iw_op_code = I40IW_VCHNL_OP_GET_VER;
	vchnl_msg->iw_op_ver = I40IW_VCHNL_OP_GET_VER_V0;
	ret_code = dev->vchnl_अगर.vchnl_send(dev, 0, (u8 *)vchnl_msg, vchnl_msg->iw_chnl_buf_len);
	अगर (ret_code)
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s: virt channel send failed 0x%x\n", __func__, ret_code);
	वापस ret_code;
पूर्ण

/**
 * vchnl_vf_send_get_hmc_fcn_req - Request HMC Function from VF
 * @dev: IWARP device poपूर्णांकer
 * @vchnl_req: Virtual channel message request poपूर्णांकer
 */
अटल क्रमागत i40iw_status_code vchnl_vf_send_get_hmc_fcn_req(काष्ठा i40iw_sc_dev *dev,
							    काष्ठा i40iw_virtchnl_req *vchnl_req)
अणु
	क्रमागत i40iw_status_code ret_code = I40IW_ERR_NOT_READY;
	काष्ठा i40iw_virtchnl_op_buf *vchnl_msg = vchnl_req->vchnl_msg;

	अगर (!dev->vchnl_up)
		वापस ret_code;

	स_रखो(vchnl_msg, 0, माप(*vchnl_msg));
	vchnl_msg->iw_chnl_op_ctx = (uपूर्णांकptr_t)vchnl_req;
	vchnl_msg->iw_chnl_buf_len = माप(*vchnl_msg);
	vchnl_msg->iw_op_code = I40IW_VCHNL_OP_GET_HMC_FCN;
	vchnl_msg->iw_op_ver = I40IW_VCHNL_OP_GET_HMC_FCN_V0;
	ret_code = dev->vchnl_अगर.vchnl_send(dev, 0, (u8 *)vchnl_msg, vchnl_msg->iw_chnl_buf_len);
	अगर (ret_code)
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s: virt channel send failed 0x%x\n", __func__, ret_code);
	वापस ret_code;
पूर्ण

/**
 * vchnl_vf_send_get_pe_stats_req - Request PE stats from VF
 * @dev: IWARP device poपूर्णांकer
 * @vchnl_req: Virtual channel message request poपूर्णांकer
 */
अटल क्रमागत i40iw_status_code vchnl_vf_send_get_pe_stats_req(काष्ठा i40iw_sc_dev *dev,
							     काष्ठा i40iw_virtchnl_req  *vchnl_req)
अणु
	क्रमागत i40iw_status_code ret_code = I40IW_ERR_NOT_READY;
	काष्ठा i40iw_virtchnl_op_buf *vchnl_msg = vchnl_req->vchnl_msg;

	अगर (!dev->vchnl_up)
		वापस ret_code;

	स_रखो(vchnl_msg, 0, माप(*vchnl_msg));
	vchnl_msg->iw_chnl_op_ctx = (uपूर्णांकptr_t)vchnl_req;
	vchnl_msg->iw_chnl_buf_len = माप(*vchnl_msg) + माप(काष्ठा i40iw_dev_hw_stats) - 1;
	vchnl_msg->iw_op_code = I40IW_VCHNL_OP_GET_STATS;
	vchnl_msg->iw_op_ver = I40IW_VCHNL_OP_GET_STATS_V0;
	ret_code = dev->vchnl_अगर.vchnl_send(dev, 0, (u8 *)vchnl_msg, vchnl_msg->iw_chnl_buf_len);
	अगर (ret_code)
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s: virt channel send failed 0x%x\n", __func__, ret_code);
	वापस ret_code;
पूर्ण

/*
 * vchnl_vf_send_add_hmc_objs_req - Add HMC objects
 * @dev: IWARP device poपूर्णांकer
 * @vchnl_req: Virtual channel message request poपूर्णांकer
 */
अटल क्रमागत i40iw_status_code vchnl_vf_send_add_hmc_objs_req(काष्ठा i40iw_sc_dev *dev,
							     काष्ठा i40iw_virtchnl_req *vchnl_req,
							     क्रमागत i40iw_hmc_rsrc_type rsrc_type,
							     u32 start_index,
							     u32 rsrc_count)
अणु
	क्रमागत i40iw_status_code ret_code = I40IW_ERR_NOT_READY;
	काष्ठा i40iw_virtchnl_op_buf *vchnl_msg = vchnl_req->vchnl_msg;
	काष्ठा i40iw_virtchnl_hmc_obj_range *add_hmc_obj;

	अगर (!dev->vchnl_up)
		वापस ret_code;

	add_hmc_obj = (काष्ठा i40iw_virtchnl_hmc_obj_range *)vchnl_msg->iw_chnl_buf;
	स_रखो(vchnl_msg, 0, माप(*vchnl_msg));
	स_रखो(add_hmc_obj, 0, माप(*add_hmc_obj));
	vchnl_msg->iw_chnl_op_ctx = (uपूर्णांकptr_t)vchnl_req;
	vchnl_msg->iw_chnl_buf_len = माप(*vchnl_msg) + माप(काष्ठा i40iw_virtchnl_hmc_obj_range) - 1;
	vchnl_msg->iw_op_code = I40IW_VCHNL_OP_ADD_HMC_OBJ_RANGE;
	vchnl_msg->iw_op_ver = I40IW_VCHNL_OP_ADD_HMC_OBJ_RANGE_V0;
	add_hmc_obj->obj_type = (u16)rsrc_type;
	add_hmc_obj->start_index = start_index;
	add_hmc_obj->obj_count = rsrc_count;
	ret_code = dev->vchnl_अगर.vchnl_send(dev, 0, (u8 *)vchnl_msg, vchnl_msg->iw_chnl_buf_len);
	अगर (ret_code)
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s: virt channel send failed 0x%x\n", __func__, ret_code);
	वापस ret_code;
पूर्ण

/**
 * vchnl_vf_send_del_hmc_objs_req - del HMC objects
 * @dev: IWARP device poपूर्णांकer
 * @vchnl_req: Virtual channel message request poपूर्णांकer
 * @rsrc_type: resource type to delete
 * @start_index: starting index क्रम resource
 * @rsrc_count: number of resource type to delete
 */
अटल क्रमागत i40iw_status_code vchnl_vf_send_del_hmc_objs_req(काष्ठा i40iw_sc_dev *dev,
							     काष्ठा i40iw_virtchnl_req *vchnl_req,
							     क्रमागत i40iw_hmc_rsrc_type rsrc_type,
							     u32 start_index,
							     u32 rsrc_count)
अणु
	क्रमागत i40iw_status_code ret_code = I40IW_ERR_NOT_READY;
	काष्ठा i40iw_virtchnl_op_buf *vchnl_msg = vchnl_req->vchnl_msg;
	काष्ठा i40iw_virtchnl_hmc_obj_range *add_hmc_obj;

	अगर (!dev->vchnl_up)
		वापस ret_code;

	add_hmc_obj = (काष्ठा i40iw_virtchnl_hmc_obj_range *)vchnl_msg->iw_chnl_buf;
	स_रखो(vchnl_msg, 0, माप(*vchnl_msg));
	स_रखो(add_hmc_obj, 0, माप(*add_hmc_obj));
	vchnl_msg->iw_chnl_op_ctx = (uपूर्णांकptr_t)vchnl_req;
	vchnl_msg->iw_chnl_buf_len = माप(*vchnl_msg) + माप(काष्ठा i40iw_virtchnl_hmc_obj_range) - 1;
	vchnl_msg->iw_op_code = I40IW_VCHNL_OP_DEL_HMC_OBJ_RANGE;
	vchnl_msg->iw_op_ver = I40IW_VCHNL_OP_DEL_HMC_OBJ_RANGE_V0;
	add_hmc_obj->obj_type = (u16)rsrc_type;
	add_hmc_obj->start_index = start_index;
	add_hmc_obj->obj_count = rsrc_count;
	ret_code = dev->vchnl_अगर.vchnl_send(dev, 0, (u8 *)vchnl_msg, vchnl_msg->iw_chnl_buf_len);
	अगर (ret_code)
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s: virt channel send failed 0x%x\n", __func__, ret_code);
	वापस ret_code;
पूर्ण

/**
 * vchnl_pf_send_get_ver_resp - Send channel version to VF
 * @dev: IWARP device poपूर्णांकer
 * @vf_id: Virtual function ID associated with the message
 * @vchnl_msg: Virtual channel message buffer poपूर्णांकer
 */
अटल व्योम vchnl_pf_send_get_ver_resp(काष्ठा i40iw_sc_dev *dev,
				       u32 vf_id,
				       काष्ठा i40iw_virtchnl_op_buf *vchnl_msg)
अणु
	क्रमागत i40iw_status_code ret_code;
	u8 resp_buffer[माप(काष्ठा i40iw_virtchnl_resp_buf) + माप(u32) - 1];
	काष्ठा i40iw_virtchnl_resp_buf *vchnl_msg_resp = (काष्ठा i40iw_virtchnl_resp_buf *)resp_buffer;

	स_रखो(resp_buffer, 0, माप(*resp_buffer));
	vchnl_msg_resp->iw_chnl_op_ctx = vchnl_msg->iw_chnl_op_ctx;
	vchnl_msg_resp->iw_chnl_buf_len = माप(resp_buffer);
	vchnl_msg_resp->iw_op_ret_code = I40IW_SUCCESS;
	*((u32 *)vchnl_msg_resp->iw_chnl_buf) = I40IW_VCHNL_CHNL_VER_V0;
	ret_code = dev->vchnl_अगर.vchnl_send(dev, vf_id, resp_buffer, माप(resp_buffer));
	अगर (ret_code)
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s: virt channel send failed 0x%x\n", __func__, ret_code);
पूर्ण

/**
 * vchnl_pf_send_get_hmc_fcn_resp - Send HMC Function to VF
 * @dev: IWARP device poपूर्णांकer
 * @vf_id: Virtual function ID associated with the message
 * @vchnl_msg: Virtual channel message buffer poपूर्णांकer
 * @hmc_fcn: HMC function index poपूर्णांकer
 */
अटल व्योम vchnl_pf_send_get_hmc_fcn_resp(काष्ठा i40iw_sc_dev *dev,
					   u32 vf_id,
					   काष्ठा i40iw_virtchnl_op_buf *vchnl_msg,
					   u16 hmc_fcn)
अणु
	क्रमागत i40iw_status_code ret_code;
	u8 resp_buffer[माप(काष्ठा i40iw_virtchnl_resp_buf) + माप(u16) - 1];
	काष्ठा i40iw_virtchnl_resp_buf *vchnl_msg_resp = (काष्ठा i40iw_virtchnl_resp_buf *)resp_buffer;

	स_रखो(resp_buffer, 0, माप(*resp_buffer));
	vchnl_msg_resp->iw_chnl_op_ctx = vchnl_msg->iw_chnl_op_ctx;
	vchnl_msg_resp->iw_chnl_buf_len = माप(resp_buffer);
	vchnl_msg_resp->iw_op_ret_code = I40IW_SUCCESS;
	*((u16 *)vchnl_msg_resp->iw_chnl_buf) = hmc_fcn;
	ret_code = dev->vchnl_अगर.vchnl_send(dev, vf_id, resp_buffer, माप(resp_buffer));
	अगर (ret_code)
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s: virt channel send failed 0x%x\n", __func__, ret_code);
पूर्ण

/**
 * vchnl_pf_send_get_pe_stats_resp - Send PE Stats to VF
 * @dev: IWARP device poपूर्णांकer
 * @vf_id: Virtual function ID associated with the message
 * @vchnl_msg: Virtual channel message buffer poपूर्णांकer
 * @hw_stats: HW Stats काष्ठा
 */

अटल व्योम vchnl_pf_send_get_pe_stats_resp(काष्ठा i40iw_sc_dev *dev,
					    u32 vf_id,
					    काष्ठा i40iw_virtchnl_op_buf *vchnl_msg,
					    काष्ठा i40iw_dev_hw_stats *hw_stats)
अणु
	क्रमागत i40iw_status_code ret_code;
	u8 resp_buffer[माप(काष्ठा i40iw_virtchnl_resp_buf) + माप(काष्ठा i40iw_dev_hw_stats) - 1];
	काष्ठा i40iw_virtchnl_resp_buf *vchnl_msg_resp = (काष्ठा i40iw_virtchnl_resp_buf *)resp_buffer;

	स_रखो(resp_buffer, 0, माप(*resp_buffer));
	vchnl_msg_resp->iw_chnl_op_ctx = vchnl_msg->iw_chnl_op_ctx;
	vchnl_msg_resp->iw_chnl_buf_len = माप(resp_buffer);
	vchnl_msg_resp->iw_op_ret_code = I40IW_SUCCESS;
	*((काष्ठा i40iw_dev_hw_stats *)vchnl_msg_resp->iw_chnl_buf) = *hw_stats;
	ret_code = dev->vchnl_अगर.vchnl_send(dev, vf_id, resp_buffer, माप(resp_buffer));
	अगर (ret_code)
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s: virt channel send failed 0x%x\n", __func__, ret_code);
पूर्ण

/**
 * vchnl_pf_send_error_resp - Send an error response to VF
 * @dev: IWARP device poपूर्णांकer
 * @vf_id: Virtual function ID associated with the message
 * @vchnl_msg: Virtual channel message buffer poपूर्णांकer
 * @op_ret_code: I40IW_ERR_* status code
 */
अटल व्योम vchnl_pf_send_error_resp(काष्ठा i40iw_sc_dev *dev, u32 vf_id,
				     काष्ठा i40iw_virtchnl_op_buf *vchnl_msg,
				     u16 op_ret_code)
अणु
	क्रमागत i40iw_status_code ret_code;
	u8 resp_buffer[माप(काष्ठा i40iw_virtchnl_resp_buf)];
	काष्ठा i40iw_virtchnl_resp_buf *vchnl_msg_resp = (काष्ठा i40iw_virtchnl_resp_buf *)resp_buffer;

	स_रखो(resp_buffer, 0, माप(resp_buffer));
	vchnl_msg_resp->iw_chnl_op_ctx = vchnl_msg->iw_chnl_op_ctx;
	vchnl_msg_resp->iw_chnl_buf_len = माप(resp_buffer);
	vchnl_msg_resp->iw_op_ret_code = (u16)op_ret_code;
	ret_code = dev->vchnl_अगर.vchnl_send(dev, vf_id, resp_buffer, माप(resp_buffer));
	अगर (ret_code)
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s: virt channel send failed 0x%x\n", __func__, ret_code);
पूर्ण

/**
 * pf_cqp_get_hmc_fcn_callback - Callback क्रम Get HMC Fcn
 * @dev: IWARP device poपूर्णांकer
 * @callback_param: unused CQP callback parameter
 * @cqe_info: CQE inक्रमmation poपूर्णांकer
 */
अटल व्योम pf_cqp_get_hmc_fcn_callback(काष्ठा i40iw_sc_dev *dev, व्योम *callback_param,
					काष्ठा i40iw_ccq_cqe_info *cqe_info)
अणु
	काष्ठा i40iw_vfdev *vf_dev = callback_param;
	काष्ठा i40iw_virt_mem vf_dev_mem;

	अगर (cqe_info->error) अणु
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "CQP Completion Error on Get HMC Function.  Maj = 0x%04x, Minor = 0x%04x\n",
			    cqe_info->maj_err_code, cqe_info->min_err_code);
		dev->vf_dev[vf_dev->iw_vf_idx] = शून्य;
		vchnl_pf_send_error_resp(dev, vf_dev->vf_id, &vf_dev->vf_msg_buffer.vchnl_msg,
					 (u16)I40IW_ERR_CQP_COMPL_ERROR);
		vf_dev_mem.va = vf_dev;
		vf_dev_mem.size = माप(*vf_dev);
		i40iw_मुक्त_virt_mem(dev->hw, &vf_dev_mem);
	पूर्ण अन्यथा अणु
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "CQP Completion Operation Return information = 0x%08x\n",
			    cqe_info->op_ret_val);
		vf_dev->pmf_index = (u16)cqe_info->op_ret_val;
		vf_dev->msg_count--;
		vchnl_pf_send_get_hmc_fcn_resp(dev,
					       vf_dev->vf_id,
					       &vf_dev->vf_msg_buffer.vchnl_msg,
					       vf_dev->pmf_index);
	पूर्ण
पूर्ण

/**
 * pf_add_hmc_obj_callback - Callback क्रम Add HMC Object
 * @work_vf_dev: poपूर्णांकer to the VF Device
 */
अटल व्योम pf_add_hmc_obj_callback(व्योम *work_vf_dev)
अणु
	काष्ठा i40iw_vfdev *vf_dev = (काष्ठा i40iw_vfdev *)work_vf_dev;
	काष्ठा i40iw_hmc_info *hmc_info = &vf_dev->hmc_info;
	काष्ठा i40iw_virtchnl_op_buf *vchnl_msg = &vf_dev->vf_msg_buffer.vchnl_msg;
	काष्ठा i40iw_hmc_create_obj_info info;
	काष्ठा i40iw_virtchnl_hmc_obj_range *add_hmc_obj;
	क्रमागत i40iw_status_code ret_code;

	अगर (!vf_dev->pf_hmc_initialized) अणु
		ret_code = i40iw_pf_init_vfhmc(vf_dev->pf_dev, (u8)vf_dev->pmf_index, शून्य);
		अगर (ret_code)
			जाओ add_out;
		vf_dev->pf_hmc_initialized = true;
	पूर्ण

	add_hmc_obj = (काष्ठा i40iw_virtchnl_hmc_obj_range *)vchnl_msg->iw_chnl_buf;

	स_रखो(&info, 0, माप(info));
	info.hmc_info = hmc_info;
	info.is_pf = false;
	info.rsrc_type = (u32)add_hmc_obj->obj_type;
	info.entry_type = (info.rsrc_type == I40IW_HMC_IW_PBLE) ? I40IW_SD_TYPE_PAGED : I40IW_SD_TYPE_सूचीECT;
	info.start_idx = add_hmc_obj->start_index;
	info.count = add_hmc_obj->obj_count;
	i40iw_debug(vf_dev->pf_dev, I40IW_DEBUG_VIRT,
		    "I40IW_VCHNL_OP_ADD_HMC_OBJ_RANGE.  Add %u type %u objects\n",
		    info.count, info.rsrc_type);
	ret_code = i40iw_sc_create_hmc_obj(vf_dev->pf_dev, &info);
	अगर (!ret_code)
		vf_dev->hmc_info.hmc_obj[add_hmc_obj->obj_type].cnt = add_hmc_obj->obj_count;
add_out:
	vf_dev->msg_count--;
	vchnl_pf_send_error_resp(vf_dev->pf_dev, vf_dev->vf_id, vchnl_msg, (u16)ret_code);
पूर्ण

/**
 * pf_del_hmc_obj_callback - Callback क्रम delete HMC Object
 * @work_vf_dev: poपूर्णांकer to the VF Device
 */
अटल व्योम pf_del_hmc_obj_callback(व्योम *work_vf_dev)
अणु
	काष्ठा i40iw_vfdev *vf_dev = (काष्ठा i40iw_vfdev *)work_vf_dev;
	काष्ठा i40iw_hmc_info *hmc_info = &vf_dev->hmc_info;
	काष्ठा i40iw_virtchnl_op_buf *vchnl_msg = &vf_dev->vf_msg_buffer.vchnl_msg;
	काष्ठा i40iw_hmc_del_obj_info info;
	काष्ठा i40iw_virtchnl_hmc_obj_range *del_hmc_obj;
	क्रमागत i40iw_status_code ret_code = I40IW_SUCCESS;

	अगर (!vf_dev->pf_hmc_initialized)
		जाओ del_out;

	del_hmc_obj = (काष्ठा i40iw_virtchnl_hmc_obj_range *)vchnl_msg->iw_chnl_buf;

	स_रखो(&info, 0, माप(info));
	info.hmc_info = hmc_info;
	info.is_pf = false;
	info.rsrc_type = (u32)del_hmc_obj->obj_type;
	info.start_idx = del_hmc_obj->start_index;
	info.count = del_hmc_obj->obj_count;
	i40iw_debug(vf_dev->pf_dev, I40IW_DEBUG_VIRT,
		    "I40IW_VCHNL_OP_DEL_HMC_OBJ_RANGE.  Delete %u type %u objects\n",
		    info.count, info.rsrc_type);
	ret_code = i40iw_sc_del_hmc_obj(vf_dev->pf_dev, &info, false);
del_out:
	vf_dev->msg_count--;
	vchnl_pf_send_error_resp(vf_dev->pf_dev, vf_dev->vf_id, vchnl_msg, (u16)ret_code);
पूर्ण

/**
 * i40iw_vf_init_pestat - Initialize stats क्रम VF
 * @dev: poपूर्णांकer to the VF Device
 * @stats: Statistics काष्ठाure poपूर्णांकer
 * @index: Stats index
 */
अटल व्योम i40iw_vf_init_pestat(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_vsi_pestat *stats, u16 index)
अणु
	stats->hw = dev->hw;
	i40iw_hw_stats_init(stats, (u8)index, false);
	spin_lock_init(&stats->lock);
पूर्ण

/**
 * i40iw_vchnl_recv_pf - Receive PF भव channel messages
 * @dev: IWARP device poपूर्णांकer
 * @vf_id: Virtual function ID associated with the message
 * @msg: Virtual channel message buffer poपूर्णांकer
 * @len: Length of the भव channels message
 */
क्रमागत i40iw_status_code i40iw_vchnl_recv_pf(काष्ठा i40iw_sc_dev *dev,
					   u32 vf_id,
					   u8 *msg,
					   u16 len)
अणु
	काष्ठा i40iw_virtchnl_op_buf *vchnl_msg = (काष्ठा i40iw_virtchnl_op_buf *)msg;
	काष्ठा i40iw_vfdev *vf_dev = शून्य;
	काष्ठा i40iw_hmc_fcn_info hmc_fcn_info;
	u16 iw_vf_idx;
	u16 first_avail_iw_vf = I40IW_MAX_PE_ENABLED_VF_COUNT;
	काष्ठा i40iw_virt_mem vf_dev_mem;
	काष्ठा i40iw_virtchnl_work_info work_info;
	काष्ठा i40iw_vsi_pestat *stats;
	क्रमागत i40iw_status_code ret_code;

	अगर (!dev || !msg || !len)
		वापस I40IW_ERR_PARAM;

	अगर (!dev->vchnl_up)
		वापस I40IW_ERR_NOT_READY;
	अगर (vchnl_msg->iw_op_code == I40IW_VCHNL_OP_GET_VER) अणु
		vchnl_pf_send_get_ver_resp(dev, vf_id, vchnl_msg);
		वापस I40IW_SUCCESS;
	पूर्ण
	क्रम (iw_vf_idx = 0; iw_vf_idx < I40IW_MAX_PE_ENABLED_VF_COUNT; iw_vf_idx++) अणु
		अगर (!dev->vf_dev[iw_vf_idx]) अणु
			अगर (first_avail_iw_vf == I40IW_MAX_PE_ENABLED_VF_COUNT)
				first_avail_iw_vf = iw_vf_idx;
			जारी;
		पूर्ण
		अगर (dev->vf_dev[iw_vf_idx]->vf_id == vf_id) अणु
			vf_dev = dev->vf_dev[iw_vf_idx];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (vf_dev) अणु
		अगर (!vf_dev->msg_count) अणु
			vf_dev->msg_count++;
		पूर्ण अन्यथा अणु
			i40iw_debug(dev, I40IW_DEBUG_VIRT,
				    "VF%u already has a channel message in progress.\n",
				    vf_id);
			वापस I40IW_SUCCESS;
		पूर्ण
	पूर्ण
	चयन (vchnl_msg->iw_op_code) अणु
	हाल I40IW_VCHNL_OP_GET_HMC_FCN:
		अगर (!vf_dev &&
		    (first_avail_iw_vf != I40IW_MAX_PE_ENABLED_VF_COUNT)) अणु
			ret_code = i40iw_allocate_virt_mem(dev->hw, &vf_dev_mem, माप(काष्ठा i40iw_vfdev) +
							   (माप(काष्ठा i40iw_hmc_obj_info) * I40IW_HMC_IW_MAX));
			अगर (!ret_code) अणु
				vf_dev = vf_dev_mem.va;
				vf_dev->stats_initialized = false;
				vf_dev->pf_dev = dev;
				vf_dev->msg_count = 1;
				vf_dev->vf_id = vf_id;
				vf_dev->iw_vf_idx = first_avail_iw_vf;
				vf_dev->pf_hmc_initialized = false;
				vf_dev->hmc_info.hmc_obj = (काष्ठा i40iw_hmc_obj_info *)(&vf_dev[1]);
				i40iw_debug(dev, I40IW_DEBUG_VIRT,
					    "vf_dev %p, hmc_info %p, hmc_obj %p\n",
					    vf_dev, &vf_dev->hmc_info, vf_dev->hmc_info.hmc_obj);
				dev->vf_dev[first_avail_iw_vf] = vf_dev;
				iw_vf_idx = first_avail_iw_vf;
			पूर्ण अन्यथा अणु
				i40iw_debug(dev, I40IW_DEBUG_VIRT,
					    "VF%u Unable to allocate a VF device structure.\n",
					    vf_id);
				vchnl_pf_send_error_resp(dev, vf_id, vchnl_msg, (u16)I40IW_ERR_NO_MEMORY);
				वापस I40IW_SUCCESS;
			पूर्ण
			स_नकल(&vf_dev->vf_msg_buffer.vchnl_msg, vchnl_msg, len);
			hmc_fcn_info.callback_fcn = pf_cqp_get_hmc_fcn_callback;
			hmc_fcn_info.vf_id = vf_id;
			hmc_fcn_info.iw_vf_idx = vf_dev->iw_vf_idx;
			hmc_fcn_info.cqp_callback_param = vf_dev;
			hmc_fcn_info.मुक्त_fcn = false;
			ret_code = i40iw_cqp_manage_hmc_fcn_cmd(dev, &hmc_fcn_info);
			अगर (ret_code)
				i40iw_debug(dev, I40IW_DEBUG_VIRT,
					    "VF%u error CQP HMC Function operation.\n",
					    vf_id);
			i40iw_vf_init_pestat(dev, &vf_dev->pestat, vf_dev->pmf_index);
			vf_dev->stats_initialized = true;
		पूर्ण अन्यथा अणु
			अगर (vf_dev) अणु
				vf_dev->msg_count--;
				vchnl_pf_send_get_hmc_fcn_resp(dev, vf_id, vchnl_msg, vf_dev->pmf_index);
			पूर्ण अन्यथा अणु
				vchnl_pf_send_error_resp(dev, vf_id, vchnl_msg,
							 (u16)I40IW_ERR_NO_MEMORY);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल I40IW_VCHNL_OP_ADD_HMC_OBJ_RANGE:
		अगर (!vf_dev)
			वापस I40IW_ERR_BAD_PTR;
		work_info.worker_vf_dev = vf_dev;
		work_info.callback_fcn = pf_add_hmc_obj_callback;
		स_नकल(&vf_dev->vf_msg_buffer.vchnl_msg, vchnl_msg, len);
		i40iw_cqp_spawn_worker(dev, &work_info, vf_dev->iw_vf_idx);
		अवरोध;
	हाल I40IW_VCHNL_OP_DEL_HMC_OBJ_RANGE:
		अगर (!vf_dev)
			वापस I40IW_ERR_BAD_PTR;
		work_info.worker_vf_dev = vf_dev;
		work_info.callback_fcn = pf_del_hmc_obj_callback;
		स_नकल(&vf_dev->vf_msg_buffer.vchnl_msg, vchnl_msg, len);
		i40iw_cqp_spawn_worker(dev, &work_info, vf_dev->iw_vf_idx);
		अवरोध;
	हाल I40IW_VCHNL_OP_GET_STATS:
		अगर (!vf_dev)
			वापस I40IW_ERR_BAD_PTR;
		stats = &vf_dev->pestat;
		i40iw_hw_stats_पढ़ो_all(stats, &stats->hw_stats);
		vf_dev->msg_count--;
		vchnl_pf_send_get_pe_stats_resp(dev, vf_id, vchnl_msg, &stats->hw_stats);
		अवरोध;
	शेष:
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "40iw_vchnl_recv_pf: Invalid OpCode 0x%x\n",
			    vchnl_msg->iw_op_code);
		vchnl_pf_send_error_resp(dev, vf_id,
					 vchnl_msg, (u16)I40IW_ERR_NOT_IMPLEMENTED);
	पूर्ण
	वापस I40IW_SUCCESS;
पूर्ण

/**
 * i40iw_vchnl_recv_vf - Receive VF भव channel messages
 * @dev: IWARP device poपूर्णांकer
 * @vf_id: Virtual function ID associated with the message
 * @msg: Virtual channel message buffer poपूर्णांकer
 * @len: Length of the भव channels message
 */
क्रमागत i40iw_status_code i40iw_vchnl_recv_vf(काष्ठा i40iw_sc_dev *dev,
					   u32 vf_id,
					   u8 *msg,
					   u16 len)
अणु
	काष्ठा i40iw_virtchnl_resp_buf *vchnl_msg_resp = (काष्ठा i40iw_virtchnl_resp_buf *)msg;
	काष्ठा i40iw_virtchnl_req *vchnl_req;

	vchnl_req = (काष्ठा i40iw_virtchnl_req *)(uपूर्णांकptr_t)vchnl_msg_resp->iw_chnl_op_ctx;
	vchnl_req->ret_code = (क्रमागत i40iw_status_code)vchnl_msg_resp->iw_op_ret_code;
	अगर (len == (माप(*vchnl_msg_resp) + vchnl_req->parm_len - 1)) अणु
		अगर (vchnl_req->parm_len && vchnl_req->parm)
			स_नकल(vchnl_req->parm, vchnl_msg_resp->iw_chnl_buf, vchnl_req->parm_len);
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s: Got response, data size %u\n", __func__,
			    vchnl_req->parm_len);
	पूर्ण अन्यथा अणु
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s: error length on response, Got %u, expected %u\n", __func__,
			    len, (u32)(माप(*vchnl_msg_resp) + vchnl_req->parm_len - 1));
	पूर्ण

	वापस I40IW_SUCCESS;
पूर्ण

/**
 * i40iw_vchnl_vf_get_ver - Request Channel version
 * @dev: IWARP device poपूर्णांकer
 * @vchnl_ver: Virtual channel message version poपूर्णांकer
 */
क्रमागत i40iw_status_code i40iw_vchnl_vf_get_ver(काष्ठा i40iw_sc_dev *dev,
					      u32 *vchnl_ver)
अणु
	काष्ठा i40iw_virtchnl_req vchnl_req;
	क्रमागत i40iw_status_code ret_code;

	अगर (!i40iw_vf_clear_to_send(dev))
		वापस I40IW_ERR_TIMEOUT;
	स_रखो(&vchnl_req, 0, माप(vchnl_req));
	vchnl_req.dev = dev;
	vchnl_req.parm = vchnl_ver;
	vchnl_req.parm_len = माप(*vchnl_ver);
	vchnl_req.vchnl_msg = &dev->vchnl_vf_msg_buf.vchnl_msg;

	ret_code = vchnl_vf_send_get_ver_req(dev, &vchnl_req);
	अगर (ret_code) अणु
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s Send message failed 0x%0x\n", __func__, ret_code);
		वापस ret_code;
	पूर्ण
	ret_code = i40iw_vf_रुको_vchnl_resp(dev);
	अगर (ret_code)
		वापस ret_code;
	अन्यथा
		वापस vchnl_req.ret_code;
पूर्ण

/**
 * i40iw_vchnl_vf_get_hmc_fcn - Request HMC Function
 * @dev: IWARP device poपूर्णांकer
 * @hmc_fcn: HMC function index poपूर्णांकer
 */
क्रमागत i40iw_status_code i40iw_vchnl_vf_get_hmc_fcn(काष्ठा i40iw_sc_dev *dev,
						  u16 *hmc_fcn)
अणु
	काष्ठा i40iw_virtchnl_req vchnl_req;
	क्रमागत i40iw_status_code ret_code;

	अगर (!i40iw_vf_clear_to_send(dev))
		वापस I40IW_ERR_TIMEOUT;
	स_रखो(&vchnl_req, 0, माप(vchnl_req));
	vchnl_req.dev = dev;
	vchnl_req.parm = hmc_fcn;
	vchnl_req.parm_len = माप(*hmc_fcn);
	vchnl_req.vchnl_msg = &dev->vchnl_vf_msg_buf.vchnl_msg;

	ret_code = vchnl_vf_send_get_hmc_fcn_req(dev, &vchnl_req);
	अगर (ret_code) अणु
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s Send message failed 0x%0x\n", __func__, ret_code);
		वापस ret_code;
	पूर्ण
	ret_code = i40iw_vf_रुको_vchnl_resp(dev);
	अगर (ret_code)
		वापस ret_code;
	अन्यथा
		वापस vchnl_req.ret_code;
पूर्ण

/**
 * i40iw_vchnl_vf_add_hmc_objs - Add HMC Object
 * @dev: IWARP device poपूर्णांकer
 * @rsrc_type: HMC Resource type
 * @start_index: Starting index of the objects to be added
 * @rsrc_count: Number of resources to be added
 */
क्रमागत i40iw_status_code i40iw_vchnl_vf_add_hmc_objs(काष्ठा i40iw_sc_dev *dev,
						   क्रमागत i40iw_hmc_rsrc_type rsrc_type,
						   u32 start_index,
						   u32 rsrc_count)
अणु
	काष्ठा i40iw_virtchnl_req vchnl_req;
	क्रमागत i40iw_status_code ret_code;

	अगर (!i40iw_vf_clear_to_send(dev))
		वापस I40IW_ERR_TIMEOUT;
	स_रखो(&vchnl_req, 0, माप(vchnl_req));
	vchnl_req.dev = dev;
	vchnl_req.vchnl_msg = &dev->vchnl_vf_msg_buf.vchnl_msg;

	ret_code = vchnl_vf_send_add_hmc_objs_req(dev,
						  &vchnl_req,
						  rsrc_type,
						  start_index,
						  rsrc_count);
	अगर (ret_code) अणु
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s Send message failed 0x%0x\n", __func__, ret_code);
		वापस ret_code;
	पूर्ण
	ret_code = i40iw_vf_रुको_vchnl_resp(dev);
	अगर (ret_code)
		वापस ret_code;
	अन्यथा
		वापस vchnl_req.ret_code;
पूर्ण

/**
 * i40iw_vchnl_vf_del_hmc_obj - del HMC obj
 * @dev: IWARP device poपूर्णांकer
 * @rsrc_type: HMC Resource type
 * @start_index: Starting index of the object to delete
 * @rsrc_count: Number of resources to be delete
 */
क्रमागत i40iw_status_code i40iw_vchnl_vf_del_hmc_obj(काष्ठा i40iw_sc_dev *dev,
						  क्रमागत i40iw_hmc_rsrc_type rsrc_type,
						  u32 start_index,
						  u32 rsrc_count)
अणु
	काष्ठा i40iw_virtchnl_req vchnl_req;
	क्रमागत i40iw_status_code ret_code;

	अगर (!i40iw_vf_clear_to_send(dev))
		वापस I40IW_ERR_TIMEOUT;
	स_रखो(&vchnl_req, 0, माप(vchnl_req));
	vchnl_req.dev = dev;
	vchnl_req.vchnl_msg = &dev->vchnl_vf_msg_buf.vchnl_msg;

	ret_code = vchnl_vf_send_del_hmc_objs_req(dev,
						  &vchnl_req,
						  rsrc_type,
						  start_index,
						  rsrc_count);
	अगर (ret_code) अणु
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s Send message failed 0x%0x\n", __func__, ret_code);
		वापस ret_code;
	पूर्ण
	ret_code = i40iw_vf_रुको_vchnl_resp(dev);
	अगर (ret_code)
		वापस ret_code;
	अन्यथा
		वापस vchnl_req.ret_code;
पूर्ण

/**
 * i40iw_vchnl_vf_get_pe_stats - Get PE stats
 * @dev: IWARP device poपूर्णांकer
 * @hw_stats: HW stats काष्ठा
 */
क्रमागत i40iw_status_code i40iw_vchnl_vf_get_pe_stats(काष्ठा i40iw_sc_dev *dev,
						   काष्ठा i40iw_dev_hw_stats *hw_stats)
अणु
	काष्ठा i40iw_virtchnl_req  vchnl_req;
	क्रमागत i40iw_status_code ret_code;

	अगर (!i40iw_vf_clear_to_send(dev))
		वापस I40IW_ERR_TIMEOUT;
	स_रखो(&vchnl_req, 0, माप(vchnl_req));
	vchnl_req.dev = dev;
	vchnl_req.parm = hw_stats;
	vchnl_req.parm_len = माप(*hw_stats);
	vchnl_req.vchnl_msg = &dev->vchnl_vf_msg_buf.vchnl_msg;

	ret_code = vchnl_vf_send_get_pe_stats_req(dev, &vchnl_req);
	अगर (ret_code) अणु
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "%s Send message failed 0x%0x\n", __func__, ret_code);
		वापस ret_code;
	पूर्ण
	ret_code = i40iw_vf_रुको_vchnl_resp(dev);
	अगर (ret_code)
		वापस ret_code;
	अन्यथा
		वापस vchnl_req.ret_code;
पूर्ण
