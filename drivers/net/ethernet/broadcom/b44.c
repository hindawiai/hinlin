<शैली गुरु>
/* b44.c: Broadcom 44xx/47xx Fast Ethernet device driver.
 *
 * Copyright (C) 2002 David S. Miller (davem@redhat.com)
 * Copyright (C) 2004 Pekka Pietikainen (pp@ee.oulu.fi)
 * Copyright (C) 2004 Florian Schirmer (jolt@tuxbox.org)
 * Copyright (C) 2006 Felix Fietkau (nbd@खोलोwrt.org)
 * Copyright (C) 2006 Broadcom Corporation.
 * Copyright (C) 2007 Michael Buesch <m@bues.ch>
 * Copyright (C) 2013 Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Distribute under GPL.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/ssb/ssb.h>
#समावेश <linux/slab.h>
#समावेश <linux/phy.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>


#समावेश "b44.h"

#घोषणा DRV_MODULE_NAME		"b44"
#घोषणा DRV_DESCRIPTION		"Broadcom 44xx/47xx 10/100 PCI ethernet driver"

#घोषणा B44_DEF_MSG_ENABLE	  \
	(NETIF_MSG_DRV		| \
	 NETIF_MSG_PROBE	| \
	 NETIF_MSG_LINK		| \
	 NETIF_MSG_TIMER	| \
	 NETIF_MSG_IFDOWN	| \
	 NETIF_MSG_IFUP		| \
	 NETIF_MSG_RX_ERR	| \
	 NETIF_MSG_TX_ERR)

/* length of समय beक्रमe we decide the hardware is borked,
 * and dev->tx_समयout() should be called to fix the problem
 */
#घोषणा B44_TX_TIMEOUT			(5 * HZ)

/* hardware minimum and maximum क्रम a single frame's data payload */
#घोषणा B44_MIN_MTU			ETH_ZLEN
#घोषणा B44_MAX_MTU			ETH_DATA_LEN

#घोषणा B44_RX_RING_SIZE		512
#घोषणा B44_DEF_RX_RING_PENDING		200
#घोषणा B44_RX_RING_BYTES	(माप(काष्ठा dma_desc) * \
				 B44_RX_RING_SIZE)
#घोषणा B44_TX_RING_SIZE		512
#घोषणा B44_DEF_TX_RING_PENDING		(B44_TX_RING_SIZE - 1)
#घोषणा B44_TX_RING_BYTES	(माप(काष्ठा dma_desc) * \
				 B44_TX_RING_SIZE)

#घोषणा TX_RING_GAP(BP)	\
	(B44_TX_RING_SIZE - (BP)->tx_pending)
#घोषणा TX_BUFFS_AVAIL(BP)						\
	(((BP)->tx_cons <= (BP)->tx_prod) ?				\
	  (BP)->tx_cons + (BP)->tx_pending - (BP)->tx_prod :		\
	  (BP)->tx_cons - (BP)->tx_prod - TX_RING_GAP(BP))
#घोषणा NEXT_TX(N)		(((N) + 1) & (B44_TX_RING_SIZE - 1))

#घोषणा RX_PKT_OFFSET		(RX_HEADER_LEN + 2)
#घोषणा RX_PKT_BUF_SZ		(1536 + RX_PKT_OFFSET)

/* minimum number of मुक्त TX descriptors required to wake up TX process */
#घोषणा B44_TX_WAKEUP_THRESH		(B44_TX_RING_SIZE / 4)

/* b44 पूर्णांकernal pattern match filter info */
#घोषणा B44_PATTERN_BASE	0x400
#घोषणा B44_PATTERN_SIZE	0x80
#घोषणा B44_PMASK_BASE		0x600
#घोषणा B44_PMASK_SIZE		0x10
#घोषणा B44_MAX_PATTERNS	16
#घोषणा B44_ETHIPV6UDP_HLEN	62
#घोषणा B44_ETHIPV4UDP_HLEN	42

MODULE_AUTHOR("Felix Fietkau, Florian Schirmer, Pekka Pietikainen, David S. Miller");
MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_LICENSE("GPL");

अटल पूर्णांक b44_debug = -1;	/* -1 == use B44_DEF_MSG_ENABLE as value */
module_param(b44_debug, पूर्णांक, 0);
MODULE_PARM_DESC(b44_debug, "B44 bitmapped debugging message enable value");


#अगर_घोषित CONFIG_B44_PCI
अटल स्थिर काष्ठा pci_device_id b44_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_BCM4401) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_BCM4401B0) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_BCM4401B1) पूर्ण,
	अणु 0 पूर्ण /* terminate list with empty entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, b44_pci_tbl);

अटल काष्ठा pci_driver b44_pci_driver = अणु
	.name		= DRV_MODULE_NAME,
	.id_table	= b44_pci_tbl,
पूर्ण;
#पूर्ण_अगर /* CONFIG_B44_PCI */

अटल स्थिर काष्ठा ssb_device_id b44_ssb_tbl[] = अणु
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_ETHERNET, SSB_ANY_REV),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ssb, b44_ssb_tbl);

अटल व्योम b44_halt(काष्ठा b44 *);
अटल व्योम b44_init_rings(काष्ठा b44 *);

#घोषणा B44_FULL_RESET		1
#घोषणा B44_FULL_RESET_SKIP_PHY	2
#घोषणा B44_PARTIAL_RESET	3
#घोषणा B44_CHIP_RESET_FULL	4
#घोषणा B44_CHIP_RESET_PARTIAL	5

अटल व्योम b44_init_hw(काष्ठा b44 *, पूर्णांक);

अटल पूर्णांक dma_desc_sync_size;
अटल पूर्णांक instance;

अटल स्थिर अक्षर b44_gstrings[][ETH_GSTRING_LEN] = अणु
#घोषणा _B44(x...)	# x,
B44_STAT_REG_DECLARE
#अघोषित _B44
पूर्ण;

अटल अंतरभूत व्योम b44_sync_dma_desc_क्रम_device(काष्ठा ssb_device *sdev,
						dma_addr_t dma_base,
						अचिन्हित दीर्घ offset,
						क्रमागत dma_data_direction dir)
अणु
	dma_sync_single_क्रम_device(sdev->dma_dev, dma_base + offset,
				   dma_desc_sync_size, dir);
पूर्ण

अटल अंतरभूत व्योम b44_sync_dma_desc_क्रम_cpu(काष्ठा ssb_device *sdev,
					     dma_addr_t dma_base,
					     अचिन्हित दीर्घ offset,
					     क्रमागत dma_data_direction dir)
अणु
	dma_sync_single_क्रम_cpu(sdev->dma_dev, dma_base + offset,
				dma_desc_sync_size, dir);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ br32(स्थिर काष्ठा b44 *bp, अचिन्हित दीर्घ reg)
अणु
	वापस ssb_पढ़ो32(bp->sdev, reg);
पूर्ण

अटल अंतरभूत व्योम bw32(स्थिर काष्ठा b44 *bp,
			अचिन्हित दीर्घ reg, अचिन्हित दीर्घ val)
अणु
	ssb_ग_लिखो32(bp->sdev, reg, val);
पूर्ण

अटल पूर्णांक b44_रुको_bit(काष्ठा b44 *bp, अचिन्हित दीर्घ reg,
			u32 bit, अचिन्हित दीर्घ समयout, स्थिर पूर्णांक clear)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < समयout; i++) अणु
		u32 val = br32(bp, reg);

		अगर (clear && !(val & bit))
			अवरोध;
		अगर (!clear && (val & bit))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (i == समयout) अणु
		अगर (net_ratelimit())
			netdev_err(bp->dev, "BUG!  Timeout waiting for bit %08x of register %lx to %s\n",
				   bit, reg, clear ? "clear" : "set");

		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __b44_cam_पढ़ो(काष्ठा b44 *bp, अचिन्हित अक्षर *data, पूर्णांक index)
अणु
	u32 val;

	bw32(bp, B44_CAM_CTRL, (CAM_CTRL_READ |
			    (index << CAM_CTRL_INDEX_SHIFT)));

	b44_रुको_bit(bp, B44_CAM_CTRL, CAM_CTRL_BUSY, 100, 1);

	val = br32(bp, B44_CAM_DATA_LO);

	data[2] = (val >> 24) & 0xFF;
	data[3] = (val >> 16) & 0xFF;
	data[4] = (val >> 8) & 0xFF;
	data[5] = (val >> 0) & 0xFF;

	val = br32(bp, B44_CAM_DATA_HI);

	data[0] = (val >> 8) & 0xFF;
	data[1] = (val >> 0) & 0xFF;
पूर्ण

अटल अंतरभूत व्योम __b44_cam_ग_लिखो(काष्ठा b44 *bp, अचिन्हित अक्षर *data, पूर्णांक index)
अणु
	u32 val;

	val  = ((u32) data[2]) << 24;
	val |= ((u32) data[3]) << 16;
	val |= ((u32) data[4]) <<  8;
	val |= ((u32) data[5]) <<  0;
	bw32(bp, B44_CAM_DATA_LO, val);
	val = (CAM_DATA_HI_VALID |
	       (((u32) data[0]) << 8) |
	       (((u32) data[1]) << 0));
	bw32(bp, B44_CAM_DATA_HI, val);
	bw32(bp, B44_CAM_CTRL, (CAM_CTRL_WRITE |
			    (index << CAM_CTRL_INDEX_SHIFT)));
	b44_रुको_bit(bp, B44_CAM_CTRL, CAM_CTRL_BUSY, 100, 1);
पूर्ण

अटल अंतरभूत व्योम __b44_disable_पूर्णांकs(काष्ठा b44 *bp)
अणु
	bw32(bp, B44_IMASK, 0);
पूर्ण

अटल व्योम b44_disable_पूर्णांकs(काष्ठा b44 *bp)
अणु
	__b44_disable_पूर्णांकs(bp);

	/* Flush posted ग_लिखोs. */
	br32(bp, B44_IMASK);
पूर्ण

अटल व्योम b44_enable_पूर्णांकs(काष्ठा b44 *bp)
अणु
	bw32(bp, B44_IMASK, bp->imask);
पूर्ण

अटल पूर्णांक __b44_पढ़ोphy(काष्ठा b44 *bp, पूर्णांक phy_addr, पूर्णांक reg, u32 *val)
अणु
	पूर्णांक err;

	bw32(bp, B44_EMAC_ISTAT, EMAC_INT_MII);
	bw32(bp, B44_MDIO_DATA, (MDIO_DATA_SB_START |
			     (MDIO_OP_READ << MDIO_DATA_OP_SHIFT) |
			     (phy_addr << MDIO_DATA_PMD_SHIFT) |
			     (reg << MDIO_DATA_RA_SHIFT) |
			     (MDIO_TA_VALID << MDIO_DATA_TA_SHIFT)));
	err = b44_रुको_bit(bp, B44_EMAC_ISTAT, EMAC_INT_MII, 100, 0);
	*val = br32(bp, B44_MDIO_DATA) & MDIO_DATA_DATA;

	वापस err;
पूर्ण

अटल पूर्णांक __b44_ग_लिखोphy(काष्ठा b44 *bp, पूर्णांक phy_addr, पूर्णांक reg, u32 val)
अणु
	bw32(bp, B44_EMAC_ISTAT, EMAC_INT_MII);
	bw32(bp, B44_MDIO_DATA, (MDIO_DATA_SB_START |
			     (MDIO_OP_WRITE << MDIO_DATA_OP_SHIFT) |
			     (phy_addr << MDIO_DATA_PMD_SHIFT) |
			     (reg << MDIO_DATA_RA_SHIFT) |
			     (MDIO_TA_VALID << MDIO_DATA_TA_SHIFT) |
			     (val & MDIO_DATA_DATA)));
	वापस b44_रुको_bit(bp, B44_EMAC_ISTAT, EMAC_INT_MII, 100, 0);
पूर्ण

