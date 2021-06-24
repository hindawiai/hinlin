<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Applied Micro X-Gene SoC Ethernet v2 Driver
 *
 * Copyright (c) 2017, Applied Micro Circuits Corporation
 * Author(s): Iyappan Subramanian <isubramanian@apm.com>
 *	      Keyur Chudgar <kchudgar@apm.com>
 */

#समावेश "main.h"

अटल स्थिर काष्ठा acpi_device_id xge_acpi_match[];

अटल पूर्णांक xge_get_resources(काष्ठा xge_pdata *pdata)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा net_device *ndev;
	पूर्णांक phy_mode, ret = 0;
	काष्ठा resource *res;
	काष्ठा device *dev;

	pdev = pdata->pdev;
	dev = &pdev->dev;
	ndev = pdata->ndev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "Resource enet_csr not defined\n");
		वापस -ENODEV;
	पूर्ण

	pdata->resources.base_addr = devm_ioremap(dev, res->start,
						  resource_size(res));
	अगर (!pdata->resources.base_addr) अणु
		dev_err(dev, "Unable to retrieve ENET Port CSR region\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (!device_get_mac_address(dev, ndev->dev_addr, ETH_ALEN))
		eth_hw_addr_अक्रमom(ndev);

	स_नकल(ndev->perm_addr, ndev->dev_addr, ndev->addr_len);

	phy_mode = device_get_phy_mode(dev);
	अगर (phy_mode < 0) अणु
		dev_err(dev, "Unable to get phy-connection-type\n");
		वापस phy_mode;
	पूर्ण
	pdata->resources.phy_mode = phy_mode;

	अगर (pdata->resources.phy_mode != PHY_INTERFACE_MODE_RGMII) अणु
		dev_err(dev, "Incorrect phy-connection-type specified\n");
		वापस -ENODEV;
	पूर्ण

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;
	pdata->resources.irq = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक xge_refill_buffers(काष्ठा net_device *ndev, u32 nbuf)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा xge_desc_ring *ring = pdata->rx_ring;
	स्थिर u8 slots = XGENE_ENET_NUM_DESC - 1;
	काष्ठा device *dev = &pdata->pdev->dev;
	काष्ठा xge_raw_desc *raw_desc;
	u64 addr_lo, addr_hi;
	u8 tail = ring->tail;
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;
	u16 len;
	पूर्णांक i;

	क्रम (i = 0; i < nbuf; i++) अणु
		raw_desc = &ring->raw_desc[tail];

		len = XGENE_ENET_STD_MTU;
		skb = netdev_alloc_skb(ndev, len);
		अगर (unlikely(!skb))
			वापस -ENOMEM;

		dma_addr = dma_map_single(dev, skb->data, len, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(dev, dma_addr)) अणु
			netdev_err(ndev, "DMA mapping error\n");
			dev_kमुक्त_skb_any(skb);
			वापस -EINVAL;
		पूर्ण

		ring->pkt_info[tail].skb = skb;
		ring->pkt_info[tail].dma_addr = dma_addr;

		addr_hi = GET_BITS(NEXT_DESC_ADDRH, le64_to_cpu(raw_desc->m1));
		addr_lo = GET_BITS(NEXT_DESC_ADDRL, le64_to_cpu(raw_desc->m1));
		raw_desc->m1 = cpu_to_le64(SET_BITS(NEXT_DESC_ADDRL, addr_lo) |
					   SET_BITS(NEXT_DESC_ADDRH, addr_hi) |
					   SET_BITS(PKT_ADDRH,
						    upper_32_bits(dma_addr)));

		dma_wmb();
		raw_desc->m0 = cpu_to_le64(SET_BITS(PKT_ADDRL, dma_addr) |
					   SET_BITS(E, 1));
		tail = (tail + 1) & slots;
	पूर्ण

	ring->tail = tail;

	वापस 0;
पूर्ण

अटल पूर्णांक xge_init_hw(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	पूर्णांक ret;

	ret = xge_port_reset(ndev);
	अगर (ret)
		वापस ret;

	xge_port_init(ndev);
	pdata->nbufs = NUM_BUFS;

	वापस 0;
पूर्ण

अटल irqवापस_t xge_irq(स्थिर पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xge_pdata *pdata = data;

	अगर (napi_schedule_prep(&pdata->napi)) अणु
		xge_पूर्णांकr_disable(pdata);
		__napi_schedule(&pdata->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xge_request_irq(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	पूर्णांक ret;

	snम_लिखो(pdata->irq_name, IRQ_ID_SIZE, "%s", ndev->name);

	ret = request_irq(pdata->resources.irq, xge_irq, 0, pdata->irq_name,
			  pdata);
	अगर (ret)
		netdev_err(ndev, "Failed to request irq %s\n", pdata->irq_name);

	वापस ret;
पूर्ण

अटल व्योम xge_मुक्त_irq(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);

	मुक्त_irq(pdata->resources.irq, pdata);
पूर्ण

अटल bool is_tx_slot_available(काष्ठा xge_raw_desc *raw_desc)
अणु
	अगर (GET_BITS(E, le64_to_cpu(raw_desc->m0)) &&
	    (GET_BITS(PKT_SIZE, le64_to_cpu(raw_desc->m0)) == SLOT_EMPTY))
		वापस true;

	वापस false;
पूर्ण

अटल netdev_tx_t xge_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा device *dev = &pdata->pdev->dev;
	काष्ठा xge_desc_ring *tx_ring;
	काष्ठा xge_raw_desc *raw_desc;
	अटल dma_addr_t dma_addr;
	u64 addr_lo, addr_hi;
	व्योम *pkt_buf;
	u8 tail;
	u16 len;

	tx_ring = pdata->tx_ring;
	tail = tx_ring->tail;
	len = skb_headlen(skb);
	raw_desc = &tx_ring->raw_desc[tail];

	अगर (!is_tx_slot_available(raw_desc)) अणु
		netअगर_stop_queue(ndev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* Packet buffers should be 64B aligned */
	pkt_buf = dma_alloc_coherent(dev, XGENE_ENET_STD_MTU, &dma_addr,
				     GFP_ATOMIC);
	अगर (unlikely(!pkt_buf)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	स_नकल(pkt_buf, skb->data, len);

	addr_hi = GET_BITS(NEXT_DESC_ADDRH, le64_to_cpu(raw_desc->m1));
	addr_lo = GET_BITS(NEXT_DESC_ADDRL, le64_to_cpu(raw_desc->m1));
	raw_desc->m1 = cpu_to_le64(SET_BITS(NEXT_DESC_ADDRL, addr_lo) |
				   SET_BITS(NEXT_DESC_ADDRH, addr_hi) |
				   SET_BITS(PKT_ADDRH,
					    upper_32_bits(dma_addr)));

	tx_ring->pkt_info[tail].skb = skb;
	tx_ring->pkt_info[tail].dma_addr = dma_addr;
	tx_ring->pkt_info[tail].pkt_buf = pkt_buf;

	dma_wmb();

	raw_desc->m0 = cpu_to_le64(SET_BITS(PKT_ADDRL, dma_addr) |
				   SET_BITS(PKT_SIZE, len) |
				   SET_BITS(E, 0));
	skb_tx_बारtamp(skb);
	xge_wr_csr(pdata, DMATXCTRL, 1);

	tx_ring->tail = (tail + 1) & (XGENE_ENET_NUM_DESC - 1);

	वापस NETDEV_TX_OK;
पूर्ण

अटल bool is_tx_hw_करोne(काष्ठा xge_raw_desc *raw_desc)
अणु
	अगर (GET_BITS(E, le64_to_cpu(raw_desc->m0)) &&
	    !GET_BITS(PKT_SIZE, le64_to_cpu(raw_desc->m0)))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम xge_txc_poll(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा device *dev = &pdata->pdev->dev;
	काष्ठा xge_desc_ring *tx_ring;
	काष्ठा xge_raw_desc *raw_desc;
	dma_addr_t dma_addr;
	काष्ठा sk_buff *skb;
	व्योम *pkt_buf;
	u32 data;
	u8 head;

	tx_ring = pdata->tx_ring;
	head = tx_ring->head;

	data = xge_rd_csr(pdata, DMATXSTATUS);
	अगर (!GET_BITS(TXPKTCOUNT, data))
		वापस;

	जबतक (1) अणु
		raw_desc = &tx_ring->raw_desc[head];

		अगर (!is_tx_hw_करोne(raw_desc))
			अवरोध;

		dma_rmb();

		skb = tx_ring->pkt_info[head].skb;
		dma_addr = tx_ring->pkt_info[head].dma_addr;
		pkt_buf = tx_ring->pkt_info[head].pkt_buf;
		pdata->stats.tx_packets++;
		pdata->stats.tx_bytes += skb->len;
		dma_मुक्त_coherent(dev, XGENE_ENET_STD_MTU, pkt_buf, dma_addr);
		dev_kमुक्त_skb_any(skb);

		/* clear pktstart address and pktsize */
		raw_desc->m0 = cpu_to_le64(SET_BITS(E, 1) |
					   SET_BITS(PKT_SIZE, SLOT_EMPTY));
		xge_wr_csr(pdata, DMATXSTATUS, 1);

		head = (head + 1) & (XGENE_ENET_NUM_DESC - 1);
	पूर्ण

	अगर (netअगर_queue_stopped(ndev))
		netअगर_wake_queue(ndev);

	tx_ring->head = head;
पूर्ण

अटल पूर्णांक xge_rx_poll(काष्ठा net_device *ndev, अचिन्हित पूर्णांक budget)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा device *dev = &pdata->pdev->dev;
	काष्ठा xge_desc_ring *rx_ring;
	काष्ठा xge_raw_desc *raw_desc;
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;
	पूर्णांक processed = 0;
	u8 head, rx_error;
	पूर्णांक i, ret;
	u32 data;
	u16 len;

	rx_ring = pdata->rx_ring;
	head = rx_ring->head;

	data = xge_rd_csr(pdata, DMARXSTATUS);
	अगर (!GET_BITS(RXPKTCOUNT, data))
		वापस 0;

	क्रम (i = 0; i < budget; i++) अणु
		raw_desc = &rx_ring->raw_desc[head];

		अगर (GET_BITS(E, le64_to_cpu(raw_desc->m0)))
			अवरोध;

		dma_rmb();

		skb = rx_ring->pkt_info[head].skb;
		rx_ring->pkt_info[head].skb = शून्य;
		dma_addr = rx_ring->pkt_info[head].dma_addr;
		len = GET_BITS(PKT_SIZE, le64_to_cpu(raw_desc->m0));
		dma_unmap_single(dev, dma_addr, XGENE_ENET_STD_MTU,
				 DMA_FROM_DEVICE);

		rx_error = GET_BITS(D, le64_to_cpu(raw_desc->m2));
		अगर (unlikely(rx_error)) अणु
			pdata->stats.rx_errors++;
			dev_kमुक्त_skb_any(skb);
			जाओ out;
		पूर्ण

		skb_put(skb, len);
		skb->protocol = eth_type_trans(skb, ndev);

		pdata->stats.rx_packets++;
		pdata->stats.rx_bytes += len;
		napi_gro_receive(&pdata->napi, skb);
out:
		ret = xge_refill_buffers(ndev, 1);
		xge_wr_csr(pdata, DMARXSTATUS, 1);
		xge_wr_csr(pdata, DMARXCTRL, 1);

		अगर (ret)
			अवरोध;

		head = (head + 1) & (XGENE_ENET_NUM_DESC - 1);
		processed++;
	पूर्ण

	rx_ring->head = head;

	वापस processed;
पूर्ण

अटल व्योम xge_delete_desc_ring(काष्ठा net_device *ndev,
				 काष्ठा xge_desc_ring *ring)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा device *dev = &pdata->pdev->dev;
	u16 size;

	अगर (!ring)
		वापस;

	size = XGENE_ENET_DESC_SIZE * XGENE_ENET_NUM_DESC;
	अगर (ring->desc_addr)
		dma_मुक्त_coherent(dev, size, ring->desc_addr, ring->dma_addr);

	kमुक्त(ring->pkt_info);
	kमुक्त(ring);
पूर्ण

अटल व्योम xge_मुक्त_buffers(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा xge_desc_ring *ring = pdata->rx_ring;
	काष्ठा device *dev = &pdata->pdev->dev;
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;
	पूर्णांक i;

	क्रम (i = 0; i < XGENE_ENET_NUM_DESC; i++) अणु
		skb = ring->pkt_info[i].skb;
		dma_addr = ring->pkt_info[i].dma_addr;

		अगर (!skb)
			जारी;

		dma_unmap_single(dev, dma_addr, XGENE_ENET_STD_MTU,
				 DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम xge_delete_desc_rings(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);

	xge_txc_poll(ndev);
	xge_delete_desc_ring(ndev, pdata->tx_ring);

	xge_rx_poll(ndev, 64);
	xge_मुक्त_buffers(ndev);
	xge_delete_desc_ring(ndev, pdata->rx_ring);
पूर्ण

अटल काष्ठा xge_desc_ring *xge_create_desc_ring(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा device *dev = &pdata->pdev->dev;
	काष्ठा xge_desc_ring *ring;
	u16 size;

	ring = kzalloc(माप(*ring), GFP_KERNEL);
	अगर (!ring)
		वापस शून्य;

	ring->ndev = ndev;

	size = XGENE_ENET_DESC_SIZE * XGENE_ENET_NUM_DESC;
	ring->desc_addr = dma_alloc_coherent(dev, size, &ring->dma_addr,
					     GFP_KERNEL);
	अगर (!ring->desc_addr)
		जाओ err;

	ring->pkt_info = kसुस्मृति(XGENE_ENET_NUM_DESC, माप(*ring->pkt_info),
				 GFP_KERNEL);
	अगर (!ring->pkt_info)
		जाओ err;

	xge_setup_desc(ring);

	वापस ring;

err:
	xge_delete_desc_ring(ndev, ring);

	वापस शून्य;
पूर्ण

अटल पूर्णांक xge_create_desc_rings(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा xge_desc_ring *ring;
	पूर्णांक ret;

	/* create tx ring */
	ring = xge_create_desc_ring(ndev);
	अगर (!ring)
		जाओ err;

	pdata->tx_ring = ring;
	xge_update_tx_desc_addr(pdata);

	/* create rx ring */
	ring = xge_create_desc_ring(ndev);
	अगर (!ring)
		जाओ err;

	pdata->rx_ring = ring;
	xge_update_rx_desc_addr(pdata);

	ret = xge_refill_buffers(ndev, XGENE_ENET_NUM_DESC);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	xge_delete_desc_rings(ndev);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक xge_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	पूर्णांक ret;

	ret = xge_create_desc_rings(ndev);
	अगर (ret)
		वापस ret;

	napi_enable(&pdata->napi);
	ret = xge_request_irq(ndev);
	अगर (ret)
		वापस ret;

	xge_पूर्णांकr_enable(pdata);
	xge_wr_csr(pdata, DMARXCTRL, 1);

	phy_start(ndev->phydev);
	xge_mac_enable(pdata);
	netअगर_start_queue(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक xge_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);

	netअगर_stop_queue(ndev);
	xge_mac_disable(pdata);
	phy_stop(ndev->phydev);

	xge_पूर्णांकr_disable(pdata);
	xge_मुक्त_irq(ndev);
	napi_disable(&pdata->napi);
	xge_delete_desc_rings(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक xge_napi(काष्ठा napi_काष्ठा *napi, स्थिर पूर्णांक budget)
अणु
	काष्ठा net_device *ndev = napi->dev;
	काष्ठा xge_pdata *pdata;
	पूर्णांक processed;

	pdata = netdev_priv(ndev);

	xge_txc_poll(ndev);
	processed = xge_rx_poll(ndev, budget);

	अगर (processed < budget) अणु
		napi_complete_करोne(napi, processed);
		xge_पूर्णांकr_enable(pdata);
	पूर्ण

	वापस processed;
पूर्ण

अटल पूर्णांक xge_set_mac_addr(काष्ठा net_device *ndev, व्योम *addr)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	पूर्णांक ret;

	ret = eth_mac_addr(ndev, addr);
	अगर (ret)
		वापस ret;

	xge_mac_set_station_addr(pdata);

	वापस 0;
पूर्ण

अटल bool is_tx_pending(काष्ठा xge_raw_desc *raw_desc)
अणु
	अगर (!GET_BITS(E, le64_to_cpu(raw_desc->m0)))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम xge_मुक्त_pending_skb(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा device *dev = &pdata->pdev->dev;
	काष्ठा xge_desc_ring *tx_ring;
	काष्ठा xge_raw_desc *raw_desc;
	dma_addr_t dma_addr;
	काष्ठा sk_buff *skb;
	व्योम *pkt_buf;
	पूर्णांक i;

	tx_ring = pdata->tx_ring;

	क्रम (i = 0; i < XGENE_ENET_NUM_DESC; i++) अणु
		raw_desc = &tx_ring->raw_desc[i];

		अगर (!is_tx_pending(raw_desc))
			जारी;

		skb = tx_ring->pkt_info[i].skb;
		dma_addr = tx_ring->pkt_info[i].dma_addr;
		pkt_buf = tx_ring->pkt_info[i].pkt_buf;
		dma_मुक्त_coherent(dev, XGENE_ENET_STD_MTU, pkt_buf, dma_addr);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम xge_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);

	rtnl_lock();

	अगर (!netअगर_running(ndev))
		जाओ out;

	netअगर_stop_queue(ndev);
	xge_पूर्णांकr_disable(pdata);
	napi_disable(&pdata->napi);

	xge_wr_csr(pdata, DMATXCTRL, 0);
	xge_txc_poll(ndev);
	xge_मुक्त_pending_skb(ndev);
	xge_wr_csr(pdata, DMATXSTATUS, ~0U);

	xge_setup_desc(pdata->tx_ring);
	xge_update_tx_desc_addr(pdata);
	xge_mac_init(pdata);

	napi_enable(&pdata->napi);
	xge_पूर्णांकr_enable(pdata);
	xge_mac_enable(pdata);
	netअगर_start_queue(ndev);

out:
	rtnl_unlock();
पूर्ण

अटल व्योम xge_get_stats64(काष्ठा net_device *ndev,
			    काष्ठा rtnl_link_stats64 *storage)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा xge_stats *stats = &pdata->stats;

	storage->tx_packets += stats->tx_packets;
	storage->tx_bytes += stats->tx_bytes;

	storage->rx_packets += stats->rx_packets;
	storage->rx_bytes += stats->rx_bytes;
	storage->rx_errors += stats->rx_errors;
पूर्ण

अटल स्थिर काष्ठा net_device_ops xgene_ndev_ops = अणु
	.nकरो_खोलो = xge_खोलो,
	.nकरो_stop = xge_बंद,
	.nकरो_start_xmit = xge_start_xmit,
	.nकरो_set_mac_address = xge_set_mac_addr,
	.nकरो_tx_समयout = xge_समयout,
	.nकरो_get_stats64 = xge_get_stats64,
पूर्ण;

अटल पूर्णांक xge_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा net_device *ndev;
	काष्ठा xge_pdata *pdata;
	पूर्णांक ret;

	ndev = alloc_etherdev(माप(*pdata));
	अगर (!ndev)
		वापस -ENOMEM;

	pdata = netdev_priv(ndev);

	pdata->pdev = pdev;
	pdata->ndev = ndev;
	SET_NETDEV_DEV(ndev, dev);
	platक्रमm_set_drvdata(pdev, pdata);
	ndev->netdev_ops = &xgene_ndev_ops;

	ndev->features |= NETIF_F_GSO |
			  NETIF_F_GRO;

	ret = xge_get_resources(pdata);
	अगर (ret)
		जाओ err;

	ndev->hw_features = ndev->features;
	xge_set_ethtool_ops(ndev);

	ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(64));
	अगर (ret) अणु
		netdev_err(ndev, "No usable DMA configuration\n");
		जाओ err;
	पूर्ण

	ret = xge_init_hw(ndev);
	अगर (ret)
		जाओ err;

	ret = xge_mdio_config(ndev);
	अगर (ret)
		जाओ err;

	netअगर_napi_add(ndev, &pdata->napi, xge_napi, NAPI_POLL_WEIGHT);

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		netdev_err(ndev, "Failed to register netdev\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	मुक्त_netdev(ndev);

	वापस ret;
पूर्ण

अटल पूर्णांक xge_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xge_pdata *pdata;
	काष्ठा net_device *ndev;

	pdata = platक्रमm_get_drvdata(pdev);
	ndev = pdata->ndev;

	rtnl_lock();
	अगर (netअगर_running(ndev))
		dev_बंद(ndev);
	rtnl_unlock();

	xge_mdio_हटाओ(ndev);
	unरेजिस्टर_netdev(ndev);
	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

अटल व्योम xge_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xge_pdata *pdata;

	pdata = platक्रमm_get_drvdata(pdev);
	अगर (!pdata)
		वापस;

	अगर (!pdata->ndev)
		वापस;

	xge_हटाओ(pdev);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id xge_acpi_match[] = अणु
	अणु "APMC0D80" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, xge_acpi_match);

अटल काष्ठा platक्रमm_driver xge_driver = अणु
	.driver = अणु
		   .name = "xgene-enet-v2",
		   .acpi_match_table = ACPI_PTR(xge_acpi_match),
	पूर्ण,
	.probe = xge_probe,
	.हटाओ = xge_हटाओ,
	.shutकरोwn = xge_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(xge_driver);

MODULE_DESCRIPTION("APM X-Gene SoC Ethernet v2 driver");
MODULE_AUTHOR("Iyappan Subramanian <isubramanian@apm.com>");
MODULE_LICENSE("GPL");
