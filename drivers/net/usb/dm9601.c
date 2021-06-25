<शैली गुरु>
/*
 * Davicom DM96xx USB 10/100Mbps ethernet devices
 *
 * Peter Korsgaard <jacmet@sunsite.dk>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

//#घोषणा DEBUG

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
#समावेश <linux/slab.h>

/* datasheet:
 http://pपंचांग2.cc.utu.fi/ftp/network/cards/DM9601/From_NET/DM9601-DS-P01-930914.pdf
*/

/* control requests */
#घोषणा DM_READ_REGS	0x00
#घोषणा DM_WRITE_REGS	0x01
#घोषणा DM_READ_MEMS	0x02
#घोषणा DM_WRITE_REG	0x03
#घोषणा DM_WRITE_MEMS	0x05
#घोषणा DM_WRITE_MEM	0x07

/* रेजिस्टरs */
#घोषणा DM_NET_CTRL	0x00
#घोषणा DM_RX_CTRL	0x05
#घोषणा DM_SHARED_CTRL	0x0b
#घोषणा DM_SHARED_ADDR	0x0c
#घोषणा DM_SHARED_DATA	0x0d	/* low + high */
#घोषणा DM_PHY_ADDR	0x10	/* 6 bytes */
#घोषणा DM_MCAST_ADDR	0x16	/* 8 bytes */
#घोषणा DM_GPR_CTRL	0x1e
#घोषणा DM_GPR_DATA	0x1f
#घोषणा DM_CHIP_ID	0x2c
#घोषणा DM_MODE_CTRL	0x91	/* only on dm9620 */

/* chip id values */
#घोषणा ID_DM9601	0
#घोषणा ID_DM9620	1

#घोषणा DM_MAX_MCAST	64
#घोषणा DM_MCAST_SIZE	8
#घोषणा DM_EEPROM_LEN	256
#घोषणा DM_TX_OVERHEAD	2	/* 2 byte header */
#घोषणा DM_RX_OVERHEAD	7	/* 3 byte header + 4 byte crc tail */
#घोषणा DM_TIMEOUT	1000

अटल पूर्णांक dm_पढ़ो(काष्ठा usbnet *dev, u8 reg, u16 length, व्योम *data)
अणु
	पूर्णांक err;
	err = usbnet_पढ़ो_cmd(dev, DM_READ_REGS,
			       USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			       0, reg, data, length);
	अगर(err != length && err >= 0)
		err = -EINVAL;
	वापस err;
पूर्ण

अटल पूर्णांक dm_पढ़ो_reg(काष्ठा usbnet *dev, u8 reg, u8 *value)
अणु
	वापस dm_पढ़ो(dev, reg, 1, value);
पूर्ण

अटल पूर्णांक dm_ग_लिखो(काष्ठा usbnet *dev, u8 reg, u16 length, व्योम *data)
अणु
	पूर्णांक err;
	err = usbnet_ग_लिखो_cmd(dev, DM_WRITE_REGS,
				USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0, reg, data, length);

	अगर (err >= 0 && err < length)
		err = -EINVAL;
	वापस err;
पूर्ण

अटल पूर्णांक dm_ग_लिखो_reg(काष्ठा usbnet *dev, u8 reg, u8 value)
अणु
	वापस usbnet_ग_लिखो_cmd(dev, DM_WRITE_REG,
				USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				value, reg, शून्य, 0);
पूर्ण

अटल व्योम dm_ग_लिखो_async(काष्ठा usbnet *dev, u8 reg, u16 length, व्योम *data)
अणु
	usbnet_ग_लिखो_cmd_async(dev, DM_WRITE_REGS,
			       USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			       0, reg, data, length);
पूर्ण

अटल व्योम dm_ग_लिखो_reg_async(काष्ठा usbnet *dev, u8 reg, u8 value)
अणु
	usbnet_ग_लिखो_cmd_async(dev, DM_WRITE_REG,
			       USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			       value, reg, शून्य, 0);
पूर्ण