अटल अंतरभूत पूर्णांक b44_पढ़ोphy(काष्ठा b44 *bp, पूर्णांक reg, u32 *val)
अणु
	अगर (bp->flags & B44_FLAG_EXTERNAL_PHY)
		वापस 0;

	वापस __b44_पढ़ोphy(bp, bp->phy_addr, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक b44_ग_लिखोphy(काष्ठा b44 *bp, पूर्णांक reg, u32 val)
अणु
	अगर (bp->flags & B44_FLAG_EXTERNAL_PHY)
		वापस 0;

	वापस __b44_ग_लिखोphy(bp, bp->phy_addr, reg, val);
पूर्ण

/* miilib पूर्णांकerface */
अटल पूर्णांक b44_mdio_पढ़ो_mii(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location)
अणु
	u32 val;
	काष्ठा b44 *bp = netdev_priv(dev);
	पूर्णांक rc = __b44_पढ़ोphy(bp, phy_id, location, &val);
	अगर (rc)
		वापस 0xffffffff;
	वापस val;
पूर्ण

अटल व्योम b44_mdio_ग_लिखो_mii(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location,
			       पूर्णांक val)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	__b44_ग_लिखोphy(bp, phy_id, location, val);
पूर्ण

अटल पूर्णांक b44_mdio_पढ़ो_phylib(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक location)
अणु
	u32 val;
	काष्ठा b44 *bp = bus->priv;
	पूर्णांक rc = __b44_पढ़ोphy(bp, phy_id, location, &val);
	अगर (rc)
		वापस 0xffffffff;
	वापस val;
पूर्ण

अटल पूर्णांक b44_mdio_ग_लिखो_phylib(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक location,
				 u16 val)
अणु
	काष्ठा b44 *bp = bus->priv;
	वापस __b44_ग_लिखोphy(bp, phy_id, location, val);
पूर्ण

अटल पूर्णांक b44_phy_reset(काष्ठा b44 *bp)
अणु
	u32 val;
	पूर्णांक err;

	अगर (bp->flags & B44_FLAG_EXTERNAL_PHY)
		वापस 0;
	err = b44_ग_लिखोphy(bp, MII_BMCR, BMCR_RESET);
	अगर (err)
		वापस err;
	udelay(100);
	err = b44_पढ़ोphy(bp, MII_BMCR, &val);
	अगर (!err) अणु
		अगर (val & BMCR_RESET) अणु
			netdev_err(bp->dev, "PHY Reset would not complete\n");
			err = -ENODEV;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम __b44_set_flow_ctrl(काष्ठा b44 *bp, u32 छोड़ो_flags)
अणु
	u32 val;

	bp->flags &= ~(B44_FLAG_TX_PAUSE | B44_FLAG_RX_PAUSE);
	bp->flags |= छोड़ो_flags;

	val = br32(bp, B44_RXCONFIG);
	अगर (छोड़ो_flags & B44_FLAG_RX_PAUSE)
		val |= RXCONFIG_FLOW;
	अन्यथा
		val &= ~RXCONFIG_FLOW;
	bw32(bp, B44_RXCONFIG, val);

	val = br32(bp, B44_MAC_FLOW);
	अगर (छोड़ो_flags & B44_FLAG_TX_PAUSE)
		val |= (MAC_FLOW_PAUSE_ENAB |
			(0xc0 & MAC_FLOW_RX_HI_WATER));
	अन्यथा
		val &= ~MAC_FLOW_PAUSE_ENAB;
	bw32(bp, B44_MAC_FLOW, val);
पूर्ण

अटल व्योम b44_set_flow_ctrl(काष्ठा b44 *bp, u32 local, u32 remote)
अणु
	u32 छोड़ो_enab = 0;

	/* The driver supports only rx छोड़ो by शेष because
	   the b44 mac tx छोड़ो mechanism generates excessive
	   छोड़ो frames.
	   Use ethtool to turn on b44 tx छोड़ो अगर necessary.
	 */
	अगर ((local & ADVERTISE_PAUSE_CAP) &&
	    (local & ADVERTISE_PAUSE_ASYM))अणु
		अगर ((remote & LPA_PAUSE_ASYM) &&
		    !(remote & LPA_PAUSE_CAP))
			छोड़ो_enab |= B44_FLAG_RX_PAUSE;
	पूर्ण

	__b44_set_flow_ctrl(bp, छोड़ो_enab);
पूर्ण

#अगर_घोषित CONFIG_BCM47XX
#समावेश <linux/bcm47xx_nvram.h>
अटल व्योम b44_wap54g10_workaround(काष्ठा b44 *bp)
अणु
	अक्षर buf[20];
	u32 val;
	पूर्णांक err;

	/*
	 * workaround क्रम bad hardware design in Linksys WAP54G v1.0
	 * see https://dev.खोलोwrt.org/ticket/146
	 * check and reset bit "isolate"
	 */
	अगर (bcm47xx_nvram_दो_पर्या("boardnum", buf, माप(buf)) < 0)
		वापस;
	अगर (simple_म_से_अदीर्घ(buf, शून्य, 0) == 2) अणु
		err = __b44_पढ़ोphy(bp, 0, MII_BMCR, &val);
		अगर (err)
			जाओ error;
		अगर (!(val & BMCR_ISOLATE))
			वापस;
		val &= ~BMCR_ISOLATE;
		err = __b44_ग_लिखोphy(bp, 0, MII_BMCR, val);
		अगर (err)
			जाओ error;
	पूर्ण
	वापस;
error:
	pr_warn("PHY: cannot reset MII transceiver isolate bit\n");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम b44_wap54g10_workaround(काष्ठा b44 *bp)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक b44_setup_phy(काष्ठा b44 *bp)
अणु
	u32 val;
	पूर्णांक err;

	b44_wap54g10_workaround(bp);

	अगर (bp->flags & B44_FLAG_EXTERNAL_PHY)
		वापस 0;
	अगर ((err = b44_पढ़ोphy(bp, B44_MII_ALEDCTRL, &val)) != 0)
		जाओ out;
	अगर ((err = b44_ग_लिखोphy(bp, B44_MII_ALEDCTRL,
				val & MII_ALEDCTRL_ALLMSK)) != 0)
		जाओ out;
	अगर ((err = b44_पढ़ोphy(bp, B44_MII_TLEDCTRL, &val)) != 0)
		जाओ out;
	अगर ((err = b44_ग_लिखोphy(bp, B44_MII_TLEDCTRL,
				val | MII_TLEDCTRL_ENABLE)) != 0)
		जाओ out;

	अगर (!(bp->flags & B44_FLAG_FORCE_LINK)) अणु
		u32 adv = ADVERTISE_CSMA;

		अगर (bp->flags & B44_FLAG_ADV_10HALF)
			adv |= ADVERTISE_10HALF;
		अगर (bp->flags & B44_FLAG_ADV_10FULL)
			adv |= ADVERTISE_10FULL;
		अगर (bp->flags & B44_FLAG_ADV_100HALF)
			adv |= ADVERTISE_100HALF;
		अगर (bp->flags & B44_FLAG_ADV_100FULL)
			adv |= ADVERTISE_100FULL;

		अगर (bp->flags & B44_FLAG_PAUSE_AUTO)
			adv |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;

		अगर ((err = b44_ग_लिखोphy(bp, MII_ADVERTISE, adv)) != 0)
			जाओ out;
		अगर ((err = b44_ग_लिखोphy(bp, MII_BMCR, (BMCR_ANENABLE |
						       BMCR_ANRESTART))) != 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		u32 bmcr;

		अगर ((err = b44_पढ़ोphy(bp, MII_BMCR, &bmcr)) != 0)
			जाओ out;
		bmcr &= ~(BMCR_FULLDPLX | BMCR_ANENABLE | BMCR_SPEED100);
		अगर (bp->flags & B44_FLAG_100_BASE_T)
			bmcr |= BMCR_SPEED100;
		अगर (bp->flags & B44_FLAG_FULL_DUPLEX)
			bmcr |= BMCR_FULLDPLX;
		अगर ((err = b44_ग_लिखोphy(bp, MII_BMCR, bmcr)) != 0)
			जाओ out;

		/* Since we will not be negotiating there is no safe way
		 * to determine अगर the link partner supports flow control
		 * or not.  So just disable it completely in this हाल.
		 */
		b44_set_flow_ctrl(bp, 0, 0);
	पूर्ण

out:
	वापस err;
पूर्ण

अटल व्योम b44_stats_update(काष्ठा b44 *bp)
अणु
	अचिन्हित दीर्घ reg;
	u64 *val;

	val = &bp->hw_stats.tx_good_octets;
	u64_stats_update_begin(&bp->hw_stats.syncp);

	क्रम (reg = B44_TX_GOOD_O; reg <= B44_TX_PAUSE; reg += 4UL) अणु
		*val++ += br32(bp, reg);
	पूर्ण

	क्रम (reg = B44_RX_GOOD_O; reg <= B44_RX_NPAUSE; reg += 4UL) अणु
		*val++ += br32(bp, reg);
	पूर्ण

	u64_stats_update_end(&bp->hw_stats.syncp);
पूर्ण

अटल व्योम b44_link_report(काष्ठा b44 *bp)
अणु
	अगर (!netअगर_carrier_ok(bp->dev)) अणु
		netdev_info(bp->dev, "Link is down\n");
	पूर्ण अन्यथा अणु
		netdev_info(bp->dev, "Link is up at %d Mbps, %s duplex\n",
			    (bp->flags & B44_FLAG_100_BASE_T) ? 100 : 10,
			    (bp->flags & B44_FLAG_FULL_DUPLEX) ? "full" : "half");

		netdev_info(bp->dev, "Flow control is %s for TX and %s for RX\n",
			    (bp->flags & B44_FLAG_TX_PAUSE) ? "on" : "off",
			    (bp->flags & B44_FLAG_RX_PAUSE) ? "on" : "off");
	पूर्ण
पूर्ण

अटल व्योम b44_check_phy(काष्ठा b44 *bp)
अणु
	u32 bmsr, aux;

	अगर (bp->flags & B44_FLAG_EXTERNAL_PHY) अणु
		bp->flags |= B44_FLAG_100_BASE_T;
		अगर (!netअगर_carrier_ok(bp->dev)) अणु
			u32 val = br32(bp, B44_TX_CTRL);
			अगर (bp->flags & B44_FLAG_FULL_DUPLEX)
				val |= TX_CTRL_DUPLEX;
			अन्यथा
				val &= ~TX_CTRL_DUPLEX;
			bw32(bp, B44_TX_CTRL, val);
			netअगर_carrier_on(bp->dev);
			b44_link_report(bp);
		पूर्ण
		वापस;
	पूर्ण

	अगर (!b44_पढ़ोphy(bp, MII_BMSR, &bmsr) &&
	    !b44_पढ़ोphy(bp, B44_MII_AUXCTRL, &aux) &&
	    (bmsr != 0xffff)) अणु
		अगर (aux & MII_AUXCTRL_SPEED)
			bp->flags |= B44_FLAG_100_BASE_T;
		अन्यथा
			bp->flags &= ~B44_FLAG_100_BASE_T;
		अगर (aux & MII_AUXCTRL_DUPLEX)
			bp->flags |= B44_FLAG_FULL_DUPLEX;
		अन्यथा
			bp->flags &= ~B44_FLAG_FULL_DUPLEX;

		अगर (!netअगर_carrier_ok(bp->dev) &&
		    (bmsr & BMSR_LSTATUS)) अणु
			u32 val = br32(bp, B44_TX_CTRL);
			u32 local_adv, remote_adv;

			अगर (bp->flags & B44_FLAG_FULL_DUPLEX)
				val |= TX_CTRL_DUPLEX;
			अन्यथा
				val &= ~TX_CTRL_DUPLEX;
			bw32(bp, B44_TX_CTRL, val);

			अगर (!(bp->flags & B44_FLAG_FORCE_LINK) &&
			    !b44_पढ़ोphy(bp, MII_ADVERTISE, &local_adv) &&
			    !b44_पढ़ोphy(bp, MII_LPA, &remote_adv))
				b44_set_flow_ctrl(bp, local_adv, remote_adv);

			/* Link now up */
			netअगर_carrier_on(bp->dev);
			b44_link_report(bp);
		पूर्ण अन्यथा अगर (netअगर_carrier_ok(bp->dev) && !(bmsr & BMSR_LSTATUS)) अणु
			/* Link now करोwn */
			netअगर_carrier_off(bp->dev);
			b44_link_report(bp);
		पूर्ण

		अगर (bmsr & BMSR_RFAULT)
			netdev_warn(bp->dev, "Remote fault detected in PHY\n");
		अगर (bmsr & BMSR_JCD)
			netdev_warn(bp->dev, "Jabber detected in PHY\n");
	पूर्ण
पूर्ण

अटल व्योम b44_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा b44 *bp = from_समयr(bp, t, समयr);

	spin_lock_irq(&bp->lock);

	b44_check_phy(bp);

	b44_stats_update(bp);

	spin_unlock_irq(&bp->lock);

	mod_समयr(&bp->समयr, round_jअगरfies(jअगरfies + HZ));
पूर्ण

अटल व्योम b44_tx(काष्ठा b44 *bp)
अणु
	u32 cur, cons;
	अचिन्हित bytes_compl = 0, pkts_compl = 0;

	cur  = br32(bp, B44_DMATX_STAT) & DMATX_STAT_CDMASK;
	cur /= माप(काष्ठा dma_desc);

	/* XXX needs updating when NETIF_F_SG is supported */
	क्रम (cons = bp->tx_cons; cons != cur; cons = NEXT_TX(cons)) अणु
		काष्ठा ring_info *rp = &bp->tx_buffers[cons];
		काष्ठा sk_buff *skb = rp->skb;

		BUG_ON(skb == शून्य);

		dma_unmap_single(bp->sdev->dma_dev,
				 rp->mapping,
				 skb->len,
				 DMA_TO_DEVICE);
		rp->skb = शून्य;

		bytes_compl += skb->len;
		pkts_compl++;

		dev_consume_skb_irq(skb);
	पूर्ण

	netdev_completed_queue(bp->dev, pkts_compl, bytes_compl);
	bp->tx_cons = cons;
	अगर (netअगर_queue_stopped(bp->dev) &&
	    TX_BUFFS_AVAIL(bp) > B44_TX_WAKEUP_THRESH)
		netअगर_wake_queue(bp->dev);

	bw32(bp, B44_GPTIMER, 0);
पूर्ण

/* Works like this.  This chip ग_लिखोs a 'काष्ठा rx_header" 30 bytes
 * beक्रमe the DMA address you give it.  So we allocate 30 more bytes
 * क्रम the RX buffer, DMA map all of it, skb_reserve the 30 bytes, then
 * poपूर्णांक the chip at 30 bytes past where the rx_header will go.
 */
अटल पूर्णांक b44_alloc_rx_skb(काष्ठा b44 *bp, पूर्णांक src_idx, u32 dest_idx_unmasked)
अणु
	काष्ठा dma_desc *dp;
	काष्ठा ring_info *src_map, *map;
	काष्ठा rx_header *rh;
	काष्ठा sk_buff *skb;
	dma_addr_t mapping;
	पूर्णांक dest_idx;
	u32 ctrl;

	src_map = शून्य;
	अगर (src_idx >= 0)
		src_map = &bp->rx_buffers[src_idx];
	dest_idx = dest_idx_unmasked & (B44_RX_RING_SIZE - 1);
	map = &bp->rx_buffers[dest_idx];
	skb = netdev_alloc_skb(bp->dev, RX_PKT_BUF_SZ);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	mapping = dma_map_single(bp->sdev->dma_dev, skb->data,
				 RX_PKT_BUF_SZ,
				 DMA_FROM_DEVICE);

	/* Hardware bug work-around, the chip is unable to करो PCI DMA
	   to/from anything above 1GB :-( */
	अगर (dma_mapping_error(bp->sdev->dma_dev, mapping) ||
		mapping + RX_PKT_BUF_SZ > DMA_BIT_MASK(30)) अणु
		/* Sigh... */
		अगर (!dma_mapping_error(bp->sdev->dma_dev, mapping))
			dma_unmap_single(bp->sdev->dma_dev, mapping,
					     RX_PKT_BUF_SZ, DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
		skb = alloc_skb(RX_PKT_BUF_SZ, GFP_ATOMIC | GFP_DMA);
		अगर (skb == शून्य)
			वापस -ENOMEM;
		mapping = dma_map_single(bp->sdev->dma_dev, skb->data,
					 RX_PKT_BUF_SZ,
					 DMA_FROM_DEVICE);
		अगर (dma_mapping_error(bp->sdev->dma_dev, mapping) ||
		    mapping + RX_PKT_BUF_SZ > DMA_BIT_MASK(30)) अणु
			अगर (!dma_mapping_error(bp->sdev->dma_dev, mapping))
				dma_unmap_single(bp->sdev->dma_dev, mapping, RX_PKT_BUF_SZ,DMA_FROM_DEVICE);
			dev_kमुक्त_skb_any(skb);
			वापस -ENOMEM;
		पूर्ण
		bp->क्रमce_copyअवरोध = 1;
	पूर्ण

	rh = (काष्ठा rx_header *) skb->data;

	rh->len = 0;
	rh->flags = 0;

	map->skb = skb;
	map->mapping = mapping;

	अगर (src_map != शून्य)
		src_map->skb = शून्य;

	ctrl = (DESC_CTRL_LEN & RX_PKT_BUF_SZ);
	अगर (dest_idx == (B44_RX_RING_SIZE - 1))
		ctrl |= DESC_CTRL_EOT;

	dp = &bp->rx_ring[dest_idx];
	dp->ctrl = cpu_to_le32(ctrl);
	dp->addr = cpu_to_le32((u32) mapping + bp->dma_offset);

	अगर (bp->flags & B44_FLAG_RX_RING_HACK)
		b44_sync_dma_desc_क्रम_device(bp->sdev, bp->rx_ring_dma,
			                    dest_idx * माप(*dp),
			                    DMA_BIसूचीECTIONAL);

	वापस RX_PKT_BUF_SZ;
पूर्ण

अटल व्योम b44_recycle_rx(काष्ठा b44 *bp, पूर्णांक src_idx, u32 dest_idx_unmasked)
अणु
	काष्ठा dma_desc *src_desc, *dest_desc;
	काष्ठा ring_info *src_map, *dest_map;
	काष्ठा rx_header *rh;
	पूर्णांक dest_idx;
	__le32 ctrl;

	dest_idx = dest_idx_unmasked & (B44_RX_RING_SIZE - 1);
	dest_desc = &bp->rx_ring[dest_idx];
	dest_map = &bp->rx_buffers[dest_idx];
	src_desc = &bp->rx_ring[src_idx];
	src_map = &bp->rx_buffers[src_idx];

	dest_map->skb = src_map->skb;
	rh = (काष्ठा rx_header *) src_map->skb->data;
	rh->len = 0;
	rh->flags = 0;
	dest_map->mapping = src_map->mapping;

	अगर (bp->flags & B44_FLAG_RX_RING_HACK)
		b44_sync_dma_desc_क्रम_cpu(bp->sdev, bp->rx_ring_dma,
			                 src_idx * माप(*src_desc),
			                 DMA_BIसूचीECTIONAL);

	ctrl = src_desc->ctrl;
	अगर (dest_idx == (B44_RX_RING_SIZE - 1))
		ctrl |= cpu_to_le32(DESC_CTRL_EOT);
	अन्यथा
		ctrl &= cpu_to_le32(~DESC_CTRL_EOT);

	dest_desc->ctrl = ctrl;
	dest_desc->addr = src_desc->addr;

	src_map->skb = शून्य;

	अगर (bp->flags & B44_FLAG_RX_RING_HACK)
		b44_sync_dma_desc_क्रम_device(bp->sdev, bp->rx_ring_dma,
					     dest_idx * माप(*dest_desc),
					     DMA_BIसूचीECTIONAL);

	dma_sync_single_क्रम_device(bp->sdev->dma_dev, dest_map->mapping,
				   RX_PKT_BUF_SZ,
				   DMA_FROM_DEVICE);
पूर्ण

अटल पूर्णांक b44_rx(काष्ठा b44 *bp, पूर्णांक budget)
अणु
	पूर्णांक received;
	u32 cons, prod;

	received = 0;
	prod  = br32(bp, B44_DMARX_STAT) & DMARX_STAT_CDMASK;
	prod /= माप(काष्ठा dma_desc);
	cons = bp->rx_cons;

	जबतक (cons != prod && budget > 0) अणु
		काष्ठा ring_info *rp = &bp->rx_buffers[cons];
		काष्ठा sk_buff *skb = rp->skb;
		dma_addr_t map = rp->mapping;
		काष्ठा rx_header *rh;
		u16 len;

		dma_sync_single_क्रम_cpu(bp->sdev->dma_dev, map,
					RX_PKT_BUF_SZ,
					DMA_FROM_DEVICE);
		rh = (काष्ठा rx_header *) skb->data;
		len = le16_to_cpu(rh->len);
		अगर ((len > (RX_PKT_BUF_SZ - RX_PKT_OFFSET)) ||
		    (rh->flags & cpu_to_le16(RX_FLAG_ERRORS))) अणु
		drop_it:
			b44_recycle_rx(bp, cons, bp->rx_prod);
		drop_it_no_recycle:
			bp->dev->stats.rx_dropped++;
			जाओ next_pkt;
		पूर्ण

		अगर (len == 0) अणु
			पूर्णांक i = 0;

			करो अणु
				udelay(2);
				barrier();
				len = le16_to_cpu(rh->len);
			पूर्ण जबतक (len == 0 && i++ < 5);
			अगर (len == 0)
				जाओ drop_it;
		पूर्ण

		/* Omit CRC. */
		len -= 4;

		अगर (!bp->क्रमce_copyअवरोध && len > RX_COPY_THRESHOLD) अणु
			पूर्णांक skb_size;
			skb_size = b44_alloc_rx_skb(bp, cons, bp->rx_prod);
			अगर (skb_size < 0)
				जाओ drop_it;
			dma_unmap_single(bp->sdev->dma_dev, map,
					 skb_size, DMA_FROM_DEVICE);
			/* Leave out rx_header */
			skb_put(skb, len + RX_PKT_OFFSET);
			skb_pull(skb, RX_PKT_OFFSET);
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *copy_skb;

			b44_recycle_rx(bp, cons, bp->rx_prod);
			copy_skb = napi_alloc_skb(&bp->napi, len);
			अगर (copy_skb == शून्य)
				जाओ drop_it_no_recycle;

			skb_put(copy_skb, len);
			/* DMA sync करोne above, copy just the actual packet */
			skb_copy_from_linear_data_offset(skb, RX_PKT_OFFSET,
							 copy_skb->data, len);
			skb = copy_skb;
		पूर्ण
		skb_checksum_none_निश्चित(skb);
		skb->protocol = eth_type_trans(skb, bp->dev);
		netअगर_receive_skb(skb);
		received++;
		budget--;
	next_pkt:
		bp->rx_prod = (bp->rx_prod + 1) &
			(B44_RX_RING_SIZE - 1);
		cons = (cons + 1) & (B44_RX_RING_SIZE - 1);
	पूर्ण

	bp->rx_cons = cons;
	bw32(bp, B44_DMARX_PTR, cons * माप(काष्ठा dma_desc));

	वापस received;
पूर्ण

अटल पूर्णांक b44_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा b44 *bp = container_of(napi, काष्ठा b44, napi);
	पूर्णांक work_करोne;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bp->lock, flags);

	अगर (bp->istat & (ISTAT_TX | ISTAT_TO)) अणु
		/* spin_lock(&bp->tx_lock); */
		b44_tx(bp);
		/* spin_unlock(&bp->tx_lock); */
	पूर्ण
	अगर (bp->istat & ISTAT_RFO) अणु	/* fast recovery, in ~20msec */
		bp->istat &= ~ISTAT_RFO;
		b44_disable_पूर्णांकs(bp);
		ssb_device_enable(bp->sdev, 0); /* resets ISTAT_RFO */
		b44_init_rings(bp);
		b44_init_hw(bp, B44_FULL_RESET_SKIP_PHY);
		netअगर_wake_queue(bp->dev);
	पूर्ण

	spin_unlock_irqrestore(&bp->lock, flags);

	work_करोne = 0;
	अगर (bp->istat & ISTAT_RX)
		work_करोne += b44_rx(bp, budget);

	अगर (bp->istat & ISTAT_ERRORS) अणु
		spin_lock_irqsave(&bp->lock, flags);
		b44_halt(bp);
		b44_init_rings(bp);
		b44_init_hw(bp, B44_FULL_RESET_SKIP_PHY);
		netअगर_wake_queue(bp->dev);
		spin_unlock_irqrestore(&bp->lock, flags);
		work_करोne = 0;
	पूर्ण

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		b44_enable_पूर्णांकs(bp);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल irqवापस_t b44_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा b44 *bp = netdev_priv(dev);
	u32 istat, imask;
	पूर्णांक handled = 0;

	spin_lock(&bp->lock);

	istat = br32(bp, B44_ISTAT);
	imask = br32(bp, B44_IMASK);

	/* The पूर्णांकerrupt mask रेजिस्टर controls which पूर्णांकerrupt bits
	 * will actually उठाओ an पूर्णांकerrupt to the CPU when set by hw/firmware,
	 * but करोesn't mask off the bits.
	 */
	istat &= imask;
	अगर (istat) अणु
		handled = 1;

		अगर (unlikely(!netअगर_running(dev))) अणु
			netdev_info(dev, "late interrupt\n");
			जाओ irq_ack;
		पूर्ण

		अगर (napi_schedule_prep(&bp->napi)) अणु
			/* NOTE: These ग_लिखोs are posted by the पढ़ोback of
			 *       the ISTAT रेजिस्टर below.
			 */
			bp->istat = istat;
			__b44_disable_पूर्णांकs(bp);
			__napi_schedule(&bp->napi);
		पूर्ण

irq_ack:
		bw32(bp, B44_ISTAT, istat);
		br32(bp, B44_ISTAT);
	पूर्ण
	spin_unlock(&bp->lock);
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम b44_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);

	netdev_err(dev, "transmit timed out, resetting\n");

	spin_lock_irq(&bp->lock);

	b44_halt(bp);
	b44_init_rings(bp);
	b44_init_hw(bp, B44_FULL_RESET);

	spin_unlock_irq(&bp->lock);

	b44_enable_पूर्णांकs(bp);

	netअगर_wake_queue(dev);
पूर्ण

अटल netdev_tx_t b44_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	पूर्णांक rc = NETDEV_TX_OK;
	dma_addr_t mapping;
	u32 len, entry, ctrl;
	अचिन्हित दीर्घ flags;

	len = skb->len;
	spin_lock_irqsave(&bp->lock, flags);

	/* This is a hard error, log it. */
	अगर (unlikely(TX_BUFFS_AVAIL(bp) < 1)) अणु
		netअगर_stop_queue(dev);
		netdev_err(dev, "BUG! Tx Ring full when queue awake!\n");
		जाओ err_out;
	पूर्ण

	mapping = dma_map_single(bp->sdev->dma_dev, skb->data, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(bp->sdev->dma_dev, mapping) || mapping + len > DMA_BIT_MASK(30)) अणु
		काष्ठा sk_buff *bounce_skb;

		/* Chip can't handle DMA to/from >1GB, use bounce buffer */
		अगर (!dma_mapping_error(bp->sdev->dma_dev, mapping))
			dma_unmap_single(bp->sdev->dma_dev, mapping, len,
					     DMA_TO_DEVICE);

		bounce_skb = alloc_skb(len, GFP_ATOMIC | GFP_DMA);
		अगर (!bounce_skb)
			जाओ err_out;

		mapping = dma_map_single(bp->sdev->dma_dev, bounce_skb->data,
					 len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(bp->sdev->dma_dev, mapping) || mapping + len > DMA_BIT_MASK(30)) अणु
			अगर (!dma_mapping_error(bp->sdev->dma_dev, mapping))
				dma_unmap_single(bp->sdev->dma_dev, mapping,
						     len, DMA_TO_DEVICE);
			dev_kमुक्त_skb_any(bounce_skb);
			जाओ err_out;
		पूर्ण

		skb_copy_from_linear_data(skb, skb_put(bounce_skb, len), len);
		dev_consume_skb_any(skb);
		skb = bounce_skb;
	पूर्ण

	entry = bp->tx_prod;
	bp->tx_buffers[entry].skb = skb;
	bp->tx_buffers[entry].mapping = mapping;

	ctrl  = (len & DESC_CTRL_LEN);
	ctrl |= DESC_CTRL_IOC | DESC_CTRL_SOF | DESC_CTRL_खातापूर्ण;
	अगर (entry == (B44_TX_RING_SIZE - 1))
		ctrl |= DESC_CTRL_EOT;

	bp->tx_ring[entry].ctrl = cpu_to_le32(ctrl);
	bp->tx_ring[entry].addr = cpu_to_le32((u32) mapping+bp->dma_offset);

	अगर (bp->flags & B44_FLAG_TX_RING_HACK)
		b44_sync_dma_desc_क्रम_device(bp->sdev, bp->tx_ring_dma,
			                    entry * माप(bp->tx_ring[0]),
			                    DMA_TO_DEVICE);

	entry = NEXT_TX(entry);

	bp->tx_prod = entry;

	wmb();

	bw32(bp, B44_DMATX_PTR, entry * माप(काष्ठा dma_desc));
	अगर (bp->flags & B44_FLAG_BUGGY_TXPTR)
		bw32(bp, B44_DMATX_PTR, entry * माप(काष्ठा dma_desc));
	अगर (bp->flags & B44_FLAG_REORDER_BUG)
		br32(bp, B44_DMATX_PTR);

	netdev_sent_queue(dev, skb->len);

	अगर (TX_BUFFS_AVAIL(bp) < 1)
		netअगर_stop_queue(dev);

out_unlock:
	spin_unlock_irqrestore(&bp->lock, flags);

	वापस rc;

err_out:
	rc = NETDEV_TX_BUSY;
	जाओ out_unlock;
पूर्ण

अटल पूर्णांक b44_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);

	अगर (!netअगर_running(dev)) अणु
		/* We'll just catch it later when the
		 * device is up'd.
		 */
		dev->mtu = new_mtu;
		वापस 0;
	पूर्ण

	spin_lock_irq(&bp->lock);
	b44_halt(bp);
	dev->mtu = new_mtu;
	b44_init_rings(bp);
	b44_init_hw(bp, B44_FULL_RESET);
	spin_unlock_irq(&bp->lock);

	b44_enable_पूर्णांकs(bp);

	वापस 0;
