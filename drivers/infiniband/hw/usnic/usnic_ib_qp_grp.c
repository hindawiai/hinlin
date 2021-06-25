<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
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
 *
 */
#समावेश <linux/bug.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>

#समावेश "usnic_log.h"
#समावेश "usnic_vnic.h"
#समावेश "usnic_fwd.h"
#समावेश "usnic_uiom.h"
#समावेश "usnic_debugfs.h"
#समावेश "usnic_ib_qp_grp.h"
#समावेश "usnic_ib_sysfs.h"
#समावेश "usnic_transport.h"

#घोषणा DFLT_RQ_IDX	0

स्थिर अक्षर *usnic_ib_qp_grp_state_to_string(क्रमागत ib_qp_state state)
अणु
	चयन (state) अणु
	हाल IB_QPS_RESET:
		वापस "Rst";
	हाल IB_QPS_INIT:
		वापस "Init";
	हाल IB_QPS_RTR:
		वापस "RTR";
	हाल IB_QPS_RTS:
		वापस "RTS";
	हाल IB_QPS_SQD:
		वापस "SQD";
	हाल IB_QPS_SQE:
		वापस "SQE";
	हाल IB_QPS_ERR:
		वापस "ERR";
	शेष:
		वापस "UNKNOWN STATE";

	पूर्ण
पूर्ण

पूर्णांक usnic_ib_qp_grp_dump_hdr(अक्षर *buf, पूर्णांक buf_sz)
अणु
	वापस scnम_लिखो(buf, buf_sz, "|QPN\t|State\t|PID\t|VF Idx\t|Fil ID");
पूर्ण

पूर्णांक usnic_ib_qp_grp_dump_rows(व्योम *obj, अक्षर *buf, पूर्णांक buf_sz)
अणु
	काष्ठा usnic_ib_qp_grp *qp_grp = obj;
	काष्ठा usnic_ib_qp_grp_flow *शेष_flow;
	अगर (obj) अणु
		शेष_flow = list_first_entry(&qp_grp->flows_lst,
					काष्ठा usnic_ib_qp_grp_flow, link);
		वापस scnम_लिखो(buf, buf_sz, "|%d\t|%s\t|%d\t|%hu\t|%d",
					qp_grp->ibqp.qp_num,
					usnic_ib_qp_grp_state_to_string(
							qp_grp->state),
					qp_grp->owner_pid,
					usnic_vnic_get_index(qp_grp->vf->vnic),
					शेष_flow->flow->flow_id);
	पूर्ण अन्यथा अणु
		वापस scnम_लिखो(buf, buf_sz, "|N/A\t|N/A\t|N/A\t|N/A\t|N/A");
	पूर्ण
पूर्ण

अटल काष्ठा usnic_vnic_res_chunk *
get_qp_res_chunk(काष्ठा usnic_ib_qp_grp *qp_grp)
अणु
	lockdep_निश्चित_held(&qp_grp->lock);
	/*
	 * The QP res chunk, used to derive qp indices,
	 * are just indices of the RQs
	 */
	वापस usnic_ib_qp_grp_get_chunk(qp_grp, USNIC_VNIC_RES_TYPE_RQ);
पूर्ण

अटल पूर्णांक enable_qp_grp(काष्ठा usnic_ib_qp_grp *qp_grp)
अणु

	पूर्णांक status;
	पूर्णांक i, vnic_idx;
	काष्ठा usnic_vnic_res_chunk *res_chunk;
	काष्ठा usnic_vnic_res *res;

	lockdep_निश्चित_held(&qp_grp->lock);

	vnic_idx = usnic_vnic_get_index(qp_grp->vf->vnic);

	res_chunk = get_qp_res_chunk(qp_grp);
	अगर (IS_ERR(res_chunk)) अणु
		usnic_err("Unable to get qp res with err %ld\n",
				PTR_ERR(res_chunk));
		वापस PTR_ERR(res_chunk);
	पूर्ण

	क्रम (i = 0; i < res_chunk->cnt; i++) अणु
		res = res_chunk->res[i];
		status = usnic_fwd_enable_qp(qp_grp->ufdev, vnic_idx,
						res->vnic_idx);
		अगर (status) अणु
			usnic_err("Failed to enable qp %d of %s:%d\n with err %d\n",
					res->vnic_idx, qp_grp->ufdev->name,
					vnic_idx, status);
			जाओ out_err;
		पूर्ण
	पूर्ण

	वापस 0;

