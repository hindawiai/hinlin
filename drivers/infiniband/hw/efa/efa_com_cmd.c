<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-2-Clause
/*
 * Copyright 2018-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#समावेश "efa_com.h"
#समावेश "efa_com_cmd.h"

व्योम efa_com_set_dma_addr(dma_addr_t addr, u32 *addr_high, u32 *addr_low)
अणु
	*addr_low = lower_32_bits(addr);
	*addr_high = upper_32_bits(addr);
पूर्ण

पूर्णांक efa_com_create_qp(काष्ठा efa_com_dev *edev,
		      काष्ठा efa_com_create_qp_params *params,
		      काष्ठा efa_com_create_qp_result *res)
अणु
	काष्ठा efa_admin_create_qp_cmd create_qp_cmd = अणुपूर्ण;
	काष्ठा efa_admin_create_qp_resp cmd_completion;
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	पूर्णांक err;

	create_qp_cmd.aq_common_desc.opcode = EFA_ADMIN_CREATE_QP;

	create_qp_cmd.pd = params->pd;
	create_qp_cmd.qp_type = params->qp_type;
	create_qp_cmd.rq_base_addr = params->rq_base_addr;
	create_qp_cmd.send_cq_idx = params->send_cq_idx;
	create_qp_cmd.recv_cq_idx = params->recv_cq_idx;
	create_qp_cmd.qp_alloc_size.send_queue_ring_size =
		params->sq_ring_size_in_bytes;
	create_qp_cmd.qp_alloc_size.send_queue_depth =
			params->sq_depth;
	create_qp_cmd.qp_alloc_size.recv_queue_ring_size =
			params->rq_ring_size_in_bytes;
	create_qp_cmd.qp_alloc_size.recv_queue_depth =
			params->rq_depth;
	create_qp_cmd.uar = params->uarn;

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&create_qp_cmd,
			       माप(create_qp_cmd),
			       (काष्ठा efa_admin_acq_entry *)&cmd_completion,
			       माप(cmd_completion));
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to create qp [%d]\n", err);
		वापस err;
	पूर्ण

	res->qp_handle = cmd_completion.qp_handle;
	res->qp_num = cmd_completion.qp_num;
	res->sq_db_offset = cmd_completion.sq_db_offset;
	res->rq_db_offset = cmd_completion.rq_db_offset;
	res->llq_descriptors_offset = cmd_completion.llq_descriptors_offset;
	res->send_sub_cq_idx = cmd_completion.send_sub_cq_idx;
	res->recv_sub_cq_idx = cmd_completion.recv_sub_cq_idx;

	वापस 0;
पूर्ण

पूर्णांक efa_com_modअगरy_qp(काष्ठा efa_com_dev *edev,
		      काष्ठा efa_com_modअगरy_qp_params *params)
अणु
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	काष्ठा efa_admin_modअगरy_qp_cmd cmd = अणुपूर्ण;
	काष्ठा efa_admin_modअगरy_qp_resp resp;
	पूर्णांक err;

	cmd.aq_common_desc.opcode = EFA_ADMIN_MODIFY_QP;
	cmd.modअगरy_mask = params->modअगरy_mask;
	cmd.qp_handle = params->qp_handle;
	cmd.qp_state = params->qp_state;
	cmd.cur_qp_state = params->cur_qp_state;
	cmd.qkey = params->qkey;
	cmd.sq_psn = params->sq_psn;
	cmd.sq_drained_async_notअगरy = params->sq_drained_async_notअगरy;
	cmd.rnr_retry = params->rnr_retry;

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&cmd,
			       माप(cmd),
			       (काष्ठा efa_admin_acq_entry *)&resp,
			       माप(resp));
	अगर (err) अणु
		ibdev_err_ratelimited(
			edev->efa_dev,
			"Failed to modify qp-%u modify_mask[%#x] [%d]\n",
			cmd.qp_handle, cmd.modअगरy_mask, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक efa_com_query_qp(काष्ठा efa_com_dev *edev,
		     काष्ठा efa_com_query_qp_params *params,
		     काष्ठा efa_com_query_qp_result *result)
अणु
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	काष्ठा efa_admin_query_qp_cmd cmd = अणुपूर्ण;
	काष्ठा efa_admin_query_qp_resp resp;
	पूर्णांक err;

	cmd.aq_common_desc.opcode = EFA_ADMIN_QUERY_QP;
	cmd.qp_handle = params->qp_handle;

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&cmd,
			       माप(cmd),
			       (काष्ठा efa_admin_acq_entry *)&resp,
			       माप(resp));
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to query qp-%u [%d]\n",
				      cmd.qp_handle, err);
		वापस err;
	पूर्ण

	result->qp_state = resp.qp_state;
	result->qkey = resp.qkey;
	result->sq_draining = resp.sq_draining;
	result->sq_psn = resp.sq_psn;
	result->rnr_retry = resp.rnr_retry;

	वापस 0;
पूर्ण

पूर्णांक efa_com_destroy_qp(काष्ठा efa_com_dev *edev,
		       काष्ठा efa_com_destroy_qp_params *params)
अणु
	काष्ठा efa_admin_destroy_qp_resp cmd_completion;
	काष्ठा efa_admin_destroy_qp_cmd qp_cmd = अणुपूर्ण;
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	पूर्णांक err;

	qp_cmd.aq_common_desc.opcode = EFA_ADMIN_DESTROY_QP;
	qp_cmd.qp_handle = params->qp_handle;

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&qp_cmd,
			       माप(qp_cmd),
			       (काष्ठा efa_admin_acq_entry *)&cmd_completion,
			       माप(cmd_completion));
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to destroy qp-%u [%d]\n",
				      qp_cmd.qp_handle, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक efa_com_create_cq(काष्ठा efa_com_dev *edev,
		      काष्ठा efa_com_create_cq_params *params,
		      काष्ठा efa_com_create_cq_result *result)
अणु
	काष्ठा efa_admin_create_cq_resp cmd_completion;
	काष्ठा efa_admin_create_cq_cmd create_cmd = अणुपूर्ण;
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	पूर्णांक err;

	create_cmd.aq_common_desc.opcode = EFA_ADMIN_CREATE_CQ;
	EFA_SET(&create_cmd.cq_caps_2,
		EFA_ADMIN_CREATE_CQ_CMD_CQ_ENTRY_SIZE_WORDS,
		params->entry_size_in_bytes / 4);
	create_cmd.cq_depth = params->cq_depth;
	create_cmd.num_sub_cqs = params->num_sub_cqs;
	create_cmd.uar = params->uarn;

	efa_com_set_dma_addr(params->dma_addr,
			     &create_cmd.cq_ba.mem_addr_high,
			     &create_cmd.cq_ba.mem_addr_low);

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&create_cmd,
			       माप(create_cmd),
			       (काष्ठा efa_admin_acq_entry *)&cmd_completion,
			       माप(cmd_completion));
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to create cq[%d]\n", err);
		वापस err;
	पूर्ण

	result->cq_idx = cmd_completion.cq_idx;
	result->actual_depth = params->cq_depth;

	वापस 0;
पूर्ण

पूर्णांक efa_com_destroy_cq(काष्ठा efa_com_dev *edev,
		       काष्ठा efa_com_destroy_cq_params *params)
अणु
	काष्ठा efa_admin_destroy_cq_cmd destroy_cmd = अणुपूर्ण;
	काष्ठा efa_admin_destroy_cq_resp destroy_resp;
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	पूर्णांक err;

	destroy_cmd.cq_idx = params->cq_idx;
	destroy_cmd.aq_common_desc.opcode = EFA_ADMIN_DESTROY_CQ;

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&destroy_cmd,
			       माप(destroy_cmd),
			       (काष्ठा efa_admin_acq_entry *)&destroy_resp,
			       माप(destroy_resp));

	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to destroy CQ-%u [%d]\n",
				      params->cq_idx, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक efa_com_रेजिस्टर_mr(काष्ठा efa_com_dev *edev,
			काष्ठा efa_com_reg_mr_params *params,
			काष्ठा efa_com_reg_mr_result *result)
अणु
	काष्ठा efa_admin_reg_mr_resp cmd_completion;
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	काष्ठा efa_admin_reg_mr_cmd mr_cmd = अणुपूर्ण;
	पूर्णांक err;

	mr_cmd.aq_common_desc.opcode = EFA_ADMIN_REG_MR;
	mr_cmd.pd = params->pd;
	mr_cmd.mr_length = params->mr_length_in_bytes;
	EFA_SET(&mr_cmd.flags, EFA_ADMIN_REG_MR_CMD_PHYS_PAGE_SIZE_SHIFT,
		params->page_shअगरt);
	mr_cmd.iova = params->iova;
	mr_cmd.permissions = params->permissions;

	अगर (params->अंतरभूत_pbl) अणु
		स_नकल(mr_cmd.pbl.अंतरभूत_pbl_array,
		       params->pbl.अंतरभूत_pbl_array,
		       माप(mr_cmd.pbl.अंतरभूत_pbl_array));
	पूर्ण अन्यथा अणु
		mr_cmd.pbl.pbl.length = params->pbl.pbl.length;
		mr_cmd.pbl.pbl.address.mem_addr_low =
			params->pbl.pbl.address.mem_addr_low;
		mr_cmd.pbl.pbl.address.mem_addr_high =
			params->pbl.pbl.address.mem_addr_high;
		EFA_SET(&mr_cmd.aq_common_desc.flags,
			EFA_ADMIN_AQ_COMMON_DESC_CTRL_DATA, 1);
		अगर (params->indirect)
			EFA_SET(&mr_cmd.aq_common_desc.flags,
				EFA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INसूचीECT, 1);
	पूर्ण

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&mr_cmd,
			       माप(mr_cmd),
			       (काष्ठा efa_admin_acq_entry *)&cmd_completion,
			       माप(cmd_completion));
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to register mr [%d]\n", err);
		वापस err;
	पूर्ण

	result->l_key = cmd_completion.l_key;
	result->r_key = cmd_completion.r_key;

	वापस 0;
पूर्ण

पूर्णांक efa_com_dereg_mr(काष्ठा efa_com_dev *edev,
		     काष्ठा efa_com_dereg_mr_params *params)
अणु
	काष्ठा efa_admin_dereg_mr_resp cmd_completion;
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	काष्ठा efa_admin_dereg_mr_cmd mr_cmd = अणुपूर्ण;
	पूर्णांक err;

	mr_cmd.aq_common_desc.opcode = EFA_ADMIN_DEREG_MR;
	mr_cmd.l_key = params->l_key;

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&mr_cmd,
			       माप(mr_cmd),
			       (काष्ठा efa_admin_acq_entry *)&cmd_completion,
			       माप(cmd_completion));
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to de-register mr(lkey-%u) [%d]\n",
				      mr_cmd.l_key, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक efa_com_create_ah(काष्ठा efa_com_dev *edev,
		      काष्ठा efa_com_create_ah_params *params,
		      काष्ठा efa_com_create_ah_result *result)
अणु
	काष्ठा efa_admin_create_ah_resp cmd_completion;
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	काष्ठा efa_admin_create_ah_cmd ah_cmd = अणुपूर्ण;
	पूर्णांक err;

	ah_cmd.aq_common_desc.opcode = EFA_ADMIN_CREATE_AH;

	स_नकल(ah_cmd.dest_addr, params->dest_addr, माप(ah_cmd.dest_addr));
	ah_cmd.pd = params->pdn;

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&ah_cmd,
			       माप(ah_cmd),
			       (काष्ठा efa_admin_acq_entry *)&cmd_completion,
			       माप(cmd_completion));
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to create ah for %pI6 [%d]\n",
				      ah_cmd.dest_addr, err);
		वापस err;
	पूर्ण

	result->ah = cmd_completion.ah;

	वापस 0;
पूर्ण

पूर्णांक efa_com_destroy_ah(काष्ठा efa_com_dev *edev,
		       काष्ठा efa_com_destroy_ah_params *params)
अणु
	काष्ठा efa_admin_destroy_ah_resp cmd_completion;
	काष्ठा efa_admin_destroy_ah_cmd ah_cmd = अणुपूर्ण;
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	पूर्णांक err;

	ah_cmd.aq_common_desc.opcode = EFA_ADMIN_DESTROY_AH;
	ah_cmd.ah = params->ah;
	ah_cmd.pd = params->pdn;

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&ah_cmd,
			       माप(ah_cmd),
			       (काष्ठा efa_admin_acq_entry *)&cmd_completion,
			       माप(cmd_completion));
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to destroy ah-%d pd-%d [%d]\n",
				      ah_cmd.ah, ah_cmd.pd, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

bool
efa_com_check_supported_feature_id(काष्ठा efa_com_dev *edev,
				   क्रमागत efa_admin_aq_feature_id feature_id)
अणु
	u32 feature_mask = 1 << feature_id;

	/* Device attributes is always supported */
	अगर (feature_id != EFA_ADMIN_DEVICE_ATTR &&
	    !(edev->supported_features & feature_mask))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक efa_com_get_feature_ex(काष्ठा efa_com_dev *edev,
				  काष्ठा efa_admin_get_feature_resp *get_resp,
				  क्रमागत efa_admin_aq_feature_id feature_id,
				  dma_addr_t control_buf_dma_addr,
				  u32 control_buff_size)
