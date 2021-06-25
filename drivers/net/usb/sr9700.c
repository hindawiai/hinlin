<शैली गुरु>
/*
 * CoreChip-sz SR9700 one chip USB 1.1 Ethernet Devices
 *
 * Author : Liu Junliang <liujunliang_ljl@163.com>
 *
 * Based on dm9601.c
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/crc32.h>
#समावेश <linux/usb/usbnet.h>

#समावेश "sr9700.h"

अटल पूर्णांक sr_पढ़ो(काष्ठा usbnet *dev, u8 reg, u16 length, व्योम *data)
अणु
	पूर्णांक err;

	err = usbnet_पढ़ो_cmd(dev, SR_RD_REGS, SR_REQ_RD_REG, 0, reg, data,
			      length);
	अगर ((err != length) && (err >= 0))
		err = -EINVAL;
	वापस err;
पूर्ण

अटल पूर्णांक sr_ग_लिखो(काष्ठा usbnet *dev, u8 reg, u16 length, व्योम *data)
अणु
	पूर्णांक err;

	err = usbnet_ग_लिखो_cmd(dev, SR_WR_REGS, SR_REQ_WR_REG, 0, reg, data,
			       length);
	अगर ((err >= 0) && (err < length))
		err = -EINVAL;
	वापस err;
पूर्ण

अटल पूर्णांक sr_पढ़ो_reg(काष्ठा usbnet *dev, u8 reg, u8 *value)
अणु
	वापस sr_पढ़ो(dev, reg, 1, value);
पूर्ण

अटल पूर्णांक sr_ग_लिखो_reg(काष्ठा usbnet *dev, u8 reg, u8 value)
अणु
	वापस usbnet_ग_लिखो_cmd(dev, SR_WR_REGS, SR_REQ_WR_REG,
				value, reg, शून्य, 0);
पूर्ण

अटल व्योम sr_ग_लिखो_async(काष्ठा usbnet *dev, u8 reg, u16 length, व्योम *data)
अणु
	usbnet_ग_लिखो_cmd_async(dev, SR_WR_REGS, SR_REQ_WR_REG,
			       0, reg, data, length);
पूर्ण

अटल व्योम sr_ग_लिखो_reg_async(काष्ठा usbnet *dev, u8 reg, u8 value)
अणु
	usbnet_ग_लिखो_cmd_async(dev, SR_WR_REGS, SR_REQ_WR_REG,
			       value, reg, शून्य, 0);
पूर्ण

अटल पूर्णांक रुको_phy_eeprom_पढ़ोy(काष्ठा usbnet *dev, पूर्णांक phy)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SR_SHARE_TIMEOUT; i++) अणु
		u8 पंचांगp = 0;
		पूर्णांक ret;

		udelay(1);
		ret = sr_पढ़ो_reg(dev, SR_EPCR, &पंचांगp);
		अगर (ret < 0)
			वापस ret;

		/* पढ़ोy */
		अगर (!(पंचांगp & EPCR_ERRE))
			वापस 0;
	पूर्ण

	netdev_err(dev->net, "%s write timed out!\n", phy ? "phy" : "eeprom");

	वापस -EIO;
पूर्ण

अटल पूर्णांक sr_share_पढ़ो_word(काष्ठा usbnet *dev, पूर्णांक phy, u8 reg,
			      __le16 *value)
अणु
	पूर्णांक ret;

	mutex_lock(&dev->phy_mutex);

	sr_ग_लिखो_reg(dev, SR_EPAR, phy ? (reg | EPAR_PHY_ADR) : reg);
	sr_ग_लिखो_reg(dev, SR_EPCR, phy ? (EPCR_EPOS | EPCR_ERPRR) : EPCR_ERPRR);

	ret = रुको_phy_eeprom_पढ़ोy(dev, phy);
	अगर (ret < 0)
		जाओ out_unlock;

	sr_ग_लिखो_reg(dev, SR_EPCR, 0x0);
	ret = sr_पढ़ो(dev, SR_EPDR, 2, value);

	netdev_dbg(dev->net, "read shared %d 0x%02x returned 0x%04x, %d\n",
		   phy, reg, *value, ret);

