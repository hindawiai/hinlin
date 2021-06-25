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

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/अगर_vlan.h>

#समावेश "i40iw.h"

/**
 * i40iw_initialize_hw_resources - initialize hw resource during खोलो
 * @iwdev: iwarp device
 */
u32 i40iw_initialize_hw_resources(काष्ठा i40iw_device *iwdev)
अणु
	अचिन्हित दीर्घ num_pds;
	u32 resources_size;
	u32 max_mr;
	u32 max_qp;
	u32 max_cq;
	u32 arp_table_size;
	u32 mrdrvbits;
	व्योम *resource_ptr;

	max_qp = iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_QP].cnt;
	max_cq = iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_CQ].cnt;
	max_mr = iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_MR].cnt;
	arp_table_size = iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_ARP].cnt;
	iwdev->max_cqe = 0xFFFFF;
	num_pds = I40IW_MAX_PDS;
	resources_size = माप(काष्ठा i40iw_arp_entry) * arp_table_size;
	resources_size += माप(अचिन्हित दीर्घ) * BITS_TO_LONGS(max_qp);
	resources_size += माप(अचिन्हित दीर्घ) * BITS_TO_LONGS(max_mr);
	resources_size += माप(अचिन्हित दीर्घ) * BITS_TO_LONGS(max_cq);
	resources_size += माप(अचिन्हित दीर्घ) * BITS_TO_LONGS(num_pds);
	resources_size += माप(अचिन्हित दीर्घ) * BITS_TO_LONGS(arp_table_size);
	resources_size += माप(काष्ठा i40iw_qp **) * max_qp;
	iwdev->mem_resources = kzalloc(resources_size, GFP_KERNEL);

	अगर (!iwdev->mem_resources)
		वापस -ENOMEM;

	iwdev->max_qp = max_qp;
	iwdev->max_mr = max_mr;
	iwdev->max_cq = max_cq;
	iwdev->max_pd = num_pds;
	iwdev->arp_table_size = arp_table_size;
	iwdev->arp_table = (काष्ठा i40iw_arp_entry *)iwdev->mem_resources;
	resource_ptr = iwdev->mem_resources + (माप(काष्ठा i40iw_arp_entry) * arp_table_size);

	iwdev->device_cap_flags = IB_DEVICE_LOCAL_DMA_LKEY |
	    IB_DEVICE_MEM_WINDOW | IB_DEVICE_MEM_MGT_EXTENSIONS;

	iwdev->allocated_qps = resource_ptr;
	iwdev->allocated_cqs = &iwdev->allocated_qps[BITS_TO_LONGS(max_qp)];
	iwdev->allocated_mrs = &iwdev->allocated_cqs[BITS_TO_LONGS(max_cq)];
	iwdev->allocated_pds = &iwdev->allocated_mrs[BITS_TO_LONGS(max_mr)];
	iwdev->allocated_arps = &iwdev->allocated_pds[BITS_TO_LONGS(num_pds)];
	iwdev->qp_table = (काष्ठा i40iw_qp **)(&iwdev->allocated_arps[BITS_TO_LONGS(arp_table_size)]);
	set_bit(0, iwdev->allocated_mrs);
	set_bit(0, iwdev->allocated_qps);
	set_bit(0, iwdev->allocated_cqs);
	set_bit(0, iwdev->allocated_pds);
	set_bit(0, iwdev->allocated_arps);

	/* Following क्रम ILQ/IEQ */
	set_bit(1, iwdev->allocated_qps);
	set_bit(1, iwdev->allocated_cqs);
	set_bit(1, iwdev->allocated_pds);
	set_bit(2, iwdev->allocated_cqs);
	set_bit(2, iwdev->allocated_pds);

	spin_lock_init(&iwdev->resource_lock);
	spin_lock_init(&iwdev->qptable_lock);
	/* stag index mask has a minimum of 14 bits */
	mrdrvbits = 24 - max(get_count_order(iwdev->max_mr), 14);
	iwdev->mr_stagmask = ~(((1 << mrdrvbits) - 1) << (32 - mrdrvbits));
	वापस 0;
पूर्ण

/**
 * i40iw_cqp_ce_handler - handle cqp completions
 * @iwdev: iwarp device
 * @arm: flag to arm after completions
 * @cq: cq क्रम cqp completions
 */
