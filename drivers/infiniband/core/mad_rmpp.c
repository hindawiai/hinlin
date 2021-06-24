<शैली गुरु>
/*
 * Copyright (c) 2005 Intel Inc. All rights reserved.
 * Copyright (c) 2005-2006 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2014 Intel Corporation.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/slab.h>

#समावेश "mad_priv.h"
#समावेश "mad_rmpp.h"

क्रमागत rmpp_state अणु
	RMPP_STATE_ACTIVE,
	RMPP_STATE_TIMEOUT,
	RMPP_STATE_COMPLETE
पूर्ण;

काष्ठा mad_rmpp_recv अणु
	काष्ठा ib_mad_agent_निजी *agent;
	काष्ठा list_head list;
	काष्ठा delayed_work समयout_work;
	काष्ठा delayed_work cleanup_work;
	काष्ठा completion comp;
	क्रमागत rmpp_state state;
	spinlock_t lock;
	refcount_t refcount;

	काष्ठा ib_ah *ah;
	काष्ठा ib_mad_recv_wc *rmpp_wc;
	काष्ठा ib_mad_recv_buf *cur_seg_buf;
	पूर्णांक last_ack;
	पूर्णांक seg_num;
	पूर्णांक newwin;
	पूर्णांक repwin;

	__be64 tid;
	u32 src_qp;
	u32 slid;
	u8 mgmt_class;
	u8 class_version;
	u8 method;
	u8 base_version;
पूर्ण;

अटल अंतरभूत व्योम deref_rmpp_recv(काष्ठा mad_rmpp_recv *rmpp_recv)
अणु
	अगर (refcount_dec_and_test(&rmpp_recv->refcount))
		complete(&rmpp_recv->comp);
पूर्ण

अटल व्योम destroy_rmpp_recv(काष्ठा mad_rmpp_recv *rmpp_recv)
अणु
	deref_rmpp_recv(rmpp_recv);
	रुको_क्रम_completion(&rmpp_recv->comp);
	rdma_destroy_ah(rmpp_recv->ah, RDMA_DESTROY_AH_SLEEPABLE);
	kमुक्त(rmpp_recv);
पूर्ण

व्योम ib_cancel_rmpp_recvs(काष्ठा ib_mad_agent_निजी *agent)
अणु
	काष्ठा mad_rmpp_recv *rmpp_recv, *temp_rmpp_recv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&agent->lock, flags);
	list_क्रम_each_entry(rmpp_recv, &agent->rmpp_list, list) अणु
		cancel_delayed_work(&rmpp_recv->समयout_work);
		cancel_delayed_work(&rmpp_recv->cleanup_work);
	पूर्ण
	spin_unlock_irqrestore(&agent->lock, flags);

	flush_workqueue(agent->qp_info->port_priv->wq);

	list_क्रम_each_entry_safe(rmpp_recv, temp_rmpp_recv,
				 &agent->rmpp_list, list) अणु
		list_del(&rmpp_recv->list);
		अगर (rmpp_recv->state != RMPP_STATE_COMPLETE)
			ib_मुक्त_recv_mad(rmpp_recv->rmpp_wc);
		destroy_rmpp_recv(rmpp_recv);
	पूर्ण
पूर्ण

अटल व्योम क्रमmat_ack(काष्ठा ib_mad_send_buf *msg,
		       काष्ठा ib_rmpp_mad *data,
		       काष्ठा mad_rmpp_recv *rmpp_recv)
अणु
	काष्ठा ib_rmpp_mad *ack = msg->mad;
	अचिन्हित दीर्घ flags;

	स_नकल(ack, &data->mad_hdr, msg->hdr_len);

	ack->mad_hdr.method ^= IB_MGMT_METHOD_RESP;
	ack->rmpp_hdr.rmpp_type = IB_MGMT_RMPP_TYPE_ACK;
	ib_set_rmpp_flags(&ack->rmpp_hdr, IB_MGMT_RMPP_FLAG_ACTIVE);

	spin_lock_irqsave(&rmpp_recv->lock, flags);
	rmpp_recv->last_ack = rmpp_recv->seg_num;
	ack->rmpp_hdr.seg_num = cpu_to_be32(rmpp_recv->seg_num);
	ack->rmpp_hdr.paylen_newwin = cpu_to_be32(rmpp_recv->newwin);
	spin_unlock_irqrestore(&rmpp_recv->lock, flags);
पूर्ण

अटल व्योम ack_recv(काष्ठा mad_rmpp_recv *rmpp_recv,
		     काष्ठा ib_mad_recv_wc *recv_wc)
अणु
	काष्ठा ib_mad_send_buf *msg;
	पूर्णांक ret, hdr_len;

	hdr_len = ib_get_mad_data_offset(recv_wc->recv_buf.mad->mad_hdr.mgmt_class);
	msg = ib_create_send_mad(&rmpp_recv->agent->agent, recv_wc->wc->src_qp,
				 recv_wc->wc->pkey_index, 1, hdr_len,
				 0, GFP_KERNEL,
				 IB_MGMT_BASE_VERSION);
	अगर (IS_ERR(msg))
		वापस;

	क्रमmat_ack(msg, (काष्ठा ib_rmpp_mad *) recv_wc->recv_buf.mad, rmpp_recv);
	msg->ah = rmpp_recv->ah;
	ret = ib_post_send_mad(msg, शून्य);
	अगर (ret)
		ib_मुक्त_send_mad(msg);
पूर्ण

अटल काष्ठा ib_mad_send_buf *alloc_response_msg(काष्ठा ib_mad_agent *agent,
						  काष्ठा ib_mad_recv_wc *recv_wc)
अणु
	काष्ठा ib_mad_send_buf *msg;
	काष्ठा ib_ah *ah;
	पूर्णांक hdr_len;

	ah = ib_create_ah_from_wc(agent->qp->pd, recv_wc->wc,
				  recv_wc->recv_buf.grh, agent->port_num);
	अगर (IS_ERR(ah))
		वापस (व्योम *) ah;

	hdr_len = ib_get_mad_data_offset(recv_wc->recv_buf.mad->mad_hdr.mgmt_class);
	msg = ib_create_send_mad(agent, recv_wc->wc->src_qp,
				 recv_wc->wc->pkey_index, 1,
				 hdr_len, 0, GFP_KERNEL,
				 IB_MGMT_BASE_VERSION);
	अगर (IS_ERR(msg))
		rdma_destroy_ah(ah, RDMA_DESTROY_AH_SLEEPABLE);
	अन्यथा अणु
		msg->ah = ah;
		msg->context[0] = ah;
	पूर्ण

	वापस msg;
पूर्ण

अटल व्योम ack_ds_ack(काष्ठा ib_mad_agent_निजी *agent,
		       काष्ठा ib_mad_recv_wc *recv_wc)
अणु
	काष्ठा ib_mad_send_buf *msg;
	काष्ठा ib_rmpp_mad *rmpp_mad;
	पूर्णांक ret;

	msg = alloc_response_msg(&agent->agent, recv_wc);
	अगर (IS_ERR(msg))
		वापस;

	rmpp_mad = msg->mad;
	स_नकल(rmpp_mad, recv_wc->recv_buf.mad, msg->hdr_len);

	rmpp_mad->mad_hdr.method ^= IB_MGMT_METHOD_RESP;
	ib_set_rmpp_flags(&rmpp_mad->rmpp_hdr, IB_MGMT_RMPP_FLAG_ACTIVE);
	rmpp_mad->rmpp_hdr.seg_num = 0;
	rmpp_mad->rmpp_hdr.paylen_newwin = cpu_to_be32(1);

	ret = ib_post_send_mad(msg, शून्य);
	अगर (ret) अणु
		rdma_destroy_ah(msg->ah, RDMA_DESTROY_AH_SLEEPABLE);
		ib_मुक्त_send_mad(msg);
	पूर्ण
पूर्ण

व्योम ib_rmpp_send_handler(काष्ठा ib_mad_send_wc *mad_send_wc)
अणु
	अगर (mad_send_wc->send_buf->context[0] == mad_send_wc->send_buf->ah)
		rdma_destroy_ah(mad_send_wc->send_buf->ah,
				RDMA_DESTROY_AH_SLEEPABLE);
	ib_मुक्त_send_mad(mad_send_wc->send_buf);
पूर्ण

अटल व्योम nack_recv(काष्ठा ib_mad_agent_निजी *agent,
		      काष्ठा ib_mad_recv_wc *recv_wc, u8 rmpp_status)
अणु
	काष्ठा ib_mad_send_buf *msg;
	काष्ठा ib_rmpp_mad *rmpp_mad;
	पूर्णांक ret;

	msg = alloc_response_msg(&agent->agent, recv_wc);
	अगर (IS_ERR(msg))
		वापस;

	rmpp_mad = msg->mad;
	स_नकल(rmpp_mad, recv_wc->recv_buf.mad, msg->hdr_len);

	rmpp_mad->mad_hdr.method ^= IB_MGMT_METHOD_RESP;
	rmpp_mad->rmpp_hdr.rmpp_version = IB_MGMT_RMPP_VERSION;
	rmpp_mad->rmpp_hdr.rmpp_type = IB_MGMT_RMPP_TYPE_ABORT;
	ib_set_rmpp_flags(&rmpp_mad->rmpp_hdr, IB_MGMT_RMPP_FLAG_ACTIVE);
	rmpp_mad->rmpp_hdr.rmpp_status = rmpp_status;
	rmpp_mad->rmpp_hdr.seg_num = 0;
	rmpp_mad->rmpp_hdr.paylen_newwin = 0;

	ret = ib_post_send_mad(msg, शून्य);
	अगर (ret) अणु
		rdma_destroy_ah(msg->ah, RDMA_DESTROY_AH_SLEEPABLE);
		ib_मुक्त_send_mad(msg);
	पूर्ण
पूर्ण

अटल व्योम recv_समयout_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mad_rmpp_recv *rmpp_recv =
		container_of(work, काष्ठा mad_rmpp_recv, समयout_work.work);
	काष्ठा ib_mad_recv_wc *rmpp_wc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rmpp_recv->agent->lock, flags);
	अगर (rmpp_recv->state != RMPP_STATE_ACTIVE) अणु
		spin_unlock_irqrestore(&rmpp_recv->agent->lock, flags);
		वापस;
	पूर्ण
	rmpp_recv->state = RMPP_STATE_TIMEOUT;
	list_del(&rmpp_recv->list);
	spin_unlock_irqrestore(&rmpp_recv->agent->lock, flags);

	rmpp_wc = rmpp_recv->rmpp_wc;
	nack_recv(rmpp_recv->agent, rmpp_wc, IB_MGMT_RMPP_STATUS_T2L);
	destroy_rmpp_recv(rmpp_recv);
	ib_मुक्त_recv_mad(rmpp_wc);
पूर्ण

अटल व्योम recv_cleanup_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mad_rmpp_recv *rmpp_recv =
		container_of(work, काष्ठा mad_rmpp_recv, cleanup_work.work);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rmpp_recv->agent->lock, flags);
	list_del(&rmpp_recv->list);
	spin_unlock_irqrestore(&rmpp_recv->agent->lock, flags);
	destroy_rmpp_recv(rmpp_recv);
पूर्ण

अटल काष्ठा mad_rmpp_recv *
create_rmpp_recv(काष्ठा ib_mad_agent_निजी *agent,
		 काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा mad_rmpp_recv *rmpp_recv;
	काष्ठा ib_mad_hdr *mad_hdr;

	rmpp_recv = kदो_स्मृति(माप *rmpp_recv, GFP_KERNEL);
	अगर (!rmpp_recv)
		वापस शून्य;

	rmpp_recv->ah = ib_create_ah_from_wc(agent->agent.qp->pd,
					     mad_recv_wc->wc,
					     mad_recv_wc->recv_buf.grh,
					     agent->agent.port_num);
	अगर (IS_ERR(rmpp_recv->ah))
		जाओ error;

	rmpp_recv->agent = agent;
	init_completion(&rmpp_recv->comp);
	INIT_DELAYED_WORK(&rmpp_recv->समयout_work, recv_समयout_handler);
	INIT_DELAYED_WORK(&rmpp_recv->cleanup_work, recv_cleanup_handler);
	spin_lock_init(&rmpp_recv->lock);
	rmpp_recv->state = RMPP_STATE_ACTIVE;
	refcount_set(&rmpp_recv->refcount, 1);

	rmpp_recv->rmpp_wc = mad_recv_wc;
	rmpp_recv->cur_seg_buf = &mad_recv_wc->recv_buf;
	rmpp_recv->newwin = 1;
	rmpp_recv->seg_num = 1;
	rmpp_recv->last_ack = 0;
	rmpp_recv->repwin = 1;

	mad_hdr = &mad_recv_wc->recv_buf.mad->mad_hdr;
	rmpp_recv->tid = mad_hdr->tid;
	rmpp_recv->src_qp = mad_recv_wc->wc->src_qp;
	rmpp_recv->slid = mad_recv_wc->wc->slid;
	rmpp_recv->mgmt_class = mad_hdr->mgmt_class;
	rmpp_recv->class_version = mad_hdr->class_version;
	rmpp_recv->method  = mad_hdr->method;
	rmpp_recv->base_version  = mad_hdr->base_version;
	वापस rmpp_recv;

error:	kमुक्त(rmpp_recv);
	वापस शून्य;
पूर्ण

अटल काष्ठा mad_rmpp_recv *
find_rmpp_recv(काष्ठा ib_mad_agent_निजी *agent,
	       काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा mad_rmpp_recv *rmpp_recv;
	काष्ठा ib_mad_hdr *mad_hdr = &mad_recv_wc->recv_buf.mad->mad_hdr;

	list_क्रम_each_entry(rmpp_recv, &agent->rmpp_list, list) अणु
		अगर (rmpp_recv->tid == mad_hdr->tid &&
		    rmpp_recv->src_qp == mad_recv_wc->wc->src_qp &&
		    rmpp_recv->slid == mad_recv_wc->wc->slid &&
		    rmpp_recv->mgmt_class == mad_hdr->mgmt_class &&
		    rmpp_recv->class_version == mad_hdr->class_version &&
		    rmpp_recv->method == mad_hdr->method)
			वापस rmpp_recv;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mad_rmpp_recv *
acquire_rmpp_recv(काष्ठा ib_mad_agent_निजी *agent,
		  काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा mad_rmpp_recv *rmpp_recv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&agent->lock, flags);
	rmpp_recv = find_rmpp_recv(agent, mad_recv_wc);
	अगर (rmpp_recv)
		refcount_inc(&rmpp_recv->refcount);
	spin_unlock_irqrestore(&agent->lock, flags);
	वापस rmpp_recv;
पूर्ण

अटल काष्ठा mad_rmpp_recv *
insert_rmpp_recv(काष्ठा ib_mad_agent_निजी *agent,
		 काष्ठा mad_rmpp_recv *rmpp_recv)
अणु
	काष्ठा mad_rmpp_recv *cur_rmpp_recv;

	cur_rmpp_recv = find_rmpp_recv(agent, rmpp_recv->rmpp_wc);
	अगर (!cur_rmpp_recv)
		list_add_tail(&rmpp_recv->list, &agent->rmpp_list);

	वापस cur_rmpp_recv;
पूर्ण

अटल अंतरभूत पूर्णांक get_last_flag(काष्ठा ib_mad_recv_buf *seg)
अणु
	काष्ठा ib_rmpp_mad *rmpp_mad;

	rmpp_mad = (काष्ठा ib_rmpp_mad *) seg->mad;
	वापस ib_get_rmpp_flags(&rmpp_mad->rmpp_hdr) & IB_MGMT_RMPP_FLAG_LAST;
पूर्ण

अटल अंतरभूत पूर्णांक get_seg_num(काष्ठा ib_mad_recv_buf *seg)
अणु
	काष्ठा ib_rmpp_mad *rmpp_mad;

	rmpp_mad = (काष्ठा ib_rmpp_mad *) seg->mad;
	वापस be32_to_cpu(rmpp_mad->rmpp_hdr.seg_num);
पूर्ण

अटल अंतरभूत काष्ठा ib_mad_recv_buf *get_next_seg(काष्ठा list_head *rmpp_list,
						   काष्ठा ib_mad_recv_buf *seg)
अणु
	अगर (seg->list.next == rmpp_list)
		वापस शून्य;

	वापस container_of(seg->list.next, काष्ठा ib_mad_recv_buf, list);
पूर्ण

अटल अंतरभूत पूर्णांक winकरोw_size(काष्ठा ib_mad_agent_निजी *agent)
अणु
	वापस max(agent->qp_info->recv_queue.max_active >> 3, 1);
पूर्ण

अटल काष्ठा ib_mad_recv_buf *find_seg_location(काष्ठा list_head *rmpp_list,
						 पूर्णांक seg_num)
अणु
	काष्ठा ib_mad_recv_buf *seg_buf;
	पूर्णांक cur_seg_num;

	list_क्रम_each_entry_reverse(seg_buf, rmpp_list, list) अणु
		cur_seg_num = get_seg_num(seg_buf);
		अगर (seg_num > cur_seg_num)
			वापस seg_buf;
		अगर (seg_num == cur_seg_num)
			अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम update_seg_num(काष्ठा mad_rmpp_recv *rmpp_recv,
			   काष्ठा ib_mad_recv_buf *new_buf)
अणु
	काष्ठा list_head *rmpp_list = &rmpp_recv->rmpp_wc->rmpp_list;

	जबतक (new_buf && (get_seg_num(new_buf) == rmpp_recv->seg_num + 1)) अणु
		rmpp_recv->cur_seg_buf = new_buf;
		rmpp_recv->seg_num++;
		new_buf = get_next_seg(rmpp_list, new_buf);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक get_mad_len(काष्ठा mad_rmpp_recv *rmpp_recv)
अणु
	काष्ठा ib_rmpp_mad *rmpp_mad;
	पूर्णांक hdr_size, data_size, pad;
	bool opa = rdma_cap_opa_mad(rmpp_recv->agent->qp_info->port_priv->device,
				    rmpp_recv->agent->qp_info->port_priv->port_num);

	rmpp_mad = (काष्ठा ib_rmpp_mad *)rmpp_recv->cur_seg_buf->mad;

	hdr_size = ib_get_mad_data_offset(rmpp_mad->mad_hdr.mgmt_class);
	अगर (opa && rmpp_recv->base_version == OPA_MGMT_BASE_VERSION) अणु
		data_size = माप(काष्ठा opa_rmpp_mad) - hdr_size;
		pad = OPA_MGMT_RMPP_DATA - be32_to_cpu(rmpp_mad->rmpp_hdr.paylen_newwin);
		अगर (pad > OPA_MGMT_RMPP_DATA || pad < 0)
			pad = 0;
	पूर्ण अन्यथा अणु
		data_size = माप(काष्ठा ib_rmpp_mad) - hdr_size;
		pad = IB_MGMT_RMPP_DATA - be32_to_cpu(rmpp_mad->rmpp_hdr.paylen_newwin);
		अगर (pad > IB_MGMT_RMPP_DATA || pad < 0)
			pad = 0;
	पूर्ण

	वापस hdr_size + rmpp_recv->seg_num * data_size - pad;
पूर्ण

अटल काष्ठा ib_mad_recv_wc *complete_rmpp(काष्ठा mad_rmpp_recv *rmpp_recv)
अणु
	काष्ठा ib_mad_recv_wc *rmpp_wc;

	ack_recv(rmpp_recv, rmpp_recv->rmpp_wc);
	अगर (rmpp_recv->seg_num > 1)
		cancel_delayed_work(&rmpp_recv->समयout_work);

	rmpp_wc = rmpp_recv->rmpp_wc;
	rmpp_wc->mad_len = get_mad_len(rmpp_recv);
	/* 10 seconds until we can find the packet lअगरeसमय */
	queue_delayed_work(rmpp_recv->agent->qp_info->port_priv->wq,
			   &rmpp_recv->cleanup_work, msecs_to_jअगरfies(10000));
	वापस rmpp_wc;
