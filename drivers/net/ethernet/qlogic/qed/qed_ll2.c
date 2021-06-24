<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/workqueue.h>
#समावेश <net/ipv6.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/qed/qed_ll2_अगर.h>
#समावेश "qed.h"
#समावेश "qed_cxt.h"
#समावेश "qed_dev_api.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_int.h"
#समावेश "qed_ll2.h"
#समावेश "qed_mcp.h"
#समावेश "qed_ooo.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_sp.h"
#समावेश "qed_rdma.h"

#घोषणा QED_LL2_RX_REGISTERED(ll2)	((ll2)->rx_queue.b_cb_रेजिस्टरed)
#घोषणा QED_LL2_TX_REGISTERED(ll2)	((ll2)->tx_queue.b_cb_रेजिस्टरed)

#घोषणा QED_LL2_TX_SIZE (256)
#घोषणा QED_LL2_RX_SIZE (4096)

काष्ठा qed_cb_ll2_info अणु
	पूर्णांक rx_cnt;
	u32 rx_size;
	u8 handle;

	/* Lock protecting LL2 buffer lists in sleepless context */
	spinlock_t lock;
	काष्ठा list_head list;

	स्थिर काष्ठा qed_ll2_cb_ops *cbs;
	व्योम *cb_cookie;
पूर्ण;

काष्ठा qed_ll2_buffer अणु
	काष्ठा list_head list;
	व्योम *data;
	dma_addr_t phys_addr;
पूर्ण;

अटल व्योम qed_ll2b_complete_tx_packet(व्योम *cxt,
					u8 connection_handle,
					व्योम *cookie,
					dma_addr_t first_frag_addr,
					bool b_last_fragment,
					bool b_last_packet)
अणु
	काष्ठा qed_hwfn *p_hwfn = cxt;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	काष्ठा sk_buff *skb = cookie;

	/* All we need to करो is release the mapping */
	dma_unmap_single(&p_hwfn->cdev->pdev->dev, first_frag_addr,
			 skb_headlen(skb), DMA_TO_DEVICE);

	अगर (cdev->ll2->cbs && cdev->ll2->cbs->tx_cb)
		cdev->ll2->cbs->tx_cb(cdev->ll2->cb_cookie, skb,
				      b_last_fragment);

	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल पूर्णांक qed_ll2_alloc_buffer(काष्ठा qed_dev *cdev,
				u8 **data, dma_addr_t *phys_addr)
अणु
	*data = kदो_स्मृति(cdev->ll2->rx_size, GFP_ATOMIC);
	अगर (!(*data)) अणु
		DP_INFO(cdev, "Failed to allocate LL2 buffer data\n");
		वापस -ENOMEM;
	पूर्ण

	*phys_addr = dma_map_single(&cdev->pdev->dev,
				    ((*data) + NET_SKB_PAD),
				    cdev->ll2->rx_size, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&cdev->pdev->dev, *phys_addr)) अणु
		DP_INFO(cdev, "Failed to map LL2 buffer data\n");
		kमुक्त((*data));
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_ll2_dealloc_buffer(काष्ठा qed_dev *cdev,
				 काष्ठा qed_ll2_buffer *buffer)
अणु
	spin_lock_bh(&cdev->ll2->lock);

	dma_unmap_single(&cdev->pdev->dev, buffer->phys_addr,
			 cdev->ll2->rx_size, DMA_FROM_DEVICE);
	kमुक्त(buffer->data);
	list_del(&buffer->list);

	cdev->ll2->rx_cnt--;
	अगर (!cdev->ll2->rx_cnt)
		DP_INFO(cdev, "All LL2 entries were removed\n");

	spin_unlock_bh(&cdev->ll2->lock);

	वापस 0;
पूर्ण

अटल व्योम qed_ll2_समाप्त_buffers(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_ll2_buffer *buffer, *पंचांगp_buffer;

	list_क्रम_each_entry_safe(buffer, पंचांगp_buffer, &cdev->ll2->list, list)
		qed_ll2_dealloc_buffer(cdev, buffer);
पूर्ण

अटल व्योम qed_ll2b_complete_rx_packet(व्योम *cxt,
					काष्ठा qed_ll2_comp_rx_data *data)
अणु
	काष्ठा qed_hwfn *p_hwfn = cxt;
	काष्ठा qed_ll2_buffer *buffer = data->cookie;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	dma_addr_t new_phys_addr;
	काष्ठा sk_buff *skb;
	bool reuse = false;
	पूर्णांक rc = -EINVAL;
	u8 *new_data;

	DP_VERBOSE(p_hwfn,
		   (NETIF_MSG_RX_STATUS | QED_MSG_STORAGE | NETIF_MSG_PKTDATA),
		   "Got an LL2 Rx completion: [Buffer at phys 0x%llx, offset 0x%02x] Length 0x%04x Parse_flags 0x%04x vlan 0x%04x Opaque data [0x%08x:0x%08x]\n",
		   (u64)data->rx_buf_addr,
		   data->u.placement_offset,
		   data->length.packet_length,
		   data->parse_flags,
		   data->vlan, data->opaque_data_0, data->opaque_data_1);

	अगर ((cdev->dp_module & NETIF_MSG_PKTDATA) && buffer->data) अणु
		prपूर्णांक_hex_dump(KERN_INFO, "",
			       DUMP_PREFIX_OFFSET, 16, 1,
			       buffer->data, data->length.packet_length, false);
	पूर्ण

	/* Determine अगर data is valid */
	अगर (data->length.packet_length < ETH_HLEN)
		reuse = true;

	/* Allocate a replacement क्रम buffer; Reuse upon failure */
	अगर (!reuse)
		rc = qed_ll2_alloc_buffer(p_hwfn->cdev, &new_data,
					  &new_phys_addr);

	/* If need to reuse or there's no replacement buffer, repost this */
	अगर (rc)
		जाओ out_post;
	dma_unmap_single(&cdev->pdev->dev, buffer->phys_addr,
			 cdev->ll2->rx_size, DMA_FROM_DEVICE);

	skb = build_skb(buffer->data, 0);
	अगर (!skb) अणु
		DP_INFO(cdev, "Failed to build SKB\n");
		kमुक्त(buffer->data);
		जाओ out_post1;
	पूर्ण

	data->u.placement_offset += NET_SKB_PAD;
	skb_reserve(skb, data->u.placement_offset);
	skb_put(skb, data->length.packet_length);
	skb_checksum_none_निश्चित(skb);

	/* Get parital ethernet inक्रमmation instead of eth_type_trans(),
	 * Since we करोn't have an associated net_device.
	 */
	skb_reset_mac_header(skb);
	skb->protocol = eth_hdr(skb)->h_proto;

	/* Pass SKB onward */
	अगर (cdev->ll2->cbs && cdev->ll2->cbs->rx_cb) अणु
		अगर (data->vlan)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       data->vlan);
		cdev->ll2->cbs->rx_cb(cdev->ll2->cb_cookie, skb,
				      data->opaque_data_0,
				      data->opaque_data_1);
	पूर्ण अन्यथा अणु
		DP_VERBOSE(p_hwfn, (NETIF_MSG_RX_STATUS | NETIF_MSG_PKTDATA |
				    QED_MSG_LL2 | QED_MSG_STORAGE),
			   "Dropping the packet\n");
		kमुक्त(buffer->data);
	पूर्ण

out_post1:
	/* Update Buffer inक्रमmation and update FW producer */
	buffer->data = new_data;
	buffer->phys_addr = new_phys_addr;

out_post:
	rc = qed_ll2_post_rx_buffer(p_hwfn, cdev->ll2->handle,
				    buffer->phys_addr, 0, buffer, 1);
	अगर (rc)
		qed_ll2_dealloc_buffer(cdev, buffer);
पूर्ण

अटल काष्ठा qed_ll2_info *__qed_ll2_handle_sanity(काष्ठा qed_hwfn *p_hwfn,
						    u8 connection_handle,
						    bool b_lock,
						    bool b_only_active)
अणु
	काष्ठा qed_ll2_info *p_ll2_conn, *p_ret = शून्य;

	अगर (connection_handle >= QED_MAX_NUM_OF_LL2_CONNECTIONS)
		वापस शून्य;

	अगर (!p_hwfn->p_ll2_info)
		वापस शून्य;

	p_ll2_conn = &p_hwfn->p_ll2_info[connection_handle];

	अगर (b_only_active) अणु
		अगर (b_lock)
			mutex_lock(&p_ll2_conn->mutex);
		अगर (p_ll2_conn->b_active)
			p_ret = p_ll2_conn;
		अगर (b_lock)
			mutex_unlock(&p_ll2_conn->mutex);
	पूर्ण अन्यथा अणु
		p_ret = p_ll2_conn;
	पूर्ण

	वापस p_ret;
पूर्ण

अटल काष्ठा qed_ll2_info *qed_ll2_handle_sanity(काष्ठा qed_hwfn *p_hwfn,
						  u8 connection_handle)
अणु
	वापस __qed_ll2_handle_sanity(p_hwfn, connection_handle, false, true);
पूर्ण

अटल काष्ठा qed_ll2_info *qed_ll2_handle_sanity_lock(काष्ठा qed_hwfn *p_hwfn,
						       u8 connection_handle)
अणु
	वापस __qed_ll2_handle_sanity(p_hwfn, connection_handle, true, true);
पूर्ण

अटल काष्ठा qed_ll2_info *qed_ll2_handle_sanity_inactive(काष्ठा qed_hwfn
							   *p_hwfn,
							   u8 connection_handle)
अणु
	वापस __qed_ll2_handle_sanity(p_hwfn, connection_handle, false, false);
पूर्ण

अटल व्योम qed_ll2_txq_flush(काष्ठा qed_hwfn *p_hwfn, u8 connection_handle)
अणु
	bool b_last_packet = false, b_last_frag = false;
	काष्ठा qed_ll2_tx_packet *p_pkt = शून्य;
	काष्ठा qed_ll2_info *p_ll2_conn;
	काष्ठा qed_ll2_tx_queue *p_tx;
	अचिन्हित दीर्घ flags = 0;
	dma_addr_t tx_frag;

	p_ll2_conn = qed_ll2_handle_sanity_inactive(p_hwfn, connection_handle);
	अगर (!p_ll2_conn)
		वापस;

	p_tx = &p_ll2_conn->tx_queue;

	spin_lock_irqsave(&p_tx->lock, flags);
	जबतक (!list_empty(&p_tx->active_descq)) अणु
		p_pkt = list_first_entry(&p_tx->active_descq,
					 काष्ठा qed_ll2_tx_packet, list_entry);
		अगर (!p_pkt)
			अवरोध;

		list_del(&p_pkt->list_entry);
		b_last_packet = list_empty(&p_tx->active_descq);
		list_add_tail(&p_pkt->list_entry, &p_tx->मुक्त_descq);
		spin_unlock_irqrestore(&p_tx->lock, flags);
		अगर (p_ll2_conn->input.conn_type == QED_LL2_TYPE_OOO) अणु
			काष्ठा qed_ooo_buffer *p_buffer;

			p_buffer = (काष्ठा qed_ooo_buffer *)p_pkt->cookie;
			qed_ooo_put_मुक्त_buffer(p_hwfn, p_hwfn->p_ooo_info,
						p_buffer);
		पूर्ण अन्यथा अणु
			p_tx->cur_completing_packet = *p_pkt;
			p_tx->cur_completing_bd_idx = 1;
			b_last_frag =
				p_tx->cur_completing_bd_idx == p_pkt->bd_used;
			tx_frag = p_pkt->bds_set[0].tx_frag;
			p_ll2_conn->cbs.tx_release_cb(p_ll2_conn->cbs.cookie,
						      p_ll2_conn->my_id,
						      p_pkt->cookie,
						      tx_frag,
						      b_last_frag,
						      b_last_packet);
		पूर्ण
		spin_lock_irqsave(&p_tx->lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&p_tx->lock, flags);
पूर्ण

अटल पूर्णांक qed_ll2_txq_completion(काष्ठा qed_hwfn *p_hwfn, व्योम *p_cookie)
अणु
	काष्ठा qed_ll2_info *p_ll2_conn = p_cookie;
	काष्ठा qed_ll2_tx_queue *p_tx = &p_ll2_conn->tx_queue;
	u16 new_idx = 0, num_bds = 0, num_bds_in_packet = 0;
	काष्ठा qed_ll2_tx_packet *p_pkt;
	bool b_last_frag = false;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = -EINVAL;

	spin_lock_irqsave(&p_tx->lock, flags);
	अगर (p_tx->b_completing_packet) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	new_idx = le16_to_cpu(*p_tx->p_fw_cons);
	num_bds = ((s16)new_idx - (s16)p_tx->bds_idx);
	जबतक (num_bds) अणु
		अगर (list_empty(&p_tx->active_descq))
			जाओ out;

		p_pkt = list_first_entry(&p_tx->active_descq,
					 काष्ठा qed_ll2_tx_packet, list_entry);
		अगर (!p_pkt)
			जाओ out;

		p_tx->b_completing_packet = true;
		p_tx->cur_completing_packet = *p_pkt;
		num_bds_in_packet = p_pkt->bd_used;
		list_del(&p_pkt->list_entry);

		अगर (num_bds < num_bds_in_packet) अणु
			DP_NOTICE(p_hwfn,
				  "Rest of BDs does not cover whole packet\n");
			जाओ out;
		पूर्ण

		num_bds -= num_bds_in_packet;
		p_tx->bds_idx += num_bds_in_packet;
		जबतक (num_bds_in_packet--)
			qed_chain_consume(&p_tx->txq_chain);

		p_tx->cur_completing_bd_idx = 1;
		b_last_frag = p_tx->cur_completing_bd_idx == p_pkt->bd_used;
		list_add_tail(&p_pkt->list_entry, &p_tx->मुक्त_descq);

		spin_unlock_irqrestore(&p_tx->lock, flags);

		p_ll2_conn->cbs.tx_comp_cb(p_ll2_conn->cbs.cookie,
					   p_ll2_conn->my_id,
					   p_pkt->cookie,
					   p_pkt->bds_set[0].tx_frag,
					   b_last_frag, !num_bds);

		spin_lock_irqsave(&p_tx->lock, flags);
	पूर्ण

	p_tx->b_completing_packet = false;
	rc = 0;
out:
	spin_unlock_irqrestore(&p_tx->lock, flags);
	वापस rc;
पूर्ण

अटल व्योम qed_ll2_rxq_parse_gsi(काष्ठा qed_hwfn *p_hwfn,
				  जोड़ core_rx_cqe_जोड़ *p_cqe,
				  काष्ठा qed_ll2_comp_rx_data *data)
