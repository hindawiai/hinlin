<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Aquantia Corp. Aquantia AQtion USB to 5GbE Controller
 * Copyright (C) 2003-2005 David Hollis <dhollis@davehollis.com>
 * Copyright (C) 2005 Phil Chang <pchang23@sbcglobal.net>
 * Copyright (C) 2002-2003 TiVo Inc.
 * Copyright (C) 2017-2018 ASIX
 * Copyright (C) 2018 Aquantia Corp.
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/crc32.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/linkmode.h>

#समावेश "aqc111.h"

#घोषणा DRIVER_NAME "aqc111"

अटल पूर्णांक aqc111_पढ़ो_cmd_nopm(काष्ठा usbnet *dev, u8 cmd, u16 value,
				u16 index, u16 size, व्योम *data)
अणु
	पूर्णांक ret;

	ret = usbnet_पढ़ो_cmd_nopm(dev, cmd, USB_सूची_IN | USB_TYPE_VENDOR |
				   USB_RECIP_DEVICE, value, index, data, size);

	अगर (unlikely(ret < 0))
		netdev_warn(dev->net,
			    "Failed to read(0x%x) reg index 0x%04x: %d\n",
			    cmd, index, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक aqc111_पढ़ो_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value,
			   u16 index, u16 size, व्योम *data)
अणु
	पूर्णांक ret;

	ret = usbnet_पढ़ो_cmd(dev, cmd, USB_सूची_IN | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, value, index, data, size);

	अगर (unlikely(ret < 0))
		netdev_warn(dev->net,
			    "Failed to read(0x%x) reg index 0x%04x: %d\n",
			    cmd, index, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक aqc111_पढ़ो16_cmd_nopm(काष्ठा usbnet *dev, u8 cmd, u16 value,
				  u16 index, u16 *data)
अणु
	पूर्णांक ret = 0;

	ret = aqc111_पढ़ो_cmd_nopm(dev, cmd, value, index, माप(*data), data);
	le16_to_cpus(data);

	वापस ret;
पूर्ण

अटल पूर्णांक aqc111_पढ़ो16_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value,
			     u16 index, u16 *data)
अणु
	पूर्णांक ret = 0;

	ret = aqc111_पढ़ो_cmd(dev, cmd, value, index, माप(*data), data);
	le16_to_cpus(data);

	वापस ret;
पूर्ण

अटल पूर्णांक __aqc111_ग_लिखो_cmd(काष्ठा usbnet *dev, u8 cmd, u8 reqtype,
			      u16 value, u16 index, u16 size, स्थिर व्योम *data)
अणु
	पूर्णांक err = -ENOMEM;
	व्योम *buf = शून्य;

	netdev_dbg(dev->net,
		   "%s cmd=%#x reqtype=%#x value=%#x index=%#x size=%d\n",
		   __func__, cmd, reqtype, value, index, size);

	अगर (data) अणु
		buf = kmemdup(data, size, GFP_KERNEL);
		अगर (!buf)
			जाओ out;
	पूर्ण

	err = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
			      cmd, reqtype, value, index, buf, size,
			      (cmd == AQ_PHY_POWER) ? AQ_USB_PHY_SET_TIMEOUT :
			      AQ_USB_SET_TIMEOUT);

	अगर (unlikely(err < 0))
		netdev_warn(dev->net,
			    "Failed to write(0x%x) reg index 0x%04x: %d\n",
			    cmd, index, err);
	kमुक्त(buf);

out:
	वापस err;
पूर्ण

अटल पूर्णांक aqc111_ग_लिखो_cmd_nopm(काष्ठा usbnet *dev, u8 cmd, u16 value,
				 u16 index, u16 size, व्योम *data)
अणु
	पूर्णांक ret;

	ret = __aqc111_ग_लिखो_cmd(dev, cmd, USB_सूची_OUT | USB_TYPE_VENDOR |
				 USB_RECIP_DEVICE, value, index, size, data);

	वापस ret;
पूर्ण

अटल पूर्णांक aqc111_ग_लिखो_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value,
			    u16 index, u16 size, व्योम *data)
अणु
	पूर्णांक ret;

	अगर (usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf) < 0)
		वापस -ENODEV;

	ret = __aqc111_ग_लिखो_cmd(dev, cmd, USB_सूची_OUT | USB_TYPE_VENDOR |
				 USB_RECIP_DEVICE, value, index, size, data);

	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस ret;
पूर्ण

अटल पूर्णांक aqc111_ग_लिखो16_cmd_nopm(काष्ठा usbnet *dev, u8 cmd, u16 value,
				   u16 index, u16 *data)
अणु
	u16 पंचांगp = *data;

	cpu_to_le16s(&पंचांगp);

	वापस aqc111_ग_लिखो_cmd_nopm(dev, cmd, value, index, माप(पंचांगp), &पंचांगp);
पूर्ण

अटल पूर्णांक aqc111_ग_लिखो16_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value,
			      u16 index, u16 *data)
अणु
	u16 पंचांगp = *data;

	cpu_to_le16s(&पंचांगp);

	वापस aqc111_ग_लिखो_cmd(dev, cmd, value, index, माप(पंचांगp), &पंचांगp);
पूर्ण

अटल पूर्णांक aqc111_ग_लिखो32_cmd_nopm(काष्ठा usbnet *dev, u8 cmd, u16 value,
				   u16 index, u32 *data)
अणु
	u32 पंचांगp = *data;

	cpu_to_le32s(&पंचांगp);

	वापस aqc111_ग_लिखो_cmd_nopm(dev, cmd, value, index, माप(पंचांगp), &पंचांगp);
पूर्ण

अटल पूर्णांक aqc111_ग_लिखो32_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value,
			      u16 index, u32 *data)
अणु
	u32 पंचांगp = *data;

	cpu_to_le32s(&पंचांगp);

	वापस aqc111_ग_लिखो_cmd(dev, cmd, value, index, माप(पंचांगp), &पंचांगp);
पूर्ण

अटल पूर्णांक aqc111_ग_लिखो_cmd_async(काष्ठा usbnet *dev, u8 cmd, u16 value,
				  u16 index, u16 size, व्योम *data)
अणु
	वापस usbnet_ग_लिखो_cmd_async(dev, cmd, USB_सूची_OUT | USB_TYPE_VENDOR |
				      USB_RECIP_DEVICE, value, index, data,
				      size);
पूर्ण

अटल पूर्णांक aqc111_ग_लिखो16_cmd_async(काष्ठा usbnet *dev, u8 cmd, u16 value,
				    u16 index, u16 *data)
अणु
	u16 पंचांगp = *data;

	cpu_to_le16s(&पंचांगp);

	वापस aqc111_ग_लिखो_cmd_async(dev, cmd, value, index,
				      माप(पंचांगp), &पंचांगp);
पूर्ण