अटल व्योम i40iw_cqp_ce_handler(काष्ठा i40iw_device *iwdev, काष्ठा i40iw_sc_cq *cq, bool arm)
अणु
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	u32 cqe_count = 0;
	काष्ठा i40iw_ccq_cqe_info info;
	पूर्णांक ret;

	करो अणु
		स_रखो(&info, 0, माप(info));
		ret = dev->ccq_ops->ccq_get_cqe_info(cq, &info);
		अगर (ret)
			अवरोध;
		cqp_request = (काष्ठा i40iw_cqp_request *)(अचिन्हित दीर्घ)info.scratch;
		अगर (info.error)
			i40iw_pr_err("opcode = 0x%x maj_err_code = 0x%x min_err_code = 0x%x\n",
				     info.op_code, info.maj_err_code, info.min_err_code);
		अगर (cqp_request) अणु
			cqp_request->compl_info.maj_err_code = info.maj_err_code;
			cqp_request->compl_info.min_err_code = info.min_err_code;
			cqp_request->compl_info.op_ret_val = info.op_ret_val;
			cqp_request->compl_info.error = info.error;

			अगर (cqp_request->रुकोing) अणु
				cqp_request->request_करोne = true;
				wake_up(&cqp_request->रुकोq);
				i40iw_put_cqp_request(&iwdev->cqp, cqp_request);
			पूर्ण अन्यथा अणु
				अगर (cqp_request->callback_fcn)
					cqp_request->callback_fcn(cqp_request, 1);
				i40iw_put_cqp_request(&iwdev->cqp, cqp_request);
			पूर्ण
		पूर्ण

		cqe_count++;
	पूर्ण जबतक (1);

	अगर (arm && cqe_count) अणु
		i40iw_process_bh(dev);
		dev->ccq_ops->ccq_arm(cq);
	पूर्ण
पूर्ण

/**
 * i40iw_iwarp_ce_handler - handle iwarp completions
 * @iwdev: iwarp device
 * @iwcq: iwarp cq receiving event
 */
अटल व्योम i40iw_iwarp_ce_handler(काष्ठा i40iw_device *iwdev,
				   काष्ठा i40iw_sc_cq *iwcq)
अणु
	काष्ठा i40iw_cq *i40iwcq = iwcq->back_cq;

	अगर (i40iwcq->ibcq.comp_handler)
		i40iwcq->ibcq.comp_handler(&i40iwcq->ibcq,
					   i40iwcq->ibcq.cq_context);
पूर्ण

/**
 * i40iw_puda_ce_handler - handle puda completion events
 * @iwdev: iwarp device
 * @cq: puda completion q क्रम event
 */
अटल व्योम i40iw_puda_ce_handler(काष्ठा i40iw_device *iwdev,
				  काष्ठा i40iw_sc_cq *cq)
अणु
	काष्ठा i40iw_sc_dev *dev = (काष्ठा i40iw_sc_dev *)&iwdev->sc_dev;
	क्रमागत i40iw_status_code status;
	u32 compl_error;

	करो अणु
		status = i40iw_puda_poll_completion(dev, cq, &compl_error);
		अगर (status == I40IW_ERR_QUEUE_EMPTY)
			अवरोध;
		अगर (status) अणु
			i40iw_pr_err("puda  status = %d\n", status);
			अवरोध;
		पूर्ण
		अगर (compl_error) अणु
			i40iw_pr_err("puda compl_err  =0x%x\n", compl_error);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);

	dev->ccq_ops->ccq_arm(cq);
पूर्ण

/**
 * i40iw_process_ceq - handle ceq क्रम completions
 * @iwdev: iwarp device
 * @ceq: ceq having cq क्रम completion
 */
व्योम i40iw_process_ceq(काष्ठा i40iw_device *iwdev, काष्ठा i40iw_ceq *ceq)
अणु
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_sc_ceq *sc_ceq;
	काष्ठा i40iw_sc_cq *cq;
	bool arm = true;

	sc_ceq = &ceq->sc_ceq;
	करो अणु
		cq = dev->ceq_ops->process_ceq(dev, sc_ceq);
		अगर (!cq)
			अवरोध;

		अगर (cq->cq_type == I40IW_CQ_TYPE_CQP)
			i40iw_cqp_ce_handler(iwdev, cq, arm);
		अन्यथा अगर (cq->cq_type == I40IW_CQ_TYPE_IWARP)
			i40iw_iwarp_ce_handler(iwdev, cq);
		अन्यथा अगर ((cq->cq_type == I40IW_CQ_TYPE_ILQ) ||
			 (cq->cq_type == I40IW_CQ_TYPE_IEQ))
			i40iw_puda_ce_handler(iwdev, cq);
	पूर्ण जबतक (1);
पूर्ण

