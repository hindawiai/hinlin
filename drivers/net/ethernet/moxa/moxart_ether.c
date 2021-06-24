<शैली गुरु>
/* MOXA ART Ethernet (RTL8201CP) driver.
 *
 * Copyright (C) 2013 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmail.com>
 *
 * Based on code from
 * Moxa Technology Co., Ltd. <www.moxa.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/crc32.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/circ_buf.h>

#समावेश "moxart_ether.h"

अटल अंतरभूत व्योम moxart_desc_ग_लिखो(u32 data, u32 *desc)
अणु
	*desc = cpu_to_le32(data);
पूर्ण

अटल अंतरभूत u32 moxart_desc_पढ़ो(u32 *desc)
अणु
	वापस le32_to_cpu(*desc);
पूर्ण

अटल अंतरभूत व्योम moxart_emac_ग_लिखो(काष्ठा net_device *ndev,
				     अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ value)
अणु
	काष्ठा moxart_mac_priv_t *priv = netdev_priv(ndev);

	ग_लिखोl(value, priv->base + reg);
पूर्ण

अटल व्योम moxart_update_mac_address(काष्ठा net_device *ndev)
अणु
	moxart_emac_ग_लिखो(ndev, REG_MAC_MS_ADDRESS,
			  ((ndev->dev_addr[0] << 8) | (ndev->dev_addr[1])));
	moxart_emac_ग_लिखो(ndev, REG_MAC_MS_ADDRESS + 4,
			  ((ndev->dev_addr[2] << 24) |
			   (ndev->dev_addr[3] << 16) |
			   (ndev->dev_addr[4] << 8) |
			   (ndev->dev_addr[5])));
पूर्ण

अटल पूर्णांक moxart_set_mac_address(काष्ठा net_device *ndev, व्योम *addr)
अणु
	काष्ठा sockaddr *address = addr;

	अगर (!is_valid_ether_addr(address->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(ndev->dev_addr, address->sa_data, ndev->addr_len);
	moxart_update_mac_address(ndev);

	वापस 0;
पूर्ण

अटल व्योम moxart_mac_मुक्त_memory(काष्ठा net_device *ndev)
अणु
	काष्ठा moxart_mac_priv_t *priv = netdev_priv(ndev);
	पूर्णांक i;

	क्रम (i = 0; i < RX_DESC_NUM; i++)
		dma_unmap_single(&ndev->dev, priv->rx_mapping[i],
				 priv->rx_buf_size, DMA_FROM_DEVICE);

	अगर (priv->tx_desc_base)
		dma_मुक्त_coherent(&priv->pdev->dev,
				  TX_REG_DESC_SIZE * TX_DESC_NUM,
				  priv->tx_desc_base, priv->tx_base);

	अगर (priv->rx_desc_base)
		dma_मुक्त_coherent(&priv->pdev->dev,
				  RX_REG_DESC_SIZE * RX_DESC_NUM,
				  priv->rx_desc_base, priv->rx_base);

	kमुक्त(priv->tx_buf_base);
	kमुक्त(priv->rx_buf_base);
पूर्ण

अटल व्योम moxart_mac_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा moxart_mac_priv_t *priv = netdev_priv(ndev);

	ग_लिखोl(SW_RST, priv->base + REG_MAC_CTRL);
	जबतक (पढ़ोl(priv->base + REG_MAC_CTRL) & SW_RST)
		mdelay(10);

	ग_लिखोl(0, priv->base + REG_INTERRUPT_MASK);

	priv->reg_maccr = RX_BROADPKT | FULLDUP | CRC_APD | RX_FTL;
पूर्ण

अटल व्योम moxart_mac_enable(काष्ठा net_device *ndev)
अणु
	काष्ठा moxart_mac_priv_t *priv = netdev_priv(ndev);

	ग_लिखोl(0x00001010, priv->base + REG_INT_TIMER_CTRL);
	ग_लिखोl(0x00000001, priv->base + REG_APOLL_TIMER_CTRL);
	ग_लिखोl(0x00000390, priv->base + REG_DMA_BLEN_CTRL);

	priv->reg_imr |= (RPKT_FINISH_M | XPKT_FINISH_M);
	ग_लिखोl(priv->reg_imr, priv->base + REG_INTERRUPT_MASK);

	priv->reg_maccr |= (RCV_EN | XMT_EN | RDMA_EN | XDMA_EN);
	ग_लिखोl(priv->reg_maccr, priv->base + REG_MAC_CTRL);
पूर्ण

अटल व्योम moxart_mac_setup_desc_ring(काष्ठा net_device *ndev)
अणु
	काष्ठा moxart_mac_priv_t *priv = netdev_priv(ndev);
	व्योम *desc;
	पूर्णांक i;

	क्रम (i = 0; i < TX_DESC_NUM; i++) अणु
		desc = priv->tx_desc_base + i * TX_REG_DESC_SIZE;
		स_रखो(desc, 0, TX_REG_DESC_SIZE);

		priv->tx_buf[i] = priv->tx_buf_base + priv->tx_buf_size * i;
	पूर्ण
	moxart_desc_ग_लिखो(TX_DESC1_END, desc + TX_REG_OFFSET_DESC1);

	priv->tx_head = 0;
	priv->tx_tail = 0;

	क्रम (i = 0; i < RX_DESC_NUM; i++) अणु
		desc = priv->rx_desc_base + i * RX_REG_DESC_SIZE;
		स_रखो(desc, 0, RX_REG_DESC_SIZE);
		moxart_desc_ग_लिखो(RX_DESC0_DMA_OWN, desc + RX_REG_OFFSET_DESC0);
		moxart_desc_ग_लिखो(RX_BUF_SIZE & RX_DESC1_BUF_SIZE_MASK,
		       desc + RX_REG_OFFSET_DESC1);

		priv->rx_buf[i] = priv->rx_buf_base + priv->rx_buf_size * i;
		priv->rx_mapping[i] = dma_map_single(&ndev->dev,
						     priv->rx_buf[i],
						     priv->rx_buf_size,
						     DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&ndev->dev, priv->rx_mapping[i]))
			netdev_err(ndev, "DMA mapping error\n");

		moxart_desc_ग_लिखो(priv->rx_mapping[i],
		       desc + RX_REG_OFFSET_DESC2 + RX_DESC2_ADDRESS_PHYS);
		moxart_desc_ग_लिखो((uपूर्णांकptr_t)priv->rx_buf[i],
		       desc + RX_REG_OFFSET_DESC2 + RX_DESC2_ADDRESS_VIRT);
	पूर्ण
	moxart_desc_ग_लिखो(RX_DESC1_END, desc + RX_REG_OFFSET_DESC1);

	priv->rx_head = 0;

	/* reset the MAC controller TX/RX descriptor base address */
	ग_लिखोl(priv->tx_base, priv->base + REG_TXR_BASE_ADDRESS);
	ग_लिखोl(priv->rx_base, priv->base + REG_RXR_BASE_ADDRESS);