अटल व्योम aqc111_get_drvinfo(काष्ठा net_device *net,
			       काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;

	/* Inherit standard device info */
	usbnet_get_drvinfo(net, info);
	strlcpy(info->driver, DRIVER_NAME, माप(info->driver));
	snम_लिखो(info->fw_version, माप(info->fw_version), "%u.%u.%u",
		 aqc111_data->fw_ver.major,
		 aqc111_data->fw_ver.minor,
		 aqc111_data->fw_ver.rev);
	info->eedump_len = 0x00;
	info->regdump_len = 0x00;
पूर्ण

अटल व्योम aqc111_get_wol(काष्ठा net_device *net,
			   काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;

	wolinfo->supported = WAKE_MAGIC;
	wolinfo->wolopts = 0;

	अगर (aqc111_data->wol_flags & AQ_WOL_FLAG_MP)
		wolinfo->wolopts |= WAKE_MAGIC;
पूर्ण

अटल पूर्णांक aqc111_set_wol(काष्ठा net_device *net,
			  काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;

	अगर (wolinfo->wolopts & ~WAKE_MAGIC)
		वापस -EINVAL;

	aqc111_data->wol_flags = 0;
	अगर (wolinfo->wolopts & WAKE_MAGIC)
		aqc111_data->wol_flags |= AQ_WOL_FLAG_MP;

	वापस 0;
पूर्ण

अटल व्योम aqc111_speed_to_link_mode(u32 speed,
				      काष्ठा ethtool_link_ksettings *elk)
अणु
	चयन (speed) अणु
	हाल SPEED_5000:
		ethtool_link_ksettings_add_link_mode(elk, advertising,
						     5000baseT_Full);
		अवरोध;
	हाल SPEED_2500:
		ethtool_link_ksettings_add_link_mode(elk, advertising,
						     2500baseT_Full);
		अवरोध;
	हाल SPEED_1000:
		ethtool_link_ksettings_add_link_mode(elk, advertising,
						     1000baseT_Full);
		अवरोध;
	हाल SPEED_100:
		ethtool_link_ksettings_add_link_mode(elk, advertising,
						     100baseT_Full);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक aqc111_get_link_ksettings(काष्ठा net_device *net,
				     काष्ठा ethtool_link_ksettings *elk)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;
	क्रमागत usb_device_speed usb_speed = dev->udev->speed;
	u32 speed = SPEED_UNKNOWN;

	ethtool_link_ksettings_zero_link_mode(elk, supported);
	ethtool_link_ksettings_add_link_mode(elk, supported,
					     100baseT_Full);
	ethtool_link_ksettings_add_link_mode(elk, supported,
					     1000baseT_Full);
	अगर (usb_speed == USB_SPEED_SUPER) अणु
		ethtool_link_ksettings_add_link_mode(elk, supported,
						     2500baseT_Full);
		ethtool_link_ksettings_add_link_mode(elk, supported,
						     5000baseT_Full);
	पूर्ण
	ethtool_link_ksettings_add_link_mode(elk, supported, TP);
	ethtool_link_ksettings_add_link_mode(elk, supported, Autoneg);

	elk->base.port = PORT_TP;
	elk->base.transceiver = XCVR_INTERNAL;

	elk->base.mdio_support = 0x00; /*Not supported*/

	अगर (aqc111_data->स्वतःneg)
		linkmode_copy(elk->link_modes.advertising,
			      elk->link_modes.supported);
	अन्यथा
		aqc111_speed_to_link_mode(aqc111_data->advertised_speed, elk);

	elk->base.स्वतःneg = aqc111_data->स्वतःneg;

	चयन (aqc111_data->link_speed) अणु
	हाल AQ_INT_SPEED_5G:
		speed = SPEED_5000;
		अवरोध;
	हाल AQ_INT_SPEED_2_5G:
		speed = SPEED_2500;
		अवरोध;
	हाल AQ_INT_SPEED_1G:
		speed = SPEED_1000;
		अवरोध;
	हाल AQ_INT_SPEED_100M:
		speed = SPEED_100;
		अवरोध;
	पूर्ण
	elk->base.duplex = DUPLEX_FULL;
	elk->base.speed = speed;

	वापस 0;
पूर्ण

अटल व्योम aqc111_set_phy_speed(काष्ठा usbnet *dev, u8 स्वतःneg, u16 speed)
अणु
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;

	aqc111_data->phy_cfg &= ~AQ_ADV_MASK;
	aqc111_data->phy_cfg |= AQ_PAUSE;
	aqc111_data->phy_cfg |= AQ_ASYM_PAUSE;
	aqc111_data->phy_cfg |= AQ_DOWNSHIFT;
	aqc111_data->phy_cfg &= ~AQ_DSH_RETRIES_MASK;
	aqc111_data->phy_cfg |= (3 << AQ_DSH_RETRIES_SHIFT) &
				AQ_DSH_RETRIES_MASK;

	अगर (स्वतःneg == AUTONEG_ENABLE) अणु
		चयन (speed) अणु
		हाल SPEED_5000:
			aqc111_data->phy_cfg |= AQ_ADV_5G;
			fallthrough;
		हाल SPEED_2500:
			aqc111_data->phy_cfg |= AQ_ADV_2G5;
			fallthrough;
		हाल SPEED_1000:
			aqc111_data->phy_cfg |= AQ_ADV_1G;
			fallthrough;
		हाल SPEED_100:
			aqc111_data->phy_cfg |= AQ_ADV_100M;
			/* fall-through */
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (speed) अणु
		हाल SPEED_5000:
			aqc111_data->phy_cfg |= AQ_ADV_5G;
			अवरोध;
		हाल SPEED_2500:
			aqc111_data->phy_cfg |= AQ_ADV_2G5;
			अवरोध;
		हाल SPEED_1000:
			aqc111_data->phy_cfg |= AQ_ADV_1G;
			अवरोध;
		हाल SPEED_100:
			aqc111_data->phy_cfg |= AQ_ADV_100M;
			अवरोध;
		पूर्ण
	पूर्ण

	aqc111_ग_लिखो32_cmd(dev, AQ_PHY_OPS, 0, 0, &aqc111_data->phy_cfg);
पूर्ण

अटल पूर्णांक aqc111_set_link_ksettings(काष्ठा net_device *net,
				     स्थिर काष्ठा ethtool_link_ksettings *elk)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;
	क्रमागत usb_device_speed usb_speed = dev->udev->speed;
	u8 स्वतःneg = elk->base.स्वतःneg;
	u32 speed = elk->base.speed;

	अगर (स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (aqc111_data->स्वतःneg != AUTONEG_ENABLE) अणु
			aqc111_data->स्वतःneg = AUTONEG_ENABLE;
			aqc111_data->advertised_speed =
					(usb_speed == USB_SPEED_SUPER) ?
					 SPEED_5000 : SPEED_1000;
			aqc111_set_phy_speed(dev, aqc111_data->स्वतःneg,
					     aqc111_data->advertised_speed);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (speed != SPEED_100 &&
		    speed != SPEED_1000 &&
		    speed != SPEED_2500 &&
		    speed != SPEED_5000 &&
		    speed != SPEED_UNKNOWN)
			वापस -EINVAL;

		अगर (elk->base.duplex != DUPLEX_FULL)
			वापस -EINVAL;

		अगर (usb_speed != USB_SPEED_SUPER && speed > SPEED_1000)
			वापस -EINVAL;

		aqc111_data->स्वतःneg = AUTONEG_DISABLE;
		अगर (speed != SPEED_UNKNOWN)
			aqc111_data->advertised_speed = speed;

		aqc111_set_phy_speed(dev, aqc111_data->स्वतःneg,
				     aqc111_data->advertised_speed);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops aqc111_ethtool_ops = अणु
	.get_drvinfo = aqc111_get_drvinfo,
	.get_wol = aqc111_get_wol,
	.set_wol = aqc111_set_wol,
	.get_msglevel = usbnet_get_msglevel,
	.set_msglevel = usbnet_set_msglevel,
	.get_link = ethtool_op_get_link,
	.get_link_ksettings = aqc111_get_link_ksettings,
	.set_link_ksettings = aqc111_set_link_ksettings
पूर्ण;

अटल पूर्णांक aqc111_change_mtu(काष्ठा net_device *net, पूर्णांक new_mtu)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u16 reg16 = 0;
	u8 buf[5];

	net->mtu = new_mtu;
	dev->hard_mtu = net->mtu + net->hard_header_len;

	aqc111_पढ़ो16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
			  2, &reg16);
	अगर (net->mtu > 1500)
		reg16 |= SFR_MEDIUM_JUMBO_EN;
	अन्यथा
		reg16 &= ~SFR_MEDIUM_JUMBO_EN;

	aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
			   2, &reg16);

	अगर (dev->net->mtu > 12500) अणु
		स_नकल(buf, &AQC111_BULKIN_SIZE[2], 5);
		/* RX bulk configuration */
		aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_RX_BULKIN_QCTRL,
				 5, 5, buf);
	पूर्ण

	/* Set high low water level */
	अगर (dev->net->mtu <= 4500)
		reg16 = 0x0810;
	अन्यथा अगर (dev->net->mtu <= 9500)
		reg16 = 0x1020;
	अन्यथा अगर (dev->net->mtu <= 12500)
		reg16 = 0x1420;
	अन्यथा
		reg16 = 0x1A20;

	aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_PAUSE_WATERLVL_LOW,
			   2, &reg16);

	वापस 0;