/**
 * i40iw_next_iw_state - modअगरy qp state
 * @iwqp: iwarp qp to modअगरy
 * @state: next state क्रम qp
 * @del_hash: del hash
 * @term: term message
 * @termlen: length of term message
 */
व्योम i40iw_next_iw_state(काष्ठा i40iw_qp *iwqp,
			 u8 state,
			 u8 del_hash,
			 u8 term,
			 u8 termlen)
अणु
	काष्ठा i40iw_modअगरy_qp_info info;

	स_रखो(&info, 0, माप(info));
	info.next_iwarp_state = state;
	info.हटाओ_hash_idx = del_hash;
	info.cq_num_valid = true;
	info.arp_cache_idx_valid = true;
	info.करोnt_send_term = true;
	info.करोnt_send_fin = true;
	info.termlen = termlen;

	अगर (term & I40IWQP_TERM_SEND_TERM_ONLY)
		info.करोnt_send_term = false;
	अगर (term & I40IWQP_TERM_SEND_FIN_ONLY)
		info.करोnt_send_fin = false;
	अगर (iwqp->sc_qp.term_flags && (state == I40IW_QP_STATE_ERROR))
		info.reset_tcp_conn = true;
	iwqp->hw_iwarp_state = state;
	i40iw_hw_modअगरy_qp(iwqp->iwdev, iwqp, &info, 0);
पूर्ण

/**
 * i40iw_process_aeq - handle aeq events
 * @iwdev: iwarp device
 */
