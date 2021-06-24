<शैली गुरु>
/* QLogic qedr NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
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
 *        disclaimer in the करोcumentation and /or other materials
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
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/udp.h>
#समावेश <net/addrconf.h>
#समावेश <net/route.h>
#समावेश <net/ip6_route.h>
#समावेश <net/flow.h>
#समावेश "qedr.h"
#समावेश "qedr_iw_cm.h"

अटल अंतरभूत व्योम
qedr_fill_sockaddr4(स्थिर काष्ठा qed_iwarp_cm_info *cm_info,
		    काष्ठा iw_cm_event *event)
अणु
	काष्ठा sockaddr_in *laddr = (काष्ठा sockaddr_in *)&event->local_addr;
	काष्ठा sockaddr_in *raddr = (काष्ठा sockaddr_in *)&event->remote_addr;

	laddr->sin_family = AF_INET;
	raddr->sin_family = AF_INET;

	laddr->sin_port = htons(cm_info->local_port);
	raddr->sin_port = htons(cm_info->remote_port);

	laddr->sin_addr.s_addr = htonl(cm_info->local_ip[0]);
	raddr->sin_addr.s_addr = htonl(cm_info->remote_ip[0]);
पूर्ण

अटल अंतरभूत व्योम
qedr_fill_sockaddr6(स्थिर काष्ठा qed_iwarp_cm_info *cm_info,
		    काष्ठा iw_cm_event *event)
अणु
	काष्ठा sockaddr_in6 *laddr6 = (काष्ठा sockaddr_in6 *)&event->local_addr;
	काष्ठा sockaddr_in6 *raddr6 =
	    (काष्ठा sockaddr_in6 *)&event->remote_addr;
	पूर्णांक i;

	laddr6->sin6_family = AF_INET6;
	raddr6->sin6_family = AF_INET6;

	laddr6->sin6_port = htons(cm_info->local_port);
	raddr6->sin6_port = htons(cm_info->remote_port);

	क्रम (i = 0; i < 4; i++) अणु
		laddr6->sin6_addr.in6_u.u6_addr32[i] =
		    htonl(cm_info->local_ip[i]);
		raddr6->sin6_addr.in6_u.u6_addr32[i] =
		    htonl(cm_info->remote_ip[i]);
	पूर्ण
पूर्ण

अटल व्योम qedr_iw_मुक्त_qp(काष्ठा kref *ref)
अणु
	काष्ठा qedr_qp *qp = container_of(ref, काष्ठा qedr_qp, refcnt);

	kमुक्त(qp);
पूर्ण

अटल व्योम
qedr_iw_मुक्त_ep(काष्ठा kref *ref)
अणु
	काष्ठा qedr_iw_ep *ep = container_of(ref, काष्ठा qedr_iw_ep, refcnt);

	अगर (ep->qp)
		kref_put(&ep->qp->refcnt, qedr_iw_मुक्त_qp);

	अगर (ep->cm_id)
		ep->cm_id->rem_ref(ep->cm_id);

	kमुक्त(ep);
पूर्ण

अटल व्योम
qedr_iw_mpa_request(व्योम *context, काष्ठा qed_iwarp_cm_event_params *params)
अणु
	काष्ठा qedr_iw_listener *listener = (काष्ठा qedr_iw_listener *)context;
	काष्ठा qedr_dev *dev = listener->dev;
	काष्ठा iw_cm_event event;
	काष्ठा qedr_iw_ep *ep;

	ep = kzalloc(माप(*ep), GFP_ATOMIC);
	अगर (!ep)
		वापस;

	ep->dev = dev;
	ep->qed_context = params->ep_context;
	kref_init(&ep->refcnt);

	स_रखो(&event, 0, माप(event));
	event.event = IW_CM_EVENT_CONNECT_REQUEST;
	event.status = params->status;

	अगर (!IS_ENABLED(CONFIG_IPV6) ||
	    params->cm_info->ip_version == QED_TCP_IPV4)
		qedr_fill_sockaddr4(params->cm_info, &event);
	अन्यथा
		qedr_fill_sockaddr6(params->cm_info, &event);

	event.provider_data = (व्योम *)ep;
	event.निजी_data = (व्योम *)params->cm_info->निजी_data;
	event.निजी_data_len = (u8)params->cm_info->निजी_data_len;
	event.ord = params->cm_info->ord;
	event.ird = params->cm_info->ird;

	listener->cm_id->event_handler(listener->cm_id, &event);
पूर्ण

अटल व्योम
qedr_iw_issue_event(व्योम *context,
		    काष्ठा qed_iwarp_cm_event_params *params,
		    क्रमागत iw_cm_event_type event_type)
अणु
	काष्ठा qedr_iw_ep *ep = (काष्ठा qedr_iw_ep *)context;
	काष्ठा iw_cm_event event;

	स_रखो(&event, 0, माप(event));
	event.status = params->status;
	event.event = event_type;

	अगर (params->cm_info) अणु
		event.ird = params->cm_info->ird;
		event.ord = params->cm_info->ord;
		/* Only connect_request and reply have valid निजी data
		 * the rest of the events this may be left overs from
		 * connection establishment. CONNECT_REQUEST is issued via
		 * qedr_iw_mpa_request
		 */
		अगर (event_type == IW_CM_EVENT_CONNECT_REPLY) अणु
			event.निजी_data_len =
				params->cm_info->निजी_data_len;
			event.निजी_data =
				(व्योम *)params->cm_info->निजी_data;
		पूर्ण
	पूर्ण

	अगर (ep->cm_id)
		ep->cm_id->event_handler(ep->cm_id, &event);