पूर्ण

/* Free up pending packets in all rx/tx rings.
 *
 * The chip has been shut करोwn and the driver detached from
 * the networking, so no पूर्णांकerrupts or new tx packets will
 * end up in the driver.  bp->lock is not held and we are not
 * in an पूर्णांकerrupt context and thus may sleep.
 */
अटल व्योम b44_मुक्त_rings(काष्ठा b44 *bp)
अणु
	काष्ठा ring_info *rp;
	पूर्णांक i;

	क्रम (i = 0; i < B44_RX_RING_SIZE; i++) अणु
		rp = &bp->rx_buffers[i];

		अगर (rp->skb == शून्य)
			जारी;
		dma_unmap_single(bp->sdev->dma_dev, rp->mapping, RX_PKT_BUF_SZ,
				 DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(rp->skb);
		rp->skb = शून्य;
	पूर्ण

	/* XXX needs changes once NETIF_F_SG is set... */
	क्रम (i = 0; i < B44_TX_RING_SIZE; i++) अणु
		rp = &bp->tx_buffers[i];

		अगर (rp->skb == शून्य)
			जारी;
		dma_unmap_single(bp->sdev->dma_dev, rp->mapping, rp->skb->len,
				 DMA_TO_DEVICE);
		dev_kमुक्त_skb_any(rp->skb);
		rp->skb = शून्य;
	पूर्ण
पूर्ण

/* Initialize tx/rx rings क्रम packet processing.
 *
 * The chip has been shut करोwn and the driver detached from
 * the networking, so no पूर्णांकerrupts or new tx packets will
 * end up in the driver.
 */
अटल व्योम b44_init_rings(काष्ठा b44 *bp)
अणु
	पूर्णांक i;

	b44_मुक्त_rings(bp);

	स_रखो(bp->rx_ring, 0, B44_RX_RING_BYTES);
	स_रखो(bp->tx_ring, 0, B44_TX_RING_BYTES);

	अगर (bp->flags & B44_FLAG_RX_RING_HACK)
		dma_sync_single_क्रम_device(bp->sdev->dma_dev, bp->rx_ring_dma,
					   DMA_TABLE_BYTES, DMA_BIसूचीECTIONAL);

	अगर (bp->flags & B44_FLAG_TX_RING_HACK)
		dma_sync_single_क्रम_device(bp->sdev->dma_dev, bp->tx_ring_dma,
					   DMA_TABLE_BYTES, DMA_TO_DEVICE);

	क्रम (i = 0; i < bp->rx_pending; i++) अणु
		अगर (b44_alloc_rx_skb(bp, -1, i) < 0)
			अवरोध;
	पूर्ण
पूर्ण

/*
 * Must not be invoked with पूर्णांकerrupt sources disabled and
 * the hardware shutकरोwn करोwn.
 */
अटल व्योम b44_मुक्त_consistent(काष्ठा b44 *bp)
अणु
	kमुक्त(bp->rx_buffers);
	bp->rx_buffers = शून्य;
	kमुक्त(bp->tx_buffers);
	bp->tx_buffers = शून्य;
	अगर (bp->rx_ring) अणु
		अगर (bp->flags & B44_FLAG_RX_RING_HACK) अणु
			dma_unmap_single(bp->sdev->dma_dev, bp->rx_ring_dma,
					 DMA_TABLE_BYTES, DMA_BIसूचीECTIONAL);
			kमुक्त(bp->rx_ring);
		पूर्ण अन्यथा
			dma_मुक्त_coherent(bp->sdev->dma_dev, DMA_TABLE_BYTES,
					  bp->rx_ring, bp->rx_ring_dma);
		bp->rx_ring = शून्य;
		bp->flags &= ~B44_FLAG_RX_RING_HACK;
	पूर्ण
	अगर (bp->tx_ring) अणु
		अगर (bp->flags & B44_FLAG_TX_RING_HACK) अणु
			dma_unmap_single(bp->sdev->dma_dev, bp->tx_ring_dma,
					 DMA_TABLE_BYTES, DMA_TO_DEVICE);
			kमुक्त(bp->tx_ring);
		पूर्ण अन्यथा
			dma_मुक्त_coherent(bp->sdev->dma_dev, DMA_TABLE_BYTES,
					  bp->tx_ring, bp->tx_ring_dma);
		bp->tx_ring = शून्य;
		bp->flags &= ~B44_FLAG_TX_RING_HACK;
	पूर्ण
पूर्ण

/*
 * Must not be invoked with पूर्णांकerrupt sources disabled and
 * the hardware shutकरोwn करोwn.  Can sleep.
 */
अटल पूर्णांक b44_alloc_consistent(काष्ठा b44 *bp, gfp_t gfp)
अणु
	पूर्णांक size;

	size  = B44_RX_RING_SIZE * माप(काष्ठा ring_info);
	bp->rx_buffers = kzalloc(size, gfp);
	अगर (!bp->rx_buffers)
		जाओ out_err;

	size = B44_TX_RING_SIZE * माप(काष्ठा ring_info);
	bp->tx_buffers = kzalloc(size, gfp);
	अगर (!bp->tx_buffers)
		जाओ out_err;

	size = DMA_TABLE_BYTES;
	bp->rx_ring = dma_alloc_coherent(bp->sdev->dma_dev, size,
					 &bp->rx_ring_dma, gfp);
	अगर (!bp->rx_ring) अणु
		/* Allocation may have failed due to pci_alloc_consistent
		   insisting on use of GFP_DMA, which is more restrictive
		   than necessary...  */
		काष्ठा dma_desc *rx_ring;
		dma_addr_t rx_ring_dma;

		rx_ring = kzalloc(size, gfp);
		अगर (!rx_ring)
			जाओ out_err;

		rx_ring_dma = dma_map_single(bp->sdev->dma_dev, rx_ring,
					     DMA_TABLE_BYTES,
					     DMA_BIसूचीECTIONAL);

		अगर (dma_mapping_error(bp->sdev->dma_dev, rx_ring_dma) ||
			rx_ring_dma + size > DMA_BIT_MASK(30)) अणु
			kमुक्त(rx_ring);
			जाओ out_err;
		पूर्ण

		bp->rx_ring = rx_ring;
		bp->rx_ring_dma = rx_ring_dma;
		bp->flags |= B44_FLAG_RX_RING_HACK;
	पूर्ण

	bp->tx_ring = dma_alloc_coherent(bp->sdev->dma_dev, size,
					 &bp->tx_ring_dma, gfp);
	अगर (!bp->tx_ring) अणु
		/* Allocation may have failed due to ssb_dma_alloc_consistent
		   insisting on use of GFP_DMA, which is more restrictive
		   than necessary...  */
		काष्ठा dma_desc *tx_ring;
		dma_addr_t tx_ring_dma;

		tx_ring = kzalloc(size, gfp);
		अगर (!tx_ring)
			जाओ out_err;

		tx_ring_dma = dma_map_single(bp->sdev->dma_dev, tx_ring,
					     DMA_TABLE_BYTES,
					     DMA_TO_DEVICE);

		अगर (dma_mapping_error(bp->sdev->dma_dev, tx_ring_dma) ||
			tx_ring_dma + size > DMA_BIT_MASK(30)) अणु
			kमुक्त(tx_ring);
			जाओ out_err;
		पूर्ण

		bp->tx_ring = tx_ring;
		bp->tx_ring_dma = tx_ring_dma;
		bp->flags |= B44_FLAG_TX_RING_HACK;
	पूर्ण

	वापस 0;

out_err:
	b44_मुक्त_consistent(bp);
	वापस -ENOMEM;
पूर्ण

/* bp->lock is held. */
अटल व्योम b44_clear_stats(काष्ठा b44 *bp)
अणु
	अचिन्हित दीर्घ reg;

	bw32(bp, B44_MIB_CTRL, MIB_CTRL_CLR_ON_READ);
	क्रम (reg = B44_TX_GOOD_O; reg <= B44_TX_PAUSE; reg += 4UL)
		br32(bp, reg);
	क्रम (reg = B44_RX_GOOD_O; reg <= B44_RX_NPAUSE; reg += 4UL)
		br32(bp, reg);
पूर्ण

/* bp->lock is held. */
अटल व्योम b44_chip_reset(काष्ठा b44 *bp, पूर्णांक reset_kind)
अणु
	काष्ठा ssb_device *sdev = bp->sdev;
	bool was_enabled;

	was_enabled = ssb_device_is_enabled(bp->sdev);

	ssb_device_enable(bp->sdev, 0);
	ssb_pcicore_dev_irqvecs_enable(&sdev->bus->pcicore, sdev);

	अगर (was_enabled) अणु
		bw32(bp, B44_RCV_LAZY, 0);
		bw32(bp, B44_ENET_CTRL, ENET_CTRL_DISABLE);
		b44_रुको_bit(bp, B44_ENET_CTRL, ENET_CTRL_DISABLE, 200, 1);
		bw32(bp, B44_DMATX_CTRL, 0);
		bp->tx_prod = bp->tx_cons = 0;
		अगर (br32(bp, B44_DMARX_STAT) & DMARX_STAT_EMASK) अणु
			b44_रुको_bit(bp, B44_DMARX_STAT, DMARX_STAT_SIDLE,
				     100, 0);
		पूर्ण
		bw32(bp, B44_DMARX_CTRL, 0);
		bp->rx_prod = bp->rx_cons = 0;
	पूर्ण

	b44_clear_stats(bp);

	/*
	 * Don't enable PHY अगर we are करोing a partial reset
	 * we are probably going to घातer करोwn
	 */
	अगर (reset_kind == B44_CHIP_RESET_PARTIAL)
		वापस;

	चयन (sdev->bus->bustype) अणु
	हाल SSB_BUSTYPE_SSB:
		bw32(bp, B44_MDIO_CTRL, (MDIO_CTRL_PREAMBLE |
		     (DIV_ROUND_CLOSEST(ssb_घड़ीspeed(sdev->bus),
					B44_MDC_RATIO)
		     & MDIO_CTRL_MAXF_MASK)));
		अवरोध;
	हाल SSB_BUSTYPE_PCI:
		bw32(bp, B44_MDIO_CTRL, (MDIO_CTRL_PREAMBLE |
		     (0x0d & MDIO_CTRL_MAXF_MASK)));
		अवरोध;
	हाल SSB_BUSTYPE_PCMCIA:
	हाल SSB_BUSTYPE_SDIO:
		WARN_ON(1); /* A device with this bus करोes not exist. */
		अवरोध;
	पूर्ण

	br32(bp, B44_MDIO_CTRL);

	अगर (!(br32(bp, B44_DEVCTRL) & DEVCTRL_IPP)) अणु
		bw32(bp, B44_ENET_CTRL, ENET_CTRL_EPSEL);
		br32(bp, B44_ENET_CTRL);
		bp->flags |= B44_FLAG_EXTERNAL_PHY;
	पूर्ण अन्यथा अणु
		u32 val = br32(bp, B44_DEVCTRL);

		अगर (val & DEVCTRL_EPR) अणु
			bw32(bp, B44_DEVCTRL, (val & ~DEVCTRL_EPR));
			br32(bp, B44_DEVCTRL);
			udelay(100);
		पूर्ण
		bp->flags &= ~B44_FLAG_EXTERNAL_PHY;
	पूर्ण
पूर्ण

/* bp->lock is held. */
अटल व्योम b44_halt(काष्ठा b44 *bp)
अणु
	b44_disable_पूर्णांकs(bp);
	/* reset PHY */
	b44_phy_reset(bp);
	/* घातer करोwn PHY */
	netdev_info(bp->dev, "powering down PHY\n");
	bw32(bp, B44_MAC_CTRL, MAC_CTRL_PHY_PDOWN);
	/* now reset the chip, but without enabling the MAC&PHY
	 * part of it. This has to be करोne _after_ we shut करोwn the PHY */
	अगर (bp->flags & B44_FLAG_EXTERNAL_PHY)
		b44_chip_reset(bp, B44_CHIP_RESET_FULL);
	अन्यथा
		b44_chip_reset(bp, B44_CHIP_RESET_PARTIAL);
पूर्ण

/* bp->lock is held. */
अटल व्योम __b44_set_mac_addr(काष्ठा b44 *bp)
अणु
	bw32(bp, B44_CAM_CTRL, 0);
	अगर (!(bp->dev->flags & IFF_PROMISC)) अणु
		u32 val;

		__b44_cam_ग_लिखो(bp, bp->dev->dev_addr, 0);
		val = br32(bp, B44_CAM_CTRL);
		bw32(bp, B44_CAM_CTRL, val | CAM_CTRL_ENABLE);
	पूर्ण
पूर्ण

अटल पूर्णांक b44_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	काष्ठा sockaddr *addr = p;
	u32 val;

	अगर (netअगर_running(dev))
		वापस -EBUSY;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EINVAL;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	spin_lock_irq(&bp->lock);

	val = br32(bp, B44_RXCONFIG);
	अगर (!(val & RXCONFIG_CAM_ABSENT))
		__b44_set_mac_addr(bp);

	spin_unlock_irq(&bp->lock);

	वापस 0;
पूर्ण

/* Called at device खोलो समय to get the chip पढ़ोy क्रम
 * packet processing.  Invoked with bp->lock held.
 */
अटल व्योम __b44_set_rx_mode(काष्ठा net_device *);
अटल व्योम b44_init_hw(काष्ठा b44 *bp, पूर्णांक reset_kind)
अणु
	u32 val;

	b44_chip_reset(bp, B44_CHIP_RESET_FULL);
	अगर (reset_kind == B44_FULL_RESET) अणु
		b44_phy_reset(bp);
		b44_setup_phy(bp);
	पूर्ण

	/* Enable CRC32, set proper LED modes and घातer on PHY */
	bw32(bp, B44_MAC_CTRL, MAC_CTRL_CRC32_ENAB | MAC_CTRL_PHY_LEDCTRL);
	bw32(bp, B44_RCV_LAZY, (1 << RCV_LAZY_FC_SHIFT));

	/* This sets the MAC address too.  */
	__b44_set_rx_mode(bp->dev);

	/* MTU + eth header + possible VLAN tag + काष्ठा rx_header */
	bw32(bp, B44_RXMAXLEN, bp->dev->mtu + ETH_HLEN + 8 + RX_HEADER_LEN);
	bw32(bp, B44_TXMAXLEN, bp->dev->mtu + ETH_HLEN + 8 + RX_HEADER_LEN);

	bw32(bp, B44_TX_WMARK, 56); /* XXX magic */
	अगर (reset_kind == B44_PARTIAL_RESET) अणु
		bw32(bp, B44_DMARX_CTRL, (DMARX_CTRL_ENABLE |
				      (RX_PKT_OFFSET << DMARX_CTRL_ROSHIFT)));
	पूर्ण अन्यथा अणु
		bw32(bp, B44_DMATX_CTRL, DMATX_CTRL_ENABLE);
		bw32(bp, B44_DMATX_ADDR, bp->tx_ring_dma + bp->dma_offset);
		bw32(bp, B44_DMARX_CTRL, (DMARX_CTRL_ENABLE |
				      (RX_PKT_OFFSET << DMARX_CTRL_ROSHIFT)));
		bw32(bp, B44_DMARX_ADDR, bp->rx_ring_dma + bp->dma_offset);

		bw32(bp, B44_DMARX_PTR, bp->rx_pending);
		bp->rx_prod = bp->rx_pending;

		bw32(bp, B44_MIB_CTRL, MIB_CTRL_CLR_ON_READ);
	पूर्ण

	val = br32(bp, B44_ENET_CTRL);
	bw32(bp, B44_ENET_CTRL, (val | ENET_CTRL_ENABLE));

	netdev_reset_queue(bp->dev);
पूर्ण

अटल पूर्णांक b44_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	पूर्णांक err;

	err = b44_alloc_consistent(bp, GFP_KERNEL);
	अगर (err)
		जाओ out;

	napi_enable(&bp->napi);

	b44_init_rings(bp);
	b44_init_hw(bp, B44_FULL_RESET);

	b44_check_phy(bp);

	err = request_irq(dev->irq, b44_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev);
	अगर (unlikely(err < 0)) अणु
		napi_disable(&bp->napi);
		b44_chip_reset(bp, B44_CHIP_RESET_PARTIAL);
		b44_मुक्त_rings(bp);
		b44_मुक्त_consistent(bp);
		जाओ out;
	पूर्ण

	समयr_setup(&bp->समयr, b44_समयr, 0);
	bp->समयr.expires = jअगरfies + HZ;
	add_समयr(&bp->समयr);

	b44_enable_पूर्णांकs(bp);

	अगर (bp->flags & B44_FLAG_EXTERNAL_PHY)
		phy_start(dev->phydev);

	netअगर_start_queue(dev);
out:
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Polling receive - used by netconsole and other diagnostic tools
 * to allow network i/o with पूर्णांकerrupts disabled.
 */
अटल व्योम b44_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	b44_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

अटल व्योम bwfilter_table(काष्ठा b44 *bp, u8 *pp, u32 bytes, u32 table_offset)
अणु
	u32 i;
	u32 *pattern = (u32 *) pp;

	क्रम (i = 0; i < bytes; i += माप(u32)) अणु
		bw32(bp, B44_FILT_ADDR, table_offset + i);
		bw32(bp, B44_FILT_DATA, pattern[i / माप(u32)]);
	पूर्ण
पूर्ण

अटल पूर्णांक b44_magic_pattern(u8 *macaddr, u8 *ppattern, u8 *pmask, पूर्णांक offset)
अणु
	पूर्णांक magicsync = 6;
	पूर्णांक k, j, len = offset;
	पूर्णांक ethaddr_bytes = ETH_ALEN;

	स_रखो(ppattern + offset, 0xff, magicsync);
	क्रम (j = 0; j < magicsync; j++) अणु
		pmask[len >> 3] |= BIT(len & 7);
		len++;
	पूर्ण

	क्रम (j = 0; j < B44_MAX_PATTERNS; j++) अणु
		अगर ((B44_PATTERN_SIZE - len) >= ETH_ALEN)
			ethaddr_bytes = ETH_ALEN;
		अन्यथा
			ethaddr_bytes = B44_PATTERN_SIZE - len;
		अगर (ethaddr_bytes <=0)
			अवरोध;
		क्रम (k = 0; k< ethaddr_bytes; k++) अणु
			ppattern[offset + magicsync +
				(j * ETH_ALEN) + k] = macaddr[k];
			pmask[len >> 3] |= BIT(len & 7);
			len++;
		पूर्ण
	पूर्ण
	वापस len - 1;
पूर्ण

/* Setup magic packet patterns in the b44 WOL
 * pattern matching filter.
 */
अटल व्योम b44_setup_pseuकरो_magicp(काष्ठा b44 *bp)
अणु

	u32 val;
	पूर्णांक plen0, plen1, plen2;
	u8 *pwol_pattern;
	u8 pwol_mask[B44_PMASK_SIZE];

	pwol_pattern = kzalloc(B44_PATTERN_SIZE, GFP_KERNEL);
	अगर (!pwol_pattern)
		वापस;

	/* Ipv4 magic packet pattern - pattern 0.*/
	स_रखो(pwol_mask, 0, B44_PMASK_SIZE);
	plen0 = b44_magic_pattern(bp->dev->dev_addr, pwol_pattern, pwol_mask,
				  B44_ETHIPV4UDP_HLEN);

   	bwfilter_table(bp, pwol_pattern, B44_PATTERN_SIZE, B44_PATTERN_BASE);
   	bwfilter_table(bp, pwol_mask, B44_PMASK_SIZE, B44_PMASK_BASE);

	/* Raw ethernet II magic packet pattern - pattern 1 */
	स_रखो(pwol_pattern, 0, B44_PATTERN_SIZE);
	स_रखो(pwol_mask, 0, B44_PMASK_SIZE);
	plen1 = b44_magic_pattern(bp->dev->dev_addr, pwol_pattern, pwol_mask,
				  ETH_HLEN);

   	bwfilter_table(bp, pwol_pattern, B44_PATTERN_SIZE,
		       B44_PATTERN_BASE + B44_PATTERN_SIZE);
  	bwfilter_table(bp, pwol_mask, B44_PMASK_SIZE,
		       B44_PMASK_BASE + B44_PMASK_SIZE);

	/* Ipv6 magic packet pattern - pattern 2 */
	स_रखो(pwol_pattern, 0, B44_PATTERN_SIZE);
	स_रखो(pwol_mask, 0, B44_PMASK_SIZE);
	plen2 = b44_magic_pattern(bp->dev->dev_addr, pwol_pattern, pwol_mask,
				  B44_ETHIPV6UDP_HLEN);

   	bwfilter_table(bp, pwol_pattern, B44_PATTERN_SIZE,
		       B44_PATTERN_BASE + B44_PATTERN_SIZE + B44_PATTERN_SIZE);
  	bwfilter_table(bp, pwol_mask, B44_PMASK_SIZE,
		       B44_PMASK_BASE + B44_PMASK_SIZE + B44_PMASK_SIZE);

	kमुक्त(pwol_pattern);

	/* set these pattern's lengths: one less than each real length */
	val = plen0 | (plen1 << 8) | (plen2 << 16) | WKUP_LEN_ENABLE_THREE;
	bw32(bp, B44_WKUP_LEN, val);

	/* enable wakeup pattern matching */
	val = br32(bp, B44_DEVCTRL);
	bw32(bp, B44_DEVCTRL, val | DEVCTRL_PFE);

पूर्ण

#अगर_घोषित CONFIG_B44_PCI
अटल व्योम b44_setup_wol_pci(काष्ठा b44 *bp)
अणु
	u16 val;

	अगर (bp->sdev->bus->bustype != SSB_BUSTYPE_SSB) अणु
		bw32(bp, SSB_TMSLOW, br32(bp, SSB_TMSLOW) | SSB_TMSLOW_PE);
		pci_पढ़ो_config_word(bp->sdev->bus->host_pci, SSB_PMCSR, &val);
		pci_ग_लिखो_config_word(bp->sdev->bus->host_pci, SSB_PMCSR, val | SSB_PE);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम b44_setup_wol_pci(काष्ठा b44 *bp) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_B44_PCI */

अटल व्योम b44_setup_wol(काष्ठा b44 *bp)
अणु
	u32 val;

	bw32(bp, B44_RXCONFIG, RXCONFIG_ALLMULTI);

	अगर (bp->flags & B44_FLAG_B0_ANDLATER) अणु

		bw32(bp, B44_WKUP_LEN, WKUP_LEN_DISABLE);

		val = bp->dev->dev_addr[2] << 24 |
			bp->dev->dev_addr[3] << 16 |
			bp->dev->dev_addr[4] << 8 |
			bp->dev->dev_addr[5];
		bw32(bp, B44_ADDR_LO, val);

		val = bp->dev->dev_addr[0] << 8 |
			bp->dev->dev_addr[1];
		bw32(bp, B44_ADDR_HI, val);

		val = br32(bp, B44_DEVCTRL);
		bw32(bp, B44_DEVCTRL, val | DEVCTRL_MPM | DEVCTRL_PFE);

 	पूर्ण अन्यथा अणु
 		b44_setup_pseuकरो_magicp(bp);
 	पूर्ण
	b44_setup_wol_pci(bp);
पूर्ण

अटल पूर्णांक b44_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);

	netअगर_stop_queue(dev);

	अगर (bp->flags & B44_FLAG_EXTERNAL_PHY)
		phy_stop(dev->phydev);

	napi_disable(&bp->napi);

	del_समयr_sync(&bp->समयr);

	spin_lock_irq(&bp->lock);

	b44_halt(bp);
	b44_मुक्त_rings(bp);
	netअगर_carrier_off(dev);

	spin_unlock_irq(&bp->lock);

	मुक्त_irq(dev->irq, dev);

	अगर (bp->flags & B44_FLAG_WOL_ENABLE) अणु
		b44_init_hw(bp, B44_PARTIAL_RESET);
		b44_setup_wol(bp);
	पूर्ण

	b44_मुक्त_consistent(bp);

	वापस 0;
