<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/net/ethernet/ethoc.c
 *
 * Copyright (C) 2007-2008 Avionic Design Development GmbH
 * Copyright (C) 2008-2009 Avionic Design GmbH
 *
 * Written by Thierry Reding <thierry.reding@avionic-design.de>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/clk.h>
#समावेश <linux/crc32.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/module.h>
#समावेश <net/ethoc.h>

अटल पूर्णांक buffer_size = 0x8000; /* 32 KBytes */
module_param(buffer_size, पूर्णांक, 0);
MODULE_PARM_DESC(buffer_size, "DMA buffer allocation size");

/* रेजिस्टर offsets */
#घोषणा	MODER		0x00
#घोषणा	INT_SOURCE	0x04
#घोषणा	INT_MASK	0x08
#घोषणा	IPGT		0x0c
#घोषणा	IPGR1		0x10
#घोषणा	IPGR2		0x14
#घोषणा	PACKETLEN	0x18
#घोषणा	COLLCONF	0x1c
#घोषणा	TX_BD_NUM	0x20
#घोषणा	CTRLMODER	0x24
#घोषणा	MIIMODER	0x28
#घोषणा	MIICOMMAND	0x2c
#घोषणा	MIIADDRESS	0x30
#घोषणा	MIITX_DATA	0x34
#घोषणा	MIIRX_DATA	0x38
#घोषणा	MIISTATUS	0x3c
#घोषणा	MAC_ADDR0	0x40
#घोषणा	MAC_ADDR1	0x44
#घोषणा	ETH_HASH0	0x48
#घोषणा	ETH_HASH1	0x4c
#घोषणा	ETH_TXCTRL	0x50
#घोषणा	ETH_END		0x54

/* mode रेजिस्टर */
#घोषणा	MODER_RXEN	(1 <<  0) /* receive enable */
#घोषणा	MODER_TXEN	(1 <<  1) /* transmit enable */
#घोषणा	MODER_NOPRE	(1 <<  2) /* no preamble */
#घोषणा	MODER_BRO	(1 <<  3) /* broadcast address */
#घोषणा	MODER_IAM	(1 <<  4) /* inभागidual address mode */
#घोषणा	MODER_PRO	(1 <<  5) /* promiscuous mode */
#घोषणा	MODER_IFG	(1 <<  6) /* पूर्णांकerframe gap क्रम incoming frames */
#घोषणा	MODER_LOOP	(1 <<  7) /* loopback */
#घोषणा	MODER_NBO	(1 <<  8) /* no back-off */
#घोषणा	MODER_EDE	(1 <<  9) /* excess defer enable */
#घोषणा	MODER_FULLD	(1 << 10) /* full duplex */
#घोषणा	MODER_RESET	(1 << 11) /* FIXME: reset (unकरोcumented) */
#घोषणा	MODER_DCRC	(1 << 12) /* delayed CRC enable */
#घोषणा	MODER_CRC	(1 << 13) /* CRC enable */
#घोषणा	MODER_HUGE	(1 << 14) /* huge packets enable */
#घोषणा	MODER_PAD	(1 << 15) /* padding enabled */
#घोषणा	MODER_RSM	(1 << 16) /* receive small packets */

/* पूर्णांकerrupt source and mask रेजिस्टरs */
#घोषणा	INT_MASK_TXF	(1 << 0) /* transmit frame */
#घोषणा	INT_MASK_TXE	(1 << 1) /* transmit error */
#घोषणा	INT_MASK_RXF	(1 << 2) /* receive frame */
#घोषणा	INT_MASK_RXE	(1 << 3) /* receive error */
#घोषणा	INT_MASK_BUSY	(1 << 4)
#घोषणा	INT_MASK_TXC	(1 << 5) /* transmit control frame */
#घोषणा	INT_MASK_RXC	(1 << 6) /* receive control frame */

#घोषणा	INT_MASK_TX	(INT_MASK_TXF | INT_MASK_TXE)
#घोषणा	INT_MASK_RX	(INT_MASK_RXF | INT_MASK_RXE)

#घोषणा	INT_MASK_ALL ( \
		INT_MASK_TXF | INT_MASK_TXE | \
		INT_MASK_RXF | INT_MASK_RXE | \
		INT_MASK_TXC | INT_MASK_RXC | \
		INT_MASK_BUSY \
	)

/* packet length रेजिस्टर */
#घोषणा	PACKETLEN_MIN(min)		(((min) & 0xffff) << 16)
#घोषणा	PACKETLEN_MAX(max)		(((max) & 0xffff) <<  0)
#घोषणा	PACKETLEN_MIN_MAX(min, max)	(PACKETLEN_MIN(min) | \
					PACKETLEN_MAX(max))

/* transmit buffer number रेजिस्टर */
#घोषणा	TX_BD_NUM_VAL(x)	(((x) <= 0x80) ? (x) : 0x80)

/* control module mode रेजिस्टर */
#घोषणा	CTRLMODER_PASSALL	(1 << 0) /* pass all receive frames */
#घोषणा	CTRLMODER_RXFLOW	(1 << 1) /* receive control flow */
#घोषणा	CTRLMODER_TXFLOW	(1 << 2) /* transmit control flow */

/* MII mode रेजिस्टर */
#घोषणा	MIIMODER_CLKDIV(x)	((x) & 0xfe) /* needs to be an even number */
#घोषणा	MIIMODER_NOPRE		(1 << 8) /* no preamble */

/* MII command रेजिस्टर */
#घोषणा	MIICOMMAND_SCAN		(1 << 0) /* scan status */
#घोषणा	MIICOMMAND_READ		(1 << 1) /* पढ़ो status */
#घोषणा	MIICOMMAND_WRITE	(1 << 2) /* ग_लिखो control data */

/* MII address रेजिस्टर */
#घोषणा	MIIADDRESS_FIAD(x)		(((x) & 0x1f) << 0)
#घोषणा	MIIADDRESS_RGAD(x)		(((x) & 0x1f) << 8)
#घोषणा	MIIADDRESS_ADDR(phy, reg)	(MIIADDRESS_FIAD(phy) | \
					MIIADDRESS_RGAD(reg))