out_unlock:
	mutex_unlock(&dev->phy_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक sr_share_ग_लिखो_word(काष्ठा usbnet *dev, पूर्णांक phy, u8 reg,
			       __le16 value)
अणु
	पूर्णांक ret;

	mutex_lock(&dev->phy_mutex);

	ret = sr_ग_लिखो(dev, SR_EPDR, 2, &value);
	अगर (ret < 0)
		जाओ out_unlock;

	sr_ग_लिखो_reg(dev, SR_EPAR, phy ? (reg | EPAR_PHY_ADR) : reg);
	sr_ग_लिखो_reg(dev, SR_EPCR, phy ? (EPCR_WEP | EPCR_EPOS | EPCR_ERPRW) :
		    (EPCR_WEP | EPCR_ERPRW));

	ret = रुको_phy_eeprom_पढ़ोy(dev, phy);
	अगर (ret < 0)
		जाओ out_unlock;

	sr_ग_लिखो_reg(dev, SR_EPCR, 0x0);

out_unlock:
	mutex_unlock(&dev->phy_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक sr_पढ़ो_eeprom_word(काष्ठा usbnet *dev, u8 offset, व्योम *value)
अणु
	वापस sr_share_पढ़ो_word(dev, 0, offset, value);
पूर्ण

अटल पूर्णांक sr9700_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	वापस SR_EEPROM_LEN;
पूर्ण

अटल पूर्णांक sr9700_get_eeprom(काष्ठा net_device *netdev,
			     काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	__le16 *buf = (__le16 *)data;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* access is 16bit */
	अगर ((eeprom->offset & 0x01) || (eeprom->len & 0x01))
		वापस -EINVAL;

	क्रम (i = 0; i < eeprom->len / 2; i++) अणु
		ret = sr_पढ़ो_eeprom_word(dev, eeprom->offset / 2 + i, buf + i);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sr_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	__le16 res;
	पूर्णांक rc = 0;

	अगर (phy_id) अणु
		netdev_dbg(netdev, "Only internal phy supported\n");
		वापस 0;
	पूर्ण

	/* Access NSR_LINKST bit क्रम link status instead of MII_BMSR */
	अगर (loc == MII_BMSR) अणु
		u8 value;

		sr_पढ़ो_reg(dev, SR_NSR, &value);
		अगर (value & NSR_LINKST)
			rc = 1;
	पूर्ण
	sr_share_पढ़ो_word(dev, 1, loc, &res);
	अगर (rc == 1)
		res = le16_to_cpu(res) | BMSR_LSTATUS;
	अन्यथा
		res = le16_to_cpu(res) & ~BMSR_LSTATUS;

	netdev_dbg(netdev, "sr_mdio_read() phy_id=0x%02x, loc=0x%02x, returns=0x%04x\n",
		   phy_id, loc, res);

	वापस res;
पूर्ण

अटल व्योम sr_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc,
			  पूर्णांक val)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	__le16 res = cpu_to_le16(val);

	अगर (phy_id) अणु
		netdev_dbg(netdev, "Only internal phy supported\n");
		वापस;
	पूर्ण

	netdev_dbg(netdev, "sr_mdio_write() phy_id=0x%02x, loc=0x%02x, val=0x%04x\n",
		   phy_id, loc, val);

	sr_share_ग_लिखो_word(dev, 1, loc, res);
पूर्ण

अटल u32 sr9700_get_link(काष्ठा net_device *netdev)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	u8 value = 0;
	पूर्णांक rc = 0;

	/* Get the Link Status directly */
	sr_पढ़ो_reg(dev, SR_NSR, &value);
	अगर (value & NSR_LINKST)
		rc = 1;

	वापस rc;
पूर्ण

अटल पूर्णांक sr9700_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);

	वापस generic_mii_ioctl(&dev->mii, अगर_mii(rq), cmd, शून्य);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops sr9700_ethtool_ops = अणु
	.get_drvinfo	= usbnet_get_drvinfo,
	.get_link	= sr9700_get_link,
	.get_msglevel	= usbnet_get_msglevel,
	.set_msglevel	= usbnet_set_msglevel,
	.get_eeprom_len	= sr9700_get_eeprom_len,
	.get_eeprom	= sr9700_get_eeprom,
	.nway_reset	= usbnet_nway_reset,
	.get_link_ksettings	= usbnet_get_link_ksettings_mii,
	.set_link_ksettings	= usbnet_set_link_ksettings_mii,
पूर्ण;

अटल व्योम sr9700_set_multicast(काष्ठा net_device *netdev)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	/* We use the 20 byte dev->data क्रम our 8 byte filter buffer
	 * to aव्योम allocating memory that is tricky to मुक्त later
	 */
	u8 *hashes = (u8 *)&dev->data;
	/* rx_ctl setting : enable, disable_दीर्घ, disable_crc */
	u8 rx_ctl = RCR_RXEN | RCR_DIS_CRC | RCR_DIS_LONG;

	स_रखो(hashes, 0x00, SR_MCAST_SIZE);
	/* broadcast address */
	hashes[SR_MCAST_SIZE - 1] |= SR_MCAST_ADDR_FLAG;
	अगर (netdev->flags & IFF_PROMISC) अणु
		rx_ctl |= RCR_PRMSC;
	पूर्ण अन्यथा अगर (netdev->flags & IFF_ALLMULTI ||
		   netdev_mc_count(netdev) > SR_MCAST_MAX) अणु
		rx_ctl |= RCR_RUNT;
	पूर्ण अन्यथा अगर (!netdev_mc_empty(netdev)) अणु
		काष्ठा netdev_hw_addr *ha;

		netdev_क्रम_each_mc_addr(ha, netdev) अणु
			u32 crc = ether_crc(ETH_ALEN, ha->addr) >> 26;
			hashes[crc >> 3] |= 1 << (crc & 0x7);
		पूर्ण
	पूर्ण

	sr_ग_लिखो_async(dev, SR_MAR, SR_MCAST_SIZE, hashes);
	sr_ग_लिखो_reg_async(dev, SR_RCR, rx_ctl);
पूर्ण

अटल पूर्णांक sr9700_set_mac_address(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data)) अणु
		netdev_err(netdev, "not setting invalid mac address %pM\n",
			   addr->sa_data);
		वापस -EINVAL;
	पूर्ण

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	sr_ग_लिखो_async(dev, SR_PAR, 6, netdev->dev_addr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops sr9700_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_change_mtu		= usbnet_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= sr9700_ioctl,
	.nकरो_set_rx_mode	= sr9700_set_multicast,
	.nकरो_set_mac_address	= sr9700_set_mac_address,
पूर्ण;

अटल पूर्णांक sr9700_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा net_device *netdev;
	काष्ठा mii_अगर_info *mii;
	पूर्णांक ret;

	ret = usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);
	अगर (ret)
		जाओ out;

	netdev = dev->net;

	netdev->netdev_ops = &sr9700_netdev_ops;
	netdev->ethtool_ops = &sr9700_ethtool_ops;
	netdev->hard_header_len += SR_TX_OVERHEAD;
	dev->hard_mtu = netdev->mtu + netdev->hard_header_len;
	/* bulkin buffer is preferably not less than 3K */
	dev->rx_urb_size = 3072;

	mii = &dev->mii;
	mii->dev = netdev;
	mii->mdio_पढ़ो = sr_mdio_पढ़ो;
	mii->mdio_ग_लिखो = sr_mdio_ग_लिखो;
	mii->phy_id_mask = 0x1f;
	mii->reg_num_mask = 0x1f;

	sr_ग_लिखो_reg(dev, SR_NCR, NCR_RST);
	udelay(20);

	/* पढ़ो MAC
	 * After Chip Power on, the Chip will reload the MAC from
	 * EEPROM स्वतःmatically to PAR. In हाल there is no EEPROM बाह्यally,
	 * a शेष MAC address is stored in PAR क्रम making chip work properly.
	 */
	अगर (sr_पढ़ो(dev, SR_PAR, ETH_ALEN, netdev->dev_addr) < 0) अणु
		netdev_err(netdev, "Error reading MAC address\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* घातer up and reset phy */
	sr_ग_लिखो_reg(dev, SR_PRR, PRR_PHY_RST);
	/* at least 10ms, here 20ms क्रम safe */
	msleep(20);
	sr_ग_लिखो_reg(dev, SR_PRR, 0);
	/* at least 1ms, here 2ms क्रम पढ़ोing right रेजिस्टर */
	udelay(2 * 1000);

	/* receive broadcast packets */
	sr9700_set_multicast(netdev);

	sr_mdio_ग_लिखो(netdev, mii->phy_id, MII_BMCR, BMCR_RESET);
	sr_mdio_ग_लिखो(netdev, mii->phy_id, MII_ADVERTISE, ADVERTISE_ALL |
		      ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP);
	mii_nway_restart(mii);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक sr9700_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *sr_skb;
	पूर्णांक len;

	/* skb content (packets) क्रमmat :
	 *                    p0            p1            p2    ......    pm
	 *                 /      \
	 *            /                \
	 *        /                            \
	 *  /                                        \
	 * p0b0 p0b1 p0b2 p0b3 ...... p0b(n-4) p0b(n-3)...p0bn
	 *
	 * p0 : packet 0
	 * p0b0 : packet 0 byte 0
	 *
	 * b0: rx status
	 * b1: packet length (incl crc) low
	 * b2: packet length (incl crc) high
	 * b3..n-4: packet data
	 * bn-3..bn: ethernet packet crc
	 */
	अगर (unlikely(skb->len < SR_RX_OVERHEAD)) अणु
		netdev_err(dev->net, "unexpected tiny rx frame\n");
		वापस 0;
	पूर्ण

	/* one skb may contains multiple packets */
	जबतक (skb->len > SR_RX_OVERHEAD) अणु
		अगर (skb->data[0] != 0x40)
			वापस 0;

		/* ignore the CRC length */
		len = (skb->data[1] | (skb->data[2] << 8)) - 4;

		अगर (len > ETH_FRAME_LEN)
			वापस 0;

		/* the last packet of current skb */
		अगर (skb->len == (len + SR_RX_OVERHEAD))	अणु
			skb_pull(skb, 3);
			skb->len = len;
			skb_set_tail_poपूर्णांकer(skb, len);
			skb->truesize = len + माप(काष्ठा sk_buff);
			वापस 2;
		पूर्ण

		/* skb_clone is used क्रम address align */
		sr_skb = skb_clone(skb, GFP_ATOMIC);
		अगर (!sr_skb)
			वापस 0;

		sr_skb->len = len;
		sr_skb->data = skb->data + 3;
		skb_set_tail_poपूर्णांकer(sr_skb, len);
		sr_skb->truesize = len + माप(काष्ठा sk_buff);
		usbnet_skb_वापस(dev, sr_skb);

		skb_pull(skb, len + SR_RX_OVERHEAD);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *sr9700_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb,
				       gfp_t flags)
