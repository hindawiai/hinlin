<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Lantiq / Intel PMAC driver क्रम XRX200 SoCs
 *
 * Copyright (C) 2010 Lantiq Deutschland
 * Copyright (C) 2012 John Crispin <john@phrozen.org>
 * Copyright (C) 2017 - 2018 Hauke Mehrtens <hauke@hauke-m.de>
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>

#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <xway_dma.h>

/* DMA */
#घोषणा XRX200_DMA_DATA_LEN	0x600
#घोषणा XRX200_DMA_RX		0
#घोषणा XRX200_DMA_TX		1

/* cpu port mac */
#घोषणा PMAC_RX_IPG		0x0024
#घोषणा PMAC_RX_IPG_MASK	0xf

#घोषणा PMAC_HD_CTL		0x0000
/* Add Ethernet header to packets from DMA to PMAC */
#घोषणा PMAC_HD_CTL_ADD		BIT(0)
/* Add VLAN tag to Packets from DMA to PMAC */
#घोषणा PMAC_HD_CTL_TAG		BIT(1)
/* Add CRC to packets from DMA to PMAC */
#घोषणा PMAC_HD_CTL_AC		BIT(2)
/* Add status header to packets from PMAC to DMA */
#घोषणा PMAC_HD_CTL_AS		BIT(3)
/* Remove CRC from packets from PMAC to DMA */
#घोषणा PMAC_HD_CTL_RC		BIT(4)
/* Remove Layer-2 header from packets from PMAC to DMA */
#घोषणा PMAC_HD_CTL_RL2		BIT(5)
/* Status header is present from DMA to PMAC */
#घोषणा PMAC_HD_CTL_RXSH	BIT(6)
/* Add special tag from PMAC to चयन */
#घोषणा PMAC_HD_CTL_AST		BIT(7)
/* Remove specail Tag from PMAC to DMA */
#घोषणा PMAC_HD_CTL_RST		BIT(8)
/* Check CRC from DMA to PMAC */
#घोषणा PMAC_HD_CTL_CCRC	BIT(9)
/* Enable reaction to Pause frames in the PMAC */
#घोषणा PMAC_HD_CTL_FC		BIT(10)

काष्ठा xrx200_chan अणु
	पूर्णांक tx_मुक्त;

	काष्ठा napi_काष्ठा napi;
	काष्ठा ltq_dma_channel dma;
	काष्ठा sk_buff *skb[LTQ_DESC_NUM];

	काष्ठा xrx200_priv *priv;
पूर्ण;

काष्ठा xrx200_priv अणु
	काष्ठा clk *clk;

	काष्ठा xrx200_chan chan_tx;
	काष्ठा xrx200_chan chan_rx;

	काष्ठा net_device *net_dev;
	काष्ठा device *dev;

	__iomem व्योम *pmac_reg;
पूर्ण;

अटल u32 xrx200_pmac_r32(काष्ठा xrx200_priv *priv, u32 offset)
अणु
	वापस __raw_पढ़ोl(priv->pmac_reg + offset);
पूर्ण

अटल व्योम xrx200_pmac_w32(काष्ठा xrx200_priv *priv, u32 val, u32 offset)
अणु
	__raw_ग_लिखोl(val, priv->pmac_reg + offset);
पूर्ण

अटल व्योम xrx200_pmac_mask(काष्ठा xrx200_priv *priv, u32 clear, u32 set,
			     u32 offset)
अणु
	u32 val = xrx200_pmac_r32(priv, offset);

	val &= ~(clear);
	val |= set;
	xrx200_pmac_w32(priv, val, offset);
पूर्ण

/* drop all the packets from the DMA ring */
अटल व्योम xrx200_flush_dma(काष्ठा xrx200_chan *ch)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < LTQ_DESC_NUM; i++) अणु
		काष्ठा ltq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];

		अगर ((desc->ctl & (LTQ_DMA_OWN | LTQ_DMA_C)) != LTQ_DMA_C)
			अवरोध;

		desc->ctl = LTQ_DMA_OWN | LTQ_DMA_RX_OFFSET(NET_IP_ALIGN) |
			    XRX200_DMA_DATA_LEN;
		ch->dma.desc++;
		ch->dma.desc %= LTQ_DESC_NUM;
	पूर्ण
