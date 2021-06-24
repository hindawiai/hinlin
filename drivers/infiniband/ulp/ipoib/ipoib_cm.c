<शैली गुरु>
/*
 * Copyright (c) 2006 Mellanox Technologies. All rights reserved
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

#समावेश <rdma/ib_cm.h>
#समावेश <net/dst.h>
#समावेश <net/icmp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>

#समावेश "ipoib.h"

पूर्णांक ipoib_max_conn_qp = 128;

module_param_named(max_nonsrq_conn_qp, ipoib_max_conn_qp, पूर्णांक, 0444);
MODULE_PARM_DESC(max_nonsrq_conn_qp,
		 "Max number of connected-mode QPs per interface "
		 "(applied only if shared receive queue is not available)");

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG_DATA
अटल पूर्णांक data_debug_level;

module_param_named(cm_data_debug_level, data_debug_level, पूर्णांक, 0644);
MODULE_PARM_DESC(cm_data_debug_level,
		 "Enable data path debug tracing for connected mode if > 0");
#पूर्ण_अगर

#घोषणा IPOIB_CM_IETF_ID 0x1000000000000000ULL

#घोषणा IPOIB_CM_RX_UPDATE_TIME (256 * HZ)
#घोषणा IPOIB_CM_RX_TIMEOUT     (2 * 256 * HZ)
#घोषणा IPOIB_CM_RX_DELAY       (3 * 256 * HZ)
#घोषणा IPOIB_CM_RX_UPDATE_MASK (0x3)

#घोषणा IPOIB_CM_RX_RESERVE     (ALIGN(IPOIB_HARD_LEN, 16) - IPOIB_ENCAP_LEN)

अटल काष्ठा ib_qp_attr ipoib_cm_err_attr = अणु
	.qp_state = IB_QPS_ERR
पूर्ण;

#घोषणा IPOIB_CM_RX_DRAIN_WRID 0xffffffff

अटल काष्ठा ib_send_wr ipoib_cm_rx_drain_wr = अणु
	.opcode = IB_WR_SEND,
पूर्ण;

अटल पूर्णांक ipoib_cm_tx_handler(काष्ठा ib_cm_id *cm_id,
			       स्थिर काष्ठा ib_cm_event *event);

अटल व्योम ipoib_cm_dma_unmap_rx(काष्ठा ipoib_dev_priv *priv, पूर्णांक frags,
				  u64 mapping[IPOIB_CM_RX_SG])
अणु
	पूर्णांक i;

	ib_dma_unmap_single(priv->ca, mapping[0], IPOIB_CM_HEAD_SIZE, DMA_FROM_DEVICE);

	क्रम (i = 0; i < frags; ++i)
		ib_dma_unmap_page(priv->ca, mapping[i + 1], PAGE_SIZE, DMA_FROM_DEVICE);
पूर्ण

अटल पूर्णांक ipoib_cm_post_receive_srq(काष्ठा net_device *dev, पूर्णांक id)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक i, ret;

	priv->cm.rx_wr.wr_id = id | IPOIB_OP_CM | IPOIB_OP_RECV;

	क्रम (i = 0; i < priv->cm.num_frags; ++i)
		priv->cm.rx_sge[i].addr = priv->cm.srq_ring[id].mapping[i];

	ret = ib_post_srq_recv(priv->cm.srq, &priv->cm.rx_wr, शून्य);
	अगर (unlikely(ret)) अणु
		ipoib_warn(priv, "post srq failed for buf %d (%d)\n", id, ret);
		ipoib_cm_dma_unmap_rx(priv, priv->cm.num_frags - 1,
				      priv->cm.srq_ring[id].mapping);
		dev_kमुक्त_skb_any(priv->cm.srq_ring[id].skb);
		priv->cm.srq_ring[id].skb = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ipoib_cm_post_receive_nonsrq(काष्ठा net_device *dev,
					काष्ठा ipoib_cm_rx *rx,
					काष्ठा ib_recv_wr *wr,
					काष्ठा ib_sge *sge, पूर्णांक id)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक i, ret;

	wr->wr_id = id | IPOIB_OP_CM | IPOIB_OP_RECV;

	क्रम (i = 0; i < IPOIB_CM_RX_SG; ++i)
		sge[i].addr = rx->rx_ring[id].mapping[i];

	ret = ib_post_recv(rx->qp, wr, शून्य);
	अगर (unlikely(ret)) अणु
		ipoib_warn(priv, "post recv failed for buf %d (%d)\n", id, ret);
		ipoib_cm_dma_unmap_rx(priv, IPOIB_CM_RX_SG - 1,
				      rx->rx_ring[id].mapping);
		dev_kमुक्त_skb_any(rx->rx_ring[id].skb);
		rx->rx_ring[id].skb = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा sk_buff *ipoib_cm_alloc_rx_skb(काष्ठा net_device *dev,
					     काष्ठा ipoib_cm_rx_buf *rx_ring,
					     पूर्णांक id, पूर्णांक frags,
					     u64 mapping[IPOIB_CM_RX_SG],
					     gfp_t gfp)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	skb = dev_alloc_skb(ALIGN(IPOIB_CM_HEAD_SIZE + IPOIB_PSEUDO_LEN, 16));
	अगर (unlikely(!skb))
		वापस शून्य;

	/*
	 * IPoIB adds a IPOIB_ENCAP_LEN byte header, this will align the
	 * IP header to a multiple of 16.
	 */
	skb_reserve(skb, IPOIB_CM_RX_RESERVE);

	mapping[0] = ib_dma_map_single(priv->ca, skb->data, IPOIB_CM_HEAD_SIZE,
				       DMA_FROM_DEVICE);
	अगर (unlikely(ib_dma_mapping_error(priv->ca, mapping[0]))) अणु
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < frags; i++) अणु
		काष्ठा page *page = alloc_page(gfp);

		अगर (!page)
			जाओ partial_error;
		skb_fill_page_desc(skb, i, page, 0, PAGE_SIZE);

		mapping[i + 1] = ib_dma_map_page(priv->ca, page,
						 0, PAGE_SIZE, DMA_FROM_DEVICE);
		अगर (unlikely(ib_dma_mapping_error(priv->ca, mapping[i + 1])))
			जाओ partial_error;
	पूर्ण

	rx_ring[id].skb = skb;
	वापस skb;

partial_error:

	ib_dma_unmap_single(priv->ca, mapping[0], IPOIB_CM_HEAD_SIZE, DMA_FROM_DEVICE);

	क्रम (; i > 0; --i)
		ib_dma_unmap_page(priv->ca, mapping[i], PAGE_SIZE, DMA_FROM_DEVICE);

	dev_kमुक्त_skb_any(skb);
	वापस शून्य;
पूर्ण

अटल व्योम ipoib_cm_मुक्त_rx_ring(काष्ठा net_device *dev,
				  काष्ठा ipoib_cm_rx_buf *rx_ring)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < ipoib_recvq_size; ++i)
		अगर (rx_ring[i].skb) अणु
			ipoib_cm_dma_unmap_rx(priv, IPOIB_CM_RX_SG - 1,
					      rx_ring[i].mapping);
			dev_kमुक्त_skb_any(rx_ring[i].skb);
		पूर्ण

	vमुक्त(rx_ring);
पूर्ण

अटल व्योम ipoib_cm_start_rx_drain(काष्ठा ipoib_dev_priv *priv)
अणु
	काष्ठा ipoib_cm_rx *p;

	/* We only reserved 1 extra slot in CQ क्रम drain WRs, so
	 * make sure we have at most 1 outstanding WR. */
	अगर (list_empty(&priv->cm.rx_flush_list) ||
	    !list_empty(&priv->cm.rx_drain_list))
		वापस;

	/*
	 * QPs on flush list are error state.  This way, a "flush
	 * error" WC will be immediately generated क्रम each WR we post.
	 */
	p = list_entry(priv->cm.rx_flush_list.next, typeof(*p), list);
	ipoib_cm_rx_drain_wr.wr_id = IPOIB_CM_RX_DRAIN_WRID;
	अगर (ib_post_send(p->qp, &ipoib_cm_rx_drain_wr, शून्य))
		ipoib_warn(priv, "failed to post drain wr\n");

	list_splice_init(&priv->cm.rx_flush_list, &priv->cm.rx_drain_list);
