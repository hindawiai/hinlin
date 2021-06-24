<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/sctp.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>

#समावेश "hinic_common.h"
#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_wqe.h"
#समावेश "hinic_hw_wq.h"
#समावेश "hinic_hw_qp.h"
#समावेश "hinic_hw_dev.h"
#समावेश "hinic_dev.h"
#समावेश "hinic_tx.h"

#घोषणा TX_IRQ_NO_PENDING               0
#घोषणा TX_IRQ_NO_COALESC               0
#घोषणा TX_IRQ_NO_LLI_TIMER             0
#घोषणा TX_IRQ_NO_CREDIT                0
#घोषणा TX_IRQ_NO_RESEND_TIMER          0

#घोषणा CI_UPDATE_NO_PENDING            0
#घोषणा CI_UPDATE_NO_COALESC            0

#घोषणा HW_CONS_IDX(sq)                 be16_to_cpu(*(u16 *)((sq)->hw_ci_addr))

#घोषणा MIN_SKB_LEN			32

#घोषणा	MAX_PAYLOAD_OFFSET	        221
#घोषणा TRANSPORT_OFFSET(l4_hdr, skb)	((u32)((l4_hdr) - (skb)->data))

जोड़ hinic_l3 अणु
	काष्ठा iphdr *v4;
	काष्ठा ipv6hdr *v6;
	अचिन्हित अक्षर *hdr;
पूर्ण;

जोड़ hinic_l4 अणु
	काष्ठा tcphdr *tcp;
	काष्ठा udphdr *udp;
	अचिन्हित अक्षर *hdr;
पूर्ण;

क्रमागत hinic_offload_type अणु
	TX_OFFLOAD_TSO     = BIT(0),
	TX_OFFLOAD_CSUM    = BIT(1),
	TX_OFFLOAD_VLAN    = BIT(2),
	TX_OFFLOAD_INVALID = BIT(3),
पूर्ण;

/**
 * hinic_txq_clean_stats - Clean the statistics of specअगरic queue
 * @txq: Logical Tx Queue
 **/
व्योम hinic_txq_clean_stats(काष्ठा hinic_txq *txq)
अणु
	काष्ठा hinic_txq_stats *txq_stats = &txq->txq_stats;

	u64_stats_update_begin(&txq_stats->syncp);
	txq_stats->pkts    = 0;
	txq_stats->bytes   = 0;
	txq_stats->tx_busy = 0;
	txq_stats->tx_wake = 0;
	txq_stats->tx_dropped = 0;
	txq_stats->big_frags_pkts = 0;
	u64_stats_update_end(&txq_stats->syncp);
पूर्ण

/**
 * hinic_txq_get_stats - get statistics of Tx Queue
 * @txq: Logical Tx Queue
 * @stats: वापस updated stats here
 **/
व्योम hinic_txq_get_stats(काष्ठा hinic_txq *txq, काष्ठा hinic_txq_stats *stats)
अणु
	काष्ठा hinic_txq_stats *txq_stats = &txq->txq_stats;
	अचिन्हित पूर्णांक start;

	u64_stats_update_begin(&stats->syncp);
	करो अणु
		start = u64_stats_fetch_begin(&txq_stats->syncp);
		stats->pkts    = txq_stats->pkts;
		stats->bytes   = txq_stats->bytes;
		stats->tx_busy = txq_stats->tx_busy;
		stats->tx_wake = txq_stats->tx_wake;
		stats->tx_dropped = txq_stats->tx_dropped;
		stats->big_frags_pkts = txq_stats->big_frags_pkts;
	पूर्ण जबतक (u64_stats_fetch_retry(&txq_stats->syncp, start));
	u64_stats_update_end(&stats->syncp);
पूर्ण

/**
 * txq_stats_init - Initialize the statistics of specअगरic queue
 * @txq: Logical Tx Queue
 **/
अटल व्योम txq_stats_init(काष्ठा hinic_txq *txq)
अणु
	काष्ठा hinic_txq_stats *txq_stats = &txq->txq_stats;

	u64_stats_init(&txq_stats->syncp);
	hinic_txq_clean_stats(txq);
पूर्ण