व्योम i40iw_process_aeq(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_aeq *aeq = &iwdev->aeq;
	काष्ठा i40iw_sc_aeq *sc_aeq = &aeq->sc_aeq;
	काष्ठा i40iw_aeqe_info aeinfo;
	काष्ठा i40iw_aeqe_info *info = &aeinfo;
	पूर्णांक ret;
	काष्ठा i40iw_qp *iwqp = शून्य;
	काष्ठा i40iw_sc_cq *cq = शून्य;
	काष्ठा i40iw_cq *iwcq = शून्य;
	काष्ठा i40iw_sc_qp *qp = शून्य;
	काष्ठा i40iw_qp_host_ctx_info *ctx_info = शून्य;
	अचिन्हित दीर्घ flags;

	u32 aeqcnt = 0;

	अगर (!sc_aeq->size)
		वापस;

	करो अणु
		स_रखो(info, 0, माप(*info));
		ret = dev->aeq_ops->get_next_aeqe(sc_aeq, info);
		अगर (ret)
			अवरोध;

		aeqcnt++;
		i40iw_debug(dev, I40IW_DEBUG_AEQ,
			    "%s ae_id = 0x%x bool qp=%d qp_id = %d\n",
			    __func__, info->ae_id, info->qp, info->qp_cq_id);
		अगर (info->qp) अणु
			spin_lock_irqsave(&iwdev->qptable_lock, flags);
			iwqp = iwdev->qp_table[info->qp_cq_id];
			अगर (!iwqp) अणु
				spin_unlock_irqrestore(&iwdev->qptable_lock, flags);
				i40iw_debug(dev, I40IW_DEBUG_AEQ,
					    "%s qp_id %d is already freed\n",
					    __func__, info->qp_cq_id);
				जारी;
			पूर्ण
			i40iw_qp_add_ref(&iwqp->ibqp);
			spin_unlock_irqrestore(&iwdev->qptable_lock, flags);
			qp = &iwqp->sc_qp;
			spin_lock_irqsave(&iwqp->lock, flags);
			iwqp->hw_tcp_state = info->tcp_state;
			iwqp->hw_iwarp_state = info->iwarp_state;
			iwqp->last_aeq = info->ae_id;
			spin_unlock_irqrestore(&iwqp->lock, flags);
			ctx_info = &iwqp->ctx_info;
			ctx_info->err_rq_idx_valid = true;
		पूर्ण अन्यथा अणु
			अगर (info->ae_id != I40IW_AE_CQ_OPERATION_ERROR)
				जारी;
		पूर्ण

		चयन (info->ae_id) अणु
		हाल I40IW_AE_LLP_FIN_RECEIVED:
			अगर (qp->term_flags)
				अवरोध;
			अगर (atomic_inc_वापस(&iwqp->बंद_समयr_started) == 1) अणु
				iwqp->hw_tcp_state = I40IW_TCP_STATE_CLOSE_WAIT;
				अगर ((iwqp->hw_tcp_state == I40IW_TCP_STATE_CLOSE_WAIT) &&
				    (iwqp->ibqp_state == IB_QPS_RTS)) अणु
					i40iw_next_iw_state(iwqp,
							    I40IW_QP_STATE_CLOSING, 0, 0, 0);
					i40iw_cm_disconn(iwqp);
				पूर्ण
				iwqp->cm_id->add_ref(iwqp->cm_id);
				i40iw_schedule_cm_समयr(iwqp->cm_node,
							(काष्ठा i40iw_puda_buf *)iwqp,
							I40IW_TIMER_TYPE_CLOSE, 1, 0);
			पूर्ण
			अवरोध;
		हाल I40IW_AE_LLP_CLOSE_COMPLETE:
			अगर (qp->term_flags)
				i40iw_terminate_करोne(qp, 0);
			अन्यथा
				i40iw_cm_disconn(iwqp);
			अवरोध;
		हाल I40IW_AE_BAD_CLOSE:
		हाल I40IW_AE_RESET_SENT:
			i40iw_next_iw_state(iwqp, I40IW_QP_STATE_ERROR, 1, 0, 0);
			i40iw_cm_disconn(iwqp);
			अवरोध;
		हाल I40IW_AE_LLP_CONNECTION_RESET:
			अगर (atomic_पढ़ो(&iwqp->बंद_समयr_started))
				अवरोध;
			i40iw_cm_disconn(iwqp);
			अवरोध;
		हाल I40IW_AE_QP_SUSPEND_COMPLETE:
			i40iw_qp_suspend_resume(dev, &iwqp->sc_qp, false);
			अवरोध;
		हाल I40IW_AE_TERMINATE_SENT:
			i40iw_terminate_send_fin(qp);
			अवरोध;
		हाल I40IW_AE_LLP_TERMINATE_RECEIVED:
			i40iw_terminate_received(qp, info);
			अवरोध;
		हाल I40IW_AE_CQ_OPERATION_ERROR:
			i40iw_pr_err("Processing an iWARP related AE for CQ misc = 0x%04X\n",
				     info->ae_id);
			cq = (काष्ठा i40iw_sc_cq *)(अचिन्हित दीर्घ)info->compl_ctx;
			iwcq = (काष्ठा i40iw_cq *)cq->back_cq;

			अगर (iwcq->ibcq.event_handler) अणु
				काष्ठा ib_event ibevent;

				ibevent.device = iwcq->ibcq.device;
				ibevent.event = IB_EVENT_CQ_ERR;
				ibevent.element.cq = &iwcq->ibcq;
				iwcq->ibcq.event_handler(&ibevent, iwcq->ibcq.cq_context);
			पूर्ण
			अवरोध;
		हाल I40IW_AE_LLP_DOUBT_REACHABILITY:
			अवरोध;
		हाल I40IW_AE_PRIV_OPERATION_DENIED:
		हाल I40IW_AE_STAG_ZERO_INVALID:
		हाल I40IW_AE_IB_RREQ_AND_Q1_FULL:
		हाल I40IW_AE_DDP_UBE_INVALID_DDP_VERSION:
		हाल I40IW_AE_DDP_UBE_INVALID_MO:
		हाल I40IW_AE_DDP_UBE_INVALID_QN:
		हाल I40IW_AE_DDP_NO_L_BIT:
		हाल I40IW_AE_RDMAP_ROE_INVALID_RDMAP_VERSION:
		हाल I40IW_AE_RDMAP_ROE_UNEXPECTED_OPCODE:
		हाल I40IW_AE_ROE_INVALID_RDMA_READ_REQUEST:
		हाल I40IW_AE_ROE_INVALID_RDMA_WRITE_OR_READ_RESP:
		हाल I40IW_AE_INVALID_ARP_ENTRY:
		हाल I40IW_AE_INVALID_TCP_OPTION_RCVD:
		हाल I40IW_AE_STALE_ARP_ENTRY:
		हाल I40IW_AE_LLP_RECEIVED_MPA_CRC_ERROR:
		हाल I40IW_AE_LLP_SEGMENT_TOO_SMALL:
		हाल I40IW_AE_LLP_SYN_RECEIVED:
		हाल I40IW_AE_LLP_TOO_MANY_RETRIES:
		हाल I40IW_AE_LCE_QP_CATASTROPHIC:
		हाल I40IW_AE_LCE_FUNCTION_CATASTROPHIC:
		हाल I40IW_AE_LCE_CQ_CATASTROPHIC:
		हाल I40IW_AE_UDA_XMIT_DGRAM_TOO_LONG:
		हाल I40IW_AE_UDA_XMIT_DGRAM_TOO_SHORT:
			ctx_info->err_rq_idx_valid = false;
			fallthrough;
		शेष:
			अगर (!info->sq && ctx_info->err_rq_idx_valid) अणु
				ctx_info->err_rq_idx = info->wqe_idx;
				ctx_info->tcp_info_valid = false;
				ctx_info->iwarp_info_valid = false;
				ret = dev->iw_priv_qp_ops->qp_setctx(&iwqp->sc_qp,
								     iwqp->host_ctx.va,
								     ctx_info);
			पूर्ण
			i40iw_terminate_connection(qp, info);
			अवरोध;
		पूर्ण
		अगर (info->qp)
			i40iw_qp_rem_ref(&iwqp->ibqp);
	पूर्ण जबतक (1);

	अगर (aeqcnt)
		dev->aeq_ops->repost_aeq_entries(dev, aeqcnt);
पूर्ण

/**
 * i40iw_cqp_manage_abvpt_cmd - send cqp command manage abpvt
 * @iwdev: iwarp device
 * @accel_local_port: port क्रम apbvt
 * @add_port: add or delete port
 */
अटल क्रमागत i40iw_status_code
i40iw_cqp_manage_abvpt_cmd(काष्ठा i40iw_device *iwdev,
			   u16 accel_local_port,
			   bool add_port)
अणु
	काष्ठा i40iw_apbvt_info *info;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	क्रमागत i40iw_status_code status;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, add_port);
	अगर (!cqp_request)
		वापस I40IW_ERR_NO_MEMORY;

	cqp_info = &cqp_request->info;
	info = &cqp_info->in.u.manage_apbvt_entry.info;

	स_रखो(info, 0, माप(*info));
	info->add = add_port;
	info->port = cpu_to_le16(accel_local_port);

	cqp_info->cqp_cmd = OP_MANAGE_APBVT_ENTRY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.manage_apbvt_entry.cqp = &iwdev->cqp.sc_cqp;
	cqp_info->in.u.manage_apbvt_entry.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP Manage APBVT entry fail");

	वापस status;
