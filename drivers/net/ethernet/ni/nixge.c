<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2016-2017, National Instruments Corp.
 *
 * Author: Moritz Fischer <mdf@kernel.org>
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/phy.h>
#समावेश <linux/mii.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/iopoll.h>

#घोषणा TX_BD_NUM		64
#घोषणा RX_BD_NUM		128

/* Axi DMA Register definitions */
#घोषणा XAXIDMA_TX_CR_OFFSET	0x00 /* Channel control */
#घोषणा XAXIDMA_TX_SR_OFFSET	0x04 /* Status */
#घोषणा XAXIDMA_TX_CDESC_OFFSET	0x08 /* Current descriptor poपूर्णांकer */
#घोषणा XAXIDMA_TX_TDESC_OFFSET	0x10 /* Tail descriptor poपूर्णांकer */

#घोषणा XAXIDMA_RX_CR_OFFSET	0x30 /* Channel control */
#घोषणा XAXIDMA_RX_SR_OFFSET	0x34 /* Status */
#घोषणा XAXIDMA_RX_CDESC_OFFSET	0x38 /* Current descriptor poपूर्णांकer */
#घोषणा XAXIDMA_RX_TDESC_OFFSET	0x40 /* Tail descriptor poपूर्णांकer */

#घोषणा XAXIDMA_CR_RUNSTOP_MASK	0x1 /* Start/stop DMA channel */
#घोषणा XAXIDMA_CR_RESET_MASK	0x4 /* Reset DMA engine */

#घोषणा XAXIDMA_BD_CTRL_LENGTH_MASK	0x007FFFFF /* Requested len */
#घोषणा XAXIDMA_BD_CTRL_TXSOF_MASK	0x08000000 /* First tx packet */
#घोषणा XAXIDMA_BD_CTRL_TXखातापूर्ण_MASK	0x04000000 /* Last tx packet */
#घोषणा XAXIDMA_BD_CTRL_ALL_MASK	0x0C000000 /* All control bits */

#घोषणा XAXIDMA_DELAY_MASK		0xFF000000 /* Delay समयout counter */
#घोषणा XAXIDMA_COALESCE_MASK		0x00FF0000 /* Coalesce counter */

#घोषणा XAXIDMA_DELAY_SHIFT		24
#घोषणा XAXIDMA_COALESCE_SHIFT		16

#घोषणा XAXIDMA_IRQ_IOC_MASK		0x00001000 /* Completion पूर्णांकr */
#घोषणा XAXIDMA_IRQ_DELAY_MASK		0x00002000 /* Delay पूर्णांकerrupt */
#घोषणा XAXIDMA_IRQ_ERROR_MASK		0x00004000 /* Error पूर्णांकerrupt */
#घोषणा XAXIDMA_IRQ_ALL_MASK		0x00007000 /* All पूर्णांकerrupts */

/* Default TX/RX Threshold and रुकोbound values क्रम SGDMA mode */
#घोषणा XAXIDMA_DFT_TX_THRESHOLD	24
#घोषणा XAXIDMA_DFT_TX_WAITBOUND	254
#घोषणा XAXIDMA_DFT_RX_THRESHOLD	24
#घोषणा XAXIDMA_DFT_RX_WAITBOUND	254

#घोषणा XAXIDMA_BD_STS_ACTUAL_LEN_MASK	0x007FFFFF /* Actual len */
#घोषणा XAXIDMA_BD_STS_COMPLETE_MASK	0x80000000 /* Completed */
#घोषणा XAXIDMA_BD_STS_DEC_ERR_MASK	0x40000000 /* Decode error */
#घोषणा XAXIDMA_BD_STS_SLV_ERR_MASK	0x20000000 /* Slave error */
#घोषणा XAXIDMA_BD_STS_INT_ERR_MASK	0x10000000 /* Internal err */
#घोषणा XAXIDMA_BD_STS_ALL_ERR_MASK	0x70000000 /* All errors */
#घोषणा XAXIDMA_BD_STS_RXSOF_MASK	0x08000000 /* First rx pkt */
#घोषणा XAXIDMA_BD_STS_RXखातापूर्ण_MASK	0x04000000 /* Last rx pkt */
#घोषणा XAXIDMA_BD_STS_ALL_MASK		0xFC000000 /* All status bits */

#घोषणा NIXGE_REG_CTRL_OFFSET	0x4000
#घोषणा NIXGE_REG_INFO		0x00
#घोषणा NIXGE_REG_MAC_CTL	0x04
#घोषणा NIXGE_REG_PHY_CTL	0x08
#घोषणा NIXGE_REG_LED_CTL	0x0c
#घोषणा NIXGE_REG_MDIO_DATA	0x10
#घोषणा NIXGE_REG_MDIO_ADDR	0x14
#घोषणा NIXGE_REG_MDIO_OP	0x18
#घोषणा NIXGE_REG_MDIO_CTRL	0x1c

#घोषणा NIXGE_ID_LED_CTL_EN	BIT(0)
#घोषणा NIXGE_ID_LED_CTL_VAL	BIT(1)

#घोषणा NIXGE_MDIO_CLAUSE45	BIT(12)
#घोषणा NIXGE_MDIO_CLAUSE22	0
#घोषणा NIXGE_MDIO_OP(n)     (((n) & 0x3) << 10)
#घोषणा NIXGE_MDIO_OP_ADDRESS	0
#घोषणा NIXGE_MDIO_C45_WRITE	BIT(0)
#घोषणा NIXGE_MDIO_C45_READ	(BIT(1) | BIT(0))
#घोषणा NIXGE_MDIO_C22_WRITE	BIT(0)
#घोषणा NIXGE_MDIO_C22_READ	BIT(1)
#घोषणा NIXGE_MDIO_ADDR(n)   (((n) & 0x1f) << 5)
#घोषणा NIXGE_MDIO_MMD(n)    (((n) & 0x1f) << 0)

#घोषणा NIXGE_REG_MAC_LSB	0x1000
#घोषणा NIXGE_REG_MAC_MSB	0x1004

/* Packet size info */
#घोषणा NIXGE_HDR_SIZE		14 /* Size of Ethernet header */
#घोषणा NIXGE_TRL_SIZE		4 /* Size of Ethernet trailer (FCS) */
#घोषणा NIXGE_MTU		1500 /* Max MTU of an Ethernet frame */
#घोषणा NIXGE_JUMBO_MTU		9000 /* Max MTU of a jumbo Eth. frame */

#घोषणा NIXGE_MAX_FRAME_SIZE	 (NIXGE_MTU + NIXGE_HDR_SIZE + NIXGE_TRL_SIZE)
#घोषणा NIXGE_MAX_JUMBO_FRAME_SIZE \
	(NIXGE_JUMBO_MTU + NIXGE_HDR_SIZE + NIXGE_TRL_SIZE)

क्रमागत nixge_version अणु
	NIXGE_V2,
	NIXGE_V3,
	NIXGE_VERSION_COUNT
पूर्ण;

काष्ठा nixge_hw_dma_bd अणु
	u32 next_lo;
	u32 next_hi;
	u32 phys_lo;
	u32 phys_hi;
	u32 reserved3;
	u32 reserved4;
	u32 cntrl;
	u32 status;
	u32 app0;
	u32 app1;
	u32 app2;
	u32 app3;
	u32 app4;
	u32 sw_id_offset_lo;
	u32 sw_id_offset_hi;
	u32 reserved6;
पूर्ण;