पूर्ण

अटल पूर्णांक moxart_mac_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा moxart_mac_priv_t *priv = netdev_priv(ndev);

	अगर (!is_valid_ether_addr(ndev->dev_addr))
		वापस -EADDRNOTAVAIL;

	napi_enable(&priv->napi);

	moxart_mac_reset(ndev);
	moxart_update_mac_address(ndev);
	moxart_mac_setup_desc_ring(ndev);
	moxart_mac_enable(ndev);
	netअगर_start_queue(ndev);

	netdev_dbg(ndev, "%s: IMR=0x%x, MACCR=0x%x\n",
		   __func__, पढ़ोl(priv->base + REG_INTERRUPT_MASK),
		   पढ़ोl(priv->base + REG_MAC_CTRL));

	वापस 0;
पूर्ण

अटल पूर्णांक moxart_mac_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा moxart_mac_priv_t *priv = netdev_priv(ndev);

	napi_disable(&priv->napi);

	netअगर_stop_queue(ndev);

	/* disable all पूर्णांकerrupts */
	ग_लिखोl(0, priv->base + REG_INTERRUPT_MASK);

	/* disable all functions */
	ग_लिखोl(0, priv->base + REG_MAC_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक moxart_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा moxart_mac_priv_t *priv = container_of(napi,
						      काष्ठा moxart_mac_priv_t,
						      napi);
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा sk_buff *skb;
	व्योम *desc;
	अचिन्हित पूर्णांक desc0, len;
	पूर्णांक rx_head = priv->rx_head;
	पूर्णांक rx = 0;

	जबतक (rx < budget) अणु
		desc = priv->rx_desc_base + (RX_REG_DESC_SIZE * rx_head);
		desc0 = moxart_desc_पढ़ो(desc + RX_REG_OFFSET_DESC0);
		rmb(); /* ensure desc0 is up to date */

		अगर (desc0 & RX_DESC0_DMA_OWN)
			अवरोध;

		अगर (desc0 & (RX_DESC0_ERR | RX_DESC0_CRC_ERR | RX_DESC0_FTL |
			     RX_DESC0_RUNT | RX_DESC0_ODD_NB)) अणु
			net_dbg_ratelimited("packet error\n");
			ndev->stats.rx_dropped++;
			ndev->stats.rx_errors++;
			जाओ rx_next;
		पूर्ण

		len = desc0 & RX_DESC0_FRAME_LEN_MASK;

		अगर (len > RX_BUF_SIZE)
			len = RX_BUF_SIZE;

		dma_sync_single_क्रम_cpu(&ndev->dev,
					priv->rx_mapping[rx_head],
					priv->rx_buf_size, DMA_FROM_DEVICE);
		skb = netdev_alloc_skb_ip_align(ndev, len);

		अगर (unlikely(!skb)) अणु
			net_dbg_ratelimited("netdev_alloc_skb_ip_align failed\n");
			ndev->stats.rx_dropped++;
			ndev->stats.rx_errors++;
			जाओ rx_next;
		पूर्ण

		स_नकल(skb->data, priv->rx_buf[rx_head], len);
		skb_put(skb, len);
		skb->protocol = eth_type_trans(skb, ndev);
		napi_gro_receive(&priv->napi, skb);
		rx++;

		ndev->stats.rx_packets++;
		ndev->stats.rx_bytes += len;
		अगर (desc0 & RX_DESC0_MULTICAST)
			ndev->stats.multicast++;

rx_next:
		wmb(); /* prevent setting ownership back too early */
		moxart_desc_ग_लिखो(RX_DESC0_DMA_OWN, desc + RX_REG_OFFSET_DESC0);

		rx_head = RX_NEXT(rx_head);
		priv->rx_head = rx_head;
	पूर्ण

	अगर (rx < budget)
		napi_complete_करोne(napi, rx);

	priv->reg_imr |= RPKT_FINISH_M;
	ग_लिखोl(priv->reg_imr, priv->base + REG_INTERRUPT_MASK);

	वापस rx;
पूर्ण

अटल पूर्णांक moxart_tx_queue_space(काष्ठा net_device *ndev)
अणु
	काष्ठा moxart_mac_priv_t *priv = netdev_priv(ndev);

	वापस CIRC_SPACE(priv->tx_head, priv->tx_tail, TX_DESC_NUM);
पूर्ण

अटल व्योम moxart_tx_finished(काष्ठा net_device *ndev)
अणु
	काष्ठा moxart_mac_priv_t *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक tx_head = priv->tx_head;
	अचिन्हित पूर्णांक tx_tail = priv->tx_tail;

	जबतक (tx_tail != tx_head) अणु
		dma_unmap_single(&ndev->dev, priv->tx_mapping[tx_tail],
				 priv->tx_len[tx_tail], DMA_TO_DEVICE);

		ndev->stats.tx_packets++;
		ndev->stats.tx_bytes += priv->tx_skb[tx_tail]->len;

		dev_consume_skb_irq(priv->tx_skb[tx_tail]);
		priv->tx_skb[tx_tail] = शून्य;

		tx_tail = TX_NEXT(tx_tail);
	पूर्ण
	priv->tx_tail = tx_tail;
	अगर (netअगर_queue_stopped(ndev) &&
	    moxart_tx_queue_space(ndev) >= TX_WAKE_THRESHOLD)
		netअगर_wake_queue(ndev);
पूर्ण

अटल irqवापस_t moxart_mac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = (काष्ठा net_device *)dev_id;
	काष्ठा moxart_mac_priv_t *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक ists = पढ़ोl(priv->base + REG_INTERRUPT_STATUS);

	अगर (ists & XPKT_OK_INT_STS)
		moxart_tx_finished(ndev);

	अगर (ists & RPKT_FINISH) अणु
		अगर (napi_schedule_prep(&priv->napi)) अणु
			priv->reg_imr &= ~RPKT_FINISH_M;
			ग_लिखोl(priv->reg_imr, priv->base + REG_INTERRUPT_MASK);
			__napi_schedule(&priv->napi);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल netdev_tx_t moxart_mac_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *ndev)