/**
 * tx_map_skb - dma mapping क्रम skb and वापस sges
 * @nic_dev: nic device
 * @skb: the skb
 * @sges: वापसed sges
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक tx_map_skb(काष्ठा hinic_dev *nic_dev, काष्ठा sk_buff *skb,
		      काष्ठा hinic_sge *sges)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	skb_frag_t *frag;
	dma_addr_t dma_addr;
	पूर्णांक i, j;

	dma_addr = dma_map_single(&pdev->dev, skb->data, skb_headlen(skb),
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(&pdev->dev, dma_addr)) अणु
		dev_err(&pdev->dev, "Failed to map Tx skb data\n");
		वापस -EFAULT;
	पूर्ण

	hinic_set_sge(&sges[0], dma_addr, skb_headlen(skb));

	क्रम (i = 0 ; i < skb_shinfo(skb)->nr_frags; i++) अणु
		frag = &skb_shinfo(skb)->frags[i];

		dma_addr = skb_frag_dma_map(&pdev->dev, frag, 0,
					    skb_frag_size(frag),
					    DMA_TO_DEVICE);
		अगर (dma_mapping_error(&pdev->dev, dma_addr)) अणु
			dev_err(&pdev->dev, "Failed to map Tx skb frag\n");
			जाओ err_tx_map;
		पूर्ण

		hinic_set_sge(&sges[i + 1], dma_addr, skb_frag_size(frag));
	पूर्ण

	वापस 0;

err_tx_map:
	क्रम (j = 0; j < i; j++)
		dma_unmap_page(&pdev->dev, hinic_sge_to_dma(&sges[j + 1]),
			       sges[j + 1].len, DMA_TO_DEVICE);

	dma_unmap_single(&pdev->dev, hinic_sge_to_dma(&sges[0]), sges[0].len,
			 DMA_TO_DEVICE);
	वापस -EFAULT;
पूर्ण

/**
 * tx_unmap_skb - unmap the dma address of the skb
 * @nic_dev: nic device
 * @skb: the skb
 * @sges: the sges that are connected to the skb
 **/
अटल व्योम tx_unmap_skb(काष्ठा hinic_dev *nic_dev, काष्ठा sk_buff *skb,
			 काष्ठा hinic_sge *sges)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक i;

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags ; i++)
		dma_unmap_page(&pdev->dev, hinic_sge_to_dma(&sges[i + 1]),
			       sges[i + 1].len, DMA_TO_DEVICE);

	dma_unmap_single(&pdev->dev, hinic_sge_to_dma(&sges[0]), sges[0].len,
			 DMA_TO_DEVICE);
पूर्ण

अटल व्योम get_inner_l3_l4_type(काष्ठा sk_buff *skb, जोड़ hinic_l3 *ip,
				 जोड़ hinic_l4 *l4,
				 क्रमागत hinic_offload_type offload_type,
				 क्रमागत hinic_l3_offload_type *l3_type,
				 u8 *l4_proto)
अणु
	u8 *exthdr;

	अगर (ip->v4->version == 4) अणु
		*l3_type = (offload_type == TX_OFFLOAD_CSUM) ?
			   IPV4_PKT_NO_CHKSUM_OFFLOAD :
			   IPV4_PKT_WITH_CHKSUM_OFFLOAD;
		*l4_proto = ip->v4->protocol;
	पूर्ण अन्यथा अगर (ip->v4->version == 6) अणु
		*l3_type = IPV6_PKT;
		exthdr = ip->hdr + माप(*ip->v6);
		*l4_proto = ip->v6->nexthdr;
		अगर (exthdr != l4->hdr) अणु
			पूर्णांक start = exthdr - skb->data;
			__be16 frag_off;

			ipv6_skip_exthdr(skb, start, l4_proto, &frag_off);
		पूर्ण
	पूर्ण अन्यथा अणु
		*l3_type = L3TYPE_UNKNOWN;
		*l4_proto = 0;
	पूर्ण
पूर्ण

अटल व्योम get_inner_l4_info(काष्ठा sk_buff *skb, जोड़ hinic_l4 *l4,
			      क्रमागत hinic_offload_type offload_type, u8 l4_proto,
			      क्रमागत hinic_l4_offload_type *l4_offload,
			      u32 *l4_len, u32 *offset)
अणु
	*l4_offload = OFFLOAD_DISABLE;
	*offset = 0;
	*l4_len = 0;

	चयन (l4_proto) अणु
	हाल IPPROTO_TCP:
		*l4_offload = TCP_OFFLOAD_ENABLE;
		/* करोff in unit of 4B */
		*l4_len = l4->tcp->करोff * 4;
		*offset = *l4_len + TRANSPORT_OFFSET(l4->hdr, skb);
		अवरोध;

	हाल IPPROTO_UDP:
		*l4_offload = UDP_OFFLOAD_ENABLE;
		*l4_len = माप(काष्ठा udphdr);
		*offset = TRANSPORT_OFFSET(l4->hdr, skb);
		अवरोध;

	हाल IPPROTO_SCTP:
		/* only csum offload support sctp */
		अगर (offload_type != TX_OFFLOAD_CSUM)
			अवरोध;

		*l4_offload = SCTP_OFFLOAD_ENABLE;
		*l4_len = माप(काष्ठा sctphdr);
		*offset = TRANSPORT_OFFSET(l4->hdr, skb);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल __sum16 csum_magic(जोड़ hinic_l3 *ip, अचिन्हित लघु proto)