पूर्ण

अटल पूर्णांक aqc111_set_mac_addr(काष्ठा net_device *net, व्योम *p)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	पूर्णांक ret = 0;

	ret = eth_mac_addr(net, p);
	अगर (ret < 0)
		वापस ret;

	/* Set the MAC address */
	वापस aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_NODE_ID, ETH_ALEN,
				ETH_ALEN, net->dev_addr);
पूर्ण

अटल पूर्णांक aqc111_vlan_rx_समाप्त_vid(काष्ठा net_device *net,
				   __be16 proto, u16 vid)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u8 vlan_ctrl = 0;
	u16 reg16 = 0;
	u8 reg8 = 0;

	aqc111_पढ़ो_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_CONTROL, 1, 1, &reg8);
	vlan_ctrl = reg8;

	/* Address */
	reg8 = (vid / 16);
	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_ADDRESS, 1, 1, &reg8);
	/* Data */
	reg8 = vlan_ctrl | SFR_VLAN_CONTROL_RD;
	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_CONTROL, 1, 1, &reg8);
	aqc111_पढ़ो16_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_DATA0, 2, &reg16);
	reg16 &= ~(1 << (vid % 16));
	aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_DATA0, 2, &reg16);
	reg8 = vlan_ctrl | SFR_VLAN_CONTROL_WE;
	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_CONTROL, 1, 1, &reg8);

	वापस 0;
पूर्ण

अटल पूर्णांक aqc111_vlan_rx_add_vid(काष्ठा net_device *net, __be16 proto, u16 vid)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u8 vlan_ctrl = 0;
	u16 reg16 = 0;
	u8 reg8 = 0;

	aqc111_पढ़ो_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_CONTROL, 1, 1, &reg8);
	vlan_ctrl = reg8;

	/* Address */
	reg8 = (vid / 16);
	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_ADDRESS, 1, 1, &reg8);
	/* Data */
	reg8 = vlan_ctrl | SFR_VLAN_CONTROL_RD;
	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_CONTROL, 1, 1, &reg8);
	aqc111_पढ़ो16_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_DATA0, 2, &reg16);
	reg16 |= (1 << (vid % 16));
	aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_DATA0, 2, &reg16);
	reg8 = vlan_ctrl | SFR_VLAN_CONTROL_WE;
	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_CONTROL, 1, 1, &reg8);

	वापस 0;
पूर्ण

अटल व्योम aqc111_set_rx_mode(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;
	पूर्णांक mc_count = 0;

	mc_count = netdev_mc_count(net);

	aqc111_data->rxctl &= ~(SFR_RX_CTL_PRO | SFR_RX_CTL_AMALL |
				SFR_RX_CTL_AM);

	अगर (net->flags & IFF_PROMISC) अणु
		aqc111_data->rxctl |= SFR_RX_CTL_PRO;
	पूर्ण अन्यथा अगर ((net->flags & IFF_ALLMULTI) || mc_count > AQ_MAX_MCAST) अणु
		aqc111_data->rxctl |= SFR_RX_CTL_AMALL;
	पूर्ण अन्यथा अगर (!netdev_mc_empty(net)) अणु
		u8 m_filter[AQ_MCAST_FILTER_SIZE] = अणु 0 पूर्ण;
		काष्ठा netdev_hw_addr *ha = शून्य;
		u32 crc_bits = 0;

		netdev_क्रम_each_mc_addr(ha, net) अणु
			crc_bits = ether_crc(ETH_ALEN, ha->addr) >> 26;
			m_filter[crc_bits >> 3] |= BIT(crc_bits & 7);
		पूर्ण

		aqc111_ग_लिखो_cmd_async(dev, AQ_ACCESS_MAC,
				       SFR_MULTI_FILTER_ARRY,
				       AQ_MCAST_FILTER_SIZE,
				       AQ_MCAST_FILTER_SIZE, m_filter);

		aqc111_data->rxctl |= SFR_RX_CTL_AM;
	पूर्ण

	aqc111_ग_लिखो16_cmd_async(dev, AQ_ACCESS_MAC, SFR_RX_CTL,
				 2, &aqc111_data->rxctl);
पूर्ण

अटल पूर्णांक aqc111_set_features(काष्ठा net_device *net,
			       netdev_features_t features)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;
	netdev_features_t changed = net->features ^ features;
	u16 reg16 = 0;
	u8 reg8 = 0;

	अगर (changed & NETIF_F_IP_CSUM) अणु
		aqc111_पढ़ो_cmd(dev, AQ_ACCESS_MAC, SFR_TXCOE_CTL, 1, 1, &reg8);
		reg8 ^= SFR_TXCOE_TCP | SFR_TXCOE_UDP;
		aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_TXCOE_CTL,
				 1, 1, &reg8);
	पूर्ण

	अगर (changed & NETIF_F_IPV6_CSUM) अणु
		aqc111_पढ़ो_cmd(dev, AQ_ACCESS_MAC, SFR_TXCOE_CTL, 1, 1, &reg8);
		reg8 ^= SFR_TXCOE_TCPV6 | SFR_TXCOE_UDPV6;
		aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_TXCOE_CTL,
				 1, 1, &reg8);
	पूर्ण

	अगर (changed & NETIF_F_RXCSUM) अणु
		aqc111_पढ़ो_cmd(dev, AQ_ACCESS_MAC, SFR_RXCOE_CTL, 1, 1, &reg8);
		अगर (features & NETIF_F_RXCSUM) अणु
			aqc111_data->rx_checksum = 1;
			reg8 &= ~(SFR_RXCOE_IP | SFR_RXCOE_TCP | SFR_RXCOE_UDP |
				  SFR_RXCOE_TCPV6 | SFR_RXCOE_UDPV6);
		पूर्ण अन्यथा अणु
			aqc111_data->rx_checksum = 0;
			reg8 |= SFR_RXCOE_IP | SFR_RXCOE_TCP | SFR_RXCOE_UDP |
				SFR_RXCOE_TCPV6 | SFR_RXCOE_UDPV6;
		पूर्ण

		aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_RXCOE_CTL,
				 1, 1, &reg8);
	पूर्ण
	अगर (changed & NETIF_F_HW_VLAN_CTAG_FILTER) अणु
		अगर (features & NETIF_F_HW_VLAN_CTAG_FILTER) अणु
			u16 i = 0;

			क्रम (i = 0; i < 256; i++) अणु
				/* Address */
				reg8 = i;
				aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC,
						 SFR_VLAN_ID_ADDRESS,
						 1, 1, &reg8);
				/* Data */
				aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC,
						   SFR_VLAN_ID_DATA0,
						   2, &reg16);
				reg8 = SFR_VLAN_CONTROL_WE;
				aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC,
						 SFR_VLAN_ID_CONTROL,
						 1, 1, &reg8);
			पूर्ण
			aqc111_पढ़ो_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_CONTROL,
					1, 1, &reg8);
			reg8 |= SFR_VLAN_CONTROL_VFE;
			aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC,
					 SFR_VLAN_ID_CONTROL, 1, 1, &reg8);
		पूर्ण अन्यथा अणु
			aqc111_पढ़ो_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_CONTROL,
					1, 1, &reg8);
			reg8 &= ~SFR_VLAN_CONTROL_VFE;
			aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC,
					 SFR_VLAN_ID_CONTROL, 1, 1, &reg8);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops aqc111_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_change_mtu		= aqc111_change_mtu,
	.nकरो_set_mac_address	= aqc111_set_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_vlan_rx_add_vid	= aqc111_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= aqc111_vlan_rx_समाप्त_vid,
	.nकरो_set_rx_mode	= aqc111_set_rx_mode,
	.nकरो_set_features	= aqc111_set_features,