अणु
	data->parse_flags = le16_to_cpu(p_cqe->rx_cqe_gsi.parse_flags.flags);
	data->length.data_length = le16_to_cpu(p_cqe->rx_cqe_gsi.data_length);
	data->vlan = le16_to_cpu(p_cqe->rx_cqe_gsi.vlan);
	data->opaque_data_0 = le32_to_cpu(p_cqe->rx_cqe_gsi.src_mac_addrhi);
	data->opaque_data_1 = le16_to_cpu(p_cqe->rx_cqe_gsi.src_mac_addrlo);
	data->u.data_length_error = p_cqe->rx_cqe_gsi.data_length_error;
	data->qp_id = le16_to_cpu(p_cqe->rx_cqe_gsi.qp_id);

	data->src_qp = le32_to_cpu(p_cqe->rx_cqe_gsi.src_qp);
पूर्ण

अटल व्योम qed_ll2_rxq_parse_reg(काष्ठा qed_hwfn *p_hwfn,
				  जोड़ core_rx_cqe_जोड़ *p_cqe,
				  काष्ठा qed_ll2_comp_rx_data *data)
अणु
	data->parse_flags = le16_to_cpu(p_cqe->rx_cqe_fp.parse_flags.flags);
	data->err_flags = le16_to_cpu(p_cqe->rx_cqe_fp.err_flags.flags);
	data->length.packet_length =
	    le16_to_cpu(p_cqe->rx_cqe_fp.packet_length);
	data->vlan = le16_to_cpu(p_cqe->rx_cqe_fp.vlan);
	data->opaque_data_0 = le32_to_cpu(p_cqe->rx_cqe_fp.opaque_data.data[0]);
	data->opaque_data_1 = le32_to_cpu(p_cqe->rx_cqe_fp.opaque_data.data[1]);
	data->u.placement_offset = p_cqe->rx_cqe_fp.placement_offset;
पूर्ण

अटल पूर्णांक
qed_ll2_handle_slowpath(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ll2_info *p_ll2_conn,
			जोड़ core_rx_cqe_जोड़ *p_cqe,
			अचिन्हित दीर्घ *p_lock_flags)
अणु
	काष्ठा qed_ll2_rx_queue *p_rx = &p_ll2_conn->rx_queue;
	काष्ठा core_rx_slow_path_cqe *sp_cqe;

	sp_cqe = &p_cqe->rx_cqe_sp;
	अगर (sp_cqe->ramrod_cmd_id != CORE_RAMROD_RX_QUEUE_FLUSH) अणु
		DP_NOTICE(p_hwfn,
			  "LL2 - unexpected Rx CQE slowpath ramrod_cmd_id:%d\n",
			  sp_cqe->ramrod_cmd_id);
		वापस -EINVAL;
	पूर्ण

	अगर (!p_ll2_conn->cbs.slowpath_cb) अणु
		DP_NOTICE(p_hwfn,
			  "LL2 - received RX_QUEUE_FLUSH but no callback was provided\n");
		वापस -EINVAL;
	पूर्ण

	spin_unlock_irqrestore(&p_rx->lock, *p_lock_flags);

	p_ll2_conn->cbs.slowpath_cb(p_ll2_conn->cbs.cookie,
				    p_ll2_conn->my_id,
				    le32_to_cpu(sp_cqe->opaque_data.data[0]),
				    le32_to_cpu(sp_cqe->opaque_data.data[1]));

	spin_lock_irqsave(&p_rx->lock, *p_lock_flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_ll2_rxq_handle_completion(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ll2_info *p_ll2_conn,
			      जोड़ core_rx_cqe_जोड़ *p_cqe,
			      अचिन्हित दीर्घ *p_lock_flags, bool b_last_cqe)
अणु
	काष्ठा qed_ll2_rx_queue *p_rx = &p_ll2_conn->rx_queue;
	काष्ठा qed_ll2_rx_packet *p_pkt = शून्य;
	काष्ठा qed_ll2_comp_rx_data data;

	अगर (!list_empty(&p_rx->active_descq))
		p_pkt = list_first_entry(&p_rx->active_descq,
					 काष्ठा qed_ll2_rx_packet, list_entry);
	अगर (!p_pkt) अणु
		DP_NOTICE(p_hwfn,
			  "[%d] LL2 Rx completion but active_descq is empty\n",
			  p_ll2_conn->input.conn_type);

		वापस -EIO;
	पूर्ण
	list_del(&p_pkt->list_entry);

	अगर (p_cqe->rx_cqe_sp.type == CORE_RX_CQE_TYPE_REGULAR)
		qed_ll2_rxq_parse_reg(p_hwfn, p_cqe, &data);
	अन्यथा
		qed_ll2_rxq_parse_gsi(p_hwfn, p_cqe, &data);
	अगर (qed_chain_consume(&p_rx->rxq_chain) != p_pkt->rxq_bd)
		DP_NOTICE(p_hwfn,
			  "Mismatch between active_descq and the LL2 Rx chain\n");

	list_add_tail(&p_pkt->list_entry, &p_rx->मुक्त_descq);

	data.connection_handle = p_ll2_conn->my_id;
	data.cookie = p_pkt->cookie;
	data.rx_buf_addr = p_pkt->rx_buf_addr;
	data.b_last_packet = b_last_cqe;

	spin_unlock_irqrestore(&p_rx->lock, *p_lock_flags);
	p_ll2_conn->cbs.rx_comp_cb(p_ll2_conn->cbs.cookie, &data);

	spin_lock_irqsave(&p_rx->lock, *p_lock_flags);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_ll2_rxq_completion(काष्ठा qed_hwfn *p_hwfn, व्योम *cookie)
अणु
	काष्ठा qed_ll2_info *p_ll2_conn = (काष्ठा qed_ll2_info *)cookie;
	काष्ठा qed_ll2_rx_queue *p_rx = &p_ll2_conn->rx_queue;
	जोड़ core_rx_cqe_जोड़ *cqe = शून्य;
	u16 cq_new_idx = 0, cq_old_idx = 0;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&p_rx->lock, flags);
	cq_new_idx = le16_to_cpu(*p_rx->p_fw_cons);
	cq_old_idx = qed_chain_get_cons_idx(&p_rx->rcq_chain);

	जबतक (cq_new_idx != cq_old_idx) अणु
		bool b_last_cqe = (cq_new_idx == cq_old_idx);

		cqe =
		    (जोड़ core_rx_cqe_जोड़ *)
		    qed_chain_consume(&p_rx->rcq_chain);
		cq_old_idx = qed_chain_get_cons_idx(&p_rx->rcq_chain);

		DP_VERBOSE(p_hwfn,
			   QED_MSG_LL2,
			   "LL2 [sw. cons %04x, fw. at %04x] - Got Packet of type %02x\n",
			   cq_old_idx, cq_new_idx, cqe->rx_cqe_sp.type);

		चयन (cqe->rx_cqe_sp.type) अणु
		हाल CORE_RX_CQE_TYPE_SLOW_PATH:
			rc = qed_ll2_handle_slowpath(p_hwfn, p_ll2_conn,
						     cqe, &flags);
			अवरोध;
		हाल CORE_RX_CQE_TYPE_GSI_OFFLOAD:
		हाल CORE_RX_CQE_TYPE_REGULAR:
			rc = qed_ll2_rxq_handle_completion(p_hwfn, p_ll2_conn,
							   cqe, &flags,
							   b_last_cqe);
			अवरोध;
		शेष:
			rc = -EIO;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&p_rx->lock, flags);
	वापस rc;
पूर्ण

अटल व्योम qed_ll2_rxq_flush(काष्ठा qed_hwfn *p_hwfn, u8 connection_handle)
अणु
	काष्ठा qed_ll2_info *p_ll2_conn = शून्य;
	काष्ठा qed_ll2_rx_packet *p_pkt = शून्य;
	काष्ठा qed_ll2_rx_queue *p_rx;
	अचिन्हित दीर्घ flags = 0;

	p_ll2_conn = qed_ll2_handle_sanity_inactive(p_hwfn, connection_handle);
	अगर (!p_ll2_conn)
		वापस;

	p_rx = &p_ll2_conn->rx_queue;

	spin_lock_irqsave(&p_rx->lock, flags);
	जबतक (!list_empty(&p_rx->active_descq)) अणु
		p_pkt = list_first_entry(&p_rx->active_descq,
					 काष्ठा qed_ll2_rx_packet, list_entry);
		अगर (!p_pkt)
			अवरोध;
		list_move_tail(&p_pkt->list_entry, &p_rx->मुक्त_descq);
		spin_unlock_irqrestore(&p_rx->lock, flags);

		अगर (p_ll2_conn->input.conn_type == QED_LL2_TYPE_OOO) अणु
			काष्ठा qed_ooo_buffer *p_buffer;

			p_buffer = (काष्ठा qed_ooo_buffer *)p_pkt->cookie;
			qed_ooo_put_मुक्त_buffer(p_hwfn, p_hwfn->p_ooo_info,
						p_buffer);
		पूर्ण अन्यथा अणु
			dma_addr_t rx_buf_addr = p_pkt->rx_buf_addr;
			व्योम *cookie = p_pkt->cookie;
			bool b_last;

			b_last = list_empty(&p_rx->active_descq);
			p_ll2_conn->cbs.rx_release_cb(p_ll2_conn->cbs.cookie,
						      p_ll2_conn->my_id,
						      cookie,
						      rx_buf_addr, b_last);
		पूर्ण
		spin_lock_irqsave(&p_rx->lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&p_rx->lock, flags);
पूर्ण

अटल bool
qed_ll2_lb_rxq_handler_slowpath(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा core_rx_slow_path_cqe *p_cqe)
अणु
	काष्ठा ooo_opaque *iscsi_ooo;
	u32 cid;

	अगर (p_cqe->ramrod_cmd_id != CORE_RAMROD_RX_QUEUE_FLUSH)
		वापस false;

	iscsi_ooo = (काष्ठा ooo_opaque *)&p_cqe->opaque_data;
	अगर (iscsi_ooo->ooo_opcode != TCP_EVENT_DELETE_ISLES)
		वापस false;

	/* Need to make a flush */
	cid = le32_to_cpu(iscsi_ooo->cid);
	qed_ooo_release_connection_isles(p_hwfn, p_hwfn->p_ooo_info, cid);

	वापस true;
पूर्ण

अटल पूर्णांक qed_ll2_lb_rxq_handler(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ll2_info *p_ll2_conn)
अणु
	काष्ठा qed_ll2_rx_queue *p_rx = &p_ll2_conn->rx_queue;
	u16 packet_length = 0, parse_flags = 0, vlan = 0;
	काष्ठा qed_ll2_rx_packet *p_pkt = शून्य;
	u32 num_ooo_add_to_peninsula = 0, cid;
	जोड़ core_rx_cqe_जोड़ *cqe = शून्य;
	u16 cq_new_idx = 0, cq_old_idx = 0;
	काष्ठा qed_ooo_buffer *p_buffer;
	काष्ठा ooo_opaque *iscsi_ooo;
	u8 placement_offset = 0;
	u8 cqe_type;

	cq_new_idx = le16_to_cpu(*p_rx->p_fw_cons);
	cq_old_idx = qed_chain_get_cons_idx(&p_rx->rcq_chain);
	अगर (cq_new_idx == cq_old_idx)
		वापस 0;

	जबतक (cq_new_idx != cq_old_idx) अणु
		काष्ठा core_rx_fast_path_cqe *p_cqe_fp;

		cqe = qed_chain_consume(&p_rx->rcq_chain);
		cq_old_idx = qed_chain_get_cons_idx(&p_rx->rcq_chain);
		cqe_type = cqe->rx_cqe_sp.type;

		अगर (cqe_type == CORE_RX_CQE_TYPE_SLOW_PATH)
			अगर (qed_ll2_lb_rxq_handler_slowpath(p_hwfn,
							    &cqe->rx_cqe_sp))
				जारी;

		अगर (cqe_type != CORE_RX_CQE_TYPE_REGULAR) अणु
			DP_NOTICE(p_hwfn,
				  "Got a non-regular LB LL2 completion [type 0x%02x]\n",
				  cqe_type);
			वापस -EINVAL;
		पूर्ण
		p_cqe_fp = &cqe->rx_cqe_fp;

		placement_offset = p_cqe_fp->placement_offset;
		parse_flags = le16_to_cpu(p_cqe_fp->parse_flags.flags);
		packet_length = le16_to_cpu(p_cqe_fp->packet_length);
		vlan = le16_to_cpu(p_cqe_fp->vlan);
		iscsi_ooo = (काष्ठा ooo_opaque *)&p_cqe_fp->opaque_data;
		qed_ooo_save_history_entry(p_hwfn, p_hwfn->p_ooo_info,
					   iscsi_ooo);
		cid = le32_to_cpu(iscsi_ooo->cid);

		/* Process delete isle first */
		अगर (iscsi_ooo->drop_size)
			qed_ooo_delete_isles(p_hwfn, p_hwfn->p_ooo_info, cid,
					     iscsi_ooo->drop_isle,
					     iscsi_ooo->drop_size);

		अगर (iscsi_ooo->ooo_opcode == TCP_EVENT_NOP)
			जारी;

		/* Now process create/add/join isles */
		अगर (list_empty(&p_rx->active_descq)) अणु
			DP_NOTICE(p_hwfn,
				  "LL2 OOO RX chain has no submitted buffers\n"
				  );
			वापस -EIO;
		पूर्ण

		p_pkt = list_first_entry(&p_rx->active_descq,
					 काष्ठा qed_ll2_rx_packet, list_entry);

		अगर ((iscsi_ooo->ooo_opcode == TCP_EVENT_ADD_NEW_ISLE) ||
		    (iscsi_ooo->ooo_opcode == TCP_EVENT_ADD_ISLE_RIGHT) ||
		    (iscsi_ooo->ooo_opcode == TCP_EVENT_ADD_ISLE_LEFT) ||
		    (iscsi_ooo->ooo_opcode == TCP_EVENT_ADD_PEN) ||
		    (iscsi_ooo->ooo_opcode == TCP_EVENT_JOIN)) अणु
			अगर (!p_pkt) अणु
				DP_NOTICE(p_hwfn,
					  "LL2 OOO RX packet is not valid\n");
				वापस -EIO;
			पूर्ण
			list_del(&p_pkt->list_entry);
			p_buffer = (काष्ठा qed_ooo_buffer *)p_pkt->cookie;
			p_buffer->packet_length = packet_length;
			p_buffer->parse_flags = parse_flags;
			p_buffer->vlan = vlan;
			p_buffer->placement_offset = placement_offset;
			qed_chain_consume(&p_rx->rxq_chain);
			list_add_tail(&p_pkt->list_entry, &p_rx->मुक्त_descq);

			चयन (iscsi_ooo->ooo_opcode) अणु
			हाल TCP_EVENT_ADD_NEW_ISLE:
				qed_ooo_add_new_isle(p_hwfn,
						     p_hwfn->p_ooo_info,
						     cid,
						     iscsi_ooo->ooo_isle,
						     p_buffer);
				अवरोध;
			हाल TCP_EVENT_ADD_ISLE_RIGHT:
				qed_ooo_add_new_buffer(p_hwfn,
						       p_hwfn->p_ooo_info,
						       cid,
						       iscsi_ooo->ooo_isle,
						       p_buffer,
						       QED_OOO_RIGHT_BUF);
				अवरोध;
			हाल TCP_EVENT_ADD_ISLE_LEFT:
				qed_ooo_add_new_buffer(p_hwfn,
						       p_hwfn->p_ooo_info,
						       cid,
						       iscsi_ooo->ooo_isle,
						       p_buffer,
						       QED_OOO_LEFT_BUF);
				अवरोध;
			हाल TCP_EVENT_JOIN:
				qed_ooo_add_new_buffer(p_hwfn,
						       p_hwfn->p_ooo_info,
						       cid,
						       iscsi_ooo->ooo_isle +
						       1,
						       p_buffer,
						       QED_OOO_LEFT_BUF);
				qed_ooo_join_isles(p_hwfn,
						   p_hwfn->p_ooo_info,
						   cid, iscsi_ooo->ooo_isle);
				अवरोध;
			हाल TCP_EVENT_ADD_PEN:
				num_ooo_add_to_peninsula++;
				qed_ooo_put_पढ़ोy_buffer(p_hwfn,
							 p_hwfn->p_ooo_info,
							 p_buffer, true);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			DP_NOTICE(p_hwfn,
				  "Unexpected event (%d) TX OOO completion\n",
				  iscsi_ooo->ooo_opcode);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
