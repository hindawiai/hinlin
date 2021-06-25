<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /***************************************************************************
 *
 * Copyright (C) 2007-2008 SMSC
 *
 *****************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/kmod.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/crc16.h>
#समावेश <linux/crc32.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_net.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/phy.h>
#समावेश "smsc95xx.h"

#घोषणा SMSC_CHIPNAME			"smsc95xx"
#घोषणा SMSC_DRIVER_VERSION		"2.0.0"
#घोषणा HS_USB_PKT_SIZE			(512)
#घोषणा FS_USB_PKT_SIZE			(64)
#घोषणा DEFAULT_HS_BURST_CAP_SIZE	(16 * 1024 + 5 * HS_USB_PKT_SIZE)
#घोषणा DEFAULT_FS_BURST_CAP_SIZE	(6 * 1024 + 33 * FS_USB_PKT_SIZE)
#घोषणा DEFAULT_BULK_IN_DELAY		(0x00002000)
#घोषणा MAX_SINGLE_PACKET_SIZE		(2048)
#घोषणा LAN95XX_EEPROM_MAGIC		(0x9500)
#घोषणा EEPROM_MAC_OFFSET		(0x01)
#घोषणा DEFAULT_TX_CSUM_ENABLE		(true)
#घोषणा DEFAULT_RX_CSUM_ENABLE		(true)
#घोषणा SMSC95XX_INTERNAL_PHY_ID	(1)
#घोषणा SMSC95XX_TX_OVERHEAD		(8)
#घोषणा SMSC95XX_TX_OVERHEAD_CSUM	(12)
#घोषणा SUPPORTED_WAKE			(WAKE_PHY | WAKE_UCAST | WAKE_BCAST | \
					 WAKE_MCAST | WAKE_ARP | WAKE_MAGIC)

#घोषणा FEATURE_8_WAKEUP_FILTERS	(0x01)
#घोषणा FEATURE_PHY_NLP_CROSSOVER	(0x02)
#घोषणा FEATURE_REMOTE_WAKEUP		(0x04)

#घोषणा SUSPEND_SUSPEND0		(0x01)
#घोषणा SUSPEND_SUSPEND1		(0x02)
#घोषणा SUSPEND_SUSPEND2		(0x04)
#घोषणा SUSPEND_SUSPEND3		(0x08)
#घोषणा SUSPEND_ALLMODES		(SUSPEND_SUSPEND0 | SUSPEND_SUSPEND1 | \
					 SUSPEND_SUSPEND2 | SUSPEND_SUSPEND3)

काष्ठा smsc95xx_priv अणु
	u32 mac_cr;
	u32 hash_hi;
	u32 hash_lo;
	u32 wolopts;
	spinlock_t mac_cr_lock;
	u8 features;
	u8 suspend_flags;
	काष्ठा mii_bus *mdiobus;
	काष्ठा phy_device *phydev;
पूर्ण;

अटल bool turbo_mode = true;
module_param(turbo_mode, bool, 0644);
MODULE_PARM_DESC(turbo_mode, "Enable multiple frames per Rx transaction");

अटल पूर्णांक __must_check __smsc95xx_पढ़ो_reg(काष्ठा usbnet *dev, u32 index,
					    u32 *data, पूर्णांक in_pm)
अणु
	u32 buf;
	पूर्णांक ret;
	पूर्णांक (*fn)(काष्ठा usbnet *, u8, u8, u16, u16, व्योम *, u16);

	BUG_ON(!dev);

	अगर (!in_pm)
		fn = usbnet_पढ़ो_cmd;
	अन्यथा
		fn = usbnet_पढ़ो_cmd_nopm;

	ret = fn(dev, USB_VENDOR_REQUEST_READ_REGISTER, USB_सूची_IN
		 | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		 0, index, &buf, 4);
	अगर (unlikely(ret < 0)) अणु
		netdev_warn(dev->net, "Failed to read reg index 0x%08x: %d\n",
			    index, ret);
		वापस ret;
	पूर्ण

	le32_to_cpus(&buf);
	*data = buf;

	वापस ret;
पूर्ण

अटल पूर्णांक __must_check __smsc95xx_ग_लिखो_reg(काष्ठा usbnet *dev, u32 index,
					     u32 data, पूर्णांक in_pm)
अणु
	u32 buf;
	पूर्णांक ret;
	पूर्णांक (*fn)(काष्ठा usbnet *, u8, u8, u16, u16, स्थिर व्योम *, u16);

	BUG_ON(!dev);

	अगर (!in_pm)
		fn = usbnet_ग_लिखो_cmd;
	अन्यथा
		fn = usbnet_ग_लिखो_cmd_nopm;

	buf = data;
	cpu_to_le32s(&buf);

	ret = fn(dev, USB_VENDOR_REQUEST_WRITE_REGISTER, USB_सूची_OUT
		 | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		 0, index, &buf, 4);
	अगर (unlikely(ret < 0))
		netdev_warn(dev->net, "Failed to write reg index 0x%08x: %d\n",
			    index, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक __must_check smsc95xx_पढ़ो_reg_nopm(काष्ठा usbnet *dev, u32 index,
					       u32 *data)
अणु
	वापस __smsc95xx_पढ़ो_reg(dev, index, data, 1);
पूर्ण

अटल पूर्णांक __must_check smsc95xx_ग_लिखो_reg_nopm(काष्ठा usbnet *dev, u32 index,
						u32 data)
अणु
	वापस __smsc95xx_ग_लिखो_reg(dev, index, data, 1);
पूर्ण

अटल पूर्णांक __must_check smsc95xx_पढ़ो_reg(काष्ठा usbnet *dev, u32 index,
					  u32 *data)
अणु
	वापस __smsc95xx_पढ़ो_reg(dev, index, data, 0);
पूर्ण

अटल पूर्णांक __must_check smsc95xx_ग_लिखो_reg(काष्ठा usbnet *dev, u32 index,
					   u32 data)
अणु
	वापस __smsc95xx_ग_लिखो_reg(dev, index, data, 0);
पूर्ण

/* Loop until the पढ़ो is completed with समयout
 * called with phy_mutex held */
अटल पूर्णांक __must_check __smsc95xx_phy_रुको_not_busy(काष्ठा usbnet *dev,
						     पूर्णांक in_pm)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;
	u32 val;
	पूर्णांक ret;

	करो अणु
		ret = __smsc95xx_पढ़ो_reg(dev, MII_ADDR, &val, in_pm);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading MII_ACCESS\n");
			वापस ret;
		पूर्ण

		अगर (!(val & MII_BUSY_))
			वापस 0;
	पूर्ण जबतक (!समय_after(jअगरfies, start_समय + HZ));

	वापस -EIO;
पूर्ण

अटल u32 mii_address_cmd(पूर्णांक phy_id, पूर्णांक idx, u16 op)
अणु
	वापस (phy_id & 0x1f) << 11 | (idx & 0x1f) << 6 | op;
पूर्ण

अटल पूर्णांक __smsc95xx_mdio_पढ़ो(काष्ठा usbnet *dev, पूर्णांक phy_id, पूर्णांक idx,
				पूर्णांक in_pm)