अणु
	काष्ठा efa_admin_get_feature_cmd get_cmd = अणुपूर्ण;
	काष्ठा efa_com_admin_queue *aq;
	पूर्णांक err;

	अगर (!efa_com_check_supported_feature_id(edev, feature_id)) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Feature %d isn't supported\n",
				      feature_id);
		वापस -EOPNOTSUPP;
	पूर्ण

	aq = &edev->aq;

	get_cmd.aq_common_descriptor.opcode = EFA_ADMIN_GET_FEATURE;

	अगर (control_buff_size)
		EFA_SET(&get_cmd.aq_common_descriptor.flags,
			EFA_ADMIN_AQ_COMMON_DESC_CTRL_DATA, 1);

	efa_com_set_dma_addr(control_buf_dma_addr,
			     &get_cmd.control_buffer.address.mem_addr_high,
			     &get_cmd.control_buffer.address.mem_addr_low);

	get_cmd.control_buffer.length = control_buff_size;
	get_cmd.feature_common.feature_id = feature_id;
	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)
			       &get_cmd,
			       माप(get_cmd),
			       (काष्ठा efa_admin_acq_entry *)
			       get_resp,
			       माप(*get_resp));

	अगर (err) अणु
		ibdev_err_ratelimited(
			edev->efa_dev,
			"Failed to submit get_feature command %d [%d]\n",
			feature_id, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक efa_com_get_feature(काष्ठा efa_com_dev *edev,
			       काष्ठा efa_admin_get_feature_resp *get_resp,
			       क्रमागत efa_admin_aq_feature_id feature_id)
अणु
	वापस efa_com_get_feature_ex(edev, get_resp, feature_id, 0, 0);
पूर्ण

पूर्णांक efa_com_get_device_attr(काष्ठा efa_com_dev *edev,
			    काष्ठा efa_com_get_device_attr_result *result)
अणु
	काष्ठा efa_admin_get_feature_resp resp;
	पूर्णांक err;

	err = efa_com_get_feature(edev, &resp, EFA_ADMIN_DEVICE_ATTR);
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to get device attributes %d\n",
				      err);
		वापस err;
	पूर्ण

	result->page_size_cap = resp.u.device_attr.page_size_cap;
	result->fw_version = resp.u.device_attr.fw_version;
	result->admin_api_version = resp.u.device_attr.admin_api_version;
	result->device_version = resp.u.device_attr.device_version;
	result->supported_features = resp.u.device_attr.supported_features;
	result->phys_addr_width = resp.u.device_attr.phys_addr_width;
	result->virt_addr_width = resp.u.device_attr.virt_addr_width;
	result->db_bar = resp.u.device_attr.db_bar;
	result->max_rdma_size = resp.u.device_attr.max_rdma_size;
	result->device_caps = resp.u.device_attr.device_caps;

	अगर (result->admin_api_version < 1) अणु
		ibdev_err_ratelimited(
			edev->efa_dev,
			"Failed to get device attr api version [%u < 1]\n",
			result->admin_api_version);
		वापस -EINVAL;
	पूर्ण

	edev->supported_features = resp.u.device_attr.supported_features;
	err = efa_com_get_feature(edev, &resp,
				  EFA_ADMIN_QUEUE_ATTR);
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to get queue attributes %d\n",
				      err);
		वापस err;
	पूर्ण

	result->max_qp = resp.u.queue_attr.max_qp;
	result->max_sq_depth = resp.u.queue_attr.max_sq_depth;
	result->max_rq_depth = resp.u.queue_attr.max_rq_depth;
	result->max_cq = resp.u.queue_attr.max_cq;
	result->max_cq_depth = resp.u.queue_attr.max_cq_depth;
	result->अंतरभूत_buf_size = resp.u.queue_attr.अंतरभूत_buf_size;
	result->max_sq_sge = resp.u.queue_attr.max_wr_send_sges;
	result->max_rq_sge = resp.u.queue_attr.max_wr_recv_sges;
	result->max_mr = resp.u.queue_attr.max_mr;
	result->max_mr_pages = resp.u.queue_attr.max_mr_pages;
	result->max_pd = resp.u.queue_attr.max_pd;
	result->max_ah = resp.u.queue_attr.max_ah;
	result->max_llq_size = resp.u.queue_attr.max_llq_size;
	result->sub_cqs_per_cq = resp.u.queue_attr.sub_cqs_per_cq;
	result->max_wr_rdma_sge = resp.u.queue_attr.max_wr_rdma_sges;
	result->max_tx_batch = resp.u.queue_attr.max_tx_batch;
	result->min_sq_depth = resp.u.queue_attr.min_sq_depth;

	err = efa_com_get_feature(edev, &resp, EFA_ADMIN_NETWORK_ATTR);
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to get network attributes %d\n",
				      err);
		वापस err;
	पूर्ण

	स_नकल(result->addr, resp.u.network_attr.addr,
	       माप(resp.u.network_attr.addr));
	result->mtu = resp.u.network_attr.mtu;

	वापस 0;