qed_ooo_submit_tx_buffers(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ll2_info *p_ll2_conn)
अणु
	काष्ठा qed_ll2_tx_pkt_info tx_pkt;
	काष्ठा qed_ooo_buffer *p_buffer;
	u16 l4_hdr_offset_w;
	dma_addr_t first_frag;
	u8 bd_flags;
	पूर्णांक rc;

	/* Submit Tx buffers here */
	जबतक ((p_buffer = qed_ooo_get_पढ़ोy_buffer(p_hwfn,
						    p_hwfn->p_ooo_info))) अणु
		l4_hdr_offset_w = 0;
		bd_flags = 0;

		first_frag = p_buffer->rx_buffer_phys_addr +
			     p_buffer->placement_offset;
		SET_FIELD(bd_flags, CORE_TX_BD_DATA_FORCE_VLAN_MODE, 1);
		SET_FIELD(bd_flags, CORE_TX_BD_DATA_L4_PROTOCOL, 1);

		स_रखो(&tx_pkt, 0, माप(tx_pkt));
		tx_pkt.num_of_bds = 1;
		tx_pkt.vlan = p_buffer->vlan;
		tx_pkt.bd_flags = bd_flags;
		tx_pkt.l4_hdr_offset_w = l4_hdr_offset_w;
		चयन (p_ll2_conn->tx_dest) अणु
		हाल CORE_TX_DEST_NW:
			tx_pkt.tx_dest = QED_LL2_TX_DEST_NW;
			अवरोध;
		हाल CORE_TX_DEST_LB:
			tx_pkt.tx_dest = QED_LL2_TX_DEST_LB;
			अवरोध;
		हाल CORE_TX_DEST_DROP:
		शेष:
			tx_pkt.tx_dest = QED_LL2_TX_DEST_DROP;
			अवरोध;
		पूर्ण
		tx_pkt.first_frag = first_frag;
		tx_pkt.first_frag_len = p_buffer->packet_length;
		tx_pkt.cookie = p_buffer;

		rc = qed_ll2_prepare_tx_packet(p_hwfn, p_ll2_conn->my_id,
					       &tx_pkt, true);
		अगर (rc) अणु
			qed_ooo_put_पढ़ोy_buffer(p_hwfn, p_hwfn->p_ooo_info,
						 p_buffer, false);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
qed_ooo_submit_rx_buffers(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ll2_info *p_ll2_conn)
अणु
	काष्ठा qed_ooo_buffer *p_buffer;
	पूर्णांक rc;

	जबतक ((p_buffer = qed_ooo_get_मुक्त_buffer(p_hwfn,
						   p_hwfn->p_ooo_info))) अणु
		rc = qed_ll2_post_rx_buffer(p_hwfn,
					    p_ll2_conn->my_id,
					    p_buffer->rx_buffer_phys_addr,
					    0, p_buffer, true);
		अगर (rc) अणु
			qed_ooo_put_मुक्त_buffer(p_hwfn,
						p_hwfn->p_ooo_info, p_buffer);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक qed_ll2_lb_rxq_completion(काष्ठा qed_hwfn *p_hwfn, व्योम *p_cookie)
अणु
	काष्ठा qed_ll2_info *p_ll2_conn = (काष्ठा qed_ll2_info *)p_cookie;
	पूर्णांक rc;

	अगर (!QED_LL2_RX_REGISTERED(p_ll2_conn))
		वापस 0;

	rc = qed_ll2_lb_rxq_handler(p_hwfn, p_ll2_conn);
	अगर (rc)
		वापस rc;

	qed_ooo_submit_rx_buffers(p_hwfn, p_ll2_conn);
	qed_ooo_submit_tx_buffers(p_hwfn, p_ll2_conn);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_ll2_lb_txq_completion(काष्ठा qed_hwfn *p_hwfn, व्योम *p_cookie)
अणु
	काष्ठा qed_ll2_info *p_ll2_conn = (काष्ठा qed_ll2_info *)p_cookie;
	काष्ठा qed_ll2_tx_queue *p_tx = &p_ll2_conn->tx_queue;
	काष्ठा qed_ll2_tx_packet *p_pkt = शून्य;
	काष्ठा qed_ooo_buffer *p_buffer;
	bool b_करोnt_submit_rx = false;
	u16 new_idx = 0, num_bds = 0;
	पूर्णांक rc;

	अगर (!QED_LL2_TX_REGISTERED(p_ll2_conn))
		वापस 0;

	new_idx = le16_to_cpu(*p_tx->p_fw_cons);
	num_bds = ((s16)new_idx - (s16)p_tx->bds_idx);

	अगर (!num_bds)
		वापस 0;

	जबतक (num_bds) अणु
		अगर (list_empty(&p_tx->active_descq))
			वापस -EINVAL;

		p_pkt = list_first_entry(&p_tx->active_descq,
					 काष्ठा qed_ll2_tx_packet, list_entry);
		अगर (!p_pkt)
			वापस -EINVAL;

		अगर (p_pkt->bd_used != 1) अणु
			DP_NOTICE(p_hwfn,
				  "Unexpectedly many BDs(%d) in TX OOO completion\n",
				  p_pkt->bd_used);
			वापस -EINVAL;
		पूर्ण

		list_del(&p_pkt->list_entry);

		num_bds--;
		p_tx->bds_idx++;
		qed_chain_consume(&p_tx->txq_chain);

		p_buffer = (काष्ठा qed_ooo_buffer *)p_pkt->cookie;
		list_add_tail(&p_pkt->list_entry, &p_tx->मुक्त_descq);

		अगर (b_करोnt_submit_rx) अणु
			qed_ooo_put_मुक्त_buffer(p_hwfn, p_hwfn->p_ooo_info,
						p_buffer);
			जारी;
		पूर्ण

		rc = qed_ll2_post_rx_buffer(p_hwfn, p_ll2_conn->my_id,
					    p_buffer->rx_buffer_phys_addr, 0,
					    p_buffer, true);
		अगर (rc != 0) अणु
			qed_ooo_put_मुक्त_buffer(p_hwfn,
						p_hwfn->p_ooo_info, p_buffer);
			b_करोnt_submit_rx = true;
		पूर्ण
	पूर्ण

	qed_ooo_submit_tx_buffers(p_hwfn, p_ll2_conn);

	वापस 0;
पूर्ण

अटल व्योम qed_ll2_stop_ooo(काष्ठा qed_hwfn *p_hwfn)
अणु
	u8 *handle = &p_hwfn->pf_params.iscsi_pf_params.ll2_ooo_queue_id;

	DP_VERBOSE(p_hwfn, (QED_MSG_STORAGE | QED_MSG_LL2),
		   "Stopping LL2 OOO queue [%02x]\n", *handle);

	qed_ll2_terminate_connection(p_hwfn, *handle);
	qed_ll2_release_connection(p_hwfn, *handle);
	*handle = QED_LL2_UNUSED_HANDLE;
पूर्ण

अटल पूर्णांक qed_sp_ll2_rx_queue_start(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ll2_info *p_ll2_conn,
				     u8 action_on_error)
अणु
	क्रमागत qed_ll2_conn_type conn_type = p_ll2_conn->input.conn_type;
	काष्ठा qed_ll2_rx_queue *p_rx = &p_ll2_conn->rx_queue;
	काष्ठा core_rx_start_ramrod_data *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	u16 cqe_pbl_size;
	पूर्णांक rc = 0;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_ll2_conn->cid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 CORE_RAMROD_RX_QUEUE_START,
				 PROTOCOLID_CORE, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.core_rx_queue_start;
	स_रखो(p_ramrod, 0, माप(*p_ramrod));
	p_ramrod->sb_id = cpu_to_le16(qed_पूर्णांक_get_sp_sb_id(p_hwfn));
	p_ramrod->sb_index = p_rx->rx_sb_index;
	p_ramrod->complete_event_flg = 1;

	p_ramrod->mtu = cpu_to_le16(p_ll2_conn->input.mtu);
	DMA_REGPAIR_LE(p_ramrod->bd_base, p_rx->rxq_chain.p_phys_addr);
	cqe_pbl_size = (u16)qed_chain_get_page_cnt(&p_rx->rcq_chain);
	p_ramrod->num_of_pbl_pages = cpu_to_le16(cqe_pbl_size);
	DMA_REGPAIR_LE(p_ramrod->cqe_pbl_addr,
		       qed_chain_get_pbl_phys(&p_rx->rcq_chain));

	p_ramrod->drop_ttl0_flg = p_ll2_conn->input.rx_drop_ttl0_flg;
	p_ramrod->inner_vlan_stripping_en =
		p_ll2_conn->input.rx_vlan_removal_en;

	अगर (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits) &&
	    p_ll2_conn->input.conn_type == QED_LL2_TYPE_FCOE)
		p_ramrod->report_outer_vlan = 1;
	p_ramrod->queue_id = p_ll2_conn->queue_id;
	p_ramrod->मुख्य_func_queue = p_ll2_conn->मुख्य_func_queue ? 1 : 0;

	अगर (test_bit(QED_MF_LL2_NON_UNICAST, &p_hwfn->cdev->mf_bits) &&
	    p_ramrod->मुख्य_func_queue && conn_type != QED_LL2_TYPE_ROCE &&
	    conn_type != QED_LL2_TYPE_IWARP) अणु
		p_ramrod->mf_si_bcast_accept_all = 1;
		p_ramrod->mf_si_mcast_accept_all = 1;
	पूर्ण अन्यथा अणु
		p_ramrod->mf_si_bcast_accept_all = 0;
		p_ramrod->mf_si_mcast_accept_all = 0;
	पूर्ण

	p_ramrod->action_on_error.error_type = action_on_error;
	p_ramrod->gsi_offload_flag = p_ll2_conn->input.gsi_enable;
	p_ramrod->zero_prod_flg = 1;

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक qed_sp_ll2_tx_queue_start(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ll2_info *p_ll2_conn)
अणु
	क्रमागत qed_ll2_conn_type conn_type = p_ll2_conn->input.conn_type;
	काष्ठा qed_ll2_tx_queue *p_tx = &p_ll2_conn->tx_queue;
	काष्ठा core_tx_start_ramrod_data *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	u16 pq_id = 0, pbl_size;
	पूर्णांक rc = -EINVAL;

	अगर (!QED_LL2_TX_REGISTERED(p_ll2_conn))
		वापस 0;

	अगर (p_ll2_conn->input.conn_type == QED_LL2_TYPE_OOO)
		p_ll2_conn->tx_stats_en = 0;
	अन्यथा
		p_ll2_conn->tx_stats_en = 1;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_ll2_conn->cid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 CORE_RAMROD_TX_QUEUE_START,
				 PROTOCOLID_CORE, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.core_tx_queue_start;

	p_ramrod->sb_id = cpu_to_le16(qed_पूर्णांक_get_sp_sb_id(p_hwfn));
	p_ramrod->sb_index = p_tx->tx_sb_index;
	p_ramrod->mtu = cpu_to_le16(p_ll2_conn->input.mtu);
	p_ramrod->stats_en = p_ll2_conn->tx_stats_en;
	p_ramrod->stats_id = p_ll2_conn->tx_stats_id;

	DMA_REGPAIR_LE(p_ramrod->pbl_base_addr,
		       qed_chain_get_pbl_phys(&p_tx->txq_chain));
	pbl_size = qed_chain_get_page_cnt(&p_tx->txq_chain);
	p_ramrod->pbl_size = cpu_to_le16(pbl_size);

	चयन (p_ll2_conn->input.tx_tc) अणु
	हाल PURE_LB_TC:
		pq_id = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_LB);
		अवरोध;
	हाल PKT_LB_TC:
		pq_id = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OOO);
		अवरोध;
	शेष:
		pq_id = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OFLD);
		अवरोध;
	पूर्ण

	p_ramrod->qm_pq_id = cpu_to_le16(pq_id);

	चयन (conn_type) अणु
	हाल QED_LL2_TYPE_FCOE:
		p_ramrod->conn_type = PROTOCOLID_FCOE;
		अवरोध;
	हाल QED_LL2_TYPE_ISCSI:
		p_ramrod->conn_type = PROTOCOLID_ISCSI;
		अवरोध;
	हाल QED_LL2_TYPE_ROCE:
		p_ramrod->conn_type = PROTOCOLID_ROCE;
		अवरोध;
	हाल QED_LL2_TYPE_IWARP:
		p_ramrod->conn_type = PROTOCOLID_IWARP;
		अवरोध;
	हाल QED_LL2_TYPE_OOO:
		अगर (p_hwfn->hw_info.personality == QED_PCI_ISCSI)
			p_ramrod->conn_type = PROTOCOLID_ISCSI;
		अन्यथा
			p_ramrod->conn_type = PROTOCOLID_IWARP;
		अवरोध;
	शेष:
		p_ramrod->conn_type = PROTOCOLID_ETH;
		DP_NOTICE(p_hwfn, "Unknown connection type: %d\n", conn_type);
	पूर्ण

	p_ramrod->gsi_offload_flag = p_ll2_conn->input.gsi_enable;

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc)
		वापस rc;

	rc = qed_db_recovery_add(p_hwfn->cdev, p_tx->करोorbell_addr,
				 &p_tx->db_msg, DB_REC_WIDTH_32B,
				 DB_REC_KERNEL);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_sp_ll2_rx_queue_stop(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ll2_info *p_ll2_conn)