पूर्ण

अटल व्योम
qedr_iw_बंद_event(व्योम *context, काष्ठा qed_iwarp_cm_event_params *params)
अणु
	काष्ठा qedr_iw_ep *ep = (काष्ठा qedr_iw_ep *)context;

	अगर (ep->cm_id)
		qedr_iw_issue_event(context, params, IW_CM_EVENT_CLOSE);

	kref_put(&ep->refcnt, qedr_iw_मुक्त_ep);
पूर्ण

अटल व्योम
qedr_iw_qp_event(व्योम *context,
		 काष्ठा qed_iwarp_cm_event_params *params,
		 क्रमागत ib_event_type ib_event, अक्षर *str)
अणु
	काष्ठा qedr_iw_ep *ep = (काष्ठा qedr_iw_ep *)context;
	काष्ठा qedr_dev *dev = ep->dev;
	काष्ठा ib_qp *ibqp = &ep->qp->ibqp;
	काष्ठा ib_event event;

	DP_NOTICE(dev, "QP error received: %s\n", str);

	अगर (ibqp->event_handler) अणु
		event.event = ib_event;
		event.device = ibqp->device;
		event.element.qp = ibqp;
		ibqp->event_handler(&event, ibqp->qp_context);
	पूर्ण
पूर्ण

काष्ठा qedr_discon_work अणु
	काष्ठा work_काष्ठा		work;
	काष्ठा qedr_iw_ep		*ep;
	क्रमागत qed_iwarp_event_type	event;
	पूर्णांक				status;
पूर्ण;

अटल व्योम qedr_iw_disconnect_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qedr_discon_work *dwork =
	    container_of(work, काष्ठा qedr_discon_work, work);
	काष्ठा qed_rdma_modअगरy_qp_in_params qp_params = अणु 0 पूर्ण;
	काष्ठा qedr_iw_ep *ep = dwork->ep;
	काष्ठा qedr_dev *dev = ep->dev;
	काष्ठा qedr_qp *qp = ep->qp;
	काष्ठा iw_cm_event event;

	/* The qp won't be released until we release the ep.
	 * the ep's refcnt was increased beक्रमe calling this
	 * function, thereक्रमe it is safe to access qp
	 */
	अगर (test_and_set_bit(QEDR_IWARP_CM_WAIT_FOR_DISCONNECT,
			     &qp->iwarp_cm_flags))
		जाओ out;

	स_रखो(&event, 0, माप(event));
	event.status = dwork->status;
	event.event = IW_CM_EVENT_DISCONNECT;

	/* Success means graceful disconnect was requested. modअगरying
	 * to SQD is translated to graceful disconnect. O/w reset is sent
	 */
	अगर (dwork->status)
		qp_params.new_state = QED_ROCE_QP_STATE_ERR;
	अन्यथा
		qp_params.new_state = QED_ROCE_QP_STATE_SQD;


	अगर (ep->cm_id)
		ep->cm_id->event_handler(ep->cm_id, &event);

	SET_FIELD(qp_params.modअगरy_flags,
		  QED_RDMA_MODIFY_QP_VALID_NEW_STATE, 1);

	dev->ops->rdma_modअगरy_qp(dev->rdma_ctx, qp->qed_qp, &qp_params);

	complete(&ep->qp->iwarp_cm_comp);
