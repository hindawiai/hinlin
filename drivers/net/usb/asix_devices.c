<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ASIX AX8817X based USB 2.0 Ethernet Devices
 * Copyright (C) 2003-2006 David Hollis <dhollis@davehollis.com>
 * Copyright (C) 2005 Phil Chang <pchang23@sbcglobal.net>
 * Copyright (C) 2006 James Paपूर्णांकer <jamie.paपूर्णांकer@iname.com>
 * Copyright (c) 2002-2003 TiVo Inc.
 */

#समावेश "asix.h"

#घोषणा PHY_MODE_MARVELL	0x0000
#घोषणा MII_MARVELL_LED_CTRL	0x0018
#घोषणा MII_MARVELL_STATUS	0x001b
#घोषणा MII_MARVELL_CTRL	0x0014

#घोषणा MARVELL_LED_MANUAL	0x0019

#घोषणा MARVELL_STATUS_HWCFG	0x0004

#घोषणा MARVELL_CTRL_TXDELAY	0x0002
#घोषणा MARVELL_CTRL_RXDELAY	0x0080

#घोषणा	PHY_MODE_RTL8211CL	0x000C

#घोषणा AX88772A_PHY14H		0x14
#घोषणा AX88772A_PHY14H_DEFAULT 0x442C

#घोषणा AX88772A_PHY15H		0x15
#घोषणा AX88772A_PHY15H_DEFAULT 0x03C8

#घोषणा AX88772A_PHY16H		0x16
#घोषणा AX88772A_PHY16H_DEFAULT 0x4044

काष्ठा ax88172_पूर्णांक_data अणु
	__le16 res1;
	u8 link;
	__le16 res2;
	u8 status;
	__le16 res3;
पूर्ण __packed;

अटल व्योम asix_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	काष्ठा ax88172_पूर्णांक_data *event;
	पूर्णांक link;

	अगर (urb->actual_length < 8)
		वापस;

	event = urb->transfer_buffer;
	link = event->link & 0x01;
	अगर (netअगर_carrier_ok(dev->net) != link) अणु
		usbnet_link_change(dev, link, 1);
		netdev_dbg(dev->net, "Link Status is: %d\n", link);
	पूर्ण
पूर्ण

अटल व्योम asix_set_netdev_dev_addr(काष्ठा usbnet *dev, u8 *addr)
अणु
	अगर (is_valid_ether_addr(addr)) अणु
		स_नकल(dev->net->dev_addr, addr, ETH_ALEN);
	पूर्ण अन्यथा अणु
		netdev_info(dev->net, "invalid hw address, using random\n");
		eth_hw_addr_अक्रमom(dev->net);
	पूर्ण
पूर्ण

/* Get the PHY Identअगरier from the PHYSID1 & PHYSID2 MII रेजिस्टरs */
अटल u32 asix_get_phyid(काष्ठा usbnet *dev)
अणु
	पूर्णांक phy_reg;
	u32 phy_id;
	पूर्णांक i;

	/* Poll क्रम the rare हाल the FW or phy isn't पढ़ोy yet.  */
	क्रम (i = 0; i < 100; i++) अणु
		phy_reg = asix_mdio_पढ़ो(dev->net, dev->mii.phy_id, MII_PHYSID1);
		अगर (phy_reg < 0)
			वापस 0;
		अगर (phy_reg != 0 && phy_reg != 0xFFFF)
			अवरोध;
		mdelay(1);
	पूर्ण

	अगर (phy_reg <= 0 || phy_reg == 0xFFFF)
		वापस 0;

	phy_id = (phy_reg & 0xffff) << 16;

	phy_reg = asix_mdio_पढ़ो(dev->net, dev->mii.phy_id, MII_PHYSID2);
	अगर (phy_reg < 0)
		वापस 0;

	phy_id |= (phy_reg & 0xffff);

	वापस phy_id;
पूर्ण

