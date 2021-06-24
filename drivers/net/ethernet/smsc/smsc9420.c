<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /***************************************************************************
 *
 * Copyright (C) 2007,2008  SMSC
 *
 ***************************************************************************
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/pci.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/crc32.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "smsc9420.h"

#घोषणा DRV_NAME		"smsc9420"
#घोषणा DRV_MDIONAME		"smsc9420-mdio"
#घोषणा DRV_DESCRIPTION		"SMSC LAN9420 driver"
#घोषणा DRV_VERSION		"1.01"

MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

काष्ठा smsc9420_dma_desc अणु
	u32 status;
	u32 length;
	u32 buffer1;
	u32 buffer2;
पूर्ण;

काष्ठा smsc9420_ring_info अणु
	काष्ठा sk_buff *skb;
	dma_addr_t mapping;
पूर्ण;

काष्ठा smsc9420_pdata अणु
	व्योम __iomem *ioaddr;
	काष्ठा pci_dev *pdev;
	काष्ठा net_device *dev;

	काष्ठा smsc9420_dma_desc *rx_ring;
	काष्ठा smsc9420_dma_desc *tx_ring;
	काष्ठा smsc9420_ring_info *tx_buffers;
	काष्ठा smsc9420_ring_info *rx_buffers;
	dma_addr_t rx_dma_addr;
	dma_addr_t tx_dma_addr;
	पूर्णांक tx_ring_head, tx_ring_tail;
	पूर्णांक rx_ring_head, rx_ring_tail;

	spinlock_t पूर्णांक_lock;
	spinlock_t phy_lock;

	काष्ठा napi_काष्ठा napi;

	bool software_irq_संकेत;
	bool rx_csum;
	u32 msg_enable;

	काष्ठा mii_bus *mii_bus;
	पूर्णांक last_duplex;
	पूर्णांक last_carrier;
पूर्ण;

अटल स्थिर काष्ठा pci_device_id smsc9420_id_table[] = अणु
	अणु PCI_VENDOR_ID_9420, PCI_DEVICE_ID_9420, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, smsc9420_id_table);

#घोषणा SMSC_MSG_DEFAULT (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK)

अटल uपूर्णांक smsc_debug;
अटल uपूर्णांक debug = -1;
module_param(debug, uपूर्णांक, 0);
MODULE_PARM_DESC(debug, "debug level");

अटल अंतरभूत u32 smsc9420_reg_पढ़ो(काष्ठा smsc9420_pdata *pd, u32 offset)
अणु
	वापस ioपढ़ो32(pd->ioaddr + offset);
पूर्ण

अटल अंतरभूत व्योम
smsc9420_reg_ग_लिखो(काष्ठा smsc9420_pdata *pd, u32 offset, u32 value)
अणु
	ioग_लिखो32(value, pd->ioaddr + offset);
पूर्ण

अटल अंतरभूत व्योम smsc9420_pci_flush_ग_लिखो(काष्ठा smsc9420_pdata *pd)
अणु
	/* to ensure PCI ग_लिखो completion, we must perक्रमm a PCI पढ़ो */
	smsc9420_reg_पढ़ो(pd, ID_REV);
पूर्ण

अटल पूर्णांक smsc9420_mii_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phyaddr, पूर्णांक regidx)
अणु
	काष्ठा smsc9420_pdata *pd = (काष्ठा smsc9420_pdata *)bus->priv;
	अचिन्हित दीर्घ flags;
	u32 addr;
	पूर्णांक i, reg = -EIO;

	spin_lock_irqsave(&pd->phy_lock, flags);

	/*  confirm MII not busy */
	अगर ((smsc9420_reg_पढ़ो(pd, MII_ACCESS) & MII_ACCESS_MII_BUSY_)) अणु
		netअगर_warn(pd, drv, pd->dev, "MII is busy???\n");
		जाओ out;
	पूर्ण

	/* set the address, index & direction (पढ़ो from PHY) */
	addr = ((phyaddr & 0x1F) << 11) | ((regidx & 0x1F) << 6) |
		MII_ACCESS_MII_READ_;
	smsc9420_reg_ग_लिखो(pd, MII_ACCESS, addr);

	/* रुको क्रम पढ़ो to complete with 50us समयout */
	क्रम (i = 0; i < 5; i++) अणु
		अगर (!(smsc9420_reg_पढ़ो(pd, MII_ACCESS) &
			MII_ACCESS_MII_BUSY_)) अणु
			reg = (u16)smsc9420_reg_पढ़ो(pd, MII_DATA);
			जाओ out;
		पूर्ण
		udelay(10);
	पूर्ण

	netअगर_warn(pd, drv, pd->dev, "MII busy timeout!\n");

out:
	spin_unlock_irqrestore(&pd->phy_lock, flags);
	वापस reg;
पूर्ण

अटल पूर्णांक smsc9420_mii_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phyaddr, पूर्णांक regidx,
			   u16 val)
अणु
	काष्ठा smsc9420_pdata *pd = (काष्ठा smsc9420_pdata *)bus->priv;
	अचिन्हित दीर्घ flags;
	u32 addr;
	पूर्णांक i, reg = -EIO;

	spin_lock_irqsave(&pd->phy_lock, flags);

	/* confirm MII not busy */
	अगर ((smsc9420_reg_पढ़ो(pd, MII_ACCESS) & MII_ACCESS_MII_BUSY_)) अणु
		netअगर_warn(pd, drv, pd->dev, "MII is busy???\n");
		जाओ out;
	पूर्ण

	/* put the data to ग_लिखो in the MAC */
	smsc9420_reg_ग_लिखो(pd, MII_DATA, (u32)val);

	/* set the address, index & direction (ग_लिखो to PHY) */
	addr = ((phyaddr & 0x1F) << 11) | ((regidx & 0x1F) << 6) |
		MII_ACCESS_MII_WRITE_;
	smsc9420_reg_ग_लिखो(pd, MII_ACCESS, addr);

	/* रुको क्रम ग_लिखो to complete with 50us समयout */
	क्रम (i = 0; i < 5; i++) अणु
		अगर (!(smsc9420_reg_पढ़ो(pd, MII_ACCESS) &
			MII_ACCESS_MII_BUSY_)) अणु
			reg = 0;
			जाओ out;
		पूर्ण
		udelay(10);
	पूर्ण

	netअगर_warn(pd, drv, pd->dev, "MII busy timeout!\n");

out:
	spin_unlock_irqrestore(&pd->phy_lock, flags);
	वापस reg;
पूर्ण

/* Returns hash bit number क्रम given MAC address
 * Example:
 * 01 00 5E 00 00 01 -> वापसs bit number 31 */
अटल u32 smsc9420_hash(u8 addr[ETH_ALEN])
अणु
	वापस (ether_crc(ETH_ALEN, addr) >> 26) & 0x3f;
पूर्ण

अटल पूर्णांक smsc9420_eeprom_reload(काष्ठा smsc9420_pdata *pd)
अणु
	पूर्णांक समयout = 100000;

	BUG_ON(!pd);

	अगर (smsc9420_reg_पढ़ो(pd, E2P_CMD) & E2P_CMD_EPC_BUSY_) अणु
		netअगर_dbg(pd, drv, pd->dev, "%s: Eeprom busy\n", __func__);
		वापस -EIO;
	पूर्ण

	smsc9420_reg_ग_लिखो(pd, E2P_CMD,
		(E2P_CMD_EPC_BUSY_ | E2P_CMD_EPC_CMD_RELOAD_));

	करो अणु
		udelay(10);
		अगर (!(smsc9420_reg_पढ़ो(pd, E2P_CMD) & E2P_CMD_EPC_BUSY_))
			वापस 0;
	पूर्ण जबतक (समयout--);

	netअगर_warn(pd, drv, pd->dev, "%s: Eeprom timed out\n", __func__);
	वापस -EIO;
पूर्ण