अणु
	काष्ठा core_rx_stop_ramrod_data *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc = -EINVAL;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_ll2_conn->cid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 CORE_RAMROD_RX_QUEUE_STOP,
				 PROTOCOLID_CORE, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.core_rx_queue_stop;

	p_ramrod->complete_event_flg = 1;
	p_ramrod->queue_id = p_ll2_conn->queue_id;

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक qed_sp_ll2_tx_queue_stop(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ll2_info *p_ll2_conn)
अणु
	काष्ठा qed_ll2_tx_queue *p_tx = &p_ll2_conn->tx_queue;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc = -EINVAL;
	qed_db_recovery_del(p_hwfn->cdev, p_tx->करोorbell_addr, &p_tx->db_msg);

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_ll2_conn->cid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 CORE_RAMROD_TX_QUEUE_STOP,
				 PROTOCOLID_CORE, &init_data);
	अगर (rc)
		वापस rc;

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक
qed_ll2_acquire_connection_rx(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ll2_info *p_ll2_info)
अणु
	काष्ठा qed_chain_init_params params = अणु
		.पूर्णांकended_use	= QED_CHAIN_USE_TO_CONSUME_PRODUCE,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U16,
		.num_elems	= p_ll2_info->input.rx_num_desc,
	पूर्ण;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	काष्ठा qed_ll2_rx_packet *p_descq;
	u32 capacity;
	पूर्णांक rc = 0;

	अगर (!p_ll2_info->input.rx_num_desc)
		जाओ out;

	params.mode = QED_CHAIN_MODE_NEXT_PTR;
	params.elem_size = माप(काष्ठा core_rx_bd);

	rc = qed_chain_alloc(cdev, &p_ll2_info->rx_queue.rxq_chain, &params);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Failed to allocate ll2 rxq chain\n");
		जाओ out;
	पूर्ण

	capacity = qed_chain_get_capacity(&p_ll2_info->rx_queue.rxq_chain);
	p_descq = kसुस्मृति(capacity, माप(काष्ठा qed_ll2_rx_packet),
			  GFP_KERNEL);
	अगर (!p_descq) अणु
		rc = -ENOMEM;
		DP_NOTICE(p_hwfn, "Failed to allocate ll2 Rx desc\n");
		जाओ out;
	पूर्ण
	p_ll2_info->rx_queue.descq_array = p_descq;

	params.mode = QED_CHAIN_MODE_PBL;
	params.elem_size = माप(काष्ठा core_rx_fast_path_cqe);

	rc = qed_chain_alloc(cdev, &p_ll2_info->rx_queue.rcq_chain, &params);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Failed to allocate ll2 rcq chain\n");
		जाओ out;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_LL2,
		   "Allocated LL2 Rxq [Type %08x] with 0x%08x buffers\n",
		   p_ll2_info->input.conn_type, p_ll2_info->input.rx_num_desc);

out:
	वापस rc;
पूर्ण

अटल पूर्णांक qed_ll2_acquire_connection_tx(काष्ठा qed_hwfn *p_hwfn,
					 काष्ठा qed_ll2_info *p_ll2_info)
अणु
	काष्ठा qed_chain_init_params params = अणु
		.mode		= QED_CHAIN_MODE_PBL,
		.पूर्णांकended_use	= QED_CHAIN_USE_TO_CONSUME_PRODUCE,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U16,
		.num_elems	= p_ll2_info->input.tx_num_desc,
		.elem_size	= माप(काष्ठा core_tx_bd),
	पूर्ण;
	काष्ठा qed_ll2_tx_packet *p_descq;
	माप_प्रकार desc_size;
	u32 capacity;
	पूर्णांक rc = 0;

	अगर (!p_ll2_info->input.tx_num_desc)
		जाओ out;

	rc = qed_chain_alloc(p_hwfn->cdev, &p_ll2_info->tx_queue.txq_chain,
			     &params);
	अगर (rc)
		जाओ out;

	capacity = qed_chain_get_capacity(&p_ll2_info->tx_queue.txq_chain);
	/* All bds_set elements are flexibily added. */
	desc_size = काष्ठा_size(p_descq, bds_set,
				p_ll2_info->input.tx_max_bds_per_packet);

	p_descq = kसुस्मृति(capacity, desc_size, GFP_KERNEL);
	अगर (!p_descq) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	p_ll2_info->tx_queue.descq_mem = p_descq;

	DP_VERBOSE(p_hwfn, QED_MSG_LL2,
		   "Allocated LL2 Txq [Type %08x] with 0x%08x buffers\n",
		   p_ll2_info->input.conn_type, p_ll2_info->input.tx_num_desc);

out:
	अगर (rc)
		DP_NOTICE(p_hwfn,
			  "Can't allocate memory for Tx LL2 with 0x%08x buffers\n",
			  p_ll2_info->input.tx_num_desc);
	वापस rc;
पूर्ण

अटल पूर्णांक
qed_ll2_acquire_connection_ooo(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_ll2_info *p_ll2_info, u16 mtu)
अणु
	काष्ठा qed_ooo_buffer *p_buf = शून्य;
	व्योम *p_virt;
	u16 buf_idx;
	पूर्णांक rc = 0;

	अगर (p_ll2_info->input.conn_type != QED_LL2_TYPE_OOO)
		वापस rc;

	/* Correct number of requested OOO buffers अगर needed */
	अगर (!p_ll2_info->input.rx_num_ooo_buffers) अणु
		u16 num_desc = p_ll2_info->input.rx_num_desc;

		अगर (!num_desc)
			वापस -EINVAL;
		p_ll2_info->input.rx_num_ooo_buffers = num_desc * 2;
	पूर्ण

	क्रम (buf_idx = 0; buf_idx < p_ll2_info->input.rx_num_ooo_buffers;
	     buf_idx++) अणु
		p_buf = kzalloc(माप(*p_buf), GFP_KERNEL);
		अगर (!p_buf) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		p_buf->rx_buffer_size = mtu + 26 + ETH_CACHE_LINE_SIZE;
		p_buf->rx_buffer_size = (p_buf->rx_buffer_size +
					 ETH_CACHE_LINE_SIZE - 1) &
					~(ETH_CACHE_LINE_SIZE - 1);
		p_virt = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
					    p_buf->rx_buffer_size,
					    &p_buf->rx_buffer_phys_addr,
					    GFP_KERNEL);
		अगर (!p_virt) अणु
			kमुक्त(p_buf);
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		p_buf->rx_buffer_virt_addr = p_virt;
		qed_ooo_put_मुक्त_buffer(p_hwfn, p_hwfn->p_ooo_info, p_buf);
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_LL2,
		   "Allocated [%04x] LL2 OOO buffers [each of size 0x%08x]\n",
		   p_ll2_info->input.rx_num_ooo_buffers, p_buf->rx_buffer_size);

out:
	वापस rc;
पूर्ण

अटल पूर्णांक
qed_ll2_set_cbs(काष्ठा qed_ll2_info *p_ll2_info, स्थिर काष्ठा qed_ll2_cbs *cbs)
अणु
	अगर (!cbs || (!cbs->rx_comp_cb ||
		     !cbs->rx_release_cb ||
		     !cbs->tx_comp_cb || !cbs->tx_release_cb || !cbs->cookie))
		वापस -EINVAL;

	p_ll2_info->cbs.rx_comp_cb = cbs->rx_comp_cb;
	p_ll2_info->cbs.rx_release_cb = cbs->rx_release_cb;
	p_ll2_info->cbs.tx_comp_cb = cbs->tx_comp_cb;
	p_ll2_info->cbs.tx_release_cb = cbs->tx_release_cb;
	p_ll2_info->cbs.slowpath_cb = cbs->slowpath_cb;
	p_ll2_info->cbs.cookie = cbs->cookie;

	वापस 0;
पूर्ण

अटल व्योम _qed_ll2_calc_allowed_conns(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_ll2_acquire_data *data,
					u8 *start_idx, u8 *last_idx)
अणु
	/* LL2 queues handles will be split as follows:
	 * First will be the legacy queues, and then the ctx based.
	 */
	अगर (data->input.rx_conn_type == QED_LL2_RX_TYPE_LEGACY) अणु
		*start_idx = QED_LL2_LEGACY_CONN_BASE_PF;
		*last_idx = *start_idx +
			QED_MAX_NUM_OF_LEGACY_LL2_CONNS_PF;
	पूर्ण अन्यथा अणु
		/* QED_LL2_RX_TYPE_CTX */
		*start_idx = QED_LL2_CTX_CONN_BASE_PF;
		*last_idx = *start_idx +
			QED_MAX_NUM_OF_CTX_LL2_CONNS_PF;
	पूर्ण
पूर्ण

अटल क्रमागत core_error_handle
qed_ll2_get_error_choice(क्रमागत qed_ll2_error_handle err)
अणु
	चयन (err) अणु
	हाल QED_LL2_DROP_PACKET:
		वापस LL2_DROP_PACKET;
	हाल QED_LL2_DO_NOTHING:
		वापस LL2_DO_NOTHING;
	हाल QED_LL2_ASSERT:
		वापस LL2_ASSERT;
	शेष:
		वापस LL2_DO_NOTHING;
	पूर्ण
पूर्ण

पूर्णांक qed_ll2_acquire_connection(व्योम *cxt, काष्ठा qed_ll2_acquire_data *data)
अणु
	काष्ठा qed_hwfn *p_hwfn = cxt;
	qed_पूर्णांक_comp_cb_t comp_rx_cb, comp_tx_cb;
	काष्ठा qed_ll2_info *p_ll2_info = शून्य;
	u8 i, first_idx, last_idx, *p_tx_max;
	पूर्णांक rc;

	अगर (!data->p_connection_handle || !p_hwfn->p_ll2_info)
		वापस -EINVAL;

	_qed_ll2_calc_allowed_conns(p_hwfn, data, &first_idx, &last_idx);

	/* Find a मुक्त connection to be used */
	क्रम (i = first_idx; i < last_idx; i++) अणु
		mutex_lock(&p_hwfn->p_ll2_info[i].mutex);
		अगर (p_hwfn->p_ll2_info[i].b_active) अणु
			mutex_unlock(&p_hwfn->p_ll2_info[i].mutex);
			जारी;
		पूर्ण

		p_hwfn->p_ll2_info[i].b_active = true;
		p_ll2_info = &p_hwfn->p_ll2_info[i];
		mutex_unlock(&p_hwfn->p_ll2_info[i].mutex);
		अवरोध;
	पूर्ण
	अगर (!p_ll2_info)
		वापस -EBUSY;

	स_नकल(&p_ll2_info->input, &data->input, माप(p_ll2_info->input));

	चयन (data->input.tx_dest) अणु
	हाल QED_LL2_TX_DEST_NW:
		p_ll2_info->tx_dest = CORE_TX_DEST_NW;
		अवरोध;
	हाल QED_LL2_TX_DEST_LB:
		p_ll2_info->tx_dest = CORE_TX_DEST_LB;
		अवरोध;
	हाल QED_LL2_TX_DEST_DROP:
		p_ll2_info->tx_dest = CORE_TX_DEST_DROP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (data->input.conn_type == QED_LL2_TYPE_OOO ||
	    data->input.secondary_queue)
		p_ll2_info->मुख्य_func_queue = false;
	अन्यथा
		p_ll2_info->मुख्य_func_queue = true;

	/* Correct maximum number of Tx BDs */
	p_tx_max = &p_ll2_info->input.tx_max_bds_per_packet;
	अगर (*p_tx_max == 0)
		*p_tx_max = CORE_LL2_TX_MAX_BDS_PER_PACKET;
	अन्यथा
		*p_tx_max = min_t(u8, *p_tx_max,
				  CORE_LL2_TX_MAX_BDS_PER_PACKET);

	rc = qed_ll2_set_cbs(p_ll2_info, data->cbs);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Invalid callback functions\n");
		जाओ q_allocate_fail;
	पूर्ण

	rc = qed_ll2_acquire_connection_rx(p_hwfn, p_ll2_info);
	अगर (rc)
		जाओ q_allocate_fail;

	rc = qed_ll2_acquire_connection_tx(p_hwfn, p_ll2_info);
	अगर (rc)
		जाओ q_allocate_fail;

	rc = qed_ll2_acquire_connection_ooo(p_hwfn, p_ll2_info,
					    data->input.mtu);
	अगर (rc)
		जाओ q_allocate_fail;

	/* Register callbacks क्रम the Rx/Tx queues */
	अगर (data->input.conn_type == QED_LL2_TYPE_OOO) अणु
		comp_rx_cb = qed_ll2_lb_rxq_completion;
		comp_tx_cb = qed_ll2_lb_txq_completion;
	पूर्ण अन्यथा अणु
		comp_rx_cb = qed_ll2_rxq_completion;
		comp_tx_cb = qed_ll2_txq_completion;
	पूर्ण

	अगर (data->input.rx_num_desc) अणु
		qed_पूर्णांक_रेजिस्टर_cb(p_hwfn, comp_rx_cb,
				    &p_hwfn->p_ll2_info[i],
				    &p_ll2_info->rx_queue.rx_sb_index,
				    &p_ll2_info->rx_queue.p_fw_cons);
		p_ll2_info->rx_queue.b_cb_रेजिस्टरed = true;
	पूर्ण

	अगर (data->input.tx_num_desc) अणु
		qed_पूर्णांक_रेजिस्टर_cb(p_hwfn,
				    comp_tx_cb,
				    &p_hwfn->p_ll2_info[i],
				    &p_ll2_info->tx_queue.tx_sb_index,
				    &p_ll2_info->tx_queue.p_fw_cons);
		p_ll2_info->tx_queue.b_cb_रेजिस्टरed = true;
	पूर्ण

	*data->p_connection_handle = i;
	वापस rc;