पूर्ण

अटल पूर्णांक xrx200_खोलो(काष्ठा net_device *net_dev)
अणु
	काष्ठा xrx200_priv *priv = netdev_priv(net_dev);

	napi_enable(&priv->chan_tx.napi);
	ltq_dma_खोलो(&priv->chan_tx.dma);
	ltq_dma_enable_irq(&priv->chan_tx.dma);

	napi_enable(&priv->chan_rx.napi);
	ltq_dma_खोलो(&priv->chan_rx.dma);
	/* The boot loader करोes not always deactivate the receiving of frames
	 * on the ports and then some packets queue up in the PPE buffers.
	 * They alपढ़ोy passed the PMAC so they करो not have the tags
	 * configured here. Read the these packets here and drop them.
	 * The HW should have written them पूर्णांकo memory after 10us
	 */
	usleep_range(20, 40);
	xrx200_flush_dma(&priv->chan_rx);
	ltq_dma_enable_irq(&priv->chan_rx.dma);

	netअगर_wake_queue(net_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक xrx200_बंद(काष्ठा net_device *net_dev)
अणु
	काष्ठा xrx200_priv *priv = netdev_priv(net_dev);

	netअगर_stop_queue(net_dev);

	napi_disable(&priv->chan_rx.napi);
	ltq_dma_बंद(&priv->chan_rx.dma);

	napi_disable(&priv->chan_tx.napi);
	ltq_dma_बंद(&priv->chan_tx.dma);

	वापस 0;
पूर्ण

अटल पूर्णांक xrx200_alloc_skb(काष्ठा xrx200_chan *ch)
अणु
	काष्ठा sk_buff *skb = ch->skb[ch->dma.desc];
	dma_addr_t mapping;
	पूर्णांक ret = 0;

	ch->skb[ch->dma.desc] = netdev_alloc_skb_ip_align(ch->priv->net_dev,
							  XRX200_DMA_DATA_LEN);
	अगर (!ch->skb[ch->dma.desc]) अणु
		ret = -ENOMEM;
		जाओ skip;
	पूर्ण

	mapping = dma_map_single(ch->priv->dev, ch->skb[ch->dma.desc]->data,
				 XRX200_DMA_DATA_LEN, DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(ch->priv->dev, mapping))) अणु
		dev_kमुक्त_skb_any(ch->skb[ch->dma.desc]);
		ch->skb[ch->dma.desc] = skb;
		ret = -ENOMEM;
		जाओ skip;
	पूर्ण

	ch->dma.desc_base[ch->dma.desc].addr = mapping;
	/* Make sure the address is written beक्रमe we give it to HW */
	wmb();
skip:
	ch->dma.desc_base[ch->dma.desc].ctl =
		LTQ_DMA_OWN | LTQ_DMA_RX_OFFSET(NET_IP_ALIGN) |
		XRX200_DMA_DATA_LEN;

	वापस ret;
पूर्ण

अटल पूर्णांक xrx200_hw_receive(काष्ठा xrx200_chan *ch)
अणु
	काष्ठा xrx200_priv *priv = ch->priv;
	काष्ठा ltq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];
	काष्ठा sk_buff *skb = ch->skb[ch->dma.desc];
	पूर्णांक len = (desc->ctl & LTQ_DMA_SIZE_MASK);
	काष्ठा net_device *net_dev = priv->net_dev;
	पूर्णांक ret;

	ret = xrx200_alloc_skb(ch);

	ch->dma.desc++;
	ch->dma.desc %= LTQ_DESC_NUM;

	अगर (ret) अणु
		net_dev->stats.rx_dropped++;
		netdev_err(net_dev, "failed to allocate new rx buffer\n");
		वापस ret;
	पूर्ण

	skb_put(skb, len);
	skb->protocol = eth_type_trans(skb, net_dev);
	netअगर_receive_skb(skb);
	net_dev->stats.rx_packets++;
	net_dev->stats.rx_bytes += len - ETH_FCS_LEN;

	वापस 0;
