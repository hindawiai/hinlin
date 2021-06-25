<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hisilicon Fast Ethernet MAC Driver
 *
 * Copyright (c) 2016 HiSilicon Technologies Co., Ltd.
 */

#समावेश <linux/circ_buf.h>
#समावेश <linux/clk.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

/* MAC control रेजिस्टर list */
#घोषणा MAC_PORTSEL			0x0200
#घोषणा MAC_PORTSEL_STAT_CPU		BIT(0)
#घोषणा MAC_PORTSEL_RMII		BIT(1)
#घोषणा MAC_PORTSET			0x0208
#घोषणा MAC_PORTSET_DUPLEX_FULL		BIT(0)
#घोषणा MAC_PORTSET_LINKED		BIT(1)
#घोषणा MAC_PORTSET_SPEED_100M		BIT(2)
#घोषणा MAC_SET				0x0210
#घोषणा MAX_FRAME_SIZE			1600
#घोषणा MAX_FRAME_SIZE_MASK		GENMASK(10, 0)
#घोषणा BIT_PAUSE_EN			BIT(18)
#घोषणा RX_COALESCE_SET			0x0340
#घोषणा RX_COALESCED_FRAME_OFFSET	24
#घोषणा RX_COALESCED_FRAMES		8
#घोषणा RX_COALESCED_TIMER		0x74
#घोषणा QLEN_SET			0x0344
#घोषणा RX_DEPTH_OFFSET			8
#घोषणा MAX_HW_FIFO_DEPTH		64
#घोषणा HW_TX_FIFO_DEPTH		12
#घोषणा HW_RX_FIFO_DEPTH		(MAX_HW_FIFO_DEPTH - HW_TX_FIFO_DEPTH)
#घोषणा IQFRM_DES			0x0354
#घोषणा RX_FRAME_LEN_MASK		GENMASK(11, 0)
#घोषणा IQ_ADDR				0x0358
#घोषणा EQ_ADDR				0x0360
#घोषणा EQFRM_LEN			0x0364
#घोषणा ADDRQ_STAT			0x036C
#घोषणा TX_CNT_INUSE_MASK		GENMASK(5, 0)
#घोषणा BIT_TX_READY			BIT(24)
#घोषणा BIT_RX_READY			BIT(25)
/* global control रेजिस्टर list */
#घोषणा GLB_HOSTMAC_L32			0x0000
#घोषणा GLB_HOSTMAC_H16			0x0004
#घोषणा GLB_SOFT_RESET			0x0008
#घोषणा SOFT_RESET_ALL			BIT(0)
#घोषणा GLB_FWCTRL			0x0010
#घोषणा FWCTRL_VLAN_ENABLE		BIT(0)
#घोषणा FWCTRL_FW2CPU_ENA		BIT(5)
#घोषणा FWCTRL_FWALL2CPU		BIT(7)
#घोषणा GLB_MACTCTRL			0x0014
#घोषणा MACTCTRL_UNI2CPU		BIT(1)
#घोषणा MACTCTRL_MULTI2CPU		BIT(3)
#घोषणा MACTCTRL_BROAD2CPU		BIT(5)
#घोषणा MACTCTRL_MACT_ENA		BIT(7)
#घोषणा GLB_IRQ_STAT			0x0030
#घोषणा GLB_IRQ_ENA			0x0034
#घोषणा IRQ_ENA_PORT0_MASK		GENMASK(7, 0)
#घोषणा IRQ_ENA_PORT0			BIT(18)
#घोषणा IRQ_ENA_ALL			BIT(19)
#घोषणा GLB_IRQ_RAW			0x0038
#घोषणा IRQ_INT_RX_RDY			BIT(0)
#घोषणा IRQ_INT_TX_PER_PACKET		BIT(1)
#घोषणा IRQ_INT_TX_FIFO_EMPTY		BIT(6)
#घोषणा IRQ_INT_MULTI_RXRDY		BIT(7)
#घोषणा DEF_INT_MASK			(IRQ_INT_MULTI_RXRDY | \
					IRQ_INT_TX_PER_PACKET | \
					IRQ_INT_TX_FIFO_EMPTY)
#घोषणा GLB_MAC_L32_BASE		0x0100
#घोषणा GLB_MAC_H16_BASE		0x0104
#घोषणा MACFLT_HI16_MASK		GENMASK(15, 0)
#घोषणा BIT_MACFLT_ENA			BIT(17)
#घोषणा BIT_MACFLT_FW2CPU		BIT(21)
#घोषणा GLB_MAC_H16(reg)		(GLB_MAC_H16_BASE + ((reg) * 0x8))
#घोषणा GLB_MAC_L32(reg)		(GLB_MAC_L32_BASE + ((reg) * 0x8))
#घोषणा MAX_MAC_FILTER_NUM		8
#घोषणा MAX_UNICAST_ADDRESSES		2
#घोषणा MAX_MULTICAST_ADDRESSES		(MAX_MAC_FILTER_NUM - \
					MAX_UNICAST_ADDRESSES)
