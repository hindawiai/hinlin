<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
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

#समावेश "mlx5_ib.h"

काष्ठा mlx5_ib_gsi_wr अणु
	काष्ठा ib_cqe cqe;
	काष्ठा ib_wc wc;
	bool completed:1;
पूर्ण;

अटल bool mlx5_ib_deth_sqpn_cap(काष्ठा mlx5_ib_dev *dev)
अणु
	वापस MLX5_CAP_GEN(dev->mdev, set_deth_sqpn);
पूर्ण

/* Call with gsi->lock locked */
अटल व्योम generate_completions(काष्ठा mlx5_ib_qp *mqp)
अणु
	काष्ठा mlx5_ib_gsi_qp *gsi = &mqp->gsi;
	काष्ठा ib_cq *gsi_cq = mqp->ibqp.send_cq;
	काष्ठा mlx5_ib_gsi_wr *wr;
	u32 index;

	क्रम (index = gsi->outstanding_ci; index != gsi->outstanding_pi;
	     index++) अणु
		wr = &gsi->outstanding_wrs[index % gsi->cap.max_send_wr];

		अगर (!wr->completed)
			अवरोध;

		WARN_ON_ONCE(mlx5_ib_generate_wc(gsi_cq, &wr->wc));
		wr->completed = false;
	पूर्ण

	gsi->outstanding_ci = index;
पूर्ण

अटल व्योम handle_single_completion(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा mlx5_ib_gsi_qp *gsi = cq->cq_context;
	काष्ठा mlx5_ib_gsi_wr *wr =
		container_of(wc->wr_cqe, काष्ठा mlx5_ib_gsi_wr, cqe);
	काष्ठा mlx5_ib_qp *mqp = container_of(gsi, काष्ठा mlx5_ib_qp, gsi);
	u64 wr_id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gsi->lock, flags);
	wr->completed = true;
	wr_id = wr->wc.wr_id;
	wr->wc = *wc;
	wr->wc.wr_id = wr_id;
	wr->wc.qp = &mqp->ibqp;

	generate_completions(mqp);
	spin_unlock_irqrestore(&gsi->lock, flags);
पूर्ण

