<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Alchemy Au1x00 ethernet driver
 *
 * Copyright 2001-2003, 2006 MontaVista Software Inc.
 * Copyright 2002 TimeSys Corp.
 * Added ethtool/mii-tool support,
 * Copyright 2004 Matt Porter <mporter@kernel.crashing.org>
 * Update: 2004 Bjoern Riemer, riemer@fokus.fraunhofer.de
 * or riemer@riemer-nt.de: fixed the link beat detection with
 * ioctls (SIOCGMIIPHY)
 * Copyright 2006 Herbert Valerio Riedel <hvr@gnu.org>
 *  converted to use linux-2.6.x's PHY framework
 *
 * Author: MontaVista Software, Inc.
 *		ppopov@mvista.com or source@mvista.com
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/capability.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/in.h>
#समावेश <linux/ioport.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/crc32.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/processor.h>

#समावेश <au1000.h>
#समावेश <au1xxx_eth.h>
#समावेश <prom.h>

#समावेश "au1000_eth.h"

#अगर_घोषित AU1000_ETH_DEBUG
अटल पूर्णांक au1000_debug = 5;
#अन्यथा
अटल पूर्णांक au1000_debug = 3;
#पूर्ण_अगर

#घोषणा AU1000_DEF_MSG_ENABLE	(NETIF_MSG_DRV	| \
				NETIF_MSG_PROBE	| \
				NETIF_MSG_LINK)

#घोषणा DRV_NAME	"au1000_eth"
#घोषणा DRV_AUTHOR	"Pete Popov <ppopov@embeddedalley.com>"
#घोषणा DRV_DESC	"Au1xxx on-chip Ethernet driver"

MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION(DRV_DESC);
MODULE_LICENSE("GPL");

/* AU1000 MAC रेजिस्टरs and bits */
#घोषणा MAC_CONTROL		0x0
#  define MAC_RX_ENABLE		(1 << 2)
#  define MAC_TX_ENABLE		(1 << 3)
#  define MAC_DEF_CHECK		(1 << 5)
#  define MAC_SET_BL(X)		(((X) & 0x3) << 6)
#  define MAC_AUTO_PAD		(1 << 8)
#  define MAC_DISABLE_RETRY	(1 << 10)
#  define MAC_DISABLE_BCAST	(1 << 11)
#  define MAC_LATE_COL		(1 << 12)
#  define MAC_HASH_MODE		(1 << 13)
#  define MAC_HASH_ONLY		(1 << 15)
#  define MAC_PASS_ALL		(1 << 16)
#  define MAC_INVERSE_FILTER	(1 << 17)
#  define MAC_PROMISCUOUS	(1 << 18)
#  define MAC_PASS_ALL_MULTI	(1 << 19)
#  define MAC_FULL_DUPLEX	(1 << 20)
#  define MAC_NORMAL_MODE	0
#  define MAC_INT_LOOPBACK	(1 << 21)
#  define MAC_EXT_LOOPBACK	(1 << 22)
#  define MAC_DISABLE_RX_OWN	(1 << 23)
#  define MAC_BIG_ENDIAN	(1 << 30)
#  define MAC_RX_ALL		(1 << 31)
#घोषणा MAC_ADDRESS_HIGH	0x4
#घोषणा MAC_ADDRESS_LOW		0x8
#घोषणा MAC_MCAST_HIGH		0xC
#घोषणा MAC_MCAST_LOW		0x10
#घोषणा MAC_MII_CNTRL		0x14
#  define MAC_MII_BUSY		(1 << 0)
#  define MAC_MII_READ		0
#  define MAC_MII_WRITE		(1 << 1)
#  define MAC_SET_MII_SELECT_REG(X) (((X) & 0x1f) << 6)
#  define MAC_SET_MII_SELECT_PHY(X) (((X) & 0x1f) << 11)
#घोषणा MAC_MII_DATA		0x18
#घोषणा MAC_FLOW_CNTRL		0x1C
#  define MAC_FLOW_CNTRL_BUSY	(1 << 0)
#  define MAC_FLOW_CNTRL_ENABLE (1 << 1)
#  define MAC_PASS_CONTROL	(1 << 2)
#  define MAC_SET_PAUSE(X)	(((X) & 0xffff) << 16)
#घोषणा MAC_VLAN1_TAG		0x20
#घोषणा MAC_VLAN2_TAG		0x24

/* Ethernet Controller Enable */
#  define MAC_EN_CLOCK_ENABLE	(1 << 0)
#  define MAC_EN_RESET0		(1 << 1)
#  define MAC_EN_TOSS		(0 << 2)
#  define MAC_EN_CACHEABLE	(1 << 3)
#  define MAC_EN_RESET1		(1 << 4)
#  define MAC_EN_RESET2		(1 << 5)
#  define MAC_DMA_RESET		(1 << 6)

/* Ethernet Controller DMA Channels */
/* offsets from MAC_TX_RING_ADDR address */
#घोषणा MAC_TX_BUFF0_STATUS	0x0
#  define TX_FRAME_ABORTED	(1 << 0)
#  define TX_JAB_TIMEOUT	(1 << 1)
#  define TX_NO_CARRIER		(1 << 2)
#  define TX_LOSS_CARRIER	(1 << 3)
#  define TX_EXC_DEF		(1 << 4)
#  define TX_LATE_COLL_ABORT	(1 << 5)
#  define TX_EXC_COLL		(1 << 6)
#  define TX_UNDERRUN		(1 << 7)
#  define TX_DEFERRED		(1 << 8)
#  define TX_LATE_COLL		(1 << 9)
#  define TX_COLL_CNT_MASK	(0xF << 10)
#  define TX_PKT_RETRY		(1 << 31)
#घोषणा MAC_TX_BUFF0_ADDR	0x4
#  define TX_DMA_ENABLE		(1 << 0)
#  define TX_T_DONE		(1 << 1)
#  define TX_GET_DMA_BUFFER(X)	(((X) >> 2) & 0x3)
#घोषणा MAC_TX_BUFF0_LEN	0x8
#घोषणा MAC_TX_BUFF1_STATUS	0x10
#घोषणा MAC_TX_BUFF1_ADDR	0x14
#घोषणा MAC_TX_BUFF1_LEN	0x18
#घोषणा MAC_TX_BUFF2_STATUS	0x20
#घोषणा MAC_TX_BUFF2_ADDR	0x24
#घोषणा MAC_TX_BUFF2_LEN	0x28
#घोषणा MAC_TX_BUFF3_STATUS	0x30
#घोषणा MAC_TX_BUFF3_ADDR	0x34
#घोषणा MAC_TX_BUFF3_LEN	0x38