out_err:
	क्रम (i--; i >= 0; i--) अणु
		res = res_chunk->res[i];
		usnic_fwd_disable_qp(qp_grp->ufdev, vnic_idx,
					res->vnic_idx);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक disable_qp_grp(काष्ठा usnic_ib_qp_grp *qp_grp)
अणु
	पूर्णांक i, vnic_idx;
	काष्ठा usnic_vnic_res_chunk *res_chunk;
	काष्ठा usnic_vnic_res *res;
	पूर्णांक status = 0;

	lockdep_निश्चित_held(&qp_grp->lock);
	vnic_idx = usnic_vnic_get_index(qp_grp->vf->vnic);

	res_chunk = get_qp_res_chunk(qp_grp);
	अगर (IS_ERR(res_chunk)) अणु
		usnic_err("Unable to get qp res with err %ld\n",
			PTR_ERR(res_chunk));
		वापस PTR_ERR(res_chunk);
	पूर्ण

	क्रम (i = 0; i < res_chunk->cnt; i++) अणु
		res = res_chunk->res[i];
		status = usnic_fwd_disable_qp(qp_grp->ufdev, vnic_idx,
						res->vnic_idx);
		अगर (status) अणु
			usnic_err("Failed to disable rq %d of %s:%d\n with err %d\n",
					res->vnic_idx,
					qp_grp->ufdev->name,
					vnic_idx, status);
		पूर्ण
	पूर्ण

	वापस status;

पूर्ण

अटल पूर्णांक init_filter_action(काष्ठा usnic_ib_qp_grp *qp_grp,
				काष्ठा usnic_filter_action *uaction)
अणु
	काष्ठा usnic_vnic_res_chunk *res_chunk;

	res_chunk = usnic_ib_qp_grp_get_chunk(qp_grp, USNIC_VNIC_RES_TYPE_RQ);
	अगर (IS_ERR(res_chunk)) अणु
		usnic_err("Unable to get %s with err %ld\n",
			usnic_vnic_res_type_to_str(USNIC_VNIC_RES_TYPE_RQ),
			PTR_ERR(res_chunk));
		वापस PTR_ERR(res_chunk);
	पूर्ण

	uaction->vnic_idx = usnic_vnic_get_index(qp_grp->vf->vnic);
	uaction->action.type = FILTER_ACTION_RQ_STEERING;
	uaction->action.u.rq_idx = res_chunk->res[DFLT_RQ_IDX]->vnic_idx;

	वापस 0;
पूर्ण

अटल काष्ठा usnic_ib_qp_grp_flow*
create_roce_custom_flow(काष्ठा usnic_ib_qp_grp *qp_grp,
			काष्ठा usnic_transport_spec *trans_spec)
अणु
	uपूर्णांक16_t port_num;
	पूर्णांक err;
	काष्ठा filter filter;
	काष्ठा usnic_filter_action uaction;
	काष्ठा usnic_ib_qp_grp_flow *qp_flow;
	काष्ठा usnic_fwd_flow *flow;
	क्रमागत usnic_transport_type trans_type;

	trans_type = trans_spec->trans_type;
	port_num = trans_spec->usnic_roce.port_num;

	/* Reserve Port */
	port_num = usnic_transport_rsrv_port(trans_type, port_num);
	अगर (port_num == 0)
		वापस ERR_PTR(-EINVAL);

	/* Create Flow */
	usnic_fwd_init_usnic_filter(&filter, port_num);
	err = init_filter_action(qp_grp, &uaction);
	अगर (err)
		जाओ out_unreserve_port;

	flow = usnic_fwd_alloc_flow(qp_grp->ufdev, &filter, &uaction);
	अगर (IS_ERR_OR_शून्य(flow)) अणु
		err = flow ? PTR_ERR(flow) : -EFAULT;
		जाओ out_unreserve_port;
	पूर्ण

	/* Create Flow Handle */
	qp_flow = kzalloc(माप(*qp_flow), GFP_ATOMIC);
	अगर (!qp_flow) अणु
		err = -ENOMEM;
		जाओ out_dealloc_flow;
	पूर्ण
	qp_flow->flow = flow;
	qp_flow->trans_type = trans_type;
	qp_flow->usnic_roce.port_num = port_num;
	qp_flow->qp_grp = qp_grp;
	वापस qp_flow;