out:
	kमुक्त(dwork);
	kref_put(&ep->refcnt, qedr_iw_मुक्त_ep);
पूर्ण

अटल व्योम
qedr_iw_disconnect_event(व्योम *context,
			 काष्ठा qed_iwarp_cm_event_params *params)
अणु
	काष्ठा qedr_discon_work *work;
	काष्ठा qedr_iw_ep *ep = (काष्ठा qedr_iw_ep *)context;
	काष्ठा qedr_dev *dev = ep->dev;

	work = kzalloc(माप(*work), GFP_ATOMIC);
	अगर (!work)
		वापस;

	/* We can't get a बंद event beक्रमe disconnect, but since
	 * we're scheduling a work queue we need to make sure बंद
	 * won't delete the ep, so we increase the refcnt
	 */
	kref_get(&ep->refcnt);

	work->ep = ep;
	work->event = params->event;
	work->status = params->status;

	INIT_WORK(&work->work, qedr_iw_disconnect_worker);
	queue_work(dev->iwarp_wq, &work->work);
पूर्ण

अटल व्योम
qedr_iw_passive_complete(व्योम *context,
			 काष्ठा qed_iwarp_cm_event_params *params)
अणु
	काष्ठा qedr_iw_ep *ep = (काष्ठा qedr_iw_ep *)context;
	काष्ठा qedr_dev *dev = ep->dev;

	/* We will only reach the following state अगर MPA_REJECT was called on
	 * passive. In this हाल there will be no associated QP.
	 */
	अगर ((params->status == -ECONNREFUSED) && (!ep->qp)) अणु
		DP_DEBUG(dev, QEDR_MSG_IWARP,
			 "PASSIVE connection refused releasing ep...\n");
		kref_put(&ep->refcnt, qedr_iw_मुक्त_ep);
		वापस;
	पूर्ण

	complete(&ep->qp->iwarp_cm_comp);
	qedr_iw_issue_event(context, params, IW_CM_EVENT_ESTABLISHED);

	अगर (params->status < 0)
		qedr_iw_बंद_event(context, params);
पूर्ण

अटल व्योम
qedr_iw_active_complete(व्योम *context,
			काष्ठा qed_iwarp_cm_event_params *params)
अणु
	काष्ठा qedr_iw_ep *ep = (काष्ठा qedr_iw_ep *)context;

	complete(&ep->qp->iwarp_cm_comp);
	qedr_iw_issue_event(context, params, IW_CM_EVENT_CONNECT_REPLY);

	अगर (params->status < 0)
		kref_put(&ep->refcnt, qedr_iw_मुक्त_ep);
पूर्ण

अटल पूर्णांक
qedr_iw_mpa_reply(व्योम *context, काष्ठा qed_iwarp_cm_event_params *params)
अणु
	काष्ठा qedr_iw_ep *ep = (काष्ठा qedr_iw_ep *)context;
	काष्ठा qedr_dev *dev = ep->dev;
	काष्ठा qed_iwarp_send_rtr_in rtr_in;

	rtr_in.ep_context = params->ep_context;

	वापस dev->ops->iwarp_send_rtr(dev->rdma_ctx, &rtr_in);
पूर्ण

