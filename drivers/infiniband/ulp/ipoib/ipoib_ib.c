<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2004, 2005 Voltaire, Inc. All rights reserved.
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

#समावेश <linux/delay.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <rdma/ib_cache.h>

#समावेश "ipoib.h"

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG_DATA
अटल पूर्णांक data_debug_level;

module_param(data_debug_level, पूर्णांक, 0644);
MODULE_PARM_DESC(data_debug_level,
		 "Enable data path debug tracing if > 0");
#पूर्ण_अगर

काष्ठा ipoib_ah *ipoib_create_ah(काष्ठा net_device *dev,
				 काष्ठा ib_pd *pd, काष्ठा rdma_ah_attr *attr)
अणु
	काष्ठा ipoib_ah *ah;
	काष्ठा ib_ah *vah;

	ah = kदो_स्मृति(माप(*ah), GFP_KERNEL);
	अगर (!ah)
		वापस ERR_PTR(-ENOMEM);

	ah->dev       = dev;
	ah->last_send = 0;
	kref_init(&ah->ref);

	vah = rdma_create_ah(pd, attr, RDMA_CREATE_AH_SLEEPABLE);
	अगर (IS_ERR(vah)) अणु
		kमुक्त(ah);
		ah = (काष्ठा ipoib_ah *)vah;
	पूर्ण अन्यथा अणु
		ah->ah = vah;
		ipoib_dbg(ipoib_priv(dev), "Created ah %p\n", ah->ah);
	पूर्ण

	वापस ah;
पूर्ण

व्योम ipoib_मुक्त_ah(काष्ठा kref *kref)
अणु
	काष्ठा ipoib_ah *ah = container_of(kref, काष्ठा ipoib_ah, ref);
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(ah->dev);

	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	list_add_tail(&ah->list, &priv->dead_ahs);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम ipoib_ud_dma_unmap_rx(काष्ठा ipoib_dev_priv *priv,
				  u64 mapping[IPOIB_UD_RX_SG])
अणु
	ib_dma_unmap_single(priv->ca, mapping[0],
			    IPOIB_UD_BUF_SIZE(priv->max_ib_mtu),
			    DMA_FROM_DEVICE);
पूर्ण

अटल पूर्णांक ipoib_ib_post_receive(काष्ठा net_device *dev, पूर्णांक id)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक ret;

	priv->rx_wr.wr_id   = id | IPOIB_OP_RECV;
	priv->rx_sge[0].addr = priv->rx_ring[id].mapping[0];
	priv->rx_sge[1].addr = priv->rx_ring[id].mapping[1];


	ret = ib_post_recv(priv->qp, &priv->rx_wr, शून्य);
	अगर (unlikely(ret)) अणु
		ipoib_warn(priv, "receive failed for buf %d (%d)\n", id, ret);
		ipoib_ud_dma_unmap_rx(priv, priv->rx_ring[id].mapping);
		dev_kमुक्त_skb_any(priv->rx_ring[id].skb);
		priv->rx_ring[id].skb = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा sk_buff *ipoib_alloc_rx_skb(काष्ठा net_device *dev, पूर्णांक id)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा sk_buff *skb;
	पूर्णांक buf_size;
	u64 *mapping;

	buf_size = IPOIB_UD_BUF_SIZE(priv->max_ib_mtu);

	skb = dev_alloc_skb(buf_size + IPOIB_HARD_LEN);
	अगर (unlikely(!skb))
		वापस शून्य;

	/*
	 * the IP header will be at IPOIP_HARD_LEN + IB_GRH_BYTES, that is
	 * 64 bytes aligned
	 */
	skb_reserve(skb, माप(काष्ठा ipoib_pseuकरो_header));

	mapping = priv->rx_ring[id].mapping;
	mapping[0] = ib_dma_map_single(priv->ca, skb->data, buf_size,
				       DMA_FROM_DEVICE);
	अगर (unlikely(ib_dma_mapping_error(priv->ca, mapping[0])))
		जाओ error;

	priv->rx_ring[id].skb = skb;
	वापस skb;
error:
	dev_kमुक्त_skb_any(skb);
	वापस शून्य;
पूर्ण