अणु
	पूर्णांक len;

	/* SR9700 can only send out one ethernet packet at once.
	 *
	 * b0 b1 b2 b3 ...... b(n-4) b(n-3)...bn
	 *
	 * b0: rx status
	 * b1: packet length (incl crc) low
	 * b2: packet length (incl crc) high
	 * b3..n-4: packet data
	 * bn-3..bn: ethernet packet crc
	 */

	len = skb->len;

	अगर (skb_cow_head(skb, SR_TX_OVERHEAD)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण

	__skb_push(skb, SR_TX_OVERHEAD);

	/* usbnet adds padding अगर length is a multiple of packet size
	 * अगर so, adjust length value in header
	 */
	अगर ((skb->len % dev->maxpacket) == 0)
		len++;

	skb->data[0] = len;
	skb->data[1] = len >> 8;

	वापस skb;
पूर्ण

अटल व्योम sr9700_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	पूर्णांक link;
	u8 *buf;

	/* क्रमmat:
	   b0: net status
	   b1: tx status 1
	   b2: tx status 2
	   b3: rx status
	   b4: rx overflow
	   b5: rx count
	   b6: tx count
	   b7: gpr
	*/

	अगर (urb->actual_length < 8)
		वापस;

	buf = urb->transfer_buffer;

	link = !!(buf[0] & 0x40);
	अगर (netअगर_carrier_ok(dev->net) != link) अणु
		usbnet_link_change(dev, link, 1);
		netdev_dbg(dev->net, "Link Status is: %d\n", link);
	पूर्ण
पूर्ण

अटल पूर्णांक sr9700_link_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा ethtool_cmd ecmd;

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);

	netdev_dbg(dev->net, "link_reset() speed: %d duplex: %d\n",
		   ecmd.speed, ecmd.duplex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा driver_info sr9700_driver_info = अणु
	.description	= "CoreChip SR9700 USB Ethernet",
	.flags		= FLAG_ETHER,
	.bind		= sr9700_bind,
	.rx_fixup	= sr9700_rx_fixup,
	.tx_fixup	= sr9700_tx_fixup,
	.status		= sr9700_status,
	.link_reset	= sr9700_link_reset,
	.reset		= sr9700_link_reset,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id products[] = अणु
	अणु
		USB_DEVICE(0x0fe6, 0x9700),	/* SR9700 device */
		.driver_info = (अचिन्हित दीर्घ)&sr9700_driver_info,
	पूर्ण,
	अणुपूर्ण,			/* END */
पूर्ण;

MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver sr9700_usb_driver = अणु
	.name		= "sr9700",
	.id_table	= products,
	.probe		= usbnet_probe,
	.disconnect	= usbnet_disconnect,
	.suspend	= usbnet_suspend,
	.resume		= usbnet_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(sr9700_usb_driver);

MODULE_AUTHOR("liujl <liujunliang_ljl@163.com>");
MODULE_DESCRIPTION("SR9700 one chip USB 1.1 USB to Ethernet device from http://www.corechip-sz.com/");
MODULE_LICENSE("GPL");