अणु
	वापस (ip->v4->version == 4) ?
		csum_tcpudp_magic(ip->v4->saddr, ip->v4->daddr, 0, proto, 0) :
		csum_ipv6_magic(&ip->v6->saddr, &ip->v6->daddr, 0, proto, 0);
पूर्ण

अटल पूर्णांक offload_tso(काष्ठा hinic_sq_task *task, u32 *queue_info,
		       काष्ठा sk_buff *skb)
अणु
	u32 offset, l4_len, ip_identअगरy, network_hdr_len;
	क्रमागत hinic_l3_offload_type l3_offload;
	क्रमागत hinic_l4_offload_type l4_offload;
	जोड़ hinic_l3 ip;
	जोड़ hinic_l4 l4;
	u8 l4_proto;

	अगर (!skb_is_gso(skb))
		वापस 0;

	अगर (skb_cow_head(skb, 0) < 0)
		वापस -EPROTONOSUPPORT;

	अगर (skb->encapsulation) अणु
		u32 gso_type = skb_shinfo(skb)->gso_type;
		u32 tunnel_type = 0;
		u32 l4_tunnel_len;

		ip.hdr = skb_network_header(skb);
		l4.hdr = skb_transport_header(skb);
		network_hdr_len = skb_inner_network_header_len(skb);

		अगर (ip.v4->version == 4) अणु
			ip.v4->tot_len = 0;
			l3_offload = IPV4_PKT_WITH_CHKSUM_OFFLOAD;
		पूर्ण अन्यथा अगर (ip.v4->version == 6) अणु
			l3_offload = IPV6_PKT;
		पूर्ण अन्यथा अणु
			l3_offload = 0;
		पूर्ण

		hinic_task_set_outter_l3(task, l3_offload,
					 skb_network_header_len(skb));

		अगर (gso_type & SKB_GSO_UDP_TUNNEL_CSUM) अणु
			l4.udp->check = ~csum_magic(&ip, IPPROTO_UDP);
			tunnel_type = TUNNEL_UDP_CSUM;
		पूर्ण अन्यथा अगर (gso_type & SKB_GSO_UDP_TUNNEL) अणु
			tunnel_type = TUNNEL_UDP_NO_CSUM;
		पूर्ण

		l4_tunnel_len = skb_inner_network_offset(skb) -
				skb_transport_offset(skb);
		hinic_task_set_tunnel_l4(task, tunnel_type, l4_tunnel_len);

		ip.hdr = skb_inner_network_header(skb);
		l4.hdr = skb_inner_transport_header(skb);
	पूर्ण अन्यथा अणु
		ip.hdr = skb_network_header(skb);
		l4.hdr = skb_transport_header(skb);
		network_hdr_len = skb_network_header_len(skb);
	पूर्ण

	/* initialize inner IP header fields */
	अगर (ip.v4->version == 4)
		ip.v4->tot_len = 0;
	अन्यथा
		ip.v6->payload_len = 0;

	get_inner_l3_l4_type(skb, &ip, &l4, TX_OFFLOAD_TSO, &l3_offload,
			     &l4_proto);

	hinic_task_set_inner_l3(task, l3_offload, network_hdr_len);

	ip_identअगरy = 0;
	अगर (l4_proto == IPPROTO_TCP)
		l4.tcp->check = ~csum_magic(&ip, IPPROTO_TCP);

	get_inner_l4_info(skb, &l4, TX_OFFLOAD_TSO, l4_proto, &l4_offload,
			  &l4_len, &offset);

	hinic_set_tso_inner_l4(task, queue_info, l4_offload, l4_len, offset,
			       ip_identअगरy, skb_shinfo(skb)->gso_size);

	वापस 1;
पूर्ण

अटल पूर्णांक offload_csum(काष्ठा hinic_sq_task *task, u32 *queue_info,
			काष्ठा sk_buff *skb)