पूर्ण

/**
 * i40iw_manage_apbvt - add or delete tcp port
 * @iwdev: iwarp device
 * @accel_local_port: port क्रम apbvt
 * @add_port: add or delete port
 */
क्रमागत i40iw_status_code i40iw_manage_apbvt(काष्ठा i40iw_device *iwdev,
					  u16 accel_local_port,
					  bool add_port)
अणु
	काष्ठा i40iw_cm_core *cm_core = &iwdev->cm_core;
	क्रमागत i40iw_status_code status;
	अचिन्हित दीर्घ flags;
	bool in_use;

	/* apbvt_lock is held across CQP delete APBVT OP (non-रुकोing) to
	 * protect against race where add APBVT CQP can race ahead of the delete
	 * APBVT क्रम same port.
	 */
	अगर (add_port) अणु
		spin_lock_irqsave(&cm_core->apbvt_lock, flags);
		in_use = __test_and_set_bit(accel_local_port,
					    cm_core->ports_in_use);
		spin_unlock_irqrestore(&cm_core->apbvt_lock, flags);
		अगर (in_use)
			वापस 0;
		वापस i40iw_cqp_manage_abvpt_cmd(iwdev, accel_local_port,
						  true);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&cm_core->apbvt_lock, flags);
		in_use = i40iw_port_in_use(cm_core, accel_local_port);
		अगर (in_use) अणु
			spin_unlock_irqrestore(&cm_core->apbvt_lock, flags);
			वापस 0;
		पूर्ण
		__clear_bit(accel_local_port, cm_core->ports_in_use);
		status = i40iw_cqp_manage_abvpt_cmd(iwdev, accel_local_port,
						    false);
		spin_unlock_irqrestore(&cm_core->apbvt_lock, flags);
		वापस status;
	पूर्ण
पूर्ण

/**
 * i40iw_manage_arp_cache - manage hw arp cache
 * @iwdev: iwarp device
 * @mac_addr: mac address ptr
 * @ip_addr: ip addr क्रम arp cache
 * @ipv4: flag indicating IPv4 when true
 * @action: add, delete or modअगरy
 */
व्योम i40iw_manage_arp_cache(काष्ठा i40iw_device *iwdev,
			    अचिन्हित अक्षर *mac_addr,
			    u32 *ip_addr,
			    bool ipv4,
			    u32 action)