/* MII transmit data रेजिस्टर */
#घोषणा	MIITX_DATA_VAL(x)	((x) & 0xffff)

/* MII receive data रेजिस्टर */
#घोषणा	MIIRX_DATA_VAL(x)	((x) & 0xffff)

/* MII status रेजिस्टर */
#घोषणा	MIISTATUS_LINKFAIL	(1 << 0)
#घोषणा	MIISTATUS_BUSY		(1 << 1)
#घोषणा	MIISTATUS_INVALID	(1 << 2)

/* TX buffer descriptor */
#घोषणा	TX_BD_CS		(1 <<  0) /* carrier sense lost */
#घोषणा	TX_BD_DF		(1 <<  1) /* defer indication */
#घोषणा	TX_BD_LC		(1 <<  2) /* late collision */
#घोषणा	TX_BD_RL		(1 <<  3) /* retransmission limit */
#घोषणा	TX_BD_RETRY_MASK	(0x00f0)
#घोषणा	TX_BD_RETRY(x)		(((x) & 0x00f0) >>  4)
#घोषणा	TX_BD_UR		(1 <<  8) /* transmitter underrun */
#घोषणा	TX_BD_CRC		(1 << 11) /* TX CRC enable */
#घोषणा	TX_BD_PAD		(1 << 12) /* pad enable क्रम लघु packets */
#घोषणा	TX_BD_WRAP		(1 << 13)
#घोषणा	TX_BD_IRQ		(1 << 14) /* पूर्णांकerrupt request enable */
#घोषणा	TX_BD_READY		(1 << 15) /* TX buffer पढ़ोy */
#घोषणा	TX_BD_LEN(x)		(((x) & 0xffff) << 16)
#घोषणा	TX_BD_LEN_MASK		(0xffff << 16)

#घोषणा	TX_BD_STATS		(TX_BD_CS | TX_BD_DF | TX_BD_LC | \
				TX_BD_RL | TX_BD_RETRY_MASK | TX_BD_UR)

/* RX buffer descriptor */
#घोषणा	RX_BD_LC	(1 <<  0) /* late collision */
#घोषणा	RX_BD_CRC	(1 <<  1) /* RX CRC error */
#घोषणा	RX_BD_SF	(1 <<  2) /* लघु frame */
#घोषणा	RX_BD_TL	(1 <<  3) /* too दीर्घ */
#घोषणा	RX_BD_DN	(1 <<  4) /* dribble nibble */
#घोषणा	RX_BD_IS	(1 <<  5) /* invalid symbol */
#घोषणा	RX_BD_OR	(1 <<  6) /* receiver overrun */
#घोषणा	RX_BD_MISS	(1 <<  7)
#घोषणा	RX_BD_CF	(1 <<  8) /* control frame */
#घोषणा	RX_BD_WRAP	(1 << 13)
#घोषणा	RX_BD_IRQ	(1 << 14) /* पूर्णांकerrupt request enable */
#घोषणा	RX_BD_EMPTY	(1 << 15)
#घोषणा	RX_BD_LEN(x)	(((x) & 0xffff) << 16)

#घोषणा	RX_BD_STATS	(RX_BD_LC | RX_BD_CRC | RX_BD_SF | RX_BD_TL | \
			RX_BD_DN | RX_BD_IS | RX_BD_OR | RX_BD_MISS)

#घोषणा	ETHOC_बफ_मान		1536
#घोषणा	ETHOC_ZLEN		64
#घोषणा	ETHOC_BD_BASE		0x400
#घोषणा	ETHOC_TIMEOUT		(HZ / 2)
#घोषणा	ETHOC_MII_TIMEOUT	(1 + (HZ / 5))

/**
 * काष्ठा ethoc - driver-निजी device काष्ठाure
 * @iobase:	poपूर्णांकer to I/O memory region
 * @membase:	poपूर्णांकer to buffer memory region
 * @big_endian: just big or little (endian)
 * @num_bd:	number of buffer descriptors
 * @num_tx:	number of send buffers
 * @cur_tx:	last send buffer written
 * @dty_tx:	last buffer actually sent
 * @num_rx:	number of receive buffers
 * @cur_rx:	current receive buffer
 * @vma:        poपूर्णांकer to array of भव memory addresses क्रम buffers
 * @netdev:	poपूर्णांकer to network device काष्ठाure
 * @napi:	NAPI काष्ठाure
 * @msg_enable:	device state flags
 * @lock:	device lock
 * @mdio:	MDIO bus क्रम PHY access
 * @clk:	घड़ी
 * @phy_id:	address of attached PHY
 * @old_link:	previous link info
 * @old_duplex: previous duplex info
 */
काष्ठा ethoc अणु
	व्योम __iomem *iobase;
	व्योम __iomem *membase;
	bool big_endian;

	अचिन्हित पूर्णांक num_bd;
	अचिन्हित पूर्णांक num_tx;
	अचिन्हित पूर्णांक cur_tx;
	अचिन्हित पूर्णांक dty_tx;

	अचिन्हित पूर्णांक num_rx;
	अचिन्हित पूर्णांक cur_rx;

	व्योम **vma;

	काष्ठा net_device *netdev;
	काष्ठा napi_काष्ठा napi;
	u32 msg_enable;

	spinlock_t lock;

	काष्ठा mii_bus *mdio;
	काष्ठा clk *clk;
	s8 phy_id;

	पूर्णांक old_link;
	पूर्णांक old_duplex;
पूर्ण;

/**
 * काष्ठा ethoc_bd - buffer descriptor
 * @stat:	buffer statistics
 * @addr:	physical memory address
 */
काष्ठा ethoc_bd अणु
	u32 stat;
	u32 addr;
पूर्ण;

अटल अंतरभूत u32 ethoc_पढ़ो(काष्ठा ethoc *dev, loff_t offset)
अणु
	अगर (dev->big_endian)
		वापस ioपढ़ो32be(dev->iobase + offset);
	अन्यथा
		वापस ioपढ़ो32(dev->iobase + offset);