अणु
	काष्ठा moxart_mac_priv_t *priv = netdev_priv(ndev);
	व्योम *desc;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक tx_head;
	u32 txdes1;
	netdev_tx_t ret = NETDEV_TX_BUSY;

	spin_lock_irq(&priv->txlock);

	tx_head = priv->tx_head;
	desc = priv->tx_desc_base + (TX_REG_DESC_SIZE * tx_head);

	अगर (moxart_tx_queue_space(ndev) == 1)
		netअगर_stop_queue(ndev);

	अगर (moxart_desc_पढ़ो(desc + TX_REG_OFFSET_DESC0) & TX_DESC0_DMA_OWN) अणु
		net_dbg_ratelimited("no TX space for packet\n");
		ndev->stats.tx_dropped++;
		जाओ out_unlock;
	पूर्ण
	rmb(); /* ensure data is only पढ़ो that had TX_DESC0_DMA_OWN cleared */

	len = skb->len > TX_BUF_SIZE ? TX_BUF_SIZE : skb->len;

	priv->tx_mapping[tx_head] = dma_map_single(&ndev->dev, skb->data,
						   len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&ndev->dev, priv->tx_mapping[tx_head])) अणु
		netdev_err(ndev, "DMA mapping error\n");
		जाओ out_unlock;
	पूर्ण

	priv->tx_len[tx_head] = len;
	priv->tx_skb[tx_head] = skb;

	moxart_desc_ग_लिखो(priv->tx_mapping[tx_head],
	       desc + TX_REG_OFFSET_DESC2 + TX_DESC2_ADDRESS_PHYS);
	moxart_desc_ग_लिखो((uपूर्णांकptr_t)skb->data,
	       desc + TX_REG_OFFSET_DESC2 + TX_DESC2_ADDRESS_VIRT);

	अगर (skb->len < ETH_ZLEN) अणु
		स_रखो(&skb->data[skb->len],
		       0, ETH_ZLEN - skb->len);
		len = ETH_ZLEN;
	पूर्ण

	dma_sync_single_क्रम_device(&ndev->dev, priv->tx_mapping[tx_head],
				   priv->tx_buf_size, DMA_TO_DEVICE);

	txdes1 = TX_DESC1_LTS | TX_DESC1_FTS | (len & TX_DESC1_BUF_SIZE_MASK);
	अगर (tx_head == TX_DESC_NUM_MASK)
		txdes1 |= TX_DESC1_END;
	moxart_desc_ग_लिखो(txdes1, desc + TX_REG_OFFSET_DESC1);
	wmb(); /* flush descriptor beक्रमe transferring ownership */
	moxart_desc_ग_लिखो(TX_DESC0_DMA_OWN, desc + TX_REG_OFFSET_DESC0);

	/* start to send packet */
	ग_लिखोl(0xffffffff, priv->base + REG_TX_POLL_DEMAND);

	priv->tx_head = TX_NEXT(tx_head);

	netअगर_trans_update(ndev);
	ret = NETDEV_TX_OK;