पूर्ण

अटल व्योम b44_get_stats64(काष्ठा net_device *dev,
			    काष्ठा rtnl_link_stats64 *nstat)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	काष्ठा b44_hw_stats *hwstat = &bp->hw_stats;
	अचिन्हित पूर्णांक start;

	करो अणु
		start = u64_stats_fetch_begin_irq(&hwstat->syncp);

		/* Convert HW stats पूर्णांकo rtnl_link_stats64 stats. */
		nstat->rx_packets = hwstat->rx_pkts;
		nstat->tx_packets = hwstat->tx_pkts;
		nstat->rx_bytes   = hwstat->rx_octets;
		nstat->tx_bytes   = hwstat->tx_octets;
		nstat->tx_errors  = (hwstat->tx_jabber_pkts +
				     hwstat->tx_oversize_pkts +
				     hwstat->tx_underruns +
				     hwstat->tx_excessive_cols +
				     hwstat->tx_late_cols);
		nstat->multicast  = hwstat->rx_multicast_pkts;
		nstat->collisions = hwstat->tx_total_cols;

		nstat->rx_length_errors = (hwstat->rx_oversize_pkts +
					   hwstat->rx_undersize);
		nstat->rx_over_errors   = hwstat->rx_missed_pkts;
		nstat->rx_frame_errors  = hwstat->rx_align_errs;
		nstat->rx_crc_errors    = hwstat->rx_crc_errs;
		nstat->rx_errors        = (hwstat->rx_jabber_pkts +
					   hwstat->rx_oversize_pkts +
					   hwstat->rx_missed_pkts +
					   hwstat->rx_crc_align_errs +
					   hwstat->rx_undersize +
					   hwstat->rx_crc_errs +
					   hwstat->rx_align_errs +
					   hwstat->rx_symbol_errs);

		nstat->tx_पातed_errors = hwstat->tx_underruns;