पूर्ण

अटल पूर्णांक xrx200_poll_rx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा xrx200_chan *ch = container_of(napi,
				काष्ठा xrx200_chan, napi);
	पूर्णांक rx = 0;
	पूर्णांक ret;

	जबतक (rx < budget) अणु
		काष्ठा ltq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];

		अगर ((desc->ctl & (LTQ_DMA_OWN | LTQ_DMA_C)) == LTQ_DMA_C) अणु
			ret = xrx200_hw_receive(ch);
			अगर (ret)
				वापस ret;
			rx++;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rx < budget) अणु
		अगर (napi_complete_करोne(&ch->napi, rx))
			ltq_dma_enable_irq(&ch->dma);
	पूर्ण

	वापस rx;
पूर्ण

अटल पूर्णांक xrx200_tx_housekeeping(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा xrx200_chan *ch = container_of(napi,
				काष्ठा xrx200_chan, napi);
	काष्ठा net_device *net_dev = ch->priv->net_dev;
	पूर्णांक pkts = 0;
	पूर्णांक bytes = 0;

	netअगर_tx_lock(net_dev);
	जबतक (pkts < budget) अणु
		काष्ठा ltq_dma_desc *desc = &ch->dma.desc_base[ch->tx_मुक्त];

		अगर ((desc->ctl & (LTQ_DMA_OWN | LTQ_DMA_C)) == LTQ_DMA_C) अणु
			काष्ठा sk_buff *skb = ch->skb[ch->tx_मुक्त];

			pkts++;
			bytes += skb->len;
			ch->skb[ch->tx_मुक्त] = शून्य;
			consume_skb(skb);
			स_रखो(&ch->dma.desc_base[ch->tx_मुक्त], 0,
			       माप(काष्ठा ltq_dma_desc));
			ch->tx_मुक्त++;
			ch->tx_मुक्त %= LTQ_DESC_NUM;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	net_dev->stats.tx_packets += pkts;
	net_dev->stats.tx_bytes += bytes;
	netdev_completed_queue(ch->priv->net_dev, pkts, bytes);

	netअगर_tx_unlock(net_dev);
	अगर (netअगर_queue_stopped(net_dev))
		netअगर_wake_queue(net_dev);

	अगर (pkts < budget) अणु
		अगर (napi_complete_करोne(&ch->napi, pkts))
			ltq_dma_enable_irq(&ch->dma);
	पूर्ण

	वापस pkts;
पूर्ण

अटल netdev_tx_t xrx200_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *net_dev)
अणु
	काष्ठा xrx200_priv *priv = netdev_priv(net_dev);
	काष्ठा xrx200_chan *ch = &priv->chan_tx;
	काष्ठा ltq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];
	u32 byte_offset;
	dma_addr_t mapping;
	पूर्णांक len;

	skb->dev = net_dev;
	अगर (skb_put_padto(skb, ETH_ZLEN)) अणु
		net_dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	len = skb->len;

	अगर ((desc->ctl & (LTQ_DMA_OWN | LTQ_DMA_C)) || ch->skb[ch->dma.desc]) अणु
		netdev_err(net_dev, "tx ring full\n");
		netअगर_stop_queue(net_dev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	ch->skb[ch->dma.desc] = skb;

	mapping = dma_map_single(priv->dev, skb->data, len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(priv->dev, mapping)))
		जाओ err_drop;

	/* dma needs to start on a 16 byte aligned address */
	byte_offset = mapping % 16;

	desc->addr = mapping - byte_offset;
	/* Make sure the address is written beक्रमe we give it to HW */
	wmb();
	desc->ctl = LTQ_DMA_OWN | LTQ_DMA_SOP | LTQ_DMA_EOP |
		LTQ_DMA_TX_OFFSET(byte_offset) | (len & LTQ_DMA_SIZE_MASK);
	ch->dma.desc++;
	ch->dma.desc %= LTQ_DESC_NUM;
	अगर (ch->dma.desc == ch->tx_मुक्त)
		netअगर_stop_queue(net_dev);

	netdev_sent_queue(net_dev, len);

	वापस NETDEV_TX_OK;