पूर्ण;

अटल पूर्णांक aqc111_पढ़ो_perm_mac(काष्ठा usbnet *dev)
अणु
	u8 buf[ETH_ALEN];
	पूर्णांक ret;

	ret = aqc111_पढ़ो_cmd(dev, AQ_FLASH_PARAMETERS, 0, 0, ETH_ALEN, buf);
	अगर (ret < 0)
		जाओ out;

	ether_addr_copy(dev->net->perm_addr, buf);

	वापस 0;
out:
	वापस ret;
पूर्ण

अटल व्योम aqc111_पढ़ो_fw_version(काष्ठा usbnet *dev,
				   काष्ठा aqc111_data *aqc111_data)
अणु
	aqc111_पढ़ो_cmd(dev, AQ_ACCESS_MAC, AQ_FW_VER_MAJOR,
			1, 1, &aqc111_data->fw_ver.major);
	aqc111_पढ़ो_cmd(dev, AQ_ACCESS_MAC, AQ_FW_VER_MINOR,
			1, 1, &aqc111_data->fw_ver.minor);
	aqc111_पढ़ो_cmd(dev, AQ_ACCESS_MAC, AQ_FW_VER_REV,
			1, 1, &aqc111_data->fw_ver.rev);

	अगर (aqc111_data->fw_ver.major & 0x80)
		aqc111_data->fw_ver.major &= ~0x80;
पूर्ण

अटल पूर्णांक aqc111_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	क्रमागत usb_device_speed usb_speed = udev->speed;
	काष्ठा aqc111_data *aqc111_data;
	पूर्णांक ret;

	/* Check अगर venकरोr configuration */
	अगर (udev->actconfig->desc.bConfigurationValue != 1) अणु
		usb_driver_set_configuration(udev, 1);
		वापस -ENODEV;
	पूर्ण

	usb_reset_configuration(dev->udev);

	ret = usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);
	अगर (ret < 0) अणु
		netdev_dbg(dev->net, "usbnet_get_endpoints failed");
		वापस ret;
	पूर्ण

	aqc111_data = kzalloc(माप(*aqc111_data), GFP_KERNEL);
	अगर (!aqc111_data)
		वापस -ENOMEM;

	/* store aqc111_data poपूर्णांकer in device data field */
	dev->driver_priv = aqc111_data;

	/* Init the MAC address */
	ret = aqc111_पढ़ो_perm_mac(dev);
	अगर (ret)
		जाओ out;

	ether_addr_copy(dev->net->dev_addr, dev->net->perm_addr);

	/* Set Rx urb size */
	dev->rx_urb_size = URB_SIZE;

	/* Set TX needed headroom & tailroom */
	dev->net->needed_headroom += माप(u64);
	dev->net->needed_tailroom += माप(u64);

	dev->net->max_mtu = 16334;

	dev->net->netdev_ops = &aqc111_netdev_ops;
	dev->net->ethtool_ops = &aqc111_ethtool_ops;

	अगर (usb_device_no_sg_स्थिरraपूर्णांक(dev->udev))
		dev->can_dma_sg = 1;

	dev->net->hw_features |= AQ_SUPPORT_HW_FEATURE;
	dev->net->features |= AQ_SUPPORT_FEATURE;
	dev->net->vlan_features |= AQ_SUPPORT_VLAN_FEATURE;

	netअगर_set_gso_max_size(dev->net, 65535);

	aqc111_पढ़ो_fw_version(dev, aqc111_data);
	aqc111_data->स्वतःneg = AUTONEG_ENABLE;
	aqc111_data->advertised_speed = (usb_speed == USB_SPEED_SUPER) ?
					 SPEED_5000 : SPEED_1000;

	वापस 0;

out:
	kमुक्त(aqc111_data);
	वापस ret;
पूर्ण

अटल व्योम aqc111_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;
	u16 reg16;

	/* Force bz */
	reg16 = SFR_PHYPWR_RSTCTL_BZ;
	aqc111_ग_लिखो16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_PHYPWR_RSTCTL,
				2, &reg16);
	reg16 = 0;
	aqc111_ग_लिखो16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_PHYPWR_RSTCTL,
				2, &reg16);

	/* Power करोwn ethernet PHY */
	aqc111_data->phy_cfg &= ~AQ_ADV_MASK;
	aqc111_data->phy_cfg |= AQ_LOW_POWER;
	aqc111_data->phy_cfg &= ~AQ_PHY_POWER_EN;
	aqc111_ग_लिखो32_cmd_nopm(dev, AQ_PHY_OPS, 0, 0,
				&aqc111_data->phy_cfg);

	kमुक्त(aqc111_data);
पूर्ण