/* offsets from MAC_RX_RING_ADDR */
#घोषणा MAC_RX_BUFF0_STATUS	0x0
#  define RX_FRAME_LEN_MASK	0x3fff
#  define RX_WDOG_TIMER		(1 << 14)
#  define RX_RUNT		(1 << 15)
#  define RX_OVERLEN		(1 << 16)
#  define RX_COLL		(1 << 17)
#  define RX_ETHER		(1 << 18)
#  define RX_MII_ERROR		(1 << 19)
#  define RX_DRIBBLING		(1 << 20)
#  define RX_CRC_ERROR		(1 << 21)
#  define RX_VLAN1		(1 << 22)
#  define RX_VLAN2		(1 << 23)
#  define RX_LEN_ERROR		(1 << 24)
#  define RX_CNTRL_FRAME	(1 << 25)
#  define RX_U_CNTRL_FRAME	(1 << 26)
#  define RX_MCAST_FRAME	(1 << 27)
#  define RX_BCAST_FRAME	(1 << 28)
#  define RX_FILTER_FAIL	(1 << 29)
#  define RX_PACKET_FILTER	(1 << 30)
#  define RX_MISSED_FRAME	(1 << 31)

#  define RX_ERROR (RX_WDOG_TIMER | RX_RUNT | RX_OVERLEN |  \
		    RX_COLL | RX_MII_ERROR | RX_CRC_ERROR | \
		    RX_LEN_ERROR | RX_U_CNTRL_FRAME | RX_MISSED_FRAME)
#घोषणा MAC_RX_BUFF0_ADDR	0x4
#  define RX_DMA_ENABLE		(1 << 0)
#  define RX_T_DONE		(1 << 1)
#  define RX_GET_DMA_BUFFER(X)	(((X) >> 2) & 0x3)
#  define RX_SET_BUFF_ADDR(X)	((X) & 0xffffffc0)
#घोषणा MAC_RX_BUFF1_STATUS	0x10
#घोषणा MAC_RX_BUFF1_ADDR	0x14
#घोषणा MAC_RX_BUFF2_STATUS	0x20
#घोषणा MAC_RX_BUFF2_ADDR	0x24
#घोषणा MAC_RX_BUFF3_STATUS	0x30
#घोषणा MAC_RX_BUFF3_ADDR	0x34

/*
 * Theory of operation
 *
 * The Au1000 MACs use a simple rx and tx descriptor ring scheme.
 * There are four receive and four transmit descriptors.  These
 * descriptors are not in memory; rather, they are just a set of
 * hardware रेजिस्टरs.
 *
 * Since the Au1000 has a coherent data cache, the receive and
 * transmit buffers are allocated from the KSEG0 segment. The
 * hardware रेजिस्टरs, however, are still mapped at KSEG1 to
 * make sure there's no out-of-order ग_लिखोs, and that all ग_लिखोs
 * complete immediately.
 */

/*
 * board-specअगरic configurations
 *
 * PHY detection algorithm
 *
 * If phy_अटल_config is undefined, the PHY setup is
 * स्वतःdetected:
 *
 * mii_probe() first searches the current MAC's MII bus क्रम a PHY,
 * selecting the first (or last, अगर phy_search_highest_addr is
 * defined) PHY address not alपढ़ोy claimed by another netdev.
 *
 * If nothing was found that way when searching क्रम the 2nd ethernet
 * controller's PHY and phy1_search_mac0 is defined, then
 * the first MII bus is searched as well क्रम an unclaimed PHY; this is
 * needed in हाल of a dual-PHY accessible only through the MAC0's MII
 * bus.
 *
 * Finally, अगर no PHY is found, then the corresponding ethernet
 * controller is not रेजिस्टरed to the network subप्रणाली.
 */

/* स्वतःdetection शेषs: phy1_search_mac0 */

/* अटल PHY setup
 *
 * most boards PHY setup should be detectable properly with the
 * स्वतःdetection algorithm in mii_probe(), but in some हालs (e.g. अगर
 * you have a चयन attached, or want to use the PHY's पूर्णांकerrupt
 * notअगरication capabilities) you can provide a अटल PHY
 * configuration here
 *
 * IRQs may only be set, अगर a PHY address was configured
 * If a PHY address is given, also a bus id is required to be set
 *
 * ps: make sure the used irqs are configured properly in the board
 * specअगरic irq-map
 */
अटल व्योम au1000_enable_mac(काष्ठा net_device *dev, पूर्णांक क्रमce_reset)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा au1000_निजी *aup = netdev_priv(dev);

	spin_lock_irqsave(&aup->lock, flags);

	अगर (क्रमce_reset || (!aup->mac_enabled)) अणु
		ग_लिखोl(MAC_EN_CLOCK_ENABLE, aup->enable);
		wmb(); /* drain ग_लिखोbuffer */
		mdelay(2);
		ग_लिखोl((MAC_EN_RESET0 | MAC_EN_RESET1 | MAC_EN_RESET2
				| MAC_EN_CLOCK_ENABLE), aup->enable);
		wmb(); /* drain ग_लिखोbuffer */
		mdelay(2);

		aup->mac_enabled = 1;
	पूर्ण

	spin_unlock_irqrestore(&aup->lock, flags);
पूर्ण

/*
 * MII operations
 */
अटल पूर्णांक au1000_mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक reg)
अणु
	काष्ठा au1000_निजी *aup = netdev_priv(dev);
	u32 *स्थिर mii_control_reg = &aup->mac->mii_control;
	u32 *स्थिर mii_data_reg = &aup->mac->mii_data;
	u32 समयकरोut = 20;
	u32 mii_control;

	जबतक (पढ़ोl(mii_control_reg) & MAC_MII_BUSY) अणु
		mdelay(1);
		अगर (--समयकरोut == 0) अणु
			netdev_err(dev, "read_MII busy timeout!!\n");
			वापस -1;
		पूर्ण
	पूर्ण

	mii_control = MAC_SET_MII_SELECT_REG(reg) |
		MAC_SET_MII_SELECT_PHY(phy_addr) | MAC_MII_READ;

	ग_लिखोl(mii_control, mii_control_reg);

	समयकरोut = 20;
	जबतक (पढ़ोl(mii_control_reg) & MAC_MII_BUSY) अणु
		mdelay(1);
		अगर (--समयकरोut == 0) अणु
			netdev_err(dev, "mdio_read busy timeout!!\n");
			वापस -1;
		पूर्ण
	पूर्ण
	वापस पढ़ोl(mii_data_reg);