अटल पूर्णांक
qedr_iw_event_handler(व्योम *context, काष्ठा qed_iwarp_cm_event_params *params)
अणु
	काष्ठा qedr_iw_ep *ep = (काष्ठा qedr_iw_ep *)context;
	काष्ठा qedr_dev *dev = ep->dev;

	चयन (params->event) अणु
	हाल QED_IWARP_EVENT_MPA_REQUEST:
		qedr_iw_mpa_request(context, params);
		अवरोध;
	हाल QED_IWARP_EVENT_ACTIVE_MPA_REPLY:
		qedr_iw_mpa_reply(context, params);
		अवरोध;
	हाल QED_IWARP_EVENT_PASSIVE_COMPLETE:
		qedr_iw_passive_complete(context, params);
		अवरोध;
	हाल QED_IWARP_EVENT_ACTIVE_COMPLETE:
		qedr_iw_active_complete(context, params);
		अवरोध;
	हाल QED_IWARP_EVENT_DISCONNECT:
		qedr_iw_disconnect_event(context, params);
		अवरोध;
	हाल QED_IWARP_EVENT_CLOSE:
		qedr_iw_बंद_event(context, params);
		अवरोध;
	हाल QED_IWARP_EVENT_RQ_EMPTY:
		qedr_iw_qp_event(context, params, IB_EVENT_QP_FATAL,
				 "QED_IWARP_EVENT_RQ_EMPTY");
		अवरोध;
	हाल QED_IWARP_EVENT_IRQ_FULL:
		qedr_iw_qp_event(context, params, IB_EVENT_QP_FATAL,
				 "QED_IWARP_EVENT_IRQ_FULL");
		अवरोध;
	हाल QED_IWARP_EVENT_LLP_TIMEOUT:
		qedr_iw_qp_event(context, params, IB_EVENT_QP_FATAL,
				 "QED_IWARP_EVENT_LLP_TIMEOUT");
		अवरोध;
	हाल QED_IWARP_EVENT_REMOTE_PROTECTION_ERROR:
		qedr_iw_qp_event(context, params, IB_EVENT_QP_ACCESS_ERR,
				 "QED_IWARP_EVENT_REMOTE_PROTECTION_ERROR");
		अवरोध;
	हाल QED_IWARP_EVENT_CQ_OVERFLOW:
		qedr_iw_qp_event(context, params, IB_EVENT_QP_FATAL,
				 "QED_IWARP_EVENT_CQ_OVERFLOW");
		अवरोध;
	हाल QED_IWARP_EVENT_QP_CATASTROPHIC:
		qedr_iw_qp_event(context, params, IB_EVENT_QP_FATAL,
				 "QED_IWARP_EVENT_QP_CATASTROPHIC");
		अवरोध;
	हाल QED_IWARP_EVENT_LOCAL_ACCESS_ERROR:
		qedr_iw_qp_event(context, params, IB_EVENT_QP_ACCESS_ERR,
				 "QED_IWARP_EVENT_LOCAL_ACCESS_ERROR");
		अवरोध;
	हाल QED_IWARP_EVENT_REMOTE_OPERATION_ERROR:
		qedr_iw_qp_event(context, params, IB_EVENT_QP_FATAL,
				 "QED_IWARP_EVENT_REMOTE_OPERATION_ERROR");
		अवरोध;
	हाल QED_IWARP_EVENT_TERMINATE_RECEIVED:
		DP_NOTICE(dev, "Got terminate message\n");
		अवरोध;
	शेष:
		DP_NOTICE(dev, "Unknown event received %d\n", params->event);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल u16 qedr_iw_get_vlan_ipv4(काष्ठा qedr_dev *dev, u32 *addr)
अणु
	काष्ठा net_device *ndev;
	u16 vlan_id = 0;

	ndev = ip_dev_find(&init_net, htonl(addr[0]));

	अगर (ndev) अणु
		vlan_id = rdma_vlan_dev_vlan_id(ndev);
		dev_put(ndev);
	पूर्ण
	अगर (vlan_id == 0xffff)
		vlan_id = 0;
	वापस vlan_id;
पूर्ण

अटल u16 qedr_iw_get_vlan_ipv6(u32 *addr)
अणु
	काष्ठा net_device *ndev = शून्य;
	काष्ठा in6_addr laddr6;
	u16 vlan_id = 0;
	पूर्णांक i;

	अगर (!IS_ENABLED(CONFIG_IPV6))
		वापस vlan_id;

	क्रम (i = 0; i < 4; i++)
		laddr6.in6_u.u6_addr32[i] = htonl(addr[i]);

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, ndev) अणु
		अगर (ipv6_chk_addr(&init_net, &laddr6, ndev, 1)) अणु
			vlan_id = rdma_vlan_dev_vlan_id(ndev);
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	अगर (vlan_id == 0xffff)
		vlan_id = 0;

	वापस vlan_id;
पूर्ण

अटल पूर्णांक
qedr_addr4_resolve(काष्ठा qedr_dev *dev,
		   काष्ठा sockaddr_in *src_in,
		   काष्ठा sockaddr_in *dst_in, u8 *dst_mac)
अणु
	__be32 src_ip = src_in->sin_addr.s_addr;
	__be32 dst_ip = dst_in->sin_addr.s_addr;
	काष्ठा neighbour *neigh = शून्य;
	काष्ठा rtable *rt = शून्य;
	पूर्णांक rc = 0;

	rt = ip_route_output(&init_net, dst_ip, src_ip, 0, 0);
	अगर (IS_ERR(rt)) अणु
		DP_ERR(dev, "ip_route_output returned error\n");
		वापस -EINVAL;
	पूर्ण

	neigh = dst_neigh_lookup(&rt->dst, &dst_ip);

	अगर (neigh) अणु
		rcu_पढ़ो_lock();
		अगर (neigh->nud_state & NUD_VALID) अणु
			ether_addr_copy(dst_mac, neigh->ha);
			DP_DEBUG(dev, QEDR_MSG_QP, "mac_addr=[%pM]\n", dst_mac);
		पूर्ण अन्यथा अणु
			neigh_event_send(neigh, शून्य);
		पूर्ण
		rcu_पढ़ो_unlock();
		neigh_release(neigh);
	पूर्ण

	ip_rt_put(rt);

	वापस rc;
पूर्ण

अटल पूर्णांक
qedr_addr6_resolve(काष्ठा qedr_dev *dev,
		   काष्ठा sockaddr_in6 *src_in,
		   काष्ठा sockaddr_in6 *dst_in, u8 *dst_mac)
अणु
	काष्ठा neighbour *neigh = शून्य;
	काष्ठा dst_entry *dst;
	काष्ठा flowi6 fl6;
	पूर्णांक rc = 0;

	स_रखो(&fl6, 0, माप(fl6));
	fl6.daddr = dst_in->sin6_addr;
	fl6.saddr = src_in->sin6_addr;

	dst = ip6_route_output(&init_net, शून्य, &fl6);

	अगर ((!dst) || dst->error) अणु
		अगर (dst) अणु
			DP_ERR(dev,
			       "ip6_route_output returned dst->error = %d\n",
			       dst->error);
			dst_release(dst);
		पूर्ण
		वापस -EINVAL;
	पूर्ण
	neigh = dst_neigh_lookup(dst, &fl6.daddr);
	अगर (neigh) अणु
		rcu_पढ़ो_lock();
		अगर (neigh->nud_state & NUD_VALID) अणु
			ether_addr_copy(dst_mac, neigh->ha);
			DP_DEBUG(dev, QEDR_MSG_QP, "mac_addr=[%pM]\n", dst_mac);
		पूर्ण अन्यथा अणु
			neigh_event_send(neigh, शून्य);
		पूर्ण
		rcu_पढ़ो_unlock();
		neigh_release(neigh);
	पूर्ण

	dst_release(dst);

	वापस rc;
पूर्ण

अटल काष्ठा qedr_qp *qedr_iw_load_qp(काष्ठा qedr_dev *dev, u32 qpn)
अणु
	काष्ठा qedr_qp *qp;

	xa_lock(&dev->qps);
	qp = xa_load(&dev->qps, qpn);
	अगर (qp)
		kref_get(&qp->refcnt);
	xa_unlock(&dev->qps);

	वापस qp;
पूर्ण

पूर्णांक qedr_iw_connect(काष्ठा iw_cm_id *cm_id, काष्ठा iw_cm_conn_param *conn_param)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(cm_id->device);
	काष्ठा qed_iwarp_connect_out out_params;
	काष्ठा qed_iwarp_connect_in in_params;
	काष्ठा qed_iwarp_cm_info *cm_info;
	काष्ठा sockaddr_in6 *laddr6;
	काष्ठा sockaddr_in6 *raddr6;
	काष्ठा sockaddr_in *laddr;
	काष्ठा sockaddr_in *raddr;
	काष्ठा qedr_iw_ep *ep;
	काष्ठा qedr_qp *qp;
	पूर्णांक rc = 0;
	पूर्णांक i;

	laddr = (काष्ठा sockaddr_in *)&cm_id->m_local_addr;
	raddr = (काष्ठा sockaddr_in *)&cm_id->m_remote_addr;
	laddr6 = (काष्ठा sockaddr_in6 *)&cm_id->m_local_addr;
	raddr6 = (काष्ठा sockaddr_in6 *)&cm_id->m_remote_addr;

	DP_DEBUG(dev, QEDR_MSG_IWARP, "MAPPED %d %d\n",
		 ntohs(((काष्ठा sockaddr_in *)&cm_id->remote_addr)->sin_port),
		 ntohs(raddr->sin_port));

	DP_DEBUG(dev, QEDR_MSG_IWARP,
		 "Connect source address: %pISpc, remote address: %pISpc\n",
		 &cm_id->local_addr, &cm_id->remote_addr);

	अगर (!laddr->sin_port || !raddr->sin_port)
		वापस -EINVAL;

	ep = kzalloc(माप(*ep), GFP_KERNEL);
	अगर (!ep)
		वापस -ENOMEM;

	ep->dev = dev;
	kref_init(&ep->refcnt);

	qp = qedr_iw_load_qp(dev, conn_param->qpn);
	अगर (!qp) अणु
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	ep->qp = qp;
	cm_id->add_ref(cm_id);
	ep->cm_id = cm_id;

	in_params.event_cb = qedr_iw_event_handler;
	in_params.cb_context = ep;

	cm_info = &in_params.cm_info;
	स_रखो(cm_info->local_ip, 0, माप(cm_info->local_ip));
	स_रखो(cm_info->remote_ip, 0, माप(cm_info->remote_ip));

	अगर (!IS_ENABLED(CONFIG_IPV6) ||
	    cm_id->remote_addr.ss_family == AF_INET) अणु
		cm_info->ip_version = QED_TCP_IPV4;

		cm_info->remote_ip[0] = ntohl(raddr->sin_addr.s_addr);
		cm_info->local_ip[0] = ntohl(laddr->sin_addr.s_addr);
		cm_info->remote_port = ntohs(raddr->sin_port);
		cm_info->local_port = ntohs(laddr->sin_port);
		cm_info->vlan = qedr_iw_get_vlan_ipv4(dev, cm_info->local_ip);

		rc = qedr_addr4_resolve(dev, laddr, raddr,
					(u8 *)in_params.remote_mac_addr);

		in_params.mss = dev->iwarp_max_mtu -
		    (माप(काष्ठा iphdr) + माप(काष्ठा tcphdr));

	पूर्ण अन्यथा अणु
		in_params.cm_info.ip_version = QED_TCP_IPV6;

		क्रम (i = 0; i < 4; i++) अणु
			cm_info->remote_ip[i] =
			    ntohl(raddr6->sin6_addr.in6_u.u6_addr32[i]);
			cm_info->local_ip[i] =
			    ntohl(laddr6->sin6_addr.in6_u.u6_addr32[i]);
		पूर्ण

		cm_info->local_port = ntohs(laddr6->sin6_port);
		cm_info->remote_port = ntohs(raddr6->sin6_port);

		in_params.mss = dev->iwarp_max_mtu -
		    (माप(काष्ठा ipv6hdr) + माप(काष्ठा tcphdr));

		cm_info->vlan = qedr_iw_get_vlan_ipv6(cm_info->local_ip);

		rc = qedr_addr6_resolve(dev, laddr6, raddr6,
					(u8 *)in_params.remote_mac_addr);
	पूर्ण
	अगर (rc)
		जाओ err;

	DP_DEBUG(dev, QEDR_MSG_IWARP,
		 "ord = %d ird=%d private_data=%p private_data_len=%d rq_psn=%d\n",
		 conn_param->ord, conn_param->ird, conn_param->निजी_data,
		 conn_param->निजी_data_len, qp->rq_psn);

	cm_info->ord = conn_param->ord;
	cm_info->ird = conn_param->ird;
	cm_info->निजी_data = conn_param->निजी_data;
	cm_info->निजी_data_len = conn_param->निजी_data_len;
	in_params.qp = qp->qed_qp;
	स_नकल(in_params.local_mac_addr, dev->ndev->dev_addr, ETH_ALEN);

	अगर (test_and_set_bit(QEDR_IWARP_CM_WAIT_FOR_CONNECT,
			     &qp->iwarp_cm_flags)) अणु
		rc = -ENODEV;
		जाओ err; /* QP alपढ़ोy being destroyed */
	पूर्ण

	rc = dev->ops->iwarp_connect(dev->rdma_ctx, &in_params, &out_params);
	अगर (rc) अणु
		complete(&qp->iwarp_cm_comp);
		जाओ err;
	पूर्ण

	वापस rc;