पूर्ण

पूर्णांक efa_com_get_hw_hपूर्णांकs(काष्ठा efa_com_dev *edev,
			 काष्ठा efa_com_get_hw_hपूर्णांकs_result *result)
अणु
	काष्ठा efa_admin_get_feature_resp resp;
	पूर्णांक err;

	err = efa_com_get_feature(edev, &resp, EFA_ADMIN_HW_HINTS);
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to get hw hints %d\n", err);
		वापस err;
	पूर्ण

	result->admin_completion_समयout = resp.u.hw_hपूर्णांकs.admin_completion_समयout;
	result->driver_watchकरोg_समयout = resp.u.hw_hपूर्णांकs.driver_watchकरोg_समयout;
	result->mmio_पढ़ो_समयout = resp.u.hw_hपूर्णांकs.mmio_पढ़ो_समयout;
	result->poll_पूर्णांकerval = resp.u.hw_hपूर्णांकs.poll_पूर्णांकerval;

	वापस 0;
पूर्ण

पूर्णांक efa_com_set_feature_ex(काष्ठा efa_com_dev *edev,
			   काष्ठा efa_admin_set_feature_resp *set_resp,
			   काष्ठा efa_admin_set_feature_cmd *set_cmd,
			   क्रमागत efa_admin_aq_feature_id feature_id,
			   dma_addr_t control_buf_dma_addr,
			   u32 control_buff_size)