#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
#घोषणा nixge_hw_dma_bd_set_addr(bd, field, addr) \
	करो अणु \
		(bd)->field##_lo = lower_32_bits((addr)); \
		(bd)->field##_hi = upper_32_bits((addr)); \
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा nixge_hw_dma_bd_set_addr(bd, field, addr) \
	((bd)->field##_lo = lower_32_bits((addr)))
#पूर्ण_अगर

#घोषणा nixge_hw_dma_bd_set_phys(bd, addr) \
	nixge_hw_dma_bd_set_addr((bd), phys, (addr))

#घोषणा nixge_hw_dma_bd_set_next(bd, addr) \
	nixge_hw_dma_bd_set_addr((bd), next, (addr))

#घोषणा nixge_hw_dma_bd_set_offset(bd, addr) \
	nixge_hw_dma_bd_set_addr((bd), sw_id_offset, (addr))

#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
#घोषणा nixge_hw_dma_bd_get_addr(bd, field) \
	(dma_addr_t)((((u64)(bd)->field##_hi) << 32) | ((bd)->field##_lo))
#अन्यथा
#घोषणा nixge_hw_dma_bd_get_addr(bd, field) \
	(dma_addr_t)((bd)->field##_lo)
#पूर्ण_अगर

काष्ठा nixge_tx_skb अणु
	काष्ठा sk_buff *skb;
	dma_addr_t mapping;
	माप_प्रकार size;
	bool mapped_as_page;
पूर्ण;

काष्ठा nixge_priv अणु
	काष्ठा net_device *ndev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा device *dev;

	/* Connection to PHY device */
	काष्ठा device_node *phy_node;
	phy_पूर्णांकerface_t		phy_mode;

	पूर्णांक link;
	अचिन्हित पूर्णांक speed;
	अचिन्हित पूर्णांक duplex;

	/* MDIO bus data */
	काष्ठा mii_bus *mii_bus;	/* MII bus reference */

	/* IO रेजिस्टरs, dma functions and IRQs */
	व्योम __iomem *ctrl_regs;
	व्योम __iomem *dma_regs;

	काष्ठा tasklet_काष्ठा dma_err_tasklet;

	पूर्णांक tx_irq;
	पूर्णांक rx_irq;

	/* Buffer descriptors */
	काष्ठा nixge_hw_dma_bd *tx_bd_v;
	काष्ठा nixge_tx_skb *tx_skb;
	dma_addr_t tx_bd_p;

	काष्ठा nixge_hw_dma_bd *rx_bd_v;
	dma_addr_t rx_bd_p;
	u32 tx_bd_ci;
	u32 tx_bd_tail;
	u32 rx_bd_ci;

	u32 coalesce_count_rx;
	u32 coalesce_count_tx;
पूर्ण;

अटल व्योम nixge_dma_ग_लिखो_reg(काष्ठा nixge_priv *priv, off_t offset, u32 val)
अणु
	ग_लिखोl(val, priv->dma_regs + offset);
पूर्ण

अटल व्योम nixge_dma_ग_लिखो_desc_reg(काष्ठा nixge_priv *priv, off_t offset,
				     dma_addr_t addr)
अणु
	ग_लिखोl(lower_32_bits(addr), priv->dma_regs + offset);
#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
	ग_लिखोl(upper_32_bits(addr), priv->dma_regs + offset + 4);
#पूर्ण_अगर
पूर्ण

अटल u32 nixge_dma_पढ़ो_reg(स्थिर काष्ठा nixge_priv *priv, off_t offset)
अणु
	वापस पढ़ोl(priv->dma_regs + offset);
पूर्ण

अटल व्योम nixge_ctrl_ग_लिखो_reg(काष्ठा nixge_priv *priv, off_t offset, u32 val)
अणु
	ग_लिखोl(val, priv->ctrl_regs + offset);
पूर्ण

अटल u32 nixge_ctrl_पढ़ो_reg(काष्ठा nixge_priv *priv, off_t offset)
अणु
	वापस पढ़ोl(priv->ctrl_regs + offset);
पूर्ण

#घोषणा nixge_ctrl_poll_समयout(priv, addr, val, cond, sleep_us, समयout_us) \
	पढ़ोl_poll_समयout((priv)->ctrl_regs + (addr), (val), (cond), \
			   (sleep_us), (समयout_us))

#घोषणा nixge_dma_poll_समयout(priv, addr, val, cond, sleep_us, समयout_us) \
	पढ़ोl_poll_समयout((priv)->dma_regs + (addr), (val), (cond), \
			   (sleep_us), (समयout_us))

अटल व्योम nixge_hw_dma_bd_release(काष्ठा net_device *ndev)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(ndev);
	dma_addr_t phys_addr;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < RX_BD_NUM; i++) अणु
		phys_addr = nixge_hw_dma_bd_get_addr(&priv->rx_bd_v[i],
						     phys);

		dma_unmap_single(ndev->dev.parent, phys_addr,
				 NIXGE_MAX_JUMBO_FRAME_SIZE,
				 DMA_FROM_DEVICE);

		skb = (काष्ठा sk_buff *)(uपूर्णांकptr_t)
			nixge_hw_dma_bd_get_addr(&priv->rx_bd_v[i],
						 sw_id_offset);
		dev_kमुक्त_skb(skb);
	पूर्ण

	अगर (priv->rx_bd_v)
		dma_मुक्त_coherent(ndev->dev.parent,
				  माप(*priv->rx_bd_v) * RX_BD_NUM,
				  priv->rx_bd_v,
				  priv->rx_bd_p);

	अगर (priv->tx_skb)
		devm_kमुक्त(ndev->dev.parent, priv->tx_skb);

	अगर (priv->tx_bd_v)
		dma_मुक्त_coherent(ndev->dev.parent,
				  माप(*priv->tx_bd_v) * TX_BD_NUM,
				  priv->tx_bd_v,
				  priv->tx_bd_p);
पूर्ण

अटल पूर्णांक nixge_hw_dma_bd_init(काष्ठा net_device *ndev)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(ndev);
	काष्ठा sk_buff *skb;
	dma_addr_t phys;
	u32 cr;
	पूर्णांक i;

	/* Reset the indexes which are used क्रम accessing the BDs */
	priv->tx_bd_ci = 0;
	priv->tx_bd_tail = 0;
	priv->rx_bd_ci = 0;

	/* Allocate the Tx and Rx buffer descriptors. */
	priv->tx_bd_v = dma_alloc_coherent(ndev->dev.parent,
					   माप(*priv->tx_bd_v) * TX_BD_NUM,
					   &priv->tx_bd_p, GFP_KERNEL);
	अगर (!priv->tx_bd_v)
		जाओ out;

	priv->tx_skb = devm_kसुस्मृति(ndev->dev.parent,
				    TX_BD_NUM, माप(*priv->tx_skb),
				    GFP_KERNEL);
	अगर (!priv->tx_skb)
		जाओ out;

	priv->rx_bd_v = dma_alloc_coherent(ndev->dev.parent,
					   माप(*priv->rx_bd_v) * RX_BD_NUM,
					   &priv->rx_bd_p, GFP_KERNEL);
	अगर (!priv->rx_bd_v)
		जाओ out;

	क्रम (i = 0; i < TX_BD_NUM; i++) अणु
		nixge_hw_dma_bd_set_next(&priv->tx_bd_v[i],
					 priv->tx_bd_p +
					 माप(*priv->tx_bd_v) *
					 ((i + 1) % TX_BD_NUM));
	पूर्ण

	क्रम (i = 0; i < RX_BD_NUM; i++) अणु
		nixge_hw_dma_bd_set_next(&priv->rx_bd_v[i],
					 priv->rx_bd_p
					 + माप(*priv->rx_bd_v) *
					 ((i + 1) % RX_BD_NUM));

		skb = netdev_alloc_skb_ip_align(ndev,
						NIXGE_MAX_JUMBO_FRAME_SIZE);
		अगर (!skb)
			जाओ out;

		nixge_hw_dma_bd_set_offset(&priv->rx_bd_v[i], (uपूर्णांकptr_t)skb);
		phys = dma_map_single(ndev->dev.parent, skb->data,
				      NIXGE_MAX_JUMBO_FRAME_SIZE,
				      DMA_FROM_DEVICE);

		nixge_hw_dma_bd_set_phys(&priv->rx_bd_v[i], phys);

		priv->rx_bd_v[i].cntrl = NIXGE_MAX_JUMBO_FRAME_SIZE;
	पूर्ण

	/* Start updating the Rx channel control रेजिस्टर */
	cr = nixge_dma_पढ़ो_reg(priv, XAXIDMA_RX_CR_OFFSET);
	/* Update the पूर्णांकerrupt coalesce count */
	cr = ((cr & ~XAXIDMA_COALESCE_MASK) |
	      ((priv->coalesce_count_rx) << XAXIDMA_COALESCE_SHIFT));
	/* Update the delay समयr count */
	cr = ((cr & ~XAXIDMA_DELAY_MASK) |
	      (XAXIDMA_DFT_RX_WAITBOUND << XAXIDMA_DELAY_SHIFT));
	/* Enable coalesce, delay समयr and error पूर्णांकerrupts */
	cr |= XAXIDMA_IRQ_ALL_MASK;
	/* Write to the Rx channel control रेजिस्टर */
	nixge_dma_ग_लिखो_reg(priv, XAXIDMA_RX_CR_OFFSET, cr);

	/* Start updating the Tx channel control रेजिस्टर */
	cr = nixge_dma_पढ़ो_reg(priv, XAXIDMA_TX_CR_OFFSET);
	/* Update the पूर्णांकerrupt coalesce count */
	cr = (((cr & ~XAXIDMA_COALESCE_MASK)) |
	      ((priv->coalesce_count_tx) << XAXIDMA_COALESCE_SHIFT));
	/* Update the delay समयr count */
	cr = (((cr & ~XAXIDMA_DELAY_MASK)) |
	      (XAXIDMA_DFT_TX_WAITBOUND << XAXIDMA_DELAY_SHIFT));
	/* Enable coalesce, delay समयr and error पूर्णांकerrupts */
	cr |= XAXIDMA_IRQ_ALL_MASK;
	/* Write to the Tx channel control रेजिस्टर */
	nixge_dma_ग_लिखो_reg(priv, XAXIDMA_TX_CR_OFFSET, cr);

	/* Populate the tail poपूर्णांकer and bring the Rx Axi DMA engine out of
	 * halted state. This will make the Rx side पढ़ोy क्रम reception.
	 */
	nixge_dma_ग_लिखो_desc_reg(priv, XAXIDMA_RX_CDESC_OFFSET, priv->rx_bd_p);
	cr = nixge_dma_पढ़ो_reg(priv, XAXIDMA_RX_CR_OFFSET);
	nixge_dma_ग_लिखो_reg(priv, XAXIDMA_RX_CR_OFFSET,
			    cr | XAXIDMA_CR_RUNSTOP_MASK);
	nixge_dma_ग_लिखो_desc_reg(priv, XAXIDMA_RX_TDESC_OFFSET, priv->rx_bd_p +
			    (माप(*priv->rx_bd_v) * (RX_BD_NUM - 1)));

	/* Write to the RS (Run-stop) bit in the Tx channel control रेजिस्टर.
	 * Tx channel is now पढ़ोy to run. But only after we ग_लिखो to the
	 * tail poपूर्णांकer रेजिस्टर that the Tx channel will start transmitting.
	 */
	nixge_dma_ग_लिखो_desc_reg(priv, XAXIDMA_TX_CDESC_OFFSET, priv->tx_bd_p);
	cr = nixge_dma_पढ़ो_reg(priv, XAXIDMA_TX_CR_OFFSET);
	nixge_dma_ग_लिखो_reg(priv, XAXIDMA_TX_CR_OFFSET,
			    cr | XAXIDMA_CR_RUNSTOP_MASK);

	वापस 0;
out:
	nixge_hw_dma_bd_release(ndev);
	वापस -ENOMEM;
पूर्ण

अटल व्योम __nixge_device_reset(काष्ठा nixge_priv *priv, off_t offset)
अणु
	u32 status;
	पूर्णांक err;

	/* Reset Axi DMA. This would reset NIXGE Ethernet core as well.
	 * The reset process of Axi DMA takes a जबतक to complete as all
	 * pending commands/transfers will be flushed or completed during
	 * this reset process.
	 */
	nixge_dma_ग_लिखो_reg(priv, offset, XAXIDMA_CR_RESET_MASK);
	err = nixge_dma_poll_समयout(priv, offset, status,
				     !(status & XAXIDMA_CR_RESET_MASK), 10,
				     1000);
	अगर (err)
		netdev_err(priv->ndev, "%s: DMA reset timeout!\n", __func__);
पूर्ण

अटल व्योम nixge_device_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(ndev);

	__nixge_device_reset(priv, XAXIDMA_TX_CR_OFFSET);
	__nixge_device_reset(priv, XAXIDMA_RX_CR_OFFSET);

	अगर (nixge_hw_dma_bd_init(ndev))
		netdev_err(ndev, "%s: descriptor allocation failed\n",
			   __func__);

	netअगर_trans_update(ndev);
पूर्ण

अटल व्योम nixge_handle_link_change(काष्ठा net_device *ndev)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;

	अगर (phydev->link != priv->link || phydev->speed != priv->speed ||
	    phydev->duplex != priv->duplex) अणु
		priv->link = phydev->link;
		priv->speed = phydev->speed;
		priv->duplex = phydev->duplex;
		phy_prपूर्णांक_status(phydev);
	पूर्ण
पूर्ण

अटल व्योम nixge_tx_skb_unmap(काष्ठा nixge_priv *priv,
			       काष्ठा nixge_tx_skb *tx_skb)
अणु
	अगर (tx_skb->mapping) अणु
		अगर (tx_skb->mapped_as_page)
			dma_unmap_page(priv->ndev->dev.parent, tx_skb->mapping,
				       tx_skb->size, DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_single(priv->ndev->dev.parent,
					 tx_skb->mapping,
					 tx_skb->size, DMA_TO_DEVICE);
		tx_skb->mapping = 0;
	पूर्ण

	अगर (tx_skb->skb) अणु
		dev_kमुक्त_skb_any(tx_skb->skb);
		tx_skb->skb = शून्य;
	पूर्ण
पूर्ण

अटल व्योम nixge_start_xmit_करोne(काष्ठा net_device *ndev)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(ndev);
	काष्ठा nixge_hw_dma_bd *cur_p;
	काष्ठा nixge_tx_skb *tx_skb;
	अचिन्हित पूर्णांक status = 0;
	u32 packets = 0;
	u32 size = 0;

	cur_p = &priv->tx_bd_v[priv->tx_bd_ci];
	tx_skb = &priv->tx_skb[priv->tx_bd_ci];

	status = cur_p->status;

	जबतक (status & XAXIDMA_BD_STS_COMPLETE_MASK) अणु
		nixge_tx_skb_unmap(priv, tx_skb);
		cur_p->status = 0;

		size += status & XAXIDMA_BD_STS_ACTUAL_LEN_MASK;
		packets++;

		++priv->tx_bd_ci;
		priv->tx_bd_ci %= TX_BD_NUM;
		cur_p = &priv->tx_bd_v[priv->tx_bd_ci];
		tx_skb = &priv->tx_skb[priv->tx_bd_ci];
		status = cur_p->status;
	पूर्ण

	ndev->stats.tx_packets += packets;
	ndev->stats.tx_bytes += size;

	अगर (packets)
		netअगर_wake_queue(ndev);
पूर्ण

अटल पूर्णांक nixge_check_tx_bd_space(काष्ठा nixge_priv *priv,
				   पूर्णांक num_frag)
अणु
	काष्ठा nixge_hw_dma_bd *cur_p;

	cur_p = &priv->tx_bd_v[(priv->tx_bd_tail + num_frag) % TX_BD_NUM];
	अगर (cur_p->status & XAXIDMA_BD_STS_ALL_MASK)
		वापस NETDEV_TX_BUSY;
	वापस 0;
पूर्ण

अटल netdev_tx_t nixge_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *ndev)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(ndev);
	काष्ठा nixge_hw_dma_bd *cur_p;
	काष्ठा nixge_tx_skb *tx_skb;
	dma_addr_t tail_p, cur_phys;
	skb_frag_t *frag;
	u32 num_frag;
	u32 ii;

	num_frag = skb_shinfo(skb)->nr_frags;
	cur_p = &priv->tx_bd_v[priv->tx_bd_tail];
	tx_skb = &priv->tx_skb[priv->tx_bd_tail];

	अगर (nixge_check_tx_bd_space(priv, num_frag)) अणु
		अगर (!netअगर_queue_stopped(ndev))
			netअगर_stop_queue(ndev);
		वापस NETDEV_TX_OK;
	पूर्ण

	cur_phys = dma_map_single(ndev->dev.parent, skb->data,
				  skb_headlen(skb), DMA_TO_DEVICE);
	अगर (dma_mapping_error(ndev->dev.parent, cur_phys))
		जाओ drop;
	nixge_hw_dma_bd_set_phys(cur_p, cur_phys);

	cur_p->cntrl = skb_headlen(skb) | XAXIDMA_BD_CTRL_TXSOF_MASK;

	tx_skb->skb = शून्य;
	tx_skb->mapping = cur_phys;
	tx_skb->size = skb_headlen(skb);
	tx_skb->mapped_as_page = false;

	क्रम (ii = 0; ii < num_frag; ii++) अणु
		++priv->tx_bd_tail;
		priv->tx_bd_tail %= TX_BD_NUM;
		cur_p = &priv->tx_bd_v[priv->tx_bd_tail];
		tx_skb = &priv->tx_skb[priv->tx_bd_tail];
		frag = &skb_shinfo(skb)->frags[ii];

		cur_phys = skb_frag_dma_map(ndev->dev.parent, frag, 0,
					    skb_frag_size(frag),
					    DMA_TO_DEVICE);
		अगर (dma_mapping_error(ndev->dev.parent, cur_phys))
			जाओ frag_err;
		nixge_hw_dma_bd_set_phys(cur_p, cur_phys);

		cur_p->cntrl = skb_frag_size(frag);

		tx_skb->skb = शून्य;
		tx_skb->mapping = cur_phys;
		tx_skb->size = skb_frag_size(frag);
		tx_skb->mapped_as_page = true;
	पूर्ण

	/* last buffer of the frame */
	tx_skb->skb = skb;

	cur_p->cntrl |= XAXIDMA_BD_CTRL_TXखातापूर्ण_MASK;

	tail_p = priv->tx_bd_p + माप(*priv->tx_bd_v) * priv->tx_bd_tail;
	/* Start the transfer */
	nixge_dma_ग_लिखो_desc_reg(priv, XAXIDMA_TX_TDESC_OFFSET, tail_p);
	++priv->tx_bd_tail;
	priv->tx_bd_tail %= TX_BD_NUM;

	वापस NETDEV_TX_OK;
frag_err:
	क्रम (; ii > 0; ii--) अणु
		अगर (priv->tx_bd_tail)
			priv->tx_bd_tail--;
		अन्यथा
			priv->tx_bd_tail = TX_BD_NUM - 1;

		tx_skb = &priv->tx_skb[priv->tx_bd_tail];
		nixge_tx_skb_unmap(priv, tx_skb);

		cur_p = &priv->tx_bd_v[priv->tx_bd_tail];
		cur_p->status = 0;
	पूर्ण
	dma_unmap_single(priv->ndev->dev.parent,
			 tx_skb->mapping,
			 tx_skb->size, DMA_TO_DEVICE);
drop:
	ndev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक nixge_recv(काष्ठा net_device *ndev, पूर्णांक budget)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(ndev);
	काष्ठा sk_buff *skb, *new_skb;
	काष्ठा nixge_hw_dma_bd *cur_p;
	dma_addr_t tail_p = 0, cur_phys = 0;
	u32 packets = 0;
	u32 length = 0;
	u32 size = 0;

	cur_p = &priv->rx_bd_v[priv->rx_bd_ci];

	जबतक ((cur_p->status & XAXIDMA_BD_STS_COMPLETE_MASK &&
		budget > packets)) अणु
		tail_p = priv->rx_bd_p + माप(*priv->rx_bd_v) *
			 priv->rx_bd_ci;

		skb = (काष्ठा sk_buff *)(uपूर्णांकptr_t)
			nixge_hw_dma_bd_get_addr(cur_p, sw_id_offset);

		length = cur_p->status & XAXIDMA_BD_STS_ACTUAL_LEN_MASK;
		अगर (length > NIXGE_MAX_JUMBO_FRAME_SIZE)
			length = NIXGE_MAX_JUMBO_FRAME_SIZE;

		dma_unmap_single(ndev->dev.parent,
				 nixge_hw_dma_bd_get_addr(cur_p, phys),
				 NIXGE_MAX_JUMBO_FRAME_SIZE,
				 DMA_FROM_DEVICE);

		skb_put(skb, length);

		skb->protocol = eth_type_trans(skb, ndev);
		skb_checksum_none_निश्चित(skb);

		/* For now mark them as CHECKSUM_NONE since
		 * we करोn't have offload capabilities
		 */
		skb->ip_summed = CHECKSUM_NONE;

		napi_gro_receive(&priv->napi, skb);

		size += length;
		packets++;

		new_skb = netdev_alloc_skb_ip_align(ndev,
						    NIXGE_MAX_JUMBO_FRAME_SIZE);
		अगर (!new_skb)
			वापस packets;

		cur_phys = dma_map_single(ndev->dev.parent, new_skb->data,
					  NIXGE_MAX_JUMBO_FRAME_SIZE,
					  DMA_FROM_DEVICE);
		अगर (dma_mapping_error(ndev->dev.parent, cur_phys)) अणु
			/* FIXME: bail out and clean up */
			netdev_err(ndev, "Failed to map ...\n");
		पूर्ण
		nixge_hw_dma_bd_set_phys(cur_p, cur_phys);
		cur_p->cntrl = NIXGE_MAX_JUMBO_FRAME_SIZE;
		cur_p->status = 0;
		nixge_hw_dma_bd_set_offset(cur_p, (uपूर्णांकptr_t)new_skb);

		++priv->rx_bd_ci;
		priv->rx_bd_ci %= RX_BD_NUM;
		cur_p = &priv->rx_bd_v[priv->rx_bd_ci];
	पूर्ण

	ndev->stats.rx_packets += packets;
	ndev->stats.rx_bytes += size;

	अगर (tail_p)
		nixge_dma_ग_लिखो_desc_reg(priv, XAXIDMA_RX_TDESC_OFFSET, tail_p);

	वापस packets;
पूर्ण

अटल पूर्णांक nixge_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा nixge_priv *priv = container_of(napi, काष्ठा nixge_priv, napi);
	पूर्णांक work_करोne;
	u32 status, cr;

	work_करोne = 0;

	work_करोne = nixge_recv(priv->ndev, budget);
	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		status = nixge_dma_पढ़ो_reg(priv, XAXIDMA_RX_SR_OFFSET);

		अगर (status & (XAXIDMA_IRQ_IOC_MASK | XAXIDMA_IRQ_DELAY_MASK)) अणु
			/* If there's more, reschedule, but clear */
			nixge_dma_ग_लिखो_reg(priv, XAXIDMA_RX_SR_OFFSET, status);
			napi_reschedule(napi);
		पूर्ण अन्यथा अणु
			/* अगर not, turn on RX IRQs again ... */
			cr = nixge_dma_पढ़ो_reg(priv, XAXIDMA_RX_CR_OFFSET);
			cr |= (XAXIDMA_IRQ_IOC_MASK | XAXIDMA_IRQ_DELAY_MASK);
			nixge_dma_ग_लिखो_reg(priv, XAXIDMA_RX_CR_OFFSET, cr);
		पूर्ण
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल irqवापस_t nixge_tx_irq(पूर्णांक irq, व्योम *_ndev)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(_ndev);
	काष्ठा net_device *ndev = _ndev;
	अचिन्हित पूर्णांक status;
	dma_addr_t phys;
	u32 cr;

	status = nixge_dma_पढ़ो_reg(priv, XAXIDMA_TX_SR_OFFSET);
	अगर (status & (XAXIDMA_IRQ_IOC_MASK | XAXIDMA_IRQ_DELAY_MASK)) अणु
		nixge_dma_ग_लिखो_reg(priv, XAXIDMA_TX_SR_OFFSET, status);
		nixge_start_xmit_करोne(priv->ndev);
		जाओ out;
	पूर्ण
	अगर (!(status & XAXIDMA_IRQ_ALL_MASK)) अणु
		netdev_err(ndev, "No interrupts asserted in Tx path\n");
		वापस IRQ_NONE;
	पूर्ण
	अगर (status & XAXIDMA_IRQ_ERROR_MASK) अणु
		phys = nixge_hw_dma_bd_get_addr(&priv->tx_bd_v[priv->tx_bd_ci],
						phys);

		netdev_err(ndev, "DMA Tx error 0x%x\n", status);
		netdev_err(ndev, "Current BD is at: 0x%llx\n", (u64)phys);

		cr = nixge_dma_पढ़ो_reg(priv, XAXIDMA_TX_CR_OFFSET);
		/* Disable coalesce, delay समयr and error पूर्णांकerrupts */
		cr &= (~XAXIDMA_IRQ_ALL_MASK);
		/* Write to the Tx channel control रेजिस्टर */
		nixge_dma_ग_लिखो_reg(priv, XAXIDMA_TX_CR_OFFSET, cr);

		cr = nixge_dma_पढ़ो_reg(priv, XAXIDMA_RX_CR_OFFSET);
		/* Disable coalesce, delay समयr and error पूर्णांकerrupts */
		cr &= (~XAXIDMA_IRQ_ALL_MASK);
		/* Write to the Rx channel control रेजिस्टर */
		nixge_dma_ग_लिखो_reg(priv, XAXIDMA_RX_CR_OFFSET, cr);

		tasklet_schedule(&priv->dma_err_tasklet);
		nixge_dma_ग_लिखो_reg(priv, XAXIDMA_TX_SR_OFFSET, status);
	पूर्ण
out:
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t nixge_rx_irq(पूर्णांक irq, व्योम *_ndev)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(_ndev);
	काष्ठा net_device *ndev = _ndev;
	अचिन्हित पूर्णांक status;
	dma_addr_t phys;
	u32 cr;

	status = nixge_dma_पढ़ो_reg(priv, XAXIDMA_RX_SR_OFFSET);
	अगर (status & (XAXIDMA_IRQ_IOC_MASK | XAXIDMA_IRQ_DELAY_MASK)) अणु
		/* Turn of IRQs because NAPI */
		nixge_dma_ग_लिखो_reg(priv, XAXIDMA_RX_SR_OFFSET, status);
		cr = nixge_dma_पढ़ो_reg(priv, XAXIDMA_RX_CR_OFFSET);
		cr &= ~(XAXIDMA_IRQ_IOC_MASK | XAXIDMA_IRQ_DELAY_MASK);
		nixge_dma_ग_लिखो_reg(priv, XAXIDMA_RX_CR_OFFSET, cr);

		अगर (napi_schedule_prep(&priv->napi))
			__napi_schedule(&priv->napi);
		जाओ out;
	पूर्ण
	अगर (!(status & XAXIDMA_IRQ_ALL_MASK)) अणु
		netdev_err(ndev, "No interrupts asserted in Rx path\n");
		वापस IRQ_NONE;
	पूर्ण
	अगर (status & XAXIDMA_IRQ_ERROR_MASK) अणु
		phys = nixge_hw_dma_bd_get_addr(&priv->rx_bd_v[priv->rx_bd_ci],
						phys);
		netdev_err(ndev, "DMA Rx error 0x%x\n", status);
		netdev_err(ndev, "Current BD is at: 0x%llx\n", (u64)phys);

		cr = nixge_dma_पढ़ो_reg(priv, XAXIDMA_TX_CR_OFFSET);
		/* Disable coalesce, delay समयr and error पूर्णांकerrupts */
		cr &= (~XAXIDMA_IRQ_ALL_MASK);
		/* Finally ग_लिखो to the Tx channel control रेजिस्टर */
		nixge_dma_ग_लिखो_reg(priv, XAXIDMA_TX_CR_OFFSET, cr);

		cr = nixge_dma_पढ़ो_reg(priv, XAXIDMA_RX_CR_OFFSET);
		/* Disable coalesce, delay समयr and error पूर्णांकerrupts */
		cr &= (~XAXIDMA_IRQ_ALL_MASK);
		/* ग_लिखो to the Rx channel control रेजिस्टर */
		nixge_dma_ग_लिखो_reg(priv, XAXIDMA_RX_CR_OFFSET, cr);

		tasklet_schedule(&priv->dma_err_tasklet);
		nixge_dma_ग_लिखो_reg(priv, XAXIDMA_RX_SR_OFFSET, status);
	पूर्ण
out:
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम nixge_dma_err_handler(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा nixge_priv *lp = from_tasklet(lp, t, dma_err_tasklet);
	काष्ठा nixge_hw_dma_bd *cur_p;
	काष्ठा nixge_tx_skb *tx_skb;
	u32 cr, i;

	__nixge_device_reset(lp, XAXIDMA_TX_CR_OFFSET);
	__nixge_device_reset(lp, XAXIDMA_RX_CR_OFFSET);

	क्रम (i = 0; i < TX_BD_NUM; i++) अणु
		cur_p = &lp->tx_bd_v[i];
		tx_skb = &lp->tx_skb[i];
		nixge_tx_skb_unmap(lp, tx_skb);

		nixge_hw_dma_bd_set_phys(cur_p, 0);
		cur_p->cntrl = 0;
		cur_p->status = 0;
		nixge_hw_dma_bd_set_offset(cur_p, 0);
	पूर्ण

	क्रम (i = 0; i < RX_BD_NUM; i++) अणु
		cur_p = &lp->rx_bd_v[i];
		cur_p->status = 0;
	पूर्ण

	lp->tx_bd_ci = 0;
	lp->tx_bd_tail = 0;
	lp->rx_bd_ci = 0;

	/* Start updating the Rx channel control रेजिस्टर */
	cr = nixge_dma_पढ़ो_reg(lp, XAXIDMA_RX_CR_OFFSET);
	/* Update the पूर्णांकerrupt coalesce count */
	cr = ((cr & ~XAXIDMA_COALESCE_MASK) |
	      (XAXIDMA_DFT_RX_THRESHOLD << XAXIDMA_COALESCE_SHIFT));
	/* Update the delay समयr count */
	cr = ((cr & ~XAXIDMA_DELAY_MASK) |
	      (XAXIDMA_DFT_RX_WAITBOUND << XAXIDMA_DELAY_SHIFT));
	/* Enable coalesce, delay समयr and error पूर्णांकerrupts */
	cr |= XAXIDMA_IRQ_ALL_MASK;
	/* Finally ग_लिखो to the Rx channel control रेजिस्टर */
	nixge_dma_ग_लिखो_reg(lp, XAXIDMA_RX_CR_OFFSET, cr);

	/* Start updating the Tx channel control रेजिस्टर */
	cr = nixge_dma_पढ़ो_reg(lp, XAXIDMA_TX_CR_OFFSET);
	/* Update the पूर्णांकerrupt coalesce count */
	cr = (((cr & ~XAXIDMA_COALESCE_MASK)) |
	      (XAXIDMA_DFT_TX_THRESHOLD << XAXIDMA_COALESCE_SHIFT));
	/* Update the delay समयr count */
	cr = (((cr & ~XAXIDMA_DELAY_MASK)) |
	      (XAXIDMA_DFT_TX_WAITBOUND << XAXIDMA_DELAY_SHIFT));
	/* Enable coalesce, delay समयr and error पूर्णांकerrupts */
	cr |= XAXIDMA_IRQ_ALL_MASK;
	/* Finally ग_लिखो to the Tx channel control रेजिस्टर */
	nixge_dma_ग_लिखो_reg(lp, XAXIDMA_TX_CR_OFFSET, cr);

	/* Populate the tail poपूर्णांकer and bring the Rx Axi DMA engine out of
	 * halted state. This will make the Rx side पढ़ोy क्रम reception.
	 */
	nixge_dma_ग_लिखो_desc_reg(lp, XAXIDMA_RX_CDESC_OFFSET, lp->rx_bd_p);
	cr = nixge_dma_पढ़ो_reg(lp, XAXIDMA_RX_CR_OFFSET);
	nixge_dma_ग_लिखो_reg(lp, XAXIDMA_RX_CR_OFFSET,
			    cr | XAXIDMA_CR_RUNSTOP_MASK);
	nixge_dma_ग_लिखो_desc_reg(lp, XAXIDMA_RX_TDESC_OFFSET, lp->rx_bd_p +
			    (माप(*lp->rx_bd_v) * (RX_BD_NUM - 1)));

	/* Write to the RS (Run-stop) bit in the Tx channel control रेजिस्टर.
	 * Tx channel is now पढ़ोy to run. But only after we ग_लिखो to the
	 * tail poपूर्णांकer रेजिस्टर that the Tx channel will start transmitting
	 */
	nixge_dma_ग_लिखो_desc_reg(lp, XAXIDMA_TX_CDESC_OFFSET, lp->tx_bd_p);
	cr = nixge_dma_पढ़ो_reg(lp, XAXIDMA_TX_CR_OFFSET);
	nixge_dma_ग_लिखो_reg(lp, XAXIDMA_TX_CR_OFFSET,
			    cr | XAXIDMA_CR_RUNSTOP_MASK);
पूर्ण

अटल पूर्णांक nixge_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phy;
	पूर्णांक ret;

	nixge_device_reset(ndev);

	phy = of_phy_connect(ndev, priv->phy_node,
			     &nixge_handle_link_change, 0, priv->phy_mode);
	अगर (!phy)
		वापस -ENODEV;

	phy_start(phy);

	/* Enable tasklets क्रम Axi DMA error handling */
	tasklet_setup(&priv->dma_err_tasklet, nixge_dma_err_handler);

	napi_enable(&priv->napi);

	/* Enable पूर्णांकerrupts क्रम Axi DMA Tx */
	ret = request_irq(priv->tx_irq, nixge_tx_irq, 0, ndev->name, ndev);
	अगर (ret)
		जाओ err_tx_irq;
	/* Enable पूर्णांकerrupts क्रम Axi DMA Rx */
	ret = request_irq(priv->rx_irq, nixge_rx_irq, 0, ndev->name, ndev);
	अगर (ret)
		जाओ err_rx_irq;

	netअगर_start_queue(ndev);

	वापस 0;

err_rx_irq:
	मुक्त_irq(priv->tx_irq, ndev);
err_tx_irq:
	phy_stop(phy);
	phy_disconnect(phy);
	tasklet_समाप्त(&priv->dma_err_tasklet);
	netdev_err(ndev, "request_irq() failed\n");
	वापस ret;
पूर्ण

अटल पूर्णांक nixge_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(ndev);
	u32 cr;

	netअगर_stop_queue(ndev);
	napi_disable(&priv->napi);

	अगर (ndev->phydev) अणु
		phy_stop(ndev->phydev);
		phy_disconnect(ndev->phydev);
	पूर्ण

	cr = nixge_dma_पढ़ो_reg(priv, XAXIDMA_RX_CR_OFFSET);
	nixge_dma_ग_लिखो_reg(priv, XAXIDMA_RX_CR_OFFSET,
			    cr & (~XAXIDMA_CR_RUNSTOP_MASK));
	cr = nixge_dma_पढ़ो_reg(priv, XAXIDMA_TX_CR_OFFSET);
	nixge_dma_ग_लिखो_reg(priv, XAXIDMA_TX_CR_OFFSET,
			    cr & (~XAXIDMA_CR_RUNSTOP_MASK));

	tasklet_समाप्त(&priv->dma_err_tasklet);

	मुक्त_irq(priv->tx_irq, ndev);
	मुक्त_irq(priv->rx_irq, ndev);

	nixge_hw_dma_bd_release(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक nixge_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	अगर (netअगर_running(ndev))
		वापस -EBUSY;

	अगर ((new_mtu + NIXGE_HDR_SIZE + NIXGE_TRL_SIZE) >
	     NIXGE_MAX_JUMBO_FRAME_SIZE)
		वापस -EINVAL;

	ndev->mtu = new_mtu;

	वापस 0;
पूर्ण

अटल s32 __nixge_hw_set_mac_address(काष्ठा net_device *ndev)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(ndev);

	nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MAC_LSB,
			     (ndev->dev_addr[2]) << 24 |
			     (ndev->dev_addr[3] << 16) |
			     (ndev->dev_addr[4] << 8) |
			     (ndev->dev_addr[5] << 0));

	nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MAC_MSB,
			     (ndev->dev_addr[1] | (ndev->dev_addr[0] << 8)));

	वापस 0;
पूर्ण

अटल पूर्णांक nixge_net_set_mac_address(काष्ठा net_device *ndev, व्योम *p)
अणु
	पूर्णांक err;

	err = eth_mac_addr(ndev, p);
	अगर (!err)
		__nixge_hw_set_mac_address(ndev);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_device_ops nixge_netdev_ops = अणु
	.nकरो_खोलो = nixge_खोलो,
	.nकरो_stop = nixge_stop,
	.nकरो_start_xmit = nixge_start_xmit,
	.nकरो_change_mtu	= nixge_change_mtu,
	.nकरो_set_mac_address = nixge_net_set_mac_address,
	.nकरो_validate_addr = eth_validate_addr,
पूर्ण;

अटल व्योम nixge_ethtools_get_drvinfo(काष्ठा net_device *ndev,
				       काष्ठा ethtool_drvinfo *ed)
अणु
	strlcpy(ed->driver, "nixge", माप(ed->driver));
	strlcpy(ed->bus_info, "platform", माप(ed->bus_info));
पूर्ण

अटल पूर्णांक nixge_ethtools_get_coalesce(काष्ठा net_device *ndev,
				       काष्ठा ethtool_coalesce *ecoalesce)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(ndev);
	u32 regval = 0;

	regval = nixge_dma_पढ़ो_reg(priv, XAXIDMA_RX_CR_OFFSET);
	ecoalesce->rx_max_coalesced_frames = (regval & XAXIDMA_COALESCE_MASK)
					     >> XAXIDMA_COALESCE_SHIFT;
	regval = nixge_dma_पढ़ो_reg(priv, XAXIDMA_TX_CR_OFFSET);
	ecoalesce->tx_max_coalesced_frames = (regval & XAXIDMA_COALESCE_MASK)
					     >> XAXIDMA_COALESCE_SHIFT;
	वापस 0;
पूर्ण

अटल पूर्णांक nixge_ethtools_set_coalesce(काष्ठा net_device *ndev,
				       काष्ठा ethtool_coalesce *ecoalesce)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(ndev);

	अगर (netअगर_running(ndev)) अणु
		netdev_err(ndev,
			   "Please stop netif before applying configuration\n");
		वापस -EBUSY;
	पूर्ण

	अगर (ecoalesce->rx_max_coalesced_frames)
		priv->coalesce_count_rx = ecoalesce->rx_max_coalesced_frames;
	अगर (ecoalesce->tx_max_coalesced_frames)
		priv->coalesce_count_tx = ecoalesce->tx_max_coalesced_frames;

	वापस 0;
पूर्ण

अटल पूर्णांक nixge_ethtools_set_phys_id(काष्ठा net_device *ndev,
				      क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा nixge_priv *priv = netdev_priv(ndev);
	u32 ctrl;

	ctrl = nixge_ctrl_पढ़ो_reg(priv, NIXGE_REG_LED_CTL);
	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		ctrl |= NIXGE_ID_LED_CTL_EN;
		/* Enable identअगरication LED override*/
		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_LED_CTL, ctrl);
		वापस 2;

	हाल ETHTOOL_ID_ON:
		ctrl |= NIXGE_ID_LED_CTL_VAL;
		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_LED_CTL, ctrl);
		अवरोध;

	हाल ETHTOOL_ID_OFF:
		ctrl &= ~NIXGE_ID_LED_CTL_VAL;
		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_LED_CTL, ctrl);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		/* Restore LED settings */
		ctrl &= ~NIXGE_ID_LED_CTL_EN;
		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_LED_CTL, ctrl);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops nixge_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo    = nixge_ethtools_get_drvinfo,
	.get_coalesce   = nixge_ethtools_get_coalesce,
	.set_coalesce   = nixge_ethtools_set_coalesce,
	.set_phys_id    = nixge_ethtools_set_phys_id,
	.get_link_ksettings     = phy_ethtool_get_link_ksettings,
	.set_link_ksettings     = phy_ethtool_set_link_ksettings,
	.get_link		= ethtool_op_get_link,
पूर्ण;

अटल पूर्णांक nixge_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा nixge_priv *priv = bus->priv;
	u32 status, पंचांगp;
	पूर्णांक err;
	u16 device;

	अगर (reg & MII_ADDR_C45) अणु
		device = (reg >> 16) & 0x1f;

		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MDIO_ADDR, reg & 0xffff);

		पंचांगp = NIXGE_MDIO_CLAUSE45 | NIXGE_MDIO_OP(NIXGE_MDIO_OP_ADDRESS)
			| NIXGE_MDIO_ADDR(phy_id) | NIXGE_MDIO_MMD(device);

		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MDIO_OP, पंचांगp);
		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MDIO_CTRL, 1);

		err = nixge_ctrl_poll_समयout(priv, NIXGE_REG_MDIO_CTRL, status,
					      !status, 10, 1000);
		अगर (err) अणु
			dev_err(priv->dev, "timeout setting address");
			वापस err;
		पूर्ण

		पंचांगp = NIXGE_MDIO_CLAUSE45 | NIXGE_MDIO_OP(NIXGE_MDIO_C45_READ) |
			NIXGE_MDIO_ADDR(phy_id) | NIXGE_MDIO_MMD(device);
	पूर्ण अन्यथा अणु
		device = reg & 0x1f;

		पंचांगp = NIXGE_MDIO_CLAUSE22 | NIXGE_MDIO_OP(NIXGE_MDIO_C22_READ) |
			NIXGE_MDIO_ADDR(phy_id) | NIXGE_MDIO_MMD(device);
	पूर्ण

	nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MDIO_OP, पंचांगp);
	nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MDIO_CTRL, 1);

	err = nixge_ctrl_poll_समयout(priv, NIXGE_REG_MDIO_CTRL, status,
				      !status, 10, 1000);
	अगर (err) अणु
		dev_err(priv->dev, "timeout setting read command");
		वापस err;
	पूर्ण

	status = nixge_ctrl_पढ़ो_reg(priv, NIXGE_REG_MDIO_DATA);

	वापस status;