out_unlock:
	spin_unlock_irq(&priv->txlock);

	वापस ret;
पूर्ण

अटल व्योम moxart_mac_seपंचांगulticast(काष्ठा net_device *ndev)
अणु
	काष्ठा moxart_mac_priv_t *priv = netdev_priv(ndev);
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक crc_val;

	netdev_क्रम_each_mc_addr(ha, ndev) अणु
		crc_val = crc32_le(~0, ha->addr, ETH_ALEN);
		crc_val = (crc_val >> 26) & 0x3f;
		अगर (crc_val >= 32) अणु
			ग_लिखोl(पढ़ोl(priv->base + REG_MCAST_HASH_TABLE1) |
			       (1UL << (crc_val - 32)),
			       priv->base + REG_MCAST_HASH_TABLE1);
		पूर्ण अन्यथा अणु
			ग_लिखोl(पढ़ोl(priv->base + REG_MCAST_HASH_TABLE0) |
			       (1UL << crc_val),
			       priv->base + REG_MCAST_HASH_TABLE0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम moxart_mac_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा moxart_mac_priv_t *priv = netdev_priv(ndev);

	spin_lock_irq(&priv->txlock);

	(ndev->flags & IFF_PROMISC) ? (priv->reg_maccr |= RCV_ALL) :
				      (priv->reg_maccr &= ~RCV_ALL);

	(ndev->flags & IFF_ALLMULTI) ? (priv->reg_maccr |= RX_MULTIPKT) :
				       (priv->reg_maccr &= ~RX_MULTIPKT);

	अगर ((ndev->flags & IFF_MULTICAST) && netdev_mc_count(ndev)) अणु
		priv->reg_maccr |= HT_MULTI_EN;
		moxart_mac_seपंचांगulticast(ndev);
	पूर्ण अन्यथा अणु
		priv->reg_maccr &= ~HT_MULTI_EN;
	पूर्ण

	ग_लिखोl(priv->reg_maccr, priv->base + REG_MAC_CTRL);

	spin_unlock_irq(&priv->txlock);
पूर्ण

अटल स्थिर काष्ठा net_device_ops moxart_netdev_ops = अणु
	.nकरो_खोलो		= moxart_mac_खोलो,
	.nकरो_stop		= moxart_mac_stop,
	.nकरो_start_xmit		= moxart_mac_start_xmit,
	.nकरो_set_rx_mode	= moxart_mac_set_rx_mode,
	.nकरो_set_mac_address	= moxart_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक moxart_mac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *p_dev = &pdev->dev;
	काष्ठा device_node *node = p_dev->of_node;
	काष्ठा net_device *ndev;
	काष्ठा moxart_mac_priv_t *priv;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक irq;
	पूर्णांक ret;

	ndev = alloc_etherdev(माप(काष्ठा moxart_mac_priv_t));
	अगर (!ndev)
		वापस -ENOMEM;

	irq = irq_of_parse_and_map(node, 0);
	अगर (irq <= 0) अणु
		netdev_err(ndev, "irq_of_parse_and_map failed\n");
		ret = -EINVAL;
		जाओ irq_map_fail;
	पूर्ण

	priv = netdev_priv(ndev);
	priv->ndev = ndev;
	priv->pdev = pdev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ndev->base_addr = res->start;
	priv->base = devm_ioremap_resource(p_dev, res);
	अगर (IS_ERR(priv->base)) अणु
		ret = PTR_ERR(priv->base);
		जाओ init_fail;
	पूर्ण

	spin_lock_init(&priv->txlock);

	priv->tx_buf_size = TX_BUF_SIZE;
	priv->rx_buf_size = RX_BUF_SIZE;

	priv->tx_desc_base = dma_alloc_coherent(&pdev->dev, TX_REG_DESC_SIZE *
						TX_DESC_NUM, &priv->tx_base,
						GFP_DMA | GFP_KERNEL);
	अगर (!priv->tx_desc_base) अणु
		ret = -ENOMEM;
		जाओ init_fail;
	पूर्ण

	priv->rx_desc_base = dma_alloc_coherent(&pdev->dev, RX_REG_DESC_SIZE *
						RX_DESC_NUM, &priv->rx_base,
						GFP_DMA | GFP_KERNEL);
	अगर (!priv->rx_desc_base) अणु
		ret = -ENOMEM;
		जाओ init_fail;
	पूर्ण

	priv->tx_buf_base = kदो_स्मृति_array(priv->tx_buf_size, TX_DESC_NUM,
					  GFP_ATOMIC);
	अगर (!priv->tx_buf_base) अणु
		ret = -ENOMEM;
		जाओ init_fail;
	पूर्ण

	priv->rx_buf_base = kदो_स्मृति_array(priv->rx_buf_size, RX_DESC_NUM,
					  GFP_ATOMIC);
	अगर (!priv->rx_buf_base) अणु
		ret = -ENOMEM;
		जाओ init_fail;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ndev);

	ret = devm_request_irq(p_dev, irq, moxart_mac_पूर्णांकerrupt, 0,
			       pdev->name, ndev);
	अगर (ret) अणु
		netdev_err(ndev, "devm_request_irq failed\n");
		जाओ init_fail;
	पूर्ण

	ndev->netdev_ops = &moxart_netdev_ops;
	netअगर_napi_add(ndev, &priv->napi, moxart_rx_poll, RX_DESC_NUM);
	ndev->priv_flags |= IFF_UNICAST_FLT;
	ndev->irq = irq;

	SET_NETDEV_DEV(ndev, &pdev->dev);

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		मुक्त_netdev(ndev);
		जाओ init_fail;
	पूर्ण

	netdev_dbg(ndev, "%s: IRQ=%d address=%pM\n",
		   __func__, ndev->irq, ndev->dev_addr);

	वापस 0;

init_fail:
	netdev_err(ndev, "init failed\n");
	moxart_mac_मुक्त_memory(ndev);
irq_map_fail:
	मुक्त_netdev(ndev);
	वापस ret;
पूर्ण

अटल पूर्णांक moxart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_netdev(ndev);
	devm_मुक्त_irq(&pdev->dev, ndev->irq, ndev);
	moxart_mac_मुक्त_memory(ndev);
	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id moxart_mac_match[] = अणु
	अणु .compatible = "moxa,moxart-mac" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, moxart_mac_match);

अटल काष्ठा platक्रमm_driver moxart_mac_driver = अणु
	.probe	= moxart_mac_probe,
	.हटाओ	= moxart_हटाओ,
	.driver	= अणु
		.name		= "moxart-ethernet",
		.of_match_table	= moxart_mac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(moxart_mac_driver);

MODULE_DESCRIPTION("MOXART RTL8201CP Ethernet driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jonas Jensen <jonas.jensen@gmail.com>");