अणु
	काष्ठा efa_com_admin_queue *aq;
	पूर्णांक err;

	अगर (!efa_com_check_supported_feature_id(edev, feature_id)) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Feature %d isn't supported\n",
				      feature_id);
		वापस -EOPNOTSUPP;
	पूर्ण

	aq = &edev->aq;

	set_cmd->aq_common_descriptor.opcode = EFA_ADMIN_SET_FEATURE;
	अगर (control_buff_size) अणु
		set_cmd->aq_common_descriptor.flags = 0;
		EFA_SET(&set_cmd->aq_common_descriptor.flags,
			EFA_ADMIN_AQ_COMMON_DESC_CTRL_DATA, 1);
		efa_com_set_dma_addr(control_buf_dma_addr,
				     &set_cmd->control_buffer.address.mem_addr_high,
				     &set_cmd->control_buffer.address.mem_addr_low);
	पूर्ण

	set_cmd->control_buffer.length = control_buff_size;
	set_cmd->feature_common.feature_id = feature_id;
	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)set_cmd,
			       माप(*set_cmd),
			       (काष्ठा efa_admin_acq_entry *)set_resp,
			       माप(*set_resp));

	अगर (err) अणु
		ibdev_err_ratelimited(
			edev->efa_dev,
			"Failed to submit set_feature command %d error: %d\n",
			feature_id, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक efa_com_set_feature(काष्ठा efa_com_dev *edev,
			       काष्ठा efa_admin_set_feature_resp *set_resp,
			       काष्ठा efa_admin_set_feature_cmd *set_cmd,
			       क्रमागत efa_admin_aq_feature_id feature_id)
अणु
	वापस efa_com_set_feature_ex(edev, set_resp, set_cmd, feature_id,
				      0, 0);
पूर्ण

पूर्णांक efa_com_set_aenq_config(काष्ठा efa_com_dev *edev, u32 groups)
अणु
	काष्ठा efa_admin_get_feature_resp get_resp;
	काष्ठा efa_admin_set_feature_resp set_resp;
	काष्ठा efa_admin_set_feature_cmd cmd = अणुपूर्ण;
	पूर्णांक err;

	ibdev_dbg(edev->efa_dev, "Configuring aenq with groups[%#x]\n", groups);

	err = efa_com_get_feature(edev, &get_resp, EFA_ADMIN_AENQ_CONFIG);
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to get aenq attributes: %d\n",
				      err);
		वापस err;
	पूर्ण

	ibdev_dbg(edev->efa_dev,
		  "Get aenq groups: supported[%#x] enabled[%#x]\n",
		  get_resp.u.aenq.supported_groups,
		  get_resp.u.aenq.enabled_groups);

	अगर ((get_resp.u.aenq.supported_groups & groups) != groups) अणु
		ibdev_err_ratelimited(
			edev->efa_dev,
			"Trying to set unsupported aenq groups[%#x] supported[%#x]\n",
			groups, get_resp.u.aenq.supported_groups);
		वापस -EOPNOTSUPP;
	पूर्ण

	cmd.u.aenq.enabled_groups = groups;
	err = efa_com_set_feature(edev, &set_resp, &cmd,
				  EFA_ADMIN_AENQ_CONFIG);
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to set aenq attributes: %d\n",
				      err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक efa_com_alloc_pd(काष्ठा efa_com_dev *edev,
		     काष्ठा efa_com_alloc_pd_result *result)