q_allocate_fail:
	qed_ll2_release_connection(p_hwfn, i);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक qed_ll2_establish_connection_rx(काष्ठा qed_hwfn *p_hwfn,
					   काष्ठा qed_ll2_info *p_ll2_conn)
अणु
	क्रमागत qed_ll2_error_handle error_input;
	क्रमागत core_error_handle error_mode;
	u8 action_on_error = 0;
	पूर्णांक rc;

	अगर (!QED_LL2_RX_REGISTERED(p_ll2_conn))
		वापस 0;

	सूचीECT_REG_WR(p_ll2_conn->rx_queue.set_prod_addr, 0x0);
	error_input = p_ll2_conn->input.ai_err_packet_too_big;
	error_mode = qed_ll2_get_error_choice(error_input);
	SET_FIELD(action_on_error,
		  CORE_RX_ACTION_ON_ERROR_PACKET_TOO_BIG, error_mode);
	error_input = p_ll2_conn->input.ai_err_no_buf;
	error_mode = qed_ll2_get_error_choice(error_input);
	SET_FIELD(action_on_error, CORE_RX_ACTION_ON_ERROR_NO_BUFF, error_mode);

	rc = qed_sp_ll2_rx_queue_start(p_hwfn, p_ll2_conn, action_on_error);
	अगर (rc)
		वापस rc;

	अगर (p_ll2_conn->rx_queue.ctx_based) अणु
		rc = qed_db_recovery_add(p_hwfn->cdev,
					 p_ll2_conn->rx_queue.set_prod_addr,
					 &p_ll2_conn->rx_queue.db_data,
					 DB_REC_WIDTH_64B, DB_REC_KERNEL);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम
qed_ll2_establish_connection_ooo(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ll2_info *p_ll2_conn)
अणु
	अगर (p_ll2_conn->input.conn_type != QED_LL2_TYPE_OOO)
		वापस;

	qed_ooo_release_all_isles(p_hwfn, p_hwfn->p_ooo_info);
	qed_ooo_submit_rx_buffers(p_hwfn, p_ll2_conn);
पूर्ण

अटल अंतरभूत u8 qed_ll2_handle_to_queue_id(काष्ठा qed_hwfn *p_hwfn,
					    u8 handle,
					    u8 ll2_queue_type)
अणु
	u8 qid;

	अगर (ll2_queue_type == QED_LL2_RX_TYPE_LEGACY)
		वापस p_hwfn->hw_info.resc_start[QED_LL2_RAM_QUEUE] + handle;

	/* QED_LL2_RX_TYPE_CTX
	 * FW distinguishes between the legacy queues (ram based) and the
	 * ctx based queues by the queue_id.
	 * The first MAX_NUM_LL2_RX_RAM_QUEUES queues are legacy
	 * and the queue ids above that are ctx base.
	 */
	qid = p_hwfn->hw_info.resc_start[QED_LL2_CTX_QUEUE] +
	      MAX_NUM_LL2_RX_RAM_QUEUES;

	/* See comment on the acquire connection क्रम how the ll2
	 * queues handles are भागided.
	 */
	qid += (handle - QED_MAX_NUM_OF_LEGACY_LL2_CONNS_PF);

	वापस qid;
पूर्ण

पूर्णांक qed_ll2_establish_connection(व्योम *cxt, u8 connection_handle)
अणु
	काष्ठा e4_core_conn_context *p_cxt;
	काष्ठा qed_ll2_tx_packet *p_pkt;
	काष्ठा qed_ll2_info *p_ll2_conn;
	काष्ठा qed_hwfn *p_hwfn = cxt;
	काष्ठा qed_ll2_rx_queue *p_rx;
	काष्ठा qed_ll2_tx_queue *p_tx;
	काष्ठा qed_cxt_info cxt_info;
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc = -EINVAL;
	u32 i, capacity;
	माप_प्रकार desc_size;
	u8 qid;

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt)
		वापस -EAGAIN;

	p_ll2_conn = qed_ll2_handle_sanity_lock(p_hwfn, connection_handle);
	अगर (!p_ll2_conn) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	p_rx = &p_ll2_conn->rx_queue;
	p_tx = &p_ll2_conn->tx_queue;

	qed_chain_reset(&p_rx->rxq_chain);
	qed_chain_reset(&p_rx->rcq_chain);
	INIT_LIST_HEAD(&p_rx->active_descq);
	INIT_LIST_HEAD(&p_rx->मुक्त_descq);
	INIT_LIST_HEAD(&p_rx->posting_descq);
	spin_lock_init(&p_rx->lock);
	capacity = qed_chain_get_capacity(&p_rx->rxq_chain);
	क्रम (i = 0; i < capacity; i++)
		list_add_tail(&p_rx->descq_array[i].list_entry,
			      &p_rx->मुक्त_descq);
	*p_rx->p_fw_cons = 0;

	qed_chain_reset(&p_tx->txq_chain);
	INIT_LIST_HEAD(&p_tx->active_descq);
	INIT_LIST_HEAD(&p_tx->मुक्त_descq);
	INIT_LIST_HEAD(&p_tx->sending_descq);
	spin_lock_init(&p_tx->lock);
	capacity = qed_chain_get_capacity(&p_tx->txq_chain);
	/* All bds_set elements are flexibily added. */
	desc_size = काष्ठा_size(p_pkt, bds_set,
				p_ll2_conn->input.tx_max_bds_per_packet);

	क्रम (i = 0; i < capacity; i++) अणु
		p_pkt = p_tx->descq_mem + desc_size * i;
		list_add_tail(&p_pkt->list_entry, &p_tx->मुक्त_descq);
	पूर्ण
	p_tx->cur_completing_bd_idx = 0;
	p_tx->bds_idx = 0;
	p_tx->b_completing_packet = false;
	p_tx->cur_send_packet = शून्य;
	p_tx->cur_send_frag_num = 0;
	p_tx->cur_completing_frag_num = 0;
	*p_tx->p_fw_cons = 0;

	rc = qed_cxt_acquire_cid(p_hwfn, PROTOCOLID_CORE, &p_ll2_conn->cid);
	अगर (rc)
		जाओ out;
	cxt_info.iid = p_ll2_conn->cid;
	rc = qed_cxt_get_cid_info(p_hwfn, &cxt_info);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Cannot find context info for cid=%d\n",
			  p_ll2_conn->cid);
		जाओ out;
	पूर्ण

	p_cxt = cxt_info.p_cxt;

	स_रखो(p_cxt, 0, माप(*p_cxt));

	qid = qed_ll2_handle_to_queue_id(p_hwfn, connection_handle,
					 p_ll2_conn->input.rx_conn_type);
	p_ll2_conn->queue_id = qid;
	p_ll2_conn->tx_stats_id = qid;

	DP_VERBOSE(p_hwfn, QED_MSG_LL2,
		   "Establishing ll2 queue. PF %d ctx_based=%d abs qid=%d\n",
		   p_hwfn->rel_pf_id, p_ll2_conn->input.rx_conn_type, qid);

	अगर (p_ll2_conn->input.rx_conn_type == QED_LL2_RX_TYPE_LEGACY) अणु
		p_rx->set_prod_addr = p_hwfn->regview +
		    GTT_BAR0_MAP_REG_TSDM_RAM + TSTORM_LL2_RX_PRODS_OFFSET(qid);
	पूर्ण अन्यथा अणु
		/* QED_LL2_RX_TYPE_CTX - using करोorbell */
		p_rx->ctx_based = 1;

		p_rx->set_prod_addr = p_hwfn->करोorbells +
			p_hwfn->dpi_start_offset +
			DB_ADDR_SHIFT(DQ_PWM_OFFSET_TCM_LL2_PROD_UPDATE);

		/* prepare db data */
		p_rx->db_data.icid = cpu_to_le16((u16)p_ll2_conn->cid);
		SET_FIELD(p_rx->db_data.params,
			  CORE_PWM_PROD_UPDATE_DATA_AGG_CMD, DB_AGG_CMD_SET);
		SET_FIELD(p_rx->db_data.params,
			  CORE_PWM_PROD_UPDATE_DATA_RESERVED1, 0);
	पूर्ण

	p_tx->करोorbell_addr = (u8 __iomem *)p_hwfn->करोorbells +
					    qed_db_addr(p_ll2_conn->cid,
							DQ_DEMS_LEGACY);
	/* prepare db data */
	SET_FIELD(p_tx->db_msg.params, CORE_DB_DATA_DEST, DB_DEST_XCM);
	SET_FIELD(p_tx->db_msg.params, CORE_DB_DATA_AGG_CMD, DB_AGG_CMD_SET);
	SET_FIELD(p_tx->db_msg.params, CORE_DB_DATA_AGG_VAL_SEL,
		  DQ_XCM_CORE_TX_BD_PROD_CMD);
	p_tx->db_msg.agg_flags = DQ_XCM_CORE_DQ_CF_CMD;

	rc = qed_ll2_establish_connection_rx(p_hwfn, p_ll2_conn);
	अगर (rc)
		जाओ out;

	rc = qed_sp_ll2_tx_queue_start(p_hwfn, p_ll2_conn);
	अगर (rc)
		जाओ out;

	अगर (!QED_IS_RDMA_PERSONALITY(p_hwfn))
		qed_wr(p_hwfn, p_ptt, PRS_REG_USE_LIGHT_L2, 1);

	qed_ll2_establish_connection_ooo(p_hwfn, p_ll2_conn);

	अगर (p_ll2_conn->input.conn_type == QED_LL2_TYPE_FCOE) अणु
		अगर (!test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits))
			qed_llh_add_protocol_filter(p_hwfn->cdev, 0,
						    QED_LLH_FILTER_ETHERTYPE,
						    ETH_P_FCOE, 0);
		qed_llh_add_protocol_filter(p_hwfn->cdev, 0,
					    QED_LLH_FILTER_ETHERTYPE,
					    ETH_P_FIP, 0);
	पूर्ण

out:
	qed_ptt_release(p_hwfn, p_ptt);
	वापस rc;
पूर्ण

अटल व्योम qed_ll2_post_rx_buffer_notअगरy_fw(काष्ठा qed_hwfn *p_hwfn,
					     काष्ठा qed_ll2_rx_queue *p_rx,
					     काष्ठा qed_ll2_rx_packet *p_curp)
अणु
	काष्ठा qed_ll2_rx_packet *p_posting_packet = शून्य;
	काष्ठा core_ll2_rx_prod rx_prod = अणु 0, 0 पूर्ण;
	bool b_notअगरy_fw = false;
	u16 bd_prod, cq_prod;

	/* This handles the flushing of alपढ़ोy posted buffers */
	जबतक (!list_empty(&p_rx->posting_descq)) अणु
		p_posting_packet = list_first_entry(&p_rx->posting_descq,
						    काष्ठा qed_ll2_rx_packet,
						    list_entry);
		list_move_tail(&p_posting_packet->list_entry,
			       &p_rx->active_descq);
		b_notअगरy_fw = true;
	पूर्ण

	/* This handles the supplied packet [अगर there is one] */
	अगर (p_curp) अणु
		list_add_tail(&p_curp->list_entry, &p_rx->active_descq);
		b_notअगरy_fw = true;
	पूर्ण

	अगर (!b_notअगरy_fw)
		वापस;

	bd_prod = qed_chain_get_prod_idx(&p_rx->rxq_chain);
	cq_prod = qed_chain_get_prod_idx(&p_rx->rcq_chain);
	अगर (p_rx->ctx_based) अणु
		/* update producer by giving a करोorbell */
		p_rx->db_data.prod.bd_prod = cpu_to_le16(bd_prod);
		p_rx->db_data.prod.cqe_prod = cpu_to_le16(cq_prod);
		/* Make sure chain element is updated beक्रमe ringing the
		 * करोorbell
		 */
		dma_wmb();
		सूचीECT_REG_WR64(p_rx->set_prod_addr,
				*((u64 *)&p_rx->db_data));
	पूर्ण अन्यथा अणु
		rx_prod.bd_prod = cpu_to_le16(bd_prod);
		rx_prod.cqe_prod = cpu_to_le16(cq_prod);

		/* Make sure chain element is updated beक्रमe ringing the
		 * करोorbell
		 */
		dma_wmb();

		सूचीECT_REG_WR(p_rx->set_prod_addr, *((u32 *)&rx_prod));
	पूर्ण
पूर्ण

पूर्णांक qed_ll2_post_rx_buffer(व्योम *cxt,
			   u8 connection_handle,
			   dma_addr_t addr,
			   u16 buf_len, व्योम *cookie, u8 notअगरy_fw)
अणु
	काष्ठा qed_hwfn *p_hwfn = cxt;
	काष्ठा core_rx_bd_with_buff_len *p_curb = शून्य;
	काष्ठा qed_ll2_rx_packet *p_curp = शून्य;
	काष्ठा qed_ll2_info *p_ll2_conn;
	काष्ठा qed_ll2_rx_queue *p_rx;
	अचिन्हित दीर्घ flags;
	व्योम *p_data;
	पूर्णांक rc = 0;

	p_ll2_conn = qed_ll2_handle_sanity(p_hwfn, connection_handle);
	अगर (!p_ll2_conn)
		वापस -EINVAL;
	p_rx = &p_ll2_conn->rx_queue;

	spin_lock_irqsave(&p_rx->lock, flags);
	अगर (!list_empty(&p_rx->मुक्त_descq))
		p_curp = list_first_entry(&p_rx->मुक्त_descq,
					  काष्ठा qed_ll2_rx_packet, list_entry);
	अगर (p_curp) अणु
		अगर (qed_chain_get_elem_left(&p_rx->rxq_chain) &&
		    qed_chain_get_elem_left(&p_rx->rcq_chain)) अणु
			p_data = qed_chain_produce(&p_rx->rxq_chain);
			p_curb = (काष्ठा core_rx_bd_with_buff_len *)p_data;
			qed_chain_produce(&p_rx->rcq_chain);
		पूर्ण
	पूर्ण

	/* If we're lacking entires, let's try to flush buffers to FW */
	अगर (!p_curp || !p_curb) अणु
		rc = -EBUSY;
		p_curp = शून्य;
		जाओ out_notअगरy;
	पूर्ण

	/* We have an Rx packet we can fill */
	DMA_REGPAIR_LE(p_curb->addr, addr);
	p_curb->buff_length = cpu_to_le16(buf_len);
	p_curp->rx_buf_addr = addr;
	p_curp->cookie = cookie;
	p_curp->rxq_bd = p_curb;
	p_curp->buf_length = buf_len;
	list_del(&p_curp->list_entry);

	/* Check अगर we only want to enqueue this packet without inक्रमming FW */
	अगर (!notअगरy_fw) अणु
		list_add_tail(&p_curp->list_entry, &p_rx->posting_descq);
		जाओ out;
	पूर्ण