अणु
	क्रमागत hinic_l4_offload_type l4_offload;
	u32 offset, l4_len, network_hdr_len;
	क्रमागत hinic_l3_offload_type l3_type;
	u32 tunnel_type = NOT_TUNNEL;
	जोड़ hinic_l3 ip;
	जोड़ hinic_l4 l4;
	u8 l4_proto;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	अगर (skb->encapsulation) अणु
		u32 l4_tunnel_len;

		tunnel_type = TUNNEL_UDP_NO_CSUM;
		ip.hdr = skb_network_header(skb);

		अगर (ip.v4->version == 4) अणु
			l3_type = IPV4_PKT_NO_CHKSUM_OFFLOAD;
			l4_proto = ip.v4->protocol;
		पूर्ण अन्यथा अगर (ip.v4->version == 6) अणु
			अचिन्हित अक्षर *exthdr;
			__be16 frag_off;

			l3_type = IPV6_PKT;
			tunnel_type = TUNNEL_UDP_CSUM;
			exthdr = ip.hdr + माप(*ip.v6);
			l4_proto = ip.v6->nexthdr;
			l4.hdr = skb_transport_header(skb);
			अगर (l4.hdr != exthdr)
				ipv6_skip_exthdr(skb, exthdr - skb->data,
						 &l4_proto, &frag_off);
		पूर्ण अन्यथा अणु
			l3_type = L3TYPE_UNKNOWN;
			l4_proto = IPPROTO_RAW;
		पूर्ण

		hinic_task_set_outter_l3(task, l3_type,
					 skb_network_header_len(skb));

		चयन (l4_proto) अणु
		हाल IPPROTO_UDP:
			l4_tunnel_len = skb_inner_network_offset(skb) -
					skb_transport_offset(skb);
			ip.hdr = skb_inner_network_header(skb);
			l4.hdr = skb_inner_transport_header(skb);
			network_hdr_len = skb_inner_network_header_len(skb);
			अवरोध;
		हाल IPPROTO_IPIP:
		हाल IPPROTO_IPV6:
			tunnel_type = NOT_TUNNEL;
			l4_tunnel_len = 0;

			ip.hdr = skb_inner_network_header(skb);
			l4.hdr = skb_transport_header(skb);
			network_hdr_len = skb_network_header_len(skb);
			अवरोध;
		शेष:
			/* Unsupported tunnel packet, disable csum offload */
			skb_checksum_help(skb);
			वापस 0;
		पूर्ण

		hinic_task_set_tunnel_l4(task, tunnel_type, l4_tunnel_len);
	पूर्ण अन्यथा अणु
		ip.hdr = skb_network_header(skb);
		l4.hdr = skb_transport_header(skb);
		network_hdr_len = skb_network_header_len(skb);
	पूर्ण

	get_inner_l3_l4_type(skb, &ip, &l4, TX_OFFLOAD_CSUM, &l3_type,
			     &l4_proto);

	hinic_task_set_inner_l3(task, l3_type, network_hdr_len);

	get_inner_l4_info(skb, &l4, TX_OFFLOAD_CSUM, l4_proto, &l4_offload,
			  &l4_len, &offset);

	hinic_set_cs_inner_l4(task, queue_info, l4_offload, l4_len, offset);

	वापस 1;
पूर्ण

अटल व्योम offload_vlan(काष्ठा hinic_sq_task *task, u32 *queue_info,
			 u16 vlan_tag, u16 vlan_pri)
अणु
	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(vlan_tag, VLAN_TAG) |
				HINIC_SQ_TASK_INFO0_SET(1U, VLAN_OFFLOAD);

	*queue_info |= HINIC_SQ_CTRL_SET(vlan_pri, QUEUE_INFO_PRI);
पूर्ण

अटल पूर्णांक hinic_tx_offload(काष्ठा sk_buff *skb, काष्ठा hinic_sq_task *task,
			    u32 *queue_info)
अणु
	क्रमागत hinic_offload_type offload = 0;
	u16 vlan_tag;
	पूर्णांक enabled;

	enabled = offload_tso(task, queue_info, skb);
	अगर (enabled > 0) अणु
		offload |= TX_OFFLOAD_TSO;
	पूर्ण अन्यथा अगर (enabled == 0) अणु
		enabled = offload_csum(task, queue_info, skb);
		अगर (enabled)
			offload |= TX_OFFLOAD_CSUM;
	पूर्ण अन्यथा अणु
		वापस -EPROTONOSUPPORT;
	पूर्ण

	अगर (unlikely(skb_vlan_tag_present(skb))) अणु
		vlan_tag = skb_vlan_tag_get(skb);
		offload_vlan(task, queue_info, vlan_tag,
			     vlan_tag >> VLAN_PRIO_SHIFT);
		offload |= TX_OFFLOAD_VLAN;
	पूर्ण

	अगर (offload)
		hinic_task_set_l2hdr(task, skb_network_offset(skb));

	/* payload offset should not more than 221 */
	अगर (HINIC_SQ_CTRL_GET(*queue_info, QUEUE_INFO_PLDOFF) >
	    MAX_PAYLOAD_OFFSET) अणु
		वापस -EPROTONOSUPPORT;
	पूर्ण

	/* mss should not less than 80 */
	अगर (HINIC_SQ_CTRL_GET(*queue_info, QUEUE_INFO_MSS) < HINIC_MSS_MIN) अणु
		*queue_info = HINIC_SQ_CTRL_CLEAR(*queue_info, QUEUE_INFO_MSS);
		*queue_info |= HINIC_SQ_CTRL_SET(HINIC_MSS_MIN, QUEUE_INFO_MSS);
	पूर्ण

	वापस 0;