err_drop:
	dev_kमुक्त_skb(skb);
	net_dev->stats.tx_dropped++;
	net_dev->stats.tx_errors++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops xrx200_netdev_ops = अणु
	.nकरो_खोलो		= xrx200_खोलो,
	.nकरो_stop		= xrx200_बंद,
	.nकरो_start_xmit		= xrx200_start_xmit,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल irqवापस_t xrx200_dma_irq(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा xrx200_chan *ch = ptr;

	अगर (napi_schedule_prep(&ch->napi)) अणु
		ltq_dma_disable_irq(&ch->dma);
		__napi_schedule(&ch->napi);
	पूर्ण

	ltq_dma_ack_irq(&ch->dma);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xrx200_dma_init(काष्ठा xrx200_priv *priv)
अणु
	काष्ठा xrx200_chan *ch_rx = &priv->chan_rx;
	काष्ठा xrx200_chan *ch_tx = &priv->chan_tx;
	पूर्णांक ret = 0;
	पूर्णांक i;

	ltq_dma_init_port(DMA_PORT_ETOP);

	ch_rx->dma.nr = XRX200_DMA_RX;
	ch_rx->dma.dev = priv->dev;
	ch_rx->priv = priv;

	ltq_dma_alloc_rx(&ch_rx->dma);
	क्रम (ch_rx->dma.desc = 0; ch_rx->dma.desc < LTQ_DESC_NUM;
	     ch_rx->dma.desc++) अणु
		ret = xrx200_alloc_skb(ch_rx);
		अगर (ret)
			जाओ rx_मुक्त;
	पूर्ण
	ch_rx->dma.desc = 0;
	ret = devm_request_irq(priv->dev, ch_rx->dma.irq, xrx200_dma_irq, 0,
			       "xrx200_net_rx", &priv->chan_rx);
	अगर (ret) अणु
		dev_err(priv->dev, "failed to request RX irq %d\n",
			ch_rx->dma.irq);
		जाओ rx_ring_मुक्त;
	पूर्ण

	ch_tx->dma.nr = XRX200_DMA_TX;
	ch_tx->dma.dev = priv->dev;
	ch_tx->priv = priv;

	ltq_dma_alloc_tx(&ch_tx->dma);
	ret = devm_request_irq(priv->dev, ch_tx->dma.irq, xrx200_dma_irq, 0,
			       "xrx200_net_tx", &priv->chan_tx);
	अगर (ret) अणु
		dev_err(priv->dev, "failed to request TX irq %d\n",
			ch_tx->dma.irq);
		जाओ tx_मुक्त;
	पूर्ण

	वापस ret;

tx_मुक्त:
	ltq_dma_मुक्त(&ch_tx->dma);

rx_ring_मुक्त:
	/* मुक्त the allocated RX ring */
	क्रम (i = 0; i < LTQ_DESC_NUM; i++) अणु
		अगर (priv->chan_rx.skb[i])
			dev_kमुक्त_skb_any(priv->chan_rx.skb[i]);
	पूर्ण

rx_मुक्त:
	ltq_dma_मुक्त(&ch_rx->dma);
	वापस ret;
पूर्ण

अटल व्योम xrx200_hw_cleanup(काष्ठा xrx200_priv *priv)
अणु
	पूर्णांक i;

	ltq_dma_मुक्त(&priv->chan_tx.dma);
	ltq_dma_मुक्त(&priv->chan_rx.dma);

	/* मुक्त the allocated RX ring */
	क्रम (i = 0; i < LTQ_DESC_NUM; i++)
		dev_kमुक्त_skb_any(priv->chan_rx.skb[i]);
पूर्ण

अटल पूर्णांक xrx200_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource *res;
	काष्ठा xrx200_priv *priv;
	काष्ठा net_device *net_dev;
	पूर्णांक err;

	/* alloc the network device */
	net_dev = devm_alloc_etherdev(dev, माप(काष्ठा xrx200_priv));
	अगर (!net_dev)
		वापस -ENOMEM;

	priv = netdev_priv(net_dev);
	priv->net_dev = net_dev;
	priv->dev = dev;

	net_dev->netdev_ops = &xrx200_netdev_ops;
	SET_NETDEV_DEV(net_dev, dev);
	net_dev->min_mtu = ETH_ZLEN;
	net_dev->max_mtu = XRX200_DMA_DATA_LEN;

	/* load the memory ranges */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "failed to get resources\n");
		वापस -ENOENT;
	पूर्ण

	priv->pmac_reg = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->pmac_reg))
		वापस PTR_ERR(priv->pmac_reg);

	priv->chan_rx.dma.irq = platक्रमm_get_irq_byname(pdev, "rx");
	अगर (priv->chan_rx.dma.irq < 0)
		वापस -ENOENT;
	priv->chan_tx.dma.irq = platक्रमm_get_irq_byname(pdev, "tx");
	अगर (priv->chan_tx.dma.irq < 0)
		वापस -ENOENT;

	/* get the घड़ी */
	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "failed to get clock\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	err = of_get_mac_address(np, net_dev->dev_addr);
	अगर (err)
		eth_hw_addr_अक्रमom(net_dev);

	/* bring up the dma engine and IP core */
	err = xrx200_dma_init(priv);
	अगर (err)
		वापस err;

	/* enable घड़ी gate */
	err = clk_prepare_enable(priv->clk);
	अगर (err)
		जाओ err_uninit_dma;

	/* set IPG to 12 */
	xrx200_pmac_mask(priv, PMAC_RX_IPG_MASK, 0xb, PMAC_RX_IPG);

	/* enable status header, enable CRC */
	xrx200_pmac_mask(priv, 0,
			 PMAC_HD_CTL_RST | PMAC_HD_CTL_AST | PMAC_HD_CTL_RXSH |
			 PMAC_HD_CTL_AS | PMAC_HD_CTL_AC | PMAC_HD_CTL_RC,
			 PMAC_HD_CTL);

	/* setup NAPI */
	netअगर_napi_add(net_dev, &priv->chan_rx.napi, xrx200_poll_rx, 32);
	netअगर_tx_napi_add(net_dev, &priv->chan_tx.napi, xrx200_tx_housekeeping, 32);

	platक्रमm_set_drvdata(pdev, priv);

	err = रेजिस्टर_netdev(net_dev);
	अगर (err)
		जाओ err_unprepare_clk;

	वापस 0;