अटल व्योम aqc111_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;
	u64 *event_data = शून्य;
	पूर्णांक link = 0;

	अगर (urb->actual_length < माप(*event_data))
		वापस;

	event_data = urb->transfer_buffer;
	le64_to_cpus(event_data);

	अगर (*event_data & AQ_LS_MASK)
		link = 1;
	अन्यथा
		link = 0;

	aqc111_data->link_speed = (*event_data & AQ_SPEED_MASK) >>
				  AQ_SPEED_SHIFT;
	aqc111_data->link = link;

	अगर (netअगर_carrier_ok(dev->net) != link)
		usbnet_defer_kevent(dev, EVENT_LINK_RESET);
पूर्ण

अटल व्योम aqc111_configure_rx(काष्ठा usbnet *dev,
				काष्ठा aqc111_data *aqc111_data)
अणु
	क्रमागत usb_device_speed usb_speed = dev->udev->speed;
	u16 link_speed = 0, usb_host = 0;
	u8 buf[5] = अणु 0 पूर्ण;
	u8 queue_num = 0;
	u16 reg16 = 0;
	u8 reg8 = 0;

	buf[0] = 0x00;
	buf[1] = 0xF8;
	buf[2] = 0x07;
	चयन (aqc111_data->link_speed) अणु
	हाल AQ_INT_SPEED_5G:
		link_speed = 5000;
		reg8 = 0x05;
		reg16 = 0x001F;
		अवरोध;
	हाल AQ_INT_SPEED_2_5G:
		link_speed = 2500;
		reg16 = 0x003F;
		अवरोध;
	हाल AQ_INT_SPEED_1G:
		link_speed = 1000;
		reg16 = 0x009F;
		अवरोध;
	हाल AQ_INT_SPEED_100M:
		link_speed = 100;
		queue_num = 1;
		reg16 = 0x063F;
		buf[1] = 0xFB;
		buf[2] = 0x4;
		अवरोध;
	पूर्ण

	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_INTER_PACKET_GAP_0,
			 1, 1, &reg8);

	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_TX_PAUSE_RESEND_T, 3, 3, buf);

	चयन (usb_speed) अणु
	हाल USB_SPEED_SUPER:
		usb_host = 3;
		अवरोध;
	हाल USB_SPEED_HIGH:
		usb_host = 2;
		अवरोध;
	हाल USB_SPEED_FULL:
	हाल USB_SPEED_LOW:
		usb_host = 1;
		queue_num = 0;
		अवरोध;
	शेष:
		usb_host = 0;
		अवरोध;
	पूर्ण

	अगर (dev->net->mtu > 12500 && dev->net->mtu <= 16334)
		queue_num = 2; /* For Jumbo packet 16KB */

	स_नकल(buf, &AQC111_BULKIN_SIZE[queue_num], 5);
	/* RX bulk configuration */
	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_RX_BULKIN_QCTRL, 5, 5, buf);

	/* Set high low water level */
	अगर (dev->net->mtu <= 4500)
		reg16 = 0x0810;
	अन्यथा अगर (dev->net->mtu <= 9500)
		reg16 = 0x1020;
	अन्यथा अगर (dev->net->mtu <= 12500)
		reg16 = 0x1420;
	अन्यथा अगर (dev->net->mtu <= 16334)
		reg16 = 0x1A20;

	aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_PAUSE_WATERLVL_LOW,
			   2, &reg16);
	netdev_info(dev->net, "Link Speed %d, USB %d", link_speed, usb_host);
पूर्ण

अटल व्योम aqc111_configure_csum_offload(काष्ठा usbnet *dev)
अणु
	u8 reg8 = 0;

	अगर (dev->net->features & NETIF_F_RXCSUM) अणु
		reg8 |= SFR_RXCOE_IP | SFR_RXCOE_TCP | SFR_RXCOE_UDP |
			SFR_RXCOE_TCPV6 | SFR_RXCOE_UDPV6;
	पूर्ण
	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_RXCOE_CTL, 1, 1, &reg8);

	reg8 = 0;
	अगर (dev->net->features & NETIF_F_IP_CSUM)
		reg8 |= SFR_TXCOE_IP | SFR_TXCOE_TCP | SFR_TXCOE_UDP;

	अगर (dev->net->features & NETIF_F_IPV6_CSUM)
		reg8 |= SFR_TXCOE_TCPV6 | SFR_TXCOE_UDPV6;

	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_TXCOE_CTL, 1, 1, &reg8);
पूर्ण

अटल पूर्णांक aqc111_link_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;
	u16 reg16 = 0;
	u8 reg8 = 0;

	अगर (aqc111_data->link == 1) अणु /* Link up */
		aqc111_configure_rx(dev, aqc111_data);

		/* Vlan Tag Filter */
		reg8 = SFR_VLAN_CONTROL_VSO;
		अगर (dev->net->features & NETIF_F_HW_VLAN_CTAG_FILTER)
			reg8 |= SFR_VLAN_CONTROL_VFE;

		aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_CONTROL,
				 1, 1, &reg8);

		reg8 = 0x0;
		aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_BMRX_DMA_CONTROL,
				 1, 1, &reg8);

		aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_BMTX_DMA_CONTROL,
				 1, 1, &reg8);

		aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_ARC_CTRL, 1, 1, &reg8);

		reg16 = SFR_RX_CTL_IPE | SFR_RX_CTL_AB;
		aqc111_data->rxctl = reg16;
		aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_RX_CTL, 2, &reg16);

		reg8 = SFR_RX_PATH_READY;
		aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_ETH_MAC_PATH,
				 1, 1, &reg8);

		reg8 = SFR_BULK_OUT_EFF_EN;
		aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_BULK_OUT_CTRL,
				 1, 1, &reg8);

		reg16 = 0;
		aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				   2, &reg16);

		reg16 = SFR_MEDIUM_XGMIIMODE | SFR_MEDIUM_FULL_DUPLEX;
		aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				   2, &reg16);

		aqc111_configure_csum_offload(dev);

		aqc111_set_rx_mode(dev->net);

		aqc111_पढ़ो16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				  2, &reg16);

		अगर (dev->net->mtu > 1500)
			reg16 |= SFR_MEDIUM_JUMBO_EN;

		reg16 |= SFR_MEDIUM_RECEIVE_EN | SFR_MEDIUM_RXFLOW_CTRLEN |
			 SFR_MEDIUM_TXFLOW_CTRLEN;
		aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				   2, &reg16);

		aqc111_data->rxctl |= SFR_RX_CTL_START;
		aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_RX_CTL,
				   2, &aqc111_data->rxctl);

		netअगर_carrier_on(dev->net);
	पूर्ण अन्यथा अणु
		aqc111_पढ़ो16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				  2, &reg16);
		reg16 &= ~SFR_MEDIUM_RECEIVE_EN;
		aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				   2, &reg16);

		aqc111_data->rxctl &= ~SFR_RX_CTL_START;
		aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_RX_CTL,
				   2, &aqc111_data->rxctl);

		reg8 = SFR_BULK_OUT_FLUSH_EN | SFR_BULK_OUT_EFF_EN;
		aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_BULK_OUT_CTRL,
				 1, 1, &reg8);
		reg8 = SFR_BULK_OUT_EFF_EN;
		aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_BULK_OUT_CTRL,
				 1, 1, &reg8);

		netअगर_carrier_off(dev->net);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक aqc111_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;
	u8 reg8 = 0;

	dev->rx_urb_size = URB_SIZE;

	अगर (usb_device_no_sg_स्थिरraपूर्णांक(dev->udev))
		dev->can_dma_sg = 1;

	dev->net->hw_features |= AQ_SUPPORT_HW_FEATURE;
	dev->net->features |= AQ_SUPPORT_FEATURE;
	dev->net->vlan_features |= AQ_SUPPORT_VLAN_FEATURE;

	/* Power up ethernet PHY */
	aqc111_data->phy_cfg = AQ_PHY_POWER_EN;
	aqc111_ग_लिखो32_cmd(dev, AQ_PHY_OPS, 0, 0,
			   &aqc111_data->phy_cfg);

	/* Set the MAC address */
	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_NODE_ID, ETH_ALEN,
			 ETH_ALEN, dev->net->dev_addr);

	reg8 = 0xFF;
	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_BM_INT_MASK, 1, 1, &reg8);

	reg8 = 0x0;
	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_SWP_CTRL, 1, 1, &reg8);

	aqc111_पढ़ो_cmd(dev, AQ_ACCESS_MAC, SFR_MONITOR_MODE, 1, 1, &reg8);
	reg8 &= ~(SFR_MONITOR_MODE_EPHYRW | SFR_MONITOR_MODE_RWLC |
		  SFR_MONITOR_MODE_RWMP | SFR_MONITOR_MODE_RWWF |
		  SFR_MONITOR_MODE_RW_FLAG);
	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_MONITOR_MODE, 1, 1, &reg8);

	netअगर_carrier_off(dev->net);

	/* Phy advertise */
	aqc111_set_phy_speed(dev, aqc111_data->स्वतःneg,
			     aqc111_data->advertised_speed);

	वापस 0;