/* software tx and rx queue number, should be घातer of 2 */
#घोषणा TXQ_NUM				64
#घोषणा RXQ_NUM				128
#घोषणा FEMAC_POLL_WEIGHT		16

#घोषणा PHY_RESET_DELAYS_PROPERTY	"hisilicon,phy-reset-delays-us"

क्रमागत phy_reset_delays अणु
	PRE_DELAY,
	PULSE,
	POST_DELAY,
	DELAYS_NUM,
पूर्ण;

काष्ठा hisi_femac_queue अणु
	काष्ठा sk_buff **skb;
	dma_addr_t *dma_phys;
	पूर्णांक num;
	अचिन्हित पूर्णांक head;
	अचिन्हित पूर्णांक tail;
पूर्ण;

काष्ठा hisi_femac_priv अणु
	व्योम __iomem *port_base;
	व्योम __iomem *glb_base;
	काष्ठा clk *clk;
	काष्ठा reset_control *mac_rst;
	काष्ठा reset_control *phy_rst;
	u32 phy_reset_delays[DELAYS_NUM];
	u32 link_status;

	काष्ठा device *dev;
	काष्ठा net_device *ndev;

	काष्ठा hisi_femac_queue txq;
	काष्ठा hisi_femac_queue rxq;
	u32 tx_fअगरo_used_cnt;
	काष्ठा napi_काष्ठा napi;
पूर्ण;

अटल व्योम hisi_femac_irq_enable(काष्ठा hisi_femac_priv *priv, पूर्णांक irqs)
अणु
	u32 val;

	val = पढ़ोl(priv->glb_base + GLB_IRQ_ENA);
	ग_लिखोl(val | irqs, priv->glb_base + GLB_IRQ_ENA);
पूर्ण

अटल व्योम hisi_femac_irq_disable(काष्ठा hisi_femac_priv *priv, पूर्णांक irqs)
अणु
	u32 val;

	val = पढ़ोl(priv->glb_base + GLB_IRQ_ENA);
	ग_लिखोl(val & (~irqs), priv->glb_base + GLB_IRQ_ENA);
पूर्ण

अटल व्योम hisi_femac_tx_dma_unmap(काष्ठा hisi_femac_priv *priv,
				    काष्ठा sk_buff *skb, अचिन्हित पूर्णांक pos)
अणु
	dma_addr_t dma_addr;

	dma_addr = priv->txq.dma_phys[pos];
	dma_unmap_single(priv->dev, dma_addr, skb->len, DMA_TO_DEVICE);
पूर्ण