अटल व्योम smsc9420_ethtool_get_drvinfo(काष्ठा net_device *netdev,
					 काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(netdev);

	strlcpy(drvinfo->driver, DRV_NAME, माप(drvinfo->driver));
	strlcpy(drvinfo->bus_info, pci_name(pd->pdev),
		माप(drvinfo->bus_info));
	strlcpy(drvinfo->version, DRV_VERSION, माप(drvinfo->version));
पूर्ण

अटल u32 smsc9420_ethtool_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(netdev);
	वापस pd->msg_enable;
पूर्ण

अटल व्योम smsc9420_ethtool_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(netdev);
	pd->msg_enable = data;
पूर्ण

अटल पूर्णांक smsc9420_ethtool_getregslen(काष्ठा net_device *dev)
अणु
	/* all smsc9420 रेजिस्टरs plus all phy रेजिस्टरs */
	वापस 0x100 + (32 * माप(u32));
पूर्ण

अटल व्योम
smsc9420_ethtool_getregs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			 व्योम *buf)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	काष्ठा phy_device *phy_dev = dev->phydev;
	अचिन्हित पूर्णांक i, j = 0;
	u32 *data = buf;

	regs->version = smsc9420_reg_पढ़ो(pd, ID_REV);
	क्रम (i = 0; i < 0x100; i += (माप(u32)))
		data[j++] = smsc9420_reg_पढ़ो(pd, i);

	// cannot पढ़ो phy रेजिस्टरs अगर the net device is करोwn
	अगर (!phy_dev)
		वापस;

	क्रम (i = 0; i <= 31; i++)
		data[j++] = smsc9420_mii_पढ़ो(phy_dev->mdio.bus,
					      phy_dev->mdio.addr, i);
पूर्ण

अटल व्योम smsc9420_eeprom_enable_access(काष्ठा smsc9420_pdata *pd)
अणु
	अचिन्हित पूर्णांक temp = smsc9420_reg_पढ़ो(pd, GPIO_CFG);
	temp &= ~GPIO_CFG_EEPR_EN_;
	smsc9420_reg_ग_लिखो(pd, GPIO_CFG, temp);
	msleep(1);
पूर्ण

अटल पूर्णांक smsc9420_eeprom_send_cmd(काष्ठा smsc9420_pdata *pd, u32 op)
अणु
	पूर्णांक समयout = 100;
	u32 e2cmd;

	netअगर_dbg(pd, hw, pd->dev, "op 0x%08x\n", op);
	अगर (smsc9420_reg_पढ़ो(pd, E2P_CMD) & E2P_CMD_EPC_BUSY_) अणु
		netअगर_warn(pd, hw, pd->dev, "Busy at start\n");
		वापस -EBUSY;
	पूर्ण

	e2cmd = op | E2P_CMD_EPC_BUSY_;
	smsc9420_reg_ग_लिखो(pd, E2P_CMD, e2cmd);

	करो अणु
		msleep(1);
		e2cmd = smsc9420_reg_पढ़ो(pd, E2P_CMD);
	पूर्ण जबतक ((e2cmd & E2P_CMD_EPC_BUSY_) && (--समयout));

	अगर (!समयout) अणु
		netअगर_info(pd, hw, pd->dev, "TIMED OUT\n");
		वापस -EAGAIN;
	पूर्ण

	अगर (e2cmd & E2P_CMD_EPC_TIMEOUT_) अणु
		netअगर_info(pd, hw, pd->dev,
			   "Error occurred during eeprom operation\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smsc9420_eeprom_पढ़ो_location(काष्ठा smsc9420_pdata *pd,
					 u8 address, u8 *data)
अणु
	u32 op = E2P_CMD_EPC_CMD_READ_ | address;
	पूर्णांक ret;

	netअगर_dbg(pd, hw, pd->dev, "address 0x%x\n", address);
	ret = smsc9420_eeprom_send_cmd(pd, op);

	अगर (!ret)
		data[address] = smsc9420_reg_पढ़ो(pd, E2P_DATA);

	वापस ret;
पूर्ण

अटल पूर्णांक smsc9420_eeprom_ग_लिखो_location(काष्ठा smsc9420_pdata *pd,
					  u8 address, u8 data)
अणु
	u32 op = E2P_CMD_EPC_CMD_ERASE_ | address;
	पूर्णांक ret;

	netअगर_dbg(pd, hw, pd->dev, "address 0x%x, data 0x%x\n", address, data);
	ret = smsc9420_eeprom_send_cmd(pd, op);

	अगर (!ret) अणु
		op = E2P_CMD_EPC_CMD_WRITE_ | address;
		smsc9420_reg_ग_लिखो(pd, E2P_DATA, (u32)data);
		ret = smsc9420_eeprom_send_cmd(pd, op);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smsc9420_ethtool_get_eeprom_len(काष्ठा net_device *dev)
अणु
	वापस SMSC9420_EEPROM_SIZE;
पूर्ण

