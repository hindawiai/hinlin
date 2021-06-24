<शैली गुरु>
/* QLogic qedr NIC Driver
 * Copyright (c) 2015-2016  QLogic Corporation
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
#समावेश <linux/dma-mapping.h>
#समावेश <linux/crc32.h>
#समावेश <linux/iommu.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/udp.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/iw_cm.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_cache.h>

#समावेश <linux/qed/qed_अगर.h>
#समावेश <linux/qed/qed_rdma_अगर.h>
#समावेश "qedr.h"
#समावेश "verbs.h"
#समावेश <rdma/qedr-abi.h>
#समावेश "qedr_roce_cm.h"

व्योम qedr_inc_sw_gsi_cons(काष्ठा qedr_qp_hwq_info *info)
अणु
	info->gsi_cons = (info->gsi_cons + 1) % info->max_wr;
पूर्ण

व्योम qedr_store_gsi_qp_cq(काष्ठा qedr_dev *dev, काष्ठा qedr_qp *qp,
			  काष्ठा ib_qp_init_attr *attrs)
अणु
	dev->gsi_qp_created = 1;
	dev->gsi_sqcq = get_qedr_cq(attrs->send_cq);
	dev->gsi_rqcq = get_qedr_cq(attrs->recv_cq);
	dev->gsi_qp = qp;
पूर्ण

अटल व्योम qedr_ll2_complete_tx_packet(व्योम *cxt, u8 connection_handle,
					व्योम *cookie,
					dma_addr_t first_frag_addr,
					bool b_last_fragment,
					bool b_last_packet)
अणु
	काष्ठा qedr_dev *dev = (काष्ठा qedr_dev *)cxt;
	काष्ठा qed_roce_ll2_packet *pkt = cookie;
	काष्ठा qedr_cq *cq = dev->gsi_sqcq;
	काष्ठा qedr_qp *qp = dev->gsi_qp;
	अचिन्हित दीर्घ flags;

	DP_DEBUG(dev, QEDR_MSG_GSI,
		 "LL2 TX CB: gsi_sqcq=%p, gsi_rqcq=%p, gsi_cons=%d, ibcq_comp=%s\n",
		 dev->gsi_sqcq, dev->gsi_rqcq, qp->sq.gsi_cons,
		 cq->ibcq.comp_handler ? "Yes" : "No");

	dma_मुक्त_coherent(&dev->pdev->dev, pkt->header.len, pkt->header.vaddr,
			  pkt->header.baddr);
	kमुक्त(pkt);

	spin_lock_irqsave(&qp->q_lock, flags);
	qedr_inc_sw_gsi_cons(&qp->sq);
	spin_unlock_irqrestore(&qp->q_lock, flags);

	अगर (cq->ibcq.comp_handler)
		(*cq->ibcq.comp_handler) (&cq->ibcq, cq->ibcq.cq_context);
पूर्ण

अटल व्योम qedr_ll2_complete_rx_packet(व्योम *cxt,
					काष्ठा qed_ll2_comp_rx_data *data)
अणु
	काष्ठा qedr_dev *dev = (काष्ठा qedr_dev *)cxt;
	काष्ठा qedr_cq *cq = dev->gsi_rqcq;
	काष्ठा qedr_qp *qp = dev->gsi_qp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->q_lock, flags);

	qp->rqe_wr_id[qp->rq.gsi_cons].rc = data->u.data_length_error ?
		-EINVAL : 0;
	qp->rqe_wr_id[qp->rq.gsi_cons].vlan = data->vlan;
	/* note: length stands क्रम data length i.e. GRH is excluded */
	qp->rqe_wr_id[qp->rq.gsi_cons].sg_list[0].length =
		data->length.data_length;
	*((u32 *)&qp->rqe_wr_id[qp->rq.gsi_cons].smac[0]) =
		ntohl(data->opaque_data_0);
	*((u16 *)&qp->rqe_wr_id[qp->rq.gsi_cons].smac[4]) =
		ntohs((u16)data->opaque_data_1);

	qedr_inc_sw_gsi_cons(&qp->rq);

	spin_unlock_irqrestore(&qp->q_lock, flags);

	अगर (cq->ibcq.comp_handler)
		(*cq->ibcq.comp_handler) (&cq->ibcq, cq->ibcq.cq_context);