out_dealloc_flow:
	usnic_fwd_dealloc_flow(flow);
out_unreserve_port:
	usnic_transport_unrsrv_port(trans_type, port_num);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम release_roce_custom_flow(काष्ठा usnic_ib_qp_grp_flow *qp_flow)
अणु
	usnic_fwd_dealloc_flow(qp_flow->flow);
	usnic_transport_unrsrv_port(qp_flow->trans_type,
					qp_flow->usnic_roce.port_num);
	kमुक्त(qp_flow);
पूर्ण

अटल काष्ठा usnic_ib_qp_grp_flow*
create_udp_flow(काष्ठा usnic_ib_qp_grp *qp_grp,
		काष्ठा usnic_transport_spec *trans_spec)
अणु
	काष्ठा socket *sock;
	पूर्णांक sock_fd;
	पूर्णांक err;
	काष्ठा filter filter;
	काष्ठा usnic_filter_action uaction;
	काष्ठा usnic_ib_qp_grp_flow *qp_flow;
	काष्ठा usnic_fwd_flow *flow;
	क्रमागत usnic_transport_type trans_type;
	uपूर्णांक32_t addr;
	uपूर्णांक16_t port_num;
	पूर्णांक proto;

	trans_type = trans_spec->trans_type;
	sock_fd = trans_spec->udp.sock_fd;

	/* Get and check socket */
	sock = usnic_transport_get_socket(sock_fd);
	अगर (IS_ERR_OR_शून्य(sock))
		वापस ERR_CAST(sock);

	err = usnic_transport_sock_get_addr(sock, &proto, &addr, &port_num);
	अगर (err)
		जाओ out_put_sock;

	अगर (proto != IPPROTO_UDP) अणु
		usnic_err("Protocol for fd %d is not UDP", sock_fd);
		err = -EPERM;
		जाओ out_put_sock;
	पूर्ण

	/* Create flow */
	usnic_fwd_init_udp_filter(&filter, addr, port_num);
	err = init_filter_action(qp_grp, &uaction);
	अगर (err)
		जाओ out_put_sock;

	flow = usnic_fwd_alloc_flow(qp_grp->ufdev, &filter, &uaction);
	अगर (IS_ERR_OR_शून्य(flow)) अणु
		err = flow ? PTR_ERR(flow) : -EFAULT;
		जाओ out_put_sock;
	पूर्ण

	/* Create qp_flow */
	qp_flow = kzalloc(माप(*qp_flow), GFP_ATOMIC);
	अगर (!qp_flow) अणु
		err = -ENOMEM;
		जाओ out_dealloc_flow;
	पूर्ण
	qp_flow->flow = flow;
	qp_flow->trans_type = trans_type;
	qp_flow->udp.sock = sock;
	qp_flow->qp_grp = qp_grp;
	वापस qp_flow;

out_dealloc_flow:
	usnic_fwd_dealloc_flow(flow);
out_put_sock:
	usnic_transport_put_socket(sock);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम release_udp_flow(काष्ठा usnic_ib_qp_grp_flow *qp_flow)
अणु
	usnic_fwd_dealloc_flow(qp_flow->flow);
	usnic_transport_put_socket(qp_flow->udp.sock);
	kमुक्त(qp_flow);
पूर्ण

