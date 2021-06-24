<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MOSCHIP MCS7830 based (7730/7830/7832) USB 2.0 Ethernet Devices
 *
 * based on usbnet.c, asix.c and the venकरोr provided mcs7830 driver
 *
 * Copyright (C) 2010 Andreas Mohr <andi@lisas.de>
 * Copyright (C) 2006 Arnd Bergmann <arnd@arndb.de>
 * Copyright (C) 2003-2005 David Hollis <dhollis@davehollis.com>
 * Copyright (C) 2005 Phil Chang <pchang23@sbcglobal.net>
 * Copyright (c) 2002-2003 TiVo Inc.
 *
 * Definitions gathered from MOSCHIP, Data Sheet_7830DA.pdf (thanks!).
 *
 * 2010-12-19: add 7832 USB PID ("functionality same as MCS7830"),
 *             per active notअगरication by manufacturer
 *
 * TODO:
 * - support HIF_REG_CONFIG_SLEEPMODE/HIF_REG_CONFIG_TXENABLE (via स्वतःpm?)
 * - implement ethtool_ops get_छोड़ोparam/set_छोड़ोparam
 *   via HIF_REG_PAUSE_THRESHOLD (>= revision C only!)
 * - implement get_eeprom/[set_eeprom]
 * - चयन PHY on/off on अगरup/अगरकरोwn (perhaps in usbnet.c, via MII)
 * - mcs7830_get_regs() handling is weird: क्रम rev 2 we वापस 32 regs,
 *   can access only ~ 24, reमुख्यing user buffer is uninitialized garbage
 * - anything अन्यथा?
 */

#समावेश <linux/crc32.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/usbnet.h>

/* requests */
#घोषणा MCS7830_RD_BMREQ	(USB_सूची_IN  | USB_TYPE_VENDOR | \
				 USB_RECIP_DEVICE)
#घोषणा MCS7830_WR_BMREQ	(USB_सूची_OUT | USB_TYPE_VENDOR | \
				 USB_RECIP_DEVICE)
#घोषणा MCS7830_RD_BREQ		0x0E
#घोषणा MCS7830_WR_BREQ		0x0D

#घोषणा MCS7830_CTRL_TIMEOUT	1000
#घोषणा MCS7830_MAX_MCAST	64

#घोषणा MCS7830_VENDOR_ID	0x9710
#घोषणा MCS7832_PRODUCT_ID	0x7832
#घोषणा MCS7830_PRODUCT_ID	0x7830
#घोषणा MCS7730_PRODUCT_ID	0x7730

#घोषणा SITECOM_VENDOR_ID	0x0DF6
#घोषणा LN_030_PRODUCT_ID	0x0021

#घोषणा MCS7830_MII_ADVERTISE	(ADVERTISE_PAUSE_CAP | ADVERTISE_100FULL | \
				 ADVERTISE_100HALF | ADVERTISE_10FULL | \
				 ADVERTISE_10HALF | ADVERTISE_CSMA)

/* HIF_REG_XX corresponding index value */
क्रमागत अणु
	HIF_REG_MULTICAST_HASH			= 0x00,
	HIF_REG_PACKET_GAP1			= 0x08,
	HIF_REG_PACKET_GAP2			= 0x09,
	HIF_REG_PHY_DATA			= 0x0a,
	HIF_REG_PHY_CMD1			= 0x0c,
	   HIF_REG_PHY_CMD1_READ		= 0x40,
	   HIF_REG_PHY_CMD1_WRITE		= 0x20,
	   HIF_REG_PHY_CMD1_PHYADDR		= 0x01,
	HIF_REG_PHY_CMD2			= 0x0d,
	   HIF_REG_PHY_CMD2_PEND_FLAG_BIT	= 0x80,
	   HIF_REG_PHY_CMD2_READY_FLAG_BIT	= 0x40,
	HIF_REG_CONFIG				= 0x0e,
	/* hmm, spec sez: "R/W", "Except bit 3" (likely TXENABLE). */
	   HIF_REG_CONFIG_CFG			= 0x80,
	   HIF_REG_CONFIG_SPEED100		= 0x40,
	   HIF_REG_CONFIG_FULLDUPLEX_ENABLE	= 0x20,
	   HIF_REG_CONFIG_RXENABLE		= 0x10,
	   HIF_REG_CONFIG_TXENABLE		= 0x08,
	   HIF_REG_CONFIG_SLEEPMODE		= 0x04,
	   HIF_REG_CONFIG_ALLMULTICAST		= 0x02,
	   HIF_REG_CONFIG_PROMISCUOUS		= 0x01,
	HIF_REG_ETHERNET_ADDR			= 0x0f,
	HIF_REG_FRAME_DROP_COUNTER		= 0x15, /* 0..ff; reset: 0 */
	HIF_REG_PAUSE_THRESHOLD			= 0x16,
	   HIF_REG_PAUSE_THRESHOLD_DEFAULT	= 0,