अणु
	काष्ठा i40iw_add_arp_cache_entry_info *info;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	पूर्णांक arp_index;

	arp_index = i40iw_arp_table(iwdev, ip_addr, ipv4, mac_addr, action);
	अगर (arp_index < 0)
		वापस;
	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, false);
	अगर (!cqp_request)
		वापस;

	cqp_info = &cqp_request->info;
	अगर (action == I40IW_ARP_ADD) अणु
		cqp_info->cqp_cmd = OP_ADD_ARP_CACHE_ENTRY;
		info = &cqp_info->in.u.add_arp_cache_entry.info;
		स_रखो(info, 0, माप(*info));
		info->arp_index = cpu_to_le16((u16)arp_index);
		info->permanent = true;
		ether_addr_copy(info->mac_addr, mac_addr);
		cqp_info->in.u.add_arp_cache_entry.scratch = (uपूर्णांकptr_t)cqp_request;
		cqp_info->in.u.add_arp_cache_entry.cqp = &iwdev->cqp.sc_cqp;
	पूर्ण अन्यथा अणु
		cqp_info->cqp_cmd = OP_DELETE_ARP_CACHE_ENTRY;
		cqp_info->in.u.del_arp_cache_entry.scratch = (uपूर्णांकptr_t)cqp_request;
		cqp_info->in.u.del_arp_cache_entry.cqp = &iwdev->cqp.sc_cqp;
		cqp_info->in.u.del_arp_cache_entry.arp_index = arp_index;
	पूर्ण

	cqp_info->in.u.add_arp_cache_entry.cqp = &iwdev->cqp.sc_cqp;
	cqp_info->in.u.add_arp_cache_entry.scratch = (uपूर्णांकptr_t)cqp_request;
	cqp_info->post_sq = 1;
	अगर (i40iw_handle_cqp_op(iwdev, cqp_request))
		i40iw_pr_err("CQP-OP Add/Del Arp Cache entry fail");
पूर्ण

/**
 * i40iw_send_syn_cqp_callback - करो syn/ack after qhash
 * @cqp_request: qhash cqp completion
 * @send_ack: flag send ack
 */
अटल व्योम i40iw_send_syn_cqp_callback(काष्ठा i40iw_cqp_request *cqp_request, u32 send_ack)
अणु
	i40iw_send_syn(cqp_request->param, send_ack);
पूर्ण

/**
 * i40iw_manage_qhash - add or modअगरy qhash
 * @iwdev: iwarp device
 * @cminfo: cm info क्रम qhash
 * @etype: type (syn or quad)
 * @mtype: type of qhash
 * @cmnode: cmnode associated with connection
 * @रुको: रुको क्रम completion
 */
क्रमागत i40iw_status_code i40iw_manage_qhash(काष्ठा i40iw_device *iwdev,
					  काष्ठा i40iw_cm_info *cminfo,
					  क्रमागत i40iw_quad_entry_type etype,
					  क्रमागत i40iw_quad_hash_manage_type mtype,
					  व्योम *cmnode,
					  bool रुको)
