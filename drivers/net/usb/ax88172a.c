<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ASIX AX88172A based USB 2.0 Ethernet Devices
 * Copyright (C) 2012 OMICRON electronics GmbH
 *
 * Supports बाह्यal PHYs via phylib. Based on the driver क्रम the
 * AX88772. Original copyrights follow:
 *
 * Copyright (C) 2003-2006 David Hollis <dhollis@davehollis.com>
 * Copyright (C) 2005 Phil Chang <pchang23@sbcglobal.net>
 * Copyright (C) 2006 James Paपूर्णांकer <jamie.paपूर्णांकer@iname.com>
 * Copyright (c) 2002-2003 TiVo Inc.
 */

#समावेश "asix.h"
#समावेश <linux/phy.h>

काष्ठा ax88172a_निजी अणु
	काष्ठा mii_bus *mdio;
	काष्ठा phy_device *phydev;
	अक्षर phy_name[20];
	u16 phy_addr;
	u16 oldmode;
	पूर्णांक use_embdphy;
	काष्ठा asix_rx_fixup_info rx_fixup_info;
पूर्ण;

/* MDIO पढ़ो and ग_लिखो wrappers क्रम phylib */
अटल पूर्णांक asix_mdio_bus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum)
अणु
	वापस asix_mdio_पढ़ो(((काष्ठा usbnet *)bus->priv)->net, phy_id,
			      regnum);
पूर्ण

अटल पूर्णांक asix_mdio_bus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum,
			       u16 val)
अणु
	asix_mdio_ग_लिखो(((काष्ठा usbnet *)bus->priv)->net, phy_id, regnum, val);
	वापस 0;
पूर्ण

/* set MAC link settings according to inक्रमmation from phylib */
अटल व्योम ax88172a_adjust_link(काष्ठा net_device *netdev)
अणु
	काष्ठा phy_device *phydev = netdev->phydev;
	काष्ठा usbnet *dev = netdev_priv(netdev);
	काष्ठा ax88172a_निजी *priv = dev->driver_priv;
	u16 mode = 0;

	अगर (phydev->link) अणु
		mode = AX88772_MEDIUM_DEFAULT;

		अगर (phydev->duplex == DUPLEX_HALF)
			mode &= ~AX_MEDIUM_FD;

		अगर (phydev->speed != SPEED_100)
			mode &= ~AX_MEDIUM_PS;
	पूर्ण

	अगर (mode != priv->oldmode) अणु
		asix_ग_लिखो_medium_mode(dev, mode, 0);
		priv->oldmode = mode;
		netdev_dbg(netdev, "speed %u duplex %d, setting mode to 0x%04x\n",
			   phydev->speed, phydev->duplex, mode);
		phy_prपूर्णांक_status(phydev);
	पूर्ण
पूर्ण

अटल व्योम ax88172a_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	/* link changes are detected by polling the phy */
पूर्ण

/* use phylib infraकाष्ठाure */
अटल पूर्णांक ax88172a_init_mdio(काष्ठा usbnet *dev)
अणु
	काष्ठा ax88172a_निजी *priv = dev->driver_priv;
	पूर्णांक ret;

	priv->mdio = mdiobus_alloc();
	अगर (!priv->mdio) अणु
		netdev_err(dev->net, "Could not allocate MDIO bus\n");
		वापस -ENOMEM;
	पूर्ण

	priv->mdio->priv = (व्योम *)dev;
	priv->mdio->पढ़ो = &asix_mdio_bus_पढ़ो;
	priv->mdio->ग_लिखो = &asix_mdio_bus_ग_लिखो;
	priv->mdio->name = "Asix MDIO Bus";
	/* mii bus name is usb-<usb bus number>-<usb device number> */
	snम_लिखो(priv->mdio->id, MII_BUS_ID_SIZE, "usb-%03d:%03d",
		 dev->udev->bus->busnum, dev->udev->devnum);

	ret = mdiobus_रेजिस्टर(priv->mdio);
	अगर (ret) अणु
		netdev_err(dev->net, "Could not register MDIO bus\n");
		जाओ mमुक्त;
	पूर्ण

	netdev_info(dev->net, "registered mdio bus %s\n", priv->mdio->id);
	वापस 0;

mमुक्त:
	mdiobus_मुक्त(priv->mdio);
	वापस ret;
पूर्ण