पूर्ण

netdev_tx_t hinic_lb_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	u16 prod_idx, q_id = skb->queue_mapping;
	काष्ठा netdev_queue *netdev_txq;
	पूर्णांक nr_sges, err = NETDEV_TX_OK;
	काष्ठा hinic_sq_wqe *sq_wqe;
	अचिन्हित पूर्णांक wqe_size;
	काष्ठा hinic_txq *txq;
	काष्ठा hinic_qp *qp;

	txq = &nic_dev->txqs[q_id];
	qp = container_of(txq->sq, काष्ठा hinic_qp, sq);
	nr_sges = skb_shinfo(skb)->nr_frags + 1;

	err = tx_map_skb(nic_dev, skb, txq->sges);
	अगर (err)
		जाओ skb_error;

	wqe_size = HINIC_SQ_WQE_SIZE(nr_sges);

	sq_wqe = hinic_sq_get_wqe(txq->sq, wqe_size, &prod_idx);
	अगर (!sq_wqe) अणु
		netअगर_stop_subqueue(netdev, qp->q_id);

		sq_wqe = hinic_sq_get_wqe(txq->sq, wqe_size, &prod_idx);
		अगर (sq_wqe) अणु
			netअगर_wake_subqueue(nic_dev->netdev, qp->q_id);
			जाओ process_sq_wqe;
		पूर्ण

		tx_unmap_skb(nic_dev, skb, txq->sges);

		u64_stats_update_begin(&txq->txq_stats.syncp);
		txq->txq_stats.tx_busy++;
		u64_stats_update_end(&txq->txq_stats.syncp);
		err = NETDEV_TX_BUSY;
		wqe_size = 0;
		जाओ flush_skbs;
	पूर्ण

process_sq_wqe:
	hinic_sq_prepare_wqe(txq->sq, prod_idx, sq_wqe, txq->sges, nr_sges);
	hinic_sq_ग_लिखो_wqe(txq->sq, prod_idx, sq_wqe, skb, wqe_size);

flush_skbs:
	netdev_txq = netdev_get_tx_queue(netdev, q_id);
	अगर ((!netdev_xmit_more()) || (netअगर_xmit_stopped(netdev_txq)))
		hinic_sq_ग_लिखो_db(txq->sq, prod_idx, wqe_size, 0);

	वापस err;

skb_error:
	dev_kमुक्त_skb_any(skb);
	u64_stats_update_begin(&txq->txq_stats.syncp);
	txq->txq_stats.tx_dropped++;
	u64_stats_update_end(&txq->txq_stats.syncp);

	वापस NETDEV_TX_OK;
पूर्ण