पूर्ण

अटल काष्ठा ib_mad_recv_wc *
जारी_rmpp(काष्ठा ib_mad_agent_निजी *agent,
	      काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा mad_rmpp_recv *rmpp_recv;
	काष्ठा ib_mad_recv_buf *prev_buf;
	काष्ठा ib_mad_recv_wc *करोne_wc;
	पूर्णांक seg_num;
	अचिन्हित दीर्घ flags;

	rmpp_recv = acquire_rmpp_recv(agent, mad_recv_wc);
	अगर (!rmpp_recv)
		जाओ drop1;

	seg_num = get_seg_num(&mad_recv_wc->recv_buf);

	spin_lock_irqsave(&rmpp_recv->lock, flags);
	अगर ((rmpp_recv->state == RMPP_STATE_TIMEOUT) ||
	    (seg_num > rmpp_recv->newwin))
		जाओ drop3;

	अगर ((seg_num <= rmpp_recv->last_ack) ||
	    (rmpp_recv->state == RMPP_STATE_COMPLETE)) अणु
		spin_unlock_irqrestore(&rmpp_recv->lock, flags);
		ack_recv(rmpp_recv, mad_recv_wc);
		जाओ drop2;
	पूर्ण

	prev_buf = find_seg_location(&rmpp_recv->rmpp_wc->rmpp_list, seg_num);
	अगर (!prev_buf)
		जाओ drop3;

	करोne_wc = शून्य;
	list_add(&mad_recv_wc->recv_buf.list, &prev_buf->list);
	अगर (rmpp_recv->cur_seg_buf == prev_buf) अणु
		update_seg_num(rmpp_recv, &mad_recv_wc->recv_buf);
		अगर (get_last_flag(rmpp_recv->cur_seg_buf)) अणु
			rmpp_recv->state = RMPP_STATE_COMPLETE;
			spin_unlock_irqrestore(&rmpp_recv->lock, flags);
			करोne_wc = complete_rmpp(rmpp_recv);
			जाओ out;
		पूर्ण अन्यथा अगर (rmpp_recv->seg_num == rmpp_recv->newwin) अणु
			rmpp_recv->newwin += winकरोw_size(agent);
			spin_unlock_irqrestore(&rmpp_recv->lock, flags);
			ack_recv(rmpp_recv, mad_recv_wc);
			जाओ out;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&rmpp_recv->lock, flags);