पूर्ण;

/* Trailing status byte in Ethernet Rx frame */
क्रमागत अणु
	MCS7830_RX_SHORT_FRAME		= 0x01, /* < 64 bytes */
	MCS7830_RX_LENGTH_ERROR		= 0x02, /* framelen != Ethernet length field */
	MCS7830_RX_ALIGNMENT_ERROR	= 0x04, /* non-even number of nibbles */
	MCS7830_RX_CRC_ERROR		= 0x08,
	MCS7830_RX_LARGE_FRAME		= 0x10, /* > 1518 bytes */
	MCS7830_RX_FRAME_CORRECT	= 0x20, /* frame is correct */
	/* [7:6] reserved */
पूर्ण;

काष्ठा mcs7830_data अणु
	u8 multi_filter[8];
	u8 config;
पूर्ण;

अटल स्थिर अक्षर driver_name[] = "MOSCHIP usb-ethernet driver";

अटल पूर्णांक mcs7830_get_reg(काष्ठा usbnet *dev, u16 index, u16 size, व्योम *data)
अणु
	वापस usbnet_पढ़ो_cmd(dev, MCS7830_RD_BREQ, MCS7830_RD_BMREQ,
				0x0000, index, data, size);
पूर्ण

अटल पूर्णांक mcs7830_set_reg(काष्ठा usbnet *dev, u16 index, u16 size, स्थिर व्योम *data)
अणु
	वापस usbnet_ग_लिखो_cmd(dev, MCS7830_WR_BREQ, MCS7830_WR_BMREQ,
				0x0000, index, data, size);
पूर्ण

अटल व्योम mcs7830_set_reg_async(काष्ठा usbnet *dev, u16 index, u16 size, व्योम *data)
अणु
	usbnet_ग_लिखो_cmd_async(dev, MCS7830_WR_BREQ, MCS7830_WR_BMREQ,
				0x0000, index, data, size);
पूर्ण

अटल पूर्णांक mcs7830_hअगर_get_mac_address(काष्ठा usbnet *dev, अचिन्हित अक्षर *addr)
अणु
	पूर्णांक ret = mcs7830_get_reg(dev, HIF_REG_ETHERNET_ADDR, ETH_ALEN, addr);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक mcs7830_hअगर_set_mac_address(काष्ठा usbnet *dev, अचिन्हित अक्षर *addr)
अणु
	पूर्णांक ret = mcs7830_set_reg(dev, HIF_REG_ETHERNET_ADDR, ETH_ALEN, addr);

	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक mcs7830_set_mac_address(काष्ठा net_device *netdev, व्योम *p)
अणु
	पूर्णांक ret;
	काष्ठा usbnet *dev = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;

	अगर (netअगर_running(netdev))
		वापस -EBUSY;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	ret = mcs7830_hअगर_set_mac_address(dev, addr->sa_data);

	अगर (ret < 0)
		वापस ret;

	/* it worked --> aकरोpt it on netdev side */
	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);

	वापस 0;
पूर्ण