netdev_tx_t hinic_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	u16 prod_idx, q_id = skb->queue_mapping;
	काष्ठा netdev_queue *netdev_txq;
	पूर्णांक nr_sges, err = NETDEV_TX_OK;
	काष्ठा hinic_sq_wqe *sq_wqe;
	अचिन्हित पूर्णांक wqe_size;
	काष्ठा hinic_txq *txq;
	काष्ठा hinic_qp *qp;

	txq = &nic_dev->txqs[q_id];
	qp = container_of(txq->sq, काष्ठा hinic_qp, sq);

	अगर (skb->len < MIN_SKB_LEN) अणु
		अगर (skb_pad(skb, MIN_SKB_LEN - skb->len)) अणु
			netdev_err(netdev, "Failed to pad skb\n");
			जाओ update_error_stats;
		पूर्ण

		skb->len = MIN_SKB_LEN;
	पूर्ण

	nr_sges = skb_shinfo(skb)->nr_frags + 1;
	अगर (nr_sges > 17) अणु
		u64_stats_update_begin(&txq->txq_stats.syncp);
		txq->txq_stats.big_frags_pkts++;
		u64_stats_update_end(&txq->txq_stats.syncp);
	पूर्ण

	अगर (nr_sges > txq->max_sges) अणु
		netdev_err(netdev, "Too many Tx sges\n");
		जाओ skb_error;
	पूर्ण

	err = tx_map_skb(nic_dev, skb, txq->sges);
	अगर (err)
		जाओ skb_error;

	wqe_size = HINIC_SQ_WQE_SIZE(nr_sges);

	sq_wqe = hinic_sq_get_wqe(txq->sq, wqe_size, &prod_idx);
	अगर (!sq_wqe) अणु
		netअगर_stop_subqueue(netdev, qp->q_id);

		/* Check क्रम the हाल मुक्त_tx_poll is called in another cpu
		 * and we stopped the subqueue after मुक्त_tx_poll check.
		 */
		sq_wqe = hinic_sq_get_wqe(txq->sq, wqe_size, &prod_idx);
		अगर (sq_wqe) अणु
			netअगर_wake_subqueue(nic_dev->netdev, qp->q_id);
			जाओ process_sq_wqe;
		पूर्ण

		tx_unmap_skb(nic_dev, skb, txq->sges);

		u64_stats_update_begin(&txq->txq_stats.syncp);
		txq->txq_stats.tx_busy++;
		u64_stats_update_end(&txq->txq_stats.syncp);
		err = NETDEV_TX_BUSY;
		wqe_size = 0;
		जाओ flush_skbs;
	पूर्ण

process_sq_wqe:
	hinic_sq_prepare_wqe(txq->sq, prod_idx, sq_wqe, txq->sges, nr_sges);

	err = hinic_tx_offload(skb, &sq_wqe->task, &sq_wqe->ctrl.queue_info);
	अगर (err)
		जाओ offload_error;

	hinic_sq_ग_लिखो_wqe(txq->sq, prod_idx, sq_wqe, skb, wqe_size);

flush_skbs:
	netdev_txq = netdev_get_tx_queue(netdev, q_id);
	अगर ((!netdev_xmit_more()) || (netअगर_xmit_stopped(netdev_txq)))
		hinic_sq_ग_लिखो_db(txq->sq, prod_idx, wqe_size, 0);

	वापस err;

offload_error:
	hinic_sq_वापस_wqe(txq->sq, wqe_size);
	tx_unmap_skb(nic_dev, skb, txq->sges);

skb_error:
	dev_kमुक्त_skb_any(skb);

update_error_stats:
	u64_stats_update_begin(&txq->txq_stats.syncp);
	txq->txq_stats.tx_dropped++;
	u64_stats_update_end(&txq->txq_stats.syncp);

	वापस NETDEV_TX_OK;
पूर्ण

/**
 * tx_मुक्त_skb - unmap and मुक्त skb
 * @nic_dev: nic device
 * @skb: the skb
 * @sges: the sges that are connected to the skb
 **/
अटल व्योम tx_मुक्त_skb(काष्ठा hinic_dev *nic_dev, काष्ठा sk_buff *skb,
			काष्ठा hinic_sge *sges)
अणु
	tx_unmap_skb(nic_dev, skb, sges);

	dev_kमुक्त_skb_any(skb);
पूर्ण

/**
 * मुक्त_all_rx_skbs - मुक्त all skbs in tx queue
 * @txq: tx queue
 **/
अटल व्योम मुक्त_all_tx_skbs(काष्ठा hinic_txq *txq)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(txq->netdev);
	काष्ठा hinic_sq *sq = txq->sq;
	काष्ठा hinic_sq_wqe *sq_wqe;
	अचिन्हित पूर्णांक wqe_size;
	काष्ठा sk_buff *skb;
	पूर्णांक nr_sges;
	u16 ci;

	जबतक ((sq_wqe = hinic_sq_पढ़ो_wqebb(sq, &skb, &wqe_size, &ci))) अणु
		sq_wqe = hinic_sq_पढ़ो_wqe(sq, &skb, wqe_size, &ci);
		अगर (!sq_wqe)
			अवरोध;

		nr_sges = skb_shinfo(skb)->nr_frags + 1;

		hinic_sq_get_sges(sq_wqe, txq->मुक्त_sges, nr_sges);

		hinic_sq_put_wqe(sq, wqe_size);

		tx_मुक्त_skb(nic_dev, skb, txq->मुक्त_sges);
	पूर्ण
पूर्ण