पूर्ण

अटल अंतरभूत व्योम ethoc_ग_लिखो(काष्ठा ethoc *dev, loff_t offset, u32 data)
अणु
	अगर (dev->big_endian)
		ioग_लिखो32be(data, dev->iobase + offset);
	अन्यथा
		ioग_लिखो32(data, dev->iobase + offset);
पूर्ण

अटल अंतरभूत व्योम ethoc_पढ़ो_bd(काष्ठा ethoc *dev, पूर्णांक index,
		काष्ठा ethoc_bd *bd)
अणु
	loff_t offset = ETHOC_BD_BASE + (index * माप(काष्ठा ethoc_bd));
	bd->stat = ethoc_पढ़ो(dev, offset + 0);
	bd->addr = ethoc_पढ़ो(dev, offset + 4);
पूर्ण

अटल अंतरभूत व्योम ethoc_ग_लिखो_bd(काष्ठा ethoc *dev, पूर्णांक index,
		स्थिर काष्ठा ethoc_bd *bd)
अणु
	loff_t offset = ETHOC_BD_BASE + (index * माप(काष्ठा ethoc_bd));
	ethoc_ग_लिखो(dev, offset + 0, bd->stat);
	ethoc_ग_लिखो(dev, offset + 4, bd->addr);
पूर्ण

अटल अंतरभूत व्योम ethoc_enable_irq(काष्ठा ethoc *dev, u32 mask)
अणु
	u32 imask = ethoc_पढ़ो(dev, INT_MASK);
	imask |= mask;
	ethoc_ग_लिखो(dev, INT_MASK, imask);
पूर्ण

अटल अंतरभूत व्योम ethoc_disable_irq(काष्ठा ethoc *dev, u32 mask)
अणु
	u32 imask = ethoc_पढ़ो(dev, INT_MASK);
	imask &= ~mask;
	ethoc_ग_लिखो(dev, INT_MASK, imask);
पूर्ण

अटल अंतरभूत व्योम ethoc_ack_irq(काष्ठा ethoc *dev, u32 mask)
अणु
	ethoc_ग_लिखो(dev, INT_SOURCE, mask);
पूर्ण

अटल अंतरभूत व्योम ethoc_enable_rx_and_tx(काष्ठा ethoc *dev)
अणु
	u32 mode = ethoc_पढ़ो(dev, MODER);
	mode |= MODER_RXEN | MODER_TXEN;
	ethoc_ग_लिखो(dev, MODER, mode);
पूर्ण

अटल अंतरभूत व्योम ethoc_disable_rx_and_tx(काष्ठा ethoc *dev)
अणु
	u32 mode = ethoc_पढ़ो(dev, MODER);
	mode &= ~(MODER_RXEN | MODER_TXEN);
	ethoc_ग_लिखो(dev, MODER, mode);
पूर्ण

अटल पूर्णांक ethoc_init_ring(काष्ठा ethoc *dev, अचिन्हित दीर्घ mem_start)
अणु
	काष्ठा ethoc_bd bd;
	पूर्णांक i;
	व्योम *vma;

	dev->cur_tx = 0;
	dev->dty_tx = 0;
	dev->cur_rx = 0;

	ethoc_ग_लिखो(dev, TX_BD_NUM, dev->num_tx);

	/* setup transmission buffers */
	bd.addr = mem_start;
	bd.stat = TX_BD_IRQ | TX_BD_CRC;
	vma = dev->membase;

	क्रम (i = 0; i < dev->num_tx; i++) अणु
		अगर (i == dev->num_tx - 1)
			bd.stat |= TX_BD_WRAP;

		ethoc_ग_लिखो_bd(dev, i, &bd);
		bd.addr += ETHOC_बफ_मान;

		dev->vma[i] = vma;
		vma += ETHOC_बफ_मान;
	पूर्ण

	bd.stat = RX_BD_EMPTY | RX_BD_IRQ;

	क्रम (i = 0; i < dev->num_rx; i++) अणु
		अगर (i == dev->num_rx - 1)
			bd.stat |= RX_BD_WRAP;

		ethoc_ग_लिखो_bd(dev, dev->num_tx + i, &bd);
		bd.addr += ETHOC_बफ_मान;

		dev->vma[dev->num_tx + i] = vma;
		vma += ETHOC_बफ_मान;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ethoc_reset(काष्ठा ethoc *dev)
अणु
	u32 mode;

	/* TODO: reset controller? */

	ethoc_disable_rx_and_tx(dev);

	/* TODO: setup रेजिस्टरs */

	/* enable FCS generation and स्वतःmatic padding */
	mode = ethoc_पढ़ो(dev, MODER);
	mode |= MODER_CRC | MODER_PAD;
	ethoc_ग_लिखो(dev, MODER, mode);

	/* set full-duplex mode */
	mode = ethoc_पढ़ो(dev, MODER);
	mode |= MODER_FULLD;
	ethoc_ग_लिखो(dev, MODER, mode);
	ethoc_ग_लिखो(dev, IPGT, 0x15);

	ethoc_ack_irq(dev, INT_MASK_ALL);
	ethoc_enable_irq(dev, INT_MASK_ALL);
	ethoc_enable_rx_and_tx(dev);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ethoc_update_rx_stats(काष्ठा ethoc *dev,
		काष्ठा ethoc_bd *bd)