अटल पूर्णांक ipoib_ib_post_receives(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < ipoib_recvq_size; ++i) अणु
		अगर (!ipoib_alloc_rx_skb(dev, i)) अणु
			ipoib_warn(priv, "failed to allocate receive buffer %d\n", i);
			वापस -ENOMEM;
		पूर्ण
		अगर (ipoib_ib_post_receive(dev, i)) अणु
			ipoib_warn(priv, "ipoib_ib_post_receive failed for buf %d\n", i);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ipoib_ib_handle_rx_wc(काष्ठा net_device *dev, काष्ठा ib_wc *wc)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	अचिन्हित पूर्णांक wr_id = wc->wr_id & ~IPOIB_OP_RECV;
	काष्ठा sk_buff *skb;
	u64 mapping[IPOIB_UD_RX_SG];
	जोड़ ib_gid *dgid;
	जोड़ ib_gid *sgid;

	ipoib_dbg_data(priv, "recv completion: id %d, status: %d\n",
		       wr_id, wc->status);

	अगर (unlikely(wr_id >= ipoib_recvq_size)) अणु
		ipoib_warn(priv, "recv completion event with wrid %d (> %d)\n",
			   wr_id, ipoib_recvq_size);
		वापस;
	पूर्ण

	skb  = priv->rx_ring[wr_id].skb;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		अगर (wc->status != IB_WC_WR_FLUSH_ERR)
			ipoib_warn(priv,
				   "failed recv event (status=%d, wrid=%d vend_err %#x)\n",
				   wc->status, wr_id, wc->venकरोr_err);
		ipoib_ud_dma_unmap_rx(priv, priv->rx_ring[wr_id].mapping);
		dev_kमुक्त_skb_any(skb);
		priv->rx_ring[wr_id].skb = शून्य;
		वापस;
	पूर्ण

	स_नकल(mapping, priv->rx_ring[wr_id].mapping,
	       IPOIB_UD_RX_SG * माप(*mapping));

	/*
	 * If we can't allocate a new RX buffer, dump
	 * this packet and reuse the old buffer.
	 */
	अगर (unlikely(!ipoib_alloc_rx_skb(dev, wr_id))) अणु
		++dev->stats.rx_dropped;
		जाओ repost;
	पूर्ण

	ipoib_dbg_data(priv, "received %d bytes, SLID 0x%04x\n",
		       wc->byte_len, wc->slid);

	ipoib_ud_dma_unmap_rx(priv, mapping);

	skb_put(skb, wc->byte_len);

	/* First byte of dgid संकेतs multicast when 0xff */
	dgid = &((काष्ठा ib_grh *)skb->data)->dgid;

	अगर (!(wc->wc_flags & IB_WC_GRH) || dgid->raw[0] != 0xff)
		skb->pkt_type = PACKET_HOST;
	अन्यथा अगर (स_भेद(dgid, dev->broadcast + 4, माप(जोड़ ib_gid)) == 0)
		skb->pkt_type = PACKET_BROADCAST;
	अन्यथा
		skb->pkt_type = PACKET_MULTICAST;

	sgid = &((काष्ठा ib_grh *)skb->data)->sgid;

	/*
	 * Drop packets that this पूर्णांकerface sent, ie multicast packets
	 * that the HCA has replicated.
	 */
	अगर (wc->slid == priv->local_lid && wc->src_qp == priv->qp->qp_num) अणु
		पूर्णांक need_repost = 1;

		अगर ((wc->wc_flags & IB_WC_GRH) &&
		    sgid->global.पूर्णांकerface_id != priv->local_gid.global.पूर्णांकerface_id)
			need_repost = 0;

		अगर (need_repost) अणु
			dev_kमुक्त_skb_any(skb);
			जाओ repost;
		पूर्ण
	पूर्ण

	skb_pull(skb, IB_GRH_BYTES);

	skb->protocol = ((काष्ठा ipoib_header *) skb->data)->proto;
	skb_add_pseuकरो_hdr(skb);

	++dev->stats.rx_packets;
	dev->stats.rx_bytes += skb->len;
	अगर (skb->pkt_type == PACKET_MULTICAST)
		dev->stats.multicast++;

	skb->dev = dev;
	अगर ((dev->features & NETIF_F_RXCSUM) &&
			likely(wc->wc_flags & IB_WC_IP_CSUM_OK))
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	napi_gro_receive(&priv->recv_napi, skb);

repost:
	अगर (unlikely(ipoib_ib_post_receive(dev, wr_id)))
		ipoib_warn(priv, "ipoib_ib_post_receive failed "
			   "for buf %d\n", wr_id);
पूर्ण

पूर्णांक ipoib_dma_map_tx(काष्ठा ib_device *ca, काष्ठा ipoib_tx_buf *tx_req)
अणु
	काष्ठा sk_buff *skb = tx_req->skb;
	u64 *mapping = tx_req->mapping;
	पूर्णांक i;
	पूर्णांक off;

	अगर (skb_headlen(skb)) अणु
		mapping[0] = ib_dma_map_single(ca, skb->data, skb_headlen(skb),
					       DMA_TO_DEVICE);
		अगर (unlikely(ib_dma_mapping_error(ca, mapping[0])))
			वापस -EIO;

		off = 1;
	पूर्ण अन्यथा
		off = 0;

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; ++i) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		mapping[i + off] = ib_dma_map_page(ca,
						 skb_frag_page(frag),
						 skb_frag_off(frag),
						 skb_frag_size(frag),
						 DMA_TO_DEVICE);
		अगर (unlikely(ib_dma_mapping_error(ca, mapping[i + off])))
			जाओ partial_error;
	पूर्ण
	वापस 0;

partial_error:
	क्रम (; i > 0; --i) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i - 1];

		ib_dma_unmap_page(ca, mapping[i - !off], skb_frag_size(frag), DMA_TO_DEVICE);
	पूर्ण

	अगर (off)
		ib_dma_unmap_single(ca, mapping[0], skb_headlen(skb), DMA_TO_DEVICE);

	वापस -EIO;
पूर्ण

व्योम ipoib_dma_unmap_tx(काष्ठा ipoib_dev_priv *priv,
			काष्ठा ipoib_tx_buf *tx_req)
अणु
	काष्ठा sk_buff *skb = tx_req->skb;
	u64 *mapping = tx_req->mapping;
	पूर्णांक i;
	पूर्णांक off;

	अगर (skb_headlen(skb)) अणु
		ib_dma_unmap_single(priv->ca, mapping[0], skb_headlen(skb),
				    DMA_TO_DEVICE);
		off = 1;
	पूर्ण अन्यथा
		off = 0;

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; ++i) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		ib_dma_unmap_page(priv->ca, mapping[i + off],
				  skb_frag_size(frag), DMA_TO_DEVICE);
	पूर्ण
पूर्ण

/*
 * As the result of a completion error the QP Can be transferred to SQE states.
 * The function checks अगर the (send)QP is in SQE state and
 * moves it back to RTS state, that in order to have it functional again.
 */