/**
 * मुक्त_tx_poll - मुक्त finished tx skbs in tx queue that connected to napi
 * @napi: napi
 * @budget: number of tx
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक मुक्त_tx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा hinic_txq *txq = container_of(napi, काष्ठा hinic_txq, napi);
	काष्ठा hinic_qp *qp = container_of(txq->sq, काष्ठा hinic_qp, sq);
	काष्ठा hinic_dev *nic_dev = netdev_priv(txq->netdev);
	काष्ठा netdev_queue *netdev_txq;
	काष्ठा hinic_sq *sq = txq->sq;
	काष्ठा hinic_wq *wq = sq->wq;
	काष्ठा hinic_sq_wqe *sq_wqe;
	अचिन्हित पूर्णांक wqe_size;
	पूर्णांक nr_sges, pkts = 0;
	काष्ठा sk_buff *skb;
	u64 tx_bytes = 0;
	u16 hw_ci, sw_ci;

	करो अणु
		hw_ci = HW_CONS_IDX(sq) & wq->mask;

		dma_rmb();

		/* Reading a WQEBB to get real WQE size and consumer index. */
		sq_wqe = hinic_sq_पढ़ो_wqebb(sq, &skb, &wqe_size, &sw_ci);
		अगर ((!sq_wqe) ||
		    (((hw_ci - sw_ci) & wq->mask) * wq->wqebb_size < wqe_size))
			अवरोध;

		/* If this WQE have multiple WQEBBs, we will पढ़ो again to get
		 * full size WQE.
		 */
		अगर (wqe_size > wq->wqebb_size) अणु
			sq_wqe = hinic_sq_पढ़ो_wqe(sq, &skb, wqe_size, &sw_ci);
			अगर (unlikely(!sq_wqe))
				अवरोध;
		पूर्ण

		tx_bytes += skb->len;
		pkts++;

		nr_sges = skb_shinfo(skb)->nr_frags + 1;

		hinic_sq_get_sges(sq_wqe, txq->मुक्त_sges, nr_sges);

		hinic_sq_put_wqe(sq, wqe_size);

		tx_मुक्त_skb(nic_dev, skb, txq->मुक्त_sges);
	पूर्ण जबतक (pkts < budget);

	अगर (__netअगर_subqueue_stopped(nic_dev->netdev, qp->q_id) &&
	    hinic_get_sq_मुक्त_wqebbs(sq) >= HINIC_MIN_TX_NUM_WQEBBS(sq)) अणु
		netdev_txq = netdev_get_tx_queue(txq->netdev, qp->q_id);

		__netअगर_tx_lock(netdev_txq, smp_processor_id());
		अगर (!netअगर_testing(nic_dev->netdev))
			netअगर_wake_subqueue(nic_dev->netdev, qp->q_id);

		__netअगर_tx_unlock(netdev_txq);

		u64_stats_update_begin(&txq->txq_stats.syncp);
		txq->txq_stats.tx_wake++;
		u64_stats_update_end(&txq->txq_stats.syncp);
	पूर्ण

	u64_stats_update_begin(&txq->txq_stats.syncp);
	txq->txq_stats.bytes += tx_bytes;
	txq->txq_stats.pkts += pkts;
	u64_stats_update_end(&txq->txq_stats.syncp);

	अगर (pkts < budget) अणु
		napi_complete(napi);
		अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर))
			hinic_hwdev_set_msix_state(nic_dev->hwdev,
						   sq->msix_entry,
						   HINIC_MSIX_ENABLE);

		वापस pkts;
	पूर्ण

	वापस budget;
पूर्ण