पूर्ण

अटल व्योम qedr_ll2_release_rx_packet(व्योम *cxt, u8 connection_handle,
				       व्योम *cookie, dma_addr_t rx_buf_addr,
				       bool b_last_packet)
अणु
	/* Do nothing... */
पूर्ण

अटल व्योम qedr_destroy_gsi_cq(काष्ठा qedr_dev *dev,
				काष्ठा ib_qp_init_attr *attrs)
अणु
	काष्ठा qed_rdma_destroy_cq_in_params iparams;
	काष्ठा qed_rdma_destroy_cq_out_params oparams;
	काष्ठा qedr_cq *cq;

	cq = get_qedr_cq(attrs->send_cq);
	iparams.icid = cq->icid;
	dev->ops->rdma_destroy_cq(dev->rdma_ctx, &iparams, &oparams);
	dev->ops->common->chain_मुक्त(dev->cdev, &cq->pbl);

	cq = get_qedr_cq(attrs->recv_cq);
	/* अगर a dedicated recv_cq was used, delete it too */
	अगर (iparams.icid != cq->icid) अणु
		iparams.icid = cq->icid;
		dev->ops->rdma_destroy_cq(dev->rdma_ctx, &iparams, &oparams);
		dev->ops->common->chain_मुक्त(dev->cdev, &cq->pbl);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक qedr_check_gsi_qp_attrs(काष्ठा qedr_dev *dev,
					  काष्ठा ib_qp_init_attr *attrs)
अणु
	अगर (attrs->cap.max_recv_sge > QEDR_GSI_MAX_RECV_SGE) अणु
		DP_ERR(dev,
		       " create gsi qp: failed. max_recv_sge is larger the max %d>%d\n",
		       attrs->cap.max_recv_sge, QEDR_GSI_MAX_RECV_SGE);
		वापस -EINVAL;
	पूर्ण

	अगर (attrs->cap.max_recv_wr > QEDR_GSI_MAX_RECV_WR) अणु
		DP_ERR(dev,
		       " create gsi qp: failed. max_recv_wr is too large %d>%d\n",
		       attrs->cap.max_recv_wr, QEDR_GSI_MAX_RECV_WR);
		वापस -EINVAL;
	पूर्ण

	अगर (attrs->cap.max_send_wr > QEDR_GSI_MAX_SEND_WR) अणु
		DP_ERR(dev,
		       " create gsi qp: failed. max_send_wr is too large %d>%d\n",
		       attrs->cap.max_send_wr, QEDR_GSI_MAX_SEND_WR);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qedr_ll2_post_tx(काष्ठा qedr_dev *dev,
			    काष्ठा qed_roce_ll2_packet *pkt)