err:
	kref_put(&ep->refcnt, qedr_iw_मुक्त_ep);
	वापस rc;
पूर्ण

पूर्णांक qedr_iw_create_listen(काष्ठा iw_cm_id *cm_id, पूर्णांक backlog)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(cm_id->device);
	काष्ठा qedr_iw_listener *listener;
	काष्ठा qed_iwarp_listen_in iparams;
	काष्ठा qed_iwarp_listen_out oparams;
	काष्ठा sockaddr_in *laddr;
	काष्ठा sockaddr_in6 *laddr6;
	पूर्णांक rc;
	पूर्णांक i;

	laddr = (काष्ठा sockaddr_in *)&cm_id->m_local_addr;
	laddr6 = (काष्ठा sockaddr_in6 *)&cm_id->m_local_addr;

	DP_DEBUG(dev, QEDR_MSG_IWARP,
		 "Create Listener address: %pISpc\n", &cm_id->local_addr);

	listener = kzalloc(माप(*listener), GFP_KERNEL);
	अगर (!listener)
		वापस -ENOMEM;

	listener->dev = dev;
	cm_id->add_ref(cm_id);
	listener->cm_id = cm_id;
	listener->backlog = backlog;

	iparams.cb_context = listener;
	iparams.event_cb = qedr_iw_event_handler;
	iparams.max_backlog = backlog;

	अगर (!IS_ENABLED(CONFIG_IPV6) ||
	    cm_id->local_addr.ss_family == AF_INET) अणु
		iparams.ip_version = QED_TCP_IPV4;
		स_रखो(iparams.ip_addr, 0, माप(iparams.ip_addr));

		iparams.ip_addr[0] = ntohl(laddr->sin_addr.s_addr);
		iparams.port = ntohs(laddr->sin_port);
		iparams.vlan = qedr_iw_get_vlan_ipv4(dev, iparams.ip_addr);
	पूर्ण अन्यथा अणु
		iparams.ip_version = QED_TCP_IPV6;

		क्रम (i = 0; i < 4; i++) अणु
			iparams.ip_addr[i] =
			    ntohl(laddr6->sin6_addr.in6_u.u6_addr32[i]);
		पूर्ण

		iparams.port = ntohs(laddr6->sin6_port);

		iparams.vlan = qedr_iw_get_vlan_ipv6(iparams.ip_addr);
	पूर्ण
	rc = dev->ops->iwarp_create_listen(dev->rdma_ctx, &iparams, &oparams);
	अगर (rc)
		जाओ err;

	listener->qed_handle = oparams.handle;
	cm_id->provider_data = listener;
	वापस rc;

