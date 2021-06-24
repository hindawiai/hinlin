<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RDC R6040 Fast Ethernet MAC support
 *
 * Copyright (C) 2004 Sten Wang <sten.wang@rdc.com.tw>
 * Copyright (C) 2007
 *	Daniel Gimpelevich <daniel@gimpelevich.san-francisco.ca.us>
 * Copyright (C) 2007-2012 Florian Fainelli <f.fainelli@gmail.com>
*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/crc32.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/phy.h>

#समावेश <यंत्र/processor.h>

#घोषणा DRV_NAME	"r6040"
#घोषणा DRV_VERSION	"0.29"
#घोषणा DRV_RELDATE	"04Jul2016"

/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT	(6000 * HZ / 1000)

/* RDC MAC I/O Size */
#घोषणा R6040_IO_SIZE	256

/* MAX RDC MAC */
#घोषणा MAX_MAC		2

/* MAC रेजिस्टरs */
#घोषणा MCR0		0x00	/* Control रेजिस्टर 0 */
#घोषणा  MCR0_RCVEN	0x0002	/* Receive enable */
#घोषणा  MCR0_PROMISC	0x0020	/* Promiscuous mode */
#घोषणा  MCR0_HASH_EN	0x0100	/* Enable multicast hash table function */
#घोषणा  MCR0_XMTEN	0x1000	/* Transmission enable */
#घोषणा  MCR0_FD	0x8000	/* Full/Half duplex */
#घोषणा MCR1		0x04	/* Control रेजिस्टर 1 */
#घोषणा  MAC_RST	0x0001	/* Reset the MAC */
#घोषणा MBCR		0x08	/* Bus control */
#घोषणा MT_ICR		0x0C	/* TX पूर्णांकerrupt control */
#घोषणा MR_ICR		0x10	/* RX पूर्णांकerrupt control */
#घोषणा MTPR		0x14	/* TX poll command रेजिस्टर */
#घोषणा  TM2TX		0x0001	/* Trigger MAC to transmit */
#घोषणा MR_BSR		0x18	/* RX buffer size */
#घोषणा MR_DCR		0x1A	/* RX descriptor control */
#घोषणा MLSR		0x1C	/* Last status */
#घोषणा  TX_FIFO_UNDR	0x0200	/* TX FIFO under-run */
#घोषणा	 TX_EXCEEDC	0x2000	/* Transmit exceed collision */
#घोषणा  TX_LATEC	0x4000	/* Transmit late collision */
#घोषणा MMDIO		0x20	/* MDIO control रेजिस्टर */
#घोषणा  MDIO_WRITE	0x4000	/* MDIO ग_लिखो */
#घोषणा  MDIO_READ	0x2000	/* MDIO पढ़ो */
#घोषणा MMRD		0x24	/* MDIO पढ़ो data रेजिस्टर */
#घोषणा MMWD		0x28	/* MDIO ग_लिखो data रेजिस्टर */
#घोषणा MTD_SA0		0x2C	/* TX descriptor start address 0 */
#घोषणा MTD_SA1		0x30	/* TX descriptor start address 1 */
#घोषणा MRD_SA0		0x34	/* RX descriptor start address 0 */
#घोषणा MRD_SA1		0x38	/* RX descriptor start address 1 */
#घोषणा MISR		0x3C	/* Status रेजिस्टर */
#घोषणा MIER		0x40	/* INT enable रेजिस्टर */
#घोषणा  MSK_INT	0x0000	/* Mask off पूर्णांकerrupts */
#घोषणा  RX_FINISH	0x0001  /* RX finished */
#घोषणा  RX_NO_DESC	0x0002  /* No RX descriptor available */
#घोषणा  RX_FIFO_FULL	0x0004  /* RX FIFO full */
#घोषणा  RX_EARLY	0x0008  /* RX early */
#घोषणा  TX_FINISH	0x0010  /* TX finished */
#घोषणा  TX_EARLY	0x0080  /* TX early */
#घोषणा  EVENT_OVRFL	0x0100  /* Event counter overflow */
#घोषणा  LINK_CHANGED	0x0200  /* PHY link changed */
#घोषणा ME_CISR		0x44	/* Event counter INT status */
#घोषणा ME_CIER		0x48	/* Event counter INT enable  */
#घोषणा MR_CNT		0x50	/* Successfully received packet counter */
#घोषणा ME_CNT0		0x52	/* Event counter 0 */
#घोषणा ME_CNT1		0x54	/* Event counter 1 */
#घोषणा ME_CNT2		0x56	/* Event counter 2 */
#घोषणा ME_CNT3		0x58	/* Event counter 3 */
#घोषणा MT_CNT		0x5A	/* Successfully transmit packet counter */
#घोषणा ME_CNT4		0x5C	/* Event counter 4 */
#घोषणा MP_CNT		0x5E	/* Pause frame counter रेजिस्टर */
#घोषणा MAR0		0x60	/* Hash table 0 */
#घोषणा MAR1		0x62	/* Hash table 1 */
#घोषणा MAR2		0x64	/* Hash table 2 */
#घोषणा MAR3		0x66	/* Hash table 3 */
#घोषणा MID_0L		0x68	/* Multicast address MID0 Low */
#घोषणा MID_0M		0x6A	/* Multicast address MID0 Medium */
#घोषणा MID_0H		0x6C	/* Multicast address MID0 High */
#घोषणा MID_1L		0x70	/* MID1 Low */
#घोषणा MID_1M		0x72	/* MID1 Medium */
#घोषणा MID_1H		0x74	/* MID1 High */
#घोषणा MID_2L		0x78	/* MID2 Low */
#घोषणा MID_2M		0x7A	/* MID2 Medium */
#घोषणा MID_2H		0x7C	/* MID2 High */
#घोषणा MID_3L		0x80	/* MID3 Low */
#घोषणा MID_3M		0x82	/* MID3 Medium */
#घोषणा MID_3H		0x84	/* MID3 High */
#घोषणा PHY_CC		0x88	/* PHY status change configuration रेजिस्टर */
#घोषणा  SCEN		0x8000	/* PHY status change enable */
#घोषणा  PHYAD_SHIFT	8	/* PHY address shअगरt */
#घोषणा  TMRDIV_SHIFT	0	/* Timer भागider shअगरt */
#घोषणा PHY_ST		0x8A	/* PHY status रेजिस्टर */
#घोषणा MAC_SM		0xAC	/* MAC status machine */
#घोषणा  MAC_SM_RST	0x0002	/* MAC status machine reset */
#घोषणा MAC_ID		0xBE	/* Identअगरier रेजिस्टर */