अटल व्योम ax88172a_हटाओ_mdio(काष्ठा usbnet *dev)
अणु
	काष्ठा ax88172a_निजी *priv = dev->driver_priv;

	netdev_info(dev->net, "deregistering mdio bus %s\n", priv->mdio->id);
	mdiobus_unरेजिस्टर(priv->mdio);
	mdiobus_मुक्त(priv->mdio);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ax88172a_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_change_mtu		= usbnet_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_set_mac_address	= asix_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_set_rx_mode        = asix_set_multicast,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops ax88172a_ethtool_ops = अणु
	.get_drvinfo		= asix_get_drvinfo,
	.get_link		= usbnet_get_link,
	.get_msglevel		= usbnet_get_msglevel,
	.set_msglevel		= usbnet_set_msglevel,
	.get_wol		= asix_get_wol,
	.set_wol		= asix_set_wol,
	.get_eeprom_len		= asix_get_eeprom_len,
	.get_eeprom		= asix_get_eeprom,
	.set_eeprom		= asix_set_eeprom,
	.nway_reset		= phy_ethtool_nway_reset,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
पूर्ण;

अटल पूर्णांक ax88172a_reset_phy(काष्ठा usbnet *dev, पूर्णांक embd_phy)
अणु
	पूर्णांक ret;

	ret = asix_sw_reset(dev, AX_SWRESET_IPPD, 0);
	अगर (ret < 0)
		जाओ err;

	msleep(150);
	ret = asix_sw_reset(dev, AX_SWRESET_CLEAR, 0);
	अगर (ret < 0)
		जाओ err;

	msleep(150);

	ret = asix_sw_reset(dev, embd_phy ? AX_SWRESET_IPRL : AX_SWRESET_IPPD,
			    0);
	अगर (ret < 0)
		जाओ err;

	वापस 0;

err:
	वापस ret;
पूर्ण


अटल पूर्णांक ax88172a_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret;
	u8 buf[ETH_ALEN];
	काष्ठा ax88172a_निजी *priv;

	usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev->driver_priv = priv;

	/* Get the MAC address */
	ret = asix_पढ़ो_cmd(dev, AX_CMD_READ_NODE_ID, 0, 0, ETH_ALEN, buf, 0);
	अगर (ret < ETH_ALEN) अणु
		netdev_err(dev->net, "Failed to read MAC address: %d\n", ret);
		ret = -EIO;
		जाओ मुक्त;
	पूर्ण
	स_नकल(dev->net->dev_addr, buf, ETH_ALEN);

	dev->net->netdev_ops = &ax88172a_netdev_ops;
	dev->net->ethtool_ops = &ax88172a_ethtool_ops;

	/* are we using the पूर्णांकernal or the बाह्यal phy? */
	ret = asix_पढ़ो_cmd(dev, AX_CMD_SW_PHY_STATUS, 0, 0, 1, buf, 0);
	अगर (ret < 0) अणु
		netdev_err(dev->net, "Failed to read software interface selection register: %d\n",
			   ret);
		जाओ मुक्त;
	पूर्ण

	netdev_dbg(dev->net, "AX_CMD_SW_PHY_STATUS = 0x%02x\n", buf[0]);
	चयन (buf[0] & AX_PHY_SELECT_MASK) अणु
	हाल AX_PHY_SELECT_INTERNAL:
		netdev_dbg(dev->net, "use internal phy\n");
		priv->use_embdphy = 1;
		अवरोध;
	हाल AX_PHY_SELECT_EXTERNAL:
		netdev_dbg(dev->net, "use external phy\n");
		priv->use_embdphy = 0;
		अवरोध;
	शेष:
		netdev_err(dev->net, "Interface mode not supported by driver\n");
		ret = -ENOTSUPP;
		जाओ मुक्त;
	पूर्ण

	priv->phy_addr = asix_पढ़ो_phy_addr(dev, priv->use_embdphy);
	ax88172a_reset_phy(dev, priv->use_embdphy);

	/* Asix framing packs multiple eth frames पूर्णांकo a 2K usb bulk transfer */
	अगर (dev->driver_info->flags & FLAG_FRAMING_AX) अणु
		/* hard_mtu  is still the शेष - the device करोes not support
		   jumbo eth frames */
		dev->rx_urb_size = 2048;
	पूर्ण

	/* init MDIO bus */
	ret = ax88172a_init_mdio(dev);
	अगर (ret)
		जाओ मुक्त;

	वापस 0;

मुक्त:
	kमुक्त(priv);
	वापस ret;
पूर्ण

