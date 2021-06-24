<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <यंत्र/barrier.h>

#समावेश "hinic_common.h"
#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_wqe.h"
#समावेश "hinic_hw_wq.h"
#समावेश "hinic_hw_qp.h"
#समावेश "hinic_hw_dev.h"
#समावेश "hinic_rx.h"
#समावेश "hinic_dev.h"

#घोषणा RX_IRQ_NO_PENDING               0
#घोषणा RX_IRQ_NO_COALESC               0
#घोषणा RX_IRQ_NO_LLI_TIMER             0
#घोषणा RX_IRQ_NO_CREDIT                0
#घोषणा RX_IRQ_NO_RESEND_TIMER          0
#घोषणा HINIC_RX_BUFFER_WRITE           16

#घोषणा HINIC_RX_IPV6_PKT		7
#घोषणा LRO_PKT_HDR_LEN_IPV4		66
#घोषणा LRO_PKT_HDR_LEN_IPV6		86
#घोषणा LRO_REPLENISH_THLD		256

#घोषणा LRO_PKT_HDR_LEN(cqe)		\
	(HINIC_GET_RX_PKT_TYPE(be32_to_cpu((cqe)->offload_type)) == \
	 HINIC_RX_IPV6_PKT ? LRO_PKT_HDR_LEN_IPV6 : LRO_PKT_HDR_LEN_IPV4)

/**
 * hinic_rxq_clean_stats - Clean the statistics of specअगरic queue
 * @rxq: Logical Rx Queue
 **/
व्योम hinic_rxq_clean_stats(काष्ठा hinic_rxq *rxq)
अणु
	काष्ठा hinic_rxq_stats *rxq_stats = &rxq->rxq_stats;

	u64_stats_update_begin(&rxq_stats->syncp);
	rxq_stats->pkts  = 0;
	rxq_stats->bytes = 0;
	rxq_stats->errors = 0;
	rxq_stats->csum_errors = 0;
	rxq_stats->other_errors = 0;
	u64_stats_update_end(&rxq_stats->syncp);
पूर्ण

/**
 * hinic_rxq_get_stats - get statistics of Rx Queue
 * @rxq: Logical Rx Queue
 * @stats: वापस updated stats here
 **/
व्योम hinic_rxq_get_stats(काष्ठा hinic_rxq *rxq, काष्ठा hinic_rxq_stats *stats)
अणु
	काष्ठा hinic_rxq_stats *rxq_stats = &rxq->rxq_stats;
	अचिन्हित पूर्णांक start;

	u64_stats_update_begin(&stats->syncp);
	करो अणु
		start = u64_stats_fetch_begin(&rxq_stats->syncp);
		stats->pkts = rxq_stats->pkts;
		stats->bytes = rxq_stats->bytes;
		stats->errors = rxq_stats->csum_errors +
				rxq_stats->other_errors;
		stats->csum_errors = rxq_stats->csum_errors;
		stats->other_errors = rxq_stats->other_errors;
	पूर्ण जबतक (u64_stats_fetch_retry(&rxq_stats->syncp, start));
	u64_stats_update_end(&stats->syncp);
पूर्ण

/**
 * rxq_stats_init - Initialize the statistics of specअगरic queue
 * @rxq: Logical Rx Queue
 **/
अटल व्योम rxq_stats_init(काष्ठा hinic_rxq *rxq)
अणु
	काष्ठा hinic_rxq_stats *rxq_stats = &rxq->rxq_stats;

	u64_stats_init(&rxq_stats->syncp);
	hinic_rxq_clean_stats(rxq);
पूर्ण