अणु
	काष्ठा i40iw_qhash_table_info *info;
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_sc_vsi *vsi = &iwdev->vsi;
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_cqp *iwcqp = &iwdev->cqp;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;

	cqp_request = i40iw_get_cqp_request(iwcqp, रुको);
	अगर (!cqp_request)
		वापस I40IW_ERR_NO_MEMORY;
	cqp_info = &cqp_request->info;
	info = &cqp_info->in.u.manage_qhash_table_entry.info;
	स_रखो(info, 0, माप(*info));

	info->vsi = &iwdev->vsi;
	info->manage = mtype;
	info->entry_type = etype;
	अगर (cminfo->vlan_id != 0xFFFF) अणु
		info->vlan_valid = true;
		info->vlan_id = cpu_to_le16(cminfo->vlan_id);
	पूर्ण अन्यथा अणु
		info->vlan_valid = false;
	पूर्ण

	info->ipv4_valid = cminfo->ipv4;
	info->user_pri = cminfo->user_pri;
	ether_addr_copy(info->mac_addr, iwdev->netdev->dev_addr);
	info->qp_num = cpu_to_le32(vsi->ilq->qp_id);
	info->dest_port = cpu_to_le16(cminfo->loc_port);
	info->dest_ip[0] = cpu_to_le32(cminfo->loc_addr[0]);
	info->dest_ip[1] = cpu_to_le32(cminfo->loc_addr[1]);
	info->dest_ip[2] = cpu_to_le32(cminfo->loc_addr[2]);
	info->dest_ip[3] = cpu_to_le32(cminfo->loc_addr[3]);
	अगर (etype == I40IW_QHASH_TYPE_TCP_ESTABLISHED) अणु
		info->src_port = cpu_to_le16(cminfo->rem_port);
		info->src_ip[0] = cpu_to_le32(cminfo->rem_addr[0]);
		info->src_ip[1] = cpu_to_le32(cminfo->rem_addr[1]);
		info->src_ip[2] = cpu_to_le32(cminfo->rem_addr[2]);
		info->src_ip[3] = cpu_to_le32(cminfo->rem_addr[3]);
	पूर्ण
	अगर (cmnode) अणु
		cqp_request->callback_fcn = i40iw_send_syn_cqp_callback;
		cqp_request->param = (व्योम *)cmnode;
	पूर्ण

	अगर (info->ipv4_valid)
		i40iw_debug(dev, I40IW_DEBUG_CM,
			    "%s:%s IP=%pI4, port=%d, mac=%pM, vlan_id=%d\n",
			    __func__, (!mtype) ? "DELETE" : "ADD",
			    info->dest_ip,
			    info->dest_port, info->mac_addr, cminfo->vlan_id);
	अन्यथा
		i40iw_debug(dev, I40IW_DEBUG_CM,
			    "%s:%s IP=%pI6, port=%d, mac=%pM, vlan_id=%d\n",
			    __func__, (!mtype) ? "DELETE" : "ADD",
			    info->dest_ip,
			    info->dest_port, info->mac_addr, cminfo->vlan_id);
	cqp_info->in.u.manage_qhash_table_entry.cqp = &iwdev->cqp.sc_cqp;
	cqp_info->in.u.manage_qhash_table_entry.scratch = (uपूर्णांकptr_t)cqp_request;
	cqp_info->cqp_cmd = OP_MANAGE_QHASH_TABLE_ENTRY;
	cqp_info->post_sq = 1;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP Manage Qhash Entry fail");
	वापस status;
पूर्ण

/**
 * i40iw_hw_flush_wqes - flush qp's wqe
 * @iwdev: iwarp device
 * @qp: hardware control qp
 * @info: info क्रम flush
 * @रुको: flag रुको क्रम completion
 */
क्रमागत i40iw_status_code i40iw_hw_flush_wqes(काष्ठा i40iw_device *iwdev,
					   काष्ठा i40iw_sc_qp *qp,
					   काष्ठा i40iw_qp_flush_info *info,
					   bool रुको)
अणु
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_qp_flush_info *hw_info;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	काष्ठा i40iw_qp *iwqp = (काष्ठा i40iw_qp *)qp->back_qp;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, रुको);
	अगर (!cqp_request)
		वापस I40IW_ERR_NO_MEMORY;

	cqp_info = &cqp_request->info;
	hw_info = &cqp_request->info.in.u.qp_flush_wqes.info;
	स_नकल(hw_info, info, माप(*hw_info));

	cqp_info->cqp_cmd = OP_QP_FLUSH_WQES;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_flush_wqes.qp = qp;
	cqp_info->in.u.qp_flush_wqes.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status) अणु
		i40iw_pr_err("CQP-OP Flush WQE's fail");
		complete(&iwqp->sq_drained);
		complete(&iwqp->rq_drained);
		वापस status;
	पूर्ण
	अगर (!cqp_request->compl_info.maj_err_code) अणु
		चयन (cqp_request->compl_info.min_err_code) अणु
		हाल I40IW_CQP_COMPL_RQ_WQE_FLUSHED:
			complete(&iwqp->sq_drained);
			अवरोध;
		हाल I40IW_CQP_COMPL_SQ_WQE_FLUSHED:
			complete(&iwqp->rq_drained);
			अवरोध;
		हाल I40IW_CQP_COMPL_RQ_SQ_WQE_FLUSHED:
			अवरोध;
		शेष:
			complete(&iwqp->sq_drained);
			complete(&iwqp->rq_drained);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40iw_gen_ae - generate AE
 * @iwdev: iwarp device
 * @qp: qp associated with AE
 * @info: info क्रम ae
 * @रुको: रुको क्रम completion
 */
व्योम i40iw_gen_ae(काष्ठा i40iw_device *iwdev,
		  काष्ठा i40iw_sc_qp *qp,
		  काष्ठा i40iw_gen_ae_info *info,
		  bool रुको)