#अगर 0
		/* Carrier lost counter seems to be broken क्रम some devices */
		nstat->tx_carrier_errors = hwstat->tx_carrier_lost;
#पूर्ण_अगर
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&hwstat->syncp, start));

पूर्ण

अटल पूर्णांक __b44_load_mcast(काष्ठा b44 *bp, काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i, num_ents;

	num_ents = min_t(पूर्णांक, netdev_mc_count(dev), B44_MCAST_TABLE_SIZE);
	i = 0;
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		अगर (i == num_ents)
			अवरोध;
		__b44_cam_ग_लिखो(bp, ha->addr, i++ + 1);
	पूर्ण
	वापस i+1;
पूर्ण

अटल व्योम __b44_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	u32 val;

	val = br32(bp, B44_RXCONFIG);
	val &= ~(RXCONFIG_PROMISC | RXCONFIG_ALLMULTI);
	अगर ((dev->flags & IFF_PROMISC) || (val & RXCONFIG_CAM_ABSENT)) अणु
		val |= RXCONFIG_PROMISC;
		bw32(bp, B44_RXCONFIG, val);
	पूर्ण अन्यथा अणु
		अचिन्हित अक्षर zero[6] = अणु0, 0, 0, 0, 0, 0पूर्ण;
		पूर्णांक i = 1;

		__b44_set_mac_addr(bp);

		अगर ((dev->flags & IFF_ALLMULTI) ||
		    (netdev_mc_count(dev) > B44_MCAST_TABLE_SIZE))
			val |= RXCONFIG_ALLMULTI;
		अन्यथा
			i = __b44_load_mcast(bp, dev);

		क्रम (; i < 64; i++)
			__b44_cam_ग_लिखो(bp, zero, i);

		bw32(bp, B44_RXCONFIG, val);
        	val = br32(bp, B44_CAM_CTRL);
	        bw32(bp, B44_CAM_CTRL, val | CAM_CTRL_ENABLE);
	पूर्ण
पूर्ण

अटल व्योम b44_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);

	spin_lock_irq(&bp->lock);
	__b44_set_rx_mode(dev);
	spin_unlock_irq(&bp->lock);