#घोषणा TX_DCNT		0x80	/* TX descriptor count */
#घोषणा RX_DCNT		0x80	/* RX descriptor count */
#घोषणा MAX_BUF_SIZE	0x600
#घोषणा RX_DESC_SIZE	(RX_DCNT * माप(काष्ठा r6040_descriptor))
#घोषणा TX_DESC_SIZE	(TX_DCNT * माप(काष्ठा r6040_descriptor))
#घोषणा MBCR_DEFAULT	0x012A	/* MAC Bus Control Register */
#घोषणा MCAST_MAX	3	/* Max number multicast addresses to filter */

#घोषणा MAC_DEF_TIMEOUT	2048	/* Default MAC पढ़ो/ग_लिखो operation समयout */

/* Descriptor status */
#घोषणा DSC_OWNER_MAC	0x8000	/* MAC is the owner of this descriptor */
#घोषणा DSC_RX_OK	0x4000	/* RX was successful */
#घोषणा DSC_RX_ERR	0x0800	/* RX PHY error */
#घोषणा DSC_RX_ERR_DRI	0x0400	/* RX dribble packet */
#घोषणा DSC_RX_ERR_BUF	0x0200	/* RX length exceeds buffer size */
#घोषणा DSC_RX_ERR_LONG	0x0100	/* RX length > maximum packet length */
#घोषणा DSC_RX_ERR_RUNT	0x0080	/* RX packet length < 64 byte */
#घोषणा DSC_RX_ERR_CRC	0x0040	/* RX CRC error */
#घोषणा DSC_RX_BCAST	0x0020	/* RX broadcast (no error) */
#घोषणा DSC_RX_MCAST	0x0010	/* RX multicast (no error) */
#घोषणा DSC_RX_MCH_HIT	0x0008	/* RX multicast hit in hash table (no error) */
#घोषणा DSC_RX_MIDH_HIT	0x0004	/* RX MID table hit (no error) */
#घोषणा DSC_RX_IDX_MID_MASK 3	/* RX mask क्रम the index of matched MIDx */

MODULE_AUTHOR("Sten Wang <sten.wang@rdc.com.tw>,"
	"Daniel Gimpelevich <daniel@gimpelevich.san-francisco.ca.us>,"
	"Florian Fainelli <f.fainelli@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("RDC R6040 NAPI PCI FastEthernet driver");
MODULE_VERSION(DRV_VERSION " " DRV_RELDATE);

/* RX and TX पूर्णांकerrupts that we handle */
#घोषणा RX_INTS			(RX_FIFO_FULL | RX_NO_DESC | RX_FINISH)
#घोषणा TX_INTS			(TX_FINISH)
#घोषणा INT_MASK		(RX_INTS | TX_INTS)

काष्ठा r6040_descriptor अणु
	u16	status, len;		/* 0-3 */
	__le32	buf;			/* 4-7 */
	__le32	ndesc;			/* 8-B */
	u32	rev1;			/* C-F */
	अक्षर	*vbufp;			/* 10-13 */
	काष्ठा r6040_descriptor *vndescp;	/* 14-17 */
	काष्ठा sk_buff *skb_ptr;	/* 18-1B */
	u32	rev2;			/* 1C-1F */
पूर्ण __aligned(32);

काष्ठा r6040_निजी अणु
	spinlock_t lock;		/* driver lock */
	काष्ठा pci_dev *pdev;
	काष्ठा r6040_descriptor *rx_insert_ptr;
	काष्ठा r6040_descriptor *rx_हटाओ_ptr;
	काष्ठा r6040_descriptor *tx_insert_ptr;
	काष्ठा r6040_descriptor *tx_हटाओ_ptr;
	काष्ठा r6040_descriptor *rx_ring;
	काष्ठा r6040_descriptor *tx_ring;
	dma_addr_t rx_ring_dma;
	dma_addr_t tx_ring_dma;
	u16	tx_मुक्त_desc;
	u16	mcr0;
	काष्ठा net_device *dev;
	काष्ठा mii_bus *mii_bus;
	काष्ठा napi_काष्ठा napi;
	व्योम __iomem *base;
	पूर्णांक old_link;
	पूर्णांक old_duplex;
पूर्ण;

अटल अक्षर version[] = DRV_NAME
	": RDC R6040 NAPI net driver,"
	"version "DRV_VERSION " (" DRV_RELDATE ")";

/* Read a word data from PHY Chip */
अटल पूर्णांक r6040_phy_पढ़ो(व्योम __iomem *ioaddr, पूर्णांक phy_addr, पूर्णांक reg)
अणु
	पूर्णांक limit = MAC_DEF_TIMEOUT;
	u16 cmd;

	ioग_लिखो16(MDIO_READ + reg + (phy_addr << 8), ioaddr + MMDIO);
	/* Wait क्रम the पढ़ो bit to be cleared */
	जबतक (limit--) अणु
		cmd = ioपढ़ो16(ioaddr + MMDIO);
		अगर (!(cmd & MDIO_READ))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (limit < 0)
		वापस -ETIMEDOUT;

	वापस ioपढ़ो16(ioaddr + MMRD);
पूर्ण

/* Write a word data from PHY Chip */
अटल पूर्णांक r6040_phy_ग_लिखो(व्योम __iomem *ioaddr,
					पूर्णांक phy_addr, पूर्णांक reg, u16 val)
अणु
	पूर्णांक limit = MAC_DEF_TIMEOUT;
	u16 cmd;

	ioग_लिखो16(val, ioaddr + MMWD);
	/* Write the command to the MDIO bus */
	ioग_लिखो16(MDIO_WRITE + reg + (phy_addr << 8), ioaddr + MMDIO);
	/* Wait क्रम the ग_लिखो bit to be cleared */
	जबतक (limit--) अणु
		cmd = ioपढ़ो16(ioaddr + MMDIO);
		अगर (!(cmd & MDIO_WRITE))
			अवरोध;
		udelay(1);
	पूर्ण

	वापस (limit < 0) ? -ETIMEDOUT : 0;
पूर्ण

अटल पूर्णांक r6040_mdiobus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक reg)
अणु
	काष्ठा net_device *dev = bus->priv;
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;

	वापस r6040_phy_पढ़ो(ioaddr, phy_addr, reg);