अटल व्योम hisi_femac_xmit_reclaim(काष्ठा net_device *dev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा hisi_femac_priv *priv = netdev_priv(dev);
	काष्ठा hisi_femac_queue *txq = &priv->txq;
	अचिन्हित पूर्णांक bytes_compl = 0, pkts_compl = 0;
	u32 val;

	netअगर_tx_lock(dev);

	val = पढ़ोl(priv->port_base + ADDRQ_STAT) & TX_CNT_INUSE_MASK;
	जबतक (val < priv->tx_fअगरo_used_cnt) अणु
		skb = txq->skb[txq->tail];
		अगर (unlikely(!skb)) अणु
			netdev_err(dev, "xmitq_cnt_inuse=%d, tx_fifo_used=%d\n",
				   val, priv->tx_fअगरo_used_cnt);
			अवरोध;
		पूर्ण
		hisi_femac_tx_dma_unmap(priv, skb, txq->tail);
		pkts_compl++;
		bytes_compl += skb->len;
		dev_kमुक्त_skb_any(skb);

		priv->tx_fअगरo_used_cnt--;

		val = पढ़ोl(priv->port_base + ADDRQ_STAT) & TX_CNT_INUSE_MASK;
		txq->skb[txq->tail] = शून्य;
		txq->tail = (txq->tail + 1) % txq->num;
	पूर्ण

	netdev_completed_queue(dev, pkts_compl, bytes_compl);

	अगर (unlikely(netअगर_queue_stopped(dev)) && pkts_compl)
		netअगर_wake_queue(dev);

	netअगर_tx_unlock(dev);
पूर्ण

अटल व्योम hisi_femac_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा hisi_femac_priv *priv = netdev_priv(dev);
	काष्ठा phy_device *phy = dev->phydev;
	u32 status = 0;

	अगर (phy->link)
		status |= MAC_PORTSET_LINKED;
	अगर (phy->duplex == DUPLEX_FULL)
		status |= MAC_PORTSET_DUPLEX_FULL;
	अगर (phy->speed == SPEED_100)
		status |= MAC_PORTSET_SPEED_100M;

	अगर ((status != priv->link_status) &&
	    ((status | priv->link_status) & MAC_PORTSET_LINKED)) अणु
		ग_लिखोl(status, priv->port_base + MAC_PORTSET);
		priv->link_status = status;
		phy_prपूर्णांक_status(phy);
	पूर्ण
पूर्ण

अटल व्योम hisi_femac_rx_refill(काष्ठा hisi_femac_priv *priv)
अणु
	काष्ठा hisi_femac_queue *rxq = &priv->rxq;
	काष्ठा sk_buff *skb;
	u32 pos;
	u32 len = MAX_FRAME_SIZE;
	dma_addr_t addr;

	pos = rxq->head;
	जबतक (पढ़ोl(priv->port_base + ADDRQ_STAT) & BIT_RX_READY) अणु
		अगर (!CIRC_SPACE(pos, rxq->tail, rxq->num))
			अवरोध;
		अगर (unlikely(rxq->skb[pos])) अणु
			netdev_err(priv->ndev, "err skb[%d]=%p\n",
				   pos, rxq->skb[pos]);
			अवरोध;
		पूर्ण
		skb = netdev_alloc_skb_ip_align(priv->ndev, len);
		अगर (unlikely(!skb))
			अवरोध;

		addr = dma_map_single(priv->dev, skb->data, len,
				      DMA_FROM_DEVICE);
		अगर (dma_mapping_error(priv->dev, addr)) अणु
			dev_kमुक्त_skb_any(skb);
			अवरोध;
		पूर्ण
		rxq->dma_phys[pos] = addr;
		rxq->skb[pos] = skb;
		ग_लिखोl(addr, priv->port_base + IQ_ADDR);
		pos = (pos + 1) % rxq->num;
	पूर्ण
	rxq->head = pos;
पूर्ण

अटल पूर्णांक hisi_femac_rx(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा hisi_femac_priv *priv = netdev_priv(dev);
	काष्ठा hisi_femac_queue *rxq = &priv->rxq;
	काष्ठा sk_buff *skb;
	dma_addr_t addr;
	u32 rx_pkt_info, pos, len, rx_pkts_num = 0;

	pos = rxq->tail;
	जबतक (पढ़ोl(priv->glb_base + GLB_IRQ_RAW) & IRQ_INT_RX_RDY) अणु
		rx_pkt_info = पढ़ोl(priv->port_base + IQFRM_DES);
		len = rx_pkt_info & RX_FRAME_LEN_MASK;
		len -= ETH_FCS_LEN;

		/* tell hardware we will deal with this packet */
		ग_लिखोl(IRQ_INT_RX_RDY, priv->glb_base + GLB_IRQ_RAW);

		rx_pkts_num++;

		skb = rxq->skb[pos];
		अगर (unlikely(!skb)) अणु
			netdev_err(dev, "rx skb NULL. pos=%d\n", pos);
			अवरोध;
		पूर्ण
		rxq->skb[pos] = शून्य;

		addr = rxq->dma_phys[pos];
		dma_unmap_single(priv->dev, addr, MAX_FRAME_SIZE,
				 DMA_FROM_DEVICE);
		skb_put(skb, len);
		अगर (unlikely(skb->len > MAX_FRAME_SIZE)) अणु
			netdev_err(dev, "rcv len err, len = %d\n", skb->len);
			dev->stats.rx_errors++;
			dev->stats.rx_length_errors++;
			dev_kमुक्त_skb_any(skb);
			जाओ next;
		पूर्ण

		skb->protocol = eth_type_trans(skb, dev);
		napi_gro_receive(&priv->napi, skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
next:
		pos = (pos + 1) % rxq->num;
		अगर (rx_pkts_num >= limit)
			अवरोध;
	पूर्ण
	rxq->tail = pos;

	hisi_femac_rx_refill(priv);

	वापस rx_pkts_num;
पूर्ण

अटल पूर्णांक hisi_femac_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा hisi_femac_priv *priv = container_of(napi,
					काष्ठा hisi_femac_priv, napi);
	काष्ठा net_device *dev = priv->ndev;
	पूर्णांक work_करोne = 0, task = budget;
	पूर्णांक पूर्णांकs, num;

	करो अणु
		hisi_femac_xmit_reclaim(dev);
		num = hisi_femac_rx(dev, task);
		work_करोne += num;
		task -= num;
		अगर (work_करोne >= budget)
			अवरोध;

		पूर्णांकs = पढ़ोl(priv->glb_base + GLB_IRQ_RAW);
		ग_लिखोl(पूर्णांकs & DEF_INT_MASK,
		       priv->glb_base + GLB_IRQ_RAW);
	पूर्ण जबतक (पूर्णांकs & DEF_INT_MASK);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		hisi_femac_irq_enable(priv, DEF_INT_MASK &
					(~IRQ_INT_TX_PER_PACKET));
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल irqवापस_t hisi_femac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक पूर्णांकs;
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा hisi_femac_priv *priv = netdev_priv(dev);

	पूर्णांकs = पढ़ोl(priv->glb_base + GLB_IRQ_RAW);

	अगर (likely(पूर्णांकs & DEF_INT_MASK)) अणु
		ग_लिखोl(पूर्णांकs & DEF_INT_MASK,
		       priv->glb_base + GLB_IRQ_RAW);
		hisi_femac_irq_disable(priv, DEF_INT_MASK);
		napi_schedule(&priv->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hisi_femac_init_queue(काष्ठा device *dev,
				 काष्ठा hisi_femac_queue *queue,
				 अचिन्हित पूर्णांक num)
अणु
	queue->skb = devm_kसुस्मृति(dev, num, माप(काष्ठा sk_buff *),
				  GFP_KERNEL);
	अगर (!queue->skb)
		वापस -ENOMEM;

	queue->dma_phys = devm_kसुस्मृति(dev, num, माप(dma_addr_t),
				       GFP_KERNEL);
	अगर (!queue->dma_phys)
		वापस -ENOMEM;

	queue->num = num;
	queue->head = 0;
	queue->tail = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_femac_init_tx_and_rx_queues(काष्ठा hisi_femac_priv *priv)
अणु
	पूर्णांक ret;

	ret = hisi_femac_init_queue(priv->dev, &priv->txq, TXQ_NUM);
	अगर (ret)
		वापस ret;

	ret = hisi_femac_init_queue(priv->dev, &priv->rxq, RXQ_NUM);
	अगर (ret)
		वापस ret;

	priv->tx_fअगरo_used_cnt = 0;

	वापस 0;
पूर्ण

अटल व्योम hisi_femac_मुक्त_skb_rings(काष्ठा hisi_femac_priv *priv)
अणु
	काष्ठा hisi_femac_queue *txq = &priv->txq;
	काष्ठा hisi_femac_queue *rxq = &priv->rxq;
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;
	u32 pos;

	pos = rxq->tail;
	जबतक (pos != rxq->head) अणु
		skb = rxq->skb[pos];
		अगर (unlikely(!skb)) अणु
			netdev_err(priv->ndev, "NULL rx skb. pos=%d, head=%d\n",
				   pos, rxq->head);
			जारी;
		पूर्ण

		dma_addr = rxq->dma_phys[pos];
		dma_unmap_single(priv->dev, dma_addr, MAX_FRAME_SIZE,
				 DMA_FROM_DEVICE);

		dev_kमुक्त_skb_any(skb);
		rxq->skb[pos] = शून्य;
		pos = (pos + 1) % rxq->num;
	पूर्ण
	rxq->tail = pos;

	pos = txq->tail;
	जबतक (pos != txq->head) अणु
		skb = txq->skb[pos];
		अगर (unlikely(!skb)) अणु
			netdev_err(priv->ndev, "NULL tx skb. pos=%d, head=%d\n",
				   pos, txq->head);
			जारी;
		पूर्ण
		hisi_femac_tx_dma_unmap(priv, skb, pos);
		dev_kमुक्त_skb_any(skb);
		txq->skb[pos] = शून्य;
		pos = (pos + 1) % txq->num;
	पूर्ण
	txq->tail = pos;
	priv->tx_fअगरo_used_cnt = 0;
पूर्ण

अटल पूर्णांक hisi_femac_set_hw_mac_addr(काष्ठा hisi_femac_priv *priv,
				      अचिन्हित अक्षर *mac)
अणु
	u32 reg;

	reg = mac[1] | (mac[0] << 8);
	ग_लिखोl(reg, priv->glb_base + GLB_HOSTMAC_H16);

	reg = mac[5] | (mac[4] << 8) | (mac[3] << 16) | (mac[2] << 24);
	ग_लिखोl(reg, priv->glb_base + GLB_HOSTMAC_L32);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_femac_port_reset(काष्ठा hisi_femac_priv *priv)
अणु
	u32 val;

	val = पढ़ोl(priv->glb_base + GLB_SOFT_RESET);
	val |= SOFT_RESET_ALL;
	ग_लिखोl(val, priv->glb_base + GLB_SOFT_RESET);

	usleep_range(500, 800);

	val &= ~SOFT_RESET_ALL;
	ग_लिखोl(val, priv->glb_base + GLB_SOFT_RESET);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_femac_net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा hisi_femac_priv *priv = netdev_priv(dev);

	hisi_femac_port_reset(priv);
	hisi_femac_set_hw_mac_addr(priv, dev->dev_addr);
	hisi_femac_rx_refill(priv);

	netअगर_carrier_off(dev);
	netdev_reset_queue(dev);
	netअगर_start_queue(dev);
	napi_enable(&priv->napi);

	priv->link_status = 0;
	अगर (dev->phydev)
		phy_start(dev->phydev);

	ग_लिखोl(IRQ_ENA_PORT0_MASK, priv->glb_base + GLB_IRQ_RAW);
	hisi_femac_irq_enable(priv, IRQ_ENA_ALL | IRQ_ENA_PORT0 | DEF_INT_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_femac_net_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा hisi_femac_priv *priv = netdev_priv(dev);

	hisi_femac_irq_disable(priv, IRQ_ENA_PORT0);

	अगर (dev->phydev)
		phy_stop(dev->phydev);

	netअगर_stop_queue(dev);
	napi_disable(&priv->napi);

	hisi_femac_मुक्त_skb_rings(priv);

	वापस 0;
पूर्ण

अटल netdev_tx_t hisi_femac_net_xmit(काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev)
अणु
	काष्ठा hisi_femac_priv *priv = netdev_priv(dev);
	काष्ठा hisi_femac_queue *txq = &priv->txq;
	dma_addr_t addr;
	u32 val;

	val = पढ़ोl(priv->port_base + ADDRQ_STAT);
	val &= BIT_TX_READY;
	अगर (!val) अणु
		hisi_femac_irq_enable(priv, IRQ_INT_TX_PER_PACKET);
		dev->stats.tx_dropped++;
		dev->stats.tx_fअगरo_errors++;
		netअगर_stop_queue(dev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (unlikely(!CIRC_SPACE(txq->head, txq->tail,
				 txq->num))) अणु
		hisi_femac_irq_enable(priv, IRQ_INT_TX_PER_PACKET);
		dev->stats.tx_dropped++;
		dev->stats.tx_fअगरo_errors++;
		netअगर_stop_queue(dev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	addr = dma_map_single(priv->dev, skb->data,
			      skb->len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(priv->dev, addr))) अणु
		dev_kमुक्त_skb_any(skb);
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण
	txq->dma_phys[txq->head] = addr;

	txq->skb[txq->head] = skb;
	txq->head = (txq->head + 1) % txq->num;

	ग_लिखोl(addr, priv->port_base + EQ_ADDR);
	ग_लिखोl(skb->len + ETH_FCS_LEN, priv->port_base + EQFRM_LEN);

	priv->tx_fअगरo_used_cnt++;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;
	netdev_sent_queue(dev, skb->len);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक hisi_femac_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा hisi_femac_priv *priv = netdev_priv(dev);
	काष्ठा sockaddr *skaddr = p;

	अगर (!is_valid_ether_addr(skaddr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, skaddr->sa_data, dev->addr_len);
	dev->addr_assign_type &= ~NET_ADDR_RANDOM;

	hisi_femac_set_hw_mac_addr(priv, dev->dev_addr);

	वापस 0;
पूर्ण

अटल व्योम hisi_femac_enable_hw_addr_filter(काष्ठा hisi_femac_priv *priv,
					     अचिन्हित पूर्णांक reg_n, bool enable)
अणु
	u32 val;

	val = पढ़ोl(priv->glb_base + GLB_MAC_H16(reg_n));
	अगर (enable)
		val |= BIT_MACFLT_ENA;
	अन्यथा
		val &= ~BIT_MACFLT_ENA;
	ग_लिखोl(val, priv->glb_base + GLB_MAC_H16(reg_n));
पूर्ण

अटल व्योम hisi_femac_set_hw_addr_filter(काष्ठा hisi_femac_priv *priv,
					  अचिन्हित अक्षर *addr,
					  अचिन्हित पूर्णांक reg_n)
अणु
	अचिन्हित पूर्णांक high, low;
	u32 val;

	high = GLB_MAC_H16(reg_n);
	low = GLB_MAC_L32(reg_n);

	val = (addr[2] << 24) | (addr[3] << 16) | (addr[4] << 8) | addr[5];
	ग_लिखोl(val, priv->glb_base + low);

	val = पढ़ोl(priv->glb_base + high);
	val &= ~MACFLT_HI16_MASK;
	val |= ((addr[0] << 8) | addr[1]);
	val |= (BIT_MACFLT_ENA | BIT_MACFLT_FW2CPU);
	ग_लिखोl(val, priv->glb_base + high);
पूर्ण

अटल व्योम hisi_femac_set_promisc_mode(काष्ठा hisi_femac_priv *priv,
					bool promisc_mode)
अणु
	u32 val;

	val = पढ़ोl(priv->glb_base + GLB_FWCTRL);
	अगर (promisc_mode)
		val |= FWCTRL_FWALL2CPU;
	अन्यथा
		val &= ~FWCTRL_FWALL2CPU;
	ग_लिखोl(val, priv->glb_base + GLB_FWCTRL);
पूर्ण

/* Handle multiple multicast addresses (perfect filtering)*/
अटल व्योम hisi_femac_set_mc_addr_filter(काष्ठा hisi_femac_priv *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	u32 val;

	val = पढ़ोl(priv->glb_base + GLB_MACTCTRL);
	अगर ((netdev_mc_count(dev) > MAX_MULTICAST_ADDRESSES) ||
	    (dev->flags & IFF_ALLMULTI)) अणु
		val |= MACTCTRL_MULTI2CPU;
	पूर्ण अन्यथा अणु
		पूर्णांक reg = MAX_UNICAST_ADDRESSES;
		पूर्णांक i;
		काष्ठा netdev_hw_addr *ha;

		क्रम (i = reg; i < MAX_MAC_FILTER_NUM; i++)
			hisi_femac_enable_hw_addr_filter(priv, i, false);

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			hisi_femac_set_hw_addr_filter(priv, ha->addr, reg);
			reg++;
		पूर्ण
		val &= ~MACTCTRL_MULTI2CPU;
	पूर्ण
	ग_लिखोl(val, priv->glb_base + GLB_MACTCTRL);
पूर्ण

/* Handle multiple unicast addresses (perfect filtering)*/
अटल व्योम hisi_femac_set_uc_addr_filter(काष्ठा hisi_femac_priv *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	u32 val;

	val = पढ़ोl(priv->glb_base + GLB_MACTCTRL);
	अगर (netdev_uc_count(dev) > MAX_UNICAST_ADDRESSES) अणु
		val |= MACTCTRL_UNI2CPU;
	पूर्ण अन्यथा अणु
		पूर्णांक reg = 0;
		पूर्णांक i;
		काष्ठा netdev_hw_addr *ha;

		क्रम (i = reg; i < MAX_UNICAST_ADDRESSES; i++)
			hisi_femac_enable_hw_addr_filter(priv, i, false);

		netdev_क्रम_each_uc_addr(ha, dev) अणु
			hisi_femac_set_hw_addr_filter(priv, ha->addr, reg);
			reg++;
		पूर्ण
		val &= ~MACTCTRL_UNI2CPU;
	पूर्ण
	ग_लिखोl(val, priv->glb_base + GLB_MACTCTRL);
पूर्ण

अटल व्योम hisi_femac_net_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा hisi_femac_priv *priv = netdev_priv(dev);

	अगर (dev->flags & IFF_PROMISC) अणु
		hisi_femac_set_promisc_mode(priv, true);
	पूर्ण अन्यथा अणु
		hisi_femac_set_promisc_mode(priv, false);
		hisi_femac_set_mc_addr_filter(priv);
		hisi_femac_set_uc_addr_filter(priv);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops hisi_femac_ethtools_ops = अणु
	.get_link		= ethtool_op_get_link,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops hisi_femac_netdev_ops = अणु
	.nकरो_खोलो		= hisi_femac_net_खोलो,
	.nकरो_stop		= hisi_femac_net_बंद,
	.nकरो_start_xmit		= hisi_femac_net_xmit,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_set_mac_address	= hisi_femac_set_mac_address,
	.nकरो_set_rx_mode	= hisi_femac_net_set_rx_mode,
पूर्ण;

अटल व्योम hisi_femac_core_reset(काष्ठा hisi_femac_priv *priv)
अणु
	reset_control_निश्चित(priv->mac_rst);
	reset_control_deनिश्चित(priv->mac_rst);
पूर्ण

अटल व्योम hisi_femac_sleep_us(u32 समय_us)
अणु
	u32 समय_ms;

	अगर (!समय_us)
		वापस;

	समय_ms = DIV_ROUND_UP(समय_us, 1000);
	अगर (समय_ms < 20)
		usleep_range(समय_us, समय_us + 500);
	अन्यथा
		msleep(समय_ms);
पूर्ण

अटल व्योम hisi_femac_phy_reset(काष्ठा hisi_femac_priv *priv)
अणु
	/* To make sure PHY hardware reset success,
	 * we must keep PHY in deनिश्चित state first and
	 * then complete the hardware reset operation
	 */
	reset_control_deनिश्चित(priv->phy_rst);
	hisi_femac_sleep_us(priv->phy_reset_delays[PRE_DELAY]);

	reset_control_निश्चित(priv->phy_rst);
	/* delay some समय to ensure reset ok,
	 * this depends on PHY hardware feature
	 */
	hisi_femac_sleep_us(priv->phy_reset_delays[PULSE]);
	reset_control_deनिश्चित(priv->phy_rst);
	/* delay some समय to ensure later MDIO access */
	hisi_femac_sleep_us(priv->phy_reset_delays[POST_DELAY]);
पूर्ण

अटल व्योम hisi_femac_port_init(काष्ठा hisi_femac_priv *priv)
अणु
	u32 val;

	/* MAC माला_लो link status info and phy mode by software config */
	val = MAC_PORTSEL_STAT_CPU;
	अगर (priv->ndev->phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RMII)
		val |= MAC_PORTSEL_RMII;
	ग_लिखोl(val, priv->port_base + MAC_PORTSEL);

	/*clear all पूर्णांकerrupt status */
	ग_लिखोl(IRQ_ENA_PORT0_MASK, priv->glb_base + GLB_IRQ_RAW);
	hisi_femac_irq_disable(priv, IRQ_ENA_PORT0_MASK | IRQ_ENA_PORT0);

	val = पढ़ोl(priv->glb_base + GLB_FWCTRL);
	val &= ~(FWCTRL_VLAN_ENABLE | FWCTRL_FWALL2CPU);
	val |= FWCTRL_FW2CPU_ENA;
	ग_लिखोl(val, priv->glb_base + GLB_FWCTRL);

	val = पढ़ोl(priv->glb_base + GLB_MACTCTRL);
	val |= (MACTCTRL_BROAD2CPU | MACTCTRL_MACT_ENA);
	ग_लिखोl(val, priv->glb_base + GLB_MACTCTRL);

	val = पढ़ोl(priv->port_base + MAC_SET);
	val &= ~MAX_FRAME_SIZE_MASK;
	val |= MAX_FRAME_SIZE;
	ग_लिखोl(val, priv->port_base + MAC_SET);

	val = RX_COALESCED_TIMER |
		(RX_COALESCED_FRAMES << RX_COALESCED_FRAME_OFFSET);
	ग_लिखोl(val, priv->port_base + RX_COALESCE_SET);

	val = (HW_RX_FIFO_DEPTH << RX_DEPTH_OFFSET) | HW_TX_FIFO_DEPTH;
	ग_लिखोl(val, priv->port_base + QLEN_SET);
पूर्ण

अटल पूर्णांक hisi_femac_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा net_device *ndev;
	काष्ठा hisi_femac_priv *priv;
	काष्ठा phy_device *phy;
	पूर्णांक ret;

	ndev = alloc_etherdev(माप(*priv));
	अगर (!ndev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);

	priv = netdev_priv(ndev);
	priv->dev = dev;
	priv->ndev = ndev;

	priv->port_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->port_base)) अणु
		ret = PTR_ERR(priv->port_base);
		जाओ out_मुक्त_netdev;
	पूर्ण

	priv->glb_base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(priv->glb_base)) अणु
		ret = PTR_ERR(priv->glb_base);
		जाओ out_मुक्त_netdev;
	पूर्ण

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "failed to get clk\n");
		ret = -ENODEV;
		जाओ out_मुक्त_netdev;
	पूर्ण

	ret = clk_prepare_enable(priv->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clk %d\n", ret);
		जाओ out_मुक्त_netdev;
	पूर्ण

	priv->mac_rst = devm_reset_control_get(dev, "mac");
	अगर (IS_ERR(priv->mac_rst)) अणु
		ret = PTR_ERR(priv->mac_rst);
		जाओ out_disable_clk;
	पूर्ण
	hisi_femac_core_reset(priv);

	priv->phy_rst = devm_reset_control_get(dev, "phy");
	अगर (IS_ERR(priv->phy_rst)) अणु
		priv->phy_rst = शून्य;
	पूर्ण अन्यथा अणु
		ret = of_property_पढ़ो_u32_array(node,
						 PHY_RESET_DELAYS_PROPERTY,
						 priv->phy_reset_delays,
						 DELAYS_NUM);
		अगर (ret)
			जाओ out_disable_clk;
		hisi_femac_phy_reset(priv);
	पूर्ण

	phy = of_phy_get_and_connect(ndev, node, hisi_femac_adjust_link);
	अगर (!phy) अणु
		dev_err(dev, "connect to PHY failed!\n");
		ret = -ENODEV;
		जाओ out_disable_clk;
	पूर्ण

	phy_attached_prपूर्णांक(phy, "phy_id=0x%.8lx, phy_mode=%s\n",
			   (अचिन्हित दीर्घ)phy->phy_id,
			   phy_modes(phy->पूर्णांकerface));

	ret = of_get_mac_address(node, ndev->dev_addr);
	अगर (ret) अणु
		eth_hw_addr_अक्रमom(ndev);
		dev_warn(dev, "using random MAC address %pM\n",
			 ndev->dev_addr);
	पूर्ण

	ndev->watchकरोg_समयo = 6 * HZ;
	ndev->priv_flags |= IFF_UNICAST_FLT;
	ndev->netdev_ops = &hisi_femac_netdev_ops;
	ndev->ethtool_ops = &hisi_femac_ethtools_ops;
	netअगर_napi_add(ndev, &priv->napi, hisi_femac_poll, FEMAC_POLL_WEIGHT);

	hisi_femac_port_init(priv);

	ret = hisi_femac_init_tx_and_rx_queues(priv);
	अगर (ret)
		जाओ out_disconnect_phy;

	ndev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ndev->irq <= 0) अणु
		ret = -ENODEV;
		जाओ out_disconnect_phy;
	पूर्ण

	ret = devm_request_irq(dev, ndev->irq, hisi_femac_पूर्णांकerrupt,
			       IRQF_SHARED, pdev->name, ndev);
	अगर (ret) अणु
		dev_err(dev, "devm_request_irq %d failed!\n", ndev->irq);
		जाओ out_disconnect_phy;
	पूर्ण

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		dev_err(dev, "register_netdev failed!\n");
		जाओ out_disconnect_phy;
	पूर्ण

	वापस ret;

out_disconnect_phy:
	netअगर_napi_del(&priv->napi);
	phy_disconnect(phy);
out_disable_clk:
	clk_disable_unprepare(priv->clk);
out_मुक्त_netdev:
	मुक्त_netdev(ndev);

	वापस ret;
पूर्ण

अटल पूर्णांक hisi_femac_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा hisi_femac_priv *priv = netdev_priv(ndev);

	netअगर_napi_del(&priv->napi);
	unरेजिस्टर_netdev(ndev);

	phy_disconnect(ndev->phydev);
	clk_disable_unprepare(priv->clk);
	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक hisi_femac_drv_suspend(काष्ठा platक्रमm_device *pdev,
				  pm_message_t state)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा hisi_femac_priv *priv = netdev_priv(ndev);

	disable_irq(ndev->irq);
	अगर (netअगर_running(ndev)) अणु
		hisi_femac_net_बंद(ndev);
		netअगर_device_detach(ndev);
	पूर्ण

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_femac_drv_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा hisi_femac_priv *priv = netdev_priv(ndev);

	clk_prepare_enable(priv->clk);
	अगर (priv->phy_rst)
		hisi_femac_phy_reset(priv);

	अगर (netअगर_running(ndev)) अणु
		hisi_femac_port_init(priv);
		hisi_femac_net_खोलो(ndev);
		netअगर_device_attach(ndev);
	पूर्ण
	enable_irq(ndev->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id hisi_femac_match[] = अणु
	अणु.compatible = "hisilicon,hisi-femac-v1",पूर्ण,
	अणु.compatible = "hisilicon,hisi-femac-v2",पूर्ण,
	अणु.compatible = "hisilicon,hi3516cv300-femac",पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, hisi_femac_match);

अटल काष्ठा platक्रमm_driver hisi_femac_driver = अणु
	.driver = अणु
		.name = "hisi-femac",
		.of_match_table = hisi_femac_match,
	पूर्ण,
	.probe = hisi_femac_drv_probe,
	.हटाओ = hisi_femac_drv_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend = hisi_femac_drv_suspend,
	.resume = hisi_femac_drv_resume,
#पूर्ण_अगर
पूर्ण;

module_platक्रमm_driver(hisi_femac_driver);

MODULE_DESCRIPTION("Hisilicon Fast Ethernet MAC driver");
MODULE_AUTHOR("Dongpo Li <lidongpo@hisilicon.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:hisi-femac");