अटल काष्ठा usnic_ib_qp_grp_flow*
create_and_add_flow(काष्ठा usnic_ib_qp_grp *qp_grp,
			काष्ठा usnic_transport_spec *trans_spec)
अणु
	काष्ठा usnic_ib_qp_grp_flow *qp_flow;
	क्रमागत usnic_transport_type trans_type;

	trans_type = trans_spec->trans_type;
	चयन (trans_type) अणु
	हाल USNIC_TRANSPORT_ROCE_CUSTOM:
		qp_flow = create_roce_custom_flow(qp_grp, trans_spec);
		अवरोध;
	हाल USNIC_TRANSPORT_IPV4_UDP:
		qp_flow = create_udp_flow(qp_grp, trans_spec);
		अवरोध;
	शेष:
		usnic_err("Unsupported transport %u\n",
				trans_spec->trans_type);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(qp_flow)) अणु
		list_add_tail(&qp_flow->link, &qp_grp->flows_lst);
		usnic_debugfs_flow_add(qp_flow);
	पूर्ण


	वापस qp_flow;
पूर्ण

अटल व्योम release_and_हटाओ_flow(काष्ठा usnic_ib_qp_grp_flow *qp_flow)
अणु
	usnic_debugfs_flow_हटाओ(qp_flow);
	list_del(&qp_flow->link);

	चयन (qp_flow->trans_type) अणु
	हाल USNIC_TRANSPORT_ROCE_CUSTOM:
		release_roce_custom_flow(qp_flow);
		अवरोध;
	हाल USNIC_TRANSPORT_IPV4_UDP:
		release_udp_flow(qp_flow);
		अवरोध;
	शेष:
		WARN(1, "Unsupported transport %u\n",
				qp_flow->trans_type);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम release_and_हटाओ_all_flows(काष्ठा usnic_ib_qp_grp *qp_grp)
अणु
	काष्ठा usnic_ib_qp_grp_flow *qp_flow, *पंचांगp;
	list_क्रम_each_entry_safe(qp_flow, पंचांगp, &qp_grp->flows_lst, link)
		release_and_हटाओ_flow(qp_flow);
पूर्ण

पूर्णांक usnic_ib_qp_grp_modअगरy(काष्ठा usnic_ib_qp_grp *qp_grp,
				क्रमागत ib_qp_state new_state,
				व्योम *data)