अटल u32 asix_get_link(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	वापस mii_link_ok(&dev->mii);
पूर्ण

अटल पूर्णांक asix_ioctl (काष्ठा net_device *net, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	वापस generic_mii_ioctl(&dev->mii, अगर_mii(rq), cmd, शून्य);
पूर्ण

/* We need to override some ethtool_ops so we require our
   own काष्ठाure so we करोn't पूर्णांकerfere with other usbnet
   devices that may be connected at the same समय. */
अटल स्थिर काष्ठा ethtool_ops ax88172_ethtool_ops = अणु
	.get_drvinfo		= asix_get_drvinfo,
	.get_link		= asix_get_link,
	.get_msglevel		= usbnet_get_msglevel,
	.set_msglevel		= usbnet_set_msglevel,
	.get_wol		= asix_get_wol,
	.set_wol		= asix_set_wol,
	.get_eeprom_len		= asix_get_eeprom_len,
	.get_eeprom		= asix_get_eeprom,
	.set_eeprom		= asix_set_eeprom,
	.nway_reset		= usbnet_nway_reset,
	.get_link_ksettings	= usbnet_get_link_ksettings_mii,
	.set_link_ksettings	= usbnet_set_link_ksettings_mii,
पूर्ण;

अटल व्योम ax88172_set_multicast(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा asix_data *data = (काष्ठा asix_data *)&dev->data;
	u8 rx_ctl = 0x8c;

	अगर (net->flags & IFF_PROMISC) अणु
		rx_ctl |= 0x01;
	पूर्ण अन्यथा अगर (net->flags & IFF_ALLMULTI ||
		   netdev_mc_count(net) > AX_MAX_MCAST) अणु
		rx_ctl |= 0x02;
	पूर्ण अन्यथा अगर (netdev_mc_empty(net)) अणु
		/* just broadcast and directed */
	पूर्ण अन्यथा अणु
		/* We use the 20 byte dev->data
		 * क्रम our 8 byte filter buffer
		 * to aव्योम allocating memory that
		 * is tricky to मुक्त later */
		काष्ठा netdev_hw_addr *ha;
		u32 crc_bits;

		स_रखो(data->multi_filter, 0, AX_MCAST_FILTER_SIZE);

		/* Build the multicast hash filter. */
		netdev_क्रम_each_mc_addr(ha, net) अणु
			crc_bits = ether_crc(ETH_ALEN, ha->addr) >> 26;
			data->multi_filter[crc_bits >> 3] |=
			    1 << (crc_bits & 7);
		पूर्ण

		asix_ग_लिखो_cmd_async(dev, AX_CMD_WRITE_MULTI_FILTER, 0, 0,
				   AX_MCAST_FILTER_SIZE, data->multi_filter);

		rx_ctl |= 0x10;
	पूर्ण

	asix_ग_लिखो_cmd_async(dev, AX_CMD_WRITE_RX_CTL, rx_ctl, 0, 0, शून्य);
पूर्ण

अटल पूर्णांक ax88172_link_reset(काष्ठा usbnet *dev)
अणु
	u8 mode;
	काष्ठा ethtool_cmd ecmd = अणु .cmd = ETHTOOL_GSET पूर्ण;

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);
	mode = AX88172_MEDIUM_DEFAULT;

	अगर (ecmd.duplex != DUPLEX_FULL)
		mode |= ~AX88172_MEDIUM_FD;

	netdev_dbg(dev->net, "ax88172_link_reset() speed: %u duplex: %d setting mode to 0x%04x\n",
		   ethtool_cmd_speed(&ecmd), ecmd.duplex, mode);

	asix_ग_लिखो_medium_mode(dev, mode, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ax88172_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_change_mtu		= usbnet_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= asix_ioctl,
	.nकरो_set_rx_mode	= ax88172_set_multicast,
पूर्ण;

अटल व्योम asix_phy_reset(काष्ठा usbnet *dev, अचिन्हित पूर्णांक reset_bits)
अणु
	अचिन्हित पूर्णांक समयout = 5000;

	asix_mdio_ग_लिखो(dev->net, dev->mii.phy_id, MII_BMCR, reset_bits);

	/* give phy_id a chance to process reset */
	udelay(500);

	/* See IEEE 802.3 "22.2.4.1.1 Reset": 500ms max */
	जबतक (समयout--) अणु
		अगर (asix_mdio_पढ़ो(dev->net, dev->mii.phy_id, MII_BMCR)
							& BMCR_RESET)
			udelay(100);
		अन्यथा
			वापस;
	पूर्ण

	netdev_err(dev->net, "BMCR_RESET timeout on phy_id %d\n",
		   dev->mii.phy_id);
पूर्ण

अटल पूर्णांक ax88172_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret = 0;
	u8 buf[ETH_ALEN] = अणु0पूर्ण;
	पूर्णांक i;
	अचिन्हित दीर्घ gpio_bits = dev->driver_info->data;

	usbnet_get_endpoपूर्णांकs(dev,पूर्णांकf);

	/* Toggle the GPIOs in a manufacturer/model specअगरic way */
	क्रम (i = 2; i >= 0; i--) अणु
		ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_GPIOS,
				(gpio_bits >> (i * 8)) & 0xff, 0, 0, शून्य, 0);
		अगर (ret < 0)
			जाओ out;
		msleep(5);
	पूर्ण

	ret = asix_ग_लिखो_rx_ctl(dev, 0x80, 0);
	अगर (ret < 0)
		जाओ out;

	/* Get the MAC address */
	ret = asix_पढ़ो_cmd(dev, AX88172_CMD_READ_NODE_ID,
			    0, 0, ETH_ALEN, buf, 0);
	अगर (ret < 0) अणु
		netdev_dbg(dev->net, "read AX_CMD_READ_NODE_ID failed: %d\n",
			   ret);
		जाओ out;
	पूर्ण

	asix_set_netdev_dev_addr(dev, buf);

	/* Initialize MII काष्ठाure */
	dev->mii.dev = dev->net;
	dev->mii.mdio_पढ़ो = asix_mdio_पढ़ो;
	dev->mii.mdio_ग_लिखो = asix_mdio_ग_लिखो;
	dev->mii.phy_id_mask = 0x3f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.phy_id = asix_get_phy_addr(dev);

	dev->net->netdev_ops = &ax88172_netdev_ops;
	dev->net->ethtool_ops = &ax88172_ethtool_ops;
	dev->net->needed_headroom = 4; /* cf asix_tx_fixup() */
	dev->net->needed_tailroom = 4; /* cf asix_tx_fixup() */

	asix_phy_reset(dev, BMCR_RESET);
	asix_mdio_ग_लिखो(dev->net, dev->mii.phy_id, MII_ADVERTISE,
		ADVERTISE_ALL | ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP);
	mii_nway_restart(&dev->mii);

	वापस 0;

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ax88772_ethtool_ops = अणु
	.get_drvinfo		= asix_get_drvinfo,
	.get_link		= asix_get_link,
	.get_msglevel		= usbnet_get_msglevel,
	.set_msglevel		= usbnet_set_msglevel,
	.get_wol		= asix_get_wol,
	.set_wol		= asix_set_wol,
	.get_eeprom_len		= asix_get_eeprom_len,
	.get_eeprom		= asix_get_eeprom,
	.set_eeprom		= asix_set_eeprom,
	.nway_reset		= usbnet_nway_reset,
	.get_link_ksettings	= usbnet_get_link_ksettings_mii,
	.set_link_ksettings	= usbnet_set_link_ksettings_mii,
पूर्ण;

अटल पूर्णांक ax88772_link_reset(काष्ठा usbnet *dev)
अणु
	u16 mode;
	काष्ठा ethtool_cmd ecmd = अणु .cmd = ETHTOOL_GSET पूर्ण;

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);
	mode = AX88772_MEDIUM_DEFAULT;

	अगर (ethtool_cmd_speed(&ecmd) != SPEED_100)
		mode &= ~AX_MEDIUM_PS;

	अगर (ecmd.duplex != DUPLEX_FULL)
		mode &= ~AX_MEDIUM_FD;

	netdev_dbg(dev->net, "ax88772_link_reset() speed: %u duplex: %d setting mode to 0x%04x\n",
		   ethtool_cmd_speed(&ecmd), ecmd.duplex, mode);

	asix_ग_लिखो_medium_mode(dev, mode, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ax88772_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा asix_data *data = (काष्ठा asix_data *)&dev->data;
	पूर्णांक ret;

	/* Reग_लिखो MAC address */
	ether_addr_copy(data->mac_addr, dev->net->dev_addr);
	ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_NODE_ID, 0, 0,
			     ETH_ALEN, data->mac_addr, 0);
	अगर (ret < 0)
		जाओ out;

	/* Set RX_CTL to शेष values with 2k buffer, and enable cactus */
	ret = asix_ग_लिखो_rx_ctl(dev, AX_DEFAULT_RX_CTL, 0);
	अगर (ret < 0)
		जाओ out;

	ret = asix_ग_लिखो_medium_mode(dev, AX88772_MEDIUM_DEFAULT, 0);
	अगर (ret < 0)
		जाओ out;

	वापस 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ax88772_hw_reset(काष्ठा usbnet *dev, पूर्णांक in_pm)
अणु
	काष्ठा asix_data *data = (काष्ठा asix_data *)&dev->data;
	पूर्णांक ret, embd_phy;
	u16 rx_ctl;

	ret = asix_ग_लिखो_gpio(dev, AX_GPIO_RSE | AX_GPIO_GPO_2 |
			      AX_GPIO_GPO2EN, 5, in_pm);
	अगर (ret < 0)
		जाओ out;

	embd_phy = ((dev->mii.phy_id & 0x1f) == 0x10 ? 1 : 0);

	ret = asix_ग_लिखो_cmd(dev, AX_CMD_SW_PHY_SELECT, embd_phy,
			     0, 0, शून्य, in_pm);
	अगर (ret < 0) अणु
		netdev_dbg(dev->net, "Select PHY #1 failed: %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (embd_phy) अणु
		ret = asix_sw_reset(dev, AX_SWRESET_IPPD, in_pm);
		अगर (ret < 0)
			जाओ out;

		usleep_range(10000, 11000);

		ret = asix_sw_reset(dev, AX_SWRESET_CLEAR, in_pm);
		अगर (ret < 0)
			जाओ out;

		msleep(60);

		ret = asix_sw_reset(dev, AX_SWRESET_IPRL | AX_SWRESET_PRL,
				    in_pm);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		ret = asix_sw_reset(dev, AX_SWRESET_IPPD | AX_SWRESET_PRL,
				    in_pm);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	msleep(150);

	अगर (in_pm && (!asix_mdio_पढ़ो_nopm(dev->net, dev->mii.phy_id,
					   MII_PHYSID1)))अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	ret = asix_ग_लिखो_rx_ctl(dev, AX_DEFAULT_RX_CTL, in_pm);
	अगर (ret < 0)
		जाओ out;

	ret = asix_ग_लिखो_medium_mode(dev, AX88772_MEDIUM_DEFAULT, in_pm);
	अगर (ret < 0)
		जाओ out;

	ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_IPG0,
			     AX88772_IPG0_DEFAULT | AX88772_IPG1_DEFAULT,
			     AX88772_IPG2_DEFAULT, 0, शून्य, in_pm);
	अगर (ret < 0) अणु
		netdev_dbg(dev->net, "Write IPG,IPG1,IPG2 failed: %d\n", ret);
		जाओ out;
	पूर्ण

	/* Reग_लिखो MAC address */
	ether_addr_copy(data->mac_addr, dev->net->dev_addr);
	ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_NODE_ID, 0, 0,
			     ETH_ALEN, data->mac_addr, in_pm);
	अगर (ret < 0)
		जाओ out;

	/* Set RX_CTL to शेष values with 2k buffer, and enable cactus */
	ret = asix_ग_लिखो_rx_ctl(dev, AX_DEFAULT_RX_CTL, in_pm);
	अगर (ret < 0)
		जाओ out;

	rx_ctl = asix_पढ़ो_rx_ctl(dev, in_pm);
	netdev_dbg(dev->net, "RX_CTL is 0x%04x after all initializations\n",
		   rx_ctl);

	rx_ctl = asix_पढ़ो_medium_status(dev, in_pm);
	netdev_dbg(dev->net,
		   "Medium Status is 0x%04x after all initializations\n",
		   rx_ctl);

	वापस 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ax88772a_hw_reset(काष्ठा usbnet *dev, पूर्णांक in_pm)