अणु
	क्रमागत qed_ll2_roce_flavor_type roce_flavor;
	काष्ठा qed_ll2_tx_pkt_info ll2_tx_pkt;
	पूर्णांक rc;
	पूर्णांक i;

	स_रखो(&ll2_tx_pkt, 0, माप(ll2_tx_pkt));

	roce_flavor = (pkt->roce_mode == ROCE_V1) ?
	    QED_LL2_ROCE : QED_LL2_RROCE;

	अगर (pkt->roce_mode == ROCE_V2_IPV4)
		ll2_tx_pkt.enable_ip_cksum = 1;

	ll2_tx_pkt.num_of_bds = 1 /* hdr */  + pkt->n_seg;
	ll2_tx_pkt.vlan = 0;
	ll2_tx_pkt.tx_dest = pkt->tx_dest;
	ll2_tx_pkt.qed_roce_flavor = roce_flavor;
	ll2_tx_pkt.first_frag = pkt->header.baddr;
	ll2_tx_pkt.first_frag_len = pkt->header.len;
	ll2_tx_pkt.cookie = pkt;

	/* tx header */
	rc = dev->ops->ll2_prepare_tx_packet(dev->rdma_ctx,
					     dev->gsi_ll2_handle,
					     &ll2_tx_pkt, 1);
	अगर (rc) अणु
		/* TX failed जबतक posting header - release resources */
		dma_मुक्त_coherent(&dev->pdev->dev, pkt->header.len,
				  pkt->header.vaddr, pkt->header.baddr);
		kमुक्त(pkt);

		DP_ERR(dev, "roce ll2 tx: header failed (rc=%d)\n", rc);
		वापस rc;
	पूर्ण

	/* tx payload */
	क्रम (i = 0; i < pkt->n_seg; i++) अणु
		rc = dev->ops->ll2_set_fragment_of_tx_packet(
			dev->rdma_ctx,
			dev->gsi_ll2_handle,
			pkt->payload[i].baddr,
			pkt->payload[i].len);

		अगर (rc) अणु
			/* अगर failed not much to करो here, partial packet has
			 * been posted we can't मुक्त memory, will need to रुको
			 * क्रम completion
			 */
			DP_ERR(dev, "ll2 tx: payload failed (rc=%d)\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qedr_ll2_stop(काष्ठा qedr_dev *dev)
अणु
	पूर्णांक rc;

	अगर (dev->gsi_ll2_handle == QED_LL2_UNUSED_HANDLE)
		वापस 0;

	/* हटाओ LL2 MAC address filter */
	rc = dev->ops->ll2_set_mac_filter(dev->cdev,
					  dev->gsi_ll2_mac_address, शून्य);

	rc = dev->ops->ll2_terminate_connection(dev->rdma_ctx,
						dev->gsi_ll2_handle);
	अगर (rc)
		DP_ERR(dev, "Failed to terminate LL2 connection (rc=%d)\n", rc);

	dev->ops->ll2_release_connection(dev->rdma_ctx, dev->gsi_ll2_handle);

	dev->gsi_ll2_handle = QED_LL2_UNUSED_HANDLE;

	वापस rc;
पूर्ण

अटल पूर्णांक qedr_ll2_start(काष्ठा qedr_dev *dev,
			  काष्ठा ib_qp_init_attr *attrs, काष्ठा qedr_qp *qp)
अणु
	काष्ठा qed_ll2_acquire_data data;
	काष्ठा qed_ll2_cbs cbs;
	पूर्णांक rc;

	/* configure and start LL2 */
	cbs.rx_comp_cb = qedr_ll2_complete_rx_packet;
	cbs.tx_comp_cb = qedr_ll2_complete_tx_packet;
	cbs.rx_release_cb = qedr_ll2_release_rx_packet;
	cbs.tx_release_cb = qedr_ll2_complete_tx_packet;
	cbs.cookie = dev;

	स_रखो(&data, 0, माप(data));
	data.input.conn_type = QED_LL2_TYPE_ROCE;
	data.input.mtu = dev->ndev->mtu;
	data.input.rx_num_desc = attrs->cap.max_recv_wr;
	data.input.rx_drop_ttl0_flg = true;
	data.input.rx_vlan_removal_en = false;
	data.input.tx_num_desc = attrs->cap.max_send_wr;
	data.input.tx_tc = 0;
	data.input.tx_dest = QED_LL2_TX_DEST_NW;
	data.input.ai_err_packet_too_big = QED_LL2_DROP_PACKET;
	data.input.ai_err_no_buf = QED_LL2_DROP_PACKET;
	data.input.gsi_enable = 1;
	data.p_connection_handle = &dev->gsi_ll2_handle;
	data.cbs = &cbs;

	rc = dev->ops->ll2_acquire_connection(dev->rdma_ctx, &data);
	अगर (rc) अणु
		DP_ERR(dev,
		       "ll2 start: failed to acquire LL2 connection (rc=%d)\n",
		       rc);
		वापस rc;
	पूर्ण

	rc = dev->ops->ll2_establish_connection(dev->rdma_ctx,
						dev->gsi_ll2_handle);
	अगर (rc) अणु
		DP_ERR(dev,
		       "ll2 start: failed to establish LL2 connection (rc=%d)\n",
		       rc);
		जाओ err1;
	पूर्ण

	rc = dev->ops->ll2_set_mac_filter(dev->cdev, शून्य, dev->ndev->dev_addr);
	अगर (rc)
		जाओ err2;

	वापस 0;

err2:
	dev->ops->ll2_terminate_connection(dev->rdma_ctx, dev->gsi_ll2_handle);
err1:
	dev->ops->ll2_release_connection(dev->rdma_ctx, dev->gsi_ll2_handle);

	वापस rc;
पूर्ण

काष्ठा ib_qp *qedr_create_gsi_qp(काष्ठा qedr_dev *dev,
				 काष्ठा ib_qp_init_attr *attrs,
				 काष्ठा qedr_qp *qp)
अणु
	पूर्णांक rc;

	rc = qedr_check_gsi_qp_attrs(dev, attrs);
	अगर (rc)
		वापस ERR_PTR(rc);

	rc = qedr_ll2_start(dev, attrs, qp);
	अगर (rc) अणु
		DP_ERR(dev, "create gsi qp: failed on ll2 start. rc=%d\n", rc);
		वापस ERR_PTR(rc);
	पूर्ण

	/* create QP */
	qp->ibqp.qp_num = 1;
	qp->rq.max_wr = attrs->cap.max_recv_wr;
	qp->sq.max_wr = attrs->cap.max_send_wr;

	qp->rqe_wr_id = kसुस्मृति(qp->rq.max_wr, माप(*qp->rqe_wr_id),
				GFP_KERNEL);
	अगर (!qp->rqe_wr_id)
		जाओ err;
	qp->wqe_wr_id = kसुस्मृति(qp->sq.max_wr, माप(*qp->wqe_wr_id),
				GFP_KERNEL);
	अगर (!qp->wqe_wr_id)
		जाओ err;

	qedr_store_gsi_qp_cq(dev, qp, attrs);
	ether_addr_copy(dev->gsi_ll2_mac_address, dev->ndev->dev_addr);

	/* the GSI CQ is handled by the driver so हटाओ it from the FW */
	qedr_destroy_gsi_cq(dev, attrs);
	dev->gsi_rqcq->cq_type = QEDR_CQ_TYPE_GSI;
	dev->gsi_rqcq->cq_type = QEDR_CQ_TYPE_GSI;

	DP_DEBUG(dev, QEDR_MSG_GSI, "created GSI QP %p\n", qp);

	वापस &qp->ibqp;

err:
	kमुक्त(qp->rqe_wr_id);

	rc = qedr_ll2_stop(dev);
	अगर (rc)
		DP_ERR(dev, "create gsi qp: failed destroy on create\n");

	वापस ERR_PTR(-ENOMEM);
पूर्ण

पूर्णांक qedr_destroy_gsi_qp(काष्ठा qedr_dev *dev)
अणु
	वापस qedr_ll2_stop(dev);
पूर्ण

#घोषणा QEDR_MAX_UD_HEADER_SIZE	(100)
#घोषणा QEDR_GSI_QPN		(1)
अटल अंतरभूत पूर्णांक qedr_gsi_build_header(काष्ठा qedr_dev *dev,
					काष्ठा qedr_qp *qp,
					स्थिर काष्ठा ib_send_wr *swr,
					काष्ठा ib_ud_header *udh,
					पूर्णांक *roce_mode)
अणु
	bool has_vlan = false, has_grh_ipv6 = true;
	काष्ठा rdma_ah_attr *ah_attr = &get_qedr_ah(ud_wr(swr)->ah)->attr;
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(ah_attr);
	स्थिर काष्ठा ib_gid_attr *sgid_attr = grh->sgid_attr;
	पूर्णांक send_size = 0;
	u16 vlan_id = 0;
	u16 ether_type;
	पूर्णांक rc;
	पूर्णांक ip_ver = 0;

	bool has_udp = false;
	पूर्णांक i;

	rc = rdma_पढ़ो_gid_l2_fields(sgid_attr, &vlan_id, शून्य);
	अगर (rc)
		वापस rc;

	अगर (vlan_id < VLAN_CFI_MASK)
		has_vlan = true;

	send_size = 0;
	क्रम (i = 0; i < swr->num_sge; ++i)
		send_size += swr->sg_list[i].length;

	has_udp = (sgid_attr->gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP);
	अगर (!has_udp) अणु
		/* RoCE v1 */
		ether_type = ETH_P_IBOE;
		*roce_mode = ROCE_V1;
	पूर्ण अन्यथा अगर (ipv6_addr_v4mapped((काष्ठा in6_addr *)&sgid_attr->gid)) अणु
		/* RoCE v2 IPv4 */
		ip_ver = 4;
		ether_type = ETH_P_IP;
		has_grh_ipv6 = false;
		*roce_mode = ROCE_V2_IPV4;
	पूर्ण अन्यथा अणु
		/* RoCE v2 IPv6 */
		ip_ver = 6;
		ether_type = ETH_P_IPV6;
		*roce_mode = ROCE_V2_IPV6;
	पूर्ण

	rc = ib_ud_header_init(send_size, false, true, has_vlan,
			       has_grh_ipv6, ip_ver, has_udp, 0, udh);
	अगर (rc) अणु
		DP_ERR(dev, "gsi post send: failed to init header\n");
		वापस rc;
	पूर्ण

	/* ENET + VLAN headers */
	ether_addr_copy(udh->eth.dmac_h, ah_attr->roce.dmac);
	ether_addr_copy(udh->eth.smac_h, dev->ndev->dev_addr);
	अगर (has_vlan) अणु
		udh->eth.type = htons(ETH_P_8021Q);
		udh->vlan.tag = htons(vlan_id);
		udh->vlan.type = htons(ether_type);
	पूर्ण अन्यथा अणु
		udh->eth.type = htons(ether_type);
	पूर्ण

	/* BTH */
	udh->bth.solicited_event = !!(swr->send_flags & IB_SEND_SOLICITED);
	udh->bth.pkey = QEDR_ROCE_PKEY_DEFAULT;
	udh->bth.destination_qpn = htonl(ud_wr(swr)->remote_qpn);
	udh->bth.psn = htonl((qp->sq_psn++) & ((1 << 24) - 1));
	udh->bth.opcode = IB_OPCODE_UD_SEND_ONLY;

	/* DETH */
	udh->deth.qkey = htonl(0x80010000);
	udh->deth.source_qpn = htonl(QEDR_GSI_QPN);

	अगर (has_grh_ipv6) अणु
		/* GRH / IPv6 header */
		udh->grh.traffic_class = grh->traffic_class;
		udh->grh.flow_label = grh->flow_label;
		udh->grh.hop_limit = grh->hop_limit;
		udh->grh.destination_gid = grh->dgid;
		स_नकल(&udh->grh.source_gid.raw, sgid_attr->gid.raw,
		       माप(udh->grh.source_gid.raw));
	पूर्ण अन्यथा अणु
		/* IPv4 header */
		u32 ipv4_addr;

		udh->ip4.protocol = IPPROTO_UDP;
		udh->ip4.tos = htonl(grh->flow_label);
		udh->ip4.frag_off = htons(IP_DF);
		udh->ip4.ttl = grh->hop_limit;

		ipv4_addr = qedr_get_ipv4_from_gid(sgid_attr->gid.raw);
		udh->ip4.saddr = ipv4_addr;
		ipv4_addr = qedr_get_ipv4_from_gid(grh->dgid.raw);
		udh->ip4.daddr = ipv4_addr;
		/* note: checksum is calculated by the device */
	पूर्ण

	/* UDP */
	अगर (has_udp) अणु
		udh->udp.sport = htons(QEDR_ROCE_V2_UDP_SPORT);
		udh->udp.dport = htons(ROCE_V2_UDP_DPORT);
		udh->udp.csum = 0;
		/* UDP length is untouched hence is zero */
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक qedr_gsi_build_packet(काष्ठा qedr_dev *dev,
					काष्ठा qedr_qp *qp,
					स्थिर काष्ठा ib_send_wr *swr,
					काष्ठा qed_roce_ll2_packet **p_packet)
अणु
	u8 ud_header_buffer[QEDR_MAX_UD_HEADER_SIZE];
	काष्ठा qed_roce_ll2_packet *packet;
	काष्ठा pci_dev *pdev = dev->pdev;
	पूर्णांक roce_mode, header_size;
	काष्ठा ib_ud_header udh;
	पूर्णांक i, rc;

	*p_packet = शून्य;

	rc = qedr_gsi_build_header(dev, qp, swr, &udh, &roce_mode);
	अगर (rc)
		वापस rc;

	header_size = ib_ud_header_pack(&udh, &ud_header_buffer);

	packet = kzalloc(माप(*packet), GFP_ATOMIC);
	अगर (!packet)
		वापस -ENOMEM;

	packet->header.vaddr = dma_alloc_coherent(&pdev->dev, header_size,
						  &packet->header.baddr,
						  GFP_ATOMIC);
	अगर (!packet->header.vaddr) अणु
		kमुक्त(packet);
		वापस -ENOMEM;
	पूर्ण

	अगर (ether_addr_equal(udh.eth.smac_h, udh.eth.dmac_h))
		packet->tx_dest = QED_LL2_TX_DEST_LB;
	अन्यथा
		packet->tx_dest = QED_LL2_TX_DEST_NW;

	packet->roce_mode = roce_mode;
	स_नकल(packet->header.vaddr, ud_header_buffer, header_size);
	packet->header.len = header_size;
	packet->n_seg = swr->num_sge;
	क्रम (i = 0; i < packet->n_seg; i++) अणु
		packet->payload[i].baddr = swr->sg_list[i].addr;
		packet->payload[i].len = swr->sg_list[i].length;
	पूर्ण

	*p_packet = packet;

	वापस 0;
पूर्ण

पूर्णांक qedr_gsi_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
		       स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा qed_roce_ll2_packet *pkt = शून्य;
	काष्ठा qedr_qp *qp = get_qedr_qp(ibqp);
	काष्ठा qedr_dev *dev = qp->dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	अगर (qp->state != QED_ROCE_QP_STATE_RTS) अणु
		*bad_wr = wr;
		DP_ERR(dev,
		       "gsi post recv: failed to post rx buffer. state is %d and not QED_ROCE_QP_STATE_RTS\n",
		       qp->state);
		वापस -EINVAL;
	पूर्ण

	अगर (wr->num_sge > RDMA_MAX_SGE_PER_SQ_WQE) अणु
		DP_ERR(dev, "gsi post send: num_sge is too large (%d>%d)\n",
		       wr->num_sge, RDMA_MAX_SGE_PER_SQ_WQE);
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (wr->opcode != IB_WR_SEND) अणु
		DP_ERR(dev,
		       "gsi post send: failed due to unsupported opcode %d\n",
		       wr->opcode);
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	spin_lock_irqsave(&qp->q_lock, flags);

	rc = qedr_gsi_build_packet(dev, qp, wr, &pkt);
	अगर (rc) अणु
		spin_unlock_irqrestore(&qp->q_lock, flags);
		जाओ err;
	पूर्ण

	rc = qedr_ll2_post_tx(dev, pkt);

	अगर (!rc) अणु
		qp->wqe_wr_id[qp->sq.prod].wr_id = wr->wr_id;
		qedr_inc_sw_prod(&qp->sq);
		DP_DEBUG(qp->dev, QEDR_MSG_GSI,
			 "gsi post send: opcode=%d, wr_id=%llx\n", wr->opcode,
			 wr->wr_id);
	पूर्ण अन्यथा अणु
		DP_ERR(dev, "gsi post send: failed to transmit (rc=%d)\n", rc);
		rc = -EAGAIN;
		*bad_wr = wr;
	पूर्ण

	spin_unlock_irqrestore(&qp->q_lock, flags);

	अगर (wr->next) अणु
		DP_ERR(dev,
		       "gsi post send: failed second WR. Only one WR may be passed at a time\n");
		*bad_wr = wr->next;
		rc = -EINVAL;
	पूर्ण

	वापस rc;

err:
	*bad_wr = wr;
	वापस rc;
पूर्ण

पूर्णांक qedr_gsi_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
		       स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibqp->device);
	काष्ठा qedr_qp *qp = get_qedr_qp(ibqp);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	अगर ((qp->state != QED_ROCE_QP_STATE_RTR) &&
	    (qp->state != QED_ROCE_QP_STATE_RTS)) अणु
		*bad_wr = wr;
		DP_ERR(dev,
		       "gsi post recv: failed to post rx buffer. state is %d and not QED_ROCE_QP_STATE_RTR/S\n",
		       qp->state);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&qp->q_lock, flags);

	जबतक (wr) अणु
		अगर (wr->num_sge > QEDR_GSI_MAX_RECV_SGE) अणु
			DP_ERR(dev,
			       "gsi post recv: failed to post rx buffer. too many sges %d>%d\n",
			       wr->num_sge, QEDR_GSI_MAX_RECV_SGE);
			जाओ err;
		पूर्ण

		rc = dev->ops->ll2_post_rx_buffer(dev->rdma_ctx,
						  dev->gsi_ll2_handle,
						  wr->sg_list[0].addr,
						  wr->sg_list[0].length,
						  शून्य /* cookie */,
						  1 /* notअगरy_fw */);
		अगर (rc) अणु
			DP_ERR(dev,
			       "gsi post recv: failed to post rx buffer (rc=%d)\n",
			       rc);
			जाओ err;
		पूर्ण

		स_रखो(&qp->rqe_wr_id[qp->rq.prod], 0,
		       माप(qp->rqe_wr_id[qp->rq.prod]));
		qp->rqe_wr_id[qp->rq.prod].sg_list[0] = wr->sg_list[0];
		qp->rqe_wr_id[qp->rq.prod].wr_id = wr->wr_id;

		qedr_inc_sw_prod(&qp->rq);

		wr = wr->next;
	पूर्ण

	spin_unlock_irqrestore(&qp->q_lock, flags);

	वापस rc;