पूर्ण

अटल पूर्णांक nixge_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg, u16 val)
अणु
	काष्ठा nixge_priv *priv = bus->priv;
	u32 status, पंचांगp;
	u16 device;
	पूर्णांक err;

	अगर (reg & MII_ADDR_C45) अणु
		device = (reg >> 16) & 0x1f;

		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MDIO_ADDR, reg & 0xffff);

		पंचांगp = NIXGE_MDIO_CLAUSE45 | NIXGE_MDIO_OP(NIXGE_MDIO_OP_ADDRESS)
			| NIXGE_MDIO_ADDR(phy_id) | NIXGE_MDIO_MMD(device);

		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MDIO_OP, पंचांगp);
		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MDIO_CTRL, 1);

		err = nixge_ctrl_poll_समयout(priv, NIXGE_REG_MDIO_CTRL, status,
					      !status, 10, 1000);
		अगर (err) अणु
			dev_err(priv->dev, "timeout setting address");
			वापस err;
		पूर्ण

		पंचांगp = NIXGE_MDIO_CLAUSE45 | NIXGE_MDIO_OP(NIXGE_MDIO_C45_WRITE)
			| NIXGE_MDIO_ADDR(phy_id) | NIXGE_MDIO_MMD(device);

		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MDIO_DATA, val);
		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MDIO_OP, पंचांगp);
		err = nixge_ctrl_poll_समयout(priv, NIXGE_REG_MDIO_CTRL, status,
					      !status, 10, 1000);
		अगर (err)
			dev_err(priv->dev, "timeout setting write command");
	पूर्ण अन्यथा अणु
		device = reg & 0x1f;

		पंचांगp = NIXGE_MDIO_CLAUSE22 |
			NIXGE_MDIO_OP(NIXGE_MDIO_C22_WRITE) |
			NIXGE_MDIO_ADDR(phy_id) | NIXGE_MDIO_MMD(device);

		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MDIO_DATA, val);
		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MDIO_OP, पंचांगp);
		nixge_ctrl_ग_लिखो_reg(priv, NIXGE_REG_MDIO_CTRL, 1);

		err = nixge_ctrl_poll_समयout(priv, NIXGE_REG_MDIO_CTRL, status,
					      !status, 10, 1000);
		अगर (err)
			dev_err(priv->dev, "timeout setting write command");
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक nixge_mdio_setup(काष्ठा nixge_priv *priv, काष्ठा device_node *np)
अणु
	काष्ठा mii_bus *bus;

	bus = devm_mdiobus_alloc(priv->dev);
	अगर (!bus)
		वापस -ENOMEM;

	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(priv->dev));
	bus->priv = priv;
	bus->name = "nixge_mii_bus";
	bus->पढ़ो = nixge_mdio_पढ़ो;
	bus->ग_लिखो = nixge_mdio_ग_लिखो;
	bus->parent = priv->dev;

	priv->mii_bus = bus;

	वापस of_mdiobus_रेजिस्टर(bus, np);