अटल व्योम ipoib_qp_state_validate_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_qp_state_validate *qp_work =
		container_of(work, काष्ठा ipoib_qp_state_validate, work);

	काष्ठा ipoib_dev_priv *priv = qp_work->priv;
	काष्ठा ib_qp_attr qp_attr;
	काष्ठा ib_qp_init_attr query_init_attr;
	पूर्णांक ret;

	ret = ib_query_qp(priv->qp, &qp_attr, IB_QP_STATE, &query_init_attr);
	अगर (ret) अणु
		ipoib_warn(priv, "%s: Failed to query QP ret: %d\n",
			   __func__, ret);
		जाओ मुक्त_res;
	पूर्ण
	pr_info("%s: QP: 0x%x is in state: %d\n",
		__func__, priv->qp->qp_num, qp_attr.qp_state);

	/* currently support only in SQE->RTS transition*/
	अगर (qp_attr.qp_state == IB_QPS_SQE) अणु
		qp_attr.qp_state = IB_QPS_RTS;

		ret = ib_modअगरy_qp(priv->qp, &qp_attr, IB_QP_STATE);
		अगर (ret) अणु
			pr_warn("failed(%d) modify QP:0x%x SQE->RTS\n",
				ret, priv->qp->qp_num);
			जाओ मुक्त_res;
		पूर्ण
		pr_info("%s: QP: 0x%x moved from IB_QPS_SQE to IB_QPS_RTS\n",
			__func__, priv->qp->qp_num);
	पूर्ण अन्यथा अणु
		pr_warn("QP (%d) will stay in state: %d\n",
			priv->qp->qp_num, qp_attr.qp_state);
	पूर्ण

मुक्त_res:
	kमुक्त(qp_work);
पूर्ण

अटल व्योम ipoib_ib_handle_tx_wc(काष्ठा net_device *dev, काष्ठा ib_wc *wc)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	अचिन्हित पूर्णांक wr_id = wc->wr_id;
	काष्ठा ipoib_tx_buf *tx_req;

	ipoib_dbg_data(priv, "send completion: id %d, status: %d\n",
		       wr_id, wc->status);

	अगर (unlikely(wr_id >= ipoib_sendq_size)) अणु
		ipoib_warn(priv, "send completion event with wrid %d (> %d)\n",
			   wr_id, ipoib_sendq_size);
		वापस;
	पूर्ण

	tx_req = &priv->tx_ring[wr_id];

	ipoib_dma_unmap_tx(priv, tx_req);

	++dev->stats.tx_packets;
	dev->stats.tx_bytes += tx_req->skb->len;

	dev_kमुक्त_skb_any(tx_req->skb);

	++priv->tx_tail;
	++priv->global_tx_tail;

	अगर (unlikely(netअगर_queue_stopped(dev) &&
		     ((priv->global_tx_head - priv->global_tx_tail) <=
		      ipoib_sendq_size >> 1) &&
		     test_bit(IPOIB_FLAG_ADMIN_UP, &priv->flags)))
		netअगर_wake_queue(dev);

	अगर (wc->status != IB_WC_SUCCESS &&
	    wc->status != IB_WC_WR_FLUSH_ERR) अणु
		काष्ठा ipoib_qp_state_validate *qp_work;
		ipoib_warn(priv,
			   "failed send event (status=%d, wrid=%d vend_err %#x)\n",
			   wc->status, wr_id, wc->venकरोr_err);
		qp_work = kzalloc(माप(*qp_work), GFP_ATOMIC);
		अगर (!qp_work)
			वापस;

		INIT_WORK(&qp_work->work, ipoib_qp_state_validate_work);
		qp_work->priv = priv;
		queue_work(priv->wq, &qp_work->work);
	पूर्ण
पूर्ण

अटल पूर्णांक poll_tx(काष्ठा ipoib_dev_priv *priv)
अणु
	पूर्णांक n, i;
	काष्ठा ib_wc *wc;

	n = ib_poll_cq(priv->send_cq, MAX_SEND_CQE, priv->send_wc);
	क्रम (i = 0; i < n; ++i) अणु
		wc = priv->send_wc + i;
		अगर (wc->wr_id & IPOIB_OP_CM)
			ipoib_cm_handle_tx_wc(priv->dev, priv->send_wc + i);
		अन्यथा
			ipoib_ib_handle_tx_wc(priv->dev, priv->send_wc + i);
	पूर्ण
	वापस n == MAX_SEND_CQE;
पूर्ण

पूर्णांक ipoib_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ipoib_dev_priv *priv =
		container_of(napi, काष्ठा ipoib_dev_priv, recv_napi);
	काष्ठा net_device *dev = priv->dev;
	पूर्णांक करोne;
	पूर्णांक t;
	पूर्णांक n, i;

	करोne  = 0;

poll_more:
	जबतक (करोne < budget) अणु
		पूर्णांक max = (budget - करोne);

		t = min(IPOIB_NUM_WC, max);
		n = ib_poll_cq(priv->recv_cq, t, priv->ibwc);

		क्रम (i = 0; i < n; i++) अणु
			काष्ठा ib_wc *wc = priv->ibwc + i;

			अगर (wc->wr_id & IPOIB_OP_RECV) अणु
				++करोne;
				अगर (wc->wr_id & IPOIB_OP_CM)
					ipoib_cm_handle_rx_wc(dev, wc);
				अन्यथा
					ipoib_ib_handle_rx_wc(dev, wc);
			पूर्ण अन्यथा अणु
				pr_warn("%s: Got unexpected wqe id\n", __func__);
			पूर्ण
		पूर्ण

		अगर (n != t)
			अवरोध;
	पूर्ण

	अगर (करोne < budget) अणु
		napi_complete(napi);
		अगर (unlikely(ib_req_notअगरy_cq(priv->recv_cq,
					      IB_CQ_NEXT_COMP |
					      IB_CQ_REPORT_MISSED_EVENTS)) &&
		    napi_reschedule(napi))
			जाओ poll_more;
	पूर्ण

	वापस करोne;
पूर्ण

पूर्णांक ipoib_tx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ipoib_dev_priv *priv = container_of(napi, काष्ठा ipoib_dev_priv,
						   send_napi);
	काष्ठा net_device *dev = priv->dev;
	पूर्णांक n, i;
	काष्ठा ib_wc *wc;