पूर्णांक mlx5_ib_create_gsi(काष्ठा ib_pd *pd, काष्ठा mlx5_ib_qp *mqp,
		       काष्ठा ib_qp_init_attr *attr)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	काष्ठा mlx5_ib_gsi_qp *gsi;
	काष्ठा ib_qp_init_attr hw_init_attr = *attr;
	स्थिर u8 port_num = attr->port_num;
	पूर्णांक num_qps = 0;
	पूर्णांक ret;

	अगर (mlx5_ib_deth_sqpn_cap(dev)) अणु
		अगर (MLX5_CAP_GEN(dev->mdev,
				 port_type) == MLX5_CAP_PORT_TYPE_IB)
			num_qps = pd->device->attrs.max_pkeys;
		अन्यथा अगर (dev->lag_active)
			num_qps = MLX5_MAX_PORTS;
	पूर्ण

	gsi = &mqp->gsi;
	gsi->tx_qps = kसुस्मृति(num_qps, माप(*gsi->tx_qps), GFP_KERNEL);
	अगर (!gsi->tx_qps)
		वापस -ENOMEM;

	gsi->outstanding_wrs =
		kसुस्मृति(attr->cap.max_send_wr, माप(*gsi->outstanding_wrs),
			GFP_KERNEL);
	अगर (!gsi->outstanding_wrs) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_tx;
	पूर्ण

	mutex_lock(&dev->devr.mutex);

	अगर (dev->devr.ports[port_num - 1].gsi) अणु
		mlx5_ib_warn(dev, "GSI QP already exists on port %d\n",
			     port_num);
		ret = -EBUSY;
		जाओ err_मुक्त_wrs;
	पूर्ण
	gsi->num_qps = num_qps;
	spin_lock_init(&gsi->lock);

	gsi->cap = attr->cap;
	gsi->port_num = port_num;

	gsi->cq = ib_alloc_cq(pd->device, gsi, attr->cap.max_send_wr, 0,
			      IB_POLL_SOFTIRQ);
	अगर (IS_ERR(gsi->cq)) अणु
		mlx5_ib_warn(dev, "unable to create send CQ for GSI QP. error %ld\n",
			     PTR_ERR(gsi->cq));
		ret = PTR_ERR(gsi->cq);
		जाओ err_मुक्त_wrs;
	पूर्ण

	hw_init_attr.qp_type = MLX5_IB_QPT_HW_GSI;
	hw_init_attr.send_cq = gsi->cq;
	अगर (num_qps) अणु
		hw_init_attr.cap.max_send_wr = 0;
		hw_init_attr.cap.max_send_sge = 0;
		hw_init_attr.cap.max_अंतरभूत_data = 0;
	पूर्ण

	gsi->rx_qp = mlx5_ib_create_qp(pd, &hw_init_attr, शून्य);
	अगर (IS_ERR(gsi->rx_qp)) अणु
		mlx5_ib_warn(dev, "unable to create hardware GSI QP. error %ld\n",
			     PTR_ERR(gsi->rx_qp));
		ret = PTR_ERR(gsi->rx_qp);
		जाओ err_destroy_cq;
	पूर्ण
	gsi->rx_qp->device = pd->device;
	gsi->rx_qp->pd = pd;
	gsi->rx_qp->real_qp = gsi->rx_qp;

	gsi->rx_qp->qp_type = hw_init_attr.qp_type;
	gsi->rx_qp->send_cq = hw_init_attr.send_cq;
	gsi->rx_qp->recv_cq = hw_init_attr.recv_cq;
	gsi->rx_qp->event_handler = hw_init_attr.event_handler;
	spin_lock_init(&gsi->rx_qp->mr_lock);
	INIT_LIST_HEAD(&gsi->rx_qp->rdma_mrs);
	INIT_LIST_HEAD(&gsi->rx_qp->sig_mrs);

	dev->devr.ports[attr->port_num - 1].gsi = gsi;

	mutex_unlock(&dev->devr.mutex);

	वापस 0;

err_destroy_cq:
	ib_मुक्त_cq(gsi->cq);
err_मुक्त_wrs:
	mutex_unlock(&dev->devr.mutex);
	kमुक्त(gsi->outstanding_wrs);
err_मुक्त_tx:
	kमुक्त(gsi->tx_qps);
	वापस ret;
पूर्ण

पूर्णांक mlx5_ib_destroy_gsi(काष्ठा mlx5_ib_qp *mqp)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(mqp->ibqp.device);
	काष्ठा mlx5_ib_gsi_qp *gsi = &mqp->gsi;
	स्थिर पूर्णांक port_num = gsi->port_num;
	पूर्णांक qp_index;
	पूर्णांक ret;

	mutex_lock(&dev->devr.mutex);
	ret = mlx5_ib_destroy_qp(gsi->rx_qp, शून्य);
	अगर (ret) अणु
		mlx5_ib_warn(dev, "unable to destroy hardware GSI QP. error %d\n",
			     ret);
		mutex_unlock(&dev->devr.mutex);
		वापस ret;
	पूर्ण
	dev->devr.ports[port_num - 1].gsi = शून्य;
	mutex_unlock(&dev->devr.mutex);
	gsi->rx_qp = शून्य;

	क्रम (qp_index = 0; qp_index < gsi->num_qps; ++qp_index) अणु
		अगर (!gsi->tx_qps[qp_index])
			जारी;
		WARN_ON_ONCE(ib_destroy_qp(gsi->tx_qps[qp_index]));
		gsi->tx_qps[qp_index] = शून्य;
	पूर्ण

	ib_मुक्त_cq(gsi->cq);

	kमुक्त(gsi->outstanding_wrs);
	kमुक्त(gsi->tx_qps);
	kमुक्त(mqp);

	वापस 0;
पूर्ण