अटल पूर्णांक mcs7830_पढ़ो_phy(काष्ठा usbnet *dev, u8 index)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	__le16 val;

	u8 cmd[2] = अणु
		HIF_REG_PHY_CMD1_READ | HIF_REG_PHY_CMD1_PHYADDR,
		HIF_REG_PHY_CMD2_PEND_FLAG_BIT | index,
	पूर्ण;

	mutex_lock(&dev->phy_mutex);
	/* ग_लिखो the MII command */
	ret = mcs7830_set_reg(dev, HIF_REG_PHY_CMD1, 2, cmd);
	अगर (ret < 0)
		जाओ out;

	/* रुको क्रम the data to become valid, should be within < 1ms */
	क्रम (i = 0; i < 10; i++) अणु
		ret = mcs7830_get_reg(dev, HIF_REG_PHY_CMD1, 2, cmd);
		अगर ((ret < 0) || (cmd[1] & HIF_REG_PHY_CMD2_READY_FLAG_BIT))
			अवरोध;
		ret = -EIO;
		msleep(1);
	पूर्ण
	अगर (ret < 0)
		जाओ out;

	/* पढ़ो actual रेजिस्टर contents */
	ret = mcs7830_get_reg(dev, HIF_REG_PHY_DATA, 2, &val);
	अगर (ret < 0)
		जाओ out;
	ret = le16_to_cpu(val);
	dev_dbg(&dev->udev->dev, "read PHY reg %02x: %04x (%d tries)\n",
		index, val, i);
out:
	mutex_unlock(&dev->phy_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक mcs7830_ग_लिखो_phy(काष्ठा usbnet *dev, u8 index, u16 val)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	__le16 le_val;

	u8 cmd[2] = अणु
		HIF_REG_PHY_CMD1_WRITE | HIF_REG_PHY_CMD1_PHYADDR,
		HIF_REG_PHY_CMD2_PEND_FLAG_BIT | (index & 0x1F),
	पूर्ण;

	mutex_lock(&dev->phy_mutex);

	/* ग_लिखो the new रेजिस्टर contents */
	le_val = cpu_to_le16(val);
	ret = mcs7830_set_reg(dev, HIF_REG_PHY_DATA, 2, &le_val);
	अगर (ret < 0)
		जाओ out;

	/* ग_लिखो the MII command */
	ret = mcs7830_set_reg(dev, HIF_REG_PHY_CMD1, 2, cmd);
	अगर (ret < 0)
		जाओ out;

	/* रुको क्रम the command to be accepted by the PHY */
	क्रम (i = 0; i < 10; i++) अणु
		ret = mcs7830_get_reg(dev, HIF_REG_PHY_CMD1, 2, cmd);
		अगर ((ret < 0) || (cmd[1] & HIF_REG_PHY_CMD2_READY_FLAG_BIT))
			अवरोध;
		ret = -EIO;
		msleep(1);
	पूर्ण
	अगर (ret < 0)
		जाओ out;

	ret = 0;
	dev_dbg(&dev->udev->dev, "write PHY reg %02x: %04x (%d tries)\n",
		index, val, i);
out:
	mutex_unlock(&dev->phy_mutex);
	वापस ret;
पूर्ण

/*
 * This algorithm comes from the original mcs7830 version 1.4 driver,
 * not sure अगर it is needed.
 */
अटल पूर्णांक mcs7830_set_स्वतःneg(काष्ठा usbnet *dev, पूर्णांक ptrUserPhyMode)
अणु
	पूर्णांक ret;
	/* Enable all media types */
	ret = mcs7830_ग_लिखो_phy(dev, MII_ADVERTISE, MCS7830_MII_ADVERTISE);

	/* First reset BMCR */
	अगर (!ret)
		ret = mcs7830_ग_लिखो_phy(dev, MII_BMCR, 0x0000);
	/* Enable Auto Neg */
	अगर (!ret)
		ret = mcs7830_ग_लिखो_phy(dev, MII_BMCR, BMCR_ANENABLE);
	/* Restart Auto Neg (Keep the Enable Auto Neg Bit Set) */
	अगर (!ret)
		ret = mcs7830_ग_लिखो_phy(dev, MII_BMCR,
				BMCR_ANENABLE | BMCR_ANRESTART	);
	वापस ret;
पूर्ण


/*
 * अगर we can पढ़ो रेजिस्टर 22, the chip revision is C or higher
 */
अटल पूर्णांक mcs7830_get_rev(काष्ठा usbnet *dev)
अणु
	u8 dummy[2];
	पूर्णांक ret;
	ret = mcs7830_get_reg(dev, HIF_REG_FRAME_DROP_COUNTER, 2, dummy);
	अगर (ret > 0)
		वापस 2; /* Rev C or later */
	वापस 1; /* earlier revision */
पूर्ण

/*
 * On rev. C we need to set the छोड़ो threshold
 */
अटल व्योम mcs7830_rev_C_fixup(काष्ठा usbnet *dev)
अणु
	u8 छोड़ो_threshold = HIF_REG_PAUSE_THRESHOLD_DEFAULT;
	पूर्णांक retry;

	क्रम (retry = 0; retry < 2; retry++) अणु
		अगर (mcs7830_get_rev(dev) == 2) अणु
			dev_info(&dev->udev->dev, "applying rev.C fixup\n");
			mcs7830_set_reg(dev, HIF_REG_PAUSE_THRESHOLD,
					1, &छोड़ो_threshold);
		पूर्ण
		msleep(1);
	पूर्ण
पूर्ण

अटल पूर्णांक mcs7830_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id,
			     पूर्णांक location)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	वापस mcs7830_पढ़ो_phy(dev, location);