अणु
	काष्ठा net_device *netdev = dev->netdev;
	अचिन्हित पूर्णांक ret = 0;

	अगर (bd->stat & RX_BD_TL) अणु
		dev_err(&netdev->dev, "RX: frame too long\n");
		netdev->stats.rx_length_errors++;
		ret++;
	पूर्ण

	अगर (bd->stat & RX_BD_SF) अणु
		dev_err(&netdev->dev, "RX: frame too short\n");
		netdev->stats.rx_length_errors++;
		ret++;
	पूर्ण

	अगर (bd->stat & RX_BD_DN) अणु
		dev_err(&netdev->dev, "RX: dribble nibble\n");
		netdev->stats.rx_frame_errors++;
	पूर्ण

	अगर (bd->stat & RX_BD_CRC) अणु
		dev_err(&netdev->dev, "RX: wrong CRC\n");
		netdev->stats.rx_crc_errors++;
		ret++;
	पूर्ण

	अगर (bd->stat & RX_BD_OR) अणु
		dev_err(&netdev->dev, "RX: overrun\n");
		netdev->stats.rx_over_errors++;
		ret++;
	पूर्ण

	अगर (bd->stat & RX_BD_MISS)
		netdev->stats.rx_missed_errors++;

	अगर (bd->stat & RX_BD_LC) अणु
		dev_err(&netdev->dev, "RX: late collision\n");
		netdev->stats.collisions++;
		ret++;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ethoc_rx(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);
	पूर्णांक count;

	क्रम (count = 0; count < limit; ++count) अणु
		अचिन्हित पूर्णांक entry;
		काष्ठा ethoc_bd bd;

		entry = priv->num_tx + priv->cur_rx;
		ethoc_पढ़ो_bd(priv, entry, &bd);
		अगर (bd.stat & RX_BD_EMPTY) अणु
			ethoc_ack_irq(priv, INT_MASK_RX);
			/* If packet (पूर्णांकerrupt) came in between checking
			 * BD_EMTPY and clearing the पूर्णांकerrupt source, then we
			 * risk missing the packet as the RX पूर्णांकerrupt won't
			 * trigger right away when we reenable it; hence, check
			 * BD_EMTPY here again to make sure there isn't such a
			 * packet रुकोing क्रम us...
			 */
			ethoc_पढ़ो_bd(priv, entry, &bd);
			अगर (bd.stat & RX_BD_EMPTY)
				अवरोध;
		पूर्ण

		अगर (ethoc_update_rx_stats(priv, &bd) == 0) अणु
			पूर्णांक size = bd.stat >> 16;
			काष्ठा sk_buff *skb;

			size -= 4; /* strip the CRC */
			skb = netdev_alloc_skb_ip_align(dev, size);

			अगर (likely(skb)) अणु
				व्योम *src = priv->vma[entry];
				स_नकल_fromio(skb_put(skb, size), src, size);
				skb->protocol = eth_type_trans(skb, dev);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += size;
				netअगर_receive_skb(skb);
			पूर्ण अन्यथा अणु
				अगर (net_ratelimit())
					dev_warn(&dev->dev,
					    "low on memory - packet dropped\n");

				dev->stats.rx_dropped++;
				अवरोध;
			पूर्ण
		पूर्ण

		/* clear the buffer descriptor so it can be reused */
		bd.stat &= ~RX_BD_STATS;
		bd.stat |=  RX_BD_EMPTY;
		ethoc_ग_लिखो_bd(priv, entry, &bd);
		अगर (++priv->cur_rx == priv->num_rx)
			priv->cur_rx = 0;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम ethoc_update_tx_stats(काष्ठा ethoc *dev, काष्ठा ethoc_bd *bd)
अणु
	काष्ठा net_device *netdev = dev->netdev;

	अगर (bd->stat & TX_BD_LC) अणु
		dev_err(&netdev->dev, "TX: late collision\n");
		netdev->stats.tx_winकरोw_errors++;
	पूर्ण

	अगर (bd->stat & TX_BD_RL) अणु
		dev_err(&netdev->dev, "TX: retransmit limit\n");
		netdev->stats.tx_पातed_errors++;
	पूर्ण

	अगर (bd->stat & TX_BD_UR) अणु
		dev_err(&netdev->dev, "TX: underrun\n");
		netdev->stats.tx_fअगरo_errors++;
	पूर्ण

	अगर (bd->stat & TX_BD_CS) अणु
		dev_err(&netdev->dev, "TX: carrier sense lost\n");
		netdev->stats.tx_carrier_errors++;
	पूर्ण

	अगर (bd->stat & TX_BD_STATS)
		netdev->stats.tx_errors++;

	netdev->stats.collisions += (bd->stat >> 4) & 0xf;
	netdev->stats.tx_bytes += bd->stat >> 16;
	netdev->stats.tx_packets++;
पूर्ण

अटल पूर्णांक ethoc_tx(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);
	पूर्णांक count;
	काष्ठा ethoc_bd bd;

	क्रम (count = 0; count < limit; ++count) अणु
		अचिन्हित पूर्णांक entry;

		entry = priv->dty_tx & (priv->num_tx-1);

		ethoc_पढ़ो_bd(priv, entry, &bd);

		अगर (bd.stat & TX_BD_READY || (priv->dty_tx == priv->cur_tx)) अणु
			ethoc_ack_irq(priv, INT_MASK_TX);
			/* If पूर्णांकerrupt came in between पढ़ोing in the BD
			 * and clearing the पूर्णांकerrupt source, then we risk
			 * missing the event as the TX पूर्णांकerrupt won't trigger
			 * right away when we reenable it; hence, check
			 * BD_EMPTY here again to make sure there isn't such an
			 * event pending...
			 */
			ethoc_पढ़ो_bd(priv, entry, &bd);
			अगर (bd.stat & TX_BD_READY ||
			    (priv->dty_tx == priv->cur_tx))
				अवरोध;
		पूर्ण

		ethoc_update_tx_stats(priv, &bd);
		priv->dty_tx++;
	पूर्ण

	अगर ((priv->cur_tx - priv->dty_tx) <= (priv->num_tx / 2))
		netअगर_wake_queue(dev);

	वापस count;
पूर्ण