err:
	spin_unlock_irqrestore(&qp->q_lock, flags);
	*bad_wr = wr;
	वापस -ENOMEM;
पूर्ण

पूर्णांक qedr_gsi_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc)
अणु
	काष्ठा qedr_dev *dev = get_qedr_dev(ibcq->device);
	काष्ठा qedr_cq *cq = get_qedr_cq(ibcq);
	काष्ठा qedr_qp *qp = dev->gsi_qp;
	अचिन्हित दीर्घ flags;
	u16 vlan_id;
	पूर्णांक i = 0;

	spin_lock_irqsave(&cq->cq_lock, flags);

	जबतक (i < num_entries && qp->rq.cons != qp->rq.gsi_cons) अणु
		स_रखो(&wc[i], 0, माप(*wc));

		wc[i].qp = &qp->ibqp;
		wc[i].wr_id = qp->rqe_wr_id[qp->rq.cons].wr_id;
		wc[i].opcode = IB_WC_RECV;
		wc[i].pkey_index = 0;
		wc[i].status = (qp->rqe_wr_id[qp->rq.cons].rc) ?
		    IB_WC_GENERAL_ERR : IB_WC_SUCCESS;
		/* 0 - currently only one recv sg is supported */
		wc[i].byte_len = qp->rqe_wr_id[qp->rq.cons].sg_list[0].length;
		wc[i].wc_flags |= IB_WC_GRH | IB_WC_IP_CSUM_OK;
		ether_addr_copy(wc[i].smac, qp->rqe_wr_id[qp->rq.cons].smac);
		wc[i].wc_flags |= IB_WC_WITH_SMAC;

		vlan_id = qp->rqe_wr_id[qp->rq.cons].vlan &
			  VLAN_VID_MASK;
		अगर (vlan_id) अणु
			wc[i].wc_flags |= IB_WC_WITH_VLAN;
			wc[i].vlan_id = vlan_id;
			wc[i].sl = (qp->rqe_wr_id[qp->rq.cons].vlan &
				    VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;
		पूर्ण

		qedr_inc_sw_cons(&qp->rq);
		i++;
	पूर्ण

	जबतक (i < num_entries && qp->sq.cons != qp->sq.gsi_cons) अणु
		स_रखो(&wc[i], 0, माप(*wc));

		wc[i].qp = &qp->ibqp;
		wc[i].wr_id = qp->wqe_wr_id[qp->sq.cons].wr_id;
		wc[i].opcode = IB_WC_SEND;
		wc[i].status = IB_WC_SUCCESS;

		qedr_inc_sw_cons(&qp->sq);
		i++;
	पूर्ण

	spin_unlock_irqrestore(&cq->cq_lock, flags);

	DP_DEBUG(dev, QEDR_MSG_GSI,
		 "gsi poll_cq: requested entries=%d, actual=%d, qp->rq.cons=%d, qp->rq.gsi_cons=%x, qp->sq.cons=%d, qp->sq.gsi_cons=%d, qp_num=%d\n",
		 num_entries, i, qp->rq.cons, qp->rq.gsi_cons, qp->sq.cons,
		 qp->sq.gsi_cons, qp->ibqp.qp_num);

	वापस i;
पूर्ण