अटल पूर्णांक dm_पढ़ो_shared_word(काष्ठा usbnet *dev, पूर्णांक phy, u8 reg, __le16 *value)
अणु
	पूर्णांक ret, i;

	mutex_lock(&dev->phy_mutex);

	dm_ग_लिखो_reg(dev, DM_SHARED_ADDR, phy ? (reg | 0x40) : reg);
	dm_ग_लिखो_reg(dev, DM_SHARED_CTRL, phy ? 0xc : 0x4);

	क्रम (i = 0; i < DM_TIMEOUT; i++) अणु
		u8 पंचांगp = 0;

		udelay(1);
		ret = dm_पढ़ो_reg(dev, DM_SHARED_CTRL, &पंचांगp);
		अगर (ret < 0)
			जाओ out;

		/* पढ़ोy */
		अगर ((पंचांगp & 1) == 0)
			अवरोध;
	पूर्ण

	अगर (i == DM_TIMEOUT) अणु
		netdev_err(dev->net, "%s read timed out!\n", phy ? "phy" : "eeprom");
		ret = -EIO;
		जाओ out;
	पूर्ण

	dm_ग_लिखो_reg(dev, DM_SHARED_CTRL, 0x0);
	ret = dm_पढ़ो(dev, DM_SHARED_DATA, 2, value);

	netdev_dbg(dev->net, "read shared %d 0x%02x returned 0x%04x, %d\n",
		   phy, reg, *value, ret);

 out:
	mutex_unlock(&dev->phy_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dm_ग_लिखो_shared_word(काष्ठा usbnet *dev, पूर्णांक phy, u8 reg, __le16 value)
अणु
	पूर्णांक ret, i;

	mutex_lock(&dev->phy_mutex);

	ret = dm_ग_लिखो(dev, DM_SHARED_DATA, 2, &value);
	अगर (ret < 0)
		जाओ out;

	dm_ग_लिखो_reg(dev, DM_SHARED_ADDR, phy ? (reg | 0x40) : reg);
	dm_ग_लिखो_reg(dev, DM_SHARED_CTRL, phy ? 0x1a : 0x12);

	क्रम (i = 0; i < DM_TIMEOUT; i++) अणु
		u8 पंचांगp = 0;

		udelay(1);
		ret = dm_पढ़ो_reg(dev, DM_SHARED_CTRL, &पंचांगp);
		अगर (ret < 0)
			जाओ out;

		/* पढ़ोy */
		अगर ((पंचांगp & 1) == 0)
			अवरोध;
	पूर्ण

	अगर (i == DM_TIMEOUT) अणु
		netdev_err(dev->net, "%s write timed out!\n", phy ? "phy" : "eeprom");
		ret = -EIO;
		जाओ out;
	पूर्ण

	dm_ग_लिखो_reg(dev, DM_SHARED_CTRL, 0x0);

out:
	mutex_unlock(&dev->phy_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dm_पढ़ो_eeprom_word(काष्ठा usbnet *dev, u8 offset, व्योम *value)
अणु
	वापस dm_पढ़ो_shared_word(dev, 0, offset, value);
पूर्ण



अटल पूर्णांक dm9601_get_eeprom_len(काष्ठा net_device *dev)
अणु
	वापस DM_EEPROM_LEN;
पूर्ण

अटल पूर्णांक dm9601_get_eeprom(काष्ठा net_device *net,
			     काष्ठा ethtool_eeprom *eeprom, u8 * data)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	__le16 *ebuf = (__le16 *) data;
	पूर्णांक i;

	/* access is 16bit */
	अगर ((eeprom->offset % 2) || (eeprom->len % 2))
		वापस -EINVAL;

	क्रम (i = 0; i < eeprom->len / 2; i++) अणु
		अगर (dm_पढ़ो_eeprom_word(dev, eeprom->offset / 2 + i,
					&ebuf[i]) < 0)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dm9601_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);

	__le16 res;

	अगर (phy_id) अणु
		netdev_dbg(dev->net, "Only internal phy supported\n");
		वापस 0;
	पूर्ण

	dm_पढ़ो_shared_word(dev, 1, loc, &res);

	netdev_dbg(dev->net,
		   "dm9601_mdio_read() phy_id=0x%02x, loc=0x%02x, returns=0x%04x\n",
		   phy_id, loc, le16_to_cpu(res));

	वापस le16_to_cpu(res);
पूर्ण

अटल व्योम dm9601_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc,
			      पूर्णांक val)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	__le16 res = cpu_to_le16(val);

	अगर (phy_id) अणु
		netdev_dbg(dev->net, "Only internal phy supported\n");
		वापस;
	पूर्ण

	netdev_dbg(dev->net, "dm9601_mdio_write() phy_id=0x%02x, loc=0x%02x, val=0x%04x\n",
		   phy_id, loc, val);

	dm_ग_लिखो_shared_word(dev, 1, loc, res);