पूर्ण

अटल व्योम au1000_mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_addr,
			      पूर्णांक reg, u16 value)
अणु
	काष्ठा au1000_निजी *aup = netdev_priv(dev);
	u32 *स्थिर mii_control_reg = &aup->mac->mii_control;
	u32 *स्थिर mii_data_reg = &aup->mac->mii_data;
	u32 समयकरोut = 20;
	u32 mii_control;

	जबतक (पढ़ोl(mii_control_reg) & MAC_MII_BUSY) अणु
		mdelay(1);
		अगर (--समयकरोut == 0) अणु
			netdev_err(dev, "mdio_write busy timeout!!\n");
			वापस;
		पूर्ण
	पूर्ण

	mii_control = MAC_SET_MII_SELECT_REG(reg) |
		MAC_SET_MII_SELECT_PHY(phy_addr) | MAC_MII_WRITE;

	ग_लिखोl(value, mii_data_reg);
	ग_लिखोl(mii_control, mii_control_reg);
पूर्ण

अटल पूर्णांक au1000_mdiobus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक regnum)
अणु
	काष्ठा net_device *स्थिर dev = bus->priv;

	/* make sure the MAC associated with this
	 * mii_bus is enabled
	 */
	au1000_enable_mac(dev, 0);

	वापस au1000_mdio_पढ़ो(dev, phy_addr, regnum);
पूर्ण

अटल पूर्णांक au1000_mdiobus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक regnum,
				u16 value)
अणु
	काष्ठा net_device *स्थिर dev = bus->priv;

	/* make sure the MAC associated with this
	 * mii_bus is enabled
	 */
	au1000_enable_mac(dev, 0);

	au1000_mdio_ग_लिखो(dev, phy_addr, regnum, value);
	वापस 0;
पूर्ण

अटल पूर्णांक au1000_mdiobus_reset(काष्ठा mii_bus *bus)
अणु
	काष्ठा net_device *स्थिर dev = bus->priv;

	/* make sure the MAC associated with this
	 * mii_bus is enabled
	 */
	au1000_enable_mac(dev, 0);

	वापस 0;
पूर्ण

अटल व्योम au1000_hard_stop(काष्ठा net_device *dev)
अणु
	काष्ठा au1000_निजी *aup = netdev_priv(dev);
	u32 reg;

	netअगर_dbg(aup, drv, dev, "hard stop\n");

	reg = पढ़ोl(&aup->mac->control);
	reg &= ~(MAC_RX_ENABLE | MAC_TX_ENABLE);
	ग_लिखोl(reg, &aup->mac->control);
	wmb(); /* drain ग_लिखोbuffer */
	mdelay(10);
पूर्ण

अटल व्योम au1000_enable_rx_tx(काष्ठा net_device *dev)
अणु
	काष्ठा au1000_निजी *aup = netdev_priv(dev);
	u32 reg;

	netअगर_dbg(aup, hw, dev, "enable_rx_tx\n");

	reg = पढ़ोl(&aup->mac->control);
	reg |= (MAC_RX_ENABLE | MAC_TX_ENABLE);
	ग_लिखोl(reg, &aup->mac->control);
	wmb(); /* drain ग_लिखोbuffer */
	mdelay(10);
पूर्ण

अटल व्योम
au1000_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा au1000_निजी *aup = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	अचिन्हित दीर्घ flags;
	u32 reg;

	पूर्णांक status_change = 0;

	BUG_ON(!phydev);

	spin_lock_irqsave(&aup->lock, flags);

	अगर (phydev->link && (aup->old_speed != phydev->speed)) अणु
		/* speed changed */

		चयन (phydev->speed) अणु
		हाल SPEED_10:
		हाल SPEED_100:
			अवरोध;
		शेष:
			netdev_warn(dev, "Speed (%d) is not 10/100 ???\n",
							phydev->speed);
			अवरोध;
		पूर्ण

		aup->old_speed = phydev->speed;

		status_change = 1;
	पूर्ण

	अगर (phydev->link && (aup->old_duplex != phydev->duplex)) अणु
		/* duplex mode changed */

		/* चयनing duplex mode requires to disable rx and tx! */
		au1000_hard_stop(dev);

		reg = पढ़ोl(&aup->mac->control);
		अगर (DUPLEX_FULL == phydev->duplex) अणु
			reg |= MAC_FULL_DUPLEX;
			reg &= ~MAC_DISABLE_RX_OWN;
		पूर्ण अन्यथा अणु
			reg &= ~MAC_FULL_DUPLEX;
			reg |= MAC_DISABLE_RX_OWN;
		पूर्ण
		ग_लिखोl(reg, &aup->mac->control);
		wmb(); /* drain ग_लिखोbuffer */
		mdelay(1);

		au1000_enable_rx_tx(dev);
		aup->old_duplex = phydev->duplex;

		status_change = 1;
	पूर्ण

	अगर (phydev->link != aup->old_link) अणु
		/* link state changed */

		अगर (!phydev->link) अणु
			/* link went करोwn */
			aup->old_speed = 0;
			aup->old_duplex = -1;
		पूर्ण

		aup->old_link = phydev->link;
		status_change = 1;
	पूर्ण

	spin_unlock_irqrestore(&aup->lock, flags);

	अगर (status_change) अणु
		अगर (phydev->link)
			netdev_info(dev, "link up (%d/%s)\n",
			       phydev->speed,
			       DUPLEX_FULL == phydev->duplex ? "Full" : "Half");
		अन्यथा
			netdev_info(dev, "link down\n");
	पूर्ण
पूर्ण

अटल पूर्णांक au1000_mii_probe(काष्ठा net_device *dev)
अणु
	काष्ठा au1000_निजी *स्थिर aup = netdev_priv(dev);
	काष्ठा phy_device *phydev = शून्य;
	पूर्णांक phy_addr;

	अगर (aup->phy_अटल_config) अणु
		BUG_ON(aup->mac_id < 0 || aup->mac_id > 1);

		अगर (aup->phy_addr)
			phydev = mdiobus_get_phy(aup->mii_bus, aup->phy_addr);
		अन्यथा
			netdev_info(dev, "using PHY-less setup\n");
		वापस 0;
	पूर्ण

	/* find the first (lowest address) PHY
	 * on the current MAC's MII bus
	 */
	क्रम (phy_addr = 0; phy_addr < PHY_MAX_ADDR; phy_addr++)
		अगर (mdiobus_get_phy(aup->mii_bus, phy_addr)) अणु
			phydev = mdiobus_get_phy(aup->mii_bus, phy_addr);
			अगर (!aup->phy_search_highest_addr)
				/* अवरोध out with first one found */
				अवरोध;
		पूर्ण

	अगर (aup->phy1_search_mac0) अणु
		/* try harder to find a PHY */
		अगर (!phydev && (aup->mac_id == 1)) अणु
			/* no PHY found, maybe we have a dual PHY? */
			dev_info(&dev->dev, ": no PHY found on MAC1, "
				"let's see if it's attached to MAC0...\n");

			/* find the first (lowest address) non-attached
			 * PHY on the MAC0 MII bus
			 */
			क्रम (phy_addr = 0; phy_addr < PHY_MAX_ADDR; phy_addr++) अणु
				काष्ठा phy_device *स्थिर पंचांगp_phydev =
					mdiobus_get_phy(aup->mii_bus,
							phy_addr);

				अगर (aup->mac_id == 1)
					अवरोध;

				/* no PHY here... */
				अगर (!पंचांगp_phydev)
					जारी;

				/* alपढ़ोy claimed by MAC0 */
				अगर (पंचांगp_phydev->attached_dev)
					जारी;

				phydev = पंचांगp_phydev;
				अवरोध; /* found it */
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!phydev) अणु
		netdev_err(dev, "no PHY found\n");
		वापस -1;
	पूर्ण

	/* now we are supposed to have a proper phydev, to attach to... */
	BUG_ON(phydev->attached_dev);

	phydev = phy_connect(dev, phydev_name(phydev),
			     &au1000_adjust_link, PHY_INTERFACE_MODE_MII);

	अगर (IS_ERR(phydev)) अणु
		netdev_err(dev, "Could not attach to PHY\n");
		वापस PTR_ERR(phydev);
	पूर्ण

	phy_set_max_speed(phydev, SPEED_100);

	aup->old_link = 0;
	aup->old_speed = 0;
	aup->old_duplex = -1;

	phy_attached_info(phydev);

	वापस 0;
पूर्ण

/*
 * Buffer allocation/deallocation routines. The buffer descriptor वापसed
 * has the भव and dma address of a buffer suitable क्रम
 * both, receive and transmit operations.
 */
अटल काष्ठा db_dest *au1000_GetFreeDB(काष्ठा au1000_निजी *aup)
अणु
	काष्ठा db_dest *pDB;
	pDB = aup->pDBमुक्त;

	अगर (pDB)
		aup->pDBमुक्त = pDB->pnext;

	वापस pDB;
पूर्ण

व्योम au1000_ReleaseDB(काष्ठा au1000_निजी *aup, काष्ठा db_dest *pDB)
अणु
	काष्ठा db_dest *pDBमुक्त = aup->pDBमुक्त;
	अगर (pDBमुक्त)
		pDBमुक्त->pnext = pDB;
	aup->pDBमुक्त = pDB;
पूर्ण

अटल व्योम au1000_reset_mac_unlocked(काष्ठा net_device *dev)
अणु
	काष्ठा au1000_निजी *स्थिर aup = netdev_priv(dev);
	पूर्णांक i;

	au1000_hard_stop(dev);

	ग_लिखोl(MAC_EN_CLOCK_ENABLE, aup->enable);
	wmb(); /* drain ग_लिखोbuffer */
	mdelay(2);
	ग_लिखोl(0, aup->enable);
	wmb(); /* drain ग_लिखोbuffer */
	mdelay(2);

	aup->tx_full = 0;
	क्रम (i = 0; i < NUM_RX_DMA; i++) अणु
		/* reset control bits */
		aup->rx_dma_ring[i]->buff_stat &= ~0xf;
	पूर्ण
	क्रम (i = 0; i < NUM_TX_DMA; i++) अणु
		/* reset control bits */
		aup->tx_dma_ring[i]->buff_stat &= ~0xf;
	पूर्ण

	aup->mac_enabled = 0;

पूर्ण

अटल व्योम au1000_reset_mac(काष्ठा net_device *dev)
अणु
	काष्ठा au1000_निजी *स्थिर aup = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	netअगर_dbg(aup, hw, dev, "reset mac, aup %x\n",
					(अचिन्हित)aup);

	spin_lock_irqsave(&aup->lock, flags);

	au1000_reset_mac_unlocked(dev);

	spin_unlock_irqrestore(&aup->lock, flags);
पूर्ण

/*
 * Setup the receive and transmit "rings".  These poपूर्णांकers are the addresses
 * of the rx and tx MAC DMA रेजिस्टरs so they are fixed by the hardware --
 * these are not descriptors sitting in memory.
 */
अटल व्योम
au1000_setup_hw_rings(काष्ठा au1000_निजी *aup, व्योम __iomem *tx_base)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_RX_DMA; i++) अणु
		aup->rx_dma_ring[i] = (काष्ठा rx_dma *)
			(tx_base + 0x100 + माप(काष्ठा rx_dma) * i);
	पूर्ण
	क्रम (i = 0; i < NUM_TX_DMA; i++) अणु
		aup->tx_dma_ring[i] = (काष्ठा tx_dma *)
			(tx_base + माप(काष्ठा tx_dma) * i);
	पूर्ण
पूर्ण

/*
 * ethtool operations
 */
अटल व्योम
au1000_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा au1000_निजी *aup = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	snम_लिखो(info->bus_info, माप(info->bus_info), "%s %d", DRV_NAME,
		 aup->mac_id);
पूर्ण

अटल व्योम au1000_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा au1000_निजी *aup = netdev_priv(dev);
	aup->msg_enable = value;
पूर्ण

अटल u32 au1000_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा au1000_निजी *aup = netdev_priv(dev);
	वापस aup->msg_enable;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops au1000_ethtool_ops = अणु
	.get_drvinfo = au1000_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_msglevel = au1000_get_msglevel,
	.set_msglevel = au1000_set_msglevel,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

/*
 * Initialize the पूर्णांकerface.
 *
 * When the device घातers up, the घड़ीs are disabled and the
 * mac is in reset state.  When the पूर्णांकerface is बंदd, we
 * करो the same -- reset the device and disable the घड़ीs to
 * conserve घातer. Thus, whenever au1000_init() is called,
 * the device should alपढ़ोy be in reset state.
 */
अटल पूर्णांक au1000_init(काष्ठा net_device *dev)
अणु
	काष्ठा au1000_निजी *aup = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	u32 control;

	netअगर_dbg(aup, hw, dev, "au1000_init\n");

	/* bring the device out of reset */
	au1000_enable_mac(dev, 1);

	spin_lock_irqsave(&aup->lock, flags);

	ग_लिखोl(0, &aup->mac->control);
	aup->tx_head = (aup->tx_dma_ring[0]->buff_stat & 0xC) >> 2;
	aup->tx_tail = aup->tx_head;
	aup->rx_head = (aup->rx_dma_ring[0]->buff_stat & 0xC) >> 2;

	ग_लिखोl(dev->dev_addr[5]<<8 | dev->dev_addr[4],
					&aup->mac->mac_addr_high);
	ग_लिखोl(dev->dev_addr[3]<<24 | dev->dev_addr[2]<<16 |
		dev->dev_addr[1]<<8 | dev->dev_addr[0],
					&aup->mac->mac_addr_low);


	क्रम (i = 0; i < NUM_RX_DMA; i++)
		aup->rx_dma_ring[i]->buff_stat |= RX_DMA_ENABLE;

	wmb(); /* drain ग_लिखोbuffer */

	control = MAC_RX_ENABLE | MAC_TX_ENABLE;
#अगर_अघोषित CONFIG_CPU_LITTLE_ENDIAN
	control |= MAC_BIG_ENDIAN;
#पूर्ण_अगर
	अगर (dev->phydev) अणु
		अगर (dev->phydev->link && (DUPLEX_FULL == dev->phydev->duplex))
			control |= MAC_FULL_DUPLEX;
		अन्यथा
			control |= MAC_DISABLE_RX_OWN;
	पूर्ण अन्यथा अणु /* PHY-less op, assume full-duplex */
		control |= MAC_FULL_DUPLEX;
	पूर्ण

	ग_लिखोl(control, &aup->mac->control);
	ग_लिखोl(0x8100, &aup->mac->vlan1_tag); /* activate vlan support */
	wmb(); /* drain ग_लिखोbuffer */

	spin_unlock_irqrestore(&aup->lock, flags);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम au1000_update_rx_stats(काष्ठा net_device *dev, u32 status)
अणु
	काष्ठा net_device_stats *ps = &dev->stats;

	ps->rx_packets++;
	अगर (status & RX_MCAST_FRAME)
		ps->multicast++;

	अगर (status & RX_ERROR) अणु
		ps->rx_errors++;
		अगर (status & RX_MISSED_FRAME)
			ps->rx_missed_errors++;
		अगर (status & (RX_OVERLEN | RX_RUNT | RX_LEN_ERROR))
			ps->rx_length_errors++;
		अगर (status & RX_CRC_ERROR)
			ps->rx_crc_errors++;
		अगर (status & RX_COLL)
			ps->collisions++;
	पूर्ण अन्यथा
		ps->rx_bytes += status & RX_FRAME_LEN_MASK;

पूर्ण

/*
 * Au1000 receive routine.
 */
अटल पूर्णांक au1000_rx(काष्ठा net_device *dev)
अणु
	काष्ठा au1000_निजी *aup = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	काष्ठा rx_dma *prxd;
	u32 buff_stat, status;
	काष्ठा db_dest *pDB;
	u32	frmlen;

	netअगर_dbg(aup, rx_status, dev, "au1000_rx head %d\n", aup->rx_head);

	prxd = aup->rx_dma_ring[aup->rx_head];
	buff_stat = prxd->buff_stat;
	जबतक (buff_stat & RX_T_DONE)  अणु
		status = prxd->status;
		pDB = aup->rx_db_inuse[aup->rx_head];
		au1000_update_rx_stats(dev, status);
		अगर (!(status & RX_ERROR))  अणु

			/* good frame */
			frmlen = (status & RX_FRAME_LEN_MASK);
			frmlen -= 4; /* Remove FCS */
			skb = netdev_alloc_skb(dev, frmlen + 2);
			अगर (skb == शून्य) अणु
				dev->stats.rx_dropped++;
				जारी;
			पूर्ण
			skb_reserve(skb, 2);	/* 16 byte IP header align */
			skb_copy_to_linear_data(skb,
				(अचिन्हित अक्षर *)pDB->vaddr, frmlen);
			skb_put(skb, frmlen);
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_rx(skb);	/* pass the packet to upper layers */
		पूर्ण अन्यथा अणु
			अगर (au1000_debug > 4) अणु
				pr_err("rx_error(s):");
				अगर (status & RX_MISSED_FRAME)
					pr_cont(" miss");
				अगर (status & RX_WDOG_TIMER)
					pr_cont(" wdog");
				अगर (status & RX_RUNT)
					pr_cont(" runt");
				अगर (status & RX_OVERLEN)
					pr_cont(" overlen");
				अगर (status & RX_COLL)
					pr_cont(" coll");
				अगर (status & RX_MII_ERROR)
					pr_cont(" mii error");
				अगर (status & RX_CRC_ERROR)
					pr_cont(" crc error");
				अगर (status & RX_LEN_ERROR)
					pr_cont(" len error");
				अगर (status & RX_U_CNTRL_FRAME)
					pr_cont(" u control frame");
				pr_cont("\n");
			पूर्ण
		पूर्ण
		prxd->buff_stat = (u32)(pDB->dma_addr | RX_DMA_ENABLE);
		aup->rx_head = (aup->rx_head + 1) & (NUM_RX_DMA - 1);
		wmb(); /* drain ग_लिखोbuffer */

		/* next descriptor */
		prxd = aup->rx_dma_ring[aup->rx_head];
		buff_stat = prxd->buff_stat;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम au1000_update_tx_stats(काष्ठा net_device *dev, u32 status)