अणु
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	काष्ठा efa_admin_alloc_pd_cmd cmd = अणुपूर्ण;
	काष्ठा efa_admin_alloc_pd_resp resp;
	पूर्णांक err;

	cmd.aq_common_descriptor.opcode = EFA_ADMIN_ALLOC_PD;

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&cmd,
			       माप(cmd),
			       (काष्ठा efa_admin_acq_entry *)&resp,
			       माप(resp));
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to allocate pd[%d]\n", err);
		वापस err;
	पूर्ण

	result->pdn = resp.pd;

	वापस 0;
पूर्ण

पूर्णांक efa_com_dealloc_pd(काष्ठा efa_com_dev *edev,
		       काष्ठा efa_com_dealloc_pd_params *params)
अणु
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	काष्ठा efa_admin_dealloc_pd_cmd cmd = अणुपूर्ण;
	काष्ठा efa_admin_dealloc_pd_resp resp;
	पूर्णांक err;

	cmd.aq_common_descriptor.opcode = EFA_ADMIN_DEALLOC_PD;
	cmd.pd = params->pdn;

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&cmd,
			       माप(cmd),
			       (काष्ठा efa_admin_acq_entry *)&resp,
			       माप(resp));
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to deallocate pd-%u [%d]\n",
				      cmd.pd, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक efa_com_alloc_uar(काष्ठा efa_com_dev *edev,
		      काष्ठा efa_com_alloc_uar_result *result)