पूर्ण

अटल व्योम ipoib_cm_rx_event_handler(काष्ठा ib_event *event, व्योम *ctx)
अणु
	काष्ठा ipoib_cm_rx *p = ctx;
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(p->dev);
	अचिन्हित दीर्घ flags;

	अगर (event->event != IB_EVENT_QP_LAST_WQE_REACHED)
		वापस;

	spin_lock_irqsave(&priv->lock, flags);
	list_move(&p->list, &priv->cm.rx_flush_list);
	p->state = IPOIB_CM_RX_FLUSH;
	ipoib_cm_start_rx_drain(priv);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल काष्ठा ib_qp *ipoib_cm_create_rx_qp(काष्ठा net_device *dev,
					   काष्ठा ipoib_cm_rx *p)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ib_qp_init_attr attr = अणु
		.event_handler = ipoib_cm_rx_event_handler,
		.send_cq = priv->recv_cq, /* For drain WR */
		.recv_cq = priv->recv_cq,
		.srq = priv->cm.srq,
		.cap.max_send_wr = 1, /* For drain WR */
		.cap.max_send_sge = 1, /* FIXME: 0 Seems not to work */
		.sq_sig_type = IB_SIGNAL_ALL_WR,
		.qp_type = IB_QPT_RC,
		.qp_context = p,
	पूर्ण;

	अगर (!ipoib_cm_has_srq(dev)) अणु
		attr.cap.max_recv_wr  = ipoib_recvq_size;
		attr.cap.max_recv_sge = IPOIB_CM_RX_SG;
	पूर्ण

	वापस ib_create_qp(priv->pd, &attr);
पूर्ण