पूर्ण

अटल पूर्णांक aqc111_stop(काष्ठा usbnet *dev)
अणु
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;
	u16 reg16 = 0;

	aqc111_पढ़ो16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
			  2, &reg16);
	reg16 &= ~SFR_MEDIUM_RECEIVE_EN;
	aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
			   2, &reg16);
	reg16 = 0;
	aqc111_ग_लिखो16_cmd(dev, AQ_ACCESS_MAC, SFR_RX_CTL, 2, &reg16);

	/* Put PHY to low घातer*/
	aqc111_data->phy_cfg |= AQ_LOW_POWER;
	aqc111_ग_लिखो32_cmd(dev, AQ_PHY_OPS, 0, 0,
			   &aqc111_data->phy_cfg);

	netअगर_carrier_off(dev->net);

	वापस 0;
पूर्ण

अटल व्योम aqc111_rx_checksum(काष्ठा sk_buff *skb, u64 pkt_desc)
अणु
	u32 pkt_type = 0;

	skb->ip_summed = CHECKSUM_NONE;
	/* checksum error bit is set */
	अगर (pkt_desc & AQ_RX_PD_L4_ERR || pkt_desc & AQ_RX_PD_L3_ERR)
		वापस;

	pkt_type = pkt_desc & AQ_RX_PD_L4_TYPE_MASK;
	/* It must be a TCP or UDP packet with a valid checksum */
	अगर (pkt_type == AQ_RX_PD_L4_TCP || pkt_type == AQ_RX_PD_L4_UDP)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
पूर्ण

अटल पूर्णांक aqc111_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;
	काष्ठा sk_buff *new_skb = शून्य;
	u32 pkt_total_offset = 0;
	u64 *pkt_desc_ptr = शून्य;
	u32 start_of_descs = 0;
	u32 desc_offset = 0; /*RX Header Offset*/
	u16 pkt_count = 0;
	u64 desc_hdr = 0;
	u16 vlan_tag = 0;
	u32 skb_len = 0;

	अगर (!skb)
		जाओ err;

	अगर (skb->len == 0)
		जाओ err;

	skb_len = skb->len;
	/* RX Descriptor Header */
	skb_trim(skb, skb->len - माप(desc_hdr));
	desc_hdr = le64_to_cpup((u64 *)skb_tail_poपूर्णांकer(skb));

	/* Check these packets */
	desc_offset = (desc_hdr & AQ_RX_DH_DESC_OFFSET_MASK) >>
		      AQ_RX_DH_DESC_OFFSET_SHIFT;
	pkt_count = desc_hdr & AQ_RX_DH_PKT_CNT_MASK;
	start_of_descs = skb_len - ((pkt_count + 1) *  माप(desc_hdr));

	/* self check descs position */
	अगर (start_of_descs != desc_offset)
		जाओ err;

	/* self check desc_offset from header*/
	अगर (desc_offset >= skb_len)
		जाओ err;

	अगर (pkt_count == 0)
		जाओ err;

	/* Get the first RX packet descriptor */
	pkt_desc_ptr = (u64 *)(skb->data + desc_offset);

	जबतक (pkt_count--) अणु
		u64 pkt_desc = le64_to_cpup(pkt_desc_ptr);
		u32 pkt_len_with_padd = 0;
		u32 pkt_len = 0;

		pkt_len = (u32)((pkt_desc & AQ_RX_PD_LEN_MASK) >>
			  AQ_RX_PD_LEN_SHIFT);
		pkt_len_with_padd = ((pkt_len + 7) & 0x7FFF8);

		pkt_total_offset += pkt_len_with_padd;
		अगर (pkt_total_offset > desc_offset ||
		    (pkt_count == 0 && pkt_total_offset != desc_offset)) अणु
			जाओ err;
		पूर्ण

		अगर (pkt_desc & AQ_RX_PD_DROP ||
		    !(pkt_desc & AQ_RX_PD_RX_OK) ||
		    pkt_len > (dev->hard_mtu + AQ_RX_HW_PAD)) अणु
			skb_pull(skb, pkt_len_with_padd);
			/* Next RX Packet Descriptor */
			pkt_desc_ptr++;
			जारी;
		पूर्ण

		/* Clone SKB */
		new_skb = skb_clone(skb, GFP_ATOMIC);

		अगर (!new_skb)
			जाओ err;

		new_skb->len = pkt_len;
		skb_pull(new_skb, AQ_RX_HW_PAD);
		skb_set_tail_poपूर्णांकer(new_skb, new_skb->len);

		new_skb->truesize = SKB_TRUESIZE(new_skb->len);
		अगर (aqc111_data->rx_checksum)
			aqc111_rx_checksum(new_skb, pkt_desc);

		अगर (pkt_desc & AQ_RX_PD_VLAN) अणु
			vlan_tag = pkt_desc >> AQ_RX_PD_VLAN_SHIFT;
			__vlan_hwaccel_put_tag(new_skb, htons(ETH_P_8021Q),
					       vlan_tag & VLAN_VID_MASK);
		पूर्ण

		usbnet_skb_वापस(dev, new_skb);
		अगर (pkt_count == 0)
			अवरोध;

		skb_pull(skb, pkt_len_with_padd);

		/* Next RX Packet Header */
		pkt_desc_ptr++;

		new_skb = शून्य;
	पूर्ण

	वापस 1;