out_notअगरy:
	qed_ll2_post_rx_buffer_notअगरy_fw(p_hwfn, p_rx, p_curp);
out:
	spin_unlock_irqrestore(&p_rx->lock, flags);
	वापस rc;
पूर्ण

अटल व्योम qed_ll2_prepare_tx_packet_set(काष्ठा qed_hwfn *p_hwfn,
					  काष्ठा qed_ll2_tx_queue *p_tx,
					  काष्ठा qed_ll2_tx_packet *p_curp,
					  काष्ठा qed_ll2_tx_pkt_info *pkt,
					  u8 notअगरy_fw)
अणु
	list_del(&p_curp->list_entry);
	p_curp->cookie = pkt->cookie;
	p_curp->bd_used = pkt->num_of_bds;
	p_curp->notअगरy_fw = notअगरy_fw;
	p_tx->cur_send_packet = p_curp;
	p_tx->cur_send_frag_num = 0;

	p_curp->bds_set[p_tx->cur_send_frag_num].tx_frag = pkt->first_frag;
	p_curp->bds_set[p_tx->cur_send_frag_num].frag_len = pkt->first_frag_len;
	p_tx->cur_send_frag_num++;
पूर्ण

अटल व्योम
qed_ll2_prepare_tx_packet_set_bd(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ll2_info *p_ll2,
				 काष्ठा qed_ll2_tx_packet *p_curp,
				 काष्ठा qed_ll2_tx_pkt_info *pkt)
अणु
	काष्ठा qed_chain *p_tx_chain = &p_ll2->tx_queue.txq_chain;
	u16 prod_idx = qed_chain_get_prod_idx(p_tx_chain);
	काष्ठा core_tx_bd *start_bd = शून्य;
	क्रमागत core_roce_flavor_type roce_flavor;
	क्रमागत core_tx_dest tx_dest;
	u16 bd_data = 0, frag_idx;
	u16 bitfield1;

	roce_flavor = (pkt->qed_roce_flavor == QED_LL2_ROCE) ? CORE_ROCE
							     : CORE_RROCE;

	चयन (pkt->tx_dest) अणु
	हाल QED_LL2_TX_DEST_NW:
		tx_dest = CORE_TX_DEST_NW;
		अवरोध;
	हाल QED_LL2_TX_DEST_LB:
		tx_dest = CORE_TX_DEST_LB;
		अवरोध;
	हाल QED_LL2_TX_DEST_DROP:
		tx_dest = CORE_TX_DEST_DROP;
		अवरोध;
	शेष:
		tx_dest = CORE_TX_DEST_LB;
		अवरोध;
	पूर्ण

	start_bd = (काष्ठा core_tx_bd *)qed_chain_produce(p_tx_chain);
	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn) &&
	    p_ll2->input.conn_type == QED_LL2_TYPE_OOO) अणु
		start_bd->nw_vlan_or_lb_echo =
		    cpu_to_le16(IWARP_LL2_IN_ORDER_TX_QUEUE);
	पूर्ण अन्यथा अणु
		start_bd->nw_vlan_or_lb_echo = cpu_to_le16(pkt->vlan);
		अगर (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits) &&
		    p_ll2->input.conn_type == QED_LL2_TYPE_FCOE)
			pkt->हटाओ_stag = true;
	पूर्ण

	bitfield1 = le16_to_cpu(start_bd->bitfield1);
	SET_FIELD(bitfield1, CORE_TX_BD_L4_HDR_OFFSET_W, pkt->l4_hdr_offset_w);
	SET_FIELD(bitfield1, CORE_TX_BD_TX_DST, tx_dest);
	start_bd->bitfield1 = cpu_to_le16(bitfield1);

	bd_data |= pkt->bd_flags;
	SET_FIELD(bd_data, CORE_TX_BD_DATA_START_BD, 0x1);
	SET_FIELD(bd_data, CORE_TX_BD_DATA_NBDS, pkt->num_of_bds);
	SET_FIELD(bd_data, CORE_TX_BD_DATA_ROCE_FLAV, roce_flavor);
	SET_FIELD(bd_data, CORE_TX_BD_DATA_IP_CSUM, !!(pkt->enable_ip_cksum));
	SET_FIELD(bd_data, CORE_TX_BD_DATA_L4_CSUM, !!(pkt->enable_l4_cksum));
	SET_FIELD(bd_data, CORE_TX_BD_DATA_IP_LEN, !!(pkt->calc_ip_len));
	SET_FIELD(bd_data, CORE_TX_BD_DATA_DISABLE_STAG_INSERTION,
		  !!(pkt->हटाओ_stag));

	start_bd->bd_data.as_bitfield = cpu_to_le16(bd_data);
	DMA_REGPAIR_LE(start_bd->addr, pkt->first_frag);
	start_bd->nbytes = cpu_to_le16(pkt->first_frag_len);

	DP_VERBOSE(p_hwfn,
		   (NETIF_MSG_TX_QUEUED | QED_MSG_LL2),
		   "LL2 [q 0x%02x cid 0x%08x type 0x%08x] Tx Producer at [0x%04x] - set with a %04x bytes %02x BDs buffer at %08x:%08x\n",
		   p_ll2->queue_id,
		   p_ll2->cid,
		   p_ll2->input.conn_type,
		   prod_idx,
		   pkt->first_frag_len,
		   pkt->num_of_bds,
		   le32_to_cpu(start_bd->addr.hi),
		   le32_to_cpu(start_bd->addr.lo));

	अगर (p_ll2->tx_queue.cur_send_frag_num == pkt->num_of_bds)
		वापस;

	/* Need to provide the packet with additional BDs क्रम frags */
	क्रम (frag_idx = p_ll2->tx_queue.cur_send_frag_num;
	     frag_idx < pkt->num_of_bds; frag_idx++) अणु
		काष्ठा core_tx_bd **p_bd = &p_curp->bds_set[frag_idx].txq_bd;

		*p_bd = (काष्ठा core_tx_bd *)qed_chain_produce(p_tx_chain);
		(*p_bd)->bd_data.as_bitfield = 0;
		(*p_bd)->bitfield1 = 0;
		p_curp->bds_set[frag_idx].tx_frag = 0;
		p_curp->bds_set[frag_idx].frag_len = 0;
	पूर्ण
पूर्ण

/* This should be called जबतक the Txq spinlock is being held */
अटल व्योम qed_ll2_tx_packet_notअगरy(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ll2_info *p_ll2_conn)
अणु
	bool b_notअगरy = p_ll2_conn->tx_queue.cur_send_packet->notअगरy_fw;
	काष्ठा qed_ll2_tx_queue *p_tx = &p_ll2_conn->tx_queue;
	काष्ठा qed_ll2_tx_packet *p_pkt = शून्य;
	u16 bd_prod;

	/* If there are missing BDs, करोn't करो anything now */
	अगर (p_ll2_conn->tx_queue.cur_send_frag_num !=
	    p_ll2_conn->tx_queue.cur_send_packet->bd_used)
		वापस;

	/* Push the current packet to the list and clean after it */
	list_add_tail(&p_ll2_conn->tx_queue.cur_send_packet->list_entry,
		      &p_ll2_conn->tx_queue.sending_descq);
	p_ll2_conn->tx_queue.cur_send_packet = शून्य;
	p_ll2_conn->tx_queue.cur_send_frag_num = 0;

	/* Notअगरy FW of packet only अगर requested to */
	अगर (!b_notअगरy)
		वापस;

	bd_prod = qed_chain_get_prod_idx(&p_ll2_conn->tx_queue.txq_chain);

	जबतक (!list_empty(&p_tx->sending_descq)) अणु
		p_pkt = list_first_entry(&p_tx->sending_descq,
					 काष्ठा qed_ll2_tx_packet, list_entry);
		अगर (!p_pkt)
			अवरोध;

		list_move_tail(&p_pkt->list_entry, &p_tx->active_descq);
	पूर्ण

	p_tx->db_msg.spq_prod = cpu_to_le16(bd_prod);

	/* Make sure the BDs data is updated beक्रमe ringing the करोorbell */
	wmb();

	सूचीECT_REG_WR(p_tx->करोorbell_addr, *((u32 *)&p_tx->db_msg));

	DP_VERBOSE(p_hwfn,
		   (NETIF_MSG_TX_QUEUED | QED_MSG_LL2),
		   "LL2 [q 0x%02x cid 0x%08x type 0x%08x] Doorbelled [producer 0x%04x]\n",
		   p_ll2_conn->queue_id,
		   p_ll2_conn->cid,
		   p_ll2_conn->input.conn_type, p_tx->db_msg.spq_prod);
पूर्ण

पूर्णांक qed_ll2_prepare_tx_packet(व्योम *cxt,
			      u8 connection_handle,
			      काष्ठा qed_ll2_tx_pkt_info *pkt,
			      bool notअगरy_fw)
अणु
	काष्ठा qed_hwfn *p_hwfn = cxt;
	काष्ठा qed_ll2_tx_packet *p_curp = शून्य;
	काष्ठा qed_ll2_info *p_ll2_conn = शून्य;
	काष्ठा qed_ll2_tx_queue *p_tx;
	काष्ठा qed_chain *p_tx_chain;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	p_ll2_conn = qed_ll2_handle_sanity(p_hwfn, connection_handle);
	अगर (!p_ll2_conn)
		वापस -EINVAL;
	p_tx = &p_ll2_conn->tx_queue;
	p_tx_chain = &p_tx->txq_chain;

	अगर (pkt->num_of_bds > p_ll2_conn->input.tx_max_bds_per_packet)
		वापस -EIO;

	spin_lock_irqsave(&p_tx->lock, flags);
	अगर (p_tx->cur_send_packet) अणु
		rc = -EEXIST;
		जाओ out;
	पूर्ण

	/* Get entry, but only अगर we have tx elements क्रम it */
	अगर (!list_empty(&p_tx->मुक्त_descq))
		p_curp = list_first_entry(&p_tx->मुक्त_descq,
					  काष्ठा qed_ll2_tx_packet, list_entry);
	अगर (p_curp && qed_chain_get_elem_left(p_tx_chain) < pkt->num_of_bds)
		p_curp = शून्य;

	अगर (!p_curp) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	/* Prepare packet and BD, and perhaps send a करोorbell to FW */
	qed_ll2_prepare_tx_packet_set(p_hwfn, p_tx, p_curp, pkt, notअगरy_fw);

	qed_ll2_prepare_tx_packet_set_bd(p_hwfn, p_ll2_conn, p_curp, pkt);

	qed_ll2_tx_packet_notअगरy(p_hwfn, p_ll2_conn);

out:
	spin_unlock_irqrestore(&p_tx->lock, flags);
	वापस rc;
पूर्ण

पूर्णांक qed_ll2_set_fragment_of_tx_packet(व्योम *cxt,
				      u8 connection_handle,
				      dma_addr_t addr, u16 nbytes)
अणु
	काष्ठा qed_ll2_tx_packet *p_cur_send_packet = शून्य;
	काष्ठा qed_hwfn *p_hwfn = cxt;
	काष्ठा qed_ll2_info *p_ll2_conn = शून्य;
	u16 cur_send_frag_num = 0;
	काष्ठा core_tx_bd *p_bd;
	अचिन्हित दीर्घ flags;

	p_ll2_conn = qed_ll2_handle_sanity(p_hwfn, connection_handle);
	अगर (!p_ll2_conn)
		वापस -EINVAL;

	अगर (!p_ll2_conn->tx_queue.cur_send_packet)
		वापस -EINVAL;

	p_cur_send_packet = p_ll2_conn->tx_queue.cur_send_packet;
	cur_send_frag_num = p_ll2_conn->tx_queue.cur_send_frag_num;

	अगर (cur_send_frag_num >= p_cur_send_packet->bd_used)
		वापस -EINVAL;

	/* Fill the BD inक्रमmation, and possibly notअगरy FW */
	p_bd = p_cur_send_packet->bds_set[cur_send_frag_num].txq_bd;
	DMA_REGPAIR_LE(p_bd->addr, addr);
	p_bd->nbytes = cpu_to_le16(nbytes);
	p_cur_send_packet->bds_set[cur_send_frag_num].tx_frag = addr;
	p_cur_send_packet->bds_set[cur_send_frag_num].frag_len = nbytes;

	p_ll2_conn->tx_queue.cur_send_frag_num++;

	spin_lock_irqsave(&p_ll2_conn->tx_queue.lock, flags);
	qed_ll2_tx_packet_notअगरy(p_hwfn, p_ll2_conn);
	spin_unlock_irqrestore(&p_ll2_conn->tx_queue.lock, flags);

	वापस 0;
पूर्ण

पूर्णांक qed_ll2_terminate_connection(व्योम *cxt, u8 connection_handle)
अणु
	काष्ठा qed_hwfn *p_hwfn = cxt;
	काष्ठा qed_ll2_info *p_ll2_conn = शून्य;
	पूर्णांक rc = -EINVAL;
	काष्ठा qed_ptt *p_ptt;

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt)
		वापस -EAGAIN;

	p_ll2_conn = qed_ll2_handle_sanity_lock(p_hwfn, connection_handle);
	अगर (!p_ll2_conn) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* Stop Tx & Rx of connection, अगर needed */
	अगर (QED_LL2_TX_REGISTERED(p_ll2_conn)) अणु
		p_ll2_conn->tx_queue.b_cb_रेजिस्टरed = false;
		smp_wmb(); /* Make sure this is seen by ll2_lb_rxq_completion */
		rc = qed_sp_ll2_tx_queue_stop(p_hwfn, p_ll2_conn);
		अगर (rc)
			जाओ out;

		qed_ll2_txq_flush(p_hwfn, connection_handle);
		qed_पूर्णांक_unरेजिस्टर_cb(p_hwfn, p_ll2_conn->tx_queue.tx_sb_index);
	पूर्ण

	अगर (QED_LL2_RX_REGISTERED(p_ll2_conn)) अणु
		p_ll2_conn->rx_queue.b_cb_रेजिस्टरed = false;
		smp_wmb(); /* Make sure this is seen by ll2_lb_rxq_completion */

		अगर (p_ll2_conn->rx_queue.ctx_based)
			qed_db_recovery_del(p_hwfn->cdev,
					    p_ll2_conn->rx_queue.set_prod_addr,
					    &p_ll2_conn->rx_queue.db_data);

		rc = qed_sp_ll2_rx_queue_stop(p_hwfn, p_ll2_conn);
		अगर (rc)
			जाओ out;

		qed_ll2_rxq_flush(p_hwfn, connection_handle);
		qed_पूर्णांक_unरेजिस्टर_cb(p_hwfn, p_ll2_conn->rx_queue.rx_sb_index);
	पूर्ण

	अगर (p_ll2_conn->input.conn_type == QED_LL2_TYPE_OOO)
		qed_ooo_release_all_isles(p_hwfn, p_hwfn->p_ooo_info);

	अगर (p_ll2_conn->input.conn_type == QED_LL2_TYPE_FCOE) अणु
		अगर (!test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits))
			qed_llh_हटाओ_protocol_filter(p_hwfn->cdev, 0,
						       QED_LLH_FILTER_ETHERTYPE,
						       ETH_P_FCOE, 0);
		qed_llh_हटाओ_protocol_filter(p_hwfn->cdev, 0,
					       QED_LLH_FILTER_ETHERTYPE,
					       ETH_P_FIP, 0);
	पूर्ण