अटल irqवापस_t ethoc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा ethoc *priv = netdev_priv(dev);
	u32 pending;
	u32 mask;

	/* Figure out what triggered the पूर्णांकerrupt...
	 * The tricky bit here is that the पूर्णांकerrupt source bits get
	 * set in INT_SOURCE क्रम an event regardless of whether that
	 * event is masked or not.  Thus, in order to figure out what
	 * triggered the पूर्णांकerrupt, we need to हटाओ the sources
	 * क्रम all events that are currently masked.  This behaviour
	 * is not particularly well करोcumented but reasonable...
	 */
	mask = ethoc_पढ़ो(priv, INT_MASK);
	pending = ethoc_पढ़ो(priv, INT_SOURCE);
	pending &= mask;

	अगर (unlikely(pending == 0))
		वापस IRQ_NONE;

	ethoc_ack_irq(priv, pending);

	/* We always handle the dropped packet पूर्णांकerrupt */
	अगर (pending & INT_MASK_BUSY) अणु
		dev_dbg(&dev->dev, "packet dropped\n");
		dev->stats.rx_dropped++;
	पूर्ण

	/* Handle receive/transmit event by चयनing to polling */
	अगर (pending & (INT_MASK_TX | INT_MASK_RX)) अणु
		ethoc_disable_irq(priv, INT_MASK_TX | INT_MASK_RX);
		napi_schedule(&priv->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ethoc_get_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);
	u8 *mac = (u8 *)addr;
	u32 reg;

	reg = ethoc_पढ़ो(priv, MAC_ADDR0);
	mac[2] = (reg >> 24) & 0xff;
	mac[3] = (reg >> 16) & 0xff;
	mac[4] = (reg >>  8) & 0xff;
	mac[5] = (reg >>  0) & 0xff;

	reg = ethoc_पढ़ो(priv, MAC_ADDR1);
	mac[0] = (reg >>  8) & 0xff;
	mac[1] = (reg >>  0) & 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक ethoc_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ethoc *priv = container_of(napi, काष्ठा ethoc, napi);
	पूर्णांक rx_work_करोne = 0;
	पूर्णांक tx_work_करोne = 0;

	rx_work_करोne = ethoc_rx(priv->netdev, budget);
	tx_work_करोne = ethoc_tx(priv->netdev, budget);

	अगर (rx_work_करोne < budget && tx_work_करोne < budget) अणु
		napi_complete_करोne(napi, rx_work_करोne);
		ethoc_enable_irq(priv, INT_MASK_TX | INT_MASK_RX);
	पूर्ण

	वापस rx_work_करोne;
पूर्ण

अटल पूर्णांक ethoc_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg)
अणु
	काष्ठा ethoc *priv = bus->priv;
	पूर्णांक i;

	ethoc_ग_लिखो(priv, MIIADDRESS, MIIADDRESS_ADDR(phy, reg));
	ethoc_ग_लिखो(priv, MIICOMMAND, MIICOMMAND_READ);

	क्रम (i = 0; i < 5; i++) अणु
		u32 status = ethoc_पढ़ो(priv, MIISTATUS);
		अगर (!(status & MIISTATUS_BUSY)) अणु
			u32 data = ethoc_पढ़ो(priv, MIIRX_DATA);
			/* reset MII command रेजिस्टर */
			ethoc_ग_लिखो(priv, MIICOMMAND, 0);
			वापस data;
		पूर्ण
		usleep_range(100, 200);
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक ethoc_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg, u16 val)
अणु
	काष्ठा ethoc *priv = bus->priv;
	पूर्णांक i;

	ethoc_ग_लिखो(priv, MIIADDRESS, MIIADDRESS_ADDR(phy, reg));
	ethoc_ग_लिखो(priv, MIITX_DATA, val);
	ethoc_ग_लिखो(priv, MIICOMMAND, MIICOMMAND_WRITE);

	क्रम (i = 0; i < 5; i++) अणु
		u32 stat = ethoc_पढ़ो(priv, MIISTATUS);
		अगर (!(stat & MIISTATUS_BUSY)) अणु
			/* reset MII command रेजिस्टर */
			ethoc_ग_लिखो(priv, MIICOMMAND, 0);
			वापस 0;
		पूर्ण
		usleep_range(100, 200);
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल व्योम ethoc_mdio_poll(काष्ठा net_device *dev)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	bool changed = false;
	u32 mode;

	अगर (priv->old_link != phydev->link) अणु
		changed = true;
		priv->old_link = phydev->link;
	पूर्ण

	अगर (priv->old_duplex != phydev->duplex) अणु
		changed = true;
		priv->old_duplex = phydev->duplex;
	पूर्ण

	अगर (!changed)
		वापस;

	mode = ethoc_पढ़ो(priv, MODER);
	अगर (phydev->duplex == DUPLEX_FULL)
		mode |= MODER_FULLD;
	अन्यथा
		mode &= ~MODER_FULLD;
	ethoc_ग_लिखो(priv, MODER, mode);

	phy_prपूर्णांक_status(phydev);
पूर्ण

अटल पूर्णांक ethoc_mdio_probe(काष्ठा net_device *dev)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);
	काष्ठा phy_device *phy;
	पूर्णांक err;

	अगर (priv->phy_id != -1)
		phy = mdiobus_get_phy(priv->mdio, priv->phy_id);
	अन्यथा
		phy = phy_find_first(priv->mdio);

	अगर (!phy) अणु
		dev_err(&dev->dev, "no PHY found\n");
		वापस -ENXIO;
	पूर्ण

	priv->old_duplex = -1;
	priv->old_link = -1;

	err = phy_connect_direct(dev, phy, ethoc_mdio_poll,
				 PHY_INTERFACE_MODE_GMII);
	अगर (err) अणु
		dev_err(&dev->dev, "could not attach to PHY\n");
		वापस err;
	पूर्ण

	phy_set_max_speed(phy, SPEED_100);

	वापस 0;
पूर्ण