अणु
	काष्ठा i40iw_gen_ae_info *ae_info;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, रुको);
	अगर (!cqp_request)
		वापस;

	cqp_info = &cqp_request->info;
	ae_info = &cqp_request->info.in.u.gen_ae.info;
	स_नकल(ae_info, info, माप(*ae_info));

	cqp_info->cqp_cmd = OP_GEN_AE;
	cqp_info->post_sq = 1;
	cqp_info->in.u.gen_ae.qp = qp;
	cqp_info->in.u.gen_ae.scratch = (uपूर्णांकptr_t)cqp_request;
	अगर (i40iw_handle_cqp_op(iwdev, cqp_request))
		i40iw_pr_err("CQP OP failed attempting to generate ae_code=0x%x\n",
			     info->ae_code);
पूर्ण

/**
 * i40iw_hw_manage_vf_pble_bp - manage vf pbles
 * @iwdev: iwarp device
 * @info: info क्रम managing pble
 * @रुको: flag रुको क्रम completion
 */
क्रमागत i40iw_status_code i40iw_hw_manage_vf_pble_bp(काष्ठा i40iw_device *iwdev,
						  काष्ठा i40iw_manage_vf_pble_info *info,
						  bool रुको)
अणु
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_manage_vf_pble_info *hw_info;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;

	अगर ((iwdev->init_state < CCQ_CREATED) && रुको)
		रुको = false;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, रुको);
	अगर (!cqp_request)
		वापस I40IW_ERR_NO_MEMORY;

	cqp_info = &cqp_request->info;
	hw_info = &cqp_request->info.in.u.manage_vf_pble_bp.info;
	स_नकल(hw_info, info, माप(*hw_info));

	cqp_info->cqp_cmd = OP_MANAGE_VF_PBLE_BP;
	cqp_info->post_sq = 1;
	cqp_info->in.u.manage_vf_pble_bp.cqp = &iwdev->cqp.sc_cqp;
	cqp_info->in.u.manage_vf_pble_bp.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP Manage VF pble_bp fail");
	वापस status;
पूर्ण

/**
 * i40iw_get_ib_wc - वापस change flush code to IB's
 * @opcode: iwarp flush code
 */
अटल क्रमागत ib_wc_status i40iw_get_ib_wc(क्रमागत i40iw_flush_opcode opcode)
अणु
	चयन (opcode) अणु
	हाल FLUSH_PROT_ERR:
		वापस IB_WC_LOC_PROT_ERR;
	हाल FLUSH_REM_ACCESS_ERR:
		वापस IB_WC_REM_ACCESS_ERR;
	हाल FLUSH_LOC_QP_OP_ERR:
		वापस IB_WC_LOC_QP_OP_ERR;
	हाल FLUSH_REM_OP_ERR:
		वापस IB_WC_REM_OP_ERR;
	हाल FLUSH_LOC_LEN_ERR:
		वापस IB_WC_LOC_LEN_ERR;
	हाल FLUSH_GENERAL_ERR:
		वापस IB_WC_GENERAL_ERR;
	हाल FLUSH_FATAL_ERR:
	शेष:
		वापस IB_WC_FATAL_ERR;
	पूर्ण
पूर्ण

/**
 * i40iw_set_flush_info - set flush info
 * @pinfo: set flush info
 * @min: minor err
 * @maj: major err
 * @opcode: flush error code
 */
अटल व्योम i40iw_set_flush_info(काष्ठा i40iw_qp_flush_info *pinfo,
				 u16 *min,
				 u16 *maj,
				 क्रमागत i40iw_flush_opcode opcode)
अणु
	*min = (u16)i40iw_get_ib_wc(opcode);
	*maj = CQE_MAJOR_DRV;
	pinfo->userflushcode = true;
पूर्ण

/**
 * i40iw_flush_wqes - flush wqe क्रम qp
 * @iwdev: iwarp device
 * @iwqp: qp to flush wqes
 */
व्योम i40iw_flush_wqes(काष्ठा i40iw_device *iwdev, काष्ठा i40iw_qp *iwqp)
अणु
	काष्ठा i40iw_qp_flush_info info;
	काष्ठा i40iw_qp_flush_info *pinfo = &info;

	काष्ठा i40iw_sc_qp *qp = &iwqp->sc_qp;

	स_रखो(pinfo, 0, माप(*pinfo));
	info.sq = true;
	info.rq = true;
	अगर (qp->term_flags) अणु
		i40iw_set_flush_info(pinfo, &pinfo->sq_minor_code,
				     &pinfo->sq_major_code, qp->flush_code);
		i40iw_set_flush_info(pinfo, &pinfo->rq_minor_code,
				     &pinfo->rq_major_code, qp->flush_code);
	पूर्ण
	(व्योम)i40iw_hw_flush_wqes(iwdev, &iwqp->sc_qp, &info, true);
पूर्ण