err:
	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *aqc111_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb,
				       gfp_t flags)
अणु
	पूर्णांक frame_size = dev->maxpacket;
	काष्ठा sk_buff *new_skb = शून्य;
	u64 *tx_desc_ptr = शून्य;
	पूर्णांक padding_size = 0;
	पूर्णांक headroom = 0;
	पूर्णांक tailroom = 0;
	u64 tx_desc = 0;
	u16 tci = 0;

	/*Length of actual data*/
	tx_desc |= skb->len & AQ_TX_DESC_LEN_MASK;

	/* TSO MSS */
	tx_desc |= ((u64)(skb_shinfo(skb)->gso_size & AQ_TX_DESC_MSS_MASK)) <<
		   AQ_TX_DESC_MSS_SHIFT;

	headroom = (skb->len + माप(tx_desc)) % 8;
	अगर (headroom != 0)
		padding_size = 8 - headroom;

	अगर (((skb->len + माप(tx_desc) + padding_size) % frame_size) == 0) अणु
		padding_size += 8;
		tx_desc |= AQ_TX_DESC_DROP_PADD;
	पूर्ण

	/* Vlan Tag */
	अगर (vlan_get_tag(skb, &tci) >= 0) अणु
		tx_desc |= AQ_TX_DESC_VLAN;
		tx_desc |= ((u64)tci & AQ_TX_DESC_VLAN_MASK) <<
			   AQ_TX_DESC_VLAN_SHIFT;
	पूर्ण

	अगर (!dev->can_dma_sg && (dev->net->features & NETIF_F_SG) &&
	    skb_linearize(skb))
		वापस शून्य;

	headroom = skb_headroom(skb);
	tailroom = skb_tailroom(skb);

	अगर (!(headroom >= माप(tx_desc) && tailroom >= padding_size)) अणु
		new_skb = skb_copy_expand(skb, माप(tx_desc),
					  padding_size, flags);
		dev_kमुक्त_skb_any(skb);
		skb = new_skb;
		अगर (!skb)
			वापस शून्य;
	पूर्ण
	अगर (padding_size != 0)
		skb_put_zero(skb, padding_size);
	/* Copy TX header */
	tx_desc_ptr = skb_push(skb, माप(tx_desc));
	*tx_desc_ptr = cpu_to_le64(tx_desc);

	usbnet_set_skb_tx_stats(skb, 1, 0);

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा driver_info aqc111_info = अणु
	.description	= "Aquantia AQtion USB to 5GbE Controller",
	.bind		= aqc111_bind,
	.unbind		= aqc111_unbind,
	.status		= aqc111_status,
	.link_reset	= aqc111_link_reset,
	.reset		= aqc111_reset,
	.stop		= aqc111_stop,
	.flags		= FLAG_ETHER | FLAG_FRAMING_AX |
			  FLAG_AVOID_UNLINK_URBS | FLAG_MULTI_PACKET,
	.rx_fixup	= aqc111_rx_fixup,
	.tx_fixup	= aqc111_tx_fixup,
पूर्ण;

#घोषणा ASIX111_DESC \
"ASIX USB 3.1 Gen1 to 5G Multi-Gigabit Ethernet Adapter"

अटल स्थिर काष्ठा driver_info asix111_info = अणु
	.description	= ASIX111_DESC,
	.bind		= aqc111_bind,
	.unbind		= aqc111_unbind,
	.status		= aqc111_status,
	.link_reset	= aqc111_link_reset,
	.reset		= aqc111_reset,
	.stop		= aqc111_stop,
	.flags		= FLAG_ETHER | FLAG_FRAMING_AX |
			  FLAG_AVOID_UNLINK_URBS | FLAG_MULTI_PACKET,
	.rx_fixup	= aqc111_rx_fixup,
	.tx_fixup	= aqc111_tx_fixup,
पूर्ण;

#अघोषित ASIX111_DESC

#घोषणा ASIX112_DESC \
"ASIX USB 3.1 Gen1 to 2.5G Multi-Gigabit Ethernet Adapter"

अटल स्थिर काष्ठा driver_info asix112_info = अणु
	.description	= ASIX112_DESC,
	.bind		= aqc111_bind,
	.unbind		= aqc111_unbind,
	.status		= aqc111_status,
	.link_reset	= aqc111_link_reset,
	.reset		= aqc111_reset,
	.stop		= aqc111_stop,
	.flags		= FLAG_ETHER | FLAG_FRAMING_AX |
			  FLAG_AVOID_UNLINK_URBS | FLAG_MULTI_PACKET,
	.rx_fixup	= aqc111_rx_fixup,
	.tx_fixup	= aqc111_tx_fixup,
पूर्ण;

#अघोषित ASIX112_DESC

अटल स्थिर काष्ठा driver_info trendnet_info = अणु
	.description	= "USB-C 3.1 to 5GBASE-T Ethernet Adapter",
	.bind		= aqc111_bind,
	.unbind		= aqc111_unbind,
	.status		= aqc111_status,
	.link_reset	= aqc111_link_reset,
	.reset		= aqc111_reset,
	.stop		= aqc111_stop,
	.flags		= FLAG_ETHER | FLAG_FRAMING_AX |
			  FLAG_AVOID_UNLINK_URBS | FLAG_MULTI_PACKET,
	.rx_fixup	= aqc111_rx_fixup,
	.tx_fixup	= aqc111_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info qnap_info = अणु
	.description	= "QNAP QNA-UC5G1T USB to 5GbE Adapter",
	.bind		= aqc111_bind,
	.unbind		= aqc111_unbind,
	.status		= aqc111_status,
	.link_reset	= aqc111_link_reset,
	.reset		= aqc111_reset,
	.stop		= aqc111_stop,
	.flags		= FLAG_ETHER | FLAG_FRAMING_AX |
			  FLAG_AVOID_UNLINK_URBS | FLAG_MULTI_PACKET,
	.rx_fixup	= aqc111_rx_fixup,
	.tx_fixup	= aqc111_tx_fixup,
पूर्ण;