अणु
	पूर्णांक status = 0;
	काष्ठा ib_event ib_event;
	क्रमागत ib_qp_state old_state;
	काष्ठा usnic_transport_spec *trans_spec;
	काष्ठा usnic_ib_qp_grp_flow *qp_flow;

	old_state = qp_grp->state;
	trans_spec = (काष्ठा usnic_transport_spec *) data;

	spin_lock(&qp_grp->lock);
	चयन (new_state) अणु
	हाल IB_QPS_RESET:
		चयन (old_state) अणु
		हाल IB_QPS_RESET:
			/* NO-OP */
			अवरोध;
		हाल IB_QPS_INIT:
			release_and_हटाओ_all_flows(qp_grp);
			status = 0;
			अवरोध;
		हाल IB_QPS_RTR:
		हाल IB_QPS_RTS:
		हाल IB_QPS_ERR:
			status = disable_qp_grp(qp_grp);
			release_and_हटाओ_all_flows(qp_grp);
			अवरोध;
		शेष:
			status = -EINVAL;
		पूर्ण
		अवरोध;
	हाल IB_QPS_INIT:
		चयन (old_state) अणु
		हाल IB_QPS_RESET:
			अगर (trans_spec) अणु
				qp_flow = create_and_add_flow(qp_grp,
								trans_spec);
				अगर (IS_ERR_OR_शून्य(qp_flow)) अणु
					status = qp_flow ? PTR_ERR(qp_flow) : -EFAULT;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				/*
				 * Optional to specअगरy filters.
				 */
				status = 0;
			पूर्ण
			अवरोध;
		हाल IB_QPS_INIT:
			अगर (trans_spec) अणु
				qp_flow = create_and_add_flow(qp_grp,
								trans_spec);
				अगर (IS_ERR_OR_शून्य(qp_flow)) अणु
					status = qp_flow ? PTR_ERR(qp_flow) : -EFAULT;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				/*
				 * Doesn't make sense to go पूर्णांकo INIT state
				 * from INIT state w/o adding filters.
				 */
				status = -EINVAL;
			पूर्ण
			अवरोध;
		हाल IB_QPS_RTR:
			status = disable_qp_grp(qp_grp);
			अवरोध;
		हाल IB_QPS_RTS:
			status = disable_qp_grp(qp_grp);
			अवरोध;
		शेष:
			status = -EINVAL;
		पूर्ण
		अवरोध;
	हाल IB_QPS_RTR:
		चयन (old_state) अणु
		हाल IB_QPS_INIT:
			status = enable_qp_grp(qp_grp);
			अवरोध;
		शेष:
			status = -EINVAL;
		पूर्ण
		अवरोध;
	हाल IB_QPS_RTS:
		चयन (old_state) अणु
		हाल IB_QPS_RTR:
			/* NO-OP FOR NOW */
			अवरोध;
		शेष:
			status = -EINVAL;
		पूर्ण
		अवरोध;
	हाल IB_QPS_ERR:
		ib_event.device = &qp_grp->vf->pf->ib_dev;
		ib_event.element.qp = &qp_grp->ibqp;
		ib_event.event = IB_EVENT_QP_FATAL;

		चयन (old_state) अणु
		हाल IB_QPS_RESET:
			qp_grp->ibqp.event_handler(&ib_event,
					qp_grp->ibqp.qp_context);
			अवरोध;
		हाल IB_QPS_INIT:
			release_and_हटाओ_all_flows(qp_grp);
			qp_grp->ibqp.event_handler(&ib_event,
					qp_grp->ibqp.qp_context);
			अवरोध;
		हाल IB_QPS_RTR:
		हाल IB_QPS_RTS:
			status = disable_qp_grp(qp_grp);
			release_and_हटाओ_all_flows(qp_grp);
			qp_grp->ibqp.event_handler(&ib_event,
					qp_grp->ibqp.qp_context);
			अवरोध;
		शेष:
			status = -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		status = -EINVAL;
	पूर्ण
	spin_unlock(&qp_grp->lock);

	अगर (!status) अणु
		qp_grp->state = new_state;
		usnic_info("Transitioned %u from %s to %s",
		qp_grp->grp_id,
		usnic_ib_qp_grp_state_to_string(old_state),
		usnic_ib_qp_grp_state_to_string(new_state));
	पूर्ण अन्यथा अणु
		usnic_err("Failed to transition %u from %s to %s",
		qp_grp->grp_id,
		usnic_ib_qp_grp_state_to_string(old_state),
		usnic_ib_qp_grp_state_to_string(new_state));
	पूर्ण

	वापस status;
पूर्ण

अटल काष्ठा usnic_vnic_res_chunk**
alloc_res_chunk_list(काष्ठा usnic_vnic *vnic,
			काष्ठा usnic_vnic_res_spec *res_spec, व्योम *owner_obj)
अणु
	क्रमागत usnic_vnic_res_type res_type;
	काष्ठा usnic_vnic_res_chunk **res_chunk_list;
	पूर्णांक err, i, res_cnt, res_lst_sz;

	क्रम (res_lst_sz = 0;
		res_spec->resources[res_lst_sz].type != USNIC_VNIC_RES_TYPE_EOL;
		res_lst_sz++) अणु
		/* Do Nothing */
	पूर्ण

	res_chunk_list = kसुस्मृति(res_lst_sz + 1, माप(*res_chunk_list),
					GFP_ATOMIC);
	अगर (!res_chunk_list)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; res_spec->resources[i].type != USNIC_VNIC_RES_TYPE_EOL;
		i++) अणु
		res_type = res_spec->resources[i].type;
		res_cnt = res_spec->resources[i].cnt;

		res_chunk_list[i] = usnic_vnic_get_resources(vnic, res_type,
					res_cnt, owner_obj);
		अगर (IS_ERR_OR_शून्य(res_chunk_list[i])) अणु
			err = res_chunk_list[i] ?
					PTR_ERR(res_chunk_list[i]) : -ENOMEM;
			usnic_err("Failed to get %s from %s with err %d\n",
				usnic_vnic_res_type_to_str(res_type),
				usnic_vnic_pci_name(vnic),
				err);
			जाओ out_मुक्त_res;
		पूर्ण
	पूर्ण

	वापस res_chunk_list;