अटल व्योम rx_csum(काष्ठा hinic_rxq *rxq, u32 status,
		    काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *netdev = rxq->netdev;
	u32 csum_err;

	csum_err = HINIC_RQ_CQE_STATUS_GET(status, CSUM_ERR);

	अगर (!(netdev->features & NETIF_F_RXCSUM))
		वापस;

	अगर (!csum_err) अणु
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण अन्यथा अणु
		अगर (!(csum_err & (HINIC_RX_CSUM_HW_CHECK_NONE |
			HINIC_RX_CSUM_IPSU_OTHER_ERR)))
			rxq->rxq_stats.csum_errors++;
		skb->ip_summed = CHECKSUM_NONE;
	पूर्ण
पूर्ण
/**
 * rx_alloc_skb - allocate skb and map it to dma address
 * @rxq: rx queue
 * @dma_addr: वापसed dma address क्रम the skb
 *
 * Return skb
 **/
अटल काष्ठा sk_buff *rx_alloc_skb(काष्ठा hinic_rxq *rxq,
				    dma_addr_t *dma_addr)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(rxq->netdev);
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा sk_buff *skb;
	dma_addr_t addr;
	पूर्णांक err;

	skb = netdev_alloc_skb_ip_align(rxq->netdev, rxq->rq->buf_sz);
	अगर (!skb)
		वापस शून्य;

	addr = dma_map_single(&pdev->dev, skb->data, rxq->rq->buf_sz,
			      DMA_FROM_DEVICE);
	err = dma_mapping_error(&pdev->dev, addr);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to map Rx DMA, err = %d\n", err);
		जाओ err_rx_map;
	पूर्ण

	*dma_addr = addr;
	वापस skb;

err_rx_map:
	dev_kमुक्त_skb_any(skb);
	वापस शून्य;
पूर्ण

/**
 * rx_unmap_skb - unmap the dma address of the skb
 * @rxq: rx queue
 * @dma_addr: dma address of the skb
 **/
अटल व्योम rx_unmap_skb(काष्ठा hinic_rxq *rxq, dma_addr_t dma_addr)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(rxq->netdev);
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;

	dma_unmap_single(&pdev->dev, dma_addr, rxq->rq->buf_sz,
			 DMA_FROM_DEVICE);
पूर्ण

/**
 * rx_मुक्त_skb - unmap and मुक्त skb
 * @rxq: rx queue
 * @skb: skb to मुक्त
 * @dma_addr: dma address of the skb
 **/
अटल व्योम rx_मुक्त_skb(काष्ठा hinic_rxq *rxq, काष्ठा sk_buff *skb,
			dma_addr_t dma_addr)
अणु
	rx_unmap_skb(rxq, dma_addr);
	dev_kमुक्त_skb_any(skb);
पूर्ण

/**
 * rx_alloc_pkts - allocate pkts in rx queue
 * @rxq: rx queue
 *
 * Return number of skbs allocated
 **/
अटल पूर्णांक rx_alloc_pkts(काष्ठा hinic_rxq *rxq)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(rxq->netdev);
	काष्ठा hinic_rq_wqe *rq_wqe;
	अचिन्हित पूर्णांक मुक्त_wqebbs;
	काष्ठा hinic_sge sge;
	dma_addr_t dma_addr;
	काष्ठा sk_buff *skb;
	u16 prod_idx;
	पूर्णांक i;

	मुक्त_wqebbs = hinic_get_rq_मुक्त_wqebbs(rxq->rq);

	/* Limit the allocation chunks */
	अगर (मुक्त_wqebbs > nic_dev->rx_weight)
		मुक्त_wqebbs = nic_dev->rx_weight;

	क्रम (i = 0; i < मुक्त_wqebbs; i++) अणु
		skb = rx_alloc_skb(rxq, &dma_addr);
		अगर (!skb)
			जाओ skb_out;

		hinic_set_sge(&sge, dma_addr, skb->len);

		rq_wqe = hinic_rq_get_wqe(rxq->rq, HINIC_RQ_WQE_SIZE,
					  &prod_idx);
		अगर (!rq_wqe) अणु
			rx_मुक्त_skb(rxq, skb, dma_addr);
			जाओ skb_out;
		पूर्ण

		hinic_rq_prepare_wqe(rxq->rq, prod_idx, rq_wqe, &sge);

		hinic_rq_ग_लिखो_wqe(rxq->rq, prod_idx, rq_wqe, skb);
	पूर्ण

skb_out:
	अगर (i) अणु
		wmb();  /* ग_लिखो all the wqes beक्रमe update PI */

		hinic_rq_update(rxq->rq, prod_idx);
	पूर्ण

	वापस i;
पूर्ण

/**
 * मुक्त_all_rx_skbs - मुक्त all skbs in rx queue
 * @rxq: rx queue
 **/
अटल व्योम मुक्त_all_rx_skbs(काष्ठा hinic_rxq *rxq)
अणु
	काष्ठा hinic_rq *rq = rxq->rq;
	काष्ठा hinic_hw_wqe *hw_wqe;
	काष्ठा hinic_sge sge;
	u16 ci;

	जबतक ((hw_wqe = hinic_पढ़ो_wqe(rq->wq, HINIC_RQ_WQE_SIZE, &ci))) अणु
		अगर (IS_ERR(hw_wqe))
			अवरोध;

		hinic_rq_get_sge(rq, &hw_wqe->rq_wqe, ci, &sge);

		hinic_put_wqe(rq->wq, HINIC_RQ_WQE_SIZE);

		rx_मुक्त_skb(rxq, rq->saved_skb[ci], hinic_sge_to_dma(&sge));
	पूर्ण
पूर्ण

/**
 * rx_recv_jumbo_pkt - Rx handler क्रम jumbo pkt
 * @rxq: rx queue
 * @head_skb: the first skb in the list
 * @left_pkt_len: left size of the pkt exclude head skb
 * @ci: consumer index
 *
 * Return number of wqes that used क्रम the left of the pkt
 **/
अटल पूर्णांक rx_recv_jumbo_pkt(काष्ठा hinic_rxq *rxq, काष्ठा sk_buff *head_skb,
			     अचिन्हित पूर्णांक left_pkt_len, u16 ci)
अणु
	काष्ठा sk_buff *skb, *curr_skb = head_skb;
	काष्ठा hinic_rq_wqe *rq_wqe;
	अचिन्हित पूर्णांक curr_len;
	काष्ठा hinic_sge sge;
	पूर्णांक num_wqes = 0;

	जबतक (left_pkt_len > 0) अणु
		rq_wqe = hinic_rq_पढ़ो_next_wqe(rxq->rq, HINIC_RQ_WQE_SIZE,
						&skb, &ci);

		num_wqes++;

		hinic_rq_get_sge(rxq->rq, rq_wqe, ci, &sge);

		rx_unmap_skb(rxq, hinic_sge_to_dma(&sge));

		prefetch(skb->data);

		curr_len = (left_pkt_len > HINIC_RX_BUF_SZ) ? HINIC_RX_BUF_SZ :
			    left_pkt_len;

		left_pkt_len -= curr_len;

		__skb_put(skb, curr_len);

		अगर (curr_skb == head_skb)
			skb_shinfo(head_skb)->frag_list = skb;
		अन्यथा
			curr_skb->next = skb;

		head_skb->len += skb->len;
		head_skb->data_len += skb->len;
		head_skb->truesize += skb->truesize;

		curr_skb = skb;
	पूर्ण

	वापस num_wqes;
पूर्ण

अटल व्योम hinic_copy_lp_data(काष्ठा hinic_dev *nic_dev,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *netdev = nic_dev->netdev;
	u8 *lb_buf = nic_dev->lb_test_rx_buf;
	पूर्णांक lb_len = nic_dev->lb_pkt_len;
	पूर्णांक pkt_offset, frag_len, i;
	व्योम *frag_data = शून्य;

	अगर (nic_dev->lb_test_rx_idx == LP_PKT_CNT) अणु
		nic_dev->lb_test_rx_idx = 0;
		netअगर_warn(nic_dev, drv, netdev, "Loopback test warning, receive too more test pkts\n");
	पूर्ण

	अगर (skb->len != nic_dev->lb_pkt_len) अणु
		netअगर_warn(nic_dev, drv, netdev, "Wrong packet length\n");
		nic_dev->lb_test_rx_idx++;
		वापस;
	पूर्ण

	pkt_offset = nic_dev->lb_test_rx_idx * lb_len;
	frag_len = (पूर्णांक)skb_headlen(skb);
	स_नकल(lb_buf + pkt_offset, skb->data, frag_len);
	pkt_offset += frag_len;
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		frag_data = skb_frag_address(&skb_shinfo(skb)->frags[i]);
		frag_len = (पूर्णांक)skb_frag_size(&skb_shinfo(skb)->frags[i]);
		स_नकल((lb_buf + pkt_offset), frag_data, frag_len);
		pkt_offset += frag_len;
	पूर्ण
	nic_dev->lb_test_rx_idx++;
पूर्ण

/**
 * rxq_recv - Rx handler
 * @rxq: rx queue
 * @budget: maximum pkts to process
 *
 * Return number of pkts received
 **/
अटल पूर्णांक rxq_recv(काष्ठा hinic_rxq *rxq, पूर्णांक budget)
अणु
	काष्ठा hinic_qp *qp = container_of(rxq->rq, काष्ठा hinic_qp, rq);
	काष्ठा net_device *netdev = rxq->netdev;
	u64 pkt_len = 0, rx_bytes = 0;
	काष्ठा hinic_rq *rq = rxq->rq;
	काष्ठा hinic_rq_wqe *rq_wqe;
	काष्ठा hinic_dev *nic_dev;
	अचिन्हित पूर्णांक मुक्त_wqebbs;
	काष्ठा hinic_rq_cqe *cqe;
	पूर्णांक num_wqes, pkts = 0;
	काष्ठा hinic_sge sge;
	अचिन्हित पूर्णांक status;
	काष्ठा sk_buff *skb;
	u32 offload_type;
	u16 ci, num_lro;
	u16 num_wqe = 0;
	u32 vlan_len;
	u16 vid;

	nic_dev = netdev_priv(netdev);

	जबतक (pkts < budget) अणु
		num_wqes = 0;

		rq_wqe = hinic_rq_पढ़ो_wqe(rxq->rq, HINIC_RQ_WQE_SIZE, &skb,
					   &ci);
		अगर (!rq_wqe)
			अवरोध;

		/* make sure we पढ़ो rx_करोne beक्रमe packet length */
		dma_rmb();

		cqe = rq->cqe[ci];
		status =  be32_to_cpu(cqe->status);
		hinic_rq_get_sge(rxq->rq, rq_wqe, ci, &sge);

		rx_unmap_skb(rxq, hinic_sge_to_dma(&sge));

		rx_csum(rxq, status, skb);

		prefetch(skb->data);

		pkt_len = sge.len;

		अगर (pkt_len <= HINIC_RX_BUF_SZ) अणु
			__skb_put(skb, pkt_len);
		पूर्ण अन्यथा अणु
			__skb_put(skb, HINIC_RX_BUF_SZ);
			num_wqes = rx_recv_jumbo_pkt(rxq, skb, pkt_len -
						     HINIC_RX_BUF_SZ, ci);
		पूर्ण

		hinic_rq_put_wqe(rq, ci,
				 (num_wqes + 1) * HINIC_RQ_WQE_SIZE);

		offload_type = be32_to_cpu(cqe->offload_type);
		vlan_len = be32_to_cpu(cqe->len);
		अगर ((netdev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
		    HINIC_GET_RX_VLAN_OFFLOAD_EN(offload_type)) अणु
			vid = HINIC_GET_RX_VLAN_TAG(vlan_len);
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
		पूर्ण

		अगर (unlikely(nic_dev->flags & HINIC_LP_TEST))
			hinic_copy_lp_data(nic_dev, skb);

		skb_record_rx_queue(skb, qp->q_id);
		skb->protocol = eth_type_trans(skb, rxq->netdev);

		napi_gro_receive(&rxq->napi, skb);

		pkts++;
		rx_bytes += pkt_len;

		num_lro = HINIC_GET_RX_NUM_LRO(status);
		अगर (num_lro) अणु
			rx_bytes += ((num_lro - 1) *
				     LRO_PKT_HDR_LEN(cqe));

			num_wqe +=
			(u16)(pkt_len >> rxq->rx_buff_shअगरt) +
			((pkt_len & (rxq->buf_len - 1)) ? 1 : 0);
		पूर्ण

		cqe->status = 0;

		अगर (num_wqe >= LRO_REPLENISH_THLD)
			अवरोध;
	पूर्ण

	मुक्त_wqebbs = hinic_get_rq_मुक्त_wqebbs(rxq->rq);
	अगर (मुक्त_wqebbs > HINIC_RX_BUFFER_WRITE)
		rx_alloc_pkts(rxq);

	u64_stats_update_begin(&rxq->rxq_stats.syncp);
	rxq->rxq_stats.pkts += pkts;
	rxq->rxq_stats.bytes += rx_bytes;
	u64_stats_update_end(&rxq->rxq_stats.syncp);

	वापस pkts;
पूर्ण

अटल पूर्णांक rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा hinic_rxq *rxq = container_of(napi, काष्ठा hinic_rxq, napi);
	काष्ठा hinic_dev *nic_dev = netdev_priv(rxq->netdev);
	काष्ठा hinic_rq *rq = rxq->rq;
	पूर्णांक pkts;

	pkts = rxq_recv(rxq, budget);
	अगर (pkts >= budget)
		वापस budget;

	napi_complete(napi);

	अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर))
		hinic_hwdev_set_msix_state(nic_dev->hwdev,
					   rq->msix_entry,
					   HINIC_MSIX_ENABLE);

	वापस pkts;
पूर्ण

अटल व्योम rx_add_napi(काष्ठा hinic_rxq *rxq)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(rxq->netdev);

	netअगर_napi_add(rxq->netdev, &rxq->napi, rx_poll, nic_dev->rx_weight);
	napi_enable(&rxq->napi);
पूर्ण

अटल व्योम rx_del_napi(काष्ठा hinic_rxq *rxq)
अणु
	napi_disable(&rxq->napi);
	netअगर_napi_del(&rxq->napi);
पूर्ण

अटल irqवापस_t rx_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hinic_rxq *rxq = (काष्ठा hinic_rxq *)data;
	काष्ठा hinic_rq *rq = rxq->rq;
	काष्ठा hinic_dev *nic_dev;

	/* Disable the पूर्णांकerrupt until napi will be completed */
	nic_dev = netdev_priv(rxq->netdev);
	अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर))
		hinic_hwdev_set_msix_state(nic_dev->hwdev,
					   rq->msix_entry,
					   HINIC_MSIX_DISABLE);

	nic_dev = netdev_priv(rxq->netdev);
	hinic_hwdev_msix_cnt_set(nic_dev->hwdev, rq->msix_entry);

	napi_schedule(&rxq->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rx_request_irq(काष्ठा hinic_rxq *rxq)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(rxq->netdev);
	काष्ठा hinic_msix_config पूर्णांकerrupt_info = अणु0पूर्ण;
	काष्ठा hinic_पूर्णांकr_coal_info *पूर्णांकr_coal = शून्य;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_rq *rq = rxq->rq;
	काष्ठा hinic_qp *qp;
	पूर्णांक err;

	qp = container_of(rq, काष्ठा hinic_qp, rq);

	rx_add_napi(rxq);

	hinic_hwdev_msix_set(hwdev, rq->msix_entry,
			     RX_IRQ_NO_PENDING, RX_IRQ_NO_COALESC,
			     RX_IRQ_NO_LLI_TIMER, RX_IRQ_NO_CREDIT,
			     RX_IRQ_NO_RESEND_TIMER);

	पूर्णांकr_coal = &nic_dev->rx_पूर्णांकr_coalesce[qp->q_id];
	पूर्णांकerrupt_info.msix_index = rq->msix_entry;
	पूर्णांकerrupt_info.coalesce_समयr_cnt = पूर्णांकr_coal->coalesce_समयr_cfg;
	पूर्णांकerrupt_info.pending_cnt = पूर्णांकr_coal->pending_limt;
	पूर्णांकerrupt_info.resend_समयr_cnt = पूर्णांकr_coal->resend_समयr_cfg;

	err = hinic_set_पूर्णांकerrupt_cfg(hwdev, &पूर्णांकerrupt_info);
	अगर (err) अणु
		netअगर_err(nic_dev, drv, rxq->netdev,
			  "Failed to set RX interrupt coalescing attribute\n");
		जाओ err_req_irq;
	पूर्ण

	err = request_irq(rq->irq, rx_irq, 0, rxq->irq_name, rxq);
	अगर (err)
		जाओ err_req_irq;

	cpumask_set_cpu(qp->q_id % num_online_cpus(), &rq->affinity_mask);
	err = irq_set_affinity_hपूर्णांक(rq->irq, &rq->affinity_mask);
	अगर (err)
		जाओ err_irq_affinity;

	वापस 0;

err_irq_affinity:
	मुक्त_irq(rq->irq, rxq);
err_req_irq:
	rx_del_napi(rxq);
	वापस err;
पूर्ण

अटल व्योम rx_मुक्त_irq(काष्ठा hinic_rxq *rxq)
अणु
	काष्ठा hinic_rq *rq = rxq->rq;

	irq_set_affinity_hपूर्णांक(rq->irq, शून्य);
	मुक्त_irq(rq->irq, rxq);
	rx_del_napi(rxq);
पूर्ण

/**
 * hinic_init_rxq - Initialize the Rx Queue
 * @rxq: Logical Rx Queue
 * @rq: Hardware Rx Queue to connect the Logical queue with
 * @netdev: network device to connect the Logical queue with
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_init_rxq(काष्ठा hinic_rxq *rxq, काष्ठा hinic_rq *rq,
		   काष्ठा net_device *netdev)
अणु
	काष्ठा hinic_qp *qp = container_of(rq, काष्ठा hinic_qp, rq);
	पूर्णांक err, pkts;

	rxq->netdev = netdev;
	rxq->rq = rq;
	rxq->buf_len = HINIC_RX_BUF_SZ;
	rxq->rx_buff_shअगरt = ilog2(HINIC_RX_BUF_SZ);

	rxq_stats_init(rxq);

	rxq->irq_name = devm_kaप्र_लिखो(&netdev->dev, GFP_KERNEL,
				       "%s_rxq%d", netdev->name, qp->q_id);
	अगर (!rxq->irq_name)
		वापस -ENOMEM;

	pkts = rx_alloc_pkts(rxq);
	अगर (!pkts) अणु
		err = -ENOMEM;
		जाओ err_rx_pkts;
	पूर्ण

	err = rx_request_irq(rxq);
	अगर (err) अणु
		netdev_err(netdev, "Failed to request Rx irq\n");
		जाओ err_req_rx_irq;
	पूर्ण

	वापस 0;

err_req_rx_irq:
err_rx_pkts:
	मुक्त_all_rx_skbs(rxq);
	devm_kमुक्त(&netdev->dev, rxq->irq_name);
	वापस err;
पूर्ण

/**
 * hinic_clean_rxq - Clean the Rx Queue
 * @rxq: Logical Rx Queue
 **/
व्योम hinic_clean_rxq(काष्ठा hinic_rxq *rxq)
अणु
	काष्ठा net_device *netdev = rxq->netdev;

	rx_मुक्त_irq(rxq);

	मुक्त_all_rx_skbs(rxq);
	devm_kमुक्त(&netdev->dev, rxq->irq_name);
पूर्ण