अटल पूर्णांक ethoc_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);
	पूर्णांक ret;

	ret = request_irq(dev->irq, ethoc_पूर्णांकerrupt, IRQF_SHARED,
			dev->name, dev);
	अगर (ret)
		वापस ret;

	napi_enable(&priv->napi);

	ethoc_init_ring(priv, dev->mem_start);
	ethoc_reset(priv);

	अगर (netअगर_queue_stopped(dev)) अणु
		dev_dbg(&dev->dev, " resuming queue\n");
		netअगर_wake_queue(dev);
	पूर्ण अन्यथा अणु
		dev_dbg(&dev->dev, " starting queue\n");
		netअगर_start_queue(dev);
	पूर्ण

	priv->old_link = -1;
	priv->old_duplex = -1;

	phy_start(dev->phydev);

	अगर (netअगर_msg_अगरup(priv)) अणु
		dev_info(&dev->dev, "I/O: %08lx Memory: %08lx-%08lx\n",
				dev->base_addr, dev->mem_start, dev->mem_end);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ethoc_stop(काष्ठा net_device *dev)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);

	napi_disable(&priv->napi);

	अगर (dev->phydev)
		phy_stop(dev->phydev);

	ethoc_disable_rx_and_tx(priv);
	मुक्त_irq(dev->irq, dev);

	अगर (!netअगर_queue_stopped(dev))
		netअगर_stop_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ethoc_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);
	काष्ठा mii_ioctl_data *mdio = अगर_mii(अगरr);
	काष्ठा phy_device *phy = शून्य;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	अगर (cmd != SIOCGMIIPHY) अणु
		अगर (mdio->phy_id >= PHY_MAX_ADDR)
			वापस -दुस्फल;

		phy = mdiobus_get_phy(priv->mdio, mdio->phy_id);
		अगर (!phy)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		phy = dev->phydev;
	पूर्ण

	वापस phy_mii_ioctl(phy, अगरr, cmd);
पूर्ण

अटल व्योम ethoc_करो_set_mac_address(काष्ठा net_device *dev)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);
	अचिन्हित अक्षर *mac = dev->dev_addr;

	ethoc_ग_लिखो(priv, MAC_ADDR0, (mac[2] << 24) | (mac[3] << 16) |
				     (mac[4] <<  8) | (mac[5] <<  0));
	ethoc_ग_लिखो(priv, MAC_ADDR1, (mac[0] <<  8) | (mac[1] <<  0));
पूर्ण

अटल पूर्णांक ethoc_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	स्थिर काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;
	स_नकल(dev->dev_addr, addr->sa_data, ETH_ALEN);
	ethoc_करो_set_mac_address(dev);
	वापस 0;
पूर्ण

अटल व्योम ethoc_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);
	u32 mode = ethoc_पढ़ो(priv, MODER);
	काष्ठा netdev_hw_addr *ha;
	u32 hash[2] = अणु 0, 0 पूर्ण;

	/* set loopback mode अगर requested */
	अगर (dev->flags & IFF_LOOPBACK)
		mode |=  MODER_LOOP;
	अन्यथा
		mode &= ~MODER_LOOP;

	/* receive broadcast frames अगर requested */
	अगर (dev->flags & IFF_BROADCAST)
		mode &= ~MODER_BRO;
	अन्यथा
		mode |=  MODER_BRO;

	/* enable promiscuous mode अगर requested */
	अगर (dev->flags & IFF_PROMISC)
		mode |=  MODER_PRO;
	अन्यथा
		mode &= ~MODER_PRO;

	ethoc_ग_लिखो(priv, MODER, mode);

	/* receive multicast frames */
	अगर (dev->flags & IFF_ALLMULTI) अणु
		hash[0] = 0xffffffff;
		hash[1] = 0xffffffff;
	पूर्ण अन्यथा अणु
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			u32 crc = ether_crc(ETH_ALEN, ha->addr);
			पूर्णांक bit = (crc >> 26) & 0x3f;
			hash[bit >> 5] |= 1 << (bit & 0x1f);
		पूर्ण
	पूर्ण

	ethoc_ग_लिखो(priv, ETH_HASH0, hash[0]);
	ethoc_ग_लिखो(priv, ETH_HASH1, hash[1]);
पूर्ण

अटल पूर्णांक ethoc_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	वापस -ENOSYS;
पूर्ण

अटल व्योम ethoc_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);
	u32 pending = ethoc_पढ़ो(priv, INT_SOURCE);
	अगर (likely(pending))
		ethoc_पूर्णांकerrupt(dev->irq, dev);
पूर्ण

अटल netdev_tx_t ethoc_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);
	काष्ठा ethoc_bd bd;
	अचिन्हित पूर्णांक entry;
	व्योम *dest;

	अगर (skb_put_padto(skb, ETHOC_ZLEN)) अणु
		dev->stats.tx_errors++;
		जाओ out_no_मुक्त;
	पूर्ण

	अगर (unlikely(skb->len > ETHOC_बफ_मान)) अणु
		dev->stats.tx_errors++;
		जाओ out;
	पूर्ण

	entry = priv->cur_tx % priv->num_tx;
	spin_lock_irq(&priv->lock);
	priv->cur_tx++;

	ethoc_पढ़ो_bd(priv, entry, &bd);
	अगर (unlikely(skb->len < ETHOC_ZLEN))
		bd.stat |=  TX_BD_PAD;
	अन्यथा
		bd.stat &= ~TX_BD_PAD;

	dest = priv->vma[entry];
	स_नकल_toio(dest, skb->data, skb->len);

	bd.stat &= ~(TX_BD_STATS | TX_BD_LEN_MASK);
	bd.stat |= TX_BD_LEN(skb->len);
	ethoc_ग_लिखो_bd(priv, entry, &bd);

	bd.stat |= TX_BD_READY;
	ethoc_ग_लिखो_bd(priv, entry, &bd);

	अगर (priv->cur_tx == (priv->dty_tx + priv->num_tx)) अणु
		dev_dbg(&dev->dev, "stopping queue\n");
		netअगर_stop_queue(dev);
	पूर्ण

	spin_unlock_irq(&priv->lock);
	skb_tx_बारtamp(skb);
out:
	dev_kमुक्त_skb(skb);
out_no_मुक्त:
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक ethoc_get_regs_len(काष्ठा net_device *netdev)
अणु
	वापस ETH_END;
पूर्ण

अटल व्योम ethoc_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			   व्योम *p)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);
	u32 *regs_buff = p;
	अचिन्हित i;

	regs->version = 0;
	क्रम (i = 0; i < ETH_END / माप(u32); ++i)
		regs_buff[i] = ethoc_पढ़ो(priv, i * माप(u32));
पूर्ण