अटल पूर्णांक smsc9420_ethtool_get_eeprom(काष्ठा net_device *dev,
				       काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	u8 eeprom_data[SMSC9420_EEPROM_SIZE];
	पूर्णांक len, i;

	smsc9420_eeprom_enable_access(pd);

	len = min(eeprom->len, SMSC9420_EEPROM_SIZE);
	क्रम (i = 0; i < len; i++) अणु
		पूर्णांक ret = smsc9420_eeprom_पढ़ो_location(pd, i, eeprom_data);
		अगर (ret < 0) अणु
			eeprom->len = 0;
			वापस ret;
		पूर्ण
	पूर्ण

	स_नकल(data, &eeprom_data[eeprom->offset], len);
	eeprom->magic = SMSC9420_EEPROM_MAGIC;
	eeprom->len = len;
	वापस 0;
पूर्ण

अटल पूर्णांक smsc9420_ethtool_set_eeprom(काष्ठा net_device *dev,
				       काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	पूर्णांक ret;

	अगर (eeprom->magic != SMSC9420_EEPROM_MAGIC)
		वापस -EINVAL;

	smsc9420_eeprom_enable_access(pd);
	smsc9420_eeprom_send_cmd(pd, E2P_CMD_EPC_CMD_EWEN_);
	ret = smsc9420_eeprom_ग_लिखो_location(pd, eeprom->offset, *data);
	smsc9420_eeprom_send_cmd(pd, E2P_CMD_EPC_CMD_EWDS_);

	/* Single byte ग_लिखो, according to man page */
	eeprom->len = 1;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops smsc9420_ethtool_ops = अणु
	.get_drvinfo = smsc9420_ethtool_get_drvinfo,
	.get_msglevel = smsc9420_ethtool_get_msglevel,
	.set_msglevel = smsc9420_ethtool_set_msglevel,
	.nway_reset = phy_ethtool_nway_reset,
	.get_link = ethtool_op_get_link,
	.get_eeprom_len = smsc9420_ethtool_get_eeprom_len,
	.get_eeprom = smsc9420_ethtool_get_eeprom,
	.set_eeprom = smsc9420_ethtool_set_eeprom,
	.get_regs_len = smsc9420_ethtool_getregslen,
	.get_regs = smsc9420_ethtool_getregs,
	.get_ts_info = ethtool_op_get_ts_info,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

/* Sets the device MAC address to dev_addr */
अटल व्योम smsc9420_set_mac_address(काष्ठा net_device *dev)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	u8 *dev_addr = dev->dev_addr;
	u32 mac_high16 = (dev_addr[5] << 8) | dev_addr[4];
	u32 mac_low32 = (dev_addr[3] << 24) | (dev_addr[2] << 16) |
	    (dev_addr[1] << 8) | dev_addr[0];

	smsc9420_reg_ग_लिखो(pd, ADDRH, mac_high16);
	smsc9420_reg_ग_लिखो(pd, ADDRL, mac_low32);
पूर्ण

अटल व्योम smsc9420_check_mac_address(काष्ठा net_device *dev)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);

	/* Check अगर mac address has been specअगरied when bringing पूर्णांकerface up */
	अगर (is_valid_ether_addr(dev->dev_addr)) अणु
		smsc9420_set_mac_address(dev);
		netअगर_dbg(pd, probe, pd->dev,
			  "MAC Address is specified by configuration\n");
	पूर्ण अन्यथा अणु
		/* Try पढ़ोing mac address from device. अगर EEPROM is present
		 * it will alपढ़ोy have been set */
		u32 mac_high16 = smsc9420_reg_पढ़ो(pd, ADDRH);
		u32 mac_low32 = smsc9420_reg_पढ़ो(pd, ADDRL);
		dev->dev_addr[0] = (u8)(mac_low32);
		dev->dev_addr[1] = (u8)(mac_low32 >> 8);
		dev->dev_addr[2] = (u8)(mac_low32 >> 16);
		dev->dev_addr[3] = (u8)(mac_low32 >> 24);
		dev->dev_addr[4] = (u8)(mac_high16);
		dev->dev_addr[5] = (u8)(mac_high16 >> 8);

		अगर (is_valid_ether_addr(dev->dev_addr)) अणु
			/* eeprom values are valid  so use them */
			netअगर_dbg(pd, probe, pd->dev,
				  "Mac Address is read from EEPROM\n");
		पूर्ण अन्यथा अणु
			/* eeprom values are invalid, generate अक्रमom MAC */
			eth_hw_addr_अक्रमom(dev);
			smsc9420_set_mac_address(dev);
			netअगर_dbg(pd, probe, pd->dev,
				  "MAC Address is set to random\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम smsc9420_stop_tx(काष्ठा smsc9420_pdata *pd)
अणु
	u32 dmac_control, mac_cr, dma_पूर्णांकr_ena;
	पूर्णांक समयout = 1000;

	/* disable TX DMAC */
	dmac_control = smsc9420_reg_पढ़ो(pd, DMAC_CONTROL);
	dmac_control &= (~DMAC_CONTROL_ST_);
	smsc9420_reg_ग_लिखो(pd, DMAC_CONTROL, dmac_control);

	/* Wait max 10ms क्रम transmit process to stop */
	जबतक (--समयout) अणु
		अगर (smsc9420_reg_पढ़ो(pd, DMAC_STATUS) & DMAC_STS_TS_)
			अवरोध;
		udelay(10);
	पूर्ण

	अगर (!समयout)
		netअगर_warn(pd, अगरकरोwn, pd->dev, "TX DMAC failed to stop\n");

	/* ACK Tx DMAC stop bit */
	smsc9420_reg_ग_लिखो(pd, DMAC_STATUS, DMAC_STS_TXPS_);

	/* mask TX DMAC पूर्णांकerrupts */
	dma_पूर्णांकr_ena = smsc9420_reg_पढ़ो(pd, DMAC_INTR_ENA);
	dma_पूर्णांकr_ena &= ~(DMAC_INTR_ENA_TX_);
	smsc9420_reg_ग_लिखो(pd, DMAC_INTR_ENA, dma_पूर्णांकr_ena);
	smsc9420_pci_flush_ग_लिखो(pd);

	/* stop MAC TX */
	mac_cr = smsc9420_reg_पढ़ो(pd, MAC_CR) & (~MAC_CR_TXEN_);
	smsc9420_reg_ग_लिखो(pd, MAC_CR, mac_cr);
	smsc9420_pci_flush_ग_लिखो(pd);
पूर्ण

अटल व्योम smsc9420_मुक्त_tx_ring(काष्ठा smsc9420_pdata *pd)
अणु
	पूर्णांक i;

	BUG_ON(!pd->tx_ring);

	अगर (!pd->tx_buffers)
		वापस;

	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = pd->tx_buffers[i].skb;

		अगर (skb) अणु
			BUG_ON(!pd->tx_buffers[i].mapping);
			dma_unmap_single(&pd->pdev->dev,
					 pd->tx_buffers[i].mapping, skb->len,
					 DMA_TO_DEVICE);
			dev_kमुक्त_skb_any(skb);
		पूर्ण

		pd->tx_ring[i].status = 0;
		pd->tx_ring[i].length = 0;
		pd->tx_ring[i].buffer1 = 0;
		pd->tx_ring[i].buffer2 = 0;
	पूर्ण
	wmb();

	kमुक्त(pd->tx_buffers);
	pd->tx_buffers = शून्य;

	pd->tx_ring_head = 0;
	pd->tx_ring_tail = 0;
पूर्ण

अटल व्योम smsc9420_मुक्त_rx_ring(काष्ठा smsc9420_pdata *pd)
अणु
	पूर्णांक i;

	BUG_ON(!pd->rx_ring);

	अगर (!pd->rx_buffers)
		वापस;

	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		अगर (pd->rx_buffers[i].skb)
			dev_kमुक्त_skb_any(pd->rx_buffers[i].skb);

		अगर (pd->rx_buffers[i].mapping)
			dma_unmap_single(&pd->pdev->dev,
					 pd->rx_buffers[i].mapping,
					 PKT_BUF_SZ, DMA_FROM_DEVICE);

		pd->rx_ring[i].status = 0;
		pd->rx_ring[i].length = 0;
		pd->rx_ring[i].buffer1 = 0;
		pd->rx_ring[i].buffer2 = 0;
	पूर्ण
	wmb();

	kमुक्त(pd->rx_buffers);
	pd->rx_buffers = शून्य;

	pd->rx_ring_head = 0;
	pd->rx_ring_tail = 0;
पूर्ण

अटल व्योम smsc9420_stop_rx(काष्ठा smsc9420_pdata *pd)
अणु
	पूर्णांक समयout = 1000;
	u32 mac_cr, dmac_control, dma_पूर्णांकr_ena;

	/* mask RX DMAC पूर्णांकerrupts */
	dma_पूर्णांकr_ena = smsc9420_reg_पढ़ो(pd, DMAC_INTR_ENA);
	dma_पूर्णांकr_ena &= (~DMAC_INTR_ENA_RX_);
	smsc9420_reg_ग_लिखो(pd, DMAC_INTR_ENA, dma_पूर्णांकr_ena);
	smsc9420_pci_flush_ग_लिखो(pd);

	/* stop RX MAC prior to stoping DMA */
	mac_cr = smsc9420_reg_पढ़ो(pd, MAC_CR) & (~MAC_CR_RXEN_);
	smsc9420_reg_ग_लिखो(pd, MAC_CR, mac_cr);
	smsc9420_pci_flush_ग_लिखो(pd);

	/* stop RX DMAC */
	dmac_control = smsc9420_reg_पढ़ो(pd, DMAC_CONTROL);
	dmac_control &= (~DMAC_CONTROL_SR_);
	smsc9420_reg_ग_लिखो(pd, DMAC_CONTROL, dmac_control);
	smsc9420_pci_flush_ग_लिखो(pd);

	/* रुको up to 10ms क्रम receive to stop */
	जबतक (--समयout) अणु
		अगर (smsc9420_reg_पढ़ो(pd, DMAC_STATUS) & DMAC_STS_RS_)
			अवरोध;
		udelay(10);
	पूर्ण

	अगर (!समयout)
		netअगर_warn(pd, अगरकरोwn, pd->dev,
			   "RX DMAC did not stop! timeout\n");

	/* ACK the Rx DMAC stop bit */
	smsc9420_reg_ग_लिखो(pd, DMAC_STATUS, DMAC_STS_RXPS_);
पूर्ण

अटल irqवापस_t smsc9420_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा smsc9420_pdata *pd = dev_id;
	u32 पूर्णांक_cfg, पूर्णांक_sts, पूर्णांक_ctl;
	irqवापस_t ret = IRQ_NONE;
	uदीर्घ flags;

	BUG_ON(!pd);
	BUG_ON(!pd->ioaddr);

	पूर्णांक_cfg = smsc9420_reg_पढ़ो(pd, INT_CFG);

	/* check अगर it's our पूर्णांकerrupt */
	अगर ((पूर्णांक_cfg & (INT_CFG_IRQ_EN_ | INT_CFG_IRQ_INT_)) !=
	    (INT_CFG_IRQ_EN_ | INT_CFG_IRQ_INT_))
		वापस IRQ_NONE;

	पूर्णांक_sts = smsc9420_reg_पढ़ो(pd, INT_STAT);

	अगर (likely(INT_STAT_DMAC_INT_ & पूर्णांक_sts)) अणु
		u32 status = smsc9420_reg_पढ़ो(pd, DMAC_STATUS);
		u32 पूर्णांकs_to_clear = 0;

		अगर (status & DMAC_STS_TX_) अणु
			पूर्णांकs_to_clear |= (DMAC_STS_TX_ | DMAC_STS_NIS_);
			netअगर_wake_queue(pd->dev);
		पूर्ण

		अगर (status & DMAC_STS_RX_) अणु
			/* mask RX DMAC पूर्णांकerrupts */
			u32 dma_पूर्णांकr_ena = smsc9420_reg_पढ़ो(pd, DMAC_INTR_ENA);
			dma_पूर्णांकr_ena &= (~DMAC_INTR_ENA_RX_);
			smsc9420_reg_ग_लिखो(pd, DMAC_INTR_ENA, dma_पूर्णांकr_ena);
			smsc9420_pci_flush_ग_लिखो(pd);

			पूर्णांकs_to_clear |= (DMAC_STS_RX_ | DMAC_STS_NIS_);
			napi_schedule(&pd->napi);
		पूर्ण

		अगर (पूर्णांकs_to_clear)
			smsc9420_reg_ग_लिखो(pd, DMAC_STATUS, पूर्णांकs_to_clear);

		ret = IRQ_HANDLED;
	पूर्ण

	अगर (unlikely(INT_STAT_SW_INT_ & पूर्णांक_sts)) अणु
		/* mask software पूर्णांकerrupt */
		spin_lock_irqsave(&pd->पूर्णांक_lock, flags);
		पूर्णांक_ctl = smsc9420_reg_पढ़ो(pd, INT_CTL);
		पूर्णांक_ctl &= (~INT_CTL_SW_INT_EN_);
		smsc9420_reg_ग_लिखो(pd, INT_CTL, पूर्णांक_ctl);
		spin_unlock_irqrestore(&pd->पूर्णांक_lock, flags);

		smsc9420_reg_ग_लिखो(pd, INT_STAT, INT_STAT_SW_INT_);
		pd->software_irq_संकेत = true;
		smp_wmb();

		ret = IRQ_HANDLED;
	पूर्ण

	/* to ensure PCI ग_लिखो completion, we must perक्रमm a PCI पढ़ो */
	smsc9420_pci_flush_ग_लिखो(pd);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम smsc9420_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	स्थिर पूर्णांक irq = pd->pdev->irq;

	disable_irq(irq);
	smsc9420_isr(0, dev);
	enable_irq(irq);
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_POLL_CONTROLLER */

अटल व्योम smsc9420_dmac_soft_reset(काष्ठा smsc9420_pdata *pd)
अणु
	smsc9420_reg_ग_लिखो(pd, BUS_MODE, BUS_MODE_SWR_);
	smsc9420_reg_पढ़ो(pd, BUS_MODE);
	udelay(2);
	अगर (smsc9420_reg_पढ़ो(pd, BUS_MODE) & BUS_MODE_SWR_)
		netअगर_warn(pd, drv, pd->dev, "Software reset not cleared\n");
पूर्ण

अटल पूर्णांक smsc9420_stop(काष्ठा net_device *dev)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	u32 पूर्णांक_cfg;
	uदीर्घ flags;

	BUG_ON(!pd);
	BUG_ON(!dev->phydev);

	/* disable master पूर्णांकerrupt */
	spin_lock_irqsave(&pd->पूर्णांक_lock, flags);
	पूर्णांक_cfg = smsc9420_reg_पढ़ो(pd, INT_CFG) & (~INT_CFG_IRQ_EN_);
	smsc9420_reg_ग_लिखो(pd, INT_CFG, पूर्णांक_cfg);
	spin_unlock_irqrestore(&pd->पूर्णांक_lock, flags);

	netअगर_tx_disable(dev);
	napi_disable(&pd->napi);

	smsc9420_stop_tx(pd);
	smsc9420_मुक्त_tx_ring(pd);

	smsc9420_stop_rx(pd);
	smsc9420_मुक्त_rx_ring(pd);

	मुक्त_irq(pd->pdev->irq, pd);

	smsc9420_dmac_soft_reset(pd);

	phy_stop(dev->phydev);

	phy_disconnect(dev->phydev);
	mdiobus_unरेजिस्टर(pd->mii_bus);
	mdiobus_मुक्त(pd->mii_bus);

	वापस 0;
पूर्ण

अटल व्योम smsc9420_rx_count_stats(काष्ठा net_device *dev, u32 desc_status)
अणु
	अगर (unlikely(desc_status & RDES0_ERROR_SUMMARY_)) अणु
		dev->stats.rx_errors++;
		अगर (desc_status & RDES0_DESCRIPTOR_ERROR_)
			dev->stats.rx_over_errors++;
		अन्यथा अगर (desc_status & (RDES0_FRAME_TOO_LONG_ |
			RDES0_RUNT_FRAME_ | RDES0_COLLISION_SEEN_))
			dev->stats.rx_frame_errors++;
		अन्यथा अगर (desc_status & RDES0_CRC_ERROR_)
			dev->stats.rx_crc_errors++;
	पूर्ण

	अगर (unlikely(desc_status & RDES0_LENGTH_ERROR_))
		dev->stats.rx_length_errors++;

	अगर (unlikely(!((desc_status & RDES0_LAST_DESCRIPTOR_) &&
		(desc_status & RDES0_FIRST_DESCRIPTOR_))))
		dev->stats.rx_length_errors++;

	अगर (desc_status & RDES0_MULTICAST_FRAME_)
		dev->stats.multicast++;
पूर्ण

अटल व्योम smsc9420_rx_hanकरोff(काष्ठा smsc9420_pdata *pd, स्थिर पूर्णांक index,
				स्थिर u32 status)
अणु
	काष्ठा net_device *dev = pd->dev;
	काष्ठा sk_buff *skb;
	u16 packet_length = (status & RDES0_FRAME_LENGTH_MASK_)
		>> RDES0_FRAME_LENGTH_SHFT_;

	/* हटाओ crc from packet lendth */
	packet_length -= 4;

	अगर (pd->rx_csum)
		packet_length -= 2;

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += packet_length;

	dma_unmap_single(&pd->pdev->dev, pd->rx_buffers[index].mapping,
			 PKT_BUF_SZ, DMA_FROM_DEVICE);
	pd->rx_buffers[index].mapping = 0;

	skb = pd->rx_buffers[index].skb;
	pd->rx_buffers[index].skb = शून्य;

	अगर (pd->rx_csum) अणु
		u16 hw_csum = get_unaligned_le16(skb_tail_poपूर्णांकer(skb) +
			NET_IP_ALIGN + packet_length + 4);
		put_unaligned_le16(hw_csum, &skb->csum);
		skb->ip_summed = CHECKSUM_COMPLETE;
	पूर्ण

	skb_reserve(skb, NET_IP_ALIGN);
	skb_put(skb, packet_length);

	skb->protocol = eth_type_trans(skb, dev);

	netअगर_receive_skb(skb);
पूर्ण

अटल पूर्णांक smsc9420_alloc_rx_buffer(काष्ठा smsc9420_pdata *pd, पूर्णांक index)
अणु
	काष्ठा sk_buff *skb = netdev_alloc_skb(pd->dev, PKT_BUF_SZ);
	dma_addr_t mapping;

	BUG_ON(pd->rx_buffers[index].skb);
	BUG_ON(pd->rx_buffers[index].mapping);

	अगर (unlikely(!skb))
		वापस -ENOMEM;

	mapping = dma_map_single(&pd->pdev->dev, skb_tail_poपूर्णांकer(skb),
				 PKT_BUF_SZ, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&pd->pdev->dev, mapping)) अणु
		dev_kमुक्त_skb_any(skb);
		netअगर_warn(pd, rx_err, pd->dev, "pci_map_single failed!\n");
		वापस -ENOMEM;
	पूर्ण

	pd->rx_buffers[index].skb = skb;
	pd->rx_buffers[index].mapping = mapping;
	pd->rx_ring[index].buffer1 = mapping + NET_IP_ALIGN;
	pd->rx_ring[index].status = RDES0_OWN_;
	wmb();

	वापस 0;
पूर्ण

अटल व्योम smsc9420_alloc_new_rx_buffers(काष्ठा smsc9420_pdata *pd)
अणु
	जबतक (pd->rx_ring_tail != pd->rx_ring_head) अणु
		अगर (smsc9420_alloc_rx_buffer(pd, pd->rx_ring_tail))
			अवरोध;

		pd->rx_ring_tail = (pd->rx_ring_tail + 1) % RX_RING_SIZE;
	पूर्ण
पूर्ण

अटल पूर्णांक smsc9420_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा smsc9420_pdata *pd =
		container_of(napi, काष्ठा smsc9420_pdata, napi);
	काष्ठा net_device *dev = pd->dev;
	u32 drop_frame_cnt, dma_पूर्णांकr_ena, status;
	पूर्णांक work_करोne;

	क्रम (work_करोne = 0; work_करोne < budget; work_करोne++) अणु
		rmb();
		status = pd->rx_ring[pd->rx_ring_head].status;

		/* stop अगर DMAC owns this dma descriptor */
		अगर (status & RDES0_OWN_)
			अवरोध;

		smsc9420_rx_count_stats(dev, status);
		smsc9420_rx_hanकरोff(pd, pd->rx_ring_head, status);
		pd->rx_ring_head = (pd->rx_ring_head + 1) % RX_RING_SIZE;
		smsc9420_alloc_new_rx_buffers(pd);
	पूर्ण

	drop_frame_cnt = smsc9420_reg_पढ़ो(pd, MISS_FRAME_CNTR);
	dev->stats.rx_dropped +=
	    (drop_frame_cnt & 0xFFFF) + ((drop_frame_cnt >> 17) & 0x3FF);

	/* Kick RXDMA */
	smsc9420_reg_ग_लिखो(pd, RX_POLL_DEMAND, 1);
	smsc9420_pci_flush_ग_लिखो(pd);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(&pd->napi, work_करोne);

		/* re-enable RX DMA पूर्णांकerrupts */
		dma_पूर्णांकr_ena = smsc9420_reg_पढ़ो(pd, DMAC_INTR_ENA);
		dma_पूर्णांकr_ena |= (DMAC_INTR_ENA_RX_ | DMAC_INTR_ENA_NIS_);
		smsc9420_reg_ग_लिखो(pd, DMAC_INTR_ENA, dma_पूर्णांकr_ena);
		smsc9420_pci_flush_ग_लिखो(pd);
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल व्योम
smsc9420_tx_update_stats(काष्ठा net_device *dev, u32 status, u32 length)
अणु
	अगर (unlikely(status & TDES0_ERROR_SUMMARY_)) अणु
		dev->stats.tx_errors++;
		अगर (status & (TDES0_EXCESSIVE_DEFERRAL_ |
			TDES0_EXCESSIVE_COLLISIONS_))
			dev->stats.tx_पातed_errors++;

		अगर (status & (TDES0_LOSS_OF_CARRIER_ | TDES0_NO_CARRIER_))
			dev->stats.tx_carrier_errors++;
	पूर्ण अन्यथा अणु
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += (length & 0x7FF);
	पूर्ण

	अगर (unlikely(status & TDES0_EXCESSIVE_COLLISIONS_)) अणु
		dev->stats.collisions += 16;
	पूर्ण अन्यथा अणु
		dev->stats.collisions +=
			(status & TDES0_COLLISION_COUNT_MASK_) >>
			TDES0_COLLISION_COUNT_SHFT_;
	पूर्ण

	अगर (unlikely(status & TDES0_HEARTBEAT_FAIL_))
		dev->stats.tx_heartbeat_errors++;
पूर्ण

/* Check क्रम completed dma transfers, update stats and मुक्त skbs */
अटल व्योम smsc9420_complete_tx(काष्ठा net_device *dev)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);

	जबतक (pd->tx_ring_tail != pd->tx_ring_head) अणु
		पूर्णांक index = pd->tx_ring_tail;
		u32 status, length;

		rmb();
		status = pd->tx_ring[index].status;
		length = pd->tx_ring[index].length;

		/* Check अगर DMA still owns this descriptor */
		अगर (unlikely(TDES0_OWN_ & status))
			अवरोध;

		smsc9420_tx_update_stats(dev, status, length);

		BUG_ON(!pd->tx_buffers[index].skb);
		BUG_ON(!pd->tx_buffers[index].mapping);

		dma_unmap_single(&pd->pdev->dev,
				 pd->tx_buffers[index].mapping,
				 pd->tx_buffers[index].skb->len,
				 DMA_TO_DEVICE);
		pd->tx_buffers[index].mapping = 0;

		dev_kमुक्त_skb_any(pd->tx_buffers[index].skb);
		pd->tx_buffers[index].skb = शून्य;

		pd->tx_ring[index].buffer1 = 0;
		wmb();

		pd->tx_ring_tail = (pd->tx_ring_tail + 1) % TX_RING_SIZE;
	पूर्ण