पूर्ण

अटल u32 b44_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	वापस bp->msg_enable;
पूर्ण

अटल व्योम b44_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	bp->msg_enable = value;
पूर्ण

अटल व्योम b44_get_drvinfo (काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	काष्ठा ssb_bus *bus = bp->sdev->bus;

	strlcpy(info->driver, DRV_MODULE_NAME, माप(info->driver));
	चयन (bus->bustype) अणु
	हाल SSB_BUSTYPE_PCI:
		strlcpy(info->bus_info, pci_name(bus->host_pci), माप(info->bus_info));
		अवरोध;
	हाल SSB_BUSTYPE_SSB:
		strlcpy(info->bus_info, "SSB", माप(info->bus_info));
		अवरोध;
	हाल SSB_BUSTYPE_PCMCIA:
	हाल SSB_BUSTYPE_SDIO:
		WARN_ON(1); /* A device with this bus करोes not exist. */
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक b44_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	u32 bmcr;
	पूर्णांक r;

	spin_lock_irq(&bp->lock);
	b44_पढ़ोphy(bp, MII_BMCR, &bmcr);
	b44_पढ़ोphy(bp, MII_BMCR, &bmcr);
	r = -EINVAL;
	अगर (bmcr & BMCR_ANENABLE) अणु
		b44_ग_लिखोphy(bp, MII_BMCR,
			     bmcr | BMCR_ANRESTART);
		r = 0;
	पूर्ण
	spin_unlock_irq(&bp->lock);

	वापस r;
पूर्ण

अटल पूर्णांक b44_get_link_ksettings(काष्ठा net_device *dev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	u32 supported, advertising;

	अगर (bp->flags & B44_FLAG_EXTERNAL_PHY) अणु
		BUG_ON(!dev->phydev);
		phy_ethtool_ksettings_get(dev->phydev, cmd);

		वापस 0;
	पूर्ण

	supported = (SUPPORTED_Autoneg);
	supported |= (SUPPORTED_100baseT_Half |
		      SUPPORTED_100baseT_Full |
		      SUPPORTED_10baseT_Half |
		      SUPPORTED_10baseT_Full |
		      SUPPORTED_MII);

	advertising = 0;
	अगर (bp->flags & B44_FLAG_ADV_10HALF)
		advertising |= ADVERTISED_10baseT_Half;
	अगर (bp->flags & B44_FLAG_ADV_10FULL)
		advertising |= ADVERTISED_10baseT_Full;
	अगर (bp->flags & B44_FLAG_ADV_100HALF)
		advertising |= ADVERTISED_100baseT_Half;
	अगर (bp->flags & B44_FLAG_ADV_100FULL)
		advertising |= ADVERTISED_100baseT_Full;
	advertising |= ADVERTISED_Pause | ADVERTISED_Asym_Pause;
	cmd->base.speed = (bp->flags & B44_FLAG_100_BASE_T) ?
		SPEED_100 : SPEED_10;
	cmd->base.duplex = (bp->flags & B44_FLAG_FULL_DUPLEX) ?
		DUPLEX_FULL : DUPLEX_HALF;
	cmd->base.port = 0;
	cmd->base.phy_address = bp->phy_addr;
	cmd->base.स्वतःneg = (bp->flags & B44_FLAG_FORCE_LINK) ?
		AUTONEG_DISABLE : AUTONEG_ENABLE;
	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE)
		advertising |= ADVERTISED_Autoneg;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	अगर (!netअगर_running(dev))अणु
		cmd->base.speed = 0;
		cmd->base.duplex = 0xff;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक b44_set_link_ksettings(काष्ठा net_device *dev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	u32 speed;
	पूर्णांक ret;
	u32 advertising;

	अगर (bp->flags & B44_FLAG_EXTERNAL_PHY) अणु
		BUG_ON(!dev->phydev);
		spin_lock_irq(&bp->lock);
		अगर (netअगर_running(dev))
			b44_setup_phy(bp);

		ret = phy_ethtool_ksettings_set(dev->phydev, cmd);

		spin_unlock_irq(&bp->lock);

		वापस ret;
	पूर्ण

	speed = cmd->base.speed;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	/* We करो not support gigabit. */
	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (advertising &
		    (ADVERTISED_1000baseT_Half |
		     ADVERTISED_1000baseT_Full))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर ((speed != SPEED_100 &&
		    speed != SPEED_10) ||
		   (cmd->base.duplex != DUPLEX_HALF &&
		    cmd->base.duplex != DUPLEX_FULL)) अणु
			वापस -EINVAL;
	पूर्ण

	spin_lock_irq(&bp->lock);

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		bp->flags &= ~(B44_FLAG_FORCE_LINK |
			       B44_FLAG_100_BASE_T |
			       B44_FLAG_FULL_DUPLEX |
			       B44_FLAG_ADV_10HALF |
			       B44_FLAG_ADV_10FULL |
			       B44_FLAG_ADV_100HALF |
			       B44_FLAG_ADV_100FULL);
		अगर (advertising == 0) अणु
			bp->flags |= (B44_FLAG_ADV_10HALF |
				      B44_FLAG_ADV_10FULL |
				      B44_FLAG_ADV_100HALF |
				      B44_FLAG_ADV_100FULL);
		पूर्ण अन्यथा अणु
			अगर (advertising & ADVERTISED_10baseT_Half)
				bp->flags |= B44_FLAG_ADV_10HALF;
			अगर (advertising & ADVERTISED_10baseT_Full)
				bp->flags |= B44_FLAG_ADV_10FULL;
			अगर (advertising & ADVERTISED_100baseT_Half)
				bp->flags |= B44_FLAG_ADV_100HALF;
			अगर (advertising & ADVERTISED_100baseT_Full)
				bp->flags |= B44_FLAG_ADV_100FULL;
		पूर्ण
	पूर्ण अन्यथा अणु
		bp->flags |= B44_FLAG_FORCE_LINK;
		bp->flags &= ~(B44_FLAG_100_BASE_T | B44_FLAG_FULL_DUPLEX);
		अगर (speed == SPEED_100)
			bp->flags |= B44_FLAG_100_BASE_T;
		अगर (cmd->base.duplex == DUPLEX_FULL)
			bp->flags |= B44_FLAG_FULL_DUPLEX;
	पूर्ण

	अगर (netअगर_running(dev))
		b44_setup_phy(bp);

	spin_unlock_irq(&bp->lock);

	वापस 0;
पूर्ण

अटल व्योम b44_get_ringparam(काष्ठा net_device *dev,
			      काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);

	ering->rx_max_pending = B44_RX_RING_SIZE - 1;
	ering->rx_pending = bp->rx_pending;

	/* XXX ethtool lacks a tx_max_pending, oops... */
पूर्ण

अटल पूर्णांक b44_set_ringparam(काष्ठा net_device *dev,
			     काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);

	अगर ((ering->rx_pending > B44_RX_RING_SIZE - 1) ||
	    (ering->rx_mini_pending != 0) ||
	    (ering->rx_jumbo_pending != 0) ||
	    (ering->tx_pending > B44_TX_RING_SIZE - 1))
		वापस -EINVAL;

	spin_lock_irq(&bp->lock);

	bp->rx_pending = ering->rx_pending;
	bp->tx_pending = ering->tx_pending;

	b44_halt(bp);
	b44_init_rings(bp);
	b44_init_hw(bp, B44_FULL_RESET);
	netअगर_wake_queue(bp->dev);
	spin_unlock_irq(&bp->lock);

	b44_enable_पूर्णांकs(bp);

	वापस 0;
पूर्ण

अटल व्योम b44_get_छोड़ोparam(काष्ठा net_device *dev,
				काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);

	eछोड़ो->स्वतःneg =
		(bp->flags & B44_FLAG_PAUSE_AUTO) != 0;
	eछोड़ो->rx_छोड़ो =
		(bp->flags & B44_FLAG_RX_PAUSE) != 0;
	eछोड़ो->tx_छोड़ो =
		(bp->flags & B44_FLAG_TX_PAUSE) != 0;
पूर्ण

अटल पूर्णांक b44_set_छोड़ोparam(काष्ठा net_device *dev,
				काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);

	spin_lock_irq(&bp->lock);
	अगर (eछोड़ो->स्वतःneg)
		bp->flags |= B44_FLAG_PAUSE_AUTO;
	अन्यथा
		bp->flags &= ~B44_FLAG_PAUSE_AUTO;
	अगर (eछोड़ो->rx_छोड़ो)
		bp->flags |= B44_FLAG_RX_PAUSE;
	अन्यथा
		bp->flags &= ~B44_FLAG_RX_PAUSE;
	अगर (eछोड़ो->tx_छोड़ो)
		bp->flags |= B44_FLAG_TX_PAUSE;
	अन्यथा
		bp->flags &= ~B44_FLAG_TX_PAUSE;
	अगर (bp->flags & B44_FLAG_PAUSE_AUTO) अणु
		b44_halt(bp);
		b44_init_rings(bp);
		b44_init_hw(bp, B44_FULL_RESET);
	पूर्ण अन्यथा अणु
		__b44_set_flow_ctrl(bp, bp->flags);
	पूर्ण
	spin_unlock_irq(&bp->lock);

	b44_enable_पूर्णांकs(bp);

	वापस 0;
पूर्ण

अटल व्योम b44_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	चयन(stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(data, *b44_gstrings, माप(b44_gstrings));
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक b44_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(b44_gstrings);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम b44_get_ethtool_stats(काष्ठा net_device *dev,
				  काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	काष्ठा b44_hw_stats *hwstat = &bp->hw_stats;
	u64 *data_src, *data_dst;
	अचिन्हित पूर्णांक start;
	u32 i;

	spin_lock_irq(&bp->lock);
	b44_stats_update(bp);
	spin_unlock_irq(&bp->lock);

	करो अणु
		data_src = &hwstat->tx_good_octets;
		data_dst = data;
		start = u64_stats_fetch_begin_irq(&hwstat->syncp);

		क्रम (i = 0; i < ARRAY_SIZE(b44_gstrings); i++)
			*data_dst++ = *data_src++;

	पूर्ण जबतक (u64_stats_fetch_retry_irq(&hwstat->syncp, start));
पूर्ण

अटल व्योम b44_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);

	wol->supported = WAKE_MAGIC;
	अगर (bp->flags & B44_FLAG_WOL_ENABLE)
		wol->wolopts = WAKE_MAGIC;
	अन्यथा
		wol->wolopts = 0;
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
पूर्ण

अटल पूर्णांक b44_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);

	spin_lock_irq(&bp->lock);
	अगर (wol->wolopts & WAKE_MAGIC)
		bp->flags |= B44_FLAG_WOL_ENABLE;
	अन्यथा
		bp->flags &= ~B44_FLAG_WOL_ENABLE;
	spin_unlock_irq(&bp->lock);

	device_set_wakeup_enable(bp->sdev->dev, wol->wolopts & WAKE_MAGIC);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops b44_ethtool_ops = अणु
	.get_drvinfo		= b44_get_drvinfo,
	.nway_reset		= b44_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_wol		= b44_get_wol,
	.set_wol		= b44_set_wol,
	.get_ringparam		= b44_get_ringparam,
	.set_ringparam		= b44_set_ringparam,
	.get_छोड़ोparam		= b44_get_छोड़ोparam,
	.set_छोड़ोparam		= b44_set_छोड़ोparam,
	.get_msglevel		= b44_get_msglevel,
	.set_msglevel		= b44_set_msglevel,
	.get_strings		= b44_get_strings,
	.get_sset_count		= b44_get_sset_count,
	.get_ethtool_stats	= b44_get_ethtool_stats,
	.get_link_ksettings	= b44_get_link_ksettings,
	.set_link_ksettings	= b44_set_link_ksettings,
पूर्ण;

अटल पूर्णांक b44_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	पूर्णांक err = -EINVAL;

	अगर (!netअगर_running(dev))
		जाओ out;

	spin_lock_irq(&bp->lock);
	अगर (bp->flags & B44_FLAG_EXTERNAL_PHY) अणु
		BUG_ON(!dev->phydev);
		err = phy_mii_ioctl(dev->phydev, अगरr, cmd);
	पूर्ण अन्यथा अणु
		err = generic_mii_ioctl(&bp->mii_अगर, अगर_mii(अगरr), cmd, शून्य);
	पूर्ण
	spin_unlock_irq(&bp->lock);
out:
	वापस err;
पूर्ण

अटल पूर्णांक b44_get_invariants(काष्ठा b44 *bp)
अणु
	काष्ठा ssb_device *sdev = bp->sdev;
	पूर्णांक err = 0;
	u8 *addr;

	bp->dma_offset = ssb_dma_translation(sdev);

	अगर (sdev->bus->bustype == SSB_BUSTYPE_SSB &&
	    instance > 1) अणु
		addr = sdev->bus->sprom.et1mac;
		bp->phy_addr = sdev->bus->sprom.et1phyaddr;
	पूर्ण अन्यथा अणु
		addr = sdev->bus->sprom.et0mac;
		bp->phy_addr = sdev->bus->sprom.et0phyaddr;
	पूर्ण
	/* Some ROMs have buggy PHY addresses with the high
	 * bits set (sign extension?). Truncate them to a
	 * valid PHY address. */
	bp->phy_addr &= 0x1F;

	स_नकल(bp->dev->dev_addr, addr, ETH_ALEN);

	अगर (!is_valid_ether_addr(&bp->dev->dev_addr[0]))अणु
		pr_err("Invalid MAC address found in EEPROM\n");
		वापस -EINVAL;
	पूर्ण

	bp->imask = IMASK_DEF;

	/* XXX - really required?
	   bp->flags |= B44_FLAG_BUGGY_TXPTR;
	*/

	अगर (bp->sdev->id.revision >= 7)
		bp->flags |= B44_FLAG_B0_ANDLATER;

	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_device_ops b44_netdev_ops = अणु
	.nकरो_खोलो		= b44_खोलो,
	.nकरो_stop		= b44_बंद,
	.nकरो_start_xmit		= b44_start_xmit,
	.nकरो_get_stats64	= b44_get_stats64,
	.nकरो_set_rx_mode	= b44_set_rx_mode,
	.nकरो_set_mac_address	= b44_set_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= b44_ioctl,
	.nकरो_tx_समयout		= b44_tx_समयout,
	.nकरो_change_mtu		= b44_change_mtu,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= b44_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल व्योम b44_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा b44 *bp = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	bool status_changed = false;

	BUG_ON(!phydev);

	अगर (bp->old_link != phydev->link) अणु
		status_changed = true;
		bp->old_link = phydev->link;
	पूर्ण

	/* reflect duplex change */
	अगर (phydev->link) अणु
		अगर ((phydev->duplex == DUPLEX_HALF) &&
		    (bp->flags & B44_FLAG_FULL_DUPLEX)) अणु
			status_changed = true;
			bp->flags &= ~B44_FLAG_FULL_DUPLEX;
		पूर्ण अन्यथा अगर ((phydev->duplex == DUPLEX_FULL) &&
			   !(bp->flags & B44_FLAG_FULL_DUPLEX)) अणु
			status_changed = true;
			bp->flags |= B44_FLAG_FULL_DUPLEX;
		पूर्ण
	पूर्ण

	अगर (status_changed) अणु
		u32 val = br32(bp, B44_TX_CTRL);
		अगर (bp->flags & B44_FLAG_FULL_DUPLEX)
			val |= TX_CTRL_DUPLEX;
		अन्यथा
			val &= ~TX_CTRL_DUPLEX;
		bw32(bp, B44_TX_CTRL, val);
		phy_prपूर्णांक_status(phydev);
	पूर्ण
पूर्ण

अटल पूर्णांक b44_रेजिस्टर_phy_one(काष्ठा b44 *bp)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;
	काष्ठा mii_bus *mii_bus;
	काष्ठा ssb_device *sdev = bp->sdev;
	काष्ठा phy_device *phydev;
	अक्षर bus_id[MII_BUS_ID_SIZE + 3];
	काष्ठा ssb_sprom *sprom = &sdev->bus->sprom;
	पूर्णांक err;

	mii_bus = mdiobus_alloc();
	अगर (!mii_bus) अणु
		dev_err(sdev->dev, "mdiobus_alloc() failed\n");
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	mii_bus->priv = bp;
	mii_bus->पढ़ो = b44_mdio_पढ़ो_phylib;
	mii_bus->ग_लिखो = b44_mdio_ग_लिखो_phylib;
	mii_bus->name = "b44_eth_mii";
	mii_bus->parent = sdev->dev;
	mii_bus->phy_mask = ~(1 << bp->phy_addr);
	snम_लिखो(mii_bus->id, MII_BUS_ID_SIZE, "%x", instance);

	bp->mii_bus = mii_bus;

	err = mdiobus_रेजिस्टर(mii_bus);
	अगर (err) अणु
		dev_err(sdev->dev, "failed to register MII bus\n");
		जाओ err_out_mdiobus;
	पूर्ण

	अगर (!mdiobus_is_रेजिस्टरed_device(bp->mii_bus, bp->phy_addr) &&
	    (sprom->boardflags_lo & (B44_BOARDFLAG_ROBO | B44_BOARDFLAG_ADM))) अणु

		dev_info(sdev->dev,
			 "could not find PHY at %i, use fixed one\n",
			 bp->phy_addr);

		bp->phy_addr = 0;
		snम_लिखो(bus_id, माप(bus_id), PHY_ID_FMT, "fixed-0",
			 bp->phy_addr);
	पूर्ण अन्यथा अणु
		snम_लिखो(bus_id, माप(bus_id), PHY_ID_FMT, mii_bus->id,
			 bp->phy_addr);
	पूर्ण

	phydev = phy_connect(bp->dev, bus_id, &b44_adjust_link,
			     PHY_INTERFACE_MODE_MII);
	अगर (IS_ERR(phydev)) अणु
		dev_err(sdev->dev, "could not attach PHY at %i\n",
			bp->phy_addr);
		err = PTR_ERR(phydev);
		जाओ err_out_mdiobus_unरेजिस्टर;
	पूर्ण

	/* mask with MAC supported features */
	linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT, mask);
	linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT, mask);
	linkmode_set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, mask);
	linkmode_set_bit(ETHTOOL_LINK_MODE_MII_BIT, mask);
	linkmode_and(phydev->supported, phydev->supported, mask);
	linkmode_copy(phydev->advertising, phydev->supported);

	bp->old_link = 0;
	bp->phy_addr = phydev->mdio.addr;

	phy_attached_info(phydev);

	वापस 0;