err_unprepare_clk:
	clk_disable_unprepare(priv->clk);

err_uninit_dma:
	xrx200_hw_cleanup(priv);

	वापस err;
पूर्ण

अटल पूर्णांक xrx200_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xrx200_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा net_device *net_dev = priv->net_dev;

	/* मुक्त stack related instances */
	netअगर_stop_queue(net_dev);
	netअगर_napi_del(&priv->chan_tx.napi);
	netअगर_napi_del(&priv->chan_rx.napi);

	/* हटाओ the actual device */
	unरेजिस्टर_netdev(net_dev);

	/* release the घड़ी */
	clk_disable_unprepare(priv->clk);

	/* shut करोwn hardware */
	xrx200_hw_cleanup(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xrx200_match[] = अणु
	अणु .compatible = "lantiq,xrx200-net" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xrx200_match);

अटल काष्ठा platक्रमm_driver xrx200_driver = अणु
	.probe = xrx200_probe,
	.हटाओ = xrx200_हटाओ,
	.driver = अणु
		.name = "lantiq,xrx200-net",
		.of_match_table = xrx200_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xrx200_driver);

MODULE_AUTHOR("John Crispin <john@phrozen.org>");
MODULE_DESCRIPTION("Lantiq SoC XRX200 ethernet");
MODULE_LICENSE("GPL");