अणु
	काष्ठा asix_data *data = (काष्ठा asix_data *)&dev->data;
	पूर्णांक ret, embd_phy;
	u16 rx_ctl, phy14h, phy15h, phy16h;
	u8 chipcode = 0;

	ret = asix_ग_लिखो_gpio(dev, AX_GPIO_RSE, 5, in_pm);
	अगर (ret < 0)
		जाओ out;

	embd_phy = ((dev->mii.phy_id & 0x1f) == 0x10 ? 1 : 0);

	ret = asix_ग_लिखो_cmd(dev, AX_CMD_SW_PHY_SELECT, embd_phy |
			     AX_PHYSEL_SSEN, 0, 0, शून्य, in_pm);
	अगर (ret < 0) अणु
		netdev_dbg(dev->net, "Select PHY #1 failed: %d\n", ret);
		जाओ out;
	पूर्ण
	usleep_range(10000, 11000);

	ret = asix_sw_reset(dev, AX_SWRESET_IPPD | AX_SWRESET_IPRL, in_pm);
	अगर (ret < 0)
		जाओ out;

	usleep_range(10000, 11000);

	ret = asix_sw_reset(dev, AX_SWRESET_IPRL, in_pm);
	अगर (ret < 0)
		जाओ out;

	msleep(160);

	ret = asix_sw_reset(dev, AX_SWRESET_CLEAR, in_pm);
	अगर (ret < 0)
		जाओ out;

	ret = asix_sw_reset(dev, AX_SWRESET_IPRL, in_pm);
	अगर (ret < 0)
		जाओ out;

	msleep(200);

	अगर (in_pm && (!asix_mdio_पढ़ो_nopm(dev->net, dev->mii.phy_id,
					   MII_PHYSID1))) अणु
		ret = -1;
		जाओ out;
	पूर्ण

	ret = asix_पढ़ो_cmd(dev, AX_CMD_STATMNGSTS_REG, 0,
			    0, 1, &chipcode, in_pm);
	अगर (ret < 0)
		जाओ out;

	अगर ((chipcode & AX_CHIPCODE_MASK) == AX_AX88772B_CHIPCODE) अणु
		ret = asix_ग_लिखो_cmd(dev, AX_QCTCTRL, 0x8000, 0x8001,
				     0, शून्य, in_pm);
		अगर (ret < 0) अणु
			netdev_dbg(dev->net, "Write BQ setting failed: %d\n",
				   ret);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर ((chipcode & AX_CHIPCODE_MASK) == AX_AX88772A_CHIPCODE) अणु
		/* Check अगर the PHY रेजिस्टरs have शेष settings */
		phy14h = asix_mdio_पढ़ो_nopm(dev->net, dev->mii.phy_id,
					     AX88772A_PHY14H);
		phy15h = asix_mdio_पढ़ो_nopm(dev->net, dev->mii.phy_id,
					     AX88772A_PHY15H);
		phy16h = asix_mdio_पढ़ो_nopm(dev->net, dev->mii.phy_id,
					     AX88772A_PHY16H);

		netdev_dbg(dev->net,
			   "772a_hw_reset: MR20=0x%x MR21=0x%x MR22=0x%x\n",
			   phy14h, phy15h, phy16h);

		/* Restore PHY रेजिस्टरs शेष setting अगर not */
		अगर (phy14h != AX88772A_PHY14H_DEFAULT)
			asix_mdio_ग_लिखो_nopm(dev->net, dev->mii.phy_id,
					     AX88772A_PHY14H,
					     AX88772A_PHY14H_DEFAULT);
		अगर (phy15h != AX88772A_PHY15H_DEFAULT)
			asix_mdio_ग_लिखो_nopm(dev->net, dev->mii.phy_id,
					     AX88772A_PHY15H,
					     AX88772A_PHY15H_DEFAULT);
		अगर (phy16h != AX88772A_PHY16H_DEFAULT)
			asix_mdio_ग_लिखो_nopm(dev->net, dev->mii.phy_id,
					     AX88772A_PHY16H,
					     AX88772A_PHY16H_DEFAULT);
	पूर्ण

	ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_IPG0,
				AX88772_IPG0_DEFAULT | AX88772_IPG1_DEFAULT,
				AX88772_IPG2_DEFAULT, 0, शून्य, in_pm);
	अगर (ret < 0) अणु
		netdev_dbg(dev->net, "Write IPG,IPG1,IPG2 failed: %d\n", ret);
		जाओ out;
	पूर्ण

	/* Reग_लिखो MAC address */
	स_नकल(data->mac_addr, dev->net->dev_addr, ETH_ALEN);
	ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_NODE_ID, 0, 0, ETH_ALEN,
							data->mac_addr, in_pm);
	अगर (ret < 0)
		जाओ out;

	/* Set RX_CTL to शेष values with 2k buffer, and enable cactus */
	ret = asix_ग_लिखो_rx_ctl(dev, AX_DEFAULT_RX_CTL, in_pm);
	अगर (ret < 0)
		जाओ out;

	ret = asix_ग_लिखो_medium_mode(dev, AX88772_MEDIUM_DEFAULT, in_pm);
	अगर (ret < 0)
		वापस ret;

	/* Set RX_CTL to शेष values with 2k buffer, and enable cactus */
	ret = asix_ग_लिखो_rx_ctl(dev, AX_DEFAULT_RX_CTL, in_pm);
	अगर (ret < 0)
		जाओ out;

	rx_ctl = asix_पढ़ो_rx_ctl(dev, in_pm);
	netdev_dbg(dev->net, "RX_CTL is 0x%04x after all initializations\n",
		   rx_ctl);

	rx_ctl = asix_पढ़ो_medium_status(dev, in_pm);
	netdev_dbg(dev->net,
		   "Medium Status is 0x%04x after all initializations\n",
		   rx_ctl);

	वापस 0;

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ax88772_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_change_mtu		= usbnet_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_set_mac_address 	= asix_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= asix_ioctl,
	.nकरो_set_rx_mode        = asix_set_multicast,