पूर्ण

अटल व्योम *nixge_get_nvmem_address(काष्ठा device *dev)
अणु
	काष्ठा nvmem_cell *cell;
	माप_प्रकार cell_size;
	अक्षर *mac;

	cell = nvmem_cell_get(dev, "address");
	अगर (IS_ERR(cell))
		वापस शून्य;

	mac = nvmem_cell_पढ़ो(cell, &cell_size);
	nvmem_cell_put(cell);

	वापस mac;
पूर्ण

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id nixge_dt_ids[] = अणु
	अणु .compatible = "ni,xge-enet-2.00", .data = (व्योम *)NIXGE_V2 पूर्ण,
	अणु .compatible = "ni,xge-enet-3.00", .data = (व्योम *)NIXGE_V3 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, nixge_dt_ids);

अटल पूर्णांक nixge_of_get_resources(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	क्रमागत nixge_version version;
	काष्ठा resource *ctrlres;
	काष्ठा resource *dmares;
	काष्ठा net_device *ndev;
	काष्ठा nixge_priv *priv;

	ndev = platक्रमm_get_drvdata(pdev);
	priv = netdev_priv(ndev);
	of_id = of_match_node(nixge_dt_ids, pdev->dev.of_node);
	अगर (!of_id)
		वापस -ENODEV;

	version = (क्रमागत nixge_version)of_id->data;
	अगर (version <= NIXGE_V2)
		dmares = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अन्यथा
		dmares = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						      "dma");

	priv->dma_regs = devm_ioremap_resource(&pdev->dev, dmares);
	अगर (IS_ERR(priv->dma_regs)) अणु
		netdev_err(ndev, "failed to map dma regs\n");
		वापस PTR_ERR(priv->dma_regs);
	पूर्ण
	अगर (version <= NIXGE_V2) अणु
		priv->ctrl_regs = priv->dma_regs + NIXGE_REG_CTRL_OFFSET;
	पूर्ण अन्यथा अणु
		ctrlres = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						       "ctrl");
		priv->ctrl_regs = devm_ioremap_resource(&pdev->dev, ctrlres);
	पूर्ण
	अगर (IS_ERR(priv->ctrl_regs)) अणु
		netdev_err(ndev, "failed to map ctrl regs\n");
		वापस PTR_ERR(priv->ctrl_regs);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nixge_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *mn, *phy_node;
	काष्ठा nixge_priv *priv;
	काष्ठा net_device *ndev;
	स्थिर u8 *mac_addr;
	पूर्णांक err;

	ndev = alloc_etherdev(माप(*priv));
	अगर (!ndev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);

	ndev->features = NETIF_F_SG;
	ndev->netdev_ops = &nixge_netdev_ops;
	ndev->ethtool_ops = &nixge_ethtool_ops;

	/* MTU range: 64 - 9000 */
	ndev->min_mtu = 64;
	ndev->max_mtu = NIXGE_JUMBO_MTU;

	mac_addr = nixge_get_nvmem_address(&pdev->dev);
	अगर (mac_addr && is_valid_ether_addr(mac_addr)) अणु
		ether_addr_copy(ndev->dev_addr, mac_addr);
		kमुक्त(mac_addr);
	पूर्ण अन्यथा अणु
		eth_hw_addr_अक्रमom(ndev);
	पूर्ण

	priv = netdev_priv(ndev);
	priv->ndev = ndev;
	priv->dev = &pdev->dev;

	netअगर_napi_add(ndev, &priv->napi, nixge_poll, NAPI_POLL_WEIGHT);
	err = nixge_of_get_resources(pdev);
	अगर (err)
		जाओ मुक्त_netdev;
	__nixge_hw_set_mac_address(ndev);

	priv->tx_irq = platक्रमm_get_irq_byname(pdev, "tx");
	अगर (priv->tx_irq < 0) अणु
		netdev_err(ndev, "could not find 'tx' irq");
		err = priv->tx_irq;
		जाओ मुक्त_netdev;
	पूर्ण

	priv->rx_irq = platक्रमm_get_irq_byname(pdev, "rx");
	अगर (priv->rx_irq < 0) अणु
		netdev_err(ndev, "could not find 'rx' irq");
		err = priv->rx_irq;
		जाओ मुक्त_netdev;
	पूर्ण

	priv->coalesce_count_rx = XAXIDMA_DFT_RX_THRESHOLD;
	priv->coalesce_count_tx = XAXIDMA_DFT_TX_THRESHOLD;

	mn = of_get_child_by_name(pdev->dev.of_node, "mdio");
	अगर (mn) अणु
		err = nixge_mdio_setup(priv, mn);
		of_node_put(mn);
		अगर (err) अणु
			netdev_err(ndev, "error registering mdio bus");
			जाओ मुक्त_netdev;
		पूर्ण
	पूर्ण

	err = of_get_phy_mode(pdev->dev.of_node, &priv->phy_mode);
	अगर (err) अणु
		netdev_err(ndev, "not find \"phy-mode\" property\n");
		जाओ unरेजिस्टर_mdio;
	पूर्ण

	phy_node = of_parse_phandle(pdev->dev.of_node, "phy-handle", 0);
	अगर (!phy_node && of_phy_is_fixed_link(pdev->dev.of_node)) अणु
		err = of_phy_रेजिस्टर_fixed_link(pdev->dev.of_node);
		अगर (err < 0) अणु
			netdev_err(ndev, "broken fixed-link specification\n");
			जाओ unरेजिस्टर_mdio;
		पूर्ण
		phy_node = of_node_get(pdev->dev.of_node);
	पूर्ण
	priv->phy_node = phy_node;

	err = रेजिस्टर_netdev(priv->ndev);
	अगर (err) अणु
		netdev_err(ndev, "register_netdev() error (%i)\n", err);
		जाओ मुक्त_phy;
	पूर्ण

	वापस 0;

मुक्त_phy:
	अगर (of_phy_is_fixed_link(pdev->dev.of_node))
		of_phy_deरेजिस्टर_fixed_link(pdev->dev.of_node);
	of_node_put(phy_node);

unरेजिस्टर_mdio:
	अगर (priv->mii_bus)
		mdiobus_unरेजिस्टर(priv->mii_bus);

मुक्त_netdev:
	मुक्त_netdev(ndev);

	वापस err;
पूर्ण

अटल पूर्णांक nixge_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा nixge_priv *priv = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);

	अगर (of_phy_is_fixed_link(pdev->dev.of_node))
		of_phy_deरेजिस्टर_fixed_link(pdev->dev.of_node);
	of_node_put(priv->phy_node);

	अगर (priv->mii_bus)
		mdiobus_unरेजिस्टर(priv->mii_bus);

	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver nixge_driver = अणु
	.probe		= nixge_probe,
	.हटाओ		= nixge_हटाओ,
	.driver		= अणु
		.name		= "nixge",
		.of_match_table	= of_match_ptr(nixge_dt_ids),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(nixge_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("National Instruments XGE Management MAC");
MODULE_AUTHOR("Moritz Fischer <mdf@kernel.org>");