अणु
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	काष्ठा efa_admin_alloc_uar_cmd cmd = अणुपूर्ण;
	काष्ठा efa_admin_alloc_uar_resp resp;
	पूर्णांक err;

	cmd.aq_common_descriptor.opcode = EFA_ADMIN_ALLOC_UAR;

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&cmd,
			       माप(cmd),
			       (काष्ठा efa_admin_acq_entry *)&resp,
			       माप(resp));
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to allocate uar[%d]\n", err);
		वापस err;
	पूर्ण

	result->uarn = resp.uar;

	वापस 0;
पूर्ण

पूर्णांक efa_com_dealloc_uar(काष्ठा efa_com_dev *edev,
			काष्ठा efa_com_dealloc_uar_params *params)
अणु
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	काष्ठा efa_admin_dealloc_uar_cmd cmd = अणुपूर्ण;
	काष्ठा efa_admin_dealloc_uar_resp resp;
	पूर्णांक err;

	cmd.aq_common_descriptor.opcode = EFA_ADMIN_DEALLOC_UAR;
	cmd.uar = params->uarn;

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&cmd,
			       माप(cmd),
			       (काष्ठा efa_admin_acq_entry *)&resp,
			       माप(resp));
	अगर (err) अणु
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to deallocate uar-%u [%d]\n",
				      cmd.uar, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक efa_com_get_stats(काष्ठा efa_com_dev *edev,
		      काष्ठा efa_com_get_stats_params *params,
		      जोड़ efa_com_get_stats_result *result)