out:
	qed_ptt_release(p_hwfn, p_ptt);
	वापस rc;
पूर्ण

अटल व्योम qed_ll2_release_connection_ooo(काष्ठा qed_hwfn *p_hwfn,
					   काष्ठा qed_ll2_info *p_ll2_conn)
अणु
	काष्ठा qed_ooo_buffer *p_buffer;

	अगर (p_ll2_conn->input.conn_type != QED_LL2_TYPE_OOO)
		वापस;

	qed_ooo_release_all_isles(p_hwfn, p_hwfn->p_ooo_info);
	जबतक ((p_buffer = qed_ooo_get_मुक्त_buffer(p_hwfn,
						   p_hwfn->p_ooo_info))) अणु
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  p_buffer->rx_buffer_size,
				  p_buffer->rx_buffer_virt_addr,
				  p_buffer->rx_buffer_phys_addr);
		kमुक्त(p_buffer);
	पूर्ण
पूर्ण

व्योम qed_ll2_release_connection(व्योम *cxt, u8 connection_handle)
अणु
	काष्ठा qed_hwfn *p_hwfn = cxt;
	काष्ठा qed_ll2_info *p_ll2_conn = शून्य;

	p_ll2_conn = qed_ll2_handle_sanity(p_hwfn, connection_handle);
	अगर (!p_ll2_conn)
		वापस;

	kमुक्त(p_ll2_conn->tx_queue.descq_mem);
	qed_chain_मुक्त(p_hwfn->cdev, &p_ll2_conn->tx_queue.txq_chain);

	kमुक्त(p_ll2_conn->rx_queue.descq_array);
	qed_chain_मुक्त(p_hwfn->cdev, &p_ll2_conn->rx_queue.rxq_chain);
	qed_chain_मुक्त(p_hwfn->cdev, &p_ll2_conn->rx_queue.rcq_chain);

	qed_cxt_release_cid(p_hwfn, p_ll2_conn->cid);

	qed_ll2_release_connection_ooo(p_hwfn, p_ll2_conn);

	mutex_lock(&p_ll2_conn->mutex);
	p_ll2_conn->b_active = false;
	mutex_unlock(&p_ll2_conn->mutex);
पूर्ण

पूर्णांक qed_ll2_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ll2_info *p_ll2_connections;
	u8 i;

	/* Allocate LL2's set काष्ठा */
	p_ll2_connections = kसुस्मृति(QED_MAX_NUM_OF_LL2_CONNECTIONS,
				    माप(काष्ठा qed_ll2_info), GFP_KERNEL);
	अगर (!p_ll2_connections) अणु
		DP_NOTICE(p_hwfn, "Failed to allocate `struct qed_ll2'\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < QED_MAX_NUM_OF_LL2_CONNECTIONS; i++)
		p_ll2_connections[i].my_id = i;

	p_hwfn->p_ll2_info = p_ll2_connections;
	वापस 0;
पूर्ण

व्योम qed_ll2_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < QED_MAX_NUM_OF_LL2_CONNECTIONS; i++)
		mutex_init(&p_hwfn->p_ll2_info[i].mutex);
पूर्ण

व्योम qed_ll2_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (!p_hwfn->p_ll2_info)
		वापस;

	kमुक्त(p_hwfn->p_ll2_info);
	p_hwfn->p_ll2_info = शून्य;
पूर्ण

अटल व्योम _qed_ll2_get_port_stats(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt,
				    काष्ठा qed_ll2_stats *p_stats)
अणु
	काष्ठा core_ll2_port_stats port_stats;

	स_रखो(&port_stats, 0, माप(port_stats));
	qed_स_नकल_from(p_hwfn, p_ptt, &port_stats,
			BAR0_MAP_REG_TSDM_RAM +
			TSTORM_LL2_PORT_STAT_OFFSET(MFW_PORT(p_hwfn)),
			माप(port_stats));

	p_stats->gsi_invalid_hdr += HILO_64_REGPAIR(port_stats.gsi_invalid_hdr);
	p_stats->gsi_invalid_pkt_length +=
	    HILO_64_REGPAIR(port_stats.gsi_invalid_pkt_length);
	p_stats->gsi_unsupported_pkt_typ +=
	    HILO_64_REGPAIR(port_stats.gsi_unsupported_pkt_typ);
	p_stats->gsi_crcchksm_error +=
	    HILO_64_REGPAIR(port_stats.gsi_crcchksm_error);
पूर्ण

अटल व्योम _qed_ll2_get_tstats(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_ptt *p_ptt,
				काष्ठा qed_ll2_info *p_ll2_conn,
				काष्ठा qed_ll2_stats *p_stats)
अणु
	काष्ठा core_ll2_tstorm_per_queue_stat tstats;
	u8 qid = p_ll2_conn->queue_id;
	u32 tstats_addr;

	स_रखो(&tstats, 0, माप(tstats));
	tstats_addr = BAR0_MAP_REG_TSDM_RAM +
		      CORE_LL2_TSTORM_PER_QUEUE_STAT_OFFSET(qid);
	qed_स_नकल_from(p_hwfn, p_ptt, &tstats, tstats_addr, माप(tstats));

	p_stats->packet_too_big_discard +=
			HILO_64_REGPAIR(tstats.packet_too_big_discard);
	p_stats->no_buff_discard += HILO_64_REGPAIR(tstats.no_buff_discard);
पूर्ण

अटल व्योम _qed_ll2_get_ustats(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_ptt *p_ptt,
				काष्ठा qed_ll2_info *p_ll2_conn,
				काष्ठा qed_ll2_stats *p_stats)
अणु
	काष्ठा core_ll2_ustorm_per_queue_stat ustats;
	u8 qid = p_ll2_conn->queue_id;
	u32 ustats_addr;

	स_रखो(&ustats, 0, माप(ustats));
	ustats_addr = BAR0_MAP_REG_USDM_RAM +
		      CORE_LL2_USTORM_PER_QUEUE_STAT_OFFSET(qid);
	qed_स_नकल_from(p_hwfn, p_ptt, &ustats, ustats_addr, माप(ustats));

	p_stats->rcv_ucast_bytes += HILO_64_REGPAIR(ustats.rcv_ucast_bytes);
	p_stats->rcv_mcast_bytes += HILO_64_REGPAIR(ustats.rcv_mcast_bytes);
	p_stats->rcv_bcast_bytes += HILO_64_REGPAIR(ustats.rcv_bcast_bytes);
	p_stats->rcv_ucast_pkts += HILO_64_REGPAIR(ustats.rcv_ucast_pkts);
	p_stats->rcv_mcast_pkts += HILO_64_REGPAIR(ustats.rcv_mcast_pkts);
	p_stats->rcv_bcast_pkts += HILO_64_REGPAIR(ustats.rcv_bcast_pkts);
पूर्ण

अटल व्योम _qed_ll2_get_pstats(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_ptt *p_ptt,
				काष्ठा qed_ll2_info *p_ll2_conn,
				काष्ठा qed_ll2_stats *p_stats)
अणु
	काष्ठा core_ll2_pstorm_per_queue_stat pstats;
	u8 stats_id = p_ll2_conn->tx_stats_id;
	u32 pstats_addr;

	स_रखो(&pstats, 0, माप(pstats));
	pstats_addr = BAR0_MAP_REG_PSDM_RAM +
		      CORE_LL2_PSTORM_PER_QUEUE_STAT_OFFSET(stats_id);
	qed_स_नकल_from(p_hwfn, p_ptt, &pstats, pstats_addr, माप(pstats));

	p_stats->sent_ucast_bytes += HILO_64_REGPAIR(pstats.sent_ucast_bytes);
	p_stats->sent_mcast_bytes += HILO_64_REGPAIR(pstats.sent_mcast_bytes);
	p_stats->sent_bcast_bytes += HILO_64_REGPAIR(pstats.sent_bcast_bytes);
	p_stats->sent_ucast_pkts += HILO_64_REGPAIR(pstats.sent_ucast_pkts);
	p_stats->sent_mcast_pkts += HILO_64_REGPAIR(pstats.sent_mcast_pkts);
	p_stats->sent_bcast_pkts += HILO_64_REGPAIR(pstats.sent_bcast_pkts);
पूर्ण

अटल पूर्णांक __qed_ll2_get_stats(व्योम *cxt, u8 connection_handle,
			       काष्ठा qed_ll2_stats *p_stats)
अणु
	काष्ठा qed_hwfn *p_hwfn = cxt;
	काष्ठा qed_ll2_info *p_ll2_conn = शून्य;
	काष्ठा qed_ptt *p_ptt;

	अगर ((connection_handle >= QED_MAX_NUM_OF_LL2_CONNECTIONS) ||
	    !p_hwfn->p_ll2_info)
		वापस -EINVAL;

	p_ll2_conn = &p_hwfn->p_ll2_info[connection_handle];

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt) अणु
		DP_ERR(p_hwfn, "Failed to acquire ptt\n");
		वापस -EINVAL;
	पूर्ण

	अगर (p_ll2_conn->input.gsi_enable)
		_qed_ll2_get_port_stats(p_hwfn, p_ptt, p_stats);

	_qed_ll2_get_tstats(p_hwfn, p_ptt, p_ll2_conn, p_stats);

	_qed_ll2_get_ustats(p_hwfn, p_ptt, p_ll2_conn, p_stats);

	अगर (p_ll2_conn->tx_stats_en)
		_qed_ll2_get_pstats(p_hwfn, p_ptt, p_ll2_conn, p_stats);

	qed_ptt_release(p_hwfn, p_ptt);

	वापस 0;
पूर्ण

पूर्णांक qed_ll2_get_stats(व्योम *cxt,
		      u8 connection_handle, काष्ठा qed_ll2_stats *p_stats)
अणु
	स_रखो(p_stats, 0, माप(*p_stats));
	वापस __qed_ll2_get_stats(cxt, connection_handle, p_stats);
पूर्ण

अटल व्योम qed_ll2b_release_rx_packet(व्योम *cxt,
				       u8 connection_handle,
				       व्योम *cookie,
				       dma_addr_t rx_buf_addr,
				       bool b_last_packet)
अणु
	काष्ठा qed_hwfn *p_hwfn = cxt;

	qed_ll2_dealloc_buffer(p_hwfn->cdev, cookie);
पूर्ण

अटल व्योम qed_ll2_रेजिस्टर_cb_ops(काष्ठा qed_dev *cdev,
				    स्थिर काष्ठा qed_ll2_cb_ops *ops,
				    व्योम *cookie)
अणु
	cdev->ll2->cbs = ops;
	cdev->ll2->cb_cookie = cookie;
पूर्ण

अटल काष्ठा qed_ll2_cbs ll2_cbs = अणु
	.rx_comp_cb = &qed_ll2b_complete_rx_packet,
	.rx_release_cb = &qed_ll2b_release_rx_packet,
	.tx_comp_cb = &qed_ll2b_complete_tx_packet,
	.tx_release_cb = &qed_ll2b_complete_tx_packet,
पूर्ण;

अटल व्योम qed_ll2_set_conn_data(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ll2_acquire_data *data,
				  काष्ठा qed_ll2_params *params,
				  क्रमागत qed_ll2_conn_type conn_type,
				  u8 *handle, bool lb)
अणु
	स_रखो(data, 0, माप(*data));

	data->input.conn_type = conn_type;
	data->input.mtu = params->mtu;
	data->input.rx_num_desc = QED_LL2_RX_SIZE;
	data->input.rx_drop_ttl0_flg = params->drop_ttl0_packets;
	data->input.rx_vlan_removal_en = params->rx_vlan_stripping;
	data->input.tx_num_desc = QED_LL2_TX_SIZE;
	data->p_connection_handle = handle;
	data->cbs = &ll2_cbs;
	ll2_cbs.cookie = p_hwfn;

	अगर (lb) अणु
		data->input.tx_tc = PKT_LB_TC;
		data->input.tx_dest = QED_LL2_TX_DEST_LB;
	पूर्ण अन्यथा अणु
		data->input.tx_tc = 0;
		data->input.tx_dest = QED_LL2_TX_DEST_NW;
	पूर्ण
पूर्ण

अटल पूर्णांक qed_ll2_start_ooo(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ll2_params *params)
अणु
	u8 *handle = &p_hwfn->pf_params.iscsi_pf_params.ll2_ooo_queue_id;
	काष्ठा qed_ll2_acquire_data data;
	पूर्णांक rc;

	qed_ll2_set_conn_data(p_hwfn, &data, params,
			      QED_LL2_TYPE_OOO, handle, true);

	rc = qed_ll2_acquire_connection(p_hwfn, &data);
	अगर (rc) अणु
		DP_INFO(p_hwfn, "Failed to acquire LL2 OOO connection\n");
		जाओ out;
	पूर्ण

	rc = qed_ll2_establish_connection(p_hwfn, *handle);
	अगर (rc) अणु
		DP_INFO(p_hwfn, "Failed to establish LL2 OOO connection\n");
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	qed_ll2_release_connection(p_hwfn, *handle);
out:
	*handle = QED_LL2_UNUSED_HANDLE;
	वापस rc;
पूर्ण

अटल bool qed_ll2_is_storage_eng1(काष्ठा qed_dev *cdev)
अणु
	वापस (QED_IS_FCOE_PERSONALITY(QED_LEADING_HWFN(cdev)) ||
		QED_IS_ISCSI_PERSONALITY(QED_LEADING_HWFN(cdev))) &&
		(QED_AFFIN_HWFN(cdev) != QED_LEADING_HWFN(cdev));
पूर्ण