अटल काष्ठा ib_qp *create_gsi_ud_qp(काष्ठा mlx5_ib_gsi_qp *gsi)
अणु
	काष्ठा ib_pd *pd = gsi->rx_qp->pd;
	काष्ठा ib_qp_init_attr init_attr = अणु
		.event_handler = gsi->rx_qp->event_handler,
		.qp_context = gsi->rx_qp->qp_context,
		.send_cq = gsi->cq,
		.recv_cq = gsi->rx_qp->recv_cq,
		.cap = अणु
			.max_send_wr = gsi->cap.max_send_wr,
			.max_send_sge = gsi->cap.max_send_sge,
			.max_अंतरभूत_data = gsi->cap.max_अंतरभूत_data,
		पूर्ण,
		.qp_type = IB_QPT_UD,
		.create_flags = MLX5_IB_QP_CREATE_SQPN_QP1,
	पूर्ण;

	वापस ib_create_qp(pd, &init_attr);
पूर्ण

अटल पूर्णांक modअगरy_to_rts(काष्ठा mlx5_ib_gsi_qp *gsi, काष्ठा ib_qp *qp,
			 u16 pkey_index)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(qp->device);
	काष्ठा ib_qp_attr attr;
	पूर्णांक mask;
	पूर्णांक ret;

	mask = IB_QP_STATE | IB_QP_PKEY_INDEX | IB_QP_QKEY | IB_QP_PORT;
	attr.qp_state = IB_QPS_INIT;
	attr.pkey_index = pkey_index;
	attr.qkey = IB_QP1_QKEY;
	attr.port_num = gsi->port_num;
	ret = ib_modअगरy_qp(qp, &attr, mask);
	अगर (ret) अणु
		mlx5_ib_err(dev, "could not change QP%d state to INIT: %d\n",
			    qp->qp_num, ret);
		वापस ret;
	पूर्ण

	attr.qp_state = IB_QPS_RTR;
	ret = ib_modअगरy_qp(qp, &attr, IB_QP_STATE);
	अगर (ret) अणु
		mlx5_ib_err(dev, "could not change QP%d state to RTR: %d\n",
			    qp->qp_num, ret);
		वापस ret;
	पूर्ण

	attr.qp_state = IB_QPS_RTS;
	attr.sq_psn = 0;
	ret = ib_modअगरy_qp(qp, &attr, IB_QP_STATE | IB_QP_SQ_PSN);
	अगर (ret) अणु
		mlx5_ib_err(dev, "could not change QP%d state to RTS: %d\n",
			    qp->qp_num, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम setup_qp(काष्ठा mlx5_ib_gsi_qp *gsi, u16 qp_index)
अणु
	काष्ठा ib_device *device = gsi->rx_qp->device;
	काष्ठा mlx5_ib_dev *dev = to_mdev(device);
	पूर्णांक pkey_index = qp_index;
	काष्ठा mlx5_ib_qp *mqp;
	काष्ठा ib_qp *qp;
	अचिन्हित दीर्घ flags;
	u16 pkey;
	पूर्णांक ret;

	अगर (MLX5_CAP_GEN(dev->mdev,  port_type) != MLX5_CAP_PORT_TYPE_IB)
		pkey_index = 0;

	ret = ib_query_pkey(device, gsi->port_num, pkey_index, &pkey);
	अगर (ret) अणु
		mlx5_ib_warn(dev, "unable to read P_Key at port %d, index %d\n",
			     gsi->port_num, qp_index);
		वापस;
	पूर्ण

	अगर (!pkey) अणु
		mlx5_ib_dbg(dev, "invalid P_Key at port %d, index %d.  Skipping.\n",
			    gsi->port_num, qp_index);
		वापस;
	पूर्ण

	spin_lock_irqsave(&gsi->lock, flags);
	qp = gsi->tx_qps[qp_index];
	spin_unlock_irqrestore(&gsi->lock, flags);
	अगर (qp) अणु
		mlx5_ib_dbg(dev, "already existing GSI TX QP at port %d, index %d. Skipping\n",
			    gsi->port_num, qp_index);
		वापस;
	पूर्ण

	qp = create_gsi_ud_qp(gsi);
	अगर (IS_ERR(qp)) अणु
		mlx5_ib_warn(dev, "unable to create hardware UD QP for GSI: %ld\n",
			     PTR_ERR(qp));
		वापस;
	पूर्ण

	mqp = to_mqp(qp);
	अगर (dev->lag_active)
		mqp->gsi_lag_port = qp_index + 1;
	ret = modअगरy_to_rts(gsi, qp, pkey_index);
	अगर (ret)
		जाओ err_destroy_qp;

	spin_lock_irqsave(&gsi->lock, flags);
	WARN_ON_ONCE(gsi->tx_qps[qp_index]);
	gsi->tx_qps[qp_index] = qp;
	spin_unlock_irqrestore(&gsi->lock, flags);

	वापस;

err_destroy_qp:
	WARN_ON_ONCE(qp);
पूर्ण

अटल व्योम setup_qps(काष्ठा mlx5_ib_gsi_qp *gsi)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(gsi->rx_qp->device);
	u16 qp_index;

	mutex_lock(&dev->devr.mutex);
	क्रम (qp_index = 0; qp_index < gsi->num_qps; ++qp_index)
		setup_qp(gsi, qp_index);
	mutex_unlock(&dev->devr.mutex);
पूर्ण

पूर्णांक mlx5_ib_gsi_modअगरy_qp(काष्ठा ib_qp *qp, काष्ठा ib_qp_attr *attr,
			  पूर्णांक attr_mask)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(qp->device);
	काष्ठा mlx5_ib_qp *mqp = to_mqp(qp);
	काष्ठा mlx5_ib_gsi_qp *gsi = &mqp->gsi;
	पूर्णांक ret;

	mlx5_ib_dbg(dev, "modifying GSI QP to state %d\n", attr->qp_state);

	ret = ib_modअगरy_qp(gsi->rx_qp, attr, attr_mask);
	अगर (ret) अणु
		mlx5_ib_warn(dev, "unable to modify GSI rx QP: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (to_mqp(gsi->rx_qp)->state == IB_QPS_RTS)
		setup_qps(gsi);
	वापस 0;
पूर्ण

पूर्णांक mlx5_ib_gsi_query_qp(काष्ठा ib_qp *qp, काष्ठा ib_qp_attr *qp_attr,
			 पूर्णांक qp_attr_mask,
			 काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा mlx5_ib_qp *mqp = to_mqp(qp);
	काष्ठा mlx5_ib_gsi_qp *gsi = &mqp->gsi;
	पूर्णांक ret;

	ret = ib_query_qp(gsi->rx_qp, qp_attr, qp_attr_mask, qp_init_attr);
	qp_init_attr->cap = gsi->cap;
	वापस ret;
पूर्ण

/* Call with gsi->lock locked */
अटल पूर्णांक mlx5_ib_add_outstanding_wr(काष्ठा mlx5_ib_qp *mqp,
				      काष्ठा ib_ud_wr *wr, काष्ठा ib_wc *wc)
अणु
	काष्ठा mlx5_ib_gsi_qp *gsi = &mqp->gsi;
	काष्ठा mlx5_ib_dev *dev = to_mdev(gsi->rx_qp->device);
	काष्ठा mlx5_ib_gsi_wr *gsi_wr;

	अगर (gsi->outstanding_pi == gsi->outstanding_ci + gsi->cap.max_send_wr) अणु
		mlx5_ib_warn(dev, "no available GSI work request.\n");
		वापस -ENOMEM;
	पूर्ण

	gsi_wr = &gsi->outstanding_wrs[gsi->outstanding_pi %
				       gsi->cap.max_send_wr];
	gsi->outstanding_pi++;

	अगर (!wc) अणु
		स_रखो(&gsi_wr->wc, 0, माप(gsi_wr->wc));
		gsi_wr->wc.pkey_index = wr->pkey_index;
		gsi_wr->wc.wr_id = wr->wr.wr_id;
	पूर्ण अन्यथा अणु
		gsi_wr->wc = *wc;
		gsi_wr->completed = true;
	पूर्ण

	gsi_wr->cqe.करोne = &handle_single_completion;
	wr->wr.wr_cqe = &gsi_wr->cqe;

	वापस 0;
पूर्ण

/* Call with gsi->lock locked */
अटल पूर्णांक mlx5_ib_gsi_silent_drop(काष्ठा mlx5_ib_qp *mqp, काष्ठा ib_ud_wr *wr)
अणु
	काष्ठा ib_wc wc = अणु
		अणु .wr_id = wr->wr.wr_id पूर्ण,
		.status = IB_WC_SUCCESS,
		.opcode = IB_WC_SEND,
		.qp = &mqp->ibqp,
	पूर्ण;
	पूर्णांक ret;

	ret = mlx5_ib_add_outstanding_wr(mqp, wr, &wc);
	अगर (ret)
		वापस ret;

	generate_completions(mqp);

	वापस 0;
पूर्ण

/* Call with gsi->lock locked */
अटल काष्ठा ib_qp *get_tx_qp(काष्ठा mlx5_ib_gsi_qp *gsi, काष्ठा ib_ud_wr *wr)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(gsi->rx_qp->device);
	काष्ठा mlx5_ib_ah *ah = to_mah(wr->ah);
	पूर्णांक qp_index = wr->pkey_index;

	अगर (!gsi->num_qps)
		वापस gsi->rx_qp;

	अगर (dev->lag_active && ah->xmit_port)
		qp_index = ah->xmit_port - 1;

	अगर (qp_index >= gsi->num_qps)
		वापस शून्य;

	वापस gsi->tx_qps[qp_index];
पूर्ण

पूर्णांक mlx5_ib_gsi_post_send(काष्ठा ib_qp *qp, स्थिर काष्ठा ib_send_wr *wr,
			  स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा mlx5_ib_qp *mqp = to_mqp(qp);
	काष्ठा mlx5_ib_gsi_qp *gsi = &mqp->gsi;
	काष्ठा ib_qp *tx_qp;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	क्रम (; wr; wr = wr->next) अणु
		काष्ठा ib_ud_wr cur_wr = *ud_wr(wr);

		cur_wr.wr.next = शून्य;

		spin_lock_irqsave(&gsi->lock, flags);
		tx_qp = get_tx_qp(gsi, &cur_wr);
		अगर (!tx_qp) अणु
			ret = mlx5_ib_gsi_silent_drop(mqp, &cur_wr);
			अगर (ret)
				जाओ err;
			spin_unlock_irqrestore(&gsi->lock, flags);
			जारी;
		पूर्ण

		ret = mlx5_ib_add_outstanding_wr(mqp, &cur_wr, शून्य);
		अगर (ret)
			जाओ err;

		ret = ib_post_send(tx_qp, &cur_wr.wr, bad_wr);
		अगर (ret) अणु
			/* Unकरो the effect of adding the outstanding wr */
			gsi->outstanding_pi--;
			जाओ err;
		पूर्ण
		spin_unlock_irqrestore(&gsi->lock, flags);
	पूर्ण

	वापस 0;

err:
	spin_unlock_irqrestore(&gsi->lock, flags);
	*bad_wr = wr;
	वापस ret;
पूर्ण

पूर्णांक mlx5_ib_gsi_post_recv(काष्ठा ib_qp *qp, स्थिर काष्ठा ib_recv_wr *wr,
			  स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा mlx5_ib_qp *mqp = to_mqp(qp);
	काष्ठा mlx5_ib_gsi_qp *gsi = &mqp->gsi;

	वापस ib_post_recv(gsi->rx_qp, wr, bad_wr);
पूर्ण

व्योम mlx5_ib_gsi_pkey_change(काष्ठा mlx5_ib_gsi_qp *gsi)
अणु
	अगर (!gsi)
		वापस;

	setup_qps(gsi);
पूर्ण