अटल व्योम ethoc_get_ringparam(काष्ठा net_device *dev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);

	ring->rx_max_pending = priv->num_bd - 1;
	ring->rx_mini_max_pending = 0;
	ring->rx_jumbo_max_pending = 0;
	ring->tx_max_pending = priv->num_bd - 1;

	ring->rx_pending = priv->num_rx;
	ring->rx_mini_pending = 0;
	ring->rx_jumbo_pending = 0;
	ring->tx_pending = priv->num_tx;
पूर्ण

अटल पूर्णांक ethoc_set_ringparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ethoc *priv = netdev_priv(dev);

	अगर (ring->tx_pending < 1 || ring->rx_pending < 1 ||
	    ring->tx_pending + ring->rx_pending > priv->num_bd)
		वापस -EINVAL;
	अगर (ring->rx_mini_pending || ring->rx_jumbo_pending)
		वापस -EINVAL;

	अगर (netअगर_running(dev)) अणु
		netअगर_tx_disable(dev);
		ethoc_disable_rx_and_tx(priv);
		ethoc_disable_irq(priv, INT_MASK_TX | INT_MASK_RX);
		synchronize_irq(dev->irq);
	पूर्ण

	priv->num_tx = roundकरोwn_घात_of_two(ring->tx_pending);
	priv->num_rx = ring->rx_pending;
	ethoc_init_ring(priv, dev->mem_start);

	अगर (netअगर_running(dev)) अणु
		ethoc_enable_irq(priv, INT_MASK_TX | INT_MASK_RX);
		ethoc_enable_rx_and_tx(priv);
		netअगर_wake_queue(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ethoc_ethtool_ops = अणु
	.get_regs_len = ethoc_get_regs_len,
	.get_regs = ethoc_get_regs,
	.nway_reset = phy_ethtool_nway_reset,
	.get_link = ethtool_op_get_link,
	.get_ringparam = ethoc_get_ringparam,
	.set_ringparam = ethoc_set_ringparam,
	.get_ts_info = ethtool_op_get_ts_info,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops ethoc_netdev_ops = अणु
	.nकरो_खोलो = ethoc_खोलो,
	.nकरो_stop = ethoc_stop,
	.nकरो_करो_ioctl = ethoc_ioctl,
	.nकरो_set_mac_address = ethoc_set_mac_address,
	.nकरो_set_rx_mode = ethoc_set_multicast_list,
	.nकरो_change_mtu = ethoc_change_mtu,
	.nकरो_tx_समयout = ethoc_tx_समयout,
	.nकरो_start_xmit = ethoc_start_xmit,
पूर्ण;

/**
 * ethoc_probe - initialize OpenCores ethernet MAC
 * @pdev:	platक्रमm device
 */
अटल पूर्णांक ethoc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *netdev = शून्य;
	काष्ठा resource *res = शून्य;
	काष्ठा resource *mmio = शून्य;
	काष्ठा resource *mem = शून्य;
	काष्ठा ethoc *priv = शून्य;
	पूर्णांक num_bd;
	पूर्णांक ret = 0;
	काष्ठा ethoc_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	u32 eth_clkfreq = pdata ? pdata->eth_clkfreq : 0;

	/* allocate networking device */
	netdev = alloc_etherdev(माप(काष्ठा ethoc));
	अगर (!netdev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);
	platक्रमm_set_drvdata(pdev, netdev);

	/* obtain I/O memory space */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "cannot obtain I/O memory space\n");
		ret = -ENXIO;
		जाओ मुक्त;
	पूर्ण

	mmio = devm_request_mem_region(&pdev->dev, res->start,
			resource_size(res), res->name);
	अगर (!mmio) अणु
		dev_err(&pdev->dev, "cannot request I/O memory space\n");
		ret = -ENXIO;
		जाओ मुक्त;
	पूर्ण

	netdev->base_addr = mmio->start;

	/* obtain buffer memory space */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res) अणु
		mem = devm_request_mem_region(&pdev->dev, res->start,
			resource_size(res), res->name);
		अगर (!mem) अणु
			dev_err(&pdev->dev, "cannot request memory space\n");
			ret = -ENXIO;
			जाओ मुक्त;
		पूर्ण

		netdev->mem_start = mem->start;
		netdev->mem_end   = mem->end;
	पूर्ण


	/* obtain device IRQ number */
	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "cannot obtain IRQ\n");
		ret = -ENXIO;
		जाओ मुक्त;
	पूर्ण

	netdev->irq = res->start;

	/* setup driver-निजी data */
	priv = netdev_priv(netdev);
	priv->netdev = netdev;

	priv->iobase = devm_ioremap(&pdev->dev, netdev->base_addr,
			resource_size(mmio));
	अगर (!priv->iobase) अणु
		dev_err(&pdev->dev, "cannot remap I/O memory space\n");
		ret = -ENXIO;
		जाओ मुक्त;
	पूर्ण

	अगर (netdev->mem_end) अणु
		priv->membase = devm_ioremap(&pdev->dev,
			netdev->mem_start, resource_size(mem));
		अगर (!priv->membase) अणु
			dev_err(&pdev->dev, "cannot remap memory space\n");
			ret = -ENXIO;
			जाओ मुक्त;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Allocate buffer memory */
		priv->membase = dmam_alloc_coherent(&pdev->dev,
			buffer_size, (व्योम *)&netdev->mem_start,
			GFP_KERNEL);
		अगर (!priv->membase) अणु
			dev_err(&pdev->dev, "cannot allocate %dB buffer\n",
				buffer_size);
			ret = -ENOMEM;
			जाओ मुक्त;
		पूर्ण
		netdev->mem_end = netdev->mem_start + buffer_size;
	पूर्ण

	priv->big_endian = pdata ? pdata->big_endian :
		of_device_is_big_endian(pdev->dev.of_node);

	/* calculate the number of TX/RX buffers, maximum 128 supported */
	num_bd = min_t(अचिन्हित पूर्णांक,
		128, (netdev->mem_end - netdev->mem_start + 1) / ETHOC_बफ_मान);
	अगर (num_bd < 4) अणु
		ret = -ENODEV;
		जाओ मुक्त;
	पूर्ण
	priv->num_bd = num_bd;
	/* num_tx must be a घातer of two */
	priv->num_tx = roundकरोwn_घात_of_two(num_bd >> 1);
	priv->num_rx = num_bd - priv->num_tx;

	dev_dbg(&pdev->dev, "ethoc: num_tx: %d num_rx: %d\n",
		priv->num_tx, priv->num_rx);

	priv->vma = devm_kसुस्मृति(&pdev->dev, num_bd, माप(व्योम *),
				 GFP_KERNEL);
	अगर (!priv->vma) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	/* Allow the platक्रमm setup code to pass in a MAC address. */
	अगर (pdata) अणु
		ether_addr_copy(netdev->dev_addr, pdata->hwaddr);
		priv->phy_id = pdata->phy_id;
	पूर्ण अन्यथा अणु
		of_get_mac_address(pdev->dev.of_node, netdev->dev_addr);
		priv->phy_id = -1;
	पूर्ण

	/* Check that the given MAC address is valid. If it isn't, पढ़ो the
	 * current MAC from the controller.
	 */
	अगर (!is_valid_ether_addr(netdev->dev_addr))
		ethoc_get_mac_address(netdev, netdev->dev_addr);

	/* Check the MAC again क्रम validity, अगर it still isn't choose and
	 * program a अक्रमom one.
	 */
	अगर (!is_valid_ether_addr(netdev->dev_addr))
		eth_hw_addr_अक्रमom(netdev);

	ethoc_करो_set_mac_address(netdev);

	/* Allow the platक्रमm setup code to adjust MII management bus घड़ी. */
	अगर (!eth_clkfreq) अणु
		काष्ठा clk *clk = devm_clk_get(&pdev->dev, शून्य);

		अगर (!IS_ERR(clk)) अणु
			priv->clk = clk;
			clk_prepare_enable(clk);
			eth_clkfreq = clk_get_rate(clk);
		पूर्ण
	पूर्ण
	अगर (eth_clkfreq) अणु
		u32 clkभाग = MIIMODER_CLKDIV(eth_clkfreq / 2500000 + 1);

		अगर (!clkभाग)
			clkभाग = 2;
		dev_dbg(&pdev->dev, "setting MII clkdiv to %u\n", clkभाग);
		ethoc_ग_लिखो(priv, MIIMODER,
			    (ethoc_पढ़ो(priv, MIIMODER) & MIIMODER_NOPRE) |
			    clkभाग);
	पूर्ण

	/* रेजिस्टर MII bus */
	priv->mdio = mdiobus_alloc();
	अगर (!priv->mdio) अणु
		ret = -ENOMEM;
		जाओ मुक्त2;
	पूर्ण

	priv->mdio->name = "ethoc-mdio";
	snम_लिखो(priv->mdio->id, MII_BUS_ID_SIZE, "%s-%d",
			priv->mdio->name, pdev->id);
	priv->mdio->पढ़ो = ethoc_mdio_पढ़ो;
	priv->mdio->ग_लिखो = ethoc_mdio_ग_लिखो;
	priv->mdio->priv = priv;

	ret = mdiobus_रेजिस्टर(priv->mdio);
	अगर (ret) अणु
		dev_err(&netdev->dev, "failed to register MDIO bus\n");
		जाओ मुक्त3;
	पूर्ण

	ret = ethoc_mdio_probe(netdev);
	अगर (ret) अणु
		dev_err(&netdev->dev, "failed to probe MDIO bus\n");
		जाओ error;
	पूर्ण

	/* setup the net_device काष्ठाure */
	netdev->netdev_ops = &ethoc_netdev_ops;
	netdev->watchकरोg_समयo = ETHOC_TIMEOUT;
	netdev->features |= 0;
	netdev->ethtool_ops = &ethoc_ethtool_ops;

	/* setup NAPI */
	netअगर_napi_add(netdev, &priv->napi, ethoc_poll, 64);

	spin_lock_init(&priv->lock);

	ret = रेजिस्टर_netdev(netdev);
	अगर (ret < 0) अणु
		dev_err(&netdev->dev, "failed to register interface\n");
		जाओ error2;
	पूर्ण

	जाओ out;