out_मुक्त_res:
	क्रम (i--; i >= 0; i--)
		usnic_vnic_put_resources(res_chunk_list[i]);
	kमुक्त(res_chunk_list);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम मुक्त_qp_grp_res(काष्ठा usnic_vnic_res_chunk **res_chunk_list)
अणु
	पूर्णांक i;
	क्रम (i = 0; res_chunk_list[i]; i++)
		usnic_vnic_put_resources(res_chunk_list[i]);
	kमुक्त(res_chunk_list);
पूर्ण

अटल पूर्णांक qp_grp_and_vf_bind(काष्ठा usnic_ib_vf *vf,
				काष्ठा usnic_ib_pd *pd,
				काष्ठा usnic_ib_qp_grp *qp_grp)
अणु
	पूर्णांक err;
	काष्ठा pci_dev *pdev;

	lockdep_निश्चित_held(&vf->lock);

	pdev = usnic_vnic_get_pdev(vf->vnic);
	अगर (vf->qp_grp_ref_cnt == 0) अणु
		err = usnic_uiom_attach_dev_to_pd(pd->umem_pd, &pdev->dev);
		अगर (err) अणु
			usnic_err("Failed to attach %s to domain\n",
					pci_name(pdev));
			वापस err;
		पूर्ण
		vf->pd = pd;
	पूर्ण
	vf->qp_grp_ref_cnt++;

	WARN_ON(vf->pd != pd);
	qp_grp->vf = vf;

	वापस 0;
पूर्ण

अटल व्योम qp_grp_and_vf_unbind(काष्ठा usnic_ib_qp_grp *qp_grp)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा usnic_ib_pd *pd;

	lockdep_निश्चित_held(&qp_grp->vf->lock);

	pd = qp_grp->vf->pd;
	pdev = usnic_vnic_get_pdev(qp_grp->vf->vnic);
	अगर (--qp_grp->vf->qp_grp_ref_cnt == 0) अणु
		qp_grp->vf->pd = शून्य;
		usnic_uiom_detach_dev_from_pd(pd->umem_pd, &pdev->dev);
	पूर्ण
	qp_grp->vf = शून्य;
पूर्ण

अटल व्योम log_spec(काष्ठा usnic_vnic_res_spec *res_spec)
अणु
	अक्षर buf[512];
	usnic_vnic_spec_dump(buf, माप(buf), res_spec);
	usnic_dbg("%s\n", buf);
पूर्ण

अटल पूर्णांक qp_grp_id_from_flow(काष्ठा usnic_ib_qp_grp_flow *qp_flow,
				uपूर्णांक32_t *id)