out:
	deref_rmpp_recv(rmpp_recv);
	वापस करोne_wc;

drop3:	spin_unlock_irqrestore(&rmpp_recv->lock, flags);
drop2:	deref_rmpp_recv(rmpp_recv);
drop1:	ib_मुक्त_recv_mad(mad_recv_wc);
	वापस शून्य;
पूर्ण

अटल काष्ठा ib_mad_recv_wc *
start_rmpp(काष्ठा ib_mad_agent_निजी *agent,
	   काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा mad_rmpp_recv *rmpp_recv;
	अचिन्हित दीर्घ flags;

	rmpp_recv = create_rmpp_recv(agent, mad_recv_wc);
	अगर (!rmpp_recv) अणु
		ib_मुक्त_recv_mad(mad_recv_wc);
		वापस शून्य;
	पूर्ण

	spin_lock_irqsave(&agent->lock, flags);
	अगर (insert_rmpp_recv(agent, rmpp_recv)) अणु
		spin_unlock_irqrestore(&agent->lock, flags);
		/* duplicate first MAD */
		destroy_rmpp_recv(rmpp_recv);
		वापस जारी_rmpp(agent, mad_recv_wc);
	पूर्ण
	refcount_inc(&rmpp_recv->refcount);

	अगर (get_last_flag(&mad_recv_wc->recv_buf)) अणु
		rmpp_recv->state = RMPP_STATE_COMPLETE;
		spin_unlock_irqrestore(&agent->lock, flags);
		complete_rmpp(rmpp_recv);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&agent->lock, flags);
		/* 40 seconds until we can find the packet lअगरeबार */
		queue_delayed_work(agent->qp_info->port_priv->wq,
				   &rmpp_recv->समयout_work,
				   msecs_to_jअगरfies(40000));
		rmpp_recv->newwin += winकरोw_size(agent);
		ack_recv(rmpp_recv, mad_recv_wc);
		mad_recv_wc = शून्य;
	पूर्ण
	deref_rmpp_recv(rmpp_recv);
	वापस mad_recv_wc;