अटल पूर्णांक ax88172a_stop(काष्ठा usbnet *dev)
अणु
	काष्ठा ax88172a_निजी *priv = dev->driver_priv;

	netdev_dbg(dev->net, "Stopping interface\n");

	अगर (priv->phydev) अणु
		netdev_info(dev->net, "Disconnecting from phy %s\n",
			    priv->phy_name);
		phy_stop(priv->phydev);
		phy_disconnect(priv->phydev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ax88172a_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ax88172a_निजी *priv = dev->driver_priv;

	ax88172a_हटाओ_mdio(dev);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक ax88172a_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा asix_data *data = (काष्ठा asix_data *)&dev->data;
	काष्ठा ax88172a_निजी *priv = dev->driver_priv;
	पूर्णांक ret;
	u16 rx_ctl;

	ax88172a_reset_phy(dev, priv->use_embdphy);

	msleep(150);
	rx_ctl = asix_पढ़ो_rx_ctl(dev, 0);
	netdev_dbg(dev->net, "RX_CTL is 0x%04x after software reset\n", rx_ctl);
	ret = asix_ग_लिखो_rx_ctl(dev, 0x0000, 0);
	अगर (ret < 0)
		जाओ out;

	rx_ctl = asix_पढ़ो_rx_ctl(dev, 0);
	netdev_dbg(dev->net, "RX_CTL is 0x%04x setting to 0x0000\n", rx_ctl);

	msleep(150);

	ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_IPG0,
			     AX88772_IPG0_DEFAULT | AX88772_IPG1_DEFAULT,
			     AX88772_IPG2_DEFAULT, 0, शून्य, 0);
	अगर (ret < 0) अणु
		netdev_err(dev->net, "Write IPG,IPG1,IPG2 failed: %d\n", ret);
		जाओ out;
	पूर्ण

	/* Reग_लिखो MAC address */
	स_नकल(data->mac_addr, dev->net->dev_addr, ETH_ALEN);
	ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_NODE_ID, 0, 0, ETH_ALEN,
			     data->mac_addr, 0);
	अगर (ret < 0)
		जाओ out;

	/* Set RX_CTL to शेष values with 2k buffer, and enable cactus */
	ret = asix_ग_लिखो_rx_ctl(dev, AX_DEFAULT_RX_CTL, 0);
	अगर (ret < 0)
		जाओ out;

	rx_ctl = asix_पढ़ो_rx_ctl(dev, 0);
	netdev_dbg(dev->net, "RX_CTL is 0x%04x after all initializations\n",
		   rx_ctl);

	rx_ctl = asix_पढ़ो_medium_status(dev, 0);
	netdev_dbg(dev->net, "Medium Status is 0x%04x after all initializations\n",
		   rx_ctl);

	/* Connect to PHY */
	snम_लिखो(priv->phy_name, 20, PHY_ID_FMT,
		 priv->mdio->id, priv->phy_addr);

	priv->phydev = phy_connect(dev->net, priv->phy_name,
				   &ax88172a_adjust_link,
				   PHY_INTERFACE_MODE_MII);
	अगर (IS_ERR(priv->phydev)) अणु
		netdev_err(dev->net, "Could not connect to PHY device %s\n",
			   priv->phy_name);
		ret = PTR_ERR(priv->phydev);
		जाओ out;
	पूर्ण

	netdev_info(dev->net, "Connected to phy %s\n", priv->phy_name);

	/* During घातer-up, the AX88172A set the घातer करोwn (BMCR_PDOWN)
	 * bit of the PHY. Bring the PHY up again.
	 */
	genphy_resume(priv->phydev);
	phy_start(priv->phydev);

	वापस 0;

out:
	वापस ret;

पूर्ण

अटल पूर्णांक ax88172a_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा ax88172a_निजी *dp = dev->driver_priv;
	काष्ठा asix_rx_fixup_info *rx = &dp->rx_fixup_info;

	वापस asix_rx_fixup_पूर्णांकernal(dev, skb, rx);
पूर्ण

स्थिर काष्ठा driver_info ax88172a_info = अणु
	.description = "ASIX AX88172A USB 2.0 Ethernet",
	.bind = ax88172a_bind,
	.reset = ax88172a_reset,
	.stop = ax88172a_stop,
	.unbind = ax88172a_unbind,
	.status = ax88172a_status,
	.flags = FLAG_ETHER | FLAG_FRAMING_AX | FLAG_LINK_INTR |
		 FLAG_MULTI_PACKET,
	.rx_fixup = ax88172a_rx_fixup,
	.tx_fixup = asix_tx_fixup,
पूर्ण;