अणु
	क्रमागत usnic_transport_type trans_type = qp_flow->trans_type;
	पूर्णांक err;
	uपूर्णांक16_t port_num = 0;

	चयन (trans_type) अणु
	हाल USNIC_TRANSPORT_ROCE_CUSTOM:
		*id = qp_flow->usnic_roce.port_num;
		अवरोध;
	हाल USNIC_TRANSPORT_IPV4_UDP:
		err = usnic_transport_sock_get_addr(qp_flow->udp.sock,
							शून्य, शून्य,
							&port_num);
		अगर (err)
			वापस err;
		/*
		 * Copy port_num to stack first and then to *id,
		 * so that the लघु to पूर्णांक cast works क्रम little
		 * and big endian प्रणालीs.
		 */
		*id = port_num;
		अवरोध;
	शेष:
		usnic_err("Unsupported transport %u\n", trans_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा usnic_ib_qp_grp *
usnic_ib_qp_grp_create(काष्ठा usnic_fwd_dev *ufdev, काष्ठा usnic_ib_vf *vf,
			काष्ठा usnic_ib_pd *pd,
			काष्ठा usnic_vnic_res_spec *res_spec,
			काष्ठा usnic_transport_spec *transport_spec)
अणु
	काष्ठा usnic_ib_qp_grp *qp_grp;
	पूर्णांक err;
	क्रमागत usnic_transport_type transport = transport_spec->trans_type;
	काष्ठा usnic_ib_qp_grp_flow *qp_flow;

	lockdep_निश्चित_held(&vf->lock);

	err = usnic_vnic_res_spec_satisfied(&min_transport_spec[transport],
						res_spec);
	अगर (err) अणु
		usnic_err("Spec does not meet minimum req for transport %d\n",
				transport);
		log_spec(res_spec);
		वापस ERR_PTR(err);
	पूर्ण

	qp_grp = kzalloc(माप(*qp_grp), GFP_ATOMIC);
	अगर (!qp_grp)
		वापस शून्य;

	qp_grp->res_chunk_list = alloc_res_chunk_list(vf->vnic, res_spec,
							qp_grp);
	अगर (IS_ERR_OR_शून्य(qp_grp->res_chunk_list)) अणु
		err = qp_grp->res_chunk_list ?
				PTR_ERR(qp_grp->res_chunk_list) : -ENOMEM;
		जाओ out_मुक्त_qp_grp;
	पूर्ण

	err = qp_grp_and_vf_bind(vf, pd, qp_grp);
	अगर (err)
		जाओ out_मुक्त_res;

	INIT_LIST_HEAD(&qp_grp->flows_lst);
	spin_lock_init(&qp_grp->lock);
	qp_grp->ufdev = ufdev;
	qp_grp->state = IB_QPS_RESET;
	qp_grp->owner_pid = current->pid;

	qp_flow = create_and_add_flow(qp_grp, transport_spec);
	अगर (IS_ERR_OR_शून्य(qp_flow)) अणु
		usnic_err("Unable to create and add flow with err %ld\n",
				PTR_ERR(qp_flow));
		err = qp_flow ? PTR_ERR(qp_flow) : -EFAULT;
		जाओ out_qp_grp_vf_unbind;
	पूर्ण

	err = qp_grp_id_from_flow(qp_flow, &qp_grp->grp_id);
	अगर (err)
		जाओ out_release_flow;
	qp_grp->ibqp.qp_num = qp_grp->grp_id;

	usnic_ib_sysfs_qpn_add(qp_grp);

	वापस qp_grp;

out_release_flow:
	release_and_हटाओ_flow(qp_flow);
out_qp_grp_vf_unbind:
	qp_grp_and_vf_unbind(qp_grp);
out_मुक्त_res:
	मुक्त_qp_grp_res(qp_grp->res_chunk_list);
out_मुक्त_qp_grp:
	kमुक्त(qp_grp);

	वापस ERR_PTR(err);
पूर्ण

व्योम usnic_ib_qp_grp_destroy(काष्ठा usnic_ib_qp_grp *qp_grp)
अणु

	WARN_ON(qp_grp->state != IB_QPS_RESET);
	lockdep_निश्चित_held(&qp_grp->vf->lock);

	release_and_हटाओ_all_flows(qp_grp);
	usnic_ib_sysfs_qpn_हटाओ(qp_grp);
	qp_grp_and_vf_unbind(qp_grp);
	मुक्त_qp_grp_res(qp_grp->res_chunk_list);
	kमुक्त(qp_grp);
पूर्ण

काष्ठा usnic_vnic_res_chunk*
usnic_ib_qp_grp_get_chunk(काष्ठा usnic_ib_qp_grp *qp_grp,
				क्रमागत usnic_vnic_res_type res_type)
अणु
	पूर्णांक i;

	क्रम (i = 0; qp_grp->res_chunk_list[i]; i++) अणु
		अगर (qp_grp->res_chunk_list[i]->type == res_type)
			वापस qp_grp->res_chunk_list[i];
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण
