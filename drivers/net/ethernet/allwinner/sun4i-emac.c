<शैली गुरु>
/*
 * Allwinner EMAC Fast Ethernet driver क्रम Linux.
 *
 * Copyright 2012-2013 Stefan Roese <sr@denx.de>
 * Copyright 2013 Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 *
 * Based on the Linux driver provided by Allwinner:
 * Copyright (C) 1997  Sten Wang
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy.h>
#समावेश <linux/soc/sunxi/sunxi_sram.h>

#समावेश "sun4i-emac.h"

#घोषणा DRV_NAME		"sun4i-emac"

#घोषणा EMAC_MAX_FRAME_LEN	0x0600

#घोषणा EMAC_DEFAULT_MSG_ENABLE 0x0000
अटल पूर्णांक debug = -1;     /* शेषs above */;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "debug message flags");

/* Transmit समयout, शेष 5 seconds. */
अटल पूर्णांक watchकरोg = 5000;
module_param(watchकरोg, पूर्णांक, 0400);
MODULE_PARM_DESC(watchकरोg, "transmit timeout in milliseconds");

/* EMAC रेजिस्टर address locking.
 *
 * The EMAC uses an address रेजिस्टर to control where data written
 * to the data रेजिस्टर goes. This means that the address रेजिस्टर
 * must be preserved over पूर्णांकerrupts or similar calls.
 *
 * During पूर्णांकerrupt and other critical calls, a spinlock is used to
 * protect the प्रणाली, but the calls themselves save the address
 * in the address रेजिस्टर in हाल they are पूर्णांकerrupting another
 * access to the device.
 *
 * For general accesses a lock is provided so that calls which are
 * allowed to sleep are serialised so that the address रेजिस्टर करोes
 * not need to be saved. This lock also serves to serialise access
 * to the EEPROM and PHY access रेजिस्टरs which are shared between
 * these two devices.
 */

/* The driver supports the original EMACE, and now the two newer
 * devices, EMACA and EMACB.
 */

काष्ठा emac_board_info अणु
	काष्ठा clk		*clk;
	काष्ठा device		*dev;
	काष्ठा platक्रमm_device	*pdev;
	spinlock_t		lock;
	व्योम __iomem		*membase;
	u32			msg_enable;
	काष्ठा net_device	*ndev;
	काष्ठा sk_buff		*skb_last;
	u16			tx_fअगरo_stat;

	पूर्णांक			emacrx_completed_flag;

	काष्ठा device_node	*phy_node;
	अचिन्हित पूर्णांक		link;
	अचिन्हित पूर्णांक		speed;
	अचिन्हित पूर्णांक		duplex;

	phy_पूर्णांकerface_t		phy_पूर्णांकerface;
पूर्ण;

अटल व्योम emac_update_speed(काष्ठा net_device *dev)
अणु
	काष्ठा emac_board_info *db = netdev_priv(dev);
	अचिन्हित पूर्णांक reg_val;

	/* set EMAC SPEED, depend on PHY  */
	reg_val = पढ़ोl(db->membase + EMAC_MAC_SUPP_REG);
	reg_val &= ~(0x1 << 8);
	अगर (db->speed == SPEED_100)
		reg_val |= 1 << 8;
	ग_लिखोl(reg_val, db->membase + EMAC_MAC_SUPP_REG);
पूर्ण

अटल व्योम emac_update_duplex(काष्ठा net_device *dev)
अणु
	काष्ठा emac_board_info *db = netdev_priv(dev);
	अचिन्हित पूर्णांक reg_val;

	/* set duplex depend on phy */
	reg_val = पढ़ोl(db->membase + EMAC_MAC_CTL1_REG);
	reg_val &= ~EMAC_MAC_CTL1_DUPLEX_EN;
	अगर (db->duplex)
		reg_val |= EMAC_MAC_CTL1_DUPLEX_EN;
	ग_लिखोl(reg_val, db->membase + EMAC_MAC_CTL1_REG);
पूर्ण

अटल व्योम emac_handle_link_change(काष्ठा net_device *dev)
अणु
	काष्ठा emac_board_info *db = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	अचिन्हित दीर्घ flags;
	पूर्णांक status_change = 0;

	अगर (phydev->link) अणु
		अगर (db->speed != phydev->speed) अणु
			spin_lock_irqsave(&db->lock, flags);
			db->speed = phydev->speed;
			emac_update_speed(dev);
			spin_unlock_irqrestore(&db->lock, flags);
			status_change = 1;
		पूर्ण

		अगर (db->duplex != phydev->duplex) अणु
			spin_lock_irqsave(&db->lock, flags);
			db->duplex = phydev->duplex;
			emac_update_duplex(dev);
			spin_unlock_irqrestore(&db->lock, flags);
			status_change = 1;
		पूर्ण
	पूर्ण

	अगर (phydev->link != db->link) अणु
		अगर (!phydev->link) अणु
			db->speed = 0;
			db->duplex = -1;
		पूर्ण
		db->link = phydev->link;

		status_change = 1;
	पूर्ण

	अगर (status_change)
		phy_prपूर्णांक_status(phydev);
पूर्ण

अटल पूर्णांक emac_mdio_probe(काष्ठा net_device *dev)
अणु
	काष्ठा emac_board_info *db = netdev_priv(dev);
	काष्ठा phy_device *phydev;

	/* to-करो: PHY पूर्णांकerrupts are currently not supported */

	/* attach the mac to the phy */
	phydev = of_phy_connect(db->ndev, db->phy_node,
				&emac_handle_link_change, 0,
				db->phy_पूर्णांकerface);
	अगर (!phydev) अणु
		netdev_err(db->ndev, "could not find the PHY\n");
		वापस -ENODEV;
	पूर्ण

	/* mask with MAC supported features */
	phy_set_max_speed(phydev, SPEED_100);

	db->link = 0;
	db->speed = 0;
	db->duplex = -1;

	वापस 0;
पूर्ण

अटल व्योम emac_mdio_हटाओ(काष्ठा net_device *dev)
अणु
	phy_disconnect(dev->phydev);
पूर्ण

अटल व्योम emac_reset(काष्ठा emac_board_info *db)
अणु
	dev_dbg(db->dev, "resetting device\n");

	/* RESET device */
	ग_लिखोl(0, db->membase + EMAC_CTL_REG);
	udelay(200);
	ग_लिखोl(EMAC_CTL_RESET, db->membase + EMAC_CTL_REG);
	udelay(200);
पूर्ण

अटल व्योम emac_outblk_32bit(व्योम __iomem *reg, व्योम *data, पूर्णांक count)
अणु
	ग_लिखोsl(reg, data, round_up(count, 4) / 4);
पूर्ण

अटल व्योम emac_inblk_32bit(व्योम __iomem *reg, व्योम *data, पूर्णांक count)
अणु
	पढ़ोsl(reg, data, round_up(count, 4) / 4);
पूर्ण

/* ethtool ops */
अटल व्योम emac_get_drvinfo(काष्ठा net_device *dev,
			      काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, dev_name(&dev->dev), माप(info->bus_info));
पूर्ण

अटल u32 emac_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा emac_board_info *db = netdev_priv(dev);

	वापस db->msg_enable;
पूर्ण

अटल व्योम emac_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा emac_board_info *db = netdev_priv(dev);

	db->msg_enable = value;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops emac_ethtool_ops = अणु
	.get_drvinfo	= emac_get_drvinfo,
	.get_link	= ethtool_op_get_link,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
	.get_msglevel	= emac_get_msglevel,
	.set_msglevel	= emac_set_msglevel,
पूर्ण;

अटल अचिन्हित पूर्णांक emac_setup(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_board_info *db = netdev_priv(ndev);
	अचिन्हित पूर्णांक reg_val;

	/* set up TX */
	reg_val = पढ़ोl(db->membase + EMAC_TX_MODE_REG);

	ग_लिखोl(reg_val | EMAC_TX_MODE_ABORTED_FRAME_EN,
		db->membase + EMAC_TX_MODE_REG);

	/* set MAC */
	/* set MAC CTL0 */
	reg_val = पढ़ोl(db->membase + EMAC_MAC_CTL0_REG);
	ग_लिखोl(reg_val | EMAC_MAC_CTL0_RX_FLOW_CTL_EN |
		EMAC_MAC_CTL0_TX_FLOW_CTL_EN,
		db->membase + EMAC_MAC_CTL0_REG);

	/* set MAC CTL1 */
	reg_val = पढ़ोl(db->membase + EMAC_MAC_CTL1_REG);
	reg_val |= EMAC_MAC_CTL1_LEN_CHECK_EN;
	reg_val |= EMAC_MAC_CTL1_CRC_EN;
	reg_val |= EMAC_MAC_CTL1_PAD_EN;
	ग_लिखोl(reg_val, db->membase + EMAC_MAC_CTL1_REG);

	/* set up IPGT */
	ग_लिखोl(EMAC_MAC_IPGT_FULL_DUPLEX, db->membase + EMAC_MAC_IPGT_REG);

	/* set up IPGR */
	ग_लिखोl((EMAC_MAC_IPGR_IPG1 << 8) | EMAC_MAC_IPGR_IPG2,
		db->membase + EMAC_MAC_IPGR_REG);

	/* set up Collison winकरोw */
	ग_लिखोl((EMAC_MAC_CLRT_COLLISION_WINDOW << 8) | EMAC_MAC_CLRT_RM,
		db->membase + EMAC_MAC_CLRT_REG);

	/* set up Max Frame Length */
	ग_लिखोl(EMAC_MAX_FRAME_LEN,
		db->membase + EMAC_MAC_MAXF_REG);

	वापस 0;
पूर्ण

अटल व्योम emac_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_board_info *db = netdev_priv(ndev);
	अचिन्हित पूर्णांक reg_val;

	/* set up RX */
	reg_val = पढ़ोl(db->membase + EMAC_RX_CTL_REG);

	अगर (ndev->flags & IFF_PROMISC)
		reg_val |= EMAC_RX_CTL_PASS_ALL_EN;
	अन्यथा
		reg_val &= ~EMAC_RX_CTL_PASS_ALL_EN;

	ग_लिखोl(reg_val | EMAC_RX_CTL_PASS_LEN_OOR_EN |
		EMAC_RX_CTL_ACCEPT_UNICAST_EN | EMAC_RX_CTL_DA_FILTER_EN |
		EMAC_RX_CTL_ACCEPT_MULTICAST_EN |
		EMAC_RX_CTL_ACCEPT_BROADCAST_EN,
		db->membase + EMAC_RX_CTL_REG);
पूर्ण

अटल अचिन्हित पूर्णांक emac_घातerup(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_board_info *db = netdev_priv(ndev);
	अचिन्हित पूर्णांक reg_val;

	/* initial EMAC */
	/* flush RX FIFO */
	reg_val = पढ़ोl(db->membase + EMAC_RX_CTL_REG);
	reg_val |= 0x8;
	ग_लिखोl(reg_val, db->membase + EMAC_RX_CTL_REG);
	udelay(1);

	/* initial MAC */
	/* soft reset MAC */
	reg_val = पढ़ोl(db->membase + EMAC_MAC_CTL0_REG);
	reg_val &= ~EMAC_MAC_CTL0_SOFT_RESET;
	ग_लिखोl(reg_val, db->membase + EMAC_MAC_CTL0_REG);

	/* set MII घड़ी */
	reg_val = पढ़ोl(db->membase + EMAC_MAC_MCFG_REG);
	reg_val &= (~(0xf << 2));
	reg_val |= (0xD << 2);
	ग_लिखोl(reg_val, db->membase + EMAC_MAC_MCFG_REG);

	/* clear RX counter */
	ग_लिखोl(0x0, db->membase + EMAC_RX_FBC_REG);

	/* disable all पूर्णांकerrupt and clear पूर्णांकerrupt status */
	ग_लिखोl(0, db->membase + EMAC_INT_CTL_REG);
	reg_val = पढ़ोl(db->membase + EMAC_INT_STA_REG);
	ग_लिखोl(reg_val, db->membase + EMAC_INT_STA_REG);

	udelay(1);

	/* set up EMAC */
	emac_setup(ndev);

	/* set mac_address to chip */
	ग_लिखोl(ndev->dev_addr[0] << 16 | ndev->dev_addr[1] << 8 | ndev->
	       dev_addr[2], db->membase + EMAC_MAC_A1_REG);
	ग_लिखोl(ndev->dev_addr[3] << 16 | ndev->dev_addr[4] << 8 | ndev->
	       dev_addr[5], db->membase + EMAC_MAC_A0_REG);

	mdelay(1);

	वापस 0;
पूर्ण

अटल पूर्णांक emac_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा emac_board_info *db = netdev_priv(dev);

	अगर (netअगर_running(dev))
		वापस -EBUSY;

	स_नकल(dev->dev_addr, addr->sa_data, ETH_ALEN);

	ग_लिखोl(dev->dev_addr[0] << 16 | dev->dev_addr[1] << 8 | dev->
	       dev_addr[2], db->membase + EMAC_MAC_A1_REG);
	ग_लिखोl(dev->dev_addr[3] << 16 | dev->dev_addr[4] << 8 | dev->
	       dev_addr[5], db->membase + EMAC_MAC_A0_REG);

	वापस 0;
पूर्ण

/* Initialize emac board */
अटल व्योम emac_init_device(काष्ठा net_device *dev)
अणु
	काष्ठा emac_board_info *db = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक reg_val;

	spin_lock_irqsave(&db->lock, flags);

	emac_update_speed(dev);
	emac_update_duplex(dev);

	/* enable RX/TX */
	reg_val = पढ़ोl(db->membase + EMAC_CTL_REG);
	ग_लिखोl(reg_val | EMAC_CTL_RESET | EMAC_CTL_TX_EN | EMAC_CTL_RX_EN,
		db->membase + EMAC_CTL_REG);

	/* enable RX/TX0/RX Hlevel पूर्णांकerrup */
	reg_val = पढ़ोl(db->membase + EMAC_INT_CTL_REG);
	reg_val |= (0xf << 0) | (0x01 << 8);
	ग_लिखोl(reg_val, db->membase + EMAC_INT_CTL_REG);

	spin_unlock_irqrestore(&db->lock, flags);
पूर्ण

/* Our watchकरोg समयd out. Called by the networking layer */
अटल व्योम emac_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा emac_board_info *db = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	अगर (netअगर_msg_समयr(db))
		dev_err(db->dev, "tx time out.\n");

	/* Save previous रेजिस्टर address */
	spin_lock_irqsave(&db->lock, flags);

	netअगर_stop_queue(dev);
	emac_reset(db);
	emac_init_device(dev);
	/* We can accept TX packets again */
	netअगर_trans_update(dev);
	netअगर_wake_queue(dev);

	/* Restore previous रेजिस्टर address */
	spin_unlock_irqrestore(&db->lock, flags);
पूर्ण

/* Hardware start transmission.
 * Send a packet to media from the upper layer.
 */
अटल netdev_tx_t emac_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा emac_board_info *db = netdev_priv(dev);
	अचिन्हित दीर्घ channel;
	अचिन्हित दीर्घ flags;

	channel = db->tx_fअगरo_stat & 3;
	अगर (channel == 3)
		वापस NETDEV_TX_BUSY;

	channel = (channel == 1 ? 1 : 0);

	spin_lock_irqsave(&db->lock, flags);

	ग_लिखोl(channel, db->membase + EMAC_TX_INS_REG);

	emac_outblk_32bit(db->membase + EMAC_TX_IO_DATA_REG,
			skb->data, skb->len);
	dev->stats.tx_bytes += skb->len;

	db->tx_fअगरo_stat |= 1 << channel;
	/* TX control: First packet immediately send, second packet queue */
	अगर (channel == 0) अणु
		/* set TX len */
		ग_लिखोl(skb->len, db->membase + EMAC_TX_PL0_REG);
		/* start translate from fअगरo to phy */
		ग_लिखोl(पढ़ोl(db->membase + EMAC_TX_CTL0_REG) | 1,
		       db->membase + EMAC_TX_CTL0_REG);

		/* save the समय stamp */
		netअगर_trans_update(dev);
	पूर्ण अन्यथा अगर (channel == 1) अणु
		/* set TX len */
		ग_लिखोl(skb->len, db->membase + EMAC_TX_PL1_REG);
		/* start translate from fअगरo to phy */
		ग_लिखोl(पढ़ोl(db->membase + EMAC_TX_CTL1_REG) | 1,
		       db->membase + EMAC_TX_CTL1_REG);

		/* save the समय stamp */
		netअगर_trans_update(dev);
	पूर्ण

	अगर ((db->tx_fअगरo_stat & 3) == 3) अणु
		/* Second packet */
		netअगर_stop_queue(dev);
	पूर्ण

	spin_unlock_irqrestore(&db->lock, flags);

	/* मुक्त this SKB */
	dev_consume_skb_any(skb);

	वापस NETDEV_TX_OK;
पूर्ण

/* EMAC पूर्णांकerrupt handler
 * receive the packet to upper layer, मुक्त the transmitted packet
 */
अटल व्योम emac_tx_करोne(काष्ठा net_device *dev, काष्ठा emac_board_info *db,
			  अचिन्हित पूर्णांक tx_status)
अणु
	/* One packet sent complete */
	db->tx_fअगरo_stat &= ~(tx_status & 3);
	अगर (3 == (tx_status & 3))
		dev->stats.tx_packets += 2;
	अन्यथा
		dev->stats.tx_packets++;

	अगर (netअगर_msg_tx_करोne(db))
		dev_dbg(db->dev, "tx done, NSR %02x\n", tx_status);

	netअगर_wake_queue(dev);
पूर्ण

/* Received a packet and pass to upper layer
 */
अटल व्योम emac_rx(काष्ठा net_device *dev)
अणु
	काष्ठा emac_board_info *db = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	u8 *rdptr;
	bool good_packet;
	अटल पूर्णांक rxlen_last;
	अचिन्हित पूर्णांक reg_val;
	u32 rxhdr, rxstatus, rxcount, rxlen;

	/* Check packet पढ़ोy or not */
	जबतक (1) अणु
		/* race warning: the first packet might arrive with
		 * the पूर्णांकerrupts disabled, but the second will fix
		 * it
		 */
		rxcount = पढ़ोl(db->membase + EMAC_RX_FBC_REG);

		अगर (netअगर_msg_rx_status(db))
			dev_dbg(db->dev, "RXCount: %x\n", rxcount);

		अगर ((db->skb_last != शून्य) && (rxlen_last > 0)) अणु
			dev->stats.rx_bytes += rxlen_last;

			/* Pass to upper layer */
			db->skb_last->protocol = eth_type_trans(db->skb_last,
								dev);
			netअगर_rx(db->skb_last);
			dev->stats.rx_packets++;
			db->skb_last = शून्य;
			rxlen_last = 0;

			reg_val = पढ़ोl(db->membase + EMAC_RX_CTL_REG);
			reg_val &= ~EMAC_RX_CTL_DMA_EN;
			ग_लिखोl(reg_val, db->membase + EMAC_RX_CTL_REG);
		पूर्ण

		अगर (!rxcount) अणु
			db->emacrx_completed_flag = 1;
			reg_val = पढ़ोl(db->membase + EMAC_INT_CTL_REG);
			reg_val |= (0xf << 0) | (0x01 << 8);
			ग_लिखोl(reg_val, db->membase + EMAC_INT_CTL_REG);

			/* had one stuck? */
			rxcount = पढ़ोl(db->membase + EMAC_RX_FBC_REG);
			अगर (!rxcount)
				वापस;
		पूर्ण

		reg_val = पढ़ोl(db->membase + EMAC_RX_IO_DATA_REG);
		अगर (netअगर_msg_rx_status(db))
			dev_dbg(db->dev, "receive header: %x\n", reg_val);
		अगर (reg_val != EMAC_UNDOCUMENTED_MAGIC) अणु
			/* disable RX */
			reg_val = पढ़ोl(db->membase + EMAC_CTL_REG);
			ग_लिखोl(reg_val & ~EMAC_CTL_RX_EN,
			       db->membase + EMAC_CTL_REG);

			/* Flush RX FIFO */
			reg_val = पढ़ोl(db->membase + EMAC_RX_CTL_REG);
			ग_लिखोl(reg_val | (1 << 3),
			       db->membase + EMAC_RX_CTL_REG);

			करो अणु
				reg_val = पढ़ोl(db->membase + EMAC_RX_CTL_REG);
			पूर्ण जबतक (reg_val & (1 << 3));

			/* enable RX */
			reg_val = पढ़ोl(db->membase + EMAC_CTL_REG);
			ग_लिखोl(reg_val | EMAC_CTL_RX_EN,
			       db->membase + EMAC_CTL_REG);
			reg_val = पढ़ोl(db->membase + EMAC_INT_CTL_REG);
			reg_val |= (0xf << 0) | (0x01 << 8);
			ग_लिखोl(reg_val, db->membase + EMAC_INT_CTL_REG);

			db->emacrx_completed_flag = 1;

			वापस;
		पूर्ण

		/* A packet पढ़ोy now  & Get status/length */
		good_packet = true;

		rxhdr = पढ़ोl(db->membase + EMAC_RX_IO_DATA_REG);

		अगर (netअगर_msg_rx_status(db))
			dev_dbg(db->dev, "rxhdr: %x\n", *((पूर्णांक *)(&rxhdr)));

		rxlen = EMAC_RX_IO_DATA_LEN(rxhdr);
		rxstatus = EMAC_RX_IO_DATA_STATUS(rxhdr);

		अगर (netअगर_msg_rx_status(db))
			dev_dbg(db->dev, "RX: status %02x, length %04x\n",
				rxstatus, rxlen);

		/* Packet Status check */
		अगर (rxlen < 0x40) अणु
			good_packet = false;
			अगर (netअगर_msg_rx_err(db))
				dev_dbg(db->dev, "RX: Bad Packet (runt)\n");
		पूर्ण

		अगर (unlikely(!(rxstatus & EMAC_RX_IO_DATA_STATUS_OK))) अणु
			good_packet = false;

			अगर (rxstatus & EMAC_RX_IO_DATA_STATUS_CRC_ERR) अणु
				अगर (netअगर_msg_rx_err(db))
					dev_dbg(db->dev, "crc error\n");
				dev->stats.rx_crc_errors++;
			पूर्ण

			अगर (rxstatus & EMAC_RX_IO_DATA_STATUS_LEN_ERR) अणु
				अगर (netअगर_msg_rx_err(db))
					dev_dbg(db->dev, "length error\n");
				dev->stats.rx_length_errors++;
			पूर्ण
		पूर्ण

		/* Move data from EMAC */
		अगर (good_packet) अणु
			skb = netdev_alloc_skb(dev, rxlen + 4);
			अगर (!skb)
				जारी;
			skb_reserve(skb, 2);
			rdptr = skb_put(skb, rxlen - 4);

			/* Read received packet from RX SRAM */
			अगर (netअगर_msg_rx_status(db))
				dev_dbg(db->dev, "RxLen %x\n", rxlen);

			emac_inblk_32bit(db->membase + EMAC_RX_IO_DATA_REG,
					rdptr, rxlen);
			dev->stats.rx_bytes += rxlen;

			/* Pass to upper layer */
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_rx(skb);
			dev->stats.rx_packets++;
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t emac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा emac_board_info *db = netdev_priv(dev);
	पूर्णांक पूर्णांक_status;
	अचिन्हित पूर्णांक reg_val;

	/* A real पूर्णांकerrupt coming */

	spin_lock(&db->lock);

	/* Disable all पूर्णांकerrupts */
	ग_लिखोl(0, db->membase + EMAC_INT_CTL_REG);

	/* Got EMAC पूर्णांकerrupt status */
	/* Got ISR */
	पूर्णांक_status = पढ़ोl(db->membase + EMAC_INT_STA_REG);
	/* Clear ISR status */
	ग_लिखोl(पूर्णांक_status, db->membase + EMAC_INT_STA_REG);

	अगर (netअगर_msg_पूर्णांकr(db))
		dev_dbg(db->dev, "emac interrupt %02x\n", पूर्णांक_status);

	/* Received the coming packet */
	अगर ((पूर्णांक_status & 0x100) && (db->emacrx_completed_flag == 1)) अणु
		/* carrier lost */
		db->emacrx_completed_flag = 0;
		emac_rx(dev);
	पूर्ण

	/* Transmit Interrupt check */
	अगर (पूर्णांक_status & (0x01 | 0x02))
		emac_tx_करोne(dev, db, पूर्णांक_status);

	अगर (पूर्णांक_status & (0x04 | 0x08))
		netdev_info(dev, " ab : %x\n", पूर्णांक_status);

	/* Re-enable पूर्णांकerrupt mask */
	अगर (db->emacrx_completed_flag == 1) अणु
		reg_val = पढ़ोl(db->membase + EMAC_INT_CTL_REG);
		reg_val |= (0xf << 0) | (0x01 << 8);
		ग_लिखोl(reg_val, db->membase + EMAC_INT_CTL_REG);
	पूर्ण
	spin_unlock(&db->lock);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Used by netconsole
 */
अटल व्योम emac_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	emac_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

/*  Open the पूर्णांकerface.
 *  The पूर्णांकerface is खोलोed whenever "ifconfig" actives it.
 */
अटल पूर्णांक emac_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा emac_board_info *db = netdev_priv(dev);
	पूर्णांक ret;

	अगर (netअगर_msg_अगरup(db))
		dev_dbg(db->dev, "enabling %s\n", dev->name);

	अगर (request_irq(dev->irq, &emac_पूर्णांकerrupt, 0, dev->name, dev))
		वापस -EAGAIN;

	/* Initialize EMAC board */
	emac_reset(db);
	emac_init_device(dev);

	ret = emac_mdio_probe(dev);
	अगर (ret < 0) अणु
		मुक्त_irq(dev->irq, dev);
		netdev_err(dev, "cannot probe MDIO bus\n");
		वापस ret;
	पूर्ण

	phy_start(dev->phydev);
	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल व्योम emac_shutकरोwn(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक reg_val;
	काष्ठा emac_board_info *db = netdev_priv(dev);

	/* Disable all पूर्णांकerrupt */
	ग_लिखोl(0, db->membase + EMAC_INT_CTL_REG);

	/* clear पूर्णांकerrupt status */
	reg_val = पढ़ोl(db->membase + EMAC_INT_STA_REG);
	ग_लिखोl(reg_val, db->membase + EMAC_INT_STA_REG);

	/* Disable RX/TX */
	reg_val = पढ़ोl(db->membase + EMAC_CTL_REG);
	reg_val &= ~(EMAC_CTL_TX_EN | EMAC_CTL_RX_EN | EMAC_CTL_RESET);
	ग_लिखोl(reg_val, db->membase + EMAC_CTL_REG);
पूर्ण

/* Stop the पूर्णांकerface.
 * The पूर्णांकerface is stopped when it is brought.
 */
अटल पूर्णांक emac_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_board_info *db = netdev_priv(ndev);

	अगर (netअगर_msg_अगरकरोwn(db))
		dev_dbg(db->dev, "shutting down %s\n", ndev->name);

	netअगर_stop_queue(ndev);
	netअगर_carrier_off(ndev);

	phy_stop(ndev->phydev);

	emac_mdio_हटाओ(ndev);

	emac_shutकरोwn(ndev);

	मुक्त_irq(ndev->irq, ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops emac_netdev_ops = अणु
	.nकरो_खोलो		= emac_खोलो,
	.nकरो_stop		= emac_stop,
	.nकरो_start_xmit		= emac_start_xmit,
	.nकरो_tx_समयout		= emac_समयout,
	.nकरो_set_rx_mode	= emac_set_rx_mode,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= emac_set_mac_address,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= emac_poll_controller,
#पूर्ण_अगर
पूर्ण;

/* Search EMAC board, allocate space and रेजिस्टर it
 */
अटल पूर्णांक emac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा emac_board_info *db;
	काष्ठा net_device *ndev;
	पूर्णांक ret = 0;

	ndev = alloc_etherdev(माप(काष्ठा emac_board_info));
	अगर (!ndev) अणु
		dev_err(&pdev->dev, "could not allocate device.\n");
		वापस -ENOMEM;
	पूर्ण

	SET_NETDEV_DEV(ndev, &pdev->dev);

	db = netdev_priv(ndev);

	db->dev = &pdev->dev;
	db->ndev = ndev;
	db->pdev = pdev;
	db->msg_enable = netअगर_msg_init(debug, EMAC_DEFAULT_MSG_ENABLE);

	spin_lock_init(&db->lock);

	db->membase = of_iomap(np, 0);
	अगर (!db->membase) अणु
		dev_err(&pdev->dev, "failed to remap registers\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* fill in parameters क्रम net-dev काष्ठाure */
	ndev->base_addr = (अचिन्हित दीर्घ)db->membase;
	ndev->irq = irq_of_parse_and_map(np, 0);
	अगर (ndev->irq == -ENXIO) अणु
		netdev_err(ndev, "No irq resource\n");
		ret = ndev->irq;
		जाओ out_iounmap;
	पूर्ण

	db->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(db->clk)) अणु
		ret = PTR_ERR(db->clk);
		जाओ out_dispose_mapping;
	पूर्ण

	ret = clk_prepare_enable(db->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error couldn't enable clock (%d)\n", ret);
		जाओ out_dispose_mapping;
	पूर्ण

	ret = sunxi_sram_claim(&pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error couldn't map SRAM to device\n");
		जाओ out_clk_disable_unprepare;
	पूर्ण

	db->phy_node = of_parse_phandle(np, "phy-handle", 0);
	अगर (!db->phy_node)
		db->phy_node = of_parse_phandle(np, "phy", 0);
	अगर (!db->phy_node) अणु
		dev_err(&pdev->dev, "no associated PHY\n");
		ret = -ENODEV;
		जाओ out_release_sram;
	पूर्ण

	/* Read MAC-address from DT */
	ret = of_get_mac_address(np, ndev->dev_addr);
	अगर (ret) अणु
		/* अगर the MAC address is invalid get a अक्रमom one */
		eth_hw_addr_अक्रमom(ndev);
		dev_warn(&pdev->dev, "using random MAC address %pM\n",
			 ndev->dev_addr);
	पूर्ण

	db->emacrx_completed_flag = 1;
	emac_घातerup(ndev);
	emac_reset(db);

	ndev->netdev_ops = &emac_netdev_ops;
	ndev->watchकरोg_समयo = msecs_to_jअगरfies(watchकरोg);
	ndev->ethtool_ops = &emac_ethtool_ops;

	platक्रमm_set_drvdata(pdev, ndev);

	/* Carrier starts करोwn, phylib will bring it up */
	netअगर_carrier_off(ndev);

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Registering netdev failed!\n");
		ret = -ENODEV;
		जाओ out_release_sram;
	पूर्ण

	dev_info(&pdev->dev, "%s: at %p, IRQ %d MAC: %pM\n",
		 ndev->name, db->membase, ndev->irq, ndev->dev_addr);

	वापस 0;

out_release_sram:
	sunxi_sram_release(&pdev->dev);
out_clk_disable_unprepare:
	clk_disable_unprepare(db->clk);
out_dispose_mapping:
	irq_dispose_mapping(ndev->irq);
out_iounmap:
	iounmap(db->membase);
out:
	dev_err(db->dev, "not found (%d).\n", ret);

	मुक्त_netdev(ndev);

	वापस ret;
पूर्ण

अटल पूर्णांक emac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा emac_board_info *db = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);
	sunxi_sram_release(&pdev->dev);
	clk_disable_unprepare(db->clk);
	irq_dispose_mapping(ndev->irq);
	iounmap(db->membase);
	मुक्त_netdev(ndev);

	dev_dbg(&pdev->dev, "released and freed device\n");
	वापस 0;
पूर्ण

अटल पूर्णांक emac_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(dev);

	netअगर_carrier_off(ndev);
	netअगर_device_detach(ndev);
	emac_shutकरोwn(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक emac_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(dev);
	काष्ठा emac_board_info *db = netdev_priv(ndev);

	emac_reset(db);
	emac_init_device(ndev);
	netअगर_device_attach(ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id emac_of_match[] = अणु
	अणु.compatible = "allwinner,sun4i-a10-emac",पूर्ण,

	/* Deprecated */
	अणु.compatible = "allwinner,sun4i-emac",पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, emac_of_match);

अटल काष्ठा platक्रमm_driver emac_driver = अणु
	.driver = अणु
		.name = "sun4i-emac",
		.of_match_table = emac_of_match,
	पूर्ण,
	.probe = emac_probe,
	.हटाओ = emac_हटाओ,
	.suspend = emac_suspend,
	.resume = emac_resume,
पूर्ण;

module_platक्रमm_driver(emac_driver);

MODULE_AUTHOR("Stefan Roese <sr@denx.de>");
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner A10 emac network driver");
MODULE_LICENSE("GPL");