error2:
	netअगर_napi_del(&priv->napi);
error:
	mdiobus_unरेजिस्टर(priv->mdio);
मुक्त3:
	mdiobus_मुक्त(priv->mdio);
मुक्त2:
	clk_disable_unprepare(priv->clk);
मुक्त:
	मुक्त_netdev(netdev);
out:
	वापस ret;
पूर्ण

/**
 * ethoc_हटाओ - shutकरोwn OpenCores ethernet MAC
 * @pdev:	platक्रमm device
 */
अटल पूर्णांक ethoc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *netdev = platक्रमm_get_drvdata(pdev);
	काष्ठा ethoc *priv = netdev_priv(netdev);

	अगर (netdev) अणु
		netअगर_napi_del(&priv->napi);
		phy_disconnect(netdev->phydev);

		अगर (priv->mdio) अणु
			mdiobus_unरेजिस्टर(priv->mdio);
			mdiobus_मुक्त(priv->mdio);
		पूर्ण
		clk_disable_unprepare(priv->clk);
		unरेजिस्टर_netdev(netdev);
		मुक्त_netdev(netdev);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ethoc_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक ethoc_resume(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -ENOSYS;
पूर्ण
#अन्यथा
# define ethoc_suspend शून्य
# define ethoc_resume  शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id ethoc_match[] = अणु
	अणु .compatible = "opencores,ethoc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ethoc_match);

अटल काष्ठा platक्रमm_driver ethoc_driver = अणु
	.probe   = ethoc_probe,
	.हटाओ  = ethoc_हटाओ,
	.suspend = ethoc_suspend,
	.resume  = ethoc_resume,
	.driver  = अणु
		.name = "ethoc",
		.of_match_table = ethoc_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ethoc_driver);

MODULE_AUTHOR("Thierry Reding <thierry.reding@avionic-design.de>");
MODULE_DESCRIPTION("OpenCores Ethernet MAC driver");
MODULE_LICENSE("GPL v2");

