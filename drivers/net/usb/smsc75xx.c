<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /***************************************************************************
 *
 * Copyright (C) 2007-2010 SMSC
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
#समावेश "smsc75xx.h"

#घोषणा SMSC_CHIPNAME			"smsc75xx"
#घोषणा SMSC_DRIVER_VERSION		"1.0.0"
#घोषणा HS_USB_PKT_SIZE			(512)
#घोषणा FS_USB_PKT_SIZE			(64)
#घोषणा DEFAULT_HS_BURST_CAP_SIZE	(16 * 1024 + 5 * HS_USB_PKT_SIZE)
#घोषणा DEFAULT_FS_BURST_CAP_SIZE	(6 * 1024 + 33 * FS_USB_PKT_SIZE)
#घोषणा DEFAULT_BULK_IN_DELAY		(0x00002000)
#घोषणा MAX_SINGLE_PACKET_SIZE		(9000)
#घोषणा LAN75XX_EEPROM_MAGIC		(0x7500)
#घोषणा EEPROM_MAC_OFFSET		(0x01)
#घोषणा DEFAULT_TX_CSUM_ENABLE		(true)
#घोषणा DEFAULT_RX_CSUM_ENABLE		(true)
#घोषणा SMSC75XX_INTERNAL_PHY_ID	(1)
#घोषणा SMSC75XX_TX_OVERHEAD		(8)
#घोषणा MAX_RX_FIFO_SIZE		(20 * 1024)
#घोषणा MAX_TX_FIFO_SIZE		(12 * 1024)
#घोषणा USB_VENDOR_ID_SMSC		(0x0424)
#घोषणा USB_PRODUCT_ID_LAN7500		(0x7500)
#घोषणा USB_PRODUCT_ID_LAN7505		(0x7505)
#घोषणा RXW_PADDING			2
#घोषणा SUPPORTED_WAKE			(WAKE_PHY | WAKE_UCAST | WAKE_BCAST | \
					 WAKE_MCAST | WAKE_ARP | WAKE_MAGIC)

#घोषणा SUSPEND_SUSPEND0		(0x01)
#घोषणा SUSPEND_SUSPEND1		(0x02)
#घोषणा SUSPEND_SUSPEND2		(0x04)
#घोषणा SUSPEND_SUSPEND3		(0x08)
#घोषणा SUSPEND_ALLMODES		(SUSPEND_SUSPEND0 | SUSPEND_SUSPEND1 | \
					 SUSPEND_SUSPEND2 | SUSPEND_SUSPEND3)

काष्ठा smsc75xx_priv अणु
	काष्ठा usbnet *dev;
	u32 rfe_ctl;
	u32 wolopts;
	u32 multicast_hash_table[DP_SEL_VHF_HASH_LEN];
	काष्ठा mutex dataport_mutex;
	spinlock_t rfe_ctl_lock;
	काष्ठा work_काष्ठा set_multicast;
	u8 suspend_flags;
पूर्ण;

काष्ठा usb_context अणु
	काष्ठा usb_ctrlrequest req;
	काष्ठा usbnet *dev;
पूर्ण;

अटल bool turbo_mode = true;
module_param(turbo_mode, bool, 0644);
MODULE_PARM_DESC(turbo_mode, "Enable multiple frames per Rx transaction");

अटल पूर्णांक smsc75xx_link_ok_nopm(काष्ठा usbnet *dev);
अटल पूर्णांक smsc75xx_phy_gig_workaround(काष्ठा usbnet *dev);

अटल पूर्णांक __must_check __smsc75xx_पढ़ो_reg(काष्ठा usbnet *dev, u32 index,
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

अटल पूर्णांक __must_check __smsc75xx_ग_लिखो_reg(काष्ठा usbnet *dev, u32 index,
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

अटल पूर्णांक __must_check smsc75xx_पढ़ो_reg_nopm(काष्ठा usbnet *dev, u32 index,
					       u32 *data)
अणु
	वापस __smsc75xx_पढ़ो_reg(dev, index, data, 1);
पूर्ण

अटल पूर्णांक __must_check smsc75xx_ग_लिखो_reg_nopm(काष्ठा usbnet *dev, u32 index,
						u32 data)
अणु
	वापस __smsc75xx_ग_लिखो_reg(dev, index, data, 1);
पूर्ण

अटल पूर्णांक __must_check smsc75xx_पढ़ो_reg(काष्ठा usbnet *dev, u32 index,
					  u32 *data)
अणु
	वापस __smsc75xx_पढ़ो_reg(dev, index, data, 0);
पूर्ण

अटल पूर्णांक __must_check smsc75xx_ग_लिखो_reg(काष्ठा usbnet *dev, u32 index,
					   u32 data)
अणु
	वापस __smsc75xx_ग_लिखो_reg(dev, index, data, 0);
पूर्ण

/* Loop until the पढ़ो is completed with समयout
 * called with phy_mutex held */
अटल __must_check पूर्णांक __smsc75xx_phy_रुको_not_busy(काष्ठा usbnet *dev,
						     पूर्णांक in_pm)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;
	u32 val;
	पूर्णांक ret;

	करो अणु
		ret = __smsc75xx_पढ़ो_reg(dev, MII_ACCESS, &val, in_pm);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading MII_ACCESS\n");
			वापस ret;
		पूर्ण

		अगर (!(val & MII_ACCESS_BUSY))
			वापस 0;
	पूर्ण जबतक (!समय_after(jअगरfies, start_समय + HZ));

	वापस -EIO;
पूर्ण