पूर्ण;

अटल व्योम ax88772_suspend(काष्ठा usbnet *dev)
अणु
	काष्ठा asix_common_निजी *priv = dev->driver_priv;
	u16 medium;

	/* Stop MAC operation */
	medium = asix_पढ़ो_medium_status(dev, 1);
	medium &= ~AX_MEDIUM_RE;
	asix_ग_लिखो_medium_mode(dev, medium, 1);

	netdev_dbg(dev->net, "ax88772_suspend: medium=0x%04x\n",
		   asix_पढ़ो_medium_status(dev, 1));

	/* Preserve BMCR क्रम restoring */
	priv->presvd_phy_bmcr =
		asix_mdio_पढ़ो_nopm(dev->net, dev->mii.phy_id, MII_BMCR);

	/* Preserve ANAR क्रम restoring */
	priv->presvd_phy_advertise =
		asix_mdio_पढ़ो_nopm(dev->net, dev->mii.phy_id, MII_ADVERTISE);
पूर्ण

अटल पूर्णांक asix_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा asix_common_निजी *priv = dev->driver_priv;

	अगर (priv && priv->suspend)
		priv->suspend(dev);

	वापस usbnet_suspend(पूर्णांकf, message);
पूर्ण

अटल व्योम ax88772_restore_phy(काष्ठा usbnet *dev)
अणु
	काष्ठा asix_common_निजी *priv = dev->driver_priv;

	अगर (priv->presvd_phy_advertise) अणु
		/* Restore Advertisement control reg */
		asix_mdio_ग_लिखो_nopm(dev->net, dev->mii.phy_id, MII_ADVERTISE,
				     priv->presvd_phy_advertise);

		/* Restore BMCR */
		अगर (priv->presvd_phy_bmcr & BMCR_ANENABLE)
			priv->presvd_phy_bmcr |= BMCR_ANRESTART;

		asix_mdio_ग_लिखो_nopm(dev->net, dev->mii.phy_id, MII_BMCR,
				     priv->presvd_phy_bmcr);

		priv->presvd_phy_advertise = 0;
		priv->presvd_phy_bmcr = 0;
	पूर्ण
पूर्ण

अटल व्योम ax88772_resume(काष्ठा usbnet *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++)
		अगर (!ax88772_hw_reset(dev, 1))
			अवरोध;
	ax88772_restore_phy(dev);
पूर्ण