err:
	cm_id->rem_ref(cm_id);
	kमुक्त(listener);
	वापस rc;
पूर्ण

पूर्णांक qedr_iw_destroy_listen(काष्ठा iw_cm_id *cm_id)
अणु
	काष्ठा qedr_iw_listener *listener = cm_id->provider_data;
	काष्ठा qedr_dev *dev = get_qedr_dev(cm_id->device);
	पूर्णांक rc = 0;

	अगर (listener->qed_handle)
		rc = dev->ops->iwarp_destroy_listen(dev->rdma_ctx,
						    listener->qed_handle);

	cm_id->rem_ref(cm_id);
	kमुक्त(listener);
	वापस rc;
पूर्ण

पूर्णांक qedr_iw_accept(काष्ठा iw_cm_id *cm_id, काष्ठा iw_cm_conn_param *conn_param)
अणु
	काष्ठा qedr_iw_ep *ep = (काष्ठा qedr_iw_ep *)cm_id->provider_data;
	काष्ठा qedr_dev *dev = ep->dev;
	काष्ठा qedr_qp *qp;
	काष्ठा qed_iwarp_accept_in params;
	पूर्णांक rc;

	DP_DEBUG(dev, QEDR_MSG_IWARP, "Accept on qpid=%d\n", conn_param->qpn);

	qp = qedr_iw_load_qp(dev, conn_param->qpn);
	अगर (!qp) अणु
		DP_ERR(dev, "Invalid QP number %d\n", conn_param->qpn);
		वापस -EINVAL;
	पूर्ण

	ep->qp = qp;
	cm_id->add_ref(cm_id);
	ep->cm_id = cm_id;

	params.ep_context = ep->qed_context;
	params.cb_context = ep;
	params.qp = ep->qp->qed_qp;
	params.निजी_data = conn_param->निजी_data;
	params.निजी_data_len = conn_param->निजी_data_len;
	params.ird = conn_param->ird;
	params.ord = conn_param->ord;

	अगर (test_and_set_bit(QEDR_IWARP_CM_WAIT_FOR_CONNECT,
			     &qp->iwarp_cm_flags)) अणु
		rc = -EINVAL;
		जाओ err; /* QP alपढ़ोy destroyed */
	पूर्ण

	rc = dev->ops->iwarp_accept(dev->rdma_ctx, &params);
	अगर (rc) अणु
		complete(&qp->iwarp_cm_comp);
		जाओ err;
	पूर्ण

	वापस rc;

err:
	kref_put(&ep->refcnt, qedr_iw_मुक्त_ep);

	वापस rc;
पूर्ण

पूर्णांक qedr_iw_reject(काष्ठा iw_cm_id *cm_id, स्थिर व्योम *pdata, u8 pdata_len)
अणु
	काष्ठा qedr_iw_ep *ep = (काष्ठा qedr_iw_ep *)cm_id->provider_data;
	काष्ठा qedr_dev *dev = ep->dev;
	काष्ठा qed_iwarp_reject_in params;

	params.ep_context = ep->qed_context;
	params.cb_context = ep;
	params.निजी_data = pdata;
	params.निजी_data_len = pdata_len;
	ep->qp = शून्य;

	वापस dev->ops->iwarp_reject(dev->rdma_ctx, &params);
पूर्ण

व्योम qedr_iw_qp_add_ref(काष्ठा ib_qp *ibqp)
अणु
	काष्ठा qedr_qp *qp = get_qedr_qp(ibqp);

	kref_get(&qp->refcnt);
पूर्ण

व्योम qedr_iw_qp_rem_ref(काष्ठा ib_qp *ibqp)
अणु
	काष्ठा qedr_qp *qp = get_qedr_qp(ibqp);

	kref_put(&qp->refcnt, qedr_iw_मुक्त_qp);
पूर्ण

काष्ठा ib_qp *qedr_iw_get_qp(काष्ठा ib_device *ibdev, पूर्णांक qpn)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibdev);

	वापस xa_load(&dev->qps, qpn);
पूर्ण