पूर्ण

अटल व्योम dm9601_get_drvinfo(काष्ठा net_device *net,
			       काष्ठा ethtool_drvinfo *info)
अणु
	/* Inherit standard device info */
	usbnet_get_drvinfo(net, info);
पूर्ण

अटल u32 dm9601_get_link(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	वापस mii_link_ok(&dev->mii);
पूर्ण

अटल पूर्णांक dm9601_ioctl(काष्ठा net_device *net, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	वापस generic_mii_ioctl(&dev->mii, अगर_mii(rq), cmd, शून्य);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops dm9601_ethtool_ops = अणु
	.get_drvinfo	= dm9601_get_drvinfo,
	.get_link	= dm9601_get_link,
	.get_msglevel	= usbnet_get_msglevel,
	.set_msglevel	= usbnet_set_msglevel,
	.get_eeprom_len	= dm9601_get_eeprom_len,
	.get_eeprom	= dm9601_get_eeprom,
	.nway_reset	= usbnet_nway_reset,
	.get_link_ksettings	= usbnet_get_link_ksettings_mii,
	.set_link_ksettings	= usbnet_set_link_ksettings_mii,
पूर्ण;

अटल व्योम dm9601_set_multicast(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	/* We use the 20 byte dev->data क्रम our 8 byte filter buffer
	 * to aव्योम allocating memory that is tricky to मुक्त later */
	u8 *hashes = (u8 *) & dev->data;
	u8 rx_ctl = 0x31;

	स_रखो(hashes, 0x00, DM_MCAST_SIZE);
	hashes[DM_MCAST_SIZE - 1] |= 0x80;	/* broadcast address */

	अगर (net->flags & IFF_PROMISC) अणु
		rx_ctl |= 0x02;
	पूर्ण अन्यथा अगर (net->flags & IFF_ALLMULTI ||
		   netdev_mc_count(net) > DM_MAX_MCAST) अणु
		rx_ctl |= 0x08;
	पूर्ण अन्यथा अगर (!netdev_mc_empty(net)) अणु
		काष्ठा netdev_hw_addr *ha;

		netdev_क्रम_each_mc_addr(ha, net) अणु
			u32 crc = ether_crc(ETH_ALEN, ha->addr) >> 26;
			hashes[crc >> 3] |= 1 << (crc & 0x7);
		पूर्ण
	पूर्ण

	dm_ग_लिखो_async(dev, DM_MCAST_ADDR, DM_MCAST_SIZE, hashes);
	dm_ग_लिखो_reg_async(dev, DM_RX_CTRL, rx_ctl);
पूर्ण

अटल व्योम __dm9601_set_mac_address(काष्ठा usbnet *dev)
अणु
	dm_ग_लिखो_async(dev, DM_PHY_ADDR, ETH_ALEN, dev->net->dev_addr);
पूर्ण

अटल पूर्णांक dm9601_set_mac_address(काष्ठा net_device *net, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा usbnet *dev = netdev_priv(net);

	अगर (!is_valid_ether_addr(addr->sa_data)) अणु
		dev_err(&net->dev, "not setting invalid mac address %pM\n",
								addr->sa_data);
		वापस -EINVAL;
	पूर्ण

	स_नकल(net->dev_addr, addr->sa_data, net->addr_len);
	__dm9601_set_mac_address(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops dm9601_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_change_mtu		= usbnet_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl 		= dm9601_ioctl,
	.nकरो_set_rx_mode	= dm9601_set_multicast,
	.nकरो_set_mac_address	= dm9601_set_mac_address,
पूर्ण;

अटल पूर्णांक dm9601_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret;
	u8 mac[ETH_ALEN], id;

	ret = usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);
	अगर (ret)
		जाओ out;

	dev->net->netdev_ops = &dm9601_netdev_ops;
	dev->net->ethtool_ops = &dm9601_ethtool_ops;
	dev->net->hard_header_len += DM_TX_OVERHEAD;
	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;

	/* dm9620/21a require room क्रम 4 byte padding, even in dm9601
	 * mode, so we need +1 to be able to receive full size
	 * ethernet frames.
	 */
	dev->rx_urb_size = dev->net->mtu + ETH_HLEN + DM_RX_OVERHEAD + 1;

	dev->mii.dev = dev->net;
	dev->mii.mdio_पढ़ो = dm9601_mdio_पढ़ो;
	dev->mii.mdio_ग_लिखो = dm9601_mdio_ग_लिखो;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0x1f;

	/* reset */
	dm_ग_लिखो_reg(dev, DM_NET_CTRL, 1);
	udelay(20);

	/* पढ़ो MAC */
	अगर (dm_पढ़ो(dev, DM_PHY_ADDR, ETH_ALEN, mac) < 0) अणु
		prपूर्णांकk(KERN_ERR "Error reading MAC address\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/*
	 * Overग_लिखो the स्वतः-generated address only with good ones.
	 */
	अगर (is_valid_ether_addr(mac))
		स_नकल(dev->net->dev_addr, mac, ETH_ALEN);
	अन्यथा अणु
		prपूर्णांकk(KERN_WARNING
			"dm9601: No valid MAC address in EEPROM, using %pM\n",
			dev->net->dev_addr);
		__dm9601_set_mac_address(dev);
	पूर्ण

	अगर (dm_पढ़ो_reg(dev, DM_CHIP_ID, &id) < 0) अणु
		netdev_err(dev->net, "Error reading chip ID\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* put dm9620 devices in dm9601 mode */
	अगर (id == ID_DM9620) अणु
		u8 mode;

		अगर (dm_पढ़ो_reg(dev, DM_MODE_CTRL, &mode) < 0) अणु
			netdev_err(dev->net, "Error reading MODE_CTRL\n");
			ret = -ENODEV;
			जाओ out;
		पूर्ण
		dm_ग_लिखो_reg(dev, DM_MODE_CTRL, mode & 0x7f);
	पूर्ण

	/* घातer up phy */
	dm_ग_लिखो_reg(dev, DM_GPR_CTRL, 1);
	dm_ग_लिखो_reg(dev, DM_GPR_DATA, 0);

	/* receive broadcast packets */
	dm9601_set_multicast(dev->net);

	dm9601_mdio_ग_लिखो(dev->net, dev->mii.phy_id, MII_BMCR, BMCR_RESET);
	dm9601_mdio_ग_लिखो(dev->net, dev->mii.phy_id, MII_ADVERTISE,
			  ADVERTISE_ALL | ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP);
	mii_nway_restart(&dev->mii);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक dm9601_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	u8 status;
	पूर्णांक len;

	/* क्रमmat:
	   b1: rx status
	   b2: packet length (incl crc) low
	   b3: packet length (incl crc) high
	   b4..n-4: packet data
	   bn-3..bn: ethernet crc
	 */

	अगर (unlikely(skb->len < DM_RX_OVERHEAD)) अणु
		dev_err(&dev->udev->dev, "unexpected tiny rx frame\n");
		वापस 0;
	पूर्ण

	status = skb->data[0];
	len = (skb->data[1] | (skb->data[2] << 8)) - 4;

	अगर (unlikely(status & 0xbf)) अणु
		अगर (status & 0x01) dev->net->stats.rx_fअगरo_errors++;
		अगर (status & 0x02) dev->net->stats.rx_crc_errors++;
		अगर (status & 0x04) dev->net->stats.rx_frame_errors++;
		अगर (status & 0x20) dev->net->stats.rx_missed_errors++;
		अगर (status & 0x90) dev->net->stats.rx_length_errors++;
		वापस 0;
	पूर्ण

	skb_pull(skb, 3);
	skb_trim(skb, len);

	वापस 1;
पूर्ण

अटल काष्ठा sk_buff *dm9601_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb,
				       gfp_t flags)
अणु
	पूर्णांक len, pad;

	/* क्रमmat:
	   b1: packet length low
	   b2: packet length high
	   b3..n: packet data
	*/

	len = skb->len + DM_TX_OVERHEAD;

	/* workaround क्रम dm962x errata with tx fअगरo getting out of
	 * sync अगर a USB bulk transfer retry happens right after a
	 * packet with odd / maxpacket length by adding up to 3 bytes
	 * padding.
	 */
	जबतक ((len & 1) || !(len % dev->maxpacket))
		len++;

	len -= DM_TX_OVERHEAD; /* hw header करोesn't count as part of length */
	pad = len - skb->len;

	अगर (skb_headroom(skb) < DM_TX_OVERHEAD || skb_tailroom(skb) < pad) अणु
		काष्ठा sk_buff *skb2;

		skb2 = skb_copy_expand(skb, DM_TX_OVERHEAD, pad, flags);
		dev_kमुक्त_skb_any(skb);
		skb = skb2;
		अगर (!skb)
			वापस शून्य;
	पूर्ण

	__skb_push(skb, DM_TX_OVERHEAD);

	अगर (pad) अणु
		स_रखो(skb->data + skb->len, 0, pad);
		__skb_put(skb, pad);
	पूर्ण

	skb->data[0] = len;
	skb->data[1] = len >> 8;

	वापस skb;
पूर्ण

अटल व्योम dm9601_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
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

अटल पूर्णांक dm9601_link_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा ethtool_cmd ecmd = अणु .cmd = ETHTOOL_GSET पूर्ण;

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);

	netdev_dbg(dev->net, "link_reset() speed: %u duplex: %d\n",
		   ethtool_cmd_speed(&ecmd), ecmd.duplex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा driver_info dm9601_info = अणु
	.description	= "Davicom DM96xx USB 10/100 Ethernet",
	.flags		= FLAG_ETHER | FLAG_LINK_INTR,
	.bind		= dm9601_bind,
	.rx_fixup	= dm9601_rx_fixup,
	.tx_fixup	= dm9601_tx_fixup,
	.status		= dm9601_status,
	.link_reset	= dm9601_link_reset,
	.reset		= dm9601_link_reset,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id products[] = अणु
	अणु
	 USB_DEVICE(0x07aa, 0x9601),	/* Corega FEther USB-TXC */
	 .driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	 पूर्ण,
	अणु
	 USB_DEVICE(0x0a46, 0x9601),	/* Davicom USB-100 */
	 .driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	 पूर्ण,
	अणु
	 USB_DEVICE(0x0a46, 0x6688),	/* ZT6688 USB NIC */
	 .driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	 पूर्ण,
	अणु
	 USB_DEVICE(0x0a46, 0x0268),	/* ShanTou ST268 USB NIC */
	 .driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	 पूर्ण,
	अणु
	 USB_DEVICE(0x0a46, 0x8515),	/* ADMtek ADM8515 USB NIC */
	 .driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	 पूर्ण,
	अणु
	USB_DEVICE(0x0a47, 0x9601),	/* Hirose USB-100 */
	.driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	 पूर्ण,
	अणु
	USB_DEVICE(0x0fe6, 0x8101),	/* DM9601 USB to Fast Ethernet Adapter */
	.driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	 पूर्ण,
	अणु
	 USB_DEVICE(0x0fe6, 0x9700),	/* DM9601 USB to Fast Ethernet Adapter */
	 .driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	 पूर्ण,
	अणु
	 USB_DEVICE(0x0a46, 0x9000),	/* DM9000E */
	 .driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	 पूर्ण,
	अणु
	 USB_DEVICE(0x0a46, 0x9620),	/* DM9620 USB to Fast Ethernet Adapter */
	 .driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	 पूर्ण,
	अणु
	 USB_DEVICE(0x0a46, 0x9621),	/* DM9621A USB to Fast Ethernet Adapter */
	 .driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	पूर्ण,
	अणु
	 USB_DEVICE(0x0a46, 0x9622),	/* DM9622 USB to Fast Ethernet Adapter */
	 .driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	पूर्ण,
	अणु
	 USB_DEVICE(0x0a46, 0x0269),	/* DM962OA USB to Fast Ethernet Adapter */
	 .driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	पूर्ण,
	अणु
	 USB_DEVICE(0x0a46, 0x1269),	/* DM9621A USB to Fast Ethernet Adapter */
	 .driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	पूर्ण,
	अणु
	 USB_DEVICE(0x0586, 0x3427),	/* ZyXEL Keenetic Plus DSL xDSL modem */
	 .driver_info = (अचिन्हित दीर्घ)&dm9601_info,
	पूर्ण,
	अणुपूर्ण,			// END
पूर्ण;

MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver dm9601_driver = अणु
	.name = "dm9601",
	.id_table = products,
	.probe = usbnet_probe,
	.disconnect = usbnet_disconnect,
	.suspend = usbnet_suspend,
	.resume = usbnet_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(dm9601_driver);

MODULE_AUTHOR("Peter Korsgaard <jacmet@sunsite.dk>");
MODULE_DESCRIPTION("Davicom DM96xx USB 10/100 ethernet devices");
MODULE_LICENSE("GPL");