अटल व्योम ax88772a_resume(काष्ठा usbnet *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		अगर (!ax88772a_hw_reset(dev, 1))
			अवरोध;
	पूर्ण

	ax88772_restore_phy(dev);
पूर्ण

अटल पूर्णांक asix_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा asix_common_निजी *priv = dev->driver_priv;

	अगर (priv && priv->resume)
		priv->resume(dev);

	वापस usbnet_resume(पूर्णांकf);
पूर्ण

अटल पूर्णांक ax88772_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret, i;
	u8 buf[ETH_ALEN] = अणु0पूर्ण, chipcode = 0;
	u32 phyid;
	काष्ठा asix_common_निजी *priv;

	usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);

	/* Maybe the boot loader passed the MAC address via device tree */
	अगर (!eth_platक्रमm_get_mac_address(&dev->udev->dev, buf)) अणु
		netअगर_dbg(dev, अगरup, dev->net,
			  "MAC address read from device tree");
	पूर्ण अन्यथा अणु
		/* Try getting the MAC address from EEPROM */
		अगर (dev->driver_info->data & FLAG_EEPROM_MAC) अणु
			क्रम (i = 0; i < (ETH_ALEN >> 1); i++) अणु
				ret = asix_पढ़ो_cmd(dev, AX_CMD_READ_EEPROM,
						    0x04 + i, 0, 2, buf + i * 2,
						    0);
				अगर (ret < 0)
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = asix_पढ़ो_cmd(dev, AX_CMD_READ_NODE_ID,
					    0, 0, ETH_ALEN, buf, 0);
		पूर्ण

		अगर (ret < 0) अणु
			netdev_dbg(dev->net, "Failed to read MAC address: %d\n",
				   ret);
			वापस ret;
		पूर्ण
	पूर्ण

	asix_set_netdev_dev_addr(dev, buf);

	/* Initialize MII काष्ठाure */
	dev->mii.dev = dev->net;
	dev->mii.mdio_पढ़ो = asix_mdio_पढ़ो;
	dev->mii.mdio_ग_लिखो = asix_mdio_ग_लिखो;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.phy_id = asix_get_phy_addr(dev);

	dev->net->netdev_ops = &ax88772_netdev_ops;
	dev->net->ethtool_ops = &ax88772_ethtool_ops;
	dev->net->needed_headroom = 4; /* cf asix_tx_fixup() */
	dev->net->needed_tailroom = 4; /* cf asix_tx_fixup() */

	asix_पढ़ो_cmd(dev, AX_CMD_STATMNGSTS_REG, 0, 0, 1, &chipcode, 0);
	chipcode &= AX_CHIPCODE_MASK;

	ret = (chipcode == AX_AX88772_CHIPCODE) ? ax88772_hw_reset(dev, 0) :
						  ax88772a_hw_reset(dev, 0);

	अगर (ret < 0) अणु
		netdev_dbg(dev->net, "Failed to reset AX88772: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Read PHYID रेजिस्टर *AFTER* the PHY was reset properly */
	phyid = asix_get_phyid(dev);
	netdev_dbg(dev->net, "PHYID=0x%08x\n", phyid);

	/* Asix framing packs multiple eth frames पूर्णांकo a 2K usb bulk transfer */
	अगर (dev->driver_info->flags & FLAG_FRAMING_AX) अणु
		/* hard_mtu  is still the शेष - the device करोes not support
		   jumbo eth frames */
		dev->rx_urb_size = 2048;
	पूर्ण

	dev->driver_priv = kzalloc(माप(काष्ठा asix_common_निजी), GFP_KERNEL);
	अगर (!dev->driver_priv)
		वापस -ENOMEM;

	priv = dev->driver_priv;

	priv->presvd_phy_bmcr = 0;
	priv->presvd_phy_advertise = 0;
	अगर (chipcode == AX_AX88772_CHIPCODE) अणु
		priv->resume = ax88772_resume;
		priv->suspend = ax88772_suspend;
	पूर्ण अन्यथा अणु
		priv->resume = ax88772a_resume;
		priv->suspend = ax88772_suspend;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ax88772_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	asix_rx_fixup_common_मुक्त(dev->driver_priv);
	kमुक्त(dev->driver_priv);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ax88178_ethtool_ops = अणु
	.get_drvinfo		= asix_get_drvinfo,
	.get_link		= asix_get_link,
	.get_msglevel		= usbnet_get_msglevel,
	.set_msglevel		= usbnet_set_msglevel,
	.get_wol		= asix_get_wol,
	.set_wol		= asix_set_wol,
	.get_eeprom_len		= asix_get_eeprom_len,
	.get_eeprom		= asix_get_eeprom,
	.set_eeprom		= asix_set_eeprom,
	.nway_reset		= usbnet_nway_reset,
	.get_link_ksettings	= usbnet_get_link_ksettings_mii,
	.set_link_ksettings	= usbnet_set_link_ksettings_mii,
पूर्ण;

अटल पूर्णांक marvell_phy_init(काष्ठा usbnet *dev)
अणु
	काष्ठा asix_data *data = (काष्ठा asix_data *)&dev->data;
	u16 reg;

	netdev_dbg(dev->net, "marvell_phy_init()\n");

	reg = asix_mdio_पढ़ो(dev->net, dev->mii.phy_id, MII_MARVELL_STATUS);
	netdev_dbg(dev->net, "MII_MARVELL_STATUS = 0x%04x\n", reg);

	asix_mdio_ग_लिखो(dev->net, dev->mii.phy_id, MII_MARVELL_CTRL,
			MARVELL_CTRL_RXDELAY | MARVELL_CTRL_TXDELAY);

	अगर (data->ledmode) अणु
		reg = asix_mdio_पढ़ो(dev->net, dev->mii.phy_id,
			MII_MARVELL_LED_CTRL);
		netdev_dbg(dev->net, "MII_MARVELL_LED_CTRL (1) = 0x%04x\n", reg);

		reg &= 0xf8ff;
		reg |= (1 + 0x0100);
		asix_mdio_ग_लिखो(dev->net, dev->mii.phy_id,
			MII_MARVELL_LED_CTRL, reg);

		reg = asix_mdio_पढ़ो(dev->net, dev->mii.phy_id,
			MII_MARVELL_LED_CTRL);
		netdev_dbg(dev->net, "MII_MARVELL_LED_CTRL (2) = 0x%04x\n", reg);
		reg &= 0xfc0f;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8211cl_phy_init(काष्ठा usbnet *dev)
अणु
	काष्ठा asix_data *data = (काष्ठा asix_data *)&dev->data;

	netdev_dbg(dev->net, "rtl8211cl_phy_init()\n");

	asix_mdio_ग_लिखो (dev->net, dev->mii.phy_id, 0x1f, 0x0005);
	asix_mdio_ग_लिखो (dev->net, dev->mii.phy_id, 0x0c, 0);
	asix_mdio_ग_लिखो (dev->net, dev->mii.phy_id, 0x01,
		asix_mdio_पढ़ो (dev->net, dev->mii.phy_id, 0x01) | 0x0080);
	asix_mdio_ग_लिखो (dev->net, dev->mii.phy_id, 0x1f, 0);

	अगर (data->ledmode == 12) अणु
		asix_mdio_ग_लिखो (dev->net, dev->mii.phy_id, 0x1f, 0x0002);
		asix_mdio_ग_लिखो (dev->net, dev->mii.phy_id, 0x1a, 0x00cb);
		asix_mdio_ग_लिखो (dev->net, dev->mii.phy_id, 0x1f, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_led_status(काष्ठा usbnet *dev, u16 speed)
अणु
	u16 reg = asix_mdio_पढ़ो(dev->net, dev->mii.phy_id, MARVELL_LED_MANUAL);

	netdev_dbg(dev->net, "marvell_led_status() read 0x%04x\n", reg);

	/* Clear out the center LED bits - 0x03F0 */
	reg &= 0xfc0f;

	चयन (speed) अणु
		हाल SPEED_1000:
			reg |= 0x03e0;
			अवरोध;
		हाल SPEED_100:
			reg |= 0x03b0;
			अवरोध;
		शेष:
			reg |= 0x02f0;
	पूर्ण

	netdev_dbg(dev->net, "marvell_led_status() writing 0x%04x\n", reg);
	asix_mdio_ग_लिखो(dev->net, dev->mii.phy_id, MARVELL_LED_MANUAL, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक ax88178_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा asix_data *data = (काष्ठा asix_data *)&dev->data;
	पूर्णांक ret;
	__le16 eeprom;
	u8 status;
	पूर्णांक gpio0 = 0;
	u32 phyid;

	asix_पढ़ो_cmd(dev, AX_CMD_READ_GPIOS, 0, 0, 1, &status, 0);
	netdev_dbg(dev->net, "GPIO Status: 0x%04x\n", status);

	asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_ENABLE, 0, 0, 0, शून्य, 0);
	asix_पढ़ो_cmd(dev, AX_CMD_READ_EEPROM, 0x0017, 0, 2, &eeprom, 0);
	asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_DISABLE, 0, 0, 0, शून्य, 0);

	netdev_dbg(dev->net, "EEPROM index 0x17 is 0x%04x\n", eeprom);

	अगर (eeprom == cpu_to_le16(0xffff)) अणु
		data->phymode = PHY_MODE_MARVELL;
		data->ledmode = 0;
		gpio0 = 1;
	पूर्ण अन्यथा अणु
		data->phymode = le16_to_cpu(eeprom) & 0x7F;
		data->ledmode = le16_to_cpu(eeprom) >> 8;
		gpio0 = (le16_to_cpu(eeprom) & 0x80) ? 0 : 1;
	पूर्ण
	netdev_dbg(dev->net, "GPIO0: %d, PhyMode: %d\n", gpio0, data->phymode);

	/* Power up बाह्यal GigaPHY through AX88178 GPIO pin */
	asix_ग_लिखो_gpio(dev, AX_GPIO_RSE | AX_GPIO_GPO_1 |
			AX_GPIO_GPO1EN, 40, 0);
	अगर ((le16_to_cpu(eeprom) >> 8) != 1) अणु
		asix_ग_लिखो_gpio(dev, 0x003c, 30, 0);
		asix_ग_लिखो_gpio(dev, 0x001c, 300, 0);
		asix_ग_लिखो_gpio(dev, 0x003c, 30, 0);
	पूर्ण अन्यथा अणु
		netdev_dbg(dev->net, "gpio phymode == 1 path\n");
		asix_ग_लिखो_gpio(dev, AX_GPIO_GPO1EN, 30, 0);
		asix_ग_लिखो_gpio(dev, AX_GPIO_GPO1EN | AX_GPIO_GPO_1, 30, 0);
	पूर्ण

	/* Read PHYID रेजिस्टर *AFTER* घातering up PHY */
	phyid = asix_get_phyid(dev);
	netdev_dbg(dev->net, "PHYID=0x%08x\n", phyid);

	/* Set AX88178 to enable MII/GMII/RGMII पूर्णांकerface क्रम बाह्यal PHY */
	asix_ग_लिखो_cmd(dev, AX_CMD_SW_PHY_SELECT, 0, 0, 0, शून्य, 0);

	asix_sw_reset(dev, 0, 0);
	msleep(150);

	asix_sw_reset(dev, AX_SWRESET_PRL | AX_SWRESET_IPPD, 0);
	msleep(150);

	asix_ग_लिखो_rx_ctl(dev, 0, 0);

	अगर (data->phymode == PHY_MODE_MARVELL) अणु
		marvell_phy_init(dev);
		msleep(60);
	पूर्ण अन्यथा अगर (data->phymode == PHY_MODE_RTL8211CL)
		rtl8211cl_phy_init(dev);

	asix_phy_reset(dev, BMCR_RESET | BMCR_ANENABLE);
	asix_mdio_ग_लिखो(dev->net, dev->mii.phy_id, MII_ADVERTISE,
			ADVERTISE_ALL | ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP);
	asix_mdio_ग_लिखो(dev->net, dev->mii.phy_id, MII_CTRL1000,
			ADVERTISE_1000FULL);

	asix_ग_लिखो_medium_mode(dev, AX88178_MEDIUM_DEFAULT, 0);
	mii_nway_restart(&dev->mii);

	/* Reग_लिखो MAC address */
	स_नकल(data->mac_addr, dev->net->dev_addr, ETH_ALEN);
	ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_NODE_ID, 0, 0, ETH_ALEN,
							data->mac_addr, 0);
	अगर (ret < 0)
		वापस ret;

	ret = asix_ग_लिखो_rx_ctl(dev, AX_DEFAULT_RX_CTL, 0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ax88178_link_reset(काष्ठा usbnet *dev)
अणु
	u16 mode;
	काष्ठा ethtool_cmd ecmd = अणु .cmd = ETHTOOL_GSET पूर्ण;
	काष्ठा asix_data *data = (काष्ठा asix_data *)&dev->data;
	u32 speed;

	netdev_dbg(dev->net, "ax88178_link_reset()\n");

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);
	mode = AX88178_MEDIUM_DEFAULT;
	speed = ethtool_cmd_speed(&ecmd);

	अगर (speed == SPEED_1000)
		mode |= AX_MEDIUM_GM;
	अन्यथा अगर (speed == SPEED_100)
		mode |= AX_MEDIUM_PS;
	अन्यथा
		mode &= ~(AX_MEDIUM_PS | AX_MEDIUM_GM);

	mode |= AX_MEDIUM_ENCK;

	अगर (ecmd.duplex == DUPLEX_FULL)
		mode |= AX_MEDIUM_FD;
	अन्यथा
		mode &= ~AX_MEDIUM_FD;

	netdev_dbg(dev->net, "ax88178_link_reset() speed: %u duplex: %d setting mode to 0x%04x\n",
		   speed, ecmd.duplex, mode);

	asix_ग_लिखो_medium_mode(dev, mode, 0);

	अगर (data->phymode == PHY_MODE_MARVELL && data->ledmode)
		marvell_led_status(dev, speed);

	वापस 0;