पूर्ण

अटल पूर्णांक send_next_seg(काष्ठा ib_mad_send_wr_निजी *mad_send_wr)
अणु
	काष्ठा ib_rmpp_mad *rmpp_mad;
	पूर्णांक समयout;
	u32 paylen = 0;

	rmpp_mad = mad_send_wr->send_buf.mad;
	ib_set_rmpp_flags(&rmpp_mad->rmpp_hdr, IB_MGMT_RMPP_FLAG_ACTIVE);
	rmpp_mad->rmpp_hdr.seg_num = cpu_to_be32(++mad_send_wr->seg_num);

	अगर (mad_send_wr->seg_num == 1) अणु
		rmpp_mad->rmpp_hdr.rmpp_rसमय_flags |= IB_MGMT_RMPP_FLAG_FIRST;
		paylen = (mad_send_wr->send_buf.seg_count *
			  mad_send_wr->send_buf.seg_rmpp_size) -
			  mad_send_wr->pad;
	पूर्ण

	अगर (mad_send_wr->seg_num == mad_send_wr->send_buf.seg_count) अणु
		rmpp_mad->rmpp_hdr.rmpp_rसमय_flags |= IB_MGMT_RMPP_FLAG_LAST;
		paylen = mad_send_wr->send_buf.seg_rmpp_size - mad_send_wr->pad;
	पूर्ण
	rmpp_mad->rmpp_hdr.paylen_newwin = cpu_to_be32(paylen);

	/* 2 seconds क्रम an ACK until we can find the packet lअगरeसमय */
	समयout = mad_send_wr->send_buf.समयout_ms;
	अगर (!समयout || समयout > 2000)
		mad_send_wr->समयout = msecs_to_jअगरfies(2000);

	वापस ib_send_mad(mad_send_wr);
पूर्ण

अटल व्योम पात_send(काष्ठा ib_mad_agent_निजी *agent,
		       काष्ठा ib_mad_recv_wc *mad_recv_wc, u8 rmpp_status)
अणु
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;
	काष्ठा ib_mad_send_wc wc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&agent->lock, flags);
	mad_send_wr = ib_find_send_mad(agent, mad_recv_wc);
	अगर (!mad_send_wr)
		जाओ out;	/* Unmatched send */

	अगर ((mad_send_wr->last_ack == mad_send_wr->send_buf.seg_count) ||
	    (!mad_send_wr->समयout) || (mad_send_wr->status != IB_WC_SUCCESS))
		जाओ out;	/* Send is alपढ़ोy करोne */

	ib_mark_mad_करोne(mad_send_wr);
	spin_unlock_irqrestore(&agent->lock, flags);

	wc.status = IB_WC_REM_ABORT_ERR;
	wc.venकरोr_err = rmpp_status;
	wc.send_buf = &mad_send_wr->send_buf;
	ib_mad_complete_send_wr(mad_send_wr, &wc);
	वापस;
out:
	spin_unlock_irqrestore(&agent->lock, flags);
पूर्ण

अटल अंतरभूत व्योम adjust_last_ack(काष्ठा ib_mad_send_wr_निजी *wr,
				   पूर्णांक seg_num)