अणु
	काष्ठा net_device_stats *ps = &dev->stats;

	अगर (status & TX_FRAME_ABORTED) अणु
		अगर (!dev->phydev || (DUPLEX_FULL == dev->phydev->duplex)) अणु
			अगर (status & (TX_JAB_TIMEOUT | TX_UNDERRUN)) अणु
				/* any other tx errors are only valid
				 * in half duplex mode
				 */
				ps->tx_errors++;
				ps->tx_पातed_errors++;
			पूर्ण
		पूर्ण अन्यथा अणु
			ps->tx_errors++;
			ps->tx_पातed_errors++;
			अगर (status & (TX_NO_CARRIER | TX_LOSS_CARRIER))
				ps->tx_carrier_errors++;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Called from the पूर्णांकerrupt service routine to acknowledge
 * the TX DONE bits.  This is a must अगर the irq is setup as
 * edge triggered.
 */
अटल व्योम au1000_tx_ack(काष्ठा net_device *dev)
अणु
	काष्ठा au1000_निजी *aup = netdev_priv(dev);
	काष्ठा tx_dma *ptxd;

	ptxd = aup->tx_dma_ring[aup->tx_tail];

	जबतक (ptxd->buff_stat & TX_T_DONE) अणु
		au1000_update_tx_stats(dev, ptxd->status);
		ptxd->buff_stat &= ~TX_T_DONE;
		ptxd->len = 0;
		wmb(); /* drain ग_लिखोbuffer */

		aup->tx_tail = (aup->tx_tail + 1) & (NUM_TX_DMA - 1);
		ptxd = aup->tx_dma_ring[aup->tx_tail];

		अगर (aup->tx_full) अणु
			aup->tx_full = 0;
			netअगर_wake_queue(dev);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Au1000 पूर्णांकerrupt service routine.
 */
अटल irqवापस_t au1000_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;

	/* Handle RX पूर्णांकerrupts first to minimize chance of overrun */

	au1000_rx(dev);
	au1000_tx_ack(dev);
	वापस IRQ_RETVAL(1);
पूर्ण

अटल पूर्णांक au1000_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक retval;
	काष्ठा au1000_निजी *aup = netdev_priv(dev);

	netअगर_dbg(aup, drv, dev, "open: dev=%p\n", dev);

	retval = request_irq(dev->irq, au1000_पूर्णांकerrupt, 0,
					dev->name, dev);
	अगर (retval) अणु
		netdev_err(dev, "unable to get IRQ %d\n", dev->irq);
		वापस retval;
	पूर्ण

	retval = au1000_init(dev);
	अगर (retval) अणु
		netdev_err(dev, "error in au1000_init\n");
		मुक्त_irq(dev->irq, dev);
		वापस retval;
	पूर्ण

	अगर (dev->phydev)
		phy_start(dev->phydev);

	netअगर_start_queue(dev);

	netअगर_dbg(aup, drv, dev, "open: Initialization done.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक au1000_बंद(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा au1000_निजी *स्थिर aup = netdev_priv(dev);

	netअगर_dbg(aup, drv, dev, "close: dev=%p\n", dev);

	अगर (dev->phydev)
		phy_stop(dev->phydev);

	spin_lock_irqsave(&aup->lock, flags);

	au1000_reset_mac_unlocked(dev);

	/* stop the device */
	netअगर_stop_queue(dev);

	/* disable the पूर्णांकerrupt */
	मुक्त_irq(dev->irq, dev);
	spin_unlock_irqrestore(&aup->lock, flags);

	वापस 0;
पूर्ण

/*
 * Au1000 transmit routine.
 */
अटल netdev_tx_t au1000_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा au1000_निजी *aup = netdev_priv(dev);
	काष्ठा net_device_stats *ps = &dev->stats;
	काष्ठा tx_dma *ptxd;
	u32 buff_stat;
	काष्ठा db_dest *pDB;
	पूर्णांक i;

	netअगर_dbg(aup, tx_queued, dev, "tx: aup %x len=%d, data=%p, head %d\n",
				(अचिन्हित)aup, skb->len,
				skb->data, aup->tx_head);

	ptxd = aup->tx_dma_ring[aup->tx_head];
	buff_stat = ptxd->buff_stat;
	अगर (buff_stat & TX_DMA_ENABLE) अणु
		/* We've wrapped around and the transmitter is still busy */
		netअगर_stop_queue(dev);
		aup->tx_full = 1;
		वापस NETDEV_TX_BUSY;
	पूर्ण अन्यथा अगर (buff_stat & TX_T_DONE) अणु
		au1000_update_tx_stats(dev, ptxd->status);
		ptxd->len = 0;
	पूर्ण

	अगर (aup->tx_full) अणु
		aup->tx_full = 0;
		netअगर_wake_queue(dev);
	पूर्ण

	pDB = aup->tx_db_inuse[aup->tx_head];
	skb_copy_from_linear_data(skb, (व्योम *)pDB->vaddr, skb->len);
	अगर (skb->len < ETH_ZLEN) अणु
		क्रम (i = skb->len; i < ETH_ZLEN; i++)
			((अक्षर *)pDB->vaddr)[i] = 0;

		ptxd->len = ETH_ZLEN;
	पूर्ण अन्यथा
		ptxd->len = skb->len;

	ps->tx_packets++;
	ps->tx_bytes += ptxd->len;

	ptxd->buff_stat = pDB->dma_addr | TX_DMA_ENABLE;
	wmb(); /* drain ग_लिखोbuffer */
	dev_kमुक्त_skb(skb);
	aup->tx_head = (aup->tx_head + 1) & (NUM_TX_DMA - 1);
	वापस NETDEV_TX_OK;
पूर्ण

/*
 * The Tx ring has been full दीर्घer than the watchकरोg समयout
 * value. The transmitter must be hung?
 */
अटल व्योम au1000_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	netdev_err(dev, "au1000_tx_timeout: dev=%p\n", dev);
	au1000_reset_mac(dev);
	au1000_init(dev);
	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम au1000_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा au1000_निजी *aup = netdev_priv(dev);
	u32 reg;

	netअगर_dbg(aup, drv, dev, "%s: flags=%x\n", __func__, dev->flags);
	reg = पढ़ोl(&aup->mac->control);
	अगर (dev->flags & IFF_PROMISC) अणु			/* Set promiscuous. */
		reg |= MAC_PROMISCUOUS;
	पूर्ण अन्यथा अगर ((dev->flags & IFF_ALLMULTI)  ||
			   netdev_mc_count(dev) > MULTICAST_FILTER_LIMIT) अणु
		reg |= MAC_PASS_ALL_MULTI;
		reg &= ~MAC_PROMISCUOUS;
		netdev_info(dev, "Pass all multicast\n");
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;
		u32 mc_filter[2];	/* Multicast hash filter */

		mc_filter[1] = mc_filter[0] = 0;
		netdev_क्रम_each_mc_addr(ha, dev)
			set_bit(ether_crc(ETH_ALEN, ha->addr)>>26,
					(दीर्घ *)mc_filter);
		ग_लिखोl(mc_filter[1], &aup->mac->multi_hash_high);
		ग_लिखोl(mc_filter[0], &aup->mac->multi_hash_low);
		reg &= ~MAC_PROMISCUOUS;
		reg |= MAC_HASH_MODE;
	पूर्ण
	ग_लिखोl(reg, &aup->mac->control);
पूर्ण

अटल स्थिर काष्ठा net_device_ops au1000_netdev_ops = अणु
	.nकरो_खोलो		= au1000_खोलो,
	.nकरो_stop		= au1000_बंद,
	.nकरो_start_xmit		= au1000_tx,
	.nकरो_set_rx_mode	= au1000_multicast_list,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_tx_समयout		= au1000_tx_समयout,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक au1000_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा au1000_निजी *aup = शून्य;
	काष्ठा au1000_eth_platक्रमm_data *pd;
	काष्ठा net_device *dev = शून्य;
	काष्ठा db_dest *pDB, *pDBमुक्त;
	पूर्णांक irq, i, err = 0;
	काष्ठा resource *base, *macen, *macdma;

	base = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!base) अणु
		dev_err(&pdev->dev, "failed to retrieve base register\n");
		err = -ENODEV;
		जाओ out;
	पूर्ण

	macen = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!macen) अणु
		dev_err(&pdev->dev, "failed to retrieve MAC Enable register\n");
		err = -ENODEV;
		जाओ out;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	macdma = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	अगर (!macdma) अणु
		dev_err(&pdev->dev, "failed to retrieve MACDMA registers\n");
		err = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!request_mem_region(base->start, resource_size(base),
							pdev->name)) अणु
		dev_err(&pdev->dev, "failed to request memory region for base registers\n");
		err = -ENXIO;
		जाओ out;
	पूर्ण

	अगर (!request_mem_region(macen->start, resource_size(macen),
							pdev->name)) अणु
		dev_err(&pdev->dev, "failed to request memory region for MAC enable register\n");
		err = -ENXIO;
		जाओ err_request;
	पूर्ण

	अगर (!request_mem_region(macdma->start, resource_size(macdma),
							pdev->name)) अणु
		dev_err(&pdev->dev, "failed to request MACDMA memory region\n");
		err = -ENXIO;
		जाओ err_macdma;
	पूर्ण

	dev = alloc_etherdev(माप(काष्ठा au1000_निजी));
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	SET_NETDEV_DEV(dev, &pdev->dev);
	platक्रमm_set_drvdata(pdev, dev);
	aup = netdev_priv(dev);

	spin_lock_init(&aup->lock);
	aup->msg_enable = (au1000_debug < 4 ?
				AU1000_DEF_MSG_ENABLE : au1000_debug);

	/* Allocate the data buffers
	 * Snooping works fine with eth on all au1xxx
	 */
	aup->vaddr = (u32)dma_alloc_coherent(&pdev->dev, MAX_BUF_SIZE *
					  (NUM_TX_BUFFS + NUM_RX_BUFFS),
					  &aup->dma_addr, 0);
	अगर (!aup->vaddr) अणु
		dev_err(&pdev->dev, "failed to allocate data buffers\n");
		err = -ENOMEM;
		जाओ err_vaddr;
	पूर्ण

	/* aup->mac is the base address of the MAC's रेजिस्टरs */
	aup->mac = (काष्ठा mac_reg *)
			ioremap(base->start, resource_size(base));
	अगर (!aup->mac) अणु
		dev_err(&pdev->dev, "failed to ioremap MAC registers\n");
		err = -ENXIO;
		जाओ err_remap1;
	पूर्ण

	/* Setup some variables क्रम quick रेजिस्टर address access */
	aup->enable = (u32 *)ioremap(macen->start,
						resource_size(macen));
	अगर (!aup->enable) अणु
		dev_err(&pdev->dev, "failed to ioremap MAC enable register\n");
		err = -ENXIO;
		जाओ err_remap2;
	पूर्ण
	aup->mac_id = pdev->id;

	aup->macdma = ioremap(macdma->start, resource_size(macdma));
	अगर (!aup->macdma) अणु
		dev_err(&pdev->dev, "failed to ioremap MACDMA registers\n");
		err = -ENXIO;
		जाओ err_remap3;
	पूर्ण

	au1000_setup_hw_rings(aup, aup->macdma);

	ग_लिखोl(0, aup->enable);
	aup->mac_enabled = 0;

	pd = dev_get_platdata(&pdev->dev);
	अगर (!pd) अणु
		dev_info(&pdev->dev, "no platform_data passed,"
					" PHY search on MAC0\n");
		aup->phy1_search_mac0 = 1;
	पूर्ण अन्यथा अणु
		अगर (is_valid_ether_addr(pd->mac)) अणु
			स_नकल(dev->dev_addr, pd->mac, ETH_ALEN);
		पूर्ण अन्यथा अणु
			/* Set a अक्रमom MAC since no valid provided by platक्रमm_data. */
			eth_hw_addr_अक्रमom(dev);
		पूर्ण

		aup->phy_अटल_config = pd->phy_अटल_config;
		aup->phy_search_highest_addr = pd->phy_search_highest_addr;
		aup->phy1_search_mac0 = pd->phy1_search_mac0;
		aup->phy_addr = pd->phy_addr;
		aup->phy_busid = pd->phy_busid;
		aup->phy_irq = pd->phy_irq;
	पूर्ण

	अगर (aup->phy_busid > 0) अणु
		dev_err(&pdev->dev, "MAC0-associated PHY attached 2nd MACs MII bus not supported yet\n");
		err = -ENODEV;
		जाओ err_mdiobus_alloc;
	पूर्ण

	aup->mii_bus = mdiobus_alloc();
	अगर (aup->mii_bus == शून्य) अणु
		dev_err(&pdev->dev, "failed to allocate mdiobus structure\n");
		err = -ENOMEM;
		जाओ err_mdiobus_alloc;
	पूर्ण

	aup->mii_bus->priv = dev;
	aup->mii_bus->पढ़ो = au1000_mdiobus_पढ़ो;
	aup->mii_bus->ग_लिखो = au1000_mdiobus_ग_लिखो;
	aup->mii_bus->reset = au1000_mdiobus_reset;
	aup->mii_bus->name = "au1000_eth_mii";
	snम_लिखो(aup->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		pdev->name, aup->mac_id);

	/* अगर known, set corresponding PHY IRQs */
	अगर (aup->phy_अटल_config)
		अगर (aup->phy_irq && aup->phy_busid == aup->mac_id)
			aup->mii_bus->irq[aup->phy_addr] = aup->phy_irq;

	err = mdiobus_रेजिस्टर(aup->mii_bus);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register MDIO bus\n");
		जाओ err_mdiobus_reg;
	पूर्ण

	err = au1000_mii_probe(dev);
	अगर (err != 0)
		जाओ err_out;

	pDBमुक्त = शून्य;
	/* setup the data buffer descriptors and attach a buffer to each one */
	pDB = aup->db;
	क्रम (i = 0; i < (NUM_TX_BUFFS+NUM_RX_BUFFS); i++) अणु
		pDB->pnext = pDBमुक्त;
		pDBमुक्त = pDB;
		pDB->vaddr = (u32 *)((अचिन्हित)aup->vaddr + MAX_BUF_SIZE*i);
		pDB->dma_addr = (dma_addr_t)virt_to_bus(pDB->vaddr);
		pDB++;
	पूर्ण
	aup->pDBमुक्त = pDBमुक्त;

	err = -ENODEV;
	क्रम (i = 0; i < NUM_RX_DMA; i++) अणु
		pDB = au1000_GetFreeDB(aup);
		अगर (!pDB)
			जाओ err_out;

		aup->rx_dma_ring[i]->buff_stat = (अचिन्हित)pDB->dma_addr;
		aup->rx_db_inuse[i] = pDB;
	पूर्ण

	क्रम (i = 0; i < NUM_TX_DMA; i++) अणु
		pDB = au1000_GetFreeDB(aup);
		अगर (!pDB)
			जाओ err_out;

		aup->tx_dma_ring[i]->buff_stat = (अचिन्हित)pDB->dma_addr;
		aup->tx_dma_ring[i]->len = 0;
		aup->tx_db_inuse[i] = pDB;
	पूर्ण

	dev->base_addr = base->start;
	dev->irq = irq;
	dev->netdev_ops = &au1000_netdev_ops;
	dev->ethtool_ops = &au1000_ethtool_ops;
	dev->watchकरोg_समयo = ETH_TX_TIMEOUT;

	/*
	 * The boot code uses the ethernet controller, so reset it to start
	 * fresh.  au1000_init() expects that the device is in reset state.
	 */
	au1000_reset_mac(dev);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		netdev_err(dev, "Cannot register net device, aborting.\n");
		जाओ err_out;
	पूर्ण

	netdev_info(dev, "Au1xx0 Ethernet found at 0x%lx, irq %d\n",
			(अचिन्हित दीर्घ)base->start, irq);

	वापस 0;