poll_more:
	n = ib_poll_cq(priv->send_cq, MAX_SEND_CQE, priv->send_wc);

	क्रम (i = 0; i < n; i++) अणु
		wc = priv->send_wc + i;
		अगर (wc->wr_id & IPOIB_OP_CM)
			ipoib_cm_handle_tx_wc(dev, wc);
		अन्यथा
			ipoib_ib_handle_tx_wc(dev, wc);
	पूर्ण

	अगर (n < budget) अणु
		napi_complete(napi);
		अगर (unlikely(ib_req_notअगरy_cq(priv->send_cq, IB_CQ_NEXT_COMP |
					      IB_CQ_REPORT_MISSED_EVENTS)) &&
		    napi_reschedule(napi))
			जाओ poll_more;
	पूर्ण
	वापस n < 0 ? 0 : n;
पूर्ण

व्योम ipoib_ib_rx_completion(काष्ठा ib_cq *cq, व्योम *ctx_ptr)
अणु
	काष्ठा ipoib_dev_priv *priv = ctx_ptr;

	napi_schedule(&priv->recv_napi);
पूर्ण

व्योम ipoib_ib_tx_completion(काष्ठा ib_cq *cq, व्योम *ctx_ptr)
अणु
	काष्ठा ipoib_dev_priv *priv = ctx_ptr;

	napi_schedule(&priv->send_napi);
पूर्ण

अटल अंतरभूत पूर्णांक post_send(काष्ठा ipoib_dev_priv *priv,
			    अचिन्हित पूर्णांक wr_id,
			    काष्ठा ib_ah *address, u32 dqpn,
			    काष्ठा ipoib_tx_buf *tx_req,
			    व्योम *head, पूर्णांक hlen)
अणु
	काष्ठा sk_buff *skb = tx_req->skb;

	ipoib_build_sge(priv, tx_req);

	priv->tx_wr.wr.wr_id	= wr_id;
	priv->tx_wr.remote_qpn	= dqpn;
	priv->tx_wr.ah		= address;

	अगर (head) अणु
		priv->tx_wr.mss		= skb_shinfo(skb)->gso_size;
		priv->tx_wr.header	= head;
		priv->tx_wr.hlen	= hlen;
		priv->tx_wr.wr.opcode	= IB_WR_LSO;
	पूर्ण अन्यथा
		priv->tx_wr.wr.opcode	= IB_WR_SEND;

	वापस ib_post_send(priv->qp, &priv->tx_wr.wr, शून्य);
पूर्ण

पूर्णांक ipoib_send(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
	       काष्ठा ib_ah *address, u32 dqpn)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_tx_buf *tx_req;
	पूर्णांक hlen, rc;
	व्योम *phead;
	अचिन्हित पूर्णांक usable_sge = priv->max_send_sge - !!skb_headlen(skb);

	अगर (skb_is_gso(skb)) अणु
		hlen = skb_transport_offset(skb) + tcp_hdrlen(skb);
		phead = skb->data;
		अगर (unlikely(!skb_pull(skb, hlen))) अणु
			ipoib_warn(priv, "linear data too small\n");
			++dev->stats.tx_dropped;
			++dev->stats.tx_errors;
			dev_kमुक्त_skb_any(skb);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (unlikely(skb->len > priv->mcast_mtu + IPOIB_ENCAP_LEN)) अणु
			ipoib_warn(priv, "packet len %d (> %d) too long to send, dropping\n",
				   skb->len, priv->mcast_mtu + IPOIB_ENCAP_LEN);
			++dev->stats.tx_dropped;
			++dev->stats.tx_errors;
			ipoib_cm_skb_too_दीर्घ(dev, skb, priv->mcast_mtu);
			वापस -1;
		पूर्ण
		phead = शून्य;
		hlen  = 0;
	पूर्ण
	अगर (skb_shinfo(skb)->nr_frags > usable_sge) अणु
		अगर (skb_linearize(skb) < 0) अणु
			ipoib_warn(priv, "skb could not be linearized\n");
			++dev->stats.tx_dropped;
			++dev->stats.tx_errors;
			dev_kमुक्त_skb_any(skb);
			वापस -1;
		पूर्ण
		/* Does skb_linearize वापस ok without reducing nr_frags? */
		अगर (skb_shinfo(skb)->nr_frags > usable_sge) अणु
			ipoib_warn(priv, "too many frags after skb linearize\n");
			++dev->stats.tx_dropped;
			++dev->stats.tx_errors;
			dev_kमुक्त_skb_any(skb);
			वापस -1;
		पूर्ण
	पूर्ण

	ipoib_dbg_data(priv,
		       "sending packet, length=%d address=%p dqpn=0x%06x\n",
		       skb->len, address, dqpn);

	/*
	 * We put the skb पूर्णांकo the tx_ring _beक्रमe_ we call post_send()
	 * because it's entirely possible that the completion handler will
	 * run beक्रमe we execute anything after the post_send().  That
	 * means we have to make sure everything is properly recorded and
	 * our state is consistent beक्रमe we call post_send().
	 */
	tx_req = &priv->tx_ring[priv->tx_head & (ipoib_sendq_size - 1)];
	tx_req->skb = skb;
	अगर (unlikely(ipoib_dma_map_tx(priv->ca, tx_req))) अणु
		++dev->stats.tx_errors;
		dev_kमुक्त_skb_any(skb);
		वापस -1;
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		priv->tx_wr.wr.send_flags |= IB_SEND_IP_CSUM;
	अन्यथा
		priv->tx_wr.wr.send_flags &= ~IB_SEND_IP_CSUM;
	/* increase the tx_head after send success, but use it क्रम queue state */
	अगर ((priv->global_tx_head - priv->global_tx_tail) ==
	    ipoib_sendq_size - 1) अणु
		ipoib_dbg(priv, "TX ring full, stopping kernel net queue\n");
		netअगर_stop_queue(dev);
	पूर्ण

	skb_orphan(skb);
	skb_dst_drop(skb);

	अगर (netअगर_queue_stopped(dev))
		अगर (ib_req_notअगरy_cq(priv->send_cq, IB_CQ_NEXT_COMP |
				     IB_CQ_REPORT_MISSED_EVENTS) < 0)
			ipoib_warn(priv, "request notify on send CQ failed\n");

	rc = post_send(priv, priv->tx_head & (ipoib_sendq_size - 1),
		       address, dqpn, tx_req, phead, hlen);
	अगर (unlikely(rc)) अणु
		ipoib_warn(priv, "post_send failed, error %d\n", rc);
		++dev->stats.tx_errors;
		ipoib_dma_unmap_tx(priv, tx_req);
		dev_kमुक्त_skb_any(skb);
		अगर (netअगर_queue_stopped(dev))
			netअगर_wake_queue(dev);
		rc = 0;
	पूर्ण अन्यथा अणु
		netअगर_trans_update(dev);

		rc = priv->tx_head;
		++priv->tx_head;
		++priv->global_tx_head;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम ipoib_reap_dead_ahs(काष्ठा ipoib_dev_priv *priv)