err_out_mdiobus_unरेजिस्टर:
	mdiobus_unरेजिस्टर(mii_bus);

err_out_mdiobus:
	mdiobus_मुक्त(mii_bus);

err_out:
	वापस err;
पूर्ण

अटल व्योम b44_unरेजिस्टर_phy_one(काष्ठा b44 *bp)
अणु
	काष्ठा net_device *dev = bp->dev;
	काष्ठा mii_bus *mii_bus = bp->mii_bus;

	phy_disconnect(dev->phydev);
	mdiobus_unरेजिस्टर(mii_bus);
	mdiobus_मुक्त(mii_bus);
पूर्ण

अटल पूर्णांक b44_init_one(काष्ठा ssb_device *sdev,
			स्थिर काष्ठा ssb_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा b44 *bp;
	पूर्णांक err;

	instance++;

	dev = alloc_etherdev(माप(*bp));
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	SET_NETDEV_DEV(dev, sdev->dev);

	/* No पूर्णांकeresting netdevice features in this card... */
	dev->features |= 0;

	bp = netdev_priv(dev);
	bp->sdev = sdev;
	bp->dev = dev;
	bp->क्रमce_copyअवरोध = 0;

	bp->msg_enable = netअगर_msg_init(b44_debug, B44_DEF_MSG_ENABLE);

	spin_lock_init(&bp->lock);
	u64_stats_init(&bp->hw_stats.syncp);

	bp->rx_pending = B44_DEF_RX_RING_PENDING;
	bp->tx_pending = B44_DEF_TX_RING_PENDING;

	dev->netdev_ops = &b44_netdev_ops;
	netअगर_napi_add(dev, &bp->napi, b44_poll, 64);
	dev->watchकरोg_समयo = B44_TX_TIMEOUT;
	dev->min_mtu = B44_MIN_MTU;
	dev->max_mtu = B44_MAX_MTU;
	dev->irq = sdev->irq;
	dev->ethtool_ops = &b44_ethtool_ops;

	err = ssb_bus_घातerup(sdev->bus, 0);
	अगर (err) अणु
		dev_err(sdev->dev,
			"Failed to powerup the bus\n");
		जाओ err_out_मुक्त_dev;
	पूर्ण

	err = dma_set_mask_and_coherent(sdev->dma_dev, DMA_BIT_MASK(30));
	अगर (err) अणु
		dev_err(sdev->dev,
			"Required 30BIT DMA mask unsupported by the system\n");
		जाओ err_out_घातerकरोwn;
	पूर्ण

	err = b44_get_invariants(bp);
	अगर (err) अणु
		dev_err(sdev->dev,
			"Problem fetching invariants of chip, aborting\n");
		जाओ err_out_घातerकरोwn;
	पूर्ण

	अगर (bp->phy_addr == B44_PHY_ADDR_NO_PHY) अणु
		dev_err(sdev->dev, "No PHY present on this MAC, aborting\n");
		err = -ENODEV;
		जाओ err_out_घातerकरोwn;
	पूर्ण

	bp->mii_अगर.dev = dev;
	bp->mii_अगर.mdio_पढ़ो = b44_mdio_पढ़ो_mii;
	bp->mii_अगर.mdio_ग_लिखो = b44_mdio_ग_लिखो_mii;
	bp->mii_अगर.phy_id = bp->phy_addr;
	bp->mii_अगर.phy_id_mask = 0x1f;
	bp->mii_अगर.reg_num_mask = 0x1f;

	/* By शेष, advertise all speed/duplex settings. */
	bp->flags |= (B44_FLAG_ADV_10HALF | B44_FLAG_ADV_10FULL |
		      B44_FLAG_ADV_100HALF | B44_FLAG_ADV_100FULL);

	/* By शेष, स्वतः-negotiate PAUSE. */
	bp->flags |= B44_FLAG_PAUSE_AUTO;

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(sdev->dev, "Cannot register net device, aborting\n");
		जाओ err_out_घातerकरोwn;
	पूर्ण

	netअगर_carrier_off(dev);

	ssb_set_drvdata(sdev, dev);

	/* Chip reset provides घातer to the b44 MAC & PCI cores, which
	 * is necessary क्रम MAC रेजिस्टर access.
	 */
	b44_chip_reset(bp, B44_CHIP_RESET_FULL);

	/* करो a phy reset to test अगर there is an active phy */
	err = b44_phy_reset(bp);
	अगर (err < 0) अणु
		dev_err(sdev->dev, "phy reset failed\n");
		जाओ err_out_unरेजिस्टर_netdev;
	पूर्ण

	अगर (bp->flags & B44_FLAG_EXTERNAL_PHY) अणु
		err = b44_रेजिस्टर_phy_one(bp);
		अगर (err) अणु
			dev_err(sdev->dev, "Cannot register PHY, aborting\n");
			जाओ err_out_unरेजिस्टर_netdev;
		पूर्ण
	पूर्ण

	device_set_wakeup_capable(sdev->dev, true);
	netdev_info(dev, "%s %pM\n", DRV_DESCRIPTION, dev->dev_addr);

	वापस 0;

err_out_unरेजिस्टर_netdev:
	unरेजिस्टर_netdev(dev);
err_out_घातerकरोwn:
	ssb_bus_may_घातerकरोwn(sdev->bus);

err_out_मुक्त_dev:
	netअगर_napi_del(&bp->napi);
	मुक्त_netdev(dev);

out:
	वापस err;
पूर्ण

अटल व्योम b44_हटाओ_one(काष्ठा ssb_device *sdev)
अणु
	काष्ठा net_device *dev = ssb_get_drvdata(sdev);
	काष्ठा b44 *bp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	अगर (bp->flags & B44_FLAG_EXTERNAL_PHY)
		b44_unरेजिस्टर_phy_one(bp);
	ssb_device_disable(sdev, 0);
	ssb_bus_may_घातerकरोwn(sdev->bus);
	netअगर_napi_del(&bp->napi);
	मुक्त_netdev(dev);
	ssb_pcihost_set_घातer_state(sdev, PCI_D3hot);
	ssb_set_drvdata(sdev, शून्य);
पूर्ण

अटल पूर्णांक b44_suspend(काष्ठा ssb_device *sdev, pm_message_t state)
अणु
	काष्ठा net_device *dev = ssb_get_drvdata(sdev);
	काष्ठा b44 *bp = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस 0;

	del_समयr_sync(&bp->समयr);

	spin_lock_irq(&bp->lock);

	b44_halt(bp);
	netअगर_carrier_off(bp->dev);
	netअगर_device_detach(bp->dev);
	b44_मुक्त_rings(bp);

	spin_unlock_irq(&bp->lock);

	मुक्त_irq(dev->irq, dev);
	अगर (bp->flags & B44_FLAG_WOL_ENABLE) अणु
		b44_init_hw(bp, B44_PARTIAL_RESET);
		b44_setup_wol(bp);
	पूर्ण

	ssb_pcihost_set_घातer_state(sdev, PCI_D3hot);
	वापस 0;
पूर्ण

अटल पूर्णांक b44_resume(काष्ठा ssb_device *sdev)
अणु
	काष्ठा net_device *dev = ssb_get_drvdata(sdev);
	काष्ठा b44 *bp = netdev_priv(dev);
	पूर्णांक rc = 0;

	rc = ssb_bus_घातerup(sdev->bus, 0);
	अगर (rc) अणु
		dev_err(sdev->dev,
			"Failed to powerup the bus\n");
		वापस rc;
	पूर्ण

	अगर (!netअगर_running(dev))
		वापस 0;

	spin_lock_irq(&bp->lock);
	b44_init_rings(bp);
	b44_init_hw(bp, B44_FULL_RESET);
	spin_unlock_irq(&bp->lock);

	/*
	 * As a shared पूर्णांकerrupt, the handler can be called immediately. To be
	 * able to check the पूर्णांकerrupt status the hardware must alपढ़ोy be
	 * घातered back on (b44_init_hw).
	 */
	rc = request_irq(dev->irq, b44_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev);
	अगर (rc) अणु
		netdev_err(dev, "request_irq failed\n");
		spin_lock_irq(&bp->lock);
		b44_halt(bp);
		b44_मुक्त_rings(bp);
		spin_unlock_irq(&bp->lock);
		वापस rc;
	पूर्ण

	netअगर_device_attach(bp->dev);

	b44_enable_पूर्णांकs(bp);
	netअगर_wake_queue(dev);

	mod_समयr(&bp->समयr, jअगरfies + 1);

	वापस 0;
पूर्ण

अटल काष्ठा ssb_driver b44_ssb_driver = अणु
	.name		= DRV_MODULE_NAME,
	.id_table	= b44_ssb_tbl,
	.probe		= b44_init_one,
	.हटाओ		= b44_हटाओ_one,
	.suspend	= b44_suspend,
	.resume		= b44_resume,
पूर्ण;

अटल अंतरभूत पूर्णांक __init b44_pci_init(व्योम)
अणु
	पूर्णांक err = 0;
#अगर_घोषित CONFIG_B44_PCI
	err = ssb_pcihost_रेजिस्टर(&b44_pci_driver);
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल अंतरभूत व्योम b44_pci_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_B44_PCI
	ssb_pcihost_unरेजिस्टर(&b44_pci_driver);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init b44_init(व्योम)
अणु
	अचिन्हित पूर्णांक dma_desc_align_size = dma_get_cache_alignment();
	पूर्णांक err;

	/* Setup paramaters क्रम syncing RX/TX DMA descriptors */
	dma_desc_sync_size = max_t(अचिन्हित पूर्णांक, dma_desc_align_size, माप(काष्ठा dma_desc));

	err = b44_pci_init();
	अगर (err)
		वापस err;
	err = ssb_driver_रेजिस्टर(&b44_ssb_driver);
	अगर (err)
		b44_pci_निकास();
	वापस err;
पूर्ण

अटल व्योम __निकास b44_cleanup(व्योम)
अणु
	ssb_driver_unरेजिस्टर(&b44_ssb_driver);
	b44_pci_निकास();
पूर्ण

module_init(b44_init);
module_निकास(b44_cleanup);