err_out:
	अगर (aup->mii_bus != शून्य)
		mdiobus_unरेजिस्टर(aup->mii_bus);

	/* here we should have a valid dev plus aup-> रेजिस्टर addresses
	 * so we can reset the mac properly.
	 */
	au1000_reset_mac(dev);

	क्रम (i = 0; i < NUM_RX_DMA; i++) अणु
		अगर (aup->rx_db_inuse[i])
			au1000_ReleaseDB(aup, aup->rx_db_inuse[i]);
	पूर्ण
	क्रम (i = 0; i < NUM_TX_DMA; i++) अणु
		अगर (aup->tx_db_inuse[i])
			au1000_ReleaseDB(aup, aup->tx_db_inuse[i]);
	पूर्ण
err_mdiobus_reg:
	mdiobus_मुक्त(aup->mii_bus);
err_mdiobus_alloc:
	iounmap(aup->macdma);
err_remap3:
	iounmap(aup->enable);
err_remap2:
	iounmap(aup->mac);
err_remap1:
	dma_मुक्त_coherent(&pdev->dev, MAX_BUF_SIZE * (NUM_TX_BUFFS + NUM_RX_BUFFS),
			(व्योम *)aup->vaddr, aup->dma_addr);
err_vaddr:
	मुक्त_netdev(dev);
err_alloc:
	release_mem_region(macdma->start, resource_size(macdma));
err_macdma:
	release_mem_region(macen->start, resource_size(macen));
err_request:
	release_mem_region(base->start, resource_size(base));
out:
	वापस err;
पूर्ण

अटल पूर्णांक au1000_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा au1000_निजी *aup = netdev_priv(dev);
	पूर्णांक i;
	काष्ठा resource *base, *macen;

	unरेजिस्टर_netdev(dev);
	mdiobus_unरेजिस्टर(aup->mii_bus);
	mdiobus_मुक्त(aup->mii_bus);

	क्रम (i = 0; i < NUM_RX_DMA; i++)
		अगर (aup->rx_db_inuse[i])
			au1000_ReleaseDB(aup, aup->rx_db_inuse[i]);

	क्रम (i = 0; i < NUM_TX_DMA; i++)
		अगर (aup->tx_db_inuse[i])
			au1000_ReleaseDB(aup, aup->tx_db_inuse[i]);

	dma_मुक्त_coherent(&pdev->dev, MAX_BUF_SIZE * (NUM_TX_BUFFS + NUM_RX_BUFFS),
			(व्योम *)aup->vaddr, aup->dma_addr);

	iounmap(aup->macdma);
	iounmap(aup->mac);
	iounmap(aup->enable);

	base = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	release_mem_region(base->start, resource_size(base));

	base = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(base->start, resource_size(base));

	macen = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	release_mem_region(macen->start, resource_size(macen));

	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver au1000_eth_driver = अणु
	.probe  = au1000_probe,
	.हटाओ = au1000_हटाओ,
	.driver = अणु
		.name   = "au1000-eth",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(au1000_eth_driver);

MODULE_ALIAS("platform:au1000-eth");
