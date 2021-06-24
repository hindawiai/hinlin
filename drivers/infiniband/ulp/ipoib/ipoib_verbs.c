<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
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

#समावेश "ipoib.h"

पूर्णांक ipoib_mcast_attach(काष्ठा net_device *dev, काष्ठा ib_device *hca,
		       जोड़ ib_gid *mgid, u16 mlid, पूर्णांक set_qkey, u32 qkey)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ib_qp_attr *qp_attr = शून्य;
	पूर्णांक ret;
	u16 pkey_index;

	अगर (ib_find_pkey(priv->ca, priv->port, priv->pkey, &pkey_index)) अणु
		clear_bit(IPOIB_PKEY_ASSIGNED, &priv->flags);
		ret = -ENXIO;
		जाओ out;
	पूर्ण
	set_bit(IPOIB_PKEY_ASSIGNED, &priv->flags);

	अगर (set_qkey) अणु
		ret = -ENOMEM;
		qp_attr = kदो_स्मृति(माप(*qp_attr), GFP_KERNEL);
		अगर (!qp_attr)
			जाओ out;

		/* set correct QKey क्रम QP */
		qp_attr->qkey = qkey;
		ret = ib_modअगरy_qp(priv->qp, qp_attr, IB_QP_QKEY);
		अगर (ret) अणु
			ipoib_warn(priv, "failed to modify QP, ret = %d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/* attach QP to multicast group */
	ret = ib_attach_mcast(priv->qp, mgid, mlid);
	अगर (ret)
		ipoib_warn(priv, "failed to attach to multicast group, ret = %d\n", ret);

out:
	kमुक्त(qp_attr);
	वापस ret;
पूर्ण

पूर्णांक ipoib_mcast_detach(काष्ठा net_device *dev, काष्ठा ib_device *hca,
		       जोड़ ib_gid *mgid, u16 mlid)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक ret;

	ret = ib_detach_mcast(priv->qp, mgid, mlid);

	वापस ret;
पूर्ण

पूर्णांक ipoib_init_qp(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक ret;
	काष्ठा ib_qp_attr qp_attr;
	पूर्णांक attr_mask;

	अगर (!test_bit(IPOIB_PKEY_ASSIGNED, &priv->flags))
		वापस -1;

	qp_attr.qp_state = IB_QPS_INIT;
	qp_attr.qkey = 0;
	qp_attr.port_num = priv->port;
	qp_attr.pkey_index = priv->pkey_index;
	attr_mask =
	    IB_QP_QKEY |
	    IB_QP_PORT |
	    IB_QP_PKEY_INDEX |
	    IB_QP_STATE;
	ret = ib_modअगरy_qp(priv->qp, &qp_attr, attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to modify QP to init, ret = %d\n", ret);
		जाओ out_fail;
	पूर्ण

	qp_attr.qp_state = IB_QPS_RTR;
	/* Can't set this in a INIT->RTR transition */
	attr_mask &= ~IB_QP_PORT;
	ret = ib_modअगरy_qp(priv->qp, &qp_attr, attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to modify QP to RTR, ret = %d\n", ret);
		जाओ out_fail;
	पूर्ण

	qp_attr.qp_state = IB_QPS_RTS;
	qp_attr.sq_psn = 0;
	attr_mask |= IB_QP_SQ_PSN;
	attr_mask &= ~IB_QP_PKEY_INDEX;
	ret = ib_modअगरy_qp(priv->qp, &qp_attr, attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to modify QP to RTS, ret = %d\n", ret);
		जाओ out_fail;
	पूर्ण

	वापस 0;

out_fail:
	qp_attr.qp_state = IB_QPS_RESET;
	अगर (ib_modअगरy_qp(priv->qp, &qp_attr, IB_QP_STATE))
		ipoib_warn(priv, "Failed to modify QP to RESET state\n");

	वापस ret;
पूर्ण

पूर्णांक ipoib_transport_dev_init(काष्ठा net_device *dev, काष्ठा ib_device *ca)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ib_qp_init_attr init_attr = अणु
		.cap = अणु
			.max_send_wr  = ipoib_sendq_size,
			.max_recv_wr  = ipoib_recvq_size,
			.max_send_sge = min_t(u32, priv->ca->attrs.max_send_sge,
					      MAX_SKB_FRAGS + 1),
			.max_recv_sge = IPOIB_UD_RX_SG
		पूर्ण,
		.sq_sig_type = IB_SIGNAL_ALL_WR,
		.qp_type     = IB_QPT_UD
	पूर्ण;
	काष्ठा ib_cq_init_attr cq_attr = अणुपूर्ण;

	पूर्णांक ret, size, req_vec;
	पूर्णांक i;
	अटल atomic_t counter;

	size = ipoib_recvq_size + 1;
	ret = ipoib_cm_dev_init(dev);
	अगर (!ret) अणु
		size += ipoib_sendq_size;
		अगर (ipoib_cm_has_srq(dev))
			size += ipoib_recvq_size + 1; /* 1 extra क्रम rx_drain_qp */
		अन्यथा
			size += ipoib_recvq_size * ipoib_max_conn_qp;
	पूर्ण अन्यथा
		अगर (ret != -EOPNOTSUPP)
			वापस ret;

	req_vec = atomic_inc_वापस(&counter) * 2;
	cq_attr.cqe = size;
	cq_attr.comp_vector = req_vec % priv->ca->num_comp_vectors;
	priv->recv_cq = ib_create_cq(priv->ca, ipoib_ib_rx_completion, शून्य,
				     priv, &cq_attr);
	अगर (IS_ERR(priv->recv_cq)) अणु
		pr_warn("%s: failed to create receive CQ\n", ca->name);
		जाओ out_cm_dev_cleanup;
	पूर्ण

	cq_attr.cqe = ipoib_sendq_size;
	cq_attr.comp_vector = (req_vec + 1) % priv->ca->num_comp_vectors;
	priv->send_cq = ib_create_cq(priv->ca, ipoib_ib_tx_completion, शून्य,
				     priv, &cq_attr);
	अगर (IS_ERR(priv->send_cq)) अणु
		pr_warn("%s: failed to create send CQ\n", ca->name);
		जाओ out_मुक्त_recv_cq;
	पूर्ण

	अगर (ib_req_notअगरy_cq(priv->recv_cq, IB_CQ_NEXT_COMP))
		जाओ out_मुक्त_send_cq;

	init_attr.send_cq = priv->send_cq;
	init_attr.recv_cq = priv->recv_cq;

	अगर (priv->hca_caps & IB_DEVICE_UD_TSO)
		init_attr.create_flags |= IB_QP_CREATE_IPOIB_UD_LSO;

	अगर (priv->hca_caps & IB_DEVICE_BLOCK_MULTICAST_LOOPBACK)
		init_attr.create_flags |= IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK;

	अगर (priv->hca_caps & IB_DEVICE_MANAGED_FLOW_STEERING)
		init_attr.create_flags |= IB_QP_CREATE_NETIF_QP;

	अगर (priv->hca_caps & IB_DEVICE_RDMA_NETDEV_OPA)
		init_attr.create_flags |= IB_QP_CREATE_NETDEV_USE;

	priv->qp = ib_create_qp(priv->pd, &init_attr);
	अगर (IS_ERR(priv->qp)) अणु
		pr_warn("%s: failed to create QP\n", ca->name);
		जाओ out_मुक्त_send_cq;
	पूर्ण

	अगर (ib_req_notअगरy_cq(priv->send_cq, IB_CQ_NEXT_COMP))
		जाओ out_मुक्त_send_cq;

	क्रम (i = 0; i < MAX_SKB_FRAGS + 1; ++i)
		priv->tx_sge[i].lkey = priv->pd->local_dma_lkey;

	priv->tx_wr.wr.opcode		= IB_WR_SEND;
	priv->tx_wr.wr.sg_list		= priv->tx_sge;
	priv->tx_wr.wr.send_flags	= IB_SEND_SIGNALED;

	priv->rx_sge[0].lkey = priv->pd->local_dma_lkey;

	priv->rx_sge[0].length = IPOIB_UD_BUF_SIZE(priv->max_ib_mtu);
	priv->rx_wr.num_sge = 1;

	priv->rx_wr.next = शून्य;
	priv->rx_wr.sg_list = priv->rx_sge;

	अगर (init_attr.cap.max_send_sge > 1)
		dev->features |= NETIF_F_SG;

	priv->max_send_sge = init_attr.cap.max_send_sge;

	वापस 0;

out_मुक्त_send_cq:
	ib_destroy_cq(priv->send_cq);

out_मुक्त_recv_cq:
	ib_destroy_cq(priv->recv_cq);

out_cm_dev_cleanup:
	ipoib_cm_dev_cleanup(dev);

	वापस -ENODEV;
पूर्ण

व्योम ipoib_transport_dev_cleanup(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	अगर (priv->qp) अणु
		अगर (ib_destroy_qp(priv->qp))
			ipoib_warn(priv, "ib_qp_destroy failed\n");

		priv->qp = शून्य;
	पूर्ण

	ib_destroy_cq(priv->send_cq);
	ib_destroy_cq(priv->recv_cq);
पूर्ण

व्योम ipoib_event(काष्ठा ib_event_handler *handler,
		 काष्ठा ib_event *record)
अणु
	काष्ठा ipoib_dev_priv *priv =
		container_of(handler, काष्ठा ipoib_dev_priv, event_handler);

	अगर (record->element.port_num != priv->port)
		वापस;

	ipoib_dbg(priv, "Event %d on device %s port %d\n", record->event,
		  dev_name(&record->device->dev), record->element.port_num);

	अगर (record->event == IB_EVENT_CLIENT_REREGISTER) अणु
		queue_work(ipoib_workqueue, &priv->flush_light);
	पूर्ण अन्यथा अगर (record->event == IB_EVENT_PORT_ERR ||
		   record->event == IB_EVENT_PORT_ACTIVE ||
		   record->event == IB_EVENT_LID_CHANGE) अणु
		queue_work(ipoib_workqueue, &priv->flush_normal);
	पूर्ण अन्यथा अगर (record->event == IB_EVENT_PKEY_CHANGE) अणु
		queue_work(ipoib_workqueue, &priv->flush_heavy);
	पूर्ण अन्यथा अगर (record->event == IB_EVENT_GID_CHANGE &&
		   !test_bit(IPOIB_FLAG_DEV_ADDR_SET, &priv->flags)) अणु
		queue_work(ipoib_workqueue, &priv->flush_light);
	पूर्ण
पूर्ण