पूर्ण

अटल netdev_tx_t smsc9420_hard_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	dma_addr_t mapping;
	पूर्णांक index = pd->tx_ring_head;
	u32 पंचांगp_desc1;
	bool about_to_take_last_desc =
		(((pd->tx_ring_head + 2) % TX_RING_SIZE) == pd->tx_ring_tail);

	smsc9420_complete_tx(dev);

	rmb();
	BUG_ON(pd->tx_ring[index].status & TDES0_OWN_);
	BUG_ON(pd->tx_buffers[index].skb);
	BUG_ON(pd->tx_buffers[index].mapping);

	mapping = dma_map_single(&pd->pdev->dev, skb->data, skb->len,
				 DMA_TO_DEVICE);
	अगर (dma_mapping_error(&pd->pdev->dev, mapping)) अणु
		netअगर_warn(pd, tx_err, pd->dev,
			   "pci_map_single failed, dropping packet\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	pd->tx_buffers[index].skb = skb;
	pd->tx_buffers[index].mapping = mapping;

	पंचांगp_desc1 = (TDES1_LS_ | ((u32)skb->len & 0x7FF));
	अगर (unlikely(about_to_take_last_desc)) अणु
		पंचांगp_desc1 |= TDES1_IC_;
		netअगर_stop_queue(pd->dev);
	पूर्ण

	/* check अगर we are at the last descriptor and need to set EOR */
	अगर (unlikely(index == (TX_RING_SIZE - 1)))
		पंचांगp_desc1 |= TDES1_TER_;

	pd->tx_ring[index].buffer1 = mapping;
	pd->tx_ring[index].length = पंचांगp_desc1;
	wmb();

	/* increment head */
	pd->tx_ring_head = (pd->tx_ring_head + 1) % TX_RING_SIZE;

	/* assign ownership to DMAC */
	pd->tx_ring[index].status = TDES0_OWN_;
	wmb();

	skb_tx_बारtamp(skb);

	/* kick the DMA */
	smsc9420_reg_ग_लिखो(pd, TX_POLL_DEMAND, 1);
	smsc9420_pci_flush_ग_लिखो(pd);

	वापस NETDEV_TX_OK;
पूर्ण

अटल काष्ठा net_device_stats *smsc9420_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	u32 counter = smsc9420_reg_पढ़ो(pd, MISS_FRAME_CNTR);
	dev->stats.rx_dropped +=
	    (counter & 0x0000FFFF) + ((counter >> 17) & 0x000003FF);
	वापस &dev->stats;
पूर्ण

अटल व्योम smsc9420_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	u32 mac_cr = smsc9420_reg_पढ़ो(pd, MAC_CR);

	अगर (dev->flags & IFF_PROMISC) अणु
		netअगर_dbg(pd, hw, pd->dev, "Promiscuous Mode Enabled\n");
		mac_cr |= MAC_CR_PRMS_;
		mac_cr &= (~MAC_CR_MCPAS_);
		mac_cr &= (~MAC_CR_HPFILT_);
	पूर्ण अन्यथा अगर (dev->flags & IFF_ALLMULTI) अणु
		netअगर_dbg(pd, hw, pd->dev, "Receive all Multicast Enabled\n");
		mac_cr &= (~MAC_CR_PRMS_);
		mac_cr |= MAC_CR_MCPAS_;
		mac_cr &= (~MAC_CR_HPFILT_);
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु
		काष्ठा netdev_hw_addr *ha;
		u32 hash_lo = 0, hash_hi = 0;

		netअगर_dbg(pd, hw, pd->dev, "Multicast filter enabled\n");
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			u32 bit_num = smsc9420_hash(ha->addr);
			u32 mask = 1 << (bit_num & 0x1F);

			अगर (bit_num & 0x20)
				hash_hi |= mask;
			अन्यथा
				hash_lo |= mask;

		पूर्ण
		smsc9420_reg_ग_लिखो(pd, HASHH, hash_hi);
		smsc9420_reg_ग_लिखो(pd, HASHL, hash_lo);

		mac_cr &= (~MAC_CR_PRMS_);
		mac_cr &= (~MAC_CR_MCPAS_);
		mac_cr |= MAC_CR_HPFILT_;
	पूर्ण अन्यथा अणु
		netअगर_dbg(pd, hw, pd->dev, "Receive own packets only\n");
		smsc9420_reg_ग_लिखो(pd, HASHH, 0);
		smsc9420_reg_ग_लिखो(pd, HASHL, 0);

		mac_cr &= (~MAC_CR_PRMS_);
		mac_cr &= (~MAC_CR_MCPAS_);
		mac_cr &= (~MAC_CR_HPFILT_);
	पूर्ण

	smsc9420_reg_ग_लिखो(pd, MAC_CR, mac_cr);
	smsc9420_pci_flush_ग_लिखो(pd);
पूर्ण

अटल व्योम smsc9420_phy_update_flowcontrol(काष्ठा smsc9420_pdata *pd)
अणु
	काष्ठा net_device *dev = pd->dev;
	काष्ठा phy_device *phy_dev = dev->phydev;
	u32 flow;

	अगर (phy_dev->duplex == DUPLEX_FULL) अणु
		u16 lcladv = phy_पढ़ो(phy_dev, MII_ADVERTISE);
		u16 rmtadv = phy_पढ़ो(phy_dev, MII_LPA);
		u8 cap = mii_resolve_flowctrl_fdx(lcladv, rmtadv);

		अगर (cap & FLOW_CTRL_RX)
			flow = 0xFFFF0002;
		अन्यथा
			flow = 0;

		netअगर_info(pd, link, pd->dev, "rx pause %s, tx pause %s\n",
			   cap & FLOW_CTRL_RX ? "enabled" : "disabled",
			   cap & FLOW_CTRL_TX ? "enabled" : "disabled");
	पूर्ण अन्यथा अणु
		netअगर_info(pd, link, pd->dev, "half duplex\n");
		flow = 0;
	पूर्ण

	smsc9420_reg_ग_लिखो(pd, FLOW, flow);
पूर्ण

/* Update link mode अगर anything has changed.  Called periodically when the
 * PHY is in polling mode, even अगर nothing has changed. */
अटल व्योम smsc9420_phy_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	काष्ठा phy_device *phy_dev = dev->phydev;
	पूर्णांक carrier;

	अगर (phy_dev->duplex != pd->last_duplex) अणु
		u32 mac_cr = smsc9420_reg_पढ़ो(pd, MAC_CR);
		अगर (phy_dev->duplex) अणु
			netअगर_dbg(pd, link, pd->dev, "full duplex mode\n");
			mac_cr |= MAC_CR_FDPX_;
		पूर्ण अन्यथा अणु
			netअगर_dbg(pd, link, pd->dev, "half duplex mode\n");
			mac_cr &= ~MAC_CR_FDPX_;
		पूर्ण
		smsc9420_reg_ग_लिखो(pd, MAC_CR, mac_cr);

		smsc9420_phy_update_flowcontrol(pd);
		pd->last_duplex = phy_dev->duplex;
	पूर्ण

	carrier = netअगर_carrier_ok(dev);
	अगर (carrier != pd->last_carrier) अणु
		अगर (carrier)
			netअगर_dbg(pd, link, pd->dev, "carrier OK\n");
		अन्यथा
			netअगर_dbg(pd, link, pd->dev, "no carrier\n");
		pd->last_carrier = carrier;
	पूर्ण
पूर्ण

अटल पूर्णांक smsc9420_mii_probe(काष्ठा net_device *dev)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	काष्ठा phy_device *phydev = शून्य;

	BUG_ON(dev->phydev);

	/* Device only supports पूर्णांकernal PHY at address 1 */
	phydev = mdiobus_get_phy(pd->mii_bus, 1);
	अगर (!phydev) अणु
		netdev_err(dev, "no PHY found at address 1\n");
		वापस -ENODEV;
	पूर्ण

	phydev = phy_connect(dev, phydev_name(phydev),
			     smsc9420_phy_adjust_link, PHY_INTERFACE_MODE_MII);

	अगर (IS_ERR(phydev)) अणु
		netdev_err(dev, "Could not attach to PHY\n");
		वापस PTR_ERR(phydev);
	पूर्ण

	phy_set_max_speed(phydev, SPEED_100);

	/* mask with MAC supported features */
	phy_support_asym_छोड़ो(phydev);

	phy_attached_info(phydev);

	pd->last_duplex = -1;
	pd->last_carrier = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक smsc9420_mii_init(काष्ठा net_device *dev)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	पूर्णांक err = -ENXIO;

	pd->mii_bus = mdiobus_alloc();
	अगर (!pd->mii_bus) अणु
		err = -ENOMEM;
		जाओ err_out_1;
	पूर्ण
	pd->mii_bus->name = DRV_MDIONAME;
	snम_लिखो(pd->mii_bus->id, MII_BUS_ID_SIZE, "%x",
		(pd->pdev->bus->number << 8) | pd->pdev->devfn);
	pd->mii_bus->priv = pd;
	pd->mii_bus->पढ़ो = smsc9420_mii_पढ़ो;
	pd->mii_bus->ग_लिखो = smsc9420_mii_ग_लिखो;

	/* Mask all PHYs except ID 1 (पूर्णांकernal) */
	pd->mii_bus->phy_mask = ~(1 << 1);

	अगर (mdiobus_रेजिस्टर(pd->mii_bus)) अणु
		netअगर_warn(pd, probe, pd->dev, "Error registering mii bus\n");
		जाओ err_out_मुक्त_bus_2;
	पूर्ण

	अगर (smsc9420_mii_probe(dev) < 0) अणु
		netअगर_warn(pd, probe, pd->dev, "Error probing mii bus\n");
		जाओ err_out_unरेजिस्टर_bus_3;
	पूर्ण

	वापस 0;

err_out_unरेजिस्टर_bus_3:
	mdiobus_unरेजिस्टर(pd->mii_bus);
err_out_मुक्त_bus_2:
	mdiobus_मुक्त(pd->mii_bus);
err_out_1:
	वापस err;
पूर्ण

अटल पूर्णांक smsc9420_alloc_tx_ring(काष्ठा smsc9420_pdata *pd)
अणु
	पूर्णांक i;

	BUG_ON(!pd->tx_ring);

	pd->tx_buffers = kदो_स्मृति_array(TX_RING_SIZE,
				       माप(काष्ठा smsc9420_ring_info),
				       GFP_KERNEL);
	अगर (!pd->tx_buffers)
		वापस -ENOMEM;

	/* Initialize the TX Ring */
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		pd->tx_buffers[i].skb = शून्य;
		pd->tx_buffers[i].mapping = 0;
		pd->tx_ring[i].status = 0;
		pd->tx_ring[i].length = 0;
		pd->tx_ring[i].buffer1 = 0;
		pd->tx_ring[i].buffer2 = 0;
	पूर्ण
	pd->tx_ring[TX_RING_SIZE - 1].length = TDES1_TER_;
	wmb();

	pd->tx_ring_head = 0;
	pd->tx_ring_tail = 0;

	smsc9420_reg_ग_लिखो(pd, TX_BASE_ADDR, pd->tx_dma_addr);
	smsc9420_pci_flush_ग_लिखो(pd);

	वापस 0;
पूर्ण

अटल पूर्णांक smsc9420_alloc_rx_ring(काष्ठा smsc9420_pdata *pd)
अणु
	पूर्णांक i;

	BUG_ON(!pd->rx_ring);

	pd->rx_buffers = kदो_स्मृति_array(RX_RING_SIZE,
				       माप(काष्ठा smsc9420_ring_info),
				       GFP_KERNEL);
	अगर (pd->rx_buffers == शून्य)
		जाओ out;

	/* initialize the rx ring */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		pd->rx_ring[i].status = 0;
		pd->rx_ring[i].length = PKT_BUF_SZ;
		pd->rx_ring[i].buffer2 = 0;
		pd->rx_buffers[i].skb = शून्य;
		pd->rx_buffers[i].mapping = 0;
	पूर्ण
	pd->rx_ring[RX_RING_SIZE - 1].length = (PKT_BUF_SZ | RDES1_RER_);

	/* now allocate the entire ring of skbs */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		अगर (smsc9420_alloc_rx_buffer(pd, i)) अणु
			netअगर_warn(pd, अगरup, pd->dev,
				   "failed to allocate rx skb %d\n", i);
			जाओ out_मुक्त_rx_skbs;
		पूर्ण
	पूर्ण

	pd->rx_ring_head = 0;
	pd->rx_ring_tail = 0;

	smsc9420_reg_ग_लिखो(pd, VLAN1, ETH_P_8021Q);
	netअगर_dbg(pd, अगरup, pd->dev, "VLAN1 = 0x%08x\n",
		  smsc9420_reg_पढ़ो(pd, VLAN1));

	अगर (pd->rx_csum) अणु
		/* Enable RX COE */
		u32 coe = smsc9420_reg_पढ़ो(pd, COE_CR) | RX_COE_EN;
		smsc9420_reg_ग_लिखो(pd, COE_CR, coe);
		netअगर_dbg(pd, अगरup, pd->dev, "COE_CR = 0x%08x\n", coe);
	पूर्ण

	smsc9420_reg_ग_लिखो(pd, RX_BASE_ADDR, pd->rx_dma_addr);
	smsc9420_pci_flush_ग_लिखो(pd);

	वापस 0;

out_मुक्त_rx_skbs:
	smsc9420_मुक्त_rx_ring(pd);
out:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक smsc9420_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	u32 bus_mode, mac_cr, dmac_control, पूर्णांक_cfg, dma_पूर्णांकr_ena, पूर्णांक_ctl;
	स्थिर पूर्णांक irq = pd->pdev->irq;
	अचिन्हित दीर्घ flags;
	पूर्णांक result = 0, समयout;

	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		netअगर_warn(pd, अगरup, pd->dev,
			   "dev_addr is not a valid MAC address\n");
		result = -EADDRNOTAVAIL;
		जाओ out_0;
	पूर्ण

	netअगर_carrier_off(dev);

	/* disable, mask and acknowledge all पूर्णांकerrupts */
	spin_lock_irqsave(&pd->पूर्णांक_lock, flags);
	पूर्णांक_cfg = smsc9420_reg_पढ़ो(pd, INT_CFG) & (~INT_CFG_IRQ_EN_);
	smsc9420_reg_ग_लिखो(pd, INT_CFG, पूर्णांक_cfg);
	smsc9420_reg_ग_लिखो(pd, INT_CTL, 0);
	spin_unlock_irqrestore(&pd->पूर्णांक_lock, flags);
	smsc9420_reg_ग_लिखो(pd, DMAC_INTR_ENA, 0);
	smsc9420_reg_ग_लिखो(pd, INT_STAT, 0xFFFFFFFF);
	smsc9420_pci_flush_ग_लिखो(pd);

	result = request_irq(irq, smsc9420_isr, IRQF_SHARED, DRV_NAME, pd);
	अगर (result) अणु
		netअगर_warn(pd, अगरup, pd->dev, "Unable to use IRQ = %d\n", irq);
		result = -ENODEV;
		जाओ out_0;
	पूर्ण

	smsc9420_dmac_soft_reset(pd);

	/* make sure MAC_CR is sane */
	smsc9420_reg_ग_लिखो(pd, MAC_CR, 0);

	smsc9420_set_mac_address(dev);

	/* Configure GPIO pins to drive LEDs */
	smsc9420_reg_ग_लिखो(pd, GPIO_CFG,
		(GPIO_CFG_LED_3_ | GPIO_CFG_LED_2_ | GPIO_CFG_LED_1_));

	bus_mode = BUS_MODE_DMA_BURST_LENGTH_16;

#अगर_घोषित __BIG_ENDIAN
	bus_mode |= BUS_MODE_DBO_;
#पूर्ण_अगर

	smsc9420_reg_ग_लिखो(pd, BUS_MODE, bus_mode);

	smsc9420_pci_flush_ग_लिखो(pd);

	/* set bus master bridge arbitration priority क्रम Rx and TX DMA */
	smsc9420_reg_ग_लिखो(pd, BUS_CFG, BUS_CFG_RXTXWEIGHT_4_1);

	smsc9420_reg_ग_लिखो(pd, DMAC_CONTROL,
		(DMAC_CONTROL_SF_ | DMAC_CONTROL_OSF_));

	smsc9420_pci_flush_ग_लिखो(pd);

	/* test the IRQ connection to the ISR */
	netअगर_dbg(pd, अगरup, pd->dev, "Testing ISR using IRQ %d\n", irq);
	pd->software_irq_संकेत = false;

	spin_lock_irqsave(&pd->पूर्णांक_lock, flags);
	/* configure पूर्णांकerrupt deनिश्चितion समयr and enable पूर्णांकerrupts */
	पूर्णांक_cfg = smsc9420_reg_पढ़ो(pd, INT_CFG) | INT_CFG_IRQ_EN_;
	पूर्णांक_cfg &= ~(INT_CFG_INT_DEAS_MASK);
	पूर्णांक_cfg |= (INT_DEAS_TIME & INT_CFG_INT_DEAS_MASK);
	smsc9420_reg_ग_लिखो(pd, INT_CFG, पूर्णांक_cfg);

	/* unmask software पूर्णांकerrupt */
	पूर्णांक_ctl = smsc9420_reg_पढ़ो(pd, INT_CTL) | INT_CTL_SW_INT_EN_;
	smsc9420_reg_ग_लिखो(pd, INT_CTL, पूर्णांक_ctl);
	spin_unlock_irqrestore(&pd->पूर्णांक_lock, flags);
	smsc9420_pci_flush_ग_लिखो(pd);

	समयout = 1000;
	जबतक (समयout--) अणु
		अगर (pd->software_irq_संकेत)
			अवरोध;
		msleep(1);
	पूर्ण

	/* disable पूर्णांकerrupts */
	spin_lock_irqsave(&pd->पूर्णांक_lock, flags);
	पूर्णांक_cfg = smsc9420_reg_पढ़ो(pd, INT_CFG) & (~INT_CFG_IRQ_EN_);
	smsc9420_reg_ग_लिखो(pd, INT_CFG, पूर्णांक_cfg);
	spin_unlock_irqrestore(&pd->पूर्णांक_lock, flags);

	अगर (!pd->software_irq_संकेत) अणु
		netअगर_warn(pd, अगरup, pd->dev, "ISR failed signaling test\n");
		result = -ENODEV;
		जाओ out_मुक्त_irq_1;
	पूर्ण

	netअगर_dbg(pd, अगरup, pd->dev, "ISR passed test using IRQ %d\n", irq);

	result = smsc9420_alloc_tx_ring(pd);
	अगर (result) अणु
		netअगर_warn(pd, अगरup, pd->dev,
			   "Failed to Initialize tx dma ring\n");
		result = -ENOMEM;
		जाओ out_मुक्त_irq_1;
	पूर्ण

	result = smsc9420_alloc_rx_ring(pd);
	अगर (result) अणु
		netअगर_warn(pd, अगरup, pd->dev,
			   "Failed to Initialize rx dma ring\n");
		result = -ENOMEM;
		जाओ out_मुक्त_tx_ring_2;
	पूर्ण

	result = smsc9420_mii_init(dev);
	अगर (result) अणु
		netअगर_warn(pd, अगरup, pd->dev, "Failed to initialize Phy\n");
		result = -ENODEV;
		जाओ out_मुक्त_rx_ring_3;
	पूर्ण

	/* Bring the PHY up */
	phy_start(dev->phydev);

	napi_enable(&pd->napi);

	/* start tx and rx */
	mac_cr = smsc9420_reg_पढ़ो(pd, MAC_CR) | MAC_CR_TXEN_ | MAC_CR_RXEN_;
	smsc9420_reg_ग_लिखो(pd, MAC_CR, mac_cr);

	dmac_control = smsc9420_reg_पढ़ो(pd, DMAC_CONTROL);
	dmac_control |= DMAC_CONTROL_ST_ | DMAC_CONTROL_SR_;
	smsc9420_reg_ग_लिखो(pd, DMAC_CONTROL, dmac_control);
	smsc9420_pci_flush_ग_लिखो(pd);

	dma_पूर्णांकr_ena = smsc9420_reg_पढ़ो(pd, DMAC_INTR_ENA);
	dma_पूर्णांकr_ena |=
		(DMAC_INTR_ENA_TX_ | DMAC_INTR_ENA_RX_ | DMAC_INTR_ENA_NIS_);
	smsc9420_reg_ग_लिखो(pd, DMAC_INTR_ENA, dma_पूर्णांकr_ena);
	smsc9420_pci_flush_ग_लिखो(pd);

	netअगर_wake_queue(dev);

	smsc9420_reg_ग_लिखो(pd, RX_POLL_DEMAND, 1);

	/* enable पूर्णांकerrupts */
	spin_lock_irqsave(&pd->पूर्णांक_lock, flags);
	पूर्णांक_cfg = smsc9420_reg_पढ़ो(pd, INT_CFG) | INT_CFG_IRQ_EN_;
	smsc9420_reg_ग_लिखो(pd, INT_CFG, पूर्णांक_cfg);
	spin_unlock_irqrestore(&pd->पूर्णांक_lock, flags);

	वापस 0;

out_मुक्त_rx_ring_3:
	smsc9420_मुक्त_rx_ring(pd);
out_मुक्त_tx_ring_2:
	smsc9420_मुक्त_tx_ring(pd);
out_मुक्त_irq_1:
	मुक्त_irq(irq, pd);
out_0:
	वापस result;
पूर्ण

अटल पूर्णांक __maybe_unused smsc9420_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा smsc9420_pdata *pd = netdev_priv(dev);
	u32 पूर्णांक_cfg;
	uदीर्घ flags;

	/* disable पूर्णांकerrupts */
	spin_lock_irqsave(&pd->पूर्णांक_lock, flags);
	पूर्णांक_cfg = smsc9420_reg_पढ़ो(pd, INT_CFG) & (~INT_CFG_IRQ_EN_);
	smsc9420_reg_ग_लिखो(pd, INT_CFG, पूर्णांक_cfg);
	spin_unlock_irqrestore(&pd->पूर्णांक_lock, flags);

	अगर (netअगर_running(dev)) अणु
		netअगर_tx_disable(dev);
		smsc9420_stop_tx(pd);
		smsc9420_मुक्त_tx_ring(pd);

		napi_disable(&pd->napi);
		smsc9420_stop_rx(pd);
		smsc9420_मुक्त_rx_ring(pd);

		मुक्त_irq(pd->pdev->irq, pd);

		netअगर_device_detach(dev);
	पूर्ण

	device_wakeup_disable(dev_d);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused smsc9420_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	पूर्णांक err;

	pci_set_master(to_pci_dev(dev_d));

	device_wakeup_disable(dev_d);

	err = 0;
	अगर (netअगर_running(dev)) अणु
		/* FIXME: gross. It looks like ancient PM relic.*/
		err = smsc9420_खोलो(dev);
		netअगर_device_attach(dev);
	पूर्ण
	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_device_ops smsc9420_netdev_ops = अणु
	.nकरो_खोलो		= smsc9420_खोलो,
	.nकरो_stop		= smsc9420_stop,
	.nकरो_start_xmit		= smsc9420_hard_start_xmit,
	.nकरो_get_stats		= smsc9420_get_stats,
	.nकरो_set_rx_mode	= smsc9420_set_multicast_list,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= smsc9420_poll_controller,
#पूर्ण_अगर /* CONFIG_NET_POLL_CONTROLLER */
पूर्ण;

अटल पूर्णांक
smsc9420_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा net_device *dev;
	काष्ठा smsc9420_pdata *pd;
	व्योम __iomem *virt_addr;
	पूर्णांक result = 0;
	u32 id_rev;

	pr_info("%s version %s\n", DRV_DESCRIPTION, DRV_VERSION);

	/* First करो the PCI initialisation */
	result = pci_enable_device(pdev);
	अगर (unlikely(result)) अणु
		pr_err("Cannot enable smsc9420\n");
		जाओ out_0;
	पूर्ण

	pci_set_master(pdev);

	dev = alloc_etherdev(माप(*pd));
	अगर (!dev)
		जाओ out_disable_pci_device_1;

	SET_NETDEV_DEV(dev, &pdev->dev);

	अगर (!(pci_resource_flags(pdev, SMSC_BAR) & IORESOURCE_MEM)) अणु
		netdev_err(dev, "Cannot find PCI device base address\n");
		जाओ out_मुक्त_netdev_2;
	पूर्ण

	अगर ((pci_request_regions(pdev, DRV_NAME))) अणु
		netdev_err(dev, "Cannot obtain PCI resources, aborting\n");
		जाओ out_मुक्त_netdev_2;
	पूर्ण

	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		netdev_err(dev, "No usable DMA configuration, aborting\n");
		जाओ out_मुक्त_regions_3;
	पूर्ण

	virt_addr = ioremap(pci_resource_start(pdev, SMSC_BAR),
		pci_resource_len(pdev, SMSC_BAR));
	अगर (!virt_addr) अणु
		netdev_err(dev, "Cannot map device registers, aborting\n");
		जाओ out_मुक्त_regions_3;
	पूर्ण

	/* रेजिस्टरs are द्विगुन mapped with 0 offset क्रम LE and 0x200 क्रम BE */
	virt_addr += LAN9420_CPSR_ENDIAN_OFFSET;

	pd = netdev_priv(dev);

	/* pci descriptors are created in the PCI consistent area */
	pd->rx_ring = dma_alloc_coherent(&pdev->dev,
		माप(काष्ठा smsc9420_dma_desc) * (RX_RING_SIZE + TX_RING_SIZE),
		&pd->rx_dma_addr, GFP_KERNEL);

	अगर (!pd->rx_ring)
		जाओ out_मुक्त_io_4;

	/* descriptors are aligned due to the nature of pci_alloc_consistent */
	pd->tx_ring = (pd->rx_ring + RX_RING_SIZE);
	pd->tx_dma_addr = pd->rx_dma_addr +
	    माप(काष्ठा smsc9420_dma_desc) * RX_RING_SIZE;

	pd->pdev = pdev;
	pd->dev = dev;
	pd->ioaddr = virt_addr;
	pd->msg_enable = smsc_debug;
	pd->rx_csum = true;

	netअगर_dbg(pd, probe, pd->dev, "lan_base=0x%08lx\n", (uदीर्घ)virt_addr);

	id_rev = smsc9420_reg_पढ़ो(pd, ID_REV);
	चयन (id_rev & 0xFFFF0000) अणु
	हाल 0x94200000:
		netअगर_info(pd, probe, pd->dev,
			   "LAN9420 identified, ID_REV=0x%08X\n", id_rev);
		अवरोध;
	शेष:
		netअगर_warn(pd, probe, pd->dev, "LAN9420 NOT identified\n");
		netअगर_warn(pd, probe, pd->dev, "ID_REV=0x%08X\n", id_rev);
		जाओ out_मुक्त_dmadesc_5;
	पूर्ण

	smsc9420_dmac_soft_reset(pd);
	smsc9420_eeprom_reload(pd);
	smsc9420_check_mac_address(dev);

	dev->netdev_ops = &smsc9420_netdev_ops;
	dev->ethtool_ops = &smsc9420_ethtool_ops;

	netअगर_napi_add(dev, &pd->napi, smsc9420_rx_poll, NAPI_WEIGHT);

	result = रेजिस्टर_netdev(dev);
	अगर (result) अणु
		netअगर_warn(pd, probe, pd->dev, "error %i registering device\n",
			   result);
		जाओ out_मुक्त_dmadesc_5;
	पूर्ण

	pci_set_drvdata(pdev, dev);

	spin_lock_init(&pd->पूर्णांक_lock);
	spin_lock_init(&pd->phy_lock);

	dev_info(&dev->dev, "MAC Address: %pM\n", dev->dev_addr);

	वापस 0;

out_मुक्त_dmadesc_5:
	dma_मुक्त_coherent(&pdev->dev,
			  माप(काष्ठा smsc9420_dma_desc) * (RX_RING_SIZE + TX_RING_SIZE),
			  pd->rx_ring, pd->rx_dma_addr);
out_मुक्त_io_4:
	iounmap(virt_addr - LAN9420_CPSR_ENDIAN_OFFSET);
out_मुक्त_regions_3:
	pci_release_regions(pdev);
out_मुक्त_netdev_2:
	मुक्त_netdev(dev);
out_disable_pci_device_1:
	pci_disable_device(pdev);
out_0:
	वापस -ENODEV;
पूर्ण

अटल व्योम smsc9420_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा smsc9420_pdata *pd;

	dev = pci_get_drvdata(pdev);
	अगर (!dev)
		वापस;

	pd = netdev_priv(dev);
	unरेजिस्टर_netdev(dev);

	/* tx_buffers and rx_buffers are मुक्तd in stop */
	BUG_ON(pd->tx_buffers);
	BUG_ON(pd->rx_buffers);

	BUG_ON(!pd->tx_ring);
	BUG_ON(!pd->rx_ring);

	dma_मुक्त_coherent(&pdev->dev,
			  माप(काष्ठा smsc9420_dma_desc) * (RX_RING_SIZE + TX_RING_SIZE),
			  pd->rx_ring, pd->rx_dma_addr);

	iounmap(pd->ioaddr - LAN9420_CPSR_ENDIAN_OFFSET);
	pci_release_regions(pdev);
	मुक्त_netdev(dev);
	pci_disable_device(pdev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(smsc9420_pm_ops, smsc9420_suspend, smsc9420_resume);

अटल काष्ठा pci_driver smsc9420_driver = अणु
	.name = DRV_NAME,
	.id_table = smsc9420_id_table,
	.probe = smsc9420_probe,
	.हटाओ = smsc9420_हटाओ,
	.driver.pm = &smsc9420_pm_ops,
पूर्ण;

अटल पूर्णांक __init smsc9420_init_module(व्योम)
अणु
	smsc_debug = netअगर_msg_init(debug, SMSC_MSG_DEFAULT);

	वापस pci_रेजिस्टर_driver(&smsc9420_driver);
पूर्ण

अटल व्योम __निकास smsc9420_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&smsc9420_driver);
पूर्ण

module_init(smsc9420_init_module);
module_निकास(smsc9420_निकास_module);