अणु
	काष्ठा list_head *list;

	wr->last_ack = seg_num;
	list = &wr->last_ack_seg->list;
	list_क्रम_each_entry(wr->last_ack_seg, list, list)
		अगर (wr->last_ack_seg->num == seg_num)
			अवरोध;
पूर्ण

अटल व्योम process_ds_ack(काष्ठा ib_mad_agent_निजी *agent,
			   काष्ठा ib_mad_recv_wc *mad_recv_wc, पूर्णांक newwin)
अणु
	काष्ठा mad_rmpp_recv *rmpp_recv;

	rmpp_recv = find_rmpp_recv(agent, mad_recv_wc);
	अगर (rmpp_recv && rmpp_recv->state == RMPP_STATE_COMPLETE)
		rmpp_recv->repwin = newwin;
पूर्ण

अटल व्योम process_rmpp_ack(काष्ठा ib_mad_agent_निजी *agent,
			     काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;
	काष्ठा ib_rmpp_mad *rmpp_mad;
	अचिन्हित दीर्घ flags;
	पूर्णांक seg_num, newwin, ret;

	rmpp_mad = (काष्ठा ib_rmpp_mad *)mad_recv_wc->recv_buf.mad;
	अगर (rmpp_mad->rmpp_hdr.rmpp_status) अणु
		पात_send(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_BAD_STATUS);
		nack_recv(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_BAD_STATUS);
		वापस;
	पूर्ण

	seg_num = be32_to_cpu(rmpp_mad->rmpp_hdr.seg_num);
	newwin = be32_to_cpu(rmpp_mad->rmpp_hdr.paylen_newwin);
	अगर (newwin < seg_num) अणु
		पात_send(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_W2S);
		nack_recv(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_W2S);
		वापस;
	पूर्ण

	spin_lock_irqsave(&agent->lock, flags);
	mad_send_wr = ib_find_send_mad(agent, mad_recv_wc);
	अगर (!mad_send_wr) अणु
		अगर (!seg_num)
			process_ds_ack(agent, mad_recv_wc, newwin);
		जाओ out;	/* Unmatched or DS RMPP ACK */
	पूर्ण

	अगर ((mad_send_wr->last_ack == mad_send_wr->send_buf.seg_count) &&
	    (mad_send_wr->समयout)) अणु
		spin_unlock_irqrestore(&agent->lock, flags);
		ack_ds_ack(agent, mad_recv_wc);
		वापस;		/* Repeated ACK क्रम DS RMPP transaction */
	पूर्ण

	अगर ((mad_send_wr->last_ack == mad_send_wr->send_buf.seg_count) ||
	    (!mad_send_wr->समयout) || (mad_send_wr->status != IB_WC_SUCCESS))
		जाओ out;	/* Send is alपढ़ोy करोne */

	अगर (seg_num > mad_send_wr->send_buf.seg_count ||
	    seg_num > mad_send_wr->newwin) अणु
		spin_unlock_irqrestore(&agent->lock, flags);
		पात_send(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_S2B);
		nack_recv(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_S2B);
		वापस;
	पूर्ण

	अगर (newwin < mad_send_wr->newwin || seg_num < mad_send_wr->last_ack)
		जाओ out;	/* Old ACK */

	अगर (seg_num > mad_send_wr->last_ack) अणु
		adjust_last_ack(mad_send_wr, seg_num);
		mad_send_wr->retries_left = mad_send_wr->max_retries;
	पूर्ण
	mad_send_wr->newwin = newwin;
	अगर (mad_send_wr->last_ack == mad_send_wr->send_buf.seg_count) अणु
		/* If no response is expected, the ACK completes the send */
		अगर (!mad_send_wr->send_buf.समयout_ms) अणु
			काष्ठा ib_mad_send_wc wc;

			ib_mark_mad_करोne(mad_send_wr);
			spin_unlock_irqrestore(&agent->lock, flags);

			wc.status = IB_WC_SUCCESS;
			wc.venकरोr_err = 0;
			wc.send_buf = &mad_send_wr->send_buf;
			ib_mad_complete_send_wr(mad_send_wr, &wc);
			वापस;
		पूर्ण
		अगर (mad_send_wr->refcount == 1)
			ib_reset_mad_समयout(mad_send_wr,
					     mad_send_wr->send_buf.समयout_ms);
		spin_unlock_irqrestore(&agent->lock, flags);
		ack_ds_ack(agent, mad_recv_wc);
		वापस;
	पूर्ण अन्यथा अगर (mad_send_wr->refcount == 1 &&
		   mad_send_wr->seg_num < mad_send_wr->newwin &&
		   mad_send_wr->seg_num < mad_send_wr->send_buf.seg_count) अणु
		/* Send failure will just result in a समयout/retry */
		ret = send_next_seg(mad_send_wr);
		अगर (ret)
			जाओ out;

		mad_send_wr->refcount++;
		list_move_tail(&mad_send_wr->agent_list,
			      &mad_send_wr->mad_agent_priv->send_list);
	पूर्ण
out:
	spin_unlock_irqrestore(&agent->lock, flags);
पूर्ण

अटल काष्ठा ib_mad_recv_wc *
process_rmpp_data(काष्ठा ib_mad_agent_निजी *agent,
		  काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा ib_rmpp_hdr *rmpp_hdr;
	u8 rmpp_status;

	rmpp_hdr = &((काष्ठा ib_rmpp_mad *)mad_recv_wc->recv_buf.mad)->rmpp_hdr;

	अगर (rmpp_hdr->rmpp_status) अणु
		rmpp_status = IB_MGMT_RMPP_STATUS_BAD_STATUS;
		जाओ bad;
	पूर्ण

	अगर (rmpp_hdr->seg_num == cpu_to_be32(1)) अणु
		अगर (!(ib_get_rmpp_flags(rmpp_hdr) & IB_MGMT_RMPP_FLAG_FIRST)) अणु
			rmpp_status = IB_MGMT_RMPP_STATUS_BAD_SEG;
			जाओ bad;
		पूर्ण
		वापस start_rmpp(agent, mad_recv_wc);
	पूर्ण अन्यथा अणु
		अगर (ib_get_rmpp_flags(rmpp_hdr) & IB_MGMT_RMPP_FLAG_FIRST) अणु
			rmpp_status = IB_MGMT_RMPP_STATUS_BAD_SEG;
			जाओ bad;
		पूर्ण
		वापस जारी_rmpp(agent, mad_recv_wc);
	पूर्ण
bad:
	nack_recv(agent, mad_recv_wc, rmpp_status);
	ib_मुक्त_recv_mad(mad_recv_wc);
	वापस शून्य;
पूर्ण

अटल व्योम process_rmpp_stop(काष्ठा ib_mad_agent_निजी *agent,
			      काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा ib_rmpp_mad *rmpp_mad;

	rmpp_mad = (काष्ठा ib_rmpp_mad *)mad_recv_wc->recv_buf.mad;

	अगर (rmpp_mad->rmpp_hdr.rmpp_status != IB_MGMT_RMPP_STATUS_RESX) अणु
		पात_send(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_BAD_STATUS);
		nack_recv(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_BAD_STATUS);
	पूर्ण अन्यथा
		पात_send(agent, mad_recv_wc, rmpp_mad->rmpp_hdr.rmpp_status);
पूर्ण

अटल व्योम process_rmpp_पात(काष्ठा ib_mad_agent_निजी *agent,
			       काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा ib_rmpp_mad *rmpp_mad;

	rmpp_mad = (काष्ठा ib_rmpp_mad *)mad_recv_wc->recv_buf.mad;

	अगर (rmpp_mad->rmpp_hdr.rmpp_status < IB_MGMT_RMPP_STATUS_ABORT_MIN ||
	    rmpp_mad->rmpp_hdr.rmpp_status > IB_MGMT_RMPP_STATUS_ABORT_MAX) अणु
		पात_send(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_BAD_STATUS);
		nack_recv(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_BAD_STATUS);
	पूर्ण अन्यथा
		पात_send(agent, mad_recv_wc, rmpp_mad->rmpp_hdr.rmpp_status);
पूर्ण

काष्ठा ib_mad_recv_wc *
ib_process_rmpp_recv_wc(काष्ठा ib_mad_agent_निजी *agent,
			काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा ib_rmpp_mad *rmpp_mad;

	rmpp_mad = (काष्ठा ib_rmpp_mad *)mad_recv_wc->recv_buf.mad;
	अगर (!(rmpp_mad->rmpp_hdr.rmpp_rसमय_flags & IB_MGMT_RMPP_FLAG_ACTIVE))
		वापस mad_recv_wc;

	अगर (rmpp_mad->rmpp_hdr.rmpp_version != IB_MGMT_RMPP_VERSION) अणु
		पात_send(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_UNV);
		nack_recv(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_UNV);
		जाओ out;
	पूर्ण

	चयन (rmpp_mad->rmpp_hdr.rmpp_type) अणु
	हाल IB_MGMT_RMPP_TYPE_DATA:
		वापस process_rmpp_data(agent, mad_recv_wc);
	हाल IB_MGMT_RMPP_TYPE_ACK:
		process_rmpp_ack(agent, mad_recv_wc);
		अवरोध;
	हाल IB_MGMT_RMPP_TYPE_STOP:
		process_rmpp_stop(agent, mad_recv_wc);
		अवरोध;
	हाल IB_MGMT_RMPP_TYPE_ABORT:
		process_rmpp_पात(agent, mad_recv_wc);
		अवरोध;
	शेष:
		पात_send(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_BADT);
		nack_recv(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_BADT);
		अवरोध;
	पूर्ण
out:
	ib_मुक्त_recv_mad(mad_recv_wc);
	वापस शून्य;
पूर्ण

अटल पूर्णांक init_newwin(काष्ठा ib_mad_send_wr_निजी *mad_send_wr)
अणु
	काष्ठा ib_mad_agent_निजी *agent = mad_send_wr->mad_agent_priv;
	काष्ठा ib_mad_hdr *mad_hdr = mad_send_wr->send_buf.mad;
	काष्ठा mad_rmpp_recv *rmpp_recv;
	काष्ठा rdma_ah_attr ah_attr;
	अचिन्हित दीर्घ flags;
	पूर्णांक newwin = 1;

	अगर (!(mad_hdr->method & IB_MGMT_METHOD_RESP))
		जाओ out;

	spin_lock_irqsave(&agent->lock, flags);
	list_क्रम_each_entry(rmpp_recv, &agent->rmpp_list, list) अणु
		अगर (rmpp_recv->tid != mad_hdr->tid ||
		    rmpp_recv->mgmt_class != mad_hdr->mgmt_class ||
		    rmpp_recv->class_version != mad_hdr->class_version ||
		    (rmpp_recv->method & IB_MGMT_METHOD_RESP))
			जारी;

		अगर (rdma_query_ah(mad_send_wr->send_buf.ah, &ah_attr))
			जारी;

		अगर (rmpp_recv->slid == rdma_ah_get_dlid(&ah_attr)) अणु
			newwin = rmpp_recv->repwin;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&agent->lock, flags);
out:
	वापस newwin;
पूर्ण

पूर्णांक ib_send_rmpp_mad(काष्ठा ib_mad_send_wr_निजी *mad_send_wr)
अणु
	काष्ठा ib_rmpp_mad *rmpp_mad;
	पूर्णांक ret;

	rmpp_mad = mad_send_wr->send_buf.mad;
	अगर (!(ib_get_rmpp_flags(&rmpp_mad->rmpp_hdr) &
	      IB_MGMT_RMPP_FLAG_ACTIVE))
		वापस IB_RMPP_RESULT_UNHANDLED;

	अगर (rmpp_mad->rmpp_hdr.rmpp_type != IB_MGMT_RMPP_TYPE_DATA) अणु
		mad_send_wr->seg_num = 1;
		वापस IB_RMPP_RESULT_INTERNAL;
	पूर्ण

	mad_send_wr->newwin = init_newwin(mad_send_wr);

	/* We need to रुको क्रम the final ACK even अगर there isn't a response */
	mad_send_wr->refcount += (mad_send_wr->समयout == 0);
	ret = send_next_seg(mad_send_wr);
	अगर (!ret)
		वापस IB_RMPP_RESULT_CONSUMED;
	वापस ret;
पूर्ण

पूर्णांक ib_process_rmpp_send_wc(काष्ठा ib_mad_send_wr_निजी *mad_send_wr,
			    काष्ठा ib_mad_send_wc *mad_send_wc)
अणु
	काष्ठा ib_rmpp_mad *rmpp_mad;
	पूर्णांक ret;

	rmpp_mad = mad_send_wr->send_buf.mad;
	अगर (!(ib_get_rmpp_flags(&rmpp_mad->rmpp_hdr) &
	      IB_MGMT_RMPP_FLAG_ACTIVE))
		वापस IB_RMPP_RESULT_UNHANDLED; /* RMPP not active */

	अगर (rmpp_mad->rmpp_hdr.rmpp_type != IB_MGMT_RMPP_TYPE_DATA)
		वापस IB_RMPP_RESULT_INTERNAL;	 /* ACK, STOP, or ABORT */

	अगर (mad_send_wc->status != IB_WC_SUCCESS ||
	    mad_send_wr->status != IB_WC_SUCCESS)
		वापस IB_RMPP_RESULT_PROCESSED; /* Canceled or send error */

	अगर (!mad_send_wr->समयout)
		वापस IB_RMPP_RESULT_PROCESSED; /* Response received */

	अगर (mad_send_wr->last_ack == mad_send_wr->send_buf.seg_count) अणु
		mad_send_wr->समयout =
			msecs_to_jअगरfies(mad_send_wr->send_buf.समयout_ms);
		वापस IB_RMPP_RESULT_PROCESSED; /* Send करोne */
	पूर्ण

	अगर (mad_send_wr->seg_num == mad_send_wr->newwin ||
	    mad_send_wr->seg_num == mad_send_wr->send_buf.seg_count)
		वापस IB_RMPP_RESULT_PROCESSED; /* Wait क्रम ACK */

	ret = send_next_seg(mad_send_wr);
	अगर (ret) अणु
		mad_send_wc->status = IB_WC_GENERAL_ERR;
		वापस IB_RMPP_RESULT_PROCESSED;
	पूर्ण
	वापस IB_RMPP_RESULT_CONSUMED;
पूर्ण

पूर्णांक ib_retry_rmpp(काष्ठा ib_mad_send_wr_निजी *mad_send_wr)
अणु
	काष्ठा ib_rmpp_mad *rmpp_mad;
	पूर्णांक ret;

	rmpp_mad = mad_send_wr->send_buf.mad;
	अगर (!(ib_get_rmpp_flags(&rmpp_mad->rmpp_hdr) &
	      IB_MGMT_RMPP_FLAG_ACTIVE))
		वापस IB_RMPP_RESULT_UNHANDLED; /* RMPP not active */

	अगर (mad_send_wr->last_ack == mad_send_wr->send_buf.seg_count)
		वापस IB_RMPP_RESULT_PROCESSED;

	mad_send_wr->seg_num = mad_send_wr->last_ack;
	mad_send_wr->cur_seg = mad_send_wr->last_ack_seg;

	ret = send_next_seg(mad_send_wr);
	अगर (ret)
		वापस IB_RMPP_RESULT_PROCESSED;

	वापस IB_RMPP_RESULT_CONSUMED;
पूर्ण