अटल पूर्णांक __smsc75xx_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक idx,
				पूर्णांक in_pm)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	u32 val, addr;
	पूर्णांक ret;

	mutex_lock(&dev->phy_mutex);

	/* confirm MII not busy */
	ret = __smsc75xx_phy_रुको_not_busy(dev, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "MII is busy in smsc75xx_mdio_read\n");
		जाओ करोne;
	पूर्ण

	/* set the address, index & direction (पढ़ो from PHY) */
	phy_id &= dev->mii.phy_id_mask;
	idx &= dev->mii.reg_num_mask;
	addr = ((phy_id << MII_ACCESS_PHY_ADDR_SHIFT) & MII_ACCESS_PHY_ADDR)
		| ((idx << MII_ACCESS_REG_ADDR_SHIFT) & MII_ACCESS_REG_ADDR)
		| MII_ACCESS_READ | MII_ACCESS_BUSY;
	ret = __smsc75xx_ग_लिखो_reg(dev, MII_ACCESS, addr, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing MII_ACCESS\n");
		जाओ करोne;
	पूर्ण

	ret = __smsc75xx_phy_रुको_not_busy(dev, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Timed out reading MII reg %02X\n", idx);
		जाओ करोne;
	पूर्ण

	ret = __smsc75xx_पढ़ो_reg(dev, MII_DATA, &val, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading MII_DATA\n");
		जाओ करोne;
	पूर्ण

	ret = (u16)(val & 0xFFFF);

करोne:
	mutex_unlock(&dev->phy_mutex);
	वापस ret;
पूर्ण

अटल व्योम __smsc75xx_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक phy_id,
				  पूर्णांक idx, पूर्णांक regval, पूर्णांक in_pm)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	u32 val, addr;
	पूर्णांक ret;

	mutex_lock(&dev->phy_mutex);

	/* confirm MII not busy */
	ret = __smsc75xx_phy_रुको_not_busy(dev, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "MII is busy in smsc75xx_mdio_write\n");
		जाओ करोne;
	पूर्ण

	val = regval;
	ret = __smsc75xx_ग_लिखो_reg(dev, MII_DATA, val, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing MII_DATA\n");
		जाओ करोne;
	पूर्ण

	/* set the address, index & direction (ग_लिखो to PHY) */
	phy_id &= dev->mii.phy_id_mask;
	idx &= dev->mii.reg_num_mask;
	addr = ((phy_id << MII_ACCESS_PHY_ADDR_SHIFT) & MII_ACCESS_PHY_ADDR)
		| ((idx << MII_ACCESS_REG_ADDR_SHIFT) & MII_ACCESS_REG_ADDR)
		| MII_ACCESS_WRITE | MII_ACCESS_BUSY;
	ret = __smsc75xx_ग_लिखो_reg(dev, MII_ACCESS, addr, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing MII_ACCESS\n");
		जाओ करोne;
	पूर्ण

	ret = __smsc75xx_phy_रुको_not_busy(dev, in_pm);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Timed out writing MII reg %02X\n", idx);
		जाओ करोne;
	पूर्ण

करोne:
	mutex_unlock(&dev->phy_mutex);
पूर्ण

अटल पूर्णांक smsc75xx_mdio_पढ़ो_nopm(काष्ठा net_device *netdev, पूर्णांक phy_id,
				   पूर्णांक idx)
अणु
	वापस __smsc75xx_mdio_पढ़ो(netdev, phy_id, idx, 1);
पूर्ण

अटल व्योम smsc75xx_mdio_ग_लिखो_nopm(काष्ठा net_device *netdev, पूर्णांक phy_id,
				     पूर्णांक idx, पूर्णांक regval)
अणु
	__smsc75xx_mdio_ग_लिखो(netdev, phy_id, idx, regval, 1);
पूर्ण

अटल पूर्णांक smsc75xx_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक idx)
अणु
	वापस __smsc75xx_mdio_पढ़ो(netdev, phy_id, idx, 0);
पूर्ण

अटल व्योम smsc75xx_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक idx,
				पूर्णांक regval)
अणु
	__smsc75xx_mdio_ग_लिखो(netdev, phy_id, idx, regval, 0);
पूर्ण

अटल पूर्णांक smsc75xx_रुको_eeprom(काष्ठा usbnet *dev)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;
	u32 val;
	पूर्णांक ret;

	करो अणु
		ret = smsc75xx_पढ़ो_reg(dev, E2P_CMD, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading E2P_CMD\n");
			वापस ret;
		पूर्ण

		अगर (!(val & E2P_CMD_BUSY) || (val & E2P_CMD_TIMEOUT))
			अवरोध;
		udelay(40);
	पूर्ण जबतक (!समय_after(jअगरfies, start_समय + HZ));

	अगर (val & (E2P_CMD_TIMEOUT | E2P_CMD_BUSY)) अणु
		netdev_warn(dev->net, "EEPROM read operation timeout\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_eeprom_confirm_not_busy(काष्ठा usbnet *dev)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;
	u32 val;
	पूर्णांक ret;

	करो अणु
		ret = smsc75xx_पढ़ो_reg(dev, E2P_CMD, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading E2P_CMD\n");
			वापस ret;
		पूर्ण

		अगर (!(val & E2P_CMD_BUSY))
			वापस 0;

		udelay(40);
	पूर्ण जबतक (!समय_after(jअगरfies, start_समय + HZ));

	netdev_warn(dev->net, "EEPROM is busy\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक smsc75xx_पढ़ो_eeprom(काष्ठा usbnet *dev, u32 offset, u32 length,
				u8 *data)
अणु
	u32 val;
	पूर्णांक i, ret;

	BUG_ON(!dev);
	BUG_ON(!data);

	ret = smsc75xx_eeprom_confirm_not_busy(dev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < length; i++) अणु
		val = E2P_CMD_BUSY | E2P_CMD_READ | (offset & E2P_CMD_ADDR);
		ret = smsc75xx_ग_लिखो_reg(dev, E2P_CMD, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing E2P_CMD\n");
			वापस ret;
		पूर्ण

		ret = smsc75xx_रुको_eeprom(dev);
		अगर (ret < 0)
			वापस ret;

		ret = smsc75xx_पढ़ो_reg(dev, E2P_DATA, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading E2P_DATA\n");
			वापस ret;
		पूर्ण

		data[i] = val & 0xFF;
		offset++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_ग_लिखो_eeprom(काष्ठा usbnet *dev, u32 offset, u32 length,
				 u8 *data)
अणु
	u32 val;
	पूर्णांक i, ret;

	BUG_ON(!dev);
	BUG_ON(!data);

	ret = smsc75xx_eeprom_confirm_not_busy(dev);
	अगर (ret)
		वापस ret;

	/* Issue ग_लिखो/erase enable command */
	val = E2P_CMD_BUSY | E2P_CMD_EWEN;
	ret = smsc75xx_ग_लिखो_reg(dev, E2P_CMD, val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing E2P_CMD\n");
		वापस ret;
	पूर्ण

	ret = smsc75xx_रुको_eeprom(dev);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < length; i++) अणु

		/* Fill data रेजिस्टर */
		val = data[i];
		ret = smsc75xx_ग_लिखो_reg(dev, E2P_DATA, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing E2P_DATA\n");
			वापस ret;
		पूर्ण

		/* Send "write" command */
		val = E2P_CMD_BUSY | E2P_CMD_WRITE | (offset & E2P_CMD_ADDR);
		ret = smsc75xx_ग_लिखो_reg(dev, E2P_CMD, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing E2P_CMD\n");
			वापस ret;
		पूर्ण

		ret = smsc75xx_रुको_eeprom(dev);
		अगर (ret < 0)
			वापस ret;

		offset++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_dataport_रुको_not_busy(काष्ठा usbnet *dev)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < 100; i++) अणु
		u32 dp_sel;
		ret = smsc75xx_पढ़ो_reg(dev, DP_SEL, &dp_sel);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading DP_SEL\n");
			वापस ret;
		पूर्ण

		अगर (dp_sel & DP_SEL_DPRDY)
			वापस 0;

		udelay(40);
	पूर्ण

	netdev_warn(dev->net, "smsc75xx_dataport_wait_not_busy timed out\n");

	वापस -EIO;
पूर्ण

अटल पूर्णांक smsc75xx_dataport_ग_लिखो(काष्ठा usbnet *dev, u32 ram_select, u32 addr,
				   u32 length, u32 *buf)
अणु
	काष्ठा smsc75xx_priv *pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);
	u32 dp_sel;
	पूर्णांक i, ret;

	mutex_lock(&pdata->dataport_mutex);

	ret = smsc75xx_dataport_रुको_not_busy(dev);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "smsc75xx_dataport_write busy on entry\n");
		जाओ करोne;
	पूर्ण

	ret = smsc75xx_पढ़ो_reg(dev, DP_SEL, &dp_sel);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading DP_SEL\n");
		जाओ करोne;
	पूर्ण

	dp_sel &= ~DP_SEL_RSEL;
	dp_sel |= ram_select;
	ret = smsc75xx_ग_लिखो_reg(dev, DP_SEL, dp_sel);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing DP_SEL\n");
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < length; i++) अणु
		ret = smsc75xx_ग_लिखो_reg(dev, DP_ADDR, addr + i);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing DP_ADDR\n");
			जाओ करोne;
		पूर्ण

		ret = smsc75xx_ग_लिखो_reg(dev, DP_DATA, buf[i]);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing DP_DATA\n");
			जाओ करोne;
		पूर्ण

		ret = smsc75xx_ग_लिखो_reg(dev, DP_CMD, DP_CMD_WRITE);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing DP_CMD\n");
			जाओ करोne;
		पूर्ण

		ret = smsc75xx_dataport_रुको_not_busy(dev);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "smsc75xx_dataport_write timeout\n");
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	mutex_unlock(&pdata->dataport_mutex);
	वापस ret;
पूर्ण

/* वापसs hash bit number क्रम given MAC address */
अटल u32 smsc75xx_hash(अक्षर addr[ETH_ALEN])
अणु
	वापस (ether_crc(ETH_ALEN, addr) >> 23) & 0x1ff;
पूर्ण

अटल व्योम smsc75xx_deferred_multicast_ग_लिखो(काष्ठा work_काष्ठा *param)
अणु
	काष्ठा smsc75xx_priv *pdata =
		container_of(param, काष्ठा smsc75xx_priv, set_multicast);
	काष्ठा usbnet *dev = pdata->dev;
	पूर्णांक ret;

	netअगर_dbg(dev, drv, dev->net, "deferred multicast write 0x%08x\n",
		  pdata->rfe_ctl);

	smsc75xx_dataport_ग_लिखो(dev, DP_SEL_VHF, DP_SEL_VHF_VLAN_LEN,
		DP_SEL_VHF_HASH_LEN, pdata->multicast_hash_table);

	ret = smsc75xx_ग_लिखो_reg(dev, RFE_CTL, pdata->rfe_ctl);
	अगर (ret < 0)
		netdev_warn(dev->net, "Error writing RFE_CRL\n");
पूर्ण

अटल व्योम smsc75xx_set_multicast(काष्ठा net_device *netdev)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	काष्ठा smsc75xx_priv *pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&pdata->rfe_ctl_lock, flags);

	pdata->rfe_ctl &=
		~(RFE_CTL_AU | RFE_CTL_AM | RFE_CTL_DPF | RFE_CTL_MHF);
	pdata->rfe_ctl |= RFE_CTL_AB;

	क्रम (i = 0; i < DP_SEL_VHF_HASH_LEN; i++)
		pdata->multicast_hash_table[i] = 0;

	अगर (dev->net->flags & IFF_PROMISC) अणु
		netअगर_dbg(dev, drv, dev->net, "promiscuous mode enabled\n");
		pdata->rfe_ctl |= RFE_CTL_AM | RFE_CTL_AU;
	पूर्ण अन्यथा अगर (dev->net->flags & IFF_ALLMULTI) अणु
		netअगर_dbg(dev, drv, dev->net, "receive all multicast enabled\n");
		pdata->rfe_ctl |= RFE_CTL_AM | RFE_CTL_DPF;
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev->net)) अणु
		काष्ठा netdev_hw_addr *ha;

		netअगर_dbg(dev, drv, dev->net, "receive multicast hash filter\n");

		pdata->rfe_ctl |= RFE_CTL_MHF | RFE_CTL_DPF;

		netdev_क्रम_each_mc_addr(ha, netdev) अणु
			u32 bitnum = smsc75xx_hash(ha->addr);
			pdata->multicast_hash_table[bitnum / 32] |=
				(1 << (bitnum % 32));
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_dbg(dev, drv, dev->net, "receive own packets only\n");
		pdata->rfe_ctl |= RFE_CTL_DPF;
	पूर्ण

	spin_unlock_irqrestore(&pdata->rfe_ctl_lock, flags);

	/* defer रेजिस्टर ग_लिखोs to a sleepable context */
	schedule_work(&pdata->set_multicast);
पूर्ण

अटल पूर्णांक smsc75xx_update_flowcontrol(काष्ठा usbnet *dev, u8 duplex,
					    u16 lcladv, u16 rmtadv)
अणु
	u32 flow = 0, fct_flow = 0;
	पूर्णांक ret;

	अगर (duplex == DUPLEX_FULL) अणु
		u8 cap = mii_resolve_flowctrl_fdx(lcladv, rmtadv);

		अगर (cap & FLOW_CTRL_TX) अणु
			flow = (FLOW_TX_FCEN | 0xFFFF);
			/* set fct_flow thresholds to 20% and 80% */
			fct_flow = (8 << 8) | 32;
		पूर्ण

		अगर (cap & FLOW_CTRL_RX)
			flow |= FLOW_RX_FCEN;

		netअगर_dbg(dev, link, dev->net, "rx pause %s, tx pause %s\n",
			  (cap & FLOW_CTRL_RX ? "enabled" : "disabled"),
			  (cap & FLOW_CTRL_TX ? "enabled" : "disabled"));
	पूर्ण अन्यथा अणु
		netअगर_dbg(dev, link, dev->net, "half duplex\n");
	पूर्ण

	ret = smsc75xx_ग_लिखो_reg(dev, FLOW, flow);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing FLOW\n");
		वापस ret;
	पूर्ण

	ret = smsc75xx_ग_लिखो_reg(dev, FCT_FLOW, fct_flow);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing FCT_FLOW\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_link_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा mii_अगर_info *mii = &dev->mii;
	काष्ठा ethtool_cmd ecmd = अणु .cmd = ETHTOOL_GSET पूर्ण;
	u16 lcladv, rmtadv;
	पूर्णांक ret;

	/* ग_लिखो to clear phy पूर्णांकerrupt status */
	smsc75xx_mdio_ग_लिखो(dev->net, mii->phy_id, PHY_INT_SRC,
		PHY_INT_SRC_CLEAR_ALL);

	ret = smsc75xx_ग_लिखो_reg(dev, INT_STS, INT_STS_CLEAR_ALL);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing INT_STS\n");
		वापस ret;
	पूर्ण

	mii_check_media(mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);
	lcladv = smsc75xx_mdio_पढ़ो(dev->net, mii->phy_id, MII_ADVERTISE);
	rmtadv = smsc75xx_mdio_पढ़ो(dev->net, mii->phy_id, MII_LPA);

	netअगर_dbg(dev, link, dev->net, "speed: %u duplex: %d lcladv: %04x rmtadv: %04x\n",
		  ethtool_cmd_speed(&ecmd), ecmd.duplex, lcladv, rmtadv);

	वापस smsc75xx_update_flowcontrol(dev, ecmd.duplex, lcladv, rmtadv);
पूर्ण

अटल व्योम smsc75xx_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	u32 पूर्णांकdata;

	अगर (urb->actual_length != 4) अणु
		netdev_warn(dev->net, "unexpected urb length %d\n",
			    urb->actual_length);
		वापस;
	पूर्ण

	पूर्णांकdata = get_unaligned_le32(urb->transfer_buffer);

	netअगर_dbg(dev, link, dev->net, "intdata: 0x%08X\n", पूर्णांकdata);

	अगर (पूर्णांकdata & INT_ENP_PHY_INT)
		usbnet_defer_kevent(dev, EVENT_LINK_RESET);
	अन्यथा
		netdev_warn(dev->net, "unexpected interrupt, intdata=0x%08X\n",
			    पूर्णांकdata);
पूर्ण

अटल पूर्णांक smsc75xx_ethtool_get_eeprom_len(काष्ठा net_device *net)
अणु
	वापस MAX_EEPROM_SIZE;
पूर्ण

अटल पूर्णांक smsc75xx_ethtool_get_eeprom(काष्ठा net_device *netdev,
				       काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);

	ee->magic = LAN75XX_EEPROM_MAGIC;

	वापस smsc75xx_पढ़ो_eeprom(dev, ee->offset, ee->len, data);
पूर्ण

अटल पूर्णांक smsc75xx_ethtool_set_eeprom(काष्ठा net_device *netdev,
				       काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);

	अगर (ee->magic != LAN75XX_EEPROM_MAGIC) अणु
		netdev_warn(dev->net, "EEPROM: magic value mismatch: 0x%x\n",
			    ee->magic);
		वापस -EINVAL;
	पूर्ण

	वापस smsc75xx_ग_लिखो_eeprom(dev, ee->offset, ee->len, data);
पूर्ण

अटल व्योम smsc75xx_ethtool_get_wol(काष्ठा net_device *net,
				     काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा smsc75xx_priv *pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);

	wolinfo->supported = SUPPORTED_WAKE;
	wolinfo->wolopts = pdata->wolopts;
पूर्ण

अटल पूर्णांक smsc75xx_ethtool_set_wol(काष्ठा net_device *net,
				    काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा smsc75xx_priv *pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);
	पूर्णांक ret;

	अगर (wolinfo->wolopts & ~SUPPORTED_WAKE)
		वापस -EINVAL;

	pdata->wolopts = wolinfo->wolopts & SUPPORTED_WAKE;

	ret = device_set_wakeup_enable(&dev->udev->dev, pdata->wolopts);
	अगर (ret < 0)
		netdev_warn(dev->net, "device_set_wakeup_enable error %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops smsc75xx_ethtool_ops = अणु
	.get_link	= usbnet_get_link,
	.nway_reset	= usbnet_nway_reset,
	.get_drvinfo	= usbnet_get_drvinfo,
	.get_msglevel	= usbnet_get_msglevel,
	.set_msglevel	= usbnet_set_msglevel,
	.get_eeprom_len	= smsc75xx_ethtool_get_eeprom_len,
	.get_eeprom	= smsc75xx_ethtool_get_eeprom,
	.set_eeprom	= smsc75xx_ethtool_set_eeprom,
	.get_wol	= smsc75xx_ethtool_get_wol,
	.set_wol	= smsc75xx_ethtool_set_wol,
	.get_link_ksettings	= usbnet_get_link_ksettings_mii,
	.set_link_ksettings	= usbnet_set_link_ksettings_mii,
पूर्ण;

अटल पूर्णांक smsc75xx_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);

	अगर (!netअगर_running(netdev))
		वापस -EINVAL;

	वापस generic_mii_ioctl(&dev->mii, अगर_mii(rq), cmd, शून्य);
पूर्ण

अटल व्योम smsc75xx_init_mac_address(काष्ठा usbnet *dev)
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
	अगर (smsc75xx_पढ़ो_eeprom(dev, EEPROM_MAC_OFFSET, ETH_ALEN,
			dev->net->dev_addr) == 0) अणु
		अगर (is_valid_ether_addr(dev->net->dev_addr)) अणु
			/* eeprom values are valid so use them */
			netअगर_dbg(dev, अगरup, dev->net,
				  "MAC address read from EEPROM\n");
			वापस;
		पूर्ण
	पूर्ण

	/* no useful अटल MAC address found. generate a अक्रमom one */
	eth_hw_addr_अक्रमom(dev->net);
	netअगर_dbg(dev, अगरup, dev->net, "MAC address set to eth_random_addr\n");
पूर्ण

अटल पूर्णांक smsc75xx_set_mac_address(काष्ठा usbnet *dev)
अणु
	u32 addr_lo = dev->net->dev_addr[0] | dev->net->dev_addr[1] << 8 |
		dev->net->dev_addr[2] << 16 | dev->net->dev_addr[3] << 24;
	u32 addr_hi = dev->net->dev_addr[4] | dev->net->dev_addr[5] << 8;

	पूर्णांक ret = smsc75xx_ग_लिखो_reg(dev, RX_ADDRH, addr_hi);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write RX_ADDRH: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = smsc75xx_ग_लिखो_reg(dev, RX_ADDRL, addr_lo);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write RX_ADDRL: %d\n", ret);
		वापस ret;
	पूर्ण

	addr_hi |= ADDR_FILTX_FB_VALID;
	ret = smsc75xx_ग_लिखो_reg(dev, ADDR_FILTX, addr_hi);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write ADDR_FILTX: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = smsc75xx_ग_लिखो_reg(dev, ADDR_FILTX + 4, addr_lo);
	अगर (ret < 0)
		netdev_warn(dev->net, "Failed to write ADDR_FILTX+4: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक smsc75xx_phy_initialize(काष्ठा usbnet *dev)
अणु
	पूर्णांक bmcr, ret, समयout = 0;

	/* Initialize MII काष्ठाure */
	dev->mii.dev = dev->net;
	dev->mii.mdio_पढ़ो = smsc75xx_mdio_पढ़ो;
	dev->mii.mdio_ग_लिखो = smsc75xx_mdio_ग_लिखो;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.supports_gmii = 1;
	dev->mii.phy_id = SMSC75XX_INTERNAL_PHY_ID;

	/* reset phy and रुको क्रम reset to complete */
	smsc75xx_mdio_ग_लिखो(dev->net, dev->mii.phy_id, MII_BMCR, BMCR_RESET);

	करो अणु
		msleep(10);
		bmcr = smsc75xx_mdio_पढ़ो(dev->net, dev->mii.phy_id, MII_BMCR);
		अगर (bmcr < 0) अणु
			netdev_warn(dev->net, "Error reading MII_BMCR\n");
			वापस bmcr;
		पूर्ण
		समयout++;
	पूर्ण जबतक ((bmcr & BMCR_RESET) && (समयout < 100));

	अगर (समयout >= 100) अणु
		netdev_warn(dev->net, "timeout on PHY Reset\n");
		वापस -EIO;
	पूर्ण

	/* phy workaround क्रम gig link */
	smsc75xx_phy_gig_workaround(dev);

	smsc75xx_mdio_ग_लिखो(dev->net, dev->mii.phy_id, MII_ADVERTISE,
		ADVERTISE_ALL | ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP |
		ADVERTISE_PAUSE_ASYM);
	smsc75xx_mdio_ग_लिखो(dev->net, dev->mii.phy_id, MII_CTRL1000,
		ADVERTISE_1000FULL);

	/* पढ़ो and ग_लिखो to clear phy पूर्णांकerrupt status */
	ret = smsc75xx_mdio_पढ़ो(dev->net, dev->mii.phy_id, PHY_INT_SRC);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading PHY_INT_SRC\n");
		वापस ret;
	पूर्ण

	smsc75xx_mdio_ग_लिखो(dev->net, dev->mii.phy_id, PHY_INT_SRC, 0xffff);

	smsc75xx_mdio_ग_लिखो(dev->net, dev->mii.phy_id, PHY_INT_MASK,
		PHY_INT_MASK_DEFAULT);
	mii_nway_restart(&dev->mii);

	netअगर_dbg(dev, अगरup, dev->net, "phy initialised successfully\n");
	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_set_rx_max_frame_length(काष्ठा usbnet *dev, पूर्णांक size)
अणु
	पूर्णांक ret = 0;
	u32 buf;
	bool rxenabled;

	ret = smsc75xx_पढ़ो_reg(dev, MAC_RX, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read MAC_RX: %d\n", ret);
		वापस ret;
	पूर्ण

	rxenabled = ((buf & MAC_RX_RXEN) != 0);

	अगर (rxenabled) अणु
		buf &= ~MAC_RX_RXEN;
		ret = smsc75xx_ग_लिखो_reg(dev, MAC_RX, buf);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Failed to write MAC_RX: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* add 4 to size क्रम FCS */
	buf &= ~MAC_RX_MAX_SIZE;
	buf |= (((size + 4) << MAC_RX_MAX_SIZE_SHIFT) & MAC_RX_MAX_SIZE);

	ret = smsc75xx_ग_लिखो_reg(dev, MAC_RX, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write MAC_RX: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (rxenabled) अणु
		buf |= MAC_RX_RXEN;
		ret = smsc75xx_ग_लिखो_reg(dev, MAC_RX, buf);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Failed to write MAC_RX: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	पूर्णांक ret;

	ret = smsc75xx_set_rx_max_frame_length(dev, new_mtu + ETH_HLEN);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to set mac rx frame length\n");
		वापस ret;
	पूर्ण

	वापस usbnet_change_mtu(netdev, new_mtu);
पूर्ण

/* Enable or disable Rx checksum offload engine */
अटल पूर्णांक smsc75xx_set_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	काष्ठा smsc75xx_priv *pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&pdata->rfe_ctl_lock, flags);

	अगर (features & NETIF_F_RXCSUM)
		pdata->rfe_ctl |= RFE_CTL_TCPUDP_CKM | RFE_CTL_IP_CKM;
	अन्यथा
		pdata->rfe_ctl &= ~(RFE_CTL_TCPUDP_CKM | RFE_CTL_IP_CKM);

	spin_unlock_irqrestore(&pdata->rfe_ctl_lock, flags);
	/* it's racing here! */

	ret = smsc75xx_ग_लिखो_reg(dev, RFE_CTL, pdata->rfe_ctl);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing RFE_CTL\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_रुको_पढ़ोy(काष्ठा usbnet *dev, पूर्णांक in_pm)
अणु
	पूर्णांक समयout = 0;

	करो अणु
		u32 buf;
		पूर्णांक ret;

		ret = __smsc75xx_पढ़ो_reg(dev, PMT_CTL, &buf, in_pm);

		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Failed to read PMT_CTL: %d\n", ret);
			वापस ret;
		पूर्ण

		अगर (buf & PMT_CTL_DEV_RDY)
			वापस 0;

		msleep(10);
		समयout++;
	पूर्ण जबतक (समयout < 100);

	netdev_warn(dev->net, "timeout waiting for device ready\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक smsc75xx_phy_gig_workaround(काष्ठा usbnet *dev)
अणु
	काष्ठा mii_अगर_info *mii = &dev->mii;
	पूर्णांक ret = 0, समयout = 0;
	u32 buf, link_up = 0;

	/* Set the phy in Gig loopback */
	smsc75xx_mdio_ग_लिखो(dev->net, mii->phy_id, MII_BMCR, 0x4040);

	/* Wait क्रम the link up */
	करो अणु
		link_up = smsc75xx_link_ok_nopm(dev);
		usleep_range(10000, 20000);
		समयout++;
	पूर्ण जबतक ((!link_up) && (समयout < 1000));

	अगर (समयout >= 1000) अणु
		netdev_warn(dev->net, "Timeout waiting for PHY link up\n");
		वापस -EIO;
	पूर्ण

	/* phy reset */
	ret = smsc75xx_पढ़ो_reg(dev, PMT_CTL, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read PMT_CTL: %d\n", ret);
		वापस ret;
	पूर्ण

	buf |= PMT_CTL_PHY_RST;

	ret = smsc75xx_ग_लिखो_reg(dev, PMT_CTL, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write PMT_CTL: %d\n", ret);
		वापस ret;
	पूर्ण

	समयout = 0;
	करो अणु
		usleep_range(10000, 20000);
		ret = smsc75xx_पढ़ो_reg(dev, PMT_CTL, &buf);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Failed to read PMT_CTL: %d\n",
				    ret);
			वापस ret;
		पूर्ण
		समयout++;
	पूर्ण जबतक ((buf & PMT_CTL_PHY_RST) && (समयout < 100));

	अगर (समयout >= 100) अणु
		netdev_warn(dev->net, "timeout waiting for PHY Reset\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा smsc75xx_priv *pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);
	u32 buf;
	पूर्णांक ret = 0, समयout;

	netअगर_dbg(dev, अगरup, dev->net, "entering smsc75xx_reset\n");

	ret = smsc75xx_रुको_पढ़ोy(dev, 0);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "device not ready in smsc75xx_reset\n");
		वापस ret;
	पूर्ण

	ret = smsc75xx_पढ़ो_reg(dev, HW_CFG, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read HW_CFG: %d\n", ret);
		वापस ret;
	पूर्ण

	buf |= HW_CFG_LRST;

	ret = smsc75xx_ग_लिखो_reg(dev, HW_CFG, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write HW_CFG: %d\n", ret);
		वापस ret;
	पूर्ण

	समयout = 0;
	करो अणु
		msleep(10);
		ret = smsc75xx_पढ़ो_reg(dev, HW_CFG, &buf);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Failed to read HW_CFG: %d\n", ret);
			वापस ret;
		पूर्ण
		समयout++;
	पूर्ण जबतक ((buf & HW_CFG_LRST) && (समयout < 100));

	अगर (समयout >= 100) अणु
		netdev_warn(dev->net, "timeout on completion of Lite Reset\n");
		वापस -EIO;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "Lite reset complete, resetting PHY\n");

	ret = smsc75xx_पढ़ो_reg(dev, PMT_CTL, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read PMT_CTL: %d\n", ret);
		वापस ret;
	पूर्ण

	buf |= PMT_CTL_PHY_RST;

	ret = smsc75xx_ग_लिखो_reg(dev, PMT_CTL, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write PMT_CTL: %d\n", ret);
		वापस ret;
	पूर्ण

	समयout = 0;
	करो अणु
		msleep(10);
		ret = smsc75xx_पढ़ो_reg(dev, PMT_CTL, &buf);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Failed to read PMT_CTL: %d\n", ret);
			वापस ret;
		पूर्ण
		समयout++;
	पूर्ण जबतक ((buf & PMT_CTL_PHY_RST) && (समयout < 100));

	अगर (समयout >= 100) अणु
		netdev_warn(dev->net, "timeout waiting for PHY Reset\n");
		वापस -EIO;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "PHY reset complete\n");

	ret = smsc75xx_set_mac_address(dev);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to set mac address\n");
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "MAC Address: %pM\n",
		  dev->net->dev_addr);

	ret = smsc75xx_पढ़ो_reg(dev, HW_CFG, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read HW_CFG: %d\n", ret);
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "Read Value from HW_CFG : 0x%08x\n",
		  buf);

	buf |= HW_CFG_BIR;

	ret = smsc75xx_ग_लिखो_reg(dev, HW_CFG, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net,  "Failed to write HW_CFG: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = smsc75xx_पढ़ो_reg(dev, HW_CFG, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read HW_CFG: %d\n", ret);
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "Read Value from HW_CFG after writing HW_CFG_BIR: 0x%08x\n",
		  buf);

	अगर (!turbo_mode) अणु
		buf = 0;
		dev->rx_urb_size = MAX_SINGLE_PACKET_SIZE;
	पूर्ण अन्यथा अगर (dev->udev->speed == USB_SPEED_HIGH) अणु
		buf = DEFAULT_HS_BURST_CAP_SIZE / HS_USB_PKT_SIZE;
		dev->rx_urb_size = DEFAULT_HS_BURST_CAP_SIZE;
	पूर्ण अन्यथा अणु
		buf = DEFAULT_FS_BURST_CAP_SIZE / FS_USB_PKT_SIZE;
		dev->rx_urb_size = DEFAULT_FS_BURST_CAP_SIZE;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "rx_urb_size=%ld\n",
		  (uदीर्घ)dev->rx_urb_size);

	ret = smsc75xx_ग_लिखो_reg(dev, BURST_CAP, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write BURST_CAP: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = smsc75xx_पढ़ो_reg(dev, BURST_CAP, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read BURST_CAP: %d\n", ret);
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net,
		  "Read Value from BURST_CAP after writing: 0x%08x\n", buf);

	ret = smsc75xx_ग_लिखो_reg(dev, BULK_IN_DLY, DEFAULT_BULK_IN_DELAY);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write BULK_IN_DLY: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = smsc75xx_पढ़ो_reg(dev, BULK_IN_DLY, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read BULK_IN_DLY: %d\n", ret);
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net,
		  "Read Value from BULK_IN_DLY after writing: 0x%08x\n", buf);

	अगर (turbo_mode) अणु
		ret = smsc75xx_पढ़ो_reg(dev, HW_CFG, &buf);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Failed to read HW_CFG: %d\n", ret);
			वापस ret;
		पूर्ण

		netअगर_dbg(dev, अगरup, dev->net, "HW_CFG: 0x%08x\n", buf);

		buf |= (HW_CFG_MEF | HW_CFG_BCE);

		ret = smsc75xx_ग_लिखो_reg(dev, HW_CFG, buf);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Failed to write HW_CFG: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = smsc75xx_पढ़ो_reg(dev, HW_CFG, &buf);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Failed to read HW_CFG: %d\n", ret);
			वापस ret;
		पूर्ण

		netअगर_dbg(dev, अगरup, dev->net, "HW_CFG: 0x%08x\n", buf);
	पूर्ण

	/* set FIFO sizes */
	buf = (MAX_RX_FIFO_SIZE - 512) / 512;
	ret = smsc75xx_ग_लिखो_reg(dev, FCT_RX_FIFO_END, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write FCT_RX_FIFO_END: %d\n", ret);
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "FCT_RX_FIFO_END set to 0x%08x\n", buf);

	buf = (MAX_TX_FIFO_SIZE - 512) / 512;
	ret = smsc75xx_ग_लिखो_reg(dev, FCT_TX_FIFO_END, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write FCT_TX_FIFO_END: %d\n", ret);
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "FCT_TX_FIFO_END set to 0x%08x\n", buf);

	ret = smsc75xx_ग_लिखो_reg(dev, INT_STS, INT_STS_CLEAR_ALL);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write INT_STS: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = smsc75xx_पढ़ो_reg(dev, ID_REV, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read ID_REV: %d\n", ret);
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "ID_REV = 0x%08x\n", buf);

	ret = smsc75xx_पढ़ो_reg(dev, E2P_CMD, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read E2P_CMD: %d\n", ret);
		वापस ret;
	पूर्ण

	/* only set शेष GPIO/LED settings अगर no EEPROM is detected */
	अगर (!(buf & E2P_CMD_LOADED)) अणु
		ret = smsc75xx_पढ़ो_reg(dev, LED_GPIO_CFG, &buf);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Failed to read LED_GPIO_CFG: %d\n", ret);
			वापस ret;
		पूर्ण

		buf &= ~(LED_GPIO_CFG_LED2_FUN_SEL | LED_GPIO_CFG_LED10_FUN_SEL);
		buf |= LED_GPIO_CFG_LEDGPIO_EN | LED_GPIO_CFG_LED2_FUN_SEL;

		ret = smsc75xx_ग_लिखो_reg(dev, LED_GPIO_CFG, buf);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Failed to write LED_GPIO_CFG: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = smsc75xx_ग_लिखो_reg(dev, FLOW, 0);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write FLOW: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = smsc75xx_ग_लिखो_reg(dev, FCT_FLOW, 0);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write FCT_FLOW: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Don't need rfe_ctl_lock during initialisation */
	ret = smsc75xx_पढ़ो_reg(dev, RFE_CTL, &pdata->rfe_ctl);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read RFE_CTL: %d\n", ret);
		वापस ret;
	पूर्ण

	pdata->rfe_ctl |= RFE_CTL_AB | RFE_CTL_DPF;

	ret = smsc75xx_ग_लिखो_reg(dev, RFE_CTL, pdata->rfe_ctl);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write RFE_CTL: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = smsc75xx_पढ़ो_reg(dev, RFE_CTL, &pdata->rfe_ctl);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read RFE_CTL: %d\n", ret);
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "RFE_CTL set to 0x%08x\n",
		  pdata->rfe_ctl);

	/* Enable or disable checksum offload engines */
	smsc75xx_set_features(dev->net, dev->net->features);

	smsc75xx_set_multicast(dev->net);

	ret = smsc75xx_phy_initialize(dev);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to initialize PHY: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = smsc75xx_पढ़ो_reg(dev, INT_EP_CTL, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read INT_EP_CTL: %d\n", ret);
		वापस ret;
	पूर्ण

	/* enable PHY पूर्णांकerrupts */
	buf |= INT_ENP_PHY_INT;

	ret = smsc75xx_ग_लिखो_reg(dev, INT_EP_CTL, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write INT_EP_CTL: %d\n", ret);
		वापस ret;
	पूर्ण

	/* allow mac to detect speed and duplex from phy */
	ret = smsc75xx_पढ़ो_reg(dev, MAC_CR, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read MAC_CR: %d\n", ret);
		वापस ret;
	पूर्ण

	buf |= (MAC_CR_ADD | MAC_CR_ASD);
	ret = smsc75xx_ग_लिखो_reg(dev, MAC_CR, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write MAC_CR: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = smsc75xx_पढ़ो_reg(dev, MAC_TX, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read MAC_TX: %d\n", ret);
		वापस ret;
	पूर्ण

	buf |= MAC_TX_TXEN;

	ret = smsc75xx_ग_लिखो_reg(dev, MAC_TX, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write MAC_TX: %d\n", ret);
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "MAC_TX set to 0x%08x\n", buf);

	ret = smsc75xx_पढ़ो_reg(dev, FCT_TX_CTL, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read FCT_TX_CTL: %d\n", ret);
		वापस ret;
	पूर्ण

	buf |= FCT_TX_CTL_EN;

	ret = smsc75xx_ग_लिखो_reg(dev, FCT_TX_CTL, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write FCT_TX_CTL: %d\n", ret);
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "FCT_TX_CTL set to 0x%08x\n", buf);

	ret = smsc75xx_set_rx_max_frame_length(dev, dev->net->mtu + ETH_HLEN);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to set max rx frame length\n");
		वापस ret;
	पूर्ण

	ret = smsc75xx_पढ़ो_reg(dev, MAC_RX, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read MAC_RX: %d\n", ret);
		वापस ret;
	पूर्ण

	buf |= MAC_RX_RXEN;

	ret = smsc75xx_ग_लिखो_reg(dev, MAC_RX, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write MAC_RX: %d\n", ret);
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "MAC_RX set to 0x%08x\n", buf);

	ret = smsc75xx_पढ़ो_reg(dev, FCT_RX_CTL, &buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read FCT_RX_CTL: %d\n", ret);
		वापस ret;
	पूर्ण

	buf |= FCT_RX_CTL_EN;

	ret = smsc75xx_ग_लिखो_reg(dev, FCT_RX_CTL, buf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write FCT_RX_CTL: %d\n", ret);
		वापस ret;
	पूर्ण

	netअगर_dbg(dev, अगरup, dev->net, "FCT_RX_CTL set to 0x%08x\n", buf);

	netअगर_dbg(dev, अगरup, dev->net, "smsc75xx_reset, return 0\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops smsc75xx_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_change_mtu		= smsc75xx_change_mtu,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl 		= smsc75xx_ioctl,
	.nकरो_set_rx_mode	= smsc75xx_set_multicast,
	.nकरो_set_features	= smsc75xx_set_features,
पूर्ण;

अटल पूर्णांक smsc75xx_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा smsc75xx_priv *pdata = शून्य;
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO SMSC_CHIPNAME " v" SMSC_DRIVER_VERSION "\n");

	ret = usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "usbnet_get_endpoints failed: %d\n", ret);
		वापस ret;
	पूर्ण

	dev->data[0] = (अचिन्हित दीर्घ)kzalloc(माप(काष्ठा smsc75xx_priv),
					      GFP_KERNEL);

	pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->dev = dev;

	spin_lock_init(&pdata->rfe_ctl_lock);
	mutex_init(&pdata->dataport_mutex);

	INIT_WORK(&pdata->set_multicast, smsc75xx_deferred_multicast_ग_लिखो);

	अगर (DEFAULT_TX_CSUM_ENABLE)
		dev->net->features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;

	अगर (DEFAULT_RX_CSUM_ENABLE)
		dev->net->features |= NETIF_F_RXCSUM;

	dev->net->hw_features = NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				NETIF_F_RXCSUM;

	ret = smsc75xx_रुको_पढ़ोy(dev, 0);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "device not ready in smsc75xx_bind\n");
		जाओ मुक्त_pdata;
	पूर्ण

	smsc75xx_init_mac_address(dev);

	/* Init all रेजिस्टरs */
	ret = smsc75xx_reset(dev);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "smsc75xx_reset error %d\n", ret);
		जाओ cancel_work;
	पूर्ण

	dev->net->netdev_ops = &smsc75xx_netdev_ops;
	dev->net->ethtool_ops = &smsc75xx_ethtool_ops;
	dev->net->flags |= IFF_MULTICAST;
	dev->net->hard_header_len += SMSC75XX_TX_OVERHEAD;
	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;
	dev->net->max_mtu = MAX_SINGLE_PACKET_SIZE;
	वापस 0;

cancel_work:
	cancel_work_sync(&pdata->set_multicast);
मुक्त_pdata:
	kमुक्त(pdata);
	dev->data[0] = 0;
	वापस ret;
पूर्ण

अटल व्योम smsc75xx_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा smsc75xx_priv *pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);
	अगर (pdata) अणु
		cancel_work_sync(&pdata->set_multicast);
		netअगर_dbg(dev, अगरकरोwn, dev->net, "free pdata\n");
		kमुक्त(pdata);
		dev->data[0] = 0;
	पूर्ण
पूर्ण

अटल u16 smsc_crc(स्थिर u8 *buffer, माप_प्रकार len)
अणु
	वापस bitrev16(crc16(0xFFFF, buffer, len));
पूर्ण

अटल पूर्णांक smsc75xx_ग_लिखो_wuff(काष्ठा usbnet *dev, पूर्णांक filter, u32 wuf_cfg,
			       u32 wuf_mask1)
अणु
	पूर्णांक cfg_base = WUF_CFGX + filter * 4;
	पूर्णांक mask_base = WUF_MASKX + filter * 16;
	पूर्णांक ret;

	ret = smsc75xx_ग_लिखो_reg(dev, cfg_base, wuf_cfg);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing WUF_CFGX\n");
		वापस ret;
	पूर्ण

	ret = smsc75xx_ग_लिखो_reg(dev, mask_base, wuf_mask1);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing WUF_MASKX\n");
		वापस ret;
	पूर्ण

	ret = smsc75xx_ग_लिखो_reg(dev, mask_base + 4, 0);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing WUF_MASKX\n");
		वापस ret;
	पूर्ण

	ret = smsc75xx_ग_लिखो_reg(dev, mask_base + 8, 0);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing WUF_MASKX\n");
		वापस ret;
	पूर्ण

	ret = smsc75xx_ग_लिखो_reg(dev, mask_base + 12, 0);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing WUF_MASKX\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_enter_suspend0(काष्ठा usbnet *dev)
अणु
	काष्ठा smsc75xx_priv *pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);
	u32 val;
	पूर्णांक ret;

	ret = smsc75xx_पढ़ो_reg_nopm(dev, PMT_CTL, &val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading PMT_CTL\n");
		वापस ret;
	पूर्ण

	val &= (~(PMT_CTL_SUS_MODE | PMT_CTL_PHY_RST));
	val |= PMT_CTL_SUS_MODE_0 | PMT_CTL_WOL_EN | PMT_CTL_WUPS;

	ret = smsc75xx_ग_लिखो_reg_nopm(dev, PMT_CTL, val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing PMT_CTL\n");
		वापस ret;
	पूर्ण

	pdata->suspend_flags |= SUSPEND_SUSPEND0;

	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_enter_suspend1(काष्ठा usbnet *dev)
अणु
	काष्ठा smsc75xx_priv *pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);
	u32 val;
	पूर्णांक ret;

	ret = smsc75xx_पढ़ो_reg_nopm(dev, PMT_CTL, &val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading PMT_CTL\n");
		वापस ret;
	पूर्ण

	val &= ~(PMT_CTL_SUS_MODE | PMT_CTL_WUPS | PMT_CTL_PHY_RST);
	val |= PMT_CTL_SUS_MODE_1;

	ret = smsc75xx_ग_लिखो_reg_nopm(dev, PMT_CTL, val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing PMT_CTL\n");
		वापस ret;
	पूर्ण

	/* clear wol status, enable energy detection */
	val &= ~PMT_CTL_WUPS;
	val |= (PMT_CTL_WUPS_ED | PMT_CTL_ED_EN);

	ret = smsc75xx_ग_लिखो_reg_nopm(dev, PMT_CTL, val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing PMT_CTL\n");
		वापस ret;
	पूर्ण

	pdata->suspend_flags |= SUSPEND_SUSPEND1;

	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_enter_suspend2(काष्ठा usbnet *dev)
अणु
	काष्ठा smsc75xx_priv *pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);
	u32 val;
	पूर्णांक ret;

	ret = smsc75xx_पढ़ो_reg_nopm(dev, PMT_CTL, &val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading PMT_CTL\n");
		वापस ret;
	पूर्ण

	val &= ~(PMT_CTL_SUS_MODE | PMT_CTL_WUPS | PMT_CTL_PHY_RST);
	val |= PMT_CTL_SUS_MODE_2;

	ret = smsc75xx_ग_लिखो_reg_nopm(dev, PMT_CTL, val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing PMT_CTL\n");
		वापस ret;
	पूर्ण

	pdata->suspend_flags |= SUSPEND_SUSPEND2;

	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_enter_suspend3(काष्ठा usbnet *dev)
अणु
	काष्ठा smsc75xx_priv *pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);
	u32 val;
	पूर्णांक ret;

	ret = smsc75xx_पढ़ो_reg_nopm(dev, FCT_RX_CTL, &val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading FCT_RX_CTL\n");
		वापस ret;
	पूर्ण

	अगर (val & FCT_RX_CTL_RXUSED) अणु
		netdev_dbg(dev->net, "rx fifo not empty in autosuspend\n");
		वापस -EBUSY;
	पूर्ण

	ret = smsc75xx_पढ़ो_reg_nopm(dev, PMT_CTL, &val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading PMT_CTL\n");
		वापस ret;
	पूर्ण

	val &= ~(PMT_CTL_SUS_MODE | PMT_CTL_WUPS | PMT_CTL_PHY_RST);
	val |= PMT_CTL_SUS_MODE_3 | PMT_CTL_RES_CLR_WKP_EN;

	ret = smsc75xx_ग_लिखो_reg_nopm(dev, PMT_CTL, val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing PMT_CTL\n");
		वापस ret;
	पूर्ण

	/* clear wol status */
	val &= ~PMT_CTL_WUPS;
	val |= PMT_CTL_WUPS_WOL;

	ret = smsc75xx_ग_लिखो_reg_nopm(dev, PMT_CTL, val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing PMT_CTL\n");
		वापस ret;
	पूर्ण

	pdata->suspend_flags |= SUSPEND_SUSPEND3;

	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_enable_phy_wakeup_पूर्णांकerrupts(काष्ठा usbnet *dev, u16 mask)
अणु
	काष्ठा mii_अगर_info *mii = &dev->mii;
	पूर्णांक ret;

	netdev_dbg(dev->net, "enabling PHY wakeup interrupts\n");

	/* पढ़ो to clear */
	ret = smsc75xx_mdio_पढ़ो_nopm(dev->net, mii->phy_id, PHY_INT_SRC);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading PHY_INT_SRC\n");
		वापस ret;
	पूर्ण

	/* enable पूर्णांकerrupt source */
	ret = smsc75xx_mdio_पढ़ो_nopm(dev->net, mii->phy_id, PHY_INT_MASK);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading PHY_INT_MASK\n");
		वापस ret;
	पूर्ण

	ret |= mask;

	smsc75xx_mdio_ग_लिखो_nopm(dev->net, mii->phy_id, PHY_INT_MASK, ret);

	वापस 0;
पूर्ण

अटल पूर्णांक smsc75xx_link_ok_nopm(काष्ठा usbnet *dev)
अणु
	काष्ठा mii_अगर_info *mii = &dev->mii;
	पूर्णांक ret;

	/* first, a dummy पढ़ो, needed to latch some MII phys */
	ret = smsc75xx_mdio_पढ़ो_nopm(dev->net, mii->phy_id, MII_BMSR);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading MII_BMSR\n");
		वापस ret;
	पूर्ण

	ret = smsc75xx_mdio_पढ़ो_nopm(dev->net, mii->phy_id, MII_BMSR);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading MII_BMSR\n");
		वापस ret;
	पूर्ण

	वापस !!(ret & BMSR_LSTATUS);
पूर्ण

अटल पूर्णांक smsc75xx_स्वतःsuspend(काष्ठा usbnet *dev, u32 link_up)
अणु
	पूर्णांक ret;

	अगर (!netअगर_running(dev->net)) अणु
		/* पूर्णांकerface is अगरconfig करोwn so fully घातer करोwn hw */
		netdev_dbg(dev->net, "autosuspend entering SUSPEND2\n");
		वापस smsc75xx_enter_suspend2(dev);
	पूर्ण

	अगर (!link_up) अणु
		/* link is करोwn so enter EDPD mode */
		netdev_dbg(dev->net, "autosuspend entering SUSPEND1\n");

		/* enable PHY wakeup events क्रम अगर cable is attached */
		ret = smsc75xx_enable_phy_wakeup_पूर्णांकerrupts(dev,
			PHY_INT_MASK_ANEG_COMP);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "error enabling PHY wakeup ints\n");
			वापस ret;
		पूर्ण

		netdev_info(dev->net, "entering SUSPEND1 mode\n");
		वापस smsc75xx_enter_suspend1(dev);
	पूर्ण

	/* enable PHY wakeup events so we remote wakeup अगर cable is pulled */
	ret = smsc75xx_enable_phy_wakeup_पूर्णांकerrupts(dev,
		PHY_INT_MASK_LINK_DOWN);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "error enabling PHY wakeup ints\n");
		वापस ret;
	पूर्ण

	netdev_dbg(dev->net, "autosuspend entering SUSPEND3\n");
	वापस smsc75xx_enter_suspend3(dev);
पूर्ण

अटल पूर्णांक smsc75xx_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा smsc75xx_priv *pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);
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
	link_up = smsc75xx_link_ok_nopm(dev);

	अगर (message.event == PM_EVENT_AUTO_SUSPEND) अणु
		ret = smsc75xx_स्वतःsuspend(dev, link_up);
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
		ret = smsc75xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading WUCSR\n");
			जाओ करोne;
		पूर्ण

		val &= ~(WUCSR_MPEN | WUCSR_WUEN);

		ret = smsc75xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing WUCSR\n");
			जाओ करोne;
		पूर्ण

		ret = smsc75xx_पढ़ो_reg_nopm(dev, PMT_CTL, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading PMT_CTL\n");
			जाओ करोne;
		पूर्ण

		val &= ~(PMT_CTL_ED_EN | PMT_CTL_WOL_EN);

		ret = smsc75xx_ग_लिखो_reg_nopm(dev, PMT_CTL, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing PMT_CTL\n");
			जाओ करोne;
		पूर्ण

		ret = smsc75xx_enter_suspend2(dev);
		जाओ करोne;
	पूर्ण

	अगर (pdata->wolopts & WAKE_PHY) अणु
		ret = smsc75xx_enable_phy_wakeup_पूर्णांकerrupts(dev,
			(PHY_INT_MASK_ANEG_COMP | PHY_INT_MASK_LINK_DOWN));
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "error enabling PHY wakeup ints\n");
			जाओ करोne;
		पूर्ण

		/* अगर link is करोwn then configure EDPD and enter SUSPEND1,
		 * otherwise enter SUSPEND0 below
		 */
		अगर (!link_up) अणु
			काष्ठा mii_अगर_info *mii = &dev->mii;
			netdev_info(dev->net, "entering SUSPEND1 mode\n");

			/* enable energy detect घातer-करोwn mode */
			ret = smsc75xx_mdio_पढ़ो_nopm(dev->net, mii->phy_id,
				PHY_MODE_CTRL_STS);
			अगर (ret < 0) अणु
				netdev_warn(dev->net, "Error reading PHY_MODE_CTRL_STS\n");
				जाओ करोne;
			पूर्ण

			ret |= MODE_CTRL_STS_EDPWRDOWN;

			smsc75xx_mdio_ग_लिखो_nopm(dev->net, mii->phy_id,
				PHY_MODE_CTRL_STS, ret);

			/* enter SUSPEND1 mode */
			ret = smsc75xx_enter_suspend1(dev);
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (pdata->wolopts & (WAKE_MCAST | WAKE_ARP)) अणु
		पूर्णांक i, filter = 0;

		/* disable all filters */
		क्रम (i = 0; i < WUF_NUM; i++) अणु
			ret = smsc75xx_ग_लिखो_reg_nopm(dev, WUF_CFGX + i * 4, 0);
			अगर (ret < 0) अणु
				netdev_warn(dev->net, "Error writing WUF_CFGX\n");
				जाओ करोne;
			पूर्ण
		पूर्ण

		अगर (pdata->wolopts & WAKE_MCAST) अणु
			स्थिर u8 mcast[] = अणु0x01, 0x00, 0x5Eपूर्ण;
			netdev_info(dev->net, "enabling multicast detection\n");

			val = WUF_CFGX_EN | WUF_CFGX_ATYPE_MULTICAST
				| smsc_crc(mcast, 3);
			ret = smsc75xx_ग_लिखो_wuff(dev, filter++, val, 0x0007);
			अगर (ret < 0) अणु
				netdev_warn(dev->net, "Error writing wakeup filter\n");
				जाओ करोne;
			पूर्ण
		पूर्ण

		अगर (pdata->wolopts & WAKE_ARP) अणु
			स्थिर u8 arp[] = अणु0x08, 0x06पूर्ण;
			netdev_info(dev->net, "enabling ARP detection\n");

			val = WUF_CFGX_EN | WUF_CFGX_ATYPE_ALL | (0x0C << 16)
				| smsc_crc(arp, 2);
			ret = smsc75xx_ग_लिखो_wuff(dev, filter++, val, 0x0003);
			अगर (ret < 0) अणु
				netdev_warn(dev->net, "Error writing wakeup filter\n");
				जाओ करोne;
			पूर्ण
		पूर्ण

		/* clear any pending pattern match packet status */
		ret = smsc75xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading WUCSR\n");
			जाओ करोne;
		पूर्ण

		val |= WUCSR_WUFR;

		ret = smsc75xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing WUCSR\n");
			जाओ करोne;
		पूर्ण

		netdev_info(dev->net, "enabling packet match detection\n");
		ret = smsc75xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading WUCSR\n");
			जाओ करोne;
		पूर्ण

		val |= WUCSR_WUEN;

		ret = smsc75xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing WUCSR\n");
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev_info(dev->net, "disabling packet match detection\n");
		ret = smsc75xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading WUCSR\n");
			जाओ करोne;
		पूर्ण

		val &= ~WUCSR_WUEN;

		ret = smsc75xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing WUCSR\n");
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* disable magic, bcast & unicast wakeup sources */
	ret = smsc75xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error reading WUCSR\n");
		जाओ करोne;
	पूर्ण

	val &= ~(WUCSR_MPEN | WUCSR_BCST_EN | WUCSR_PFDA_EN);

	ret = smsc75xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Error writing WUCSR\n");
		जाओ करोne;
	पूर्ण

	अगर (pdata->wolopts & WAKE_PHY) अणु
		netdev_info(dev->net, "enabling PHY wakeup\n");

		ret = smsc75xx_पढ़ो_reg_nopm(dev, PMT_CTL, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading PMT_CTL\n");
			जाओ करोne;
		पूर्ण

		/* clear wol status, enable energy detection */
		val &= ~PMT_CTL_WUPS;
		val |= (PMT_CTL_WUPS_ED | PMT_CTL_ED_EN);

		ret = smsc75xx_ग_लिखो_reg_nopm(dev, PMT_CTL, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing PMT_CTL\n");
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (pdata->wolopts & WAKE_MAGIC) अणु
		netdev_info(dev->net, "enabling magic packet wakeup\n");
		ret = smsc75xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading WUCSR\n");
			जाओ करोne;
		पूर्ण

		/* clear any pending magic packet status */
		val |= WUCSR_MPR | WUCSR_MPEN;

		ret = smsc75xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing WUCSR\n");
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (pdata->wolopts & WAKE_BCAST) अणु
		netdev_info(dev->net, "enabling broadcast detection\n");
		ret = smsc75xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading WUCSR\n");
			जाओ करोne;
		पूर्ण

		val |= WUCSR_BCAST_FR | WUCSR_BCST_EN;

		ret = smsc75xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing WUCSR\n");
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (pdata->wolopts & WAKE_UCAST) अणु
		netdev_info(dev->net, "enabling unicast detection\n");
		ret = smsc75xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading WUCSR\n");
			जाओ करोne;
		पूर्ण

		val |= WUCSR_WUFR | WUCSR_PFDA_EN;

		ret = smsc75xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing WUCSR\n");
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* enable receiver to enable frame reception */
	ret = smsc75xx_पढ़ो_reg_nopm(dev, MAC_RX, &val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to read MAC_RX: %d\n", ret);
		जाओ करोne;
	पूर्ण

	val |= MAC_RX_RXEN;

	ret = smsc75xx_ग_लिखो_reg_nopm(dev, MAC_RX, val);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "Failed to write MAC_RX: %d\n", ret);
		जाओ करोne;
	पूर्ण

	/* some wol options are enabled, so enter SUSPEND0 */
	netdev_info(dev->net, "entering SUSPEND0 mode\n");
	ret = smsc75xx_enter_suspend0(dev);

करोne:
	/*
	 * TODO: resume() might need to handle the suspend failure
	 * in प्रणाली sleep
	 */
	अगर (ret && PMSG_IS_AUTO(message))
		usbnet_resume(पूर्णांकf);
	वापस ret;
पूर्ण

अटल पूर्णांक smsc75xx_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा smsc75xx_priv *pdata = (काष्ठा smsc75xx_priv *)(dev->data[0]);
	u8 suspend_flags = pdata->suspend_flags;
	पूर्णांक ret;
	u32 val;

	netdev_dbg(dev->net, "resume suspend_flags=0x%02x\n", suspend_flags);

	/* करो this first to ensure it's cleared even in error हाल */
	pdata->suspend_flags = 0;

	अगर (suspend_flags & SUSPEND_ALLMODES) अणु
		/* Disable wakeup sources */
		ret = smsc75xx_पढ़ो_reg_nopm(dev, WUCSR, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading WUCSR\n");
			वापस ret;
		पूर्ण

		val &= ~(WUCSR_WUEN | WUCSR_MPEN | WUCSR_PFDA_EN
			| WUCSR_BCST_EN);

		ret = smsc75xx_ग_लिखो_reg_nopm(dev, WUCSR, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing WUCSR\n");
			वापस ret;
		पूर्ण

		/* clear wake-up status */
		ret = smsc75xx_पढ़ो_reg_nopm(dev, PMT_CTL, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading PMT_CTL\n");
			वापस ret;
		पूर्ण

		val &= ~PMT_CTL_WOL_EN;
		val |= PMT_CTL_WUPS;

		ret = smsc75xx_ग_लिखो_reg_nopm(dev, PMT_CTL, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing PMT_CTL\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (suspend_flags & SUSPEND_SUSPEND2) अणु
		netdev_info(dev->net, "resuming from SUSPEND2\n");

		ret = smsc75xx_पढ़ो_reg_nopm(dev, PMT_CTL, &val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error reading PMT_CTL\n");
			वापस ret;
		पूर्ण

		val |= PMT_CTL_PHY_PWRUP;

		ret = smsc75xx_ग_लिखो_reg_nopm(dev, PMT_CTL, val);
		अगर (ret < 0) अणु
			netdev_warn(dev->net, "Error writing PMT_CTL\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = smsc75xx_रुको_पढ़ोy(dev, 1);
	अगर (ret < 0) अणु
		netdev_warn(dev->net, "device not ready in smsc75xx_resume\n");
		वापस ret;
	पूर्ण

	वापस usbnet_resume(पूर्णांकf);
पूर्ण

अटल व्योम smsc75xx_rx_csum_offload(काष्ठा usbnet *dev, काष्ठा sk_buff *skb,
				     u32 rx_cmd_a, u32 rx_cmd_b)
अणु
	अगर (!(dev->net->features & NETIF_F_RXCSUM) ||
	    unlikely(rx_cmd_a & RX_CMD_A_LCSM)) अणु
		skb->ip_summed = CHECKSUM_NONE;
	पूर्ण अन्यथा अणु
		skb->csum = ntohs((u16)(rx_cmd_b >> RX_CMD_B_CSUM_SHIFT));
		skb->ip_summed = CHECKSUM_COMPLETE;
	पूर्ण
पूर्ण

अटल पूर्णांक smsc75xx_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	/* This check is no दीर्घer करोne by usbnet */
	अगर (skb->len < dev->net->hard_header_len)
		वापस 0;

	जबतक (skb->len > 0) अणु
		u32 rx_cmd_a, rx_cmd_b, align_count, size;
		काष्ठा sk_buff *ax_skb;
		अचिन्हित अक्षर *packet;

		rx_cmd_a = get_unaligned_le32(skb->data);
		skb_pull(skb, 4);

		rx_cmd_b = get_unaligned_le32(skb->data);
		skb_pull(skb, 4 + RXW_PADDING);

		packet = skb->data;

		/* get the packet length */
		size = (rx_cmd_a & RX_CMD_A_LEN) - RXW_PADDING;
		align_count = (4 - ((size + RXW_PADDING) % 4)) % 4;

		अगर (unlikely(rx_cmd_a & RX_CMD_A_RED)) अणु
			netअगर_dbg(dev, rx_err, dev->net,
				  "Error rx_cmd_a=0x%08x\n", rx_cmd_a);
			dev->net->stats.rx_errors++;
			dev->net->stats.rx_dropped++;

			अगर (rx_cmd_a & RX_CMD_A_FCS)
				dev->net->stats.rx_crc_errors++;
			अन्यथा अगर (rx_cmd_a & (RX_CMD_A_LONG | RX_CMD_A_RUNT))
				dev->net->stats.rx_frame_errors++;
		पूर्ण अन्यथा अणु
			/* MAX_SINGLE_PACKET_SIZE + 4(CRC) + 2(COE) + 4(Vlan) */
			अगर (unlikely(size > (MAX_SINGLE_PACKET_SIZE + ETH_HLEN + 12))) अणु
				netअगर_dbg(dev, rx_err, dev->net,
					  "size err rx_cmd_a=0x%08x\n",
					  rx_cmd_a);
				वापस 0;
			पूर्ण

			/* last frame in this batch */
			अगर (skb->len == size) अणु
				smsc75xx_rx_csum_offload(dev, skb, rx_cmd_a,
					rx_cmd_b);

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

			smsc75xx_rx_csum_offload(dev, ax_skb, rx_cmd_a,
				rx_cmd_b);

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

अटल काष्ठा sk_buff *smsc75xx_tx_fixup(काष्ठा usbnet *dev,
					 काष्ठा sk_buff *skb, gfp_t flags)
अणु
	u32 tx_cmd_a, tx_cmd_b;
	व्योम *ptr;

	अगर (skb_cow_head(skb, SMSC75XX_TX_OVERHEAD)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण

	tx_cmd_a = (u32)(skb->len & TX_CMD_A_LEN) | TX_CMD_A_FCS;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		tx_cmd_a |= TX_CMD_A_IPE | TX_CMD_A_TPE;

	अगर (skb_is_gso(skb)) अणु
		u16 mss = max(skb_shinfo(skb)->gso_size, TX_MSS_MIN);
		tx_cmd_b = (mss << TX_CMD_B_MSS_SHIFT) & TX_CMD_B_MSS;

		tx_cmd_a |= TX_CMD_A_LSO;
	पूर्ण अन्यथा अणु
		tx_cmd_b = 0;
	पूर्ण

	ptr = skb_push(skb, 8);
	put_unaligned_le32(tx_cmd_a, ptr);
	put_unaligned_le32(tx_cmd_b, ptr + 4);

	वापस skb;
पूर्ण

अटल पूर्णांक smsc75xx_manage_घातer(काष्ठा usbnet *dev, पूर्णांक on)
अणु
	dev->पूर्णांकf->needs_remote_wakeup = on;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा driver_info smsc75xx_info = अणु
	.description	= "smsc75xx USB 2.0 Gigabit Ethernet",
	.bind		= smsc75xx_bind,
	.unbind		= smsc75xx_unbind,
	.link_reset	= smsc75xx_link_reset,
	.reset		= smsc75xx_reset,
	.rx_fixup	= smsc75xx_rx_fixup,
	.tx_fixup	= smsc75xx_tx_fixup,
	.status		= smsc75xx_status,
	.manage_घातer	= smsc75xx_manage_घातer,
	.flags		= FLAG_ETHER | FLAG_SEND_ZLP | FLAG_LINK_INTR,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id products[] = अणु
	अणु
		/* SMSC7500 USB Gigabit Ethernet Device */
		USB_DEVICE(USB_VENDOR_ID_SMSC, USB_PRODUCT_ID_LAN7500),
		.driver_info = (अचिन्हित दीर्घ) &smsc75xx_info,
	पूर्ण,
	अणु
		/* SMSC7500 USB Gigabit Ethernet Device */
		USB_DEVICE(USB_VENDOR_ID_SMSC, USB_PRODUCT_ID_LAN7505),
		.driver_info = (अचिन्हित दीर्घ) &smsc75xx_info,
	पूर्ण,
	अणु पूर्ण,		/* END */
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver smsc75xx_driver = अणु
	.name		= SMSC_CHIPNAME,
	.id_table	= products,
	.probe		= usbnet_probe,
	.suspend	= smsc75xx_suspend,
	.resume		= smsc75xx_resume,
	.reset_resume	= smsc75xx_resume,
	.disconnect	= usbnet_disconnect,
	.disable_hub_initiated_lpm = 1,
	.supports_स्वतःsuspend = 1,
पूर्ण;

module_usb_driver(smsc75xx_driver);

MODULE_AUTHOR("Nancy Lin");
MODULE_AUTHOR("Steve Glendinning <steve.glendinning@shawell.net>");
MODULE_DESCRIPTION("SMSC75XX USB 2.0 Gigabit Ethernet Devices");
MODULE_LICENSE("GPL");