पूर्ण

अटल व्योम ax88178_set_mfb(काष्ठा usbnet *dev)
अणु
	u16 mfb = AX_RX_CTL_MFB_16384;
	u16 rxctl;
	u16 medium;
	पूर्णांक old_rx_urb_size = dev->rx_urb_size;

	अगर (dev->hard_mtu < 2048) अणु
		dev->rx_urb_size = 2048;
		mfb = AX_RX_CTL_MFB_2048;
	पूर्ण अन्यथा अगर (dev->hard_mtu < 4096) अणु
		dev->rx_urb_size = 4096;
		mfb = AX_RX_CTL_MFB_4096;
	पूर्ण अन्यथा अगर (dev->hard_mtu < 8192) अणु
		dev->rx_urb_size = 8192;
		mfb = AX_RX_CTL_MFB_8192;
	पूर्ण अन्यथा अगर (dev->hard_mtu < 16384) अणु
		dev->rx_urb_size = 16384;
		mfb = AX_RX_CTL_MFB_16384;
	पूर्ण

	rxctl = asix_पढ़ो_rx_ctl(dev, 0);
	asix_ग_लिखो_rx_ctl(dev, (rxctl & ~AX_RX_CTL_MFB_16384) | mfb, 0);

	medium = asix_पढ़ो_medium_status(dev, 0);
	अगर (dev->net->mtu > 1500)
		medium |= AX_MEDIUM_JFE;
	अन्यथा
		medium &= ~AX_MEDIUM_JFE;
	asix_ग_लिखो_medium_mode(dev, medium, 0);

	अगर (dev->rx_urb_size > old_rx_urb_size)
		usbnet_unlink_rx_urbs(dev);
पूर्ण