अणु
	काष्ठा efa_com_admin_queue *aq = &edev->aq;
	काष्ठा efa_admin_aq_get_stats_cmd cmd = अणुपूर्ण;
	काष्ठा efa_admin_acq_get_stats_resp resp;
	पूर्णांक err;

	cmd.aq_common_descriptor.opcode = EFA_ADMIN_GET_STATS;
	cmd.type = params->type;
	cmd.scope = params->scope;
	cmd.scope_modअगरier = params->scope_modअगरier;

	err = efa_com_cmd_exec(aq,
			       (काष्ठा efa_admin_aq_entry *)&cmd,
			       माप(cmd),
			       (काष्ठा efa_admin_acq_entry *)&resp,
			       माप(resp));
	अगर (err) अणु
		ibdev_err_ratelimited(
			edev->efa_dev,
			"Failed to get stats type-%u scope-%u.%u [%d]\n",
			cmd.type, cmd.scope, cmd.scope_modअगरier, err);
		वापस err;
	पूर्ण

	चयन (cmd.type) अणु
	हाल EFA_ADMIN_GET_STATS_TYPE_BASIC:
		result->basic_stats.tx_bytes = resp.u.basic_stats.tx_bytes;
		result->basic_stats.tx_pkts = resp.u.basic_stats.tx_pkts;
		result->basic_stats.rx_bytes = resp.u.basic_stats.rx_bytes;
		result->basic_stats.rx_pkts = resp.u.basic_stats.rx_pkts;
		result->basic_stats.rx_drops = resp.u.basic_stats.rx_drops;
		अवरोध;
	हाल EFA_ADMIN_GET_STATS_TYPE_MESSAGES:
		result->messages_stats.send_bytes = resp.u.messages_stats.send_bytes;
		result->messages_stats.send_wrs = resp.u.messages_stats.send_wrs;
		result->messages_stats.recv_bytes = resp.u.messages_stats.recv_bytes;
		result->messages_stats.recv_wrs = resp.u.messages_stats.recv_wrs;
		अवरोध;
	हाल EFA_ADMIN_GET_STATS_TYPE_RDMA_READ:
		result->rdma_पढ़ो_stats.पढ़ो_wrs = resp.u.rdma_पढ़ो_stats.पढ़ो_wrs;
		result->rdma_पढ़ो_stats.पढ़ो_bytes = resp.u.rdma_पढ़ो_stats.पढ़ो_bytes;
		result->rdma_पढ़ो_stats.पढ़ो_wr_err = resp.u.rdma_पढ़ो_stats.पढ़ो_wr_err;
		result->rdma_पढ़ो_stats.पढ़ो_resp_bytes = resp.u.rdma_पढ़ो_stats.पढ़ो_resp_bytes;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