अणु
	u32 val, addr;
	पूर्णांक ret;

	mutex_lock(&dev->phy_mutex);

	/* confirm MII not busy */
	ret = __smsc95xx_phy_रुको_not_busy(dev, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "%s: MII is busy\n", __func__);
		जाओ करोne;
	पूर्ण

	/* set the address, index & direction (पढ़ो from PHY) */
	addr = mii_address_cmd(phy_id, idx, MII_READ_ | MII_BUSY_);
	ret = __smsc95xx_ग_लिखो_reg(dev, MII_ADDR, addr, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing MII_ADDR\n");
		जाओ करोne;
	पूर्ण

	ret = __smsc95xx_phy_रुको_not_busy(dev, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Timed out reading MII reg %02X\n", idx);
		जाओ करोne;
	पूर्ण

	ret = __smsc95xx_पढ़ो_reg(dev, MII_DATA, &val, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading MII_DATA\n");
		जाओ करोne;
	पूर्ण

	ret = (u16)(val & 0xFFFF);

करोne:
	mutex_unlock(&dev->phy_mutex);
	वापस ret;
पूर्ण

अटल व्योम __smsc95xx_mdio_ग_लिखो(काष्ठा usbnet *dev, पूर्णांक phy_id,
				  पूर्णांक idx, पूर्णांक regval, पूर्णांक in_pm)
अणु
	u32 val, addr;
	पूर्णांक ret;

	mutex_lock(&dev->phy_mutex);

	/* confirm MII not busy */
	ret = __smsc95xx_phy_रुको_not_busy(dev, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "%s: MII is busy\n", __func__);
		जाओ करोne;
	पूर्ण

	val = regval;
	ret = __smsc95xx_ग_लिखो_reg(dev, MII_DATA, val, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing MII_DATA\n");
		जाओ करोne;
	पूर्ण

	/* set the address, index & direction (ग_लिखो to PHY) */
	addr = mii_address_cmd(phy_id, idx, MII_WRITE_ | MII_BUSY_);
	ret = __smsc95xx_ग_लिखो_reg(dev, MII_ADDR, addr, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing MII_ADDR\n");
		जाओ करोne;
	पूर्ण

	ret = __smsc95xx_phy_रुको_not_busy(dev, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Timed out writing MII reg %02X\n", idx);
		जाओ करोne;
	पूर्ण

करोne:
	mutex_unlock(&dev->phy_mutex);
पूर्ण

अटल पूर्णांक smsc95xx_mdio_पढ़ो_nopm(काष्ठा usbnet *dev, पूर्णांक idx)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;

	वापस __smsc95xx_mdio_पढ़ो(dev, pdata->phydev->mdio.addr, idx, 1);
पूर्ण

अटल व्योम smsc95xx_mdio_ग_लिखो_nopm(काष्ठा usbnet *dev, पूर्णांक idx, पूर्णांक regval)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;

	__smsc95xx_mdio_ग_लिखो(dev, pdata->phydev->mdio.addr, idx, regval, 1);
पूर्ण

अटल पूर्णांक smsc95xx_mdiobus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक idx)
अणु
	काष्ठा usbnet *dev = bus->priv;

	वापस __smsc95xx_mdio_पढ़ो(dev, phy_id, idx, 0);
पूर्ण

अटल पूर्णांक smsc95xx_mdiobus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक idx,
				  u16 regval)
अणु
	काष्ठा usbnet *dev = bus->priv;

	__smsc95xx_mdio_ग_लिखो(dev, phy_id, idx, regval, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक __must_check smsc95xx_रुको_eeprom(काष्ठा usbnet *dev)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;
	u32 val;
	पूर्णांक ret;

	करो अणु
		ret = smsc95xx_पढ़ो_reg(dev, E2P_CMD, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading E2P_CMD\n");
			वापस ret;
		पूर्ण

		अगर (!(val & E2P_CMD_BUSY_) || (val & E2P_CMD_TIMEOUT_))
			अवरोध;
		udelay(40);
	पूर्ण जबतक (!समय_after(jअगरfies, start_समय + HZ));

	अगर (val & (E2P_CMD_TIMEOUT_ | E2P_CMD_BUSY_)) अणु
		netdev_warn(dev->net, "EEPROM read operation timeout\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __must_check smsc95xx_eeprom_confirm_not_busy(काष्ठा usbnet *dev)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;
	u32 val;
	पूर्णांक ret;

	करो अणु
		ret = smsc95xx_पढ़ो_reg(dev, E2P_CMD, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading E2P_CMD\n");
			वापस ret;
		पूर्ण

		अगर (!(val & E2P_CMD_BUSY_))
			वापस 0;

		udelay(40);
	पूर्ण जबतक (!समय_after(jअगरfies, start_समय + HZ));

	netdev_warn(dev->net, "EEPROM is busy\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक smsc95xx_पढ़ो_eeprom(काष्ठा usbnet *dev, u32 offset, u32 length,
				u8 *data)
अणु
	u32 val;
	पूर्णांक i, ret;

	BUG_ON(!dev);
	BUG_ON(!data);

	ret = smsc95xx_eeprom_confirm_not_busy(dev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < length; i++) अणु
		val = E2P_CMD_BUSY_ | E2P_CMD_READ_ | (offset & E2P_CMD_ADDR_);
		ret = smsc95xx_ग_लिखो_reg(dev, E2P_CMD, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing E2P_CMD\n");
			वापस ret;
		पूर्ण

		ret = smsc95xx_रुको_eeprom(dev);
		अगर (ret < 0)
			वापस ret;

		ret = smsc95xx_पढ़ो_reg(dev, E2P_DATA, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading E2P_DATA\n");
			वापस ret;
		पूर्ण

		data[i] = val & 0xFF;
		offset++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smsc95xx_ग_लिखो_eeprom(काष्ठा usbnet *dev, u32 offset, u32 length,
				 u8 *data)
अणु
	u32 val;
	पूर्णांक i, ret;

	BUG_ON(!dev);
	BUG_ON(!data);

	ret = smsc95xx_eeprom_confirm_not_busy(dev);
	अगर (ret)
		वापस ret;

	/* Issue ग_लिखो/erase enable command */
	val = E2P_CMD_BUSY_ | E2P_CMD_EWEN_;
	ret = smsc95xx_ग_लिखो_reg(dev, E2P_CMD, val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing E2P_DATA\n");
		वापस ret;
	पूर्ण

	ret = smsc95xx_रुको_eeprom(dev);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < length; i++) अणु

		/* Fill data रेजिस्टर */
		val = data[i];
		ret = smsc95xx_ग_लिखो_reg(dev, E2P_DATA, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing E2P_DATA\n");
			वापस ret;
		पूर्ण

		/* Send "write" command */
		val = E2P_CMD_BUSY_ | E2P_CMD_WRITE_ | (offset & E2P_CMD_ADDR_);
		ret = smsc95xx_ग_लिखो_reg(dev, E2P_CMD, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing E2P_CMD\n");
			वापस ret;
		पूर्ण

		ret = smsc95xx_रुको_eeprom(dev);
		अगर (ret < 0)
			वापस ret;

		offset++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __must_check smsc95xx_ग_लिखो_reg_async(काष्ठा usbnet *dev, u16 index,
						 u32 data)
अणु
	स्थिर u16 size = 4;
	u32 buf;
	पूर्णांक ret;

	buf = data;
	cpu_to_le32s(&buf);

	ret = usbnet_ग_लिखो_cmd_async(dev, USB_VENDOR_REQUEST_WRITE_REGISTER,
				     USB_सूची_OUT | USB_TYPE_VENDOR |
				     USB_RECIP_DEVICE,
				     0, index, &buf, size);
	अगर (ret < 0)
		netdev_warn(dev->net, "Error write async cmd, sts=%d\n",
			    ret);
	वापस ret;
पूर्ण

/* वापसs hash bit number क्रम given MAC address
 * example:
 * 01 00 5E 00 00 01 -> वापसs bit number 31 */
अटल अचिन्हित पूर्णांक smsc95xx_hash(अक्षर addr[ETH_ALEN])
अणु
	वापस (ether_crc(ETH_ALEN, addr) >> 26) & 0x3f;
पूर्ण

अटल व्योम smsc95xx_set_multicast(काष्ठा net_device *netdev)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	pdata->hash_hi = 0;
	pdata->hash_lo = 0;

	spin_lock_irqsave(&pdata->mac_cr_lock, flags);

	अगर (dev->net->flags & IFF_PROMISC) अणु
		netअगर_dbg(dev, drv, dev->net, "promiscuous mode enabled\n");
		pdata->mac_cr |= MAC_CR_PRMS_;
		pdata->mac_cr &= ~(MAC_CR_MCPAS_ | MAC_CR_HPFILT_);
	पूर्ण अन्यथा अगर (dev->net->flags & IFF_ALLMULTI) अणु
		netअगर_dbg(dev, drv, dev->net, "receive all multicast enabled\n");
		pdata->mac_cr |= MAC_CR_MCPAS_;
		pdata->mac_cr &= ~(MAC_CR_PRMS_ | MAC_CR_HPFILT_);
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev->net)) अणु
		काष्ठा netdev_hw_addr *ha;

		pdata->mac_cr |= MAC_CR_HPFILT_;
		pdata->mac_cr &= ~(MAC_CR_PRMS_ | MAC_CR_MCPAS_);

		netdev_क्रम_each_mc_addr(ha, netdev) अणु
			u32 bitnum = smsc95xx_hash(ha->addr);
			u32 mask = 0x01 << (bitnum & 0x1F);
			अगर (bitnum & 0x20)
				pdata->hash_hi |= mask;
			अन्यथा
				pdata->hash_lo |= mask;
		पूर्ण

		netअगर_dbg(dev, drv, dev->net, "HASHH=0x%08X, HASHL=0x%08X\n",
				   pdata->hash_hi, pdata->hash_lo);
	पूर्ण अन्यथा अणु
		netअगर_dbg(dev, drv, dev->net, "receive own packets only\n");
		pdata->mac_cr &=
			~(MAC_CR_PRMS_ | MAC_CR_MCPAS_ | MAC_CR_HPFILT_);
	पूर्ण

	spin_unlock_irqrestore(&pdata->mac_cr_lock, flags);

	/* Initiate async ग_लिखोs, as we can't रुको क्रम completion here */
	ret = smsc95xx_ग_लिखो_reg_async(dev, HASHH, pdata->hash_hi);
	अगर (ret < 0)
		netdev_warn(dev->net, "failed to initiate async write to HASHH\n");

	ret = smsc95xx_ग_लिखो_reg_async(dev, HASHL, pdata->hash_lo);
	अगर (ret < 0)
		netdev_warn(dev->net, "failed to initiate async write to HASHL\n");

	ret = smsc95xx_ग_लिखो_reg_async(dev, MAC_CR, pdata->mac_cr);
	अगर (ret < 0)
		netdev_warn(dev->net, "failed to initiate async write to MAC_CR\n");
पूर्ण

अटल पूर्णांक smsc95xx_phy_update_flowcontrol(काष्ठा usbnet *dev)
अणु
	u32 flow = 0, afc_cfg;
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	bool tx_छोड़ो, rx_छोड़ो;

	पूर्णांक ret = smsc95xx_पढ़ो_reg(dev, AFC_CFG, &afc_cfg);
	अगर (ret < 0)
		वापस ret;

	अगर (pdata->phydev->duplex == DUPLEX_FULL) अणु
		phy_get_छोड़ो(pdata->phydev, &tx_छोड़ो, &rx_छोड़ो);

		अगर (rx_छोड़ो)
			flow = 0xFFFF0002;

		अगर (tx_छोड़ो) अणु
			afc_cfg |= 0xF;
			flow |= 0xFFFF0000;
		पूर्ण अन्यथा अणु
			afc_cfg &= ~0xF;
		पूर्ण

		netअगर_dbg(dev, link, dev->net, "rx pause %s, tx pause %s\n",
			  rx_छोड़ो ? "enabled" : "disabled",
			  tx_छोड़ो ? "enabled" : "disabled");
	पूर्ण अन्यथा अणु
		netअगर_dbg(dev, link, dev->net, "half duplex\n");
		afc_cfg |= 0xF;
	पूर्ण

	ret = smsc95xx_ग_लिखो_reg(dev, FLOW, flow);
	अगर (ret < 0)
		वापस ret;

	वापस smsc95xx_ग_लिखो_reg(dev, AFC_CFG, afc_cfg);
पूर्ण

अटल पूर्णांक smsc95xx_link_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = smsc95xx_ग_लिखो_reg(dev, INT_STS, INT_STS_CLEAR_ALL_);
	अगर (ret < 0)
		वापस ret;

	spin_lock_irqsave(&pdata->mac_cr_lock, flags);
	अगर (pdata->phydev->duplex != DUPLEX_FULL) अणु
		pdata->mac_cr &= ~MAC_CR_FDPX_;
		pdata->mac_cr |= MAC_CR_RCVOWN_;
	पूर्ण अन्यथा अणु
		pdata->mac_cr &= ~MAC_CR_RCVOWN_;
		pdata->mac_cr |= MAC_CR_FDPX_;
	पूर्ण
	spin_unlock_irqrestore(&pdata->mac_cr_lock, flags);

	ret = smsc95xx_ग_लिखो_reg(dev, MAC_CR, pdata->mac_cr);
	अगर (ret < 0)
		वापस ret;

	ret = smsc95xx_phy_update_flowcontrol(dev);
	अगर (ret < 0)
		netdev_warn(dev->net, "Error updating PHY flow control\n");

	वापस ret;
पूर्ण

अटल व्योम smsc95xx_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	u32 पूर्णांकdata;

	अगर (urb->actual_length != 4) अणु
		netdev_warn(dev->net, "unexpected urb length %d\n",
			    urb->actual_length);
		वापस;
	पूर्ण

	पूर्णांकdata = get_unaligned_le32(urb->transfer_buffer);
	netअगर_dbg(dev, link, dev->net, "intdata: 0x%08X\n", पूर्णांकdata);

	अगर (पूर्णांकdata & INT_ENP_PHY_INT_)
		usbnet_defer_kevent(dev, EVENT_LINK_RESET);
	अन्यथा
		netdev_warn(dev->net, "unexpected interrupt, intdata=0x%08X\n",
			    पूर्णांकdata);
पूर्ण

/* Enable or disable Tx & Rx checksum offload engines */
अटल पूर्णांक smsc95xx_set_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	u32 पढ़ो_buf;
	पूर्णांक ret;

	ret = smsc95xx_पढ़ो_reg(dev, COE_CR, &पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	अगर (features & NETIF_F_IP_CSUM)
		पढ़ो_buf |= Tx_COE_EN_;
	अन्यथा
		पढ़ो_buf &= ~Tx_COE_EN_;

	अगर (features & NETIF_F_RXCSUM)
		पढ़ो_buf |= Rx_COE_EN_;
	अन्यथा
		पढ़ो_buf &= ~Rx_COE_EN_;

	ret = smsc95xx_ग_लिखो_reg(dev, COE_CR, पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	netअगर_dbg(dev, hw, dev->net, "COE_CR = 0x%08x\n", पढ़ो_buf);
	वापस 0;
पूर्ण

अटल पूर्णांक smsc95xx_ethtool_get_eeprom_len(काष्ठा net_device *net)
अणु
	वापस MAX_EEPROM_SIZE;
पूर्ण

अटल पूर्णांक smsc95xx_ethtool_get_eeprom(काष्ठा net_device *netdev,
				       काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);

	ee->magic = LAN95XX_EEPROM_MAGIC;

	वापस smsc95xx_पढ़ो_eeprom(dev, ee->offset, ee->len, data);
पूर्ण

अटल पूर्णांक smsc95xx_ethtool_set_eeprom(काष्ठा net_device *netdev,
				       काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);

	अगर (ee->magic != LAN95XX_EEPROM_MAGIC) अणु
		netdev_warn(dev->net, "EEPROM: magic value mismatch, magic = 0x%x\n",
			    ee->magic);
		वापस -EINVAL;
	पूर्ण

	वापस smsc95xx_ग_लिखो_eeprom(dev, ee->offset, ee->len, data);
पूर्ण

अटल पूर्णांक smsc95xx_ethtool_getregslen(काष्ठा net_device *netdev)
अणु
	/* all smsc95xx रेजिस्टरs */
	वापस COE_CR - ID_REV + माप(u32);
पूर्ण

अटल व्योम
smsc95xx_ethtool_getregs(काष्ठा net_device *netdev, काष्ठा ethtool_regs *regs,
			 व्योम *buf)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	अचिन्हित पूर्णांक i, j;
	पूर्णांक retval;
	u32 *data = buf;

	retval = smsc95xx_पढ़ो_reg(dev, ID_REV, &regs->version);
	अगर (retval < 0) अणु
		netdev_warn(netdev, "REGS: cannot read ID_REV\n");
		वापस;
	पूर्ण

	क्रम (i = ID_REV, j = 0; i <= COE_CR; i += (माप(u32)), j++) अणु
		retval = smsc95xx_पढ़ो_reg(dev, i, &data[j]);
		अगर (retval < 0) अणु
			netdev_warn(netdev, "REGS: cannot read reg[%x]\n", i);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम smsc95xx_ethtool_get_wol(काष्ठा net_device *net,
				     काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;

	wolinfo->supported = SUPPORTED_WAKE;
	wolinfo->wolopts = pdata->wolopts;
पूर्ण

अटल पूर्णांक smsc95xx_ethtool_set_wol(काष्ठा net_device *net,
				    काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	पूर्णांक ret;

	अगर (wolinfo->wolopts & ~SUPPORTED_WAKE)
		वापस -EINVAL;

	pdata->wolopts = wolinfo->wolopts & SUPPORTED_WAKE;

	ret = device_set_wakeup_enable(&dev->udev->dev, pdata->wolopts);
	अगर (ret < 0)
		netdev_warn(dev->net, "device_set_wakeup_enable error %d\n", ret);

	वापस ret;
पूर्ण

अटल u32 smsc95xx_get_link(काष्ठा net_device *net)
अणु
	phy_पढ़ो_status(net->phydev);
	वापस net->phydev->link;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops smsc95xx_ethtool_ops = अणु
	.get_link	= smsc95xx_get_link,
	.nway_reset	= phy_ethtool_nway_reset,
	.get_drvinfo	= usbnet_get_drvinfo,
	.get_msglevel	= usbnet_get_msglevel,
	.set_msglevel	= usbnet_set_msglevel,
	.get_eeprom_len	= smsc95xx_ethtool_get_eeprom_len,
	.get_eeprom	= smsc95xx_ethtool_get_eeprom,
	.set_eeprom	= smsc95xx_ethtool_set_eeprom,
	.get_regs_len	= smsc95xx_ethtool_getregslen,
	.get_regs	= smsc95xx_ethtool_getregs,
	.get_wol	= smsc95xx_ethtool_get_wol,
	.set_wol	= smsc95xx_ethtool_set_wol,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
	.get_ts_info	= ethtool_op_get_ts_info,
पूर्ण;

अटल पूर्णांक smsc95xx_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	अगर (!netअगर_running(netdev))
		वापस -EINVAL;

	वापस phy_mii_ioctl(netdev->phydev, rq, cmd);
पूर्ण

अटल व्योम smsc95xx_init_mac_address(काष्ठा usbnet *dev)
अणु
	/* maybe the boot loader passed the MAC address in devicetree */
	अगर (!eth_platक्रमm_get_mac_address(&dev->udev->dev,
			dev->net->dev_addr)) अणु
		अगर (is_valid_ether_addr(dev->net->dev_addr)) अणु
			/* device tree values are valid so use them */
			netअगर_dbg(dev, अगरup, dev->net, "MAC address read from the device tree\n");
			वापस;
		पूर्ण
	पूर्ण

	/* try पढ़ोing mac address from EEPROM */
	अगर (smsc95xx_पढ़ो_eeprom(dev, EEPROM_MAC_OFFSET, ETH_ALEN,
			dev->net->dev_addr) == 0) अणु
		अगर (is_valid_ether_addr(dev->net->dev_addr)) अणु
			/* eeprom values are valid so use them */
			netअगर_dbg(dev, अगरup, dev->net, "MAC address read from EEPROM\n");
			वापस;
		पूर्ण
	पूर्ण

	/* no useful अटल MAC address found. generate a अक्रमom one */
	eth_hw_addr_अक्रमom(dev->net);
	netअगर_dbg(dev, अगरup, dev->net, "MAC address set to eth_random_addr\n");
पूर्ण

अटल पूर्णांक smsc95xx_set_mac_address(काष्ठा usbnet *dev)
अणु
	u32 addr_lo = dev->net->dev_addr[0] | dev->net->dev_addr[1] << 8 |
		dev->net->dev_addr[2] << 16 | dev->net->dev_addr[3] << 24;
	u32 addr_hi = dev->net->dev_addr[4] | dev->net->dev_addr[5] << 8;
	पूर्णांक ret;

	ret = smsc95xx_ग_लिखो_reg(dev, ADDRL, addr_lo);
	अगर (ret < 0)
		वापस ret;

	वापस smsc95xx_ग_लिखो_reg(dev, ADDRH, addr_hi);
पूर्ण

/* starts the TX path */
अटल पूर्णांक smsc95xx_start_tx_path(काष्ठा usbnet *dev)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Enable Tx at MAC */
	spin_lock_irqsave(&pdata->mac_cr_lock, flags);
	pdata->mac_cr |= MAC_CR_TXEN_;
	spin_unlock_irqrestore(&pdata->mac_cr_lock, flags);

	ret = smsc95xx_ग_लिखो_reg(dev, MAC_CR, pdata->mac_cr);
	अगर (ret < 0)
		वापस ret;

	/* Enable Tx at SCSRs */
	वापस smsc95xx_ग_लिखो_reg(dev, TX_CFG, TX_CFG_ON_);
पूर्ण

/* Starts the Receive path */
अटल पूर्णांक smsc95xx_start_rx_path(काष्ठा usbnet *dev, पूर्णांक in_pm)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->mac_cr_lock, flags);
	pdata->mac_cr |= MAC_CR_RXEN_;
	spin_unlock_irqrestore(&pdata->mac_cr_lock, flags);

	वापस __smsc95xx_ग_लिखो_reg(dev, MAC_CR, pdata->mac_cr, in_pm);
पूर्ण

अटल पूर्णांक smsc95xx_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	u32 पढ़ो_buf, ग_लिखो_buf, burst_cap;
	पूर्णांक ret = 0, समयout;

	netअगर_dbg(dev, अगरup, dev->net, "entering smsc95xx_reset\n");

	ret = smsc95xx_ग_लिखो_reg(dev, HW_CFG, HW_CFG_LRST_);
	अगर (ret < 0)
		वापस ret;

	समयout = 0;
	करो अणु
		msleep(10);
		ret = smsc95xx_पढ़ो_reg(dev, HW_CFG, &पढ़ो_buf);
		अगर (ret < 0)
			वापस ret;
		समयout++;
	पूर्ण जबतक ((पढ़ो_buf & HW_CFG_LRST_) && (समयout < 100));

	अगर (समयout >= 100) अणु
		netdev_warn(dev->net, "timeout waiting for completion of Lite Reset\n");
		वापस ret;
	पूर्ण

	ret = smsc95xx_ग_लिखो_reg(dev, PM_CTRL, PM_CTL_PHY_RST_);
	अगर (ret < 0)
		वापस ret;

	समयout = 0;
	करो अणु
		msleep(10);
		ret = smsc95xx_पढ़ो_reg(dev, PM_CTRL, &पढ़ो_buf);
		अगर (ret < 0)
			वापस ret;
		समयout++;
	पूर्ण जबतक ((पढ़ो_buf & PM_CTL_PHY_RST_) && (समयout < 100));

	अगर (समयout >= 100) अणु
		netdev_warn(dev->net, "timeout waiting for PHY Reset\n");
		वापस ret;
	पूर्ण

	ret = smsc95xx_set_mac_address(dev);
	अगर (ret < 0)
		वापस ret;

	netअगर_dbg(dev, अगरup, dev->net, "MAC Address: %pM\n",
		  dev->net->dev_addr);

	ret = smsc95xx_पढ़ो_reg(dev, HW_CFG, &पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	netअगर_dbg(dev, अगरup, dev->net, "Read Value from HW_CFG : 0x%08x\n",
		  पढ़ो_buf);

	पढ़ो_buf |= HW_CFG_BIR_;

	ret = smsc95xx_ग_लिखो_reg(dev, HW_CFG, पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	ret = smsc95xx_पढ़ो_reg(dev, HW_CFG, &पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	netअगर_dbg(dev, अगरup, dev->net,
		  "Read Value from HW_CFG after writing HW_CFG_BIR_: 0x%08x\n",
		  पढ़ो_buf);

	अगर (!turbo_mode) अणु
		burst_cap = 0;
		dev->rx_urb_size = MAX_SINGLE_PACKET_SIZE;
	पूर्ण अन्यथा अगर (dev->udev->speed == USB_SPEED_HIGH) अणु
		burst_cap = DEFAULT_HS_BURST_CAP_SIZE / HS_USB_PKT_SIZE;
		dev->rx_urb_size = DEFAULT_HS_BURST_CAP_SIZE;
	पूर्ण अन्यथा अणु
		burst_cap = DEFAULT_FS_BURST_CAP_SIZE / FS_USB_PKT_SIZE;
		dev->rx_urb_size = DEFAULT_FS_BURST_CAP_SIZE;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "rx_urb_size=%ld\n",
		  (uदीर्घ)dev->rx_urb_size);

	ret = smsc95xx_ग_लिखो_reg(dev, BURST_CAP, burst_cap);
	अगर (ret < 0)
		वापस ret;

	ret = smsc95xx_पढ़ो_reg(dev, BURST_CAP, &पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	netअगर_dbg(dev, अगरup, dev->net,
		  "Read Value from BURST_CAP after writing: 0x%08x\n",
		  पढ़ो_buf);

	ret = smsc95xx_ग_लिखो_reg(dev, BULK_IN_DLY, DEFAULT_BULK_IN_DELAY);
	अगर (ret < 0)
		वापस ret;

	ret = smsc95xx_पढ़ो_reg(dev, BULK_IN_DLY, &पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	netअगर_dbg(dev, अगरup, dev->net,
		  "Read Value from BULK_IN_DLY after writing: 0x%08x\n",
		  पढ़ो_buf);

	ret = smsc95xx_पढ़ो_reg(dev, HW_CFG, &पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	netअगर_dbg(dev, अगरup, dev->net, "Read Value from HW_CFG: 0x%08x\n",
		  पढ़ो_buf);

	अगर (turbo_mode)
		पढ़ो_buf |= (HW_CFG_MEF_ | HW_CFG_BCE_);

	पढ़ो_buf &= ~HW_CFG_RXDOFF_;

	/* set Rx data offset=2, Make IP header aligns on word boundary. */
	पढ़ो_buf |= NET_IP_ALIGN << 9;

	ret = smsc95xx_ग_लिखो_reg(dev, HW_CFG, पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	ret = smsc95xx_पढ़ो_reg(dev, HW_CFG, &पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	netअगर_dbg(dev, अगरup, dev->net,
		  "Read Value from HW_CFG after writing: 0x%08x\n", पढ़ो_buf);

	ret = smsc95xx_ग_लिखो_reg(dev, INT_STS, INT_STS_CLEAR_ALL_);
	अगर (ret < 0)
		वापस ret;

	ret = smsc95xx_पढ़ो_reg(dev, ID_REV, &पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;
	netअगर_dbg(dev, अगरup, dev->net, "ID_REV = 0x%08x\n", पढ़ो_buf);

	/* Configure GPIO pins as LED outमाला_दो */
	ग_लिखो_buf = LED_GPIO_CFG_SPD_LED | LED_GPIO_CFG_LNK_LED |
		LED_GPIO_CFG_FDX_LED;
	ret = smsc95xx_ग_लिखो_reg(dev, LED_GPIO_CFG, ग_लिखो_buf);
	अगर (ret < 0)
		वापस ret;

	/* Init Tx */
	ret = smsc95xx_ग_लिखो_reg(dev, FLOW, 0);
	अगर (ret < 0)
		वापस ret;

	ret = smsc95xx_ग_लिखो_reg(dev, AFC_CFG, AFC_CFG_DEFAULT);
	अगर (ret < 0)
		वापस ret;

	/* Don't need mac_cr_lock during initialisation */
	ret = smsc95xx_पढ़ो_reg(dev, MAC_CR, &pdata->mac_cr);
	अगर (ret < 0)
		वापस ret;

	/* Init Rx */
	/* Set Vlan */
	ret = smsc95xx_ग_लिखो_reg(dev, VLAN1, (u32)ETH_P_8021Q);
	अगर (ret < 0)
		वापस ret;

	/* Enable or disable checksum offload engines */
	ret = smsc95xx_set_features(dev->net, dev->net->features);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to set checksum offload features\n");
		वापस ret;
	पूर्ण

	smsc95xx_set_multicast(dev->net);

	ret = smsc95xx_पढ़ो_reg(dev, INT_EP_CTL, &पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	/* enable PHY पूर्णांकerrupts */
	पढ़ो_buf |= INT_EP_CTL_PHY_INT_;

	ret = smsc95xx_ग_लिखो_reg(dev, INT_EP_CTL, पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	ret = smsc95xx_start_tx_path(dev);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to start TX path\n");
		वापस ret;
	पूर्ण

	ret = smsc95xx_start_rx_path(dev, 0);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to start RX path\n");
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "smsc95xx_reset, return 0\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops smsc95xx_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_change_mtu		= usbnet_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl 		= smsc95xx_ioctl,
	.nकरो_set_rx_mode	= smsc95xx_set_multicast,
	.nकरो_set_features	= smsc95xx_set_features,
पूर्ण;

अटल पूर्णांक smsc95xx_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा smsc95xx_priv *pdata;
	bool is_पूर्णांकernal_phy;
	u32 val;
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO SMSC_CHIPNAME " v" SMSC_DRIVER_VERSION "\n");

	ret = usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "usbnet_get_endpoints failed: %d\n", ret);
		वापस ret;
	पूर्ण

	pdata = kzalloc(माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	dev->driver_priv = pdata;

	spin_lock_init(&pdata->mac_cr_lock);

	/* LAN95xx devices करो not alter the computed checksum of 0 to 0xffff.
	 * RFC 2460, ipv6 UDP calculated checksum yields a result of zero must
	 * be changed to 0xffff. RFC 768, ipv4 UDP computed checksum is zero,
	 * it is transmitted as all ones. The zero transmitted checksum means
	 * transmitter generated no checksum. Hence, enable csum offload only
	 * क्रम ipv4 packets.
	 */
	अगर (DEFAULT_TX_CSUM_ENABLE)
		dev->net->features |= NETIF_F_IP_CSUM;
	अगर (DEFAULT_RX_CSUM_ENABLE)
		dev->net->features |= NETIF_F_RXCSUM;

	dev->net->hw_features = NETIF_F_IP_CSUM | NETIF_F_RXCSUM;
	set_bit(EVENT_NO_IP_ALIGN, &dev->flags);

	smsc95xx_init_mac_address(dev);

	/* Init all रेजिस्टरs */
	ret = smsc95xx_reset(dev);
	अगर (ret)
		जाओ मुक्त_pdata;

	pdata->mdiobus = mdiobus_alloc();
	अगर (!pdata->mdiobus) अणु
		ret = -ENOMEM;
		जाओ मुक्त_pdata;
	पूर्ण

	ret = smsc95xx_पढ़ो_reg(dev, HW_CFG, &val);
	अगर (ret < 0)
		जाओ मुक्त_mdio;

	is_पूर्णांकernal_phy = !(val & HW_CFG_PSEL_);
	अगर (is_पूर्णांकernal_phy)
		pdata->mdiobus->phy_mask = ~(1u << SMSC95XX_INTERNAL_PHY_ID);

	pdata->mdiobus->priv = dev;
	pdata->mdiobus->पढ़ो = smsc95xx_mdiobus_पढ़ो;
	pdata->mdiobus->ग_लिखो = smsc95xx_mdiobus_ग_लिखो;
	pdata->mdiobus->name = "smsc95xx-mdiobus";
	pdata->mdiobus->parent = &dev->udev->dev;

	snम_लिखो(pdata->mdiobus->id, ARRAY_SIZE(pdata->mdiobus->id),
		 "usb-%03d:%03d", dev->udev->bus->busnum, dev->udev->devnum);

	ret = mdiobus_रेजिस्टर(pdata->mdiobus);
	अगर (ret) अणु
		netdev_err(dev->net, "Could not register MDIO bus\n");
		जाओ मुक्त_mdio;
	पूर्ण

	pdata->phydev = phy_find_first(pdata->mdiobus);
	अगर (!pdata->phydev) अणु
		netdev_err(dev->net, "no PHY found\n");
		ret = -ENODEV;
		जाओ unरेजिस्टर_mdio;
	पूर्ण

	pdata->phydev->is_पूर्णांकernal = is_पूर्णांकernal_phy;

	/* detect device revision as dअगरferent features may be available */
	ret = smsc95xx_पढ़ो_reg(dev, ID_REV, &val);
	अगर (ret < 0)
		जाओ unरेजिस्टर_mdio;

	val >>= 16;
	अगर ((val == ID_REV_CHIP_ID_9500A_) || (val == ID_REV_CHIP_ID_9530_) ||
	    (val == ID_REV_CHIP_ID_89530_) || (val == ID_REV_CHIP_ID_9730_))
		pdata->features = (FEATURE_8_WAKEUP_FILTERS |
			FEATURE_PHY_NLP_CROSSOVER |
			FEATURE_REMOTE_WAKEUP);
	अन्यथा अगर (val == ID_REV_CHIP_ID_9512_)
		pdata->features = FEATURE_8_WAKEUP_FILTERS;

	dev->net->netdev_ops = &smsc95xx_netdev_ops;
	dev->net->ethtool_ops = &smsc95xx_ethtool_ops;
	dev->net->flags |= IFF_MULTICAST;
	dev->net->hard_header_len += SMSC95XX_TX_OVERHEAD_CSUM;
	dev->net->min_mtu = ETH_MIN_MTU;
	dev->net->max_mtu = ETH_DATA_LEN;
	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;
	वापस 0;

unरेजिस्टर_mdio:
	mdiobus_unरेजिस्टर(pdata->mdiobus);

मुक्त_mdio:
	mdiobus_मुक्त(pdata->mdiobus);

मुक्त_pdata:
	kमुक्त(pdata);
	वापस ret;
पूर्ण

अटल व्योम smsc95xx_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;

	mdiobus_unरेजिस्टर(pdata->mdiobus);
	mdiobus_मुक्त(pdata->mdiobus);
	netअगर_dbg(dev, अगरकरोwn, dev->net, "free pdata\n");
	kमुक्त(pdata);
पूर्ण

अटल व्योम smsc95xx_handle_link_change(काष्ठा net_device *net)
अणु
	phy_prपूर्णांक_status(net->phydev);
पूर्ण

अटल पूर्णांक smsc95xx_start_phy(काष्ठा usbnet *dev)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	काष्ठा net_device *net = dev->net;
	पूर्णांक ret;

	ret = smsc95xx_reset(dev);
	अगर (ret < 0)
		वापस ret;

	ret = phy_connect_direct(net, pdata->phydev,
				 &smsc95xx_handle_link_change,
				 PHY_INTERFACE_MODE_MII);
	अगर (ret) अणु
		netdev_err(net, "can't attach PHY to %s\n", pdata->mdiobus->id);
		वापस ret;
	पूर्ण

	phy_attached_info(net->phydev);
	phy_start(net->phydev);
	वापस 0;
पूर्ण

अटल पूर्णांक smsc95xx_disconnect_phy(काष्ठा usbnet *dev)
अणु
	phy_stop(dev->net->phydev);
	phy_disconnect(dev->net->phydev);
	वापस 0;
पूर्ण

अटल u32 smsc_crc(स्थिर u8 *buffer, माप_प्रकार len, पूर्णांक filter)
अणु
	u32 crc = bitrev16(crc16(0xFFFF, buffer, len));
	वापस crc << ((filter % 2) * 16);
पूर्ण

अटल पूर्णांक smsc95xx_enable_phy_wakeup_पूर्णांकerrupts(काष्ठा usbnet *dev, u16 mask)
अणु
	पूर्णांक ret;

	netdev_dbg(dev->net, "enabling PHY wakeup interrupts\n");

	/* पढ़ो to clear */
	ret = smsc95xx_mdio_पढ़ो_nopm(dev, PHY_INT_SRC);
	अगर (ret < 0)
		वापस ret;

	/* enable पूर्णांकerrupt source */
	ret = smsc95xx_mdio_पढ़ो_nopm(dev, PHY_INT_MASK);
	अगर (ret < 0)
		वापस ret;

	ret |= mask;

	smsc95xx_mdio_ग_लिखो_nopm(dev, PHY_INT_MASK, ret);

	वापस 0;
पूर्ण

अटल पूर्णांक smsc95xx_link_ok_nopm(काष्ठा usbnet *dev)
अणु
	पूर्णांक ret;

	/* first, a dummy पढ़ो, needed to latch some MII phys */
	ret = smsc95xx_mdio_पढ़ो_nopm(dev, MII_BMSR);
	अगर (ret < 0)
		वापस ret;

	ret = smsc95xx_mdio_पढ़ो_nopm(dev, MII_BMSR);
	अगर (ret < 0)
		वापस ret;

	वापस !!(ret & BMSR_LSTATUS);
पूर्ण

अटल पूर्णांक smsc95xx_enter_suspend0(काष्ठा usbnet *dev)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	u32 val;
	पूर्णांक ret;

	ret = smsc95xx_पढ़ो_reg_nopm(dev, PM_CTRL, &val);
	अगर (ret < 0)
		वापस ret;

	val &= (~(PM_CTL_SUS_MODE_ | PM_CTL_WUPS_ | PM_CTL_PHY_RST_));
	val |= PM_CTL_SUS_MODE_0;

	ret = smsc95xx_ग_लिखो_reg_nopm(dev, PM_CTRL, val);
	अगर (ret < 0)
		वापस ret;

	/* clear wol status */
	val &= ~PM_CTL_WUPS_;
	val |= PM_CTL_WUPS_WOL_;

	/* enable energy detection */
	अगर (pdata->wolopts & WAKE_PHY)
		val |= PM_CTL_WUPS_ED_;

	ret = smsc95xx_ग_लिखो_reg_nopm(dev, PM_CTRL, val);
	अगर (ret < 0)
		वापस ret;

	/* पढ़ो back PM_CTRL */
	ret = smsc95xx_पढ़ो_reg_nopm(dev, PM_CTRL, &val);
	अगर (ret < 0)
		वापस ret;

	pdata->suspend_flags |= SUSPEND_SUSPEND0;

	वापस 0;
पूर्ण

अटल पूर्णांक smsc95xx_enter_suspend1(काष्ठा usbnet *dev)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	u32 val;
	पूर्णांक ret;

	/* reconfigure link pulse detection timing क्रम
	 * compatibility with non-standard link partners
	 */
	अगर (pdata->features & FEATURE_PHY_NLP_CROSSOVER)
		smsc95xx_mdio_ग_लिखो_nopm(dev, PHY_EDPD_CONFIG,
					 PHY_EDPD_CONFIG_DEFAULT);

	/* enable energy detect घातer-करोwn mode */
	ret = smsc95xx_mdio_पढ़ो_nopm(dev, PHY_MODE_CTRL_STS);
	अगर (ret < 0)
		वापस ret;

	ret |= MODE_CTRL_STS_EDPWRDOWN_;

	smsc95xx_mdio_ग_लिखो_nopm(dev, PHY_MODE_CTRL_STS, ret);

	/* enter SUSPEND1 mode */
	ret = smsc95xx_पढ़ो_reg_nopm(dev, PM_CTRL, &val);
	अगर (ret < 0)
		वापस ret;

	val &= ~(PM_CTL_SUS_MODE_ | PM_CTL_WUPS_ | PM_CTL_PHY_RST_);
	val |= PM_CTL_SUS_MODE_1;

	ret = smsc95xx_ग_लिखो_reg_nopm(dev, PM_CTRL, val);
	अगर (ret < 0)
		वापस ret;

	/* clear wol status, enable energy detection */
	val &= ~PM_CTL_WUPS_;
	val |= (PM_CTL_WUPS_ED_ | PM_CTL_ED_EN_);

	ret = smsc95xx_ग_लिखो_reg_nopm(dev, PM_CTRL, val);
	अगर (ret < 0)
		वापस ret;

	pdata->suspend_flags |= SUSPEND_SUSPEND1;

	वापस 0;
पूर्ण

अटल पूर्णांक smsc95xx_enter_suspend2(काष्ठा usbnet *dev)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	u32 val;
	पूर्णांक ret;

	ret = smsc95xx_पढ़ो_reg_nopm(dev, PM_CTRL, &val);
	अगर (ret < 0)
		वापस ret;

	val &= ~(PM_CTL_SUS_MODE_ | PM_CTL_WUPS_ | PM_CTL_PHY_RST_);
	val |= PM_CTL_SUS_MODE_2;

	ret = smsc95xx_ग_लिखो_reg_nopm(dev, PM_CTRL, val);
	अगर (ret < 0)
		वापस ret;

	pdata->suspend_flags |= SUSPEND_SUSPEND2;

	वापस 0;
पूर्ण

अटल पूर्णांक smsc95xx_enter_suspend3(काष्ठा usbnet *dev)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	u32 val;
	पूर्णांक ret;

	ret = smsc95xx_पढ़ो_reg_nopm(dev, RX_FIFO_INF, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val & RX_FIFO_INF_USED_) अणु
		netdev_info(dev->net, "rx fifo not empty in autosuspend\n");
		वापस -EBUSY;
	पूर्ण

	ret = smsc95xx_पढ़ो_reg_nopm(dev, PM_CTRL, &val);
	अगर (ret < 0)
		वापस ret;

	val &= ~(PM_CTL_SUS_MODE_ | PM_CTL_WUPS_ | PM_CTL_PHY_RST_);
	val |= PM_CTL_SUS_MODE_3 | PM_CTL_RES_CLR_WKP_STS;

	ret = smsc95xx_ग_लिखो_reg_nopm(dev, PM_CTRL, val);
	अगर (ret < 0)
		वापस ret;

	/* clear wol status */
	val &= ~PM_CTL_WUPS_;
	val |= PM_CTL_WUPS_WOL_;

	ret = smsc95xx_ग_लिखो_reg_nopm(dev, PM_CTRL, val);
	अगर (ret < 0)
		वापस ret;

	pdata->suspend_flags |= SUSPEND_SUSPEND3;

	वापस 0;
पूर्ण

अटल पूर्णांक smsc95xx_स्वतःsuspend(काष्ठा usbnet *dev, u32 link_up)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	पूर्णांक ret;

	अगर (!netअगर_running(dev->net)) अणु
		/* पूर्णांकerface is अगरconfig करोwn so fully घातer करोwn hw */
		netdev_dbg(dev->net, "autosuspend entering SUSPEND2\n");
		वापस smsc95xx_enter_suspend2(dev);
	पूर्ण

	अगर (!link_up) अणु
		/* link is करोwn so enter EDPD mode, but only अगर device can
		 * reliably resume from it.  This check should be redundant
		 * as current FEATURE_REMOTE_WAKEUP parts also support
		 * FEATURE_PHY_NLP_CROSSOVER but it's included क्रम clarity */
		अगर (!(pdata->features & FEATURE_PHY_NLP_CROSSOVER)) अणु
			netdev_warn(dev->net, "EDPD not supported\n");
			वापस -EBUSY;
		पूर्ण

		netdev_dbg(dev->net, "autosuspend entering SUSPEND1\n");

		/* enable PHY wakeup events क्रम अगर cable is attached */
		ret = smsc95xx_enable_phy_wakeup_पूर्णांकerrupts(dev,
			PHY_INT_MASK_ANEG_COMP_);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "error enabling PHY wakeup ints\n");
			वापस ret;
		पूर्ण

		netdev_info(dev->net, "entering SUSPEND1 mode\n");
		वापस smsc95xx_enter_suspend1(dev);
	पूर्ण

	/* enable PHY wakeup events so we remote wakeup अगर cable is pulled */
	ret = smsc95xx_enable_phy_wakeup_पूर्णांकerrupts(dev,
		PHY_INT_MASK_LINK_DOWN_);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "error enabling PHY wakeup ints\n");
		वापस ret;
	पूर्ण

	netdev_dbg(dev->net, "autosuspend entering SUSPEND3\n");
	वापस smsc95xx_enter_suspend3(dev);
पूर्ण

अटल पूर्णांक smsc95xx_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;
	u32 val, link_up;
	पूर्णांक ret;

	ret = usbnet_suspend(पूर्णांकf, message);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "usbnet_suspend error\n");
		वापस ret;
	पूर्ण

	अगर (pdata->suspend_flags) अणु
		netdev_warn(dev->net, "error during last resume\n");
		pdata->suspend_flags = 0;
	पूर्ण

	/* determine अगर link is up using only _nopm functions */
	link_up = smsc95xx_link_ok_nopm(dev);

	अगर (message.event == PM_EVENT_AUTO_SUSPEND &&
	    (pdata->features & FEATURE_REMOTE_WAKEUP)) अणु
		ret = smsc95xx_स्वतःsuspend(dev, link_up);
		जाओ करोne;
	पूर्ण

	/* अगर we get this far we're not स्वतःsuspending */
	/* अगर no wol options set, or अगर link is करोwn and we're not waking on
	 * PHY activity, enter lowest घातer SUSPEND2 mode
	 */
	अगर (!(pdata->wolopts & SUPPORTED_WAKE) ||
		!(link_up || (pdata->wolopts & WAKE_PHY))) अणु
		netdev_info(dev->net, "entering SUSPEND2 mode\n");

		/* disable energy detect (link up) & wake up events */
		ret = smsc95xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
		अगर (ret < 0)
			जाओ करोne;

		val &= ~(WUCSR_MPEN_ | WUCSR_WAKE_EN_);

		ret = smsc95xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
		अगर (ret < 0)
			जाओ करोne;

		ret = smsc95xx_पढ़ो_reg_nopm(dev, PM_CTRL, &val);
		अगर (ret < 0)
			जाओ करोne;

		val &= ~(PM_CTL_ED_EN_ | PM_CTL_WOL_EN_);

		ret = smsc95xx_ग_लिखो_reg_nopm(dev, PM_CTRL, val);
		अगर (ret < 0)
			जाओ करोne;

		ret = smsc95xx_enter_suspend2(dev);
		जाओ करोne;
	पूर्ण

	अगर (pdata->wolopts & WAKE_PHY) अणु
		ret = smsc95xx_enable_phy_wakeup_पूर्णांकerrupts(dev,
			(PHY_INT_MASK_ANEG_COMP_ | PHY_INT_MASK_LINK_DOWN_));
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "error enabling PHY wakeup ints\n");
			जाओ करोne;
		पूर्ण

		/* अगर link is करोwn then configure EDPD and enter SUSPEND1,
		 * otherwise enter SUSPEND0 below
		 */
		अगर (!link_up) अणु
			netdev_info(dev->net, "entering SUSPEND1 mode\n");
			ret = smsc95xx_enter_suspend1(dev);
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (pdata->wolopts & (WAKE_BCAST | WAKE_MCAST | WAKE_ARP | WAKE_UCAST)) अणु
		u32 *filter_mask = kसुस्मृति(32, माप(u32), GFP_KERNEL);
		u32 command[2];
		u32 offset[2];
		u32 crc[4];
		पूर्णांक wuff_filter_count =
			(pdata->features & FEATURE_8_WAKEUP_FILTERS) ?
			LAN9500A_WUFF_NUM : LAN9500_WUFF_NUM;
		पूर्णांक i, filter = 0;

		अगर (!filter_mask) अणु
			netdev_warn(dev->net, "Unable to allocate filter_mask\n");
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण

		स_रखो(command, 0, माप(command));
		स_रखो(offset, 0, माप(offset));
		स_रखो(crc, 0, माप(crc));

		अगर (pdata->wolopts & WAKE_BCAST) अणु
			स्थिर u8 bcast[] = अणु0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFFपूर्ण;
			netdev_info(dev->net, "enabling broadcast detection\n");
			filter_mask[filter * 4] = 0x003F;
			filter_mask[filter * 4 + 1] = 0x00;
			filter_mask[filter * 4 + 2] = 0x00;
			filter_mask[filter * 4 + 3] = 0x00;
			command[filter/4] |= 0x05UL << ((filter % 4) * 8);
			offset[filter/4] |= 0x00 << ((filter % 4) * 8);
			crc[filter/2] |= smsc_crc(bcast, 6, filter);
			filter++;
		पूर्ण

		अगर (pdata->wolopts & WAKE_MCAST) अणु
			स्थिर u8 mcast[] = अणु0x01, 0x00, 0x5Eपूर्ण;
			netdev_info(dev->net, "enabling multicast detection\n");
			filter_mask[filter * 4] = 0x0007;
			filter_mask[filter * 4 + 1] = 0x00;
			filter_mask[filter * 4 + 2] = 0x00;
			filter_mask[filter * 4 + 3] = 0x00;
			command[filter/4] |= 0x09UL << ((filter % 4) * 8);
			offset[filter/4] |= 0x00  << ((filter % 4) * 8);
			crc[filter/2] |= smsc_crc(mcast, 3, filter);
			filter++;
		पूर्ण

		अगर (pdata->wolopts & WAKE_ARP) अणु
			स्थिर u8 arp[] = अणु0x08, 0x06पूर्ण;
			netdev_info(dev->net, "enabling ARP detection\n");
			filter_mask[filter * 4] = 0x0003;
			filter_mask[filter * 4 + 1] = 0x00;
			filter_mask[filter * 4 + 2] = 0x00;
			filter_mask[filter * 4 + 3] = 0x00;
			command[filter/4] |= 0x05UL << ((filter % 4) * 8);
			offset[filter/4] |= 0x0C << ((filter % 4) * 8);
			crc[filter/2] |= smsc_crc(arp, 2, filter);
			filter++;
		पूर्ण

		अगर (pdata->wolopts & WAKE_UCAST) अणु
			netdev_info(dev->net, "enabling unicast detection\n");
			filter_mask[filter * 4] = 0x003F;
			filter_mask[filter * 4 + 1] = 0x00;
			filter_mask[filter * 4 + 2] = 0x00;
			filter_mask[filter * 4 + 3] = 0x00;
			command[filter/4] |= 0x01UL << ((filter % 4) * 8);
			offset[filter/4] |= 0x00 << ((filter % 4) * 8);
			crc[filter/2] |= smsc_crc(dev->net->dev_addr, ETH_ALEN, filter);
			filter++;
		पूर्ण

		क्रम (i = 0; i < (wuff_filter_count * 4); i++) अणु
			ret = smsc95xx_ग_लिखो_reg_nopm(dev, WUFF, filter_mask[i]);
			अगर (ret < 0) अणु
				kमुक्त(filter_mask);
				जाओ करोne;
			पूर्ण
		पूर्ण
		kमुक्त(filter_mask);

		क्रम (i = 0; i < (wuff_filter_count / 4); i++) अणु
			ret = smsc95xx_ग_लिखो_reg_nopm(dev, WUFF, command[i]);
			अगर (ret < 0)
				जाओ करोne;
		पूर्ण

		क्रम (i = 0; i < (wuff_filter_count / 4); i++) अणु
			ret = smsc95xx_ग_लिखो_reg_nopm(dev, WUFF, offset[i]);
			अगर (ret < 0)
				जाओ करोne;
		पूर्ण

		क्रम (i = 0; i < (wuff_filter_count / 2); i++) अणु
			ret = smsc95xx_ग_लिखो_reg_nopm(dev, WUFF, crc[i]);
			अगर (ret < 0)
				जाओ करोne;
		पूर्ण

		/* clear any pending pattern match packet status */
		ret = smsc95xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
		अगर (ret < 0)
			जाओ करोne;

		val |= WUCSR_WUFR_;

		ret = smsc95xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	अगर (pdata->wolopts & WAKE_MAGIC) अणु
		/* clear any pending magic packet status */
		ret = smsc95xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
		अगर (ret < 0)
			जाओ करोne;

		val |= WUCSR_MPR_;

		ret = smsc95xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	/* enable/disable wakeup sources */
	ret = smsc95xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
	अगर (ret < 0)
		जाओ करोne;

	अगर (pdata->wolopts & (WAKE_BCAST | WAKE_MCAST | WAKE_ARP | WAKE_UCAST)) अणु
		netdev_info(dev->net, "enabling pattern match wakeup\n");
		val |= WUCSR_WAKE_EN_;
	पूर्ण अन्यथा अणु
		netdev_info(dev->net, "disabling pattern match wakeup\n");
		val &= ~WUCSR_WAKE_EN_;
	पूर्ण

	अगर (pdata->wolopts & WAKE_MAGIC) अणु
		netdev_info(dev->net, "enabling magic packet wakeup\n");
		val |= WUCSR_MPEN_;
	पूर्ण अन्यथा अणु
		netdev_info(dev->net, "disabling magic packet wakeup\n");
		val &= ~WUCSR_MPEN_;
	पूर्ण

	ret = smsc95xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
	अगर (ret < 0)
		जाओ करोne;

	/* enable wol wakeup source */
	ret = smsc95xx_पढ़ो_reg_nopm(dev, PM_CTRL, &val);
	अगर (ret < 0)
		जाओ करोne;

	val |= PM_CTL_WOL_EN_;

	/* phy energy detect wakeup source */
	अगर (pdata->wolopts & WAKE_PHY)
		val |= PM_CTL_ED_EN_;

	ret = smsc95xx_ग_लिखो_reg_nopm(dev, PM_CTRL, val);
	अगर (ret < 0)
		जाओ करोne;

	/* enable receiver to enable frame reception */
	smsc95xx_start_rx_path(dev, 1);

	/* some wol options are enabled, so enter SUSPEND0 */
	netdev_info(dev->net, "entering SUSPEND0 mode\n");
	ret = smsc95xx_enter_suspend0(dev);

करोne:
	/*
	 * TODO: resume() might need to handle the suspend failure
	 * in प्रणाली sleep
	 */
	अगर (ret && PMSG_IS_AUTO(message))
		usbnet_resume(पूर्णांकf);

	वापस ret;
पूर्ण

अटल पूर्णांक smsc95xx_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा smsc95xx_priv *pdata;
	u8 suspend_flags;
	पूर्णांक ret;
	u32 val;

	BUG_ON(!dev);
	pdata = dev->driver_priv;
	suspend_flags = pdata->suspend_flags;

	netdev_dbg(dev->net, "resume suspend_flags=0x%02x\n", suspend_flags);

	/* करो this first to ensure it's cleared even in error हाल */
	pdata->suspend_flags = 0;

	अगर (suspend_flags & SUSPEND_ALLMODES) अणु
		/* clear wake-up sources */
		ret = smsc95xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
		अगर (ret < 0)
			वापस ret;

		val &= ~(WUCSR_WAKE_EN_ | WUCSR_MPEN_);

		ret = smsc95xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
		अगर (ret < 0)
			वापस ret;

		/* clear wake-up status */
		ret = smsc95xx_पढ़ो_reg_nopm(dev, PM_CTRL, &val);
		अगर (ret < 0)
			वापस ret;

		val &= ~PM_CTL_WOL_EN_;
		val |= PM_CTL_WUPS_;

		ret = smsc95xx_ग_लिखो_reg_nopm(dev, PM_CTRL, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = usbnet_resume(पूर्णांकf);
	अगर (ret < 0)
		netdev_warn(dev->net, "usbnet_resume error\n");

	phy_init_hw(pdata->phydev);
	वापस ret;
पूर्ण

अटल पूर्णांक smsc95xx_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक ret;

	ret = smsc95xx_reset(dev);
	अगर (ret < 0)
		वापस ret;

	वापस smsc95xx_resume(पूर्णांकf);
पूर्ण

अटल व्योम smsc95xx_rx_csum_offload(काष्ठा sk_buff *skb)
अणु
	skb->csum = *(u16 *)(skb_tail_poपूर्णांकer(skb) - 2);
	skb->ip_summed = CHECKSUM_COMPLETE;
	skb_trim(skb, skb->len - 2);
पूर्ण

अटल पूर्णांक smsc95xx_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	/* This check is no दीर्घer करोne by usbnet */
	अगर (skb->len < dev->net->hard_header_len)
		वापस 0;

	जबतक (skb->len > 0) अणु
		u32 header, align_count;
		काष्ठा sk_buff *ax_skb;
		अचिन्हित अक्षर *packet;
		u16 size;

		header = get_unaligned_le32(skb->data);
		skb_pull(skb, 4 + NET_IP_ALIGN);
		packet = skb->data;

		/* get the packet length */
		size = (u16)((header & RX_STS_FL_) >> 16);
		align_count = (4 - ((size + NET_IP_ALIGN) % 4)) % 4;

		अगर (unlikely(header & RX_STS_ES_)) अणु
			netअगर_dbg(dev, rx_err, dev->net,
				  "Error header=0x%08x\n", header);
			dev->net->stats.rx_errors++;
			dev->net->stats.rx_dropped++;

			अगर (header & RX_STS_CRC_) अणु
				dev->net->stats.rx_crc_errors++;
			पूर्ण अन्यथा अणु
				अगर (header & (RX_STS_TL_ | RX_STS_RF_))
					dev->net->stats.rx_frame_errors++;

				अगर ((header & RX_STS_LE_) &&
					(!(header & RX_STS_FT_)))
					dev->net->stats.rx_length_errors++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* ETH_FRAME_LEN + 4(CRC) + 2(COE) + 4(Vlan) */
			अगर (unlikely(size > (ETH_FRAME_LEN + 12))) अणु
				netअगर_dbg(dev, rx_err, dev->net,
					  "size err header=0x%08x\n", header);
				वापस 0;
			पूर्ण

			/* last frame in this batch */
			अगर (skb->len == size) अणु
				अगर (dev->net->features & NETIF_F_RXCSUM)
					smsc95xx_rx_csum_offload(skb);
				skb_trim(skb, skb->len - 4); /* हटाओ fcs */
				skb->truesize = size + माप(काष्ठा sk_buff);

				वापस 1;
			पूर्ण

			ax_skb = skb_clone(skb, GFP_ATOMIC);
			अगर (unlikely(!ax_skb)) अणु
				netdev_warn(dev->net, "Error allocating skb\n");
				वापस 0;
			पूर्ण

			ax_skb->len = size;
			ax_skb->data = packet;
			skb_set_tail_poपूर्णांकer(ax_skb, size);

			अगर (dev->net->features & NETIF_F_RXCSUM)
				smsc95xx_rx_csum_offload(ax_skb);
			skb_trim(ax_skb, ax_skb->len - 4); /* हटाओ fcs */
			ax_skb->truesize = size + माप(काष्ठा sk_buff);

			usbnet_skb_वापस(dev, ax_skb);
		पूर्ण

		skb_pull(skb, size);

		/* padding bytes beक्रमe the next frame starts */
		अगर (skb->len)
			skb_pull(skb, align_count);
	पूर्ण

	वापस 1;
पूर्ण

अटल u32 smsc95xx_calc_csum_preamble(काष्ठा sk_buff *skb)
अणु
	u16 low_16 = (u16)skb_checksum_start_offset(skb);
	u16 high_16 = low_16 + skb->csum_offset;
	वापस (high_16 << 16) | low_16;
पूर्ण

/* The TX CSUM won't work अगर the checksum lies in the last 4 bytes of the
 * transmission. This is fairly unlikely, only seems to trigger with some
 * लघु TCP ACK packets sent.
 *
 * Note, this calculation should probably check क्रम the alignment of the
 * data as well, but a straight check क्रम csum being in the last four bytes
 * of the packet should be ok क्रम now.
 */
अटल bool smsc95xx_can_tx_checksum(काष्ठा sk_buff *skb)
अणु
       अचिन्हित पूर्णांक len = skb->len - skb_checksum_start_offset(skb);

       अगर (skb->len <= 45)
	       वापस false;
       वापस skb->csum_offset < (len - (4 + 1));
पूर्ण

अटल काष्ठा sk_buff *smsc95xx_tx_fixup(काष्ठा usbnet *dev,
					 काष्ठा sk_buff *skb, gfp_t flags)
अणु
	bool csum = skb->ip_summed == CHECKSUM_PARTIAL;
	पूर्णांक overhead = csum ? SMSC95XX_TX_OVERHEAD_CSUM : SMSC95XX_TX_OVERHEAD;
	u32 tx_cmd_a, tx_cmd_b;
	व्योम *ptr;

	/* We करो not advertise SG, so skbs should be alपढ़ोy linearized */
	BUG_ON(skb_shinfo(skb)->nr_frags);

	/* Make writable and expand header space by overhead अगर required */
	अगर (skb_cow_head(skb, overhead)) अणु
		/* Must deallocate here as वापसing शून्य to indicate error
		 * means the skb won't be deallocated in the caller.
		 */
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण

	tx_cmd_b = (u32)skb->len;
	tx_cmd_a = tx_cmd_b | TX_CMD_A_FIRST_SEG_ | TX_CMD_A_LAST_SEG_;

	अगर (csum) अणु
		अगर (!smsc95xx_can_tx_checksum(skb)) अणु
			/* workaround - hardware tx checksum करोes not work
			 * properly with extremely small packets */
			दीर्घ csstart = skb_checksum_start_offset(skb);
			__wsum calc = csum_partial(skb->data + csstart,
				skb->len - csstart, 0);
			*((__sum16 *)(skb->data + csstart
				+ skb->csum_offset)) = csum_fold(calc);

			csum = false;
		पूर्ण अन्यथा अणु
			u32 csum_preamble = smsc95xx_calc_csum_preamble(skb);
			ptr = skb_push(skb, 4);
			put_unaligned_le32(csum_preamble, ptr);

			tx_cmd_a += 4;
			tx_cmd_b += 4;
			tx_cmd_b |= TX_CMD_B_CSUM_ENABLE;
		पूर्ण
	पूर्ण

	ptr = skb_push(skb, 8);
	put_unaligned_le32(tx_cmd_a, ptr);
	put_unaligned_le32(tx_cmd_b, ptr+4);

	वापस skb;
पूर्ण

अटल पूर्णांक smsc95xx_manage_घातer(काष्ठा usbnet *dev, पूर्णांक on)
अणु
	काष्ठा smsc95xx_priv *pdata = dev->driver_priv;

	dev->पूर्णांकf->needs_remote_wakeup = on;

	अगर (pdata->features & FEATURE_REMOTE_WAKEUP)
		वापस 0;

	/* this chip revision isn't capable of remote wakeup */
	netdev_info(dev->net, "hardware isn't capable of remote wakeup\n");

	अगर (on)
		usb_स्वतःpm_get_पूर्णांकerface_no_resume(dev->पूर्णांकf);
	अन्यथा
		usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा driver_info smsc95xx_info = अणु
	.description	= "smsc95xx USB 2.0 Ethernet",
	.bind		= smsc95xx_bind,
	.unbind		= smsc95xx_unbind,
	.link_reset	= smsc95xx_link_reset,
	.reset		= smsc95xx_start_phy,
	.stop		= smsc95xx_disconnect_phy,
	.rx_fixup	= smsc95xx_rx_fixup,
	.tx_fixup	= smsc95xx_tx_fixup,
	.status		= smsc95xx_status,
	.manage_घातer	= smsc95xx_manage_घातer,
	.flags		= FLAG_ETHER | FLAG_SEND_ZLP | FLAG_LINK_INTR,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id products[] = अणु
	अणु
		/* SMSC9500 USB Ethernet Device */
		USB_DEVICE(0x0424, 0x9500),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9505 USB Ethernet Device */
		USB_DEVICE(0x0424, 0x9505),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9500A USB Ethernet Device */
		USB_DEVICE(0x0424, 0x9E00),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9505A USB Ethernet Device */
		USB_DEVICE(0x0424, 0x9E01),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9512/9514 USB Hub & Ethernet Device */
		USB_DEVICE(0x0424, 0xec00),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9500 USB Ethernet Device (SAL10) */
		USB_DEVICE(0x0424, 0x9900),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9505 USB Ethernet Device (SAL10) */
		USB_DEVICE(0x0424, 0x9901),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9500A USB Ethernet Device (SAL10) */
		USB_DEVICE(0x0424, 0x9902),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9505A USB Ethernet Device (SAL10) */
		USB_DEVICE(0x0424, 0x9903),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9512/9514 USB Hub & Ethernet Device (SAL10) */
		USB_DEVICE(0x0424, 0x9904),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9500A USB Ethernet Device (HAL) */
		USB_DEVICE(0x0424, 0x9905),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9505A USB Ethernet Device (HAL) */
		USB_DEVICE(0x0424, 0x9906),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9500 USB Ethernet Device (Alternate ID) */
		USB_DEVICE(0x0424, 0x9907),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9500A USB Ethernet Device (Alternate ID) */
		USB_DEVICE(0x0424, 0x9908),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC9512/9514 USB Hub & Ethernet Device (Alternate ID) */
		USB_DEVICE(0x0424, 0x9909),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC LAN9530 USB Ethernet Device */
		USB_DEVICE(0x0424, 0x9530),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC LAN9730 USB Ethernet Device */
		USB_DEVICE(0x0424, 0x9730),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु
		/* SMSC LAN89530 USB Ethernet Device */
		USB_DEVICE(0x0424, 0x9E08),
		.driver_info = (अचिन्हित दीर्घ) &smsc95xx_info,
	पूर्ण,
	अणु पूर्ण,		/* END */
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver smsc95xx_driver = अणु
	.name		= "smsc95xx",
	.id_table	= products,
	.probe		= usbnet_probe,
	.suspend	= smsc95xx_suspend,
	.resume		= smsc95xx_resume,
	.reset_resume	= smsc95xx_reset_resume,
	.disconnect	= usbnet_disconnect,
	.disable_hub_initiated_lpm = 1,
	.supports_स्वतःsuspend = 1,
पूर्ण;

module_usb_driver(smsc95xx_driver);

MODULE_AUTHOR("Nancy Lin");
MODULE_AUTHOR("Steve Glendinning <steve.glendinning@shawell.net>");
MODULE_DESCRIPTION("SMSC95XX USB 2.0 Ethernet Devices");
MODULE_LICENSE("GPL");