अटल पूर्णांक ax88178_change_mtu(काष्ठा net_device *net, पूर्णांक new_mtu)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	पूर्णांक ll_mtu = new_mtu + net->hard_header_len + 4;

	netdev_dbg(dev->net, "ax88178_change_mtu() new_mtu=%d\n", new_mtu);

	अगर ((ll_mtu % dev->maxpacket) == 0)
		वापस -गलत_तर्क;

	net->mtu = new_mtu;
	dev->hard_mtu = net->mtu + net->hard_header_len;
	ax88178_set_mfb(dev);

	/* max qlen depend on hard_mtu and rx_urb_size */
	usbnet_update_max_qlen(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ax88178_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_set_mac_address 	= asix_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= asix_set_multicast,
	.nकरो_करो_ioctl 		= asix_ioctl,
	.nकरो_change_mtu 	= ax88178_change_mtu,
पूर्ण;

अटल पूर्णांक ax88178_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret;
	u8 buf[ETH_ALEN] = अणु0पूर्ण;

	usbnet_get_endpoपूर्णांकs(dev,पूर्णांकf);

	/* Get the MAC address */
	ret = asix_पढ़ो_cmd(dev, AX_CMD_READ_NODE_ID, 0, 0, ETH_ALEN, buf, 0);
	अगर (ret < 0) अणु
		netdev_dbg(dev->net, "Failed to read MAC address: %d\n", ret);
		वापस ret;
	पूर्ण

	asix_set_netdev_dev_addr(dev, buf);

	/* Initialize MII काष्ठाure */
	dev->mii.dev = dev->net;
	dev->mii.mdio_पढ़ो = asix_mdio_पढ़ो;
	dev->mii.mdio_ग_लिखो = asix_mdio_ग_लिखो;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0xff;
	dev->mii.supports_gmii = 1;
	dev->mii.phy_id = asix_get_phy_addr(dev);

	dev->net->netdev_ops = &ax88178_netdev_ops;
	dev->net->ethtool_ops = &ax88178_ethtool_ops;
	dev->net->max_mtu = 16384 - (dev->net->hard_header_len + 4);

	/* Blink LEDS so users know driver saw करोngle */
	asix_sw_reset(dev, 0, 0);
	msleep(150);

	asix_sw_reset(dev, AX_SWRESET_PRL | AX_SWRESET_IPPD, 0);
	msleep(150);

	/* Asix framing packs multiple eth frames पूर्णांकo a 2K usb bulk transfer */
	अगर (dev->driver_info->flags & FLAG_FRAMING_AX) अणु
		/* hard_mtu  is still the शेष - the device करोes not support
		   jumbo eth frames */
		dev->rx_urb_size = 2048;
	पूर्ण

	dev->driver_priv = kzalloc(माप(काष्ठा asix_common_निजी), GFP_KERNEL);
	अगर (!dev->driver_priv)
			वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा driver_info ax8817x_info = अणु
	.description = "ASIX AX8817x USB 2.0 Ethernet",
	.bind = ax88172_bind,
	.status = asix_status,
	.link_reset = ax88172_link_reset,
	.reset = ax88172_link_reset,
	.flags =  FLAG_ETHER | FLAG_LINK_INTR,
	.data = 0x00130103,
पूर्ण;

अटल स्थिर काष्ठा driver_info dlink_dub_e100_info = अणु
	.description = "DLink DUB-E100 USB Ethernet",
	.bind = ax88172_bind,
	.status = asix_status,
	.link_reset = ax88172_link_reset,
	.reset = ax88172_link_reset,
	.flags =  FLAG_ETHER | FLAG_LINK_INTR,
	.data = 0x009f9d9f,
पूर्ण;

अटल स्थिर काष्ठा driver_info netgear_fa120_info = अणु
	.description = "Netgear FA-120 USB Ethernet",
	.bind = ax88172_bind,
	.status = asix_status,
	.link_reset = ax88172_link_reset,
	.reset = ax88172_link_reset,
	.flags =  FLAG_ETHER | FLAG_LINK_INTR,
	.data = 0x00130103,
पूर्ण;

अटल स्थिर काष्ठा driver_info hawking_uf200_info = अणु
	.description = "Hawking UF200 USB Ethernet",
	.bind = ax88172_bind,
	.status = asix_status,
	.link_reset = ax88172_link_reset,
	.reset = ax88172_link_reset,
	.flags =  FLAG_ETHER | FLAG_LINK_INTR,
	.data = 0x001f1d1f,
पूर्ण;

अटल स्थिर काष्ठा driver_info ax88772_info = अणु
	.description = "ASIX AX88772 USB 2.0 Ethernet",
	.bind = ax88772_bind,
	.unbind = ax88772_unbind,
	.status = asix_status,
	.link_reset = ax88772_link_reset,
	.reset = ax88772_reset,
	.flags = FLAG_ETHER | FLAG_FRAMING_AX | FLAG_LINK_INTR | FLAG_MULTI_PACKET,
	.rx_fixup = asix_rx_fixup_common,
	.tx_fixup = asix_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info ax88772b_info = अणु
	.description = "ASIX AX88772B USB 2.0 Ethernet",
	.bind = ax88772_bind,
	.unbind = ax88772_unbind,
	.status = asix_status,
	.link_reset = ax88772_link_reset,
	.reset = ax88772_reset,
	.flags = FLAG_ETHER | FLAG_FRAMING_AX | FLAG_LINK_INTR |
	         FLAG_MULTI_PACKET,
	.rx_fixup = asix_rx_fixup_common,
	.tx_fixup = asix_tx_fixup,
	.data = FLAG_EEPROM_MAC,
पूर्ण;

अटल स्थिर काष्ठा driver_info ax88178_info = अणु
	.description = "ASIX AX88178 USB 2.0 Ethernet",
	.bind = ax88178_bind,
	.unbind = ax88772_unbind,
	.status = asix_status,
	.link_reset = ax88178_link_reset,
	.reset = ax88178_reset,
	.flags = FLAG_ETHER | FLAG_FRAMING_AX | FLAG_LINK_INTR |
		 FLAG_MULTI_PACKET,
	.rx_fixup = asix_rx_fixup_common,
	.tx_fixup = asix_tx_fixup,
पूर्ण;

/*
 * USBLINK 20F9 "USB 2.0 LAN" USB ethernet adapter, typically found in
 * no-name packaging.
 * USB device strings are:
 *   1: Manufacturer: USBLINK
 *   2: Product: HG20F9 USB2.0
 *   3: Serial: 000003
 * Appears to be compatible with Asix 88772B.
 */
अटल स्थिर काष्ठा driver_info hg20f9_info = अणु
	.description = "HG20F9 USB 2.0 Ethernet",
	.bind = ax88772_bind,
	.unbind = ax88772_unbind,
	.status = asix_status,
	.link_reset = ax88772_link_reset,
	.reset = ax88772_reset,
	.flags = FLAG_ETHER | FLAG_FRAMING_AX | FLAG_LINK_INTR |
	         FLAG_MULTI_PACKET,
	.rx_fixup = asix_rx_fixup_common,
	.tx_fixup = asix_tx_fixup,
	.data = FLAG_EEPROM_MAC,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id	products [] = अणु
अणु
	// Linksys USB200M
	USB_DEVICE (0x077b, 0x2226),
	.driver_info =	(अचिन्हित दीर्घ) &ax8817x_info,
पूर्ण, अणु
	// Netgear FA120
	USB_DEVICE (0x0846, 0x1040),
	.driver_info =  (अचिन्हित दीर्घ) &netgear_fa120_info,
पूर्ण, अणु
	// DLink DUB-E100
	USB_DEVICE (0x2001, 0x1a00),
	.driver_info =  (अचिन्हित दीर्घ) &dlink_dub_e100_info,
पूर्ण, अणु
	// Intellinet, ST Lab USB Ethernet
	USB_DEVICE (0x0b95, 0x1720),
	.driver_info =  (अचिन्हित दीर्घ) &ax8817x_info,
पूर्ण, अणु
	// Hawking UF200, TrendNet TU2-ET100
	USB_DEVICE (0x07b8, 0x420a),
	.driver_info =  (अचिन्हित दीर्घ) &hawking_uf200_info,
पूर्ण, अणु
	// Billionton Systems, USB2AR
	USB_DEVICE (0x08dd, 0x90ff),
	.driver_info =  (अचिन्हित दीर्घ) &ax8817x_info,
पूर्ण, अणु
	// Billionton Systems, GUSB2AM-1G-B
	USB_DEVICE(0x08dd, 0x0114),
	.driver_info =  (अचिन्हित दीर्घ) &ax88178_info,
पूर्ण, अणु
	// ATEN UC210T
	USB_DEVICE (0x0557, 0x2009),
	.driver_info =  (अचिन्हित दीर्घ) &ax8817x_info,
पूर्ण, अणु
	// Buffalo LUA-U2-KTX
	USB_DEVICE (0x0411, 0x003d),
	.driver_info =  (अचिन्हित दीर्घ) &ax8817x_info,
पूर्ण, अणु
	// Buffalo LUA-U2-GT 10/100/1000
	USB_DEVICE (0x0411, 0x006e),
	.driver_info =  (अचिन्हित दीर्घ) &ax88178_info,
पूर्ण, अणु
	// Sitecom LN-029 "USB 2.0 10/100 Ethernet adapter"
	USB_DEVICE (0x6189, 0x182d),
	.driver_info =  (अचिन्हित दीर्घ) &ax8817x_info,
पूर्ण, अणु
	// Sitecom LN-031 "USB 2.0 10/100/1000 Ethernet adapter"
	USB_DEVICE (0x0df6, 0x0056),
	.driver_info =  (अचिन्हित दीर्घ) &ax88178_info,
पूर्ण, अणु
	// Sitecom LN-028 "USB 2.0 10/100/1000 Ethernet adapter"
	USB_DEVICE (0x0df6, 0x061c),
	.driver_info =  (अचिन्हित दीर्घ) &ax88178_info,
पूर्ण, अणु
	// corega FEther USB2-TX
	USB_DEVICE (0x07aa, 0x0017),
	.driver_info =  (अचिन्हित दीर्घ) &ax8817x_info,
पूर्ण, अणु
	// Surecom EP-1427X-2
	USB_DEVICE (0x1189, 0x0893),
	.driver_info = (अचिन्हित दीर्घ) &ax8817x_info,
पूर्ण, अणु
	// goodway corp usb gwusb2e
	USB_DEVICE (0x1631, 0x6200),
	.driver_info = (अचिन्हित दीर्घ) &ax8817x_info,
पूर्ण, अणु
	// JVC MP-PRX1 Port Replicator
	USB_DEVICE (0x04f1, 0x3008),
	.driver_info = (अचिन्हित दीर्घ) &ax8817x_info,
पूर्ण, अणु
	// Lenovo U2L100P 10/100
	USB_DEVICE (0x17ef, 0x7203),
	.driver_info = (अचिन्हित दीर्घ)&ax88772b_info,
पूर्ण, अणु
	// ASIX AX88772B 10/100
	USB_DEVICE (0x0b95, 0x772b),
	.driver_info = (अचिन्हित दीर्घ) &ax88772b_info,
पूर्ण, अणु
	// ASIX AX88772 10/100
	USB_DEVICE (0x0b95, 0x7720),
	.driver_info = (अचिन्हित दीर्घ) &ax88772_info,
पूर्ण, अणु
	// ASIX AX88178 10/100/1000
	USB_DEVICE (0x0b95, 0x1780),
	.driver_info = (अचिन्हित दीर्घ) &ax88178_info,
पूर्ण, अणु
	// Logitec LAN-GTJ/U2A
	USB_DEVICE (0x0789, 0x0160),
	.driver_info = (अचिन्हित दीर्घ) &ax88178_info,
पूर्ण, अणु
	// Linksys USB200M Rev 2
	USB_DEVICE (0x13b1, 0x0018),
	.driver_info = (अचिन्हित दीर्घ) &ax88772_info,
पूर्ण, अणु
	// 0Q0 cable ethernet
	USB_DEVICE (0x1557, 0x7720),
	.driver_info = (अचिन्हित दीर्घ) &ax88772_info,
पूर्ण, अणु
	// DLink DUB-E100 H/W Ver B1
	USB_DEVICE (0x07d1, 0x3c05),
	.driver_info = (अचिन्हित दीर्घ) &ax88772_info,
पूर्ण, अणु
	// DLink DUB-E100 H/W Ver B1 Alternate
	USB_DEVICE (0x2001, 0x3c05),
	.driver_info = (अचिन्हित दीर्घ) &ax88772_info,
पूर्ण, अणु
       // DLink DUB-E100 H/W Ver C1
       USB_DEVICE (0x2001, 0x1a02),
       .driver_info = (अचिन्हित दीर्घ) &ax88772_info,
पूर्ण, अणु
	// Linksys USB1000
	USB_DEVICE (0x1737, 0x0039),
	.driver_info = (अचिन्हित दीर्घ) &ax88178_info,
पूर्ण, अणु
	// IO-DATA ETG-US2
	USB_DEVICE (0x04bb, 0x0930),
	.driver_info = (अचिन्हित दीर्घ) &ax88178_info,
पूर्ण, अणु
	// Belkin F5D5055
	USB_DEVICE(0x050d, 0x5055),
	.driver_info = (अचिन्हित दीर्घ) &ax88178_info,
पूर्ण, अणु
	// Apple USB Ethernet Adapter
	USB_DEVICE(0x05ac, 0x1402),
	.driver_info = (अचिन्हित दीर्घ) &ax88772_info,
पूर्ण, अणु
	// Cables-to-Go USB Ethernet Adapter
	USB_DEVICE(0x0b95, 0x772a),
	.driver_info = (अचिन्हित दीर्घ) &ax88772_info,
पूर्ण, अणु
	// ABOCOM क्रम pci
	USB_DEVICE(0x14ea, 0xab11),
	.driver_info = (अचिन्हित दीर्घ) &ax88178_info,
पूर्ण, अणु
	// ASIX 88772a
	USB_DEVICE(0x0db0, 0xa877),
	.driver_info = (अचिन्हित दीर्घ) &ax88772_info,
पूर्ण, अणु
	// Asus USB Ethernet Adapter
	USB_DEVICE (0x0b95, 0x7e2b),
	.driver_info = (अचिन्हित दीर्घ)&ax88772b_info,
पूर्ण, अणु
	/* ASIX 88172a demo board */
	USB_DEVICE(0x0b95, 0x172a),
	.driver_info = (अचिन्हित दीर्घ) &ax88172a_info,
पूर्ण, अणु
	/*
	 * USBLINK HG20F9 "USB 2.0 LAN"
	 * Appears to have gazumped Linksys's manufacturer ID but
	 * करोesn't (yet) conflict with any known Linksys product.
	 */
	USB_DEVICE(0x066b, 0x20f9),
	.driver_info = (अचिन्हित दीर्घ) &hg20f9_info,
पूर्ण,
	अणु पूर्ण,		// END
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver asix_driver = अणु
	.name =		DRIVER_NAME,
	.id_table =	products,
	.probe =	usbnet_probe,
	.suspend =	asix_suspend,
	.resume =	asix_resume,
	.reset_resume =	asix_resume,
	.disconnect =	usbnet_disconnect,
	.supports_स्वतःsuspend = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(asix_driver);

MODULE_AUTHOR("David Hollis");
MODULE_VERSION(DRIVER_VERSION);
MODULE_DESCRIPTION("ASIX AX8817X based USB 2.0 Ethernet Devices");
MODULE_LICENSE("GPL");