पूर्ण

अटल व्योम mcs7830_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक phy_id,
				पूर्णांक location, पूर्णांक val)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	mcs7830_ग_लिखो_phy(dev, location, val);
पूर्ण

अटल पूर्णांक mcs7830_ioctl(काष्ठा net_device *net, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	वापस generic_mii_ioctl(&dev->mii, अगर_mii(rq), cmd, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा mcs7830_data *mcs7830_get_data(काष्ठा usbnet *dev)
अणु
	वापस (काष्ठा mcs7830_data *)&dev->data;
पूर्ण

अटल व्योम mcs7830_hअगर_update_multicast_hash(काष्ठा usbnet *dev)
अणु
	काष्ठा mcs7830_data *data = mcs7830_get_data(dev);
	mcs7830_set_reg_async(dev, HIF_REG_MULTICAST_HASH,
				माप data->multi_filter,
				data->multi_filter);
पूर्ण

अटल व्योम mcs7830_hअगर_update_config(काष्ठा usbnet *dev)
अणु
	/* implementation specअगरic to data->config
           (argument needs to be heap-based anyway - USB DMA!) */
	काष्ठा mcs7830_data *data = mcs7830_get_data(dev);
	mcs7830_set_reg_async(dev, HIF_REG_CONFIG, 1, &data->config);
पूर्ण

अटल व्योम mcs7830_data_set_multicast(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा mcs7830_data *data = mcs7830_get_data(dev);

	स_रखो(data->multi_filter, 0, माप data->multi_filter);

	data->config = HIF_REG_CONFIG_TXENABLE;

	/* this should not be needed, but it करोesn't work otherwise */
	data->config |= HIF_REG_CONFIG_ALLMULTICAST;

	अगर (net->flags & IFF_PROMISC) अणु
		data->config |= HIF_REG_CONFIG_PROMISCUOUS;
	पूर्ण अन्यथा अगर (net->flags & IFF_ALLMULTI ||
		   netdev_mc_count(net) > MCS7830_MAX_MCAST) अणु
		data->config |= HIF_REG_CONFIG_ALLMULTICAST;
	पूर्ण अन्यथा अगर (netdev_mc_empty(net)) अणु
		/* just broadcast and directed */
	पूर्ण अन्यथा अणु
		/* We use the 20 byte dev->data
		 * क्रम our 8 byte filter buffer
		 * to aव्योम allocating memory that
		 * is tricky to मुक्त later */
		काष्ठा netdev_hw_addr *ha;
		u32 crc_bits;

		/* Build the multicast hash filter. */
		netdev_क्रम_each_mc_addr(ha, net) अणु
			crc_bits = ether_crc(ETH_ALEN, ha->addr) >> 26;
			data->multi_filter[crc_bits >> 3] |= 1 << (crc_bits & 7);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mcs7830_apply_base_config(काष्ठा usbnet *dev)
अणु
	पूर्णांक ret;

	/* re-configure known MAC (suspend हाल etc.) */
	ret = mcs7830_hअगर_set_mac_address(dev, dev->net->dev_addr);
	अगर (ret) अणु
		dev_info(&dev->udev->dev, "Cannot set MAC address\n");
		जाओ out;
	पूर्ण

	/* Set up PHY */
	ret = mcs7830_set_स्वतःneg(dev, 0);
	अगर (ret) अणु
		dev_info(&dev->udev->dev, "Cannot set autoneg\n");
		जाओ out;
	पूर्ण

	mcs7830_hअगर_update_multicast_hash(dev);
	mcs7830_hअगर_update_config(dev);

	mcs7830_rev_C_fixup(dev);
	ret = 0;
out:
	वापस ret;
पूर्ण

/* credits go to asix_set_multicast */
अटल व्योम mcs7830_set_multicast(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	mcs7830_data_set_multicast(net);

	mcs7830_hअगर_update_multicast_hash(dev);
	mcs7830_hअगर_update_config(dev);
पूर्ण

अटल पूर्णांक mcs7830_get_regs_len(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	चयन (mcs7830_get_rev(dev)) अणु
	हाल 1:
		वापस 21;
	हाल 2:
		वापस 32;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mcs7830_get_drvinfo(काष्ठा net_device *net, काष्ठा ethtool_drvinfo *drvinfo)
अणु
	usbnet_get_drvinfo(net, drvinfo);
पूर्ण

अटल व्योम mcs7830_get_regs(काष्ठा net_device *net, काष्ठा ethtool_regs *regs, व्योम *data)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	regs->version = mcs7830_get_rev(dev);
	mcs7830_get_reg(dev, 0, regs->len, data);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops mcs7830_ethtool_ops = अणु
	.get_drvinfo		= mcs7830_get_drvinfo,
	.get_regs_len		= mcs7830_get_regs_len,
	.get_regs		= mcs7830_get_regs,

	/* common usbnet calls */
	.get_link		= usbnet_get_link,
	.get_msglevel		= usbnet_get_msglevel,
	.set_msglevel		= usbnet_set_msglevel,
	.nway_reset		= usbnet_nway_reset,
	.get_link_ksettings	= usbnet_get_link_ksettings_mii,
	.set_link_ksettings	= usbnet_set_link_ksettings_mii,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops mcs7830_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_change_mtu		= usbnet_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl 		= mcs7830_ioctl,
	.nकरो_set_rx_mode	= mcs7830_set_multicast,
	.nकरो_set_mac_address	= mcs7830_set_mac_address,
पूर्ण;

अटल पूर्णांक mcs7830_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *udev)
अणु
	काष्ठा net_device *net = dev->net;
	पूर्णांक ret;
	पूर्णांक retry;

	/* Initial startup: Gather MAC address setting from EEPROM */
	ret = -EINVAL;
	क्रम (retry = 0; retry < 5 && ret; retry++)
		ret = mcs7830_hअगर_get_mac_address(dev, net->dev_addr);
	अगर (ret) अणु
		dev_warn(&dev->udev->dev, "Cannot read MAC address\n");
		जाओ out;
	पूर्ण

	mcs7830_data_set_multicast(net);

	ret = mcs7830_apply_base_config(dev);
	अगर (ret)
		जाओ out;

	net->ethtool_ops = &mcs7830_ethtool_ops;
	net->netdev_ops = &mcs7830_netdev_ops;

	/* reserve space क्रम the status byte on rx */
	dev->rx_urb_size = ETH_FRAME_LEN + 1;

	dev->mii.mdio_पढ़ो = mcs7830_mdio_पढ़ो;
	dev->mii.mdio_ग_लिखो = mcs7830_mdio_ग_लिखो;
	dev->mii.dev = net;
	dev->mii.phy_id_mask = 0x3f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.phy_id = *((u8 *) net->dev_addr + 1);

	ret = usbnet_get_endpoपूर्णांकs(dev, udev);
out:
	वापस ret;
पूर्ण

/* The chip always appends a status byte that we need to strip */
अटल पूर्णांक mcs7830_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	u8 status;

	/* This check is no दीर्घer करोne by usbnet */
	अगर (skb->len < dev->net->hard_header_len) अणु
		dev_err(&dev->udev->dev, "unexpected tiny rx frame\n");
		वापस 0;
	पूर्ण

	skb_trim(skb, skb->len - 1);
	status = skb->data[skb->len];

	अगर (status != MCS7830_RX_FRAME_CORRECT) अणु
		dev_dbg(&dev->udev->dev, "rx fixup status %x\n", status);

		/* hmm, perhaps usbnet.c alपढ़ोy sees a globally visible
		   frame error and increments rx_errors on its own alपढ़ोy? */
		dev->net->stats.rx_errors++;

		अगर (status &	(MCS7830_RX_SHORT_FRAME
				|MCS7830_RX_LENGTH_ERROR
				|MCS7830_RX_LARGE_FRAME))
			dev->net->stats.rx_length_errors++;
		अगर (status & MCS7830_RX_ALIGNMENT_ERROR)
			dev->net->stats.rx_frame_errors++;
		अगर (status & MCS7830_RX_CRC_ERROR)
			dev->net->stats.rx_crc_errors++;
	पूर्ण

	वापस skb->len > 0;
पूर्ण

अटल व्योम mcs7830_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	u8 *buf = urb->transfer_buffer;
	bool link, link_changed;

	अगर (urb->actual_length < 16)
		वापस;

	link = !(buf[1] == 0x20);
	link_changed = netअगर_carrier_ok(dev->net) != link;
	अगर (link_changed) अणु
		usbnet_link_change(dev, link, 0);
		netdev_dbg(dev->net, "Link Status is: %d\n", link);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा driver_info moschip_info = अणु
	.description	= "MOSCHIP 7830/7832/7730 usb-NET adapter",
	.bind		= mcs7830_bind,
	.rx_fixup	= mcs7830_rx_fixup,
	.flags		= FLAG_ETHER | FLAG_LINK_INTR,
	.status		= mcs7830_status,
	.in		= 1,
	.out		= 2,
पूर्ण;

अटल स्थिर काष्ठा driver_info sitecom_info = अणु
	.description    = "Sitecom LN-30 usb-NET adapter",
	.bind		= mcs7830_bind,
	.rx_fixup	= mcs7830_rx_fixup,
	.flags		= FLAG_ETHER | FLAG_LINK_INTR,
	.status		= mcs7830_status,
	.in		= 1,
	.out		= 2,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id products[] = अणु
	अणु
		USB_DEVICE(MCS7830_VENDOR_ID, MCS7832_PRODUCT_ID),
		.driver_info = (अचिन्हित दीर्घ) &moschip_info,
	पूर्ण,
	अणु
		USB_DEVICE(MCS7830_VENDOR_ID, MCS7830_PRODUCT_ID),
		.driver_info = (अचिन्हित दीर्घ) &moschip_info,
	पूर्ण,
	अणु
		USB_DEVICE(MCS7830_VENDOR_ID, MCS7730_PRODUCT_ID),
		.driver_info = (अचिन्हित दीर्घ) &moschip_info,
	पूर्ण,
	अणु
		USB_DEVICE(SITECOM_VENDOR_ID, LN_030_PRODUCT_ID),
		.driver_info = (अचिन्हित दीर्घ) &sitecom_info,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल पूर्णांक mcs7830_reset_resume (काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
 	/* YES, this function is successful enough that ethtool -d
           करोes show same output pre-/post-suspend */

	काष्ठा usbnet		*dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	mcs7830_apply_base_config(dev);

	usbnet_resume(पूर्णांकf);

	वापस 0;
पूर्ण

अटल काष्ठा usb_driver mcs7830_driver = अणु
	.name = driver_name,
	.id_table = products,
	.probe = usbnet_probe,
	.disconnect = usbnet_disconnect,
	.suspend = usbnet_suspend,
	.resume = usbnet_resume,
	.reset_resume = mcs7830_reset_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(mcs7830_driver);

MODULE_DESCRIPTION("USB to network adapter MCS7830)");
MODULE_LICENSE("GPL");