अटल पूर्णांक ipoib_cm_modअगरy_rx_qp(काष्ठा net_device *dev,
				 काष्ठा ib_cm_id *cm_id, काष्ठा ib_qp *qp,
				 अचिन्हित पूर्णांक psn)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ib_qp_attr qp_attr;
	पूर्णांक qp_attr_mask, ret;

	qp_attr.qp_state = IB_QPS_INIT;
	ret = ib_cm_init_qp_attr(cm_id, &qp_attr, &qp_attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to init QP attr for INIT: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = ib_modअगरy_qp(qp, &qp_attr, qp_attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to modify QP to INIT: %d\n", ret);
		वापस ret;
	पूर्ण
	qp_attr.qp_state = IB_QPS_RTR;
	ret = ib_cm_init_qp_attr(cm_id, &qp_attr, &qp_attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to init QP attr for RTR: %d\n", ret);
		वापस ret;
	पूर्ण
	qp_attr.rq_psn = psn;
	ret = ib_modअगरy_qp(qp, &qp_attr, qp_attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to modify QP to RTR: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Current Mellanox HCA firmware won't generate completions
	 * with error क्रम drain WRs unless the QP has been moved to
	 * RTS first. This work-around leaves a winकरोw where a QP has
	 * moved to error asynchronously, but this will eventually get
	 * fixed in firmware, so let's not error out अगर modअगरy QP
	 * fails.
	 */
	qp_attr.qp_state = IB_QPS_RTS;
	ret = ib_cm_init_qp_attr(cm_id, &qp_attr, &qp_attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to init QP attr for RTS: %d\n", ret);
		वापस 0;
	पूर्ण
	ret = ib_modअगरy_qp(qp, &qp_attr, qp_attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to modify QP to RTS: %d\n", ret);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ipoib_cm_init_rx_wr(काष्ठा net_device *dev,
				काष्ठा ib_recv_wr *wr,
				काष्ठा ib_sge *sge)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < priv->cm.num_frags; ++i)
		sge[i].lkey = priv->pd->local_dma_lkey;

	sge[0].length = IPOIB_CM_HEAD_SIZE;
	क्रम (i = 1; i < priv->cm.num_frags; ++i)
		sge[i].length = PAGE_SIZE;

	wr->next    = शून्य;
	wr->sg_list = sge;
	wr->num_sge = priv->cm.num_frags;
पूर्ण

अटल पूर्णांक ipoib_cm_nonsrq_init_rx(काष्ठा net_device *dev, काष्ठा ib_cm_id *cm_id,
				   काष्ठा ipoib_cm_rx *rx)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा अणु
		काष्ठा ib_recv_wr wr;
		काष्ठा ib_sge sge[IPOIB_CM_RX_SG];
	पूर्ण *t;
	पूर्णांक ret;
	पूर्णांक i;

	rx->rx_ring = vzalloc(array_size(ipoib_recvq_size,
					 माप(*rx->rx_ring)));
	अगर (!rx->rx_ring)
		वापस -ENOMEM;

	t = kदो_स्मृति(माप(*t), GFP_KERNEL);
	अगर (!t) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_1;
	पूर्ण

	ipoib_cm_init_rx_wr(dev, &t->wr, t->sge);

	spin_lock_irq(&priv->lock);

	अगर (priv->cm.nonsrq_conn_qp >= ipoib_max_conn_qp) अणु
		spin_unlock_irq(&priv->lock);
		ib_send_cm_rej(cm_id, IB_CM_REJ_NO_QP, शून्य, 0, शून्य, 0);
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण अन्यथा
		++priv->cm.nonsrq_conn_qp;

	spin_unlock_irq(&priv->lock);

	क्रम (i = 0; i < ipoib_recvq_size; ++i) अणु
		अगर (!ipoib_cm_alloc_rx_skb(dev, rx->rx_ring, i, IPOIB_CM_RX_SG - 1,
					   rx->rx_ring[i].mapping,
					   GFP_KERNEL)) अणु
			ipoib_warn(priv, "failed to allocate receive buffer %d\n", i);
			ret = -ENOMEM;
			जाओ err_count;
		पूर्ण
		ret = ipoib_cm_post_receive_nonsrq(dev, rx, &t->wr, t->sge, i);
		अगर (ret) अणु
			ipoib_warn(priv, "ipoib_cm_post_receive_nonsrq "
				   "failed for buf %d\n", i);
			ret = -EIO;
			जाओ err_count;
		पूर्ण
	पूर्ण

	rx->recv_count = ipoib_recvq_size;

	kमुक्त(t);

	वापस 0;

err_count:
	spin_lock_irq(&priv->lock);
	--priv->cm.nonsrq_conn_qp;
	spin_unlock_irq(&priv->lock);

err_मुक्त:
	kमुक्त(t);

err_मुक्त_1:
	ipoib_cm_मुक्त_rx_ring(dev, rx->rx_ring);

	वापस ret;
पूर्ण

अटल पूर्णांक ipoib_cm_send_rep(काष्ठा net_device *dev, काष्ठा ib_cm_id *cm_id,
			     काष्ठा ib_qp *qp,
			     स्थिर काष्ठा ib_cm_req_event_param *req,
			     अचिन्हित पूर्णांक psn)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_cm_data data = अणुपूर्ण;
	काष्ठा ib_cm_rep_param rep = अणुपूर्ण;

	data.qpn = cpu_to_be32(priv->qp->qp_num);
	data.mtu = cpu_to_be32(IPOIB_CM_BUF_SIZE);

	rep.निजी_data = &data;
	rep.निजी_data_len = माप(data);
	rep.flow_control = 0;
	rep.rnr_retry_count = req->rnr_retry_count;
	rep.srq = ipoib_cm_has_srq(dev);
	rep.qp_num = qp->qp_num;
	rep.starting_psn = psn;
	वापस ib_send_cm_rep(cm_id, &rep);
पूर्ण

अटल पूर्णांक ipoib_cm_req_handler(काष्ठा ib_cm_id *cm_id,
				स्थिर काष्ठा ib_cm_event *event)
अणु
	काष्ठा net_device *dev = cm_id->context;
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_cm_rx *p;
	अचिन्हित पूर्णांक psn;
	पूर्णांक ret;

	ipoib_dbg(priv, "REQ arrived\n");
	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;
	p->dev = dev;
	p->id = cm_id;
	cm_id->context = p;
	p->state = IPOIB_CM_RX_LIVE;
	p->jअगरfies = jअगरfies;
	INIT_LIST_HEAD(&p->list);

	p->qp = ipoib_cm_create_rx_qp(dev, p);
	अगर (IS_ERR(p->qp)) अणु
		ret = PTR_ERR(p->qp);
		जाओ err_qp;
	पूर्ण

	psn = pअक्रमom_u32() & 0xffffff;
	ret = ipoib_cm_modअगरy_rx_qp(dev, cm_id, p->qp, psn);
	अगर (ret)
		जाओ err_modअगरy;

	अगर (!ipoib_cm_has_srq(dev)) अणु
		ret = ipoib_cm_nonsrq_init_rx(dev, cm_id, p);
		अगर (ret)
			जाओ err_modअगरy;
	पूर्ण

	spin_lock_irq(&priv->lock);
	queue_delayed_work(priv->wq,
			   &priv->cm.stale_task, IPOIB_CM_RX_DELAY);
	/* Add this entry to passive ids list head, but करो not re-add it
	 * अगर IB_EVENT_QP_LAST_WQE_REACHED has moved it to flush list. */
	p->jअगरfies = jअगरfies;
	अगर (p->state == IPOIB_CM_RX_LIVE)
		list_move(&p->list, &priv->cm.passive_ids);
	spin_unlock_irq(&priv->lock);

	ret = ipoib_cm_send_rep(dev, cm_id, p->qp, &event->param.req_rcvd, psn);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to send REP: %d\n", ret);
		अगर (ib_modअगरy_qp(p->qp, &ipoib_cm_err_attr, IB_QP_STATE))
			ipoib_warn(priv, "unable to move qp to error state\n");
	पूर्ण
	वापस 0;

err_modअगरy:
	ib_destroy_qp(p->qp);
err_qp:
	kमुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक ipoib_cm_rx_handler(काष्ठा ib_cm_id *cm_id,
			       स्थिर काष्ठा ib_cm_event *event)
अणु
	काष्ठा ipoib_cm_rx *p;
	काष्ठा ipoib_dev_priv *priv;

	चयन (event->event) अणु
	हाल IB_CM_REQ_RECEIVED:
		वापस ipoib_cm_req_handler(cm_id, event);
	हाल IB_CM_DREQ_RECEIVED:
		ib_send_cm_drep(cm_id, शून्य, 0);
		fallthrough;
	हाल IB_CM_REJ_RECEIVED:
		p = cm_id->context;
		priv = ipoib_priv(p->dev);
		अगर (ib_modअगरy_qp(p->qp, &ipoib_cm_err_attr, IB_QP_STATE))
			ipoib_warn(priv, "unable to move qp to error state\n");
		fallthrough;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
/* Adjust length of skb with fragments to match received data */
अटल व्योम skb_put_frags(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hdr_space,
			  अचिन्हित पूर्णांक length, काष्ठा sk_buff *toskb)
अणु
	पूर्णांक i, num_frags;
	अचिन्हित पूर्णांक size;

	/* put header पूर्णांकo skb */
	size = min(length, hdr_space);
	skb->tail += size;
	skb->len += size;
	length -= size;

	num_frags = skb_shinfo(skb)->nr_frags;
	क्रम (i = 0; i < num_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		अगर (length == 0) अणु
			/* करोn't need this page */
			skb_fill_page_desc(toskb, i, skb_frag_page(frag),
					   0, PAGE_SIZE);
			--skb_shinfo(skb)->nr_frags;
		पूर्ण अन्यथा अणु
			size = min_t(अचिन्हित पूर्णांक, length, PAGE_SIZE);

			skb_frag_size_set(frag, size);
			skb->data_len += size;
			skb->truesize += size;
			skb->len += size;
			length -= size;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ipoib_cm_handle_rx_wc(काष्ठा net_device *dev, काष्ठा ib_wc *wc)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_cm_rx_buf *rx_ring;
	अचिन्हित पूर्णांक wr_id = wc->wr_id & ~(IPOIB_OP_CM | IPOIB_OP_RECV);
	काष्ठा sk_buff *skb, *newskb;
	काष्ठा ipoib_cm_rx *p;
	अचिन्हित दीर्घ flags;
	u64 mapping[IPOIB_CM_RX_SG];
	पूर्णांक frags;
	पूर्णांक has_srq;
	काष्ठा sk_buff *small_skb;

	ipoib_dbg_data(priv, "cm recv completion: id %d, status: %d\n",
		       wr_id, wc->status);

	अगर (unlikely(wr_id >= ipoib_recvq_size)) अणु
		अगर (wr_id == (IPOIB_CM_RX_DRAIN_WRID & ~(IPOIB_OP_CM | IPOIB_OP_RECV))) अणु
			spin_lock_irqsave(&priv->lock, flags);
			list_splice_init(&priv->cm.rx_drain_list, &priv->cm.rx_reap_list);
			ipoib_cm_start_rx_drain(priv);
			queue_work(priv->wq, &priv->cm.rx_reap_task);
			spin_unlock_irqrestore(&priv->lock, flags);
		पूर्ण अन्यथा
			ipoib_warn(priv, "cm recv completion event with wrid %d (> %d)\n",
				   wr_id, ipoib_recvq_size);
		वापस;
	पूर्ण

	p = wc->qp->qp_context;

	has_srq = ipoib_cm_has_srq(dev);
	rx_ring = has_srq ? priv->cm.srq_ring : p->rx_ring;

	skb = rx_ring[wr_id].skb;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		ipoib_dbg(priv,
			  "cm recv error (status=%d, wrid=%d vend_err %#x)\n",
			  wc->status, wr_id, wc->venकरोr_err);
		++dev->stats.rx_dropped;
		अगर (has_srq)
			जाओ repost;
		अन्यथा अणु
			अगर (!--p->recv_count) अणु
				spin_lock_irqsave(&priv->lock, flags);
				list_move(&p->list, &priv->cm.rx_reap_list);
				spin_unlock_irqrestore(&priv->lock, flags);
				queue_work(priv->wq, &priv->cm.rx_reap_task);
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण

	अगर (unlikely(!(wr_id & IPOIB_CM_RX_UPDATE_MASK))) अणु
		अगर (p && समय_after_eq(jअगरfies, p->jअगरfies + IPOIB_CM_RX_UPDATE_TIME)) अणु
			spin_lock_irqsave(&priv->lock, flags);
			p->jअगरfies = jअगरfies;
			/* Move this entry to list head, but करो not re-add it
			 * अगर it has been moved out of list. */
			अगर (p->state == IPOIB_CM_RX_LIVE)
				list_move(&p->list, &priv->cm.passive_ids);
			spin_unlock_irqrestore(&priv->lock, flags);
		पूर्ण
	पूर्ण

	अगर (wc->byte_len < IPOIB_CM_COPYBREAK) अणु
		पूर्णांक dlen = wc->byte_len;

		small_skb = dev_alloc_skb(dlen + IPOIB_CM_RX_RESERVE);
		अगर (small_skb) अणु
			skb_reserve(small_skb, IPOIB_CM_RX_RESERVE);
			ib_dma_sync_single_क्रम_cpu(priv->ca, rx_ring[wr_id].mapping[0],
						   dlen, DMA_FROM_DEVICE);
			skb_copy_from_linear_data(skb, small_skb->data, dlen);
			ib_dma_sync_single_क्रम_device(priv->ca, rx_ring[wr_id].mapping[0],
						      dlen, DMA_FROM_DEVICE);
			skb_put(small_skb, dlen);
			skb = small_skb;
			जाओ copied;
		पूर्ण
	पूर्ण

	frags = PAGE_ALIGN(wc->byte_len -
			   min_t(u32, wc->byte_len, IPOIB_CM_HEAD_SIZE)) /
		PAGE_SIZE;

	newskb = ipoib_cm_alloc_rx_skb(dev, rx_ring, wr_id, frags,
				       mapping, GFP_ATOMIC);
	अगर (unlikely(!newskb)) अणु
		/*
		 * If we can't allocate a new RX buffer, dump
		 * this packet and reuse the old buffer.
		 */
		ipoib_dbg(priv, "failed to allocate receive buffer %d\n", wr_id);
		++dev->stats.rx_dropped;
		जाओ repost;
	पूर्ण

	ipoib_cm_dma_unmap_rx(priv, frags, rx_ring[wr_id].mapping);
	स_नकल(rx_ring[wr_id].mapping, mapping, (frags + 1) * माप(*mapping));

	ipoib_dbg_data(priv, "received %d bytes, SLID 0x%04x\n",
		       wc->byte_len, wc->slid);

	skb_put_frags(skb, IPOIB_CM_HEAD_SIZE, wc->byte_len, newskb);

copied:
	skb->protocol = ((काष्ठा ipoib_header *) skb->data)->proto;
	skb_add_pseuकरो_hdr(skb);

	++dev->stats.rx_packets;
	dev->stats.rx_bytes += skb->len;

	skb->dev = dev;
	/* XXX get correct PACKET_ type here */
	skb->pkt_type = PACKET_HOST;
	netअगर_receive_skb(skb);

repost:
	अगर (has_srq) अणु
		अगर (unlikely(ipoib_cm_post_receive_srq(dev, wr_id)))
			ipoib_warn(priv, "ipoib_cm_post_receive_srq failed "
				   "for buf %d\n", wr_id);
	पूर्ण अन्यथा अणु
		अगर (unlikely(ipoib_cm_post_receive_nonsrq(dev, p,
							  &priv->cm.rx_wr,
							  priv->cm.rx_sge,
							  wr_id))) अणु
			--p->recv_count;
			ipoib_warn(priv, "ipoib_cm_post_receive_nonsrq failed "
				   "for buf %d\n", wr_id);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक post_send(काष्ठा ipoib_dev_priv *priv,
			    काष्ठा ipoib_cm_tx *tx,
			    अचिन्हित पूर्णांक wr_id,
			    काष्ठा ipoib_tx_buf *tx_req)
अणु
	ipoib_build_sge(priv, tx_req);

	priv->tx_wr.wr.wr_id	= wr_id | IPOIB_OP_CM;

	वापस ib_post_send(tx->qp, &priv->tx_wr.wr, शून्य);
पूर्ण

व्योम ipoib_cm_send(काष्ठा net_device *dev, काष्ठा sk_buff *skb, काष्ठा ipoib_cm_tx *tx)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_tx_buf *tx_req;
	पूर्णांक rc;
	अचिन्हित पूर्णांक usable_sge = tx->max_send_sge - !!skb_headlen(skb);

	अगर (unlikely(skb->len > tx->mtu)) अणु
		ipoib_warn(priv, "packet len %d (> %d) too long to send, dropping\n",
			   skb->len, tx->mtu);
		++dev->stats.tx_dropped;
		++dev->stats.tx_errors;
		ipoib_cm_skb_too_दीर्घ(dev, skb, tx->mtu - IPOIB_ENCAP_LEN);
		वापस;
	पूर्ण
	अगर (skb_shinfo(skb)->nr_frags > usable_sge) अणु
		अगर (skb_linearize(skb) < 0) अणु
			ipoib_warn(priv, "skb could not be linearized\n");
			++dev->stats.tx_dropped;
			++dev->stats.tx_errors;
			dev_kमुक्त_skb_any(skb);
			वापस;
		पूर्ण
		/* Does skb_linearize वापस ok without reducing nr_frags? */
		अगर (skb_shinfo(skb)->nr_frags > usable_sge) अणु
			ipoib_warn(priv, "too many frags after skb linearize\n");
			++dev->stats.tx_dropped;
			++dev->stats.tx_errors;
			dev_kमुक्त_skb_any(skb);
			वापस;
		पूर्ण
	पूर्ण
	ipoib_dbg_data(priv, "sending packet: head 0x%x length %d connection 0x%x\n",
		       tx->tx_head, skb->len, tx->qp->qp_num);

	/*
	 * We put the skb पूर्णांकo the tx_ring _beक्रमe_ we call post_send()
	 * because it's entirely possible that the completion handler will
	 * run beक्रमe we execute anything after the post_send().  That
	 * means we have to make sure everything is properly recorded and
	 * our state is consistent beक्रमe we call post_send().
	 */
	tx_req = &tx->tx_ring[tx->tx_head & (ipoib_sendq_size - 1)];
	tx_req->skb = skb;

	अगर (unlikely(ipoib_dma_map_tx(priv->ca, tx_req))) अणु
		++dev->stats.tx_errors;
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	अगर ((priv->global_tx_head - priv->global_tx_tail) ==
	    ipoib_sendq_size - 1) अणु
		ipoib_dbg(priv, "TX ring 0x%x full, stopping kernel net queue\n",
			  tx->qp->qp_num);
		netअगर_stop_queue(dev);
	पूर्ण

	skb_orphan(skb);
	skb_dst_drop(skb);

	अगर (netअगर_queue_stopped(dev)) अणु
		rc = ib_req_notअगरy_cq(priv->send_cq, IB_CQ_NEXT_COMP |
				      IB_CQ_REPORT_MISSED_EVENTS);
		अगर (unlikely(rc < 0))
			ipoib_warn(priv, "IPoIB/CM:request notify on send CQ failed\n");
		अन्यथा अगर (rc)
			napi_schedule(&priv->send_napi);
	पूर्ण

	rc = post_send(priv, tx, tx->tx_head & (ipoib_sendq_size - 1), tx_req);
	अगर (unlikely(rc)) अणु
		ipoib_warn(priv, "IPoIB/CM:post_send failed, error %d\n", rc);
		++dev->stats.tx_errors;
		ipoib_dma_unmap_tx(priv, tx_req);
		dev_kमुक्त_skb_any(skb);

		अगर (netअगर_queue_stopped(dev))
			netअगर_wake_queue(dev);
	पूर्ण अन्यथा अणु
		netअगर_trans_update(dev);
		++tx->tx_head;
		++priv->global_tx_head;
	पूर्ण
पूर्ण

व्योम ipoib_cm_handle_tx_wc(काष्ठा net_device *dev, काष्ठा ib_wc *wc)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_cm_tx *tx = wc->qp->qp_context;
	अचिन्हित पूर्णांक wr_id = wc->wr_id & ~IPOIB_OP_CM;
	काष्ठा ipoib_tx_buf *tx_req;
	अचिन्हित दीर्घ flags;

	ipoib_dbg_data(priv, "cm send completion: id %d, status: %d\n",
		       wr_id, wc->status);

	अगर (unlikely(wr_id >= ipoib_sendq_size)) अणु
		ipoib_warn(priv, "cm send completion event with wrid %d (> %d)\n",
			   wr_id, ipoib_sendq_size);
		वापस;
	पूर्ण

	tx_req = &tx->tx_ring[wr_id];

	ipoib_dma_unmap_tx(priv, tx_req);

	/* FIXME: is this right? Shouldn't we only increment on success? */
	++dev->stats.tx_packets;
	dev->stats.tx_bytes += tx_req->skb->len;

	dev_kमुक्त_skb_any(tx_req->skb);

	netअगर_tx_lock(dev);

	++tx->tx_tail;
	++priv->global_tx_tail;

	अगर (unlikely(netअगर_queue_stopped(dev) &&
		     ((priv->global_tx_head - priv->global_tx_tail) <=
		      ipoib_sendq_size >> 1) &&
		     test_bit(IPOIB_FLAG_ADMIN_UP, &priv->flags)))
		netअगर_wake_queue(dev);

	अगर (wc->status != IB_WC_SUCCESS &&
	    wc->status != IB_WC_WR_FLUSH_ERR) अणु
		काष्ठा ipoib_neigh *neigh;

		/* IB_WC[_RNR]_RETRY_EXC_ERR error is part of the lअगरe cycle,
		 * so करोn't make waves.
		 */
		अगर (wc->status == IB_WC_RNR_RETRY_EXC_ERR ||
		    wc->status == IB_WC_RETRY_EXC_ERR)
			ipoib_dbg(priv,
				  "%s: failed cm send event (status=%d, wrid=%d vend_err %#x)\n",
				   __func__, wc->status, wr_id, wc->venकरोr_err);
		अन्यथा
			ipoib_warn(priv,
				    "%s: failed cm send event (status=%d, wrid=%d vend_err %#x)\n",
				   __func__, wc->status, wr_id, wc->venकरोr_err);

		spin_lock_irqsave(&priv->lock, flags);
		neigh = tx->neigh;

		अगर (neigh) अणु
			neigh->cm = शून्य;
			ipoib_neigh_मुक्त(neigh);

			tx->neigh = शून्य;
		पूर्ण

		अगर (test_and_clear_bit(IPOIB_FLAG_INITIALIZED, &tx->flags)) अणु
			list_move(&tx->list, &priv->cm.reap_list);
			queue_work(priv->wq, &priv->cm.reap_task);
		पूर्ण

		clear_bit(IPOIB_FLAG_OPER_UP, &tx->flags);

		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण

	netअगर_tx_unlock(dev);
पूर्ण

पूर्णांक ipoib_cm_dev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक ret;

	अगर (!IPOIB_CM_SUPPORTED(dev->dev_addr))
		वापस 0;

	priv->cm.id = ib_create_cm_id(priv->ca, ipoib_cm_rx_handler, dev);
	अगर (IS_ERR(priv->cm.id)) अणु
		pr_warn("%s: failed to create CM ID\n", priv->ca->name);
		ret = PTR_ERR(priv->cm.id);
		जाओ err_cm;
	पूर्ण

	ret = ib_cm_listen(priv->cm.id, cpu_to_be64(IPOIB_CM_IETF_ID | priv->qp->qp_num),
			   0);
	अगर (ret) अणु
		pr_warn("%s: failed to listen on ID 0x%llx\n", priv->ca->name,
			IPOIB_CM_IETF_ID | priv->qp->qp_num);
		जाओ err_listen;
	पूर्ण

	वापस 0;

err_listen:
	ib_destroy_cm_id(priv->cm.id);
err_cm:
	priv->cm.id = शून्य;
	वापस ret;
पूर्ण

अटल व्योम ipoib_cm_मुक्त_rx_reap_list(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_cm_rx *rx, *n;
	LIST_HEAD(list);

	spin_lock_irq(&priv->lock);
	list_splice_init(&priv->cm.rx_reap_list, &list);
	spin_unlock_irq(&priv->lock);

	list_क्रम_each_entry_safe(rx, n, &list, list) अणु
		ib_destroy_cm_id(rx->id);
		ib_destroy_qp(rx->qp);
		अगर (!ipoib_cm_has_srq(dev)) अणु
			ipoib_cm_मुक्त_rx_ring(priv->dev, rx->rx_ring);
			spin_lock_irq(&priv->lock);
			--priv->cm.nonsrq_conn_qp;
			spin_unlock_irq(&priv->lock);
		पूर्ण
		kमुक्त(rx);
	पूर्ण
पूर्ण

व्योम ipoib_cm_dev_stop(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_cm_rx *p;
	अचिन्हित दीर्घ begin;
	पूर्णांक ret;

	अगर (!IPOIB_CM_SUPPORTED(dev->dev_addr) || !priv->cm.id)
		वापस;

	ib_destroy_cm_id(priv->cm.id);
	priv->cm.id = शून्य;

	spin_lock_irq(&priv->lock);
	जबतक (!list_empty(&priv->cm.passive_ids)) अणु
		p = list_entry(priv->cm.passive_ids.next, typeof(*p), list);
		list_move(&p->list, &priv->cm.rx_error_list);
		p->state = IPOIB_CM_RX_ERROR;
		spin_unlock_irq(&priv->lock);
		ret = ib_modअगरy_qp(p->qp, &ipoib_cm_err_attr, IB_QP_STATE);
		अगर (ret)
			ipoib_warn(priv, "unable to move qp to error state: %d\n", ret);
		spin_lock_irq(&priv->lock);
	पूर्ण

	/* Wait क्रम all RX to be drained */
	begin = jअगरfies;

	जबतक (!list_empty(&priv->cm.rx_error_list) ||
	       !list_empty(&priv->cm.rx_flush_list) ||
	       !list_empty(&priv->cm.rx_drain_list)) अणु
		अगर (समय_after(jअगरfies, begin + 5 * HZ)) अणु
			ipoib_warn(priv, "RX drain timing out\n");

			/*
			 * assume the HW is wedged and just मुक्त up everything.
			 */
			list_splice_init(&priv->cm.rx_flush_list,
					 &priv->cm.rx_reap_list);
			list_splice_init(&priv->cm.rx_error_list,
					 &priv->cm.rx_reap_list);
			list_splice_init(&priv->cm.rx_drain_list,
					 &priv->cm.rx_reap_list);
			अवरोध;
		पूर्ण
		spin_unlock_irq(&priv->lock);
		usleep_range(1000, 2000);
		ipoib_drain_cq(dev);
		spin_lock_irq(&priv->lock);
	पूर्ण

	spin_unlock_irq(&priv->lock);

	ipoib_cm_मुक्त_rx_reap_list(dev);

	cancel_delayed_work(&priv->cm.stale_task);
पूर्ण

अटल पूर्णांक ipoib_cm_rep_handler(काष्ठा ib_cm_id *cm_id,
				स्थिर काष्ठा ib_cm_event *event)
अणु
	काष्ठा ipoib_cm_tx *p = cm_id->context;
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(p->dev);
	काष्ठा ipoib_cm_data *data = event->निजी_data;
	काष्ठा sk_buff_head skqueue;
	काष्ठा ib_qp_attr qp_attr;
	पूर्णांक qp_attr_mask, ret;
	काष्ठा sk_buff *skb;

	p->mtu = be32_to_cpu(data->mtu);

	अगर (p->mtu <= IPOIB_ENCAP_LEN) अणु
		ipoib_warn(priv, "Rejecting connection: mtu %d <= %d\n",
			   p->mtu, IPOIB_ENCAP_LEN);
		वापस -EINVAL;
	पूर्ण

	qp_attr.qp_state = IB_QPS_RTR;
	ret = ib_cm_init_qp_attr(cm_id, &qp_attr, &qp_attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to init QP attr for RTR: %d\n", ret);
		वापस ret;
	पूर्ण

	qp_attr.rq_psn = 0 /* FIXME */;
	ret = ib_modअगरy_qp(p->qp, &qp_attr, qp_attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to modify QP to RTR: %d\n", ret);
		वापस ret;
	पूर्ण

	qp_attr.qp_state = IB_QPS_RTS;
	ret = ib_cm_init_qp_attr(cm_id, &qp_attr, &qp_attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to init QP attr for RTS: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = ib_modअगरy_qp(p->qp, &qp_attr, qp_attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to modify QP to RTS: %d\n", ret);
		वापस ret;
	पूर्ण

	skb_queue_head_init(&skqueue);

	netअगर_tx_lock_bh(p->dev);
	spin_lock_irq(&priv->lock);
	set_bit(IPOIB_FLAG_OPER_UP, &p->flags);
	अगर (p->neigh)
		जबतक ((skb = __skb_dequeue(&p->neigh->queue)))
			__skb_queue_tail(&skqueue, skb);
	spin_unlock_irq(&priv->lock);
	netअगर_tx_unlock_bh(p->dev);

	जबतक ((skb = __skb_dequeue(&skqueue))) अणु
		skb->dev = p->dev;
		ret = dev_queue_xmit(skb);
		अगर (ret)
			ipoib_warn(priv, "%s:dev_queue_xmit failed to re-queue packet, ret:%d\n",
				   __func__, ret);
	पूर्ण

	ret = ib_send_cm_rtu(cm_id, शून्य, 0);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to send RTU: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा ib_qp *ipoib_cm_create_tx_qp(काष्ठा net_device *dev, काष्ठा ipoib_cm_tx *tx)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ib_qp_init_attr attr = अणु
		.send_cq		= priv->send_cq,
		.recv_cq		= priv->recv_cq,
		.srq			= priv->cm.srq,
		.cap.max_send_wr	= ipoib_sendq_size,
		.cap.max_send_sge	= 1,
		.sq_sig_type		= IB_SIGNAL_ALL_WR,
		.qp_type		= IB_QPT_RC,
		.qp_context		= tx,
		.create_flags		= 0
	पूर्ण;
	काष्ठा ib_qp *tx_qp;

	अगर (dev->features & NETIF_F_SG)
		attr.cap.max_send_sge = min_t(u32, priv->ca->attrs.max_send_sge,
					      MAX_SKB_FRAGS + 1);

	tx_qp = ib_create_qp(priv->pd, &attr);
	tx->max_send_sge = attr.cap.max_send_sge;
	वापस tx_qp;
पूर्ण

अटल पूर्णांक ipoib_cm_send_req(काष्ठा net_device *dev,
			     काष्ठा ib_cm_id *id, काष्ठा ib_qp *qp,
			     u32 qpn,
			     काष्ठा sa_path_rec *pathrec)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_cm_data data = अणुपूर्ण;
	काष्ठा ib_cm_req_param req = अणुपूर्ण;

	data.qpn = cpu_to_be32(priv->qp->qp_num);
	data.mtu = cpu_to_be32(IPOIB_CM_BUF_SIZE);

	req.primary_path		= pathrec;
	req.alternate_path		= शून्य;
	req.service_id			= cpu_to_be64(IPOIB_CM_IETF_ID | qpn);
	req.qp_num			= qp->qp_num;
	req.qp_type			= qp->qp_type;
	req.निजी_data		= &data;
	req.निजी_data_len		= माप(data);
	req.flow_control		= 0;

	req.starting_psn		= 0; /* FIXME */

	/*
	 * Pick some arbitrary शेषs here; we could make these
	 * module parameters अगर anyone cared about setting them.
	 */
	req.responder_resources		= 4;
	req.remote_cm_response_समयout	= 20;
	req.local_cm_response_समयout	= 20;
	req.retry_count			= 0; /* RFC draft warns against retries */
	req.rnr_retry_count		= 0; /* RFC draft warns against retries */
	req.max_cm_retries		= 15;
	req.srq				= ipoib_cm_has_srq(dev);
	वापस ib_send_cm_req(id, &req);
पूर्ण

अटल पूर्णांक ipoib_cm_modअगरy_tx_init(काष्ठा net_device *dev,
				  काष्ठा ib_cm_id *cm_id, काष्ठा ib_qp *qp)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ib_qp_attr qp_attr;
	पूर्णांक qp_attr_mask, ret;

	qp_attr.pkey_index = priv->pkey_index;
	qp_attr.qp_state = IB_QPS_INIT;
	qp_attr.qp_access_flags = IB_ACCESS_LOCAL_WRITE;
	qp_attr.port_num = priv->port;
	qp_attr_mask = IB_QP_STATE | IB_QP_ACCESS_FLAGS | IB_QP_PKEY_INDEX | IB_QP_PORT;

	ret = ib_modअगरy_qp(qp, &qp_attr, qp_attr_mask);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to modify tx QP to INIT: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ipoib_cm_tx_init(काष्ठा ipoib_cm_tx *p, u32 qpn,
			    काष्ठा sa_path_rec *pathrec)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(p->dev);
	अचिन्हित पूर्णांक noio_flag;
	पूर्णांक ret;

	noio_flag = meदो_स्मृति_noio_save();
	p->tx_ring = vzalloc(array_size(ipoib_sendq_size, माप(*p->tx_ring)));
	अगर (!p->tx_ring) अणु
		meदो_स्मृति_noio_restore(noio_flag);
		ret = -ENOMEM;
		जाओ err_tx;
	पूर्ण

	p->qp = ipoib_cm_create_tx_qp(p->dev, p);
	meदो_स्मृति_noio_restore(noio_flag);
	अगर (IS_ERR(p->qp)) अणु
		ret = PTR_ERR(p->qp);
		ipoib_warn(priv, "failed to create tx qp: %d\n", ret);
		जाओ err_qp;
	पूर्ण

	p->id = ib_create_cm_id(priv->ca, ipoib_cm_tx_handler, p);
	अगर (IS_ERR(p->id)) अणु
		ret = PTR_ERR(p->id);
		ipoib_warn(priv, "failed to create tx cm id: %d\n", ret);
		जाओ err_id;
	पूर्ण

	ret = ipoib_cm_modअगरy_tx_init(p->dev, p->id,  p->qp);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to modify tx qp to rtr: %d\n", ret);
		जाओ err_modअगरy_send;
	पूर्ण

	ret = ipoib_cm_send_req(p->dev, p->id, p->qp, qpn, pathrec);
	अगर (ret) अणु
		ipoib_warn(priv, "failed to send cm req: %d\n", ret);
		जाओ err_modअगरy_send;
	पूर्ण

	ipoib_dbg(priv, "Request connection 0x%x for gid %pI6 qpn 0x%x\n",
		  p->qp->qp_num, pathrec->dgid.raw, qpn);

	वापस 0;

err_modअगरy_send:
	ib_destroy_cm_id(p->id);
err_id:
	p->id = शून्य;
	ib_destroy_qp(p->qp);
err_qp:
	p->qp = शून्य;
	vमुक्त(p->tx_ring);
err_tx:
	वापस ret;
पूर्ण

अटल व्योम ipoib_cm_tx_destroy(काष्ठा ipoib_cm_tx *p)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(p->dev);
	काष्ठा ipoib_tx_buf *tx_req;
	अचिन्हित दीर्घ begin;

	ipoib_dbg(priv, "Destroy active connection 0x%x head 0x%x tail 0x%x\n",
		  p->qp ? p->qp->qp_num : 0, p->tx_head, p->tx_tail);

	अगर (p->id)
		ib_destroy_cm_id(p->id);

	अगर (p->tx_ring) अणु
		/* Wait क्रम all sends to complete */
		begin = jअगरfies;
		जबतक ((पूर्णांक) p->tx_tail - (पूर्णांक) p->tx_head < 0) अणु
			अगर (समय_after(jअगरfies, begin + 5 * HZ)) अणु
				ipoib_warn(priv, "timing out; %d sends not completed\n",
					   p->tx_head - p->tx_tail);
				जाओ समयout;
			पूर्ण

			usleep_range(1000, 2000);
		पूर्ण
	पूर्ण

समयout:

	जबतक ((पूर्णांक) p->tx_tail - (पूर्णांक) p->tx_head < 0) अणु
		tx_req = &p->tx_ring[p->tx_tail & (ipoib_sendq_size - 1)];
		ipoib_dma_unmap_tx(priv, tx_req);
		dev_kमुक्त_skb_any(tx_req->skb);
		netअगर_tx_lock_bh(p->dev);
		++p->tx_tail;
		++priv->global_tx_tail;
		अगर (unlikely((priv->global_tx_head - priv->global_tx_tail) <=
			     ipoib_sendq_size >> 1) &&
		    netअगर_queue_stopped(p->dev) &&
		    test_bit(IPOIB_FLAG_ADMIN_UP, &priv->flags))
			netअगर_wake_queue(p->dev);
		netअगर_tx_unlock_bh(p->dev);
	पूर्ण

	अगर (p->qp)
		ib_destroy_qp(p->qp);

	vमुक्त(p->tx_ring);
	kमुक्त(p);
पूर्ण

अटल पूर्णांक ipoib_cm_tx_handler(काष्ठा ib_cm_id *cm_id,
			       स्थिर काष्ठा ib_cm_event *event)
अणु
	काष्ठा ipoib_cm_tx *tx = cm_id->context;
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(tx->dev);
	काष्ठा net_device *dev = priv->dev;
	काष्ठा ipoib_neigh *neigh;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	चयन (event->event) अणु
	हाल IB_CM_DREQ_RECEIVED:
		ipoib_dbg(priv, "DREQ received.\n");
		ib_send_cm_drep(cm_id, शून्य, 0);
		अवरोध;
	हाल IB_CM_REP_RECEIVED:
		ipoib_dbg(priv, "REP received.\n");
		ret = ipoib_cm_rep_handler(cm_id, event);
		अगर (ret)
			ib_send_cm_rej(cm_id, IB_CM_REJ_CONSUMER_DEFINED,
				       शून्य, 0, शून्य, 0);
		अवरोध;
	हाल IB_CM_REQ_ERROR:
	हाल IB_CM_REJ_RECEIVED:
	हाल IB_CM_TIMEWAIT_EXIT:
		ipoib_dbg(priv, "CM error %d.\n", event->event);
		netअगर_tx_lock_bh(dev);
		spin_lock_irqsave(&priv->lock, flags);
		neigh = tx->neigh;

		अगर (neigh) अणु
			neigh->cm = शून्य;
			ipoib_neigh_मुक्त(neigh);

			tx->neigh = शून्य;
		पूर्ण

		अगर (test_and_clear_bit(IPOIB_FLAG_INITIALIZED, &tx->flags)) अणु
			list_move(&tx->list, &priv->cm.reap_list);
			queue_work(priv->wq, &priv->cm.reap_task);
		पूर्ण

		spin_unlock_irqrestore(&priv->lock, flags);
		netअगर_tx_unlock_bh(dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा ipoib_cm_tx *ipoib_cm_create_tx(काष्ठा net_device *dev, काष्ठा ipoib_path *path,
				       काष्ठा ipoib_neigh *neigh)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_cm_tx *tx;

	tx = kzalloc(माप(*tx), GFP_ATOMIC);
	अगर (!tx)
		वापस शून्य;

	neigh->cm = tx;
	tx->neigh = neigh;
	tx->dev = dev;
	list_add(&tx->list, &priv->cm.start_list);
	set_bit(IPOIB_FLAG_INITIALIZED, &tx->flags);
	queue_work(priv->wq, &priv->cm.start_task);
	वापस tx;
पूर्ण

व्योम ipoib_cm_destroy_tx(काष्ठा ipoib_cm_tx *tx)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(tx->dev);
	अचिन्हित दीर्घ flags;
	अगर (test_and_clear_bit(IPOIB_FLAG_INITIALIZED, &tx->flags)) अणु
		spin_lock_irqsave(&priv->lock, flags);
		list_move(&tx->list, &priv->cm.reap_list);
		queue_work(priv->wq, &priv->cm.reap_task);
		ipoib_dbg(priv, "Reap connection for gid %pI6\n",
			  tx->neigh->daddr + 4);
		tx->neigh = शून्य;
		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण
पूर्ण

#घोषणा QPN_AND_OPTIONS_OFFSET	4

अटल व्योम ipoib_cm_tx_start(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_dev_priv *priv = container_of(work, काष्ठा ipoib_dev_priv,
						   cm.start_task);
	काष्ठा net_device *dev = priv->dev;
	काष्ठा ipoib_neigh *neigh;
	काष्ठा ipoib_cm_tx *p;
	अचिन्हित दीर्घ flags;
	काष्ठा ipoib_path *path;
	पूर्णांक ret;

	काष्ठा sa_path_rec pathrec;
	u32 qpn;

	netअगर_tx_lock_bh(dev);
	spin_lock_irqsave(&priv->lock, flags);

	जबतक (!list_empty(&priv->cm.start_list)) अणु
		p = list_entry(priv->cm.start_list.next, typeof(*p), list);
		list_del_init(&p->list);
		neigh = p->neigh;

		qpn = IPOIB_QPN(neigh->daddr);
		/*
		 * As दीर्घ as the search is with these 2 locks,
		 * path existence indicates its validity.
		 */
		path = __path_find(dev, neigh->daddr + QPN_AND_OPTIONS_OFFSET);
		अगर (!path) अणु
			pr_info("%s ignore not valid path %pI6\n",
				__func__,
				neigh->daddr + QPN_AND_OPTIONS_OFFSET);
			जाओ मुक्त_neigh;
		पूर्ण
		स_नकल(&pathrec, &path->pathrec, माप(pathrec));

		spin_unlock_irqrestore(&priv->lock, flags);
		netअगर_tx_unlock_bh(dev);

		ret = ipoib_cm_tx_init(p, qpn, &pathrec);

		netअगर_tx_lock_bh(dev);
		spin_lock_irqsave(&priv->lock, flags);

		अगर (ret) अणु
मुक्त_neigh:
			neigh = p->neigh;
			अगर (neigh) अणु
				neigh->cm = शून्य;
				ipoib_neigh_मुक्त(neigh);
			पूर्ण
			list_del(&p->list);
			kमुक्त(p);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
	netअगर_tx_unlock_bh(dev);
पूर्ण

अटल व्योम ipoib_cm_tx_reap(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_dev_priv *priv = container_of(work, काष्ठा ipoib_dev_priv,
						   cm.reap_task);
	काष्ठा net_device *dev = priv->dev;
	काष्ठा ipoib_cm_tx *p;
	अचिन्हित दीर्घ flags;

	netअगर_tx_lock_bh(dev);
	spin_lock_irqsave(&priv->lock, flags);

	जबतक (!list_empty(&priv->cm.reap_list)) अणु
		p = list_entry(priv->cm.reap_list.next, typeof(*p), list);
		list_del_init(&p->list);
		spin_unlock_irqrestore(&priv->lock, flags);
		netअगर_tx_unlock_bh(dev);
		ipoib_cm_tx_destroy(p);
		netअगर_tx_lock_bh(dev);
		spin_lock_irqsave(&priv->lock, flags);
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
	netअगर_tx_unlock_bh(dev);
पूर्ण

अटल व्योम ipoib_cm_skb_reap(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_dev_priv *priv = container_of(work, काष्ठा ipoib_dev_priv,
						   cm.skb_task);
	काष्ठा net_device *dev = priv->dev;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mtu = priv->mcast_mtu;

	netअगर_tx_lock_bh(dev);
	spin_lock_irqsave(&priv->lock, flags);

	जबतक ((skb = skb_dequeue(&priv->cm.skb_queue))) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		netअगर_tx_unlock_bh(dev);

		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			स_रखो(IPCB(skb), 0, माप(*IPCB(skb)));
			icmp_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED, htonl(mtu));
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
		अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
			स_रखो(IP6CB(skb), 0, माप(*IP6CB(skb)));
			icmpv6_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		पूर्ण
#पूर्ण_अगर
		dev_kमुक्त_skb_any(skb);

		netअगर_tx_lock_bh(dev);
		spin_lock_irqsave(&priv->lock, flags);
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
	netअगर_tx_unlock_bh(dev);
पूर्ण

व्योम ipoib_cm_skb_too_दीर्घ(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			   अचिन्हित पूर्णांक mtu)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक e = skb_queue_empty(&priv->cm.skb_queue);

	skb_dst_update_pmtu(skb, mtu);

	skb_queue_tail(&priv->cm.skb_queue, skb);
	अगर (e)
		queue_work(priv->wq, &priv->cm.skb_task);
पूर्ण

अटल व्योम ipoib_cm_rx_reap(काष्ठा work_काष्ठा *work)
अणु
	ipoib_cm_मुक्त_rx_reap_list(container_of(work, काष्ठा ipoib_dev_priv,
						cm.rx_reap_task)->dev);
पूर्ण

अटल व्योम ipoib_cm_stale_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_dev_priv *priv = container_of(work, काष्ठा ipoib_dev_priv,
						   cm.stale_task.work);
	काष्ठा ipoib_cm_rx *p;
	पूर्णांक ret;

	spin_lock_irq(&priv->lock);
	जबतक (!list_empty(&priv->cm.passive_ids)) अणु
		/* List is sorted by LRU, start from tail,
		 * stop when we see a recently used entry */
		p = list_entry(priv->cm.passive_ids.prev, typeof(*p), list);
		अगर (समय_beक्रमe_eq(jअगरfies, p->jअगरfies + IPOIB_CM_RX_TIMEOUT))
			अवरोध;
		list_move(&p->list, &priv->cm.rx_error_list);
		p->state = IPOIB_CM_RX_ERROR;
		spin_unlock_irq(&priv->lock);
		ret = ib_modअगरy_qp(p->qp, &ipoib_cm_err_attr, IB_QP_STATE);
		अगर (ret)
			ipoib_warn(priv, "unable to move qp to error state: %d\n", ret);
		spin_lock_irq(&priv->lock);
	पूर्ण

	अगर (!list_empty(&priv->cm.passive_ids))
		queue_delayed_work(priv->wq,
				   &priv->cm.stale_task, IPOIB_CM_RX_DELAY);
	spin_unlock_irq(&priv->lock);
पूर्ण

अटल sमाप_प्रकार show_mode(काष्ठा device *d, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा net_device *dev = to_net_dev(d);
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	अगर (test_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags))
		वापस sysfs_emit(buf, "connected\n");
	अन्यथा
		वापस sysfs_emit(buf, "datagram\n");
पूर्ण

अटल sमाप_प्रकार set_mode(काष्ठा device *d, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा net_device *dev = to_net_dev(d);
	पूर्णांक ret;

	अगर (!rtnl_trylock()) अणु
		वापस restart_syscall();
	पूर्ण

	अगर (dev->reg_state != NETREG_REGISTERED) अणु
		rtnl_unlock();
		वापस -EPERM;
	पूर्ण

	ret = ipoib_set_mode(dev, buf);

	/* The assumption is that the function ipoib_set_mode वापसed
	 * with the rtnl held by it, अगर not the value -EBUSY वापसed,
	 * then no need to rtnl_unlock
	 */
	अगर (ret != -EBUSY)
		rtnl_unlock();

	वापस (!ret || ret == -EBUSY) ? count : ret;
पूर्ण

अटल DEVICE_ATTR(mode, S_IWUSR | S_IRUGO, show_mode, set_mode);

पूर्णांक ipoib_cm_add_mode_attr(काष्ठा net_device *dev)
अणु
	वापस device_create_file(&dev->dev, &dev_attr_mode);
पूर्ण

अटल व्योम ipoib_cm_create_srq(काष्ठा net_device *dev, पूर्णांक max_sge)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ib_srq_init_attr srq_init_attr = अणु
		.srq_type = IB_SRQT_BASIC,
		.attr = अणु
			.max_wr  = ipoib_recvq_size,
			.max_sge = max_sge
		पूर्ण
	पूर्ण;

	priv->cm.srq = ib_create_srq(priv->pd, &srq_init_attr);
	अगर (IS_ERR(priv->cm.srq)) अणु
		अगर (PTR_ERR(priv->cm.srq) != -EOPNOTSUPP)
			pr_warn("%s: failed to allocate SRQ, error %ld\n",
			       priv->ca->name, PTR_ERR(priv->cm.srq));
		priv->cm.srq = शून्य;
		वापस;
	पूर्ण

	priv->cm.srq_ring = vzalloc(array_size(ipoib_recvq_size,
					       माप(*priv->cm.srq_ring)));
	अगर (!priv->cm.srq_ring) अणु
		ib_destroy_srq(priv->cm.srq);
		priv->cm.srq = शून्य;
		वापस;
	पूर्ण

पूर्ण

पूर्णांक ipoib_cm_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक max_srq_sge, i;

	INIT_LIST_HEAD(&priv->cm.passive_ids);
	INIT_LIST_HEAD(&priv->cm.reap_list);
	INIT_LIST_HEAD(&priv->cm.start_list);
	INIT_LIST_HEAD(&priv->cm.rx_error_list);
	INIT_LIST_HEAD(&priv->cm.rx_flush_list);
	INIT_LIST_HEAD(&priv->cm.rx_drain_list);
	INIT_LIST_HEAD(&priv->cm.rx_reap_list);
	INIT_WORK(&priv->cm.start_task, ipoib_cm_tx_start);
	INIT_WORK(&priv->cm.reap_task, ipoib_cm_tx_reap);
	INIT_WORK(&priv->cm.skb_task, ipoib_cm_skb_reap);
	INIT_WORK(&priv->cm.rx_reap_task, ipoib_cm_rx_reap);
	INIT_DELAYED_WORK(&priv->cm.stale_task, ipoib_cm_stale_task);

	skb_queue_head_init(&priv->cm.skb_queue);

	ipoib_dbg(priv, "max_srq_sge=%d\n", priv->ca->attrs.max_srq_sge);

	max_srq_sge = min_t(पूर्णांक, IPOIB_CM_RX_SG, priv->ca->attrs.max_srq_sge);
	ipoib_cm_create_srq(dev, max_srq_sge);
	अगर (ipoib_cm_has_srq(dev)) अणु
		priv->cm.max_cm_mtu = max_srq_sge * PAGE_SIZE - 0x10;
		priv->cm.num_frags  = max_srq_sge;
		ipoib_dbg(priv, "max_cm_mtu = 0x%x, num_frags=%d\n",
			  priv->cm.max_cm_mtu, priv->cm.num_frags);
	पूर्ण अन्यथा अणु
		priv->cm.max_cm_mtu = IPOIB_CM_MTU;
		priv->cm.num_frags  = IPOIB_CM_RX_SG;
	पूर्ण

	ipoib_cm_init_rx_wr(dev, &priv->cm.rx_wr, priv->cm.rx_sge);

	अगर (ipoib_cm_has_srq(dev)) अणु
		क्रम (i = 0; i < ipoib_recvq_size; ++i) अणु
			अगर (!ipoib_cm_alloc_rx_skb(dev, priv->cm.srq_ring, i,
						   priv->cm.num_frags - 1,
						   priv->cm.srq_ring[i].mapping,
						   GFP_KERNEL)) अणु
				ipoib_warn(priv, "failed to allocate "
					   "receive buffer %d\n", i);
				ipoib_cm_dev_cleanup(dev);
				वापस -ENOMEM;
			पूर्ण

			अगर (ipoib_cm_post_receive_srq(dev, i)) अणु
				ipoib_warn(priv, "ipoib_cm_post_receive_srq "
					   "failed for buf %d\n", i);
				ipoib_cm_dev_cleanup(dev);
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण

	priv->dev->dev_addr[0] = IPOIB_FLAGS_RC;
	वापस 0;
पूर्ण

व्योम ipoib_cm_dev_cleanup(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	अगर (!priv->cm.srq)
		वापस;

	ipoib_dbg(priv, "Cleanup ipoib connected mode.\n");

	ib_destroy_srq(priv->cm.srq);
	priv->cm.srq = शून्य;
	अगर (!priv->cm.srq_ring)
		वापस;

	ipoib_cm_मुक्त_rx_ring(dev, priv->cm.srq_ring);
	priv->cm.srq_ring = शून्य;
पूर्ण