अटल पूर्णांक aqc111_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;
	u16 temp_rx_ctrl = 0x00;
	u16 reg16;
	u8 reg8;

	usbnet_suspend(पूर्णांकf, message);

	aqc111_पढ़ो16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_CTL, 2, &reg16);
	temp_rx_ctrl = reg16;
	/* Stop RX operations*/
	reg16 &= ~SFR_RX_CTL_START;
	aqc111_ग_लिखो16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_CTL, 2, &reg16);
	/* Force bz */
	aqc111_पढ़ो16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_PHYPWR_RSTCTL,
			       2, &reg16);
	reg16 |= SFR_PHYPWR_RSTCTL_BZ;
	aqc111_ग_लिखो16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_PHYPWR_RSTCTL,
				2, &reg16);

	reg8 = SFR_BULK_OUT_EFF_EN;
	aqc111_ग_लिखो_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_BULK_OUT_CTRL,
			      1, 1, &reg8);

	temp_rx_ctrl &= ~(SFR_RX_CTL_START | SFR_RX_CTL_RF_WAK |
			  SFR_RX_CTL_AP | SFR_RX_CTL_AM);
	aqc111_ग_लिखो16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_CTL,
				2, &temp_rx_ctrl);

	reg8 = 0x00;
	aqc111_ग_लिखो_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_ETH_MAC_PATH,
			      1, 1, &reg8);

	अगर (aqc111_data->wol_flags) अणु
		काष्ठा aqc111_wol_cfg wol_cfg;

		स_रखो(&wol_cfg, 0, माप(काष्ठा aqc111_wol_cfg));

		aqc111_data->phy_cfg |= AQ_WOL;
		ether_addr_copy(wol_cfg.hw_addr, dev->net->dev_addr);
		wol_cfg.flags = aqc111_data->wol_flags;

		temp_rx_ctrl |= (SFR_RX_CTL_AB | SFR_RX_CTL_START);
		aqc111_ग_लिखो16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_CTL,
					2, &temp_rx_ctrl);
		reg8 = 0x00;
		aqc111_ग_लिखो_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_BM_INT_MASK,
				      1, 1, &reg8);
		reg8 = SFR_BMRX_DMA_EN;
		aqc111_ग_लिखो_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_BMRX_DMA_CONTROL,
				      1, 1, &reg8);
		reg8 = SFR_RX_PATH_READY;
		aqc111_ग_लिखो_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_ETH_MAC_PATH,
				      1, 1, &reg8);
		reg8 = 0x07;
		aqc111_ग_लिखो_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_BULKIN_QCTRL,
				      1, 1, &reg8);
		reg8 = 0x00;
		aqc111_ग_लिखो_cmd_nopm(dev, AQ_ACCESS_MAC,
				      SFR_RX_BULKIN_QTIMR_LOW, 1, 1, &reg8);
		aqc111_ग_लिखो_cmd_nopm(dev, AQ_ACCESS_MAC,
				      SFR_RX_BULKIN_QTIMR_HIGH, 1, 1, &reg8);
		reg8 = 0xFF;
		aqc111_ग_लिखो_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_BULKIN_QSIZE,
				      1, 1, &reg8);
		aqc111_ग_लिखो_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_BULKIN_QIFG,
				      1, 1, &reg8);

		aqc111_पढ़ो16_cmd_nopm(dev, AQ_ACCESS_MAC,
				       SFR_MEDIUM_STATUS_MODE, 2, &reg16);
		reg16 |= SFR_MEDIUM_RECEIVE_EN;
		aqc111_ग_लिखो16_cmd_nopm(dev, AQ_ACCESS_MAC,
					SFR_MEDIUM_STATUS_MODE, 2, &reg16);

		aqc111_ग_लिखो_cmd(dev, AQ_WOL_CFG, 0, 0,
				 WOL_CFG_SIZE, &wol_cfg);
		aqc111_ग_लिखो32_cmd(dev, AQ_PHY_OPS, 0, 0,
				   &aqc111_data->phy_cfg);
	पूर्ण अन्यथा अणु
		aqc111_data->phy_cfg |= AQ_LOW_POWER;
		aqc111_ग_लिखो32_cmd(dev, AQ_PHY_OPS, 0, 0,
				   &aqc111_data->phy_cfg);

		/* Disable RX path */
		aqc111_पढ़ो16_cmd_nopm(dev, AQ_ACCESS_MAC,
				       SFR_MEDIUM_STATUS_MODE, 2, &reg16);
		reg16 &= ~SFR_MEDIUM_RECEIVE_EN;
		aqc111_ग_लिखो16_cmd_nopm(dev, AQ_ACCESS_MAC,
					SFR_MEDIUM_STATUS_MODE, 2, &reg16);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aqc111_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा aqc111_data *aqc111_data = dev->driver_priv;
	u16 reg16;
	u8 reg8;

	netअगर_carrier_off(dev->net);

	/* Power up ethernet PHY */
	aqc111_data->phy_cfg |= AQ_PHY_POWER_EN;
	aqc111_data->phy_cfg &= ~AQ_LOW_POWER;
	aqc111_data->phy_cfg &= ~AQ_WOL;

	reg8 = 0xFF;
	aqc111_ग_लिखो_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_BM_INT_MASK,
			      1, 1, &reg8);
	/* Configure RX control रेजिस्टर => start operation */
	reg16 = aqc111_data->rxctl;
	reg16 &= ~SFR_RX_CTL_START;
	aqc111_ग_लिखो16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_CTL, 2, &reg16);

	reg16 |= SFR_RX_CTL_START;
	aqc111_ग_लिखो16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_RX_CTL, 2, &reg16);

	aqc111_set_phy_speed(dev, aqc111_data->स्वतःneg,
			     aqc111_data->advertised_speed);

	aqc111_पढ़ो16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
			       2, &reg16);
	reg16 |= SFR_MEDIUM_RECEIVE_EN;
	aqc111_ग_लिखो16_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_MEDIUM_STATUS_MODE,
				2, &reg16);
	reg8 = SFR_RX_PATH_READY;
	aqc111_ग_लिखो_cmd_nopm(dev, AQ_ACCESS_MAC, SFR_ETH_MAC_PATH,
			      1, 1, &reg8);
	reg8 = 0x0;
	aqc111_ग_लिखो_cmd(dev, AQ_ACCESS_MAC, SFR_BMRX_DMA_CONTROL, 1, 1, &reg8);

	वापस usbnet_resume(पूर्णांकf);
पूर्ण

#घोषणा AQC111_USB_ETH_DEV(vid, pid, table) \
	USB_DEVICE_INTERFACE_CLASS((vid), (pid), USB_CLASS_VENDOR_SPEC), \
	.driver_info = (अचिन्हित दीर्घ)&(table) \
पूर्ण, \
अणु \
	USB_DEVICE_AND_INTERFACE_INFO((vid), (pid), \
				      USB_CLASS_COMM, \
				      USB_CDC_SUBCLASS_ETHERNET, \
				      USB_CDC_PROTO_NONE), \
	.driver_info = (अचिन्हित दीर्घ)&(table),

अटल स्थिर काष्ठा usb_device_id products[] = अणु
	अणुAQC111_USB_ETH_DEV(0x2eca, 0xc101, aqc111_info)पूर्ण,
	अणुAQC111_USB_ETH_DEV(0x0b95, 0x2790, asix111_info)पूर्ण,
	अणुAQC111_USB_ETH_DEV(0x0b95, 0x2791, asix112_info)पूर्ण,
	अणुAQC111_USB_ETH_DEV(0x20f4, 0xe05a, trendnet_info)पूर्ण,
	अणुAQC111_USB_ETH_DEV(0x1c04, 0x0015, qnap_info)पूर्ण,
	अणु पूर्ण,/* END */
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver aq_driver = अणु
	.name		= "aqc111",
	.id_table	= products,
	.probe		= usbnet_probe,
	.suspend	= aqc111_suspend,
	.resume		= aqc111_resume,
	.disconnect	= usbnet_disconnect,
पूर्ण;

module_usb_driver(aq_driver);

MODULE_DESCRIPTION("Aquantia AQtion USB to 5/2.5GbE Controllers");
MODULE_LICENSE("GPL");