पूर्ण

अटल पूर्णांक r6040_mdiobus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_addr,
						पूर्णांक reg, u16 value)
अणु
	काष्ठा net_device *dev = bus->priv;
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;

	वापस r6040_phy_ग_लिखो(ioaddr, phy_addr, reg, value);
पूर्ण

अटल व्योम r6040_मुक्त_txbufs(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < TX_DCNT; i++) अणु
		अगर (lp->tx_insert_ptr->skb_ptr) अणु
			dma_unmap_single(&lp->pdev->dev,
					 le32_to_cpu(lp->tx_insert_ptr->buf),
					 MAX_BUF_SIZE, DMA_TO_DEVICE);
			dev_kमुक्त_skb(lp->tx_insert_ptr->skb_ptr);
			lp->tx_insert_ptr->skb_ptr = शून्य;
		पूर्ण
		lp->tx_insert_ptr = lp->tx_insert_ptr->vndescp;
	पूर्ण
पूर्ण

अटल व्योम r6040_मुक्त_rxbufs(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < RX_DCNT; i++) अणु
		अगर (lp->rx_insert_ptr->skb_ptr) अणु
			dma_unmap_single(&lp->pdev->dev,
					 le32_to_cpu(lp->rx_insert_ptr->buf),
					 MAX_BUF_SIZE, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(lp->rx_insert_ptr->skb_ptr);
			lp->rx_insert_ptr->skb_ptr = शून्य;
		पूर्ण
		lp->rx_insert_ptr = lp->rx_insert_ptr->vndescp;
	पूर्ण
पूर्ण

अटल व्योम r6040_init_ring_desc(काष्ठा r6040_descriptor *desc_ring,
				 dma_addr_t desc_dma, पूर्णांक size)
अणु
	काष्ठा r6040_descriptor *desc = desc_ring;
	dma_addr_t mapping = desc_dma;

	जबतक (size-- > 0) अणु
		mapping += माप(*desc);
		desc->ndesc = cpu_to_le32(mapping);
		desc->vndescp = desc + 1;
		desc++;
	पूर्ण
	desc--;
	desc->ndesc = cpu_to_le32(desc_dma);
	desc->vndescp = desc_ring;
पूर्ण

अटल व्योम r6040_init_txbufs(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);

	lp->tx_मुक्त_desc = TX_DCNT;

	lp->tx_हटाओ_ptr = lp->tx_insert_ptr = lp->tx_ring;
	r6040_init_ring_desc(lp->tx_ring, lp->tx_ring_dma, TX_DCNT);
पूर्ण

अटल पूर्णांक r6040_alloc_rxbufs(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	काष्ठा r6040_descriptor *desc;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	lp->rx_हटाओ_ptr = lp->rx_insert_ptr = lp->rx_ring;
	r6040_init_ring_desc(lp->rx_ring, lp->rx_ring_dma, RX_DCNT);

	/* Allocate skbs क्रम the rx descriptors */
	desc = lp->rx_ring;
	करो अणु
		skb = netdev_alloc_skb(dev, MAX_BUF_SIZE);
		अगर (!skb) अणु
			rc = -ENOMEM;
			जाओ err_निकास;
		पूर्ण
		desc->skb_ptr = skb;
		desc->buf = cpu_to_le32(dma_map_single(&lp->pdev->dev,
						       desc->skb_ptr->data,
						       MAX_BUF_SIZE,
						       DMA_FROM_DEVICE));
		desc->status = DSC_OWNER_MAC;
		desc = desc->vndescp;
	पूर्ण जबतक (desc != lp->rx_ring);

	वापस 0;

err_निकास:
	/* Deallocate all previously allocated skbs */
	r6040_मुक्त_rxbufs(dev);
	वापस rc;
पूर्ण

अटल व्योम r6040_reset_mac(काष्ठा r6040_निजी *lp)
अणु
	व्योम __iomem *ioaddr = lp->base;
	पूर्णांक limit = MAC_DEF_TIMEOUT;
	u16 cmd;

	ioग_लिखो16(MAC_RST, ioaddr + MCR1);
	जबतक (limit--) अणु
		cmd = ioपढ़ो16(ioaddr + MCR1);
		अगर (cmd & MAC_RST)
			अवरोध;
	पूर्ण

	/* Reset पूर्णांकernal state machine */
	ioग_लिखो16(MAC_SM_RST, ioaddr + MAC_SM);
	ioग_लिखो16(0, ioaddr + MAC_SM);
	mdelay(5);
पूर्ण

अटल व्योम r6040_init_mac_regs(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;

	/* Mask Off Interrupt */
	ioग_लिखो16(MSK_INT, ioaddr + MIER);

	/* Reset RDC MAC */
	r6040_reset_mac(lp);

	/* MAC Bus Control Register */
	ioग_लिखो16(MBCR_DEFAULT, ioaddr + MBCR);

	/* Buffer Size Register */
	ioग_लिखो16(MAX_BUF_SIZE, ioaddr + MR_BSR);

	/* Write TX ring start address */
	ioग_लिखो16(lp->tx_ring_dma, ioaddr + MTD_SA0);
	ioग_लिखो16(lp->tx_ring_dma >> 16, ioaddr + MTD_SA1);

	/* Write RX ring start address */
	ioग_लिखो16(lp->rx_ring_dma, ioaddr + MRD_SA0);
	ioग_लिखो16(lp->rx_ring_dma >> 16, ioaddr + MRD_SA1);

	/* Set पूर्णांकerrupt रुकोing समय and packet numbers */
	ioग_लिखो16(0, ioaddr + MT_ICR);
	ioग_लिखो16(0, ioaddr + MR_ICR);

	/* Enable पूर्णांकerrupts */
	ioग_लिखो16(INT_MASK, ioaddr + MIER);

	/* Enable TX and RX */
	ioग_लिखो16(lp->mcr0 | MCR0_RCVEN, ioaddr);

	/* Let TX poll the descriptors
	 * we may got called by r6040_tx_समयout which has left
	 * some unsent tx buffers */
	ioग_लिखो16(TM2TX, ioaddr + MTPR);
पूर्ण

अटल व्योम r6040_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा r6040_निजी *priv = netdev_priv(dev);
	व्योम __iomem *ioaddr = priv->base;

	netdev_warn(dev, "transmit timed out, int enable %4.4x "
		"status %4.4x\n",
		ioपढ़ो16(ioaddr + MIER),
		ioपढ़ो16(ioaddr + MISR));

	dev->stats.tx_errors++;

	/* Reset MAC and re-init all रेजिस्टरs */
	r6040_init_mac_regs(dev);
पूर्ण

अटल काष्ठा net_device_stats *r6040_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *priv = netdev_priv(dev);
	व्योम __iomem *ioaddr = priv->base;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	dev->stats.rx_crc_errors += ioपढ़ो8(ioaddr + ME_CNT1);
	dev->stats.multicast += ioपढ़ो8(ioaddr + ME_CNT0);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस &dev->stats;
पूर्ण

/* Stop RDC MAC and Free the allocated resource */
अटल व्योम r6040_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	u16 *adrp;

	/* Stop MAC */
	ioग_लिखो16(MSK_INT, ioaddr + MIER);	/* Mask Off Interrupt */

	/* Reset RDC MAC */
	r6040_reset_mac(lp);

	/* Restore MAC Address to MIDx */
	adrp = (u16 *) dev->dev_addr;
	ioग_लिखो16(adrp[0], ioaddr + MID_0L);
	ioग_लिखो16(adrp[1], ioaddr + MID_0M);
	ioग_लिखो16(adrp[2], ioaddr + MID_0H);
पूर्ण

अटल पूर्णांक r6040_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	काष्ठा pci_dev *pdev = lp->pdev;

	phy_stop(dev->phydev);
	napi_disable(&lp->napi);
	netअगर_stop_queue(dev);

	spin_lock_irq(&lp->lock);
	r6040_करोwn(dev);

	/* Free RX buffer */
	r6040_मुक्त_rxbufs(dev);

	/* Free TX buffer */
	r6040_मुक्त_txbufs(dev);

	spin_unlock_irq(&lp->lock);

	मुक्त_irq(dev->irq, dev);

	/* Free Descriptor memory */
	अगर (lp->rx_ring) अणु
		dma_मुक्त_coherent(&pdev->dev, RX_DESC_SIZE, lp->rx_ring,
				  lp->rx_ring_dma);
		lp->rx_ring = शून्य;
	पूर्ण

	अगर (lp->tx_ring) अणु
		dma_मुक्त_coherent(&pdev->dev, TX_DESC_SIZE, lp->tx_ring,
				  lp->tx_ring_dma);
		lp->tx_ring = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक r6040_rx(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा r6040_निजी *priv = netdev_priv(dev);
	काष्ठा r6040_descriptor *descptr = priv->rx_हटाओ_ptr;
	काष्ठा sk_buff *skb_ptr, *new_skb;
	पूर्णांक count = 0;
	u16 err;

	/* Limit not reached and the descriptor beदीर्घs to the CPU */
	जबतक (count < limit && !(descptr->status & DSC_OWNER_MAC)) अणु
		/* Read the descriptor status */
		err = descptr->status;
		/* Global error status set */
		अगर (err & DSC_RX_ERR) अणु
			/* RX dribble */
			अगर (err & DSC_RX_ERR_DRI)
				dev->stats.rx_frame_errors++;
			/* Buffer length exceeded */
			अगर (err & DSC_RX_ERR_BUF)
				dev->stats.rx_length_errors++;
			/* Packet too दीर्घ */
			अगर (err & DSC_RX_ERR_LONG)
				dev->stats.rx_length_errors++;
			/* Packet < 64 bytes */
			अगर (err & DSC_RX_ERR_RUNT)
				dev->stats.rx_length_errors++;
			/* CRC error */
			अगर (err & DSC_RX_ERR_CRC) अणु
				spin_lock(&priv->lock);
				dev->stats.rx_crc_errors++;
				spin_unlock(&priv->lock);
			पूर्ण
			जाओ next_descr;
		पूर्ण

		/* Packet successfully received */
		new_skb = netdev_alloc_skb(dev, MAX_BUF_SIZE);
		अगर (!new_skb) अणु
			dev->stats.rx_dropped++;
			जाओ next_descr;
		पूर्ण
		skb_ptr = descptr->skb_ptr;
		skb_ptr->dev = priv->dev;

		/* Do not count the CRC */
		skb_put(skb_ptr, descptr->len - 4);
		dma_unmap_single(&priv->pdev->dev, le32_to_cpu(descptr->buf),
				 MAX_BUF_SIZE, DMA_FROM_DEVICE);
		skb_ptr->protocol = eth_type_trans(skb_ptr, priv->dev);

		/* Send to upper layer */
		netअगर_receive_skb(skb_ptr);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += descptr->len - 4;

		/* put new skb पूर्णांकo descriptor */
		descptr->skb_ptr = new_skb;
		descptr->buf = cpu_to_le32(dma_map_single(&priv->pdev->dev,
							  descptr->skb_ptr->data,
							  MAX_BUF_SIZE,
							  DMA_FROM_DEVICE));

next_descr:
		/* put the descriptor back to the MAC */
		descptr->status = DSC_OWNER_MAC;
		descptr = descptr->vndescp;
		count++;
	पूर्ण
	priv->rx_हटाओ_ptr = descptr;

	वापस count;
पूर्ण

अटल व्योम r6040_tx(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *priv = netdev_priv(dev);
	काष्ठा r6040_descriptor *descptr;
	व्योम __iomem *ioaddr = priv->base;
	काष्ठा sk_buff *skb_ptr;
	u16 err;

	spin_lock(&priv->lock);
	descptr = priv->tx_हटाओ_ptr;
	जबतक (priv->tx_मुक्त_desc < TX_DCNT) अणु
		/* Check क्रम errors */
		err = ioपढ़ो16(ioaddr + MLSR);

		अगर (err & TX_FIFO_UNDR)
			dev->stats.tx_fअगरo_errors++;
		अगर (err & (TX_EXCEEDC | TX_LATEC))
			dev->stats.tx_carrier_errors++;

		अगर (descptr->status & DSC_OWNER_MAC)
			अवरोध; /* Not complete */
		skb_ptr = descptr->skb_ptr;

		/* Statistic Counter */
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += skb_ptr->len;

		dma_unmap_single(&priv->pdev->dev, le32_to_cpu(descptr->buf),
				 skb_ptr->len, DMA_TO_DEVICE);
		/* Free buffer */
		dev_kमुक्त_skb(skb_ptr);
		descptr->skb_ptr = शून्य;
		/* To next descriptor */
		descptr = descptr->vndescp;
		priv->tx_मुक्त_desc++;
	पूर्ण
	priv->tx_हटाओ_ptr = descptr;

	अगर (priv->tx_मुक्त_desc)
		netअगर_wake_queue(dev);
	spin_unlock(&priv->lock);
पूर्ण

अटल पूर्णांक r6040_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा r6040_निजी *priv =
		container_of(napi, काष्ठा r6040_निजी, napi);
	काष्ठा net_device *dev = priv->dev;
	व्योम __iomem *ioaddr = priv->base;
	पूर्णांक work_करोne;

	r6040_tx(dev);

	work_करोne = r6040_rx(dev, budget);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		/* Enable RX/TX पूर्णांकerrupt */
		ioग_लिखो16(ioपढ़ो16(ioaddr + MIER) | RX_INTS | TX_INTS,
			  ioaddr + MIER);
	पूर्ण
	वापस work_करोne;
पूर्ण

/* The RDC पूर्णांकerrupt handler. */
अटल irqवापस_t r6040_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	u16 misr, status;

	/* Save MIER */
	misr = ioपढ़ो16(ioaddr + MIER);
	/* Mask off RDC MAC पूर्णांकerrupt */
	ioग_लिखो16(MSK_INT, ioaddr + MIER);
	/* Read MISR status and clear */
	status = ioपढ़ो16(ioaddr + MISR);

	अगर (status == 0x0000 || status == 0xffff) अणु
		/* Restore RDC MAC पूर्णांकerrupt */
		ioग_लिखो16(misr, ioaddr + MIER);
		वापस IRQ_NONE;
	पूर्ण

	/* RX पूर्णांकerrupt request */
	अगर (status & (RX_INTS | TX_INTS)) अणु
		अगर (status & RX_NO_DESC) अणु
			/* RX descriptor unavailable */
			dev->stats.rx_dropped++;
			dev->stats.rx_missed_errors++;
		पूर्ण
		अगर (status & RX_FIFO_FULL)
			dev->stats.rx_fअगरo_errors++;

		अगर (likely(napi_schedule_prep(&lp->napi))) अणु
			/* Mask off RX पूर्णांकerrupt */
			misr &= ~(RX_INTS | TX_INTS);
			__napi_schedule_irqoff(&lp->napi);
		पूर्ण
	पूर्ण

	/* Restore RDC MAC पूर्णांकerrupt */
	ioग_लिखो16(misr, ioaddr + MIER);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम r6040_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	r6040_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

/* Init RDC MAC */
अटल पूर्णांक r6040_up(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	पूर्णांक ret;

	/* Initialise and alloc RX/TX buffers */
	r6040_init_txbufs(dev);
	ret = r6040_alloc_rxbufs(dev);
	अगर (ret)
		वापस ret;

	/* improve perक्रमmance (by RDC guys) */
	r6040_phy_ग_लिखो(ioaddr, 30, 17,
			(r6040_phy_पढ़ो(ioaddr, 30, 17) | 0x4000));
	r6040_phy_ग_लिखो(ioaddr, 30, 17,
			~((~r6040_phy_पढ़ो(ioaddr, 30, 17)) | 0x2000));
	r6040_phy_ग_लिखो(ioaddr, 0, 19, 0x0000);
	r6040_phy_ग_लिखो(ioaddr, 0, 30, 0x01F0);

	/* Initialize all MAC रेजिस्टरs */
	r6040_init_mac_regs(dev);

	phy_start(dev->phydev);

	वापस 0;
पूर्ण


/* Read/set MAC address routines */
अटल व्योम r6040_mac_address(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	u16 *adrp;

	/* Reset MAC */
	r6040_reset_mac(lp);

	/* Restore MAC Address */
	adrp = (u16 *) dev->dev_addr;
	ioग_लिखो16(adrp[0], ioaddr + MID_0L);
	ioग_लिखो16(adrp[1], ioaddr + MID_0M);
	ioग_लिखो16(adrp[2], ioaddr + MID_0H);
पूर्ण

अटल पूर्णांक r6040_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	पूर्णांक ret;

	/* Request IRQ and Register पूर्णांकerrupt handler */
	ret = request_irq(dev->irq, r6040_पूर्णांकerrupt,
		IRQF_SHARED, dev->name, dev);
	अगर (ret)
		जाओ out;

	/* Set MAC address */
	r6040_mac_address(dev);

	/* Allocate Descriptor memory */
	lp->rx_ring =
		dma_alloc_coherent(&lp->pdev->dev, RX_DESC_SIZE,
				   &lp->rx_ring_dma, GFP_KERNEL);
	अगर (!lp->rx_ring) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_irq;
	पूर्ण

	lp->tx_ring =
		dma_alloc_coherent(&lp->pdev->dev, TX_DESC_SIZE,
				   &lp->tx_ring_dma, GFP_KERNEL);
	अगर (!lp->tx_ring) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_rx_ring;
	पूर्ण

	ret = r6040_up(dev);
	अगर (ret)
		जाओ err_मुक्त_tx_ring;

	napi_enable(&lp->napi);
	netअगर_start_queue(dev);

	वापस 0;

err_मुक्त_tx_ring:
	dma_मुक्त_coherent(&lp->pdev->dev, TX_DESC_SIZE, lp->tx_ring,
			  lp->tx_ring_dma);
err_मुक्त_rx_ring:
	dma_मुक्त_coherent(&lp->pdev->dev, RX_DESC_SIZE, lp->rx_ring,
			  lp->rx_ring_dma);
err_मुक्त_irq:
	मुक्त_irq(dev->irq, dev);
out:
	वापस ret;
पूर्ण

अटल netdev_tx_t r6040_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	काष्ठा r6040_descriptor *descptr;
	व्योम __iomem *ioaddr = lp->base;
	अचिन्हित दीर्घ flags;

	अगर (skb_put_padto(skb, ETH_ZLEN) < 0)
		वापस NETDEV_TX_OK;

	/* Critical Section */
	spin_lock_irqsave(&lp->lock, flags);

	/* TX resource check */
	अगर (!lp->tx_मुक्त_desc) अणु
		spin_unlock_irqrestore(&lp->lock, flags);
		netअगर_stop_queue(dev);
		netdev_err(dev, ": no tx descriptor\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* Set TX descriptor & Transmit it */
	lp->tx_मुक्त_desc--;
	descptr = lp->tx_insert_ptr;
	descptr->len = skb->len;
	descptr->skb_ptr = skb;
	descptr->buf = cpu_to_le32(dma_map_single(&lp->pdev->dev, skb->data,
						  skb->len, DMA_TO_DEVICE));
	descptr->status = DSC_OWNER_MAC;

	skb_tx_बारtamp(skb);

	/* Trigger the MAC to check the TX descriptor */
	अगर (!netdev_xmit_more() || netअगर_queue_stopped(dev))
		ioग_लिखो16(TM2TX, ioaddr + MTPR);
	lp->tx_insert_ptr = descptr->vndescp;

	/* If no tx resource, stop */
	अगर (!lp->tx_मुक्त_desc)
		netअगर_stop_queue(dev);

	spin_unlock_irqrestore(&lp->lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम r6040_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	अचिन्हित दीर्घ flags;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i;
	u16 *adrp;
	u16 hash_table[4] = अणु 0 पूर्ण;

	spin_lock_irqsave(&lp->lock, flags);

	/* Keep our MAC Address */
	adrp = (u16 *)dev->dev_addr;
	ioग_लिखो16(adrp[0], ioaddr + MID_0L);
	ioग_लिखो16(adrp[1], ioaddr + MID_0M);
	ioग_लिखो16(adrp[2], ioaddr + MID_0H);

	/* Clear AMCP & PROM bits */
	lp->mcr0 = ioपढ़ो16(ioaddr + MCR0) & ~(MCR0_PROMISC | MCR0_HASH_EN);

	/* Promiscuous mode */
	अगर (dev->flags & IFF_PROMISC)
		lp->mcr0 |= MCR0_PROMISC;

	/* Enable multicast hash table function to
	 * receive all multicast packets. */
	अन्यथा अगर (dev->flags & IFF_ALLMULTI) अणु
		lp->mcr0 |= MCR0_HASH_EN;

		क्रम (i = 0; i < MCAST_MAX ; i++) अणु
			ioग_लिखो16(0, ioaddr + MID_1L + 8 * i);
			ioग_लिखो16(0, ioaddr + MID_1M + 8 * i);
			ioग_लिखो16(0, ioaddr + MID_1H + 8 * i);
		पूर्ण

		क्रम (i = 0; i < 4; i++)
			hash_table[i] = 0xffff;
	पूर्ण
	/* Use पूर्णांकernal multicast address रेजिस्टरs अगर the number of
	 * multicast addresses is not greater than MCAST_MAX. */
	अन्यथा अगर (netdev_mc_count(dev) <= MCAST_MAX) अणु
		i = 0;
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			u16 *adrp = (u16 *) ha->addr;
			ioग_लिखो16(adrp[0], ioaddr + MID_1L + 8 * i);
			ioग_लिखो16(adrp[1], ioaddr + MID_1M + 8 * i);
			ioग_लिखो16(adrp[2], ioaddr + MID_1H + 8 * i);
			i++;
		पूर्ण
		जबतक (i < MCAST_MAX) अणु
			ioग_लिखो16(0, ioaddr + MID_1L + 8 * i);
			ioग_लिखो16(0, ioaddr + MID_1M + 8 * i);
			ioग_लिखो16(0, ioaddr + MID_1H + 8 * i);
			i++;
		पूर्ण
	पूर्ण
	/* Otherwise, Enable multicast hash table function. */
	अन्यथा अणु
		u32 crc;

		lp->mcr0 |= MCR0_HASH_EN;

		क्रम (i = 0; i < MCAST_MAX ; i++) अणु
			ioग_लिखो16(0, ioaddr + MID_1L + 8 * i);
			ioग_लिखो16(0, ioaddr + MID_1M + 8 * i);
			ioग_लिखो16(0, ioaddr + MID_1H + 8 * i);
		पूर्ण

		/* Build multicast hash table */
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			u8 *addrs = ha->addr;

			crc = ether_crc(ETH_ALEN, addrs);
			crc >>= 26;
			hash_table[crc >> 4] |= 1 << (crc & 0xf);
		पूर्ण
	पूर्ण

	ioग_लिखो16(lp->mcr0, ioaddr + MCR0);

	/* Fill the MAC hash tables with their values */
	अगर (lp->mcr0 & MCR0_HASH_EN) अणु
		ioग_लिखो16(hash_table[0], ioaddr + MAR0);
		ioग_लिखो16(hash_table[1], ioaddr + MAR1);
		ioग_लिखो16(hash_table[2], ioaddr + MAR2);
		ioग_लिखो16(hash_table[3], ioaddr + MAR3);
	पूर्ण

	spin_unlock_irqrestore(&lp->lock, flags);
पूर्ण

अटल व्योम netdev_get_drvinfo(काष्ठा net_device *dev,
			काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा r6040_निजी *rp = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(rp->pdev), माप(info->bus_info));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		= netdev_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_link_ksettings     = phy_ethtool_get_link_ksettings,
	.set_link_ksettings     = phy_ethtool_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops r6040_netdev_ops = अणु
	.nकरो_खोलो		= r6040_खोलो,
	.nकरो_stop		= r6040_बंद,
	.nकरो_start_xmit		= r6040_start_xmit,
	.nकरो_get_stats		= r6040_get_stats,
	.nकरो_set_rx_mode	= r6040_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_करो_ioctl		= phy_करो_ioctl,
	.nकरो_tx_समयout		= r6040_tx_समयout,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= r6040_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल व्योम r6040_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	पूर्णांक status_changed = 0;
	व्योम __iomem *ioaddr = lp->base;

	BUG_ON(!phydev);

	अगर (lp->old_link != phydev->link) अणु
		status_changed = 1;
		lp->old_link = phydev->link;
	पूर्ण

	/* reflect duplex change */
	अगर (phydev->link && (lp->old_duplex != phydev->duplex)) अणु
		lp->mcr0 |= (phydev->duplex == DUPLEX_FULL ? MCR0_FD : 0);
		ioग_लिखो16(lp->mcr0, ioaddr);

		status_changed = 1;
		lp->old_duplex = phydev->duplex;
	पूर्ण

	अगर (status_changed)
		phy_prपूर्णांक_status(phydev);
पूर्ण

अटल पूर्णांक r6040_mii_probe(काष्ठा net_device *dev)
अणु
	काष्ठा r6040_निजी *lp = netdev_priv(dev);
	काष्ठा phy_device *phydev = शून्य;

	phydev = phy_find_first(lp->mii_bus);
	अगर (!phydev) अणु
		dev_err(&lp->pdev->dev, "no PHY found\n");
		वापस -ENODEV;
	पूर्ण

	phydev = phy_connect(dev, phydev_name(phydev), &r6040_adjust_link,
			     PHY_INTERFACE_MODE_MII);

	अगर (IS_ERR(phydev)) अणु
		dev_err(&lp->pdev->dev, "could not attach to PHY\n");
		वापस PTR_ERR(phydev);
	पूर्ण

	phy_set_max_speed(phydev, SPEED_100);

	lp->old_link = 0;
	lp->old_duplex = -1;

	phy_attached_info(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक r6040_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा r6040_निजी *lp;
	व्योम __iomem *ioaddr;
	पूर्णांक err, io_size = R6040_IO_SIZE;
	अटल पूर्णांक card_idx = -1;
	पूर्णांक bar = 0;
	u16 *adrp;

	pr_info("%s\n", version);

	err = pci_enable_device(pdev);
	अगर (err)
		जाओ err_out;

	/* this should always be supported */
	err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(&pdev->dev, "32-bit PCI DMA addresses not supported by the card\n");
		जाओ err_out_disable_dev;
	पूर्ण
	err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(&pdev->dev, "32-bit PCI DMA addresses not supported by the card\n");
		जाओ err_out_disable_dev;
	पूर्ण

	/* IO Size check */
	अगर (pci_resource_len(pdev, bar) < io_size) अणु
		dev_err(&pdev->dev, "Insufficient PCI resources, aborting\n");
		err = -EIO;
		जाओ err_out_disable_dev;
	पूर्ण

	pci_set_master(pdev);

	dev = alloc_etherdev(माप(काष्ठा r6040_निजी));
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_out_disable_dev;
	पूर्ण
	SET_NETDEV_DEV(dev, &pdev->dev);
	lp = netdev_priv(dev);

	err = pci_request_regions(pdev, DRV_NAME);

	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to request PCI regions\n");
		जाओ err_out_मुक्त_dev;
	पूर्ण

	ioaddr = pci_iomap(pdev, bar, io_size);
	अगर (!ioaddr) अणु
		dev_err(&pdev->dev, "ioremap failed for device\n");
		err = -EIO;
		जाओ err_out_मुक्त_res;
	पूर्ण

	/* If PHY status change रेजिस्टर is still set to zero it means the
	 * bootloader didn't initialize it, so we set it to:
	 * - enable phy status change
	 * - enable all phy addresses
	 * - set to lowest समयr भागider */
	अगर (ioपढ़ो16(ioaddr + PHY_CC) == 0)
		ioग_लिखो16(SCEN | PHY_MAX_ADDR << PHYAD_SHIFT |
				7 << TMRDIV_SHIFT, ioaddr + PHY_CC);

	/* Init प्रणाली & device */
	lp->base = ioaddr;
	dev->irq = pdev->irq;

	spin_lock_init(&lp->lock);
	pci_set_drvdata(pdev, dev);

	/* Set MAC address */
	card_idx++;

	adrp = (u16 *)dev->dev_addr;
	adrp[0] = ioपढ़ो16(ioaddr + MID_0L);
	adrp[1] = ioपढ़ो16(ioaddr + MID_0M);
	adrp[2] = ioपढ़ो16(ioaddr + MID_0H);

	/* Some bootloader/BIOSes करो not initialize
	 * MAC address, warn about that */
	अगर (!(adrp[0] || adrp[1] || adrp[2])) अणु
		netdev_warn(dev, "MAC address not initialized, "
					"generating random\n");
		eth_hw_addr_अक्रमom(dev);
	पूर्ण

	/* Link new device पूर्णांकo r6040_root_dev */
	lp->pdev = pdev;
	lp->dev = dev;

	/* Init RDC निजी data */
	lp->mcr0 = MCR0_XMTEN | MCR0_RCVEN;

	/* The RDC-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &r6040_netdev_ops;
	dev->ethtool_ops = &netdev_ethtool_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	netअगर_napi_add(dev, &lp->napi, r6040_poll, 64);

	lp->mii_bus = mdiobus_alloc();
	अगर (!lp->mii_bus) अणु
		dev_err(&pdev->dev, "mdiobus_alloc() failed\n");
		err = -ENOMEM;
		जाओ err_out_unmap;
	पूर्ण

	lp->mii_bus->priv = dev;
	lp->mii_bus->पढ़ो = r6040_mdiobus_पढ़ो;
	lp->mii_bus->ग_लिखो = r6040_mdiobus_ग_लिखो;
	lp->mii_bus->name = "r6040_eth_mii";
	snम_लिखो(lp->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		dev_name(&pdev->dev), card_idx);

	err = mdiobus_रेजिस्टर(lp->mii_bus);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register MII bus\n");
		जाओ err_out_mdio;
	पूर्ण

	err = r6040_mii_probe(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to probe MII bus\n");
		जाओ err_out_mdio_unरेजिस्टर;
	पूर्ण

	/* Register net device. After this dev->name assign */
	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register net device\n");
		जाओ err_out_mdio_unरेजिस्टर;
	पूर्ण
	वापस 0;

err_out_mdio_unरेजिस्टर:
	mdiobus_unरेजिस्टर(lp->mii_bus);
err_out_mdio:
	mdiobus_मुक्त(lp->mii_bus);
err_out_unmap:
	netअगर_napi_del(&lp->napi);
	pci_iounmap(pdev, ioaddr);
err_out_मुक्त_res:
	pci_release_regions(pdev);
err_out_मुक्त_dev:
	मुक्त_netdev(dev);
err_out_disable_dev:
	pci_disable_device(pdev);
err_out:
	वापस err;
पूर्ण

अटल व्योम r6040_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा r6040_निजी *lp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	mdiobus_unरेजिस्टर(lp->mii_bus);
	mdiobus_मुक्त(lp->mii_bus);
	netअगर_napi_del(&lp->napi);
	pci_iounmap(pdev, lp->base);
	pci_release_regions(pdev);
	मुक्त_netdev(dev);
	pci_disable_device(pdev);
पूर्ण


अटल स्थिर काष्ठा pci_device_id r6040_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_RDC, 0x6040) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, r6040_pci_tbl);

अटल काष्ठा pci_driver r6040_driver = अणु
	.name		= DRV_NAME,
	.id_table	= r6040_pci_tbl,
	.probe		= r6040_init_one,
	.हटाओ		= r6040_हटाओ_one,
पूर्ण;

module_pci_driver(r6040_driver);