अटल पूर्णांक __qed_ll2_stop(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	पूर्णांक rc;

	rc = qed_ll2_terminate_connection(p_hwfn, cdev->ll2->handle);
	अगर (rc)
		DP_INFO(cdev, "Failed to terminate LL2 connection\n");

	qed_ll2_release_connection(p_hwfn, cdev->ll2->handle);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_ll2_stop(काष्ठा qed_dev *cdev)
अणु
	bool b_is_storage_eng1 = qed_ll2_is_storage_eng1(cdev);
	काष्ठा qed_hwfn *p_hwfn = QED_AFFIN_HWFN(cdev);
	पूर्णांक rc = 0, rc2 = 0;

	अगर (cdev->ll2->handle == QED_LL2_UNUSED_HANDLE)
		वापस 0;

	qed_llh_हटाओ_mac_filter(cdev, 0, cdev->ll2_mac_address);
	eth_zero_addr(cdev->ll2_mac_address);

	अगर (QED_IS_ISCSI_PERSONALITY(p_hwfn))
		qed_ll2_stop_ooo(p_hwfn);

	/* In CMT mode, LL2 is always started on engine 0 क्रम a storage PF */
	अगर (b_is_storage_eng1) अणु
		rc2 = __qed_ll2_stop(QED_LEADING_HWFN(cdev));
		अगर (rc2)
			DP_NOTICE(QED_LEADING_HWFN(cdev),
				  "Failed to stop LL2 on engine 0\n");
	पूर्ण

	rc = __qed_ll2_stop(p_hwfn);
	अगर (rc)
		DP_NOTICE(p_hwfn, "Failed to stop LL2\n");

	qed_ll2_समाप्त_buffers(cdev);

	cdev->ll2->handle = QED_LL2_UNUSED_HANDLE;

	वापस rc | rc2;
पूर्ण

अटल पूर्णांक __qed_ll2_start(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_ll2_params *params)
अणु
	काष्ठा qed_ll2_buffer *buffer, *पंचांगp_buffer;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	क्रमागत qed_ll2_conn_type conn_type;
	काष्ठा qed_ll2_acquire_data data;
	पूर्णांक rc, rx_cnt;

	चयन (p_hwfn->hw_info.personality) अणु
	हाल QED_PCI_FCOE:
		conn_type = QED_LL2_TYPE_FCOE;
		अवरोध;
	हाल QED_PCI_ISCSI:
		conn_type = QED_LL2_TYPE_ISCSI;
		अवरोध;
	हाल QED_PCI_ETH_ROCE:
		conn_type = QED_LL2_TYPE_ROCE;
		अवरोध;
	शेष:

		conn_type = QED_LL2_TYPE_TEST;
	पूर्ण

	qed_ll2_set_conn_data(p_hwfn, &data, params, conn_type,
			      &cdev->ll2->handle, false);

	rc = qed_ll2_acquire_connection(p_hwfn, &data);
	अगर (rc) अणु
		DP_INFO(p_hwfn, "Failed to acquire LL2 connection\n");
		वापस rc;
	पूर्ण

	rc = qed_ll2_establish_connection(p_hwfn, cdev->ll2->handle);
	अगर (rc) अणु
		DP_INFO(p_hwfn, "Failed to establish LL2 connection\n");
		जाओ release_conn;
	पूर्ण

	/* Post all Rx buffers to FW */
	spin_lock_bh(&cdev->ll2->lock);
	rx_cnt = cdev->ll2->rx_cnt;
	list_क्रम_each_entry_safe(buffer, पंचांगp_buffer, &cdev->ll2->list, list) अणु
		rc = qed_ll2_post_rx_buffer(p_hwfn,
					    cdev->ll2->handle,
					    buffer->phys_addr, 0, buffer, 1);
		अगर (rc) अणु
			DP_INFO(p_hwfn,
				"Failed to post an Rx buffer; Deleting it\n");
			dma_unmap_single(&cdev->pdev->dev, buffer->phys_addr,
					 cdev->ll2->rx_size, DMA_FROM_DEVICE);
			kमुक्त(buffer->data);
			list_del(&buffer->list);
			kमुक्त(buffer);
		पूर्ण अन्यथा अणु
			rx_cnt++;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&cdev->ll2->lock);

	अगर (rx_cnt == cdev->ll2->rx_cnt) अणु
		DP_NOTICE(p_hwfn, "Failed passing even a single Rx buffer\n");
		जाओ terminate_conn;
	पूर्ण
	cdev->ll2->rx_cnt = rx_cnt;

	वापस 0;

terminate_conn:
	qed_ll2_terminate_connection(p_hwfn, cdev->ll2->handle);
release_conn:
	qed_ll2_release_connection(p_hwfn, cdev->ll2->handle);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_ll2_start(काष्ठा qed_dev *cdev, काष्ठा qed_ll2_params *params)
अणु
	bool b_is_storage_eng1 = qed_ll2_is_storage_eng1(cdev);
	काष्ठा qed_hwfn *p_hwfn = QED_AFFIN_HWFN(cdev);
	काष्ठा qed_ll2_buffer *buffer;
	पूर्णांक rx_num_desc, i, rc;

	अगर (!is_valid_ether_addr(params->ll2_mac_address)) अणु
		DP_NOTICE(cdev, "Invalid Ethernet address\n");
		वापस -EINVAL;
	पूर्ण

	WARN_ON(!cdev->ll2->cbs);

	/* Initialize LL2 locks & lists */
	INIT_LIST_HEAD(&cdev->ll2->list);
	spin_lock_init(&cdev->ll2->lock);

	cdev->ll2->rx_size = NET_SKB_PAD + ETH_HLEN +
			     L1_CACHE_BYTES + params->mtu;

	/* Allocate memory क्रम LL2.
	 * In CMT mode, in हाल of a storage PF which is affपूर्णांकized to engine 1,
	 * LL2 is started also on engine 0 and thus we need twofold buffers.
	 */
	rx_num_desc = QED_LL2_RX_SIZE * (b_is_storage_eng1 ? 2 : 1);
	DP_INFO(cdev, "Allocating %d LL2 buffers of size %08x bytes\n",
		rx_num_desc, cdev->ll2->rx_size);
	क्रम (i = 0; i < rx_num_desc; i++) अणु
		buffer = kzalloc(माप(*buffer), GFP_KERNEL);
		अगर (!buffer) अणु
			DP_INFO(cdev, "Failed to allocate LL2 buffers\n");
			rc = -ENOMEM;
			जाओ err0;
		पूर्ण

		rc = qed_ll2_alloc_buffer(cdev, (u8 **)&buffer->data,
					  &buffer->phys_addr);
		अगर (rc) अणु
			kमुक्त(buffer);
			जाओ err0;
		पूर्ण

		list_add_tail(&buffer->list, &cdev->ll2->list);
	पूर्ण

	rc = __qed_ll2_start(p_hwfn, params);
	अगर (rc) अणु
		DP_NOTICE(cdev, "Failed to start LL2\n");
		जाओ err0;
	पूर्ण

	/* In CMT mode, always need to start LL2 on engine 0 क्रम a storage PF,
	 * since broadcast/mutlicast packets are routed to engine 0.
	 */
	अगर (b_is_storage_eng1) अणु
		rc = __qed_ll2_start(QED_LEADING_HWFN(cdev), params);
		अगर (rc) अणु
			DP_NOTICE(QED_LEADING_HWFN(cdev),
				  "Failed to start LL2 on engine 0\n");
			जाओ err1;
		पूर्ण
	पूर्ण

	अगर (QED_IS_ISCSI_PERSONALITY(p_hwfn)) अणु
		DP_VERBOSE(cdev, QED_MSG_STORAGE, "Starting OOO LL2 queue\n");
		rc = qed_ll2_start_ooo(p_hwfn, params);
		अगर (rc) अणु
			DP_NOTICE(cdev, "Failed to start OOO LL2\n");
			जाओ err2;
		पूर्ण
	पूर्ण

	rc = qed_llh_add_mac_filter(cdev, 0, params->ll2_mac_address);
	अगर (rc) अणु
		DP_NOTICE(cdev, "Failed to add an LLH filter\n");
		जाओ err3;
	पूर्ण

	ether_addr_copy(cdev->ll2_mac_address, params->ll2_mac_address);

	वापस 0;

err3:
	अगर (QED_IS_ISCSI_PERSONALITY(p_hwfn))
		qed_ll2_stop_ooo(p_hwfn);
err2:
	अगर (b_is_storage_eng1)
		__qed_ll2_stop(QED_LEADING_HWFN(cdev));
err1:
	__qed_ll2_stop(p_hwfn);
err0:
	qed_ll2_समाप्त_buffers(cdev);
	cdev->ll2->handle = QED_LL2_UNUSED_HANDLE;
	वापस rc;
पूर्ण

अटल पूर्णांक qed_ll2_start_xmit(काष्ठा qed_dev *cdev, काष्ठा sk_buff *skb,
			      अचिन्हित दीर्घ xmit_flags)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_AFFIN_HWFN(cdev);
	काष्ठा qed_ll2_tx_pkt_info pkt;
	स्थिर skb_frag_t *frag;
	u8 flags = 0, nr_frags;
	पूर्णांक rc = -EINVAL, i;
	dma_addr_t mapping;
	u16 vlan = 0;

	अगर (unlikely(skb->ip_summed != CHECKSUM_NONE)) अणु
		DP_INFO(cdev, "Cannot transmit a checksummed packet\n");
		वापस -EINVAL;
	पूर्ण

	/* Cache number of fragments from SKB since SKB may be मुक्तd by
	 * the completion routine after calling qed_ll2_prepare_tx_packet()
	 */
	nr_frags = skb_shinfo(skb)->nr_frags;

	अगर (1 + nr_frags > CORE_LL2_TX_MAX_BDS_PER_PACKET) अणु
		DP_ERR(cdev, "Cannot transmit a packet with %d fragments\n",
		       1 + nr_frags);
		वापस -EINVAL;
	पूर्ण

	mapping = dma_map_single(&cdev->pdev->dev, skb->data,
				 skb->len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(&cdev->pdev->dev, mapping))) अणु
		DP_NOTICE(cdev, "SKB mapping failed\n");
		वापस -EINVAL;
	पूर्ण

	/* Request HW to calculate IP csum */
	अगर (!((vlan_get_protocol(skb) == htons(ETH_P_IPV6)) &&
	      ipv6_hdr(skb)->nexthdr == NEXTHDR_IPV6))
		flags |= BIT(CORE_TX_BD_DATA_IP_CSUM_SHIFT);

	अगर (skb_vlan_tag_present(skb)) अणु
		vlan = skb_vlan_tag_get(skb);
		flags |= BIT(CORE_TX_BD_DATA_VLAN_INSERTION_SHIFT);
	पूर्ण

	स_रखो(&pkt, 0, माप(pkt));
	pkt.num_of_bds = 1 + nr_frags;
	pkt.vlan = vlan;
	pkt.bd_flags = flags;
	pkt.tx_dest = QED_LL2_TX_DEST_NW;
	pkt.first_frag = mapping;
	pkt.first_frag_len = skb->len;
	pkt.cookie = skb;
	अगर (test_bit(QED_MF_UFP_SPECIFIC, &cdev->mf_bits) &&
	    test_bit(QED_LL2_XMIT_FLAGS_FIP_DISCOVERY, &xmit_flags))
		pkt.हटाओ_stag = true;

	/* qed_ll2_prepare_tx_packet() may actually send the packet अगर
	 * there are no fragments in the skb and subsequently the completion
	 * routine may run and मुक्त the SKB, so no dereferencing the SKB
	 * beyond this poपूर्णांक unless skb has any fragments.
	 */
	rc = qed_ll2_prepare_tx_packet(p_hwfn, cdev->ll2->handle,
				       &pkt, 1);
	अगर (rc)
		जाओ err;

	क्रम (i = 0; i < nr_frags; i++) अणु
		frag = &skb_shinfo(skb)->frags[i];

		mapping = skb_frag_dma_map(&cdev->pdev->dev, frag, 0,
					   skb_frag_size(frag), DMA_TO_DEVICE);

		अगर (unlikely(dma_mapping_error(&cdev->pdev->dev, mapping))) अणु
			DP_NOTICE(cdev,
				  "Unable to map frag - dropping packet\n");
			rc = -ENOMEM;
			जाओ err;
		पूर्ण

		rc = qed_ll2_set_fragment_of_tx_packet(p_hwfn,
						       cdev->ll2->handle,
						       mapping,
						       skb_frag_size(frag));

		/* अगर failed not much to करो here, partial packet has been posted
		 * we can't मुक्त memory, will need to रुको क्रम completion
		 */
		अगर (rc)
			जाओ err2;
	पूर्ण

	वापस 0;

err:
	dma_unmap_single(&cdev->pdev->dev, mapping, skb->len, DMA_TO_DEVICE);
err2:
	वापस rc;
पूर्ण

अटल पूर्णांक qed_ll2_stats(काष्ठा qed_dev *cdev, काष्ठा qed_ll2_stats *stats)
अणु
	bool b_is_storage_eng1 = qed_ll2_is_storage_eng1(cdev);
	काष्ठा qed_hwfn *p_hwfn = QED_AFFIN_HWFN(cdev);
	पूर्णांक rc;

	अगर (!cdev->ll2)
		वापस -EINVAL;

	rc = qed_ll2_get_stats(p_hwfn, cdev->ll2->handle, stats);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Failed to get LL2 stats\n");
		वापस rc;
	पूर्ण

	/* In CMT mode, LL2 is always started on engine 0 क्रम a storage PF */
	अगर (b_is_storage_eng1) अणु
		rc = __qed_ll2_get_stats(QED_LEADING_HWFN(cdev),
					 cdev->ll2->handle, stats);
		अगर (rc) अणु
			DP_NOTICE(QED_LEADING_HWFN(cdev),
				  "Failed to get LL2 stats on engine 0\n");
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा qed_ll2_ops qed_ll2_ops_pass = अणु
	.start = &qed_ll2_start,
	.stop = &qed_ll2_stop,
	.start_xmit = &qed_ll2_start_xmit,
	.रेजिस्टर_cb_ops = &qed_ll2_रेजिस्टर_cb_ops,
	.get_stats = &qed_ll2_stats,
पूर्ण;

पूर्णांक qed_ll2_alloc_अगर(काष्ठा qed_dev *cdev)
अणु
	cdev->ll2 = kzalloc(माप(*cdev->ll2), GFP_KERNEL);
	वापस cdev->ll2 ? 0 : -ENOMEM;
पूर्ण

व्योम qed_ll2_dealloc_अगर(काष्ठा qed_dev *cdev)
अणु
	kमुक्त(cdev->ll2);
	cdev->ll2 = शून्य;
पूर्ण