अटल irqवापस_t tx_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hinic_txq *txq = data;
	काष्ठा hinic_dev *nic_dev;

	nic_dev = netdev_priv(txq->netdev);

	अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर))
		/* Disable the पूर्णांकerrupt until napi will be completed */
		hinic_hwdev_set_msix_state(nic_dev->hwdev,
					   txq->sq->msix_entry,
					   HINIC_MSIX_DISABLE);

	hinic_hwdev_msix_cnt_set(nic_dev->hwdev, txq->sq->msix_entry);

	napi_schedule(&txq->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tx_request_irq(काष्ठा hinic_txq *txq)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(txq->netdev);
	काष्ठा hinic_msix_config पूर्णांकerrupt_info = अणु0पूर्ण;
	काष्ठा hinic_पूर्णांकr_coal_info *पूर्णांकr_coal = शून्य;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_sq *sq = txq->sq;
	काष्ठा hinic_qp *qp;
	पूर्णांक err;

	qp = container_of(sq, काष्ठा hinic_qp, sq);

	netअगर_napi_add(txq->netdev, &txq->napi, मुक्त_tx_poll, nic_dev->tx_weight);

	hinic_hwdev_msix_set(nic_dev->hwdev, sq->msix_entry,
			     TX_IRQ_NO_PENDING, TX_IRQ_NO_COALESC,
			     TX_IRQ_NO_LLI_TIMER, TX_IRQ_NO_CREDIT,
			     TX_IRQ_NO_RESEND_TIMER);

	पूर्णांकr_coal = &nic_dev->tx_पूर्णांकr_coalesce[qp->q_id];
	पूर्णांकerrupt_info.msix_index = sq->msix_entry;
	पूर्णांकerrupt_info.coalesce_समयr_cnt = पूर्णांकr_coal->coalesce_समयr_cfg;
	पूर्णांकerrupt_info.pending_cnt = पूर्णांकr_coal->pending_limt;
	पूर्णांकerrupt_info.resend_समयr_cnt = पूर्णांकr_coal->resend_समयr_cfg;

	err = hinic_set_पूर्णांकerrupt_cfg(hwdev, &पूर्णांकerrupt_info);
	अगर (err) अणु
		netअगर_err(nic_dev, drv, txq->netdev,
			  "Failed to set TX interrupt coalescing attribute\n");
		netअगर_napi_del(&txq->napi);
		वापस err;
	पूर्ण

	err = request_irq(sq->irq, tx_irq, 0, txq->irq_name, txq);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to request Tx irq\n");
		netअगर_napi_del(&txq->napi);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tx_मुक्त_irq(काष्ठा hinic_txq *txq)
अणु
	काष्ठा hinic_sq *sq = txq->sq;

	मुक्त_irq(sq->irq, txq);
	netअगर_napi_del(&txq->napi);
पूर्ण

/**
 * hinic_init_txq - Initialize the Tx Queue
 * @txq: Logical Tx Queue
 * @sq: Hardware Tx Queue to connect the Logical queue with
 * @netdev: network device to connect the Logical queue with
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_init_txq(काष्ठा hinic_txq *txq, काष्ठा hinic_sq *sq,
		   काष्ठा net_device *netdev)
अणु
	काष्ठा hinic_qp *qp = container_of(sq, काष्ठा hinic_qp, sq);
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	पूर्णांक err, irqname_len;
	माप_प्रकार sges_size;

	txq->netdev = netdev;
	txq->sq = sq;

	txq_stats_init(txq);

	txq->max_sges = HINIC_MAX_SQ_BUFDESCS;

	sges_size = txq->max_sges * माप(*txq->sges);
	txq->sges = devm_kzalloc(&netdev->dev, sges_size, GFP_KERNEL);
	अगर (!txq->sges)
		वापस -ENOMEM;

	sges_size = txq->max_sges * माप(*txq->मुक्त_sges);
	txq->मुक्त_sges = devm_kzalloc(&netdev->dev, sges_size, GFP_KERNEL);
	अगर (!txq->मुक्त_sges) अणु
		err = -ENOMEM;
		जाओ err_alloc_मुक्त_sges;
	पूर्ण

	irqname_len = snम_लिखो(शून्य, 0, "%s_txq%d", netdev->name, qp->q_id) + 1;
	txq->irq_name = devm_kzalloc(&netdev->dev, irqname_len, GFP_KERNEL);
	अगर (!txq->irq_name) अणु
		err = -ENOMEM;
		जाओ err_alloc_irqname;
	पूर्ण

	प्र_लिखो(txq->irq_name, "%s_txq%d", netdev->name, qp->q_id);

	err = hinic_hwdev_hw_ci_addr_set(hwdev, sq, CI_UPDATE_NO_PENDING,
					 CI_UPDATE_NO_COALESC);
	अगर (err)
		जाओ err_hw_ci;

	err = tx_request_irq(txq);
	अगर (err) अणु
		netdev_err(netdev, "Failed to request Tx irq\n");
		जाओ err_req_tx_irq;
	पूर्ण

	वापस 0;

err_req_tx_irq:
err_hw_ci:
	devm_kमुक्त(&netdev->dev, txq->irq_name);

err_alloc_irqname:
	devm_kमुक्त(&netdev->dev, txq->मुक्त_sges);

err_alloc_मुक्त_sges:
	devm_kमुक्त(&netdev->dev, txq->sges);
	वापस err;
पूर्ण

/**
 * hinic_clean_txq - Clean the Tx Queue
 * @txq: Logical Tx Queue
 **/
व्योम hinic_clean_txq(काष्ठा hinic_txq *txq)
अणु
	काष्ठा net_device *netdev = txq->netdev;

	tx_मुक्त_irq(txq);

	मुक्त_all_tx_skbs(txq);

	devm_kमुक्त(&netdev->dev, txq->irq_name);
	devm_kमुक्त(&netdev->dev, txq->मुक्त_sges);
	devm_kमुक्त(&netdev->dev, txq->sges);
पूर्ण