अणु
	काष्ठा ipoib_ah *ah, *tah;
	अचिन्हित दीर्घ flags;

	netअगर_tx_lock_bh(priv->dev);
	spin_lock_irqsave(&priv->lock, flags);

	list_क्रम_each_entry_safe(ah, tah, &priv->dead_ahs, list)
		अगर ((पूर्णांक) priv->tx_tail - (पूर्णांक) ah->last_send >= 0) अणु
			list_del(&ah->list);
			rdma_destroy_ah(ah->ah, 0);
			kमुक्त(ah);
		पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
	netअगर_tx_unlock_bh(priv->dev);
पूर्ण

व्योम ipoib_reap_ah(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_dev_priv *priv =
		container_of(work, काष्ठा ipoib_dev_priv, ah_reap_task.work);

	ipoib_reap_dead_ahs(priv);

	अगर (!test_bit(IPOIB_STOP_REAPER, &priv->flags))
		queue_delayed_work(priv->wq, &priv->ah_reap_task,
				   round_jअगरfies_relative(HZ));
पूर्ण

अटल व्योम ipoib_start_ah_reaper(काष्ठा ipoib_dev_priv *priv)
अणु
	clear_bit(IPOIB_STOP_REAPER, &priv->flags);
	queue_delayed_work(priv->wq, &priv->ah_reap_task,
			   round_jअगरfies_relative(HZ));
पूर्ण

अटल व्योम ipoib_stop_ah_reaper(काष्ठा ipoib_dev_priv *priv)
अणु
	set_bit(IPOIB_STOP_REAPER, &priv->flags);
	cancel_delayed_work(&priv->ah_reap_task);
	/*
	 * After ipoib_stop_ah_reaper() we always go through
	 * ipoib_reap_dead_ahs() which ensures the work is really stopped and
	 * करोes a final flush out of the dead_ah's list
	 */
पूर्ण

अटल पूर्णांक recvs_pending(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक pending = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ipoib_recvq_size; ++i)
		अगर (priv->rx_ring[i].skb)
			++pending;

	वापस pending;
पूर्ण

अटल व्योम check_qp_movement_and_prपूर्णांक(काष्ठा ipoib_dev_priv *priv,
					काष्ठा ib_qp *qp,
					क्रमागत ib_qp_state new_state)
अणु
	काष्ठा ib_qp_attr qp_attr;
	काष्ठा ib_qp_init_attr query_init_attr;
	पूर्णांक ret;

	ret = ib_query_qp(qp, &qp_attr, IB_QP_STATE, &query_init_attr);
	अगर (ret) अणु
		ipoib_warn(priv, "%s: Failed to query QP\n", __func__);
		वापस;
	पूर्ण
	/* prपूर्णांक according to the new-state and the previous state.*/
	अगर (new_state == IB_QPS_ERR && qp_attr.qp_state == IB_QPS_RESET)
		ipoib_dbg(priv, "Failed modify QP, IB_QPS_RESET to IB_QPS_ERR, acceptable\n");
	अन्यथा
		ipoib_warn(priv, "Failed to modify QP to state: %d from state: %d\n",
			   new_state, qp_attr.qp_state);
पूर्ण

अटल व्योम ipoib_napi_enable(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	napi_enable(&priv->recv_napi);
	napi_enable(&priv->send_napi);
पूर्ण

अटल व्योम ipoib_napi_disable(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	napi_disable(&priv->recv_napi);
	napi_disable(&priv->send_napi);
पूर्ण

पूर्णांक ipoib_ib_dev_stop_शेष(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ib_qp_attr qp_attr;
	अचिन्हित दीर्घ begin;
	काष्ठा ipoib_tx_buf *tx_req;
	पूर्णांक i;

	अगर (test_bit(IPOIB_FLAG_INITIALIZED, &priv->flags))
		ipoib_napi_disable(dev);

	ipoib_cm_dev_stop(dev);

	/*
	 * Move our QP to the error state and then reinitialize in
	 * when all work requests have completed or have been flushed.
	 */
	qp_attr.qp_state = IB_QPS_ERR;
	अगर (ib_modअगरy_qp(priv->qp, &qp_attr, IB_QP_STATE))
		check_qp_movement_and_prपूर्णांक(priv, priv->qp, IB_QPS_ERR);

	/* Wait क्रम all sends and receives to complete */
	begin = jअगरfies;

	जबतक (priv->tx_head != priv->tx_tail || recvs_pending(dev)) अणु
		अगर (समय_after(jअगरfies, begin + 5 * HZ)) अणु
			ipoib_warn(priv,
				   "timing out; %d sends %d receives not completed\n",
				   priv->tx_head - priv->tx_tail,
				   recvs_pending(dev));

			/*
			 * assume the HW is wedged and just मुक्त up
			 * all our pending work requests.
			 */
			जबतक ((पूर्णांक)priv->tx_tail - (पूर्णांक)priv->tx_head < 0) अणु
				tx_req = &priv->tx_ring[priv->tx_tail &
							(ipoib_sendq_size - 1)];
				ipoib_dma_unmap_tx(priv, tx_req);
				dev_kमुक्त_skb_any(tx_req->skb);
				++priv->tx_tail;
				++priv->global_tx_tail;
			पूर्ण

			क्रम (i = 0; i < ipoib_recvq_size; ++i) अणु
				काष्ठा ipoib_rx_buf *rx_req;

				rx_req = &priv->rx_ring[i];
				अगर (!rx_req->skb)
					जारी;
				ipoib_ud_dma_unmap_rx(priv,
						      priv->rx_ring[i].mapping);
				dev_kमुक्त_skb_any(rx_req->skb);
				rx_req->skb = शून्य;
			पूर्ण

			जाओ समयout;
		पूर्ण

		ipoib_drain_cq(dev);

		usleep_range(1000, 2000);
	पूर्ण

	ipoib_dbg(priv, "All sends and receives done.\n");

समयout:
	qp_attr.qp_state = IB_QPS_RESET;
	अगर (ib_modअगरy_qp(priv->qp, &qp_attr, IB_QP_STATE))
		ipoib_warn(priv, "Failed to modify QP to RESET state\n");

	ib_req_notअगरy_cq(priv->recv_cq, IB_CQ_NEXT_COMP);

	वापस 0;
पूर्ण

पूर्णांक ipoib_ib_dev_खोलो_शेष(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक ret;

	ret = ipoib_init_qp(dev);
	अगर (ret) अणु
		ipoib_warn(priv, "ipoib_init_qp returned %d\n", ret);
		वापस -1;
	पूर्ण

	ret = ipoib_ib_post_receives(dev);
	अगर (ret) अणु
		ipoib_warn(priv, "ipoib_ib_post_receives returned %d\n", ret);
		जाओ out;
	पूर्ण

	ret = ipoib_cm_dev_खोलो(dev);
	अगर (ret) अणु
		ipoib_warn(priv, "ipoib_cm_dev_open returned %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (!test_bit(IPOIB_FLAG_INITIALIZED, &priv->flags))
		ipoib_napi_enable(dev);

	वापस 0;
out:
	वापस -1;
पूर्ण

पूर्णांक ipoib_ib_dev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_pkey_dev_check_presence(dev);

	अगर (!test_bit(IPOIB_PKEY_ASSIGNED, &priv->flags)) अणु
		ipoib_warn(priv, "P_Key 0x%04x is %s\n", priv->pkey,
			   (!(priv->pkey & 0x7fff) ? "Invalid" : "not found"));
		वापस -1;
	पूर्ण

	ipoib_start_ah_reaper(priv);
	अगर (priv->rn_ops->nकरो_खोलो(dev)) अणु
		pr_warn("%s: Failed to open dev\n", dev->name);
		जाओ dev_stop;
	पूर्ण

	set_bit(IPOIB_FLAG_INITIALIZED, &priv->flags);

	वापस 0;

dev_stop:
	ipoib_stop_ah_reaper(priv);
	वापस -1;
पूर्ण

व्योम ipoib_ib_dev_stop(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	priv->rn_ops->nकरो_stop(dev);

	clear_bit(IPOIB_FLAG_INITIALIZED, &priv->flags);
	ipoib_stop_ah_reaper(priv);
पूर्ण

व्योम ipoib_pkey_dev_check_presence(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा rdma_netdev *rn = netdev_priv(dev);

	अगर (!(priv->pkey & 0x7fff) ||
	    ib_find_pkey(priv->ca, priv->port, priv->pkey,
			 &priv->pkey_index)) अणु
		clear_bit(IPOIB_PKEY_ASSIGNED, &priv->flags);
	पूर्ण अन्यथा अणु
		अगर (rn->set_id)
			rn->set_id(dev, priv->pkey_index);
		set_bit(IPOIB_PKEY_ASSIGNED, &priv->flags);
	पूर्ण
पूर्ण

व्योम ipoib_ib_dev_up(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_pkey_dev_check_presence(dev);

	अगर (!test_bit(IPOIB_PKEY_ASSIGNED, &priv->flags)) अणु
		ipoib_dbg(priv, "PKEY is not assigned.\n");
		वापस;
	पूर्ण

	set_bit(IPOIB_FLAG_OPER_UP, &priv->flags);

	ipoib_mcast_start_thपढ़ो(dev);
पूर्ण

व्योम ipoib_ib_dev_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_dbg(priv, "downing ib_dev\n");

	clear_bit(IPOIB_FLAG_OPER_UP, &priv->flags);
	netअगर_carrier_off(dev);

	ipoib_mcast_stop_thपढ़ो(dev);
	ipoib_mcast_dev_flush(dev);

	ipoib_flush_paths(dev);
पूर्ण

व्योम ipoib_drain_cq(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक i, n;

	/*
	 * We call completion handling routines that expect to be
	 * called from the BH-disabled NAPI poll context, so disable
	 * BHs here too.
	 */
	local_bh_disable();

	करो अणु
		n = ib_poll_cq(priv->recv_cq, IPOIB_NUM_WC, priv->ibwc);
		क्रम (i = 0; i < n; ++i) अणु
			/*
			 * Convert any successful completions to flush
			 * errors to aव्योम passing packets up the
			 * stack after bringing the device करोwn.
			 */
			अगर (priv->ibwc[i].status == IB_WC_SUCCESS)
				priv->ibwc[i].status = IB_WC_WR_FLUSH_ERR;

			अगर (priv->ibwc[i].wr_id & IPOIB_OP_RECV) अणु
				अगर (priv->ibwc[i].wr_id & IPOIB_OP_CM)
					ipoib_cm_handle_rx_wc(dev, priv->ibwc + i);
				अन्यथा
					ipoib_ib_handle_rx_wc(dev, priv->ibwc + i);
			पूर्ण अन्यथा अणु
				pr_warn("%s: Got unexpected wqe id\n", __func__);
			पूर्ण
		पूर्ण
	पूर्ण जबतक (n == IPOIB_NUM_WC);

	जबतक (poll_tx(priv))
		; /* nothing */

	local_bh_enable();
पूर्ण

/*
 * Takes whatever value which is in pkey index 0 and updates priv->pkey
 * वापसs 0 अगर the pkey value was changed.
 */
अटल अंतरभूत पूर्णांक update_parent_pkey(काष्ठा ipoib_dev_priv *priv)
अणु
	पूर्णांक result;
	u16 prev_pkey;

	prev_pkey = priv->pkey;
	result = ib_query_pkey(priv->ca, priv->port, 0, &priv->pkey);
	अगर (result) अणु
		ipoib_warn(priv, "ib_query_pkey port %d failed (ret = %d)\n",
			   priv->port, result);
		वापस result;
	पूर्ण

	priv->pkey |= 0x8000;

	अगर (prev_pkey != priv->pkey) अणु
		ipoib_dbg(priv, "pkey changed from 0x%x to 0x%x\n",
			  prev_pkey, priv->pkey);
		/*
		 * Update the pkey in the broadcast address, जबतक making sure to set
		 * the full membership bit, so that we join the right broadcast group.
		 */
		priv->dev->broadcast[8] = priv->pkey >> 8;
		priv->dev->broadcast[9] = priv->pkey & 0xff;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
/*
 * वापसs 0 अगर pkey value was found in a dअगरferent slot.
 */
अटल अंतरभूत पूर्णांक update_child_pkey(काष्ठा ipoib_dev_priv *priv)
अणु
	u16 old_index = priv->pkey_index;

	priv->pkey_index = 0;
	ipoib_pkey_dev_check_presence(priv->dev);

	अगर (test_bit(IPOIB_PKEY_ASSIGNED, &priv->flags) &&
	    (old_index == priv->pkey_index))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * वापसs true अगर the device address of the ipoib पूर्णांकerface has changed and the
 * new address is a valid one (i.e in the gid table), वापस false otherwise.
 */
अटल bool ipoib_dev_addr_changed_valid(काष्ठा ipoib_dev_priv *priv)
अणु
	जोड़ ib_gid search_gid;
	जोड़ ib_gid gid0;
	जोड़ ib_gid *netdev_gid;
	पूर्णांक err;
	u16 index;
	u32 port;
	bool ret = false;

	netdev_gid = (जोड़ ib_gid *)(priv->dev->dev_addr + 4);
	अगर (rdma_query_gid(priv->ca, priv->port, 0, &gid0))
		वापस false;

	netअगर_addr_lock_bh(priv->dev);

	/* The subnet prefix may have changed, update it now so we won't have
	 * to करो it later
	 */
	priv->local_gid.global.subnet_prefix = gid0.global.subnet_prefix;
	netdev_gid->global.subnet_prefix = gid0.global.subnet_prefix;
	search_gid.global.subnet_prefix = gid0.global.subnet_prefix;

	search_gid.global.पूर्णांकerface_id = priv->local_gid.global.पूर्णांकerface_id;

	netअगर_addr_unlock_bh(priv->dev);

	err = ib_find_gid(priv->ca, &search_gid, &port, &index);

	netअगर_addr_lock_bh(priv->dev);

	अगर (search_gid.global.पूर्णांकerface_id !=
	    priv->local_gid.global.पूर्णांकerface_id)
		/* There was a change जबतक we were looking up the gid, bail
		 * here and let the next work sort this out
		 */
		जाओ out;

	/* The next section of code needs some background:
	 * Per IB spec the port GUID can't change अगर the HCA is घातered on.
	 * port GUID is the basis क्रम GID at index 0 which is the basis क्रम
	 * the शेष device address of a ipoib पूर्णांकerface.
	 *
	 * so it seems the flow should be:
	 * अगर user_changed_dev_addr && gid in gid tbl
	 *	set bit dev_addr_set
	 *	वापस true
	 * अन्यथा
	 *	वापस false
	 *
	 * The issue is that there are devices that करोn't follow the spec,
	 * they change the port GUID when the HCA is घातered, so in order
	 * not to अवरोध userspace applications, We need to check अगर the
	 * user wanted to control the device address and we assume that
	 * अगर he sets the device address back to be based on GID index 0,
	 * he no दीर्घer wishs to control it.
	 *
	 * If the user करोesn't control the the device address,
	 * IPOIB_FLAG_DEV_ADDR_SET is set and ib_find_gid failed it means
	 * the port GUID has changed and GID at index 0 has changed
	 * so we need to change priv->local_gid and priv->dev->dev_addr
	 * to reflect the new GID.
	 */
	अगर (!test_bit(IPOIB_FLAG_DEV_ADDR_SET, &priv->flags)) अणु
		अगर (!err && port == priv->port) अणु
			set_bit(IPOIB_FLAG_DEV_ADDR_SET, &priv->flags);
			अगर (index == 0)
				clear_bit(IPOIB_FLAG_DEV_ADDR_CTRL,
					  &priv->flags);
			अन्यथा
				set_bit(IPOIB_FLAG_DEV_ADDR_CTRL, &priv->flags);
			ret = true;
		पूर्ण अन्यथा अणु
			ret = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!err && port == priv->port) अणु
			ret = true;
		पूर्ण अन्यथा अणु
			अगर (!test_bit(IPOIB_FLAG_DEV_ADDR_CTRL, &priv->flags)) अणु
				स_नकल(&priv->local_gid, &gid0,
				       माप(priv->local_gid));
				स_नकल(priv->dev->dev_addr + 4, &gid0,
				       माप(priv->local_gid));
				ret = true;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	netअगर_addr_unlock_bh(priv->dev);

	वापस ret;
पूर्ण

अटल व्योम __ipoib_ib_dev_flush(काष्ठा ipoib_dev_priv *priv,
				क्रमागत ipoib_flush_level level,
				पूर्णांक nesting)
अणु
	काष्ठा ipoib_dev_priv *cpriv;
	काष्ठा net_device *dev = priv->dev;
	पूर्णांक result;

	करोwn_पढ़ो_nested(&priv->vlan_rwsem, nesting);

	/*
	 * Flush any child पूर्णांकerfaces too -- they might be up even अगर
	 * the parent is करोwn.
	 */
	list_क्रम_each_entry(cpriv, &priv->child_पूर्णांकfs, list)
		__ipoib_ib_dev_flush(cpriv, level, nesting + 1);

	up_पढ़ो(&priv->vlan_rwsem);

	अगर (!test_bit(IPOIB_FLAG_INITIALIZED, &priv->flags) &&
	    level != IPOIB_FLUSH_HEAVY) अणु
		/* Make sure the dev_addr is set even अगर not flushing */
		अगर (level == IPOIB_FLUSH_LIGHT)
			ipoib_dev_addr_changed_valid(priv);
		ipoib_dbg(priv, "Not flushing - IPOIB_FLAG_INITIALIZED not set.\n");
		वापस;
	पूर्ण

	अगर (!test_bit(IPOIB_FLAG_ADMIN_UP, &priv->flags)) अणु
		/* पूर्णांकerface is करोwn. update pkey and leave. */
		अगर (level == IPOIB_FLUSH_HEAVY) अणु
			अगर (!test_bit(IPOIB_FLAG_SUBINTERFACE, &priv->flags))
				update_parent_pkey(priv);
			अन्यथा
				update_child_pkey(priv);
		पूर्ण अन्यथा अगर (level == IPOIB_FLUSH_LIGHT)
			ipoib_dev_addr_changed_valid(priv);
		ipoib_dbg(priv, "Not flushing - IPOIB_FLAG_ADMIN_UP not set.\n");
		वापस;
	पूर्ण

	अगर (level == IPOIB_FLUSH_HEAVY) अणु
		/* child devices chase their origin pkey value, जबतक non-child
		 * (parent) devices should always takes what present in pkey index 0
		 */
		अगर (test_bit(IPOIB_FLAG_SUBINTERFACE, &priv->flags)) अणु
			result = update_child_pkey(priv);
			अगर (result) अणु
				/* restart QP only अगर P_Key index is changed */
				ipoib_dbg(priv, "Not flushing - P_Key index not changed.\n");
				वापस;
			पूर्ण

		पूर्ण अन्यथा अणु
			result = update_parent_pkey(priv);
			/* restart QP only अगर P_Key value changed */
			अगर (result) अणु
				ipoib_dbg(priv, "Not flushing - P_Key value not changed.\n");
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (level == IPOIB_FLUSH_LIGHT) अणु
		पूर्णांक oper_up;
		ipoib_mark_paths_invalid(dev);
		/* Set IPoIB operation as करोwn to prevent races between:
		 * the flush flow which leaves MCG and on the fly joins
		 * which can happen during that समय. mcast restart task
		 * should deal with join requests we missed.
		 */
		oper_up = test_and_clear_bit(IPOIB_FLAG_OPER_UP, &priv->flags);
		ipoib_mcast_dev_flush(dev);
		अगर (oper_up)
			set_bit(IPOIB_FLAG_OPER_UP, &priv->flags);
		ipoib_reap_dead_ahs(priv);
	पूर्ण

	अगर (level >= IPOIB_FLUSH_NORMAL)
		ipoib_ib_dev_करोwn(dev);

	अगर (level == IPOIB_FLUSH_HEAVY) अणु
		अगर (test_bit(IPOIB_FLAG_INITIALIZED, &priv->flags))
			ipoib_ib_dev_stop(dev);

		अगर (ipoib_ib_dev_खोलो(dev))
			वापस;

		अगर (netअगर_queue_stopped(dev))
			netअगर_start_queue(dev);
	पूर्ण

	/*
	 * The device could have been brought करोwn between the start and when
	 * we get here, करोn't bring it back up if it's not configured up
	 */
	अगर (test_bit(IPOIB_FLAG_ADMIN_UP, &priv->flags)) अणु
		अगर (level >= IPOIB_FLUSH_NORMAL)
			ipoib_ib_dev_up(dev);
		अगर (ipoib_dev_addr_changed_valid(priv))
			ipoib_mcast_restart_task(&priv->restart_task);
	पूर्ण
पूर्ण

व्योम ipoib_ib_dev_flush_light(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_dev_priv *priv =
		container_of(work, काष्ठा ipoib_dev_priv, flush_light);

	__ipoib_ib_dev_flush(priv, IPOIB_FLUSH_LIGHT, 0);
पूर्ण

व्योम ipoib_ib_dev_flush_normal(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_dev_priv *priv =
		container_of(work, काष्ठा ipoib_dev_priv, flush_normal);

	__ipoib_ib_dev_flush(priv, IPOIB_FLUSH_NORMAL, 0);
पूर्ण

व्योम ipoib_ib_dev_flush_heavy(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_dev_priv *priv =
		container_of(work, काष्ठा ipoib_dev_priv, flush_heavy);

	rtnl_lock();
	__ipoib_ib_dev_flush(priv, IPOIB_FLUSH_HEAVY, 0);
	rtnl_unlock();
पूर्ण

व्योम ipoib_ib_dev_cleanup(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_dbg(priv, "cleaning up ib_dev\n");
	/*
	 * We must make sure there are no more (path) completions
	 * that may wish to touch priv fields that are no दीर्घer valid
	 */
	ipoib_flush_paths(dev);

	ipoib_mcast_stop_thपढ़ो(dev);
	ipoib_mcast_dev_flush(dev);

	/*
	 * All of our ah references aren't मुक्त until after
	 * ipoib_mcast_dev_flush(), ipoib_flush_paths, and
	 * the neighbor garbage collection is stopped and reaped.
	 * That should all be करोne now, so make a final ah flush.
	 */
	ipoib_reap_dead_ahs(priv);

	clear_bit(IPOIB_PKEY_ASSIGNED, &priv->flags);

	priv->rn_ops->nकरो_uninit(dev);

	अगर (priv->pd) अणु
		ib_dealloc_pd(priv->pd);
		priv->pd = शून्य;
	पूर्ण
पूर्ण

